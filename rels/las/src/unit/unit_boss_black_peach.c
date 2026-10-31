// Palace of Shadow battle unit: Shadow Queen (final boss), her hands and the possessed-Peach first phase (`boss_black_peach`): parts, stats, poses and AI scripts.

#include "eff/n64/eff_shock_n64.h"
#include "eff/n64/eff_pokopi_thunder_n64.h"
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "battle/battle_audience.h"
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/npcdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "string.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "battle/battle_event_cmd.h"
#include "eff/n64/eff_stardust2_n64.h"
#include "evt/evt_batstage.h"
#include "evt/evt_eff.h"
#include "evt/evt_env.h"
#include "evt/evt_ext.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "pmario_sound.h"
#include "unit/party/unit_party_vivian.h"
#include "battle/battle_camera.h"
#include "evt/evt_story.h"

// Unit work slots of the possessed Peach, later the Shadow Queen (also reached through GW(13)).
enum {
    UW_BOSS_BLACK_PEACH_ATTACK_STEP = 0, // step of the fixed opening attacks, then random draws; the hands skip while 2
    UW_BOSS_BLACK_PEACH_ATTACK_MSG = 1,  // queen attack messages shown so far (1 first, 2 next, 3 last)
    UW_BOSS_BLACK_PEACH_HP_MSG = 2,      // queen HP messages shown (1 at half HP, 2 at a quarter)
};

typedef struct HandElem {
    u16 flip;
    u8 pad_2[2];
    s32 animIdx;
    OSTime time;
    s16 ofs;
    s16 phase;
    f32 speed;
    Vec pos;
    s32 poseId;
} HandElem; /* poseId: never accessed */
typedef struct HandAnim {
    char name[16];
    char anim[8];
    f32 rate;
    s32 start;
    s32 count;
} HandAnim;
typedef struct HandWork {
    HandElem* elems;
    s32 num;
    HandAnim anim[32];
    u8 groupPos[0x49C - 0x488];
    f32 y;
    u8 ySpeed[4];
    s32 animNum;
    s32 timer;
    s32 state;
} HandWork; /* groupPos/ySpeed: never accessed */
typedef struct HandData {
    const char* name;
    const char* anim;
    f32 rate;
} HandData;
typedef struct QueenConnect {
    s32 poseId[3];
    u8 locatorWork[0x40 - 0xC];
    s32 idx[2];
} QueenConnect; /* locatorWork: never accessed */
HandData hand_data[32];
HandWork* hand_wp;
#include "battle/battle_break_slot.h"
#include "driver/extdrv.h"
#include "driver/lightdrv.h"

static USER_FUNC(eff_queen_set_alpha_evt);
static USER_FUNC(make_pattern);
static USER_FUNC(peach_hand1000_dark_drag_1_evt);
static USER_FUNC(peach_talk_synchro_shadow_head_evt);
static USER_FUNC(queen_drain);
static USER_FUNC(queen_get_aud_num);
static USER_FUNC(queen_hand_small_1000hand_1_evt);
static USER_FUNC(queen_hand_small_1000hand_2_evt);
static USER_FUNC(queen_hand_small_1000hand_set_offset_evt);
static USER_FUNC(queen_hand_small_dead_evt);
static USER_FUNC(queen_hand_small_drag_1_evt);
static USER_FUNC(queen_hand_small_drag_2_evt);
static USER_FUNC(queen_hand_small_drag_3_evt);
static USER_FUNC(queen_hand_small_entry_evt);
static USER_FUNC(queen_hp_drain_1_evt);
static USER_FUNC(queen_hp_drain_2_evt);
static USER_FUNC(queen_hp_drain_3_evt);
static USER_FUNC(queen_hp_drain_4_evt);
static USER_FUNC(queen_hp_drain_5_evt);
static USER_FUNC(queen_kankyaku_delete_evt);
static USER_FUNC(queen_thunder);
static USER_FUNC(shadow_queen_connect);
static USER_FUNC(slot_init);
#if VERSION >= VERSION_JP
USER_FUNC(queen_break_slot_flag2_on);
#endif
static void hand_main(void);
static void hand_draw(CameraId cameraId, void* param);
static void hand_init(void);
static void pose_main(void);
static void pose_init(void);

BattleUnitKind unit_boss_black_peach;
BattleUnitDefense peach_defence;
BattleUnitDefenseAttr peach_defence_attr;
StatusVulnerability peach_regist;
PoseTableEntry peach_pose_table[18];
BattleDataEntry peach_data_table[2];
BattleUnitKindPart peach_parts[7];
BattleWeapon weapon_peach_black_thunder_attack;
BattleWeapon weapon_peach_black_energy_attack;
BattleWeapon weapon_peach_drain_attack;
BattleWeapon weapon_peach_dark_drag_attack;
BattleWeapon weapon_peach_dark_drag_last_attack;
BattleWeapon weapon_peach_dark_charge_attack;
BattleWeapon weapon_peach_black_wave_attack;
BattleWeapon weapon_peach_black_sigh_attack;
BattleWeapon weapon_peach_black_temptation_attack;
BattleWeapon weapon_peach_black_poison_attack;
BattleWeapon weapon_peach_black_press_attack;
BattleWeapon weapon_peach_black_1000hand_attack;
BattleUnitKind unit_boss_shadow_queen;
BattleUnitDefense queen_defence;
BattleUnitDefenseAttr queen_defence_attr;
StatusVulnerability queen_regist;
BattleUnitDefense queen_muteki_defence;
BattleUnitDefenseAttr queen_muteki_defence_attr;
StatusVulnerability queen_muteki_regist;
PoseTableEntry queen_pose_table[18];
PoseTableEntry queen_hand_pose_table[4];
BattleDataEntry queen_data_table[2];
BattleUnitKindPart queen_parts[5];
f32 hair_offset[36];
BattleUnitKind unit_boss_shadow_hand_1;
BattleUnitDefense queen_hand_1_defence;
BattleUnitDefenseAttr queen_hand_1_defence_attr;
StatusVulnerability queen_hand_1_regist;
PoseTableEntry queen_hand_1_pose_table[8];
BattleDataEntry queen_hand_1_data_table[2];
BattleUnitKindPart queen_hand_1_parts[1];
BattleUnitKind unit_boss_shadow_hand_2;
BattleUnitDefense queen_hand_2_defence;
BattleUnitDefenseAttr queen_hand_2_defence_attr;
StatusVulnerability queen_hand_2_regist;
PoseTableEntry queen_hand_2_pose_table[8];
BattleDataEntry queen_hand_2_data_table[2];
BattleUnitKindPart queen_hand_2_parts[1];
BattleUnitKind unit_boss_shadow_hand_small;
BattleUnitDefense queen_hand_small_defence;
BattleUnitDefenseAttr queen_hand_small_defence_attr;
StatusVulnerability queen_hand_small_regist;
PoseTableEntry queen_hand_small_pose_table[8];
BattleDataEntry queen_hand_small_data_table[2];
BattleUnitKindPart queen_hand_small_parts[1];
BattleUnitSetup entry_shadow_queen;
BattleUnitSetup entry_shadow_hand_1;
BattleUnitSetup entry_shadow_hand_2;
BattleUnitSetup entry_shadow_hand_small;
extern EvtWord peach_init_event[];
extern EvtWord peach_entry_event[];
extern EvtWord peach_damage_event[];
extern EvtWord peach_phase_event[];
extern EvtWord peach_dead_event[];
extern EvtWord peach_attack_event[];
extern EvtWord peach_wait_event[];
extern EvtWord queen_init_event[];
extern EvtWord queen_phase_event[];
extern EvtWord queen_attack_event[];
extern EvtWord queen_damage_event[];
extern EvtWord queen_dead_event[];
extern EvtWord queen_wait_event[];
extern EvtWord queen_entry_event[];
extern EvtWord queen_hand_1_init_event[];
extern EvtWord queen_hand_1_attack_event[];
extern EvtWord queen_hand_1_damage_event[];
extern EvtWord queen_hand_1_dead_event[];
extern EvtWord queen_hand_1_wait_event[];
extern EvtWord queen_hand_2_init_event[];
extern EvtWord queen_hand_2_attack_event[];
extern EvtWord queen_hand_2_damage_event[];
extern EvtWord queen_hand_2_dead_event[];
extern EvtWord queen_hand_2_wait_event[];
extern EvtWord queen_hand_small_init_event[];
extern EvtWord queen_hand_small_attack_event[];
extern EvtWord queen_hand_small_damage_event[];
extern EvtWord queen_hand_small_dead_event[];
extern EvtWord queen_hand_small_wait_event[];

/**
 * Unit data of the Shadow Queen (possessing Peach), the first phase of the final fight, in the Palace of
 * Shadow: 150 HP;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_black_peach = {
    148,
    "btl_un_black_peach",
    150,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    6,
    40,
    54,
    5,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    -3,
    0.0f,
    40.0f,
    0.0f,
    20.0f,
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
    15.0f,
    45.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    40.0f,
    54.0f,
    80,
    0,
    0,
    2,
    100,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_BPCH_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &peach_regist,
    7,
    peach_parts,
    peach_init_event,
    peach_data_table,
};

/**
 * Defence of the Shadow Queen (possessing Peach) against each element (normal, fire, ice, explosion,
 * electric): none, so every hit does its full damage.
 */
BattleUnitDefense peach_defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of the Shadow Queen (possessing Peach) per element (normal, fire, ice, explosion,
 * electric): none, so no element is a weakness, an immunity or a heal.
 */
BattleUnitDefenseAttr peach_defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of the Shadow Queen (possessing Peach):
 * percent chance that each status takes hold (100 is normal);
 * immune to Frozen, Fright, Gale Force, Instant KO;
 * strongly resistant to Sleep, Stop, Dizzy, Confuse, Defense Down, Allergic, Slow.
 */
StatusVulnerability peach_regist = {30, 30, 30, 100, 30, 100, 50, 0, 100, 50, 100, 50, 100, 30, 30, 0, 0, 100, 30, 100, 100, 0};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Shadow Queen (possessing Peach):
 * percent chance that each status takes hold (100 is normal);
 * immune to Frozen, Fright, Gale Force, Instant KO;
 * strongly resistant to Sleep, Stop, Dizzy, Confuse, Allergic, Slow.
 */
StatusVulnerability peach_regist = {30, 30, 30, 100, 30, 100, 100, 0, 100, 60, 100, 60, 100, 75, 30, 0, 0, 100, 30, 100, 100, 0};
#endif

/**
 * Pose table of the Shadow Queen (possessing Peach): animation names for each pose type (idle, walk, hurt,
 * attack and so on).
 */
