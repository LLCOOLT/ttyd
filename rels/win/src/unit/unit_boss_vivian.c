// Battle unit Vivian, in the Shadow Sirens fight (ビビアン): win.rel's copy.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "unit/party/unit_party_vivian.h"
#include "battle/battle_database_common.h"
#include "unit/unit_boss_majolyne.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "win.h"
#include "version.h"

// Unit work slots (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_BOSS_VIVIAN_HOLD_SHADOW = 3, // 0 lets majo3_shadow_tail_event track her floor position in work 0-2
    UW_BOSS_VIVIAN_HP_RANK = 4,     // her place in the sisters' HP order (0 to 2)
    UW_BOSS_VIVIAN_NEW_HP_RANK = 5, // place majo_unison_phase_event gives her; she moves when it differs
    UW_BOSS_VIVIAN_SERIOUS = 6,     // cleared at init; in Beldam it marks her 66% HP line
    UW_BOSS_VIVIAN_AGGRESSIVE = 7,  // 1 set by Beldam (below 50% HP), 2 once Vivian has switched attacks
    UW_BOSS_VIVIAN_ATTACK_MODE = 8, // 0 shadow slip only, 1 flame next, 2 shadow slip or flame at random
};

BattleUnitKind unit_boss_vivian;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
BattleWeapon weapon_vivian_kagenuke_attack1;
BattleWeapon weapon_vivian_flame_attack1;
static BattleUnitSetup entry_marilyn;
static BattleUnitSetup entry_majolyne;
static EvtWord init_event[179];
static EvtWord entry_event[46];
static EvtWord damage_event[22];
static EvtWord dead_event[189];
static EvtWord phase_event[2];
static EvtWord attack_event[98];
#if VERSION >= VERSION_US
static EvtWord kagenuke_attack_event[207];
#else
static EvtWord kagenuke_attack_event[204];
#endif
extern EvtWord flame_attack_event[];
#if VERSION >= VERSION_US
static EvtWord wait_event[7];
#else
static EvtWord wait_event[6];
#endif

/**
 * Unit data of Vivian (btl_un_vivian1), the lead unit of the Shadow Sirens fight in Boggly Woods: 10 HP,
 * level 26. Her init script spawns Marilyn and Beldam behind her.
 */
BattleUnitKind unit_boss_vivian = {
    33,
    "btl_un_vivian1",
    10,
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
    30,
    40,
    0,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    6.0f,
    16.0f,
    0.0f,
    15.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    0.0f,
    0.0f,
    11.0f,
    26.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    30.0f,
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
    "SFX_BOSS_VIVI_DAMAGED1",
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

/** Flat damage reduction of Vivian against normal, fire, ice, explosion and electric hits: none. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Element attributes of Vivian: none, so every element does its normal damage. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of Vivian in the demo builds, as a percent of the normal chance of each status:
 * immune to fright, Gale Force, instant KO; 60% for freeze; 70% for sleep, dizzy, confusion, Tiny,
 * Attack Down, Defense Down, allergy, Slow; 80% for stop.
 */
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 60, 100, 70, 100, 70, 100, 70, 70, 0, 0, 100, 70, 100, 100, 0};
#else
/**
 * Status vulnerability of Vivian in the retail builds, as a percent of the normal chance of each status:
 * immune to fright, Gale Force, instant KO; 50% for freeze; 70% for sleep, dizzy, confusion, allergy, Slow;
 * 80% for stop, Tiny, Attack Down; 95% for Defense Down.
 */
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 50, 100, 80, 100, 80, 100, 95, 70, 0, 0, 100, 70, 100, 100, 0};
#endif

/**
 * Poses of Vivian (PTR_*): idle, status, hurt, run, walk and talking animations;
 * her attack poses are set by name in her scripts.
 */
static PoseTableEntry pose_table[] = {
    {1, "PTR_N_1"},
    {2, "PTR_Z_1"},
    {9, "PTR_Z_1"},
    {5, "PTR_X_1"},
    {4, "PTR_X_1"},
    {3, "PTR_X_1"},
    {BTL_POSE_NORMAL, "PTR_S_4"},
    {29, "PTR_Q_1"},
    {30, "PTR_Q_1"},
    {31, "PTR_D_1"},
    {BTL_POSE_DAMAGE, "PTR_D_1"},
    {50, "PTR_S_4"},
    {BTL_POSE_RUN, "PTR_R_1"},
    {BTL_POSE_WALK, "PTR_W_1"},
    {BTL_POSE_DANGER, "PTR_D_2"},
    {BTL_POSE_PERIL, "PTR_D_2"},
    {BTL_POSE_TALK, "PTR_T_5"},
    {BTL_POSE_STAY_DEFAULT, "PTR_S_4"},
};

