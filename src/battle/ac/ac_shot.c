#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "system.h"
#include <string.h>

#pragma optimize_for_size on

void btlDispTex4(s32 id, Vec pos, Vec scale, Vec rot, GXColor color);
void btlGetScreenPoint(Vec* in, Vec* out);
f32 sinfd(f32 degrees);
f32 cosfd(f32 degrees);
s32 psndSFXOn(const char* name);
void psndSFXOff(s32 id);

typedef struct ShotDisp {
    u8 field_0x0[0xC];
    GXColor col;      // 0xC
    s8 delta[4];      // 0x10
    f32 iconX;        // 0x14
    f32 iconY;        // 0x18
    s32 field_0x1C;
    s32 counter;      // 0x20
    s32 field_0x24;
    f32 progress;     // 0x28
} ShotDisp;

typedef struct ShotWork {
    s32 timer;        // 0x0
    s32 field_0x4;
    s32 idx;          // 0x8
    f32 minV;         // 0xC
    f32 maxV;         // 0x10
    f32 left;         // 0x14
    f32 right;        // 0x18
    f32 speed;        // 0x1C
    f32 speed0;       // 0x20
    f32 pos;          // 0x24
    f32 vel;          // 0x28
    f32 angle;        // 0x2C
    Vec unitPos;      // 0x30
    s32 endTimer;     // 0x3C
    f32 ang[3];       // 0x40
    f32 spin[3];      // 0x4C
    f32 life[3];      // 0x58
    u32 sfxId;        // 0x64
} ShotWork;

typedef struct ShotParams {
    s32 unitId;       // 0x38
    s32 count;        // 0x3C
    s32 a;            // 0x40
    s32 b;            // 0x44
    s32 c;            // 0x48
    s32 d;            // 0x4C
    s32 e;            // 0x50
} ShotParams;

#define SH_DISP(ac) ((ShotDisp*)((u8*)(ac) + 0x290))
#define SH_WORK(ac) ((ShotWork*)((u8*)(ac) + 0x2BC))
#define SH_PARAMS(ac) ((ShotParams*)((u8*)(ac) + 0x38))
#define SH_FLAGS(ac) (*(u32*)((u8*)(ac) + 0x34))
#define SH_OUT(ac) ((s32*)((u8*)(ac) + 0x58))
#define SH_S16(ac) (*(s16*)((u8*)(ac) + 0x88))


static void _disp_target_mark(CameraId cameraId, void* param);
static void _disp_target_mark_afterimage(CameraId cameraId, void* param);
static void _ac_disp_init(BattleWork* work);

#define SH_RECORD(ac, sw)                \
    SH_OUT(ac)[2] = (s32)(sw)->pos;      \
    SH_OUT(ac)[0] = 1;                   \
    (sw)->ang[(sw)->idx] = (sw)->pos;    \
    (sw)->spin[(sw)->idx] = (sw)->angle; \
    (sw)->life[(sw)->idx] = 70.0f;       \
    (sw)->idx++;                         \
    SH_OUT(ac)[3]++

