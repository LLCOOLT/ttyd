// Battle unit data and scripts for Bobbery (Sanders) as a partner.
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include <string.h>
#include "battle/battle_attack_audience.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "unit/unit_bomzou.h"
#include "evt/evt_snd.h"

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "version.h"

// Unit work slots of Bobbery (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_SANDERS_UNUSED_0 = 0, // set to -1 by init_event; nothing reads it
    UW_SANDERS_UNUSED_1 = 1, // set to -1 by init_event; nothing reads it
    UW_SANDERS_UNUSED_2 = 2, // set to -1 by init_event; nothing reads it
};

static USER_FUNC(_get_bomb_hit_position);
static USER_FUNC(_judge_on_stage);
static USER_FUNC(_sanders_make_extra_work_area);
static USER_FUNC(_shot_move);
static USER_FUNC(_make_counterset_weapon);
static void __makeTechMenuFunc(BattleCommand* command, s32* count);

PoseTableEntry pose_table_sanders_stay[25];
PoseTableEntry pose_table_counter_sanders[20];
#if VERSION <= VERSION_DEMO_US
static BattleDataEntry data_table[8];
#else
static BattleDataEntry data_table[9];
#endif
BattleUnitKindPart unitpartsdata_Party_Sanders[1];
BattleUnitKind unitdata_Party_Sanders;
static EvtWord init_event[63];
static EvtWord damage_event[16];
static EvtWord wait_event[26];
BattleWeapon partyWeapon_SandersFirstAttack;
BattleWeapon partyWeapon_SandersNormalAttack;
BattleWeapon partyWeapon_SandersTimeBombSet;
BattleWeapon partyWeapon_SandersCounterSet;
BattleWeapon partyWeapon_SandersSuperBombAttack;
extern EvtWord partySandersAttack_FirstAttack[];
extern EvtWord partySandersAttack_NormalAttack[];
extern EvtWord partySandersAttack_SuperBombAttack[];
extern EvtWord partySandersAttack_CounterSet[];
extern EvtWord partySandersAttack_TimeBombSet[];
extern EvtWord _shot_bomb_event[];
extern EvtWord sanders_appeal_event[];
static EvtWord attack_audience_event[284];
extern EvtWord sanders_battle_end_event[];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static EvtWord attack_event[2];
BattleUnitSetup entry_bomzou;
static EvtWord party_win_reaction[9];

/** Bobbery's defence: 0 against every element. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Bobbery's defence attributes: normal (0) against every element, no weakness or immunity. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Bobbery's status chances: 100 for every status (badges lower them in battle). */
static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

/**
 * Bobbery's normal pose table: animations for each status (stop, dizzy, poison, confusion, sleep, freeze,
 * instant KO), the hurt poses, walking and running, low HP, the failed Run Away tumble, talking, item use,
 * the command menu wait, the Appeal, zero gravity, the Defend stance and plain standing.
 */
