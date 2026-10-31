// Palace of Shadow battle unit: the Phantom Ember (`phantom`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "eff/eff_fire.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_sub.h"
#include "version.h"

static EffectEntry* eff;
static EffectEntry* eff2[10];
static s32 step[10];

static USER_FUNC(eff_fire);

BattleUnitKind unit_phantom;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[4];
static BattleUnitKindPart parts[2];
static BattleWeapon weapon_bubble_attack;
static BattleWeapon weapon_bubble_fire_attack;
static BattleUnitSetup entry_bubble;
static EvtWord init_event[39];
static EvtWord damage_event[10];
static EvtWord avoid_fire_event[16];
static EvtWord damage_fire_explosion_event[103];
static EvtWord friend_event[99];
static EvtWord attack_event[51];
static EvtWord normal_attack_event[412];
static EvtWord fire_attack_event[365];
static EvtWord wait_event[6];

/**
 * Script helper: copies HP (clamped to the target's maximum),
 * shrink/grow status and the HP gauge's displayed HP from the unit in args[0] to the unit in args[1],
 * so a Phantom Ember's flame keeps its source's HP.
 */
static USER_FUNC(bubble_copy_status) {
    EvtWord* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    if (unit2->currentHp > unit2->maxHp) {
        unit2->currentHp = unit2->maxHp;
    }
    unit2->sizeChangeTurns = unit1->sizeChangeTurns;
    unit2->sizeChangeStrength = unit1->sizeChangeStrength;
    unit2->hpGauge.prevHp = unit2->currentHp;
    unit2->hpGauge.targetHp = unit2->currentHp;
    unit2->hpGauge.barRatio = unit2->hpGauge.trailRatio = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

/**
 * Unit data of the Phantom Ember: 10 HP, 26x36 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_phantom = {
    124,
    "btl_un_phantom",
    10,
    0,
    1,
    1,
    30,
    0,
    2,
    70,
    2,
    50,
    9999,
    26,
    36,
    8,
    24,
    0.0f,
    18.0f,
    0.0f,
    0,
    -3,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    0.0f,
    13.0f,
    23.4f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    26.0f,
    36.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BUBBLE_DAMAGED1",
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

/** Defence of the Phantom Ember: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/**
 * Defence attributes of the Phantom Ember: fire hits heal it; ice hits do one extra damage;
 * explosion hits do one extra damage.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 3, 1, 1, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of the Phantom Ember (percent chance each status takes hold):
 * immune to burn; resists sleep (40%), dizzy (65%), poison (25%), confusion (65%), freeze (40%),
 * Tiny (65%), Attack Down (65%), Defense Down (65%), allergic (65%), fright (40%), Slow (65%);
 * the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {40, 80, 65, 25, 65, 100, 0, 40, 100, 65, 100, 65, 100, 65, 65, 40, 80, 100, 65, 100, 100, 90};
#else
/**
 * Retail builds: Status vulnerability of the Phantom Ember (percent chance each status takes hold):
 * immune to burn; resists sleep (40%), confusion (65%), freeze (40%), allergic (65%), fright (40%),
 * Slow (65%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {40, 80, 100, 100, 65, 100, 0, 40, 100, 80, 100, 80, 100, 90, 65, 40, 80, 100, 65, 100, 100, 90};
#endif

/** Pose table of the Phantom Ember: maps its battle poses to its animations. */
static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {BTL_POSE_NORMAL, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_2B"},
    {BTL_POSE_DAMAGE, "D_1"},
    {50, "A_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_DANGER, "X_1"},
    {BTL_POSE_PERIL, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/** Event table of the Phantom Ember: damage_fire_explosion_event (tag 11), avoid_fire_event (tag 40). */
static BattleDataEntry data_table[] = {
    {11, damage_fire_explosion_event},
    {40, avoid_fire_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/** Parts of the Phantom Ember: 1 part (model c_phantom). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_phantom", "c_phantom", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WEAK_TO_ICE_POWER, COUNTER_ATTR_FIERY, pose_table},
    {2, NULL, "c_phantom", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/**
 * Weapon of the Phantom Ember (attack): targets one unit for 5 damage, fire element; used by attack_event.
 */
static BattleWeapon weapon_bubble_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    1, // superguardsAllowed
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_JP
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#endif
    COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of the Phantom Ember (fire attack): targets one unit for 5 damage, fire element, ignores Defense,
 * may inflict Burn (75%, 3 turns); used by attack_event.
 */
static BattleWeapon weapon_bubble_fire_attack = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_JP
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    75, // burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Spawn setup for the Phantom Ember (unit_phantom): enemy side, placed off-screen at first;
 * used by friend_event.
 */
static BattleUnitSetup entry_bubble = {
    &unit_phantom, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Init event of the Phantom Ember: installs its wait, attack,
 * damage and confusion events and puts it 10 units above the ground.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 10, LW(2))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Phantom Ember: default damage handling on its body part. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Event (data table entry) for when the Phantom Ember is hit by fire and shrugs it off:
 * plays the fire sound and the A_2B pose for a second.
 */
static EVT_BEGIN(avoid_fire_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_FIRE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * Run when a fire hit lands on the Phantom Ember (data table entry 11, damage code 0x18), which makes it split:
 * it takes pose A_2B, waits as many frames as its x position, then looks for free space beside it, first behind
 * and then in front (btlevtcmd_CheckSpace), and calls friend_event there to spawn a new Phantom Ember.
 */
static EVT_BEGIN(damage_fire_explosion_event)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(friend_event)
                WAIT_MS(500)
                GOTO(99)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
        IF_INT_GREATER_OR_EQUAL(LW(0), 10)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(friend_event)
                WAIT_MS(500)
                GOTO(99)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    LABEL(99)
    RETURN
EVT_END()

/**
 * Splitting move of the Phantom Ember: a new Phantom Ember (entry_bubble, which uses this unit kind) is spawned
 * at its position,
 * copies its status (bubble_copy_status), spins and jumps to the free spot found by the caller.
 */
static EVT_BEGIN(friend_event)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("S_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(12), LW(13), LW(14))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_bubble), 0)
    CALL(bubble_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_SetPos, LW(3), LW(12), LW(13), LW(14))
    CALL(btlevtcmd_JumpSetting, LW(3), 0, 10, FLOAT(0.5f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_SPLIT1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 10, 0)
        SET_VALUE(LW(12), 0)
        LOOP(0)
            WAIT_FRAMES(1)
            ADD(LW(12), 1)
            IF_INT_GREATER_OR_EQUAL(LW(12), 30)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AddRotate, LW(3), 0, 0, 40)
        END_LOOP
        CALL(btlevtcmd_SetRotate, LW(3), 0, 0, 0)
        CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), FLOAT(30.0f), -1)
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * Attack event of the Phantom Ember: can use an item;
 * otherwise draws 0 to 99 and uses the body charge (weapon_bubble_attack) for 70
 * and the fire ball (weapon_bubble_fire_attack) for 30.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
        RETURN
    END_IF
    SET_VALUE(LW(0), 70)
    ADD(LW(0), 30)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 70)
        SET_VALUE(LW(9), PTR(&weapon_bubble_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_bubble_fire_attack))
    CALL_CHILD(fire_attack_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack of the Phantom Ember: the body charge.
 * It flies at the target in two dives, gives off the fire sound,
 * and either misses (with the dodge reaction) or hits with the action command defence check,
 * then flies back to its home position.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // The camera pulls in as the Phantom Ember drifts toward its target with a floating sound.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(120)
    END_SIBLING_EVENT
    // It swoops down in front of its target in two dives, ending right next to it.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 13)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), 0)
        SET_VALUE(LW(1), 0)
    END_IF
    ADD(LW(2), 5)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 0, 0, -1)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 5)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), 0)
        SET_VALUE(LW(1), 0)
    END_IF
    ADD(LW(2), 5)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    DELETE_EVENT(LW(15))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
    // The attack misses or is blocked: it still breathes its flame (A_1B), but the target avoids it.
    LABEL(90)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_FIRE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(4)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
        WAIT_FRAMES(10)
    END_LOOP
    GOTO(98)
    // The attack hits: the camera shakes and pulls back, the flame burns the target and the Action Command
    // defence result is applied.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_FIRE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(10)
    LOOP(3)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
        WAIT_FRAMES(10)
    END_LOOP
    GOTO(98)
    // The Phantom Ember floats back up and away in three dives to its starting spot, then settles into its
    // idle pose.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(1), 20)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 20, 0, 0, -1)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 100)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -30, 0, 0, -1)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 25, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(400)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper (runs every frame while blocked):
 * keeps a fire effect on the Phantom Ember's part 2
 * and grows it by 0.1 per frame up to the unit's size multiplier. The first call creates the effect.
 */
static USER_FUNC(eff_fire) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 2);
    EffFireWork* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
#if VERSION <= VERSION_DEMO_JP
        eff = effFireEntry(7, 90, 0.0f, -1000.0f, 0.0f, 1.0f);
#else
        eff = effFireEntry(7, 106, 0.0f, -1000.0f, 0.0f, 1.0f);
#endif
        ((EffFireWork*)eff->userdata)->scaleX = 0.0f;
        ((EffFireWork*)eff->userdata)->scaleY = 0.0f;
    }
    wk = eff->userdata;
    if (wk != NULL) {
        BtlUnit_GetPartsPos(part, &x, &y, &z);
        wk->position = (Vec){x, y, z};
        wk->scaleX += 0.1f * unit->sizeMultiplier;
        if (wk->scaleX >= unit->sizeMultiplier) {
            wk->scaleX = unit->sizeMultiplier;
        }
        wk->scaleY += 0.1f * unit->sizeMultiplier;
        if (wk->scaleY >= unit->sizeMultiplier) {
            wk->scaleY = unit->sizeMultiplier;
        }
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Attack of the Phantom Ember: the fire ball.
 * It shoots a fire ball (part 2, with the fire effect) in an arc to the target,
 * which either dodges it or takes the damage with a smoke puff at the hit point.
 */
static EVT_BEGIN(fire_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 0)
    BEGIN_SIBLING_EVENT
        // The Phantom Ember tilts back (T_1) for a moment while it conjures a fireball.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("T_1"))
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    END_SIBLING_EVENT
    // The fireball (part 2) appears at the Phantom Ember with a fire effect trailing behind it.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(eff_fire, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 0)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    SUBTRACT_FLOAT(LW(10), LW(0))
    SUBTRACT_FLOAT(LW(12), LW(2))
    MULTIPLY_FLOAT(LW(10), FLOAT(0.69921875f))
    MULTIPLY_FLOAT(LW(12), FLOAT(0.5996094f))
    ADD_FLOAT(LW(0), LW(10))
    ADD_FLOAT(LW(2), LW(12))
    // The fireball flies toward the target in three arcing dives that get shorter as it closes in.
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 40, 0, 4, 0, -1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    SUBTRACT_FLOAT(LW(10), LW(0))
    SUBTRACT_FLOAT(LW(12), LW(2))
    MULTIPLY_FLOAT(LW(10), FLOAT(0.39941406f))
    MULTIPLY_FLOAT(LW(12), FLOAT(0.39941406f))
    ADD_FLOAT(LW(0), LW(10))
    ADD_FLOAT(LW(2), LW(12))
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 20, 0, 4, 0, -1)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 30, 0, 1, 0, -1)
    // The fireball reaches the target and disappears.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
    GOTO(98)
    // The fireball hits: a puff of smoke bursts, the Action Command defence result is applied and damage is
    // dealt.
    LABEL(91)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 16, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    // The camera resets and the Phantom Ember pauses a moment.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(400)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper (runs every frame while blocked):
 * keeps one flame of the all-fire attack, index args[1], in front of the unit at 24 units per index;
 * the flame sizes follow a rising and falling table (1.0 to 2.25). The first call creates the effect.
 */
