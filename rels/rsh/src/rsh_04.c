// rsh_04 (列車, Excess Express): passenger car with compartments 3-5: Narikin family, conductor, salaryman and Powan
// detective NPCs, and a lost-documents event; doors to rsh_03, rsh_05 and rsh_07.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "mario/mario.h"
#include "driver/npcdrv.h"
#include "driver/itemdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_env.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "rsh.h"
#include "mario/mario_pouch.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_snd.h"
#include "party.h"
#include "evt/evt_sub.h"
#include "evt/evt_window.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"

static USER_FUNC(mario_flag);

static BeroEntry bero_data_a[3];
static BeroEntry bero_data_b[3];
static BeroEntry bero_data_c[3];
static const char* door_3[7];
static const char* door_4[7];
static const char* door_5[7];
extern EvtWord evt_allow_kamotsu[];
extern EvtWord evt_mario_chuumoku[];
extern EvtWord evt_party_chuumoku[];
extern EvtWord evt_shorui_funshitu[];
static s32 item_tbl[2];
extern EvtWord evt_daijisouna_kami[];
extern EvtWord evt_syasyou_auto_talk[];
static s32 item_tbl2[2];
extern EvtWord talk_sarary_repeat[];
extern EvtWord talk_papa_mama[];
extern EvtWord talk_papa_repeat[];
extern EvtWord talk_mama_repeat[];
s32 item_tbl3[2];
extern EvtWord talk_powan_repeat[];
static NpcSetupInfo npc_data[7];
extern EvtWord evt_tana_5[];
/* shelf access table read by READ_INT4: hit, msg, event, second msg (the demo reads three words with READ_INT3:
   it has no second message); a NULL hit ends it */
typedef struct ShelfAccess {
    const char* hit;
    const char* msg;
    EvtWord* evt;
#if VERSION >= VERSION_JP
    const char* msg2;
#endif
} ShelfAccess;
typedef struct ShelfAccessTbl3 {
    ShelfAccess rows[3];
    const char* end[1];
} ShelfAccessTbl3;
static ShelfAccessTbl3 access_tbl;
extern EvtWord evt_narikin_room[];
extern EvtWord evt_powan_room[];
extern EvtWord rsh_04_init_evt[];
static const char* window_tbl[4];
static BeroEntry bero_data_a_return[3];
static BeroEntry bero_data_b_return[3];
static BeroEntry bero_data_c_return[3];
extern EvtWord rsh_04_init_evt_nidome[];

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
        "rsh_05_a", // nextMapName
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
        "rsh_03_a", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
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
        "rsh_05_a", // nextMapName
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
        "rsh_03_b", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
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
        "rsh_05_a", // nextMapName
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
        "rsh_03_c", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

static const char* door_3[] = {
    "heya_3",
    "haikei_3",
    "tobira_3",
    "a_tobira_3",
    "3_door_open",
    "a_tobira_3_heya",
    "3_door_close",
};

static const char* door_4[] = {
    "heya_4",
    "haikei_4",
    "tobira_4",
    "a_tobira_4",
    "4_door_open",
    "a_tobira_4_heya",
    "4_door_close",
};

static const char* door_5[] = {
    "heya_5",
    "haikei_5",
    "tobira_5",
    "a_tobira_5",
    "5_door_open",
    "a_tobira_5_heya",
    "5_door_close",
};

EVT_BEGIN(evt_rsh_konarikin_irai_party_talk)
    IF_INT_EQUAL(GSWF(GSWF_RSH04_CONDUCTOR_AUTOGRAPH_TALK), 0)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_RSH01_TORON_AUTOGRAPH_TALK), 0)
        RETURN
    END_IF
    CALL(evt_party_stop, 0)
    WAIT_MS(300)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_0"), 0, STRING("party"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_1"), 0, STRING("party"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_2"), 0, STRING("party"))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_3"), 0, STRING("party"))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_4"), 0, STRING("party"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_5"), 0, STRING("party"))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_107_6"), 0, STRING("party"))
    END_SWITCH
    CALL(evt_party_run, 0)
#if VERSION >= VERSION_US
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
#endif
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
#if VERSION >= VERSION_US
    END_IF
#endif
    RETURN
EVT_END()

EVT_BEGIN(evt_allow_kamotsu)
#if VERSION >= VERSION_US
    CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_INTANGIBLE)
#endif
    CALL(evt_mario_mov_pos, -360, -100, 500)
    CALL(evt_mario_set_dir_npc, STRING("車掌"))
#if VERSION >= VERSION_US
    CALL(evt_set_dir_to_target, STRING("車掌"), STRING("mario"))
