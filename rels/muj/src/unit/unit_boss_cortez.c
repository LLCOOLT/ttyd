// Keelhaul Key (muj) battle unit: Cortez (cortez): its parts, defence/status tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_unit.h"
#include "battle/battle_audience.h"
#include "system.h"
#include "driver/effdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_batstage.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_msg.h"
#include "battle/battle_database_common.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "pmario_sound.h"
#include "muj.h"
#include "data_tables.h"
#include "eff/eff_spirit.h"
#include "eff/n64/eff_kumokumo_n64.h"
#include "version.h"

typedef struct CortezWork {
    s16 state;
    s16 count;
    s16 audienceId[100];
    s16 wait[100];
    s16 timer[100];
    s16 seq[100];
    void* eff[100];
    Vec srcPos[100];
    Vec dstPos[100];
} CortezWork;
BattleUnitSetup entry_honeduka;

static USER_FUNC(_cortez_check_drain_audience);
static USER_FUNC(_make_cortez_work_area);
static USER_FUNC(_check_zenei_kouei);
static USER_FUNC(_cortez_recovery_audience);
static USER_FUNC(_cortez_drain_energy);
static USER_FUNC(_cortez_collect_energy);
#if VERSION >= VERSION_JP
USER_FUNC(_cortez_get_sfx_vol);
#endif

BattleUnitKind unit_boss_cortez;
static StatusVulnerability regist;
BattleUnitDefense defence_mode1;
BattleUnitDefenseAttr defence_attr_mode1;
BattleUnitDefense defence_mode2_upper_head;
BattleUnitDefenseAttr defence_attr_mode2_upper_head;
BattleUnitDefense defence_mode2_upper_rib_open;
BattleUnitDefenseAttr defence_attr_mode2_upper_rib_open;
BattleUnitDefense defence_mode2_upper_rib_close;
BattleUnitDefenseAttr defence_attr_mode2_upper_rib_close;
BattleUnitDefense defence_mode2_middle_head;
BattleUnitDefenseAttr defence_attr_mode2_middle_head;
BattleUnitDefense defence_mode2_middle_rib_open;
BattleUnitDefenseAttr defence_attr_mode2_middle_rib_open;
BattleUnitDefense defence_mode2_middle_rib_close;
BattleUnitDefenseAttr defence_attr_mode2_middle_rib_close;
BattleUnitDefense defence_mode2_lower_head;
BattleUnitDefenseAttr defence_attr_mode2_lower_head;
BattleUnitDefense defence_mode2_lower_rib_open;
BattleUnitDefenseAttr defence_attr_mode2_lower_rib_open;
BattleUnitDefense defence_mode2_lower_rib_close;
BattleUnitDefenseAttr defence_attr_mode2_lower_rib_close;
BattleUnitDefense defence_mode3;
BattleUnitDefenseAttr defence_attr_mode3;
BattleUnitDefense defence_honeduka;
BattleUnitDefenseAttr defence_honeduka_attr;
BattleWeapon weapon_cortez_normal_front_attack;
BattleWeapon weapon_cortez_normal_rear_attack;
BattleWeapon weapon_cortez_midaregiri_attack;
BattleWeapon weapon_cortez_mode2_head_attack;
BattleWeapon weapon_cortez_mode2_charge;
BattleWeapon weapon_cortez_mode2_bone_attack;
BattleWeapon weapon_cortez_mode3_kamitsuki_attack;
static PoseSoundTiming pose_sound_timing_table[73];
PoseTableEntry pose_table_mode_1[10];
PoseTableEntry pose_table_mode_1_hone[10];
PoseTableEntry pose_table_mode_2_normal[4];
PoseTableEntry pose_table_mode_2_upper_normal[4];
PoseTableEntry pose_table_mode_2_upper_normal_counter[4];
PoseTableEntry pose_table_mode_2_upper_charge[4];
PoseTableEntry pose_table_mode_2_upper_charge_counter[4];
PoseTableEntry pose_table_mode_2_middle_normal[4];
PoseTableEntry pose_table_mode_2_middle_normal_counter[4];
PoseTableEntry pose_table_mode_2_middle_charge[4];
PoseTableEntry pose_table_mode_2_middle_charge_counter[4];
PoseTableEntry pose_table_mode_2_lower_normal[4];
PoseTableEntry pose_table_mode_2_lower_normal_counter[4];
PoseTableEntry pose_table_mode_2_lower_charge[4];
PoseTableEntry pose_table_mode_2_lower_charge_counter[4];
PoseTableEntry pose_table_fly_bone[4];
PoseTableEntry pose_table_mode_3[12];
PoseTableEntry pose_table_honeduka[4];
static BattleDataEntry data_table[7];
static BattleUnitKindPart parts[19];
static EvtWord init_event[260];
static EvtWord damage_event[70];
extern EvtWord cortez_ac_counter_damage_event[];
static EvtWord avoid_thorn_event[89];
#if VERSION <= VERSION_DEMO_US
static EvtWord phase_event[184];
#else
static EvtWord phase_event[196];
#endif
extern EvtWord attack_event_mode1[];
extern EvtWord attack_event_mode2[];
extern EvtWord at2_head_bat_event[];
extern EvtWord at2_hone_charge_event[];
extern EvtWord at2_hone_rain_attack_event[];
extern EvtWord _bone_rain_event[];
extern EvtWord attack_event_mode3[];
#if VERSION <= VERSION_DEMO_US
static EvtWord attack_audience_event[198];
#else
static EvtWord attack_audience_event[247];
#endif
extern EvtWord at3_kamitsuki_attack[];
extern EvtWord at1_normal_attack[];
extern EvtWord at1_midaregiri_attack[];
static EvtWord wait_event[6];
BattleUnitSetup entry_claw;
BattleUnitSetup entry_rapier;
BattleUnitSetup entry_sword;
BattleUnitSetup entry_saber;
extern EvtWord cortez_reset_pose_table[];
static EvtWord cortez_damage_sub_event[153];
#if VERSION <= VERSION_DEMO_US
static EvtWord dead_event[1007];
#else
static EvtWord dead_event[1033];
#endif
extern EvtWord mode2_rib_open_event[];
extern EvtWord mode2_rib_close_event[];
extern EvtWord mode2_honeduka_damage_event[];
extern EvtWord mode_change_event[];