PoseTableEntry pose_table_sanders_stay[] = {
    {9, "D_4"},
    {2, "D_4"},
    {3, "X_1"},
    {4, "D_2"},
    {5, "X_1"},
    {1, "N_1"},
    {27, "D_3"},
    {BTL_POSE_NORMAL, "S_1"},
    {37, "G_2"},
    {31, "G_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_PERIL, "D_2"},
    {BTL_POSE_DANGER, "D_2"},
    {BTL_POSE_ESCAPE_FAIL, "D_4"},
    {BTL_POSE_ESCAPE_FAIL_END, "D_2"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_ITEM_USE, "I_1"},
    {BTL_POSE_COMMAND_WAIT, "C_1"},
    {BTL_POSE_APPEAL, "O_1"},
    {BTL_POSE_ZERO_GRAVITY, "R_3"},
    {49, "J_1A"},
    {BTL_POSE_DEFEND, "G_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

/**
 * Bobbery's pose table while Hold Fast is active (wait_event swaps it in):
 * the same poses, but he stands and idles with his fuse lit (A_3).
 */
PoseTableEntry pose_table_counter_sanders[] = {
    {1, "N_2"},
    {27, "D_3"},
    {BTL_POSE_NORMAL, "A_3"},
    {37, "G_2"},
    {31, "G_1"},
    {BTL_POSE_DAMAGE, "D_1"},
    {BTL_POSE_WALK, "W_1"},
    {BTL_POSE_RUN, "R_1"},
    {BTL_POSE_PERIL, "D_2"},
    {BTL_POSE_DANGER, "D_2"},
    {BTL_POSE_ESCAPE_FAIL, "D_4"},
    {BTL_POSE_ESCAPE_FAIL_END, "D_2"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_ITEM_USE, "I_1"},
    {BTL_POSE_COMMAND_WAIT, "C_1"},
    {BTL_POSE_APPEAL, "O_1"},
    {BTL_POSE_ZERO_GRAVITY, "R_3"},
    {49, "J_1A"},
    {BTL_POSE_DEFEND, "G_1"},
    {BTL_POSE_STAY_DEFAULT, "A_3"},
};

/**
 * Bobbery's data events: Appeal, the audience attack reaction, his move list (tag 1, __makeTechMenuFunc),
 * First Strike (nothing), the victory pose, an empty step run after a move's cost is paid (7), the battle-end
 * Hold Fast reset (retail only) and the spin when he superguards an attack (47).
 */
static BattleDataEntry data_table[] = {
    {5, sanders_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
#if VERSION >= VERSION_JP
    {66, sanders_battle_end_event},
#endif
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

/** Bobbery's single battle part: his targetable body (model c_bomt_n) with the normal pose table. */
BattleUnitKindPart unitpartsdata_Party_Sanders[] = {
    {1, "btl_un_sanders", "c_bomt_n", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table_sanders_stay},
};

/**
 * Bobbery's battle unit (UNIT_BOBBERY), listed in battle_party.c's partner table:
 * one part, the partner hit sounds, no enemy HP gauge.
 */
BattleUnitKind unitdata_Party_Sanders = {
    229,
    "btl_un_sanders",
    10,
    5,
    5,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    20,
    33,
    11,
    28,
    0.0f,
    16.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    10.0f,
    0.0f,
    0.0f,
    10.0f,
    21.45f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_MARIO_DAMAGE_FIRE1",
    "SFX_MARIO_DAMAGE_ICE1",
    "SFX_MARIO_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_NO_HP_GAUGE,
    &regist,
    1,
    unitpartsdata_Party_Sanders,
    init_event,
    data_table,
};

/**
 * Bobbery's battle entry: starts 250 units behind his home spot and, after 40 frames,
 * runs in to it at speed 4 with his footstep sounds, then takes his stay pose.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 9, 9, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Init for Bobbery: registers his wait, attack, damage, confusion and entry scripts and his walk,
 * run and jump sounds, sets UW_SANDERS_UNUSED_0-2 to -1 (not read anywhere)
 * and allocates Hold Fast's spare weapon.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 18, 18)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 9)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SANDERS_UNUSED_0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SANDERS_UNUSED_1, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_SANDERS_UNUSED_2, -1)
    CALL(_sanders_make_extra_work_area)
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Hit reaction: straightens his rotation (left over from his moves), then runs the default damage script. */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Idle: uses the Hold Fast pose table while he has the Hold Fast status (22), the normal one otherwise,
 * and plays its stay pose.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HOLD_FAST, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_counter_sanders))
    ELSE
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_sanders_stay))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Weapon of Bobbery's First Strike, when he starts the battle by hitting an enemy in the field:
 * an explosion on the front ground-bound enemy dealing 4, 5 or 6 damage at Normal, Super or Ultra rank,
 * with no action command; it cannot be guarded.
 */
BattleWeapon partyWeapon_SandersFirstAttack = {
    NULL, // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {4, 4, 5, 5, 6, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_EXPLOSION, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_GROUNDS_WINGED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partySandersAttack_FirstAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Bomb (0 FP): Bobbery explodes on the front ground-bound enemy (explosive, cannot be guarded).
 * Damage by rank: 1, 2 or 3 on a failed action command, 4, 5 or 6 on success. Usable while confused.
 */
BattleWeapon partyWeapon_SandersNormalAttack = {
    "btl_wn_pbm_normal", // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pbm_bakuhatsu", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 4, 2, 5, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_EXPLOSION, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_bakuhatsu", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partySandersAttack_NormalAttack, // attackEvtScript
    {0, 10, 10, 100, 10, 10, 10, 5, 10, 0, 0, 0}, // stageEffectRates
};

/**
 * Bomb Squad (3 FP): Bobbery throws up to three time bombs that explode a turn later.
 * The weapon itself does no damage; the thrown bombs (unit_bomzou) do.
 */
BattleWeapon partyWeapon_SandersTimeBombSet = {
    "btl_wn_pbm_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pbm_jigen_bakudan", // description
    100, // baseAccuracy
    3, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_jigen_bakudan", // acHelpMsg
    SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partySandersAttack_TimeBombSet, // attackEvtScript
    {0}, // stageEffectRates
};

/**
 * Hold Fast (4 FP): Bobbery targets himself and gains the Hold Fast status, which damages enemies
 * that attack him directly. The 1-turn duration here is replaced per use by the action command result plus one
 * (_make_counterset_weapon copies this weapon into his spare slot).
 */
BattleWeapon partyWeapon_SandersCounterSet = {
    "btl_wn_pbm_lv2", // name
#if VERSION >= VERSION_US
    346, // icon
#else
    338, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pbm_counter", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_bom_counter", // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    1, // holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partySandersAttack_CounterSet, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 5, 5, 100, 20, 10, 5, 5, 5, 5, 0, 0}, // stageEffectRates
#else
    {0, 5, 5, 100, 20, 5, 5, 5, 5, 5, 0, 0}, // stageEffectRates
#endif
};

/**
 * Bob-ombast (9 FP): a massive explosion that hits every enemy (explosive, cannot be guarded).
 * The damage is the action command's gauge result (weaponGetACOutputParam on output 2).
 */
BattleWeapon partyWeapon_SandersSuperBombAttack = {
    "btl_wn_pbm_lv3", // name
#if VERSION >= VERSION_US
    347, // icon
#else
    339, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pbm_sungoi_bakuhatsu", // description
    100, // baseAccuracy
    9, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
#if VERSION >= VERSION_US
    1, // stylishCommandMultiplier
#else
    2, // stylishCommandMultiplier
#endif
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetACOutputParam, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_EXPLOSION, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_super_bakuhatsu", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_GROUNDS_WINGED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partySandersAttack_SuperBombAttack, // attackEvtScript
    {0, 50, 50, 100, 20, 25, 25, 10, 10, 5, 0, 0}, // stageEffectRates
};

/**
 * Bobbery's first strike, used when he hits an enemy in the field to start the battle:
 * he moves up to the first-attack target's hit point (_get_bomb_hit_position) and explodes on it,
 * then returns home.
 */
EVT_BEGIN(partySandersAttack_FirstAttack)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    SET_VALUE(LW(12), PTR(&partyWeapon_SandersFirstAttack))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -2, 1)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    WAIT_FRAMES(60)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
#else
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
#endif
    CALL(btlevtcmd_StageDispellFog)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(8)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    WAIT_FRAMES(20)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Bobbery's Bomb: he walks up to the enemy, lights his fuse during the action command and explodes on it,
 * damaging the target, then walks back home.
 */
EVT_BEGIN(partySandersAttack_NormalAttack)
    // Pick the target, pay the cost and aim the camera at Bobbery and the enemy.
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Action command (hold A, release when the light comes on): the timing window shrinks at higher difficulty.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 60)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 45)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 30)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 25)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 20)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 12)
        CASE_DEFAULT
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 6)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 2, LW(0), LW(1), 0, 100, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 15)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 15, 1, 0)
    WAIT_FRAMES(22)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(0), 5)
        LOOP(LW(0))
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(1))
            IF_INT_EQUAL(LW(1), 0)
                SET_VALUE(LW(0), 5)
            ELSE
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    // The command went wrong: his fuse fizzles, he topples over and the move ends without an explosion.
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(1))
    IF_INT_EQUAL(LW(1), 2)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -2, 1)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
        CALL(btlevtcmd_StopAC)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), 0)
        WAIT_FRAMES(60)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        GOTO(95)
    END_IF
    // A pre-emptive spiky enemy: he walks into its spikes first and is hurt.
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(5))
        MULTIPLY_FLOAT(LW(5), 35)
        CALL(_get_bomb_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(5))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 60, -2, 1)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    // He walks up to the enemy with his fuse sizzling while the camera zooms in, then glows for a second.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 90, -2, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    WAIT_FRAMES(60)
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
        WAIT_MS(1000)
    END_SWITCH
    // He explodes (a bigger blast for a successful command in retail), the camera shakes and stage fog clears.
    CALL(btlevtcmd_ResultAC)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    ELSE
        CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
