// Battle unit Beldam, in the Shadow Sirens fight (マジョリン): win.rel's copy.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "unit/party/unit_party_vivian.h"
#include "battle/battle_database_common.h"
#include "unit/unit_boss_majolyne.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "version.h"

// Unit work slots of Beldam (GW(8) is Beldam; slots read on her sisters stay raw).
enum {
    UW_BOSS_MAJOLYNE_SHADOW_X = 0,          // floor position of her shadow tail (majo3_shadow_tail_event)
    UW_BOSS_MAJOLYNE_SHADOW_Y = 1,          // (y of the same position)
    UW_BOSS_MAJOLYNE_SHADOW_Z = 2,          // (z of the same position)
    UW_BOSS_MAJOLYNE_HIDING = 3,            // 1 while she is under the floor: the shadow tail stops following her
    UW_BOSS_MAJOLYNE_SIREN_RANK = 4,        // her spot in the Sirens' HP order, where she stands
    UW_BOSS_MAJOLYNE_SIREN_RANK_NEW = 5,    // her new spot, from majo_unison_phase_event
    UW_BOSS_MAJOLYNE_LOW_HP_NOTED = 6,      // 1 once her low HP has been remarked on (btl_majo3_03)
    UW_BOSS_MAJOLYNE_SIREN_ANGRY = 7,       // 1 once she is low on HP: the sisters turn aggressive
    UW_BOSS_MAJOLYNE_ATTACK_STEP = 8,       // opening move sequence: 0 shadow slip, 1 shrink, 2 enlarge, 3 blizzard, 4 weighted choice
    UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN = 9, // turns until she may use the blizzard again
};

static USER_FUNC(majo3_sort);

BattleUnitKind unit_boss_majolyne;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_majolyne_kagenuke_attack1;
static BattleWeapon weapon_majolyne_blizzard_attack1;
static BattleWeapon weapon_majolyne_powder_attack1;
static BattleWeapon weapon_majolyne_powder_attack2;
static EvtWord init_event[45];
static EvtWord damage_event[22];
static EvtWord dead_event[122];
static EvtWord phase_event[337];
static EvtWord attack_event[241];
#if VERSION >= VERSION_US
static EvtWord kagenuke_attack_event[225];
#else
static EvtWord kagenuke_attack_event[222];
#endif
static EvtWord blizzard_attack_event[243];
static EvtWord powder_attack_check[16];
static EvtWord powder_attack_event[179];
static EvtWord wait_event[6];

/**
 * Unit data of Beldam (btl_un_majolyne1), the Shadow Sirens' leader in Boggly Woods: 9 HP, level 26.
 * Vivian's init script spawns her and her sister Marilyn at the start of the fight,
 * and Beldam's phase script drives the sisters' lines.
 */
BattleUnitKind unit_boss_majolyne = {
    31,
    "btl_un_majolyne1",
    9,
    0,
    1,
    1,
    26,
    0,
    0,
    100,
    0,
    50,
    9,
    26,
    34,
    0,
    34,
    0.0f,
    17.0f,
    0.0f,
    0,
    0,
    6.0f,
    2.0f,
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
    8.0f,
    22.1f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    26.0f,
    34.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MAJO_DAMAGED1",
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

/** Flat damage reduction of Beldam against normal, fire, ice, explosion and electric hits: none. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element attributes of Beldam: none, so every element does its normal damage. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Status vulnerability of Beldam in the demo builds, as a percent of the normal chance of each status:
 * immune to fright, Gale Force, instant KO; 50% for freeze; 70% for sleep, dizzy, confusion, Tiny,
 * Attack Down, Defense Down, allergy, Slow; 80% for stop.
 */
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 50, 100, 70, 100, 70, 100, 70, 70, 0, 0, 100, 70, 100, 100, 0};
#else
/**
 * Status vulnerability of Beldam in the retail builds, as a percent of the normal chance of each status:
 * immune to fright, Gale Force, instant KO; 50% for freeze; 70% for sleep, dizzy, confusion, allergy, Slow;
 * 80% for stop, Tiny, Attack Down; 95% for Defense Down.
 */
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 50, 100, 80, 100, 80, 100, 95, 70, 0, 0, 100, 70, 100, 100, 0};
#endif

