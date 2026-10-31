// Palace of Shadow battle unit: the Gloomtail (boss) (`boss_bunbaba`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_map.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "version.h"

static USER_FUNC(_leg_smoke_effect);

BattleUnitKind unit_boss_bunbaba;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
#if VERSION <= VERSION_DEMO_US
static PoseTableEntry pose_table[7];
#else
static PoseTableEntry pose_table[9];
#endif
static BattleDataEntry data_table[3];
static BattleUnitKindPart parts[2];
BattleWeapon weapon_bunbaba_fumituke_attack;
BattleWeapon weapon_bunbaba_kamituki_attack;
BattleWeapon weapon_bunbaba_poison_attack;
BattleWeapon weapon_bunbaba_eq_attack;
BattleWeapon weapon_bunbaba_charge;
BattleWeapon weapon_bunbaba_mega_attack;
static EvtWord init_event[53];
static EvtWord damage_event[10];
extern EvtWord bunbaba_damage_sub_event[];
static EvtWord dead_event[264];
static EvtWord phase_event[160];
static EvtWord attack_event[237];
static EvtWord wait_event[6];

BattleUnitKind unit_boss_bunbaba = {
    132,
    "btl_un_bunbaba",
    80,
    0,
    1,
    1,
    76,
    0,
    0,
    100,
    0,
    50,
    6,
    230,
    170,
    -210,
    45,
    0.0f,
    0.0f,
    0.0f,
    -250,
    0,
    280.0f,
    40.0f,
    0.0f,
    115.0f,
    0.0f,
    -10.0f,
#if VERSION >= VERSION_US
    115.0f,
#else
    0.0f,
#endif
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    250.0f,
#else
    20.0f,
#endif
    0.0f,
    250.0f,
    0.0f,
    50.0f,
    380.0f,
    110.0f,
    50.0f,
    -290.0f,
    85.0f,
    0.0f,
    230.0f,
    170.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_GNB_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {40, 40, 40, 100, 40, 100, 100, 0, 0, 0, 100, 0, 100, 40, 40, 0, 0, 100, 40, 0, 0, 1};
#else
static StatusVulnerability regist = {30, 30, 30, 100, 30, 100, 100, 0, 0, 0, 100, 0, 100, 70, 30, 0, 0, 100, 30, 0, 0, 1};
#endif

static PoseTableEntry pose_table[] = {
    {1, "GNB_N_1"},
    {5, "GNB_X_1"},
#if VERSION >= VERSION_JP
    {3, "GNB_X_1"},
    {2, "GNB_D2_1"},
#endif
    {28, "GNB_S_3"},
    {BTL_POSE_TALK, "GNB_T_3"},
    {31, "GNB_S_3"},
    {39, "GNB_D_1"},
    {BTL_POSE_STAY_DEFAULT, "GNB_S_3"},
};

static BattleDataEntry data_table[] = {
    {9, bunbaba_damage_sub_event},
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_bunbaba", "c_gonbaba_b", 0.0f, 0.0f, 0.0f, 230.0f, 36.0f, 60.0f, 230.0f, 36.0f, 60.0f, 20, 30, 255, &defence, &defence_attr, 0x2, 0, pose_table},
    {2, "btl_un_bunbaba", "c_gonbaba_b", 100.0f, 0.0f, 0.0f, 250.0f, 110.0f, 25.0f, 250.0f, 110.0f, 25.0f, 20, 30, 255, &defence, &defence_attr, 0x1600009, 0, pose_table},
};

BattleWeapon weapon_bunbaba_fumituke_attack = {
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
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    11, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 10, 0, 0, 0}, // stageEffectRates
};

