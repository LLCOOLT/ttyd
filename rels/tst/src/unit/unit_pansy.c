// Battle unit Crazee Dayzee (`pansy`): tst.rel's copy of rels/gra/src/unit/unit_pansy.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_map.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_sub.h"
#include "version.h"

BattleUnitKind unit_pansy;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
BattleWeapon weapon_pansy_attack;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static EvtWord init_event[21];
static EvtWord damage_event[10];
#if VERSION <= VERSION_DEMO_US
static EvtWord song_event[298];
#else
static EvtWord song_event[300];
#endif
static EvtWord escape_event[96];
static EvtWord wait_event[6];

/**
 * Unit definition of the Crazee Dayzee: 7 HP, level 16, 1 part, with its sounds, init script and data table.
 */
BattleUnitKind unit_pansy = {
    69,
    "btl_un_pansy",
    7,
    0,
    1,
    1,
    16,
    0,
    2,
    70,
    1,
    70,
    9999,
    22,
    32,
    5,
    32,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    11.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    11.0f,
    0.0f,
    0.0f,
    6.0f,
    20.8f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    22.0f,
    32.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PANSY_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of the Crazee Dayzee: none, so it takes full damage from every kind of attack. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type modifiers of the Crazee Dayzee: none, no special weakness or immunity. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of the Crazee Dayzee (100% is the normal chance): resists Sleep 95%, Stop 30%, Dizzy
 * 30%, Confusion 30%, Freeze 30%, Tiny 30%, Attack Down 30%, Defense Down 30%, Allergic 30%, Gale Force 80%,
 * Slow 30% and instant KO 30%.
 */
static StatusVulnerability regist = {95, 30, 30, 100, 30, 100, 100, 30, 100, 30, 100, 30, 100, 30, 30, 100, 80, 100, 30, 100, 100, 30};
#else
static StatusVulnerability regist = {95, 30, 30, 100, 50, 100, 100, 30, 100, 30, 100, 30, 100, 30, 30, 100, 80, 100, 30, 100, 100, 30};
#endif

/**
 * Body of the Crazee Dayzee: one targetable part, the model `c_pansy`, with its hit box, defence tables and
 * pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_pansy", "c_pansy", 0.0f, 0.0f, 0.0f, 0.0f, 29.0f, 0.0f, 0.0f, 34.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/**
 * Attack data of the Crazee Dayzee's lullaby: hits every opposing unit for 2 damage, ignoring the target's
 * defence; may inflict Sleep (50%, 5 turns).
 */
BattleWeapon weapon_pansy_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_US
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
#if VERSION >= VERSION_US
    50, // sleepChance
#else
    75, // sleepChance
#endif
    5, // sleepTime
    0, 0, 0, 0, 0, 0, 0, 0, // stopChance..confuseChance
    0, 0, 0, 0, 0, 0, 0, 0, // confuseTime..freezeChance
    0, 0, 0, 0, 0, 0, 0, 0, // freezeTime..defChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeTime..fastTime
    0, 0, 0, 0, 0, 0, 0, 0, // slowChance..invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Attack AI of the Crazee Dayzee: uses an enemy item if it has one.
 * At 1 HP or less it always runs away (escape_event);
 * otherwise it sings its lullaby 70% of the time and runs away 30% of the time.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        GOTO(10)
    END_IF
    SET_VALUE(LW(0), 70)
    ADD(LW(0), 30)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 70)
        SET_VALUE(LW(9), PTR(&weapon_pansy_attack))
        CALL_CHILD(song_event)
        GOTO(99)
    END_IF
    LABEL(10)
    CALL_CHILD(escape_event)
    GOTO(99)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Pose table of the Crazee Dayzee: its 18 battle poses (status, hurt and action) and the animation each one
 * plays; the idle animation is `PAN_S_1`.
 */
