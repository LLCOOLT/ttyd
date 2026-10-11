#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "memory.h"
#include "driver/effdrv.h"
#include "eff/eff_syuryou.h"

static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);
f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
static s32 zanzou_count[3];
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
typedef struct BarriernSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BarriernSpline;
void spline_maketable(s32 n, s32* table, f32* a, f32* b);
void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);
static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table);
s32 irand(s32 scalar);
EffectEntry* effGlassN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);

static USER_FUNC(_check_satellite);
static USER_FUNC(barriern_satellite_zanzou);
static USER_FUNC(barriern_satellite_zanzou2);
static USER_FUNC(battleGetBarriernSatelliteInitPos);
USER_FUNC(btlevtcmd_AddPartsScale);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckPartsAttribute);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetPartsWork);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPartsPosition);
USER_FUNC(btlevtcmd_JumpPartsSetting);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_RecoverHp);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPartsBlur);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPartsScale);
USER_FUNC(btlevtcmd_SetPartsWork);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRGB);
USER_FUNC(btlevtcmd_SetScale);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_random);
static USER_FUNC(outSplineTableSet);
static USER_FUNC(barriern_zanzou);
static USER_FUNC(barriern_zanzou2);
static USER_FUNC(barriern_zanzou3);
static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type);
static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type);
static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);
static USER_FUNC(barriernSatelliteToInside);
static USER_FUNC(barriernSatelliteToOutside);
static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table);
static USER_FUNC(barriern_wawawa_set_target);
static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx);
static void barriern_wawawa_get_next_target(s32* unitIdx, s32* partIdx);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AddPos[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AddUnitWork[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckPhase[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_StopWaitEvent[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_get_turn[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_snd_sfxoff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 unit_barriern_satellite_19_data_30B08[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_barriern_negone_one_374;
__declspec(section ".data") s32 fd_barriern_neg_one_382[1];
__declspec(section ".data") s32 fd_barriern___local_PI_383[1];
__declspec(section ".data") s32 fd_barriern___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_barriern_one_negone_373;
__declspec(section ".data") s32 fd_barriern___local_PIO2_384[1];
__declspec(section ".data") s32 fd_barriern_one_381[1];
__declspec(section ".data") u64 fd_barriern_negone_one_360;
__declspec(section ".data") s32 fd_barriern_neg_one_365[1];
__declspec(section ".data") s32 fd_barriern___local_PI_366[1];
__declspec(section ".data") s32 fd_barriern___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_barriern_one_negone_359;
__declspec(section ".data") s32 fd_barriern___local_PIO2_367[1];
__declspec(section ".data") s32 fd_barriern_one_364[1];
BattleUnitKind unit_barriern_19_data_2B8A8;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static BattleUnitKindPart parts[11];
static __declspec(section ".data") StatusVulnerability regist;
static s32 weapon_wakka_attack[48];
static s32 weapon_wawawa_attack[48];
static __declspec(section ".data") s32 entry_barriern_satellite[12];
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[2];
static s32 splineTableIn1_1[15];
static s32 splineTableIn2_1[15];
static s32 splineTableIn2_2[15];
static s32 splineTableIn3_1[15];
static s32 splineTableIn3_2[15];
static s32 splineTableIn3_3[15];
static s32 splineTableIn4_1[15];
static s32 splineTableIn4_2[15];
static s32 splineTableIn4_3[15];
static s32 splineTableIn4_4[15];
static s32 splineTableOut1_1[15];
static s32 splineTableOut2_1[15];
static s32 splineTableOut2_2[15];
static s32 splineTableOut3_1[15];
static s32 splineTableOut3_2[15];
static s32 splineTableOut3_3[15];
static s32 splineTableOut4_1[15];
static s32 splineTableOut4_2[15];
static s32 splineTableOut4_3[15];
static s32 splineTableOut4_4[15];
static s32 init_event[143];
static s32 damage_event[17];
static s32 barriern_dmg_first_attack_pos[19];
static s32 satellite_blur_on[42];
static s32 satellite_blur_off[29];
static s32 unison_phase_event[190];
static s32 attack_event[106];
static s32 recovery_event[69];
static s32 start_avoid[26];
static s32 wakka_attack_common_event_no_hit[305];
static s32 wakka_attack_common_event_hit[211];
static s32 damage_check_event_sub[131];
static s32 wakka_attack_event[255];
static __declspec(section ".data") s32 wawawa_attack_event_satellite_blur[10];
static s32 wawawa_attack_event[548];
static s32 wawawa_attack_event_sub[87];
static __declspec(section ".data") s32 wawawa_attack_event_sub_no_last[10];
static s32 wawawa_attack_event_sub_last[93];
static s32 wait_event[116];

__declspec(section ".data") u64 fd_barriern_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_barriern_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_barriern___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_barriern___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_barriern_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_barriern___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_barriern_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_barriern_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_barriern_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_barriern___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_barriern___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_barriern_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_barriern___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_barriern_one_364[] = {
    1065353216,
};

BattleUnitKind unit_barriern_19_data_2B8A8 = {
    29,
    "btl_un_barriern",
    3,
    0,
    1,
    1,
    12,
    0,
    1,
    70,
    1,
    60,
    9999,
    40,
    40,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    0,
    -40,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    20.0f,
    0.0f,
    0.0f,
    10.0f,
    10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    40.0f,
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
    "SFX_ENM_BARRI_DAMAGED2",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    11,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 12.0f, 0.0f, 0.0f, 22.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {7, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {8, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {9, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {10, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {11, "btl_un_barriern", "c_baria", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10, 10, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static __declspec(section ".data") StatusVulnerability regist = {30, 80, 100, 0, 70, 100, 0, 0, 100, 90, 100, 90, 100, 95, 70, 0, 90, 100, 70, 100, 100, 95};

static s32 weapon_wakka_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_wawawa_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_barriern_satellite[] = {
    (s32)unit_barriern_satellite_19_data_30B08, 16777216, 67108868, 1148846080, 0, 1148846080, 0, 0,
    0, 0, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_1"},
    {39, "D_1"},
    {42, "R_1"},
    {41, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static USER_FUNC(barriern_zanzou) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 0);
}

static USER_FUNC(barriern_zanzou2) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 1);
}

static USER_FUNC(barriern_zanzou3) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    return barriern_zanzou_sub(isFirstCall, unit, scales, 2);
}

static inline f32 intpl_ff(f32 start, f32 end, s32 mode, s32 cur, s32 total) {
    return intplGetValue(start, end, mode, cur, total);
}

static s32 barriern_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 type) {
    f32 start[5];
    f32 end[5];
    f32 x;
    f32 y;
    f32 z;
    BattleUnitPart* part;
    s32 frames;
    f32 scale;
    f32 ofs;
    u8 alphaStart;
    u8 alphaEnd;
    s32 mode = 4;
    s32 i;
    s32 j;

    switch (type) {
        case 0:
            scale = 0.6f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = 0.8f * scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
        case 2:
            scale = 0.8f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scale * scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (type == 2) {
        frames = 36;
    }
    if (isFirstCall) {
        zanzou_count[0] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 0.8f, 0.8f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            part->color.a = alphaEnd;
            part->attributes &= ~0x1000000;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(0.8f, scale, mode, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intpl_ff(start[j], end[j], mode, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(alphaStart, alphaEnd, 0, zanzou_count[0], frames);
    }
    if (zanzou_count[0] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 0.8f, 0.8f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= 0x1000000;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[0]++;
    return EVT_RETURN_BLOCK;
}

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {48, barriern_dmg_first_attack_pos},
    {0, NULL},
};

static s32 splineTableIn1_1[] = {
    1103626240, 0, 0, 1101004800, -1041235968, -1082130432, 1095237632, -1038090240,
    -1082130432, 1084227584, -1041235968, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn2_1[] = {
    1103626240, 0, 0, 1101004800, -1041235968, -1082130432, 1095237632, -1038090240,
    -1082130432, 1084227584, -1041235968, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn2_2[] = {
    -1043857408, 0, 0, -1046478848, 1106247680, -1082130432, -1052246016, 1106247680,
    -1082130432, -1063256064, 1106247680, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn3_1[] = {
    0, 1103626240, 0, 0, 1110704128, -1082130432, 0, 1112014848,
    -1082130432, 0, 1103626240, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn3_2[] = {
    1103626240, -1043857408, 0, 1109393408, -1038090240, -1082130432, 1106247680, -1039400960,
    -1082130432, 1101004800, -1043857408, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn3_3[] = {
    -1043857408, -1043857408, 0, -1038090240, -1038090240, -1082130432, -1041235968, -1039400960,
    -1082130432, -1046478848, -1043857408, -1082130432, -2147483648, 0, -1082130432,
};

static s32 splineTableIn4_1[] = {
    1103626240, 1103626240, 0, 1106247680, 1108082688, -1082130432, 1109393408, 1110704128,
    -1082130432, 1101004800, 1103626240, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn4_2[] = {
    -1043857408, 1103626240, 0, -1041235968, 1108082688, -1082130432, -1038090240, 1110704128,
    -1082130432, -1046478848, 1103626240, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn4_3[] = {
    1103626240, -1043857408, 0, 1106247680, -1039400960, -1082130432, 1109393408, -1036779520,
    -1082130432, 1101004800, -1043857408, -1082130432, 0, 0, -1082130432,
};

static s32 splineTableIn4_4[] = {
    -1043857408, -1043857408, 0, -1041235968, -1039400960, -1082130432, -1038090240, -1036779520,
    -1082130432, -1046478848, -1043857408, -1082130432, -2147483648, 0, -1082130432,
};

static s32 splineTableOut1_1[] = {
    0, 0, -1082130432, -1039400960, -1039400960, -1082130432, -1038090240, 0,
    -1082130432, 1106247680, 1109393408, -1082130432, 1103626240, 0, 0,
};

static s32 splineTableOut2_1[] = {
    0, 0, -1082130432, 1084227584, 1106247680, -1082130432, 1095237632, 1109393408,
    -1082130432, 1101004800, 1106247680, -1082130432, 1103626240, 0, 0,
};

static s32 splineTableOut2_2[] = {
    0, 0, -1082130432, -1063256064, -1041235968, -1082130432, -1052246016, -1038090240,
    -1082130432, -1046478848, -1041235968, -1082130432, -1043857408, 0, 0,
};

static s32 splineTableOut3_1[] = {
    0, 0, -1082130432, 0, 1103626240, -1082130432, 0, 1112014848,
    -1082130432, 0, 1110704128, -1082130432, 0, 1103626240, 0,
};

static s32 splineTableOut3_2[] = {
    0, 0, -1082130432, 1103626240, -1046478848, -1082130432, 1110704128, -1041235968,
    -1082130432, 1106247680, -1043857408, -1082130432, 1103626240, -1043857408, 0,
};

static s32 splineTableOut3_3[] = {
    0, 0, -1082130432, -1043857408, -1046478848, -1082130432, -1036779520, -1041235968,
    -1082130432, -1041235968, -1043857408, -1082130432, -1043857408, -1043857408, 0,
};

static s32 splineTableOut4_1[] = {
    0, 0, -1082130432, 1103626240, 1101004800, -1082130432, 1110704128, 1106247680,
    -1082130432, 1106247680, 1103626240, -1082130432, 1103626240, 1103626240, 0,
};

static s32 splineTableOut4_2[] = {
    0, 0, -1082130432, -1043857408, 1101004800, -1082130432, -1036779520, 1106247680,
    -1082130432, -1041235968, 1103626240, -1082130432, -1043857408, 1103626240, 0,
};

static s32 splineTableOut4_3[] = {
    0, 0, -1082130432, 1103626240, -1046478848, -1082130432, 1110704128, -1041235968,
    -1082130432, 1106247680, -1043857408, -1082130432, 1103626240, -1043857408, 0,
};

static s32 splineTableOut4_4[] = {
    0, 0, -1082130432, -1043857408, -1046478848, -1082130432, -1036779520, -1041235968,
    -1082130432, -1041235968, -1043857408, -1082130432, -1043857408, -1043857408, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetPartsScale, -2, 1, FLOAT(0.7998047f), FLOAT(0.7998047f), FLOAT(1.0f))
    CALL(btlevtcmd_OnUnitFlag, -2, 3145728)
    SET_VALUE(LW(0), 4)
    LOOP(2)
        CALL(btlevtcmd_SetUnitWork, -2, LW(0), -1)
        ADD(LW(0), 1)
    END_LOOP
    SET_VALUE(LW(6), 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(7))
    LABEL(0)
    IF_INT_LESS(LW(6), LW(7))
        CALL(btlevtcmd_GetUnitId, -2, LW(5))
        SET_VALUE(LW(8), LW(6))
        ADD(LW(8), 4)
        CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_barriern_satellite), 0)
        CALL(btlevtcmd_SetUnitWork, -2, LW(8), LW(3))
        CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(5))
        CALL(btlevtcmd_SetUnitWork, LW(3), 1, 1)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(battleGetBarriernSatelliteInitPos, -2, LW(7), LW(6), LW(10), LW(11), LW(12))
        ADD(LW(0), LW(10))
        ADD(LW(1), LW(11))
        ADD(LW(2), LW(12))
        CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetScale, LW(3), FLOAT(0.7998047f), FLOAT(0.7998047f), FLOAT(1.0f))
        ADD(LW(6), 1)
        GOTO(0)
    END_IF
    LABEL(10)
    CALL(outSplineTableSet, -2, LW(7))
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRGB, -2, 1, 255, 255, 255)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static EVT_BEGIN(barriern_dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 20)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static EVT_BEGIN(satellite_blur_on)
    SET_VALUE(LW(2), 4)
    LOOP(2)
        CALL(btlevtcmd_GetUnitWork, -2, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_SetPartsBlur, LW(3), LW(4), 255, 255, 255, 255, 255, 255, 255, 100, 0)
            CALL(btlevtcmd_OnPartsAttribute, LW(3), LW(4), 67108864)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(satellite_blur_off)
    SET_VALUE(LW(2), 4)
    LOOP(2)
        CALL(btlevtcmd_GetUnitWork, -2, LW(2), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
            CALL(btlevtcmd_OffPartsAttribute, LW(3), LW(4), 67108864)
        END_IF
        ADD(LW(2), 1)
    END_LOOP
    RETURN
EVT_END()

static USER_FUNC(barriern_satellite_zanzou) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 n = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnit* sat;
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    sat = BattleGetUnitPtr(wp, unit->work[4 + n]);
    return barriern_satellite_zanzou_sub(isFirstCall, sat, scales, n, 0);
}

static USER_FUNC(barriern_satellite_zanzou2) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 n = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, id);
    BattleUnit* sat;
    f32 scales[5] = {1.7f, 2.4f, 3.1f, 3.8f, 4.5f};

    sat = BattleGetUnitPtr(wp, unit->work[4 + n]);
    return barriern_satellite_zanzou_sub(isFirstCall, sat, scales, n, 1);
}

static s32 barriern_satellite_zanzou_sub(BOOL isFirstCall, BattleUnit* unit, f32* scales, s32 n, s32 type) {
    f32 start[5];
    f32 end[5];
    f32 x;
    f32 y;
    f32 z;
    BattleUnitPart* part;
    s32 frames;
    f32 scale;
    f32 ofs;
    u8 alphaStart;
    u8 alphaEnd;
    s32 mode = 4;
    s32 i;
    s32 j;

    switch (type) {
        case 0:
            scale = 0.6f;
            frames = 36;
            for (i = 0; i < 5; i++) {
                start[i] = 0.8f * scales[i];
                end[i] = scale;
            }
            ofs = 0.5f;
            alphaStart = 0;
            alphaEnd = 64;
            mode = 4;
            break;
        case 1:
            scale = 0.8f;
            frames = 8;
            for (i = 0; i < 5; i++) {
                start[i] = scale;
                end[i] = scale * scales[i];
            }
            ofs = -0.5f;
            alphaStart = 64;
            alphaEnd = 0;
            mode = 1;
            break;
    }
    if (isFirstCall) {
        zanzou_count[(s32)(n + 1)] = 0;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetPartsScale(BtlUnit_GetPartsPtr(unit, 1), 0.8f, 0.8f, 1.0f);
        for (i = 2, j = 0; i <= 6; i++, j++) {
            part = BtlUnit_GetPartsPtr(unit, i);
            BtlUnit_SetPartsPos(part, x, y, i * ofs + z);
            BtlUnit_SetPartsScale(part, start[j], start[j], 1.0f);
            BtlUnit_SetPartsRotate(part, 0.0f, 0.0f, 0.0f);
            part->color.a = alphaStart;
            BtlUnit_SetAnim(part, "Z_2");
            part->attributes &= ~0x1000000;
        }
    }
    part = BtlUnit_GetPartsPtr(unit, 1);
    {
        f32 s = intplGetValue(0.8f, scale, 4, zanzou_count[0], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
    }
    for (i = 2, j = 0; i <= 6; i++, j++) {
        f32 s;

        part = BtlUnit_GetPartsPtr(unit, i);
        s = intplGetValue(start[j], end[j], mode, zanzou_count[(s32)(n + 1)], frames);
        BtlUnit_SetPartsScale(part, s, s, 1.0f);
        part->color.a = intplGetValue(alphaStart, alphaEnd, 0, zanzou_count[(s32)(n + 1)], frames);
    }
    if (zanzou_count[(s32)(n + 1)] >= frames) {
        part = BtlUnit_GetPartsPtr(unit, 1);
        BtlUnit_SetPartsScale(part, 0.8f, 0.8f, 1.0f);
        part->color.a = 255;
        for (i = 2; i <= 6; i++) {
            BtlUnit_GetPartsPtr(unit, i)->attributes |= 0x1000000;
        }
        return EVT_RETURN_DONE;
    }
    zanzou_count[(s32)(n + 1)]++;
    return EVT_RETURN_BLOCK;
}

static s32 unison_phase_event[] = {
    131163, (s32)btlevtcmd_StopWaitEvent, -2, 196699, (s32)btlevtcmd_CheckPhase, -30000000, 67108865, 131096,
    -30000000, 0, 65540, 99, 33, 131163, (s32)btlevtcmd_get_turn, -30000000,
    131100, -30000000, 1, 65540, 99, 33, 196699, (s32)btlevtcmd_CheckActStatus,
    -2, -30000000, 131096, -30000000, 0, 65540, 99, 33,
    196699, (s32)evt_sub_random, 10, -30000000, 65545, -30000000, 131122, -30000000,
    0, 131122, -29999999, 4, 65541, 2, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, -29999999, -29999997, 131097, -29999997, -1, 131125, -30000000,
    1, 33, 131125, -29999999, 1, 6, 131101, -30000000,
    2, 65540, 99, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK9",
    -250000000, 0, -250000000, 131163, (s32)barriern_zanzou3, -2, 65630, (s32)satellite_blur_on,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -29999999, 131101, -29999999, 1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_SPLIT1", -250000000, 0, -250000000, 33,
    196699, (s32)barriernSatelliteToInside, -2, -29999999, 65630, (s32)satellite_blur_off, 196699, (s32)btlevtcmd_GetUnitId,
    -2, -29999996, 131122, -29999999, 4, 131122, -29999995, 0,
    65541, 2, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999999, -29999998, 131096,
    -29999998, -1, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_barriern_satellite, 0, 327771,
    (s32)btlevtcmd_AddPos, -29999997, 0, 0, -1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    -29999999, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999996, 131125,
    -30000000, 1, 131125, -29999995, 1, 131101, -29999995, 1,
    7, 33, 33, 131125, -29999999, 1, 6, 65545,
    5, 65630, (s32)satellite_blur_on, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_SPLIT2", -250000000,
    0, -250000000, 196699, (s32)barriernSatelliteToOutside, -2, -30000000, 65545, 60,
    65630, (s32)satellite_blur_off, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, -30000000, 65539,
    99, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetRGB, -2, 1, 255, 255, 255)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(wakka_attack_event))
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(_check_satellite)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 4)
    LOOP(2)
        CALL(btlevtcmd_GetUnitWork, -2, LW(1), LW(3))
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_CheckActStatus, LW(3), LW(2))
            IF_INT_NOT_EQUAL(LW(2), 0)
                CALL(btlevtcmd_CheckStatus, LW(3), 5, LW(2))
                IF_INT_EQUAL(LW(2), 0)
                    ADD(LW(0), 1)
                END_IF
            END_IF
        END_IF
        ADD(LW(1), 1)
    END_LOOP
    IF_INT_EQUAL(LW(0), 2)
        CALL_CHILD(PTR(wawawa_attack_event))
        ELSE
        SET_VALUE(LW(0), 100)
        ADD(LW(0), 0)
        SUBTRACT(LW(0), 1)
        CALL(evt_sub_random, LW(0), LW(1))
        IF_INT_LESS(LW(1), 100)
            CALL_CHILD(PTR(wakka_attack_event))
            ELSE
            CALL_CHILD(PTR(recovery_event))
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(recovery_event)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_zoom, 0, 300)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_3"))
    WAIT_FRAMES(120)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_RecoverHp, -2, 1, 0)
    CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
    ADD(LW(6), 30)
    ADD(LW(7), 10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(5), LW(6), LW(7), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(30)
    RETURN
EVT_END()

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

static s32 wakka_attack_common_event_no_hit[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 1, -29999994, 131096, -29999994, 0,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 67108864, 32, 786523, (s32)btlevtcmd_SetPartsBlur,
    -2, -29999985, 255, 255, 255, 255, 255, 255,
    255, 100, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, -29999985, 67108864,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, -29999985, (s32)"Z_3", 327771, (s32)btlevtcmd_GetPos,
    -29999988, -29999994, -29999993, -29999992, 131125, -29999992, 1, 393307,
    (s32)btlevtcmd_SetPartsPos, -2, -29999985, -29999994, -29999993, -29999992, 327771, (s32)btlevtcmd_CheckPartsAttribute,
    -2, -29999985, 16777216, -30000000, 131097, -30000000, 0, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, -29999985, 16777216, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"A_5", 110, 65541, 0, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -30000000, 131096, -30000000, -1, 393307, (s32)btlevtcmd_GetPartsPos, -2, -29999985,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994,
    -29999993, -29999992, 131100, -30000000, -29999994, 65630, (s32)start_avoid, 7,
    33, 32, 393307, (s32)btlevtcmd_GetPartsPos, -2, -29999985, -30000000, -29999999,
    -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993, -29999992,
    131101, -30000000, -29999994, 65630, (s32)start_avoid, 7, 33, 33,
    65545, 1, 6, 112, 262235, (s32)btlevtcmd_GetUnitWork, -2, 1,
    -29999994, 131096, -29999994, 0, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -29999994, -29999993, -29999992, 262235, (s32)btlevtcmd_GetStageSize, -29999994, -250000000, -250000000,
    131127, -29999994, 1, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127,
    -29999994, -30000000, 131126, -29999993, 5, 393307, (s32)btlevtcmd_SetPartsScale, -2,
    -29999985, 1, 0, 1, 110, 65541, 0, 65541,
    10, 393307, (s32)btlevtcmd_AddPartsScale, -2, -29999985, 0, -229999872, 0,
    65545, 1, 6, 65541, 10, 393307, (s32)btlevtcmd_AddPartsScale, -2,
    -29999985, 0, -230000128, 0, 65545, 1, 6, 6,
    112, 393307, (s32)btlevtcmd_JumpPartsSetting, -2, -29999985, 0, 4, 0,
    524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999985, -29999994, -29999993, -29999992, 0,
    -1, 32, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993,
    -29999992, 262235, (s32)btlevtcmd_GetStageSize, -29999994, -250000000, -250000000, 131127, -29999994,
    1, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127, -29999994, -30000000,
    131126, -29999993, 5, 393307, (s32)btlevtcmd_SetPartsScale, -2, -29999985, 1,
    0, 1, 110, 65541, 0, 65541, 5, 393307,
    (s32)btlevtcmd_AddPartsScale, -2, -29999985, 0, -229999744, 0, 65545, 1,
    6, 65541, 5, 393307, (s32)btlevtcmd_AddPartsScale, -2, -29999985, 0,
    -230000256, 0, 65545, 1, 6, 6, 112, 393307,
    (s32)btlevtcmd_JumpPartsSetting, -2, -29999985, 0, 7, 0, 524379, (s32)btlevtcmd_JumpPartsPosition,
    -2, -29999985, -29999994, -29999993, -29999992, 0, -1, 393307,
    (s32)btlevtcmd_SetPartsPos, -2, -29999985, 0, -1000, 0, 33, 2,
    1,
};

static EVT_BEGIN(wakka_attack_common_event_hit)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_OffPartsAttribute, -2, LW(15), 67108864)
        ELSE
        CALL(btlevtcmd_SetPartsBlur, -2, LW(15), 255, 255, 255, 255, 255, 255, 255, 100, 0)
        CALL(btlevtcmd_OnPartsAttribute, -2, LW(15), 67108864)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, -2, LW(15), STRING("Z_3"))
    CALL(btlevtcmd_GetPos, LW(12), LW(6), LW(7), LW(8))
    ADD(LW(8), 1)
    CALL(btlevtcmd_SetPartsPos, -2, LW(15), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_CheckPartsAttribute, -2, LW(15), 16777216, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OffPartsAttribute, -2, LW(15), 16777216)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_5"))
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(6))
    IF_INT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_SetPartsScale, -2, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, -2, LW(15), 0, FLOAT(0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(10)
                    CALL(btlevtcmd_AddPartsScale, -2, LW(15), 0, FLOAT(-0.125f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_JumpPartsSetting, -2, LW(15), 0, 4, 0)
        CALL(btlevtcmd_JumpPartsPosition, -2, LW(15), LW(6), LW(7), LW(8), 0, -1)
        ELSE
        CALL(btlevtcmd_SetPartsScale, -2, LW(15), 1, 0, 1)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, -2, LW(15), 0, FLOAT(0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
                LOOP(5)
                    CALL(btlevtcmd_AddPartsScale, -2, LW(15), 0, FLOAT(-0.25f), 0)
                    WAIT_FRAMES(1)
                END_LOOP
            END_LOOP
        END_SIBLING_EVENT
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
        CALL(btlevtcmd_JumpPartsSetting, -2, LW(15), 0, 7, 0)
        CALL(btlevtcmd_JumpPartsPosition, -2, LW(15), LW(6), LW(7), LW(8), 0, -1)
        CALL(btlevtcmd_SetPartsPos, -2, LW(15), 0, -1000, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_event_sub)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 0, LW(5))
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
    CALL_CHILD(PTR(wakka_attack_common_event_no_hit))
    GOTO(98)
    LABEL(91)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(14), 5)
    LOOP(0)
        CALL(btlevtcmd_GetPartsWork, -2, 1, LW(13), LW(5))
        CALL(btlevtcmd_GetPartsWork, -2, 1, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                ADD(LW(13), 10)
                CALL(btlevtcmd_SetPartsWork, -2, 1, LW(13), 1)
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
    END_LOOP
    CALL_CHILD(PTR(wakka_attack_common_event_hit))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    IF_INT_EQUAL(LW(10), 1)
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
        ELSE
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 0, LW(5))
    END_IF
    GOTO(98)
    LABEL(98)
    CALL(btlevtcmd_SetPartsPos, -2, LW(15), 0, -1000, 0)
    RETURN
EVT_END()

static s32 wakka_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_wakka_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_wakka_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    1, 0, -29999997, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 5,
    -29999996, 131122, -29999991, (s32)weapon_wakka_attack, 131122, -29999990, 1, 131122,
    -29999988, -2, 131122, -29999985, 7, 196699, (s32)evt_btl_camera_set_mode, 0,
    7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 250, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_wakka_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_wakka_attack, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -29999997, -29999996, 16, -29999986, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999986,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BARRI_ATTACK2", -250000000, 0, -250000000, 131163, (s32)barriern_zanzou, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK9", -250000000, 0, -250000000, 131163, (s32)barriern_zanzou2,
    -2, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 131122,
    -30000000, 6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999986, 131127, -30000000,
    -29999986, 65541, 10, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, -30000000, 0, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1",
    65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 65545,
    30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3", 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_4", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK3", -250000000, 0, -250000000,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK7", -250000000, 0, -30000000, 327771,
    (s32)btlevtcmd_SetPartsWork, -2, 7, 15, -30000000, 65630, (s32)damage_check_event_sub, 327771,
    (s32)btlevtcmd_GetPartsWork, -2, 7, 15, -30000000, 131163, (s32)evt_snd_sfxoff, -30000000,
    131122, -30000000, -6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999986, 131127,
    -30000000, -29999986, 65541, 10, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, -30000000, 0, 6, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wawawa_attack_event_satellite_blur)
    CALL(barriern_satellite_zanzou, -2, LW(0))
    CALL(barriern_satellite_zanzou2, -2, LW(0))
    RETURN
EVT_END()

static s32 wawawa_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_wawawa_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_wawawa_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    2, 0, 720987, (s32)barriern_wawawa_set_target, -30000000, -29999999, -29999998, -29999997,
    -29999996, -29999995, -29999994, -29999993, -29999992, -29999991, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 0, -30000000, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    1, -29999998, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 2, -29999996,
    327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 3, -29999994, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 4, -29999992, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    5, -29999999, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 6, -29999997,
    327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 7, -29999995, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 8, -29999993, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    9, -29999991, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 10, 0,
    327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 11, 0, 327771, (s32)btlevtcmd_SetPartsWork,
    -2, 1, 12, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1,
    13, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 1, 14, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_wawawa_attack, 131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_wawawa_attack, 327771, (s32)btlevtcmd_GetPartsWork, -2,
    1, 0, -29999997, 327771, (s32)btlevtcmd_GetPartsWork, -2, 1, 5,
    -29999996, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BARRI_ATTACK5", -250000000, 0, -250000000, 131122, -30000000, 0, 65541,
    2, 65628, (s32)wawawa_attack_event_satellite_blur, 131125, -30000000, 1, 65545, 10,
    6, 131163, (s32)barriern_zanzou, -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK10",
    -250000000, 0, -250000000, 131163, (s32)barriern_zanzou2, -2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_BARRI_ATTACK6", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"F_1", 65545, 20, 131122, -29999989, 4, 65541,
    0, 131101, -29999989, 6, 7, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, -29999989, -29999988, 196699, (s32)btlevtcmd_GetBodyId, -29999988, -29999987, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999988, -29999987, (s32)"F_2", 131125, -29999989, 1, 6,
    65545, 20, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    131122, -29999989, 4, 65541, 0, 131101, -29999989, 6,
    7, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999988, 327771,
    (s32)btlevtcmd_SetRotate, -29999988, 0, 0, 0, 131125, -29999989, 1,
    6, 131122, -30000000, 6, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999986,
    131127, -30000000, -29999986, 65541, 10, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, -30000000, 0, 131122, -29999989, 4,
    65541, 0, 131101, -29999989, 6, 7, 33, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999988, 327771, (s32)btlevtcmd_AddRotate, -29999988, 0,
    -30000000, 0, 131125, -29999989, 1, 6, 6, 131122,
    -29999989, 4, 65541, 0, 131101, -29999989, 6, 7,
    33, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999988, 196699, (s32)btlevtcmd_GetBodyId,
    -29999988, -29999987, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, -29999987, (s32)"S_2", 131125,
    -29999989, 1, 6, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1", 65545,
    30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2", 65545, 30,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_3", 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 65545, 10, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_4",
    131122, -29999988, -2, 131122, -29999987, 0, 131122, -29999986,
    5, 131122, -29999985, 7, 65628, (s32)wawawa_attack_event_sub, 65545, 30,
    131122, -29999989, 4, 131125, -29999987, 1, 131125, -29999986,
    1, 131125, -29999985, 1, 65541, 0, 131101, -29999989,
    6, 7, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999988,
    65628, (s32)wawawa_attack_event_sub, 65545, 20, 131125, -29999989, 1, 131125,
    -29999987, 1, 131125, -29999986, 1, 131125, -29999985, 1,
    6, 65541, 0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000,
    131101, -30000000, 3, 7, 33, 65545, 1, 6,
    65545, 10, 65627, (s32)_check_satellite, 131122, -30000000, -6, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999986, 131127, -30000000, -29999986, 65541, 10,
    65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000, 0,
    131122, -29999989, 4, 65541, 0, 131101, -29999989, 6,
    7, 33, 262235, (s32)btlevtcmd_GetUnitWork, -2, -29999989, -29999988, 327771,
    (s32)btlevtcmd_AddRotate, -29999988, 0, -30000000, 0, 131125, -29999989, 1,
    6, 6, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 wawawa_attack_event_sub[] = {
    327771, (s32)btlevtcmd_GetPartsWork, -2, 1, -29999987, -29999997, 327771, (s32)btlevtcmd_GetPartsWork,
    -2, 1, -29999986, -29999996, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK4",
    -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BARRI_ATTACK8", -250000000,
    0, -30000000, 327771, (s32)btlevtcmd_SetPartsWork, -2, -29999985, 15, -30000000,
    65541, 0, 131101, -29999987, 1, 65630, (s32)wawawa_attack_event_sub_last, 7,
    33, 131125, -29999987, 1, 131125, -29999986, 1, 327771,
    (s32)btlevtcmd_GetPartsWork, -2, 1, -29999987, -29999995, 327771, (s32)btlevtcmd_GetPartsWork, -2,
    1, -29999986, -29999994, 131096, -29999997, -29999995, 131096, -29999996,
    -29999994, 65630, (s32)wawawa_attack_event_sub_no_last, 7, 33, 33, 6, 262235,
    (s32)btlevtcmd_AddUnitWork, -2, 2, 1, 327771, (s32)btlevtcmd_GetPartsWork, -2, -29999985,
    15, -30000000, 131163, (s32)evt_snd_sfxoff, -30000000, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wawawa_attack_event_sub_no_last)
    SET_VALUE(LW(9), PTR(weapon_wawawa_attack))
    SET_VALUE(LW(10), 0)
    CALL_CHILD(PTR(damage_check_event_sub))
    RETURN
EVT_END()

static EVT_BEGIN(wawawa_attack_event_sub_last)
    SET_VALUE(LW(13), 0)
    SET_VALUE(LW(14), 5)
    LOOP(0)
        CALL(btlevtcmd_GetPartsWork, -2, 1, LW(13), LW(5))
        CALL(btlevtcmd_GetPartsWork, -2, 1, LW(14), LW(6))
        IF_INT_EQUAL(LW(3), LW(5))
            IF_INT_EQUAL(LW(4), LW(6))
                ADD(LW(13), 10)
                CALL(btlevtcmd_GetPartsWork, -2, 1, LW(13), LW(0))
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(13), 1)
        ADD(LW(14), 1)
    END_LOOP
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(wakka_attack_common_event_hit))
        CALL(btlevtcmd_ResultACDefence, LW(3), PTR(weapon_wawawa_attack))
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), PTR(weapon_wawawa_attack), 256, LW(5))
        CALL(btlevtcmd_SetPartsPos, -2, LW(15), 0, -1000, 0)
        WAIT_FRAMES(20)
        CALL(btlevtcmd_OffPartsAttribute, -2, LW(15), 67108864)
        CALL(btlevtcmd_OnPartsAttribute, -2, LW(15), 16777216)
        ELSE
        SET_VALUE(LW(9), PTR(weapon_wawawa_attack))
        SET_VALUE(LW(10), 1)
        CALL_CHILD(PTR(damage_check_event_sub))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(_check_satellite)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    SET_VALUE(LW(11), 4)
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(11), 6)
            BREAK_LOOP
        END_IF
        CALL(btlevtcmd_GetUnitWork, -2, LW(11), LW(12))
        IF_INT_NOT_EQUAL(LW(12), -1)
            CALL(btlevtcmd_SetUnitWork, LW(12), 1, 1)
        END_IF
        ADD(LW(11), 1)
    END_LOOP
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(1), 255)
        SET_VALUE(LW(2), 255)
        SET_VALUE(LW(3), 255)
        SET_VALUE(LW(4), -8)
        LABEL(0)
        CALL(_check_satellite, LW(0))
        WAIT_FRAMES(1)
        GOTO(0)
    END_SIBLING_EVENT
    LABEL(1)
    CALL(evt_sub_random, 120, LW(0))
    ADD(LW(0), 30)
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckStatus, -2, 5, LW(0))
        CALL(btlevtcmd_CheckStatus, -2, 3, LW(1))
        CALL(btlevtcmd_CheckStatus, -2, 4, LW(2))
        OR(LW(0), LW(1))
        OR(LW(0), LW(2))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_3"))
            WAIT_FRAMES(180)
            CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
        END_IF
    END_IF
    GOTO(1)
    RETURN
