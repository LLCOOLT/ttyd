// Star-power special move Sweet Treat (sac_genki): the target game and its recovery effects.
#include "version.h"
#include "icon_ids.h"
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
#include "battle/battle.h"
#include "eff/n64/eff_stamp_n64.h"
#include "battle/battle_audience.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/icondrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include "version.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/sac/sac_common.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/sac/sac_genki.h"
#include "battle/battle_sub.h"
#include "eff/eff_hit.h"
#include "eff/eff_recovery.h"
#include "eff/eff_stardust.h"
#include "eff/eff_starstone.h"
#include "eff/n64/eff_stardust_n64.h"
#include "libc_decls.h"
#include "statuswindow.h"
#include "battle/battle_disp.h"

static void weapon_entry(void);
// FAKE: sac_genki.c calls weapon_entry through this prototype (the types it was compiled with) instead of the one in battle/sac/sac_genki.h; same registers, behaviour-identical.
typedef void (*Weapon_entryLocalFn)(void);
// FAKE: sac_genki.c calls iconDispGxCol through this prototype (the types it was compiled with) instead of the one in driver/icondrv.h; same registers, behaviour-identical.
typedef void (*IconDispGxColU16S32Fn)(Mtx, u16, s32, GXColor);
// US battle texture ids are 0x16 higher for these entries.
#define BTL_TEX(id) ((id) + VERSION_PICK(0, 0x16))

typedef struct GenkiRing {
    s32 timer;
    Vec pos;
    f32 scale;
} GenkiRing;

typedef struct GenkiWeapon {
    s32 state;            // 0x00
    s32 timer;            // 0x04
    Vec pos;              // 0x08
    Vec trail[3];         // 0x14
    Vec vel;              // 0x38
    EffectEntry* eff;     // 0x44
    EffectEntry* effs[3]; // 0x48
} GenkiWeapon;

typedef struct GenkiObject {
    s32 state;                   // 0x00
    s32 timer;                   // 0x04
    s32 kind;                    // 0x08
    Vec pos;                     // 0x0C
    u8 reserved_18[0x2C - 0x18]; // 0x18, never accessed
} GenkiObject;

typedef struct GenkiStar {
    s32 state;        // 0x00
    s32 timer;        // 0x04
    s32 isStone;      // 0x08, 1: the star stone (star_stone_appear), never read
    Vec pos;          // 0x0C
    Vec start;        // 0x18
    Vec end;          // 0x24
    Vec vel;          // 0x30
    Vec scale;        // 0x3C
    Vec rot;          // 0x48
    f32 radius;       // 0x54
    f32 angle;        // 0x58
    f32 angleSpeed;   // 0x5C
    EffectEntry* eff; // 0x60
} GenkiStar;

typedef struct GenkiWork {
    s32 reserved_00;        // 0x00, never accessed
    s32 state;              // 0x04
    s32 reserved_08;        // 0x08, never accessed
    s32 mode;               // 0x0C
    s32 score0;             // 0x10
    s32 score1;             // 0x14
    s32 score2;             // 0x18
    f32 disp0;              // 0x1C
    f32 disp1;              // 0x20
    f32 disp2;              // 0x24
    s32 blink0;             // 0x28
    s32 blink1;             // 0x2C
    s32 blink2;             // 0x30
    EffectEntry* rec0;      // 0x34
    EffectEntry* rec1;      // 0x38
    EffectEntry* rec2;      // 0x3C
    s32 timeLeft;           // 0x40
    s32 marioState;         // 0x44
    s32 marioTimer;         // 0x48
    s32 objTimer;           // 0x4C
    s32 partyArg;           // 0x50
    s32 marioCnt;           // 0x54
    s32 weaponNum;          // 0x58
    s32* table;             // 0x5C
    s32 tableIdx;           // 0x60
    s32 targetState;        // 0x64
    s32 targetAngle;        // 0x68
    f32 targetRad;          // 0x6C
    f32 targetSpeed;        // 0x70
    Vec targetPos;          // 0x74
    GenkiRing ring[7];      // 0x80
    GenkiWeapon weapon[7];  // 0x10C
    GenkiObject object[10]; // 0x358
    GenkiStar star[7];      // 0x510
} GenkiWork;

static USER_FUNC(recover_cmd_disable);
static USER_FUNC(star_appear);
static USER_FUNC(status_on);
static USER_FUNC(get_score);
static USER_FUNC(object_get_num);
static USER_FUNC(object_entry);
static USER_FUNC(star_stone_appear);
static USER_FUNC(wait_game_end);
static USER_FUNC(start_game);
static void main_star1(void);
static void main_star0(s32 idx);
static void main_star(void);
static void main_object(s32 idx);
static void main_weapon(s32 idx);
static void main_target(void);
static void main_mario(void);
static void main_base(void);
static void disp_3D_alpha(CameraId cam, void* param);
static void disp_3D(CameraId cam, void* param);
static void disp_2D(CameraId cam, void* param);
static GenkiWork* get_ptr(void);

