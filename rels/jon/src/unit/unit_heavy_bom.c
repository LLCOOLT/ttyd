// Pit of 100 Trials battle unit: the Bob-ulk (`heavy_bom`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "string.h"
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "battle/battle_database_common.h"
#include "evt/evt_snd.h"
#include "data_tables.h"
#include "version.h"

static USER_FUNC(_set_draw_callback);

BattleUnitKind unit_heavy_bom;
static BattleWeapon weapon_heavy_bomb_super_explosion;
static BattleWeapon weapon_heavy_bomb_guard;
static BattleWeapon weapon_heavy_bomb_guard_2;
static BattleWeapon weapon_heavy_bomb_guard_3;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static PoseTableEntry pose_table_3[16];
static PoseTableEntry pose_table_3_fire[16];
static PoseTableEntry pose_table_2[16];
static PoseTableEntry pose_table_2_fire[16];
static PoseTableEntry pose_table_1[16];
static PoseTableEntry pose_table_1_fire[16];
static PoseTableEntry pose_table_0_fire[16];
static PoseTableEntry pose_table_0[16];
static PoseTableEntry pose_table_3_to_2[13];
static PoseTableEntry pose_table_2_to_1[13];
static PoseTableEntry pose_table_1_to_0[13];
static BattleDataEntry data_table[3];
static PoseSoundTiming pose_sound_timing_table[9];
static BattleUnitKindPart parts[2];
static EvtWord init_event[57];
static EvtWord damage_event[118];
static EvtWord phase_event[126];
static EvtWord attack_event[175];
static EvtWord wait_event[6];
static EvtWord dead_event[52];
#if VERSION >= VERSION_US
static EvtWord explosion_event[254];
#else
static EvtWord explosion_event[247];
#endif