/**
 * Poses of Beldam (MJR_*): idle, status, hurt, walk and talking animations;
 * her attack poses are set by name in her scripts.
 */
static PoseTableEntry pose_table[] = {
    {1, "MJR_N_1"},
    {2, "MJR_Z_1"},
    {9, "MJR_Z_1"},
    {5, "MJR_X_1"},
    {4, "MJR_X_1"},
    {3, "MJR_X_1"},
    {BTL_POSE_NORMAL, "MJR_S_1"},
    {29, "MJR_Q_1"},
    {30, "MJR_Q_1"},
    {31, "MJR_D_1"},
    {BTL_POSE_DAMAGE, "MJR_D_1"},
    {50, "MJR_S_1"},
    {BTL_POSE_RUN, "MJR_R_1"},
    {BTL_POSE_WALK, "MJR_W_1"},
    {BTL_POSE_DANGER, "MJR_S_1"},
    {BTL_POSE_PERIL, "MJR_S_1"},
    {BTL_POSE_TALK, "MJR_T_1"},
    {BTL_POSE_STAY_DEFAULT, "MJR_S_1"},
};

/** Data table of Beldam: event 49 (she is defeated) runs dead_event. */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/** Beldam's single part: her model (c_majyorin), the main target and the part that covers for allies. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_majolyne1", "c_majyorin", 0.0f, 0.0f, 0.0f, 5.0f, 20.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/** Beldam's shadow-slip push: 1 ice-element damage to one opposing target, guardable. */
static BattleWeapon weapon_majolyne_kagenuke_attack1 = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_ICE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
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

