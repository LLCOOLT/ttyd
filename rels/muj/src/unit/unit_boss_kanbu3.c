// Keelhaul Key (muj) battle unit: Lord Crump (kanbu3): its parts, defence/status tables, and attack events.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_snd.h"
#include "battle/battle_database_common.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_sub.h"
#include "evt/evt_batstage.h"
#include "evt/evt_eff.h"
#include "evt/evt_msg.h"
#include "evt/evt_sub.h"
#include "muj.h"
#include "version.h"

USER_FUNC(check_exist_group);
extern s32 down_ceil[];
extern BattleUnitKind unit_gundan_zako_magician;
extern s32 zakogun_escape3[];
extern s32 zakogun_ext_init2[];

BattleUnitKind unit_boss_kanbu3;
static BattleUnitDefense defence;
static BattleUnitDefense defence_guard;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[3];
BattleDataEntry data_table2[2];
static BattleUnitKindPart parts[1];
BattleWeapon weapon_kanbu3_attack;
BattleWeapon weapon_kanbu3_charge;
BattleUnitSetup entry_kenkyu;
BattleUnitSetup entry_group1;
BattleUnitSetup entry_group2;
BattleUnitSetup entry_group3;
static EvtWord init_event[59];
static EvtWord entry_event[45];
#if VERSION >= VERSION_US
static EvtWord damage_event[337];
#else
static EvtWord damage_event[315];
#endif
#if VERSION <= VERSION_DEMO_US
static EvtWord dead_event[393];
#else
static EvtWord dead_event[402];
#endif
static EvtWord phase_event[55];
extern EvtWord call_event[];
static EvtWord attack_event[136];
static EvtWord guard_event[56];
static EvtWord guard_cancel_event[69];
extern EvtWord no_event[];
static EvtWord charge_event[71];
static EvtWord wait_event[6];
static PoseTableEntry pose_table[18];
static PoseTableEntry pose_table_guard[18];
static EvtWord normal_attack_event[365];