PoseTableEntry peach_pose_table[] = {
    {1, "KRT_N_1"},
    {2, "KRT_Z_1"},
    {9, "KRT_Z_1"},
    {5, "KRT_K_1"},
    {4, "KRT_S_1"},
    {3, "KRT_K_1"},
    {28, "KRT_S_1"},
    {29, "KRT_D_1"},
    {30, "KRT_Q_1"},
    {31, "KRT_Q_1"},
    {39, "KRT_D_1"},
    {50, "KRT_A_1"},
    {42, "KRT_W_1"},
    {40, "KRT_W_1"},
    {56, "KRT_X_1"},
    {57, "KRT_X_1"},
    {BTL_POSE_TALK, "KRT_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Data table of the Shadow Queen (possessing Peach): event scripts and values the battle looks up by tag
 * (damage reactions, dodge, first strike and so on).
 */
BattleDataEntry peach_data_table[] = {
    {49, peach_dead_event},
    {0, NULL},
};

/**
 * Parts of the Shadow Queen (possessing Peach): 7 parts with their hit boxes, defence tables and pose tables.
 */
BattleUnitKindPart peach_parts[] = {
    {1, "btl_un_shadow_queen", "c_b_peach_b", 0.0f, VERSION_PICK(0.0f, 2.0f), 0.0f, -2.0f, 44.0f, 0.0f, -2.0f, 44.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, peach_pose_table},
    {2, "btl_un_shadow_queen", "c_q_kage_b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, peach_pose_table},
    {3, "btl_un_shadow_queen", "c_q_kage_f", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, peach_pose_table},
    {4, "btl_un_shadow_queen", "c_q_kage_h", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, peach_pose_table},
    {5, "btl_un_shadow_queen", "c_q_kage_f", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, peach_pose_table},
    {6, "btl_un_shadow_hand_big_1", "c_b_hand", 15.0f, 0.0f, -50.0f, 0.0f, 38.0f, 5.0f, 0.0f, 38.0f, 5.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, peach_pose_table},
    {7, "btl_un_shadow_hand_big_2", "c_b_hand", 160.0f, 0.0f, 50.0f, 0.0f, 38.0f, 5.0f, 0.0f, 38.0f, 5.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, peach_pose_table},
};

/** Weapon of the Shadow Queen's black thunder: damage 7. */
BattleWeapon weapon_peach_black_thunder_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_ELECTRIC, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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
 * Weapon of the Shadow Queen's energy move that changes attack and defence:
 * inflicts an attack change, a defense change.
 */
BattleWeapon weapon_peach_black_energy_attack = {
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
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, // burnTime..sizeChangeStrength
    100, // atkChangeChance
    3, // atkChangeTime
    3, // atkChangeStrength
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

/** Weapon of the possessed Peach's life drain: damage 7. */
BattleWeapon weapon_peach_drain_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon of the dark drag, in which the hands drag at the target: damage 3. */
BattleWeapon weapon_peach_dark_drag_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon of the last hit of the dark drag. */
BattleWeapon weapon_peach_dark_drag_last_attack = {
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
#if VERSION <= VERSION_DEMO_US
    weaponGetPowerDefault, // hpDamageFn
#else
    NULL, // hpDamageFn
#endif
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    27, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION <= VERSION_DEMO_US
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon of the possessed Peach's charge-up. */
BattleWeapon weapon_peach_dark_charge_attack = {
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

/** Weapon of the Shadow Queen's wave of dark energy over the party: damage 7. */
BattleWeapon weapon_peach_black_wave_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
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
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of the Shadow Queen's sigh: damage 4; inflicts Allergic (90% in US and PAL, 60% in the demos and
 * JP).
 */
BattleWeapon weapon_peach_black_sigh_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, // atkChangeStrength..defChangeStrength
#if VERSION >= VERSION_US
    90, // allergicChance
#else
    60, // allergicChance
#endif
    3, // allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of the Shadow Queen's temptation breath: damage 4;
 * inflicts Confuse (75% in US and PAL, 50% in the demos and JP).
 */
BattleWeapon weapon_peach_black_temptation_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, // poisonStrength
#if VERSION >= VERSION_US
    75, // confuseChance
#else
    50, // confuseChance
#endif
    3, // confuseTime
    0, 0, 0, 0, 0, 0, 0, 0, // electricChance..freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Weapon of the Shadow Queen's poison breath: damage 4;
 * inflicts Poison (75% in US and PAL, 50% in the demos and JP).
 */
BattleWeapon weapon_peach_black_poison_attack = {
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
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
#if VERSION >= VERSION_US
    75, // poisonChance
#else
    50, // poisonChance
#endif
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

/** Weapon of the big hand's press: damage 7. */
BattleWeapon weapon_peach_black_press_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
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

/** Weapon of the small hand's thousand-hands attack: damage 3. */
BattleWeapon weapon_peach_black_1000hand_attack = {
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
#if VERSION >= VERSION_US
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE, // special
#else
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE, // special
#endif
    COUNTER_RESIST_ALL, // counterResistFlags
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
 * Unit data of the Shadow Queen in the Palace of Shadow: 150 HP;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_shadow_queen = {
    150,
    "btl_un_shadow_queen",
    150,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    VERSION_PICK(6, 5),
    40,
    54,
    0,
    54,
    0.0f,
    90.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    20.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    50.0f,
    40.0f,
    0.0f,
    0.0f,
    27.0f,
    0.0f,
    40.0f,
    54.0f,
    80,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    "SFX_BOSS_QUEN_DAMAGED1",
#else
    "SFX_BOSS_QWEN_DAMAGED1",
#endif
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &queen_regist,
    5,
    queen_parts,
    queen_init_event,
    queen_data_table,
};

/**
 * Defence of the Shadow Queen against each element (normal, fire, ice, explosion, electric):
 * 1 against every element, so each hit is cut by 1.
 */
BattleUnitDefense queen_defence = {{1, 1, 1, 1, 1}};

/**
 * Damage modifiers of the Shadow Queen per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
BattleUnitDefenseAttr queen_defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of the Shadow Queen:
 * percent chance that each status takes hold (100 is normal);
 * immune to Frozen, Tiny, Attack Down, Fright, Gale Force, Dodgy, Invisible, Instant KO;
 * strongly resistant to Sleep, Stop, Dizzy, Confuse, Defense Down, Allergic, Slow.
 */
StatusVulnerability queen_regist = {30, 30, 30, 100, 30, 100, 50, 0, 100, 0, 100, 0, 100, 30, 30, 0, 0, 100, 30, 0, 0, 0};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Shadow Queen:
 * percent chance that each status takes hold (100 is normal);
 * immune to Frozen, Tiny, Attack Down, Fright, Gale Force, Dodgy, Invisible, Instant KO;
 * strongly resistant to Sleep, Stop, Dizzy, Confuse, Allergic, Slow.
 */
StatusVulnerability queen_regist = {30, 30, 30, 100, 30, 100, 100, 0, 100, 0, 100, 0, 100, 60, 30, 0, 0, 100, 30, 0, 0, 0};
#endif

/**
 * Defence of the Shadow Queen while she is invincible:
 * defence 99 against every kind of hit, so no attack does damage.
 */
BattleUnitDefense queen_muteki_defence = {{99, 99, 99, 99, 99}};

/**
 * Damage modifiers of the Shadow Queen while she is invincible per element (normal, fire, ice, explosion,
 * electric): normal: immune, fire: immune, ice: immune, explosion: immune, electric: immune.
 */
BattleUnitDefenseAttr queen_muteki_defence_attr = {{2, 2, 2, 2, 2}};

/**
 * Status vulnerability of the Shadow Queen while she is invincible:
 * percent chance that each status takes hold (100 is normal); immune to Sleep.
 */
StatusVulnerability queen_muteki_regist = {0};

/**
 * Pose table of the Shadow Queen: animation names for each pose type (idle, walk, hurt, attack and so on).
 */
PoseTableEntry queen_pose_table[] = {
    {1, "KRT_S_1"},
    {2, "KRT_S_1"},
    {9, "KRT_S_1"},
    {5, "KRT_S_1"},
    {4, "KRT_S_1"},
    {3, "KRT_S_1"},
    {28, "KRT_S_1"},
    {29, "KRT_S_1"},
    {30, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {50, "KRT_S_1"},
    {42, "KRT_S_1"},
    {40, "KRT_S_1"},
    {56, "KRT_S_1"},
    {57, "KRT_S_1"},
    {BTL_POSE_TALK, "KRT_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Pose table of the Shadow Queen's big hands: animation names for each pose type (idle, walk, hurt, attack
 * and so on).
 */
PoseTableEntry queen_hand_pose_table[] = {
    {28, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Data table of the Shadow Queen: event scripts
 * and values the battle looks up by tag (damage reactions, dodge, first strike and so on).
 */
BattleDataEntry queen_data_table[] = {
    {49, queen_dead_event},
    {0, NULL},
};

/** Parts of the Shadow Queen: 6 parts with their hit boxes, defence tables and pose tables. */
BattleUnitKindPart queen_parts[] = {
#if VERSION <= VERSION_DEMO_US
    {1, "btl_un_shadow_queen", "c_b_peach_b", 0.0f, VERSION_PICK(0.0f, 2.0f), 0.0f, 0.0f, 47.0f, 0.0f, 0.0f, 47.0f, 0.0f, 41, 61, 255, &peach_defence, &peach_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, peach_pose_table},
#else
    {1, "btl_un_shadow_queen", "c_b_peach_b", 0.0f, VERSION_PICK(0.0f, 2.0f), 0.0f, 0.0f, 47.0f, 0.0f, 0.0f, 47.0f, 0.0f, 41, 61, 255, &queen_defence, &queen_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, peach_pose_table},
#endif
    {2, "btl_un_shadow_queen", "c_q_kage_b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &queen_defence, &queen_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW, 0, queen_pose_table},
    {3, "btl_un_shadow_queen", "c_q_kage_f", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &queen_defence, &queen_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, queen_pose_table},
    {4, "btl_un_shadow_queen", "c_q_kage_h", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &queen_defence, &queen_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, queen_pose_table},
    {5, "btl_un_shadow_queen", "c_q_kage_f", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 41, 61, 255, &queen_defence, &queen_defence_attr, PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, queen_pose_table},
};

/**
 * Unused table of 36 offsets named hair_offset in the symbol map;
 * the Shadow Queen's unit code does not read it.
 */
f32 hair_offset[] = {
    -13.0f, 63.0f, 5.0f, 57.0f, -24.0f, -40.0f, -10.0f, 61.0f,
    -7.0f, 24.0f, 17.0f, -16.0f, -10.0f, 60.0f, -9.0f, -27.0f,
    29.0f, 7.0f, -4.0f, 63.0f, -5.0f, 21.0f, -3.0f, 14.0f,
    -6.0f, 63.0f, 1.0f, 22.0f, -18.0f, -18.0f, -7.0f, 61.0f,
    0.0f, 13.0f, 0.0f, -21.0f,
};

/** inline helper for pose_init: defined here so its Vec template lands at this .rodata position */
inline void hand_light_init(void) {
    Mtx mtx;
    LightEntry* light = lightGetPaperCraft();

    light->position = (Vec){-200.0f, 100.0f, 500.0f};
    PSMTXScale(mtx, 3.0f, 3.0f, 3.0f);
    PSMTXMultVec(mtx, &light->position, &light->position);
}

/**
 * Event script: sets up the swarm of "small hand" ext poses (model c_s_hand, animation KRT_S_1) that the Shadow
 * Queen uses for her many-hands attacks and her draining.
 * It creates a hidden helper NPC "dummy" to read the animation,
 * builds the pattern table with make_pattern and registers the ext drawing callbacks (hand_init, hand_main).
 */
EVT_BEGIN(shadow_queen_1000)
    CALL(evt_npc_entry, STRING("dummy"), STRING("c_s_hand"))
    CALL(evt_npc_set_anim, STRING("dummy"), STRING("KRT_S_1"))
    CALL(evt_npc_set_position, STRING("dummy"), 0, -1000, 0)
    CALL(make_pattern)
    CALL(evt_ext_entry, 100, PTR(hand_data), PTR(hand_init), PTR(hand_main), 0)
    RETURN
EVT_END()

/**
 * Unit data of the Shadow Queen's first big hand in the Palace of Shadow: 5 HP;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_shadow_hand_1 = {
    151,
    "btl_un_shadow_queen",
    5,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    7,
    90,
    110,
    0,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    40.0f,
    40.0f,
    0.0f,
    45.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    45.0f,
    71.5f,
    0.0f,
    -30.0f,
    55.0f,
    0.0f,
    75.0f,
    110.0f,
    100,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    "SFX_BOSS_QUEN_DAMAGED1",
#else
    "SFX_BOSS_QWEN_DAMAGED1",
#endif
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_HP_GAUGE,
    &queen_hand_1_regist,
    1,
    queen_hand_1_parts,
    queen_hand_1_init_event,
    queen_hand_1_data_table,
};

/**
 * Defence of the Shadow Queen's first big hand against each element (normal, fire, ice, explosion,
 * electric): none, so every hit does its full damage.
 */
BattleUnitDefense queen_hand_1_defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of the Shadow Queen's first big hand per element (normal, fire, ice, explosion,
 * electric): none, so no element is a weakness, an immunity or a heal.
 */
BattleUnitDefenseAttr queen_hand_1_defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of the Shadow Queen's first big hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Defense Down,
 * Allergic.
 */
StatusVulnerability queen_hand_1_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 30, 30, 0, 0, 0, 0, 0, 0, 0};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Shadow Queen's first big hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Allergic.
 */
StatusVulnerability queen_hand_1_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 80, 30, 0, 0, 0, 0, 0, 0, 0};
#endif

/**
 * Pose table of the Shadow Queen's first big hand:
 * animation names for each pose type (idle, walk, hurt, attack and so on).
 */
PoseTableEntry queen_hand_1_pose_table[] = {
    {28, "KRT_S_1"},
    {29, "KRT_Q_1"},
    {30, "KRT_Q_1"},
    {31, "KRT_D_1"},
    {39, "KRT_D_1"},
    {56, "KRT_S_1"},
    {57, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Data table of the Shadow Queen's first big hand:
 * event scripts and values the battle looks up by tag (damage reactions, dodge, first strike and so on).
 */
BattleDataEntry queen_hand_1_data_table[] = {
#if VERSION <= VERSION_DEMO_US
    {50, queen_hand_1_dead_event},
#else
    {49, queen_hand_1_dead_event},
#endif
    {0, NULL},
};

/**
 * Part of the Shadow Queen's first big hand: its one body part with hit box, defence tables and pose table.
 */
BattleUnitKindPart queen_hand_1_parts[] = {
    {1, "btl_un_shadow_hand_big_1", "c_b_hand", 0.0f, 0.0f, 0.0f, 16.0f, 47.0f, 30.0f, 16.0f, 47.0f, 30.0f, 41, 61, 255, &queen_hand_1_defence, &queen_hand_1_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, queen_hand_1_pose_table},
};

/**
 * Unit data of the Shadow Queen's second big hand in the Palace of Shadow: 5 HP;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_shadow_hand_2 = {
    151,
    "btl_un_shadow_queen",
    5,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    7,
    90,
    110,
    0,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    40.0f,
    40.0f,
    0.0f,
    45.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    25.0f,
    0.0f,
    0.0f,
    45.0f,
    71.5f,
    0.0f,
    -30.0f,
    55.0f,
    0.0f,
    75.0f,
    110.0f,
    100,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    "SFX_BOSS_QUEN_DAMAGED1",
#else
    "SFX_BOSS_QWEN_DAMAGED1",
#endif
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_HP_GAUGE,
    &queen_hand_2_regist,
    1,
    queen_hand_2_parts,
    queen_hand_2_init_event,
    queen_hand_2_data_table,
};

/**
 * Defence of the Shadow Queen's second big hand against each element (normal, fire, ice, explosion,
 * electric): none, so every hit does its full damage.
 */
BattleUnitDefense queen_hand_2_defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of the Shadow Queen's second big hand per element (normal, fire, ice, explosion,
 * electric): none, so no element is a weakness, an immunity or a heal.
 */
BattleUnitDefenseAttr queen_hand_2_defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of the Shadow Queen's second big hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Defense Down,
 * Allergic.
 */
StatusVulnerability queen_hand_2_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 30, 30, 0, 0, 0, 0, 0, 0, 0};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Shadow Queen's second big hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Allergic.
 */
StatusVulnerability queen_hand_2_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 80, 30, 0, 0, 0, 0, 0, 0, 0};
#endif

/**
 * Pose table of the Shadow Queen's second big hand:
 * animation names for each pose type (idle, walk, hurt, attack and so on).
 */
PoseTableEntry queen_hand_2_pose_table[] = {
    {28, "KRT_S_1"},
    {29, "KRT_Q_1"},
    {30, "KRT_Q_1"},
    {31, "KRT_D_1"},
    {39, "KRT_D_1"},
    {56, "KRT_S_1"},
    {57, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Data table of the Shadow Queen's second big hand:
 * event scripts and values the battle looks up by tag (damage reactions, dodge, first strike and so on).
 */
BattleDataEntry queen_hand_2_data_table[] = {
#if VERSION <= VERSION_DEMO_US
    {50, queen_hand_2_dead_event},
#else
    {49, queen_hand_2_dead_event},
#endif
    {0, NULL},
};

/**
 * Part of the Shadow Queen's second big hand: its one body part with hit box, defence tables and pose table.
 */
BattleUnitKindPart queen_hand_2_parts[] = {
    {1, "btl_un_shadow_hand_big_2", "c_b_hand", 0.0f, 0.0f, 0.0f, 28.0f, 56.0f, 20.0f, 28.0f, 56.0f, 20.0f, 41, 61, 255, &queen_hand_2_defence, &queen_hand_2_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, queen_hand_2_pose_table},
};

/**
 * Unit data of the Shadow Queen's small hand in the Palace of Shadow: 8 HP;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_boss_shadow_hand_small = {
    152,
    "btl_un_shadow_queen",
    8,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    7,
    220,
    45,
    0,
    54,
    0.0f,
    27.0f,
    0.0f,
    0,
    0,
    40.0f,
    40.0f,
    0.0f,
    110.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    110.0f,
    0.0f,
    0.0f,
    110.0f,
    29.25f,
    0.0f,
    0.0f,
    22.0f,
    0.0f,
    180.0f,
    45.0f,
    90,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_US
    "SFX_BOSS_QUEN_DAMAGED1",
#else
    "SFX_BOSS_QWEN_DAMAGED1",
#endif
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &queen_hand_small_regist,
    1,
    queen_hand_small_parts,
    queen_hand_small_init_event,
    queen_hand_small_data_table,
};

/**
 * Defence of the Shadow Queen's small hand against each element (normal, fire, ice, explosion, electric):
 * none, so every hit does its full damage.
 */
BattleUnitDefense queen_hand_small_defence = {{0, 0, 0, 0, 0}};

/**
 * Damage modifiers of the Shadow Queen's small hand per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
BattleUnitDefenseAttr queen_hand_small_defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
/**
 * Demo values of the status vulnerability of the Shadow Queen's small hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Defense Down,
 * Allergic.
 */
StatusVulnerability queen_hand_small_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 30, 30, 0, 0, 0, 0, 0, 0, 0};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Shadow Queen's small hand:
 * percent chance that each status takes hold (100 is normal);
 * immune to Poison, Electrified, Frozen, Huge, Tiny, Attack Up, Attack Down, Defense Up, Fright, Gale Force,
 * Fast, Slow, Dodgy, Invisible, Instant KO; strongly resistant to Sleep, Stop, Dizzy, Confuse, Allergic.
 */
StatusVulnerability queen_hand_small_regist = {30, 30, 30, 0, 30, 0, 100, 0, 0, 0, 0, 0, 0, 80, 30, 0, 0, 0, 0, 0, 0, 0};
#endif

/**
 * Pose table of the Shadow Queen's small hand: animation names for each pose type (idle, walk, hurt, attack
 * and so on).
 */
PoseTableEntry queen_hand_small_pose_table[] = {
    {28, "KRT_S_1"},
    {29, "KRT_S_1"},
    {30, "KRT_S_1"},
    {31, "KRT_S_1"},
    {39, "KRT_S_1"},
    {56, "KRT_S_1"},
    {57, "KRT_S_1"},
    {BTL_POSE_STAY_DEFAULT, "KRT_S_1"},
};

/**
 * Data table of the Shadow Queen's small hand: event scripts
 * and values the battle looks up by tag (damage reactions, dodge, first strike and so on).
 */
BattleDataEntry queen_hand_small_data_table[] = {
#if VERSION <= VERSION_DEMO_US
    {50, queen_hand_small_dead_event},
#else
    {49, queen_hand_small_dead_event},
#endif
    {0, NULL},
};

/** Part of the Shadow Queen's small hand: its one body part with hit box, defence tables and pose table. */
BattleUnitKindPart queen_hand_small_parts[] = {
    {1, "btl_un_shadow_hand_small", "c_b_hand", 0.0f, 0.0f, 0.0f, 70.0f, 18.0f, 0.0f, 70.0f, 18.0f, 0.0f, 188, 40, 255, &queen_hand_small_defence, &queen_hand_small_defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_NO_TRANSLUCENT_POSE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW, 0, queen_hand_small_pose_table},
};

/** Setup used to spawn the Shadow Queen: unit kind, alliance, position and turn phase. */
BattleUnitSetup entry_shadow_queen = {
    &unit_boss_shadow_queen, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {75.0f, 0.0f, 0.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Setup used to spawn the Shadow Queen's first big hand: unit kind, alliance, position and turn phase. */
BattleUnitSetup entry_shadow_hand_1 = {
    &unit_boss_shadow_hand_1, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {15.0f, 0.0f, -50.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Setup used to spawn the Shadow Queen's second big hand: unit kind, alliance, position and turn phase. */
BattleUnitSetup entry_shadow_hand_2 = {
    &unit_boss_shadow_hand_2, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {160.0f, 0.0f, 50.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Setup used to spawn the Shadow Queen's small hand: unit kind, alliance, position and turn phase. */
BattleUnitSetup entry_shadow_hand_small = {
    &unit_boss_shadow_hand_small, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {95.0f, 0.0f, 0.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Event script: init of the Shadow Queen (possessing Peach), the first phase of the final fight:
 * spawns the Shadow Queen unit that hides behind her, connects the queen's head and hand parts to her pose,
 * starts the hand swarm, and plays the idle animation.
 */
EVT_BEGIN(peach_init_event)
    SET_VALUE(GW(8), -1)
    SET_VALUE(GW(9), -1)
    SET_VALUE(GW(10), -1)
    SET_VALUE(GW(14), 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 0)
    ELSE
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_queen), 0)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, 0, -1000, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_NO_HP_GAUGE | UNIT_ATTR_IGNORE_FOR_CLEAR)
        CALL(btlevtcmd_SetMaxMoveCount, BTL_UNIT_SELF, 0)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    SET_VALUE(GW(13), LW(0))
    BEGIN_INLINE_EVENT
        CALL(shadow_queen_connect)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(peach_talk_synchro_shadow_head_evt)
    END_INLINE_EVENT
    CALL(btlevtcmd_SetPartsBaseScale, BTL_UNIT_SELF, 7, FLOAT(-1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_SetPartsBaseRotate, BTL_UNIT_SELF, 6, 0, 315, 0)
    CALL(btlevtcmd_SetPartsBaseRotate, BTL_UNIT_SELF, 7, 0, 315, 0)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 6, 15, 0, -50)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 7, 160, 0, 50)
    SPAWN_EVENT(shadow_queen_1000)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(360.0f))
        LOOP(0)
            CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, FLOAT(0.0f), LW(0), FLOAT(3.6992188f))
            SUBTRACT_FLOAT(LW(0), FLOAT(0.71972656f))
            IF_FLOAT_LESS(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRT_S_1"))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(peach_wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(peach_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(peach_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(peach_damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(peach_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Event script: entry scene of the Shadow Queen (possessing Peach): hides the status window, she speaks
 * (stg8_las_140_02), the partner answers (stg8_las_141), and (JP and later) the break slot is kept off a
 * Poison Mushroom BINGO.
 */
EVT_BEGIN(peach_entry_event)
    WAIT_MS(2000)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 83, 69, 332, 83, 46, 0, 30, 11)
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_140_02"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_moveto, 0, -122, 69, 332, -122, 46, 0, 15, 11)
    WAIT_MS(550)
    CALL(evt_msg_print_battle_party, STRING("stg8_las_141"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    CALL(queen_break_slot_flag2_on)
#endif
    RETURN
EVT_END()

/** Damage event of the Shadow Queen (possessing Peach): the default damage handling. */
EVT_BEGIN(peach_damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
#endif
    RETURN
EVT_END()

/**
 * Event script: the change from the Shadow Queen (possessing Peach) into her true form, played when Peach's
 * HP is used up.
 * The queen's mist and queen effect appear, her head, body and hand parts rise,
 * two big hands (shadow_hand_1/2) are spawned, and the whole unit group turns invulnerable (queen_muteki
 * defence, defence attributes and status table) while she speaks (stg8_las_141_01..03).
 * The queen's phase, attack, damage and wait events replace Peach's.
 */
EVT_BEGIN(peach_change_evt)
    // The status window is hidden and the camera moves in on the Shadow Queen (possessing Peach).
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 83, 69, 332, 83, 46, 0, 30, 11)
    WAIT_MS(800)
    // Speaking through Peach, the queen admits that Mario is not as weak as he looks.
    CALL(evt_msg_print, 2, STRING("stg8_las_141_01"), 0, BTL_UNIT_SELF)
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_L_2"))
    WAIT_MS(200)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KRT_T_3"))
    // She finds this body unfamiliar and says she will show her true form.
    CALL(evt_msg_print, 2, STRING("stg8_las_141_02"), 0, BTL_UNIT_SELF)
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 500)
    END_INLINE_EVENT
    CALL(evt_btl_camera_set_moveto, 0, 83, 125, 565, 83, 86, 0, 30, 11)
    WAIT_MS(400)
    // All statuses are cleared and her mist and queen effect appear.
    CALL(btlevtcmd_ClearAllStatus, BTL_UNIT_SELF)
    WAIT_MS(400)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_q"), STRING("mist2"), 0, LW(0), 15, LW(2), 100, 0, -1, 0, 0, 0, 0, 0)
    ADD(LW(2), 30)
    CALL(evt_eff, STRING("m_q2"), STRING("queen"), 0, LW(0), 0, LW(2), FLOAT(1.0f), 330, 0, 0, 0, 0, 0, 0)
    CALL(eff_queen_set_alpha_evt, 90)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_QWEN_APPEAR2"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), 0, LW(2))
        // Her head, body and hand parts rise out of the mist.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_O_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRT_S_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRT_S_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRT_O_2"))
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 0)
        LOOP(63)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, LW(0))
            ADD(LW(0), 4)
            WAIT_MS(50)
        END_LOOP
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 255)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 255)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 255)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, 255)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(2000)
        // Two big hands appear at her sides.
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_1), 0)
        SET_VALUE(GW(8), LW(0))
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_2), 0)
        SET_VALUE(GW(9), LW(0))
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT | PSND_CH(1), 2000)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_FLOAT_VALUE(LW(1), LW(1))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    LOOP(100)
        ADD_FLOAT(LW(1), FLOAT(0.4091797f))
        ADD_FLOAT(LW(3), FLOAT(0.4091797f))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_FLOAT_VALUE(LW(4), LW(1))
        SUBTRACT_FLOAT(LW(4), LW(3))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(4), LW(2))
        WAIT_MS(20)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_L_1"))
    WAIT_MS(800)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_T_1"))
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
    CALL(evt_snd_bgmon, PSND_FADE_OUT | PSND_CH(1), STRING("BGM_BOSS_STG8_LAST_BOSS1"))
    WAIT_MS(800)
    // In this form she says Mario's attacks are like a child's.
    CALL(evt_msg_print, 2, STRING("stg8_las_141_03"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsHomePos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence))
    CALL(btlevtcmd_SetPartsDefenceTable, GW(8), 1, PTR(&queen_muteki_defence))
    CALL(btlevtcmd_SetPartsDefenceTable, GW(9), 1, PTR(&queen_muteki_defence))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence_attr))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, GW(8), 1, PTR(&queen_muteki_defence_attr))
    CALL(btlevtcmd_SetPartsDefenceAttrTable, GW(9), 1, PTR(&queen_muteki_defence_attr))
    // The whole group becomes invulnerable while she speaks.
    CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&queen_muteki_regist))
    CALL(btlevtcmd_SetRegistStatus, GW(8), PTR(&queen_muteki_regist))
    CALL(btlevtcmd_SetRegistStatus, GW(9), PTR(&queen_muteki_regist))
    CALL(btlevtcmd_OffPartsAttribute, GW(8), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffPartsAttribute, GW(9), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffAttribute, GW(8), UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_OffAttribute, GW(9), UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 34, -15, 30)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 34, -15, 30)
    CALL(btlevtcmd_SetBintaHitOffset, BTL_UNIT_SELF, 25, 0, 0)
    CALL(btlevtcmd_SetKissHitOffset, BTL_UNIT_SELF, 50, 40, 0)
    // The queen's own phase, attack, damage and wait events replace Peach's.
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(queen_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(queen_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(queen_damage_event))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(queen_wait_event))
    SET_VALUE(GW(11), 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_HP_MSG, 0)
    SET_VALUE(GW(10), -1)
    SET_VALUE(GW(12), 0)
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_US
        CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, 90)
