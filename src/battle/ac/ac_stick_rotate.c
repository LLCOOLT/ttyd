#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "system.h"
#include <stdlib.h>
#include <string.h>

typedef struct StickRotateParams {
    u8 field_0x0[0x34 - 0x0];
    u32 flags;       // 0x34
    s32 maxCount;    // 0x38
    s32 startTime;   // 0x3C
    u32 button;      // 0x40
    s32 needCount;   // 0x44
    s32 stepsA;      // 0x48
    s32 stepsB;      // 0x4C
    s32 timeout;     // 0x50
} StickRotateParams;

typedef struct StickRotateWork {
    s8 dir;       // 0x0
    s8 prevDir;   // 0x1
    s8 iconA;     // 0x2
    s8 iconB;     // 0x3
    u8 roll;      // 0x4
    s8 stall;     // 0x5
    s8 iconDir;   // 0x6
    u8 iconTimer; // 0x7
    u16 count;    // 0x8
    u8 pad_A[2];
    s32 timer;    // 0xC
    u16 slow;     // 0x10
    u8 pad_12[2];
    s32 endTimer; // 0x14
} StickRotateWork;

#define AC_PARAMS(work) ((StickRotateParams*)&(work)->actionCommands)
#define AC_WORK(work) ((StickRotateWork*)((u8*)&(work)->actionCommands + 0x2BC))
#define AC_DISP(work) ((BattleACDispParams*)((u8*)&(work)->actionCommands + 0x290))

#define PAD(m) (((s32(*)(s32))BattlePadCheckNow)(m))

static void actionCommandDisp(f32 x, f32 y);
void actionCommandDisp2(f32 x, f32 y);
s32 _get_icon_id(s8 dir);

#pragma dont_inline on
s32 _GetInputDir(void) {
    if (AC_PARAMS(_battleWorkPointer)->button != 0 && !PAD(AC_PARAMS(_battleWorkPointer)->button)) {
        return -1;
    }
    if (PAD(0x10000)) {
        if (PAD(0x80000)) {
            return 2;
        }
        if (PAD(0x40000)) {
            return 8;
        }
        return 1;
    }
    if (PAD(0x20000)) {
        if (PAD(0x80000)) {
            return 4;
        }
        return (BattlePadCheckNow(0x40000) != 0U) + 5;
    }
    if (PAD(0x80000)) {
        return 3;
    }
    return BattlePadCheckNow(0x40000) != 0U ? 7 : 0;
}

s32 _CalcRollDir(void) {
    StickRotateWork* w = AC_WORK(_battleWorkPointer);
    s8 cur = w->dir;
    s8 prev = w->prevDir;
    s32 d;
    if (cur <= 0) {
        return 0;
    }
    if (prev <= 0) {
        return 0;
    }
    if (cur == prev) {
        return w->roll;
    }
    if (cur == 1 && prev == 8) {
        return 1;
    }
    if (prev == 1 && cur == 8) {
        return -1;
    }
    d = (s8)(cur - prev);
    if (abs(d) > 1) {
        return 0;
    }
    return d;
}

#define FINISH(w)                            \
    do {                                     \
        (w)->actionCommands.result &= ~1;    \
        (w)->actionCommands.mAcState = 1002; \
        restart = TRUE;                      \
    } while (0)

