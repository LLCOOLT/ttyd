#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "string.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "manager/evtmgr_cmd.h"

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct MoamoaGroup { char anim[16]; char pose[8]; f32 speed; s32 start; s32 num; } MoamoaGroup;
typedef struct Moamoa { u16 flags; u8 field_0x2[2]; Vec pos; s16 group; u8 field_0x12[6]; OSTime time; s16 chain; s16 order; f32 t; s32 poseId; s32 type; s32* owner; Vec vel; Vec pos2; u8 field_0x4c[4]; } Moamoa;
typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* elems; s32 numGroups; MoamoaGroup groups[32]; s16 chainNum[128]; s16 chainIdx[128][2]; s32 poseId[5]; s32 unitId; Vec center; f32 angle; f32 radius; f32 targetScale; f32 scale; } MoamoaWork;
typedef struct MoamoaExtData { const char* anim; const char* pose; f32 speed; } MoamoaExtData;
static MoamoaWork* wp;
ExtPose* extGetPosePtr(void);
void extReset(void);
int rand(void);
void moamoa_mainUnitIdClear(void);
static f32 randf(f32 min, f32 max);
extern const char* g_moamoa_chain_tbl[][2];
extern const s32 dat_80419a28;
USER_FUNC(moamoa1_on);
void moamoa_pose(Moamoa* elem);
void moamoa_draw(CameraId cameraId, void* param);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHitCursorOffset);
USER_FUNC(btlevtcmd_SetHitOffset);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_ext_entry);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_set_position);
USER_FUNC(moamoa_on);
USER_FUNC(moamoa_set_bodyScale);
void moamoa_draw(CameraId cameraId, void* param);
static void ext_moamoa_main(void);
static void ext_moamoa_init(void);
void moamoa_pose(Moamoa* elem);
USER_FUNC(moamoa2_on);
USER_FUNC(moamoa1_on);
USER_FUNC(moamoa_bomb);
USER_FUNC(moamoa_guruguru);
void moamoa_mainUnitIdClear(void);
static f32 randf(f32 min, f32 max);
USER_FUNC(evt_moamoa_mainUnitIdClear);
USER_FUNC(boss_moamoa_check_zenei_kouei);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Confuse[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeSetPoseTable[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_GetBackItem[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_SetPartsDefenceTable[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_WaitAttackEnd[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_eff[];
extern s32 unit_boss_moamoa_mouth[];
extern s32 unit_boss_moamoa_tentacle_a[];
extern s32 unit_boss_moamoa_tentacle_b[];
extern s32 unit_boss_moamoa_tentacle_c[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_boss_moamoa_negone_one_374;
__declspec(section ".data") s32 fd_boss_moamoa_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_moamoa___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_moamoa___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_moamoa_one_negone_373;
__declspec(section ".data") s32 fd_boss_moamoa___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_moamoa_one_381[1];
__declspec(section ".data") u64 fd_boss_moamoa_negone_one_360;
__declspec(section ".data") s32 fd_boss_moamoa_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_moamoa___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_moamoa___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_moamoa_one_negone_359;
__declspec(section ".data") s32 fd_boss_moamoa___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_moamoa_one_364[1];
BattleUnitKind unit_boss_moamoa;
__declspec(section ".data") BattleUnitDefense moamoa_defence;
__declspec(section ".data") s32 moamoa_defence_no_parts[2];
__declspec(section ".data") s32 moamoa2_defence[2];
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
__declspec(section ".data") PoseTableEntry moamoa1_pose_table[4];
__declspec(section ".data") s32 moamoa1_weakness_pose_table[8];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[1];
__declspec(section ".data") s32 entry_boss_moamoa_tentacle_a[12];
__declspec(section ".data") s32 entry_boss_moamoa_tentacle_b[12];
__declspec(section ".data") s32 entry_boss_moamoa_tentacle_c[12];
__declspec(section ".data") s32 entry_boss_moamoa_mouth[12];
s32 weapon_moamoa_tsunami_attack[48];
s32 moamoa_zoom[34];
static s32 mario_party_zoom[34];
static s32 init_event[159];
static __declspec(section ".data") s32 damage_event[10];
__declspec(section ".data") s32 MOAMOA_TAIJOU[4];
static s32 dead_event[349];
__declspec(section ".data") s32 moamoa2_change_tbl[7];
s32 moamoa_tentacl_on[208];
s32 moamoa_mouth_on[132];
static s32 phase_event[159];
static s32 attack_event[19];
static __declspec(section ".data") s32 wait_event[6];
static s32 ext_moamoa_data[267];
static s32 evt_moamoa[151];
__declspec(section ".data") s32 MOAMOA_SET_BODYSCALE[4];

USER_FUNC(boss_moamoa_check_zenei_kouei) {
    BattleWork* btlwp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    f32 x, y, z;

    id = BattleTransID(event, id);
    BtlUnit_GetPos(BattleGetUnitPtr(btlwp, id), &x, &y, &z);
    if (x >= -120.0f) {
        evtSetValue(event, out, 0);
    } else {
        evtSetValue(event, out, 1);
    }
    return 2;
}

USER_FUNC(evt_moamoa_mainUnitIdClear) {
    moamoa_mainUnitIdClear();
    return 2;
}

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

void moamoa_mainUnitIdClear(void) {
    wp->unitId = -1;
}

__declspec(section ".data") u64 fd_boss_moamoa_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_moamoa_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_moamoa___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_moamoa___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_moamoa_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_moamoa___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_moamoa_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_moamoa_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_moamoa_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_moamoa___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_moamoa___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_moamoa_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_moamoa___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_moamoa_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_moamoa = {
    107,
    "btl_un_moamoa",
    50,
    0,
    1,
    1,
    78,
    0,
    0,
    100,
    0,
    50,
    6,
    160,
    80,
    0,
    24,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    280.0f,
    40.0f,
    0.0f,
    80.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    15.0f,
    10.0f,
    80.0f,
    0.0f,
    0.0f,
    10.0f,
    80.0f,
    20.0f,
    0.0f,
    70.0f,
    0.0f,
    160.0f,
    80.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MOA_G_DAMAGED1",
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

__declspec(section ".data") BattleUnitDefense moamoa_defence = {{2, 2, 2, 2, 2}};

__declspec(section ".data") s32 moamoa_defence_no_parts[] = {
    0, 0,
};

__declspec(section ".data") s32 moamoa2_defence[] = {
    16843009, 16777216,
};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

__declspec(section ".data") PoseTableEntry moamoa1_pose_table[] = {
    {28, "S_1_1"},
    {31, "D_1_1"},
    {39, "D_1_1"},
    {69, "S_1_1"},
};

__declspec(section ".data") s32 moamoa1_weakness_pose_table[] = {
    28, (s32)"S_1_3", 31, (s32)"D_1_3", 39, (s32)"D_1_3", 69, (s32)"S_1_3",
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_moamoa", "c_g_moamoa_b", 0.0f, 0.0f, 0.0f, -2.0f, 53.0f, 20.0f, -4.0f, 63.0f, 20.0f, 20, 30, 255, &moamoa_defence, &defence_attr, 0x20000001, 0, moamoa1_pose_table},
};

__declspec(section ".data") s32 entry_boss_moamoa_tentacle_a[] = {
    (s32)unit_boss_moamoa_tentacle_a, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_boss_moamoa_tentacle_b[] = {
    (s32)unit_boss_moamoa_tentacle_b, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_boss_moamoa_tentacle_c[] = {
    (s32)unit_boss_moamoa_tentacle_c, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 entry_boss_moamoa_mouth[] = {
    (s32)unit_boss_moamoa_mouth, 16777216, 67108868, 0, -998637568, 0, 0, 0,
    0, 0, 0, 0,
};

s32 weapon_moamoa_tsunami_attack[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

EVT_BEGIN(moamoa_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 30)
        ELSE
        SET_VALUE(LW(1), 1)
    END_IF
    CALL(evt_btl_camera_set_moveto, 0, 83, 144, 512, 83, 109, 0, LW(1), 11)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(mario_party_zoom)
    CALL(evt_btl_camera_set_mode, 0, 3)
    IF_INT_NOT_EQUAL(LW(0), 2)
        SET_VALUE(LW(1), 30)
        ELSE
        SET_VALUE(LW(1), 1)
    END_IF
    CALL(evt_btl_camera_set_moveto, 0, -120, 58, 257, -120, 40, 0, LW(1), 11)
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(600)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, -2, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, -2, 1, 2)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_GetUnitId, -2, LW(4))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_boss_moamoa_tentacle_c), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(5), 3)
    CALL(btlevtcmd_SetUnitWork, -2, LW(5), LW(3))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(4))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_boss_moamoa_tentacle_b), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(5), 4)
    CALL(btlevtcmd_SetUnitWork, -2, LW(5), LW(3))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(4))
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_boss_moamoa_tentacle_a), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    SET_VALUE(LW(5), 5)
    CALL(btlevtcmd_SetUnitWork, -2, LW(5), LW(3))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(4))
    SET_VALUE(LW(5), 6)
    CALL(btlevtcmd_SetUnitWork, -2, LW(5), -1)
    CALL_CHILD(PTR(evt_moamoa))
    SPAWN_EVENT(PTR(MOAMOA_SET_BODYSCALE))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

__declspec(section ".data") s32 MOAMOA_TAIJOU[] = {
    (s32)"S_1_2", 0, (s32)"L_1_4", 0,
};

static s32 dead_event[] = {
    65627, (s32)btlevtcmd_WaitAttackEnd, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131097,
    -30000000, 1, 131122, -30000000, 5, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    -30000000, -29999999, 131097, -29999999, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_MOA_G_ARM_DOWN1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999999, 1,
    (s32)"R_1A", 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999999, 1, 196699,
    (s32)btlevtcmd_KillUnit, -29999999, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, -30000000, -1,
    33, 131122, -30000000, 4, 262235, (s32)btlevtcmd_GetUnitWork, -2, -30000000,
    -29999999, 131097, -29999999, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_DOWN1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999999, 1, (s32)"R_1B",
    65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999999, 1, 196699, (s32)btlevtcmd_KillUnit,
    -29999999, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2, -30000000, -1, 33,
    131122, -30000000, 3, 262235, (s32)btlevtcmd_GetUnitWork, -2, -30000000, -29999999,
    131097, -29999999, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_DOWN1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999999, 1, (s32)"R_1C", 65545,
    1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999999, 1, 196699, (s32)btlevtcmd_KillUnit, -29999999,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -2, -30000000, -1, 33, 32,
    131122, -30000000, 6, 262235, (s32)btlevtcmd_GetUnitWork, -2, -30000000, -29999999,
    131097, -29999999, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_DOWN2", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -29999999, 1, (s32)"L_2_6", 65545,
    1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999999, 1, 196699, (s32)btlevtcmd_KillUnit, -29999999,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -2, -30000000, -1, 33, 33,
    65598, (s32)MOAMOA_TAIJOU, 65541, 0, 65599, -29999998, 131096, -29999998,
    0, 7, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998,
    65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 6, 65546,
    1000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_LUMP1", -250000000, 0, -250000000,
    65541, 0, 65599, -29999998, 131096, -29999998, 0, 7,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 1,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 6, 65627, (s32)moamoa_guruguru, 65546,
    500, 131122, -29999990, -2, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999,
    -29999998, 131125, -29999998, 10, 983131, (s32)evt_eff, 0, (s32)"kemuri_test",
    4, -30000000, -29999999, -29999998, -229999181, 0, 0, 0,
    0, 0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000,
    131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163,
    (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999, -29999998,
    131125, -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset,
    -29999990, -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point",
    0, -29999997, -29999999, -29999998, -30000000, 0, 0, 0,
    0, 0, 0, 0, 131101, -30000000, 1, 65541,
    -30000000, 6, 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_EXPLOSION1", -250000000,
    0, -250000000, 65627, (s32)moamoa_bomb, 65627, (s32)evt_moamoa_mainUnitIdClear, 131163, (s32)btlevtcmd_GetBackItem,
    -29999990, 262235, (s32)btlevtcmd_CheckDamageCode, -29999990, 1024, -30000000, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_KillUnit, -29999990, 0, 32, 196699, (s32)btlevtcmd_KillUnit,
    -29999990, 2, 33, 2, 1,
};

__declspec(section ".data") s32 moamoa2_change_tbl[] = {
    (s32)"L_2_1", (s32)"L_2_3", 0, (s32)"L_2_4", (s32)"L_2_5", (s32)"S_2", 0,
};

s32 moamoa_tentacl_on[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_RESTORE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"V_2", 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -2, 1, 196699, (s32)btlevtcmd_GetUnitId, -2, -29999996, 262235, (s32)btlevtcmd_SpawnUnit,
    -29999997, (s32)entry_boss_moamoa_tentacle_c, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 131122, -29999995, 3,
    262235, (s32)btlevtcmd_SetUnitWork, -2, -29999995, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997,
    0, -29999996, 131122, -29999994, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997,
    (s32)entry_boss_moamoa_tentacle_b, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos,
    -29999997, -30000000, -29999999, -29999998, 131122, -29999995, 4, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, -29999995, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0,
    -29999996, 131122, -29999993, -29999997, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_boss_moamoa_tentacle_a,
    0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetHomePos, -29999997,
    -30000000, -29999999, -29999998, 131122, -29999995, 5, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, -29999995, -29999997, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999996,
    65627, (s32)moamoa1_on, 262235, (s32)btlevtcmd_SetPartsDefenceTable, -2, 1, (s32)&moamoa_defence, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 1, 536870912, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1,
    (s32)moamoa1_pose_table, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999997, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -29999993, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999994, 1, 16777216,
    65545, 3, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1, 16777216, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -29999993, 1, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999994, 1,
    16777216, 262235, (s32)btlevtcmd_AnimeChangePose, -29999997, 1, (s32)"B_1A", 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999993, 1, (s32)"B_1B", 262235, (s32)btlevtcmd_AnimeChangePose, -29999994, 1, (s32)"B_1C",
    65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999994, 1, 2, 1,
};

s32 moamoa_mouth_on[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MOA_G_ARM_RESTORE2", -250000000, 0, -250000000, 65545,
    40, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"V_2", 65545, 1,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 196699, (s32)btlevtcmd_GetUnitId, -2, -29999996,
    262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_boss_moamoa_mouth, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -29999997, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 131122,
    -29999995, 6, 262235, (s32)btlevtcmd_SetUnitWork, -2, -29999995, -29999997, 262235,
    (s32)btlevtcmd_SetUnitWork, -29999997, 0, -29999996, 65627, (s32)moamoa2_on, 262235, (s32)btlevtcmd_SetPartsDefenceTable,
    -2, 1, (s32)moamoa2_defence, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)moamoa1_pose_table,
    65598, (s32)moamoa2_change_tbl, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999997, 1, 16777216, 65545,
    3, 262235, (s32)btlevtcmd_OffPartsAttribute, -29999997, 1, 16777216, 65541, 0,
    65599, -29999998, 131096, -29999998, 0, 7, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999997, 1, -29999998, 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete,
    -29999997, 1, 6, 65546, 1000, 65541, 0, 65599,
    -29999998, 131096, -29999998, 0, 7, 33, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999997, 1, -29999998, 65545, 1, 196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -29999997,
    1, 6, 2, 1,
};

static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108867)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 6, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_GetUnitWork, -2, 3, LW(0))
                IF_INT_EQUAL(LW(0), -1)
                    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(1))
                    IF_INT_NOT_EQUAL(LW(1), 0)
                        SUBTRACT(LW(1), 1)
                        CALL(btlevtcmd_SetUnitWork, -2, 1, LW(1))
                        IF_INT_EQUAL(LW(1), 0)
                            CALL(btlevtcmd_SetUnitWork, -2, 1, 2)
                            CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
                            SWITCH(LW(0))
                                CASE_EQUAL(0)
                                CALL(btlevtcmd_GetMaxHp, -2, LW(0))
                                MULTIPLY(LW(0), 50)
                                DIVIDE(LW(0), 100)
                                CALL(btlevtcmd_GetHp, -2, LW(1))
                                IF_INT_LESS_OR_EQUAL(LW(1), LW(0))
                                    CALL(btlevtcmd_SetUnitWork, -2, 2, 1)
                                    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1_2"))
                                    WAIT_MS(1000)
                                    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("S_1_1"))
                                END_IF
                            END_SWITCH
                            CALL(btlevtcmd_GetUnitWork, -2, 2, LW(1))
                            IF_INT_NOT_EQUAL(LW(1), 1)
                                CALL_CHILD(PTR(moamoa_tentacl_on))
                                ELSE
                                CALL_CHILD(PTR(moamoa_mouth_on))
                            END_IF
                            CALL(btlevtcmd_SetHitOffset, -2, 1, 0, 0, 0)
                            CALL(btlevtcmd_SetHitCursorOffset, -2, 1, 0, 0, 0)
                        END_IF
                    END_IF
                END_IF
            END_IF
        END_IF
    END_IF
    LABEL(0)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

