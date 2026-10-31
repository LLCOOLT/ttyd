// tou_02 (闘技場, Glitz Pit): the entrance lobby with the fans and the reception; leads to tou_01, tou_03, tou_04.

#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"

#include "string.h"
#include "mario/mariost.h"
#include "dolphin/os.h"
#include "stdlib.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "party/party_cloud.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "driver/dispdrv.h"
#include "party.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "data_tables.h"
#include "evt/evt_npc.h"
#include "driver/extdrv.h"
#include "driver/itemdrv.h"
#include "evt/evt_cam.h"
#include "evt/evt_cloud.h"
#include "evt/evt_eff.h"
#include "evt/evt_ext.h"
#include "evt/evt_fade.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "tou.h"
#include "libc_decls.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#if VERSION >= VERSION_US
USER_FUNC(N_evt_sub_status_gauge_force_update);
#endif

typedef struct Fan {
    u16 flags;
    s16 state;
    s16 animIdx;
    u8 pad_0x6[2];
    u64 time;
    Vec pos;
    Vec vel;
    f32 dir;
    Vec target;
    Vec param;
    s16 timer;
} Fan; /* dir: never accessed */
typedef struct FanAnim {
    char name[16];
    char anim[8];
    s16 loop;
    f32 rate;
    s32 start;
    s32 count;
} FanAnim;
typedef struct FanWork {
    s32 num;
    Fan* fans;
    s32 animNum;
    FanAnim anim[32];
    s32 hammerTimer;
    s32 count;
    s32 sfxId;
    u8 vol;
} FanWork;
typedef struct FanData {
    const char* name;
    const char* anim;
    f32 rate;
} FanData;
FanWork* fan_wp;
/** Polynomial sine approximation (x in radians, 0 to 2 pi) used for the lobby crowd's movement. */
static inline f32 fan_sin(f32 x) {
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
/** Polynomial cosine approximation (x in radians, 0 to 2 pi) used for the lobby crowd's movement. */
static inline f32 fan_cos(f32 x) {
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
static s32 check_hammer(Fan* fan);

static s32 evt_end_count(EventEntry* event, BOOL isFirstCall);
static void ext_fan_dispent(void);

s32 move_pos[26];
ExtTexInfo ext_fan_data[28];

/**
 * Builds the fan crowd's animation table (FanAnim) from ext_fan_data:
 * groups the per-frame texture entries by model name and animation,
 * recording each animation's first texture and frame count.
 */
static void pose_init(void) {
    char name[32];
    char anim[32];
    FanData* d = (FanData*)ext_fan_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    fan_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            fan_wp->animNum++;
        }
        strcpy(fan_wp->anim[fan_wp->animNum].name, name);
        strcpy(fan_wp->anim[fan_wp->animNum].anim, anim);
        fan_wp->anim[fan_wp->animNum].start = start;
        fan_wp->anim[fan_wp->animNum].count = i - start + 1;
        fan_wp->anim[fan_wp->animNum].rate = d->rate;
        fan_wp->anim[fan_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    fan_wp->animNum++;
}

/**
 * Per-frame update of the crowd's sprites: picks each fan's current texture frame from its animation
 * and the render time.
 */
static void pose_main(void) {
    s32 i;
    ExtdrvPose* pose;
    Fan* fan;
    FanAnim* a;
    f32 t;

    pose = extGetPosePtr();
    fan = fan_wp->fans;

    for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
        a = &fan_wp->anim[fan->animIdx];
        t = 60.0f * OSTicksToMilliseconds((u64)(gp->renderTime - fan->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            fan->time = gp->renderTime;
            t = 0.0f;
        }
        pose->texId = a->start + (s32)((a->count - 1) * t);
    }
}

/** Switches a fan to the animation named `anim` of model `name` (if it exists and differs) and restarts its timer. */
static void pose_change(Fan* fan, const char* name, const char* anim) {
    FanAnim* a;
    s32 i;

    for (i = 0, a = fan_wp->anim; i < fan_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < fan_wp->animNum && fan->animIdx != i) {
        fan->animIdx = i;
        fan->time = gp->renderTime;
    }
}

/** Returns a random float between min and max. */
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

/**
 * Door animation callback for the lobby's automatic double door on the street side (the exit animation of the
 * bero back to tou_01): LW(0) is the swing angle 0 to 180.
 * At the start it plays the automatic door sound at Mario's position (GW(13) keeps its handle)
 * unless the door is busy (GSWF_TOU_DOOR_BUSY), and at 180 it clears the flag and stops the sound.
 * It slides door_1_b by a third of the angle along X and door_1_a the opposite way.
 */
static EVT_BEGIN(s_door_open)
    IF_FLOAT_EQUAL(LW(0), FLOAT((0.0f)))
        IF_INT_EQUAL(GSWF(GSWF_TOU_DOOR_BUSY), 0)
            SET_VALUE(GSWF(GSWF_TOU_DOOR_BUSY), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AUTO_DOOR1"), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        SET_VALUE(GSWF(GSWF_TOU_DOOR_BUSY), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_b"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_a"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Door animation callback for the same automatic double door (the enter animation):
 * the mirror image of s_door_open, run as the angle goes from 180 back to 0.
 * It plays the door sound at the start, stops it and clears GSWF_TOU_DOOR_BUSY at 0,
 * and slides door_1_a and door_1_b shut.
 */
static EVT_BEGIN(s_door_close)
    IF_FLOAT_EQUAL(LW(0), FLOAT(180.0f))
        IF_INT_EQUAL(GSWF(GSWF_TOU_DOOR_BUSY), 0)
            SET_VALUE(GSWF(GSWF_TOU_DOOR_BUSY), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AUTO_DOOR1"), LW(0), LW(1), LW(2), GW(13))
            END_INLINE_EVENT
        END_IF
    END_IF
    IF_FLOAT_EQUAL(LW(0), FLOAT((0.0f)))
        SET_VALUE(GSWF(GSWF_TOU_DOOR_BUSY), 0)
        CALL(evt_snd_sfxoff, GW(13))
    END_IF
    MULTIPLY_FLOAT(LW(0), FLOAT(0.3330078f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_b"), LW(0), 0, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING("door_1_a"), LW(0), 0, 0)
    RETURN
EVT_END()

/** Swings open the double doors door_2_a / door_2_b (the first lobby door pair). */
EVT_BEGIN(n_1_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_a"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Swings the double doors door_2_a / door_2_b closed again. */
EVT_BEGIN(n_1_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_2_a"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback for the lobby's second double door (door_3_a and door_3_b): LW(0) is the swing angle;
 * the two leaves turn about the Y axis in opposite directions by 0.39 times the angle.
 */
static EVT_BEGIN(n_2_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_a"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback for the second double door going shut:
 * like n_2_door_open with the angle direction reversed.
 */
static EVT_BEGIN(n_2_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_b"), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("door_3_a"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Swings open the lobby door door_4. */
EVT_BEGIN(n_3_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_4"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Swings the lobby door door_4 closed again. */
EVT_BEGIN(n_3_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_4"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Swings open the lobby door door_5. */
EVT_BEGIN(n_4_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_5"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Swings the lobby door door_5 closed again. */
EVT_BEGIN(n_4_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_5"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Doors of the lobby: the front door out to the plaza (tou_01), the two arena doors to tou_03
 * (ground floor and upper floor) and the two doors to the main corridor (tou_04).
 */
static BeroEntry bero_data[] = {
    {
        ("s_bero"), // hitName
        1, // type
        0, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_01", // nextMapName
        ("a_door_mon"), // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_door_close, // enterAnimeArg
        s_door_open, // exitAnimeArg
    },
    {
        ("n_bero_1"), // hitName
        1, // type
        6, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_03", // nextMapName
        ("s_bero_1"), // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_1_door_close, // enterAnimeArg
        n_1_door_open, // exitAnimeArg
    },
    {
        ("n_bero_2"), // hitName
        1, // type
        6, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_03", // nextMapName
        ("s_bero_2"), // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_2_door_close, // enterAnimeArg
        n_2_door_open, // exitAnimeArg
    },
    {
        ("n_bero_3"), // hitName
        1, // type
        4, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_04", // nextMapName
        ("e_bero"), // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_3_door_close, // enterAnimeArg
        n_3_door_open, // exitAnimeArg
    },
    {
        ("n_bero_4"), // hitName
        1, // type
        4, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_04", // nextMapName
        ("w_bero"), // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_4_door_close, // enterAnimeArg
        n_4_door_open, // exitAnimeArg
    },
    {0},
};

/**
 * The two guards step aside to x = -530 and x = 530 and face Mario;
 * sets GSWF_TOU02_GUARDS_STEP_ASIDE and advances the story to STORY_STG3_02_THE_GUARD_BACKS_OFF
 * if it was earlier.
 */
EVT_BEGIN(evt_move_g)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    ADD(LW(2), 100)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガードマン１"), -530, -185, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING("ガードマン１"), STRING("mario"))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("ガードマン２"), 530, -185, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("ガードマン２"), STRING("mario"))
    SET_VALUE(LW(0), 3)
    CALL_CHILD(bero_case_switch_on)
    SET_VALUE(LW(0), 4)
    CALL_CHILD(bero_case_switch_on)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_02_THE_GUARD_BACKS_OFF)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_02_THE_GUARD_BACKS_OFF)
    ELSE
        SET_VALUE(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 1)
    END_IF
    RETURN
EVT_END()

/**
 * NPC init for the left guard: stands at x = -470 until the guards step aside, then at -530;
 * absent when the story has moved on.
 */
EVT_BEGIN(init_gard1)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_02_THE_GUARD_BACKS_OFF)
        CALL(evt_npc_set_position, STRING("me"), -470, 0, -185)
        CASE_LESS(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_npc_set_position, STRING("me"), -530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 0)
            CALL(evt_npc_set_position, STRING("me"), -470, 0, -185)
        ELSE
            CALL(evt_npc_set_position, STRING("me"), -530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the left guard: lines depend on story progress (before the arena intro, after he steps aside,
 * after Mario's gone champion).
 */
EVT_BEGIN(talk_gard1)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_01_ARENA_INTRO)
        CALL(evt_msg_print, 0, STRING("stg3_tou_24"), 0, 0)
        CASE_LESS(STORY_STG3_02_THE_GUARD_BACKS_OFF)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37"), 0, 0)
        CALL_CHILD(evt_move_g)
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_01"), 0, 0)
        CASE_LESS(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_02"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_re_002_1"), 0, 0)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_001"), 0, 0)
                CALL_CHILD(evt_move_g)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_002"), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the right guard: stands at x = 470 until the guards step aside, then at 530. */
EVT_BEGIN(init_gard2)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_02_THE_GUARD_BACKS_OFF)
        CALL(evt_npc_set_position, STRING("me"), 470, 0, -185)
        CASE_LESS(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_npc_set_position, STRING("me"), 530, 0, -185)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 0)
            CALL(evt_npc_set_position, STRING("me"), 470, 0, -185)
        ELSE
            CALL(evt_npc_set_position, STRING("me"), 530, 0, -185)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of the right guard: same lines as talk_gard1. */
EVT_BEGIN(talk_gard2)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_01_ARENA_INTRO)
        CALL(evt_msg_print, 0, STRING("stg3_tou_24"), 0, 0)
        CASE_LESS(STORY_STG3_02_THE_GUARD_BACKS_OFF)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37"), 0, 0)
        CALL_CHILD(evt_move_g)
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_01"), 0, 0)
        CASE_LESS(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_37_02"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_re_002_1"), 0, 0)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_001"), 0, 0)
                CALL_CHILD(evt_move_g)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg3_tou_re_002"), 0, 0)
            END_IF
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the madam: stands at (525, 0, 0)
 * until STORY_STG3_34_RETURN_TO_ROGUEPORT (and at that stage when Mario has not left as champion),
 * and is hidden below the map afterwards.
 */
static EVT_BEGIN(init_madam)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_34_RETURN_TO_ROGUEPORT)
        CALL(evt_npc_set_position, STRING("me"), 525, 0, 0)
        CASE_EQUAL(STORY_STG3_34_RETURN_TO_ROGUEPORT)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), 525, 0, 0)
        ELSE
            CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the madam: a line before STORY_STG3_04_GONZALES_IS_BORN,
 * lines chosen by Mario's Glitz Pit ranking until STORY_STG3_32_BOSS_BATTLE (above 15, 10, 5, 0, or 0),
 * and one line afterwards.
 */
static EVT_BEGIN(talk_madam)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_01_07"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the reporter: stands at (-100, 0, -25). */
EVT_BEGIN(init_repo)
    CALL(evt_npc_set_position, STRING("me"), -100, 0, -25)
    RETURN
EVT_END()

/**
 * Talk script of the reporter: story-dependent lines (before Gonzales, until the boss battle,
 * then after the league reopens).
 */
EVT_BEGIN(talk_repo)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_02_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_024"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_024_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_023"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_024_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the first camera operator: stands at (-150, 0, 0). */
EVT_BEGIN(init_cam1)
    CALL(evt_npc_set_position, STRING("me"), -150, 0, 0)
    RETURN
EVT_END()

/** Talk script of the first camera operator: story-dependent lines. */
EVT_BEGIN(talk_cam1)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_03_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_026"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_026_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_025"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_026_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the second camera operator: stands at (80, 200, -125), or (30, 200, -60) before the arena intro. */
EVT_BEGIN(init_cam2)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_npc_set_position, STRING("me"), 80, 200, -125)
#else
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_01_ARENA_INTRO)
        CALL(evt_npc_set_position, STRING("me"), 80, 200, -125)
    ELSE
        CALL(evt_npc_set_position, STRING("me"), 30, 200, -60)
    END_IF
#endif
    RETURN
EVT_END()

/** Talk script of the second camera operator: story-dependent lines. */
EVT_BEGIN(talk_cam2)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_04_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_028"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_028_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_027"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_028_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the fourth Toad: placed at (-350, 0, 75). */
EVT_BEGIN(init_kino4)
    CALL(evt_npc_set_position, STRING("me"), -350, 0, 75)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    RETURN
EVT_END()

/** Regular (idle) script of the fourth Toad: paces between x = -350 and 350. */
EVT_BEGIN(reg_kino4)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), -350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        CALL(evt_npc_move_position, STRING("me"), 350, 75, 0, FLOAT(48.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
    END_LOOP
    RETURN
EVT_END()

/** Talk script of the fourth Toad: story-dependent lines. */
EVT_BEGIN(talk_kino4)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_05_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_030"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_030_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_029"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_030_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the fifth Toad: placed at (-520, 0, 25). */
EVT_BEGIN(init_kino5)
    CALL(evt_npc_set_position, STRING("me"), -520, 0, 25)
    RETURN
EVT_END()

/**
 * Talk script of the fifth Toad (キノピオ５), a parent who brought their son to the Glitz Pit: before Gonzales
 * debuts the son is a fan of Prince Mush (stg3_npc_02_06_01);
 * until the title match the line follows Mario's rank
 * (02 to 05), then congratulations (06) and, after the chapter, a farewell (07) or, when Mario re-entered the
 * league, the stg3_npc_re_031/032 lines. With Yoshi as the partner the _yos variants address him by the Yoshi's
 * name (LW(10)).
 */
EVT_BEGIN(talk_kino5)
    CALL(evt_pouch_get_yoshiname, LW(10))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        // Before Gonzales debuts the son is a fan of Prince Mush.
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        // Up to the title match the line follows Mario's rank, naming the Yoshi when he is the partner.
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_04_yos"), 0, 0, LW(10))
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_04"), 0, 0, LW(10))
            END_IF
            CASE_GREATER(0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
#if VERSION == VERSION_EU
                CALL(evt_sub_get_language, LW(0))
                SWITCH(LW(0))
                    CASE_EQUAL(2)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10))
                    CASE_EQUAL(4)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10))
                    CASE_EQUAL(5)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10))
                    CASE_DEFAULT
                    CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10), LW(10))
                END_SWITCH
