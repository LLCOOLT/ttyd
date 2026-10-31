// Battle unit data and scripts for Koops (Nokotarou) as a partner.
#include "version.h"
#include "icon_ids.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "eff/eff_nokotarou.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_attack_audience.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_sub.h"
#include "unit/unit_koura.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"

static USER_FUNC(_check_guard_koura);
static USER_FUNC(_tsuranuki_effect_control);
static USER_FUNC(_color_lv_set);
static USER_FUNC(_check_mario_move_count);
static void __makeTechMenuFunc(BattleCommand* command, s32* count);

PoseTableEntry pose_table_nokotarou_stay[26];
PoseTableEntry pose_table_nokotarou_turn[12];
#if VERSION <= VERSION_DEMO_US
static BattleDataEntry data_table[11];
#else
static BattleDataEntry data_table[12];
#endif
BattleUnitKindPart unitpartsdata_Party_Nokotarou[1];
BattleUnitKind unitdata_Party_Nokotarou;
static EvtWord init_event[78];
extern EvtWord change_party_spawn_init_event[];
static EvtWord dmg_turn_event[65];
static EvtWord wakeup_event[67];
BattleWeapon partyWeapon_NokotarouFirstAttack;
BattleWeapon partyWeapon_NokotarouKouraAttack;
BattleWeapon partyWeapon_NokotarouSyubibinKoura;
BattleWeapon partyWeapon_NokotarouKouraGuard;
BattleWeapon partyWeapon_NokotarouTsuranukiKoura;
extern EvtWord partyNokotarouAttack_FirstAttack[];
extern EvtWord partyNokotarouAttack_NormalAttack[];
extern EvtWord partyNokotarouAttack_SyubibinKoura[];
extern EvtWord partyNokotarouAttack_KouraGuard[];
extern EvtWord partyNokotarouAttack_TsuranukiKoura[];
extern EvtWord nokotarou_appeal_event[];
static EvtWord party_win_reaction[16];
static EvtWord attack_audience_event[263];
#if VERSION >= VERSION_JP
extern EvtWord nokotarou_revive_event[];
#endif
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitDefense defence_turn;
static StatusVulnerability regist;
static EvtWord damage_event[10];
static EvtWord attack_event[2];
static EvtWord wait_event[6];
BattleUnitSetup entry_koura;

static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static BattleUnitDefense defence_turn = {0};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

PoseTableEntry pose_table_nokotarou_stay[] = {
    {9, "PNK_D_5"},
    {2, "PNK_D_5"},
    {3, "PNK_X_1"},
    {4, "PNK_D_2"},
    {5, "PNK_X_1"},
    {1, "PNK_N_1"},
    {27, "PNK_D_3"},
    {28, "PNK_S_1"},
    {37, "PNK_G_2"},
    {31, "PNK_G_1"},
    {39, "PNK_D_1"},
    {40, "PNK_W_1"},
    {42, "PNK_R_1"},
    {50, "PNK_A_1"},
    {57, "PNK_D_2"},
    {56, "PNK_D_2"},
    {BTL_POSE_ESCAPE_FAIL, "PNK_D_4"},
    {BTL_POSE_ESCAPE_FAIL_END, "PNK_X_1"},
    {BTL_POSE_TALK, "PNK_T_1"},
    {52, "PNK_I_1"},
    {BTL_POSE_COMMAND_WAIT, "PNK_C_1"},
    {BTL_POSE_APPEAL, "PNK_O_1"},
    {BTL_POSE_ZERO_GRAVITY, "PNK_X_1"},
    {49, "PNK_A_1"},
    {45, "PNK_G_1"},
    {BTL_POSE_STAY_DEFAULT, "PNK_S_1"},
};

PoseTableEntry pose_table_nokotarou_turn[] = {
    {9, "PNK_D_5"},
    {2, "PNK_D_5"},
    {1, "PNK_N_2"},
    {27, "PNK_D_3"},
    {28, "PNK_H_1"},
    {31, "PNK_D_1"},
    {39, "PNK_D_1"},
    {57, "PNK_H_1"},
    {56, "PNK_H_1"},
    {BTL_POSE_ZERO_GRAVITY, "PNK_H_1"},
    {45, "PNK_H_1"},
    {BTL_POSE_STAY_DEFAULT, "PNK_H_1"},
};

