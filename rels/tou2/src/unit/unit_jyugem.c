// unit_jyugem: Lakitu, battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "tou2.h"

// Unit work slots of the Lakitu (btlevtcmd_Get/SetUnitWork).
enum {
    UW_JYUGEM_EGG_HELD = 0,    // 1 while it holds a Spiny egg overhead (top-spiky)
    UW_JYUGEM_EGG_HATCHES = 1, // 1 when this throw's egg hatches a Spiny if the target guards
    UW_JYUGEM_CHARGED = 2,     // cleared by init_event; nothing in this file reads it
};

static USER_FUNC(togezo_copy_status);

BattleUnitKind unit_jyugem;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
static BattleWeapon weapon_jyugem_attack;
static BattleUnitSetup entry_togezo;
static EvtWord init_event[40];
static EvtWord damage_event[322];
static EvtWord unison_phase_event[139];
static EvtWord avoid_counter_thorn_head_event[61];
static EvtWord dmg_first_attack_pos_event[19];
static EvtWord attack_event[185];
static EvtWord normal_attack_event[585];
static EvtWord friend_event[263];
static EvtWord wait_event[6];

/**
 * Script helper: arg0 = source unit, arg1 = destination unit;
 * copies the size-change status so the Spiny thrown by the Lakitu keeps the Lakitu's Mini/Giant state.
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

/**
 * Unit data of the Lakitu: 5 HP and level 11, with its parts, status vulnerability, init event and event
 * data table.
 */