static USER_FUNC(eff_all_fire) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 index = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[10] = {1.0f, 1.25f, 1.5f, 1.75f, 2.0f, 2.25f, 2.0f, 1.75f, 1.5f, 1.25f};
    EffFireWork* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        eff2[index] = effFireEntry(7, 120, 0.0f, -1000.0f, 0.0f, 1.0f);
        ((EffFireWork*)eff2[index]->userdata)->scaleX = 2.0f;
        ((EffFireWork*)eff2[index]->userdata)->scaleY = unit->sizeMultiplier * scales[index];
    }
    wk = eff2[index]->userdata;
    if (wk != NULL) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        wk->position = (Vec){x + 24.0f * unit->faceDirection * (index + 1), y - 15.0f - 2.0f * scales[index], z - 10.0f};
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Helper of all_fire_attack_event: spawns the fire shower effect (eff_all_fire) for the count in LW(0)
 * and waits 120 frames.
 */
static EVT_BEGIN(all_fire_attackEvent_sub)
    BEGIN_SIBLING_EVENT
        CALL(eff_all_fire, BTL_UNIT_SELF, LW(0))
    END_SIBLING_EVENT
    WAIT_FRAMES(120)
    RETURN
EVT_END()

/**
 * Attack of the Phantom Ember on every target; unused, as nothing in the file calls it:
 * it shakes while charging, then fire rains on the whole opposing side (ten eff_all_fire showers),
 * and each target gets its dodge or hit check in turn. It then returns to its home position.
 */