BattleUnitKind unit_boss_cortez = {
    93,
    "btl_un_cortez",
    20,
    0,
    1,
    1,
    77,
    0,
    0,
    100,
    0,
    50,
    6,
    250,
    170,
    -10,
    90,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    125.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    32.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    -70.0f,
    65.0f,
    0.0f,
    180.0f,
    130.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KOR_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    19,
    parts,
    init_event,
    data_table,
};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {50, 40, 50, 100, 50, 100, 100, 40, 0, 0, 100, 0, 100, 40, 50, 0, 0, 100, 50, 0, 0, 0};
#else
static StatusVulnerability regist = {40, 40, 50, 100, 50, 100, 100, 25, 0, 0, 100, 0, 100, 90, 50, 0, 0, 100, 50, 0, 0, 0};
#endif

BattleUnitDefense defence_mode1 = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_attr_mode1 = {{0, 0, 0, 0, 0}};

BattleUnitDefense defence_mode2_upper_head = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_attr_mode2_upper_head = {0};

BattleUnitDefense defence_mode2_upper_rib_open = {0};

BattleUnitDefenseAttr defence_attr_mode2_upper_rib_open = {{1, 1, 1, 1, 1}};

BattleUnitDefense defence_mode2_upper_rib_close = {{3, 3, 3, 3, 3}};

BattleUnitDefenseAttr defence_attr_mode2_upper_rib_close = {{0, 0, 0, 0, 0}};

BattleUnitDefense defence_mode2_middle_head = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_attr_mode2_middle_head = {0};

BattleUnitDefense defence_mode2_middle_rib_open = {0};

BattleUnitDefenseAttr defence_attr_mode2_middle_rib_open = {{1, 1, 1, 1, 1}};

BattleUnitDefense defence_mode2_middle_rib_close = {{3, 3, 3, 3, 3}};

BattleUnitDefenseAttr defence_attr_mode2_middle_rib_close = {0};

BattleUnitDefense defence_mode2_lower_head = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_attr_mode2_lower_head = {0};

BattleUnitDefense defence_mode2_lower_rib_open = {0};

BattleUnitDefenseAttr defence_attr_mode2_lower_rib_open = {{1, 1, 1, 1, 1}};

BattleUnitDefense defence_mode2_lower_rib_close = {{3, 3, 3, 3, 3}};

BattleUnitDefenseAttr defence_attr_mode2_lower_rib_close = {0};

BattleUnitDefense defence_mode3 = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_attr_mode3 = {0};

BattleUnitDefense defence_honeduka = {{1, 1, 1, 1, 1}};

BattleUnitDefenseAttr defence_honeduka_attr = {{0, 0, 0, 0, 0}};

BattleWeapon weapon_cortez_normal_front_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
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

BattleWeapon weapon_cortez_normal_rear_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_BACK, // targetWeightFlags
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

BattleWeapon weapon_cortez_midaregiri_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
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

BattleWeapon weapon_cortez_mode2_head_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
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