#else
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05_yos"), 0, 0, LW(10), LW(10))
#endif
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_05"), 0, 0, LW(10))
            END_IF
            CASE_DEFAULT
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_06_yos"), 0, 0, LW(10))
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_06"), 0, 0, LW(10))
            END_IF
        END_SWITCH
        CASE_DEFAULT
        // After chapter 3: a farewell, or comments on Mario's return to the league.
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_EQUAL(LW(0), 4)
                CALL(evt_msg_print_insert, 0, STRING("stg3_npc_02_06_07_yos"), 0, 0, LW(10))
            ELSE
                CALL(evt_msg_print, 0, STRING("stg3_npc_02_06_07"), 0, 0)
            END_IF
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_yos"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032"), 0, 0)
                END_IF
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_mario_get_party, LW(0))
                IF_INT_EQUAL(LW(0), 4)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1_yos"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1"), 0, 0)
                END_IF
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print_insert, 0, STRING("stg3_npc_re_031_yos"), 0, 0, LW(10))
                    ELSE
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_031"), 0, 0)
                    END_IF
#if VERSION <= VERSION_DEMO_US
                    WAIT_MS(300)
                    CALL(evt_npc_set_anim, STRING("me"), STRING("M_1"))
                    WAIT_MS(600)
                    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
#endif
                ELSE
                    CALL(evt_mario_get_party, LW(0))
                    IF_INT_EQUAL(LW(0), 4)
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1_yos"), 0, 0)
                    ELSE
                        CALL(evt_msg_print, 0, STRING("stg3_npc_re_032_1"), 0, 0)
                    END_IF
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for Toadette (kinopiko): placed at (-490, 0, 25). */
EVT_BEGIN(init_kinopiko)
    CALL(evt_npc_set_position, STRING("me"), -490, 0, 25)
    RETURN
