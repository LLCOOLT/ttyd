#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario_pouch.h"
#include "mario/mario.h"
#include "driver/npcdrv.h"
#include "string.h"
#include "driver/camdrv.h"
#include "mario/mariost.h"
#include "driver/effdrv.h"

NpcEntry* fbatNpcTalkCheck(void);
static char tmp[32];
Vec camPt;
Vec camAt;
EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
void mapObjGetPos(const char* name, Vec* pos);
void mapObjFlagOn(const char* name, u32 flags);

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam3d_evt_set_rel);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_env_blur_on);
USER_FUNC(evt_hit_get_position);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_img_alloc_capture);
USER_FUNC(evt_img_clear_virtual_point);
USER_FUNC(evt_img_entry);
USER_FUNC(evt_img_free_capture);
USER_FUNC(evt_img_onoff);
USER_FUNC(evt_img_release);
USER_FUNC(evt_img_set_paper);
USER_FUNC(evt_img_set_paper_anim);
USER_FUNC(evt_img_wait_animend);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_item_get_item_end_wait);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_clear_offscreen);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mario_flag_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_mov_pos);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_set_dir_npc);
USER_FUNC(evt_mario_set_pose);
USER_FUNC(evt_msg_close);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_height);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_reglid);
USER_FUNC(evt_npc_jump_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_restart_regular_event);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_autotalkpose);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_setup);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_paper_entry);
USER_FUNC(evt_party_move_pos);
USER_FUNC(evt_party_move_pos2);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_dir_npc);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_pouch_check_item);
USER_FUNC(evt_pouch_remove_item);
USER_FUNC(evt_run_case_evt);
USER_FUNC(evt_set_dir_to_target);
USER_FUNC(evt_shop_setup);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_coin);
USER_FUNC(evt_sub_get_mapname);
USER_FUNC(evt_sub_intpl_msec_get_value);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_win_item_select);
USER_FUNC(fire);
USER_FUNC(iri_22_make_item_tbl);
static USER_FUNC(mario_flag);
USER_FUNC(omiseFukki);
USER_FUNC(omiseHozon);
USER_FUNC(unk_rsh_00002634);
extern s32 evt_bero_info_run[];
extern s32 evt_rsh_03_rnd_npc_entry[];
extern s32 evt_rsh_moamoa_on_window[];
extern s32 evt_rsh_window[];
extern s32 evt_sub_mail_event[];

__declspec(section ".data") u64 fd_rsh_03_negone_one_374;
__declspec(section ".data") s32 fd_rsh_03_neg_one_382[1];
__declspec(section ".data") s32 fd_rsh_03___local_PI_383[1];
__declspec(section ".data") s32 fd_rsh_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_rsh_03_one_negone_373;
__declspec(section ".data") s32 fd_rsh_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_rsh_03_one_381[1];
__declspec(section ".data") u64 fd_rsh_03_negone_one_360;
__declspec(section ".data") s32 fd_rsh_03_neg_one_365[1];
__declspec(section ".data") s32 fd_rsh_03___local_PI_366[1];
__declspec(section ".data") s32 fd_rsh_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_rsh_03_one_negone_359;
__declspec(section ".data") s32 fd_rsh_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_rsh_03_one_364[1];
static s32 bero_data_a[45];
static s32 bero_data_b[45];
static s32 bero_data_c[45];
s32 init_cook[29];
__declspec(section ".data") s32 item_tbl_cook[2];
s32 talk_cook_nabe_return[47];
__declspec(section ".data") s32 iri_22_item_tbl[4];
s32 talk_cook[351];
static s32 init_waitless[29];
__declspec(section ".data") s32 item_tbl_waitless[2];
s32 talk_waitless_pias_return[112];
static s32 talk_waitless[268];
s32 move_waitless[49];
static s32 npc_data[92];
static s32 talk_toron[20];
static s32 talk_sarary[31];
s32 dir_target[21];
s32 evt_lanch_missing[761];
static s32 talk_powan[184];
s32 npc_data_lunch[161];
static __declspec(section ".data") s32 msg_tbl[10];
s32 evt_lunch_talk[101];
s32 evt_shop_moamoa_talk[59];
static __declspec(section ".data") s32 obj_list[12];
static __declspec(section ".data") s32 goods_list[12];
static s32 trade_list[36];
static s32 shopper_data[38];
s32 shop_door_open[27];
s32 shop_door_close[31];
s32 evt_shop_open[267];
s32 evt_shop_close[317];
s32 evt_shop_door_init[36];
static s32 evt_yuka_simi[45];
static s32 access_tbl[16];
static s32 evt_access[25];
static s32 evt_access_entry[24];
s32 rsh_03_init_evt[269];
s32 rsh_03_a_init_evt[62];
__declspec(section ".data") s32 rsh_03_b_init_evt[11];
static __declspec(section ".data") s32 window_tbl[5];
s32 rsh_03_c_init_evt[71];
s32 rsh_03_init_evt_nidome[140];
s32 rsh_03_a_init_evt_nidome[23];
__declspec(section ".data") s32 rsh_03_b_init_evt_nidome[11];
s32 rsh_03_c_init_evt_nidome[50];