static BattleDataEntry data_table[] = {
    {5, nokotarou_appeal_event},
    {6, attack_audience_event},
    {4, change_party_spawn_init_event},
    {13, dmg_turn_event},
    {1, __makeTechMenuFunc},
    {2, wakeup_event},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
#if VERSION >= VERSION_JP
    {67, nokotarou_revive_event},
#endif
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Nokotarou[] = {
    {1, "btl_un_nokotarou", "c_pnk", 0.0f, 0.0f, 0.0f, 12.0f, 30.0f, 5.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER | PART_ATTR_SHELLED, 0, pose_table_nokotarou_stay},
};

BattleUnitKind unitdata_Party_Nokotarou = {
    225,
    "btl_un_nokotarou",
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
    14,
    36,
    0.0f,
    12.0f,
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
    unitpartsdata_Party_Nokotarou,
    init_event,
    data_table,
};

/**
 * Koops's battle entry: starts 250 units behind his home spot and, after 40 frames,
 * runs in to it at speed 4 with his footstep sounds, then takes his stay pose.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 9, 9, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Init for Koops: registers his wait, attack, damage, confusion and entry scripts and his walk,
 * run and jump sounds; clears the shell-spin work (unit work 0-1, part work 0 and 2)
 * and sets the Shell Toss spin sound's top pitch (unit work 4 = 3410, scaled by the charge in unit work 5).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 3410)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 2, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 9, 3)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Hit reaction: the default damage script with no special pose (LW10 = -2). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Run when Koops is switched into battle (data tag 4):
 * if he was still flipped on his back (overturn count 1 or more),
 * restores the flipped defence and pose tables and flag, then starts his pose from the table.
 */
EVT_BEGIN(change_party_spawn_init_event)
    CALL(btlevtcmd_GetOverTurnCount, BTL_UNIT_PARTNER, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_PARTNER, 1, PTR(&defence_turn))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_PARTNER, 1, PTR(pose_table_nokotarou_turn))
        CALL(btlevtcmd_OnStatusFlag, BTL_UNIT_PARTNER, STATUS_FLAG_FLIPPED)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_PARTNER, 1)
    RETURN
EVT_END()

/**
 * Flipped reaction (data tag 13): Koops lands on his back for 2 turns,
 * with the flipped defence and pose tables and the flipped status flag;
 * drops any Defend, plays the status sound and bounces twice.
 */
static EVT_BEGIN(dmg_turn_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence_turn))
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_turn))
    CALL(btlevtcmd_OnStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), 2)
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_D_1"))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_DEFENDING)
    CALL(evt_snd_sfxon, STRING("SFX_CONDITION_INSIDE"), 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 6, -1)
    RETURN
EVT_END()

/**
 * Turn-start recovery while flipped (data tag 2): counts the flip down;
 * when it reaches 0 restores his normal defence and pose table,
 * clears the flipped flag and hops back onto his feet.
 */