static USER_FUNC(main_genki) {
    GenkiWork* w = get_ptr();
    s32 i;
    s32 j;
    EvtWord* args;
    if (isFirstCall) {
        args = event->args;
        memset(w, 0, sizeof(GenkiWork));
        w->partyArg = evtGetValue(event, args[0]);
        w->mode = evtGetValue(event, args[1]);
        w->timeLeft = 900;
        w->score0 = w->score1 = w->score2 = 0;
        w->disp0 = w->disp1 = w->disp2 = 0.0f;
        if (w->mode == 0) {
            w->weaponNum = 3;
        } else {
            w->weaponNum = 7;
        }
        if (w->mode == 0) {
            w->table = BattleAlloc(100);
        } else {
            w->table = BattleAlloc(200);
        }
        w->rec0 = effRecoveryEntry(2, 0, 0.0f, -1000.0f, 0.0f);
        w->rec1 = effRecoveryEntry(2, 0, 0.0f, -1000.0f, 0.0f);
        w->rec2 = effRecoveryEntry(3, 0, 0.0f, -1000.0f, 0.0f);
        for (i = 0; i < 7; i++) {
            w->weapon[i].eff = effStarStoneEntry(i, 0.0f, -1000.0f, 0.0f, 1.0f);
            for (j = 0; j < 3; j++) {
                w->weapon[i].effs[j] = effStarStoneEntry(i + 7, 0.0f, -1000.0f, 0.0f, 1.0f);
            }
        }
    }
    main_base();
    main_mario();
    main_target();
    for (i = 0; i < w->weaponNum; i++) {
        main_weapon(i);
    }
    for (i = 0; i < 10; i++) {
        main_object(i);
    }
    main_star();
    dispEntry((CameraId)CAMERA_2D, 901.0f, 1, disp_2D, NULL);
    dispEntry((CameraId)CAMERA_3D, 0.0f, 1, disp_3D, NULL);
    dispEntry((CameraId)CAMERA_3D, 0.0f, 2, disp_3D_alpha, NULL);
    return 0;
}

static void main_base(void) {
    GenkiWork* w = get_ptr();
    s32 i;
    s32 j;
    s32 a;
    s32 n;

    if (w->disp0 > w->score0) {
        w->disp0 -= 1.0f;
        w->blink0 = 60;
    }
    if (w->disp0 < w->score0) {
        w->disp0 += 1.0f;
        w->blink0 = 60;
    }
    if (w->disp1 > w->score1) {
        w->disp1 -= 1.0f;
        w->blink1 = 60;
    }
    if (w->disp1 < w->score1) {
        w->disp1 += 1.0f;
        w->blink1 = 60;
    }
    if (w->disp2 > w->score2) {
        w->disp2 -= 1.0f;
        w->blink2 = 60;
    }
    if (w->disp2 < w->score2) {
        w->disp2 += 1.0f;
        w->blink2 = 60;
    }
    if (w->blink0 > 0) {
        w->blink0--;
    }
    if (w->blink1 > 0) {
        w->blink1--;
    }
    if (w->blink2 > 0) {
        w->blink2--;
    }

    switch (w->state) {
        case 1:
            w->state = 2;
            w->marioState = 1;
            w->targetState = 1;
            w->tableIdx = 0;
            if (w->mode == 0) {
                n = 0;
                for (i = 0; i < 7; i++) {
                    w->table[n++] = 0;
                }
                for (i = 0; i < 7; i++) {
                    w->table[n++] = 2;
                }
                for (i = 0; i < 8; i++) {
                    w->table[n++] = 4;
                }
                for (i = 0; i < 3; i++) {
                    w->table[n++] = 6;
                }
                for (i = 0; i < 200; i++) {
                    s32 t;
                    a = irand(25);
                    j = irand(25);
                    t = w->table[a];
                    w->table[a] = w->table[j];
                    w->table[j] = t;
                }
            } else {
                n = 0;
                for (i = 0; i < 12; i++) {
                    w->table[n++] = 0;
                }
                for (i = 0; i < 4; i++) {
                    w->table[n++] = 1;
                }
                for (i = 0; i < 12; i++) {
                    w->table[n++] = 2;
                }
                for (i = 0; i < 4; i++) {
                    w->table[n++] = 3;
                }
                for (i = 0; i < 12; i++) {
                    w->table[n++] = 4;
                }
                for (i = 0; i < 4; i++) {
                    w->table[n++] = 5;
                }
                for (i = 0; i < 2; i++) {
                    w->table[n++] = 6;
                }
                for (i = 0; i < 200; i++) {
                    s32 t;
                    a = irand(50);
                    j = irand(50);
                    t = w->table[a];
                    w->table[a] = w->table[j];
                    w->table[j] = t;
                }
            }
        case 2:
            w->objTimer--;
            if (w->objTimer <= 0) {
                if (w->mode == 0) {
                    w->objTimer = 37;
                } else {
                    w->objTimer = 18;
                }
                if (w->timeLeft > 0) {
                    ((void (*)(void))object_entry)();
                }
            }
            if (w->timeLeft <= 0) {
                n = w->weaponNum;
                for (j = 0; j < n; j++) {
                    if (w->weapon[j].state != 0) {
                        break;
                    }
                }
                for (i = 0; i < 10; i++) {
                    if (w->object[i].state != 0) {
                        break;
                    }
                }
                if (j == n && i == 10) {
                    w->state = 3;
                }
            } else {
                w->timeLeft--;
            }
            break;
        case 0:
        case 3:
            break;
    }
}

static void main_mario(void) {
    GenkiWork* w = get_ptr();
    s32 stick = keyGetStickX(0);
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(mario, BtlUnit_GetBodyPartsId(mario));
    f32 x, y, z;
    EffectEntry* eff;

    if (w->marioState >= 1 && w->marioState <= 4 && w->timeLeft <= 0 &&
        ((s32 (*)(void))object_get_num)() == 0) {
        w->marioState = 5;
        w->targetState = 4;
        BtlUnit_SetAnim(part, "M_S_1");
    }
    switch (w->marioState) {
        case 1:
            if (stick < -40) {
                w->marioState = 2;
                w->marioTimer = 0;
                w->marioCnt = 10;
                BtlUnit_SetAnim(part, "M_C_2A");
            }
            break;
        case 2:
            if (stick > -20) {
                w->marioState = 1;
                ((Weapon_entryLocalFn)weapon_entry)();
            } else {
                w->marioCnt--;
                if (w->marioCnt == 2) {
                    BtlUnit_SetAnim(part, "M_C_2B");
                }
                if (w->marioCnt <= 0 && w->mode == 1) {
                    w->marioCnt = 10;
                    ((Weapon_entryLocalFn)weapon_entry)();
                }
            }
            break;
        case 3:
            w->marioState = 4;
            w->marioTimer = 0;
            BtlUnit_SetAnim(part, "M_D_1");
            BtlUnit_GetPos(mario, &x, &y, &z);
            eff = effStampN64Entry(2, x, 20.0f + y, 10.0f + z);
            ((EffStampN64Work*)eff->userdata)->r = 0;
            ((EffStampN64Work*)eff->userdata)->g = 200;
            ((EffStampN64Work*)eff->userdata)->b = 0;
            ((EffStampN64Work*)eff->userdata)->r2 = 0;
            ((EffStampN64Work*)eff->userdata)->g2 = 10;
            ((EffStampN64Work*)eff->userdata)->b2 = 0;
        case 4:
            w->marioTimer++;
            if (w->marioTimer == 30) {
                BtlUnit_SetAnim(part, "M_X_1");
            }
            if (w->marioTimer == 180) {
                BtlUnit_SetAnim(part, "M_I_Y");
                w->marioState = 1;
                w->marioTimer = 0;
            }
            break;
        case 5:
            break;
    }
}