BattleWeapon weapon_bunbaba_kamituki_attack = {
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
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_UNGUARDABLE, // special
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

BattleWeapon weapon_bunbaba_poison_attack = {
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
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..dizzyTime
    50, // poisonChance
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

BattleWeapon weapon_bunbaba_eq_attack = {
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
    {10, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_FLOATING_2 | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_FLIPS_SHELLED, // special
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

BattleWeapon weapon_bunbaba_charge = {
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
    weaponGetPowerDefault, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    8, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon weapon_bunbaba_mega_attack = {
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
    {8, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
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
 * Entry event of the Gloomtail fight: the camera moves in on Gloomtail while Mario
 * and the partner strike a startled pose, Gloomtail rises (GNB_F_3) and roars with a camera shake,
 * and Mario and the partner ready themselves before the battle starts.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_map_replayanim, 0, STRING("dontyo"))
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 0, 110, 1080, 0, 93, -2, 1, 0)
    CALL(btlevtcmd_GetStageSize, LW(6), EVT_NULLPTR, EVT_NULLPTR)
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_PARTNER, LW(3), LW(4), LW(5))
    CALL(btlevtcmd_SetPos, BTL_UNIT_MARIO, LW(6), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_PARTNER, LW(6), LW(4), LW(5))
    CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(3), EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), LW(3))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_MARIO, 1, 42)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_PARTNER, LW(0), 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_PARTNER, LW(3), LW(4), LW(5))
    SET_VALUE(LW(8), LW(0))
    SUBTRACT(LW(8), LW(3))
    IF_INT_LESS(LW(8), 0)
        MULTIPLY(LW(8), -1)
    END_IF
    CALL(btlevtcmd_GetStageSize, LW(6), EVT_NULLPTR, EVT_NULLPTR)
    SET_VALUE(LW(7), LW(6))
    ADD(LW(7), LW(8))
    MULTIPLY(LW(6), -1)
    MULTIPLY(LW(7), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_MARIO, LW(6), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_PARTNER, LW(7), LW(4), LW(5))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_PARTNER, FLOAT(6.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_PARTNER, LW(3), LW(4), LW(5), 0, -1, 0)
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_PARTNER, LW(0), 43)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_MARIO, FLOAT(6.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_MARIO, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_I_Y"))
    WAIT_MS(33)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_F_3"))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_MS(166)
    BEGIN_INLINE_EVENT
        WAIT_MS(83)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_I_O"))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_MARIO, FLOAT(0.2998047f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_MARIO, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_snd_se, BTL_UNIT_MARIO, STRING("SFX_VOICE_MARIO_SURPRISED2_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_MARIO, LW(0), LW(1), LW(2), 25, -1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(83)
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_PARTNER, FLOAT(0.2998047f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_PARTNER, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_PARTNER, LW(0), LW(1), LW(2), 25, -1)
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_PARTNER, LW(0), 5)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_GNB_APPEAR1"), 0)
    CALL(evt_btl_camera_shake_h, 1, 8, 0, 20, 13)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_I_Y"))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_PARTNER, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_PARTNER, LW(0), 43)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, -233, 45, 452, 56, 125, 37, 60, 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("GNB_T_3"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("GNB_S_3"))
    CALL(evt_msg_print, 2, STRING("stg8_las_49_01"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_MARIO)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 3)
    RETURN
EVT_END()

/**
 * Init event of Gloomtail: installs its wait, phase, attack, damage and confusion events and entry event,
 * and clears unit work 1 (the flag that its last line before death was spoken).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetTalkBodyId, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_SetBaseScale, BTL_UNIT_SELF, FLOAT(1.2998047f), FLOAT(1.2998047f), FLOAT(0.5f))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of Gloomtail: default damage handling. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Event script: Gloomtail's sub-event when he is hit:
 * plays the pain animation of the part that was hit (GNB_D_2 for the head part 1, GNB_D_1 otherwise) and,
 * if the hit did no damage, a miss sound at the hit position.
 */
