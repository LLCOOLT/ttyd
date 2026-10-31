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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 60, 100, 70, 100, 70, 100, 70, 70, 0, 0, 100, 70, 100, 100, 0};
#else
static StatusVulnerability regist = {70, 80, 70, 100, 70, 100, 100, 50, 100, 80, 100, 80, 100, 95, 70, 0, 0, 100, 70, 100, 100, 0};
#endif

static PoseTableEntry pose_table[] = {
    {1, "PTR_N_1"},
    {2, "PTR_Z_1"},
    {9, "PTR_Z_1"},
    {5, "PTR_X_1"},
    {4, "PTR_X_1"},
    {3, "PTR_X_1"},
    {28, "PTR_S_4"},
    {29, "PTR_Q_1"},
    {30, "PTR_Q_1"},
    {31, "PTR_D_1"},
    {39, "PTR_D_1"},
    {50, "PTR_S_4"},
    {42, "PTR_R_1"},
    {40, "PTR_W_1"},
    {56, "PTR_D_2"},
    {57, "PTR_D_2"},
    {BTL_POSE_TALK, "PTR_T_5"},
    {BTL_POSE_STAY_DEFAULT, "PTR_S_4"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

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
    0, 0, // element..damagePattern
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
    1, // element
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
 * Guess: init script of Vivian in the Shadow Sirens fight:
 * installs her wait, phase, attack, damage, confusion and entry handlers and resets her unit work.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 6, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 0)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 8, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    SPAWN_EVENT(majo3_shadow_tail_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Guess: battle intro lines: the camera zooms on Beldam,
 * Marilyn and Vivian in turn as they speak "btl_majo3_00" to "02".
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
 * Guess: damage handler for Vivian: records in her shared flag when she took the knocked-out damage code,
 * then runs the default damage script.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(13), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Guess: vivian's defeat: she returns to her home spot if displaced, speaks and plays the shared dead sequence. */
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
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
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
 * Guess: vivian's unison-phase script, run after the player's phase:
 * first runs the shared majo_unison_phase_event, then, if her move choice changed,
 * has her sink into her shadow and re-emerge.
 */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(majo_unison_phase_event)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(3))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(4))
        IF_INT_NOT_EQUAL(LW(3), LW(4))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, LW(4))
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
 * Guess: vivian's attack choice: uses an item if the AI says so,
 * otherwise picks by unit work 8 between the shadow-slip attack and the fire attack.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 7, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 8, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 2)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 8, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(&weapon_vivian_kagenuke_attack1))
        CALL_CHILD(kagenuke_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 8, 2)
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

/** Guess: vivian's shadow-slip attack: she dives into the shadow, slips under the target and strikes from below. */
static EVT_BEGIN(kagenuke_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
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
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
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
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    LABEL(98)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    CALL_CHILD(vivian_down)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL_CHILD(vivian_up)
    RETURN
EVT_END()

/**
 * Guess: vivian's fire attack (weapon_vivian_flame_attack1):
 * she raises her hands, the magic sound plays, flame smoke appears on every target in turn and each is hit
 * or avoids it by the usual guard check; with no valid targets it ends (or flusters her when confused).
 */
EVT_BEGIN(flame_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
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
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
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
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
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
