#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"

USER_FUNC(btlevtcmd_AddHomePos);
USER_FUNC(btlevtcmd_AddPos);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetPartsRotate);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPartsRotate);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_sub_random);
static USER_FUNC(killer_get_angle);
static USER_FUNC(killer_copy_status);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_CheckStatus[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_OnOffStatus[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetJumpSpeed[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_shake_w[];
extern s32 evt_eff[];
extern s32 evt_sub_get_dir[];
extern s32 unit_killer[];

__declspec(section ".data") u64 fd_killer_cannon_negone_one_374;
__declspec(section ".data") s32 fd_killer_cannon_neg_one_382[1];
__declspec(section ".data") s32 fd_killer_cannon___local_PI_383[1];
__declspec(section ".data") s32 fd_killer_cannon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_killer_cannon_one_negone_373;
__declspec(section ".data") s32 fd_killer_cannon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_killer_cannon_one_381[1];
__declspec(section ".data") u64 fd_killer_cannon_negone_one_360;
__declspec(section ".data") s32 fd_killer_cannon_neg_one_365[1];
__declspec(section ".data") s32 fd_killer_cannon___local_PI_366[1];
__declspec(section ".data") s32 fd_killer_cannon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_killer_cannon_one_negone_359;
__declspec(section ".data") s32 fd_killer_cannon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_killer_cannon_one_364[1];
BattleUnitKind unit_killer_cannon;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static BattleUnitKindPart parts[3];
static __declspec(section ".data") s32 entry_killer[12];
static PoseTableEntry pose_table[16];
static __declspec(section ".data") BattleDataEntry data_table[1];
static s32 init_event[63];
static __declspec(section ".data") s32 damage_event[10];
static s32 attack_event[738];
static s32 friend_event[244];
static s32 friend_event_sky[318];
static __declspec(section ".data") s32 wait_event[6];

static USER_FUNC(killer_copy_status) {
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

__declspec(section ".data") u64 fd_killer_cannon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_killer_cannon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_killer_cannon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_killer_cannon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_killer_cannon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_killer_cannon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_killer_cannon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_killer_cannon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_killer_cannon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_killer_cannon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_killer_cannon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_killer_cannon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_killer_cannon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_killer_cannon_one_364[] = {
    1065353216,
};

BattleUnitKind unit_killer_cannon = {
    90,
    "btl_un_killer_cannon",
    5,
    0,
    1,
    1,
    22,
    0,
    3,
    70,
    3,
    60,
    9999,
    52,
    38,
    5,
    38,
    0.0f,
    19.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    10.0f,
    26.0f,
    0.0f,
    0.0f,
    26.0f,
    24.7f,
    0.0f,
    -10.0f,
    19.0f,
    0.0f,
    52.0f,
    38.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KILLER_CANON_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    3,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 150, 100, 100, 100, 90, 100, 90, 100, 95, 50, 0, 15, 100, 50, 100, 100, 95};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 35, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 255, &defence, &defence_attr, 0x10000, 0, pose_table},
    {3, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 255, &defence, &defence_attr, 0x10000, 0, pose_table},
};

static __declspec(section ".data") s32 entry_killer[] = {
    (s32)unit_killer, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "KTA_N_1"},
    {2, "KTA_Y_1"},
    {9, "KTA_Y_1"},
    {5, "KTA_K_1"},
    {4, "KTA_X_1"},
    {3, "KTA_X_1"},
    {28, "KTA_S_1"},
    {29, "KTA_Q_1"},
    {30, "KTA_Q_1"},
    {31, "KTA_A_1"},
    {39, "KTA_D_1"},
    {56, "KTA_X_1"},
    {57, "KTA_X_1"},
    {50, "KTA_A_1"},
    {65, "KTA_T_1"},
    {69, "KTA_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    CALL(btlevtcmd_AddPos, -2, 20, 0, 0)
    CALL(btlevtcmd_AddHomePos, -2, 20, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("KTA_Z_3"))
    CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("KTA_Z_2"))
    CALL(btlevtcmd_OnPartsAttribute, -2, 2, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, -2, 2, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, -2, 3, 33554432)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(0), 15)
    ADD(LW(0), 0)
    ADD(LW(0), 10)
    ADD(LW(0), 20)
    ADD(LW(0), 0)
    ADD(LW(0), 10)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 15)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(PTR(friend_event))
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        GOTO(99)
    END_IF
    ADD(LW(0), 0)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 1)
                    CALL_CHILD(PTR(friend_event))
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        GOTO(99)
    END_IF
    ADD(LW(0), 10)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(PTR(friend_event))
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        GOTO(99)
    END_IF
    ADD(LW(0), 20)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(PTR(friend_event_sky))
                    CALL(btlevtcmd_GetPartsRotate, -2, 2, LW(5), LW(6), LW(11))
                    LOOP(0)
                        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                            BREAK_LOOP
                        END_IF
                        ADD(LW(11), 2)
                        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, LW(11))
                        WAIT_FRAMES(1)
                    END_LOOP
                    CALL(btlevtcmd_OffPartsAttribute, -2, 1, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, -2, 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        GOTO(99)
    END_IF
    ADD(LW(0), 0)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 1)
                    CALL_CHILD(PTR(friend_event_sky))
                    CALL(btlevtcmd_GetPartsRotate, -2, 2, LW(5), LW(6), LW(11))
                    LOOP(0)
                        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                            BREAK_LOOP
                        END_IF
                        ADD(LW(11), 2)
                        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, LW(11))
                        WAIT_FRAMES(1)
                    END_LOOP
                    CALL(btlevtcmd_OffPartsAttribute, -2, 1, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, -2, 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
                    GOTO(99)
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        GOTO(99)
    END_IF
    ADD(LW(0), 10)
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(15), 0)
        SET_VALUE(LW(14), 160)
        SET_VALUE(LW(13), 30)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, -2, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(PTR(friend_event_sky))
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(btlevtcmd_GetPartsRotate, -2, 2, LW(5), LW(6), LW(11))
        LOOP(0)
            IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                BREAK_LOOP
            END_IF
            ADD(LW(11), 2)
            CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, LW(11))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_OffPartsAttribute, -2, 1, 16777216)
        CALL(btlevtcmd_OnPartsAttribute, -2, 2, 16777216)
        CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 friend_event[] = {
    131096, -29999988, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_CANNON_CHARGE1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KTA_A_2A", 65545,
    10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KTA_Z_1", 65545, 10,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KTA_A_2A", 65545, 10, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KTA_Z_1", 65545, 10, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KTA_A_1", 65545, 40, 131096, -29999988,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_CANNON3", -250000000, 0, -250000000,
    32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_CANNON1", -250000000, 0, -250000000,
    33, 262235, (s32)btlevtcmd_CheckStatus, -2, 10, -29999995, 131097, -29999995,
    0, 327771, (s32)btlevtcmd_GetPos, -2, -29999993, -29999992, -29999991, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -29999993, 70, 131125, -29999991, 10, 983131,
    (s32)evt_eff, (s32)"", (s32)"kemuri_test", 18, -29999993, 50, -29999991, -229998464,
    0, 0, 0, 0, 0, 0, 0, 65540,
    10, 33, 262235, (s32)btlevtcmd_CheckStatus, -2, 11, -29999995, 131097,
    -29999995, 0, 327771, (s32)btlevtcmd_GetPos, -2, -29999993, -29999992, -29999991,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999993, 28, 131125, -29999991, 10,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 18, -29999993, 15, -29999991,
    -229999488, 0, 0, 0, 0, 0, 0, 0,
    65540, 10, 33, 327771, (s32)btlevtcmd_GetPos, -2, -29999993, -29999992,
    -29999991, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999993, 40, 131125, -29999991,
    10, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 18, -29999993, 30,
    -29999991, -229998976, 0, 0, 0, 0, 0, 0,
    0, 65540, 10, 65539, 10, 393307, (s32)evt_btl_camera_shake_w, 0,
    5, 0, 20, 0, 327771, (s32)btlevtcmd_GetPos, -2, -29999993,
    -29999992, -29999991, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_killer, 0, 196699,
    (s32)killer_copy_status, -2, -29999997, 327771, (s32)btlevtcmd_SetPos, -29999997, -29999993, 10,
    -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -29999997, 0, 196699, (s32)btlevtcmd_SetJumpSpeed, -29999997,
    0, 458843, (s32)btlevtcmd_JumpPosition, -29999997, -30000000, 10, -29999998, -229992832,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, 10, -29999998, 131096,
    -29999988, 1, 393307, (s32)btlevtcmd_OnOffStatus, -29999997, 16, 1, 1,
    1, 33, 2, 1,
};

