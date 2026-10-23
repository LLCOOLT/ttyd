#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "mario/mario_pouch.h"
#include "string.h"

BOOL BattlePartyAnimeLoad(s32 id);
typedef struct FakerStatus { s16 data[15]; } FakerStatus;
#ifdef VERSION_G8ME01
typedef struct FakerParam { f32 size; FakerStatus status; s32 statusFlags; u16 commandDisabled[2]; s16 currentHp; s16 maxHp; s16 currentFp; s16 maxFp; } FakerParam;
#else
typedef struct FakerParam { f32 size; FakerStatus status; s32 statusFlags; s16 currentHp; s16 maxHp; s16 currentFp; s16 maxFp; } FakerParam;
#endif

static USER_FUNC(_anime_load);
static USER_FUNC(_anime_load_wait);
USER_FUNC(_gullible_party_info_init);
USER_FUNC(_load_param);
USER_FUNC(_save_param);
#ifdef VERSION_G8ME01
USER_FUNC(faker_mario_sync_max_moves);
#endif
USER_FUNC(btlevtcmd_AddScale);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckDataOfDataTable);
USER_FUNC(btlevtcmd_DrawLots);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetScale);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_SortPhaseMoveTable);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_sub_random);
static USER_FUNC(vivian_comeback);
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHp[];
extern s32 btlevtcmd_GetMarioId[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetStayPose[];
extern s32 btlevtcmd_SetTalkPose[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_get_turn[];
extern s32 btlevtcmd_snd_se[];
extern s32 entryunit_party[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 subsetevt_confuse_flustered[];
extern s32 subsetevt_dead_core_nospin_norotate[];
extern s32 unit_gullible_christine[];
extern s32 unit_gullible_clauda[];
extern s32 unit_gullible_nokotarou[];
extern s32 unit_gullible_yoshi[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_faker_mario_negone_one_374;
__declspec(section ".data") s32 fd_faker_mario_neg_one_382[1];
__declspec(section ".data") s32 fd_faker_mario___local_PI_383[1];
__declspec(section ".data") s32 fd_faker_mario___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_faker_mario_one_negone_373;
__declspec(section ".data") s32 fd_faker_mario___local_PIO2_384[1];
__declspec(section ".data") s32 fd_faker_mario_one_381[1];
__declspec(section ".data") u64 fd_faker_mario_negone_one_360;
__declspec(section ".data") s32 fd_faker_mario_neg_one_365[1];
__declspec(section ".data") s32 fd_faker_mario___local_PI_366[1];
__declspec(section ".data") s32 fd_faker_mario___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_faker_mario_one_negone_359;
__declspec(section ".data") s32 fd_faker_mario___local_PIO2_367[1];
__declspec(section ".data") s32 fd_faker_mario_one_364[1];
BattleUnitKind unit_faker_mario;
static __declspec(section ".data") BattleUnitDefense defence_fmario;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_fmario;
static __declspec(section ".data") StatusVulnerability regist_fmario;
static PoseTableEntry pose_table_fmario_stay[15];
static __declspec(section ".data") BattleDataEntry data_table_fmario[2];
static BattleUnitKindPart parts_fmario[1];
static s32 weapon_masao_jump[48];
static s32 weapon_masao_hammer[48];
static s32 weapon_masao_kururin_jump[48];
static s32 weapon_masao_kaiten_hammer[48];
__declspec(section ".data") s32 entry_gullible_christine[12];
__declspec(section ".data") s32 entry_gullible_nokotarou[12];
__declspec(section ".data") s32 entry_gullible_clauda[12];
__declspec(section ".data") s32 entry_gullible_yoshi[12];
static s32 mario_zoom[19];
static s32 enemy_zoom[19];
static s32 fmario_zoom[19];
static s32 gparty_zoom[19];
static s32 init_event_fmario[189];
s32 fmario_entry_event[24];
s32 dead_event_fmario_down[53];
static s32 dead_event_fmario[198];
static s32 damage_event_fmario[22];
s32 phase_event_fmario[VERSION_PICK(400, 403)];
static s32 attack_event_fmario[60];
static s32 jump_attack_voice[36];
static s32 marioAttackEvent_NormalJump[344];
static s32 marioAttackEvent_KururinJump[469];
static s32 marioAttackEvent_NormalHammer[299];
static s32 marioAttackEvent_KaitenHammer[299];
s32 party_change_event[196];
static __declspec(section ".data") s32 wait_event_fmario[6];

static USER_FUNC(_anime_load_wait) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 anime;

    switch (unit->currentKind) {
        case 0x50:
            anime = 0xE0;
            break;
        case 0x51:
            anime = 0xE1;
            break;
        case 0x53:
            anime = 0xE3;
            break;
        case 0x52:
        default:
            anime = 0xE2;
            break;
    }
    if (BattlePartyAnimeLoad(anime)) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(_anime_load) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 anime;

    switch (unit->currentKind) {
        case 0x50:
            anime = 0xE0;
            break;
        case 0x51:
            anime = 0xE1;
            break;
        case 0x53:
            anime = 0xE3;
            break;
        case 0x52:
        default:
            anime = 0xE2;
            break;
    }
    BattlePartyAnimeLoad(anime);
    return EVT_RETURN_DONE;
}

USER_FUNC(_save_param) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id1));
    BattleUnit* party = BattleGetUnitPtr(wp, BattleTransID(event, id2));
    FakerParam* params = (FakerParam*)unit->countersetWeapon;
    FakerParam* p;

    switch (party->currentKind) {
        case 0x50:
            p = &params[0];
            break;
        case 0x51:
            p = &params[1];
            break;
        case 0x53:
            p = &params[2];
            break;
        case 0x52:
            p = &params[3];
            break;
    }
    p->size = party->mSizeMultiplier;
    p->statusFlags = party->mStatusFlags;
#ifdef VERSION_G8ME01
    p->commandDisabled[0] = party->usCommandDisabled[0];
    p->commandDisabled[1] = party->usCommandDisabled[1];
#endif
    p->status = *(FakerStatus*)&party->mSleepTurns;
    p->maxHp = party->maxHp;
    p->currentHp = party->currentHp;
    p->maxFp = party->maxFp;
    p->currentFp = party->currentFp;
    return EVT_RETURN_DONE;
}

