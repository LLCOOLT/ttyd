// Battle unit data and scripts for Yoshi as a partner.
#include "data_tables.h"
#include "version.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_disp.h"
// FAKE: the Stampede Yoshis call btlDispTexPlane with the float arguments listed first. The registers are the
// same as (id, color, 0, x, y, z, sx, sy); listing the floats first makes MWCC load the texture id last, as here.
typedef void (*BtlDispTexPlaneFloatsFirstFn)(f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY, u32 id, GXColor color, s32 unused);
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_env.h"
#include "evt/evt_sub.h"
#include "battle/battle_attack_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"

#include "unit/party/unit_party_yoshi.h"
#if VERSION <= VERSION_DEMO_JP
static void _btlYoshiDisp(CameraId camera, YoshiGundanWork* w);
#else
static void _btlYoshiDisp(CameraId camera, YoshiGundanPart* p);
#endif
static void _yoshi_slide_move_sound(BattleUnit* unit, PoseSoundTiming* s);
static void __makeTechMenuFunc(BattleCommand* command, s32* count);

#include "eff/eff_kemu_test.h"
#include "eff/n64/eff_sweat_n64.h"
#include "data_tables.h"

// Unit work slots of Yoshi (btlevtcmd_SetUnitWork / GetUnitWork); the same names as rels/tst/src/unit/unit_yoshi.c.
enum {
    UW_YOSHI_ATE_TARGET = 1,          // 1 once Gulp has swallowed the target whole; the run home then has a stylish
    UW_YOSHI_GROUND_POUND_ACTIVE = 2, // 1 while Ground Pound runs (nothing reads it)
    UW_YOSHI_UNUSED_3 = 3,            // set to -1 when Ground Pound starts; nothing reads it
    UW_YOSHI_SLIDE_SOUND_POWER = 4,   // slide sound strength, following the action-command power (power * 2387 / 100)
    UW_YOSHI_SLIDE_SOUND_PERCENT = 5, // percent of the slide sound strength played (the flutter sways it 50-100)
};

// Forward declaration of the helper that loads Yoshi's hatched colour model for battle (defined further down).
USER_FUNC(yoshi_original_color_anim_set);
static USER_FUNC(_gundan_yoshi_run_effect);
static USER_FUNC(_wait_yoshig_complete);
static USER_FUNC(_wait_yoshig_run);
static USER_FUNC(_check_swallow_attribute);
static USER_FUNC(_get_swallow_param);
static USER_FUNC(_get_nomikomi_hit_position);

PoseTableEntry pose_table_yoshi_stay[25];

static BattleDataEntry data_table[8];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
PoseTableEntry pose_table_egg_g[4];
PoseTableEntry pose_table_egg_y[4];
PoseTableEntry pose_table_egg_p[4];
BattleUnitKindPart unitpartsdata_Party_Yoshi[7];
BattleUnitKind unitdata_Party_Yoshi;
static EvtWord init_event[54];
static EvtWord damage_event[16];
BattleWeapon partyWeapon_YoshiNormalAttack;
BattleWeapon partyWeapon_YoshiNomikomi_Shot;
BattleWeapon partyWeapon_YoshiNomikomi_Spew;
BattleWeapon partyWeapon_YoshiNomikomi_Dmg0;
BattleWeapon partyWeapon_YoshiNomikomi_Fire;
BattleWeapon partyWeapon_YoshiNomikomi_Involved;
BattleWeapon partyWeapon_YoshiEggAttack_Minimini;
BattleWeapon partyWeapon_YoshiCallGuard;
PoseSoundTiming posesound_normal_attack[15];
extern EvtWord partyYoshiAttack_NormalAttack[];
extern EvtWord partyYoshiAttack_Nomikomi[];
extern EvtWord partyYoshiAttack_EggAttack[];
extern EvtWord _egg_attack_event[];
extern EvtWord partyYoshiAttack_CallGuard[];
extern EvtWord yoshi_appeal_event[];
static EvtWord party_win_reaction[25];
static EvtWord attack_audience_event[290];
static EvtWord attack_event[2];
static EvtWord wait_event[6];
u8 _yoshig_tpl_no_tbl[8] __attribute__((aligned(4)));

// The demo defines regist first and data_table after the egg pose tables.
#if VERSION <= VERSION_DEMO_JP
/** Yoshi's status chances: 100 for every status (badges lower them in battle). */
static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
#endif

/**
 * Yoshi's pose table: animations for each status (stop, dizzy, poison, confusion, sleep, freeze, instant KO),
 * the hurt poses, walking and running, low HP, the failed Run Away tumble, talking, item use,
 * the command menu wait, the Appeal, zero gravity, the Defend stance and plain standing.
 */
PoseTableEntry pose_table_yoshi_stay[] = {
    {9, "PYS_D_5"},
    {2, "PYS_D_5"},
    {3, "PYS_X_1"},
    {4, "PYS_D_2"},
    {5, "PYS_X_1"},
    {1, "PYS_N_1"},
    {27, "PYS_D_3"},
    {BTL_POSE_NORMAL, "PYS_S_1"},
    {37, "PYS_G_2"},
    {31, "PYS_G_1"},
    {BTL_POSE_DAMAGE, "PYS_D_1"},
    {BTL_POSE_WALK, "PYS_W_1"},
    {BTL_POSE_RUN, "PYS_R_1"},
    {BTL_POSE_PERIL, "PYS_D_2"},
    {BTL_POSE_DANGER, "PYS_D_2"},
    {BTL_POSE_ESCAPE_FAIL, "PYS_D_4"},
    {BTL_POSE_ESCAPE_FAIL_END, "PYS_D_2"},
    {BTL_POSE_TALK, "PYS_T_1"},
    {BTL_POSE_ITEM_USE, "PYS_I_1"},
    {BTL_POSE_COMMAND_WAIT, "PYS_C_1"},
    {BTL_POSE_APPEAL, "PYS_O_1"},
    {BTL_POSE_ZERO_GRAVITY, "PYS_F_1"},
    {49, "PYS_F_1"},
    {BTL_POSE_DEFEND, "PYS_G_1"},
    {BTL_POSE_STAY_DEFAULT, "PYS_S_1"},
};

#if VERSION >= VERSION_JP
/**
 * Yoshi's data events: Appeal, the audience attack reaction, his move list (tag 1, __makeTechMenuFunc), First
 * Strike (nothing), the victory pose, an empty step run after a move's cost is paid (7) and the spin when he
 * superguards an attack (47).
 */
