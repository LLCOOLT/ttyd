#pragma optimize_for_size on
#include "battle/battle_seq_end.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "battle/battle_audience.h"
#include "battle/battle_stage_object.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "driver/npcdrv.h"
#include "driver/windowdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "system.h"
#include "battle/battle_stage.h"
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include <stdio.h>
#include <string.h>

void FontDrawString(f32 x, f32 y, const char* msg);

void BattleAudience_Case_GreatVictory(void);
void BattleAudience_Case_FastVictory(f32 rate);
void mapGrpFlagOn(const char* name, u32 flags);

typedef struct SeqEndObj {
    Vec pos;                    // 0x0
    Vec scale;                  // 0xC
    Vec rot;                    // 0x18
    u16 value;                  // 0x24
    u16 nextValue;              // 0x26
    u8 paramDisp;               // 0x28
    u8 field_0x29[0x30 - 0x29]; // 0x29
    GXColor color;              // 0x30
} SeqEndObj;

typedef struct SeqEndWork {
    s32 state;                     // 0x0
    u8 field_0x4[0xA - 0x4];       // 0x4
    s16 expDisp;                   // 0xA
    u8 field_0xC[0x10 - 0xC];      // 0xC
    s32 selected;                  // 0x10
    u8 field_0x14[0x18 - 0x14];    // 0x14
    s32 objCount;                  // 0x18
    u8 field_0x1C[0x24 - 0x1C];    // 0x1C
    s32 cursor;                    // 0x24
    u8 field_0x28[0x30 - 0x28];    // 0x28
    u32 flags;                     // 0x30
    IconEntry* icons[19];          // 0x34
    s32 alpha[19];                 // 0x80
    s32 counter[19];               // 0xCC
    Vec iconPos[19];               // 0x118
    u8 field_0x1FC[0x200 - 0x1FC]; // 0x1FC
    SeqEndObj objs[3];             // 0x200
    u8 field_0x29C[0x2A0 - 0x29C]; // 0x29C
    s32 whistleTimer;              // 0x2A0
    s32 confettiEvtId;             // 0x2A4
    u8 field_0x2A8[0x2AC - 0x2A8]; // 0x2A8
} SeqEndWork;
void _GetExpIcon_Init(SeqEndWork* work);

typedef struct SeqEndUnitSetup {
    u8* kind;                 // 0x0
    u8 field_0x4[0x30 - 0x4]; // 0x4
} SeqEndUnitSetup;

typedef struct SeqEndGroup {
    s32 count;              // 0x0
    SeqEndUnitSetup* units; // 0x4
} SeqEndGroup;

typedef struct SeqEndSpot {
    u16 flags;               // 0x0
    u8 field_0x2[0x4 - 0x2]; // 0x2
    Vec pos;                 // 0x4
    Vec rot;                 // 0x10
    Vec scale;               // 0x1C
    GXColor color;           // 0x28
} SeqEndSpot;
EffectEntry* effPokopiPchargeN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 scale);

void _GetExpIcon_Main(BattleWork* wp);
void _LvupParamConfirmDisp(CameraId camId, void* param);
void L__LvupParamHelpMsgDisp(CameraId camId, void* param);
void _MarioExpDisp(CameraId camId, void* param);
void _GetExpIcon_Disp(CameraId camId, void* param);
void _lvup_select_object_disp(CameraId camId, void* param);
BattleSpotWork* BatSpotGetPtr(void);


#define SEW(wp) ((SeqEndWork*)(wp)->seqEndWork)

extern s32 _koura_delete_event[];

//.data
extern s32 _confetti_control_event[];
USER_FUNC(_check_guard_koura);
USER_FUNC(_disable_enemy_unit_disp);
USER_FUNC(_get_rank_up_msg);
USER_FUNC(_lvup_ap_recover_full);
USER_FUNC(_lvup_disp_flag_onoff);
USER_FUNC(_lvup_obj_set_color);
USER_FUNC(_lvup_object_decide_bound);
USER_FUNC(_lvup_object_noselect_delete);
USER_FUNC(_lvup_object_select_move);
USER_FUNC(_lvup_select_obj_disp_on);
USER_FUNC(_lvup_select_obj_lvup_param_disp);
USER_FUNC(_lvup_select_object_init);
USER_FUNC(_lvup_spot_move);
USER_FUNC(_lvup_spot_off);
USER_FUNC(_lvup_spot_on);
USER_FUNC(_nozzle_set_offset);
USER_FUNC(_set_confetti_control_evtid);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnnounceMessage);
USER_FUNC(btlevtcmd_BtlStageObjFlagOnOff);
USER_FUNC(btlevtcmd_BtlStageObjGetRotate);
USER_FUNC(btlevtcmd_BtlStageObjSetRotate);
USER_FUNC(btlevtcmd_ClearAllStatus);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitKind);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(btlevtcmd_onoff_battleflag);
USER_FUNC(btlevtcmd_snd_se);
USER_FUNC(evt_audience_sound_cheer);
USER_FUNC(evt_batstage_set_aud_dark);
USER_FUNC(evt_batstage_set_stg_dark);
USER_FUNC(evt_batstage_set_stg_dark_base);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_shake_h);
USER_FUNC(evt_eff);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_entry);
USER_FUNC(evt_fade_set_anim_ofs_pos);
USER_FUNC(evt_fade_set_anim_virtual_pos);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_intpl_get_float);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_intpl_init_float);

__declspec(section ".data") u64 lbl_803ACB10 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_battle_seq_end_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_803ACB20 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_battle_seq_end_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_803ACB30 = 0xBF8000003F800000;

__declspec(section ".data") u64 fd_battle_seq_end_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_803ACB40 = 0x3F800000BF800000;

__declspec(section ".data") u64 fd_battle_seq_end_one_negone_359 = 0x3F800000BF800000;


RankUpData _rank_up_data[] = {
    {1, 0, "msg_menu_mario_name_0", "butai_01"},
    {10, 1, "msg_menu_mario_name_1", "butai_01"},
    {20, 2, "msg_menu_mario_name_2", "butai_02"},
    {30, 3, "msg_menu_mario_name_3", "butai_03"},
    {0xFFFF, 0, NULL, NULL},
};
__declspec(section ".sdata") EVT_BEGIN(_event_MajinaiEnd)
    CALL(btlevtcmd_AnnounceMessage, 0, 0, -36, STRING("btl_msg_mj_last"), 60)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

__declspec(section ".sdata") EVT_BEGIN(_rank_up_event)
    CALL(_get_rank_up_msg, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, 0)
    RETURN
EVT_END()