#else
        CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, 112)
#endif
    END_IF
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
    SET_VALUE(GSW(GSW_SHADOW_QUEEN_HP), LW(0))
    // The camera returns to the battle view.
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Phase event of the Shadow Queen (possessing Peach): before the enemy phase checks her state in work[0] and
 * runs peach_change_evt when the transformation is due.
 */
EVT_BEGIN(peach_phase_event)
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 4)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
    IF_INT_NOT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
#if VERSION >= VERSION_US
    IF_INT_LESS(LW(0), 90)
#else
    IF_INT_LESS(LW(0), 112)
#endif
        CALL_CHILD(peach_change_evt)
        CALL(btlevtcmd_reset_turn)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Dead event of the Shadow Queen (possessing Peach): instead of dying she runs peach_change_evt and changes
 * into her true form.
 */
EVT_BEGIN(peach_dead_event)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL_CHILD(peach_change_evt)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    CALL(btlevtcmd_reset_turn)
    RETURN
EVT_END()

/**
 * Event script: the possessed Peach's black thunder attack (weapon_peach_black_thunder_attack) on a sampled
 * target: a pose and a thunder strike with the damage check.
 */
EVT_BEGIN(peack_attack_black_thunder)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_thunder_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    WAIT_MS(500)
    WAIT_MS(700)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(queen_thunder, LW(0), LW(1), LW(2))
    WAIT_MS(80)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_thunder_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    GOTO(95)
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_thunder_attack))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_thunder_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: the possessed Peach's black energy move (weapon_peach_black_energy_attack):
 * she charges (charge effect, KRT_A_2) and the attack is paid for and checked against herself, a self-buff.
 */
EVT_BEGIN(peack_attack_black_energy)
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    WAIT_MS(200)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_2"))
    WAIT_MS(750)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 1000)
    END_INLINE_EVENT
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
    ADD(LW(1), LW(5))
    ADD(LW(1), -15)
    CALL(evt_eff, STRING(""), STRING("charge"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 60, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_DARK_POWER1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_energy_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, PTR(&weapon_peach_black_energy_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    RETURN
EVT_END()

/**
 * Event script: the possessed Peach's dark drag attack (weapon_peach_dark_drag_attack):
 * the swarm of small hands rises (peach_hand1000_dark_drag_1_evt) and drags at the target through mist,
 * with three damage checks and a final hit (weapon_peach_dark_drag_last_attack).
 */
EVT_BEGIN(peack_attack_dark_drag)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_dark_drag_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_dark_drag_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_dark_drag_attack))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_QWEN_APPEAR1"), LW(0), LW(1), LW(2), LW(10))
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 7, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 0)
        LOOP(6)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, LW(0))
            ADD(LW(0), 16)
            WAIT_MS(5)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    // The swarm of small hands rises and drags at the target through the mist.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_2"))
    WAIT_MS(500)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(500)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_APPEAR1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        CALL(peach_hand1000_dark_drag_1_evt)
    END_INLINE_EVENT
    CALL(evt_eff, STRING("m_h_s1"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    WAIT_MS(1250)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    WAIT_MS(2250)
    CALL(evt_eff_softdelete, STRING("m_h_s1"))
    CALL(evt_eff_softdelete, STRING("m_h_s2"))
    CALL(evt_eff_softdelete, STRING("m_h_s3"))
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_dark_drag_attack))
    CALL(battle_evt_majo_disp_off, LW(3), LW(4), 0, 0)
    // The hands drag the target out of sight.
    CALL(btlevtcmd_SetScale, LW(3), 0, 0, 0)
    CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
    CALL(evt_eff_softdelete, STRING("m_h_s1"))
    CALL(evt_eff_softdelete, STRING("m_h_s2"))
    CALL(evt_eff_softdelete, STRING("m_h_s3"))
    CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
    // The target is dropped back where it stood.
    CALL(btlevtcmd_SetScale, LW(3), 1, 1, 1)
    CALL(battle_evt_majo_disp_on, LW(3), LW(4), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_last_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_MS(750)
    // The mist closes in around her again.
    LABEL(95)
    LABEL(98)
    CALL(evt_snd_sfxoff, LW(10))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 100)
        LOOP(6)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, LW(0))
            ADD(LW(0), -16)
            WAIT_MS(5)
        END_LOOP
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 7, PART_ATTR_HIDDEN)
    END_INLINE_EVENT
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Event script: the possessed Peach's drain attack (weapon_peach_drain_attack):
 * a hand grabs the target and she recovers HP equal to the damage dealt, with the recovery effect.
 */
