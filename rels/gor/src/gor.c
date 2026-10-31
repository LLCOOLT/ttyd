// gor.rel (ゴロツキタウン, Rogueport): shared code and the REL prolog/epilog.
// Registers the init events of gor_00..gor_04 and gor_10..gor_12.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "data/mapdata.h"
#include "mario/mariost.h"
#include "string.h"
#include "memory.h"
#include "driver/msgdrv.h"
#include "stdio.h"
#include "manager/evtmgr_cmd.h"
#include "dolphin/mtx.h"
#include "evt/evt_johoya.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_urouro.h"
#include "evt/evt_window.h"
#include "system.h"
#include "pmario_sound.h"
#include "gor.h"
#include "evt/evt_story.h"
#include "rel_module.h"

#if VERSION >= VERSION_JP
static s32 gor_inemuri_snd_id;
static char* gor_msg_cat_buf;
#endif

void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("gor_00", gor_00_init_evt);
    relSetEvtAddr("gor_01", gor_01_init_evt);
    relSetEvtAddr("gor_02", gor_02_init_evt);
    relSetEvtAddr("gor_03", gor_03_init_evt);
    relSetEvtAddr("gor_04", gor_04_init_evt);
    relSetEvtAddr("gor_10", gor_10_init_evt);
    relSetEvtAddr("gor_11", gor_11_init_evt);
    relSetEvtAddr("gor_12", gor_12_init_evt);
    relSetBtlAddr("gor", btlsetup_gor_tbl, btl_gor_setup_no_tbl);
}

