// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#pragma optimize_for_size on
#pragma dont_inline on
#include "battle/battle_menu_disp.h"
#include "battle/battle_seq_command.h"
#include "battle/battle_unit.h"
#include "system.h"
#include "battle/battle_database_common.h"
#include "data/item_data.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"

extern BattleWork* _battleWorkPointer;
void FontDrawString(f32 x, f32 y, const char* msg);
void FontDrawScale(f32 scale);
void FontDrawColorIDX(s32 idx);
extern ItemData itemDataTable[];
extern BattleWeapon ItemWeaponData_CookingItem;
s32 BtlUnit_GetWeaponCost(BattleUnit* unit, BattleWeapon* weapon);
extern int sprintf(char* str, const char* format, ...);
double sin(double);
double cos(double);
void btlGetScreenPoint(Vec* pos, Vec* out);
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color, s32 a);
void btlDispGXInit2D(void);

typedef struct BattleSubMenu {
    BattleCursor* cursor;           // 0x0
    BattleCommandAct* acts;         // 0x4
    BattleCommandWeapon* weapons;   // 0x8
    s32 field_C;                    // 0xC
    s32 field_10;                   // 0x10
    u8 field_14;                    // 0x14
    u8 pad15[3];                    // 0x15
    s32 field_18;                   // 0x18
    s32 field_1C;                   // 0x1C
    s32 field_20[5];                // 0x20
    s32 field_34[5];                // 0x34
    s32 field_48[15];               // 0x48
    s32 field_84[5];                // 0x84
    f32 field_98;                   // 0x98
    f32 field_9C;                   // 0x9C
    f32 field_A0;                   // 0xA0
    s32 field_A4[7];                // 0xA4
    s32 field_C0[7];                // 0xC0
    s32 field_DC[7];                // 0xDC
    s32 field_F8[7];                // 0xF8
    u8 field_114[8];
    s32 field_11C; // 0x11C
    f32 field_120; // 0x120
} BattleSubMenu;

#define WP_SUBMENU(wp) (*(BattleSubMenu**)&(wp)->commandMenu.field_55C)

void DrawMultiItemWin(void);
void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d);
void DrawMainIcon(BattleSubMenu* menu, BattleCommandAct* acts, void* a, void* b, void* c);
void DrawSubIcon(BattleSubMenu* menu, void* a, s32* enabled, s16* icons, const char** names, s32* costs, s32* p34, void* party, s32 y);
void DrawMenuCursorAndScrollArrow(Vec* v);
void DrawMenuHelpWin(const char* help, f32 x, f32 y);
void DrawChangePartyWin(void);
void DrawOperationWin(void);
void DrawWeaponWin(void);
void DrawMainMenu(BattleWork* wp);
void DrawMenuPinchMark(void);
#include "battle/battle_audience.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
void DrawSubIconSub(BattleSubMenu* menu, s32 i, Mtx m, s32 enabled, s32 icon, const char* name, s32 cost, s32 p34, void* party, s32 y);
void DrawMainIconCircle(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, Vec v, f32 s);
void DrawMainIconHukidasi(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, f32 s);
BOOL BattleCommandCheckChangePositionEnable(BattleWork* wp);
void DrawMenuPartyChangeButton_Sub(u32 id, f32 x, f32 y, f32 angle);
void DrawMenuPartyChangeButton(void);
void DrawSubMenuCommonProcessSub1(BattleSubMenu* menu, BattleCursor* cursor, s32 prev, s32 key);
void btlDispGXQuads2D(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a);
#include "mario/mariost.h"
#include "sdk/texPalette.h"
extern GlobalWork* gp;
void FontDrawStringCenterMtx(Mtx mtx, const char* msg);
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t);
void FontDrawColor(GXColor color);
void GetRingCenter(Vec* out);
void GetRingOffset(f32 angle, f32* x, f32* y);
f32 kakutable[3][5] = {{240.0f, 120.0f, 0.0f, 0.0f, 0.0f}, {270.0f, 180.0f, 90.0f, 0.0f, 0.0f}, {270.0f, 203.0f, 157.0f, 90.0f, 0.0f}};

//.sdata
GXColor seleItemCoordCol = {0xFF, 0xC0, 0xC0, 0xCF};

#ifdef NONMATCHING
void SelectedItemCoordinateColorUpDate(void) {
    static s8 seq;
    switch (seq) {
        case 0:
            if (++seleItemCoordCol.g == 0xFF) {
                seq = 1;
            }
            break;
        case 1:
            if (--seleItemCoordCol.r == 0xC0) {
                seq = 2;
            }
            break;
        case 2:
            if (++seleItemCoordCol.b == 0xFF) {
                seq = 3;
            }
            break;
        case 3:
            if (--seleItemCoordCol.g == 0xC0) {
                seq = 4;
            }
            break;
        case 4:
            if (++seleItemCoordCol.r == 0xFF) {
                seq = 5;
            }
            break;
        case 5:
            if (--seleItemCoordCol.b == 0xC0) {
                seq = 0;
            }
            break;
    }
}
#endif

#ifdef NONMATCHING
BOOL BattleMenuKeyOKInACT(BattleWork* wp) {
    if (!wp->commandMenu.unk540[0x18] && !WP_SUBMENU(wp)->field_14) {
        return FALSE;
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
void battleMenuDispInit(void) {
    BattleWork* wp = _battleWorkPointer;
    char path[256];

    sprintf(path, "%s/battle/common/battle_common.tpl\0", getMarioStDvdRoot());
    wp->menuTex = fileAlloc(path, 4);
}
#endif

#ifdef NONMATCHING
void battleMenuDispEnd(void) {
    fileFree(_battleWorkPointer->menuTex);
}
#endif

#ifdef NONMATCHING
void GetRingCenter(Vec* out) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, wp->activeUnitId);

    btlGetScreenPoint((Vec*)((u8*)unit + 0x3C), out);
    out->x += 22.5f;
    out->y += 105.0f;
    out->z = 0.0f;
    if (out->x <= -180.0f) {
        out->x = -180.0f;
    }
}
#endif

#ifdef NONMATCHING
void GetRingOffset(f32 angle, f32* x, f32* y) {
    f32 t = 4.712389f - angle;
    *x = 80.0f * (f32)cos(t);
    *y = 35.0f * (f32)sin(t);
}
#endif