static EVT_BEGIN(all_fire_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    // The camera zooms out to take in every target while the Phantom Ember floats back (A_1A) to its firing
    // spot.
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
#if VERSION >= VERSION_US
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -40, LW(1), -15, 30, 0, 4, 0, -1)
#else
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -40, LW(1), LW(2), 30, 0, 4, 0, -1)
#endif
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It charges up (A_2A), trembling from side to side for about 80 frames.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    LOOP(20)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, 2, 0, 0)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_AddPos, BTL_UNIT_SELF, -2, 0, 0)
        WAIT_FRAMES(2)
    END_LOOP
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(10)
            // Ten fireballs shoot out one after another across the stage.
            SPAWN_EVENT(all_fire_attackEvent_sub)
            WAIT_FRAMES(2)
            ADD(LW(0), 1)
        END_LOOP
    END_SIBLING_EVENT
    // It breathes the fire out (A_2B) and the camera follows the flames.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    // Each target is checked in turn: a miss, or a hit that applies damage (the defence result counts for the
    // first target only).
    LABEL(0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
    GOTO(98)
    LABEL(91)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(0)
    END_IF
    // After a long pause (180 frames) it floats back to its starting spot.
    LABEL(98)
    WAIT_FRAMES(180)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BUBBLE_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(400)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event of the Phantom Ember: plays its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