BattleWeapon weapon_cortez_mode2_charge = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
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
    4, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon weapon_cortez_mode2_bone_attack = {
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
    0, 0, // element..damagePattern
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

BattleWeapon weapon_cortez_mode3_kamitsuki_attack = {
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

static PoseSoundTiming pose_sound_timing_table[] = {
    {"KRT_1S_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_1S2_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_2S2_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#if VERSION <= VERSION_DEMO_US
    {"KRT_3S2_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#else
    {"KRT_3S3_1", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_1", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_1", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_1", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_1", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_1", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#endif
    {"KRT_3S_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#if VERSION <= VERSION_DEMO_US
    {"KRT_3S2_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S2_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#else
    {"KRT_3S3_2", 0.01f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_2", 0.2f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_2", 0.4f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_2", 0.6f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_2", 0.8f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
    {"KRT_3S3_2", 1.0f, NULL, "SFX_BOSS_KOR_WAIT1", 0, 1},
#endif
    {NULL, 0.0f, NULL, NULL, 0, 1},
};

PoseTableEntry pose_table_mode_1[] = {
    {1, "KRT_N_1"},
    {5, "KRT_K_1"},
    // the demo names these poses after the Goomba animations (KUR_*)
#if VERSION <= VERSION_DEMO_US
    {2, "KUR_Z_1"},
    {9, "KUR_Z_1"},
    {4, "KUR_X_1"},
    {3, "KUR_K_1"},
#else
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
#endif
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_D1_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

PoseTableEntry pose_table_mode_1_hone[] = {
    {1, "KRT_N_1"},
    {5, "KRT_K_1"},
#if VERSION <= VERSION_DEMO_US
    {2, "KUR_Z_1"},
    {9, "KUR_Z_1"},
    {4, "KUR_X_1"},
    {3, "KUR_K_1"},
#else
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
#endif
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_D1_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

PoseTableEntry pose_table_mode_2_normal[] = {
    {28, "KRT_1S_1"},
    {31, "KRT_1S_1"},
    {39, "KRT_1D_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_1S_1"},
};

PoseTableEntry pose_table_mode_2_upper_normal[] = {
    {28, "KRT_1S_1"},
    {31, "KRT_1S_1"},
    {39, "KRT_1D_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_1S_1"},
};

PoseTableEntry pose_table_mode_2_upper_normal_counter[] = {
    {28, "KRT_1S2_1"},
    {31, "KRT_1S2_1"},
    {39, "KRT_1D2_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_1S2_1"},
};

PoseTableEntry pose_table_mode_2_upper_charge[] = {
    {28, "KRT_1S_2"},
    {31, "KRT_1S_2"},
    {39, "KRT_1D_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_1S_2"},
};

PoseTableEntry pose_table_mode_2_upper_charge_counter[] = {
    {28, "KRT_1S2_2"},
    {31, "KRT_1S2_2"},
    {39, "KRT_1D2_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_1S2_2"},
};

PoseTableEntry pose_table_mode_2_middle_normal[] = {
    {28, "KRT_2S_1"},
    {31, "KRT_2S_1"},
    {39, "KRT_2D_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_2S_1"},
};

PoseTableEntry pose_table_mode_2_middle_normal_counter[] = {
    {28, "KRT_2S2_1"},
    {31, "KRT_2S2_1"},
    {39, "KRT_2D2_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_2S2_1"},
};

PoseTableEntry pose_table_mode_2_middle_charge[] = {
    {28, "KRT_2S_2"},
    {31, "KRT_2S_2"},
    {39, "KRT_2D_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_2S_2"},
};

PoseTableEntry pose_table_mode_2_middle_charge_counter[] = {
    {28, "KRT_2S2_2"},
    {31, "KRT_2S2_2"},
    {39, "KRT_2D2_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_2S2_2"},
};

PoseTableEntry pose_table_mode_2_lower_normal[] = {
    {28, "KRT_3S_1"},
    {31, "KRT_3S_1"},
    {39, "KRT_3D_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_3S_1"},
};

PoseTableEntry pose_table_mode_2_lower_normal_counter[] = {
    {28, "KRT_3S3_1"},
    {31, "KRT_3S3_1"},
    {39, "KRT_3D3_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_3S3_1"},
};

PoseTableEntry pose_table_mode_2_lower_charge[] = {
    {28, "KRT_3S_2"},
    {31, "KRT_3S_2"},
    {39, "KRT_3D_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_3S_2"},
};

PoseTableEntry pose_table_mode_2_lower_charge_counter[] = {
    {28, "KRT_3S3_2"},
    {31, "KRT_3S3_2"},
    {39, "KRT_3D3_2"},
    {BTL_POSE_STAY_DEFAULT, "KRT_3S3_2"},
};

PoseTableEntry pose_table_fly_bone[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

PoseTableEntry pose_table_mode_3[] = {
#if VERSION <= VERSION_DEMO_US
    {1, "KUR_N_1"},
    {2, "KUR_Z_1"},
    {9, "KUR_Z_1"},
    {5, "KUR_K_1"},
    {4, "KUR_X_1"},
    {3, "KUR_K_1"},
#else
    {1, "KRT_N_1"},
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {5, "KRT_K_1"},
    {4, "KRT_X_1"},
    {3, "KRT_K_1"},
#endif
    {28, "KRT_S_1"},
    {29, "KRT_D_2"},
    {30, "KRT_D_2"},
    {31, "KRT_S_1"},
    {39, "KRT_D_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

PoseTableEntry pose_table_honeduka[] = {
    {28, "KRT_Z_1"},
    {31, "KRT_Z_1"},
    {39, "KRT_Z_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_Z_1"},
};

static BattleDataEntry data_table[] = {
    {9, cortez_damage_sub_event},
    {49, dead_event},
#if VERSION <= VERSION_DEMO_US
    {70, mode2_honeduka_damage_event},
#else
    {71, mode2_honeduka_damage_event},
#endif
    {36, cortez_ac_counter_damage_event},
    {39, avoid_thorn_event},
    {37, avoid_thorn_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_cortez", "c_korutesu1", 0.0f, 0.0f, 0.0f, 145.0f, 90.0f, 30.0f, 145.0f, 90.0f, 30.0f, 20, 30, 255, &defence_honeduka, &defence_honeduka_attr, 0x600009, 0, pose_table_mode_1},
    {2, "btl_un_cortez", NULL, 0.0f, 0.0f, 0.0f, 60.0f, 110.0f, 20.0f, 60.0f, 110.0f, 20.0f, 20, 30, 255, &defence_mode2_upper_rib_close, &defence_attr_mode2_upper_rib_close, 0x3310004, 0, pose_table_mode_1},
    {3, "btl_un_cortez", "c_otitabuki", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x3010000, 0, pose_table_mode_1},
    {4, "btl_un_honeduka", "c_honezuka", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 10.0f, 0.0f, 30.0f, 10.0f, 45, 30, 255, &defence_mode1, &defence_attr_mode1, 0x2000006, 0x1, pose_table_honeduka},
    {5, "btl_un_honeduka", "c_hone2", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x3010000, 0, pose_table_fly_bone},
    {6, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {7, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {8, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {9, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {10, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {11, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {12, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {13, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {14, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {15, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {16, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {17, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {18, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
    {19, "btl_un_honeduka", "c_hone", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence_mode1, &defence_attr_mode1, 0x13010000, 0, pose_table_fly_bone},
};

/**
 * Guess: init event of Cortez: sets up his work values (mode 1, rib state, bone rain flag) and his pose
 * and defence tables, and allocates the audience work area.
 */
static EVT_BEGIN(init_event)
    CALL(_make_cortez_work_area, BTL_UNIT_SELF)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 16777216)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_mode1))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 6, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 9, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 10, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, 0)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_claw), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, LW(3))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 39)
    ADD(LW(1), 41)
    SUBTRACT(LW(2), 45)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_rapier), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, LW(3))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 2)
    ADD(LW(1), 6)
    ADD(LW(2), 60)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_sword), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(3))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 154)
    ADD(LW(1), 11)
    SUBTRACT(LW(2), 65)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_saber), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(3))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 116)
    ADD(LW(1), 28)
    ADD(LW(2), 73)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 160, 85, 50)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Guess: damage event of Cortez: chooses the reaction by which part was hit (head, ribs or the bone part):
 * the head and body use the default damage reaction,
 * a rib hit sets the hit flags and the bone part runs mode2_honeduka_damage_event.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 4)
            CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_1))
            CALL_CHILD(btldefaultevt_Damage)
        ELSE
            CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_1_hone))
            CALL_CHILD(btldefaultevt_Damage)
        END_IF
        RETURN
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL_CHILD(btldefaultevt_Damage)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, 2)
        CALL_CHILD(btldefaultevt_Damage)
        CASE_EQUAL(4)
        CALL_CHILD(mode2_honeduka_damage_event)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Cortez's damage event for the counterattack (action command) phase:
 * when he is hit while swinging, he recovers into his idle pose and dives back to his home position,
 * with a different path depending on the damage code, then continues in the normal damage flow.
 */
EVT_BEGIN(cortez_ac_counter_damage_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    IF_INT_LESS(LW(0), 4)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 39)
        WAIT_MS(500)
        RETURN
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A3_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, 0, 2, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            RETURN
        END_IF
    END_IF
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 15, 11, 0, -1)
    RETURN
EVT_END()

/**
 * Guess: event run when Cortez touches a spiked attacker (Mario's spiked or fiery counter):
 * plays his hurt reaction, then returns to his pose for the current mode.
 */
static EVT_BEGIN(avoid_thorn_event)
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 4)
        CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("toge_flush"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    ELSE
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_RIB_COUNTER1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1C_3"))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2C_3"))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3C_3"))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        END_SWITCH
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, 0)
        CALL_CHILD(cortez_reset_pose_table)
    END_IF
    RETURN
EVT_END()