#else
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
#endif
    CALL(btlevtcmd_StageDispellFog)
    // A miss: the enemy plays its dodge reaction.
    IF_INT_NOT_EQUAL(LW(5), 1)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(90)
    END_IF
    // The hit: a successful command adds the rating effect (Nice, Good...) and the higher damage.
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    // The blast throws him off the top of the screen and he falls back down to his home spot.
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(8), EVT_NULLPTR)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    // Stylish: pressing A as he lands makes him stretch and squash for the audience; otherwise he lands in a heap.
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 15, 15, 15)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.1992188f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.1992188f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        WAIT_FRAMES(40)
    ELSE
        CALL(evt_audience_acrobat_notry)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(40)
    END_IF
    // The audience refills Star Power, then he walks back home.
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Bobbery's Bob-ombast: he charges a huge explosion with the action command and blasts every enemy at once,
 * then returns home.
 */
EVT_BEGIN(partySandersAttack_SuperBombAttack)
    // Target every enemy, pay the cost and aim the camera at Bobbery.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // Action command (tap A to fill the gauge): its length and fill rate depend on the difficulty.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 300)
        SET_VALUE(LW(1), 20)
        SET_VALUE(LW(2), 20)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 370)
        SET_VALUE(LW(1), 18)
        SET_VALUE(LW(2), 22)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 255)
        SET_VALUE(LW(1), 17)
        SET_VALUE(LW(2), 23)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 225)
        SET_VALUE(LW(1), 16)
        SET_VALUE(LW(2), 24)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 210)
        SET_VALUE(LW(1), 15)
        SET_VALUE(LW(2), 26)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 180)
        SET_VALUE(LW(1), 14)
        SET_VALUE(LW(2), 28)
        CASE_DEFAULT
        SET_VALUE(LW(0), 150)
        SET_VALUE(LW(1), 13)
        SET_VALUE(LW(2), 28)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 1, LW(0), 178, LW(1), LW(2), 15, 46, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetGaugeParam, 45, 75, 100, 100)
    CALL(btlevtcmd_AcSetFlag, 64)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 6, 1, 0)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_StartAC, 1)
    // A pre-emptive spiky enemy in front: he walks into its spikes and the move ends there.
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
        MULTIPLY_FLOAT(LW(6), 35)
        CALL(_get_bomb_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 60, -2, 1)
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
        RETURN
    END_IF
    // While the command runs: sparks burst around him, the fuse hiss rises in pitch and he swells with the gauge.
    BEGIN_SIBLING_EVENT
        SUBTRACT(LW(0), 85)
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 150, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 30, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(15)
        CALL(evt_eff, STRING(""), STRING("sandars"), 5, LW(0), LW(1), LW(2), 120, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(40)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SUBTRACT(LW(0), 85)
        WAIT_FRAMES(LW(0))
        CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
        SET_VALUE(LW(0), 0)
        LOOP(80)
            ADD(LW(0), 1)
            IF_INT_GREATER(LW(0), 80)
                SET_VALUE(LW(0), 80)
            END_IF
            SET_VALUE(LW(1), 4096)
            MULTIPLY(LW(1), LW(0))
            DIVIDE(LW(1), 80)
            CALL(evt_snd_sfx_pit, LW(14), LW(1))
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_FRAMES(3)
        CALL(evt_snd_sfxoff, LW(14))
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(LW(0))
            CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
            ADD(LW(0), 100)
            MULTIPLY_FLOAT(LW(0), FLOAT(0.009765625f))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(0), FLOAT(1.0f))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // He walks up to the front enemy; when the command ends he blows up in a huge blast that shakes the screen.
    SET_VALUE(LW(13), LW(0))
    SUBTRACT(LW(13), 85)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(_get_bomb_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_ATTACK1"), 0, 0, -1, -1, 0, 0)
    ADD(LW(2), 5)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(13), -2, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
        WAIT_MS(1000)
    END_SWITCH
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK4"), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_BITS_SET(LW(6), 2)
        CALL(evt_eff, STRING(""), STRING("sandars"), 3, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    ELSE
        CALL(evt_eff, STRING(""), STRING("sandars"), 4, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
#if VERSION >= VERSION_US
    CALL(btlevtcmd_StageDispellFog)
#endif
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 20, 13)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    // Each enemy in turn: a miss plays its dodge reaction; a hit deals the gauge damage and a full enough gauge
    // earns a rating (Nice, Good...).
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
        SWITCH(LW(0))
#if VERSION >= VERSION_JP
            CASE_LESS_OR_EQUAL(3)
            SET_VALUE(LW(0), -1)
            CASE_LESS_OR_EQUAL(5)
            SET_VALUE(LW(0), 0)
            CASE_LESS_OR_EQUAL(7)
            SET_VALUE(LW(0), 1)
#else
            CASE_LESS_OR_EQUAL(2)
            SET_VALUE(LW(0), -1)
            CASE_LESS_OR_EQUAL(4)
            SET_VALUE(LW(0), 0)
            CASE_LESS_OR_EQUAL(6)
            SET_VALUE(LW(0), 1)
#endif
            CASE_DEFAULT
            SET_VALUE(LW(0), 2)
        END_SWITCH
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
        ELSE
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
            CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
        END_IF
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    // Move on to the next enemy until every one has been hit.
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    // The blast throws him off the top of the screen and he falls back down to his home spot.
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(92)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
        CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(8), EVT_NULLPTR)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    // Stylish: pressing A as he lands makes him stretch and squash for the audience; otherwise he lands in a heap.
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 15, 15, 15)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.1992188f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.1992188f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(0.5996094f), 8)
            LOOP(8)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_sub_intpl_init_float, 11, FLOAT(0.5996094f), FLOAT(1.0f), 6)
            LOOP(6)
                CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
                CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        WAIT_FRAMES(40)
    ELSE
        CALL(evt_audience_acrobat_notry)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("F_1"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_THUNDERS_DOWN1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        WAIT_FRAMES(40)
    END_IF
    // The audience refills Star Power, then he walks back home.
    LABEL(95)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Bobbery's Hold Fast: he braces himself; the action command output plus one sets how many turns the Hold Fast
 * status lasts (_make_counterset_weapon), so enemies that touch him take explosive counter damage.
 */
EVT_BEGIN(partySandersAttack_CounterSet)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    SET_VALUE(LW(12), PTR(&partyWeapon_SandersCounterSet))
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_MARIO, LW(1), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(0), LW(1))
    DIVIDE(LW(0), 2)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 73, 400, LW(0), 43, 0, 30, 5)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(9), STRING("O_1"))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 3, 0, 40, 1, 0, 1, 2, 0)
    CALL(btlevtcmd_AcSetFlag, 8)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 18, 1, 0)
    WAIT_FRAMES(52)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_2"))
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_GetResultAC, LW(0))
    CALL(btlevtcmd_StopAC)
    IF_BITS_CLEAR(LW(0), 2)
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    ELSE
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
        SUBTRACT(LW(0), 1)
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_GetResultPrizeLv, BTL_UNIT_NONE, LW(0), LW(6))
#else
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
#endif
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    END_IF
#if VERSION >= VERSION_US
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 12, 12, 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
        WAIT_FRAMES(30)
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
#endif
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    ADD(LW(0), 1)
    CALL(_make_counterset_weapon, LW(12), LW(0))
    WAIT_FRAMES(20)
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(30)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    END_INLINE_EVENT
#if VERSION >= VERSION_US
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
#endif
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    WAIT_FRAMES(80)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Empty: partner moves come from the player's menu choices, not a unit attack script. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/**
 * Setup for each time bomb that Bomb Squad spawns (unit_bomzou): on Bobbery's side,
 * acting before the player's turn, placed off stage until the throw moves it.
 */
