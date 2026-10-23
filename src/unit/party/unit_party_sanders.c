#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include <string.h>
#include "battle/battle_attack_audience.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"
#include "unit/unit_bomzou.h"

f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);
void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
f32 sinfd(f32 degrees);
f32 cosfd(f32 degrees);
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(_get_bomb_hit_position);
USER_FUNC(_judge_on_stage);
USER_FUNC(_sanders_make_extra_work_area);
USER_FUNC(_shot_move);
USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_AudienceAppeal);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_InviteApInfoReport);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OnOffStatus);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRotateOffset);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StageDispellFog);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_audience_ap_recovery);
USER_FUNC(evt_btl_camera_set_homing_unitparts);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_btl_camera_shake_h);
USER_FUNC(evt_eff64);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(_make_counterset_weapon);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);

__declspec(section ".data") s32 unit_party_sanders_negone_one_a[2];
__declspec(section ".data") s32 sanders_negone_one_374[2];
__declspec(section ".data") s32 unit_party_sanders_one_negone_a[2];
__declspec(section ".data") s32 sanders_one_negone_373[2];
__declspec(section ".data") s32 unit_party_sanders_negone_one_b[2];
__declspec(section ".data") s32 sanders_negone_one_360[2];
__declspec(section ".data") s32 unit_party_sanders_one_negone_b[2];
__declspec(section ".data") s32 sanders_one_negone_359[2];
PoseTableEntry pose_table_sanders_stay[25];
PoseTableEntry pose_table_counter_sanders[20];
static BattleDataEntry data_table[9];
BattleUnitKindPart unitpartsdata_Party_Sanders[1];
BattleUnitKind unitdata_Party_Sanders;
static s32 battle_entry_event[59];
static s32 init_event[63];
static s32 damage_event[16];
static s32 wait_event[26];
s32 partyWeapon_SandersFirstAttack[48];
s32 partyWeapon_SandersNormalAttack[48];
s32 partyWeapon_SandersTimeBombSet[48];
s32 partyWeapon_SandersCounterSet[48];
s32 partyWeapon_SandersSuperBombAttack[48];
s32 partySandersAttack_FirstAttack[321];
s32 partySandersAttack_NormalAttack[970];
#ifdef VERSION_G8ME01
s32 partySandersAttack_SuperBombAttack[1118];
#else
s32 partySandersAttack_SuperBombAttack[1116];
#endif
#ifdef VERSION_G8ME01
s32 partySandersAttack_CounterSet[242];
#else
s32 partySandersAttack_CounterSet[201];
#endif
#ifdef VERSION_G8ME01
s32 partySandersAttack_TimeBombSet[331];
#else
s32 partySandersAttack_TimeBombSet[290];
#endif
s32 _shot_bomb_event[155];
s32 sanders_appeal_event[121];
static s32 attack_audience_event[284];
s32 sanders_battle_end_event[14];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static s32 attack_event[2];
s32 entry_bomzou[12];
static s32 party_win_reaction[9];

