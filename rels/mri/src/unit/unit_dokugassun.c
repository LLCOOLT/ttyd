// The Great Tree (mri) battle unit: Poison Puff (dokugassun): its parts, defence/status tables, and the attack, poison
// gas and barrier events.
#include "eff/n64/eff_vapor_n64.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "driver/effdrv.h"
#include "system.h"
#include "stdlib.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_sub.h"
#include "version.h"

static USER_FUNC(eff_poison_barrier);
static USER_FUNC(eff_poison_breath);

static BattleUnitKind unit_dokugassun;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_dokugassun_attack;
static BattleWeapon weapon_dokugassun_poisongas_attack;
#if VERSION <= VERSION_DEMO_US
static EvtWord poisongas_event[274];
#else
static EvtWord poisongas_event[303];
#endif
static PoseTableEntry pose_table[17];
static BattleDataEntry data_table[3];
static EvtWord init_event[37];
static EvtWord barrier_event[33];
static EvtWord dmg_first_attack_pos[19];
static EvtWord damage_event[10];
static EvtWord counter_event[2];
static EvtWord unison_phase_event[140];
static EvtWord normal_attack_event[386];
static EvtWord charge_event[58];
#if VERSION <= VERSION_DEMO_US
static EvtWord wait_event[12];
#else
static EvtWord wait_event[13];
#endif

static BattleUnitKind unit_dokugassun = {
    166, // unitType
    "btl_un_dokugassun", // name
    15, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    34, // level
    2, // bonusExp
    2, // bonusCoin
    70, // bonusCoinRate
    2, // baseCoin
    50, // runRate
    9999, // pbSoftCap
    35, // width
    30, // height
    {4, 30}, // hitOffset
    {0.0f, 15.0f, 0.0f}, // centerOffset
    {0, -3}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {18.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {17.5f, 0.0f, 0.0f}, // bintaHitOffset
    {17.5f, 19.5f, 0.0f}, // kissHitOffset
    {0.0f, 15.0f, 0.0f}, // cutBaseOffset
    35.0f, // cutWidth
    30.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    100, // hammerKnockbackChance
    20, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_KUMO_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    UNIT_ATTR_FLOATING, // attributeFlags
    &regist, // statusVulnerability
    1, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table, // dataTable
};

static BattleUnitDefense defence = {0};

static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 70, 80, 0, 60, 100, 100, 60, 100, 60, 100, 60, 100, 60, 60, 60, 80, 100, 60, 100, 100, 20};
#else
static StatusVulnerability regist = {65, 65, 90, 0, 60, 100, 100, 100, 100, 80, 100, 80, 100, 80, 50, 60, 85, 100, 60, 100, 100, 20};
#endif

static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_dokugassun", // partName
        "c_kmoon_g", // modelName
        {0}, // positionOffset
        {0.0f, 25.0f, 0.0f}, // hitBaseOffset
        {0.0f, 30.0f, 0.0f}, // hitCursorBaseOffset
        30, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, // attributes
        0, // counterAttributes
        pose_table, // poseTable
    },
};

/**
 * Creates one puff of poison gas (a green-blue vapor effect) at a random spot on the target side of the stage:
 * x near -125 (args[0] = 0) or 125 (otherwise) plus or minus 75,
 * random height up to 70 and depth plus or minus 40, with a random size.
 */
static USER_FUNC(eff_poison_breath) {
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;
    EffVaporN64Work* wk;

    if (evtGetValue(event, event->args[0]) == 0) {
        x = -125.0f;
    } else {
        x = 125.0f;
    }
    x += irand(150) - 75;
    y = irand(70);
    z = irand(80) - 40;
    eff = effVaporN64Entry(0, 15, x, y, z, 2.5f + rand() / 32767.0f);
    wk = eff->userdata;
    wk->r1 = 32;
    wk->g1 = 115;
    wk->b1 = 100;
    wk->alpha = 255;
    wk->r2 = 32;
    wk->g2 = 115;
    wk->b2 = 100;
    wk->a2 = 255;
    return EVT_RETURN_DONE;
}

