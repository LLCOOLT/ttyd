// Battle unit Hyper Paragoomba (ハイパーパタクリボー): gra.rel's copy.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "system.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "data_tables.h"
#include "battle/battle_sub.h"

// Unit work slots of the Hyper Paragoomba.
enum {
    UW_HYPER_PATAKURI_CHARGED = 0, // set to 1 when it charges up; cleared by init_event; nothing in this file reads it
};

static USER_FUNC(krb_get_dir);

BattleUnitKind unit_hyper_patakuri;
static BattleUnitDefense defence_patakuri;
static BattleUnitDefenseAttr defence_patakuri_attr;
static StatusVulnerability regist_patakuri;
static BattleWeapon weapon_patakuri_attack;
BattleWeapon weapon_patakuri_charge;
static BattleUnitKindPart parts_patakuri[1];
static PoseTableEntry pose_table_patakuri[19];
static BattleDataEntry data_table_patakuri[3];
static PoseSoundTiming pose_sound_timing_table[7];
static EvtWord init_event_patakuri[26];
static EvtWord dmg_fall_event[107];
static EvtWord patakuri_dmg_first_attack_pos[19];
static EvtWord attack_event_patakuri[532];
static EvtWord wait_event_patakuri[12];
static PoseTableEntry pose_table[20];
static BattleDataEntry data_table[2];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_kuriboo_attack;
static BattleWeapon weapon_kuriboo_charge;
static EvtWord init_event[47];
static EvtWord damage_event[10];
static EvtWord attack_event[638];
static EvtWord wait_event[6];

/**
 * Unit kind of the H. Paragoomba:
 * 8 HP, level 15, with its size, sounds and the links to its parts, status vulnerability and scripts.
 */
BattleUnitKind unit_hyper_patakuri = {
    UNIT_HYPER_PARAGOOMBA,
    "btl_un_hyper_patakuri",
    8,
    0,
    1,
    1,
    15,
    0,
    2,
    70,
    1,
    60,
    9999,
    23,
    25,
    5,
    25,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    11.5f,
    0.0f,
    0.0f,
    12.0f,
    16.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    23.0f,
    25.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PATAKURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING | UNIT_ATTR_REQUIRED_FOR_CLEAR,
    &regist_patakuri,
    1,
    parts_patakuri,
    init_event_patakuri,
    data_table_patakuri,
};

/** Defence of the H. Paragoomba's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence_patakuri = {{0, 0, 0, 0, 0}};

/** Defence attributes of the H. Paragoomba's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_patakuri_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the H. Paragoomba in the demo, as a percent of the normal chance:
 * sleep 80%, freeze 80%, instant kill 95%; raised chance for gale force 130% (and 6 other statuses lowered).
 */
