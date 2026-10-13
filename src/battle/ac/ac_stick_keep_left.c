#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "mario/mariost.h"
#include "system.h"
#include <string.h>

#pragma optimize_for_size on

typedef struct SklParams {
    u8 field_0x0[0x34];
    u32 flags;   // 0x34
    s32 count;   // 0x38
    s32 frames;  // 0x3C
    s32 conf;    // 0x40
    s32 endFlag; // 0x44
    s32 sfxFlag; // 0x48
} SklParams;

typedef struct SklWork {
    s32 timer;    // 0x0
    s32 idx;      // 0x4
    s32 endTimer; // 0x8
    u32 sfx[12];  // 0xC
} SklWork;

typedef struct SklDisp {
    u8 field_0x0[0x14];
    f32 iconX;
    f32 iconY;
    u8 field_0x1C[4];
    s32 frame; // 0x20
    s32 idx;   // 0x24
    u8 field_0x28[4];
} SklDisp;

#define SKL_P(work) ((SklParams*)&(work)->actionCommands)
#define SKL_W(work) ((SklWork*)((u8*)&(work)->actionCommands + 0x2BC))
#define SKL_D(work) ((SklDisp*)((u8*)&(work)->actionCommands + 0x290))
#define SKL_S16(work) (*(s16*)((u8*)&(work)->actionCommands + 0x88))

s32 psndSFXOn(const char* name);

s32 ac_stickkeepleft_ok_frame[7] = {80, 70, 60, 40, 20, 10, 5};

static void actionCommandDisp(f32 x, f32 y, s32 unused);