BattleUnitSetup entry_bomzou = {
    &unit_bomzou, // unitKindParams
    2, // alliance
    {0}, // pad_05
    BATTLE_PHASE_BEFORE_PLAYER, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Bobbery's Bomb Squad: for each successful action command he throws one of up to three bombs (unit_bomzou)
 * along the aimed arc (_shot_bomb_event); bombs that land off the stage are removed, the rest explode next turn.
 */
EVT_BEGIN(partySandersAttack_TimeBombSet)
    // Pay the cost and spawn three hidden bombs at Bobbery's position.
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(10), LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(11), LW(3))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_bomzou), 0)
    CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(12), LW(3))
    // Action command (press A with good timing to throw): the aiming speed depends on the difficulty.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 12)
        CASE_EQUAL(-2)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 15)
        CASE_EQUAL(-1)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 20)
        CASE_EQUAL(0)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 22)
        CASE_EQUAL(1)
        SET_VALUE(LW(1), 80)
        SET_VALUE(LW(2), 32)
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 90)
        SET_VALUE(LW(2), 50)
        CASE_DEFAULT
        SET_VALUE(LW(1), 120)
        SET_VALUE(LW(2), 80)
    END_SWITCH
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, LW(0), 3, LW(1), LW(1), 0, 90, LW(2), EVT_NULLPTR)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 7, 1, 0)
    CALL(btlevtcmd_AcSetFlag, 1)
    WAIT_FRAMES(20)
    // Each successful press shows the next bomb and throws it along the aimed arc; after the third throw comes
    // the stylish chance (retail only) and the throwing stops.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_4A"))
    CALL(btlevtcmd_StartAC, 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(13), 0)
        SET_VALUE(LW(14), 5)
        LOOP(LW(14))
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                SWITCH(LW(13))
                    CASE_EQUAL(0)
                    SET_VALUE(LW(3), LW(10))
                    CASE_EQUAL(1)
                    SET_VALUE(LW(3), LW(11))
                    CASE_DEFAULT
                    SET_VALUE(LW(3), LW(12))
                END_SWITCH
                CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_HIDDEN)
                CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
                CALL(btlevtcmd_AcGetOutputParam, 1, LW(1))
                ADD(LW(1), 20)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_4B"))
                SPAWN_EVENT_GET_ID(PTR(_shot_bomb_event), LW(9))
                ADD(LW(13), 1)
                IF_INT_GREATER_OR_EQUAL(LW(13), 3)
                    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