__declspec(section ".data") s32 unit_party_sanders_negone_one_a[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 sanders_negone_one_374[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 unit_party_sanders_one_negone_a[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 sanders_one_negone_373[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 unit_party_sanders_negone_one_b[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 sanders_negone_one_360[] = {
    -1082130432, 1065353216,
};

__declspec(section ".data") s32 unit_party_sanders_one_negone_b[] = {
    1065353216, -1082130432,
};

__declspec(section ".data") s32 sanders_one_negone_359[] = {
    1065353216, -1082130432,
};

PoseTableEntry pose_table_sanders_stay[] = {
    {9, "D_4"},
    {2, "D_4"},
    {3, "X_1"},
    {4, "D_2"},
    {5, "X_1"},
    {1, "N_1"},
    {27, "D_3"},
    {28, "S_1"},
    {37, "G_2"},
    {31, "G_1"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {57, "D_2"},
    {56, "D_2"},
    {60, "D_4"},
    {61, "D_2"},
    {65, "T_1"},
    {52, "I_1"},
    {67, "C_1"},
    {66, "O_1"},
    {64, "R_3"},
    {49, "J_1A"},
    {45, "G_1"},
    {69, "S_1"},
};

PoseTableEntry pose_table_counter_sanders[] = {
    {1, "N_2"},
    {27, "D_3"},
    {28, "A_3"},
    {37, "G_2"},
    {31, "G_1"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {57, "D_2"},
    {56, "D_2"},
    {60, "D_4"},
    {61, "D_2"},
    {65, "T_1"},
    {52, "I_1"},
    {67, "C_1"},
    {66, "O_1"},
    {64, "R_3"},
    {49, "J_1A"},
    {45, "G_1"},
    {69, "A_3"},
};

static BattleDataEntry data_table[] = {
    {5, sanders_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {66, sanders_battle_end_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Sanders[] = {
    {1, "btl_un_sanders", "c_bomt_n", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, 0x9, 0, pose_table_sanders_stay},
};

BattleUnitKind unitdata_Party_Sanders = {
    229,
    "btl_un_sanders",
    10,
    5,
    5,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    20,
    33,
    11,
    28,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    10.0f,
    0.0f,
    0.0f,
    10.0f,
    21.45f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_MARIO_DAMAGE_FIRE1",
    "SFX_MARIO_DAMAGE_ICE1",
    "SFX_MARIO_DAMAGE_BIRIBIRI1",
    0x2000000,
    &regist,
    1,
    unitpartsdata_Party_Sanders,
    init_event,
    data_table,
};

static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 250)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 9, 9, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 18, 18)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 9)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, -2, 0, -1)
    CALL(btlevtcmd_SetUnitWork, -2, 1, -1)
    CALL(btlevtcmd_SetUnitWork, -2, 2, -1)
    CALL(_sanders_make_extra_work_area)
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_CheckStatus, -2, 22, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_counter_sanders))
        ELSE
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_sanders_stay))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

s32 partyWeapon_SandersFirstAttack[] = {
#ifdef VERSION_G8ME01
    0, 22544384, 0, 0, 1677721600, 1065353216, 16843058, (s32)weaponGetPowerFromPartyAttackLv,
#else
    0, 22020096, 0, 0, 1677721600, 1065353216, 16843058, (s32)weaponGetPowerFromPartyAttackLv,
#endif
    4, 4, 5, 5, 6, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 50332418, 0, 155783, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partySandersAttack_FirstAttack, 100, 0, 0,
};

s32 partyWeapon_SandersNormalAttack[] = {
#ifdef VERSION_G8ME01
    (s32)"btl_wn_pbm_normal", 22544384, 0, (s32)"msg_pbm_bakuhatsu", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
#else
    (s32)"btl_wn_pbm_normal", 22020096, 0, (s32)"msg_pbm_bakuhatsu", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
#endif
    1, 4, 2, 5, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 50332418, (s32)"msg_ac_bakuhatsu", 221319, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partySandersAttack_NormalAttack, 658020, 168430085, 167772160,
};

s32 partyWeapon_SandersTimeBombSet[] = {
#ifdef VERSION_G8ME01
    (s32)"btl_wn_pbm_lv1", 22609920, 0, (s32)"msg_pbm_jigen_bakudan", 1677918208, 1065353216, 17130546, 0,
#else
    (s32)"btl_wn_pbm_lv1", 22085632, 0, (s32)"msg_pbm_jigen_bakudan", 1677918208, 1065353216, 17130546, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_ac_jigen_bakudan", 131072, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partySandersAttack_TimeBombSet, 0, 0, 0,
};

s32 partyWeapon_SandersCounterSet[] = {
#ifdef VERSION_G8ME01
    (s32)"btl_wn_pbm_lv2", 22675456, 0, (s32)"msg_pbm_counter", 1677983744, 1065353216, 17130546, 0,
#else
    (s32)"btl_wn_pbm_lv2", 22151168, 0, (s32)"msg_pbm_counter", 1677983744, 1065353216, 17130546, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, (s32)"msg_ac_bom_counter", 131336, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
#ifdef VERSION_G8ME01
    0, 1, 0, 0, (s32)partySandersAttack_CounterSet, 329060, 336200965, 84213760,
#else
    0, 1, 0, 0, (s32)partySandersAttack_CounterSet, 329060, 335873285, 84213760,
#endif
};

s32 partyWeapon_SandersSuperBombAttack[] = {
#ifdef VERSION_G8ME01
    (s32)"btl_wn_pbm_lv3", 22740992, 0, (s32)"msg_pbm_sungoi_bakuhatsu", 1678311424, 1065353216, 17130546, (s32)weaponGetACOutputParam,
#else
    (s32)"btl_wn_pbm_lv3", 22216704, 0, (s32)"msg_pbm_sungoi_bakuhatsu", 1678311424, 1065353216, 33907762, (s32)weaponGetACOutputParam,
#endif
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 50332418, (s32)"msg_ac_super_bakuhatsu", 155783, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partySandersAttack_SuperBombAttack, 3289700, 337189130, 168099840,
};

EVT_BEGIN(partySandersAttack_FirstAttack)
    CALL(btlevtcmd_JumpSetting, -2, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    SET_VALUE(LW(12), PTR(partyWeapon_SandersFirstAttack))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, -2, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 250)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, -2, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, -2, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, -2, LW(0), 0, LW(2), 0, -2, 1)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_3"))
    WAIT_FRAMES(60)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
    CALL(btlevtcmd_StageDispellFog)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(12), 131328, LW(5))
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.5f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(8)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 16, -1)
    WAIT_FRAMES(20)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL_CHILD(PTR(btldefaultevt_SuitoruBadgeEffect))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
