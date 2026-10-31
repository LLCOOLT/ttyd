// Bill Blaster (killer_cannon): battle unit used in Pirate's Grotto.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "dou.h"

static USER_FUNC(killer_get_angle);
static USER_FUNC(killer_copy_status);

BattleUnitKind unit_killer_cannon;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[3];
static BattleUnitSetup entry_killer;
static PoseTableEntry pose_table[16];
static BattleDataEntry data_table[1];
static EvtWord init_event[63];
static EvtWord damage_event[10];
static EvtWord attack_event[738];
static EvtWord friend_event[244];
static EvtWord friend_event_sky[318];
static EvtWord wait_event[6];

/**
 * Script helper: copies the size-change state (turns and strength) from the Bill Blaster args[0] to the Bullet
 * Bill args[1] it has just spawned; HP is not copied.
 */
static USER_FUNC(killer_copy_status) {
    EvtWord* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->sizeChangeTurns = unit1->sizeChangeTurns;
    unit2->sizeChangeStrength = unit1->sizeChangeStrength;
    return EVT_RETURN_DONE;
}

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
#if VERSION <= VERSION_DEMO_US
    0.0f,
    0.0f,
#else
    20.0f,
    10.0f,
#endif
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

static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {0, 0, 0, 0, 0, 150, 100, 50, 100, 50, 100, 50, 100, 50, 50, 0, 15, 100, 50, 100, 100, 95};
#else
static StatusVulnerability regist = {0, 0, 0, 0, 0, 150, 100, 100, 100, 90, 100, 90, 100, 95, 50, 0, 15, 100, 50, 100, 100, 95};
#endif

static BattleUnitKindPart parts[] = {
    {1, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 35, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 255, &defence, &defence_attr, 0x10000, 0, pose_table},
    {3, "btl_un_killer_cannon", "c_killtai", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 255, &defence, &defence_attr, 0x10000, 0, pose_table},
};

static BattleUnitSetup entry_killer = {
    &unit_killer, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
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
    {BTL_POSE_TALK, "KTA_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KTA_S_1"},
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Init event of the Bombshell Bill Blaster: installs its wait, attack, damage and confusion events,
 * shifts it 20 units right, sets the poses of the two upper barrel parts (KTA_Z_3 and KTA_Z_2)
 * and sets attributes 0x1000000 and 0x2000000 on them (Guess: hidden and untargetable while retracted).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 20, 0, 0)
    CALL(btlevtcmd_AddHomePos, BTL_UNIT_SELF, 20, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_Z_3"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KTA_Z_2"))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 33554432)
    RETURN
EVT_END()

/** Guess: damage event of a sword: runs the default damage reaction. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Attack event of the Bombshell Bill Blaster: it never attacks directly,
 * it fires a Bombshell Bill into free space beside it.
 * It can use an item; otherwise it draws a number and picks one of the weighted launches:
 * from the front barrel (friend_event), or from the upper barrel (friend_event_sky) after raising it;
 * LW(12) = 1 selects the charged shot with extra charging flashes.
 * If no free space is found on either side nothing is launched.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
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
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(friend_event)
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
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 1)
                    CALL_CHILD(friend_event)
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
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(friend_event)
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
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(friend_event_sky)
                    CALL(btlevtcmd_GetPartsRotate, BTL_UNIT_SELF, 2, LW(5), LW(6), LW(11))
                    LOOP(0)
                        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                            BREAK_LOOP
                        END_IF
                        ADD(LW(11), 2)
                        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, LW(11))
                        WAIT_FRAMES(1)
                    END_LOOP
                    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
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
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 1)
                    CALL_CHILD(friend_event_sky)
                    CALL(btlevtcmd_GetPartsRotate, BTL_UNIT_SELF, 2, LW(5), LW(6), LW(11))
                    LOOP(0)
                        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                            BREAK_LOOP
                        END_IF
                        ADD(LW(11), 2)
                        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, LW(11))
                        WAIT_FRAMES(1)
                    END_LOOP
                    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
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
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(14))
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), LW(5))
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                ADD(LW(2), LW(13))
                IF_INT_EQUAL(LW(3), -1)
                    SET_VALUE(LW(12), 0)
                    CALL_CHILD(friend_event_sky)
                END_IF
            END_IF
            ADD(LW(15), 1)
            SUBTRACT(LW(14), 40)
            SUBTRACT(LW(13), 10)
            IF_INT_GREATER_OR_EQUAL(LW(15), 3)
                BREAK_LOOP
            END_IF
        END_LOOP
        CALL(btlevtcmd_GetPartsRotate, BTL_UNIT_SELF, 2, LW(5), LW(6), LW(11))
        LOOP(0)
            IF_INT_GREATER_OR_EQUAL(LW(11), 0)
                BREAK_LOOP
            END_IF
            ADD(LW(11), 2)
            CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, LW(11))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 16777216)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Launches a Bombshell Bill (entry_killer) from the front barrel:
 * the barrel animation and cannon sound play, a smoke puff appears at the muzzle (its size depends on statuses
 * 10 and 11, Guess: the size statuses), the camera shakes,
 * the new unit copies the cannon's status (killer_copy_status),
 * flies to the free spot found by the caller and takes that as its home.
 * With LW(12) = 1 it charges first and sets status 16 on the new Bill.
 */
