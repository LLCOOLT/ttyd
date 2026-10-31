// Battle unit data and scripts for Flurrie (Clauda) as a partner.
#include "battle/battle.h"
#include "eff/n64/eff_kumokumo_n64.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
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
#include "evt/evt_snd.h"

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "version.h"

static USER_FUNC(_clauda_make_extra_work_area);
static USER_FUNC(_make_kumoguard_weapon);
static USER_FUNC(_get_clauda_kiss_hit_position);
static USER_FUNC(_make_kiss_weapon);
static USER_FUNC(_make_breath_weapon);
static USER_FUNC(_clauda_breath_effect_fire);
static USER_FUNC(_clauda_breath_effect_ready);
static USER_FUNC(_check_blow_rate);
static void __makeTechMenuFunc(BattleCommand* command, s32* count);

BattleWeapon partyWeapon_ClaudaNormalAttack;
BattleWeapon partyWeapon_ClaudaBreathAttack;
BattleWeapon partyWeapon_ClaudaPredationAttack;
BattleWeapon partyWeapon_ClaudaKumogakureAttack;
PoseTableEntry pose_table_clauda_stay[25];
static BattleDataEntry data_table[8];
BattleUnitKindPart unitpartsdata_Party_Clauda[1];
BattleUnitKind unitdata_Party_Clauda;
static EvtWord init_event[60];
static EvtWord damage_event[16];
extern EvtWord partyClaudaAttack_NormalAttack[];
extern EvtWord partyClaudaAttack_BreathAttack[];
extern EvtWord partyClaudaAttack_PredationAttack[];
extern EvtWord partyClaudaAttack_KumoGuard[];
extern EvtWord clauda_appeal_event[];
static EvtWord attack_audience_event[15];
extern EvtWord attack_bad_audience_event[];
extern EvtWord attack_good_audience_event[];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static EvtWord attack_event[2];
static EvtWord wait_event[6];
static EvtWord party_win_reaction[11];

BattleWeapon partyWeapon_ClaudaNormalAttack = {
    "btl_wn_pwd_normal", // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pwd_body_press", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 2, 2, 4, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    10, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_body_press", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyClaudaAttack_NormalAttack, // attackEvtScript
    {0, 20, 20, 100, 20, 10, 2, 5, 10, 0, 0, 0}, // stageEffectRates
};

