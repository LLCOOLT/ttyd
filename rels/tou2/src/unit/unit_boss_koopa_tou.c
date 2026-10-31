// unit_boss_koopa_tou: Bowser, boss unit used in the Glitz Pit REL, battle unit.

#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "driver/icondrv.h"
#include "driver/camdrv.h"
#include "battle/battle.h"
#include "manager/evtmgr_cmd.h"
#include "driver/dispdrv.h"
#include "system.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_message.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "unit/unit_boss_koopa.h"
#include "evt/evt_msg.h"

static USER_FUNC(_icon_jump_icon);
static USER_FUNC(party_cannot_use_command);
static USER_FUNC(mario_cannot_use_command);

BattleUnitKind unit_boss_koopa_tou;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_koopa_hip_attack;
static BattleWeapon weapon_koopa_bite_attack;
static BattleWeapon weapon_koopa_critical_bite_attack;
static BattleWeapon weapon_koopa_fire_attack;
static EvtWord init_event[72];
static EvtWord entry_event[45];
static EvtWord damage_event[10];
static EvtWord dead_event[111];
static EvtWord phase_event[31];
static EvtWord harf_hp_event[62];
static EvtWord attack_event[108];
static EvtWord hip_attack_event[VERSION_PICK(419, 420)];
static EvtWord bite_attack_event[267];
static EvtWord critical_bite_attack_event[250];
static EvtWord fire_attack_event[345];
static EvtWord wait_event[6];

