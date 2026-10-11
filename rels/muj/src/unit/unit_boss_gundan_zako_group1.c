#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_stage_object.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/dispdrv.h"

typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; ZakoGun* zako; } ZakoGunWork;
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
extern ZakoGun* zakogun;
extern ZakoGunWork* work_20_bss_6C;
ExtPose* extGetPosePtr(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
void zakogun_ext_main1(void);
void zakogun_ext_main2(void);
void zakogun_ext_main3(void);
void zakogun_ext_disp(CameraId camera, void* param);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_set_position);
USER_FUNC(zakogun_attack1);
USER_FUNC(zakogun_damage_pose);
USER_FUNC(zakogun_damage_pose_cancel);
USER_FUNC(zakogun_end_sukima);
USER_FUNC(zakogun_set_target_id);
USER_FUNC(zakogun_start_sukima);
USER_FUNC(zakogun_escape1);
USER_FUNC(zakogun_dead1);
void zakogun_ext_main1(void);
void zakogun_ext_init123_common(ExtPose* pose, s32 i);
USER_FUNC(zakogun_ext_init1);
s32 zakogun_get_kanbu_id(void);
USER_FUNC(zakogun_get_kanbu_id_evtcmd);
void zakogun_ext_disp(CameraId camera, void* param);
void zakogun_ext_main(void);
void zakogun_ext_init(void);
BattleUnit* zakogun_get_ptr(void);
void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_eff[];
extern s32 evt_sub_random[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_gundan_zako_group1_negone_one_374;
__declspec(section ".data") s32 fd_boss_gundan_zako_group1_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_gundan_zako_group1_one_negone_373;
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1_one_381[1];
__declspec(section ".data") u64 fd_boss_gundan_zako_group1_negone_one_360;
__declspec(section ".data") s32 fd_boss_gundan_zako_group1_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_gundan_zako_group1_one_negone_359;
__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_gundan_zako_group1_one_364[1];
BattleUnitKind unit_boss_gundan_zako_group1;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
static __declspec(section ".data") BattleDataEntry data_table[4];
static BattleUnitKindPart parts[1];
s32 weapon_gundan_zako_group1_attack[48];
static s32 init_event[44];
static s32 damage_event[134];
s32 damage_event_kaiten_hammer[30];
static s32 dead_event[138];
static s32 attack_event[85];
static s32 hit_check_event[95];
static __declspec(section ".data") s32 wait_event[6];
s32 zakogun_ext_entry_data[147];
s32 zakogun_entry[19];

USER_FUNC(zakogun_set_target_id) {
    work_20_bss_6C->targetId = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div) {
    zako->poseBase = base;
    zako->poseNum = num;
    zako->poseDiv = div;
    zako->poseCount = 0;
}

USER_FUNC(zakogun_damage_pose) {
    s32 i;
    ZakoGun* zako;

    if (isFirstCall) {
        for (i = 0; i < 500; i++) {
            zako = &zakogun[i];
            if (zako != NULL) {
                switch (work_20_bss_6C->flag) {
                    case 0:
                    case 2:
                        zakogun_set_pose(zako, 0x21, 3, 3);
                        break;
                    case 1:
                        zakogun_set_pose(zako, 0x2d, 3, 2);
                        break;
                }
            }
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(zakogun_damage_pose_cancel) {
    s32 i;
    ZakoGun* zako;

    if (isFirstCall) {
        for (i = 0; i < 500; i++) {
            zako = &zakogun[i];
            if (zako != NULL) {
                switch (work_20_bss_6C->flag) {
                    case 0:
                        zakogun_set_pose(zako, 0x15, 1, 1);
                        break;
                    case 1:
                        zakogun_set_pose(zako, 0x25, 4, 6);
                        break;
                    case 2:
                        zakogun_set_pose(zako, 0, 20, 2);
                        break;
                }
            }
        }
    }
    return EVT_RETURN_DONE;
}

BattleUnit* zakogun_get_ptr(void) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 i;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && (unit->initialKind == 0x64 || unit->initialKind == 0x65 || unit->initialKind == 0x66)) {
            return unit;
        }
    }
    return NULL;
}

__declspec(section ".data") u64 fd_boss_gundan_zako_group1_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gundan_zako_group1_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gundan_zako_group1_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_gundan_zako_group1_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_gundan_zako_group1_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_gundan_zako_group1_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_gundan_zako_group1___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_gundan_zako_group1_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_gundan_zako_group1 = {
    100,
    "btl_un_gundan_zako_group1",
    6,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    9999,
    50,
    50,
    0,
    50,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
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
    25.0f,
    32.5f,
    0.0f,
    -4.0f,
    25.0f,
    0.0f,
    50.0f,
    50.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_TEAM_3RD_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x200000,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static __declspec(section ".data") PoseTableEntry pose_table[] = {
    {28, "Z_1"},
    {31, "Z_1"},
    {39, "Z_1"},
    {69, "Z_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {18, damage_event_kaiten_hammer},
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gundan_zako_group1", "c_zako_n", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3000009, 0, pose_table},
};

s32 weapon_gundan_zako_group1_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 4231, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), LW(1), 15)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), 15)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamage, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        SET_VALUE(LW(15), 1)
        ELSE
        SET_VALUE(LW(15), 0)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 1, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 3, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 5, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 9, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 2, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 4, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 8, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 11, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 15, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 20, LW(14))
    OR(LW(15), LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 0, LW(14))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(zakogun_damage_pose)
        CALL(zakogun_start_sukima, 0)
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(zakogun_damage_pose_cancel)
    CALL(zakogun_end_sukima)
    RETURN