/**
 * Guess: phase event of Cortez: at the start of each turn it handles the change of mode,
 * summons or drains audience energy and runs his per-turn bookkeeping.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_ENEMY)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_sub_random, 3, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 8, LW(0))
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_END
        CASE_DEFAULT
        GOTO(50)
    END_SWITCH
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 7, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 0)
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(50)
    END_IF
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(mode2_rib_close_event)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
#if VERSION <= VERSION_DEMO_US
    SET_VALUE(LW(15), -1)
    SWITCH(LW(0))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2B_1"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
        CASE_EQUAL(3)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3B_1"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
    END_SWITCH
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    IF_INT_NOT_EQUAL(LW(15), -1)
        CALL(evt_snd_sfxoff, LW(15))
    END_IF
#else
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(15), -1)
        SWITCH(LW(0))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2B_1"))
            CALL(btlevtcmd_ftomsec, 80, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3B_1"))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
        END_SWITCH
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        IF_INT_NOT_EQUAL(LW(15), -1)
            CALL(evt_snd_sfxoff, LW(15))
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
#endif
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 1)
    CALL_CHILD(cortez_reset_pose_table)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
    LABEL(50)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_StopWaitEvent, BTL_UNIT_SELF)
    CALL_CHILD(mode2_rib_close_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
    LABEL(99)
    RETURN
EVT_END()

/**
 * Cortez's attack chooser for mode 1 (first phase):
 * picks between the normal sword stab (at1_normal_attack)
 * and the flurry slash (at1_midaregiri_attack) from a counter in unit work 6 so the order cycles.
 */
EVT_BEGIN(attack_event_mode1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 6, LW(0))
    IF_INT_LESS(LW(0), 3)
        SET_VALUE(LW(1), LW(0))
        ADD(LW(1), 1)
        IF_INT_GREATER_OR_EQUAL(LW(1), 3)
            SET_VALUE(LW(1), 0)
        END_IF
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 6, LW(1))
    END_IF
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL_CHILD(at1_normal_attack)
        CASE_END
        CASE_EQUAL(2)
        CALL_CHILD(at1_midaregiri_attack)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

/**
 * Cortez's attack chooser for mode 2 (second phase, ribs and head):
 * if the bone rain is pending, throws it (at2_hone_rain_attack_event);
 * otherwise chooses between the bone charge (at2_hone_charge_event)
 * and the head-bat attack (at2_head_bat_event) by weighted lots.
 */
EVT_BEGIN(attack_event_mode2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(at2_hone_rain_attack_event)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CALL_CHILD(at2_hone_charge_event)
        RETURN
        CASE_END
    END_SWITCH
    CALL(btlevtcmd_DrawLots, LW(0), 2, 25, 75)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(at2_hone_charge_event)
        CASE_EQUAL(1)
        CALL_CHILD(at2_head_bat_event)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Cortez's head-bat attack (mode 2): swings his skull at one target,
 * with pose KRT_1A variants depending on whether the ribs are open;
 * the attack hits for the weapon's damage and the head-attack sound plays twice.
 */
EVT_BEGIN(at2_head_bat_event)
    SET_VALUE(LW(12), PTR(&weapon_cortez_mode2_head_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(_check_zenei_kouei, LW(3), LW(13))
    IF_INT_EQUAL(LW(13), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1A_1"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1A_3"))
        END_IF
    ELSE
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1A_2"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1A_4"))
        END_IF
    END_IF
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_HEAD_ATTACK1"), EVT_NULLPTR, 0, LW(15))
        WAIT_MS(667)
        CALL(evt_snd_sfxoff, LW(15))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_ftomsec, 50, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_HEAD_ATTACK2"), EVT_NULLPTR, 0, LW(15))
        CALL(btlevtcmd_ftomsec, 18, LW(0))
        WAIT_MS(LW(0))
        CALL(evt_snd_sfxoff, LW(15))
    END_INLINE_EVENT
    WAIT_MS(1116)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_DEFAULT
        GOTO(91)
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Cortez's bone charge (mode 2): sets the bone-rain pending flag,
 * moves the camera back and plays the charge-up pose KRT_2A for his current mode, preparing the bone rain.
 */
EVT_BEGIN(at2_hone_charge_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 10, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(1))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260, 60, 4)
        IF_INT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A_1"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A1_1"))
        END_IF
        CASE_EQUAL(2)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260, 60, 4)
        IF_INT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A_2"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A2_2"))
        END_IF
        CASE_EQUAL(3)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 50, 140, 520, 50, 90, -260, 60, 4)
        IF_INT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A_3"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2A3_3"))
        END_IF
    END_SWITCH
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_INHALE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(2000)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL_CHILD(cortez_reset_pose_table)
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, PTR(&weapon_cortez_mode2_charge), 256, LW(5))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Cortez's bone rain (mode 2): declares an attack on all enemies,
 * throws his bones into the air and has them fall on the player's side in a shower (spawned through
 * _bone_rain_event), then clears the pending flag.
 */
EVT_BEGIN(at2_hone_rain_attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 10, 0)
    SET_VALUE(LW(12), PTR(&weapon_cortez_mode2_bone_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3A_1"))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3A_2"))
        CASE_EQUAL(3)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3A_3"))
    END_SWITCH
    WAIT_MS(1700)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FLY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, 16777216)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRT_A_1"))
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 5)
        WAIT_MS(500)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, 16777216)
    END_INLINE_EVENT
    SET_VALUE(LW(5), 12)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 13)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 14)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 15)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 16)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 17)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 18)
    SPAWN_EVENT(_bone_rain_event)
    SET_VALUE(LW(5), 19)
    SPAWN_EVENT(_bone_rain_event)
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, 16777216)
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 6, FLOAT(0.89941406f))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2), 30, -1)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 6, 0, 0, 0)
        LOOP(30)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 6, 0, 0, 30)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 9, 16777216)
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 9, FLOAT(0.89941406f))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2), 30, -1)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, 9, 0, 0, 0)
            LOOP(30)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 9, 0, 0, 30)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_DEFAULT
        GOTO(90)
    END_SWITCH
    LABEL(90)
    IF_INT_EQUAL(LW(10), 0)
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 6)
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 6, FLOAT(0.69921875f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2), 24, -1)
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, 16777216)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            LOOP(24)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 6, 0, 0, 30)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    ELSE
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_JumpPartsContinue, BTL_UNIT_SELF, 9)
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 9, FLOAT(0.69921875f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2), 24, -1)
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 9, 16777216)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            LOOP(24)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 9, 0, 0, 30)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    GOTO(97)
    LABEL(91)
    IF_INT_EQUAL(LW(10), 0)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    IF_INT_EQUAL(LW(10), 0)
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 80)
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 6, FLOAT(0.5996094f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2), 26, -1)
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, 16777216)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            LOOP(26)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 6, 0, 0, 30)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    ELSE
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 80)
            CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, 9, FLOAT(0.5996094f))
            CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 9, LW(0), LW(1), LW(2), 26, -1)
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 9, 16777216)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            LOOP(26)
                CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 9, 0, 0, 30)
                WAIT_FRAMES(1)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    LABEL(97)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        WAIT_MS(60)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    WAIT_FRAMES(84)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * One falling bone of the bone rain: starts after a random delay, picks a random start above Cortez,
 * flies to a random spot around the target and spins as it falls, then lands and damages.
 */
