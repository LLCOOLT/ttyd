#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_audience.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/icondrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

extern BattleWork* _battleWorkPointer;

double cos(double);
double sin(double);
void btlDispTexPlane2(Mtx, u32, GXColor);
void btlDispTexPlane3(Mtx, u32, GXColor, GXColor, GXColor, GXColor);
void btlDispGXInit2DRasta(void);
void btlDispGXQuads2DRasta(f32 x0, f32 y0, f32 x1, f32 y1, u8 r, u8 g, u8 b, u8 a);
void btlGetScreenPoint(Vec* in, Vec* out);
void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
void BattleAudienceSoundHandBeat(void);
void BattleAudienceSoundCallKind(s32 kind);
void BattleAudienceSoundBooingKind(s32 kind);
void psndSFXOn(const char* name);
EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 size);
EffectEntry* effHitEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5);
EffectEntry* effStampN64Entry(s32 type, f32 x, f32 y, f32 z);

#define INTPL(mode, cur, steps, a, b) ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(a, b, mode, cur, steps)

USER_FUNC(btlevtcmd_ACSuccessEffect);
static USER_FUNC(star_stone_appear);
static USER_FUNC(wait_game_end);
static USER_FUNC(start_game);
static USER_FUNC(set_weapon);
USER_FUNC(end_muki);
USER_FUNC(main_muki);
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckStatus[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_StartWaitEvent[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_reset_move_color_lv_all[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_set_zoomSpeedLv[];
extern s32 evt_snd_sfxoff[];
extern s32 sac_ac_help_off[];
extern s32 sac_ac_help_on[];
extern s32 sac_enemy_slide_go[];
extern s32 sac_enemy_slide_return[];
extern s32 sac_handbeat[];
extern s32 sac_handbeat_end[];
extern s32 sac_mario_back_home[];
extern s32 sac_mario_item_on_end_evt[];
extern s32 sac_mario_item_on_evt[];
extern s32 sac_start_camera_evt[];
extern s32 sac_start_stardust[];
extern s32 sac_wao[];

typedef struct MukiObj { // 0x38
    s32 kind;          // 0x0
    s32 timer;         // 0x4
    s32 type;          // 0x8
    Vec pos;           // 0xc
    Vec scale;         // 0x18
    Vec rot;           // 0x24
    EffectEntry* eff;  // 0x30
    u8 alpha;          // 0x34
    u8 pad35[3];
} MukiObj;

typedef struct Muki3D { // 0x24
    s32 kind;          // 0x0
    s32 timer;         // 0x4
    Vec pos;           // 0x8
    Vec scale;         // 0x14
    MukiObj* link;     // 0x20
} Muki3D;

typedef struct MukiWork {
    u32 flags;             // 0x0
    s32 state;             // 0x4
    s32 timer;             // 0x8
    s32 timeLeft;          // 0xc
    s32 unitId;            // 0x10
    f32 f14;               // 0x14
    f32 f18;               // 0x18
    f32 f1c;               // 0x1c
    f32 f20;               // 0x20
    s32 t24;               // 0x24
    s32 t28;               // 0x28
    f32 f2c;               // 0x2c
    f32 f30;               // 0x30
    s32 t34;               // 0x34
    s32 kind38;            // 0x38
    s32 t3c;               // 0x3c
    s32 idx;               // 0x40
    Vec cpos;              // 0x44
    Vec cfrom;             // 0x50
    Vec cto;               // 0x5c
    Vec cscale;            // 0x68
    GXColor col74;         // 0x74
    Muki3D o3d[9];         // 0x78
    MukiObj obj[9];        // 0x1bc
    s32 star;              // 0x3b4
    s32 starTimer;         // 0x3b8
    Vec spos;              // 0x3bc
    Vec from;              // 0x3c8
    Vec to;                // 0x3d4
    u8 pad3e0[0xc];
    Vec scale;             // 0x3ec
    Vec rot;               // 0x3f8
    EffectEntry* eff;      // 0x404
    u8 weapon[0xc0];       // 0x408
} MukiWork;

typedef struct StarEffWork {
    u8 pad0[8];
    Vec pos;  // 0x8
    f32 scl;  // 0x14
    Vec rot;  // 0x18
} StarEffWork;

typedef struct IconEffWork {
    u8 pad0[8];
    Vec pos;  // 0x8
    f32 scl;  // 0x14
    Vec rot;  // 0x18
    u8 pad24[0x5f - 0x24];
    u8 alpha; // 0x5f
} IconEffWork;

static void disp_3D_alpha(CameraId cam, void* param);
static void disp_3D(CameraId cam, void* param);
static void disp_2D(CameraId cam, void* param);
static MukiWork* get_ptr(void);
static void main_star(void);
static void main_base(void);
void main_icon(s32 idx);
void main_point(s32 idx);
void main_cursor(void);


static s32 weapon[48];
s32 nice_event_pow[8];
s32 marioAttackEvent_Muki[254];

static s32 weapon[] = {
    (s32)"btl_wn_sac_mukimuki_body", 26869760, 0, (s32)"msg_mukimuki_body", 1677722368, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603120, 268435456, 770, (s32)"msg_sac_4", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Muki, 100, 0, 0,
};

EVT_BEGIN(nice_event_pow)
    CALL(btlevtcmd_ACSuccessEffect, LW(0), -100, 175, 0)
    RETURN
EVT_END()


USER_FUNC(main_muki) {
    MukiWork* w = get_ptr();
    s32* args = event->args;
    s32 i;

    if (isFirstCall) {
        memset(w, 0, 0x4C8);
        w->unitId = evtGetValue(event, args[0]);
        for (i = 0; i < 9; i++) {
            w->obj[i].eff = effStarStoneEntry(9, 0.0f, -1000.0f, 0.0f, 1.0f);
        }
    }
    main_base();
    main_cursor();
    for (i = 0; i < 9; i++) {
        main_point(i);
    }
    for (i = 0; i < 9; i++) {
        main_icon(i);
    }
    main_star();
    dispEntry(8, 901.0f, 1, disp_2D, 0);
    dispEntry(4, 0.0f, 1, disp_3D, 0);
    dispEntry(4, 0.0f, 2, disp_3D_alpha, 0);
    return 0;
}

static void main_base(void) {
    MukiWork* w = get_ptr();
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(mario, BtlUnit_GetBodyPartsId(mario));
    s32 i;
    s32 n;
    f32 d;
    f32 step;

    if (w->t24 > 0) {
        w->t24--;
    }
    if (w->t28 > 0) {
        w->t28--;
    }
    switch (w->state) {
    case 1:
        w->state = 2;
        w->f14 = w->f18 = 0.0f;
        w->f1c = w->f20 = 0.0f;
        w->f2c = -400.0f;
        w->f30 = 90.0f;
        w->timeLeft = 899;
        for (i = 0; i < 9; i++) {
            w->o3d[i].kind = 1;
        }
    case 2:
        n = 0;
        for (i = 0; i < 9; i++) {
            if (w->o3d[i].kind != 4) {
                break;
            }
            n++;
        }
        if (n == 9) {
            w->state = 3;
            w->timer = 0;
        }
        break;
    case 3:
        w->timer++;
        w->f2c = INTPL(4, w->timer, 30, -400.0f, -120.0f);
        if (w->timer >= 30) {
            w->state = 4;
            w->timer = 0;
            w->kind38 = 1;
            for (i = 0; i < 9; i++) {
                w->o3d[i].kind = 5;
            }
        }
        break;
    case 4:
        if (w->flags & 1) {
            w->t34++;
            if (w->t34 == 30) {
                BtlUnit_SetAnim(part, "M_X_1");
            }
        }
        w->timeLeft--;
        if (w->timeLeft <= 0) {
            w->state = 5;
            w->timer = 0;
            w->kind38 = 7;
            BtlUnit_SetAnim(part, "M_S_1");
            for (i = 0; i < 9; i++) {
                w->o3d[i].kind = 6;
                w->obj[i].kind = 9;
            }
            n = (s32)(w->f14 + w->f1c);
            if (n >= 1) {
                if (n == 1) {
                    n = 2;
                } else if (n == 2) {
                    n = 3;
                } else if (n == 3) {
                    n = 4;
                } else if (n == 4) {
                    n = 5;
                } else if (n >= 5) {
                    n = 6;
                }
                evtEntry(nice_event_pow, 0, 0x20)->lwData[0] = n;
            }
        }
        break;
    case 5:
        n = 0;
        for (i = 0; i < 9; i++) {
            if (w->o3d[i].kind != 8) {
                break;
            }
            n++;
        }
        if (n == 9) {
            w->state = 6;
            w->timer = 0;
        }
        break;
    case 6:
        w->timer++;
        if (w->timer >= 30) {
            w->state = 7;
            w->timer = 0;
        }
        break;
    case 0:
    case 7:
        break;
    }
    d = w->f14 - w->f18;
    if (d != 0.0f) {
        if (d > 0.0f) {
            step = (0.1f * d < 0.1f) ? 0.1f : 0.1f * d;
            w->f18 += step;
            if (w->f14 - w->f18 < 0.0f) {
                w->f18 = w->f14;
            }
        } else {
            step = (0.1f * d > -0.1f) ? 0.1f : -0.1f * d;
            w->f18 -= step;
            if (w->f14 - w->f18 > 0.0f) {
                w->f18 = w->f14;
            }
        }
    }
    d = w->f1c - w->f20;
    if (d != 0.0f) {
        if (d > 0.0f) {
            step = (0.1f * d < 0.1f) ? 0.1f : 0.1f * d;
            w->f20 += step;
            if (w->f1c - w->f20 < 0.0f) {
                w->f20 = w->f1c;
            }
        } else {
            step = (0.1f * d > -0.1f) ? 0.1f : -0.1f * d;
            w->f20 -= step;
            if (w->f1c - w->f20 > 0.0f) {
                w->f20 = w->f1c;
            }
        }
    }
}

#define AUD_CALL(num)                         \
    if ((num) >= 1 && (num) <= 49) {          \
        BattleAudienceSoundCallKind(1);       \
    }                                         \
    if ((num) >= 50 && (num) <= 99) {         \
        BattleAudienceSoundCallKind(1);       \
        BattleAudienceSoundHandBeat();        \
    }                                         \
    if ((num) >= 100 && (num) <= 149) {       \
        BattleAudienceSoundCallKind(2);       \
    }                                         \
    if ((num) >= 150) {                       \
        BattleAudienceSoundCallKind(2);       \
        BattleAudienceSoundHandBeat();        \
    }

void main_cursor(void) {
    MukiWork* w = get_ptr();
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(mario, BtlUnit_GetBodyPartsId(mario));
    s32 num = BattleAudience_GetAudienceNum();
    MukiObj* ob;
    f32 prev;
    f32 x, y, z;
    EffectEntry* eff;

    switch (w->kind38) {
    case 1:
        if (w->o3d[4].kind < 5) {
            break;
        }
        w->kind38 = 2;
        w->cpos = w->o3d[4].pos;
        w->cpos.z += 5.0f;
        w->cscale = (Vec){0.5f, 0.5f, 1.0f};
        w->idx = 4;
        w->col74 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    case 2:
        w->col74 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
        if (w->t34 >= 120) {
            BtlUnit_SetAnim(part, "M_I_Y");
            w->flags &= ~1;
            w->t34 = 0;
        }
        if (keyGetButtonTrg(0) & 0x100) {
            w->kind38 = 5;
            ob = w->o3d[w->idx].link;
            if (ob) {
                ob->kind = 5;
                effHitEntry(0, 5, ob->pos.x, ob->pos.y, ob->pos.z, 1.0f);
                switch (ob->type) {
                case 0:
                    prev = w->f14;
                    w->f14 += 0.25f;
                    if (w->f14 > 9.0f) {
                        w->f14 = 9.0f;
                    }
                    if ((s32)w->f14 > (s32)prev) {
                        w->t24 = 60;
                        psndSFXOn("SFX_BTL_SAC_BODY6");
                        AUD_CALL(num)
                    }
                    psndSFXOn("SFX_BTL_SAC_BODY4");
                    break;
                case 1:
                    prev = w->f1c;
                    w->f1c += 0.25f;
                    if (w->f1c > 9.0f) {
                        w->f1c = 9.0f;
                    }
                    if ((s32)w->f1c > (s32)prev) {
                        w->t28 = 60;
                        psndSFXOn("SFX_BTL_SAC_BODY6");
                        AUD_CALL(num)
                    }
                    psndSFXOn("SFX_BTL_SAC_BODY4");
                    break;
                case 2:
                    BtlUnit_SetAnim(part, "M_D_1");
                    BtlUnit_GetPos(mario, &x, &y, &z);
                    eff = effStampN64Entry(2, x, 20.0f + y, 10.0f + z);
                    ((u8*)eff->userdata)[0x38] = 0;
                    ((u8*)eff->userdata)[0x39] = 200;
                    ((u8*)eff->userdata)[0x3a] = 0;
                    ((u8*)eff->userdata)[0x3b] = 0;
                    ((u8*)eff->userdata)[0x3c] = 10;
                    ((u8*)eff->userdata)[0x3d] = 0;
                    w->t34 = 0;
                    w->flags |= 1;
                    psndSFXOn("SFX_BTL_SAC_BODY5");
                    if (num >= 1 && num <= 49) {
                        BattleAudienceSoundBooingKind(1);
                    }
                    if (num >= 50 && num <= 99) {
                        BattleAudienceSoundBooingKind(1);
                    }
                    if (num >= 100 && num <= 149) {
                        BattleAudienceSoundBooingKind(2);
                    }
                    if (num >= 150) {
                        BattleAudienceSoundBooingKind(3);
                    }
                    break;
                }
            }
        }
        if (keyGetDirTrg(0) & 0x8000) {
            if (w->idx % 3 != 2) {
                w->kind38 = 3;
                w->idx++;
            }
        }
        if (keyGetDirTrg(0) & 0x4000) {
            if (w->idx % 3) {
                w->kind38 = 3;
                w->idx--;
            }
        }
        if (keyGetDirTrg(0) & 0x1000) {
            if (w->idx / 3) {
                w->kind38 = 3;
                w->idx -= 3;
            }
        }
        if (keyGetDirTrg(0) & 0x2000) {
            if (w->idx / 3 != 2) {
                w->kind38 = 3;
                w->idx += 3;
            }
        }
        break;
    case 3:
        w->kind38 = 4;
        w->t3c = 0;
        w->cfrom = w->cpos;
        w->cto = w->o3d[w->idx].pos;
        psndSFXOn("SFX_BTL_SAC_BODY3\0\0");
    case 4:
        w->t3c++;
        w->col74 = (GXColor){0x00, 0x00, 0xFF, 0xFF};
        if (!(w->flags & 1)) {
            w->cpos.x = INTPL(4, w->t3c, 5, w->cfrom.x, w->cto.x);
            w->cpos.y = INTPL(4, w->t3c, 5, w->cfrom.y, w->cto.y);
            if (w->t3c >= 5) {
                w->kind38 = 2;
            }
        } else {
            w->cpos.x = INTPL(4, w->t3c, 25, w->cfrom.x, w->cto.x);
            w->cpos.y = INTPL(4, w->t3c, 25, w->cfrom.y, w->cto.y);
            if (w->t3c >= 25) {
                w->kind38 = 2;
            }
        }
        break;
    case 5:
        w->kind38 = 6;
        w->t3c = 0;
    case 6:
        w->t3c++;
        w->col74 = (GXColor){0xFF, 0x00, 0x00, 0xFF};
        if (w->t3c >= 1) {
            w->kind38 = 2;
            w->t3c = 0;
        }
        break;
    case 0:
    case 7:
        break;
    }
}

void main_point(s32 idx) {
    MukiWork* w = get_ptr();
    Muki3D* o = &w->o3d[idx];
    s32 i;

    switch (o->kind) {
    case 1: {
        o->kind = 2;
        o->timer = irand(30) + 30;
        {
        Vec p = {0.0f, 0.0f, 20.0f};
        p.x = (f32)((idx % 3) * 48 - 48);
        p.y = (f32)(125 - (idx / 3) * 48);
        o->pos = p;
        }
        o->scale = (Vec){0.0f, 0.0f, 1.0f};
        o->link = NULL;
    }
    case 2:
        o->timer--;
        if (o->timer <= 30) {
            o->scale.x = o->scale.y = INTPL(0, 30 - o->timer, 30, 0.0f, 0.5f);
        }
        if (o->timer <= 0) {
            o->kind = 3;
            o->timer = 0;
        }
        break;
    case 3:
        o->kind = 4;
        o->timer = 0;
        o->scale = (Vec){0.5f, 0.5f, 1.0f};
        break;
    case 5:
        if (o->link) {
            if (o->link->kind == 0) {
                o->link = NULL;
            }
        } else if (irand(65) == 0) {
            for (i = 0; i < 9; i++) {
                MukiObj* ob = &w->obj[i];
                if (ob->kind == 0) {
                    ob->kind = 1;
                    ob->pos = o->pos;
                    ob->pos.z = 0.0f;
                    o->link = ob;
                    break;
                }
            }
        }
        break;
    case 6:
        o->kind = 7;
        o->timer = irand(30) + 30;
        o->link = NULL;
    case 7:
        o->timer--;
        if (o->timer <= 30) {
            o->scale.x = o->scale.y = INTPL(0, 30 - o->timer, 30, 0.5f, 0.0f);
        }
        if (o->timer <= 0) {
            o->kind = 8;
            o->timer = 0;
        }
        break;
    case 0:
    case 4:
    case 8:
        break;
    }
}

void main_icon(s32 idx) {
    MukiWork* w = get_ptr();
    MukiObj* o = &w->obj[idx];

    switch (o->kind) {
    case 0:
        o->pos = (Vec){0.0f, -1000.0f, 0.0f};
        o->alpha = 0xFF;
        break;
    case 1:
        o->kind = 2;
        o->timer = 0;
        o->type = irand(3);
        o->rot.y = 0.0f;
        o->scale = (Vec){0.3f, 0.3f, 0.3f};
    case 2:
        o->timer++;
        o->rot.y = INTPL(4, o->timer, 30, 180.0f, 1080.0f);
        o->alpha = INTPL(0, o->timer, 30, 0.0f, 255.0f);
        if (o->timer >= 30) {
            o->kind = 7;
        }
        break;
    case 3:
        o->kind = 4;
        o->timer = 0;
        o->rot.y = 0.0f;
    case 4:
        o->timer++;
        o->rot.y = INTPL(1, o->timer, 30, 0.0f, 900.0f);
        o->alpha = INTPL(0, o->timer, 30, 255.0f, 0.0f);
        if (o->timer >= 30) {
            o->kind = 0;
        }
        break;
    case 5:
        o->kind = 6;
    case 6:
        o->kind = 0;
        break;
    case 7:
        o->kind = 8;
        o->timer = 0;
        o->rot.y = 0.0f;
        break;
    case 8:
        o->timer++;
        o->alpha = 0xFF;
        if (o->timer >= 90) {
            o->kind = 3;
        }
        break;
    case 9:
        if (o->alpha >= 8) {
            o->alpha -= 8;
        } else {
            o->alpha = 0;
        }
        break;
    }
    if (o->eff) {
        IconEffWork* e = (IconEffWork*)o->eff->userdata;
        e->pos.x = o->pos.x;
        e->pos.y = o->pos.y;
        e->pos.z = o->pos.z;
        e->rot.x = o->rot.x;
        e->rot.y = o->rot.y;
        e->rot.z = o->rot.z;
        e->scl = 9.0f * o->scale.x;
        e->alpha = o->alpha;
    }
}

static void main_star(void) {
    MukiWork* w = get_ptr();
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);

    switch (w->star) {
    case 1:
        w->star = 2;
        w->starTimer = 0;
        w->eff = effStarStoneEntry(2, 0.0f, -1000.0f, 0.0f, 1.0f);
        BtlUnit_GetPos(mario, &w->spos.x, &w->spos.y, &w->spos.z);
        w->spos.y += mario->mSizeMultiplier * (f32)mario->mHeight + 37.0f;
        w->from = w->spos;
        w->to = w->spos;
        w->to.y += 50.0f;
        w->to.z += -1.0f;
        w->scale = (Vec){0.0f, 0.0f, 0.0f};
        w->rot = (Vec){0.0f, 0.0f, 0.0f};
    case 2:
        w->starTimer++;
        if (w->starTimer <= 100) {
            w->spos.x = INTPL(0, w->starTimer, 100, w->from.x, w->to.x);
            w->spos.y = INTPL(0, w->starTimer, 100, w->from.y, w->to.y);
            w->spos.z = INTPL(0, w->starTimer, 100, w->from.z, w->to.z);
            w->scale.x = w->scale.y = w->scale.z = INTPL(0, w->starTimer, 100, 0.0f, 2.0f);
        } else {
            w->spos.x = w->to.x;
            w->spos.y = w->to.y;
            w->spos.z = w->to.z;
            w->scale.x = w->scale.y = w->scale.z = 2.0f;
        }
        w->rot.y = INTPL(4, w->starTimer, 120, 0.0f, 2160.0f);
        if (w->starTimer >= 120) {
            w->star = 3;
            w->starTimer = 0;
            w->from = w->spos;
            w->to.y = 300.0f;
        }
        break;
    case 3:
        w->starTimer++;
        w->spos.y = INTPL(1, w->starTimer, 60, w->from.y, w->to.y);
        if (w->starTimer >= 60) {
            w->star = 5;
            w->starTimer = 0;
        }
        break;
    case 0:
    case 4:
    case 5:
        break;
    }
    if (w->eff) {
        StarEffWork* e = (StarEffWork*)w->eff->userdata;
        e->pos.x = w->spos.x;
        e->pos.y = w->spos.y;
        e->pos.z = w->spos.z;
        e->rot.x = w->rot.x;
        e->rot.y = w->rot.y;
        e->rot.z = w->rot.z;
        e->scl = 1.5f * w->scale.x;
    }
}

USER_FUNC(end_muki) {
    MukiWork* w = get_ptr();
    s32 i;

    effDelete(*(EffectEntry**)((u8*)w->eff->userdata + 0x34));
    effDelete(w->eff);
    for (i = 0; i < 9; i++) {
        effDelete(w->obj[i].eff);
    }
    return 2;
}

#define TEXPLANE2(m, id, c) ((void (*)(Mtx, u32, GXColor, s32))btlDispTexPlane2)(m, id, c, 0)
static void disp_2D(CameraId cam, void* param) {
    MukiWork* w = get_ptr();
    Mtx m;
    Vec s;
    GXColor col[4];
    f32 x;
    f32 y;
    f32 d;
    f32 frac;
    u8 r, g, b, a;

    if (w->state >= 2 && w->state <= 7) {
        Vec p = {0.0f, 0.0f, 0.0f};
        GXColor c;
        s32 t;
        p.x = w->f2c;
        p.y = w->f30;
        p.z = 0.0f;
        s = p;
        btlGetScreenPoint(&s, &s);
        x = s.x;
        y = s.y;
        c = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
        PSMTXTrans(m, x - 32.0f - 8.0f, y, 0.0f);
        TEXPLANE2(m, 0x43, c);
        PSMTXScale(m, 16.0f, 1.0f, 1.0f);
        PSMTXTransApply(m, m, x, y, 0.0f);
        TEXPLANE2(m, 0x44, c);
        PSMTXScale(m, -1.0f, 1.0f, 1.0f);
        PSMTXTransApply(m, m, 8.0f + (32.0f + x), y, 0.0f);
        TEXPLANE2(m, 0x43, c);
        x = x - 32.0f - 8.0f;
        frac = w->f18 - (f32)(s32)w->f18;
        btlDispGXInit2DRasta();
        GXLoadPosMtxImm(camGetPtr(8)->view, 0);
        d = w->f14 - w->f18;
        if (d != 0.0f) {
            r = 0xFF; g = 0xB4; b = 0xB4; a = 0xFF;
        } else {
            r = 0xF0; g = 0xA0; b = 0xA0; a = 0xFF;
        }
        btlDispGXQuads2DRasta(x, 8.0f + y, x + 80.0f * frac, y - 8.0f, r, g, b, a);
        t = w->t24 % 12;
        if (t >= 0 && t <= 5) {
            PSMTXScale(m, 0.5f, 0.5f, 0.5f);
            PSMTXTransApply(m, m, x - 30.0f, y, 0.0f);
            col[0] = col[1] = (GXColor){0xE9, 0x4A, 0x3F, 0xFF};
            col[2] = col[3] = (GXColor){0xFE, 0xE6, 0x3E, 0xFF};
            ((void (*)(Mtx, u32, GXColor, GXColor, GXColor, GXColor, s32))btlDispTexPlane3)(m, 0x45, col[0], col[1], col[2], col[3], 0);
            PSMTXScale(m, 0.7f, 0.7f, 0.7f);
            PSMTXTransApply(m, m, x - 35.0f, y - 14.0f, 0.0f);
            iconDispGx2(m, 0x10, 0x1ED);
            PSMTXScale(m, 0.7f, 0.7f, 0.7f);
            PSMTXTransApply(m, m, x - 25.0f, y - 14.0f, 0.0f);
            iconNumberDispGx(m, (s32)w->f18, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        }
    }
    if (w->state >= 2 && w->state <= 7) {
        Vec p = {0.0f, 0.0f, 0.0f};
        GXColor c;
        s32 t;
        p.x = w->f2c;
        p.y = w->f30 - 30.0f;
        p.z = 0.0f;
        s = p;
        btlGetScreenPoint(&s, &s);
        x = s.x;
        y = s.y;
        c = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
        PSMTXTrans(m, x - 32.0f - 8.0f, y, 0.0f);
        TEXPLANE2(m, 0x43, c);
        PSMTXScale(m, 16.0f, 1.0f, 1.0f);
        PSMTXTransApply(m, m, x, y, 0.0f);
        TEXPLANE2(m, 0x44, c);
        PSMTXScale(m, -1.0f, 1.0f, 1.0f);
        PSMTXTransApply(m, m, 8.0f + (32.0f + x), y, 0.0f);
        TEXPLANE2(m, 0x43, c);
        x = x - 32.0f - 8.0f;
        frac = w->f20 - (f32)(s32)w->f20;
        btlDispGXInit2DRasta();
        GXLoadPosMtxImm(camGetPtr(8)->view, 0);
        if (d != 0.0f) {
            r = 0xB4; g = 0xB4; b = 0xFF; a = 0xFF;
        } else {
            r = 0xA0; g = 0xA0; b = 0xF0; a = 0xFF;
        }
        btlDispGXQuads2DRasta(x, 8.0f + y, x + 80.0f * frac, y - 8.0f, r, g, b, a);
        t = w->t28 % 12;
        if (t >= 0 && t <= 5) {
            PSMTXScale(m, 0.5f, 0.5f, 0.5f);
            PSMTXTransApply(m, m, x - 30.0f, y, 0.0f);
            col[0] = col[1] = (GXColor){0x3F, 0x3F, 0xE9, 0xFF};
            col[2] = col[3] = (GXColor){0x74, 0xC9, 0xFF, 0xFF};
            ((void (*)(Mtx, u32, GXColor, GXColor, GXColor, GXColor, s32))btlDispTexPlane3)(m, 0x45, col[0], col[1], col[2], col[3], 0);
            PSMTXScale(m, 0.7f, 0.7f, 0.7f);
            PSMTXTransApply(m, m, x - 35.0f, y - 14.0f, 0.0f);
            iconDispGx2(m, 0x10, 0x1ED);
            PSMTXScale(m, 0.7f, 0.7f, 0.7f);
            PSMTXTransApply(m, m, x - 25.0f, y - 14.0f, 0.0f);
            iconNumberDispGx(m, (s32)w->f20, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        }
    }
}

static void disp_3D(CameraId cam, void* param) {
    MukiWork* w = get_ptr();
    s32 a[8] = {-8, 8, 8, 8, 8, -8, -8, -8};
    s32 b[8] = {-24, 24, 24, 24, 24, -24, -24, -24};
    s32 c[8] = {1, 1, -1, 1, -1, -1, 1, -1};
    Muki3D* o;
    s32 i, j;
    Mtx m;
    for (i = 0; i < 9; i++) {
        o = &w->o3d[i];
        if (o->kind >= 2 && o->kind < 8) {
            for (j = 0; j < 4; j++) {
                PSMTXScale(m, o->scale.x * (f32)c[j * 2], o->scale.y * (f32)c[j * 2 + 1], o->scale.z);
                PSMTXTransApply(m, m, o->pos.x, o->pos.y, o->pos.z);
                PSMTXTransApply(m, m, o->scale.x * (f32)a[j * 2], o->scale.y * (f32)a[j * 2 + 1], 0.0f);
                ((void (*)(Mtx, u32, GXColor, s32))btlDispTexPlane2)(m, 0x42, (GXColor){0xDE, 0xDE, 0xDE, 0xFF}, 0);
            }
        }
    }
    if (w->kind38 >= 2 && w->kind38 < 7) {
        for (j = 0; j < 4; j++) {
            PSMTXScale(m, w->cscale.x * (f32)c[j * 2], w->cscale.y * (f32)c[j * 2 + 1], w->cscale.z);
            PSMTXTransApply(m, m, w->cpos.x, w->cpos.y, w->cpos.z);
            PSMTXTransApply(m, m, w->cscale.x * (f32)b[j * 2], w->cscale.y * (f32)b[j * 2 + 1], 0.0f);
            TEXPLANE2(m, 0x41, w->col74);
        }
    }
}

static void disp_3D_alpha(CameraId cam, void* param) {
    MukiWork* w = get_ptr();
    s32 i;
    MukiObj* o;
    Mtx m;
    GXColor col[4];
    for (i = 0; i < 9; i++) {
        o = &w->obj[i];
        if (o->kind >= 1 && o->kind <= 9) {
            f32 a;
            f32 c;
            switch (o->type) {
            case 0:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot.y);
                PSMTXScaleApply(m, m, 2.0f * o->scale.x, 2.0f * o->scale.y, o->scale.z);
                PSMTXTransApply(m, m, o->pos.x, o->pos.y, o->pos.z);
                a = 2.0f * o->rot.y * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                {
                GXColor ca = {0xE9, 0x4A, 0x3F, 0};
                GXColor cb = {0xFE, 0xE6, 0x3E, 0};
                ca.a = o->alpha;
                cb.a = o->alpha;
                col[0] = col[1] = ca;
                col[2] = col[3] = cb;
                ((void (*)(Mtx, u32, GXColor, GXColor, GXColor, GXColor, s32))btlDispTexPlane3)(m, 0x45, col[0], col[1], col[2], col[3], 0);
                }
                break;
            case 1:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot.y);
                PSMTXScaleApply(m, m, 2.0f * o->scale.x, 2.0f * o->scale.y, o->scale.z);
                PSMTXTransApply(m, m, o->pos.x, o->pos.y, o->pos.z);
                a = 2.0f * o->rot.y * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                {
                GXColor ca = {0x3F, 0x3F, 0xE9, 0};
                GXColor cb = {0x74, 0xC9, 0xFF, 0};
                ca.a = o->alpha;
                cb.a = o->alpha;
                col[0] = col[1] = ca;
                col[2] = col[3] = cb;
                ((void (*)(Mtx, u32, GXColor, GXColor, GXColor, GXColor, s32))btlDispTexPlane3)(m, 0x45, col[0], col[1], col[2], col[3], 0);
                }
                break;
            case 2:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot.y);
                PSMTXScaleApply(m, m, o->scale.x, o->scale.y, o->scale.z);
                PSMTXTransApply(m, m, o->pos.x, o->pos.y, o->pos.z);
                a = 2.0f * o->rot.y * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                {
                GXColor ca = {0xFF, 0xFF, 0xFF, 0};
                ca.a = o->alpha;
                col[0] = ca;
                TEXPLANE2(m, 0x31, col[0]);
                }
                break;
            }
        }
    }
}

#pragma dont_inline on
static MukiWork* get_ptr(void) {
    return (MukiWork*)((u8*)_battleWorkPointer + 0x1f4c);
}

#pragma dont_inline reset

static USER_FUNC(set_weapon) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 power = evtGetValue(event, args[1]);
    MukiWork* w = get_ptr();
    memcpy(w->weapon, weapon, 0xc0);
    switch (type) {
    case 0:
        w->weapon[0x96] = 100;
        w->weapon[0x97] = 3;
        w->weapon[0x98] = power;
        break;
    case 1:
        w->weapon[0x99] = 100;
        w->weapon[0x9a] = 3;
        w->weapon[0x9b] = power;
        break;
    }
    evtSetValue(event, args[2], (s32)w->weapon);
    return 2;
}