EVT_BEGIN(peack_attack_drain)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_drain_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_drain_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_drain_attack))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_QWEN_APPEAR1"), LW(0), LW(1), LW(2), LW(10))
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, 0)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 7, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 0)
        LOOP(6)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, LW(0))
            ADD(LW(0), 16)
            WAIT_MS(5)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_2"))
    WAIT_MS(500)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(500)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // A big hand rises out of the floor beside her.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRT_S_1"))
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_h_1"), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    ADD(LW(0), 20)
    SET_VALUE(LW(1), 0)
    ADD(LW(2), -30)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2))
    SET_VALUE(LW(0), 0)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, LW(0))
        ADD(LW(0), 16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, 255)
    WAIT_MS(500)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_DRAIN1"), LW(0), LW(1), LW(2), 0)
    // The hand seizes the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRT_A2_1"))
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
    END_INLINE_EVENT
    WAIT_MS(2000)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_drain_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_drain_attack))
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_drain_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_drain_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_GetHpDamage, LW(3), LW(0))
    // She recovers HP equal to the damage dealt, with the recovery effect.
    CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, LW(0))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(8))
    ADD(LW(6), LW(8))
    ADD(LW(7), 30)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(5), LW(6), LW(7), LW(0), 0, 0, 0, 0, 0, 0, 0)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_eff_softdelete, STRING("m_h_1"))
    CALL(evt_snd_sfxoff, LW(10))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 100)
        LOOP(6)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 7, LW(0))
            ADD(LW(0), -16)
            WAIT_MS(5)
        END_LOOP
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 7, PART_ATTR_HIDDEN)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 255)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 6, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 6, 15, 0, -50)
    // The attack is over; back to waiting.
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack event of the Shadow Queen (possessing Peach): picks one of her attacks with a random draw and runs
 * it.
 */
EVT_BEGIN(peach_attack_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 1)
        CALL_CHILD(peack_attack_black_thunder)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 2)
        CALL_CHILD(peack_attack_black_energy)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 3)
        CALL_CHILD(peack_attack_dark_drag)
        CASE_EQUAL(3)
        CALL(btlevtcmd_DrawLots, LW(0), 4, 100, 30, 30, 30)
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DEFENSE_UP, LW(1))
        IF_INT_EQUAL(LW(1), 1)
            IF_INT_EQUAL(LW(0), 1)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL_CHILD(peack_attack_black_thunder)
            CASE_EQUAL(1)
            CALL_CHILD(peack_attack_black_energy)
            CASE_EQUAL(2)
            CALL_CHILD(peack_attack_drain)
            CASE_EQUAL(3)
            CALL_CHILD(peack_attack_dark_drag)
        END_SWITCH
    END_SWITCH
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Wait event of the Shadow Queen (possessing Peach): plays her idle pose from the pose table. */
EVT_BEGIN(peach_wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Init event of the Shadow Queen unit (spawned behind Peach):
 * sets the shared state in GW (GW(11) form, GW(12) attack counter, GW(8)/GW(9) the two big hands,
 * GW(10) the small hand, GW(13) the queen), spawns the two big hands and starts the queen's mist.
 */
EVT_BEGIN(queen_init_event)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(queen_wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(queen_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(queen_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(queen_damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(queen_entry_event))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_NO_BACKFACE_FLIP)
    SET_VALUE(GW(11), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, 3)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_HP_MSG, 0)
    SET_VALUE(GW(10), -1)
    SET_VALUE(GW(12), 300)
    SET_VALUE(GW(18), 0)
    CALL(queen_kankyaku_delete_evt)
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_1), 0)
    SET_VALUE(GW(8), LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_2), 0)
    SET_VALUE(GW(9), LW(0))
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    SET_VALUE(GW(13), LW(0))
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(360.0f))
        LOOP(0)
            CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 2, FLOAT(0.0f), LW(0), FLOAT(3.6992188f))
            SUBTRACT_FLOAT(LW(0), FLOAT(0.71972656f))
            IF_FLOAT_LESS(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        CALL(shadow_queen_connect)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(peach_talk_synchro_shadow_head_evt)
    END_INLINE_EVENT
    SPAWN_EVENT(shadow_queen_1000)
    CALL(btlevtcmd_OffPartsAttribute, GW(8), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffPartsAttribute, GW(9), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffAttribute, GW(8), UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_OffAttribute, GW(9), UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 34, -15, 30)
    CALL(btlevtcmd_SetHitCursorOffset, BTL_UNIT_SELF, 1, 34, -15, 30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRT_S_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_q"), STRING("mist2"), 0, LW(0), 15, LW(2), 100, 0, -1, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Event script: the Shadow Queen's first attack message (stg8_las_142); sets the attack counter GW(12) to 100. */
EVT_BEGIN(queen_first_attack_message_evt)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_142"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, 1)
    SET_VALUE(GW(12), 100)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Event script: the Shadow Queen's second attack message (stg8_las_143); sets the attack counter GW(12) to 200. */
EVT_BEGIN(queen_next_attack_message_evt)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_143"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, 2)
    SET_VALUE(GW(12), 200)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's last attack message from the partner (stg8_las_145);
 * sets the attack counter GW(12) to 300.
 */
EVT_BEGIN(queen_last_attack_message_evt)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        RETURN
    END_IF
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_moveto, 0, -113, 69, 332, -113, 46, 0, 15, 11)
    WAIT_MS(550)
    CALL(evt_msg_print_battle_party, STRING("stg8_las_145"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_MSG, 3)
    SET_VALUE(GW(12), 300)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_InterruptStop, 1)
    RETURN
EVT_END()

/**
 * Event script: the queen swaps her two big hands for the small hand swarm:
 * kills the big hands, spawns entry_shadow_hand_small and sets the form GW(11) to 2.
 */
EVT_BEGIN(queen_change_hand_small_evt)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        RETURN
    END_IF
#if VERSION >= VERSION_JP
    SET_VALUE(GF(1), 1)
#endif
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(8), -1)
#if VERSION >= VERSION_JP
            SET_VALUE(GF(1), 0)
#endif
            CALL_CHILD(queen_hand_1_dead_event)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(9), -1)
#if VERSION >= VERSION_JP
            SET_VALUE(GF(1), 0)
#endif
            CALL_CHILD(queen_hand_2_dead_event)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(300)
    SET_VALUE(GF(0), 0)
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_small), 0)
    SET_VALUE(GW(10), LW(0))
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#if VERSION >= VERSION_JP
    LOOP(0)
        IF_INT_EQUAL(GF(1), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#endif
    WAIT_MS(1000)
    SET_VALUE(GW(11), 2)
    RETURN
EVT_END()

/**
 * Event script: the queen swaps the small hand swarm for her two big hands again:
 * kills the small hand, respawns the big hands and sets the form GW(11) to 1.
 */
EVT_BEGIN(queen_change_hand_big_evt)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        RETURN
    END_IF
#if VERSION >= VERSION_JP
    SET_VALUE(GF(1), 1)
#endif
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(10), -1)
#if VERSION >= VERSION_JP
            SET_VALUE(GF(1), 0)
#endif
            CALL_CHILD(queen_hand_small_dead_event)
        END_IF
    END_INLINE_EVENT
    WAIT_MS(300)
    SET_VALUE(GF(0), 0)
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_1), 0)
    SET_VALUE(GW(8), LW(0))
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_2), 0)
    SET_VALUE(GW(9), LW(0))
    CALL(btlevtcmd_OffPartsAttribute, GW(8), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffPartsAttribute, GW(9), 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffAttribute, GW(8), UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_OffAttribute, GW(9), UNIT_ATTR_NO_HP_GAUGE)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#if VERSION >= VERSION_JP
    LOOP(0)
        IF_INT_EQUAL(GF(1), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#endif
    WAIT_MS(1000)
    SET_VALUE(GW(11), 1)
    RETURN
EVT_END()

/** Event script: respawns whichever big hand (GW(8) or GW(9)) has been destroyed. */
EVT_BEGIN(queen_hand_big_life_check_evt)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        RETURN
    END_IF
#if VERSION <= VERSION_DEMO_US
    IF_INT_NOT_EQUAL(GW(8), -1)
        RETURN
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        RETURN
    END_IF
#else
    SET_VALUE(GF(0), 1)
    IF_INT_EQUAL(GW(8), -1)
#endif
        SET_VALUE(GF(0), 0)
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_1), 0)
        SET_VALUE(GW(8), LW(0))
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_OffPartsAttribute, GW(8), 1, PART_ATTR_NOT_TARGETABLE)
        CALL(btlevtcmd_OffAttribute, GW(8), UNIT_ATTR_NO_HP_GAUGE)
    END_IF
    IF_INT_EQUAL(GW(9), -1)
        SET_VALUE(GF(0), 0)
#endif
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_2), 0)
        SET_VALUE(GW(9), LW(0))
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_OffPartsAttribute, GW(8), 1, PART_ATTR_NOT_TARGETABLE)
#endif
        CALL(btlevtcmd_OffPartsAttribute, GW(9), 1, PART_ATTR_NOT_TARGETABLE)
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_OffAttribute, GW(8), UNIT_ATTR_NO_HP_GAUGE)
#endif
        CALL(btlevtcmd_OffAttribute, GW(9), UNIT_ATTR_NO_HP_GAUGE)
#if VERSION >= VERSION_JP
    END_IF
#endif
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    RETURN
EVT_END()

/** Event script: respawns the small hand unit (GW(10)) if it has been destroyed. */
EVT_BEGIN(queen_hand_small_life_check_evt)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        RETURN
    END_IF
    IF_INT_NOT_EQUAL(GW(10), -1)
        RETURN
    END_IF
    SET_VALUE(GF(0), 0)
    CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_small), 0)
    SET_VALUE(GW(10), LW(0))
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1000)
    RETURN
EVT_END()

/**
 * Event script: the queen's HP drain scene.
 * She says stg8_las_144, the swarm of hands rises (queen_hp_drain_1..4) and drags the audience under the floor,
 * the queen heals to full HP (RecoverHp with her maximum HP) and speaks again (stg8_las_142_01);
 * then the form is set to 2.
 */
EVT_BEGIN(queen_hp_drain_evt)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    // The queen calls Mario a troublesome little pest.
    CALL(evt_msg_print, 2, STRING("stg8_las_144"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_mode, 0, 0)
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(8), -1)
            // The big hand leaves the stage.
            CALL_CHILD(queen_hand_1_dead_event)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(9), -1)
            CALL_CHILD(queen_hand_2_dead_event)
        END_IF
    END_INLINE_EVENT
    IF_INT_EQUAL(GW(10), -1)
        // A swarm of small hands appears.
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_small), 0)
        SET_VALUE(GW(10), LW(0))
        WAIT_MS(1000)
    END_IF
    CALL(evt_eff_softdelete, STRING("m_h_1"))
    CALL(evt_eff_softdelete, STRING("m_h_2"))
    CALL(evt_eff_softdelete, STRING("m_h_3"))
    WAIT_MS(1000)
    CALL(queen_get_aud_num, LW(10))
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_GOOUT1"), 0)
    CALL(queen_hp_drain_1_evt)
    CALL(evt_eff, STRING("m_h_s1_"), STRING("mist2"), 0, 0, -40, 0, 400, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2_"), STRING("mist2"), 0, 0, -25, 0, 400, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3_"), STRING("mist2"), 0, 0, -35, 0, 400, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s4_"), STRING("mist2"), 0, 0, -15, 0, 400, 0, -1, 0, 0, 0, 0, 0)
    // The camera shakes hard as the hands drag the audience under the floor.
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 240, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWENH_HAND_APPEAR2"), 0)
    CALL(evt_snd_sfxon, STRING("SFX_AUDIENCE_PANIC_SCREAM1"), LW(11))
    CALL(queen_hp_drain_2_evt)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(queen_hp_drain_3_evt)
    END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
    CALL(queen_hp_drain_4_evt)
#else
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), 127)
        LOOP(63)
            SUBTRACT(LW(0), 2)
            CALL(evt_snd_sfx_vol, LW(11), LW(0))
            WAIT_MS(31)
        END_LOOP
#endif
        CALL(evt_snd_sfxoff, LW(11))
#if VERSION >= VERSION_JP
    END_INLINE_EVENT
    CALL(queen_hp_drain_4_evt)
#endif
#if VERSION <= VERSION_DEMO_US
    IF_INT_GREATER(LW(10), 99)
        SET_VALUE(LW(10), 99)
#else
    IF_INT_GREATER(LW(10), 7)
        SET_VALUE(LW(10), 7)
