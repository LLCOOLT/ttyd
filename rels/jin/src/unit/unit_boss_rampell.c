// Doopliss (rampell): boss battle unit used in Creepy Steeple.
#include "battle/battle_unit.h"
#include "eff/eff_scanning.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "driver/animdrv.h"
#include "mario/mario_pouch.h"
#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "unit/unit_mario.h"
#include "evt/evt_msg.h"
#include "version.h"

static USER_FUNC(_mario_makkuro_set);
static USER_FUNC(vivian_comeback);
static USER_FUNC(eff_scanning);

BattleUnitKind unit_boss_rampell;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_rampell_attack;
extern EvtWord rampell_zoom[];
extern EvtWord to_faker_mario[];
static EvtWord init_event[61];
static EvtWord damage_event[10];
static EvtWord dead_event[74];
static EvtWord phase_event[106];
static EvtWord attack_event[24];
#if VERSION <= VERSION_DEMO_US
static EvtWord ogg_attack_event[481];
#else
static EvtWord ogg_attack_event[491];
#endif
static EvtWord wait_event[6];
static BattleUnitDefense defence_fmario;
static BattleUnitDefenseAttr defence_attr_fmario;
static StatusVulnerability regist_fmario;
static PoseTableEntry pose_table_fmario_stay[15];
static BattleDataEntry data_table_fmario[2];
static BattleUnitKindPart parts_fmario[1];
static BattleWeapon weapon_masao_jump;
static BattleWeapon weapon_masao_hammer;
static BattleWeapon weapon_masao_kururin_jump;
static BattleWeapon weapon_masao_kaiten_hammer;
static EvtWord init_event_fmario[73];
static EvtWord dead_event_fmario[93];
static EvtWord damage_event_fmario[10];
static EvtWord attack_event_fmario[58];
static EvtWord marioAttackEvent_NormalJump[344];
static EvtWord marioAttackEvent_KururinJump[469];
static EvtWord marioAttackEvent_NormalHammer[299];
static EvtWord marioAttackEvent_KaitenHammer[299];
static EvtWord wait_event_fmario[6];

/**
 * Battle script helper: turns Doopliss (Rampell) black for the shadow look (faker_mario_makkuro_set)
 * and switches on the shadow tint on his first part's pose.
 */
static USER_FUNC(_mario_makkuro_set) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, -2));

    if (unit != NULL) {
        faker_mario_makkuro_set(unit);
        animPoseSetMaterialFlagOn(BtlUnit_GetPartsPtr(unit, 1)->poseId, ANIM_MATERIAL_TEV_CALLBACK(11));
    }
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_US
/** US only: restore the moves of the unit for this turn. */
USER_FUNC(boss_rampell_sync_max_moves) {
    BattleUnit* unit;
    s32 id = evtGetValue(event, event->args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit != NULL) {
        unit->maxMovesThisTurn = unit->movesRemaining;
    }
    return EVT_RETURN_DONE;
}
#endif

/** Battle script helper: clears the "away" flag in Vivian's party data so she is back in the party; returns 1. */
static USER_FUNC(vivian_comeback) {
    pouchGetPtr()->partyData[6].flags &= ~2;
    return 1;
}

/**
 * Battle script helper: spawns the "scanning" effect at (args[1], args[2], args[3]) on the unit args[0],
 * scaled to the unit's size (the beam that copies Mario).
 */
static USER_FUNC(eff_scanning) {
    EvtWord* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = effScanningEntry(0, x, y, z);
    effScanningData* scan = eff->userdata;

    scan->scale = unit->sizeMultiplier;
    return EVT_RETURN_DONE;
}

