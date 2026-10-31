// rsh_05 (列車, Excess Express): car where Smorg (moamoa) is first met and flees; conductor, waitress and ghost NPCs, a
// ghost diary and the Power Punch badge; doors to rsh_04 and rsh_06.
#include "version.h"
// The unit's inlining budget: a larger or the default limit changes which of the moamoa helpers are inlined
// (checked by removing it; eki_00 and rsh_06 use their own limits).
#pragma inline_max_total_size(11500)
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "string.h"
#include "memory.h"
#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "mario/mariost.h"
#include "driver/mapdrv.h"
#include "manager/evtmgr.h"
#include "driver/hitdrv.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/offscreendrv.h"
#include "system.h"
#define _MATH_H_
#define fabs(x) __fabs(x)
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "party.h"
#include "party/party_cloud.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_npc.h"
#include "data_tables.h"
#include "driver/extdrv.h"
#include "map/moamoa.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_ext.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "party/party_nokonoko.h"
#include "rsh.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "libc_decls.h"
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)

static MoamoaWork* wp;
static f32 randf(f32 min, f32 max);
static void moamoa_pose_init(void);
static void moamoa_pose_main(void);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
/**
 * Polynomial approximation of sin(x) for an angle in radians in [0, 2*pi);
 * the Smorg (moamoa) swarm code uses its own sine to keep results identical on every frame without calling the
 * libm. Inlined into the swarm code.
 */
static inline f32 moa_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * y;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    return a;
}
/**
 * Polynomial approximation of cos(x) for an angle in radians in [0, 2*pi), companion of moa_sin.
 * Inlined into the swarm code.
 */
static inline f32 moa_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}
/**
 * Variant of moa_sin that reduces its argument in place instead of using a second local;
 * same polynomial sine for an angle in radians in [0, 2*pi).
 */
static inline f32 moa_sinx(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        } else {
            x = 1.5707964f - (x - 1.5707964f);
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        }
    } else if (x < 4.712389f) {
        x = x - 3.1415927f;
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * x;
        a = -a;
    } else {
        x = 1.5707964f - (x - 4.712389f);
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * x;
        a = -a;
    }
    return a;
}
/**
 * Variant of moa_cos that reduces its argument in place;
 * same polynomial cosine for an angle in radians in [0, 2*pi).
 */
static inline f32 moa_cosx(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        } else {
            x = 1.5707964f - (x - 1.5707964f);
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    } else if (x < 4.712389f) {
        x = x - 3.1415927f;
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    } else {
        x = 1.5707964f - (x - 4.712389f);
        x2 = x * x;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}
static void ext_moamoa_main(void);
static s32 moamoa_hit_check(ExtdrvPose* pose, Moamoa* moa);
static void moamoa_jump(ExtdrvPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);

static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
static void ext_moamoa_dispent(void);
static void ext_moamoa_init(void);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);

static MoamoaData ext_moamoa_data[47];
extern EvtWord evt_moamoa_help[];
extern EvtWord evt_moamoa_escape0[];
extern EvtWord evt_moamoa_escape1[];
#if VERSION <= VERSION_DEMO_US
static EvtWord evt_moamoa_escape[205];
#else
static EvtWord evt_moamoa_escape[228];
#endif
static EvtWord talk_syashou[19];
static EvtWord talk_waitless[19];
static BeroEntry bero_data_a[3];
static BeroEntry bero_data_b[3];
static BeroEntry bero_data_c[3];
static NpcSetupInfo npc_data[3];
extern EvtWord evt_ghost_diary[];
extern EvtWord evt_ghost_diary_read[];
/* shelf access table: hit, msg; a NULL hit ends it */
typedef struct ShelfMsg {
    const char* hit;
    const char* msg;
} ShelfMsg;
typedef struct ShelfMsgTbl6 {
    ShelfMsg rows[6];
    const char* end[1];
} ShelfMsgTbl6;
static ShelfMsgTbl6 access_tbl;
extern EvtWord rsh_05_init_evt[];
extern EvtWord rsh_05_init_evt_nidome[];

/**
 * Animation table of the swarm of small Smorgs (c_n_moa_a): the figure, its animation set and a start offset
 * for each.
 */
static MoamoaData ext_moamoa_data[] = {
    {("c_n_moa_a"), ("S_1"), 0.0f},
    {("c_n_moa_a"), ("S_1"), 2.0f},
    {("c_n_moa_a"), ("S_1"), 4.0f},
    {("c_n_moa_a"), ("S_1"), 6.0f},
    {("c_n_moa_a"), ("S_1"), 8.0f},
    {("c_n_moa_a"), ("S_1"), 10.0f},
    {("c_n_moa_a"), ("S_1"), 12.0f},
    {("c_n_moa_a"), ("S_1"), 14.0f},
    {("c_n_moa_a"), ("S_1"), 16.0f},
    {("c_n_moa_a"), ("S_1"), 18.0f},
    {("c_n_moa_a"), ("S_1"), 20.0f},
    {("c_n_moa_a"), ("S_1"), 22.0f},
    {("c_n_moa_a"), ("S_1"), 24.0f},
    {("c_n_moa_a"), ("S_1"), 26.0f},
    {("c_n_moa_a"), ("S_1"), 28.0f},
    {("c_n_moa_a"), ("S_1"), 30.0f},
    {("c_n_moa_a"), ("S_1"), 32.0f},
    {("c_n_moa_a"), ("S_1"), 34.0f},
    {("c_n_moa_a"), ("S_1"), 36.0f},
    {("c_n_moa_a"), ("S_1"), 38.0f},
    {("c_n_moa_a"), ("D_1"), 0.0f},
    {("c_n_moa_a"), ("D_1"), 4.0f},
    {("c_n_moa_a"), ("D_1"), 8.0f},
    {("c_n_moa_b"), ("S_1"), 0.0f},
    {("c_n_moa_b"), ("S_1"), 2.0f},
    {("c_n_moa_b"), ("S_1"), 4.0f},
    {("c_n_moa_b"), ("S_1"), 6.0f},
    {("c_n_moa_b"), ("S_1"), 8.0f},
    {("c_n_moa_b"), ("S_1"), 10.0f},
    {("c_n_moa_b"), ("S_1"), 12.0f},
    {("c_n_moa_b"), ("S_1"), 14.0f},
    {("c_n_moa_b"), ("S_1"), 16.0f},
    {("c_n_moa_b"), ("S_1"), 18.0f},
    {("c_n_moa_b"), ("S_1"), 20.0f},
    {("c_n_moa_b"), ("S_1"), 22.0f},
    {("c_n_moa_b"), ("S_1"), 24.0f},
    {("c_n_moa_b"), ("S_1"), 26.0f},
    {("c_n_moa_b"), ("S_1"), 28.0f},
    {("c_n_moa_b"), ("S_1"), 30.0f},
    {("c_n_moa_b"), ("S_1"), 32.0f},
    {("c_n_moa_b"), ("S_1"), 34.0f},
    {("c_n_moa_b"), ("S_1"), 36.0f},
    {("c_n_moa_b"), ("S_1"), 38.0f},
    {("c_n_moa_b"), ("D_1"), 0.0f},
    {("c_n_moa_b"), ("D_1"), 4.0f},
    {("c_n_moa_b"), ("D_1"), 8.0f},
    {0},
};

// FAKE: dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
/**
 * Builds the swarm's animation table (wp->defs) from ext_moamoa_data:
 * consecutive rows with the same model and animation name become one MoamoaPoseDef (first texture frame,
 * frame count, speed, and looping unless the animation name starts with J).
 * Kept out of line to match the original.
 */