EVT_END()

static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table) {
    BarriernSpline* sp;

    if (unit->work[4 + n] == -1) {
        return FALSE;
    }
    sp = __memAlloc(HEAP_BATTLE, sizeof(BarriernSpline));
    unit->work[10 + n] = (s32)sp;
    sp->n = 5;
    sp->table = table;
    sp->count = 0;
    spline_maketable(5, sp->table, sp->a, sp->b);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]), 1)->work[2] = (s32)table;
    return TRUE;
}

static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n) {
    BarriernSpline* sp;
    BattleUnit* sat;
    Vec upos;
    Vec pos;

    if (unit->work[4 + n] == -1) {
        return FALSE;
    }
    sp = (BarriernSpline*)unit->work[10 + n];
    if (sp == NULL) {
        return FALSE;
    }
    if (sp->count >= 60) {
        if (sp != NULL) {
            __memFree(HEAP_BATTLE, sp);
            unit->work[10 + n] = 0;
        }
        return FALSE;
    }
    spline_getvalue(intplGetValue(0.0f, 1.0f, 4, sp->count, 60), &pos, sp->n, sp->table, sp->a, sp->b);
    sat = BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]);
    if (sat == NULL) {
        return FALSE;
    }
    BtlUnit_GetPos(unit, &upos.x, &upos.y, &upos.z);
    BtlUnit_SetPos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    BtlUnit_SetHomePos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    sp->count++;
    return TRUE;
}

