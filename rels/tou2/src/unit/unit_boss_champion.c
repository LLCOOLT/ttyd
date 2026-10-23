#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_stage_object.h"
#include "system.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_icon.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_env.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"

EffectEntry* effFallEntry(s32 type, f32 x, f32 y, f32 z, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8);
BOOL effFallCheckHit(EffectEntry* effect);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckAttribute);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetDamageCode);
USER_FUNC(btlevtcmd_GetTotalDamage);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventCeilFall);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStayPose);
USER_FUNC(btlevtcmd_SetStayPoseType);
USER_FUNC(btlevtcmd_SetTalkPose);
USER_FUNC(btlevtcmd_SetTalkPoseType);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(check_ceil);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_btl_camera_set_prilimit);
USER_FUNC(evt_btl_camera_wait_move_end);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_battle_party);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(init_ceil);
USER_FUNC(eff_fall_hit_wait);
USER_FUNC(eff_fall_entry);
static USER_FUNC(down_ceil);
USER_FUNC(ceil_exist);

__declspec(section ".data") u64 fd_boss_champion_negone_one_374;
__declspec(section ".data") s32 fd_boss_champion_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_champion___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_champion___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_champion_one_negone_373;
__declspec(section ".data") s32 fd_boss_champion___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_champion_one_381[1];
__declspec(section ".data") u64 fd_boss_champion_negone_one_360;
__declspec(section ".data") s32 fd_boss_champion_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_champion___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_champion___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_champion_one_negone_359;
__declspec(section ".data") s32 fd_boss_champion___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_champion_one_364[1];
BattleUnitKind unit_boss_champion;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
PoseTableEntry pose_table_roof[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
s32 weapon_champion_drop_kick_attack[48];
s32 weapon_champion_screw_attack[48];
s32 weapon_champion_flying_chop_attack[48];
s32 weapon_champion_foot_stamp_attack[48];
s32 weapon_champion_healing[48];
s32 weapon_champion_roof_shake_attack[48];
s32 weapon_champion_roof_shake_last_attack[48];
s32 to_ceiling[103];
s32 to_floor[95];
static s32 init_event[52];
static s32 entry_event[354];
static s32 damage_event[75];
static __declspec(section ".data") s32 ceil_fall_ready_event[8];
static s32 dead_event[90];
static s32 phase_event[450];
static s32 attack_event[221];
s32 drop_kick_attack_event[299];
s32 screw_attack_event[295];
s32 flying_chop_attack_event[326];
s32 foot_stamp_attack_event[467];
s32 healing_event[209];
s32 roof_shake_attack_event[386];
static __declspec(section ".data") s32 wait_event[6];

USER_FUNC(ceil_exist) {
    s32* args = event->args;

    if (_battleWorkPointer->field_180DC & 0x20) {
        evtSetValue(event, args[0], 0);
    } else {
        evtSetValue(event, args[0], 1);
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_boss_champion_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_champion_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_champion___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_champion___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_champion_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_champion___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_champion_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_champion_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_champion_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_champion___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_champion___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_champion_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_champion___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_champion_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_champion = {
    64,
    "btl_un_champion",
    40,
    0,
    1,
    1,
    34,
    0,
    0,
    100,
    0,
    50,
#ifdef VERSION_G8ME01
    7,
#else
    8,
#endif
    50,
    64,
    3,
    64,
    0.0f,
    32.0f,
    0.0f,
    0,
    0,
    8.0f,
    36.0f,
    0.0f,
    25.0f,
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
    10.0f,
    48.0f,
    10.0f,
    0.0f,
    32.0f,
    0.0f,
    50.0f,
    64.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_BLED_DAMAGED1",
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

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {60, 50, 60, 100, 60, 100, 100, 40, 0, 85, 100, 85, 100, 90, 60, 0, 0, 100, 70, 100, 100, 0};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "K_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {39, "D_1"},
    {50, "Z_6"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

PoseTableEntry pose_table_roof[] = {
    {1, "N_2"},
    {2, "Y_2"},
    {9, "Y_2"},
    {5, "K_2"},
    {4, "X_2"},
    {3, "K_2"},
    {28, "S_8"},
    {29, "Q_2"},
    {30, "Q_2"},
    {31, "D_2"},
    {39, "D_2"},
    {50, "Z_8"},
    {42, "W_2"},
    {40, "W_2"},
    {56, "X_2"},
    {57, "X_2"},
    {65, "T_8"},
    {69, "S_8"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_champion", "c_bred_h", 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 55.0f, 0.0f, 35, 70, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

USER_FUNC(init_ceil) {
    u8* ceil = &_battleWorkPointer->field_180DC;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    wire->mPosition = (Vec){0.0f, 250.0f, 0.0f};
    body->mPosition = wire->mPosition;
    *ceil |= 0x20;
    return EVT_RETURN_DONE;
}

s32 weapon_champion_drop_kick_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_screw_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536875008, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_flying_chop_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_foot_stamp_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 4231, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_healing[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 135, 0, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_roof_shake_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_champion_roof_shake_last_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, 0,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
#endif
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 1770242, 0, 131207, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1644900, 0, 0,
};

s32 to_ceiling[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A", 65546, 250, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1D", 131122, -29999999, 60, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_8", 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    -229995904, -229999796, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -250000000, -29999998,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_JUMP1", -250000000, 0, -250000000, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_GRASP_CAILING1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1,
    (s32)pose_table_roof, 196699, (s32)btlevtcmd_SetTalkPoseType, -2, 65, 196699, (s32)btlevtcmd_SetStayPoseType, -2,
    43, 196699, (s32)btlevtcmd_OnAttribute, -2, 2, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    1, 6291456, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 16, 48, 10,
    327771, (s32)btlevtcmd_SetCutBaseOffset, -2, -2, -38, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset,
    -2, 1, 0, -44, 0, 2, 1,
};

s32 to_floor[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 327771, (s32)btlevtcmd_JumpSetting, -2,
    0, -229995904, -229999796, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -250000000,
    -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 20,
    -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0, -29999998, 393307, (s32)evt_btl_camera_shake_h,
    0, 3, 0, 50, 13, 65546, 250, 262235,
    (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 196699, (s32)btlevtcmd_SetTalkPoseType, -2, 65,
    196699, (s32)btlevtcmd_SetStayPoseType, -2, 43, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    43, 196699, (s32)btlevtcmd_OffAttribute, -2, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    1, 6291456, 327771, (s32)btlevtcmd_SetKissHitOffset, -2, 10, 48, 10,
    327771, (s32)btlevtcmd_SetCutBaseOffset, -2, 0, 32, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset,
    -2, 1, 0, 0, 0, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(init_ceil)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_BLED_MOVE1L"), STRING("SFX_BOSS_BLED_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_BLED_MOVE1L"), STRING("SFX_BOSS_BLED_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    IF_INT_LESS(GSW(0), 158)
        IF_INT_EQUAL(GSWF(2513), 0)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_6"))
            CALL(btlevtcmd_SetTalkPose, -2, STRING("T_6"))
            CALL(btlevtcmd_SetStayPose, -2, STRING("S_6"))
            WAIT_FRAMES(120)
            SET_VALUE(GSWF(2513), 1)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, -102, 83, 334, -102, 59, 0, 30, 11)
            WAIT_FRAMES(37)
            CALL(evt_msg_print_battle_party, STRING("stg3_tou_432"))
            WAIT_MS(300)
            CALL(evt_btl_camera_set_moveto, 0, 81, 83, 334, 81, 59, 0, 30, 11)
            WAIT_FRAMES(37)
            CALL(evt_msg_print, 2, STRING("stg3_tou_433"), 0, -2)
            WAIT_MS(200)
            CALL(evt_btl_camera_set_mode, 0, 0)
            WAIT_MS(200)
            CALL(evt_msg_print_battle_party, STRING("stg3_tou_434"))
            WAIT_MS(200)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, 81, 83, 334, 81, 59, 0, 1, 11)
            WAIT_FRAMES(7)
            CALL(evt_msg_print, 2, STRING("stg3_tou_435"), 0, -2)
            WAIT_MS(200)
            CALL(evt_btl_camera_set_moveto, 0, -111, 67, 275, -111, 49, 0, 1, 11)
            WAIT_FRAMES(7)
            CALL(evt_msg_print_battle_party, STRING("stg3_tou_435_01"))
            WAIT_MS(200)
            CALL(evt_btl_camera_set_moveto, 0, 74, 67, 275, 74, 49, 0, 30, 11)
            WAIT_FRAMES(37)
            CALL(evt_msg_print, 2, STRING("stg3_tou_435_02"), 0, -2)
            WAIT_MS(200)
            ELSE
            WAIT_FRAMES(60)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
            WAIT_FRAMES(60)
            CALL(evt_btl_camera_set_mode, 0, 3)
            CALL(evt_btl_camera_set_moveto, 0, -102, 83, 334, -102, 59, 0, 30, 11)
            WAIT_FRAMES(37)
            CALL(evt_msg_print_battle_party, STRING("stg3_tou_436"))
            WAIT_MS(200)
            CALL(evt_btl_camera_set_moveto, 0, 81, 83, 334, 81, 59, 0, 30, 11)
            WAIT_FRAMES(37)
            CALL(evt_msg_print, 2, STRING("stg3_tou_436_01"), 0, -2)
            WAIT_MS(200)
        END_IF
        ELSE
        IF_INT_LESS(GSW(0), 172)
            ELSE
            SET_VALUE(GSWF(2514), 0)
            DEBUG_PUT_MSG(STRING("チャンピオン　再挑戦"))
            DEBUG_PUT_REG(GSWF(2515))
            IF_INT_EQUAL(GSWF(2503), 0)
                WAIT_FRAMES(60)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
                WAIT_FRAMES(60)
                CALL(evt_btl_camera_set_mode, 0, 3)
                CALL(evt_btl_camera_set_moveto, 0, -102, 83, 334, -102, 59, 0, 30, 11)
                WAIT_FRAMES(37)
                CALL(evt_msg_print_battle_party, STRING("stg3_tou_re_116"))
                WAIT_MS(200)
                CALL(evt_btl_camera_set_moveto, 0, 81, 83, 334, 81, 59, 0, 30, 11)
                WAIT_FRAMES(37)
                CALL(evt_msg_print, 2, STRING("stg3_tou_re_123"), 0, -2)
                WAIT_MS(200)
                ELSE
                WAIT_FRAMES(60)
                CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
                WAIT_FRAMES(60)
                CALL(evt_btl_camera_set_mode, 0, 3)
                CALL(evt_btl_camera_set_moveto, 0, -102, 83, 334, -102, 59, 0, 30, 11)
                WAIT_FRAMES(37)
                CALL(evt_msg_print_battle_party, STRING("stg3_tou_re_124"))
                WAIT_MS(200)
                CALL(evt_btl_camera_set_moveto, 0, 81, 83, 334, 81, 59, 0, 30, 11)
                WAIT_FRAMES(37)
                CALL(evt_msg_print, 2, STRING("stg3_tou_re_131"), 0, -2)
                WAIT_MS(200)
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_GetBodyId, -4, LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, -4, LW(0))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(200)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(btlevtcmd_SetTalkPoseType, -2, 65)
    CALL(btlevtcmd_SetStayPoseType, -2, 43)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1"))
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(2), 0)
        CALL(btlevtcmd_GetDamageCode, -2, LW(0))
        SWITCH(LW(0))
            CASE_OR_EQUAL(23)
            CASE_OR_EQUAL(24)
            CASE_OR_EQUAL(25)
            CASE_OR_EQUAL(26)
            CASE_OR_EQUAL(27)
            CALL(btlevtcmd_GetTotalDamage, -2, LW(1))
            IF_INT_GREATER_OR_EQUAL(LW(1), 1)
                SET_VALUE(LW(2), 1)
            END_IF
            CASE_END
        END_SWITCH
        CALL(btlevtcmd_CheckStatus, -2, 11, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(2), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_StopWaitEvent, -2)
            CALL_CHILD(PTR(to_floor))
            CALL(btlevtcmd_StartWaitEvent, -2)
        END_IF
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(ceil_fall_ready_event)
    CALL(btlevtcmd_SetEventCeilFall, -2, 0)
    CALL_CHILD(PTR(to_floor))
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(to_floor))
    END_IF
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("D_3"))
    WAIT_MS(200)
    CALL(evt_snd_sfxon, STRING("SFX_BOSS_BLED_DIE1"), 0)
    WAIT_MS(100)
    IF_INT_LESS(GSW(0), 158)
        CALL(btlevtcmd_WaitAttackEnd)
        CALL(evt_btl_camera_set_prilimit, 1)
        CALL(evt_btl_camera_wait_move_end)
        CALL(btlevtcmd_StatusWindowOnOff, 0)
        CALL(evt_btl_camera_set_mode, 1, 3)
        CALL(evt_btl_camera_set_moveto, 1, 81, 83, 334, 81, 59, 0, 30, 11)
        WAIT_FRAMES(37)
        CALL(btlevtcmd_SetTalkPose, -2, STRING("T_10"))
        CALL(btlevtcmd_SetStayPose, -2, STRING("S_10"))
        CALL(evt_msg_print, 2, STRING("stg3_tou_436_06"), 0, -2)
        WAIT_MS(300)
        CALL(evt_btl_camera_set_mode, 1, 0)
        WAIT_MS(300)
        CALL(evt_btl_camera_set_prilimit, 0)
        CALL(btlevtcmd_StatusWindowOnOff, 1)
    END_IF
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static s32 phase_event[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108867, 131096, -30000000, 0, 65540,
    99, 33, 196699, (s32)btlevtcmd_CheckActStatus, -2, -30000000, 131096, -30000000,
    0, 65540, 99, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0,
    -30000000, 65570, -30000000, 65572, 0, 196699, (s32)btlevtcmd_GetMaxHp, -2,
    -30000000, 65651, -30000000, 131127, -30000000, 67, 65651, -30000000,
    131128, -30000000, 100, 65651, -30000000, 196699, (s32)btlevtcmd_GetHp, -2,
    -29999999, 65651, -29999999, 131100, -29999999, -30000000, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 1, 131096, -129997486, 0, 131122, -129997486,
    1, 131163, (s32)btlevtcmd_StopWaitEvent, -2, 131098, -170000000, 158, 131163,
    (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto,
    0, 73, 78, 322, 73, 57, 0, 30,
    11, 65545, 37, 327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_436_02", 0,
    -2, 32, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 655451, (s32)evt_btl_camera_set_moveto,
    0, 73, 78, 322, 73, 57, 0, 30,
    11, 65545, 37, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_2", 65546, 200, 655451, (s32)evt_btl_camera_set_moveto, 0, 73, 82,
    379, 73, 57, 0, 30, 11, 196699, (s32)evt_env_blur_on,
    0, 500, 65545, 37, 131098, -170000000, 158, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"T_2", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"S_2", 327771,
    (s32)evt_msg_print, 2, (s32)"stg3_tou_436_03", 0, -2, 196699, (s32)btlevtcmd_SetTalkPoseType, -2,
    65, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 43, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    33, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 33, 33, 65572,
    2, 196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 65651, -30000000, 131127,
    -30000000, 34, 65651, -30000000, 131128, -30000000, 100, 65651,
    -30000000, 196699, (s32)btlevtcmd_GetHp, -2, -29999999, 65651, -29999999, 131100,
    -29999999, -30000000, 131122, -30000000, 0, 262235, (s32)btlevtcmd_CheckStatus, -2,
    11, -29999999, 131096, -29999999, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    0, 3, 131098, -170000000, 158, 131096, -129997485, 0,
    131122, -129997485, 1, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)evt_btl_camera_set_mode,
    0, 3, 655451, (s32)evt_btl_camera_set_moveto, 0, 73, 78, 322,
    73, 57, 0, 30, 11, 65545, 37, 327771,
    (s32)evt_msg_print, 2, (s32)"stg3_tou_436_04", 0, -2, 65546, 300, 131163,
    (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 33, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3C", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_JUMP1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 25, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0, 3,
    0, 50, 13, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B",
    107, 65546, 600, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 43,
    109, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_BLED_MOVE_CAILING1", -29999985, 65627, (s32)down_ceil, 131163,
    (s32)evt_snd_sfxoff, -29999985, 196699, (s32)btlevtcmd_SetEventCeilFall, -2, (s32)ceil_fall_ready_event, 33, 33,
    65572, 4, 196699, (s32)btlevtcmd_GetMaxHp, -2, -30000000, 65651, -30000000,
    131127, -30000000, 25, 65651, -30000000, 131128, -30000000, 100,
    65651, -30000000, 196699, (s32)btlevtcmd_GetHp, -2, -29999999, 65651, -29999999,
    131100, -29999999, -30000000, 131098, -170000000, 158, 131096, -129997484,
    0, 131122, -129997484, 1, 131163, (s32)btlevtcmd_StopWaitEvent, -2, 131163,
    (s32)btlevtcmd_StatusWindowOnOff, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 262235, (s32)btlevtcmd_CheckAttribute,
    -2, 2, -30000000, 131096, -30000000, 0, 655451, (s32)evt_btl_camera_set_moveto,
    0, 73, 78, 322, 73, 57, 0, 30,
    11, 32, 655451, (s32)evt_btl_camera_set_moveto, 0, 73, 138, 322,
    73, 117, 0, 30, 11, 33, 65545, 37,
    327771, (s32)evt_msg_print, 2, (s32)"stg3_tou_436_05", 0, -2, 65546, 300,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 33, 33, 33, 49, 65539, 99,
    2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(btlevtcmd_DrawLots, LW(0), 2, 10, 15)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_champion_drop_kick_attack))
            CALL_CHILD(PTR(drop_kick_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_champion_screw_attack))
            CALL_CHILD(PTR(screw_attack_event))
        END_SWITCH
        CASE_EQUAL(1)
        CALL(btlevtcmd_SetUnitWork, -2, 0, 2)
        SET_VALUE(LW(9), PTR(weapon_champion_flying_chop_attack))
        CALL_CHILD(PTR(flying_chop_attack_event))
        CASE_EQUAL(2)
        CALL(btlevtcmd_DrawLots, LW(0), 3, 10, 15, 20)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            SET_VALUE(LW(9), PTR(weapon_champion_drop_kick_attack))
            CALL_CHILD(PTR(drop_kick_attack_event))
            CASE_EQUAL(1)
            SET_VALUE(LW(9), PTR(weapon_champion_screw_attack))
            CALL_CHILD(PTR(screw_attack_event))
            CASE_EQUAL(2)
            SET_VALUE(LW(9), PTR(weapon_champion_flying_chop_attack))
            CALL_CHILD(PTR(flying_chop_attack_event))
        END_SWITCH
        CASE_EQUAL(3)
        CALL(btlevtcmd_SetUnitWork, -2, 0, 4)
        CALL_CHILD(PTR(to_ceiling))
        SET_VALUE(LW(9), PTR(weapon_champion_roof_shake_attack))
        CALL_CHILD(PTR(roof_shake_attack_event))
        CASE_EQUAL(4)
        CALL(btlevtcmd_CheckAttribute, -2, 2, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LW(2), 30)
            CALL(btlevtcmd_CheckStatus, -2, 11, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                SET_VALUE(LW(2), 0)
            END_IF
            CALL(check_ceil)
            IF_INT_NOT_EQUAL(LW(1), 0)
                SET_VALUE(LW(2), 0)
            END_IF
            CALL(btlevtcmd_DrawLots, LW(0), 4, 10, 15, 20, LW(2))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                SET_VALUE(LW(9), PTR(weapon_champion_drop_kick_attack))
                CALL_CHILD(PTR(drop_kick_attack_event))
                CASE_EQUAL(1)
                SET_VALUE(LW(9), PTR(weapon_champion_screw_attack))
                CALL_CHILD(PTR(screw_attack_event))
                CASE_EQUAL(2)
                SET_VALUE(LW(9), PTR(weapon_champion_flying_chop_attack))
                CALL_CHILD(PTR(flying_chop_attack_event))
                CASE_EQUAL(3)
                CALL_CHILD(PTR(to_ceiling))
                SET_VALUE(LW(9), PTR(weapon_champion_roof_shake_attack))
                CALL_CHILD(PTR(roof_shake_attack_event))
            END_SWITCH
            ELSE
            CALL(btlevtcmd_DrawLots, LW(0), 3, 10, 20, 20)
            SWITCH(LW(0))
                CASE_EQUAL(0)
                SET_VALUE(LW(9), PTR(weapon_champion_foot_stamp_attack))
                CALL_CHILD(PTR(foot_stamp_attack_event))
                CASE_EQUAL(1)
                SET_VALUE(LW(9), PTR(weapon_champion_healing))
                CALL_CHILD(PTR(healing_event))
                CASE_EQUAL(2)
                SET_VALUE(LW(9), PTR(weapon_champion_roof_shake_attack))
                CALL_CHILD(PTR(roof_shake_attack_event))
            END_SWITCH
        END_IF
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 drop_kick_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"R_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    131125, -30000000, 150, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2A", 327771, (s32)btlevtcmd_JumpSetting, -2,
    0, -229995904, -229999990, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 131125, -30000000, 30, 131125, -29999998, 5, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_DROP_KICK1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 65546,
    300, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 393307, (s32)evt_btl_camera_shake_h, 0, 3, 0, 50, 13,
    65546, 60, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 98, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_CHOP_ROUND1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000,
    100, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229996928, -229999744, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"J_1A", 65546, 250, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1C", 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    -229995904, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0,
    -250000000, 2, 1,
};

s32 screw_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A",
    65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1F", 327771,
    (s32)btlevtcmd_JumpSetting, -2, 0, -229994880, -229999591, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 131122, -29999990, 0, 65539, 10, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_CHOP_ROUND1", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579, 4,
    65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 65540, 90, 65572, 1, 65540, 91,
    46, 42, 65540, 98, 46, 49, 65539, 90,
    131163, (s32)btlevtcmd_JumpContinue, -2, 65546, 150, 65540, 98, 65539,
    91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 0, -229998464, -229999284, 131097, -29999997, -1,
    131125, -29999990, 1, 65540, 10, 33, 65539, 98,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_CHOP_ROUND1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, 100, 327771, (s32)btlevtcmd_JumpSetting, -2,
    0, -229996928, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0,
    -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A", 65546,
    250, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"J_1C", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229995904, -229999744, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000, 2, 1,
};

s32 flying_chop_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"J_1A", 65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, -229995904, -229999847, 131125, -30000000, 82, 131125,
    -29999999, 80, 131125, -29999998, 140, 196699, (s32)btlevtcmd_GetStatusMg, -2,
    -29999995, 131132, -29999995, 30, 131126, -30000000, -29999995, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_CHOP_ROUND1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_CHOP_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_1A", 65546, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1B", 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229989760, -229999990, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 131125, -30000000, 30,
    131125, -29999999, 5, 131125, -29999998, 5, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_CHOP_FLY1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1C", 131163, (s32)btlevtcmd_JumpContinue,
    -2, 65546, 150, 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 393307, (s32)evt_btl_camera_shake_h, 0, 3, 0,
    50, 13, 65546, 60, 65539, 98, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"J_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -30000000, 100, 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    -229996928, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998,
    0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1A", 65546, 250,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"J_1C", 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_JumpSetting, -2, 0, -229995904, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000, 2, 1,
};

s32 foot_stamp_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"W_2", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"B_1", 65546,
    700, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A", 327771, (s32)btlevtcmd_GetPos,
    -29999997, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999232,
    131125, -29999999, 20, 131125, -29999998, 5, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_BLED_FUMI_FALL1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 10, -1, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0,
    -29999998, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 196699, (s32)btlevtcmd_SetTalkPoseType,
    -2, 65, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 43, 196699, (s32)btlevtcmd_OffAttribute,
    -2, 2, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 6291456, 327771,
    (s32)btlevtcmd_SetKissHitOffset, -2, 10, 48, 10, 327771, (s32)btlevtcmd_SetCutBaseOffset, -2,
    0, 32, 0, 393307, (s32)btlevtcmd_SetHitCursorOffset, -2, 1, 0,
    0, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_FUMI_STEPON1", -250000000, 0,
    -250000000, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 0,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65546, 300, 65540,
    98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 0, -29999995, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65546, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"A_3C", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 25, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_BLED_FUMI_STEPON1", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 0, -29999995,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3B", 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3C", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    35, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_FUMI_STEPON1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_3B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 14, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    393307, (s32)evt_btl_camera_shake_h, 0, 3, 0, 50, 13, 65546,
    300, 65539, 98, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1B",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -30000000,
    100, 327771, (s32)btlevtcmd_JumpSetting, -2, 0, -229996928, -229999744, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 0, -1, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"J_1A", 65546, 250, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"J_1C", 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -2, 0,
    -229995904, -229999744, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_LANDING1", -250000000, 0,
    -250000000, 2, 1,
};