#endif
    CALL(evt_msg_print, 0, STRING("stg6_rsh_126"), 0, STRING("車掌"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(600)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_127"), 0, STRING("車掌"))
#if VERSION <= VERSION_JP
    CALL(evt_npc_flag_onoff, 1, STRING("車掌"), NPC_FLAG_INTANGIBLE)
#endif
    CALL(evt_npc_move_position, STRING("車掌"), -395, -145, 1000, 0, 1)
    CALL(evt_npc_flag_onoff, 0, STRING("車掌"), NPC_FLAG_INTANGIBLE)
    CALL(evt_set_dir_to_target, STRING("車掌"), STRING("mario"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_16_THE_BAGGAGE_CAR)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(bero_case_switch_on)
    RETURN
EVT_END()

EVT_BEGIN(evt_mario_chuumoku)
    LOOP(0)
        CALL(evt_mario_set_dir_npc, STRING("ポワン探偵"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_party_chuumoku)
    LOOP(0)
        CALL(evt_party_set_dir_npc, 0, STRING("ポワン探偵"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_shorui_funshitu)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
    CALL(evt_cam3d_evt_set, 220, 130, 250, 220, 55, -180, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_party_move_pos, 0, 255, -150, 500)
            CALL(evt_party_set_dir_npc, 0, STRING("ポワン探偵"))
        END_IF
    END_INLINE_EVENT
#if VERSION >= VERSION_US
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
#endif
    CALL(evt_mario_mov_pos, 260, -135, 500)
    CALL(evt_mario_set_dir_npc, STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("サラリーマン"), STRING("mario"))
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
#if VERSION >= VERSION_US
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
#endif
    CALL(evt_npc_status_onoff, 1, STRING("ポワン探偵"), 2)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_msg_print, 0, STRING("stg6_rsh_167"), 0, 0)
#else
    CALL(evt_msg_print, 0, STRING("stg6_rsh_167"), 0, STRING("me"))
#endif
    CALL(evt_set_dir_to_target, STRING("me"), STRING("サラリーマン"))
    WAIT_MS(500)
    CALL(evt_mario_set_dir_npc, STRING("サラリーマン"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_168"), 0, STRING("サラリーマン"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_168_01"), 0, STRING("ポワン探偵"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_168_02"), 0, STRING("サラリーマン"))
    WAIT_MS(500)
    SPAWN_EVENT_GET_ID(PTR(evt_mario_chuumoku), LW(10))
    SPAWN_EVENT_GET_ID(PTR(evt_party_chuumoku), LW(11))
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_TALK_ANIM)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_169_00"), 0, 0)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_TALK_ANIM)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("me"), 220, -125, 0, FLOAT(30.0f), 0)
    CALL(evt_npc_move_position, STRING("me"), 210, -115, 0, FLOAT(30.0f), 0)
    CALL(evt_npc_move_position, STRING("me"), 180, -110, 0, FLOAT(30.0f), 0)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_TALK_ANIM)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_169_01"), 0, 0)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_TALK_ANIM)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("me"), 270, -100, 0, FLOAT(30.0f), 0)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_TALK_ANIM)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_169_02"), 0, 0)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_TALK_ANIM)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("me"), 290, -140, 0, FLOAT(30.0f), 0)
    CALL(evt_npc_move_position, STRING("me"), 280, -170, 0, FLOAT(30.0f), 0)
    CALL(evt_npc_move_position, STRING("me"), 250, -200, 0, FLOAT(30.0f), 0)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_move_position, STRING("me"), 230, -180, 0, FLOAT(30.0f), 0)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 225, 71, 17, 225, 35, -180, 200, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 500)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg6_rsh_169_03"), 0, 0)
    CALL(evt_cam3d_evt_set, 225, 93, 115, 225, 40, -180, 500, 11)
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_169_04"), 0, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    DELETE_EVENT(LW(10))
    DELETE_EVENT(LW(11))
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), -2147483648)
    CALL(evt_npc_flag_onoff, 0, STRING("サラリーマン"), -2147483648)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_22_DOCUMENT)
    RETURN
EVT_END()

static s32 item_tbl[] = {
    ITEM_VITAL_PAPER, -1,
};

