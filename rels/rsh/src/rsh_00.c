// rsh_00 (列車, Excess Express): the driver's cab: driver NPC, controls and schedule board, a Smorg (moamoa) window
// scene; door to rsh_01.

// defer_codegen: the original emits this unit's functions in deferred order (checked by removing it).
#pragma defer_codegen on
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "string.h"
#include "dolphin/os.h"
#include "mario/mariost.h"
#include "memory.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "system.h"
#include "driver/dispdrv.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_bero.h"
#include "rsh.h"
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
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "libc_decls.h"

typedef struct MoamoaScene {
    u16 flags;
    s16 state;
    s16 timer;
    Vec pos;
    f32 angle;
    s16 pose;
    u64 startTime;
} MoamoaScene;
typedef struct MoamoaSceneWork {
    s32 flags;
    s32 count;
    MoamoaScene* moa;
    s32 numDefs;
    MoamoaPoseDef defs[32];
} MoamoaSceneWork;

static MoamoaSceneWork* wp;
static f32 randf(f32 min, f32 max);
static void moamoa_pose_init(void);
static void moamoa_pose_change(MoamoaScene* moa, const char* model, const char* anim);
static void moamoa_pose_main(void);
static void ext_disp(CameraId camera, void* param);

static void moamoa_dispent(void);
static void moamoa_main(void);
static void moamoa_init(void);

MoamoaData moamoa_data[81];
static BeroEntry bero_data_a[2];
static BeroEntry bero_data_b[2];
static BeroEntry bero_data_c[2];
extern EvtWord evt_handle[];
extern EvtWord regu_unten[];
static NpcSetupInfo npc_data[2];
static const char* access_tbl[5];
extern EvtWord rsh_00_init_evt[];
static const char* window_tbl[5];
extern EvtWord rsh_00_init_evt_nidome[];