static void moamoa_pose_init(void) {
    MoamoaData* data = ext_moamoa_data;
    s32 i = 0;
    s32 start;
    char model[32];
    char anim[32];

    strcpy(model, "");
    strcpy(anim, "");
    wp->numDefs = -1;
    do {
        if (strcmp(data->model, model)) {
            strcpy(model, data->model);
            strcpy(anim, "");
        }
        if (strcmp(data->anim, anim)) {
            strcpy(anim, data->anim);
            start = i;
            wp->numDefs++;
        }
        strcpy(wp->defs[wp->numDefs].model, model);
        strcpy(wp->defs[wp->numDefs].anim, anim);
        wp->defs[wp->numDefs].start = start;
        wp->defs[wp->numDefs].count = i - start + 1;
        wp->defs[wp->numDefs].speed = data->speed;
        wp->defs[wp->numDefs].loop = 1;
        if (!strncmp(anim, "J", 1)) {
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}

/**
 * Per-frame update of every Moamoa sprite's animation:
 * turns the time since its pose started into a texture frame index in the sprite's ExtdrvPose.
 */
static void moamoa_pose_main(void) {
    f32 t;
    u64 now;
    s32 i;
    ExtdrvPose* pose;
    Moamoa* moa;
    MoamoaPoseDef* def;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = 60.0f * OSTicksToMilliseconds(now - moa->startTime) / 1000.0f / def->speed;

        if (t >= 1.0f) {
            moa->startTime = now;
            t = 0.0f;
        }
        pose->texId = def->start + (s32)((def->count - 1) * t);
    }
}
#pragma dont_inline reset

// The model and animation of each moamoa kind. The demo map has it as a static local of moamoa_pose_change
// (group_tbl$582); here that function also has an inlined copy, so the table stays at file scope.
static const char* group_tbl[][2] = {
    {("c_n_moa_a"), ("S_1")},
    {("c_n_moa_b"), ("S_1")},
    {("c_kinodebu"), ("G_1")},
    {("c_puku_c"), ("U_1")},
    {("c_powan"), ("O_1")},
    {("c_smoko"), ("T_2")},
    {("c_rose"), ("G_1")},
    {("c_papab"), ("G_1")},
    {("c_mamab"), ("G_1")},
    {("c_konari"), ("G_1")},
    {("c_n_moa_a"), ("S_1")},
};
static inline void /**/ moamoa_pose_change_i(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & MOAMOA_FLAG_KIND_MODEL) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = "S_2";
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & MOAMOA_FLAG_DAMAGED) {
            if (strncmp(anim, "D", 1)) {
                return;
            }
        }
        if (moa->flags & MOAMOA_FLAG_ESCAPING) {
            if (strncmp(anim, "R", 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}

// FAKE: dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
/**
 * Switches one Moamoa to the named model/animation pair (a swarm member with MOAMOA_FLAG_KIND_MODEL set uses the
 * model of its kind from group_tbl instead) and restarts its animation clock.
 * A damaged Moamoa only accepts D_ poses and an escaping one only R_ poses.
 * Out-of-line copy of moamoa_pose_change_i.
 */
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & MOAMOA_FLAG_KIND_MODEL) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = "S_2";
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & MOAMOA_FLAG_DAMAGED) {
            if (strncmp(anim, "D", 1)) {
                return;
            }
        }
        if (moa->flags & MOAMOA_FLAG_ESCAPING) {
            if (strncmp(anim, "R", 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
#pragma dont_inline reset

/**
 * Script helper: sets (args[0] nonzero) or clears the MOAMOA_WORK_* bits args[1] in the swarm's work flags,
 * e.g. to start drawing the swarm, turn its hit checks off, or draw it offscreen.
 */
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall) {
    EvtWord* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);

    if (on) {
        wp->flags |= mask;
    } else {
        wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: removes the swarm effect (extReset). */
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall) {
    extReset();
    return EVT_RETURN_DONE;
}

/** Script helper: resets the facing (ry and target ry) of every Moamoa sprite to 0. */
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtdrvPose* pose = extGetPosePtr();

    for (i = 0; i < wp->count; i++, pose++) {
        pose->ry = 0.0f;
        pose->targetRy = 0.0f;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: blocks the calling script until every Moamoa has finished leaving (MOAMOA_FLAG_GONE). */
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    Moamoa* moa;

    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (!(moa->flags & MOAMOA_FLAG_GONE)) {
            return EVT_RETURN_BLOCK;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: makes the whole swarm gather at its target and merge into one body.
 * The first call puts every Moamoa into the gather state with a staggered delay;
 * the helper then blocks until all have arrived (MOAMOA_FLAG_GATHERED) and switches them to the merged state.
 */
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtdrvPose* pose;
    Moamoa* moa;

    if (isFirstCall) {
        pose = extGetPosePtr();
        moa = wp->moa;
        for (i = 0; i < wp->count; i++, pose++, moa++) {
            (*pose->mtx)[2][2] = 1.0f;
            (*pose->mtx)[1][1] = 1.0f;
            (*pose->mtx)[0][0] = 1.0f;
            moa->next = 14;
            moa->state = 14;
            moa->timer = i < 100 ? i % 100 : i % 60 + 100;
            moa->flags |= MOAMOA_FLAG_FUSING;
        }
    }
    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (!(moa->flags & MOAMOA_FLAG_GATHERED)) {
            return EVT_RETURN_BLOCK;
        }
    }
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        pose->flags |= 4;
        moa->flags |= MOAMOA_FLAG_MERGED;
        moa->state = 61;
        moamoa_pose_change_i(moa, "c_n_moa_a", "S_1");
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] turns the per-kind model on or off (MOAMOA_FLAG_KIND_MODEL),
 * args[1] applies it to every Moamoa or only to those of kind 1; each sprite then refreshes its pose.
 * rsh_06 uses it as the Smorg merges; kinds 2-9 are passenger models (c_kinodebu, c_powan, c_rose, c_papab ...).
 * Guess: the swarm is meant to show the passengers it has swallowed.
 */
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall) {
    EvtWord* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 all = evtGetValue(event, args[1]);
    s32 i;
    Moamoa* moa;

    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (on) {
            if (!all) {
                if (moa->kind == 1) {
                    moa->flags |= MOAMOA_FLAG_KIND_MODEL;
                }
            } else {
                moa->flags |= MOAMOA_FLAG_KIND_MODEL;
            }
        } else {
            if (!all) {
                if (moa->kind != 1) {
                    moa->flags &= ~MOAMOA_FLAG_KIND_MODEL;
                }
            } else {
                moa->flags &= ~MOAMOA_FLAG_KIND_MODEL;
            }
        }
        moamoa_pose_change_i(moa, "c_n_moa_a", "S_1");
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: breaks the merged Smorg apart;
 * every Moamoa leaves the merged state and goes to the blown-away state (63).
 */
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    Moamoa* moa;

    evtGetValue(event, event->args[0]);
    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        moa->flags &= ~MOAMOA_FLAG_MERGED;
        moa->state = 63;
    }
    return EVT_RETURN_DONE;
}

/**
 * Debug leftover: instantly puts every Moamoa into the fully merged state with kind models,
 * skipping the gathering. Used by moamoa_debug.
 */
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtdrvPose* pose = extGetPosePtr();
    Moamoa* moa = wp->moa;

    for (i = 0; i < wp->count; i++, pose++, moa++) {
        pose->flags |= 4;
        moa->flags |= MOAMOA_FLAG_MERGED;
        moa->flags |= MOAMOA_FLAG_FUSING;
        moa->flags |= MOAMOA_FLAG_GATHERED;
        moa->state = 61;
        moa->flags |= MOAMOA_FLAG_KIND_MODEL;
        moamoa_pose_change_i(moa, "c_n_moa_a", "S_1");
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: retires one of the swarm's targets.
 * args[0] picks target 0 (waitress in rsh_05) or 1 (conductor);
 * its hit count is set to 100, the target is replaced by the other one
 * and the matching MOAMOA_WORK_TARGETn_OFF bit is set.
 */
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall) {
    s32 i = evtGetValue(event, event->args[0]);

    wp->target[i] = wp->target[1 - i];
    wp->targetHits[i] = 100;
    if (i == 0) {
        wp->flags |= MOAMOA_WORK_TARGET0_OFF;
    } else {
        wp->flags |= MOAMOA_WORK_TARGET1_OFF;
    }
    return EVT_RETURN_DONE;
}

/** Returns a random float between min and max using rand(). */
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

/**
 * Init callback of the Smorg swarm effect (evt_ext_entry):
 * allocates the work area, sets the swarm targets,
 * scatters the sprites at random spots on the car floor (snapped to the ground with a hit check),
 * looks up the train map object and runs 600 frames of the swarm logic so the swarm starts already spread out.
 */
