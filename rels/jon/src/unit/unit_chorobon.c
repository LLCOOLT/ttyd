// Pit of 100 Trials battle unit: the Fuzzy (`chorobon`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"

BattleUnitKind unit_chorobon;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_chorobon_drain_attack;
static BattleWeapon weapon_chorobon_drain_attack_biribiri_counterd;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[14];
static PoseSoundTiming pose_sound_timing_table[4];
static EvtWord init_event[31];
static EvtWord damage_event[10];
static EvtWord counter_damage_event[41];
static EvtWord return_event[24];
static EvtWord drain_attack_event[887];
static EvtWord wait_event[6];

/** Unit data of the Fuzzy: stats, sounds, attributes, parts, init script and data table. */
BattleUnitKind unit_chorobon = {
    UNIT_FUZZY,
    "btl_un_chorobon",
    3,
    0,
    1,
    1,
    8,
    0,
    1,
    70,
    0,
    60,
    9999,
    28,
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
    14.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    14.0f,
    0.0f,
    0.0f,
    9.0f,
    20.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    28.0f,
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
    "SFX_ENM_CHORO1_DAMAGED1",
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

/** Damage reduction of the Fuzzy: none, every attack type does full damage. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element response of the Fuzzy: none, every attack type is treated normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/** Status vulnerability of the Fuzzy (percent, 0 is immune): every status effect can land. Demo values. */
static StatusVulnerability regist = {100, 100, 90, 100, 90, 100, 100, 75, 100, 80, 100, 80, 100, 75, 75, 95, 95, 100, 75, 100, 100, 100};
#else
/**
 * Status vulnerability of the Fuzzy (percent, 0 is immune): every status effect can land. Released game
 * values.
 */
static StatusVulnerability regist = {95, 95, 90, 100, 95, 100, 100, 80, 100, 90, 100, 90, 100, 95, 70, 95, 90, 100, 90, 100, 100, 100};
#endif

/** Body part of the Fuzzy: hit position, size, defence tables and attributes. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_chorobon", "c_chorobon", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/** Attack data for the Fuzzy's drain attack: 1 damage. */
static BattleWeapon weapon_chorobon_drain_attack = {
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
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    0, // counterResistFlags
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

/** Attack script of the Fuzzy: after an item check it always uses its drain attack (drain_attack_event). */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_chorobon_drain_attack))
    CALL_CHILD(drain_attack_event)
    RETURN
EVT_END()

/**
 * Attack data for the Fuzzy's stand-in for a drain the target counters (electrified or Hold Fast): no
 * damage.
 */
static BattleWeapon weapon_chorobon_drain_attack_biribiri_counterd = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, 0, 0, // acHelpMsg..counterResistFlags
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

/** Pose table of the Fuzzy: battle pose types mapped to animation names. */
static PoseTableEntry pose_table[] = {
    {STATUS_SLEEP, "CBN_N_1"},
    {STATUS_STOP, "CBN_Y_1"},
    {STATUS_FREEZE, "CBN_Y_1"},
    {STATUS_CONFUSE, "CBN_K_1"},
    {STATUS_POISON, "CBN_X_1"},
    {STATUS_DIZZY, "CBN_X_1"},
    {BTL_POSE_NORMAL, "CBN_S_1"},
    {29, "CBN_Q_1"},
    {30, "CBN_Q_1"},
    {31, "CBN_S_1"},
    {BTL_POSE_DAMAGE, "CBN_D_1"},
    {50, "CBN_A_1"},
    {BTL_POSE_RUN, "CBN_R_1"},
    {BTL_POSE_WALK, "CBN_W_1"},
    {BTL_POSE_DANGER, "CBN_X_1"},
    {BTL_POSE_PERIL, "CBN_X_1"},
    {BTL_POSE_TALK, "CBN_T_1"},
    {BTL_POSE_STAY_DEFAULT, "CBN_S_1"},
};

