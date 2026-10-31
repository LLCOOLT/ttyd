// Palace of Shadow battle unit: Marilyn (Shadow Sirens rematch) (`boss_marilyn_las`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "unit/party/unit_party_vivian.h"
#include "battle/battle_database_common.h"
#include "unit/unit_boss_majolyne.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "version.h"

// Unit work slots of Marilyn (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BOSS_MARILYN_LAS_SHADOW_HELD = 3, // non-zero stops the shadow position from following her
    UW_BOSS_MARILYN_LAS_RANK = 4,        // the HP rank (0 to 2) she stands at
    UW_BOSS_MARILYN_LAS_NEW_RANK = 5,    // her HP rank among the Sirens (set by Beldam's majo3_sort)
    UW_BOSS_MARILYN_LAS_ATTACK_STEP = 8, // step of her attack cycle
    UW_BOSS_MARILYN_LAS_CHARGE_COUNT = 9 // charge-ups in a row
};

BattleUnitKind unit_boss_marilyn_las;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_marilyn_kagenuke_attack1;
static BattleWeapon weapon_marilyn_thunder_attack1;
static BattleWeapon weapon_marilyn_charge1;
static EvtWord init_event[37];
static EvtWord damage_event[22];
static EvtWord dead_event[152];
static EvtWord phase_event[2];
static EvtWord attack_event[93];
#if VERSION >= VERSION_US
static EvtWord kagenuke_attack_event[241];
#else
static EvtWord kagenuke_attack_event[238];
#endif
static EvtWord thunder_attack_event[235];
static EvtWord charge_attack_event[58];
#if VERSION >= VERSION_US
static EvtWord wait_event[7];
#else
static EvtWord wait_event[6];
#endif

/**
 * Unit data of Marilyn in the Palace of Shadow: 40 HP, level 57;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_marilyn_las = {
    134,
    "btl_un_marilyn4",
    40,
    0,
    1,
    1,
    57,
    0,
    0,
    100,
    0,
    50,
    7,
    40,
    54,
    0,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    6.0f,
    24.0f,
    0.0f,
    20.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    0.0f,
    16.0f,
    35.1f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    40.0f,
    54.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MARI_DAMAGED1",
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

/**
 * Defence of Marilyn against each element (normal, fire, ice, explosion, electric):
 * none, so every hit does its full damage.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of Marilyn per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of Marilyn:
 * percent chance that each status takes hold (100 is normal); immune to Fright, Gale Force;
 * strongly resistant to Frozen, Tiny, Attack Down, Defense Down, Allergic, Slow, Instant KO.
 */
static StatusVulnerability regist = {50, 50, 50, 100, 50, 100, 100, 30, 100, 40, 100, 40, 100, 40, 40, 0, 0, 100, 40, 100, 100, 5};
#else
/**
 * JP, US and PAL values of the status vulnerability of Marilyn:
 * percent chance that each status takes hold (100 is normal); immune to Fright, Gale Force;
 * strongly resistant to Frozen, Allergic, Slow, Instant KO.
 */
static StatusVulnerability regist = {50, 50, 50, 100, 50, 100, 100, 40, 100, 60, 100, 60, 100, 80, 40, 0, 0, 100, 40, 100, 100, 5};
#endif

/** Pose table of Marilyn: animation names for each pose type (idle, walk, hurt, attack and so on). */
static PoseTableEntry pose_table[] = {
    {1, "MRR_N_1"},
    {2, "MRR_Z_1"},
    {9, "MRR_Z_1"},
    {5, "MRR_X_1"},
    {4, "MRR_X_1"},
    {3, "MRR_X_1"},
    {BTL_POSE_NORMAL, "MRR_S_1"},
    {29, "MRR_Q_2"},
    {30, "MRR_Q_2"},
    {31, "MRR_D_1"},
    {BTL_POSE_DAMAGE, "MRR_D_1"},
    {50, "MRR_S_1"},
    {BTL_POSE_RUN, "MRR_R_1"},
    {BTL_POSE_WALK, "MRR_W_1"},
    {BTL_POSE_DANGER, "MRR_S_1"},
    {BTL_POSE_PERIL, "MRR_S_1"},
    {BTL_POSE_TALK, "MRR_T_1"},
    {BTL_POSE_STAY_DEFAULT, "MRR_S_1"},
};