#if VERSION >= VERSION_US
                    WAIT_FRAMES(10)
                    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 12, 12, 10)
                    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
                    SWITCH(LW(6))
                        CASE_GREATER_OR_EQUAL(2)
                        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
                        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
                        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
                        CASE_DEFAULT
                        CALL(evt_audience_acrobat_notry)
                    END_SWITCH
#endif
                    CALL(btlevtcmd_WaitEventEnd, LW(9))
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_4A"))
                CALL(btlevtcmd_AcSetOutputParam, 0, 0)
            END_IF
            WAIT_FRAMES(1)
            SET_VALUE(LW(14), 5)
        END_LOOP
#if VERSION >= VERSION_US
        DEBUG_PUT_MSG(STRING("イベント終了"))
#else
        DEBUG_PUT_MSG(STRING("イベント終了"))
#endif
    END_SIBLING_EVENT
    // Wait for the command and the throws to finish, refill Star Power (retail only) and end the turn.
    CALL(btlevtcmd_ResultAC)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    LABEL(90)
#if VERSION >= VERSION_US
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
#endif
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Spawned by Bomb Squad for each bomb (LW(3)): flies it along the arc given by the angle LW(0) and power LW(1),
 * then bounces it to a stop, deletes it if it landed off the stage, and starts its fuse sizzle.
 */
