#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include "version.h"
// US battle texture ids are 0x16 higher for these entries.
#define BTL_TEX(id) ((id) + VERSION_PICK(0, 0x16))


void btlDispTex4(s32 id, Vec pos, Vec scale, Vec rot, GXColor color);
void btlGetScreenPoint(Vec* in, Vec* out);
f32 sinfd(f32 degrees);

typedef struct ShotTargetDisp {
    u8 field_0x0[0xC];
    GXColor color; // 0xC
    u8 b10;        // 0x10
    s8 b11;        // 0x11
    s8 b12;        // 0x12
    u8 b13;        // 0x13
    f32 iconX;     // 0x14
    f32 iconY;     // 0x18
    u8 field_0x1C[4];
    s32 timer;     // 0x20
    u8 field_0x24[4];
    f32 f28;       // 0x28
} ShotTargetDisp;

typedef struct ShotTargetWork {
    s32 frame;    // 0x0
    s32 endTimer; // 0x4
    Vec hitPos;   // 0x8
    Vec pos;      // 0x14
    s32 inRange;  // 0x20
    f32 angle;    // 0x24
    s16 periodX;  // 0x28
    s16 cntX;     // 0x2A
    f32 ampX;     // 0x2C
    s16 periodY;  // 0x30
    s16 cntY;     // 0x32
    f32 ampY;     // 0x34
    s32 sfxId;    // 0x38
} ShotTargetWork;

typedef struct ShotTargetParams {
    u8 field_0x0[0x38];
    s32 unitId;     // 0x38
    s32 partsId;    // 0x3C
    s32 startFrame; // 0x40
    u32 difficulty; // 0x44
    u8 field_0x48[0x88 - 0x48];
    s16 shotCount;  // 0x88
} ShotTargetParams;

#define ST_PARAMS(ac) ((ShotTargetParams*)(ac))
#define ST_WORK(ac) ((ShotTargetWork*)((u8*)(ac) + 0x2BC))
#define ST_DISP(ac) ((ShotTargetDisp*)((u8*)(ac) + 0x290))

#pragma optimize_for_size on
#pragma dont_inline on

static void _ac_disp_init(BattleWork* work);
static void actionCommandDisp(f32 x, f32 y);
void _ac_rumble_param_set(u32 difficulty, s16* period, s16* count, f32* amp);

s32 battleAcMain_ShotTarget(BattleWork* work) {
    const char* sfxName;
    BattleActions* ac;
    ShotTargetWork* cw;
    BOOL repeat;
    BOOL autoCommand;
    u32 difficulty;
    BattleUnit* unit;
    BattleUnitPart* parts;
    Vec hit;

    ac = &work->actionCommands;
    cw = ST_WORK(ac);
    autoCommand = FALSE;
    if (ac->mAcUnit->badgesEquipped.AutoCommand) {
        autoCommand = TRUE;
    }
    difficulty = ((ShotTargetParams*)&work->actionCommands)->difficulty;
    do {
        sfxName = "SFX_AC_CURSOR_MOVE1";
        repeat = FALSE;
        switch (ac->mAcState) {
            case 0:
                _ac_disp_init(work);
                ac->result = 1;
                unit = BattleGetUnitPtr(work, ((ShotTargetParams*)&work->actionCommands)->unitId);
                parts = BtlUnit_GetPartsPtr(unit, ((ShotTargetParams*)&work->actionCommands)->partsId);
                BtlUnit_GetHitPos(unit, parts, &hit.x, &hit.y, &hit.z);
                cw->hitPos = hit;
                cw->inRange = 0;
                {
                    Vec p = {0.0f, 60.0f, 0.0f};
                    cw->pos = p;
                }
                cw->angle = 0.0f;
                _ac_rumble_param_set(difficulty, &cw->periodX, &cw->cntX, &cw->ampX);
                _ac_rumble_param_set(difficulty, &cw->periodY, &cw->cntY, &cw->ampY);
                cw->sfxId = -1;
                ac->mAcState = 99;
                break;
            case 99:
                break;
            case 100:
                cw->frame = ((ShotTargetParams*)&work->actionCommands)->startFrame;
                ac->mAcState = 1000;
                cw->sfxId = ((s32(*)(const char*))psndSFXOn)(sfxName);
            case 1000:
                if (((ShotTargetParams*)&work->actionCommands)->shotCount > 0) {
                    (((ShotTargetParams*)&work->actionCommands)->shotCount)--;
                    ac->result = 2;
                    repeat = TRUE;
                    ac->mResultCount++;
                    ac->mAcState = 1001;
                    break;
                }
                cw->cntX--;
                if (cw->cntX < 0) {
                    _ac_rumble_param_set(difficulty, &cw->periodX, &cw->cntX, &cw->ampX);
                }
                {
                    f32 s = cw->ampX * sinfd((cw->cntX + 1) * 180 / cw->periodX);
                    cw->pos.x += cw->ampX * sinfd(cw->cntX * 180 / cw->periodX) - s;
                }
                cw->cntY--;
                if (cw->cntY < 0) {
                    _ac_rumble_param_set(difficulty, &cw->periodY, &cw->cntY, &cw->ampY);
                }
                {
                    f32 s = cw->ampY * sinfd((cw->cntY + 1) * 180 / cw->periodY);
                    cw->pos.y += cw->ampY * sinfd(cw->cntY * 180 / cw->periodY) - s;
                }
                cw->pos.x += work->padWork[0].mPadData[0].stickX / 10.0f;
                cw->pos.y += work->padWork[0].mPadData[0].stickY / 10.0f;
                if (autoCommand) {
                    if (__fabs(cw->pos.x - cw->hitPos.x) < 3.0) {
                        cw->pos.x = cw->hitPos.x;
                    } else if (cw->pos.x > cw->hitPos.x) {
                        cw->pos.x -= 3.0f;
                    } else {
                        cw->pos.x += 3.0f;
                    }
                    if (__fabs(cw->pos.y - cw->hitPos.y) < 3.0) {
                        cw->pos.y = cw->hitPos.y;
                    } else if (cw->pos.y > cw->hitPos.y) {
                        cw->pos.y -= 3.0f;
                    } else {
                        cw->pos.y += 3.0f;
                    }
                }
                if (__fabs(distABf(cw->pos.x, cw->pos.y, cw->hitPos.x, cw->hitPos.y)) <= 28.0) {
                    cw->inRange = 1;
                } else {
                    cw->inRange = 0;
                }
                cw->frame--;
                if ((ac->setupFlags & 1) && (*(u32*)((u8*)ac->mAcUnit + BUOFF(0x278)) & 0x10)) {
                    if (irand(100) >= 0) {
                        ac->result = 0;
                    } else {
                        ac->result = 2;
                        ac->mResultCount++;
                    }
                    ac->mAcState = 1001;
                    break;
                }
                if (cw->frame < 0) {
                    if (cw->inRange) {
                        ac->result = 2;
                        ac->mResultCount++;
                    } else {
                        ac->result = 0;
                    }
                    ac->mAcState = 1001;
                }
                break;
            case 1001:
                ac->mAcState = 1002;
                break;
            case 1002:
                break;
            case 1003:
                cw->endTimer = 60;
                ac->mAcState = 1004;
                if ((u32)cw->sfxId != 0xFFFFFFFF) {
                    psndSFXOff(cw->sfxId);
                }
                break;
            case 1004:
                cw->endTimer--;
                if (cw->endTimer <= 0) {
                    ac->mAcState = 1005;
                }
                break;
            case 1005:
                ac->maincb = NULL;
                ac->dispcb = NULL;
                ac->resultcb = NULL;
                ac->deletecb = NULL;
                break;
        }
    } while (repeat);
    return 1;
}