USER_FUNC(iri_22_make_item_tbl) {
    s32* args = event->args;
    u8 bought;
    s32 n;
    s32 i;

    bought = evtGetValue(NULL, GSW(1469));
    for (i = 0; i < 4; i++) {
        iri_22_item_tbl[i] = -1;
    }
    n = 0;
    if (!(bought & 1) && (s32)pouchCheckItem(0xA9) != 0) {
        iri_22_item_tbl[0] = 0xA9;
        n = 1;
    }
    if (!(bought & 2) && (s32)pouchCheckItem(0xA8) != 0) {
        iri_22_item_tbl[n++] = 0xA8;
    }
    if (!(bought & 4) && (s32)pouchCheckItem(0xAA) != 0) {
        iri_22_item_tbl[n++] = 0xAA;
    }
    evtSetValue(event, args[0], (s32)iri_22_item_tbl);
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}

static USER_FUNC(mario_flag) {
    static BOOL flg;
    s32* args = event->args;
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

__declspec(section ".data") u64 fd_rsh_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_rsh_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_03_one_364[] = {
    1065353216,
};

static s32 bero_data_a[] = {
    (s32)"w_bero", 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_a", (s32)"e_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", (s32)"e_bero",
    65544, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"rsh_02_a", (s32)"w_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_b[] = {
    (s32)"w_bero", 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_b", (s32)"e_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", (s32)"e_bero",
    65544, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"rsh_02_b", (s32)"w_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_c[] = {
    (s32)"w_bero", 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"rsh_04_c", (s32)"e_bero", 65537, (s32)"w_door_close", (s32)"w_door_open", (s32)"e_bero",
    65544, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)"rsh_02_c", (s32)"w_bero", 65537, (s32)"e_door_close", (s32)"e_door_open", 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(init_cook)
    SWITCH(GSW(0))
        CASE_BETWEEN(328, 332)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") s32 item_tbl_cook[] = {
    74, -1,
};

EVT_BEGIN(talk_cook_nabe_return)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_70_00"), 0, STRING("コック"))
    CALL(evt_win_item_select, 0, PTR(item_tbl_cook), LW(1), 0)
    IF_INT_NOT_EQUAL(LW(1), -1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_70_01"), 0, STRING("コック"))
        CALL(evt_item_entry, STRING("orei"), 125, 0, 0, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING("orei"))
        CALL(evt_item_get_item_end_wait, STRING("orei"))
        SET_VALUE(GSWF(5650), 1)
        CALL(evt_pouch_remove_item, 74, LW(0))
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") s32 iri_22_item_tbl[] = {
    -1, -1, -1, -1,
};

