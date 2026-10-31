// Keelhaul Key (muj) battle unit: X-Naut horde group 2 (gundan_zako_group2) in Lord Crump's fight: its parts,
// defence/status tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_stage_object.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "pmario_sound.h"
#include "battle/battle_sub.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "muj.h"
#include "dolphin/mtx.h"
#include "battle/battle_database_common.h"
#include "driver/extdrv.h"
#include "zakogun.h"
#include "system.h"
#include "libc_decls.h"
#include "version.h"

// Unit work slots (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_BOSS_GUNDAN_ZAKO_GROUP2_ATTACK_DONE = 0, // set to 1 by the C code once all 25 X-Nauts have landed
    UW_BOSS_GUNDAN_ZAKO_GROUP2_FALL_HIT = 1,    // 1 after a fall-attack hit lands; the last drop skips its dodge check
    UW_BOSS_GUNDAN_ZAKO_GROUP2_DYING = 2,       // set to 1 when its death event starts
};

USER_FUNC(shake_ceil);
USER_FUNC(zakogun_attack2);
USER_FUNC(zakogun_attack2_yusuri);
USER_FUNC(zakogun_dead2);
USER_FUNC(down_ceil);

BattleUnitKind unit_boss_gundan_zako_group2;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[4];
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
BattleWeapon weapon_gundan_zako_group2_attack;
BattleWeapon weapon_gundan_zako_group2_yusuri_attack;
static EvtWord init_event[21];
static EvtWord damage_event[129];
static EvtWord dead_event[136];
static EvtWord attack_event[32];
extern EvtWord fall_attack_event[];
static EvtWord shake_attack_event[281];
static EvtWord hit_check_event[34];
extern EvtWord hit_check_event2[];
extern EvtWord hit_check_event_sub[];
static EvtWord wait_event[6];

/**
 * Unit data of X-Nauts: 6 HP, 400x36 units in size; ties together its sounds, parts, status vulnerability,
 * init event and event table.
 */