EVT_END()

EVT_BEGIN(damage_event_kaiten_hammer)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_GetDamage, -2, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(zakogun_damage_pose)
        CALL(zakogun_start_sukima, 1)
        WAIT_FRAMES(80)
        CALL(zakogun_damage_pose_cancel)
        CALL(zakogun_end_sukima)
        ELSE
        WAIT_FRAMES(80)
    END_IF
    RETURN
EVT_END()

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 65627, (s32)zakogun_dead1, 65545,
    36, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_1", -250000000, 0, -250000000,
    65545, 48, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000,
    0, -250000000, 65541, 10, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)evt_sub_random, 100, -29999997, 131126, -29999997,
    50, 131125, -30000000, -29999997, 196699, (s32)evt_sub_random, 30, -29999997,
    131125, -29999999, -29999997, 131122, -29999998, 75, 983131, (s32)evt_eff,
    0, (s32)"kemuri_test", 4, -30000000, -29999999, -29999998, -229999181, 0,
    0, 0, 0, 0, 0, 0, 65545, 1,
    6, 112, 196699, (s32)btlevtcmd_GetCoin, -2, -30000000, 131163, (s32)btlevtcmd_StoreCoin,
    -30000000, 196699, (s32)btlevtcmd_GetExp, -2, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000,
    327771, (s32)btlevtcmd_GetPos, -2, -29999997, -29999999, -29999998, 327771, (s32)_add_star_point_disp_offset,
    -2, -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point",
    0, -29999997, -29999999, -29999998, -30000000, 0, 0, 0,
    0, 0, 0, 0, 65545, 20, 262235, (s32)btlevtcmd_CheckDamageCode,
    -2, 1024, -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_KillUnit,
    -2, 0, 32, 196699, (s32)btlevtcmd_KillUnit, -2, 2, 33,
    2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    SET_VALUE(LW(9), PTR(weapon_gundan_zako_group1_attack))
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(zakogun_set_target_id, LW(3))
    BEGIN_SIBLING_EVENT
        CALL_CHILD(PTR(hit_check_event))
    END_SIBLING_EVENT
    CALL(zakogun_attack1)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(hit_check_event)
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 0, LW(5))
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
    LABEL(90)
    GOTO(98)
    LABEL(91)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    GOTO(98)
    LABEL(98)
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