EVT_BEGIN(talk_cook)
    IF_INT_EQUAL(GSW(1420), 22)
        CALL(iri_22_make_item_tbl, LW(0), LW(1))
        IF_INT_EQUAL(GSWF(5405), 0)
            SET_VALUE(GSWF(5405), 1)
            IF_INT_EQUAL(LW(1), 0)
                CALL(evt_msg_print, 0, STRING("irai_22_00"), 0, 0)
                ELSE
                CALL(evt_msg_print, 0, STRING("irai_22_01"), 0, 0)
                GOTO(0)
            END_IF
            ELSE
            IF_INT_EQUAL(LW(1), 0)
                SWITCH(GSW(1469))
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
            CALL(evt_pouch_remove_item, 169, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_10"), 0, 0)
            OR(GSW(1469), 1)
            CASE_EQUAL(168)
            CALL(evt_pouch_remove_item, 168, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_11"), 0, 0)
            OR(GSW(1469), 2)
            CASE_EQUAL(170)
            CALL(evt_pouch_remove_item, 170, LW(0))
            CALL(evt_msg_print, 0, STRING("irai_22_12"), 0, 0)
            OR(GSW(1469), 4)
        END_SWITCH
        IF_INT_EQUAL(GSW(1469), 7)
            CALL(evt_msg_print_add, 0, STRING("irai_22_13"))
            CALL(evt_sub_get_coin, 40)
            SET_VALUE(GSW(1420), 0)
            SET_VALUE(GSWF(5396), 1)
            CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
            ELSE
            IF_INT_NOT_EQUAL(LW(1), -1)
                CALL(evt_msg_continue)
            END_IF
        END_IF
        RETURN
    END_IF
    CALL(evt_pouch_check_item, 74, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(talk_cook_nabe_return))
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(283)
        IF_INT_EQUAL(LSWF(5), 0)
            SET_VALUE(LSWF(5), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_04"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_05"), 0, 0)
        END_IF
        CASE_LESS(284)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_19"), 0, 0)
        CASE_LESS(287)
        IF_INT_EQUAL(GSWF(3428), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_40"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_50_1"), 0, 0)
        END_IF
        CASE_LESS(294)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_72"), 0, 0)
        CASE_LESS(301)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_72_01"), 0, 0)
        CASE_LESS(302)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_07"), 0, 0)
        CASE_LESS(310)
        IF_INT_EQUAL(LSWF(6), 0)
            SET_VALUE(LSWF(6), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_156"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_157"), 0, 0)
        END_IF
        CASE_LESS(326)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_212"), 0, 0)
        CASE_LESS(327)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_219"), 0, 0)
        CALL(evt_msg_print_party, STRING("stg6_rsh_219_2"))
        CASE_LESS(346)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_257"), 0, 0)
        CASE_LESS(402)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_12"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_12_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_waitless)
    SWITCH(GSW(0))
        CASE_BETWEEN(328, 332)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(1), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") s32 item_tbl_waitless[] = {
    76, -1,
};