static USER_FUNC(barriernSatelliteToInside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        for (i = 0; i < 4; i++) {
            if (unit->work[4 + i] != -1) {
                s32 table = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + i]), 1)->work[2];

                if (table == (s32)splineTableOut1_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn1_1);
                }
                if (table == (s32)splineTableOut2_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_1);
                }
                if (table == (s32)splineTableOut2_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_2);
                }
                if (table == (s32)splineTableOut3_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_1);
                }
                if (table == (s32)splineTableOut3_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_2);
                }
                if (table == (s32)splineTableOut3_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_3);
                }
                if (table == (s32)splineTableOut4_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_1);
                }
                if (table == (s32)splineTableOut4_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_2);
                }
                if (table == (s32)splineTableOut4_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_3);
                }
                if (table == (s32)splineTableOut4_4) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_4);
                }
            }
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (barriernSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

static USER_FUNC(barriernSatelliteToOutside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        switch (num) {
        case 1:
            i = 0;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut1_1) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 2:
            i = 0;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut2_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut2_2) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 3:
            i = 0;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut3_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut3_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut3_3) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 4:
            i = 0;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut4_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut4_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut4_3) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (barriernSatelliteTo_Init(unit, i, splineTableOut4_4) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        default:
            return EVT_RETURN_DONE;
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (barriernSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

static USER_FUNC(outSplineTableSet) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    switch (evtGetValue(event, args[1])) {
        case 1:
            outSplineTableSet_Sub(unit, 0, splineTableOut1_1);
            break;
        case 2:
            outSplineTableSet_Sub(unit, 0, splineTableOut2_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut2_2);
            break;
        case 3:
            outSplineTableSet_Sub(unit, 0, splineTableOut3_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut3_2);
            outSplineTableSet_Sub(unit, 2, splineTableOut3_3);
            break;
        case 4:
            outSplineTableSet_Sub(unit, 0, splineTableOut4_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut4_2);
            outSplineTableSet_Sub(unit, 2, splineTableOut4_3);
            outSplineTableSet_Sub(unit, 3, splineTableOut4_4);
            break;
    }
    return EVT_RETURN_DONE;
}

static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table) {
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]), 1)->work[2] = (s32)table;
}