EVT_BEGIN(_shot_bomb_event)
    CALL(_shot_move, LW(3), LW(0), LW(1), LW(0), LW(1), LW(2), LW(5))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(6.399414f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.5f))
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), 16, -1)
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(3.5996094f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_JumpPosition, LW(3), LW(0), LW(1), LW(2), 12, -1)
    SET_FLOAT_VALUE(LW(6), LW(5))
    MULTIPLY_FLOAT(LW(6), FLOAT(4.0f))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetFaceDirection, LW(3), LW(0))
        MULTIPLY(LW(0), -18)
        CALL(btlevtcmd_SetRotateOffset, LW(3), 0, 7, 0)
        LOOP(20)
            CALL(btlevtcmd_AddRotate, LW(3), 0, 0, LW(0))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, LW(3), 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_MovePosition, LW(3), LW(0), LW(1), LW(2), 20, -1, 0)
    CALL(_judge_on_stage, LW(3), LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_KillUnit, LW(3), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("B_2"))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_BOMB1"), LW(0))
    CALL(btlevtcmd_SetUnitWork, LW(3), 1, LW(0))
    WAIT_MS(400)
    CALL(btlevtcmd_StartWaitEvent, LW(3))
    RETURN
EVT_END()

/** Bobbery's Appeal (data tag 5): appeal pose and sound, then the audience is fired up. */
EVT_BEGIN(sanders_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_APPEAL)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
    DIVIDE(LW(6), 2)
    ADD(LW(1), LW(6))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
