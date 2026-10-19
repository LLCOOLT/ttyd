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
#ifndef NONMATCHING
#include "manager/filemgr.h"
__declspec(section ".sdata2") u32 gap_10_80422FF4_sbss2[1];
__declspec(section ".sdata2") u32 unk_80422ff0;
__declspec(section ".rodata") extern const u32 dat_802ef068[32];
__declspec(section ".rodata") extern const u32 dat_802ef0e8[32];
__declspec(section ".rodata") extern const f32 vec3_802ef168[3];
__declspec(section ".rodata") extern const f32 vec3_802ef174[3];
__declspec(section ".rodata") extern const f32 vec3_802ef180[3];
__declspec(section ".rodata") extern const f32 vec3_802ef18c[3];
__declspec(section ".rodata") extern const f64 double_to_int_802ef198;
__declspec(section ".rodata") extern const char str_802EF1A0[];
__declspec(section ".rodata") extern const char str_802EF1BC[];
__declspec(section ".rodata") extern const char str_802EF1D8[];
__declspec(section ".rodata") extern const char str_802EF1EC[];
__declspec(section ".rodata") extern const char str_802EF200[];
__declspec(section ".rodata") extern const char str_802EF20C[];
__declspec(section ".rodata") extern const u32 gap_04_802EF21C_rodata;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802ef220;
__declspec(section ".rodata") extern const char str_802EF228[];
__declspec(section ".rodata") extern const u32 gap_04_802EF24C_rodata;
__declspec(section ".sdata2") extern const u32 dat_8041c118;
__declspec(section ".sdata2") extern const u32 dat_8041c11c;
__declspec(section ".sdata2") extern const u32 dat_8041c120;
__declspec(section ".sdata2") extern const u32 dat_8041c124;
__declspec(section ".sdata2") extern const u32 dat_8041c128;
__declspec(section ".sdata2") extern const u32 dat_8041c12c;
__declspec(section ".sdata2") extern const u32 dat_8041c130;
__declspec(section ".sdata2") extern const u32 dat_8041c134;
__declspec(section ".sdata2") extern const f32 float_3p0039_8041c138;
__declspec(section ".sdata2") extern const u32 dat_8041c13c;
__declspec(section ".sdata2") extern const u32 dat_8041c140;
__declspec(section ".sdata2") extern const f32 float_0_8041c144;
__declspec(section ".sdata2") extern const f32 float_0p2_8041c148;
__declspec(section ".sdata2") extern const f32 float_3p1416_8041c14c;
__declspec(section ".sdata2") extern const f32 float_180_8041c150;
__declspec(section ".sdata2") extern const f32 float_270_8041c154;
__declspec(section ".sdata2") extern const f32 float_90_8041c158;
__declspec(section ".sdata2") extern const f32 float_10_8041c15c;
__declspec(section ".sdata2") extern const f32 float_360_8041c160;
__declspec(section ".sdata2") extern const f32 float_0p017453_8041c164;
__declspec(section ".sdata2") extern const f32 float_20_8041c168;
__declspec(section ".sdata2") extern const f32 float_neg60_8041c16c;
__declspec(section ".sdata2") extern const f32 float_55_8041c170;
__declspec(section ".sdata2") extern const f32 float_0p1_8041c174;
__declspec(section ".sdata2") extern const f32 float_1_8041c178;
__declspec(section ".sdata2") extern const f32 float_neg200_8041c17c;
__declspec(section ".sdata2") extern const f32 float_neg100_8041c180;
__declspec(section ".sdata2") extern const f32 float_neg40_8041c184;
__declspec(section ".sdata2") extern const f32 float_155_8041c188;
__declspec(section ".sdata2") extern const f32 float_15_8041c18c;
__declspec(section ".sdata2") extern const f32 float_0p75_8041c190;
__declspec(section ".sdata2") extern const f32 float_164_8041c194;
__declspec(section ".sdata2") extern const f32 float_24_8041c198;
__declspec(section ".sdata2") extern const f32 float_400_8041c19c;
__declspec(section ".sdata2") extern const f32 float_50_8041c1a0;
__declspec(section ".sdata2") extern const f32 float_0p8_8041c1a4;
__declspec(section ".sdata2") extern const f32 float_4_8041c1a8;
__declspec(section ".sdata2") extern const f32 float_28_8041c1ac;
__declspec(section ".sdata2") extern const f32 float_52_8041c1b0;
__declspec(section ".sdata2") extern const f32 float_60_8041c1b4;
__declspec(section ".sdata2") extern const f32 float_neg28_8041c1b8;
__declspec(section ".sdata2") extern const f32 float_12_8041c1bc;
__declspec(section ".sdata2") extern const f32 float_neg12_8041c1c0;
__declspec(section ".sdata2") extern const f32 float_5_8041c1c4;
__declspec(section ".sdata2") extern const f32 float_0p5_8041c1c8;
__declspec(section ".sdata2") extern const f32 float_255_8041c1cc;
__declspec(section ".sdata2") extern const f32 float_144_8041c1d0;
__declspec(section ".sdata2") extern const f32 float_neg152_8041c1d4;
__declspec(section ".sdata2") extern const f32 float_neg136_8041c1d8;
__declspec(section ".sdata2") extern const f32 float_152_8041c1dc;
__declspec(section ".sdata2") extern const f32 float_136_8041c1e0;
__declspec(section ".sdata2") extern const f32 float_neg119_8041c1e4;
__declspec(section ".sdata2") extern const f32 float_2_8041c1e8;
__declspec(section ".sdata2") extern const f32 float_neg104_8041c1ec;
__declspec(section ".sdata2") extern const f32 float_22_8041c1f0;
__declspec(section ".sdata2") extern const f32 float_120_8041c1f4;
__declspec(section ".sdata2") extern const f32 float_72_8041c1f8;
__declspec(section ".sdata2") extern const f32 float_25_8041c1fc;
__declspec(section ".sdata2") extern const f32 float_30_8041c200;
__declspec(section ".sdata2") extern const f32 float_26_8041c204;
__declspec(section ".sdata2") extern const f32 float_92_8041c208;
__declspec(section ".sdata2") extern const f32 float_100_8041c20c;
__declspec(section ".sdata2") extern const f32 float_76_8041c210;
__declspec(section ".sdata2") extern const f32 float_78_8041c214;
__declspec(section ".sdata2") extern const f32 float_35_8041c218;
__declspec(section ".sdata2") extern const f32 float_1p5_8041c21c;
__declspec(section ".sdata2") extern const f32 float_1p3_8041c220;
__declspec(section ".sdata2") extern const f32 float_0p005_8041c224;
__declspec(section ".sdata2") extern const f32 float_8_8041c228;
__declspec(section ".sdata2") extern const f32 float_neg4_8041c22c;
__declspec(section ".sdata2") extern const f32 float_neg3p0769_8041c230;
__declspec(section ".sdata2") extern const f32 float_7p5_8041c234;
__declspec(section ".sdata2") extern const f32 float_0p66_8041c238;
__declspec(section ".sdata2") extern const f32 float_neg5_8041c23c;
__declspec(section ".sdata2") extern const f32 float_64_8041c240;
__declspec(section ".sdata2") extern const f32 float_neg64_8041c244;
__declspec(section ".sdata2") extern const f32 float_80_8041c248;
__declspec(section ".sdata2") extern const f32 float_neg67_8041c24c;
__declspec(section ".sdata2") extern const f32 float_52p5_8041c250;
__declspec(section ".sdata2") extern const f32 float_0p9_8041c254;
__declspec(section ".sdata2") extern const f32 float_4p7124_8041c258;
__declspec(section ".sdata2") extern const f32 float_22p5_8041c25c;
__declspec(section ".sdata2") extern const f32 float_105_8041c260;
__declspec(section ".sdata2") extern const f32 float_neg180_8041c264;
#define EXT_LIT(sym, val) (sym)

#endif
extern GlobalWork* gp;
void FontDrawStringCenterMtx(Mtx mtx, const char* msg);
void btlDispGXPoint2D(f32 x, f32 y, u8 r, u8 g, u8 b, u8 a, f32 s, f32 t);
void FontDrawColor(GXColor color);
void GetRingCenter(Vec* out);
void GetRingOffset(f32 angle, f32* x, f32* y);
f32 kakutable[3][5] = {{240.0f, 120.0f, 0.0f, 0.0f, 0.0f}, {270.0f, 180.0f, 90.0f, 0.0f, 0.0f}, {270.0f, 203.0f, 157.0f, 90.0f, 0.0f}};

//.sdata
GXColor seleItemCoordCol = {0xFF, 0xC0, 0xC0, 0xCF};