EVT_BEGIN(bunbaba_damage_sub_event)
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(11))
    IF_INT_EQUAL(LW(11), 1)
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("GNB_D_2"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("GNB_D_1"))
    END_IF
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_ATTACK_MISS2"), LW(0), LW(1), LW(2), 0)
    END_IF
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * Dead event of Gloomtail: it collapses (GNB_X_1), the camera closes in,
 * the status window is hidden and Gloomtail says its last words (stg8_las_49_08)
 * before the death animation (GNB_D_3, GNB_H_x) and the unit is removed.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_X_1"))
    CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_DOWN1"), EVT_NULLPTR, 0, -250, 0, 0, LW(15))
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_wait_move_end)
    CALL(evt_btl_camera_set_mode, 1, 3)
    SET_VALUE(LW(1), 160)
    SET_VALUE(LW(2), 536)
    CALL(btlevtcmd_GetStageAudienceAreaSize, EVT_NULLPTR, LW(5), EVT_NULLPTR)
    ADD(LW(1), LW(5))
    CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, EVT_NULLPTR, LW(5))
    ADD(LW(2), LW(5))
    ADD(LW(2), 80)
    SET_VALUE(LW(5), LW(1))
    SUBTRACT(LW(5), 37)
    SET_VALUE(LW(6), LW(2))
    SUBTRACT(LW(6), 511)
    CALL(evt_btl_camera_set_moveto, 1, 93, LW(1), LW(2), 93, LW(5), LW(6), 30, 0)
    WAIT_MS(1500)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("GNB_X_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("GNB_X_1"))
    CALL(evt_msg_print, 2, STRING("stg8_las_49_08"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, -38, 33, 1005, -38, 92, 13, 60, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_DOWN2"), EVT_NULLPTR, 0, -250, 0, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_D_3"))
    WAIT_MS(700)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_H_1"))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), 25)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_H_1"))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(5), 100)
        SET_VALUE(LW(4), 120)
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, LW(5), 0)
        LOOP(40)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(4))
            SUBTRACT(LW(4), 3)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 20)
    SUBTRACT(LW(2), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_GNB_DOWN3"), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_H_2"))
    CALL(evt_btl_camera_shake_h, 1, 8, 0, 30, 13)
    WAIT_MS(166)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_H_3"))
    CALL(btlevtcmd_GetExp, LW(10), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    WAIT_MS(1000)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_prilimit, 0)
    RETURN
EVT_END()

/**
 * Phase event of Gloomtail: after the player phase it speaks lines (stg8_las_49_03 to 49_07) as its HP drops
 * through the stages tracked in unit work 0, and below a low HP threshold marks that (unit work 1)
 * so it speaks stg8_las_49_07 once.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
        MULTIPLY(LW(0), 60)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 2)
            CALL(evt_msg_print, 2, STRING("stg8_las_49_03"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
        END_IF
        CASE_EQUAL(3)
        CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
        MULTIPLY(LW(0), 40)
        DIVIDE(LW(0), 100)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(1))
        IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 4)
            CALL(evt_msg_print, 2, STRING("stg8_las_49_04"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
        END_IF
        CASE_EQUAL(5)
        CALL(evt_msg_print, 2, STRING("stg8_las_49_05"), 0, BTL_UNIT_SELF)
        CASE_GREATER_OR_EQUAL(6)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
            MULTIPLY(LW(0), 20)
            DIVIDE(LW(0), 100)
            CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(1))
            IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
                CALL(evt_msg_print, 2, STRING("stg8_las_49_07"), 0, BTL_UNIT_SELF)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
            END_IF
        END_IF
    END_SWITCH
    LABEL(99)
    RETURN
EVT_END()

/**
 * Stomp attack of Gloomtail (fumituke): it raises a foot
 * and stamps on one target (weapon_bunbaba_fumituke_attack, with the camera shaking),
 * which dodges or takes the damage with the action command defence check.
 */