static StatusVulnerability regist_patakuri = {80, 100, 100, 100, 80, 100, 100, 80, 100, 80, 100, 80, 100, 80, 80, 100, 130, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of the H. Paragoomba in the retail versions, as a percent of the normal chance:
 * sleep 80%, stop 90%, freeze 80%, instant kill 95% (and 8 other statuses lowered).
 */
static StatusVulnerability regist_patakuri = {80, 90, 100, 100, 80, 100, 100, 80, 100, 90, 100, 90, 100, 95, 80, 90, 90, 100, 80, 100, 100, 95};
#endif

/** H. Paragoomba's attack: 2 damage to a single target, a plain attack. */
static BattleWeapon weapon_patakuri_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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

/** H. Paragoomba's charge-up move (no damage, used on itself). */
BattleWeapon weapon_patakuri_charge = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    6, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Body part of the H. Paragoomba: a single part using the model "c_kuribo_h". */
static BattleUnitKindPart parts_patakuri[] = {
    {1, "btl_un_hyper_patakuri", "c_kuribo_h", 0.0f, 0.0f, 0.0f, 0.0f, 22.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_patakuri, &defence_patakuri_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_WINGED | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET, 0, pose_table_patakuri},
};

/**
 * Pose table of the H. Paragoomba:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table_patakuri[] = {
    {STATUS_SLEEP, "PTK_N_1"},
    {STATUS_STOP, "PTK_Y_1"},
    {STATUS_FREEZE, "PTK_Y_1"},
    {STATUS_CONFUSE, "PTK_K_1"},
    {STATUS_POISON, "PTK_I_1"},
    {STATUS_DIZZY, "PTK_I_1"},
    {BTL_POSE_NORMAL, "PTK_S_1"},
    {29, "PTK_Q_1"},
    {30, "PTK_Q_1"},
    {31, "PTK_S_1"},
    {BTL_POSE_DAMAGE, "PTK_D_1"},
    {50, "PTK_A_1"},
    {BTL_POSE_RUN, "PTK_R_1"},
    {41, "PTK_R_2"},
    {BTL_POSE_WALK, "PTK_W_1"},
    {BTL_POSE_DANGER, "PTK_I_1"},
    {BTL_POSE_PERIL, "PTK_I_1"},
    {BTL_POSE_TALK, "PTK_T_1"},
    {BTL_POSE_STAY_DEFAULT, "PTK_S_1"},
};

/** Event table of the H. Paragoomba: its fall when knocked out of the air, its reaction to a First Strike. */
static BattleDataEntry data_table_patakuri[] = {
    {14, dmg_fall_event},
    {48, patakuri_dmg_first_attack_pos},
    {0, NULL},
};

/**
 * Sound timing of the H. Paragoomba:
 * the sound effect played at set points of its idle, walk and run animations.
 */
static PoseSoundTiming pose_sound_timing_table[] = {
    {"PTK_S_1", 0.01f, NULL, "SFX_ENM_PATAKURI_WAIT1", 0, 1},
    {"PTK_W_1", 0.01f, NULL, "SFX_ENM_PATAKURI_MOVE1", 0, 1},
    {"PTK_R_1", 0.01f, NULL, "SFX_ENM_PATAKURI_MOVE1", 0, 1},
    {"PTK_K_1", 0.01f, NULL, "SFX_ENM_PATAKURI_WAIT1", 0, 1},
    {"PTK_N_1", 0.01f, NULL, "SFX_ENM_PATAKURI_WAIT1", 0, 1},
    {"PTK_I_1", 0.01f, NULL, "SFX_ENM_PATAKURI_WAIT1", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

/**
 * Init script of the Paragoomba.
 * Registers its wait, attack, damage and fall scripts, sets the flying movement sounds and starts waiting.
 */
static EVT_BEGIN(init_event_patakuri)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_patakuri))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_patakuri))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_patakuri))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Reaction when the Hyper Paragoomba loses its wings:
 * it drops with SFX_ENM_FALL1, lands with a hop and its pose table
 * and data switch to those of the walking Hyper Goomba form (kind 66).
 */
static EVT_BEGIN(dmg_fall_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_FLOATING)
    CALL(btlevtcmd_OffPartsAttribute, LW(10), LW(11), PART_ATTR_WINGED)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table))
    CALL(btlevtcmd_ChangeDataTable, LW(10), PTR(data_table))
    CALL(btlevtcmd_ReplaceParts, LW(10), LW(11), PTR(parts), 1)
    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_KIND_CHANGED)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 10, -1)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(500)
    CALL(btlevtcmd_ChangeKind, LW(10), 66)
    CALL_CHILD(init_event)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DAMAGE)
    RETURN
EVT_END()

/**
 * Data-table event 48, run when the battle opens with Mario's
 * or his partner's First Strike on the Hyper Paragoomba:
 * puts it at height 10 and waits for the attack to end.
 */
