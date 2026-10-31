// unit_ura_pata: Shady Paratroopa (with Shady Koopa after it falls), battle unit.

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
#include "data_tables.h"
#include "manager/evtmgr_cmd.h"

// Unit work slots of the Shady Paratroopa.
enum {
    UW_URA_PATA_SPIN_STOP = 0,   // set to 1 to stop the shell spin loop of its attacks
    UW_URA_PATA_SPIN_SPEED = 1,  // degrees per frame the shell spin loop turns it
    UW_URA_PATA_AURA_EFFECT = 2, // the aura effect of its power-up (EffectEntry*, set by eff_aura)
};

static USER_FUNC(eff_aura);

BattleUnitKind unit_ura_pata;
static BattleWeapon weapon_patapata_attack;
static BattleUnitDefense defence_patapata;
static BattleUnitDefenseAttr defence_patapata_attr;
static StatusVulnerability regist_patapata;
static BattleUnitKindPart parts_patapata[1];
static PoseTableEntry pose_table_patapata[18];
static BattleDataEntry data_table_patapata[3];
static EvtWord init_event_patapata[26];
static EvtWord dmg_fall_event[189];
static EvtWord patapata_dmg_first_attack_pos[19];
static EvtWord attack_event_patapata[541];
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[3];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_nokonoko_attack;
static BattleWeapon weapon_ura_noko_ura_attack;
static EvtWord damage_event[10];
static EvtWord dmg_turn_event[78];
static EvtWord attack_event[548];
static EvtWord ura_attack_event[560];
static EvtWord wait_event[6];

/**
 * Unit data of the Shady Paratroopa: 8 HP and level 17, with its parts, status vulnerability, init event
 * and event data table.
 */
BattleUnitKind unit_ura_pata = {
    48,
    "btl_un_ura_pata",
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
    24.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    9.0f,
    6.0f,
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
    24.0f,
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
    "SFX_ENM_PATA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING | UNIT_ATTR_REQUIRED_FOR_CLEAR,
    &regist_patapata,
    1,
    parts_patapata,
    init_event_patapata,
    data_table_patapata,
};

/** Weapon record of the Shady Paratroopa's dive attack: 3 damage. */
static BattleWeapon weapon_patapata_attack = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    0, // counterResistFlags
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
 * Defense of the Shady Paratroopa against normal, fire, ice, explosion and electric attacks in its winged
 * form: 1, 1, 1, 1, 1.
 */
static BattleUnitDefense defence_patapata = {{1, 1, 1, 1, 1}};

/**
 * Defense of the Shady Paratroopa against normal, fire, ice, explosion and electric attacks in its winged
 * form: none, so it takes full damage from every element.
 */
static BattleUnitDefenseAttr defence_patapata_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Shady Paratroopa in its winged form (both early demos), as the percent chance each
 * status takes hold: resists 11 statuses (down to 85% of the normal chance); extra vulnerable to dizziness
 * and Gale Force.
 */
static StatusVulnerability regist_patapata = {90, 90, 110, 100, 85, 100, 100, 85, 100, 85, 100, 85, 100, 85, 85, 90, 110, 100, 85, 100, 100, 95};
#else
/**
 * Status vulnerability of the Shady Paratroopa in its winged form (the retail releases), as the percent
 * chance each status takes hold: resists 11 statuses (down to 80% of the normal chance); extra vulnerable
 * to dizziness.
 */
static StatusVulnerability regist_patapata = {85, 90, 110, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 90, 80, 85, 100, 100, 80, 100, 100, 95};
#endif

/**
 * Parts of the Shady Paratroopa in its winged form: a single body part (part 1, model c_uranoko), each
 * with its defense tables, attributes and pose table.
 */
static BattleUnitKindPart parts_patapata[] = {
    {1, "btl_un_ura_pata", "c_uranoko", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence_patapata, &defence_patapata_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WINGED | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_patapata},
};

/**
 * Pose table of the Shady Paratroopa in its winged form: maps each battle pose (idle, hurt, attacking and
 * so on) to its animation, named PTP_*.
 */