BattleWeapon partyWeapon_ClaudaBreathAttack = {
    "btl_wn_pwd_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pwd_breath", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {1, 2, 2, 3, 3, 4, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, // element
    25, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_breath", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNUSED_200 | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, // fastChance..frightChance
    100, // galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    partyClaudaAttack_BreathAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

BattleWeapon partyWeapon_ClaudaPredationAttack = {
    "btl_wn_pwd_lv2", // name
#if VERSION >= VERSION_US
    346, // icon
#else
    338, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pwd_sexy_kiss", // description
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
    weaponGetACOutputParam, // hpDamageFn
    {0, 1, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {3, 3, 0, 0, 0, 0, 0, 0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_sexy_kiss", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyClaudaAttack_PredationAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 5, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon partyWeapon_ClaudaKumogakureAttack = {
    "btl_wn_pwd_lv3", // name
#if VERSION >= VERSION_US
    347, // icon
#else
    339, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pwd_kumogakure", // description
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
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_kumogakure", // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, // poisonStrength..electricTime
    100, // dodgyChance
    2, // dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    partyClaudaAttack_KumoGuard, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 5, 0, 0, 0, 0, 0}, // stageEffectRates
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

PoseTableEntry pose_table_clauda_stay[] = {
    {9, "PWD_D_5"},
    {2, "PWD_D_5"},
    {3, "PWD_X_1"},
    {4, "PWD_D_2"},
    {5, "PWD_X_1"},
    {1, "PWD_N_1"},
    {27, "PWD_D_3"},
    {28, "PWD_S_1"},
    {37, "PWD_G_2"},
    {31, "PWD_G_1"},
    {39, "PWD_D_1"},
    {40, "PWD_W_1"},
    {42, "PWD_R_1"},
    {57, "PWD_D_2"},
    {56, "PWD_D_2"},
    {BTL_POSE_ESCAPE_FAIL, "PWD_D_3"},
    {BTL_POSE_ESCAPE_FAIL_END, "PWD_D_2"},
    {BTL_POSE_TALK, "PWD_T_1"},
    {52, "PWD_I_1"},
    {BTL_POSE_COMMAND_WAIT, "PWD_C_1"},
    {BTL_POSE_APPEAL, "PWD_O_1"},
    {BTL_POSE_ZERO_GRAVITY, "PWD_X_1"},
    {49, "PWD_A4_3"},
    {45, "PWD_G_1"},
    {BTL_POSE_STAY_DEFAULT, "PWD_S_1"},
};

static BattleDataEntry data_table[] = {
    {5, clauda_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Clauda[] = {
    {1, "btl_un_clauda", "c_windy", 0.0f, 0.0f, 0.0f, 16.0f, 44.0f, 5.0f, 0.0f, 44.0f, 0.0f, 26, 50, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table_clauda_stay},
};

BattleUnitKind unitdata_Party_Clauda = {
    227,
    "btl_un_clauda",
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
    50,
    16,
    44,
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
    32.5f,
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
    UNIT_ATTR_FLOATING | UNIT_ATTR_NO_HP_GAUGE,
    &regist,
    1,
    unitpartsdata_Party_Clauda,
    init_event,
    data_table,
};

static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBHANG1"), STRING("SFX_PARTY_BATTLE_SUBHANG1"), 0, 9, 3, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(_clauda_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 6, 12, 16)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 8)
    CALL(btlevtcmd_SetDiveSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 9, 8)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT | UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

EVT_BEGIN(partyClaudaAttack_NormalAttack)
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    CALL(btlevtcmd_AcSetParamAll, LW(3), LW(4), 180, LW(0), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 8, 1, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_OffUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(btlevtcmd_GetResultAC, LW(5))
    IF_BITS_CLEAR(LW(5), 2)
        CALL(evt_sub_random, 40, LW(5))
        SUBTRACT(LW(5), 20)
        ADD(LW(0), LW(5))
        CALL(evt_sub_random, 20, LW(5))
        SUBTRACT(LW(5), 10)
        ADD(LW(1), LW(5))
    END_IF
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -1)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        GOTO(20)
    END_IF
    SET_VALUE(LW(5), 1)
    LABEL(10)
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
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_2"))
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_D_3"))
    CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.39941406f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(0.39941406f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    WAIT_FRAMES(30)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    GOTO(95)
    LABEL(20)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATT2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 16, 16, 20)
    END_SIBLING_EVENT
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.39941406f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(0.39941406f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(14))
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_NOT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        CALL(evt_audience_acrobat_notry)
        GOTO(95)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    ADD(LW(1), 20)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, FLOAT(-60.0f), 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_Y_1"))
    WAIT_MS(500)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 0, 4, 0, -1)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(partyClaudaAttack_BreathAttack)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    WAIT_FRAMES(20)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(1))
    SUBTRACT(LW(1), 3)
    SWITCH(LW(1))
#if VERSION <= VERSION_DEMO_US
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 420)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 360)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 320)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 270)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 240)
        CASE_DEFAULT
        SET_VALUE(LW(0), 180)
#else
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 300)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 300)
        CASE_DEFAULT
        SET_VALUE(LW(0), 300)