void SelectedItemCoordinateColorUpDate(void) {
#ifndef NONMATCHING
    static u8 gap_08_80418981_sbss[4];  // .sbss pad after seq$510
#endif
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

BOOL BattleMenuKeyOKInACT(BattleWork* wp) {
    if (!wp->commandMenu.unk540[0x18] && !WP_SUBMENU(wp)->field_14) {
        return FALSE;
    }
    return TRUE;
}

#ifndef NONMATCHING
BattleUnit* BattleGetMarioPtr(BattleWork* work);
BattleUnit* BattleGetPartyPtr(BattleWork* wp);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
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
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
extern void* jumptable_80360DE8[];
extern void* jumptable_80360D44[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void battleMenuDispInit(void) {
#ifdef NONMATCHING
    BattleWork* wp = _battleWorkPointer;
    char path[256];

    sprintf(path, "%s/battle/common/battle_common.tpl\0", getMarioStDvdRoot());
    wp->menuTex = fileAlloc(path, 4);
#endif
#ifndef NONMATCHING
	char _af_pad[252];
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		bl getMarioStDvdRoot
		lis r4, str_802EF228@ha
		opword 0x7C651B78
		addi r4, r4, str_802EF228@l
		la r3, _af_pad+0
		opword 0x4CC63182
		bl sprintf
		opword 0x38610008
		opword 0x38800004
		bl fileAlloc
		opword 0x3C9F0001
		opword 0x906463DC
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void battleMenuDispEnd(void) {
    fileFree(_battleWorkPointer->menuTex);
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void GetRingCenter(Vec* out) {
#ifdef NONMATCHING
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, wp->activeUnitId);
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C7F1B78
		lwz r5, _battleWorkPointer(r13)
		opword 0x80850420
		opword 0x7CA32B78
		bl BattleGetUnitPtr
		opword 0x7FE4FB78
		opword 0x3863003C
		bl btlGetScreenPoint
		opword 0xC03F0000
		lfs f0, float_22p5_8041c25c(r2)
		lfs f2, float_105_8041c260(r2)
		opword 0xEC61002A
		lfs f1, float_0_8041c144(r2)
		lfs f0, float_neg180_8041c264(r2)
		opword 0xD07F0000
		opword 0xC07F0004
		opword 0xEC43102A
		opword 0xD05F0004
		opword 0xD03F0008
		opword 0xC03F0000
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		opword 0xD01F0000
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    btlGetScreenPoint((Vec*)((u8*)unit + 0x3C), out);
    out->x += 22.5f;
    out->y += 105.0f;
    out->z = 0.0f;
    if (out->x <= -180.0f) {
        out->x = -180.0f;
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void GetRingOffset(f32 angle, f32* x, f32* y) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xDBE10010
		opword 0xF3E10018
		opword 0xBFC10008
		lfs f0, float_4p7124_8041c258(r2)
		opword 0x7C7E1B78
		opword 0x7C9F2378
		opword 0xEFE00828
		opword 0xFC20F890
		bl cos
		opword 0xFC400818
		lfs f0, float_80_8041c248(r2)
		opword 0xFC20F890
		opword 0xEC0000B2
		opword 0xD01E0000
		bl sin
		opword 0xFC200818
		lfs f0, float_35_8041c218(r2)
		opword 0xEC000072
		opword 0xD01F0000
		opword 0xE3E10018
		opword 0xCBE10010
		opword 0xBBC10008
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifdef NONMATCHING

void GetRingOffset(f32 angle, f32* x, f32* y) {
    f32 t = 4.712389f - angle;
    *x = 80.0f * (f32)cos(t);
    *y = 35.0f * (f32)sin(t);
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void DrawMainIconHukidasi(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, f32 s) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[236];
	asm volatile {
		fmr f29, f1
		mr r27, r3
		lwz r30, _battleWorkPointer(r13)
		opword 0x7C9C2378
		opword 0x7CBD2B78
		opword 0x38600008
		bl camGetPtr
		opword 0x7C7F1B78
		bl btlDispGXInit2D
		lwz r0, dat_8041c118(r2)
		la r4, _af_pad+4
		opword 0x38600001
		opword 0x9001000C
		bl GXSetTevColor
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000A
		opword 0x38C00002
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		lfs f1, float_1_8041c178(r2)
		opword 0x38610090
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		lfs f1, float_0_8041c144(r2)
		opword 0x38610060
		lfs f2, float_neg5_8041c23c(r2)
		opword 0xFC600890
		bl PSMTXTrans
		lfs f0, float_0p017453_8041c164(r2)
		opword 0x386100C0
		opword 0x38800079
		opword 0xEFE00772
		opword 0xFC20F890
		bl PSMTXRotRad
		opword 0x7FA3EB78
		opword 0x388100C0
		opword 0x38A10030
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810060
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38810030
		opword 0x387F011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3C7E0001
		opword 0x38810010
		opword 0x806363DC
		opword 0x38A00001
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x38610010
		opword 0x38800000
		bl GXLoadTexObj
		lfs f0, float_0_8041c144(r2)
		opword 0xFC1D0040
		opword 0x4C411382
		opword 0x40820028
		lfs f2, float_180_8041c150(r2)
		opword 0xFC1D1040
		opword 0x4C401382
		opword 0x40820018
		lfs f0, float_8_8041c228(r2)
		lfs f1, float_4_8041c1a8(r2)
		opword 0xEC000772
		opword 0xEC001024
		opword 0xEFC10028
		lfs f3, float_180_8041c150(r2)
		opword 0xFC1D1840
		opword 0x4C411382
		opword 0x4082002C
		lfs f0, float_360_8041c160(r2)
		opword 0xFC1D0040
		opword 0x4C401382
		opword 0x4082001C
		opword 0xEC1D1828
		lfs f1, float_8_8041c228(r2)
		lfs f2, float_neg4_8041c22c(r2)
		opword 0xEC010032
		opword 0xEC001824
		opword 0xEFC2002A
		opword 0x801B001C
		opword 0x2C000000
		opword 0x40820058
		lfs f1, float_64_8041c240(r2)
		opword 0x38600000
		lfs f0, float_neg64_8041c244(r2)
		opword 0x38800000
		opword 0xEC21F02A
		lfs f2, float_76_8041c210(r2)
		opword 0xEC60F02A
		lfs f4, float_neg4_8041c22c(r2)
		opword 0x38A00000
		opword 0x38C00080
		bl btlDispGXQuads2D
		lfs f1, float_64_8041c240(r2)
		opword 0x386000FF
		lfs f2, float_80_8041c248(r2)
		opword 0x388000FF
		lfs f3, float_neg64_8041c244(r2)
		opword 0x38A000FF
		lfs f4, float_0_8041c144(r2)
		opword 0x38C000FF
		bl btlDispGXQuads2D
		opword 0x48000054
		lfs f1, float_neg64_8041c244(r2)
		opword 0x38600000
		lfs f0, float_64_8041c240(r2)
		opword 0x38800000
		opword 0xEC21F02A
		lfs f2, float_76_8041c210(r2)
		opword 0xEC60F02A
		lfs f4, float_neg4_8041c22c(r2)
		opword 0x38A00000
		opword 0x38C00080
		bl btlDispGXQuads2D
		lfs f1, float_neg64_8041c244(r2)
		opword 0x386000FF
		lfs f2, float_80_8041c248(r2)
		opword 0x388000FF
		lfs f3, float_64_8041c240(r2)
		opword 0x38A000FF
		lfs f4, float_0_8041c144(r2)
		opword 0x38C000FF
		bl btlDispGXQuads2D
		lfs f1, float_neg67_8041c24c(r2)
		opword 0x38610060
		lfs f2, float_20_8041c168(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		lfs f1, float_1_8041c178(r2)
		opword 0x38610090
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0xFC20F890
		opword 0x386100C0
		opword 0x38800079
		bl PSMTXRotRad
		opword 0x7FA3EB78
		opword 0x388100C0
		opword 0x38A10030
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810060
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xA0BC000C
		opword 0x28050000
		opword 0x40820008
		opword 0x38A0018B
		opword 0x801C0004
		opword 0x2C000001
		opword 0x40820014
		opword 0x38610030
		opword 0x38800010
		bl iconDispGx2
		opword 0x48000010
		opword 0x38610030
		opword 0x38800030
		bl iconDispGx2
		lfs f1, float_0_8041c144(r2)
		opword 0x38610060
		opword 0x83DC0008
		opword 0xFC600890
		lfs f2, float_52p5_8041c250(r2)
		bl PSMTXTrans
		lfs f1, float_0p9_8041c254(r2)
		opword 0x38610090
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0xFC20F890
		opword 0x386100C0
		opword 0x38800079
		bl PSMTXRotRad
		opword 0x7FA3EB78
		opword 0x388100C0
		opword 0x38A10030
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810060
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x38610030
		opword 0x38810090
		opword 0x7C651B78
		bl PSMTXConcat
		bl FontDrawStart
		opword 0x801C0004
		opword 0x2C000001
		opword 0x40820010
		lwz r0, dat_8041c11c(r2)
		opword 0x900100F0
		opword 0x4800000C
		lwz r0, dat_8041c120(r2)
		opword 0x900100F0
		opword 0x800100F0
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		opword 0x7FC4F378
		opword 0x38610030
		bl FontDrawStringCenterMtx
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void DrawMainIconCircle(BattleSubMenu* menu, BattleCommandAct* act, Mtx m, Vec v, f32 s) {
	char _af_pad[504];
	asm volatile {
		opword 0xFFA00890
		lwz r22, _battleWorkPointer(r13)
		opword 0x7C9C2378
		opword 0x7CBD2B78
		opword 0x7CDE3378
		opword 0x38600008
		bl camGetPtr
		lfs f1, float_1p5_8041c21c(r2)
		opword 0x7C7A1B78
		opword 0xC01E0008
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010200
		opword 0x80010204
		opword 0x200000C0
		opword 0x541F063E
		bl btlDispGXInit2D
		lwz r0, dat_8041c124(r2)
		la r4, _af_pad+16
		opword 0x38600001
		opword 0x90010018
		bl GXSetTevColor
		opword 0x38600001
		bl GXSetNumTevStages
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevColorOp
		opword 0x38600000
		opword 0x3880000F
		opword 0x38A0000A
		opword 0x38C00002
		opword 0x38E0000F
		bl GXSetTevColorIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00000
		opword 0x38E00001
		opword 0x39000000
		bl GXSetTevAlphaOp
		opword 0x38600000
		opword 0x38800007
		opword 0x38A00005
		opword 0x38C00004
		opword 0x38E00007
		bl GXSetTevAlphaIn
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x38C00004
		bl GXSetTevOrder
		lfs f2, float_0p005_8041c224(r2)
		opword 0x3861009C
		opword 0xC03E0008
		lfs f0, float_1p3_8041c220(r2)
		lfs f3, float_1_8041c178(r2)
		opword 0xEC22007C
		opword 0xFC400890
		bl PSMTXScale
		lfs f0, float_0p017453_8041c164(r2)
		opword 0x386100CC
		opword 0x38800079
		opword 0xEFE00772
		opword 0xFC20F890
		bl PSMTXRotRad
		opword 0x7FA3EB78
		opword 0x388100CC
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x3881009C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3881003C
		opword 0x387A011C
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3C760001
		opword 0x3881001C
		opword 0x806363DC
		opword 0x38A00000
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x3861001C
		opword 0x38800000
		bl GXLoadTexObj
		lfs f0, float_0_8041c144(r2)
		opword 0xFC1D0040
		opword 0x4C411382
		opword 0x40820030
		lfs f3, float_180_8041c150(r2)
		opword 0xFC1D1840
		opword 0x4C401382
		opword 0x40820020
		lfs f0, float_8_8041c228(r2)
		lfs f2, float_4_8041c1a8(r2)
		opword 0xEC200772
		lfs f0, float_1p3_8041c220(r2)
		opword 0xEC211824
		opword 0xEC220828
		opword 0xEFC10024
		lfs f4, float_180_8041c150(r2)
		opword 0xFC1D2040
		opword 0x4C411382
		opword 0x40820034
		lfs f0, float_360_8041c160(r2)
		opword 0xFC1D0040
		opword 0x4C401382
		opword 0x40820024
		opword 0xEC3D2028
		lfs f2, float_8_8041c228(r2)
		lfs f3, float_neg4_8041c22c(r2)
		lfs f0, float_1p3_8041c220(r2)
		opword 0xEC220072
		opword 0xEC212024
		opword 0xEC23082A
		opword 0xEFC10024
		lis r3, dat_802ef068@ha
		opword 0x38000010
		addi r3, r3, dat_802ef068@l
		opword 0x38A10178
		opword 0x3883FFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lis r3, dat_802ef0e8@ha
		opword 0x38000010
		addi r3, r3, dat_802ef0e8@l
		opword 0x38A100F8
		opword 0x3883FFFC
		opword 0x7C0903A6
		opword 0x80640004
		opword 0x84040008
		opword 0x90650004
		opword 0x94050008
		opword 0x4200FFF0
		lfs f29, float_neg3p0769_8041c230(r2)
		opword 0x3AC00000
		opword 0x3B400000
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0x3B2100FC
		opword 0x3B01017C
		opword 0x7F39D214
		opword 0x3AE00000
		opword 0x7F18D214
		opword 0x3B600000
		opword 0x7C98DA14
		opword 0x7CB9DA14
		opword 0xC0240000
		opword 0x38600000
		opword 0xC0040004
		opword 0x38800000
		opword 0xEC3E082A
		opword 0xC0650000
		opword 0xEC5D002A
		opword 0xC0850004
		opword 0x38A00000
		opword 0x38C00080
		bl btlDispGXPoint2D
		opword 0x3AF70002
		opword 0x3B7B0008
		opword 0x2C170007
		opword 0x4180FFC0
		opword 0x3AD60001
		opword 0x3B5A0020
		opword 0x2C160004
		opword 0x4180FF88
		opword 0x3AE00000
		opword 0x3B600000
		opword 0x38600080
		opword 0x38800000
		opword 0x38A00004
		bl GXBegin
		opword 0x3B0100FC
		opword 0x3B21017C
		opword 0x7F18DA14
		opword 0x3AC00000
		opword 0x7F39DA14
		opword 0x3B400000
		opword 0x7CD8D214
		opword 0x7C99D214
		opword 0xC0240000
		opword 0x7FE3FB78
		opword 0xC0440004
		opword 0x7FE4FB78
		opword 0xC0660000
		opword 0x7FE5FB78
		opword 0xC0860004
		opword 0x38C000FF
		bl btlDispGXPoint2D
		opword 0x3AD60002
		opword 0x3B5A0008
		opword 0x2C160007
		opword 0x4180FFC8
		opword 0x3AF70001
		opword 0x3B7B0020
		opword 0x2C170004
		opword 0x4180FF90
		lfs f1, float_0_8041c144(r2)
		opword 0x3861006C
		lfs f2, float_7p5_8041c234(r2)
		opword 0xFC600890
		bl PSMTXTrans
		lfs f2, float_0p005_8041c224(r2)
		opword 0x3861009C
		opword 0xC03E0008
		lfs f0, float_1p3_8041c220(r2)
		lfs f4, float_0p66_8041c238(r2)
		opword 0xEC02007C
		lfs f3, float_1_8041c178(r2)
		opword 0xEC240032
		opword 0xFC400890
		bl PSMTXScale
		opword 0xFC20F890
		opword 0x386100CC
		opword 0x38800079
		bl PSMTXRotRad
		opword 0x386100CC
		bl PSMTXIdentity
		opword 0x7FA3EB78
		opword 0x388100CC
		opword 0x38A1003C
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x3881009C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861003C
		opword 0x3881006C
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0xA0BC000C
		opword 0x28050000
		opword 0x40820008
		opword 0x38A0018B
		opword 0x801C0004
		opword 0x2C000001
		opword 0x40820034
		lwz r0, dat_8041c128(r2)
		opword 0x3861003C
		opword 0x38C10014
		opword 0x38800010
		opword 0x90010010
		opword 0x9BE10010
		opword 0x9BE10011
		opword 0x9BE10012
		opword 0x80010010
		opword 0x90010014
		bl iconDispGxCol
		opword 0x48000030
		lwz r0, dat_8041c12c(r2)
		opword 0x3861003C
		opword 0x38C1000C
		opword 0x38800030
		opword 0x90010008
		opword 0x9BE10008
		opword 0x9BE10009
		opword 0x9BE1000A
		opword 0x80010008
		opword 0x9001000C
		bl iconDispGxCol
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void DrawSubIcon(BattleSubMenu* menu, void* a, s32* enabled, s16* icons, const char** names, s32* costs, s32* p34, void* party, s32 y) {
	asm volatile {
		opword 0x9421FE10
		opword 0x7C0802A6
		opword 0x900101F4
		opword 0xDBE101E0
		opword 0xF3E101E8
		opword 0xBE2101A4
		lwz r11, _battleWorkPointer(r13)
		opword 0x7C962378
		opword 0x7C751B78
		opword 0x83A101F8
		opword 0x808B0420
		opword 0x7CB72B78
		opword 0x7CD83378
		opword 0x7CF93B78
		opword 0x7D1A4378
		opword 0x7D3B4B78
		opword 0x7D5C5378
		opword 0x7D635B78
		bl BattleGetUnitPtr
		opword 0xC0750098
		opword 0x3C004330
		lis r3, double_to_int_802ef198@ha
		opword 0x90010198
		opword 0xFC20181E
		lfd f2, double_to_int_802ef198@l(r3)
		lfs f0, float_24_8041c198(r2)
		opword 0x3BC00000
		opword 0x83F50000
		opword 0x3A800000
		opword 0xD8210190
		opword 0x3A600000
		opword 0x3A400000
		opword 0x80010194
		opword 0x6C008000
		opword 0x9001019C
		opword 0xC8210198
		opword 0xEC211028
		opword 0xEC230828
		opword 0xEFE00072
		opword 0xC0150098
		opword 0x801F0008
		opword 0xFC00001E
		opword 0xD8010198
		opword 0x8061019C
		opword 0x7C63F214
		opword 0x7C030000
		opword 0x40800098
		opword 0x381200A4
		opword 0x7C15002E
		opword 0x540007FF
		opword 0x41820088
		opword 0x6FC38000
		opword 0x3C004330
		opword 0x9061019C
		lis r4, double_to_int_802ef198@ha
		lfd f2, double_to_int_802ef198@l(r4)
		opword 0x38610010
		opword 0x90010198
		lfs f4, float_24_8041c198(r2)
		opword 0xC8210198
		lfs f0, float_35_8041c218(r2)
		opword 0xEC411028
		lfs f1, float_100_8041c20c(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xEC0400BC
		opword 0xEC40F82A
		bl PSMTXTrans
		opword 0x3A210040
		opword 0x38610010
		opword 0x7E319A14
		opword 0x7C969A14
		opword 0x7E258B78
		bl PSMTXConcat
		opword 0x93810008
		opword 0x7EA3AB78
		opword 0x7FC4F378
		opword 0x7E258B78
		opword 0x93A1000C
		opword 0x7CD7902E
		opword 0x7CF8A22E
		opword 0x7D19902E
		opword 0x7D3A902E
		opword 0x7D5B902E
		bl DrawSubIconSub
		opword 0x3BDE0001
		opword 0x3A730030
		opword 0x2C1E0007
		opword 0x3A520004
		opword 0x3A940002
		opword 0x4180FF38
		opword 0xE3E101E8
		opword 0xCBE101E0
		opword 0xBA2101A4
		opword 0x800101F4
		opword 0x7C0803A6
		opword 0x382101F0
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void DrawSubIconSub(BattleSubMenu* menu, s32 i, Mtx m, s32 enabled, s32 icon, const char* name, s32 cost, s32 p34, void* party, s32 y) {
	char _af_pad[328];
	asm volatile {
		opword 0x7C7D1B78
		lis r3, dat_802ef068@ha
		opword 0x828101D8
		opword 0x7C9E2378
		opword 0x82A101DC
		opword 0x7CBF2B78
		lwz r27, _battleWorkPointer(r13)
		opword 0x7CCF3378
		opword 0x82DD0000
		opword 0x7CF03B78
		opword 0x7D114378
		opword 0x7D324B78
		opword 0x7D535378
		addi r28, r3, dat_802ef068@l
		opword 0x38600008
		bl camGetPtr
		opword 0xC05D0098
		opword 0x3C004330
		stw r0, _af_pad+304(r1)
		opword 0x2C1E0000
		opword 0xFC00101E
		opword 0xC83C0130
		opword 0x7C6E1B78
		opword 0x3B4000FF
		opword 0xD8010130
		opword 0x80610134
		opword 0x6C608000
		opword 0x9001013C
		opword 0xC8010138
		opword 0xEC000828
		opword 0xEC420028
		opword 0x40820020
		lfs f0, float_1_8041c178(r2)
		lfs f1, float_255_8041c1cc(r2)
		opword 0xEC001028
		opword 0xEC010032
		opword 0xFC00001E
		opword 0xD8010140
		opword 0x83410144
		opword 0x2C1E0006
		opword 0x40820018
		lfs f0, float_255_8041c1cc(r2)
		opword 0xEC0000B2
		opword 0xFC00001E
		opword 0xD8010148
		opword 0x8341014C
		opword 0x80160000
		opword 0x7C63F214
		opword 0x7C030000
		opword 0x4082001C
		la r3, seleItemCoordCol(r13)
		lbz r25, seleItemCoordCol(r13)
		opword 0x8B030001
		opword 0x7F56D378
		opword 0x8AE30002
		opword 0x48000048
		opword 0x5743063E
		opword 0x3C004330
		opword 0x9061014C
		opword 0x3AE000FF
		opword 0xC85C01B8
		opword 0x3B0000FF
		opword 0x90010148
		opword 0x3B2000FF
		lfs f3, float_144_8041c1d0(r2)
		opword 0xC8210148
		lfs f0, float_255_8041c1cc(r2)
		opword 0xEC211028
		opword 0xEC230072
		opword 0xEC010024
		opword 0xFC00001E
		opword 0xD8010140
		opword 0x82C10144
		bl btlDispGXInit2D
		opword 0x7FE4FB78
		opword 0x386E011C
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x38800000
		bl GXLoadPosMtxImm
		opword 0x3C7B0001
		opword 0x3881007C
		opword 0x806363DC
		opword 0x38A00002
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x3861007C
		opword 0x38800000
		bl GXLoadTexObj
		lfs f1, float_neg152_8041c1d4(r2)
		opword 0x7F23CB78
		lfs f2, float_24_8041c198(r2)
		opword 0x7F04C378
		lfs f3, float_neg136_8041c1d8(r2)
		opword 0x7EE5BB78
		lfs f4, float_0_8041c144(r2)
		opword 0x7EC6B378
		bl btlDispGXQuads2D
		lfs f1, float_152_8041c1dc(r2)
		opword 0x7F23CB78
		lfs f2, float_24_8041c198(r2)
		opword 0x7F04C378
		lfs f3, float_136_8041c1e0(r2)
		opword 0x7EE5BB78
		lfs f4, float_0_8041c144(r2)
		opword 0x7EC6B378
		bl btlDispGXQuads2D
		opword 0x3C7B0001
		opword 0x3881007C
		opword 0x806363DC
		opword 0x38A00003
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x3861007C
		opword 0x38800000
		bl GXLoadTexObj
		lfs f1, float_neg136_8041c1d8(r2)
		opword 0x7F23CB78
		lfs f2, float_24_8041c198(r2)
		opword 0x7F04C378
		lfs f3, float_136_8041c1e0(r2)
		opword 0x7EE5BB78
		lfs f4, float_0_8041c144(r2)
		opword 0x7EC6B378
		bl btlDispGXQuads2D
		lfs f1, float_neg119_8041c1e4(r2)
		opword 0x386100CC
		lfs f2, float_2_8041c1e8(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		lfs f1, float_0p5_8041c1c8(r2)
		opword 0x386100FC
		lfs f3, float_1_8041c178(r2)
		opword 0xFC400890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x5600043F
		opword 0x40820008
		opword 0x3A00018B
		opword 0x2C0F0001
		opword 0x40820030
		lwz r0, dat_8041c130(r2)
		opword 0x7E058378
		opword 0x3861009C
		opword 0x38C1002C
		opword 0x90010028
		opword 0x38800010
		opword 0x9B41002B
		opword 0x80010028
		opword 0x9001002C
		bl iconDispGxCol
		opword 0x4800002C
		lwz r0, dat_8041c134(r2)
		opword 0x7E058378
		opword 0x3861009C
		opword 0x38C10024
		opword 0x90010020
		opword 0x38800030
		opword 0x9B410023
		opword 0x80010020
		opword 0x90010024
		bl iconDispGxCol
		bl FontDrawStart
		opword 0x2C0F0001
		opword 0x4082001C
		lwz r0, unk_80422ff0(r2)
		opword 0x9001001C
		opword 0x9B41001F
		opword 0x8001001C
		opword 0x90010030
		opword 0x48000018
		lwz r0, float_3p0039_8041c138(r2)
		opword 0x90010018
		opword 0x9B41001B
		opword 0x80010018
		opword 0x90010030
		opword 0x80010030
		opword 0x38610014
		opword 0x90010014
		bl FontDrawColor
		lfs f1, float_neg104_8041c1ec(r2)
		opword 0x386100CC
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		opword 0x2C150001
		opword 0x40820060
		opword 0x7E238B78
		bl FontGetMessageWidth
		opword 0x5460043E
		opword 0x28000096
		opword 0x40810034
		opword 0x7E238B78
		bl FontGetMessageWidth
		opword 0x5463043E
		opword 0x3C004330
		opword 0x9061014C
		opword 0xC85C01B8
		opword 0x90010148
		lfs f0, float_120_8041c1f4(r2)
		opword 0xC8210148
		opword 0xEC211028
		opword 0xEC200824
		opword 0x48000008
		lfs f1, float_0p8_8041c1a4(r2)
		lfs f2, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC601090
		bl PSMTXScale
		opword 0x48000018
		lfs f1, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x7E248B78
		opword 0x3861009C
		bl FontDrawStringMtx
		opword 0x2C120000
		opword 0x418201A8
		opword 0x38600064
		opword 0x3800000A
		opword 0x7C921BD7
		opword 0x1C640064
		opword 0x90810078
		opword 0x7C839050
		opword 0x7C6403D6
		opword 0x1C03000A
		opword 0x90610074
		opword 0x7C002050
		opword 0x90010070
		opword 0x40810024
		opword 0x3880001C
		opword 0x3860000E
		opword 0x38000000
		opword 0x90810064
		li r14, 0x3
		opword 0x90610068
		opword 0x9001006C
		opword 0x48000044
		opword 0x2C030000
		opword 0x40810024
		opword 0x38800015
		opword 0x38600007
		opword 0x38000000
		opword 0x90810064
		opword 0x39C00002
		opword 0x90610068
		opword 0x9001006C
		opword 0x4800001C
		opword 0x38000000
		opword 0x3860000E
		opword 0x90610064
		opword 0x39C00001
		opword 0x90010068
		opword 0x9001006C
		lfs f1, float_1_8041c178(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		lfs f31, float_4_8041c1a8(r2)
		opword 0x3A410070
		lfs f30, float_72_8041c1f8(r2)
		opword 0x3A210064
		opword 0xCBBC0130
		opword 0x3AA00000
		opword 0x39E00000
		opword 0x3E004330
		opword 0x4800007C
		opword 0x7C11782E
		opword 0x38800000
		opword 0x7CB2782E
		opword 0x386100CC
		opword 0x6C008000
		opword 0x92010148
		opword 0x38A50030
		lfs f2, float_25_8041c1fc(r2)
		opword 0x9001014C
		lfs f3, float_0_8041c144(r2)
		opword 0xC8010148
		opword 0x98A10010
		opword 0xEC00E828
		opword 0x98810011
		opword 0xEC1E002A
		opword 0xEC3F002A
		bl PSMTXTrans
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x38810010
		bl FontDrawStringMtx
		opword 0x3AB50001
		opword 0x39EF0004
		opword 0x7C157000
		opword 0x4180FF84
		lfs f1, float_120_8041c1f4(r2)
		opword 0x386100CC
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		lfs f1, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387C0170
		bl msgSearch
		opword 0x7C641B78
		opword 0x3861009C
		bl FontDrawStringMtx
		opword 0x2C130000
		opword 0x418201A8
		opword 0x38600064
		opword 0x3800000A
		opword 0x7C931BD7
		opword 0x1C640064
		opword 0x90810060
		opword 0x7C839850
		opword 0x7C6403D6
		opword 0x1C03000A
		opword 0x9061005C
		opword 0x7C002050
		opword 0x90010058
		opword 0x40810024
		opword 0x3880001C
		opword 0x3860000E
		opword 0x38000000
		opword 0x9081004C
		opword 0x39C00003
		opword 0x90610050
		opword 0x90010054
		opword 0x48000044
		opword 0x2C030000
		opword 0x40810024
		opword 0x38800015
		opword 0x38600007
		opword 0x38000000
		opword 0x9081004C
		opword 0x39C00002
		opword 0x90610050
		opword 0x90010054
		opword 0x4800001C
		opword 0x38000000
		opword 0x3860000E
		opword 0x9061004C
		opword 0x39C00001
		opword 0x90010050
		opword 0x90010054
		lfs f1, float_1_8041c178(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		lfs f29, float_4_8041c1a8(r2)
		opword 0x3A410058
		lfs f30, float_72_8041c1f8(r2)
		opword 0x3A21004C
		opword 0xCBFC0130
		opword 0x3A600000
		opword 0x39E00000
		opword 0x3E004330
		opword 0x4800007C
		opword 0x7C11782E
		opword 0x38800000
		opword 0x7CB2782E
		opword 0x386100CC
		opword 0x6C008000
		opword 0x92010148
		opword 0x38A50030
		lfs f2, float_25_8041c1fc(r2)
		opword 0x9001014C
		lfs f3, float_0_8041c144(r2)
		opword 0xC8010148
		opword 0x98A1000C
		opword 0xEC00F828
		opword 0x9881000D
		opword 0xEC1E002A
		opword 0xEC3D002A
		bl PSMTXTrans
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x3881000C
		bl FontDrawStringMtx
		opword 0x3A730001
		opword 0x39EF0004
		opword 0x7C137000
		opword 0x4180FF84
		lfs f1, float_120_8041c1f4(r2)
		opword 0x386100CC
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		lfs f1, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387C0184
		bl msgSearch
		opword 0x7C641B78
		opword 0x3861009C
		bl FontDrawStringMtx
		opword 0x28140000
		opword 0x41820448
		opword 0xC01D0098
		opword 0x386100CC
		lfs f1, float_30_8041c200(r2)
		opword 0xFC00001E
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xD8010148
		opword 0x8001014C
		opword 0x7C1E0214
		opword 0x1C000018
		opword 0x7C940214
		opword 0xA9C40014
		opword 0xAA240016
		bl PSMTXTrans
		lfs f1, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387C0198
		bl msgSearch
		opword 0x7C641B78
		opword 0x3861009C
		bl FontDrawStringMtx
		opword 0x38600064
		opword 0x3800000A
		opword 0x7C8E1BD7
		opword 0x1C640064
		opword 0x90810048
		opword 0x7C837050
		opword 0x7C6403D6
		opword 0x1C03000A
		opword 0x90610044
		opword 0x7C002050
		opword 0x90010040
		opword 0x40810024
		opword 0x3880001C
		opword 0x3860000E
		opword 0x38000000
		opword 0x90810034
		opword 0x3A000003
		opword 0x90610038
		opword 0x9001003C
		opword 0x48000044
		opword 0x2C030000
		opword 0x40810024
		opword 0x38800015
		opword 0x38600007
		opword 0x38000000
		opword 0x90810034
		opword 0x3A000002
		opword 0x90610038
		opword 0x9001003C
		opword 0x4800001C
		opword 0x38000000
		opword 0x3860000E
		opword 0x90610034
		opword 0x3A000001
		opword 0x90010038
		opword 0x9001003C
		lfs f1, float_1_8041c178(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x39C10040
		opword 0x39E00000
		opword 0x3A400000
		opword 0x480000E8
		opword 0x7C6E902E
		opword 0x38000000
		opword 0x98010009
		opword 0x38030030
		lwz r3, gp(r13)
		opword 0x98010008
		opword 0x8003016C
		opword 0x28000000
		opword 0x4082004C
		opword 0x38610034
		opword 0x3C004330
		opword 0x7C83902E
		opword 0x386100CC
		opword 0x90010148
		opword 0x6C808000
		opword 0xC83C0130
		opword 0x9001014C
		lfs f4, float_30_8041c200(r2)
		opword 0xC8010148
		lfs f5, float_26_8041c204(r2)
		opword 0xEC000828
		lfs f2, float_25_8041c1fc(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xEC04002A
		opword 0xEC25002A
		bl PSMTXTrans
		opword 0x48000048
		opword 0x38610034
		opword 0x3C004330
		opword 0x7C83902E
		opword 0x386100CC
		opword 0x90010148
		opword 0x6C808000
		opword 0xC83C0130
		opword 0x9001014C
		lfs f4, float_30_8041c200(r2)
		opword 0xC8010148
		lfs f5, float_28_8041c1ac(r2)
		opword 0xEC000828
		lfs f2, float_25_8041c1fc(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xEC04002A
		opword 0xEC25002A
		bl PSMTXTrans
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x38810008
		bl FontDrawStringMtx
		opword 0x39EF0001
		opword 0x3A520004
		opword 0x7C0F8000
		opword 0x4180FF18
		lwz r3, gp(r13)
		opword 0x8003016C
		opword 0x28000000
		opword 0x4082001C
		lfs f1, float_92_8041c208(r2)
		opword 0x386100CC
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		opword 0x48000018
		lfs f1, float_100_8041c20c(r2)
		opword 0x386100CC
		lfs f2, float_22_8041c1f0(r2)
		lfs f3, float_0_8041c144(r2)
		bl PSMTXTrans
		lfs f1, float_0p8_8041c1a4(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x387C01A4
		bl msgSearch
		opword 0x7C641B78
		opword 0x3861009C
		bl FontDrawStringMtx
		opword 0x38600064
		opword 0x3800000A
		opword 0x7C911BD7
		opword 0x1C640064
		opword 0x90810048
		opword 0x7C838850
		opword 0x7C6403D6
		opword 0x1C03000A
		opword 0x90610044
		opword 0x7C002050
		opword 0x90010040
		opword 0x40810024
		opword 0x3880001C
		opword 0x3860000E
		opword 0x38000000
		opword 0x90810034
		opword 0x3A000003
		opword 0x90610038
		opword 0x9001003C
		opword 0x48000044
		opword 0x2C030000
		opword 0x40810024
		opword 0x38800015
		opword 0x38600007
		opword 0x38000000
		opword 0x90810034
		opword 0x3A000002
		opword 0x90610038
		opword 0x9001003C
		opword 0x4800001C
		opword 0x38000000
		opword 0x3860000E
		opword 0x90610034
		opword 0x3A000001
		opword 0x90010038
		opword 0x9001003C
		lfs f1, float_1_8041c178(r2)
		opword 0x386100FC
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x39C10040
		opword 0x39E00000
		opword 0x3A200000
		opword 0x480000E8
		opword 0x7C6E882E
		opword 0x38000000
		opword 0x98010009
		opword 0x38030030
		lwz r3, gp(r13)
		opword 0x98010008
		opword 0x8003016C
		opword 0x28000000
		opword 0x4082004C
		opword 0x38610034
		opword 0x3C004330
		opword 0x7C83882E
		opword 0x386100CC
		opword 0x90010148
		opword 0x6C808000
		opword 0xC83C0130
		opword 0x9001014C
		lfs f4, float_30_8041c200(r2)
		opword 0xC8010148
		lfs f5, float_76_8041c210(r2)
		opword 0xEC000828
		lfs f2, float_25_8041c1fc(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xEC04002A
		opword 0xEC25002A
		bl PSMTXTrans
		opword 0x48000048
		opword 0x38610034
		opword 0x3C004330
		opword 0x7C83882E
		opword 0x386100CC
		opword 0x90010148
		opword 0x6C808000
		opword 0xC83C0130
		opword 0x9001014C
		lfs f4, float_30_8041c200(r2)
		opword 0xC8010148
		lfs f5, float_78_8041c214(r2)
		opword 0xEC000828
		lfs f2, float_25_8041c1fc(r2)
		lfs f3, float_0_8041c144(r2)
		opword 0xEC04002A
		opword 0xEC25002A
		bl PSMTXTrans
		opword 0x7FE3FB78
		opword 0x388100CC
		opword 0x38A1009C
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x388100FC
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x3861009C
		opword 0x38810008
		bl FontDrawStringMtx
		opword 0x39EF0001
		opword 0x3A310004
		opword 0x7C0F8000
		opword 0x4180FF18
	}
}
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void DrawMenuPartyChangeButton(void) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xDBC10040
		opword 0xF3C10048
		opword 0xBF810030
		lwz r4, _battleWorkPointer(r13)
		opword 0x38600008
		opword 0x83841C78
		opword 0x7C9D2378
		bl camGetPtr
		opword 0x7FA3EB78
		bl BattleGetMarioPtr
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl BattleGetPartyPtr
		opword 0x7C7F1B79
		opword 0x40820084
		opword 0x38610014
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x38E00000
		bl BattleAudience_GetItemOn
		opword 0x80010014
		opword 0x2C00FFFF
		opword 0x41820054
		opword 0xC03C0120
		lfs f0, float_0_8041c144(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_5_8041c1c4(r2)
		opword 0xEC010028
		opword 0xD01C0120
		opword 0x48000008
		opword 0xD01C0120
		opword 0x387E003C
		opword 0x38810024
		bl btlGetScreenPoint
		opword 0xC0410028
		opword 0x38600005
		lfs f0, float_20_8041c168(r2)
		opword 0xC0210024
		opword 0xEC420028
		opword 0xC07C0120
		bl DrawMenuPartyChangeButton_Sub
		opword 0x480000F0
		lfs f0, float_90_8041c158(r2)
		opword 0xD01C0120
		opword 0x480000E4
		opword 0x387E003C
		opword 0x38810024
		bl btlGetScreenPoint
		opword 0x387F003C
		opword 0x38810018
		bl btlGetScreenPoint
		opword 0xC0410024
		opword 0x38610014
		opword 0xC0210018
		opword 0x38810010
		lfs f0, float_0p5_8041c1c8(r2)
		opword 0x38A1000C
		opword 0xEC22082A
		opword 0xC3C10028
		opword 0x38C10008
		opword 0x38E00000
		opword 0xEFE10032
		bl BattleAudience_GetItemOn
		opword 0x80010014
		opword 0x2C00FFFF
		opword 0x41820060
		lfs f1, float_90_8041c158(r2)
		opword 0xC01C0120
		opword 0xFC010000
		opword 0x40820010
		lis r3, str_802EF1BC@ha
		addi r3, r3, str_802EF1BC@l
		bl psndSFXOn
		opword 0xC03C0120
		lfs f0, float_0_8041c144(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_5_8041c1c4(r2)
		opword 0xEC010028
		opword 0xD01C0120
		opword 0x48000008
		opword 0xD01C0120
		lfs f0, float_20_8041c168(r2)
		opword 0xFC20F890
		opword 0xC07C0120
		opword 0x38600005
		opword 0xEC5E0028
		bl DrawMenuPartyChangeButton_Sub
		opword 0x48000034
		lfs f0, float_90_8041c158(r2)
		opword 0x7FA3EB78
		opword 0xD01C0120
		bl BattleCommandCheckChangePositionEnable
		opword 0x2C030000
		opword 0x4182001C
		lfs f0, float_20_8041c168(r2)
		opword 0xFC20F890
		lfs f3, float_0_8041c144(r2)
		opword 0x38600004
		opword 0xEC5E0028
		bl DrawMenuPartyChangeButton_Sub
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xE3C10048
		opword 0xCBC10040
		opword 0xBB810030
		opword 0x80010064
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void DrawMenuPartyChangeButton_Sub(u32 id, f32 x, f32 y, f32 angle) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0x93E1004C
		lfs f0, float_0p017453_8041c164(r2)
		opword 0xFFC00890
		opword 0x7C7F1B78
		opword 0xFFE01090
		opword 0xEC2000F2
		opword 0x3861000C
		opword 0x38800079
		bl PSMTXRotRad
		opword 0xFC20F090
		opword 0x3861000C
		opword 0xFC40F890
		lfs f3, float_0_8041c144(r2)
		opword 0x7C641B78
		bl PSMTXTransApply
		lwz r0, dat_8041c13c(r2)
		opword 0x7FE4FB78
		opword 0x3861000C
		opword 0x38A10008
		opword 0x90010008
		opword 0x38C00000
		bl btlDispTexPlane2
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0x80010074
		opword 0x83E1004C
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop
#endif

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void DrawMenuPinchMark(void) {
	char _af_pad[148];
	asm {
		li r3, 0x8
	}
	asm volatile {
		lwz r29, _battleWorkPointer(r13)
		bl camGetPtr
		opword 0x7C7E1B78
		bl btlDispGXInit2D
		opword 0x7FA3EB78
		bl BattleGetMarioPtr
		opword 0x7C7F1B78
		opword 0xA863010C
		opword 0x7C600735
		opword 0x40810134
		opword 0xA81F0108
		opword 0x7C030000
		opword 0x40800128
		opword 0x2C030005
		opword 0x41810120
		opword 0x2C030001
		opword 0x4082005C
		lwz r5, gp(r13)
		opword 0x38600032
		opword 0x8085001C
		opword 0x80A5016C
		opword 0x7C041B96
		opword 0x30A5FFFF
		opword 0x7CA52910
		opword 0x38A50009
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x28000018
		opword 0x41810018
		li r25, 0xff
		opword 0x3B4000E9
		opword 0x3B600040
		opword 0x3B8000FF
		opword 0x48000040
		opword 0x3B2000E9
		opword 0x3B400052
		opword 0x3B60002F
		opword 0x3B8000FF
		opword 0x4800002C
		lwz r3, gp(r13)
		opword 0x3B2000FF
		opword 0x3B4000E9
		opword 0x3B600040
		opword 0x8003016C
		opword 0x3B8000FF
		opword 0x3000FFFF
		opword 0x7C600110
		opword 0x38030007
		opword 0x7C050378
		opword 0x3C7D0001
		la r4, _af_pad+24
		opword 0x806363DC
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x38610020
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x387F003C
		opword 0x38810014
		bl btlGetScreenPoint
		opword 0xC0610014
		opword 0x38610070
		lfs f1, float_20_8041c168(r2)
		lfs f2, float_60_8041c1b4(r2)
		opword 0xC0010018
		opword 0xEC230828
		lfs f3, float_0_8041c144(r2)
		opword 0xEC42002A
		bl PSMTXTrans
		opword 0x387E011C
		opword 0x38810070
		opword 0x38A10040
		bl PSMTXConcat
		opword 0x38610040
		opword 0x38800000
		bl GXLoadPosMtxImm
		lfs f1, float_neg28_8041c1b8(r2)
		opword 0x7F23CB78
		lfs f2, float_12_8041c1bc(r2)
		opword 0x7F44D378
		lfs f3, float_28_8041c1ac(r2)
		opword 0x7F65DB78
		lfs f4, float_neg12_8041c1c0(r2)
		opword 0x7F86E378
		bl btlDispGXQuads2D
		opword 0x7FA3EB78
		bl BattleGetPartyPtr
		opword 0x7C7F1B79
		opword 0x4182013C
		opword 0xA87F010C
		opword 0x7C600735
		opword 0x40810130
		opword 0xA81F0108
		opword 0x7C030000
		opword 0x40800124
		opword 0x2C030005
		opword 0x4181011C
		opword 0x2C030001
		opword 0x4082005C
		lwz r5, gp(r13)
		opword 0x38600032
		opword 0x8085001C
		opword 0x80A5016C
		opword 0x7C041B96
		opword 0x30A5FFFF
		opword 0x7CA52910
		opword 0x38A50009
		opword 0x7C0019D6
		opword 0x7C002050
		opword 0x28000018
		opword 0x41810018
		opword 0x3B8000FF
		opword 0x3B6000E9
		opword 0x7F99E378
		opword 0x3B400040
		opword 0x4800003C
		opword 0x3B8000E9
		opword 0x3B600052
		opword 0x3B40002F
		opword 0x3B2000FF
		opword 0x48000028
		lwz r3, gp(r13)
		opword 0x3B8000FF
		opword 0x7F99E378
		opword 0x3B6000E9
		opword 0x8003016C
		opword 0x3B400040
		opword 0x3000FFFF
		opword 0x7C600110
		opword 0x38A30007
		opword 0x3C7D0001
		opword 0x38810020
		opword 0x806363DC
		opword 0x806300A0
		opword 0x80630000
		bl TEXGetGXTexObjFromPalette
		opword 0x38610020
		opword 0x38800000
		bl GXLoadTexObj
		opword 0x387F003C
		opword 0x38810008
		bl btlGetScreenPoint
		opword 0xC0610008
		opword 0x38610070
		lfs f1, float_20_8041c168(r2)
		lfs f2, float_60_8041c1b4(r2)
		opword 0xC001000C
		opword 0xEC230828
		lfs f3, float_0_8041c144(r2)
		opword 0xEC42002A
		bl PSMTXTrans
		opword 0x387E011C
		opword 0x38810070
		opword 0x38A10040
		bl PSMTXConcat
		opword 0x38610040
		opword 0x38800000
		bl GXLoadPosMtxImm
		lfs f1, float_neg28_8041c1b8(r2)
		opword 0x7F83E378
		lfs f2, float_12_8041c1bc(r2)
		opword 0x7F64DB78
		lfs f3, float_28_8041c1ac(r2)
		opword 0x7F45D378
		lfs f4, float_neg12_8041c1c0(r2)
		opword 0x7F26CB78
		bl btlDispGXQuads2D
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    } else {
        iconDispGxCol(out, 0x30, icon, (GXColor){c, c, c, 0xFF});
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void DrawMenuHelpWin(const char* msg, f32 x, f32 y) {
	asm volatile {
		opword 0x9421FF00
		opword 0x7C0802A6
		opword 0x90010104
		opword 0xDBE100F0
		opword 0xF3E100F8
		opword 0xDBC100E0
		opword 0xF3C100E8
		opword 0x93E100DC
		lwz r0, dat_8041c140(r2)
		opword 0x7C7F1B78
		opword 0xFFE00890
		lfs f3, float_400_8041c19c(r2)
		opword 0xFFC01090
		opword 0x90010008
		lfs f4, float_50_8041c1a0(r2)
		opword 0x38810008
		lfs f5, float_10_8041c15c(r2)
		opword 0x38600000
		bl windowDispGX_Waku_col
		bl FontDrawStart
		opword 0x38600000
		bl FontDrawColorIDX
		lfs f1, float_0p8_8041c1a4(r2)
		bl FontDrawScale
		opword 0x7FE3FB78
		bl msgSearch
		opword 0x7C7F1B79
		opword 0x41820128
		opword 0x38600000
		opword 0x38000004
		opword 0x7C651B78
		opword 0x3881000C
		opword 0x7C0903A6
		opword 0x7CA419AE
		opword 0x38630030
		opword 0x4200FFF8
		opword 0x7FE5FB78
		opword 0x38C1000C
		opword 0x38600000
		opword 0x88050000
		opword 0x2C00003C
		opword 0x40820014
		opword 0x8C050001
		opword 0x2C00003E
		opword 0x4082FFF8
		opword 0x38A50001
		opword 0x88850000
		opword 0x7C800775
		opword 0x40820010
		opword 0x38000000
		opword 0x98060000
		opword 0x4800003C
		opword 0x7C800774
		opword 0x2C00000A
		opword 0x40820020
		opword 0x38000000
		opword 0x38630030
		opword 0x98060000
		opword 0x38C1000C
		opword 0x7CC61A14
		opword 0x38A50001
		opword 0x4BFFFFA8
		opword 0x98860000
		opword 0x38A50001
		opword 0x38C60001
		opword 0x4BFFFF98
		opword 0x8801000C
		opword 0x7C000775
		opword 0x4182000C
		lfs f1, float_0p8_8041c1a4(r2)
		bl FontDrawScale
		lfs f1, float_20_8041c168(r2)
		opword 0x3861000C
		lfs f0, float_4_8041c1a8(r2)
		opword 0xEFE1F82A
		opword 0xEC5E0028
		opword 0xFC20F890
		bl FontDrawString
		opword 0x8801003C
		opword 0x3BE1003C
		opword 0x7C000775
		opword 0x4182000C
		lfs f1, float_0p8_8041c1a4(r2)
		bl FontDrawScale
		lfs f0, float_28_8041c1ac(r2)
		opword 0xFC20F890
		opword 0x7FE3FB78
		opword 0xEC5E0028
		bl FontDrawString
		opword 0x8801006C
		opword 0x3BE1006C
		opword 0x7C000775
		opword 0x4182000C
		lfs f1, float_0p8_8041c1a4(r2)
		bl FontDrawScale
		lfs f0, float_52_8041c1b0(r2)
		opword 0xFC20F890
		opword 0x7FE3FB78
		opword 0xEC5E0028
		bl FontDrawString
		opword 0x48000020
		lfs f1, float_10_8041c15c(r2)
		lis r3, str_802EF1A0@ha
		lfs f0, float_4_8041c1a8(r2)
		addi r3, r3, str_802EF1A0@l
		opword 0xEC21F82A
		opword 0xEC5E0028
		bl FontDrawString
		opword 0xE3E100F8
		opword 0xCBE100F0
		opword 0xE3C100E8
		opword 0xCBC100E0
		opword 0x80010104
		opword 0x83E100DC
		opword 0x7C0803A6
		opword 0x38210100
	}
}
#pragma pop
#endif

#ifdef NONMATCHING



    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void DrawMenuCursorAndScrollArrow(Vec* v) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0xBFA10024
		lwz r4, _battleWorkPointer(r13)
		opword 0x7C7F1B78
		lfs f1, float_0_8041c144(r2)
		opword 0x38600004
		opword 0x83C41C78
		opword 0x38A00006
		lfs f2, float_10_8041c15c(r2)
		opword 0x83BE0000
		opword 0x809E011C
		bl intplGetValue
		opword 0x807E011C
		opword 0xFFE00890
		opword 0x38030001
		opword 0x901E011C
		opword 0x801E011C
		opword 0x2C00000C
		opword 0x4180000C
		opword 0x38000000
		opword 0x901E011C
		opword 0x801D0004
		opword 0x2C000000
		opword 0x40810044
		lfs f2, float_15_8041c18c(r2)
		opword 0x38610008
		opword 0xC03F0004
		opword 0x38800010
		lfs f0, float_0_8041c144(r2)
		opword 0x38A001B5
		opword 0xEC42082A
		lfs f3, float_155_8041c188(r2)
		opword 0xC03F0000
		opword 0xD0010010
		opword 0xEC63082A
		lfs f1, float_0p75_8041c190(r2)
		opword 0xEC02F82A
		opword 0xD0610008
		opword 0xD001000C
		bl iconDispGx
		opword 0x807D0008
		opword 0x809D0004
		opword 0x3803FFFA
		opword 0x7C040000
		opword 0x4080004C
		lfs f2, float_20_8041c168(r2)
		opword 0x38610008
		opword 0xC03F0004
		opword 0x38800010
		lfs f0, float_0_8041c144(r2)
		opword 0x38A001B6
		opword 0xEC42082A
		lfs f1, float_164_8041c194(r2)
		lfs f4, float_155_8041c188(r2)
		opword 0xC07F0000
		opword 0xEC420828
		opword 0xD0010010
		opword 0xEC64182A
		lfs f1, float_0p75_8041c190(r2)
		opword 0xEC02F828
		opword 0xD0610008
		opword 0xD001000C
		bl iconDispGx
		opword 0x807D0004
		opword 0x801D0000
		opword 0x7C030051
		opword 0x40800008
		opword 0x38000000
		opword 0x2C000006
		opword 0x41800008
		opword 0x38000005
		opword 0x6C038000
		opword 0x3C004330
		opword 0x9061001C
		lis r4, double_to_int_802ef198@ha
		lfd f1, double_to_int_802ef198@l(r4)
		opword 0x38610008
		opword 0x90010018
		opword 0x38800014
		opword 0xC09F0000
		opword 0x38A001F0
		opword 0xC8010018
		lfs f3, float_24_8041c198(r2)
		opword 0xEC400828
		opword 0xC03F0004
		lfs f0, float_0_8041c144(r2)
		opword 0xD0810008
		opword 0xEC4308BC
		lfs f1, float_1_8041c178(r2)
		opword 0xD0010010
		opword 0xD041000C
		bl iconDispGx
		opword 0xE3E10038
		opword 0xCBE10030
		opword 0xBBA10024
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
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

void DrawMenuPartyChangeButton_Sub(u32 id, f32 x, f32 y, f32 angle) {
    Mtx mtx;

    PSMTXRotRad(mtx, 'y', 0.017453292f * angle);
    PSMTXTransApply(mtx, mtx, x, y, 0.0f);
    btlDispTexPlane2(mtx, id, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, 0);
}

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
#ifndef NONMATCHING
#pragma pop
#endif

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
#ifdef NONMATCHING
    (*out)->field_98 = 0.0f;
#endif
#ifndef NONMATCHING
    (*out)->field_98 = EXT_LIT(float_0_8041c144, 0.0f);
#endif
    for (i = 0; i < 7; i++) {
        (*out)->field_A4[i] = 0;
        (*out)->field_C0[i] = 1;
        (*out)->field_DC[i] = -i;
        (*out)->field_F8[i] = 0;
    }
}

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

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void DrawSubMenuCommonProcessSub1(BattleSubMenu* menu, BattleCursor* cursor, s32 prev, s32 key) {
#ifdef NONMATCHING
    s32 i;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x2C060006
		opword 0x9421FFE0
		opword 0x4082009C
		opword 0x80E40008
		opword 0x2C070006
		opword 0x40810090
		opword 0x3807FFFA
		opword 0x7C050000
		opword 0x40820084
		opword 0x80040004
		opword 0x2C000000
		opword 0x40820078
		opword 0x80040000
		opword 0x2C000001
		opword 0x4182006C
		opword 0x3900001E
		lis r6, double_to_int_802ef198@ha
		opword 0x9103000C
		opword 0x38E00000
		opword 0x3CA04330
		lfd f2, double_to_int_802ef198@l(r6)
		opword 0x90E30010
		opword 0x38000007
		lfs f0, float_0_8041c144(r2)
		opword 0x80C40008
		opword 0x7CE43B78
		opword 0x90A10008
		opword 0x38A6FFFA
		opword 0x6CA58000
		opword 0x90A1000C
		opword 0xC8210008
		opword 0xEC211028
		opword 0xD023009C
		opword 0xD00300A0
		opword 0x7C0903A6
		opword 0x7CA32214
		opword 0x38840004
		opword 0x910500C0
		opword 0x90E500DC
		opword 0x4200FFF0
		opword 0x4800019C
		opword 0x2C060006
		opword 0x4082009C
		opword 0x80E40008
		opword 0x2C070006
		opword 0x40810090
		opword 0x2C050000
		opword 0x40820088
		opword 0x80C40004
		opword 0x3807FFFA
		opword 0x7C060000
		opword 0x40820078
		opword 0x80040000
		opword 0x2C000005
		opword 0x4182006C
		opword 0x39000028
		opword 0x3CC04330
		opword 0x9103000C
		opword 0x38E00000
		lis r5, double_to_int_802ef198@ha
		lfs f0, float_0_8041c144(r2)
		opword 0x90E30010
		opword 0x38000007
		lfd f1, double_to_int_802ef198@l(r5)
		opword 0x38A00000
		opword 0xD003009C
		opword 0x80840008
		opword 0x90C10008
		opword 0x3884FFFA
		opword 0x6C848000
		opword 0x9081000C
		opword 0xC8010008
		opword 0xEC000828
		opword 0xD00300A0
		opword 0x7C0903A6
		opword 0x7C832A14
		opword 0x38A50004
		opword 0x910400C0
		opword 0x90E400DC
		opword 0x4200FFF0
		opword 0x480000FC
		opword 0x80040004
		opword 0x38E50001
		opword 0x7C003800
		opword 0x40820074
		opword 0x3CC04330
		opword 0x6CA08000
		opword 0x9001000C
		opword 0x6CE58000
		lis r4, double_to_int_802ef198@ha
		opword 0x3900000A
		opword 0x90C10008
		opword 0x38E00000
		lfd f2, double_to_int_802ef198@l(r4)
		opword 0x38000007
		opword 0xC8010008
		opword 0x38800000
		opword 0x9103000C
		opword 0xEC201028
		opword 0x90E30010
		opword 0x90A10014
		opword 0x90C10010
		opword 0xC8010010
		opword 0xD023009C
		opword 0xEC001028
		opword 0xD00300A0
		opword 0x7C0903A6
		opword 0x7CA32214
		opword 0x38840004
		opword 0x910500C0
		opword 0x90E500DC
		opword 0x4200FFF0
		opword 0x4800007C
		opword 0x38E5FFFF
		opword 0x7C003800
		opword 0x40820070
		opword 0x3CC04330
		opword 0x6CA08000
		opword 0x90010014
		opword 0x6CE58000
		lis r4, double_to_int_802ef198@ha
		opword 0x39000014
		opword 0x90C10010
		opword 0x38E00000
		lfd f2, double_to_int_802ef198@l(r4)
		opword 0x38000007
		opword 0xC8010010
		opword 0x38800000
		opword 0x9103000C
		opword 0xEC201028
		opword 0x90E30010
		opword 0x90A1000C
		opword 0x90C10008
		opword 0xC8010008
		opword 0xD023009C
		opword 0xEC001028
		opword 0xD00300A0
		opword 0x7C0903A6
		opword 0x7CA32214
		opword 0x38840004
		opword 0x910500C0
		opword 0x90E500DC
		opword 0x4200FFF0
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void DrawSubMenuCommonProcess(f32* x, f32* y, void* a, void* b, void* c, void* d) {
	char _af_pad[104];
	asm volatile {
		lwz r18, _battleWorkPointer(r13)
		opword 0x7C9D2378
		opword 0x7C7E1B78
		opword 0x7CB52B78
		opword 0x83921C78
		opword 0x7CD63378
		opword 0x80920420
		opword 0x7CF73B78
		opword 0x837C0000
		opword 0x7D184378
		opword 0x7E439378
		bl BattleGetUnitPtr
		opword 0x80030008
		opword 0x2C0000DE
		opword 0x4082000C
		opword 0x3B521BB4
		opword 0x48000008
		opword 0x3B521BC0
		opword 0x801B0008
		opword 0x38600006
		opword 0x2C000006
		opword 0x40800008
		opword 0x7C030378
		opword 0x809B0004
		opword 0x7C661B78
		opword 0x80FB0000
		opword 0x7C852378
		opword 0x7C072000
		opword 0x41810010
		opword 0x3807FFFF
		opword 0x901B0004
		opword 0x48000020
		opword 0x3803FFFF
		opword 0x7C040214
		opword 0x7C070000
		opword 0x41800010
		opword 0x7C633850
		opword 0x38030002
		opword 0x901B0004
		opword 0x801B0004
		opword 0x2C000000
		opword 0x4080000C
		opword 0x38000000
		opword 0x901B0004
		opword 0x801B0008
		opword 0x807B0004
		opword 0x7C060050
		opword 0x7C030000
		opword 0x41800008
		opword 0x901B0004
		lfs f1, float_neg200_8041c17c(r2)
		lfs f0, float_neg100_8041c180(r2)
		opword 0xD03E0000
		opword 0xD01D0000
		opword 0x809C000C
		opword 0x28040028
		opword 0x418101AC
		lis r3, jumptable_80360DE8@ha
		opword 0x5480103A
		addi r3, r3, jumptable_80360DE8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x38600001
		opword 0x3C004330
		opword 0x987C0014
		lis r3, double_to_int_802ef198@ha
		addi r4, r3, double_to_int_802ef198@l
		opword 0x39000000
		opword 0x80FB0004
		opword 0x38600000
		opword 0x90010070
		opword 0x6CE08000
		opword 0xC8240000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xD01C0098
		opword 0x809A0008
		opword 0x7C8903A6
		opword 0x2C040000
		opword 0x40810028
		opword 0x38030034
		opword 0x7C1C002E
		opword 0x2C000001
		opword 0x4182000C
		opword 0x2C00000B
		opword 0x40820008
		opword 0x39080001
		opword 0x38630004
		opword 0x4200FFE0
		opword 0x38000007
		opword 0x38600000
		opword 0x38E00000
		opword 0x7C0903A6
		opword 0x380300C0
		opword 0x7C1C002E
		opword 0x2C000002
		opword 0x40820008
		opword 0x38E70001
		opword 0x38630004
		opword 0x4200FFE8
		opword 0x7C082000
		opword 0x40820014
		opword 0x2C070007
		opword 0x4082000C
		opword 0x38000002
		opword 0x901C000C
		opword 0x7F83E378
		opword 0x7F64DB78
		bl DrawSubMenuCommonProcessSub1
		opword 0x480000D0
		opword 0x38600001
		opword 0x3C004330
		opword 0x987C0014
		lis r3, double_to_int_802ef198@ha
		addi r7, r3, double_to_int_802ef198@l
		opword 0x7F64DB78
		opword 0x811B0004
		opword 0x7F83E378
		opword 0x90010070
		opword 0x6D008000
		opword 0xC8270000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xD01C0098
		bl DrawSubMenuCommonProcessSub1
		opword 0x4800008C
		opword 0x2C04000A
		opword 0x4182000C
		opword 0x2C040014
		opword 0x4082000C
		opword 0x38000001
		opword 0x981C0014
		opword 0x38000007
		opword 0x38800000
		opword 0x38600000
		opword 0x7C0903A6
		opword 0x380300C0
		opword 0x7C1C002E
		opword 0x2C000002
		opword 0x40820008
		opword 0x38840001
		opword 0x38630004
		opword 0x4200FFE8
		opword 0x2C040007
		opword 0x40820034
		opword 0x38600002
		opword 0x3C004330
		opword 0x907C000C
		lis r3, double_to_int_802ef198@ha
		lfd f1, double_to_int_802ef198@l(r3)
		opword 0x809B0004
		opword 0x90010070
		opword 0x6C808000
		opword 0x90010074
		opword 0xC8010070
		opword 0xEC000828
		opword 0xD01C0098
		opword 0x7F83E378
		opword 0x7F64DB78
		bl DrawSubMenuCommonProcessSub1
		opword 0x3BA00000
		opword 0x3A800000
		opword 0x93BC001C
		opword 0x3A600000
		opword 0x3A400000
		opword 0x480002A0
		opword 0x7FFC9214
		opword 0x801F0034
		opword 0x2C00000A
		opword 0x41820150
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820104
		opword 0x40800270
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000264
		opword 0x2C00000C
		opword 0x4080025C
		opword 0x4800024C
		opword 0x801F0020
		opword 0x7FD69A14
		opword 0x7FC3F378
		opword 0x60000001
		opword 0x901F0020
		opword 0x801F0020
		opword 0x60000002
		opword 0x901F0020
		bl GetRingCenter
		opword 0xC03E0000
		opword 0x38600004
		lfs f2, float_neg60_8041c16c(r2)
		opword 0x38A0000C
		opword 0x809F0048
		bl intplGetValue
		opword 0xD03E0000
		opword 0x38600004
		lfs f2, float_55_8041c170(r2)
		opword 0x38A0000C
		opword 0xC03E0004
		opword 0x809F0048
		bl intplGetValue
		opword 0xD03E0004
		opword 0x7C75A214
		lfs f1, float_20_8041c168(r2)
		opword 0xC01E0000
		opword 0xC05E0004
		opword 0xEC21002A
		opword 0xC07E0008
		bl PSMTXTrans
		lfs f1, float_0_8041c144(r2)
		opword 0x38600000
		lfs f2, float_360_8041c160(r2)
		opword 0x38A0000C
		opword 0x809F0048
		bl intplGetValue
		opword 0x7C37952E
		lfs f0, float_360_8041c160(r2)
		opword 0x7C37942E
		opword 0xFC010040
		opword 0x4081000C
		opword 0xEC010028
		opword 0x7C17952E
		opword 0x801F0048
		opword 0x2C000003
		opword 0x4180000C
		opword 0x38000001
		opword 0x901C001C
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x801F0048
		opword 0x2C00000C
		opword 0x40810180
		opword 0x38000001
		opword 0x901F0034
		opword 0x48000174
		opword 0x801F0020
		opword 0x7C75A214
		lfs f1, float_neg40_8041c184(r2)
		opword 0x60000001
		lfs f2, float_55_8041c170(r2)
		opword 0x901F0020
		lfs f3, float_0_8041c144(r2)
		opword 0x801F0020
		opword 0x60000002
		opword 0x901F0020
		bl PSMTXTrans
		lfs f0, float_360_8041c160(r2)
		opword 0x38000001
		opword 0x7C17952E
		opword 0x901C001C
		opword 0x48000134
		opword 0x801F0020
		lis r3, kakutable@ha
		opword 0x7FD69A14
		lfs f2, float_3p1416_8041c14c(r2)
		opword 0x60000001
		addi r4, r3, kakutable@l
		opword 0x901F0020
		opword 0x7FC3F378
		lfs f0, float_180_8041c150(r2)
		opword 0x801F0020
		opword 0x540007FA
		opword 0x901F0020
		opword 0x80BA0008
		opword 0x801F0084
		opword 0x1CA50014
		opword 0x5400103A
		opword 0x7C842A14
		opword 0x7C840214
		opword 0xC024FFC4
		opword 0xEC220072
		fdivs f31, f1, f0
		bl GetRingCenter
		opword 0xFC20F890
		la r3, _af_pad+4
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0x3C004330
		opword 0xC001000C
		lis r3, double_to_int_802ef198@ha
		opword 0x90010070
		opword 0xEC01002A
		lfd f3, double_to_int_802ef198@l(r3)
		lfs f4, float_0p1_8041c174(r2)
		lfs f1, float_1_8041c178(r2)
		opword 0xD01E0000
		lfs f0, float_0_8041c144(r2)
		opword 0xC0BE0004
		opword 0xC0410008
		opword 0xEC45102A
		opword 0xD05E0004
		opword 0xC0410008
		opword 0xD05E0008
		opword 0x801F0048
		opword 0x6C008000
		opword 0x90010074
		opword 0xC8410070
		opword 0xEC421828
		opword 0xEC2408BC
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		opword 0x3800000B
		opword 0x901F0034
		opword 0xFC400890
		lfs f3, float_1_8041c178(r2)
		opword 0x38610010
		bl PSMTXScale
		opword 0xC03E0000
		opword 0x38610040
		opword 0xC05E0004
		opword 0xC07E0008
		bl PSMTXTrans
		opword 0x38610040
		opword 0x38810010
		opword 0x7CB5A214
		bl PSMTXConcat
		lfs f0, float_0_8041c144(r2)
		opword 0x7C17952E
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x48000010
		opword 0x801F0020
		opword 0x5400003C
		opword 0x901F0020
		opword 0x3BBD0001
		opword 0x3A940030
		opword 0x3A73000C
		opword 0x3A520004
		opword 0x801A0008
		opword 0x7C1D0000
		opword 0x4180FD5C
		opword 0x3BE00000
		opword 0x3AA00000
		opword 0x3AC00000
		opword 0x7FDCB214
		opword 0x809E00C0
		opword 0x28040028
		opword 0x41810188
		lis r3, jumptable_80360D44@ha
		opword 0x5480103A
		addi r3, r3, jumptable_80360D44@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x809E00A4
		opword 0x381F0114
		opword 0x386000FF
		opword 0x5484003C
		opword 0x909E00A4
		opword 0x7C7C01AE
		opword 0x48000154
		opword 0x809E00A4
		opword 0x381F0114
		opword 0x386000FF
		opword 0x5484003C
		opword 0x909E00A4
		opword 0x7C7C01AE
		opword 0x809E00DC
		opword 0x2C040000
		opword 0x41800040
		opword 0x2C1F0006
		opword 0x41820038
		lfs f1, float_90_8041c158(r2)
		opword 0x38600000
		lfs f2, float_0_8041c144(r2)
		opword 0x38A0000C
		bl intplGetValue
		opword 0x801E00A4
		opword 0x7C78AA14
		lfs f0, float_0p017453_8041c164(r2)
		opword 0x38800079
		opword 0x60000001
		opword 0xEC200072
		opword 0x901E00A4
		bl PSMTXRotRad
		opword 0x807E00DC
		opword 0x38030001
		opword 0x901E00DC
		opword 0x801E00DC
		opword 0x2C00000C
		opword 0x408100DC
		opword 0x38000002
		opword 0x901E00C0
		opword 0x480000D0
		opword 0x2C1F0006
		opword 0x381F0114
		opword 0x386000FF
		opword 0x7C7C01AE
		opword 0x4182001C
		opword 0x801E00A4
		opword 0x7C78AA14
		opword 0x60000001
		opword 0x901E00A4
		bl PSMTXIdentity
		opword 0x480000A4
		opword 0x801E00A4
		opword 0x5400003C
		opword 0x901E00A4
		opword 0x48000094
		opword 0x2C04000A
		opword 0x4182000C
		opword 0x2C040014
		opword 0x40820008
		opword 0x3B20000C
		opword 0x2C04001E
		opword 0x4182000C
		opword 0x2C040028
		opword 0x40820018
		opword 0x807B0008
		opword 0x3803FFFA
		opword 0x7C000E70
		opword 0x7C600194
		opword 0x3B23000C
		opword 0x801E00A4
		opword 0x7C78AA14
		opword 0x60000001
		opword 0x901E00A4
		bl PSMTXIdentity
		opword 0xC03C009C
		opword 0x7F25CB78
		opword 0xC05C00A0
		opword 0x38600004
		opword 0x809E00DC
		bl intplGetValue
		opword 0xD03C0098
		opword 0x807E00DC
		opword 0x38030001
		opword 0x901E00DC
		opword 0x801E00DC
		opword 0x7C00C800
		opword 0x40810014
		opword 0x38600002
		opword 0x38000000
		opword 0x907E00C0
		opword 0x901E00DC
		opword 0x3BFF0001
		opword 0x3AD60004
		opword 0x2C1F0007
		opword 0x3AB50030
		opword 0x4180FE5C
	}
#endif
}
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
#ifndef NONMATCHING
#pragma pop
#endif

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

void BattleMenuDisp_ActSelect_Main(BattleWork* wp) {
}

void BattleMenuDisp_ActSelect_Disp(BattleWork* wp) {
    DrawMainMenu(wp);
}

void BattleMenuDisp_ActSelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}

#ifndef NONMATCHING
extern void* jumptable_80360D14[];
extern void* jumptable_80360D44[];
extern void* jumptable_80360DE8[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void DrawMainMenu(BattleWork* wp_) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FDD0
		opword 0x7C0802A6
		opword 0x90010234
		opword 0xDBE10220
		opword 0xF3E10228
		opword 0xDBC10210
		opword 0xF3C10218
		opword 0xBF0101F0
		lwz r4, _battleWorkPointer(r13)
		opword 0x38600008
		opword 0x83841C78
		opword 0x837C0000
		bl camGetPtr
		opword 0x801C000C
		opword 0x2C000002
		opword 0x418201A4
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x4080005C
		opword 0x480001E4
		opword 0x2C00000A
		opword 0x418201D0
		opword 0x480001D8
		opword 0x809B0008
		opword 0x38A00000
		opword 0x38600000
		opword 0x7C8903A6
		opword 0x2C040000
		opword 0x40810020
		opword 0x38030034
		opword 0x7C1C002E
		opword 0x2C000003
		opword 0x40820008
		opword 0x38A50001
		opword 0x38630004
		opword 0x4200FFE8
		opword 0x7C052000
		opword 0x4082019C
		opword 0x38000001
		opword 0x901C000C
		opword 0x48000190
		opword 0x38000001
		opword 0x981C0014
		opword 0x80BC0000
		opword 0x807C0018
		opword 0x80050000
		opword 0x7C830050
		opword 0x2C040001
		opword 0x41820018
		opword 0x80650008
		opword 0x3863FFFF
		opword 0x7C0300D0
		opword 0x7C002000
		opword 0x40820080
		opword 0x38000002
		opword 0x38C00000
		opword 0x901C000C
		opword 0x7CC83378
		opword 0x38600000
		opword 0x38A00004
		opword 0x98DC0014
		opword 0x809C0000
		opword 0x80040000
		opword 0x901C0018
		opword 0x48000044
		opword 0x7CFC1A14
		opword 0x90A70034
		opword 0x90C70048
		opword 0x80070084
		opword 0x90070070
		opword 0x80870084
		opword 0x3804FFFF
		opword 0x90070084
		opword 0x80070084
		opword 0x2C00FFFF
		opword 0x40820010
		opword 0x809B0008
		opword 0x3804FFFF
		opword 0x90070084
		opword 0x39080001
		opword 0x38630004
		opword 0x801B0008
		opword 0x7C080000
		opword 0x4180FFB8
		opword 0x480000E0
		opword 0x2C04FFFF
		opword 0x4182000C
		opword 0x7C032000
		opword 0x408200D0
		opword 0x38000002
		opword 0x38C00000
		opword 0x901C000C
		opword 0x7CC83378
		opword 0x38600000
		opword 0x38A00005
		opword 0x98DC0014
		opword 0x809C0000
		opword 0x80040000
		opword 0x901C0018
		opword 0x48000040
		opword 0x7CFC1A14
		opword 0x90A70034
		opword 0x90C70048
		opword 0x80070084
		opword 0x90070070
		opword 0x80870084
		opword 0x38040001
		opword 0x90070084
		opword 0x80870084
		opword 0x801B0008
		opword 0x7C040000
		opword 0x40820008
		opword 0x90C70084
		opword 0x39080001
		opword 0x38630004
		opword 0x801B0008
		opword 0x7C080000
		opword 0x4180FFBC
		opword 0x48000058
		opword 0x809B0008
		opword 0x38A00000
		opword 0x38600000
		opword 0x7C8903A6
		opword 0x2C040000
		opword 0x40810020
		opword 0x38030034
		opword 0x7C1C002E
		opword 0x2C000003
		opword 0x40820008
		opword 0x38A50001
		opword 0x38630004
		opword 0x4200FFE8
		opword 0x7C052000
		opword 0x4082001C
		opword 0x38000001
		opword 0x901C000C
		opword 0x48000010
		opword 0x38000001
		opword 0x901C000C
		opword 0x981C0014
		opword 0x3BA00000
		opword 0x3B400000
		opword 0x93BC001C
		opword 0x3B200000
		opword 0x3B000000
		opword 0x480007F4
		opword 0x7FFCC214
		opword 0x801F0034
		opword 0x2800000B
		opword 0x418107D4
		lis r3, jumptable_80360D14@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80360D14@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x807F0048
		opword 0x3803FFFF
		opword 0x901F0048
		opword 0x801F0048
		opword 0x2C000000
		opword 0x418107A4
		opword 0x38600001
		opword 0x38000000
		opword 0x907F0034
		opword 0x901F0048
		opword 0x48000790
		opword 0x801F0020
		lis r3, kakutable@ha
		opword 0x3CA04330
		lis r4, double_to_int_802ef198@ha
		opword 0x60000001
		addi r3, r3, kakutable@l
		opword 0x901F0020
		addi r7, r4, double_to_int_802ef198@l
		lfs f2, float_3p1416_8041c14c(r2)
		opword 0x809B0008
		opword 0x801F0084
		opword 0x1C840014
		opword 0x80DF0048
		opword 0x5400103A
		lfs f0, float_180_8041c150(r2)
		opword 0x6CC68000
		opword 0x90A101E0
		opword 0x7C632214
		opword 0x90C101E4
		opword 0x7C630214
		opword 0xC8870000
		opword 0xC023FFC4
		opword 0xC86101E0
		opword 0xEC220072
		lfs f5, float_0p2_8041c148(r2)
		opword 0xEC632028
		lfs f2, float_0_8041c144(r2)
		opword 0xEFC10024
		opword 0xEFE510FA
		opword 0xFC1FF040
		opword 0x4C411382
		opword 0x40820008
		opword 0xFFE0F090
		opword 0x3BC100B4
		opword 0x7FDECA14
		opword 0x7FC3F378
		bl GetRingCenter
		opword 0xFC20F890
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0xC001000C
		opword 0xC0410008
		opword 0xEC01002A
		opword 0xD01E0000
		opword 0xC01E0004
		opword 0xEC00102A
		opword 0xD01E0004
		opword 0xD05E0008
		opword 0x801B0000
		opword 0x7C1D0000
		opword 0x408200A8
		opword 0x809F0048
		opword 0x3C004330
		opword 0x900101E0
		lis r3, double_to_int_802ef198@ha
		opword 0x6C808000
		lfd f2, double_to_int_802ef198@l(r3)
		opword 0x900101E4
		lfs f3, float_90_8041c158(r2)
		opword 0xC80101E0
		lfs f1, float_10_8041c15c(r2)
		opword 0xEC401028
		lfs f4, float_270_8041c154(r2)
		lfs f0, float_360_8041c160(r2)
		opword 0xEC4300B2
		opword 0xEC220824
		opword 0xEC24082A
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f1, float_0_8041c144(r2)
		lfs f0, float_0p017453_8041c164(r2)
		opword 0x38610054
		opword 0x38800078
		opword 0xEC200072
		bl PSMTXRotRad
		lfs f1, float_20_8041c168(r2)
		opword 0x38610084
		opword 0xC01E0000
		opword 0xC05E0004
		opword 0xEC21002A
		opword 0xC07E0008
		bl PSMTXTrans
		opword 0x38A100F0
		opword 0x38610084
		opword 0x38810054
		opword 0x7CA5D214
		bl PSMTXConcat
		opword 0x801F0020
		opword 0x60000002
		opword 0x901F0020
		opword 0x48000090
		opword 0x809F0048
		opword 0x3C004330
		opword 0x900101E0
		lis r3, double_to_int_802ef198@ha
		opword 0x6C808000
		lfd f2, double_to_int_802ef198@l(r3)
		opword 0x900101E4
		lfs f3, float_90_8041c158(r2)
		opword 0xC80101E0
		lfs f1, float_10_8041c15c(r2)
		opword 0xEC401028
		lfs f4, float_270_8041c154(r2)
		lfs f0, float_360_8041c160(r2)
		opword 0xEC4300B2
		opword 0xEC220824
		opword 0xEC24082A
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		lfs f1, float_0_8041c144(r2)
		lfs f0, float_0p017453_8041c164(r2)
		opword 0x38610054
		opword 0x38800078
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0xC03E0000
		opword 0x38610084
		opword 0xC05E0004
		opword 0xC07E0008
		bl PSMTXTrans
		opword 0x38A100F0
		opword 0x38610084
		opword 0x38810054
		opword 0x7CA5D214
		bl PSMTXConcat
		opword 0xFC1FF040
		lfs f0, float_0_8041c144(r2)
		opword 0x38610010
		opword 0x7C03C52E
		opword 0x4C411382
		opword 0x40820020
		opword 0x801F0048
		opword 0x2C00000A
		opword 0x41800014
		opword 0x38600003
		opword 0x3800FFFF
		opword 0x907F0034
		opword 0x901F0048
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x48000548
		opword 0x1C840014
		opword 0x801F0084
		lis r3, kakutable@ha
		lfs f2, float_3p1416_8041c14c(r2)
		opword 0x3BC100B4
		lfs f0, float_180_8041c150(r2)
		addi r3, r3, kakutable@l
		opword 0x5400103A
		opword 0x7C632214
		opword 0x7FDECA14
		opword 0x7C630214
		opword 0xC023FFC4
		opword 0x7FC3F378
		opword 0xEC220072
		opword 0xEFC10024
		bl GetRingCenter
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0xC001000C
		opword 0xC0410008
		opword 0xEC01002A
		opword 0xD01E0000
		opword 0xC01E0004
		opword 0xEC00102A
		opword 0xD01E0004
		opword 0xD05E0008
		opword 0x801B0000
		opword 0x7C1D0000
		opword 0x40820034
		lfs f1, float_20_8041c168(r2)
		opword 0x386100F0
		opword 0xC01E0000
		opword 0x7C63D214
		opword 0xC05E0004
		opword 0xEC21002A
		opword 0xC07E0008
		bl PSMTXTrans
		opword 0x801F0020
		opword 0x60000002
		opword 0x901F0020
		opword 0x4800001C
		opword 0x386100F0
		opword 0xC03E0000
		opword 0xC05E0004
		opword 0x7C63D214
		opword 0xC07E0008
		bl PSMTXTrans
		lfs f0, float_0_8041c144(r2)
		opword 0x38610010
		opword 0x7C03C52E
		opword 0x48000470
		opword 0x801F0084
		opword 0x1CC40014
		lis r5, kakutable@ha
		opword 0x809F0070
		opword 0x5403103A
		lfs f0, float_0_8041c144(r2)
		addi r0, r5, kakutable@l
		opword 0x7CA03214
		opword 0x3803FFC4
		opword 0x7C65042E
		opword 0x5483103A
		opword 0x3803FFC4
		opword 0xFC001800
		opword 0x7C25042E
		opword 0x40820008
		lfs f3, float_360_8041c160(r2)
		lfs f0, float_3p1416_8041c14c(r2)
		opword 0x3C004330
		opword 0x807F0048
		lis r4, double_to_int_802ef198@ha
		opword 0xEC200072
		lfs f2, float_180_8041c150(r2)
		opword 0xEC0000F2
		opword 0x6C638000
		opword 0x906101E4
		opword 0xEC211024
		opword 0x900101E0
		lfd f4, double_to_int_802ef198@l(r4)
		opword 0xC86101E0
		lfs f5, float_0p2_8041c148(r2)
		opword 0xEC632028
		opword 0xEC001024
		opword 0xEFC508FA
		opword 0xFC1E0040
		opword 0x4C411382
		opword 0x40820018
		opword 0x38000003
		opword 0xFFC00090
		opword 0x901F0034
		opword 0x3800FFFF
		opword 0x901F0048
		opword 0x3BC100B4
		opword 0x7FDECA14
		opword 0x7FC3F378
		bl GetRingCenter
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0x386100F0
		opword 0xC001000C
		opword 0x7C63D214
		opword 0xC0410008
		opword 0xEC01002A
		opword 0xD01E0000
		opword 0xC01E0004
		opword 0xEC00102A
		opword 0xD01E0004
		opword 0xD05E0008
		opword 0xC03E0000
		opword 0xC05E0004
		opword 0xC07E0008
		bl PSMTXTrans
		lfs f0, float_0_8041c144(r2)
		opword 0x38610010
		opword 0x7C03C52E
		opword 0x801F0020
		opword 0x540007FA
		opword 0x901F0020
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x48000348
		opword 0x801F0070
		opword 0x1CA40014
		lis r4, kakutable@ha
		lfs f0, float_0_8041c144(r2)
		opword 0x5403103A
		addi r0, r4, kakutable@l
		opword 0x7CE02A14
		opword 0x3803FFC4
		opword 0x7C27042E
		opword 0xFC000800
		opword 0x40820008
		lfs f1, float_360_8041c160(r2)
		opword 0x801F0084
		opword 0x3C804330
		lfs f3, float_3p1416_8041c14c(r2)
		lis r5, double_to_int_802ef198@ha
		opword 0x5403103A
		lfs f2, float_180_8041c150(r2)
		opword 0x3803FFC4
		opword 0xEC230072
		opword 0x7C07042E
		opword 0x80DF0048
		opword 0xEC030032
		opword 0x908101E0
		opword 0xEC211024
		opword 0x6CC38000
		opword 0x906101E4
		lfd f5, double_to_int_802ef198@l(r5)
		opword 0xC88101E0
		lfs f6, float_0p2_8041c148(r2)
		opword 0xEC642828
		opword 0xEC001024
		opword 0xEFC608FC
		opword 0xFC1E0040
		opword 0x4C401382
		opword 0x40820018
		opword 0x38000003
		opword 0xFFC00090
		opword 0x901F0034
		opword 0x3800FFFF
		opword 0x901F0048
		opword 0x3BC100B4
		opword 0x7FDECA14
		opword 0x7FC3F378
		bl GetRingCenter
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0x386100F0
		opword 0xC001000C
		opword 0x7C63D214
		opword 0xC0410008
		opword 0xEC01002A
		opword 0xD01E0000
		opword 0xC01E0004
		opword 0xEC00102A
		opword 0xD01E0004
		opword 0xD05E0008
		opword 0xC03E0000
		opword 0xC05E0004
		opword 0xC07E0008
		bl PSMTXTrans
		lfs f0, float_0_8041c144(r2)
		opword 0x38610010
		opword 0x7C03C52E
		opword 0x801F0020
		opword 0x540007FA
		opword 0x901F0020
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x48000220
		opword 0x801F0020
		opword 0x3BC100B4
		opword 0x7FDECA14
		opword 0x60000001
		opword 0x901F0020
		opword 0x7FC3F378
		opword 0x801F0020
		opword 0x60000002
		opword 0x901F0020
		bl GetRingCenter
		lfs f1, float_0_8041c144(r2)
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0x38600004
		opword 0xC001000C
		opword 0x38A0000C
		opword 0xC0410008
		opword 0xEC01002A
		lfs f1, float_neg60_8041c16c(r2)
		opword 0xD01E0000
		opword 0xC01E0004
		opword 0xEC00102A
		opword 0xD01E0004
		opword 0xD05E0008
		opword 0xC05E0000
		opword 0x809F0048
		bl intplGetValue
		opword 0xD03E0000
		opword 0x38600004
		lfs f1, float_55_8041c170(r2)
		opword 0x38A0000C
		opword 0xC05E0004
		opword 0x809F0048
		bl intplGetValue
		opword 0xD03E0004
		opword 0x386100F0
		lfs f1, float_20_8041c168(r2)
		opword 0x7C63D214
		opword 0xC01E0000
		opword 0xC05E0004
		opword 0xEC21002A
		opword 0xC07E0008
		bl PSMTXTrans
		lfs f1, float_360_8041c160(r2)
		opword 0x38600000
		lfs f2, float_0_8041c144(r2)
		opword 0x38A0000C
		opword 0x809F0048
		bl intplGetValue
		opword 0x38610010
		opword 0x7C23C52E
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x801F0048
		opword 0x2C00000C
		opword 0x40810134
		opword 0x38000003
		opword 0x901F0034
		opword 0x48000128
		opword 0x801F0020
		lis r3, kakutable@ha
		opword 0x3BC100B4
		lfs f2, float_3p1416_8041c14c(r2)
		opword 0x60000001
		addi r4, r3, kakutable@l
		opword 0x901F0020
		opword 0x7FDECA14
		lfs f0, float_180_8041c150(r2)
		opword 0x7FC3F378
		opword 0x801F0020
		opword 0x540007FA
		opword 0x901F0020
		opword 0x80BB0008
		opword 0x801F0084
		opword 0x1CA50014
		opword 0x5400103A
		opword 0x7C842A14
		opword 0x7C840214
		opword 0xC024FFC4
		opword 0xEC220072
		opword 0xEFC10024
		bl GetRingCenter
		opword 0xFC20F090
		opword 0x3861000C
		opword 0x38810008
		bl GetRingOffset
		opword 0xC03E0000
		opword 0x3C004330
		opword 0xC001000C
		lis r3, double_to_int_802ef198@ha
		opword 0xC0810008
		opword 0xEC01002A
		opword 0x900101E0
		lfd f2, double_to_int_802ef198@l(r3)
		lfs f3, float_0p1_8041c174(r2)
		opword 0xD01E0000
		lfs f0, float_1_8041c178(r2)
		opword 0xC03E0004
		opword 0xEC21202A
		opword 0xD03E0004
		opword 0xD09E0008
		opword 0x801F0048
		opword 0x6C008000
		opword 0x900101E4
		opword 0xC82101E0
		opword 0xEC211028
		opword 0xEC230072
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000003
		opword 0x901F0034
		opword 0xFC400890
		lfs f3, float_1_8041c178(r2)
		opword 0x38610024
		bl PSMTXScale
		opword 0xC03E0000
		opword 0x38610084
		opword 0xC05E0004
		opword 0xC07E0008
		bl PSMTXTrans
		opword 0x38A100F0
		opword 0x38610084
		opword 0x38810024
		opword 0x7CA5D214
		bl PSMTXConcat
		lfs f0, float_0_8041c144(r2)
		opword 0x38610010
		opword 0x7C03C52E
		opword 0x807F0048
		opword 0x38030001
		opword 0x901F0048
		opword 0x3BBD0001
		opword 0x3B5A0030
		opword 0x3B39000C
		opword 0x3B180004
		opword 0x809B0008
		opword 0x7C1D2000
		opword 0x4180F808
		opword 0x809C0004
		opword 0x7F83E378
		opword 0x38A100F0
		opword 0x38C100B4
		opword 0x38E10010
		bl DrawMainIcon
		bl DrawMenuPartyChangeButton
		bl DrawMenuPinchMark
		opword 0xE3E10228
		opword 0xCBE10220
		opword 0xE3C10218
		opword 0xCBC10210
		opword 0xBB0101F0
		opword 0x80010234
		opword 0x7C0803A6
		opword 0x38210230
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

void BattleMenuDisp_WeaponSelect_Main(BattleWork* wp) {
}

void BattleMenuDisp_WeaponSelect_Disp(BattleWork* wp) {
    DrawWeaponWin();
}

void BattleMenuDisp_WeaponSelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void DrawWeaponWin(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[824];
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		opword 0x839F1C78
		opword 0x3BBF171C
		opword 0x809F0420
		opword 0x7FE3FB78
		opword 0x837C0000
		bl BattleGetUnitPtr
		opword 0x801B0000
		opword 0x7C7A1B78
		opword 0x80DC0008
		la r3, _af_pad+12
		opword 0x1C00001C
		opword 0x38810010
		opword 0x38A100F4
		opword 0x38E100A4
		opword 0x7F26002E
		opword 0x38C100B8
		opword 0x390101E4
		bl DrawSubMenuCommonProcess
		opword 0x3B000000
		opword 0x3AE00000
		li r22, 0x0
		opword 0xC01C0098
		opword 0x801B0008
		opword 0xFC00001E
		opword 0xD8010338
		opword 0x8061033C
		opword 0x7C63C214
		opword 0x7C030000
		opword 0x4080009C
		opword 0x1FC3001C
		opword 0x80BC0008
		opword 0x38C10088
		opword 0x38810024
		opword 0x381E0004
		opword 0x3861006C
		opword 0x7CE5002E
		opword 0x38BE008C
		opword 0x381E0008
		opword 0x7CE6B12E
		opword 0x7CBD2A2E
		opword 0x7CA4BB2E
		opword 0x809C0008
		opword 0x7C04002E
		opword 0x7C03B12E
		opword 0x807C0008
		opword 0x7C83F02E
		opword 0x28040000
		opword 0x41820018
		opword 0x7F43D378
		bl BtlUnit_GetWeaponCost
		opword 0x38810050
		opword 0x7C64B12E
		opword 0x48000010
		opword 0x38610050
		opword 0x38000000
		opword 0x7C03B12E
		opword 0x807C0008
		opword 0x7C63F02E
		opword 0x28030000
		opword 0x41820014
		opword 0x88030012
		opword 0x38610034
		opword 0x7C03B12E
		opword 0x48000010
		opword 0x38610034
		opword 0x38000000
		opword 0x7C03B12E
		opword 0x3B180001
		opword 0x3AD60004
		opword 0x2C180007
		opword 0x3AF70002
		opword 0x4180FF38
		opword 0x7F83E378
		opword 0x389F1724
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		bl DrawMainIcon
		opword 0x38000000
		opword 0x7F83E378
		opword 0x90010008
		opword 0x388101E4
		opword 0x38A10088
		opword 0x38C10024
		opword 0x38E1006C
		opword 0x39010050
		opword 0x39210034
		opword 0x39400000
		bl DrawSubIcon
		lis r4, vec3_802ef168@ha
		opword 0x38610018
		addi r6, r4, vec3_802ef168@l
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90010020
		bl DrawMenuCursorAndScrollArrow
		opword 0x28190000
		opword 0x4182006C
		opword 0x80190008
		opword 0x2C000000
		opword 0x4182001C
		opword 0x1C000028
		lis r3, itemDataTable@ha
		addi r3, r3, itemDataTable@l
		opword 0x7C630214
		opword 0x80630008
		opword 0x48000070
		lis r3, ItemWeaponData_CookingItem@ha
		addi r0, r3, ItemWeaponData_CookingItem@l
		opword 0x7C190040
		opword 0x40820030
		opword 0x801B0000
		lis r4, itemDataTable@ha
		opword 0x807C0008
		addi r4, r4, itemDataTable@l
		opword 0x1C00001C
		opword 0x7C630214
		opword 0x80030014
		opword 0x1C000028
		opword 0x7C640214
		opword 0x80630008
		opword 0x48000034
		opword 0x8079000C
		opword 0x4800002C
		opword 0x801B0000
		lis r4, itemDataTable@ha
		opword 0x807C0008
		addi r4, r4, itemDataTable@l
		opword 0x1C00001C
		opword 0x7C630214
		opword 0x80030014
		opword 0x1C000028
		opword 0x7C640214
		opword 0x80630008
		opword 0x28030000
		opword 0x41820010
		opword 0xC0210014
		opword 0xC0410010
		bl DrawMenuHelpWin
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

void BattleMenuDisp_Operation_Main(BattleWork* wp) {
}

void BattleMenuDisp_Operation_Disp(BattleWork* wp) {
    DrawOperationWin();
}

void BattleMenuDisp_Operation_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void DrawOperationWin(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[816];
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		opword 0x83DF1C78
		opword 0x7FE3FB78
		opword 0x809F0420
		opword 0x83BE0000
		bl BattleGetUnitPtr
		addi r28, r31, 0x19e8
		la r3, _af_pad+12
		opword 0x38810010
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		opword 0x390101E4
		bl DrawSubMenuCommonProcess
		opword 0x38000007
		opword 0x39400000
		opword 0x38600000
		opword 0x38800000
		opword 0x38A00000
		opword 0x7C0903A6
		opword 0xC01E0098
		opword 0x801D0008
		opword 0xFC00001E
		opword 0xD8010338
		opword 0x80C1033C
		opword 0x7CC65214
		opword 0x7C060000
		opword 0x40800068
		opword 0x1CE6001C
		opword 0x38C10088
		opword 0x38040010
		opword 0x7D3C3A14
		opword 0x80E90004
		opword 0x7CE6292E
		opword 0x7C1C022E
		opword 0x28000000
		opword 0x41820014
		opword 0xA0090010
		opword 0x38C10024
		opword 0x7C061B2E
		opword 0x48000010
		opword 0x38C10024
		opword 0x3800018B
		opword 0x7C061B2E
		opword 0x8009000C
		opword 0x3901006C
		opword 0x38E10050
		opword 0x38C10034
		opword 0x7C08292E
		opword 0x38000000
		opword 0x81090018
		opword 0x7D07292E
		opword 0x7C06292E
		opword 0x394A0001
		opword 0x38630002
		opword 0x3884001C
		opword 0x38A50004
		opword 0x4200FF6C
		opword 0x7FC3F378
		opword 0x389F1724
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		bl DrawMainIcon
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x90010008
		opword 0x388101E4
		opword 0x38A10088
		opword 0x38C10024
		opword 0x38E1006C
		opword 0x39010050
		opword 0x39210034
		opword 0x39400000
		bl DrawSubIcon
		lis r4, vec3_802ef174@ha
		opword 0x38610018
		addi r6, r4, vec3_802ef174@l
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90010020
		bl DrawMenuCursorAndScrollArrow
		opword 0x801D0000
		opword 0x1C00001C
		opword 0x7C7C0214
		opword 0x80630014
		opword 0x28030000
		opword 0x41820010
		opword 0xC0210014
		opword 0xC0410010
		bl DrawMenuHelpWin
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

void BattleMenuDisp_ChangePartySelect_Main(BattleWork* wp) {
}

void BattleMenuDisp_ChangePartySelect_Disp(BattleWork* wp) {
    DrawChangePartyWin();
}

void BattleMenuDisp_ChangePartySelect_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void DrawChangePartyWin(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[816];
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		opword 0x83DF1C78
		opword 0x7FE3FB78
		opword 0x809F0420
		opword 0x83BE0000
		bl BattleGetUnitPtr
		addi r28, r31, 0x1aac
		la r3, _af_pad+12
		opword 0x38810010
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		opword 0x390101E4
		bl DrawSubMenuCommonProcess
		opword 0x38000007
		opword 0x39200000
		opword 0x38600000
		opword 0x38800000
		opword 0x7C0903A6
		opword 0xC01E0098
		opword 0x801D0008
		opword 0xFC00001E
		opword 0xD8010338
		opword 0x80A1033C
		opword 0x7CA54A14
		opword 0x7C050000
		opword 0x4080005C
		opword 0x1C050018
		opword 0x38A10088
		opword 0x7CDC0214
		opword 0x80060004
		opword 0x7C05212E
		opword 0xA006000C
		opword 0x28000000
		opword 0x41820010
		opword 0x38A10024
		opword 0x7C051B2E
		opword 0x48000010
		opword 0x38A10024
		opword 0x3800018B
		opword 0x7C051B2E
		opword 0x81060008
		opword 0x38E1006C
		opword 0x38C10050
		opword 0x38000000
		opword 0x38A10034
		opword 0x7D07212E
		opword 0x7C06212E
		opword 0x7C05212E
		opword 0x39290001
		opword 0x38630002
		opword 0x38840004
		opword 0x4200FF7C
		opword 0x7FC3F378
		opword 0x389F1724
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		bl DrawMainIcon
		opword 0x38000001
		opword 0x7FC3F378
		opword 0x90010008
		opword 0x7F8AE378
		opword 0x388101E4
		opword 0x38A10088
		opword 0x38C10024
		opword 0x38E1006C
		opword 0x39010050
		opword 0x39210034
		bl DrawSubIcon
		lis r4, vec3_802ef180@ha
		opword 0x38610018
		addi r6, r4, vec3_802ef180@l
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90010020
		bl DrawMenuCursorAndScrollArrow
		opword 0x801D0000
		opword 0x1C000018
		opword 0x7C7C0214
		opword 0x80630010
		opword 0x28030000
		opword 0x41820010
		opword 0xC0210014
		opword 0xC0410010
		bl DrawMenuHelpWin
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

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

void BattleMenuDisp_MultiItem_Main(BattleWork* wp) {
}

void BattleMenuDisp_MultiItem_Disp(BattleWork* wp) {
    DrawMultiItemWin();
}

void BattleMenuDisp_MultiItem_End(BattleWork* wp) {
    if (WP_SUBMENU(wp)) {
        BattleFree(WP_SUBMENU(wp));
        WP_SUBMENU(wp) = NULL;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void DrawMultiItemWin(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[816];
	asm volatile {
		lwz r31, _battleWorkPointer(r13)
		opword 0x83DF1C78
		opword 0x7FE3FB78
		opword 0x809F0420
		opword 0x83BE0000
		bl BattleGetUnitPtr
		addi r28, r31, 0x1b6c
		la r3, _af_pad+12
		opword 0x38810010
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		opword 0x390101E4
		bl DrawSubMenuCommonProcess
		opword 0x38000007
		opword 0x39200000
		opword 0x38600000
		opword 0x38800000
		opword 0x7C0903A6
		opword 0xC01E0098
		opword 0x801D0008
		opword 0xFC00001E
		opword 0xD8010338
		opword 0x80A1033C
		opword 0x7CA54A14
		opword 0x7C050000
		opword 0x40800060
		opword 0x1C050018
		opword 0x38A10088
		opword 0x7D1C0214
		opword 0x80080000
		opword 0x7C05212E
		opword 0xA008000C
		opword 0x28000000
		opword 0x41820010
		opword 0x38A10024
		opword 0x7C051B2E
		opword 0x48000010
		opword 0x38A10024
		opword 0x3800018B
		opword 0x7C051B2E
		opword 0x80080004
		opword 0x38E1006C
		opword 0x38C10050
		opword 0x38A10034
		opword 0x7C07212E
		opword 0x38000000
		opword 0x80E80010
		opword 0x7CE6212E
		opword 0x7C05212E
		opword 0x39290001
		opword 0x38630002
		opword 0x38840004
		opword 0x4200FF78
		opword 0x7FC3F378
		opword 0x389F1724
		opword 0x38A100F4
		opword 0x38C100B8
		opword 0x38E100A4
		bl DrawMainIcon
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x90010008
		opword 0x388101E4
		opword 0x38A10088
		opword 0x38C10024
		opword 0x38E1006C
		opword 0x39010050
		opword 0x39210034
		opword 0x39400000
		bl DrawSubIcon
		lis r4, vec3_802ef18c@ha
		opword 0x38610018
		addi r6, r4, vec3_802ef18c@l
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90010020
		bl DrawMenuCursorAndScrollArrow
		opword 0x801D0000
		opword 0x1C000018
		opword 0x7C7C0214
		opword 0x80630008
		opword 0x28030000
		opword 0x41820010
		opword 0xC0210014
		opword 0xC0410010
		bl DrawMenuHelpWin
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif


#ifndef NONMATCHING
__declspec(section ".sdata") u32 gap_07_80410F74_sdata[1] = {0};

// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const u32 dat_802ef068[32] = {0xC1A00000, 0x42200000, 0x00000000, 0x42200000, 0x00000000, 0x41A00000, 0xC1A00000, 0x41A00000, 0x41A00000, 0x42200000, 0x41A00000, 0x41A00000, 0x00000000, 0x41A00000, 0x00000000, 0x42200000, 0xC1A00000, 0x41A00000, 0x00000000, 0x41A00000, 0x00000000, 0x00000000, 0xC1A00000, 0x00000000, 0x00000000, 0x41A00000, 0x41A00000, 0x41A00000, 0x41A00000, 0x00000000, 0x00000000, 0x00000000};
__declspec(section ".rodata") const u32 dat_802ef0e8[32] = {0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000};
__declspec(section ".rodata") const f32 vec3_802ef168[3] = {-60.0f, 35.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ef174[3] = {-60.0f, 35.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ef180[3] = {-60.0f, 35.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ef18c[3] = {-60.0f, 35.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802ef198 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802EF1A0[28] = "\x82\xb9\x82\xc2\x82\xdf\x82\xa2\x82\xcd\x81@\x82\xc8\x82\xa2\x82\xcc\x82\xbe\x81I\x81I\0\0\0";
__declspec(section ".rodata") const char str_802EF1BC[28] = "SFX_BTL_SYS_CAUTION_THROW1\0";
__declspec(section ".rodata") const char str_802EF1D8[20] = "btl_cost_disp_FP\0\0\0";
__declspec(section ".rodata") const char str_802EF1EC[20] = "btl_cost_disp_AP\0\0\0";
__declspec(section ".rodata") const char str_802EF200[12] = "btl_disp_HP";
__declspec(section ".rodata") const char str_802EF20C[16] = "btl_disp_slash\0";
__declspec(section ".rodata") const u32 gap_04_802EF21C_rodata = 0x00000000;
__declspec(section ".rodata") const f64 double_to_int_mask_802ef220 = 4503599627370496.0;
__declspec(section ".rodata") const char str_802EF228[36] = "%s/battle/common/battle_common.tpl\0";
__declspec(section ".rodata") const u32 gap_04_802EF24C_rodata = 0x00000000;
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

// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* jumptable_80360D14[] = {
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
__declspec(section ".data") void* jumptable_80360D44[] = {
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
__declspec(section ".data") void* jumptable_80360DE8[] = {
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
#endif
// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80360E8C_data[1] = {0};
#ifdef NONMATCHING
__declspec(section ".sdata") u32 gap_07_80410F74_sdata[1] = {0};
#endif