/** Beldam's blizzard: 2 ice-element damage to every opposing target, ignoring defense. */
static BattleWeapon weapon_majolyne_blizzard_attack1 = {
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
    ELEMENT_ICE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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
 * Beldam's enlarging powder: aimed at an ally of hers, it always hits and makes the target Huge for 3 turns.
 */
static BattleWeapon weapon_majolyne_powder_attack1 = {
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
    {0, 2, 2, 3, 3, 4, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ALWAYS_HITS | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Beldam's shrinking powder: aimed at an enemy, it makes the target Tiny for 3 turns. */
static BattleWeapon weapon_majolyne_powder_attack2 = {
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
    NULL, // hpDamageFn
    {0, 2, 2, 3, 3, 4, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    -2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Beldam sinks into her shadow: after 250 ms plays the shadow sound (SFX_BOSS_MAJO_SHADOW1)
 * and hides her model (battle_evt_majo_disp_off).
 */
static EVT_BEGIN(majolyne_down)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_SHADOW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    RETURN
EVT_END()

/**
 * Beldam rises out of her shadow at the position in LW(0..2):
 * after 250 ms plays the rising sound (SFX_BOSS_MAJO_SHADOW2), shows her model again and sets her position.
 */
static EVT_BEGIN(majolyne_up)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_SHADOW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

/**
 * Moves the battle camera onto the unit id in LW(0) (looking at its x from a fixed height and distance,
 * a 30-frame move) and waits 37 frames;
 * the Shadow Sirens' scripts use it before each of their lines.
 */
static EVT_BEGIN(majo3_zoom)
    CALL(btlevtcmd_GetPos, LW(0), LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, LW(0), 65, 332, LW(0), 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Camera move onto Vivian (unit id in GW(10), set by her init script) through majo3_zoom,
 * used before her lines in the fight.
 */
EVT_BEGIN(btl_vivian_zoom)
    SET_VALUE(LW(0), GW(10))
    CALL_CHILD(majo3_zoom)
    RETURN
EVT_END()

/**
 * Camera move onto Marilyn (unit id in GW(9), spawned by Vivian's init script) through majo3_zoom,
 * used before her lines in the fight.
 */
EVT_BEGIN(btl_marilyn_zoom)
    SET_VALUE(LW(0), GW(9))
    CALL_CHILD(majo3_zoom)
    RETURN
EVT_END()

/**
 * Camera move onto Beldam (unit id in GW(8), spawned by Vivian's init script) through majo3_zoom,
 * used before her lines in the fight.
 */
EVT_BEGIN(btl_majolyne_zoom)
    SET_VALUE(LW(0), GW(8))
    CALL_CHILD(majo3_zoom)
    RETURN
EVT_END()

/**
 * Init script of Beldam in the Shadow Sirens fight:
 * installs her wait, phase, attack and damage scripts and the default confusion script,
 * clears unit work 8 (attack cycle step), 9 (blizzard cooldown) and 3 (shadow-tail pause),
 * starts majo3_shadow_tail_event and allocates 10 user words into GW(15).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_HIDING, 0)
    SPAWN_EVENT(majo3_shadow_tail_event)
    ALLOCATE_UW(10, GW(15))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage handler for Beldam: records in GW(11) when she took the "knocked out" damage code (1024),
 * then runs the default damage script.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(11), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Beldam's defeat: she walks back to her home spot if displaced and the camera moves onto her;
 * if both sisters are already down (GW(12) and GW(13) nonzero) she only screams (btl_majo3_11),
 * otherwise she leaves the rest to them (btl_majo3_08).
 * Then GW(11) becomes 2 (dead) and the shared dead sequence runs.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(3), LW(4), LW(5))
    SET_VALUE(LW(6), 1)
    IF_INT_EQUAL(LW(0), LW(3))
        IF_INT_EQUAL(LW(1), LW(4))
            IF_INT_EQUAL(LW(2), LW(5))
                SET_VALUE(LW(6), 0)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    END_IF
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(btl_majolyne_zoom)
    WAIT_MS(500)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MJR_D_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MJR_D_1"))
    IF_INT_NOT_EQUAL(GW(12), 0)
        IF_INT_NOT_EQUAL(GW(13), 0)
            CALL(evt_msg_print, 2, STRING("btl_majo3_11"), 0, BTL_UNIT_SELF)
            GOTO(90)
        END_IF
    END_IF
    CALL(evt_msg_print, 2, STRING("btl_majo3_08"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_D_3"))
    LABEL(90)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    SET_VALUE(GW(11), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    RETURN
EVT_END()

/**
 * HP-order helper shared by the Shadow Sirens' unison-phase scripts:
 * reads the HP of each sister still alive (GW(11) to GW(13) zero)
 * into the slot given by her unit work 5, orders the slots by HP with majo3_sort (highest first)
 * and writes each sister's new slot back to her unit work 5.
 */
EVT_BEGIN(majo_unison_phase_event)
    // Read the HP of each sister still standing (Vivian, Marilyn, Beldam) under the
    // formation slot she holds now.
    SET_VALUE(LW(0), -1)
    SET_VALUE(LW(1), -1)
    SET_VALUE(LW(2), -1)
    IF_INT_EQUAL(GW(13), 0)
        CALL(btlevtcmd_GetUnitWork, GW(10), 5, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(10), LW(0))
            SET_VALUE(LW(3), 1)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(10), LW(1))
            SET_VALUE(LW(4), 1)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(10), LW(2))
            SET_VALUE(LW(5), 1)
        END_SWITCH
    END_IF
    IF_INT_EQUAL(GW(12), 0)
        CALL(btlevtcmd_GetUnitWork, GW(9), 5, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(9), LW(0))
            SET_VALUE(LW(3), 2)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(9), LW(1))
            SET_VALUE(LW(4), 2)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(9), LW(2))
            SET_VALUE(LW(5), 2)
        END_SWITCH
    END_IF
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_GetUnitWork, GW(8), UW_BOSS_MAJOLYNE_SIREN_RANK_NEW, LW(6))
        SWITCH(LW(6))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHp, GW(8), LW(0))
            SET_VALUE(LW(3), 3)
            CASE_EQUAL(1)
            CALL(btlevtcmd_GetHp, GW(8), LW(1))
            SET_VALUE(LW(4), 3)
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHp, GW(8), LW(2))
            SET_VALUE(LW(5), 3)
        END_SWITCH
    END_IF
    // Sort the sisters by HP, highest first.
    CALL(majo3_sort)
    // Hand out the new formation slots in that order: the healthiest sister takes slot 0 (front),
    // the weakest slot 2; defeated sisters are skipped.
    SWITCH(LW(0))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 0)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 0)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), UW_BOSS_MAJOLYNE_SIREN_RANK_NEW, 0)
        END_IF
    END_SWITCH
    SWITCH(LW(1))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 1)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 1)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), UW_BOSS_MAJOLYNE_SIREN_RANK_NEW, 1)
        END_IF
    END_SWITCH
    SWITCH(LW(2))
        CASE_EQUAL(1)
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_SetUnitWork, GW(10), 5, 2)
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_SetUnitWork, GW(9), 5, 2)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GW(11), 0)
            CALL(btlevtcmd_SetUnitWork, GW(8), UW_BOSS_MAJOLYNE_SIREN_RANK_NEW, 2)
        END_IF
    END_SWITCH
    RETURN
