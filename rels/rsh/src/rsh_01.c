// rsh_01 (列車, Excess Express): car joining the driver's cab (rsh_00) and rsh_02: Toron, Madam, conductor, cook and
// waitress NPCs; doors to Rogueport (gor_04), Riverside (hom_00) and Poshley Heights (pik_00) stations.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "rsh.h"
#include "evt/evt_npc.h"
#include "mario/mario_pouch.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_fade.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_window.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"

extern EvtWord s_bero_close[];
extern EvtWord s_bero_open[];
static BeroEntry bero_data_a[4];
static BeroEntry bero_data_b[4];
static BeroEntry bero_data_c[4];
static const char* door_3[7];
static const char* door_4[7];
static s32 item_tbl_madam[2];
static NpcSetupInfo npc_data[7];
NpcSetupInfo npc_data_2[3];
extern EvtWord evt_pikary_arrival[];
#if VERSION <= VERSION_DEMO_JP
static const char* access_tbl[5];
#else
static const char* access_tbl[7];
#endif
extern EvtWord rsh_01_init_evt[];
static const char* window_tbl[3];
extern EvtWord talk_syasyou[];
static BeroEntry bero_data_a_return[4];
static BeroEntry bero_data_b_return[4];
static BeroEntry bero_data_c_return[4];
BeroEntry gor_bero[2];
extern EvtWord rsh_01_init_evt_nidome[];

/**
 * Enter animation of the south door (s_bero) of rsh_01:
 * slides the s_tobira door object by the door animation's progress value in LW(0), scaled by -0.333.
 */
EVT_BEGIN(s_bero_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.3330078f))
    CALL(evt_mapobj_trans, 0, STRING("s_tobira"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Exit animation of the south door (s_bero) of rsh_01:
 * slides the s_tobira door object by the door animation's progress value in LW(0),
 * scaled by -0.333 (same motion as s_bero_close).
 */
EVT_BEGIN(s_bero_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.3330078f))
    CALL(evt_mapobj_trans, 0, STRING("s_tobira"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Doors and exits of rsh_01 variant a: w_bero to rsh_02_a; e_bero to rsh_00_a; s_bero to pik_00 (Poshley
 * Heights).
 */
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
        "rsh_02_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_00_a", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        17, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "pik_00", // nextMapName
        "n_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/**
 * Doors and exits of rsh_01 variant b: w_bero to rsh_02_b; e_bero to rsh_00_b; s_bero to hom_00 (Excess
 * Express platform).
 */
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
        "rsh_02_b", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_00_b", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        17, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "hom_00", // nextMapName
        "n_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/** Doors and exits of rsh_01 variant c: w_bero to rsh_02_c; e_bero to rsh_00_c; s_bero to rsh_01_c. */
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
        "rsh_02_c", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_00_c", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        17, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_01_c", // nextMapName
        "s_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/**
 * Map objects of cabin 3 for evt_rsh_door_entry: the room, backdrop, door, door hit areas and open and close
 * animations.
 */
static const char* door_3[] = {
    "heya_3",
    "haikei_3",
    "tobira_3",
    "a_tobira_3",
    "3_door_open",
    "a_tobira_3_heya",
    "3_door_close",
};

/**
 * Map objects of cabin 4 for evt_rsh_door_entry: the room, backdrop, door, door hit areas and open and close
 * animations.
 */
static const char* door_4[] = {
    "heya_4",
    "haikei_4",
    "tobira_4",
    "a_tobira_4",
    "4_door_open",
    "a_tobira_4_heya",
    "4_door_close",
};

/**
 * Init event of Zip Toad (Toron) in rsh_01: places him at (-45, 0, -175) before the first stage
 * and again from the Galley Pot stage to the end of day 1; at other stages he is parked below the floor.
 */
static EVT_BEGIN(init_toron)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_01_THE_CONDUCTOR)
        CALL(evt_npc_set_position, STRING("me"), -45, 0, -175)
        CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED, STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_npc_set_position, STRING("me"), -45, 0, -175)
        CASE_BETWEEN(STORY_STG6_21_DAY_2, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

/**
 * Talk script of Zip Toad (Toron) in rsh_01: first meeting (stg6_rsh_09, 10), then lines by story stage.
 * Between STORY_STG6_09_BUBS_REQUEST and STORY_STG6_12_GIVE_AUTOGRAPH he gives the autograph hint
 * and sets GSWF_RSH01_TORON_AUTOGRAPH_TALK.
 */
static EVT_BEGIN(talk_toron)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        IF_INT_EQUAL(GSWF(GSWF_RSH01_TORON_FIRST_TALK), 0)
            SET_VALUE(GSWF(GSWF_RSH01_TORON_FIRST_TALK), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_09"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_10"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_09_BUBS_REQUEST)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_61"), 0, 0)
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_106"), 0, 0)
        SET_VALUE(GSWF(GSWF_RSH01_TORON_AUTOGRAPH_TALK), 1)
        CALL_CHILD(evt_rsh_konarikin_irai_party_talk)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_61"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_02"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

/** Init event of Madam: places her at (-275, 0, -225) before day 3; later she is parked below the floor. */
static EVT_BEGIN(init_madam)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_45_DAY_3_STARTS)
        CALL(evt_npc_set_position, STRING("me"), -275, 0, -225)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_48_01_ARRIVING_AT_POSHLEY)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

