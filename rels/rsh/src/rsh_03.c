// rsh_03 (列車, Excess Express): dining car: cook, waitress and shop clerk, the Smorg (moamoa) shop with its trade list,
// and the lunch-missing mystery; doors to rsh_02 and rsh_04.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"

#include "mario/mario_pouch.h"
#include "mario/mario.h"
#include "driver/npcdrv.h"
#include "string.h"
#include "driver/camdrv.h"
#include "mario/mariost.h"
#include "driver/effdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "rsh.h"
#include "evt/evt_npc.h"
#include "evt/evt_shop.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_env.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_paper.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_snd.h"
#include "evt/evt_window.h"
#include "party/party_motion.h"
#include "data_tables.h"
#include "version.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#include "driver/mapdrv.h"

static char tmp[32];
Vec camPt;
Vec camAt;
EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);

USER_FUNC(fire);
static USER_FUNC(mario_flag);
USER_FUNC(npc_alpha_except_tenin);
#if VERSION >= VERSION_US
USER_FUNC(evt_sub_get_language);
#endif

static BeroEntry bero_data_a[3];
static BeroEntry bero_data_b[3];
static BeroEntry bero_data_c[3];
extern EvtWord init_cook[];
s32 item_tbl_cook[2];
extern EvtWord talk_cook_nabe_return[];
s32 iri_22_item_tbl[4];
extern EvtWord talk_cook[];
s32 item_tbl_waitless[2];
extern EvtWord talk_waitless_pias_return[];
extern EvtWord move_waitless[];
static NpcSetupInfo npc_data[4];
extern EvtWord dir_target[];
extern EvtWord evt_lanch_missing[];
NpcSetupInfo npc_data_lunch[7];
static const char* msg_tbl[10];
extern EvtWord evt_lunch_talk[];
extern EvtWord evt_shop_moamoa_talk[];
static ShopObj obj_list[6];
static ShopItem goods_list[6];
static ShopDb trade_list[18];
static ShopperData35 shopper_data;
extern EvtWord shop_door_open[];
extern EvtWord shop_door_close[];
extern EvtWord evt_shop_open[];
extern EvtWord evt_shop_close[];
extern EvtWord evt_shop_door_init[];
static EvtWord evt_yuka_simi[45];
static const char* access_tbl[16];
extern EvtWord rsh_03_init_evt[];
static const char* window_tbl[5];
extern EvtWord rsh_03_init_evt_nidome[];