BattleUnitKind unit_boss_gundan_zako_group2 = {
    101,
    "btl_un_gundan_zako_group2",
    6,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9999,
    400,
    36,
    0,
    55,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    200.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    200.0f,
    0.0f,
    0.0f,
    200.0f,
    23.4f,
    0.0f,
    60.0f,
    -35.0f,
    0.0f,
    280.0f,
    36.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_TEAM_3RD_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_CEILING | UNIT_ATTR_NO_KNOCKBACK_POSE,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/** Defence of X-Nauts: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of X-Nauts: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Status vulnerability of X-Nauts (percent chance each status takes hold): immune to sleep, stop, dizzy,
 * poison, confusion, electrified, burn, freeze, Huge, Tiny, Attack Up, Attack Down, Defense Up,
 * Defense Down, allergic, fright, Gale Force, Fast, Slow, Dodgy, Invisible, instant KO;
 * the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/** Pose table of X-Nauts: maps its battle poses to its animations (Z_*). */
static PoseTableEntry pose_table[] = {
    {BTL_POSE_NORMAL, "Z_1"},
    {31, "Z_1"},
    {BTL_POSE_DAMAGE, "Z_1"},
    {BTL_POSE_STAY_DEFAULT, "Z_1"},
};

/** Event table of X-Nauts: dead_event (tag 49). */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/** Parts of X-Nauts: 1 part (model c_zako_n). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_gundan_zako_group2", "c_zako_n", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_HAMMERLIKE_CANNOT_TARGET | PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, pose_table},
};

/**
 * Weapon of X-Nauts (attack): targets one unit for 1 damage; used by fall_attack_event,
 * hit_check_event_sub.
 */
BattleWeapon weapon_gundan_zako_group2_attack = {
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
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
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
 * Weapon of X-Nauts (yusuri attack): targets every unit for 4 damage; used by shake_attack_event.
 */
BattleWeapon weapon_gundan_zako_group2_yusuri_attack = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
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

/** Init event of X-Naut group 2: installs its wait, attack, damage and confusion events and starts the wait event. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage event of X-Naut group 2: the X-Nauts take the hurt pose when the hit did damage
 * or the group has one of several statuses (KO, sleep, dizzy, confusion, freeze, stop, poison, burn, tiny,
 * defense down, slow or allergic), then the default damage reaction runs.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamage, BTL_UNIT_SELF, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        SET_VALUE(LW(15), 1)
    ELSE
        SET_VALUE(LW(15), 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_INSTANT_KILL, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_SLEEP, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DIZZY, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CONFUSE, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_FREEZE, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_STOP, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_POISON, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_BURN, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_TINY, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DEFENSE_DOWN, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_SLOW, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_ALLERGIC, LW(14))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(zakogun_damage_pose)
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(zakogun_damage_pose_cancel)
    RETURN
EVT_END()

/**
 * Death event of X-Naut group 2: marks the group dying (unit work 2),
 * raises the ceiling (up_ceil) as the 25 X-Nauts collapse (zakogun_dead2) with the enemy-death sounds
 * and smoke across the stage, stores its coins and experience with the Star Point effect and removes the unit.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_DYING, 1)
    BEGIN_INLINE_EVENT
        CALL(up_ceil)
    END_INLINE_EVENT
    CALL(zakogun_dead2)
    WAIT_FRAMES(50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(48)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        LOOP(20)
            CALL(evt_sub_random, 500, LW(3))
            SUBTRACT(LW(3), 250)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), LW(3))
            CALL(evt_sub_random, 30, LW(3))
            SET_VALUE(LW(1), 0)
            ADD(LW(1), LW(3))
            SET_VALUE(LW(2), 75)
            CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetCoin, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(_add_star_point_disp_offset, BTL_UNIT_SELF, 0, 0, 0)
    CALL(evt_eff, STRING(""), STRING("star_point"), 0, 0, 0, 0, LW(0), 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    ELSE
        CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 2)
    END_IF
    RETURN
EVT_END()

/**
 * Attack event of X-Naut group 2: 50/50 between dropping onto one target (fall_attack_event)
 * and shaking the ceiling (shake_attack_event).
 */
static EVT_BEGIN(attack_event)
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 50)
        CALL_CHILD(fall_attack_event)
        GOTO(99)
    END_IF
    CALL_CHILD(shake_attack_event)
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Group 2's fall attack: picks one target and the 25 X-Nauts hop along the ceiling until above it
 * and drop onto it one by one (zakogun_attack2), while hit_check_event deals the hits.
 */
EVT_BEGIN(fall_attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_ATTACK_DONE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_FALL_HIT, 0)
    SET_VALUE(LW(9), PTR(&weapon_gundan_zako_group2_attack))
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
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(zakogun_set_target_id, LW(3))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    BEGIN_SIBLING_EVENT
        CALL_CHILD(hit_check_event)
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_MOVE_CAILING2"), 0)
    CALL(zakogun_attack2)
    DELETE_EVENT(LW(15))
    RETURN
EVT_END()

/**
 * Group 2's shaking attack: the X-Nauts rock the ceiling (zakogun_attack2_yusuri, shake_ceil) with growing
 * camera shakes, then debris (fall effects) rains across the stage and hits the first
 * and the next selected target (weapon_gundan_zako_group2_yusuri_attack).
 */
static EVT_BEGIN(shake_attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_ATTACK_DONE, 0)
    SET_VALUE(LW(9), PTR(&weapon_gundan_zako_group2_yusuri_attack))
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
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(zakogun_set_target_id, LW(3))
    BEGIN_SIBLING_EVENT
        LOOP(8)
            CALL(shake_ceil)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.5f))
        LOOP(7)
            WAIT_FRAMES(18)
            CALL(evt_btl_camera_shake_h, 0, LW(0), 0, 18, 0)
            CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_MOVE_CAILING3"), 0)
            ADD_FLOAT(LW(0), FLOAT(0.5f))
        END_LOOP
        WAIT_FRAMES(18)
        CALL(evt_btl_camera_shake_h, 0, LW(0), 0, 100, 0)
    END_SIBLING_EVENT
    CALL(zakogun_attack2_yusuri)
    BEGIN_SIBLING_EVENT
        CALL(evt_eff, STRING(""), STRING("fall"), 2, 0, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(20)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, 100, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(35)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, -35, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(57)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, -100, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL_CHILD(hit_check_event2)
        END_IF
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(82)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, 80, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(90)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, 40, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(105)
        CALL(evt_eff, STRING(""), STRING("fall"), 2, 130, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    END_SIBLING_EVENT
    WAIT_FRAMES(115)
    CALL(evt_eff, STRING(""), STRING("fall"), 2, -145, 0, 20, 0, 250, 0, 1, 60, 0, 0, 0)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL_CHILD(hit_check_event2)
    END_IF
    RETURN
EVT_END()

/**
 * Script helper: lowers the stage objects if_body and
 * if_wire from height 250 to 130 over 120 frames (the ceiling the horde stands on comes down).
 */
USER_FUNC(down_ceil) {
    u8* ceil = &_battleWorkPointer->stageObjectWork.flags;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        work->start = (Vec){0.0f, 250.0f, 0.0f};
        work->end = (Vec){0.0f, 130.0f, 0.0f};
        work->moveTimer = 120;
        work->steps = 120;
        *ceil &= ~STAGE_OBJ_FLAG_IRON_FRAME_GONE;
        work->sfx = work->sfx = psndSFXOn("SFX_BOSS_TEAM_3RD_MOVE_CAILING1");
    }
    body->position.y = wire->position.y = intplGetValue(4, work->start.y, work->end.y, work->steps - work->moveTimer, work->steps);
    work->moveTimer--;
    if (work->moveTimer < 0) {
        psndSFXOff(work->sfx);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/** Script helper: raises the stage objects if_body and if_wire from 130 back to 250 over 120 frames. */
USER_FUNC(up_ceil) {
    u8* ceil = &_battleWorkPointer->stageObjectWork.flags;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        work->start = (Vec){0.0f, 130.0f, 0.0f};
        work->end = (Vec){0.0f, 250.0f, 0.0f};
        work->moveTimer = 120;
        work->steps = 120;
        *ceil |= STAGE_OBJ_FLAG_IRON_FRAME_GONE;
        work->sfx = psndSFXOn("SFX_BOSS_TEAM_3RD_MOVE_CAILING1");
    }
    body->position.y = wire->position.y = intplGetValue(4, work->start.y, work->end.y, work->steps - work->moveTimer, work->steps);
    work->moveTimer--;
    if (work->moveTimer < 0) {
        psndSFXOff(work->sfx);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: makes the lowered stage objects if_body and if_wire shudder between height 130
 * and 135 over 9 frames.
 */
USER_FUNC(shake_ceil) {
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        work->start = (Vec){0.0f, 130.0f, 0.0f};
        work->end = (Vec){0.0f, 135.0f, 0.0f};
        work->moveTimer = 0;
    }
    body->position.y = wire->position.y = intplGetValue(4, work->start.y, work->end.y, work->moveTimer, 9);
    work->moveTimer++;
    if (work->moveTimer > 17) {
        body->position.y = wire->position.y = 130.0f;
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/** Script helper: starts formation 2: selects it (work->flag = 1) and initialises the first 25 X-Nauts of the pool. */
USER_FUNC(zakogun_ext_init2) {
    s32 i;
    ExtdrvPose* pose = extGetPosePtr();

    work->flag = 1;
    for (i = 0; i < 25; i++, pose++) {
        zakogun_ext_init123_common(pose, i);
    }
    return EVT_RETURN_DONE;
}

/**
 * Per-frame update of formation 2 (25 X-Nauts):
 * moves each member through its state machine and updates its pose matrix and sounds.
 */
void zakogun_ext_main2(void) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = zakogun_get_ptr();
    ExtdrvPose* pose = extGetPosePtr();
    BattleStageObject* body;
    s32 i;
    ZakoGun* zako;
    f32 x, y, z;
    Mtx m;
    const char* se1;
    const char* se2;
    const char* se3;

    if (unit == NULL) {
        return;
    }
    body = BattleSearchObjectPtr("if_body");
    // FAKE: the (0, "...") comma expressions keep these two names out of constant propagation so they stay in
    // saved registers as in the game; plain assignments change zakogun_ext_main2 (no runtime effect).
    se1 = (0, "SFX_BOSS_TEAM_3RD_ATTACK2");
    se2 = (0, "SFX_BOSS_TEAM_3RD_MOVE_CAILING2");
    se3 = "SFX_BOSS_TEAM_3RD_ATTACK2";
    for (i = 0; i < 25; i++, pose++) {
        zako = &zakogun[i];
        pose->texId = zako->poseBase + zako->poseCount / zako->poseDiv;
        zako->poseCount++;
        if (zako->poseCount >= zako->poseNum * zako->poseDiv) {
            zako->poseCount = 0;
        }
        switch (zako->state) {
            case 0:
                zako->state = 5;
                zako->rot.x = zako->rot.y = zako->rot.z = 0.0f;
                zakogun_set_pose(zako, 0x25, 4, 6);
                break;
            case 5:
                zako->pos.x = zako->home.x = body->position.x - 250.0f + i * 20.0f;
                zako->pos.y = zako->home.y = body->position.y - 35.0f;
                zako->pos.z = zako->home.z = 0.0f;
                zako->state = 10;
                break;
            case 10:
                zako->pos.x = zako->home.x = body->position.x + unit->position.x - 250.0f + i * 20.0f;
                zako->pos.y = zako->home.y = body->position.y - 35.0f;
                if (zako->pos.y < unit->position.y) {
                    zako->pos.y = unit->position.y;
                }
                zako->pos.z = zako->home.z = -10.0f;
                break;
            case 20:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work->targetId), &x, &y, &z);
                zako->start = zako->pos;
                if (zako->pos.x >= x) {
                    zako->target.x = zako->pos.x - 30.0f;
                    zako->rot.y = 0.0f;
                } else {
                    zako->target.x = 15.0f + zako->pos.x;
                    zako->rot.y = 180.0f;
                }
                zako->target.y = zako->start.y - 2.0f;
                zako->state = 25;
                zako->timer = zako->timerMax = 8;
            case 25:
                zako->pos.x = intplGetValue(4, zako->start.x, zako->target.x, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y = intplGetValue(4, zako->start.y, zako->target.y, (zako->timerMax - zako->timer) * 2, zako->timerMax);
                zako->timer--;
                if (zako->timer < 0) {
                    BtlUnit_GetPos(BattleGetUnitPtr(wp, work->targetId), &x, &y, &z);
                    if (__fabs(zako->pos.x - x) <= 20.0) {
                        zako->state = 30;
                    } else {
                        zako->state = 20;
                    }
                }
                break;
            case 30:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work->targetId), &x, &y, &z);
                zako->vel.x = rand() / 32767.0f - 0.5f;
                zako->vel.y = 0.0f;
#if VERSION <= VERSION_DEMO_JP
                zako->vel.z = 0.2f;
#else
                zako->vel.z = 1.5f;
#endif
                zako->target.y = y + work->count * 2.0f;
                zako->state = 35;
                zakogun_set_pose(zako, 0x2C, 1, 1);
                psndSFXOn(se1);
            case 35:
                zako->pos.x += zako->vel.x;
                zako->pos.y += zako->vel.y;
                zako->pos.z += zako->vel.z;
                zako->vel.y += -0.5f;
                if (zako->pos.y < zako->target.y) {
                    zako->pos.y = zako->target.y;
                    zako->state = 40;
                    work->count++;
                    if (work->count == 25) {
                        unit->work[UW_BOSS_GUNDAN_ZAKO_GROUP2_ATTACK_DONE] = 1;
                    }
                }
                break;
            case 40:
                if (work->count == 25) {
                    zako->state = 45;
                    zako->timer = irand(60);
                }
                break;
            case 45:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->vel.x = -5.0f;
                    zako->vel.y = 3.0f;
                    zako->state = 48;
                    zakogun_set_pose(zako, 0x22, 1, 1);
                    zako->rot.y = 0.0f;
                }
                break;
            case 48:
                zako->pos.x += zako->vel.x;
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                if (zako->pos.y < 0.0f) {
                    zako->pos.y = 0.0f;
                    zakogun_set_pose(zako, 0x16, 10, 1);
                    zako->state = 49;
                }
                break;
            case 49:
                zako->pos.x += zako->vel.x;
                if (zako->pos.x <= -300.0f) {
                    zako->state = 50;
                    zako->pos.x = 300.0f;
                    zako->pos.y = zako->home.y;
                    zako->pos.z = zako->home.z;
                    zakogun_set_pose(zako, 0x25, 4, 6);
                    if (i == 0) {
                        psndSFXOn(se2);
                    }
                }
                break;
            case 50:
#if VERSION >= VERSION_US
            {
                BattleUnit* tgt = BattleGetUnitPtr(wp, work->targetId);
                if (tgt != NULL) {
                    BtlUnit_GetPos(tgt, &x, &y, &z);
                    work->targetPos = (Vec){x, y, z};
                } else {
                    x = work->targetPos.x;
                    y = work->targetPos.y;
                    z = work->targetPos.z;
                }
            }
#else
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work->targetId), &x, &y, &z);
#endif
                zako->rot.y = 0.0f;
                zako->start = zako->pos;
                zako->target.x = zako->pos.x - 30.0f;
                if (zako->target.x < zako->home.x) {
                    zako->target.x = zako->home.x;
                }
                zako->target.y = zako->start.y - 2.0f;
                zako->state = 55;
                zako->timer = zako->timerMax = 8;
                btl_camera_set_mode(0, 0);
            case 55:
                zako->pos.x = intplGetValue(4, zako->start.x, zako->target.x, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y = intplGetValue(4, zako->start.y, zako->target.y, (zako->timerMax - zako->timer) * 2, zako->timerMax);
                zako->timer--;
                if (zako->timer < 0) {
                    if (zako->pos.x <= zako->home.x) {
                        zako->pos.x = zako->home.x;
                        zako->state = 10;
                    } else {
                        zako->state = 50;
                    }
                }
                break;
            case 60:
                zakogun_set_pose(zako, 0x29, 3, 6);
                zako->state = 65;
                zako->timer = 120;
            case 65:
                zako->pos.x = body->position.x - 250.0f + i * 20.0f;
                zako->pos.y = body->position.y - 35.0f;
                zako->pos.z = 0.0f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 10;
                    zakogun_set_pose(zako, 0x25, 4, 6);
                }
                break;
            case 80:
                zako->timer = irand(10);
                zako->state = 82;
            case 82:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 83;
                    zako->vel.y = 0.0f;
                    psndSFXOn(se3);
                }
                break;
            case 83:
                zako->vel.y += -0.5f;
                zako->pos.y += zako->vel.y;
                if (zako->pos.y <= 0.0f) {
                    zako->pos.y = 0.0f;
                    zako->state = 84;
                    zakogun_set_pose(zako, 0x21, 3, 3);
                }
                break;
            case 84:
                zako->start = zako->pos;
                zako->target.x = zako->start.x + irand(100) - 50.0f;
                zako->target.y = 0.0f;
                zako->target.z = zako->start.z + irand(20) - 10.0f;
                zako->state = 85;
                zako->timer = zako->timerMax = 20;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
            case 85:
                zako->pos.x = intplGetValue(0, zako->start.x, zako->target.x, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.z = intplGetValue(0, zako->start.z, zako->target.z, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 86;
                }
                break;
            case 86:
                zako->start = zako->pos;
                zako->target.x = zako->start.x + irand(50) - 25.0f;
                zako->target.y = 0.0f;
                zako->target.z = zako->start.z + irand(10) - 5.0f;
                zako->state = 87;
                zako->timer = zako->timerMax = 10;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -50.0f) / 20.0f;
            case 87:
                zako->pos.x = intplGetValue(0, zako->start.x, zako->target.x, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.z = intplGetValue(0, zako->start.z, zako->target.z, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 88;
                    zako->rot.y = 0.0f;
                    zako->timer = 48;
                }
                break;
            case 88:
                zako->rot.y -= 15.0f;
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->rot.y = 0.0f;
                    zako->state = 89;
                }
                break;
            case 89:
                zako->rot.x += 3.0f;
                if (zako->rot.x >= 90.0f) {
                    zako->state = -1;
                    zako->pos = (Vec){0.0f, -1000.0f, 0.0f};
                }
                break;
            case 90:
                zako->pos.x = 0.0f;
                zako->pos.y = -1000.0f;
                zako->pos.z = 0.0f;
                zako->state = -1;
                break;
        }
        PSMTXIdentity(*pose->mtx);
        PSMTXRotRad(m, 'x', zako->rot.x * 0.017453292f);
        PSMTXConcat(*pose->mtx, m, *pose->mtx);
        PSMTXRotRad(m, 'y', zako->rot.y * 0.017453292f);
        PSMTXConcat(*pose->mtx, m, *pose->mtx);
        (*pose->mtx)[0][3] = zako->pos.x;
        (*pose->mtx)[1][3] = zako->pos.y;
        (*pose->mtx)[2][3] = zako->pos.z + i * 0.25f;
    }
}