// inlining off for main_target, as in the original (the object differs without it)
#pragma dont_inline on
static void main_target(void) {
    GenkiWork* w = get_ptr();
    switch (w->targetState) {
        case 0:
            break;
        case 1:
            w->targetAngle = 0;
            w->targetRad = 30.0f;
            w->targetSpeed = 1.25f;
            w->targetState = 2;
        case 2:
            w->targetAngle++;
            if (w->targetAngle >= 360) {
                w->targetAngle = w->targetAngle - 360.0f;
            }
            w->targetRad += w->targetSpeed;
            if (w->targetRad >= 60.0f) {
                w->targetRad = 60.0f;
                w->targetSpeed = -1.25f;
                w->targetState = 3;
            }
            break;
        case 3:
            w->targetAngle++;
            if (w->targetAngle >= 360) {
                w->targetAngle = w->targetAngle - 360.0f;
            }
            w->targetRad += w->targetSpeed;
            if (w->targetRad <= 0.0f) {
                w->targetRad = 0.0f;
                w->targetSpeed = 1.25f;
                w->targetState = 2;
            }
            break;
        case 4:
            break;
    }
}
#pragma dont_inline reset

static void main_weapon(s32 idx) {
    GenkiWork* w = get_ptr();
    GenkiWeapon* wp = &w->weapon[idx];
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    f32 ang = 3.141592f * (2.0f * w->targetRad) / 360.0f;
    s32 audience = BattleAudience_GetAudienceNum();
    f32 x, y, z;
    s32 i;
    GenkiObject* o;
    s32 near;
    f32 min;
    EffStarStoneWork* star;

    for (i = 2; i > 0; i--) {
        wp->trail[i] = wp->trail[i - 1];
    }
    wp->trail[0] = wp->pos;

    switch (wp->state) {
        case 0:
            wp->pos = (Vec){0.0f, -1000.0f, 0.0f};
            break;
        case 1:
            wp->timer--;
            if (wp->timer >= 0) {
                break;
            }
            wp->state = 2;
            BtlUnit_GetPos(mario, &wp->pos.x, &wp->pos.y, &wp->pos.z);
            wp->pos.x += 20.0f * mario->sizeMultiplier;
            wp->pos.y += 28.0f * mario->sizeMultiplier;
            wp->vel = (Vec){10.0f * (f32)cos(ang), 10.0f * (f32)sin(ang), 0.0f};
            for (i = 0; i < 7; i++) {
                GenkiRing* r = &w->ring[i];
                if (r->timer <= 0) {
                    r->timer = 30;
                    r->pos = w->targetPos;
                    r->scale = 2.0f * w->targetAngle;
                    break;
                }
            }
            BtlUnit_snd_se(mario, "SFX_BTL_SAC_HEART_SHOOT2", -250000000, 0);
        case 2:
            wp->pos.x += wp->vel.x;
            wp->pos.y += wp->vel.y;
            wp->vel.y -= 0.15f;
            BtlUnit_GetPos(mario, &x, &y, &z);
            if (wp->pos.x >= 250.0f || wp->pos.y >= 180.0f || wp->pos.y <= y) {
                wp->state = 3;
                break;
            }
            min = 10000000.0f;
            near = -1;
            for (i = 0; i < 10; i++) {
                o = &w->object[i];
                if (o->state == 2) {
                    f32 dx = wp->pos.x - o->pos.x;
                    f32 dy = wp->pos.y - o->pos.y;
                    f32 d = dx * dx + dy * dy;
                    if (d < min) {
                        min = d;
                        near = i;
                    }
                }
            }
            if (near == -1) {
                break;
            }
            o = &w->object[near];
            {
                f32 thr;
                switch (o->kind) {
                    case 6:
                        thr = 344.0f;
                        break;
                    case 0:
                    case 2:
                    case 4:
                        thr = 576.0f;
                        break;
                    default:
                        thr = 1296.0f;
                        break;
                }
                if (!(min <= thr && o->pos.y <= 200.0f)) {
                    break;
                }
            }
            wp->state = 3;
            o->state = 3;
            effStardustN64Entry(5, o->pos.x, o->pos.y, o->pos.z, 10.0f);
#if VERSION <= VERSION_DEMO_US
            effHitEntry(0, 10, o->pos.x, o->pos.y, o->pos.z, 1.0f);
#else
            effHitEntry(0, 5, o->pos.x, o->pos.y, o->pos.z, 1.0f);
#endif
            switch (o->kind) {
                case 0:
                    psndSFXOn_3D((const char*)0xA64, &wp->pos);
                    w->score0 += 1;
                    if (w->score0 >= 99) {
                        w->score0 = 99;
                    }
                    break;
                case 1:
                    psndSFXOn_3D((const char*)0xA66, &wp->pos);
                    w->score0 += 3;
                    if (w->score0 >= 99) {
                        w->score0 = 99;
                    }
                    break;
                case 2:
                    psndSFXOn_3D((const char*)0xA64, &wp->pos);
                    w->score1 += 1;
                    if (w->score1 >= 99) {
                        w->score1 = 99;
                    }
                    break;
                case 3:
                    psndSFXOn_3D((const char*)0xA66, &wp->pos);
                    w->score1 += 3;
                    if (w->score1 >= 99) {
                        w->score1 = 99;
                    }
                    break;
                case 4:
                    psndSFXOn_3D((const char*)0xA65, &wp->pos);
                    w->score2 += 1;
                    if (w->score2 >= 99) {
                        w->score2 = 99;
                    }
                    break;
                case 5:
                    psndSFXOn_3D((const char*)0xA67, &wp->pos);
                    w->score2 += 3;
                    if (w->score2 >= 99) {
                        w->score2 = 99;
                    }
                    break;
                case 6:
                    psndSFXOn_3D((const char*)0xA68, &wp->pos);
                    w->marioState = 3;
                    break;
            }
            switch (o->kind) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    if (audience >= 1 && audience <= 49) {
                        BattleAudienceSoundCallKind(1);
                    }
                    if (audience >= 50 && audience <= 99) {
                        BattleAudienceSoundCallKind(1);
                        BattleAudienceSoundHandBeat();
                    }
                    if (audience >= 100 && audience <= 149) {
                        BattleAudienceSoundCallKind(2);
                    }
                    if (audience >= 150) {
                        BattleAudienceSoundCallKind(2);
                        BattleAudienceSoundHandBeat();
                    }
                    break;
                case 6:
                    if (audience >= 1 && audience <= 49) {
                        BattleAudienceSoundBooingKind(1);
                    }
                    if (audience >= 50 && audience <= 99) {
                        BattleAudienceSoundBooingKind(1);
                    }
                    if (audience >= 100 && audience <= 149) {
                        BattleAudienceSoundBooingKind(2);
                    }
                    if (audience >= 150) {
                        BattleAudienceSoundBooingKind(3);
                    }
                    break;
            }
            break;
        case 3:
            wp->state = 0;
            break;
    }

    if (wp->eff) {
        star = wp->eff->userdata;
        star->position.x = wp->pos.x;
        star->position.y = wp->pos.y;
        star->position.z = wp->pos.z;
        star->scale = 1.125f;
        star->a = 255;
    }
    for (i = 0; i < 3; i++) {
        star = wp->effs[i]->userdata;
        star->position.x = wp->trail[i].x;
        star->position.y = wp->trail[i].y;
        star->position.z = wp->trail[i].z;
        star->scale = 1.125f;
        star->a = 255 - (i + 1) * 50;
    }
}