s32 battleAcMain_StickKeepLeft(BattleWork* work) {
    char* sfxPi;
    char* sfxPone;
    SklWork* cw;
    SklDisp* disp;
    s32 loop;
    s32 autoCommand;
    s32 ok;
    s32 i;
    s32 diff;
    s32 j;

    autoCommand = 0;
    cw = SKL_W(work);
    disp = SKL_D(work);
    if (work->actionCommands.mAcUnit->badgesEquipped.AutoCommand) {
        autoCommand = 1;
    }
    SKL_P(work)->endFlag = 0;
    if (work->actionCommands.mAcState != 0) {
        if (SKL_P(work)->conf != 0) {
            SKL_P(work)->endFlag = 1;
        } else {
            SKL_P(work)->endFlag = 0;
        }
    }
    sfxPi = "SFX_AC_PI1";
    sfxPone = "SFX_AC_PONE1\0\0\0";
    do {
        loop = 0;
        if (SKL_P(work)->endFlag != 0) {
            break;
        }
        switch (work->actionCommands.mAcState) {
            case 0:
                work->actionCommands.result = 1;
                cw->idx = 0;
                memset(disp, 0, sizeof(SklDisp));
                disp->iconX = -300.0f;
                disp->iconY = 0.0f;
                disp->frame = 20;
                work->actionCommands.outputParams[0] = 0;
                SKL_P(work)->conf = 0;
                SKL_P(work)->endFlag = 0;
                SKL_P(work)->sfxFlag = 0;
                work->actionCommands.outputParams[2] = 0;
                for (i = 0; i < 12; i++) {
                    cw->sfx[i] = -1;
                }
                work->actionCommands.mAcState = 99;
                break;
            case 99:
                break;
            case 100:
                cw->timer = 120;
                work->actionCommands.mAcState = 1000;
                // fallthrough
            case 1000:
                if ((work->actionCommands.field_0x4 & 1) && (work->actionCommands.mAcUnit->mTokenFlags & 0x10)) {
                    if (work->actionCommands.field_0x4 & 2) {
                        work->actionCommands.field_0x8--;
                        if (work->actionCommands.field_0x8 >= 0) {
                            break;
                        }
                    }
                    if (irand(100) >= 0) {
                        work->actionCommands.result = 0;
                    } else {
                        work->actionCommands.result = 2;
                        work->actionCommands.mResultCount++;
                    }
                    return 0;
                }
                if (!((s32(*)(s32))BattlePadCheckNow)(0x40000) && SKL_S16(work) <= 0 && autoCommand == 0) {
                    if (--cw->timer <= 0) {
                        work->actionCommands.result = 0;
                        loop = 1;
                        work->actionCommands.mAcState = 1003;
                    }
                } else {
                    work->actionCommands.outputParams[0] = 1;
                    work->actionCommands.mAcState = 1001;
                    cw->timer = 1;
                    cw->idx = 1;
                    work->actionCommands.outputParams[1] = 0;
                }
                break;
            case 1001:
                if (SKL_S16(work) > 0) {
                    SKL_S16(work)--;
                    loop = 1;
                    work->actionCommands.result = 2;
                    work->actionCommands.mAcState = 1003;
                }
                cw->timer--;
                if (cw->timer < 0) {
                    cw->idx++;
                    work->actionCommands.outputParams[1]++;
                    if (cw->idx >= SKL_P(work)->count + 2) {
                        work->actionCommands.result &= ~1;
                        work->actionCommands.mAcState = 1003;
                        work->actionCommands.outputParams[2] = 2;
                        if (SKL_P(work)->flags & 2) {
                            work->actionCommands.result |= 2;
                            work->actionCommands.result &= ~1;
                        }
                        loop = 1;
                        break;
                    }
                    j = cw->idx - 2;
                    if (j < SKL_P(work)->count - 1) {
                        if (cw->sfx[j] == -1) {
                            cw->sfx[j] = psndSFXOn(sfxPi);
                        }
                    } else {
                        if (cw->sfx[j] == -1) {
                            cw->sfx[j] = psndSFXOn(sfxPone);
                            SKL_P(work)->sfxFlag = 1;
                        }
                    }
                    cw->timer = SKL_P(work)->frames;
                } else {
                    if (((s32(*)(s32))BattlePadCheckNow)(0x40000) && autoCommand == 0) {
                        break;
                    }
                    ok = 0;
                    if (cw->idx != SKL_P(work)->count + 1) {
                        if (!(SKL_P(work)->flags & 2)) {
                            work->actionCommands.outputParams[2] = 1;
                        }
                    } else {
                        diff = SKL_P(work)->frames - cw->timer;
                        if (diff > ac_stickkeepleft_ok_frame[((s32(*)(BattleWork*))BattleActionCommandGetDifficulty)(work)]) {
                            if (!(SKL_P(work)->flags & 2)) {
                                work->actionCommands.outputParams[2] = 1;
                            }
                        } else {
                            work->actionCommands.outputParams[2] = 3;
                            ok = 1;
                        }
                    }
                    if (autoCommand) {
                        if (!ok) {
                            break;
                        }
                        work->actionCommands.result |= 2;
                        work->actionCommands.result &= ~1;
                        loop = 1;
                        work->actionCommands.mAcState = 1003;
                    } else if (ok) {
                        work->actionCommands.result |= 2;
                        work->actionCommands.result &= ~1;
                        loop = 1;
                        work->actionCommands.mAcState = 1003;
                    } else if (!(SKL_P(work)->flags & 2)) {
                        work->actionCommands.result &= ~1;
                        loop = 1;
                        work->actionCommands.mAcState = 1003;
                    }
                }
                break;
            case 1003:
                {
                    s32 k;
                    for (k = 0; k <= cw->idx - 2; k++) {
                    }
                }
                work->actionCommands.mAcState = 1004;
                break;
            case 1005:
                cw->endTimer = 60;
                work->actionCommands.mAcState = 1006;
                break;
            case 1006:
                cw->endTimer--;
                if (cw->endTimer <= 0) {
                    work->actionCommands.mAcState = 1007;
                }
                break;
            case 1007:
                work->actionCommands.maincb = NULL;
                work->actionCommands.dispcb = NULL;
                work->actionCommands.resultcb = NULL;
                work->actionCommands.deletecb = NULL;
                break;
        }
    } while (loop);
    return 1;
}