BattleUnitKind unit_boss_kanbu3 = {
    99,
    "btl_un_kanbu3",
    30,
    0,
    1,
    1,
    57,
    0,
    0,
    100,
    0,
    50,
    8,
    56,
    59,
    0,
    56,
    0.0f,
    26.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    28.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    18.0f,
    38.35f,
    0.0f,
    0.0f,
    26.0f,
    0.0f,
    42.0f,
    52.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_KANBU_DAMAGED1",
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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefense defence_guard = {{2, 2, 2, 2, 2}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {80, 70, 60, 100, 60, 100, 100, 60, 100, 60, 100, 60, 100, 50, 60, 0, 0, 100, 60, 100, 0, 0};
#else
static StatusVulnerability regist = {80, 70, 60, 100, 80, 100, 100, 60, 100, 85, 100, 85, 100, 90, 60, 0, 0, 100, 60, 100, 0, 0};
#endif

static BattleDataEntry data_table[] = {
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

BattleDataEntry data_table2[] = {
    {48, btldefaultevt_Dummy},
    {0},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kanbu3", "c_kanbu", 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

BattleWeapon weapon_kanbu3_attack = {
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
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_HAMMERLIKE | TARGET_PROP_FRONTMOST | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED, // special
    0, // counterResistFlags
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

BattleWeapon weapon_kanbu3_charge = {
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
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    3, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleUnitSetup entry_kenkyu = {
    &unit_gundan_zako_magician, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_group1 = {
    &unit_boss_gundan_zako_group1, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_group2 = {
    &unit_boss_gundan_zako_group2, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

BattleUnitSetup entry_group3 = {
    &unit_boss_gundan_zako_group3, // unitKindParams
    1, // alliance
    {0}, // pad_05
    BATTLE_PHASE_ENEMY, // attackPhase
    {-1000.0f, -1000.0f, -1000.0f}, // position
    0, // hitOffsetX
    {0}, // unitWork
    NULL, // itemDropTable
};

/** Guess: init event of Lord Crump: sets his work values (formation, guard and charge state) and his pose tables. */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(entry_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_MOVE1L"), STRING("SFX_BOSS_KANBU_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    CALL_CHILD(zakogun_entry)
    CALL(zakogun_ext_init1)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Guess: entry event of Lord Crump: his entrance into the battle. */
static EVT_BEGIN(entry_event)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 166, 88, 422, 166, 60, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg5_muj_125_00"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    RETURN
EVT_END()

/**
 * Guess: damage event of Lord Crump: chooses the reaction by damage and whether he is guarding;
 * a heavy hit cancels his guard.
 */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 512, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CheckDamageCode, BTL_UNIT_SELF, 2048, LW(0))
            IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_US
                CALL(btlevtcmd_GetDamageCode, BTL_UNIT_SELF, LW(0))
                SWITCH(LW(0))
                    CASE_EQUAL(24)
                    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 29)
                    CASE_EQUAL(25)
                    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 29)
                    CASE_DEFAULT
                    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_1"))
                END_SWITCH
#else
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_1"))
#endif
                CALL(btlevtcmd_WaitAttackEnd)
                WAIT_FRAMES(120)
                CALL(check_exist_group, LW(0))
                IF_INT_NOT_EQUAL(LW(0), -1)
                    CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_ESCAPE1"), LW(13))
                    CALL(zakogun_escape3)
                    CALL(evt_snd_sfxoff, LW(13))
                    CALL(btlevtcmd_KillUnit, LW(0), 0)
                END_IF
            END_IF
        END_IF
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, BTL_UNIT_SELF, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 15)
            CALL(btlevtcmd_WaitAttackEnd)
            WAIT_FRAMES(90)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
            CALL(check_exist_group, LW(0))
            IF_INT_NOT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetUnitWork, LW(0), 1, LW(1))
                IF_INT_NOT_EQUAL(LW(1), 0)
                    WAIT_FRAMES(90)
                    GOTO(10)
                END_IF
            ELSE
                GOTO(10)
            END_IF
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(16)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(16)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(60)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
            CALL(check_exist_group, LW(0))
            IF_INT_NOT_EQUAL(LW(0), -1)
                CALL(zakogun_escape1)
                CALL(btlevtcmd_KillUnit, LW(0), 0)
            END_IF
            WAIT_FRAMES(20)
            LABEL(10)
            WAIT_FRAMES(20)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_btl_camera_set_prilimit, 1)
            CALL(evt_btl_camera_set_mode, 1, 3)
            CALL(evt_btl_camera_set_moveto, 1, 166, 88, 422, 166, 60, 0, 20, 11)
            WAIT_FRAMES(20)
            CALL(evt_msg_print, 2, STRING("stg5_muj_125_01"), 0, BTL_UNIT_SELF)
            CALL(evt_btl_camera_set_prilimit, 0)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            WAIT_MS(500)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(16)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(16)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
            WAIT_FRAMES(60)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_msg_print, 2, STRING("stg5_muj_125_02"), 0, BTL_UNIT_SELF)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            WAIT_MS(500)
            CALL(zakogun_ext_init2)
            CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_group2), 0)
            CALL(btlevtcmd_SetPos, LW(0), 0, 80, 0)
            CALL(btlevtcmd_SetHomePos, LW(0), 0, 80, 0)
            CALL(down_ceil)
            WAIT_FRAMES(60)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
            CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 1)
        END_IF
        GOTO(99)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/** Guess: death event of Lord Crump: he is defeated, his horde runs away and the battle ends. */