EVT_END()

/** Talk script of Toadette: story-dependent lines. */
EVT_BEGIN(talk_kinopiko)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_07_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_034"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_034_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_033"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_034_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the female Toad: placed at (100, 0, 0). */
EVT_BEGIN(init_kinopio_f)
    CALL(evt_npc_set_position, STRING("キノピオ女"), 100, 0, 0)
    RETURN
EVT_END()

/** Talk script of the female Toad: story-dependent lines. */
EVT_BEGIN(talk_kinopio_f)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TOU_REENTERED_LEAGUE), 0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_08_07"), 0, 0)
        ELSE
            CALL(evt_tou_get_ranking, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_036"), 0, 0)
                CASE_LESS_OR_EQUAL(10)
                CALL(evt_msg_print, 0, STRING("stg3_npc_re_036_1"), 0, 0)
                CASE_DEFAULT
                IF_INT_EQUAL(GSWF(GSWF_TOU_REMATCH_PROMOTED), 0)
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_035"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg3_npc_re_036_1"), 0, 0)
                END_IF
            END_SWITCH
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the mouse (chu): placed at (245, 0, 125) from Ms. Mowz's introduction,
 * otherwise hidden at y = -1000.
 */
EVT_BEGIN(init_chu)
    SWITCH(GSW(GSW_STORY_PROGRESS))
#if VERSION <= VERSION_DEMO_US
        CASE_LESS(STORY_STG3_20_08_MS_MOWZ)
#else
        CASE_LESS(STORY_STG3_20_05_MAJORS_4TH_PL)
#endif
        CALL(evt_npc_set_position, STRING("me"), 245, 0, 125)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of the mouse (chu): story-dependent lines. */
EVT_BEGIN(talk_chu)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_04_GONZALES_IS_BORN)
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_01"), 0, 0)
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_GREATER(15)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_02"), 0, 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_03"), 0, 0)
            CASE_GREATER(5)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_04"), 0, 0)
            CASE_GREATER(0)
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_05"), 0, 0)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_06"), 0, 0)
        END_SWITCH
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_npc_02_10_07"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the champion (Rawk Hawk) in the lobby:
 * only at story stage STORY_STG3_33_06_BOWSER_PUNI_ELDER, when Mario did not leave as champion,
 * he stands at (-15, 0, 25) and faces Mario instantly until the first sequence frame has passed.
 */
static EVT_BEGIN(init_champ)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -15, 0, 25)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Thirteen (x, z) points around the lobby that move_champ steps through; it does not use the values. */
s32 move_pos[] = {
    0, 0, -100, -70, -225, 50, -230, 135,
    -105, 110, 10, -10, 135, 135, 220, 40,
    138, -65, 35, -50, 0, 110, -80, -40,
    110, -40,
};

/**
 * Move event the lobby crowd scene gives the champion (チャンピョン) while the fans mob him (GF(10) clear): every
 * 2 to 7 s a fan's cry (stg3_tou_182 to 189 and 186_01, in turn) pops up with its tail at a random spot near
 * him; it ends once fewer than 10 fans are left. It steps through move_pos but discards the values it reads.
 */
EVT_BEGIN(move_champ)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(move_pos))
        LOOP(13)
            READ_INT2(LW(0), LW(1))
            CALL(evt_sub_random, 5, LW(0))
            ADD(LW(0), 2)
            MULTIPLY(LW(0), 1000)
            WAIT_MS(LW(0))
            CALL(evt_npc_get_position, STRING("me"), LW(5), LW(6), LW(7))
            CALL(evt_sub_random, 100, LW(0))
            CALL(evt_sub_random, 100, LW(1))
            SUBTRACT(LW(0), 50)
            ADD(LW(5), LW(0))
            ADD(LW(6), 40)
            SUBTRACT(LW(7), LW(1))
            CALL(evt_msg_toge, 2, LW(5), LW(6), LW(7))
            CALL(evt_end_count, LW(0))
            IF_INT_LESS(LW(0), 10)
                RETURN
            END_IF
            BEGIN_INLINE_EVENT
                SWITCH(LW(10))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_182"), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_183"), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_184"), 0, 0)
                    CASE_EQUAL(3)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_185"), 0, 0)
                    CASE_EQUAL(4)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_186"), 0, 0)
                    CASE_EQUAL(5)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_187"), 0, 0)
                    CASE_EQUAL(6)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_188"), 0, 0)
                    CASE_EQUAL(7)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_189"), 0, 0)
                    CASE_EQUAL(8)
                    CALL(evt_msg_print, 0, STRING("stg3_tou_186_01"), 0, 0)
                END_SWITCH
            END_INLINE_EVENT
            ADD(LW(10), 1)
            IF_INT_GREATER(LW(10), 8)
                SET_VALUE(LW(10), 0)
            END_IF
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

/** Talk script of the champion in the lobby (stg3_tou_190), with the post-Chapter 3 line stg3_tou_479_02. */
EVT_BEGIN(talk_champ)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_end_count, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_190_01"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("stg3_tou_190"), 0, STRING("me"))
        END_IF
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_02"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for Jolene (キノシコワ): at STORY_STG3_33_06_BOWSER_PUNI_ELDER (after the Bowser interlude, before
 * Mario leaves Glitzville) she is placed at (-25, 0, 75) unless Mario left as champion.
 */
EVT_BEGIN(init_shikowa)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -25, 0, 75)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of Jolene: at STORY_STG3_33_06_BOWSER_PUNI_ELDER she says stg3_tou_479_01; otherwise nothing. */
EVT_BEGIN(talk_shikowa)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_01"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the Shady Koopa (ウラノコ) in the lobby:
 * only at story stage STORY_STG3_33_06_BOWSER_PUNI_ELDER, when Mario did not leave as champion,
 * he stands at (-75, 0, 50) and faces Mario instantly until the first sequence frame has passed.
 */
static EVT_BEGIN(init_uranoko)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -75, 0, 50)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of the Shady Koopa: at story stage STORY_STG3_33_06_BOWSER_PUNI_ELDER he says stg3_tou_479_03;
 * otherwise nothing.
 */
static EVT_BEGIN(talk_uranoko)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_03"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the first Iron Cleft (アイアンＡ): scaled 1.5 in x and y, and at
 * STORY_STG3_33_06_BOWSER_PUNI_ELDER placed at (-30, 0, -50) unless Mario left as champion.
 */
EVT_BEGIN(init_ironA)
    CALL(evt_npc_set_scale, STRING("me"), FLOAT(1.5f), FLOAT(1.5f), FLOAT((1.0f)))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -30, 0, -50)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of the first Iron Cleft: stg3_tou_479_04 at STORY_STG3_33_06_BOWSER_PUNI_ELDER, otherwise nothing. */
EVT_BEGIN(talk_ironA)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_04"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC init for the second Iron Cleft (アイアンＢ): scaled 1.5 in x and y, and at
 * STORY_STG3_33_06_BOWSER_PUNI_ELDER placed at (-60, 0, -25) unless Mario left as champion.
 */
EVT_BEGIN(init_ironB)
    CALL(evt_npc_set_scale, STRING("me"), FLOAT(1.5f), FLOAT(1.5f), FLOAT((1.0f)))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -60, 0, -25)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of the second Iron Cleft: stg3_tou_479_05 at STORY_STG3_33_06_BOWSER_PUNI_ELDER, otherwise nothing. */
