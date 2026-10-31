// Battle unit Piranha Plant (キラーパックン): win.rel's copy.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_eff.h"
#include "system.h"

static USER_FUNC(shadow_scale_memory);
static USER_FUNC(shadow_scale_return);
static USER_FUNC(shadow_scale_small);
static USER_FUNC(pakkun_ceil_exist);

static BattleUnitKind unit_pakkun_flower;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_pakkun_flower_attack;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_ceil[18];
static BattleDataEntry data_table[15];
static EvtWord init_event[31];
static EvtWord dmg_avoid_counter_thorn_head_event[71];
static EvtWord damage_event[10];
static EvtWord counter_damage_event[30];
static EvtWord return_event[256];
static EvtWord normal_attack_event[311];
static EvtWord wait_event[6];

/**
 * Unit data of the Piranha Plant (btl_un_pakkun_flower): 15 HP, level 33,
 * a ground plant that dives underground and bites for 9 damage. win.rel carries this copy,
 * but no battle group of Boggly Woods places it.
 */
static BattleUnitKind unit_pakkun_flower = {
    162, // unitType
    "btl_un_pakkun_flower", // name
    15, // maxHp
    0, // maxFp
    1, // dangerHP
    1, // perilHP
    33, // level
    1, // bonusExp
    3, // bonusCoin
    70, // bonusCoinRate
    1, // baseCoin
    50, // runRate
    9999, // pbSoftCap
    40, // width
    48, // height
    {4, 48}, // hitOffset
    {0.0f, 24.0f, 0.0f}, // centerOffset
    {0}, // hpGaugeOffset
    {0}, // talkTogeBaseOffset
    {20.0f, 0.0f, -10.0f}, // heldItemBaseOffset
    {0}, // burnFlameOffset
    0.0f, 0.0f, // vivianOffsetX..vivianOffsetZ
    {20.0f, 0.0f, 0.0f}, // bintaHitOffset
    {16.0f, 32.0f, 0.0f}, // kissHitOffset
    {0.0f, 24.0f, 0.0f}, // cutBaseOffset
    40.0f, // cutWidth
    48.0f, // cutHeight
    0, 0, 0, // turnOrder..swallowChance
    2, // swallowAttributes
    100, // hammerKnockbackChance
    20, // itemStealParam
    {0}, // starPointDispOffset
    "SFX_ENM_PAKKUN_DAMAGED1", // damageSfxName
    "SFX_BTL_DAMAGE_FIRE1", // fireDamageSfxName
    "SFX_BTL_DAMAGE_ICE1", // iceDamageSfxName
    "SFX_BTL_DAMAGE_BIRIBIRI1", // explosionDamageSfxName
    0, // attributeFlags
    &regist, // statusVulnerability
    1, // numParts
    parts, // parts
    init_event, // initEventCode
    (BattleDataEntry*)data_table, // dataTable
};

/**
 * Flat damage reduction of the Piranha Plant against normal, fire, ice, explosion and electric hits: none.
 */
static BattleUnitDefense defence = {0};

/** Element attributes of the Piranha Plant: none, so every element does its normal damage. */
static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Piranha Plant in the demo builds,
 * as a percent of the normal chance of each status:
 * 20% for fright; 30% for Gale Force, instant KO; 60% for dizzy; 70% for Tiny, Attack Down, Defense Down,
 * allergy, Slow; 75% for confusion; 80% for sleep, stop, freeze.
 */
static StatusVulnerability regist = {80, 80, 60, 100, 75, 100, 100, 80, 100, 70, 100, 70, 100, 70, 70, 20, 30, 100, 70, 100, 100, 30};
#else
/**
 * Status vulnerability of the Piranha Plant in the retail builds,
 * as a percent of the normal chance of each status:
 * 10% for fright; 30% for Gale Force, instant KO; 40% for dizzy; 60% for freeze; 70% for stop, allergy, Slow;
 * 80% for confusion; 85% for Tiny, Attack Down, Defense Down.
 */
