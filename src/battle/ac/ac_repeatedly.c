#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "system.h"
#include <dolphin/os.h>
#include <string.h>

u32 SIProbe(s32 chan);
void BattleAcDrawGauge();
void BattleAcGaugeSeInit(void);
void BattleAcGaugeSeUpdate(f32 value);
void BattleAcGaugeSeDelete(void);

typedef struct RepeatDisp {
    s32 frame;        // 0x0
    s32 frame2;       // 0x4
    u8 field_0x8[4];  // 0x8
    GXColor color;    // 0xC
    s8 delta[4];      // 0x10
    f32 unk14;        // 0x14
    f32 unk18;        // 0x18
    f32 unk1C;        // 0x1C
    s32 timer;        // 0x20
    u8 field_0x24[4]; // 0x24
    f32 gauge;        // 0x28
} RepeatDisp;

typedef struct RepeatWork {
    u32 btn0;         // 0x0
    u32 btn1;         // 0x4
    u32 btn2;         // 0x8
    u32 holdMask;     // 0xC
    f32 pos;          // 0x10
    f32 vel;          // 0x14
    f32 gauge;        // 0x18
    f32 decay;        // 0x1C
    u16 count;        // 0x20
    u16 timer;        // 0x22
    s16 power;        // 0x24
    s16 field_0x26;   // 0x26
    s16 grace;        // 0x28
    u8 iconParam;     // 0x2A
    s8 done;          // 0x2B
    u8 resetFlag;     // 0x2C
    u8 field_0x2D[3]; // 0x2D
    s32 endTimer;     // 0x30
} RepeatWork;

#pragma optimize_for_size on

#define RW(w) ((RepeatWork*)((u8*)&(w)->actionCommands + 0x2BC))
#define RD(w) ((RepeatDisp*)((u8*)&(w)->actionCommands + 0x290))
#define ACP(w, off, T) (*(T*)((u8*)&(w)->actionCommands + (off)))

static void actionCommandDisp(f32 x, f32 y);
void battleAcDelete_Repeatedly(BattleWork* work);

#define PadNow(m) (((s32(*)(s32))BattlePadCheckNow)(m))

static s32 _power_table[] = {55, 50, 45, 40, 35, 30, 25};

static void _init_param(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    RepeatWork* r = (RepeatWork*)((u8*)ac + 0x2BC);
    RepeatDisp* d = (RepeatDisp*)((u8*)ac + 0x290);
    ACP(work, 0x2E8, u8) = 0;
    ACP(work, 0x2C8, u32) = 0;
    switch (ACP(work, 0x38, s32)) {
        case 10:
            work->flags |= 0x20000000;
            break;
        case 8:
            r->holdMask = 0x100;
        case 6:
            r->btn0 = r->btn1 = r->btn2 = 0x40000;
            break;
        case 2:
            r->btn0 = r->btn1 = r->btn2 = 0x200;
            break;
        case 3:
            r->btn0 = r->btn1 = r->btn2 = 0x400;
            break;
        case 4:
            r->btn0 = r->btn1 = r->btn2 = 0x800;
            break;
        case 5:
            r->btn0 = r->btn1 = r->btn2 = 0x20;
            break;
        case 11:
            r->btn0 = r->btn1 = 0x100;
            r->btn2 = 0x200;
            break;
        case 16:
            r->btn0 = r->btn1 = 0x100;
            r->btn2 = 0x200;
            r->timer = irand(30) + 60;
            break;
        case 12:
            r->btn0 = r->btn1 = 0x400;
            r->btn2 = 0x800;
            break;
        default:
            r->btn0 = r->btn1 = r->btn2 = 0x100;
            break;
    }
    r->field_0x26 = r->grace = ACP(work, 0x3C, s32);
    r->pos = ACP(work, 0x40, s32);
    r->vel = ACP(work, 0x44, s32) / 10.0f;
    if (r->vel) {
        r->pos = irand(100);
    }
    r->gauge = ACP(work, 0x54, s32);
    d->gauge = 0.01f * r->gauge;
    r->count = 0;
    r->power = ACP(work, 0x4C, s32);
    r->decay = 0.01f * ACP(work, 0x50, s32);
    r->iconParam = 0xB2;
    if (*(s16*)((u8*)work + 0x1D18) > 0) {
        (*(s16*)((u8*)work + 0x1D18))--;
        r->done = 1;
    } else {
        r->done = 0;
    }
    ACP(work, 0x58, s32) = 0;
}