static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence))
        CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    END_IF
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_WaitAttackEnd)
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(btlevtcmd_GetUnitWork, LW(0), 1, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                WAIT_FRAMES(180)
            END_IF
        END_IF
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(zakogun_escape1)
            CALL(btlevtcmd_KillUnit, LW(0), 0)
        END_IF
        CASE_END
        CASE_EQUAL(1)
        CALL(btlevtcmd_WaitAttackEnd)
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(btlevtcmd_GetUnitWork, LW(0), 2, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                WAIT_FRAMES(180)
            END_IF
        END_IF
        CALL(check_exist_group, LW(0))
        IF_INT_NOT_EQUAL(LW(0), -1)
            CALL(up_ceil)
            CALL(zakogun_escape2)
            CALL(btlevtcmd_KillUnit, LW(0), 0)
        END_IF
        CASE_END
    END_SWITCH
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, 300, LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_moveto, 0, 220, 87, 419, 220, 60, 0, 60, 11)
    WAIT_FRAMES(60)
#if VERSION >= VERSION_JP
    CALL(evt_batstage_set_aud_dark, 0, 1, 0)
#endif
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 250, 30, 104, 4, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 220, 30, 103, 5, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(25)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 280, 30, 102, 6, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(15)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 235, 60, 101, 7, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, 265, 60, 100, 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(5)
    CALL(btlevtcmd_GetMaxHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SetHp, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_OnOffStatus, BTL_UNIT_SELF, 27, 0, 0, 0)
    WAIT_FRAMES(95)
#if VERSION >= VERSION_JP
    CALL(evt_batstage_return_aud_dark_base, 1, 0)
#endif
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 80)
    SUBTRACT(LW(2), 20)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_group3), 0)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, -1)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_MOVE2"), 0)
    CALL(zakogun_ext_init3)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, 2)
    CALL(btlevtcmd_ChangeDataTable, BTL_UNIT_SELF, PTR(data_table2))
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 166, 88, 422, 166, 60, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg5_muj_125_03"), 0, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Guess: phase event of Lord Crump: at the start of each turn decides whether he calls his horde,
 * guards or charges.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_get_turn, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_EQUAL(LW(0), 2)
        CALL_CHILD(call_event)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

/**
 * Lord Crump calls his horde (call_event): if no horde unit is on the stage yet,
 * he plays the call-back sound and pose C_1 and brings in horde group 1, 2 or 3 according to unit work 0.
 */
EVT_BEGIN(call_event)
    CALL(check_exist_group, LW(15))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        IF_INT_EQUAL(LW(15), -1)
            GOTO(10)
        END_IF
        CASE_END
        CASE_EQUAL(1)
        IF_INT_EQUAL(LW(15), -1)
            GOTO(10)
        END_IF
        CASE_END
        CASE_EQUAL(2)
        IF_INT_EQUAL(LW(15), -1)
            GOTO(10)
        END_IF
        CASE_END
    END_SWITCH
    SET_VALUE(LW(0), 0)
    GOTO(99)
    LABEL(10)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_BACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_1"))
        WAIT_FRAMES(16)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_BACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_1"))
        CASE_END
        CASE_EQUAL(1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
        WAIT_FRAMES(16)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
        WAIT_FRAMES(16)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_ON1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_2"))
        CASE_END
        CASE_EQUAL(2)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_BACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_1"))
        WAIT_FRAMES(16)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_CALL_BACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("C_1"))
        CASE_END
    END_SWITCH
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(100)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY_DEFAULT)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(15), -1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 80)
            SUBTRACT(LW(2), 20)
            CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_group1), 0)
            CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
            CALL(zakogun_ext_init1)
            WAIT_FRAMES(120)
            CASE_END
            CASE_EQUAL(1)
            CALL(zakogun_ext_init2)
            CALL(btlevtcmd_SpawnUnit, LW(0), PTR(&entry_group2), 0)
            CALL(btlevtcmd_SetPos, LW(0), 0, 80, 0)
            CALL(btlevtcmd_SetHomePos, LW(0), 0, 80, 0)
            CALL(down_ceil)
            WAIT_FRAMES(60)
            CASE_END
            CASE_EQUAL(2)
            CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 80)
            SUBTRACT(LW(2), 20)
            CALL(btlevtcmd_SpawnUnit, LW(3), PTR(&entry_group3), 0)
            CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon, STRING("SFX_BOSS_TEAM_3RD_MOVE2"), 0)
            CALL(zakogun_ext_init3)
            WAIT_FRAMES(120)
            CASE_END
        END_SWITCH
    END_IF
    SET_VALUE(LW(0), 1)
    LABEL(99)
    RETURN
EVT_END()