EVT_BEGIN(evt_daijisouna_kami)
    CALL(evt_cam3d_evt_set, 220, 107, 165, 220, 45, -180, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_US
            CALL(evt_party_move_pos, 0, 275, -160, 500)
#else
            CALL(evt_party_move_pos, 0, 245, -160, 500)
#endif
            CALL(evt_party_set_dir_npc, 0, STRING("ポワン探偵"))
        END_IF
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    CALL(evt_mario_mov_pos, 255, -150, 500)
    CALL(evt_mario_set_dir_npc, STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("サラリーマン"), STRING("mario"))
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_172"), 0, STRING("me"))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_win_item_select, PTR(item_tbl), LW(1))
#else
    CALL(evt_win_item_select, 0, PTR(item_tbl), LW(1), 0)
#endif
    IF_INT_EQUAL(LW(1), -1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_173_2"), 0, STRING("me"))
        CALL(evt_cam3d_evt_off, 500, 11)
        RETURN
    END_IF
    CALL(evt_mario_set_pose, STRING("M_C_3"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), -20)
    ADD(LW(1), 15)
    CALL(evt_item_entry, STRING("dummy"), ITEM_VITAL_PAPER, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_173"), 0, STRING("me"))
    CALL(evt_eff_fukidashi, 1, STRING("a"), STRING("サラリーマン"), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1200)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_set_dir_to_target, STRING("ポワン探偵"), STRING("サラリーマン"))
        CALL(evt_mario_set_dir_npc, STRING("サラリーマン"))
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("stg6_rsh_174"), 0, STRING("サラリーマン"))
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_item_delete, STRING("dummy"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_175"), 0, STRING("me"))
    CALL(evt_mario_set_pose, STRING("M_I_N"))
    CALL(evt_set_dir_to_target, STRING("ポワン探偵"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_176"), 0, STRING("me"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_4"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(2000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_177_00"), 0, STRING("me"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_24_A_VITAL_CLUE)
    RETURN
EVT_END()

EVT_BEGIN(evt_syasyou_auto_talk)
    IF_INT_EQUAL(GSWF(GSWF_RSH04_CONDUCTOR_AUTO_TALK_DONE), 1)
        RETURN
    END_IF
    CALL(evt_mario_wait_movable)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_dir_npc, STRING("車掌"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_129"), 0, STRING("車掌"))
    SET_VALUE(GSWF(GSWF_RSH04_CONDUCTOR_AUTO_TALK_DONE), 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_syashou)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_16_THE_BAGGAGE_CAR, STORY_STG6_17_GHOST_DIARY)
        CALL(evt_npc_set_position, STRING("車掌"), -395, 0, -145)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("車掌"), 0, -1000, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
            CALL(evt_npc_set_position, STRING("車掌"), -400, 0, -100)
        ELSE
            CALL(evt_npc_set_position, STRING("車掌"), 0, -1000, 0)
        END_IF
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

static s32 item_tbl2[] = {
    ITEM_BLANKET, -1,
};

static EVT_BEGIN(talk_syashou)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_12_GIVE_AUTOGRAPH, STORY_STG6_18_BLANKET_EXCHANGE)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    END_SWITCH
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_01_THE_CONDUCTOR)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_06"), 0, 0)
        WAIT_MS(300)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAND_UP1_1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_06_01"), 0, 0)
        CALL(evt_npc_set_position, STRING("サラリーマン"), 0, -1000, 0)
        CALL(evt_npc_set_position, STRING("ポワン探偵"), 0, -1000, 0)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_01_THE_CONDUCTOR)
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        IF_INT_EQUAL(LSWF(9), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_07"), 0, 0)
            SET_VALUE(LSWF(9), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_08"), 0, 0)
            SET_VALUE(LSWF(9), 0)
        END_IF
        CASE_LESS(STORY_STG6_09_BUBS_REQUEST)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_84_01"), 0, 0)
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_105"), 0, 0)
        SET_VALUE(GSWF(GSWF_RSH04_CONDUCTOR_AUTOGRAPH_TALK), 1)
        CALL_CHILD(evt_rsh_konarikin_irai_party_talk)
        IF_INT_EQUAL(GSWF(GSWF_RSH04_BUB_NO_AUTOGRAPH_AGAIN), 1)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
                SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
            END_IF
        END_IF
        CASE_LESS(STORY_STG6_13_TALK_TO_THE_CONDUCTOR)
        IF_INT_EQUAL(GSWF(GSWF_RSH04_CONDUCTOR_NIGHT_FIRST_TALK), 0)
            SET_VALUE(GSWF(GSWF_RSH04_CONDUCTOR_NIGHT_FIRST_TALK), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_111"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_114"), 0, 0)
        END_IF
        CALL(evt_msg_select, 0, STRING("stg6_rsh_114_yn"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_112"))
            SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_13_TALK_TO_THE_CONDUCTOR)
        ELSE
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_113"))
        END_IF
        CASE_LESS(STORY_STG6_15_GHOST_REQUEST)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_115"), 0, 0)
        CASE_LESS(STORY_STG6_16_THE_BAGGAGE_CAR)
        CALL_CHILD(evt_allow_kamotsu)
        CASE_LESS(STORY_STG6_17_GHOST_DIARY)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_129_01"), 0, 0)
        CASE_LESS(STORY_STG6_18_BLANKET_EXCHANGE)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_129"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_142"), 0, 0)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_win_item_select, PTR(item_tbl2), LW(1))
#else
        CALL(evt_win_item_select, 0, PTR(item_tbl2), LW(1), 0)
#endif
        IF_INT_NOT_EQUAL(LW(1), -1)
#if VERSION >= VERSION_US
            CALL(evt_mario_adjust_dir)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_mario_get_dispdir, LW(3))
            IF_INT_LESS(LW(3), 90)
                ADD(LW(0), -18)
            ELSE
                ADD(LW(0), 18)
            END_IF
            ADD(LW(1), 18)
            CALL(evt_item_entry, STRING("mofu"), ITEM_BLANKET, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_item_delete, STRING("mofu"))