static s32 ext_moamoa_data[] = {
    (s32)"c_n_moa_a", (s32)"S_1", 0, (s32)"c_n_moa_a", (s32)"S_1", 1073741824, (s32)"c_n_moa_a", (s32)"S_1",
    1082130432, (s32)"c_n_moa_a", (s32)"S_1", 1086324736, (s32)"c_n_moa_a", (s32)"S_1", 1090519040, (s32)"c_n_moa_a",
    (s32)"S_1", 1092616192, (s32)"c_n_moa_a", (s32)"S_1", 1094713344, (s32)"c_n_moa_a", (s32)"S_1", 1096810496,
    (s32)"c_n_moa_a", (s32)"S_1", 1098907648, (s32)"c_n_moa_a", (s32)"S_1", 1099956224, (s32)"c_n_moa_a", (s32)"S_1",
    1101004800, (s32)"c_n_moa_a", (s32)"S_1", 1102053376, (s32)"c_n_moa_a", (s32)"S_1", 1103101952, (s32)"c_n_moa_a",
    (s32)"S_1", 1104150528, (s32)"c_n_moa_a", (s32)"S_1", 1105199104, (s32)"c_n_moa_a", (s32)"S_1", 1106247680,
    (s32)"c_n_moa_a", (s32)"S_1", 1107296256, (s32)"c_n_moa_a", (s32)"S_1", 1107820544, (s32)"c_n_moa_a", (s32)"S_1",
    1108344832, (s32)"c_n_moa_a", (s32)"S_1", 1108869120, (s32)"c_n_moa_a", (s32)"D_1", 0, (s32)"c_n_moa_a",
    (s32)"D_1", 1073741824, (s32)"c_n_moa_a", (s32)"D_1", 1082130432, (s32)"c_n_moa_a", (s32)"D_1", 1086324736,
    (s32)"c_n_moa_a", (s32)"D_1", 1090519040, (s32)"c_n_moa_a", (s32)"D_1", 1092616192, (s32)"c_n_moa_a", (s32)"S_2",
    0, (s32)"c_n_moa_a", (s32)"S_2", 1073741824, (s32)"c_n_moa_a", (s32)"S_2", 1082130432, (s32)"c_n_moa_a",
    (s32)"S_2", 1086324736, (s32)"c_n_moa_a", (s32)"S_2", 1090519040, (s32)"c_n_moa_a", (s32)"S_2", 1092616192,
    (s32)"c_n_moa_a", (s32)"S_2", 1094713344, (s32)"c_n_moa_a", (s32)"S_2", 1096810496, (s32)"c_n_moa_a", (s32)"S_2",
    1098907648, (s32)"c_n_moa_a", (s32)"S_2", 1099956224, (s32)"c_n_moa_a", (s32)"S_2", 1101004800, (s32)"c_n_moa_a",
    (s32)"S_2", 1102053376, (s32)"c_n_moa_a", (s32)"S_2", 1103101952, (s32)"c_n_moa_a", (s32)"S_2", 1104150528,
    (s32)"c_n_moa_a", (s32)"S_2", 1105199104, (s32)"c_n_moa_a", (s32)"S_2", 1106247680, (s32)"c_n_moa_a", (s32)"S_2",
    1107296256, (s32)"c_n_moa_a", (s32)"S_2", 1107820544, (s32)"c_n_moa_a", (s32)"S_2", 1108344832, (s32)"c_n_moa_a",
    (s32)"S_2", 1108869120, (s32)"c_n_moa_b", (s32)"S_1", 0, (s32)"c_n_moa_b", (s32)"S_1", 1073741824,
    (s32)"c_n_moa_b", (s32)"S_1", 1082130432, (s32)"c_n_moa_b", (s32)"S_1", 1086324736, (s32)"c_n_moa_b", (s32)"S_1",
    1090519040, (s32)"c_n_moa_b", (s32)"S_1", 1092616192, (s32)"c_n_moa_b", (s32)"S_1", 1094713344, (s32)"c_n_moa_b",
    (s32)"S_1", 1096810496, (s32)"c_n_moa_b", (s32)"S_1", 1098907648, (s32)"c_n_moa_b", (s32)"S_1", 1099956224,
    (s32)"c_n_moa_b", (s32)"S_1", 1101004800, (s32)"c_n_moa_b", (s32)"S_1", 1102053376, (s32)"c_n_moa_b", (s32)"S_1",
    1103101952, (s32)"c_n_moa_b", (s32)"S_1", 1104150528, (s32)"c_n_moa_b", (s32)"S_1", 1105199104, (s32)"c_n_moa_b",
    (s32)"S_1", 1106247680, (s32)"c_n_moa_b", (s32)"S_1", 1107296256, (s32)"c_n_moa_b", (s32)"S_1", 1107820544,
    (s32)"c_n_moa_b", (s32)"S_1", 1108344832, (s32)"c_n_moa_b", (s32)"S_1", 1108869120, (s32)"c_n_moa_b", (s32)"D_1",
    0, (s32)"c_n_moa_b", (s32)"D_1", 1073741824, (s32)"c_n_moa_b", (s32)"D_1", 1082130432, (s32)"c_n_moa_b",
    (s32)"D_1", 1086324736, (s32)"c_n_moa_b", (s32)"D_1", 1090519040, (s32)"c_n_moa_b", (s32)"D_1", 1092616192,
    (s32)"c_kinodebu", (s32)"G_1", 1077936128, (s32)"c_kinodebu", (s32)"G_1", 1093664768, (s32)"c_puku_c", (s32)"U_1",
    1065353216, (s32)"c_puku_c", (s32)"U_1", 1086324736, (s32)"c_powan", (s32)"R_2", 1077936128, (s32)"c_powan",
    (s32)"R_2", 1086324736, (s32)"c_smoko", (s32)"G_1", 1073741824, (s32)"c_smoko", (s32)"G_1", 1086324736,
    (s32)"c_rose", (s32)"G_1", 1082130432, (s32)"c_rose", (s32)"G_1", 1090519040, (s32)"c_papab", (s32)"G_1",
    1065353216, (s32)"c_papab", (s32)"G_1", 1084227584, (s32)"c_mamab", (s32)"G_1", 1065353216, (s32)"c_mamab",
    (s32)"G_1", 1084227584, (s32)"c_konari", (s32)"G_1", 1065353216, (s32)"c_konari", (s32)"G_1", 1084227584,
    0, 0, 0,
};

