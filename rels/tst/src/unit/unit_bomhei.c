// Battle unit Bob-omb (`bomhei`): tst.rel's copy of rels/jon/src/unit/unit_bomhei.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"

// Unit work slots of the Bob-omb (btlevtcmd_Get/SetUnitWork).
enum {
    UW_BOMHEI_FUSE_SFX = 0, // handle of the looping fuse sound, -1 when none is playing
};

BattleUnitKind unit_bomhei;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_spark[18];
static BattleDataEntry data_table[2];
static BattleDataEntry data_table_spark[2];
static BattleUnitKindPart parts[1];
static StatusVulnerability regist;
static BattleWeapon weapon_bomhei_attack;
static BattleWeapon weapon_bomhei_bomb;
static EvtWord init_event[42];
#if VERSION <= VERSION_DEMO_JP
static EvtWord damage_event[55];
#else
static EvtWord damage_event[58];
#endif
static EvtWord change_spark_event[70];
static EvtWord attack_event[440];
static EvtWord wait_event[6];
#if VERSION <= VERSION_DEMO_JP
static EvtWord damage_event_spark[22];
#else
static EvtWord damage_event_spark[25];
#endif
#if VERSION <= VERSION_DEMO_JP
static EvtWord attack_event_spark[286];
#else
static EvtWord attack_event_spark[288];
#endif
static EvtWord wait_event_spark[27];

/**
 * Unit kind of Bob-omb: 4 max HP, level 12. The battle engine reads it when the unit spawns:
 * size, offsets, sounds, status vulnerability, parts, init script and event table.
 */