static void ext_moamoa_init(void) {
    s32 i;
    ExtdrvPose* pose;
    Moamoa* moa;
    f32 hitX, hitY, hitZ, hitDist, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = npcNameToPtr("ウェイトレス")->position;
    wp->target[1] = npcNameToPtr("車掌")->position;
    wp->target[2] = (Vec){-290.0f, 65.0f, -95.0f};
    wp->count = extGetPoseNum();
    wp->moa = _mapAlloc(wp->count * sizeof(Moamoa));
    memset(wp->moa, 0, wp->count * sizeof(Moamoa));
    moamoa_pose_init();
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        moa->flags = 0;
        moa->state = 0;
        moa->timer = 0;
        moamoa_pose_change_i(moa, "c_n_moa_a", "S_1");
        pose->flags |= 3;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = randf(-290.0f, 240.0f);
        (*pose->mtx)[1][3] = 0.0f;
        (*pose->mtx)[2][3] = randf(-130.0f, 50.0f);
        hitX = hitY = hitZ = 0.0f;
        hitDist = 1000000.0f;
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &nx, &ny, &nz, (*pose->mtx)[0][3], 100.0f + (*pose->mtx)[1][3], (*pose->mtx)[2][3], 0.0f, -1.0f, 0.0f)) {
            (*pose->mtx)[1][3] = hitY;
        }
    }
    wp->mobj = mapGetMapObj("ressha");
    wp->mobjY = wp->mobj->animMtx[1][3];
    for (i = 0; i < 600; i++) {
        ext_moamoa_main();
    }
}

/**
 * Draw callback of the swarm sprites: loads the ext driver state and draws all sprites.
 * When drawn into the offscreen camera it also records the bounding box of what was drawn.
 */
static void ext_disp(CameraId camera, void* param) {
    u16 left, top, right, bottom;

    if (camera == CAMERA_OFFSCREEN2) {
        GXClearBoundingBox();
    }
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    if (camera == CAMERA_OFFSCREEN2) {
        sysWaitDrawSync();
        GXReadBoundingBox(&left, &top, &right, &bottom);
        offscreenAddBoundingBox(offscreenNameToId("offscreen"), left, top, right, bottom);
    }
}

/**
 * Draw callback of the swarm's shadows: loads the shadow matrix and TEV state
 * and draws the flat shadow of every sprite (also records the bounding box for the offscreen camera).
 */
static void ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };
    u16 left, top, right, bottom;

    if (camera == CAMERA_OFFSCREEN2) {
        GXClearBoundingBox();
    }
    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
    if (camera == CAMERA_OFFSCREEN2) {
        sysWaitDrawSync();
        GXReadBoundingBox(&left, &top, &right, &bottom);
        offscreenAddBoundingBox(offscreenNameToId("offscreen"), left, top, right, bottom);
    }
}

/**
 * Starts a hop for one Moamoa toward (x, y, z) with the given horizontal speed and gravity:
 * optionally snaps y to the ground below the target, computes the flight time and initial vertical speed,
 * turns the sprite toward the target, and sets its state to the jump state (3) with `next` as the state to
 * return to.
 */
static void moamoa_jump(ExtdrvPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;
    f32 dy;
    f32 d;
    f32 angle;

    if (checkGround) {
        hitX = hitY = hitZ = 0.0f;
        dist = 1000000.0f;
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, x, 100.0f + y, z, 0.0f, -1.0f, 0.0f)) {
            if (fabs(y - hitY) > 30.0) {
                speed -= 0.1f;
                gravity += 0.1f;
            }
            y = hitY;
        }
    }
    moa->target = (Vec){x, y, z};
    moa->speed = speed;
    moa->gravity = gravity;
    dy = moa->target.y - (*pose->mtx)[1][3];
    d = distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], moa->target.x, moa->target.z);
    angle = angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], moa->target.x, moa->target.z);
    moa->jumpTimer = d / moa->speed;
    moa->vy = dy / moa->jumpTimer + moa->gravity * moa->jumpTimer / 2;
    moa->state = 3;
    moa->next = next;
    pose->dir = 180.0f + angle;
    moa->flags |= MOAMOA_FLAG_JUMPING;
    pose->flags |= 0x10;
    pose->flags &= ~4;
}

// FAKE: built with copy propagation and lifetime analysis off: the plain build allocates registers differently (checked by
// removing them).
#pragma opt_propagation off
#pragma opt_lifetimes off
/**
 * Checks whether something hits one Moamoa.
 * Returns 0 for nothing, 1 for Mario jumping on it (Mario bounces), 2 for a hammer swing or Koops's shell,
 * 3 for Flurrie's breath and 4 for Bobbery's bomb.
 * As a side effect it also pushes Mario out when he walks into a Moamoa on the ground.
 */
static s32 moamoa_hit_check(ExtdrvPose* pose, Moamoa* moa) {
    MarioWork* mario = marioGetPtr();
    f32 range;
    f32 dist;
    f32 angle;
    f32 rad;
    Vec a, b, c, d, e, f;

    if (mario->position.y > 20.0f + (*pose->mtx)[1][3]) {
        return 0;
    }
    if ((*pose->mtx)[1][3] > mario->position.y + mario->wPlayerCollisionBox.y) {
        return 0;
    }
    if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], mario->position.x, mario->position.z) < (20.0f + mario->wPlayerCollisionBox.x) / 2.0f && mario->position.y > 10.0f + (*pose->mtx)[1][3] && (mario->flags & MARIO_FLAG_IS_FALLING) && !(mario->flags & MARIO_FLAG_IS_JUMPING) && wp->bounceCount < 2) {
#if VERSION <= VERSION_DEMO_US
        marioChgMot(5);
#else
        if (mario->currMotionId != MARIO_MOTION_ROLL && mario->currMotionId != MARIO_MOTION_YOSHI) {
            marioChgMot(5);
        }
#endif
        wp->bounceCount++;
        return 1;
    }
    if (!(mario->flags & (MARIO_FLAG_IS_JUMPING | MARIO_FLAG_IS_FALLING))) {
        wp->bounceCount = 0;
    }
    if (mario->currMotionId == MARIO_MOTION_HAMMER && wp->hammerFrames > 10) {
        rad = 6.2831855f * reviseAngle(camGetPtr(CAMERA_3D)->viewYaw + (mario->displayDirection - 90.0f)) / 360.0f;
        dist = 35.0f * moa_sinx(rad) + mario->position.x;
        if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], dist, mario->position.z - 35.0f * moa_cosx(rad)) < 35.0f) {
            return 2;
        }
    }
    if (mario->currMotionId == MARIO_MOTION_HAMMER_2 && (s32)mario->currSubMotionId == 0x14) {
        f32(*mtx)[4] = *pose->mtx;
        a = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&mario->position, &a) < 65.0f) {
            return 2;
        }
    }
    if (wp->breathDir >= 0.0f) {
        f32(*mtx)[4] = *pose->mtx;
        b = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&wp->breathPos, &b) < 30.0f) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        f32(*mtx)[4] = *pose->mtx;
        c = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < 30.0f) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == PARTY_MEMBER_BOBBERY && partyGetPtr(0)->useMotionId == 0x46) {
        f32(*mtx)[4] = *pose->mtx;
        d = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < 50.0f) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, (*pose->mtx)[1][3], mario->position.z};
    f = (Vec){(*pose->mtx)[0][3], (*pose->mtx)[1][3], (*pose->mtx)[2][3]};
    range = (20.0f + mario->wPlayerCollisionBox.x) / 2.0f;
    if (PSVECDistance(&e, &f) < range) {
        (*pose->mtx)[0][3] = moa->lastX;
        (*pose->mtx)[2][3] = moa->lastZ;
        {
            f32(*mtx)[4] = *pose->mtx;
            f = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        }
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
                mario->floorMove.x = -((range - dist) * moa_sinx(6.2831855f * mario->directionView / 360.0f));
                mario->floorMove.z = (range - dist) * moa_cosx(6.2831855f * mario->directionView / 360.0f);
            } else {
                mario->floorMove.x = (*pose->mtx)[0][3] - range * moa_sinx(6.2831855f * angle / 360.0f) - mario->position.x;
                mario->floorMove.z = (*pose->mtx)[2][3] + range * moa_cosx(6.2831855f * angle / 360.0f) - mario->position.z;
            }
        }
    }
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

// FAKE: built with copy propagation and lifetime analysis off: the plain build allocates registers differently (checked by
// removing them).
#pragma opt_propagation off
#pragma opt_lifetimes off
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
/**
 * Per-frame callback of the Smorg swarm.
 * Tracks hammer and idle time, Flurrie's breath and partner use, counts hits on the swarm's targets,
 * and runs each Moamoa's state machine (idle hopping toward its target or Mario, jumps, damage and knock-off,
 * escape, gathering and merging, being blown away).
 * When both targets have been freed it starts the swarm's escape.
 */