static EVT_BEGIN(wakeup_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetOverTurnCount, LW(10), LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetOverTurnCount, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_stay))
    CALL(btlevtcmd_AnimeChangePose, LW(10), LW(11), STRING("PNK_S_1"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Empty: partner moves come from the player's menu choices, not a unit attack script. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/** Idle: plays the stay pose from the current pose table (normal or flipped). */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

BattleWeapon partyWeapon_NokotarouFirstAttack = {
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
    1, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {2, 2, 3, 3, 5, 5, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_ALWAYS_HITS | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyNokotarouAttack_FirstAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon partyWeapon_NokotarouKouraAttack = {
    "btl_wn_pnk_normal", // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pnk_normal_attack", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 2, 2, 3, 3, 5, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_hammer", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyNokotarouAttack_NormalAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 4, 2, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 2, 2, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

BattleWeapon partyWeapon_NokotarouSyubibinKoura = {
    "btl_wn_pnk_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pnk_syubibin_koura", // description
    100, // baseAccuracy
    3, // baseFpCost
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
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 2, 2, 3, 3, 5, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    8, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_koura_shubibin", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyNokotarouAttack_SyubibinKoura, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

BattleWeapon partyWeapon_NokotarouKouraGuard = {
    "btl_wn_pnk_lv2", // name
#if VERSION >= VERSION_US
    346, // icon
#else
    338, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pnk_koura_no_mamori", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0, 2, 2, 3, 3, 4, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_ONLY_MARIO | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_koura_no_mamori", // acHelpMsg
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
    partyNokotarouAttack_KouraGuard, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon partyWeapon_NokotarouTsuranukiKoura = {
    "btl_wn_pnk_lv3_tsuranuki", // name
#if VERSION >= VERSION_US
    347, // icon
#else
    339, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pnk_koura_tsuranuki", // description
    100, // baseAccuracy
    6, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
#if VERSION >= VERSION_US
    1, // stylishCommandMultiplier
#else
    3, // stylishCommandMultiplier
#endif
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetACOutputParam, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_tsuranuki_koura", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyNokotarouAttack_TsuranukiKoura, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

/** Withdraws Koops into his shell for Shell Toss: shell pose PNK_K_2, spinning 15 degrees a frame for 24 frames. */
static EVT_BEGIN(_change_koura_pose)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_2"))
    LOOP(18)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

/**
 * Quicker shell withdraw for Shell Slam: a smoke puff, a 10-frame spin at 27 degrees a frame, 3 more at 30,
 * and a second puff.
 */
static EVT_BEGIN(_change_koura_pose_fast)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_2"))
    LOOP(10)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 27, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_1"))
    LOOP(3)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 30, 0)
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Pops Koops back out of his shell: stops the spin loop (unit work 0 = 0),
 * resets his rotation and turns him through two short spins while switching shell poses.
 */
static EVT_BEGIN(_restore_koura_pose)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_1"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_2"))
    LOOP(6)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
    END_LOOP
    RETURN
EVT_END()

/**
 * Starts the shell-spin loop in an inline event.
 * LW0 is the starting spin speed and unit work 1 the target speed in degrees per frame (negative = the other
 * way); the speed moves 1 a frame toward it, unit work 2 set reverses it,
 * and with part work 0 set a smoke puff appears each turn. Runs until unit work 0 is cleared.
 */
static EVT_BEGIN(_koura_rotate_start)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
    BEGIN_INLINE_EVENT
        LABEL(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(1))
        IF_INT_EQUAL(LW(1), 0)
            GOTO(10)
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(11))
        IF_INT_NOT_EQUAL(LW(11), 0)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, 0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(10))
            MULTIPLY(LW(10), -1)
            MULTIPLY(LW(0), -1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(10))
        END_IF
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(10))
        IF_INT_GREATER_OR_EQUAL(LW(10), 0)
            ADD(LW(0), 1)
            IF_INT_GREATER(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
            CALL(btlevtcmd_GetRotate, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
            IF_INT_LESS(LW(1), LW(0))
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, 0, LW(1))
                IF_INT_NOT_EQUAL(LW(1), 0)
                    BEGIN_SIBLING_EVENT
                        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                        CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
                    END_SIBLING_EVENT
                END_IF
            END_IF
        ELSE
            SUBTRACT(LW(0), 1)
            IF_INT_LESS(LW(0), LW(10))
                SET_VALUE(LW(0), LW(10))
            END_IF
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, LW(0), 0)
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, 1, 0, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                BEGIN_SIBLING_EVENT
                    MULTIPLY(LW(0), -1)
                    CALL(btlevtcmd_GetRotate, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
                    ADD(LW(1), 360)
                    IF_INT_LESS(LW(1), LW(0))
                        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
                        CALL(evt_eff, 0, STRING("kemuri_test"), 5, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
                    END_IF
                END_SIBLING_EVENT
            END_IF
        END_IF
        WAIT_FRAMES(1)
        GOTO(0)
        LABEL(10)
    END_INLINE_EVENT
    RETURN
EVT_END()

/** Stops the shell-spin loop (unit work 0 = 0) and resets Koops's rotation. */
static EVT_BEGIN(_koura_rotate_stop)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Koops's first strike, used when he hits an enemy in the field to start the battle:
 * he spins in his shell from offstage into the first-attack target, bounces back and returns home.
 */
EVT_BEGIN(partyNokotarouAttack_FirstAttack)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&partyWeapon_NokotarouFirstAttack))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(3), BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    SET_VALUE(LW(0), 45)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
    CALL_CHILD(_koura_rotate_start)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(5), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_ATTACK2"), 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL_CHILD(_koura_rotate_stop)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&partyWeapon_NokotarouFirstAttack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&partyWeapon_NokotarouFirstAttack), 131328, LW(5))
    SET_VALUE(LW(0), 45)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
    CALL_CHILD(_koura_rotate_start)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL_CHILD(_koura_rotate_stop)
    CALL_CHILD(_restore_koura_pose)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Koops's Shell Toss: he spins in his shell along the ground into the front enemy,
 * the action command (charging the spin) setting the damage, then bounces back home.
 */
EVT_BEGIN(partyNokotarouAttack_NormalAttack)
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
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL_CHILD(_change_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_ATTACK1"), LW(13))
    SET_VALUE(LW(0), 15)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
    CALL_CHILD(_koura_rotate_start)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 360)
        SET_VALUE(LW(1), 100)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 280)
        SET_VALUE(LW(1), 150)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 240)
        SET_VALUE(LW(1), 200)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 200)
        SET_VALUE(LW(1), 250)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 200)
        SET_VALUE(LW(1), 360)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 200)
        SET_VALUE(LW(1), 600)
        CASE_DEFAULT
        SET_VALUE(LW(0), 200)
        SET_VALUE(LW(1), 960)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 2, LW(0), 0, 1, LW(1), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 3)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 19, 1, 60)
    WAIT_FRAMES(22)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        LOOP(10000)
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(6), 0)
        LOOP(10000)
            ADD(LW(6), 1)
            IF_INT_GREATER(LW(6), 100)
                SET_VALUE(LW(6), 100)
            END_IF
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, LW(6))
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(1))
            MULTIPLY(LW(0), LW(1))
            DIVIDE(LW(0), 100)
            CALL(evt_snd_sfx_pit, LW(13), LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_ATTACK2"), 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, LW(13))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(13), 0, 0)
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
        CALL(btlevtcmd_StopAC)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL_CHILD(_koura_rotate_stop)
        CALL_CHILD(_restore_koura_pose)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        WAIT_FRAMES(30)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_CommandPreCheckCounter, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL_CHILD(_koura_rotate_stop)
    END_IF
#endif
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 17, 17, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
#if VERSION >= VERSION_US
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
#endif
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 10, 0)
        LOOP(9)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, 20)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 180, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_2"))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
            LABEL(91)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                GOTO(92)
            END_IF
            SUBTRACT(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(0))
            WAIT_FRAMES(2)
            GOTO(91)
            LABEL(92)
        END_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 60, 90, 90, 0)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
        IF_INT_EQUAL(LW(6), 1)
            GOTO(94)
        END_IF
        IF_INT_NOT_EQUAL(LW(6), 2)
            GOTO(94)
        END_IF
        CALL_CHILD(_koura_rotate_stop)
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_3"))
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
        END_LOOP
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        WAIT_FRAMES(60)
        GOTO(95)
        LABEL(94)
        CALL_CHILD(_koura_rotate_stop)
        CALL(evt_audience_acrobat_notry)
        CALL_CHILD(_restore_koura_pose)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        WAIT_FRAMES(30)
        GOTO(95)
    END_IF
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL_CHILD(_restore_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    WAIT_FRAMES(30)
    LABEL(95)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Koops's Power Shell: he spins in his shell and sweeps through every enemy on the ground,
 * the action command deciding the damage, then returns home.
 */
EVT_BEGIN(partyNokotarouAttack_SyubibinKoura)
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
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    WAIT_FRAMES(20)
    CALL_CHILD(_change_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_SHUBIBIN1"), LW(13))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    SET_VALUE(LW(0), 15)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
    CALL_CHILD(_koura_rotate_start)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 480)
        SET_VALUE(LW(1), 240)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 300)
        SET_VALUE(LW(1), 180)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 240)
        SET_VALUE(LW(1), 120)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 180)
        SET_VALUE(LW(1), 105)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 150)
        SET_VALUE(LW(1), 90)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 60)
        CASE_DEFAULT
        SET_VALUE(LW(0), 100)
        SET_VALUE(LW(1), 30)
    END_SWITCH
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_AcSetParamAll, 2, LW(0), 1, 95, LW(1), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
#else
    CALL(btlevtcmd_AcSetParamAll, 2, LW(0), 1, 90, LW(1), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
#endif
    CALL(btlevtcmd_AcSetFlag, 3)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 19, 1, 60)
    WAIT_FRAMES(22)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        LOOP(10000)
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(6), 0)
        LOOP(10000)
            ADD(LW(6), 1)
            IF_INT_GREATER(LW(6), 200)
                SET_VALUE(LW(6), 200)
            END_IF
            SET_VALUE(LW(7), LW(6))
            DIVIDE(LW(7), 2)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, LW(7))
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(1))
            MULTIPLY(LW(0), LW(1))
            DIVIDE(LW(0), 100)
            CALL(evt_snd_sfx_pit, LW(13), LW(0))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_SHUBIBIN2"), 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(5), LW(5))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
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
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_CommandPreCheckCounter, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL_CHILD(_koura_rotate_stop)
    END_IF