/**
 * Data table of Marilyn: event scripts and values the battle looks up by tag (damage reactions, dodge, first
 * strike and so on).
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

/** Part of Marilyn: its one body part with hit box, defence tables and pose table. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_marilyn4", "c_maririn", 0.0f, 0.0f, 0.0f, 15.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 38, 56, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

/** Weapon of Marilyn's kagenuke attack: damage 7. */
static BattleWeapon weapon_marilyn_kagenuke_attack1 = {
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
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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

/** Weapon of Marilyn's thunder: damage 7. */
static BattleWeapon weapon_marilyn_thunder_attack1 = {
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
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
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

/** Weapon of Marilyn's charge-up. */
static BattleWeapon weapon_marilyn_charge1 = {
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
    7, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Marilyn sinks into her shadow: after 250 ms plays the shadow sound (SFX_BOSS_MARI_SHADOW1)
 * and hides her model (battle_evt_majo_disp_off).
 */
static EVT_BEGIN(marilyn_down)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_SHADOW1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    RETURN
EVT_END()

/**
 * Marilyn rises out of her shadow at the position in LW(0..2):
 * after 250 ms plays the rising sound (SFX_BOSS_MARI_SHADOW2), shows her model again and sets her position.
 */
static EVT_BEGIN(marilyn_up)
    BEGIN_INLINE_EVENT
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_SHADOW2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    RETURN
EVT_END()

/**
 * Init script of Marilyn in the Shadow Sirens rematch (Palace of Shadow):
 * installs her wait, phase, attack, damage and confusion handlers, clears unit work 8 (attack cycle step) and 3,
 * and starts the shared shadow-tail follower (majo3_shadow_tail_event).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_ATTACK_STEP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_SHADOW_HELD, 0)
    SPAWN_EVENT(majo3_shadow_tail_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage handler for Marilyn: sets GW(12) (her state for the sisters' scripts) to 1
 * when the hit carries damage code 1024, then runs the default damage script.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(12), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Marilyn's defeat (data table entry 49): walks back to her home spot if displaced
 * and waits for the attack to end.
 * The camera zooms on her and she cries out: the long "btl_majo3_12" when Beldam (GW(11)) is dead and Doopliss
 * (GW(13)) is down, else "btl_majo3_09"; if Beldam is mid-knockout she waits for it to finish and says nothing.
 * Then GW(12) = 2 and the shared no-spin dead sequence runs.
 * GW(11), GW(12) and GW(13) (Beldam, Marilyn, Doopliss) are 0 while alive, 1 once their damage event sees a
 * defeating hit, and 2 at the end of their dead event.
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
        CASE_EQUAL(1)
        LOOP(0)
            IF_INT_EQUAL(GW(11), 2)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        GOTO(99)
        CASE_EQUAL(2)
        SWITCH(GW(13))
            CASE_EQUAL(0)
            CASE_DEFAULT
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(btl_marilyn_zoom)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MRR_D_1"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MRR_D_1"))
            CALL(evt_msg_print, 2, STRING("btl_majo3_12"), 0, BTL_UNIT_SELF)
            GOTO(90)
        END_SWITCH
    END_SWITCH
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(btl_marilyn_zoom)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("MRR_D_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("MRR_D_1"))
    CALL(evt_msg_print, 2, STRING("btl_majo3_09"), 0, BTL_UNIT_SELF)
    LABEL(90)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_D_3"))
    SET_VALUE(GW(12), 2)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    RETURN
EVT_END()

/**
 * Marilyn's unison-phase script; nothing installs it (no SetEventUnisonPhase in the las Siren units).
 * After the player's phase it
 * runs the shared majo_unison_phase_event, and if her slot in the HP order (unit work 5) changed,
 * sinks into her shadow and re-emerges at the new home spot (x 55 / 105 / 155), then re-sorts the turn order.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(majo_unison_phase_event)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_RANK, LW(3))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_NEW_RANK, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_RANK, LW(4))
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            WAIT_MS(200)
            CALL_CHILD(marilyn_down)
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
            CALL_CHILD(marilyn_up)
            CALL(btlevtcmd_SortPhaseMoveTable)
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        END_IF
    END_IF
    RETURN
EVT_END()

/** Phase handler for Marilyn: does nothing (Beldam's phase script drives the sisters' lines). */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/**
 * Marilyn's turn: uses an enemy item if she has one;
 * otherwise draws lots between the shadow-slip attack,
 * the lightning attack and a charge-up (weights 40/35/25 in the retail releases, 50/25/25 in the demos).
 * The charge-up has weight 25 only while she has charged fewer than twice in a row (unit work 9 counts charges
 * and resets after either attack).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(2), 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_CHARGE_COUNT, LW(0))
    IF_INT_LESS(LW(0), 2)
        SET_VALUE(LW(2), 25)
    END_IF
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_DrawLots, LW(0), 3, 50, 25, LW(2))
#else
    CALL(btlevtcmd_DrawLots, LW(0), 3, 40, 35, LW(2))
#endif
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_CHARGE_COUNT, 0)
        SET_VALUE(LW(9), PTR(&weapon_marilyn_kagenuke_attack1))
        CALL_CHILD(kagenuke_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_CHARGE_COUNT, 0)
        SET_VALUE(LW(9), PTR(&weapon_marilyn_thunder_attack1))
        CALL_CHILD(thunder_attack_event)
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_CHARGE_COUNT, LW(0))
        ADD(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_MARILYN_LAS_CHARGE_COUNT, LW(0))
        SET_VALUE(LW(9), PTR(&weapon_marilyn_charge1))
        CALL_CHILD(charge_attack_event)
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Marilyn's shadow-slip attack (weapon in LW(9)):
 * she sinks into her shadow, rises 30 units in front of a randomly chosen target,
 * claps her hands at it (one hit, guardable), then sinks again and returns home.
 * The US release places her 5 units further forward in depth.
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_ARM_FOLD1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A1_1"))
    CALL_CHILD(marilyn_down)
    WAIT_MS(300)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_US
    ADD(LW(2), 5)
#endif
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SET_VALUE(LW(1), 0)
    CALL_CHILD(marilyn_up)
    WAIT_MS(600)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_HAND_CLAP1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A2_1"))
    WAIT_FRAMES(4)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A2_2"))
    WAIT_MS(350)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A2_3"))
    WAIT_MS(100)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A2_4"))
    WAIT_MS(400)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A1_1"))
    CALL_CHILD(marilyn_down)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL_CHILD(marilyn_up)
    RETURN
EVT_END()

/**
 * Marilyn's lightning attack (weapon in LW(9)):
 * she powers up, then drops a thunder_n64 bolt with screen shake
 * and rumble on each target on the player's side in turn; the weapon pierces defense and cannot be guarded.
 */
static EVT_BEGIN(thunder_attack_event)
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
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_POWER1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A3_1"))
    WAIT_MS(800)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A3_2"))
    WAIT_MS(150)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(evt_sub_random, 2, LW(7))
    ADD(LW(7), 3)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetWidth, LW(3), LW(5))
    CALL(btlevtcmd_GetHeight, LW(3), LW(6))
    CALL(evt_eff64, STRING(""), STRING("thunder_n64"), LW(7), LW(0), LW(1), LW(2), LW(5), LW(6), 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_MARI_ATTACK_THUNDER1"), 0)
    CALL(evt_btl_camera_shake_h, 0, 3, 0, 25, 13)
    BEGIN_INLINE_EVENT
        CALL(evt_sub_rumble_onoff, 0, 0)
        WAIT_MS(300)
        CALL(evt_sub_rumble_onoff, 1, 0)
    END_INLINE_EVENT
    WAIT_MS(83)
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
 * Marilyn charges up (weapon in LW(9), weapon_marilyn_charge1):
 * camera on her, power-up pose and sound, then the weapon hits herself to apply a charge of +2 to her next
 * attack.
 */
static EVT_BEGIN(charge_attack_event)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("MRR_A3_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_MARI_CHARGE1"), EVT_NULLPTR, 0, LW(15))
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), DAMAGE_FLAG_LAST_HIT, LW(5))
    RETURN
EVT_END()

/** Wait event of Marilyn: switches to pose table entry 1 (idle). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