MoamoaData moamoa_data[] = {
    {"c_n_moa_a", "S_1", 0.0f},
    {"c_n_moa_a", "S_1", 1.0f},
    {"c_n_moa_a", "S_1", 2.0f},
    {"c_n_moa_a", "S_1", 3.0f},
    {"c_n_moa_a", "S_1", 4.0f},
    {"c_n_moa_a", "S_1", 5.0f},
    {"c_n_moa_a", "S_1", 6.0f},
    {"c_n_moa_a", "S_1", 7.0f},
    {"c_n_moa_a", "S_1", 8.0f},
    {"c_n_moa_a", "S_1", 9.0f},
    {"c_n_moa_a", "S_1", 10.0f},
    {"c_n_moa_a", "S_1", 11.0f},
    {"c_n_moa_a", "S_1", 12.0f},
    {"c_n_moa_a", "S_1", 13.0f},
    {"c_n_moa_a", "S_1", 14.0f},
    {"c_n_moa_a", "S_1", 15.0f},
    {"c_n_moa_a", "S_1", 16.0f},
    {"c_n_moa_a", "S_1", 17.0f},
    {"c_n_moa_a", "S_1", 18.0f},
    {"c_n_moa_a", "S_1", 19.0f},
    {"c_n_moa_a", "S_1", 20.0f},
    {"c_n_moa_a", "S_1", 21.0f},
    {"c_n_moa_a", "S_1", 22.0f},
    {"c_n_moa_a", "S_1", 23.0f},
    {"c_n_moa_a", "S_1", 24.0f},
    {"c_n_moa_a", "S_1", 25.0f},
    {"c_n_moa_a", "S_1", 26.0f},
    {"c_n_moa_a", "S_1", 27.0f},
    {"c_n_moa_a", "S_1", 28.0f},
    {"c_n_moa_a", "S_1", 29.0f},
    {"c_n_moa_a", "S_1", 30.0f},
    {"c_n_moa_a", "S_1", 31.0f},
    {"c_n_moa_a", "S_1", 32.0f},
    {"c_n_moa_a", "S_1", 33.0f},
    {"c_n_moa_a", "S_1", 34.0f},
    {"c_n_moa_a", "S_1", 35.0f},
    {"c_n_moa_a", "S_1", 36.0f},
    {"c_n_moa_a", "S_1", 37.0f},
    {"c_n_moa_a", "S_1", 38.0f},
    {"c_n_moa_a", "S_1", 39.0f},
    {"c_n_moa_b", "S_1", 0.0f},
    {"c_n_moa_b", "S_1", 1.0f},
    {"c_n_moa_b", "S_1", 2.0f},
    {"c_n_moa_b", "S_1", 3.0f},
    {"c_n_moa_b", "S_1", 4.0f},
    {"c_n_moa_b", "S_1", 5.0f},
    {"c_n_moa_b", "S_1", 6.0f},
    {"c_n_moa_b", "S_1", 7.0f},
    {"c_n_moa_b", "S_1", 8.0f},
    {"c_n_moa_b", "S_1", 9.0f},
    {"c_n_moa_b", "S_1", 10.0f},
    {"c_n_moa_b", "S_1", 11.0f},
    {"c_n_moa_b", "S_1", 12.0f},
    {"c_n_moa_b", "S_1", 13.0f},
    {"c_n_moa_b", "S_1", 14.0f},
    {"c_n_moa_b", "S_1", 15.0f},
    {"c_n_moa_b", "S_1", 16.0f},
    {"c_n_moa_b", "S_1", 17.0f},
    {"c_n_moa_b", "S_1", 18.0f},
    {"c_n_moa_b", "S_1", 19.0f},
    {"c_n_moa_b", "S_1", 20.0f},
    {"c_n_moa_b", "S_1", 21.0f},
    {"c_n_moa_b", "S_1", 22.0f},
    {"c_n_moa_b", "S_1", 23.0f},
    {"c_n_moa_b", "S_1", 24.0f},
    {"c_n_moa_b", "S_1", 25.0f},
    {"c_n_moa_b", "S_1", 26.0f},
    {"c_n_moa_b", "S_1", 27.0f},
    {"c_n_moa_b", "S_1", 28.0f},
    {"c_n_moa_b", "S_1", 29.0f},
    {"c_n_moa_b", "S_1", 30.0f},
    {"c_n_moa_b", "S_1", 31.0f},
    {"c_n_moa_b", "S_1", 32.0f},
    {"c_n_moa_b", "S_1", 33.0f},
    {"c_n_moa_b", "S_1", 34.0f},
    {"c_n_moa_b", "S_1", 35.0f},
    {"c_n_moa_b", "S_1", 36.0f},
    {"c_n_moa_b", "S_1", 37.0f},
    {"c_n_moa_b", "S_1", 38.0f},
    {"c_n_moa_b", "S_1", 39.0f},
    {0},
};

// dont_inline: MWCC would inline this function into its callers; the original calls it (checked by removing it).
#pragma dont_inline on
/**
 * Builds the work area's animation table (wp->defs) from moamoa_data:
 * consecutive rows with the same model and animation name become one MoamoaPoseDef (first texture frame,
 * frame count, speed, looping unless the animation name starts with J). Kept out of line to match the original.
 */
static void moamoa_pose_init(void) {
    MoamoaData* data = moamoa_data;
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
 * Per-frame update of every Smorg (moamoa) sprite:
 * converts the time since the pose started into a texture frame index (looping or clamped at the end)
 * and stores it in the sprite's ExtdrvPose.
 */
static void moamoa_pose_main(void) {
    f32 t;
    u64 now;
    s32 i;
    ExtdrvPose* pose;
    MoamoaScene* moa;
    MoamoaPoseDef* def;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = 60.0f * OSTicksToMilliseconds(now - moa->startTime) / 1000.0f / def->speed;

        if (t >= 1.0f) {
            if (def->loop) {
                moa->startTime = now;
                t = 0.0f;
            } else {
                t = 1.0f;
            }
        }
        pose->texId = def->start + (s32)((def->count - 1) * t);
    }
}

/**
 * Switches one Smorg sprite to the named model/animation pair from the table (the b model is forced when flag 2
 * is set) and restarts its animation clock; does nothing if it is already playing it.
 */