#endif
    END_IF
    IF_INT_GREATER(LW(10), 99)
        SET_VALUE(LW(10), 99)
    END_IF
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(10))
    // She recovers to full HP, with the recovery effect.
    CALL(btlevtcmd_RecoverHp, GW(13), 1, LW(10))
    CALL(btlevtcmd_GetPos, GW(13), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetHeight, GW(13), LW(8))
    ADD(LW(6), LW(8))
    ADD(LW(7), 30)
    CALL(evt_eff, STRING(""), STRING("recovery"), 4, LW(5), LW(6), LW(7), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1500)
    CALL(evt_batstage_return_aud_dark_base, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_APPEAR1_2"), 0)
    CALL(queen_hp_drain_5_evt)
    CALL(evt_eff_softdelete, STRING("m_h_s1_"))
    CALL(evt_eff_softdelete, STRING("m_h_s2_"))
    CALL(evt_eff_softdelete, STRING("m_h_s3_"))
    CALL(evt_eff_softdelete, STRING("m_h_s4_"))
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    // She says she has recovered and will punish Mario for resisting.
    CALL(evt_msg_print, 2, STRING("stg8_las_142_01"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    SET_VALUE(GW(11), 2)
    CALL(btlevtcmd_reset_turn)
    RETURN
EVT_END()

/**
 * Event script: the HP drain scene when it fails to take hold:
 * she says stg8_las_144 and the form is set to 2 without healing.
 */
EVT_BEGIN(queen_hp_drain_evt_miss)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_144"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    SET_VALUE(GW(11), 2)
    CALL(btlevtcmd_reset_turn)
    RETURN
EVT_END()

/**
 * Event script: the queen's reaction the first time she is damaged (stg8_las_163,
 * the partner's stg8_las_164 and stg8_las_165).
 */
EVT_BEGIN(queen_first_damage_evt)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_163"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -113, 69, 332, -113, 46, 0, 30, 11)
    WAIT_MS(800)
    CALL(evt_msg_print_battle_party, STRING("stg8_las_164"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    WAIT_MS(300)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 1, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 1, 11)
#endif
    WAIT_MS(350)
    CALL(evt_msg_print, 2, STRING("stg8_las_165"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()

/** Event script: the queen's line when her HP falls to the second threshold (stg8_las_166). */
EVT_BEGIN(queen_2_hp_msg_evt)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_166"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()

/** Event script: the queen's line when her HP falls to the fourth threshold (stg8_las_167). */
EVT_BEGIN(queen_4_hp_msg_evt)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 30, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
#endif
    WAIT_MS(800)
    CALL(evt_msg_print, 2, STRING("stg8_las_167"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
EVT_END()

/** Event script: the queen's line when she is about to die (stg8_las_168). */
EVT_BEGIN(queen_dead_hp_msg_evt)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
#else
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 30, 11)
    WAIT_MS(800)
    CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KRT_D_1"))
    CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("KRT_D_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRT_S_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_D_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRT_S_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_D_1"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_D_1"))
    END_IF
#endif
    CALL(evt_msg_print, 2, STRING("stg8_las_168"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_StatusWindowOnOff, 1)
#else
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    CALL(evt_btl_camera_set_mode, 0, 0)
#endif
    WAIT_MS(1000)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
#endif
    RETURN
EVT_END()

/**
 * Phase event of the Shadow Queen: updates her HP-stage counter (work[2] of the queen unit),
 * runs the story messages in order as her HP drops, and decides when the HP drain or the hands swap happens;
 * at the enemy phase it advances the form.
 */
EVT_BEGIN(queen_phase_event)
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    IF_INT_NOT_EQUAL(GW(11), 0)
        IF_INT_EQUAL(GW(18), 1)
            SET_VALUE(GW(18), 2)
            // Messages for the queen's first damage and her HP stages.
            CALL_CHILD(queen_first_damage_evt)
        END_IF
        CALL(btlevtcmd_GetMaxHp, GW(13), LW(0))
        CALL(btlevtcmd_GetHp, GW(13), LW(1))
        DIVIDE(LW(0), 4)
        IF_INT_LESS(LW(1), LW(0))
            CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_HP_MSG, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 1)
                CALL(btlevtcmd_SetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_HP_MSG, 2)
                CALL_CHILD(queen_4_hp_msg_evt)
            END_IF
        END_IF
        CALL(btlevtcmd_GetMaxHp, GW(13), LW(0))
        CALL(btlevtcmd_GetHp, GW(13), LW(1))
        DIVIDE(LW(0), 2)
        IF_INT_LESS(LW(1), LW(0))
            CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_HP_MSG, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                CALL(btlevtcmd_SetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_HP_MSG, 1)
                CALL_CHILD(queen_2_hp_msg_evt)
            END_IF
        END_IF
    END_IF
    SWITCH(GW(11))
        CASE_EQUAL(0)
        IF_INT_GREATER(GW(12), 200)
            CALL(queen_get_aud_num, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 1)
                SET_VALUE(GW(11), 3)
                SET_VALUE(GW(14), 1)
                // At the right HP stage she drains the HP of the audience.
                CALL_CHILD(queen_hp_drain_evt)
            ELSE
                CALL_CHILD(queen_hp_drain_evt_miss)
            END_IF
            // Her attack messages: the last attack, the next attack and the first attack.
            CALL_CHILD(queen_last_attack_message_evt)
            BREAK_SWITCH
        END_IF
        IF_INT_GREATER(GW(12), 100)
            CALL_CHILD(queen_next_attack_message_evt)
            BREAK_SWITCH
        END_IF
        IF_INT_GREATER(GW(12), 0)
            CALL_CHILD(queen_first_attack_message_evt)
            BREAK_SWITCH
        END_IF
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_EQUAL(LW(0), 1)
            // Hand swaps: when the big hands are gone small hands take over, and the other way round.
            CALL_CHILD(queen_hand_big_life_check_evt)
        END_IF
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_sub_random, 100, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 50)
                CALL_CHILD(queen_change_hand_small_evt)
                BREAK_SWITCH
            END_IF
        END_IF
        CASE_EQUAL(2)
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(queen_hand_small_life_check_evt)
        END_IF
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_AFTER_PLAYER)
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_sub_random, 100, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 50)
                CALL_CHILD(queen_change_hand_big_evt)
                BREAK_SWITCH
            END_IF
        END_IF
        CASE_EQUAL(3)
        CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_ENEMY)
        IF_INT_EQUAL(LW(0), 1)
            SET_VALUE(GW(11), 2)
        END_IF
    END_SWITCH
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's black thunder attack (weapon_peach_black_thunder_attack):
 * calls lightning down on the target with queen_thunder and checks the damage.
 */
EVT_BEGIN(queen_attack_black_thunder)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_thunder_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -33)
    ADD(LW(1), 82)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 4, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_EYE_SHINE1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_2"))
    WAIT_MS(700)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(queen_thunder, LW(0), LW(1), LW(2))
    WAIT_MS(80)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_thunder_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    GOTO(95)
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_thunder_attack))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_thunder_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_thunder_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    LABEL(99)
    RETURN
EVT_END()

/** Event script: the Shadow Queen's dark charge (weapon_peach_dark_charge_attack): a self-targeted charge move. */
EVT_BEGIN(queen_attack_charge)
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_dark_charge_attack))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_2"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_A_3"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_A_3"))
    END_IF
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 1000)
    END_INLINE_EVENT
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
    ADD(LW(1), LW(5))
    ADD(LW(2), 30)
    CALL(evt_eff, STRING(""), STRING("charge"), 2, LW(0), LW(1), LW(2), FLOAT(3.0f), 60, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DARK_POWER1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1000)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_S_1"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_S_1"))
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, PTR(&weapon_peach_dark_charge_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's black wave attack (weapon_peach_black_wave_attack):
 * a wave of dark energy over the party; kills the small hand first if it is out.
 */
EVT_BEGIN(queen_attack_black_wave)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_wave_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_wave_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_wave_attack))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    IF_INT_NOT_EQUAL(GW(10), -1)
        // If the small hand is out, it is removed first.
        CALL_CHILD(queen_hand_small_dead_event)
        // The big hand rises beside the queen.
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_1), 0)
        SET_VALUE(GW(8), LW(0))
        CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_shadow_hand_2), 0)
        SET_VALUE(GW(9), LW(0))
        WAIT_MS(1500)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_L_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_T_3"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        // She and her hand rear back, gathering dark energy.
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_A_3"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_A_3"))
    END_IF
    WAIT_MS(1000)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_3"))
    WAIT_MS(200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -33)
    ADD(LW(1), 82)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 4, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_EYE_SHINE1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_q2"), STRING("queen2"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DARK_WAVE1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1500)
        LOOP(3)
            CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DARK_WAVE2"), LW(0), LW(1), LW(2), 0)
            WAIT_MS(1000)
        END_LOOP
        WAIT_MS(500)
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DARK_WAVE3"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(500)
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DARK_WAVE3"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    WAIT_MS(1500)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 1000)
    END_INLINE_EVENT
    // The wave of dark energy sweeps over the party and shakes the camera.
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 120, 0)
    WAIT_MS(3500)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 120, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_2"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_A_4"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_A_4"))
    END_IF
    WAIT_MS(1500)
    // She and her hands settle back.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_S_1"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_S_1"))
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_wave_attack))
#if VERSION >= VERSION_JP
    SET_VALUE(LF(0), 0)
#endif
    LABEL(0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_wave_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        GOTO(95)
        CASE_END
    END_SWITCH
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    IF_INT_EQUAL(LF(0), 0)
#endif
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_wave_attack))
#if VERSION >= VERSION_JP
        SET_VALUE(LF(0), 1)
    END_IF
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_wave_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    IF_INT_NOT_EQUAL(GW(11), 0)
        SET_VALUE(GW(11), 1)
    END_IF
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's black energy move (weapon_peach_black_energy_attack),
 * a self-targeted charge like the one she uses while possessing Peach.
 */
EVT_BEGIN(queen_attack_black_energy)
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_2"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_A_3"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_A_3"))
    END_IF
    WAIT_MS(750)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    IF_INT_NOT_EQUAL(GW(8), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(8), 1, STRING("KRT_S_1"))
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        CALL(btlevtcmd_AnimeChangePose, GW(9), 1, STRING("KRT_S_1"))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 1000)
    END_INLINE_EVENT
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
    ADD(LW(1), LW(5))
    ADD(LW(1), -15)
    CALL(evt_eff, STRING(""), STRING("charge"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 60, 0, 0, 0, 0, 0, 0)
#if VERSION >= VERSION_JP
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_DARK_POWER1"), LW(0), LW(1), LW(2), 0)
#endif
    WAIT_MS(1000)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_energy_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, BTL_UNIT_SELF, 1, PTR(&weapon_peach_black_energy_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's first breath attack (weapon_peach_black_sigh_attack, "sigh") on a sampled
 * target.
 */
EVT_BEGIN(queen_attack_bress1)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_sigh_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_sigh_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_sigh_attack))
    // The queen leans in and takes a breath.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -33)
    ADD(LW(1), 82)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 4, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_EYE_SHINE1"), LW(0), LW(1), LW(2), 0)
    // She breathes a sigh out at the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_2"))
    CALL(evt_eff, STRING(""), STRING("toiki"), 0, 73, 112, 0, 180, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(2500)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH2"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_3"))
    WAIT_MS(80)
    // She settles back.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_sigh_attack))
#if VERSION >= VERSION_JP
    SET_VALUE(LF(0), 0)
#endif
    LABEL(0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_sigh_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        GOTO(95)
        CASE_END
    END_SWITCH
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    IF_INT_EQUAL(LF(0), 0)
#endif
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_sigh_attack))
#if VERSION >= VERSION_JP
        SET_VALUE(LF(0), 1)
    END_IF
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_sigh_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's second breath attack (weapon_peach_black_temptation_attack,
 * "temptation") on a sampled target.
 */
EVT_BEGIN(queen_attack_bress2)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_temptation_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_temptation_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_temptation_attack))
    // The queen leans in and takes a breath.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -33)
    ADD(LW(1), 82)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 4, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_EYE_SHINE1"), LW(0), LW(1), LW(2), 0)
    // She breathes out a tempting breath at the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_2"))
    CALL(evt_eff, STRING(""), STRING("toiki"), 1, 73, 112, 0, 180, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(2500)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH2"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_3"))
    WAIT_MS(80)
    // She settles back.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_temptation_attack))
#if VERSION >= VERSION_JP
    SET_VALUE(LF(0), 0)
#endif
    LABEL(0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_temptation_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        GOTO(95)
        CASE_END
    END_SWITCH
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    IF_INT_EQUAL(LF(0), 0)
#endif
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_temptation_attack))
#if VERSION >= VERSION_JP
        SET_VALUE(LF(0), 1)
    END_IF
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_temptation_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    RETURN
EVT_END()

/**
 * Event script: the Shadow Queen's third breath attack (weapon_peach_black_poison_attack, "poison") on a sampled
 * target.
 */
EVT_BEGIN(queen_attack_bress3)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_poison_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_poison_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_poison_attack))
    WAIT_MS(200)
    // The queen leans in and takes a breath.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(0), -33)
    ADD(LW(1), 82)
    CALL(evt_eff, STRING(""), STRING("toge_flush"), 4, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_EYE_SHINE1"), LW(0), LW(1), LW(2), 0)
    // She breathes out a poisonous breath at the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_2"))
    CALL(evt_eff, STRING(""), STRING("toiki"), 2, 73, 112, 0, 180, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(2500)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_BREATH2"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_A2_3"))
    WAIT_MS(80)
    // She settles back.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_S_1"))
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_poison_attack))
#if VERSION >= VERSION_JP
    SET_VALUE(LF(0), 0)
#endif
    LABEL(0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_poison_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
        GOTO(95)
        CASE_END
    END_SWITCH
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    IF_INT_EQUAL(LF(0), 0)
#endif
        // Deal the damage, reduced by the action command defence.
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_poison_attack))
#if VERSION >= VERSION_JP
        SET_VALUE(LF(0), 1)
    END_IF
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_poison_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(98)
    END_IF
    GOTO(0)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The attack is over; back to waiting.
    LABEL(99)
    RETURN
EVT_END()

/**
 * Attack event of the Shadow Queen: chooses her next attack with weighted draws (btlevtcmd_DrawLots) depending
 * on the current form and which stage she has reached (work[0]), then runs that attack script.
 */
EVT_BEGIN(queen_attack_event)
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 3)
            CALL_CHILD(queen_attack_black_thunder)
            CASE_EQUAL(1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 3)
            CALL_CHILD(queen_attack_black_energy)
            CASE_EQUAL(3)
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_DrawLots, LW(0), 4, 100, 30, 30, 30)
#else
            CALL(btlevtcmd_DrawLots, LW(0), 4, 100, 20, 30, 30)
#endif
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL_CHILD(queen_attack_black_thunder)
                CASE_EQUAL(1)
                CALL_CHILD(queen_attack_bress1)
                CASE_EQUAL(2)
                CALL_CHILD(queen_attack_bress2)
                CASE_EQUAL(3)
                CALL_CHILD(queen_attack_bress3)
            END_SWITCH
        END_SWITCH
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 1)
        CALL_CHILD(queen_attack_black_thunder)
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 2)
        CALL_CHILD(queen_attack_charge)
        CASE_EQUAL(2)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 3)
        CALL_CHILD(queen_attack_black_wave)
        CASE_EQUAL(3)
#if VERSION >= VERSION_US
        CALL(btlevtcmd_DrawLots, LW(0), 6, 100, 50, 60, 20, 30, 30)
#elif VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_DrawLots, LW(0), 6, 100, 50, 50, 30, 30, 30)
#else
        CALL(btlevtcmd_DrawLots, LW(0), 6, 100, 50, 30, 20, 30, 30)
#endif
        CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_DEFENSE_UP, LW(1))
        IF_INT_EQUAL(LW(1), 1)
            IF_INT_EQUAL(LW(0), 1)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL_CHILD(queen_attack_black_thunder)
            CASE_EQUAL(1)
            CALL_CHILD(queen_attack_black_energy)
            CASE_EQUAL(2)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOSS_BLACK_PEACH_ATTACK_STEP, 2)
            CALL_CHILD(queen_attack_charge)
            CASE_EQUAL(3)
            CALL_CHILD(queen_attack_bress1)
            CASE_EQUAL(4)
            CALL_CHILD(queen_attack_bress2)
            CASE_EQUAL(5)
            CALL_CHILD(queen_attack_bress3)
        END_SWITCH
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Shadow Queen: default damage handling. */
EVT_BEGIN(queen_damage_event)
    CALL(btlevtcmd_GetDamageCode, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 22)
        ADD(GW(12), 1)
        IF_INT_EQUAL(GW(18), 0)
            SET_VALUE(GW(18), 1)
        END_IF
        BEGIN_INLINE_EVENT
            LOOP(5)
                CALL(btlevtcmd_AddPartsPos, BTL_UNIT_SELF, 2, 2, 0, 0)
                WAIT_MS(70)
                CALL(btlevtcmd_AddPartsPos, BTL_UNIT_SELF, 2, -2, 0, 0)
                WAIT_MS(70)
            END_LOOP
        END_INLINE_EVENT
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
#endif
    RETURN
