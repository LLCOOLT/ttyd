#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "driver/animdrv.h"
#include "mario/mario_pouch.h"
#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"

static USER_FUNC(_mario_makkuro_set);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_ClearAllStatus);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_ReplaceParts);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetRegistStatus);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_get_turn);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_btl_camera_set_prilimit);
USER_FUNC(evt_btl_camera_wait_move_end);
USER_FUNC(evt_msg_print);
static USER_FUNC(vivian_comeback);
static USER_FUNC(eff_scanning);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnimeSetMotionSpeed[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetHp[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxon[];
extern s32 evt_sub_intpl_get_value_para[];
extern s32 evt_sub_intpl_init[];
extern s32 evt_sub_intpl_msec_get_value_para[];
extern s32 evt_sub_intpl_msec_init[];
extern s32 evt_sub_random[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_rampell_negone_one_374;
__declspec(section ".data") s32 fd_boss_rampell_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_rampell___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_rampell___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_rampell_one_negone_373;
__declspec(section ".data") s32 fd_boss_rampell___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_rampell_one_381[1];
__declspec(section ".data") u64 fd_boss_rampell_negone_one_360;
__declspec(section ".data") s32 fd_boss_rampell_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_rampell___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_rampell___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_rampell_one_negone_359;
__declspec(section ".data") s32 fd_boss_rampell___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_rampell_one_364[1];
BattleUnitKind unit_boss_rampell;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
static s32 weapon_rampell_attack[48];
s32 rampell_zoom[19];
s32 to_faker_mario[339];
static s32 init_event[61];
static __declspec(section ".data") s32 damage_event[10];
static s32 dead_event[74];
static s32 phase_event[106];
static s32 attack_event[24];
static s32 ogg_attack_event[491];
static __declspec(section ".data") s32 wait_event[6];
static __declspec(section ".data") s32 defence_fmario[2];
static __declspec(section ".data") s32 defence_attr_fmario[2];
static __declspec(section ".data") s32 regist_fmario[6];
static PoseTableEntry pose_table_fmario_stay[15];
static __declspec(section ".data") s32 data_table_fmario[4];
static s32 parts_fmario[19];
static s32 weapon_masao_jump[48];
static s32 weapon_masao_hammer[48];
static s32 weapon_masao_kururin_jump[48];
static s32 weapon_masao_kaiten_hammer[48];
static s32 mario_zoom[19];
static s32 enemy_zoom[19];
static s32 fmario_zoom[19];
static s32 gparty_zoom[19];
static s32 init_event_fmario[73];
static s32 dead_event_fmario[93];
static __declspec(section ".data") s32 damage_event_fmario[10];
static s32 attack_event_fmario[58];
static s32 jump_attack_voice[36];
static s32 marioAttackEvent_NormalJump[344];
static s32 marioAttackEvent_KururinJump[469];
static s32 marioAttackEvent_NormalHammer[299];
static s32 marioAttackEvent_KaitenHammer[299];
static __declspec(section ".data") s32 wait_event_fmario[6];

void faker_mario_makkuro_set(BattleUnit* unit);

static USER_FUNC(_mario_makkuro_set) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, -2));

    if (unit != NULL) {
        faker_mario_makkuro_set(unit);
        animPoseSetMaterialFlagOn(BtlUnit_GetPartsPtr(unit, 1)->poseId, 0xB000000);
    }
    return EVT_RETURN_DONE;
}

#ifdef VERSION_G8ME01
// US only: restore the moves of the unit for this turn.
USER_FUNC(boss_rampell_sync_max_moves) {
    BattleUnit* unit;
    s32 id = evtGetValue(event, event->args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);

    if (unit != NULL) {
        unit->maxMovesThisTurn = unit->movesRemaining;
    }
    return EVT_RETURN_DONE;
}
#endif

static USER_FUNC(vivian_comeback) {
    pouchGetPtr()->partyData[6].flags &= ~2;
    return 1;
}

EffectEntry* effScanningEntry(s32 type, f32 x, f32 y, f32 z);

