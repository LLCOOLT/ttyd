// Battle unit Shady Koopa (`ura_noko`): tst.rel's copy of rels/jon/src/unit/unit_ura_noko.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "eff/eff_uranoko.h"
#include "battle/battle_sub.h"
#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"

// Unit work slots of the Shady Koopa (btlevtcmd_SetUnitWork / GetUnitWork, unit->work)
enum {
    UW_URA_NOKO_SPIN_DONE = 0,   // set to 1 to stop the shell-spin loop of the attack (it then resets its rotation)
    UW_URA_NOKO_SPIN_SPEED = 1,  // degrees per frame the spinning shell turns by
    UW_URA_NOKO_AURA_EFFECT = 2, // dark aura effect (effUranoko EffectEntry*)
};

static USER_FUNC(eff_aura);

BattleUnitKind unit_ura_noko;
static PoseTableEntry pose_table[18];
#if VERSION <= VERSION_DEMO_JP
static PoseTableEntry pose_table_turn[15];
#else
static PoseTableEntry pose_table_turn[17];
#endif
static BattleDataEntry data_table[3];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_nokonoko_attack;
static BattleWeapon weapon_ura_noko_ura_attack;
static EvtWord init_event[41];
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[78];
static EvtWord attack_event[548];
static EvtWord ura_attack_event[560];
static EvtWord wait_event[6];

/**
 * Unit definition of the Shady Koopa: 8 HP and level 17, with its sizes, damage sounds, status vulnerability,
 * parts and init script.
 */
