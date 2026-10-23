#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/effdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"

#define BTL_WORK_1C70(wp) (*(s32*)((u8*)(wp) + 0x1C70))
#define BTL_WORK_1C74(wp) (*(u8*)((u8*)(wp) + 0x1C74))

typedef struct WhirlwindN64Work {
    u8 field_0x0[0x8 - 0x0]; // 0x0
    Vec position;            // 0x8
} WhirlwindN64Work;

EffectEntry* effWhirlwindN64Entry(BOOL flip, s32 type, f32 scale, s32 lifetime);

USER_FUNC(_binta_effect);
USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeCmpPoseType);
USER_FUNC(btlevtcmd_AnimeSetMotionSpeed);
USER_FUNC(btlevtcmd_CheckDamagePattern);
USER_FUNC(btlevtcmd_CheckDataOfDataTable);
USER_FUNC(btlevtcmd_CheckDefinePosetype);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EllipseMovePosition);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetGuardKouraId);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetPartnerId);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnToken);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(_check_through_pos);
USER_FUNC(_set_hp_gauge_fade_flag);
USER_FUNC(_add_star_point_disp_offset);
USER_FUNC(_check_at_dm_event_wait);
USER_FUNC(_disable_restore_command_cursor);
extern s32 btlevtcmd_AnimeFlagOnOff[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_CheckAttribute[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ClearAllStatus[];
extern s32 btlevtcmd_ConsumeItemReserve[];
extern s32 btlevtcmd_DispItemIcon[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetBackItem[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetDamage[];
extern s32 btlevtcmd_GetDamageCode[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetFriendBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetScale[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_GetUnitKind[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffUnitFlag[];
extern s32 btlevtcmd_OnOffStatus[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetDispOffset[];
extern s32 btlevtcmd_SetHp[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetRotateOffsetFromCenterOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxon_3d[];
extern s32 evt_sub_intpl_get_float[];
extern s32 evt_sub_intpl_init_float[];
extern s32 marioWeapon_KaitenHammerInvolved[];
extern s32 marioWeapon_UltraHammerInvolved[];
extern s32 partyWeapon_YoshiNomikomi_Involved[];

s32 subsetevt_dead[608];
s32 subsetevt_dead_core[193];
s32 subsetevt_dead_core_nospin_norotate[125];
s32 btldefaultevt_avoid_guard[92];
s32 subsetevt_damage[979];
s32 subsetevt_counter_damage[174];
s32 btldefaultevt_ChangePosition[186];
s32 subsetevt_happy_heart[53];
s32 subsetevt_happy_flower[53];
s32 subsetevt_terror[51];
s32 subsetevt_blow_damage[69];
s32 subsetevt_blow_dead[76];
s32 subsetevt_shot_damage[31];
s32 subsetevt_shot_damage_kaiten[288];
s32 subsetevt_shot_damage_ultra[429];
s32 subsetevt_swallow_failed_damage[55];
s32 subsetevt_swallow_spew_damage[55];
s32 subsetevt_swallow_shot_damage[342];
s32 subset_ultra_hammer_acrobat_damage_event[63];
s32 subsetevt_confuse_flustered[43];
s32 subsetevt_binta_damage_left[48];
s32 subsetevt_binta_damage_right[48];
s32 subsetevt_binta_damage_left_last[69];
s32 subsetevt_binta_damage_right_last[69];
s32 subsetevt_status_recovery[48];
s32 unk_evt_803510ec[57];
s32 subsetevt_nodamage_motion[6];
s32 subsetevt_regeneration[4];
s32 subset_attack_ready_jump_event[2];

s32 subsetevt_dead[] = {
    65627, (s32)_disable_restore_command_cursor, 196699, (s32)btlevtcmd_GetUnitKind, -29999990, -30000000, 65570, -30000000,
    65572, 222, 65540, 0, 131119, 224, 230, 65540,
    0, 42, 65540, 1, 49, 65539, 0, 262235,
    (s32)btlevtcmd_CheckAttribute, -29999990, 4, -30000000, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 42, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -29999998,
    -29999997, -29999996, 196699, (s32)btlevtcmd_SetMoveSpeed, -29999990, -229995904, 655451, (s32)btlevtcmd_DivePosition,
    -29999990, -29999998, -29999997, -29999996, 0, 0, 0, 0,
    -1, 32, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 40, 327771,
    (s32)btlevtcmd_GetHomePos, -29999990, -29999998, -29999997, -29999996, 196699, (s32)btlevtcmd_SetMoveSpeed, -29999990,
    -229995904, 524379, (s32)btlevtcmd_MovePosition, -29999990, -29999998, -29999997, -29999996, 0,
    -1, 0, 33, 131163, (s32)btlevtcmd_ResetFaceDirection, -29999990, 65539, 1,
    393307, (s32)btlevtcmd_OnOffStatus, -29999990, 27, 1, 1, 1, 196699,
    (s32)btlevtcmd_GetUnitKind, -29999990, -30000000, 65570, -30000000, 65572, 222, 131163,
    (s32)btlevtcmd_ClearAllStatus, -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 2048, -29999999, 131097,
    -29999999, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 51, 32, 196699,
    (s32)btlevtcmd_RunDataEventChild, -29999990, 49, 33, 131119, 224, 230, 262235,
    (s32)btlevtcmd_CheckDamageCode, -29999990, 2048, -29999999, 131097, -29999999, 0, 131163,
    (s32)btlevtcmd_ClearAllStatus, -29999990, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 51, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 51, 32, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 27, 110, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999990,
    -29999989, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_PARTY_BATTLE_DIE1", -250000000, 0, -250000000,
    112, 65545, 60, 131163, (s32)btlevtcmd_ClearAllStatus, -29999990, 196699, (s32)btlevtcmd_ConsumeItemReserve,
    -29999990, 151, 110, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 131125, -29999999, 40, 393307, (s32)btlevtcmd_DispItemIcon, -30000000, -29999999,
    -29999998, 151, 90, 112, 65545, 90, 262235, (s32)btlevtcmd_CheckDataOfDataTable,
    -29999990, -30000000, 67, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild,
    -29999990, 67, 33, 393307, (s32)btlevtcmd_OnOffStatus, -29999990, 27, 0,
    0, 0, 196699, (s32)btlevtcmd_SetHp, -29999990, 0, 262235, (s32)btlevtcmd_RecoverHp,
    -29999990, -29999989, 10, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 131125, -29999999, 30, 983131, (s32)evt_eff, 0, (s32)"recovery",
    0, -30000000, -29999999, -29999998, 10, 0, 0, 0,
    0, 0, 0, 0, 65546, 2000, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -29999990, -29999989, 42, 327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -230000000,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 33, 32, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000,
    49, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 49,
    32, 33, 196699, (s32)btlevtcmd_KillUnit, -29999990, 1, 196699, (s32)btlevtcmd_GetBodyId,
    -2, -29999989, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 27, 110,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999990, -29999989, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_PARTY_BATTLE_DIE1",
    -250000000, 0, -250000000, 112, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_GetPartnerId, -29999990, -29999996, 327771, (s32)btlevtcmd_GetHomePos,
    -29999996, -29999994, -29999993, -29999992, 131098, -30000000, 0, 131127,
    -30000000, -1, 33, 131098, -29999994, 0, 131127, -29999994,
    -1, 33, 131098, -30000000, -29999994, 65546, 500, 131163,
    (s32)_check_at_dm_event_wait, -3, 196699, (s32)btlevtcmd_GetHp, -3, -30000000, 131099, -30000000,
    0, 65630, (s32)btldefaultevt_ChangePosition, 33, 33, 33, 42, 262235,
    (s32)btlevtcmd_CheckDamageCode, -29999990, 2048, -29999999, 131097, -29999999, 0, 262235,
    (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 51, 131097, -30000000, 0, 131163,
    (s32)btlevtcmd_ClearAllStatus, -29999990, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 51, 32, 196699,
    (s32)btlevtcmd_OnUnitFlag, -29999990, 134217728, 131122, -30000000, 48, 65539, 5,
    65545, 1, 327771, (s32)btlevtcmd_AddRotate, -29999990, 0, -15, 0,
    131126, -30000000, 1, 131099, -30000000, 0, 65540, 5,
    33, 327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0, 0, 327771,
    (s32)btlevtcmd_SetRotateOffset, -29999990, 0, 0, 0, 131122, -30000000, 30,
    65539, 6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -29999990, 3,
    0, 0, 131126, -30000000, 1, 131099, -30000000, 0,
    65540, 6, 33, 131163, (s32)btlevtcmd_ClearAllStatus, -29999990, 196699, (s32)btlevtcmd_ConsumeItemReserve,
    -29999990, 151, 110, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 131125, -29999999, 40, 393307, (s32)btlevtcmd_DispItemIcon, -30000000, -29999999,
    -29999998, 151, 120, 112, 65545, 90, 131122, -30000000,
    30, 65539, 7, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -29999990,
    -3, 0, 0, 131126, -30000000, 1, 131099, -30000000,
    0, 65540, 7, 33, 393307, (s32)btlevtcmd_OnOffStatus, -29999990, 27,
    0, 0, 0, 196699, (s32)btlevtcmd_SetHp, -29999990, 0, 262235,
    (s32)btlevtcmd_RecoverHp, -29999990, -29999989, 10, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000,
    -29999999, -29999998, 131125, -29999999, 30, 983131, (s32)evt_eff, 0,
    (s32)"recovery", 0, -30000000, -29999999, -29999998, 10, 0, 0,
    0, 0, 0, 0, 0, 65546, 2000, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 42, 327771, (s32)btlevtcmd_JumpSetting, -29999990, 0,
    -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1,
    196699, (s32)btlevtcmd_OffUnitFlag, -29999990, 134217728, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 33,
    32, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 49, 131097, -30000000,
    0, 131163, (s32)btlevtcmd_ClearAllStatus, -29999990, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 49,
    32, 65630, (s32)subsetevt_dead_core, 33, 33, 49, 2, 1,
};

s32 subsetevt_dead_core[] = {
    262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 50, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 50, 33, 131122, -30000000, 48,
    196699, (s32)btlevtcmd_OnUnitFlag, -29999990, 134217728, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_1",
    -250000000, 0, -250000000, 65539, 10, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -29999990, 0, -15, 0, 131126, -30000000, 1,
    131099, -30000000, 0, 65540, 10, 33, 327771, (s32)btlevtcmd_SetRotate,
    -29999990, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff, 0, (s32)"kemuri_test",
    4, -30000000, -29999999, -29999998, -229999181, 0, 0, 0,
    0, 0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000,
    131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163,
    (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999, -29999998,
    131125, -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset,
    -29999990, -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point",
    0, -29999997, -29999999, -29999998, -30000000, 0, 0, 0,
    0, 0, 0, 0, 131101, -30000000, 1, 65541,
    -30000000, 6, 33, 327771, (s32)btlevtcmd_SetRotateOffset, -29999990, 0, 0,
    0, 131122, -30000000, 30, 65539, 20, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -29999990, 3, 0, 0, 131126, -30000000,
    1, 131099, -30000000, 0, 65540, 20, 33, 131163,
    (s32)btlevtcmd_GetBackItem, -29999990, 131163, (s32)btlevtcmd_ClearAllStatus, -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990,
    1024, -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_KillUnit, -29999990,
    0, 32, 196699, (s32)btlevtcmd_KillUnit, -29999990, 2, 33, 2,
    1,
};

s32 subsetevt_dead_core_nospin_norotate[] = {
    262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 50, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 50, 33, 393307, (s32)btlevtcmd_snd_se, -29999990,
    (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000,
    -29999999, -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff, 0,
    (s32)"kemuri_test", 4, -30000000, -29999999, -29999998, -229999181, 0, 0,
    0, 0, 0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -29999990,
    -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000,
    131163, (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999,
    -29999998, 131125, -29999998, 10, 131125, -29999999, 30, 327771,
    (s32)_add_star_point_disp_offset, -29999990, -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"",
    (s32)"star_point", 0, -29999997, -29999999, -29999998, -30000000, 0, 0,
    0, 0, 0, 0, 0, 131101, -30000000, 1,
    65541, -30000000, 6, 33, 65545, 30, 131163, (s32)btlevtcmd_GetBackItem,
    -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 1024, -30000000, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_KillUnit, -29999990, 1, 32, 196699, (s32)btlevtcmd_KillUnit,
    -29999990, 2, 33, 2, 1,
};

EVT_BEGIN(btldefaultevt_avoid_guard)
    CALL(btlevtcmd_AnimeCmpPoseType, LW(10), LW(11), 42, 40, LW(2))
    IF_INT_EQUAL(LW(2), 0)
        CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(2.0f))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 42)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 20)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 20, -1, 0)
    CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 46)
    CALL(btlevtcmd_WaitAttackEnd)
    IF_INT_EQUAL(LW(14), LW(15))
        CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(2.0f))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 42)
    CALL(btlevtcmd_GetHomePos, -2, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_MovePosition, -2, LW(2), LW(3), LW(4), 20, -1, 0)
    CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(1.0f))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 subsetevt_damage[] = {
    262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 2097152, -30000000, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 13, 2, 33, 262235, (s32)btlevtcmd_CheckDamageCode,
    -29999990, 4194304, -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild,
    -29999990, 14, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 9,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000,
    17, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 17,
    2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 8, -30000000,
    131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 16,
    131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 16, 2,
    33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 14, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 18, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 18, 2, 33,
    33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 16, -30000000, 131097, -30000000,
    0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 18, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 18, 2, 33, 33,
    262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 15, -30000000, 131097, -30000000, 0,
    262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 19, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 19, 2, 33, 33, 262235,
    (s32)btlevtcmd_CheckDamagePattern, -29999990, 17, -30000000, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 19, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_RunDataEventChild, -29999990, 19, 2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern,
    -29999990, 21, -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable,
    -29999990, -30000000, 20, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild,
    -29999990, 20, 2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990,
    22, -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990,
    -30000000, 21, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990,
    21, 2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 23,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000,
    22, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 22,
    2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 24, -30000000,
    131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 23,
    131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 23, 2,
    33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 25, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_blow_damage, 327771, (s32)btlevtcmd_SetRotate, -29999990, 0,
    0, 0, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 4,
    -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000,
    55, 131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 55,
    2, 33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 5, -30000000,
    131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 56,
    131097, -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 56, 2,
    33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 6, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 57, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 57, 2, 33,
    33, 262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 9, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 9, 2, 33, 262235,
    (s32)btlevtcmd_CheckDamagePattern, -29999990, 4, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_swallow_failed_damage, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 5, -30000000,
    131097, -30000000, 0, 65630, (s32)subsetevt_swallow_spew_damage, 2, 33, 262235,
    (s32)btlevtcmd_CheckDamagePattern, -29999990, 6, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_swallow_shot_damage, 2, 33, 196699, (s32)btlevtcmd_GetDamage, -29999990, -30000000, 131101,
    -30000000, 1, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 256, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 10, -30000000, 131097,
    -30000000, 0, 65540, 10, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990,
    12, -30000000, 131097, -30000000, 0, 65540, 10, 33,
    262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 11, -30000000, 131097, -30000000, 0,
    65540, 10, 33, 65540, 11, 65539, 10, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 65647, -30000000, 327771, (s32)evt_sub_intpl_init_float,
    5, -229998976, -229999847, 10, 65541, 11, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999990, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -29999990, -30000000, -29999995, -29999998, 65545, 1,
    6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990,
    11, -29999999, 131097, -29999999, 0, 65546, 3000, 32,
    262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 12, -29999999, 131097, -29999999, 0,
    65546, 2500, 32, 65546, 1500, 33, 33, 110,
    196699, (s32)btlevtcmd_GetFriendBelong, -29999990, -30000000, 131096, -30000000, 0, 393307,
    (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_DAMAGE_PRESS1", -250000000, 0, -250000000, 33, 112,
    110, 327771, (s32)evt_sub_intpl_init_float, 5, -229999847, -229998720, 10, 65541,
    10, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -29999990,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -29999990, -30000000, -29999995,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 7, -229998720,
    -229998976, 30, 65541, 30, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -29999990, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -29999990, -30000000, -29999995, -29999998, 65545, 1, 6, 112,
    65545, 60, 2, 65539, 11, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990,
    14, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_shot_damage, 2,
    33, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 16, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_shot_damage, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern,
    -29999990, 21, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_binta_damage_left,
    2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 22, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_binta_damage_right, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern,
    -29999990, 23, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_binta_damage_left_last,
    2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 24, -30000000, 131097,
    -30000000, 0, 65630, (s32)subsetevt_binta_damage_right_last, 2, 33, 262235, (s32)btlevtcmd_CheckDamagePattern,
    -29999990, 13, -30000000, 131097, -30000000, 0, 327771, (s32)btlevtcmd_AnimeFlagOnOff,
    -29999990, -29999989, 32, 1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    -29999986, 65546, 2000, 327771, (s32)btlevtcmd_AnimeFlagOnOff, -29999990, -29999989, 32,
    0, 32, 262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 26, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 65546,
    2000, 131097, -29999985, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989,
    -29999985, 65545, 30, 33, 32, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990,
    -29999989, -29999986, 65546, 1000, 131097, -29999985, -1, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999985, 65545, 30, 33, 33,
    33, 2, 32, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 256, -30000000,
    131097, -30000000, 0, 131163, (s32)_set_hp_gauge_fade_flag, -29999990, 33, 196699,
    (s32)btlevtcmd_GetDamageCode, -29999990, -30000000, 65570, -30000000, 65572, 23, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 65546, 1000, 131097, -29999985,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999985, 65545, 30,
    33, 2, 42, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ATTACK_MISS2", 0, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -2, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -2, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -4, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -2, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -2, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -3, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -2, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, -1, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 327771,
    (s32)btlevtcmd_SetDispOffset, -29999990, 0, 0, 0, 65545, 1, 49,
    33, 2, 1,
};

s32 subsetevt_counter_damage[] = {
    196699, (s32)btlevtcmd_OnUnitFlag, -29999990, 1, 110, 65570, -30000000, 65579,
    43, 65579, 44, 65579, 45, 196699, (s32)btlevtcmd_GetUnitKind, -29999990,
    -29999998, 131096, -29999998, 222, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999998,
    -29999997, -29999996, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_VOICE_MARIO_DAMAGED1", -29999998, -29999997, -29999996,
    0, 33, 46, 49, 112, 65570, -30000000, 65572,
    43, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ATTACK_MISS3", 0, 131122, -29999986, 36,
    65572, 46, 196699, (s32)btlevtcmd_GetUnitKind, -29999990, -29999998, 131096, -29999998,
    222, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_VOICE_MARIO_DAMAGED1", -250000000, 0, -250000000,
    33, 131122, -29999986, 29, 65579, 49, 65579, 50,
    65579, 54, 131122, -29999986, 29, 46, 42, 131122,
    -29999986, 39, 49, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986,
    110, 196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 10, 112, 196699, (s32)btlevtcmd_SetFallAccel,
    -29999990, -229998976, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999998, -29999997, -29999996,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -29999998, 25, 131125, -29999997, 25,
    655451, (s32)btlevtcmd_DivePosition, -29999990, -29999998, -29999997, -29999996, 10, 0,
    0, 0, -1, 65546, 500, 196699, (s32)btlevtcmd_SetFallAccel, -29999990,
    -229998976, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999998, -29999997, -29999996, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -29999998, -29999997, -29999996, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -29999998,
    30, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -29999998, -29999997, -29999996, 20,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -29999998, 15, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -29999998, -29999997, -29999996, 10, -1, 65545, 30,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

EVT_BEGIN(btldefaultevt_ChangePosition)
    CALL(btlevtcmd_GetGuardKouraId, -3, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 60)
        CALL(btlevtcmd_OffPartsAttribute, -3, 1, 16777216)
        CALL(btlevtcmd_SetUnitWork, LW(10), 2, 2)
    END_IF
    CALL(evt_snd_sfxon, STRING("SFX_BTL_POS_CHANGE1"), 0)
    CALL(btlevtcmd_GetPartnerId, -2, LW(3))
    CALL(btlevtcmd_GetBodyId, -2, LW(5))
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(5), 42)
    END_IF
    CALL(btlevtcmd_GetBodyId, LW(3), LW(5))
    CALL(btlevtcmd_CheckStatus, LW(3), 27, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(5), 42)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetHomePos, LW(3), LW(5), LW(6), LW(7))
        CALL(btlevtcmd_GetHomePos, -2, LW(5), LW(8), LW(7))
        CALL(btlevtcmd_EllipseMovePosition, LW(3), LW(5), LW(6), LW(7), 20, 15, 0)
        CALL(btlevtcmd_SetHomePos, LW(3), LW(5), LW(6), LW(7))
    END_INLINE_EVENT
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(4), LW(2))
    CALL(btlevtcmd_EllipseMovePosition, -2, LW(0), LW(1), LW(2), 20, 15, 0)
    CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_GetGuardKouraId, -3, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_SetUnitWork, LW(10), 2, 3)
        LABEL(10)
        CALL(btlevtcmd_GetUnitWork, LW(10), 2, LW(0))
        IF_INT_EQUAL(LW(0), 3)
            WAIT_FRAMES(1)
            GOTO(10)
        END_IF
        CALL(btlevtcmd_GetHp, LW(10), LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 59)
            CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
        END_IF
    END_IF
    CALL(btlevtcmd_SortPhaseMoveTable)
    CALL(btlevtcmd_StartWaitEvent, -3)
    CALL(btlevtcmd_StartWaitEvent, -4)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_happy_heart)
    CALL(btlevtcmd_GetBodyId, -2, LW(5))
    CALL(btlevtcmd_CheckDefinePosetype, -2, LW(5), 62, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, LW(3), 9, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CheckStatus, LW(3), 1, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_CheckStatus, LW(3), 2, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(5), 62)
                END_IF
            END_IF
        END_IF
    END_IF
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_happy_flower)
    CALL(btlevtcmd_GetBodyId, -2, LW(5))
    CALL(btlevtcmd_CheckDefinePosetype, -2, LW(5), 63, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, LW(3), 9, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CheckStatus, LW(3), 1, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_CheckStatus, LW(3), 2, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(5), 63)
                END_IF
            END_IF
        END_IF
    END_IF
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 subsetevt_terror[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 16, -1, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229989760,
    262235, (s32)btlevtcmd_GetStageSize, -30000000, -250000000, -250000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_ESCAPE1", -250000000, 0, -250000000, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 196699, (s32)btlevtcmd_KillUnit, -2,
    0, 2, 1,
};

s32 subsetevt_blow_damage[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999990,
    -30000000, -29999999, -29999998, 2, 1,
};

s32 subsetevt_blow_dead[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 196699, (s32)btlevtcmd_KillUnit,
    -2, 0, 2, 1,
};

EVT_BEGIN(subsetevt_shot_damage)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_OnToken, LW(10), 32)
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 14, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(12), PTR(marioWeapon_KaitenHammerInvolved))
        CALL_CHILD(PTR(subsetevt_shot_damage_kaiten))
        ELSE
        SET_VALUE(LW(12), PTR(marioWeapon_UltraHammerInvolved))
        CALL_CHILD(PTR(subsetevt_shot_damage_ultra))
    END_IF
    RETURN