EVT_BEGIN(partySandersAttack_NormalAttack)
    CALL(btlevtcmd_JumpSetting, -2, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, -2)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, -2, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, -2, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 60)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 45)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 30)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 25)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 20)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 12)
        CASE_DEFAULT
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 6)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 2, LW(0), LW(1), 0, 100, -250000000, -250000000, -250000000)
    CALL(btlevtcmd_AcSetFlag, 15)
    CALL(btlevtcmd_SetupAC, -2, 15, 1, 0)
    WAIT_FRAMES(22)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(0), 5)
        LOOP(LW(0))
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(0), 5)
                ELSE
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(1))
    IF_INT_EQUAL(LW(1), 2)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 20)
        CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 20, -2, 1)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, -2, STRING("SFX_BTL_THUNDERS_DOWN1"), -250000000, 0, -250000000)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 20)
        CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.5f))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 12, -1)
        CALL(btlevtcmd_StopAC)
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), 0)
        WAIT_FRAMES(60)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        GOTO(95)
    END_IF
    CALL(btlevtcmd_CommandPreCheckDamage, -2, LW(3), LW(4), 256, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
        CALL(btlevtcmd_GetStatusMg, -2, LW(5))
        MULTIPLY_FLOAT(LW(5), 35)
        CALL(_get_bomb_hit_position, -2, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(5))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, -2, LW(0), 0, LW(2), 60, -2, 1)
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
    END_IF
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, -2, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, -2, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_MovePosition, -2, LW(0), 0, LW(2), 90, -2, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_3"))
    WAIT_FRAMES(60)
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
        WAIT_MS(1000)
    END_SWITCH
    CALL(btlevtcmd_ResultAC)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
    CALL(btlevtcmd_StageDispellFog)
    IF_INT_NOT_EQUAL(LW(5), 1)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        ELSE
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, -250000000, LW(8), -250000000)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_ACRStart, -2, 0, 15, 15, 15)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.1992188f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.1992188f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        WAIT_FRAMES(40)
        ELSE
        CALL(evt_audience_acrobat_notry)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, -2, STRING("SFX_BTL_THUNDERS_DOWN1"), -250000000, 0, -250000000)
        WAIT_FRAMES(40)
    END_IF
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL_CHILD(PTR(btldefaultevt_SuitoruBadgeEffect))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
s32 partySandersAttack_NormalAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0,
    -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000,
    3, 65570, -30000000, 65576, -3, 131122, -30000000, 120,
    131122, -29999999, 60, 65572, -2, 131122, -30000000, 120,
    131122, -29999999, 45, 65572, -1, 131122, -30000000, 120,
    131122, -29999999, 30, 65572, 0, 131122, -30000000, 120,
    131122, -29999999, 25, 65572, 1, 131122, -30000000, 120,
    131122, -29999999, 20, 65572, 2, 131122, -30000000, 120,
    131122, -29999999, 12, 42, 131122, -30000000, 120, 131122,
    -29999999, 6, 49, 589915, (s32)btlevtcmd_AcSetParamAll, 2, -30000000, -29999999,
    0, 100, -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 15,
    327771, (s32)btlevtcmd_SetupAC, -2, 15, 1, 0, 65545, 22,
    65647, -29999985, 131122, -30000000, 5, 65541, -30000000, 196699,
    (s32)btlevtcmd_AcGetOutputParam, 0, -29999999, 131096, -29999999, 0, 131122, -30000000,
    5, 32, 7, 33, 65545, 1, 6, 112,
    131163, (s32)btlevtcmd_StartAC, 1, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 196699, (s32)btlevtcmd_AcGetOutputParam,
    0, -29999999, 131096, -29999999, 2, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20,
    589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_THUNDERS_ATTACK1", 0, 0, -1, -1,
    0, 0, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    20, -2, 1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"F_1", 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_THUNDERS_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 20, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 65627, (s32)btlevtcmd_StopAC,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, 0,
    65545, 60, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95,
    33, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995,
    131096, -29999995, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_2",
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999995, 131132, -29999995, 35, 458843,
    (s32)_get_bomb_hit_position, -2, -29999997, -29999996, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999995, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_THUNDERS_ATTACK1", 0, 0, -1,
    -1, 0, 0, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 60, -2, 1, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"R_2", 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 131132, -29999994, 20,
    458843, (s32)_get_bomb_hit_position, -2, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000,
    -29999999, -29999998, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_THUNDERS_ATTACK1", 0, 0,
    -1, -1, 0, 0, 131125, -29999998, 5, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 90, -2, 1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 300,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_THUNDERS_ATTACK2", -29999986, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_3", 65545, 60, 65570, -29999995, 65579, 2, 65579,
    3, 65579, 6, 65579, 4, 46, 65572, 1,
    42, 65546, 1000, 49, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)evt_snd_sfxoff,
    -29999986, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_THUNDERS_ATTACK3", 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999994, 131128,
    -29999994, 2, 131125, -29999999, -29999994, 131163, (s32)btlevtcmd_GetResultAC, -29999994,
    131102, -29999994, 2, 983131, (s32)evt_eff64, (s32)"", (s32)"bomb_n64", 1,
    -30000000, -29999999, -29999998, 0, 0, 0, 0, 0,
    0, 0, 0, 32, 983131, (s32)evt_eff64, (s32)"", (s32)"bomb_n64",
    0, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 33, 393307, (s32)evt_btl_camera_shake_h, 0,
    5, 0, 10, 13, 65627, (s32)btlevtcmd_StageDispellFog, 131097, -29999995,
    1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 65540, 90, 33, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102,
    -29999994, 2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328,
    -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 65539, 90, 65627, (s32)btlevtcmd_StopAC,
    65539, 92, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A", 110,
    65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B", 112,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999591, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 65647, -29999985, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 90, -1, 112, 65545, 60, 65631,
    -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -29999995, -29999994, -29999993, 262235,
    (s32)btlevtcmd_GetStageSize, -250000000, -29999992, -250000000, 131125, -29999994, -29999992, 131128,
    -29999994, 2, 327771, (s32)btlevtcmd_SetPos, -2, -29999995, -29999994, -29999993,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 30, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 65647, -29999985,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 16, -1,
    112, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15, 15, 15,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131101,
    -29999994, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"Y_1", 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0,
    0, 0, 65647, -29999985, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976,
    -229999386, 8, 65541, 8, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -30000000, -29999995, -29999998, 65545, 1, 6, 327771,
    (s32)evt_sub_intpl_init_float, 11, -229999386, -229998772, 8, 65541, 8, 196699,
    (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995, -29999998, 65545,
    1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998772, -229998976, 6,
    65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000,
    -29999995, -29999998, 65545, 1, 6, 112, 110, 327771,
    (s32)evt_sub_intpl_init_float, 11, -229998976, -229998464, 8, 65541, 8, 196699,
    (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999, -29999998, 65545,
    1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464, -229999386, 8,
    65541, 8, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995,
    -29999999, -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11,
    -229999386, -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995,
    -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetScale, -2, -29999995, -29999999, -29999998, 65545, 1, 6,
    112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65545, 40, 32, 65627,
    (s32)evt_audience_acrobat_notry, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"F_1", 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_THUNDERS_DOWN1", -250000000, 0, -250000000, 65545, 40, 33,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539, 95, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};
#endif

#ifdef VERSION_G8ME01
EVT_BEGIN(partySandersAttack_SuperBombAttack)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, -2)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, -2)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, -2, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, -2, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 300)
        SET_VALUE(LW(1), 20)
        SET_VALUE(LW(2), 20)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 370)
        SET_VALUE(LW(1), 18)
        SET_VALUE(LW(2), 22)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 255)
        SET_VALUE(LW(1), 17)
        SET_VALUE(LW(2), 23)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 225)
        SET_VALUE(LW(1), 16)
        SET_VALUE(LW(2), 24)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 210)
        SET_VALUE(LW(1), 15)
        SET_VALUE(LW(2), 26)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 180)
        SET_VALUE(LW(1), 14)
        SET_VALUE(LW(2), 28)
        CASE_DEFAULT
        SET_VALUE(LW(0), 150)
        SET_VALUE(LW(1), 13)
        SET_VALUE(LW(2), 28)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 1, LW(0), 178, LW(1), LW(2), 15, 46, -250000000)
    CALL(btlevtcmd_AcSetGaugeParam, 45, 75, 100, 100)
    CALL(btlevtcmd_AcSetFlag, 64)
    CALL(btlevtcmd_SetupAC, -2, 6, 1, 0)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_CommandPreCheckDamage, -2, LW(3), LW(4), 256, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
        CALL(btlevtcmd_GetStatusMg, -2, LW(6))
        MULTIPLY_FLOAT(LW(6), 35)
        CALL(_get_bomb_hit_position, -2, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, -2, LW(0), 0, LW(2), 60, -2, 1)
        CALL(btlevtcmd_SetScale, -2, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
        RETURN
    END_IF
    BEGIN_SIBLING_EVENT
        SUBTRACT(LW(0), 85)
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 150, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 30, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 120, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(40)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SUBTRACT(LW(0), 85)
        WAIT_FRAMES(LW(0))
        CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
        SET_VALUE(LW(0), 0)
        LOOP(80)
            ADD(LW(0), 1)
            IF_INT_GREATER(LW(0), 80)
                SET_VALUE(LW(0), 80)
            END_IF
            SET_VALUE(LW(1), 4096)
            MULTIPLY(LW(1), LW(0))
            DIVIDE(LW(1), 80)
            CALL(evt_snd_sfx_pit, LW(14), LW(1))
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_FRAMES(3)
        CALL(evt_snd_sfxoff, LW(14))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(LW(0))
            CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
            ADD(LW(0), 100)
            MULTIPLY_FLOAT(LW(0), FLOAT(0.009765625f))
            CALL(btlevtcmd_SetScale, -2, LW(0), LW(0), FLOAT(1.0f))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    SET_VALUE(LW(13), LW(0))
    SUBTRACT(LW(13), 85)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, -2, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, -2, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), LW(13), -2, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_3"))
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
        WAIT_MS(1000)
    END_SWITCH
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_SetScale, -2, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK4"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(evt_eff, STRING(""), STRING("sandars"), 3, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(evt_eff, STRING(""), STRING("sandars"), 4, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_StageDispellFog)
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 20, 13)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_CommandPreCheckDamage, -2, LW(3), LW(4), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
        SWITCH(LW(0))
            CASE_LESS_OR_EQUAL(3)
            SET_VALUE(LW(0), -1)
            CASE_LESS_OR_EQUAL(5)
            SET_VALUE(LW(0), 0)
            CASE_LESS_OR_EQUAL(7)
            SET_VALUE(LW(0), 1)
            CASE_DEFAULT
            SET_VALUE(LW(0), 2)
        END_SWITCH
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 131328, LW(5))
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
            ELSE
            CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
            CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
        END_IF
        ELSE
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
        CALL(btlevtcmd_SetScale, -2, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, -250000000, LW(8), -250000000)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_ACRStart, -2, 0, 15, 15, 15)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.1992188f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.1992188f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), -250000000)
                CALL(btlevtcmd_GetScale, -2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, -2, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        WAIT_FRAMES(40)
        ELSE
        CALL(evt_audience_acrobat_notry)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, -2, STRING("SFX_BTL_THUNDERS_DOWN1"), -250000000, 0, -250000000)
        WAIT_FRAMES(40)
    END_IF
    LABEL(95)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL_CHILD(PTR(btldefaultevt_SuitoruBadgeEffect))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