USER_FUNC(moamoa_guruguru) {
    s32 i;
    Moamoa* elem;
    ExtPose* pose;
    f32 cnt;
    f32 ang;
    Vec v;
    Mtx m;

    BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    wp->center = (Vec){0.0f, 0.0f, 0.0f};
    pose = extGetPosePtr();
    elem = wp->elems;
    cnt = 0.0f;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        if (*elem->owner != -1) {
            v.x = pose->mtx[0][3];
            v.y = pose->mtx[1][3];
            v.z = pose->mtx[2][3];
            if (v.y >= 0.0f) {
                elem->flags |= 1;
                cnt += 1.0f;
                PSVECAdd(&v, &wp->center, &wp->center);
            }
        }
    }
    PSVECScale(&wp->center, &wp->center, 1.0f / cnt);
    wp->angle = 0.0f;
    wp->radius = 2.0f;
    pose = extGetPosePtr();
    elem = wp->elems;
    ang = 0.0f;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        if (elem->flags & 1) {
            elem->vel.x = pose->mtx[0][3];
            elem->vel.y = pose->mtx[1][3];
            elem->vel.z = pose->mtx[2][3];
            elem->pos2 = (Vec){0.0f, 1.0f, 0.0f};
            PSMTXRotRad(m, 'Z', 0.017453292f * ang);
            PSMTXMultVec(m, &elem->pos2, &elem->pos2);
            ang += 22.4375f;
            if (ang >= 360.0f) {
                ang -= 360.0f;
            }
        }
    }
    return 2;
}