EVT_BEGIN(talk_ironB)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_05"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** NPC init for the Bandit (borodo): placed at (-100, 0, 100) in the late Chapter 3 scene. */
EVT_BEGIN(init_borodo)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("me"), -100, 0, 100)
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_INSTANT_TURN)
            BEGIN_INLINE_EVENT
                CALL(evt_seq_wait, 2)
                CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_INSTANT_TURN)
            END_INLINE_EVENT
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/** Talk script of the Bandit in the late Chapter 3 scene (stg3_tou_479_06). */
EVT_BEGIN(talk_borodo)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_msg_print, 0, STRING("stg3_tou_479_06"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPCs of the lobby: the two door guards, the madam, a reporter and two cameramen, two Toads, Toadette,
 * the badge seller, Rawk Hawk, Jolene, the Shady Koopa, the two Iron Clefts and the Bandit.
 */
static NpcSetupInfo npcEnt[] = {
    {
        "ガードマン１", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_gard1, // initEvent
        NULL, // regularEvent
        talk_gard1, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ガードマン２", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_gard2, // initEvent
        NULL, // regularEvent
        talk_gard2, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マダム", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_madam, // initEvent
        NULL, // regularEvent
        talk_madam, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "レポーター", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_repo, // initEvent
        NULL, // regularEvent
        talk_repo, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "カメラマン１", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_cam1, // initEvent
        NULL, // regularEvent
        talk_cam1, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "カメラマン２", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_cam2, // initEvent
        NULL, // regularEvent
        talk_cam2, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノピオ４", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_kino4, // initEvent
        reg_kino4, // regularEvent
        talk_kino4, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノピオ５", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_kino5, // initEvent
        NULL, // regularEvent
        talk_kino5, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノピコ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_kinopiko, // initEvent
        NULL, // regularEvent
        talk_kinopiko, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "バッジ屋", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_chu, // initEvent
        NULL, // regularEvent
        talk_chu, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "チャンピョン", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_champ, // initEvent
        NULL, // regularEvent
        talk_champ, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノシコワ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_shikowa, // initEvent
        NULL, // regularEvent
        talk_shikowa, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ウラノコ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_uranoko, // initEvent
        NULL, // regularEvent
        talk_uranoko, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "アイアンＡ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_ironA, // initEvent
        NULL, // regularEvent
        talk_ironA, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "アイアンＢ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_ironB, // initEvent
        NULL, // regularEvent
        talk_ironB, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ボロドー", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_borodo, // initEvent
        NULL, // regularEvent
        talk_borodo, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Lobby scene after the arena intro in tou_03 (which sets GSWF_TOU_ARENA_INTRO_TO_LOBBY): Mario and the partner
 * come in through door n_bero_1, or n_bero_2 on the upper floor, the partner asks how to get the Crystal Star
 * (stg3_tou_33) with the choice to steal it or battle to the top (stg3_tou_33_yn); Goombella, Koops or Flurrie
 * answer the choice (stg3_tou_34_* or 35_*), Mario nods, the partner speaks again (stg3_tou_36), the flag is
 * cleared and the story is set to STORY_STG3_01_ARENA_INTRO.
 */
EVT_BEGIN(evt_tougi2)
    // Mario and the partner wait behind the arena door they came out of (the upper one for n_bero_2).
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SET_VALUE(LF(0), 0)
    CALL(evt_bero_get_entername, LW(0))
    IF_STR_EQUAL(LW(0), STRING("n_bero_2"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mario_set_pos, -25, 200, -220)
        CALL(evt_party_set_pos, 0, 25, 200, -220)
    ELSE
        CALL(evt_mario_set_pos, -25, 0, -220)
        CALL(evt_party_set_pos, 0, 25, 0, -220)
    END_IF
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_party_set_dir, 0, 270, -1)
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_cam3d_evt_set, 0, 290, 190, 0, 238, -158, 0, 11)
    ELSE
        CALL(evt_cam3d_evt_set, 0, 90, 190, 0, 38, -158, 0, 11)
    END_IF
    // The door opens and they step into the lobby.
    CALL(evt_seq_wait, 2)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(n_2_door_open)
        ELSE
            CALL_CHILD(n_1_door_open)
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_mario_mov_pos, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(2), 100)
        CALL(evt_party_move_pos, 0, LW(0), LW(2), 1000)
    END_INLINE_EVENT
    WAIT_MS(700)
    SET_VALUE(LW(1), 2)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(0), 1)
            CALL_CHILD(n_2_door_close)
        ELSE
            CALL_CHILD(n_1_door_close)
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    // The partner asks how to get the Crystal Star, steal it or fight to the top, and answers Mario's choice.
    CALL(evt_msg_print_party, STRING("stg3_tou_33"))
    CALL(evt_msg_select, 0, STRING("stg3_tou_33_yn"))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(PARTY_MEMBER_GOOMBELLA)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_kur"))
            CASE_EQUAL(PARTY_MEMBER_KOOPS)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_nok"))
            CASE_EQUAL(PARTY_MEMBER_FLURRIE)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_34_win"))
        END_SWITCH
    ELSE
        CALL(evt_mario_get_party, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(PARTY_MEMBER_GOOMBELLA)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_kur"))
            CASE_EQUAL(PARTY_MEMBER_KOOPS)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_nok"))
            CASE_EQUAL(PARTY_MEMBER_FLURRIE)
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_35_win"))
        END_SWITCH
    END_IF
    // Mario nods, the partner sums up and the story moves on.
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_36"))
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSWF(GSWF_TOU_ARENA_INTRO_TO_LOBBY), 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_01_ARENA_INTRO)
#if VERSION >= VERSION_JP
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
#endif
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Texture frames of the lobby fan crowd sprites: the Toad, Toadette and Lakitu walk cycles,
 * grouped into animations by pose_init and registered with evt_ext_entry.
 */
ExtTexInfo ext_fan_data[] = {
    {("c_kinopio"), ("KNP_W_1"), 2.0f},
    {("c_kinopio"), ("KNP_W_1"), 6.0f},
    {("c_kinopio"), ("KNP_W_1"), 10.0f},
    {("c_kinopio"), ("KNP_W_1"), 14.0f},
    {("c_kinopio"), ("KNP_W_1"), 18.0f},
    {("c_kinopio"), ("KNP_W_1"), 22.0f},
    {("c_kinopio"), ("KNP_W_1"), 26.0f},
    {("c_kinopio"), ("KNP_W_1"), 30.0f},
    {("c_kinopio"), ("KNP_W_1"), 34.0f},
    {("c_kinopiko"), ("KNF_W_1"), 2.0f},
    {("c_kinopiko"), ("KNF_W_1"), 6.0f},
    {("c_kinopiko"), ("KNF_W_1"), 10.0f},
    {("c_kinopiko"), ("KNF_W_1"), 14.0f},
    {("c_kinopiko"), ("KNF_W_1"), 18.0f},
    {("c_kinopiko"), ("KNF_W_1"), 22.0f},
    {("c_kinopiko"), ("KNF_W_1"), 26.0f},
    {("c_kinopiko"), ("KNF_W_1"), 30.0f},
    {("c_kinopiko"), ("KNF_W_1"), 34.0f},
    {("c_kinopiko"), ("KNF_W_1"), 38.0f},
    {("c_jugemu"), ("JGM_W_1"), 0.0f},
    {("c_jugemu"), ("JGM_W_1"), 4.0f},
    {("c_jugemu"), ("JGM_W_1"), 8.0f},
    {("c_jugemu"), ("JGM_W_1"), 12.0f},
    {("c_jugemu"), ("JGM_W_1"), 16.0f},
    {("c_jugemu"), ("JGM_W_1"), 20.0f},
    {("c_jugemu"), ("JGM_W_1"), 24.0f},
    {("c_jugemu"), ("JGM_W_1"), 28.0f},
    {0},
};

/**
 * Init callback of the lobby fan crowd (extdrv sprites): allocates FanWork and one Fan per pose, gives each fan
 * a random facing, a random Toad, Toadette or Lakitu walk animation and a random spot within 100 of the centre,
 * and starts the crowd noise SFX_STG3_AUDIENCE_FAN1, keeping its full volume.
 */
static void ext_fan_init(void) {
    s32 i;
    ExtdrvPose* pose;
    Fan* fan;

    fan_wp = _mapAlloc(sizeof(FanWork));
    memset(fan_wp, 0, sizeof(FanWork));
    fan_wp->num = extGetPoseNum();
    fan_wp->fans = _mapAlloc(fan_wp->num * sizeof(Fan));
    memset(fan_wp->fans, 0, fan_wp->num * sizeof(Fan));
    pose_init();
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        pose->flags |= 7;
        PSMTXIdentity(*pose->mtx);
        (*pose->mtx)[0][3] = 0.0f;
        (*pose->mtx)[1][3] = 0.0f;
        (*pose->mtx)[2][3] = 0.0f;
        pose->dir = randf(0.0f, 360.0f);
        switch (irand(1000) % 3) {
            case 0:
                pose_change(fan, "c_kinopio", "KNP_W_1");
                break;
            case 1:
                pose_change(fan, "c_kinopiko", "KNF_W_1");
                break;
            case 2:
            default:
                pose_change(fan, "c_jugemu", "JGM_W_1");
                break;
        }
        fan->state = 0;
        {
            Vec pos = {0.0f, 0.0f, 0.0f};

            pos.x = randf(-100.0f, 100.0f);
            pos.z = randf(-100.0f, 100.0f);
            fan->pos = pos;
#if VERSION >= VERSION_JP
            fan->vel = (Vec){0.0f, 0.0f, 0.0f};
#endif
        }
    }
#if VERSION <= VERSION_DEMO_US
    // the demo hides the first fan: ext_fan_main moves it onto Mario
    extGetPosePtr()->flags &= ~1;
#endif
    fan_wp->sfxId = psndSFXOn_3D("SFX_STG3_AUDIENCE_FAN1", &(Vec){0.0f, 0.0f, 0.0f});
    fan_wp->vol = psndSFX_get_vol(fan_wp->sfxId);
}