static USER_FUNC(eff_scanning) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = effScanningEntry(0, x, y, z);

    ((f32*)eff->userdata)[4] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_boss_rampell_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_rampell_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_rampell___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_rampell___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_rampell_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_rampell___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_rampell_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_rampell_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_rampell_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_rampell___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_rampell___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_rampell_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_rampell___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_rampell_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_rampell = {
    77,
    "btl_un_hatena",
    40,
    0,
    1,
    1,
    52,
    0,
    0,
    100,
    0,
    70,
    7,
    50,
    48,
    4,
    48,
    0.0f,
    22.0f,
    0.0f,
    0,
    -3,
    0.0f,
    40.0f,
    0.0f,
    25.0f,
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
    12.0f,
    32.0f,
    0.0f,
    7.0f,
    22.0f,
    0.0f,
    50.0f,
    48.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_RNPL_DAMAGED1",
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

static __declspec(section ".data") StatusVulnerability regist = {60, 60, 70, 100, 60, 100, 100, 50, 100, 80, 100, 80, 100, 90, 60, 0, 0, 100, 60, 100, 100, 0};

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
    {31, "S_1"},
    {39, "D_1"},
    {50, "A_2"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_hatena", "c_ranpel", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 40.0f, 0.0f, 30, 40, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static s32 weapon_rampell_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 69639, 6, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

EVT_BEGIN(rampell_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

s32 to_faker_mario[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 2, 65627, (s32)btlevtcmd_WaitAttackEnd, 131163,
    (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)rampell_zoom, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_08_02",
    0, -2, 65546, 200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_ARM_UP1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A",
    65546, 600, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_ARM_UP1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A", 65546, 600,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_ARM_UP1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3A", 65546, 200, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_RNPL_LAUGH1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_3B", 65546, 800, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_EYE_SHINE1",
    -250000000, 0, -250000000, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999994, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131124, -29999993, -230006144,
    131132, -29999993, -29999994, 131130, -30000000, -29999993, 131124, -29999993,
    -229966208, 131132, -29999993, -29999994, 131130, -29999999, -29999993, 983131,
    (s32)evt_eff, (s32)"", (s32)"toge_flush", 3, -30000000, -29999999, -29999998, 60,
    0, 0, 0, 0, 0, 0, 0, 131124,
    -29999993, -229992832, 131132, -29999993, -29999994, 131130, -30000000, -29999993,
    131124, -29999993, -230001024, 131132, -29999993, -29999994, 131130, -29999999,
    -29999993, 983131, (s32)evt_eff, (s32)"", (s32)"toge_flush", 3, -30000000, -29999999,
    -29999998, 60, 0, 0, 0, 0, 0, 0,
    0, 65546, 1000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_TRANSFORM4", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 7,
    -30000000, -29999999, -29999998, -229997952, 0, 0, 0, 0,
    0, 0, 0, 65546, 200, 327771, (s32)btlevtcmd_SetPos, -2,
    -1000, -1000, 0, 65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 655451, (s32)evt_btl_camera_set_moveto, 0, -110, 65, 332, -110,
    30, -340, 30, 11, 65545, 37, 327771, (s32)btlevtcmd_GetPos,
    -3, -30000000, -29999999, -29999998, 131125, -30000000, 3, 131125,
    -29999999, -5, 131125, -29999998, 5, 327771, (s32)eff_scanning, -3,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM2", -250000000,
    0, -250000000, 65546, 200, 393307, (s32)btlevtcmd_snd_se, -3, (s32)"SFX_BOSS_RNPL_TRANSFORM1",
    -250000000, 0, -250000000, 65546, 1300, 393307, (s32)btlevtcmd_snd_se, -3,
    (s32)"SFX_BOSS_RNPL_TRANSFORM3", -250000000, 0, -250000000, 65546, 500, 65630, (s32)rampell_zoom,
    65630, (s32)init_event_fmario, 196699, (s32)btlevtcmd_GetHp, -2, -30000000, 131098, -30000000,
    10, 196699, (s32)btlevtcmd_SetHp, -2, 10, 33, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_BOSS_RNPLTRANSFORM5", 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -29999995, -29999994, -29999993,
    327771, (s32)evt_sub_intpl_msec_init, 11, -50, 0, 1000, 65541, 0,
    196699, (s32)evt_sub_intpl_msec_get_value_para, -30000000, -29999999, 327771, (s32)btlevtcmd_SetPos, -2, -29999995,
    -30000000, -29999993, 131096, -29999999, 0, 7, 33, 65545,
    1, 6, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_08_03", 0, -2,
    65546, 200, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 2, 1,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_GetMaxHp, -2, LW(0))
    MULTIPLY(LW(0), 50)
    DIVIDE(LW(0), 100)
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(0))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 15, 15)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_RNPL_MOVE1L"), STRING("SFX_BOSS_RNPL_MOVE1R"), 0, 8, 8)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(dead_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 2)
        CALL_CHILD(PTR(to_faker_mario))
        RETURN
    END_IF
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_wait_move_end)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(evt_btl_camera_set_moveto, 1, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    CALL(evt_msg_print, 2, STRING("stg4_jin_08_04"), 0, -2)
    WAIT_MS(300)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("EM_K_1"))
    WAIT_FRAMES(192)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("EM_D_2"))
    WAIT_MS(300)
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, -2, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 2)
                CALL(btlevtcmd_get_turn, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 5)
                    CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                    CALL_CHILD(PTR(to_faker_mario))
                    CALL(btlevtcmd_StartWaitEvent, -2)
                END_IF
            END_IF
            CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
            SWITCH(LW(0))
                CASE_EQUAL(0)
                CALL(btlevtcmd_SetUnitWork, -2, 0, 1)
                CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                CALL(btlevtcmd_StatusWindowOnOff, 0)
                CALL_CHILD(PTR(rampell_zoom))
                CALL(evt_msg_print, 2, STRING("stg4_jin_08_01"), 0, -2)
                WAIT_MS(200)
                CALL(btlevtcmd_StatusWindowOnOff, 1)
                CALL(evt_btl_camera_set_mode, 0, 0)
                CALL(btlevtcmd_StartWaitEvent, -2)
                CASE_EQUAL(1)
                CALL(btlevtcmd_GetHp, -2, LW(0))
                CALL(btlevtcmd_GetUnitWork, -2, 1, LW(1))
                IF_INT_LESS(LW(0), LW(1))
                    CALL(btlevtcmd_PhaseEventStartDeclare, -2)
                    CALL_CHILD(PTR(to_faker_mario))
                    CALL(btlevtcmd_StartWaitEvent, -2)
                END_IF
            END_SWITCH
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    SET_VALUE(LW(9), PTR(weapon_rampell_attack))
    CALL_CHILD(PTR(ogg_attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 ogg_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 8,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"R_1", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 65546,
    250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65546, 500,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131125, -30000000, 120, 131125,
    -29999999, 70, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952, 110,
    65545, 10, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998464, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_FLY1", -250000000, 0, -250000000, 65545, 15,
    262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 112, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 50, 7, 4, 0,
    -1, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229999232, 65546, 200,
    110, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 15, 0, 327771,
    (s32)evt_sub_intpl_msec_init, 1, 0, 135, 200, 65541, 0, 196699,
    (s32)evt_sub_intpl_msec_get_value_para, -30000000, -29999999, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    -30000000, 131096, -29999999, 0, 7, 33, 65545, 1,
    6, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_RNPL_FALL1", -250000000, 0,
    -250000000, 65546, 80, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998,
    1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed,
    -2, 1, -229997952, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999990, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 15, -1, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_RNPL_DOWN1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"D_2", 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"O_1", 65546, 800, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"R_2", 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229997952, 110, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 15, 0, 327771, (s32)evt_sub_intpl_init, 4, 135,
    0, 20, 65541, 0, 196699, (s32)evt_sub_intpl_get_value_para, -30000000, -29999999,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 131096, -29999999,
    0, 7, 33, 65545, 1, 6, 112, 262235,
    (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"J_1B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -30000000, 60, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999232, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, 0, -29999998, 20, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_RNPL_LANDING1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_1A", 65546, 200, 262235, (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1,
    -229997952, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_1", 65539, 98,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 262235,
    (s32)btlevtcmd_AnimeSetMotionSpeed, -2, 1, -229998976, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"S_1", 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static __declspec(section ".data") s32 defence_fmario[] = {
    0, 0,
};

static __declspec(section ".data") s32 defence_attr_fmario[] = {
    0, 0,
};

static __declspec(section ".data") s32 regist_fmario[] = {
    842155570, 842163240, 1682334790, 1683632640, 6566500, 1677918208,
};

static PoseTableEntry pose_table_fmario_stay[] = {
    {1, "EM_N_1"},
    {2, "EM_Y_2"},
    {9, "EM_Y_2"},
    {5, "EM_K_1"},
    {4, "EM_K_1"},
    {3, "EM_K_1"},
    {28, "EM_S_1"},
    {39, "EM_D_1"},
    {50, "EM_A_1"},
    {42, "EM_R_1"},
    {40, "EM_W_1"},
    {56, "EM_D_3"},
    {57, "EM_D_3"},
    {65, "EM_T_1"},
    {69, "EM_S_1"},
};

static __declspec(section ".data") s32 data_table_fmario[] = {
    49, (s32)dead_event_fmario, 0, 0,
};

static s32 parts_fmario[] = {
    1, (s32)"btl_un_hatena", (s32)"c_mario", 0, 0, 0, 1077936128, 1104674816,
    0, 0, 1106247680, 0, 1310750, 16711680, (s32)defence_fmario, (s32)defence_attr_fmario,
    9, 0, (s32)pose_table_fmario_stay,
};

static s32 weapon_masao_jump[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_hammer[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kururin_jump[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 88071, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_masao_kaiten_hammer[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, 0, 67591, 524, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(mario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, -110, 65, 332, -110, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(enemy_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 115, 65, 332, 115, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(fmario_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 90, 65, 332, 90, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(gparty_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, 130, 65, 332, 130, 30, -340, 30, 11)
    WAIT_FRAMES(37)
    RETURN
EVT_END()

static EVT_BEGIN(init_event_fmario)
    CALL(btlevtcmd_AnimeSetPoseTable, -2, LW(11), PTR(pose_table_fmario_stay))
    CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_fmario))
    CALL(btlevtcmd_ReplaceParts, -2, LW(11), PTR(parts_fmario), 1)
    CALL(btlevtcmd_SetRegistStatus, -2, PTR(regist_fmario))
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_fmario))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_fmario))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_fmario))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, -2, 4)
    CALL(btlevtcmd_ClearAllStatus, -2)
    CALL(_mario_makkuro_set)
    SET_VALUE(GW(17), -1)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_BOSS_NM_JUMP1"), STRING("SFX_BOSS_NM_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 dead_event_fmario[] = {
    131163, (s32)evt_btl_camera_set_prilimit, 1, 65627, (s32)evt_btl_camera_wait_move_end, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    196699, (s32)evt_btl_camera_set_mode, 1, 3, 655451, (s32)evt_btl_camera_set_moveto, 1, 90,
    65, 332, 90, 30, -340, 30, 11, 65545,
    37, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_S_1", 65546, 300,
    196699, (s32)btlevtcmd_SetTalkPose, -2, (s32)"EM_T_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"EM_S_1",
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_08_04", 0, -2, 65546, 300,
    131163, (s32)evt_btl_camera_set_prilimit, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_K_1", 65545, 152, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_NM_DOWN2", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_VOICE_NM_LAND_DAMAGE2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"EM_D_2", 65546, 1500, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 131122, -29999990,
    -2, 65630, (s32)subsetevt_dead_core_nospin_norotate, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(damage_event_fmario)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event_fmario)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 2, 50, 50)
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(9), PTR(weapon_masao_jump))
        CALL_CHILD(PTR(marioAttackEvent_NormalJump))
        CASE_EQUAL(1)
        SET_VALUE(LW(9), PTR(weapon_masao_hammer))
        CALL_CHILD(PTR(marioAttackEvent_NormalHammer))
        CASE_EQUAL(2)
        SET_VALUE(LW(9), PTR(weapon_masao_kururin_jump))
        CALL_CHILD(PTR(marioAttackEvent_KururinJump))
        CASE_EQUAL(3)
        SET_VALUE(LW(9), PTR(weapon_masao_kaiten_hammer))
        CALL_CHILD(PTR(marioAttackEvent_KaitenHammer))
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 jump_attack_voice[] = {
    196699, (s32)evt_sub_random, 2, -29999985, 65570, -29999985, 65572, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_1", -250000000, 0, -250000000, 65572,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_2", -250000000, 0, -250000000,
    65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_VOICE_NM_AC1_5", -250000000, 0,
    -250000000, 49, 2, 1,
};

static s32 marioAttackEvent_NormalJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_KururinJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997, -1, 262235,
    (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0, 65630,
    (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts,
    0, -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition,
    -2, -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999994, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP1", -250000000, 0, -250000000, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, 36, 0, -1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_D_2", 65545, 40, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65647, -29999986, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_J_1B", 65630, (s32)jump_attack_voice, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, 36, 0, -1, 112, 65545, 15,
    65631, -29999986, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985,
    -30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_Z_2", 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 12, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_JUMP_KURURIN1",
    -250000000, 0, -250000000, 65541, 12, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -29999985, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 4, 0, 0, 0, -1, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_J_1B", 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    8, -1, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_NormalHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static s32 marioAttackEvent_KaitenHammer[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 11,
    393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 24, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1A", 65546, 66, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_NM_HAMMER_FURU2", -250000000, 0, -250000000, 65546, 233, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_A_1B", 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_A_1C", 65546, 50, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_NM_HAMMER_DON2",
    -250000000, 0, -250000000, 65546, 100, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256,
    -29999995, 65539, 98, 65546, 700, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"EM_S_1", 65546, 200, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"EM_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event_fmario)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