s32 zakogun_ext_entry_data[] = {
    (s32)"c_zako_n", (s32)"S_1", 0, (s32)"c_zako_n", (s32)"S_1", 1073741824, (s32)"c_zako_n", (s32)"S_1",
    1082130432, (s32)"c_zako_n", (s32)"S_1", 1086324736, (s32)"c_zako_n", (s32)"S_1", 1090519040, (s32)"c_zako_n",
    (s32)"S_1", 1092616192, (s32)"c_zako_n", (s32)"S_1", 1094713344, (s32)"c_zako_n", (s32)"S_1", 1096810496,
    (s32)"c_zako_n", (s32)"S_1", 1098907648, (s32)"c_zako_n", (s32)"S_1", 1099956224, (s32)"c_zako_n", (s32)"S_1",
    1101004800, (s32)"c_zako_n", (s32)"S_1", 1102053376, (s32)"c_zako_n", (s32)"S_1", 1103101952, (s32)"c_zako_n",
    (s32)"S_1", 1104150528, (s32)"c_zako_n", (s32)"S_1", 1105199104, (s32)"c_zako_n", (s32)"S_1", 1106247680,
    (s32)"c_zako_n", (s32)"S_1", 1107296256, (s32)"c_zako_n", (s32)"S_1", 1107820544, (s32)"c_zako_n", (s32)"S_1",
    1108344832, (s32)"c_zako_n", (s32)"S_1", 1108869120, (s32)"c_zako_n", (s32)"Z_2", 0, (s32)"c_zako_n",
    (s32)"Z_3", 0, (s32)"c_zako_n", (s32)"R_1", 0, (s32)"c_zako_n", (s32)"R_1", 1065353216,
    (s32)"c_zako_n", (s32)"R_1", 1073741824, (s32)"c_zako_n", (s32)"R_1", 1077936128, (s32)"c_zako_n", (s32)"R_1",
    1082130432, (s32)"c_zako_n", (s32)"R_1", 1084227584, (s32)"c_zako_n", (s32)"R_1", 1086324736, (s32)"c_zako_n",
    (s32)"R_1", 1088421888, (s32)"c_zako_n", (s32)"R_1", 1090519040, (s32)"c_zako_n", (s32)"R_1", 1091567616,
    (s32)"c_zako_n", (s32)"A_3", 0, (s32)"c_zako_n", (s32)"D_1", 0, (s32)"c_zako_n", (s32)"D_1",
    1077936128, (s32)"c_zako_n", (s32)"D_1", 1086324736, (s32)"c_zako_n", (s32)"J_1A", 0, (s32)"c_zako_n",
    (s32)"S_2", 0, (s32)"c_zako_n", (s32)"S_2", 1092616192, (s32)"c_zako_n", (s32)"S_2", 1101004800,
    (s32)"c_zako_n", (s32)"S_2", 1106247680, (s32)"c_zako_n", (s32)"A_5", 0, (s32)"c_zako_n", (s32)"A_5",
    1090519040, (s32)"c_zako_n", (s32)"A_5", 1094713344, (s32)"c_zako_n", (s32)"A_2", 0, (s32)"c_zako_n",
    (s32)"D_5", 0, (s32)"c_zako_n", (s32)"D_5", 1073741824, (s32)"c_zako_n", (s32)"D_5", 1082130432,
    0, 0, 0,
};

EVT_BEGIN(zakogun_entry)
    CALL(evt_npc_entry, STRING("ext_zakogun"), STRING("c_zako_n"))
    CALL(evt_npc_set_position, STRING("ext_zakogun"), 0, -1000, 0)
    CALL(evt_ext_entry, 500, PTR(zakogun_ext_entry_data), PTR(zakogun_ext_init), PTR(zakogun_ext_main), 0)
    RETURN
EVT_END()