s32 battleAcMain_Shot(BattleWork* work) {
    const char* sfx = "SFX_AC_CURSOR_MOVE1";
    BattleActions* ac = &work->actionCommands;
    ShotWork* sw = SH_WORK(ac);
    s32 loop;
    do {
        loop = 0;
        switch (ac->mAcState) {
            case 0: {
                BattleUnit* unit;
                s32 i;
                _ac_disp_init(work);
                ac->result = 1;
                sw->minV = SH_PARAMS(ac)->a;
                sw->maxV = SH_PARAMS(ac)->b;
                sw->left = SH_PARAMS(ac)->c;
                sw->right = SH_PARAMS(ac)->d;
                sw->speed0 = 100.0f * sw->minV / sw->maxV;
                sw->speed = sw->speed0;
                sw->pos = sw->left + (f32)irand((s32)(sw->right - sw->left));
                sw->vel = 0.1f * SH_PARAMS(ac)->e;
                sw->idx = 0;
                ac->field_0x8 = 30;
                unit = BattleGetUnitPtr(work, SH_PARAMS(ac)->unitId);
                BtlUnit_GetPos(unit, &sw->unitPos.x, &sw->unitPos.y, &sw->unitPos.z);
                sw->unitPos.y = sw->unitPos.y + 0.5 * (unit->mSizeMultiplier * (f32)BtlUnit_GetHeight(unit));
                SH_OUT(ac)[0] = 0;
                SH_OUT(ac)[3] = 0;
                for (i = 0; i < 3; i++) {
                    sw->ang[i] = -1000.0f;
                    sw->spin[i] = 0.0f;
                }
                sw->sfxId = -1;
                ac->mAcState = 99;
                break;
            }
            case 99:
            case 1003:
                break;
            case 100:
                sw->timer = 360;
                ac->mAcState = 1000;
                sw->sfxId = psndSFXOn(sfx);
            case 1000:
                if ((ac->field_0x4 & 1) && (ac->mAcUnit->mTokenFlags & 0x10)) {
                    f32 range;
                    s32 r;
                    if (ac->field_0x4 & 2) {
                        ac->field_0x8--;
                        if (ac->field_0x8 >= 0) {
                            break;
                        }
                    }
                    range = sw->maxV - sw->minV;
                    if (range) {
                        r = (s32)(sw->minV + (f32)irand((s32)range));
                    } else {
                        r = (s32)sw->minV;
                    }
                    SH_OUT(ac)[1] = (s32)(sw->maxV * (f32)r / 100.0f);
                    if ((f32)SH_OUT(ac)[1] < sw->minV) {
                        SH_OUT(ac)[1] = (s32)sw->minV;
                    }
                    SH_RECORD(ac, sw);
                    if (sw->idx >= SH_PARAMS(ac)->count) {
                        ac->result = 2;
                        return 0;
                    }
                    if (ac->field_0x4 & 2) {
                        ac->field_0x8 = 30;
                    }
                    break;
                }
                if (!BattlePadCheckTrigger(0x100) && !SH_OUT(ac)[0] && SH_S16(ac) <= 0) {
                    if (--sw->timer <= 0) {
                        SH_OUT(ac)[1] = (s32)(sw->maxV * sw->speed / 100.0f);
                        if ((f32)SH_OUT(ac)[1] < sw->minV) {
                            SH_OUT(ac)[1] = (s32)sw->minV;
                        }
                        SH_RECORD(ac, sw);
                        if (sw->idx >= SH_PARAMS(ac)->count) {
                            ac->result = 0;
                            ac->mAcState = 1002;
                        } else {
                            sw->timer = 360;
                        }
                        loop = 1;
                    }
                } else if (!SH_OUT(ac)[0]) {
                    ac->mAcState = 1001;
                }
                if (sw->vel) {
                    sw->pos += sw->vel;
                    if (sw->vel > 0.0f) {
                        if (sw->pos >= sw->right) {
                            sw->pos = sw->right;
                            sw->vel *= -1.0f;
                        }
                    } else if (sw->pos <= sw->left) {
                        sw->pos = sw->left;
                        sw->vel *= -1.0f;
                    }
                }
                sw->angle += 8.0f;
                break;
            case 1001:
                if (SH_S16(ac) > 0) {
                    SH_OUT(ac)[1] = (s32)(50.0f * sw->maxV / 100.0f);
                    if ((f32)SH_OUT(ac)[1] < sw->minV) {
                        SH_OUT(ac)[1] = (s32)sw->minV;
                    }
                    SH_RECORD(ac, sw);
                    if (sw->idx >= SH_PARAMS(ac)->count) {
                        SH_S16(ac)--;
                        ac->result = 2;
                        ac->mAcState = 1002;
                    } else {
                        ac->mAcState = 1000;
                    }
                    loop = 1;
                }
                sw->speed += 1.0f;
                if (sw->speed > 100.0f) {
                    sw->speed = 100.0f;
                }
                if (SH_FLAGS(ac) & 1) {
                    SH_OUT(ac)[1] = (s32)((sw->minV + sw->maxV) / 2.0f);
                    SH_RECORD(ac, sw);
                    if (sw->idx >= SH_PARAMS(ac)->count) {
                        ac->mAcState = 1002;
                        ac->result = 2;
                    } else {
                        ac->mAcState = 1000;
                    }
                } else if (!((s32 (*)(s32))BattlePadCheckNow)(0x100)) {
                    SH_OUT(ac)[1] = (s32)(sw->maxV * sw->speed / 100.0f);
                    if ((f32)SH_OUT(ac)[1] < sw->minV) {
                        SH_OUT(ac)[1] = (s32)sw->minV;
                    }
                    SH_RECORD(ac, sw);
                    if (sw->idx >= SH_PARAMS(ac)->count) {
                        ac->result = 2;
                        ac->mAcState = 1002;
                    } else {
                        ac->mAcState = 1000;
                    }
                }
                break;
            case 1002:
                ac->mAcState = 1003;
                break;
            case 1004:
                sw->endTimer = 60;
                ac->mAcState = 1005;
                if (sw->sfxId != -1) {
                    psndSFXOff(sw->sfxId);
                }
                break;
            case 1005:
                sw->endTimer--;
                if (sw->endTimer <= 0) {
                    ac->mAcState = 1006;
                }
                break;
            case 1006:
                ac->maincb = 0;
                ac->dispcb = 0;
                ac->resultcb = 0;
                ac->deletecb = 0;
                break;
        }
    } while (loop);
    if (ac->mAcState == 1000 || ac->mAcState == 1001) {
        dispEntry(8, 900.0f, 1, _disp_target_mark, work);
    }
    dispEntry(8, 900.0f, 1, _disp_target_mark_afterimage, work);
    return 1;
}

s32 battleAcResult_Shot(BattleWork* work) {
    return work->actionCommands.result;
}

static void actionCommandDisp(f32 x, f32 y);

void battleAcDisp_Shot(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    ShotDisp* disp = SH_DISP(ac);
    switch (ac->mAcState) {
        case 99:
        case 100:
        case 1000:
        case 1001:
        case 1002:
        case 1003:
            disp->iconX = intplGetValue(4, 20 - disp->counter, 20, -200.0f, 30.0f);
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->counter > 0) {
                disp->counter--;
            }
            break;
        case 1004:
        case 1005:
            if (disp->counter >= 40) {
                disp->iconX = intplGetValue(4, disp->counter - 40, 20, 30.0f, -200.0f);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (disp->counter < 60) {
                disp->counter++;
            }
            break;
    }
}