static void main_object(s32 idx) {
    GenkiWork* w = get_ptr();
    GenkiObject* o = &w->object[idx];
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    s32 kinds[3] = {0, 4, 2};
    f32 x, y, z;
    GenkiStar* s;
    s32 n;

    switch (o->state) {
        case 0:
            break;
        case 1:
            o->state = 2;
            o->timer = 0;
            if (w->mode == 0) {
                n = 25;
            } else {
                n = 50;
            }
            if (w->tableIdx < n) {
                o->kind = w->table[w->tableIdx];
            } else if (irand(w->mode == 0 ? 7 : 14) == 0) {
                o->kind = 6;
            } else {
                if (w->partyArg != -1) {
                    o->kind = kinds[irand(3)];
                } else {
                    o->kind = kinds[irand(2)];
                }
                if (irand(5) == 0 && w->mode == 1) {
                    switch (o->kind) {
                        case 0:
                            o->kind = 1;
                            break;
                        case 2:
                            o->kind = 3;
                            break;
                        case 4:
                            o->kind = 5;
                            break;
                    }
                }
            }
            if (w->partyArg == -1 && o->kind == 2) {
                o->kind = 0;
            }
            if (w->partyArg == -1 && o->kind == 3) {
                o->kind = 1;
            }
            w->tableIdx++;
            if (w->mode == 0) {
                s = &w->star[irand(7)];
            } else {
                s = &w->star[0];
            }
            BtlUnit_GetPos(mario, &x, &y, &z);
            o->pos.x = s->pos.x;
            o->pos.y = s->pos.y;
            o->pos.z = z + idx;
        case 2:
            if (w->mode == 0) {
                o->pos.y -= 1.32f;
            } else {
                o->pos.y -= 1.98f;
            }
            BtlUnit_GetPos(mario, &x, &y, &z);
            if (o->pos.y <= 15.0f + y) {
                o->state = 3;
                effStardustEntry(5, 10, 60, o->pos.x, 15.0f + y, o->pos.z, 30.0f, 30.0f);
            }
            o->timer++;
            if (o->timer > 120) {
                o->timer = 0;
            }
            break;
        case 3:
            o->state = 0;
            break;
    }
}

// inlining off for main_star, as in the original (the object differs without it)
#pragma dont_inline on
static void main_star(void) {
    GenkiWork* w = get_ptr();
    s32 i;
    if (w->mode == 0) {
        for (i = 0; i < 7; i++) {
            main_star0(i);
        }
    } else {
        main_star1();
    }
}
#pragma dont_inline reset