s32 _curtain_close_event[] = {
    110, 262235, (s32)evt_batstage_set_stg_dark, 80, 30, 0, 262235, (s32)evt_batstage_set_stg_dark_base,
    80, 30, 0, 112, 110, 393307, (s32)evt_fade_entry, 24,
    1000, 0, 0, 0, 196699, (s32)evt_fade_set_anim_ofs_pos, 0, 130,
    262235, (s32)evt_fade_set_anim_virtual_pos, 0, 0, 80, 65627, (s32)evt_fade_end_wait, 112,
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 256, 131097, -30000000, 0, 110,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1, 42, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -3, -300, -29999999,
    -29999998, 120, -1, 0, 112, 196699, (s32)btlevtcmd_GetUnitId, -4,
    -29999997, 131097, -29999997, -1, 110, 196699, (s32)btlevtcmd_GetBodyId, -29999997,
    -29999996, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 42, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -29999997, -330,
    -29999999, -29999998, 120, -1, 0, 112, 33, 33,
    110, 327771, (s32)evt_sub_intpl_init_float, 0, 0, -230040960, 29, 65541,
    30, 196699, (s32)evt_sub_intpl_get_float, -30000000, -250000000, 196699, (s32)_nozzle_set_offset, (s32)"nozzle_l",
    -30000000, 65545, 1, 6, 112, 110, 327771, (s32)evt_sub_intpl_init_float,
    0, 0, -230040960, 29, 65541, 30, 196699, (s32)evt_sub_intpl_get_float,
    -30000000, -250000000, 196699, (s32)_nozzle_set_offset, (s32)"nozzle_c", -30000000, 65545, 1,
    6, 112, 110, 327771, (s32)evt_sub_intpl_init_float, 0, 0, -230040960,
    29, 65541, 30, 196699, (s32)evt_sub_intpl_get_float, -30000000, -250000000, 196699,
    (s32)_nozzle_set_offset, (s32)"nozzle_r", -30000000, 65545, 1, 6, 112, 196699,
    (s32)btlevtcmd_onoff_battleflag, 0, 256, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 65546, 1500, 110, 65541, 6,
    983131, (s32)evt_eff, (s32)"", (s32)"confetti", 13, 0, 300, 95,
    180, 0, 0, 0, 0, 0, 0, 0,
    65545, 20, 6, 112, 131165, (s32)_confetti_control_event, -30000000, 131163,
    (s32)_set_confetti_control_evtid, -30000000, 983131, (s32)evt_eff, (s32)"", (s32)"levelup", 0, 0,
    50, 100, 60, 0, 0, 0, 0, 0,
    0, 0, 65545, 48, 65627, (s32)_lvup_ap_recover_full, 65546, 1000,
    65647, -29999985, 65545, 2, 131163, (s32)_lvup_spot_on, 0, 131163,
    (s32)_lvup_spot_move, 0, 112, 65627, (s32)_disable_enemy_unit_disp, 110, 196699, (s32)btlevtcmd_GetUnitId,
    -4, -29999997, 131097, -29999997, -1, 327771, (s32)btlevtcmd_SetPos, -29999997,
    -230, 0, 90, 131163, (s32)btlevtcmd_ClearAllStatus, -29999997, 196699, (s32)btlevtcmd_GetBodyId,
    -29999997, -29999996, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 40, 131122,
    -30000000, -155, 131122, -29999999, 0, 131122, -29999998, 90,
    131122, -29999994, 28, 196699, (s32)btlevtcmd_GetUnitKind, -29999997, -29999995, 65570,
    -29999995, 65579, 224, 65579, 225, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -29999997,
    (s32)"SFX_PARTY_BATTLE_SUBMOVE1L", (s32)"SFX_PARTY_BATTLE_SUBMOVE1R", 6, 12, 16, 0, 0, 524379,
    (s32)btlevtcmd_MovePosition, -29999997, -30000000, -29999999, -29999998, -29999994, -2, 1,
    46, 65572, 226, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -29999997, (s32)"SFX_PARTY_BATTLE_SUBMOVE1L", (s32)"SFX_PARTY_BATTLE_SUBMOVE1R",
    0, 6, 6, 0, 0, 524379, (s32)btlevtcmd_MovePosition, -29999997,
    -30000000, -29999999, -29999998, -29999994, -2, 1, 65572, 227,
    589915, (s32)btlevtcmd_SetMoveSoundDataWork, -29999997, (s32)"SFX_PARTY_BATTLE_SUBHANG1", (s32)"SFX_PARTY_BATTLE_SUBHANG1", 6, 12, 16,
    0, 0, 524379, (s32)btlevtcmd_MovePosition, -29999997, -30000000, -29999999, -29999998,
    -29999994, -2, 1, 65572, 228, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -29999997,
    (s32)"SFX_PARTY_BATTLE_SUBHANG1", (s32)"SFX_PARTY_BATTLE_SUBHANG1", 0, 15, 13, 0, 0, 524379,
    (s32)btlevtcmd_MovePosition, -29999997, -30000000, -29999999, -29999998, -29999994, -2, 1,
    65572, 229, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -29999997, (s32)"SFX_PARTY_BATTLE_SUBMOVE1L", (s32)"SFX_PARTY_BATTLE_SUBMOVE1R", 0,
    18, 18, 0, 0, 524379, (s32)btlevtcmd_MovePosition, -29999997, -30000000,
    -29999999, -29999998, -29999994, -2, 1, 65572, 230, 589915,
    (s32)btlevtcmd_SetMoveSoundDataWork, -29999997, (s32)"SFX_PARTY_BATTLE_SUBMOVE1L", (s32)"SFX_PARTY_BATTLE_SUBMOVE1R", 0, 15, 13, 0,
    0, 524379, (s32)btlevtcmd_MovePosition, -29999997, -30000000, -29999999, -29999998, -29999994,
    -2, 1, 49, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, -29999996, 43,
    33, 112, 327771, (s32)btlevtcmd_SetPos, -3, -200, 0, 90,
    131163, (s32)btlevtcmd_ClearAllStatus, -3, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1, 40,
    524379, (s32)btlevtcmd_MovePosition, -3, 0, 0, 90, 75, -1,
    0, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_PAUSE2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_V_2", 196699, (s32)evt_audience_sound_cheer, 180,
    40, 65546, 1000, 65627, (s32)_lvup_select_object_init, 110, 131163, (s32)_lvup_spot_off,
    30, 112, 110, 262235, (s32)evt_batstage_set_stg_dark, 0, 30, 0,
    262235, (s32)evt_batstage_set_stg_dark_base, 0, 30, 0, 262235, (s32)btlevtcmd_BtlStageObjFlagOnOff, (s32)"spotlight",
    1, 0, 393307, (s32)_lvup_obj_set_color, 0, 100, 128, 128,
    255, 393307, (s32)_lvup_obj_set_color, 1, 100, 128, 128, 255,
    393307, (s32)_lvup_obj_set_color, 2, 100, 128, 128, 255, 262235,
    (s32)evt_batstage_set_aud_dark, 0, 60, 0, 393307, (s32)evt_fade_entry, 25, 1000,
    0, 0, 0, 196699, (s32)evt_fade_set_anim_ofs_pos, 0, 130, 262235,
    (s32)evt_fade_set_anim_virtual_pos, 0, 0, 80, 65627, (s32)evt_fade_end_wait, 112, 65546,
    1000, 65647, -30000000, 393307, (s32)_lvup_obj_set_color, 1, 255, 255,
    255, 255, 196699, (s32)_lvup_disp_flag_onoff, 1, 32, 65627, (s32)_lvup_select_obj_disp_on,
    112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 65627, (s32)_lvup_select_obj_lvup_param_disp, 2, 1,
};