static USER_FUNC(barriern_wawawa_set_target) {
    s32* args = event->args;
    s32 unitIdx[10];
    s32 partIdx[10];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    barriern_wawawa_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        barriern_wawawa_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 5; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}

static void barriern_wawawa_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}

static USER_FUNC(_check_satellite) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    s32* args = event->args;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BOOL alive;
    s32 j;

    alive = FALSE;
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    for (i = 4; i < 6; i++) {
        if (unit->work[i] != -1) {
            if (BattleGetUnitPtr(_battleWorkPointer, unit->work[i]) != NULL) {
                alive = TRUE;
            } else {
                unit->work[i] = -1;
            }
        }
    }
    if (!alive) {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (part->attributes & 0x20000000) {
            effDelete((EffectEntry*)unit->work[3]);
            unit->work[3] = 0;
            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER_BREAK1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &x, &y, &z);
            for (j = 0; j < 20; j++) {
                s32 w = BtlUnit_GetWidth(unit) + 15;
                s32 h = BtlUnit_GetHeight(unit) + 15;
                s32 dx = irand(w) - w / 2;
                s32 dy = irand(h) - h / 2;

                effGlassN64Entry(2, 60, x + dx, y + dy, z, 1.0f);
            }
        }
        part->attributes &= ~0x20000000;
        evtSetValue(event, args[0], 0);
    } else {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (!(part->attributes & 0x20000000)) {
            f32 px;
            f32 py;
            f32 pz;

            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &px, &py, &pz);
            unit->work[3] = (s32)effSyuryouEntry(1, 1000, 0.0f, -1000.0f, 0.0f);
        }
        part->attributes |= 0x20000000;
        evtSetValue(event, args[0], 1);
        if (unit->work[3] != 0) {
            f32* ud = ((EffectEntry*)unit->work[3])->userdata;

            BtlUnit_GetPos(unit, &x, &y, &z);
            ud[1] = x;
            ud[2] = y - 0.8f * (32.0f * unit->mSizeMultiplier);
            ud[3] = 10.0f + z;
            ud[4] = 1.8f * (0.8f * unit->mSizeMultiplier);
        }
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(battleGetBarriernSatelliteInitPos) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 num;
    s32 index;
    s32 id;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 j;
    static const Vec VecData[] = {
        // 1 satellite
        {25.0f, 0.0f, 0.0f},
        // 2 satellites
        {25.0f, 0.0f, 0.0f},
        {-25.0f, 0.0f, 0.0f},
        // 3 satellites
        {0.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
        // 4 satellites
        {25.0f, 25.0f, 0.0f},
        {-25.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
    };
    const Vec* p;
    BattleWork* wp = _battleWorkPointer;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    num = evtGetValue(event, args[1]);
    index = evtGetValue(event, args[2]);
    x = args[3];
    y = args[4];
    z = args[5];
    p = VecData;
    for (i = 0; i < num; i++) {
        for (j = 0; j < i; j++) {
            p++;
        }
    }
    for (j = 0; j < index; j++) {
        p++;
    }
    evtSetValue(event, x, (s32)(p->x * unit->faceDirection));
    evtSetValue(event, y, (s32)p->y);
    evtSetValue(event, z, (s32)p->z);
    return EVT_RETURN_DONE;
}
