#pragma dollar_identifiers on
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
#include <string.h>

typedef struct HeartWork {
    u8 pad[0x78];
    BattleUnit* unit;
    s32 cur;
    s32 start;
    s32 end;
    s32 total;
    s32 stop;
    s32 unitId;
    s32 partId;
} HeartWork;

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

USER_FUNC(_vivian_make_extra_work_area);
USER_FUNC(battle_evt_majo_disp_on);
USER_FUNC(btlevtcmd_ACRGetResult);
USER_FUNC(btlevtcmd_ACRStart);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnimeWaitPlayComplete);
USER_FUNC(btlevtcmd_AudienceAppeal);
USER_FUNC(btlevtcmd_AudienceDeclareAcrobatResult);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetMoveFrame);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_InviteApInfoReport);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_PhaseEventStartDeclare);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetDiveSound);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetJumpSound);
USER_FUNC(btlevtcmd_SetMoveSoundDataWork);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WaitEventEnd);
USER_FUNC(evt_audience_acrobat_notry);
USER_FUNC(evt_audience_ap_recovery);
USER_FUNC(evt_eff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(_disp_heart_entry_stop_check);
USER_FUNC(_disp_heart_entry_stop);
void _disp_heart(CameraId camera, void* param);
USER_FUNC(_disp_heart_entry);
USER_FUNC(_make_kagenuke_weapon);
USER_FUNC(_get_vivian_attack_position);
USER_FUNC(_get_move_frame);
static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count);
USER_FUNC(battle_evt_majo_disp_off);
extern s32 _attack_aud[];
extern s32 _get_attack_aud_no[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btldefaultevt_SuitoruBadgeEffect[];
extern s32 btldefaultevt_avoid_counter_event[];
extern s32 btlevtcmd_ACSuccessEffect[];
extern s32 btlevtcmd_AcGetDifficulty[];
extern s32 btlevtcmd_AcGetOutputParam[];
extern s32 btlevtcmd_AcSetDifficulty[];
extern s32 btlevtcmd_AcSetFlag[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceDeclareACResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CommandCheckDamage[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetHeight[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPartyTechLv[];
extern s32 btlevtcmd_GetResultAC[];
extern s32 btlevtcmd_GetResultPrizeLv[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageAudienceAreaSize[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetWidth[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_StopAC[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unit_audience[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_snd_sfxon[];
extern s32 evt_sub_random[];
extern s32 subset_attack_ready_jump_event[];
extern s32 weaponGetACOutputParam[];
extern s32 weaponGetPowerFromPartyAttackLv[];

__declspec(section ".data") u64 lbl_80388868;
__declspec(section ".data") static u64 negone_one$374;
__declspec(section ".data") u64 lbl_80388878;
__declspec(section ".data") static u64 one_negone$373;
__declspec(section ".data") u64 lbl_80388888;
__declspec(section ".data") static u64 negone_one$360;
__declspec(section ".data") u64 lbl_80388898;
__declspec(section ".data") static u64 one_negone$359;
PoseTableEntry pose_table_vivian_stay[24];
static BattleDataEntry data_table[20];
BattleUnitKindPart unitpartsdata_Party_Vivian[1];
BattleUnitKind unitdata_Party_Vivian;
typedef struct { BattleUnitDefense d; u8 pad[3]; } VivDef;
typedef struct { BattleUnitDefenseAttr d; u8 pad[3]; } VivDefAttr;
typedef struct { StatusVulnerability d; u8 pad[2]; } VivRegist;
static VivDef defence;
static VivDefAttr defence_attr;
static VivRegist regist;
static s32 attack_event[2];
static s32 wait_event[6];
static s32 battle_entry_event[59];
static s32 init_event[68];
static s32 damage_event[16];
s32 vivian_hide_event[209];
s32 partyWeapon_VivianNormalAttack[48];
s32 partyWeapon_VivianShadowGuard[48];
s32 partyWeapon_VivianMagicalPowder[48];
s32 partyWeapon_VivianCharmKissAttack[48];
s32 partyVivianAttack_NormalAttack[581];
s32 partyVivianAttack_ShadowGuard[430];
s32 partyVivianAttack_MagicalPowder[442];
s32 partyVivianAttack_CharmKissAttack[464];
s32 vivian_shadow_tail_event[78];
s32 vivian_counter_damage_event[177];
s32 vivian_appeal_event[80];
static s32 party_win_reaction[18];
static s32 attack_audience_event[189];












__declspec(section ".data") u64 lbl_80388868 = 0xBF8000003F800000;

__declspec(section ".data") static u64 negone_one$374 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80388878 = 0x3F800000BF800000;

__declspec(section ".data") static u64 one_negone$373 = 0x3F800000BF800000;

__declspec(section ".data") u64 lbl_80388888 = 0xBF8000003F800000;

__declspec(section ".data") static u64 negone_one$360 = 0xBF8000003F800000;

__declspec(section ".data") u64 lbl_80388898 = 0x3F800000BF800000;

__declspec(section ".data") static u64 one_negone$359 = 0x3F800000BF800000;

PoseTableEntry pose_table_vivian_stay[] = {
    {9, "PTR_D_4"},
    {2, "PTR_D_4"},
    {3, "PTR_X_1"},
    {4, "PTR_D_2"},
    {5, "PTR_X_1"},
    {1, "PTR_N_1"},
    {27, "PTR_D_3"},
    {28, "PTR_S_1"},
    {37, "PTR_G_2"},
    {31, "PTR_G_1"},
    {39, "PTR_D_1"},
    {40, "PTR_W_1"},
    {42, "PTR_R_1"},
    {57, "PTR_D_2"},
    {56, "PTR_D_2"},
    {60, "PTR_D_4"},
    {61, "PTR_D_2"},
    {65, "PTR_T_1"},
    {52, "PTR_I_1"},
    {67, "PTR_C_1"},
    {64, "PTR_X_1"},
    {49, "PTR_D_1"},
    {45, "PTR_G_1"},
    {69, "PTR_S_1"},
};

static BattleDataEntry data_table[] = {
    {3, vivian_hide_event},
    {5, vivian_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {25, vivian_counter_damage_event},
    {26, vivian_counter_damage_event},
    {27, vivian_counter_damage_event},
    {28, vivian_counter_damage_event},
    {29, vivian_counter_damage_event},
    {30, vivian_counter_damage_event},
    {31, vivian_counter_damage_event},
    {32, vivian_counter_damage_event},
    {33, vivian_counter_damage_event},
    {34, vivian_counter_damage_event},
    {35, vivian_counter_damage_event},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Vivian[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence.d, &defence_attr.d, 0x9, 0, pose_table_vivian_stay},
};

BattleUnitKind unitdata_Party_Vivian = {
    228,
    "btl_un_vivian",
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
    14,
    36,
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
    0x2000004,
    &regist.d,
    1,
    unitpartsdata_Party_Vivian,
    init_event,
    data_table,
};

static VivDef defence = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

static VivDefAttr defence_attr = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

static VivRegist regist = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, {0, 0}};

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

#define INTPL(mode, cur, steps, a, b) ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(a, b, mode, cur, steps)

USER_FUNC(battle_evt_majo_disp_on) {
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, partNo, flag;
    f32 px, py, pz;
    s32 pose;

    id = BattleTransID(event, evtGetValue(event, args[0]));
    partNo = evtGetValue(event, args[1]);
    px = evtGetFloat(event, args[2]);
    py = evtGetFloat(event, args[3]);
    pz = evtGetFloat(event, args[4]);
    flag = evtGetValue(event, args[5]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partNo);
    pose = part->poseId;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            v.x = px;
            v.y = py - 200.0f;
            v.z = pz;
            unit->mPosition = v;
        }
        animEffectAsync("p_bibi", 1);
    }
    switch (event->userdata[0]) {
        case 0:
            part->shadowScale = INTPL(0, event->userdata[1], 30, 0.0f, 2.0f);
            if (event->userdata[1] == 0) {
                psndSFXOn_3D("SFX_BTL_VIVIAN_SHADOW1_1", &unit->mPosition);
            }
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                event->userdata[0]++;
            }
            break;
        case 1:
            if (event->userdata[1] <= 30) {
                part->shadowScale = INTPL(0, event->userdata[1], 30, 0.0f, 2.0f);
                event->userdata[1]++;
            }
            if (!animEffectAsync("p_bibi", 1)) {
                return EVT_RETURN_BLOCK;
            }
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                v.x = px;
                v.y = py;
                v.z = pz;
                unit->mPosition = v;
            }
            animPoseSetEffect(pose, "p_bibi", 1);
            animPoseSetEffectAnim(pose, "PM_B_2\0", 1);
            event->userdata[0]++;
            break;
        case 2:
            if (event->userdata[1] <= 30) {
                part->shadowScale = INTPL(0, event->userdata[1], 30, 0.0f, 2.0f);
                event->userdata[1]++;
            }
            if (animPoseGetLoopTimes(animPoseGetAnimPosePtr(pose)->paperId) >= 0.6666667f) {
                animPoseSetPaperAnimGroup(pose, NULL, 1);
                event->userdata[0]++;
                event->userdata[1] = 0;
            }
            break;
        case 3:
            part->shadowScale = INTPL(0, event->userdata[1], 15, 2.0f, 1.0f);
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                part->shadowScale = 1.0f;
                animPoseSetEffect(pose, NULL, 1);
                if (flag != 0) {
                    unit->flags &= ~0x10000;
                }
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}


static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 250)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, -2, STRING("SFX_PARTY_BATTLE_SUBHANG1"), STRING("SFX_PARTY_BATTLE_SUBHANG1"), 0, 6, 6, 0, 0)
    CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(_vivian_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    SPAWN_EVENT(PTR(vivian_shadow_tail_event))
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 11, 11)
    CALL(btlevtcmd_SetDiveSound, -2, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 11, 11)
    CALL(btlevtcmd_SetJumpSound, -2, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

EVT_BEGIN(vivian_hide_event)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        SUBTRACT(LW(0), 1)
    END_IF
    CALL(btlevtcmd_SetUnitWork, -2, 4, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        SET_VALUE(LW(3), -3)
        CALL(btlevtcmd_PhaseEventStartDeclare, LW(3))
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 15)
        CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_OffAttribute, LW(3), 16)
            CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, 50331648)
            CALL(battle_evt_majo_disp_on, LW(3), 1, LW(0), LW(1), LW(2), 1)
            CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetMoveSpeed, LW(3), FLOAT(2.0f))
            CALL(btlevtcmd_MovePosition, LW(3), LW(0), LW(1), LW(2), 0, -1, 0)
        END_INLINE_EVENT
        CALL(btlevtcmd_OffPartsAttribute, -2, 1, 65536)
        CALL(btlevtcmd_OffPartsAttribute, -2, 1, 16777216)
        CALL(battle_evt_majo_disp_on, -2, 1, LW(0), LW(1), LW(2), 1)
        CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetMoveFrame, -2, LW(0), LW(1), LW(2), FLOAT(2.0f), LW(15))
        BEGIN_SIBLING_EVENT_GET_ID(LW(14))
            CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), LW(15), -1, 0)
        END_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, -2, 0, LW(15), LW(15), 15)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
        SWITCH(LW(6))
            CASE_GREATER_OR_EQUAL(2)
            DELETE_EVENT(LW(14))
            CALL(btlevtcmd_AudienceDeclareAcrobatResult, PTR(partyWeapon_VivianShadowGuard), 1, 0, 0, 0)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PTR_Y_1"))
            CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(2.0f))
            CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
            CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
            CASE_DEFAULT
            CALL(evt_audience_acrobat_notry)
            CALL(btlevtcmd_WaitEventEnd, LW(14))
        END_SWITCH
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
        CALL(btlevtcmd_StartWaitEvent, -2)
    END_IF
    RETURN