#endif
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(80)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, 400, LW(1), LW(2), 0, 0, 0)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    MULTIPLY(LW(0), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 9, 9, 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
#if VERSION >= VERSION_US
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
#endif
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 12)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_1"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 49, 79, 79, 0)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
        IF_INT_NOT_EQUAL(LW(6), 2)
            CALL_CHILD(_koura_rotate_stop)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_2"))
            LOOP(6)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
            END_LOOP
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_S_1"))
            LOOP(6)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
            END_LOOP
            CALL(evt_audience_acrobat_notry)
            GOTO(99)
        END_IF
        CALL_CHILD(_koura_rotate_stop)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_2"))
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_3"))
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
        END_LOOP
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        WAIT_FRAMES(60)
        GOTO(99)
    END_IF
    CALL_CHILD(_restore_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleUnitSetup entry_koura = {
    &unit_koura, // unitKindParams
    0, // alliance
    {0}, // pad_05
    BATTLE_PHASE_BEFORE_PLAYER, // attackPhase
    {1000.0f, 0.0f, 1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Koops's Shell Shield: removes any existing shell,
 * then drops a new shell unit (unit_koura) over Mario whose HP the action command sets.
 * Mario is hidden and untargetable inside it; if he still has a move, the shell opens again.
 */
EVT_BEGIN(partyNokotarouAttack_KouraGuard)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(_check_guard_koura, BTL_UNIT_MARIO, LW(10))
    IF_INT_NOT_EQUAL(LW(10), -1)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 62)
    END_IF
    CALL(_color_lv_set, BTL_UNIT_MARIO, 0, LW(14))
    CALL(_color_lv_set, BTL_UNIT_MARIO, 1, 255)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_A_2"))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_SpawnUnit, LW(10), PTR(&entry_koura), 0)
    CALL(btlevtcmd_OnAttribute, LW(10), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    ADD(LW(1), 240)
    CALL(btlevtcmd_SetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OffAttribute, LW(10), UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_GetBodyId, LW(10), LW(11))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 360)
        SET_VALUE(LW(1), 480)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 180)
        SET_VALUE(LW(1), 360)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 300)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 90)
        SET_VALUE(LW(1), 240)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 70)
        SET_VALUE(LW(1), 200)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 40)
        SET_VALUE(LW(1), 120)
        CASE_DEFAULT
        SET_VALUE(LW(0), 20)
        SET_VALUE(LW(1), 80)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 1, LW(10), LW(11), 30, LW(0), LW(1), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 12, 1, 0)