static void ext_moamoa_main(void) {
    MarioWork* mario;
    PartyEntry* party;
    ExtdrvPose* pose;
    Moamoa* moa;
    s32 i;
    s32 hit;
    s32 sfx;
    s32 ret;
    f32 jumpSpeed;
    f32 rad;
    f32 angle;
    f32 x;
    f32 y;
    f32 dist;
    f32 z;
    f32 spd;
    f32 grav;
    f32 tx;
    f32 tz;
    f32 ty;
    f32 a;
    f32 d;
    f32 r;
    f32 s;
    Mtx m1;
    Mtx m;
    Vec sp2_;
    Vec v;

    mario = marioGetPtr();
    party = partyGetPtr(0);
    camGetPtr(CAMERA_3D);
    hit = 0;
    if (mario->currMotionId == MARIO_MOTION_HAMMER) {
        wp->hammerFrames++;
    } else {
        wp->hammerFrames = 0;
    }
    if (mario->currMotionId == MARIO_MOTION_STAY) {
        wp->idleFrames++;
        if (wp->idleFrames > 1000) {
            wp->idleFrames = 1000;
        }
    } else {
        wp->idleFrames = 0;
    }
    if (party->flags & PARTY_FLAG_IS_BEING_USED) {
        wp->flags |= MOAMOA_WORK_PARTNER_IN_USE;
    } else {
        wp->flags &= ~MOAMOA_WORK_PARTNER_IN_USE;
    }
    wp->breathDir = -1.0f;
    wp->breathDist = -1.0f;
    if (party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        wp->breathDir = cloudGetBreathDir();
        wp->breathDist = cloudGetBreathDist();
        wp->breathPos.x = wp->breathDist * moa_sinx(6.2831855f * wp->breathDir / 360.0f) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - wp->breathDist * moa_cosx(6.2831855f * wp->breathDir / 360.0f);
    }
    if (wp->targetHits[0] > 50) {
        wp->target[0] = wp->target[1];
        if (!(wp->flags & MOAMOA_WORK_TARGET0_OFF)) {
            wp->flags |= MOAMOA_WORK_TARGET0_OFF;
            evtEntry(evt_moamoa_escape0, 0, 0);
        }
    }
    if (wp->targetHits[1] > 50) {
        wp->target[1] = wp->target[0];
        if (!(wp->flags & MOAMOA_WORK_TARGET1_OFF)) {
            wp->flags |= MOAMOA_WORK_TARGET1_OFF;
            evtEntry(evt_moamoa_escape1, 0, 0);
        }
    }
    if ((wp->flags & MOAMOA_WORK_TARGET0_OFF) && (wp->flags & MOAMOA_WORK_TARGET1_OFF)) {
        s32 j;
        Moamoa* m2;

        extGetPosePtr();
        m2 = wp->moa;
        for (j = 0; j < wp->count; j++, m2++) {
            if (m2->flags & MOAMOA_FLAG_DAMAGED) {
                continue;
            }
            if (m2->flags & MOAMOA_FLAG_ESCAPING) {
                break;
            }
            m2->state = 0x19;
            m2->timer = 0;
            m2->flags |= MOAMOA_FLAG_ESCAPING;
        }
        if (wp->escapeEvt == NULL) {
            wp->escapeEvt = evtEntry(evt_moamoa_escape, 0, 0);
        }
    }

    pose = extGetPosePtr();
    sfx = 0;
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
#if VERSION <= VERSION_DEMO_US
        if ((wp->flags & MOAMOA_WORK_ACTIVE) && !(wp->flags & MOAMOA_WORK_NO_HIT) && !hit && !(moa->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING))) {
#else
        if ((wp->flags & MOAMOA_WORK_ACTIVE) && !(wp->flags & MOAMOA_WORK_NO_HIT) && !marioKeyOffChk() && !marioCtrlOffChk() && !hit && !(moa->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING))) {
#endif
            ret = moamoa_hit_check(pose, moa);
            if (ret == 1) {
                moa->flags |= MOAMOA_FLAG_DAMAGED;
                moa->state = 0x24;
                {
                    s32 idx;
                    wp->hitCount++;
                    idx = i % 3;
                    if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[idx].x, wp->target[idx].z) < VERSION_PICK(200.0f, 80.0f)) {
                        wp->targetHits[idx]++;
                    }
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            } else if (ret == 2 || ret == 4) {
                moa->flags |= MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_KNOCKED;
                moa->state = 0x2f;
                {
                    s32 idx;
                    wp->hitCount++;
                    idx = i % 3;
                    if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[idx].x, wp->target[idx].z) < VERSION_PICK(200.0f, 80.0f)) {
                        wp->targetHits[idx]++;
                    }
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                angle = (wp->breathDir + wp->angle) / 2.0f;
                moa->flags |= MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_BLOWN;
                moa->state = 0x30;
                moa->target = moamoa_zero_vec;
                spd = randf(0.1f, 0.2f);
                rad = (6.2831855f * angle) / 360.0f;
                moa->vy = spd * moa_sinx(rad);
                moa->speed = randf(0.03f, 0.06f);
                moa->gravity = spd * (-moa_cosx(rad));
                moa->jumpTimer = 120;
                {
                    s32 idx;
                    wp->hitCount++;
                    idx = i % 3;
                    if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[idx].x, wp->target[idx].z) < VERSION_PICK(200.0f, 80.0f)) {
                        wp->targetHits[idx]++;
                    }
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            }
        }
        if ((wp->flags & MOAMOA_WORK_ACTIVE) && !(moa->flags & (MOAMOA_FLAG_TO_TARGET | MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING)) && wp->dist < 50.0f) {
            if (moa->flags & MOAMOA_FLAG_JUMPING) {
                moa->next = 1;
            } else {
                moa->state = 1;
            }
        }
        if ((wp->flags & MOAMOA_WORK_ACTIVE) && !(moa->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_MERGED)) && i == gp->retraceCount % wp->count && irand(1000) < 200) {
            /* FAKE: named Vec copied into sp2_ instead of a compound literal; integer cast hoists the literal as an @ temp (same values) */ {
                Vec tmp = {0.0f, 0.0f, 0.0f};
                tmp.x = (*pose->mtx)[0][3];
                tmp.y = (*pose->mtx)[1][3];
                tmp.z = (*pose->mtx)[2][3];
                sp2_ = tmp;
            }
            psndSFXOn_3D(SFX_NAME_WORD("SFX_STG6_MOAMOA_VOICE1"), &sp2_);
        }
        switch (moa->state) {
            case 0:
                if ((i % 133) < 100) {
                    f32 hopX;
                    f32 hopZ;
                    f32 hopY;
                    f32 ax;
                    f32 az;
                    f32 ar;
                    rad = randf(0.0f, 6.2831855f);
                    dist = randf(0.0f, 50.0f);
                    ax = wp->target[i % 3].x + (dist * moa_sinx(rad));
                    az = wp->target[i % 3].z - (dist * moa_cosx(rad));
                    ar = (6.2831855f * angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], ax, az)) / 360.0f;
                    hopX = (15.0f * moa_sinx(ar)) + (*pose->mtx)[0][3];
                    hopY = (*pose->mtx)[1][3];
                    hopZ = (*pose->mtx)[2][3] - (15.0f * moa_cosx(ar));
                    {
                        f32 k1;
                        f32 k2;
                        f32 rand1 = rand() / 32767.0f;
                        f32 rand2 = rand() / 32767.0f;
                        moamoa_jump(pose, moa, moa->state, 1, hopX, hopY, hopZ, (rand1 * (k1 = 3.0f - 1.5f)) + 1.5f, (rand2 * (k2 = 2.0f - 0.8f)) + 0.8f);
                    }
                    moa->flags |= MOAMOA_FLAG_TO_TARGET;
                    break;
                }
                {
                    f32 hopZ;
                    {
                        f32 targetDist;
                        f32 targetAngle;
                        f32 targetRad;
                        targetDist = distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                        targetAngle = angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                        if (targetDist < VERSION_PICK(200.0f, 80.0f)) {
                            targetAngle = randf(0.0f, 360.0f);
                        }
                        targetRad = (6.2831855f * targetAngle) / 360.0f;
                        rad = (5.0f * moa_sinx(targetRad)) + (*pose->mtx)[0][3];
                        y = (*pose->mtx)[1][3];
                        hopZ = (*pose->mtx)[2][3] - (5.0f * moa_cosx(targetRad));
                    }
                    {
                        f32 k1;
                        f32 k2;
                        f32 rand1 = rand() / 32767.0f;
                        f32 rand2 = rand() / 32767.0f;
                        moamoa_jump(pose, moa, moa->state, 1, rad, y, hopZ, (rand1 * (k1 = 0.5f - 0.3f)) + 0.3f, (rand2 * (k2 = 0.8f - 0.5f)) + 0.5f);
                    }
                }
                moa->flags &= ~MOAMOA_FLAG_TO_TARGET;
                break;

            case 50:
                if ((--moa->timer) < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;

            case 51:
                moa->speed = randf(0.0f, 200.0f);
                moa->gravity = randf(0.0f, (300.0f * moa->speed) / 200.0f);
                moa->state++;
                moa->timer = 0;

            case 52:
                s = (moa->timer < 200) ? (1.0f) : ((800 - moa->timer) / 600.0f);
                if (s < 0.0f) {
                    s = 0.0f;
                    moa->flags |= MOAMOA_FLAG_GATHERED;
                }
                tx = wp->target[i % 3].x;
                ty = wp->target[i % 3].y;
                tz = wp->target[i % 3].z;
                tx += s * (moa->gravity * ((f32)sin(((f32)(i + gp->retraceCount)) / 4.0f)));
                r = i + gp->retraceCount;
                ty += moa->speed * s;
                tz += s * ((-moa->gravity) * ((f32)cos(r / 4.0f)));
                (*pose->mtx)[0][3] += (tx - (*pose->mtx)[0][3]) / 15.0f;
                (*pose->mtx)[1][3] += (ty - (*pose->mtx)[1][3]) / 15.0f;
                (*pose->mtx)[2][3] += (tz - (*pose->mtx)[2][3]) / 15.0f;
                moa->timer++;
                break;

            case 1: {
                f32 hopRad;
                {
                    f32 k;
                    f32 rand1 = rand() / 32767.0f;
                    f32 hopAngle = wp->angle + ((rand1 * (k = 45.0f - -45.0f)) + -45.0f);
                    hopRad = (6.2831855f * hopAngle) / 360.0f;
                }
                d = wp->dist;
                x = (*pose->mtx)[0][3] + (15.0f * moa_sinx(hopRad));
                dist = (*pose->mtx)[1][3];
                z = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                {
                    f32 hopSpeed;
                    f32 k;
                    f32 rand1 = rand() / 32767.0f;
                    hopSpeed = rand1 * (k = 1.0f - 1.0f) + 1.0f;
                    // FAKE: block-local copies of the float args (behaviour-identical) put the f1..f5 arg moves ahead of the ?: as in the target
                    {
                        f32 g2 = randf(0.4f, 0.4f);
                        {
                            f32 x2 = x;
                            f32 y2 = dist;
                            f32 z2 = z;
                            f32 s2 = hopSpeed;
                            f32 g3 = g2;
                            moamoa_jump(pose, moa, (d < 100.0f) ? (moa->state) : (0), 1, x2, y2, z2, s2, g3);
                        }
                    }
                }
            } break;

            case 2: {
                f32 hopZ;
                f32 hopX;
                {
                    f32 turn = randf(-45.0f, 45.0f);
                    a = wp->angle;
                    a += turn;
                }
                a += 180.0f;
                d = wp->dist;
                hopX = (*pose->mtx)[0][3] + (30.0f * moa_sinx((6.2831855f * a) / 360.0f));
                y = (*pose->mtx)[1][3];
                hopZ = (*pose->mtx)[2][3];
                {
                    f32 b;
                    f32 k;
                    f32 rand1 = rand() / 32767.0f;
                    f32 rand2;
                    jumpSpeed = 2.0f * ((rand1 * (k = 1.0f - 1.0f)) + 1.0f);
                    rand2 = rand() / 32767.0f;
                    b = 2.0f * ((rand2 * (k = 0.4f - 0.4f)) + 0.4f);
                    // FAKE: block-local copies of the float args (behaviour-identical) put the f1..f5 arg moves ahead of the ?: as in the target
                    {
                        f32 x2 = hopX;
                        f32 y2 = y;
                        f32 z2 = hopZ;
                        f32 s2 = jumpSpeed;
                        f32 g2 = b;
                        moamoa_jump(pose, moa, (d < 100.0f) ? (moa->state) : (0), 1, x2, y2, z2, s2, g2);
                    }
                }
                break;
            }

            case 3:
                (*pose->mtx)[1][3] += moa->vy;
                moa->vy -= moa->gravity;
                {
                    f32 moveRad = (6.2831855f * angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], moa->target.x, moa->target.z)) / 360.0f;
                    (*pose->mtx)[0][3] += moa->speed * moa_sinx(moveRad);
                    (*pose->mtx)[2][3] = (*pose->mtx)[2][3] + (moa->speed * (-moa_cosx(moveRad)));
                }
                if ((--moa->jumpTimer) < 0) {
                    (*pose->mtx)[0][3] = moa->target.x;
                    (*pose->mtx)[1][3] = moa->target.y;
                    (*pose->mtx)[2][3] = moa->target.z;
                    moa->flags &= ~MOAMOA_FLAG_JUMPING;
                    pose->flags &= ~0x10;
                    moa->timer = 0;
                    moa->state++;
                }
                break;

            case 4:
                if ((++moa->timer) > 4) {
                    moa->state = moa->next;
                }
                break;

            case 36:

            case 37:

            case 38: {
                f32 targetZ;
                if (!(moa->flags & MOAMOA_FLAG_TO_TARGET)) {
                    tx = mario->position.x;
                    targetZ = mario->position.z;
                } else {
                    tx = wp->target[i % 3].x;
                    targetZ = wp->target[i % 3].z;
                }
                {
                    f32 hopZ;
                    {
                        f32 hopRad;
                        f32 k;
                        s = rand() / 32767.0f;
                        {
                            f32 hopAngle = angleABf(tx, targetZ, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
                            hopAngle += ((s * (k = 45.0f - -45.0f)) + -45.0f);
                            hopRad = (6.2831855f * hopAngle) / 360.0f;
                        }
                        ty = (*pose->mtx)[0][3] + (15.0f * moa_sinx(hopRad));
                        y = (*pose->mtx)[1][3];
                        hopZ = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                    }
                    {
                        f32 k;
                        f32 rand1 = rand() / 32767.0f;
                        f32 rand2 = rand() / 32767.0f;
                        k = 1.0f - 1.0f;
                        moamoa_jump(pose, moa, moa->state + 1, 1, ty, y, hopZ, (rand1 * k) + 1.0f, (rand2 * k) + 1.0f);
                    }
                }
            } break;

            case 39:
                if ((++moa->timer) < 30) {
                    (*pose->mtx)[0][0] *= 0.9f;
                    (*pose->mtx)[1][1] *= 0.9f;
                    (*pose->mtx)[2][2] *= 0.9f;
                } else {
                    moa->state = 49;
                }
                break;

            case 47: {
                f32 hopRad;
                s = rand() / 32767.0f;
                dist = randf(300.0f, 500.0f);
                {
                    f32 k;
                    hopRad = (6.2831855f * ((s * (k = 225.0f - 135.0f)) + 135.0f)) / 360.0f;
                }
                x = (dist * moa_sinx(hopRad)) + (*pose->mtx)[0][3];
                y = (*pose->mtx)[2][3] - (dist * moa_cosx(hopRad));
            }
                {
                    f32 k;
                    f32 rand1 = rand() / 32767.0f;
                    spd = (rand1 * (k = 6.0f - 5.0f)) + 5.0f;
                }
                {
                    f32 k;
                    f32 rand1 = rand() / 32767.0f;
                    s = (rand1 * (k = 0.3f - 0.2f)) + 0.2f;
                }
                if (!sfx) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = (*pose->mtx)[0][3];
                    pos.y = (*pose->mtx)[1][3];
                    pos.z = (*pose->mtx)[2][3];
                    psndSFXOn_3D((const char*)0x6c3, &pos);
                    sfx = 1;
                }
                dist = -100.0f;
                moamoa_jump(pose, moa, 49, 0, x, dist, y, spd, s);
                break;

            case 48:
                if ((--moa->jumpTimer) > 0) {
                    moa->target.x += moa->vy;
                    moa->target.y += moa->speed;
                    moa->target.z += moa->gravity;
                    (*pose->mtx)[0][3] += moa->target.x;
                    (*pose->mtx)[1][3] += moa->target.y;
                    (*pose->mtx)[2][3] += moa->target.z;
                } else {
                    moa->state = 49;
                }
                break;

            case 49:
                if ((wp->flags & MOAMOA_WORK_TARGET0_OFF) && (wp->flags & MOAMOA_WORK_TARGET1_OFF)) {
                    moa->state = 62;
                    break;
                }
                if (wp->hitCount < 500) {
                    PSMTXIdentity(*pose->mtx);
                    (*pose->mtx)[0][3] = wp->target[i % 3].x;
                    (*pose->mtx)[1][3] = wp->target[i % 3].y;
                    (*pose->mtx)[2][3] = wp->target[i % 3].z;
                    moa->flags = 0;
                    moa->state = 0;
                    moa->timer = 0;
                } else {
                    moa->state = 62;
                }
                break;

            case 25:
                if (moa->timer < 30) {
                    PSMTXRotRad(m1, 'y', 0.20943952f);
                    PSMTXConcat(*pose->mtx, m1, *pose->mtx);
                    pose->flags &= ~2;
                    moa->timer++;
                } else {
                    pose->flags |= 2;
                    moa->timer = rand() % 30;
                    moa->state++;
                }
                break;

            case 26:
                if ((--moa->timer) < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;

            case 27:
                d = distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], -275.0f, -100.0f);
                {
                    f32 hopAngle;
                    f32 k;
                    tz = rand() / 32767.0f;
                    hopAngle = angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], -275.0f, -100.0f);
                    hopAngle += ((tz * (k = 45.0f - -45.0f)) + -45.0f);
                    if (d > 6.0f && (x = (*pose->mtx)[1][3]) < 60.0f) {
                        f32 hopRad = (6.2831855f * hopAngle) / 360.0f;
                        dist = (15.0f * moa_sinx(hopRad)) + (*pose->mtx)[0][3];
                        angle = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                        {
                            f32 k1;
                            f32 k2;
                            f32 rand1 = rand() / 32767.0f;
                            f32 rand2 = rand() / 32767.0f;
                            moamoa_jump(pose, moa, moa->state, 1, dist, x, angle, 3.0f * ((rand1 * (k1 = 1.0f - 1.0f)) + 1.0f), (rand2 * (k2 = 1.0f - 1.0f)) + 1.0f);
                        }
                    } else {
                        moa->state++;
                    }
                }
                break;
            case 28:
                if ((*pose->mtx)[0][3] > -350.0f) {
                    f32 hopRad;
                    s = rand() / 32767.0f;
                    {
                        f32 k;
                        f32 hopAngle = angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], -350.0f, -100.0f);
                        hopAngle += ((s * (k = 45.0f - -45.0f)) + -45.0f);
                        hopRad = (6.2831855f * hopAngle) / 360.0f;
                    }
                    x = (15.0f * moa_sinx(hopRad)) + (*pose->mtx)[0][3];
                    y = (*pose->mtx)[1][3];
                    grav = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                    {
                        f32 k1;
                        f32 k2;
                        f32 rand1 = rand() / 32767.0f;
                        f32 rand2 = rand() / 32767.0f;
                        moamoa_jump(pose, moa, moa->state, 1, x, y, grav, 3.0f * ((rand1 * (k1 = 1.0f - 1.0f)) + 1.0f), (rand2 * (k2 = 1.0f - 1.0f)) + 1.0f);
                    }
                } else {
                    moa->state = 0x3e;
                }
                break;
            case 62:
                moa->flags |= MOAMOA_FLAG_GONE;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;

            case 63: {
                f32 k;
                s = rand() / 32767.0f;
                spd = randf(2.0f, 3.0f);
                moa->timer = irand(i / 2);
                rad = (6.2831855f * ((s * (k = 315.0f - 225.0f)) + 225.0f)) / 360.0f;
            }
                moa->target.x = spd * moa_sinx(rad);
                moa->target.y = randf(1.0f, 2.0f);
                moa->target.z = spd * (-moa_cosx(rad));
                moa->state++;
                break;

            case 64:
                if ((--moa->timer) < 0) {
                    moa->state++;
                }
                break;

            case 65:
                moa->target.x *= 1.1f;
                moa->target.y *= 1.02f;
                moa->target.z *= 1.1f;
                (*pose->mtx)[0][3] += moa->target.x;
                (*pose->mtx)[1][3] += moa->target.y;
                (*pose->mtx)[2][3] += moa->target.z;
                PSMTXRotRad(m, 'y', 0.20943952f);
                PSMTXConcat(*pose->mtx, m, *pose->mtx);
                pose->flags &= ~2;
                if ((*pose->mtx)[0][3] < (-1000.0f)) {
                    moa->state = 62;
                }
                break;
        }

        if (!(moa->flags & (MOAMOA_FLAG_KNOCKED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_BLOWN))) {
            if ((*pose->mtx)[0][3] > 290.0f) {
                (*pose->mtx)[0][3] = 290.0f;
            }
            if ((*pose->mtx)[0][3] < -290.0f) {
                (*pose->mtx)[0][3] = -290.0f;
            }
            if ((*pose->mtx)[2][3] > 50.0f) {
                (*pose->mtx)[2][3] = 50.0f;
            }
            if ((*pose->mtx)[2][3] < -130.0f) {
                (*pose->mtx)[2][3] = -130.0f;
            }
        }
        (*pose->mtx)[1][3] += wp->mobj->modelWorldMtx[1][3] - wp->mobjY;
        moa->lastX = (*pose->mtx)[0][3];
        moa->lastZ = (*pose->mtx)[2][3];
    }
    moamoa_pose_main();
    wp->mobjY = wp->mobj->modelWorldMtx[1][3];