EVT_END()

/**
 * Unison-phase script of Beldam, which nothing installs (init_event sets only phase_event):
 * after the player's phase it re-sorts the sisters by HP (majo_unison_phase_event);
 * if her slot (unit work 5) differs from her current one (unit work 4) she sinks into her shadow
 * and comes up at the new home spot (x 55, 105 or 155), and the turn order is re-sorted.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(majo_unison_phase_event)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_RANK, LW(3))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_RANK_NEW, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_RANK, LW(4))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            WAIT_MS(400)
            CALL_CHILD(majolyne_down)
            WAIT_MS(500)
            SWITCH(LW(4))
                CASE_EQUAL(0)
                SET_VALUE(LW(0), 55)
                SET_VALUE(LW(2), 0)
                CASE_EQUAL(1)
                SET_VALUE(LW(0), 105)
                SET_VALUE(LW(2), 10)
                CASE_EQUAL(2)
                SET_VALUE(LW(0), 155)
                SET_VALUE(LW(2), 20)
            END_SWITCH
            SET_VALUE(LW(1), 0)
            CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL_CHILD(majolyne_up)
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Beldam's phase script, after the player's phase: counts down her blizzard cooldown (unit work 9).
 * If she can act, it checks HP once per sister (unit work 6):
 * below 66% Beldam herself complains (btl_majo3_03), all living sisters get unit work 7 (enraged) and,
 * the first time, her next attack is the blizzard (unit work 8 = 3);
 * Marilyn below 50% gets ordered to hit Mario (btl_majo3_04, Marilyn grunts if she can act)
 * and Vivian below 50% gets scolded (btl_majo3_06, she apologizes), each setting that sister's unit work 7.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        // After the player's phase Beldam counts down her blizzard cooldown.
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, LW(0))
        END_IF
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            GOTO(90)
        END_IF
        // Beldam below 66% HP: she admits Mario is tougher than she thought and gets serious (btl_majo3_03);
        // the sisters turn aggressive and her next attack is the blizzard.
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_LOW_HP_NOTED, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
            DEBUG_PUT_REG(LW(0))
            MULTIPLY(LW(0), 66)
            DEBUG_PUT_REG(LW(0))
            DIVIDE(LW(0), 100)
            DEBUG_PUT_REG(LW(0))
            CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(1))
            DEBUG_PUT_REG(LW(1))
            IF_INT_LESS(LW(1), LW(0))
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_LOW_HP_NOTED, 1)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL_CHILD(btl_majolyne_zoom)
                CALL(evt_msg_print, 2, STRING("btl_majo3_03"), 0, BTL_UNIT_SELF)
                WAIT_MS(200)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_ANGRY, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_ANGRY, 1)
                    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 3)
                END_IF
                IF_INT_EQUAL(GW(12), 0)
                    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 1)
                END_IF
                IF_INT_EQUAL(GW(13), 0)
                    CALL(btlevtcmd_SetUnitWork, GW(10), 7, 1)
                END_IF
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            END_IF
        END_IF
        // Marilyn below 50% HP: Beldam orders her to hit Mario (btl_majo3_04) and Marilyn grunts back
        // (btl_majo3_05) if she can still act.
        IF_INT_EQUAL(GW(12), 0)
            CALL(btlevtcmd_GetUnitWork, GW(9), 6, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetMaxHp, GW(9), LW(0))
                MULTIPLY(LW(0), 50)
                DIVIDE(LW(0), 100)
                CALL(btlevtcmd_GetHp, GW(9), LW(1))
                IF_INT_LESS(LW(1), LW(0))
                    CALL(btlevtcmd_SetUnitWork, GW(9), 6, 1)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL_CHILD(btl_majolyne_zoom)
                    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, GW(9), -1, 16, LW(15))
                    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
                    WAIT_MS(200)
                    CALL(evt_msg_print, 2, STRING("btl_majo3_04"), 0, BTL_UNIT_SELF)
                    WAIT_MS(200)
                    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 1)
                    CALL(btlevtcmd_CheckActStatus, GW(9), LW(0))
                    IF_INT_NOT_EQUAL(LW(0), 0)
                        CALL_CHILD(btl_marilyn_zoom)
                        CALL(evt_msg_print, 2, STRING("btl_majo3_05"), 0, GW(9))
                        WAIT_MS(200)
                    END_IF
                    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                END_IF
            END_IF
        END_IF
        // Vivian below 50% HP: Beldam scolds her (btl_majo3_06) and Vivian apologizes (btl_majo3_07).
        IF_INT_EQUAL(GW(13), 0)
            CALL(btlevtcmd_GetUnitWork, GW(10), 6, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetMaxHp, GW(10), LW(0))
                MULTIPLY(LW(0), 50)
                DIVIDE(LW(0), 100)
                CALL(btlevtcmd_GetHp, GW(10), LW(1))
                IF_INT_LESS(LW(1), LW(0))
                    CALL(btlevtcmd_SetUnitWork, GW(10), 6, 1)
                    CALL(btlevtcmd_StatusWindowOnOff, 0)
                    CALL_CHILD(btl_majolyne_zoom)
                    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, GW(10), -1, 16, LW(15))
                    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
                    WAIT_MS(200)
                    CALL(evt_msg_print, 2, STRING("btl_majo3_06"), 0, BTL_UNIT_SELF)
                    WAIT_MS(200)
                    CALL(btlevtcmd_SetUnitWork, GW(10), 7, 1)
                    CALL(btlevtcmd_CheckActStatus, GW(10), LW(0))
                    IF_INT_NOT_EQUAL(LW(0), 0)
                        CALL_CHILD(btl_vivian_zoom)
                        CALL(evt_msg_print, 2, STRING("btl_majo3_07"), 0, GW(10))
                        WAIT_MS(200)
                    END_IF
                    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
                    CALL(btlevtcmd_StatusWindowOnOff, 1)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                END_IF
            END_IF
        END_IF
    END_IF
    LABEL(90)
    RETURN
EVT_END()

/**
 * Beldam's attack choice: uses an item if the AI picks one;
 * otherwise unit work 8 runs a fixed opening of shadow slip, shrinking powder on an enemy,
 * then enlarging powder on an ally,
 * and afterwards a weighted pick: shadow slip 40, enlarging powder 20 (if a target is not already Huge),
 * shrinking powder 20 (if a target is not already Tiny),
 * and the blizzard 20 once she is enraged (unit work 7) and its cooldown (unit work 9) is over.
 * Unit work 8 = 3 (set when she drops below 66% HP) uses the blizzard next;
 * the blizzard sets a two-phase cooldown.
 */