EVT_BEGIN(_confetti_control_event)
    SET_VALUE(LW(0), 1)
    SET_VALUE(LW(5), 5)
    LOOP(LW(5))
        SUBTRACT(LW(0), 1)
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(0), 20)
            CALL(evt_eff, STRING(""), STRING("confetti"), 3, 0, 300, 5, 180, 0, 0, 0, 0, 0, 0, 0)
        END_IF
        WAIT_FRAMES(1)
        SET_VALUE(LW(5), 5)
    END_LOOP
    RETURN
EVT_END()

s32 _jump_event[] = {
    110, 65627, (s32)_lvup_object_noselect_delete, 112, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_BTL_LVUP_BLOCK_MOVE1", 0,
    125, 0, 0, 65627, (s32)_lvup_object_select_move, 327771, (s32)btlevtcmd_GetPos, -3,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePoseType, -3, 1, 44,
    107, 65545, 10, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_BTL_LVUP_BLOCK_HIT1", 0, 125,
    0, 0, 393307, (s32)evt_btl_camera_shake_h, 0, 6, 0, 20,
    13, 65627, (s32)_lvup_object_decide_bound, 109, 196699, (s32)btlevtcmd_SetFallAccel, -3, -229999591,
    458843, (s32)btlevtcmd_JumpPosition, -3, -30000000, -29999999, -29999998, 30, -1,
    393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_VOICE_MARIO_PAUSE2", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -3, 1, (s32)"M_V_2", 196699, (s32)evt_audience_sound_cheer, 180, 40,
    2, 1,
};

EVT_BEGIN(_move_to_heart_event)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_LVUP_CURSOR1"), 0, 125, 0, 0)
    CALL(_lvup_obj_set_color, 0, 100, 128, 128, 255)
    CALL(_lvup_obj_set_color, 1, 100, 128, 128, 255)
    CALL(_lvup_obj_set_color, 2, 100, 128, 128, 255)
    CALL(_lvup_disp_flag_onoff, 0, 32)
    CALL(evt_sub_intpl_init, 5, 0, -30, 10)
    LOOP(11)
        CALL(evt_sub_intpl_get_value)
        CALL(btlevtcmd_BtlStageObjSetRotate, STRING("spotlight"), 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_BtlStageObjSetRotate, STRING("spotlight"), 0, 0, -30)
    CALL(_lvup_obj_set_color, 0, 255, 255, 255, 255)
    CALL(_lvup_disp_flag_onoff, 1, 32)
    RETURN
EVT_END()

s32 _move_to_flower_event[] = {
    393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_BTL_LVUP_CURSOR1", 0, 125, 0, 0, 393307,
    (s32)_lvup_obj_set_color, 0, 100, 128, 128, 255, 393307, (s32)_lvup_obj_set_color,
    1, 100, 128, 128, 255, 393307, (s32)_lvup_obj_set_color, 2,
    100, 128, 128, 255, 196699, (s32)_lvup_disp_flag_onoff, 0, 32,
    327771, (s32)btlevtcmd_BtlStageObjGetRotate, (s32)"spotlight", -250000000, -250000000, -29999995, 327771, (s32)evt_sub_intpl_init,
    5, -29999995, 0, 10, 65541, 11, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_BtlStageObjSetRotate, (s32)"spotlight", 0, 0, -30000000, 65545, 1,
    6, 327771, (s32)btlevtcmd_BtlStageObjSetRotate, (s32)"spotlight", 0, 0, 0, 393307,
    (s32)_lvup_obj_set_color, 1, 255, 255, 255, 255, 196699, (s32)_lvup_disp_flag_onoff,
    1, 32, 2, 1,
};

EVT_BEGIN(_move_to_badge_point_event)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_LVUP_CURSOR1"), 0, 125, 0, 0)
    CALL(_lvup_obj_set_color, 0, 100, 128, 128, 255)
    CALL(_lvup_obj_set_color, 1, 100, 128, 128, 255)
    CALL(_lvup_obj_set_color, 2, 100, 128, 128, 255)
    CALL(_lvup_disp_flag_onoff, 0, 32)
    CALL(evt_sub_intpl_init, 5, 0, 30, 10)
    LOOP(11)
        CALL(evt_sub_intpl_get_value)
        CALL(btlevtcmd_BtlStageObjSetRotate, STRING("spotlight"), 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_BtlStageObjSetRotate, STRING("spotlight"), 0, 0, 30)
    CALL(_lvup_obj_set_color, 2, 255, 255, 255, 255)
    CALL(_lvup_disp_flag_onoff, 1, 32)
    RETURN
EVT_END()

EVT_BEGIN(_koura_delete_event)
    CALL(_check_guard_koura, -3, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 62)
    END_IF
    RETURN
EVT_END()



#pragma dont_inline on
RankUpData* _get_rank_data(s32 level) {
    RankUpData* rank;

    for (rank = _rank_up_data; level != rank->startLevel; rank++) {
        if (!rank->rankUpMessage) {
            return NULL;
        }
    }
    return rank;
}
#pragma dont_inline reset

const char* BattleGetRankNameLabel(s32 level) {
    RankUpData* found = NULL;
    RankUpData* rank = _rank_up_data;

    while (level >= rank->startLevel) {
        if (rank->startLevel < 0) {
            break;
        }
        found = rank;
        rank++;
    }
    if (!found) {
        return NULL;
    }
    return found->rankUpName;
}


void _ExecAllUnitBattleEndEvent(void);
void _check_audience_battle_end_exec(void);
void _BattleMarioKouraDelete(void);
void _audience_Whistle_control(void);
void btlseqEnd_DispInit(BattleWork* wp);
void btlseqEnd_DispMain(CameraId camId, void* param);