static BattleDataEntry data_table[] = {
    {5, yoshi_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};
#endif

/** Yoshi's defence (shared by his egg parts): 0 against every element. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Yoshi's defence attributes: normal (0) against every element, no weakness or immunity. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION >= VERSION_JP
/** Yoshi's status chances: 100 for every status (badges lower them in battle). */
static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
#endif

/** Pose table for a green Mini-Egg (egg parts 2-7): the CHU_C_1 egg model for every pose. */
PoseTableEntry pose_table_egg_g[] = {
    {BTL_POSE_NORMAL, "CHU_C_1"},
    {31, "CHU_C_1"},
    {BTL_POSE_DAMAGE, "CHU_C_1"},
    {BTL_POSE_STAY_DEFAULT, "CHU_C_1"},
};

/** Pose table for a yellow Mini-Egg: the CHU_C_2 egg model for every pose. */
PoseTableEntry pose_table_egg_y[] = {
    {BTL_POSE_NORMAL, "CHU_C_2"},
    {31, "CHU_C_2"},
    {BTL_POSE_DAMAGE, "CHU_C_2"},
    {BTL_POSE_STAY_DEFAULT, "CHU_C_2"},
};

/** Pose table for a pink Mini-Egg: the CHU_C_3 egg model for every pose. */
PoseTableEntry pose_table_egg_p[] = {
    {BTL_POSE_NORMAL, "CHU_C_3"},
    {31, "CHU_C_3"},
    {BTL_POSE_DAMAGE, "CHU_C_3"},
    {BTL_POSE_STAY_DEFAULT, "CHU_C_3"},
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Yoshi's data events: Appeal, the audience attack reaction, his move list (tag 1, __makeTechMenuFunc), First
 * Strike (nothing), the victory pose, an empty step run after a move's cost is paid (7) and the spin when he
 * superguards an attack (47).
 */
static BattleDataEntry data_table[] = {
    {5, yoshi_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};
#endif

/**
 * Yoshi's battle parts: part 1 is his targetable body (model c_babyyoshi);
 * parts 2-7 are hidden, untargetable eggs (c_tamago) that Mini-Egg lays and throws.
 */
BattleUnitKindPart unitpartsdata_Party_Yoshi[] = {
    {1, "btl_un_yoshi", "c_babyyoshi", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table_yoshi_stay},
    {2, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
    {3, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
    {4, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
    {5, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
    {6, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
    {7, "btl_un_yoshi", "c_tamago", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table_egg_g},
};

/**
 * Yoshi's battle unit (UNIT_YOSHI), listed in battle_party.c's partner table:
 * seven parts, the partner hit sounds and no enemy HP gauge.
 */
BattleUnitKind unitdata_Party_Yoshi = {
    226,
    "btl_un_yoshi",
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
    8,
    28,
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
    7,
    unitpartsdata_Party_Yoshi,
    init_event,
    data_table,
};

/**
 * Yoshi's battle entry: starts 250 units behind his home spot and, after 40 frames,
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
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBMOVE1L"), STRING("SFX_PARTY_BATTLE_SUBMOVE1R"), 0, 6, 6, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Init for Yoshi: registers his wait, attack, damage, confusion and entry scripts and his walk,
 * run and jump sounds, clears UW_YOSHI_GROUND_POUND_ACTIVE
 * and loads the model for his hatched colour.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_GROUND_POUND_ACTIVE, 0)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 15, 13)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(yoshi_original_color_anim_set, BTL_UNIT_SELF)
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

/** The demo defines wait_event here; retail defines it near the end of the file. */
#if VERSION <= VERSION_DEMO_JP
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
#endif

/**
 * Ground Pound (0 FP): repeated pounds on one enemy from above (not ceiling enemies), 1 damage each,
 * lowered by each earlier hit; flips shelled enemies and grounds winged ones. Usable while confused.
 */
BattleWeapon partyWeapon_YoshiNormalAttack = {
    "btl_wn_pys_normal", // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_hip_drop", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 1, 1, 1, 1, 1, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_hip_drop", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_DIMINISHING_BY_HIT | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_PREEMPTIVE_SPIKY | COUNTER_RESIST_FRONT_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_NormalAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 10, 10, 100, 10, 10, 5, 5, 5, 5, 0, 0}, // stageEffectRates
#else
    {0, 10, 10, 100, 10, 5, 5, 5, 5, 5, 0, 0}, // stageEffectRates
#endif
};

/**
 * Gulp (4 FP), the hit on an enemy spat out as a shot at the enemies behind it (swallow attribute 2):
 * pierces defence; by rank 2, 3 or 3 damage on a failed action command, 4, 5 or 6 on success.
 */
BattleWeapon partyWeapon_YoshiNomikomi_Shot = {
    "btl_wn_pys_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_nomikomi", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {2, 4, 3, 5, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    6, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_nomikomi", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ELECTRIC | COUNTER_RESIST_TOP_SPIKY | COUNTER_RESIST_FRONT_SPIKY | COUNTER_RESIST_FIERY | COUNTER_RESIST_ICY | COUNTER_RESIST_POISON | COUNTER_RESIST_EXPLOSIVE | COUNTER_RESIST_VOLATILE_EXPLOSIVE | COUNTER_RESIST_PAYBACK | COUNTER_RESIST_HOLD_FAST, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_Nomikomi, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

/**
 * Gulp (4 FP), the hit on an enemy that is spat straight out (no swallow attribute 2):
 * pierces defence; by rank 2, 3 or 3 damage on a failed action command, 4, 5 or 6 on success.
 */
BattleWeapon partyWeapon_YoshiNomikomi_Spew = {
    "btl_wn_pys_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_nomikomi", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {2, 4, 3, 5, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    5, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_nomikomi", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_Nomikomi, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 5, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 5, 0, 0, 0, 0}, // stageEffectRates
#endif
};

/** Gulp's 0-damage tongue hit on an enemy that cannot be swallowed or after a failed action command. */
BattleWeapon partyWeapon_YoshiNomikomi_Dmg0 = {
    "btl_wn_pys_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_nomikomi", // description
    100, // baseAccuracy
    2, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_nomikomi", // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_Nomikomi, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Gulp's fire breath after swallowing an enemy with swallow attribute 4:
 * 1 fire damage to every enemy, pierces defence.
 */
BattleWeapon partyWeapon_YoshiNomikomi_Fire = {
    "btl_wn_pys_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_nomikomi", // description
    100, // baseAccuracy
    2, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_FIRE, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_nomikomi", // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_Nomikomi, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Damage dealt to the enemy behind when Gulp spits an enemy into it (subsetevt_swallow_shot_damage):
 * pierces defence; by rank 1, 2 or 3 damage on a failed action command, 4, 5 or 6 on success.
 */
BattleWeapon partyWeapon_YoshiNomikomi_Involved = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, 0.0f, 0, 0, 0, 0, // baseFpCost..reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 4, 2, 5, 3, 6, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
#if VERSION <= VERSION_DEMO_JP
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
#else
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_RECOIL | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
#endif
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
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

/**
 * Mini-Egg (3 FP): eggs thrown at random enemies, 1 damage each; a hit shrinks the enemy to Tiny
 * (strength -2) for 3 turns. Cannot be guarded.
 */
BattleWeapon partyWeapon_YoshiEggAttack_Minimini = {
    "btl_wn_pys_lv2", // name
#if VERSION >= VERSION_US
    346, // icon
#else
    338, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_wonder_egg", // description
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
    weaponGetPowerDefault, // hpDamageFn
    {1, 1, 1, 1, 1, 1, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_wonder_egg", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    -2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_EggAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 6, 3, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 3, 3, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

/**
 * Stampede (6 FP): a herd of Yoshis tramples every enemy, 1 damage per trample, lowered by each earlier hit;
 * the action command decides how many tramples. Cannot be guarded.
 */
BattleWeapon partyWeapon_YoshiCallGuard = {
    "btl_wn_pys_lv3", // name
#if VERSION >= VERSION_US
    347, // icon
#else
    339, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_pys_taigun_yoshi", // description
    100, // baseAccuracy
    6, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {1, 1, 1, 1, 1, 1, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_taigun_yoshi", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_DIMINISHING_BY_HIT | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyYoshiAttack_CallGuard, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 20, 20, 100, 20, 40, 5, 5, 20, 5, 0, 0}, // stageEffectRates
#else
    {0, 20, 20, 100, 20, 20, 5, 5, 20, 5, 0, 0}, // stageEffectRates
#endif
};

/**
 * Footstep sounds during Ground Pound's run-up and flutter (walk, run, the fast-leg poses and the flutter pose):
 * left and right steps played by _yoshi_slide_move_sound at fixed points of each loop.
 */
PoseSoundTiming posesound_normal_attack[] = {
    {"PYS_W_1", 0.01f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 0, 1},
    {"PYS_W_1", 0.25f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 0, 1},
    {"PYS_R_1", 0.01f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 0, 1},
    {"PYS_R_1", 0.1f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 0, 1},
    {"PYS_R_4", 0.01f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 1364, 1},
    {"PYS_R_4", 0.05f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 1364, 1},
    {"PYS_R_4", 0.1f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 1364, 1},
    {"PYS_R_4", 0.15f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 1364, 1},
    {"PYS_R_5", 0.01f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 2387, 1},
    {"PYS_R_5", 0.033333335f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 2387, 1},
    {"PYS_R_5", 0.083333336f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 2387, 1},
    {"PYS_R_5", 0.11666667f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 2387, 1},
    {"PYS_A_3", 0.01f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1L", 2387, 1},
    {"PYS_A_3", 0.083333336f, _yoshi_slide_move_sound, "SFX_PARTY_BATTLE_MOVE1R", 2387, 1},
    {NULL, 0.0f, _yoshi_slide_move_sound, NULL, 0, 1},
};

/**
 * Yoshi's Ground Pound: he jumps up over the enemy
 * and flutters above it during the action command (the yoroyoro jump helpers),
 * then pounds it once per hit the command earned before returning home.
 */
EVT_BEGIN(partyYoshiAttack_NormalAttack)
    // Pick the target, pay the cost and aim the camera at Yoshi.
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
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    WAIT_FRAMES(20)
    // He faces the enemy and revs his legs in place, the footsteps speeding up.
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_GROUND_POUND_ACTIVE, 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_UNUSED_3, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_SLIDE_SOUND_POWER, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_SLIDE_SOUND_PERCENT, 100)
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, PTR(posesound_normal_attack))
    CALL(btlevtcmd_AcSetOutputParam, 1, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_W_1"))
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(0), 0)
        LOOP(25)
            ADD(LW(0), 4)
            SET_VALUE(LW(1), 2387)
            MULTIPLY(LW(1), LW(0))
            DIVIDE(LW(1), 100)
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_SLIDE_SOUND_POWER, LW(1))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_R_5"))
    WAIT_FRAMES(25)
    // The camera moves to the enemy and Yoshi leaps toward it; the action command (tap R) is set up for his rank.
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 350)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetTakeoffPosition, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_J_1A"))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.2998047f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 25)
    ADD(LW(1), 35)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_CommandGetWeaponActionLv, LW(15))
        CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AcSetParamAll, 5, 180, 178, 23, 25, 20, 61, 1)
            CALL(btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100)
            CASE_EQUAL(1)
            CALL(btlevtcmd_AcSetParamAll, 5, 180, 178, 23, 25, 25, 76, 1)
            CALL(btlevtcmd_AcSetGaugeParam, 75, 100, 100, 100)
            CASE_DEFAULT
            CALL(btlevtcmd_AcSetParamAll, 5, 180, 178, 23, 25, 34, 100, 1)
            CALL(btlevtcmd_AcSetGaugeParam, 100, 100, 100, 100)
        END_SWITCH
        CALL(btlevtcmd_AcSetFlag, 72)
        CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 6, 1, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 25, -1)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    // He flutters over the enemy while the command runs; its result is the number of pounds.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_3"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    ADD(LW(7), 40)
    SET_VALUE(LW(10), FLOAT(1.0f))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL(btlevtcmd_StartAC, 1)
        CALL(btlevtcmd_ResultAC)
    END_SIBLING_EVENT
    CALL(btl_yoshi_yoroyoro_jump_calc_param, BTL_UNIT_SELF, LW(6), LW(7), LW(8), LW(10), LW(9))
    CALL(btl_yoshi_yoroyoro_jump_move, BTL_UNIT_SELF, LW(6), LW(7), LW(8), LW(10), LW(9))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    SET_VALUE(LW(13), 1)
    CALL(btlevtcmd_AcGetOutputParam, 2, LW(14))
    // Each pound: check whether it connects; before the first one, pressing A makes him spin (the stylish).
    LABEL(50)
    IF_INT_GREATER_OR_EQUAL(LW(13), 2)
        CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_ALWAYS_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
    END_SWITCH
    CALL(btlevtcmd_AnimeSetPoseSoundTable, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_GROUND_POUND_ACTIVE, 0)
    IF_INT_LESS(LW(13), 2)
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 20, 20, 0)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    ELSE
        SET_VALUE(LW(6), 1)
    END_IF
    IF_INT_EQUAL(LW(13), 1)
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_J_1B"))
        IF_INT_EQUAL(LW(6), 2)
            SET_VALUE(LW(0), 3)
            SET_VALUE(LW(1), 6)
            MULTIPLY(LW(15), -60)
        ELSE
            SET_VALUE(LW(0), 1)
            SET_VALUE(LW(1), 9)
            MULTIPLY(LW(15), -40)
        END_IF
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 12, 0)
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        WAIT_FRAMES(15)
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, -60, -25, 0)
        END_IF
        LOOP(LW(0))
            SET_VALUE(LW(2), LW(1))
            CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_ATTACK1"), 0)
            LOOP(LW(2))
                CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 0, LW(15))
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
        CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_SetRotateOffset, BTL_UNIT_SELF, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_1"))
        WAIT_FRAMES(15)
    ELSE
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_1"))
    END_IF
    // He drops onto the enemy; on a miss the enemy dodges and Yoshi crashes to the floor, ending the move.
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 4, 0, 0, 0, -1)
    IF_INT_NOT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_StopAC)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(15), LW(1))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        SUBTRACT(LW(15), LW(1))
        DIVIDE(LW(15), 10)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), 0, 0, 0, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_D_1"))
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, -7, 0)
        CALL(evt_btl_camera_shake_h, 0, 4, 0, 10, 13)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_5"))
        CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, 0, 0, 0)
        WAIT_FRAMES(54)
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        GOTO(95)
    END_IF
    // A hit: with a successful command, the pounds after the first show a rising rating (Nice, Good...).
    CALL(btlevtcmd_ac_timing_flag_onoff, 1, 1)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_ac_timing_flag_onoff, 0, 1)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        IF_INT_GREATER_OR_EQUAL(LW(13), LW(14))
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
        ELSE
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_AC_SUCCESS, LW(5))
        END_IF
        CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
            SWITCH(LW(0))
                CASE_GREATER_OR_EQUAL(6)
                SET_VALUE(LW(0), 2)
                CASE_GREATER_OR_EQUAL(4)
                SET_VALUE(LW(0), 1)
                CASE_GREATER_OR_EQUAL(2)
                SET_VALUE(LW(0), 0)
                CASE_DEFAULT
                SET_VALUE(LW(0), -1)
            END_SWITCH
            CASE_EQUAL(1)
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
            SWITCH(LW(0))
                CASE_GREATER_OR_EQUAL(4)
                SET_VALUE(LW(0), 1)
                CASE_GREATER_OR_EQUAL(2)
                SET_VALUE(LW(0), 0)
                CASE_DEFAULT
                SET_VALUE(LW(0), -1)
            END_SWITCH
            CASE_DEFAULT
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
            SWITCH(LW(0))
                CASE_GREATER_OR_EQUAL(4)
                SET_VALUE(LW(0), 1)
                CASE_GREATER_OR_EQUAL(2)
                SET_VALUE(LW(0), 0)
                CASE_DEFAULT
                SET_VALUE(LW(0), -1)
            END_SWITCH
        END_SWITCH
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            SET_VALUE(LW(1), LW(0))
            SET_VALUE(LW(2), LW(13))
            SUBTRACT(LW(2), 1)
            IF_INT_GREATER(LW(1), LW(2))
                SET_VALUE(LW(1), LW(2))
            END_IF
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(1), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(9), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(9), LW(1), LW(2))
            SET_VALUE(LW(1), LW(13))
            ADD(LW(1), 1)
            IF_INT_GREATER(LW(1), LW(14))
                CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
                CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
            END_IF
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
    ELSE
        IF_INT_GREATER_OR_EQUAL(LW(13), LW(14))
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
        ELSE
            CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 0, LW(5))
        END_IF
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    // He bounces up for the next pound until all earned pounds are used.
    LABEL(90)
    ADD(LW(13), 1)
    IF_INT_LESS_OR_EQUAL(LW(13), LW(14))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.19921875f))
        ADD(LW(1), 40)
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        GOTO(50)
    END_IF
    // He hops back down to the floor; pressing A on the landing is the stylish.
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 15, 15, 20)
    END_SIBLING_EVENT
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 25)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
    // The audience refills Star Power, then he walks home.
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
 * Yoshi's Gulp: he runs to the target's mouth point (_get_nomikomi_hit_position) and tries to swallow it.
 * Units that cannot be swallowed or a failed command just take a hit;
 * others are either spat into the enemy behind them or, by their swallowAttribute bits,
 * swallowed whole for their experience.
 */