static StatusVulnerability regist = {100, 70, 40, 100, 80, 100, 100, 60, 100, 85, 100, 85, 100, 85, 70, 10, 30, 100, 70, 100, 100, 30};
#endif

/**
 * The Piranha Plant's single part: the plant model (c_pakflwr),
 * the main target and the part that covers for allies.
 */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_pakkun_flower", // partName
        "c_pakflwr", // modelName
        {0}, // positionOffset
        {0.0f, 40.0f, 0.0f}, // hitBaseOffset
        {0}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        COUNTER_ATTR_TOP_SPIKY, // counterAttributes
        pose_table, // poseTable
    },
};

/**
 * The Piranha Plant's bite: 9 damage to the front-most opposing target,
 * a hammer-like attack that can be guarded.
 */
static BattleWeapon weapon_pakkun_flower_attack = {
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
    {9, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
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
 * Attack entry of the Piranha Plant: with a first-strike battle flag, or after any item use check,
 * it runs normal_attack_event with its single weapon (weapon_pakkun_flower_attack),
 * then returns to the wait event.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(&weapon_pakkun_flower_attack))
        CALL_CHILD(normal_attack_event)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_pakkun_flower_attack))
    CALL_CHILD(normal_attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Poses of the Piranha Plant (PKF_*) while it stands on the ground: idle, status, hurt,
 * bite and talking animations.
 */
static PoseTableEntry pose_table[] = {
    {STATUS_SLEEP, "PKF_N_1"},
    {STATUS_STOP, "PKF_Y_1"},
    {STATUS_FREEZE, "PKF_Y_1"},
    {STATUS_CONFUSE, "PKF_K_1"},
    {STATUS_POISON, "PKF_X_1"},
    {STATUS_DIZZY, "PKF_X_1"},
    {BTL_POSE_NORMAL, "PKF_S_1"},
    {29, "PKF_Q_1"},
    {30, "PKF_Q_1"},
    {31, "PKF_S_2"},
    {BTL_POSE_DAMAGE, "PKF_D_1"},
    {50, "PKF_A_1B"},
    {BTL_POSE_WALK, "PKF_S_1"},
    {BTL_POSE_RUN, "PKF_S_1"},
    {BTL_POSE_DANGER, "PKF_X_1"},
    {BTL_POSE_PERIL, "PKF_X_1"},
    {BTL_POSE_TALK, "PKF_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PKF_S_1"},
};

/**
 * Poses of the Piranha Plant while it hangs from the stage's iron frame on the ceiling;
 * the same slots as pose_table.
 */
static PoseTableEntry pose_table_ceil[] = {
    {STATUS_SLEEP, "PKF_N_2"},
    {STATUS_STOP, "PKF_Y_2"},
    {STATUS_FREEZE, "PKF_Y_2"},
    {STATUS_CONFUSE, "PKF_K_2"},
    {STATUS_POISON, "PKF_X_2"},
    {STATUS_DIZZY, "PKF_X_2"},
    {BTL_POSE_NORMAL, "PKF_S_3"},
    {29, "PKF_Q_2"},
    {30, "PKF_Q_2"},
    {31, "PKF_S_4"},
    {BTL_POSE_DAMAGE, "PKF_D_2"},
    {50, "PKF_A_5"},
    {BTL_POSE_WALK, "PKF_S_3"},
    {BTL_POSE_RUN, "PKF_S_3"},
    {BTL_POSE_DANGER, "PKF_X_2"},
    {BTL_POSE_PERIL, "PKF_X_2"},
    {BTL_POSE_TALK, "PKF_S_3"},
    {BTL_POSE_STAY_DEFAULT, "PKF_S_3"},
};

/**
 * Data table of the Piranha Plant: event 37 (an attacker is hurt by its spiky head) flashes the spikes,
 * events 25 to 36 (it is hurt by a target's counter) play counter_damage_event and event 48
 * (First Strike) does nothing.
 */
static BattleDataEntry data_table[] = {
    {37, dmg_avoid_counter_thorn_head_event},
    {26, counter_damage_event},
    {25, counter_damage_event},
    {27, counter_damage_event},
    {28, counter_damage_event},
    {29, counter_damage_event},
    {30, counter_damage_event},
    {31, counter_damage_event},
    {32, counter_damage_event},
    {33, counter_damage_event},
    {34, counter_damage_event},
    {35, counter_damage_event},
    {36, counter_damage_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Init script of the Piranha Plant: installs the wait, attack, damage and confusion event handlers,
 * sets the hit cursor offset of part 1 and saves its shadow size with shadow_scale_memory.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 50, 0)
    CALL(shadow_scale_memory, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data-table event 37, run by the default damage event when an attacker is hurt by the Piranha Plant's spiky head
 * (damage code 31): it flinches (pose type 31, 250 ms), returns to its idle pose PKF_S_1 and flashes the
 * "toge_flush" spike effect above its head, 50 units up (63 when Huge, 37 when Tiny).
 */
static EVT_BEGIN(dmg_avoid_counter_thorn_head_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 31)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_S_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 63)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        ADD(LW(1), 37)
        GOTO(90)
    END_IF
    ADD(LW(1), 50)
    GOTO(90)
    LABEL(90)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Damage handler: runs the shared default damage script (btldefaultevt_Damage) with its default parameters
 * (LW(10) = -2, LW(11) = 1).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Counter-damage handler: shows the Piranha Plant's damage pose for a second and, unless the counter killed it,
 * runs return_event so it climbs back to its spot.
 */
static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_D_1"))
    WAIT_MS(1000)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_KO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LIFE_SHROOM, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL_CHILD(return_event)
    RETURN
EVT_END()

/**
 * Ceiling-fall script, registered by return_event while the Piranha Plant hangs from the stage's iron frame
 * and run when the frame falls:
 * it hides (shadow shrinking), moves itself and its home to the floor (y 0) and comes back up from the ground,
 * with the floor hit offsets, UNIT_ATTR_CEILING and the hammer and shell-toss no-target part attributes cleared
 * and the floor pose table.
 */
static EVT_BEGIN(ceil_fall_ready_event)
    CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(shadow_scale_small, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_4"))
    WAIT_MS(300)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    WAIT_MS(500)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(shadow_scale_return, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_1"))
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 50, 0)
    CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 4, 48)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 16, 32, 0)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_S_1"))
    RETURN
EVT_END()

/**
 * Sends the Piranha Plant back after an attack or counter:
 * it ducks into the ground (shadow shrinking) and comes up again at its home x.
 * While the stage's iron frame is still there (pakkun_ceil_exist) it picks at random between the floor (y 0)
 * and hanging from the frame (y 130, UNIT_ATTR_CEILING, can't be hit by hammers or shell tosses,
 * ceiling pose table, ceil_fall_ready_event registered).
 */
static EVT_BEGIN(return_event)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(pakkun_ceil_exist, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_sub_random, 1, LW(15))
    ELSE
        SET_VALUE(LW(15), 0)
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(shadow_scale_small, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_2"))
    WAIT_MS(300)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 0, LW(2))
        WAIT_MS(500)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        BEGIN_SIBLING_EVENT
            CALL(shadow_scale_return, BTL_UNIT_SELF)
        END_SIBLING_EVENT
        CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_1"))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, 50, 0)
        CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 4, 48)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 16, 32, 0)
        CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        WAIT_MS(500)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_S_1"))
    ELSE
        CALL(btlevtcmd_SetEventCeilFall, BTL_UNIT_SELF, PTR(ceil_fall_ready_event))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 130, LW(2))
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), 130, LW(2))
        WAIT_MS(500)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        BEGIN_SIBLING_EVENT
            CALL(shadow_scale_return, BTL_UNIT_SELF)
        END_SIBLING_EVENT
        CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_3"))
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, -80, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 0, -50, 0)
        CALL(btlevtcmd_SetStatusIconOffset, BTL_UNIT_SELF, 4, 10)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 16, -32, 0)
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HAMMERLIKE_CANNOT_TARGET)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_ceil))
        WAIT_MS(500)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_S_3"))
    END_IF
    RETURN