EVT_END()

s32 partyWeapon_VivianNormalAttack[] = {
    (s32)"btl_wn_ptr_normal", 22020096, 0, (s32)"msg_ptr_kagenuke", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromPartyAttackLv,
    3, 3, 4, 4, 5, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, (s32)"msg_ac_kagenuke", 196615, 2, -2147475452,
    0, 0, 0, 100, 33554432, 0, 0, 0,
    0, 0, 0, 0, (s32)partyVivianAttack_NormalAttack, 100, 131584, 0,
};

s32 partyWeapon_VivianShadowGuard[] = {
    (s32)"btl_wn_ptr_lv1", 22085632, 0, (s32)"msg_ptr_kagegakure", 1677787136, 1065353216, 33907762, 0,
    0, 2, 2, 3, 3, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 268435458, 770, (s32)"msg_ac_kagegakure", 131080, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyVivianAttack_ShadowGuard, 100, 0, 0,
};

s32 partyWeapon_VivianMagicalPowder[] = {
    (s32)"btl_wn_ptr_lv2", 22151168, 0, (s32)"msg_ptr_mahou_no_kona", 1678114816, 1065353216, 17130546, (s32)weaponGetACOutputParam,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, (s32)"msg_ac_mahou_no_kona", 131143, 2047, -2147475456,
    0, 0, 0, 100, 50331648, 0, 0, 0,
    0, 0, 0, 0, (s32)partyVivianAttack_MagicalPowder, 100, 328960, 0,
};