s32 partySandersAttack_SuperBombAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"Y_1", 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000,
    196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126,
    -30000000, 3, 65570, -30000000, 65576, -3, 131122, -30000000,
    300, 131122, -29999999, 20, 131122, -29999998, 20, 65572,
    -2, 131122, -30000000, 370, 131122, -29999999, 18, 131122,
    -29999998, 22, 65572, -1, 131122, -30000000, 255, 131122,
    -29999999, 17, 131122, -29999998, 23, 65572, 0, 131122,
    -30000000, 225, 131122, -29999999, 16, 131122, -29999998, 24,
    65572, 1, 131122, -30000000, 210, 131122, -29999999, 15,
    131122, -29999998, 26, 65572, 2, 131122, -30000000, 180,
    131122, -29999999, 14, 131122, -29999998, 28, 42, 131122,
    -30000000, 150, 131122, -29999999, 13, 131122, -29999998, 28,
    49, 589915, (s32)btlevtcmd_AcSetParamAll, 1, -30000000, 178, -29999999, -29999998,
    15, 46, -250000000, 327771, (s32)btlevtcmd_AcSetGaugeParam, 45, 75, 100,
    100, 131163, (s32)btlevtcmd_AcSetFlag, 64, 327771, (s32)btlevtcmd_SetupAC, -2, 6,
    1, 0, 65545, 22, 131163, (s32)btlevtcmd_StartAC, 1, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 131096, -29999995,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_2", 196699, (s32)btlevtcmd_GetStatusMg,
    -2, -29999994, 131132, -29999994, 35, 458843, (s32)_get_bomb_hit_position, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, -29999994, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 589915,
    (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_THUNDERS_ATTACK1", 0, 0, -1, -1, 0,
    0, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998, 60,
    -2, 1, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 2,
    33, 110, 131126, -30000000, 85, 65545, -30000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"",
    (s32)"sandars", 5, -30000000, -29999999, -29999998, 60, 0, 0,
    0, 0, 0, 0, 0, 65545, 15, 983131,
    (s32)evt_eff, (s32)"", (s32)"sandars", 5, -30000000, -29999999, -29999998, 150,
    0, 0, 0, 0, 0, 0, 0, 65545,
    15, 983131, (s32)evt_eff, (s32)"", (s32)"sandars", 5, -30000000, -29999999,
    -29999998, 30, 0, 0, 0, 0, 0, 0,
    0, 65545, 15, 983131, (s32)evt_eff, (s32)"", (s32)"sandars", 5,
    -30000000, -29999999, -29999998, 120, 0, 0, 0, 0,
    0, 0, 0, 65545, 40, 112, 110, 131126,
    -30000000, 85, 65545, -30000000, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_THUNDERS_ATTACK2", -29999986,
    131122, -30000000, 0, 65541, 80, 131125, -30000000, 1,
    131099, -30000000, 80, 131122, -30000000, 80, 33, 131122,
    -29999999, 4096, 131127, -29999999, -30000000, 131128, -29999999, 80,
    196699, (s32)evt_snd_sfx_pit, -29999986, -29999999, 65545, 1, 6, 65545,
    3, 131163, (s32)evt_snd_sfxoff, -29999986, 112, 110, 65541, -30000000,
    196699, (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 131125, -30000000, 100, 131132,
    -30000000, -229999990, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -30000000, -229998976,
    65545, 1, 6, 112, 131122, -29999987, -30000000, 131126,
    -29999987, 85, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_2", 196699,
    (s32)btlevtcmd_GetStatusMg, -2, -29999994, 131132, -29999994, 20, 458843, (s32)_get_bomb_hit_position,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -29999997, -30000000, -29999994, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_THUNDERS_ATTACK1", 0, 0, -1, -1,
    0, 0, 131125, -29999998, 5, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, -29999987, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 300, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3", 65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 65570,
    -29999995, 65579, 2, 65579, 3, 65579, 6, 65579,
    4, 46, 65572, 1, 42, 65546, 1000, 49,
    65627, (s32)btlevtcmd_ResultAC, 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_THUNDERS_ATTACK4", 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2,
    983131, (s32)evt_eff, (s32)"", (s32)"sandars", 3, -30000000, -29999999, -29999998,
    0, 0, 0, 0, 0, 0, 0, 0,
    32, 983131, (s32)evt_eff, (s32)"", (s32)"sandars", 4, -30000000, -29999999,
    -29999998, 0, 0, 0, 0, 0, 0, 0,
    0, 33, 393307, (s32)evt_btl_camera_shake_h, 0, 10, 0, 20,
    13, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 131122, -29999990, 0, 65539, 10, 393307, (s32)btlevtcmd_CommandPreCheckDamage,
    -2, -29999997, -29999996, 256, -29999994, 131097, -29999994, 1,
    131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    65540, 50, 33, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000,
    2, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 65570, -30000000, 65576,
    3, 131122, -30000000, -1, 65576, 5, 131122, -30000000,
    0, 65576, 7, 131122, -30000000, 1, 42, 131122,
    -30000000, 2, 49, 131101, -30000000, 0, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 131328, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    -30000000, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33,
    32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1,
    33, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131097,
    -29999997, -1, 131125, -29999990, 1, 65540, 10, 33,
    65539, 90, 65627, (s32)btlevtcmd_StopAC, 65539, 92, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"J_1A", 110, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"J_1B", 327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976,
    -229998976, 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999591, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 65647, -29999985, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 90, -1, 112, 65545,
    60, 65631, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -29999995, -29999994,
    -29999993, 262235, (s32)btlevtcmd_GetStageSize, -250000000, -29999992, -250000000, 131125, -29999994,
    -29999992, 131128, -29999994, 2, 327771, (s32)btlevtcmd_SetPos, -2, -29999995,
    -29999994, -29999993, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999744, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 30, -1, 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    65647, -29999985, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    16, -1, 112, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15,
    15, 15, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 131101, -29999994, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"Y_1", 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000,
    1, 0, 0, 0, 65647, -29999985, 327771, (s32)evt_sub_intpl_init_float,
    11, -229998976, -229999386, 8, 65541, 8, 196699, (s32)evt_sub_intpl_get_float,
    -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995, -29999998, 65545, 1,
    6, 327771, (s32)evt_sub_intpl_init_float, 11, -229999386, -229998772, 8, 65541,
    8, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998772,
    -229998976, 6, 65541, 6, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -30000000, -29999995, -29999998, 65545, 1, 6, 112,
    110, 327771, (s32)evt_sub_intpl_init_float, 11, -229998976, -229998464, 8, 65541,
    8, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999,
    -29999998, 65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 11, -229998464,
    -229999386, 8, 65541, 8, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000,
    327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale,
    -2, -29999995, -29999999, -29999998, 65545, 1, 6, 327771,
    (s32)evt_sub_intpl_init_float, 11, -229999386, -229998976, 6, 65541, 6, 196699,
    (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -29999995, -29999999, -29999998, 65545,
    1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65545, 40,
    32, 65627, (s32)evt_audience_acrobat_notry, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"F_1",
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_THUNDERS_DOWN1", -250000000, 0, -250000000, 65545,
    40, 33, 65539, 95, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
#endif

#ifdef VERSION_G8ME01
EVT_BEGIN(partySandersAttack_CounterSet)
    CALL(btlevtcmd_JumpSetting, -2, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    SET_VALUE(LW(12), PTR(partyWeapon_SandersCounterSet))
    CALL(btlevtcmd_PayWeaponCost, -2, LW(12))
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_GetPos, -2, LW(0), -250000000, -250000000)
    CALL(btlevtcmd_GetPos, -3, LW(1), -250000000, -250000000)
    ADD(LW(0), LW(1))
    DIVIDE(LW(0), 2)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 73, 400, LW(0), 43, 0, 30, 5)
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePose, -2, LW(9), STRING("O_1"))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, -2, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 3, 0, 40, 1, 0, 1, 2, 0)
    CALL(btlevtcmd_AcSetFlag, 8)
    CALL(btlevtcmd_SetupAC, -2, 18, 1, 0)
    WAIT_FRAMES(52)
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_2"))
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_GetResultAC, LW(0))
    CALL(btlevtcmd_StopAC)
    IF_BITS_CLEAR(LW(0), 2)
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        ELSE
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_GetResultPrizeLv, -1, LW(0), LW(6))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    END_IF
    CALL(btlevtcmd_ACRStart, -2, 0, 12, 12, 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
        WAIT_FRAMES(30)
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    ADD(LW(0), 1)
    CALL(_make_counterset_weapon, LW(12), LW(0))
    WAIT_FRAMES(20)
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(30)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    END_INLINE_EVENT
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(12), 256, LW(5))
    WAIT_FRAMES(80)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