void btlseqEnd(BattleWork* wp) {
    SeqEndWork* work = *(SeqEndWork**)((u8*)wp + 0xF28);
    FieldBattleInfo* info = *(FieldBattleInfo**)((u8*)wp + 0x2738);
    PouchData* pouch = pouchGetPtr();
    s32 marioBelong;
    s32 enemyBelong;
    u32 flags;

    _audience_Whistle_control();
    switch (BattleGetSeq(wp, (BattleSequence)7)) {
    case 0x7000000:
        btlsubResetMoveColorLvAll(wp);
        { BattleUnit* mu = BattleGetMarioPtr(wp);
        marioBelong = *(s8*)((u8*)mu + 0xC);
        enemyBelong = BtlUnit_GetEnemyBelong(mu); }
        flags = *(u32*)((u8*)wp + 0xEF4);
        if (flags & 0x40) {
            BattleInformationSetResult(info, 4);
        } else if (flags & 0x20) {
            BattleInformationSetResult(info, 5);
        } else if (((s32*)((u8*)wp + marioBelong * 8))[3]) {
            BattleInformationSetResult(info, 3);
        } else if (((s32*)((u8*)wp + enemyBelong * 8))[3]) {
            BattleInformationSetResult(info, 1);
        } else if (flags & 0x10) {
            BattleInformationSetResult(info, 4);
        }
        switch (BattleInformationGetResult(info)) {
        case 1:
            if (*(u32*)((u8*)fbatGetPointer() + 0x3C)) {
                BattleSetSeq(wp, (BattleSequence)7, 0x7000003);
                return;
            }
            _check_audience_battle_end_exec();
            BattleSetSeq(wp, (BattleSequence)7, 0x7000005);
            _BattleMarioKouraDelete();
            break;
        case 3:
            BattleSetSeq(wp, (BattleSequence)7, 0x7000001);
            break;
        default:
            _ExecAllUnitBattleEndEvent();
            BattleSetSeq(wp, (BattleSequence)7, 0x700001D);
            BattleAudienceSoundSetVolAll(0, 30);
            break;
        }
        work = BattleAlloc(sizeof(SeqEndWork));
        /* TODO: block at 0x1c0-0x1fc: memset/init, btlseqEnd_DispInit, irand */
        btlseqEnd_DispInit(wp);
        irand(0);
        break;
    case 0x7000001: /* TODO: 0x2cc-0x334 ExecAllUnitBattleEndEvent, camera, fadeEntry, psndBGMOff */
        _ExecAllUnitBattleEndEvent();
        BattleSetSeq(wp, (BattleSequence)7, 0x7000002);
        break;
    case 0x7000002: /* TODO: 0x334-0x380 fadeIsFinish -> seqSetSeq / 0x700001F */
        break;
    case 0x7000003: /* TODO: 0x1fc-0x234 fbatGetPointer, evtEntry */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000004);
        break;
    case 0x7000004: /* TODO: 0x234-0x2cc evtCheckID, wait, set seq 1/5, alloc */
        break;
    case 0x7000005: /* TODO: 0x380-0x49c status cleanup, reserve item, evtEntry */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000006);
        break;
    case 0x7000006: /* TODO: 0x49c-0x54c clap, drop material, majinai */
        break;
    case 0x7000007: /* TODO: 0x54c-0x574 */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000008);
        break;
    case 0x7000008: /* TODO: 0x574-0x6d4 fog stop, stock exp, _GetExpIcon_Init, camera, sounds */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000009);
        break;
    case 0x7000009: /* TODO: 0x6d4-0x704 */
        BattleSetSeq(wp, (BattleSequence)7, 0x700000A);
        break;
    case 0x700000A: /* TODO: 0x704-0x818 unit evts, effPointGetEntry */
        break;
    case 0x700000B: /* TODO: 0x818-0x914 exp counting, pad, psndSFXOn */
        BattleSetSeq(wp, (BattleSequence)7, 0x700000C);
        break;
    case 0x700000C: /* TODO: 0x914-0x97c _GetExpIcon_End, effSoftDelete */
        BattleSetSeq(wp, (BattleSequence)7, 0x700000D);
        break;
    case 0x700000D: /* TODO: 0x97c-0x9b4 */
        BattleSetSeq(wp, (BattleSequence)7, 0x700000E);
        break;
    case 0x700000E: /* TODO: 0x9b4-0xa1c evtEntry */
        break;
    case 0x700000F: /* TODO: 0xa1c-0xa68 */
        break;
    case 0x7000010: /* TODO: 0xa68-0xad8 WinSetActive, HideReel */
        break;
    case 0x7000011: /* TODO: 0xad8-0xb58 evtEntry, status window, BGM */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000012);
        break;
    case 0x7000012: /* TODO: 0xb58-0xd18 level-up select pad handling */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000014);
        break;
    case 0x7000013: /* TODO: 0xd18-0xe14 confirm pad handling */
        break;
    case 0x7000014: /* TODO: 0xe14-0xe44 */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000015);
        break;
    case 0x7000015: /* TODO: 0xe44-0x105c apply level up params, recovery effects */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000016);
        break;
    case 0x7000016: /* TODO: 0x105c-0x10d8 */
        BattleSetSeq(wp, (BattleSequence)7, 0x7000017);
        break;
    case 0x7000017: /* TODO: 0x10d8-0x113c rank up */
        break;
    case 0x7000018: /* TODO: 0x113c-0x1164 */
        BattleSetSeq(wp, (BattleSequence)7, 0x700001C);
        break;
    case 0x7000019: /* TODO: 0x1164-0x1248 victory anim */
        BattleSetSeq(wp, (BattleSequence)7, 0x700001A);
        break;
    case 0x700001A: /* TODO: 0x1248-0x12c4 */
        BattleSetSeq(wp, (BattleSequence)7, 0x700001B);
        break;
    case 0x700001B:
        BattleSetSeq(wp, (BattleSequence)7, 0x700001C);
        break;
    case 0x700001C: /* TODO: 0x12dc-0x131c */
        BattleSetSeq(wp, (BattleSequence)7, 0x700001D);
        break;
    case 0x700001D: /* TODO: 0x131c-0x1350 fadeEntry */
        BattleSetSeq(wp, (BattleSequence)7, 0x700001E);
        break;
    case 0x700001E: /* TODO: 0x1350-0x1374 */
        if (fadeIsFinish()) {
            BattleSetSeq(wp, (BattleSequence)7, 0x700001F);
        }
        break;
    case 0x700001F: /* TODO: 0x1374-0x1444 party trans, free, mario party */
        BattleFree(work);
        break;
    }
    btlseqEnd_DispMain((CameraId)8, wp);
}

void _ExecAllUnitBattleEndEvent(void) {
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    void* data;

    EventEntry* evt;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit) {
            data = BtlUnit_GetData(unit, 0x3F);
            if (data) {
                evt = evtEntry(data, 10, 0);
                evt->unitId = unit->unitId;
            }
        }
    }
}

void btlseqEnd_DispInit(BattleWork* wp) {
    SEW(wp)->flags = 0;
}

void btlseqEnd_DispMain(CameraId camId, void* param) {
    BattleWork* wp = (BattleWork*)param;
    SeqEndWork* work = SEW(wp);


    if (work) {
        if (work->flags & 2) {
            _GetExpIcon_Main(wp);
            dispEntry(camId, 900.0f, 1, _GetExpIcon_Disp, wp);
        }
        if (work->flags & 4) {
            dispEntry(camId, 900.0f, 1, _MarioExpDisp, wp);
        }
        if (work->flags & 8) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            dispEntry(CAMERA_3D, dispCalcZ(&pos), 2, _lvup_select_object_disp, wp);
        }
        if (work->flags & 0x10) {
            dispEntry(camId, 900.0f, 1, _LvupParamConfirmDisp, wp);
        }
        if (work->flags & 0x20) {
            dispEntry(camId, 900.0f, 1, L__LvupParamHelpMsgDisp, wp);
        }
    }
}