static void moamoa_pose_change(MoamoaScene* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 2) {
        model = "c_n_moa_b";
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}

/** Returns a random float between min and max using rand(). */
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

/**
 * Init callback of the Smorg window effect (evt_ext_entry):
 * allocates the work area, then places every sprite at a random spot just outside the cab window
 * or the carriage (rsh_00 versus rsh_03 versus other cars), hidden below the floor at y = -1000,
 * with a yaw for the sprites that will climb in from the side.
 */
static void moamoa_init(void) {
    s32 i;
    ExtdrvPose* pose;
    MoamoaScene* moa;
    f32 x, y, z;

    wp = _mapAlloc(sizeof(MoamoaSceneWork));
    memset(wp, 0, sizeof(MoamoaSceneWork));
    wp->count = extGetPoseNum();
    wp->moa = _mapAlloc(wp->count * sizeof(MoamoaScene));
    memset(wp->moa, 0, wp->count * sizeof(MoamoaScene));
    moamoa_pose_init();
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        PSMTXIdentity(*pose->mtx);
        pose->flags |= 5;
        moa->flags = 0;
        moa->state = 0;
        moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        if (!strncmp(gp->currentMapName, "rsh_00", 6)) {
            x = randf(-200.0f, 400.0f);
            if (x > 257.0f) {
                x = randf(257.0f, 262.0f);
            }
            y = randf(20.0f, 100.0f);
            if (x < 185.0f) {
                z = randf(-160.0f, -165.0f);
            } else if (x < 257.0f) {
#if VERSION >= VERSION_US
                z = 0.8f * (x - 185.0f) + -160.0f;
                z += 50.0f;
#else
                z = 0.8f * (x - 185.0f) + -160.0f;
#endif
            } else {
#if VERSION >= VERSION_US
                z = randf(-90.0f, -20.0f);
                z += 50.0f;
#else
                z = randf(-90.0f, -20.0f);
#endif
            }
            {
                Vec pos = {0.0f, 0.0f, 0.0f};

                pos.x = x;
                pos.y = y;
                pos.z = z - 100.0f;
                moa->pos = pos;
            }
            (*pose->mtx)[0][3] = 0.0f;
            (*pose->mtx)[1][3] = -1000.0f;
            (*pose->mtx)[2][3] = 0.0f;
            if (!(x < 185.0f)) {
                if (x < 257.0f) {
                    Mtx m;
                    PSMTXRotRad(m, 'y', -0.7853982f);
                    PSMTXConcat(*pose->mtx, m, *pose->mtx);
                    moa->flags |= 1;
                } else {
                    Mtx m;
                    PSMTXRotRad(m, 'y', 1.5707964f);
                    PSMTXConcat(*pose->mtx, m, *pose->mtx);
                    moa->flags |= 1;
                }
            }
        } else {
            if (!strncmp(gp->currentMapName, "rsh_03", 6)) {
                x = randf(-500.0f, 500.0f);
                y = randf(20.0f, 100.0f) - 10.0f;
                z = randf(-170.0f, -180.0f);
                z -= 100.0f;
            } else {
                x = randf(-350.0f, 350.0f);
                y = randf(20.0f, 100.0f);
                z = randf(-290.0f, -300.0f);
            }
            {
                Vec pos = {0.0f, 0.0f, 0.0f};

                pos.x = x;
                pos.y = y;
                pos.z = z;
                moa->pos = pos;
            }
            (*pose->mtx)[0][3] = 0.0f;
            (*pose->mtx)[1][3] = -1000.0f;
            (*pose->mtx)[2][3] = 0.0f;
        }
    }
}

/**
 * Draw callback of the Smorg sprite effect: loads the ext driver's render mode, vertices,
 * textures and TEV setup and draws all sprites.
 */
static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

/**
 * Per-frame callback of the Smorg effect.
 * Steps each sprite through its state (0 idle, 1 pick a random delay, 2 wait it out,
 * 3 pop up from below the window along a random angle over 20 frames, 4 stay at its spot), clamps z to 45,
 * then advances the animations.
 */