/** Data table of the Fuzzy: event handlers keyed by tag (counter_damage_event). */
static BattleDataEntry data_table[] = {
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

/**
 * Hops the Fuzzy in steps towards (LW(5), LW(6), LW(7)), each step at most LW(8) units long,
 * squashing before and after every jump (SFX_ENM_CHORO1_LANDING1 on the last landing), until it arrives.
 */
static EVT_BEGIN(rabbit_move)
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    LABEL(0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(11), LW(5))
    SUBTRACT(LW(11), LW(0))
    SET_VALUE(LW(12), LW(11))
    IF_INT_LESS(LW(12), 0)
        MULTIPLY(LW(12), -1)
    END_IF
    IF_INT_GREATER(LW(12), LW(8))
        IF_INT_GREATER_OR_EQUAL(LW(11), 0)
            ADD(LW(0), LW(8))
        ELSE
            SUBTRACT(LW(0), LW(8))
        END_IF
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(6), LW(2), 0, -1)
        LOOP(2)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
            WAIT_FRAMES(1)
        END_LOOP
        GOTO(0)
    ELSE
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(5), LW(6), LW(7), 0, -1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        LOOP(2)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_IF
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.15917969f), FLOAT(0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/** Sound table of the Fuzzy: the sound each animation plays while it runs. */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"CBN_S_1", 0.5833333f, NULL, "SFX_ENM_CHORO1_MOVE1", 0, 1},
    {"CBN_S_1", 0.8333333f, NULL, "SFX_ENM_CHORO1_WAIT2", 0, 1},
    {"CBN_S_1", 1.5833334f, NULL, "SFX_ENM_CHORO1_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init script of the Fuzzy: registers its wait, attack, damage and confusion handlers,
 * sets the pose sound timing table and its jump sound (SFX_ENM_CHORO1_MOVE1).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_MOVE1"), 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage script of the Fuzzy: runs the default damage handling on itself. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Counter-damage script of the Fuzzy: resets its scale, runs the shared counter-damage handling and,
 * unless the damage code is 512 without 2048, hops back home (return_event).
 */
static EVT_BEGIN(counter_damage_event)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    CALL_CHILD(subsetevt_counter_damage)
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

/** Hops the Fuzzy back to its home position in steps of up to 40 units (rabbit_move). */
static EVT_BEGIN(return_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(4.0f), FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    SET_VALUE(LW(8), 40)
    CALL_CHILD(rabbit_move)
    RETURN
EVT_END()

/**
 * The Fuzzy's drain attack: it hops up to the target, climbs onto it and latches on (CBN_A_2),
 * shaking for 90 frames, then drops off.
 * Each time it connects it recovers HP equal to the damage dealt, with the "recovery" effect;
 * if the weapon in LW(9) is not the HP drain weapon it recovers FP instead.
 * When the target's counter check gives 14 (electrified) or 17 (Hold Fast) it does not latch on:
 * it makes the damage
 * check with the no-damage weapon_chorobon_drain_attack_biribiri_counterd, so only the counter lands,
 * and the script
 * ends there. Otherwise it then hops home.
 */
static EVT_BEGIN(drain_attack_event)
    // Pick a target; a confused Fuzzy with nobody to attack gets flustered.
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_chorobon_drain_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_chorobon_drain_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_chorobon_drain_attack))
    // Declare the attack.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_chorobon_drain_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    // The Fuzzy hops toward the target in short steps.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(4.0f), FLOAT(0.5996094f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(5), LW(6), LW(7))
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(5), 50)
    SET_VALUE(LW(8), 50)
    CALL_CHILD(rabbit_move)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 350)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    // One last big jump up onto the target.
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 60, 0, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
    SUBTRACT(LW(1), 10)
    SUBTRACT(LW(2), 2)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    // Find out whether it manages to latch on.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_chorobon_drain_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Miss or dodge: it bounces off the target, lands and sits there for a second.
    LABEL(90)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(3.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 5)
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(1.5f), FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 30)
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("CBN_N_1"))
    WAIT_MS(1000)
    GOTO(98)
    // Hit. If the target would counter (it is electrified or Hold Fast) the Fuzzy only sets off the counter
    // and drains nothing.
    LABEL(91)
    SET_VALUE(LF(0), 0)
    CALL(btlevtcmd_PreCheckCounter, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_chorobon_drain_attack), 256, LW(5))
    IF_INT_EQUAL(LW(5), 17)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LW(5), 14)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_chorobon_drain_attack))
        SET_VALUE(LW(9), PTR(&weapon_chorobon_drain_attack_biribiri_counterd))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
        RETURN
    END_IF
    // It latches on and the target is shaken from side to side.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_ATTACK1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetBodyId, LW(3), LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, LW(3), LW(0), 37)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 89)
        SET_VALUE(LW(1), 1)
        SET_VALUE(LW(2), 2)
        SET_VALUE(LW(5), LW(2))
        LABEL(20)
        SUBTRACT(LW(5), 1)
        IF_INT_LESS_OR_EQUAL(LW(5), 0)
            SET_VALUE(LW(5), LW(2))
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(1), 1)
            ELSE
                SET_VALUE(LW(1), 0)
            END_IF
        END_IF
        CALL(btlevtcmd_SetDispOffset, LW(3), LW(1), 0, 0)
        WAIT_FRAMES(1)
        SUBTRACT(LW(0), 1)
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            GOTO(20)
        END_IF
        CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_ATTACK1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(14), 20)
    IF_INT_EQUAL(LW(15), -1)
        SET_VALUE(LW(14), -20)
    END_IF
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(14))
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.5f))
    // It clings on and wriggles while it drains.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("CBN_A_2"))
    WAIT_FRAMES(90)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("CBN_R_2"))
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    LOOP(4)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, 0, FLOAT(-0.19921875f), 0)
    END_LOOP
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(0.19921875f), FLOAT(1.0f))
    LOOP(20)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.009765625f), FLOAT(0.049804688f), 0)
    END_LOOP
    WAIT_FRAMES(1)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    // It lets go and the damage is dealt.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_chorobon_drain_attack))
    SET_VALUE(LW(9), PTR(&weapon_chorobon_drain_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_GetHpDamage, LW(3), LW(10))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.5f), FLOAT(0.5f), 0)
    END_IF
    LOOP(4)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.07910156f), FLOAT(0.119140625f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.31933594f), FLOAT(-0.4794922f), 0)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.31933594f), FLOAT(0.4794922f), 0)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 10, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.15917969f), FLOAT(0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("CBN_W_1"))
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        LOOP(20)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.024414062f), FLOAT(-0.024414062f), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(1))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
        ADD(LW(6), 45)
        ADD(LW(7), 10)
        // It recovers the drained points with the recovery effect, then bounces away in a little flourish.
        IF_INT_EQUAL(LW(9), PTR(&weapon_chorobon_drain_attack))
            CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, LW(1), LW(10))
            CALL(evt_eff, STRING(""), STRING("recovery"), 7, LW(5), LW(6), LW(7), LW(10), 0, 0, 0, 0, 0, 0, 0)
        ELSE
            CALL(btlevtcmd_RecoverFp, BTL_UNIT_SELF, LW(1), LW(10))
            CALL(evt_eff, STRING(""), STRING("recovery"), 8, LW(5), LW(6), LW(7), LW(10), 0, 0, 0, 0, 0, 0, 0)
        END_IF
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_IF
    LOOP(2)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(1), 30)
        CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_CHORO1_ATTACK3"), 0, 0, -1, -1, 0, 0)
        LOOP(2)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 6, -2)
        WAIT_FRAMES(16)
        LOOP(2)
            CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, 0, 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 6, -2)
    END_LOOP
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(0.15917969f), FLOAT(-0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(2)
        CALL(btlevtcmd_AddScale, BTL_UNIT_SELF, FLOAT(-0.15917969f), FLOAT(0.23925781f), 0)
        WAIT_FRAMES(1)
    END_LOOP
    GOTO(98)
    // Hop back home.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 0)
    CALL_CHILD(return_event)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays the Fuzzy's idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