BattleUnitKind unit_jyugem = {
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
    UNIT_ATTR_FLOATING,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

/**
 * Defense of the Lakitu against normal, fire, ice, explosion and electric attacks: none, so it takes full
 * damage from every element.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type reactions of the Lakitu: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Lakitu (both early demos), as the percent chance each status takes hold: resists
 * 11 statuses (down to 70% of the normal chance).
 */
static StatusVulnerability regist = {80, 90, 100, 100, 80, 100, 100, 70, 100, 80, 100, 80, 100, 80, 80, 90, 100, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of the Lakitu (the retail releases), as the percent chance each status takes hold:
 * resists 10 statuses (down to 80% of the normal chance); extra vulnerable to dizziness.
 */
static StatusVulnerability regist = {80, 90, 105, 100, 80, 100, 100, 100, 100, 90, 100, 90, 100, 95, 80, 90, 100, 100, 80, 100, 100, 95};
#endif

/**
 * Pose table of the Lakitu: maps each battle pose (idle, hurt, attacking and so on) to its animation,
 * named JGM_*.
 */
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

/**
 * Pose table of the Lakitu while it is holding an egg: maps each battle pose (idle, hurt, attacking and so
 * on) to its animation, named JGM_*.
 */
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

/**
 * Event data table of the Lakitu: scripts that replace the standard handling for an attacker being hurt by
 * its spiked head (tag 37) and the battle opening with a First Strike on it (tag 48).
 */
static BattleDataEntry data_table[] = {
    {37, avoid_counter_thorn_head_event},
    {48, dmg_first_attack_pos_event},
    {0, NULL},
};

/**
 * Parts of the Lakitu: 2 parts: parts 1 and 2 (model c_jugemu), each with its defense tables, attributes
 * and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_jyugem", "c_jugemu", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table},
    {2, "パイポ", "c_jugemu", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon record of the Lakitu's egg throw: 2 damage and counts as a jump-type hit. */
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Setup of the Spiny that hatches from the egg (normal_attack_event) or is called in by friend_event: unit
 * kind, side, turn phase and starting position.
 */
static BattleUnitSetup entry_togezo = {
    &unit_togezo, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Init script of the Lakitu: registers its wait, unison-phase, attack, damage and confusion handlers,
 * clears unit work 0 (holding a Spiny egg) and 2, and sets the JGM_P_1 pose.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_CHARGED, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("JGM_P_1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage event of the Lakitu.
 * When it is not holding a Spiny egg (unit work 0 = 0) it just runs the default damage reaction.
 * When it is holding one, a hit that did damage or left it with instant KO (status 27), sleep, dizzy, confusion,
 * electric, freeze or stop knocks the egg out of its hands:
 * part 2 is thrown 200 units behind it to the floor and hidden, the hold (unit work 0),
 * its spiky counter attribute, pose table and hit offset are reset, then the default damage reaction runs.
 * Otherwise, unless the damage code is 22, 30, 31 (an attacker hurt by its spikes), 38 (lucky),
 * 39 (dodged) or 41 (guarded), a poison, burn, Tiny, defense-down,
 * slow or allergic status only makes the egg pop up and vanish again; the Lakitu keeps holding it.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    // With no egg in hand, Lakitu just reacts to the hit normally.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(btldefaultevt_Damage)
    ELSE
        CALL(btlevtcmd_GetDamage, LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            SET_VALUE(LW(15), 1)
        ELSE
            SET_VALUE(LW(15), 0)
        END_IF
        // A hit that did damage, or left instant KO, sleep, dizzy, confusion, electric, freeze or stop, knocks the egg out of its hands.
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_INSTANT_KILL, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_SLEEP, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_DIZZY, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_CONFUSE, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_ELECTRIC, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_FREEZE, LW(14))
        OR(LW(15), LW(14))
        CALL(btlevtcmd_CheckStatus, LW(10), STATUS_STOP, LW(14))
        OR(LW(15), LW(14))
        IF_INT_NOT_EQUAL(LW(15), 0)
            // The egg is flung backward to the floor and hidden, and Lakitu loses its hold on it.
            BEGIN_INLINE_EVENT
                CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
                CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                ADD(LW(1), 35)
                CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 200)
                CALL(btlevtcmd_JumpPartsSetting, LW(10), 2, 0, FLOAT(5.0f), FLOAT(0.2998047f))
                CALL(btlevtcmd_JumpPartsPosition, LW(10), 2, LW(0), 0, LW(2), 0, -1)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, PART_ATTR_HIDDEN)
                CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, PART_ATTR_NO_SHADOW)
            END_INLINE_EVENT
            CALL(btlevtcmd_SetUnitWork, LW(10), UW_JYUGEM_EGG_HELD, 0)
            CALL(btlevtcmd_OffPartsCounterAttribute, LW(10), 1, COUNTER_ATTR_TOP_SPIKY)
            CALL(btlevtcmd_AnimeSetPoseTable, LW(10), 1, PTR(pose_table))
            CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
            CALL_CHILD(btldefaultevt_Damage)
        ELSE
            // Hits where the attacker was hurt by spikes, or that were lucky, dodged or guarded, leave the egg alone.
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
            // A poison, burn, Tiny, defense-down, slow or allergic status only makes the egg pop up and drop back; Lakitu keeps holding it.
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_POISON, LW(15))
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_BURN, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_TINY, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_DEFENSE_DOWN, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_SLOW, LW(14))
            OR(LW(15), LW(14))
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_ALLERGIC, LW(14))
            OR(LW(15), LW(14))
            IF_INT_NOT_EQUAL(LW(15), 0)
                BEGIN_INLINE_EVENT
                    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                    ADD(LW(1), 35)
                    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_JumpPartsSetting, LW(10), 2, 30, 0, FLOAT(0.099609375f))
                    CALL(btlevtcmd_JumpPartsPosition, LW(10), 2, LW(0), LW(1), LW(2), 30, -1)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, PART_ATTR_HIDDEN)
                    CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, PART_ATTR_NO_SHADOW)
                END_INLINE_EVENT
            END_IF
            LABEL(90)
            CALL_CHILD(btldefaultevt_Damage)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Start-of-turn event of the Lakitu (not on turn 1, and not while it is stunned or otherwise unable to act):
 * with a 50% chance it pulls out a Spiny egg and holds it up (unit work 0 = 1, hold pose table,
 * counter attribute on), so its next throw is the held egg.
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
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_INSTANT_KILL, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    SET_VALUE(LW(15), 0)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DIZZY, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CONFUSE, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_ELECTRIC, LW(14))
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
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, 1)
        CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_hold))
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 20, 0)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Data event 37, run (damage code 31) when an attacker is hurt by the spiky egg the Lakitu holds overhead:
 * after 30 frames it shows the toge_flush spark above it, 35 units up,
 * 45 when Huge (status 10) and 25 when Tiny (status 11).
 */
