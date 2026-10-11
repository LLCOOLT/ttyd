#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "data/mapdata.h"
#include "mario/mariost.h"
#include "string.h"
#include "memory.h"
#include "driver/msgdrv.h"
#include "stdio.h"
#include "manager/evtmgr_cmd.h"
#include "dolphin/mtx.h"
#include "system.h"
#include "pmario_sound.h"

typedef void (*voidfunctionptr)(void);
extern voidfunctionptr _ctors[];
extern voidfunctionptr _dtors[];
extern s32 btl_gor_setup_no_tbl[];
extern s32 btlsetup_gor_tbl[];
extern s32 gor_00_init_evt[];
extern s32 gor_01_init_evt[];
extern s32 gor_02_init_evt[];
extern s32 gor_03_init_evt[];
extern s32 gor_04_init_evt[];
extern s32 gor_10_init_evt[];
extern s32 gor_11_init_evt[];
extern s32 gor_12_init_evt[];
void tegami_delete(void);
static s32 unk_gor_bss00000004;
static char* unk_gor_bss00000000;

USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_pose);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_win_other_select);
USER_FUNC(johoya_data_alloc);
USER_FUNC(johoya_data_free);
USER_FUNC(johoya_luigi_newjoho_setreadflag);
USER_FUNC(unk_gor_000000cc);
USER_FUNC(unk_gor_00000104);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
USER_FUNC(evt_goki_sub_intpl_get_value);
USER_FUNC(evt_goki_sub_intpl_init);
USER_FUNC(evt_gor_villager_urouro_check_func);
USER_FUNC(unk_gor_0000041c);
USER_FUNC(unk_gor_0000050c);
void _unresolved(void);
void _epilog(void);
void _prolog(void);

__declspec(section ".data") u64 fd_gor_negone_one_374;
__declspec(section ".data") s32 fd_gor_neg_one_382[1];
__declspec(section ".data") s32 fd_gor___local_PI_383[1];
__declspec(section ".data") s32 fd_gor___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_gor_one_negone_373;
__declspec(section ".data") s32 fd_gor___local_PIO2_384[1];
__declspec(section ".data") s32 fd_gor_one_381[1];
__declspec(section ".data") u64 fd_gor_negone_one_360;
__declspec(section ".data") s32 fd_gor_neg_one_365[1];
__declspec(section ".data") s32 fd_gor___local_PI_366[1];
__declspec(section ".data") s32 fd_gor___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_gor_one_negone_359;
__declspec(section ".data") s32 fd_gor___local_PIO2_367[1];
__declspec(section ".data") s32 fd_gor_one_364[1];
__declspec(section ".data") s32 fd_gor__three_localstatic4_sqrtf[2];
__declspec(section ".data") s32 fd_gor__half_localstatic3_sqrtf[2];
s32 gor_villager_urouro[19];
s32 inemuri_snd[27];
s32 mario_and_party_sleep[259];
s32 luigi_gor_first_talk[205];

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

USER_FUNC(unk_gor_0000050c) {
    if (unk_gor_bss00000000 == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(unk_gor_bss00000000);
    unk_gor_bss00000000 = NULL;
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_gor_0000041c) {
    s32* args = event->args;
    const char* head = (const char*)evtGetValue(event, args[0]);
    const char* msg = msgSearch((const char*)evtGetValue(event, args[1]));
    const char* tail = (const char*)evtGetValue(event, args[2]);
    s32 size = strlen(head) + strlen(msg) + strlen(tail) + 1;

    unk_gor_bss00000000 = _mapAlloc(size);
    memset(unk_gor_bss00000000, 0, size);
    sprintf(unk_gor_bss00000000, "%s%s%s", head, msg, tail);
    evtSetValue(event, args[3], (s32)unk_gor_bss00000000);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_gor_villager_urouro_check_func) {
    s32* args = event->args;
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
    s32* args = event->args;
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
    event->lwData[0] = intplGetValue(event->lwData[9], event->lwData[14], event->lwData[15], event->lwData[10], event->lwData[11]);
    event->lwData[1] = intplGetValue(event->lwData[9], event->lwData[14], event->lwData[15], event->lwData[12], event->lwData[13]);
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_gor_00000104) {
    unk_gor_bss00000004 = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_gor_000000cc) {
    if (unk_gor_bss00000004 != -1) {
        psndSFXOff(unk_gor_bss00000004);
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_gor_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_gor_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_gor_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_gor___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_gor___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_gor_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_gor___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_gor_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 fd_gor__three_localstatic4_sqrtf[] = {
    1074266112, 0,
};

__declspec(section ".data") s32 fd_gor__half_localstatic3_sqrtf[] = {
    1071644672, 0,
};

EVT_BEGIN(gor_villager_urouro)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(inemuri_snd)
    CALL(unk_gor_00000104, -1)
    LABEL(0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SLEEP1"), LW(0), LW(1), LW(2), LW(3))
    CALL(unk_gor_00000104, LW(3))
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
        CALL(unk_gor_000000cc)
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
    IF_INT_EQUAL(GSWF(1175), 0)
        CALL(evt_msg_print, 0, STRING("gor_luigi_00"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(500)
        IF_INT_LESS(GSW(0), 401)
            SET_VALUE(LW(2), STRING("gor_luigi_01"))
            ELSE
            SET_VALUE(LW(2), STRING("gor_luigi_01_1"))
        END_IF
        CALL(evt_msg_print, 0, LW(2), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_N_5B"))
        WAIT_MS(500)
        SET_VALUE(GSWF(1175), 1)
    END_IF
    SWITCH(GSW(0))
        CASE_BETWEEN(56, 111)
        SET_VALUE(LW(2), STRING("gor_luigi_02"))
        CASE_BETWEEN(112, 163)
        SET_VALUE(LW(2), STRING("gor_luigi_03"))
        CASE_BETWEEN(164, 214)
        SET_VALUE(LW(2), STRING("gor_luigi_04"))
        CASE_BETWEEN(215, 260)
        SET_VALUE(LW(2), STRING("gor_luigi_05"))
        CASE_BETWEEN(261, 338)
        SET_VALUE(LW(2), STRING("gor_luigi_06"))
        CASE_BETWEEN(339, 372)
        SET_VALUE(LW(2), STRING("gor_luigi_07"))
        CASE_BETWEEN(373, 400)
        SET_VALUE(LW(2), STRING("gor_luigi_08"))
        CASE_GREATER_OR_EQUAL(401)
        SET_VALUE(LW(2), STRING("gor_luigi_09"))
    END_SWITCH
    CALL(evt_msg_print, 0, LW(2), 0, STRING("me"))
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
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon_f, 257, STRING("BGM_EVT_RUIJI1"), 500)
        CALL(evt_snd_envoff, 1024)
        SET_VALUE(LW(10), 1)
    END_IF
    SET_VALUE(GF(0), 0)
    SPAWN_EVENT(PTR(mario_and_party_sleep))
    CALL(evt_msg_print, 0, LW(1), 0, STRING("me"))
    SET_VALUE(GF(0), 1)
    WAIT_WHILE(GF(0))
    CALL(johoya_luigi_newjoho_setreadflag)
    GOTO(0)
    LABEL(1)
    IF_INT_EQUAL(LW(10), 1)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
        CALL(evt_snd_envoff, 513)
        CALL(evt_snd_envon, 288, 0)
    END_IF
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

