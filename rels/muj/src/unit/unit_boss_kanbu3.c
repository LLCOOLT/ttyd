#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_JumpSetting);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OnOffStatus);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetHp);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPartsDefenceTable);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(check_exist_group);
USER_FUNC(evt_batstage_return_aud_dark_base);
USER_FUNC(evt_batstage_set_aud_dark);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_btl_camera_set_prilimit);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_eff);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_random);
USER_FUNC(up_ceil);
USER_FUNC(zakogun_escape1);
USER_FUNC(zakogun_escape2);
USER_FUNC(zakogun_ext_init1);
USER_FUNC(zakogun_ext_init3);
USER_FUNC(check_exist_kenkyu);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHp[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 down_ceil_20_text_9C8C[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 unit_boss_gundan_zako_group1[];
extern s32 unit_boss_gundan_zako_group2[];
extern s32 unit_boss_gundan_zako_group3[];
extern s32 unit_gundan_zako_magician_20_data_32438[];
extern s32 weaponGetPowerDefault[];
extern s32 zakogun_entry[];
extern s32 zakogun_escape3[];
extern s32 zakogun_ext_init2[];

__declspec(section ".data") u64 fd_boss_kanbu3_negone_one_374;
__declspec(section ".data") s32 fd_boss_kanbu3_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_kanbu3___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_kanbu3___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_kanbu3_one_negone_373;
__declspec(section ".data") s32 fd_boss_kanbu3___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_kanbu3_one_381[1];
__declspec(section ".data") u64 fd_boss_kanbu3_negone_one_360;
__declspec(section ".data") s32 fd_boss_kanbu3_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_kanbu3___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_kanbu3___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_kanbu3_one_negone_359;
__declspec(section ".data") s32 fd_boss_kanbu3___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_kanbu3_one_364[1];
BattleUnitKind unit_boss_kanbu3;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") s32 defence_guard[2];
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") BattleDataEntry data_table[3];
__declspec(section ".data") s32 data_table2[4];
static BattleUnitKindPart parts[1];
s32 weapon_kanbu3_attack[48];
s32 weapon_kanbu3_charge[48];
__declspec(section ".data") s32 entry_kenkyu[12];
__declspec(section ".data") s32 entry_group1[12];
__declspec(section ".data") s32 entry_group2[12];
__declspec(section ".data") s32 entry_group3[12];
static s32 init_event[59];
static s32 entry_event[45];
static s32 damage_event[315];
static s32 dead_event[402];
static s32 phase_event[55];
s32 call_event[284];
static s32 attack_event[136];
static s32 guard_event[56];
static s32 guard_cancel_event[69];
s32 no_event[27];
static s32 charge_event[71];
static __declspec(section ".data") s32 wait_event[6];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_guard[18];
static s32 normal_attack_event[365];

__declspec(section ".data") u64 fd_boss_kanbu3_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kanbu3_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kanbu3___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kanbu3___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kanbu3_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kanbu3___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kanbu3_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_kanbu3_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_kanbu3_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_kanbu3___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_kanbu3___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_kanbu3_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_kanbu3___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_kanbu3_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_kanbu3 = {
    99,
    "btl_un_kanbu3",
    30,
    0,
    1,
    1,
    57,
    0,
    0,
    100,
    0,
    50,
    8,
    56,
    59,
    0,
    56,
    0.0f,
    26.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    28.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    18.0f,
    38.35f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    42.0f,
    52.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KANBU_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") s32 defence_guard[] = {
    33686018, 33554432,
};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 70, 60, 100, 80, 100, 100, 60, 100, 85, 100, 85, 100, 90, 60, 0, 0, 100, 60, 100, 0, 0};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

__declspec(section ".data") s32 data_table2[] = {
    48, (s32)btldefaultevt_Dummy, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kanbu3", "c_kanbu", 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

s32 weapon_kanbu3_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 4231, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_kanbu3_charge[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    0, 0, 0, 0, 0, 100, 0, 0,
};

__declspec(section ".data") s32 entry_kenkyu[] = {
    (s32)unit_gundan_zako_magician_20_data_32438, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_group1[] = {
    (s32)unit_boss_gundan_zako_group1, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_group2[] = {
    (s32)unit_boss_gundan_zako_group2, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_group3[] = {
    (s32)unit_boss_gundan_zako_group3, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL_CHILD(PTR(zakogun_entry))
    CALL(zakogun_ext_init1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 166, 88, 422, 166, 60, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg5_muj_125_00"), 0, -2)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    RETURN
EVT_END()

static s32 damage_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 2,
    262235, (s32)btlevtcmd_CheckDamageCode, -2, 512, -30000000, 131097, -30000000, 0,
    262235, (s32)btlevtcmd_CheckDamageCode, -2, 2048, -30000000, 131096, -30000000, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_1", 65627, (s32)btlevtcmd_WaitAttackEnd, 65545,
    120, 131163, (s32)check_exist_group, -30000000, 131097, -30000000, -1, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_BOSS_TEAM_3RD_ESCAPE1", -29999987, 65627, (s32)zakogun_escape3, 131163, (s32)evt_snd_sfxoff, -29999987,
    196699, (s32)btlevtcmd_KillUnit, -30000000, 0, 33, 33, 33, 33,
    131122, -29999990, -2, 131122, -29999989, 1, 65630, (s32)btldefaultevt_Damage,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 0,
    196699, (s32)btlevtcmd_GetHp, -2, -30000000, 131100, -30000000, 15, 65627,
    (s32)btlevtcmd_WaitAttackEnd, 65545, 90, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1",
    131163, (s32)check_exist_group, -30000000, 131097, -30000000, -1, 262235, (s32)btlevtcmd_GetUnitWork,
    -30000000, 1, -29999999, 131097, -29999999, 0, 65545, 90,
    65540, 10, 33, 32, 65540, 10, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"C_2", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"C_2", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_2", 65545,
    60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 131163, (s32)check_exist_group,
    -30000000, 131097, -30000000, -1, 65627, (s32)zakogun_escape1, 196699, (s32)btlevtcmd_KillUnit,
    -30000000, 0, 33, 65545, 20, 65539, 10, 65545,
    20, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131163, (s32)evt_btl_camera_set_prilimit, 1, 196699,
    (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 166, 88,
    422, 166, 60, 0, 20, 11, 65545, 20,
    327771, (s32)evt_msg_print, 2, (s32)"stg5_muj_125_01", 0, -2, 131163, (s32)evt_btl_camera_set_prilimit,
    0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    65546, 500, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_2", 65545, 16,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_2", 65545, 16, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"C_2", 65545, 60, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 327771,
    (s32)evt_msg_print, 2, (s32)"stg5_muj_125_02", 0, -2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    65546, 500, 65627, (s32)zakogun_ext_init2, 262235, (s32)btlevtcmd_SpawnUnit, -30000000, (s32)entry_group2,
    0, 327771, (s32)btlevtcmd_SetPos, -30000000, 0, 80, 0, 327771,
    (s32)btlevtcmd_SetHomePos, -30000000, 0, 80, 0, 65627, (s32)down_ceil_20_text_9C8C, 65545,
    60, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 1, 33, 65540, 99, 33, 65539,
    99, 2, 1,
};

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(&defence))
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
        CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    END_IF
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_WaitAttackEnd)
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(btlevtcmd_GetUnitWork, LW(0), 1, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                WAIT_FRAMES(180)
            END_IF
        END_IF
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(zakogun_escape1)
            CALL(btlevtcmd_KillUnit, LW(0), 0)
        END_IF
        CASE_END
        CASE_EQUAL(1)
        CALL(btlevtcmd_WaitAttackEnd)
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(btlevtcmd_GetUnitWork, LW(0), 2, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                WAIT_FRAMES(180)
            END_IF
        END_IF
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(up_ceil)
            CALL(zakogun_escape2)
            CALL(btlevtcmd_KillUnit, LW(0), 0)
        END_IF
        CASE_END
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_1"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(5.0f))
    CALL(btlevtcmd_ChangeFaceDirection, -2, 1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_MovePosition, -2, 300, LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_moveto, 0, 220, 87, 419, 220, 60, 0, 60, 11)
    WAIT_FRAMES(60)
    CALL(evt_batstage_set_aud_dark, 0, 1, 0)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 250, 30, 104, 4, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 220, 30, 103, 5, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(25)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 280, 30, 102, 6, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(15)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 235, 60, 101, 7, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 265, 60, 100, 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(5)
    CALL(btlevtcmd_GetMaxHp, -2, LW(0))
    CALL(btlevtcmd_SetHp, -2, LW(0))
    CALL(btlevtcmd_OnOffStatus, -2, 27, 0, 0, 0)
    WAIT_FRAMES(95)
    CALL(evt_batstage_return_aud_dark_base, 1, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 80)
    SUBTRACT(LW(2), 20)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_group3), 0)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("R_1"))
        CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(5.0f))
        CALL(btlevtcmd_ChangeFaceDirection, -2, -1)
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_MOVE2"), 0)
    CALL(zakogun_ext_init3)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 2)
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table2))
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 166, 88, 422, 166, 60, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg5_muj_125_03"), 0, -2)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL_CHILD(PTR(call_event))
    END_IF
    LABEL(99)
    RETURN