EVT_BEGIN(_bone_rain_event)
    CALL(evt_sub_random, 20, LW(10))
    ADD(LW(10), 20)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_sub_random, 90, LW(7))
        SUBTRACT(LW(7), 45)
        ADD(LW(0), LW(7))
        CALL(evt_sub_random, 60, LW(7))
        SUBTRACT(LW(7), 30)
        ADD(LW(2), LW(7))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(5), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(5), 16777216)
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, LW(5), FLOAT(1.3994141f))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(evt_sub_random, 120, LW(7))
        SUBTRACT(LW(7), 60)
        ADD(LW(0), LW(7))
        CALL(evt_sub_random, 60, LW(7))
        SUBTRACT(LW(7), 30)
        ADD(LW(2), LW(7))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(5), LW(0), LW(1), LW(2), LW(10), -1)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(5), 16777216)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(LW(10))
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(5), 0, 0, 30)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Cortez's attack chooser for mode 3 (final phase):
 * he may first drain the audience (attack_audience_event) when his HP is low,
 * and otherwise bites the target (at3_kamitsuki_attack).
 */
EVT_BEGIN(attack_event_mode3)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 9, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(1))
        DIVIDE(LW(1), 2)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), LW(1))
            CALL(_cortez_check_drain_audience, BTL_UNIT_SELF, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 1)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 9, LW(0))
                ADD(LW(0), 1)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 9, LW(0))
                CALL_CHILD(attack_audience_event)
                RETURN
            END_IF
        END_IF
    END_IF
    CALL_CHILD(at3_kamitsuki_attack)
    RETURN
EVT_END()

/**
 * Guess: cortez drains the audience (mode 3): collects the spirits of the audience members
 * (_cortez_collect_energy), heals himself from them, and removes the audience members,
 * while the camera follows him.
 */
static EVT_BEGIN(attack_audience_event)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 140, 120, 500, 140, 85, 9, 60, 11)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KRT_T_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("KRT_S_1"))
    CALL(evt_msg_print, 2, STRING("stg5_dou_24_bt01"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 80, 115, 820, 80, 60, 6, 60, 11)
#if VERSION >= VERSION_JP
    CALL(evt_batstage_set_aud_dark, 0, 60, 0)
#endif
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), 120, 60, -10, 4, 0, -1)
    CALL(evt_msg_print, 2, STRING("stg5_dou_24_bt02"), 0, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_INHALE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_snd_sfxon, STRING("SFX_AUDIENCE_PANIC_SCREAM1"), LW(15))
#else
    BEGIN_SIBLING_EVENT
        CALL(evt_snd_sfxon, STRING("SFX_AUDIENCE_PANIC_SCREAM1"), LW(15))
        WAIT_FRAMES(120)
        CALL(_cortez_get_sfx_vol, LW(15), LW(14))
        SET_VALUE(LW(13), 120)
        LOOP(120)
            WAIT_FRAMES(1)
            IF_INT_GREATER(LW(13), 0)
                SUBTRACT(LW(13), 1)
            END_IF
            SET_VALUE(LW(0), LW(14))
            MULTIPLY(LW(0), LW(13))
            DIVIDE(LW(0), 120)
            CALL(evt_snd_sfx_vol, LW(15), LW(0))
            DEBUG_PUT_REG(LW(14))
            DEBUG_PUT_REG(LW(0))
        END_LOOP
        CALL(evt_snd_sfxoff, LW(15))
    END_SIBLING_EVENT
#endif
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_2"))
    CALL(_cortez_collect_energy, BTL_UNIT_SELF)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_snd_sfxoff, LW(15))
#endif
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_3"))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    END_SIBLING_EVENT
    WAIT_MS(125)
    CALL(_cortez_drain_energy, BTL_UNIT_SELF, LW(5))
    CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, LW(5))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("recovery"), 0, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_btl_camera_set_mode, 0, 0)
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
        CALL(_cortez_recovery_audience, BTL_UNIT_SELF)
    END_INLINE_EVENT
#if VERSION >= VERSION_JP
    CALL(evt_batstage_return_aud_dark_base, 60, 0)
#endif
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -10, 4, 0, -1)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Cortez's biting attack (mode 3, kamitsuki): lunges at a target with a spinning dive and bite sounds,
 * and chomps for the weapon's damage.
 */
EVT_BEGIN(at3_kamitsuki_attack)
    SET_VALUE(LW(12), PTR(&weapon_cortez_mode3_kamitsuki_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_W_1"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 40)
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), -12, 5, 0, -1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_ROUND1"), EVT_NULLPTR, 0, LW(15))
        CALL(btlevtcmd_ftomsec, 32, LW(0))
        WAIT_MS(LW(0))
        CALL(evt_snd_sfxoff, LW(15))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 46, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A3_3"))
    CALL(btlevtcmd_ftomsec, 50, LW(0))
    WAIT_MS(LW(0))
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_DEFAULT
        GOTO(91)
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    IF_INT_EQUAL(LW(5), 21)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A3_1"))
        GOTO(98)
    END_IF
    LABEL(97)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_Z_1"))
    LABEL(98)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 50)
    ADD(LW(1), 10)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -10, 2, 0, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 15, 11, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Cortez's normal sword stab (mode 1): raises the sword, then thrusts it twice with sword-stick sounds,
 * with a different pose for targets at the front guard than at the back (_check_zenei_kouei).
 */
EVT_BEGIN(at1_normal_attack)
    IF_INT_EQUAL(LW(0), 0)
        SET_VALUE(LW(12), PTR(&weapon_cortez_normal_front_attack))
    ELSE
        SET_VALUE(LW(12), PTR(&weapon_cortez_normal_rear_attack))
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_READY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(_check_zenei_kouei, LW(3), LW(13))
    IF_INT_EQUAL(LW(13), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A1_1"))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 95, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_STICK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 99, LW(0))
        WAIT_MS(LW(0))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A1_2"))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 95, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_STICK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 100, LW(0))
        WAIT_MS(LW(0))
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_DEFAULT
        GOTO(91)
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    LABEL(97)
    WAIT_FRAMES(3)
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    WAIT_FRAMES(7)
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Cortez's flurry slash (mode 1, midaregiri): shakes his sword with three swishes
 * then cuts through the target with a multi-hit slash,
 * with a different pose for the front and back guard targets.
 */
EVT_BEGIN(at1_midaregiri_attack)
    SET_VALUE(LW(12), PTR(&weapon_cortez_midaregiri_attack))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(_check_zenei_kouei, LW(3), LW(13))
    IF_INT_EQUAL(LW(13), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_1"))
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_2"))
    END_IF
    SET_VALUE(LW(0), 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 33, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_SHAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 84, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_SHAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 145, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_SHAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ftomsec, 198, LW(0))
        WAIT_MS(LW(0))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_SHAKE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    LABEL(10)
    SWITCH(LW(10))
        CASE_EQUAL(0)
        CALL(btlevtcmd_ftomsec, 38, LW(0))
        WAIT_MS(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_ftomsec, 60, LW(0))
        WAIT_MS(LW(0))
        CASE_EQUAL(2)
        CALL(btlevtcmd_ftomsec, 54, LW(0))
        WAIT_MS(LW(0))
        CASE_DEFAULT
        CALL(btlevtcmd_ftomsec, 56, LW(0))
        WAIT_MS(LW(0))
    END_SWITCH
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_DEFAULT
        GOTO(91)
    END_SWITCH
    LABEL(90)
    GOTO(97)
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(12))
    IF_INT_GREATER_OR_EQUAL(LW(10), 3)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 0, LW(5))
    END_IF
    LABEL(97)
    ADD(LW(10), 1)
    IF_INT_LESS_OR_EQUAL(LW(10), 3)
        GOTO(10)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Guess: wait (idle) event of Cortez: sets the idle pose from the current mode's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

