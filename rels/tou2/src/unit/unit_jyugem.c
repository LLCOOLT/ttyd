#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPartsPosition);
USER_FUNC(btlevtcmd_JumpPartsSetting);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OffPartsCounterAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
static USER_FUNC(togezo_copy_status);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckActStatus[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_JumpPartsContinue[];
extern s32 btlevtcmd_OnPartsCounterAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_get_turn[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_mode[];
extern s32 subsetevt_confuse_flustered[];
extern s32 unit_togezo_28_data_35BD0[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_jyugem_negone_one_374;
__declspec(section ".data") s32 fd_jyugem_neg_one_382[1];
__declspec(section ".data") s32 fd_jyugem___local_PI_383[1];
__declspec(section ".data") s32 fd_jyugem___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_jyugem_one_negone_373;
__declspec(section ".data") s32 fd_jyugem___local_PIO2_384[1];
__declspec(section ".data") s32 fd_jyugem_one_381[1];
__declspec(section ".data") u64 fd_jyugem_negone_one_360;
__declspec(section ".data") s32 fd_jyugem_neg_one_365[1];
__declspec(section ".data") s32 fd_jyugem___local_PI_366[1];
__declspec(section ".data") s32 fd_jyugem___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_jyugem_one_negone_359;
__declspec(section ".data") s32 fd_jyugem___local_PIO2_367[1];
__declspec(section ".data") s32 fd_jyugem_one_364[1];
BattleUnitKind unit_jyugem_28_data_2B678;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_hold[17];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
static s32 weapon_jyugem_attack[48];
static __declspec(section ".data") s32 entry_togezo[12];
static s32 init_event[40];
static s32 damage_event[322];
static s32 unison_phase_event[139];
static s32 avoid_counter_thorn_head_event[61];
static s32 dmg_first_attack_pos_event[19];
static s32 attack_event[185];
static s32 normal_attack_event[585];
static s32 friend_event[263];
static __declspec(section ".data") s32 wait_event[6];

static USER_FUNC(togezo_copy_status) {
    s32* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->mSizeChangeTurns = unit1->mSizeChangeTurns;
    unit2->mSizeChangeStrength = unit1->mSizeChangeStrength;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_jyugem_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jyugem_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jyugem___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jyugem___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jyugem_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jyugem___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jyugem_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_jyugem_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_jyugem_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_jyugem___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_jyugem___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_jyugem_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_jyugem___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_jyugem_one_364[] = {
    1065353216,
};

BattleUnitKind unit_jyugem_28_data_2B678 = {
    40,
    "btl_un_jyugem",
    5,
    0,
    1,
    1,
    11,
    0,
    2,
    70,
    1,
    50,
    9999,
    32,
    42,
    4,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    10.0f,
    38.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    32.0f,
    42.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_JUGEMU_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 90, 105, 100, 80, 100, 100, 100, 100, 90, 100, 90, 100, 95, 80, 90, 100, 100, 80, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "JGM_N_1"},
    {2, "JGM_Y_1"},
    {9, "JGM_Y_1"},
    {5, "JGM_K_1"},
    {4, "JGM_X_1"},
    {3, "JGM_X_1"},
    {28, "JGM_S_1"},
    {29, "JGM_Q_1"},
    {30, "JGM_Q_1"},
    {31, "JGM_S_1"},
    {39, "JGM_D_1"},
    {42, "JGM_R_1"},
    {40, "JGM_W_1"},
    {56, "JGM_I_1"},
    {57, "JGM_I_1"},
    {65, "JGM_T_1"},
    {69, "JGM_S_1"},
};

static PoseTableEntry pose_table_hold[] = {
    {1, "JGM_S_2"},
    {2, "JGM_S_2"},
    {9, "JGM_S_2"},
    {5, "JGM_S_2"},
    {4, "JGM_S_2"},
    {3, "JGM_S_2"},
    {28, "JGM_S_2"},
    {29, "JGM_Q_1"},
    {30, "JGM_Q_1"},
    {31, "JGM_S_2"},
    {39, "JGM_D_1"},
    {42, "JGM_S_2"},
    {40, "JGM_S_2"},
    {56, "JGM_S_2"},
    {57, "JGM_S_2"},
    {65, "JGM_S_2"},
    {69, "JGM_S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {37, avoid_counter_thorn_head_event},
    {48, dmg_first_attack_pos_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_jyugem", "c_jugemu", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, /*"パイポ"*/"\x83\x70\x83\x43\x83\x7C", "c_jugemu", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static s32 weapon_jyugem_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_togezo[] = {
    (s32)unit_togezo_28_data_35BD0, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("JGM_P_1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(btldefaultevt_Damage))
        ELSE
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            SET_VALUE(LW(15), 1)
            ELSE
            SET_VALUE(LW(15), 0)
        END_IF
        CALL(btlevtcmd_CheckStatus, LW(10), 27, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 1, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 3, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 5, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 6, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 9, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), 2, LW(14))
        OR(LW(15), LW(14))
        IF_INT_NOT_EQUAL(LW(15), 0)
            BEGIN_INLINE_EVENT
                CALL(btlevtcmd_OffPartsAttribute, -2, 2, 50331648)
                CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
                ADD(LW(1), 35)
                CALL(btlevtcmd_SetPartsPos, -2, 2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 200)
                CALL(btlevtcmd_JumpPartsSetting, LW(10), 2, 0, FLOAT(5.0f), FLOAT(0.2998047f))
                CALL(btlevtcmd_JumpPartsPosition, LW(10), 2, LW(0), 0, LW(2), 0, -1)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 16777216)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 33554432)
            END_INLINE_EVENT
            CALL(btlevtcmd_SetUnitWork, LW(10), 0, 0)
            CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), 1, 1)
            CALL(btlevtcmd_AnimeSetPoseTable, LW(10), 1, PTR(pose_table))
            CALL(btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0)
            CALL_CHILD(PTR(btldefaultevt_Damage))
            ELSE
            CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
            IF_INT_EQUAL(LW(0), 22)
                GOTO(90)
            END_IF
            IF_INT_EQUAL(LW(0), 30)
                GOTO(90)
            END_IF
            IF_INT_EQUAL(LW(0), 31)
                GOTO(90)
            END_IF
            IF_INT_EQUAL(LW(0), 38)
                GOTO(90)
            END_IF
            IF_INT_EQUAL(LW(0), 39)
                GOTO(90)
            END_IF
            IF_INT_EQUAL(LW(0), 41)
                GOTO(90)
            END_IF
            CALL(btlevtcmd_CheckStatus, LW(10), 4, LW(15))
            CALL(btlevtcmd_CheckStatus, LW(10), 8, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), 11, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), 15, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), 20, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), 0, LW(14))
            OR(LW(15), LW(14))
            IF_INT_NOT_EQUAL(LW(15), 0)
                BEGIN_INLINE_EVENT
                    CALL(btlevtcmd_OffPartsAttribute, -2, 2, 50331648)
                    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
                    ADD(LW(1), 35)
                    CALL(btlevtcmd_SetPartsPos, -2, 2, LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_JumpPartsSetting, LW(10), 2, 30, 0, FLOAT(0.099609375f))
                    CALL(btlevtcmd_JumpPartsPosition, LW(10), 2, LW(0), LW(1), LW(2), 30, -1)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 33554432)
                END_INLINE_EVENT
            END_IF
            LABEL(90)
            CALL_CHILD(PTR(btldefaultevt_Damage))
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 unison_phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131096, -30000000, 0, 65540,
    99, 33, 131163, (s32)btlevtcmd_get_turn, -30000000, 131096, -30000000, 1,
    65540, 99, 33, 262235, (s32)btlevtcmd_CheckStatus, -2, 27, -30000000,
    131096, -30000000, 1, 65540, 99, 33, 196699, (s32)btlevtcmd_CheckActStatus,
    -2, -30000000, 131096, -30000000, 0, 65540, 99, 33,
    131122, -29999985, 0, 262235, (s32)btlevtcmd_CheckStatus, -2, 3, -29999986,
    131151, -29999985, -29999986, 262235, (s32)btlevtcmd_CheckStatus, -2, 5, -29999986,
    131151, -29999985, -29999986, 262235, (s32)btlevtcmd_CheckStatus, -2, 6, -29999986,
    131151, -29999985, -29999986, 131097, -29999985, 0, 65540, 99,
    33, 196699, (s32)evt_sub_random, 99, -30000000, 131098, -30000000, 50,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_ATTACK1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_1", 65545, 40, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_JUGEM_HOLD1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"JGM_A_2", 65545, 30, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0,
    1, 262235, (s32)btlevtcmd_OnPartsCounterAttribute, -2, 1, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_hold, 196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 393307,
    (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 20, 0, 33, 65539,
    99, 2, 1,
};