BattleUnitKind unit_boss_rampell = {
    77,
    "btl_un_hatena",
    40,
    0,
    1,
    1,
    52,
    0,
    0,
    100,
    0,
    70,
    7,
    50,
    48,
    4,
    48,
    0.0f,
    22.0f,
    0.0f,
    0,
    -3,
    0.0f,
    40.0f,
    0.0f,
    25.0f,
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
    12.0f,
    32.0f,
    0.0f,
    7.0f,
    22.0f,
    0.0f,
    50.0f,
    48.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_RNPL_DAMAGED1",
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
static StatusVulnerability regist = {60, 60, 60, 80, 60, 80, 100, 60, 100, 60, 100, 60, 100, 60, 60, 0, 0, 100, 60, 100, 100, 0};
#else
static StatusVulnerability regist = {60, 60, 70, 100, 60, 100, 100, 50, 100, 80, 100, 80, 100, 90, 60, 0, 0, 100, 60, 100, 100, 0};
#endif

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "K_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {50, "A_2"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_hatena", "c_ranpel", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 40.0f, 0.0f, 30, 40, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static BattleWeapon weapon_rampell_attack = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_FLIPS_SHELLED | SPECIAL_USABLE_IF_CONFUSED, // special
    COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY, // counterResistFlags
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
 * Camera move used in Doopliss' transformation:
 * puts the battle camera on a close view of the stage center (mode 3) for 37 frames.
 */
EVT_BEGIN(rampell_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Doopliss' transformation into Mario's double in the first battle:
 * the status window hides, the camera zooms in, Doopliss raises his arms and laughs (stg4_jin_08_02), flashes,
 * scans Mario and swaps places with a fake Mario unit with at least 10 HP;
 * he rises from the floor and speaks again (stg4_jin_08_03).
 */
EVT_BEGIN(to_faker_mario)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 2)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(rampell_zoom)
    CALL(evt_msg_print, 2, STRING("stg4_jin_08_02"), 0, BTL_UNIT_SELF)
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_ARM_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_MS(600)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_ARM_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_MS(600)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_ARM_UP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3A"))
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_LAUGH1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3B"))
    WAIT_MS(800)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_EYE_SHINE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_FLOAT_VALUE(LW(7), FLOAT(-6.0f))
    MULTIPLY_FLOAT(LW(7), LW(6))
    ADD_FLOAT(LW(0), LW(7))
    SET_FLOAT_VALUE(LW(7), FLOAT(33.0f))
    MULTIPLY_FLOAT(LW(7), LW(6))
    ADD_FLOAT(LW(1), LW(7))
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 3, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    SET_FLOAT_VALUE(LW(7), FLOAT(7.0f))
    MULTIPLY_FLOAT(LW(7), LW(6))
    ADD_FLOAT(LW(0), LW(7))
    SET_FLOAT_VALUE(LW(7), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(7), LW(6))
    ADD_FLOAT(LW(1), LW(7))
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 3, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_TRANSFORM4"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 7, LW(0), LW(1), LW(2), FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, -1000, -1000, 0)
    WAIT_MS(500)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    CALL(btlevtcmd_GetPos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    ADD(LW(0), 3)
    ADD(LW(1), -5)
    ADD(LW(2), 5)
    CALL(eff_scanning, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_MARIO, STRING("SFX_BOSS_RNPL_TRANSFORM2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_MARIO, STRING("SFX_BOSS_RNPL_TRANSFORM1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(1300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_MARIO, STRING("SFX_BOSS_RNPL_TRANSFORM3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(500)
    CALL_CHILD(rampell_zoom)
    CALL_CHILD(init_event_fmario)
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    IF_INT_LESS(LW(0), 10)
        CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, 10)
    END_IF
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_RNPLTRANSFORM5"), 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(evt_sub_intpl_msec_init, 11, -50, 0, 1000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(5), LW(0), LW(7))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_print, 2, STRING("stg4_jin_08_03"), 0, BTL_UNIT_SELF)
    WAIT_MS(200)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Init event of Doopliss: installs wait, phase, attack, damage and default confusion events,
 * clears unit work 0 (the form: 0 first speech, 1 fighting, 2 as the Mario double)
 * and stores half of his maximum HP in work 1 as the transformation threshold.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    MULTIPLY(LW(0), 50)
    DIVIDE(LW(0), 100)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Doopliss: runs the default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Death event of Doopliss: if he has not been the Mario double yet (work 0 is not 2) his defeat starts the
 * transformation instead (to_faker_mario).
 * Otherwise the status window hides, the camera zooms in on him and he says stg4_jin_08_04
 * before flopping down (EM_K_1, EM_D_2) and being removed.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        CALL_CHILD(to_faker_mario)
        RETURN
    END_IF
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_wait_move_end)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    CALL(evt_msg_print, 2, STRING("stg4_jin_08_04"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_K_1"))
    WAIT_FRAMES(192)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_D_2"))
    WAIT_MS(300)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    RETURN
EVT_END()

/**
 * Phase event of Doopliss: after the player's phase,
 * from turn 5 on he turns into the Mario double (to_faker_mario) if he has not already.
 * At work 0 he opens the fight with stg4_jin_08_01 (rampell_zoom) and sets work 0 to 1;
 * at work 1 he transforms as soon as his HP falls below the threshold in work 1.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 2)
                CALL(btlevtcmd_get_turn, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 5)
                    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                    CALL_CHILD(to_faker_mario)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                END_IF
            END_IF
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
                CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL_CHILD(rampell_zoom)
                CALL(evt_msg_print, 2, STRING("stg4_jin_08_01"), 0, BTL_UNIT_SELF)
                WAIT_MS(200)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                CASE_EQUAL(1)
                CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(1))
                IF_INT_LESS(LW(0), LW(1))
                    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                    CALL_CHILD(to_faker_mario)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                END_IF
            END_SWITCH
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Attack event of Doopliss: uses an enemy item if he has one,
 * otherwise always the claw attack (weapon_rampell_attack, via ogg_attack_event).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(&weapon_rampell_attack))
    CALL_CHILD(ogg_attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Doopliss's flying claw attack on one target (weapon in LW(9)):
 * he winds up (A_1A, A_1B), spins up and flies over the target at 2x motion speed (SFX_BOSS_RNPL_FLY1),
 * then drops onto it with SFX_BOSS_RNPL_FALL1.
 * The pre-damage check decides between a dodge and a hit with the action-command result, then he returns home.
 */
static EVT_BEGIN(ogg_attack_event)
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
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(0), 120)
    ADD(LW(1), 70)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(2.0f))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.5f))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(15)
        CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.0f))
    END_SIBLING_EVENT
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, 7, 4, 0, -1)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(0.75f))
    WAIT_MS(200)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
        CALL(evt_sub_intpl_msec_init, 1, 0, 135, 200)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(80)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(2.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.009765625f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 15, -1)
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
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(2.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_2"))
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("O_1"))
    WAIT_MS(800)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.0f))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(2.0f))