static USER_FUNC(start_game) {
    MukiWork* w = get_ptr();
    w->state = 1;
    return 2;
}

static USER_FUNC(wait_game_end) {
    MukiWork* w = get_ptr();
    s32* args = event->args;
    if (w->state == 7) {
        evtSetValue(event, args[0], (s32)w->f14);
        evtSetValue(event, args[1], (s32)w->f1c);
        return 2;
    }
    return 0;
}

static USER_FUNC(star_stone_appear) {
    MukiWork* w = get_ptr();
    w->star = 1;
    return 2;
}

s32 marioAttackEvent_Muki[] = {
    196699, (s32)btlevtcmd_GetUnitId, -4, -29999986, 196699, (s32)btlevtcmd_GetBodyId, -29999986, -29999985,
    262235, (s32)btlevtcmd_CheckStatus, -29999986, 27, -30000000, 131097, -30000000, 0,
    131122, -29999986, -1, 33, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    131096, -29999997, -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 65627,
    (s32)btlevtcmd_reset_move_color_lv_all, 110, 131163, (s32)main_muki, -29999986, 112, 65630, (s32)sac_start_camera_evt,
    65546, 500, 65627, (s32)sac_enemy_slide_go, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_SAC_START1",
    -250000000, 0, -250000000, 65630, (s32)sac_mario_item_on_evt, 65546, 500, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_SAC_START2", -250000000, 0, -29999989, 65627, (s32)star_stone_appear,
    110, 65630, (s32)sac_start_stardust, 112, 65545, 100, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_SAC_START3", -250000000, 0, -250000000, 131163, (s32)evt_snd_sfxoff, -29999989,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65545, 40, 65630, (s32)sac_mario_item_on_end_evt,
    65630, (s32)sac_mario_back_home, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_Y", 65546,
    1000, 110, 65627, (s32)sac_handbeat, 112, 65627, (s32)sac_ac_help_on, 65627,
    (s32)start_game, 196699, (s32)wait_game_end, -30000000, -29999999, 65627, (s32)sac_ac_help_off, 65627,
    (s32)sac_handbeat_end, 65546, 500, 131122, -29999998, -30000000, 131125, -29999998,
    -29999999, 131097, -29999998, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 7,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoomSpeedLv, 0,
    2, 65546, 1000, 65627, (s32)sac_wao, 107, 65546, 1000,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)sac_enemy_slide_return, 65627, (s32)end_muki,
    109, 107, 65546, 400, 131097, -29999999, 0, 262235,
    (s32)set_weapon, 1, -29999999, -29999991, 131097, -29999986, -1, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999986, -29999985, -29999991, 256, -29999995, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -2, 1, -29999991, 256, -29999995,
    33, 109, 131097, -30000000, 0, 262235, (s32)set_weapon, 0,
    -30000000, -29999991, 131097, -29999986, -1, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999986, -29999985, -29999991, 256, -29999995, 33, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -2, 1, -29999991, 256, -29999995, 2, 33,
    33, 65627, (s32)sac_enemy_slide_return, 65546, 1000, 65627, (s32)end_muki, 65546,
    1000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