#if VERSION <= VERSION_DEMO_US
    v = (Vec){mario->floorMove.x, mario->floorMove.y, mario->floorMove.z};
    { static const Vec zv2 = {0.0f, 0.0f, 0.0f}; } // FAKE: unreferenced 12-byte .rodata pad object, defined after the compound literal's template so the template comes first (target order)
    if (PSVECMag(&v) > 2.0f) {
        PSVECNormalize(&v, &v);
        mario->floorMove.x = 2.0f * v.x;
        mario->floorMove.y = 2.0f * v.y;
        mario->floorMove.z = 2.0f * v.z;
    }
#else
    if (wp->flags & MOAMOA_WORK_PARTNER_IN_USE) {
        mario->floorMove.x = 0.0f;
        mario->floorMove.y = 0.0f;
        mario->floorMove.z = 0.0f;
    } else {
        v = (Vec){mario->floorMove.x, mario->floorMove.y, mario->floorMove.z};
        { static const Vec zv2 = {0.0f, 0.0f, 0.0f}; } // FAKE: unreferenced 12-byte .rodata pad object, defined after the compound literal's template so the template comes first (target order)
        if (PSVECMag(&v) > 2.0f) {
            PSVECNormalize(&v, &v);
            mario->floorMove.x = 2.0f * v.x;
            mario->floorMove.y = 2.0f * v.y;
            mario->floorMove.z = 2.0f * v.z;
        }
    }