#endif
    END_SWITCH
    CALL(btlevtcmd_AcGetDifficulty, LW(1))
    CALL(btlevtcmd_AcSetParamAll, 1, LW(0), 4, 40, 60, 80, 100, LW(1))
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 14, 1, 0)
    CALL(_clauda_breath_effect_ready)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A2_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_BREATH1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A2_2"))
    CALL(evt_btl_camera_nomove_x_onoff, 0, 1)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    CALL(evt_btl_camera_nomove_z_onoff, 0, 1)
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 0)
    CALL(evt_btl_camera_nomove_x_onoff, 0, 0)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 0)
    CALL(evt_btl_camera_nomove_z_onoff, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A2_3"))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(btlevtcmd_StageDispellFog)
    END_INLINE_EVENT
    CALL(_clauda_breath_effect_fire, LW(13))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_BREATH2"), EVT_NULLPTR, 0, LW(14))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(14), -1)
        LABEL(5)
        CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
        WAIT_FRAMES(1)
        GOTO(5)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(8)
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(_check_blow_rate, LW(3), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_DamageDirect, LW(3), LW(4), 0, 0, 3, 1)
        END_IF
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        GOTO(8)
    END_IF
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_StopAC)
    SET_VALUE(LW(11), 99)
    SET_VALUE(LW(12), PTR(&partyWeapon_ClaudaBreathAttack))
    CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
    CALL(_make_breath_weapon, LW(12), LW(0))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_SetDispOffset, LW(3), 0, 0, 0)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
            GOTO(51)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
            GOTO(51)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
            GOTO(51)
        END_IF
        GOTO(50)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 131328, LW(5))
        CALL(btlevtcmd_GetDamageCode, LW(3), LW(0))
        IF_INT_EQUAL(LW(0), 29)
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        END_IF
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    LABEL(50)
    WAIT_MS(300)
    LABEL(51)
    SUBTRACT(LW(11), 1)
    IF_INT_GREATER_OR_EQUAL(LW(11), 1)
        LABEL(52)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
        IF_INT_NOT_EQUAL(LW(3), -1)
            ADD(LW(10), 1)
            GOTO(10)
        END_IF
    END_IF
    LABEL(80)
    WAIT_MS(1500)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(evt_eff_delete_ptr, LW(13))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 25, 25, 20)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_NOT_EQUAL(LW(6), 2)
        CALL(evt_audience_acrobat_notry)
        WAIT_MS(500)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_Y_1"))
    WAIT_MS(1000)
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(partyClaudaAttack_PredationAttack)
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
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AcGetDifficulty, LW(0))
        SUBTRACT(LW(0), 3)
        SWITCH(LW(0))
            CASE_LESS_OR_EQUAL(-3)
            SET_VALUE(LW(0), 120)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-2)
            SET_VALUE(LW(0), 100)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-1)
            SET_VALUE(LW(0), 80)
            SET_VALUE(LW(1), 1)
            CASE_EQUAL(0)
            SET_VALUE(LW(0), 70)
            SET_VALUE(LW(1), 2)
            CASE_EQUAL(1)
#if VERSION <= VERSION_DEMO_US
            SET_VALUE(LW(0), 65)
            SET_VALUE(LW(1), 3)
            CASE_EQUAL(2)
            SET_VALUE(LW(0), 60)
            SET_VALUE(LW(1), 3)
            CASE_DEFAULT
            SET_VALUE(LW(0), 50)
            SET_VALUE(LW(1), 4)
#else
            SET_VALUE(LW(0), 66)
            SET_VALUE(LW(1), 2)
            CASE_EQUAL(2)
            SET_VALUE(LW(0), 62)
            SET_VALUE(LW(1), 2)
            CASE_DEFAULT
            SET_VALUE(LW(0), 58)
            SET_VALUE(LW(1), 2)
#endif
        END_SWITCH
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_AcSetParamAll, 0, LW(0), LW(1), 6, 3, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_AcSetGaugeParam, 51, 68, 85, 100)
#else
        CALL(btlevtcmd_AcSetParamAll, 0, LW(0), LW(1), 5, 3, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100)
#endif
        CASE_DEFAULT
        CALL(btlevtcmd_AcGetDifficulty, LW(0))
        SUBTRACT(LW(0), 3)
        SWITCH(LW(0))
#if VERSION <= VERSION_DEMO_US
            CASE_LESS_OR_EQUAL(-3)
            SET_VALUE(LW(0), 80)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-2)
            SET_VALUE(LW(0), 70)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-1)
            SET_VALUE(LW(0), 60)
            SET_VALUE(LW(1), 1)
            CASE_EQUAL(0)
            SET_VALUE(LW(0), 50)
            SET_VALUE(LW(1), 2)
            CASE_EQUAL(1)
            SET_VALUE(LW(0), 45)
            SET_VALUE(LW(1), 3)
            CASE_EQUAL(2)
            SET_VALUE(LW(0), 40)
            SET_VALUE(LW(1), 3)
            CASE_DEFAULT
            SET_VALUE(LW(0), 35)
            SET_VALUE(LW(1), 4)