static void moamoa_main(void) {
    s32 i;
    ExtdrvPose* pose;
    MoamoaScene* moa;
    f32 r;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        switch (moa->state) {
            case 0:
                break;
            case 1:
                moa->timer = rand() % 60;
                moa->state++;
                break;
            case 2:
                if (--moa->timer > 0) {
                    break;
                }
                moa->state++;
                moa->angle = randf(0.0f, 6.283184f);
                break;
            case 3:
                if (moa->timer < 20) {
                    if (!(moa->flags & 1)) {
                        r = intplGetValue(2, 50.0f, 0.0f, ++moa->timer, 20);
                        (*pose->mtx)[0][3] = moa->pos.x + r * (f32)sin(moa->angle);
                        (*pose->mtx)[1][3] = moa->pos.y - r * (f32)cos(moa->angle);
                        (*pose->mtx)[2][3] = moa->pos.z;
                    } else {
                        r = intplGetValue(2, 50.0f, 0.0f, ++moa->timer, 20);
                        (*pose->mtx)[0][3] = moa->pos.x;
                        (*pose->mtx)[1][3] = moa->pos.y - r * (f32)cos(moa->angle);
                        (*pose->mtx)[2][3] = moa->pos.z;
                    }
                } else {
                    moa->state++;
                }
                break;
            case 4:
                (*pose->mtx)[0][3] = moa->pos.x;
                (*pose->mtx)[1][3] = moa->pos.y;
                (*pose->mtx)[2][3] = moa->pos.z;
                break;
        }
        if ((*pose->mtx)[2][3] > 45.0f) {
            (*pose->mtx)[2][3] = 45.0f;
        }
    }
    moamoa_pose_main();
}

/** Registers ext_disp with the display list on the 3D camera each frame. */
static void moamoa_dispent(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
}

/**
 * Script helper: places Smorg sprite number args[0] at (args[1], args[2], args[3])
 * and puts it straight into the pop-up state (3); the first time it also turns the sprite to face sideways.
 */