EVT_BEGIN(partyYoshiAttack_Nomikomi)
    // Pick the target and pay the cost.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_ATE_TARGET, 0)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    // Action command (hold R, release when the light comes on): the window shrinks at higher difficulty.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(15))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 160)
        SET_VALUE(LW(1), 40)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 140)
        SET_VALUE(LW(1), 30)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 120)
        SET_VALUE(LW(1), 25)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 100)
        SET_VALUE(LW(1), 20)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 80)
        SET_VALUE(LW(1), 10)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 50)
        SET_VALUE(LW(1), 5)
        CASE_DEFAULT
        SET_VALUE(LW(0), 30)
        SET_VALUE(LW(1), 2)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 3, LW(0), LW(1), 0, 100, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 15)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 15, 1, 0)
    CALL(evt_btl_camera_set_mode, 0, 10)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, BTL_UNIT_NONE, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_StartAC, 1)
    // Once R is pressed he walks up to the enemy (a pre-emptive spiky enemy hurts him on the way).
    LABEL(5)
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        WAIT_FRAMES(1)
        GOTO(5)
    END_IF
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
        MULTIPLY_FLOAT(LW(6), 40)
        CALL(_get_nomikomi_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 80, -1, 0)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 40)
    CALL(_get_nomikomi_hit_position, BTL_UNIT_SELF, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), LW(6))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 80, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // He shoots out his tongue; a miss plays the enemy's dodge reaction.
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_2"))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW1"), 0)
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
        WAIT_FRAMES(50)
        GOTO(90)
    END_IF
    // Enemies that cannot be swallowed, or a failed command, just take a 0-damage tongue hit.
    WAIT_FRAMES(7)
    CALL(_get_swallow_param, LW(3), LW(7))
    IF_INT_EQUAL(LW(7), -1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&partyWeapon_YoshiNomikomi_Dmg0), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_PIERCE_IMMUNE, LW(5))
        WAIT_FRAMES(43)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_CLEAR(LW(0), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&partyWeapon_YoshiNomikomi_Dmg0), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_PIERCE_IMMUNE, LW(5))
        WAIT_FRAMES(43)
        GOTO(90)
    END_IF
    // Swallow attribute 8: the enemy plays its gulp reaction (damage pattern 7) and Yoshi lets it go.
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW2"), 0)
    CALL(_check_swallow_attribute, LW(3), 8, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_DamageDirect, LW(3), LW(4), 0, 0, 7, 1)
        WAIT_FRAMES(13)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_7"))
        CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW5"), 0)
        WAIT_FRAMES(34)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_5"))
        WAIT_FRAMES(54)
        GOTO(90)
    END_IF
    // He pulls the enemy into his mouth; it is hidden while inside.
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 350)
    CALL(btlevtcmd_DamageDirect, LW(3), LW(4), 0, 0, 2, 1)
    WAIT_FRAMES(3)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 12)
    CALL(btlevtcmd_DivePosition, LW(3), LW(0), LW(1), LW(2), 5, 0, 0, 0, -1)
    CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_HIDDEN)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW3"), 0)
    WAIT_FRAMES(6)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_3"))
    WAIT_FRAMES(7)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    // Roll against the enemy's swallow rate: on a pass he spits it out (as a shot at the enemies behind with
    // attribute 2), with the rating effect and a stylish chance.
    CALL(evt_sub_random, 99, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), LW(7))
        BEGIN_INLINE_EVENT
            CALL(evt_env_blur_on, 0, 600)
        END_INLINE_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_4"))
        CALL(btlevtcmd_ftomsec, 22, LW(0))
        WAIT_MS(LW(0))
        BEGIN_INLINE_EVENT_GET_ID(LW(15))
            CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_NOMIKOMI6"), 0)
            CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_HIDDEN)
            CALL(_check_swallow_attribute, LW(3), 2, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&partyWeapon_YoshiNomikomi_Spew), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_PIERCE_IMMUNE, LW(5))
            ELSE
                CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&partyWeapon_YoshiNomikomi_Shot), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_PIERCE_IMMUNE, LW(5))
            END_IF
            CALL(btlevtcmd_GetResultAC, LW(0))
            IF_BITS_SET(LW(0), 2)
                CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
            ELSE
                CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
            END_IF
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 15, 15, 20)
            CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
            SWITCH(LW(6))
                CASE_GREATER_OR_EQUAL(2)
                CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
                CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
                CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
                CASE_DEFAULT
                CALL(evt_audience_acrobat_notry)
            END_SWITCH
        END_INLINE_EVENT
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        GOTO(90)
    END_IF
    // Otherwise he swallows it whole: the enemy is removed and its experience kept.
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_YOSHI_ATE_TARGET, 1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW5"), 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_7"))
    WAIT_FRAMES(26)
    CALL(_check_swallow_attribute, LW(3), 1, LW(1))
    CALL(_check_swallow_attribute, LW(3), 4, LW(2))
    CALL(btlevtcmd_GetExp, LW(3), LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    CALL(btlevtcmd_KillUnit, LW(3), 0)
    WAIT_FRAMES(8)
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_6"))
        CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW7"), 0)
        WAIT_FRAMES(50)
        GOTO(90)
    ELSE
        IF_INT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_5"))
            CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_SWALLOW4"), 0)
            WAIT_FRAMES(54)
            GOTO(90)
        END_IF
    END_IF
    // An enemy with swallow attribute 4 lets him breathe fire over every enemy.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_4"))
    WAIT_FRAMES(22)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(18)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 15)
    SET_VALUE(LW(3), LW(0))
    SET_VALUE(LW(4), LW(1))
    SET_VALUE(LW(5), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(3), 240)
    CALL(evt_eff, STRING("eff"), STRING("breath_fire"), 1, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 1, 2, 60, FLOAT(0.5f), FLOAT(30.0f))
    WAIT_FRAMES(60)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiNomikomi_Fire))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(&partyWeapon_YoshiNomikomi_Fire), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_PIERCE_IMMUNE, LW(5))
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    // Star Power refill, then he runs home; after a whole swallow the run home ends with a stylish spin chance.
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_YOSHI_ATE_TARGET, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(4.0f), LW(5))
    IF_INT_LESS_OR_EQUAL(LW(5), 20)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        GOTO(99)
    END_IF
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SUBTRACT(LW(5), 1)
        SET_VALUE(LW(6), LW(5))
        SUBTRACT(LW(6), 10)
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, LW(6), LW(5), LW(5), 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(5), -1, 0)
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_O_1"))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_J_1B"))
        CALL(evt_sub_intpl_init, 4, 0, 360, 30)
        LOOP(30)
            CALL(evt_sub_intpl_get_value)
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, LW(0), 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_IF
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Yoshi's Mini-Egg: he lays eggs as the action command allows and throws each at a target (_egg_attack_event);
 * hits can shrink the enemies. Ends with an optional stylish.
 */