#if VERSION == VERSION_EU
    WAIT_FRAMES(2)
#endif
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 125)
    CALL(btlevtcmd_DivePosition, LW(10), LW(0), LW(1), LW(2), 60, 0, 13, 0, -1)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_GetResultAC, LW(6))
    IF_INT_EQUAL(0, 0)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(10)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_N_7"))
            WAIT_FRAMES(35)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_B_1"))
            WAIT_FRAMES(15)
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_MARIO, 1, 43)
        END_SIBLING_EVENT
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
        CALL(evt_btl_camera_set_zoom, 0, 400)
        CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
        CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.39941406f))
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        ADD(LW(2), 5)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_NOKO_GUARD2"), EVT_NULLPTR, 0, LW(5))
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(2)
            CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 48, 67, 67, 0)
            CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
            IF_INT_EQUAL(LW(6), 2)
                CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_O_1"))
                WAIT_MS(1000)
            ELSE
                CALL(evt_audience_acrobat_notry)
            END_IF
        END_SIBLING_EVENT
        CALL(btlevtcmd_FallPosition, LW(10), LW(0), LW(1), LW(2), 60)
        CALL(evt_snd_sfxoff, LW(5))
        CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("PKO_F_1"))
        CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_NOKO_GUARD1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
        CALL(btlevtcmd_WeaponAftereffect, LW(12))
        BEGIN_SIBLING_EVENT
            SET_VALUE(LW(9), LW(10))
            CALL(btlevtcmd_GetRotate, LW(9), EVT_NULLPTR, EVT_NULLPTR, LW(8))
            IF_INT_LESS(LW(8), 180)
                CALL(evt_sub_intpl_init, 11, LW(8), 0, 50)
            ELSE
                CALL(evt_sub_intpl_init, 11, LW(8), 360, 50)
            END_IF
            LOOP(50)
                CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
                CALL(btlevtcmd_SetRotate, LW(9), EVT_NULLPTR, EVT_NULLPTR, LW(1))
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        IF_BITS_SET(LW(6), 2)
            CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
            SWITCH(LW(0))
                CASE_GREATER_OR_EQUAL(8)
                SET_VALUE(LW(0), 2)
                CASE_GREATER_OR_EQUAL(6)
                SET_VALUE(LW(0), 1)
                CASE_GREATER_OR_EQUAL(4)
                SET_VALUE(LW(0), 0)
                CASE_DEFAULT
                SET_VALUE(LW(0), -1)
            END_SWITCH
            IF_INT_GREATER_OR_EQUAL(LW(0), 0)
#if VERSION == VERSION_EU
                CALL(btlevtcmd_GetResultPrizeLv, BTL_UNIT_NONE, LW(0), LW(7))
#else
                CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(7))