EVT_END()

s32 subsetevt_shot_damage_kaiten[] = {
    65647, -29999987, 65539, 0, 327771, (s32)btlevtcmd_AddRotate, -29999990, 0,
    30, 0, 65545, 1, 65540, 0, 112, 196699,
    (s32)btlevtcmd_GetFriendBelong, -29999990, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -29999990, -30000000, -29999988,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 1, 131096, -29999997,
    -1, 65540, 50, 33, 196699, (s32)btlevtcmd_GetUnitId, -29999990, -30000000,
    131097, -30000000, -29999997, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540,
    1, 33, 65539, 10, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131096, -29999997, -1, 65540, 50, 33, 327771, (s32)btlevtcmd_JumpSetting,
    -29999990, 0, -229994880, -229999990, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999995,
    -29999994, -29999993, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 131101, -29999995, -30000000, 131122, -29999992, -29999995, 131126,
    -29999992, -30000000, 32, 131122, -29999992, -30000000, 131126, -29999992,
    -29999995, 33, 131128, -29999992, 2, 131125, -29999992, -29999994,
    131098, -29999992, -29999999, 131122, -29999999, -29999992, 33, 458843,
    (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998, 0, -1, 458843,
    (s32)btlevtcmd_PreCheckDamage, -29999990, -29999997, -29999996, -29999988, 256, -29999995, 65570,
    -29999995, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65572, 4, 65572, 1, 458843,
    (s32)btlevtcmd_CheckDamage, -29999990, -29999997, -29999996, -29999988, 256, -29999995, 42,
    49, 65540, 10, 65539, 50, 262235, (s32)btlevtcmd_GetStageSize, -29999995,
    -250000000, -250000000, 131122, -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990,
    -30000000, -29999995, 327771, (s32)btlevtcmd_GetPos, -29999990, -250000000, -29999999, -250000000,
    327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -229994880, -229999990, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -30000000, 40, -29999998, 0, -1, 65545, 30,
    262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 512, -29999994, 131097, -29999994, 0,
    131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos, -29999990, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999990, -30000000, 40, 327771, (s32)btlevtcmd_JumpSetting, -29999990, 0,
    -229992832, -229999898, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998,
    0, -1, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -30000000, -29999999, -29999998,
    524379, (s32)btlevtcmd_MovePosition, -29999990, -30000000, -29999999, -29999998, 16, -1,
    0, 65545, 30, 32, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetPos, -29999990, -30000000, -29999999, -29999998, 33, 65631, -29999987,
    327771, (s32)btlevtcmd_SetRotate, -29999990, 0, 0, 0, 2, 1,
};

s32 subsetevt_shot_damage_ultra[] = {
    65647, -29999987, 131163, (s32)btlevtcmd_SetRotateOffsetFromCenterOffset, -29999990, 196699, (s32)btlevtcmd_GetFaceDirection, -29999990,
    -30000000, 131127, -30000000, 20, 131122, -29999995, 5, 65541,
    -29999995, 327771, (s32)btlevtcmd_AddRotate, -29999990, 0, -30000000, 0, 131122,
    -29999995, 5, 65545, 1, 6, 112, 196699, (s32)btlevtcmd_GetFriendBelong,
    -29999990, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -29999990, -30000000, -29999988, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 1, 131096, -29999997, -1,
    65540, 50, 33, 196699, (s32)btlevtcmd_GetUnitId, -29999990, -30000000, 131097,
    -30000000, -29999997, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 1,
    33, 131122, -29999992, -1, 131122, -29999991, -1, 65539,
    2, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999994, -29999993, 131097, -29999994, -1,
    131122, -29999992, -29999994, 131122, -29999991, -29999993, 65540, 2,
    33, 131096, -29999992, -1, 65540, 50, 33, 65647,
    -29999995, 327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -229994880, -229999591, 393307,
    (s32)btlevtcmd_GetHitPos, -29999992, -29999991, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999992, -30000000, 20, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998, 0, -1,
    112, 196699, (s32)btlevtcmd_GetFriendBelong, -29999990, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -29999990,
    -30000000, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 30,
    131096, -29999997, -1, 65631, -29999995, 65540, 50, 33,
    196699, (s32)btlevtcmd_GetUnitId, -29999990, -30000000, 131097, -30000000, -29999997, 196699,
    (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 30, 33, 327771, (s32)btlevtcmd_GetPos,
    -29999990, -29999999, -250000000, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999990, -29999999,
    20, 65539, 31, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096,
    -29999997, -1, 65631, -29999995, 65540, 50, 33, 65539,
    32, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999998, -250000000, -250000000,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -29999998, 20, 327771, (s32)btlevtcmd_GetPos, -29999990,
    -30000000, -250000000, -250000000, 393307, (s32)_check_through_pos, -29999990, -29999998, -30000000,
    -29999999, -29999998, 131096, -29999998, 0, 131178, -29999995, -29999994,
    131096, -29999994, 1, 131122, -29999999, -30000000, 65545, 1,
    65540, 32, 33, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -29999990, -29999997,
    -29999996, -29999988, 256, -30000000, 65570, -30000000, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65572, 4, 65572, 1, 458843, (s32)btlevtcmd_CheckDamage, -29999990, -29999997,
    -29999996, -29999988, 256, -30000000, 42, 49, 65540, 31,
    65631, -29999995, 65539, 50, 262235, (s32)btlevtcmd_GetStageSize, -29999995, -250000000,
    -250000000, 131122, -30000000, 0, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -30000000,
    -29999995, 327771, (s32)btlevtcmd_GetPos, -29999990, -250000000, -29999999, -250000000, 327771,
    (s32)btlevtcmd_JumpSetting, -29999990, 0, -229994880, -229999898, 458843, (s32)btlevtcmd_JumpPosition, -29999990,
    -30000000, 80, -29999998, 0, -1, 65545, 30, 262235,
    (s32)btlevtcmd_CheckDamagePattern, -29999990, 16, -29999995, 131097, -29999995, 0, 196699,
    (s32)btlevtcmd_OnToken, -29999990, 64, 65539, 55, 262235, (s32)btlevtcmd_CheckToken, -29999990,
    64, -29999995, 131097, -29999995, 0, 65545, 1, 65540,
    55, 33, 33, 131127, -30000000, -1, 327771, (s32)btlevtcmd_SetPos,
    -29999990, -30000000, 80, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -29999990, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -229992832, -229999898,
    458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998, 0, -1,
    262235, (s32)btlevtcmd_CheckDamagePattern, -29999990, 16, -29999995, 131097, -29999995, 0,
    196699, (s32)btlevtcmd_OnToken, -29999990, 128, 65627, (s32)btlevtcmd_WaitAttackEnd, 33, 33,
    327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -230000000, -229999847, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -30000000, -29999999, -29999998, 20, -1, 65545, 30,
    262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 256, -30000000, 131096, -30000000, 0,
    65627, (s32)btlevtcmd_WaitAttackEnd, 33, 65631, -29999987, 327771, (s32)btlevtcmd_SetRotate, -29999990,
    0, 0, 0, 2, 1,
};

EVT_BEGIN(subsetevt_swallow_failed_damage)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.5f))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 30)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 18)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 12, -1)
    WAIT_FRAMES(20)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_swallow_spew_damage)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.5f))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 30)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 18)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 12, -1)
    WAIT_FRAMES(20)
    RETURN