EVT_BEGIN(partyYoshiAttack_EggAttack)
    // Pay the cost and pick a random target for each of the six egg parts.
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_WeaponAftereffect, LW(0))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(3), LW(4))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 3, LW(3))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 4, LW(4))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 7, 0)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(10), LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 3, LW(10))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 4, LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 7, 0)
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(10), LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 3, LW(10))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 4, LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 7, 0)
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(10), LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 3, LW(10))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 4, LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 7, 0)
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(10), LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 3, LW(10))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 4, LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 7, 0)
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&partyWeapon_YoshiEggAttack_Minimini))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(10), LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 3, LW(10))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 4, LW(11))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 5, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 6, 0)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 7, 0)
    // Action command (press A when the light comes on to lay an egg): up to 3 eggs, 4 at Ultra rank;
    // less time at higher difficulty.
    CALL(evt_btl_camera_set_mode, 0, 10)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, BTL_UNIT_NONE, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(2)
        SET_VALUE(LW(1), 4)
        CASE_DEFAULT
        SET_VALUE(LW(1), 3)
    END_SWITCH
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 480)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 360)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 240)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 180)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 150)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 100)
        CASE_DEFAULT
        SET_VALUE(LW(0), 60)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, 0, LW(0), LW(1), 0, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_AcSetOutputParam, 1, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 20, 1, 60)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 272, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_StartAC, 1)
    SET_VALUE(LW(12), 2)
    // Wait for each egg; if the command ends with none laid he groans and the move ends.
    LABEL(5)
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(13))
    ADD(LW(13), 1)
    IF_INT_GREATER(LW(12), LW(13))
        CALL(btlevtcmd_AcGetOutputParam, 1, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_StopAC)
            WAIT_MS(500)
            CALL(btlevtcmd_AcGetOutputParam, 0, LW(13))
            IF_INT_GREATER_OR_EQUAL(LW(13), 1)
                CALL(btlevtcmd_AcGetOutputParam, 0, LW(13))
                ADD(LW(13), 1)
                GOTO(25)
            ELSE
                CALL(btlevtcmd_AudienceDeclareACResult, PTR(&partyWeapon_YoshiEggAttack_Minimini), -1)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_5"))
                WAIT_FRAMES(54)
                CALL(evt_audience_ap_recovery)
                CALL(btlevtcmd_InviteApInfoReport)
                GOTO(95)
            END_IF
        END_IF
        WAIT_FRAMES(1)
        GOTO(5)
    END_IF
    // A new egg: the rating effect for the count so far, and a random colour (green, yellow or pink).
    SET_VALUE(LW(0), LW(12))
    SUBTRACT(LW(0), 1)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(2)
        SET_VALUE(LW(0), 0)
        CASE_LESS_OR_EQUAL(3)
        SET_VALUE(LW(0), 1)
        CASE_DEFAULT
        SET_VALUE(LW(0), 2)
    END_SWITCH
    CALL(btlevtcmd_GetResultPrizeLv, BTL_UNIT_SYSTEM, LW(0), LW(6))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AudienceDeclareACResult, PTR(&partyWeapon_YoshiEggAttack_Minimini), LW(6))
    LABEL(10)
    CALL(evt_sub_random, 2, LW(0))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_y))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_p))
        CASE_DEFAULT
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_g))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(12), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 1, 4)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 2, PTR(&partyWeapon_YoshiEggAttack_Minimini))
    // The egg pops out of Yoshi with a spin and rolls to its place behind him.
    LABEL(20)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_SetPartsScale, BTL_UNIT_SELF, LW(12), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_8"))
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_12"))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(5))
    MULTIPLY_FLOAT(LW(5), 10)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), LW(5))
    ADD(LW(1), LW(5))
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPartsDispOffset, BTL_UNIT_SELF, LW(12), 0, 0, 0)
    CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 0)
    CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(12), 0, 0, 0)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG1"), 0)
    SET_VALUE(LW(15), 0)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(12), 0, 6, 0)
        LOOP(30)
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 48)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(5), LW(12))
        SUBTRACT(LW(5), 2)
        MULTIPLY_FLOAT(LW(5), 10)
        ADD_FLOAT(LW(5), 15)
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(0))
        MULTIPLY_FLOAT(LW(5), LW(0))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), LW(5))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, LW(12), FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 30, -1)
    END_SIBLING_EVENT
    WAIT_FRAMES(10)
    ADD(LW(12), 1)
    GOTO(5)
    // All eggs laid: mark the last egg aimed at each enemy, which deals that enemy's final hit.
    LABEL(25)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 2, 6, -1)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 3, 6, -1)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 4, 6, -1)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 5, 6, -1)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 6, 6, -1)
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, 7, 6, -1)
    SET_VALUE(LW(12), LW(13))
    LABEL(26)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 6, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 6, 1)
        SET_VALUE(LW(14), LW(12))
        LABEL(27)
        SUBTRACT(LW(14), 1)
        IF_INT_GREATER_OR_EQUAL(LW(14), 2)
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(0))
            CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(14), 3, LW(1))
            IF_INT_EQUAL(LW(0), LW(1))
                CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(14), 6, 0)
            END_IF
            GOTO(27)
        END_IF
    END_IF
    SUBTRACT(LW(12), 1)
    IF_INT_GREATER_OR_EQUAL(LW(12), 2)
        GOTO(26)
    END_IF
    // Decide in advance whether each egg connects; once an egg hits an enemy, the later eggs at it cannot miss.
    SET_VALUE(LW(12), 2)
    LABEL(28)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 6, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(0))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 4, LW(1))
        CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(0), LW(1), DAMAGE_FLAG_LAST_HIT, LW(6))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 5, LW(6))
        IF_INT_EQUAL(LW(6), 1)
            SET_VALUE(LW(14), LW(12))
            LABEL(29)
            ADD(LW(14), 1)
            IF_INT_LESS_OR_EQUAL(LW(14), LW(13))
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(0))
                CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(14), 3, LW(1))
                IF_INT_EQUAL(LW(0), LW(1))
                    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(14), 6, LW(0))
                    IF_INT_NOT_EQUAL(LW(0), 0)
                        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(14), 6, 2)
                    END_IF
                END_IF
                GOTO(29)
            END_IF
        END_IF
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(0))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 4, LW(1))
        CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(0), LW(1), DAMAGE_FLAG_LAST_HIT, LW(6))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 5, LW(6))
        CASE_DEFAULT
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(0))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 4, LW(1))
        CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(0), LW(1), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_ALWAYS_HIT, LW(6))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 5, LW(6))
    END_SWITCH
    IF_INT_LESS(LW(12), LW(13))
        ADD(LW(12), 1)
        GOTO(28)
    END_IF
    // He throws the eggs one by one, each with a throwing pose for its colour (_egg_attack_event).
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    SET_VALUE(LW(12), 2)
    LABEL(30)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(6), STRING("PYS_A3_1"))
        SET_VALUE(LW(7), STRING("PYS_A3_2"))
        SET_VALUE(LW(8), STRING("PYS_A3_3"))
        CASE_EQUAL(2)
        SET_VALUE(LW(6), STRING("PYS_A4_1"))
        SET_VALUE(LW(7), STRING("PYS_A4_2"))
        SET_VALUE(LW(8), STRING("PYS_A4_3"))
        CASE_DEFAULT
        SET_VALUE(LW(6), STRING("PYS_A2_1"))
        SET_VALUE(LW(7), STRING("PYS_A2_2"))
        SET_VALUE(LW(8), STRING("PYS_A2_3"))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(6))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(8))
    WAIT_FRAMES(7)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        CALL_CHILD(_egg_attack_event)
    END_SIBLING_EVENT
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 7, LW(15))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    LABEL(90)
    IF_INT_NOT_EQUAL(LW(12), LW(13))
        ADD(LW(12), 1)
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 3, LW(3))
        CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 4, LW(4))
        GOTO(30)
    END_IF
    // Stylish after the last throw, then the Star Power refill.
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 15, 15, 20)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    // Wait for every egg to land, then he runs home.
    LABEL(95)
    SET_VALUE(LW(12), 2)
    LABEL(96)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 7, LW(15))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 7, 0)
    END_IF
    ADD(LW(12), 1)
    IF_INT_LESS_OR_EQUAL(LW(12), LW(13))
        GOTO(96)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    WAIT_MS(2000)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Throws one Mini-Egg: launches egg part LW(12) from Yoshi to target LW(3)/LW(4) in a spinning arc,
 * bursts it there and applies the damage weapon in its part work 2,
 * or plays the target's dodge when part work 5 marks a miss.
 */