s32 battleAcMain_Repeatedly(BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    RepeatWork* r = (RepeatWork*)((u8*)ac + 0x2BC);
    RepeatDisp* d = (RepeatDisp*)((u8*)ac + 0x290);
    s32 diff = ((s32(*)(BattleWork*))BattleActionCommandGetDifficulty)(work);
    s32 pressed;
    BOOL autoCmd = FALSE;
    if (work->actionCommands.mAcUnit->badgesEquipped.AutoCommand) {
        autoCmd = TRUE;
    }
    pressed = 0;
    switch (work->actionCommands.mAcState) {
        case 0:
            memset(d, 0, sizeof(RepeatDisp));
            d->unk14 = -300.0f;
            d->unk18 = 0.0f;
            d->timer = 20;
            d->color = (GXColor){255, 255, 255, 255};
            d->delta[0] = 0;
            d->delta[1] = -16;
            d->delta[2] = -16;
            d->delta[3] = 0;
            d->gauge = 0.0f;
            work->actionCommands.result = 1;
            r->grace = 0;
            _init_param(work);
            work->actionCommands.mAcState = 99;
            break;
        case 99:
            break;
        case 100:
            if (!((work->actionCommands.setupFlags & 1) &&
                  (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction))) {
                if (r->holdMask) {
                    if (!PadNow(r->holdMask)) {
                        break;
                    }
                }
            }
            BattleAcGaugeSeInit();
            work->actionCommands.mAcState = 1000;
            ACP(work, 0x58, s32) = 1;
        case 1000:
            switch (ACP(work, 0x38, s32)) {
                case 10:
                    if (r->resetFlag) {
                        if (!OSGetResetButtonState()) {
                            r->resetFlag = 0;
                            pressed = 1;
                            r->count++;
                        }
                    } else {
                        if (OSGetResetButtonState()) {
                            r->resetFlag = 1;
                            pressed = 1;
                            r->count++;
                        }
                    }
                    break;
                case 9:
                    if (r->resetFlag) {
                        if (SIProbe(0) == 8) {
                            r->resetFlag = 0;
                            pressed = 1;
                            r->count++;
                        }
                    } else {
                        if (SIProbe(0) != 8 && SIProbe(0) != 0x80) {
                            r->resetFlag = 1;
                            pressed = 1;
                            r->count++;
                        }
                    }
                    break;
                case 16:
                    r->timer--;
                    if (r->timer == 0) {
                        r->timer = irand(30) + 60;
                        if (r->btn0 == r->btn1) {
                            r->btn0 = r->btn2;
                        } else {
                            r->btn0 = r->btn1;
                        }
                    }
                    if (BattlePadCheckTrigger(r->btn0)) {
                        pressed = 1;
                        r->count++;
                    }
                    break;
                case 11:
                case 12:
                    if (r->count & 1) {
                        r->btn0 = r->btn2;
                    } else {
                        r->btn0 = r->btn1;
                    }
                default:
                    if (BattlePadCheckTrigger(r->btn0)) {
                        pressed = 1;
                        r->count++;
                    }
                    break;
            }
            if (autoCmd && !pressed) {
                pressed = 1;
                r->count++;
            }
            if (!r->done) {
                if (pressed) {
                    r->gauge += 0.01f * ((f32)_power_table[diff] * (f32)r->power);
                }
                r->gauge -= r->decay;
                if (r->gauge <= 0.0f) {
                    r->gauge = 0.0f;
                }
                if (r->gauge >= 100.0f) {
                    r->gauge = 100.0f;
                    r->done = 1;
                }
            }
            if (0.0f != r->vel) {
                r->pos += r->vel;
                if (r->pos <= 0.0f) {
                    r->pos = 0.0f;
                    r->vel *= -1.0f;
                }
                if (r->pos >= 100.0f) {
                    r->pos = 100.0f;
                    r->vel *= -1.0f;
                }
            }
            if (r->holdMask) {
                if (!PadNow(r->holdMask)) {
                    r->grace = 0;
                }
            }
            BattleAcGaugeSeUpdate(r->gauge);
            if (r->grace > 0) {
                r->grace--;
                break;
            }
            work->actionCommands.result &= ~1;
            if (r->gauge >= r->pos || r->done) {
                work->actionCommands.result |= 2;
            }
            battleAcDelete_Repeatedly(work);
            work->actionCommands.mAcState = 1002;
            break;
        case 1002:
            r->endTimer = 60;
            work->actionCommands.mAcState = 1003;
            break;
        case 1003:
            r->endTimer--;
            if (r->endTimer <= 0) {
                work->actionCommands.mAcState = 1004;
            }
            break;
        case 1004:
            work->actionCommands.maincb = NULL;
            work->actionCommands.dispcb = NULL;
            work->actionCommands.resultcb = NULL;
            work->actionCommands.deletecb = NULL;
            break;
    }
    return 1;
}