static PoseTableEntry pose_table_patapata[] = {
    {1, "PTP_N_1"},
    {2, "PTP_Y_1"},
    {9, "PTP_Y_1"},
    {5, "PTP_K_1"},
    {4, "PTP_X_1"},
    {3, "PTP_X_1"},
    {BTL_POSE_NORMAL, "PTP_S_1"},
    {29, "PTP_Q_1"},
    {30, "PTP_Q_1"},
    {31, "PTP_S_1"},
    {BTL_POSE_DAMAGE, "PTP_D_1"},
    {50, "PTP_A_1"},
    {BTL_POSE_RUN, "PTP_R_1"},
    {BTL_POSE_WALK, "PTP_W_1"},
    {BTL_POSE_DANGER, "PTP_X_1"},
    {BTL_POSE_PERIL, "PTP_X_1"},
    {BTL_POSE_TALK, "PTP_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PTP_S_1"},
};

/**
 * Event data table of the Shady Paratroopa in its winged form: scripts that replace the standard handling
 * for being knocked out of the air (tag 14) and the battle opening with a First Strike on it (tag 48).
 */
static BattleDataEntry data_table_patapata[] = {
    {14, dmg_fall_event},
    {48, patapata_dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Sound cues for the animations of the Shady Paratroopa: each entry plays a sound effect at a set time
 * within a pose, such as SFX_ENM_PATA_WAIT1.
 */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"PTP_S_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_W_1", 0.01f, NULL, "SFX_ENM_PATA_MOVE1", 0, 1},
    {"PTP_R_1", 0.01f, NULL, "SFX_ENM_PATA_MOVE1", 0, 1},
    {"PTP_N_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_K_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_A_3", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {"PTP_X_1", 0.01f, NULL, "SFX_ENM_PATA_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init script of the winged Koopa Paratroopa: registers its wait,
 * damage and flying attack handlers (attack_event_patapata) and the pose sound table for its wing flaps.
 */
static EVT_BEGIN(init_event_patapata)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_patapata))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_patapata))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Fall reaction when the Shady Paratroopa loses its wings:
 * it drops with SFX_ENM_FALL1 and becomes a Shady Koopa, taking the walking data tables,
 * attack and walk/run sounds; after a hit of at most 1 HP of damage it lands on its feet,
 * otherwise it is also flipped (dmg_turn_event).
 */
static EVT_BEGIN(dmg_fall_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_WINGED)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_AnimeChangePoseDirect, LW(10), LW(11), STRING("NKT_D_1"))
    CALL(btlevtcmd_ChangeKind, LW(10), 47)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_KIND_CHANGED)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHpDamageCount, LW(10), LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        WAIT_FRAMES(30)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
        CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
        CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
        CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
        RETURN
    END_IF
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3R"), 0, 3, 3)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE3L"), STRING("SFX_ENM_NOKO_MOVE3L"), 0, 6, 6)
    CALL(btlevtcmd_SetOverTurnCount, BTL_UNIT_SELF, 0)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL_CHILD(dmg_turn_event)
    RETURN
EVT_END()

/** Position event for a first strike on the Paratroopa: sets its height to 10 and waits for the attack to finish. */
static EVT_BEGIN(patapata_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * The Paratroopa's flying attack: it uses an item or picks a target,
 * flaps up (PTP_A_1, PTP_A_4) and dives at it with SFX_ENM_PATA_ATTACK1;
 * a miss makes it fly past, a hit applies the damage, and it returns to its stance.
 */
static EVT_BEGIN(attack_event_patapata)
    // Use the target of the opening first attack if there was one; otherwise use an enemy item, or choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(50)
    ELSE
        CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(LW(0))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_patapata_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_patapata_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_patapata_attack))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_patapata_attack))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 45)
    ADD(LW(1), 30)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.5f))
    // The Paratroopa flies up and around to a spot behind its target.
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    // It turns, hovers and winds up with a flap of its wings.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTP_A_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 6)
    ADD(LW(1), 6)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    WAIT_FRAMES(11)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTP_A_4"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    // It swoops in on the target; find out how the target reacts.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), 1048832, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), 256, LW(5))
    END_IF
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
    // The swoop missed: the Paratroopa flies past the target and loops back around.
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    SET_VALUE(LW(1), 20)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    GOTO(98)
    // The swoop connects: the damage is applied and the Paratroopa flutters away.
    LABEL(91)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_patapata_attack))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), 1048832, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patapata_attack), 256, LW(5))
    END_IF
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATA_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    ADD(LW(1), 30)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(24)
            SUBTRACT(LW(0), 45)
            IF_INT_LESS(LW(0), 0)
                ADD(LW(0), 360)
            END_IF
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 20)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    END_INLINE_EVENT
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 30, 0, 0, 0)
    WAIT_FRAMES(10)
    GOTO(98)
    // It flies back to its home position.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Pose table of the Shady Paratroopa: maps each battle pose (idle, hurt, attacking and so on) to its
 * animation, named NKT_*.
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
 * Pose table of the Shady Paratroopa while it is flipped onto its back: maps each battle pose (idle, hurt,
 * attacking and so on) to its animation, named NKT_*.
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
 * Event data table of the Shady Paratroopa: scripts that replace the standard handling for being flipped
 * over by a stomp (tag 13).
 */