EVT_BEGIN(_egg_attack_event)
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
    MULTIPLY_FLOAT(LW(6), 10)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), LW(6))
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, LW(12), FLOAT(5.0f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, LW(12), FLOAT(0.099609375f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(5.0f), LW(5))
        CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
        MULTIPLY_FLOAT(LW(6), 6)
        CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(12), 0, LW(6), 0)
        LOOP(LW(5))
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 48)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG3"), 0)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG2"), 0)
    CALL(evt_eff, STRING(""), STRING("bomb"), 0, LW(0), LW(1), LW(2), FLOAT(0.5996094f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 5, LW(6))
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
        GOTO(89)
    END_IF
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 2, LW(0))
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 6, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(0), DAMAGE_FLAG_AC_SUCCESS | DAMAGE_FLAG_STATUS_ANY_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(0), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS | DAMAGE_FLAG_STATUS_ANY_HIT, LW(5))
    END_IF
    LABEL(89)
    RETURN
EVT_END()

/**
 * Yoshi's Stampede: he calls a herd of Yoshis that runs across the stage (_gundan_yoshi_run_effect)
 * while the action command builds damage, hitting every enemy as the herd passes,
 * then waits for the herd to finish.
 */
EVT_BEGIN(partyYoshiAttack_CallGuard)
    // Target every enemy and pay the cost.
    SET_VALUE(LW(12), PTR(&partyWeapon_YoshiCallGuard))
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    // Action command (alternate L and R to fill the gauge): its length depends on the difficulty.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 280)
        SET_VALUE(LW(1), 18)
        SET_VALUE(LW(2), 25)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 250)
        SET_VALUE(LW(1), 17)
        SET_VALUE(LW(2), 27)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 240)
        SET_VALUE(LW(1), 16)
        SET_VALUE(LW(2), 29)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 240)
        SET_VALUE(LW(1), 15)
        SET_VALUE(LW(2), 30)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 200)
        SET_VALUE(LW(1), 15)
        SET_VALUE(LW(2), 30)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 180)
        SET_VALUE(LW(1), 15)
        SET_VALUE(LW(2), 30)
        CASE_DEFAULT
        SET_VALUE(LW(0), 150)
        SET_VALUE(LW(1), 14)
        SET_VALUE(LW(2), 30)
    END_SWITCH
#if VERSION <= VERSION_DEMO_JP
    CALL(btlevtcmd_AcSetParamAll, 15, LW(0), 178, LW(1), LW(2), 17, 18, EVT_NULLPTR)