USER_FUNC(iri_22_make_item_tbl) {
    EvtWord* args = event->args;
    u8 bought;
    s32 n;
    s32 i;

    bought = evtGetValue(NULL, GSW(GSW_TROUBLE_WORK_FIRST));
    for (i = 0; i < 4; i++) {
        iri_22_item_tbl[i] = -1;
    }
    n = 0;
    if (!(bought & 1) && pouchCheckItem(ITEM_GOLDEN_LEAF) != 0) {
        iri_22_item_tbl[0] = ITEM_GOLDEN_LEAF;
        n = 1;
    }
    if (!(bought & 2) && pouchCheckItem(ITEM_MYSTIC_EGG) != 0) {
        iri_22_item_tbl[n++] = ITEM_MYSTIC_EGG;
    }
    if (!(bought & 4) && pouchCheckItem(ITEM_KEEL_MANGO) != 0) {
        iri_22_item_tbl[n++] = ITEM_KEEL_MANGO;
    }
    evtSetValue(event, args[0], (EvtWord)iri_22_item_tbl);
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_flag) {
    static BOOL flg;
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc;

    marioGetPtr();
    npc = fbatNpcTalkCheck();
    if (npc != NULL) {
        strcpy(tmp, npc->description);
        flg = TRUE;
    }
    if (flg && strcmp(name, tmp) == 0) {
        evtSetValue(event, args[1], 1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[1], 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(omiseHozon) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    camPt = cam->cameraPos;
    camAt = cam->cameraAt;
    return EVT_RETURN_DONE;
}

USER_FUNC(omiseFukki) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    cam->presetPos = cam->cameraPos;
    cam->presetAt = cam->cameraAt;
    cam->storedPos = camPt;
    cam->storedAt = camAt;
    cam->startTimeA = gp->renderTime;
    cam->durationA = OSMillisecondsToTicks(500);
    cam->stateA = 3;
    cam->curveA = 11;
    return EVT_RETURN_DONE;
}

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
        "rsh_04_a", // nextMapName
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
        "rsh_02_a", // nextMapName
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
        "rsh_04_b", // nextMapName
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
        "rsh_02_b", // nextMapName
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
        "rsh_04_c", // nextMapName
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
        "rsh_02_c", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        "e_door_close", // enterAnimeArg
        "e_door_open", // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(init_cook)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

s32 item_tbl_cook[] = {
    ITEM_GALLEY_POT, -1,
};

EVT_BEGIN(talk_cook_nabe_return)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_70_00"), 0, STRING("コック"))
    CALL(evt_win_item_select, 0, PTR(item_tbl_cook), LW(1), 0)
    IF_INT_NOT_EQUAL(LW(1), -1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_70_01"), 0, STRING("コック"))
        CALL(evt_item_entry, STRING("orei"), ITEM_STAR_PIECE, 0, 0, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING("orei"))
        CALL(evt_item_get_item_end_wait, STRING("orei"))
        SET_VALUE(GSWF(GSWF_RSH03_STAR_PIECE_GALLEY_POT), 1)
        CALL(evt_pouch_remove_item, ITEM_GALLEY_POT, LW(0))
    END_IF
    RETURN
EVT_END()

s32 iri_22_item_tbl[] = {
    -1, -1, -1, -1,
};

EVT_BEGIN(talk_cook)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 22)
        CALL(iri_22_make_item_tbl, LW(0), LW(1))
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
            SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
            IF_INT_EQUAL(LW(1), 0)
                CALL(evt_msg_print, 0, STRING("irai_22_00"), 0, 0)
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_22_01"), 0, 0)
                GOTO(0)
            END_IF
        ELSE
            IF_INT_EQUAL(LW(1), 0)
                SWITCH(GSW(GSW_TROUBLE_WORK_FIRST))
                    CASE_EQUAL(0)
                    CALL(evt_msg_print, 0, STRING("irai_22_02"), 0, 0)
                    CASE_EQUAL(1)
                    CALL(evt_msg_print, 0, STRING("irai_22_05"), 0, 0)
                    CASE_EQUAL(2)
                    CALL(evt_msg_print, 0, STRING("irai_22_04"), 0, 0)
                    CASE_EQUAL(4)
                    CALL(evt_msg_print, 0, STRING("irai_22_03"), 0, 0)
                    CASE_EQUAL(3)
                    CALL(evt_msg_print, 0, STRING("irai_22_08"), 0, 0)
                    CASE_EQUAL(5)
                    CALL(evt_msg_print, 0, STRING("irai_22_07"), 0, 0)
                    CASE_EQUAL(6)
                    CALL(evt_msg_print, 0, STRING("irai_22_06"), 0, 0)
                    CASE_DEFAULT
                    DEBUG_PUT_MSG(STRING("iri_22 status ???"))
                END_SWITCH
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_22_09"), 0, 0)
                GOTO(0)
            END_IF
        END_IF
        RETURN
        LABEL(0)
        CALL(evt_win_item_select, 0, LW(0), LW(1), 0)
        SWITCH(LW(1))
            CASE_EQUAL(169)
            CALL(evt_pouch_remove_item, ITEM_GOLDEN_LEAF, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_10"), 0, 0)
            OR(GSW(GSW_TROUBLE_WORK_FIRST), 1)
            CASE_EQUAL(168)
            CALL(evt_pouch_remove_item, ITEM_MYSTIC_EGG, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_11"), 0, 0)
            OR(GSW(GSW_TROUBLE_WORK_FIRST), 2)
            CASE_EQUAL(170)
            CALL(evt_pouch_remove_item, ITEM_KEEL_MANGO, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_12"), 0, 0)
            OR(GSW(GSW_TROUBLE_WORK_FIRST), 4)
        END_SWITCH
        IF_INT_EQUAL(GSW(GSW_TROUBLE_WORK_FIRST), 7)
            CALL(evt_msg_print_add, 0, STRING("irai_22_13"))
            CALL(evt_sub_get_coin, 40)
            SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
            SET_VALUE(GSWF(GSWF_TROUBLE_22_SOLVED), 1)
            CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
        ELSE
            IF_INT_NOT_EQUAL(LW(1), -1)
                CALL(evt_msg_continue)
            END_IF
        END_IF
        RETURN
    END_IF
    CALL(evt_pouch_check_item, ITEM_GALLEY_POT, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(talk_cook_nabe_return))
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_01_THE_CONDUCTOR)
        IF_INT_EQUAL(LSWF(5), 0)
            SET_VALUE(LSWF(5), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_04"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_05"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_19"), 0, 0)
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        IF_INT_EQUAL(GSWF(GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_40"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_50_1"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_12_GIVE_AUTOGRAPH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_72"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_72_01"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_07"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        IF_INT_EQUAL(LSWF(6), 0)
            SET_VALUE(LSWF(6), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_156"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_157"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_212"), 0, 0)
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_219"), 0, 0)
#if VERSION == VERSION_EU
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
#endif
        CALL(evt_msg_print_party, STRING("stg6_rsh_219_2"))
#if VERSION == VERSION_EU
        CALL(evt_party_run, 0)
#endif
        CASE_LESS(STORY_STG6_57_A_MAIL_FROM_PEACH)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_257"), 0, 0)
        CASE_LESS(STORY_STG8_END_AFTER_THE_BATTLE)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_12"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_12_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_waitless)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_45_DAY_3_STARTS, STORY_STG6_48_SMORG_MIASMA)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_JUMPING)
    END_IF
    RETURN
EVT_END()

s32 item_tbl_waitless[] = {
    ITEM_SHELL_EARRINGS, -1,
};

EVT_BEGIN(talk_waitless_pias_return)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_npc_get_reglid, STRING("ウェイトレス"), LW(10))
    DELETE_EVENT(LW(10))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_195"), 0, STRING("ウェイトレス"))
    CALL(evt_win_item_select, 0, PTR(item_tbl_waitless), LW(1), 0)
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
        CALL(evt_item_entry, STRING("yubiwa"), ITEM_SHELL_EARRINGS, LW(0), LW(1), LW(2), 17, -1, 0)
        CALL(evt_mario_set_pose, STRING("M_C_3"))
        WAIT_MS(1000)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_item_delete, STRING("yubiwa"))
#endif
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_4"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_196"), 0, STRING("ウェイトレス"))
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
#if VERSION >= VERSION_US
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("A_1"))
        WAIT_MS(500)
#endif
        CALL(evt_item_entry, STRING("orei"), ITEM_STAR_PIECE, 0, 0, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING("orei"))
        CALL(evt_item_get_item_end_wait, STRING("orei"))
        SET_VALUE(GSWF(GSWF_RSH03_STAR_PIECE_WAITRESS), 1)
#if VERSION >= VERSION_US
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("S_1"))
#endif
        CALL(evt_msg_print, 0, STRING("stg6_rsh_197"), 0, STRING("ウェイトレス"))
#if VERSION <= VERSION_JP
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("A_1"))
        WAIT_MS(500)
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("S_1"))
#endif
        CALL(evt_pouch_remove_item, ITEM_SHELL_EARRINGS, LW(0))
    ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_196_2"), 0, STRING("ウェイトレス"))
    END_IF
    CALL(evt_npc_restart_regular_event, STRING("ウェイトレス"))
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