s32 healing_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_4", 65545, 16, 65541, 3, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_BLED_SHAKE_CAILING1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0, 2,
    0, 10, 13, 65545, 18, 6, 393307, (s32)evt_btl_camera_shake_h,
    0, 2, 0, 10, 13, 107, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999995, -29999994, -29999993, 131125, -29999995, -30, 131125,
    -29999994, 80, 131125, -29999993, 40, 393307, (s32)btlevtcmd_BtlIconEntryItemId, 148,
    -29999995, -29999994, -29999993, -29999992, 131122, -30000000, -29999994, 131125,
    -30000000, -62, 327771, (s32)evt_sub_intpl_msec_init, 1, -29999994, -30000000, 500,
    65541, 0, 196699, (s32)evt_sub_intpl_msec_get_value_para, -30000000, -29999999, 327771, (s32)btlevtcmd_BtlIconSetPosition,
    -29999992, -29999995, -30000000, -29999993, 131096, -29999999, 0, 7,
    33, 65545, 1, 6, 131163, (s32)btlevtcmd_BtlIconDelete, -29999992, 109,
    65546, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_8", 65546,
    100, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_EAT1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"B_2", 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"E_2", 65546, 700, 262235, (s32)btlevtcmd_RecoverHp,
    -29999997, -29999996, 5, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999,
    -29999998, 131125, -29999999, 30, 131125, -29999998, 10, 983131,
    (s32)evt_eff, (s32)"", (s32)"recovery", 0, -30000000, -29999999, -29999998, 5,
    0, 0, 0, 0, 0, 0, 0, 65545,
    40, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2,
    1,
};

