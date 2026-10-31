// tou_12 (闘技場, Glitz Pit): the back room reached from the storage room tou_06.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_npc.h"
#include "evt/evt_eff.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "tou.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

/**
 * Door animation callback for the west door (door_1), opening: LW(0) is the swing angle;
 * turns door_1 about the Y axis by -0.44 times the angle.
 */
static EVT_BEGIN(w_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Door animation callback for the west door (door_1), closing:
 * turns door_1 about the Y axis by 0.44 times the angle.
 */
static EVT_BEGIN(w_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
    RETURN
EVT_END()

/** The one door of this room: the west door back to the storage room tou_06. */
static BeroEntry bero_data[] = {
    {
        "w_bero", // hitName
        1, // type
        4, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "tou_06", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {0},
};

/**
 * Scene when Mario steps into the back room: Jolene (キノシコワ) stands by the half-open door,
 * notices him and runs out (a "!" balloon, then she leaves toward x=-250 and the door slams shut with a wood
 * sound); the partner remarks stg3_tou_307_13_00 and control returns.
 */
static EVT_BEGIN(evt_kinoshikowa)
    CALL(evt_npc_set_position, STRING("キノシコワ"), -200, 0, 10)
    CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, 30, 0)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), -55)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_eff_fukidashi, 1, 0, STRING("キノシコワ"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
        CALL(evt_npc_move_position, STRING("キノシコワ"), -250, 10, 0, FLOAT(80.0f), 1)
    END_INLINE_EVENT
    CALL(evt_mapobj_get_position, STRING("door_1"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD2"), LW(0), LW(1), LW(2), 0)
    SET_VALUE(LW(0), 30)
    LOOP(10)
        SUBTRACT(LW(0), 3)
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_307_13_00"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

/**
 * Run when the block is broken and the flattened fighters are revealed:
 * the partner walks to (95, 10) with the surprised jingle and remarks stg3_tou_307_10,
 * Brots' dummy (ブロッツダミー) says stg3_tou_307_11, evt_kinoshikowa runs
 * and the story advances to STORY_STG3_20_16_FLATTENED.
 */
static EVT_BEGIN(evt_block_broken)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_move_pos2, 0, 95, 10, FLOAT(80.0f))
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SURPRISED2"))
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_party_set_dir, 0, 270, 200)
#else
    CALL(evt_party_set_dir, 0, 90, 200)
#endif
    WAIT_MS(300)
    CALL(evt_msg_print_party, STRING("stg3_tou_307_10"))
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_11"), 0, STRING("ブロッツダミー"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    SPAWN_EVENT(evt_kinoshikowa)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_16_FLATTENED)
    RETURN
EVT_END()

/**
 * NPC init for Michel (マイケル, a Koopa fighter): before STORY_STG3_32_BOSS_BATTLE he lies flattened at (175, 0,
 * -20) in the "NKT_Z_1" pose, rotated 80 degrees.
 */
static EVT_BEGIN(init_michel)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_npc_set_anim, STRING("マイケル"), STRING("NKT_Z_1"))
        CALL(evt_npc_set_position, STRING("マイケル"), 175, 0, -20)
        CALL(evt_npc_set_rotate, STRING("マイケル"), -80, 0, 0)
    END_IF
    RETURN
EVT_END()

/**
 * NPC init for the Michel stand-in (マイケルダミー), a hidden NPC that carries Michel's talk script:
 * before STORY_STG3_32_BOSS_BATTLE it is placed at (175, 0, -20), where the flattened Michel lies,
 * so talking there reaches him.
 */
EVT_BEGIN(init_michel_dummy)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_npc_set_position, STRING("マイケルダミー"), 175, 0, -20)
    END_IF
    RETURN
EVT_END()

/** Talk script of Michel: says stg3_tou_307_14_01. */
static EVT_BEGIN(talk_michel)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_14_01"), 0, STRING("マイケル"))
    RETURN
EVT_END()

/**
 * NPC init for Brots (ブロッツ): before STORY_STG3_32_BOSS_BATTLE he lies flattened at (110, 3, -60), rotated,
 * in the "S_1" pose, or the "X_1" pose once Mario has talked to him (GSWF_TOU12_FLATTENED_FIGHTER_TALK).
 */
