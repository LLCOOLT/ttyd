#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>
#include "icon_ids.h"

#pragma optimize_for_size on

void BattleAcDrawGauge(s32 x, s32 y, s32 icon, f32 ratio, s32 a, s32 b, s32 c, s32 d, s32 e);
void BattleAcGaugeSeInit(void);
void BattleAcGaugeSeUpdate(f32 value);
void BattleAcGaugeSeDelete(void);

#define ACW(ac, T, off) (*(T*)((u8*)(ac) + (off)))

// static data from inlined header functions
__declspec(section ".data") s32 air_lbl_0[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 air_negone_one_374[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 air_lbl_1[] = {1065353216, -1082130432};
__declspec(section ".data") s32 air_one_negone_373[] = {1065353216, -1082130432};
__declspec(section ".data") s32 air_lbl_2[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 air_negone_one_360[] = {-1082130432, 1065353216};
__declspec(section ".data") s32 air_lbl_3[] = {1065353216, -1082130432};
__declspec(section ".data") s32 air_one_negone_359[] = {1065353216, -1082130432};

typedef struct GaugeKey {
    s32 frame;
    f32 value;
    s32 flag;
} GaugeKey;

#define GAUGE_TABLE {{0, 0.0f, 1}, {20, 1.0f, 1}, {40, 1.0f, 1}, {80, 0.0f, 0}, {-1, -1.0f, 0}}
GaugeKey _table_0[5] = GAUGE_TABLE;
GaugeKey _table_1[5] = GAUGE_TABLE;
GaugeKey _table_2[5] = GAUGE_TABLE;
GaugeKey _table_3[5] = GAUGE_TABLE;
GaugeKey _table_4[5] = GAUGE_TABLE;
GaugeKey _table_5[5] = GAUGE_TABLE;
GaugeKey _table_6[5] = GAUGE_TABLE;

typedef struct AirPw {
    s32 frame;
    f32 gauge;
    s32 hit;
    u32 hold;
    s32 flag;
} AirPw;

typedef struct AirDisp {
    u8 pad[0x28];
    f32 ratio;
} AirDisp;

static void actionCommandDisp(f32 x, f32 y);
f32 _GetGaugeDecValue(void);

s32 battleAcMain_AirGauge(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    u8* pw = (u8*)ac + 0x2BC;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)ac + 0x290);

    switch (ac->mAcState) {
        case 0:
            memset(disp, 0, 0x2C);
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            *(s32*)&disp->field_0x1C[4] = 20;
            ACW(disp, f32, 0x28) = 0.0f;
            *(GXColor*)&disp->field_0x0[0xC] = (GXColor){255, 255, 255, 255};
            ACW(pw, s32, 0) = 0;
            ac->outputParams[0] = 0;
            ac->outputParams[2] = 0;
            ac->outputParams[1] = 0;
            ac->mAcState = 99;
            ac->result = 1;
            ACW(pw, f32, 4) = 0.0f;
            ACW(pw, s32, 8) = 0;
            ACW(pw, s32, 0xC) = 0;
            ACW(pw, s32, 0x10) = 0;
            break;
        case 99:
            break;
        case 100:
            if ((ac->setupFlags & 1) && (ac->mAcUnit->mTokenFlags & 0x10)) {
                if (irand(100) >= 0) {
                    ac->setupParam = ACW(ac, s32, 0x44) / 2;
                    ac->outputParams[0] = 0;
                    ac->outputParams[2] = 0;
                } else {
                    s32 v = irand(ACW(ac, s32, 0x40) - 1) + 1;
                    ac->outputParams[0] = v;
                    switch (v) {
                        case 1:
                            ac->setupParam = ACW(ac, s32, 0x44) - 1;
                            break;
                        case 2:
                            ac->setupParam = ACW(ac, s32, 0x48) - 1;
                            break;
                        case 3:
                            ac->setupParam = ACW(ac, s32, 0x4C) - 1;
                            break;
                        case 4:
                        default:
                            ac->setupParam = ACW(ac, s32, 0x4C) + 1;
                            break;
                    }
                    ac->outputParams[2] = 100;
                }
                ac->mAcState = 1001;
                break;
            }
            BattleAcGaugeSeInit();
            ac->mAcState = 1000;
        case 1000:
            ACW(pw, s32, 0)++;
            if (((s32(*)(s32))BattlePadCheckNow)(0x100)) {
                ac->outputParams[1] = 1;
                if (((s32(*)(s32))BattlePadCheckTrigger)(0x100)) {
                    ACW(pw, s32, 8)++;
                    ACW(pw, s32, 0xC) = 0;
                }
                ACW(pw, s32, 0xC)++;
            } else {
                ac->outputParams[1] = 0;
                ACW(pw, s32, 0xC) = 0;
            }
            ACW(pw, f32, 4) -= _GetGaugeDecValue();
            if (ac->mAcUnit->badgesEquipped.AutoCommand) {
                ACW(pw, s32, 8) = 1;
                ACW(pw, f32, 4) = 100.0f;
            }
            if (ACW(pw, f32, 4) < 0.0f) {
                ACW(pw, f32, 4) = 0.0f;
            }
            if (ACW(pw, f32, 4) > 100.0f) {
                ACW(pw, f32, 4) = 100.0f;
            }
            BattleAcGaugeSeUpdate(ACW(pw, f32, 4));
            if (ACW(pw, s32, 0) >= ACW(ac, s32, 0x3C)) {
                if (ac->mAcUnit->badgesEquipped.AutoCommand) {
                    ACW(pw, s32, 8) = 1;
                    ACW(pw, f32, 4) = 100.0f;
                }
                if (!ACW(pw, u32, 8)) {
                    ac->outputParams[0] = 0;
                    ac->outputParams[2] = 0;
                    ac->result = 0;
                    BattleAcGaugeSeDelete();
                    return 0;
                }
                ac->result = 2;
                ac->mResultCount++;
                if (ACW(pw, f32, 4) < (f32)ACW(ac, s32, 0x44)) {
                    ac->outputParams[0] = 1;
                } else if (ACW(ac, s32, 0x40) <= 2) {
                    ac->outputParams[0] = 2;
                } else if (ACW(pw, f32, 4) < (f32)ACW(ac, s32, 0x48)) {
                    ac->outputParams[0] = 2;
                } else if (ACW(ac, s32, 0x40) <= 3) {
                    ac->outputParams[0] = 3;
                } else if (ACW(pw, f32, 4) < (f32)ACW(ac, s32, 0x4C)) {
                    ac->outputParams[0] = 3;
                } else if (ACW(ac, s32, 0x40) <= 4) {
                    ac->outputParams[0] = 4;
                } else if (ACW(pw, f32, 4) < (f32)ACW(ac, s32, 0x50)) {
                    ac->outputParams[0] = 4;
                } else {
                    ac->outputParams[0] = 5;
                }
                ac->outputParams[2] = (s32)ACW(pw, f32, 4);
                ac->mAcState = 1002;
            }
            break;
        case 1001:
            ac->setupParam--;
            if (ac->setupParam < 0) {
                if ((s32)ac->outputParams[0] > 0) {
                    ac->result = 2;
                    ac->mResultCount++;
                } else {
                    ac->result = 0;
                }
                return 0;
            }
            break;
        case 1002:
            BattleAcGaugeSeDelete();
            ACW(pw, s32, 0x14) = 60;
            ac->mAcState = 1003;
        case 1003:
            ACW(pw, s32, 0x14)--;
            if (ACW(pw, s32, 0x14) <= 0) {
                ac->mAcState = 1004;
            }
            break;
        case 1004:
            ac->maincb = NULL;
            ac->dispcb = NULL;
            ac->resultcb = NULL;
            ac->deletecb = NULL;
            return 0;
    }
    return 1;
}

f32 _GetGaugeDecValue(void) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    AirPw* pw = (AirPw*)((u8*)ac + 0x2BC);
    GaugeKey* t;
    f32 base;
    u32 frame;

    switch (ACW(ac, u32, 0x54)) {
        case 0: base = 0.3f; t = _table_0; break;
        case 1: base = 0.33f; t = _table_1; break;
        case 2: base = 0.36f; t = _table_2; break;
        case 3: base = 0.4f; t = _table_3; break;
        case 4: base = 0.44f; t = _table_4; break;
        case 5: base = 0.47f; t = _table_5; break;
        case 6:
        default: t = _table_6; base = 0.5f; break;
    }
    while (pw->hold > t->frame) {
        t++;
        if (t->frame < 0) {
            break;
        }
    }
    if (t->frame <= 0) {
        pw->flag = 1;
        return base;
    }
    pw->flag = t->flag;
    base -= ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(t[-1].value, t->value, 0, pw->hold - t[-1].frame,
                                                              t->frame - t[-1].frame);
    return base;
}