BattleUnitKind unit_heavy_bom = {
    92,
    "btl_un_heavy_bom",
    6,
    0,
    1,
    1,
    22,
    0,
    4,
    70,
    0,
    40,
    9999,
    54,
    70,
    7,
    70,
    0.0f,
    35.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    0.0f,
    27.0f,
    45.5f,
    0.0f,
    0.0f,
    35.0f,
    0.0f,
    54.0f,
    70.0f,
    0,
    0,
    0,
    2,
    100,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HEAVYB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static BattleWeapon weapon_heavy_bomb_super_explosion = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    3, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_UNGUARDABLE, // special
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
    {0, 50, 50, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_heavy_bomb_guard = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, // atkChangeTime..atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    3, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_heavy_bomb_guard_2 = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, // burnChance..sizeChangeStrength
    100, // atkChangeChance
#if VERSION <= VERSION_DEMO_US
    2, // atkChangeTime
#else
    3, // atkChangeTime
#endif
    3, // atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleWeapon weapon_heavy_bomb_guard_3 = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
#if VERSION <= VERSION_DEMO_US
    6, // chargeStrength
#else
    3, // chargeStrength
#endif
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 50, 70, 0, 70, 150, 100, 70, 100, 70, 100, 70, 100, 70, 70, 80, 20, 100, 70, 100, 100, 95};
#else
static StatusVulnerability regist = {90, 75, 70, 0, 70, 150, 100, 100, 100, 80, 100, 80, 100, 95, 70, 80, 20, 100, 70, 100, 100, 95};
#endif

static PoseTableEntry pose_table_3[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {39, "D_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "S_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static PoseTableEntry pose_table_3_fire[] = {
    {1, "N_1"},
    {9, "Y_1"},
    {2, "Y_1"},
    {3, "K_1"},
    {4, "X_1"},
    {5, "K_1"},
    {9, "Z_1"},
    {28, "S_1"},
    {29, "D_1"},
    {35, "S_1"},
    {31, "S_1"},
    {39, "D_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "S_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static PoseTableEntry pose_table_2[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2B"},
    {28, "S_2B"},
    {29, "D_2"},
    {35, "S_2B"},
    {31, "S_2B"},
    {39, "D_2"},
    {56, "X_2"},
    {57, "X_2"},
    {BTL_POSE_TALK, "S_2B"},
    {BTL_POSE_STAY_DEFAULT, "S_2B"},
};

static PoseTableEntry pose_table_2_fire[] = {
    {1, "N_2"},
    {9, "Y_2"},
    {2, "Y_2"},
    {3, "K_2"},
    {4, "X_2"},
    {5, "K_2"},
    {9, "Z_2A"},
    {28, "S_2A"},
    {29, "D_2"},
    {35, "S_2A"},
    {31, "S_2A"},
    {39, "D_2"},
    {56, "X_2"},
    {57, "X_2"},
    {BTL_POSE_TALK, "S_2A"},
    {BTL_POSE_STAY_DEFAULT, "S_2A"},
};

static PoseTableEntry pose_table_1[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3B"},
    {28, "S_3B"},
    {29, "D_3"},
    {35, "S_3B"},
    {31, "S_3B"},
    {39, "D_3"},
    {56, "X_3"},
    {57, "X_3"},
    {BTL_POSE_TALK, "S_3B"},
    {BTL_POSE_STAY_DEFAULT, "S_3B"},
};

static PoseTableEntry pose_table_1_fire[] = {
    {1, "N_3"},
    {9, "Y_3"},
    {2, "Y_3"},
    {3, "K_3"},
    {4, "X_3"},
    {5, "K_3"},
    {9, "Z_3A"},
    {28, "S_3A"},
    {29, "D_3"},
    {35, "S_3A"},
    {31, "S_3A"},
    {39, "D_3"},
    {56, "X_3"},
    {57, "X_3"},
    {BTL_POSE_TALK, "S_3A"},
    {BTL_POSE_STAY_DEFAULT, "S_3A"},
};

static PoseTableEntry pose_table_0_fire[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4A"},
    {28, "S_4A"},
    {29, "D_4"},
    {35, "S_4A"},
    {31, "S_4A"},
    {39, "D_4"},
    {56, "X_4"},
    {57, "X_4"},
    {BTL_POSE_TALK, "S_4A"},
    {BTL_POSE_STAY_DEFAULT, "S_4A"},
};

static PoseTableEntry pose_table_0[] = {
    {1, "N_4"},
    {9, "Y_4"},
    {2, "Y_4"},
    {3, "K_4"},
    {4, "X_4"},
    {5, "K_4"},
    {9, "Z_4B"},
    {28, "S_4B"},
    {29, "D_4"},
    {35, "S_4B"},
    {31, "S_4B"},
    {39, "D_4"},
    {56, "X_4"},
    {57, "X_4"},
    {BTL_POSE_TALK, "S_4B"},
    {BTL_POSE_STAY_DEFAULT, "S_4B"},
};

static PoseTableEntry pose_table_3_to_2[] = {
    {1, "B_4"},
    {9, "B_1"},
    {2, "B_1"},
    {3, "B_7"},
    {4, "B_10"},
    {5, "B_7"},
    {28, "B_1"},
    {31, "B_1"},
    {39, "B_1"},
    {56, "B_10"},
    {57, "B_10"},
    {BTL_POSE_TALK, "B_1"},
    {BTL_POSE_STAY_DEFAULT, "B_1"},
};

static PoseTableEntry pose_table_2_to_1[] = {
    {1, "B_5"},
    {9, "B_2"},
    {2, "B_2"},
    {3, "B_8"},
    {4, "B_11"},
    {5, "B_8"},
    {28, "B_2"},
    {31, "B_2"},
    {39, "B_2"},
    {56, "B_11"},
    {57, "B_11"},
    {BTL_POSE_TALK, "B_2"},
    {BTL_POSE_STAY_DEFAULT, "B_2"},
};

static PoseTableEntry pose_table_1_to_0[] = {
    {1, "B_6"},
    {9, "B_3"},
    {2, "B_3"},
    {3, "B_9"},
    {4, "B_12"},
    {5, "B_9"},
    {28, "B_3"},
    {31, "B_3"},
    {39, "B_3"},
    {56, "B_12"},
    {57, "B_12"},
    {BTL_POSE_TALK, "B_3"},
    {BTL_POSE_STAY_DEFAULT, "B_3"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {52, explosion_event},
    {0, NULL},
};

static PoseSoundTiming pose_sound_timing_table[] = {
    {"S_3A", 0.01f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.26666668f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.53333336f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_3A", 0.8f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.01f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.16666667f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.33333334f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {"S_4A", 0.5f, NULL, "SFX_ENM_HEAVYB_WAIT3", 0, 1},
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_heavy_bom", "c_heavy", 0.0f, 0.0f, 0.0f, 15.0f, 50.0f, 0.0f, 0.0f, 65.0f, 0.0f, 65, 70, 255, &defence, &defence_attr, 0x9, 0, pose_table_3},
    {2, "ヘビーボム", "c_heavy", 0.0f, 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x2010000, 0, pose_table_3},
};

/**
 * Init script of the Bob-ulk: registers its wait, phase,
 * attack and damage handlers and the default confusion handler.
 * Unit work 0 (fuse lit) is cleared, unit work 1 (fuse stages left) is 3,
 * unit work 2 (fuse sound handle) is -1 and unit work 3 (guard cycle) is 0.
 * It sets the fuse part's pose (F_1), the pose sound timing table and the draw callback for the fuse flame.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("F_1"))
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
    CALL(_set_draw_callback)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage script of the Bob-ulk.
 * If it has status 9 while its fuse is lit, the fuse sound stops,
 * the fuse is put out and the pose table for the current fuse stage is restored.
 * A damaging hit with damage code 24, 25, 27, 46, 50,
 * 52 or 54 (Guess: the fire and explosion kinds) sets it off at once (pose 29, dead_event);
 * anything else takes the default damage handling.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 9, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
            CALL(evt_snd_sfxoff, LW(0))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1))
                CASE_EQUAL(0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_0))
            END_SWITCH
        END_IF
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(25)
            CASE_OR_EQUAL(52)
            CASE_OR_EQUAL(46)
            CASE_OR_EQUAL(50)
            CASE_OR_EQUAL(54)
            GOTO(50)
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 29)
    CALL_CHILD(dead_event)
    RETURN
EVT_END()

/**
 * After the player's phase, if the fuse is lit, the Bob-ulk burns one fuse stage:
 * the stage 3 to 2, 2 to 1 and 1 to 0 pose tables are played with SFX_ENM_HEAVYB_WAIT2
 * and the stage in unit work 1 goes down.
 * When the fuse is already at 0 it instead plays pose K_4 and queues the explosion (after-reaction 52).
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("K_4"))
                CALL(btlevtcmd_AfterReactionEntry, BTL_UNIT_SELF, 52)
                RETURN
            END_IF
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_WAIT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(3)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_3_to_2))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2_to_1))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1_to_0))
            END_SWITCH
            CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
            WAIT_FRAMES(40)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(2)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_2_fire))
                CASE_EQUAL(1)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_1_fire))
                CASE_EQUAL(0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_0_fire))
            END_SWITCH
            CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
            RETURN
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack script of the Bob-ulk, with SFX_ENM_HEAVYB_ATTACK1
 * and the pose for the current fuse stage (G_1 to G_4).
 * If the fuse is not lit it lights it: the looping fuse sound starts (handle kept in unit work 2)
 * and unit work 0 and unit flag 16 are set.
 * If it is already lit it instead applies one of its three guard weapons to itself, cycling through them.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_3"))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_4"))
        END_SWITCH
        WAIT_FRAMES(40)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_WAIT1"), EVT_NULLPTR, 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 16)
    ELSE
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_3"))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_4"))
        END_SWITCH
        WAIT_FRAMES(40)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
            CASE_EQUAL(1)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard_2))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 2)
            CASE_EQUAL(2)
            SET_VALUE(LW(12), PTR(&weapon_heavy_bomb_guard_3))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
        END_SWITCH
        CALL(btlevtcmd_WeaponAftereffect, LW(12))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(12), 256, LW(5))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait script: plays the Bob-ulk's idle pose from its current pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Defeat script of the Bob-ulk: stops the fuse sound, then,
 * if the killing blow has a fire or explosion damage code (24, 25, 27, 46, 50, 52 or 54),
 * queues the explosion (after-reaction 52); otherwise it dies the normal way.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_snd_sfxoff, LW(0))
    END_IF
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(27)
        CASE_OR_EQUAL(24)
        CASE_OR_EQUAL(25)
        CASE_OR_EQUAL(52)
        CASE_OR_EQUAL(46)
        CASE_OR_EQUAL(50)
        CASE_OR_EQUAL(54)
        GOTO(50)
        CASE_END
    END_SWITCH
    LABEL(10)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core)
    RETURN
    LABEL(50)
    CALL(btlevtcmd_AfterReactionEntry, BTL_UNIT_SELF, 52)
    RETURN
EVT_END()

/**
 * The Bob-ulk blows up (after-reaction 52): stops the fuse sound,
 * plays SFX_ENM_HEAVYB_ATTACK3 and a sequence of "bomb" explosion effects scaled to its size
 * while the stage fog is cleared, then deals the super explosion weapon's damage to every enemy it can hit.
 * It then dies and is removed from the battle.
 */
static EVT_BEGIN(explosion_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    CALL(evt_snd_sfxoff, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, -1)
#if VERSION >= VERSION_US
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 60, 4)
#endif
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HEAVYB_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
    DIVIDE(LW(5), 2)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    ADD(LW(1), LW(5))
    CALL(evt_eff, 0, STRING("bomb"), 5, LW(0), LW(1), LW(2), FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_StageDispellFog)
    WAIT_MS(300)
    CALL(evt_eff, 0, STRING("bomb"), 4, -40, 30, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 40, 90, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 40, 30, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, -40, 90, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, -100, 60, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(125)
    CALL(evt_eff, 0, STRING("bomb"), 4, 100, 60, 20, FLOAT(2.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_heavy_bomb_super_explosion))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_heavy_bomb_super_explosion), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_heavy_bomb_super_explosion))
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_heavy_bomb_super_explosion))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_heavy_bomb_super_explosion), 256, LW(5))
    IF_INT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_heavy_bomb_super_explosion), 256, LW(5))
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(99)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(subsetevt_dead_core)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