/** Items the player may give the madam: the Gold Ring only, ended by -1. */
static s32 item_tbl_madam[] = {
    ITEM_GOLD_RING, -1,
};

/**
 * Talk script used when Mario holds a Gold Ring: opens the item menu;
 * giving the ring pays Mario 30 coins and she thanks him (stg6_rsh_201, 202), cancelling prints stg6_rsh_201_2,
 * then the music dip is restored.
 */
static EVT_BEGIN(talk_madam_ring_return)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_200"), 0, STRING("マダム"))
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_win_item_select, PTR(item_tbl_madam), LW(1))
#else
    CALL(evt_win_item_select, 0, PTR(item_tbl_madam), LW(1), 0)
#endif
    IF_INT_NOT_EQUAL(LW(1), -1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_201"), 0, STRING("マダム"))
        CALL(evt_sub_get_coin, 30)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_202"), 0, STRING("マダム"))
        CALL(evt_pouch_remove_item, ITEM_GOLD_RING, LW(0))
    ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_201_2"), 0, STRING("マダム"))
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_BETWEEN(STORY_STG6_49_POSHLEY_HEIGHTS, STORY_STG6_55_04_BOWSER_RAWK_HAWK)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk script of Madam.
 * From STORY_STG6_06_PENNINGTONS_ASSISTANT, until she has been helped,
 * she asks Mario for help (stg6_rsh_80 to 83, yes/no, GSWF_RSH_TOODLES_HELP_ACCEPTED) with a music dip;
 * otherwise, or when Mario carries a Gold Ring,
 * she offers the ring return (talk_madam_ring_return) or says a line for the story stage.
 */
static EVT_BEGIN(talk_madam)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_06_PENNINGTONS_ASSISTANT)
        IF_INT_EQUAL(GSWF(GSWF_RSH_TOODLES_HELP_ACCEPTED), 0)
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
            IF_INT_EQUAL(GSWF(GSWF_RSH_TOODLES_ASKED_HELP), 0)
                SET_VALUE(GSWF(GSWF_RSH_TOODLES_ASKED_HELP), 1)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_80"), 0, 0)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg6_rsh_83"), 0, 0)
            END_IF
            CALL(evt_msg_select, 0, STRING("stg6_rsh_83_yn"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_81"))
                SET_VALUE(GSWF(GSWF_RSH_TOODLES_HELP_ACCEPTED), 1)
            ELSE
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_82"))
            END_IF
            SWITCH(GSW(GSW_STORY_PROGRESS))
                CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
                CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
                CASE_BETWEEN(STORY_STG6_49_POSHLEY_HEIGHTS, STORY_STG6_55_04_BOWSER_RAWK_HAWK)
                CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
                CASE_DEFAULT
                CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
            END_SWITCH
            RETURN
        END_IF
    END_IF
    CALL(evt_pouch_check_item, ITEM_GOLD_RING, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(talk_madam_ring_return)
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_11"), 0, 0)
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_53"), 0, 0)
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_62"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_84"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_03"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_160"), 0, 0)
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        IF_INT_EQUAL(GSWF(GSWF_RSH01_TOODLES_POSTSTORY_TALK), 0)
            SET_VALUE(GSWF(GSWF_RSH01_TOODLES_POSTSTORY_TALK), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_204"), 0, 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_205"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_205"), 0, 0)
        END_IF
        CALL(evt_msg_select, 0, STRING("stg6_rsh_205_01"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_206"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_207"))
        END_IF
        CALL(evt_msg_print, 0, STRING("stg6_rsh_208"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_221"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

/** NPCs of the car on the first visit: Toron and the madam. */
static NpcSetupInfo npc_data[] = {
    {
        "トロン", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_toron, // initEvent
        NULL, // regularEvent
        talk_toron, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マダム", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
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
        "ポワン探偵", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "車掌", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "コック", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ウェイトレス", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/** Second NPC setup of the car, used by the later-story entries: Toron and the madam. */
NpcSetupInfo npc_data_2[] = {
    {
        "トロン", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_toron, // initEvent
        NULL, // regularEvent
        talk_toron, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マダム", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_madam, // initEvent
        NULL, // regularEvent
        talk_madam, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Trigger when Mario steps on the paper spot (a_kami) at STORY_STG6_22_DOCUMENT:
 * sets STORY_STG6_23_VITAL_PAPER and gives him the Vital Paper item with the item-get fanfare.
 */
static EVT_BEGIN(evt_daiji_kami)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yuka_3_kami"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("yuka_3"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_23_VITAL_PAPER)
    CALL(evt_item_entry, STRING("daiji"), ITEM_VITAL_PAPER, 0, 0, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_item_get_item, STRING("daiji"))
    CALL(evt_item_get_item_end_wait, STRING("daiji"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * Cutscene when the train pulls into Poshley Heights:
 * the conductor, waitress, cook and Detective Pennington are lined up around Mario,
 * each says a line (stg6_rsh_248 to 252), then the story advances to STORY_STG6_48_01_ARRIVING_AT_POSHLEY
 * and the map changes to pik_00 with an iris fade.
 */
EVT_BEGIN(evt_pikary_arrival)
    CALL(evt_npc_set_position, STRING("ポワン探偵"), -100, 0, 0)
    CALL(evt_npc_set_position, STRING("車掌"), 0, 0, 0)
    CALL(evt_npc_set_position, STRING("コック"), 30, 0, 10)
    CALL(evt_npc_set_position, STRING("ウェイトレス"), 50, 0, 40)
    CALL(evt_mario_set_pos, -35, 0, 30)
    CALL(evt_mario_set_dir_npc, STRING("ウェイトレス"))
    CALL(evt_party_set_pos, 0, -50, 0, 20)
    CALL(evt_party_set_dir_npc, 0, STRING("ウェイトレス"))
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_JUMPING | NPC_FLAG_LAND_ON_FLOOR)
    CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_JUMPING | NPC_FLAG_LAND_ON_FLOOR)
    CALL(evt_npc_flag_onoff, 1, STRING("コック"), NPC_FLAG_JUMPING | NPC_FLAG_LAND_ON_FLOOR)
    CALL(evt_npc_flag_onoff, 1, STRING("ウェイトレス"), NPC_FLAG_JUMPING | NPC_FLAG_LAND_ON_FLOOR)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_248"), 0, STRING("車掌"))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("ウェイトレス"), STRING("S_1"), STRING("T_4"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_249"), 0, STRING("ウェイトレス"))
    CALL(evt_npc_set_autotalkpose, STRING("ウェイトレス"), STRING("S_1"), STRING("T_1"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_250"), 0, STRING("コック"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_251"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_252"), 0, STRING("車掌"))
    WAIT_MS(300)
    WAIT_MS(1000)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_48_01_ARRIVING_AT_POSHLEY)
    CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_IRIS, 500, FADE_IN_IRIS, 500)
    CALL(evt_bero_mapchange, STRING("pik_00"), STRING("resha"))
    RETURN
EVT_END()

// The demo pairs each object with one message; the releases add a second message for it.
static const char* access_tbl[] = {
#if VERSION <= VERSION_DEMO_JP
    "tana_5",
    "stg6_rsh_262",
    "tana_4",
    "stg6_rsh_263",
#else
    "tana_5",
    "stg6_rsh_262",
    "stg6_rsh_267",
    "tana_4",
    "stg6_rsh_263",
    "stg6_rsh_267",
#endif
    NULL,
};

/**
 * Trigger script for the shelves (tana_4, tana_5):
 * locks input and prints the shelf's message, a different one (LW(2)) from the Rogueport station stage on in the
 * releases.
 */
static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_msg_print, 0, LW(1), 0, 0)
#else
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_56_ROGUEPORT_STATION)
        CALL(evt_msg_print, 0, LW(1), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, LW(2), 0, 0)
    END_IF
#endif
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Registers the shelf triggers from access_tbl (hit name and message rows);
 * each runs evt_access when Mario faces it.
 */
static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(&access_tbl))
    LOOP(0)
#if VERSION <= VERSION_DEMO_JP
        READ_INT2(LW(0), LW(1))
#else
        READ_INT3(LW(0), LW(1), LW(2))
#endif
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

/**
 * Shared map init for the three variants of rsh_01 on the first trip:
 * starts the scenery animations, registers the two cabin doors (heya 3 and 4)
 * and the shelf signs (tana_4, tana_5), closes the south door with the stg6_rsh_261 message,
 * and starts the music and ambience for the story stage (Pennington theme, Riverside, Poshley, danger theme,
 * or the per-variant train theme).
 */
EVT_BEGIN(rsh_01_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CASE_GREATER_OR_EQUAL(STORY_STG6_48_01_ARRIVING_AT_POSHLEY)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING("yure"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_sora"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_yama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_iwayama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_saboten"), 1, 0)
    END_SWITCH
    CALL_CHILD(evt_rsh_door_init)
    SET_VALUE(LW(0), PTR(&door_3))
    CALL_CHILD(evt_rsh_door_entry)
    SET_VALUE(LW(0), PTR(&door_4))
    CALL_CHILD(evt_rsh_door_entry)
    CALL_CHILD(evt_access_entry)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CASE_GREATER_OR_EQUAL(STORY_STG6_48_01_ARRIVING_AT_POSHLEY)
        CASE_DEFAULT
        SET_VALUE(LW(0), 2)
        CALL_CHILD(bero_case_switch_off)
        SET_VALUE(LW(1), STRING("stg6_rsh_261"))
#if VERSION >= VERSION_JP
        SET_VALUE(LW(2), STRING("stg6_rsh_261"))
#endif
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("s_bero"), 0, PTR(evt_access), 0)
    END_SWITCH
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_02_A_CASE_OF_LOST_STEW, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        CASE_BETWEEN(STORY_STG6_22_DOCUMENT, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_HOM1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_BETWEEN(STORY_STG6_44_END_OF_DAY_2, STORY_STG6_45_DAY_3_STARTS)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(STORY_STG6_46_ENGINEER, STORY_STG6_47_ESCAPING_THE_SMORGS)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        CASE_BETWEEN(STORY_STG6_49_POSHLEY_HEIGHTS, STORY_STG6_55_04_BOWSER_RAWK_HAWK)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        CASE_DEFAULT
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_01_a"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_01_b"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH3"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_01_c"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init script of rsh_01_a (first visit): sets the doors (during the Smorg miasma stage the west door is only a
 * case trigger), runs the shared init, swaps the paper and plain floors, starts the Smorg window effect,
 * gives the Vital Paper from the a_kami spot at STORY_STG6_22_DOCUMENT and,
 * if the story is before STORY_STG6_00_START, places Mario and the partner in the car and starts it.
 */
EVT_BEGIN(rsh_01_a_init_evt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_EQUAL(STORY_STG6_48_SMORG_MIASMA)
        SET_VALUE(LW(0), PTR(bero_data_a))
        CALL(evt_bero_get_info)
        CALL_CHILD(bero_case_entry)
        SPAWN_EVENT(evt_pikary_arrival)
        CASE_DEFAULT
        SET_VALUE(LW(0), PTR(bero_data_a))
        CALL(evt_bero_get_info)
        CALL_CHILD(evt_bero_info_run)
    END_SWITCH
    CALL(evt_npc_setup, PTR(npc_data))
    CALL_CHILD(rsh_01_init_evt)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_22_DOCUMENT)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("yuka_3_kami"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yuka_3"), MAPOBJ_FLAG_HIDE)
        CALL(evt_run_case_evt, CASE_COND_STAND_ON_A, 1, STRING("a_kami"), 0, PTR(evt_daiji_kami), 0)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yuka_3_kami"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("yuka_3"), MAPOBJ_FLAG_HIDE)
    END_IF
    CALL_CHILD(evt_rsh_moamoa_on_window)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SKIP_MAP_EVENTS)
        RETURN
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_00_START)
        CALL(evt_mario_set_pos, 100, 0, 0)
        CALL(evt_party_set_pos, 0, 130, 0, 0)
        CALL(evt_mario_set_dir, 90, 0, 0)
        CALL(evt_mario_adjust_dir)
        CALL(evt_cam_road_reset)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_00_START)
    END_IF
    RETURN
EVT_END()

/**
 * Init script of rsh_01_b (first visit): sets the doors,
 * sets up the car's NPCs (npc_data_2) and runs the shared init.
 */
EVT_BEGIN(rsh_01_b_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_npc_setup, PTR(npc_data_2))
    CALL_CHILD(rsh_01_init_evt)
    RETURN
EVT_END()

/** Map objects of the scenery that passes by the windows of the car. */
static const char* window_tbl[] = {
    "mado_uturi_3",
    "mado_uturi_4",
    NULL,
};

/**
 * Init script of rsh_01_c (first visit): sets the doors, sets up the car's NPCs (npc_data_2),
 * runs the shared init, plays the lamp animation and sets up the window scenery.
 */
EVT_BEGIN(rsh_01_c_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_npc_setup, PTR(npc_data_2))
    CALL_CHILD(rsh_01_init_evt)
    CALL(evt_map_playanim, STRING("ranpu"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    RETURN
EVT_END()

/**
 * Talk script of the conductor (syasyou) on the return trip (hooked in rsh_01_init_evt_nidome):
 * says stg6_rsh_c_14, or in the releases stg6_rsh_c_09_1 once the train has reached Rogueport.
 */
EVT_BEGIN(talk_syasyou)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_msg_print, 0, STRING("stg6_rsh_c_14"), 0, 0)
#else
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_14"), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_09_1"), 0, 0)
    END_IF