/** Display callback of the fan crowd: loads render mode, vertices, textures and TEV, and draws all fan sprites. */
static void fan_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

// FAKE: optimisation pragmas: without them the function's code differs from the original (checked by removing them).
#pragma opt_propagation off
#pragma opt_lifetimes off
static Vec fan_zero;
/**
 * Per-frame callback of the fan crowd: the fans press toward the target (Mario when GF(10) is set, otherwise the
 * champion, with Mario also in the crowd), push each other apart and bounce off walls; a fan that Mario's hammer
 * hits (check_hammer 1) flies off in an arc, one caught in Flurrie's gust (2) drifts away, and both then vanish;
 * the crowd noise follows the target and its volume the share of fans left (count).
 * The demos and the releases have different bodies.
 */
static void ext_fan_main(void) {
    MarioWork* mario = marioGetPtr();
    Fan* fan;
    // The releases rewrote the fan crowd update (Mario joins it only while GF(10) is set, the pose pass checks hits), so each version keeps its own body
#if VERSION <= VERSION_DEMO_US
    s32 i;
    ExtdrvPose* pose;
    Vec dir;
    Vec target = {0.0f, 0.0f, 0.0f};

    if (mario->currMotionId == MARIO_MOTION_HAMMER) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }
    {
        Fan* fan = fan_wp->fans;
        s32 i;

        // the first fan stands in for Mario
        fan->pos = mario->position;
        if (evtGetValue(NULL, GF(10))) {
            target = fan->pos;
        } else {
            target = npcNameToPtr("チャンピョン")->position;
        }

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                PSVECSubtract(&target, &fan->pos, &dir);
                if (PSVECMag(&dir) > 50.0f) {
                    PSVECNormalize(&dir, &dir);
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, 0.4f);
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                }
            }
        }
    }

    for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
        if (fan->state == 0) {
            s32 j;
            Fan* other;
            f32 d;

            for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
                if (other->state == 0 && fan != other && (d = PSVECSquareDistance(&fan->pos, &other->pos)) < 900.0f) {
                    PSVECSubtract(&fan->pos, &other->pos, &dir);
                    if (d == 0.0f) {
                        dir.x = d = 1.0f;
                    }
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, 8.0f * (1.0f / d));
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                    PSVECSubtract(&other->vel, &dir, &other->vel);
                }
            }
        }
    }
    {
        f32 angle;
        f32 dist;
        f32 dy;
        f32 spd;
        f32 x;
        f32 z;
        f32 dir2;
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                switch (check_hammer(fan)) {
                    case 0:
                        break;
                    case 1:
                        fan->state = 10;
                        {
                            f32 k;
                            f32 mn;
                            f32 r = rand() / 32767.0f;
                            angle = (6.2831855f * ((r * (k = 225.0f - 135.0f)) + (mn = 135.0f))) / 360.0f;
                        } // FAKE: hand-inlined randf(135.0f, 225.0f) (same rand() call, r*90+135), 6.28 first so its pool address is created before 90/135 as in the target
                        dist = randf(400.0f, 500.0f);
                        x = fan->pos.x + dist * fan_sin(angle);
                        z = fan->pos.z - dist * fan_cos(angle);
                        {
                            Vec tgt = {0.0f, 0.0f, 0.0f};

                            tgt.x = x;
                            tgt.y = -100.0f;
                            tgt.z = z;
                            fan->target = tgt;
                        }
                        fan->param.y = randf(4.0f, 6.0f);
                        fan->param.z = randf(0.1f, 0.2f);
                        dy = fan->target.y - fan->pos.y;
                        dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        fan->timer = dist / fan->param.y;
                        fan->param.x = dy / fan->timer + fan->param.z * fan->timer / 2.0f;
                        // FAKE: integer cast makes the literal a CSE/loop-invariant temp (target addi r30 + mr r29 copy)
                        psndSFXOn_3D(SFX_NAME_WORD("SFX_STG3_AUDIENCE_FAN_FLY1"), &fan->pos);
                        break;
                    case 2: {

                        angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                        dir2 = cloudGetBreathDir();
                        fan->state = 20;
                        dir2 = (angle + dir2) / 2.0f;
                        fan->target = fan_zero;
                        spd = randf(0.1f, 0.2f);
                        angle = 6.2831855f * dir2 / 360.0f;
                        fan->param.x = spd * fan_sin(angle);
                        fan->param.y = randf(0.03f, 0.06f);
                        fan->param.z = spd * -fan_cos(angle);
                        fan->timer = 120;
                        // FAKE: integer cast makes the literal a CSE/loop-invariant temp (target addi r30 + mr r29 copy)
                        psndSFXOn_3D(SFX_NAME_WORD("SFX_STG3_AUDIENCE_FAN_FLY1"), &fan->pos);
                        break;
                    }
                }
            }
        }
    }
    fan_wp->count = fan_wp->num;

    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        f32 angle;

        switch (fan->state) {
            case 0:
                PSVECAdd(&fan->pos, &fan->vel, &fan->pos);
                PSVECScale(&fan->vel, &fan->vel, 0.6f);
                if (fan->pos.z < -190.0f) {
                    fan->pos.z = -190.0f;
                }
                if (fan->pos.z > 190.0f) {
                    fan->pos.z = 190.0f;
                }
                break;
            case 10:
                fan->pos.y += fan->param.x;
                fan->param.x -= fan->param.z;
                angle = angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                angle = 6.2831855f * angle / 360.0f;
                fan->pos.x += fan->param.y * fan_sin(angle);
                fan->pos.z += fan->param.y * -fan_cos(angle);
                if (--fan->timer < 0) {
                    fan->state = 100;
                }
                break;
            case 20:
                if (--fan->timer > 0) {
                    fan->target.x += fan->param.x;
                    fan->target.y += fan->param.y;
                    fan->target.z += fan->param.z;
                    fan->pos.x += fan->target.x;
                    fan->pos.y += fan->target.y;
                    fan->pos.z += fan->target.z;
                } else {
                    fan->state = 100;
                }
                break;
            case 100:
                pose->flags &= ~3;
                fan->state++;
                break;
            case 101:
                break;
        }
        if (fan->state != 0) {
            fan_wp->count--;
        }
        (*pose->mtx)[0][3] = fan->pos.x;
        (*pose->mtx)[1][3] = fan->pos.y;
        (*pose->mtx)[2][3] = fan->pos.z;
        pose->dir = angleABf(target.x, target.z, fan->pos.x, fan->pos.z);
    }
    pose_main();