#else
    CALL(btlevtcmd_AcSetParamAll, 15, LW(0), 178, LW(1), LW(2), 20, 61, EVT_NULLPTR)
#endif
    CALL(btlevtcmd_AcSetGaugeParam, 60, 80, 100, 100)
    CALL(btlevtcmd_AcSetFlag, 64)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 6, 1, 0)
    // The camera pulls back; Yoshi winds up while the command runs, then calls the herd.
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_10"))
    CALL(btlevtcmd_ftof, 24, LW(0))
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_A_11"))
#if VERSION <= VERSION_DEMO_JP
    // The demo puts the effect at Yoshi's feet and plays no sound.
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    MULTIPLY(LW(5), 30)
    CALL(evt_eff, STRING(""), STRING("kiss"), 3, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
#else
    CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
    CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(0))
    MULTIPLY_FLOAT(LW(6), LW(0))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), LW(6))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    MULTIPLY(LW(5), 30)
    CALL(evt_eff, 0, STRING("kiss"), 3, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ENM_TOGENOKO_CALL1"), LW(0), LW(1), LW(2), 0)
#endif
    // Stylish chance as he calls.
    CALL(btlevtcmd_ftof, 33, LW(0))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_FRAMES(LW(0))
    END_SIBLING_EVENT
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, LW(0), LW(0), 20)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
        CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        BEGIN_SIBLING_EVENT
            WAIT_MS(166)
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
        END_SIBLING_EVENT
    END_SWITCH
    // The herd of Yoshis runs across the stage while the screen rumbles.
    BEGIN_INLINE_EVENT_GET_ID(LW(9))
        WAIT_MS(1000)
        CALL(_gundan_yoshi_run_effect, BTL_UNIT_SELF)
    END_INLINE_EVENT
    WAIT_MS(166)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_shake_h, 0, 1, 0, 6000, 0)
    WAIT_MS(1000)
    CALL(_wait_yoshig_run, BTL_UNIT_SELF)
    // Each enemy in turn as the herd reaches it: a miss plays its dodge reaction.
    SET_VALUE(LW(15), 0)
    LABEL(70)
    IF_INT_EQUAL(LW(3), -1)
        IF_INT_NOT_EQUAL(LW(15), 0)
            CALL(btlevtcmd_WaitEventEnd, LW(15))
        END_IF
        CALL(btlevtcmd_WaitEventEnd, LW(9))
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(6))
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
        GOTO(75)
    END_IF
    // The herd tramples it once per hit the gauge earned; the last trample carries the rating effect.
    CALL(btlevtcmd_AcGetOutputParam, 2, LW(14))
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        LOOP(LW(14))
            IF_INT_GREATER_OR_EQUAL(LW(14), 2)
                CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 2)
                    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_AC_SUCCESS, LW(5))
                ELSE
                    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 0, LW(5))
                END_IF
            ELSE
                CALL(btlevtcmd_AcGetOutputParam, 2, LW(0))
                SWITCH(LW(0))
                    CASE_GREATER_OR_EQUAL(6)
                    SET_VALUE(LW(0), 2)
                    CASE_GREATER_OR_EQUAL(4)
                    SET_VALUE(LW(0), 1)
                    CASE_GREATER_OR_EQUAL(2)
                    SET_VALUE(LW(0), 0)
                    CASE_DEFAULT
                    SET_VALUE(LW(0), -1)
                END_SWITCH
                IF_INT_GREATER_OR_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
                    CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
                    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
                ELSE
                    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
                    CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
                END_IF
            END_IF
            WAIT_FRAMES(10)
        END_LOOP
    END_SIBLING_EVENT
    LABEL(75)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    GOTO(70)
    // Wait for the herd to leave, stop the rumble, refill Star Power and end the turn.
    LABEL(90)
    CALL(_wait_yoshig_complete, BTL_UNIT_SELF)
    CALL(evt_btl_camera_noshake, 1)
    WAIT_MS(500)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Yoshi's Appeal (data tag 5): appeal pose and sound, then the audience is fired up. */
EVT_BEGIN(yoshi_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_APPEAL)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Victory reaction (data tag 64): plays Yoshi's PYS_Y_1 pose through twice, then his stay pose. */
static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PYS_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    RETURN
EVT_END()

/**
 * Audience-attack reaction (data tag 6): from his spot Yoshi turns to the chosen audience member
 * and throws a randomly green, yellow or pink egg (part 2) at it, which bursts on impact; no running offstage.
 */
static EVT_BEGIN(attack_audience_event)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(12), 2)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(evt_btl_camera_set_mode, 0, 13)
        CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, LW(12), LW(3))
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_btl_camera_set_zoom, 0, 200)
    END_SIBLING_EVENT
    CALL(evt_sub_random, 2, LW(0))
    CALL(btlevtcmd_SetPartsWork, BTL_UNIT_SELF, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_y))
        CASE_EQUAL(2)
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_p))
        CASE_DEFAULT
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, LW(12), PTR(pose_table_egg_g))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(12), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_SetPartsMoveSpeed, BTL_UNIT_SELF, LW(12), FLOAT(7.5f))
    CALL(btlevtcmd_SetPartsFallAccel, BTL_UNIT_SELF, LW(12), FLOAT(0.099609375f))
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPartsWork, BTL_UNIT_SELF, LW(12), 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        SET_VALUE(LW(6), STRING("PYS_A3_1"))
        SET_VALUE(LW(7), STRING("PYS_A3_2"))
        SET_VALUE(LW(8), STRING("PYS_A3_3"))
        CASE_EQUAL(2)
        SET_VALUE(LW(6), STRING("PYS_A4_1"))
        SET_VALUE(LW(7), STRING("PYS_A4_2"))
        SET_VALUE(LW(8), STRING("PYS_A4_3"))
        CASE_DEFAULT
        SET_VALUE(LW(6), STRING("PYS_A2_1"))
        SET_VALUE(LW(7), STRING("PYS_A2_2"))
        SET_VALUE(LW(8), STRING("PYS_A2_3"))
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(6))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, LW(8))
    BEGIN_SIBLING_EVENT
        WAIT_MS(1000)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    END_SIBLING_EVENT
    WAIT_FRAMES(7)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 28)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(5.0f), LW(5))
        CALL(btlevtcmd_SetPartsRotateOffset, BTL_UNIT_SELF, LW(12), 0, 6, 0)
        LOOP(LW(5))
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 48)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG3"), 0)
    CALL(btlevtcmd_DivePartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 25, 0, 0, -1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_YOSHI_EGG2"), 0)
    CALL(evt_eff, STRING(""), STRING("bomb"), 0, LW(0), LW(1), LW(2), FLOAT(0.5996094f), 0, 0, 0, 0, 0, 0, 0)
    CALL(_attack_aud, LW(3), 0)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(500)
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Empty: partner moves come from the player's menu choices, not a unit attack script. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/** Idle (retail position; the demo defines it near the top of the file): plays the stay pose from the pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
#endif

u8 _yoshig_tpl_no_tbl[8] __attribute__((aligned(4))) = { // battle tex id per sweat frame (US ids +0x16)
    VERSION_PICK(0x46, 0x5C), VERSION_PICK(0x49, 0x5F), VERSION_PICK(0x47, 0x5D), VERSION_PICK(0x46, 0x5C),
    VERSION_PICK(0x4A, 0x60), VERSION_PICK(0x48, 0x5E), 0, 0,
};

/**
 * Swaps unit args[0]'s main part to the battle model for Yoshi's hatched colour (party colour slot 4,
 * c_babyyoshi2 to c_babyyoshi7); colour 0 keeps the default green model. Blocks until the model has loaded.
 * Run from init_event.
 */
USER_FUNC(yoshi_original_color_anim_set) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnitPart* part;
    const char* name;
    s32 id;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    BattleGetUnitPtr(wp, id);
    switch (pouchGetPartyColor(4)) {
        case 1:
            name = "c_babyyoshi2";
            break;
        case 2:
            name = "c_babyyoshi3";
            break;
        case 3:
            name = "c_babyyoshi4";
            break;
        case 4:
            name = "c_babyyoshi5";
            break;
        case 5:
            name = "c_babyyoshi6";
            break;
        case 6:
            name = "c_babyyoshi7";
            break;
        case 0:
        default:
            name = NULL;
            break;
    }
    if (isFirstCall) {
        if (name == NULL) {
            return EVT_RETURN_DONE;
        }
        part = BattleGetUnitPartsPtr(id, 1);
        animPoseGetAnimPosePtr(part->poseId);
        if (part->poseId != -1) {
            animPoseRelease(part->poseId);
            part->poseId = -1;
        }
    }
    if (animEffectAsync(name, 1)) {
        part = BattleGetUnitPartsPtr(id, 1);
        part->poseId = animPoseEntry(name, 1);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

#define ADD_WEAPON(w)                                                               \
    command->weapon[*count].index = -1;                                             \
    command->weapon[*count].itemId = 0;                                             \
    command->weapon[*count].weapon = (BattleWeapon*)(w);                            \
    command->weapon[*count].enabled = 0;                                            \
    command->weapon[*count].icon = command->weapon[*count].weapon->icon;            \
    command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name); \
    (*count)++;

/**
 * Builds Yoshi's battle move list (data tag 1):
 * Ground Pound and Gulp always, Mini-Egg from Super rank and Stampede from Ultra rank,
 * appending each to command->weapon and advancing *count.
 */
static void __makeTechMenuFunc(BattleCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));
    ADD_WEAPON(&partyWeapon_YoshiNormalAttack)
    if (techLv >= 0) {
        ADD_WEAPON(&partyWeapon_YoshiNomikomi_Shot)
    }
    if (techLv >= 1) {
        ADD_WEAPON(&partyWeapon_YoshiEggAttack_Minimini)
    }
    if (techLv >= 2) {
        ADD_WEAPON(&partyWeapon_YoshiCallGuard)
    }
}