void animPoseDrawShape(s32 poseId, s32 shapeIdx);

/**
 * Pose draw callback: draws the fuse flame (a plane shape of part 2)
 * when the body's animation group is the locator matching the current fuse stage in work[1] (locator11 down to
 * locator8); does nothing while work[0] is 0.
 */
static void _fire_point_callback(BattleUnitPart* part, s32 group) {
    BattleUnit* unit = part->owner;
    const char* name;
    s32 poseId;

    if (unit->work[0] == 0) {
        return;
    }
    poseId = part->poseId;
    switch (unit->work[1]) {
        case 0:
            name = "locator11";
            break;
        case 1:
            name = "locator10";
            break;
        case 2:
            name = "locator9";
            break;
        case 3:
        default:
            name = "locator8";
            break;
    }
    if (strcmp(name, animPoseGetGroupName(poseId, group)) == 0) {
        s32 shapePose = BtlUnit_GetPartsPtr(unit, 2)->poseId;
        s32 shape = animPoseGetShapeIdx(shapePose, "pPlaneShape3");
        animPoseDrawShape(shapePose, shape);
    }
}

/**
 * Script helper: hooks _fire_point_callback onto the bomb's body (part 1), and hides part 2, the fuse flame,
 * so the callback can draw it at the fuse's locator.
 */
static USER_FUNC(_set_draw_callback) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 1);

    animPoseSetDispCallBack(part->poseId, _fire_point_callback, part);
    BtlUnit_GetPartsPtr(unit, 2)->attributes |= PART_ATTR_HIDDEN;
    return EVT_RETURN_DONE;
}
