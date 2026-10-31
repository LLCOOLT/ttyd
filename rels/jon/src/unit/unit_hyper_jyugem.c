// Pit of 100 Trials battle unit: the Dark Lakitu (`hyper_jyugem`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"

static USER_FUNC(togezo_copy_status);
extern BattleUnitKind unit_hyper_togezo;

BattleUnitKind unit_hyper_jyugem;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_hold[17];
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
static BattleWeapon weapon_jyugem_attack;
static BattleWeapon weapon_jyugem_charge;
static BattleUnitSetup entry_togezo;
static EvtWord init_event[40];
static EvtWord damage_event[322];
static EvtWord unison_phase_event[139];
static EvtWord avoid_counter_thorn_head_event[61];
static EvtWord dmg_first_attack_pos_event[19];
static EvtWord attack_event[221];
static EvtWord normal_attack_event[585];
static EvtWord friend_event[263];
static EvtWord charge_event[102];
static EvtWord wait_event[6];

BattleUnitKind unit_hyper_jyugem = {
    159,
    "btl_un_hyper_jyugem",
    13,
    0,
    1,
    1,
    26,
    1,
    2,
    70,
    1,
    50,
    9999,
    32,
    30,
    4,
    42,
    0.0f,
    15.0f,
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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {60, 70, 80, 100, 60, 100, 100, 50, 100, 60, 100, 60, 100, 60, 60, 70, 80, 100, 60, 100, 100, 50};
#else
static StatusVulnerability regist = {60, 70, 95, 100, 60, 100, 100, 80, 100, 85, 100, 85, 100, 90, 60, 70, 80, 100, 60, 100, 100, 50};
#endif

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
    {BTL_POSE_TALK, "JGM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "JGM_S_1"},
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
    {BTL_POSE_TALK, "JGM_S_2"},
    {BTL_POSE_STAY_DEFAULT, "JGM_S_2"},
};

static BattleDataEntry data_table[] = {
    {37, avoid_counter_thorn_head_event},
    {48, dmg_first_attack_pos_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_hyper_jyugem", "c_jugemu_b", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, "ハイパーパイポ", "c_jugemu_b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static BattleWeapon weapon_jyugem_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_jyugem_charge = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    5, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleUnitSetup entry_togezo = {
    &unit_hyper_togezo, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Init script of the Dark Lakitu: registers its wait, unison-phase, attack, damage and confusion handlers,
 * clears unit work 0 (set while it holds a Spiny egg) and unit work 2 (charged flag),
 * and puts its second part (the egg) in the JGM_P_1 pose.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("JGM_P_1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage script of the Dark Lakitu. While it is not holding an egg it just takes the default damage.
 * While it is holding one (unit work 0 set), a hit that damages it,
 * or that applies one of a set of status effects (Guess: the ones that stun or disable it),
 * makes it drop the egg: the egg part is thrown away behind it,
 * the holding state and counter attribute are cleared and its pose table is restored
 * before the default damage runs.
 * Other status-inflicting damage codes (22, 30, 31, 38, 39 and 41) drop the egg too, with a shorter toss.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(btldefaultevt_Damage)
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
                CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
                CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                ADD(LW(1), 35)
                CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
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
            CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
            CALL_CHILD(btldefaultevt_Damage)
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
                    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                    ADD(LW(1), 35)
                    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_JumpPartsSetting, LW(10), 2, 30, 0, FLOAT(0.099609375f))
                    CALL(btlevtcmd_JumpPartsPosition, LW(10), 2, LW(0), LW(1), LW(2), 30, -1)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 16777216)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, 33554432)
                END_INLINE_EVENT
            END_IF
            LABEL(90)
            CALL_CHILD(btldefaultevt_Damage)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Before the player's phase, on every turn but the first, if the Dark Lakitu can act and is not in status 27, 3,
 * 5 or 6 (Guess: the ailments that disable it), it has a 50 percent chance to pick up an egg:
 * it plays JGM_A_1 and A_2 with the hold sounds, sets unit work 0 and counter attribute 1 on part 1,
 * switches to the holding pose table and raises its hit offset by 20.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    SET_VALUE(LW(15), 0)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 3, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 5, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 6, LW(14))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        GOTO(99)
    END_IF
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_LESS(LW(0), 50)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_1"))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_HOLD1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_2"))
        WAIT_FRAMES(30)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_hold))
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 20, 0)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Plays the "toge_flush" spark effect over the Dark Lakitu 30 frames after it is hit,
 * at a height that depends on its size statuses 10 and 11 (Guess: the big and small size changes).
 */
static EVT_BEGIN(avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 10, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 11, LW(3))
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