static USER_FUNC(evt_moamoa_set_one) {
    EvtWord* args = event->args;
    MoamoaScene* moa;
    s32 idx = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    Mtx m;
    ExtdrvPose* pose = extGetPosePtr();
    moa = wp->moa;
    moa[idx].state = 3;
    moa[idx].pos = (Vec){x, y, z};
    if (!(moa[idx].flags & 1)) {
        PSMTXRotRad(m, 'y', 1.5707964f);
        PSMTXConcat(*pose[idx].mtx, m, *pose[idx].mtx);
        moa[idx].flags |= 1;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: forces every Smorg sprite into the state args[0] (1 starts the random appear sequence,
 * 4 shows them all at their spots).
 */
static USER_FUNC(evt_moamoa_set_seq_all) {
    s32 seq = evtGetValue(event, event->args[0]);
    s32 i;
    MoamoaScene* moa;

    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        moa->state = seq;
    }
    return EVT_RETURN_DONE;
}

/**
 * Cutscene in the driver's cab on day 3 (the story is before STORY_STG6_46_ENGINEER):
 * the music fades, Mario and the partner walk up to the driver, who speaks (stg6_rsh_231, 232);
 * Smorgs (moamoa) pop up at the window with the danger music, the story advances to STORY_STG6_46_ENGINEER,
 * the camera shakes, Mario is startled, the driver panics (stg6_rsh_233),
 * the partner reacts (stg6_rsh_234_x) and the driver ends with stg6_rsh_235_00.
 */
static EVT_BEGIN(evt_moamoa)
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 120)
    CALL(evt_cam3d_evt_set, -70, 113, 373, 126, 38, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 1, STRING("運転手"), NPC_FLAG_INTANGIBLE)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 85, -110, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 115, -110, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 90, 200, 0)
    CALL(evt_set_dir_to_target, STRING("運転手"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_231"), 0, STRING("me"))
    CALL(evt_npc_flag_onoff, 0, STRING("運転手"), NPC_FLAG_INTANGIBLE)
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_MOAMOA_VOICE1"), 265, 25, -145, 0)
    CALL(evt_moamoa_set_one, 0, 265, 25, -145)
    CALL(evt_moamoa_set_one, 1, 265, 35, -230)
    WAIT_MS(1000)
    CALL(evt_npc_reverse_ry, STRING("me"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_232"), 0, STRING("me"))
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SURPRISED1"))
        WAIT_MS(2000)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING("SFX_STG6_MOAMOA_VOICE2"), LW(10))
        WAIT_MS(1000)
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_moamoa_set_seq_all, 1)
    WAIT_MS(500)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_46_ENGINEER)
    LOOP(3)
        CALL(evt_cam3d_evt_set, -2, 86, 230, 126, 38, -13, 350, 11)
        WAIT_MS(350)
        CALL(evt_cam3d_evt_set, -70, 113, 373, 126, 38, -13, 350, 11)
        WAIT_MS(350)
    END_LOOP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2_3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING("a"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING("b"), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_set_anim, STRING("me"), STRING("B_1"))
    CALL(evt_mario_set_pose, STRING("M_I_N"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("T_2"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_233"), 0, STRING("me"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("B_2"))
    CALL(evt_cam3d_evt_set, -2, 86, 230, 126, 38, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_0"), 0, STRING("party"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_1"), 0, STRING("party"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_2"), 0, STRING("party"))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_3"), 0, STRING("party"))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_4"), 0, STRING("party"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_5"), 0, STRING("party"))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_234_6"), 0, STRING("party"))
    END_SWITCH
    CALL(evt_party_run, 0)
    CALL(evt_snd_sfxon, STRING("SFX_STG6_MOAMOA_VOICE2"), LW(10))
    CALL(evt_snd_sfx_vol, LW(10), 88)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_235_00"), 0, STRING("me"))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    RETURN
EVT_END()

/**
 * Called when the cab map loads while the engineer scene is under way (STORY_STG6_46_ENGINEER to
 * STORY_STG6_47_ESCAPING_THE_SMORGS): plays the Smorg voice,
 * registers the two Smorg NPC models and the sprite effect, and shows all Smorgs at their window spots.
 */
EVT_BEGIN(evt_rsh_moamoa_on_window)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_snd_sfxon, STRING("SFX_STG6_MOAMOA_VOICE2"), LW(10))
        CALL(evt_snd_sfx_vol, LW(10), 88)
        CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
        CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
        CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
        CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
        CALL(evt_ext_entry, 1000, PTR(moamoa_data), PTR(moamoa_init), PTR(moamoa_main), PTR(moamoa_dispent))
        CALL(evt_moamoa_set_seq_all, 4)
    END_SWITCH
    RETURN
EVT_END()