EVT_END()

s32 call_event[] = {
    131163, (s32)check_exist_group, -29999985, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000,
    65570, -30000000, 65572, 0, 131096, -29999985, -1, 65540,
    10, 33, 46, 65572, 1, 131096, -29999985, -1,
    65540, 10, 33, 46, 65572, 2, 131096, -29999985,
    -1, 65540, 10, 33, 46, 49, 131122, -30000000,
    0, 65540, 99, 65539, 10, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -30000000, 65570, -30000000, 65572, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KANBU_CALL_BACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"C_1", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_BACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_1",
    46, 65572, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_2", 65545,
    16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_2", 65545, 16, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_ON1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"C_2", 46, 65572, 2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_KANBU_CALL_BACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"C_1", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_CALL_BACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"C_1",
    46, 49, 107, 65545, 100, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 69, 109, 131096, -29999985, -1, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 0, -30000000, 65570, -30000000, 65572, 0, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 131126, -30000000, 80,
    131126, -29999998, 20, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_group1, 0,
    327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos,
    -29999997, -30000000, -29999999, -29999998, 65627, (s32)zakogun_ext_init1, 65545, 120,
    46, 65572, 1, 65627, (s32)zakogun_ext_init2, 262235, (s32)btlevtcmd_SpawnUnit, -30000000,
    (s32)entry_group2, 0, 327771, (s32)btlevtcmd_SetPos, -30000000, 0, 80, 0,
    327771, (s32)btlevtcmd_SetHomePos, -30000000, 0, 80, 0, 65627, (s32)down_ceil_20_text_9C8C,
    65545, 60, 46, 65572, 2, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 131126, -30000000, 80, 131126, -29999998,
    20, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_group3, 0, 327771, (s32)btlevtcmd_SetPos,
    -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000,
    -29999999, -29999998, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_TEAM_3RD_MOVE2", 0, 65627, (s32)zakogun_ext_init3,
    65545, 120, 46, 49, 33, 131122, -30000000, 1,
    65539, 99, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            LABEL(10)
            SET_VALUE(LW(0), 75)
            ADD(LW(0), 0)
            ADD(LW(0), 30)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 75)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_kanbu3_attack))
                CALL_CHILD(PTR(normal_attack_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 0)
            IF_INT_LESS(LW(1), LW(0))
                CALL_CHILD(PTR(guard_event))
                GOTO(99)
            END_IF
            CALL_CHILD(PTR(call_event))
            IF_INT_EQUAL(LW(0), 1)
                GOTO(99)
                ELSE
                GOTO(10)
            END_IF
            ELSE
            CALL(evt_sub_random, 99, LW(1))
            IF_INT_LESS(LW(1), 50)
                CALL_CHILD(PTR(guard_cancel_event))
                ELSE
                CALL_CHILD(PTR(no_event))
            END_IF
        END_IF
        ELSE
        SET_VALUE(LW(0), 50)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 50)
            SET_VALUE(LW(9), PTR(weapon_kanbu3_attack))
            CALL_CHILD(PTR(normal_attack_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(charge_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(guard_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("G_1"))
    WAIT_FRAMES(16)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("G_2"))
    CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(defence_guard))
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_guard))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

