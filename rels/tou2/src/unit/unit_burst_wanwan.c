// unit_burst_wanwan: Red Chomp (`burst_wanwan`), the Glitz Pit's red Chain-Chomp, battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
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
#include "libc_decls.h"

// Unit work slots of the Red Chomp (btlevtcmd_SetUnitWork / GetUnitWork; chain_main reads slot 2).
enum {
    UW_BURST_WANWAN_IDLE = 0,        // 1 outside its attack, 0 while it attacks (not read in this file)
    UW_BURST_WANWAN_BARK_VOLUME = 1, // landing/bark sound volume, lowered by sound_gensui_event (floor 32)
    UW_BURST_WANWAN_CHAIN_MODE = 2,  // chain_main: 2 records the chain's shape, 1 holds it, 0 lets it sag
};

static USER_FUNC(chain_init);
static USER_FUNC(chain_main);

BattleUnitKind unit_burst_wanwan;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[15];
static BattleUnitKindPart parts[9];
static BattleWeapon weapon_wanwan_attack;
static EvtWord init_event[41];
static EvtWord chain_event[23];
static EvtWord damage_event[33];
#if VERSION <= VERSION_DEMO_US
static EvtWord counter_damage_event[115];
#else
static EvtWord counter_damage_event[68];
#endif
static EvtWord dead_event[200];
static EvtWord attack_event[452];
static EvtWord wait_event[476];
static EvtWord sound_gensui_event[22];
static EvtWord wait_sound_event1[25];
#if VERSION <= VERSION_DEMO_US
static EvtWord wait_sound_event2[11];
#else
static EvtWord wait_sound_event2[12];
#endif

/**
 * Unit kind of the Red Chomp (HP 6, level 24): its size, offsets, damage sounds, status vulnerability,
 * parts and init event.
 */
BattleUnitKind unit_burst_wanwan = {
    59,
    "btl_un_burst_wanwan",
    6,
    0,
    1,
    1,
    24,
    0,
    1,
    70,
    3,
    50,
    9999,
    34,
    36,
    6,
    44,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    0.0f,
    17.0f,
    23.4f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    34.0f,
    36.0f,
    0,
    0,
#if VERSION <= VERSION_DEMO_US
    -1,
    0,
#else
    0,
    2,
#endif
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_WAN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    9,
    parts,
    init_event,
    data_table,
};

#if VERSION <= VERSION_DEMO_US
/** Defence of the Red Chomp: 3 damage points off every hit. */
static BattleUnitDefense defence = {{3, 3, 3, 3, 3}};
#else
/**
 * Defence of the Red Chomp: 3 against normal, explosion and electric hits;
 * immune to fire and ice (defence 99 cancels the hit).
 */
static BattleUnitDefense defence = {{3, 99, 99, 3, 3}};
#endif

#if VERSION <= VERSION_DEMO_US
/** Element reactions of the Red Chomp: no special reaction to any element. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};
#else
/** Element reactions of the Red Chomp: fire: no damage, ice: no damage. */
static BattleUnitDefenseAttr defence_attr = {{0, 2, 2, 0, 0}};
#endif

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of the Red Chomp (percent chance to take each status): immune to sleep;
 * resists most other statuses.
 */
static StatusVulnerability regist = {0, 65, 65, 100, 65, 100, 100, 65, 100, 65, 100, 65, 100, 65, 65, 45, 30, 100, 65, 100, 100, 95};
#else
/**
 * Status vulnerability of the Red Chomp (percent chance to take each status): immune to sleep and burn;
 * resists most other statuses.
 */
static StatusVulnerability regist = {0, 70, 65, 100, 65, 100, 0, 70, 100, 90, 100, 90, 100, 95, 65, 45, 30, 100, 65, 100, 100, 95};
#endif

/** Pose table of the Red Chomp: maps each battle pose to the animation it plays (WAN_* animations). */
static PoseTableEntry pose_table[] = {
    {1, "WAN_N_1"},
    {2, "WAN_Y_1"},
    {9, "WAN_Y_1"},
    {5, "WAN_K_1"},
    {4, "WAN_X_1"},
    {3, "WAN_X_1"},
    {27, "WAN_Z_1"},
    {BTL_POSE_NORMAL, "WAN_S_1A"},
    {29, "WAN_D_1"},
    {30, "WAN_D_1"},
    {31, "WAN_A_1"},
    {BTL_POSE_DAMAGE, "WAN_D_1"},
    {50, "WAN_A_1"},
    {BTL_POSE_RUN, "WAN_R_1"},
    {BTL_POSE_WALK, "WAN_W_1"},
    {BTL_POSE_DANGER, "WAN_X_1"},
    {BTL_POSE_PERIL, "WAN_X_1"},
    {BTL_POSE_TALK, "WAN_S_1A"},
    {BTL_POSE_STAY_DEFAULT, "WAN_S_1A"},
};