USER_FUNC(_load_param) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id1));
    BattleUnit* party = BattleGetUnitPtr(wp, BattleTransID(event, id2));
    FakerParam* params = (FakerParam*)unit->countersetWeapon;
    FakerParam* p;

    switch (party->currentKind) {
        case 0x50:
            p = &params[0];
            break;
        case 0x51:
            p = &params[1];
            break;
        case 0x53:
            p = &params[2];
            break;
        case 0x52:
            p = &params[3];
            break;
    }
    party->mSizeMultiplier = p->size;
    party->mStatusFlags = p->statusFlags;
#ifdef VERSION_G8ME01
    party->usCommandDisabled[0] = p->commandDisabled[0];
    party->usCommandDisabled[1] = p->commandDisabled[1];
#endif
    *(FakerStatus*)&party->mSleepTurns = p->status;
    party->maxHp = p->maxHp;
    party->currentHp = p->currentHp;
    party->maxFp = p->maxFp;
    party->currentFp = p->currentFp;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_faker_mario_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_faker_mario_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_faker_mario___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_faker_mario___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_faker_mario_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_faker_mario___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_faker_mario_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_faker_mario_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_faker_mario_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_faker_mario___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_faker_mario___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_faker_mario_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_faker_mario___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_faker_mario_one_364[] = {
    1065353216,
};

BattleUnitKind unit_faker_mario = {
    79,
    "btl_un_rampell",
    40,
    0,
    1,
    1,
    54,
    0,
    0,
    100,
    0,
    70,
    7,
    24,
    40,
    12,
    40,
    0.0f,
    20.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    32.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    24.0f,
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
    "SFX_MARIO_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist_fmario,
    1,
    parts_fmario,
    init_event_fmario,
    data_table_fmario,
};

static __declspec(section ".data") BattleUnitDefense defence_fmario = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_fmario = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_fmario = {50, 50, 70, 50, 50, 50, 100, 40, 100, 70, 100, 70, 100, 90, 50, 0, 0, 100, 50, 100, 100, 3};

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

static __declspec(section ".data") BattleDataEntry data_table_fmario[] = {
    {49, dead_event_fmario},
    {0, NULL},
};