#else
            CASE_LESS_OR_EQUAL(-3)
            SET_VALUE(LW(0), 120)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-2)
            SET_VALUE(LW(0), 100)
            SET_VALUE(LW(1), 0)
            CASE_EQUAL(-1)
            SET_VALUE(LW(0), 80)
            SET_VALUE(LW(1), 1)
            CASE_EQUAL(0)
            SET_VALUE(LW(0), 70)
            SET_VALUE(LW(1), 2)
            CASE_EQUAL(1)
            SET_VALUE(LW(0), 66)
            SET_VALUE(LW(1), 2)
            CASE_EQUAL(2)
            SET_VALUE(LW(0), 62)
            SET_VALUE(LW(1), 2)
            CASE_DEFAULT
            SET_VALUE(LW(0), 58)
            SET_VALUE(LW(1), 2)
#endif
        END_SWITCH
#if VERSION <= VERSION_DEMO_US
        CALL(btlevtcmd_AcSetParamAll, 0, LW(0), LW(1), 4, 2, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_AcSetGaugeParam, 25, 50, 75, 100)
#else
        CALL(btlevtcmd_AcSetParamAll, 0, LW(0), LW(1), 3, 2, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
        CALL(btlevtcmd_AcSetGaugeParam, 34, 68, 100, 100)
#endif
    END_SWITCH
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 17, 1, 60)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_GetStatusMg, LW(3), LW(6))
        MULTIPLY_FLOAT(LW(6), 40)
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    END_IF
    CALL(_get_clauda_kiss_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 20)
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    ADD(LW(2), 5)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
    END_SWITCH
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
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_2"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CommandPreCheckCounter, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(7)
        CASE_OR_EQUAL(8)
        CASE_OR_EQUAL(9)
        CASE_OR_EQUAL(10)
        CASE_OR_EQUAL(11)
        CASE_OR_EQUAL(12)
        CASE_OR_EQUAL(13)
        CASE_OR_EQUAL(14)
        CASE_OR_EQUAL(15)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_2"))
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
        CASE_END
    END_SWITCH
    CALL(btlevtcmd_OffUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_KISS1"), EVT_NULLPTR, 0, LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("kiss"), 2, LW(0), LW(1), LW(2), LW(6), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_DamageDirect, LW(3), LW(4), 0, 0, 2, 1)
    CALL(btlevtcmd_StartAC, 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_SetRGB, LW(3), LW(4), 255, 255, 255)
        LOOP(45)
            CALL(btlevtcmd_GetRGB, LW(3), LW(4), LW(0), LW(1), LW(2))
            SUBTRACT(LW(1), 2)
            IF_INT_LESS(LW(1), 190)
                SET_VALUE(LW(1), 190)
            END_IF
            SUBTRACT(LW(2), 4)
            CALL(btlevtcmd_SetRGB, LW(3), LW(4), LW(0), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(45)
            CALL(btlevtcmd_GetRGB, LW(3), LW(4), LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 2)
            SUBTRACT(LW(1), 2)
            ADD(LW(2), 3)
            IF_INT_LESS(LW(1), 0)
                SET_VALUE(LW(1), 0)
            END_IF
            CALL(btlevtcmd_SetRGB, LW(3), LW(4), LW(0), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_ResultAC)
    CALL(evt_snd_sfxoff, LW(14))
    DELETE_EVENT(LW(15))
    CALL(btlevtcmd_GetResultAC, LW(9))
    IF_BITS_SET(LW(9), 2)
        CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(2)
            SET_VALUE(LW(7), 3)
            CASE_DEFAULT
            SET_VALUE(LW(7), 2)
        END_SWITCH
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(8))
        IF_INT_GREATER_OR_EQUAL(LW(8), LW(7))
            SUBTRACT(LW(8), LW(7))
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(8), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
    ELSE
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_SetRGB, LW(3), LW(4), 255, 255, 255)
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    CALL(_make_kiss_weapon, LW(12), LW(0))
    IF_BITS_SET(LW(9), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetHpDamage, LW(3), LW(0))
        WAIT_FRAMES(50)
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
            CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(8))
            MULTIPLY_FLOAT(LW(8), 40)
            ADD(LW(6), LW(8))
            CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, 1, LW(0))
            CALL(evt_eff, STRING(""), STRING("recovery"), 7, LW(5), LW(6), LW(7), LW(0), 0, 0, 0, 0, 0, 0, 0)
        END_IF
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_KISS2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_3"))
    WAIT_FRAMES(5)
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 29, 29, 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A_7"))
        WAIT_FRAMES(56)
    ELSE
        CALL(evt_audience_acrobat_notry)
        WAIT_FRAMES(60)
    END_IF
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(partyClaudaAttack_KumoGuard)
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
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(3), LW(1), EVT_NULLPTR, EVT_NULLPTR)
    ADD(LW(0), LW(1))
    DIVIDE(LW(0), 2)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 72, 400, LW(0), 42, 0, 30, 5)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 3, 0, 40, 0, 1, 1, 2, 8)
    CALL(btlevtcmd_AcSetFlag, 5)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 18, 1, 0)
    WAIT_FRAMES(1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A4_2"))
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A4_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_HIDE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(150)
    CALL(btlevtcmd_GetResultAC, LW(6))
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(3), LW(7))
    DIVIDE(LW(7), 2)
    ADD(LW(1), LW(7))
    ADD(LW(2), 20)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 8, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    ADD(LW(0), 1)
    CALL(_make_kumoguard_weapon, LW(12), LW(0))
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 131328, LW(5))
        SUBTRACT(LW(0), 1)
        CALL(btlevtcmd_GetResultPrizeLv, BTL_UNIT_SELF, LW(0), LW(6))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 29, 29, 20)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A_7"))
        WAIT_MS(1000)
    ELSE
        CALL(evt_audience_acrobat_notry)
        WAIT_MS(1000)
    END_IF
    LABEL(99)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(clauda_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_APPEAL)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 30)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(14), 45)
    CALL(evt_eff, STRING(""), STRING("kiss"), 2, LW(0), LW(1), LW(2), LW(14), 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static EVT_BEGIN(attack_audience_event)
    CALL(_check_aud_item_type, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL_CHILD(attack_bad_audience_event)
        CASE_DEFAULT
        CALL_CHILD(attack_good_audience_event)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(attack_bad_audience_event)
    CALL(btlevtcmd_OffUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_1"))
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(15)
        CALL(evt_btl_camera_set_mode, 0, 13)
        CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, 1, LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_SIBLING_EVENT
    SET_VALUE(LW(5), LW(1))
    ADD(LW(1), 28)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 5)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    SET_VALUE(LW(6), 36)
    CALL(btlevtcmd_MarioJumpParam, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(6))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_1"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        DIVIDE(LW(6), 2)
        WAIT_FRAMES(LW(6))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_2"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_MarioJumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(6), 0, 0)
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(evt_btl_camera_shake_h, 0, 8, 0, 30, 13)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(1000)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(0.39941406f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(0.39941406f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(0), LW(5), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.0f), FLOAT(1.5f), 10)
        LOOP(10)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_init_float, 11, FLOAT(1.5f), FLOAT(1.0f), 6)
        LOOP(6)
            CALL(evt_sub_intpl_get_float, LW(5), EVT_NULLPTR)
            CALL(btlevtcmd_GetScale, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, LW(5), LW(1), LW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(14))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    ADD(LW(1), 20)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 18, -1)
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    WAIT_MS(400)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 16, 0, 4, 0, 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    ADD(LW(15), 30)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 20, 4, 0, -1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(attack_good_audience_event)
    CALL(btlevtcmd_OffUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A1_1"))
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(evt_btl_camera_set_mode, 0, 13)
        CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, 1, LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_SIBLING_EVENT
    SET_VALUE(LW(5), LW(1))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.5996094f))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 40, 15, 4, 0, 0)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, 0, 4, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_KISS1"), EVT_NULLPTR, 0, LW(14))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_2"))
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 25)
    CALL(evt_eff, STRING(""), STRING("kiss"), 2, LW(0), LW(1), LW(2), LW(6), 0, 0, 0, 0, 0, 0, 0)
    CALL(_attack_aud, LW(3), 1)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(1000)
    END_SIBLING_EVENT
    WAIT_MS(500)
    CALL(evt_snd_sfxoff, LW(14))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_CLAUD_KISS2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PWD_A3_3"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 40)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 16, 0, 4, 0, 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(6.0f), LW(15))
    ADD(LW(15), 30)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 20, 4, 0, -1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static USER_FUNC(_clauda_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

    command->weapon[*count].index = -1;
    command->weapon[*count].itemId = 0;
    command->weapon[*count].weapon = &partyWeapon_ClaudaNormalAttack;
    command->weapon[*count].enabled = 0;
    command->weapon[*count].icon = command->weapon[*count].weapon->icon;
    command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
    (*count)++;

    if (techLv >= 0) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_ClaudaBreathAttack;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 1) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_ClaudaPredationAttack;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
    if (techLv >= 2) {
        command->weapon[*count].index = -1;
        command->weapon[*count].itemId = 0;
        command->weapon[*count].weapon = &partyWeapon_ClaudaKumogakureAttack;
        command->weapon[*count].enabled = 0;
        command->weapon[*count].icon = command->weapon[*count].weapon->icon;
        command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name);
        (*count)++;
    }
}