/** Data event 48 of the Dark Lakitu: after a first strike it is set to y 10 and waits for the attack to end. */
static EVT_BEGIN(dmg_first_attack_pos_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Attack script of the Dark Lakitu.
 * After an item check it draws lots: 40 against 90 (70 after the first turn) between throwing an egg that
 * hatches a Spiny into a free spot (friend_event, trying the space to its right first and then to its left)
 * and an attack. A charged Dark Lakitu (unit work 2 set) always throws an egg.
 * Otherwise the attack is drawn from the plain egg throw,
 * the Spiny-hatching throw and charging up (charge_event) in the ratio 30:30:30 on the first turn
 * and 30:30:10 afterwards.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_DrawLots, LW(0), 2, 40, 90)
    ELSE
        CALL(btlevtcmd_DrawLots, LW(0), 2, 40, 70)
    END_IF
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 0)
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
            SET_VALUE(LW(4), LW(0))
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
            MULTIPLY(LW(4), LW(5))
            IF_INT_LESS(LW(4), 0)
                SUBTRACT(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    CALL_CHILD(friend_event)
                    GOTO(99)
                END_IF
            ELSE
                GOTO(9)
            END_IF
        END_LOOP
        LABEL(9)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(1), 0)
        LOOP(0)
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
            IF_INT_LESS_OR_EQUAL(LW(0), 150)
                ADD(LW(2), 10)
                CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                IF_INT_EQUAL(LW(3), -1)
                    CALL_CHILD(friend_event)
                    GOTO(99)
                END_IF
            ELSE
                GOTO(10)
            END_IF
        END_LOOP
        LABEL(10)
    END_SWITCH
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_DrawLots, LW(0), 3, 30, 30, 30)
    ELSE
        CALL(btlevtcmd_DrawLots, LW(0), 3, 30, 30, 10)
    END_IF
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
        CALL_CHILD(normal_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
        CALL_CHILD(normal_attack_event)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 1)
        SET_VALUE(LW(9), PTR(&weapon_jyugem_charge))
        CALL_CHILD(charge_event)
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Lakitu's egg throw: if it is not already holding an egg it takes one (JGM_A_1 and A_2),
 * then throws it (SFX_ENM_JUGEM_THROW1) in an arc at the target and the target takes the damage.
 * If unit work 1 is set and the egg hits a target with damage code 262144 (Guess: a target that can be hit) the
 * egg also bounces to a free spot and hatches a Spiny there (togezo_copy_status copies its size status).
 * Otherwise the egg hops and lands behind the target and is picked up again.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_jyugem_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_1"))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_2"))
        WAIT_FRAMES(30)
    ELSE
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_3"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 35)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_THROW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 45, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 45, -1)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_jyugem_attack), 256, LW(5))
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
    CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_jyugem_attack), 256, LW(5))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_CheckDamageCode, LW(3), 262144, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 0)
            LOOP(0)
                CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
                SET_VALUE(LW(4), LW(0))
                CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
                MULTIPLY(LW(4), LW(5))
                IF_INT_LESS(LW(4), 0)
                    SUBTRACT(LW(2), 10)
                    CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                    IF_INT_EQUAL(LW(3), -1)
                        GOTO(97)
                    END_IF
                ELSE
                    GOTO(96)
                END_IF
            END_LOOP
            LABEL(96)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 0)
            LOOP(0)
                CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
                IF_INT_LESS_OR_EQUAL(LW(0), 150)
                    ADD(LW(2), 10)
                    CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
                    IF_INT_EQUAL(LW(3), -1)
                        GOTO(97)
                    END_IF
                ELSE
                    GOTO(98)
                END_IF
            END_LOOP
        END_IF
    END_IF
    GOTO(98)
    LABEL(97)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_REBOUND1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 45, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 45, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 15, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_togezo), 0)
    CALL(togezo_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, LW(3), LW(4), STRING("TGZ_P_1"))
    CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_ENM_TOGEZO_TURN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, LW(3), 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 15, 0)
    LOOP(5)
        CALL(btlevtcmd_AddRotate, LW(3), 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, LW(3), LW(4), STRING("TGZ_S_1"))
    LOOP(5)
        CALL(btlevtcmd_AddRotate, LW(3), 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 0, 0)
    GOTO(99)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 150)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(5.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), 0, LW(2), 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
    WAIT_FRAMES(10)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Lakitu throws an egg that hatches a Spiny:
 * it takes an egg if it is not holding one, throws it to the free spot in LW(0..2),
 * where it bounces twice (SFX_ENM_JUGEM_JUMP1) and spawns a new Spiny (copying its size status),
 * which spins into place.
 */
static EVT_BEGIN(friend_event)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_1"))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_2"))
        WAIT_FRAMES(30)
    ELSE
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_3"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_THROW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(10), LW(11), LW(12))
    ADD(LW(11), 35)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(10), LW(11), LW(12))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 45, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 45, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 15, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_togezo), 0)
    CALL(togezo_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 50331648)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, LW(3), LW(4), STRING("TGZ_P_1"))
    CALL(btlevtcmd_snd_se, LW(3), STRING("SFX_ENM_TOGEZO_TURN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, LW(3), 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 15, 0)
    LOOP(5)
        CALL(btlevtcmd_AddRotate, LW(3), 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, LW(3), LW(4), STRING("TGZ_S_1"))
    LOOP(5)
        CALL(btlevtcmd_AddRotate, LW(3), 0, 0, -36)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 0, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dark Lakitu charges up: it pays the charge weapon's cost, the camera zooms in,
 * a "crystal_n64" effect appears over it (SFX_ENM_CHARGE1) and it bounces once;
 * the charge weapon is then applied to itself (a power-up).
 */
static EVT_BEGIN(charge_event)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    WAIT_FRAMES(40)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    ADD(LW(2), 10)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_eff64, STRING(""), STRING("crystal_n64"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 60, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, 0, FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        WAIT_MS(500)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), 256, LW(5))
    RETURN
EVT_END()

/** Wait script: plays the Dark Lakitu's idle pose from its current pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: args[0] = source unit, args[1] = destination unit.
 * Copies the size-change status (turns and strength) from the Lakitu to the Spiny it has just spawned
 * (entry_togezo).
 */
static USER_FUNC(togezo_copy_status) {
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