#endif
            CALL(evt_msg_print, 0, STRING("stg6_rsh_143"), 0, 0)
            CALL(evt_item_entry, STRING("orei"), ITEM_MUSHROOM, 0, 0, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_item_get_item, STRING("orei"))
            CALL(evt_item_get_item_end_wait, STRING("orei"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_145"), 0, 0)
            SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_19_GIVE_BLANKET)
            CALL(evt_pouch_remove_item, ITEM_BLANKET, LW(0))
        END_IF
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_145"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        IF_INT_EQUAL(LSWF(10), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_158"), 0, 0)
            SET_VALUE(LSWF(10), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_159"), 0, 0)
            SET_VALUE(LSWF(10), 0)
        END_IF
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_213"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_220"), 0, 0)
        CASE_LESS(STORY_STG6_57_A_MAIL_FROM_PEACH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_254"), 0, 0)
        CASE_DEFAULT
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_04_a"))
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_POSHLEY), 1)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_c_09_1"), 0, 0)
                RETURN
            END_IF
            CALL(evt_msg_print, 0, STRING("stg6_rsh_c_09"), 0, 0)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_c_13"), 0, 0)
            ELSE
#if VERSION <= VERSION_DEMO_US
                CALL(evt_msg_print, 0, STRING("stg6_rsh_c_14"), 0, 0)
#else
                IF_INT_EQUAL(GSWF(GSWF_TRAIN_AT_ROGUEPORT), 0)
                    CALL(evt_msg_print, 0, STRING("stg6_rsh_c_14"), 0, 0)
                ELSE
                    CALL(evt_msg_print, 0, STRING("stg6_rsh_c_09_1"), 0, 0)
                END_IF
#endif
            END_IF
        END_IF
    END_SWITCH
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_12_GIVE_AUTOGRAPH, STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_sarary_repeat)
    CALL(evt_npc_flag_onoff, 1, STRING("サラリーマン"), -2147483648)
    CALL(evt_npc_get_position, STRING("サラリーマン"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_height, STRING("サラリーマン"), LW(3))
    ADD(LW(0), -5)
    ADD(LW(1), LW(3))
    ADD(LW(1), 10)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_165_01"), 0, STRING("サラリーマン"))
    LOOP(0)
        CALL(evt_msg_repeat)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(init_sarary)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_21_DAY_2, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_npc_set_position, STRING("me"), 190, 0, -150)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_49_POSHLEY_HEIGHTS)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(talk_sarary)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_18"), 0, 0)
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_79"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        IF_INT_EQUAL(GSWF(GSWF_RSH04_PENNINGTON_TALK_297), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_79_01"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_125"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_08"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_166"), 0, 0)
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_215"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_229"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_papa_mama)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_cam3d_evt_set, -220, 105, 186, -220, 40, -183, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_86"), 0, STRING("ナリキンママ"))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING("ナリキンパパ"), STRING("ナリキンママ"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_87"), 0, STRING("ナリキンパパ"))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING("ナリキンママ"), STRING("ナリキンパパ"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_88"), 0, STRING("ナリキンママ"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_88_01"), 0, STRING("コナリキン"))
    WAIT_MS(300)
    CALL(evt_npc_flag_onoff, 1, STRING("ナリキンパパ"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("ナリキンママ"), NPC_FLAG_INTANGIBLE)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_mario_set_dir, 270, 200, 0)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -200, -120, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 200)
        CALL(evt_party_stop, 0)
        WAIT_MS(200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, -225, -135, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_91"), 0, STRING("コナリキン"))
    CALL(evt_msg_select, 0, STRING("stg6_rsh_94_yn"))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("stg6_rsh_92"))
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_09_BUBS_REQUEST)
    ELSE
        CALL(evt_msg_print_add, 0, STRING("stg6_rsh_93"))
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_07_SYLVIA)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_08_BUB)
    END_IF
    CALL(evt_npc_flag_onoff, 0, STRING("ナリキンパパ"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 0, STRING("ナリキンママ"), NPC_FLAG_INTANGIBLE)
    CALL(evt_party_run, 0)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_cam3d_evt_off, 500, 11)
    RETURN
EVT_END()

EVT_BEGIN(talk_papa_repeat)
    CALL(evt_npc_flag_onoff, 1, STRING("ナリキンパパ"), -2147483648)
    CALL(evt_npc_get_position, STRING("ナリキンパパ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_height, STRING("ナリキンパパ"), LW(3))
    ADD(LW(1), LW(3))
    ADD(LW(1), 15)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_85_01"), 0, STRING("ナリキンパパ"))
    LOOP(0)
        CALL(evt_msg_repeat)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(init_papa)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_49_POSHLEY_HEIGHTS)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(talk_papa)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_15"), 0, 0)
        CASE_LESS(STORY_STG6_07_SYLVIA)
        CALL_CHILD(talk_papa_mama)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_85"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_09"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_163"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_226"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_mama_repeat)
    CALL(evt_npc_flag_onoff, 1, STRING("ナリキンママ"), -2147483648)
    CALL(evt_npc_get_position, STRING("ナリキンママ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_height, STRING("ナリキンママ"), LW(3))
    ADD(LW(1), LW(3))
    ADD(LW(1), 10)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_85_02"), 0, STRING("ナリキンママ"))
    LOOP(0)
        CALL(evt_msg_repeat)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(init_mama)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_49_POSHLEY_HEIGHTS)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(talk_mama)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_16"), 0, 0)
        CASE_LESS(STORY_STG6_07_SYLVIA)
        CALL_CHILD(talk_papa_mama)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_89"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_10"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_164"), 0, 0)
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_214"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_227"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_konari)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_49_POSHLEY_HEIGHTS)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