BattleUnitKind unit_bomhei = {
    43,
    "btl_un_bomhei",
    4,
    0,
    1,
    1,
    12,
    0,
    1,
    70,
    1,
    50,
    9999,
    32,
    30,
    4,
    30,
    0.0f,
    15.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    16.0f,
    0.0f,
    0.0f,
    11.0f,
    16.0f,
    0.0f,
    2.0f,
    15.0f,
    0.0f,
    32.0f,
    30.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BOMB_DAMAGED1",
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

/**
 * Defence of Bob-omb per element (normal, fire, ice, explosion, electric), subtracted from each hit:
 * 1 against every element.
 */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Element reactions of Bob-omb: none, every element hits normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/**
 * Pose table of Bob-omb: maps its battle pose types (stay, walk, hurt, dead, talk and so on) to animation
 * names, 18 entries such as BOM_N_1, BOM_Y_1, BOM_K_1, BOM_X_1.
 */
static PoseTableEntry pose_table[] = {
    {1, "BOM_N_1"},
    {2, "BOM_Y_1"},
    {9, "BOM_Y_1"},
    {5, "BOM_K_1"},
    {4, "BOM_X_1"},
    {3, "BOM_X_1"},
    {BTL_POSE_NORMAL, "BOM_S_1"},
    {29, "BOM_Q_1"},
    {30, "BOM_Q_1"},
    {31, "BOM_S_1"},
    {BTL_POSE_DAMAGE, "BOM_D_1"},
    {50, "BOM_A_1"},
    {BTL_POSE_RUN, "BOM_R_1"},
    {BTL_POSE_WALK, "BOM_W_1"},
    {BTL_POSE_DANGER, "BOM_X_1"},
    {BTL_POSE_PERIL, "BOM_X_1"},
    {BTL_POSE_TALK, "BOM_T_1"},
    {BTL_POSE_STAY_DEFAULT, "BOM_S_1"},
};

/**
 * Pose table of Bob-omb with its fuse lit: maps its battle pose types (stay, walk, hurt, dead, talk and
 * so on) to animation names, 19 entries such as BOM_N_2, BOM_Y_2, BOM_K_2, BOM_X_2.
 */
static PoseTableEntry pose_table_spark[] = {
    {1, "BOM_N_2"},
    {2, "BOM_Y_2"},
    {9, "BOM_Y_2"},
    {5, "BOM_K_2"},
    {4, "BOM_X_2"},
#if VERSION <= VERSION_DEMO_JP
    {3, "BSA_X_2"},
#else
    {3, "BOM_X_2"},
#endif
    {BTL_POSE_NORMAL, "BOM_S_2"},
    {29, "BOM_Q_2"},
    {30, "BOM_Q_2"},
    {31, "BOM_S_2"},
    {BTL_POSE_DAMAGE, "BOM_D_2"},
    {50, "BOM_A_2"},
    {BTL_POSE_RUN, "BOM_R_2"},
    {BTL_POSE_WALK, "BOM_W_2"},
    {BTL_POSE_DANGER, "BOM_X_2"},
    {BTL_POSE_PERIL, "BOM_X_2"},
    {BTL_POSE_TALK, "BOM_T_2"},
    {BTL_POSE_STAY_DEFAULT, "BOM_S_2"},
};

/**
 * Event table of Bob-omb: maps event tags to the scripts that react to them (no custom reactions);
 * tag 0 ends it.
 */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Event table of Bob-omb with its fuse lit: maps event tags to the scripts that react to them (no custom
 * reactions); tag 0 ends it.
 */
static BattleDataEntry data_table_spark[] = {
    {48, btldefaultevt_Dummy},
    {0},
};

/**
 * Body parts of Bob-omb: a single part (model c_bomhey) holding its hit box.
 * Each part names its defence tables and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_bomhei", "c_bomhey", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, COUNTER_ATTR_EXPLOSIVE, pose_table},
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of Bob-omb (the demos), as the percent chance a status takes hold:
 * immune to Poison; always hit by Electric, Burn, Huge, Attack Up, Defense Up, Fast, Dodgy and Invisible;
 * otherwise Sleep 70, Stop 80, Dizzy 80, Confuse 80, Freeze 70, Tiny 80, Attack Down 80, Defense Down 80,
 * Allergic 80, Fright 90, Gale Force 80, Slow 80 and instant KO 95.
 */
static StatusVulnerability regist = {70, 80, 80, 0, 80, 150, 100, 70, 100, 80, 100, 80, 100, 80, 80, 90, 80, 100, 80, 100, 100, 95};
#else
/**
 * Status vulnerability of Bob-omb (the final versions), as the percent chance a status takes hold:
 * immune to Poison; always hit by Stop, Electric, Burn, Freeze, Huge, Attack Up, Defense Up, Fast,
 * Dodgy and Invisible; otherwise Sleep 70, Dizzy 70, Confuse 70, Tiny 90, Attack Down 90,
 * Defense Down 95, Allergic 80, Fright 90, Gale Force 80, Slow 80 and instant KO 95.
 */
static StatusVulnerability regist = {70, 100, 70, 0, 70, 150, 100, 100, 100, 90, 100, 90, 100, 95, 80, 90, 80, 100, 80, 100, 100, 95};
#endif

/** Attack data of Bob-omb's attack: base damage 2, 100% accuracy. */
static BattleWeapon weapon_bomhei_attack = {
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
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
    0, // counterResistFlags
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

/** Attack data of Bob-omb's bomb attack: base damage 5, 100% accuracy. */
static BattleWeapon weapon_bomhei_bomb = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    2, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_CEILING | TARGET_PROP_SHELL_TOSS_LIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_BOMB_FLIPPABLE, // special
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
    {0, 25, 25, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * The Bob-omb explodes: it shakes the camera, hides itself,
 * stops the fuse hiss (unit work 0 is the sound handle, then -1),
 * plays SFX_BTL_ENEMY_DIE1_2 and SFX_BTL_ENM_BOMB_ATTACK2 with the sandars blast effect, clears any fog,
 * stores its coin and experience rewards, waits one second and removes itself from the battle.
 * When it was set off by its own attack (LW(15) = 1 in the later versions) it first waits for that attack to
 * end.
 */
static EVT_BEGIN(bomb_event)
    CALL(evt_btl_camera_shake_w, 0, 5, 0, 15, 0)
    CALL(btlevtcmd_OnAttribute, BTL_UNIT_SELF, UNIT_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOMHEI_FUSE_SFX, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_snd_sfxoff, LW(0))
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOMHEI_FUSE_SFX, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_ENM_BOMB_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING(""), STRING("sandars"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_StageDispellFog)
    CALL(btlevtcmd_GetCoin, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreCoin, LW(0))
    CALL(btlevtcmd_GetExp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_StoreExp, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        LOOP(LW(0))
        END_LOOP
    END_IF
    WAIT_MS(1000)
#if VERSION <= VERSION_DEMO_JP
    CALL(btlevtcmd_WaitAttackEnd)
#else
    IF_INT_EQUAL(LW(15), 1)
        CALL(btlevtcmd_WaitAttackEnd)
    END_IF
#endif
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 0)
    RETURN
EVT_END()

/**
 * Init script of the Bob-omb: registers its wait, attack, damage and confusion handlers,
 * sets unit work 0 to -1 (fuse not lit yet) and sets the walk and run sounds.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOMHEI_FUSE_SFX, -1)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 4, 4)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE2"), STRING("SFX_ENM_BOMB_MOVE2"), 0, 10, 10)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage reaction of the Bob-omb: a last hit (DAMAGE_FLAG_LAST_HIT) of fire, explosion or electric type
 * (damage codes 24, 25, 27) sets it off at once (bomb_event);
 * otherwise it takes the default damage and, if it is still alive and able to act,
 * lights its fuse (change_spark_event).
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_LAST_HIT, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(27)
            CASE_OR_EQUAL(25)
#if VERSION >= VERSION_JP
            SET_VALUE(LW(15), 1)
#endif
            CALL_CHILD(bomb_event)
            RETURN
            CASE_END
        END_SWITCH
    END_IF
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_INSTANT_KILL, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(change_spark_event)
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Switches the Bob-omb to its lit-fuse state after it was hurt:
 * plays SFX_ENM_BOMB_SPARK1, installs the spark wait, attack,
 * damage and confusion handlers (wait_event_spark and so on), the spark pose table and data table,
 * and sets the counter attribute 8192 on its body. Does nothing if the hit was the 256 type or did no HP damage.
 */
static EVT_BEGIN(change_spark_event)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
    CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, DAMAGE_FLAG_LAST_HIT, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetHpDamage, BTL_UNIT_SELF, LW(15))
    IF_INT_GREATER_OR_EQUAL(LW(15), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_SPARK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event_spark))
        CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event_spark))
        CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event_spark))
        CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event_spark))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_spark))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_DAMAGE)
        CALL(btlevtcmd_OnPartsCounterAttribute, BTL_UNIT_SELF, 1, COUNTER_ATTR_VOLATILE_EXPLOSIVE)
        CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table_spark))
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * The Bob-omb's attack with the fuse unlit: uses an item or picks a target,
 * scurries toward it (SFX_ENM_BOMB_MOVE1, pose type 42) and rams it;
 * a miss lets it dodge past, a hit applies the damage with SFX_ENM_BOMB_MOVE3, and it walks back.
 */
