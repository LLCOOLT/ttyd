#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/camdrv.h"
#include "mario/mariost.h"
#include "evt/evt_bero.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_npc.h"
#include "evt/evt_case.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"

USER_FUNC(camera_action);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_env_blur_on);
USER_FUNC(evt_exit_case_evt);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_item_delete_check);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mario_bgmode_on);
USER_FUNC(evt_mario_cam_y_off);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_normalize);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_toge);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_npc_check);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_start_for_event);
USER_FUNC(evt_npc_stop_for_event);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_sfxon_3d);

__declspec(section ".data") u64 fd_win_03_negone_one_374;
__declspec(section ".data") s32 fd_win_03_neg_one_382[1];
__declspec(section ".data") s32 fd_win_03___local_PI_383[1];
__declspec(section ".data") s32 fd_win_03___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_win_03_one_negone_373;
__declspec(section ".data") s32 fd_win_03___local_PIO2_384[1];
__declspec(section ".data") s32 fd_win_03_one_381[1];
__declspec(section ".data") u64 fd_win_03_negone_one_360;
__declspec(section ".data") s32 fd_win_03_neg_one_365[1];
__declspec(section ".data") s32 fd_win_03___local_PI_366[1];
__declspec(section ".data") s32 fd_win_03___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_win_03_one_negone_359;
__declspec(section ".data") s32 fd_win_03___local_PIO2_367[1];
__declspec(section ".data") s32 fd_win_03_one_364[1];
__declspec(section ".data") s32 clouda_house_in[12];
s32 clouda_house_out[19];
__declspec(section ".data") s32 cloud_out[12];
__declspec(section ".data") s32 cloud_in[12];
static s32 bero_entry_data[75];
s32 lookat_house[45];
static s32 cloud_toujou[76];
s32 cloud_lostitem[215];
s32 tree_evt_01[20];
static s32 tree_access_data[30];
__declspec(section ".data") s32 dummy_event[4];
s32 win_03_init_evt[108];

__declspec(section ".data") u64 fd_win_03_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_03_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_03___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_03___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_03_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_03___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_03_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_win_03_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_win_03_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_win_03___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_win_03___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_win_03_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_win_03___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_win_03_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(clouda_house_in)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_mapchange, STRING("win_04"), STRING("w_bero"))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(clouda_house_out)
    CALL(evt_mario_bgmode_on)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_cam_y_off)
    CALL(evt_mario_set_pos, 277, 54, -450)
    CALL_CHILD(PTR(bero_case_entry))
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(cloud_out)
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD2"), 306, 23, -448, 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(cloud_in)
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD3"), 306, 23, -448, 0)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"w_bero", 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"win_02", (s32)"e_bero", 65537, 0, 0, (s32)"dokan_1",
    131072, 9, 100000, 0, 0, -1, 0, 6,
    0, 0, (s32)"dokan_2", 65537, 0, 0, (s32)"dokan_2", 268566528,
    9, 100000, 0, 0, -1, 0, 6, 0,
    0, (s32)"dokan_1", 65537, 0, 0, (s32)"n_bero", 268632064, 2,
    100000, 0, 0, -1, (s32)cloud_out, 5, (s32)cloud_in, (s32)"win_04",
    (s32)"w_bero", 65537, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

EVT_BEGIN(lookat_house)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(0), 200)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    CALL(evt_mario_normalize)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_02"), 0, STRING("extparty"))
    SET_VALUE(GSW(0), 80)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_start_for_event)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

USER_FUNC(camera_action) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec pos = {290.0f, 150.0f, 491.0f};
    Vec at = {290.0f, 90.0f, -6.0f};
    f32 x;

    if (isFirstCall) {
        f32 speed;
        f32 dist;

        ((f32*)event->lwData)[0] = 0.0f;
        ((f32*)event->lwData)[1] = 2.5f;
        event->lwData[2] = 0;
        speed = 0.0f;
        dist = 0.0f;
        while (TRUE) {
            if (speed >= 2.5f) {
                break;
            }
            speed += 0.01f;
            dist += speed;
        }
        ((f32*)event->lwData)[2] = dist - 2.5f;
    }
    if (((f32*)event->lwData)[0] < 300.0f - ((f32*)event->lwData)[2]) {
        ((f32*)event->lwData)[0] += ((f32*)event->lwData)[1];
        x = -10.0f + ((f32*)event->lwData)[0];
        event->lwData[10] = 0;
        at.x = pos.x = x;
    } else if (((f32*)event->lwData)[0] < 300.0f) {
        ((f32*)event->lwData)[0] += ((f32*)event->lwData)[1];
        ((f32*)event->lwData)[1] -= 0.01f;
        x = -10.0f + ((f32*)event->lwData)[0];
        event->lwData[10] = 0;
        at.x = pos.x = x;
    } else {
        event->lwData[10] = 1;
    }
    cam->presetPos = cam->cameraPos;
    cam->presetAt = cam->cameraAt;
    cam->storedPos = pos;
    cam->storedAt = at;
    cam->startTimeA = gp->renderTime;
    cam->durationA = 0;
    cam->stateA = 3;
    cam->curveA = 11;
    return event->lwData[10] == 0 ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

