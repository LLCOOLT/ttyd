// rsh_06 (列車, Excess Express): the car of the Smorg (moamoa) boss fight, with the train wheel/coupling animation and
// departure/stop scenes; door to rsh_05.
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr.h"
#include "driver/mapdrv.h"
#include "string.h"
#include "memory.h"
#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "mario/mariost.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "driver/hitdrv.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/offscreendrv.h"
#include "system.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "party.h"
#include "party/party_cloud.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "data_tables.h"
#include "driver/extdrv.h"
#include "map/sharin.h"
#include "map/moamoa.h"
#include "driver/envdrv.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_ext.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "party/party_nokonoko.h"
#include "rsh.h"
#include "evt/evt_story.h"
#include "libc_decls.h"

// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)

static MoamoaWork* wp;
static f32 randf(f32 min, f32 max);
static void moamoa_pose_init(void);
static void moamoa_pose_main(void);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void evalOn(void);
static void ext_moamoa_main(void);
// The unit's inlining budget: the default limit changes which of the moamoa helpers are inlined (checked by
// removing it; eki_00 and rsh_05 use their own limits).
#pragma inline_max_total_size(100000)
/**
 * Polynomial approximation of sin(x) for an angle in radians in [0, 2*pi);
 * the Smorg (moamoa) swarm code uses its own sine to keep results identical on every frame without calling the
 * libm. Inlined into the swarm code.
 */
static inline f32 moa_sin(f32 x) {
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
 * Polynomial approximation of cos(x) for an angle in radians in [0, 2*pi), companion of moa_sin.
 * Inlined into the swarm code.
 */
static inline f32 moa_cos(f32 x) {
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
static s32 moamoa_hit_check(ExtdrvPose* pose, Moamoa* moa);
static void moamoa_jump(ExtdrvPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void moamoa_joint_position(Moamoa* moa, Vec* out);
static void ext_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);

static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall);
static s32 ramp_r(EventEntry* event, BOOL isFirstCall);
static void resha_tev(MapTevCallbackInfo* info);
static void ext_moamoa_dispent(void);
static void ext_moamoa_init(void);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);

static MoamoaData ext_moamoa_data[71];
static SharinData sharinDt[29];
static ClankData clankDt[9];
static const char* pika_tbl[15];
static const char* pika_tbl_rsh_06[10];
extern EvtWord evt_resha_init[];
static BeroEntry bero_data_a[2];
extern EvtWord evt_great_moamoa[];
const char* pose_name[8];
extern EvtWord moamoa_debug[];
extern EvtWord rsh_06_init_evt[];
extern EvtWord rsh_06_init_evt_nidome[];

/**
 * Animation table of the swarm of small Smorgs (c_n_moa_a) that merge into the giant Smorg:
 * the figure, its animation set and a start offset for each.
 */
static MoamoaData ext_moamoa_data[] = {
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 0.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 2.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 4.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 6.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 8.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 10.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 12.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 14.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 16.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 18.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 20.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 22.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 24.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 26.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 28.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 30.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 32.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 34.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 36.0f},
    {((char*)"c_n_moa_a"), ((char*)"S_1"), 38.0f},
    {((char*)"c_n_moa_a"), ((char*)"D_1"), 0.0f},
    {((char*)"c_n_moa_a"), ((char*)"D_1"), 4.0f},
    {((char*)"c_n_moa_a"), ((char*)"D_1"), 8.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 0.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 2.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 4.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 6.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 8.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 10.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 12.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 14.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 16.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 18.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 20.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 22.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 24.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 26.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 28.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 30.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 32.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 34.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 36.0f},
    {((char*)"c_n_moa_b"), ((char*)"S_1"), 38.0f},
    {((char*)"c_n_moa_b"), ((char*)"D_1"), 0.0f},
    {((char*)"c_n_moa_b"), ((char*)"D_1"), 4.0f},
    {((char*)"c_n_moa_b"), ((char*)"D_1"), 8.0f},
    {((char*)"c_kinodebu"), ((char*)"G_1"), 0.0f},
    {((char*)"c_kinodebu"), ((char*)"G_1"), 4.0f},
    {((char*)"c_kinodebu"), ((char*)"G_1"), 8.0f},
    {((char*)"c_puku_c"), ((char*)"U_1"), 0.0f},
    {((char*)"c_puku_c"), ((char*)"U_1"), 4.0f},
    {((char*)"c_puku_c"), ((char*)"U_1"), 8.0f},
    {((char*)"c_powan"), ((char*)"O_1"), 0.0f},
    {((char*)"c_powan"), ((char*)"O_1"), 4.0f},
    {((char*)"c_powan"), ((char*)"O_1"), 8.0f},
    {((char*)"c_smoko"), ((char*)"T_2"), 0.0f},
    {((char*)"c_smoko"), ((char*)"T_2"), 4.0f},
    {((char*)"c_smoko"), ((char*)"T_2"), 8.0f},
    {((char*)"c_rose"), ((char*)"G_1"), 0.0f},
    {((char*)"c_rose"), ((char*)"G_1"), 4.0f},
    {((char*)"c_rose"), ((char*)"G_1"), 8.0f},
    {((char*)"c_papab"), ((char*)"G_1"), 0.0f},
    {((char*)"c_papab"), ((char*)"G_1"), 4.0f},
    {((char*)"c_papab"), ((char*)"G_1"), 8.0f},
    {((char*)"c_mamab"), ((char*)"G_1"), 0.0f},
    {((char*)"c_mamab"), ((char*)"G_1"), 4.0f},
    {((char*)"c_mamab"), ((char*)"G_1"), 8.0f},
    {((char*)"c_konari"), ((char*)"G_1"), 0.0f},
    {((char*)"c_konari"), ((char*)"G_1"), 4.0f},
    {((char*)"c_konari"), ((char*)"G_1"), 8.0f},
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
#pragma dont_inline reset
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
/**
 * Switches one Moamoa to the named model/animation pair (a swarm member with MOAMOA_FLAG_KIND_MODEL set uses the
 * model of its kind from group_tbl instead) and restarts its animation clock.
 * A damaged Moamoa only accepts D_ poses and an escaping one only R_ poses.
 * Out-of-line copy of moamoa_pose_change_i.
 */
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    static const char* group_tbl[][2] = {
        {(char*)"c_n_moa_a", (char*)"S_1"},
        {(char*)"c_n_moa_b", (char*)"S_1"},
        {(char*)"c_kinodebu", (char*)"G_1"},
        {(char*)"c_puku_c", (char*)"U_1"},
        {(char*)"c_powan", (char*)"O_1"},
        {(char*)"c_smoko", (char*)"T_2"},
        {(char*)"c_rose", (char*)"G_1"},
        {(char*)"c_papab", (char*)"G_1"},
        {(char*)"c_mamab", (char*)"G_1"},
        {(char*)"c_konari", (char*)"G_1"},
        {(char*)"c_n_moa_a", (char*)"S_1"},
    };
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & MOAMOA_FLAG_KIND_MODEL) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = (char*)"S_2";
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & MOAMOA_FLAG_DAMAGED) {
            if (strncmp(anim, (char*)"D", 1)) {
                return;
            }
        }
        if (moa->flags & MOAMOA_FLAG_ESCAPING) {
            if (strncmp(anim, (char*)"R", 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
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
        moamoa_pose_change(moa, (char*)"c_n_moa_a", (char*)"S_1");
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
        moamoa_pose_change(moa, (char*)"c_n_moa_a", (char*)"S_1");
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
        moamoa_pose_change(moa, (char*)"c_n_moa_a", (char*)"S_1");
    }
    return EVT_RETURN_DONE;
}
/**
 * Prepares the giant Smorg's body: turns on world-position evaluation for the "base" NPC's skeleton,
 * hides its joints, sets up the chains of Moamoa along the bones and divides the swarm among them.
 * Gives some chains the models of the swallowed passengers (kinds 1 to 9).
 */
static void evalOn(void) {
    NpcEntry* npc = npcNameToPtr("base");
    AnimationPose* anim;
    Moamoa* moa;
    s32 i;
    s32 j;
    Vec* pos;
    s32 n;

    animPoseWorldPositionEvalOn(npc->poseId);
    wp->animPoseId = npc->poseId;
    anim = animPoseGetAnimPosePtr(npc->poseId);
    pos = anim->worldPositions[0];
    n = anim->numWorldPositions;
    for (i = 0; i < n; i++) {
        pos[i] = (Vec){0.0f, -1000.0f, 0.0f};
    }
    for (i = 0; i < g_moamoa_chain_max; i++) {
        wp->chainIdx[i][0] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i].from);
        wp->chainIdx[i][1] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i].to);
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        moa->group = j % g_moamoa_chain_max;
        moa->order = wp->chainNum[moa->group]++;
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        if (moa->group == 0 || moa->group == 5 || moa->group == 10 || moa->group == 15 || moa->group == 30 ||
            moa->group == 34 || moa->group == 38 || moa->group == 42 || moa->group == 46) {
            moa->kind = 1;
        }
        if (moa->order == 0) {
            if (moa->group == 3) {
                moa->kind = 2;
            }
            if (moa->group == 4) {
                moa->kind = 3;
            }
            if (moa->group == 7) {
                moa->kind = 4;
            }
            if (moa->group == 8) {
                moa->kind = 5;
            }
            if (moa->group == 9) {
                moa->kind = 6;
            }
            if (moa->group == 12) {
                moa->kind = 7;
            }
            if (moa->group == 13) {
                moa->kind = 8;
            }
            if (moa->group == 14) {
                moa->kind = 9;
            }
        }
    }
}
/**
 * Script helper: retires one of the swarm's targets.
 * args[0] picks target 0 or 1; its hit count is set to 100,
 * the target is replaced by the other one and the matching MOAMOA_WORK_TARGETn_OFF bit is set.
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
 * Init callback of the swarm effect on the roof (evt_ext_entry):
 * allocates the work area, puts all three targets at the center of the roof (10, 215, 0),
 * scatters the sprites over the roof (a sprite with no floor under it is put in the background and flagged
 * MOAMOA_FLAG_OFF_FLOOR), gives each a small random jitter,
 * builds the body chains (evalOn) and runs 600 frames of the swarm logic so it starts spread out.
 */