/**
 * Guess: attack event of Lord Crump: chooses between calling the horde (call_event), guarding,
 * charging and his normal attack.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            LABEL(10)
            SET_VALUE(LW(0), 75)
            ADD(LW(0), 0)
            ADD(LW(0), 30)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 75)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(&weapon_kanbu3_attack))
                CALL_CHILD(normal_attack_event)
                GOTO(99)
            END_IF
            ADD(LW(0), 0)
            IF_INT_LESS(LW(1), LW(0))
                CALL_CHILD(guard_event)
                GOTO(99)
            END_IF
            CALL_CHILD(call_event)
            IF_INT_EQUAL(LW(0), 1)
                GOTO(99)
            ELSE
                GOTO(10)
            END_IF
        ELSE
            CALL(evt_sub_random, 99, LW(1))
            IF_INT_LESS(LW(1), 50)
                CALL_CHILD(guard_cancel_event)
            ELSE
                CALL_CHILD(no_event)
            END_IF
        END_IF
    ELSE
        SET_VALUE(LW(0), 50)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 50)
            SET_VALUE(LW(9), PTR(&weapon_kanbu3_attack))
            CALL_CHILD(normal_attack_event)
            GOTO(99)
        END_IF
        CALL_CHILD(charge_event)
        GOTO(99)
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Guess: lord Crump raises his guard: plays the guard pose and marks him as guarding. */
static EVT_BEGIN(guard_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
    WAIT_FRAMES(16)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
    CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence_guard))
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table_guard))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 1)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/** Guess: lord Crump lowers his guard again and returns to his normal pose. */
static EVT_BEGIN(guard_cancel_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 15, 0, FLOAT(1.0f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 15, -1)
    CALL(btlevtcmd_SetPartsDefenceTable, BTL_UNIT_SELF, 1, PTR(&defence))
    CALL(btlevtcmd_AnimeSetPoseTable, BTL_UNIT_SELF, 1, PTR(pose_table))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, 0)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/**
 * Lord Crump's idle event for turns without an action:
 * aims the battle camera at him and zooms in to 200, then returns the camera to its default mode.
 */
EVT_BEGIN(no_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_FRAMES(120)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

/** Guess: lord Crump charges up for his next attack. */
static EVT_BEGIN(charge_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_kanbu3_charge))
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_kanbu3_charge))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_1"))
    WAIT_FRAMES(16)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("G_2"))
    WAIT_FRAMES(120)
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(60)
        CALL(evt_btl_camera_set_mode, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_kanbu3_charge))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_kanbu3_charge), 256, LW(5))
    RETURN
EVT_END()

/** Guess: wait (idle) event of Lord Crump: sets the idle pose for his current stance. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static PoseTableEntry pose_table_guard[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "G_2"},
    {BTL_POSE_TALK, "T_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "G_2"},
    {39, "D_1"},
    {42, "R_2"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {BTL_POSE_TALK, "T_1"},
    {BTL_POSE_STAY_DEFAULT, "G_2"},
};

/** Guess: lord Crump's normal attack: he runs at one target and hits it for the weapon damage. */
static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_2"))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 60)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_JUMP1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1A"))
        WAIT_FRAMES(10)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1B"))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, FLOAT(2.0f), FLOAT(0.19921875f))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1)
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 0, LW(5))
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
        LABEL(90)
        GOTO(98)
        LABEL(91)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(9), 256, LW(5))
        GOTO(98)
        LABEL(98)
        CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(evt_btl_camera_shake_h, 0, 10, 0, 60, 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 10)
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 0, 0, FLOAT(0.19921875f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("A_1C"))
        WAIT_FRAMES(25)
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
            WAIT_FRAMES(7)
            CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BOSS_KANBU_HIP_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
        END_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("D_1"))
        WAIT_FRAMES(15)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 15, 0, FLOAT(1.0f))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_1"))
        WAIT_FRAMES(10)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("R_1"))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(7.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 0)
        RETURN
EVT_END()

/**
 * Script helper: writes the battle unit id of the horde (the unit of kind 0x64, 0x65 or 0x66) to args[0],
 * or -1 if none is on the stage.
 */
USER_FUNC(check_exist_group) {
    s32 i;
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && (unit->initialKind == 0x64 || unit->initialKind == 0x65 || unit->initialKind == 0x66)) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
/**
 * Script helper: writes the battle unit id of the unit of kind 0x77 to args[0],
 * or -1 if none exists (the name suggests a researcher unit).
 */
static USER_FUNC(check_exist_kenkyu) {
    s32 i;
    EvtWord* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = -1;

    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x77) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}