static EVT_BEGIN(init_brots)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_npc_set_position, STRING("ブロッツ"), 110, 3, -60)
        CALL(evt_npc_set_rotate, STRING("ブロッツ"), -70, 0, -80)
        CALL(evt_npc_flag_onoff, 0, STRING("ブロッツ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_set_anim, STRING("ブロッツ"), STRING("S_1"))
        IF_INT_EQUAL(GSWF(GSWF_TOU12_FLATTENED_FIGHTER_TALK), 1)
            CALL(evt_npc_set_anim, STRING("ブロッツ"), STRING("X_1"))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * NPC init for the Brots stand-in (ブロッツダミー), a hidden NPC that carries Brots's talk script:
 * before STORY_STG3_32_BOSS_BATTLE it is placed at (125, 4, -60), next to where the flattened Brots lies,
 * so talking there reaches him.
 */
EVT_BEGIN(init_brots_dummy)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_npc_set_position, STRING("ブロッツダミー"), 125, 4, -60)
    END_IF
    RETURN
EVT_END()

/**
 * Talk script of the flattened Brots: the first time the partner is stopped and turns to him,
 * he speaks (stg3_tou_307_12), faints into the "X_1" pose and the partner comments (stg3_tou_307_13),
 * setting GSWF_TOU12_FLATTENED_FIGHTER_TALK; afterwards he only says stg3_tou_307_14.
 */
static EVT_BEGIN(talk_brots)
    IF_INT_EQUAL(GSWF(GSWF_TOU12_FLATTENED_FIGHTER_TALK), 0)
        CALL(evt_party_cont_onoff, 0, 0)
        CALL(evt_party_set_breed_pose, 0, 1)
        CALL(evt_npc_get_position, STRING("ブロッツ"), LW(0), LW(1), LW(2))
        CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
        IF_INT_LESS(LW(0), LW(3))
            CALL(evt_party_set_dir, 0, 270, 200)
        ELSE
            CALL(evt_party_set_dir, 0, 90, 200)
        END_IF
        CALL(evt_npc_flag_onoff, 1, STRING("ブロッツ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_msg_print, 0, STRING("stg3_tou_307_12"), 0, 0)
        CALL(evt_npc_flag_onoff, 0, STRING("ブロッツ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_set_anim, STRING("ブロッツ"), STRING("X_1"))
        CALL(evt_msg_print_party, STRING("stg3_tou_307_13"))
        SET_VALUE(GSWF(GSWF_TOU12_FLATTENED_FIGHTER_TALK), 1)
        CALL(evt_party_cont_onoff, 0, 1)
    ELSE
        CALL(evt_npc_flag_onoff, 0, STRING("ブロッツ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_set_anim, STRING("ブロッツ"), STRING("S_1"))
        CALL(evt_msg_print, 0, STRING("stg3_tou_307_14"), 0, 0)
        CALL(evt_npc_set_anim, STRING("ブロッツ"), STRING("X_1"))
    END_IF
    RETURN
EVT_END()

/** NPC init for Jolene (キノシコワ) in this room: does nothing. */
static EVT_BEGIN(init_kinoshikowa)
    RETURN
EVT_END()

/** Talk script of Jolene in this room: does nothing. */
static EVT_BEGIN(talk_kinoshikowa)
    RETURN
EVT_END()

/**
 * NPCs of this room: the flattened King K and Bandy Andy, the hidden stand-ins that carry their talk scripts,
 * and Jolene.
 */
static NpcSetupInfo npcEnt[] = {
    {
        "マイケル", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_NO_TURN_TO_MARIO | NPC_FLAG_INTANGIBLE, // flags
        0, // reactionFlags
        init_michel, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ブロッツ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_NO_TURN_TO_MARIO | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_INTANGIBLE, // flags
        0, // reactionFlags
        init_brots, // initEvent
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, // regularEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マイケルダミー", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_NO_TURN_TO_MARIO | NPC_FLAG_HIDDEN, // flags
        0, // reactionFlags
        init_michel_dummy, // initEvent
        NULL, // regularEvent
        talk_michel, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ブロッツダミー", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_NO_TURN_TO_MARIO | NPC_FLAG_HIDDEN, // flags
        0, // reactionFlags
        init_brots_dummy, // initEvent
        NULL, // regularEvent
        talk_brots, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノシコワ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        init_kinoshikowa, // initEvent
        NULL, // regularEvent
        talk_kinoshikowa, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Map init for tou_12, the back room beside the storage room:
 * music by story stage, NPCs, a Star Piece, and the big block that Mario breaks open until the boss battle.
 */
EVT_BEGIN(tou_12_init_evt)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_31_GRUBBAS_PLANS)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envoff, PSND_FADE_OUT)
    ELSE
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_BETWEEN(STORY_STG3_00_WELCOME_TO_GLITZVILLE, STORY_STG3_12_MINI_YOSHI_EGG)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_JP
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
#endif
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
            CASE_GREATER_OR_EQUAL(STORY_STG3_33_PEACH_THE_SECRET_WEAPON)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU2"))
#if VERSION <= VERSION_DEMO_JP
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU2"))
#else
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
#endif
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
            CASE_DEFAULT
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
        END_SWITCH
    END_IF
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_item_entry, STRING("item01"), ITEM_STAR_PIECE, 190, 0, 30, ITEM_ENTRY_FIXED, GSWF(GSWF_TOU12_STAR_PIECE), 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_16_FLATTENED)
        CALL(evt_mobj_lv_blk, STRING("aa"), 125, 0, 0, PTR(evt_block_broken), GSWF(GSWF_TOU12_BIG_BLOCK_BROKEN), STRING("MOBJ_Lv1BigBigBlock"))
        CALL(evt_mobj_flag_onoff, 0, STRING("aa"), MOBJ_FLAG_FALL)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("gor_hae"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_map_playanim, STRING("anm_hae"), 1, 0)
        BEGIN_INLINE_EVENT
            LOOP(0)
                CALL(evt_sub_random, 1000, LW(0))
                ADD(LW(0), 3000)
                WAIT_MS(LW(0))
                CALL(evt_mapobj_get_position, STRING("gor_hae"), LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_FLY1"), LW(0), LW(1), LW(2), 0)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    RETURN
EVT_END()