static void ext_moamoa_init(void) {
    s32 i;
    ExtdrvPose* pose;
    Moamoa* moa;
    Vec v;
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = (Vec){10.0f, 215.0f, 0.0f};
    wp->target[1] = (Vec){10.0f, 215.0f, 0.0f};
    wp->target[2] = (Vec){10.0f, 215.0f, 0.0f};
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
        moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        pose->flags |= 7;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = randf(-500.0f, 500.0f);
        (*pose->mtx)[1][3] = 215.0f;
        (*pose->mtx)[2][3] = randf(-45.0f, 45.0f);
        hitX = hitY = hitZ = 0.0f;
        dist = 1000000.0f;
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, (*pose->mtx)[0][3], 100.0f + (*pose->mtx)[1][3], (*pose->mtx)[2][3], 0.0f, -1.0f, 0.0f)) {
            (*pose->mtx)[1][3] = hitY;
        } else {
            pose->flags |= 4;
            (*pose->mtx)[0][3] = randf(-500.0f, 500.0f);
            (*pose->mtx)[1][3] = randf(100.0f, 215.0f);
            (*pose->mtx)[2][3] = randf(70.0f, 75.0f);
            moa->flags |= MOAMOA_FLAG_OFF_FLOOR;
            moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        }
        v = (Vec){0.0f, 0.0f, 0.0f};
        v.x = randf(-10.0f, 10.0f);
        v.y = randf(-10.0f, 10.0f);
        v.z = randf(-10.0f, 10.0f);
        moa->jitter = v;
    }
    evalOn();
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
        offscreenAddBoundingBox(offscreenNameToId((char*)"offscreen"), left, top, right, bottom);
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
        offscreenAddBoundingBox(offscreenNameToId((char*)"offscreen"), left, top, right, bottom);
    }
}

