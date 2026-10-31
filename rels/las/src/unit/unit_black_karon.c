// Palace of Shadow battle unit: the Dark Bones (`black_karon`): parts, stats, poses and AI scripts.

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

// Unit work slots of the Dark Bones (btlevtcmd_SetUnitWork / GetUnitWork)
enum {
    UW_BLACK_KARON_SPIN_DONE = 0,     // set to 1 to stop the spin loop of a thrown bone once it has landed
    UW_BLACK_KARON_REWARD_GIVEN = 1,  // 1 once its coins and Star Points were paid out on the first collapse
    UW_BLACK_KARON_REBIRTH_TURNS = 2, // turns left until a collapsed Dark Bones rebuilds itself (0 when standing)
    UW_BLACK_KARON_LINK_HIT = 3,      // 1 once a bone of the three-bone throw has hit, so the later ones hit too
    UW_BLACK_KARON_LINK_BONES = 4,    // bones of the three-bone throw launched so far; -1 once the last one is done
};

static USER_FUNC(honenoko_copy_status);
extern BattleUnitKind unit_karon;

BattleUnitKind unit_black_karon;
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

/**
 * Unit data of the Dark Bones in the Palace of Shadow: 20 HP, level 34;
 * names its parts, status table and init script.
 */
BattleUnitKind unit_black_karon = {
    131,
    "btl_un_black_karon",
    20,
    0,
    1,
    1,
    34,
    0,
    3,
    100,
    3,
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
    UNIT_ATTR_REVIVES_AFTER_KO,
    &regist,
    6,
    parts,
    init_event,
    data_table,
};

/**
 * Defence of the Dark Bones against each element (normal, fire, ice, explosion, electric):
 * 2 against every element, so each hit is cut by 2.
 */
static BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

/**
 * Damage modifiers of the Dark Bones per element (normal, fire, ice, explosion, electric):
 * none, so no element is a weakness, an immunity or a heal.
 */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo values of the status vulnerability of the Dark Bones:
 * percent chance that each status takes hold (100 is normal); immune to Sleep, Poison, Fright;
 * strongly resistant to Dizzy, Confuse, Frozen, Tiny, Attack Down, Defense Down, Allergic, Slow.
 */
static StatusVulnerability regist = {0, 85, 40, 0, 40, 100, 100, 40, 100, 40, 100, 40, 100, 40, 40, 0, 50, 100, 40, 100, 100, 85};
#else
/**
 * JP, US and PAL values of the status vulnerability of the Dark Bones:
 * percent chance that each status takes hold (100 is normal); immune to Sleep, Poison, Fright;
 * strongly resistant to Dizzy, Confuse.
 */
static StatusVulnerability regist = {0, 65, 20, 0, 20, 100, 100, 60, 100, 80, 100, 80, 100, 80, 60, 0, 60, 100, 60, 100, 100, 85};
#endif

/** Parts of the Dark Bones: the body and the bones (parts 2 to 6) it throws and piles up. */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_black_karon", "c_karon_b_h", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
    {2, "btl_un_black_karon", "c_karon_b_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {3, "btl_un_black_karon", "c_karon_b_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {4, "btl_un_black_karon", "c_karon_b_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {5, "btl_un_black_karon", "c_nagehone", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
    {6, "btl_un_black_karon", "c_karon_h", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW | PART_ATTR_WORLD_POSITION, 0, pose_table},
};

/** Weapon of the Dark Bones' bone throw: damage 5. */
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

/** Weapon of one bone of the Dark Bones' three-bone throw: damage 3. */
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
 * Setup used to spawn a Dry Bones (called by the Dark Bones): unit kind, alliance, position and turn phase.
 */
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

/**
 * Pose table of the Dark Bones: animation names for each pose type (idle, walk, hurt, attack and so on).
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
 * Data table of the Dark Bones: event scripts and values the battle looks up by tag (damage reactions,
 * dodge, first strike and so on).
 */
static BattleDataEntry data_table[] = {
    {49, dead_event},
    {15, fake_dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Init event of the Dark Bones: installs its wait, attack, damage and confusion events,
 * sets the thrown-bone part poses (KRN_H_1) and the landing sound,
 * and clears unit work 1 (the flag that the death reward was already given).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 3, STRING("KRN_H_1"))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 4, STRING("KRN_H_1"))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REWARD_GIVEN, 0)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("0"), STRING("SFX_ENM_HONENOKO_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Dark Bones: runs the default damage handling on its body part (unit LW(10) = -2, part 1). */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Dead event of the Dark Bones: it spins for 48 frames with the death sound, a smoke puff appears and the coins,
 * experience and star points are awarded once (unit work 1 guards it);
 * then it tips over and the unit is killed: KO'd and deleted
 * when the hit defeated it for good (damage flag 0x400,
 * which a reviving unit only gets from fire or explosions), otherwise only marked inactive (KILL_UNIT_INACTIVE).
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REWARD_GIVEN, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REWARD_GIVEN, 1)
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
 * Event when the Dark Bones runs out of HP but can rebuild itself:
 * it moves to its home position, awards the reward once,
 * collapses into a pile of bones (KRN_D_2, crumble sound),
 * stays there for a second and sets unit work 2 to 2 or 3,
 * the number of turns until rebirth_event brings it back.
 */