#pragma dont_inline reset
s32 battleAcMain_StickRotate(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)ac + 0x290);
    StickRotateWork* sw = (StickRotateWork*)((u8*)disp + 0x2C);
    BOOL restart;

    do {
        restart = FALSE;
        switch (ac->mAcState) {
            case 0:
                ac->result = 1;
                memset(disp, 0, sizeof(BattleACDispParams));
                disp->iconX = -300.0f;
                disp->iconY = 0.0f;
                *(s32*)&disp->field_0x1C[4] = 20;
                sw->iconA = 0;
                sw->iconB = 0;
                sw->iconDir = 0;
                sw->iconTimer = 0;
                sw->slow = 0;
                sw->stall = 0;
                ac->mAcState = 99;
                break;
            case 99:
                break;
            case 100:
                sw->timer = 120;
                ac->mAcState = 1000;
                sw->roll = 0;
                sw->count = 0;
                ac->outputParams[0] = 0;
                if (AC_PARAMS(work)->flags & 2) {
                    sw->iconA = 3;
                    sw->iconB = 2;
                }
            case 1000:
                if ((ac->field_0x4 & 1) && (ac->mAcUnit->mTokenFlags & 0x10)) {
                    if (ac->field_0x4 & 2) {
                        ac->field_0x8--;
                        if (ac->field_0x8 >= 0) {
                            break;
                        }
                    }
                    if (irand(100) >= 0) {
                        ac->result = 0;
                    } else {
                        ac->result = 2;
                        ac->mResultCount++;
                    }
                    return 0;
                }
                sw->dir = _GetInputDir();
                if (sw->dir == -1 || (AC_PARAMS(work)->button == 0 && sw->dir <= 0)) {
                    if (*(s16*)((u8*)ac + 0x88) <= 0) {
                        if (--sw->timer > 0) {
                            break;
                        }
                        ac->result = 0;
                        restart = TRUE;
                        ac->mAcState = 1002;
                        break;
                    }
                }
                ac->mAcState = 1001;
                sw->prevDir = 0;
                ac->outputParams[0]++;
                sw->timer = AC_PARAMS(work)->startTime;
                if (AC_PARAMS(work)->flags & 2) {
                    sw->roll = -1;
                    sw->prevDir = 4;
                }
                break;
            case 1001: {
                s8 r;
                if (*(s16*)((u8*)ac + 0x88) > 0) {
                    (*(s16*)((u8*)ac + 0x88))--;
                    ac->result = 2;
                    restart = TRUE;
                    ac->mAcState = 1002;
                    ac->outputParams[0] = AC_PARAMS(work)->maxCount;
                }
                sw->timer--;
                sw->stall++;
                if (AC_PARAMS(work)->button != 0 && !BattlePadCheckNow(AC_PARAMS(work)->button)) {
                    sw->timer = 0;
                }
                if (sw->timer < 0) {
                    if (ac->outputParams[0] >= AC_PARAMS(work)->needCount && !BattlePadCheckNow(AC_PARAMS(work)->button)) {
                        ac->result |= 2;
                    }
                    ac->result &= ~1;
                    restart = TRUE;
                    ac->mAcState = 1002;
                    break;
                }
                sw->dir = _GetInputDir();
                if (sw->dir == -1) {
                    if (ac->outputParams[0] >= AC_PARAMS(work)->needCount) {
                        ac->result |= 2;
                    }
                    ac->result &= ~1;
                    restart = TRUE;
                    ac->mAcState = 1002;
                    break;
                }
                if (sw->dir == 0) {
                    sw->roll = 0;
                    if ((AC_PARAMS(work)->flags & 1) && sw->prevDir != 0) {
                        FINISH(work);
                        break;
                    }
                } else if (sw->prevDir != 0) {
                    r = _CalcRollDir();
                    if (r != 0) {
                        if (sw->roll == 0) {
                            s8 t;
                            sw->roll = r;
                            t = sw->dir + sw->roll;
                            if (t >= 9) {
                                t = 1;
                            }
                            if (t <= 0) {
                                t = 8;
                            }
                            sw->iconA = sw->dir;
                            sw->iconB = t;
                        } else if ((s8)sw->roll != r) {
                            FINISH(work);
                            break;
                        }
                        if (sw->prevDir != sw->dir) {
                            sw->count++;
                            ac->outputParams[0] = (sw->count + 7) / 8;
                            if (ac->outputParams[0] > AC_PARAMS(work)->maxCount) {
                                ac->outputParams[0] = AC_PARAMS(work)->maxCount;
                            }
                            if (AC_PARAMS(work)->flags & 1) {
                                if (sw->count > 1) {
                                    s8 st = sw->stall;
                                    if (st > AC_PARAMS(work)->stepsB) {
                                        FINISH(work);
                                        break;
                                    } else if (st < AC_PARAMS(work)->stepsA) {
                                        sw->slow++;
                                        if (sw->slow > AC_PARAMS(work)->timeout) {
                                            FINISH(work);
                                            break;
                                        }
                                    }
                                }
                                sw->stall = 0;
                                if ((s8)sw->roll != 0 && (s8)sw->roll != r) {
                                    FINISH(work);
                                    break;
                                }
                                if (sw->dir != sw->iconA) {
                                    FINISH(work);
                                    break;
                                } else {
                                    s8 t = sw->iconB + sw->roll;
                                    if (t >= 9) {
                                        t = 1;
                                    }
                                    if (t <= 0) {
                                        t = 8;
                                    }
                                    sw->prevDir = sw->dir;
                                    sw->iconA = sw->iconB;
                                    sw->iconB = t;
                                    if (sw->count >= AC_PARAMS(work)->needCount * 8) {
                                        ac->result |= 2;
                                        FINISH(work);
                                        break;
                                    }
                                }
                            }
                        }
                    } else if (AC_PARAMS(work)->flags & 2) {
                        sw->roll = 0;
                        if (AC_PARAMS(work)->flags & 2) {
                            FINISH(work);
                            break;
                        }
                    } else if (sw->roll != 0) {
                        sw->roll = 0;
                    }
                }
                sw->prevDir = sw->dir;
                break;
            }
            case 1002:
                ac->mAcState = 1003;
                break;
            case 1003:
                break;
            case 1004:
                sw->endTimer = 60;
                *(s32*)&disp->field_0x1C[4] = 60;
                ac->mAcState = 1005;
            case 1005:
                sw->endTimer--;
                if (sw->endTimer <= 0) {
                    ac->mAcState = 1006;
                }
                break;
            case 1006:
                ac->maincb = NULL;
                ac->dispcb = NULL;
                ac->resultcb = NULL;
                ac->deletecb = NULL;
                break;
        }
    } while (restart);
    return 1;
}