EVT_END()

/** Dead event of the Shadow Queen: removes whichever big or small hands are still alive and kills the queen unit. */
EVT_BEGIN(queen_dead_event)
    CALL(btlevtcmd_WaitAttackEnd)
    // Her last words play as her HP runs out.
    CALL_CHILD(queen_dead_hp_msg_evt)
    CALL(evt_eff_softdelete, STRING("m_q"))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_SetTalkPose, BTL_UNIT_SELF, STRING("KRT_S_1"))
        CALL(btlevtcmd_SetStayPose, BTL_UNIT_SELF, STRING("KRT_S_1"))
        // Her head, body and hands sink away as the mist fades out.
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
#endif
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRT_O_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRT_S_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRT_S_1"))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRT_O_2"))
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 254)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 254)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 254)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, 254)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 254)
        LOOP(63)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, LW(0))
            SUBTRACT(LW(0), 4)
#if VERSION <= VERSION_DEMO_US
            WAIT_MS(10)
#else
            WAIT_MS(50)
#endif
        END_LOOP
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 2, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 3, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 4, 0)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 5, 0)
        SET_VALUE(GF(0), 1)
#if VERSION >= VERSION_JP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_BPCH_DIE1"), LW(0), LW(1), LW(2), LW(10))
        CALL(evt_eff, STRING(""), STRING("mist"), 6, 80, 50, 20, 0, 1500, 0, 0, 0, 0, 0, 0)
        WAIT_MS(200)
        CALL(evt_eff, STRING(""), STRING("mist"), 6, 100, 30, 10, 0, 1500, 0, 0, 0, 0, 0, 0)
        WAIT_MS(100)
        CALL(evt_eff, STRING(""), STRING("mist"), 6, 60, 40, 0, 0, 1500, 0, 0, 0, 0, 0, 0)
        WAIT_MS(50)
        CALL(evt_eff, STRING(""), STRING("mist"), 6, 70, 10, -20, 0, 1500, 0, 0, 0, 0, 0, 0)
        WAIT_MS(4500)
        SET_VALUE(LW(0), 127)
        LOOP(16)
            SUBTRACT(LW(0), 7)
            CALL(evt_snd_sfx_vol, LW(10), LW(0))
            WAIT_MS(125)
        END_LOOP
        CALL(evt_snd_sfxoff, LW(10))
#endif
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(8), -1)
            // The big hand is removed.
            CALL_CHILD(queen_hand_1_dead_event)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(9), -1)
            CALL_CHILD(queen_hand_2_dead_event)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        IF_INT_NOT_EQUAL(GW(10), -1)
            // The small hand is removed.
            CALL_CHILD(queen_hand_small_dead_event)
        END_IF
    END_INLINE_EVENT
    LABEL(0)
    WAIT_MS(100)
    IF_INT_NOT_EQUAL(GW(8), -1)
        GOTO(0)
    END_IF
    IF_INT_NOT_EQUAL(GW(9), -1)
        GOTO(0)
    END_IF
    IF_INT_NOT_EQUAL(GW(10), -1)
        GOTO(0)
    END_IF
    IF_INT_NOT_EQUAL(GF(0), 1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_FLOAT_VALUE(LW(1), LW(1))
    SET_FLOAT_VALUE(LW(3), FLOAT(0.0f))
    LOOP(50)
        SUBTRACT_FLOAT(LW(1), FLOAT(0.81933594f))
        SUBTRACT_FLOAT(LW(3), FLOAT(0.81933594f))
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_FLOAT_VALUE(LW(4), LW(1))
        SUBTRACT_FLOAT(LW(4), LW(3))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(4), LW(2))
        WAIT_MS(10)
    END_LOOP
    // The queen is removed from the battle.
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_prilimit, 0)
    RETURN
EVT_END()

/** Wait event of the Shadow Queen: plays her idle pose from the pose table. */
EVT_BEGIN(queen_wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 3)
    RETURN
EVT_END()

/**
 * Entry event of the Shadow Queen: hides the status window,
 * the partner says stg8_las_161 and she says stg8_las_162 when she first appears.
 */
EVT_BEGIN(queen_entry_event)
    WAIT_MS(2000)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -113, 69, 332, -113, 46, 0, 15, 11)
    WAIT_MS(550)
    CALL(evt_msg_print_battle_party, STRING("stg8_las_161"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
    WAIT_MS(300)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_set_moveto, 0, 83, 141, 412, 83, 111, 0, 1, 11)
#else
    CALL(evt_btl_camera_set_moveto, 0, 63, 141, 412, 63, 111, 0, 1, 11)
#endif
    WAIT_MS(350)
    CALL(evt_msg_print, 2, STRING("stg8_las_162"), 0, BTL_UNIT_SELF)
    WAIT_MS(300)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(slot_init)
    RETURN
EVT_END()

/** Init event of the first big hand: sets its event handlers and pose. */
EVT_BEGIN(queen_hand_1_init_event)
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, 315, 0)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 0)
        LOOP(15)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
            ADD(LW(0), 16)
            WAIT_MS(5)
        END_LOOP
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    END_INLINE_EVENT
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(queen_hand_1_wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(queen_hand_1_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(queen_hand_1_damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_h_1"), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence_attr))
        CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&queen_muteki_regist))
    END_IF
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    SET_VALUE(GF(0), 1)
    RETURN
EVT_END()

/**
 * Event script: the first big hand's press attack (weapon_peach_black_press_attack):
 * it slams down on the chosen target.
 */
EVT_BEGIN(queen_hand_1_press_attack)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_press_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_press_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_press_attack))
    CALL(evt_eff_softdelete, LW(10))
    SET_VALUE(LW(0), 255)
    LOOP(15)
        // The big hand fades out of its place.
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 0)
    WAIT_MS(500)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(0), 20)
    SET_VALUE(LW(1), 0)
    ADD(LW(2), -30)
    // It reappears above the chosen target.
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    SET_VALUE(LW(0), 0)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), 16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, LW(10), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    // It slams down on the target and the camera shakes.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A1_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_HAND_UP1"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1100)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 15, 0)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_press_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_press_attack))
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_press_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_press_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Wrap up the attack.
    LABEL(98)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(evt_eff_softdelete, LW(10))
    SET_VALUE(LW(0), 255)
    LOOP(15)
        // After the slam it fades out and comes back to its place.
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    SET_VALUE(LW(0), 0)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), 16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, LW(10), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/** Event script: the first big hand's drain attack (weapon_peach_drain_attack): grabs the target and drains HP. */
EVT_BEGIN(queen_hand_1_drain_attack)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_drain_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_drain_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_drain_attack))
    CALL(evt_eff_softdelete, LW(10))
    SET_VALUE(LW(0), 255)
    LOOP(15)
        // The big hand fades out of its place.
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 0)
    WAIT_MS(500)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    ADD(LW(2), -30)
    // It reappears next to the chosen target.
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    SET_VALUE(LW(0), 0)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), 16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, LW(10), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    // It grabs the target.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_A2_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWEN_DRAIN1"), LW(0), LW(1), LW(2), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(300)
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
        CALL(queen_drain, LW(0), LW(1), LW(2))
        WAIT_MS(600)
    END_INLINE_EVENT
    WAIT_MS(2000)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_drain_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_drain_attack))
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_drain_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_drain_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_GetHpDamage, LW(3), LW(0))
    // The queen recovers HP equal to the damage dealt.
    CALL(btlevtcmd_RecoverHp, GW(13), 1, LW(0))
    CALL(btlevtcmd_GetPos, GW(13), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetHeight, GW(13), LW(8))
    ADD(LW(6), LW(8))
    ADD(LW(7), 30)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(5), LW(6), LW(7), LW(0), 0, 0, 0, 0, 0, 0, 0)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Wrap up the attack.
    LABEL(98)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(evt_eff_softdelete, LW(10))
    SET_VALUE(LW(0), 255)
    LOOP(15)
        // The hand fades out and returns to its place.
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRT_S_1"))
    SET_VALUE(LW(0), 0)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
        ADD(LW(0), 16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, LW(10), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/** Attack event of the first big hand: picks the press or the drain attack. */
EVT_BEGIN(queen_hand_1_attack_event)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
#if VERSION >= VERSION_US
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
#else
    CALL(btlevtcmd_DrawLots, LW(0), 2, 100, 20)
#endif
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(10), STRING("m_h_1"))
        CALL_CHILD(queen_hand_1_press_attack)
        CASE_EQUAL(1)
        SET_VALUE(LW(10), STRING("m_h_1"))
        CALL_CHILD(queen_hand_1_drain_attack)
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the first big hand: default damage handling. */
EVT_BEGIN(queen_hand_1_damage_event)
    IF_INT_EQUAL(GW(18), 0)
        SET_VALUE(GW(18), 1)
    END_IF
    ADD(GW(12), 1)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Dead event of the first big hand: kills the unit GW(8). */
EVT_BEGIN(queen_hand_1_dead_event)
    SET_VALUE(LW(0), 255)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, GW(8), 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, GW(8), 1, 0)
    CALL(evt_eff_softdelete, STRING("m_h_1"))
#if VERSION >= VERSION_JP
    WAIT_FRAMES(40)
    CALL(btlevtcmd_ClearAllStatus, GW(8))
#endif
    CALL(btlevtcmd_KillUnit, GW(8), 0)
    SET_VALUE(GW(8), -1)
#if VERSION >= VERSION_JP
    SET_VALUE(GF(1), 1)
#endif
    RETURN
EVT_END()

/** Wait event of the first big hand: plays its idle pose. */
EVT_BEGIN(queen_hand_1_wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/** Init event of the second big hand: sets its event handlers and pose. */
EVT_BEGIN(queen_hand_2_init_event)
    CALL(btlevtcmd_SetBaseScale, BTL_UNIT_SELF, FLOAT(-1.0996094f), FLOAT(1.0996094f), FLOAT(1.0996094f))
    CALL(btlevtcmd_SetBaseRotate, BTL_UNIT_SELF, 0, 315, 0)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
        SET_VALUE(LW(0), 0)
        LOOP(15)
            CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, LW(0))
            ADD(LW(0), 16)
            WAIT_MS(5)
        END_LOOP
        CALL(btlevtcmd_SetAlpha, BTL_UNIT_SELF, 1, 255)
    END_INLINE_EVENT
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(queen_hand_2_wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(queen_hand_2_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(queen_hand_2_damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("m_h_2"), STRING("mist2"), 0, LW(0), 15, LW(2), 50, 0, -1, 0, 0, 0, 0, 0)
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence_attr))
        CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&queen_muteki_regist))
    END_IF
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_NO_HP_GAUGE)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    SET_VALUE(GF(0), 1)
    RETURN
EVT_END()

/** Attack event of the second big hand. */
EVT_BEGIN(queen_hand_2_attack_event)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
#if VERSION >= VERSION_US
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
#else
    CALL(btlevtcmd_DrawLots, LW(0), 2, 100, 20)
#endif
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(10), STRING("m_h_2"))
        CALL_CHILD(queen_hand_1_press_attack)
        CASE_EQUAL(1)
        SET_VALUE(LW(10), STRING("m_h_2"))
        CALL_CHILD(queen_hand_1_drain_attack)
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the second big hand: default damage handling. */
EVT_BEGIN(queen_hand_2_damage_event)
    IF_INT_EQUAL(GW(18), 0)
        SET_VALUE(GW(18), 1)
    END_IF
    ADD(GW(12), 1)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Dead event of the second big hand: kills the unit GW(9). */
EVT_BEGIN(queen_hand_2_dead_event)
    SET_VALUE(LW(0), 255)
    LOOP(15)
        CALL(btlevtcmd_SetAlpha, GW(9), 1, LW(0))
        ADD(LW(0), -16)
        WAIT_MS(5)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, GW(9), 1, 0)
    CALL(evt_eff_softdelete, STRING("m_h_2"))
#if VERSION >= VERSION_JP
    WAIT_FRAMES(40)
    CALL(btlevtcmd_ClearAllStatus, GW(9))
#endif
    CALL(btlevtcmd_KillUnit, GW(9), 0)
    SET_VALUE(GW(9), -1)
#if VERSION >= VERSION_JP
    SET_VALUE(GF(1), 1)
#endif
    RETURN
EVT_END()

/** Wait event of the second big hand: plays its idle pose. */
EVT_BEGIN(queen_hand_2_wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/** Init event of the small hand unit (the swarm that replaces the big hands). */
EVT_BEGIN(queen_hand_small_init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(queen_hand_small_wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(queen_hand_small_attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(queen_hand_small_damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(evt_eff, STRING("m_h_s1"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_APPEAR1_2"), 0)
    CALL(queen_hand_small_entry_evt)
    IF_INT_EQUAL(GW(11), 0)
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence))
        CALL(btlevtcmd_SetPartsDefenceAttrTable, BTL_UNIT_SELF, 1, PTR(&queen_muteki_defence_attr))
        CALL(btlevtcmd_SetRegistStatus, BTL_UNIT_SELF, PTR(&queen_muteki_regist))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    SET_VALUE(GF(0), 1)
    RETURN
EVT_END()

/**
 * Event script: the small hand's drag attack (weapon_peach_dark_drag_attack,
 * with a last hit weapon_peach_dark_drag_last_attack).
 */
EVT_BEGIN(queen_hand_small_drag_attack)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_dark_drag_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_dark_drag_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_dark_drag_attack))
    CALL(evt_eff_softdelete, STRING("m_h_s1"))
    CALL(evt_eff_softdelete, STRING("m_h_s2"))
    CALL(evt_eff_softdelete, STRING("m_h_s3"))
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_GOOUT1"), 0)
    CALL(queen_hand_small_drag_2_evt)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_BOSS_QWENH_HAND_APPEAR1"), LW(0), LW(1), LW(2), 0)
#if VERSION == VERSION_EU
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
#else
    BEGIN_INLINE_EVENT
#endif
        CALL(queen_hand_small_drag_1_evt)
    END_INLINE_EVENT
    CALL(evt_eff, STRING("m_h_s1_"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2_"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3_"), STRING("mist2"), 0, -100, 15, 0, 100, 0, -1, 0, 0, 0, 0, 0)
    WAIT_MS(1250)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The attack misses or is dodged.
    LABEL(90)
    WAIT_MS(2250)
    CALL(evt_eff_softdelete, STRING("m_h_s1_"))
    CALL(evt_eff_softdelete, STRING("m_h_s2_"))
    CALL(evt_eff_softdelete, STRING("m_h_s3_"))
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_dark_drag_attack))
    CALL(battle_evt_majo_disp_off, LW(3), LW(4), 0, 0)
    // The hands drag the target out of sight.
    CALL(btlevtcmd_SetScale, LW(3), 0, 0, 0)
    CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), 0, LW(5))
    WAIT_MS(750)
    CALL(evt_eff_softdelete, STRING("m_h_s1_"))
    CALL(evt_eff_softdelete, STRING("m_h_s2_"))
    CALL(evt_eff_softdelete, STRING("m_h_s3_"))
    CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
    // The target is dropped back where it stood.
    CALL(btlevtcmd_SetScale, LW(3), 1, 1, 1)
    CALL(battle_evt_majo_disp_on, LW(3), LW(4), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_dark_drag_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_last_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_MS(750)
    LABEL(95)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_eff, STRING("m_h_s1"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
#if VERSION <= VERSION_DEMO_US
    BEGIN_INLINE_EVENT
#endif
        CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_APPEAR1_2"), 0)
#if VERSION == VERSION_EU
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
    END_IF
#endif
        CALL(queen_hand_small_drag_3_evt)
#if VERSION <= VERSION_DEMO_US
    END_INLINE_EVENT
#endif
    RETURN
EVT_END()

/**
 * Event script: the small hand's thousand-hands attack (weapon_peach_black_1000hand_attack):
 * the swarm of c_s_hand poses sweeps over the party.
 */
EVT_BEGIN(queen_hand_small_1000hand_attack)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // Pick a target for the attack; a confused unit that has none flusters.
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_peach_black_1000hand_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_peach_black_1000hand_attack), LW(3), LW(4))
    CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subsetevt_confuse_flustered)
        RETURN
    END_IF
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_peach_black_1000hand_attack))
    // The camera shakes as the swarm of small hands sweeps over the party.
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 180, 0)
    CALL(evt_eff_softdelete, STRING("m_h_s1"))
    CALL(evt_eff_softdelete, STRING("m_h_s2"))
    CALL(evt_eff_softdelete, STRING("m_h_s3"))
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HANDS_MOVE1"), 0)
#if VERSION >= VERSION_US
    BEGIN_INLINE_EVENT_GET_ID(LW(15))