BattleUnitSetup entry_claw = {
    &unit_boss_cortez_claw, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_rapier = {
    &unit_boss_cortez_rapier, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_sword = {
    &unit_boss_cortez_sword, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_saber = {
    &unit_boss_cortez_saber, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Re-applies Cortez's pose table, defence tables and kiss hit offset for his current mode (unit work 5)
 * and state of the ribs (unit work 10, 11), after a mode change or rib open/close.
 */
EVT_BEGIN(cortez_reset_pose_table)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_1))
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 160, 120, 50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_upper_normal))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_upper_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_upper_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_upper_rib_close))
        ELSE
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_upper_normal_counter))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_upper_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_upper_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_upper_rib_open))
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_mode2_upper_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_mode2_upper_head))
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 7340032)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 20, 15, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 20, 15, 0)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 2, 0, 0, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 2, 0, 0, 0)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 160, 85, 50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_middle_normal))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_middle_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_middle_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_middle_rib_close))
        ELSE
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_middle_normal_counter))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_middle_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_middle_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_middle_rib_open))
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_mode2_middle_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_mode2_middle_head))
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 7340032)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 10, 10, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 10, 10, 0)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 2, -7, -20, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 2, -7, -20, 0)
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 150, 85, 50)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_lower_normal))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_lower_charge))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_lower_rib_close))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_lower_rib_close))
        ELSE
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 10, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_lower_normal_counter))
            ELSE
                CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_2_lower_charge_counter))
            END_IF
            CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 2, PTR(&defence_mode2_lower_rib_open))
            CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 2, PTR(&defence_attr_mode2_lower_rib_open))
            CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 6291456)
        END_IF
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_mode2_lower_head))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_mode2_lower_head))
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 6291456)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 1048576)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, -15, -5, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, -15, -5, 0)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 2, -20, -35, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 2, -20, -35, 0)
        CASE_DEFAULT
        CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 30, 50, 50)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_3))
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_mode3))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&defence_attr_mode3))
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 6291456)
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, 4)
        CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, -135, -64, 0)
        CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, -135, -65, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Guess: sub-event of Cortez's damage handling:
 * applies the knock-back and hurt animation for the part hit, then continues in the default damage flow.
 */