s32 battleAcResult_StickKeepLeft(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_StickKeepLeft(CameraId camId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    SklWork* cw = (SklWork*)((u8*)ac + 0x2BC);
    SklDisp* disp = (SklDisp*)((u8*)ac + 0x290);

    switch (work->actionCommands.mAcState) {
        case 0x63:
        case 0x64:
        case 0x3E8:
            disp->idx = -1;
            disp->iconX = intplGetValue(4, 20 - disp->frame, 20, -300.0f, 30.0f);
            actionCommandDisp(disp->iconX, disp->iconY, disp->idx);
            if (SKL_P(work)->endFlag == 0 && disp->frame > 0) {
                disp->frame--;
            }
            break;
        case 0x3E9:
            disp->idx = cw->idx - 1;
            disp->iconX = intplGetValue(4, 20 - disp->frame, 20, -300.0f, 30.0f);
            actionCommandDisp(disp->iconX, disp->iconY, disp->idx);
            if (SKL_P(work)->endFlag == 0 && disp->frame > 0) {
                disp->frame--;
            }
            break;
        case 0x3EA:
        case 0x3EB:
        case 0x3EC:
            actionCommandDisp(30.0f, 0.0f, disp->idx);
            break;
        case 0x3ED:
        case 0x3EE:
            if (disp->frame >= 40) {
                disp->iconX = intplGetValue(4, disp->frame - 40, 20, 30.0f, -300.0f);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY, disp->idx);
            if (SKL_P(work)->endFlag == 0 && disp->frame < 60) {
                disp->frame++;
            }
            break;
    }
}

void battleAcDelete_StickKeepLeft(BattleWork* work) {
    work->actionCommands.mAcState = 0x3ED;
}

#pragma dont_inline on
static void actionCommandDisp(f32 x, f32 y, s32 unused) {
    BattleWork* work = _battleWorkPointer;
    SklWork* cw = SKL_W(work);
    s32 idx;
    s32 count;
    s32 n;
    s32 i;
    f32 spacing;
    f32 yy;

    {
        char n1[8] = "_AcSkl1";
        char n2[8] = "_AcSkl2";
        char n3[8] = "_AcSkl3";
        char n4[8] = "_AcSkl4";
        char n5[8] = "_AcSkl5";
    }
    camGetPtr(8);
    count = SKL_P(work)->count;
    idx = cw->idx - 1;
    switch (work->actionCommands.mAcState) {
        case 0:
        case 0x63:
        case 0x64: {
            Vec p = {0.0f, 0.0f, 0.0f};
            p.x = -200.0f + x;
            p.y = 70.0f + y;
            iconDispGx(&p, 0x10, 0x79, 1.0f);
            break;
        }
        case 0x3E8:
            if (*(u32*)((u8*)gp + 0x1c) & 8) {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = -200.0f + x;
                p.y = 70.0f + y;
                iconDispGx(&p, 0x10, 0x78, 1.0f);
            } else {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = -200.0f + x;
                p.y = 70.0f + y;
                iconDispGx(&p, 0x10, 0x79, 1.0f);
            }
            break;
        default:
            if (idx < count) {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = -200.0f + x;
                p.y = 70.0f + y;
                iconDispGx(&p, 0x10, 0x78, 1.0f);
            } else {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = -200.0f + x;
                p.y = 70.0f + y;
                iconDispGx(&p, 0x10, 0x79, 1.0f);
            }
            break;
    }

    n = 10;
    if (count >= 4) {
        n = count * 2 + 3;
        if (SKL_P(work)->flags & 1) {
            n += 2;
        }
    }
    spacing = 16.0f;
    if (SKL_P(work)->flags & 1) {
        spacing = 12.0f;
    }
    {
        Vec p = {0.0f, 0.0f, 0.0f};
        p.x = -288.0f + x;
        yy = 25.0f + y;
        p.y = yy;
        iconDispGx(&p, 0x10, 0x8f, 1.0f);
    }
    for (i = 1; i < n; i++) {
        Vec p = {0.0f, 0.0f, 0.0f};
        p.x = x + (spacing * (f32)i + -288.0f);
        p.y = yy;
        iconDispGx(&p, 0x10, 0x8e, 1.0f);
    }
    {
        Vec p = {0.0f, 0.0f, 0.0f};
        p.x = x + (spacing * (f32)i + -288.0f);
        p.y = yy;
        iconDispGx(&p, 0x10, 0x90, 1.0f);
    }
    spacing = 33.0f;
    if (SKL_P(work)->flags & 1) {
        spacing = 24.75f;
    }
    n = count - 1;
    for (i = 0; i < n; i++) {
        if (i < idx) {
            if (i < 3) {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = x + (spacing * (f32)i + -258.0f);
                p.y = yy;
                iconDispGx(&p, 0x10, (u16)(0x92 + i), 1.0f);
            } else {
                Vec p = {0.0f, 0.0f, 0.0f};
                p.x = x + (spacing * (f32)i + -258.0f);
                p.y = yy;
                iconDispGx(&p, 0x10, 0x94, 1.0f);
            }
        } else {
            Vec p = {0.0f, 0.0f, 0.0f};
            p.x = x + (spacing * (f32)i + -258.0f);
            p.y = yy;
            iconDispGx(&p, 0x10, 0x91, 0.5f);
        }
    }
    if (idx < count) {
        Vec p = {0.0f, 0.0f, 0.0f};
        p.x = x + (spacing * (f32)n + -250.0f);
        p.y = yy;
        iconDispGx(&p, 0x10, 0x91, 1.0f);
    } else {
        Vec p = {0.0f, 0.0f, 0.0f};
        p.x = x + (spacing * (f32)n + -250.0f);
        p.y = yy;
        iconDispGx(&p, 0x10, 0x95, 1.0f);
    }
}