#endif
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 15, 0)
        CALL(evt_sub_intpl_init, 4, 135, 0, 20)
        LOOP(0)
            CALL(evt_sub_intpl_get_value_para, LW(0), LW(1))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(0))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), 60)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.75f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_RNPL_LANDING1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(2.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeSetMotionSpeed, BTL_UNIT_SELF, 1, FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    RETURN
EVT_END()

/** Wait (idle) event of the Doopliss: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static BattleUnitDefense defence_fmario = {0};

static BattleUnitDefenseAttr defence_attr_fmario = {0};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist_fmario = {50, 50, 50, 50, 50, 50, 100, 40, 100, 50, 100, 50, 100, 25, 50, 0, 0, 100, 50, 100, 100, 3};
#else
static StatusVulnerability regist_fmario = {50, 50, 70, 50, 50, 50, 100, 40, 100, 70, 100, 70, 100, 90, 50, 0, 0, 100, 50, 100, 100, 3};
#endif

static PoseTableEntry pose_table_fmario_stay[] = {
    {1, "EM_N_1"},
    {2, "EM_Y_2"},
    {9, "EM_Y_2"},
    {5, "EM_K_1"},
    {4, "EM_K_1"},
    {3, "EM_K_1"},
    {28, "EM_S_1"},
    {39, "EM_D_1"},
    {50, "EM_A_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {56, "EM_D_3"},
    {57, "EM_D_3"},
    {BTL_POSE_TALK, "EM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "EM_S_1"},
};

static BattleDataEntry data_table_fmario[] = {
    {49, dead_event_fmario},
    {0},
};

static BattleUnitKindPart parts_fmario[] = {
    {
        1, // partNum
        "btl_un_hatena", // partName
        "c_mario", // modelName
        {0}, // positionOffset
        {3.0f, 27.0f, 0.0f}, // hitBaseOffset
        {0.0f, 30.0f, 0.0f}, // hitCursorBaseOffset
        20, // shadowSize
        30, // hitHeight
        255, // baseAlpha
        &defence_fmario, // defense
        &defence_attr_fmario, // defenseAttr
        PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, // attributes
        0, // counterAttributes
        pose_table_fmario_stay, // poseTable
    },
};

static BattleWeapon weapon_masao_jump = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ATTACK_FX | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
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

static BattleWeapon weapon_masao_hammer = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ATTACK_FX | SPECIAL_USABLE_IF_CONFUSED, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
#else
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_PAYBACK, // counterResistFlags
#endif
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

static BattleWeapon weapon_masao_kururin_jump = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ATTACK_FX | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
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

static BattleWeapon weapon_masao_kaiten_hammer = {
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
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ATTACK_FX | SPECIAL_USABLE_IF_CONFUSED, // special
#if VERSION <= VERSION_DEMO_US
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
#else
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_PAYBACK, // counterResistFlags
#endif
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

/**
 * Camera shot on Mario's side of the stage (x = -110):
 * sets the battle camera to a fixed position and waits 37 frames for it to arrive.
 */
static EVT_BEGIN(mario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Camera shot on the enemy side (x = 115): sets the battle camera to a fixed position
 * and waits 37 frames for it to arrive.
 */
static EVT_BEGIN(enemy_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 115, 65, 332, 115, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Camera shot on the fake Mario (x = 90): sets the battle camera to a fixed position
 * and waits 37 frames for it to arrive.
 */
static EVT_BEGIN(fmario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Camera shot on the Goombella unit (x = 130): sets the battle camera to a fixed position
 * and waits 37 frames for it to arrive.
 */
static EVT_BEGIN(gparty_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 65, 332, 130, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Init event of Doopliss as Mario's double in the first battle:
 * switches to the fake Mario's pose table, data table, parts and resistances, installs his wait, attack,
 * damage and confusion events, clears all status ailments, makes him black (_mario_makkuro_set),
 * sets GW(17) to -1 and sets the Mario walk, run and jump sounds.
 */
static EVT_BEGIN(init_event_fmario)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(11), PTR(pose_table_fmario_stay))
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_fmario))
    CALL(btlevtcmd_ReplaceParts, BTL_UNIT_SELF, LW(11), PTR(parts_fmario), 1)
    CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&regist_fmario))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_fmario))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_fmario))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_fmario))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 4)
    CALL(btlevtcmd_ClearAllStatus, BTL_UNIT_SELF)
    CALL(_mario_makkuro_set)
    SET_VALUE(GW(17), -1)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_JUMP1"), STRING("SFX_BOSS_NM_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Death event of the fake Mario in the first battle:
 * the camera moves in on him, he says stg4_jin_08_04,
 * falls over with SFX_BOSS_NM_DOWN2 (EM_K_1, EM_D_2) and is removed.
 */