EVT_END()

/**
 * The Piranha Plant's bite (weapon_pakkun_flower_attack, 9 damage to one enemy):
 * picks a target (or the first-strike target),
 * sinks out of sight (from the floor or the ceiling),
 * pops up from the ground next to the target and bites it with the camera following,
 * handles the guard and avoid cases, then runs return_event.
 */
static EVT_BEGIN(normal_attack_event)
    // A First Strike aims at the first-strike target after a short pause;
    // otherwise the plant picks a target from the opposing side.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
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
    // Declare the attack, wait for any guard and pay the cost.
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    // The plant sinks into the ground while its shadow shrinks (from the floor or from the ceiling pose).
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(shadow_scale_small, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_CheckAttribute, BTL_UNIT_SELF, UNIT_ATTR_CEILING, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_2"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_4"))
    END_IF
    WAIT_MS(300)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    // Underground it slides next to the target and turns toward it.
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 45)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), 0, LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(500)
    // The camera follows as the plant pops out of the ground with its shadow growing
    // back, then winds up its bite.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(shadow_scale_return, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_E_1"))
    WAIT_MS(150)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_A_1A"))
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PAKKUN_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_A_1B"))
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PKF_A_1C"))
    // Bite: the damage pre-check decides whether the target dodges or the hit lands.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Hit: the camera shakes, the guard result is resolved and the damage is dealt.
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    LABEL(98)
    // After a pause the plant ducks down and resurfaces at its home spot (return_event).
    WAIT_MS(500)
    CALL_CHILD(return_event)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event of the Piranha Plant: switches to pose-table entry 1 (PKF_N_1 on the floor, PKF_N_2 on the ceiling). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: grows the shadow of the plant's part 1 from 0 back to the size stored by shadow_scale_memory
 * over 15 frames, after it comes out of the ground. args[0] is the unit.
 */