static EVT_BEGIN(avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, -2, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 25)
        GOTO(90)
    END_IF
    ADD(LW(1), 35)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_first_attack_pos_event)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
    END_IF
    SET_VALUE(LW(11), 20)
    ADD(LW(11), 65)
    ADD(LW(11), 15)
    SUBTRACT(LW(11), 1)
    CALL(evt_sub_random, LW(11), LW(10))
    SET_VALUE(LW(11), 20)
    IF_INT_LESS(LW(10), LW(11))
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 0)
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), 0)
                SUBTRACT(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    CALL_CHILD(PTR(friend_event))
                    GOTO(99)
                END_IF
                ELSE
                GOTO(9)
            END_IF
        END_LOOP
        LABEL(9)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 0)
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
            IF_INT_LESS_OR_EQUAL(LW(0), 150)
                ADD(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    CALL_CHILD(PTR(friend_event))
                    GOTO(99)
                END_IF
                ELSE
                GOTO(10)
            END_IF
        END_LOOP
    END_IF
    LABEL(10)
    SET_VALUE(LW(11), 65)
    ADD(LW(11), 15)
    SUBTRACT(LW(11), 1)
    CALL(evt_sub_random, LW(11), LW(10))
    SET_VALUE(LW(11), 65)
    IF_INT_LESS(LW(10), LW(11))
        CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
        ELSE
        CALL(btlevtcmd_SetUnitWork, -2, 1, 1)
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_jyugem_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_jyugem_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_jyugem_attack, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_jyugem_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 0, -29999990, 131096, -29999990, 0, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_JUGEM_ATTACK1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"JGM_A_1", 65545, 40, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_ATTACK2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_2",
    65545, 30, 32, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0,
    262235, (s32)btlevtcmd_OffPartsCounterAttribute, -2, 1, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2,
    1, (s32)pose_table, 393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 0,
    0, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_3", 65545,
    2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 50331648, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 131125, -29999999, 35, 393307,
    (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_JUGEM_THROW1", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2,
    45, 0, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000,
    -29999999, -29999998, 45, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, (s32)weapon_jyugem_attack, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    196699, (s32)btlevtcmd_JumpPartsContinue, -2, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_JUMP1",
    -250000000, 0, -250000000, 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_jyugem_attack, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_jyugem_attack, 256, -29999995, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -30000000,
    131096, -30000000, 1, 262235, (s32)btlevtcmd_CheckDamageCode, -29999997, 262144, -30000000,
    131097, -30000000, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131122, -29999999, 0, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 40, 131122, -29999996, -30000000, 196699, (s32)btlevtcmd_GetFaceDirection,
    -2, -29999995, 131127, -29999996, -29999995, 131098, -29999996, 0,
    131126, -29999998, 10, 589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999,
    -29999998, 40, 0, 0, 0, 131096, -29999997, -1,
    65540, 97, 33, 32, 65540, 96, 33, 6,
    65539, 96, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131122, -29999999, 0, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 40, 131100, -30000000, 150, 131125, -29999998, 10,
    589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999, -29999998, 40, 0,
    0, 0, 131096, -29999997, -1, 65540, 97, 33,
    32, 65540, 98, 33, 6, 33, 33, 65540,
    98, 65539, 97, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_REBOUND1", -250000000,
    0, -250000000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 20, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 45,
    0, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999,
    -29999998, 45, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_JUMP1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 393307,
    (s32)btlevtcmd_JumpPartsSetting, -2, 2, 15, 0, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, 2, -30000000, -29999999, -29999998, 15, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_JUMP1", -250000000, 0, -250000000, 65545, 20,
    262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_togezo, 0, 196699, (s32)togezo_copy_status, -2,
    -29999997, 196699, (s32)btlevtcmd_GetBodyId, -29999997, -29999996, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    2, 50331648, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999997, -29999996, (s32)"TGZ_P_1", 393307, (s32)btlevtcmd_snd_se, -29999997, (s32)"SFX_ENM_TOGEZO_TURN2", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_SetRotate, -29999997, 0, 0, 0,
    327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 15, 0, 65541, 5,
    327771, (s32)btlevtcmd_AddRotate, -29999997, 0, 0, -36, 65545, 1,
    6, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, -29999996, (s32)"TGZ_S_1", 65541, 5,
    327771, (s32)btlevtcmd_AddRotate, -29999997, 0, 0, -36, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 0, 0, 65540,
    99, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 393307,
    (s32)btlevtcmd_GetPartsPos, -2, 2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 150, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 0,
    -229994880, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, 0,
    -29999998, 0, -1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 50331648,
    65545, 10, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

static s32 friend_event[] = {
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0,
    -29999990, 131096, -29999990, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_ATTACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_1",
    65545, 40, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_ATTACK2", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_2", 65545, 30,
    32, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 262235, (s32)btlevtcmd_OffPartsCounterAttribute,
    -2, 1, 1, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table,
    393307, (s32)btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"JGM_A_3", 65545, 2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_THROW2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 2, 50331648, 327771, (s32)btlevtcmd_GetPos, -2, -29999990, -29999989,
    -29999988, 131125, -29999989, 35, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2,
    -29999990, -29999989, -29999988, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2, 45, 0, -229999693, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000, -29999999, -29999998, 45, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_JUMP1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, 2,
    15, 0, -229999693, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 2, -30000000,
    -29999999, -29999998, 15, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_JUGEM_JUMP1",
    -250000000, 0, -250000000, 65545, 20, 262235, (s32)btlevtcmd_SpawnUnit, -29999997,
    (s32)entry_togezo, 0, 196699, (s32)togezo_copy_status, -2, -29999997, 196699, (s32)btlevtcmd_GetBodyId,
    -29999997, -29999996, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 50331648, 327771,
    (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, -29999996, (s32)"TGZ_P_1",
    393307, (s32)btlevtcmd_snd_se, -29999997, (s32)"SFX_ENM_TOGEZO_TURN2", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_SetRotate, -29999997, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -29999997,
    0, 15, 0, 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -29999997,
    0, 0, -36, 65545, 1, 6, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999997, -29999996, (s32)"TGZ_S_1", 65541, 5, 327771, (s32)btlevtcmd_AddRotate, -29999997,
    0, 0, -36, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotateOffset,
    -29999997, 0, 0, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65545, 10, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