void zakogun_ext_init(void) {
    u8* flags = &_battleWorkPointer->field_180DC;
    BattleStageObject* body;
    BattleStageObject* wire;

    work_20_bss_6C = BattleAlloc(sizeof(ZakoGunWork));
    work_20_bss_6C->zako = BattleAlloc(500 * sizeof(ZakoGun));
    zakogun = work_20_bss_6C->zako;
    work_20_bss_6C->flag = 0;
    body = BattleSearchObjectPtr("if_body");
    wire = BattleSearchObjectPtr("if_wire");
    wire->mPosition = (Vec){0.0f, 250.0f, 0.0f};
    body->mPosition = wire->mPosition;
    *flags |= 0x60;
}

void zakogun_ext_main(void) {
    switch (work_20_bss_6C->flag) {
        case 0:
            zakogun_ext_main1();
            break;
        case 1:
            zakogun_ext_main2();
            break;
        case 2:
            zakogun_ext_main3();
            break;
    }
    dispEntry(CAMERA_3D, 0.0f, 1, zakogun_ext_disp, NULL);
}

void zakogun_ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

USER_FUNC(zakogun_get_kanbu_id_evtcmd) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id = -1;
    s32 i;

    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x63) {
            id = i;
        }
    }
    evtSetValue(event, args[0], id);
    return EVT_RETURN_DONE;
}

s32 zakogun_get_kanbu_id(void) {
    s32 id = -1;
    BattleUnit* unit;
    s32 i;
    BattleWork* wp = _battleWorkPointer;


    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && unit->initialKind == 0x63) {
            id = i;
        }
    }
    return id;
}

USER_FUNC(zakogun_ext_init1) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    work_20_bss_6C->flag = 0;
    for (i = 0; i < 6; i++, pose++) {
        zakogun_ext_init123_common(pose, i);
    }
    return EVT_RETURN_DONE;
}

void zakogun_ext_init123_common(ExtPose* pose, s32 i) {
    pose->flags = 1;
    PSMTXIdentity(pose->mtx);
    pose->mtx[0][3] = 0.0f;
    pose->mtx[1][3] = -1000.0f;
    pose->mtx[2][3] = 0.0f;
    pose->rot = 90.0f;
    zakogun[i].field_0x0 = 0;
    zakogun[i].state = 0;
    zakogun[i].timer = 0;
    zakogun[i].pos = (Vec){0.0f, -1000.0f, 0.0f};
    zakogun[i].home = (Vec){0.0f, 0.0f, 0.0f};
    zakogun[i].rot.y = 0.0f;
}

void zakogun_ext_main1(void) {
}

USER_FUNC(zakogun_attack1) {
    s32 i;
    s32 n = 0;

    if (isFirstCall) {
        for (i = 0; i < 6; i++) {
            zakogun[i].state = 30;
        }
    }
    for (i = 0; i < 6; i++) {
        if (zakogun[i].state == 20) {
            n++;
        }
    }
    return n == 6 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(zakogun_dead1) {
    s32 i;

    for (i = 0; i < 6; i++) {
        zakogun[i].state = 80;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(zakogun_escape1) {
    s32 i;
    s32 n = 0;

    if (isFirstCall) {
        for (i = 0; i < 6; i++) {
            ZakoGun* zako = &zakogun[i];
            zako->state = 90;
            zakogun_set_pose(zako, 0x16, 10, 1);
        }
    }
    for (i = 0; i < 6; i++) {
        if (zakogun[i].state == -1) {
            n++;
        }
    }
    return n == 6 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(zakogun_start_sukima) {
    s32 mode = evtGetValue(event, event->args[0]);
    s32 i;

    for (i = 0; i < 6; i++) {
        ZakoGun* zako = &zakogun[i];
        if (zako->state < 80 || zako->state >= 90) {
            if (mode == 1) {
                zako->state = 96;
                zako->timer = 0;
            } else {
                zako->state = 95;
            }
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(zakogun_end_sukima) {
    s32 i;

    for (i = 0; i < 6; i++) {
        ZakoGun* zako = &zakogun[i];
        if (zako->state < 80 || zako->state >= 90) {
            zako->state = 20;
        }
    }
    return EVT_RETURN_DONE;
}

ZakoGun* zakogun;
ZakoGunWork* work_20_bss_6C;