void _epilog(void) {
    voidfunctionptr* dtor;

    if (strcmp(gp->currentMapName, "gor_10") == 0) {
        tegami_delete();
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

void _unresolved(void) {
}

#if VERSION >= VERSION_JP
USER_FUNC(evt_gor_msg_cat_free) {
    if (gor_msg_cat_buf == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(gor_msg_cat_buf);
    gor_msg_cat_buf = NULL;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_gor_msg_cat_alloc) {
    EvtWord* args = event->args;
    const char* head = (const char*)evtGetValue(event, args[0]);
    const char* msg = msgSearch((const char*)evtGetValue(event, args[1]));
    const char* tail = (const char*)evtGetValue(event, args[2]);
    s32 size = strlen(head) + strlen(msg) + strlen(tail) + 1;

    gor_msg_cat_buf = _mapAlloc(size);
    memset(gor_msg_cat_buf, 0, size);
    sprintf(gor_msg_cat_buf, "%s%s%s", head, msg, tail);
    evtSetValue(event, args[3], (EvtWord)gor_msg_cat_buf);
    return EVT_RETURN_DONE;
}
#endif

USER_FUNC(evt_gor_villager_urouro_check_func) {
    EvtWord* args = event->args;
    s32 xVar = args[0];
    s32 zVar = args[1];
    f32 cx = evtGetFloat(event, args[2]);
    f32 cz = evtGetFloat(event, args[3]);
    f32 radius = evtGetFloat(event, args[4]);
    f32 x = evtGetFloat(event, xVar);
    f32 z = evtGetFloat(event, zVar);
    Vec pos;
    Vec center;

    pos = (Vec){x, 0.0f, z};
    center = (Vec){cx, 0.0f, cz};
    if (PSVECDistance(&center, &pos) <= radius) {
        return EVT_RETURN_DONE;
    }
    evtSetFloat(event, xVar, cx);
    evtSetFloat(event, zVar, cz);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_goki_sub_intpl_init) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 x0 = evtGetValue(event, args[1]);
    s32 x1 = evtGetValue(event, args[2]);
    s32 y0 = evtGetValue(event, args[3]);
    s32 y1 = evtGetValue(event, args[4]);
    s32 steps = evtGetValue(event, args[5]);

    event->lwData[9] = mode;
    event->lwData[10] = x0;
    event->lwData[11] = x1;
    event->lwData[12] = y0;
    event->lwData[13] = y1;
    event->lwData[14] = 0;
    event->lwData[15] = steps;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_goki_sub_intpl_get_value) {
    event->lwData[0] = intplGetValue(event->lwData[9], event->lwData[10], event->lwData[11], event->lwData[14], event->lwData[15]);
    event->lwData[1] = intplGetValue(event->lwData[9], event->lwData[12], event->lwData[13], event->lwData[14], event->lwData[15]);
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
USER_FUNC(evt_gor_inemuri_snd_set) {
    gor_inemuri_snd_id = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_gor_inemuri_snd_off) {
    if (gor_inemuri_snd_id != -1) {
        psndSFXOff(gor_inemuri_snd_id);
    }
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(gor_villager_urouro)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(inemuri_snd)
#if VERSION >= VERSION_JP
    CALL(evt_gor_inemuri_snd_set, -1)
#endif
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SLEEP1"), LW(0), LW(1), LW(2), 0)
#else
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SLEEP1"), LW(0), LW(1), LW(2), LW(3))
    CALL(evt_gor_inemuri_snd_set, LW(3))
#endif
    WAIT_FRAMES(140)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(mario_and_party_sleep)
    SET_VALUE(LW(1), 1200)
    SET_VALUE(LW(2), 900)
    SET_VALUE(LW(3), 600)
    SET_VALUE(LF(0), 0)
    SET_VALUE(LW(15), -1)
    LOOP(0)
        IF_INT_EQUAL(LW(1), 0)
            CALL(evt_mario_set_pose, STRING("M_N_5A"))
            SPAWN_EVENT_GET_ID(PTR(inemuri_snd), LW(15))
        END_IF
        IF_INT_EQUAL(LW(2), 0)
            CALL(evt_mario_get_party, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                SWITCH(LW(0))
                    CASE_EQUAL(1)
                    CALL(evt_party_set_pose, 0, STRING("PKR_N_1"))
                    CASE_EQUAL(2)
                    CALL(evt_party_set_pose, 0, STRING("PNK_N_1"))
                    CASE_EQUAL(3)
                    CALL(evt_party_set_pose, 0, STRING("PBM_N_1"))
                    CASE_EQUAL(4)
                    CALL(evt_party_set_pose, 0, STRING("PYS_N_1"))
                    CASE_EQUAL(5)
                    CALL(evt_party_set_pose, 0, STRING("PWD_N_1"))
                    CASE_EQUAL(6)
                    CALL(evt_party_set_pose, 0, STRING("PTR_N_1"))
                    CASE_EQUAL(7)
                    CALL(evt_party_set_pose, 0, STRING("PCH_N_1"))
                END_SWITCH
            END_IF
        END_IF
        IF_INT_EQUAL(LW(3), 0)
            IF_INT_EQUAL(LF(0), 0)
                SET_VALUE(LF(0), 1)
                SET_VALUE(LW(3), 51)
                CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
                CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_YAWN1"), LW(4), LW(5), LW(6), 0)
                CALL(evt_mario_set_pose, STRING("M_I_5"))
            ELSE
                SET_VALUE(LF(0), 0)
                CALL(evt_mario_set_pose, STRING("M_S_1"))
            END_IF
        END_IF
        WAIT_FRAMES(1)
        IF_INT_NOT_EQUAL(GF(0), 0)
            BREAK_LOOP
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(1), 0)
            SUBTRACT(LW(1), 1)
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(2), 0)
            SUBTRACT(LW(2), 1)
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(3), 0)
            SUBTRACT(LW(3), 1)
        END_IF
    END_LOOP
    IF_INT_NOT_EQUAL(LW(15), -1)
        DELETE_EVENT(LW(15))
#if VERSION >= VERSION_JP
        CALL(evt_gor_inemuri_snd_off)
#endif
    END_IF
    IF_INT_LESS_OR_EQUAL(LW(2), 0)
        CALL(evt_mario_get_party, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SWITCH(LW(0))
                CASE_EQUAL(1)
                CALL(evt_party_set_pose, 0, STRING("PKR_S_1"))
                CASE_EQUAL(2)
                CALL(evt_party_set_pose, 0, STRING("PNK_S_1"))
                CASE_EQUAL(3)
                CALL(evt_party_set_pose, 0, STRING("PBM_S_1"))
                CASE_EQUAL(4)
                CALL(evt_party_set_pose, 0, STRING("PYS_S_1"))
                CASE_EQUAL(5)
                CALL(evt_party_set_pose, 0, STRING("PWD_S_1"))
                CASE_EQUAL(6)
                CALL(evt_party_set_pose, 0, STRING("PTR_S_1"))
                CASE_EQUAL(7)
                CALL(evt_party_set_pose, 0, STRING("PCH_S_1"))
            END_SWITCH
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        IF_INT_NOT_EQUAL(LW(3), 0)
            SUBTRACT(LW(3), 1)
        END_IF
        WAIT_FRAMES(LW(3))
        CALL(evt_mario_set_pose, STRING("M_S_1"))
    END_IF
    IF_INT_LESS_OR_EQUAL(LW(1), 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_AWAKE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_5B"))
        WAIT_MS(550)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
    END_IF
    SET_VALUE(GF(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(luigi_gor_first_talk)
    CALL(evt_party_stop, 0)
    IF_INT_EQUAL(GSWF(GSWF_GOR_LUIGI_FIRST_TALK), 0)
        CALL(evt_msg_print, 0, STRING("gor_luigi_00"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(500)
        // Both demos print the greeting in each branch; the releases pick the message into LW(2) and print it once
#if VERSION <= VERSION_DEMO_US
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG8_16_SHADOW_QUEEN)
            CALL(evt_msg_print, 0, STRING("gor_luigi_01"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("gor_luigi_01_1"), 0, STRING("me"))
        END_IF
#else
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG8_16_SHADOW_QUEEN)
            SET_VALUE(LW(2), STRING("gor_luigi_01"))
        ELSE
            SET_VALUE(LW(2), STRING("gor_luigi_01_1"))
        END_IF
        CALL(evt_msg_print, 0, LW(2), 0, STRING("me"))
#endif
        CALL(evt_mario_set_pose, STRING("M_N_5B"))
        WAIT_MS(500)
        SET_VALUE(GSWF(GSWF_GOR_LUIGI_FIRST_TALK), 1)
    END_IF
    // Both demos print each Luigi line in its case; the releases pick the message into LW(2) and print it once
#if VERSION <= VERSION_DEMO_US
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG1_17_FATHER_AND_SON_REUNITED, STORY_STG2_24_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_luigi_02"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        CALL(evt_msg_print, 0, STRING("gor_luigi_03"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG3_32_BOSS_BATTLE, STORY_STG4_15_04_SHADOW_SIRENS_AND_DOOPLISS)
        CALL(evt_msg_print, 0, STRING("gor_luigi_04"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL(evt_msg_print, 0, STRING("gor_luigi_05"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG5_43_X_NAUTS_RETREAT, STORY_STG6_53_THE_REAL_GARNET_STAR)
        CALL(evt_msg_print, 0, STRING("gor_luigi_06"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG6_54_WELCOME_BACK, STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP)
        CALL(evt_msg_print, 0, STRING("gor_luigi_07"), 0, STRING("me"))
        CASE_BETWEEN(STORY_STG7_20_LORD_CRUMP_DEFEATED, STORY_STG8_15_GRODUS)
        CALL(evt_msg_print, 0, STRING("gor_luigi_08"), 0, STRING("me"))
        CASE_GREATER_OR_EQUAL(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_luigi_09"), 0, STRING("me"))
    END_SWITCH
#else
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG1_17_FATHER_AND_SON_REUNITED, STORY_STG2_24_BOSS_BATTLE)
        SET_VALUE(LW(2), STRING("gor_luigi_02"))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        SET_VALUE(LW(2), STRING("gor_luigi_03"))
        CASE_BETWEEN(STORY_STG3_32_BOSS_BATTLE, STORY_STG4_15_04_SHADOW_SIRENS_AND_DOOPLISS)
        SET_VALUE(LW(2), STRING("gor_luigi_04"))
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        SET_VALUE(LW(2), STRING("gor_luigi_05"))
        CASE_BETWEEN(STORY_STG5_43_X_NAUTS_RETREAT, STORY_STG6_53_THE_REAL_GARNET_STAR)
        SET_VALUE(LW(2), STRING("gor_luigi_06"))
        CASE_BETWEEN(STORY_STG6_54_WELCOME_BACK, STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP)
        SET_VALUE(LW(2), STRING("gor_luigi_07"))
        CASE_BETWEEN(STORY_STG7_20_LORD_CRUMP_DEFEATED, STORY_STG8_15_GRODUS)
        SET_VALUE(LW(2), STRING("gor_luigi_08"))
        CASE_GREATER_OR_EQUAL(STORY_STG8_16_SHADOW_QUEEN)
        SET_VALUE(LW(2), STRING("gor_luigi_09"))
    END_SWITCH
    CALL(evt_msg_print, 0, LW(2), 0, STRING("me"))
#endif
    CALL(evt_msg_select, 0, STRING("gor_luigi_yesno"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("gor_luigi_12"))
        GOTO(1)
    END_IF
    CALL(evt_msg_print_add, 0, STRING("gor_luigi_11"))
    CALL(johoya_data_alloc, STRING("gor_luigi_talk"))
    SET_VALUE(LW(10), 0)
    LABEL(0)
    CALL(evt_win_other_select, 18)
    IF_INT_EQUAL(LW(0), 0)
        CALL(johoya_data_free)
        CALL(evt_msg_print, 0, STRING("gor_luigi_13"), 0, STRING("me"))
        GOTO(1)
    END_IF
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon_f, PSND_FADE_IN | PSND_CH(1), STRING("BGM_EVT_RUIJI1"), 500)
        CALL(evt_snd_envoff, PSND_FADE_HOLD)
        SET_VALUE(LW(10), 1)
    END_IF
    SET_VALUE(GF(0), 0)
    SPAWN_EVENT(mario_and_party_sleep)
    CALL(evt_msg_print, 0, LW(1), 0, STRING("me"))
    SET_VALUE(GF(0), 1)
    WAIT_WHILE(GF(0))
    CALL(johoya_luigi_newjoho_setreadflag)
    GOTO(0)
    LABEL(1)
    IF_INT_EQUAL(LW(10), 1)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
        CALL(evt_snd_envoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_IF
    CALL(evt_party_run, 0)
    RETURN
EVT_END()