#else
    ExtdrvPose* pose;
    s32 li;
    Fan* lfan;
    s32 i;
    Vec dir;
    Vec target = {0.0f, 0.0f, 0.0f};

    if (mario->currMotionId == MARIO_MOTION_HAMMER) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }
    if (evtGetValue(NULL, GF(10))) {
        ExtdrvPose* pose = extGetPosePtr();
        Fan* fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                fan->pos = mario->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    } else {
        s32 i;
        s32 found = 0;

        pose = extGetPosePtr();
        fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                if (!found) {
                    found = 1;
                    fan->pos = mario->position;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                } else {
                    fan->pos = npcNameToPtr("チャンピョン")->position;
                    target = fan->pos;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                    break;
                }
            }
        }
    }

    {

        Fan* fan;
        s32 i;

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                PSVECSubtract(&target, &fan->pos, &dir);
                if (PSVECMag(&dir)) {
                    PSVECNormalize(&dir, &dir);
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, 0.1f);
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                }
            }
        }
    }

    {

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                s32 j;
                Fan* other;

                for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
                    if (other->state == 0 && i != j && PSVECSquareDistance(&fan->pos, &other->pos) < 900.0f) {
                        PSVECSubtract(&fan->pos, &other->pos, &dir);
                        dir.y = 0.0f;
                        PSVECNormalize(&dir, &dir);
                        PSVECScale(&dir, &dir, 5.0f);
                        PSVECAdd(&fan->vel, &dir, &fan->vel);
                        PSVECSubtract(&other->vel, &dir, &other->vel);
                    }
                }
            }
        }
    }

    {
        f32 angle;
        f32 dist;
        f32 dy;
        f32 spd;
        f32 x;
        f32 z;
        f32 dir2;
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                switch (check_hammer(fan)) {
                    case 0:
                        break;
                    case 1:
                        fan->state = 10;
                        {
                            f32 k;
                            f32 mn;
                            f32 r = rand() / 32767.0f;
                            angle = (6.2831855f * ((r * (k = 225.0f - 135.0f)) + (mn = 135.0f))) / 360.0f;
                        } // FAKE: hand-inlined randf(135.0f, 225.0f) (same rand() call, r*90+135), 6.28 first so its pool address is created before 90/135 as in the target
                        dist = randf(400.0f, 500.0f);
                        x = fan->pos.x + dist * fan_sin(angle);
                        z = fan->pos.z - dist * fan_cos(angle);
                        {
                            Vec tgt = {0.0f, 0.0f, 0.0f};

                            tgt.x = x;
                            tgt.y = -100.0f;
                            tgt.z = z;
                            fan->target = tgt;
                        }
                        fan->param.y = randf(4.0f, 6.0f);
                        fan->param.z = randf(0.1f, 0.2f);
                        dy = fan->target.y - fan->pos.y;
                        dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        fan->timer = dist / fan->param.y;
                        fan->param.x = dy / fan->timer + fan->param.z * fan->timer / 2.0f;
                        // FAKE: integer cast makes the literal a CSE/loop-invariant temp (target addi r30 + mr r29 copy)
                        psndSFXOn_3D(SFX_NAME_WORD("SFX_STG3_AUDIENCE_FAN_FLY1"), &fan->pos);
                        break;
                    case 2: {

                        angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                        dir2 = cloudGetBreathDir();
                        fan->state = 20;
                        angle = (angle + dir2) / 2.0f;
                        fan->target = fan_zero;
                        spd = randf(0.1f, 0.2f);
                        angle = 6.2831855f * angle / 360.0f;
                        fan->param.x = spd * fan_sin(angle);
                        fan->param.y = randf(0.03f, 0.06f);
                        fan->param.z = spd * -fan_cos(angle);
                        fan->timer = 120;
                        // FAKE: integer cast makes the literal a CSE/loop-invariant temp (target addi r30 + mr r29 copy)
                        psndSFXOn_3D(SFX_NAME_WORD("SFX_STG3_AUDIENCE_FAN_FLY1"), &fan->pos);
                        break;
                    }
                }
            }
        }
    }
    fan_wp->count = fan_wp->num;

    {
        f32 angle;
        f32 dist;
        f32 h;

        pose = extGetPosePtr();
        lfan = fan_wp->fans;
        for (li = 0; li < fan_wp->num; li++, pose++, lfan++) {
            switch (lfan->state) {
                case 0: {
                    HitCheckQuery query;
                    HitCheckQuery* q = &query;
                    PSVECNormalize(&lfan->vel, &lfan->vel);
                    dist = PSVECMag(&lfan->vel);
                    query.targetPos = lfan->pos;
                    query.targetPos.y += 4.0f;
                    query.targetDir = lfan->vel;
                    query.targetDir.y = 0.0f;
                    query.targetDistance = 25.0f + dist;
                    if (hitCheckVecFilter(&query, NULL)) {
                        C_VECReflect(&lfan->vel, &q->hitNormal, &lfan->vel);
                    } else {
                        lfan->pos.x += lfan->vel.x;
                        lfan->pos.z += lfan->vel.z;
                        lfan->vel.x *= 0.6f;
                        lfan->vel.z *= 0.6f;
                    }
                    if (lfan->pos.x < -350.0f) {
                        lfan->pos.x = -350.0f;
                    }
                    if (lfan->pos.x > 350.0f) {
                        lfan->pos.x = 350.0f;
                    }
                    if (lfan->pos.z > (h = 195.0f + li / 100.0f)) {
                        lfan->pos.z = h;
                    }
                    break;
                }
                case 10:
                    lfan->pos.y += lfan->param.x;
                    lfan->param.x -= lfan->param.z;
                    angle = angleABf(lfan->pos.x, lfan->pos.z, lfan->target.x, lfan->target.z);
                    angle = 6.2831855f * angle / 360.0f;
                    lfan->pos.x += lfan->param.y * fan_sin(angle);
                    lfan->pos.z += lfan->param.y * -fan_cos(angle);
                    if (--lfan->timer < 0) {
                        lfan->state = 100;
                    }
                    break;
                case 20:
                    if (--lfan->timer > 0) {
                        lfan->target.x += lfan->param.x;
                        lfan->target.y += lfan->param.y;
                        lfan->target.z += lfan->param.z;
                        lfan->pos.x += lfan->target.x;
                        lfan->pos.y += lfan->target.y;
                        lfan->pos.z += lfan->target.z;
                    } else {
                        lfan->state = 100;
                    }
                    break;
                case 100:
                    pose->flags &= ~3;
                    lfan->state++;
                    break;
                case 101:
                    break;
            }
            if (lfan->flags & 1) {
                fan_wp->count--;
            } else if (lfan->state != 0) {
                fan_wp->count--;
            }
            (*pose->mtx)[0][3] = lfan->pos.x;
            (*pose->mtx)[1][3] = lfan->pos.y;
            (*pose->mtx)[2][3] = lfan->pos.z;
            pose->dir = angleABf(target.x, target.z, lfan->pos.x, lfan->pos.z);
        }
    }
#endif
    psndSFX_pos(fan_wp->sfxId, &target);
    psndSFX_vol(fan_wp->sfxId, fan_wp->vol * fan_wp->count / fan_wp->num);
}
static __declspec(section ".rodata") Vec fan_zero = {0.0f, 0.0f, 0.0f};
#pragma opt_propagation reset
#pragma opt_lifetimes reset

/**
 * Loop spawned while the fans mob Mario (GF(10) set): every 2 to 7 s a fan's cry for Gonzales (stg3_tou_236 to
 * 240 and 240_01, in turn) pops up with its tail at a random spot (near Mario in the demos, within -50 to 150 of
 * the lobby centre in the releases); it ends once fewer than 10 fans are left.
 */
EVT_BEGIN(mario_momikucha_msg)
    SET_VALUE(LW(10), 0)
    LOOP(0)
        CALL(evt_sub_random, 5, LW(0))
        ADD(LW(0), 2)
        MULTIPLY(LW(0), 1000)
        WAIT_MS(LW(0))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_mario_get_pos, 0, LW(5), LW(7), LW(8))
        CALL(evt_sub_random, 100, LW(0))
        CALL(evt_sub_random, 100, LW(1))
#else
        CALL(evt_sub_random, 200, LW(0))
        CALL(evt_sub_random, 200, LW(1))
#endif
        SUBTRACT(LW(0), 50)
        SUBTRACT(LW(1), 50)
#if VERSION <= VERSION_DEMO_US
        ADD(LW(5), LW(0))
        ADD(LW(8), LW(1))
        CALL(evt_msg_toge, 2, LW(5), LW(7), LW(8))
#else
        CALL(evt_msg_toge, 2, LW(0), 30, LW(1))