void _ac_rumble_param_set(u32 difficulty, s16* period, s16* count, f32* amp) {
    *period = irand(120) + 120;
    *count = *period - 1;
    *amp = 25.0f;
    if (irand(100) < 50) {
        *amp = -1.0f * *amp;
    }
    switch (difficulty) {
        case 0:
            *amp = 0.6f * (0.25f * *amp);
            break;
        case 1:
            *amp = 0.6f * (0.5f * *amp);
            break;
        case 2:
            *amp = 0.6f * (0.8f * *amp);
            break;
        case 3:
            *amp = 0.6f * *amp;
            break;
        case 4:
            *amp = 0.6f * (1.5f * *amp);
            break;
        case 5:
            *amp = 0.6f * (2.0f * *amp);
            break;
        case 6:
        default:
            *amp = 0.6f * (3.0f * *amp);
            break;
    }
}

s32 battleAcResult_ShotTarget(BattleWork* work) {
    return work->actionCommands.result;
}

void battleAcDisp_ShotTarget(CameraId cameraId, void* param) {
    BattleWork* work = param;
    BattleActions* ac = &work->actionCommands;
    ShotTargetDisp* d = ST_DISP(ac);

    switch (ac->mAcState) {
        case 99:
        case 100:
        case 1000:
        case 1001:
        case 1002:
            d->iconX = intplGetValue(4, 20 - d->timer, 20, -200.0f, 30.0f);
            actionCommandDisp(d->iconX, d->iconY);
            if (d->timer > 0) {
                d->timer--;
            }
            break;
        case 1003:
        case 1004:
            if (d->timer >= 40) {
                d->iconX = intplGetValue(4, d->timer - 40, 20, 30.0f, -200.0f);
            } else {
                d->iconX = 30.0f;
            }
            actionCommandDisp(d->iconX, d->iconY);
            if (d->timer < 60) {
                d->timer++;
            }
            break;
    }
}

void battleAcDelete_ShotTarget(BattleWork* work) {
    work->actionCommands.mAcState = 1003;
}

static void _ac_disp_init(BattleWork* work) {
    ShotTargetDisp* d = ST_DISP(&work->actionCommands);
    memset(d, 0, 0x2C);
    d->iconX = -200.0f;
    d->iconY = 0.0f;
    d->timer = 20;
    d->color = (GXColor){255, 255, 255, 255};
    d->b10 = 0;
    d->b11 = -16;
    d->b12 = -16;
    d->b13 = 0;
    d->f28 = 0.0f;
}

static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    ShotTargetWork* cw = ST_WORK(ac);
    Vec screen;
    Vec screen2;

    switch (ac->mAcState) {
        case 100:
        case 1000:
        case 1001:
        case 1002:
            cw->angle += 2.0f;
            btlGetScreenPoint(&cw->pos, &screen);
            btlDispTex4(BTL_TEX(0x42), screen, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, 0.0f}, (GXColor){255, 255, 255, 255});
            screen.x += 4.0f;
            screen.y -= 4.0f;
            screen.z -= 2.0f;
            btlDispTex4(BTL_TEX(0x42), screen, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, 0.0f}, (GXColor){128, 128, 128, 255});
            btlGetScreenPoint(&cw->hitPos, &screen2);
            btlDispTex4(BTL_TEX(0x41), screen2, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, cw->angle}, (GXColor){255, 255, 255, 255});
            screen2.x += 4.0f;
            screen2.y -= 4.0f;
            screen2.z -= 2.0f;
            btlDispTex4(BTL_TEX(0x41), screen2, (Vec){1.0f, 1.0f, 1.0f}, (Vec){0.0f, 0.0f, cw->angle}, (GXColor){128, 128, 128, 255});
            break;
    }
}