static void main_star0(s32 idx) {
    GenkiWork* w = get_ptr();
    GenkiStar* s = &w->star[idx];
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    f32 x, y, z;
    EffStarStoneWork* star;

    switch (s->state) {
        case 1:
            s->state = 2;
            s->timer = 0;
            s->eff = effStarStoneEntry(idx, 0.0f, -1000.0f, 0.0f, 1.0f);
            BtlUnit_GetPos(mario, &s->pos.x, &s->pos.y, &s->pos.z);
            s->pos.y += mario->sizeMultiplier * mario->height + 37.0f;
            s->start = s->pos;
            s->end = s->pos;
            s->end.y += 30.0f;
            s->scale = (Vec){0.0f, 0.0f, 0.0f};
            s->rot = (Vec){0.0f, 0.0f, 0.0f};
            s->radius = 0.0f;
            s->angle = 6.283184f * idx / 7.0f;
            s->angleSpeed = 0.1f;
        case 2:
            s->timer++;
            if (s->timer <= 100) {
                s->pos.y = intplGetValue(0, s->start.y, s->end.y, s->timer, 100);
                BtlUnit_GetPos(mario, &x, &y, &z);
                s->radius = intplGetValue(0, 0.0f, 40.0f, s->timer, 100);
                s->angle += s->angleSpeed;
                s->pos.x = s->radius * (f32)cos(s->angle) + x;
                s->pos.z = s->radius * (f32)sin(s->angle) + z;
                s->scale.x = s->scale.y = s->scale.z = intplGetValue(0, 0.0f, 0.75f, s->timer, 100);
            } else {
                s->pos.y = s->end.y;
                BtlUnit_GetPos(mario, &x, &y, &z);
                s->angle += s->angleSpeed;
                s->pos.x = s->radius * (f32)cos(s->angle) + x;
                s->pos.z = s->radius * (f32)sin(s->angle) + z;
                s->scale.x = s->scale.y = s->scale.z = 0.75f;
            }
            s->rot.y = intplGetValue(4, 0.0f, 2160.0f, s->timer, 120);
            if (s->timer >= 120) {
                s->state = 3;
                s->timer = 0;
                s->start = s->pos;
                s->end = (Vec){200.0f * rand() / 32767.0f, 180.0f, s->start.z};
                s->vel = (Vec){0.0f, 0.0f, 0.0f};
                s->vel.y = (2.0f * (s->end.y - s->start.y) - 60.0f * (60.0f * (0.2f - 0.01f * idx))) / 120.0f;
            }
            break;
        case 3:
            s->timer++;
            s->pos.x = intplGetValue(4, s->start.x, s->end.x, s->timer, 60);
            s->pos.y += s->vel.y;
            s->vel.y += 0.2f - 0.01f * idx;
            s->rot.y = 0.0f;
            s->scale.x = s->scale.y = s->scale.z = 0.75f;
            if (s->timer >= 60) {
                s->state = 4;
                s->timer = 0;
                if (irand(2) == 0) {
                    s->vel.x = -2.0f - 0.05f * idx;
                }
                s->vel.x = 2.0f + 0.05f * idx;
                s->vel.y = 0.0f;
            }
            break;
        case 4:
            s->pos.x += s->vel.x;
            if (s->pos.x < 0.0f) {
                s->vel.x = 3.0f + 0.05f * idx;
            }
            if (s->pos.x > 200.0f) {
                s->vel.x = -3.0f - 0.05f * idx;
            }
            s->vel.y += 0.1f + 0.01f * idx;
            if (s->vel.y >= 6.283184f) {
                s->vel.y -= 6.283184f;
            }
            s->pos.y = 10.0f * (f32)sin(s->vel.y) + 180.0f;
            if (w->timeLeft <= 0) {
                s->state = 5;
                s->timer = 0;
                s->pos = (Vec){0.0f, -1000.0f, 0.0f};
            }
            break;
        case 5:
            break;
    }
    if (s->eff) {
        star = s->eff->userdata;
        star->position.x = s->pos.x;
        star->position.y = s->pos.y;
        star->position.z = s->pos.z;
        star->spinY = s->rot.x;
        star->rotY = s->rot.y;
        star->tiltZ = s->rot.z;
        star->scale = 1.5f * s->scale.x;
    }
}

static void main_star1(void) {
    GenkiWork* w = get_ptr();
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    EffStarStoneWork* star;

    switch (w->star[0].state) {
        case 1:
            w->star[0].state = 2;
            w->star[0].timer = 0;
            w->star[0].eff = effStarStoneEntry(4, 0.0f, -1000.0f, 0.0f, 1.0f);
            BtlUnit_GetPos(mario, &w->star[0].pos.x, &w->star[0].pos.y, &w->star[0].pos.z);
            w->star[0].pos.y += mario->sizeMultiplier * mario->height + 37.0f;
            w->star[0].start = w->star[0].pos;
            w->star[0].end = w->star[0].pos;
            w->star[0].end.y += 50.0f;
            w->star[0].end.z += -1.0f;
            w->star[0].scale = (Vec){0.0f, 0.0f, 0.0f};
            w->star[0].rot = (Vec){0.0f, 0.0f, 0.0f};
        case 2:
            w->star[0].timer++;
            if (w->star[0].timer <= 100) {
                w->star[0].pos.x = intplGetValue(0, w->star[0].start.x, w->star[0].end.x, w->star[0].timer, 100);
                w->star[0].pos.y = intplGetValue(0, w->star[0].start.y, w->star[0].end.y, w->star[0].timer, 100);
                w->star[0].pos.z = intplGetValue(0, w->star[0].start.z, w->star[0].end.z, w->star[0].timer, 100);
                w->star[0].scale.x = w->star[0].scale.y = w->star[0].scale.z =
                    intplGetValue(0, 0.0f, 2.0f, w->star[0].timer, 100);
            } else {
                w->star[0].pos.x = w->star[0].end.x;
                w->star[0].pos.y = w->star[0].end.y;
                w->star[0].pos.z = w->star[0].end.z;
                w->star[0].scale.x = w->star[0].scale.y = w->star[0].scale.z = 2.0f;
            }
            w->star[0].rot.y = intplGetValue(4, 0.0f, 2160.0f, w->star[0].timer, 120);
            if (w->star[0].timer >= 120) {
                w->star[0].state = 3;
                w->star[0].timer = 0;
                w->star[0].start = w->star[0].pos;
                w->star[0].end = (Vec){200.0f * rand() / 32767.0f, 180.0f, w->star[0].start.z};
                w->star[0].vel = (Vec){0.0f, 0.0f, 0.0f};
                w->star[0].vel.y = (2.0f * (w->star[0].end.y - w->star[0].start.y) - 60.0f * (60.0f * 0.2f)) / 120.0f;
            }
            break;
        case 3:
            w->star[0].timer++;
            w->star[0].pos.x = intplGetValue(4, w->star[0].start.x, w->star[0].end.x, w->star[0].timer, 60);
            w->star[0].pos.y += w->star[0].vel.y;
            w->star[0].vel.y += 0.2f;
            w->star[0].rot.y = 0.0f;
            w->star[0].scale.x = w->star[0].scale.y = w->star[0].scale.z = 2.0f;
            if (w->star[0].timer >= 60) {
                w->star[0].state = 4;
                w->star[0].timer = 0;
                if (irand(2) == 0) {
                    w->star[0].vel.x = -2.0f;
                }
                w->star[0].vel.x = 2.0f;
                w->star[0].vel.y = 0.0f;
            }
            break;
        case 4:
            w->star[0].pos.x += w->star[0].vel.x;
            if (w->star[0].pos.x < 0.0f) {
                w->star[0].vel.x = 3.0f;
            }
            if (w->star[0].pos.x > 200.0f) {
                w->star[0].vel.x = -3.0f;
            }
            w->star[0].vel.y += 0.1f;
            if (w->star[0].vel.y >= 6.283184f) {
                w->star[0].vel.y -= 6.283184f;
            }
            w->star[0].pos.y = 10.0f * (f32)sin(w->star[0].vel.y) + 180.0f;
            if (w->timeLeft <= 0) {
                w->star[0].state = 5;
                w->star[0].timer = 0;
                w->star[0].pos = (Vec){0.0f, -1000.0f, 0.0f};
            }
            break;
        case 5:
            break;
    }
    if (w->star[0].eff) {
        star = w->star[0].eff->userdata;
        star->position.x = w->star[0].pos.x;
        star->position.y = w->star[0].pos.y;
        star->position.z = w->star[0].pos.z;
        star->spinY = w->star[0].rot.x;
        star->rotY = w->star[0].rot.y;
        star->tiltZ = w->star[0].rot.z;
        star->scale = 1.5f * w->star[0].scale.x;
    }
}