static BattleDataEntry data_table[] = {
    {13, dmg_turn_event},
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Defense of the Shady Paratroopa against normal, fire, ice, explosion and electric attacks: 1, 1, 1, 1,
 * 1.
 */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Damage-type reactions of the Shady Paratroopa: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {0};

/**
 * Defense of the Shady Paratroopa against normal, fire, ice, explosion and electric attacks while it is
 * flipped onto its back: none, so it takes full damage from every element.
 */
static BattleUnitDefense defence_turn = {0};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Shady Paratroopa (both early demos), as the percent chance each status takes hold:
 * resists 13 statuses (down to 80% of the normal chance).
 */
static StatusVulnerability regist = {90, 90, 80, 100, 85, 100, 100, 85, 100, 85, 100, 85, 100, 85, 85, 90, 80, 100, 85, 100, 100, 95};
#else
/**
 * Status vulnerability of the Shady Paratroopa (the retail releases), as the percent chance each status
 * takes hold: resists 13 statuses (down to 80% of the normal chance).
 */
static StatusVulnerability regist = {85, 90, 80, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 90, 80, 85, 80, 100, 80, 100, 100, 95};
#endif

/**
 * Parts of the Shady Paratroopa: a single body part (part 1, model c_uranoko), each with its defense
 * tables, attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_ura_noko", // partName
        "c_uranoko", // modelName
        {0}, // positionOffset
        {0.0f, 30.0f, 0.0f}, // hitBaseOffset
        {0.0f, 40.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_SHELLED, // attributes
        0, // counterAttributes
        pose_table, // poseTable
    },
};

/**
 * Weapon record of the Shady Paratroopa's spinning shell attack: 3 damage and counts as a hammer-type hit.
 */
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
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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
 * Weapon record of the Shady Paratroopa's dark spinning shell attack: 6 damage and can hit several
 * targets.
 */
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
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
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
 * Init script of the Koopa: registers its wait, attack, damage and confusion handlers,
 * clears its flipped-over counter and sets the shell-clack run and walk sounds.
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

/**
 * Damage reaction: runs the default damage handling (btldefaultevt_Damage) with LW(10) = -2 (the unit itself)
 * and LW(11) = 1.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Flips the Koopa onto its back when it is hit while helpless:
 * it switches to the upside-down defence and pose tables (NKT_D_1, then NKT_S_2),
 * sets the flipped status flag and a flipped-over counter of 2 turns, lowers its hit offset,
 * and bounces with SFX_ENM_INSIDE1.
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
 * Run when the Shady Koopa's turn comes while it is on its back: counts the flipped-over counter down;
 * while it is still nonzero it attacks anyway with ura_attack_event,
 * at zero it flips back up (normal defence and pose tables, SFX_ENM_INSIDE2, a small hop).
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
 * The Koopa's shell spin when it makes a first strike on Mario's side (the pre-battle attack):
 * it pulls into its shell with SFX_ENM_NOKO_SHELL1 and spins into the target,
 * which takes the hit via the damage check; afterwards it settles back into its rest pose.
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 40)
    WAIT_MS(100)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), 256, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 10)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 1)
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
 * The Koopa's attack: while it is flipped over it just wakes up (wakeup_event);
 * otherwise it uses an item or picks a target, pulls into its shell (SFX_ENM_NOKO_SHELL1) and spins into it,
 * kicking up kemuri_test dust; a miss lets it slide past, a hit applies the damage,
 * and it returns to its stance.
 */
static EVT_BEGIN(attack_event)
    // If the Koopa is flipped over, it first rights itself with wakeup_event.
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(wakeup_event)
        RETURN
    END_IF
    // Use the target of the opening first attack if there was one; otherwise use an enemy item, or choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        WAIT_FRAMES(30)
    ELSE
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
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_nokonoko_attack))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    // The Koopa hops up and withdraws into its shell.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_SHELL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("NKT_A_1"))
    // The shell starts to spin, faster and faster.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 20)
    WAIT_MS(100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 40)
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    // The spinning shell rolls across the stage into the target.
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    DELETE_EVENT(LW(13))
    // Find out how the target reacts to the shell.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), 256, LW(5))
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
    // The shell missed: it rolls on past the target, slows, and the Koopa hops out of it.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, 0, 1)
    WAIT_MS(250)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 10)
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_NOKO_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(10.0f), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    GOTO(98)
    // The shell connects: the damage is applied and the Koopa bounces back in two hops.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_nokonoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_nokonoko_attack), 256, LW(5))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 10)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 1)
    GOTO(98)
    // The Koopa walks back to its home position.
    LABEL(98)
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
 * The Shady Koopa's attack: like the Koopa's shell spin
 * but it first surrounds itself with a dark aura (eff_aura, SFX_ENM_URANOKO_MOVE1 to 4),
 * spins into the target with the Shady attack weapon, and returns to its stance after a miss or a hit.
 */
