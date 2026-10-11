#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "system.h"

USER_FUNC(btlevtcmd_AddUnitWork);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_AttackDeclareAll);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetPartsWork);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPartsWork);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_sub_random);
USER_FUNC(fire_bros_nagemakuri_set_target);
void fire_bros_get_next_target(s32* unitIdx, s32* partIdx);
void fire_bros_get_target(s32* unitIdx, s32* partIdx);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPartsRotate[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_JumpPartsPosition[];
extern s32 btlevtcmd_JumpPartsSetting[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetPartsRotate[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_snd_se[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_fire_bros_negone_one_374;
__declspec(section ".data") s32 fd_fire_bros_neg_one_382[1];
__declspec(section ".data") s32 fd_fire_bros___local_PI_383[1];
__declspec(section ".data") s32 fd_fire_bros___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_fire_bros_one_negone_373;
__declspec(section ".data") s32 fd_fire_bros___local_PIO2_384[1];
__declspec(section ".data") s32 fd_fire_bros_one_381[1];
__declspec(section ".data") u64 fd_fire_bros_negone_one_360;
__declspec(section ".data") s32 fd_fire_bros_neg_one_365[1];
__declspec(section ".data") s32 fd_fire_bros___local_PI_366[1];
__declspec(section ".data") s32 fd_fire_bros___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_fire_bros_one_negone_359;
__declspec(section ".data") s32 fd_fire_bros___local_PIO2_367[1];
__declspec(section ".data") s32 fd_fire_bros_one_364[1];
BattleUnitKind unit_fire_bros;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[7];
s32 weapon_fire_bros_attack[48];
s32 weapon_fire_bros_renzoku_attack[48];
s32 weapon_fire_bros_nagemakuri_attack[48];
static s32 init_event[21];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[92];
static s32 damage_check_sub[167];
static __declspec(section ".data") s32 damage_check_no_last[7];
static s32 damage_check_last[113];
s32 fire_move_event[605];
static s32 normal_attack_event[125];
static s32 renzoku_attack_event[141];
static s32 nagemakuri_attack_event[316];
s32 nagemakuri_judge_last_attack_event[73];
static __declspec(section ".data") s32 wait_event[6];

#pragma dont_inline on
void fire_bros_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void fire_bros_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}
#pragma dont_inline reset

USER_FUNC(fire_bros_nagemakuri_set_target) {
    s32* args = event->args;
    s32 unitIdx[20];
    s32 partIdx[20];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    fire_bros_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        fire_bros_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_fire_bros_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_fire_bros_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_fire_bros___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_fire_bros___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_fire_bros_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_fire_bros___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_fire_bros_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_fire_bros_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_fire_bros_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_fire_bros___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_fire_bros___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_fire_bros_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_fire_bros___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_fire_bros_one_364[] = {
    1065353216,
};

BattleUnitKind unit_fire_bros = {
    58,
    "btl_un_fire_bros",
    7,
    0,
    1,
    1,
    20,
    0,
    2,
    70,
    2,
    50,
    9999,
    36,
    44,
    3,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    10.0f,
    28.0f,
    0.0f,
    0.0f,
    22.0f,
    0.0f,
    36.0f,
    44.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_FIREB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    7,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {80, 80, 70, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 95, 80, 70, 60, 100, 80, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "BRO_N_1"},
    {2, "BRO_Y_1"},
    {9, "BRO_Y_1"},
    {5, "BRO_K_1"},
    {4, "BRO_X_1"},
    {3, "BRO_X_1"},
    {27, "BRO_D_1"},
    {28, "BRO_S_1"},
    {29, "BRO_Q_1"},
    {30, "BRO_Q_1"},
    {31, "BRO_S_1"},
    {39, "BRO_D_1"},
    {42, "BRO_R_1"},
    {40, "BRO_W_1"},
    {56, "BRO_X_1"},
    {57, "BRO_X_1"},
    {65, "BRO_T_1"},
    {69, "BRO_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {7, "btl_un_fire_bros", "c_burosu_f", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

s32 weapon_fire_bros_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 16777986, 0, 7, 2047, -2147475456,
    0, 0, 0, 30, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_fire_bros_renzoku_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 16777986, 0, 7, 2047, -2147475456,
    0, 0, 0, 30, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_fire_bros_nagemakuri_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 7, 2047, -2147483648,
    0, 0, 0, 30, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetHp, -2, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 3)
        SET_VALUE(LW(0), 50)
        ADD(LW(0), 50)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 30)
            CALL_CHILD(PTR(renzoku_attack_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(nagemakuri_attack_event))
        GOTO(99)
        ELSE
        SET_VALUE(LW(0), 70)
        ADD(LW(0), 30)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 70)
            CALL_CHILD(PTR(normal_attack_event))
            GOTO(99)
        END_IF
        CALL_CHILD(PTR(renzoku_attack_event))
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_sub)
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(6), 0, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(99)
    LABEL(91)
    SET_VALUE(LW(0), 1)
    IF_INT_EQUAL(LW(6), PTR(weapon_fire_bros_renzoku_attack))
        CALL(btlevtcmd_SetPartsWork, -2, 2, 10, 1)
    END_IF
    IF_INT_EQUAL(LW(8), 1)
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(0)
            SET_VALUE(LW(12), 2)
            LOOP(0)
                CALL(btlevtcmd_GetPartsWork, -2, LW(12), LW(13), LW(1))
                CALL(btlevtcmd_GetPartsWork, -2, LW(12), LW(14), LW(2))
                IF_INT_EQUAL(LW(3), LW(1))
                    IF_INT_EQUAL(LW(4), LW(2))
                        ADD(LW(13), 10)
                        CALL(btlevtcmd_SetPartsWork, -2, LW(12), LW(13), 1)
                        GOTO(98)
                    END_IF
                END_IF
                ADD(LW(12), 1)
                IF_INT_GREATER(LW(12), 7)
                    BREAK_LOOP
                END_IF
            END_LOOP
            ADD(LW(13), 1)
            ADD(LW(14), 1)
        END_LOOP
    END_IF
    LABEL(98)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
    IF_INT_EQUAL(LW(7), 1)
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 256, LW(5))
        ELSE
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 0, LW(5))
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_check_no_last)
    SET_VALUE(LW(7), 0)
    CALL_CHILD(PTR(damage_check_sub))
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_last)
    IF_INT_EQUAL(LW(6), PTR(weapon_fire_bros_renzoku_attack))
        CALL(btlevtcmd_GetPartsWork, -2, 2, 10, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            SET_VALUE(LW(0), 1)
            ELSE
            SET_VALUE(LW(0), 0)
        END_IF
        GOTO(10)
    END_IF
    IF_INT_EQUAL(LW(8), 1)
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(0)
            SET_VALUE(LW(12), 2)
            LOOP(0)
                CALL(btlevtcmd_GetPartsWork, -2, LW(12), LW(13), LW(1))
                CALL(btlevtcmd_GetPartsWork, -2, LW(12), LW(14), LW(2))
                IF_INT_EQUAL(LW(3), LW(1))
                    IF_INT_EQUAL(LW(4), LW(2))
                        ADD(LW(13), 10)
                        CALL(btlevtcmd_GetPartsWork, -2, LW(12), LW(13), LW(0))
                        GOTO(10)
                    END_IF
                END_IF
                ADD(LW(12), 1)
                IF_INT_GREATER(LW(12), 7)
                    BREAK_LOOP
                END_IF
            END_LOOP
            ADD(LW(13), 1)
            ADD(LW(14), 1)
        END_LOOP
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(6))
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(6), 256, LW(5))
        ELSE
        SET_VALUE(LW(7), 1)
        CALL_CHILD(PTR(damage_check_sub))
    END_IF
    RETURN