static EVT_BEGIN(guard_cancel_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, -2, 15, 0, FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_SetPartsDefenceTable, -2, 1, PTR(&defence))
    CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

EVT_BEGIN(no_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

static EVT_BEGIN(charge_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_kanbu3_charge))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_kanbu3_charge))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("G_1"))
    WAIT_FRAMES(16)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("G_2"))
    WAIT_FRAMES(120)
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(60)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_kanbu3_charge))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_kanbu3_charge), 256, LW(5))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {65, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "G_2"},
    {65, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "G_2"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "G_2"},
};

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"R_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0,
    -29999998, 0, -1, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_JUMP1",
    -250000000, 0, -250000000, 110, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1A", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B",
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229997952, -229999796, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65540, 98, 65539, 98, 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1C", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KANBU_HIP_ATTACK1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0, 10,
    0, 60, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, 0, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1C", 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 10, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, 0, -229999796, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 10, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1C", 65545, 25, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_KANBU_HIP_ATTACK2",
    -250000000, 0, -250000000, 65545, 7, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_KANBU_HIP_ATTACK2", -250000000, 0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"D_1", 65545, 15, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -2, 15, 0, -229998976,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 10, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 65545, 10, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1",
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229992832, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, 0, -29999998,
    0, -1, 0, 2, 1,
};

USER_FUNC(check_exist_group) {
    s32 i;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && (unit->initialKind == 0x64 || unit->initialKind == 0x65 || unit->initialKind == 0x66)) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
USER_FUNC(check_exist_kenkyu) {
    s32 i;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x77) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