static EVT_BEGIN(ura_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // The Shady Koopa chooses a target for its shell attack.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_ura_noko_ura_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_ura_noko_ura_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_ura_noko_ura_attack))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_ura_noko_ura_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT
        // The Shady Koopa hops up and spins around into its shell.
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
    LOOP(36)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 10, 0)
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 5)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, LW(14))
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(14), 0)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_FRAMES(20)
    BEGIN_SIBLING_EVENT
        WAIT_MS(200)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(2), 10)
        // A dark aura wraps around the spinning shell as it speeds up.
        CALL(eff_aura, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_URANOKO_MOVE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 10)
    WAIT_MS(400)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 20)
    WAIT_MS(400)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_SPEED, 40)
    WAIT_MS(400)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(evt_btl_camera_set_mode, 0, 0)
    BEGIN_SIBLING_EVENT_GET_ID(LW(13))
        LOOP(0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxoff, LW(15))
    // The shell rolls across the stage toward the target.
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
    // Find out how the target reacts to the shell.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_ura_noko_ura_attack), 256, LW(5))
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
    // The shell missed: it rolls on past the target.
    LABEL(90)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(5), LW(2), 0, 0, 1)
    GOTO(97)
    // The shell connects: the damage is applied.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_ura_noko_ura_attack))
        SET_VALUE(LW(6), 1)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_ura_noko_ura_attack), 256, LW(5))
    GOTO(97)
    // Move on to the next target in line, if there is one.
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
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 250, LW(1), LW(2))
    // The shell slows down, the aura fades and the Shady Koopa hops out of its shell.
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_URA_PATA_SPIN_STOP, 1)
    WAIT_FRAMES(3)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle event: sets the unit's body part 1 to the pose given by its pose table for its current state. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper that keeps the Shady Paratroopa's aura effect centred on the unit and scaled to its size;
 * blocks until the effect ends.
 */
static USER_FUNC(eff_aura) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff;
    EffUranokoWork* work;
    f32 x, y, z;

    if (isFirstCall) {
        unit->work[UW_URA_PATA_AURA_EFFECT] = (EvtWord)effUranokoEntry(0, 120, 0.0f, -1000.0f, 0.0f);
    }
    BtlUnit_GetPos(unit, &x, &y, &z);
    eff = (EffectEntry*)unit->work[UW_URA_PATA_AURA_EFFECT];
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