EVT_BEGIN(talk_waitless_pias_return)
    CALL(evt_snd_bgmoff, 18432)
    CALL(evt_npc_get_reglid, STRING("ウェイトレス"), LW(10))
    DELETE_EVENT(LW(10))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_195"), 0, STRING("ウェイトレス"))
    CALL(evt_win_item_select, 0, PTR(item_tbl_waitless), LW(1), 0)
    IF_INT_NOT_EQUAL(LW(1), -1)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_4"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_196"), 0, STRING("ウェイトレス"))
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        CALL(evt_item_entry, STRING("orei"), 125, 0, 0, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING("orei"))
        CALL(evt_item_get_item_end_wait, STRING("orei"))
        SET_VALUE(GSWF(5651), 1)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_197"), 0, STRING("ウェイトレス"))
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("A_1"))
        WAIT_MS(500)
        CALL(evt_npc_set_anim, STRING("ウェイトレス"), STRING("S_1"))
        CALL(evt_pouch_remove_item, 76, LW(0))
        ELSE
        CALL(evt_msg_print, 0, STRING("stg6_rsh_196_2"), 0, STRING("ウェイトレス"))
    END_IF
    CALL(evt_npc_restart_regular_event, STRING("ウェイトレス"))
    SWITCH(GSW(0))
        CASE_BETWEEN(310, 325)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(334, 344)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmon, 160, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_waitless)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 288)
        IF_INT_EQUAL(GSWF(3432), 0)
            CALL(evt_snd_bgmoff, 18432)
            IF_INT_EQUAL(GSWF(3431), 0)
                SET_VALUE(GSWF(3431), 1)
                CALL(evt_msg_print, 0, STRING("stg6_rsh_74"), 0, 0)
                ELSE
                CALL(evt_msg_print, 0, STRING("stg6_rsh_77"), 0, 0)
            END_IF
            CALL(evt_msg_select, 0, STRING("stg6_rsh_77_yn"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_75"))
                SET_VALUE(GSWF(3432), 1)
                ELSE
                CALL(evt_msg_print_add, 0, STRING("stg6_rsh_76"))
            END_IF
            SWITCH(GSW(0))
                CASE_BETWEEN(310, 325)
                CALL(evt_snd_bgmoff, 26624)
                CASE_BETWEEN(334, 344)
                CALL(evt_snd_bgmoff, 26624)
                CASE_DEFAULT
                CALL(evt_snd_bgmon, 160, 0)
            END_SWITCH
            RETURN
        END_IF
    END_IF
    CALL(evt_pouch_check_item, 76, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(talk_waitless_pias_return))
        RETURN
    END_IF
    SWITCH(GSW(0))
        CASE_LESS(283)
        IF_INT_EQUAL(LSWF(7), 0)
            SET_VALUE(LSWF(7), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_02"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_03"), 0, 0)
        END_IF
        CASE_LESS(284)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_22"), 0, 0)
        CASE_LESS(287)
        IF_INT_EQUAL(GSWF(3428), 0)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_41"), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_47"), 0, 0)
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_48"), 0, STRING("トロン"))
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_49"), 0, 0)
        END_IF
        CASE_LESS(288)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_73"), 0, 0)
        CASE_LESS(301)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_78"), 0, 0)
        CASE_LESS(302)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_147_06"), 0, 0)
        CASE_LESS(310)
        IF_INT_EQUAL(LSWF(8), 0)
            SET_VALUE(LSWF(8), 1)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_154"), 0, 0)
            ELSE
            CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("H_1"), STRING("T_4"))
            CALL(evt_msg_print, 0, STRING("stg6_rsh_155"), 0, 0)
            CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        END_IF
        CASE_LESS(326)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("P_1"), STRING("T_5"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_199"), 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        CASE_LESS(327)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_218"), 0, 0)
        CASE_LESS(346)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_4"))
        CALL(evt_msg_print, 0, STRING("stg6_rsh_256"), 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING("me"), STRING("S_1"), STRING("T_1"))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_11"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_c_11_1"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(move_waitless)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 283)
        IF_INT_LESS(GSW(0), 287)
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