static EVT_BEGIN(fake_dead_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(2), LW(3), LW(4), 0, -1, 0)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REWARD_GIVEN, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REWARD_GIVEN, 1)
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REBIRTH_TURNS, LW(0))
    CALL(btlevtcmd_SetHitOffset, LW(10), LW(11), 0, -20, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Turn event of the collapsed Dark Bones: counts unit work 2 down and, when it reaches zero,
 * reassembles it (KRN_D_3 and KRN_D_4 with the reunite sounds),
 * clears attribute 0x20000 and restores its HP to the maximum.
 */
static EVT_BEGIN(rebirth_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REBIRTH_TURNS, LW(0))
    SUBTRACT(LW(0), 1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REBIRTH_TURNS, LW(0))
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
 * Attack event of the Dark Bones: when confused it throws a plain bone;
 * when collapsed it rebuilds itself (rebirth_event);
 * otherwise it can use an item, or draws a number from 0 to 99:
 * bone throw (50), three-bone throw (30) or calling a Dry Bones friend (20).
 * For the call it first checks that there is room beside it by turning to both sides with btlevtcmd_CheckSpace.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(normal_attack_event)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_REBIRTH_TURNS, LW(0))
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
 * Helper child script of the bone throw: given the pre-check result in LW(5) it makes the target start its dodge
 * reaction (avoid type 38, 39 or 40) as the bone passes it.
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
 * Attack of the Dark Bones: it picks a target (weapon_honenoko_attack),
 * winds up (KRN_A_1, KRN_A_2) and throws a spinning bone (part 2) in an arc;
 * the target can dodge as the bone passes (start_avoid).
 * If the bone is not avoided it lands on the target with the action command defence check,
 * and the bone then bounces off.
 */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), BATTLE_FLAG_FIRST_ATTACK)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        // Pick a target for the attack; a confused unit that has none flusters.
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
    // Announce the attack; the camera swings to follow it.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(500)
    // Wind up and raise a bone above its head.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_2"))
    WAIT_MS(250)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_BONE_THROW2"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 2, STRING("KRN_H_1"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, 0)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, LW(14))
            IF_INT_EQUAL(LW(14), 1)
                BREAK_LOOP
            END_IF
            // The bone spins as it is hurled at the target in an arc.
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, 2, 0, 0, 25)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    // Find out whether the attack will connect or miss.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
                CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
                IF_INT_LESS_OR_EQUAL(LW(0), LW(6))
                    // The target can dodge as the bone passes.
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
    // The bone sails on past the target and drops.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(8.0f), FLOAT(0.049804688f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    GOTO(98)
    // The attack connects.
    LABEL(91)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    // The bone lands on the target.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(8.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(evt_btl_camera_set_mode, 0, 0)
    // Deal the damage, reduced by the action command defence.
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_honenoko_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -50)
    // The bone bounces off the target.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, 2, 0, FLOAT(2.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, 2, LW(0), LW(1), LW(2), 0, 0)
    GOTO(98)
    // Wrap up the attack.
    LABEL(98)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, 1)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 2, PART_ATTR_NO_SHADOW)
    WAIT_FRAMES(10)
    // The attack is over; back to waiting.
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Helper child script of the three-bone throw: like start_avoid but the pre-check result comes from LW(11). */
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
 * Attack of the Dark Bones: three bones thrown at one target in sequence (weapon_honenoko_link_attack).
 * It spawns link_attack_event_sub for bone parts 2, 3 and 4, 40 and 35 frames apart,
 * and waits until the last one has finished (unit work 4 = -1).
 */