static USER_FUNC(end_genki) {
    GenkiWork* w = get_ptr();
    GenkiStar* s;
    GenkiWeapon* wp;
    s32 i;
    s32 j;
    for (i = 0; i < 7; i++) {
        s = &w->star[i];
        if (s->eff) {
            effDelete(((EffStarStoneWork*)s->eff->userdata)->dust);
            effDelete(s->eff);
        }
    }
    for (i = 0; i < 7; i++) {
        wp = &w->weapon[i];
        if (wp->eff) {
            effDelete(((EffStarStoneWork*)wp->eff->userdata)->dust);
            effDelete(wp->eff);
            for (j = 0; j < 3; j++) {
                effDelete(((EffStarStoneWork*)wp->effs[j]->userdata)->dust);
                effDelete(wp->effs[j]);
            }
        }
    }
    effDelete(w->rec0);
    effDelete(w->rec1);
    effDelete(w->rec2);
    BattleFree(w->table);
    return 2;
}

static void disp_2D(CameraId cam, void* param) {
}

#define genki_blink(t) ((t) % 12 >= 0 && (t) % 12 <= 5)

static void disp_3D(CameraId cam, void* param) {
    GenkiWork* w;
    GenkiObject* o;
    BattleUnit* mario;
    BattleUnit* party;
    u16 flags;
    s32 i;
    s32 icon;
    f32 ang;
    f32 mx, my, mz;
    f32 px, py, pz;
    Vec p;
    Vec p1;
    Mtx m;
    Mtx m2;
    RecoveryWork* rec;
    f32 s;

    w = get_ptr();
    mario = BattleGetMarioPtr(_battleWorkPointer);
    party = BattleGetPartyPtr(_battleWorkPointer);
    ang = 3.141592f * w->targetRad / 180.0f;

    if (w->state) {
        BtlUnit_GetHomePos(mario, &mx, &my, &mz);
        my += 60.0f;
        rec = w->rec0->userdata;
        rec->position.x = mx;
        rec->position.y = my - 10.0f;
        rec->position.z = 5.0f + mz;
        if (w->disp0 >= 10.0f) {
            p = (Vec){6.0f + mx, my, 8.0f + mz};
        } else {
            p = (Vec){mx, my, 8.0f + mz};
        }
        PSMTXTrans(m, p.x, p.y, p.z);
        if (genki_blink(w->blink0)) {
            iconNumberDispGx3D(m, w->disp0, 0, (GXColor){255, 255, 255, 255});
        }
        if (w->partyArg != -1) {
            BtlUnit_GetHomePos(party, &px, &py, &pz);
            py += 60.0f;
            rec = w->rec1->userdata;
            rec->position.x = px;
            rec->position.y = py - 10.0f;
            rec->position.z = 5.0f + pz;
            if (w->disp1 >= 10.0f) {
                p1 = (Vec){6.0f + px, py, 8.0f + pz};
            } else {
                p1 = (Vec){px, py, 8.0f + pz};
            }
            PSMTXTrans(m, p1.x, p1.y, p1.z);
            if (genki_blink(w->blink1)) {
                iconNumberDispGx3D(m, w->disp1, 0, (GXColor){255, 255, 255, 255});
            }
            BtlUnit_GetHomePos(mario, &mx, &my, &mz);
            BtlUnit_GetHomePos(party, &px, &py, &pz);
            mx = 0.5f * (mx + px);
            my += 90.0f;
            rec = w->rec2->userdata;
            rec->position.x = mx;
            rec->position.y = my - 10.0f;
            rec->position.z = 5.0f + mz;
            if (w->disp2 >= 10.0f) {
                p = (Vec){6.0f + mx, my, 8.0f + mz};
            } else {
                p = (Vec){mx, my, 8.0f + mz};
            }
            PSMTXTrans(m, p.x, p.y, p.z);
            if (genki_blink(w->blink2)) {
                iconNumberDispGx3D(m, w->disp2, 0, (GXColor){255, 255, 255, 255});
            }
        } else {
            BtlUnit_GetHomePos(mario, &mx, &my, &mz);
            my += 90.0f;
            rec = w->rec2->userdata;
            rec->position.x = mx;
            rec->position.y = my - 10.0f;
            rec->position.z = 5.0f + mz;
            if (w->disp2 >= 10.0f) {
                p = (Vec){6.0f + mx, my, 8.0f + mz};
            } else {
                p = (Vec){mx, my, 8.0f + mz};
            }
            PSMTXTrans(m, p.x, p.y, p.z);
            if (genki_blink(w->blink2)) {
                iconNumberDispGx3D(m, w->disp2, 0, (GXColor){255, 255, 255, 255});
            }
        }
    }

    for (i = 0; i < 10; i++) {
        o = &w->object[i];
        if (o->state == 2) {
            flags = 0;
            s = 1.25f;
            switch (o->kind) {
                case 0:
                case 1:
                    icon = ICON_1A3;
                    if (o->kind == 1) {
                        s = 2.0f;
                        if (genki_blink(o->timer)) {
                            flags |= ICON_FLAG_GRAYSCALE;
                        }
                    }
                    break;
                case 2:
                case 3:
                    switch (party->currentKind) {
                        case 0xE0:
                            icon = ICON_1A4;
                            break;
                        case 0xE1:
                            icon = ICON_1A5;
                            break;
                        case 0xE3:
                            icon = ICON_1AE;
                            break;
                        case 0xE2:
                            switch (pouchGetPartyColor(4)) {
                                case 1:
                                    icon = ICON_1A8;
                                    break;
                                case 2:
                                    icon = ICON_1A9;
                                    break;
                                case 3:
                                    icon = ICON_1AA;
                                    break;
                                case 4:
                                    icon = ICON_1AB;
                                    break;
                                case 5:
                                    icon = ICON_1AC;
                                    break;
                                case 6:
                                    icon = ICON_1AD;
                                    break;
                                case 0:
                                    icon = ICON_1A7;
                                    break;
                            }
                            break;
                        case 0xE4:
                            icon = ICON_1AF;
                            break;
                        case 0xE5:
                            icon = ICON_1A6;
                            break;
                        case 0xE6:
                            icon = ICON_1B0;
                            break;
                        default:
                            icon = 0;
                            break;
                    }
                    if (o->kind == 3) {
                        s = 2.0f;
                        if (genki_blink(o->timer)) {
                            flags |= ICON_FLAG_GRAYSCALE;
                        }
                    }
                    break;
                case 4:
                case 5:
                    icon = ICON_1B1;
                    if (o->kind == 5) {
                        s = 2.0f;
                        if (genki_blink(o->timer)) {
                            flags |= ICON_FLAG_GRAYSCALE;
                        }
                    }
                    break;
                case 6:
                    icon = ICON_143;
                    break;
            }
            PSMTXScale(m, s, s, 1.0f);
            PSMTXTransApply(m, m, o->pos.x, o->pos.y - 20.0f * s, o->pos.z);
            ((IconDispGxColU16S32Fn)iconDispGxCol)(m, flags, icon, (GXColor){255, 255, 255, 255});
        }
    }

    if (w->targetState >= 2 && w->targetState <= 3) {
        PSMTXScale(m2, 0.5f, 0.5f, 0.5f);
        BtlUnit_GetPos(mario, &mx, &my, &mz);
        mx = 85.0f * (f32)cos(ang) + mx;
        my = 85.0f * (f32)sin(ang) + my;
        mx += 10.0f;
        my += 30.0f;
        mz += 10.0f;
        btlDispTex4(BTL_TEX(0x41), (Vec){mx, my, mz}, (Vec){0.5f, 0.5f, 1.0f}, (Vec){0.0f, 0.0f, 6.0f * w->targetAngle},
                    (GXColor){255, 255, 255, 255});
        btlDispTex4(BTL_TEX(0x42), (Vec){mx, my, mz}, (Vec){0.5f, 0.5f, 1.0f}, (Vec){0.0f, 0.0f, 6.0f * -(f32)w->targetAngle},
                    (GXColor){255, 255, 255, 255});
    }
}