#endif
        CALL(evt_end_count, LW(0))
        IF_INT_LESS(LW(0), 10)
            RETURN
        END_IF
        BEGIN_INLINE_EVENT
            SWITCH(LW(10))
                CASE_EQUAL(0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_236"), 0, 0)
                CASE_EQUAL(1)
                CALL(evt_msg_print, 0, STRING("stg3_tou_237"), 0, 0)
                CASE_EQUAL(2)
                CALL(evt_msg_print, 0, STRING("stg3_tou_238"), 0, 0)
                CASE_EQUAL(3)
                CALL(evt_msg_print, 0, STRING("stg3_tou_239"), 0, 0)
                CASE_EQUAL(4)
                CALL(evt_msg_print, 0, STRING("stg3_tou_240"), 0, 0)
                CASE_EQUAL(5)
                CALL(evt_msg_print, 0, STRING("stg3_tou_240_01"), 0, 0)
            END_SWITCH
        END_INLINE_EVENT
        ADD(LW(10), 1)
        IF_INT_GREATER(LW(10), 5)
            SET_VALUE(LW(10), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

/**
 * The lobby crowd scene, played once after the first match (GSWF_TOU02_LOBBY_CROWD_SEEN: the fans mob the
 * champion, who gets move_champ) and once when Mario is champion,
 * rank 0 (GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN: they
 * mob Mario, with mario_momikucha_msg). Registers the fan NPC models, then spawns the ext_fan entry with its
 * init/main/display callbacks.
 */
EVT_BEGIN(evt_momikucha)
    SET_VALUE(LF(0), 0)
    SET_VALUE(GF(10), 0)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_06_1ST_MATCH)
        IF_INT_EQUAL(GSWF(GSWF_TOU02_LOBBY_CROWD_SEEN), 0)
            SET_VALUE(GSWF(GSWF_TOU02_LOBBY_CROWD_SEEN), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 0)
        END_IF
    END_IF
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN), 0)
            SET_VALUE(GSWF(GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN), 1)
            SET_VALUE(LF(0), 1)
            SET_VALUE(GF(10), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        RETURN
    END_IF
    CALL(evt_npc_entry, STRING("fan"), STRING("c_kinopio"))
    CALL(evt_npc_entry, STRING("fan2"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("fan3"), STRING("c_jugemu"))
    CALL(evt_npc_set_position, STRING("fan"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("fan2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("fan3"), 0, -1000, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_ext_entry, 250, PTR(ext_fan_data), PTR(ext_fan_init), PTR(ext_fan_main), PTR(ext_fan_dispent))
#else
    CALL(evt_ext_entry, 200, PTR(ext_fan_data), PTR(ext_fan_init), PTR(ext_fan_main), PTR(ext_fan_dispent))
#endif
    IF_INT_EQUAL(GF(10), 0)
        CALL(evt_npc_set_position, STRING("チャンピョン"), 0, 0, 0)
        CALL(evt_npc_change_interrupt, STRING("チャンピョン"), 1, PTR(move_champ))
    ELSE
        SPAWN_EVENT(mario_momikucha_msg)
    END_IF
    RETURN
EVT_END()

/**
 * Pickup callback of the Storage Key that pops out of poster 8:
 * takes control, sets the story stage to STORY_STG3_20_14_LOBBY_POSTER, the partner remarks (stg3_tou_307_08),
 * then Mario gets a mail notification (vibration, jingle, "!" balloon until A is pressed), says stg3_tou_307_09,
 * receives mail 15 and opens it, and control returns.
 */
static EVT_BEGIN(evt_key)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_14_LOBBY_POSTER)
    CALL(evt_item_get_item_end_wait, STRING("key"))
    CALL(evt_party_stop, 0)
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_307_08"))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_09"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_pouch_receive_mail, 15)
    CALL(evt_pouch_open_mail, 15)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

/** Display-entry callback of the crowd: updates the poses (JP and later) and queues fan_disp. */
static void ext_fan_dispent(void) {
#if VERSION >= VERSION_JP
    pose_main();
#endif
    dispEntry(CAMERA_3D, 0.0f, 1, fan_disp, NULL);
}

// FAKE: optimisation pragmas: without them the function's code differs from the original (checked by removing them).
#pragma opt_propagation off
#pragma opt_lifetimes off
/**
 * Checks whether a fan is knocked away, only while Mario is on the ground: returns 1 when his hammer swing (more
 * than 10 frames in) lands within 35 of the fan 35 in front of him,
 * or his spin hammer (submotion 0x14) is within 65;
 * 2 when Flurrie's gust reaches within 30 of it; 0 otherwise. In JP and later, the fan standing in for Mario or
 * the champion (flags bit 1) is never hit.
 */
static s32 check_hammer(Fan* fan) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    f32 rot;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    Vec pos;

    if (mario->position.y > 0.0f) {
        return 0;
    }
#if VERSION >= VERSION_JP
    if (fan->flags & 1) {
        return 0;
    }
#endif
    if (mario->currMotionId == MARIO_MOTION_HAMMER && fan_wp->hammerTimer > 10) {
        rot = 6.2831855f * reviseAngle(mario->displayDirection - 90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;

        x = mario->position.x + 35.0f * fan_sin(rot);
        z = mario->position.z - 35.0f * fan_cos(rot);
        if (distABf(fan->pos.x, fan->pos.z, x, z) < 35.0f) {
            return 1;
        }
    }
    if (mario->currMotionId == MARIO_MOTION_HAMMER_2 && (s32)mario->currSubMotionId == 0x14 && PSVECDistance(&mario->position, &fan->pos) < 65.0f) {
        return 1;
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == PARTY_MEMBER_FLURRIE && (party->flags & PARTY_FLAG_IS_BEING_USED)) {
        angle = 6.2831855f * cloudGetBreathDir() / 360.0f;
        dist = cloudGetBreathDist();
        pos.x = party->position.x + dist * fan_sin(angle);
        pos.y = party->position.y;
        pos.z = party->position.z - dist * fan_cos(angle);
        if (angle >= 0.0f && PSVECDistance(&pos, &fan->pos) < 30.0f) {
            return 2;
        }
    }
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

/** Script helper: args[0] receives the number of fans still in the lobby crowd. */
static s32 evt_end_count(EventEntry* event, BOOL isFirstCall) {
    evtSetValue(event, event->args[0], fan_wp->count);
    return EVT_RETURN_DONE;
}

/** Run when Flurrie blows lobby poster 1 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_1_SEEN. */
static EVT_BEGIN(evt_poster_1)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_1_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 2 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_2_SEEN. */
static EVT_BEGIN(evt_poster_2)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_2_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 3 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_3_SEEN. */
static EVT_BEGIN(evt_poster_3)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_3_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 4 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_4_SEEN. */
static EVT_BEGIN(evt_poster_4)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_4_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 5 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_5_SEEN. */
static EVT_BEGIN(evt_poster_5)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_5_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 6 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_6_SEEN. */
static EVT_BEGIN(evt_poster_6)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_6_SEEN), 1)
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 7 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_7_SEEN. */
static EVT_BEGIN(evt_poster_7)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_7_SEEN), 1)
    RETURN
EVT_END()

/**
 * Run when Flurrie blows lobby poster 8 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_8_SEEN;
 * at STORY_STG3_20_13_MAJORS_1ST_PL it also makes the Storage Key (ITEM_STORAGE_KEY_0x13) pop out of the poster
 * (the English poster object p_m_8_e in non-Japanese languages from the US version on),
 * launched up and bouncing, with evt_key as its pickup callback.
 */
static EVT_BEGIN(evt_poster_8)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_8_SEEN), 1)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_13_MAJORS_1ST_PL)
#if VERSION <= VERSION_JP
        CALL(evt_mapobj_get_position, STRING("p_m_8"), LW(0), LW(1), LW(2))
#else
        CALL(evt_sub_get_language, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_mapobj_get_position, STRING("p_m_8"), LW(0), LW(1), LW(2))
        ELSE
            CALL(evt_mapobj_get_position, STRING("p_m_8_e"), LW(0), LW(1), LW(2))
        END_IF
#endif
        CALL(evt_item_entry, STRING("key"), ITEM_STORAGE_KEY_0x13, LW(0), LW(1), LW(2), ITEM_ENTRY_LAUNCH, -1, PTR(evt_key))
        CALL(evt_item_set_move_dir_speed, STRING("key"), FLOAT(180.0f), FLOAT(90.0f))
        CALL(evt_item_set_gravity, STRING("key"), FLOAT(1.0f))
        CALL(evt_item_set_bound_rate, STRING("key"), FLOAT(0.5996094f))
        CALL(evt_item_set_jump_power, STRING("key"), FLOAT(500.0f))
        CALL(evt_item_status_on, STRING("key"), ITEM_STATUS_CUSTOM_LAUNCH)
    END_IF
    RETURN
EVT_END()

/** Run when Flurrie blows lobby poster 9 away (registered with evt_cloud_ent): sets GSWF_TOU02_POSTER_9_SEEN. */
static EVT_BEGIN(evt_poster_9)
    SET_VALUE(GSWF(GSWF_TOU02_POSTER_9_SEEN), 1)
    RETURN
EVT_END()

/**
 * Lobby scene spawned right after the Champ's Belt is taken away and the party healed (the Peach interlude):
 * Mario and the partner appear in the lobby with the doors hidden,
 * Jolene (キノシコワ) speaks (stg3_tou_479_00_01 to 05) with the champion and the Shady Koopa answering,
 * Mario nods and cheers, then they walk out and the map changes to tou_01 (bero a_door_mon).
 */