/**
 * Sets up Ground Pound's flutter for unit args[0] towards (args[1], args[2], args[3]):
 * a 180-frame move whose horizontal speed covers the X distance.
 * Returns the speed in args[4] and the frame count in args[5].
 */
USER_FUNC(btl_yoshi_yoroyoro_jump_calc_param) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, outSpeed, outFrames;
    f32 tx, ty, tz, speed;
    f32 x, y, z;
    EvtWord* args = event->args;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    outSpeed = args[4];
    speed = evtGetFloat(event, outSpeed);
    unit = BattleGetUnitPtr(wp, id);
    outFrames = args[5];
    if (speed > 0.0f) {
        unit->moveSpeedXZ = speed;
    }
    if (unit->moveSpeedXZ <= 0.0f) {
        unit->moveSpeedXZ = 1.0f;
    }
    BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
    BtlUnit_GetPos(unit, &x, &y, &z);
    BtlUnit_SetMoveStartPos(unit, x, y, z);
    BtlUnit_SetMoveCurrentPos(unit, x, y, z);
    unit->moveAngle = angleABf(x, z, tx, tz);
    unit->moveDistance = distABf(x, z, tx, tz);
    if (tx - x > 0.0f) {
        unit->moveDirection = 1;
    } else if (tx - x < 0.0f) {
        unit->moveDirection = -1;
    }
    unit->moveDistance = __fabs(tx - x);
    unit->moveFrames = 180;
    unit->moveProgress = (f32)unit->moveFrames;
    unit->moveSpeedY = 0.0f;
    unit->moveSpeedXZ = unit->moveDistance / (f32)unit->moveFrames;
    evtSetFloat(event, outSpeed, unit->moveSpeedXZ);
    evtSetValue(event, outFrames, unit->moveFrames);
    return EVT_RETURN_DONE;
}

/**
 * Runs the flutter set up by btl_yoshi_yoroyoro_jump_calc_param one frame per call:
 * drifts unit args[0] toward the target while bobbing up and down, sets the slide sound volume in UW_YOSHI_SLIDE_SOUND_PERCENT,
 * and spawns a sweat drop every 20 frames. Blocks until the 180 frames are over, then snaps to the target.
 */
USER_FUNC(btl_yoshi_yoroyoro_jump_move) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 id;
    f32 sweatAngle;
    EffectEntry* eff;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    evtGetValue(event, args[3]);
    evtGetFloat(event, args[4]);
    unit = BattleGetUnitPtr(wp, id);
    evtGetValue(event, args[5]);
    if (isFirstCall) {
        event->blocked = 1;
        event->userdata[1] = 20;
        event->userdata[2] = 0;
    }
    if (unit->moveCurrentPos.x != unit->moveTargetPos.x) {
        if (__fabs(unit->moveTargetPos.x - unit->moveCurrentPos.x) < unit->moveSpeedXZ) {
            unit->moveCurrentPos.x = unit->moveTargetPos.x;
            if (!unit->moveCurrentPos.z) {
            }
        } else {
            unit->moveCurrentPos.x += unit->moveSpeedXZ * unit->moveDirection;
        }
    }
    if (unit->moveCurrentPos.z != unit->moveTargetPos.z) {
        if (__fabs(unit->moveTargetPos.z - unit->moveCurrentPos.z) < unit->moveSpeedXZ) {
            unit->moveCurrentPos.z = unit->moveTargetPos.z;
        } else if (unit->moveTargetPos.z - unit->moveStartPos.z > 0.0f) {
            unit->moveCurrentPos.z += unit->moveSpeedXZ;
        } else {
            unit->moveCurrentPos.z -= unit->moveSpeedXZ;
        }
    }
    sweatAngle = 10.0f * sinfd(180.0f + 360.0f * (unit->moveProgress - (f32)(unit->moveFrames % 90)) / 90.0f);
    BtlUnit_GetPartsPtr(unit, 1);
    unit->moveCurrentPos.y = unit->moveSpeedY + (unit->moveStartPos.y + (unit->moveTargetPos.y - unit->moveStartPos.y) * (unit->moveProgress - (f32)unit->moveFrames) / unit->moveProgress);
    unit->moveSpeedY = sweatAngle;
    unit->work[UW_YOSHI_SLIDE_SOUND_PERCENT] = (s32)(75.0f - 25.0f * sinfd(360.0f * (unit->moveProgress - (f32)(unit->moveFrames % 90)) / 90.0f));
    BtlUnit_SetPos(unit, unit->moveCurrentPos.x, unit->moveCurrentPos.y, unit->moveCurrentPos.z);
    event->userdata[1]++;
    if (event->userdata[1] > 20) {
        event->userdata[1] = 0;
        if (unit->moveDirection >= 0) {
            sweatAngle = -50.0f;
        } else {
            sweatAngle = 50.0f;
        }
        event->userdata[2] = (EvtWord)effSweatN64Entry(1, unit->moveCurrentPos.x, unit->moveCurrentPos.y + unit->sizeMultiplier * (0.5f * BtlUnit_GetHeight(unit)), unit->moveCurrentPos.z, 5.0f * unit->sizeMultiplier, sweatAngle, 16);
    } else {
        eff = (EffectEntry*)event->userdata[2];
        if (event->userdata[1] < 16) {
            ((EffSweatN64Work*)eff->userdata)->position.x = unit->moveCurrentPos.x;
            ((EffSweatN64Work*)eff->userdata)->position.y = unit->moveCurrentPos.y + unit->sizeMultiplier * (0.5f * BtlUnit_GetHeight(unit));
            ((EffSweatN64Work*)eff->userdata)->position.z = unit->moveCurrentPos.z;
        }
    }
    unit->moveFrames--;
    if (unit->moveFrames <= 0) {
        BtlUnit_SetPos(unit, unit->moveTargetPos.x, unit->moveTargetPos.y, unit->moveTargetPos.z);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Pose sound callback for Yoshi's walk, run and flutter poses:
 * plays the footstep sound at volume UW_YOSHI_SLIDE_SOUND_POWER * UW_YOSHI_SLIDE_SOUND_PERCENT / 100.
 */
static void _yoshi_slide_move_sound(BattleUnit* unit, PoseSoundTiming* s) {
    BtlUnit_snd_se(unit, s->sfxName, -250000000, (s16)(unit->work[UW_YOSHI_SLIDE_SOUND_POWER] * unit->work[UW_YOSHI_SLIDE_SOUND_PERCENT] / 100)); // slide sound volume
}

/**
 * Returns in args[3]-args[5] where Yoshi's tongue should reach target unit args[1] for Gulp:
 * its position plus its bintaHitOffset (scaled by size, X mirrored by facing).
 * args[0] and args[2] (the part) are read but not used.
 */
static USER_FUNC(_get_nomikomi_hit_position) {
    BattleWork* wp;
    EvtWord* args;
    BattleUnit* unit;
    Vec pos;
    s32 id, targetId, dir;
    s32 outZ, outX, outY;

    wp = _battleWorkPointer;
    args = event->args;
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

/** Returns unit args[0]'s swallowRate in args[1]; Gulp treats -1 as cannot be swallowed. */
static USER_FUNC(_get_swallow_param) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    s32 out;
    EvtWord* args = event->args;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    out = args[1];
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, out, unit->swallowRate);
    return EVT_RETURN_DONE;
}