void _MarioExpDisp(CameraId camId, void* param) {
    SeqEndWork* work = SEW((BattleWork*)param);
    char buf[0x10];
    Vec pos;
    f32 width;

    pouchGetPtr();
    pos.x = 200.0f;
    pos.y = -200.0f;
    pos.z = 0.0f;
    if (work) {
        sprintf(buf, "%2d", work->expDisp);
        width = (f32)strlen(buf) * 12.5f + 65.0f;
        windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, 180.0f, -160.0f, width, 32.0f, 10.0f);

        iconDispGx(&pos, 0x10, 0x18C, 1.0f);
        FontDrawStart();
        FontDrawString(225.0f, -163.0f, buf);
    }
}

void _LvupParamConfirmDisp(CameraId camId, void* param) {
    Vec pos;
    char buf[0x14];
    f32 w;
    u32 len;
    f32 zero = 0.0f;
    f32 w2;
    SeqEndWork* work = SEW((BattleWork*)param);
    pouchGetPtr();
    sprintf(buf, msgSearch("btl_msg_lvup_ok"));
    len = strlen(buf);
    w2 = 12.5f * len;
    w = 6.25f * len;
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -30.0f - w, 30.0f, w2 + 65.0f, 32.0f, 10.0f);
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -70.0f, -10.0f, 130.0f, 60.0f, 10.0f);
    FontDrawStart();
    FontDrawString(zero - w, 27.0f, buf);
    FontDrawString(-20.0f, -13.0f, msgSearch("btl_msg_lvup_yes"));
    FontDrawString(-20.0f, -38.0f, msgSearch("btl_msg_lvup_no"));
    pos.x = -40.0f;
    pos.y = -50 - work->cursor * 25;
    pos.z = 0.0f;
    iconDispGx(&pos, 0x10, 0x18C, 1.0f);
}

void L__LvupParamHelpMsgDisp(CameraId camId, void* param) {
    SeqEndWork* work = SEW((BattleWork*)param);
    PouchData* pouch;
    const char* msg;
    u16 lines;
    s32 width;

    f32 y;
    f32 zero = 0.0f;

    pouch = pouchGetPtr();
    switch (work->selected) {
        case 0:
            msg = msgSearch("help_btl_levelup_hp");
            if (pouch->baseMaxHP >= 200) {
                msg = msgSearch("helperr_btl_levelup_hp");
            }
            break;
        case 1:
            msg = msgSearch("help_btl_levelup_fp");
            if (pouch->baseMaxFP >= 200) {
                msg = msgSearch("helperr_btl_levelup_fp");
            }
            break;
        case 2:
            msg = msgSearch("help_btl_levelup_bp");
            if (pouch->maximumBP >= 99) {
                msg = msgSearch("helperr_btl_levelup_bp");
            }
            break;
    }
    width = FontGetMessageWidthLine(msg, &lines);
    lines++;
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, (zero - width / 2) - 20.0f, -145.0f + (lines - 1) * 29, width + 40, lines * 29 + 1, 10.0f);
    FontDrawStart_alpha(0xFF);
    y = -148.0f;
    FontDrawMessage(zero - width / 2, (s32)y + (lines - 1) * 29, msg);
}

void _GetExpIcon_Init(SeqEndWork* work) {
    s32 i;
    char name[16];

    for (i = 0; i < 10; i++) {
        sprintf(name, "_Bgsp%d", i);
        iconEntry2D(name, 0x18C);
        work->icons[i] = iconNameToPtr(name);
        iconSetScale(name, 0.9f);
        iconFlagOn(name, 2);
        work->counter[i] = 0;
        work->iconPos[i].x = 24.0f - 18.0f * (work->expDisp / 10) + 36.0f * i;
        work->iconPos[i].y = 25.0f;
        work->iconPos[i].z = 0.0f;
        iconSetPos(name, work->iconPos[i].x, work->iconPos[i].y, work->iconPos[i].z);
    }
    for (i = 10; i < 19; i++) {
        sprintf(name, "_Bgsp%d", i);
        iconEntry2D(name, 0x18C);
        work->icons[i] = iconNameToPtr(name);
        iconSetScale(name, 0.45f);
        iconFlagOn(name, 2);
        work->counter[i] = 0;
        work->iconPos[i].x = 86.9f - 16.2f * (i - 9);
        work->iconPos[i].y = 0.0f;
        work->iconPos[i].z = 0.0f;
        iconSetPos(name, work->iconPos[i].x, work->iconPos[i].y, work->iconPos[i].z);
    }
    work->flags |= 2;
}

void _GetExpIcon_Main(BattleWork* wp) {
    s32 new_var[2];
    SeqEndWork* work = SEW(wp);
    s32 exp = work->expDisp;
    s32 i;
    f32 ofs;

    new_var[1] = exp / 10;
    for (i = 0; i < new_var[1]; i++) {
        iconFlagOff(work->icons[i]->name, 2);
        if (work->alpha[i] <= 0) {
            work->alpha[i] = 0x40;
        } else {
            work->alpha[i] += 0x40;
            if (work->alpha[i] > 0xFF) {
                work->alpha[i] = 0xFF;
            }
        }
        if (work->counter[i] < 16) {
            work->counter[i]++;
        }
        work->iconPos[i].x = 24.0f - 18.0f * (work->expDisp / 10) + 36.0f * i;
    }
    for (; i < 10; i++) {
        iconFlagOn(work->icons[i]->name, 2);
        work->alpha[i] = 0;
        work->counter[i] = 0;
    }
    new_var[0] = exp % 10;
    for (i = 10; i - 10 < new_var[0]; i++) {
        iconFlagOff(work->icons[i]->name, 2);
        if (work->alpha[i] <= 0) {
            work->alpha[i] = 0x40;
        } else {
            work->alpha[i] += 0x40;
            if (work->alpha[i] > 0xFF) {
                work->alpha[i] = 0xFF;
            }
        }
    }
    for (; i < 19; i++) {
        iconFlagOn(work->icons[i]->name, 2);
        work->alpha[i] = 0;
    }
    ofs = 0.0f;
    for (i = 0; i < 19; i++) {
        iconSetAlpha(work->icons[i]->name, work->alpha[i]);
        iconSetPos(work->icons[i]->name, work->iconPos[i].x, work->iconPos[i].y + ofs, work->iconPos[i].z);
    }
}

void _GetExpIcon_Disp(CameraId camId, void* param) {
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0x80}, -76.9f, 21.0f, 165.8f, 24.2f, 10.0f);
}

void _GetExpIcon_End(SeqEndWork* work) {
    s32 i;

    work->flags &= ~2;
    for (i = 0; i < 19; i++) {
        iconDelete(work->icons[i]->name);
    }
}

USER_FUNC(_nozzle_set_offset) {
    s32* args = event->args;
    const char* name;
    f32 ofs;
    BattleStageObject* obj;

    name = (const char*)evtGetValue(event, args[0]);
    ofs = evtGetFloat(event, args[1]);
    obj = BattleSearchObjectPtr(name);
    if (obj) {
        obj->field_0x10.y = ofs;
    }
    return 2;
}

USER_FUNC(_lvup_ap_recover_full) {
    BattleAudience* aud = BattleAudienceBaseGetPtr();

    aud->excited = TRUE;
    pouchSetAP(pouchGetMaxAP());
    return 2;
}

