#include "icon_ids.h"
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>

#pragma optimize_for_size on

s32 BattleACGetButtonIcon(s32 button, s32 pressed);
void BattleAcDrawGauge(f32 ratio, s32 x, s32 y, s32 icon, s32 count, s32 a, s32 b, s32 c, s32 flags);
void BattleAcGaugeSeInit(void);
void BattleAcGaugeSeUpdate(f32 value);
void BattleAcGaugeSeDelete(void);

typedef struct PGLv2Disp {
    u8 pad0[0xC]; // 0x0
    u8 col[4];    // 0xC
    s8 delta[4];  // 0x10
    f32 iconX;    // 0x14
    f32 iconY;    // 0x18
    s32 field_1C; // 0x1C
    s32 timer;    // 0x20
    s32 field_24; // 0x24
    f32 ratio;    // 0x28
} PGLv2Disp;

typedef struct PGLv2Work {
    s32 timer;     // 0x0
    s32 maxFrames; // 0x4
    f32 gauge;     // 0x8
    s32 button;    // 0xC
    f32 rate;      // 0x10
    f32 dec;       // 0x14
    s32 full;      // 0x18
    s32 inZone;    // 0x1C
    s16 zones[3];  // 0x20
    u8 pad26[2];   // 0x26
    s32 endTimer;  // 0x28
} PGLv2Work;

typedef struct PGLv2Ac {
    u8 pad0[0xC];
    s32 state;
    u8 pad10[0x78 - 0x10];
    s32 tbl[4];
    u8 pad88[0x290 - 0x88];
    PGLv2Disp disp;
    PGLv2Work w;
} PGLv2Ac;

#define AC_S32(ac, off) (*(s32*)((u8*)(ac) + (off)))
#define AC_DISP(ac) ((PGLv2Disp*)((u8*)(ac) + 0x290))
#define AC_WORK(ac) ((PGLv2Work*)((u8*)(ac) + 0x2BC))

static s32 _power_table[] = {300, 200, 150, 100, 80, 60, 40};
s32 _power_table2[] = {100, 100, 100, 100, 110, 120, 130};

static void actionCommandDisp(f32 x, f32 y);

s32 battleAcMain_PowerGaugeLv2(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    PGLv2Work* g = AC_WORK(ac);
    PGLv2Disp* disp = AC_DISP(ac);
    s32 diff = ((s32 (*)(BattleWork*))BattleActionCommandGetDifficulty)(work);
    s32 flag = 0;
    s32 pressed;
    s32 i;
    if (*((u8*)ac->mAcUnit + BUOFF(0x303))) {
        flag = 1;
    }
    switch (ac->mAcState) {
        case 0:
            memset(disp, 0, 0x2C);
            disp->iconX = -300.0f;
            disp->iconY = 0.0f;
            disp->timer = 20;
            disp->ratio = 0.0f;
            *(GXColor*)disp->col = (GXColor){255, 255, 255, 255};
            disp->delta[0] = 0;
            disp->delta[1] = -16;
            disp->delta[2] = -16;
            disp->delta[3] = 0;
            g->timer = 0;
            AC_S32(ac, 0x58) = 0;
            ac->mAcState = 99;
            ac->result = 1;
            g->maxFrames = sysMsec2Frame(7000);
            g->gauge = 0.0f;
            g->rate = 0.01f * AC_S32(ac, 0x3C);
            g->dec = 0.01f * AC_S32(ac, 0x40);
            g->full = 0;
            g->inZone = 0;
            g->button = 0x100;
            sysMsec2Frame(1000);
            for (i = 0; i < 3; i++) {
                g->zones[i] = irand(sysMsec2Frame(250)) + (i * 2 + 1) * sysMsec2Frame(1000);
            }
            break;
        case 99:
            break;
        case 100:
            if ((ac->setupFlags & 1) && (*(u32*)((u8*)ac->mAcUnit + BUOFF(0x278)) & 0x10)) {
                if (irand(100) >= 0) {
                    ac->setupParam = 30;
                    AC_S32(ac, 0x58) = 0;
                } else {
                    AC_S32(ac, 0x58) = irand(AC_S32(ac, 0x44) - 1) + 1;
                    ac->setupParam = 30;
                }
                ac->mAcState = 1001;
                break;
            }
            BattleAcGaugeSeInit();
            ac->mAcState = 1000;
        case 1000:
            g->timer++;
            if (g->timer > g->maxFrames) {
                if (AC_S32(ac, 0x58) < AC_S32(ac, 0x48)) {
                    ac->result = 0;
                    ac->result &= ~2;
                } else {
                    ac->result = 2;
                    ac->mResultCount++;
                }
                ac->mAcState = 1002;
                break;
            }
            pressed = BattlePadCheckNow(g->button) != 0;
            {
                s32 w = sysMsec2Frame(750);
                g->inZone = 1;
                for (i = 0; i < 3; i++) {
                    s32 z = g->zones[i];
                    if (g->timer >= z && g->timer < z + w) {
                        g->inZone = 0;
                        break;
                    }
                }
            }
            if (flag) {
                if (g->inZone) {
                    pressed = TRUE;
                } else {
                    pressed = FALSE;
                }
            }
            if (!g->full) {
                if (pressed) {
                    if (g->inZone) {
                        g->gauge += 0.01f * (g->rate * (f32)_power_table[diff]);
                    } else {
                        g->gauge -= 0.01f * (g->rate * (f32)_power_table2[diff]);
                    }
                }
                if (g->gauge >= 100.0f) {
                    g->gauge = 100.0f;
                    g->full = 1;
                } else {
                    g->gauge -= g->dec;
                }
                if (g->gauge <= 0.0f) {
                    g->gauge = 0.0f;
                }
            }
            BattleAcGaugeSeUpdate(g->gauge);
            AC_S32(ac, 0x58) = (s32)(g->gauge * (f32)AC_S32(ac, 0x44) / 100.0f);
            if (AC_S32(ac, 0x58) >= AC_S32(ac, 0x44)) {
                AC_S32(ac, 0x58) = AC_S32(ac, 0x44) - 1;
            }
            if (!(AC_S32(ac, 0x34) & 1)) {
                if (g->gauge >= 100.0f) {
                    AC_S32(ac, 0x58)++;
                }
            }
            break;
        case 1001:
            ac->setupParam--;
            if (ac->setupParam < 0) {
                if (AC_S32(ac, 0x58) >= AC_S32(ac, 0x48)) {
                    ac->result = 2;
                    ac->mResultCount++;
                } else {
                    ac->result = 0;
                }
                return 0;
            }
            break;
        case 1002:
            ac->mAcState = 1003;
        case 1003:
            ac->field_0x30 |= 1;
            BattleAcGaugeSeDelete();
            g->endTimer = 60;
            ac->mAcState = 1004;
        case 1004:
            g->endTimer--;
            if (g->endTimer <= 0) {
                ac->mAcState = 1005;
            }
            break;
        case 1005:
            ac->maincb = NULL;
            ac->dispcb = NULL;
            ac->resultcb = NULL;
            ac->deletecb = NULL;
            return 0;
    }
    return 1;
}