USER_FUNC(moamoa_bomb) {
    ExtPose* p2;
    Moamoa* e2;
    s32 k;
    s32 i;
    ExtPose* pose;
    Moamoa* elem;
    s32 n;

    BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    wp->center = (Vec){0.0f, 0.0f, 0.0f};
    if (isFirstCall) {
        extGetPosePtr();
        elem = wp->elems;
        for (i = 0; i < wp->count; i++, elem++) {
            if (*elem->owner != -1) {
                elem->flags &= ~1;
            }
        }
    }
    if (!(gp->retraceCount & 1)) {
        p2 = extGetPosePtr();
        n = 0;
        e2 = wp->elems;
        for (k = 0; k < wp->count; k++, p2++, e2++) {
            if (p2->mtx[1][3] >= 0.0f && !(e2->flags & 1)) {
                e2->flags |= 1;
                if (e2->flags & 1) {
                    e2->vel.x = randf(0.0f, 60.0f) - 30.0f;
                    e2->vel.y = randf(0.0f, 35.0f);
                    e2->vel.z = 60.0f + randf(0.0f, 30.0f);
                    n++;
                    e2->pos2.x = p2->mtx[0][3];
                    e2->pos2.y = p2->mtx[1][3];
                    e2->pos2.z = p2->mtx[2][3];
                }
            }
            if (n >= 10) {
                break;
            }
        }
    }
    pose = extGetPosePtr();
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        if (elem->flags & 1) {
            if (elem->pos2.y >= -500.0f) {
                elem->pos2.x += elem->vel.x;
                elem->pos2.y += elem->vel.y;
                elem->pos2.z += elem->vel.z;
                elem->vel.y -= 1.0f;
            }
            pose->mtx[0][3] = elem->pos2.x;
            pose->mtx[1][3] = elem->pos2.y;
            pose->mtx[2][3] = elem->pos2.z;
        }
    }
    pose = extGetPosePtr();
    n = 0;
    for (i = 0; i < wp->count; i++, pose++) {
        if (pose->mtx[1][3] >= -200.0f) {
            n++;
        }
    }
    if (n <= 9) {
        wp->center = (Vec){0.0f, -1000.0f, 0.0f};
        return 2;
    }
    return 0;
}