/**
 * Data table of the Red Chomp: event handlers for the counter-hit reactions (tags 25-36),
 * a First Strike on it (no reaction) and being defeated.
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
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
    {0, NULL},
};

/** Parts of the Red Chomp (9 parts): hit positions, defences, attributes and pose tables. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {2, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {5, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {6, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {7, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {8, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {9, "btl_un_burst_wanwan", "c_wanwan_a", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon of the Red Chomp's bite: 5 damage, hammer-type contact attack. */
static BattleWeapon weapon_wanwan_attack = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON, // counterResistFlags
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
 * Init event of the Red Chomp: registers its wait, attack, damage and confusion events,
 * sets unit work 0 to 1 and the sound volume in work 1 to 127,
 * sets up its chain (chain_init) and spawns chain_event to keep it moving,
 * sets the landing sound for jumps and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_IDLE, 1)
    CALL(chain_init, BTL_UNIT_SELF)
    SPAWN_EVENT(chain_event)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("0"), STRING("SFX_ENM_WAN_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_BARK_VOLUME, 127)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Runs alongside the Red Chomp for the whole battle:
 * every frame calls chain_main to update the chain links, until the unit no longer exists.
 */
static EVT_BEGIN(chain_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(chain_main, BTL_UNIT_SELF)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Damage event of the Red Chomp: sets unit work 0 to 1 and work 2 to 2 and,
 * with attribute 4 (UNIT_ATTR_FLOATING) set on it, runs the default damage reaction,
 * then clears the attribute and unit work 2.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_IDLE, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_CHAIN_MODE, 2)
    CALL(btlevtcmd_OnAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_CHAIN_MODE, 0)
    RETURN
EVT_END()

/**
 * Data events 25 to 36, which the standard damage reaction runs for the counter-damage codes 44 to 55:
 * the Red Chomp takes the hurt pose (type 39) and its head (part 1) is flung 25 units back and up;
 * up to the US demo it then drops back to the floor in two hops.
 * After 30 frames the camera resets, and it restarts its wait event
 * unless the damage code has 512 set without 2048.
 */
static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    CALL(btlevtcmd_SetPartsFallAccel, LW(10), 1, FLOAT(1.0f))
    CALL(btlevtcmd_GetPartsPos, LW(10), 1, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_PartsFaceDirectionSub, LW(10), 1, LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePartsPosition, LW(10), 1, LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
#if VERSION <= VERSION_DEMO_US
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SetPartsFallAccel, LW(10), 1, FLOAT(1.0f))
    CALL(btlevtcmd_GetPartsPos, LW(10), 1, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_TransStageFloorPosition, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(2), 30)
    CALL(btlevtcmd_JumpPartsPosition, LW(10), 1, LW(2), LW(3), LW(4), 20, -1)
    CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(2), 15)
    CALL(btlevtcmd_JumpPartsPosition, LW(10), 1, LW(2), LW(3), LW(4), 10, -1)
#endif
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_KO, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LIFE_SHROOM, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Death of the Red Chomp: it spins its body parts around quickly with the defeat sound, puffs smoke,
 * pays out its coins and EXP (StoreCoin and StoreExp) and a star-point effect,
 * then spins the parts for 30 more frames and removes the unit (KillUnit mode 2,
 * or 0 when the hit has damage-code bit 1024).
 */
static EVT_BEGIN(dead_event)
    SET_VALUE(LW(0), 48)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LABEL(10)
    WAIT_FRAMES(1)
    SET_VALUE(LW(11), 1)
    LOOP(9)
        CALL(btlevtcmd_AddPartsRotate, LW(10), LW(11), 0, -8, 0)
        ADD(LW(11), 1)
    END_LOOP
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(10)
    END_IF
    SET_VALUE(LW(11), 1)
    LOOP(9)
        CALL(btlevtcmd_SetPartsRotate, LW(10), LW(11), 0, 0, 0)
        ADD(LW(11), 1)
    END_LOOP
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetCoin, LW(10), LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
    ADD(LW(2), 10)
    ADD(LW(1), 30)
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
    SET_VALUE(LW(11), 1)
    LOOP(9)
        CALL(btlevtcmd_SetPartsRotateOffset, LW(10), LW(11), 0, 0, 0)
        ADD(LW(11), 1)
    END_LOOP
    SET_VALUE(LW(0), 30)
    LABEL(20)
    WAIT_FRAMES(1)
    SET_VALUE(LW(11), 1)
    LOOP(9)
        CALL(btlevtcmd_AddPartsRotate, LW(10), LW(11), 3, 0, 0)
        ADD(LW(11), 1)
    END_LOOP
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetBackItem, LW(10))
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