#endif
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_ACSuccessEffect, LW(7), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(7))
            ELSE
                CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
            END_IF
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
        WAIT_FRAMES(50)
        CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_SHELL_SHIELDED)
        CALL(btlevtcmd_GetUnitId, LW(3), LW(0))
        CALL(btlevtcmd_SetUnitWork, LW(10), 0, LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        CALL(btlevtcmd_SetUnitWork, LW(10), 2, 3)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            SET_VALUE(LW(5), 5)
            LOOP(LW(5))
                CALL(btlevtcmd_GetUnitWork, LW(10), 2, LW(10))
                IF_INT_NOT_EQUAL(LW(0), 3)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
                SET_VALUE(LW(5), 5)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        CALL(btlevtcmd_SetUnitWork, LW(10), 2, 0)
        IF_BITS_SET(LW(6), 2)
            CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
        ELSE
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
        END_IF
        CALL(btlevtcmd_SetHp, LW(10), LW(0))
        CALL(btlevtcmd_RunDataEventChild, LW(10), 61)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), 1, 43)
        CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_SHELL_SHIELDED | UNIT_ATTR_NOT_SAMPLED_AS_TARGET)
#if VERSION >= VERSION_JP
        CALL(btlevtcmd_StartWaitEvent, LW(3))
#endif
        CALL(_check_mario_move_count, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
            CALL(evt_btl_camera_off_posoffset_manual, 0)
            WAIT_MS(500)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 59)
            WAIT_FRAMES(60)
        END_IF
        CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
        CALL(evt_btl_camera_off_posoffset_manual, 0)
        RETURN
    END_IF
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_N_7"))
        WAIT_FRAMES(35)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_MARIO, 1, STRING("M_B_1"))
        WAIT_FRAMES(150)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_MARIO, 1, 43)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_NOKO_GUARD2"), EVT_NULLPTR, 0, LW(5))
    CALL(btlevtcmd_SetFallAccel, LW(10), FLOAT(0.39941406f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_FallPosition, LW(10), LW(0), LW(1), LW(2), 60)
    CALL(btlevtcmd_SetHomePos, LW(10), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxoff, LW(5))
    CALL(evt_btl_camera_shake_h, 0, 2, 0, 10, 13)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("PKO_F_1"))
    WAIT_FRAMES(50)
    CALL(btlevtcmd_AnimeChangePose, LW(10), 1, STRING("PKO_H_1"))
    CALL(btlevtcmd_AnimeChangePose, LW(10), 2, STRING("PKO_H_2"))
    CALL(btlevtcmd_OffPartsAttribute, LW(10), 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_SetPartsRotateOffset, LW(10), 1, 20, 0, 0)
    CALL(btlevtcmd_SetPartsRotateOffset, LW(10), 2, -20, 0, 0)
    LOOP(20)
        CALL(btlevtcmd_AddPartsRotate, LW(10), 1, 0, 0, 2)
        CALL(btlevtcmd_AddPartsRotate, LW(10), 2, 0, 0, -2)
        WAIT_FRAMES(1)
    END_LOOP
    LOOP(10)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 1, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OnPartsAttribute, LW(10), 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 1, PART_ATTR_HIDDEN)
        CALL(btlevtcmd_OffPartsAttribute, LW(10), 2, PART_ATTR_HIDDEN)
        WAIT_FRAMES(2)
    END_LOOP
    CALL(btlevtcmd_KillUnit, LW(10), 0)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_off_posoffset_manual, 0)
    CALL(_color_lv_set, BTL_UNIT_MARIO, 1, LW(14))
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Koops's Shell Slam: he charges a spin with the action command (_tsuranuki_effect_control grows the effect with
 * the charge level) and slams through every ground enemy, ignoring defence, then returns home.
 */