static EVT_BEGIN(patakuri_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

/**
 * The Hyper Paragoomba's attack: like the Paragoomba's dive attack,
 * it can instead spend its turn charging (weapon_patakuri_charge) unless it is already charged (status 16).
 */
static EVT_BEGIN(attack_event_patakuri)
    // Already charged: it goes straight to the dive attack.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CHARGE, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(10)
    END_IF
    // It may use an enemy item instead of acting.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // It draws lots between spending the turn charging up and attacking.
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 75)
    ELSE
        CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 25)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_patakuri_charge))
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
        CALL(evt_btl_camera_set_mode, 0, 7)
        CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 300)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(1), 15)
        ADD(LW(2), 10)
        // Charge-up: the charge sound and a crystal effect play while it hops in place.
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
        // The charge weapon applies the charged state to itself and the turn ends.
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
        RETURN
    END_IF
    // Dive attack: it picks a target; with none, a confused one flusters, otherwise the attack ends.
    LABEL(10)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_patakuri_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_patakuri_attack), LW(3), LW(4))
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
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_patakuri_attack))
    // The attack is declared and it flies up and toward the target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_patakuri_attack))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 50)
    ADD(LW(1), 40)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    // Wind-up: a short hover, then it swoops down onto the target;
    // the pre-damage check decides between a dodge and a hit.
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 0, 0, -1)
    WAIT_MS(100)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 50)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAKURI_MOVE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 5, 4, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patakuri_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Miss: it swoops past the target (which dodges for some kinds of miss) and flaps back to its spot.
    LABEL(90)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAKURI_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 50)
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -20, 1, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    WAIT_MS(500)
    GOTO(98)
    // Hit: the dive lands for its damage and it rebounds into the air.
    LABEL(91)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_PATAKURI_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -16, 1, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_patakuri_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_patakuri_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    GOTO(98)
    // It flies back to its home position.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_PATAKURI_MOVE1"), STRING("SFX_ENM_PATAKURI_MOVE1"), 0, 15, 15, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(7.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -10, 0, 0, -2)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script of the Hyper Paragoomba: shows its flying idle pose from the pose table. */
static EVT_BEGIN(wait_event_patakuri)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    WAIT_FRAMES(30)
    GOTO(0)
    RETURN
EVT_END()

/**
 * Pose table of the H. Paragoomba:
 * the animation played for each pose type (idle, hurt, walk, run, attack and so on).
 */
static PoseTableEntry pose_table[] = {
    {STATUS_SLEEP, "KUR_N_1"},
    {STATUS_STOP, "KUR_Y_1"},
    {STATUS_FREEZE, "KUR_Y_1"},
    {STATUS_CONFUSE, "KUR_K_1"},
    {STATUS_POISON, "KUR_I_1"},
    {STATUS_DIZZY, "KUR_I_1"},
    {BTL_POSE_NORMAL, "KUR_S_1"},
    {29, "KUR_Q_1"},
    {30, "KUR_Q_1"},
    {31, "KUR_S_1"},
    {BTL_POSE_DAMAGE, "KUR_D_1"},
    {50, "KUR_A_1"},
    {51, "KUR_A_2"},
    {BTL_POSE_RUN, "KUR_R_1"},
    {41, "KUR_R_2"},
    {BTL_POSE_WALK, "KUR_W_1"},
    {BTL_POSE_DANGER, "KUR_I_1"},
    {BTL_POSE_PERIL, "KUR_I_1"},
    {BTL_POSE_TALK, "KUR_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KUR_S_1"},
};

/** Event table of the H. Paragoomba: nothing special on a First Strike. */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0},
};

/** Defence of the H. Paragoomba's body per damage type: 0 against every damage type. */
static BattleUnitDefense defence = {0};

/** Defence attributes of the H. Paragoomba's body: none, so every damage type is dealt normally. */
static BattleUnitDefenseAttr defence_attr = {0};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the H. Paragoomba in the demo, as a percent of the normal chance:
 * sleep 80%, freeze 80%, instant kill 95% (and 7 other statuses lowered).
 */