s32 partyWeapon_VivianCharmKissAttack[] = {
    (s32)"btl_wn_ptr_lv3", 22216704, 0, (s32)"msg_ptr_meromero_kiss", 1677983744, 1065353216, 33907762, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_ac_meromero_kiss", 131072, 2047, -2147475452,
    0, 0, 6554368, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)partyVivianAttack_CharmKissAttack, 100, 328960, 0,
};

s32 partyVivianAttack_NormalAttack[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 196699,
    (s32)btlevtcmd_GetPartyTechLv, -2, -30000000, 65570, -30000000, 65572, 2, 196699,
    (s32)_make_kagenuke_weapon, -29999988, 2, 65572, 1, 196699, (s32)_make_kagenuke_weapon, -29999988,
    2, 42, 196699, (s32)_make_kagenuke_weapon, -29999988, 2, 49, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915,
    (s32)btlevtcmd_AcSetParamAll, 1, 1, 40, 1, 2, 0, 3,
    0, 131163, (s32)btlevtcmd_AcSetFlag, 23, 327771, (s32)btlevtcmd_SetupAC, -2, 18,
    1, 0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_VIVIAN_ATTACK1", 0, 327771, (s32)battle_evt_majo_disp_off,
    -2, 1, 0, 0, 131163, (s32)btlevtcmd_StartAC, 1, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)_get_vivian_attack_position,
    -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000,
    -29999999, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    50, 0, 5, 0, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    3, 1, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_VIVIAN_ATTACK2", -250000000, 0, -250000000, 458843, (s32)battle_evt_majo_disp_on,
    -2, 1, -30000000, -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPos,
    -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994,
    -29999993, -29999992, 327771, (s32)_get_vivian_attack_position, -29999997, -30000000, -29999999, -29999998,
    327771, (s32)_get_vivian_attack_position, -29999997, -29999994, -29999993, -29999992, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -29999994, -29999993, -29999992, 196699, (s32)btlevtcmd_GetFaceDirection, -29999997, -29999985, 131127,
    -29999985, -1, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999994, -29999993, -29999992, 589915, (s32)_get_move_frame, -30000000, -29999999,
    -29999998, -29999994, -29999993, -29999992, -229995904, -29999994, 131101, -29999994,
    1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_VIVIAN_ATTACK3", -250000000, 0, -250000000,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 12, 0,
    5, 0, -1, 33, 65539, 9, 393307, (s32)btlevtcmd_CommandPreCheckDamage,
    -2, -29999997, -29999996, 256, -29999995, 131096, -29999995, 5,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    33, 65627, (s32)btlevtcmd_ResultAC, 131122, -29999990, 0, 65539, 10,
    131101, -29999990, 1, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999988, 1048832, -29999995, 32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 33, 65570, -29999995, 65579,
    2, 65579, 3, 65579, 6, 65579, 4, 46,
    65572, 1, 42, 49, 131097, -29999995, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A1_2", 65546, 166, 131096, -29999995,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995,
    6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65546, 500,
    65540, 90, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A1_2",
    196699, (s32)btlevtcmd_ftomsec, 4, -30000000, 65546, -30000000, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_BTL_VIVIAN_ATTACK4", 0, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328, -29999995,
    32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 536871168,
    -29999995, 33, 131102, -30000000, 2, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    33, 65546, 500, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 65539,
    95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A1_1", 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 12,
    0, 5, 0, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3,
    0, 327771, (s32)battle_evt_majo_disp_off, -2, 1, 0, 0, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2,
    -250000000, -29999999, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 40, 0, 5, 0, -1, 110, 393307,
    (s32)btlevtcmd_ACRStart, -2, 20, 29, 29, 0, 112, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 458843, (s32)battle_evt_majo_disp_on, -2,
    1, -30000000, -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096,
    -29999994, 2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PTR_Y_1", 65545, 52, 33, 65539, 99, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyVivianAttack_ShadowGuard[] = {
    131122, -29999997, -3, 196699, (s32)btlevtcmd_GetBodyId, -29999997, -29999996, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild,
    -2, 7, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 327771, (s32)evt_btl_camera_set_posoffset, 0, 20, 0,
    0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -1, 16,
    -30000000, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PTR_A2_1", 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -29999997, -30000000, 15, 131125, -29999998, 5,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -1, 16, -30000000, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -30000000, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163,
    (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126, -30000000, 3, 65570, -30000000, 65576,
    -3, 131122, -30000000, 420, 65572, -2, 131122, -30000000,
    330, 65572, -1, 131122, -30000000, 270, 65572, 0,
    131122, -30000000, 240, 65572, 1, 131122, -30000000, 200,
    65572, 2, 131122, -30000000, 160, 42, 131122, -30000000,
    120, 49, 589915, (s32)btlevtcmd_AcSetParamAll, -30000000, 1, 5, -2,
    5, -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 0, 327771,
    (s32)btlevtcmd_SetupAC, -2, 10, 1, 0, 65545, 22, 131163,
    (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131103,
    -30000000, 2, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 65627, (s32)btlevtcmd_StopAC,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229997952, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65540, 90, 33, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -1, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 327771, (s32)evt_btl_camera_set_posoffset,
    0, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PTR_A2_2", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PTR_A2_3", 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 110, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"M_B_3", 327771, (s32)battle_evt_majo_disp_off, -29999997, 1,
    1, 0, 196699, (s32)btlevtcmd_OnAttribute, -29999997, 16, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -29999997, 1, 50331648, 65545, 1, 327771, (s32)btlevtcmd_GetHomePos, -29999997,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999,
    -29999998, 112, 327771, (s32)battle_evt_majo_disp_off, -2, 1, 1, 1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos,
    -29999997, -29999995, -29999999, -29999998, 131125, -30000000, -29999995, 131128,
    -30000000, 2, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 131125,
    -29999999, 1, 983131, (s32)evt_eff, 0, (s32)"ripple", 1, -30000000,
    -29999999, -29999998, 0, 0, 0, 0, 0, 0,
    0, 0, 65546, 333, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1,
    16842752, 65545, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, 1,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 65545, 1, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -1,
    -1, 4, -30000000, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -30000000, 65546,
    500, 65539, 90, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539,
    95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0, 0, 65539,
    99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 partyVivianAttack_MagicalPowder[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65545, 20, 131163,
    (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty,
    -30000000, 131126, -30000000, 3, 65570, -30000000, 65576, -3,
    131122, -30000000, 360, 65572, -2, 131122, -30000000, 270,
    65572, -1, 131122, -30000000, 210, 65572, 0, 131122,
    -30000000, 180, 65572, 1, 131122, -30000000, 160, 65572,
    2, 131122, -30000000, 140, 42, 131122, -30000000, 120,
    49, 589915, (s32)btlevtcmd_AcSetParamAll, -30000000, 1, 5, -3, 1,
    -250000000, -250000000, -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 7, 327771, (s32)btlevtcmd_SetupAC,
    -2, 10, 1, 0, 65545, 22, 196699, (s32)evt_btl_camera_set_mode,
    0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, 1, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0, 400, 327771,
    (s32)evt_btl_camera_set_posoffset, 0, 20, 0, 0, 131163, (s32)btlevtcmd_StartAC, 1,
    65627, (s32)btlevtcmd_ResultAC, 65627, (s32)btlevtcmd_StopAC, 110, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetWidth, -2, -29999995, 196699,
    (s32)btlevtcmd_GetHeight, -2, -29999994, 983131, (s32)evt_eff, 0, (s32)"stardust", 4,
    -30000000, -29999999, -29999998, -29999995, -29999994, 30, 60, 0,
    0, 0, 0, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_VIVIAN_MAGIC1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A3_1",
    196699, (s32)btlevtcmd_ftof, 20, -30000000, 65545, 20, 196699, (s32)btlevtcmd_ftof,
    26, -30000000, 196699, (s32)btlevtcmd_ftof, 46, -29999999, 393307, (s32)btlevtcmd_ACRStart,
    -2, -30000000, -29999999, -29999999, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994,
    -29999993, 65570, -29999994, 65577, 2, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988,
    1, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PTR_Y_1", 42, 65627, (s32)evt_audience_acrobat_notry, 49, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 65545, 40, 131122,
    -29999990, 0, 65539, 10, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 983131, (s32)evt_eff, 0, (s32)"kemuri_test", 6,
    -30000000, -29999999, -29999998, -229998976, 0, 0, 0, 0,
    0, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996,
    256, -29999994, 131097, -29999994, 1, 131096, -29999994, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999994, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999994, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65540, 50, 33,
    196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 131100, -30000000, 3, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 32, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 33, 131096,
    -29999995, 18, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 65570, -30000000,
    65576, 0, 131122, -30000000, -1, 65579, 1, 65579,
    2, 131122, -30000000, 0, 46, 65579, 3, 65579,
    4, 131122, -30000000, 1, 46, 42, 131122, -30000000,
    2, 49, 131101, -30000000, 0, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    -30000000, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    33, 33, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 131125, -29999990, 1, 65540, 10,
    33, 65539, 80, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539,
    90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 327771, (s32)evt_btl_camera_set_posoffset, 0, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A1_1", 65546, 800, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 partyVivianAttack_CharmKissAttack[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65545, 20, 131122,
    -29999990, 0, 65539, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"PTR_A4_1", 196699, (s32)evt_snd_sfxon, (s32)"SFX_PARTY_MOJIMOJI1", 0, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000,
    196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000, 131126,
    -30000000, 3, 65570, -30000000, 65576, -3, 131122, -29999995,
    60, 65572, -2, 131122, -29999995, 45, 65572, -1,
    131122, -29999995, 30, 65572, 0, 131122, -29999995, 25,
    65572, 1, 131122, -29999995, 20, 65572, 2, 131122,
    -29999995, 12, 42, 131122, -29999995, 6, 49, 196699,
    (s32)evt_sub_random, -29999999, 89, 131125, -29999999, 30, 131122, -29999998,
    -29999999, 131126, -29999998, -29999995, 589915, (s32)btlevtcmd_AcSetParamAll, 5, -29999999,
    -29999998, -29999999, -250000000, -250000000, -250000000, -250000000, 131099, -29999990,
    0, 131163, (s32)btlevtcmd_AcSetFlag, 9, 32, 131163, (s32)btlevtcmd_AcSetFlag, 8,
    33, 327771, (s32)btlevtcmd_SetupAC, -2, 11, 1, 0, 65545,
    22, 131099, -29999990, 0, 131163, (s32)btlevtcmd_StartAC, 0, 32,
    131163, (s32)btlevtcmd_StartAC, 1, 33, 65647, -29999985, 131122, -30000000,
    5, 65541, -30000000, 196699, (s32)btlevtcmd_AcGetOutputParam, 2, -29999999, 131097,
    -29999999, 0, 393307, (s32)_disp_heart_entry, 10, 20, 25, -29999997,
    -29999996, 65545, 1, 7, 33, 131163, (s32)_disp_heart_entry_stop_check, -29999999,
    131097, -29999999, 0, 7, 33, 131122, -30000000, 5,
    65545, 1, 6, 112, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC,
    -29999993, 131178, -29999985, -30000000, 131097, -30000000, 0, 131163,
    (s32)_disp_heart_entry_stop, -29999985, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_A4_2",
    65546, 200, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_VIVIAN_MEROMERO1", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 15, 131125, -29999999, 30, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999994, 131127, -29999994, 45, 983131, (s32)evt_eff,
    0, (s32)"kiss", 4, -30000000, -29999999, -29999998, -29999994, 0,
    0, 0, 0, 0, 0, 0, 393307, (s32)btlevtcmd_CommandPreCheckDamage,
    -2, -29999997, -29999996, 256, -29999994, 131097, -29999994, 1,
    131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    65540, 50, 33, 131102, -29999993, 2, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 131328, -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 536871168, -29999995, 33, 131096, -29999995,
    18, 131102, -29999993, 2, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff,
    0, (s32)"kiss", 5, -30000000, -29999999, -29999998, 0, 0,
    0, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988,
    -1, 33, 33, 110, 393307, (s32)btlevtcmd_ACRStart, -2, 0,
    30, 30, 0, 112, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131096, -29999994, 2, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0,
    0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"PTR_Y_1", 65545,
    32, 33, 65545, 5, 65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 10, 33, 65539, 80, 65627, (s32)btlevtcmd_StopAC, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PTR_A1_1", 65545, 48, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

EVT_BEGIN(vivian_shadow_tail_event)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, -2, 0, LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
    CALL(btlevtcmd_SetUnitWork, -2, 2, LW(2))
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, -2, LW(5))
    IF_INT_EQUAL(LW(5), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 3, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, -2, 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
        CALL(btlevtcmd_SetUnitWork, -2, 2, LW(2))
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

s32 vivian_counter_damage_event[] = {
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 196699, (s32)btlevtcmd_OnUnitFlag,
    -2, 1, 131096, -30000000, 43, 131122, -29999986, 36,
    32, 131122, -29999986, 39, 33, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    -29999989, -29999986, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229998976, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999998, -29999997, -29999996, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -29999998,
    25, 131125, -29999997, 25, 655451, (s32)btlevtcmd_DivePosition, -2, -29999998,
    -29999997, -29999996, 5, 0, 0, 0, -1, 65545,
    30, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999995, 131097, -29999995,
    0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 1, -29999999, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -29999998,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 12, 0, 5, 0, -1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 327771, (s32)battle_evt_majo_disp_off, -2,
    1, 0, 0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -250000000, 655451,
    (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 80, 0, 5,
    0, -1, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    458843, (s32)battle_evt_majo_disp_on, -2, 1, -30000000, -29999999, -29999998, 0,
    327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 32, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -29999998, -29999997, -29999996, 655451, (s32)btlevtcmd_DivePosition, -2,
    -29999998, -29999997, -29999996, 5, 0, 0, 0, -1,
    33, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

EVT_BEGIN(vivian_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PTR_O_1"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PTR_O_2"))
    WAIT_MS(333)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 15)
    ADD(LW(1), 30)
    CALL(btlevtcmd_GetFaceDirection, -2, LW(14))
    MULTIPLY(LW(14), 45)
    CALL(evt_eff, STRING(""), STRING("kiss"), 0, LW(0), LW(1), LW(2), LW(14), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(333)
    CALL(btlevtcmd_AudienceAppeal, -2)
    WAIT_MS(500)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PTR_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, -2, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
    RETURN
EVT_END()

static s32 attack_audience_event[] = {
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize,
    -29999997, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999996, 131122,
    -29999992, -29999997, 131127, -29999992, -29999996, 131127, -29999992, -1,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 524379, (s32)btlevtcmd_MovePosition, -2, -29999992, -29999999, -29999998, 0,
    -1, 0, 65545, 20, 327771, (s32)_get_attack_aud_no, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageAudienceAreaSize, -29999996, -250000000, -250000000, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131122, -29999994, -29999996, 131127, -29999994,
    -29999995, 131127, -29999994, -1, 327771, (s32)btlevtcmd_SetPos, -2, -29999994,
    -29999999, -29999998, 196699, (s32)evt_btl_camera_set_mode, 0, 13, 327771, (s32)evt_btl_camera_set_homing_unit_audience,
    0, -2, 1, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 100, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"PTR_A1_2", 196699, (s32)btlevtcmd_ftomsec, 4, -30000000, 65546,
    -30000000, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_VIVIAN_ATTACK4", 0, 196699, (s32)_attack_aud, -29999997,
    0, 65647, -29999985, 65546, 1500, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65546, 1000, 112, 65546, 500, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379,
    (s32)btlevtcmd_MovePosition, -2, -29999994, -29999999, -29999998, 0, -1, 0,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos,
    -2, -29999992, -29999999, -29999998, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};


#define INTPL(mode, cur, steps, a, b) ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(a, b, mode, cur, steps)

USER_FUNC(battle_evt_majo_disp_off) {
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, partNo, flag, flag2;
    s32 pose;

    id = BattleTransID(event, evtGetValue(event, args[0]));
    partNo = evtGetValue(event, args[1]);
    flag = evtGetValue(event, args[2]);
    flag2 = evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partNo);
    pose = part->poseId;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        animEffectAsync("p_bibi", 1);
    }
    switch (event->userdata[0]) {
        case 0:
            part->shadowScale = INTPL(0, event->userdata[1], 30, 1.0f, 2.0f);
            if (flag != 0) {
                unit->flags |= 0x10000;
            }
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                event->userdata[0]++;
            }
            break;
        case 1:
            if (event->userdata[1] <= 30) {
                part->shadowScale = INTPL(0, event->userdata[1], 30, 1.0f, 2.0f);
                event->userdata[1]++;
            }
            if (!animEffectAsync("p_bibi", 1)) {
                return EVT_RETURN_BLOCK;
            }
            animPoseSetEffect(pose, "p_bibi", 1);
            animPoseSetEffectAnim(pose, "PM_B_1", 1);
            animPoseSetLocalTime(animPoseGetAnimPosePtr(pose)->paperId, 8.0f);
            event->userdata[0]++;
            break;
        case 2:
            if (event->userdata[1] <= 30) {
                part->shadowScale = INTPL(0, event->userdata[1], 30, 1.0f, 2.0f);
                event->userdata[1]++;
            }
            if (animPoseGetLoopTimes(animPoseGetAnimPosePtr(pose)->paperId) >= 1.0f) {
                event->userdata[0]++;
                event->userdata[1] = 0;
                psndSFXOn_3D("SFX_BTL_VIVIAN_SHADOW1_2", &unit->mPosition);
                if (flag2 != 0) {
                    part->attributes |= 0x1000000;
                }
            }
            break;
        case 3:
            part->shadowScale = INTPL(0, event->userdata[1], 20, 2.0f, 0.0f);
            event->userdata[1]++;
            if (event->userdata[1] > 20) {
                part->shadowScale = 0.0f;
                unit->mPosition.y -= 500.0f;
                animPoseSetEffect(pose, NULL, 1);
                animPoseSetPaperAnimGroup(pose, NULL, 1);
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_vivian_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleWorkCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

#define ADD_W(w)                                                                                   \
    command->mWeaponTable[*count].mIndex = -1;                                                     \
    command->mWeaponTable[*count].mItem = 0;                                                       \
    command->mWeaponTable[*count].mWeaponParams = (BattleWeapon*)(w);                              \
    command->mWeaponTable[*count].field_0x4 = 0;                                                   \
    command->mWeaponTable[*count].mIcon = command->mWeaponTable[*count].mWeaponParams->icon;       \
    command->mWeaponTable[*count].mName = (char*)msgSearch(command->mWeaponTable[*count].mWeaponParams->name); \
    (*count)++;
    ADD_W(partyWeapon_VivianNormalAttack)
    if (techLv >= 0) {
        ADD_W(partyWeapon_VivianShadowGuard)
    }
    if (techLv >= 1) {
        ADD_W(partyWeapon_VivianMagicalPowder)
    }
    if (techLv >= 2) {
        ADD_W(partyWeapon_VivianCharmKissAttack)
    }
}

double sqrt(double);

USER_FUNC(_get_move_frame) {
    s32* args = event->args;
    Vec a, b, d;
    f32 speed;
    s32 frames, out;

    a.x = evtGetFloat(event, args[0]);
    a.y = evtGetFloat(event, args[1]);
    a.z = evtGetFloat(event, args[2]);
    b.x = evtGetFloat(event, args[3]);
    b.y = evtGetFloat(event, args[4]);
    b.z = evtGetFloat(event, args[5]);
    speed = evtGetFloat(event, args[6]);
    out = args[7];
    PSVECSubtract(&a, &b, &d);
    frames = (s32)((f32)sqrt(d.x * d.x + d.y * d.y + d.z * d.z) / speed);
    if (frames > 15) {
        frames = 15;
    }
    evtSetValue(event, out, frames);
    return EVT_RETURN_DONE;
}

f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);

USER_FUNC(_get_vivian_attack_position) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* self;
    BattleUnit* target;
    s32 targetId, x, y, z;
    s32 i1, i2, i3;
    s32 ix, iy;
    f32 floor;
    f32 sx, sy, sz;

    targetId = evtGetValue(event, args[0]);
    i1 = args[1];
    x = evtGetValue(event, i1);
    i2 = args[2];
    y = evtGetValue(event, i2);
    i3 = args[3];
    z = evtGetValue(event, i3);
    self = BattleGetUnitPtr(wp, BattleTransID(event, -2));
    target = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    BtlUnit_GetScale(target, &sx, &sy, &sz);
    ix = (s32)((f32)target->faceDirection * (target->mKindParams->field_0x54 * sx));
    iy = (s32)(target->mKindParams->field_0x58 * sz);
    {
        x += -30.0f * self->mSizeMultiplier * (f32)self->faceDirection + ix;
        z = z + iy;
        y -= 20.0f * self->mSizeMultiplier;
    }
    floor = BattleGetFloorHeight(wp, x, y, z);
    if (floor > y) {
        y = (s32)floor;
    }
    evtSetValue(event, i1, x);
    evtSetValue(event, i2, y);
    evtSetValue(event, i3, z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_make_kagenuke_weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
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
    weapon->burnTime = value;
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}


USER_FUNC(_disp_heart_entry) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    if (isFirstCall) {
        ((HeartWork*)event)->unit = unit;
        ((HeartWork*)event)->cur = 0;
        ((HeartWork*)event)->start = evtGetValue(event, args[0]);
        ((HeartWork*)event)->end = evtGetValue(event, args[1]);
        ((HeartWork*)event)->total = evtGetValue(event, args[2]);
        ((HeartWork*)event)->stop = 0;
        ((HeartWork*)event)->unitId = evtGetValue(event, args[3]);
        ((HeartWork*)event)->partId = evtGetValue(event, args[4]);
    }
    if (((HeartWork*)event)->stop != 0) {
        return EVT_RETURN_DONE;
    }
    ((HeartWork*)event)->cur++;
    dispEntry(4, 0.0f, 1, (DispCallback)_disp_heart, event);
    return ((HeartWork*)event)->cur < ((HeartWork*)event)->total ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

void _disp_heart(CameraId camera, void* param) {
    HeartWork* w;
    f32 scale;
    Vec p, b, a, c;
    BattleUnit* unit;

    if (param == NULL) {
        return;
    }
    w = param;
    if (w->unit != NULL) {
        {
            if (w->cur <= w->start) {
                scale = intplGetValue(5, w->cur, w->start, 0.0f, 1.2f);
            } else if (w->cur <= w->end) {
                scale = intplGetValue(0xb, w->cur - w->start, w->end - w->start, 1.2f, 1.0f);
            } else {
                scale = 1.0f;
            }
            unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID((EventEntry*)w, w->unitId));
            BtlUnit_GetHitPos(unit, BtlUnit_GetPartsPtr(unit, w->partId), &p.x, &p.y, &p.z);
            p.z += 10.0f;
            a = p;
            b = p;
            c = p;
            b.y = 16.0f * scale + a.y;
            b.z = 5.0f + a.z;
            iconDispGx(&a, 0, 0x1f2, scale);
            iconDispGx(&b, 0, 0x189, scale);
        }
    }
}

USER_FUNC(_disp_heart_entry_stop) {
    EventEntry* e = evtGetPtrID(evtGetValue(event, *event->args));
    ((HeartWork*)e)->stop = 1;
    return EVT_RETURN_DONE;
}

USER_FUNC(_disp_heart_entry_stop_check) {
    evtSetValue(event, *event->args, *(s32*)((u8*)event + 0x8c));
    return EVT_RETURN_DONE;
}


#pragma force_active on
__declspec(section ".sdata") u8 gap_07_80412488_sdata[24] = {0};
#pragma force_active reset