static EVT_BEGIN(attack_event)
    // Use an item if the AI decided to.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    // Opening moves by unit work 8: shadow slip, then shrinking powder on an enemy,
    // then enlarging powder on an ally; 3 is the blizzard.
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 1)
        SET_VALUE(LW(9), PTR(&weapon_majolyne_kagenuke_attack1))
        CALL_CHILD(kagenuke_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 2)
        SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack2))
        CALL_CHILD(powder_attack_check)
        CALL_CHILD(powder_attack_event)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 4)
        SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack1))
        CALL_CHILD(powder_attack_check)
        CALL_CHILD(powder_attack_event)
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_ATTACK_STEP, 4)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, 2)
        SET_VALUE(LW(9), PTR(&weapon_majolyne_blizzard_attack1))
        CALL_CHILD(blizzard_attack_event)
        CASE_EQUAL(4)
        // After the opening, a weighted pick: shadow slip 40,
        // plus 20 for each powder still useful and 20 for the blizzard once she is
        // angry and its cooldown is over.
        SET_VALUE(LW(14), 40)
        SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack1))
        CALL_CHILD(powder_attack_check)
        IF_INT_NOT_EQUAL(LW(3), -1)
            SET_VALUE(LW(10), LW(3))
            SET_VALUE(LW(11), LW(4))
            CALL(btlevtcmd_CheckStatus, LW(3), STATUS_HUGE, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack2))
        CALL_CHILD(powder_attack_check)
        IF_INT_NOT_EQUAL(LW(3), -1)
            SET_VALUE(LW(12), LW(3))
            SET_VALUE(LW(13), LW(4))
            CALL(btlevtcmd_CheckStatus, LW(3), STATUS_TINY, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SIREN_ANGRY, LW(2))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                ADD(LW(14), 20)
            END_IF
        END_IF
        SUBTRACT(LW(14), 1)
        // Roll the die and run the chosen attack.
        CALL(evt_sub_random, LW(14), LW(0))
        SET_VALUE(LW(1), 40)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(&weapon_majolyne_kagenuke_attack1))
            CALL_CHILD(kagenuke_attack_event)
            GOTO(90)
        END_IF
        ADD(LW(1), 20)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack1))
            SET_VALUE(LW(3), LW(10))
            SET_VALUE(LW(4), LW(11))
            CALL_CHILD(powder_attack_event)
            GOTO(90)
        END_IF
        ADD(LW(1), 20)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(&weapon_majolyne_powder_attack2))
            SET_VALUE(LW(3), LW(12))
            SET_VALUE(LW(4), LW(13))
            CALL_CHILD(powder_attack_event)
            GOTO(90)
        ELSE
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_BLIZZARD_COOLDOWN, 2)
            SET_VALUE(LW(9), PTR(&weapon_majolyne_blizzard_attack1))
            CALL_CHILD(blizzard_attack_event)
        END_IF
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Beldam's shadow-slip attack (weapon_majolyne_kagenuke_attack1, 1 damage to one enemy):
 * she sinks into her shadow, rises in front of the target, pushes it and sinks again to return home.
 */