// FAKE: dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
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
            if (__fabs(y - hitY) > 30.0) {
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
#pragma dont_inline reset
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
    CameraEntry* cam;
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
    if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], mario->position.x, mario->position.z) < (20.0f + mario->wPlayerCollisionBox.x) / 2 && mario->position.y > 10.0f + (*pose->mtx)[1][3] && (mario->flags & MARIO_FLAG_IS_FALLING) && !(mario->flags & MARIO_FLAG_IS_JUMPING) && wp->bounceCount < 2) {
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
        cam = camGetPtr(CAMERA_3D);
        {
            f32 yaw = cam->viewYaw;
            rad = reviseAngle((mario->displayDirection - 90.0f) + yaw);
        }
        angle = 35.0f * moa_sin((6.2831855f * rad) / 360.0f) + mario->position.x;
        dist = mario->position.z - 35.0f * moa_cos((6.2831855f * rad) / 360.0f);
        if (distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], angle, dist) < 35.0f) {
            return 2;
        }
    }
    if (mario->currMotionId == MARIO_MOTION_HAMMER_2 && (s32)mario->currSubMotionId == 0x14) {
        {
            f32(*m)[4] = *pose->mtx;
            a = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        if (PSVECDistance(&mario->position, &a) < 65.0f) {
            return 2;
        }
    }
    if (wp->breathDir >= 0.0f) {
        {
            f32(*m)[4] = *pose->mtx;
            b = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        if (PSVECDistance(&wp->breathPos, &b) < 30.0f) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        {
            f32(*m)[4] = *pose->mtx;
            c = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < 30.0f) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == PARTY_MEMBER_BOBBERY && partyGetPtr(0)->useMotionId == 0x46) {
        {
            f32(*m)[4] = *pose->mtx;
            d = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < 50.0f) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, (*pose->mtx)[1][3], mario->position.z};
    {
        f32(*m)[4] = *pose->mtx;
        f = (Vec){m[0][3], m[1][3], m[2][3]};
    }
    range = (20.0f + mario->wPlayerCollisionBox.x) / 2;
    if (PSVECDistance(&e, &f) < range) {
        (*pose->mtx)[0][3] = moa->lastX;
        (*pose->mtx)[2][3] = moa->lastZ;
        {
            f32(*m)[4] = *pose->mtx;
            f = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
                mario->floorMove.x = -((range - dist) * moa_sin(6.2831855f * mario->directionView / 360.0f));
                mario->floorMove.z = (range - dist) * moa_cos(6.2831855f * mario->directionView / 360.0f);
            } else {
                rad = 6.2831855f * angle / 360.0f;
                mario->floorMove.x = (*pose->mtx)[0][3] - range * moa_sin(rad) - mario->position.x;
                mario->floorMove.z = (*pose->mtx)[2][3] + range * moa_cos(rad) - mario->position.z;
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
#pragma opt_dead_assignments off // FAKE: keeps the named in-argument holder `aa` of case 15 (dead store otherwise dropped by IRO), so the sum is a low-numbered named vreg as in the target
// FAKE: identity function used so the compiler keeps the original code shape of the swarm main loop; it returns its
// argument.
static inline f32 mmI(f32 x) {
    return x;
} // FAKE: identity; replaces the dead `(k = A - B)` holders of the hand-inlined randf sites, which opt_dead_assignments off would otherwise keep as named vregs
/**
 * Per-frame callback of the Smorg swarm.
 * Tracks hammer and idle time, Flurrie's breath and partner use, counts hits on the swarm's targets,
 * and runs each Moamoa's state machine (idle hopping toward its target or Mario, jumps, damage and knock-off,
 * escape, gathering and merging, being blown away).
 * When both targets have been freed it starts the swarm's escape.
 */
static void ext_moamoa_main(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    s32 hit = 0;
    s32 sndFlag;
    s32 i;
    s32 ret;
    s32 idx;
    ExtdrvPose* pose;
    ExtdrvPose* other;
    Moamoa* m;
    f32 jumpSpeed;
    f32 spd;
    f32 rad;
    f32 angle;
    f32 x;
    f32 y;
    f32 z;
    f32 z0;
    f32 x1;
    f32 dist;
    f32 s;
    f32 x0;
    f32 tx;
    Vec sp;
    Vec jv;
    Vec pv;
    Mtx rot;
    f32 cnt = 0.0f;
    f32 a;
    f32 d;
    f32 r;

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
    if ((party->currentMemberId == PARTY_MEMBER_FLURRIE) && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        wp->breathDir = cloudGetBreathDir();
        wp->breathDist = cloudGetBreathDist();
        wp->breathPos.x = (wp->breathDist * moa_sinx((6.2831855f * wp->breathDir) / 360.0f)) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - (wp->breathDist * moa_cosx((6.2831855f * wp->breathDir) / 360.0f));
    }

    pose = extGetPosePtr();
    sndFlag = 0;
    m = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, m++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, (*pose->mtx)[0][3], (*pose->mtx)[2][3]);
        if (((!(m->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING))) && (mario->position.y > 200.0f)) && (wp->dist < 30.0f)) {
            cnt += 1.0f;
        }
#if VERSION <= VERSION_DEMO_US
        if ((((wp->flags & MOAMOA_WORK_ACTIVE) && (!(wp->flags & MOAMOA_WORK_NO_HIT))) && (!hit)) && (!(m->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING)))) {
#else
        if ((((((wp->flags & MOAMOA_WORK_ACTIVE) && (!(wp->flags & MOAMOA_WORK_NO_HIT))) && (!marioKeyOffChk())) && (!marioCtrlOffChk())) && (!hit)) && (!(m->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING)))) {
#endif
            ret = moamoa_hit_check(pose, m);
            if (ret == 1) {
                m->flags |= MOAMOA_FLAG_DAMAGED;
                m->state = 36;
                wp->hitCount++;
                moamoa_pose_change(m, "c_n_moa_a", "D_1");
                hit = 1;
            } else if ((ret == 2) || (ret == 4)) {
                m->flags |= MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_KNOCKED;
                m->state = 47;
                wp->hitCount++;
                moamoa_pose_change(m, "c_n_moa_a", "D_1");
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                angle = (wp->breathDir + wp->angle) / 2.0f;
                m->flags |= MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_BLOWN;
                m->state = 48;
                m->target = moamoa_zero_vec;
                {
                    spd = randf(0.1f, 0.2f);
                    rad = (6.2831855f * angle) / 360.0f;
                    m->vy = spd * moa_sinx(rad);
                    m->speed = randf(0.03f, 0.06f);
                    m->gravity = spd * (-moa_cosx(rad));
                }
                m->jumpTimer = 120;
                wp->hitCount++;
                moamoa_pose_change(m, "c_n_moa_a", "D_1");
                hit = 1;
            }
        }
        if ((wp->flags & MOAMOA_WORK_ACTIVE) && (!(m->flags & (MOAMOA_FLAG_TO_TARGET | MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_ESCAPING | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_FUSING)))) {
#if VERSION <= VERSION_DEMO_US
            if (mario->currMotionId == MARIO_MOTION_STAY || mario->currMotionId == MARIO_MOTION_WALK || mario->currMotionId == MARIO_MOTION_DASH) {
#else
            if ((((mario->currMotionId == MARIO_MOTION_STAY) || (((u16)(mario->currMotionId - MARIO_MOTION_WALK)) <= 1)) || (((u16)(mario->currMotionId - MARIO_MOTION_SLIT)) <= 1)) ||
                (mario->currMotionId == MARIO_MOTION_YOSHI)) {
#endif
                if ((((mario->position.y > 200.0f) && (wp->dist > 30.0f)) && (wp->dist < 100.0f)) && (i & 1)) {
                    if (m->flags & MOAMOA_FLAG_JUMPING) {
                        m->next = 2;
                    } else {
                        m->state = 2;
                    }
                }
            } else if (wp->dist < 50.0f) {
                if (m->flags & MOAMOA_FLAG_JUMPING) {
                    m->next = 1;
                } else {
                    m->state = 1;
                }
            }
        }
        if ((((wp->flags & MOAMOA_WORK_ACTIVE) && (!(m->flags & (MOAMOA_FLAG_DAMAGED | MOAMOA_FLAG_OFF_FLOOR | MOAMOA_FLAG_MERGED)))) && (i == (gp->retraceCount % wp->count))) && (irand(1000) < 200)) {
            {
                Vec tmp = {0.0f, 0.0f, 0.0f};
                tmp.x = (*pose->mtx)[0][3];
                tmp.y = (*pose->mtx)[1][3];
                tmp.z = (*pose->mtx)[2][3];
                sp = tmp;
            }
            psndSFXOn_3D(SFX_NAME_WORD("SFX_STG6_MOAMOA_VOICE1"), &sp); /* FAKE: integer cast hoists the literal as an @ temp (sfx local removed) */
        }
        switch (m->state) {
            case 0:
                if (m->flags & MOAMOA_FLAG_OFF_FLOOR) {
                    break;
                }
                {
                    f32 mn;
                    f32 rr;
                    f32 rnd = rand() / 32767.0f;
                    rr = (6.2831855f * ((rnd * mmI(360.0f - 0.0f)) + (mn = 0.0f))) / 360.0f; // FAKE: hand-inlined randf(0.0f, 360.0f) (same rand() call, rnd*360+0) with the 6.28 factor first, so its pool address is created before 360/0 as in the target
                    x0 = (5.0f * moa_sinx(rr)) + (*pose->mtx)[0][3];
                    z0 = (*pose->mtx)[2][3] - (5.0f * moa_cosx(rr));
                }
                {
                    f32 k1;
                    f32 k2;
                    f32 rand1 = rand() / 32767.0f;
                    f32 rand2 = rand() / 32767.0f;
                    moamoa_jump(pose, m, m->state, 0, x0, 215.0f, z0, (rand1 * (k1 = 0.5f - 0.3f)) + 0.3f, (rand2 * (k2 = 0.8f - 0.5f)) + 0.5f);
                }
                break;
            case 14:
                if ((--m->timer) < 0) {
                    m->timer = 0;
                    m->state++;
                }
                break;
            case 15:
                dist = distABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                angle = angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                if (dist > 31.0f) {
                    x1 = (30.0f * moa_sinx((6.2831855f * angle) / 360.0f)) + (*pose->mtx)[0][3];
                    dist = (*pose->mtx)[2][3] - (30.0f * moa_cosx((6.2831855f * angle) / 360.0f));
                    {
                        f32 k1;
                        f32 k2;
                        f32 rand2;
                        f32 aa;
                        s = rand() / 32767.0f;
                        rand2 = rand() / 32767.0f;
                        moamoa_jump(pose, m, m->state, 0, x1, 215.0f, dist, 2.0f * (aa = (s * (k1 = 1.0f - 1.0f)) + 1.0f), 2.0f * ((rand2 * (k2 = 0.4f - 0.4f)) + 0.4f));
                    } // FAKE: `aa` is a never-read holder kept by opt_dead_assignments off (in-argument sum stays in argument order, numbered below k/rand2)
                } else {
                    moamoa_joint_position(m, &jv);
                    PSVECAdd(&jv, &m->jitter, &jv);
                    {
                        f32 k1;
                        f32 k2;
                        f32 rand2;
                        d = rand() / 32767.0f;
                        rand2 = rand() / 32767.0f;
                        moamoa_jump(pose, m, 61, 0, jv.x, jv.y, jv.z, 2.0f * ((d * (k1 = 1.5f - 1.5f)) + 1.5f), 2.0f * ((rand2 * (k2 = 0.8f - 0.8f)) + 0.8f));
                    }
                    m->flags |= MOAMOA_FLAG_GATHERED;
                    pose->flags |= 4;
                }
                break;
            case 61:
                moamoa_joint_position(m, &pv);
                PSVECAdd(&pv, &m->jitter, &pv);
                (*pose->mtx)[0][3] = pv.x;
                (*pose->mtx)[1][3] = pv.y;
                (*pose->mtx)[2][3] = pv.z;
                break;
            case 50:
                if ((--m->timer) < 0) {
                    m->timer = 0;
                    m->state++;
                }
                break;
            case 51:
                m->speed = randf(0.0f, 200.0f);
                m->gravity = randf(0.0f, 300.0f * m->speed / 200.0f);
                m->state++;
                m->timer = 0;
            case 52: {
                f32 orbitX;
                f32 orbitY;
                f32 orbitZ;
                f32 orbitScale;
                orbitScale = (m->timer < 200) ? (1.0f) : ((800 - m->timer) / 600.0f);
                if (orbitScale < 0.0f) {
                    orbitScale = 0.0f;
                    m->flags |= MOAMOA_FLAG_GATHERED;
                }
                orbitX = wp->target[i % 3].x;
                orbitY = wp->target[i % 3].y;
                orbitZ = wp->target[i % 3].z;
                orbitX += orbitScale * (m->gravity * ((f32)sin(((f32)(i + gp->retraceCount)) / 4.0f)));
                r = i + gp->retraceCount;
                orbitY += m->speed * orbitScale;
                orbitZ += orbitScale * ((-m->gravity) * ((f32)cos(r / 4.0f)));
                (*pose->mtx)[0][3] += (orbitX - (*pose->mtx)[0][3]) / 15.0f;
                (*pose->mtx)[1][3] += (orbitY - (*pose->mtx)[1][3]) / 15.0f;
                (*pose->mtx)[2][3] += (orbitZ - (*pose->mtx)[2][3]) / 15.0f;
                m->timer++;
                break;
            }
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
                z = (*pose->mtx)[1][3];
                dist = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                {
                    f32 hopSpeed;
                    f32 rand1 = rand() / 32767.0f;
                    hopSpeed = rand1 * mmI(1.0f - 1.0f) + 1.0f;
                    // FAKE: block-local copies of the float args (behaviour-identical) put the f1..f5 arg moves ahead of the ?: as in the target
                    {
                        f32 g2 = randf(0.4f, 0.4f);
                        {
                            f32 x2 = x;
                            f32 y2 = z;
                            f32 z2 = dist;
                            f32 s2 = hopSpeed;
                            f32 g3 = g2;
                            moamoa_jump(pose, m, (d < 100.0f) ? (m->state) : (0), 0, x2, y2, z2, s2, g3);
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
                    jumpSpeed = 2.0f * ((rand1 * mmI(1.0f - 1.0f)) + 1.0f);
                    rand2 = rand() / 32767.0f;
                    b = 2.0f * ((rand2 * (k = 0.4f - 0.4f)) + 0.4f);
                    // FAKE: block-local copies of the float args (behaviour-identical) put the f1..f5 arg moves ahead of the ?: as in the target
                    {
                        f32 x2 = hopX;
                        f32 y2 = y;
                        f32 z2 = hopZ;
                        f32 s2 = jumpSpeed;
                        f32 g2 = b;
                        moamoa_jump(pose, m, (d < 100.0f) ? (m->state) : (0), 0, x2, y2, z2, s2, g2);
                    }
                }
                break;
            }

            case 3:
                (*pose->mtx)[1][3] += m->vy;
                m->vy -= m->gravity;
                {
                    f32 moveRad = (6.2831855f * angleABf((*pose->mtx)[0][3], (*pose->mtx)[2][3], m->target.x, m->target.z)) / 360.0f;
                    (*pose->mtx)[0][3] += m->speed * moa_sinx(moveRad);
                    (*pose->mtx)[2][3] = (*pose->mtx)[2][3] + (m->speed * (-moa_cosx(moveRad)));
                }
                if ((--m->jumpTimer) < 0) {
                    (*pose->mtx)[0][3] = m->target.x;
                    (*pose->mtx)[1][3] = m->target.y;
                    (*pose->mtx)[2][3] = m->target.z;
                    m->flags &= ~MOAMOA_FLAG_JUMPING;
                    pose->flags &= ~0x10;
                    m->timer = 0;
                    m->state++;
                }
                break;

            case 4:
                if ((++m->timer) > 4) {
                    m->state = m->next;
                }
                break;
            case 36:

            case 37:

            case 38: {
                f32 targetZ;
                if (!(m->flags & MOAMOA_FLAG_TO_TARGET)) {
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
                        x = (*pose->mtx)[0][3] + (15.0f * moa_sinx(hopRad));
                        y = (*pose->mtx)[1][3];
                        hopZ = (*pose->mtx)[2][3] - (15.0f * moa_cosx(hopRad));
                    }
                    {
                        f32 k;
                        f32 rand1 = rand() / 32767.0f;
                        f32 rand2 = rand() / 32767.0f;
                        k = 1.0f - 1.0f;
                        moamoa_jump(pose, m, m->state + 1, 1, x, y, hopZ, (rand1 * k) + 1.0f, (rand2 * k) + 1.0f);
                    }
                }
            } break;

            case 39:
                if ((++m->timer) < 30) {
                    (*pose->mtx)[0][0] *= 0.9f;
                    (*pose->mtx)[1][1] *= 0.9f;
                    (*pose->mtx)[2][2] *= 0.9f;
                } else {
                    m->state = 49;
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
                    f32 rand1 = rand() / 32767.0f;
                    spd = (rand1 * mmI(6.0f - 5.0f)) + 5.0f;
                }
                {
                    f32 rand1 = rand() / 32767.0f;
                    s = (rand1 * mmI(0.3f - 0.2f)) + 0.2f;
                }
                if (!sndFlag) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = (*pose->mtx)[0][3];
                    pos.y = (*pose->mtx)[1][3];
                    pos.z = (*pose->mtx)[2][3];
                    psndSFXOn_3D((const char*)0x6c3, &pos);
                    sndFlag = 1;
                }
                dist = -100.0f;
                moamoa_jump(pose, m, 49, 0, x, dist, y, spd, s);
                break;

            case 48:
                if ((--m->jumpTimer) > 0) {
                    m->target.x += m->vy;
                    m->target.y += m->speed;
                    m->target.z += m->gravity;
                    (*pose->mtx)[0][3] += m->target.x;
                    (*pose->mtx)[1][3] += m->target.y;
                    (*pose->mtx)[2][3] += m->target.z;
                } else {
                    m->state = 49;
                }
                break;
            case 49:
                PSMTXIdentity(*pose->mtx);
                {
                    Moamoa* mm;
                    do {
                        idx = rand() % 700;
                        mm = &wp->moa[idx];
                    } while (((mm->state != 0) && (mm->state != 3)) || (mm->flags & MOAMOA_FLAG_OFF_FLOOR));
                }
                other = extGetPosePtr() + idx;
                (*pose->mtx)[0][3] = (*other->mtx)[0][3];
                (*pose->mtx)[1][3] = 215.0f;
                (*pose->mtx)[2][3] = (*other->mtx)[2][3];
                m->flags = 0;
                m->state = 0;
                m->timer = 0;
                break;
            case 62:
                m->flags |= MOAMOA_FLAG_GONE;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63: {
                f32 k;
                s = rand() / 32767.0f;
                spd = randf(2.0f, 3.0f);
                m->timer = irand(i / 2);
                rad = (6.2831855f * ((s * (k = 315.0f - 225.0f)) + 225.0f)) / 360.0f;
            }
                m->target.x = spd * moa_sinx(rad);
                m->target.y = randf(1.0f, 2.0f);
                m->target.z = spd * (-moa_cosx(rad));
                m->state++;
                break;

            case 64:
                if ((--m->timer) < 0) {
                    m->state++;
                }
                break;
            case 65:
                m->target.x *= 1.1f;
                m->target.y *= 1.02f;
                m->target.z *= 1.1f;
                (*pose->mtx)[0][3] += m->target.x;
                (*pose->mtx)[1][3] += m->target.y;
                (*pose->mtx)[2][3] += m->target.z;
                PSMTXRotRad(rot, 'y', 0.20943952f);
                PSMTXConcat(*pose->mtx, rot, *pose->mtx);
                pose->flags &= ~2;
                if ((*pose->mtx)[0][3] < (-1000.0f)) {
                    m->state = 62;
                }
                break;
        }
        if (!(m->flags & (MOAMOA_FLAG_KNOCKED | MOAMOA_FLAG_BLOWN | MOAMOA_FLAG_FUSING | MOAMOA_FLAG_MERGED))) {
            f32 nx;
            if ((cam->cameraAt.x - (*pose->mtx)[0][3]) > 250.0f) {
                nx = 450.0f + (*pose->mtx)[0][3];
                if (nx < (-50.0f)) {
                    (*pose->mtx)[0][3] = nx;
                }
            } else if (((*pose->mtx)[0][3] - cam->cameraAt.x) > 250.0f) {
                nx = (*pose->mtx)[0][3] - 450.0f;
                if (nx > (-1870.0f)) {
                    (*pose->mtx)[0][3] = nx;
                }
            }
        }
        if (!(m->flags & (MOAMOA_FLAG_KNOCKED | MOAMOA_FLAG_BLOWN | MOAMOA_FLAG_FUSING | MOAMOA_FLAG_MERGED))) {
            if ((*pose->mtx)[0][3] > 100.0f) {
                {
                    f32 rnd = rand() / 32767.0f;
                    (*pose->mtx)[0][3] = 100.0f + ((rnd * mmI(5.0f - 0.0f)) + mmI(0.0f));
                } // FAKE: hand-inlined randf(0.0f, 5.0f) (same rand() call, same r*5+0 then +c), so the constant is reloaded after the call as in the target
            }
            if ((*pose->mtx)[0][3] < -1870.0f) {
                {
                    f32 rnd = rand() / 32767.0f;
                    (*pose->mtx)[0][3] = -1870.0f + ((rnd * mmI(5.0f - 0.0f)) + mmI(0.0f));
                }
            }
            if (!(m->flags & MOAMOA_FLAG_OFF_FLOOR)) {
                if ((*pose->mtx)[2][3] > 45.0f) {
                    {
                        f32 rnd = rand() / 32767.0f;
                        (*pose->mtx)[2][3] = 45.0f + ((rnd * mmI(5.0f - 0.0f)) + mmI(0.0f));
                    }
                }
                if ((*pose->mtx)[2][3] < -45.0f) {
                    {
                        f32 rnd = rand() / 32767.0f;
                        (*pose->mtx)[2][3] = -45.0f + ((rnd * mmI(5.0f - 0.0f)) + mmI(0.0f));
                    }
                }
            }
        }
        m->lastX = (*pose->mtx)[0][3];
        m->lastZ = (*pose->mtx)[2][3];
    }
    moamoa_pose_main();
    mario->floorMove.x = 0.0f;
    mario->floorMove.y = 0.0f;
    mario->floorMove.z = 0.0f;
    if (!(wp->flags & 0x18)) {
#if VERSION <= VERSION_DEMO_US
        // the demo moves Mario himself instead of setting his floor movement
        mario->position.x -= cnt / 20.0f;
#else
        mario->floorMove.x = (-cnt) / 20.0f;
#endif
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#pragma opt_dead_assignments reset
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
/**
 * Computes the world position of one Moamoa on the giant Smorg's body:
 * a point along the bone chain of its group, interpolated by its order in the chain,
 * taken from the base model's joint positions.
 */
static void moamoa_joint_position(Moamoa* moa, Vec* out) {
    NpcEntry* npc = npcNameToPtr((char*)"base");
    AnimationPose* anim = animPoseGetAnimPosePtr(npc->poseId);
    f32 t;
    Vec* b = anim->worldPositions[0] + wp->chainIdx[moa->group][1];
    Vec tmp;

    t = (f32)moa->order / (f32)wp->chainNum[moa->group];
    PSVECScale(anim->worldPositions[0] + wp->chainIdx[moa->group][0], out, t);
    PSVECScale(b, &tmp, 1.0f - t);
    PSVECAdd(out, &tmp, out);
}

/** Wheels of the train: each wheel map object (sha_N_M) with how it turns and its speed. */
static SharinData sharinDt[] = {
    {((char*)"sha_1_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_1_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_1_3"), 2, 0, FLOAT(1.0f)},
    {((char*)"sha_1_4"), 1, 1, FLOAT(1.0f)},
    {((char*)"sha_1_5"), 1, 1, FLOAT(1.0f)},
    {((char*)"sha_2_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_2_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_2_3"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_3_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_3_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_3_3"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_4_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_4_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_4_3"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_5_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_5_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_5_3"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_6_1"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_6_2"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_6_3"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_1_1_c"), 0, 0, FLOAT(-1.0f)},
    {((char*)"sha_1_2_c"), 0, 0, FLOAT(-1.0f)},
    {((char*)"sha_1_3_c"), 2, 0, FLOAT(-1.0f)},
    {((char*)"sha_1_4_c"), 1, 1, FLOAT(-1.0f)},
    {((char*)"sha_1_5_c"), 1, 1, FLOAT(-1.0f)},
    {((char*)"sha_6_1_c"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_6_2_c"), 0, 0, FLOAT(1.0f)},
    {((char*)"sha_6_3_c"), 0, 0, FLOAT(1.0f)},
    {0},
};

/**
 * Spins one wheel map object (LW(0)) of the train:
 * LW(1) picks the wheel's radius and LW(2) picks which wheel speed, GW(0) or GW(1), drives it;
 * every frame the angle grows by speed over radius and the object is rotated.
 */
static EVT_BEGIN(evt_sharin_main)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_FLOAT_VALUE(LW(11), FLOAT(23.889648f))
        CASE_EQUAL(1)
        SET_FLOAT_VALUE(LW(11), FLOAT(31.139648f))
        CASE_EQUAL(2)
        SET_FLOAT_VALUE(LW(11), FLOAT(55.01953f))
    END_SWITCH
    LOOP(0)
        SWITCH(LW(2))
            CASE_EQUAL(0)
            SET_FLOAT_VALUE(LW(9), GW(0))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(9), GW(1))
        END_SWITCH
        DIVIDE_FLOAT(LW(9), LW(11))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        SET_FLOAT_VALUE(LW(12), LW(10))
        MULTIPLY_FLOAT(LW(12), LW(3))
        CALL(evt_mapobj_rotate, 1, LW(0), 0, 0, LW(12))
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

/** Starts evt_sharin_main for every wheel listed in sharinDt (sha_1_1 and so on). */
static EVT_BEGIN(evt_sharin)
    SET_INT_READ_ADDR(PTR(sharinDt))
    LOOP(0)
        READ_INT4(LW(0), LW(1), LW(2), LW(3))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(evt_sharin_main)
    END_LOOP
    RETURN
EVT_END()

/** Connecting rods (bou_N) of the train, each moved in a circle together with its wheel. */
static ClankData clankDt[] = {
    {((char*)"bou_1"), 0, 0, FLOAT(20.0f), FLOAT(1.0f)},
    {((char*)"bou_2"), 1, 1, FLOAT(16.5f), FLOAT(1.0f)},
    {((char*)"bou_3"), 0, 0, FLOAT(20.0f), FLOAT(1.0f)},
    {((char*)"bou_4"), 1, 1, FLOAT(16.5f), FLOAT(1.0f)},
    {((char*)"bou_1_c"), 0, 0, FLOAT(20.0f), FLOAT(-1.0f)},
    {((char*)"bou_2_c"), 1, 1, FLOAT(16.5f), FLOAT(-1.0f)},
    {((char*)"bou_3_c"), 0, 0, FLOAT(20.0f), FLOAT(-1.0f)},
    {((char*)"bou_4_c"), 1, 1, FLOAT(16.5f), FLOAT(-1.0f)},
    {0},
};

/**
 * Moves one connecting rod (bou_n) in a small circle every frame according to the wheel speed,
 * so the rods move with the wheels.
 */
static EVT_BEGIN(evt_clank_main)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SWITCH(LW(1))
        CASE_EQUAL(0)
        SET_FLOAT_VALUE(LW(11), FLOAT(23.889648f))
        CASE_EQUAL(1)
        SET_FLOAT_VALUE(LW(11), FLOAT(31.139648f))
        CASE_EQUAL(2)
        SET_FLOAT_VALUE(LW(11), FLOAT(55.01953f))
    END_SWITCH
    LOOP(0)
        SWITCH(LW(2))
            CASE_EQUAL(0)
            SET_FLOAT_VALUE(LW(9), GW(0))
            CASE_EQUAL(1)
            SET_FLOAT_VALUE(LW(9), GW(1))
        END_SWITCH
        DIVIDE_FLOAT(LW(9), LW(11))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        SET_FLOAT_VALUE(LW(12), LW(10))
        MULTIPLY_FLOAT(LW(12), LW(4))
        CALL(evt_sub_get_sincos, LW(12), LW(13), LW(14))
        MULTIPLY_FLOAT(LW(13), LW(3))
        MULTIPLY_FLOAT(LW(14), LW(3))
        SUBTRACT_FLOAT(LW(14), LW(3))
        MULTIPLY_FLOAT(LW(14), FLOAT(-1.0f))
        CALL(evt_mapobj_trans, 1, LW(0), LW(14), LW(13), FLOAT(0.0f))
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

/** Starts evt_clank_main for every rod listed in clankDt. */
static EVT_BEGIN(evt_clank)
    SET_INT_READ_ADDR(PTR(clankDt))
    LOOP(0)
        READ_INT4(LW(0), LW(1), LW(2), LW(3))
        READ_INT(LW(4))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(evt_clank_main)
    END_LOOP
    RETURN
EVT_END()

/**
 * US and PAL wrap the two scrolling layers with float compares over a shorter range
 * and move "yama" with the far layer; JP and the demos wrap them with integer compares
 * and move "yama" with the near one.
 */
#if VERSION >= VERSION_US
static EVT_BEGIN(evt_bg)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(11), FLOAT(0.0f))
    LOOP(0)
        SET_FLOAT_VALUE(LW(0), GW(0))
        ADD_FLOAT(LW(10), LW(0))
        IF_FLOAT_GREATER(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(-800.0f))
        END_IF
        IF_FLOAT_LESS(LW(10), FLOAT(-800.0f))
            ADD_FLOAT(LW(10), FLOAT(800.0f))
        END_IF
        ADD_FLOAT(LW(11), LW(0))
        IF_FLOAT_GREATER(LW(11), FLOAT(0.0f))
            ADD_FLOAT(LW(11), FLOAT(-2400.0f))
        END_IF
        IF_FLOAT_LESS(LW(11), FLOAT(-2400.0f))
            ADD_FLOAT(LW(11), FLOAT(2400.0f))
        END_IF
        CALL(evt_mapobj_trans, 1, STRING("jimen"), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING("iwayama"), LW(11), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING("yama"), LW(11), 0, 0)
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()
/**
 * Scrolls the background layers (ground, mountains) sideways every frame by speeds derived from the train speed
 * GW(0), so the scenery flows past the train.
 */
#else
static EVT_BEGIN(evt_bg)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(11), FLOAT(0.0f))
    LOOP(0)
        SET_FLOAT_VALUE(LW(0), GW(0))
        ADD_FLOAT(LW(10), LW(0))
        IF_INT_GREATER(LW(10), FLOAT(1200.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(2400.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(-1200.0f))
            ADD_FLOAT(LW(10), FLOAT(2400.0f))
        END_IF
        ADD_FLOAT(LW(11), LW(0))
        IF_INT_GREATER(LW(11), FLOAT(3600.0f))
            SUBTRACT_FLOAT(LW(11), FLOAT(7200.0f))
        END_IF
        IF_INT_LESS(LW(11), FLOAT(-3600.0f))
            ADD_FLOAT(LW(11), FLOAT(7200.0f))
        END_IF
        CALL(evt_mapobj_trans, 1, STRING("jimen"), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING("yama"), LW(10), 0, 0)
        CALL(evt_mapobj_trans, 1, STRING("iwayama"), LW(11), 0, 0)
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()
#endif

/**
 * Rotates the star objects (hosi_left, hosi_center,
 * hosi_right and the _c copies) every frame by the train speed GW(0).
 */
static EVT_BEGIN(evt_hoshi)
    SET_FLOAT_VALUE(LW(10), FLOAT(0.0f))
    LOOP(0)
        SET_FLOAT_VALUE(LW(9), GW(0))
        DIVIDE_FLOAT(LW(9), FLOAT(30.0f))
        MULTIPLY_FLOAT(LW(9), FLOAT(57.29492f))
        ADD_FLOAT(LW(10), LW(9))
        IF_INT_GREATER(LW(10), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        IF_INT_LESS(LW(10), FLOAT(0.0f))
            ADD_FLOAT(LW(10), FLOAT(360.0f))
        END_IF
        CALL(evt_mapobj_rotate, 0, STRING("hosi_right"), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING("hosi_left"), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING("hosi_center"), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING("hosi_right_c"), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING("hosi_left_c"), LW(10), 0, 0)
        CALL(evt_mapobj_rotate, 0, STRING("hosi_center_c"), LW(10), 0, 0)
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

/**
 * Departure of the train outbound: clears the at-station flags, rings the bell,
 * plays the engine sounds and ramps the wheel speeds GW(0) and GW(1) up to -15 (leftward).
 */
static EVT_BEGIN(hom_10_evt_resha_start)
    // The train starts moving: the station flags are cleared and the bell rings.
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 0)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_POSHLEY), 0)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
    CALL(evt_mapobj_get_position, STRING("ranpu"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TRAIN_BELL1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TRAIN_BELL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        // The engine sounds start and the wheel speeds ramp up to the left (outbound).
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_54_WELCOME_BACK)
            CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1_2"), 0)
        ELSE
            CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1_2_2"), 0)
        END_IF
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1_3"), 0)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
        CALL(evt_sub_intpl_msec_init, 11, 0, -1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(0), FLOAT(-15.0f))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            CALL(evt_sub_get_stopwatch, LW(0), LW(1))
            IF_INT_GREATER(LW(1), 1500)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 0, -1000, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, -1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Departure of the train on the return trip: like hom_10_evt_resha_start
 * but ramps the speeds up to +15 (rightward).
 */
static EVT_BEGIN(hom_10_evt_resha_start2)
    // The train starts moving on the return trip: the station flags are cleared.
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 0)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_POSHLEY), 0)
    SET_VALUE(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
    CALL(evt_mapobj_get_position, STRING("ranpu"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TRAIN_BELL1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(200)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TRAIN_BELL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1_2_3"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE1_3"), 0)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        BEGIN_INLINE_EVENT
            SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
            LOOP(0)
                ADD_FLOAT(LW(0), GW(0))
                CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
        CALL(evt_sub_intpl_msec_init, 11, 0, 1500, 20000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        // The wheel speeds ramp up to the right.
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            CALL(evt_sub_get_stopwatch, LW(0), LW(1))
            IF_INT_GREATER(LW(1), 1500)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, 0, 1000, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        CALL(evt_sub_intpl_msec_init, 11, 1000, 0, 1000)
        LABEL(2)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(1), GW(0))
        ADD_FLOAT(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(2)
        END_IF
        LOOP(0)
            SET_FLOAT_VALUE(GW(1), GW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

/** Puts the train at full outbound speed at once: marks it moving and sets GW(0) and GW(1) to -15. */
static EVT_BEGIN(hom_10_evt_resha_start3)
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(-15.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(-15.0f))
    RETURN
EVT_END()

/** Puts the train at full return speed at once: marks it moving and sets GW(0) and GW(1) to +15. */
static EVT_BEGIN(hom_10_evt_resha_start4)
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(15.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(15.0f))
    RETURN
EVT_END()

/**
 * Arrival braking of the outbound train: plays the stop sounds and slows the wheel speeds to 0,
 * then clears GSWF_TRAIN_MOVING.
 */
static EVT_BEGIN(stop_1)
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2_2"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2_3"), 0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, 3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
    SET_FLOAT_VALUE(LW(2), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 0)
    RETURN
EVT_END()

/** Arrival braking of the return-trip train: like stop_1 with the return-trip sound variants. */
static EVT_BEGIN(stop_2)
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(2), FLOAT(-3000.0f))
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2_2_2"), 0)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        CALL(evt_snd_sfxon, STRING("SFX_STG6_TRAIN_MOVE2_3"), 0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 11, -3000, 0, 10000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    MULTIPLY_FLOAT(LW(0), FLOAT(1.0f))
    CALL(evt_mapobj_trans, 1, STRING("train"), LW(0), 0, 0)
    SUBTRACT_FLOAT(LW(2), LW(0))
    SET_FLOAT_VALUE(GW(0), LW(2))
    SET_FLOAT_VALUE(GW(1), LW(2))
    MULTIPLY_FLOAT(GW(0), FLOAT(-1.0f))
    MULTIPLY_FLOAT(GW(1), FLOAT(-1.0f))
    SET_FLOAT_VALUE(LW(2), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 0)
    RETURN
EVT_END()

/** Stops the train: runs stop_1 or stop_2 depending on the trip direction (GSWF_TRAIN_RETURN_TRIP). */
static EVT_BEGIN(hom_10_evt_resha_stop)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        SPAWN_EVENT(stop_1)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        SPAWN_EVENT(stop_2)
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
            SPAWN_EVENT(stop_1)
        ELSE
            SPAWN_EVENT(stop_2)
        END_IF
    END_IF
    RETURN
EVT_END()

/** Keeps the lamp objects (ranpu, ranpu_c) swinging every frame by the amount from ramp_r while the train is moving. */
static EVT_BEGIN(evt_ramp)
    LOOP(0)
        CALL(ramp_r)
        CALL(evt_mapobj_rotate, 1, STRING("ranpu"), 0, 0, LW(10))
        CALL(evt_mapobj_rotate, 1, STRING("ranpu_c"), 0, 0, LW(10))
        WAIT_FRAMES(1)
        LOOP(0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_MOVING), 1)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

/**
 * Map object groups of the train (pika_*) that hom_10_evt_resha_sub hooks to the TEV callback resha_tev,
 * which adds environment effect 7 (an env.tpl reflection or shine texture) to them; NULL ends the list.
 */
static const char* pika_tbl[] = {
    "pika_1_1", "pika_1_2", "pika_1_3", "pika_1_4", "pika_2",
    "pika_3", "pika_4", "pika_5", "pika_6", "pika_1_1_c",
    "pika_1_2_c", "pika_1_3_c", "pika_1_4_c", "pika_6_c", NULL,
};

/** The shorter list used instead on the map rsh_06_a: the same groups without the *_c ones. */
static const char* pika_tbl_rsh_06[] = {
    "pika_1_1", "pika_1_2", "pika_1_3", "pika_1_4", "pika_2",
    "pika_3", "pika_4", "pika_5", "pika_6", NULL,
};

/**
 * Common start of the train-exterior scenes: marks the train as not moving,
 * zeroes the wheel speeds and spawns the wheel, rod,
 * background and star scripts (plus lamp and sparks on the maps that have them).
 */
static EVT_BEGIN(hom_10_evt_resha_sub)
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 0)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(0.0f))
    SPAWN_EVENT(evt_sharin)
    SPAWN_EVENT(evt_clank)
    SET_VALUE(LF(0), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("hom_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_11"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_12"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("rsh_06_a"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        SPAWN_EVENT(evt_bg)
    END_IF
    SPAWN_EVENT(evt_hoshi)
    SPAWN_EVENT(evt_ramp)
    CALL(evt_map_set_tevcallback, 1, PTR(resha_tev))
    SET_INT_READ_ADDR(PTR(&pika_tbl))
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("rsh_06_a"))
        SET_INT_READ_ADDR(PTR(&pika_tbl_rsh_06))
    END_IF
    LOOP(0)
        READ_INT(LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_TEV_CALLBACK(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_DISPLAY_LIST)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_COLOR_STAGE)
    END_LOOP
    RETURN
EVT_END()

/**
 * Train facing right: runs hom_10_evt_resha_sub and, outside rsh_06_a,
 * hides the rear cars (train_7, train_8) and their couplings.
 */
static EVT_BEGIN(hom_10_evt_resha_right)
    CALL_CHILD(hom_10_evt_resha_sub)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_NOT_EQUAL(LW(0), STRING("rsh_06_a"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("train_7"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("train_8"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu_6"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu_7"), 1)
    END_IF
    RETURN
EVT_END()

/** Train facing left: runs hom_10_evt_resha_sub and hides the front cars (train_1, train_6) and their couplings. */
static EVT_BEGIN(hom_10_evt_resha_left)
    CALL_CHILD(hom_10_evt_resha_sub)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("train_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("train_6"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu_1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu_5"), 1)
    RETURN
EVT_END()

/**
 * Copy of the hom_10 init event (the outside view of the train at the start of the second trip) that this module
 * does not use: the train drives past a fixed camera for about 4 seconds,
 * then the map changes to rsh_02_a (entrance nidome).
 */
static EVT_BEGIN(hom_10_init_evt)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH2"))
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        CALL_CHILD(hom_10_evt_resha_right)
        CALL_CHILD(hom_10_evt_resha_start3)
        SET_VALUE(LW(0), 500)
        SET_VALUE(LW(1), -500)
#if VERSION >= VERSION_JP
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("renketu"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_3"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_4"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("renketu_5"), 1)
#endif
    ELSE
        CALL_CHILD(hom_10_evt_resha_left)
        CALL_CHILD(hom_10_evt_resha_start4)
        SET_VALUE(LW(0), 0)
        SET_VALUE(LW(1), 1000)
        CALL(evt_mapobj_trans, 1, STRING("train"), -1500, 0, 0)
    END_IF
    CALL(evt_cam_letter_box_onoff, 1, 1)
    CALL(evt_cam3d_evt_set, LW(0), 300, 1400, LW(0), 125, 0, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_cam3d_evt_set, LW(1), 300, 1400, LW(1), 125, 0, 8000, 0)
        WAIT_MS(4000)
        CALL(evt_bero_mapchange, STRING("rsh_02_a"), STRING("nidome"))
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Starts the train-exterior effects of the roof map using the train scripts shared with hom_10
 * (hom_10_evt_resha_right: wheels, clanking, train cars shown or hidden),
 * marks the train as moving (GSWF_TRAIN_MOVING, JP and later) and sets the wheel rotation speeds GW(0)
 * and GW(1) to -15.
 */
EVT_BEGIN(evt_resha_init)
    CALL_CHILD(hom_10_evt_resha_right)
#if VERSION >= VERSION_JP
    SET_VALUE(GSWF(GSWF_TRAIN_MOVING), 1)
#endif
    SET_VALUE(GW(0), FLOAT(-15.0f))
    SET_VALUE(GW(1), FLOAT(-15.0f))
    RETURN
EVT_END()

/** Doors and exits of rsh_06 variant a: w_bero to rsh_05_a. */
static BeroEntry bero_data_a[] = {
    {
        ((char*)"w_bero"), // hitName
        0, // type
        8, // sfxId
        BERO_DIR_E, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_05_a", // nextMapName
        ((char*)"w_bero"), // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Sets up the roof boss: registers the Smorg and passenger NPC models, the giant Smorg model (base),
 * the swarm effect for 700 sprites and the voice sound, turns the swarm on and runs the giant Smorg cutscene.
 */
static EVT_BEGIN(evt_moamoa_init)
    CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
    CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
    CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("kinopio"), STRING("c_kinodebu"))
    CALL(evt_npc_entry, STRING("cook"), STRING("c_puku_c"))
    CALL(evt_npc_entry, STRING("powan"), STRING("c_powan"))
    CALL(evt_npc_entry, STRING("sarary"), STRING("c_smoko"))
    CALL(evt_npc_entry, STRING("rose"), STRING("c_rose"))
    CALL(evt_npc_entry, STRING("papa"), STRING("c_papab"))
    CALL(evt_npc_entry, STRING("mama"), STRING("c_mamab"))
    CALL(evt_npc_entry, STRING("konari"), STRING("c_konari"))
    CALL(evt_npc_set_position, STRING("kinopio"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("cook"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("powan"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("sarary"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("rose"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("papa"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("mama"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("konari"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("kinopio"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("cook"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("powan"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("sarary"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("rose"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("papa"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("mama"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("konari"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_snd_sfxon, STRING("SFX_STG6_MOAMOA_VOICE2"), GW(2))
    CALL(evt_npc_entry, STRING("base"), STRING("c_g_moamoa"))
    CALL(evt_npc_set_position, STRING("base"), 0, -1000, 0)
    CALL(evt_ext_entry, 700, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    BEGIN_INLINE_EVENT
        LABEL(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), -300)
            WAIT_FRAMES(1)
            GOTO(0)
        END_IF
        CALL_CHILD(evt_great_moamoa)
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Cutscene and boss fight with the giant Smorg (moamoa) on the roof of the train:
 * the swarm gathers and merges (evt_moamoa_fusion) into a giant body with the passengers' faces (kinds),
 * the camera sweeps over it, Mario and the partner react (stg6_rsh_244 to 246),
 * the battle starts with the "base" NPC and, after the fight, the Smorg falls apart (evt_moamoa_blow),
 * the story advances to STORY_STG6_48_SMORG_MIASMA and the map changes to rsh_01_a.
 */
EVT_BEGIN(evt_great_moamoa)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_moamoa_flag_onoff, 1, 8)
    CALL(evt_moamoa_flag_onoff, 1, 4)
    // The swarm gathers and merges into the giant Smorg.
    CALL(evt_msg_print, 0, STRING("stg6_rsh_244"), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("group339"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("group340"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("group341"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("senro"), 1)
    CALL(evt_npc_set_position, STRING("base"), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING("base"), 0)
    CALL(evt_npc_set_anim, STRING("base"), STRING("Z_1"))
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_snd_sfxon, STRING("SFX_STG6_MOA_TOGETHER_MOVE1"), GW(2))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, STRING("eff0"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff_fukidashi, 3, STRING("eff1"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 90, 200, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
        WAIT_MS(300)
        CALL(evt_cam3d_evt_set, 10, 349, 516, 10, 253, -25, 3000, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(15)
            CALL(evt_snd_sfxon, STRING("SFX_STG6_MOA_TOGETHER_MOVE2"), 0)
            WAIT_MS(500)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_moamoa_fusion)
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_snd_sfxon, STRING("SFX_STG6_MOAMOA_VOICE2"), GW(2))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("group166"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("group339"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("group340"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("group341"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("senro"), 1)
    WAIT_MS(2000)
    CALL(evt_moamoa_kind_onoff, 1, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("base"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(800)
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("base"), STRING("H_1"))
    CALL(npc_anim_wait)
    CALL(evt_cam3d_evt_set, 10, 335, 369, 10, 265, -25, 1000, 11)
    CALL(evt_moamoa_kind_onoff, 1, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("base"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("base"), STRING("U_1"))
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1700)
        CALL(evt_npc_get_position, STRING("base"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG3"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_cam3d_evt_set, 10, 300, 450, 10, 300, -25, 1000, 11)
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("base"), STRING("H_2"))
    CALL(npc_anim_wait)
    CALL(evt_npc_set_anim, STRING("base"), STRING("S_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pos, -160, 215, 0)
    CALL(evt_party_set_pos, 0, -200, 215, -10)
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 90, 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    CALL(evt_mario_set_pose, STRING("M_I_Y"))
    CALL(evt_cam3d_evt_set, -180, 308, 270, -180, 255, -25, 0, 11)
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    // Mario and his partner react.
    CALL(evt_msg_print_party, STRING("stg6_rsh_245"))
    WAIT_MS(300)
    CALL(evt_party_run, 0)
    CALL(evt_cam3d_evt_set, 10, 498, 467, 10, 410, -25, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_246_02"), 0, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_246_03"), 0, 0)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 1000, 20, 841, -50, 200, -66, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -440, 230, 180, 5, 300, -36, 4000, 11)
    WAIT_MS(4000)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("base"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_LEG4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING("base"), STRING("P_1"))
    CALL(npc_anim_wait)
    CALL(evt_npc_set_anim, STRING("base"), STRING("S_3"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_246_01"), 0, 0)
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -100, 488, 1370, -100, 245, -8, 4000, 11)
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, GW(2))
    CALL(evt_npc_set_battle_info, STRING("base"), 1)
    // The battle with the giant Smorg starts.
    CALL(evt_npc_battle_start, STRING("base"))
    CALL(evt_npc_wait_battle_end)
    CALL(evt_cam3d_evt_set, -50, 355, 534, -50, 260, -8, 0, 11)
    CALL(evt_npc_set_anim, STRING("base"), STRING("Z_1"))
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_flag_onoff, 0, STRING("kinopio"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("cook"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("powan"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("sarary"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("rose"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("papa"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("mama"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 0, STRING("konari"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_set_position, STRING("kinopio"), 0, 215, 0)
    CALL(evt_npc_set_position, STRING("cook"), 0, 215, 1)
    CALL(evt_npc_set_position, STRING("sarary"), 0, 215, 2)
    CALL(evt_npc_set_position, STRING("rose"), 0, 215, 3)
    CALL(evt_npc_set_position, STRING("papa"), 0, 215, 4)
    CALL(evt_npc_set_position, STRING("mama"), 0, 215, 5)
    CALL(evt_npc_set_position, STRING("konari"), 0, 215, 6)
    CALL(evt_npc_set_position, STRING("powan"), 20, 215, 7)
    CALL(evt_npc_set_ry, STRING("kinopio"), 270)
    CALL(evt_npc_set_ry, STRING("cook"), 270)
    CALL(evt_npc_set_ry, STRING("sarary"), 270)
    CALL(evt_npc_set_ry, STRING("rose"), 270)
    CALL(evt_npc_set_ry, STRING("papa"), 270)
    CALL(evt_npc_set_ry, STRING("mama"), 270)
    CALL(evt_npc_set_ry, STRING("konari"), 270)
    CALL(evt_npc_set_ry, STRING("powan"), 270)
    CALL(evt_npc_set_anim, STRING("kinopio"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("cook"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("sarary"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("rose"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("papa"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("mama"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("konari"), STRING("Z_1"))
    CALL(evt_npc_set_anim, STRING("powan"), STRING("Z_1"))
    CALL(evt_moamoa_kind_onoff, 0, 0)
    // After the fight the Smorg falls apart.
    CALL(evt_msg_print, 0, STRING("stg6_rsh_247"), 0, STRING("base"))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("base"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_G_ESCAPE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_moamoa_blow)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, -150, 485, 1469, -150, 225, -8, 4000, 11)
    WAIT_MS(4000)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING("powan"))
            WAIT_MS(1500)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_reverse_ry, STRING("konari"))
            WAIT_MS(1000)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(2000)
    // The story advances and the map changes to rsh_01_a.
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_48_SMORG_MIASMA)
    CALL(evt_bero_mapchange, STRING("rsh_01_a"), STRING("w_bero"))
    RETURN
EVT_END()

/** Animation names the Smorg debug leftover cycles through when a button is pressed. */
const char* pose_name[] = {
    "Z_1", "H_1", "S_1", "U_1", "H_2", "S_2", "P_1",
    "S_3",
};

/**
 * Debug leftover run when map events are skipped (GLOBAL_FLAG_SKIP_MAP_EVENTS):
 * spawns all the Smorg models, the swarm and the pre-merged giant body
 * so it can be inspected without the cutscene.
 */
EVT_BEGIN(moamoa_debug)
    CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
    CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
    CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("kinopio"), STRING("c_kinodebu"))
    CALL(evt_npc_entry, STRING("cook"), STRING("c_puku_c"))
    CALL(evt_npc_entry, STRING("powan"), STRING("c_powan"))
    CALL(evt_npc_entry, STRING("sarary"), STRING("c_smoko"))
    CALL(evt_npc_entry, STRING("rose"), STRING("c_rose"))
    CALL(evt_npc_entry, STRING("papa"), STRING("c_papab"))
    CALL(evt_npc_entry, STRING("mama"), STRING("c_mamab"))
    CALL(evt_npc_entry, STRING("konari"), STRING("c_konari"))
    CALL(evt_npc_set_position, STRING("kinopio"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("cook"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("powan"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("sarary"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("rose"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("papa"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("mama"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("konari"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("kinopio"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("cook"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("powan"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("sarary"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("rose"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("papa"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("mama"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_flag_onoff, 1, STRING("konari"), NPC_FLAG_NO_DISPLAY)
    CALL(evt_npc_entry, STRING("base"), STRING("c_g_moamoa"))
    CALL(evt_npc_set_position, STRING("base"), 0, -1000, 0)
    CALL(evt_ext_entry, 700, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    CALL(evt_moamoa_flag_onoff, 1, 4)
    CALL(evt_moamoa_fusion_debug)
    CALL(evt_npc_set_position, STRING("base"), 10, 190, 0)
    CALL(evt_npc_pera_onoff, STRING("base"), 0)
    CALL(evt_npc_set_anim, STRING("base"), STRING("S_2"))
    CALL(evt_npc_set_scale, STRING("base"), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(0)
            CALL(evt_key_get_buttontrg, 0, LW(10))
            IF_BITS_SET(LW(10), 256)
                ADD(LW(0), 1)
                MODULO(LW(0), 8)
                SET_VALUE(LW(1), LW(0))
                ADD(LW(1), 1)
                SET_INT_READ_ADDR(PTR(&pose_name))
                LOOP(LW(1))
                    READ_INT(LW(2))
                END_LOOP
                CALL(evt_npc_set_anim, STRING("base"), LW(2))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Shared map init for rsh_06 on the first trip:
 * starts the train-exterior scene and the music and ambience for the story stage.
 */
EVT_BEGIN(rsh_06_init_evt)
    CALL_CHILD(evt_resha_init)
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
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH2"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init script of rsh_06_a (first trip): places Mario at (-500, 250, 0) on the roof,
 * sets the door back to rsh_05, runs the shared init and, before STORY_STG6_48_SMORG_MIASMA,
 * sets up the swarm and the giant Smorg scenes (or the debug scene when map events are skipped).
 */
EVT_BEGIN(rsh_06_a_init_evt)
    CALL(evt_mario_set_pos, -500, 250, 0)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_06_init_evt)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SKIP_MAP_EVENTS)
        SPAWN_EVENT(moamoa_debug)
        RETURN
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_48_SMORG_MIASMA)
        CALL_CHILD(evt_moamoa_init)
    END_IF
    RETURN
EVT_END()

/**
 * Shared map init for rsh_06 on the second visit:
 * train-exterior scene plus the music for the station the train has reached.
 */
EVT_BEGIN(rsh_06_init_evt_nidome)
    CALL_CHILD(evt_resha_init)
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
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH2"))
        END_IF
    END_IF
    RETURN
EVT_END()

/** Init script of rsh_06_a on the second visit: door back to rsh_05 plus rsh_06_init_evt_nidome. */
EVT_BEGIN(rsh_06_a_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_06_init_evt_nidome)
    RETURN
EVT_END()

/**
 * Script helper used by evt_ramp: writes into LW(10) a swaying angle,
 * 1.8 times the absolute value of GW(0) times sin(retraceCount / 15),
 * which the script applies to the lamp objects (ranpu, ranpu_c) so they swing with the train.
 */
static s32 ramp_r(EventEntry* event, BOOL isFirstCall) {
    f32 amp = __fabsf(evtGetFloat(event, GW(0)));
    f32 wave = sin(gp->retraceCount / 15.0f);

    evtSetFloat(event, LW(10), 1.8f * amp * wave);
    return EVT_RETURN_DONE;
}
/**
 * Map TEV callback 1, installed by the map init with evt_map_set_tevcallback: adds environment effect type 7
 * (envAddTev) to the material of each map object that uses that callback slot.
 */
static void resha_tev(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
/**
 * Script helper: blocks until the current animation of the base NPC (the giant Smorg model)
 * has played through once.
 */
static s32 npc_anim_wait(EventEntry* event, BOOL isFirstCall) {
    NpcEntry* npc = npcNameToPtr((char*)"base");

    if (animPoseGetLoopTimes(npc->poseId) >= 1.0f) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