#else
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 10, 13)
#endif
    CALL(btlevtcmd_StageDispellFog)
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Victory reaction (data tag 64): Bobbery's Y_1 pose for 48 frames. */
static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("Y_1"))
    WAIT_FRAMES(48)
    RETURN
EVT_END()

/**
 * Audience-attack reaction (data tag 6): Bobbery runs offstage, reappears in the audience,
 * lights his fuse for a second and explodes on the chosen audience member,
 * then is blown up off the screen and falls back home.
 */
static EVT_BEGIN(attack_audience_event)
    // Bobbery runs off the side of the stage.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(3), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(4))
    SET_VALUE(LW(8), LW(3))
    MULTIPLY(LW(8), LW(4))
    MULTIPLY(LW(8), -1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(8), LW(1), LW(2), 0, -1, 0)
    WAIT_FRAMES(20)
    // He reappears at the edge of the audience; the camera homes in on the chosen audience member and he walks up.
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageAudienceAreaSize, LW(4), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    SET_VALUE(LW(6), LW(4))
    MULTIPLY(LW(6), LW(5))
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(6), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 13)
    CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, 1, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    // His fuse sizzles for a second, then he explodes on the audience member and the camera shakes.
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK2"), LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_3"))
    WAIT_MS(1000)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
#if VERSION >= VERSION_US
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
#else
#if VERSION <= VERSION_DEMO_US
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK4"), 0)
#else
    CALL(evt_snd_sfxon, STRING("SFX_BTL_THUNDERS_ATTACK3"), 0)
#endif
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_eff, STRING(""), STRING("sandars"), 3, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
#else
    CALL(evt_eff64, STRING(""), STRING("bomb_n64"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
#endif
#endif
    CALL(evt_btl_camera_shake_h, 0, 10, 0, 20, 13)
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    BEGIN_SIBLING_EVENT
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(500)
    END_SIBLING_EVENT
    // The blast throws him off the top of the screen and he falls back down to his home spot.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1A"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("J_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.39941406f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 90, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(60)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(8), EVT_NULLPTR)
    ADD(LW(6), LW(8))
    DIVIDE(LW(6), 2)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.25f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data tag 66, run on each unit at the end of the battle:
 * clears Bobbery's Hold Fast status and restores his normal stand pose table. Not in the US demo.
 */
#if VERSION >= VERSION_JP
EVT_BEGIN(sanders_battle_end_event)
    CALL(btlevtcmd_OnOffStatus, BTL_UNIT_SELF, STATUS_HOLD_FAST, 0, 0, 0)
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_sanders_stay))
    RETURN
EVT_END()
#endif

/**
 * Allocates a spare BattleWeapon in the running unit's countersetWeapon slot,
 * which Hold Fast fills per use (_make_counterset_weapon). Run from init_event.
 */