static s32 npc_data[] = {
    (s32)/*"コック"*/"\x83\x52\x83\x62\x83\x4E", 1073874448, 0, (s32)init_cook, 0, (s32)talk_cook, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58",
    1073874448, 0, (s32)init_waitless, (s32)move_waitless, (s32)talk_waitless, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"店員"*/"\x93\x58\x88\xF5", 1073874448,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(talk_toron)
    SWITCH(GSW(0))
        CASE_LESS(284)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_20"), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg6_rsh_42"), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_sarary)
    SWITCH(GSW(0))
        CASE_LESS(284)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_21"), 0, 0)
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(3428), 0)
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
    CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_POWAN1"))
    CALL(evt_snd_envoff, 1024)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), 32)
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
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SURPRISED2"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), 512)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_25"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), 512)
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
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_BOKE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), 512)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_27"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), 512)
    CALL(evt_cam3d_evt_set, 45, 75, 75, 45, 40, -122, 200, 11)
    WAIT_MS(200)
    SET_VALUE(LW(0), STRING("ポワン探偵"))
    SPAWN_EVENT(PTR(dir_target))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_28"), 0, STRING("ポワン探偵"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 102, 174, 0, 50, -122, 0, 11)
    WAIT_FRAMES(1)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_ADMIRE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
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
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), 512)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_29"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), 512)
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
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_BOKE1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), 512)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_33"), 0, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ポワン探偵"), 512)
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
    SET_VALUE(GSW(0), 284)
    CALL(evt_run_case_evt, 5, 1, STRING("a_yuka_simi"), 0, PTR(evt_yuka_simi), 0)
    CALL(evt_snd_envoff, 513)
    CALL(evt_snd_envon, 288, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ポワン探偵"), 32)
    CALL(evt_party_run, 0)
    SET_VALUE(GF(10), 0)
    RETURN
EVT_END()

static EVT_BEGIN(talk_powan)
    SWITCH(GSW(0))
        CASE_LESS(284)
        CALL_CHILD(PTR(evt_lanch_missing))
        CASE_DEFAULT
        IF_INT_EQUAL(GSWF(3428), 0)
            SET_INT_READ_ADDR(PTR(msg_tbl))
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
            SET_VALUE(GSWF(3428), 1)
            ELSE
            CALL(evt_msg_print, 0, STRING("stg6_rsh_46"), 0, 0)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

s32 npc_data_lunch[] = {
    (s32)/*"コック"*/"\x83\x52\x83\x62\x83\x4E", 1073874448, 0, 0, 0, (s32)talk_cook, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58",
    1073874448, 0, 0, 0, (s32)talk_waitless, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"店員"*/"\x93\x58\x88\xF5", 1073874448,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"トロン"*/"\x83\x67\x83\x8D\x83\x93", 1073874448, 0,
    0, 0, (s32)talk_toron, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"サラリーマン"*/"\x83\x54\x83\x89\x83\x8A\x81\x5B\x83\x7D\x83\x93", 1073874448, 0, 0,
    0, (s32)talk_sarary, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ポワン探偵"*/"\x83\x7C\x83\x8F\x83\x93\x92\x54\x92\xE3", 1073874448, 0, 0, 0,
    (s32)talk_powan, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

static __declspec(section ".data") s32 msg_tbl[] = {
    (s32)/*"コック"*/"\x83\x52\x83\x62\x83\x4E", (s32)"stg6_rsh_18_01", (s32)/*"トロン"*/"\x83\x67\x83\x8D\x83\x93", (s32)"stg6_rsh_18_02", (s32)/*"サラリーマン"*/"\x83\x54\x83\x89\x83\x8A\x81\x5B\x83\x7D\x83\x93", (s32)"stg6_rsh_18_03", (s32)/*"ウェイトレス"*/"\x83\x45\x83\x46\x83\x43\x83\x67\x83\x8C\x83\x58", (s32)"stg6_rsh_18_04",
    (s32)/*"ポワン探偵"*/"\x83\x7C\x83\x8F\x83\x93\x92\x54\x92\xE3", (s32)"stg6_rsh_18_05",
};

EVT_BEGIN(evt_lunch_talk)
    SET_VALUE(GF(10), 0)
    LOOP(0)
        SET_INT_READ_ADDR(PTR(msg_tbl))
        CALL(evt_sub_random, 4, LW(0))
        ADD(LW(0), 1)
        LOOP(LW(0))
            READ_INT2(LW(10), LW(11))
        END_LOOP
        CALL(mario_flag, LW(10), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BEGIN_INLINE_EVENT
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
            WAIT_MS(1000)
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
    SWITCH(GSW(0))
        CASE_LESS(328)
        SET_VALUE(LW(0), 0)
        CASE_LESS(329)
        CALL(evt_msg_print, 0, STRING("stg6_rsh_236_00"), 0, STRING("店員"))
        SET_VALUE(LW(0), -1)
        CASE_LESS(332)
        IF_INT_EQUAL(GSWF(3442), 0)
            CALL(evt_npc_set_anim, STRING("店員"), STRING("O_1"))
            WAIT_MS(500)
            CALL(evt_npc_flag_onoff, 0, STRING("店員"), 16777216)
            CALL(evt_npc_flag_onoff, 1, STRING("店員"), 1536)
            CALL(evt_msg_print, 0, STRING("stg6_rsh_236_01"), 0, STRING("店員"))
            SET_VALUE(GSWF(3442), 1)
        END_IF
        SET_VALUE(LW(0), 0)
        CASE_DEFAULT
        SET_VALUE(LW(0), 0)
    END_SWITCH
    RETURN
EVT_END()

static __declspec(section ".data") s32 obj_list[] = {
    (s32)"sina_1", (s32)"a_sina_1", (s32)"sina_2", (s32)"a_sina_2", (s32)"sina_3", (s32)"a_sina_3", (s32)"sina_4", (s32)"a_sina_4",
    (s32)"sina_5", (s32)"a_sina_5", (s32)"sina_6", (s32)"a_sina_6",
};

static __declspec(section ".data") s32 goods_list[] = {
    129, 15, 163, 3, 134, 20, 153, 3,
    155, 15, 149, 15,
};

static s32 trade_list[] = {
    129, 458752, 163, 65536, 134, 655360, 153, 65536,
    155, 458752, 149, 458752, 165, 6553600, 166, 262144,
    167, 1114112, 168, 393216, 169, 458752, 170, 262144,
    172, 524288, 173, 983040, 174, 327680, 175, 327680,
    176, 524288, 0, 0,
};

static s32 shopper_data[] = {
    (s32)/*"店員"*/"\x93\x58\x88\xF5", (s32)evt_shop_moamoa_talk, 0, (s32)"stg6_shop_00", (s32)"stg6_shop_01", (s32)"stg6_shop_02", (s32)"stg6_shop_03", (s32)"stg6_shop_04",
    (s32)"stg6_shop_05", (s32)"stg6_shop_06", (s32)"stg6_shop_07", (s32)"stg6_shop_08", (s32)"stg6_shop_09", (s32)"stg6_shop_10", (s32)"stg6_shop_11", (s32)"stg6_shop_12",
    (s32)"stg6_shop_13", (s32)"stg6_shop_14", (s32)"stg6_shop_15", (s32)"stg6_shop_16", (s32)"stg6_shop_17", (s32)"stg6_shop_18", (s32)"stg6_shop_19", (s32)"stg6_shop_20",
    (s32)"stg6_shop_21", (s32)"stg6_shop_22", (s32)"stg6_shop_23", (s32)"stg6_shop_24", (s32)"stg6_shop_25", (s32)"stg6_shop_26", (s32)"stg6_shop_27", (s32)"stg6_shop_28",
    (s32)"stg6_shop_29", (s32)"stg6_shop_30", (s32)"stg6_shop_31", (s32)"stg6_shop_32", (s32)"stg6_shop_33", (s32)"stg6_shop_34",
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

USER_FUNC(unk_rsh_00002634) {
    s32 alpha = evtGetValue(event, event->args[0]);
    NpcWork* wp = npcGetWorkPtr();
    s32 i;
    NpcEntry* npc;

    for (i = 0, npc = wp->entries; i < wp->total; i++, npc++) {
        // 店員
        if ((npc->flags & 1) && (npc->flags & 2) && strcmp(npc->description, "\x93\x58\x88\xF5") != 0) {
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
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("omise_soto"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shokudou"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("kagu_s"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("tobira"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_tobira_omise"), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 11, 255, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(unk_rsh_00002634, LW(0))
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
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("omise_masuku"), 1)
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
            CALL(unk_rsh_00002634, LW(0))
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
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("omise_masuku"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("omise_soto"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("shokudou"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("kagu_s"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("tobira"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_tobira_omise"), 1)
    CALL(evt_sub_get_mapname, LW(10))
    IF_STR_EQUAL(LW(10), STRING("rsh_03_c"))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_yuka1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("close"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_sc"), 1)
    END_IF
    CALL(evt_sub_get_mapname, LW(10))
    IF_STR_EQUAL(LW(10), STRING("rsh_03_a"))
        SWITCH(GSW(0))
            CASE_BETWEEN(283, 302)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_yuka"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_yuka_simi"), 1)
            CASE_DEFAULT
            CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_yuka"), 1)
            CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_yuka_simi"), 1)
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
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("omise_masuku"), 1)
    SWITCH(GSW(0))
        CASE_OR_EQUAL(301)
        CASE_OR_EQUAL(326)
        CASE_END
        CASE_DEFAULT
        CALL(evt_run_case_evt, 9, 1, STRING("tobira_omise"), 0, PTR(evt_shop_open), 0)
        CALL(evt_run_case_evt, 9, 1, STRING("tobira_omise_heya"), 0, PTR(evt_shop_close), 0)
    END_SWITCH
    CALL(evt_paper_entry, STRING("OFF_d_jaba"))
    RETURN
EVT_END()

static EVT_BEGIN(evt_yuka_simi)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_DOUBTFUL_POINT1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_51"), 0, 0)
    IF_INT_LESS(GSW(0), 285)
        CALL(evt_party_stop, 0)
        WAIT_MS(300)
        CALL(evt_msg_print_party, STRING("stg6_rsh_52"))
        CALL(evt_party_run, 0)
    END_IF
    SET_VALUE(GSW(0), 285)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static s32 access_tbl[] = {
    (s32)"table_1", (s32)"stg6_rsh_268", (s32)"stg6_rsh_268", (s32)"table_2", (s32)"stg6_rsh_268", (s32)"stg6_rsh_268", (s32)"oubun", (s32)"stg6_rsh_269",
    (s32)"stg6_rsh_269", (s32)"shokki", (s32)"stg6_rsh_270", (s32)"stg6_rsh_270", (s32)"memo", (s32)"stg6_rsh_271", (s32)"stg6_rsh_271", 0,
};

static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_LESS(GSW(0), 345)
        CALL(evt_msg_print, 0, LW(1), 0, 0)
        ELSE
        CALL(evt_msg_print, 0, LW(2), 0, 0)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(access_tbl))
    LOOP(0)
        READ_INT3(LW(0), LW(1), LW(2))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, 9, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(310, 325)
        CASE_GREATER_OR_EQUAL(333)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING("yure"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_sora"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_yama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_iwayama"), 1, 0)
        CALL(evt_map_playanim, STRING("hai_saboten"), 1, 0)
    END_SWITCH
    SWITCH(GSW(0))
        CASE_BETWEEN(283, 286)
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
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("nabe"), 1)
        CASE_LESS(283)
        CALL(evt_npc_setup, PTR(npc_data))
        CASE_BETWEEN(287, 352)
        CALL(evt_npc_setup, PTR(npc_data))
    END_SWITCH
    CALL_CHILD(PTR(evt_shop_door_init))
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    BEGIN_INLINE_EVENT
        LOOP(10)
            IF_INT_GREATER_OR_EQUAL(GSW(0), 328)
                IF_INT_LESS(GSW(0), 332)
                    IF_INT_EQUAL(GSWF(3442), 0)
                        CALL(evt_npc_flag_onoff, 1, STRING("店員"), 16777216)
                        CALL(evt_npc_flag_onoff, 0, STRING("店員"), 1536)
                        CALL(evt_npc_set_anim, STRING("店員"), STRING("D_1"))
                    END_IF
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL_CHILD(PTR(evt_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(284, 286)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(304, 309)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_POWAN1"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(310, 325)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_HOM1"))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(327, 328)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(329, 331)
        CALL(evt_snd_bgmon, 512, STRING("BGM_EVT_DANGER4"))
        CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_3"))
        CASE_BETWEEN(334, 344)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_sub_get_mapname, LW(0))
        IF_STR_EQUAL(LW(0), STRING("rsh_03_a"))
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH1"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_2"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_03_b"))
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH3"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_2"))
        END_IF
        IF_STR_EQUAL(LW(0), STRING("rsh_03_c"))
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH2"))
            CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_2"))
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
    SWITCH(GSW(0))
        CASE_BETWEEN(283, 302)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_yuka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_yuka_simi"), 1)
        IF_INT_GREATER(GSW(0), 283)
            IF_INT_LESS(GSW(0), 287)
                CALL(evt_run_case_evt, 5, 1, STRING("a_yuka_simi"), 0, PTR(evt_yuka_simi), 0)
            END_IF
        END_IF
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_yuka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_yuka_simi"), 1)
    END_SWITCH
    SPAWN_EVENT(PTR(evt_sub_mail_event))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(rsh_03_b_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_b))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt))
    RETURN
