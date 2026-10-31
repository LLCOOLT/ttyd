#include <dolphin.h>
#include <dolphin/gx.h>
#include <demo.h>
#include <dolphin/mtx.h>

#include "__demo.h"

static GXTexObj fontTexObj;

static s32 fontShift;
static OSFontHeader* FontData;
static void* LastSheet;
static s16 FontSize;
static s16 FontSpace;

// prototypes
static void DrawFontChar(int x, int y, int z, int xChar, int yChar);
static void LoadSheet(void* image, GXTexMapID texMapID);

/** Sets the GX blend mode for demo text: reversed (inverse copy), translucent (additive) or opaque. */
void DEMOSetFontType(s32 attr) {
    switch(attr) {
    case DM_FT_RVS:
        GXSetBlendMode(GX_BM_LOGIC, GX_BL_ZERO, GX_BL_ZERO, GX_LO_INVCOPY);
        break;
    case DM_FT_XLU:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
        break;
    case DM_FT_OPQ:
    default:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
        break;
    }
}

/**
 * Loads the built-in 64-pixel-wide I4 bitmap font as a texture into the given texture map with a texture matrix
 * for it, point-sampled or filtered, and sets one texture coordinate generator.
 */
void DEMOLoadFont(GXTexMapID texMap, GXTexMtx texMtx, DMTexFlt texFlt) {
    Mtx fontTMtx;
    u16 width;
    u16 height;

    width = 64;
    height = 0x1800 / width;
    GXInitTexObj(&fontTexObj, (void*)DEMOFontBitmap, width, (u16)height, GX_TF_I4, GX_CLAMP, GX_CLAMP, 0);

    if (texFlt == DMTF_POINTSAMPLE) {
        GXInitTexObjLOD(&fontTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        fontShift = 0;
    } else {
        fontShift = 1;
    }

    GXLoadTexObj(&fontTexObj, texMap);
    MTXScale(fontTMtx, 1.0f / width, 1.0f / height, 1.0f);
    GXLoadTexMtxImm(fontTMtx, texMtx, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, texMtx);
}

/**
 * Sets an orthographic projection over 'width' by 'height' screen pixels with an identity position matrix
 * (shifted by -0.667 on the second field for field rendering), for 2D text drawing.
 */
void DEMOSetupScrnSpc(s32 width, s32 height, f32 depth) {
    Mtx44 pMtx;
    Mtx mMtx;
    f32 top;

    if (DEMOGetRenderModeObj()->field_rendering && !VIGetNextField()) {
        top = -0.667f;
    } else {
        top = 0.0f;
    }

    MTXOrtho(pMtx, top, height, 0.0f, width, 0.0f, -depth);
    GXSetProjection(pMtx, GX_ORTHOGRAPHIC);
    MTXIdentity(mMtx);
    GXLoadPosMtxImm(mMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

/**
 * Sets up GX for drawing 8x8 caption text: screen-space projection, texture-only TEV stage replacing the colour,
 * the font texture and the font blend type.
 */
void DEMOInitCaption(s32 font_type, s32 width, s32 height) {
    DEMOSetupScrnSpc(width, height, 100.0f);
    GXSetZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    DEMOLoadFont(GX_TEXMAP0, GX_TEXMTX0, DMTF_POINTSAMPLE);
    DEMOSetFontType(font_type);
}

/**
 * Draws an ASCII string (characters 0x20-0x7F, 8x8 pixels each) at x, y, z with the built-in bitmap font;
 * a newline moves down 8 pixels and any other control character ends the string.
 */
void DEMOPuts(s16 x, s16 y, s16 z, char* string) {
    char* str;
    s32 s;
    s32 t;
    s32 c;
    s32 w;
    s32 len;
    s32 i;

    str = string;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 1);

    // calc len
    len = 0;
    while (1) {
        c = *(str++);
        if ((c >= 0x20) && (c <= 0x7F)) {
            len++;
            continue;
        }

        if (len > 0) {
            GXBegin(GX_QUADS, GX_VTXFMT0, len * 4);
            for(i = 0; i < len; i++) {
                w = string[i] - 0x20;
                s = fontShift + ((w % 8) * 0x10);
                t = fontShift + ((w / 8) * 0x10);
                GXPosition3s16(x + (i * 8), y, z);
                GXTexCoord2s16(s, t);
                GXPosition3s16(x + (i * 8) + 8, y, z);
                GXTexCoord2s16(s + 0x10, t);
                GXPosition3s16(x + (i * 8) + 8, y + 8, z);
                GXTexCoord2s16(s + 0x10, t + 0x10);
                GXPosition3s16(x + (i * 8), y + 8, z);
                GXTexCoord2s16(s, t + 0x10);
            }
            GXEnd();
            len = 0;
        }

        string = str;
        if (c == 0xA) {
            y += 0x8;
        } else {
            break;
        }
    }
}

/** printf front end to DEMOPuts (256-byte buffer). */
void DEMOPrintf(s16 x, s16 y, s16 z, char* fmt, ...) {
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    DEMOPuts(x, y, z, buf);
    va_end(vlist);
}

/**
 * Allocates and loads the console's built-in ROM font (Shift-JIS or ANSI by the OS font encoding)
 * and sets the default size and spacing. Panics if there is no memory or the boot ROM is too old.
 */
OSFontHeader* DEMOInitROMFont(void) {
    switch (OSGetFontEncode()) {
    case OS_FONT_ENCODE_SJIS:
        FontData = OSAlloc(OS_FONT_SIZE_SJIS);
        break;
    case OS_FONT_ENCODE_ANSI:
        FontData = OSAlloc(OS_FONT_SIZE_ANSI);
        break;
    default:
        FontData = OSAlloc(0x141020);
        break;
    }

    if (!FontData) {
        OSPanic(__FILE__, 446, "Ins. memory to load ROM font.");
    }

    if (OSInitFont(FontData) == 0) {
        OSPanic(__FILE__, 450, "ROM font is available in boot ROM ver 0.8 or later.");
    }

    FontSize = FontData->cellWidth * 16;
    FontSpace = -16;
    return FontData;
}

/** Sets the ROM font cell size and the extra space between characters (stored in 1/16 pixel units). */
void DEMOSetROMFontSize(s16 size, s16 space) {
    FontSize = size * 16;
    FontSpace = space * 16;
}

/** Reads the ROM font cell size and spacing back in pixels (either pointer may be NULL). */
void DEMOGetROMFontSize(s16* size, s16* space) {
    if (size != 0) {
        *size = FontSize / 16;
    }

    if (space != 0) {
        *space = FontSpace / 16;
    }
}

/**
 * Draws one ROM font glyph as a textured quad at x, y (in 1/16 pixel),
 * taking its size from the font's cell width and its top and bottom from the ascent and descent.
 */
static void DrawFontChar(int x, int y, int z, int xChar, int yChar) {
    s16 posLeft = x;
    s16 posRight = posLeft + FontSize;
    s16 posTop = y - (FontData->ascent * FontSize / FontData->cellWidth);
    s16 posBottom = y + (FontData->descent * FontSize / FontData->cellWidth);

    s16 texLeft = xChar;
    s16 texRight = (xChar + FontData->cellWidth);
    s16 texTop = yChar;
    s16 texBottom = (yChar + FontData->cellHeight);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(posLeft, posTop, z);
    GXTexCoord2s16(texLeft, texTop);
    GXPosition3s16(posRight, posTop, z);
    GXTexCoord2s16(texRight, texTop);
    GXPosition3s16(posRight, posBottom, z);
    GXTexCoord2s16(texRight, texBottom);
    GXPosition3s16(posLeft, posBottom, z);
    GXTexCoord2s16(texLeft, texBottom);
    GXEnd();
}

/** Loads the ROM font texture sheet into a texture map, skipping the load if it is the same sheet as last time. */
static void LoadSheet(void* image, GXTexMapID texMapID) {
    Mtx mtx;
    GXTexObj texObj;

    if (LastSheet != image) {
        LastSheet = image;
        GXInitTexObj(&texObj, image, FontData->sheetWidth, FontData->sheetHeight, FontData->sheetFormat, 0, 0, 0);
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, texMapID);
        MTXScale(mtx, 1.0f / FontData->sheetWidth, 1.0f / FontData->sheetHeight, 1.0f);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
    }
}

/**
 * Draws a string with the ROM font at x, y, z: handles newline (moves down one line) and tab,
 * loads the right sheet for each character and advances by the character width.
 * Returns the width in pixels of the last line.
 */
int DEMORFPuts(s16 x, s16 y, s16 z, char* string) {
    s32 cx;
    void* image;
    s32 xChar;
    s32 yChar;
    s32 width;

    ASSERTLINE(583, FontData);
    LastSheet = NULL;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);

    x *= 16;
    y *= 16;
    z *= 16;

    width = 0;
    while (*string != 0) {
        if (*string == '\n') {
            width = 0;
            y += FontData->leading * FontSize / FontData->cellWidth;
            string++;
        } else if (*string == '\t') {
            width += 8 * (FontSize + FontSpace);
            width -= width % (8 * (FontSize + FontSpace));
            string++;
        } else {
            string = OSGetFontTexture(string, &image, &xChar, &yChar, &cx);
            LoadSheet(image, GX_TEXMAP0);
            DrawFontChar(x + width, y, z, xChar, yChar);
            width = FontSpace + ((FontSize * cx) / FontData->cellWidth) + width;
        }
    }

    return (width + 15) / 16;
}