static EVT_BEGIN(attack_event)
    // The Bob-omb first checks whether to use a held item instead of attacking.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // It picks a target; with none, it ends the turn (or flusters when confused).
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_bomhei_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#else
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
#endif
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_bomhei_attack))
    // The attack is declared and paid for, and the camera follows the Bob-omb.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It hops twice toward the target with its walking sound, then runs the rest of the way.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    // The damage check decides between a miss and a hit.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // On a miss it runs past the target, turns around and stands there for a moment.
    LABEL(90)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_WALK)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 90)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("BOM_N_1"))
#if VERSION <= VERSION_DEMO_JP
    WAIT_MS(1000)
#else
    WAIT_MS(500)
#endif
    GOTO(98)
    // On a hit the action-command defence is resolved and the Bob-omb bumps the target for damage.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_bomhei_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(2.0f), FLOAT(0.5f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 75)
    // It hops back toward its home position.
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(1.0f), FLOAT(0.5f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 100)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 20, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE4"), STRING("SFX_ENM_BOMB_MOVE4"), 0, 10, 10, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
#if VERSION <= VERSION_DEMO_JP
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
#else
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
#endif
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 1)
    // It faces forward again and returns to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle event: sets the unit's body part 1 to the pose given by its pose table for its current state. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Damage reaction of the lit Bob-omb: a hit with damage code bit 256 sets it off at once (bomb_event);
 * anything else is the default damage handling.
 */
static EVT_BEGIN(damage_event_spark)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_LAST_HIT, LW(0))
    IF_INT_EQUAL(LW(0), 1)
#if VERSION >= VERSION_JP
        SET_VALUE(LW(15), 1)
#endif
        CALL_CHILD(bomb_event)
    ELSE
        CALL_CHILD(btldefaultevt_Damage)
    END_IF
    RETURN
EVT_END()

/**
 * The lit Bob-omb's attack: it picks a target with weapon_bomhei_bomb,
 * runs at it with the fuse sparking and explodes (bomb_event) on it, whether the attack hits or is avoided.
 */
static EVT_BEGIN(attack_event_spark)
    // The lit Bob-omb first checks whether to use a held item instead of attacking.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    // It picks a target; with none, it ends the turn (or flusters when confused).
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_bomhei_bomb), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#else
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
#endif
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_bomhei_bomb))
    // The attack is declared and paid for, and the camera follows the Bob-omb.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    // It hops twice toward the target with its walking sound, then runs the rest of the way with the fuse sparking.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_MOVE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 10)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_btl_camera_set_mode, 0, 0)
#endif
    // The damage check decides between a miss and a hit.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_bomb), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // On a miss it still reaches the target and explodes beside it.
    LABEL(90)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 500)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
#if VERSION >= VERSION_JP
    SET_VALUE(LW(15), 0)
#endif
    CALL_CHILD(bomb_event)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
    // On a hit the action-command defence is resolved and the Bob-omb blows up on the target.
    LABEL(91)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_bomhei_bomb))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_bomhei_bomb), DAMAGE_FLAG_LAST_HIT, LW(5))
#if VERSION >= VERSION_JP
    SET_VALUE(LW(15), 0)
#endif
    CALL_CHILD(bomb_event)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    RETURN
    // The camera returns to normal.
    LABEL(98)
    WAIT_MS(1000)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Idle event of the lit Bob-omb: shows its pose from the spark pose table and,
 * while the fuse has not gone off (unit work 0 = -1),
 * plays the SFX_ENM_BOMB_WAIT1 fuse hiss and stores the sound handle in unit work 0.
 */
static EVT_BEGIN(wait_event_spark)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BOMHEI_FUSE_SFX, LW(15))
    IF_INT_EQUAL(LW(15), -1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_BOMB_WAIT1"), EVT_NULLPTR, 0, LW(15))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BOMHEI_FUSE_SFX, LW(15))
    END_IF
    RETURN
EVT_END()