static EVT_BEGIN(cloud_toujou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    CALL(evt_cam3d_evt_set, -10, 150, 491, -10, 90, -6, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(camera_action)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_01"), 0, 0)
    CALL(evt_fade_set_mapchange_type, 0, 2, 500, 1, 500)
    CALL(evt_bero_mapchange, STRING("win_04"), STRING(""))
    RETURN
EVT_END()

EVT_BEGIN(cloud_lostitem)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_party_cont_onoff, 1, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    CALL(evt_npc_check, STRING("パックン1"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING("パックン1"), 0, -100, 0)
    END_IF
    CALL(evt_npc_check, STRING("パックン2"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_set_position, STRING("パックン2"), 0, -100, 0)
    END_IF
    CALL(evt_cam3d_evt_set, 290, 150, 491, 290, 90, -6, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1000)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 1, 600)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 290, 137, 391, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        CALL(evt_cam3d_evt_set, 290, 150, 491, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        CALL(evt_cam3d_evt_set, 290, 137, 391, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        CALL(evt_cam3d_evt_set, 290, 150, 491, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        CALL(evt_cam3d_evt_set, 290, 137, 391, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        CALL(evt_cam3d_evt_set, 290, 150, 491, 290, 90, -6, 100, 11)
        WAIT_MS(100)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING("BGM_FF_ENV_SURPRISED3"))
        WAIT_MS(3000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg2_win_e04_00_05"), 0, 0)
    WAIT_WHILE(GF(0))
    WAIT_MS(2000)
    SET_VALUE(GSW(0), 78)
    CALL(evt_fade_set_mapchange_type, 0, 2, 500, 1, 500)
    CALL(evt_bero_mapchange, STRING("win_01"), STRING("n_bero"))
    RETURN
EVT_END()

EVT_BEGIN(tree_evt_01)
    CALL(evt_item_delete_check, STRING("item_tree01"), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_item_entry, STRING("item_tree01"), 125, -333, 72, -24, 0, GSWF(5609), 0)
    END_IF
    RETURN
EVT_END()

static s32 tree_access_data[] = {
    4, (s32)"A_tree_01", (s32)"S_tree_mki_01", (s32)"S_tree_ha01", 0, 0, 4, (s32)"A_tree_02",
    (s32)"S_tree_mki_02", (s32)"S_tree_ha03", 0, (s32)tree_evt_01, 4, (s32)"A_tree_03", (s32)"S_tree_mki_03", (s32)"S_tree_ha02",
    0, 0, 4, (s32)"A_tree_04", (s32)"S_tree_mki_04", (s32)"S_tree_ha04", 0, 0,
    7, 0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(dummy_event)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

s32 win_03_init_evt[] = {
    131122, -30000000, (s32)bero_entry_data, 65627, (s32)evt_bero_get_info, 65630, (s32)evt_bero_info_run, 458843,
    (s32)evt_run_case_evt, 5, 1, (s32)"n_bero", 0, (s32)dummy_event, 0, 196699,
    (s32)evt_snd_bgmon, 512, (s32)"BGM_STG2_WIN1", 196699, (s32)evt_snd_envon, 272, (s32)"ENV_STG2_WIN1", 196699,
    (s32)evt_snd_bgmon, 160, 0, 131122, -30000000, (s32)tree_access_data, 65630, (s32)evt_sub_tree_access_entry,
    524379, (s32)evt_mobj_recovery_blk, (s32)"mobj_recover", 7, 425, 60, 75, 0,
    0, 589915, (s32)evt_item_entry, (s32)"i", 135, 475, 0, -60,
    16, -129997321, 0, 589915, (s32)evt_item_entry, (s32)"item_00", 125, -150,
    0, -30, 16, -129994390, 0, 327771, (s32)evt_mapobj_flag_onoff, 1,
    1, (s32)"S_ana", 1, 327771, (s32)evt_mapobj_flag_onoff, 1, 1, (s32)"S_siro_asu",
    1, 262235, (s32)evt_hitobj_onoff, (s32)"A_siro_asu", 1, 0, 131096, -170000000,
    79, 65628, (s32)lookat_house, 33, 131096, -170000000, 76, 131163,
    (s32)evt_npc_check_delete, (s32)/*"パックン1"*/"\x83\x70\x83\x62\x83\x4E\x83\x93\x31", 65628, (s32)cloud_toujou, 33, 131096, -170000000, 77,
    131163, (s32)evt_npc_check_delete, (s32)/*"パックン1"*/"\x83\x70\x83\x62\x83\x4E\x83\x93\x31", 65628, (s32)cloud_lostitem, 33, 2, 1,
    0, 0, 0, 0,
};