static void disp_3D_alpha(CameraId cam, void* param) {
}

static USER_FUNC(start_game);

static GenkiWork* get_ptr(void);
EVT_BEGIN(genki_evt_common)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_PARTNER, LW(13))
    CALL(btlevtcmd_GetBodyId, LW(13), LW(14))
    CALL(btlevtcmd_CheckStatus, LW(13), 27, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(13), -1)
    END_IF
    CALL(btlevtcmd_reset_move_color_lv_all)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    BEGIN_SIBLING_EVENT
        CALL(main_genki, LW(13), LW(15))
    END_SIBLING_EVENT
    CALL_CHILD(sac_start_camera_evt)
    WAIT_MS(500)
    CALL(sac_enemy_slide_go)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_START1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL_CHILD(sac_mario_item_on_evt)
    WAIT_MS(500)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_START2"), EVT_NULLPTR, 0, LW(11))
    IF_INT_EQUAL(LW(15), 0)
        CALL(star_appear)
    ELSE
        CALL(star_stone_appear)
    END_IF
    BEGIN_SIBLING_EVENT
        CALL_CHILD(sac_start_stardust)
    END_SIBLING_EVENT
    WAIT_FRAMES(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_HEART_SHOOT1"), EVT_NULLPTR, 0, LW(10))
    CALL(evt_snd_sfxoff, LW(11))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(40)
    CALL_CHILD(sac_mario_item_on_end_evt)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -75, LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_I_Y"))
    WAIT_FRAMES(40)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(sac_ac_help_on)
    CALL(start_game)
    CALL(wait_game_end)
    CALL(sac_ac_help_off)
    CALL(get_score, LW(10), LW(11), LW(12))
    WAIT_FRAMES(70)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
#if VERSION <= VERSION_JP
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
#else
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
#endif
    CALL(status_on)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoomSpeedLv, 0, 2)
    SET_VALUE(LW(15), LW(10))
    ADD(LW(15), LW(11))
    ADD(LW(15), LW(12))
    IF_INT_GREATER_OR_EQUAL(LW(15), 1)
        CALL(sac_wao)
    END_IF
    IF_INT_NOT_EQUAL(LW(13), -1)
        CALL(evt_snd_sfxon, STRING("SFX_HP_RECOVER_SHINE2"), 0)
        SET_VALUE(LW(9), -2)
        CALL_CHILD(status_recover_evt)
        CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, LW(10))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("stardust"), 2, LW(0), LW(1), LW(2), 50, 50, 50, 100, 0, 0, 0, 0)
        SET_VALUE(LW(9), LW(13))
        CALL_CHILD(status_recover_evt)
        CALL(btlevtcmd_StartWaitEvent, LW(13))
        CALL(btlevtcmd_RecoverHp, LW(13), LW(14), LW(11))
        CALL(btlevtcmd_GetPos, LW(13), LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("stardust"), 2, LW(0), LW(1), LW(2), 50, 50, 50, 100, 0, 0, 0, 0)
        CALL(btlevtcmd_RecoverFp, BTL_UNIT_SELF, 1, LW(12))
    ELSE
        CALL(evt_snd_sfxon, STRING("SFX_HP_RECOVER_SHINE2"), 0)
        SET_VALUE(LW(9), -2)
        CALL_CHILD(status_recover_evt)
        CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, LW(10))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("stardust"), 2, LW(0), LW(1), LW(2), 50, 50, 50, 100, 0, 0, 0, 0)
        CALL(btlevtcmd_RecoverFp, BTL_UNIT_SELF, 1, LW(12))
    END_IF
    WAIT_MS(1000)
    CALL(sac_enemy_slide_return)
    WAIT_MS(1000)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    CALL(end_genki)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