static EVT_BEGIN(friend_event)
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KTA_A_2A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KTA_Z_1"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KTA_A_2A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KTA_Z_1"))
        WAIT_FRAMES(10)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KTA_A_1"))
    WAIT_FRAMES(40)
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 70)
        ADD(LW(9), 10)
        CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 50, LW(9), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 28)
        ADD(LW(9), 10)
        CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 15, LW(9), FLOAT(0.5f), 0, 0, 0, 0, 0, 0, 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 40)
    ADD(LW(9), 10)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 30, LW(9), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    GOTO(10)
    LABEL(10)
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 20, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_killer), 0)
    CALL(killer_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_SetPos, LW(3), LW(7), 10, LW(2))
    CALL(btlevtcmd_SetFallAccel, LW(3), 0)
    CALL(btlevtcmd_SetJumpSpeed, LW(3), 0)
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), 10, LW(2), FLOAT(7.0f), -1)
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), 10, LW(2))
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_OnOffStatus, LW(3), 16, 1, 1, 1)
    END_IF
    RETURN
EVT_END()

/**
 * Launches a Bombshell Bill (entry_killer) from the raised upper barrel (part 2):
 * the barrel turns to aim at the free spot (killer_get_angle),
 * then it fires like friend_event with a slightly different smoke and sound,
 * and the new Bill flies with the barrel's angle at height 40 and gets attributes 0x400000
 * and 0x200000 on its body.
 */
static EVT_BEGIN(friend_event_sky)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
    CALL(evt_sub_get_dir, LW(7), LW(8), LW(0), 40, LW(10))
    CALL(killer_get_angle, LW(7), LW(8), LW(0), 40, LW(10))
    CALL(btlevtcmd_GetPartsRotate, BTL_UNIT_SELF, 2, LW(5), LW(6), LW(11))
    LOOP(0)
        IF_INT_GREATER(LW(11), 0)
            BREAK_LOOP
        END_IF
        IF_INT_LESS_OR_EQUAL(LW(11), LW(10))
            BREAK_LOOP
        END_IF
        SUBTRACT(LW(11), 2)
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, 0, 0, LW(11))
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_A_3A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_Z_3"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_A_3A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_Z_3"))
        WAIT_FRAMES(10)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KTA_A_3"))
    WAIT_FRAMES(40)
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KILLER_CANNON2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 60)
        ADD(LW(9), 10)
        CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 75, LW(9), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 28)
        ADD(LW(9), 10)
        CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 20, LW(9), FLOAT(0.5f), 0, 0, 0, 0, 0, 0, 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(7), LW(8), LW(9))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(7), 40)
    ADD(LW(9), 10)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(7), 38, LW(9), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    GOTO(10)
    LABEL(10)
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 20, 0)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_killer), 0)
    CALL(killer_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_SetPos, LW(3), LW(7), 10, LW(2))
    CALL(btlevtcmd_SetPartsRotate, LW(3), LW(4), 0, 0, LW(10))
    CALL(btlevtcmd_SetFallAccel, LW(3), 0)
    CALL(btlevtcmd_SetJumpSpeed, LW(3), 0)
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), 40, LW(2), FLOAT(7.0f), -1)
    CALL(btlevtcmd_SetPartsRotate, LW(3), LW(4), 0, 0, 0)
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), 40, LW(2))
    IF_INT_EQUAL(LW(12), 1)
        CALL(btlevtcmd_OnOffStatus, LW(3), 16, 1, 1, 1)
    END_IF
    CALL(btlevtcmd_OnPartsAttribute, LW(3), LW(4), 4194304)
    CALL(btlevtcmd_OnPartsAttribute, LW(3), LW(4), 2097152)
    RETURN
EVT_END()

double atan(double x);

/**
 * Script helper: args[0..3] are two points (x1, y1, x2, y2);
 * stores the angle in degrees of the line between them, from atan((y2 - y1) / (x2 - x1)), in args[4].
 * Used to tilt the Bullet Bill fired from the Bill Blaster in the sky formation.
 */
static USER_FUNC(killer_get_angle) {
    EvtWord* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 y1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 y2 = evtGetFloat(event, args[3]);
    f32 angle = atan((y2 - y1) / (x2 - x1));

    evtSetFloat(event, args[4], 360.0f * angle / 6.283184f);
    return EVT_RETURN_DONE;
}

/** Guess: wait (idle) event of Cortez: sets the idle pose from the current mode's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
