// unit_honenoko: Dull Bones, battle unit.

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

// Unit work slots of the Dull Bones.
enum {
    UW_HONENOKO_BONE_LANDED = 0,  // set to 1 when the thrown bone lands; stops its spin loop
    UW_HONENOKO_REWARD_GIVEN = 1, // 1 once the coins, experience and star points were awarded
    UW_HONENOKO_REVIVE_TURNS = 2, // turns left until the collapsed Dull Bones rebuilds itself (0: standing)
};

static USER_FUNC(honenoko_copy_status);

BattleUnitKind unit_honenoko;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[4];
static BattleWeapon weapon_honenoko_attack;
static BattleUnitSetup entry_honenoko;
static PoseTableEntry pose_table[19];
static BattleDataEntry data_table[4];
static EvtWord init_event[31];
static EvtWord damage_event[10];
static EvtWord dead_event[190];
static EvtWord fake_dead_event[165];
static EvtWord attack_event[185];
static EvtWord normal_attack_event[428];
static EvtWord call_friend_event[311];
static EvtWord wait_event[6];

/**
 * Script helper: arg0 = source unit, arg1 = destination unit;
 * copies the size-change status (Mini/Giant turns and strength),
 * used when a Dull Bones is rebuilt after collapsing.
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

/**
 * Unit data of the Dull Bones: 1 HP and level 9, with its parts, status vulnerability, init event and
 * event data table.
 */
BattleUnitKind unit_honenoko = {
    17,
    "btl_un_honenoko",
    1,
    0,
    1,
    1,
    9,
    0,
    0,
    70,
    1,
    70,
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
    18.0f,
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
    0,
    &regist,
    4,
    parts,
    init_event,
    data_table,
};

/** Defense of the Dull Bones against normal, fire, ice, explosion and electric attacks: 1, 1, 1, 1, 1. */
static BattleUnitDefense defence = {{1, 1, 1, 1, 1}};

/** Damage-type reactions of the Dull Bones: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Dull Bones (both demos), as the percent chance each status takes hold:
 * immune to sleep and poison; resists 12 statuses (down to 10% of the normal chance).
 */
static StatusVulnerability regist = {0, 60, 50, 0, 50, 100, 100, 90, 100, 90, 100, 90, 100, 90, 90, 10, 90, 100, 90, 100, 100, 50};
#else
/**
 * Status vulnerability of the Dull Bones (the retail releases), as the percent chance each status takes
 * hold: immune to sleep and poison; resists 10 statuses (down to 10% of the normal chance).
 */
static StatusVulnerability regist = {0, 95, 50, 0, 50, 100, 100, 90, 100, 100, 100, 100, 100, 95, 90, 10, 90, 100, 90, 100, 100, 50};
#endif

/**
 * Parts of the Dull Bones: 4 parts: parts 1 and 2 (model c_karon_g_h), part 3 (model c_nagehone_g) and
 * part 4 (model c_karon_g_h), each with its defense tables, attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_honenoko", "c_karon_g_h", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
    {2, "btl_un_honenoko", "c_karon_g_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_honenoko", "c_nagehone_g", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_honenoko", "c_karon_g_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon record of the Dull Bones' bone throw: 2 damage. */
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
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Setup of the extra Dull Bones that call_friend_event summons: unit kind, side, turn phase and starting
 * position.
 */