static StatusVulnerability regist = {80, 100, 80, 100, 80, 100, 100, 80, 100, 80, 100, 80, 100, 80, 80, 100, 100, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of the H. Paragoomba in the retail versions, as a percent of the normal chance:
 * sleep 80%, stop 90%, freeze 80%, instant kill 95% (and 9 other statuses lowered).
 */
static StatusVulnerability regist = {80, 90, 80, 100, 80, 100, 100, 80, 100, 95, 100, 95, 100, 95, 80, 90, 80, 100, 80, 100, 100, 95};
#endif

/** Body part of the H. Paragoomba: a single part using the model "c_kuribo_h". */
static BattleUnitKindPart parts[] = {
    {
        1, // partNum
        "btl_un_hyper_kuriboo", // partName
        "c_kuribo_h", // modelName
        {0}, // positionOffset
        {0.0f, 22.0f, 0.0f}, // hitBaseOffset
        {0.0f, 30.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence, // defense
        &defence_attr, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        0, // counterAttributes
        pose_table, // poseTable
    },
};

/** H. Paragoomba's attack: 2 damage to a single target, a jump-style hit. */
static BattleWeapon weapon_kuriboo_attack = {
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    0, // counterResistFlags
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

/** H. Paragoomba's charge-up move (no damage, used on itself). */
static BattleWeapon weapon_kuriboo_charge = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    6, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of the walking form of the Hyper Paragoomba (after losing its wings).
 * Registers its wait, attack and damage scripts and the walking sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_PATAKURI_CHARGED, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Hyper Paragoomba: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event of the Hyper Paragoomba: does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** The Hyper Goomba-form attack: the Goomba headbutt, with the same charge option as the winged form. */
static EVT_BEGIN(attack_event)
    // Target: the first-strike target if the battle opened that way, otherwise one picked for its attack.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_kuriboo_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_kuriboo_attack), LW(3), LW(4))
    END_IF
    // No target: a confused one flusters, otherwise the attack ends.
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // Already charged: it goes straight to the headbutt.
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CHARGE, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(10)
    END_IF
    // It may use an enemy item instead of acting.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // It draws lots between spending the turn charging up and attacking.
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 75)
    ELSE
        CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 25)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(9), PTR(&weapon_kuriboo_charge))
        CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HYPER_PATAKURI_CHARGED, 1)
        CALL(evt_btl_camera_set_mode, 0, 7)
        CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 300)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(1), 15)
        ADD(LW(2), 10)
        // Charge-up: the charge sound and a crystal effect play while it hops in place.
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
        // The charge weapon applies the charged state to itself and the turn ends.
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
        RETURN
    END_IF
    // Headbutt: the attack is declared.
    LABEL(10)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.5996094f))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_kuriboo_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_kuriboo_attack))
    // It runs up to the target.
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 100)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // Wind-up: a short pause, then it leaps at the target, spinning in the air.
    WAIT_MS(170)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPosFloat, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
        SET_VALUE(LW(8), 0)
        LOOP(32)
            CALL(btlevtcmd_GetPosFloat, BTL_UNIT_SELF, LW(9), LW(10), LW(11))
            CALL(krb_get_dir, LW(5), LW(6), LW(9), LW(10), LW(8))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(8))
            SET_FLOAT_VALUE(LW(5), LW(9))
            SET_FLOAT_VALUE(LW(6), LW(10))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(12)
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(15), 50)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    END_INLINE_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    // The leap comes down on the target; the pre-damage check decides between a dodge and a hit.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 32, -1)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_kuriboo_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        GOTO(91)
        CASE_END
    END_SWITCH
    // Miss: it hops on past the target, which dodges for some kinds of miss.
    LABEL(90)
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(15), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MoveDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_MoveDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
    WAIT_MS(500)
    GOTO(95)
    // Hit: the attack lands for its damage and the Goomba bounces back off the target.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_kuriboo_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_kuriboo_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(15), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 10)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 6, -1)
    GOTO(95)
    // It walks back to its home position.
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 3, 3, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of the Hyper Paragoomba: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: computes the facing direction (degrees) from point (args[0], args[1]) to (args[2], args[3])
 * and stores it in args[4]; if both points coincide args[4] is left as it was.
 */
static USER_FUNC(krb_get_dir) {
    EvtWord* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);
    s32 dir = evtGetValue(event, args[4]);
    f32 dx = x2 - x1;
    f32 dz = z2 - z1;

    if (dx == 0.0f && dz == 0.0f) {
        evtSetValue(event, args[4], dir);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dz, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}