static EVT_BEGIN(link_attack_event)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_HIT, 0)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_honenoko_link_attack))
    CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_honenoko_link_attack), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_BONES, 0)
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
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_BONES, LW(0))
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
 * One bone of the three-bone throw of the Dark Bones: LW(12) is the bone part (2, 3 or 4).
 * Wind-up, a spinning arc to the target and dodge or hit handling as in normal_attack_event;
 * the third bone does the damage check, and if an earlier bone hit,
 * unit work 3 makes the following ones hit too.
 */
static EVT_BEGIN(link_attack_event_sub)
    // Wind up and raise a bone above its head.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_A_2"))
    WAIT_MS(250)
    CALL(btlevtcmd_AddUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_BONES, 1)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_BONES, LW(13))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_SEND_GROUP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_BONE_THROW3"), EVT_NULLPTR, 0, LW(15))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, LW(12), STRING("KRN_H_1"))
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, 0)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, LW(14))
            IF_INT_EQUAL(LW(14), 1)
                BREAK_LOOP
            END_IF
            // The bone spins as it is hurled at the target in an arc.
            CALL(btlevtcmd_AddPartsRotate, BTL_UNIT_SELF, LW(12), 0, 0, 25)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), DAMAGE_FLAG_LAST_HIT, LW(11))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), DAMAGE_FLAG_LAST_HIT, LW(11))
    END_IF
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_HIT, LW(14))
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
                    // The target can dodge as the bone passes.
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
    // The bone sails on past the target and drops.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(8.0f), FLOAT(0.049804688f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    GOTO(98)
    LABEL(91)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_HIT, 1)
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 14)
    CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    // The bone lands on the target.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(8.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_honenoko_link_attack))
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_honenoko_link_attack), 0, LW(5))
    END_IF
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), -50)
    // The bone bounces off the target.
    CALL(btlevtcmd_JumpPartsSetting, BTL_UNIT_SELF, LW(12), 0, FLOAT(2.0f), FLOAT(0.2998047f))
    CALL(btlevtcmd_JumpPartsPosition, BTL_UNIT_SELF, LW(12), LW(0), LW(1), LW(2), 0, 0)
    GOTO(98)
    LABEL(98)
    IF_INT_EQUAL(LW(13), 3)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, 1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_LINK_BONES, -1)
    END_IF
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_HIDDEN)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, LW(12), PART_ATTR_NO_SHADOW)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Call-for-help move of the Dark Bones: the camera zooms in and, six times,
 * it throws up pieces of itself (parts and poses KRN_H_x, KRN_C_x) which pile up beside it;
 * the pile reassembles (KRN_D_3, KRN_D_4) and a new Dry Bones unit (entry_honenoko, whose kind is unit_karon) is
 * spawned in that spot,
 * copying its status (honenoko_copy_status).
 */
static EVT_BEGIN(call_friend_event)
    // The camera zooms in on the Dark Bones.
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    SET_VALUE(LW(10), 0)
    LOOP(6)
        // It throws up pieces of itself, one by one, and they pile up beside it.
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
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, 1, LW(4), LW(5), LW(6))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(4), 15)
        ADD(LW(5), 14)
        CALL(btlevtcmd_SetPartsPos, BTL_UNIT_SELF, 5, LW(4), LW(5), LW(6))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, 0)
            SET_VALUE(LW(15), 0)
            LOOP(0)
                CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BLACK_KARON_SPIN_DONE, LW(14))
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
            CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
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
        CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 5, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        ADD(LW(10), 1)
    END_LOOP
    WAIT_FRAMES(15)
    // The pile reassembles into a Dry Bones.
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_D_3"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 6, STRING("KRN_D_4"))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_HONENOKO_UNITE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("KRN_S_1"))
    // The new Dry Bones appears in that spot, copying the status of its caller.
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_honenoko), 0)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 6, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(honenoko_copy_status, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_mode, 0, 0)
    RETURN
EVT_END()

/** Wait event of the Dark Bones: plays the idle pose from its pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: copies the shrink/grow status (sizeChangeTurns and sizeChangeStrength) from the unit in args[0]
 * to the unit in args[1], so a revived or called-in bone keeps the caller's size effect.
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