#endif
    RETURN
EVT_END()

/**
 * Doors and exits of rsh_01 variant a (return trip): w_bero to rsh_02_a; e_bero to rsh_08_a; s_bero to pik_00
 * (Poshley Heights).
 */
static BeroEntry bero_data_a_return[] = {
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
        "rsh_02_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_08_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "pik_00", // nextMapName
        "n_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/**
 * Doors and exits of rsh_01 variant b (return trip): w_bero to rsh_02_b; e_bero to rsh_08_a; s_bero to hom_00
 * (Excess Express platform).
 */
static BeroEntry bero_data_b_return[] = {
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
        "rsh_02_b", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_08_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "hom_00", // nextMapName
        "n_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/**
 * Doors and exits of rsh_01 variant c (return trip): w_bero to rsh_02_c; e_bero to rsh_08_a; s_bero to
 * rsh_01_c.
 */
static BeroEntry bero_data_c_return[] = {
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
        "rsh_02_c", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "w_door_close", // enterAnimeArg
        "w_door_open", // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "rsh_08_a", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {
        "s_bero", // hitName
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
        "s_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/** Replacement exit used when the train stands at Rogueport: s_bero leads to gor_04. */
BeroEntry gor_bero[] = {
    {
        "s_bero", // hitName
        1, // type
        8, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gor_04", // nextMapName
        "n_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_bero_close, // enterAnimeArg
        s_bero_open, // exitAnimeArg
    },
    {0},
};

/**
 * Shared map init for rsh_01 on the second visit (return trip after WELCOME_BACK):
 * plays the outbound or return-trip scenery, re-registers the cabin doors and shelf signs,
 * locks the south door while the train runs, picks the music for the station reached,
 * and spawns the random passengers.
 */
EVT_BEGIN(rsh_01_init_evt_nidome)
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
    CALL_CHILD(evt_rsh_door_init)
    SET_VALUE(LW(0), PTR(&door_3))
    CALL_CHILD(evt_rsh_door_entry)
    SET_VALUE(LW(0), PTR(&door_4))
    CALL_CHILD(evt_rsh_door_entry)
    CALL_CHILD(evt_access_entry)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_RIVERSIDE), 0)
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 0)
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
                BEGIN_INLINE_EVENT
                    CALL(evt_bero_exec_wait, 65536)
                    SET_VALUE(LW(0), STRING("s_bero"))
                    CALL_CHILD(bero_case_switch_off)
                    SET_VALUE(LW(1), STRING("stg6_rsh_261"))