/**
 * Returns 1 in args[2] if unit args[0]'s swallowAttribute has any of the bits in args[1], else 0.
 * Gulp checks bit 8 (hurts when swallowed), 2 (spat as a shot) and 1 and 4 (how it is swallowed whole).
 */
static USER_FUNC(_check_swallow_attribute) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, out;
    u16 mask;
    EvtWord* args = event->args;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    mask = args[1];
    out = args[2];
    unit = BattleGetUnitPtr(wp, id);
    if ((u8)unit->swallowAttribute & mask) {
        evtSetValue(event, out, 1);
    } else {
        evtSetValue(event, out, 0);
    }
    return EVT_RETURN_DONE;
}

/**
 * Blocks until the Stampede herd of unit args[0] exists
 * and its average position (work timer) has crossed the stage centre, so the attack can start hitting enemies.
 */
static USER_FUNC(_wait_yoshig_run) {
    BattleUnit* unit;
    YoshiGundanWork* w;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    w = (YoshiGundanWork*)unit->countersetWeapon;
    if (w == NULL) {
        return EVT_RETURN_BLOCK;
    }
    if (w->timer <= 0.0f) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

/** Blocks until unit args[0]'s Stampede herd has run off and its work (kept in countersetWeapon) is freed. */
static USER_FUNC(_wait_yoshig_complete) {
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (unit->countersetWeapon) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

/**
 * Moves one Stampede Yoshi (index i) for a frame:
 * on the first call places it in a 16-wide grid off the left edge with a random speed and small depth drift,
 * then runs it right, bouncing between the depth limits, until it reaches X 300.
 * Returns FALSE once it has finished.
 */
static inline s32 _gundan_part_update(YoshiGundanPart* p, s32 i) {
    switch (p->state) {
        case 0:
            p->state++;
            p->delay = irand(3);
            p->x = (f32)(-(i / 16 * 30 + 300) + irand(10));
            p->y = 0.0f;
            p->z = (f32)(i % 16 * 10 - 80);
            p->frame = irand(6);
            p->frameCount = irand(5);
            p->vx = 0.1f * (f32)irand(10) + 3.0f;
            p->vy = 0.0f;
            p->vz = 0.001f * (f32)(irand(2000) - 1000);
        case 1:
            if (p->delay > 0) {
                p->delay--;
                break;
            }
        case 2:
            p->z += p->vz;
            if (p->z >= VERSION_PICK(80.0f, 65.0f)) {
                p->z = VERSION_PICK(80.0f, 65.0f);
                p->vz *= -1.0f;
            }
            if (p->z <= -80.0f) {
                p->z = -80.0f;
                p->vz *= -1.0f;
            }
            p->x += p->vx;
            if (p->x >= 300.0f) {
                p->x = 300.0f;
                p->vx = 0.0f;
                p->state = 999;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

/**
 * Runs the Stampede herd for unit args[0]: allocates 256 running Yoshi sprites (work stored in
 * countersetWeapon), moves them each frame with dust puffs and a run sound that follows the herd's average X,
 * draws them, and frees the work and stops the sound when all are across.
 * The US and PAL releases cap the herd's depth at 65 instead of 80.
 */
static USER_FUNC(_gundan_yoshi_run_effect) {
    BattleUnit* unit;
    YoshiGundanWork* w;
    YoshiGundanPart* p;
    s32 i;
    s32 allDone;
    Vec pos;
    s32 id;

    do {
        id = evtGetValue(event, event->args[0]);
        id = BattleTransID(event, id);
        unit = BattleGetUnitPtr(_battleWorkPointer, id);
        if (isFirstCall) {
            w = BattleAlloc(sizeof(YoshiGundanWork));
            unit->countersetWeapon = (BattleWeapon*)w;
            memset(w, 0, sizeof(YoshiGundanWork));
            w->state = 0;
            w->timer = 0.0f;
            event->userdata[0] = 0;
            {
                Vec tmp;
                tmp.x = (f32)id;
            }
            event->userdata[1] = psndSFXOn("SFX_BTL_YOSHI_TAIGUN1");
        } else {
            w = (YoshiGundanWork*)unit->countersetWeapon;
        }
        switch (w->state) {
            case 0:
                w->state++;
            case 1:
                w->timer = 0.0f;
                allDone = TRUE;
                for (i = 0; i < 256; i++) {
                    p = &w->parts[i];
                    p->frameCount++;
                    if (p->frameCount > 2) {
                        p->frameCount = 0;
                        p->frame++;
                        if (p->frame >= 6) {
                            p->frame = 0;
                        }
                    }
                    if (_gundan_part_update(p, i)) {
                        allDone = FALSE;
                    }
                    w->timer += p->x;
                }
                if (event->userdata[0] > 0) {
                    event->userdata[0]--;
                } else {
                    f32 sc;
                    p = &w->parts[irand(256)];
                    sc = 1.0f + 0.05f * (f32)irand(20);
#if VERSION <= VERSION_DEMO_JP
                    effKemuTestEntry(0, p->x, 5.0f + p->y + (f32)irand(10), p->z, sc);
#else
                    effKemuTestEntry(0, p->x, 5.0f + p->y + (f32)irand(15), 65.0f, sc);
#endif
                }
                w->timer *= 0.00390625f;
                pos.x = w->timer;
                pos.y = 0.0f;
                pos.z = 0.0f;
                psndSFX_pos(event->userdata[1], &pos);
                if (allDone) {
                    w->state = 999;
                }
                break;
            case 999:
                psndSFXOff(event->userdata[1]);
                BattleFree(unit->countersetWeapon);
                unit->countersetWeapon = NULL;
                return EVT_RETURN_DONE;
        }
#if VERSION <= VERSION_DEMO_JP
        // The demo draws every Yoshi from one display callback.
        dispEntry(CAMERA_3D, 0.0f, 2, (DispCallback)_btlYoshiDisp, w);
#else
        for (i = 0; i < 256; i++) {
            dispEntry(CAMERA_3D, dispCalcZ((Vec*)p), VERSION_PICK(2, 1), (DispCallback)_btlYoshiDisp, &w->parts[i]);
        }
#endif
    } while (0);
    return EVT_RETURN_BLOCK;
}
/**
 * Display callback that draws the Stampede Yoshis as textured planes,
 * animated from _yoshig_tpl_no_tbl and flipped by run direction.
 * The US demo draws all 256 in one call; later releases register one call per Yoshi.
 */
#if VERSION <= VERSION_DEMO_JP
static void _btlYoshiDisp(CameraId camera, YoshiGundanWork* w) {
    YoshiGundanPart* p;
    s32 i;
    f32 s;
    for (i = 0; i < 256; i++) {
        p = &w->parts[i];
        s = (p->vx < 0.0f) ? 0.4f : -0.4f;
        ((BtlDispTexPlaneFloatsFirstFn)btlDispTexPlane)(p->x, p->y + 20.0f, p->z, s, 0.4f, _yoshig_tpl_no_tbl[p->frame], (GXColor){255, 255, 255, 255}, 0);
    }
}
#else
/** Draws one Stampede Yoshi (later releases). */
static void _btlYoshiDisp(CameraId camera, YoshiGundanPart* p) {
    f32 s;
    s = (p->vx < 0.0f) ? 0.4f : -0.4f;
    ((BtlDispTexPlaneFloatsFirstFn)btlDispTexPlane)(p->x, p->y + 20.0f, p->z, s, 0.4f, _yoshig_tpl_no_tbl[p->frame], (GXColor){255, 255, 255, 255}, 0);
}
#endif

/**
 * Stand-in for a function the linker stripped (in no version's symbols);
 * never called, it only creates the int-to-float conversion constant in .sdata2
 * so the pool keeps its original order.
 */
// FAKE: uncalled stand-in for a stripped function; places the int-to-float double in .rodata
void yoshiStrippedPool(f32* f, s32 i) {
    *f = (f32)i;
}
