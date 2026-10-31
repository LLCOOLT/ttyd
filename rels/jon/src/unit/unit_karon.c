// Pit of 100 Trials battle unit: the Dry Bones (`karon`): parts, stats, poses and AI scripts.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "evt/evt_sub.h"

static USER_FUNC(honenoko_copy_status);

BattleUnitKind unit_karon;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[6];
static BattleWeapon weapon_honenoko_attack;
static BattleWeapon weapon_honenoko_link_attack;
static BattleUnitSetup entry_honenoko;
static PoseTableEntry pose_table[19];
static BattleDataEntry data_table[4];
static EvtWord init_event[46];
static EvtWord damage_event[10];
static EvtWord dead_event[190];
static EvtWord fake_dead_event[165];
static EvtWord attack_event[196];
static EvtWord normal_attack_event[428];
static EvtWord link_attack_event[111];
static EvtWord link_attack_event_sub[402];
static EvtWord call_friend_event[311];
static EvtWord wait_event[6];

BattleUnitKind unit_karon = {
    130,
    "btl_un_karon",
    8,
    0,
    1,
    1,
    30,
    0,
    2,
    70,
    2,
    50,
    9999,
    36,
    40,
    -4,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
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
    9.0f,
    24.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    36.0f,
    40.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_HONENOKO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x10000,
    &regist,
    6,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {0, 70, 60, 0, 60, 100, 100, 60, 100, 60, 100, 60, 100, 60, 60, 10, 70, 100, 60, 100, 100, 90};
#else
static StatusVulnerability regist = {0, 75, 30, 0, 30, 100, 100, 70, 100, 90, 100, 90, 100, 85, 70, 0, 70, 100, 70, 100, 100, 90};
#endif

static BattleUnitKindPart parts[] = {
    {1, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_karon", "c_nagehone", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static BattleWeapon weapon_honenoko_attack = {
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
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE, // special
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

static BattleWeapon weapon_honenoko_link_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
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

static BattleUnitSetup entry_honenoko = {
    &unit_karon, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

static PoseTableEntry pose_table[] = {
    {1, "KRN_N_1"},
    {2, "KRN_Y_1"},
    {9, "KRN_Y_1"},
    {5, "KRN_K_1"},
    {4, "KRN_X_1"},
    {3, "KRN_X_1"},
    {27, "KRN_Z_2"},
    {28, "KRN_S_1"},
    {29, "KRN_Q_1"},
    {30, "KRN_Q_1"},
    {31, "KRN_S_1"},
    {39, "KRN_D_1"},
    {50, "KRN_A_1"},
    {42, "KRN_R_1"},
    {40, "KRN_W_1"},
    {56, "KRN_X_1"},
    {57, "KRN_X_1"},
    {BTL_POSE_TALK, "KRN_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KRN_S_1"},
};

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {15, fake_dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Init script of the Dry Bones: registers its wait, attack, damage and confusion handlers,
 * puts its three bone parts (2 to 4) in the KRN_H_1 pose,
 * clears unit work 1 (set once its reward has been paid out)
 * and sets its landing sound (SFX_ENM_HONENOKO_LANDING1).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_H_1"))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("0"), STRING("SFX_ENM_HONENOKO_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage script of the Dry Bones: runs the default damage handling on itself. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Real defeat script of the Dry Bones (data event 49):
 * it spins for 48 frames (SFX_BTL_ENEMY_DIE1_1) and bursts into smoke.
 * Its coins and experience are stored only if they were not paid already (unit work 1, which fake_dead_event
 * also sets), a star-point effect shows the experience, it tips over,
 * returns any item it held and is removed from the battle.
 */
static EVT_BEGIN(dead_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(0), 48)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LABEL(10)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 0, -15, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
        CALL(btlevtcmd_GetCoin, LW(10), LW(0))
        CALL(btlevtcmd_StoreCoin, LW(0))
        CALL(btlevtcmd_GetExp, LW(10), LW(0))
        CALL(btlevtcmd_StoreExp, LW(0))
        CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
        ADD(LW(2), 10)
        ADD(LW(1), 30)
        CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            LOOP(LW(0))
            END_LOOP
        END_IF
    END_IF
    CALL(btlevtcmd_SetRotateOffset, LW(10), 0, 0, 0)
    SET_VALUE(LW(0), 30)
    LABEL(20)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_AddRotate, LW(10), 3, 0, 0)
    SUBTRACT(LW(0), 1)
    IF_INT_GREATER(LW(0), 0)
        GOTO(20)
    END_IF
    CALL(btlevtcmd_GetBackItem, LW(10))
    CALL(btlevtcmd_CheckDamageCode, LW(10), 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

/**
 * Collapse script of the Dry Bones (data event 15):
 * it walks home, pays its coins and experience out once (unit work 1), shows the star-point effect,
 * crumbles into a pile of bones (KRN_D_2, SFX_ENM_HONENOKO_CRUMBLE1)
 * and is taken off the field for 2 to 3 turns (unit work 2), after which rebirth_event brings it back.
 * Its hit offset is lowered by 20.
 */
static EVT_BEGIN(fake_dead_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(2), LW(3), LW(4), 0, -1, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
        SET_VALUE(LW(10), -2)
        CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_BTL_ENEMY_DIE1_2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        ADD(LW(2), 10)
        CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
        CALL(btlevtcmd_GetCoin, LW(10), LW(0))
        CALL(btlevtcmd_StoreCoin, LW(0))
        CALL(btlevtcmd_GetExp, LW(10), LW(0))
        CALL(btlevtcmd_StoreExp, LW(0))
        CALL(btlevtcmd_GetPos, LW(10), LW(3), LW(1), LW(2))
        ADD(LW(2), 10)
        ADD(LW(1), 30)
        CALL(_add_star_point_disp_offset, LW(10), LW(3), LW(1), LW(2))
        CALL(evt_eff, STRING(""), STRING("star_point"), 0, LW(3), LW(1), LW(2), LW(0), 0, 0, 0, 0, 0, 0, 0)
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            LOOP(LW(0))
            END_LOOP
        END_IF
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_D_2"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_CRUMBLE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_MS(1000)
    CALL(btlevtcmd_KillUnit, BTL_UNIT_SELF, 2)
    CALL(evt_sub_random, 2, LW(0))
    ADD(LW(0), 2)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, -20, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Count-down for a collapsed Dry Bones, run from its attack script:
 * unit work 2 goes down by one each turn, and at 0 it pieces itself back together (KRN_D_3 and D_4,
 * SFX_ENM_HONENOKO_UNITE1 and UNITE2) with full HP and a normal hit offset.
 */
static EVT_BEGIN(rebirth_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_D_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_D_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, 131072)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Attack script of the Dry Bones. On a first strike it just throws its bone.
 * If it is collapsed (unit work 2 above 0) it runs rebirth_event.
 * Otherwise, after an item check, it draws a random number:
 * 50 in 100 for a single bone throw, 30 in 100 for the three-bone link attack
 * and 20 in 100 to call a friend (call_friend_event, trying space to its right first and then to its left).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL_CHILD(rebirth_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    LABEL(0)
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 30)
    ADD(LW(0), 20)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 50)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    ADD(LW(0), 30)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(link_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
        SET_VALUE(LW(4), LW(0))
        CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
        MULTIPLY(LW(4), LW(5))
        IF_INT_LESS(LW(4), 0)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(call_friend_event)
                WAIT_MS(500)
                GOTO(99)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 180, 0)
                CALL_CHILD(call_friend_event)
                CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
                WAIT_MS(500)
                GOTO(99)
            END_IF
        ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    GOTO(0)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Plays the avoid reaction on the target in LW(3) (animation 38, 39 or 40) according to the pre-damage result in
 * LW(5): 3, 6 or 2.
 */
static EVT_BEGIN(start_avoid)
    IF_INT_EQUAL(LW(5), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(5), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(5), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

/**
 * The Dry Bones' single bone throw: it rears back (KRN_A_1 and A_2) and throws a bone (part 2,
 * spinning at 25 degrees a frame, SFX_ENM_HONENOKO_BONE_THROW2) at the target.
 * A dodging target gets its avoid reaction (start_avoid) as the bone reaches it,
 * and the damage is dealt on impact. The bone then lands behind the target and is hidden again.
 * After a first strike it pauses first. When confused with no target it is flustered.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_honenoko_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_honenoko_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_2"))
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_BONE_THROW2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(14))
            IF_INT_EQUAL(LW(14), 1)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 25)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_attack), 256, LW(5))
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
    LABEL(90)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            ELSE
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_GREATER_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(9))
    MULTIPLY(LW(0), LW(9))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(8.0f), FLOAT(0.049804688f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(8.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_attack), 256, LW(5))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -50)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(2.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    GOTO(98)
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, 33554432)
    WAIT_FRAMES(10)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Plays the avoid reaction on the target in LW(3) (animation 38, 39 or 40) according to the pre-damage result in
 * LW(11): 3, 6 or 2. Used by the link attack's bones.
 */
static EVT_BEGIN(start_avoid2)
    IF_INT_EQUAL(LW(11), 3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
    END_IF
    IF_INT_EQUAL(LW(11), 6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
    END_IF
    IF_INT_EQUAL(LW(11), 2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
    END_IF
    RETURN
EVT_END()

/**
 * The Dry Bones' link attack: it picks a target and throws three bones (parts 2, 3 and 4) one after another,
 * 40 and 35 frames apart, each from link_attack_event_sub.
 * It waits until all three are done (unit work 4 reaches -1).
 */
static EVT_BEGIN(link_attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_honenoko_link_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_honenoko_link_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_honenoko_link_attack))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_honenoko_link_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    SET_VALUE(LW(12), 2)
    SPAWN_EVENT(link_attack_event_sub)
    WAIT_FRAMES(40)
    SET_VALUE(LW(12), 3)
    SPAWN_EVENT(link_attack_event_sub)
    WAIT_FRAMES(35)
    SET_VALUE(LW(12), 4)
    SPAWN_EVENT(link_attack_event_sub)
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    WAIT_MS(300)
    RETURN
EVT_END()

/**
 * One bone throw of the link attack, with the bone part in LW(12).
 * The Dry Bones rears back (KRN_A_1 and A_2) and throws a bone (SFX_ENM_HONENOKO_BONE_THROW3) that spins at the
 * target.
 * The target is checked in turn; only the last bone (LW(13) = 3) reads the defence action command result
 * and uses the full damage argument 256. Each bone lands behind the target and is hidden again.
 */
static EVT_BEGIN(link_attack_event_sub)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_2"))
    WAIT_MS(250)
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, 4, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(13))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_BONE_THROW3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(12), STRING("KRN_H_1"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), 16777216)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), 33554432)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(14))
            IF_INT_EQUAL(LW(14), 1)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 25)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), 256, LW(11))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), 256, LW(11))
    END_IF
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(14))
        IF_INT_EQUAL(LW(14), 1)
            GOTO(91)
        END_IF
    END_IF
    SWITCH(LW(11))
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
    LABEL(90)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid2)
                    BREAK_LOOP
                END_IF
            ELSE
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_GREATER_OR_EQUAL(LW(0), LW(6))
                    CALL_CHILD(start_avoid2)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(0), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(9))
    MULTIPLY(LW(0), LW(9))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(8.0f), FLOAT(0.049804688f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(8.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_honenoko_link_attack))
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), 256, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), 0, LW(5))
    END_IF
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -50)
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(2.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    GOTO(98)
    LABEL(98)
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, -1)
    END_IF
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), 16777216)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), 33554432)
    LABEL(99)
    RETURN