static USER_FUNC(shadow_scale_return) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    part->shadowScale = intplGetValue(0, 0.0f, unit->work[0], unit->work[1], 15);
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: shrinks the shadow of the plant's part 1 from its stored size to 0 over 15 frames,
 * as it goes into the ground. args[0] is the unit.
 */
static USER_FUNC(shadow_scale_small) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    if (isFirstCall) {
        unit->work[1] = 0;
    }
    part->shadowScale = intplGetValue(0, unit->work[0], 0.0f, unit->work[1], 15);
    if (unit->work[1] >= 15) {
        return EVT_RETURN_DONE;
    }
    unit->work[1]++;
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: saves the current shadow scale of the plant's part 1 into the unit's work[0],
 * for shadow_scale_return and shadow_scale_small. args[0] is the unit.
 */
static USER_FUNC(shadow_scale_memory) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    unit->work[0] = part->shadowScale;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: writes 0 to args[0] if the stage's ceiling iron frame has been knocked away
 * (STAGE_OBJ_FLAG_IRON_FRAME_GONE), otherwise 1;
 * the plant uses it to decide whether it can hang from the ceiling.
 */
static USER_FUNC(pakkun_ceil_exist) {
    EvtWord* args = event->args;

    if (_battleWorkPointer->stageObjectWork.flags & STAGE_OBJ_FLAG_IRON_FRAME_GONE) {
        evtSetValue(event, args[0], 0);
    } else {
        evtSetValue(event, args[0], 1);
    }
    return EVT_RETURN_DONE;
}