EVT_END()

s32 subsetevt_swallow_shot_damage[] = {
    262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 131122, -29999988, (s32)partyWeapon_YoshiNomikomi_Involved,
    196699, (s32)btlevtcmd_GetFriendBelong, -29999990, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -29999990, -30000000,
    -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 0, 131096,
    -29999997, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 39, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -29999990,
    -229999488, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -30000000, 30, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999,
    -29999998, 20, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -30000000, 18,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -29999990,
    -30000000, -29999999, -29999998, 12, -1, 65545, 20, 65540,
    99, 33, 196699, (s32)btlevtcmd_GetUnitId, -29999990, -30000000, 131097, -30000000,
    -29999997, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 0, 33,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65651, -29999997, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, 39, 327771, (s32)btlevtcmd_GetPos,
    -29999990, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229999488,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -30000000, 30, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998,
    20, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990, -30000000, 18, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000,
    -29999999, -29999998, 12, -1, 65545, 20, 65540, 99,
    33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_JumpSetting, -29999990, 0, -229994880, -229999898, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -30000000, -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage,
    -4, -29999997, -29999996, -29999988, 256, -29999995, 65570, -29999995,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65572, 4, 65572, 1, 458843, (s32)btlevtcmd_CheckDamage,
    -4, -29999997, -29999996, -29999988, -2147483392, -29999995, 65540, 50,
    42, 49, 65539, 20, 65647, -29999995, 131163, (s32)btlevtcmd_JumpContinue,
    -29999990, 112, 65539, 21, 131178, -29999995, -30000000, 131096,
    -30000000, 0, 65540, 25, 33, 327771, (s32)btlevtcmd_GetPos, -29999990,
    -30000000, -29999999, -29999998, 131122, -29999994, -30000000, 131098, -29999994,
    0, 131127, -29999994, -1, 33, 131101, -29999994, 400,
    65631, -29999995, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetPos, -29999990, -30000000, -29999999, -29999998, 65540, 99, 33,
    65545, 1, 65540, 21, 65539, 25, 65540, 99,
    65539, 50, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229999488, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999990, -30000000,
    30, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -29999990, -30000000, -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999990, -30000000, 18, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    458843, (s32)btlevtcmd_JumpPosition, -29999990, -30000000, -29999999, -29999998, 12, -1,
    65545, 20, 65539, 99, 2, 1,
};