BattleUnitKind unit_boss_koopa_tou = {
    63,
    "btl_un_koopa",
    30,
    0,
    1,
    1,
    39,
    0,
    0,
    100,
    0,
    50,
    9,
    86,
    80,
    0,
    70,
    0.0f,
    40.0f,
    0.0f,
    0,
    0,
    40.0f,
    40.0f,
    0.0f,
    43.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    36.0f,
    72.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    86.0f,
    80.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOOPA_DAMAGED1",
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

static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {80, 60, 70, 50, 60, 50, 100, 40, 100, 75, 100, 75, 100, 60, 60, 0, 0, 100, 60, 100, 100, 0};
#else
static StatusVulnerability regist = {70, 60, 60, 100, 70, 100, 100, 40, 100, 75, 100, 75, 100, 90, 60, 0, 0, 100, 60, 100, 100, 0};
#endif

static PoseTableEntry pose_table[] = {
    {1, "KPA_N_3"},
    {2, "KPA_Z_6"},
    {9, "KPA_Z_6"},
    {5, "KPA_K_2"},
    {4, "KPA_S_2"},
    {3, "KPA_S_2"},
    {28, "KPA_S_1"},
    {29, "KPA_Q_2"},
    {30, "KPA_Q_2"},
    {31, "KPA_D_1"},
    {39, "KPA_D_1"},
    {50, "KPA_S_1"},
    {42, "KPA_R_1"},
    {40, "KPA_W_1"},
    {56, "KPA_S_1"},
    {57, "KPA_S_1"},
    {BTL_POSE_TALK, "KPA_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KPA_S_1"},
};

static PoseTableEntry pose_table_forward_leaning[] = {
    {1, "KPA_N_2"},
    {2, "KPA_Z_5"},
    {9, "KPA_Z_5"},
    {5, "KPA_K_1"},
    {4, "KPA_X_1"},
    {3, "KPA_X_1"},
    {28, "KPA_S_8"},
    {29, "KPA_D_4"},
    {30, "KPA_D_4"},
    {31, "KPA_D_4"},
    {39, "KPA_D_4"},
    {50, "KPA_S_8"},
    {42, "KPA_R_1"},
    {40, "KPA_W_1"},
    {56, "KPA_S_8"},
    {57, "KPA_S_8"},
    {BTL_POSE_TALK, "KPA_T_9"},
    {BTL_POSE_STAY_DEFAULT, "KPA_S_8"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_koopa", "c_koopa", 0.0f, 0.0f, 0.0f, 34.0f, 62.0f, 0.0f, 22.0f, 78.0f, 0.0f, 70, 80, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static BattleWeapon weapon_koopa_hip_attack = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    10, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 25, 25, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_koopa_bite_attack = {
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
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    30, // poisonChance
    10, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_koopa_critical_bite_attack = {
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
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
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

static BattleWeapon weapon_koopa_fire_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    1, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Camera helper for Bowser's talk: moves the camera to x = LW(0), looking at him from the front,
 * over 30 frames and waits 37 frames for it to arrive.
 */
static EVT_BEGIN(koopa_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_btl_camera_set_moveto, 0, LW(0), 95, 350, LW(0), 45, -300, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

/**
 * Init event of Bowser: registers his wait, phase, attack,
 * damage and entry events (confusion uses the default confuse event), sets unit work 1 and 4 to 0,
 * work 2 to half his max HP (the threshold for his half-HP line) and work 3 to 0 (that line not yet shown),
 * and sets his walk and run sounds, then starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    DIVIDE(LW(0), 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_MOVE1L"), STRING("SFX_BOSS_KOOPA_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_MOVE1L"), STRING("SFX_BOSS_KOOPA_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Bowser's entrance: he stands still, then laughs and strikes a pose ("KPA_Y_2") while the camera zooms in,
 * and says stg3_tou_403_06_01 before the fight starts.
 */
static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_S_1"))
    WAIT_FRAMES(60)
    CALL_CHILD(koopa_zoom)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_VOICE_KOOPA_LAUGH2_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_Y_2"))
    WAIT_MS(1000)
    CALL(evt_msg_print, 2, STRING("stg3_tou_403_06_01"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Bowser's defeat: if he is away from his home spot he walks back to it, waits for the attack to end,
 * zooms the camera and has him say the closing line (stg3_tou_403_06_03) with a satisfied voice
 * and the "KPA_D_2" collapse pose, then runs the common no-spin death.
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
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    END_IF
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL_CHILD(koopa_zoom)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KPA_D_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("KPA_D_1"))
    CALL(evt_msg_print, 2, STRING("stg3_tou_403_06_03"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_VOICE_KOOPA_SATIATED2_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_D_2"))
    WAIT_MS(700)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core_nospin_norotate)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Phase event of Bowser: after the player's phase, unless he is marked with the instant-kill status (27),
 * it declares the phase event and runs harf_hp_event, then restarts the wait event.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
        CALL_CHILD(harf_hp_event)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Bowser's half-HP line ("harf" is the original spelling of "half"):
 * the first time his HP drops below the value in unit work 2 (half his max HP) it sets unit work 3,
 * zooms in on him and has him say stg3_tou_403_06_02 in a new talk pose.
 */
static EVT_BEGIN(harf_hp_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(1))
        IF_INT_LESS(LW(0), LW(1))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL_CHILD(koopa_zoom)
            CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KPA_T_3"))
            CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("KPA_S_4"))
            CALL(evt_msg_print, 2, STRING("stg3_tou_403_06_02"), 0, BTL_UNIT_SELF)
            WAIT_MS(300)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Bowser's move choice. He uses an enemy item if one fits.
 * His first three turns are scripted by unit work 4: fire breath, then bite, then hip drop.
 * After that he draws lots with weights 30 (hip drop), 30 (bite),
 * 0 (critical bite, never drawn) and 30 (fire breath). LW(9) receives the weapon each sub-event uses.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(&weapon_koopa_fire_attack))
        CALL_CHILD(fire_attack_event)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 1)
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(&weapon_koopa_bite_attack))
        CALL_CHILD(bite_attack_event)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 2)
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(&weapon_koopa_hip_attack))
        CALL_CHILD(hip_attack_event)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 3)
        CASE_DEFAULT
        CALL(btlevtcmd_DrawLots, LW(0), 4, 30, 30, 0, 30)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(&weapon_koopa_hip_attack))
            CALL_CHILD(hip_attack_event)
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(&weapon_koopa_bite_attack))
            CALL_CHILD(bite_attack_event)
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(&weapon_koopa_critical_bite_attack))
            CALL_CHILD(critical_bite_attack_event)
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(&weapon_koopa_fire_attack))
            CALL_CHILD(fire_attack_event)
        END_SWITCH
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Bowser's Hip Drop: walks to the target, jumps up and slams down on it (camera shake on a hit).
 * If the action command result is 3 or less and the target is Mario or a partner,
 * it also seals one of that character's commands:
 * the lost command's icon is tossed across the screen with _icon_jump_icon
 * and an announcement message is shown (the US and later versions pass the partner to party_cannot_use_command).
 * Then he walks back home.
 */