s32 partySandersAttack_CounterSet[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    131122, -29999988, (s32)partyWeapon_SandersCounterSet, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699,
    (s32)btlevtcmd_RunDataEventChild, -2, 7, 65545, 20, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -250000000, -250000000, 327771, (s32)btlevtcmd_GetPos, -3, -29999999, -250000000,
    -250000000, 131125, -30000000, -29999999, 131128, -30000000, 2, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 73,
    400, -30000000, 43, 0, 30, 5, 196699, (s32)btlevtcmd_GetBodyId,
    -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, -29999991, (s32)"O_1", 131163,
    (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll,
    3, 0, 40, 1, 0, 1, 2, 0,
    131163, (s32)btlevtcmd_AcSetFlag, 8, 327771, (s32)btlevtcmd_SetupAC, -2, 18, 1,
    0, 65545, 52, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_2", 131163, (s32)btlevtcmd_StartAC, 1, 65627,
    (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 65627, (s32)btlevtcmd_StopAC, 131103, -30000000,
    2, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 32, 196699, (s32)btlevtcmd_AcGetOutputParam,
    0, -30000000, 131126, -30000000, 1, 262235, (s32)btlevtcmd_GetResultPrizeLv, -1,
    -30000000, -29999994, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -29999988, -29999994, 33, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131125,
    -30000000, 1, 196699, (s32)_make_counterset_weapon, -29999988, -30000000, 65545, 20,
    107, 65545, 30, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 109, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 65545, 80, 65539, 99,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};
#endif

#ifdef VERSION_G8ME01
EVT_BEGIN(partySandersAttack_TimeBombSet)
    CALL(btlevtcmd_CommandPayWeaponCost, -2)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(10), LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(11), LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), 16777216)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(12), LW(3))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, -2, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 12)
        CASE_EQUAL(-2)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 15)
        CASE_EQUAL(-1)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 20)
        CASE_EQUAL(0)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 22)
        CASE_EQUAL(1)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 32)
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 90)
        SET_VALUE(LW(2), 50)
        CASE_DEFAULT
        SET_VALUE(LW(1), 120)
        SET_VALUE(LW(2), 80)
    END_SWITCH
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    CALL(btlevtcmd_AcSetParamAll, LW(0), 3, LW(1), LW(1), 0, 90, LW(2), -250000000)
    CALL(btlevtcmd_SetupAC, -2, 7, 1, 0)
    CALL(btlevtcmd_AcSetFlag, 1)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_4A"))
    CALL(btlevtcmd_StartAC, 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(LW(14))
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                SWITCH(LW(13))
                    CASE_EQUAL(0)
                    SET_VALUE(LW(3), LW(10))
                    CASE_EQUAL(1)
                    SET_VALUE(LW(3), LW(11))
                    CASE_DEFAULT
                    SET_VALUE(LW(3), LW(12))
                END_SWITCH
                CALL(btlevtcmd_OffAttribute, LW(3), 16777216)
                CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
                CALL(btlevtcmd_AcGetOutputParam, 1, LW(1))
                ADD(LW(1), 20)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_4B"))
                SPAWN_EVENT_GET_ID(PTR(_shot_bomb_event), LW(9))
                ADD(LW(13), 1)
                IF_INT_GREATER_OR_EQUAL(LW(13), 3)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
                    WAIT_FRAMES(10)
                    CALL(btlevtcmd_ACRStart, -2, 0, 12, 12, 10)
                    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
                    SWITCH(LW(6))
                        CASE_GREATER_OR_EQUAL(2)
                        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
                        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
                        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
                        CASE_DEFAULT
                        CALL(evt_audience_acrobat_notry)
                    END_SWITCH
                    CALL(btlevtcmd_WaitEventEnd, LW(9))
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_4A"))
                CALL(btlevtcmd_AcSetOutputParam, 0, 0)
            END_IF
            WAIT_FRAMES(1)
            SET_VALUE(LW(14), 5)
        END_LOOP
        DEBUG_PUT_MSG(STRING("イベント終了"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_ResultAC)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
s32 partySandersAttack_TimeBombSet[] = {
    131163, (s32)btlevtcmd_CommandPayWeaponCost, -2, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_bomzou, 0,
    196699, (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998,
    131122, -29999990, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_bomzou, 0,
    196699, (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998,
    131122, -29999989, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_bomzou, 0,
    196699, (s32)btlevtcmd_OnAttribute, -29999997, 16777216, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998,
    131122, -29999988, -29999997, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3,
    65570, -30000000, 65576, -3, 131122, -29999999, 80, 131122,
    -29999998, 12, 65572, -2, 131122, -29999999, 80, 131122,
    -29999998, 15, 65572, -1, 131122, -29999999, 80, 131122,
    -29999998, 20, 65572, 0, 131122, -29999999, 80, 131122,
    -29999998, 22, 65572, 1, 131122, -29999999, 80, 131122,
    -29999998, 32, 65572, 2, 131122, -29999999, 90, 131122,
    -29999998, 50, 42, 131122, -29999999, 120, 131122, -29999998,
    80, 49, 196699, (s32)btlevtcmd_GetUnitId, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll,
    -30000000, 3, -29999999, -29999999, 0, 90, -29999998, -250000000,
    327771, (s32)btlevtcmd_SetupAC, -2, 7, 1, 0, 131163, (s32)btlevtcmd_AcSetFlag,
    1, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A",
    131163, (s32)btlevtcmd_StartAC, 1, 65647, -29999985, 131122, -29999987, 0,
    131122, -29999986, 5, 65541, -29999986, 196699, (s32)btlevtcmd_AcGetOutputParam, 0,
    -30000000, 131097, -30000000, 0, 65570, -29999987, 65572, 0,
    131122, -29999997, -29999990, 65572, 1, 131122, -29999997, -29999989,
    42, 131122, -29999997, -29999988, 49, 196699, (s32)btlevtcmd_OffAttribute, -29999997,
    16777216, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -30000000, 196699, (s32)btlevtcmd_AcGetOutputParam, 1,
    -29999999, 131125, -29999999, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_4B", 131165, (s32)_shot_bomb_event, -29999991, 131125, -29999987, 1, 131101,
    -29999987, 3, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999991, 7, 33, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4A", 196699, (s32)btlevtcmd_AcSetOutputParam, 0, 0,
    33, 65545, 1, 131122, -29999986, 5, 6, 65649,
    (s32)/*"イベント終了"*/"\x83\x43\x83\x78\x83\x93\x83\x67\x8F\x49\x97\xB9", 112, 65627, (s32)btlevtcmd_ResultAC, 65545, 60, 65627, (s32)btlevtcmd_StopAC,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65539, 90, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};
#endif

EVT_BEGIN(_shot_bomb_event)
    CALL(_shot_move, LW(3), LW(0), LW(1), LW(0), LW(1), LW(2), LW(5))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(6.399414f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), 16, -1)
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(3.5996094f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), 12, -1)
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(4.0f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetFaceDirection, LW(3), LW(0))
        MULTIPLY(LW(0), -18)
        CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 7, 0)
        LOOP(20)
            CALL(btlevtcmd_AddRotate, LW(3), 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, LW(3), 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_MovePosition, LW(3), LW(0), LW(1), LW(2), 20, -1, 0)
    CALL(_judge_on_stage, LW(3), LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_KillUnit, LW(3), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("B_2"))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_BOMB1"), LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 1, LW(0))
    WAIT_MS(400)
    CALL(btlevtcmd_StartWaitEvent, LW(3))
    RETURN
EVT_END()

EVT_BEGIN(sanders_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 66)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    CALL(btlevtcmd_AudienceAppeal, -2)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
    CALL(btlevtcmd_StageDispellFog)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
static EVT_BEGIN(attack_audience_event)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(3), -250000000, -250000000)
    CALL(btlevtcmd_GetFaceDirection, -2, LW(4))
    SET_VALUE(LW(8), LW(3))
    MULTIPLY(LW(8), LW(4))
    MULTIPLY(LW(8), -1)
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_MovePosition, -2, LW(8), LW(1), LW(2), 0, -1, 0)
    WAIT_FRAMES(20)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageAudienceAreaSize, LW(4), -250000000, -250000000)
    CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
    SET_VALUE(LW(6), LW(4))
    MULTIPLY(LW(6), LW(5))
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_SetPos, -2, LW(6), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 13)
    CALL(evt_btl_camera_set_homing_unit_audience, 0, -2, 1, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 30)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_3"))
    WAIT_MS(1000)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_SetScale, -2, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 20, 13)
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    BEGIN_SIBLING_EVENT
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(500)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, -250000000, LW(8), -250000000)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, -2, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
static s32 attack_audience_event[] = {
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize,
    -29999997, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999996, 131122,
    -29999992, -29999997, 131127, -29999992, -29999996, 131127, -29999992, -1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 524379, (s32)btlevtcmd_MovePosition, -2, -29999992, -29999999, -29999998, 0,
    -1, 0, 65545, 20, 327771, (s32)_get_attack_aud_no, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -29999996, -250000000, -250000000, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131122, -29999994, -29999996, 131127, -29999994,
    -29999995, 131127, -29999994, -1, 327771, (s32)btlevtcmd_SetPos, -2, -29999994,
    -29999999, -29999998, 196699, (s32)evt_btl_camera_set_mode, 0, 13, 327771, (s32)evt_btl_camera_set_homing_unit_audience,
    0, -2, 1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    30, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_BTL_THUNDERS_ATTACK2", -29999986, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3", 65546,
    1000, 131163, (s32)evt_snd_sfxoff, -29999986, 327771, (s32)btlevtcmd_SetScale, -2, -229998976,
    -229998976, -229998976, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_THUNDERS_ATTACK3", 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 983131, (s32)evt_eff64, (s32)"", (s32)"bomb_n64",
    1, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 393307, (s32)evt_btl_camera_shake_h, 0, 10,
    0, 20, 13, 196699, (s32)_attack_aud, -29999997, 0, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 110, 65546, 1500, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65546, 500, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"J_1A", 110, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"J_1B", 112, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999591, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 65647, -29999985, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 90, -1, 112,
    65545, 60, 65631, -29999985, 327771, (s32)btlevtcmd_GetPos, -2, -29999995,
    -29999994, -29999993, 262235, (s32)btlevtcmd_GetStageSize, -250000000, -29999992, -250000000, 131125,
    -29999994, -29999992, 131128, -29999994, 2, 327771, (s32)btlevtcmd_SetPos, -2,
    -29999995, -29999994, -29999993, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999744, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 65647, -29999985, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 16, -1, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};