static EVT_BEGIN(dead_event_fmario)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_wait_move_end)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_S_1"))
    WAIT_MS(300)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("EM_T_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("EM_S_1"))
    CALL(evt_msg_print, 2, STRING("stg4_jin_08_04"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_K_1"))
    WAIT_FRAMES(152)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_DOWN2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_VOICE_NM_LAND_DAMAGE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_D_2"))
    WAIT_MS(1500)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    RETURN
EVT_END()

/** Damage event of the fake Mario: runs the default damage handling. */
static EVT_BEGIN(damage_event_fmario)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Attack event of the fake Mario in the first battle:
 * uses an enemy item if he has one, otherwise draws a jump
 * or a hammer (50/50) from Mario's attacks (the spin variants in the switch are never drawn).
 */
static EVT_BEGIN(attack_event_fmario)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(&weapon_masao_jump))
        CALL_CHILD(marioAttackEvent_NormalJump)
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(&weapon_masao_hammer))
        CALL_CHILD(marioAttackEvent_NormalHammer)
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(&weapon_masao_kururin_jump))
        CALL_CHILD(marioAttackEvent_KururinJump)
        CASE_EQUAL(3)
        SET_VALUE(LW(9), PTR(&weapon_masao_kaiten_hammer))
        CALL_CHILD(marioAttackEvent_KaitenHammer)
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Plays one of three Mario-style jump voices (SFX_BOSS_VOICE_NM_AC1_1, _2 or _5) at random. */
static EVT_BEGIN(jump_attack_voice)
    CALL(evt_sub_random, 2, LW(15))
    SWITCH(LW(15))
        CASE_EQUAL(0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VOICE_NM_AC1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CASE_EQUAL(1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VOICE_NM_AC1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CASE_EQUAL(2)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_VOICE_NM_AC1_5"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SWITCH
    RETURN
EVT_END()

/**
 * The fake Mario's jump attack (weapon_masao_jump):
 * walks to the take-off point and jumps onto the target with the Mario jump voice;
 * the pre-damage check decides between a dodge (he falls back down) and a hit,
 * after which he bounces back in three small hops and returns home.
 */
static EVT_BEGIN(marioAttackEvent_NormalJump)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetTakeoffPosition, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(6))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL_CHILD(jump_attack_voice)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, 0, -1)
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
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_D_2"))
    WAIT_FRAMES(40)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The fake Mario's spin jump (weapon_masao_kururin_jump):
 * like the normal jump, but after the first hop he spins in the air and dives onto the target a second time.
 */