static USER_FUNC(down_ceil) {
    u8* ceil = &_battleWorkPointer->field_180DC;
    BattleStageObject* body = BattleSearchObjectPtr("if_body");
    BattleStageObject* wire = BattleSearchObjectPtr("if_wire");

    if (isFirstCall) {
        event->userdata[0] = 120;
        *ceil &= ~0x20;
    }
    body->mPosition.y = wire->mPosition.y = intplGetValue(4, 120 - event->userdata[0], 120, 250.0f, 130.0f);
    event->userdata[0]--;
    if (event->userdata[0] < 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(check_ceil) {
    event->lwData[1] = _battleWorkPointer->field_180DC & 0x20;
    return EVT_RETURN_DONE;
}

USER_FUNC(eff_fall_entry) {
    s32* args = event->args;
    s32 var = args[0];
    s32 type = evtGetValue(event, args[1]);
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    f32 a = evtGetFloat(event, args[5]);
    f32 b = evtGetFloat(event, args[6]);
    f32 c = evtGetFloat(event, args[7]);
    s32 d = evtGetValue(event, args[8]);
    s32 e = evtGetValue(event, args[9]);
    EffectEntry* eff = effFallEntry(type, x, y, z, a, b, c, d, e);

    evtSetValue(event, var, (s32)eff);
    return EVT_RETURN_DONE;
}

USER_FUNC(eff_fall_hit_wait) {
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, event->args[0]);

    if (eff != NULL && !effFallCheckHit(eff)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

s32 roof_shake_attack_event[] = {
    131122, -29999985, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 0,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 1, 0, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 2, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 3, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 4,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 5, 0, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 1, 6, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 7, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 8,
    0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 9, 0, 131122,
    -29999987, 0, 65541, 10, 131122, -30000000, 0, 131125,
    -30000000, -29999987, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, -30000000, 0,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_4", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_BLED_SHAKE_CAILING1", -250000000,
    0, -250000000, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0, 10,
    13, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999998, 10, 131122, -29999992, -29999999, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 131097, -29999995, 1, 131122, -29999992,
    0, 33, 196699, (s32)evt_sub_random, 2, -29999994, 65570, -29999994,
    65572, 0, 720987, (s32)eff_fall_entry, -29999986, 4, -30000000, -29999999,
    -29999998, 20, -29999992, 0, 1, 60, 65572, 1,
    720987, (s32)eff_fall_entry, -29999986, 5, -30000000, -29999999, -29999998, 20,
    -29999992, 0, 1, 60, 65572, 2, 720987, (s32)eff_fall_entry,
    -29999986, 8, -30000000, -29999999, -29999998, 20, -29999992, 0,
    1, 60, 49, 65644, -29999985, 65570, -29999995, 65572,
    1, 131163, (s32)eff_fall_hit_wait, -29999986, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 0, -29999995,
    65572, 3, 131163, (s32)eff_fall_hit_wait, -29999986, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 65572, 6, 65545, 10, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65572, 2, 131163, (s32)eff_fall_hit_wait, -29999986, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 42, 131163, (s32)eff_fall_hit_wait, -29999986, 49, 109,
    131122, -30000000, 0, 131125, -30000000, -29999987, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, -30000000, -29999985, 65545, 4, 65539, 90,
    131125, -29999987, 1, 6, 65545, 10, 65539, 92,
    65545, 1, 131122, -29999987, 0, 65539, 93, 131122,
    -30000000, 0, 131125, -30000000, -29999987, 327771, (s32)btlevtcmd_GetPartsWork, -2,
    1, -30000000, -29999985, 131097, -29999985, 0, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, -30000000, 0, 65540,
    92, 33, 131125, -29999987, 1, 131098, -29999987, 10,
    65540, 93, 33, 196699, (s32)btlevtcmd_GetGuardKouraId, -3, -30000000, 131097,
    -30000000, -1, 458843, (s32)btlevtcmd_CheckDamage, -2, -30000000, 1, (s32)weapon_champion_roof_shake_last_attack,
    256, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -3, 1,
    (s32)weapon_champion_roof_shake_last_attack, 256, -29999995, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -4,
    1, (s32)weapon_champion_roof_shake_last_attack, 256, -29999995, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