#else
    BEGIN_INLINE_EVENT
#endif
        CALL(queen_hand_small_1000hand_1_evt)
    END_INLINE_EVENT
    WAIT_MS(400)
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_dark_drag_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        GOTO(90)
        CASE_EQUAL(2)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(98)
        CASE_END
    END_SWITCH
    // The attack misses or is dodged.
    LABEL(90)
    LOOP(4)
        SWITCH(LW(5))
            CASE_OR_EQUAL(4)
            CASE_END
            CASE_EQUAL(3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
            CASE_END
            CASE_EQUAL(6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
            CASE_EQUAL(2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_SWITCH
        WAIT_MS(500)
    END_LOOP
    WAIT_MS(1000)
    GOTO(95)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_peach_black_1000hand_attack))
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_1000hand_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_1000hand_attack), 0, LW(5))
    WAIT_MS(500)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_1000hand_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_1000hand_attack), 0, LW(5))
    WAIT_MS(500)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_1000hand_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_1000hand_attack), 0, LW(5))
    WAIT_MS(500)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_peach_black_1000hand_attack))
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_peach_black_1000hand_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_MS(500)
    WAIT_MS(1000)
    GOTO(98)
    LABEL(95)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_eff, STRING("m_h_s1"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s2"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING("m_h_s3"), STRING("mist2"), 0, 100, 15, 0, 150, 0, -1, 0, 0, 0, 0, 0)
#if VERSION >= VERSION_US
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
    END_IF
#endif
#if VERSION <= VERSION_DEMO_US
    BEGIN_INLINE_EVENT
        CALL(queen_hand_small_1000hand_2_evt)
    END_INLINE_EVENT
    WAIT_MS(1000)
#else
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_APPEAR1_2"), 0)
    CALL(queen_hand_small_1000hand_2_evt)
#endif
    RETURN
EVT_END()

/** Attack event of the small hand: picks the thousand-hands or the drag attack. */
EVT_BEGIN(queen_hand_small_attack_event)
    CALL(btlevtcmd_GetUnitWork, GW(13), UW_BOSS_BLACK_PEACH_ATTACK_STEP, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        GOTO(99)
    END_IF
#if VERSION >= VERSION_US
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
#else
    CALL(btlevtcmd_DrawLots, LW(0), 2, 60, 40)
#endif
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(queen_hand_small_1000hand_attack)
        CASE_EQUAL(1)
        CALL_CHILD(queen_hand_small_drag_attack)
    END_SWITCH
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the small hand: default damage handling. */
EVT_BEGIN(queen_hand_small_damage_event)
    IF_INT_EQUAL(GW(18), 0)
        SET_VALUE(GW(18), 1)
    END_IF
    ADD(GW(12), 1)
    CALL(btlevtcmd_GetDamageCode, BTL_UNIT_SELF, LW(0))
    BEGIN_INLINE_EVENT
        LOOP(5)
            CALL(queen_hand_small_1000hand_set_offset_evt, 2, 0, 0)
            WAIT_MS(70)
            CALL(queen_hand_small_1000hand_set_offset_evt, -2, 0, 0)
            WAIT_MS(70)
        END_LOOP
    END_INLINE_EVENT
END_IF // stray: no IF is open here; the original script has it too, and END_IF does nothing when run
SET_VALUE(LW(10), -2)
SET_VALUE(LW(11), 1)
CALL_CHILD(btldefaultevt_Damage)
CALL(evt_btl_camera_set_mode, 0, 0)
RETURN
EVT_END()

/** Dead event of the small hand: kills the unit GW(10). */
EVT_BEGIN(queen_hand_small_dead_event)
    CALL(evt_eff_softdelete, STRING("m_h_s1"))
    CALL(evt_eff_softdelete, STRING("m_h_s2"))
    CALL(evt_eff_softdelete, STRING("m_h_s3"))
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_QWEN_HAND_GOOUT1"), 0)
    CALL(queen_hand_small_dead_evt)
#if VERSION >= VERSION_JP
    WAIT_FRAMES(40)
    CALL(btlevtcmd_ClearAllStatus, GW(10))
#endif
    CALL(btlevtcmd_KillUnit, GW(10), 0)
    SET_VALUE(GW(10), -1)
#if VERSION >= VERSION_JP
    SET_VALUE(GF(1), 1)
#endif
    RETURN
EVT_END()

/** Wait event of the small hand: plays its idle pose. */
EVT_BEGIN(queen_hand_small_wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/** Script helper: shifts every hand of the swarm by (args[0], args[1], args[2]). */
static USER_FUNC(queen_hand_small_1000hand_set_offset_evt) {
    EvtWord* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 z = evtGetValue(event, args[2]);
    s32 i;
    HandElem* elem;

    extGetPosePtr();
    elem = hand_wp->elems;
    for (i = 0; i < hand_wp->num; i++, elem++) {
        elem->pos.x += x;
        elem->pos.y += y;
        elem->pos.z += z;
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper (runs until done): raises the swarm of small hands from below the floor (y from -80 to 0) in
 * randomised positions, ready for the thousand-hands attack.
 */
static USER_FUNC(queen_hand_small_1000hand_2_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): the thousand-hands sweep:
 * for 200 frames the hands move left along X in a wave, bobbing on a cosine,
 * with columns starting one after another.
 */
static USER_FUNC(queen_hand_small_1000hand_1_evt) {
    s32 i;
    HandElem* elem;
    f32 c;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->timer = 0;
            hand_wp->y = 0.0f;
            hand_wp->timer = 0;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->phase = 0;
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->timer > 200) {
                hand_wp->state++;
                break;
            }
            hand_wp->timer++;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                if (i % 10 <= hand_wp->timer / 3) {
                    elem->pos.x -= 3.0f;
                    c = cos(elem->phase / 6.0f);
                    elem->pos.y -= 0.3f * c;
                    elem->phase++;
                    if (elem->phase >= 2160) {
                        elem->phase -= 2160;
                    }
                }
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/** Script helper (runs until done): drags the hand swarm across the party for the drag attack (first stage). */
static USER_FUNC(queen_hand_small_drag_1_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 - 200 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
            hand_wp->timer = 30;
            hand_wp->state++;
            break;
        case 3:
            if (hand_wp->timer != 0) {
                hand_wp->timer--;
                if (hand_wp->timer == 0) {
                    Vec pos;
                    pos.x = -100.0f;
                    pos.y = 0.0f;
                    pos.z = 0.0f;
                    psndSFXOn_3D((const char*)0xF3C, &pos);
                }
                break;
            }
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 4:
        case 99:
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): the second stage of the drag:
 * sinks the swarm back below the floor (y from 0 to -80) and hides it.
 */
static USER_FUNC(queen_hand_small_drag_2_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = 0.0f;
            hand_wp->state++;
        case 1:
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            pose = extGetPosePtr();
            for (i = 0; i < hand_wp->num; i++, pose++) {
                pose->flags &= ~1;
            }
            return 1;
    }
    return 0;
}

/** Script helper (runs until done): the third stage: raises a fresh randomised swarm out of the floor. */
static USER_FUNC(queen_hand_small_drag_3_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/** Script helper (runs until done): the fourth stage: sinks the swarm back below the floor and hides it. */
static USER_FUNC(queen_hand_small_drag_4_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = 0.0f;
            hand_wp->state++;
        case 1:
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            pose = extGetPosePtr();
            for (i = 0; i < hand_wp->num; i++, pose++) {
                pose->flags &= ~1;
            }
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): sinks the swarm of small hands under the floor (y 0 to -80) and hides it;
 * used when the small hand unit dies.
 */
static USER_FUNC(queen_hand_small_dead_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = 0.0f;
            hand_wp->state++;
        case 1:
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            pose = extGetPosePtr();
            for (i = 0; i < hand_wp->num; i++, pose++) {
                pose->flags &= ~1;
            }
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): raises the swarm of small hands out of the floor (y -80 to 0) at randomised
 * positions; used when the small hand unit enters.
 */
static USER_FUNC(queen_hand_small_entry_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/**
 * Script helper: at the start of the fight, forces the break slot's cards until the first BINGO: Shine
 * Sprites (BREAK_SLOT_FLAG_QUEEN_FORCE_SHINE), or Stars in the demos (BREAK_SLOT_FLAG_QUEEN_FORCE_STAR).
 */
static USER_FUNC(slot_init) {
#if VERSION <= VERSION_DEMO_US
    BattleBreakSlotGetPtr()->flags |= BREAK_SLOT_FLAG_QUEEN_FORCE_STAR;
#else
    BattleBreakSlotGetPtr()->flags |= BREAK_SLOT_FLAG_QUEEN_FORCE_SHINE;
#endif
    return EVT_RETURN_DONE;
}

/** Script helper: creates a dark shock effect at (args[0], args[1], args[2]) with random pale colours. */
static USER_FUNC(peach_shock_evt) {
    EvtWord* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 z = evtGetValue(event, args[2]);
    EffectEntry* eff;

    eff = effShockN64Entry(3, x, y, z, 200.0f, 150.0f);
    ((EffShockN64Work*)eff->userdata)->col0[0] = 10;
    ((EffShockN64Work*)eff->userdata)->col0[1] = 10;
    ((EffShockN64Work*)eff->userdata)->col0[2] = 10;
    ((EffShockN64Work*)eff->userdata)->col1[0] = irand(50) + 155;
    ((EffShockN64Work*)eff->userdata)->col1[1] = irand(50) + 155;
    ((EffShockN64Work*)eff->userdata)->col1[2] = irand(50) + 155;
    return EVT_RETURN_DONE;
}

/**
 * Script helper (runs until done): the last stage of the HP drain:
 * raises the hand swarm in front of the stage as the queen takes her heal.
 */
static USER_FUNC(queen_hp_drain_5_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): the audience part of the HP drain:
 * sets the audience members' animation, sinks them 80 units while they are pulled down, then deletes them.
 */
static USER_FUNC(queen_hp_drain_4_evt) {
    s32 i;
    f32 x, y, z;

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    switch (event->userdata[0]) {
        case 0:
            event->userdata[1] = 0;
            event->userdata[0]++;
            for (i = 0; i < 200; i++) {
                if ((u8)BattleAudience_GetSysCtrl(i)) {
                    BattleAudience_SetAnim(i, 9, TRUE);
                }
            }
        case 1:
            for (i = 0; i < 200; i++) {
                if ((u8)BattleAudience_GetSysCtrl(i)) {
                    BattleAudience_GetPosition(i, &x, &y, &z);
                    BattleAudience_SetPosition(i, x, y - 1.0f, z);
                }
            }
            event->userdata[1]--;
            if (event->userdata[1] < -80) {
                event->userdata[0]++;
            }
            break;
        case 2:
            for (i = 0; i < 200; i++) {
                if ((u8)BattleAudience_GetSysCtrl(i)) {
                    BattleAudience_Delete(i);
                    BattleAudienceAddTargetNum(0.0f, -1.0f);
                }
            }
            event->userdata[0] = 99;
        case 99:
            return 1;
    }
    return 0;
}

/** Script helper (runs until done): lowers the hand swarm from y -30 to -110 under the floor during the HP drain. */
static USER_FUNC(queen_hp_drain_3_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -30.0f;
            hand_wp->state++;
        case 1:
            if (hand_wp->y <= -110.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            pose = extGetPosePtr();
            for (i = 0; i < hand_wp->num; i++, pose++) {
                pose->flags &= ~1;
            }
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): raises a hand swarm from y -110 to -30 closer to the audience (Z 270) during
 * the HP drain.
 */
static USER_FUNC(queen_hp_drain_2_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            event->userdata[0]++;
            hand_wp->y = -110.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 40 - 200 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 270 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 270 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= -30.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            return 1;
    }
    return 0;
}

/**
 * Script helper (runs until done): sinks the hand swarm from y 0 to -80 under the floor at the start of the HP
 * drain.
 */
static USER_FUNC(queen_hp_drain_1_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = 0.0f;
            hand_wp->state++;
        case 1:
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
        case 99:
            pose = extGetPosePtr();
            for (i = 0; i < hand_wp->num; i++, pose++) {
                pose->flags &= ~1;
            }
            return 1;
    }
    return 0;
}

/** Script helper: returns in args[0] how many audience members are in the stands. */
static USER_FUNC(queen_get_aud_num) {
    EvtWord* args = event->args;

    BattleAudience_GetAudienceNum();
    evtSetValue(event, args[0], BattleAudience_GetAudienceNum());
    return EVT_RETURN_DONE;
}

/** Script helper: deletes every audience member and reduces the audience's target count by one for each. */
static USER_FUNC(queen_kankyaku_delete_evt) {
    s32 i;

    for (i = 0; i < 200; i++) {
        if ((u8)BattleAudience_GetSysCtrl(i)) {
            BattleAudience_Delete(i);
            BattleAudienceAddTargetNum(0.0f, -1.0f);
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper (runs until done): raises the hand swarm for the possessed Peach's dark drag attack, shifted
 * 200 units left.
 */
static USER_FUNC(peach_hand1000_dark_drag_1_evt) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    if (isFirstCall) {
        hand_wp->state = 0;
    }
    switch (hand_wp->state) {
        case 0:
            hand_wp->y = -80.0f;
            pose = extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
                pose->flags |= 1;
                pose->flags &= ~2;
                PSMTXIdentity(*pose->mtx);
                elem->ofs = irand(20);
                elem->speed = 1.0f + irand(200) / 100.0f;
                elem->pos.x = (i % 10) * 20 - 200 + irand(15);
                elem->pos.y = hand_wp->y - elem->ofs;
#if VERSION <= VERSION_DEMO_US
                elem->pos.z = (i / 10) * -20 + 70 + irand(15);
#else
                elem->pos.z = (i / 10) * -15 + 70 + irand(15);
#endif
                pose->dir = irand(20) - 10;
                (*pose->mtx)[0][0] = 50.0f / (50.0f + irand(50));
                (*pose->mtx)[1][1] = 50.0f / (50.0f + irand(50));
                if (elem->flip) {
                    (*pose->mtx)[0][0] *= -1.0f;
                }
            }
            hand_wp->state++;
        case 1:
            if (hand_wp->y >= 0.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y += 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 2:
            hand_wp->timer = 30;
            hand_wp->state++;
            break;
        case 3:
            if (hand_wp->timer != 0) {
                hand_wp->timer--;
                break;
            }
            if (hand_wp->y <= -80.0f) {
                hand_wp->state++;
                break;
            }
            hand_wp->y -= 1.0f;
            extGetPosePtr();
            elem = hand_wp->elems;
            for (i = 0; i < hand_wp->num; i++, elem++) {
                elem->pos.y = hand_wp->y * elem->speed - elem->ofs;
            }
            break;
        case 4:
        case 99:
            return 1;
    }
    return 0;
}

/** Script helper: sets the alpha of the queen effect "m_q2" to args[0]. */
static USER_FUNC(eff_queen_set_alpha_evt) {
    s32 alpha = evtGetValue(event, *event->args);

    ((s32*)effNameToPtr("m_q2")->userdata)[10] = alpha;
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/**
 * Script helper: sets BREAK_SLOT_FLAG_NO_POISON_BINGO on the break slot, so the reels never land a Poison
 * Mushroom BINGO in this fight (JP and later).
 */
USER_FUNC(queen_break_slot_flag2_on) {
    BattleBreakSlotGetPtr()->flags |= BREAK_SLOT_FLAG_NO_POISON_BINGO;
    return EVT_RETURN_DONE;
}
#endif

/**
 * Script helper: plays the drain sound at (args[0], args[1], args[2]) with a stardust effect,
 * used when the queen drains the party.
 */
static USER_FUNC(queen_drain) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    psndSFXOn_3D((const char*)0xF20, &pos);
    effStardust2N64Entry(5, 10, 30, x, y, z, 20.0f, 40.0f);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: calls a lightning strike down at (args[0], args[1], args[2]):
 * a sound, a pink pokopi thunder bolt with a ground shock, and a camera shake.
 */
static USER_FUNC(queen_thunder) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    EffectEntry* eff;
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    psndSFXOn_3D((const char*)0xF1E, &pos);
    eff = effPokopiThunderN64Entry(0, 40, 20.0f + x + irand(20), 150.0f, 20.0f + z, x, 0.0f, z, 1.0f);
    ((EffPokopiThunderN64Work*)eff->userdata)->r = 255;
    ((EffPokopiThunderN64Work*)eff->userdata)->g = 160;
    ((EffPokopiThunderN64Work*)eff->userdata)->b = 192;
    ((EffPokopiThunderN64Work*)eff->userdata)->r2 = 20;
    ((EffPokopiThunderN64Work*)eff->userdata)->g2 = 20;
    ((EffPokopiThunderN64Work*)eff->userdata)->b2 = 20;
    eff = effShockN64Entry(3, x, 0.0f, z, 80.0f, 80.0f);
    ((EffShockN64Work*)eff->userdata)->col0[0] = 20;
    ((EffShockN64Work*)eff->userdata)->col0[1] = 20;
    ((EffShockN64Work*)eff->userdata)->col0[2] = 20;
    ((EffShockN64Work*)eff->userdata)->col1[0] = 255;
    ((EffShockN64Work*)eff->userdata)->col1[1] = 160;
    ((EffShockN64Work*)eff->userdata)->col1[2] = 192;
    btl_camera_shake_w(0, 1.0f, 1.0f, 8, 0);
    return EVT_RETURN_DONE;
}

/** Script helper: switches the animation index of every hand in the swarm to args[0]. */
static USER_FUNC(change_pose) {
    s32 anim = evtGetValue(event, *event->args);
    s32 i;
    HandElem* elem;

    elem = hand_wp->elems;
    for (i = 0; i < hand_wp->num; i++, elem++) {
        elem->animIdx = anim;
        elem->time = gp->renderTime;
    }
    return EVT_RETURN_DONE;
}

/** same body as pose_main; hand_main inlines it (register/stack order only match this way) */
inline void hand_pose_inl(void) {
    ExtdrvPose* pose;
    HandElem* elem;
    s32 i;
    HandAnim* a;
    f32 t;
    s32 id;
    f32 x, y, z;
    f32 hx, hy, hz;

    pose = extGetPosePtr();
    elem = hand_wp->elems;
    for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
        a = &hand_wp->anim[elem->animIdx];
        t = (f32)gp->framerate * OSTicksToMilliseconds((u64)(gp->renderTime - elem->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            elem->time = gp->renderTime;
            t -= 1.0f;
        }
        pose->texId = a->start + (s32)((a->count - 1) * t);
        id = evtGetValue(NULL, GW(10));
        if (id == -1) {
            (*pose->mtx)[0][3] = elem->pos.x;
            (*pose->mtx)[1][3] = elem->pos.y;
            (*pose->mtx)[2][3] = elem->pos.z;
        } else {
            BattleGetUnitPtr(_battleWorkPointer, id);
            BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
            BtlUnit_GetHomePos(BattleGetUnitPtr(_battleWorkPointer, id), &hx, &hy, &hz);
            (*pose->mtx)[0][3] = elem->pos.x + x - hx;
            (*pose->mtx)[1][3] = elem->pos.y + y - hy;
            (*pose->mtx)[2][3] = elem->pos.z + z - hz;
        }
    }
}
/**
 * Ext update callback of the hand swarm: advances every hand's animation and position (inlined hand_pose_inl),
 * then queues the draw callback.
 */
static void hand_main(void) {
    hand_pose_inl();
    dispEntry(CAMERA_3D, 0.0f, 1, hand_draw, NULL);
}

/** Draw callback of the hand swarm: loads the ext render mode, vertex, texture and TEV set-up and draws all hands. */
static void hand_draw(CameraId cameraId, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

/**
 * Ext init callback of the hand swarm: allocates the work area and the hand list,
 * builds the animation table via pose_init and gives every hand a random animation start and flip.
 */
static void hand_init(void) {
    s32 i;
    ExtdrvPose* pose;
    HandElem* elem;

    hand_wp = BTL_ALLOC(sizeof(HandWork));
    memset(hand_wp, 0, sizeof(HandWork));
    hand_wp->num = extGetPoseNum();
    hand_wp->elems = BTL_ALLOC(hand_wp->num * sizeof(HandElem));
    memset(hand_wp->elems, 0, hand_wp->num * sizeof(HandElem));
    pose_init();
    pose = extGetPosePtr();
    elem = hand_wp->elems;
    for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
        pose->flags |= 6;
        PSMTXIdentity(*pose->mtx);
        elem->animIdx = 0;
        elem->time = gp->renderTime - (u64)irand(100) * 10000000;
        elem->flip = irand(1);
    }
}

/**
 * Advances every hand pose: computes the animation frame from the elapsed render time
 * and places the hand at its position, offset by the position of the unit in GW(10) if there is one.
 */
static void pose_main(void) {
    ExtdrvPose* pose;
    HandElem* elem;
    s32 i;
    HandAnim* a;
    f32 t;
    s32 id;
    f32 x, y, z;
    f32 hx, hy, hz;

    pose = extGetPosePtr();
    elem = hand_wp->elems;
    for (i = 0; i < hand_wp->num; i++, pose++, elem++) {
        a = &hand_wp->anim[elem->animIdx];
        t = (f32)gp->framerate * OSTicksToMilliseconds((u64)(gp->renderTime - elem->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            elem->time = gp->renderTime;
            t -= 1.0f;
        }
        pose->texId = a->start + (s32)((a->count - 1) * t);
        id = evtGetValue(NULL, GW(10));
        if (id == -1) {
            (*pose->mtx)[0][3] = elem->pos.x;
            (*pose->mtx)[1][3] = elem->pos.y;
            (*pose->mtx)[2][3] = elem->pos.z;
        } else {
            BattleGetUnitPtr(_battleWorkPointer, id);
            BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
            BtlUnit_GetHomePos(BattleGetUnitPtr(_battleWorkPointer, id), &hx, &hy, &hz);
            (*pose->mtx)[0][3] = elem->pos.x + x - hx;
            (*pose->mtx)[1][3] = elem->pos.y + y - hy;
            (*pose->mtx)[2][3] = elem->pos.z + z - hz;
        }
    }
}

/**
 * Builds the animation table of the hand swarm from hand_data:
 * groups consecutive entries of the same model and animation into HandAnim ranges,
 * and sets the paper-craft light position for the hands.
 */
static void pose_init(void) {
    char name[32];
    char anim[32];
    HandData* d = hand_data;
    s32 i = 0;
    s32 start;

    // hand_light_init is an inline helper defined by hand before EVT_BEGIN(shadow_queen_1000) in the
    // rels/ source: its (Vec){-200, 100, 500} template must sit there in .rodata
    hand_light_init();
    strcpy(name, "");
    strcpy(anim, "");
    hand_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            hand_wp->animNum++;
        }
        strcpy(hand_wp->anim[hand_wp->animNum].name, name);
        strcpy(hand_wp->anim[hand_wp->animNum].anim, anim);
        hand_wp->anim[hand_wp->animNum].start = start;
        hand_wp->anim[hand_wp->animNum].count = i - start + 1;
        hand_wp->anim[hand_wp->animNum].rate = d->rate;
        i++;
        d++;
    } while (d->name != NULL);
    hand_wp->animNum++;
}

/**
 * Script helper: fills hand_data with one entry per third frame of the queen's KRT_S_1 animation,
 * giving every hand its own animation start offset.
 */
static USER_FUNC(make_pattern) {
    HandData* d = hand_data;
    NpcEntry* npc = npcNameToPtr("dummy");
    AnimData* data;
    s32 i;

    animPoseSetAnim(npc->poseId, "KRT_S_1", TRUE);
    animPoseGetAnimPosePtr(npc->poseId);
    data = animPoseGetAnimDataPtr(npc->poseId);
    for (i = 0; i < (s32)(data->loopInfo)[2]; i += 3, d++) {
        d->name = "c_s_hand";
        d->anim = "KRT_S_1";
        d->rate = 3.0f * i;
    }
    d->name = NULL;
    return EVT_RETURN_DONE;
}

/**
 * Script helper: keeps the queen's head (part 3) animation in step with the possessed Peach's talking
 * and damage animations (KRT_T_x, KRT_D_1) so the shadow head talks with her.
 */
static USER_FUNC(peach_talk_synchro_shadow_head_evt) {
    BattleUnitPart* part;

    part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 1);
    if (strcmp(part->poseName, "KRT_T_1") == 0 || strcmp(part->poseName, "KRT_T_2") == 0 ||
        strcmp(part->poseName, "KRT_T_3") == 0) {
        part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3);
        if (strcmp(part->poseName, "KRT_T_1") != 0) {
            BtlUnit_SetAnim(part, "KRT_T_1");
            return 0;
        }
    }
    part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 1);
    if (strcmp(part->poseName, "KRT_T_1") != 0 && strcmp(part->poseName, "KRT_T_2") != 0 &&
        strcmp(part->poseName, "KRT_T_3") != 0) {
        part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3);
        if (strcmp(part->poseName, "KRT_T_1") == 0) {
            BtlUnit_SetAnim(part, "KRT_S_1");
            return 0;
        }
    }
    if (strcmp(BattleGetUnitPartsPtr(BattleTransID(event, -2), 1)->poseName, "KRT_D_1") == 0) {
        part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3);
        if (strcmp(part->poseName, "KRT_D_1") != 0) {
            BtlUnit_SetAnim(part, "KRT_D_1");
            return 0;
        }
    }
    if (strcmp(BattleGetUnitPartsPtr(BattleTransID(event, -2), 1)->poseName, "KRT_D_1") != 0) {
        part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3);
        if (strcmp(part->poseName, "KRT_D_1") == 0) {
            BtlUnit_SetAnim(part, "KRT_S_1");
            return 0;
        }
    }
    return 0;
}