s32 battleAcResult_Repeatedly(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_Repeatedly(CameraId cameraId, BattleWork* work) {
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)ac + 0x290);
    switch (ac->mAcState) {
        case 99:
        case 100:
        case 1000:
        case 1001:
            disp->iconX = intplGetValue(4, 20 - *(s32*)&disp->field_0x1C[4], 20, -300.0f, 30.0f);
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] > 0) {
                (*(s32*)&disp->field_0x1C[4])--;
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

#pragma dont_inline on
void battleAcDelete_Repeatedly(BattleWork* work) {
    switch (ACP(work, 0x38, s32)) {
        case 10:
            work->flags &= ~0x20000000;
            break;
    }
    BattleAcGaugeSeDelete();
    work->actionCommands.mAcState = 1002;
}
#pragma dont_inline reset

static void actionCommandDisp(f32 x, f32 y) {
    RepeatWork* r;
    RepeatDisp* d;
    s32 odd;
    s32 i;
    u16 icon1, icon2;
    s32 flags;
    f32 target;
    r = RW(_battleWorkPointer);
    d = RD(_battleWorkPointer);
    camGetPtr(8);
    if (*(s32*)((u8*)r - 0x2BC + 0x38) != 16) {
        switch (r->btn0) {
            case 0x100:
                icon1 = 0x65;
                icon2 = 0x64;
                break;
            case 0x200:
                icon1 = 0x67;
                icon2 = 0x66;
                break;
            case 0x400:
                icon1 = 0x69;
                icon2 = 0x68;
                break;
            case 0x800:
                icon1 = 0x6B;
                icon2 = 0x6A;
                break;
            case 0x40000:
            default:
                icon1 = 0x78;
                icon2 = 0x79;
                break;
        }
        if ((d->frame / 7 & 1) == 1) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = -200.0f + x;
            pos.y = 70.0f + y;
            iconDispGx(&pos, 0x10, icon2, 1.0f);
        } else {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = -200.0f + x;
            pos.y = 70.0f + y;
            iconDispGx(&pos, 0x10, icon1, 1.0f);
        }
    } else {
        odd = (d->frame / 7) & 1;
        for (i = 0; i < 2; i++) {
            BOOL match;
            u16 a, b, icon;
            if (i == 0) {
                a = 0x65;
                b = 0x64;
                if (r->btn0 == r->btn1) {
                    match = TRUE;
                } else {
                    match = FALSE;
                }
            } else {
                a = 0x67;
                b = 0x66;
                if (r->btn0 == r->btn2) {
                    match = TRUE;
                } else {
                    match = FALSE;
                }
            }
            if (match) {
                icon = a;
                if (odd == 1) {
                    icon = b;
                }
                {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = (-200.0f + x) + (f32)(i * 40);
                    pos.y = 70.0f + y;
                    iconDispGx(&pos, 0x10, icon, 1.0f);
                }
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = (-200.0f + x) + (f32)(i * 40);
                pos.y = 70.0f + y;
                iconDispGx(&pos, 0x10, b, 0.5f);
            }
        }
    }
    target = r->gauge / 100.0f;
    if (d->gauge <= target) {
        d->gauge += 0.01f;
        if (d->gauge > target) {
            d->gauge = target;
        }
    } else {
        d->gauge -= 0.01f;
        if (d->gauge < target) {
            d->gauge = target;
        }
    }
    flags = 0;
    if ((s32)(u8)r->done == 1 && d->gauge >= 1.0f) {
        flags |= 1;
        ((u8*)&d->color)[1] += d->delta[1];
        ((u8*)&d->color)[2] += d->delta[2];
        if (((u8*)&d->color)[1] <= 0x80 && d->delta[1] < 0) {
            d->delta[1] = d->delta[2] = 0x10;
        }
        if (((u8*)&d->color)[1] >= 0xF5 && d->delta[1] > 0) {
            d->delta[1] = d->delta[2] = -0x10;
        }
    }
    if (r->done == -1) {
        flags |= 2;
    }
    BattleAcDrawGauge((s32)x, (s32)y, d->gauge, r->iconParam, 2,
                      (*(s32*)((u8*)r - 0x2BC + 0x34) & 2) ? 100 : (s32)r->pos, 100, 100, flags);
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = (-288.0f + x) + (176.0f * r->pos) / 100.0f;
        pos.y = 45.0f + y;
        iconDispGx(&pos, 0x10, 0x96, 1.0f);
    }
    d->frame++;
    d->frame2++;
}

#pragma force_active on
__declspec(section ".sdata") u32 gap_07_804117CC_sdata[5] = {0};
#pragma force_active reset