/** Data table of Vivian: event 49 (she is defeated) runs dead_event. */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/** Vivian's single part: her model (c_vivian), the main target and the part that covers for allies. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/** Vivian's shadow-slip strike: 1 damage to one opposing target, guardable. */
BattleWeapon weapon_vivian_kagenuke_attack1 = {
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
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

/**
 * Vivian's flame: 1 fire-element damage to every opposing target, ignoring defense and impossible to guard.
 */
BattleWeapon weapon_vivian_flame_attack1 = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
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
 * Spawn data for Marilyn: she is created far off-screen at (1000, 0, 1000) and Vivian's init script
 * then moves her behind Vivian.
 */
static BattleUnitSetup entry_marilyn = {
    &unit_boss_marilyn, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Spawn data for Beldam: she is created far off-screen at (1000, 0, 1000) and Vivian's init script
 * then moves her behind Vivian.
 */
static BattleUnitSetup entry_majolyne = {
    &unit_boss_majolyne, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Vivian sinks into her shadow: after 250 ms plays the shadow sound (SFX_BOSS_VIVI_SHADOW1)
 * and hides her model (battle_evt_majo_disp_off).
 */
static EVT_BEGIN(vivian_down)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VIVI_SHADOW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    RETURN
EVT_END()

/**
 * Vivian rises out of her shadow at the position in LW(0..2):
 * after 250 ms plays the rising sound (SFX_BOSS_VIVI_SHADOW2), shows her model and sets her position.
 */
static EVT_BEGIN(vivian_up)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VIVI_SHADOW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

/**
 * Init script of Vivian, the unit that sets up the Shadow Sirens fight:
 * installs her wait, phase, attack, damage and entry scripts and the default confusion script.
 * It stores her unit id in GW(10), spawns Marilyn (GW(9)) and Beldam (GW(8)) behind her at x offsets 50
 * and 100 (z +10, +20), gives the three HP-order slots 0,
 * 1 and 2 (unit work 4 and 5) and clears unit work 6 and 7,
 * zeroes the sisters' states GW(11) to GW(13), sets GW(14) to 2,
 * clears her unit work 8 and 3 and starts majo3_shadow_tail_event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_HP_RANK, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_NEW_HP_RANK, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_SERIOUS, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_AGGRESSIVE, 0)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, GW(10))
    CALL(btlevtcmd_SpawnUnit, GW(9), PTR(&entry_marilyn), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetPos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, GW(9), 4, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 5, 1)
    CALL(btlevtcmd_SetUnitWork, GW(9), 6, 0)
    CALL(btlevtcmd_SetUnitWork, GW(9), 7, 0)
    CALL(btlevtcmd_SpawnUnit, GW(8), PTR(&entry_majolyne), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 100)
    ADD(LW(2), 20)
    CALL(btlevtcmd_SetPos, GW(8), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, GW(8), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, GW(8), 4, 2)
    CALL(btlevtcmd_SetUnitWork, GW(8), 5, 2)
    CALL(btlevtcmd_SetUnitWork, GW(8), 6, 0)
    CALL(btlevtcmd_SetUnitWork, GW(8), 7, 0)
    SET_VALUE(GW(13), 0)
    SET_VALUE(GW(12), 0)
    SET_VALUE(GW(11), 0)
    SET_VALUE(GW(14), 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_ATTACK_MODE, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_HOLD_SHADOW, 0)
    SPAWN_EVENT(majo3_shadow_tail_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Battle intro (entry script): after 120 frames the camera moves onto each sister in turn:
 * Beldam says they will show what they can do (btl_majo3_00),
 * Marilyn grunts (btl_majo3_01) and Vivian answers "Yes, Sis!" (btl_majo3_02).
 */
static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    WAIT_FRAMES(60)
    WAIT_FRAMES(60)
    CALL_CHILD(btl_majolyne_zoom)
    CALL(evt_msg_print, 2, STRING("btl_majo3_00"), 0, GW(8))
    WAIT_MS(300)
    CALL_CHILD(btl_marilyn_zoom)
    CALL(evt_msg_print, 2, STRING("btl_majo3_01"), 0, GW(9))
    WAIT_MS(300)
    CALL_CHILD(btl_vivian_zoom)
    CALL(evt_msg_print, 2, STRING("btl_majo3_02"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Damage script of Vivian: sets GW(13) (her state for the sisters' scripts) to 1
 * when the hit carries DAMAGE_FLAG_DEFEATED (1024),
 * then runs the default damage script.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(13), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Vivian's defeat: she walks back to her home spot if displaced.
 * If a sister is in the middle of her own defeat (state 1) she waits for it and says nothing;
 * if both sisters are dead she screams (btl_majo3_13);
 * otherwise she apologizes (btl_majo3_10). Then GW(13) = 2 and the shared no-spin dead sequence runs.
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
    SWITCH(GW(11))
        CASE_EQUAL(0)
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_EQUAL(1)
            LOOP(0)
                IF_INT_EQUAL(GW(12), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            GOTO(99)
            CASE_EQUAL(2)
        END_SWITCH
        CASE_EQUAL(1)
        LOOP(0)
            IF_INT_EQUAL(GW(11), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        GOTO(99)
        CASE_EQUAL(2)
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_EQUAL(1)
            LOOP(0)
                IF_INT_EQUAL(GW(12), 2)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            GOTO(99)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(btl_vivian_zoom)
            CALL(evt_msg_print, 2, STRING("btl_majo3_13"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            GOTO(90)
        END_SWITCH
        SWITCH(GW(12))
            CASE_EQUAL(0)
            CASE_DEFAULT
        END_SWITCH
    END_SWITCH
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("PTR_D_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("PTR_D_1"))
    CALL_CHILD(btl_vivian_zoom)
    CALL(evt_msg_print, 2, STRING("btl_majo3_10"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_D_3"))
    SET_VALUE(GW(13), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    RETURN
EVT_END()

/**
 * Vivian's unison-phase script, which nothing installs (init_event sets only phase_event):
 * after the player's phase it re-sorts the sisters by HP (majo_unison_phase_event);
 * if her slot (unit work 5) differs from her current one (unit work 4) she sinks into her shadow
 * and comes up at the new home spot (x 55, 105 or 155), and the turn order is re-sorted.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(majo_unison_phase_event)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_HP_RANK, LW(3))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_NEW_HP_RANK, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_HP_RANK, LW(4))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            CALL_CHILD(vivian_down)
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
            CALL_CHILD(vivian_up)
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    RETURN
EVT_END()

/** Vivian's phase script: empty, it does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/**
 * Vivian's attack choice: uses an item if the AI picks one.
 * Otherwise she always uses the shadow slip (unit work 8 = 0)
 * until Beldam's phase script sets her unit work 7 (below 50% HP);
 * then her next attack is the flame and from then on she picks shadow slip 70% or flame 30%.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_AGGRESSIVE, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_ATTACK_MODE, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_AGGRESSIVE, 2)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_ATTACK_MODE, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(&weapon_vivian_kagenuke_attack1))
        CALL_CHILD(kagenuke_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_VIVIAN_ATTACK_MODE, 2)
        SET_VALUE(LW(9), PTR(&weapon_vivian_flame_attack1))
        CALL_CHILD(flame_attack_event)
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 70)
        ADD(LW(1), 30)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        IF_INT_LESS(LW(0), 70)
            SET_VALUE(LW(9), PTR(&weapon_vivian_kagenuke_attack1))
            CALL_CHILD(kagenuke_attack_event)
        ELSE
            SET_VALUE(LW(9), PTR(&weapon_vivian_flame_attack1))
            CALL_CHILD(flame_attack_event)
        END_IF
    END_SWITCH
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Vivian's shadow-slip attack (weapon_vivian_kagenuke_attack1, 1 damage to one enemy):
 * she sinks into her shadow, rises in front of the target and strikes, then sinks again to return home.
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
    CALL_CHILD(vivian_down)
    WAIT_MS(300)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_US
    ADD(LW(2), 5)
#endif
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SET_VALUE(LW(1), 0)
    CALL_CHILD(vivian_up)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
    WAIT_MS(70)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VIVI_ATTACK4"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    CALL_CHILD(vivian_down)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL_CHILD(vivian_up)
    RETURN
EVT_END()

/**
 * Vivian's flame attack (weapon_vivian_flame_attack1, 1 damage to every enemy,
 * piercing defense and unguardable):
 * she raises her hands with the magic sound, then smoke appears on each target in turn as it is hit or dodges;
 * with no valid targets it ends (or flusters her when confused).
 */
EVT_BEGIN(flame_attack_event)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A3_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VIVI_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 6, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
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

/** Wait event of Vivian: switches to pose table entry 1 (idle). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