#if VERSION >= VERSION_JP
                    SET_VALUE(LW(2), STRING("stg6_rsh_261"))
#endif
                    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("s_bero"), 0, PTR(evt_access), 0)
                END_INLINE_EVENT
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_POSHLEY), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
#if VERSION <= VERSION_DEMO_JP
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR5"))
#else
            CALL(evt_snd_envoff, PSND_FADE_OUT)
#endif
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        ELSE
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_01_a"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_01_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_01_c"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
            END_IF
        END_IF
    END_IF
    CALL_CHILD(evt_rsh_01_rnd_npc_entry)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 1)
        CALL(evt_npc_set_position, STRING("車掌"), 395, 0, -90)
        CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR)
        CALL(evt_npc_set_ry, STRING("車掌"), 270)
        CALL(evt_npc_change_interrupt, STRING("車掌"), 6, PTR(talk_syasyou))
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(bero_case_switch_off)
    END_IF
    RETURN
EVT_END()

/**
 * Init script of rsh_01_a on the second visit: uses the outbound doors or the return-trip doors,
 * runs rsh_01_init_evt_nidome, marks variant A active in GSWF_RSH_REVISIT_VARIANT_A and, at Rogueport,
 * replaces the south door with the exit to gor_04.
 */
EVT_BEGIN(rsh_01_a_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_a))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_a_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_01_init_evt_nidome)
    CALL(evt_npc_setup, PTR(npc_data_2))
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 1)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 0)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
        SET_VALUE(LW(0), STRING("s_bero"))
        CALL_CHILD(bero_case_switch_off)
        CALL(evt_bero_overwrite, STRING("s_bero"), PTR(gor_bero))
        SET_VALUE(LW(0), STRING("s_bero"))
        CALL_CHILD(bero_case_switch_on)
    END_IF
    RETURN
EVT_END()

/**
 * Init script of rsh_01_b on the second visit: outbound or return-trip doors, shared second-visit init,
 * and marks variant B active.
 */
EVT_BEGIN(rsh_01_b_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_b))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_b_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_01_init_evt_nidome)
    CALL(evt_npc_setup, PTR(npc_data_2))
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 1)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 0)
    RETURN
EVT_END()

/**
 * Init script of rsh_01_c on the second visit: outbound or return-trip doors, shared second-visit init,
 * and marks variant C active.
 */
EVT_BEGIN(rsh_01_c_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_c))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_c_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_01_init_evt_nidome)
    CALL(evt_npc_setup, PTR(npc_data_2))
    CALL(evt_map_playanim, STRING("ranpu"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 1)
    RETURN
EVT_END()