#endif
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

/**
 * Registers the swarm's draw callbacks each frame (sprites and shadows on the 3D camera and, if enabled,
 * on the offscreen camera).
 */
static void ext_moamoa_dispent(void) {
    if (wp->flags & MOAMOA_WORK_ACTIVE) {
        dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, 0.0f, 2, ext_shadow_disp, NULL);
    }
    if (wp->flags & MOAMOA_WORK_DRAW_OFFSCREEN) {
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 2, ext_shadow_disp, NULL);
    }
}

// FAKE: built with copy propagation and lifetime analysis off: the plain build allocates registers differently (checked by
// removing them).
#pragma opt_propagation off
#pragma opt_lifetimes off
/**
 * Script helper: moves the named NPC in a hop to (x, y, z).
 * Args: name, x, y, z, horizontal speed, gravity, duration in milliseconds. Blocks until the NPC lands.
 */
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    f32 gravity = evtGetFloat(event, args[5]);
    s32 frames = evtGetValue(event, args[6]);
    f32 t = 60.0f * frames / 1000.0f;
    NpcEntry* npc = npcNameToPtr(name);
    f32 dy;
    f32 vy;
    f32 dist;
    f32 angle;

    if (isFirstCall) {
        static const Vec va = {0.0f, 0.0f, 0.0f};
        static const Vec vb = {0.0f, 0.0f, 0.0f};
        Vec a;
        Vec b;

        b = vb;
        b.x = npc->position.x;
        b.z = npc->position.z;
        a = va;
        a.x = x;
        a.z = z;
        dist = PSVECDistance(&a, &b);
        dy = y - npc->position.y;
        if (t == 0.0f) {
            t = dist / speed;
        } else {
            speed = dist / t;
        }
        vy = dy / t + gravity * t / 2.0f;
        // The floats are stored as their bit patterns through the word view (a float store gives different code).
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = 6.2831855f * angleABf(npc->position.x, npc->position.z, x, z) / 360.0f;
    npc->position.x = speed * moa_sinx(angle) + npc->position.x;
    npc->position.z = npc->position.z - speed * moa_cosx(angle);
    npc->position.y += vy;
    vy -= gravity;
    t -= 1.0f;
    if (t < 0.0f) {
        npc->position = (Vec){x, y, z};
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

/**
 * Starts the Smorg swarm in the baggage car: registers the two Smorg NPC models,
 * adds the swarm effect for 400 sprites, turns the swarm on, and,
 * if the waitress or conductor was already freed (GSWF_RSH05_SMORG_RELEASED_*),
 * retires that target and restores their talk script.
 */
static EVT_BEGIN(evt_moamoa_init)
    CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
    CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
    CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
    CALL(evt_ext_entry, 400, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    IF_INT_EQUAL(GSWF(GSWF_RSH05_SMORG_RELEASED_WAITRESS), 1)
        CALL(evt_moamoa_target_off, 0)
        CALL(evt_npc_change_interrupt, STRING("ウェイトレス"), 6, PTR(talk_waitless))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH05_SMORG_RELEASED_CONDUCTOR), 1)
        CALL(evt_moamoa_target_off, 1)
        CALL(evt_npc_change_interrupt, STRING("車掌"), 6, PTR(talk_syashou))
    END_IF
    RETURN
EVT_END()

/**
 * Cutscene when Mario first enters the baggage car with the Smorgs (STORY_STG6_46_ENGINEER):
 * the waitress and conductor are being held in the swarm, Mario is startled,
 * and messages play with the partner's reaction (stg6_rsh_237, 238_x).
 */
static EVT_BEGIN(evt_meet_moamoa)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1500)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("G_1"))
    CALL(evt_npc_set_anim, STRING("車掌"), STRING("G_1"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("eff0"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING("eff1"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_237"), 0, 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_zoom_in, 25, 1500, 0, 11)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set_at, -200, 60, -80, 0, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(2000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_moamoa_ry_reset)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_0"), 0, STRING("party"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_1"), 0, STRING("party"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_2"), 0, STRING("party"))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_3"), 0, STRING("party"))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_4"), 0, STRING("party"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_5"), 0, STRING("party"))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_238_6"), 0, STRING("party"))
    END_SWITCH
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_47_00_BAGGAGE_CAR_SMORGS)
    RETURN