static EVT_BEGIN(hip_attack_event)
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
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2A"))
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2B"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(25)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2C"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2D"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.25f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SUBTRACT(LW(2), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_HIP_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2E"))
    WAIT_MS(500)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(evt_btl_camera_shake_h, 0, 3, 0, 50, 13)
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_2E"))
    WAIT_MS(300)
    CALL(btlevtcmd_GetResultACDefence, LW(7))
    IF_INT_LESS_OR_EQUAL(LW(7), 3)
        SET_VALUE(LW(15), 0)
        CALL(btlevtcmd_GetUnitKind, LW(3), LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(222)
            CALL(mario_cannot_use_command, LW(15))
            CASE_BETWEEN(224, 230)
#if VERSION <= VERSION_JP
            CALL(party_cannot_use_command, LW(15))
#else
            CALL(party_cannot_use_command, LW(15), LW(3))
#endif
            CASE_DEFAULT
            SET_VALUE(LW(0), -1)
        END_SWITCH
        IF_INT_NOT_EQUAL(LW(0), -1)
            IF_INT_NOT_EQUAL(LW(15), 0)
                BEGIN_INLINE_EVENT
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
                    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(5), 60)
                    CALL(btlevtcmd_TransStageFloorPosition, LW(5), LW(6), LW(7))
                    CALL(_icon_jump_icon, LW(15), LW(0), LW(1), LW(2), LW(5), LW(6), LW(7), FLOAT(0.5f), 30)
                    SET_VALUE(LW(0), LW(5))
                    SET_VALUE(LW(1), LW(6))
                    SET_VALUE(LW(2), LW(7))
                    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(5), 40)
                    CALL(_icon_jump_icon, LW(15), LW(0), LW(1), LW(2), LW(5), LW(6), LW(7), FLOAT(0.5f), 20)
                    SET_VALUE(LW(0), LW(5))
                    SET_VALUE(LW(1), LW(6))
                    SET_VALUE(LW(2), LW(7))
                    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(5), 25)
                    CALL(_icon_jump_icon, LW(15), LW(0), LW(1), LW(2), LW(5), LW(6), LW(7), FLOAT(0.5f), 12)
                END_INLINE_EVENT
            END_IF
            BEGIN_SIBLING_EVENT
                CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, LW(0), 120)
            END_SIBLING_EVENT
        END_IF
    END_IF
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_S_1"))
    RETURN
EVT_END()

/**
 * Bowser's Bite: walks to the side of the target, bites down (two bite sounds) and does the weapon damage,
 * then walks back home.
 */
static EVT_BEGIN(bite_attack_event)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 65)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3A"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_BITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(170)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3B"))
    WAIT_MS(150)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_BITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3C"))
    WAIT_MS(150)
    GOTO(98)
    LABEL(91)
    WAIT_MS(100)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3C"))
    WAIT_MS(150)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_S_1"))
    RETURN
EVT_END()

/**
 * Bowser's strong Bite: like bite_attack_event but on a hit he holds the target in his jaws for 1.5 seconds
 * ("KPA_A_4") before the damage lands.
 * It is in the code but attack_event gives it zero weight, so it never runs.
 */
static EVT_BEGIN(critical_bite_attack_event)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 65)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3A"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_BITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(170)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3B"))
    WAIT_MS(150)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_BITE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
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
    WAIT_MS(100)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3C"))
    WAIT_MS(150)
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_4"))
    WAIT_MS(1500)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_3C"))
    WAIT_MS(150)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    RETURN
EVT_END()

/**
 * Bowser's Fire Breath: moves in front of the party,
 * breathes fire for about 1.5 seconds and hits every target in turn (AttackDeclareAll,
 * with the action command result taken from the first),
 * using the "gonbaba_breath" fire effect scaled by his size. Then he returns to his home position.
 */