USER_FUNC(_disable_enemy_unit_disp) {
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    BattleUnit* unit;
    BattleStageObject* obj;
    void* data;
    EventEntry* evt;
    s32 kind;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (!unit) continue;
        if (unit->flags & 0x80000000) continue;
        kind = unit->currentKind;
        if (kind == 0xDC) continue;
        if (kind == 0xDE) continue;
        if (kind >= 0xE0 && kind < 0xE7 && unit->mAlliance == 0 && kind != 0xE5) continue;
        data = BtlUnit_GetData(unit, 0x42);
        if (data) {
            evt = evtEntry(data, 10, 0);
            evt->unitId = unit->unitId;
        } else if (unit->currentKind != 0xE5) {
            unit->mAttributeFlags |= 0x21000000;
        }
    }
    obj = BattleSearchObjectPtr("if_body");
    if (obj) {
        *((u8*)wp + 0x180DC) |= 0x20;
        obj->mFlags |= 1;
        mapGrpFlagOn("if_body", 1);
        mapGrpFlagOn("if_wire", 1);
    }
    return 2;
}

USER_FUNC(_set_confetti_control_evtid) {
    s32* args = event->args;
    SeqEndWork* work = SEW(_battleWorkPointer);
    if (!_battleWorkPointer->seqEndWork && !_battleWorkPointer->seqEndWork && !_battleWorkPointer->seqEndWork) {
    }
    work->confettiEvtId = evtGetValue(event, args[0]);

    return 2;
}

USER_FUNC(_lvup_select_obj_disp_on) {
    SeqEndWork* work = SEW(_battleWorkPointer);

    work->flags |= 8;
    return 2;
}

USER_FUNC(_lvup_select_obj_lvup_param_disp) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    s32 i;

    for (i = 0; i < 3; i++) {
        work->objs[i].paramDisp = 1;
    }
    return 2;
}

USER_FUNC(_lvup_obj_set_color) {
    s32* args = event->args;
    SeqEndWork* work = SEW(_battleWorkPointer);
    SeqEndObj* obj;

    obj = &work->objs[evtGetValue(event, args[0])];
    obj->color.r = evtGetValue(event, args[1]);
    obj->color.g = evtGetValue(event, args[2]);
    obj->color.b = evtGetValue(event, args[3]);
    obj->color.a = evtGetValue(event, args[4]);
    return 2;
}

USER_FUNC(_lvup_disp_flag_onoff) {
    s32* args = event->args;
    SeqEndWork* work = SEW(_battleWorkPointer);
    s32 on = evtGetValue(event, args[0]);
    u32 mask = args[1];

    if (on) {
        work->flags |= mask;
    } else {
        work->flags &= ~mask;
    }
    return 2;
}

USER_FUNC(_lvup_spot_on) {
    BattleSpotWork* spot = BatSpotGetPtr();
    s32* args = event->args;
    s32 n;
    SeqEndSpot* e;

    spot->skipRender = 1;
    n = evtGetValue(event, args[0]);
    e = (SeqEndSpot*)spot->entries + n;
    switch (n) {
    case 0: {
        Vec v = {0.0f, 25.0f, -50.0f};
        v.x = 25.0f * n + -50.0f;
        e->pos = v;
        break;
    }
    case 1: {
        Vec v = {0.0f, -10.0f, -50.0f};
        v.x = 25.0f * n + -50.0f;
        e->pos = v;
        break;
    }
    case 2: {
        Vec v = {0.0f, 25.0f, -50.0f};
        v.x = 25.0f * n + -50.0f;
        e->pos = v;
        break;
    }
    case 3:
        if (1) {
            Vec v = {0.0f, -10.0f, -50.0f};
            v.x = 25.0f * n + -50.0f;
            e->pos = v;
            break;
        }
    case 4: {
        Vec v = {0.0f, 25.0f, -50.0f};
        v.x = 25.0f * n + -50.0f;
        e->pos = v;
        break;
    }
    }
    e->rot = (Vec){0.0f, 0.0f, 0.0f};
    e->scale = (Vec){15.0f, 15.0f, 150.0f};
    e->color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    e->flags |= 2;
    return 2;
}

f32 sinfd(f32);

USER_FUNC(_lvup_spot_move) {
    BattleSpotWork* spot = BatSpotGetPtr();
    s32 n = evtGetValue(event, event->args[0]);
    SeqEndSpot* e = (SeqEndSpot*)spot->entries + n;
    f32 s;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        event->userdata[2] = e->pos.x;
        event->userdata[3] = e->pos.y;
        event->userdata[4] = 0;
    }
    event->userdata[0]++;
    switch (event->userdata[1]) {
    case 0:
        event->userdata[0] = 1;
        event->userdata[1]++;
    case 1:
        switch (n) {
        case 0:
            e->pos.x = 0.5f * *(f32*)((u8*)BattleGetMarioPtr(_battleWorkPointer) + 0x3C);
            e->pos.y = -20.0f;
            break;
        case 1:
            s = sinfd(reviseAngle(1.1f * (3.0f * event->userdata[0])));
            e->pos.x = 50.0f * s + event->userdata[2];
            s = sinfd(reviseAngle(1.1f * (2.5f * event->userdata[0]) + 90.0f));
            e->pos.y = -(25.0f * s - (event->userdata[3] + 25));
            break;
        case 2:
            s = sinfd(reviseAngle(1.1f * (2.5f * event->userdata[0]) + 180.0f));
            e->pos.x = 65.0f * s + event->userdata[2];
            s = sinfd(reviseAngle(1.1f * (7.5f * event->userdata[0]) + 90.0f));
            e->pos.y = 25.0f * s + (event->userdata[3] - 25);
            break;
        case 3:
            s = sinfd(reviseAngle(1.1f * (4.0f * event->userdata[0])));
            e->pos.x = -(50.0f * s - event->userdata[2]);
            s = sinfd(reviseAngle(1.1f * (2.5f * event->userdata[0]) + 90.0f));
            e->pos.y = -(25.0f * s - (event->userdata[3] + 25));
            break;
        case 4:
            s = sinfd(reviseAngle(1.1f * (3.0f * event->userdata[0]) + 270.0f));
            e->pos.x = -(50.0f * s - (event->userdata[2] - 50));
            s = sinfd(reviseAngle(1.1f * (4.5f * event->userdata[0]) + 90.0f));
            e->pos.y = 25.0f * s + (event->userdata[3] - 25);
            break;
        }
        break;
    case 2:
        event->userdata[4] = 20;
        event->userdata[2] = e->pos.x;
        event->userdata[3] = e->pos.y;
        event->userdata[1]++;
    case 3:
        event->userdata[4]--;
        e->pos.x = intplGetValue(2, event->userdata[4], 21, 0.0f, event->userdata[2]);
        e->pos.y = intplGetValue(2, event->userdata[4], 21, -25.0f, event->userdata[3]);
        {
            GXColor c = {0xFF, 0xFF, 0xFF, 0xFF};
            c.a = intplGetValue(0, event->userdata[4], 21, 255.0f, 128.0f);
            e->color = c;
        }
        if (event->userdata[4] <= 0) {
            event->userdata[1]++;
        }
        break;
    }
    return event->userdata[1] < 4 ? 0 : 2;
}