EVT_END()

static __declspec(section ".data") s32 window_tbl[] = {
    (s32)"mado_uturi_1", (s32)"mado_uturi_2", (s32)"mado_uturi_3", (s32)"mado_uturi_4", 0,
};

EVT_BEGIN(rsh_03_c_init_evt)
    SET_VALUE(LW(0), PTR(bero_data_c))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt))
    CALL(evt_map_playanim, STRING("rousoku"), 1, 0)
    CALL(evt_map_playanim, STRING("hosi"), 1, 0)
    SET_VALUE(LW(0), PTR(window_tbl))
    CALL_CHILD(PTR(evt_rsh_window))
    CALL(fire, STRING("rousoku_1"))
    CALL(fire, STRING("rousoku_2"))
    SWITCH(GSW(0))
        CASE_OR_EQUAL(301)
        CASE_OR_EQUAL(326)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_open_yuka"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("open"), 1)
        CASE_END
        CASE_DEFAULT
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_yuka1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("close"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_sc"), 1)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_init_evt_nidome)
    IF_INT_EQUAL(GSWF(3579), 0)
        IF_INT_EQUAL(GSWF(3580), 0)
            IF_INT_EQUAL(GSWF(3581), 0)
                CALL(evt_map_playanim, STRING("yure"), 1, 0)
                IF_INT_EQUAL(GSWF(3578), 0)
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
    CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(shopper_data), PTR(trade_list))
    IF_INT_EQUAL(GSWF(3460), 1)
        CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_PIK1"))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
            CALL(evt_snd_bgmon, 512, STRING("BGM_STG0_GOR1"))
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_sub_get_mapname, LW(0))
            IF_STR_EQUAL(LW(0), STRING("rsh_03_a"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH1"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_2"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_03_b"))
            END_IF
            IF_STR_EQUAL(LW(0), STRING("rsh_03_c"))
                CALL(evt_snd_bgmon, 512, STRING("BGM_STG6_RSH2"))
                CALL(evt_snd_envon, 272, STRING("ENV_STG6_RSH1_2"))
            END_IF
        END_IF
    END_IF
    CALL_CHILD(PTR(evt_rsh_03_rnd_npc_entry))
    CALL_CHILD(PTR(evt_access_entry))
    RETURN
EVT_END()

EVT_BEGIN(rsh_03_a_init_evt_nidome)
    SET_VALUE(LW(0), PTR(bero_data_a))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_03_init_evt_nidome))
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("s_yuka"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("s_yuka_simi"), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(rsh_03_b_init_evt_nidome)
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
    SET_VALUE(LW(0), PTR(window_tbl))
    CALL_CHILD(PTR(evt_rsh_window))
    CALL(fire, STRING("rousoku_1"))
    CALL(fire, STRING("rousoku_2"))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_yuka1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("close"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("shop_close_sc"), 1)
    RETURN
EVT_END()

