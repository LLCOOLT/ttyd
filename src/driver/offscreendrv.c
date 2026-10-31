// Offscreen driver: named screen regions that are copied into textures each frame (for effects that
// draw the scene into a texture), one set for the field and one for battle.
#include "driver/offscreendrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "sdk/DEMOInit.h"
#include "mario/mariost.h"
#include "memory.h"
#include <string.h>

//.sbss
static OffscreenWork work[2]; // field, battle

/** Returns the battle (inBattle) or field set of offscreen entries. */
static inline OffscreenWork* offscreenGetWork(BOOL inBattle) {
    return inBattle ? &work[1] : &work[0];
}

/** Returns the offscreen entry set for the current mode (battle or field, from gp->inBattle). */
static inline OffscreenWork* offscreenGetWorkGp(void) {
    return gp->inBattle ? &work[1] : &work[0];
}

// local prototypes
static void offscreenDisp(CameraId camId, void* param);

/** Allocates the 10-entry offscreen tables for the field and for battle; called once at boot. */
void offscreenInit(void) {
    OffscreenWork* wp;

    work[0].count = 10;
    work[0].entries = __memAlloc(HEAP_DEFAULT, work[0].count * sizeof(OffscreenEntry));
    memset(work[0].entries, 0, work[0].count * sizeof(OffscreenEntry));
    wp = &work[1];
    wp->count = 10;
    wp->entries = __memAlloc(HEAP_DEFAULT, wp->count * sizeof(OffscreenEntry));
    memset(wp->entries, 0, wp->count * sizeof(OffscreenEntry));
}

/** Frees every offscreen entry of the field or battle set; the map-change and battle sequences call it on entry. */
void offscreenReset(BOOL inBattle) {
    OffscreenWork* wp = offscreenGetWork(inBattle);
    memset(wp->entries, 0, wp->count * sizeof(OffscreenEntry));
}

/**
 * Registers a named offscreen region (reusing the slot if the name exists) with an empty bounding box
 * and returns its id. Map objects, NPCs, shadows and effects such as the cloud and scissor screens use it.
 */
s32 offscreenEntry(const char* name) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;

    // check if already created
    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->name, name)) {
            break;
        }
    }

    // find new slot
    for (i = 0, entry = wp->entries; i < count; i++, entry++) {
        if (!(entry->flags & 1))
            break;
    }

    entry->flags = 1;
    strcpy(entry->name, name);
    entry->currLeft = 1020;
    entry->currTop = 1020;
    entry->currRight = 2;
    entry->currBottom = 2;
    entry->prevLeft = 1020;
    entry->prevTop = 2;
    entry->prevRight = 2;
    entry->prevBottom = 2;
    entry->copyFmt = 5;
    entry->texFmt = 5;
    return i;
}

/**
 * Draw callback on the offscreen camera: copies each entry's bounding box from the frame buffer into a freshly
 * allocated texture so it can be drawn back later in the frame.
 */
static void offscreenDisp(CameraId camId, void* param) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;
    u16 width, height;

    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1 && entry->flags & 2) {
            width = entry->currRight - entry->currLeft;
            height = entry->currBottom - entry->currTop;
            GXSetTexCopySrc(entry->currLeft, entry->currTop, width, height);
            GXSetTexCopyDst(width, height, (GXTexFmt)entry->copyFmt, GX_FALSE);
            entry->texBuf = smartAlloc(GXGetTexBufferSize(width, height, (u32)entry->copyFmt, GX_FALSE, 0), 3);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXCopyTex(entry->texBuf->address, GX_TRUE);
            GXPixModeSync();
            GXInitTexObj(&entry->texObj, entry->texBuf->address, width, height, (GXTexFmt)entry->texFmt,
                         GX_CLAMP, GX_CLAMP, GX_FALSE);
            entry->flags |= 4;
        }
    }
}

/**
 * Per-frame update: keeps last frame's bounding boxes, empties the current ones for drawers to grow again,
 * and queues offscreenDisp.
 */
void offscreenMain(void) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;

    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1) {
            entry->flags &= ~2;
            entry->flags &= ~4;
            entry->prevLeft = entry->currLeft;
            entry->prevTop = entry->currTop;
            entry->prevRight = entry->currRight;
            entry->prevBottom = entry->currBottom;
            entry->currLeft = 1020;
            entry->currTop = 1020;
            entry->currRight = 2;
            entry->currBottom = 2;
        }
    }
    dispEntry(CAMERA_OFFSCREEN2, 0.0f, 7, offscreenDisp, NULL);
}