static PoseTableEntry pose_table[] = {
    {1, "PAN_N_1"},
    {2, "PAN_Y_1"},
    {9, "PAN_Y_1"},
    {5, "PAN_K_1"},
    {4, "PAN_X_1"},
    {3, "PAN_X_1"},
    {BTL_POSE_NORMAL, "PAN_S_1"},
    {29, "PAN_Q_1"},
    {30, "PAN_Q_1"},
    {31, "PAN_S_1"},
    {BTL_POSE_DAMAGE, "PAN_D_1"},
    {50, "PAN_A_1"},
    {BTL_POSE_RUN, "PAN_R_1"},
    {BTL_POSE_WALK, "PAN_W_1"},
    {BTL_POSE_DANGER, "PAN_X_1"},
    {BTL_POSE_PERIL, "PAN_X_1"},
    {BTL_POSE_TALK, "PAN_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PAN_S_1"},
};

/** Data table of the Crazee Dayzee: event 48 does nothing (btldefaultevt_Dummy). */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Battle init script for the Crazee Dayzee: installs the wait, attack,
 * damage and confusion handlers and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage handler: selects this unit (-2) and its part 1
 * and runs the shared default damage reaction (btldefaultevt_Damage).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * The Crazee Dayzee's lullaby, aimed at every opposing target:
 * darkens the screen (map blend 255 to 192), sings with music-note effects for 120 frames (60 + 60 in the US
 * demo) and then checks each target in turn, showing avoid animations
 * or applying the attack (it can put them to sleep). Then the screen brightens back to normal.
 * A flustered (confused) unit with no target runs the confused subset instead.
 */
static EVT_BEGIN(song_event)
    // Picks the target: the preset first-attack target when battle flag 2 is set, otherwise a random opposing unit;
    // with no target it does nothing (or is flustered when confused).
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Declares the lullaby and pays its cost, turning toward the party.
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // The stage dims and takes on a blue tint as the Crazee Dayzee starts to sing.
    SET_VALUE(LW(0), 255)
    SET_VALUE(LW(1), 255)
    LOOP(0)
        IF_INT_LESS(LW(0), 192)
            BREAK_LOOP
        END_IF
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(1), 255)
        SUBTRACT(LW(0), 2)
        WAIT_FRAMES(1)
    END_LOOP
    // It sings (pose 50, song sound) and a stream of music notes drifts out of it every 12 frames.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PANSY_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    BEGIN_SIBLING_EVENT
        LOOP(10)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            IF_INT_LESS(LW(15), 0)
                CALL(evt_eff64, STRING(""), STRING("onpu_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
            ELSE
                CALL(evt_eff64, STRING(""), STRING("onpu_n64"), 2, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
            END_IF
            WAIT_FRAMES(12)
        END_LOOP
    END_SIBLING_EVENT
    // After about two seconds the song reaches the party.
#if VERSION <= VERSION_DEMO_US
    WAIT_FRAMES(60)
    WAIT_FRAMES(60)
    SET_VALUE(LW(6), 0)
#else
    WAIT_FRAMES(120)
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
#endif
    // Goes through every opposing unit in turn and works out whether the song affects it.
    LABEL(10)
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
        GOTO(97)
        CASE_END
    END_SWITCH
    // Miss branch: this unit is unaffected.
    LABEL(90)
    GOTO(97)
    // Hit branch: reads the defence result (once, for the first unit) and applies the song's effect.
    LABEL(91)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(97)
    // Next target, until all have been checked.
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(10)
    // The stage light fades back to normal.
    LABEL(98)
    SET_VALUE(LW(0), 192)
    SET_VALUE(LW(1), 255)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(1), 255)
        ADD(LW(0), 2)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_blend_off, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The Crazee Dayzee returns to its idle pose.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    WAIT_MS(500)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Flees the battle: turns around, jumps back and dashes off the right side of the stage (x = 300) at speed 9
 * with a blur trail, then removes the unit from the battle without rewards (KillUnit mode 0).
 */
static EVT_BEGIN(escape_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PANSY_ESCAPE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PAN_E_1"))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 180, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_SetPartsBlur, BTL_UNIT_SELF, 1, 255, 255, 255, 255, 100, 100, 100, 100, 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_BLUR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PANSY_ESCAPE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(20.0f), -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PANSY_ESCAPE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(9.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, 300, LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_BLUR)
    WAIT_MS(500)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Wait (idle) event: refreshes the body animation (part 1) from the unit's pose table
 * so it matches the current state, then returns; the battle system runs it whenever the unit is idle.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