/**
 * Script helper: positions the queen's head, hand
 * and cape parts (parts 3, 4 and 5) on the world positions of the locators of her body poses;
 * sets their display Z offsets.
 */
static USER_FUNC(shadow_queen_connect) {
    QueenConnect* wk;
    Vec* wpos;
    BattleUnitPart* part;

    if (isFirstCall) {
        event->userdatap[0] = wk = BTL_ALLOC(sizeof(QueenConnect));
        wk->poseId[0] = BattleGetUnitPartsPtr(BattleTransID(event, -2), 2)->poseId;
        animPoseWorldPositionEvalOn(wk->poseId[0]);
        wk->idx[0] = animPoseGetGroupIdx(wk->poseId[0], "locator12");
        wk->poseId[1] = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3)->poseId;
        animPoseWorldPositionEvalOn(wk->poseId[1]);
        wk->idx[1] = animPoseGetGroupIdx(wk->poseId[1], "locator12");
        animPosePeraOff(wk->poseId[0]);
        animPosePeraOff(wk->poseId[1]);
        wk->poseId[2] = BattleGetUnitPartsPtr(BattleTransID(event, -2), 4)->poseId;
        animPosePeraOff(wk->poseId[2]);
    }
    wk = event->userdatap[0];
    wpos = *animPoseGetAnimPosePtr(wk->poseId[0])->worldPositions;
    part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 3);
    BtlUnit_SetPartsPos(part, wpos[wk->idx[0]].x, wpos[wk->idx[0]].y, wpos[wk->idx[0]].z);
    part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 5);
    part->dispZOffset = 7.0f;
    BtlUnit_SetPartsPos(part, wpos[wk->idx[0]].x, wpos[wk->idx[0]].y, wpos[wk->idx[0]].z);
    wpos = *animPoseGetAnimPosePtr(wk->poseId[1])->worldPositions;
    part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 4);
    part->dispZOffset = 1.0f;
    BtlUnit_SetPartsPos(part, wpos[wk->idx[1]].x, wpos[wk->idx[1]].y, wpos[wk->idx[1]].z);
    return 0;
}