EVT_END()

/**
 * The Dry Bones calls a friend: it winds up six times (KRN_A_3 and A_4) while bone parts 5
 * and 6 act out a hand-over in the KRN_H and KRN_C poses (SFX_ENM_HONENOKO_SEND_GROUP1 and 2).
 * A heap then re-forms (KRN_D_3, KRN_D_4) and a new Dry Bones (entry_honenoko) is spawned in the free spot,
 * copying its size status through honenoko_copy_status.
 * Guess: the pose sequence is the new Bones being assembled from the thrown bones.
 */
static EVT_BEGIN(call_friend_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    SET_VALUE(LW(10), 0)
    LOOP(6)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_3"))
        WAIT_FRAMES(5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_4"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SWITCH(LW(10))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_4"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_5"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_5"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_3"))
            CASE_EQUAL(4)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_3"))
            CASE_DEFAULT
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 5, STRING("KRN_H_2"))
        END_SWITCH
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, 50331648)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(4), LW(5), LW(6))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(4), 15)
        ADD(LW(5), 14)
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 5, LW(4), LW(5), LW(6))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
            SET_VALUE(LW(15), 0)
            LOOP(0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(14))
                IF_INT_EQUAL(LW(14), 1)
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 5, 0, 0, LW(15))
                ADD(LW(15), 25)
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 5, 0, FLOAT(6.0f), FLOAT(1.0f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2), 20, 0)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 5, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 6, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SWITCH(LW(10))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_C_5"))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, 50331648)
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_C_4"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_C_3"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_C_2"))
            CASE_EQUAL(4)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_C_1"))
            CASE_DEFAULT
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_Z_2"))
        END_SWITCH
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, 50331648)
        ADD(LW(10), 1)
    END_LOOP
    WAIT_FRAMES(15)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_D_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_D_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_S_1"))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_honenoko), 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, 50331648)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(honenoko_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Wait script: plays the Dry Bones' idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: args[0] = source unit, args[1] = destination unit.
 * Copies the size-change status (turns and strength) from the Bones unit to the unit it has just spawned in its
 * place (entry_honenoko).
 */
static USER_FUNC(honenoko_copy_status) {
    EvtWord* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->sizeChangeTurns = unit1->sizeChangeTurns;
    unit2->sizeChangeStrength = unit1->sizeChangeStrength;
    return EVT_RETURN_DONE;
}