EVT_END()

/**
 * Script run for a freed NPC (name in LW(0): the waitress or the conductor):
 * the NPC thanks Mario (stg6_rsh_249_00 / 249_01),
 * then hops away from the swarm in three shrinking jumps (400, 200 and 100 ms) in a random direction,
 * and ends in a relieved pose.
 */
EVT_BEGIN(evt_moamoa_help)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_TALK_ANIM)
        IF_STR_EQUAL(LW(0), STRING("車掌"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_249_00"), 0, LW(0))
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_249_01"), 0, LW(0))
        END_IF
        CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_TALK_ANIM)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_MOVE_ANIM)
    SET_VALUE(LW(10), LW(0))
    CALL(evt_npc_get_position, LW(0), LW(1), LW(2), LW(3))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_sub_random, 180, LW(4))
    ADD(LW(4), 90)
#else
    CALL(evt_sub_random, 1000, LW(4))
    IF_INT_LESS(LW(4), 500)
        SET_VALUE(LW(4), 90)
    ELSE
        SET_VALUE(LW(4), 270)
    END_IF
#endif
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(30.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(30.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.5f), 400)
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(20.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(20.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.2998047f), 200)
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(10.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(10.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.19921875f), 100)
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INTANGIBLE)
    IF_STR_EQUAL(LW(10), STRING("車掌"))
        CALL(evt_npc_set_anim, LW(10), STRING("O_1"))
    ELSE
        CALL(evt_npc_set_anim, LW(10), STRING("P_1"))
    END_IF
    RETURN
EVT_END()

/**
 * Runs when the swarm gives up its first target:
 * frees the waitress (evt_moamoa_help) and gives her talk_waitless as her talk event.
 */
EVT_BEGIN(evt_moamoa_escape0)
    SET_VALUE(LW(0), STRING("ウェイトレス"))
    SPAWN_EVENT(evt_moamoa_help)
    SET_VALUE(GSWF(GSWF_RSH05_SMORG_RELEASED_WAITRESS), 1)
    CALL(evt_npc_change_interrupt, STRING("ウェイトレス"), 6, PTR(talk_waitless))
    RETURN
EVT_END()

/**
 * Runs when the swarm gives up its second target:
 * frees the conductor (evt_moamoa_help), sets GSWF_RSH05_SMORG_RELEASED_CONDUCTOR
 * and gives him talk_syashou as his talk event.
 */
EVT_BEGIN(evt_moamoa_escape1)
    SET_VALUE(LW(0), STRING("車掌"))
    SPAWN_EVENT(evt_moamoa_help)
    SET_VALUE(GSWF(GSWF_RSH05_SMORG_RELEASED_CONDUCTOR), 1)
    CALL(evt_npc_change_interrupt, STRING("車掌"), 6, PTR(talk_syashou))
    RETURN
EVT_END()

/**
 * Cutscene after both captives are freed: the swarm flees, the camera pulls back,
 * the conductor and waitress thank Mario (stg6_rsh_240_00, 241, 240_01),
 * the story advances to STORY_STG6_47_ESCAPING_THE_SMORGS and the west door opens.
 */
static EVT_BEGIN(evt_moamoa_escape)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set_xyz, -200, 0, 0, 0, 3000, 11)
    WAIT_MS(3000)
    CALL(evt_moamoa_end_wait)
    CALL(evt_moamoa_exit)
    CALL(evt_cam3d_evt_xyz_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    // The demo turns each NPC's intangible flag on and off inside its own walk; the releases set both before the walks.
#if VERSION <= VERSION_DEMO_US
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_status_onoff, 1, STRING("車掌"), 2)
        CALL(evt_npc_move_position, STRING("車掌"), -80, 22, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING("車掌"), 90)
        CALL(evt_npc_flag_onoff, 0, STRING("車掌"), NPC_FLAG_INTANGIBLE)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("ウェイトレス"), NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_status_onoff, 1, STRING("ウェイトレス"), 2)
        CALL(evt_npc_move_position, STRING("ウェイトレス"), 0, 15, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING("ウェイトレス"), 270)
        CALL(evt_npc_flag_onoff, 0, STRING("ウェイトレス"), NPC_FLAG_INTANGIBLE)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -20, -10, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
#else
    CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("ウェイトレス"), NPC_FLAG_INTANGIBLE)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING("車掌"), 2)
        CALL(evt_npc_move_position, STRING("車掌"), -80, 22, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING("車掌"), 90)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING("ウェイトレス"), 2)
        CALL(evt_npc_move_position, STRING("ウェイトレス"), 0, 15, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING("ウェイトレス"), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -20, -10, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
#endif
#if VERSION >= VERSION_JP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(2), -140)
        CALL(evt_mario_mov_pos2, LW(0), -100, FLOAT(80.0f))
    END_IF
    CALL(evt_mario_flag_onoff, 1, 1024)
#endif
    CALL(evt_mario_mov_pos2, -45, 5, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
#if VERSION >= VERSION_JP
    CALL(evt_mario_flag_onoff, 0, 1024)
#endif
    CALL(evt_cam3d_evt_set, -40, 90, 283, -40, 38, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_240_00"), 0, STRING("車掌"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg6_rsh_241"), 0, STRING("ウェイトレス"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg6_rsh_240_01"), 0, STRING("車掌"))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
#if VERSION >= VERSION_JP
    CALL(evt_npc_flag_onoff, 0, STRING("車掌"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("ウェイトレス"), NPC_FLAG_INTANGIBLE)
#endif
    CALL(evt_npc_change_interrupt, STRING("車掌"), 6, PTR(talk_syashou))
    CALL(evt_npc_change_interrupt, STRING("ウェイトレス"), 6, PTR(talk_waitless))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_47_ESCAPING_THE_SMORGS)
    SET_VALUE(LW(0), STRING("w_bero"))
    CALL_CHILD(bero_case_switch_on)
    RETURN
EVT_END()

/**
 * Init event of the conductor (車掌) in the baggage car: from STORY_STG6_46_ENGINEER to STORY_STG6_48_SMORG_MIASMA
 * he stands at (-115, 0, 20) ((-100, 0, 0) in the demos) with the O_1 / T_3 poses and the distressed tribe
 * 車掌悲, begging Mario to help the waitress the Smorgs have caught; at other times he is off the map.
 */
static EVT_BEGIN(init_syashou)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_48_SMORG_MIASMA)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_npc_set_position, STRING("me"), -100, 0, 0)
#else
        CALL(evt_npc_set_position, STRING("me"), -115, 0, 20)
#endif
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("O_1"), STRING("T_3"))
        CALL(evt_npc_set_tribe, STRING("me"), STRING("車掌悲"))
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the conductor in the baggage car:
 * before the escape he says he is stuck (stg6_rsh_249_01_01), afterwards he thanks Mario (stg6_rsh_242).
 */