BattleUnitKind unit_ura_noko = {
    47,
    "btl_un_ura_noko",
    8,
    0,
    1,
    1,
    17,
    0,
    2,
    70,
    1,
    50,
    9999,
    36,
    40,
    -4,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    9.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    11.0f,
    24.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    36.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_NOKO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_REQUIRED_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/**
 * Pose table of the Shady Koopa: maps each battle pose (waiting, hurt, running...) to one of its NKT_*
 * animations.
 */
static PoseTableEntry pose_table[] = {
    {1, "NKT_N_1"},
    {2, "NKT_Y_1"},
    {9, "NKT_Y_1"},
    {5, "NKT_K_1"},
    {4, "NKT_X_1"},
    {3, "NKT_X_1"},
    {BTL_POSE_NORMAL, "NKT_S_1"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_S_1"},
    {BTL_POSE_DAMAGE, "NKT_D_1"},
    {50, "NKT_A_1"},
    {BTL_POSE_RUN, "NKT_R_1"},
    {BTL_POSE_WALK, "NKT_W_1"},
    {BTL_POSE_DANGER, "NKT_X_1"},
    {BTL_POSE_PERIL, "NKT_X_1"},
    {BTL_POSE_TALK, "NKT_T_1"},
    {BTL_POSE_STAY_DEFAULT, "NKT_S_1"},
};

/**
 * Pose table of the Shady Koopa while it is flipped on its back:
 * maps each battle pose (waiting, hurt, running...) to one of its NKT_* animations.
 */
static PoseTableEntry pose_table_turn[] = {
    {1, "NKT_N_2"},
    {2, "NKT_B_1"},
    {9, "NKT_B_1"},
    {5, "NKT_K_2"},
    {4, "NKT_K_2"},
    {3, "NKT_K_2"},
    {BTL_POSE_NORMAL, "NKT_S_2"},
    {29, "NKT_Q_1"},
    {30, "NKT_Q_1"},
    {31, "NKT_D_1"},
    {BTL_POSE_DAMAGE, "NKT_D_1"},
#if VERSION >= VERSION_JP
    {BTL_POSE_RUN, "NKT_R_1"},
    {BTL_POSE_WALK, "NKT_W_1"},
#endif
    {BTL_POSE_DANGER, "NKT_K_2"},
    {BTL_POSE_PERIL, "NKT_K_2"},
    {BTL_POSE_TALK, "NKT_S_2"},
    {BTL_POSE_STAY_DEFAULT, "NKT_S_2"},
};

/**
 * Data table of the Shady Koopa: reaction scripts for being flipped over;
 * a First Strike on it triggers nothing special.
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/** Defence of the Shady Koopa: 1 against every kind of hit. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element modifiers of the Shady Koopa: none, no element is special to it. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Defence of the Shady Koopa while it is flipped on its back: none, every hit does its full damage. */
static BattleUnitDefense defence_turn = {0};

#if VERSION <= VERSION_DEMO_JP
/** Status vulnerability of the Shady Koopa in the demo builds: resists most statuses. */
static StatusVulnerability regist = {85, 90, 85, 100, 85, 100, 100, 85, 100, 85, 100, 85, 100, 85, 85, 90, 80, 100, 85, 100, 100, 95};
#else
/** Status vulnerability of the Shady Koopa in the retail builds: resists most statuses. */
static StatusVulnerability regist = {85, 90, 80, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 90, 80, 85, 80, 100, 80, 100, 100, 95};
#endif

/** Body part of the Shady Koopa: a single part using the c_uranoko model. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_ura_noko", "c_uranoko", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_SHELLED, 0, pose_table},
};

/** Attack data of the Shady Koopa's shell charge: 3 damage. */
static BattleWeapon weapon_nokonoko_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_JP
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
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

/** Attack data of the Shady Koopa's attack from its back: 6 damage; hits every target. */
static BattleWeapon weapon_ura_noko_ura_attack = {
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
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
#if VERSION <= VERSION_DEMO_JP
    COUNTER_RESIST_ALL, // counterResistFlags
#else
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
#endif
    TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
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
 * Init event of the Shady Koopa: registers its wait,
 * attack and damage events (attack_event also handles confusion), clears the overturned counter,
 * sets its run and walk sounds and starts waiting.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Shady Koopa: runs the default damage reaction (btldefaultevt_Damage) for its body part. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Data-table event 13: flips the Shady Koopa onto its back after a stomp-type hit.
 * Moves its hit offset 15 units down, switches to the overturned defence (0 DEF) and pose tables,
 * sets the flipped status flag and the overturned counter to 2,
 * plays SFX_ENM_INSIDE1 and bounces twice in place.
 */
static EVT_BEGIN(dmg_turn_event)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, -15, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_D_1"))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_S_2"))
    RETURN
EVT_END()

/**
 * Run instead of a normal attack while the Shady Koopa is on its back: counts the overturned counter down.
 * If it is still above 0 the Koopa attacks from its back (ura_attack_event);
 * at 0 it restores its normal defence and pose tables,
 * clears the flipped status flag and hops back onto its feet.
 */
static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(ura_attack_event)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("NKT_S_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_INSIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Unused (no table or event refers to it): a first-strike version of the shell attack that spins into the
 * first-attack target and always runs the damage check, then bounces off in two hops and walks home.
 */
static EVT_BEGIN(first_attack_event)
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_nokonoko_attack))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 40)
    WAIT_MS(100)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack event of the Shady Koopa. On its back it runs wakeup_event instead.
 * Otherwise it uses an item if it decides to, or picks the front-most target for its 3-damage shell attack (the
 * first-attack target on a first strike), tucks into its shell,
 * spins up and slides at the target with a smoke trail.
 * A miss slides past and hops back; a hit shakes the camera, damages the target and bounces off in two hops.
 * It then walks home.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        // If the Shady Koopa is on its back it spends the turn getting up instead of attacking.
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // First-strike battle: the target is already fixed; otherwise one is picked from the opposing party.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(30)
    ELSE
        // If the Shady Koopa holds an item, it uses that instead of attacking.
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_nokonoko_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_nokonoko_attack), LW(3), LW(4))
    END_IF
    // No target to attack: a confused Shady Koopa just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The camera frames the Shady Koopa and its target.
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_nokonoko_attack))
    // The Shady Koopa declares its shell charge.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 0)
    // It curls into its shell and starts to spin, faster in two steps.
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 40)
    WAIT_MS(100)
    // A trail of smoke kicks up behind it while it rolls at the target.
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    DELETE_EVENT(LW(13))
    // Check whether the attack will connect; a miss sends the target into its dodge.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // A miss: it rolls past the target, then jumps and turns back.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 10)
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    // A hit: the target takes the damage and the Shady Koopa bounces off it twice.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 1)
    GOTO(98)
    // The charge is over: it walks back to its place.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    // Turn finished: the Shady Koopa goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Shady Koopa's attack from its back (called from wakeup_event on the turn after it is flipped):
 * it spins round once, gathers a dark aura (eff_aura) while spinning faster,
 * then slides through every target in the row in turn with the 6-damage multi-target weapon,
 * each one dodging or taking the hit (the action-command defence is read on the first hit only).
 * It shoots off the right side of the screen and slides back home, still on its back.
 */