EVT_BEGIN(subset_ultra_hammer_acrobat_damage_event)
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 39)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 40)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 24, -1)
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 18)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_OnToken, LW(10), 128)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_confuse_flustered)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetBodyId, -2, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(0), 5)
    WAIT_MS(1500)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    WAIT_MS(1000)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_binta_damage_left)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_GetFaceDirection, LW(10), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), -18)
        ELSE
        SET_VALUE(LW(0), 18)
    END_IF
    LOOP(20)
        CALL(btlevtcmd_AddRotate, LW(10), 0, LW(0), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    WAIT_FRAMES(10)
    RETURN
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_binta_damage_right)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_GetFaceDirection, LW(10), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 18)
        ELSE
        SET_VALUE(LW(0), -18)
    END_IF
    LOOP(20)
        CALL(btlevtcmd_AddRotate, LW(10), 0, LW(0), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    WAIT_FRAMES(10)
    RETURN
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_binta_damage_left_last)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    BEGIN_SIBLING_EVENT_GET_ID(LW(0))
        CALL(btlevtcmd_GetFaceDirection, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(8), -2160)
            ELSE
            SET_VALUE(LW(8), 2160)
        END_IF
        CALL(_binta_effect, LW(10), LW(8))
        SET_VALUE(LW(7), LW(10))
        CALL(evt_sub_intpl_init, 11, 0, LW(8), 90)
        LOOP(90)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, LW(7), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, LW(7), 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(0))
    WAIT_FRAMES(30)
    RETURN
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_binta_damage_right_last)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    BEGIN_SIBLING_EVENT_GET_ID(LW(0))
        CALL(btlevtcmd_GetFaceDirection, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(8), 2160)
            ELSE
            SET_VALUE(LW(8), -2160)
        END_IF
        CALL(_binta_effect, LW(10), LW(8))
        SET_VALUE(LW(7), LW(10))
        CALL(evt_sub_intpl_init, 11, 0, LW(8), 90)
        LOOP(90)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, LW(7), 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, LW(7), 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(0))
    WAIT_FRAMES(30)
    RETURN
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_status_recovery)
    CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(0), 8)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 8)
        RETURN
    END_IF
    CALL(btlevtcmd_StopWaitEvent, -2)
    CALL(btlevtcmd_GetBodyId, -2, LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, LW(0))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(unk_evt_803510ec)
    CALL(btlevtcmd_CheckStatus, LW(3), 27, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(3), 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(3), 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckStatus, LW(3), 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_nodamage_motion)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_ATTACK_MISS2"), 0)
    RETURN