#ifdef NONMATCHING
void DrawMainIcon(BattleSubMenu* menu, BattleCommandAct* acts, void* a, void* b, void* c) {
    s32 order[5];
    f32 z[6];
    BattleWork* wp = _battleWorkPointer;
    BattleCursor* cursor;
    f32 tf;
    s32 ti;
    s32 i;
    s32 j;
    s32 k;

    if (BattleGetUnitPtr(wp, wp->activeUnitId)->currentKind == 0xDE) {
        cursor = &wp->commandMenu.cursor[0];
    } else {
        cursor = &wp->commandMenu.cursor[1];
    }
    for (i = 0; i < cursor->unk8; i++) {
        order[i] = i;
        z[i] = ((Vec*)b)[i].y;
    }
    for (i = 0; i < cursor->unk8 - 1; i++) {
        for (j = i + 1; j < cursor->unk8; j++) {
            if (z[i] < z[j]) {
                tf = z[i];
                ti = order[i];
                z[i] = z[j];
                order[i] = order[j];
                z[j] = tf;
                order[j] = ti;
            }
        }
    }
    for (i = 0; i < cursor->unk8; i++) {
        k = order[i];
        if (menu->field_20[k] & 1) {
            if (menu->field_20[k] & 2) {
                DrawMainIconHukidasi(menu, &acts[k], ((Mtx*)a)[k], ((f32*)c)[k]);
            } else {
                DrawMainIconCircle(menu, &acts[k], ((Mtx*)a)[k], ((Vec*)b)[k], ((f32*)c)[k]);
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawMainIconHukidasi(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, f32 s) {
    GXColor tev;
    GXColor col;
    Mtx rot;
    Mtx scl;
    Mtx trn;
    Mtx out;
    GXTexObj texobj;
    BattleWork* wp = _battleWorkPointer;
    CameraEntry* cam;
    const char* name;
    u16 icon;
    f32 rad;
    f32 ofs;

    cam = camGetPtr(8);
    btlDispGXInit2D();
    tev = (GXColor){0xE1, 0xE1, 0xE1, 0xFF};
    GXSetTevColor(GX_TEVREG0, tev);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
    PSMTXTrans(trn, 0.0f, -5.0f, 0.0f);
    rad = 0.017453292f * s;
    PSMTXRotRad(rot, 'y', rad);
    PSMTXConcat(m, rot, out);
    PSMTXConcat(out, scl, out);
    PSMTXConcat(out, trn, out);
    PSMTXConcat(cam->view, out, out);
    GXLoadPosMtxImm(out, 0);
    TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, 1);
    GXLoadTexObj(&texobj, GX_TEXMAP0);
    if (s >= 0.0f && s <= 180.0f) {
        ofs = 4.0f - 8.0f * s / 180.0f;
    }
    if (s >= 180.0f && s <= 360.0f) {
        ofs = -4.0f + 8.0f * (s - 180.0f) / 180.0f;
    }
    if (menu->field_1C == 0) {
        btlDispGXQuads2D(64.0f + ofs, 76.0f, -64.0f + ofs, -4.0f, 0, 0, 0, 0x80);
        btlDispGXQuads2D(64.0f, 80.0f, -64.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        btlDispGXQuads2D(-64.0f + ofs, 76.0f, 64.0f + ofs, -4.0f, 0, 0, 0, 0x80);
        btlDispGXQuads2D(-64.0f, 80.0f, 64.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    PSMTXTrans(trn, -67.0f, 20.0f, 0.0f);
    PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
    PSMTXRotRad(rot, 'y', rad);
    PSMTXConcat(m, rot, out);
    PSMTXConcat(out, trn, out);
    PSMTXConcat(out, scl, out);
    icon = *(u16*)&act->icon;
    if (!icon) {
        icon = 0x18B;
    }
    if (act->enabled == 1) {
        ((void (*)(Mtx, s16, u16))iconDispGx2)(out, 0x10, icon);
    } else {
        ((void (*)(Mtx, s16, u16))iconDispGx2)(out, 0x30, icon);
    }
    name = act->name;
    PSMTXTrans(trn, 0.0f, 52.5f, 0.0f);
    PSMTXScale(scl, 0.9f, 0.9f, 0.9f);
    PSMTXRotRad(rot, 'y', rad);
    PSMTXConcat(m, rot, out);
    PSMTXConcat(out, trn, out);
    PSMTXConcat(out, scl, out);
    FontDrawStart();
    if (act->enabled == 1) {
        col = (GXColor){0x00, 0x00, 0x00, 0xFF};
    } else {
        col = (GXColor){0x80, 0x80, 0x80, 0xFF};
    }
    FontDrawColor(col);
    FontDrawStringCenterMtx(out, name);
}
#endif

#ifdef NONMATCHING
void DrawMainIconCircle(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, Vec v, f32 s) {
    GXColor tev;
    Mtx rot;
    Mtx scl;
    Mtx trn;
    Mtx out;
    GXTexObj texobj;
    BattleWork* wp = _battleWorkPointer;
    CameraEntry* cam;
    u8 c;
    u32 icon;
    f32 rad;
    f32 ofs;
    f32 sc;
    s32 i;
    s32 j;

    cam = camGetPtr(8);
    c = 0xC0 - (s32)(1.5f * v.z);
    btlDispGXInit2D();
    tev = (GXColor){0xE1, 0xE1, 0xE1, 0xFF};
    GXSetTevColor(GX_TEVREG0, tev);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    sc = 1.3f - 0.005f * v.z;
    PSMTXScale(scl, sc, sc, 1.0f);
    rad = 0.017453292f * s;
    PSMTXRotRad(rot, 'y', rad);
    PSMTXConcat(m, rot, out);
    PSMTXConcat(out, scl, out);
    PSMTXConcat(cam->view, out, out);
    GXLoadPosMtxImm(out, 0);
    TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, 0);
    GXLoadTexObj(&texobj, GX_TEXMAP0);
    if (s >= 0.0f && s <= 180.0f) {
        ofs = (4.0f - 8.0f * s / 180.0f) / 1.3f;
    }
    if (s >= 180.0f && s <= 360.0f) {
        ofs = (-4.0f + 8.0f * (s - 180.0f) / 180.0f) / 1.3f;
    }
    {
    f32 pos[4][8] = {{-20.0f, 40.0f, 0.0f, 40.0f, 0.0f, 20.0f, -20.0f, 20.0f}, {20.0f, 40.0f, 20.0f, 20.0f, 0.0f, 20.0f, 0.0f, 40.0f}, {-20.0f, 20.0f, 0.0f, 20.0f, 0.0f, 0.0f, -20.0f, 0.0f}, {0.0f, 20.0f, 20.0f, 20.0f, 20.0f, 0.0f, 0.0f, 0.0f}};
    f32 uv[4][8] = {{0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f}};
    for (i = 0; i < 4; i++) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (j = 0; j < 7; j += 2) {
            btlDispGXPoint2D(ofs + pos[i][j], -4.0f / 1.3f + pos[i][j + 1], 0, 0, 0, 0x80, uv[i][j], uv[i][j + 1]);
        }
    }
    for (i = 0; i < 4; i++) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        for (j = 0; j < 7; j += 2) {
            btlDispGXPoint2D(pos[i][j], pos[i][j + 1], c, c, c, 0xFF, uv[i][j], uv[i][j + 1]);
        }
    }
    }
    PSMTXTrans(trn, 0.0f, 7.5f, 0.0f);
    sc = 0.66f * (1.3f - 0.005f * v.z);
    PSMTXScale(scl, sc, sc, 1.0f);
    PSMTXRotRad(rot, 'y', rad);
    PSMTXIdentity(rot);
    PSMTXConcat(m, rot, out);
    PSMTXConcat(out, scl, out);
    PSMTXConcat(out, trn, out);
    icon = *(u16*)&act->icon;
    if (!icon) {
        icon = 0x18B;
    }
    if (act->enabled == 1) {
        iconDispGxCol(out, 0x10, icon, (GXColor){c, c, c, 0xFF});




    } else {
        iconDispGxCol(out, 0x30, icon, (GXColor){c, c, c, 0xFF});




    }
}
#endif

#ifdef NONMATCHING
void DrawSubIcon(BattleSubMenu* menu, void* a, s32* enabled, s16* icons, const char** names, s32* costs, s32* p34, void* party, s32 y) {
    Mtx out[7];
    Mtx m;
    BattleWork* wp = _battleWorkPointer;
    BattleCursor* cursor;
    f32 ofs;
    s32 i;

    BattleGetUnitPtr(wp, wp->activeUnitId);
    cursor = menu->cursor;
    ofs = menu->field_98 - (f32)(s32)menu->field_98; ofs = 24.0f * ofs;
    for (i = 0; i < 7; i++) {
        if ((s32)menu->field_98 + i < cursor->unk8 && (menu->field_A4[i] & 1)) {
            PSMTXTrans(m, 100.0f, 35.0f - 24.0f * i + ofs, 0.0f);
            PSMTXConcat(m, ((Mtx*)a)[i], out[i]);
            DrawSubIconSub(menu, i, out[i], enabled[i], ((u16*)icons)[i], names[i], costs[i], p34[i], party, y);
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawSubIconSub(BattleSubMenu* menu, s32 i, Mtx m, s32 enabled, s32 icon, const char* name, s32 cost, s32 p34, void* party, s32 y) {
    BattleWork* wp = _battleWorkPointer;
    CameraEntry* cam;
    BattleCursor* cursor = menu->cursor;
    f32 frac;
    u8 alpha;
    u8 r; u8 g; u8 b; u8 a;
    Mtx scl;
    Mtx trn;
    Mtx out;
    GXTexObj texobj;
    s32 d1[3];
    s32 o1[3];
    s32 d2[3];
    s32 o2[3];
    s32 d3[3];
    s32 o3[3];
    char buf1[2];
    char buf2[2];
    char buf3[2];
    s32 j;
    s32 n;

    cam = camGetPtr(8);
    frac = menu->field_98 - (( s32)menu->field_98) ;
    alpha = 0xFF;
    if (i == 0) {
        alpha = 255.0f * (1.0f - frac);
    }
    if (i == 6) {
        alpha = 255.0f * frac;
    }
    j = ((s32)menu->field_98 ) + i ; if (j == cursor->field_0) {
        r = seleItemCoordCol.r;
        g = seleItemCoordCol.g;
        b = seleItemCoordCol.b;
        a = alpha;
    } else {
        b = 0xFF;
        g = 0xFF;
        r = 0xFF;
        a = ( 144.0f * ( (u8)alpha )) / 255.0f;
    }
    btlDispGXInit2D();
    PSMTXConcat(cam->view, m, out);
    GXLoadPosMtxImm(out, 0);
    TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, 2);
    GXLoadTexObj(&texobj, GX_TEXMAP0);
    btlDispGXQuads2D(-152.0f, 24.0f, -136.0f, 0.0f, r, g, b, a);
    btlDispGXQuads2D(152.0f, 24.0f, 136.0f, 0.0f, r, g, b, a);
    TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, 3);
    GXLoadTexObj(&texobj, GX_TEXMAP0);
    btlDispGXQuads2D(-136.0f, 24.0f, 136.0f, 0.0f, r, g, b, a);
    PSMTXTrans(trn, -119.0f, 2.0f, 0.0f);
    PSMTXScale(scl, 0.5f, 0.5f, 1.0f);
    PSMTXConcat(m, trn, out);
    PSMTXConcat(out, scl, out);
    if (!(( u16)icon) ) {
        icon = 0x18B;
    }
    if (enabled == 1) {
        iconDispGxCol(out, 0x10, icon, (GXColor){0xFF, 0xFF, 0xFF, alpha});
    } else {
        iconDispGxCol(out, 0x30, icon, (GXColor){0xFF, 0xFF, 0xFF, alpha});
    }
    FontDrawStart();
    {
        GXColor fc;
        if (enabled == 1) {
            fc = (GXColor){0x00, 0x00, 0x00, alpha};
        } else {
            fc = (GXColor){0x40, 0x40, 0x40, alpha};
        }
        FontDrawColor(fc);
    }
    PSMTXTrans(trn, -104.0f, 22.0f, 0.0f);
    if (y == 1) {
        PSMTXScale(scl, ( FontGetMessageWidth(name) > 150 ) ? ( 120.0f / FontGetMessageWidth(name) ) : ( 0.8f) , 0.8f, 0.8f);
    } else {
        PSMTXScale(scl, 0.8f, 0.8f, 0.8f);
    }
    PSMTXConcat(m, trn, out);
    PSMTXConcat(out, scl, out);
    FontDrawStringMtx(out, name);
    if (cost != 0) {
        d1[2] = cost / 100;
        d1[1] = (cost - ( d1[2] * 100) ) / 10;
        d1[0] = (cost - ( d1[2] * 100) ) - ( d1[1] * 10) ;
        if (d1[2] > 0) {
            o1[0] = 28; o1[1] = 14; o1[2] = 0; n = 3;
        } else if (d1[1] > 0) {
            o1[0] = 21; o1[1] = 7; o1[2] = 0; n = 2;
        } else {
            o1[0] = 14; o1[1] = 0; o1[2] = 0; n = 1;
        }
        PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
        for (j = 0; j < n; j++) {
            buf1[0] = d1[j] + '0';
            buf1[1] = 0;
            PSMTXTrans(trn, 4.0f + (72.0f + o1[j]), 25.0f, 0.0f);
            PSMTXConcat(m, trn, out);
            PSMTXConcat(out, scl, out);
            FontDrawStringMtx(out, buf1);
        }
        PSMTXTrans(trn, 120.0f, 22.0f, 0.0f);
        PSMTXScale(scl, 0.8f, 0.8f, 0.8f);
        PSMTXConcat(m, trn, out);
        PSMTXConcat(out, scl, out);
        FontDrawStringMtx(out, msgSearch("btl_cost_disp_FP"));
    }
    if (p34 != 0) {
        d2[2] = p34 / 100;
        d2[1] = (p34 - ( d2[2] * 100) ) / 10;
        d2[0] = (p34 - ( d2[2] * 100) ) - ( d2[1] * 10) ;
        if (d2[2] > 0) {
            o2[0] = 28; o2[1] = 14; o2[2] = 0; n = 3;
        } else if (d2[1] > 0) {
            o2[0] = 21; o2[1] = 7; o2[2] = 0; n = 2;
        } else {
            o2[0] = 14; o2[1] = 0; o2[2] = 0; n = 1;
        }
        PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
        for (j = 0; j < n; j++) {
            buf2[0] = d2[j] + '0';
            buf2[1] = 0;
            PSMTXTrans(trn, 4.0f + (72.0f + o2[j]), 25.0f, 0.0f);
            PSMTXConcat(m, trn, out);
            PSMTXConcat(out, scl, out);
            FontDrawStringMtx(out, buf2);
        }
        PSMTXTrans(trn, 120.0f, 22.0f, 0.0f);
        PSMTXScale(scl, 0.8f, 0.8f, 0.8f);
        PSMTXConcat(m, trn, out);
        PSMTXConcat(out, scl, out);
        FontDrawStringMtx(out, msgSearch("btl_cost_disp_AP"));
    }
    if (party != NULL) {
        s16* p = (s16*)((( u8*)party ) + ( (i + ( (s32)menu->field_98) ) * 0x18) );
        s32 n;
        s32 hp; s32 maxhp;
        hp = p[10];
        maxhp = p[11];
        PSMTXTrans(trn, 30.0f, 22.0f, 0.0f);
        PSMTXScale(scl, 0.8f, 0.8f, 0.8f);
        PSMTXConcat(m, trn, out);
        PSMTXConcat(out, scl, out);
        FontDrawStringMtx(out, msgSearch("btl_disp_HP"));
        d3[2] = hp / 100;
        d3[1] = (hp - ( d3[2] * 100) ) / 10;
        d3[0] = (hp - ( d3[2] * 100) ) - ( d3[1] * 10) ;
        if (d3[2] > 0) {
            o3[0] = 28; o3[1] = 14; o3[2] = 0; n = 3;
        } else if (d3[1] > 0) {
            o3[0] = 21; o3[1] = 7; o3[2] = 0; n = 2;
        } else {
            o3[0] = 14; o3[1] = 0; o3[2] = 0; n = 1;
        }
        PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
        for (j = 0; j < n; j++) {
            buf3[0] = d3[j] + '0';
            buf3[1] = 0;
            if ((( u32)gp->language ) == 0) {
                PSMTXTrans(trn, 26.0f + (30.0f + o3[j]), 25.0f, 0.0f);
            } else {
                PSMTXTrans(trn, 28.0f + (30.0f + o3[j]), 25.0f, 0.0f);
            }
            PSMTXConcat(m, trn, out);
            PSMTXConcat(out, scl, out);
            FontDrawStringMtx(out, buf3);
        }
        if ((( u32)gp->language ) == 0) {
            PSMTXTrans(trn, 92.0f, 22.0f, 0.0f);
        } else {
            PSMTXTrans(trn, 100.0f, 22.0f, 0.0f);
        }
        PSMTXScale(scl, 0.8f, 0.8f, 0.8f);
        PSMTXConcat(m, trn, out);
        PSMTXConcat(out, scl, out);
        FontDrawStringMtx(out, msgSearch("btl_disp_slash"));
        d3[2] = maxhp / 100;
        d3[1] = (maxhp - ( d3[2] * 100) ) / 10;
        d3[0] = (maxhp - ( d3[2] * 100) ) - ( d3[1] * 10) ;
        if (d3[2] > 0) {
            o3[0] = 28; o3[1] = 14; o3[2] = 0; n = 3;
        } else if (d3[1] > 0) {
            o3[0] = 21; o3[1] = 7; o3[2] = 0; n = 2;
        } else {
            o3[0] = 14; o3[1] = 0; o3[2] = 0; n = 1;
        }
        PSMTXScale(scl, 1.0f, 1.0f, 1.0f);
        for (j = 0; j < n; j++) {
            buf3[0] = d3[j] + '0';
            buf3[1] = 0;
            if ((( u32)gp->language ) == 0) {
                PSMTXTrans(trn, 76.0f + (30.0f + o3[j]), 25.0f, 0.0f);
            } else {
                PSMTXTrans(trn, 78.0f + (30.0f + o3[j]), 25.0f, 0.0f);
            }
            PSMTXConcat(m, trn, out);
            PSMTXConcat(out, scl, out);
            FontDrawStringMtx(out, buf3);
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawMenuPartyChangeButton(void) {
    Vec p;
    Vec q;
    s32 id;
    f32 ix;
    f32 iy;
    f32 iz;
    BattleUnit* party;
    BattleUnit* mario;
    BattleWork* wp;
    BattleSubMenu* menu;
    f32 x;
    f32 y;

    wp = _battleWorkPointer;
    menu = WP_SUBMENU(wp);
    camGetPtr(8);
    mario = BattleGetMarioPtr(wp);
    party = BattleGetPartyPtr(wp);
    if (!party) {
        BattleAudience_GetItemOn(&id, &ix, &iy, &iz, NULL);
        if (id != -1) {
            if (menu->field_120 > 0.0f) {
                menu->field_120 -= 5.0f;
            } else {
                menu->field_120 = 0.0f;
            }
            btlGetScreenPoint((Vec*)((u8*)mario + 0x3C), &p);
            DrawMenuPartyChangeButton_Sub(5, p.x, p.y - 20.0f, menu->field_120);
        } else {
            menu->field_120 = 90.0f;
        }
    } else {
        btlGetScreenPoint((Vec*)((u8*)mario + 0x3C), &p);
        btlGetScreenPoint((Vec*)((u8*)party + 0x3C), &q);
        x = (p.x + q.x) / 2.0f;
        y = p.y;
        BattleAudience_GetItemOn(&id, &ix, &iy, &iz, NULL);
        if (id != -1) {
            if (menu->field_120 == 90.0f) {
                psndSFXOn("SFX_BTL_SYS_CAUTION_THROW1");
            }
            if (menu->field_120 > 0.0f) {
                menu->field_120 -= 5.0f;
            } else {
                menu->field_120 = 0.0f;
            }
            DrawMenuPartyChangeButton_Sub(5, x, y - 20.0f, menu->field_120);
        } else {
            menu->field_120 = 90.0f;
            if (BattleCommandCheckChangePositionEnable(wp)) {
                DrawMenuPartyChangeButton_Sub(4, x, y - 20.0f, 0.0f);
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawMenuPartyChangeButton_Sub(u32 id, f32 x, f32 y, f32 angle) {
    Mtx mtx;

    PSMTXRotRad(mtx, 'y', 0.017453292f * angle);
    PSMTXTransApply(mtx, mtx, x, y, 0.0f);
    btlDispTexPlane2(mtx, id, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, 0);
}
#endif

#ifdef NONMATCHING
void DrawMenuPinchMark(void) {
    Mtx m;
    Mtx out;
    GXTexObj texobj;
    Vec p;
    Vec q;
    BattleWork* wp = _battleWorkPointer;
    CameraEntry* cam;
    BattleUnit* unit;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u32 id;

    cam = camGetPtr(8);
    btlDispGXInit2D();
    unit = BattleGetMarioPtr(wp);
    if (unit->currentHp > 0 && unit->currentHp < unit->maxHp && unit->currentHp <= 5) {
        if (unit->currentHp == 1) {
            id = (gp->language ? 0 : -1) + 9;
            if (gp->retraceCount % 50 <= 24) {
                r = 0xFF;
                g = 0xE9;
                b = 0x40;
                a = 0xFF;
            } else {
                r = 0xE9;
                g = 0x52;
                b = 0x2F;
                a = 0xFF;
            }
        } else {
            id = gp->language == 0 ? 6 : 7;
            r = 0xFF;
            g = 0xE9;
            b = 0x40;
            a = 0xFF;
        }
        TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, id);
        GXLoadTexObj(&texobj, GX_TEXMAP0);
        btlGetScreenPoint((Vec*)((u8*)unit + 0x3C), &p);
        PSMTXTrans(m, p.x - 20.0f, 60.0f + p.y, 0.0f);
        PSMTXConcat(cam->view, m, out);
        GXLoadPosMtxImm(out, 0);
        btlDispGXQuads2D(-28.0f, 12.0f, 28.0f, -12.0f, r, g, b, a);
    }
    unit = BattleGetPartyPtr(wp);
    if (unit && unit->currentHp > 0 && unit->currentHp < unit->maxHp && unit->currentHp <= 5) {
        if (unit->currentHp == 1) {
            id = (gp->language ? 0 : -1) + 9;
            if (gp->retraceCount % 50 <= 24) {
                r = 0xFF;
                g = 0xE9;
                b = 0x40;
                a = 0xFF;
            } else {
                r = 0xE9;
                g = 0x52;
                b = 0x2F;
                a = 0xFF;
            }
        } else {
            r = 0xFF;
            g = 0xE9;
            b = 0x40;
            a = 0xFF;
            id = (gp->language ? 0 : -1) + 7;
        }
        TEXGetGXTexObjFromPalette(*wp->menuTex->data, &texobj, id);
        GXLoadTexObj(&texobj, GX_TEXMAP0);
        btlGetScreenPoint((Vec*)((u8*)unit + 0x3C), &q);
        PSMTXTrans(m, q.x - 20.0f, 60.0f + q.y, 0.0f);
        PSMTXConcat(cam->view, m, out);
        GXLoadPosMtxImm(out, 0);
        btlDispGXQuads2D(-28.0f, 12.0f, 28.0f, -12.0f, r, g, b, a);
    }
}
#endif

#ifdef NONMATCHING
void DrawMenuHelpWin(const char* msg, f32 x, f32 y) {
    f32 tx;
    s8 lines[4][0x30];
    s32 line;
    const s8* p;
    s8* dst;
    s32 i;

    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xCF}, x, y, 400.0f, 50.0f, 10.0f);
    FontDrawStart();
    FontDrawColorIDX(0);
    FontDrawScale(0.8f);
    msg = msgSearch(msg);
    if (msg) {
        for (i = 0; i < 4; i++) {
            lines[i][0] = 0;
        }
        p = (const s8*)msg;
        line = 0;
        dst = lines[0];
        while (1) {
            if (*p == '<') {
                while (*++p != '>') {
                }
                p++;
            }
            if (*p == 0) {
                *dst = 0;
                break;
            }
            if (*p == '\n') {
                *dst = 0;
                dst = lines[++line];
                p++;
                continue;
            }
            *dst = *p;
            p++;
            dst++;
        }
        if (lines[0][0]) {
            FontDrawScale(0.8f);
        }
        tx = 20.0f + x;
        FontDrawString(tx, y - 4.0f, (char*)lines[0]);
        if (lines[1][0]) {
            FontDrawScale(0.8f);
        }
        FontDrawString(tx, y - 28.0f, (char*)lines[1]);
        if (lines[2][0]) {
            FontDrawScale(0.8f);
        }
        FontDrawString(tx, y - 52.0f, (char*)lines[2]);
    } else {
        FontDrawString(10.0f + x, y - 4.0f, "\202\271\202\302\202\337\202\242\202\315\201@\202\310\202\242\202\314\202\276\201I\201I");
    }
}
#endif

#ifdef NONMATCHING
void DrawMenuCursorAndScrollArrow(Vec* v) {
    Vec pos;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    f32 bob;
    s32 n;
    f32 ax = 155.0f;
    f32 ay = 15.0f;

    bob = intplGetValue(4, menu->field_11C, 6, 0.0f, 10.0f);
    menu->field_11C++;
    if (menu->field_11C >= 12) {
        menu->field_11C = 0;
    }
    if (cursor->field_4 > 0) {
        pos.y = ay + v->y;
        pos.z = 0.0f;
        {
            f32 py = pos.y + bob;
            pos.x = ax + v->x;
            pos.y = py;
        }

        iconDispGx(&pos, 0x10, 0x1B5, 0.75f);
    }
    if (cursor->field_4 < cursor->unk8 - 6) {
        f32 x = 155.0f + v->x;
        pos.y = 20.0f + v->y - 164.0f - bob;
        pos.x = x;
        pos.z = 0.0f;
        iconDispGx(&pos, 0x10, 0x1B6, 0.75f);
    }
    n = cursor->field_0 - cursor->field_4;
    if (n < 0) {
        n = 0;
    }
    if (n >= 6) {
        n = 5;
    }
    {
        f32 y = v->y - (f32)n * 24.0f;
        pos.x = v->x;
        pos.z = 0.0f;
        pos.y = y;
    }
    iconDispGx(&pos, 0x14, 0x1F0, 1.0f);
}
#endif

#ifdef NONMATCHING
void InitSubMenuCommonProcess(BattleSubMenu** out, BattleCursor** mainCursor, BattleCursor* cursor) {
    BattleWork* wp = _battleWorkPointer;
    s32 i;

    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
    }
    WP_SUBMENU(wp) = BattleAlloc(sizeof(BattleSubMenu));
    *out = WP_SUBMENU(wp);
    (*out)->cursor = cursor;
    (*out)->field_C = 0;
    (*out)->field_10 = 0;
    (*out)->field_14 = 0;
    (*out)->field_18 = cursor->field_0;
    if (BattleGetUnitPtr(wp, wp->activeUnitId)->currentKind == 0xDE) {
        *mainCursor = &wp->commandMenu.cursor[0];
    } else {
        *mainCursor = &wp->commandMenu.cursor[1];
    }
    (*out)->field_98 = 0.0f;
    for (i = 0; i < 7; i++) {
        (*out)->field_A4[i] = 0;
        (*out)->field_C0[i] = 1;
        (*out)->field_DC[i] = -i;
        (*out)->field_F8[i] = 0;
    }
}
#endif

#ifdef NONMATCHING
void InitSubMenuCommonProcess2(BattleSubMenu* menu, BattleCursor* cursor) {
    s32 i;
    s32 idx = cursor->field_0;

    for (i = 0; i < cursor->unk8; i++) {
        if (++idx >= cursor->unk8) {
            idx = 0;
        }
        menu->field_48[idx] = 0;
        menu->field_84[idx] = i;
        menu->field_20[idx] = 0;
        menu->field_20[idx] |= 1;
        if (i == cursor->unk8 - 1) {
            menu->field_34[idx] = 0;
        } else {
            menu->field_34[idx] = 10;
        }
    }
}
#endif

#ifdef NONMATCHING
void InitSubMenuCommonProcess3(BattleSubMenu* menu, BattleCursor* cursor) {
    s32 i;
    s32 idx = cursor->field_0;

    for (i = 0; i < cursor->unk8; i++) {
        if (++idx >= cursor->unk8) {
            idx = 0;
        }
        menu->field_48[idx] = 0;
        menu->field_84[idx] = i;
        menu->field_20[idx] = 0;
        menu->field_20[idx] |= 1;
        if (i == cursor->unk8 - 1) {
            menu->field_34[idx] = 1;
        } else {
            menu->field_34[idx] = 11;
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawSubMenuCommonProcessSub1(BattleSubMenu* menu, BattleCursor* cursor, s32 prev, s32 key) {
    s32 i;

    if (key == 6 && cursor->unk8 > 6 && prev == cursor->unk8 - 6 && cursor->field_4 == 0 && cursor->field_0 != 1) {
        menu->field_C = 30;
        menu->field_10 = 0;
        menu->field_9C = cursor->unk8 - 6;
        menu->field_A0 = 0.0f;
        for (i = 0; i < 7; i++) {
            menu->field_C0[i] = 30;
            menu->field_DC[i] = 0;
        }
    } else if (key == 6 && cursor->unk8 > 6 && prev == 0 && cursor->field_4 == cursor->unk8 - 6 && cursor->field_0 != 5) {
        menu->field_C = 40;
        menu->field_10 = 0;
        menu->field_9C = 0.0f;
        menu->field_A0 = cursor->unk8 - 6;
        for (i = 0; i < 7; i++) {
            menu->field_C0[i] = 40;
            menu->field_DC[i] = 0;
        }
    } else if (cursor->field_4 == prev + 1) {
        menu->field_C = 10;
        menu->field_10 = 0;
        menu->field_9C = prev;
        menu->field_A0 = prev + 1;
        for (i = 0; i < 7; i++) {
            menu->field_C0[i] = 10;
            menu->field_DC[i] = 0;
        }
    } else if (cursor->field_4 == prev - 1) {
        menu->field_C = 20;
        menu->field_10 = 0;
        menu->field_9C = prev;
        menu->field_A0 = prev - 1;
        for (i = 0; i < 7; i++) {
            menu->field_C0[i] = 20;
            menu->field_DC[i] = 0;
        }
    }
}
#endif

#ifdef NONMATCHING
void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d) {
    Mtx tm;
    Mtx sm;
    f32 ox;
    f32 oy;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    BattleCursor* mainCursor;
    s32 steps;
    s32 prev;
    s32 n;
    s32 cnt;
    s32 cnt2;
    s32 i;
    f32 ang;
    f32 s;
    s32 sw;
    s32 nn;

    if (BattleGetUnitPtr(wp, wp->activeUnitId)->currentKind == 0xDE) {
        mainCursor = &wp->commandMenu.cursor[0];
    } else {
        mainCursor = &wp->commandMenu.cursor[1];
    }
    n = 6;
    if (cursor->unk8 < 6) {
        n = cursor->unk8;
    }
    prev = cursor->field_4;
    if (cursor->field_0 <= prev) {
        cursor->field_4 = cursor->field_0 - 1;
    } else if (cursor->field_0 >= cursor->field_4 + n - 1) {
        cursor->field_4 = cursor->field_0 - n + 2;
    }
    if (cursor->field_4 < 0) {
        cursor->field_4 = 0;
    }
    if (cursor->field_4 >= cursor->unk8 - n) {
        cursor->field_4 = cursor->unk8 - n;
    }
    *x = -200.0f;
    *y = -100.0f;
    switch (sw = menu->field_C) {
        case 0:
            menu->field_14 = 1;
            menu->field_98 = cursor->field_4;
            cnt = 0;
            for (i = 0; i < mainCursor->unk8; i++) {
                if (menu->field_34[i] == 1 || menu->field_34[i] == 11) {
                    cnt++;
                }
            }
            cnt2 = 0;
            for (i = 0; i < 7; i++) {
                if (menu->field_C0[i] == 2) {
                    cnt2++;
                }
            }
            if (cnt == mainCursor->unk8 && cnt2 == 7) {
                menu->field_C = 2;
            }
            DrawSubMenuCommonProcessSub1(menu, cursor, prev, n);
            break;
        case 2:
            menu->field_14 = 1;
            menu->field_98 = cursor->field_4;
            DrawSubMenuCommonProcessSub1(menu, cursor, prev, n);
            break;
        case 10:
        case 20:
        case 30:
        case 40:
            if (sw == 10 || sw == 20) {
                menu->field_14 = 1;
            }
            cnt = 0;
            for (i = 0; i < 7; i++) {
                if (menu->field_C0[i] == 2) {
                    cnt++;
                }
            }
            if (cnt == 7) {
                menu->field_C = 2;
                menu->field_98 = cursor->field_4;
            }
            DrawSubMenuCommonProcessSub1(menu, cursor, prev, n);
            break;
    }
    menu->field_1C = 0;
    for (i = 0; i < mainCursor->unk8; i++) {
        switch (menu->field_34[i]) {
            case 0:
                menu->field_20[i] |= 1;
                menu->field_20[i] |= 2;
                GetRingCenter(&((Vec*)b)[i]);
                {
                    f32 px = ((Vec*)b)[i].x;
                    f32 py;
                    ((Vec*)b)[i].x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(4, px, -60.0f, menu->field_48[i], 12);
                    py = ((Vec*)b)[i].y;
                    ((Vec*)b)[i].y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(4, py, 55.0f, menu->field_48[i], 12);
                }
                PSMTXTrans(((Mtx*)a)[i], 20.0f + ((Vec*)b)[i].x, ((Vec*)b)[i].y, ((Vec*)b)[i].z);
                ((f32*)c)[i] = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(0, 0.0f, 360.0f, menu->field_48[i], 12);
                if (((f32*)c)[i] > 360.0f) {
                    ((f32*)c)[i] -= 360.0f;
                }
                if (menu->field_48[i] >= 3) {
                    menu->field_1C = 1;
                }
                menu->field_48[i]++;
                if (menu->field_48[i] > 12) {
                    menu->field_34[i] = 1;
                }
                break;
            case 1:
                menu->field_20[i] |= 1;
                menu->field_20[i] |= 2;
                PSMTXTrans(((Mtx*)a)[i], -40.0f, 55.0f, 0.0f);
                ((f32*)c)[i] = 360.0f;
                menu->field_1C = 1;
                break;
            case 10:
                menu->field_20[i] |= 1;
                menu->field_20[i] &= ~2;
                ang = 3.1415927f * kakutable[mainCursor->unk8 - 3][menu->field_84[i]] / 180.0f;
                GetRingCenter(&((Vec*)b)[i]);
                GetRingOffset(ang, &ox, &oy);
                ((Vec*)b)[i].x += ox;
                ((Vec*)b)[i].y += oy;
                ((Vec*)b)[i].z = oy;
                s = 1.0f - 0.1f * menu->field_48[i];
                if (s <= 0.0f) {
                    menu->field_34[i] = 11;
                }
                PSMTXScale(sm, s, s, 1.0f);
                PSMTXTrans(tm, ((Vec*)b)[i].x, ((Vec*)b)[i].y, ((Vec*)b)[i].z);
                PSMTXConcat(tm, sm, ((Mtx*)a)[i]);
                ((f32*)c)[i] = 0.0f;
                menu->field_48[i]++;
                break;
            case 11:
                menu->field_20[i] &= ~1;
                break;
        }
    }
    for (i = 0; i < 7; i++) {
        switch (sw = menu->field_C0[i]) {
            case 0:
                menu->field_A4[i] &= ~1;
                menu->field_114[i] = 0xFF;
                break;
            case 1:
                menu->field_A4[i] &= ~1;
                menu->field_114[i] = 0xFF;
                if (menu->field_DC[i] >= 0 && i != 6) {
                    s = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(0, 90.0f, 0.0f, menu->field_DC[i], 12);
                    menu->field_A4[i] |= 1;
                    PSMTXRotRad(((Mtx*)d)[i], 'y', 0.017453292f * s);
                }
                menu->field_DC[i]++;
                if (menu->field_DC[i] > 12) {
                    menu->field_C0[i] = 2;
                }
                break;
            case 2:
                menu->field_114[i] = 0xFF;
                if (i != 6) {
                    menu->field_A4[i] |= 1;
                    PSMTXIdentity(((Mtx*)d)[i]);
                } else {
                    menu->field_A4[i] &= ~1;
                }
                break;
            case 10:
            case 20:
            case 30:
            case 40:
                if (sw == 10 || sw == 20) {
                    steps = 12;
                }
                if (sw == 30 || sw == 40) {
                    steps = (cursor->unk8 - 6) / 2 + 12;
                }
                menu->field_A4[i] |= 1;
                PSMTXIdentity(((Mtx*)d)[i]);
                menu->field_98 = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(4, menu->field_9C, menu->field_A0, menu->field_DC[i], steps);
                menu->field_DC[i]++;
                if (menu->field_DC[i] > steps) {
                    menu->field_C0[i] = 2;
                    menu->field_DC[i] = 0;
                }
                break;
        }
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ActSelect_Init(BattleWork* wp, BattleCursor* cursor, BattleCommandAct* acts, BOOL flag) {
    s32 i;
    s32 idx;
    BattleSubMenu* menu;

    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
    }
    WP_SUBMENU(wp) = BattleAlloc(sizeof(BattleSubMenu));
    if (flag & 1) {
        menu = WP_SUBMENU(wp);
        menu->cursor = cursor;
        menu->acts = acts;
        menu->field_C = 10;
        menu->field_14 = 0;
        menu->field_18 = cursor->field_0;
        idx = cursor->field_0;
        for (i = 0; i < cursor->unk8; i++) {
            if (idx == cursor->field_0) {
                menu->field_34[idx] = 10;
            } else {
                menu->field_34[idx] = 11;
            }
            menu->field_48[idx] = 0;
            menu->field_84[idx] = cursor->unk8 - 1 + i;
            if (menu->field_84[idx] >= cursor->unk8) {
                menu->field_84[idx] -= cursor->unk8;
            }
            menu->field_20[idx] = 0;
            if (++idx >= cursor->unk8) {
                idx = 0;
            }
        }
    } else {
        menu = WP_SUBMENU(wp);
        menu->cursor = cursor;
        menu->acts = acts;
        menu->field_C = 0;
        menu->field_14 = 0;
        menu->field_18 = cursor->field_0;
        idx = cursor->field_0;
        for (i = 0; i < cursor->unk8; i++) {
            if (++idx >= cursor->unk8) {
                idx = 0;
            }
            menu->field_34[idx] = 0;
            menu->field_48[idx] = (i * 10) / 2;
            menu->field_84[idx] = i;
            menu->field_20[idx] = 0;
        }
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ActSelect_Main(BattleWork* wp) {
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ActSelect_Disp(BattleWork* wp) {
    DrawMainMenu(wp);
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ActSelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}
#endif

#ifdef NONMATCHING
void DrawMainMenu(BattleWork* wp_) {
    Mtx mtx[5];
    Vec pos[5];
    Mtx trans;
    Mtx rot;
    Mtx scale;
    f32 z[5];
    f32 a;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    f32 c;
    f32 ox;
    f32 oy;
    f32 b;
    s32 n;
    s32 diff;
    BattleCursor* mc;

    camGetPtr(CAMERA_2D);
    switch (menu->field_C) {
    case 0:
        n = 0;
        for (i = 0; i < cursor->unk8; i++) {
            if (menu->field_34[i] == 3) {
                n++;
            }
        }
        if (n == cursor->unk8) {
            menu->field_C = 1;
        }
        break;
    case 1:
        menu->field_14 = 1;
        mc = menu->cursor;
        diff = mc->field_0 - menu->field_18;
        if (diff == 1 || -(mc->unk8 - 1) == diff) {
            menu->field_C = 2;
            menu->field_14 = 0;
            menu->field_18 = menu->cursor->field_0;
            for (i = 0; i < cursor->unk8; i++) {
                menu->field_34[i] = 4;
                menu->field_48[i] = 0;
                menu->field_48[i + 10] = menu->field_84[i];
                menu->field_84[i]--;
                if (menu->field_84[i] == -1) {
                    menu->field_84[i] = cursor->unk8 - 1;
                }
            }
        } else if (diff == -1 || mc->unk8 - 1 == diff) {

            menu->field_C = 2;
            menu->field_14 = 0;
            menu->field_18 = menu->cursor->field_0;
            for (i = 0; i < cursor->unk8; i++) {
                menu->field_34[i] = 5;
                menu->field_48[i] = 0;
                menu->field_48[i + 10] = menu->field_84[i];
                menu->field_84[i]++;
                if (menu->field_84[i] == cursor->unk8) {
                    menu->field_84[i] = 0;
                }
            }
        }
        break;
    case 2:
        n = 0;
        for (i = 0; i < cursor->unk8; i++) {
            if (menu->field_34[i] == 3) {
                n++;
            }
        }
        if (n == cursor->unk8) {
            menu->field_C = 1;
        }
        break;
    case 10:
        menu->field_C = 1;
        menu->field_14 = 1;
        break;
    }

    menu->field_1C = 0;
    for (i = 0; i < cursor->unk8; i++) {
        switch (menu->field_34[i]) {
        case 0:
            menu->field_48[i]--;
            if (menu->field_48[i] <= 0) {
                menu->field_34[i] = 1;
                menu->field_48[i] = 0;
            }
            break;
        case 1:
            menu->field_20[i] |= 1;
            c = 0.0f;
            a = c + 0.2f * menu->field_48[i];
            b = 3.1415927f * kakutable[cursor->unk8 - 3][menu->field_84[i]] / 180.0f;
            if (a >= b) {
                a = b;
            }
            GetRingCenter(&pos[i]);
            GetRingOffset(a, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            if (i == cursor->field_0) {
                c = 270.0f + 90.0f * menu->field_48[i] / 10.0f;
                if (c >= 360.0f) {
                    c = 0.0f;
                }
                PSMTXRotRad(rot, 'x', 0.017453292f * c);
                PSMTXTrans(trans, 20.0f + pos[i].x, pos[i].y, pos[i].z);
                PSMTXConcat(trans, rot, mtx[i]);
                menu->field_20[i] |= 2;
            } else {
                c = 270.0f + 90.0f * menu->field_48[i] / 10.0f;
                if (c >= 360.0f) {
                    c = 0.0f;
                }
                PSMTXRotRad(rot, 'x', 0.017453292f * c);
                PSMTXTrans(trans, pos[i].x, pos[i].y, pos[i].z);
                PSMTXConcat(trans, rot, mtx[i]);
            }
            z[i] = 0.0f;
            if (a >= b && menu->field_48[i] >= 10) {
                menu->field_34[i] = 3;
                menu->field_48[i] = -1;
            }
            menu->field_48[i]++;
            break;
        case 3:
            a = 3.1415927f * kakutable[cursor->unk8 - 3][menu->field_84[i]] / 180.0f;
            GetRingCenter(&pos[i]);
            GetRingOffset(a, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            if (i == cursor->field_0) {
                PSMTXTrans(mtx[i], 20.0f + pos[i].x, pos[i].y, pos[i].z);
                menu->field_20[i] |= 2;
            } else {
                PSMTXTrans(mtx[i], pos[i].x, pos[i].y, pos[i].z);
            }
            z[i] = 0.0f;
            break;
        case 4:
            c = kakutable[cursor->unk8 - 3][menu->field_48[i + 10]];
            b = kakutable[cursor->unk8 - 3][menu->field_84[i]];
            if (0.0f == b) {
                b = 360.0f;
            }
            a = 3.1415927f * c / 180.0f + 0.2f * menu->field_48[i];
            b = 3.1415927f * b / 180.0f;
            if (a >= b) {
                a = b;
                menu->field_34[i] = 3;
                menu->field_48[i] = -1;
            }
            GetRingCenter(&pos[i]);
            GetRingOffset(a, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            PSMTXTrans(mtx[i], pos[i].x, pos[i].y, pos[i].z);
            z[i] = 0.0f;
            menu->field_20[i] &= ~2;
            menu->field_48[i]++;
            break;
        case 5:
            c = kakutable[cursor->unk8 - 3][menu->field_48[i + 10]];
            if (0.0f == c) {
                c = 360.0f;
            }
            a = 3.1415927f * c / 180.0f - 0.2f * menu->field_48[i];
            b = 3.1415927f * kakutable[cursor->unk8 - 3][menu->field_84[i]] / 180.0f;
            if (a <= b) {
                a = b;
                menu->field_34[i] = 3;
                menu->field_48[i] = -1;
            }
            GetRingCenter(&pos[i]);
            GetRingOffset(a, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            PSMTXTrans(mtx[i], pos[i].x, pos[i].y, pos[i].z);
            z[i] = 0.0f;
            menu->field_20[i] &= ~2;
            menu->field_48[i]++;
            break;
        case 10:
            menu->field_20[i] |= 1;
            menu->field_20[i] |= 2;
            GetRingCenter(&pos[i]);
            GetRingOffset(0.0f, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            pos[i].x = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(4, -60.0f, pos[i].x, menu->field_48[i], 12);
            pos[i].y = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(4, 55.0f, pos[i].y, menu->field_48[i], 12);
            PSMTXTrans(mtx[i], 20.0f + pos[i].x, pos[i].y, pos[i].z);
            z[i] = ((f32 (*)(s32, f32, f32, s32, s32))intplGetValue)(0, 360.0f, 0.0f, menu->field_48[i], 12);
            menu->field_48[i]++;
            if (menu->field_48[i] > 12) {
                menu->field_34[i] = 3;
            }
            break;
        case 11:
            menu->field_20[i] |= 1;
            menu->field_20[i] &= ~2;
            a = 3.1415927f * kakutable[cursor->unk8 - 3][menu->field_84[i]] / 180.0f;
            GetRingCenter(&pos[i]);
            GetRingOffset(a, &ox, &oy);
            pos[i].x += ox;
            pos[i].y += oy;
            pos[i].z = oy;
            a = 0.1f * menu->field_48[i];
            if (a >= 1.0f) {
                menu->field_34[i] = 3;
            }
            PSMTXScale(scale, a, a, 1.0f);
            PSMTXTrans(trans, pos[i].x, pos[i].y, pos[i].z);
            PSMTXConcat(trans, scale, mtx[i]);
            z[i] = 0.0f;
            menu->field_48[i]++;
            break;
        }
    }
    DrawMainIcon(menu, menu->acts, mtx, pos, z);
    DrawMenuPartyChangeButton();
    DrawMenuPinchMark();
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_WeaponSelect_Init(BattleWork* wp, BattleCursor* cursor, BattleCommandWeapon* weapons, BOOL flag) {
    BattleSubMenu* menu = NULL;
    BattleCursor* mainCursor = NULL;

    InitSubMenuCommonProcess(&menu, &mainCursor, cursor);
    menu->weapons = weapons;
    if (flag & 1) {
        InitSubMenuCommonProcess2(menu, mainCursor);
    } else {
        InitSubMenuCommonProcess3(menu, mainCursor);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_WeaponSelect_Main(BattleWork* wp) {
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_WeaponSelect_Disp(BattleWork* wp) {
    DrawWeaponWin();
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_WeaponSelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}
#endif

#ifdef NONMATCHING
void DrawWeaponWin(void) {
    u8 buf1E4[0x154];
    u8 bufF4[0xF0];
    u8 bufB8[0x3C];
    u8 bufA4[0x14];
    s32 enabled[7];
    const char* names[7];
    s32 costs[7];
    s32 p34[7];
    s16 icons[8];
    Vec v;
    f32 x;
    f32 y;
    BattleWork* wp = _battleWorkPointer;
    BattleCommand* cmd;
    BattleSubMenu* menu;
    BattleCursor* cursor;
    BattleUnit* unit;
    BattleWeapon* weapon;
    const char* help;
    s32 i;
    s32 idx;

    cmd = &wp->commandMenu;
    menu = *(BattleSubMenu**)&cmd->field_55C;
    cursor = menu->cursor;
    unit = BattleGetUnitPtr(wp, wp->activeUnitId);
    weapon = menu->weapons[cursor->field_0].weapon;
    DrawSubMenuCommonProcess(&x, &y, bufF4, bufB8, bufA4, buf1E4);
    for (i = 0; i < 7; i++) {
        idx = (s32)menu->field_98 + i;
        if (idx < cursor->unk8) {
            enabled[i] = menu->weapons[idx].enabled;
            icons[i] = *(u16*)&cmd->weapon[idx].icon;
            names[i] = menu->weapons[idx].name;
            if (menu->weapons[idx].weapon) {
                costs[i] = BtlUnit_GetWeaponCost(unit, menu->weapons[idx].weapon);
            } else {
                costs[i] = 0;
            }
            if (menu->weapons[idx].weapon) {
                p34[i] = (u8)menu->weapons[idx].weapon->baseSpCost;
            } else {
                p34[i] = 0;
            }
        }
    }
    DrawMainIcon(menu, wp->commandMenu.act, bufF4, bufB8, bufA4);
    DrawSubIcon(menu, buf1E4, enabled, icons, names, costs, p34, NULL, 0);
    v = (Vec){-60.0f, 35.0f, 0.0f};
    DrawMenuCursorAndScrollArrow(&v);
    if (weapon) {
        if (weapon->itemId) {
            help = itemDataTable[weapon->itemId].description;
        } else if (weapon == &ItemWeaponData_CookingItem) {
            help = itemDataTable[menu->weapons[cursor->field_0].itemId].description;
        } else {
            help = weapon->description;
        }
    } else {
        help = itemDataTable[menu->weapons[cursor->field_0].itemId].description;
    }
    if (help) {
        DrawMenuHelpWin(help, x, y);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_Operation_Init(BattleWork* wp, BOOL flag) {
    BattleSubMenu* menu;
    BattleCursor* mainCursor;
    BattleCursor* cursor;

    if (BattleGetUnitPtr(wp, wp->activeUnitId)->currentKind == 0xDE) {
        cursor = &wp->commandMenu.cursor[8];
    } else {
        cursor = &wp->commandMenu.cursor[9];
    }
    InitSubMenuCommonProcess(&menu, &mainCursor, cursor);
    if (flag & 1) {
        InitSubMenuCommonProcess2(menu, mainCursor);
    } else {
        InitSubMenuCommonProcess3(menu, mainCursor);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_Operation_Main(BattleWork* wp) {
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_Operation_Disp(BattleWork* wp) {
    DrawOperationWin();
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_Operation_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}
#endif

#ifdef NONMATCHING
void DrawOperationWin(void) {
    u8 buf1E4[0x154];
    u8 bufF4[0xF0];
    u8 bufB8[0x3C];
    u8 bufA4[0x14];
    s32 enabled[7];
    const char* names[7];
    s32 costs[7];
    s32 p34[7];
    s16 icons[8];
    Vec v;
    f32 x;
    f32 y;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    BattleCommandOperation* items;
    s32 i;
    s32 idx;

    BattleGetUnitPtr(wp, wp->activeUnitId);
    items = wp->commandMenu.operation;
    DrawSubMenuCommonProcess(&x, &y, bufF4, bufB8, bufA4, buf1E4);
    for (i = 0; i < 7; i++) {
        idx = (s32)menu->field_98 + i;
        if (idx < cursor->unk8) {
            enabled[i] = items[idx].enabled;
            if (*(u16*)&items[i].icon) {
                icons[i] = *(u16*)&items[idx].icon;
            } else {
                icons[i] = 0x18B;
            }
            names[i] = items[idx].name;
            costs[i] = items[idx].cost;
            p34[i] = 0;
        }
    }
    DrawMainIcon(menu, wp->commandMenu.act, bufF4, bufB8, bufA4);
    DrawSubIcon(menu, buf1E4, enabled, icons, names, costs, p34, NULL, 0);
    v = (Vec){-60.0f, 35.0f, 0.0f};
    DrawMenuCursorAndScrollArrow(&v);
    if (items[cursor->field_0].help) {
        DrawMenuHelpWin(items[cursor->field_0].help, x, y);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ChangePartySelect_Init(BattleWork* wp, BOOL flag) {
    BattleSubMenu* menu;
    BattleCursor* mainCursor;

    InitSubMenuCommonProcess(&menu, &mainCursor, &wp->commandMenu.cursor[10]);
    if (flag & 1) {
        InitSubMenuCommonProcess3(menu, mainCursor);
    } else {
        InitSubMenuCommonProcess2(menu, mainCursor);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ChangePartySelect_Main(BattleWork* wp) {
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ChangePartySelect_Disp(BattleWork* wp) {
    DrawChangePartyWin();
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_ChangePartySelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}
#endif

#ifdef NONMATCHING
void DrawChangePartyWin(void) {
    u8 buf1E4[0x154];
    u8 bufF4[0xF0];
    u8 bufB8[0x3C];
    u8 bufA4[0x14];
    s32 enabled[7];
    const char* names[7];
    s32 costs[7];
    s32 p34[7];
    s16 icons[8];
    Vec v;
    f32 x;
    f32 y;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    BattleCommandParty* items;
    s32 i;
    s32 idx;

    BattleGetUnitPtr(wp, wp->activeUnitId);
    items = wp->commandMenu.party;
    DrawSubMenuCommonProcess(&x, &y, bufF4, bufB8, bufA4, buf1E4);
    for (i = 0; i < 7; i++) {
        idx = (s32)menu->field_98 + i;
        if (idx < cursor->unk8) {
            enabled[i] = items[idx].enabled;
            if (*(u16*)&items[idx].icon) {
                icons[i] = *(u16*)&items[idx].icon;
            } else {
                icons[i] = 0x18B;
            }
            names[i] = items[idx].name;
            costs[i] = 0;
            p34[i] = 0;
        }
    }
    DrawMainIcon(menu, wp->commandMenu.act, bufF4, bufB8, bufA4);
    DrawSubIcon(menu, buf1E4, enabled, icons, names, costs, p34, items, 1);
    v = (Vec){-60.0f, 35.0f, 0.0f};
    DrawMenuCursorAndScrollArrow(&v);
    if (items[cursor->field_0].help) {
        DrawMenuHelpWin(items[cursor->field_0].help, x, y);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_MultiItem_Init(BattleWork* wp, BOOL flag) {
    BattleSubMenu* menu;
    BattleCursor* mainCursor;

    InitSubMenuCommonProcess(&menu, &mainCursor, &wp->commandMenu.cursor[12]);
    if (flag & 1) {
        InitSubMenuCommonProcess2(menu, mainCursor);
    } else {
        InitSubMenuCommonProcess3(menu, mainCursor);
    }
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_MultiItem_Main(BattleWork* wp) {
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_MultiItem_Disp(BattleWork* wp) {
    DrawMultiItemWin();
}
#endif

#ifdef NONMATCHING
void BattleMenuDisp_MultiItem_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}
#endif

#ifdef NONMATCHING
void DrawMultiItemWin(void) {
    u8 buf1E4[0x154];
    u8 bufF4[0xF0];
    u8 bufB8[0x3C];
    u8 bufA4[0x14];
    s32 enabled[7];
    const char* names[7];
    s32 costs[7];
    s32 p34[7];
    s16 icons[8];
    Vec v;
    f32 x;
    f32 y;
    BattleWork* wp = _battleWorkPointer;
    BattleSubMenu* menu = WP_SUBMENU(wp);
    BattleCursor* cursor = menu->cursor;
    BattleCommandMultiItem* items;
    s32 i;
    s32 idx;

    BattleGetUnitPtr(wp, wp->activeUnitId);
    items = wp->commandMenu.multiItem;
    DrawSubMenuCommonProcess(&x, &y, bufF4, bufB8, bufA4, buf1E4);
    for (i = 0; i < 7; i++) {
        idx = (s32)menu->field_98 + i;
        if (idx < cursor->unk8) {
            enabled[i] = items[idx].enabled;
            if (*(u16*)&items[idx].icon) {
                icons[i] = *(u16*)&items[idx].icon;
            } else {
                icons[i] = 0x18B;
            }
            names[i] = items[idx].name;
            costs[i] = items[idx].cost;
            p34[i] = 0;
        }
    }
    DrawMainIcon(menu, wp->commandMenu.act, bufF4, bufB8, bufA4);
    DrawSubIcon(menu, buf1E4, enabled, icons, names, costs, p34, NULL, 0);
    v = (Vec){-60.0f, 35.0f, 0.0f};
    DrawMenuCursorAndScrollArrow(&v);
    if (items[cursor->field_0].help) {
        DrawMenuHelpWin(items[cursor->field_0].help, x, y);
    }
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: SelectedItemCoordinateColorUpDate (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const u32 dat_802ef068[32] = { 0xC1A00000, 0x42200000, 0x00000000, 0x42200000, 0x00000000, 0x41A00000, 0xC1A00000, 0x41A00000, 0x41A00000, 0x42200000, 0x41A00000, 0x41A00000, 0x00000000, 0x41A00000, 0x00000000, 0x42200000, 0xC1A00000, 0x41A00000, 0x00000000, 0x41A00000, 0x00000000, 0x00000000, 0xC1A00000, 0x00000000, 0x00000000, 0x41A00000, 0x41A00000, 0x41A00000, 0x41A00000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const u32 dat_802ef0e8[32] = { 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802ef168[3] = { -60.0f, 35.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ef174[3] = { -60.0f, 35.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ef180[3] = { -60.0f, 35.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ef18c[3] = { -60.0f, 35.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802ef198 = 4503601774854144;
__declspec(section ".rodata") const char str_802EF1A0[] = "\202\271\202\302\202\337\202\242\202\315\201@\202\310\202\242\202\314\202\276\201I\201I\000\000\000";
__declspec(section ".rodata") const char str_802EF1BC[] = "SFX_BTL_SYS_CAUTION_THROW1\000";
__declspec(section ".rodata") const char str_802EF1D8[] = "btl_cost_disp_FP\000\000\000";
__declspec(section ".rodata") const char str_802EF1EC[] = "btl_cost_disp_AP\000\000\000";
__declspec(section ".rodata") const char str_802EF200[] = "btl_disp_HP";
__declspec(section ".rodata") const char str_802EF20C[] = "btl_disp_slash\000";
__declspec(section ".rodata") const u32 gap_04_802EF21C_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_to_int_mask_802ef220 = 4503599627370496;
__declspec(section ".rodata") const char str_802EF228[] = "%s/battle/common/battle_common.tpl\000";
__declspec(section ".rodata") const u32 gap_04_802EF24C_rodata[1] = { 0x00000000 };
__declspec(section ".sdata2") const u32 dat_8041c118 = 0xE1E1E1FF;
__declspec(section ".sdata2") const u32 dat_8041c11c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c120 = 0x808080FF;
__declspec(section ".sdata2") const u32 dat_8041c124 = 0xE1E1E1FF;
__declspec(section ".sdata2") const u32 dat_8041c128 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c12c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c130 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_8041c134 = 0xFFFFFF00;
__declspec(section ".sdata2") const f32 float_3p0039_8041c138 = 3.0039063f;
__declspec(section ".sdata2") const u32 dat_8041c13c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041c140 = 0xFFFFFFCF;
__declspec(section ".sdata2") const f32 float_0_8041c144 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p2_8041c148 = 0.2f;
__declspec(section ".sdata2") const f32 float_3p1416_8041c14c = 3.1415927f;
__declspec(section ".sdata2") const f32 float_180_8041c150 = 180.0f;
__declspec(section ".sdata2") const f32 float_270_8041c154 = 270.0f;
__declspec(section ".sdata2") const f32 float_90_8041c158 = 90.0f;
__declspec(section ".sdata2") const f32 float_10_8041c15c = 10.0f;
__declspec(section ".sdata2") const f32 float_360_8041c160 = 360.0f;
__declspec(section ".sdata2") const f32 float_0p017453_8041c164 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_20_8041c168 = 20.0f;
__declspec(section ".sdata2") const f32 float_neg60_8041c16c = -60.0f;
__declspec(section ".sdata2") const f32 float_55_8041c170 = 55.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041c174 = 0.1f;
__declspec(section ".sdata2") const f32 float_1_8041c178 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg200_8041c17c = -200.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041c180 = -100.0f;
__declspec(section ".sdata2") const f32 float_neg40_8041c184 = -40.0f;
__declspec(section ".sdata2") const f32 float_155_8041c188 = 155.0f;
__declspec(section ".sdata2") const f32 float_15_8041c18c = 15.0f;
__declspec(section ".sdata2") const f32 float_0p75_8041c190 = 0.75f;
__declspec(section ".sdata2") const f32 float_164_8041c194 = 164.0f;
__declspec(section ".sdata2") const f32 float_24_8041c198 = 24.0f;
__declspec(section ".sdata2") const f32 float_400_8041c19c = 400.0f;
__declspec(section ".sdata2") const f32 float_50_8041c1a0 = 50.0f;
__declspec(section ".sdata2") const f32 float_0p8_8041c1a4 = 0.8f;
__declspec(section ".sdata2") const f32 float_4_8041c1a8 = 4.0f;
__declspec(section ".sdata2") const f32 float_28_8041c1ac = 28.0f;
__declspec(section ".sdata2") const f32 float_52_8041c1b0 = 52.0f;
__declspec(section ".sdata2") const f32 float_60_8041c1b4 = 60.0f;
__declspec(section ".sdata2") const f32 float_neg28_8041c1b8 = -28.0f;
__declspec(section ".sdata2") const f32 float_12_8041c1bc = 12.0f;
__declspec(section ".sdata2") const f32 float_neg12_8041c1c0 = -12.0f;
__declspec(section ".sdata2") const f32 float_5_8041c1c4 = 5.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041c1c8 = 0.5f;
__declspec(section ".sdata2") const f32 float_255_8041c1cc = 255.0f;
__declspec(section ".sdata2") const f32 float_144_8041c1d0 = 144.0f;
__declspec(section ".sdata2") const f32 float_neg152_8041c1d4 = -152.0f;
__declspec(section ".sdata2") const f32 float_neg136_8041c1d8 = -136.0f;
__declspec(section ".sdata2") const f32 float_152_8041c1dc = 152.0f;
__declspec(section ".sdata2") const f32 float_136_8041c1e0 = 136.0f;
__declspec(section ".sdata2") const f32 float_neg119_8041c1e4 = -119.0f;
__declspec(section ".sdata2") const f32 float_2_8041c1e8 = 2.0f;
__declspec(section ".sdata2") const f32 float_neg104_8041c1ec = -104.0f;
__declspec(section ".sdata2") const f32 float_22_8041c1f0 = 22.0f;
__declspec(section ".sdata2") const f32 float_120_8041c1f4 = 120.0f;
__declspec(section ".sdata2") const f32 float_72_8041c1f8 = 72.0f;
__declspec(section ".sdata2") const f32 float_25_8041c1fc = 25.0f;
__declspec(section ".sdata2") const f32 float_30_8041c200 = 30.0f;
__declspec(section ".sdata2") const f32 float_26_8041c204 = 26.0f;
__declspec(section ".sdata2") const f32 float_92_8041c208 = 92.0f;
__declspec(section ".sdata2") const f32 float_100_8041c20c = 100.0f;
__declspec(section ".sdata2") const f32 float_76_8041c210 = 76.0f;
__declspec(section ".sdata2") const f32 float_78_8041c214 = 78.0f;
__declspec(section ".sdata2") const f32 float_35_8041c218 = 35.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041c21c = 1.5f;
__declspec(section ".sdata2") const f32 float_1p3_8041c220 = 1.3f;
__declspec(section ".sdata2") const f32 float_0p005_8041c224 = 0.005f;
__declspec(section ".sdata2") const f32 float_8_8041c228 = 8.0f;
__declspec(section ".sdata2") const f32 float_neg4_8041c22c = -4.0f;
__declspec(section ".sdata2") const f32 float_neg3p0769_8041c230 = -3.0769231f;
__declspec(section ".sdata2") const f32 float_7p5_8041c234 = 7.5f;
__declspec(section ".sdata2") const f32 float_0p66_8041c238 = 0.66f;
__declspec(section ".sdata2") const f32 float_neg5_8041c23c = -5.0f;
__declspec(section ".sdata2") const f32 float_64_8041c240 = 64.0f;
__declspec(section ".sdata2") const f32 float_neg64_8041c244 = -64.0f;
__declspec(section ".sdata2") const f32 float_80_8041c248 = 80.0f;
__declspec(section ".sdata2") const f32 float_neg67_8041c24c = -67.0f;
__declspec(section ".sdata2") const f32 float_52p5_8041c250 = 52.5f;
__declspec(section ".sdata2") const f32 float_0p9_8041c254 = 0.9f;
__declspec(section ".sdata2") const f32 float_4p7124_8041c258 = 4.712389f;
__declspec(section ".sdata2") const f32 float_22p5_8041c25c = 22.5f;
__declspec(section ".sdata2") const f32 float_105_8041c260 = 105.0f;
__declspec(section ".sdata2") const f32 float_neg180_8041c264 = -180.0f;

__declspec(section ".sdata2") u32 gap_10_80422FF4_sbss2[1]; // FAKE: .sbss2 pad after unk_80422ff0 (reverse emit order)
__declspec(section ".sdata2") const u32 unk_80422ff0;
void DrawMainMenu(BattleWork* wp);
__declspec(section ".data") static void* jumptable_80360D14[] = {
    (char*)DrawMainMenu + 0x274,
    (char*)DrawMainMenu + 0x2A0,
    (char*)DrawMainMenu + 0xA2C,
    (char*)DrawMainMenu + 0x4E8,
    (char*)DrawMainMenu + 0x5C0,
    (char*)DrawMainMenu + 0x6E8,
    (char*)DrawMainMenu + 0xA2C,
    (char*)DrawMainMenu + 0xA2C,
    (char*)DrawMainMenu + 0xA2C,
    (char*)DrawMainMenu + 0xA2C,
    (char*)DrawMainMenu + 0x810,
    (char*)DrawMainMenu + 0x908,
};
void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d);
__declspec(section ".data") static void* jumptable_80360D44[] = {
    (char*)DrawSubMenuCommonProcess + 0x598,
    (char*)DrawSubMenuCommonProcess + 0x5B4,
    (char*)DrawSubMenuCommonProcess + 0x638,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x674,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x674,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x674,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x704,
    (char*)DrawSubMenuCommonProcess + 0x674,
};
void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d);
__declspec(section ".data") static void* jumptable_80360DE8[] = {
    (char*)DrawSubMenuCommonProcess + 0x114,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x1D8,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x21C,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x21C,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x21C,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x2A4,
    (char*)DrawSubMenuCommonProcess + 0x21C,
};
void* BattleAlloc(u32 size);
void BattleAudience_GetItemOn(s32* memberId, f32* x, f32* y, f32* z, ItemType* itemType);
void BattleFree(void* ptr);
BattleUnit* BattleGetMarioPtr(BattleWork* work);
BattleUnit* BattleGetPartyPtr(BattleWork* wp);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
void FontDrawStart(void);
void FontDrawStringMtx(Mtx mtx, const char* message);
u16 FontGetMessageWidth(const char* message);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXSetNumTevStages(u8 nStages);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void InitSubMenuCommonProcess();
void InitSubMenuCommonProcess2();
void InitSubMenuCommonProcess3();
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id);
CameraEntry* camGetPtr(CameraId cameraId);
FileEntry* fileAlloc(const char* filename, s32 type);
void fileFree(FileEntry* handle);
const char* getMarioStDvdRoot(void);
void iconDispGx(Vec* position, s16 flags, u16 iconId, f32 scale);
void iconDispGx2(Mtx mtx, s16 flags, s16 iconId);
void iconDispGxCol(Mtx pos, s16 flags, s32 iconId, GXColor color);
f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
const char* msgSearch(const char* tag);
void psndSFXOn(const char* name);
void windowDispGX_Waku_col(u16 gxTexMapID, GXColor color, f32 x, f32 y, f32 width, f32 height, f32 curve);
__declspec(section ".sdata") u32 gap_08_80418981_sbss[1]; // FAKE: .sbss pad after seq (reverse emit order)
/* G5 TODO init seq$510 in None */ static u8 g5_seq_s510[1];
asm void DrawMultiItemWin(void) {
	nofralloc
	stwu r1, -0x350(r1)
	mflr r0
	stw r0, 0x354(r1)
	stmw r28, 0x340(r1)
	lwz r31, _battleWorkPointer(r13)
	lwz r30, 0x1c78(r31)
	mr r3, r31
	lwz r4, 0x420(r31)
	lwz r29, 0x0(r30)
	bl BattleGetUnitPtr
	addi r28, r31, 0x1b6c
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	addi r8, r1, 0x1e4
	bl DrawSubMenuCommonProcess
	li r0, 0x7
	li r9, 0x0
	li r3, 0x0
	li r4, 0x0
	mtctr r0
	@1:
	lfs f0, 0x98(r30)
	lwz r0, 0x8(r29)
	fctiwz f0, f0
	stfd f0, 0x338(r1)
	lwz r5, 0x33c(r1)
	add r5, r5, r9
	cmpw r5, r0
	bge @2
	mulli r0, r5, 0x18
	addi r5, r1, 0x88
	add r8, r28, r0
	lwz r0, 0x0(r8)
	stwx r0, r5, r4
	lhz r0, 0xc(r8)
	cmplwi r0, 0x0
	beq @3
	addi r5, r1, 0x24
	sthx r0, r5, r3
	b @4
	@3:
	addi r5, r1, 0x24
	li r0, 0x18b
	sthx r0, r5, r3
	@4:
	lwz r0, 0x4(r8)
	addi r7, r1, 0x6c
	addi r6, r1, 0x50
	addi r5, r1, 0x34
	stwx r0, r7, r4
	li r0, 0x0
	lwz r7, 0x10(r8)
	stwx r7, r6, r4
	stwx r0, r5, r4
	@2:
	addi r9, r9, 0x1
	addi r3, r3, 0x2
	addi r4, r4, 0x4
	bdnz @1
	mr r3, r30
	addi r4, r31, 0x1724
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	bl DrawMainIcon
	li r0, 0x0
	mr r3, r30
	stw r0, 0x8(r1)
	addi r4, r1, 0x1e4
	addi r5, r1, 0x88
	addi r6, r1, 0x24
	addi r7, r1, 0x6c
	addi r8, r1, 0x50
	addi r9, r1, 0x34
	li r10, 0x0
	bl DrawSubIcon
	lis r4, vec3_802ef18c@ha
	addi r3, r1, 0x18
	addi r6, r4, vec3_802ef18c@l
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	bl DrawMenuCursorAndScrollArrow
	lwz r0, 0x0(r29)
	mulli r0, r0, 0x18
	add r3, r28, r0
	lwz r3, 0x8(r3)
	cmplwi r3, 0x0
	beq @5
	lfs f1, 0x14(r1)
	lfs f2, 0x10(r1)
	bl DrawMenuHelpWin
	@5:
	lmw r28, 0x340(r1)
	lwz r0, 0x354(r1)
	mtlr r0
	addi r1, r1, 0x350
	blr
}

asm void BattleMenuDisp_MultiItem_End(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	li r0, 0x0
	stw r0, 0x1c78(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_MultiItem_Disp(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl DrawMultiItemWin
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_MultiItem_Main(BattleWork* wp) {
	nofralloc
	blr
}

asm void BattleMenuDisp_MultiItem_Init(BattleWork* wp, BOOL flag) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	mr r5, r3
	stw r0, 0x24(r1)
	addi r3, r1, 0xc
	addi r5, r5, 0x1c44
	stw r31, 0x1c(r1)
	mr r31, r4
	addi r4, r1, 0x8
	bl InitSubMenuCommonProcess
	clrlwi. r0, r31, 31
	beq @1
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess2
	b @2
	@1:
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess3
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawChangePartyWin(void) {
	nofralloc
	stwu r1, -0x350(r1)
	mflr r0
	stw r0, 0x354(r1)
	stmw r28, 0x340(r1)
	lwz r31, _battleWorkPointer(r13)
	lwz r30, 0x1c78(r31)
	mr r3, r31
	lwz r4, 0x420(r31)
	lwz r29, 0x0(r30)
	bl BattleGetUnitPtr
	addi r28, r31, 0x1aac
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	addi r8, r1, 0x1e4
	bl DrawSubMenuCommonProcess
	li r0, 0x7
	li r9, 0x0
	li r3, 0x0
	li r4, 0x0
	mtctr r0
	@1:
	lfs f0, 0x98(r30)
	lwz r0, 0x8(r29)
	fctiwz f0, f0
	stfd f0, 0x338(r1)
	lwz r5, 0x33c(r1)
	add r5, r5, r9
	cmpw r5, r0
	bge @2
	mulli r0, r5, 0x18
	addi r5, r1, 0x88
	add r6, r28, r0
	lwz r0, 0x4(r6)
	stwx r0, r5, r4
	lhz r0, 0xc(r6)
	cmplwi r0, 0x0
	beq @3
	addi r5, r1, 0x24
	sthx r0, r5, r3
	b @4
	@3:
	addi r5, r1, 0x24
	li r0, 0x18b
	sthx r0, r5, r3
	@4:
	lwz r8, 0x8(r6)
	addi r7, r1, 0x6c
	addi r6, r1, 0x50
	li r0, 0x0
	addi r5, r1, 0x34
	stwx r8, r7, r4
	stwx r0, r6, r4
	stwx r0, r5, r4
	@2:
	addi r9, r9, 0x1
	addi r3, r3, 0x2
	addi r4, r4, 0x4
	bdnz @1
	mr r3, r30
	addi r4, r31, 0x1724
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	bl DrawMainIcon
	li r0, 0x1
	mr r3, r30
	stw r0, 0x8(r1)
	mr r10, r28
	addi r4, r1, 0x1e4
	addi r5, r1, 0x88
	addi r6, r1, 0x24
	addi r7, r1, 0x6c
	addi r8, r1, 0x50
	addi r9, r1, 0x34
	bl DrawSubIcon
	lis r4, vec3_802ef180@ha
	addi r3, r1, 0x18
	addi r6, r4, vec3_802ef180@l
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	bl DrawMenuCursorAndScrollArrow
	lwz r0, 0x0(r29)
	mulli r0, r0, 0x18
	add r3, r28, r0
	lwz r3, 0x10(r3)
	cmplwi r3, 0x0
	beq @5
	lfs f1, 0x14(r1)
	lfs f2, 0x10(r1)
	bl DrawMenuHelpWin
	@5:
	lmw r28, 0x340(r1)
	lwz r0, 0x354(r1)
	mtlr r0
	addi r1, r1, 0x350
	blr
}

asm void BattleMenuDisp_ChangePartySelect_End(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	li r0, 0x0
	stw r0, 0x1c78(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_ChangePartySelect_Disp(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl DrawChangePartyWin
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_ChangePartySelect_Main(BattleWork* wp) {
	nofralloc
	blr
}

asm void BattleMenuDisp_ChangePartySelect_Init(BattleWork* wp, BOOL flag) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	mr r5, r3
	stw r0, 0x24(r1)
	addi r3, r1, 0xc
	addi r5, r5, 0x1c2c
	stw r31, 0x1c(r1)
	mr r31, r4
	addi r4, r1, 0x8
	bl InitSubMenuCommonProcess
	clrlwi. r0, r31, 31
	beq @1
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess3
	b @2
	@1:
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess2
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawOperationWin(void) {
	nofralloc
	stwu r1, -0x350(r1)
	mflr r0
	stw r0, 0x354(r1)
	stmw r28, 0x340(r1)
	lwz r31, _battleWorkPointer(r13)
	lwz r30, 0x1c78(r31)
	mr r3, r31
	lwz r4, 0x420(r31)
	lwz r29, 0x0(r30)
	bl BattleGetUnitPtr
	addi r28, r31, 0x19e8
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	addi r8, r1, 0x1e4
	bl DrawSubMenuCommonProcess
	li r0, 0x7
	li r10, 0x0
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	mtctr r0
	@1:
	lfs f0, 0x98(r30)
	lwz r0, 0x8(r29)
	fctiwz f0, f0
	stfd f0, 0x338(r1)
	lwz r6, 0x33c(r1)
	add r6, r6, r10
	cmpw r6, r0
	bge @2
	mulli r7, r6, 0x1c
	addi r6, r1, 0x88
	addi r0, r4, 0x10
	add r9, r28, r7
	lwz r7, 0x4(r9)
	stwx r7, r6, r5
	lhzx r0, r28, r0
	cmplwi r0, 0x0
	beq @3
	lhz r0, 0x10(r9)
	addi r6, r1, 0x24
	sthx r0, r6, r3
	b @4
	@3:
	addi r6, r1, 0x24
	li r0, 0x18b
	sthx r0, r6, r3
	@4:
	lwz r0, 0xc(r9)
	addi r8, r1, 0x6c
	addi r7, r1, 0x50
	addi r6, r1, 0x34
	stwx r0, r8, r5
	li r0, 0x0
	lwz r8, 0x18(r9)
	stwx r8, r7, r5
	stwx r0, r6, r5
	@2:
	addi r10, r10, 0x1
	addi r3, r3, 0x2
	addi r4, r4, 0x1c
	addi r5, r5, 0x4
	bdnz @1
	mr r3, r30
	addi r4, r31, 0x1724
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	bl DrawMainIcon
	li r0, 0x0
	mr r3, r30
	stw r0, 0x8(r1)
	addi r4, r1, 0x1e4
	addi r5, r1, 0x88
	addi r6, r1, 0x24
	addi r7, r1, 0x6c
	addi r8, r1, 0x50
	addi r9, r1, 0x34
	li r10, 0x0
	bl DrawSubIcon
	lis r4, vec3_802ef174@ha
	addi r3, r1, 0x18
	addi r6, r4, vec3_802ef174@l
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	bl DrawMenuCursorAndScrollArrow
	lwz r0, 0x0(r29)
	mulli r0, r0, 0x1c
	add r3, r28, r0
	lwz r3, 0x14(r3)
	cmplwi r3, 0x0
	beq @5
	lfs f1, 0x14(r1)
	lfs f2, 0x10(r1)
	bl DrawMenuHelpWin
	@5:
	lmw r28, 0x340(r1)
	lwz r0, 0x354(r1)
	mtlr r0
	addi r1, r1, 0x350
	blr
}

asm void BattleMenuDisp_Operation_End(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	li r0, 0x0
	stw r0, 0x1c78(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_Operation_Disp(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl DrawOperationWin
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_Operation_Main(BattleWork* wp) {
	nofralloc
	blr
}

asm void BattleMenuDisp_Operation_Init(BattleWork* wp, BOOL flag) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r30, 0x18(r1)
	mr r31, r4
	mr r30, r3
	lwz r4, 0x420(r3)
	bl BattleGetUnitPtr
	lwz r0, 0x8(r3)
	cmpwi r0, 0xde
	bne @1
	addi r5, r30, 0x1c14
	b @2
	@1:
	addi r5, r30, 0x1c20
	@2:
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl InitSubMenuCommonProcess
	clrlwi. r0, r31, 31
	beq @3
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess2
	b @4
	@3:
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess3
	@4:
	lmw r30, 0x18(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawWeaponWin(void) {
	nofralloc
	stwu r1, -0x370(r1)
	mflr r0
	stw r0, 0x374(r1)
	stmw r22, 0x348(r1)
	lwz r31, _battleWorkPointer(r13)
	lwz r28, 0x1c78(r31)
	addi r29, r31, 0x171c
	lwz r4, 0x420(r31)
	mr r3, r31
	lwz r27, 0x0(r28)
	bl BattleGetUnitPtr
	lwz r0, 0x0(r27)
	mr r26, r3
	lwz r6, 0x8(r28)
	addi r3, r1, 0x14
	mulli r0, r0, 0x1c
	addi r4, r1, 0x10
	addi r5, r1, 0xf4
	addi r7, r1, 0xa4
	lwzx r25, r6, r0
	addi r6, r1, 0xb8
	addi r8, r1, 0x1e4
	bl DrawSubMenuCommonProcess
	li r24, 0x0
	li r23, 0x0
	li r22, 0x0
	@1:
	lfs f0, 0x98(r28)
	lwz r0, 0x8(r27)
	fctiwz f0, f0
	stfd f0, 0x338(r1)
	lwz r3, 0x33c(r1)
	add r3, r3, r24
	cmpw r3, r0
	bge @2
	mulli r30, r3, 0x1c
	lwz r5, 0x8(r28)
	addi r6, r1, 0x88
	addi r4, r1, 0x24
	addi r0, r30, 0x4
	addi r3, r1, 0x6c
	lwzx r7, r5, r0
	addi r5, r30, 0x8c
	addi r0, r30, 0x8
	stwx r7, r6, r22
	lhzx r5, r29, r5
	sthx r5, r4, r23
	lwz r4, 0x8(r28)
	lwzx r0, r4, r0
	stwx r0, r3, r22
	lwz r3, 0x8(r28)
	lwzx r4, r3, r30
	cmplwi r4, 0x0
	beq @3
	mr r3, r26
	bl BtlUnit_GetWeaponCost
	addi r4, r1, 0x50
	stwx r3, r4, r22
	b @4
	@3:
	addi r3, r1, 0x50
	li r0, 0x0
	stwx r0, r3, r22
	@4:
	lwz r3, 0x8(r28)
	lwzx r3, r3, r30
	cmplwi r3, 0x0
	beq @5
	lbz r0, 0x12(r3)
	addi r3, r1, 0x34
	stwx r0, r3, r22
	b @2
	@5:
	addi r3, r1, 0x34
	li r0, 0x0
	stwx r0, r3, r22
	@2:
	addi r24, r24, 0x1
	addi r22, r22, 0x4
	cmpwi r24, 0x7
	addi r23, r23, 0x2
	blt @1
	mr r3, r28
	addi r4, r31, 0x1724
	addi r5, r1, 0xf4
	addi r6, r1, 0xb8
	addi r7, r1, 0xa4
	bl DrawMainIcon
	li r0, 0x0
	mr r3, r28
	stw r0, 0x8(r1)
	addi r4, r1, 0x1e4
	addi r5, r1, 0x88
	addi r6, r1, 0x24
	addi r7, r1, 0x6c
	addi r8, r1, 0x50
	addi r9, r1, 0x34
	li r10, 0x0
	bl DrawSubIcon
	lis r4, vec3_802ef168@ha
	addi r3, r1, 0x18
	addi r6, r4, vec3_802ef168@l
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	bl DrawMenuCursorAndScrollArrow
	cmplwi r25, 0x0
	beq @6
	lwz r0, 0x8(r25)
	cmpwi r0, 0x0
	beq @7
	mulli r0, r0, 0x28
	lis r3, itemDataTable@ha
	addi r3, r3, itemDataTable@l
	add r3, r3, r0
	lwz r3, 0x8(r3)
	b @8
	@7:
	lis r3, ItemWeaponData_CookingItem@ha
	addi r0, r3, ItemWeaponData_CookingItem@l
	cmplw r25, r0
	bne @9
	lwz r0, 0x0(r27)
	lis r4, itemDataTable@ha
	lwz r3, 0x8(r28)
	addi r4, r4, itemDataTable@l
	mulli r0, r0, 0x1c
	add r3, r3, r0
	lwz r0, 0x14(r3)
	mulli r0, r0, 0x28
	add r3, r4, r0
	lwz r3, 0x8(r3)
	b @8
	@9:
	lwz r3, 0xc(r25)
	b @8
	@6:
	lwz r0, 0x0(r27)
	lis r4, itemDataTable@ha
	lwz r3, 0x8(r28)
	addi r4, r4, itemDataTable@l
	mulli r0, r0, 0x1c
	add r3, r3, r0
	lwz r0, 0x14(r3)
	mulli r0, r0, 0x28
	add r3, r4, r0
	lwz r3, 0x8(r3)
	@8:
	cmplwi r3, 0x0
	beq @10
	lfs f1, 0x14(r1)
	lfs f2, 0x10(r1)
	bl DrawMenuHelpWin
	@10:
	lmw r22, 0x348(r1)
	lwz r0, 0x374(r1)
	mtlr r0
	addi r1, r1, 0x370
	blr
}

asm void BattleMenuDisp_WeaponSelect_End(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	li r0, 0x0
	stw r0, 0x1c78(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_WeaponSelect_Disp(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl DrawWeaponWin
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_WeaponSelect_Main(BattleWork* wp) {
	nofralloc
	blr
}

asm void BattleMenuDisp_WeaponSelect_Init(BattleWork* wp, BattleCursor* cursor, BattleCommandWeapon* weapons, BOOL flag) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	li r0, 0x0
	addi r3, r1, 0xc
	stmw r30, 0x18(r1)
	mr r30, r5
	mr r5, r4
	mr r31, r6
	addi r4, r1, 0x8
	stw r0, 0xc(r1)
	stw r0, 0x8(r1)
	bl InitSubMenuCommonProcess
	lwz r3, 0xc(r1)
	clrlwi. r0, r31, 31
	stw r30, 0x8(r3)
	beq @1
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess2
	b @2
	@1:
	lwz r3, 0xc(r1)
	lwz r4, 0x8(r1)
	bl InitSubMenuCommonProcess3
	@2:
	lmw r30, 0x18(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawMainMenu(BattleWork* wp_) {
	nofralloc
	stwu r1, -0x230(r1)
	mflr r0
	stw r0, 0x234(r1)
	stfd f31, 0x220(r1)
	psq_st f31, 0x228(r1), 0, 0
	stfd f30, 0x210(r1)
	psq_st f30, 0x218(r1), 0, 0
	stmw r24, 0x1f0(r1)
	lwz r4, _battleWorkPointer(r13)
	li r3, 0x8
	lwz r28, 0x1c78(r4)
	lwz r27, 0x0(r28)
	bl camGetPtr
	lwz r0, 0xc(r28)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0xa
	beq @6
	b @5
	@3:
	lwz r4, 0x8(r27)
	li r5, 0x0
	li r3, 0x0
	mtctr r4
	cmpwi r4, 0x0
	ble @7
	@8:
	addi r0, r3, 0x34
	lwzx r0, r28, r0
	cmpwi r0, 0x3
	bne @9
	addi r5, r5, 0x1
	@9:
	addi r3, r3, 0x4
	bdnz @8
	@7:
	cmpw r5, r4
	bne @5
	li r0, 0x1
	stw r0, 0xc(r28)
	b @5
	@4:
	li r0, 0x1
	stb r0, 0x14(r28)
	lwz r5, 0x0(r28)
	lwz r3, 0x18(r28)
	lwz r0, 0x0(r5)
	subf r4, r3, r0
	cmpwi r4, 0x1
	beq @10
	lwz r3, 0x8(r5)
	subi r3, r3, 0x1
	neg r0, r3
	cmpw r0, r4
	bne @11
	@10:
	li r0, 0x2
	li r6, 0x0
	stw r0, 0xc(r28)
	mr r8, r6
	li r3, 0x0
	li r5, 0x4
	stb r6, 0x14(r28)
	lwz r4, 0x0(r28)
	lwz r0, 0x0(r4)
	stw r0, 0x18(r28)
	b @12
	@13:
	add r7, r28, r3
	stw r5, 0x34(r7)
	stw r6, 0x48(r7)
	lwz r0, 0x84(r7)
	stw r0, 0x70(r7)
	lwz r4, 0x84(r7)
	subi r0, r4, 0x1
	stw r0, 0x84(r7)
	lwz r0, 0x84(r7)
	cmpwi r0, -0x1
	bne @14
	lwz r4, 0x8(r27)
	subi r0, r4, 0x1
	stw r0, 0x84(r7)
	@14:
	addi r8, r8, 0x1
	addi r3, r3, 0x4
	@12:
	lwz r0, 0x8(r27)
	cmpw r8, r0
	blt @13
	b @5
	@11:
	cmpwi r4, -0x1
	beq @15
	cmpw r3, r4
	bne @5
	@15:
	li r0, 0x2
	li r6, 0x0
	stw r0, 0xc(r28)
	mr r8, r6
	li r3, 0x0
	li r5, 0x5
	stb r6, 0x14(r28)
	lwz r4, 0x0(r28)
	lwz r0, 0x0(r4)
	stw r0, 0x18(r28)
	b @16
	@17:
	add r7, r28, r3
	stw r5, 0x34(r7)
	stw r6, 0x48(r7)
	lwz r0, 0x84(r7)
	stw r0, 0x70(r7)
	lwz r4, 0x84(r7)
	addi r0, r4, 0x1
	stw r0, 0x84(r7)
	lwz r4, 0x84(r7)
	lwz r0, 0x8(r27)
	cmpw r4, r0
	bne @18
	stw r6, 0x84(r7)
	@18:
	addi r8, r8, 0x1
	addi r3, r3, 0x4
	@16:
	lwz r0, 0x8(r27)
	cmpw r8, r0
	blt @17
	b @5
	@1:
	lwz r4, 0x8(r27)
	li r5, 0x0
	li r3, 0x0
	mtctr r4
	cmpwi r4, 0x0
	ble @19
	@20:
	addi r0, r3, 0x34
	lwzx r0, r28, r0
	cmpwi r0, 0x3
	bne @21
	addi r5, r5, 0x1
	@21:
	addi r3, r3, 0x4
	bdnz @20
	@19:
	cmpw r5, r4
	bne @5
	li r0, 0x1
	stw r0, 0xc(r28)
	b @5
	@6:
	li r0, 0x1
	stw r0, 0xc(r28)
	stb r0, 0x14(r28)
	@5:
	li r29, 0x0
	li r26, 0x0
	stw r29, 0x1c(r28)
	li r25, 0x0
	li r24, 0x0
	b @22
	@23:
	add r31, r28, r24
	lwz r0, 0x34(r31)
	cmplwi r0, 0xb
	bgt @24
	lis r3, jumptable_80360D14@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80360D14@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@25:
	lwz r3, 0x48(r31)
	subi r0, r3, 0x1
	stw r0, 0x48(r31)
	lwz r0, 0x48(r31)
	cmpwi r0, 0x0
	bgt @24
	li r3, 0x1
	li r0, 0x0
	stw r3, 0x34(r31)
	stw r0, 0x48(r31)
	b @24
	@26:
	lwz r0, 0x20(r31)
	lis r3, kakutable@ha
	lis r5, 0x4330
	lis r4, double_to_int_802ef198@ha
	ori r0, r0, 0x1
	addi r3, r3, kakutable@l
	stw r0, 0x20(r31)
	addi r7, r4, double_to_int_802ef198@l
	lfs f2, float_3p1416_8041c14c(r2)
	lwz r4, 0x8(r27)
	lwz r0, 0x84(r31)
	mulli r4, r4, 0x14
	lwz r6, 0x48(r31)
	slwi r0, r0, 2
	lfs f0, float_180_8041c150(r2)
	xoris r6, r6, 0x8000
	stw r5, 0x1e0(r1)
	add r3, r3, r4
	stw r6, 0x1e4(r1)
	add r3, r3, r0
	lfd f4, 0x0(r7)
	lfs f1, -0x3c(r3)
	lfd f3, 0x1e0(r1)
	fmuls f1, f2, f1
	lfs f5, float_0p2_8041c148(r2)
	fsubs f3, f3, f4
	lfs f2, float_0_8041c144(r2)
	fdivs f30, f1, f0
	fmadds f31, f5, f3, f2
	fcmpo cr0, f31, f30
	cror eq, gt, eq
	bne @27
	fmr f31, f30
	@27:
	addi r30, r1, 0xb4
	add r30, r30, r25
	mr r3, r30
	bl GetRingCenter
	fmr f1, f31
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	lfs f0, 0xc(r1)
	lfs f2, 0x8(r1)
	fadds f0, f1, f0
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r30)
	fadds f0, f0, f2
	stfs f0, 0x4(r30)
	stfs f2, 0x8(r30)
	lwz r0, 0x0(r27)
	cmpw r29, r0
	bne @28
	lwz r4, 0x48(r31)
	lis r0, 0x4330
	stw r0, 0x1e0(r1)
	lis r3, double_to_int_802ef198@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802ef198@l(r3)
	stw r0, 0x1e4(r1)
	lfs f3, float_90_8041c158(r2)
	lfd f0, 0x1e0(r1)
	lfs f1, float_10_8041c15c(r2)
	fsubs f2, f0, f2
	lfs f4, float_270_8041c154(r2)
	lfs f0, float_360_8041c160(r2)
	fmuls f2, f3, f2
	fdivs f1, f2, f1
	fadds f1, f4, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @29
	lfs f1, float_0_8041c144(r2)
	@29:
	lfs f0, float_0p017453_8041c164(r2)
	addi r3, r1, 0x54
	li r4, 0x78
	fmuls f1, f0, f1
	bl PSMTXRotRad
	lfs f1, float_20_8041c168(r2)
	addi r3, r1, 0x84
	lfs f0, 0x0(r30)
	lfs f2, 0x4(r30)
	fadds f1, f1, f0
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	addi r5, r1, 0xf0
	addi r3, r1, 0x84
	addi r4, r1, 0x54
	add r5, r5, r26
	bl PSMTXConcat
	lwz r0, 0x20(r31)
	ori r0, r0, 0x2
	stw r0, 0x20(r31)
	b @30
	@28:
	lwz r4, 0x48(r31)
	lis r0, 0x4330
	stw r0, 0x1e0(r1)
	lis r3, double_to_int_802ef198@ha
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802ef198@l(r3)
	stw r0, 0x1e4(r1)
	lfs f3, float_90_8041c158(r2)
	lfd f0, 0x1e0(r1)
	lfs f1, float_10_8041c15c(r2)
	fsubs f2, f0, f2
	lfs f4, float_270_8041c154(r2)
	lfs f0, float_360_8041c160(r2)
	fmuls f2, f3, f2
	fdivs f1, f2, f1
	fadds f1, f4, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @31
	lfs f1, float_0_8041c144(r2)
	@31:
	lfs f0, float_0p017453_8041c164(r2)
	addi r3, r1, 0x54
	li r4, 0x78
	fmuls f1, f0, f1
	bl PSMTXRotRad
	lfs f1, 0x0(r30)
	addi r3, r1, 0x84
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	addi r5, r1, 0xf0
	addi r3, r1, 0x84
	addi r4, r1, 0x54
	add r5, r5, r26
	bl PSMTXConcat
	@30:
	fcmpo cr0, f31, f30
	lfs f0, float_0_8041c144(r2)
	addi r3, r1, 0x10
	stfsx f0, r3, r24
	cror eq, gt, eq
	bne @32
	lwz r0, 0x48(r31)
	cmpwi r0, 0xa
	blt @32
	li r3, 0x3
	li r0, -0x1
	stw r3, 0x34(r31)
	stw r0, 0x48(r31)
	@32:
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	b @24
	@33:
	mulli r4, r4, 0x14
	lwz r0, 0x84(r31)
	lis r3, kakutable@ha
	lfs f2, float_3p1416_8041c14c(r2)
	addi r30, r1, 0xb4
	lfs f0, float_180_8041c150(r2)
	addi r3, r3, kakutable@l
	slwi r0, r0, 2
	add r3, r3, r4
	add r30, r30, r25
	add r3, r3, r0
	lfs f1, -0x3c(r3)
	mr r3, r30
	fmuls f1, f2, f1
	fdivs f30, f1, f0
	bl GetRingCenter
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	lfs f0, 0xc(r1)
	lfs f2, 0x8(r1)
	fadds f0, f1, f0
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r30)
	fadds f0, f0, f2
	stfs f0, 0x4(r30)
	stfs f2, 0x8(r30)
	lwz r0, 0x0(r27)
	cmpw r29, r0
	bne @34
	lfs f1, float_20_8041c168(r2)
	addi r3, r1, 0xf0
	lfs f0, 0x0(r30)
	add r3, r3, r26
	lfs f2, 0x4(r30)
	fadds f1, f1, f0
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	lwz r0, 0x20(r31)
	ori r0, r0, 0x2
	stw r0, 0x20(r31)
	b @35
	@34:
	addi r3, r1, 0xf0
	lfs f1, 0x0(r30)
	lfs f2, 0x4(r30)
	add r3, r3, r26
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	@35:
	lfs f0, float_0_8041c144(r2)
	addi r3, r1, 0x10
	stfsx f0, r3, r24
	b @24
	@36:
	lwz r0, 0x84(r31)
	mulli r6, r4, 0x14
	lis r5, kakutable@ha
	lwz r4, 0x70(r31)
	slwi r3, r0, 2
	lfs f0, float_0_8041c144(r2)
	addi r0, r5, kakutable@l
	add r5, r0, r6
	subi r0, r3, 0x3c
	lfsx f3, r5, r0
	slwi r3, r4, 2
	subi r0, r3, 0x3c
	fcmpu cr0, f0, f3
	lfsx f1, r5, r0
	bne @37
	lfs f3, float_360_8041c160(r2)
	@37:
	lfs f0, float_3p1416_8041c14c(r2)
	lis r0, 0x4330
	lwz r3, 0x48(r31)
	lis r4, double_to_int_802ef198@ha
	fmuls f1, f0, f1
	lfs f2, float_180_8041c150(r2)
	fmuls f0, f0, f3
	xoris r3, r3, 0x8000
	stw r3, 0x1e4(r1)
	fdivs f1, f1, f2
	stw r0, 0x1e0(r1)
	lfd f4, double_to_int_802ef198@l(r4)
	lfd f3, 0x1e0(r1)
	lfs f5, float_0p2_8041c148(r2)
	fsubs f3, f3, f4
	fdivs f0, f0, f2
	fmadds f30, f5, f3, f1
	fcmpo cr0, f30, f0
	cror eq, gt, eq
	bne @38
	li r0, 0x3
	fmr f30, f0
	stw r0, 0x34(r31)
	li r0, -0x1
	stw r0, 0x48(r31)
	@38:
	addi r30, r1, 0xb4
	add r30, r30, r25
	mr r3, r30
	bl GetRingCenter
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	addi r3, r1, 0xf0
	lfs f0, 0xc(r1)
	add r3, r3, r26
	lfs f2, 0x8(r1)
	fadds f0, f1, f0
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r30)
	fadds f0, f0, f2
	stfs f0, 0x4(r30)
	stfs f2, 0x8(r30)
	lfs f1, 0x0(r30)
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	lfs f0, float_0_8041c144(r2)
	addi r3, r1, 0x10
	stfsx f0, r3, r24
	lwz r0, 0x20(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x20(r31)
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	b @24
	@39:
	lwz r0, 0x70(r31)
	mulli r5, r4, 0x14
	lis r4, kakutable@ha
	lfs f0, float_0_8041c144(r2)
	slwi r3, r0, 2
	addi r0, r4, kakutable@l
	add r7, r0, r5
	subi r0, r3, 0x3c
	lfsx f1, r7, r0
	fcmpu cr0, f0, f1
	bne @40
	lfs f1, float_360_8041c160(r2)
	@40:
	lwz r0, 0x84(r31)
	lis r4, 0x4330
	lfs f3, float_3p1416_8041c14c(r2)
	lis r5, double_to_int_802ef198@ha
	slwi r3, r0, 2
	lfs f2, float_180_8041c150(r2)
	subi r0, r3, 0x3c
	fmuls f1, f3, f1
	lfsx f0, r7, r0
	lwz r6, 0x48(r31)
	fmuls f0, f3, f0
	stw r4, 0x1e0(r1)
	fdivs f1, f1, f2
	xoris r3, r6, 0x8000
	stw r3, 0x1e4(r1)
	lfd f5, double_to_int_802ef198@l(r5)
	lfd f4, 0x1e0(r1)
	lfs f6, float_0p2_8041c148(r2)
	fsubs f3, f4, f5
	fdivs f0, f0, f2
	fnmsubs f30, f6, f3, f1
	fcmpo cr0, f30, f0
	cror eq, lt, eq
	bne @41
	li r0, 0x3
	fmr f30, f0
	stw r0, 0x34(r31)
	li r0, -0x1
	stw r0, 0x48(r31)
	@41:
	addi r30, r1, 0xb4
	add r30, r30, r25
	mr r3, r30
	bl GetRingCenter
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	addi r3, r1, 0xf0
	lfs f0, 0xc(r1)
	add r3, r3, r26
	lfs f2, 0x8(r1)
	fadds f0, f1, f0
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r30)
	fadds f0, f0, f2
	stfs f0, 0x4(r30)
	stfs f2, 0x8(r30)
	lfs f1, 0x0(r30)
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	lfs f0, float_0_8041c144(r2)
	addi r3, r1, 0x10
	stfsx f0, r3, r24
	lwz r0, 0x20(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x20(r31)
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	b @24
	@42:
	lwz r0, 0x20(r31)
	addi r30, r1, 0xb4
	add r30, r30, r25
	ori r0, r0, 0x1
	stw r0, 0x20(r31)
	mr r3, r30
	lwz r0, 0x20(r31)
	ori r0, r0, 0x2
	stw r0, 0x20(r31)
	bl GetRingCenter
	lfs f1, float_0_8041c144(r2)
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	li r3, 0x4
	lfs f0, 0xc(r1)
	li r5, 0xc
	lfs f2, 0x8(r1)
	fadds f0, f1, f0
	lfs f1, float_neg60_8041c16c(r2)
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r30)
	fadds f0, f0, f2
	stfs f0, 0x4(r30)
	stfs f2, 0x8(r30)
	lfs f2, 0x0(r30)
	lwz r4, 0x48(r31)
	bl intplGetValue
	stfs f1, 0x0(r30)
	li r3, 0x4
	lfs f1, float_55_8041c170(r2)
	li r5, 0xc
	lfs f2, 0x4(r30)
	lwz r4, 0x48(r31)
	bl intplGetValue
	stfs f1, 0x4(r30)
	addi r3, r1, 0xf0
	lfs f1, float_20_8041c168(r2)
	add r3, r3, r26
	lfs f0, 0x0(r30)
	lfs f2, 0x4(r30)
	fadds f1, f1, f0
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	lfs f1, float_360_8041c160(r2)
	li r3, 0x0
	lfs f2, float_0_8041c144(r2)
	li r5, 0xc
	lwz r4, 0x48(r31)
	bl intplGetValue
	addi r3, r1, 0x10
	stfsx f1, r3, r24
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	lwz r0, 0x48(r31)
	cmpwi r0, 0xc
	ble @24
	li r0, 0x3
	stw r0, 0x34(r31)
	b @24
	@43:
	lwz r0, 0x20(r31)
	lis r3, kakutable@ha
	addi r30, r1, 0xb4
	lfs f2, float_3p1416_8041c14c(r2)
	ori r0, r0, 0x1
	addi r4, r3, kakutable@l
	stw r0, 0x20(r31)
	add r30, r30, r25
	lfs f0, float_180_8041c150(r2)
	mr r3, r30
	lwz r0, 0x20(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x20(r31)
	lwz r5, 0x8(r27)
	lwz r0, 0x84(r31)
	mulli r5, r5, 0x14
	slwi r0, r0, 2
	add r4, r4, r5
	add r4, r4, r0
	lfs f1, -0x3c(r4)
	fmuls f1, f2, f1
	fdivs f30, f1, f0
	bl GetRingCenter
	fmr f1, f30
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	lis r0, 0x4330
	lfs f0, 0xc(r1)
	lis r3, double_to_int_802ef198@ha
	lfs f4, 0x8(r1)
	fadds f0, f1, f0
	stw r0, 0x1e0(r1)
	lfd f2, double_to_int_802ef198@l(r3)
	lfs f3, float_0p1_8041c174(r2)
	stfs f0, 0x0(r30)
	lfs f0, float_1_8041c178(r2)
	lfs f1, 0x4(r30)
	fadds f1, f1, f4
	stfs f1, 0x4(r30)
	stfs f4, 0x8(r30)
	lwz r0, 0x48(r31)
	xoris r0, r0, 0x8000
	stw r0, 0x1e4(r1)
	lfd f1, 0x1e0(r1)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @44
	li r0, 0x3
	stw r0, 0x34(r31)
	@44:
	fmr f2, f1
	lfs f3, float_1_8041c178(r2)
	addi r3, r1, 0x24
	bl PSMTXScale
	lfs f1, 0x0(r30)
	addi r3, r1, 0x84
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	addi r5, r1, 0xf0
	addi r3, r1, 0x84
	addi r4, r1, 0x24
	add r5, r5, r26
	bl PSMTXConcat
	lfs f0, float_0_8041c144(r2)
	addi r3, r1, 0x10
	stfsx f0, r3, r24
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	@24:
	addi r29, r29, 0x1
	addi r26, r26, 0x30
	addi r25, r25, 0xc
	addi r24, r24, 0x4
	@22:
	lwz r4, 0x8(r27)
	cmpw r29, r4
	blt @23
	lwz r4, 0x4(r28)
	mr r3, r28
	addi r5, r1, 0xf0
	addi r6, r1, 0xb4
	addi r7, r1, 0x10
	bl DrawMainIcon
	bl DrawMenuPartyChangeButton
	bl DrawMenuPinchMark
	psq_l f31, 0x228(r1), 0, 0
	lfd f31, 0x220(r1)
	psq_l f30, 0x218(r1), 0, 0
	lfd f30, 0x210(r1)
	lmw r24, 0x1f0(r1)
	lwz r0, 0x234(r1)
	mtlr r0
	addi r1, r1, 0x230
	blr
}

asm void BattleMenuDisp_ActSelect_End(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	li r0, 0x0
	stw r0, 0x1c78(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_ActSelect_Disp(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl DrawMainMenu
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleMenuDisp_ActSelect_Main(BattleWork* wp) {
	nofralloc
	blr
}

asm void BattleMenuDisp_ActSelect_Init(BattleWork* wp, BattleCursor* cursor, BattleCommandAct* acts, BOOL flag) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r28, r3
	mr r31, r4
	mr r29, r5
	mr r30, r6
	lwz r3, 0x1c78(r3)
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	@1:
	li r3, 0x124
	bl BattleAlloc
	clrlwi. r0, r30, 31
	stw r3, 0x1c78(r28)
	beq @2
	lwz r7, 0x1c78(r28)
	li r3, 0xa
	li r0, 0x0
	li r5, 0x0
	stw r31, 0x0(r7)
	stw r29, 0x4(r7)
	stw r3, 0xc(r7)
	stb r0, 0x14(r7)
	lwz r0, 0x0(r31)
	stw r0, 0x18(r7)
	lwz r6, 0x0(r31)
	b @3
	@4:
	lwz r0, 0x0(r31)
	cmpw r6, r0
	bne @5
	slwi r3, r6, 2
	li r4, 0xa
	addi r0, r3, 0x34
	stwx r4, r7, r0
	b @6
	@5:
	slwi r3, r6, 2
	li r4, 0xb
	addi r0, r3, 0x34
	stwx r4, r7, r0
	@6:
	slwi r0, r6, 2
	li r3, 0x0
	add r4, r7, r0
	stw r3, 0x48(r4)
	lwz r0, 0x8(r31)
	add r3, r0, r5
	subi r0, r3, 0x1
	stw r0, 0x84(r4)
	lwz r0, 0x84(r4)
	lwz r3, 0x8(r31)
	cmpw r0, r3
	blt @7
	subf r0, r3, r0
	stw r0, 0x84(r4)
	@7:
	li r0, 0x0
	addi r6, r6, 0x1
	stw r0, 0x20(r4)
	lwz r0, 0x8(r31)
	cmpw r6, r0
	blt @8
	li r6, 0x0
	@8:
	addi r5, r5, 0x1
	@3:
	lwz r0, 0x8(r31)
	cmpw r5, r0
	blt @4
	b @9
	@2:
	lwz r6, 0x1c78(r28)
	li r5, 0x0
	mr r8, r5
	stw r31, 0x0(r6)
	mr r3, r5
	stw r29, 0x4(r6)
	stw r5, 0xc(r6)
	stb r5, 0x14(r6)
	lwz r0, 0x0(r31)
	stw r0, 0x18(r6)
	lwz r7, 0x0(r31)
	b @10
	@11:
	addi r7, r7, 0x1
	cmpw r7, r0
	blt @12
	li r7, 0x0
	@12:
	slwi r4, r7, 2
	srawi r0, r3, 1
	add r4, r6, r4
	addi r3, r3, 0xa
	stw r5, 0x34(r4)
	addze r0, r0
	stw r0, 0x48(r4)
	stw r8, 0x84(r4)
	addi r8, r8, 0x1
	stw r5, 0x20(r4)
	@10:
	lwz r0, 0x8(r31)
	cmpw r8, r0
	blt @11
	@9:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stmw r18, 0x78(r1)
	lwz r18, _battleWorkPointer(r13)
	mr r29, r4
	mr r30, r3
	mr r21, r5
	lwz r28, 0x1c78(r18)
	mr r22, r6
	lwz r4, 0x420(r18)
	mr r23, r7
	lwz r27, 0x0(r28)
	mr r24, r8
	mr r3, r18
	bl BattleGetUnitPtr
	lwz r0, 0x8(r3)
	cmpwi r0, 0xde
	bne @1
	addi r26, r18, 0x1bb4
	b @2
	@1:
	addi r26, r18, 0x1bc0
	@2:
	lwz r0, 0x8(r27)
	li r3, 0x6
	cmpwi r0, 0x6
	bge @3
	mr r3, r0
	@3:
	lwz r4, 0x4(r27)
	mr r6, r3
	lwz r7, 0x0(r27)
	mr r5, r4
	cmpw r7, r4
	bgt @4
	subi r0, r7, 0x1
	stw r0, 0x4(r27)
	b @5
	@4:
	subi r0, r3, 0x1
	add r0, r4, r0
	cmpw r7, r0
	blt @5
	subf r3, r3, r7
	addi r0, r3, 0x2
	stw r0, 0x4(r27)
	@5:
	lwz r0, 0x4(r27)
	cmpwi r0, 0x0
	bge @6
	li r0, 0x0
	stw r0, 0x4(r27)
	@6:
	lwz r0, 0x8(r27)
	lwz r3, 0x4(r27)
	subf r0, r6, r0
	cmpw r3, r0
	blt @7
	stw r0, 0x4(r27)
	@7:
	lfs f1, float_neg200_8041c17c(r2)
	lfs f0, float_neg100_8041c180(r2)
	stfs f1, 0x0(r30)
	stfs f0, 0x0(r29)
	lwz r4, 0xc(r28)
	cmplwi r4, 0x28
	bgt @8
	lis r3, jumptable_80360DE8@ha
	slwi r0, r4, 2
	addi r3, r3, jumptable_80360DE8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@9:
	li r3, 0x1
	lis r0, 0x4330
	stb r3, 0x14(r28)
	lis r3, double_to_int_802ef198@ha
	addi r4, r3, double_to_int_802ef198@l
	li r8, 0x0
	lwz r7, 0x4(r27)
	li r3, 0x0
	stw r0, 0x70(r1)
	xoris r0, r7, 0x8000
	lfd f1, 0x0(r4)
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	stfs f0, 0x98(r28)
	lwz r4, 0x8(r26)
	mtctr r4
	cmpwi r4, 0x0
	ble @10
	@11:
	addi r0, r3, 0x34
	lwzx r0, r28, r0
	cmpwi r0, 0x1
	beq @12
	cmpwi r0, 0xb
	bne @13
	@12:
	addi r8, r8, 0x1
	@13:
	addi r3, r3, 0x4
	bdnz @11
	@10:
	li r0, 0x7
	li r3, 0x0
	li r7, 0x0
	mtctr r0
	@14:
	addi r0, r3, 0xc0
	lwzx r0, r28, r0
	cmpwi r0, 0x2
	bne @15
	addi r7, r7, 0x1
	@15:
	addi r3, r3, 0x4
	bdnz @14
	cmpw r8, r4
	bne @16
	cmpwi r7, 0x7
	bne @16
	li r0, 0x2
	stw r0, 0xc(r28)
	@16:
	mr r3, r28
	mr r4, r27
	bl DrawSubMenuCommonProcessSub1
	b @8
	@17:
	li r3, 0x1
	lis r0, 0x4330
	stb r3, 0x14(r28)
	lis r3, double_to_int_802ef198@ha
	addi r7, r3, double_to_int_802ef198@l
	mr r4, r27
	lwz r8, 0x4(r27)
	mr r3, r28
	stw r0, 0x70(r1)
	xoris r0, r8, 0x8000
	lfd f1, 0x0(r7)
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	stfs f0, 0x98(r28)
	bl DrawSubMenuCommonProcessSub1
	b @8
	@18:
	cmpwi r4, 0xa
	beq @19
	cmpwi r4, 0x14
	bne @20
	@19:
	li r0, 0x1
	stb r0, 0x14(r28)
	@20:
	li r0, 0x7
	li r4, 0x0
	li r3, 0x0
	mtctr r0
	@21:
	addi r0, r3, 0xc0
	lwzx r0, r28, r0
	cmpwi r0, 0x2
	bne @22
	addi r4, r4, 0x1
	@22:
	addi r3, r3, 0x4
	bdnz @21
	cmpwi r4, 0x7
	bne @23
	li r3, 0x2
	lis r0, 0x4330
	stw r3, 0xc(r28)
	lis r3, double_to_int_802ef198@ha
	lfd f1, double_to_int_802ef198@l(r3)
	lwz r4, 0x4(r27)
	stw r0, 0x70(r1)
	xoris r0, r4, 0x8000
	stw r0, 0x74(r1)
	lfd f0, 0x70(r1)
	fsubs f0, f0, f1
	stfs f0, 0x98(r28)
	@23:
	mr r3, r28
	mr r4, r27
	bl DrawSubMenuCommonProcessSub1
	@8:
	li r29, 0x0
	li r20, 0x0
	stw r29, 0x1c(r28)
	li r19, 0x0
	li r18, 0x0
	b @24
	@25:
	add r31, r28, r18
	lwz r0, 0x34(r31)
	cmpwi r0, 0xa
	beq @26
	bge @27
	cmpwi r0, 0x1
	beq @28
	bge @29
	cmpwi r0, 0x0
	bge @30
	b @29
	@27:
	cmpwi r0, 0xc
	bge @29
	b @31
	@30:
	lwz r0, 0x20(r31)
	add r30, r22, r19
	mr r3, r30
	ori r0, r0, 0x1
	stw r0, 0x20(r31)
	lwz r0, 0x20(r31)
	ori r0, r0, 0x2
	stw r0, 0x20(r31)
	bl GetRingCenter
	lfs f1, 0x0(r30)
	li r3, 0x4
	lfs f2, float_neg60_8041c16c(r2)
	li r5, 0xc
	lwz r4, 0x48(r31)
	bl intplGetValue
	stfs f1, 0x0(r30)
	li r3, 0x4
	lfs f2, float_55_8041c170(r2)
	li r5, 0xc
	lfs f1, 0x4(r30)
	lwz r4, 0x48(r31)
	bl intplGetValue
	stfs f1, 0x4(r30)
	add r3, r21, r20
	lfs f1, float_20_8041c168(r2)
	lfs f0, 0x0(r30)
	lfs f2, 0x4(r30)
	fadds f1, f1, f0
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	lfs f1, float_0_8041c144(r2)
	li r3, 0x0
	lfs f2, float_360_8041c160(r2)
	li r5, 0xc
	lwz r4, 0x48(r31)
	bl intplGetValue
	stfsx f1, r23, r18
	lfs f0, float_360_8041c160(r2)
	lfsx f1, r23, r18
	fcmpo cr0, f1, f0
	ble @32
	fsubs f0, f1, f0
	stfsx f0, r23, r18
	@32:
	lwz r0, 0x48(r31)
	cmpwi r0, 0x3
	blt @33
	li r0, 0x1
	stw r0, 0x1c(r28)
	@33:
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	lwz r0, 0x48(r31)
	cmpwi r0, 0xc
	ble @29
	li r0, 0x1
	stw r0, 0x34(r31)
	b @29
	@28:
	lwz r0, 0x20(r31)
	add r3, r21, r20
	lfs f1, float_neg40_8041c184(r2)
	ori r0, r0, 0x1
	lfs f2, float_55_8041c170(r2)
	stw r0, 0x20(r31)
	lfs f3, float_0_8041c144(r2)
	lwz r0, 0x20(r31)
	ori r0, r0, 0x2
	stw r0, 0x20(r31)
	bl PSMTXTrans
	lfs f0, float_360_8041c160(r2)
	li r0, 0x1
	stfsx f0, r23, r18
	stw r0, 0x1c(r28)
	b @29
	@26:
	lwz r0, 0x20(r31)
	lis r3, kakutable@ha
	add r30, r22, r19
	lfs f2, float_3p1416_8041c14c(r2)
	ori r0, r0, 0x1
	addi r4, r3, kakutable@l
	stw r0, 0x20(r31)
	mr r3, r30
	lfs f0, float_180_8041c150(r2)
	lwz r0, 0x20(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x20(r31)
	lwz r5, 0x8(r26)
	lwz r0, 0x84(r31)
	mulli r5, r5, 0x14
	slwi r0, r0, 2
	add r4, r4, r5
	add r4, r4, r0
	lfs f1, -0x3c(r4)
	fmuls f1, f2, f1
	fdivs f31, f1, f0
	bl GetRingCenter
	fmr f1, f31
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl GetRingOffset
	lfs f1, 0x0(r30)
	lis r0, 0x4330
	lfs f0, 0xc(r1)
	lis r3, double_to_int_802ef198@ha
	stw r0, 0x70(r1)
	fadds f0, f1, f0
	lfd f3, double_to_int_802ef198@l(r3)
	lfs f4, float_0p1_8041c174(r2)
	lfs f1, float_1_8041c178(r2)
	stfs f0, 0x0(r30)
	lfs f0, float_0_8041c144(r2)
	lfs f5, 0x4(r30)
	lfs f2, 0x8(r1)
	fadds f2, f5, f2
	stfs f2, 0x4(r30)
	lfs f2, 0x8(r1)
	stfs f2, 0x8(r30)
	lwz r0, 0x48(r31)
	xoris r0, r0, 0x8000
	stw r0, 0x74(r1)
	lfd f2, 0x70(r1)
	fsubs f2, f2, f3
	fnmsubs f1, f4, f2, f1
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @34
	li r0, 0xb
	stw r0, 0x34(r31)
	@34:
	fmr f2, f1
	lfs f3, float_1_8041c178(r2)
	addi r3, r1, 0x10
	bl PSMTXScale
	lfs f1, 0x0(r30)
	addi r3, r1, 0x40
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl PSMTXTrans
	addi r3, r1, 0x40
	addi r4, r1, 0x10
	add r5, r21, r20
	bl PSMTXConcat
	lfs f0, float_0_8041c144(r2)
	stfsx f0, r23, r18
	lwz r3, 0x48(r31)
	addi r0, r3, 0x1
	stw r0, 0x48(r31)
	b @29
	@31:
	lwz r0, 0x20(r31)
	clrrwi r0, r0, 1
	stw r0, 0x20(r31)
	@29:
	addi r29, r29, 0x1
	addi r20, r20, 0x30
	addi r19, r19, 0xc
	addi r18, r18, 0x4
	@24:
	lwz r0, 0x8(r26)
	cmpw r29, r0
	blt @25
	li r31, 0x0
	li r21, 0x0
	li r22, 0x0
	@35:
	add r30, r28, r22
	lwz r4, 0xc0(r30)
	cmplwi r4, 0x28
	bgt @36
	lis r3, jumptable_80360D44@ha
	slwi r0, r4, 2
	addi r3, r3, jumptable_80360D44@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@37:
	lwz r4, 0xa4(r30)
	addi r0, r31, 0x114
	li r3, 0xff
	clrrwi r4, r4, 1
	stw r4, 0xa4(r30)
	stbx r3, r28, r0
	b @36
	@38:
	lwz r4, 0xa4(r30)
	addi r0, r31, 0x114
	li r3, 0xff
	clrrwi r4, r4, 1
	stw r4, 0xa4(r30)
	stbx r3, r28, r0
	lwz r4, 0xdc(r30)
	cmpwi r4, 0x0
	blt @39
	cmpwi r31, 0x6
	beq @39
	lfs f1, float_90_8041c158(r2)
	li r3, 0x0
	lfs f2, float_0_8041c144(r2)
	li r5, 0xc
	bl intplGetValue
	lwz r0, 0xa4(r30)
	add r3, r24, r21
	lfs f0, float_0p017453_8041c164(r2)
	li r4, 0x79
	ori r0, r0, 0x1
	fmuls f1, f0, f1
	stw r0, 0xa4(r30)
	bl PSMTXRotRad
	@39:
	lwz r3, 0xdc(r30)
	addi r0, r3, 0x1
	stw r0, 0xdc(r30)
	lwz r0, 0xdc(r30)
	cmpwi r0, 0xc
	ble @36
	li r0, 0x2
	stw r0, 0xc0(r30)
	b @36
	@40:
	cmpwi r31, 0x6
	addi r0, r31, 0x114
	li r3, 0xff
	stbx r3, r28, r0
	beq @41
	lwz r0, 0xa4(r30)
	add r3, r24, r21
	ori r0, r0, 0x1
	stw r0, 0xa4(r30)
	bl PSMTXIdentity
	b @36
	@41:
	lwz r0, 0xa4(r30)
	clrrwi r0, r0, 1
	stw r0, 0xa4(r30)
	b @36
	@42:
	cmpwi r4, 0xa
	beq @43
	cmpwi r4, 0x14
	bne @44
	@43:
	li r25, 0xc
	@44:
	cmpwi r4, 0x1e
	beq @45
	cmpwi r4, 0x28
	bne @46
	@45:
	lwz r3, 0x8(r27)
	subi r0, r3, 0x6
	srawi r0, r0, 1
	addze r3, r0
	addi r25, r3, 0xc
	@46:
	lwz r0, 0xa4(r30)
	add r3, r24, r21
	ori r0, r0, 0x1
	stw r0, 0xa4(r30)
	bl PSMTXIdentity
	lfs f1, 0x9c(r28)
	mr r5, r25
	lfs f2, 0xa0(r28)
	li r3, 0x4
	lwz r4, 0xdc(r30)
	bl intplGetValue
	stfs f1, 0x98(r28)
	lwz r3, 0xdc(r30)
	addi r0, r3, 0x1
	stw r0, 0xdc(r30)
	lwz r0, 0xdc(r30)
	cmpw r0, r25
	ble @36
	li r3, 0x2
	li r0, 0x0
	stw r3, 0xc0(r30)
	stw r0, 0xdc(r30)
	@36:
	addi r31, r31, 0x1
	addi r22, r22, 0x4
	cmpwi r31, 0x7
	addi r21, r21, 0x30
	blt @35
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	lmw r18, 0x78(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm void DrawSubMenuCommonProcessSub1(BattleSubMenu* menu, BattleCursor* cursor, s32 prev, s32 key) {
	nofralloc
	cmpwi r6, 0x6
	stwu r1, -0x20(r1)
	bne @1
	lwz r7, 0x8(r4)
	cmpwi r7, 0x6
	ble @1
	subi r0, r7, 0x6
	cmpw r5, r0
	bne @1
	lwz r0, 0x4(r4)
	cmpwi r0, 0x0
	bne @1
	lwz r0, 0x0(r4)
	cmpwi r0, 0x1
	beq @1
	li r8, 0x1e
	lis r6, double_to_int_802ef198@ha
	stw r8, 0xc(r3)
	li r7, 0x0
	lis r5, 0x4330
	lfd f2, double_to_int_802ef198@l(r6)
	stw r7, 0x10(r3)
	li r0, 0x7
	lfs f0, float_0_8041c144(r2)
	lwz r6, 0x8(r4)
	mr r4, r7
	stw r5, 0x8(r1)
	subi r5, r6, 0x6
	xoris r5, r5, 0x8000
	stw r5, 0xc(r1)
	lfd f1, 0x8(r1)
	fsubs f1, f1, f2
	stfs f1, 0x9c(r3)
	stfs f0, 0xa0(r3)
	mtctr r0
	@2:
	add r5, r3, r4
	addi r4, r4, 0x4
	stw r8, 0xc0(r5)
	stw r7, 0xdc(r5)
	bdnz @2
	b @3
	@1:
	cmpwi r6, 0x6
	bne @4
	lwz r7, 0x8(r4)
	cmpwi r7, 0x6
	ble @4
	cmpwi r5, 0x0
	bne @4
	lwz r6, 0x4(r4)
	subi r0, r7, 0x6
	cmpw r6, r0
	bne @4
	lwz r0, 0x0(r4)
	cmpwi r0, 0x5
	beq @4
	li r8, 0x28
	lis r6, 0x4330
	stw r8, 0xc(r3)
	li r7, 0x0
	lis r5, double_to_int_802ef198@ha
	lfs f0, float_0_8041c144(r2)
	stw r7, 0x10(r3)
	li r0, 0x7
	lfd f1, double_to_int_802ef198@l(r5)
	li r5, 0x0
	stfs f0, 0x9c(r3)
	lwz r4, 0x8(r4)
	stw r6, 0x8(r1)
	subi r4, r4, 0x6
	xoris r4, r4, 0x8000
	stw r4, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	stfs f0, 0xa0(r3)
	mtctr r0
	@5:
	add r4, r3, r5
	addi r5, r5, 0x4
	stw r8, 0xc0(r4)
	stw r7, 0xdc(r4)
	bdnz @5
	b @3
	@4:
	lwz r0, 0x4(r4)
	addi r7, r5, 0x1
	cmpw r0, r7
	bne @6
	lis r6, 0x4330
	xoris r0, r5, 0x8000
	stw r0, 0xc(r1)
	xoris r5, r7, 0x8000
	lis r4, double_to_int_802ef198@ha
	li r8, 0xa
	stw r6, 0x8(r1)
	li r7, 0x0
	lfd f2, double_to_int_802ef198@l(r4)
	li r0, 0x7
	lfd f0, 0x8(r1)
	li r4, 0x0
	stw r8, 0xc(r3)
	fsubs f1, f0, f2
	stw r7, 0x10(r3)
	stw r5, 0x14(r1)
	stw r6, 0x10(r1)
	lfd f0, 0x10(r1)
	stfs f1, 0x9c(r3)
	fsubs f0, f0, f2
	stfs f0, 0xa0(r3)
	mtctr r0
	@7:
	add r5, r3, r4
	addi r4, r4, 0x4
	stw r8, 0xc0(r5)
	stw r7, 0xdc(r5)
	bdnz @7
	b @3
	@6:
	subi r7, r5, 0x1
	cmpw r0, r7
	bne @3
	lis r6, 0x4330
	xoris r0, r5, 0x8000
	stw r0, 0x14(r1)
	xoris r5, r7, 0x8000
	lis r4, double_to_int_802ef198@ha
	li r8, 0x14
	stw r6, 0x10(r1)
	li r7, 0x0
	lfd f2, double_to_int_802ef198@l(r4)
	li r0, 0x7
	lfd f0, 0x10(r1)
	li r4, 0x0
	stw r8, 0xc(r3)
	fsubs f1, f0, f2
	stw r7, 0x10(r3)
	stw r5, 0xc(r1)
	stw r6, 0x8(r1)
	lfd f0, 0x8(r1)
	stfs f1, 0x9c(r3)
	fsubs f0, f0, f2
	stfs f0, 0xa0(r3)
	mtctr r0
	@8:
	add r5, r3, r4
	addi r4, r4, 0x4
	stw r8, 0xc0(r5)
	stw r7, 0xdc(r5)
	bdnz @8
	@3:
	addi r1, r1, 0x20
	blr
}

asm void InitSubMenuCommonProcess3(BattleSubMenu* menu, BattleCursor* cursor) {
	nofralloc
	lwz r8, 0x0(r4)
	li r7, 0x0
	b @1
	@2:
	addi r8, r8, 0x1
	cmpw r8, r0
	blt @3
	li r8, 0x0
	@3:
	slwi r0, r8, 2
	li r5, 0x0
	add r6, r3, r0
	stw r5, 0x48(r6)
	stw r7, 0x84(r6)
	stw r5, 0x20(r6)
	lwz r0, 0x20(r6)
	ori r0, r0, 0x1
	stw r0, 0x20(r6)
	lwz r5, 0x8(r4)
	subi r0, r5, 0x1
	cmpw r7, r0
	bne @4
	li r0, 0x1
	stw r0, 0x34(r6)
	b @5
	@4:
	li r0, 0xb
	stw r0, 0x34(r6)
	@5:
	addi r7, r7, 0x1
	@1:
	lwz r0, 0x8(r4)
	cmpw r7, r0
	blt @2
	blr
}

asm void InitSubMenuCommonProcess2(BattleSubMenu* menu, BattleCursor* cursor) {
	nofralloc
	lwz r9, 0x0(r4)
	li r8, 0x0
	li r6, 0x0
	li r0, 0xa
	b @1
	@2:
	addi r9, r9, 0x1
	cmpw r9, r5
	blt @3
	li r9, 0x0
	@3:
	slwi r5, r9, 2
	add r7, r3, r5
	stw r6, 0x48(r7)
	stw r8, 0x84(r7)
	stw r6, 0x20(r7)
	lwz r5, 0x20(r7)
	ori r5, r5, 0x1
	stw r5, 0x20(r7)
	lwz r5, 0x8(r4)
	subi r5, r5, 0x1
	cmpw r8, r5
	bne @4
	stw r6, 0x34(r7)
	b @5
	@4:
	stw r0, 0x34(r7)
	@5:
	addi r8, r8, 0x1
	@1:
	lwz r5, 0x8(r4)
	cmpw r8, r5
	blt @2
	blr
}

asm void InitSubMenuCommonProcess(BattleSubMenu** out, BattleCursor** mainCursor, BattleCursor* cursor) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r31, r3
	mr r28, r4
	mr r29, r5
	lwz r6, _battleWorkPointer(r13)
	lwz r3, 0x1c78(r6)
	mr r30, r6
	cmplwi r3, 0x0
	beq @1
	bl BattleFree
	@1:
	li r3, 0x124
	bl BattleAlloc
	stw r3, 0x1c78(r30)
	li r0, 0x0
	mr r3, r30
	lwz r4, 0x1c78(r30)
	stw r4, 0x0(r31)
	lwz r4, 0x0(r31)
	stw r29, 0x0(r4)
	lwz r4, 0x0(r31)
	stw r0, 0xc(r4)
	lwz r4, 0x0(r31)
	stw r0, 0x10(r4)
	lwz r4, 0x0(r31)
	stb r0, 0x14(r4)
	lwz r0, 0x0(r29)
	lwz r4, 0x0(r31)
	stw r0, 0x18(r4)
	lwz r4, 0x420(r30)
	bl BattleGetUnitPtr
	lwz r0, 0x8(r3)
	cmpwi r0, 0xde
	bne @2
	addi r0, r30, 0x1bb4
	stw r0, 0x0(r28)
	b @3
	@2:
	addi r0, r30, 0x1bc0
	stw r0, 0x0(r28)
	@3:
	lfs f0, float_0_8041c144(r2)
	li r3, 0x0
	lwz r4, 0x0(r31)
	li r0, 0x7
	mr r10, r3
	mr r5, r3
	stfs f0, 0x98(r4)
	li r11, 0x0
	li r9, 0x1
	mtctr r0
	@4:
	lwz r4, 0x0(r31)
	addi r0, r3, 0xa4
	neg r7, r11
	addi r6, r3, 0xc0
	stwx r10, r4, r0
	addi r4, r3, 0xdc
	addi r0, r3, 0xf8
	addi r11, r11, 0x1
	lwz r8, 0x0(r31)
	addi r3, r3, 0x4
	stwx r9, r8, r6
	lwz r6, 0x0(r31)
	stwx r7, r6, r4
	lwz r4, 0x0(r31)
	stwx r5, r4, r0
	bdnz @4
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void DrawMenuCursorAndScrollArrow(Vec* v) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stmw r29, 0x24(r1)
	lwz r4, _battleWorkPointer(r13)
	mr r31, r3
	lfs f1, float_0_8041c144(r2)
	li r3, 0x4
	lwz r30, 0x1c78(r4)
	li r5, 0x6
	lfs f2, float_10_8041c15c(r2)
	lwz r29, 0x0(r30)
	lwz r4, 0x11c(r30)
	bl intplGetValue
	lwz r3, 0x11c(r30)
	fmr f31, f1
	addi r0, r3, 0x1
	stw r0, 0x11c(r30)
	lwz r0, 0x11c(r30)
	cmpwi r0, 0xc
	blt @1
	li r0, 0x0
	stw r0, 0x11c(r30)
	@1:
	lwz r0, 0x4(r29)
	cmpwi r0, 0x0
	ble @2
	lfs f2, float_15_8041c18c(r2)
	addi r3, r1, 0x8
	lfs f1, 0x4(r31)
	li r4, 0x10
	lfs f0, float_0_8041c144(r2)
	li r5, 0x1b5
	fadds f2, f2, f1
	lfs f3, float_155_8041c188(r2)
	lfs f1, 0x0(r31)
	stfs f0, 0x10(r1)
	fadds f3, f3, f1
	lfs f1, float_0p75_8041c190(r2)
	fadds f0, f2, f31
	stfs f3, 0x8(r1)
	stfs f0, 0xc(r1)
	bl iconDispGx
	@2:
	lwz r3, 0x8(r29)
	lwz r4, 0x4(r29)
	subi r0, r3, 0x6
	cmpw r4, r0
	bge @3
	lfs f2, float_20_8041c168(r2)
	addi r3, r1, 0x8
	lfs f1, 0x4(r31)
	li r4, 0x10
	lfs f0, float_0_8041c144(r2)
	li r5, 0x1b6
	fadds f2, f2, f1
	lfs f1, float_164_8041c194(r2)
	lfs f4, float_155_8041c188(r2)
	lfs f3, 0x0(r31)
	fsubs f2, f2, f1
	stfs f0, 0x10(r1)
	fadds f3, f4, f3
	lfs f1, float_0p75_8041c190(r2)
	fsubs f0, f2, f31
	stfs f3, 0x8(r1)
	stfs f0, 0xc(r1)
	bl iconDispGx
	@3:
	lwz r3, 0x4(r29)
	lwz r0, 0x0(r29)
	subf. r0, r3, r0
	bge @4
	li r0, 0x0
	@4:
	cmpwi r0, 0x6
	blt @5
	li r0, 0x5
	@5:
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x1c(r1)
	lis r4, double_to_int_802ef198@ha
	lfd f1, double_to_int_802ef198@l(r4)
	addi r3, r1, 0x8
	stw r0, 0x18(r1)
	li r4, 0x14
	lfs f4, 0x0(r31)
	li r5, 0x1f0
	lfd f0, 0x18(r1)
	lfs f3, float_24_8041c198(r2)
	fsubs f2, f0, f1
	lfs f1, 0x4(r31)
	lfs f0, float_0_8041c144(r2)
	stfs f4, 0x8(r1)
	fnmsubs f2, f3, f2, f1
	lfs f1, float_1_8041c178(r2)
	stfs f0, 0x10(r1)
	stfs f2, 0xc(r1)
	bl iconDispGx
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	lmw r29, 0x24(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void DrawMenuHelpWin(const char* msg, f32 x, f32 y) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stw r31, 0xdc(r1)
	lwz r0, dat_8041c140(r2)
	mr r31, r3
	fmr f31, f1
	lfs f3, float_400_8041c19c(r2)
	fmr f30, f2
	stw r0, 0x8(r1)
	lfs f4, float_50_8041c1a0(r2)
	addi r4, r1, 0x8
	lfs f5, float_10_8041c15c(r2)
	li r3, 0x0
	bl windowDispGX_Waku_col
	bl FontDrawStart
	li r3, 0x0
	bl FontDrawColorIDX
	lfs f1, float_0p8_8041c1a4(r2)
	bl FontDrawScale
	mr r3, r31
	bl msgSearch
	mr. r31, r3
	beq @1
	li r3, 0x0
	li r0, 0x4
	mr r5, r3
	addi r4, r1, 0xc
	mtctr r0
	@2:
	stbx r5, r4, r3
	addi r3, r3, 0x30
	bdnz @2
	mr r5, r31
	addi r6, r1, 0xc
	li r3, 0x0
	@3:
	lbz r0, 0x0(r5)
	cmpwi r0, 0x3c
	bne @4
	@5:
	lbzu r0, 0x1(r5)
	cmpwi r0, 0x3e
	bne @5
	addi r5, r5, 0x1
	@4:
	lbz r4, 0x0(r5)
	extsb. r0, r4
	bne @6
	li r0, 0x0
	stb r0, 0x0(r6)
	b @7
	@6:
	extsb r0, r4
	cmpwi r0, 0xa
	bne @8
	li r0, 0x0
	addi r3, r3, 0x30
	stb r0, 0x0(r6)
	addi r6, r1, 0xc
	add r6, r6, r3
	addi r5, r5, 0x1
	b @3
	@8:
	stb r4, 0x0(r6)
	addi r5, r5, 0x1
	addi r6, r6, 0x1
	b @3
	@7:
	lbz r0, 0xc(r1)
	extsb. r0, r0
	beq @9
	lfs f1, float_0p8_8041c1a4(r2)
	bl FontDrawScale
	@9:
	lfs f1, float_20_8041c168(r2)
	addi r3, r1, 0xc
	lfs f0, float_4_8041c1a8(r2)
	fadds f31, f1, f31
	fsubs f2, f30, f0
	fmr f1, f31
	bl FontDrawString
	lbz r0, 0x3c(r1)
	addi r31, r1, 0x3c
	extsb. r0, r0
	beq @10
	lfs f1, float_0p8_8041c1a4(r2)
	bl FontDrawScale
	@10:
	lfs f0, float_28_8041c1ac(r2)
	fmr f1, f31
	mr r3, r31
	fsubs f2, f30, f0
	bl FontDrawString
	lbz r0, 0x6c(r1)
	addi r31, r1, 0x6c
	extsb. r0, r0
	beq @11
	lfs f1, float_0p8_8041c1a4(r2)
	bl FontDrawScale
	@11:
	lfs f0, float_52_8041c1b0(r2)
	fmr f1, f31
	mr r3, r31
	fsubs f2, f30, f0
	bl FontDrawString
	b @12
	@1:
	lfs f1, float_10_8041c15c(r2)
	lis r3, str_802EF1A0@ha
	lfs f0, float_4_8041c1a8(r2)
	addi r3, r3, str_802EF1A0@l
	fadds f1, f1, f31
	fsubs f2, f30, f0
	bl FontDrawString
	@12:
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	lwz r0, 0x104(r1)
	lwz r31, 0xdc(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void DrawMenuPinchMark(void) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	li r3, 0x8
	stw r0, 0xc4(r1)
	stmw r25, 0xa4(r1)
	lwz r29, _battleWorkPointer(r13)
	bl camGetPtr
	mr r30, r3
	bl btlDispGXInit2D
	mr r3, r29
	bl BattleGetMarioPtr
	mr r31, r3
	lha r3, 0x10c(r3)
	extsh. r0, r3
	ble @1
	lha r0, 0x108(r31)
	cmpw r3, r0
	bge @1
	cmpwi r3, 0x5
	bgt @1
	cmpwi r3, 0x1
	bne @2
	lwz r5, gp(r13)
	li r3, 0x32
	lwz r4, 0x1c(r5)
	lwz r5, 0x16c(r5)
	divwu r0, r4, r3
	subic r5, r5, 0x1
	subfe r5, r5, r5
	addi r5, r5, 0x9
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplwi r0, 0x18
	bgt @3
	li r25, 0xff
	li r26, 0xe9
	li r27, 0x40
	li r28, 0xff
	b @4
	@3:
	li r25, 0xe9
	li r26, 0x52
	li r27, 0x2f
	li r28, 0xff
	b @4
	@2:
	lwz r3, gp(r13)
	li r25, 0xff
	li r26, 0xe9
	li r27, 0x40
	lwz r0, 0x16c(r3)
	li r28, 0xff
	subic r0, r0, 0x1
	subfe r3, r0, r0
	addi r0, r3, 0x7
	mr r5, r0
	@4:
	addis r3, r29, 0x1
	addi r4, r1, 0x20
	lwz r3, 0x63dc(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r31, 0x3c
	addi r4, r1, 0x14
	bl btlGetScreenPoint
	lfs f3, 0x14(r1)
	addi r3, r1, 0x70
	lfs f1, float_20_8041c168(r2)
	lfs f2, float_60_8041c1b4(r2)
	lfs f0, 0x18(r1)
	fsubs f1, f3, f1
	lfs f3, float_0_8041c144(r2)
	fadds f2, f2, f0
	bl PSMTXTrans
	addi r3, r30, 0x11c
	addi r4, r1, 0x70
	addi r5, r1, 0x40
	bl PSMTXConcat
	addi r3, r1, 0x40
	li r4, 0x0
	bl GXLoadPosMtxImm
	lfs f1, float_neg28_8041c1b8(r2)
	mr r3, r25
	lfs f2, float_12_8041c1bc(r2)
	mr r4, r26
	lfs f3, float_28_8041c1ac(r2)
	mr r5, r27
	lfs f4, float_neg12_8041c1c0(r2)
	mr r6, r28
	bl btlDispGXQuads2D
	@1:
	mr r3, r29
	bl BattleGetPartyPtr
	mr. r31, r3
	beq @5
	lha r3, 0x10c(r31)
	extsh. r0, r3
	ble @5
	lha r0, 0x108(r31)
	cmpw r3, r0
	bge @5
	cmpwi r3, 0x5
	bgt @5
	cmpwi r3, 0x1
	bne @6
	lwz r5, gp(r13)
	li r3, 0x32
	lwz r4, 0x1c(r5)
	lwz r5, 0x16c(r5)
	divwu r0, r4, r3
	subic r5, r5, 0x1
	subfe r5, r5, r5
	addi r5, r5, 0x9
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplwi r0, 0x18
	bgt @7
	li r28, 0xff
	li r27, 0xe9
	mr r25, r28
	li r26, 0x40
	b @8
	@7:
	li r28, 0xe9
	li r27, 0x52
	li r26, 0x2f
	li r25, 0xff
	b @8
	@6:
	lwz r3, gp(r13)
	li r28, 0xff
	mr r25, r28
	li r27, 0xe9
	lwz r0, 0x16c(r3)
	li r26, 0x40
	subic r0, r0, 0x1
	subfe r3, r0, r0
	addi r5, r3, 0x7
	@8:
	addis r3, r29, 0x1
	addi r4, r1, 0x20
	lwz r3, 0x63dc(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x20
	li r4, 0x0
	bl GXLoadTexObj
	addi r3, r31, 0x3c
	addi r4, r1, 0x8
	bl btlGetScreenPoint
	lfs f3, 0x8(r1)
	addi r3, r1, 0x70
	lfs f1, float_20_8041c168(r2)
	lfs f2, float_60_8041c1b4(r2)
	lfs f0, 0xc(r1)
	fsubs f1, f3, f1
	lfs f3, float_0_8041c144(r2)
	fadds f2, f2, f0
	bl PSMTXTrans
	addi r3, r30, 0x11c
	addi r4, r1, 0x70
	addi r5, r1, 0x40
	bl PSMTXConcat
	addi r3, r1, 0x40
	li r4, 0x0
	bl GXLoadPosMtxImm
	lfs f1, float_neg28_8041c1b8(r2)
	mr r3, r28
	lfs f2, float_12_8041c1bc(r2)
	mr r4, r27
	lfs f3, float_28_8041c1ac(r2)
	mr r5, r26
	lfs f4, float_neg12_8041c1c0(r2)
	mr r6, r25
	bl btlDispGXQuads2D
	@5:
	lmw r25, 0xa4(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm void DrawMenuPartyChangeButton_Sub(u32 id, f32 x, f32 y, f32 angle) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	lfs f0, float_0p017453_8041c164(r2)
	fmr f30, f1
	mr r31, r3
	fmr f31, f2
	fmuls f1, f0, f3
	addi r3, r1, 0xc
	li r4, 0x79
	bl PSMTXRotRad
	fmr f1, f30
	addi r3, r1, 0xc
	fmr f2, f31
	lfs f3, float_0_8041c144(r2)
	mr r4, r3
	bl PSMTXTransApply
	lwz r0, dat_8041c13c(r2)
	mr r4, r31
	addi r3, r1, 0xc
	addi r5, r1, 0x8
	stw r0, 0x8(r1)
	li r6, 0x0
	bl btlDispTexPlane2
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	lwz r0, 0x74(r1)
	lwz r31, 0x4c(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void DrawMenuPartyChangeButton(void) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stmw r28, 0x30(r1)
	lwz r4, _battleWorkPointer(r13)
	li r3, 0x8
	lwz r28, 0x1c78(r4)
	mr r29, r4
	bl camGetPtr
	mr r3, r29
	bl BattleGetMarioPtr
	mr r30, r3
	mr r3, r29
	bl BattleGetPartyPtr
	mr. r31, r3
	bne @1
	addi r3, r1, 0x14
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	li r7, 0x0
	bl BattleAudience_GetItemOn
	lwz r0, 0x14(r1)
	cmpwi r0, -0x1
	beq @2
	lfs f1, 0x120(r28)
	lfs f0, float_0_8041c144(r2)
	fcmpo cr0, f1, f0
	ble @3
	lfs f0, float_5_8041c1c4(r2)
	fsubs f0, f1, f0
	stfs f0, 0x120(r28)
	b @4
	@3:
	stfs f0, 0x120(r28)
	@4:
	addi r3, r30, 0x3c
	addi r4, r1, 0x24
	bl btlGetScreenPoint
	lfs f2, 0x28(r1)
	li r3, 0x5
	lfs f0, float_20_8041c168(r2)
	lfs f1, 0x24(r1)
	fsubs f2, f2, f0
	lfs f3, 0x120(r28)
	bl DrawMenuPartyChangeButton_Sub
	b @5
	@2:
	lfs f0, float_90_8041c158(r2)
	stfs f0, 0x120(r28)
	b @5
	@1:
	addi r3, r30, 0x3c
	addi r4, r1, 0x24
	bl btlGetScreenPoint
	addi r3, r31, 0x3c
	addi r4, r1, 0x18
	bl btlGetScreenPoint
	lfs f2, 0x24(r1)
	addi r3, r1, 0x14
	lfs f1, 0x18(r1)
	addi r4, r1, 0x10
	lfs f0, float_0p5_8041c1c8(r2)
	addi r5, r1, 0xc
	fadds f1, f2, f1
	lfs f30, 0x28(r1)
	addi r6, r1, 0x8
	li r7, 0x0
	fmuls f31, f1, f0
	bl BattleAudience_GetItemOn
	lwz r0, 0x14(r1)
	cmpwi r0, -0x1
	beq @6
	lfs f1, float_90_8041c158(r2)
	lfs f0, 0x120(r28)
	fcmpu cr0, f1, f0
	bne @7
	lis r3, str_802EF1BC@ha
	addi r3, r3, str_802EF1BC@l
	bl psndSFXOn
	@7:
	lfs f1, 0x120(r28)
	lfs f0, float_0_8041c144(r2)
	fcmpo cr0, f1, f0
	ble @8
	lfs f0, float_5_8041c1c4(r2)
	fsubs f0, f1, f0
	stfs f0, 0x120(r28)
	b @9
	@8:
	stfs f0, 0x120(r28)
	@9:
	lfs f0, float_20_8041c168(r2)
	fmr f1, f31
	lfs f3, 0x120(r28)
	li r3, 0x5
	fsubs f2, f30, f0
	bl DrawMenuPartyChangeButton_Sub
	b @5
	@6:
	lfs f0, float_90_8041c158(r2)
	mr r3, r29
	stfs f0, 0x120(r28)
	bl BattleCommandCheckChangePositionEnable
	cmpwi r3, 0x0
	beq @5
	lfs f0, float_20_8041c168(r2)
	fmr f1, f31
	lfs f3, float_0_8041c144(r2)
	li r3, 0x4
	fsubs f2, f30, f0
	bl DrawMenuPartyChangeButton_Sub
	@5:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	lmw r28, 0x30(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void DrawSubIconSub(BattleSubMenu* menu, s32 i, Mtx m, s32 enabled, s32 icon, const char* name, s32 cost, s32 p34, void* party, s32 y) {
	nofralloc
	stwu r1, -0x1d0(r1)
	mflr r0
	stw r0, 0x1d4(r1)
	stfd f31, 0x1c0(r1)
	psq_st f31, 0x1c8(r1), 0, 0
	stfd f30, 0x1b0(r1)
	psq_st f30, 0x1b8(r1), 0, 0
	stfd f29, 0x1a0(r1)
	psq_st f29, 0x1a8(r1), 0, 0
	stmw r14, 0x158(r1)
	mr r29, r3
	lis r3, dat_802ef068@ha
	lwz r20, 0x1d8(r1)
	mr r30, r4
	lwz r21, 0x1dc(r1)
	mr r31, r5
	lwz r27, _battleWorkPointer(r13)
	mr r15, r6
	lwz r22, 0x0(r29)
	mr r16, r7
	mr r17, r8
	mr r18, r9
	mr r19, r10
	addi r28, r3, dat_802ef068@l
	li r3, 0x8
	bl camGetPtr
	lfs f2, 0x98(r29)
	lis r0, 0x4330
	stw r0, 0x138(r1)
	cmpwi r30, 0x0
	fctiwz f0, f2
	lfd f1, 0x130(r28)
	mr r14, r3
	li r26, 0xff
	stfd f0, 0x130(r1)
	lwz r3, 0x134(r1)
	xoris r0, r3, 0x8000
	stw r0, 0x13c(r1)
	lfd f0, 0x138(r1)
	fsubs f0, f0, f1
	fsubs f2, f2, f0
	bne @1
	lfs f0, float_1_8041c178(r2)
	lfs f1, float_255_8041c1cc(r2)
	fsubs f0, f0, f2
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x140(r1)
	lwz r26, 0x144(r1)
	@1:
	cmpwi r30, 0x6
	bne @2
	lfs f0, float_255_8041c1cc(r2)
	fmuls f0, f0, f2
	fctiwz f0, f0
	stfd f0, 0x148(r1)
	lwz r26, 0x14c(r1)
	@2:
	lwz r0, 0x0(r22)
	add r3, r3, r30
	cmpw r3, r0
	bne @3
	la r3, seleItemCoordCol(r13)
	lbz r25, seleItemCoordCol(r13)
	lbz r24, 0x1(r3)
	mr r22, r26
	lbz r23, 0x2(r3)
	b @4
	@3:
	clrlwi r3, r26, 24
	lis r0, 0x4330
	stw r3, 0x14c(r1)
	li r23, 0xff
	lfd f2, 0x1b8(r28)
	li r24, 0xff
	stw r0, 0x148(r1)
	li r25, 0xff
	lfs f3, float_144_8041c1d0(r2)
	lfd f1, 0x148(r1)
	lfs f0, float_255_8041c1cc(r2)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x140(r1)
	lwz r22, 0x144(r1)
	@4:
	bl btlDispGXInit2D
	mr r4, r31
	addi r3, r14, 0x11c
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	li r4, 0x0
	bl GXLoadPosMtxImm
	addis r3, r27, 0x1
	addi r4, r1, 0x7c
	lwz r3, 0x63dc(r3)
	li r5, 0x2
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x7c
	li r4, 0x0
	bl GXLoadTexObj
	lfs f1, float_neg152_8041c1d4(r2)
	mr r3, r25
	lfs f2, float_24_8041c198(r2)
	mr r4, r24
	lfs f3, float_neg136_8041c1d8(r2)
	mr r5, r23
	lfs f4, float_0_8041c144(r2)
	mr r6, r22
	bl btlDispGXQuads2D
	lfs f1, float_152_8041c1dc(r2)
	mr r3, r25
	lfs f2, float_24_8041c198(r2)
	mr r4, r24
	lfs f3, float_136_8041c1e0(r2)
	mr r5, r23
	lfs f4, float_0_8041c144(r2)
	mr r6, r22
	bl btlDispGXQuads2D
	addis r3, r27, 0x1
	addi r4, r1, 0x7c
	lwz r3, 0x63dc(r3)
	li r5, 0x3
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x7c
	li r4, 0x0
	bl GXLoadTexObj
	lfs f1, float_neg136_8041c1d8(r2)
	mr r3, r25
	lfs f2, float_24_8041c198(r2)
	mr r4, r24
	lfs f3, float_136_8041c1e0(r2)
	mr r5, r23
	lfs f4, float_0_8041c144(r2)
	mr r6, r22
	bl btlDispGXQuads2D
	lfs f1, float_neg119_8041c1e4(r2)
	addi r3, r1, 0xcc
	lfs f2, float_2_8041c1e8(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	lfs f1, float_0p5_8041c1c8(r2)
	addi r3, r1, 0xfc
	lfs f3, float_1_8041c178(r2)
	fmr f2, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	clrlwi. r0, r16, 16
	bne @5
	li r16, 0x18b
	@5:
	cmpwi r15, 0x1
	bne @6
	lwz r0, dat_8041c130(r2)
	mr r5, r16
	addi r3, r1, 0x9c
	addi r6, r1, 0x2c
	stw r0, 0x28(r1)
	li r4, 0x10
	stb r26, 0x2b(r1)
	lwz r0, 0x28(r1)
	stw r0, 0x2c(r1)
	bl iconDispGxCol
	b @7
	@6:
	lwz r0, dat_8041c134(r2)
	mr r5, r16
	addi r3, r1, 0x9c
	addi r6, r1, 0x24
	stw r0, 0x20(r1)
	li r4, 0x30
	stb r26, 0x23(r1)
	lwz r0, 0x20(r1)
	stw r0, 0x24(r1)
	bl iconDispGxCol
	@7:
	bl FontDrawStart
	cmpwi r15, 0x1
	bne @8
	lwz r0, unk_80422ff0(r2)
	stw r0, 0x1c(r1)
	stb r26, 0x1f(r1)
	lwz r0, 0x1c(r1)
	stw r0, 0x30(r1)
	b @9
	@8:
	lwz r0, float_3p0039_8041c138(r2)
	stw r0, 0x18(r1)
	stb r26, 0x1b(r1)
	lwz r0, 0x18(r1)
	stw r0, 0x30(r1)
	@9:
	lwz r0, 0x30(r1)
	addi r3, r1, 0x14
	stw r0, 0x14(r1)
	bl FontDrawColor
	lfs f1, float_neg104_8041c1ec(r2)
	addi r3, r1, 0xcc
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	cmpwi r21, 0x1
	bne @10
	mr r3, r17
	bl FontGetMessageWidth
	clrlwi r0, r3, 16
	cmplwi r0, 0x96
	ble @11
	mr r3, r17
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x14c(r1)
	lfd f2, 0x1b8(r28)
	stw r0, 0x148(r1)
	lfs f0, float_120_8041c1f4(r2)
	lfd f1, 0x148(r1)
	fsubs f1, f1, f2
	fdivs f1, f0, f1
	b @12
	@11:
	lfs f1, float_0p8_8041c1a4(r2)
	@12:
	lfs f2, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f3, f2
	bl PSMTXScale
	b @13
	@10:
	lfs f1, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	@13:
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	mr r4, r17
	addi r3, r1, 0x9c
	bl FontDrawStringMtx
	cmpwi r18, 0x0
	beq @14
	li r3, 0x64
	li r0, 0xa
	divw. r4, r18, r3
	mulli r3, r4, 0x64
	stw r4, 0x78(r1)
	subf r4, r3, r18
	divw r3, r4, r0
	mulli r0, r3, 0xa
	stw r3, 0x74(r1)
	subf r0, r0, r4
	stw r0, 0x70(r1)
	ble @15
	li r4, 0x1c
	li r3, 0xe
	li r0, 0x0
	stw r4, 0x64(r1)
	li r14, 0x3
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	b @16
	@15:
	cmpwi r3, 0x0
	ble @17
	li r4, 0x15
	li r3, 0x7
	li r0, 0x0
	stw r4, 0x64(r1)
	li r14, 0x2
	stw r3, 0x68(r1)
	stw r0, 0x6c(r1)
	b @16
	@17:
	li r0, 0x0
	li r3, 0xe
	stw r3, 0x64(r1)
	li r14, 0x1
	stw r0, 0x68(r1)
	stw r0, 0x6c(r1)
	@16:
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lfs f31, float_4_8041c1a8(r2)
	addi r18, r1, 0x70
	lfs f30, float_72_8041c1f8(r2)
	addi r17, r1, 0x64
	lfd f29, 0x130(r28)
	li r21, 0x0
	li r15, 0x0
	lis r16, 0x4330
	b @18
	@19:
	lwzx r0, r17, r15
	li r4, 0x0
	lwzx r5, r18, r15
	addi r3, r1, 0xcc
	xoris r0, r0, 0x8000
	stw r16, 0x148(r1)
	addi r5, r5, 0x30
	lfs f2, float_25_8041c1fc(r2)
	stw r0, 0x14c(r1)
	lfs f3, float_0_8041c144(r2)
	lfd f0, 0x148(r1)
	stb r5, 0x10(r1)
	fsubs f0, f0, f29
	stb r4, 0x11(r1)
	fadds f0, f30, f0
	fadds f1, f31, f0
	bl PSMTXTrans
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0x10
	bl FontDrawStringMtx
	addi r21, r21, 0x1
	addi r15, r15, 0x4
	@18:
	cmpw r21, r14
	blt @19
	lfs f1, float_120_8041c1f4(r2)
	addi r3, r1, 0xcc
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	lfs f1, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r28, 0x170
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x9c
	bl FontDrawStringMtx
	@14:
	cmpwi r19, 0x0
	beq @20
	li r3, 0x64
	li r0, 0xa
	divw. r4, r19, r3
	mulli r3, r4, 0x64
	stw r4, 0x60(r1)
	subf r4, r3, r19
	divw r3, r4, r0
	mulli r0, r3, 0xa
	stw r3, 0x5c(r1)
	subf r0, r0, r4
	stw r0, 0x58(r1)
	ble @21
	li r4, 0x1c
	li r3, 0xe
	li r0, 0x0
	stw r4, 0x4c(r1)
	li r14, 0x3
	stw r3, 0x50(r1)
	stw r0, 0x54(r1)
	b @22
	@21:
	cmpwi r3, 0x0
	ble @23
	li r4, 0x15
	li r3, 0x7
	li r0, 0x0
	stw r4, 0x4c(r1)
	li r14, 0x2
	stw r3, 0x50(r1)
	stw r0, 0x54(r1)
	b @22
	@23:
	li r0, 0x0
	li r3, 0xe
	stw r3, 0x4c(r1)
	li r14, 0x1
	stw r0, 0x50(r1)
	stw r0, 0x54(r1)
	@22:
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lfs f29, float_4_8041c1a8(r2)
	addi r18, r1, 0x58
	lfs f30, float_72_8041c1f8(r2)
	addi r17, r1, 0x4c
	lfd f31, 0x130(r28)
	li r19, 0x0
	li r15, 0x0
	lis r16, 0x4330
	b @24
	@25:
	lwzx r0, r17, r15
	li r4, 0x0
	lwzx r5, r18, r15
	addi r3, r1, 0xcc
	xoris r0, r0, 0x8000
	stw r16, 0x148(r1)
	addi r5, r5, 0x30
	lfs f2, float_25_8041c1fc(r2)
	stw r0, 0x14c(r1)
	lfs f3, float_0_8041c144(r2)
	lfd f0, 0x148(r1)
	stb r5, 0xc(r1)
	fsubs f0, f0, f31
	stb r4, 0xd(r1)
	fadds f0, f30, f0
	fadds f1, f29, f0
	bl PSMTXTrans
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xc
	bl FontDrawStringMtx
	addi r19, r19, 0x1
	addi r15, r15, 0x4
	@24:
	cmpw r19, r14
	blt @25
	lfs f1, float_120_8041c1f4(r2)
	addi r3, r1, 0xcc
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	lfs f1, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r28, 0x184
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x9c
	bl FontDrawStringMtx
	@20:
	cmplwi r20, 0x0
	beq @26
	lfs f0, 0x98(r29)
	addi r3, r1, 0xcc
	lfs f1, float_30_8041c200(r2)
	fctiwz f0, f0
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	stfd f0, 0x148(r1)
	lwz r0, 0x14c(r1)
	add r0, r30, r0
	mulli r0, r0, 0x18
	add r4, r20, r0
	lha r14, 0x14(r4)
	lha r17, 0x16(r4)
	bl PSMTXTrans
	lfs f1, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r28, 0x198
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x9c
	bl FontDrawStringMtx
	li r3, 0x64
	li r0, 0xa
	divw. r4, r14, r3
	mulli r3, r4, 0x64
	stw r4, 0x48(r1)
	subf r4, r3, r14
	divw r3, r4, r0
	mulli r0, r3, 0xa
	stw r3, 0x44(r1)
	subf r0, r0, r4
	stw r0, 0x40(r1)
	ble @27
	li r4, 0x1c
	li r3, 0xe
	li r0, 0x0
	stw r4, 0x34(r1)
	li r16, 0x3
	stw r3, 0x38(r1)
	stw r0, 0x3c(r1)
	b @28
	@27:
	cmpwi r3, 0x0
	ble @29
	li r4, 0x15
	li r3, 0x7
	li r0, 0x0
	stw r4, 0x34(r1)
	li r16, 0x2
	stw r3, 0x38(r1)
	stw r0, 0x3c(r1)
	b @28
	@29:
	li r0, 0x0
	li r3, 0xe
	stw r3, 0x34(r1)
	li r16, 0x1
	stw r0, 0x38(r1)
	stw r0, 0x3c(r1)
	@28:
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r14, r1, 0x40
	li r15, 0x0
	li r18, 0x0
	b @30
	@31:
	lwzx r3, r14, r18
	li r0, 0x0
	stb r0, 0x9(r1)
	addi r0, r3, 0x30
	lwz r3, gp(r13)
	stb r0, 0x8(r1)
	lwz r0, 0x16c(r3)
	cmplwi r0, 0x0
	bne @32
	addi r3, r1, 0x34
	lis r0, 0x4330
	lwzx r4, r3, r18
	addi r3, r1, 0xcc
	stw r0, 0x148(r1)
	xoris r0, r4, 0x8000
	lfd f1, 0x130(r28)
	stw r0, 0x14c(r1)
	lfs f4, float_30_8041c200(r2)
	lfd f0, 0x148(r1)
	lfs f5, float_26_8041c204(r2)
	fsubs f0, f0, f1
	lfs f2, float_25_8041c1fc(r2)
	lfs f3, float_0_8041c144(r2)
	fadds f0, f4, f0
	fadds f1, f5, f0
	bl PSMTXTrans
	b @33
	@32:
	addi r3, r1, 0x34
	lis r0, 0x4330
	lwzx r4, r3, r18
	addi r3, r1, 0xcc
	stw r0, 0x148(r1)
	xoris r0, r4, 0x8000
	lfd f1, 0x130(r28)
	stw r0, 0x14c(r1)
	lfs f4, float_30_8041c200(r2)
	lfd f0, 0x148(r1)
	lfs f5, float_28_8041c1ac(r2)
	fsubs f0, f0, f1
	lfs f2, float_25_8041c1fc(r2)
	lfs f3, float_0_8041c144(r2)
	fadds f0, f4, f0
	fadds f1, f5, f0
	bl PSMTXTrans
	@33:
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0x8
	bl FontDrawStringMtx
	addi r15, r15, 0x1
	addi r18, r18, 0x4
	@30:
	cmpw r15, r16
	blt @31
	lwz r3, gp(r13)
	lwz r0, 0x16c(r3)
	cmplwi r0, 0x0
	bne @34
	lfs f1, float_92_8041c208(r2)
	addi r3, r1, 0xcc
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	b @35
	@34:
	lfs f1, float_100_8041c20c(r2)
	addi r3, r1, 0xcc
	lfs f2, float_22_8041c1f0(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	@35:
	lfs f1, float_0p8_8041c1a4(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r28, 0x1a4
	bl msgSearch
	mr r4, r3
	addi r3, r1, 0x9c
	bl FontDrawStringMtx
	li r3, 0x64
	li r0, 0xa
	divw. r4, r17, r3
	mulli r3, r4, 0x64
	stw r4, 0x48(r1)
	subf r4, r3, r17
	divw r3, r4, r0
	mulli r0, r3, 0xa
	stw r3, 0x44(r1)
	subf r0, r0, r4
	stw r0, 0x40(r1)
	ble @36
	li r4, 0x1c
	li r3, 0xe
	li r0, 0x0
	stw r4, 0x34(r1)
	li r16, 0x3
	stw r3, 0x38(r1)
	stw r0, 0x3c(r1)
	b @37
	@36:
	cmpwi r3, 0x0
	ble @38
	li r4, 0x15
	li r3, 0x7
	li r0, 0x0
	stw r4, 0x34(r1)
	li r16, 0x2
	stw r3, 0x38(r1)
	stw r0, 0x3c(r1)
	b @37
	@38:
	li r0, 0x0
	li r3, 0xe
	stw r3, 0x34(r1)
	li r16, 0x1
	stw r0, 0x38(r1)
	stw r0, 0x3c(r1)
	@37:
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0xfc
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r14, r1, 0x40
	li r15, 0x0
	li r17, 0x0
	b @39
	@40:
	lwzx r3, r14, r17
	li r0, 0x0
	stb r0, 0x9(r1)
	addi r0, r3, 0x30
	lwz r3, gp(r13)
	stb r0, 0x8(r1)
	lwz r0, 0x16c(r3)
	cmplwi r0, 0x0
	bne @41
	addi r3, r1, 0x34
	lis r0, 0x4330
	lwzx r4, r3, r17
	addi r3, r1, 0xcc
	stw r0, 0x148(r1)
	xoris r0, r4, 0x8000
	lfd f1, 0x130(r28)
	stw r0, 0x14c(r1)
	lfs f4, float_30_8041c200(r2)
	lfd f0, 0x148(r1)
	lfs f5, float_76_8041c210(r2)
	fsubs f0, f0, f1
	lfs f2, float_25_8041c1fc(r2)
	lfs f3, float_0_8041c144(r2)
	fadds f0, f4, f0
	fadds f1, f5, f0
	bl PSMTXTrans
	b @42
	@41:
	addi r3, r1, 0x34
	lis r0, 0x4330
	lwzx r4, r3, r17
	addi r3, r1, 0xcc
	stw r0, 0x148(r1)
	xoris r0, r4, 0x8000
	lfd f1, 0x130(r28)
	stw r0, 0x14c(r1)
	lfs f4, float_30_8041c200(r2)
	lfd f0, 0x148(r1)
	lfs f5, float_78_8041c214(r2)
	fsubs f0, f0, f1
	lfs f2, float_25_8041c1fc(r2)
	lfs f3, float_0_8041c144(r2)
	fadds f0, f4, f0
	fadds f1, f5, f0
	bl PSMTXTrans
	@42:
	mr r3, r31
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0xfc
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x9c
	addi r4, r1, 0x8
	bl FontDrawStringMtx
	addi r15, r15, 0x1
	addi r17, r17, 0x4
	@39:
	cmpw r15, r16
	blt @40
	@26:
	psq_l f31, 0x1c8(r1), 0, 0
	lfd f31, 0x1c0(r1)
	psq_l f30, 0x1b8(r1), 0, 0
	lfd f30, 0x1b0(r1)
	psq_l f29, 0x1a8(r1), 0, 0
	lfd f29, 0x1a0(r1)
	lmw r14, 0x158(r1)
	lwz r0, 0x1d4(r1)
	mtlr r0
	addi r1, r1, 0x1d0
	blr
}

asm void DrawSubIcon(BattleSubMenu* menu, void* a, s32* enabled, s16* icons, const char** names, s32* costs, s32* p34, void* party, s32 y) {
	nofralloc
	stwu r1, -0x1f0(r1)
	mflr r0
	stw r0, 0x1f4(r1)
	stfd f31, 0x1e0(r1)
	psq_st f31, 0x1e8(r1), 0, 0
	stmw r17, 0x1a4(r1)
	lwz r11, _battleWorkPointer(r13)
	mr r22, r4
	mr r21, r3
	lwz r29, 0x1f8(r1)
	lwz r4, 0x420(r11)
	mr r23, r5
	mr r24, r6
	mr r25, r7
	mr r26, r8
	mr r27, r9
	mr r28, r10
	mr r3, r11
	bl BattleGetUnitPtr
	lfs f3, 0x98(r21)
	lis r0, 0x4330
	lis r3, double_to_int_802ef198@ha
	stw r0, 0x198(r1)
	fctiwz f1, f3
	lfd f2, double_to_int_802ef198@l(r3)
	lfs f0, float_24_8041c198(r2)
	li r30, 0x0
	lwz r31, 0x0(r21)
	li r20, 0x0
	stfd f1, 0x190(r1)
	li r19, 0x0
	li r18, 0x0
	lwz r0, 0x194(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x19c(r1)
	lfd f1, 0x198(r1)
	fsubs f1, f1, f2
	fsubs f1, f3, f1
	fmuls f31, f0, f1
	@1:
	lfs f0, 0x98(r21)
	lwz r0, 0x8(r31)
	fctiwz f0, f0
	stfd f0, 0x198(r1)
	lwz r3, 0x19c(r1)
	add r3, r3, r30
	cmpw r3, r0
	bge @2
	addi r0, r18, 0xa4
	lwzx r0, r21, r0
	clrlwi. r0, r0, 31
	beq @2
	xoris r3, r30, 0x8000
	lis r0, 0x4330
	stw r3, 0x19c(r1)
	lis r4, double_to_int_802ef198@ha
	lfd f2, double_to_int_802ef198@l(r4)
	addi r3, r1, 0x10
	stw r0, 0x198(r1)
	lfs f4, float_24_8041c198(r2)
	lfd f1, 0x198(r1)
	lfs f0, float_35_8041c218(r2)
	fsubs f2, f1, f2
	lfs f1, float_100_8041c20c(r2)
	lfs f3, float_0_8041c144(r2)
	fnmsubs f0, f4, f2, f0
	fadds f2, f0, f31
	bl PSMTXTrans
	addi r17, r1, 0x40
	addi r3, r1, 0x10
	add r17, r17, r19
	add r4, r22, r19
	mr r5, r17
	bl PSMTXConcat
	stw r28, 0x8(r1)
	mr r3, r21
	mr r4, r30
	mr r5, r17
	stw r29, 0xc(r1)
	lwzx r6, r23, r18
	lhzx r7, r24, r20
	lwzx r8, r25, r18
	lwzx r9, r26, r18
	lwzx r10, r27, r18
	bl DrawSubIconSub
	@2:
	addi r30, r30, 0x1
	addi r19, r19, 0x30
	cmpwi r30, 0x7
	addi r18, r18, 0x4
	addi r20, r20, 0x2
	blt @1
	psq_l f31, 0x1e8(r1), 0, 0
	lfd f31, 0x1e0(r1)
	lmw r17, 0x1a4(r1)
	lwz r0, 0x1f4(r1)
	mtlr r0
	addi r1, r1, 0x1f0
	blr
}

asm void DrawMainIconCircle(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, Vec v, f32 s) {
	nofralloc
	stwu r1, -0x260(r1)
	mflr r0
	stw r0, 0x264(r1)
	stfd f31, 0x250(r1)
	psq_st f31, 0x258(r1), 0, 0
	stfd f30, 0x240(r1)
	psq_st f30, 0x248(r1), 0, 0
	stfd f29, 0x230(r1)
	psq_st f29, 0x238(r1), 0, 0
	stmw r22, 0x208(r1)
	fmr f29, f1
	lwz r22, _battleWorkPointer(r13)
	mr r28, r4
	mr r29, r5
	mr r30, r6
	li r3, 0x8
	bl camGetPtr
	lfs f1, float_1p5_8041c21c(r2)
	mr r26, r3
	lfs f0, 0x8(r30)
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x200(r1)
	lwz r0, 0x204(r1)
	subfic r0, r0, 0xc0
	clrlwi r31, r0, 24
	bl btlDispGXInit2D
	lwz r0, dat_8041c124(r2)
	addi r4, r1, 0x18
	li r3, 0x1
	stw r0, 0x18(r1)
	bl GXSetTevColor
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xa
	li r6, 0x2
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	lfs f2, float_0p005_8041c224(r2)
	addi r3, r1, 0x9c
	lfs f1, 0x8(r30)
	lfs f0, float_1p3_8041c220(r2)
	lfs f3, float_1_8041c178(r2)
	fnmsubs f1, f2, f1, f0
	fmr f2, f1
	bl PSMTXScale
	lfs f0, float_0p017453_8041c164(r2)
	addi r3, r1, 0xcc
	li r4, 0x79
	fmuls f31, f0, f29
	fmr f1, f31
	bl PSMTXRotRad
	mr r3, r29
	addi r4, r1, 0xcc
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r3, r1, 0x3c
	addi r4, r1, 0x9c
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x3c
	addi r3, r26, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x3c
	li r4, 0x0
	bl GXLoadPosMtxImm
	addis r3, r22, 0x1
	addi r4, r1, 0x1c
	lwz r3, 0x63dc(r3)
	li r5, 0x0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x1c
	li r4, 0x0
	bl GXLoadTexObj
	lfs f0, float_0_8041c144(r2)
	fcmpo cr0, f29, f0
	cror eq, gt, eq
	bne @1
	lfs f3, float_180_8041c150(r2)
	fcmpo cr0, f29, f3
	cror eq, lt, eq
	bne @1
	lfs f0, float_8_8041c228(r2)
	lfs f2, float_4_8041c1a8(r2)
	fmuls f1, f0, f29
	lfs f0, float_1p3_8041c220(r2)
	fdivs f1, f1, f3
	fsubs f1, f2, f1
	fdivs f30, f1, f0
	@1:
	lfs f4, float_180_8041c150(r2)
	fcmpo cr0, f29, f4
	cror eq, gt, eq
	bne @2
	lfs f0, float_360_8041c160(r2)
	fcmpo cr0, f29, f0
	cror eq, lt, eq
	bne @2
	fsubs f1, f29, f4
	lfs f2, float_8_8041c228(r2)
	lfs f3, float_neg4_8041c22c(r2)
	lfs f0, float_1p3_8041c220(r2)
	fmuls f1, f2, f1
	fdivs f1, f1, f4
	fadds f1, f3, f1
	fdivs f30, f1, f0
	@2:
	lis r3, dat_802ef068@ha
	li r0, 0x10
	addi r3, r3, dat_802ef068@l
	addi r5, r1, 0x178
	subi r4, r3, 0x4
	mtctr r0
	@3:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @3
	lis r3, dat_802ef0e8@ha
	li r0, 0x10
	addi r3, r3, dat_802ef0e8@l
	addi r5, r1, 0xf8
	subi r4, r3, 0x4
	mtctr r0
	@4:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @4
	lfs f29, float_neg3p0769_8041c230(r2)
	li r22, 0x0
	li r26, 0x0
	@5:
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	addi r25, r1, 0xfc
	addi r24, r1, 0x17c
	add r25, r25, r26
	li r23, 0x0
	add r24, r24, r26
	li r27, 0x0
	@6:
	add r4, r24, r27
	add r5, r25, r27
	lfs f1, 0x0(r4)
	li r3, 0x0
	lfs f0, 0x4(r4)
	li r4, 0x0
	fadds f1, f30, f1
	lfs f3, 0x0(r5)
	fadds f2, f29, f0
	lfs f4, 0x4(r5)
	li r5, 0x0
	li r6, 0x80
	bl btlDispGXPoint2D
	addi r23, r23, 0x2
	addi r27, r27, 0x8
	cmpwi r23, 0x7
	blt @6
	addi r22, r22, 0x1
	addi r26, r26, 0x20
	cmpwi r22, 0x4
	blt @5
	li r23, 0x0
	li r27, 0x0
	@7:
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	addi r24, r1, 0xfc
	addi r25, r1, 0x17c
	add r24, r24, r27
	li r22, 0x0
	add r25, r25, r27
	li r26, 0x0
	@8:
	add r6, r24, r26
	add r4, r25, r26
	lfs f1, 0x0(r4)
	mr r3, r31
	lfs f2, 0x4(r4)
	mr r4, r31
	lfs f3, 0x0(r6)
	mr r5, r31
	lfs f4, 0x4(r6)
	li r6, 0xff
	bl btlDispGXPoint2D
	addi r22, r22, 0x2
	addi r26, r26, 0x8
	cmpwi r22, 0x7
	blt @8
	addi r23, r23, 0x1
	addi r27, r27, 0x20
	cmpwi r23, 0x4
	blt @7
	lfs f1, float_0_8041c144(r2)
	addi r3, r1, 0x6c
	lfs f2, float_7p5_8041c234(r2)
	fmr f3, f1
	bl PSMTXTrans
	lfs f2, float_0p005_8041c224(r2)
	addi r3, r1, 0x9c
	lfs f1, 0x8(r30)
	lfs f0, float_1p3_8041c220(r2)
	lfs f4, float_0p66_8041c238(r2)
	fnmsubs f0, f2, f1, f0
	lfs f3, float_1_8041c178(r2)
	fmuls f1, f4, f0
	fmr f2, f1
	bl PSMTXScale
	fmr f1, f31
	addi r3, r1, 0xcc
	li r4, 0x79
	bl PSMTXRotRad
	addi r3, r1, 0xcc
	bl PSMTXIdentity
	mr r3, r29
	addi r4, r1, 0xcc
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r3, r1, 0x3c
	addi r4, r1, 0x9c
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x3c
	addi r4, r1, 0x6c
	mr r5, r3
	bl PSMTXConcat
	lhz r5, 0xc(r28)
	cmplwi r5, 0x0
	bne @9
	li r5, 0x18b
	@9:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x1
	bne @10
	lwz r0, dat_8041c128(r2)
	addi r3, r1, 0x3c
	addi r6, r1, 0x14
	li r4, 0x10
	stw r0, 0x10(r1)
	stb r31, 0x10(r1)
	stb r31, 0x11(r1)
	stb r31, 0x12(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl iconDispGxCol
	b @11
	@10:
	lwz r0, dat_8041c12c(r2)
	addi r3, r1, 0x3c
	addi r6, r1, 0xc
	li r4, 0x30
	stw r0, 0x8(r1)
	stb r31, 0x8(r1)
	stb r31, 0x9(r1)
	stb r31, 0xa(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl iconDispGxCol
	@11:
	psq_l f31, 0x258(r1), 0, 0
	lfd f31, 0x250(r1)
	psq_l f30, 0x248(r1), 0, 0
	lfd f30, 0x240(r1)
	psq_l f29, 0x238(r1), 0, 0
	lfd f29, 0x230(r1)
	lmw r22, 0x208(r1)
	lwz r0, 0x264(r1)
	mtlr r0
	addi r1, r1, 0x260
	blr
}

asm void DrawMainIconHukidasi(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, f32 s) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stmw r27, 0xfc(r1)
	fmr f29, f1
	mr r27, r3
	lwz r30, _battleWorkPointer(r13)
	mr r28, r4
	mr r29, r5
	li r3, 0x8
	bl camGetPtr
	mr r31, r3
	bl btlDispGXInit2D
	lwz r0, dat_8041c118(r2)
	addi r4, r1, 0xc
	li r3, 0x1
	stw r0, 0xc(r1)
	bl GXSetTevColor
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xa
	li r6, 0x2
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lfs f1, float_0_8041c144(r2)
	addi r3, r1, 0x60
	lfs f2, float_neg5_8041c23c(r2)
	fmr f3, f1
	bl PSMTXTrans
	lfs f0, float_0p017453_8041c164(r2)
	addi r3, r1, 0xc0
	li r4, 0x79
	fmuls f31, f0, f29
	fmr f1, f31
	bl PSMTXRotRad
	mr r3, r29
	addi r4, r1, 0xc0
	addi r5, r1, 0x30
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x60
	mr r5, r3
	bl PSMTXConcat
	addi r4, r1, 0x30
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x30
	li r4, 0x0
	bl GXLoadPosMtxImm
	addis r3, r30, 0x1
	addi r4, r1, 0x10
	lwz r3, 0x63dc(r3)
	li r5, 0x1
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x10
	li r4, 0x0
	bl GXLoadTexObj
	lfs f0, float_0_8041c144(r2)
	fcmpo cr0, f29, f0
	cror eq, gt, eq
	bne @1
	lfs f2, float_180_8041c150(r2)
	fcmpo cr0, f29, f2
	cror eq, lt, eq
	bne @1
	lfs f0, float_8_8041c228(r2)
	lfs f1, float_4_8041c1a8(r2)
	fmuls f0, f0, f29
	fdivs f0, f0, f2
	fsubs f30, f1, f0
	@1:
	lfs f3, float_180_8041c150(r2)
	fcmpo cr0, f29, f3
	cror eq, gt, eq
	bne @2
	lfs f0, float_360_8041c160(r2)
	fcmpo cr0, f29, f0
	cror eq, lt, eq
	bne @2
	fsubs f0, f29, f3
	lfs f1, float_8_8041c228(r2)
	lfs f2, float_neg4_8041c22c(r2)
	fmuls f0, f1, f0
	fdivs f0, f0, f3
	fadds f30, f2, f0
	@2:
	lwz r0, 0x1c(r27)
	cmpwi r0, 0x0
	bne @3
	lfs f1, float_64_8041c240(r2)
	li r3, 0x0
	lfs f0, float_neg64_8041c244(r2)
	li r4, 0x0
	fadds f1, f1, f30
	lfs f2, float_76_8041c210(r2)
	fadds f3, f0, f30
	lfs f4, float_neg4_8041c22c(r2)
	li r5, 0x0
	li r6, 0x80
	bl btlDispGXQuads2D
	lfs f1, float_64_8041c240(r2)
	li r3, 0xff
	lfs f2, float_80_8041c248(r2)
	li r4, 0xff
	lfs f3, float_neg64_8041c244(r2)
	li r5, 0xff
	lfs f4, float_0_8041c144(r2)
	li r6, 0xff
	bl btlDispGXQuads2D
	b @4
	@3:
	lfs f1, float_neg64_8041c244(r2)
	li r3, 0x0
	lfs f0, float_64_8041c240(r2)
	li r4, 0x0
	fadds f1, f1, f30
	lfs f2, float_76_8041c210(r2)
	fadds f3, f0, f30
	lfs f4, float_neg4_8041c22c(r2)
	li r5, 0x0
	li r6, 0x80
	bl btlDispGXQuads2D
	lfs f1, float_neg64_8041c244(r2)
	li r3, 0xff
	lfs f2, float_80_8041c248(r2)
	li r4, 0xff
	lfs f3, float_64_8041c240(r2)
	li r5, 0xff
	lfs f4, float_0_8041c144(r2)
	li r6, 0xff
	bl btlDispGXQuads2D
	@4:
	lfs f1, float_neg67_8041c24c(r2)
	addi r3, r1, 0x60
	lfs f2, float_20_8041c168(r2)
	lfs f3, float_0_8041c144(r2)
	bl PSMTXTrans
	lfs f1, float_1_8041c178(r2)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	fmr f1, f31
	addi r3, r1, 0xc0
	li r4, 0x79
	bl PSMTXRotRad
	mr r3, r29
	addi r4, r1, 0xc0
	addi r5, r1, 0x30
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x60
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	lhz r5, 0xc(r28)
	cmplwi r5, 0x0
	bne @5
	li r5, 0x18b
	@5:
	lwz r0, 0x4(r28)
	cmpwi r0, 0x1
	bne @6
	addi r3, r1, 0x30
	li r4, 0x10
	bl iconDispGx2
	b @7
	@6:
	addi r3, r1, 0x30
	li r4, 0x30
	bl iconDispGx2
	@7:
	lfs f1, float_0_8041c144(r2)
	addi r3, r1, 0x60
	lwz r30, 0x8(r28)
	fmr f3, f1
	lfs f2, float_52p5_8041c250(r2)
	bl PSMTXTrans
	lfs f1, float_0p9_8041c254(r2)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	fmr f1, f31
	addi r3, r1, 0xc0
	li r4, 0x79
	bl PSMTXRotRad
	mr r3, r29
	addi r4, r1, 0xc0
	addi r5, r1, 0x30
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x60
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x30
	addi r4, r1, 0x90
	mr r5, r3
	bl PSMTXConcat
	bl FontDrawStart
	lwz r0, 0x4(r28)
	cmpwi r0, 0x1
	bne @8
	lwz r0, dat_8041c11c(r2)
	stw r0, 0xf0(r1)
	b @9
	@8:
	lwz r0, dat_8041c120(r2)
	stw r0, 0xf0(r1)
	@9:
	lwz r0, 0xf0(r1)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	mr r4, r30
	addi r3, r1, 0x30
	bl FontDrawStringCenterMtx
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	lmw r27, 0xfc(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void DrawMainIcon(BattleSubMenu* menu, BattleCommandAct* acts, void* a, void* b, void* c) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stmw r23, 0x4c(r1)
	mr r25, r4
	mr r24, r3
	mr r26, r5
	mr r27, r6
	mr r28, r7
	lwz r23, _battleWorkPointer(r13)
	lwz r4, 0x420(r23)
	mr r3, r23
	bl BattleGetUnitPtr
	lwz r0, 0x8(r3)
	cmpwi r0, 0xde
	bne @1
	addi r29, r23, 0x1bb4
	b @2
	@1:
	addi r29, r23, 0x1bc0
	@2:
	lwz r0, 0x8(r29)
	addi r6, r1, 0x2c
	addi r5, r1, 0x14
	li r7, 0x0
	li r3, 0x0
	li r4, 0x0
	mtctr r0
	cmpwi r0, 0x0
	ble @3
	@4:
	addi r0, r3, 0x4
	stwx r7, r6, r4
	lfsx f0, r27, r0
	addi r7, r7, 0x1
	addi r3, r3, 0xc
	stfsx f0, r5, r4
	addi r4, r4, 0x4
	bdnz @4
	@3:
	addi r6, r1, 0x14
	addi r7, r1, 0x2c
	li r8, 0x0
	li r3, 0x0
	b @5
	@6:
	addi r9, r8, 0x1
	subf r0, r9, r5
	slwi r4, r9, 2
	mtctr r0
	cmpw r9, r5
	bge @7
	@8:
	lfsx f0, r6, r3
	lfsx f1, r6, r4
	fcmpo cr0, f0, f1
	bge @9
	lwzx r5, r7, r3
	lwzx r0, r7, r4
	stfsx f1, r6, r3
	stwx r0, r7, r3
	stfsx f0, r6, r4
	stwx r5, r7, r4
	@9:
	addi r9, r9, 0x1
	addi r4, r4, 0x4
	bdnz @8
	@7:
	addi r8, r8, 0x1
	addi r3, r3, 0x4
	@5:
	lwz r5, 0x8(r29)
	subi r0, r5, 0x1
	cmpw r8, r0
	blt @6
	addi r31, r1, 0x2c
	li r30, 0x0
	li r23, 0x0
	b @10
	@11:
	lwzx r9, r31, r23
	slwi r8, r9, 2
	addi r0, r8, 0x20
	lwzx r3, r24, r0
	clrlwi. r0, r3, 31
	beq @12
	rlwinm. r0, r3, 0, 30, 30
	beq @13
	mulli r4, r9, 0x14
	lfsx f1, r28, r8
	mr r3, r24
	mulli r0, r9, 0x30
	add r4, r25, r4
	add r5, r26, r0
	bl DrawMainIconHukidasi
	b @12
	@13:
	mulli r0, r9, 0xc
	mr r3, r24
	addi r6, r1, 0x8
	add r7, r27, r0
	lwz r0, 0x0(r7)
	mulli r4, r9, 0x14
	lwz r5, 0x4(r7)
	stw r0, 0x8(r1)
	mulli r0, r9, 0x30
	add r4, r25, r4
	stw r5, 0xc(r1)
	add r5, r26, r0
	lwz r0, 0x8(r7)
	stw r0, 0x10(r1)
	lfsx f1, r28, r8
	bl DrawMainIconCircle
	@12:
	addi r30, r30, 0x1
	addi r23, r23, 0x4
	@10:
	lwz r0, 0x8(r29)
	cmpw r30, r0
	blt @11
	lmw r23, 0x4c(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void GetRingOffset(f32 angle, f32* x, f32* y) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x10(r1)
	psq_st f31, 0x18(r1), 0, 0
	stmw r30, 0x8(r1)
	lfs f0, float_4p7124_8041c258(r2)
	mr r30, r3
	mr r31, r4
	fsubs f31, f0, f1
	fmr f1, f31
	bl cos
	frsp f2, f1
	lfs f0, float_80_8041c248(r2)
	fmr f1, f31
	fmuls f0, f0, f2
	stfs f0, 0x0(r30)
	bl sin
	frsp f1, f1
	lfs f0, float_35_8041c218(r2)
	fmuls f0, f0, f1
	stfs f0, 0x0(r31)
	psq_l f31, 0x18(r1), 0, 0
	lfd f31, 0x10(r1)
	lmw r30, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void GetRingCenter(Vec* out) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r5, _battleWorkPointer(r13)
	lwz r4, 0x420(r5)
	mr r3, r5
	bl BattleGetUnitPtr
	mr r4, r31
	addi r3, r3, 0x3c
	bl btlGetScreenPoint
	lfs f1, 0x0(r31)
	lfs f0, float_22p5_8041c25c(r2)
	lfs f2, float_105_8041c260(r2)
	fadds f3, f1, f0
	lfs f1, float_0_8041c144(r2)
	lfs f0, float_neg180_8041c264(r2)
	stfs f3, 0x0(r31)
	lfs f3, 0x4(r31)
	fadds f2, f3, f2
	stfs f2, 0x4(r31)
	stfs f1, 0x8(r31)
	lfs f1, 0x0(r31)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @1
	stfs f0, 0x0(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void battleMenuDispEnd(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, _battleWorkPointer(r13)
	addis r3, r3, 0x1
	lwz r3, 0x63dc(r3)
	bl fileFree
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void battleMenuDispInit(void) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stw r31, 0x10c(r1)
	lwz r31, _battleWorkPointer(r13)
	bl getMarioStDvdRoot
	lis r4, str_802EF228@ha
	mr r5, r3
	addi r4, r4, str_802EF228@l
	addi r3, r1, 0x8
	crclr 6
	bl sprintf
	addi r3, r1, 0x8
	li r4, 0x4
	bl fileAlloc
	addis r4, r31, 0x1
	stw r3, 0x63dc(r4)
	lwz r0, 0x114(r1)
	lwz r31, 0x10c(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm BOOL BattleMenuKeyOKInACT(BattleWork* wp) {
	nofralloc
	lbz r0, 0x1c74(r3)
	cmplwi r0, 0x0
	bne @1
	lwz r3, 0x1c78(r3)
	lbz r0, 0x14(r3)
	cmplwi r0, 0x0
	bne @1
	li r3, 0x0
	blr
	@1:
	li r3, 0x1
	blr
}

asm void SelectedItemCoordinateColorUpDate(void) {
	nofralloc
	lbz r0, g5_seq_s510(r13)
	extsb r0, r0
	cmpwi r0, 0x3
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	blr
	@2:
	cmpwi r0, 0x5
	beq @6
	bgelr
	b @7
	@5:
	la r4, seleItemCoordCol(r13)
	lbz r3, 0x1(r4)
	addi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, 0x1(r4)
	cmplwi r0, 0xff
	bnelr
	li r0, 0x1
	stb r0, g5_seq_s510(r13)
	blr
	@3:
	lbz r3, seleItemCoordCol(r13)
	subi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, seleItemCoordCol(r13)
	cmplwi r0, 0xc0
	bnelr
	li r0, 0x2
	stb r0, g5_seq_s510(r13)
	blr
	@4:
	la r4, seleItemCoordCol(r13)
	lbz r3, 0x2(r4)
	addi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, 0x2(r4)
	cmplwi r0, 0xff
	bnelr
	li r0, 0x3
	stb r0, g5_seq_s510(r13)
	blr
	@1:
	la r4, seleItemCoordCol(r13)
	lbz r3, 0x1(r4)
	subi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, 0x1(r4)
	cmplwi r0, 0xc0
	bnelr
	li r0, 0x4
	stb r0, g5_seq_s510(r13)
	blr
	@7:
	lbz r3, seleItemCoordCol(r13)
	addi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, seleItemCoordCol(r13)
	cmplwi r0, 0xff
	bnelr
	li r0, 0x5
	stb r0, g5_seq_s510(r13)
	blr
	@6:
	la r4, seleItemCoordCol(r13)
	lbz r3, 0x2(r4)
	subi r3, r3, 0x1
	clrlwi r0, r3, 24
	stb r3, 0x2(r4)
	cmplwi r0, 0xc0
	bnelr
	li r0, 0x0
	stb r0, g5_seq_s510(r13)
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80360E8C_data[1] = {0};
__declspec(section ".sdata") u32 gap_07_80410F74_sdata[1] = {0};