static EVT_BEGIN(cortez_damage_sub_event)
    CALL_CHILD(cortez_reset_pose_table)
    CALL(btlevtcmd_GetDamage, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_GetHitPos, BTL_UNIT_SELF, LW(0), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_ATTACK_MISS2"), LW(0), LW(1), LW(2), 0)
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 39)
        ELSE
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1D_3"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2D_3"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3D_3"))
                ELSE
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3D3_1"))
            END_IF
        END_SWITCH
    END_IF
    WAIT_FRAMES(30)
    GOTO(60)
    LABEL(50)
    LABEL(60)
    CALL(btlevtcmd_GetDamagePartsId, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 256, LW(1))
        IF_INT_NOT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 1024, LW(1))
            IF_INT_EQUAL(LW(1), 0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
                SWITCH(LW(0))
                    CASE_OR_EQUAL(1)
                    CASE_OR_EQUAL(2)
                    CASE_OR_EQUAL(3)
                    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
                    IF_INT_EQUAL(LW(0), 0)
                        CALL_CHILD(mode2_rib_open_event)
                    END_IF
                    CASE_END
                END_SWITCH
            END_IF
        END_IF
    END_IF
END_IF // stray: no IF is open here; the original script has it too, and END_IF does nothing when run
LABEL(99)
RETURN
EVT_END()

/**
 * Guess: death event of Cortez: collapses his skeleton, removes his swords,
 * awards coins and experience and ends the battle.
 */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_ClearAllStatus, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 1)
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_mode2))
        CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, 999)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, 65536)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_D2_1"))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 125, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 120, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 118, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 117, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_SWORD_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            WAIT_MS(2000)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_Z_1"))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_D2_2"))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_ftomsec, 33, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(7))
            CALL(btlevtcmd_ftomsec, 36, LW(0))
            WAIT_MS(LW(0))
            CALL(evt_snd_sfxoff, LW(7))
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
        CALL(evt_fade_entry, FADE_CURTAIN_SIDES_A1_3D, 1000, 0, 0, 0)
        CALL(evt_fade_set_anim_ofs_pos, 0, 130)
        CALL(evt_fade_set_anim_virtual_pos, 0, 0, 80)
        CALL(evt_fade_end_wait)
        CALL(btlevtcmd_AnimeChangeGroup, BTL_UNIT_SELF, 1, STRING("c_korutesu2"))
        CALL_CHILD(cortez_reset_pose_table)
        CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(pose_sound_timing_table))
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        CALL(evt_fade_entry, FADE_CURTAIN_SIDES_A2_3D, 1000, 0, 0, 0)
        CALL(evt_fade_set_anim_ofs_pos, 0, 130)
        CALL(evt_fade_set_anim_virtual_pos, 0, 0, 80)
        CALL(evt_fade_end_wait)
        CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, -80, 120, 0)
        CALL(btlevtcmd_SetCutWidth, BTL_UNIT_SELF, 200)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 100)
        CALL(btlevtcmd_reset_turn)
        CASE_OR_EQUAL(1)
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_mode3))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1B_1"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2B_1"))
#if VERSION >= VERSION_JP
            CALL(btlevtcmd_ftomsec, 80, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
#endif
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
#if VERSION >= VERSION_JP
            CALL(evt_snd_sfxoff, LW(15))
#endif
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1B_1"))
            CASE_EQUAL(3)
#if VERSION >= VERSION_JP
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
#endif
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3B_1"))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
#if VERSION >= VERSION_JP
            CALL(evt_snd_sfxoff, LW(15))
#endif
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1B_1"))
        END_SWITCH
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 7, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 8, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 4, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 6, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 7, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 8, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 8, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 5, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 7, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 5, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 7, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 14, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_ftomsec, 30, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 4)
        WAIT_MS(1000)
        CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, 16777216)
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 3)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(3))
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 50397184)
        CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
        CALL(btlevtcmd_SetMaxMoveCount, LW(3), 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(3))
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 50397184)
        CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
        CALL(btlevtcmd_SetMaxMoveCount, LW(3), 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(3))
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 50397184)
        CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
        CALL(btlevtcmd_SetMaxMoveCount, LW(3), 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(3))
        CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 50397184)
        CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
        CALL(btlevtcmd_SetMaxMoveCount, LW(3), 1)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, 50331648)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, 50397184)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 65536)
        SET_VALUE(LW(11), 1)
        LOOP(4)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, LW(11), LW(9))
            BEGIN_INLINE_EVENT
                CALL_CHILD(cortez_weapon_get_home_height)
                CALL(btlevtcmd_GetUnitWork, LW(9), 2, LW(6))
                IF_INT_EQUAL(LW(6), 2)
                    CALL(btlevtcmd_FaceDirectionAdd, LW(9), LW(0), 15)
                END_IF
                CALL(btlevtcmd_PhaseEventStartDeclare, LW(9))
                CALL(btlevtcmd_DivePosition, LW(9), LW(0), LW(5), LW(2), 60, 0, 5, 0, -1)
                CALL(btlevtcmd_SetHomePos, LW(9), LW(0), LW(5), LW(2))
                CALL_CHILD(cortez_weapon_set_formation_attribute)
                CALL(btlevtcmd_StartWaitEvent, LW(9))
            END_INLINE_EVENT
            ADD(LW(11), 1)
        END_LOOP
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_fade_entry, FADE_CURTAIN_SIDES_A1_3D, 1000, 0, 0, 0)
        CALL(evt_fade_set_anim_ofs_pos, 0, 130)
        CALL(evt_fade_set_anim_virtual_pos, 0, 0, 80)
        CALL(evt_fade_end_wait)
        CALL(btlevtcmd_AnimeChangeGroup, BTL_UNIT_SELF, 1, STRING("c_korutesu3"))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_mode_3))
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_SetDiveSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE3"), 0, 0, 0, 0)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_fade_entry, FADE_CURTAIN_SIDES_A2_3D, 1000, 0, 0, 0)
        CALL(evt_fade_set_anim_ofs_pos, 0, 130)
        CALL(evt_fade_set_anim_virtual_pos, 0, 0, 80)
        CALL(evt_fade_end_wait)
        CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
        CALL_CHILD(cortez_reset_pose_table)
        CALL(btlevtcmd_SetCutBaseOffset, BTL_UNIT_SELF, 0, 48, 0)
        CALL(btlevtcmd_SetCutWidth, BTL_UNIT_SELF, 90)
        CALL(btlevtcmd_SetCutHeight, BTL_UNIT_SELF, 96)
        CALL(btlevtcmd_reset_turn)
        CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
        CASE_END
        CASE_DEFAULT
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 0, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, -1)
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 70)
#else
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 71)
#endif
            CALL(btlevtcmd_RunHitEventDirect, LW(3), 0, LW(0), 0)
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 0, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, -1)
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 70)
#else
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 71)
#endif
            CALL(btlevtcmd_RunHitEventDirect, LW(3), 0, LW(0), 0)
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 0, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, -1)
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 70)
#else
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 71)
#endif
            CALL(btlevtcmd_RunHitEventDirect, LW(3), 0, LW(0), 0)
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_SetUnitWork, LW(3), 0, -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, -1)
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 70)
#else
            CALL(btlevtcmd_GetDataFromDataTable, LW(3), LW(0), 71)
#endif
            CALL(btlevtcmd_RunHitEventDirect, LW(3), 0, LW(0), 0)
        END_IF
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_D_3"))
        BEGIN_SIBLING_EVENT
            WAIT_MS(1500)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_BONE_FALL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, 50331648)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        ADD(LW(2), 10)
        CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(btlevtcmd_GetCoin, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_StoreCoin, LW(0))
        CALL(btlevtcmd_GetExp, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_StoreExp, LW(0))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(3), LW(1), LW(2))
        ADD(LW(2), 10)
        ADD(LW(1), 30)
        CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1000)
        CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Opens Cortez's ribs in mode 2: plays the rib-open pose for his mode,
 * an inhale sound and then makes the interior (part 2) hittable, resetting his pose table.
 */
EVT_BEGIN(mode2_rib_open_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, 2)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1D2_3"))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2D2_3"))
        CASE_EQUAL(3)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3D3_3"))
    END_SWITCH
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_INHALE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 65536)
    CALL_CHILD(cortez_reset_pose_table)
    RETURN
EVT_END()

/**
 * Closes Cortez's ribs in mode 2: plays the rib-close pose and the counter sound,
 * makes the ribs protect the interior again and resets his pose table.
 */
EVT_BEGIN(mode2_rib_close_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 11, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1D2_4"))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2D2_4"))
        CASE_EQUAL(3)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_3D3_4"))
    END_SWITCH
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_RIB_COUNTER1"), EVT_NULLPTR, 0, EVT_NULLPTR)
#endif
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 65536)
    CALL_CHILD(cortez_reset_pose_table)
    RETURN
EVT_END()

/**
 * Damage event when the bone part (part 4) is hit in mode 2:
 * marks the unit hit, and if the damage code says it is a heavy hit changes mode (mode_change_event)
 * while a sibling event wobbles the part; kills Cortez if his HP is gone.
 */
EVT_BEGIN(mode2_honeduka_damage_event)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 1)
#endif
    SET_VALUE(LW(8), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 7, 1)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 256, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(8))
            CALL_CHILD(mode_change_event)
        END_SIBLING_EVENT
    END_IF
    BEGIN_SIBLING_EVENT_GET_ID(LW(9))
        CALL(evt_sub_intpl_init, 8, 6, 0, 30)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetPartsDispOffset, BTL_UNIT_SELF, 4, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(8))
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL_CHILD(dead_event)
        RETURN
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Changes Cortez's phase: plays the transformation pose (KRT_1H to KRT_3H),
 * the move sounds and sets unit work 5 to the next mode, then resets his pose and defence tables.
 * Mode 1 goes to mode 2, mode 2 goes to mode 3.
 */