EVT_END()

EVT_BEGIN(subsetevt_regeneration)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

EVT_BEGIN(subset_attack_ready_jump_event)
    RETURN
EVT_END()

USER_FUNC(_disable_restore_command_cursor) {
    BattleWork* wp = _battleWorkPointer;
    BTL_WORK_1C70(wp) = 0;
    BTL_WORK_1C74(wp) = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(_check_at_dm_event_wait) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;

    id = evtGetValue(event, event->args[0]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    if (unit->attackEventId && evtCheckID(unit->attackEventId)) {
        return EVT_RETURN_BLOCK;
    }
    if (unit->damageEventId && evtCheckID(unit->damageEventId)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_add_star_point_disp_offset) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    BattleUnit* unit;
    s32 xi, yi, zi;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    xi = args[1];
    x = evtGetValue(event, xi);
    yi = args[2];
    y = evtGetValue(event, yi);
    zi = args[3];
    z = evtGetValue(event, zi);
    x += unit->mKindParams->starPointDispOffset.x;
    y += unit->mKindParams->starPointDispOffset.y;
    z += unit->mKindParams->starPointDispOffset.z;
    evtSetValue(event, xi, x);
    evtSetValue(event, yi, y);
    evtSetValue(event, zi, z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_set_hp_gauge_fade_flag) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;

    id = evtGetValue(event, event->args[0]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (unit) {
        unit->hpGauge.field_0x2 |= 1;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_check_through_pos) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    s32 pos = evtGetValue(event, *args++);
    s32 a = evtGetValue(event, *args++);
    s32 b = evtGetValue(event, *args++);
    s32 out = *args++;
    BattleUnit* unit;
    s32 min, max;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (a > b) {
        max = a;
        min = b;
    }
    else {
        max = b;
        min = a;
    }
    if (pos >= min && pos <= max) {
        evtSetValue(event, out, TRUE);
    }
    else {
        evtSetValue(event, out, FALSE);
        if (unit->faceDirection >= 0) {
            if (pos > max) {
                evtSetValue(event, out, TRUE);
            }
        }
        else if (pos < min) {
            evtSetValue(event, out, TRUE);
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_binta_effect) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    s32 dir = evtGetValue(event, *args++);
    BattleUnit* unit;
    EffectEntry* eff;
    Vec pos;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    eff = effWhirlwindN64Entry(dir < 0, 0, unit->mSizeMultiplier, 90);
    ((WhirlwindN64Work*)eff->userdata)->position.x = pos.x;
    ((WhirlwindN64Work*)eff->userdata)->position.y = pos.y;
    ((WhirlwindN64Work*)eff->userdata)->position.z = pos.z;
    return EVT_RETURN_DONE;
}