/** Script helper for group 2 attack: sets the 25 X-Nauts to attack state 20 and blocks until they finish. */
USER_FUNC(zakogun_attack2) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        work->count = 0;
        for (i = 0; i < 25; i++) {
            zakogun[i].state = 20;
        }
    }
    i = 0;
    n = 0;
    for (; i < 25; i++) {
        if (zakogun[i].state == 10) {
            n++;
        }
    }
    return n == 25 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Script helper for group 2 shaking attack (yusuri): sets the 25 X-Nauts to state 60 and blocks until they finish. */
USER_FUNC(zakogun_attack2_yusuri) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        for (i = 0; i < 25; i++) {
            zakogun[i].state = 60;
        }
    }
    i = 0;
    n = 0;
    for (; i < 25; i++) {
        if (zakogun[i].state == 10) {
            n++;
        }
    }
    return n == 25 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Script helper: puts the 25 X-Nauts of group 2 into their death state (80). */
USER_FUNC(zakogun_dead2) {
    s32 i;

    for (i = 0; i < 25; i++) {
        zakogun[i].state = 80;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: sends the 25 X-Nauts of group 2 running away (state 90) and blocks until they have left. */
USER_FUNC(zakogun_escape2) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        for (i = 0; i < 25; i++) {
            zakogun[i].state = 90;
        }
    }
    i = 0;
    n = 0;
    for (; i < 25; i++) {
        if (zakogun[i].state == -1) {
            n++;
        }
    }
    return n == 25 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/**
 * Hit check of group 2's fall attack: four hits 20 frames apart as the X-Nauts drop,
 * then a last hit once all 25 have landed (unit work 0), each through hit_check_event_sub.
 */
static EVT_BEGIN(hit_check_event)
    WAIT_FRAMES(10)
    LOOP(4)
        WAIT_FRAMES(20)
        SET_VALUE(LW(15), 0)
        CALL_CHILD(hit_check_event_sub)
    END_LOOP
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_ATTACK_DONE, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(LW(15), 1)
    CALL_CHILD(hit_check_event_sub)
    RETURN
EVT_END()

/** Hit check event for group 2: runs hit_check_event_sub whenever the group is about to hit someone. */
EVT_BEGIN(hit_check_event2)
    SET_VALUE(LW(15), 1)
    CALL_CHILD(hit_check_event_sub)
    RETURN
EVT_END()

/**
 * One hit of a group 2 attack: starts the target's avoid pose on a dodge,
 * otherwise applies the hit with the action-command defence (the last hit when LW(15) is 1).
 * In the fall attack the first landed hit sets unit work 1, after which the last hit skips the dodge check.
 */
EVT_BEGIN(hit_check_event_sub)
    IF_INT_EQUAL(LW(9), PTR(&weapon_gundan_zako_group2_attack))
        IF_INT_EQUAL(LW(15), 1)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_FALL_HIT, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                GOTO(92)
            END_IF
        END_IF
    END_IF
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
    LABEL(92)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    IF_INT_EQUAL(LW(15), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
        CALL(evt_btl_camera_set_mode, 0, 0)
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
    END_IF
    IF_INT_EQUAL(LW(9), PTR(&weapon_gundan_zako_group2_attack))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_GUNDAN_ZAKO_GROUP2_FALL_HIT, 1)
    END_IF
    GOTO(98)
    LABEL(98)
    LABEL(99)
    RETURN
EVT_END()

/** Wait (idle) event of X-Naut group 2: sets the idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