static EVT_BEGIN(ura_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // A target is picked from the opposing party.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_ura_noko_ura_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_ura_noko_ura_attack), LW(3), LW(4))
    // No target to attack: a confused Shady Koopa just flusters about, otherwise it skips its turn.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // The camera frames the Shady Koopa and its target.
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_ura_noko_ura_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_ura_noko_ura_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.5f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(27)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_2"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    // Lying on its back, it spins round once.
    LOOP(36)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 10, 0)
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 5)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_FRAMES(20)
    BEGIN_SIBLING_EVENT
        WAIT_MS(200)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(2), 10)
        // A dark aura gathers around it while it spins faster and faster (three speed-ups).
        CALL(eff_aura, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_URANOKO_MOVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 10)
    WAIT_MS(400)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 20)
    WAIT_MS(400)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_SPEED, 40)
    WAIT_MS(400)
    // It slides through every target in the row, one after another.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(evt_btl_camera_set_mode, 0, 0)
    // A smoke trail follows it as it starts to slide.
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_URANOKO_MOVE2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    SET_VALUE(LW(6), 0)
    LABEL(10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    // Check whether the attack will connect; a miss sends the target into its dodge.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_ura_noko_ura_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // A miss: that target dodges as it slides past.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    GOTO(97)
    // A hit: the target takes the damage (the action-command result is read on the first one only).
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_ura_noko_ura_attack))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_ura_noko_ura_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    // On to the next target in the row.
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 1)
    WAIT_MS(500)
    // It shoots off the right side of the screen.
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 250, LW(1), LW(2))
    // It slides back in to its place, still on its back, and bounces to a stop.
    LABEL(98)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_URANOKO_MOVE3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 1)
    DELETE_EVENT(LW(13))
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_URANOKO_MOVE4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_NOKO_SPIN_DONE, 1)
    WAIT_FRAMES(3)
    // Turn finished: the Shady Koopa goes back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Script helper called every frame: keeps the dark aura effect (effUranoko) on the unit,
 * creating it on the first call and following the unit's position and size.
 * Returns DONE when the effect is over, BLOCK while it lives.
 */
static USER_FUNC(eff_aura) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff;
    EffUranokoWork* work;
    f32 x, y, z;

    if (isFirstCall) {
        unit->work[UW_URA_NOKO_AURA_EFFECT] = (EvtWord)effUranokoEntry(0, 120, 0.0f, -1000.0f, 0.0f);
    }
    BtlUnit_GetPos(unit, &x, &y, &z);
    eff = (EffectEntry*)unit->work[UW_URA_NOKO_AURA_EFFECT];
    if (!(eff->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    work = eff->userdata;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->baseScale = unit->sizeMultiplier;
    return EVT_RETURN_BLOCK;
}

/** Wait event of the Shady Koopa: plays the idle pose from its current pose table (normal or overturned). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