static USER_FUNC(_sanders_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

/**
 * Builds Bobbery's battle move list (data tag 1):
 * Bomb and Bomb Squad always, Hold Fast from Super rank and Bob-ombast from Ultra rank,
 * appending each to command->weapon and advancing *count.
 */
static void __makeTechMenuFunc(BattleCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->weapon[*count].index = -1;
    command->weapon[*count].itemId = 0;
    command->weapon[*count].weapon = &partyWeapon_SandersNormalAttack;
    command->weapon[*count].enabled = 0;
    command->weapon[*count].icon = command->weapon[*count].weapon->icon;
    command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
    (*count)++;

    if (techLv >= 0) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_SandersTimeBombSet;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_SandersCounterSet;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_SandersSuperBombAttack;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
}

/**
 * Returns in args[3]-args[5] where Bobbery should stand to hit target unit args[1]:
 * its position plus its bintaHitOffset (scaled by size, X mirrored by facing).
 * args[0] and args[2] (the part) are read but not used.
 */
static USER_FUNC(_get_bomb_hit_position) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    Vec pos;
    s32 id, targetId, dir;
    s32 outZ, outX, outY;

    id = evtGetValue(event, args[0]);
    targetId = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    BattleGetUnitPtr(wp, BattleTransID(event, id));
    unit = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    dir = unit->faceDirection;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += dir * (unit->bintaHitOffset.x * unit->sizeMultiplier);
    pos.y += unit->bintaHitOffset.y * unit->sizeMultiplier;
    pos.z += unit->bintaHitOffset.z * unit->sizeMultiplier;
    evtSetFloat(event, outX, pos.x);
    evtSetFloat(event, outY, pos.y);
    evtSetFloat(event, outZ, pos.z);
    return EVT_RETURN_DONE;
}

/**
 * Copies the weapon pointed to by args[0] into the unit's spare weapon,
 * sets its Hold Fast duration (holdFastTime) to args[1] turns, and writes the copy's address back into args[0].
 */
static USER_FUNC(_make_counterset_weapon) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id, value;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    value = evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    weapon->holdFastTime = value;
    evtSetValue(event, index, (EvtWord)weapon);
    return EVT_RETURN_DONE;
}

/**
 * Moves thrown bomb args[0] one frame along a ballistic arc launched at angle args[1] (degrees from vertical)
 * with power args[2] / 10, until it reaches the floor.
 * Then returns the landing point in args[3]-args[5] and its horizontal speed in args[6] for the bounces.
 */
static USER_FUNC(_shot_move) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    f32 speed, floor;
    s32 id, angle, outX, outY, outZ, outSpeed;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    angle = evtGetValue(event, args[1]);
    speed = 0.1f * evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    outSpeed = args[6];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        f32 x, y, z;

        BtlUnit_GetPos(unit, &x, &y, &z);
        unit->moveCurrentPos.x = x;
        unit->moveCurrentPos.y = y;
        unit->moveCurrentPos.z = z;
        unit->moveAngle = angleABf(0.0f, 0.0f, 1.0f, 0.0f);
        unit->fallAccel = 0.2f;
        unit->moveSpeedY = 0.8f * (0.9f * (speed * cosfd(angle)));
        unit->moveSpeedXZ = 0.8f * (0.75f * (speed * sinfd(angle)));
    }
    unit->moveCurrentPos.y += unit->moveSpeedY;
    unit->moveSpeedY -= unit->fallAccel;
    btlMovePos(unit->moveSpeedXZ, unit->moveAngle, &unit->moveCurrentPos.x, &unit->moveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->moveCurrentPos.x, unit->moveCurrentPos.y, unit->moveCurrentPos.z);
    floor = BattleGetFloorHeight(wp, unit->moveCurrentPos.x, unit->moveCurrentPos.y, unit->moveCurrentPos.z);
    if (unit->moveCurrentPos.y > floor) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_SetPos(unit, unit->moveCurrentPos.x, floor, unit->moveCurrentPos.z);
    evtSetValue(event, outX, unit->moveCurrentPos.x);
    evtSetValue(event, outY, floor);
    evtSetValue(event, outZ, unit->moveCurrentPos.z);
    evtSetFloat(event, outSpeed, unit->moveSpeedXZ);
    return EVT_RETURN_YIELD;
}

/**
 * Returns in args[1] whether unit args[0] is on the stage:
 * TRUE when its X is within the stage half-width plus 40. Bomb Squad removes bombs that land outside.
 */
static USER_FUNC(_judge_on_stage) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleStage* stage;
    f32 z, y, x;
    s32 id, index;

    stage = BattleStageGetPtr();
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    index = args[1];
    BtlUnit_GetPos(BattleGetUnitPtr(wp, id), &x, &y, &z);
    if (__fabs(x) < 40.0f + stage->stageSizeX) {
        evtSetValue(event, index, TRUE);
    } else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}