/**
 * Attack event of the Red Chomp: uses an enemy item if one fits,
 * otherwise picks a target (BATTLE_FLAG_FIRST_ATTACK uses the first-strike target),
 * hops twice on the spot barking, then lunges at the target on its chain
 * and bites (damage with weapon_wanwan_attack).
 * A miss falls short and it pulls back; a hit shakes the camera first.
 * A confused unit with no target runs subsetevt_confuse_flustered. It always ends back in the wait event.
 */
static EVT_BEGIN(attack_event)
    // Choose the target: the First Strike target if the battle opened with one,
    // otherwise it may use an item or pick a normal target.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_wanwan_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_wanwan_attack), LW(3), LW(4))
    END_IF
    // No target left: a confused Red Chomp is flustered; either way it ends its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The attack is announced and the Chomp turns toward the target; its idle animation stops.
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_BARK_VOLUME, 127)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_BARK_VOLUME, LW(14))
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_wanwan_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_wanwan_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangePartsFaceDirection, BTL_UNIT_SELF, 1, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_IDLE, 0)
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_SELF)
    // The camera frames the Chomp and its target.
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_A_1"))
    // The Chomp hops twice on the spot, barking.
    LOOP(2)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 20, 0, FLOAT(0.69921875f))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT1"), LW(14), 0, EVT_NULLPTR)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT3"), LW(14), 0, EVT_NULLPTR)
            WAIT_FRAMES(10)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT2"), LW(14), 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 20, -1)
    END_LOOP
    // It rears back on its chain, then lunges at the target with a bark.
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(20)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_S_1A"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_ATTACK1"), LW(14), 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 30, 0, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 30, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_A_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_ATTACK2"), LW(14), 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(1), 10)
    IF_INT_LESS(LW(1), 0)
        SET_VALUE(LW(1), 0)
    END_IF
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 0, FLOAT(16.0f), FLOAT(0.0f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), LW(1), 10, 0, -1)
    // Check how the target defends against the bite.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_wanwan_attack), 0, LW(5))
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
    // The target dodged: the Chomp falls short and pulls back in.
    LABEL(90)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT1"), LW(14), 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_S_1A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 0, FLOAT(8.0f), FLOAT(0.0f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0, -1)
    GOTO(98)
    // The bite lands: the camera shakes, the damage is dealt and the Chomp pulls back in.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_wanwan_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_wanwan_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT1"), LW(14), 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_S_1A"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 0, FLOAT(8.0f), FLOAT(0.25f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0, -1)
    GOTO(98)
    // The camera returns and the Chomp goes back to its idle animation.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    LABEL(99)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_IDLE, 1)
    CALL(btlevtcmd_ChangePartsFaceDirection, BTL_UNIT_SELF, 1, -1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Idle behaviour of the Red Chomp, chosen by status: asleep (status 1) it rocks slowly in "WAN_N_1";
 * stopped or frozen (2, 9) it stays in "WAN_Y_1" making occasional sounds;
 * confused, poisoned or dizzy (5, 4, 3) it hops in a looping series of landings;
 * otherwise it hops in place in a similar loop with its barking poses.
 * The loops run as sibling events with the bark sounds from wait_sound_event1 and wait_sound_event2.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_CHAIN_MODE, 0)
    // Asleep: the Red Chomp sways slowly from side to side in its sleeping pose.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_SLEEP, LW(15))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_CHAIN_MODE, 2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_N_1"))
        CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 1, 0, 10, 0)
        BEGIN_SIBLING_EVENT
            LABEL(1)
            CALL_CHILD(sound_gensui_event)
            CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 1, 0, 0, 0)
            WAIT_FRAMES(20)
            LOOP(10)
                WAIT_FRAMES(4)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 1, 0, 0, 1)
            END_LOOP
            LOOP(10)
                WAIT_FRAMES(4)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 1, 0, 0, -1)
            END_LOOP
            GOTO(1)
        END_SIBLING_EVENT
        GOTO(98)
    END_IF
    // Stopped or frozen: it stays still in its stunned pose, making an occasional sound.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_STOP, LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_FREEZE, LW(15))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_CHAIN_MODE, 2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_Y_1"))
        BEGIN_SIBLING_EVENT
            LABEL(5)
            CALL_CHILD(sound_gensui_event)
            CALL(evt_sub_random, 20, LW(0))
            WAIT_FRAMES(LW(0))
            GOTO(5)
        END_SIBLING_EVENT
        GOTO(98)
    END_IF
    // Confused, poisoned or dizzy: it keeps hopping in place in a looping series of landings,
    // barking out of time.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CONFUSE, LW(13))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_POISON, LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DIZZY, LW(15))
    OR(LW(15), LW(13))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        BEGIN_SIBLING_EVENT
            LABEL(3)
            CALL_CHILD(sound_gensui_event)
            CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
            CALL(evt_sub_random, 20, LW(0))
            WAIT_FRAMES(LW(0))
            SET_VALUE(LW(10), 15)
            SPAWN_EVENT(wait_sound_event1)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 30, 0, FLOAT(0.25f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 30, 0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
            SET_VALUE(LW(10), 10)
            SPAWN_EVENT(wait_sound_event2)
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
            CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 20, 0, FLOAT(0.19921875f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 20, 0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
            SET_VALUE(LW(10), 7)
            SPAWN_EVENT(wait_sound_event2)
            CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
            CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 15, 0, FLOAT(0.39941406f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 15, 0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
            SET_VALUE(LW(10), 7)
            SPAWN_EVENT(wait_sound_event2)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 15, 0, FLOAT(0.19921875f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 15, 0)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
            GOTO(3)
        END_SIBLING_EVENT
        GOTO(98)
    END_IF
    // Otherwise it keeps hopping in place, alternating barking poses with each landing.
    BEGIN_SIBLING_EVENT
        LABEL(4)
        CALL_CHILD(sound_gensui_event)
        CALL(evt_sub_random, 20, LW(0))
        WAIT_FRAMES(LW(0))
        SET_VALUE(LW(10), 15)
        SPAWN_EVENT(wait_sound_event1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_A_1"))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 30, 0, FLOAT(0.25f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 30, 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
        SET_VALUE(LW(10), 10)
        SPAWN_EVENT(wait_sound_event2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_S_1A"))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 20, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 20, 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
        SET_VALUE(LW(10), 7)
        SPAWN_EVENT(wait_sound_event2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_A_1"))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 15, 0, FLOAT(0.39941406f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), 0, LW(2), 15, 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
        SET_VALUE(LW(10), 7)
        SPAWN_EVENT(wait_sound_event2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("WAN_S_1A"))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 1, 15, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 15, 0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_LANDING1"), LW(11), 0, EVT_NULLPTR)
        GOTO(4)
    END_SIBLING_EVENT
    GOTO(98)
    LABEL(98)
    LABEL(99)
    WAIT_FRAMES(1)
    GOTO(99)
    RETURN
EVT_END()

/**
 * Lowers the Red Chomp's sound volume in unit work 1 to 70% of its value each call,
 * with a floor of 32 ("gensui" is attenuation); wait_event uses it so the idle barks fade.
 */
static EVT_BEGIN(sound_gensui_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_BARK_VOLUME, LW(11))
    MULTIPLY_FLOAT(LW(11), FLOAT(0.69921875f))
    IF_INT_LESS(LW(11), 32)
        SET_VALUE(LW(11), 32)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BURST_WANWAN_BARK_VOLUME, LW(11))
    RETURN
EVT_END()

/**
 * Plays the first two bark sounds of a hop at the unit's current volume (LW(11)),
 * then the third after LW(10) frames.
 */
static EVT_BEGIN(wait_sound_event1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT1"), LW(11), 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT3"), LW(11), 0, EVT_NULLPTR)
    WAIT_FRAMES(LW(10))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT2"), LW(11), 0, EVT_NULLPTR)
    RETURN
EVT_END()

/** Plays the fourth bark sound ("SFX_ENM_WAN_WAIT4") after LW(10) frames, at the unit's current volume (LW(11)). */
static EVT_BEGIN(wait_sound_event2)
    WAIT_FRAMES(LW(10))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_WAN_WAIT4"), LW(11), 0, EVT_NULLPTR)
    RETURN
#if VERSION <= VERSION_DEMO_US
EVT_END()
#else
EVT_END_PAD()
#endif

/**
 * Per-frame script helper (chain_event) that lays out the Red Chomp's chain; args[0] = unit.
 * It keeps the stake (part 9) 20 units behind the chomp.
 * With unit work 2 at 2 it records each link's offset from the stake in the parts' work and switches to 1;
 * at 1 the links (parts 1 to 8) keep that recorded shape.
 * Otherwise the links hang between the head (part 1, held below y = 110 in JP and later) and the stake:
 * link 2 sits on the head, and the links are pulled toward each other from both ends at a fixed spacing (the
 * distance over 8, over 7 up to the US demo, at least 10),
 * sagging by 300 / spacing squared and never below the floor.
 */
static USER_FUNC(chain_main) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id;
    BattleUnit* unit;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 len;
    f32 sag;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    BtlUnit_SetPartsPos(BtlUnit_GetPartsPtr(unit, 9), x - 20.0f * unit->faceDirection, y, z);
    // 2: remember the chain's shape relative to the stake
    if (unit->work[UW_BURST_WANWAN_CHAIN_MODE] == 2) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x, &y, &z);
        for (i = 8; i >= 1; i--) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
            part->work[0] = x2 - x;
            part->work[1] = y2 - y;
        }
        unit->work[UW_BURST_WANWAN_CHAIN_MODE] = 1;
    }
    // 1: keep that shape
    if (unit->work[UW_BURST_WANWAN_CHAIN_MODE] == 1) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x, &y, &z);
        for (i = 8; i >= 1; i--) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x + part->work[0], y + part->work[1], z);
        }
        return EVT_RETURN_DONE;
    }
    // otherwise hang the links between the chomp and the stake
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 1), &x1, &y1, &z1);
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 9), &x2, &y2, &z2);
    dx = x1 - x2;
    dy = y1 - y2;
    dz = z1 - z2;