USER_FUNC(_lvup_spot_off) {
    BattleSpotWork* spot = BatSpotGetPtr();
    s32* args = event->args;
    SeqEndSpot* e;
    s32 i;

    if (isFirstCall) {
        event->userdata[0] = evtGetValue(event, args[0]);
        event->userdata[1] = event->userdata[0];
        event->userdata[2] = ((SeqEndSpot*)spot->entries)->color.a;
    }
    event->userdata[1]--;
    for (i = 0; i < 5; i++) {
        GXColor c = {0xFF, 0xFF, 0xFF, 0x00};
        e = (SeqEndSpot*)spot->entries + i;
        c.a = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, event->userdata[2], 2, event->userdata[1], event->userdata[0]);

        e->color = c;
        if (e->color.a == 0) {
            e->flags &= ~2;
        }
    }
    return event->userdata[1] > 0 ? 0 : 2;
}

USER_FUNC(_lvup_object_noselect_delete) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    s32 sel = work->selected;
    s32 i;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[2] = 30;
        for (i = 0; i < work->objCount; i++) {
            if (i != sel) {
                work->objs[i].paramDisp = 3;
            }
        }
    }
    event->userdata[0]++;
    if (event->userdata[0] < event->userdata[2]) {
        for (i = 0; i < work->objCount; i++) {
            if (i != sel) {
                work->objs[i].color.a = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(255.0f, 0.0f, 5, event->userdata[0], event->userdata[2]);

            }
        }
        return 0;
    }
    for (i = 0; i < work->objCount; i++) {
        if (i != sel) {
            work->objs[i].color.a = 0;
        }
    }
    return 2;
}


USER_FUNC(_lvup_object_select_move) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    s32 sel = work->selected;
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    SeqEndObj* obj = &work->objs[sel];

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 60;
        event->userdata[2] = obj->pos.x;
        event->userdata[3] = obj->pos.z;
        event->userdata[4] = mario->mPosition.x;
        event->userdata[5] = mario->mPosition.z;
    }
    event->userdata[0]++;
    if (event->userdata[0] < event->userdata[1]) {
        obj->pos.x = intplGetValue(5, event->userdata[0], event->userdata[1], event->userdata[2], event->userdata[4]);
        obj->pos.z = intplGetValue(5, event->userdata[0], event->userdata[1], event->userdata[3], event->userdata[5]);
        { f32 ang = intplGetValue(5, event->userdata[0], event->userdata[1], 0.0f, 2160.0f); obj->rot.y = reviseAngle(ang); }
        return 0;
    }
    obj->pos.x = event->userdata[4];
    obj->pos.z = event->userdata[5];
    return 2;
}

USER_FUNC(_lvup_object_decide_bound) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    SeqEndObj* obj = &work->objs[work->selected];
    s32 half;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = obj->pos.y;
        event->userdata[2] = 16;
        event->userdata[3] = 30;
        obj->paramDisp = 2;
    }
    event->userdata[0]++;
    if (event->userdata[0] < event->userdata[2]) {
        half = event->userdata[2] / 2;
        if (event->userdata[0] < half) {
            obj->pos.y = event->userdata[1] + intplGetValue(5, event->userdata[0], half, 0.0f, event->userdata[3]);
        } else {
            obj->pos.y = event->userdata[1] + intplGetValue(5, event->userdata[0] - half, half, event->userdata[3], 0.0f);
        }
        return 0;
    }
    obj->pos.y = event->userdata[1];
    obj->paramDisp = 4;
    effPokopiPchargeN64Entry(3, 120, obj->pos.x, obj->pos.y, obj->pos.z, 1.5f);
    return 2;
}

USER_FUNC(_lvup_select_object_init) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    PouchData* pouch = pouchGetPtr();

    work->objs[0].pos = (Vec){-80.0f, 105.0f, 0.0f};
    work->objs[0].scale = (Vec){0.5f, 0.5f, 1.0f};
    work->objs[1].pos = (Vec){0.0f, 105.0f, 0.0f};
    work->objs[1].scale = (Vec){0.5f, 0.5f, 1.0f};
    work->objs[2].pos = (Vec){80.0f, 105.0f, 0.0f};
    work->objs[2].scale = (Vec){0.5f, 0.5f, 1.0f};

    work->objs[0].paramDisp = 0;
    work->objs[0].color = (GXColor){0xC8, 0xFF, 0xFF, 0xFF};
    work->objs[0].value = pouch->baseMaxHP;
    work->objs[0].rot = (Vec){0.0f, 0.0f, 0.0f};
    if (work->objs[0].value >= 200) {
        work->objs[0].nextValue = work->objs[0].value;
    } else {
        work->objs[0].nextValue = work->objs[0].value + 5;
    }

    work->objs[1].paramDisp = 0;
    work->objs[1].color = (GXColor){0xC8, 0xFF, 0xFF, 0xFF};
    work->objs[1].value = pouch->baseMaxFP;
    work->objs[1].rot = (Vec){0.0f, 0.0f, 0.0f};
    if (work->objs[1].value >= 200) {
        work->objs[1].nextValue = work->objs[1].value;
    } else {
        work->objs[1].nextValue = work->objs[1].value + 5;
    }

    work->objs[2].paramDisp = 0;
    work->objs[2].color = (GXColor){0xC8, 0xFF, 0xFF, 0xFF};
    work->objs[2].value = pouch->maximumBP;
    work->objs[2].rot = (Vec){0.0f, 0.0f, 0.0f};
    if (work->objs[2].value >= 99) {
        work->objs[2].nextValue = work->objs[2].value;
    } else {
        work->objs[2].nextValue = work->objs[2].value + 3;
    }

    work->flags |= 8;
    return 2;
}

#pragma dont_inline on
s32 _keta_get(s32 n) {

    s32 k = 0;

    if (n < 0) {
        n *= -1;
    }
    if (n == 0) {
        return 1;
    }
    while (n > 0) {
        n /= 10;
        k++;
    }
    return k;
}

void btlDispTexPlane(u32 id, GXColor color, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY);
void btlDispTexPlane2(Mtx mtx, u32 id, GXColor color);
#define LVOBJ_TIMER(o) ((o)->field_0x29[0])
#define LVOBJ_DISP(o) (*(s32*)&(o)->field_0x29[3])
#define LVOBJ_PLANE(o, n)                                                              \
    if (LVOBJ_DISP(o)) {                                                               \
        PSMTXIdentity(m);                                                              \
        PSMTXTrans(trans, (o)->pos.x, (o)->pos.y, (o)->pos.z);                         \
        PSMTXScale(scale, (o)->scale.x, (o)->scale.y, (o)->scale.z);                   \
        PSMTXRotRad(rotX, 'x', 0.017453292f * (o)->rot.x);                             \
        PSMTXRotRad(rotY, 'y', 0.017453292f * (o)->rot.y);                             \
        PSMTXRotRad(rotZ, 'z', 0.017453292f * (o)->rot.z);                             \
        PSMTXConcat(rotZ, scale, m);                                                   \
        PSMTXConcat(rotZ, m, m);                                                       \
        PSMTXConcat(rotX, m, m);                                                       \
        PSMTXConcat(rotY, m, m);                                                       \
        PSMTXConcat(trans, m, m);                                                      \
        ((void (*)(Mtx, u32, GXColor, s32))btlDispTexPlane2)(m, 0x24 + n, (o)->color, 0); \
        ((void (*)(u32, GXColor, s32, f32, f32, f32, f32, f32))btlDispTexPlane)(        \
            0x27 + n, (o)->color, 0, (o)->pos.x - 16.0f, 20.0f + (o)->pos.y,             \
            2.0f + (o)->pos.z, (o)->scale.x, (o)->scale.y);                              \
    }