static EVT_BEGIN(talk_syashou)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_249_01_01"), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_242"), 0, 0)
    END_IF
    RETURN
EVT_END()

/**
 * Init event of the waitress (ウェイトレス) in the baggage car: from STORY_STG6_46_ENGINEER to
 * STORY_STG6_48_SMORG_MIASMA she is at (50, 0, 0), caught by the Smorgs, with the P_1 / T_5 poses and the
 * distressed tribe ウェイトレス悲; at other times she is off the map.
 */
static EVT_BEGIN(init_waitless)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 50, 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("P_1"), STRING("T_5"))
        CALL(evt_npc_set_tribe, STRING("me"), STRING("ウェイトレス悲"))
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the waitress in the baggage car:
 * before the escape she says she is stuck (stg6_rsh_249_01_02), afterwards she thanks Mario (stg6_rsh_243).
 */
static EVT_BEGIN(talk_waitless)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_249_01_02"), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_243"), 0, 0)
    END_IF
    RETURN
EVT_END()

/** Doors and exits of rsh_05 variant a: e_bero to rsh_04_a; w_bero to rsh_06_a. */
static BeroEntry bero_data_a[] = {
    {
        ("e_bero"), // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_04_a", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        ("w_bero"), // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_06_a", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/** Doors and exits of rsh_05 variant b: e_bero to rsh_04_b; w_bero to rsh_06_a. */
static BeroEntry bero_data_b[] = {
    {
        ("e_bero"), // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_04_b", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        ("w_bero"), // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_06_a", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/** Doors and exits of rsh_05 variant c: e_bero to rsh_04_c; w_bero to rsh_06_a. */
static BeroEntry bero_data_c[] = {
    {
        ("e_bero"), // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_04_c", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        ("w_bero"), // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_06_a", // nextMapName
        ("w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/** NPCs of the car: the conductor. */
static NpcSetupInfo npc_data[] = {
    {
        "車掌", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_syashou, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"ウェイトレス"*/"\x83" "E\x83" "F\x83" "C\x83g\x83\x8c\x83X", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_waitless, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/** Pickup event of the Ragged Diary lying in the car: advances the story to STORY_STG6_17_GHOST_DIARY. */
EVT_BEGIN(evt_ghost_diary)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_17_GHOST_DIARY)
    RETURN
EVT_END()

/**
 * Reading the Ragged Diary: asks whether to read it (stg6_rsh_130_yn),
 * then shows its pages (stg6_rsh_131 to 133) and the ghost's remark (stg6_rsh_134).
 */
EVT_BEGIN(evt_ghost_diary_read)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_130"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg6_rsh_130_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("stg6_rsh_131"))
    CALL(evt_msg_select, 0, STRING("stg6_rsh_130_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("stg6_rsh_132"))
    CALL(evt_msg_select, 0, STRING("stg6_rsh_130_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("stg6_rsh_133"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_134"), 0, STRING("ゆうれい"))
    RETURN
EVT_END()

/** Shelf and crate hit areas of the car with the message each shows when Mario checks it. */
static ShelfMsgTbl6 access_tbl = {
    {
        {"kihako_1", "stg6_rsh_275"},
        {"kibako_2", "stg6_rsh_275"},
        {"bin_1", "stg6_rsh_276"},
        {"wagon", "stg6_rsh_280"},
        {"hako_1", "stg6_rsh_281"},
        {"hako_2", "stg6_rsh_281"},
    },
    {NULL},
};

/** Trigger script for the shelves: locks input, prints the message in LW(1) and unlocks. */
static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, LW(1), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Trigger for the bottle shelf (bin_2): the first time (LSWF 12) Mario finds a Power Punch badge (stg6_rsh_277,
 * item-get); afterwards it only prints stg6_rsh_279.
 */
static EVT_BEGIN(evt_access2)
    IF_INT_EQUAL(LSWF(12), 0)
        SET_VALUE(LSWF(12), 1)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_277"), 0, 0)
        CALL(evt_item_entry, STRING("a"), ITEM_POWER_PUNCH, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
        CALL(evt_item_get_item, STRING("a"))
        CALL(evt_mario_key_onoff, 1)
    ELSE
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_279"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

/** Registers the shelf triggers from access_tbl and the Power Punch bottle (bin_2). */
static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(&access_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("bin_2"), 0, PTR(evt_access2), 0)
    RETURN
EVT_END()

/**
 * Shared map init for rsh_05 on the first trip:
 * scenery, shelf signs and the Power Punch bottle (bin_2) trigger, and the music for the story stage.
 */
EVT_BEGIN(rsh_05_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING("yure"), 1, 0)
    END_SWITCH
    CALL_CHILD(evt_access_entry)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_02_A_CASE_OF_LOST_STEW, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(STORY_STG6_22_DOCUMENT, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_HOM1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_BETWEEN(STORY_STG6_44_END_OF_DAY_2, STORY_STG6_45_DAY_3_STARTS)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(STORY_STG6_49_POSHLEY_HEIGHTS, STORY_STG6_55_04_BOWSER_RAWK_HAWK)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init script of rsh_05 on the first trip (it is the only variant; the door back to rsh_04 goes to variant a,
 * b or c depending on the story stage).
 * Sets up the NPCs, the swarm at STORY_STG6_46_ENGINEER (with the meeting cutscene)
 * and STORY_STG6_47_00_BAGGAGE_CAR_SMORGS, locks the doors while the swarm is active,
 * and places the Ragged Diary until it is picked up.
 */
EVT_BEGIN(rsh_05_a_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        SET_VALUE(LW(0), PTR(bero_data_a))
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CASE_LESS(STORY_STG6_21_DAY_2)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CASE_LESS(STORY_STG6_26_ZIP_TOAD_CAUGHT)
        SET_VALUE(LW(0), PTR(bero_data_a))
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CASE_LESS(STORY_STG6_45_DAY_3_STARTS)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CASE_DEFAULT
        SET_VALUE(LW(0), PTR(bero_data_a))
    END_SWITCH
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_05_init_evt)
    CALL(evt_npc_setup, PTR(npc_data))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_46_ENGINEER)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(bero_case_switch_off)
        CASE_EQUAL(STORY_STG6_46_ENGINEER)
        CALL_CHILD(evt_moamoa_init)
        SPAWN_EVENT(evt_meet_moamoa)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(bero_case_switch_off)
        CASE_EQUAL(STORY_STG6_47_00_BAGGAGE_CAR_SMORGS)
        CALL_CHILD(evt_moamoa_init)
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(bero_case_switch_off)
        CASE_DEFAULT
        CALL(evt_npc_change_interrupt, STRING("車掌"), 6, PTR(talk_syashou))
        CALL(evt_npc_change_interrupt, STRING("ウェイトレス"), 6, PTR(talk_waitless))
    END_SWITCH
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_17_GHOST_DIARY)
        CALL(evt_item_entry, STRING("diary"), ITEM_RAGGED_DIARY, -90, 0, -140, ITEM_ENTRY_STAY, -1, PTR(evt_ghost_diary))
    END_IF
    RETURN
EVT_END()

/**
 * Shared map init for rsh_05 on the second visit:
 * scenery, NPCs and the music for the station the train has reached.
 */
EVT_BEGIN(rsh_05_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 0)
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
                CALL(evt_map_playanim, STRING("yure"), 1, 0)
            END_IF
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npc_data))
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_POSHLEY), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
#if VERSION <= VERSION_DEMO_US
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR5"))
#else
            CALL(evt_snd_envoff, PSND_FADE_OUT)
#endif
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        ELSE
            CALL(evt_snd_bgmoff, PSND_FADE_OUT)
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Init script of rsh_05 on the second visit: picks the door set matching the active scenery variant
 * (GSWF_RSH_REVISIT_VARIANT_A, B or C) and runs rsh_05_init_evt_nidome.
 */
EVT_BEGIN(rsh_05_a_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 1)
        SET_VALUE(LW(0), PTR(bero_data_a))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 1)
        SET_VALUE(LW(0), PTR(bero_data_b))
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 1)
        SET_VALUE(LW(0), PTR(bero_data_c))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_05_init_evt_nidome)
    RETURN
EVT_END()