s32 battleAcResult_PowerGaugeLv2(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_PowerGaugeLv2(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    PGLv2Disp* disp = AC_DISP(ac);
    switch (ac->mAcState) {
        case 99:
            disp->iconX = intplGetValue(4, 20 - disp->timer, 20, -300.0f, 30.0f);
        case 100:
        case 1000:
        case 1002:
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->timer > 0) {
                disp->timer--;
            }
            break;
        case 1003:
        case 1004:
            if (disp->timer >= 40) {
                disp->iconX = intplGetValue(4, disp->timer - 40, 20, 30.0f, -300.0f);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->timer < 60) {
                disp->timer++;
            }
            break;
    }
}

void battleAcDelete_PowerGaugeLv2(BattleWork* work) {
    if (!(work->actionCommands.field_0x30 & 1)) {
        work->actionCommands.mAcState = 1003;
    }
}

#pragma dont_inline on
#define ICON ((void (*)(Vec*, s32, s32, f32))iconDispGx)
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    PGLv2Ac* ac = (PGLv2Ac*)&work->actionCommands;
    f32 ratio;
    s32 full;
    s32 tmp[4];
    s32 cnt;
    s32 i;
    s32 pressedIcon;
    s32 icon;
    f32 px;
    f32 py;
    camGetPtr(8);
    px = -200.0f + x;
    py = 25.0f + y;
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = px;
        pos.y = py;
        ICON(&pos, 0x10, ICON_08C, 1.0f);
    }
    full = 0;
    ratio = ac->w.gauge / 100.0f;
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    ac->disp.ratio = ratio;
    if (ac->w.full) {
        ac->disp.col[1] += ac->disp.delta[1];
        ac->disp.col[2] += ac->disp.delta[2];
        if (ac->disp.ratio >= 1.0f) {
            full |= 1;
        }
        if (ac->disp.col[1] <= 0x80 && ac->disp.delta[1] < 0) {
            ac->disp.delta[1] = ac->disp.delta[2] = 0x10;
        }
        if (ac->disp.col[1] >= 0xF5 && ac->disp.delta[1] > 0) {
            ac->disp.delta[1] = ac->disp.delta[2] = -0x10;
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        tmp[i] = 100;
    }
    for (i = 0; i < 4; i++, cnt++) {
        tmp[i] = ac->tbl[i];
        if (i != 0 && !(tmp[i] - tmp[i - 1] > 0)) {
            break;
        }
    }
    BattleAcDrawGauge(ac->disp.ratio, (s32)x, (s32)y, 0xB2, cnt, tmp[0], tmp[1], tmp[2], full);
    pressedIcon = BattleACGetButtonIcon(ac->w.button, 1);
    icon = BattleACGetButtonIcon(ac->w.button, 0);
    switch (ac->state) {
        case 99:
        case 100:
        case 1002:
        case 1003:
        case 1004: {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = px;
            pos.y = 70.0f + y;
            ICON(&pos, 0x10, icon, 1.0f);
            break;
        }
        case 1000:
            if (ac->w.inZone) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = px;
                pos.y = 70.0f + y;
                ICON(&pos, 0x10, pressedIcon, 1.0f);
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = px;
                pos.y = 70.0f + y;
                ICON(&pos, 0x10, icon, 1.0f);
            }
            break;
    }
    {
        s32 id = ICON_091;
        Vec pos;
        if (ac->w.inZone) {
            id = ICON_095;
        }
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            pos = zero;
        }
        pos.x = 120.0f + px;
        pos.y = py;
        ICON(&pos, 0x10, id, 1.0f);
    }
}
#pragma dont_inline reset

#pragma force_active on
__declspec(section ".sdata") u32 gap_07_804179E8_sdata[6] = {0};
#pragma force_active reset