USER_FUNC(moamoa1_on) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    s32 i;
    BattleUnitPart* part;
    Moamoa* elem;
    AnimationPose* ap;
    s32 j;
    Vec* p;

    for (i = 1; i < 4; i++) {
        switch (i) {
            case 1:
                part = BattleGetUnitPartsPtr(unit->work[3], 1);
                break;
            case 2:
                part = BattleGetUnitPartsPtr(unit->work[4], 1);
                break;
            case 3:
                part = BattleGetUnitPartsPtr(unit->work[5], 1);
                break;
        }
        wp->poseId[i] = part->poseId;
        animPoseWorldPositionEvalOn(wp->poseId[i]);
        ap = animPoseGetAnimPosePtr(wp->poseId[i]);
        p = *ap->worldPositions;
        for (j = 0; j < ap->numWorldPositions; j++, p++) {
            *p = (Vec){0.0f, -1000.0f, 0.0f};
        }
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        if (elem->chain < 5) {
            elem->poseId = wp->poseId[3];
            elem->owner = &unit->work[5];
        } else if (elem->chain < 10) {
            elem->poseId = wp->poseId[2];
            elem->owner = &unit->work[4];
        } else if (elem->chain < 15) {
            elem->poseId = wp->poseId[1];
            elem->owner = &unit->work[3];
        } else if (elem->chain < 30) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        }
    }
    return 2;
}