static BattleUnitSetup entry_honenoko = {
    &unit_honenoko, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/**
 * Pose table of the Dull Bones: maps each battle pose (idle, hurt, attacking and so on) to its animation,
 * named KRN_*.
 */
static PoseTableEntry pose_table[] = {
    {1, "KRN_N_1"},
    {2, "KRN_Y_1"},
    {9, "KRN_Y_1"},
    {5, "KRN_K_1"},
    {4, "KRN_X_1"},
    {3, "KRN_X_1"},
    {27, "KRN_Z_2"},
    {BTL_POSE_NORMAL, "KRN_S_1"},
    {29, "KRN_Q_1"},
    {30, "KRN_Q_1"},
    {31, "KRN_S_1"},
    {BTL_POSE_DAMAGE, "KRN_D_1"},
    {50, "KRN_A_1"},
    {BTL_POSE_RUN, "KRN_R_1"},
    {BTL_POSE_WALK, "KRN_W_1"},
    {BTL_POSE_DANGER, "KRN_X_1"},
    {BTL_POSE_PERIL, "KRN_X_1"},
    {BTL_POSE_TALK, "KRN_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KRN_S_1"},
};

/**
 * Event data table of the Dull Bones: scripts that replace the standard handling for its defeat (tag 49)
 * and running out of HP (it crumbles but can be rebuilt) (tag 15).
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {15, fake_dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Init event of the Dull Bones: registers its wait, attack, damage and confusion events,
 * clears unit work 1 (the rewards-paid flag), sets the landing sound for jumps and starts the wait event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REWARD_GIVEN, 0)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("0"), STRING("SFX_ENM_HONENOKO_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event: runs the default battle damage reaction on the unit itself (part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Final death of the Dull Bones: it spins around quickly with the defeat sound, puffs smoke,
 * pays its coins and EXP (once, tracked in unit work 1,
 * since a crumbled Dull Bones may already have paid) with a star-point effect,
 * spins for 30 more frames and removes the unit (KillUnit mode 2, or 0 when the hit has damage-code bit 1024).
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REWARD_GIVEN, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REWARD_GIVEN, 1)
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
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_DEFEATED, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_KillUnit, LW(10), 0)
    ELSE
        CALL(btlevtcmd_KillUnit, LW(10), 2)
    END_IF
    RETURN
EVT_END()

/**
 * Data event 15 of the Dull Bones, run when it runs out of HP:
 * it walks back to its home position and, the first time only (unit work 1), pays out its coins,
 * experience and star points with a smoke puff.
 * It then crumbles into a pile of bones (KRN_D_2, SFX_ENM_HONENOKO_CRUMBLE1),
 * and after a second is taken out of play with HP 0 (KillUnit with the inactive flag, UNIT_ATTR_INACTIVE).
 * Unit work 2 gets a countdown of 2 to 4, which rebirth_event lowers by one each turn, rebuilding it at 0;
 * the hit offset is lowered by 20 and the wait event restarts.
 */
static EVT_BEGIN(fake_dead_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(2), LW(3), LW(4), 0, -1, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REWARD_GIVEN, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REWARD_GIVEN, 1)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REVIVE_TURNS, LW(0))
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, -20, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Runs instead of the Dull Bones' attack while it is a heap of bones: counts the countdown in unit work 2 down;
 * when it reaches zero it plays the bones coming together ("KRN_D_3" and "KRN_D_4" with the unite sounds),
 * clears attribute 0x20000 (UNIT_ATTR_INACTIVE), restores full HP and resets the hit offset.
 */
static EVT_BEGIN(rebirth_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REVIVE_TURNS, LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REVIVE_TURNS, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_D_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_D_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_OffAttribute, BTL_UNIT_SELF, UNIT_ATTR_INACTIVE)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHitOffset, BTL_UNIT_SELF, 1, 0, 0, 0)
    RETURN
EVT_END()

/**
 * Attack event of the Dull Bones: a first strike uses normal_attack_event.
 * A heap of bones (unit work 2 above 0) runs rebirth_event.
 * Otherwise it uses an enemy item if one fits, then a roll of 0-99 under 85 picks the bone throw
 * and anything else makes it look around for open floor beside it (CheckSpace)
 * and call a friend with call_friend_event, trying the other side if the first has no room.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_REVIVE_TURNS, LW(0))
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
    SET_VALUE(LW(0), 85)
    ADD(LW(0), 0)
    ADD(LW(0), 15)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    SET_VALUE(LW(0), 85)
    IF_INT_LESS(LW(1), LW(0))
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LOOP(1)
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
    LOOP(1)
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
 * Starts the target's dodge animation (LW(3) is the target) according to the pre-check result in LW(5):
 * 3 (dodged by luck) plays avoid 38, 6 (Dodgy) avoid 39, 2 (plain miss) avoid 40.
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
 * The Dull Bones' bone throw (weapon_honenoko_attack):
 * winds up for half a second, then throws a bone (part 2) spinning at the target.
 * A miss triggers the target's dodge when the bone passes and it flies on to the edge of the stage;
 * a hit drops the bone on the target (guard judged with ResultACDefence), which bounces off.
 * The bone is then hidden and the Dull Bones returns to its stance.
 */