static BattleUnitKindPart parts_fmario[] = {
    {1, "btl_un_rampell", "c_mario", 0.0f, 0.0f, 0.0f, 3.0f, 27.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence_fmario, &defence_attr_fmario, 0x9, 0, pose_table_fmario_stay},
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

__declspec(section ".data") s32 entry_gullible_christine[] = {
    (s32)unit_gullible_christine, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_gullible_nokotarou[] = {
    (s32)unit_gullible_nokotarou, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_gullible_clauda[] = {
    (s32)unit_gullible_clauda, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_gullible_yoshi[] = {
    (s32)unit_gullible_yoshi, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
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
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event_fmario))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event_fmario))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event_fmario))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event_fmario))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(fmario_entry_event))
    CALL(btlevtcmd_GetUnitId, -2, GW(16))
    SET_VALUE(GW(17), -1)
    CALL(_gullible_party_info_init)
    CALL(evt_sub_random, 3, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LW(12), PTR(entry_gullible_christine))
        CASE_EQUAL(1)
        SET_VALUE(LW(12), PTR(entry_gullible_nokotarou))
        CASE_EQUAL(2)
        SET_VALUE(LW(12), PTR(entry_gullible_clauda))
        CASE_DEFAULT
        SET_VALUE(LW(12), PTR(entry_gullible_yoshi))
    END_SWITCH
    SET_VALUE(GW(18), 0)
    SET_VALUE(LW(12), PTR(entry_gullible_christine))
    CALL(btlevtcmd_SpawnUnit, LW(3), LW(12), 0)
    SET_VALUE(GW(17), LW(3))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
    ADD(LW(2), 10)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(_load_param, -2, LW(3))
    SET_VALUE(GW(20), 0)
    SET_VALUE(GW(19), 0)
    CALL(btlevtcmd_GetMaxHp, -2, LW(0))
    SET_VALUE(LW(1), LW(0))
    MULTIPLY(LW(1), 66)
    DIVIDE(LW(1), 100)
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
    SET_VALUE(LW(1), LW(0))
    MULTIPLY(LW(1), 50)
    DIVIDE(LW(1), 100)
    CALL(btlevtcmd_SetUnitWork, -2, 2, LW(1))
    SET_VALUE(LW(1), LW(0))
    MULTIPLY(LW(1), 25)
    DIVIDE(LW(1), 100)
    CALL(btlevtcmd_SetUnitWork, -2, 3, LW(1))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    SET_VALUE(GW(21), 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_NM_MOVE1L"), STRING("SFX_BOSS_NM_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_BOSS_NM_JUMP1"), STRING("SFX_BOSS_NM_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(fmario_entry_event)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    WAIT_MS(2000)
    CALL_CHILD(PTR(fmario_zoom))
    CALL(evt_msg_print, 2, STRING("stg4_jin_22"), 0, -2)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    RETURN
EVT_END()

s32 dead_event_fmario_down[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_S_1", 65546, 300, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"EM_T_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"EM_S_1", 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_05", 0, -2, 65546, 300, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"EM_K_1", 65545, 152, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_NM_DOWN2", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_VOICE_NM_LAND_DAMAGE2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"EM_D_2", 65546, 1500, 2, 1,
};

static EVT_BEGIN(dead_event_fmario)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, -2, LW(3), LW(4), LW(5))
    SET_VALUE(LW(6), 1)
    IF_INT_EQUAL(LW(0), LW(3))
        IF_INT_EQUAL(LW(1), LW(4))
            IF_INT_EQUAL(LW(2), LW(5))
                SET_VALUE(LW(6), 0)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LW(6), 1)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("EM_W_1"))
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(6.0f))
        CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 40)
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_ResetFaceDirection, -2)
    END_IF
    WAIT_FRAMES(1)
    CALL(btlevtcmd_WaitAttackEnd)
    IF_INT_EQUAL(GW(21), 0)
        SET_VALUE(GW(21), 1)
        CALL(vivian_comeback)
        CALL(btlevtcmd_SpawnUnit, LW(3), PTR((u8*)entryunit_party + 0xC0), 0)
        CALL(btlevtcmd_SetHomePos, LW(3), FLOAT(-140.0f), FLOAT(0.0f), FLOAT(5.0f))
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, LW(3), 1, LW(1))
        CALL(btlevtcmd_SetUnitWork, LW(3), 2, LW(2))
        WAIT_FRAMES(1)
    END_IF
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    SWITCH(GW(20))
        CASE_EQUAL(0)
        CALL_CHILD(PTR(fmario_zoom))
        CALL_CHILD(PTR(dead_event_fmario_down))
        WAIT_MS(300)
        CALL_CHILD(PTR(gparty_zoom))
        SWITCH(GW(18))
            CASE_EQUAL(0)
            CALL(evt_msg_print, 2, STRING("stg4_jin_26_05_kur"), 0, GW(17))
            CASE_EQUAL(1)
            CALL(evt_msg_print, 2, STRING("stg4_jin_26_05_nok"), 0, GW(17))
            CASE_EQUAL(2)
            CALL(evt_msg_print, 2, STRING("stg4_jin_26_05_win"), 0, GW(17))
            CASE_EQUAL(3)
            CALL(evt_msg_print, 2, STRING("stg4_jin_26_05_yos"), 0, GW(17))
        END_SWITCH
        WAIT_MS(200)
        CASE_EQUAL(1)
        CALL_CHILD(PTR(enemy_zoom))
        CALL_CHILD(PTR(dead_event_fmario_down))
        WAIT_MS(200)
        CASE_EQUAL(2)
        CALL_CHILD(PTR(fmario_zoom))
        CALL_CHILD(PTR(dead_event_fmario_down))
        WAIT_MS(200)
    END_SWITCH
    SET_VALUE(GW(19), 2)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    SET_VALUE(LW(10), -2)
    CALL_CHILD(PTR(subsetevt_dead_core_nospin_norotate))
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_fmario)
    CALL(btlevtcmd_CheckDamageCode, -2, 1024, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GW(19), 1)
    END_IF
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