EVT_END()

s32 fire_move_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, -29999985, (s32)"BRO_A_1B", 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999985,
    15, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999999, 15, 393307, (s32)btlevtcmd_SetPartsPos, -2, -29999985, -30000000,
    -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, -29999985, 0, 0,
    -180, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, -29999985, 0, 0, 0,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    -29999985, 33554432, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999991, -29999990,
    -29999989, 131126, -29999991, -30000000, 131122, -29999990, 0, 110,
    65541, 0, 65545, 1, 393307, (s32)btlevtcmd_GetPartsPos, -2, -29999985,
    -30000000, -29999988, -29999987, 65570, -29999990, 65572, 0, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999989, -29999988, -29999987, 131101, -29999991,
    0, 131100, -30000000, -29999989, 48, 33, 32, 131101,
    -30000000, -29999989, 48, 33, 33, 131096, -29999986, 0,
    65630, (s32)damage_check_no_last, 32, 65630, (s32)damage_check_last, 33, 131096, -30000000,
    1, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, -29999985, 33554432, 131122, -29999990, 2, 32, 131122,
    -29999990, 1, 33, 46, 65572, 1, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999985, -29999989, -29999988, -29999987, 131101, -29999989, 250,
    262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    -29999985, 33554432, 131122, -29999990, 2, 33, 131100, -29999989,
    -250, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, -29999985, 33554432, 131122, -29999990, 2, 33, 46,
    65572, 2, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999985, 15, 1,
    7, 46, 49, 6, 112, 110, 65541, 0,
    65545, 1, 393307, (s32)btlevtcmd_AddPartsRotate, -2, -29999985, 0, 0,
    16, 6, 112, 196699, (s32)evt_sub_random, 1, -29999989, 131096,
    -29999989, 0, 393307, (s32)btlevtcmd_GetPartsPos, -2, -29999985, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, -29999985, 0, 6, -229999386,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2,
    -29999985, -30000000, 0, -29999998, 0, -1, 327771, (s32)btlevtcmd_GetPartsWork,
    -2, -29999985, 15, -29999990, 131096, -29999990, 1, 65540,
    99, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, -29999985, -30000000, 0, -29999998, 0, -1, 327771,
    (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15, -29999990, 131096, -29999990, 1,
    65540, 99, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 100, 524379,
    (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0, -29999998, 0, -1,
    327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15, -29999990, 131096, -29999990,
    1, 65540, 99, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 100,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0, -29999998, 0,
    -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15, -29999990, 131096,
    -29999990, 1, 65540, 99, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0, -29999998,
    0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15, -29999990,
    131096, -29999990, 1, 65540, 99, 33, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 32, 393307, (s32)btlevtcmd_GetPartsPos,
    -2, -29999985, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    -29999985, 0, 5, -229999386, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0, -29999998,
    0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15, -29999990,
    131096, -29999990, 1, 65540, 99, 33, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0,
    -29999998, 0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15,
    -29999990, 131096, -29999990, 1, 65540, 99, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000,
    0, -29999998, 0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985,
    15, -29999990, 131096, -29999990, 1, 65540, 99, 33,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 131096,
    -29999990, 2, 65540, 99, 33, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000, 0,
    -29999998, 0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985, 15,
    -29999990, 131096, -29999990, 1, 65540, 99, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 100, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -30000000,
    0, -29999998, 0, -1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985,
    15, -29999990, 131096, -29999990, 1, 65540, 99, 33,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FIREB_ATTACK2", -250000000, 0, -250000000, 33,
    65539, 99, 65545, 6, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985,
    16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 33554432, 262235, (s32)btlevtcmd_AddUnitWork,
    -2, 1, 1, 2, 1,
};

static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_fire_bros_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_fire_bros_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_fire_bros_attack))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_fire_bros_attack))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_1A"))
    WAIT_FRAMES(40)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 1)
    SET_VALUE(LW(6), PTR(weapon_fire_bros_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(PTR(fire_move_event))
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(20)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(renzoku_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_fire_bros_renzoku_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_fire_bros_renzoku_attack))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetPartsWork, -2, 2, 10, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(20)
    SET_VALUE(LW(15), 2)
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(6), PTR(weapon_fire_bros_renzoku_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(PTR(fire_move_event))
    WAIT_FRAMES(12)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
    WAIT_FRAMES(20)
    SET_VALUE(LW(15), 3)
    SET_VALUE(LW(14), 1)
    SET_VALUE(LW(6), PTR(weapon_fire_bros_renzoku_attack))
    SET_VALUE(LW(8), 0)
    SPAWN_EVENT(PTR(fire_move_event))
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 2)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(20)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(nagemakuri_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(weapon_fire_bros_nagemakuri_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(weapon_fire_bros_nagemakuri_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(weapon_fire_bros_nagemakuri_attack))
    CALL(btlevtcmd_AttackDeclareAll, -2)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, PTR(weapon_fire_bros_nagemakuri_attack))
    SET_VALUE(LW(10), 2)
    LOOP(0)
        IF_INT_GREATER(LW(10), 7)
            BREAK_LOOP
        END_IF
        CALL(fire_bros_nagemakuri_set_target, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 0, LW(0))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 1, LW(2))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 2, LW(4))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 3, LW(6))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 4, LW(8))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 5, LW(1))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 6, LW(3))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 7, LW(5))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 8, LW(7))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 9, LW(9))
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 10, 0)
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 11, 0)
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 12, 0)
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 13, 0)
        CALL(btlevtcmd_SetPartsWork, -2, LW(10), 14, 0)
        ADD(LW(10), 1)
    END_LOOP
    WAIT_FRAMES(12)
    SET_VALUE(LW(10), 0)
    SET_VALUE(LW(11), 5)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    LOOP(0)
        SET_VALUE(LW(15), 2)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(1))
            IF_INT_GREATER_OR_EQUAL(LW(1), 6)
                LOOP(0)
                    WAIT_FRAMES(1)
                    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(1))
                    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(2))
                    SUBTRACT(LW(1), 6)
                    IF_INT_GREATER(LW(2), LW(1))
                        WAIT_FRAMES(3)
                        BREAK_LOOP
                    END_IF
                END_LOOP
            END_IF
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("BRO_A_2A"))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_GetPartsWork, -2, LW(15), LW(10), LW(3))
            CALL(btlevtcmd_GetPartsWork, -2, LW(15), LW(11), LW(4))
            CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(14))
            CALL(btlevtcmd_ChangeFaceDirection, -2, LW(14))
            CALL_CHILD(PTR(nagemakuri_judge_last_attack_event))
            SET_VALUE(LW(6), PTR(weapon_fire_bros_nagemakuri_attack))
            SET_VALUE(LW(8), 1)
            SPAWN_EVENT(PTR(fire_move_event))
            CALL(btlevtcmd_AddUnitWork, -2, 0, 1)
            WAIT_FRAMES(15)
            ADD(LW(15), 1)
            IF_INT_GREATER(LW(15), 7)
                BREAK_LOOP
            END_IF
        END_LOOP
        ADD(LW(10), 1)
        ADD(LW(11), 1)
        IF_INT_GREATER(LW(10), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    LOOP(0)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 6)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

EVT_BEGIN(nagemakuri_judge_last_attack_event)
    SET_VALUE(LW(0), LW(10))
    SET_VALUE(LW(1), LW(11))
    SET_VALUE(LW(13), LW(15))
    ADD(LW(13), 1)
    LOOP(0)
        IF_INT_GREATER(LW(0), 0)
            SET_VALUE(LW(14), 1)
            GOTO(99)
        END_IF
        LOOP(0)
            IF_INT_GREATER(LW(13), 7)
                SET_VALUE(LW(13), 2)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_GetPartsWork, -2, LW(13), LW(0), LW(5))
            CALL(btlevtcmd_GetPartsWork, -2, LW(13), LW(1), LW(6))
            IF_INT_EQUAL(LW(3), LW(5))
                IF_INT_EQUAL(LW(4), LW(6))
                    SET_VALUE(LW(14), 0)
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(13), 1)
        END_LOOP
        ADD(LW(0), 1)
        ADD(LW(1), 1)
    END_LOOP
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