static BeroEntry bero_data_a[] = {
    {
        "w_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {0},
};

static BeroEntry bero_data_b[] = {
    {
        "w_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_b", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {0},
};

static BeroEntry bero_data_c[] = {
    {
        "w_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_c", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {0},
};

/**
 * Animates the cab's handles while the story is between the engineer stage and Poshley Heights:
 * spins handoru_1 and handoru_2 in opposite directions and slides handoru_3 back and forth,
 * driving the shaking controls during the Smorg attack.
 */
EVT_BEGIN(evt_handle)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_46_ENGINEER)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_49_POSHLEY_HEIGHTS)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(0)
            ADD(LW(0), 10)
            MODULO(LW(0), 360)
            CALL(evt_mapobj_rotate, 1, STRING("handoru_1"), 0, LW(0), 0)
            SET_VALUE(LW(1), LW(0))
            MULTIPLY(LW(1), -1)
            CALL(evt_mapobj_rotate, 1, STRING("handoru_2"), 0, LW(1), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 0, -40, 300)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_trans, 1, STRING("handoru_3"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, -40, 0, 300)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_trans, 1, STRING("handoru_3"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Regular (idle) event of the driver NPC: every one to two seconds it picks one of three handles at random
 * and eases it to a new random angle or position, so the driver seems to steer.
 * It does nothing during the stages where the train is stopped or the driver is busy.
 */
EVT_BEGIN(regu_unten)
    SET_VALUE(LW(2), 0)
    SET_VALUE(LW(3), 0)
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_27_RIVERSIDE_STATION)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_43_CONDUCTOR_APPEARS)
                RETURN
            END_IF
        END_IF
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_46_ENGINEER)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_54_WELCOME_BACK)
                RETURN
            END_IF
        END_IF
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_57_A_MAIL_FROM_PEACH)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 1)
                RETURN
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 1)
                RETURN
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 1)
                RETURN
            END_IF
        END_IF
        CALL(evt_sub_random, 300, LW(10))
        SWITCH(LW(10))
            CASE_LESS(100)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
            END_IF
            SET_VALUE(LW(2), LW(3))
            CALL(evt_sub_random, 135, LW(10))
            SUBTRACT(LW(10), 45)
            SET_VALUE(LW(3), LW(10))
            CALL(evt_sub_intpl_msec_init, 11, LW(2), LW(3), 1000)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("handoru_1"), 0, LW(0), 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
            CASE_LESS(200)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
            END_IF
            SET_VALUE(LW(4), LW(5))
            CALL(evt_sub_random, 40, LW(10))
            MULTIPLY(LW(10), -1)
            SET_VALUE(LW(5), LW(10))
            CALL(evt_sub_intpl_msec_init, 11, LW(4), LW(5), 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_trans, 1, STRING("handoru_3"), LW(0), 0, 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CASE_DEFAULT
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
            END_IF
            SET_VALUE(LW(6), LW(7))
            CALL(evt_sub_random, 135, LW(10))
            SUBTRACT(LW(10), 90)
            SET_VALUE(LW(7), LW(10))
            CALL(evt_sub_intpl_msec_init, 11, LW(6), LW(7), 1000)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_mapobj_rotate, 1, STRING("handoru_2"), 0, LW(0), 0)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(2)
            END_IF
        END_SWITCH
        CALL(evt_sub_random, 2, LW(10))
        ADD(LW(10), 1)
        MULTIPLY(LW(10), 1000)
        WAIT_MS(LW(10))
    END_LOOP
    RETURN
EVT_END()

/**
 * Init event of the driver: during the Smorg stages (STORY_STG6_46_ENGINEER to
 * STORY_STG6_47_ESCAPING_THE_SMORGS) turns on his move and talk animations and puts him in the B_2 panic pose.
 */
static EVT_BEGIN(init_unten)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_set_anim, STRING("me"), STRING("B_2"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the driver (unten).
 * Picks his line by story stage: the greeting that alternates,
 * the autograph request (at STORY_STG6_10 to 11 he signs and gives Mario the Autograph with the item-get
 * fanfare, STORY_STG6_11_OBTAIN_AUTOGRAPH), hints for each later stage,
 * the Smorg scene (evt_moamoa) before STORY_STG6_46_ENGINEER, and after the story a line for where the train is.
 */
static EVT_BEGIN(talk_unten)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        IF_INT_EQUAL(LSWF(1), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_00"), 0, 0)
            SET_VALUE(LSWF(1), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_01"), 0, 0)
            SET_VALUE(LSWF(1), 0)
        END_IF
        CASE_LESS(STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_01_01"), 0, 0)
        CASE_LESS(STORY_STG6_11_OBTAIN_AUTOGRAPH)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_TALK_ANIM)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_108"), 0, 0)
#else
        CALL(evt_msg_print, 0, STRING("stg6_rsh_108"), 0, STRING("me"))
#endif
        CALL(evt_npc_set_anim, STRING("me"), STRING("A_1"))
        WAIT_MS(500)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_DRIVER_SIGN1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_npc_set_anim, STRING("me"), STRING("A_2"))
        WAIT_MS(2000)
        CALL(evt_npc_set_anim, STRING("me"), STRING("A_3"))
        WAIT_MS(500)
        CALL(evt_item_entry, STRING("sign"), ITEM_AUTOGRAPH, 0, 0, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
        CALL(evt_item_get_item, STRING("sign"))
        CALL(evt_item_get_item_end_wait, STRING("sign"))
        CALL(evt_npc_set_anim, STRING("me"), STRING("T_1"))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_msg_print, 0, STRING("stg6_rsh_110"), 0, 0)
#else
        CALL(evt_msg_print, 0, STRING("stg6_rsh_110"), 0, STRING("me"))
#endif
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_11_OBTAIN_AUTOGRAPH)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_TALK_ANIM)
#endif
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_01_01"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_01_02"), 0, 0)
        CASE_LESS(STORY_STG6_21_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_01"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        IF_INT_EQUAL(LSWF(2), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_152"), 0, 0)
            SET_VALUE(LSWF(2), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_153"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_209"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_217"), 0, 0)
        CASE_LESS(STORY_STG6_46_ENGINEER)
        CALL_CHILD(evt_moamoa)
        CASE_LESS(STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_anim, STRING("me"), STRING("T_2"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_235"), 0, 0)
        CALL(evt_npc_set_anim, STRING("me"), STRING("B_2"))
        CASE_LESS(STORY_STG6_57_A_MAIL_FROM_PEACH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_253"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08_1"), 0, 0)
            RETURN
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_c_07"), 0, 0)
        ELSE
#if VERSION <= VERSION_DEMO_US
            CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08"), 0, 0)
#else
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08"), 0, 0)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg6_rsh_c_08_1"), 0, 0)
            END_IF