/**
 * Like DEMORFPuts but draws at most 'length' bytes and wraps to a new line
 * when a character would pass 'maxWidth' pixels. Returns the width of the last line.
 */
int DEMORFPutsEx(s16 x, s16 y, s16 z, char* string, s16 maxWidth, int length) {
    s32 cx;
    void* image;
    s32 xChar;
    s32 yChar;
    s32 width;
    char* end;

    ASSERTLINE(636, FontData);
    LastSheet = NULL;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);

    x *= 16;
    y *= 16;
    z *= 16;
    maxWidth *= 16;

    end = (char*)&string[length];
    width = 0;
    while (*string && string < end) {
        if (*string == '\n') {
            width = 0;
            y += FontData->leading * FontSize / FontData->cellWidth;
            string++;
        } else {
            string = OSGetFontTexture(string, &image, &xChar, &yChar, &cx);
            if (maxWidth < width + (FontSize * cx / FontData->cellWidth) + FontSpace) {
                width = 0;
                y += FontData->leading * FontSize / FontData->cellWidth;
            }
            LoadSheet(image, GX_TEXMAP0);
            DrawFontChar(x + width, y, z, xChar, yChar);
            width = FontSpace + (FontSize * cx / FontData->cellWidth) + width;
        }
    }

    return (width + 15) / 16;
}