static EVT_BEGIN(kagenuke_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_1"))
    CALL_CHILD(majolyne_down)
    WAIT_MS(300)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_US
    ADD(LW(2), 5)
#endif
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SET_VALUE(LW(1), 0)
    CALL_CHILD(majolyne_up)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_PUSH1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_2"))
    WAIT_FRAMES(25)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_3"))
    WAIT_MS(350)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_4"))
    WAIT_MS(200)
    CALL(evt_snd_sfxoff, LW(15))
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
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(98)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_1"))
    CALL_CHILD(majolyne_down)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL_CHILD(majolyne_up)
    RETURN
EVT_END()

/**
 * Beldam's blizzard attack (weapon_majolyne_blizzard_attack1):
 * she opens her hands and blows an icy breath ("ibuki" effect)
 * that hits every enemy for 2 damage, piercing defense; the weapon gives no freeze chance.
 */
static EVT_BEGIN(blizzard_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_HAND_OPEN1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_2"))
    WAIT_FRAMES(25)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_3"))
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A1_4"))
    WAIT_MS(200)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_ATTACK_ICE1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    IF_INT_GREATER_OR_EQUAL(LW(5), 0)
        CALL(evt_eff, 0, STRING("ibuki"), 0, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
    ELSE
        CALL(evt_eff, 0, STRING("ibuki"), 1, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_FRAMES(150)
    CALL(evt_snd_sfxoff, LW(15))
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
        GOTO(98)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * Powder-attack helper: picks a target for the weapon in LW(9) with the sampling calls
 * and returns it in LW(3) (unit, -1 if none)
 * and LW(4) (part).
 */
static EVT_BEGIN(powder_attack_check)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    RETURN
EVT_END()

/**
 * Beldam's powder attack on the target in LW(3)/LW(4) with the weapon in LW(9):
 * weapon_majolyne_powder_attack1 makes an ally (a sister or Beldam herself) Huge
 * and weapon_majolyne_powder_attack2 makes an enemy Tiny,
 * both for 3 turns and without damage. With no target she gets flustered when confused, else does nothing.
 */
static EVT_BEGIN(powder_attack_event)
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
    IF_INT_EQUAL(LW(9), PTR(&weapon_majolyne_powder_attack1))
        CALL(evt_btl_camera_set_mode, 0, 9)
        CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_IF
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MAJO_HAND_OPEN1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A2_1"))
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A2_2"))
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MJR_A2_3"))
    CALL(evt_snd_sfxoff, LW(15))
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
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(30)
    GOTO(99)
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event of Beldam: switches to pose table entry 1 (idle). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Background loop that keeps Beldam's shadow-tail position (unit work 0..2) following her position on the stage
 * floor each frame, until the unit is gone.
 */
EVT_BEGIN(majo3_shadow_tail_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_X, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_Y, LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_Z, LW(2))
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(5))
    IF_INT_EQUAL(LW(5), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_HIDING, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_X, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_Y, LW(1))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MAJOLYNE_SHADOW_Z, LW(2))
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

/**
 * Script helper: sorts three (id, value) pairs from lwData[3..5] and lwData[0..2] by value, highest first,
 * and writes the ids back to lwData[0..2]; used to order the sisters by HP.
 */
static USER_FUNC(majo3_sort) {
    MajoSortEntry tbl[3];
    MajoSortEntry tmp1;
    MajoSortEntry tmp3;
    MajoSortEntry tmp2;
    s32 i;

    for (i = 0; i < 3; i++) {
        tbl[i].id = event->lwData[3 + i];
        tbl[i].value = event->lwData[i];
    }
    if (tbl[0].value < tbl[1].value) {
        tmp1 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp1;
    }
    if (tbl[1].value < tbl[2].value) {
        tmp2 = tbl[1];
        tbl[1] = tbl[2];
        tbl[2] = tmp2;
    }
    if (tbl[0].value < tbl[1].value) {
        tmp3 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp3;
    }
    for (i = 0; i < 3; i++) {
        event->lwData[i] = tbl[i].id;
    }
    return EVT_RETURN_DONE;
}