static USER_FUNC(_check_blow_rate) {
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, out;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    out = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    evtSetValue(event, out, unit->vulnStatus->galeForceRate);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_clauda_breath_effect_ready) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->sizeMultiplier * (unit->faceDirection * 20);
    pos.y += 25.0f * unit->sizeMultiplier;
    if (unit->faceDirection >= 0) {
        eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 0.0f, 2.0f, 1.0f);
    } else {
        eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 180.0f, 2.0f, 1.0f);
    }
    ((EffKumokumoN64Particle*)eff->userdata)->r1 = 76;
    ((EffKumokumoN64Particle*)eff->userdata)->g1 = 167;
    ((EffKumokumoN64Particle*)eff->userdata)->b1 = 202;
    ((EffKumokumoN64Particle*)eff->userdata)->r2 = 125;
    ((EffKumokumoN64Particle*)eff->userdata)->g2 = 27;
    ((EffKumokumoN64Particle*)eff->userdata)->b2 = 245;
    return EVT_RETURN_DONE;
}

static USER_FUNC(_clauda_breath_effect_fire) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id;
    BattleUnit* unit;
    s32 var;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    var = args[0];
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->sizeMultiplier * (unit->faceDirection * 25);
    pos.y += 15.0f * unit->sizeMultiplier;
    if (unit->faceDirection >= 0) {
        eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 0.0f, -2.0f, 1.0f);
    } else {
        eff = effKumokumoN64Entry(0, 0, pos.x, pos.y, pos.z, 180.0f, -2.0f, 1.0f);
    }
    ((EffKumokumoN64Particle*)eff->userdata)->r1 = 76;
    ((EffKumokumoN64Particle*)eff->userdata)->g1 = 167;
    ((EffKumokumoN64Particle*)eff->userdata)->b1 = 202;
    ((EffKumokumoN64Particle*)eff->userdata)->r2 = 125;
    ((EffKumokumoN64Particle*)eff->userdata)->g2 = 27;
    ((EffKumokumoN64Particle*)eff->userdata)->b2 = 245;
    ((EffKumokumoN64Particle*)eff->userdata)->rot = -10.0f;
    evtSetValue(event, var, (EvtWord)eff);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_make_breath_weapon) {
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
    weapon->galeForceChance = value;
    evtSetValue(event, index, (EvtWord)weapon);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_make_kiss_weapon) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    evtSetValue(event, index, (EvtWord)weapon);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_get_clauda_kiss_hit_position) {
    EvtWord* args = event->args;
    Vec pos, tmp;
    s32 dir;
    BattleUnit* target;
    BattleWork* wp = _battleWorkPointer;
    s32 targetId;
    s32 outX;
    s32 outY;
    BattleUnit* unit;
    s32 outZ;
    s32 id;

    id = evtGetValue(event, args[0]);
    targetId = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    outX = args[3];
    outY = args[4];
    outZ = args[5];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    target = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    dir = target->faceDirection;
    BtlUnit_GetPos(target, &pos.x, &pos.y, &pos.z);
    pos.x += dir * (target->kissHitOffset.x * target->sizeMultiplier);
    pos.y += target->kissHitOffset.y * target->sizeMultiplier;
    pos.z += target->kissHitOffset.z * target->sizeMultiplier;
    pos.y -= 30.0f * unit->sizeMultiplier;
    tmp = pos;
    tmp.y = BattleGetFloorHeight(wp, tmp.x, tmp.y, tmp.z);
    if (tmp.y > pos.y) {
        pos.y = tmp.y;
    }
    evtSetFloat(event, outX, pos.x);
    evtSetFloat(event, outY, pos.y);
    evtSetFloat(event, outZ, pos.z);
    return EVT_RETURN_DONE;
}

static USER_FUNC(_make_kumoguard_weapon) {
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
    weapon->dodgyTime = value;
    evtSetValue(event, index, (EvtWord)weapon);
    return EVT_RETURN_DONE;
}