s32 battleAcResult_StickRotate(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_StickRotate(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleACDispParams* disp = AC_DISP(work);
    void (*fn)(f32, f32) = actionCommandDisp2;

    if (AC_PARAMS(work)->flags & 2) {
        fn = actionCommandDisp;
    }
    switch (work->actionCommands.mAcState) {
        case 99:
            disp->iconX = intplGetValue(4, 20 - *(s32*)&disp->field_0x1C[4], 20, -300.0f, 30.0f);
            fn(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] > 0) {
                (*(s32*)&disp->field_0x1C[4])--;
            }
            break;
        case 100:
        case 1000:
        case 1001:
        case 1002:
        case 1003:
            disp->iconX = 30.0f;
            fn(disp->iconX, disp->iconY);
            break;
        case 1004:
        case 1005:
        case 1006:
            if (*(s32*)&disp->field_0x1C[4] > 0) {
                (*(s32*)&disp->field_0x1C[4])--;
            }
            if (*(s32*)&disp->field_0x1C[4] <= 40) {
                disp->iconX = intplGetValue(4, *(s32*)&disp->field_0x1C[4], 40, -300.0f, 30.0f);
            } else {
                disp->iconX = 30.0f;
            }
            fn(disp->iconX, disp->iconY);
            break;
    }
}

s32 _get_icon_id(s8 dir) {
    switch (dir) {
        case 1:
            return 0x7C;
        case 2:
            return 0x7D;
        case 3:
            return 0x7A;
        case 4:
            return 0x77;
        case 5:
            return 0x76;
        case 6:
            return 0x75;
        case 7:
            return 0x78;
        case 8:
            return 0x7B;
        default:
            return 0x79;
    }
}

#define ICON(v, id)                  \
    (v) = (Vec){0.0f, 0.0f, 0.0f};   \
    (v).x = -200.0f + x;             \
    (v).y = 70.0f + y;               \
    iconDispGx(&(v), 0x10, (id), 1.0f)

static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    StickRotateWork* sw = AC_WORK(work);
    Vec v0, v1, v2, v3, v4, v5;

    switch (work->actionCommands.mAcState) {
        case 99:
        case 100:
            ICON(v0, 0x79);
            break;
        case 1000:
            ICON(v1, _get_icon_id(sw->iconA));
            break;
        case 1001:
            if (sw->stall < AC_PARAMS(work)->stepsA) {
                if (sw->count <= 1) {
                    ICON(v2, _get_icon_id(sw->iconA));
                } else {
                    ICON(v3, _get_icon_id(sw->prevDir));
                }
            } else {
                ICON(v4, _get_icon_id(sw->iconA));
            }
            break;
        case 1002:
        case 1003:
        case 1004:
        case 1005:
        case 1006:
            ICON(v5, 0x79);
            break;
    }
}

void actionCommandDisp2(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    StickRotateWork* sw = AC_WORK(work);
    Vec v0, v1, v2;

    switch (work->actionCommands.mAcState) {
        case 99:
        case 100:
            ICON(v0, 0x79);
            break;
        case 1000:
        case 1001:
            sw->iconTimer++;
            if (sw->iconTimer >= (AC_PARAMS(work)->stepsA + AC_PARAMS(work)->stepsB) / 2) {
                s32 step;
                sw->iconTimer = 0;
                step = (s8)sw->roll;
                if (step == 0) {
                    step = -1;
                }
                if (sw->iconDir == 0) {
                    sw->iconDir = 1;
                } else {
                    sw->iconDir += step;
                    if (sw->iconDir >= 9) {
                        sw->iconDir = 1;
                    } else if (sw->iconDir <= 0) {
                        sw->iconDir = 8;
                    }
                }
            }
            ICON(v1, _get_icon_id(sw->iconDir));
            break;
        case 1002:
        case 1003:
        case 1004:
        case 1005:
        case 1006:
            ICON(v2, 0x79);
            break;
    }
}

void battleAcDelete_StickRotate(BattleWork* work) {
    work->actionCommands.mAcState = 1004;
}