static EVT_BEGIN(fire_attack_event)
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
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 120)
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(170)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_1A"))
    WAIT_MS(300)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_VOICE_KOOPA_FIRE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOOPA_FIRE_BREATH1"), EVT_NULLPTR, 0, LW(15))
    BEGIN_INLINE_EVENT
        WAIT_MS(1500)
        CALL(evt_snd_sfxoff, LW(15))
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_1B"))
    WAIT_MS(300)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(5))
    SET_FLOAT_VALUE(LW(6), FLOAT(60.0f))
    MULTIPLY_FLOAT(LW(6), LW(5))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), LW(6))
    SET_FLOAT_VALUE(LW(6), FLOAT(22.5f))
    MULTIPLY_FLOAT(LW(6), LW(5))
    ADD_FLOAT(LW(1), LW(6))
    SUBTRACT(LW(2), 5)
    MULTIPLY_FLOAT(LW(5), FLOAT(3.5f))
    CALL(evt_eff, STRING(""), STRING("gonbaba_breath"), 7, LW(0), LW(1), LW(2), LW(5), 90, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_1C"))
    WAIT_MS(300)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LABEL(10)
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
    WAIT_MS(1200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_A_1D"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KPA_R_1"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static const char* cmd_disable_string[] = {
    "btl_jump_cmd_disable",
    "btl_hammer_cmd_disable",
    "btl_item_cmd_disable",
    "btl_party_tech_cmd_disable",
    "btl_party_item_cmd_disable",
};

/** Draw callback of _icon_jump_icon: draws the flying icon at its current position. */
static void _disp_icon(CameraId camera, void* param) {
    EventEntry* event = param;

    iconDispGx(&((IconJumpWork*)event->userdatap[0])->pos, 0, event->userdata[1], 1.0f);
}

/**
 * Script helper that tosses an icon along an arc:
 * arg0 = icon id, arg1..3 = start, arg4..6 = end, arg7 = gravity, arg8 = frames.
 * Runs until it lands; used to show the command that Bowser takes away.
 */
static USER_FUNC(_icon_jump_icon) {
    EvtWord* args = event->args;
    s32 icon = evtGetValue(event, args[0]);
    f32 x0 = evtGetFloat(event, args[1]);
    f32 y0 = evtGetFloat(event, args[2]);
    f32 z0 = evtGetFloat(event, args[3]);
    f32 x1 = evtGetFloat(event, args[4]);
    f32 y1 = evtGetFloat(event, args[5]);
    f32 z1 = evtGetFloat(event, args[6]);
    f32 gravity = evtGetFloat(event, args[7]);
    s32 frames = evtGetValue(event, args[8]);
    IconJumpWork* wk;

    if (isFirstCall) {
        Vec start;

        event->userdatap[0] = BattleAlloc(sizeof(IconJumpWork));
        wk = event->userdatap[0];
        wk->end.x = x1;
        wk->end.y = y1;
        wk->end.z = z1;
        start.x = x0;
        start.y = y0;
        start.z = z0;
        wk->pos = start;
        wk->start = start;
        wk->gravity = gravity;
        wk->frames = frames;
        wk->vy = (wk->end.y - wk->start.y) / wk->frames + wk->gravity * wk->frames / 2;
        wk->speed = distABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z) / wk->frames;
        event->userdata[1] = icon;
        event->userdata[2] = 0;
    }
    wk = event->userdatap[0];
    if (event->userdata[2]) {
        BattleFree(wk);
        return EVT_RETURN_DONE;
    }
    wk->pos.y += wk->vy;
    wk->vy -= wk->gravity;
    if (wk->vy < 0.0f && wk->pos.y < wk->end.y) {
        wk->pos.y = wk->end.y;
    }
    btlMovePos(wk->speed, angleABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z), &wk->pos.x, &wk->pos.z);
    wk->frames--;
    if (wk->frames <= 0) {
        event->userdata[2] = 1;
        wk->pos = wk->end;
    }
    dispEntry(CAMERA_3D, 900.0f, 1, _disp_icon, event);
    return EVT_RETURN_BLOCK;
}

/**
 * Guess: script helper for Bowser's command-seal attack on the partner:
 * disables either the partner's special command or its item command for 3 turns
 * and gives the matching message key in LW(0); arg0 (and arg1, the partner, on US and later) selects the weapon
 * id written back.
 */
static USER_FUNC(party_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(1);
    s32 var = event->args[0];
#if VERSION >= VERSION_US
    s32 id = evtGetValue(event, event->args[1]);
    s32 weapon = 0;
    BattleUnit* unit;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
#else
    s32 weapon = 0;
#endif
#if VERSION >= VERSION_US

    switch (r) {
        case 0:
            if (unit != NULL) {
                unit->usCommandDisabled[0] = 3;
            }
            weapon = 344;
            break;
        case 1:
            if (unit != NULL) {
                unit->usCommandDisabled[1] = 3;
            }
            weapon = 340;
            break;
    }
#else
    switch (r) {
        case 0:
            wp->commandDisabled[3] = 3;
            weapon = 336;
            break;
        case 1:
            wp->commandDisabled[4] = 3;
            weapon = 332;
            break;
    }
#endif
    event->lwData[0] = (EvtWord)cmd_disable_string[r + 3];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}

/**
 * Guess: script helper for Bowser's command-seal attack on Mario:
 * randomly disables jump, hammer or item for 3 turns;
 * LW(0) receives the message key of the disabled command and arg0 the weapon id used to show it.
 */
static USER_FUNC(mario_cannot_use_command) {
    BattleWork* wp = _battleWorkPointer;
    s32 r = irand(2);
    s32 var = event->args[0];
    s32 weapon = 0;

    switch (r) {
        case 0:
            wp->commandDisabled[0] = 3;
#if VERSION >= VERSION_US
            weapon = 334;
#else
            weapon = 326;
#endif
            break;
        case 1:
            wp->commandDisabled[1] = 3;
#if VERSION >= VERSION_US
            weapon = 337;
#else
            weapon = 329;
#endif
            break;
        case 2:
            wp->commandDisabled[2] = 3;
#if VERSION >= VERSION_US
            weapon = 340;
#else
            weapon = 332;
#endif
            break;
    }
    event->lwData[0] = (EvtWord)cmd_disable_string[r];
    evtSetValue(event, var, weapon);
    return EVT_RETURN_DONE;
}