USER_FUNC(moamoa2_on) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    Moamoa* elem;
    AnimationPose* ap;
    Vec* p;
    s32 i;

    wp->poseId[4] = BattleGetUnitPartsPtr(unit->work[6], 1)->poseId;
    animPoseWorldPositionEvalOn(wp->poseId[4]);
    ap = animPoseGetAnimPosePtr(wp->poseId[4]);
    p = *ap->worldPositions;
    for (i = 0; i < ap->numWorldPositions; i++, p++) {
        *p = (Vec){0.0f, -1000.0f, 0.0f};
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        if (elem->chain < 5) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 10) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 15) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 30) {
            elem->poseId = wp->poseId[4];
            elem->owner = &unit->work[6];
        } else {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        }
    }
    return 2;
}

USER_FUNC(moamoa_on) {
    s32 i;
    s32 j;
    Moamoa* elem;
    MoamoaExtData* d;
    AnimationPose* ap;
    Vec* p;
    s32 start;
    Vec v;
    char anim[32];
    char pose[32];

    wp = __memAlloc(HEAP_BATTLE, sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->count = 750;
    wp->elems = __memAlloc(HEAP_BATTLE, wp->count * sizeof(Moamoa));
    memset(wp->elems, 0, wp->count * sizeof(Moamoa));
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->flags = 0;
        v = (Vec){0.0f, 0.0f, 0.0f};
        v.x = randf(-10.0f, 10.0f);
        v.y = randf(-10.0f, 10.0f);
        v.z = randf(-10.0f, 10.0f);
        elem->pos = v;
    }
    wp->unitId = BattleTransID(event, -2);
    BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    wp->poseId[0] = BattleGetUnitPartsPtr(wp->unitId, 1)->poseId;
    animPoseWorldPositionEvalOn(wp->poseId[0]);
    ap = animPoseGetAnimPosePtr(wp->poseId[0]);
    p = *ap->worldPositions;
    for (i = 0; i < ap->numWorldPositions; i++, p++) {
        *p = (Vec){0.0f, -1000.0f, 0.0f};
    }
    for (i = 0; i < dat_80419a28; i++) {
        wp->chainIdx[i][0] = animPoseGetGroupIdx(wp->poseId[0], g_moamoa_chain_tbl[i][0]);
        wp->chainIdx[i][1] = animPoseGetGroupIdx(wp->poseId[0], g_moamoa_chain_tbl[i][1]);
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->chain = i % dat_80419a28;
        elem->order = wp->chainNum[elem->chain]++;
    }
    moamoa1_on(event, isFirstCall);
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->t = (f32)elem->order / (f32)wp->chainNum[elem->chain];
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        if (elem->chain == 0 || elem->chain == 5 || elem->chain == 10 || elem->chain == 15 || elem->chain == 46) {
            elem->type = 1;
        }
        if (elem->order == 0) {
            if (elem->chain == 3) {
                elem->type = 2;
            }
            if (elem->chain == 4) {
                elem->type = 3;
            }
            if (elem->chain == 7) {
                elem->type = 4;
            }
            if (elem->chain == 8) {
                elem->type = 5;
            }
            if (elem->chain == 9) {
                elem->type = 6;
            }
            if (elem->chain == 12) {
                elem->type = 7;
            }
            if (elem->chain == 13) {
                elem->type = 8;
            }
            if (elem->chain == 14) {
                elem->type = 9;
            }
        }
    }
    d = (MoamoaExtData*)ext_moamoa_data;
    j = 0;
    strcpy(anim, "");
    strcpy(pose, "");
    wp->numGroups = -1;
    do {
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            strcpy(pose, "");
        }
        if (strcmp(d->pose, pose) != 0) {
            strcpy(pose, d->pose);
            start = j;
            wp->numGroups++;
        }
        strcpy(wp->groups[wp->numGroups].anim, anim);
        strcpy(wp->groups[wp->numGroups].pose, pose);
        wp->groups[wp->numGroups].start = start;
        wp->groups[wp->numGroups].num = j - start + 1;
        if (elem->type >= 2 && elem->type != 10) {
            wp->groups[wp->numGroups].speed = 12.0f;
        } else {
            wp->groups[wp->numGroups].speed = d->speed;
        }
        j++;
    } while ((++d)->anim != NULL);
    wp->numGroups++;
    for (i = 0; i < wp->numGroups; i++) {
    }
    return 2;
}