#endif
        END_IF
    END_SWITCH
    RETURN
EVT_END()

static NpcSetupInfo npc_data[] = {
    {
        "運転手", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_unten, // initEvent
        regu_unten, // regularEvent
        talk_unten, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

static const char* access_tbl[] = {
    "nittei",
    "stg6_rsh_259",
    "soujyuu",
    "stg6_rsh_260",
    NULL,
};

/** Trigger script for the signboards (nittei, soujyuu): locks input, prints the message in LW(1) and unlocks. */
static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, LW(1), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Registers the cab's signboard triggers from access_tbl (hit name, message):
 * each row runs evt_access when Mario faces it.
 */
static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(&access_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

/**
 * Shared map init for the three variants of the driver's cab:
 * starts the window and scenery animations unless the train is stopped at a station, registers the driver,
 * the signboards, the handle animation, the save block and the Star Piece spinning-floor panel,
 * and starts the music and ambience for the current story stage.
 */
EVT_BEGIN(rsh_00_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CASE_GREATER_OR_EQUAL(STORY_STG6_48_01_ARRIVING_AT_POSHLEY)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING("yure"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_sora"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_yama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_iwayama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_saboten"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_hosi"), 1, 0)
    END_SWITCH
    CALL(evt_npc_setup, PTR(npc_data))
    CALL_CHILD(evt_access_entry)
    SPAWN_EVENT(evt_handle)
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -210, 60, -145, 0, 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_NOT_EQUAL(LW(0), STRING("rsh_00_c"))
        CALL(evt_mobj_kururing_floor, STRING("kururin1"), -132, 0, -95, STRING("s_zentai"), 125, GSWF(GSWF_RSH00_STAR_PIECE_PANEL))
    ELSE
        CALL(evt_mobj_kururing_floor, STRING("kururin1"), -132, 0, -95, STRING("s_yuka1"), 125, GSWF(GSWF_RSH00_STAR_PIECE_PANEL))
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_02_A_CASE_OF_LOST_STEW, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        CASE_BETWEEN(STORY_STG6_22_DOCUMENT, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_HOM1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_BETWEEN(STORY_STG6_44_END_OF_DAY_2, STORY_STG6_45_DAY_3_STARTS)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        CASE_BETWEEN(STORY_STG6_49_POSHLEY_HEIGHTS, STORY_STG6_55_04_BOWSER_RAWK_HAWK)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_00_a"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_00_b"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH3"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_00_c"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init script of rsh_00_a (first visit): sets up the door to rsh_01_a, runs the shared init,
 * and from day 3 on sets up the Smorg effect (shown at once from the engineer stage on).
 */
EVT_BEGIN(rsh_00_a_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
        CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
        CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
        CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
        CALL(evt_ext_entry, 1000, PTR(moamoa_data), PTR(moamoa_init), PTR(moamoa_main), PTR(moamoa_dispent))
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_46_ENGINEER)
            CALL(evt_moamoa_set_seq_all, 4)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Init script of rsh_00_b (first visit): sets up the door to rsh_01_b and runs the shared init. */
EVT_BEGIN(rsh_00_b_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt)
    RETURN
EVT_END()

static const char* window_tbl[] = {
    "mado_uturi_1",
    "mado_uturi_2",
    "mado_uturi_3",
    "mado_uturi_4",
    NULL,
};

/**
 * Init script of rsh_00_c (first visit): sets up the door to rsh_01_c,
 * runs the shared init and the window scenery for mado_uturi_1..4.
 */
EVT_BEGIN(rsh_00_c_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    RETURN
EVT_END()

/**
 * Shared map init for the cab on the second visit (after the story has reached WELCOME_BACK):
 * plays the scenery animation for the outbound or return trip unless the train is standing at a station,
 * and restores the driver, save block, Star Piece panel and signboards,
 * then picks the music for the station the train has reached (Poshley Heights, Rogueport, or the train theme).
 */
EVT_BEGIN(rsh_00_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 0)
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
                CALL(evt_map_playanim, STRING("yure"), 1, 0)
                IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
                    CALL(evt_map_playanim, STRING("hai_sora"), 1, 0)
                    CALL(evt_map_playanim, STRING("hai_yama"), 1, 0)
                    CALL(evt_map_playanim, STRING("hai_iwayama"), 1, 0)
                    CALL(evt_map_playanim, STRING("hai_saboten"), 1, 0)
                ELSE
                    CALL(evt_map_playanim, STRING("rt_hai_sora"), 1, 0)
                    CALL(evt_map_playanim, STRING("rt_hai_yama"), 1, 0)
                    CALL(evt_map_playanim, STRING("rt_hai_iwayama"), 1, 0)
                    CALL(evt_map_playanim, STRING("rt_hai_saboten"), 1, 0)
                END_IF
            END_IF
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npc_data))
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -210, 60, -145, 0, 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_NOT_EQUAL(LW(0), STRING("rsh_00_c"))
        CALL(evt_mobj_kururing_floor, STRING("kururin1"), -132, 0, -95, STRING("s_zentai"), 125, GSWF(GSWF_RSH00_STAR_PIECE_PANEL))
    ELSE
        CALL(evt_mobj_kururing_floor, STRING("kururin1"), -132, 0, -95, STRING("s_yuka1"), 125, GSWF(GSWF_RSH00_STAR_PIECE_PANEL))
    END_IF
    CALL_CHILD(evt_access_entry)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_POSHLEY), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        // The demo checks the Rogueport arrival in its own IF after the Poshley one and restarts the ambient sound;
        // the releases test it in the ELSE and stop the ambient sound.
#if VERSION <= VERSION_DEMO_US
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR5"))
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    ELSE
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_00_a"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_00_b"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_00_c"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
        END_IF
    END_IF
    RETURN
#else
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
            CALL(evt_snd_envoff, PSND_FADE_OUT)
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        ELSE
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_00_a"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_00_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_00_c"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_4"))
            END_IF
        END_IF
    END_IF
    RETURN
#endif
EVT_END()

/** Init script of rsh_00_a on the second visit: door to rsh_01_a plus rsh_00_init_evt_nidome. */
EVT_BEGIN(rsh_00_a_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt_nidome)
    RETURN
EVT_END()

/** Init script of rsh_00_b on the second visit: door to rsh_01_b plus rsh_00_init_evt_nidome. */
EVT_BEGIN(rsh_00_b_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt_nidome)
    RETURN
EVT_END()

/** Init script of rsh_00_c on the second visit: door to rsh_01_c, rsh_00_init_evt_nidome and the window scenery. */
EVT_BEGIN(rsh_00_c_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_00_init_evt_nidome)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    RETURN
EVT_END()