/** printf front end to DEMORFPuts (256-byte buffer). */
int DEMORFPrintf(s16 x, s16 y, s16 z, char* fmt, ...) {
    va_list vlist;
    char buf[256];

    va_start(vlist, fmt);
    vsprintf(buf, fmt, vlist);
    return DEMORFPuts(x, y, z, buf);
}

/**
 * Debug helper: loads the ROM font data, converts the glyph for the first character of the string to texels
 * and prints it as hex through OSReport together with its width, then reinitialises the font.
 * Returns the string advanced by that character.
 */
char* DEMODumpROMFont(char* string) {
    u32 image[288];
    void* temp;
    int i;
    int j;
    s32 width;

    ASSERTLINE(724, FontData);

    switch (OSGetFontEncode()) {
    case OS_FONT_ENCODE_SJIS:
        temp = (u8*)FontData + OS_FONT_SIZE_SJIS - OS_FONT_ROM_SIZE_SJIS;
        break;
    case OS_FONT_ENCODE_ANSI:
        temp = (u8*)FontData + OS_FONT_SIZE_ANSI - OS_FONT_ROM_SIZE_ANSI;
        break;
    default:
        temp = (u8*)FontData + 0xF4020;
        break;
    }

    temp = (void*)OSRoundDown32B(temp);
    OSLoadFont(FontData, temp);

    memset(image, 0, sizeof(image));
    string = OSGetFontTexel(string, &image[0], 0, 0xC, &width);
    for (i = 0; i < 0x30; i++) {
        j = (i % 8) + ((i / 8) * 0x30);
        OSReport("%08x%08x%08x%08x%08x%08x\n", image[j], image[j+8], image[j+0x10], image[j+0x18], image[j+0x20], image[j+0x28]);
    }

    OSReport("\nwidth %d\n", width);
    OSInitFont(FontData);
    return string;
}

/** Returns the width in pixels of the widest line of a string in the ROM font. */
int DEMOGetRFTextWidth(char* string) {
    s32 cx;
    s32 width;
    s32 maxWidth;

    ASSERTLINE(779, FontData);
    maxWidth = width = 0;

    while (*string != 0) {
        if (*string == '\n') {
            if (maxWidth < width) {
                maxWidth = width;
            }

            width = 0;
        }

        string = OSGetFontWidth(string, &cx);
        width = FontSpace + ((FontSize * cx) / FontData->cellWidth) + width;
    }

    if (maxWidth < width) {
        maxWidth = width;
    }

    return (maxWidth + 15) / 16;
}

/** Returns the height in pixels of a string (its number of lines times the font's line spacing). */
int DEMOGetRFTextHeight(char* string) {
    s32 height;

    ASSERTLINE(815, FontData);

    height = 1;
    while (*string) {
        if (*string == '\n') {
            height++;
        }
        string++;
    }

    height *= FontData->leading * FontSize / FontData->cellWidth;
    return (height + 15) / 16;
}