static EVT_BEGIN(normal_attack_event)
    // Use the target of the opening first attack if there was one, otherwise choose a target.
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_honenoko_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_honenoko_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_honenoko_attack))
    // The attack is announced and Dull Bones turns to face its target.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(500)
    // Dull Bones winds up, pulls a bone out of itself and holds it overhead.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_2"))
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    // The bone is hurled and spins through the air toward the target.
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_BONE_THROW1"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_BONE_LANDED, 0)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_BONE_LANDED, LW(14))
            IF_INT_EQUAL(LW(14), 1)
                BREAK_LOOP
            END_IF
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 25)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // Find out how the target reacts to the thrown bone.
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
    // The throw missed: the bone sails past the target, and anyone it passes jumps out of its way.
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
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(6.0f), FLOAT(0.049804688f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    GOTO(98)
    // The bone hits: the damage is applied, then the bone drops to the ground.
    LABEL(91)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(6.0f), FLOAT(0.19921875f))
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
    // The bone is taken back and Dull Bones returns to its idle pose.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_BONE_LANDED, 1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    WAIT_FRAMES(10)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * The Dull Bones calls a friend: it throws six bones (parts 3 and 4 alternately with different poses) one
 * after another at the free spot, which pile up there;
 * they then reunite with the unite sounds and a new Dull Bones is spawned from entry_honenoko at that spot,
 * copying the status of the caller (honenoko_copy_status).
 */
static EVT_BEGIN(call_friend_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    SET_VALUE(LW(10), 0)
    // Dull Bones calls for help: it rattles and sends a bone flying up, which lands as a pile of bones.
    LOOP(6)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_3"))
        WAIT_FRAMES(5)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_4"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SWITCH(LW(10))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_4"))
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_5"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_5"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_3"))
            CASE_EQUAL(4)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_3"))
            CASE_DEFAULT
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_2"))
        END_SWITCH
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(4), LW(5), LW(6))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(4), 15)
        ADD(LW(5), 14)
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 3, LW(4), LW(5), LW(6))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_BONE_LANDED, 0)
            SET_VALUE(LW(15), 0)
            LOOP(0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_HONENOKO_BONE_LANDED, LW(14))
                IF_INT_EQUAL(LW(14), 1)
                    BREAK_LOOP
                END_IF
                CALL(btlevtcmd_SetPartsRotate, BTL_UNIT_SELF, 3, 0, 0, LW(15))
                ADD(LW(15), 25)
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 3, 0, FLOAT(6.0f), FLOAT(1.0f))
        CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 3, LW(0), LW(1), LW(2), 20, 0)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 3, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 4, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        SWITCH(LW(10))
            CASE_EQUAL(0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_C_5"))
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
            CASE_EQUAL(1)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_C_4"))
            CASE_EQUAL(2)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_C_3"))
            CASE_EQUAL(3)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_C_2"))
            CASE_EQUAL(4)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_C_1"))
            CASE_DEFAULT
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_Z_2"))
        END_SWITCH
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 3, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        ADD(LW(10), 1)
    END_LOOP
    WAIT_FRAMES(15)
    // The pile reassembles into a new Dull Bones with a joining sound.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_D_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_D_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_S_1"))
    // The new Dull Bones joins the battle and copies the status of the one that called it.
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_honenoko), 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 4, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(honenoko_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Wait event: sets the idle animation from the unit's pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