#ifdef VERSION_G8ME01
s32 phase_event_fmario[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131097, -30000000, 0, 131163,
    (s32)btlevtcmd_get_turn, -30000000, 131096, -30000000, 3, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_23", 0, 0, 65546, 200,
    131122, -49999979, 1, 65627, (s32)vivian_comeback, 262235, (s32)btlevtcmd_SpawnUnit, -29999997,
    (s32)((u8*)entryunit_party + 192), 0, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -230143360, -230000000, -229994880,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -30000000,
    262235, (s32)btlevtcmd_SetUnitWork, -29999997, 1, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -29999997,
    2, -29999998, 131163, (s32)faker_mario_sync_max_moves, -29999997, 65545, 1, 196699,
    (s32)btlevtcmd_GetMarioId, -29999997, -29999995, 196699, (s32)btlevtcmd_GetBodyId, -29999995, -29999994, 131163,
    (s32)btlevtcmd_StopWaitEvent, -29999997, 131163, (s32)btlevtcmd_StopWaitEvent, -29999995, 65546, 700, 65628,
    (s32)mario_zoom, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_VIVIAN_ATTACK2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_SetPos, -29999997, -140, -40, 5, 655451, (s32)btlevtcmd_DivePosition,
    -29999997, -140, 0, 5, 60, 0, 0, 4,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995, -29999994, (s32)"M_Z_1", 65647, -30000000,
    327771, (s32)evt_sub_intpl_init, 0, 0, 180, 15, 65541, 16,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -3, 0, -30000000, 0,
    65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_24", 0, -29999997, 65546, 200, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_FIND1_3", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -29999995, -29999993, -29999992, -29999990, 327771, (s32)btlevtcmd_JumpSetting, -29999995, 12,
    -229998976, -229998772, 458843, (s32)btlevtcmd_JumpPosition, -29999995, -29999993, -29999992, -29999990,
    0, -1, 65546, 1000, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_25",
    0, -29999997, 65546, 1000, 65647, -30000000, 327771, (s32)evt_sub_intpl_init,
    0, 180, 0, 15, 65541, 16, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetRotate, -3, 0, -30000000, 0, 65545, 1,
    6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 65546, 200, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999995, -29999994, (s32)"M_I_Y", 65546, 1000, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    1, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997,
    33, 33, 196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108867, 131097, -30000000,
    0, 131097, -49999980, 0, 65630, (s32)party_change_event, 33, 196699,
    (s32)btlevtcmd_GetHp, -2, -30000000, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999998,
    131097, -49999980, 0, 131096, -29999998, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 1, 131122, -29999998, 1, 33, 33,
    65570, -29999998, 65572, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1,
    -29999999, 131098, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0,
    1, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)enemy_zoom, 65570, -49999982,
    65572, 0, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_kur", 0, -49999983,
    65572, 1, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_nok", 0, -49999983,
    65572, 2, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_win", 0, -49999983,
    65572, 3, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_yos", 0, -49999983,
    49, 65546, 200, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 65572,
    1, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999999, 131098, -30000000,
    -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 2, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    0, 65630, (s32)fmario_zoom, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_01", 0,
    -2, 65546, 200, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 65572,
    2, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999999, 131098, -30000000,
    -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 3, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    0, 65630, (s32)fmario_zoom, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_02", 0,
    -2, 65546, 200, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 49,
    33, 2, 1,
};
#else
s32 phase_event_fmario[] = {
    196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131097, -30000000, 0, 131163,
    (s32)btlevtcmd_get_turn, -30000000, 131096, -30000000, 3, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    327771, (s32)evt_msg_print, 0, (s32)"stg4_jin_23", 0, 0, 65546, 200,
    131122, -49999979, 1, 65627, (s32)vivian_comeback, 262235, (s32)btlevtcmd_SpawnUnit, -29999997,
    (s32)(void*)((u8*)entryunit_party + 0xC0), 0, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -230143360, -230000000, -229994880,
    327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -30000000,
    262235, (s32)btlevtcmd_SetUnitWork, -29999997, 1, -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -29999997,
    2, -29999998, 65545, 1, 196699, (s32)btlevtcmd_GetMarioId, -29999997, -29999995,
    196699, (s32)btlevtcmd_GetBodyId, -29999995, -29999994, 131163, (s32)btlevtcmd_StopWaitEvent, -29999997, 131163,
    (s32)btlevtcmd_StopWaitEvent, -29999995, 65546, 700, 65628, (s32)mario_zoom, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_VIVIAN_ATTACK2", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_SetPos, -29999997,
    -140, -40, 5, 655451, (s32)btlevtcmd_DivePosition, -29999997, -140, 0,
    5, 60, 0, 0, 4, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999995, -29999994, (s32)"M_Z_1", 65647, -30000000, 327771, (s32)evt_sub_intpl_init, 0,
    0, 180, 15, 65541, 16, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -3, 0, -30000000, 0, 65545, 1, 6,
    112, 131163, (s32)btlevtcmd_WaitEventEnd, -30000000, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_24",
    0, -29999997, 65546, 200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_FIND1_3",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999995, -29999993, -29999992,
    -29999990, 327771, (s32)btlevtcmd_JumpSetting, -29999995, 12, -229998976, -229998772, 458843,
    (s32)btlevtcmd_JumpPosition, -29999995, -29999993, -29999992, -29999990, 0, -1, 65546,
    1000, 327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_25", 0, -29999997, 65546,
    1000, 65647, -30000000, 327771, (s32)evt_sub_intpl_init, 0, 180, 0,
    15, 65541, 16, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -3,
    0, -30000000, 0, 65545, 1, 6, 112, 131163,
    (s32)btlevtcmd_WaitEventEnd, -30000000, 65546, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995, -29999994,
    (s32)"M_I_Y", 65546, 1000, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -29999997, 33, 33, 196699,
    (s32)btlevtcmd_CheckPhase, -30000000, 67108867, 131097, -30000000, 0, 131097, -49999980,
    0, 65630, (s32)party_change_event, 33, 196699, (s32)btlevtcmd_GetHp, -2, -30000000,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999998, 131097, -49999980, 0,
    131096, -29999998, 0, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1,
    131122, -29999998, 1, 33, 33, 65570, -29999998, 65572,
    0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999999, 131098, -30000000,
    -29999999, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    0, 65630, (s32)enemy_zoom, 65570, -49999982, 65572, 0, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_kur", 0, -49999983, 65572, 1, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_nok", 0, -49999983, 65572, 2, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_win", 0, -49999983, 65572, 3, 327771,
    (s32)evt_msg_print, 2, (s32)"stg4_jin_26_yos", 0, -49999983, 49, 65546, 200,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 65572, 1, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 2, -29999999, 131098, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 2, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)fmario_zoom,
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_01", 0, -2, 65546, 200,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 65572, 2, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 3, -29999999, 131098, -30000000, -29999999, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 0, 3, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 65630, (s32)fmario_zoom,
    327771, (s32)evt_msg_print, 2, (s32)"stg4_jin_26_02", 0, -2, 65546, 200,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 33, 49, 33, 2, 1,
};
#endif