s32 item_tbl3[] = {
    ITEM_AUTOGRAPH, -1,
};

static EVT_BEGIN(talk_konari)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_17"), 0, 0)
        CASE_LESS(STORY_STG6_07_SYLVIA)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_90"), 0, 0)
        CASE_LESS(STORY_STG6_09_BUBS_REQUEST)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_08_BUB)
            SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_08_BUB)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_91"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_94"), 0, 0)
        END_IF
        CALL(evt_msg_select, 0, STRING("stg6_rsh_94_yn"))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_92"))
            SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_09_BUBS_REQUEST)
        ELSE
            CALL(evt_msg_print_add, 0, STRING("stg6_rsh_93"))
        END_IF
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_pouch_check_item, ITEM_AUTOGRAPH, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            IF_INT_EQUAL(GSWF(GSWF_RSH04_BUB_NO_AUTOGRAPH_FIRST), 0)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_95"), 0, 0)
                SET_VALUE(GSWF(GSWF_RSH04_BUB_NO_AUTOGRAPH_FIRST), 1)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg6_rsh_95_01"), 0, 0)
                SET_VALUE(GSWF(GSWF_RSH04_BUB_NO_AUTOGRAPH_AGAIN), 1)
                IF_INT_EQUAL(GSWF(GSWF_RSH04_CONDUCTOR_AUTOGRAPH_TALK), 1)
                    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
                        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD)
                    END_IF
                END_IF
            END_IF
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_96"), 0, 0)
#if VERSION <= VERSION_DEMO_US
            CALL(evt_win_item_select, PTR(item_tbl3), LW(1))
#else
            CALL(evt_win_item_select, 0, PTR(item_tbl3), LW(1), 0)
#endif
            IF_INT_EQUAL(LW(1), -1)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_101"), 0, 0)
            ELSE
                IF_INT_NOT_EQUAL(LW(1), 77)
                    CALL(evt_msg_print, 0, STRING("stg6_rsh_100"), 0, 0)
                ELSE