static EVT_BEGIN(talk_waitless)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_06_PENNINGTONS_ASSISTANT)
        IF_INT_EQUAL(GSWF(GSWF_RSH03_WAITRESS_HELP_ACCEPTED), 0)
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
            IF_INT_EQUAL(GSWF(GSWF_RSH03_WAITRESS_ASKED_HELP), 0)
                SET_VALUE(GSWF(GSWF_RSH03_WAITRESS_ASKED_HELP), 1)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_74"), 0, 0)
            ELSE
                CALL(evt_msg_print, 0, STRING("stg6_rsh_77"), 0, 0)
            END_IF
            CALL(evt_msg_select, 0, STRING("stg6_rsh_77_yn"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_75"))
                SET_VALUE(GSWF(GSWF_RSH03_WAITRESS_HELP_ACCEPTED), 1)
            ELSE
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_76"))
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
    CALL(evt_pouch_check_item, ITEM_SHELL_EARRINGS, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(talk_waitless_pias_return))
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_01_THE_CONDUCTOR)
        IF_INT_EQUAL(LSWF(7), 0)
            SET_VALUE(LSWF(7), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_02"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_03"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_22"), 0, 0)
        CASE_LESS(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
        IF_INT_EQUAL(GSWF(GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_41"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_47"), 0, 0)
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_48"), 0, STRING("トロン"))
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_49"), 0, 0)
        END_IF
        CASE_LESS(STORY_STG6_06_PENNINGTONS_ASSISTANT)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_73"), 0, 0)
        CASE_LESS(STORY_STG6_19_GIVE_BLANKET)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_78"), 0, 0)
        CASE_LESS(STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_06"), 0, 0)
        CASE_LESS(STORY_STG6_27_RIVERSIDE_STATION)
        IF_INT_EQUAL(LSWF(8), 0)
            SET_VALUE(LSWF(8), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_154"), 0, 0)
        ELSE
            CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("H_1"), STRING("T_4"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_155"), 0, 0)
            CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        END_IF
        CASE_LESS(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("P_1"), STRING("T_5"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_199"), 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        CASE_LESS(STORY_STG6_44_END_OF_DAY_2)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_218"), 0, 0)
        CASE_LESS(STORY_STG6_57_A_MAIL_FROM_PEACH)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_4"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_256"), 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        CASE_LESS_OR_EQUAL(STORY_STG8_END_AFTER_THE_BATTLE)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_11"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_11_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(move_waitless)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_01_THE_CONDUCTOR)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
            RETURN
        END_IF
    END_IF
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), 150, -125, 0, FLOAT(24.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(5000)
        CALL(evt_npc_move_position, STRING("me"), 400, -125, 0, FLOAT(24.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(5000)
    END_LOOP
    RETURN
EVT_END()

static NpcSetupInfo npc_data[] = {
    {
        /*"コック"*/"\x83\x52\x83\x62\x83\x4E", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_cook, // initEvent
        NULL, // regularEvent
        talk_cook, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, // reactionFlags
        init_waitless, // initEvent
        move_waitless, // regularEvent
        talk_waitless, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"店員"*/"\x93\x58\x88\xF5", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

static EVT_BEGIN(talk_toron)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_20"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_42"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_sarary)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_21"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_43"), 0, 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_50"), 0, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(dir_target)
    CALL(evt_set_dir_to_target, STRING("ウェイトレス"), LW(0))
    CALL(evt_set_dir_to_target, STRING("トロン"), LW(0))
    CALL(evt_set_dir_to_target, STRING("サラリーマン"), LW(0))
    CALL(evt_set_dir_to_target, STRING("ポワン探偵"), LW(0))
    CALL(evt_mario_set_dir_npc, LW(0))
    RETURN
EVT_END()

EVT_BEGIN(evt_lanch_missing)
    SET_VALUE(GF(10), 1)
    CALL(evt_set_dir_to_target, STRING("サラリーマン"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("トロン"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("ウェイトレス"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("コック"), STRING("ポワン探偵"))
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_POWAN1"))
    CALL(evt_snd_envoff, PSND_FADE_HOLD)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 0, -135, FLOAT(70.0f))
        CALL(evt_party_set_dir_npc, 0, STRING("ポワン探偵"))
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_flag_onoff, 1, 1024)
        CALL(evt_mario_mov_pos2, 10, -125, FLOAT(70.0f))
        CALL(evt_mario_set_dir_npc, STRING("ポワン探偵"))
        CALL(evt_mario_flag_onoff, 0, 1024)
        CALL(evt_set_dir_to_target, STRING("ポワン探偵"), STRING("mario"))
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 500, 11)
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_23"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 45, 75, 75, 45, 40, -122, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_24"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 0, 11)
    WAIT_FRAMES(1)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(3)
            CALL(evt_cam3d_evt_set, 0, 88, 95, 0, 50, -122, 200, 11)
            WAIT_MS(200)
            CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 200, 11)
            WAIT_MS(200)
        END_LOOP
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING("トロン"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("トロン"), LW(0), LW(1), LW(2), 200, FLOAT(0.0f), FLOAT(10.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_npc_get_position, STRING("コック"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("コック"), LW(0), LW(1), LW(2), 200, FLOAT(0.0f), FLOAT(10.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_npc_get_position, STRING("サラリーマン"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("サラリーマン"), LW(0), LW(1), LW(2), 200, FLOAT(0.0f), FLOAT(10.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_npc_get_position, STRING("ウェイトレス"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("ウェイトレス"), LW(0), LW(1), LW(2), 200, FLOAT(0.0f), FLOAT(10.0f), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SURPRISED2"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_25"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_cam3d_evt_set, 25, 102, 174, 25, 50, -122, 500, 11)
    WAIT_MS(500)
    SET_VALUE(LW(0), STRING("コック"))
    SPAWN_EVENT(PTR(dir_target))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_26"), 0, STRING("コック"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_BOKE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_27"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    CALL(evt_cam3d_evt_set, 45, 75, 75, 45, 40, -122, 200, 11)
    WAIT_MS(200)
    SET_VALUE(LW(0), STRING("ポワン探偵"))
    SPAWN_EVENT(PTR(dir_target))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_28"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_ADMIRE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(3)
            CALL(evt_cam3d_evt_set, 0, 88, 95, 0, 50, -122, 200, 11)
            WAIT_MS(200)
            CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 200, 11)
            WAIT_MS(200)
        END_LOOP
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_29"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    WAIT_MS(300)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_print, 0, STRING("stg6_rsh_30"), 0, STRING("ポワン探偵"))
    CALL(evt_cam3d_evt_set, -20, 76, 26, -20, 50, -122, 200, 11)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_30_01"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_set_dir_to_target, STRING("コック"), STRING("ウェイトレス"))
        CALL(evt_set_dir_to_target, STRING("ウェイトレス"), STRING("ポワン探偵"))
        CALL(evt_set_dir_to_target, STRING("トロン"), STRING("ウェイトレス"))
        CALL(evt_set_dir_to_target, STRING("サラリーマン"), STRING("ウェイトレス"))
        CALL(evt_set_dir_to_target, STRING("ポワン探偵"), STRING("ウェイトレス"))
        CALL(evt_eff_fukidashi, 1, STRING("a"), STRING("ウェイトレス"), 0, 0, 0, 0, 0, 0, 0, 100)
        CALL(evt_npc_get_position, STRING("ウェイトレス"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("ウェイトレス"), LW(0), LW(1), LW(2), 200, 0, FLOAT(10.0f), 0)
        CALL(evt_npc_reverse_ry, STRING("ウェイトレス"))
        WAIT_MS(300)
        CALL(evt_npc_reverse_ry, STRING("ウェイトレス"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("B_1"))
        WAIT_MS(200)
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("B_2"))
    END_INLINE_EVENT
    WAIT_MS(1500)
    CALL(evt_npc_set_autotalkpose, STRING("ウェイトレス"), STRING("B_2"), STRING("T_2"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_31"), 0, STRING("ウェイトレス"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_set_dir_to_target, STRING("コック"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("ウェイトレス"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("トロン"), STRING("ポワン探偵"))
    CALL(evt_set_dir_to_target, STRING("サラリーマン"), STRING("ポワン探偵"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_32"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_BOKE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_33"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), NPC_FLAG_TALK_ANIM)
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("O_1"))
    CALL(evt_npc_set_autotalkpose, STRING("ウェイトレス"), STRING("O_1"), STRING("T_3"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_34"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_35"), 0, STRING("サラリーマン"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_36"), 0, STRING("トロン"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_37"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_38"), 0, STRING("ウェイトレス"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_39"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_npc_set_autotalkpose, STRING("ウェイトレス"), STRING("S_1"), STRING("T_1"))
    CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("S_1"))
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_02_A_CASE_OF_LOST_STEW)
    CALL(evt_run_case_evt, CASE_COND_STAND_ON_A, 1, STRING("a_yuka_simi"), 0, PTR(evt_yuka_simi), 0)
    CALL(evt_snd_envoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), NPC_FLAG_INTANGIBLE)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(10), 0)
    RETURN
EVT_END()

static EVT_BEGIN(talk_powan)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_02_A_CASE_OF_LOST_STEW)
        CALL_CHILD(PTR(evt_lanch_missing))
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK), 0)
            SET_INT_READ_ADDR(PTR(&msg_tbl))
            LOOP(5)
                READ_INT2(LW(0), LW(1))
                CALL(evt_msg_close, LW(1))
            END_LOOP
            SET_VALUE(GF(10), 1)
            CALL(evt_cam3d_evt_set, 45, 88, 124, 45, 45, -122, 500, 11)
            WAIT_MS(600)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_44"), 0, 0)
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_AWAKE1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_5B"))
            CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 500, 11)
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_44_01"), 0, 0)
            BEGIN_INLINE_EVENT
                CALL(evt_env_blur_on, 0, 500)
            END_INLINE_EVENT
            CALL(evt_cam3d_evt_set_rel, 0, 21, 246, 0, 34, -10, 200, 11)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_45"), 0, 0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_7"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 500, 11)
            WAIT_MS(700)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_C"))
            WAIT_MS(600)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_45_01"), 0, 0)
            CALL(evt_cam3d_evt_off, 500, 11)
            SET_VALUE(GF(10), 0)
            SET_VALUE(GSWF(GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_46"), 0, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

NpcSetupInfo npc_data_lunch[] = {
    {
        /*"コック"*/"\x83\x52\x83\x62\x83\x4E", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, // reactionFlags..regularEvent
        talk_cook, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, // reactionFlags..regularEvent
        talk_waitless, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"店員"*/"\x93\x58\x88\xF5", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"トロン"*/"\x83\x67\x83\x8D\x83\x93", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, // reactionFlags..regularEvent
        talk_toron, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"サラリーマン"*/"\x83\x54\x83\x89\x83\x8A\x81\x5B\x83\x7D\x83\x93", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, // reactionFlags..regularEvent
        talk_sarary, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        /*"ポワン探偵"*/"\x83\x7C\x83\x8F\x83\x93\x92\x54\x92\xE3", // name
        NPC_FLAG_NO_WALL_HIT | NPC_FLAG_JUMPING | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM | NPC_FLAG_LAND_ON_FLOOR, // flags
        0, NULL, NULL, // reactionFlags..regularEvent
        talk_powan, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

static const char* msg_tbl[] = {
    /*"コック"*/"\x83\x52\x83\x62\x83\x4E",
    "stg6_rsh_18_01",
    /*"トロン"*/"\x83\x67\x83\x8D\x83\x93",
    "stg6_rsh_18_02",
    /*"サラリーマン"*/"\x83\x54\x83\x89\x83\x8A\x81\x5B\x83\x7D\x83\x93",
    "stg6_rsh_18_03",
    /*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58",
    "stg6_rsh_18_04",
    /*"ポワン探偵"*/"\x83\x7C\x83\x8F\x83\x93\x92\x54\x92\xE3",
    "stg6_rsh_18_05",
};

EVT_BEGIN(evt_lunch_talk)
    SET_VALUE(GF(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(&msg_tbl))
        CALL(evt_sub_random, 4, LW(0))
        ADD(LW(0), 1)
        LOOP(LW(0))
            READ_INT2(LW(10), LW(11))
        END_LOOP
        CALL(mario_flag, LW(10), LW(0))
        IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_US
            BEGIN_INLINE_EVENT_GET_ID(LW(3))
#else
            BEGIN_INLINE_EVENT
#endif
                CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
                CALL(evt_npc_get_height, LW(10), LW(3))
                ADD(LW(3), 10)
                CALL(evt_msg_toge, 2, LW(0), LW(3), LW(2))
                CALL(evt_msg_print, 0, LW(11), 0, LW(10))
            END_INLINE_EVENT
            BEGIN_INLINE_EVENT_GET_ID(LW(0))
                LOOP(0)
                    CALL(mario_flag, LW(10), LW(0))
                    IF_INT_EQUAL(LW(0), 1)
                        CALL(evt_msg_close, LW(11))
                        BREAK_LOOP
                    END_IF
                    WAIT_FRAMES(1)
                END_LOOP
            END_INLINE_EVENT
#if VERSION >= VERSION_US
            LOOP(0)
                IS_EVENT_RUNNING(LW(3), LW(4))
                IF_INT_EQUAL(LW(4), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
#else
            WAIT_MS(1000)
#endif
            DELETE_EVENT(LW(0))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(GF(10), 1)
            CALL(evt_msg_close, LW(11))
        END_IF
        LOOP(0)
            IF_INT_EQUAL(GF(10), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(evt_shop_moamoa_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG6_45_DAY_3_STARTS)
        SET_VALUE(LW(0), 0)
        CASE_LESS(STORY_STG6_46_ENGINEER)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_236_00"), 0, STRING("店員"))
        SET_VALUE(LW(0), -1)
        CASE_LESS(STORY_STG6_48_SMORG_MIASMA)
        IF_INT_EQUAL(GSWF(GSWF_RSH03_SHOP_CLERK_WOKEN), 0)
            CALL(evt_npc_set_anim, STRING("店員"), STRING("O_1"))
            WAIT_MS(500)
            CALL(evt_npc_flag_onoff, 0, STRING("店員"), NPC_FLAG_NO_TURN_TO_MARIO)
            CALL(evt_npc_flag_onoff, 1, STRING("店員"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_236_01"), 0, STRING("店員"))
            SET_VALUE(GSWF(GSWF_RSH03_SHOP_CLERK_WOKEN), 1)
        END_IF
        SET_VALUE(LW(0), 0)
        CASE_DEFAULT
        SET_VALUE(LW(0), 0)
    END_SWITCH
    RETURN
EVT_END()

static ShopObj obj_list[] = {
    {"sina_1", "a_sina_1"},
    {"sina_2", "a_sina_2"},
    {"sina_3", "a_sina_3"},
    {"sina_4", "a_sina_4"},
    {"sina_5", "a_sina_5"},
    {"sina_6", "a_sina_6"},
};

static ShopItem goods_list[] = {
    {ITEM_THUNDER_RAGE, 15},
    {ITEM_MYSTERY, 3},
    {ITEM_BOOS_SHEET, 20},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_MAPLE_SYRUP, 15},
    {ITEM_SUPER_SHROOM, 15},
};

static ShopDb trade_list[] = {
    {ITEM_THUNDER_RAGE, 7, 0},
    {ITEM_MYSTERY, 1, 0},
    {ITEM_BOOS_SHEET, 10, 0},
    {ITEM_TASTY_TONIC, 1, 0},
    {ITEM_MAPLE_SYRUP, 7, 0},
    {ITEM_SUPER_SHROOM, 7, 0},
    {ITEM_WHACKA_BUMP, 100, 0},
    {ITEM_COCONUT, 4, 0},
    {ITEM_DRIED_BOUQUET, 17, 0},
    {ITEM_MYSTIC_EGG, 6, 0},
    {ITEM_GOLDEN_LEAF, 7, 0},
    {ITEM_KEEL_MANGO, 4, 0},
    {ITEM_CAKE_MIX, 8, 0},
    {ITEM_HOT_SAUCE, 15, 0},
    {ITEM_TURTLEY_LEAF, 5, 0},
    {ITEM_HORSETAIL, 5, 0},
    {ITEM_PEACHY_PEACH, 8, 0},
    {0},
};

static ShopperData35 shopper_data = {
    /*"店員"*/"\x93\x58\x88\xF5", // name
    evt_shop_moamoa_talk, // fook_evt
    NULL, // buy_evt
    {"stg6_shop_00", "stg6_shop_01", "stg6_shop_02", "stg6_shop_03", "stg6_shop_04", "stg6_shop_05", "stg6_shop_06", "stg6_shop_07", "stg6_shop_08", "stg6_shop_09", "stg6_shop_10", "stg6_shop_11", "stg6_shop_12", "stg6_shop_13", "stg6_shop_14", "stg6_shop_15", "stg6_shop_16", "stg6_shop_17", "stg6_shop_18", "stg6_shop_19", "stg6_shop_20", "stg6_shop_21", "stg6_shop_22", "stg6_shop_23", "stg6_shop_24", "stg6_shop_25", "stg6_shop_26", "stg6_shop_27", "stg6_shop_28", "stg6_shop_29", "stg6_shop_30", "stg6_shop_31", "stg6_shop_32", "stg6_shop_33", "stg6_shop_34"}, // msgs
};

EVT_BEGIN(shop_door_open)
    CALL(evt_mapobj_get_position, STRING("S_tobira_omise"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_SLIDE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_map_playanim, STRING("mise_door_open"), 0, 0)
    CALL(evt_map_checkanim, STRING("mise_door_open"), LW(0), LW(1))
    WAIT_MS(LW(1))
    RETURN
EVT_END()

EVT_BEGIN(shop_door_close)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(evt_mapobj_get_position, STRING("S_tobira_omise"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_SLIDE1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING("mise_door_close"), 0, 0)
    CALL(evt_map_checkanim, STRING("mise_door_close"), LW(0), LW(1))
    WAIT_MS(LW(1))
    RETURN
EVT_END()

USER_FUNC(npc_alpha_except_tenin) {
    s32 alpha = evtGetValue(event, event->args[0]);
    NpcWork* wp = npcGetWorkPtr();
    s32 i;
    NpcEntry* npc;

    for (i = 0, npc = wp->entries; i < wp->total; i++, npc++) {
        // 店員
        if ((npc->flags & NPC_FLAG_USED) && (npc->flags & NPC_FLAG_ACTIVE) && strcmp(npc->description, "\x93\x58\x88\xF5") != 0) {
            npcSetColor(npc->description, (GXColor){0xFF, 0xFF, 0xFF, alpha});
        }
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(evt_shop_open)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("tobira_omise"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("tobira_omise_heya"), 8388608)
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        ADD(LW(12), 30)
        CALL(evt_party_move_pos, 0, LW(10), LW(12), 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        ADD(LW(12), 50)
        CALL(evt_party_move_pos, 1, LW(10), LW(12), 300)
    END_INLINE_EVENT
    CALL_CHILD(PTR(shop_door_open))
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        SUBTRACT(LW(12), 30)
        CALL(evt_mario_mov_pos, LW(10), LW(12), 300)
    END_INLINE_EVENT
    CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
    SUBTRACT(LW(12), 20)
    CALL(evt_party_move_pos, 0, LW(10), LW(12), 300)
    CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
    SUBTRACT(LW(12), 10)
    CALL(evt_party_move_pos, 1, LW(10), LW(12), 300)
    CALL_CHILD(PTR(shop_door_close))
    CALL(omiseHozon)
    CALL(evt_img_entry, STRING("capture_img"))
    CALL(evt_img_set_paper, STRING("capture_img"), STRING("OFF_d_jaba"))
    CALL(evt_img_free_capture, STRING("capture_img"), 0)
    CALL(evt_img_alloc_capture, STRING("capture_img"), 0, 0, 1, 0, 0, 608, 480)
    WAIT_FRAMES(1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("omise_soto"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shokudou"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kagu_s"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("tobira"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_tobira_omise"), MAPOBJ_FLAG_HIDE)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 255, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(npc_alpha_except_tenin, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF6_SHOP_IN1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_1"))
    CALL(evt_img_clear_virtual_point, STRING("capture_img"))
    CALL(evt_img_onoff, STRING("capture_img"), 1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("omise_masuku"), MAPOBJ_FLAG_HIDE)
    WAIT_FRAMES(1)
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("omise_soto"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("shokudou"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("kagu_s"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("tobira"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("s_tobira_omise"))
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("tobira_omise"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("tobira_omise_heya"), 8388608)
    CALL(evt_party_run, 1)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_shop_close)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    CALL(omiseFukki)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("tobira_omise"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 1, STRING("tobira_omise_heya"), 8388608)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF6_SHOP_OUT1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 0, 255, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(npc_alpha_except_tenin, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_img_clear_virtual_point, STRING("capture_img"))
    CALL(evt_img_set_paper_anim, STRING("capture_img"), STRING("A_2"))
    CALL(evt_img_onoff, STRING("capture_img"), 1)
    CALL(evt_img_wait_animend, STRING("capture_img"))
    CALL(evt_img_onoff, STRING("capture_img"), 0)
    CALL(evt_img_release, STRING("capture_img"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("omise_masuku"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("omise_soto"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("shokudou"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("kagu_s"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("tobira"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_tobira_omise"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_get_mapname, LW(10))
    IF_STR_EQUAL(LW(10), STRING("rsh_03_c"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_yuka1"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_sc"), MAPOBJ_FLAG_HIDE)
#endif
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("close"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_close"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_close"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_close"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_close"), MAPOBJ_FLAG_HIDE)
#else
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_sc"), MAPOBJ_FLAG_HIDE)
#endif
    END_IF
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("open"), MAPOBJ_FLAG_HIDE)
        CASE_END
        CASE_EQUAL(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(4)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(5)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
#endif
    CALL(evt_sub_get_mapname, LW(10))
    IF_STR_EQUAL(LW(10), STRING("rsh_03_a"))
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_20_END_OF_DAY_1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_yuka"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_yuka_simi"), MAPOBJ_FLAG_HIDE)
            CASE_DEFAULT
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_yuka"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_yuka_simi"), MAPOBJ_FLAG_HIDE)
        END_SWITCH
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(13), LW(14), LW(15))
        CALL(evt_mario_mov_pos, LW(13), LW(12), 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        SUBTRACT(LW(12), 20)
        CALL(evt_party_move_pos, 0, LW(10), LW(12), 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        SUBTRACT(LW(12), 30)
        CALL(evt_party_move_pos, 1, LW(10), LW(12), 300)
    END_INLINE_EVENT
    CALL_CHILD(PTR(shop_door_open))
    CALL(evt_cam3d_evt_off, 500, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        ADD(LW(12), 50)
        CALL(evt_mario_mov_pos, LW(10), LW(12), 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        ADD(LW(12), 30)
        CALL(evt_party_move_pos, 0, LW(10), LW(12), 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_hit_get_position, STRING("tobira_omise"), LW(10), LW(11), LW(12))
        ADD(LW(12), 10)
        CALL(evt_party_move_pos, 1, LW(10), LW(12), 300)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL_CHILD(PTR(shop_door_close))
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("tobira_omise"), 8388608)
    CALL(evt_hitobj_attr_onoff, 0, 0, STRING("tobira_omise_heya"), 8388608)
    CALL(evt_party_run, 1)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

USER_FUNC(fire) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    Vec pos;

    mapObjGetPos(name, &pos);
    mapObjFlagOn(name, 0x4000);
    effFireEntry(3, pos.x, pos.y - 4.0f, pos.z, 0.5f, 0);
    return EVT_RETURN_DONE;
}

EVT_BEGIN(evt_shop_door_init)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("omise_masuku"), MAPOBJ_FLAG_HIDE)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_OR_EQUAL(STORY_STG6_19_GIVE_BLANKET)
        CASE_OR_EQUAL(STORY_STG6_43_CONDUCTOR_APPEARS)
        CASE_END
        CASE_DEFAULT
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("tobira_omise"), 0, PTR(evt_shop_open), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("tobira_omise_heya"), 0, PTR(evt_shop_close), 0)
    END_SWITCH
    CALL(evt_paper_entry, STRING("OFF_d_jaba"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_yuka_simi)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_DOUBTFUL_POINT1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_51"), 0, 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_03_STAINED_CARPET)
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
        CALL(evt_msg_print_party, STRING("stg6_rsh_52"))
        CALL(evt_party_run, 0)
    END_IF
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_03_STAINED_CARPET)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static const char* access_tbl[] = {
    "table_1",
    "stg6_rsh_268",
    "stg6_rsh_268",
    "table_2",
    "stg6_rsh_268",
    "stg6_rsh_268",
    "oubun",
    "stg6_rsh_269",
    "stg6_rsh_269",
    "shokki",
    "stg6_rsh_270",
    "stg6_rsh_270",
    "memo",
    "stg6_rsh_271",
    "stg6_rsh_271",
    NULL,
};

static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_56_ROGUEPORT_STATION)
        CALL(evt_msg_print, 0, LW(1), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, LW(2), 0, 0)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(&access_tbl))
    LOOP(0)
        READ_INT3(LW(0), LW(1), LW(2))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_init_evt)
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
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_04_GRILLING_HEFF_T)
        CALL(evt_npc_setup, PTR(npc_data_lunch))
        CALL(evt_npc_set_position, STRING("コック"), 25, 1, -180)
        CALL(evt_npc_set_ry, STRING("コック"), 270)
        CALL(evt_npc_set_position, STRING("ウェイトレス"), -20, 1, -205)
        CALL(evt_npc_set_ry, STRING("ウェイトレス"), 90)
        CALL(evt_npc_set_position, STRING("トロン"), -50, 1, -170)
        CALL(evt_npc_set_ry, STRING("トロン"), 90)
        CALL(evt_npc_set_position, STRING("サラリーマン"), -65, 0, -120)
        CALL(evt_npc_set_ry, STRING("サラリーマン"), 90)
        CALL(evt_npc_set_position, STRING("ポワン探偵"), 45, 1, -135)
        CALL(evt_npc_set_ry, STRING("ポワン探偵"), 270)
        SPAWN_EVENT(PTR(evt_lunch_talk))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("nabe"), MAPOBJ_FLAG_HIDE)
        CASE_LESS(STORY_STG6_01_THE_CONDUCTOR)
        CALL(evt_npc_setup, PTR(npc_data))
        CASE_BETWEEN(STORY_STG6_05_GALLEY_KETTLE_DISCOVERED, STORY_STG7_00_START)
        CALL(evt_npc_setup, PTR(npc_data))
    END_SWITCH
    CALL_CHILD(PTR(evt_shop_door_init))
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(&shopper_data), PTR(trade_list))
    BEGIN_INLINE_EVENT
        LOOP(10)
            IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
                IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_48_SMORG_MIASMA)
                    IF_INT_EQUAL(GSWF(GSWF_RSH03_SHOP_CLERK_WOKEN), 0)
                        CALL(evt_npc_flag_onoff, 1, STRING("店員"), NPC_FLAG_NO_TURN_TO_MARIO)
                        CALL(evt_npc_flag_onoff, 0, STRING("店員"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
                        CALL(evt_npc_set_anim, STRING("店員"), STRING("D_1"))
                    END_IF
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL_CHILD(PTR(evt_access_entry))
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
        IF_STR_EQUAL(LW(0), STRING("rsh_03_a"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_2"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_03_b"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH3"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_2"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_03_c"))
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_2"))
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_a_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt))
    CALL_CHILD(PTR(evt_rsh_moamoa_on_window))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG6_01_THE_CONDUCTOR, STORY_STG6_20_END_OF_DAY_1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_yuka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_yuka_simi"), MAPOBJ_FLAG_HIDE)
        IF_INT_GREATER(GSW(GSW_STORY_PROGRESS), STORY_STG6_01_THE_CONDUCTOR)
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG6_05_GALLEY_KETTLE_DISCOVERED)
                CALL(evt_run_case_evt, CASE_COND_STAND_ON_A, 1, STRING("a_yuka_simi"), 0, PTR(evt_yuka_simi), 0)
            END_IF
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_yuka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_yuka_simi"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
    SPAWN_EVENT(PTR(evt_sub_mail_event))
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("open"), MAPOBJ_FLAG_HIDE)
        CASE_END
        CASE_EQUAL(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(4)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(5)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
#endif
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_b_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt))
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("open"), MAPOBJ_FLAG_HIDE)
        CASE_END
        CASE_EQUAL(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(4)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(5)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
#endif
    RETURN
EVT_END()

static const char* window_tbl[] = {
    "mado_uturi_1",
    "mado_uturi_2",
    "mado_uturi_3",
    "mado_uturi_4",
    NULL,
};

EVT_BEGIN(rsh_03_c_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt))
    CALL(evt_map_playanim, STRING("rousoku"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(PTR(evt_rsh_window))
    CALL(fire, STRING("rousoku_1"))
    CALL(fire, STRING("rousoku_2"))
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
#endif
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_OR_EQUAL(STORY_STG6_19_GIVE_BLANKET)
        CASE_OR_EQUAL(STORY_STG6_43_CONDUCTOR_APPEARS)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_open_yuka"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
        CALL(evt_sub_get_language, LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(0)
            CASE_OR_EQUAL(1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("close"), MAPOBJ_FLAG_HIDE)
            CASE_END
            CASE_EQUAL(2)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_close"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(3)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_close"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(4)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_close"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(5)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_close"), MAPOBJ_FLAG_HIDE)
        END_SWITCH
#else
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
#endif
        CASE_END
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_yuka1"), MAPOBJ_FLAG_HIDE)
#if VERSION <= VERSION_JP
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("close"), MAPOBJ_FLAG_HIDE)
#endif
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_sc"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
        CALL(evt_sub_get_language, LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(0)
            CASE_OR_EQUAL(1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("open"), MAPOBJ_FLAG_HIDE)
            CASE_END
            CASE_EQUAL(2)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_open"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(3)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_open"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(4)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
            CASE_EQUAL(5)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_open"), MAPOBJ_FLAG_HIDE)
        END_SWITCH
#endif
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_init_evt_nidome)
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
    CALL_CHILD(PTR(evt_shop_door_init))
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(&shopper_data), PTR(trade_list))
    IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_POSHLEY), 1)
        CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, PSND_FADE_OUT)
        CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_TRAIN_ARRIVED_ROGUEPORT), 1)
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
            CALL(evt_snd_envoff, PSND_FADE_OUT)
            CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
        ELSE
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_03_a"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_2"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_03_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_03_c"))
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG6_RSH1_2"))
            END_IF
        END_IF
    END_IF
    CALL_CHILD(PTR(evt_rsh_03_rnd_npc_entry))
    CALL_CHILD(PTR(evt_access_entry))
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("open"), MAPOBJ_FLAG_HIDE)
        CASE_END
        CASE_EQUAL(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(4)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_open"), MAPOBJ_FLAG_HIDE)
        CASE_EQUAL(5)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_open"), MAPOBJ_FLAG_HIDE)
    END_SWITCH
#endif
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_a_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt_nidome))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("s_yuka"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("s_yuka_simi"), MAPOBJ_FLAG_HIDE)
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_b_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt_nidome))
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_c_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt_nidome))
    CALL(evt_map_playanim, STRING("rousoku"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi"), 1, 0)
    SET_VALUE(LW(0), PTR(&window_tbl))
    CALL_CHILD(PTR(evt_rsh_window))
    CALL(fire, STRING("rousoku_1"))
    CALL(fire, STRING("rousoku_2"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_yuka1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("shop_close_sc"), MAPOBJ_FLAG_HIDE)
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_close"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_close"), MAPOBJ_FLAG_HIDE)
#endif
    RETURN
EVT_END()