static EVT_BEGIN(marioAttackEvent_KururinJump)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetTakeoffPosition, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(6))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL_CHILD(jump_attack_voice)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, 0, -1)
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
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_D_2"))
    WAIT_FRAMES(40)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
        CALL_CHILD(jump_attack_voice)
        CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 36, 0, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(15)
    DELETE_EVENT(LW(14))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(15))
    MULTIPLY(LW(15), -30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_Z_2"))
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 12, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    WAIT_FRAMES(15)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_JUMP_KURURIN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(12)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(15))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
    WAIT_FRAMES(15)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 4, 0, 0, 0, -1)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_J_1B"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 27)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The fake Mario's hammer attack (weapon_masao_hammer):
 * walks next to the target, raises the hammer (EM_A_1A to 1C, SFX_BOSS_NM_HAMMER_FURU2 and DON2) and swings it;
 * the pre-damage check decides between a dodge and a hit, then he returns home.
 */
static EVT_BEGIN(marioAttackEvent_NormalHammer)
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 24)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    ADD(LW(2), 5)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1A"))
    WAIT_MS(66)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_HAMMER_FURU2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(233)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1B"))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1C"))
    WAIT_MS(50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_HAMMER_DON2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(100)
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
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_S_1"))
    WAIT_MS(200)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The fake Mario's spinning hammer attack: the script is identical to marioAttackEvent_NormalHammer;
 * only the weapon in LW(9) (weapon_masao_kaiten_hammer, set by attack_event) differs.
 */
static EVT_BEGIN(marioAttackEvent_KaitenHammer)
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 24)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    ADD(LW(2), 5)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1A"))
    WAIT_MS(66)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_HAMMER_FURU2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(233)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1B"))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_A_1C"))
    WAIT_MS(50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_NM_HAMMER_DON2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(100)
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
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_S_1"))
    WAIT_MS(200)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("EM_W_1"))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait (idle) event of the fake Mario: shows the idle pose from the pose table. */
static EVT_BEGIN(wait_event_fmario)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