static EVT_BEGIN(attack_event_fmario)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_DrawLots, LW(0), 4, 50, 50, 20, 20)
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

EVT_BEGIN(party_change_event)
    ADD(GW(18), 1)
    IF_INT_GREATER(GW(18), 4)
        RETURN
    END_IF
    SWITCH(GW(18))
        CASE_EQUAL(0)
        SET_VALUE(LW(12), PTR(entry_gullible_christine))
        CASE_EQUAL(1)
        SET_VALUE(LW(12), PTR(entry_gullible_nokotarou))
        CASE_EQUAL(2)
        SET_VALUE(LW(12), PTR(entry_gullible_clauda))
        CASE_EQUAL(3)
        SET_VALUE(LW(12), PTR(entry_gullible_yoshi))
        CASE_DEFAULT
        RETURN
    END_SWITCH
    SET_VALUE(GW(20), 0)
    SET_VALUE(LW(3), GW(17))
    CALL(btlevtcmd_SpawnUnit, LW(9), LW(12), 0)
    SET_VALUE(GW(17), LW(9))
    CALL(_anime_load, LW(9))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(9), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetScale, LW(3), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        LOOP(18)
            CALL(btlevtcmd_AddScale, LW(3), FLOAT(-0.049804688f), FLOAT(-0.049804688f), FLOAT(-0.049804688f))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_PARTY_IN1"), 0)
    CALL(btlevtcmd_JumpPosition, LW(3), LW(5), LW(6), LW(7), 20, 0)
    CALL(_anime_load_wait, LW(9))
    CALL(_save_param, -2, LW(3))
    CALL(_load_param, -2, LW(9))
    CALL(btlevtcmd_SetPos, LW(9), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, LW(9), FLOAT(0.69921875f))
    CALL(btlevtcmd_CheckDataOfDataTable, LW(9), LW(0), 4)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(9), 4)
    END_IF
    CALL(evt_snd_sfxon, STRING("SFX_PARTY_CHANGE1"), 0)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetScale, LW(9), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
        LOOP(18)
            CALL(btlevtcmd_AddScale, LW(9), FLOAT(0.049804688f), FLOAT(0.049804688f), FLOAT(0.049804688f))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetScale, LW(9), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHomePos, LW(9), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon, STRING("SFX_PARTY_OUT1"), 0)
    CALL(btlevtcmd_JumpPosition, LW(9), LW(0), LW(1), LW(2), 20, 0)
    CALL(btlevtcmd_KillUnit, LW(3), 0)
    CALL(btlevtcmd_SortPhaseMoveTable)
    RETURN