#if VERSION >= VERSION_US
                    CALL(evt_mario_adjust_dir)
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    CALL(evt_mario_get_dispdir, LW(3))
                    IF_INT_LESS(LW(3), 90)
                        ADD(LW(0), -18)
                    ELSE
                        ADD(LW(0), 18)
                    END_IF
                    ADD(LW(1), 18)
                    CALL(evt_item_entry, STRING("sign"), ITEM_AUTOGRAPH, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                    CALL(evt_mario_set_pose, STRING("M_C_3"))
                    WAIT_MS(1000)
                    CALL(evt_mario_set_pose, STRING("M_S_1"))
                    CALL(evt_item_delete, STRING("sign"))
#endif
                    CALL(evt_msg_print, 0, STRING("stg6_rsh_97"), 0, 0)
                    CALL(evt_item_entry, STRING("orei"), ITEM_SHINE_SPRITE, 0, 0, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                    CALL(evt_item_get_item, STRING("orei"))
                    CALL(evt_item_get_item_end_wait, STRING("orei"))
                    CALL(evt_msg_print, 0, STRING("stg6_rsh_99"), 0, 0)
                    CALL(evt_pouch_remove_item, ITEM_AUTOGRAPH, LW(0))
                    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_12_GIVE_AUTOGRAPH)
                    SET_VALUE(GSWF(GSWF_RSH04_SHINE_SPRITE_AUTOGRAPH), 1)
                END_IF
            END_IF
        END_IF
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_102"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_11"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_165"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_228"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(talk_powan_repeat)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), -2147483648)
    CALL(evt_npc_get_position, STRING("ポワン探偵"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_height, STRING("ポワン探偵"), LW(3))
    ADD(LW(0), 15)
    ADD(LW(1), LW(3))
    SUBTRACT(LW(1), 4)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_165_02"), 0, STRING("ポワン探偵"))
    LOOP(0)
        CALL(evt_msg_repeat)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(init_powan)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_21_DAY_2, STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_npc_set_position, STRING("me"), 230, 0, -180)
        CASE_BETWEEN(STORY_STG6_27_RIVERSIDE_STATION, STORY_STG6_42_DRAWBRIDGE_DOWN)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        CASE_GREATER_OR_EQUAL(STORY_STG6_49_POSHLEY_HEIGHTS)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(talk_powan)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_14"), 0, 0)
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        BEGIN_INLINE_EVENT
            CALL(evt_party_set_dir_npc, 0, STRING("ポワン探偵"))
        END_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_65"), 0, 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_QUESTION1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_I_G"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_66"), 0, 0)
        CALL(evt_cam3d_evt_set, 265, 93, 137, 265, 36, -183, 500, 11)
        WAIT_MS(500)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_67"), 0, 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_7"))
        WAIT_MS(1500)
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_C"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_68"), 0, 0)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_cam3d_evt_off, 500, 11)
        CASE_LESS(STORY_STG6_09_BUBS_REQUEST)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_69"), 0, 0)
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_103"), 0, 0)
        SET_VALUE(GSWF(GSWF_RSH04_PENNINGTON_AUTOGRAPH_TALK), 1)
        CASE_LESS(STORY_STG6_13_TALK_TO_THE_CONDUCTOR)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_104"), 0, 0)
        CASE_LESS(STORY_STG6_15_GHOST_REQUEST)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_116"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_124"), 0, 0)
        SET_VALUE(GSWF(GSWF_RSH04_PENNINGTON_TALK_297), 1)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147"), 0, 0)
        CASE_LESS(STORY_STG6_22_DOCUMENT)
        CALL_CHILD(evt_shorui_funshitu)
        CASE_LESS(STORY_STG6_23_VITAL_PAPER)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_170"), 0, 0)
        CASE_LESS(STORY_STG6_24_A_VITAL_CLUE)
        CALL_CHILD(evt_daijisouna_kami)
        CASE_LESS(STORY_STG6_26_ZIP_TOAD_CAUGHT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_177_01"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_225"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static NpcSetupInfo npc_data[] = {
    {
        "車掌", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_syashou, // initEvent
        NULL, // regularEvent
        talk_syashou, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "サラリーマン", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_sarary, // initEvent
        NULL, // regularEvent
        talk_sarary, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ナリキンパパ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_papa, // initEvent
        NULL, // regularEvent
        talk_papa, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ナリキンママ", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_mama, // initEvent
        NULL, // regularEvent
        talk_mama, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "コナリキン", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_konari, // initEvent
        NULL, // regularEvent
        talk_konari, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ポワン探偵", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_powan, // initEvent
        NULL, // regularEvent
        talk_powan, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

EVT_BEGIN(evt_tana_5)
    IF_INT_EQUAL(GSWF(GSWF_RSH04_STAR_PIECE_SHELF), 1)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_msg_print, 0, LW(1), 0, 0)
#else
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_56_ROGUEPORT_STATION)
            CALL(evt_msg_print, 0, LW(1), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, LW(3), 0, 0)
        END_IF
#endif
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_item_entry, STRING("_item00"), ITEM_STAR_PIECE, -260, 0, -240, ITEM_ENTRY_FIXED, -1, 0)
    CALL(evt_item_flag_on, STRING("_item00"), ITEM_FLAG_NO_TOUCH)
    CALL(evt_item_get_item, STRING("_item00"))
    SET_VALUE(GSWF(GSWF_RSH04_STAR_PIECE_SHELF), 1)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static ShelfAccessTbl3 access_tbl = {
    {
#if VERSION <= VERSION_DEMO_US
        {"tana_3", "stg6_rsh_272", NULL},
        {"tana_4", "stg6_rsh_273", NULL},
        {"tana_5", "stg6_rsh_274", evt_tana_5},
#else
        {"tana_3", "stg6_rsh_272", NULL, "stg6_rsh_267"},
        {"tana_4", "stg6_rsh_273", NULL, "stg6_rsh_267"},
        {"tana_5", "stg6_rsh_274", evt_tana_5, "stg6_rsh_267"},
#endif
    },
    {NULL},
};

static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_EQUAL(LW(2), 0)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_msg_print, 0, LW(1), 0, 0)
#else
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_56_ROGUEPORT_STATION)
            CALL(evt_msg_print, 0, LW(1), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, LW(3), 0, 0)
        END_IF
#endif
    ELSE
        CALL_CHILD(LW(2))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(&access_tbl))
    LOOP(0)
#if VERSION <= VERSION_DEMO_US
        READ_INT3(LW(0), LW(1), LW(2))
#else
        READ_INT4(LW(0), LW(1), LW(2), LW(3))