static EVT_BEGIN(evt_moamoa)
    CALL(evt_npc_entry, STRING("moa_a"), STRING("c_n_moa_a"))
    CALL(evt_npc_entry, STRING("moa_b"), STRING("c_n_moa_b"))
    CALL(evt_npc_set_position, STRING("moa_a"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("moa_b"), 0, -1000, 0)
    CALL(evt_npc_entry, STRING("kinopio"), STRING("c_kinodebu"))
    CALL(evt_npc_entry, STRING("cook"), STRING("c_puku_c"))
    CALL(evt_npc_entry, STRING("powan"), STRING("c_powan"))
    CALL(evt_npc_entry, STRING("sarary"), STRING("c_smoko"))
    CALL(evt_npc_entry, STRING("rose"), STRING("c_rose"))
    CALL(evt_npc_entry, STRING("papa"), STRING("c_papab"))
    CALL(evt_npc_entry, STRING("mama"), STRING("c_mamab"))
    CALL(evt_npc_entry, STRING("konari"), STRING("c_konari"))
    CALL(evt_npc_set_position, STRING("kinopio"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("cook"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("powan"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("sarary"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("rose"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("papa"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("mama"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("konari"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("kinopio"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("cook"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("powan"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("sarary"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("rose"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("papa"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("mama"), 2048)
    CALL(evt_npc_flag_onoff, 1, STRING("konari"), 2048)
    CALL(moamoa_on)
    CALL(evt_ext_entry, 750, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), 0)
    RETURN
EVT_END()

void moamoa_pose(Moamoa* elem) {
    static const char* group_tbl[][2] = {
        {"c_n_moa_a", "S_1"},
        {"c_n_moa_b", "S_1"},
        {"c_kinodebu", "G_1"},
        {"c_puku_c", "U_1"},
        {"c_powan", "R_2"},
        {"c_smoko", "G_1"},
        {"c_rose", "G_1"},
        {"c_papab", "G_1"},
        {"c_mamab", "G_1"},
        {"c_konari", "G_1"},
        {"c_n_moa_a", "S_2"},
    };
    MoamoaGroup* grp;
    s32 i;
    const char* pose;
    const char* anim;

    grp = wp->groups;
    anim = group_tbl[elem->type][0];
    pose = group_tbl[elem->type][1];
    for (i = 0; i < wp->numGroups; i++, grp++) {
        if (strcmp(grp->anim, anim) == 0 && strcmp(grp->pose, pose) == 0) {
            break;
        }
    }
    if (i < wp->numGroups && elem->group != i) {
        elem->group = i;
        elem->time = gp->renderTime;
    }
}

static void ext_moamoa_init(void) {
    s32 i;
    ExtPose* pose;
    Moamoa* elem;

    pose = extGetPosePtr();
    elem = wp->elems;
    wp->targetScale = 1.0f;
    wp->scale = 1.0f;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        pose->flags |= 5;
        PSMTXIdentity(pose->mtx);
        moamoa_pose(elem);
    }
}

__declspec(section ".data") EVT_BEGIN(MOAMOA_SET_BODYSCALE)
    CALL(moamoa_set_bodyScale)
    RETURN
EVT_END()

static void ext_moamoa_main(void) {
    Moamoa* elem;
    Moamoa* e4;
    Moamoa* e2;
    s32 k4;
    s32 k3;
    s32 k;
    s32 i;
    ExtPose* pose;
    s32 j;
    BattleUnit* unit;
    AnimationPose* ap;
    Vec* a;
    Vec* b;
    MoamoaGroup* grp;
    s32 n;
    f32 t;
    f32 s;
    Vec joint[5];
    Vec ofs[5];
    Mtx m;
    Vec w;
    Vec v;
    Vec r;

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
    }
    wp->scale += 0.1f * (wp->targetScale - wp->scale);

    pose = extGetPosePtr();
    e2 = wp->elems;
    for (k = 0; k < wp->count; k++, e2++, pose++) {
        grp = &wp->groups[e2->group];
        t = gp->framerate * (f32)OSTicksToMilliseconds((u64)(gp->renderTime - e2->time)) / 1000.0f / grp->speed;
        if (t >= 1.0f) {
            e2->time = gp->renderTime;
            t = 0.0f;
        }
        n = grp->num * t;
        if (n >= grp->num) {
            n = grp->num - 1;
        }
        pose->frame = grp->start + n;
    }

    if (wp->unitId != -1) {
        unit = BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
        for (j = 0; j < 5; j++) {
            if (j == 0 || unit->work[j + 2] != -1) {
                ap = animPoseGetAnimPosePtr(wp->poseId[j]);
                joint[j] = (*ap->worldPositions)[animPoseGetGroupIdx(wp->poseId[j], "joint_core")];
                PSVECSubtract(&joint[0], &joint[j], &ofs[j]);
            }
        }
        pose = extGetPosePtr();
        e4 = wp->elems;
        for (k4 = 0; k4 < wp->count; k4++, pose++, e4++) {
            if (*e4->owner == -1) {
                pose->mtx[0][3] = 0.0f;
                pose->mtx[1][3] = -1000.0f;
                pose->mtx[2][3] = 0.0f;
                continue;
            }
            ap = animPoseGetAnimPosePtr(e4->poseId);
            a = &(*ap->worldPositions)[wp->chainIdx[e4->chain][0]];
            b = &(*ap->worldPositions)[wp->chainIdx[e4->chain][1]];
            t = e4->t;
            s = 1.0f - t;
            if (a->y == -1000.0f || b->y == -1000.0f) {
                v = (Vec){0.0f, -1000.0f, 0.0f};
                pose->flags &= ~1;
            } else {
                PSVECScale(a, &v, t);
                PSVECScale(b, &w, s);
                PSVECAdd(&v, &w, &v);
                PSVECAdd(&v, &e4->pos, &v);
                pose->flags |= 1;
            }
            if (e4->owner != &wp->unitId) {
                for (j = 1; j < 5; j++) {
                    if (&unit->work[j + 2] == e4->owner) {
                        PSVECAdd(&v, &ofs[j], &v);
                        break;
                    }
                }
            }
            if (e4->chain >= 46) {
                pose->mtx[0][0] = pose->mtx[1][1] = wp->scale;
            }
            pose->mtx[0][3] += (v.x - pose->mtx[0][3]) / 2;
            pose->mtx[1][3] += (v.y - pose->mtx[1][3]) / 2;
            pose->mtx[2][3] += (v.z - pose->mtx[2][3]) / 2;
        }
    } else {
        wp->angle += 8.571428f;
        wp->radius -= 0.0044444446f;
        if (wp->radius < 0.8f) {
            wp->radius = 0.8f;
        }
        if (wp->angle >= 360.0f) {
            wp->angle -= 360.0f;
        }
        pose = extGetPosePtr();
        elem = wp->elems;
        for (k3 = 0; k3 < wp->count; k3++, pose++, elem++) {
            if (elem->flags & 1) {
                PSVECSubtract(&elem->vel, &wp->center, &r);
                PSMTXRotAxisRad(m, &elem->pos2, 0.017453292f * wp->angle);
                PSMTXMultVec(m, &r, &r);
                PSVECScale(&r, &r, wp->radius);
                PSVECAdd(&r, &wp->center, &r);
                pose->mtx[0][3] += (r.x - pose->mtx[0][3]) / 2;
                pose->mtx[1][3] += (r.y - pose->mtx[1][3]) / 2;
                pose->mtx[2][3] += (r.z - pose->mtx[2][3]) / 2;
            }
        }
    }
    dispEntry(CAMERA_3D, 0.0f, 1, moamoa_draw, NULL);
}

void moamoa_draw(CameraId cameraId, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

USER_FUNC(moamoa_set_bodyScale) {
    BattleUnit* unit;
    s32 n;

    unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, -2));
    n = 0;
    if (unit == NULL) {
        extReset();
        return 2;
    }
    if (unit->work[6] == -1) {
        n += 3;
    }
    if (unit->work[5] == -1) {
        n++;
    }
    if (unit->work[4] == -1) {
        n++;
    }
    if (unit->work[3] == -1) {
        n++;
    }
    wp->targetScale = 0.333f * (n - 3) + 1.0f;
    return 0;
}