static EVT_BEGIN(fumituke_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_W_2"))
    WAIT_MS(950)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MOVE1"), EVT_NULLPTR, 0, -300, 0, -30, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -300)
        ADD(LW(2), -30)
        CALL(_leg_smoke_effect, LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(766)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MOVE1"), EVT_NULLPTR, 0, -300, 0, 30, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -300)
        ADD(LW(2), 30)
        CALL(_leg_smoke_effect, LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(16)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A_3"))
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_ARM_UP1"), EVT_NULLPTR, 0, -320, 30, 30, EVT_NULLPTR)
        WAIT_MS(700)
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_ARM_DOWN1"), EVT_NULLPTR, 0, -360, 50, 30, EVT_NULLPTR)
    END_INLINE_EVENT
    WAIT_MS(750)
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
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(97)
    LABEL(97)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MOVE1"), EVT_NULLPTR, 0, -400, 0, -5, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -400)
        ADD(LW(2), -5)
        CALL(_leg_smoke_effect, LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    WAIT_MS(50)
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(116)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    WAIT_MS(583)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_W_3"))
    WAIT_MS(850)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MOVE1"), EVT_NULLPTR, 0, -180, 0, 30, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -180)
        ADD(LW(2), 30)
        CALL(_leg_smoke_effect, LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(766)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MOVE1"), EVT_NULLPTR, 0, -100, 0, 30, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(0), -100)
        ADD(LW(2), -30)
        CALL(_leg_smoke_effect, LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(116)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Bite attack of Gloomtail (kamituki): it bites one target (GNB_A_2),
 * which dodges or takes the damage with the action command defence check.
 */
static EVT_BEGIN(kamituki_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_BITE1"), EVT_NULLPTR, 0, -220, 80, 0, EVT_NULLPTR)
        WAIT_MS(250)
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_BITE2"), EVT_NULLPTR, 0, -260, 40, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A_2"))
    WAIT_MS(333)
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
        GOTO(99)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    LABEL(97)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    LABEL(99)
    WAIT_MS(333)
    RETURN
EVT_END()

/**
 * Event script: Gloomtail's earthquake attack (weapon_bunbaba_eq_attack):
 * a stomp that shakes the stage and hits the sampled target;
 * the damage is checked once the animation reaches the impact.
 */
EVT_BEGIN(eq_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A_5"))
    WAIT_MS(666)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_GNB_NECK_UP1"), 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A_6"))
    WAIT_MS(233)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_GNB_DOWN3"), 0)
    WAIT_MS(50)
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_MS(250)
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
        GOTO(99)
        CASE_END
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(97)
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    WAIT_MS(583)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: Gloomtail's poison breath (weapon_bunbaba_poison_attack):
 * raises his neck (GNB_A2_1..3) and breathes poison at the chosen target.
 */
EVT_BEGIN(poison_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A2_1"))
    WAIT_MS(833)
    CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_NECK_UP1"), EVT_NULLPTR, 0, -250, 0, 0, EVT_NULLPTR)
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A2_3"))
    CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_BREATH_POISON1"), EVT_NULLPTR, 0, -300, 0, 0, EVT_NULLPTR)
    SET_VALUE(LW(10), 120)
    SET_VALUE(LW(11), 30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(6), 360)
    ADD(LW(7), 30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(12), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(12), 360)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(12), LW(10))
    BEGIN_INLINE_EVENT
        WAIT_MS(333)
        ADD(LW(11), 45)
        SUBTRACT(LW(8), 10)
        CALL(evt_eff, 0, STRING("gonbaba_breath"), 1, LW(6), LW(7), LW(8), FLOAT(3.0f), LW(11), 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(12), EVT_NULLPTR, EVT_NULLPTR)
    SUBTRACT(LW(12), LW(6))
    IF_INT_LESS(LW(12), 0)
        MULTIPLY(LW(12), -1)
    END_IF
    ADD(LW(12), 20)
    MULTIPLY(LW(12), LW(11))
    DIVIDE(LW(12), LW(10))
    ADD(LW(12), 20)
    WAIT_FRAMES(LW(12))
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
    GOTO(97)
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        WAIT_MS(333)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    WAIT_MS(1400)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: Gloomtail's Mega Breath (weapon_bunbaba_mega_attack):
 * charges (SFX_BOSS_GNB_CHARGE1) and breathes fire with the mega breath sound at the chosen targets;
 * the attack he announces with a message.
 */
EVT_BEGIN(mega_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("GNB_A_1"))
    SET_VALUE(LW(10), 120)
    SET_VALUE(LW(11), 30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(6), 360)
    ADD(LW(7), 30)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(12), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(12), 360)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(12), LW(10))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_NECK_UP1"), EVT_NULLPTR, 0, -250, 0, 0, EVT_NULLPTR)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1750)
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_BREATH_FIRE1"), EVT_NULLPTR, 0, -300, 0, 0, EVT_NULLPTR)
#else
        CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_MEGABREATH1"), EVT_NULLPTR, 0, -300, 0, 0, EVT_NULLPTR)
#endif
        ADD(LW(11), 45)
        SUBTRACT(LW(8), 10)
        CALL(evt_eff, 0, STRING("gonbaba_breath"), 2, LW(6), LW(7), LW(8), FLOAT(3.0f), LW(11), 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(12), EVT_NULLPTR, EVT_NULLPTR)
    SUBTRACT(LW(12), LW(6))
    IF_INT_LESS(LW(12), 0)
        MULTIPLY(LW(12), -1)
    END_IF
    ADD(LW(12), 20)
    MULTIPLY(LW(12), LW(11))
    DIVIDE(LW(12), LW(10))
    ADD(LW(12), 105)
    WAIT_FRAMES(LW(12))
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
    GOTO(97)
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        WAIT_MS(333)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    WAIT_MS(1400)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Charge move of Gloomtail: a charge effect appears at its head
 * and it powers itself up (damage check against itself) for the mega attack that follows.
 */
static EVT_BEGIN(charge_event)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_snd_se_offset, BTL_UNIT_SELF, STRING("SFX_BOSS_GNB_CHARGE1"), EVT_NULLPTR, 0, -250, 0, 0, LW(15))
    CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    ADD(LW(0), 20)
    ADD(LW(1), -25)
    CALL(evt_eff, STRING(""), STRING("charge"), 0, LW(0), LW(1), LW(2), FLOAT(2.0f), 60, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, LW(9), 256, LW(5))
    RETURN
EVT_END()

/**
 * Attack event of Gloomtail: can use an item; its attacks depend on the stage in unit work 0.
 * It opens with the poison breath, then draws lots among the stomp, bite, poison breath and earthquake,
 * and at later stages also the charge and the mega attack (always follows a charge).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        SET_VALUE(LW(9), PTR(&weapon_bunbaba_poison_attack))
        CALL_CHILD(poison_attack_event)
        CASE_EQUAL(1)
        CALL(btlevtcmd_DrawLots, LW(0), 3, 10, 10, 20)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_fumituke_attack))
            CALL_CHILD(fumituke_attack_event)
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_kamituki_attack))
            CALL_CHILD(kamituki_attack_event)
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_poison_attack))
            CALL_CHILD(poison_attack_event)
        END_SWITCH
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 3)
        SET_VALUE(LW(9), PTR(&weapon_bunbaba_eq_attack))
        CALL_CHILD(eq_attack_event)
        CASE_EQUAL(3)
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_DrawLots, LW(0), 4, 10, 10, 20, 10)
#else
        CALL(btlevtcmd_DrawLots, LW(0), 4, 10, 10, 20, 15)
#endif
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_fumituke_attack))
            CALL_CHILD(fumituke_attack_event)
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_kamituki_attack))
            CALL_CHILD(kamituki_attack_event)
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_poison_attack))
            CALL_CHILD(poison_attack_event)
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_eq_attack))
            CALL_CHILD(eq_attack_event)
        END_SWITCH
        CASE_EQUAL(4)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 5)
        SET_VALUE(LW(9), PTR(&weapon_bunbaba_charge))
        CALL_CHILD(charge_event)
        CASE_EQUAL(5)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 7)
        SET_VALUE(LW(9), PTR(&weapon_bunbaba_mega_attack))
        CALL_CHILD(mega_attack_event)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_msg_print, 2, STRING("stg8_las_49_06"), 0, BTL_UNIT_SELF)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
        CASE_EQUAL(6)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 7)
        SET_VALUE(LW(9), PTR(&weapon_bunbaba_mega_attack))
        CALL_CHILD(mega_attack_event)
        CASE_EQUAL(7)
        CALL(btlevtcmd_DrawLots, LW(0), 6, 10, 10, 20, 10, 20, 0)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_fumituke_attack))
            CALL_CHILD(fumituke_attack_event)
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_kamituki_attack))
            CALL_CHILD(kamituki_attack_event)
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_poison_attack))
            CALL_CHILD(poison_attack_event)
            CASE_EQUAL(3)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_eq_attack))
            CALL_CHILD(eq_attack_event)
            CASE_EQUAL(4)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 6)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_charge))
            CALL_CHILD(charge_event)
            CASE_EQUAL(5)
            SET_VALUE(LW(9), PTR(&weapon_bunbaba_mega_attack))
            CALL_CHILD(mega_attack_event)
        END_SWITCH
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

struct EffectEntry* effKemuri9N64Entry(s32 type, s32 count, s32 life, f32 x, f32 y, f32 z, f32 radiusEnd, f32 angle);

/**
 * Script helper: spawns a ring of 18 puffs of smoke (N64 style, radius 60, 90 frames) at (args[0], args[1],
 * args[2]) for Gloomtail's footsteps.
 */
static USER_FUNC(_leg_smoke_effect) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effKemuri9N64Entry(1, 18, 90, x, y, z, 60.0f, 0.0f);
    return EVT_RETURN_DONE;
}

/** Wait event of Gloomtail: plays its idle pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