EVT_END()

USER_FUNC(_gullible_party_info_init) {
    PouchData* pouch = pouchGetPtr();
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    FakerParam* params = BattleAlloc(sizeof(FakerParam) * 4);
    s32 i;
    FakerParam* p;

    unit->countersetWeapon = (struct BattleWeapon*)params;
    memset(params, 0, sizeof(FakerParam) * 4);
    for (i = 0; i < 4; i++) {
        p = &params[i];
        p->size = 1.0f;
        p->statusFlags = 0;
        memset(&p->status, 0, sizeof(FakerStatus));
        switch (i) {
            case 0:
                p->maxHp = p->currentHp = pouch->partyData[1].baseMaxHP;
                break;
            case 1:
                p->maxHp = p->currentHp = pouch->partyData[2].baseMaxHP;
                break;
            case 2:
                p->maxHp = p->currentHp = pouch->partyData[5].baseMaxHP;
                break;
            default:
                p->maxHp = p->currentHp = pouch->partyData[4].baseMaxHP;
                break;
        }
        p->maxFp = p->currentFp = pouch->baseMaxFP;
#ifdef VERSION_G8ME01
        p->commandDisabled[0] = 0;
        p->commandDisabled[1] = 0;
#endif
    }
    return EVT_RETURN_DONE;
}

#ifdef VERSION_G8ME01
// US only: restore the moves of the unit for this turn.
USER_FUNC(faker_mario_sync_max_moves) {
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

static __declspec(section ".data") EVT_BEGIN(wait_event_fmario)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