static s32 friend_event_sky[] = {
    327771, (s32)btlevtcmd_GetPos, -2, -29999993, -29999992, -29999991, 393307, (s32)evt_sub_get_dir,
    -29999993, -29999992, -30000000, 40, -29999990, 393307, (s32)killer_get_angle, -29999993,
    -29999992, -30000000, 40, -29999990, 393307, (s32)btlevtcmd_GetPartsRotate, -2, 2,
    -29999995, -29999994, -29999989, 65541, 0, 131099, -29999989, 0,
    7, 33, 131100, -29999989, -29999990, 7, 33, 131126,
    -29999989, 2, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 0,
    -29999989, 65545, 1, 6, 131096, -29999988, 1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KILLER_CANNON_CHARGE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 2, (s32)"KTA_A_3A", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    2, (s32)"KTA_Z_3", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2,
    (s32)"KTA_A_3A", 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"KTA_Z_3",
    65545, 10, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"KTA_A_3",
    65545, 40, 131096, -29999988, 1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_KILLER_CANNON4", -250000000, 0, -250000000, 32, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_KILLER_CANNON2", -250000000, 0, -250000000, 33, 262235, (s32)btlevtcmd_CheckStatus, -2,
    10, -29999995, 131097, -29999995, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -29999993, -29999992, -29999991, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999993, 60,
    131125, -29999991, 10, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 18,
    -29999993, 75, -29999991, -229998464, 0, 0, 0, 0,
    0, 0, 0, 65540, 10, 33, 262235, (s32)btlevtcmd_CheckStatus,
    -2, 11, -29999995, 131097, -29999995, 0, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999993, -29999992, -29999991, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -29999993,
    28, 131125, -29999991, 10, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test",
    18, -29999993, 20, -29999991, -229999488, 0, 0, 0,
    0, 0, 0, 0, 65540, 10, 33, 327771,
    (s32)btlevtcmd_GetPos, -2, -29999993, -29999992, -29999991, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -29999993, 40, 131125, -29999991, 10, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 18, -29999993, 38, -29999991, -229998976, 0, 0,
    0, 0, 0, 0, 0, 65540, 10, 65539,
    10, 393307, (s32)evt_btl_camera_shake_w, 0, 5, 0, 20, 0,
    262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_killer, 0, 196699, (s32)killer_copy_status, -2,
    -29999997, 196699, (s32)btlevtcmd_GetBodyId, -29999997, -29999996, 327771, (s32)btlevtcmd_SetPos, -29999997,
    -29999993, 10, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -29999997, -29999996, 0,
    0, -29999990, 196699, (s32)btlevtcmd_SetFallAccel, -29999997, 0, 196699, (s32)btlevtcmd_SetJumpSpeed,
    -29999997, 0, 458843, (s32)btlevtcmd_JumpPosition, -29999997, -30000000, 40, -29999998,
    -229992832, -1, 393307, (s32)btlevtcmd_SetPartsRotate, -29999997, -29999996, 0, 0,
    0, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, 40, -29999998, 131096,
    -29999988, 1, 393307, (s32)btlevtcmd_OnOffStatus, -29999997, 16, 1, 1,
    1, 33, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999997, -29999996, 4194304, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -29999997, -29999996, 2097152, 2, 1,
};

double atan(double x);

static USER_FUNC(killer_get_angle) {
    s32* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 y1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 y2 = evtGetFloat(event, args[3]);
    f32 angle = atan((y2 - y1) / (x2 - x1));

    evtSetFloat(event, args[4], 360.0f * angle / 6.283184f);
    return EVT_RETURN_DONE;
}

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