#if VERSION <= VERSION_DEMO_US
    len = (f32)sqrt(dx * dx + dy * dy + dz * dz) / 7;
#else
    len = (f32)sqrt(dx * dx + dy * dy + dz * dz) / 8;
#endif
    if (len < 10.0f) {
        len = 10.0f;
    }
    sag = 300.0f / (len * len);
#if VERSION >= VERSION_JP
    part = BtlUnit_GetPartsPtr(unit, 1);
    BtlUnit_GetPartsPos(part, &x, &y, &z);
    if (y > 110.0f) {
        y = 110.0f;
    }
    BtlUnit_SetPartsPos(part, x, y, z);
#endif
    BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, 1), &x, &y, &z);
    x += -(unit->faceDirection * 16);
    y += 16.0f;
    BtlUnit_SetPartsPos(BtlUnit_GetPartsPtr(unit, 2), x, y, z);
#if VERSION <= VERSION_DEMO_US
    for (i = 2; i <= 6; i++) {
#else
    for (i = 2; i <= 7; i++) {
#endif
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, i), &x1, &y1, &z1);
        part = BtlUnit_GetPartsPtr(unit, i + 1);
        BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
        y2 -= sag;
        dx = x1 - x2;
        dy = y1 - y2;
        dz = z1 - z2;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        x2 += dx * t;
        y2 += dy * t;
        z2 += dz * t;
        if (y2 < 0.0f) {
            y2 = 0.0f;
        }
        BtlUnit_SetPartsPos(part, x2, y2, z2);
    }
    for (i = 9; i >= 3; i--) {
        BtlUnit_GetPartsPos(BtlUnit_GetPartsPtr(unit, i), &x1, &y1, &z1);
        part = BtlUnit_GetPartsPtr(unit, i - 1);
        BtlUnit_GetPartsPos(part, &x2, &y2, &z2);
        y2 -= sag;
        dx = x1 - x2;
        dy = y1 - y2;
        dz = z1 - z2;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        x2 += dx * t;
        y2 += dy * t;
        z2 += dz * t;
        if (y2 < 0.0f) {
            y2 = 0.0f;
        }
        BtlUnit_SetPartsPos(part, x2, y2, z2);
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper run by init_event to set up the Red Chomp's chain;
 * args[0] = unit: puts the chain links (parts 2 to 7) on the chomp with the WAN_S_1B animation,
 * and part 8 and the stake (part 9, animation WAN_Z_2) 20 units behind it.
 */
static USER_FUNC(chain_init) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id;
    BattleUnit* unit;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    // the chain links all start at the chomp
    for (i = 2; i <= 7; i++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        BtlUnit_SetPartsPos(part, x, y, z);
        BtlUnit_SetAnim(part, "WAN_S_1B");
    }
    part = BtlUnit_GetPartsPtr(unit, 8);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_S_1B");
    part = BtlUnit_GetPartsPtr(unit, 9);
    BtlUnit_SetPartsPos(part, x - 20.0f * unit->faceDirection, y, z);
    BtlUnit_SetAnim(part, "WAN_Z_2");
    return EVT_RETURN_DONE;
}