static EVT_BEGIN(avoid_counter_thorn_head_event)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 45)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
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

/** Position event for a first strike on the Lakitu: puts it at height 10 and waits for the attack to finish. */
static EVT_BEGIN(dmg_first_attack_pos_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * Chooses the Lakitu's action: item use if any;
 * otherwise, with weight 20 and when a free spot exists on either side of it, it summons a Spiny (friend_event),
 * else a normal egg throw (weight 65, unit work 1 = 0)
 * or the throw variant that can hatch into a Spiny (weight 15, unit work 1 = 1).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
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
    END_IF
    LABEL(10)
    SET_VALUE(LW(11), 65)
    ADD(LW(11), 15)
    SUBTRACT(LW(11), 1)
    CALL(evt_sub_random, LW(11), LW(10))
    SET_VALUE(LW(11), 65)
    IF_INT_LESS(LW(10), LW(11))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HATCHES, 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    ELSE
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HATCHES, 1)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Lakitu's egg throw (weapon_jyugem_attack):
 * it picks a target (flustered when confused with none), and either raises a new egg (JGM_A_1, JGM_A_2) or,
 * if it was already holding one, drops the hold state;
 * then it throws the egg (part 2) in an arc at the target's hit position.
 * A dodge plays the target's avoid reaction and the egg flies on; a hit applies the guard result and the damage.
 * If unit work 1 is 1 and the target guarded (damage flag 0x40000, DAMAGE_FLAG_GUARDED),
 * the egg rebounds to a free spot near the Lakitu and hatches there into a Spiny (entry_togezo,
 * which takes the Lakitu's Huge or Tiny status from togezo_copy_status) that uncurls with a spin.
 * Otherwise the egg bounces 150 units on to the floor and is hidden.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Lakitu chooses a target for its egg throw.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_jyugem_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_jyugem_attack))
    // The attack is announced and Lakitu turns to face its target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // If Lakitu is not already holding an egg, it raises a new one over its head.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_1"))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_2"))
        WAIT_FRAMES(30)
    ELSE
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_3"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 35)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    // Lakitu throws the egg in an arc toward the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_THROW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 45, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 45, -1)
    // Find out how the target reacts to the egg.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_jyugem_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The throw missed: the egg flies on past the target.
    LABEL(90)
    CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    // The egg hits: the damage is applied.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_jyugem_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_jyugem_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HATCHES, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        // If the target guarded the egg, it rebounds to a free spot near Lakitu and hatches into a Spiny.
        CALL(btlevtcmd_CheckDamageCode, LW(3), DAMAGE_FLAG_GUARDED, LW(0))
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
    // The new Spiny takes on Lakitu's Huge or Tiny status and uncurls with a spin.
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_togezo), 0)
    CALL(togezo_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
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
    // Otherwise the egg bounces on to the floor and is hidden.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 150)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(5.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), 0, LW(2), 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    WAIT_FRAMES(10)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Lakitu calls a friend: winds up, tosses the Spiny egg to the free spot in LW(0), LW(2),
 * and spawns a Spiny (entry_togezo) there, copying its status from the Lakitu (togezo_copy_status)
 * and rolling it into place.
 */
static EVT_BEGIN(friend_event)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_1"))
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_2"))
        WAIT_FRAMES(30)
    ELSE
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_JYUGEM_EGG_HELD, 0)
        CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_TOP_SPIKY)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("JGM_A_3"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_JUGEM_THROW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
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
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
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

/** Idle event: sets the unit's body part 1 to the pose given by its pose table for its current state. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