#endif
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_door_msg)
    CALL(evt_mario_key_onoff, 0)
    BEGIN_INLINE_EVENT
        LOOP(3)
            CALL(evt_sub_intpl_msec_init, 11, 0, -50, 200)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_trans, 1, STRING("w_tobira"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, -50, 0, 200)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
            CALL(evt_mapobj_trans, 1, STRING("w_tobira"), 0, 0, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    IF_INT_EQUAL(GSWF(GSWF_RSH04_WEST_DOOR_MSG_SEEN), 0)
        CALL(evt_cam3d_evt_set, 150, 135, 261, -200, 67, -13, 800, 11)
        WAIT_MS(800)
    END_IF
    CALL(evt_msg_print, 0, STRING("stg6_rsh_236_02"), 0, 0)
    IF_INT_EQUAL(GSWF(GSWF_RSH04_WEST_DOOR_MSG_SEEN), 0)
        CALL(evt_cam3d_evt_off, 500, 11)
        SET_VALUE(GSWF(GSWF_RSH04_WEST_DOOR_MSG_SEEN), 1)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_narikin_room)
    SET_TYPE(0)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        IF_INT_EQUAL(GSWF(GSWF_RSH04_INSIDE_CABIN5), 1)
            IF_INT_EQUAL(LF(0), 0)
                CALL(mario_flag, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    SET_VALUE(LF(0), 1)
                    SWITCH(GSW(GSW_STORY_PROGRESS))
                        CASE_BETWEEN(STORY_STG6_06_PENNINGTONS_ASSISTANT, STORY_STG6_18_BLANKET_EXCHANGE)
                        SPAWN_EVENT_GET_ID(PTR(talk_papa_repeat), GW(14))
                        SPAWN_EVENT_GET_ID(PTR(talk_mama_repeat), GW(15))
                    END_SWITCH
                END_IF
            ELSE
                CALL(mario_flag, LW(0))
                IF_INT_EQUAL(LW(0), 1)
                    SET_VALUE(LF(0), 0)
                    DELETE_EVENT(GW(14))
                    DELETE_EVENT(GW(15))
                    CALL(evt_msg_close, STRING("stg6_rsh_85_01"))
                    CALL(evt_msg_close, STRING("stg6_rsh_85_02"))
                END_IF
            END_IF
        ELSE
            IF_INT_EQUAL(LF(0), 1)
                SET_VALUE(LF(0), 0)
                SWITCH(GSW(GSW_STORY_PROGRESS))
                    CASE_BETWEEN(STORY_STG6_06_PENNINGTONS_ASSISTANT, STORY_STG6_18_BLANKET_EXCHANGE)
                    DELETE_EVENT(GW(14))
                    DELETE_EVENT(GW(15))
                    CALL(evt_msg_close, STRING("stg6_rsh_85_01"))
                    CALL(evt_msg_close, STRING("stg6_rsh_85_02"))
                END_SWITCH
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_powan_room)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        IF_INT_EQUAL(GSWF(GSWF_RSH04_INSIDE_CABIN3), 1)
            IF_INT_EQUAL(LF(0), 0)
                CALL(mario_flag, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    SET_VALUE(LF(0), 1)
                    SWITCH(GSW(GSW_STORY_PROGRESS))
                        CASE_EQUAL(STORY_STG6_21_DAY_2)
                        SPAWN_EVENT_GET_ID(PTR(talk_sarary_repeat), GW(14))
                        SPAWN_EVENT_GET_ID(PTR(talk_powan_repeat), GW(15))
                    END_SWITCH
                END_IF
            ELSE
                CALL(mario_flag, LW(0))
                IF_INT_EQUAL(LW(0), 1)
                    SET_VALUE(LF(0), 0)
                    DELETE_EVENT(GW(14))
                    DELETE_EVENT(GW(15))
                    CALL(evt_msg_close, STRING("stg6_rsh_165_01"))
                    CALL(evt_msg_close, STRING("stg6_rsh_165_02"))
                END_IF
            END_IF
        ELSE
            IF_INT_EQUAL(LF(0), 1)
                SET_VALUE(LF(0), 0)
                SWITCH(GSW(GSW_STORY_PROGRESS))
                    CASE_EQUAL(STORY_STG6_21_DAY_2)
                    DELETE_EVENT(GW(14))
                    DELETE_EVENT(GW(15))
                    CALL(evt_msg_close, STRING("stg6_rsh_165_01"))
                    CALL(evt_msg_close, STRING("stg6_rsh_165_02"))
                END_SWITCH
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_init_evt)
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
    SET_VALUE(LW(0), PTR(&door_5))
    CALL_CHILD(evt_rsh_door_entry)
    CALL(evt_npc_setup, PTR(npc_data))
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_16_THE_BAGGAGE_CAR)
        SET_VALUE(LW(0), 0)
        CALL_CHILD(bero_case_switch_off)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_18_BLANKET_EXCHANGE)
        SET_VALUE(LW(0), 0)
        CALL_CHILD(bero_case_switch_off)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
        SET_VALUE(LW(0), 0)
        CALL_CHILD(bero_case_switch_on)
#if VERSION >= VERSION_US
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_49_POSHLEY_HEIGHTS)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_55_PEACH_GRODUS_AND_X_NAUT)
            SET_VALUE(LW(0), 0)
            CALL_CHILD(bero_case_switch_off)
        END_IF