/**
 * Grows entry id's screen-space box (in pixels) to include the given rectangle,
 * padded by 2 and aligned to even pixels, clamped to the frame buffer;
 * marks the entry as having an area this frame.
 */
void offscreenAddBoundingBox(s32 id, u16 left, u16 top, u16 right, u16 bottom) {
    OffscreenEntry* entry;

    if (right > left) {
        entry = &offscreenGetWorkGp()->entries[id];
        if (entry->flags & 1) {
            if (left >= 2) {
                left -= 2;
            }
            if (top >= 2) {
                top -= 2;
            }
            if (right <= DEMOGetRenderModeObj()->fbWidth - 2) {
                right += 2;
            }
            if (bottom <= DEMOGetRenderModeObj()->efbHeight - 2) {
                bottom += 2;
            }
            left -= (left & 1);
            top -= (top & 1);
            right += (right & 1);
            bottom += (bottom & 1);
            if (left < entry->currLeft) {
                entry->currLeft = left;
                entry->flags |= 2;
            }
            if (top < entry->currTop) {
                entry->currTop = top;
                entry->flags |= 2;
            }
            if (right > entry->currRight) {
                entry->currRight = right;
                entry->flags |= 2;
            }
            if (bottom > entry->currBottom) {
                entry->currBottom = bottom;
                entry->flags |= 2;
            }
        }
    }
}

/** Fetches entry id's screen box for this frame; FALSE if the entry is unused or nothing was added to it. */
BOOL offscreenGetBoundingBox(s32 id, u16* left, u16* top, u16* right, u16* bottom) {
    OffscreenEntry* entry = &offscreenGetWorkGp()->entries[id];

    if (!(entry->flags & 1)) {
        return FALSE;
    }
    if (!(entry->flags & 2)) {
        return FALSE;
    }
    *left = entry->currLeft;
    *top = entry->currTop;
    *right = entry->currRight;
    *bottom = entry->currBottom;
    return TRUE;
}

/**
 * Hands out entry id's copied texture and its buffer,
 * or NULLs if the entry has no area or was not copied this frame.
 */
void offscreenGetTexObj(s32 id, GXTexObj** texObj, smartEntry** texBuf) {
    OffscreenEntry* entry = &offscreenGetWorkGp()->entries[id];

    if (!(entry->flags & 1)) {
        *texObj = NULL;
        *texBuf = NULL;
        return;
    }
    if (!(entry->flags & 2)) {
        *texObj = NULL;
        *texBuf = NULL;
        return;
    }
    if (!(entry->flags & 4)) {
        *texObj = NULL;
        *texBuf = NULL;
        return;
    }
    *texObj = &entry->texObj;
    *texBuf = entry->texBuf;
}

/** Returns the id of the entry with this name (the table size if none). */
s32 offscreenNameToId(const char* name) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;

    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->name, name)) {
            break;
        }
    }
    return i;
}

/** Returns the entry with this name (one past the table if none). */
OffscreenEntry* offscreenNameToPtr(const char* name) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;

    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->name, name)) {
            break;
        }
    }
    return entry;
}

/** Frees the entry with this name. */
void offscreenDelete(const char* name) {
    OffscreenWork* wp = offscreenGetWorkGp();
    int i, count;
    OffscreenEntry* entry;

    for (i = 0, count = wp->count, entry = wp->entries; i < count; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->name, name)) {
            break;
        }
    }
    entry->flags = 0;
}

/** Fetches entry id's screen box from the previous frame; FALSE if unused or the box was empty. */
BOOL offscreenGetBoundingBox_BeforeFrame(s32 id, u16* left, u16* top, u16* right, u16* bottom) {
    OffscreenEntry* entry = &offscreenGetWorkGp()->entries[id];

    if (!(entry->flags & 1)) {
        return FALSE;
    }
    if (entry->prevLeft > entry->prevRight) {
        return FALSE;
    }
    *left = entry->prevLeft;
    *top = entry->prevTop;
    *right = entry->prevRight;
    *bottom = entry->prevBottom;
    return TRUE;
}