void battleAcDelete_Shot(BattleWork* work) {
    work->actionCommands.mAcState = 1004;
}

#pragma dont_inline on
static void _ac_disp_init(BattleWork* work) {
    ShotDisp* disp = SH_DISP(&work->actionCommands);
    memset(disp, 0, 0x2C);
    disp->iconX = -200.0f;
    disp->iconY = 0.0f;
    disp->counter = 20;
    disp->col = (GXColor){255, 255, 255, 255};
    disp->delta[0] = 0;
    disp->delta[1] = -16;
    disp->delta[2] = -16;
    disp->delta[3] = 0;
    disp->progress = 0.0f;
}
#pragma dont_inline reset

#pragma dont_inline on
static void actionCommandDisp(f32 x, f32 y) {
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    ShotWork* sw = SH_WORK(ac);
    ShotDisp* disp = SH_DISP(ac);
    Mtx m3;
    Mtx m1;
    Mtx m2;
    f32 limit;
    if (!(SH_FLAGS(ac) & 1)) {
        Vec pos = {0.0f, 0.0f, 0.0f};
        f32 px = -200.0f + x;
        pos.x = px;
        pos.y = 25.0f + y;
        iconDispGx(&pos, 0x10, 0x8c, 1.0f);
        limit = sw->speed / 100.0f;
        if (disp->progress <= limit) {
            disp->progress += 0.01f;
            if (disp->progress > limit) {
                disp->progress = limit;
            }
        } else {
            disp->progress -= 0.01f;
            if (disp->progress < limit) {
                disp->progress = limit;
            }
        }
        if (disp->progress >= 1.0f) {
            disp->col.g += disp->delta[1];
            disp->col.b += disp->delta[2];
            if (disp->col.g <= 0x80 && disp->delta[1] < 0) {
                disp->delta[1] = disp->delta[2] = 16;
            }
            if (disp->col.g >= 0xF5 && disp->delta[1] > 0) {
                disp->delta[1] = disp->delta[2] = -16;
            }
        }
        MTXTrans(m1, px - 88.0f * (1.0f - disp->progress), 33.0f + y, 0.0f);
        MTXScale(m2, disp->progress, 1.0f, 1.0f);
        MTXConcat(m1, m2, m3);
        iconDispGxCol(m3, 0x10, 0x8d, (GXColor){disp->col.r, disp->col.g, disp->col.b, disp->col.a});
    }
}
#pragma dont_inline reset

#pragma dont_inline on
static void _draw_target_mark(GXColor color, f32 x, f32 y, f32 z, f32 angle) {
    Vec pos = {0.0f, 0.0f, 0.0f};
    pos.x = x;
    pos.y = y;
    pos.z = z;
    btlDispTex4(0x42, pos, (Vec){0.5f, 0.5f, 1.0f}, (Vec){0.0f, 0.0f, reviseAngle(-angle)}, color);
    btlDispTex4(0x41, pos, (Vec){0.5f, 0.5f, 1.0f}, (Vec){0.0f, 0.0f, reviseAngle(angle)}, color);
}
#pragma dont_inline reset

static void _disp_target_mark(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    ShotWork* sw = SH_WORK(&work->actionCommands);
    Vec in;
    Vec out;
    in.x = 60.0f * sinfd(sw->pos) + sw->unitPos.x;
    in.y = 60.0f * cosfd(sw->pos) + sw->unitPos.y;
    in.z = sw->unitPos.z;
    btlGetScreenPoint(&in, &out);
    _draw_target_mark((GXColor){255, 255, 255, 255}, out.x, out.y, out.z, sw->angle);
}

static void _disp_target_mark_afterimage(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    ShotWork* sw = SH_WORK(&work->actionCommands);
    s32 i;
    for (i = 0; i < 3; i++) {
        if (sw->ang[i] >= 0.0f && sw->life[i] > 0.0f) {
            Vec in;
            Vec out;
            sw->life[i] -= 1.0f;
            in.x = 60.0f * sinfd(sw->ang[i]) + sw->unitPos.x;
            in.y = 60.0f * cosfd(sw->ang[i]) + sw->unitPos.y;
            in.z = sw->unitPos.z;
            btlGetScreenPoint(&in, &out);
            if (sw->life[i] >= 30.0f) {
                _draw_target_mark((GXColor){0x90, 0x80, 0xA0, 0xFF}, out.x, out.y, out.z, sw->spin[i]);
            } else {
                u8 a = (u8)intplGetValue(0, (s32)(30.0f - sw->life[i]), 30, 255.0f, 0.0f);
                _draw_target_mark((GXColor){0x90, 0x80, 0xA0, a}, out.x, out.y, out.z, sw->spin[i]);
            }
            if (sw->life[i] <= 0.0f) {
                sw->ang[i] = -1.0f;
            }
        }
    }
}