EVT_BEGIN(mode_change_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1H_1"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_1H2_1"))
        END_IF
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE1"), EVT_NULLPTR, 0, LW(15))
#else
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
#endif
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(evt_snd_sfxoff, LW(15))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 2)
        CALL_CHILD(cortez_reset_pose_table)
        CASE_EQUAL(2)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 11, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2H_1"))
        ELSE
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_2H2_1"))
        END_IF
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE1"), EVT_NULLPTR, 0, LW(15))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(evt_snd_sfxoff, LW(15))
#else
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(btlevtcmd_ftomsec, 80, LW(0))
            WAIT_MS(LW(0))
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KOR_MOVE2"), EVT_NULLPTR, 0, LW(15))
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            CALL(evt_snd_sfxoff, LW(15))
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
#endif
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 3)
        CALL_CHILD(cortez_reset_pose_table)
        CALL_CHILD(mode2_rib_open_event)
        CASE_DEFAULT
    END_SWITCH
    RETURN
EVT_END()

/**
 * Script helper: writes 1 to args[1] if the unit args[0] stands left of x = -120 (the front or back guard side),
 * otherwise 0; Cortez uses it to choose which attack pose to play.
 */
static USER_FUNC(_check_zenei_kouei) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    f32 x, y, z;

    id = BattleTransID(event, id);
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (x >= -120.0f) {
        evtSetValue(event, out, 0);
    } else {
        evtSetValue(event, out, 1);
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper for the audience drain (runs until finished):
 * resets the 100 audience seat markers, waits for all of them to settle,
 * then deletes each seat's audience member and subtracts it from the audience target count.
 */
static USER_FUNC(_cortez_recovery_audience) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, *args++);
    CortezWork* work;
    BOOL done;
    s32 i;
    s32 aid;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    work->seq[i] = 0;
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                if (work->audienceId[i] != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            done = TRUE;
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
            work->state++;
        case 2:
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    BattleAudience_Delete(aid);
                    BattleAudienceAddTargetNum(0.0f, -1.0f);
                }
            }
            work->state++;
            return EVT_RETURN_DONE;
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: removes every spirit effect Cortez's audience drain created
 * and writes the number of audience members he collected (work->count) to args[1].
 */
static USER_FUNC(_cortez_drain_energy) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    for (i = 0; i < 100; i++) {
        if (work->eff[i] != NULL) {
            effDelete(work->eff[i]);
            work->eff[i] = NULL;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}

/**
 * Script helper for the audience drain (runs until finished):
 * flags each audience member of the 100 seats as removed, plays their scared animation,
 * sends a spirit effect from each seat to Cortez and a cloud at his position,
 * then tips each member back by 90 degrees over 30 frames.
 */
static USER_FUNC(_cortez_collect_energy) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;
    CortezWork* work;
    BattleAudienceMember* member;
    BOOL done;
    s32 aid;
    s32 i;
    BOOL kumo;
    f32 x, y, z;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    work = (CortezWork*)unit->countersetWeapon;
    if (isFirstCall) {
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            kumo = FALSE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    member = BattleAudienceGetPtr(aid);
                    member->flags |= MEMBER_FLAG_REMOVED | MEMBER_FLAG_EVT_CTRL;
                    BattleAudience_SetAnim(aid, 9, TRUE);
                    work->wait[i] = irand(60) + 30;
                    work->srcPos[i] = member->position;
                    BtlUnit_GetPos(unit, &work->dstPos[i].x, &work->dstPos[i].y, &work->dstPos[i].z);
                    work->dstPos[i].y += 20.0f;
                    effSpiritEntry(0, work->wait[i] + 60, work->srcPos[i].x, work->srcPos[i].y, work->srcPos[i].z,
                                   work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 2.0f);
                    if (!kumo) {
                        kumo = TRUE;
                        effKumokumoN64Entry(1, 60, work->dstPos[i].x, work->dstPos[i].y, work->dstPos[i].z, 180.0f,
                                            -1.0f, 1.0f);
                    }
                }
            }
            work->state++;
        case 1:
            done = TRUE;
            for (i = 0; i < 100; i++) {
                aid = work->audienceId[i];
                if (aid != -1) {
                    switch (work->seq[i]) {
                        case 0:
                            if (work->wait[i] > 0) {
                                work->wait[i]--;
                                done = FALSE;
                                break;
                            }
                            work->seq[i]++;
                            work->timer[i] = 0;
                        case 1:
                            work->timer[i]++;
                            BattleAudience_GetRotate(aid, &x, &y, &z);
                            x = intplGetValue(0, 0.0f, -90.0f, work->timer[i], 30);
                            BattleAudience_SetRotate(aid, x, y, z);
                            if (work->timer[i] >= 30) {
                                work->seq[i]++;
                            } else {
                                done = FALSE;
                                break;
                            }
                        case 2:
                            work->timer[i] = 0;
                            work->seq[i]++;
                        case 3:
                            work->timer[i]++;
                            if (work->timer[i] >= 60) {
                                work->seq[i]++;
                            }
                            done = FALSE;
                            break;
                        case 4:
                            break;
                    }
                }
            }
            if (!done) {
                break;
            }
        default:
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Script helper: scans the 100 audience seats (10 rows of 10) and records
 * which are occupied in Cortez's work area; writes the number of occupied seats to args[1].
 */
static USER_FUNC(_cortez_check_drain_audience) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    s32 seat;
    CortezWork* work;
    s32 i;

    id = BattleTransID(event, id);
    work = (CortezWork*)BattleGetUnitPtr(wp, id)->countersetWeapon;
    work->count = 0;
    for (i = 0; i < 100; i++) {
        work->audienceId[i] = -1;
        work->eff[i] = NULL;
        work->seq[i] = 0;
        seat = 10 + (i / 10) * 20 + i % 10;
        if ((u8)BattleAudience_GetExist(seat)) {
            work->audienceId[i] = seat;
            work->count++;
        }
    }
    evtSetValue(event, out, work->count);
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/** Script helper: writes the current volume of sound effect args[0] to args[1]. */
USER_FUNC(_cortez_get_sfx_vol) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];

    evtSetValue(event, out, psndSFX_get_vol(id));
    return EVT_RETURN_DONE;
}
#endif

/**
 * Script helper: allocates Cortez's work area (CortezWork, used to track the audience drain)
 * and stores it in the unit's countersetWeapon pointer.
 */
static USER_FUNC(_make_cortez_work_area) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(CortezWork));
    return EVT_RETURN_DONE;
}