s32 battleAcResult_AirGauge(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_AirGauge(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)&work->actionCommands + 0x290);
    s32 i;
    switch (work->actionCommands.mAcState) {
        case 99:
            disp->iconX = intplGetValue(4, 20 - *(s32*)&disp->field_0x1C[4], 20, -300.0f, 30.0f);
        case 100:
            i = 4;
        case 1000:
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[i] > 0) {
                (*(s32*)&disp->field_0x1C[i])--;
            }
            break;
        case 1002:
        case 1003:
            if (*(s32*)&disp->field_0x1C[4] >= 40) {
                disp->iconX = intplGetValue(4, *(s32*)&disp->field_0x1C[4] - 40, 20, 30.0f, -300.0f);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] < 60) {
                (*(s32*)&disp->field_0x1C[4])++;
            }
            break;
    }
}

void battleAcDelete_AirGauge(BattleWork* work) {
    work->actionCommands.mAcState = 1002;
}

#pragma dont_inline on
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    AirDisp* disp = (AirDisp*)((u8*)ac + 0x290);
    AirPw* pw;
    f32 ratio;
    f32 cur;

    camGetPtr(8);
    pw = (AirPw*)((u8*)ac + 0x2BC);
    ratio = pw->gauge / 100.0f;
    if (disp->ratio <= ratio) {
        disp->ratio += 0.01f;
        if (disp->ratio > ratio) {
            disp->ratio = ratio;
        }
    } else {
        disp->ratio -= 0.01f;
        if (disp->ratio < ratio) {
            disp->ratio = ratio;
        }
    }
    BattleAcDrawGauge((s32)x, (s32)y, 0xB2, disp->ratio, ACW(ac, s32, 0x40), ACW(ac, s32, 0x44), ACW(ac, s32, 0x48),
                      ACW(ac, s32, 0x4C), 0);
    if (pw->flag) {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = -200.0f + x;
        pos.y = 58.0f + y;
        iconDispGx(&pos, 0x10, ICON_065, 1.0f);
    } else {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = -200.0f + x;
        pos.y = 58.0f + y;
        iconDispGx(&pos, 0x10, ICON_064, 1.0f);
    }
}
#pragma dont_inline reset