static EVT_BEGIN(evt_after_peach)
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 0, 11)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_set_dir, 270, 0, 0)
    CALL(evt_party_set_dir, 0, 270, 0)
    CALL(evt_mario_set_pos, 25, 0, 75)
    CALL(evt_party_set_pos, 0, 60, 0, 100)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("door_1_a"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("door_1_b"), MAPOBJ_FLAG_HIDE)
    CALL(evt_seq_wait, 2)
    CALL(evt_bero_exec_wait, 65536)
    CALL(evt_fade_end_wait)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_01"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_02"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -40, 100, 395, -40, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_03"), 0, STRING("チャンピョン"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_04"), 0, STRING("ウラノコ"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 100, 395, 0, 40, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_479_00_05"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_cam3d_evt_set, 0, 120, 494, 0, 40, 0, 500, 11)
    CALL(evt_party_run, 0)
    CALL(evt_mario_mov_pos2, 0, 190, FLOAT(80.0f))
    CALL(evt_bero_mapchange, STRING("tou_01"), STRING("a_door_mon"))
    RETURN
EVT_END()

/**
 * Map init for tou_02, the lobby: music and ambience by story stage,
 * NPCs (guards, reporters, spectators, the champion),
 * and the first-visit scenes (evt_tougi2, evt_momikucha, doors to tou_01, tou_03 and tou_04).
 */
EVT_BEGIN(tou_02_init_evt)
    // Music: the lobby theme early in the chapter and after it, the main Glitz Pit theme in between.
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG3_00_WELCOME_TO_GLITZVILLE, STORY_STG3_12_MINI_YOSHI_EGG)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_GREATER_OR_EQUAL(STORY_STG3_33_PEACH_THE_SECRET_WEAPON)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
    END_SWITCH
    // Entrances; coming back from the arena intro plays evt_tougi2.
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSWF(GSWF_TOU_ARENA_INTRO_TO_LOBBY), 1)
        CALL_CHILD(bero_case_entry)
        SPAWN_EVENT(evt_tougi2)
    ELSE
        CALL_CHILD(evt_bero_info_run)
    END_IF
    // NPCs and the Star Piece panel.
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL_CHILD(init_kinopio_f)
    CALL(evt_npc_change_interrupt, STRING("キノピオ女"), 6, PTR(talk_kinopio_f))
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -260, 0, -120, STRING("sita"), 125, GSWF(GSWF_TOU02_STAR_PIECE_PANEL))
    // The guards keep the corridor doors shut until they step aside.
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_02_THE_GUARD_BACKS_OFF)
        SET_VALUE(LW(0), 3)
        CALL_CHILD(bero_case_switch_off)
        SET_VALUE(LW(0), 4)
        CALL_CHILD(bero_case_switch_off)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
        IF_INT_EQUAL(GSWF(GSWF_TOU02_GUARDS_STEP_ASIDE), 0)
            SET_VALUE(LW(0), 3)
            CALL_CHILD(bero_case_switch_off)
            SET_VALUE(LW(0), 4)
            CALL_CHILD(bero_case_switch_off)
        END_IF
    END_IF
    // After the Peach interlude: the party is healed, the Champ's Belt is taken and Jolene's scene plays.
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        IF_INT_EQUAL(GSWF(GSWF_TOU_LEFT_AS_CHAMPION), 0)
            CALL(evt_npc_set_position, STRING("キノピオ女"), 0, -1000, 0)
            CALL(evt_npc_set_position, STRING("キノピオ４"), 0, -1000, 0)
        END_IF
    END_IF
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_33_06_BOWSER_PUNI_ELDER)
        CALL(evt_mario_get_party, LW(15))
#if VERSION <= VERSION_JP
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
            CALL(evt_pouch_mario_recovery)
            CALL(evt_pouch_all_party_recovery)
        END_IF
#else
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_mario_set_party, 0, 1)
            CALL(evt_party_run, 0)
        END_IF
        CALL(evt_pouch_mario_recovery)
        CALL(evt_pouch_all_party_recovery)
        CALL(N_evt_sub_status_gauge_force_update)
#endif
        CALL(evt_pouch_remove_item, ITEM_CHAMPS_BELT, LW(0))
        SPAWN_EVENT(evt_after_peach)
        SET_VALUE(GSWF(GSWF_TOU02_LOBBY_CROWD_SEEN), 1)
        SET_VALUE(GSWF(GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN), 1)
    END_IF
    // The big screen's animation and its sounds.
    CALL(evt_map_playanim, STRING("anm_paneru"), 1, 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_LESS(LW(1), 5333)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN2"), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(10)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN1"), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_LESS(LW(1), 2000)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN2"), 178, 0, -98, 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            WAIT_FRAMES(5)
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_AMB_OBJ_SCREEN1"), 178, 0, -98, 0)
            LOOP(0)
                CALL(evt_map_checkanim, STRING("anm_paneru"), LW(0), LW(1))
                IF_INT_GREATER(LW(1), 6333)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
    END_INLINE_EVENT
    // The fan crowd scene.
    CALL_CHILD(evt_momikucha)
    // Wall posters by Mario's rank (none in the minors, one in the majors, eight more in the top two),
    // each blown away by Flurrie once.
#if VERSION <= VERSION_JP
    CALL(evt_tou_get_ranking, LW(0))
    SWITCH(LW(0))
        CASE_LESS(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 1)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_2_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_2"), STRING("a_p_m_2"), PTR(evt_poster_2))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_2"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_2"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_3_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_3"), STRING("a_p_m_3"), PTR(evt_poster_3))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_3"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_3"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_4_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_4"), STRING("a_p_m_4"), PTR(evt_poster_4))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_4"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_4"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_5_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_5"), STRING("a_p_m_5"), PTR(evt_poster_5))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_5"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_5"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_6_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_6"), STRING("a_p_m_6"), PTR(evt_poster_6))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_6"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_6"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_7_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_7"), STRING("a_p_m_7"), PTR(evt_poster_7))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_7"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_7"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_8_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_8"), STRING("a_p_m_8"), PTR(evt_poster_8))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_8"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_8"), 1, 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_9_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_9"), STRING("a_p_m_9"), PTR(evt_poster_9))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_9"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_9"), 1, 0)
        END_IF
        CASE_LESS(11)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 1)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
        CALL(evt_cloud_init)
        IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_1_SEEN), 0)
            CALL(evt_cloud_ent, 0, STRING("p_m_1"), STRING("a_p_m_1"), PTR(evt_poster_1))
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_1"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_m_1"), 1, 0)
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
        CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
    END_SWITCH
#else
    CALL(evt_sub_get_language, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1_e"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2_e"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3_e"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_LESS(2)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 1)
            CALL(evt_cloud_init)
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_2_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_2"), STRING("a_p_m_2"), PTR(evt_poster_2))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_2"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_2"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_3_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_3"), STRING("a_p_m_3"), PTR(evt_poster_3))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_3"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_3"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_4_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_4"), STRING("a_p_m_4"), PTR(evt_poster_4))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_4"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_4"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_5_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_5"), STRING("a_p_m_5"), PTR(evt_poster_5))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_5"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_5"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_6_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_6"), STRING("a_p_m_6"), PTR(evt_poster_6))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_6"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_6"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_7_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_7"), STRING("a_p_m_7"), PTR(evt_poster_7))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_7"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_7"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_8_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_8"), STRING("a_p_m_8"), PTR(evt_poster_8))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_8"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_8"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_9_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_9"), STRING("a_p_m_9"), PTR(evt_poster_9))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_9"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_9"), 1, 0)
            END_IF
            CASE_LESS(11)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 1)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
            CALL(evt_cloud_init)
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_1_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_1"), STRING("a_p_m_1"), PTR(evt_poster_1))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_1"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_1"), 1, 0)
            END_IF
            CASE_DEFAULT
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_1"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
        END_SWITCH
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_tou_get_ranking, LW(0))
        SWITCH(LW(0))
            CASE_LESS(2)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_3_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 1)
            CALL(evt_cloud_init)
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_2_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_2_e"), STRING("a_p_m_2"), PTR(evt_poster_2))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_2_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_2"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_3_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_3_e"), STRING("a_p_m_3"), PTR(evt_poster_3))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_3_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_3"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_4_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_4_e"), STRING("a_p_m_4"), PTR(evt_poster_4))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_4_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_4"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_5_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_5_e"), STRING("a_p_m_5"), PTR(evt_poster_5))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_5_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_5"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_6_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_6_e"), STRING("a_p_m_6"), PTR(evt_poster_6))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_6_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_6"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_7_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_7_e"), STRING("a_p_m_7"), PTR(evt_poster_7))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_7_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_7"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_8_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_8_e"), STRING("a_p_m_8"), PTR(evt_poster_8))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_8_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_8"), 1, 0)
            END_IF
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_9_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_9_e"), STRING("a_p_m_9"), PTR(evt_poster_9))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_9_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_9"), 1, 0)
            END_IF
            CASE_LESS(11)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_1_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_2_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 1)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
            CALL(evt_cloud_init)
            IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_1_SEEN), 0)
                CALL(evt_cloud_ent, 0, STRING("p_m_1_e"), STRING("a_p_m_1"), PTR(evt_poster_1))
            ELSE
                CALL(evt_mapobj_flag_onoff, MAPOBJ_SINGLE, 1, STRING("p_m_1_e"), MAPOBJ_FLAG_HIDE)
                CALL(evt_hitobj_onoff, STRING("a_p_m_1"), 1, 0)
            END_IF
            CASE_DEFAULT
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("p_p_1_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_2_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("p_p_3_e"), MAPOBJ_FLAG_HIDE)
            CALL(evt_hitobj_onoff, STRING("a_p_p_2"), 1, 0)
            CALL(evt_hitobj_onoff, STRING("a_p_p_3"), 1, 0)
        END_SWITCH
    END_IF
#endif
    // If poster 8 was blown away at this stage, the Storage Key lies where it fell.
    IF_INT_EQUAL(GSWF(GSWF_TOU02_POSTER_8_SEEN), 1)
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_13_MAJORS_1ST_PL)
            CALL(evt_item_entry, STRING("key"), ITEM_STORAGE_KEY_0x13, -110, 200, -180, ITEM_ENTRY_FIXED, -1, PTR(evt_key))
        END_IF
    END_IF
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_kaidan_7"), MAPOBJ_FLAG_BBOX_CULL)
    RETURN
EVT_END()