EVT_BEGIN(partyNokotarouAttack_TsuranukiKoura)
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
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    WAIT_FRAMES(20)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 25)
        SET_VALUE(LW(1), 15)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 24)
        SET_VALUE(LW(1), 21)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 22)
        SET_VALUE(LW(1), 24)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 20)
        SET_VALUE(LW(1), 25)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 17)
        SET_VALUE(LW(1), 27)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 15)
        SET_VALUE(LW(1), 30)
        CASE_DEFAULT
        SET_VALUE(LW(0), 12)
        SET_VALUE(LW(1), 30)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 7, 200, 178, LW(0), LW(1), 20, 61, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100)
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 6, 1, 0)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, -1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        LABEL(5)
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            WAIT_FRAMES(1)
            GOTO(5)
        END_IF
        CALL_CHILD(_change_koura_pose_fast)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, 1)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
        CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_IPPATSU1"), LW(13))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, LW(13))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
        SET_VALUE(LW(0), 15)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 15)
        CALL_CHILD(_koura_rotate_start)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        CALL(_tsuranuki_effect_control, BTL_UNIT_SELF)
    END_SIBLING_EVENT
    CALL(btlevtcmd_StartAC, 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        SET_VALUE(LW(5), 5)
        LOOP(LW(5))
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
            SWITCH(LW(0))
                CASE_LESS_OR_EQUAL(1)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 1, 0)
                CASE_EQUAL(2)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 1, 1)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 24)
                CASE_EQUAL(3)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 1, 2)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 36)
                CASE_EQUAL(4)
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 1, 3)
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
            END_SWITCH
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(13))
            IF_INT_NOT_EQUAL(LW(13), -1)
                CALL(btlevtcmd_AcGetOutputParam, 1, LW(1))
                CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, LW(1))
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 5, LW(1))
                MULTIPLY(LW(0), LW(1))
                DIVIDE(LW(0), 100)
                CALL(evt_snd_sfx_pit, LW(13), LW(0))
            END_IF
            WAIT_FRAMES(1)
            SET_VALUE(LW(5), 5)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_ResultAC)
    DELETE_EVENT(LW(14))
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        DELETE_EVENT(LW(15))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_2"))
        LOOP(10)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 12, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_K_1"))
        LOOP(16)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 20, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_H_1"))
        LOOP(14)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 20, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(evt_snd_sfxon, STRING("SFX_BTL_ACROBAT_SHAKE1"), 0)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 2, 1)
        CALL_CHILD(_restore_koura_pose)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        WAIT_FRAMES(30)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(13))
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_IPPATSU2"), 0)
    CALL(btlevtcmd_StopAC)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 5, 0)
    CALL(evt_snd_sfxoff, LW(13))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_SHUBIBIN2"), 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
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
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 0)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_CommandPreCheckCounter, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 2, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL_CHILD(_koura_rotate_stop)
    END_IF
#endif
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_AcGetOutputParam, 2, LW(9))
        IF_INT_GREATER_OR_EQUAL(LW(9), 4)
            SUBTRACT(LW(9), 4)
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(9), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
        ELSE
            CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
        END_IF
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(80)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, 400, LW(1), LW(2), 0, 0, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 1, 2, 1)
    WAIT_MS(100)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    MULTIPLY(LW(0), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 9, 9, 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
#if VERSION >= VERSION_US
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
#endif
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 12)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_1"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 49, 79, 79, 0)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
        IF_INT_NOT_EQUAL(LW(6), 2)
            CALL(evt_audience_acrobat_notry)
            CALL_CHILD(_koura_rotate_stop)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_2"))
            LOOP(6)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
            END_LOOP
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_S_1"))
            LOOP(6)
                WAIT_FRAMES(1)
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
            END_LOOP
            GOTO(99)
        END_IF
        CALL_CHILD(_koura_rotate_stop)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_2"))
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 45, 0)
        END_LOOP
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_E_3"))
        LOOP(6)
            WAIT_FRAMES(1)
            CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 15, 0)
        END_LOOP
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        WAIT_FRAMES(60)
        GOTO(99)
    ELSE
        CALL(evt_audience_acrobat_notry)
    END_IF
    CALL_CHILD(_restore_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Koops's Appeal (data tag 5): appeal pose and sound, then the audience is fired up. */
EVT_BEGIN(nokotarou_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_APPEAL)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(58)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Victory reaction (data tag 64): Koops's PNK_Y_1 pose, unless he is still flipped on his back. */
static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 17, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PNK_Y_1"))
    END_IF
    RETURN
EVT_END()

/**
 * Audience-attack reaction (data tag 6): Koops runs offstage, reappears in the audience, spins up in his shell,
 * shoots into the chosen audience member, bounces back out of his shell and runs home.
 */
static EVT_BEGIN(attack_audience_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(3), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(4))
    SET_VALUE(LW(8), LW(3))
    MULTIPLY(LW(8), LW(4))
    MULTIPLY(LW(8), -1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(8), LW(1), LW(2), 0, -1, 0)
    WAIT_FRAMES(20)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageAudienceAreaSize, LW(4), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    SET_VALUE(LW(6), LW(4))
    MULTIPLY(LW(6), LW(5))
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(6), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 12)
    CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, 1, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 50)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(0), 15)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 45)
        CALL_CHILD(_koura_rotate_start)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_MS(1000)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_NOKO_ATTACK2"), 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(8.0f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 15)
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
#else
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
#endif
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(1000)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 8)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 8, -1)
    CALL_CHILD(_restore_koura_pose)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(6), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(8), LW(1), LW(2))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Data tag 67, run on Koops (args in LW(10)/LW(11)) when he is revived:
 * resets his defence and pose tables to the upright ones and clears the flipped flag. Not in the US demo.
 */