static BattleWeapon weapon_dokugassun_attack = {
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
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    COUNTER_RESIST_POISON, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
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

static BattleWeapon weapon_dokugassun_poisongas_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
#if VERSION >= VERSION_US
    2, // superguardsAllowed
#else
    0, // superguardsAllowed
#endif
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {10, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
#if VERSION <= VERSION_DEMO_US
    50, // poisonChance
#else
    70, // poisonChance
#endif
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack event of the Poison Puff. Uses an enemy item if it has one.
 * If it is charged up (the counter attribute 512 is set) it breathes the poison gas (poisongas_event);
 * otherwise it rolls: a 65 percent chance (70 in the demo) of the body slam (normal_attack_event),
 * else it charges up (charge_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 512, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_dokugassun_poisongas_attack))
        CALL_CHILD(poisongas_event)
        GOTO(99)
    END_IF
#if VERSION <= VERSION_DEMO_US
    SET_VALUE(LW(0), 70)
    ADD(LW(0), 30)
#else
    SET_VALUE(LW(0), 65)
    ADD(LW(0), 35)
#endif
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
#if VERSION <= VERSION_DEMO_US
    SET_VALUE(LW(0), 70)
#else
    SET_VALUE(LW(0), 65)
#endif
    IF_INT_LESS(LW(1), LW(0))
        SET_VALUE(LW(9), PTR(&weapon_dokugassun_attack))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL_CHILD(charge_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Poison gas attack: the Poison Puff, already charged, breathes poison gas on all targets.
 * From JP it first slides back 40 units.
 * It faces the opponents, plays the wind-up poses with the charge sounds, turns off the charge,
 * then puffs 20 clouds of gas (one every 3 frames) over the target side while the damage
 * and poison checks run for each target.
 */
static EVT_BEGIN(poisongas_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
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
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, -40, LW(1), LW(2), 30, 0, 4, 0, -1)
#endif
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_DOKU_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_DOKU_KUMO_CHARGE_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_OffPartsCounterAttribute, BTL_UNIT_SELF, 1, 512)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetEnemyBelong, LW(3), LW(10))
        IF_INT_EQUAL(LW(10), 0)
            LOOP(20)
                CALL(eff_poison_breath, 1)
                WAIT_FRAMES(3)
            END_LOOP
        ELSE
            LOOP(20)
                CALL(eff_poison_breath, 0)
                WAIT_FRAMES(3)
            END_LOOP
        END_IF
    END_SIBLING_EVENT
    WAIT_FRAMES(10)
    SET_VALUE(LW(6), 0)
    LABEL(0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
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
    GOTO(97)
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(97)
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    LABEL(98)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(250)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
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
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "A_1"},
    {39, "D_1"},
    {40, "W_1"},
    {42, "R_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Creates three small puffs of poison gas around the Poison Puff (random offsets of 10 left or right and up to
 * 30 up), scaled to its size, to show it is charged.
 */
static USER_FUNC(eff_poison_barrier) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    for (i = 0; i < 3; i++) {
        EffectEntry* eff;
        EffVaporN64Work* wk;

        BtlUnit_GetPos(unit, &x, &y, &z);
        x += irand(20) - 10;
        y += irand(30);
        eff = effVaporN64Entry(2, (i + 1) * 10, x, y, z, 0.5f + 0.5f * rand() / 32767.0f);
        wk = eff->userdata;
        wk->r1 = 32;
        wk->g1 = 115;
        wk->b1 = 100;
        wk->alpha = 255;
        wk->r2 = 32;
        wk->g2 = 115;
        wk->b2 = 100;
        wk->a2 = 255;
        wk->scale = unit->sizeMultiplier;
    }
    return EVT_RETURN_DONE;
}

static BattleDataEntry data_table[] = {
    {43, counter_event},
    {48, dmg_first_attack_pos},
    {0},
};

/**
 * Init script of the Poison Puff: sets its wait, unison phase, attack, damage and confusion events,
 * clears its two unit work values (work 0 says which way its next hop goes),
 * starts the barrier_event loop and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    SPAWN_EVENT(barrier_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Loop that runs for as long as the Poison Puff exists:
 * every 31 frames, if it is charged (counter attribute 512), it creates the poison barrier puffs around itself.
 */
static EVT_BEGIN(barrier_event)
    LABEL(0)
    WAIT_FRAMES(31)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(eff_poison_barrier, BTL_UNIT_SELF)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/** Data-table hook for a first attack on the Poison Puff: sets its y position to 10 and waits for the attack to end. */
static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/** Damage event of the Poison Puff: runs the default damage reaction. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Counter event of the Poison Puff: does nothing. */
static EVT_BEGIN(counter_event)
    RETURN
EVT_END()

/**
 * Unison-phase event: before the player phase, if it can act and is not charged,
 * there is a 25 percent chance (rolled from 0 to 98) it moves between two heights,
 * y 40 (with the hit-avoiding part attributes 6291456 set) and y 10 (attributes cleared), with a sound,
 * toggling work 0 each time.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPartsCounterAttribute, BTL_UNIT_SELF, 1, 512, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_LESS(LW(0), 25)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 40)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, 10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        ELSE
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE5"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SET_VALUE(LW(1), 10)
            CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Body slam of the Poison Puff: it picks a target (or uses the first-strike target),
 * shakes and shrinks for 40 frames, then dives to a spot behind itself and flies at the target to strike it;
 * the damage and result checks follow, and the Puff returns to its home position afterwards.
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
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
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
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 1, 0, 0)
            WAIT_FRAMES(2)
            CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, -1, 0, 0)
            WAIT_FRAMES(2)
        END_LOOP
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(40)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.009765625f), 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -40)
    SET_VALUE(LW(1), 60)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 4, 0, -1)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 40, -40, 1, 0, -1)
    CALL(evt_snd_sfxoff, LW(15))
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
        SET_VALUE(LW(15), 1)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(10), 40)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(10), LW(1), LW(12), 40, 0, 4, 0, -1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KUMO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 40, 4, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(evt_snd_sfxoff, LW(15))
    WAIT_MS(250)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Charge-up: the camera moves in, the Poison Puff plays the charge sound and poses for 80 frames
 * while the counter attribute (512) is set, which makes it poison whoever hits it,
 * then goes back to its normal pose.
 */
static EVT_BEGIN(charge_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_DOKU_KUMO_CHARGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, 512)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2A"))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2B"))
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    WAIT_MS(600)
    LABEL(99)
    RETURN
EVT_END()

/** Idle script of the Poison Puff: plays its idle pose and resets its scale to normal. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, 1, 1, 1)
    RETURN
#if VERSION <= VERSION_DEMO_US
EVT_END()
#else
EVT_END_PAD()
#endif