// After genki_evt_common, where the demo's .data places them (retail keeps them in .sdata).
EVT_BEGIN(marioAttackEvent_Genki0)
    SET_VALUE(LW(15), 0)
    CALL_CHILD(genki_evt_common)
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_Genki1)
    SET_VALUE(LW(15), 1)
    CALL_CHILD(genki_evt_common)
    RETURN
EVT_END()

EVT_BEGIN(status_recover_evt)
    CALL(btlevtcmd_CheckStatus, LW(9), 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 1, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 2, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 3, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 3, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 4, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 5, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 5, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 8, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 8, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 9, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 13, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 13, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 11, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 11, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 15, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 15, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(9), 20, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnOffStatus, LW(9), 20, 0, 0, 0)
    END_IF
    CALL(recover_cmd_disable)
    RETURN
EVT_END()

// inlining off for get_ptr, as in the original (the object differs without it)
#pragma dont_inline on
static GenkiWork* get_ptr(void) {
    return (GenkiWork*)_battleWorkPointer->actionCommands.work;
}
#pragma dont_inline reset

static void weapon_entry(void) {
    GenkiWork* w = get_ptr();
    s32 cnt = 0;
    s32 idx[7];
    s32 i;
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(mario, BtlUnit_GetBodyPartsId(mario));
    for (i = 0; i < w->weaponNum; i++) {
        if (w->weapon[i].state == 0) {
            idx[cnt] = i;
            cnt++;
        }
    }
    if (cnt >= 1) {
        i = idx[irand(cnt)];
        {
            GenkiWeapon* wp = &w->weapon[i];
            wp->state = 1;
            wp->timer = 7;
        }
        BtlUnit_SetAnim(part, "M_C_2C");
    }
}

// Starts the first idle object. main_genki calls it directly, not from a script, so it is called through a
// cast; it returns nothing (r3 still holds the work pointer), which main_genki ignores.
static USER_FUNC(object_entry) {
    GenkiWork* w = get_ptr();
    s32 i;
    for (i = 0; i < 10; i++) {
        s32* p = &w->object[i].state;
        if (*p == 0) {
            *p = 1;
            break;
        }
    }
}

// Counts the objects in state 2 (called directly by main_genki through a cast).
static USER_FUNC(object_get_num) {
    GenkiWork* w = get_ptr();
    s32 i;
    s32 n;
    for (i = 0, n = 0; i < 10; i++) {
        if (w->object[i].state == 2) {
            n++;
        }
    }
    return n;
}

static USER_FUNC(start_game) {
    GenkiWork* w = get_ptr();
    w->state = 1;
    return 2;
}

static USER_FUNC(wait_game_end) {
    return get_ptr()->state == 3 ? 2 : 0;
}

static USER_FUNC(get_score) {
    GenkiWork* w = get_ptr();
    EvtWord* args = event->args;
    evtSetValue(event, args[0], w->score0);
    evtSetValue(event, args[1], w->score1);
    evtSetValue(event, args[2], w->score2);
    return 2;
}

static USER_FUNC(status_on) {
    statusWinOpen();
    return 2;
}

static USER_FUNC(star_appear) {
    GenkiWork* w = get_ptr();
    s32 i;
    for (i = 0; i < 7; i++) {
        GenkiStar* s = &w->star[i];
        s->state = 1;
        s->isStone = 0;
    }
    return 2;
}

static USER_FUNC(star_stone_appear) {
    GenkiWork* w = get_ptr();
    w->star[0].state = 1;
    w->star[0].isStone = 1;
    return 2;
}

static USER_FUNC(recover_cmd_disable) {
    BattleWork* w = _battleWorkPointer;
    w->commandDisabled[0] = 0;
    w->commandDisabled[1] = 0;
    w->commandDisabled[2] = 0;
#if VERSION >= VERSION_US
    {
        BattleUnit* party = BattleGetPartyPtr(w);
        if (party != NULL) {
            party->usCommandDisabled[0] = 0;
            party->usCommandDisabled[1] = 0;
        }
    }
#else
    w->commandDisabled[3] = 0;
    w->commandDisabled[4] = 0;
#endif
    return 2;
}