#if VERSION >= VERSION_JP
EVT_BEGIN(nokotarou_revive_event)
    CALL(btlevtcmd_SetPartsDefenceTable, LW(10), LW(11), PTR(&defence))
    CALL(btlevtcmd_OffStatusFlag, LW(10), STATUS_FLAG_FLIPPED)
    CALL(btlevtcmd_AnimeSetPoseTable, LW(10), LW(11), PTR(pose_table_nokotarou_stay))
    RETURN
EVT_END()
#endif

/**
 * Builds Koops's battle move list (data tag 1):
 * Shell Toss and Power Shell always (with fixed menu icons),
 * Shell Shield from Super rank and Shell Slam from Ultra rank,
 * appending each to command->weapon and advancing *count.
 */
static void __makeTechMenuFunc(BattleCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->weapon[*count].index = -1;
    command->weapon[*count].itemId = 0;
    command->weapon[*count].weapon = &partyWeapon_NokotarouKouraAttack;
    command->weapon[*count].enabled = 0;
    command->weapon[*count].icon = ICON_150;
    command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
    (*count)++;

    if (techLv >= 0) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_NokotarouSyubibinKoura;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = ICON_151;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_NokotarouKouraGuard;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_NokotarouTsuranukiKoura;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
}

/**
 * Returns Mario's moves remaining this turn in args[0];
 * Shell Shield opens the new shell right away when he still has a move.
 */
static USER_FUNC(_check_mario_move_count) {
    s32 index = event->args[0];
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);

    evtSetValue(event, index, mario->movesRemaining);
    return EVT_RETURN_DONE;
}

/**
 * Reads or writes unit args[0]'s moveColorLv: with args[1] zero it is returned in args[2],
 * otherwise set to args[2].
 * Shell Shield saves Mario's value, sets it to 255 during the move and restores it after.
 */
static USER_FUNC(_color_lv_set) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, index, set, value;

    id = evtGetValue(event, args[0]);
    set = evtGetValue(event, args[1]);
    index = args[2];
    value = evtGetValue(event, index);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (set) {
        unit->moveColorLv = value;
    } else {
        evtSetValue(event, index, unit->moveColorLv);
    }
    return EVT_RETURN_DONE;
}

/**
 * Runs Shell Slam's shell effect on unit args[0] until stopped:
 * spawns it on the first call, follows the unit, and eases its size toward the charge level in part work[1];
 * part work[2] set ends it and deletes the effect.
 */
static USER_FUNC(_tsuranuki_effect_control) {
    BattleWork* wp;
    BattleUnit* unit;
    BattleUnitPart* part;
    EffectEntry* effect;
    Vec pos;
    s32 id, target;

    id = evtGetValue(event, event->args[0]);
    wp = _battleWorkPointer;
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    part = BtlUnit_GetPartsPtr(unit, 1);
    if (isFirstCall) {
        event->userdatap[0] = effNokotarouEntry(0, 1000, pos.x, pos.y, pos.z, unit->sizeMultiplier);
        part->work[2] = 0;
        part->work[1] = 0;
        event->userdata[1] = 0;
    }
    target = part->work[1] * 100;
    if (event->userdata[1] != target) {
        if (event->userdata[1] < target) {
            event->userdata[1] += 10;
            if (event->userdata[1] > target) {
                event->userdata[1] = target;
            }
        } else {
            event->userdata[1] -= 10;
            if (event->userdata[1] < target) {
                event->userdata[1] = target;
            }
        }
    }
    {
        f32 size = (2.0f + 0.006f * event->userdata[1]);

        size *= unit->sizeMultiplier;
        effect = event->userdatap[0];
        ((EffNokotarouWork*)effect->userdata)->position.x = pos.x;
        ((EffNokotarouWork*)effect->userdata)->position.y = pos.y;
        ((EffNokotarouWork*)effect->userdata)->position.z = pos.z;
        ((EffNokotarouWork*)effect->userdata)->size = size;
    }
    if (part->work[2]) {
        part->work[2] = 0;
        effSoftDelete(effect);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/** Returns in args[1] the unit id of the Shell Shield shell covering unit args[0], or -1 when it has none. */
static USER_FUNC(_check_guard_koura) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    BattleUnit* koura;
    s32 id, index;

    id = evtGetValue(event, args[0]);
    index = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (!(unit->attributeFlags & UNIT_ATTR_SHELL_SHIELDED)) {
        evtSetValue(event, index, -1);
        return EVT_RETURN_DONE;
    }
    koura = BtlUnit_GetGuardKouraPtr(unit);
    if (!koura) {
        evtSetValue(event, index, -1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, index, koura->unitId);
    return EVT_RETURN_DONE;
}