#endif

EVT_BEGIN(sanders_battle_end_event)
    CALL(btlevtcmd_OnOffStatus, -2, 22, 0, 0, 0)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_sanders_stay))
    RETURN
EVT_END()

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

s32 entry_bomzou[] = {
    (s32)unit_bomzou, 33554432, 67108865, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("Y_1"))
    WAIT_FRAMES(48)
    RETURN
EVT_END()

USER_FUNC(_sanders_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->mWeaponTable[*count].mIndex = -1;
    command->mWeaponTable[*count].mItem = 0;
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_SandersNormalAttack;
    command->mWeaponTable[*count].field_0x4 = 0;
    command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
    (*count)++;

    if (techLv >= 0) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_SandersTimeBombSet;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_SandersCounterSet;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->mWeaponTable[*count].mIndex = -1;
        command->mWeaponTable[*count].mItem = 0;
        command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)partyWeapon_SandersSuperBombAttack;
        command->mWeaponTable[*count].field_0x4 = 0;
        command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;
        command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name);
        (*count)++;
    }
}

USER_FUNC(_get_bomb_hit_position) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    Vec pos;
    s32 id, targetId, dir;
    s32 outZ, outX, outY;


    id = evtGetValue(event, args[0]);
    targetId = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    BattleGetUnitPtr(wp, BattleTransID(event, id));
    unit = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    dir = unit->faceDirection;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += dir * (unit->bintaHitOffset.x * unit->mSizeMultiplier);
    pos.y += unit->bintaHitOffset.y * unit->mSizeMultiplier;
    pos.z += unit->bintaHitOffset.z * unit->mSizeMultiplier;
    evtSetFloat(event, outX, pos.x);
    evtSetFloat(event, outY, pos.y);
    evtSetFloat(event, outZ, pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_counterset_weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id, value;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    value = evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    weapon->holdFastTime = value;
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(_shot_move) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    f32 speed, floor;
    s32 id, angle, outX, outY, outZ, outSpeed;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    angle = evtGetValue(event, args[1]);
    speed = 0.1f * evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    outSpeed = args[6];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        f32 x, y, z;

        BtlUnit_GetPos(unit, &x, &y, &z);
        unit->mMoveCurrentPos.x = x;
        unit->mMoveCurrentPos.y = y;
        unit->mMoveCurrentPos.z = z;
        unit->mMoveDirection = angleABf(0.0f, 0.0f, 1.0f, 0.0f);
        unit->mFallAccel = 0.2f;
        unit->mMoveSpeedY = 0.8f * (0.9f * (speed * cosfd(angle)));
        unit->mMoveSpeedXZ = 0.8f * (0.75f * (speed * sinfd(angle)));
    }
    unit->mMoveCurrentPos.y += unit->mMoveSpeedY;
    unit->mMoveSpeedY -= unit->mFallAccel;
    btlMovePos(unit->mMoveSpeedXZ, unit->mMoveDirection, &unit->mMoveCurrentPos.x, &unit->mMoveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    floor = BattleGetFloorHeight(wp, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    if (unit->mMoveCurrentPos.y > floor) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, floor, unit->mMoveCurrentPos.z);
    evtSetValue(event, outX, unit->mMoveCurrentPos.x);
    evtSetValue(event, outY, floor);
    evtSetValue(event, outZ, unit->mMoveCurrentPos.z);
    evtSetFloat(event, outSpeed, unit->mMoveSpeedXZ);
    return EVT_RETURN_YIELD;
}

USER_FUNC(_judge_on_stage) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleStage* stage;
    f32 z, y, x;
    s32 id, index;

    stage = BattleStageGetPtr();
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    index = args[1];
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (__fabs(x) < 40.0f + stage->stageSizeX) {
        evtSetValue(event, index, TRUE);
    } else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}