#endif
    END_IF
    CALL_CHILD(evt_access_entry)
    SPAWN_EVENT(evt_narikin_room)
    SPAWN_EVENT(evt_powan_room)
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
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_04_a"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_04_b"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH3"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_04_c"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_a_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_04_init_evt)
    CALL_CHILD(evt_rsh_moamoa_on_window)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
        SET_VALUE(LW(0), 0)
        CALL_CHILD(bero_case_switch_off)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("w_bero"), 0, PTR(evt_door_msg), 0)
        CALL(evt_npc_entry, STRING("moa1"), STRING("c_n_moa_a"))
        CALL(evt_npc_entry, STRING("moa2"), STRING("c_n_moa_a"))
        CALL(evt_npc_entry, STRING("moa3"), STRING("c_n_moa_a"))
        CALL(evt_npc_set_position, STRING("moa1"), -440, 10, -100)
        CALL(evt_npc_set_position, STRING("moa2"), -441, 30, -125)
        CALL(evt_npc_set_position, STRING("moa3"), -442, 40, -75)
        CALL(evt_npc_pera_onoff, STRING("moa1"), 0)
        CALL(evt_npc_pera_onoff, STRING("moa2"), 0)
        CALL(evt_npc_pera_onoff, STRING("moa3"), 0)
        CALL(evt_npc_set_ry, STRING("moa1"), 270)
        CALL(evt_npc_set_ry, STRING("moa2"), 270)
        CALL(evt_npc_set_ry, STRING("moa3"), 270)
        CALL(evt_npc_set_anim, STRING("moa1"), STRING("S_1"))
        CALL(evt_npc_set_anim, STRING("moa2"), STRING("S_1"))
        CALL(evt_npc_set_anim, STRING("moa3"), STRING("S_1"))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_b_init_evt)
    IF_INT_EQUAL(GSWF(GSWF_RSH_SCRIPTED_ENTRY_PENDING), 0)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CALL(evt_bero_get_info)
        CALL_CHILD(evt_bero_info_run)
    ELSE
        SET_VALUE(GSWF(GSWF_RSH_SCRIPTED_ENTRY_PENDING), 0)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CALL(evt_bero_get_info)
        CALL_CHILD(bero_case_entry)
        CALL(evt_mario_set_pos, 220, 0, -20)
        CALL(evt_party_set_pos, 0, 200, 0, -20)
#if VERSION >= VERSION_JP
        DEBUG_PUT_MSG(STRING("パーティドア移動フラグクリア"))
        CALL(evt_party_trigflg_onoff, 0, PARTY_TRIG_FLAG_FOLLOW_CLOSE | PARTY_TRIG_FLAG_SMALL_HOSEI | PARTY_TRIG_FLAG_HOME_DIR_SET | PARTY_TRIG_FLAG_DOOR_MOVE, 0)
#endif
    END_IF
    CALL_CHILD(rsh_04_init_evt)
    RETURN
EVT_END()

static const char* window_tbl[] = {
    "mado_uturi_1",
    "mado_uturi_2",
    "mado_uturi_3",
    NULL,
};

EVT_BEGIN(rsh_04_c_init_evt)
    IF_INT_EQUAL(GSWF(GSWF_RSH_SCRIPTED_ENTRY_PENDING), 0)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CALL(evt_bero_get_info)
        CALL_CHILD(evt_bero_info_run)
    ELSE
        SET_VALUE(GSWF(GSWF_RSH_SCRIPTED_ENTRY_PENDING), 0)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CALL(evt_bero_get_info)
        CALL_CHILD(bero_case_entry)
        CALL(evt_mario_set_pos, -200, 0, -30)
        CALL(evt_party_set_pos, 0, -230, 0, -30)
#if VERSION >= VERSION_JP
        DEBUG_PUT_MSG(STRING("パーティドア移動フラグクリア"))
        CALL(evt_party_trigflg_onoff, 0, PARTY_TRIG_FLAG_FOLLOW_CLOSE | PARTY_TRIG_FLAG_SMALL_HOSEI | PARTY_TRIG_FLAG_HOME_DIR_SET | PARTY_TRIG_FLAG_DOOR_MOVE, 0)
#endif
    END_IF
    CALL_CHILD(rsh_04_init_evt)
    CALL(evt_map_playanim, STRING("ranpu"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_17_GHOST_DIARY)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("w_bero"))
            SPAWN_EVENT(evt_syasyou_auto_talk)
        END_IF
    END_IF
    RETURN
EVT_END()

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
        "rsh_07_a", // nextMapName
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
        "rsh_03_a", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

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
        "rsh_07_b", // nextMapName
        "w_bero", // nextBeroName
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
        "rsh_03_b", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

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
        "rsh_07_c", // nextMapName
        "w_bero", // nextBeroName
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
        "rsh_03_c", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(rsh_04_init_evt_nidome)
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
    SET_VALUE(LW(0), PTR(&door_5))
    CALL_CHILD(evt_rsh_door_entry)
    CALL_CHILD(evt_access_entry)
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
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_04_a"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_04_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_04_c"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1"))
            END_IF
        END_IF
    END_IF
    CALL_CHILD(evt_rsh_04_rnd_npc_entry)
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_a_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_a))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_a_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_04_init_evt_nidome)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 1)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 0)
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_b_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_b))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_b_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_04_init_evt_nidome)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 1)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 0)
    RETURN
EVT_END()

EVT_BEGIN(rsh_04_c_init_evt_nidome)
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_RETURN_TRIP), 0)
        SET_VALUE(LW(0), PTR(bero_data_c))
    ELSE
        SET_VALUE(LW(0), PTR(bero_data_c_return))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(rsh_04_init_evt_nidome)
    CALL(evt_map_playanim, STRING("ranpu"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(evt_rsh_window)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_A), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_B), 0)
    SET_VALUE(GSWF(GSWF_RSH_REVISIT_VARIANT_C), 1)
    RETURN
EVT_END()

BOOL winGhostDiaryChk(void);

static USER_FUNC(mario_flag) {
    EvtWord* args = event->args;
    MarioWork* mario = marioGetPtr();
    if (fbatGetPointer()->mode == 2 || winGhostDiaryChk()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