void _lvup_select_object_disp(CameraId camId, void* param) {
    SeqEndWork* work = SEW(_battleWorkPointer);
    SeqEndObj* obj;
    s32 i;
    Vec pos3;
    Vec pos;
    Vec pos2;
    Mtx m, trans, scale, rotX, rotY, rotZ;
    Mtx m1, m2, m3, ms;

    for (i = 0; i < 3; i++) {
        obj = &work->objs[i];
        switch (obj->paramDisp) {
        case 4:
            obj->paramDisp = 5;
            LVOBJ_TIMER(obj) = 1;
        case 5:
            LVOBJ_TIMER(obj)--;
            if (LVOBJ_TIMER(obj) == 0) {
                LVOBJ_TIMER(obj) = 8;
                if (LVOBJ_DISP(obj)) {
                    LVOBJ_DISP(obj) = 0;
                } else {
                    LVOBJ_DISP(obj) = 1;
                }
            }
            break;
        default:
            LVOBJ_DISP(obj) = 1;
            break;
        }
    }
    LVOBJ_PLANE(&work->objs[0], 0)
    LVOBJ_PLANE(&work->objs[1], 1)
    LVOBJ_PLANE(&work->objs[2], 2)

    for (i = 0; i < 3; i++) {
        obj = &work->objs[i];
        if (LVOBJ_DISP(obj)) {
            if (obj->paramDisp == 1) {
                if (obj->value != obj->nextValue) {
                    pos = obj->pos;
                    pos.x = pos.x - 8.0f - 6.0f;
                    pos.y = pos.y - (96.0f * obj->scale.y + 2.0f);
                    pos.z += 5.0f;
                    PSMTXScale(ms, 0.8f, 0.8f, 1.0f);
                    PSMTXTrans(m1, pos.x, pos.y, pos.z);
                    PSMTXConcat(m1, ms, m1);
                    iconNumberDispGx3D(m1, obj->value, 0, obj->color);

                    pos2 = obj->pos;
                    pos2.x = 1.2f * (_keta_get(obj->nextValue) * 8 + 6) + pos2.x;
                    pos2.y = pos2.y - (96.0f * obj->scale.y + 3.0f);
                    pos2.z += 5.0f;
                    PSMTXTrans(m2, pos2.x, pos2.y, pos2.z);
                    PSMTXScale(ms, 1.2f, 1.2f, 1.0f);
                    PSMTXConcat(m2, ms, m2);
                    iconNumberDispGx3D(m2, obj->nextValue, 0, obj->color);

                    pos3 = obj->pos;
                    pos3.y = pos3.y - 96.0f * obj->scale.y;
                    pos3.z += 5.0f;
                    PSMTXTrans(m3, pos3.x, pos3.y, pos3.z);
                    PSMTXScale(ms, -0.6f, 0.6f, 1.0f);
                    PSMTXConcat(m3, ms, m3);
                    iconDispGxCol(m3, 0, 0x163, obj->color);
                }
            } else if (obj->paramDisp == 2 || obj->paramDisp == 5) {
                pos2 = obj->pos;
                pos2.x = pos2.x + ((_keta_get(obj->nextValue) * 8) / 2 - 4.0f);
                pos2.y = pos2.y - (96.0f * obj->scale.y + 2.0f);
                pos2.z += 5.0f;
                PSMTXTrans(m2, pos2.x, pos2.y, pos2.z);
                iconNumberDispGx3D(m2, obj->nextValue, 0, obj->color);
            }
        }
    }
}
#pragma dont_inline reset
#pragma auto_inline reset
#pragma dont_inline on
void _check_audience_battle_end_exec(void) {
    BattleWork* wp = _battleWorkPointer;
    SeqEndGroup* group = *(SeqEndGroup**)((u8*)wp->fbatInfo->setup + 0x18);
    s32 level = group->units[0].kind[0xE];
    s32 turn;
    s32 sum;
    s32 i;
    s32 lv;
    s32 limit;
    SeqEndUnitSetup* unit;

    if (level > pouchGetPtr()->level + 1) {
        BattleAudience_Case_GreatVictory();
    }
    turn = wp->turnCount;
    lv = pouchGetPtr()->level + 1;
    sum = 0;
    unit = group->units;
    for (i = 0; i < group->count; i++, unit++) {
        sum += unit->kind[0xE];
    }
    limit = sum * 2 / lv / 3;
    if (turn < limit) {
        BattleAudience_Case_FastVictory(limit - turn);
    }
}

void _audience_Whistle_control(void) {
    SeqEndWork* work = SEW(_battleWorkPointer);

    if (work) {
        switch (work->state) {
        case 0x7000007:
        case 0x7000008:
        case 0x7000009:
        case 0x700000A:
        case 0x700000B:
        case 0x700000C:
        case 0x700000D:
        case 0x700000E:
        case 0x700000F:
        case 0x7000010:
        case 0x7000011:
        case 0x7000012:
        case 0x7000013:
        case 0x7000014:
        case 0x7000015:
        case 0x7000016:
        case 0x7000017:
        case 0x7000018:
        case 0x7000019:
        case 0x700001A:
        case 0x700001B:
            if (--work->whistleTimer < 0) {
                work->whistleTimer = irand(120) + 60;
                BattleAudienceSoundWhistle();
            }
            break;
        }
    }
}

void _BattleMarioKouraDelete(void) {
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    EventEntry* evt = evtEntry(_koura_delete_event, 10, 0);

    evt->unitId = mario->unitId;
}
#pragma dont_inline reset

USER_FUNC(_check_guard_koura) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnit* koura;
    s32 out;
    s32 id;

    id = evtGetValue(event, args[0]);
    out = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (!(unit->mAttributeFlags & 0x20)) {
        evtSetValue(event, out, -1);
        return 2;
    }
    koura = BtlUnit_GetGuardKouraPtr(unit);
    if (!koura) {
        evtSetValue(event, out, -1);
        return 2;
    }
    evtSetValue(event, out, koura->unitId);
    return 2;
}

USER_FUNC(_get_rank_up_msg) {
    s32 index = event->args[0];

    evtSetValue(event, index, (s32)_get_rank_data(pouchGetPtr()->level)->rankUpMessage);
    return 2;
}
