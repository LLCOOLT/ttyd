#include "version.h"
#pragma dollar_identifiers on
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_stage_object.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_eff.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"

typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
typedef struct ZakoGunWork { s32 flag; s32 targetId;
#ifdef VERSION_G8ME01
    u8 us_pad08[0xC]; // US: 12 more bytes here
#endif
    s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
extern ZakoGun* zakogun;
extern ZakoGunWork* work;
ExtPose* extGetPosePtr(void);
BattleUnit* zakogun_get_ptr(void);
s32 zakogun_get_kanbu_id(void);
void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
void zakogun_ext_init123_common(ExtPose* pose, s32 i);
void psndSFXOff(s32 id);
int rand(void);
double sqrt(double x);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(zakogun_damage_pose);
USER_FUNC(zakogun_damage_pose_cancel);
USER_FUNC(zakogun_set_target_id);
USER_FUNC(zakogun_escape3);
USER_FUNC(zakogun_dead3);
USER_FUNC(zakogun_attack3_3);
USER_FUNC(zakogun_attack3_2);
USER_FUNC(zakogun_attack3_1);
void zakogun_ext_main3(void);
USER_FUNC(zakogun_ext_init3);
USER_FUNC(zakogun_kanbu_on_ball);
extern s32 zakogun_get_kanbu_id_evtcmd[];

__declspec(section ".data") u64 negone_one$374;
__declspec(section ".data") s32 neg_one$382[1];
__declspec(section ".data") s32 __local_PI$383[1];
__declspec(section ".data") s32 __local_3PIO2$385[1];
__declspec(section ".data") u32 gap_04_000314E4_data[1];
__declspec(section ".data") u64 one_negone$373;
__declspec(section ".data") s32 __local_PIO2$384[1];
__declspec(section ".data") s32 one$381[1];
__declspec(section ".data") u64 negone_one$360;
__declspec(section ".data") s32 neg_one$365[1];
__declspec(section ".data") s32 __local_PI$366[1];
__declspec(section ".data") s32 __local_3PIO2$368[1];
__declspec(section ".data") u32 gap_04_0003150C_data[1];
__declspec(section ".data") u64 one_negone$359;
__declspec(section ".data") s32 __local_PIO2$367[1];
__declspec(section ".data") s32 one$364[1];
BattleUnitKind unit_boss_gundan_zako_group3;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") PoseTableEntry pose_table[4];
static __declspec(section ".data") BattleDataEntry data_table[3];
static BattleUnitKindPart parts[1];
s32 weapon_gundan_zako_group3_attack[48];
static s32 init_event[21];
static s32 damage_event[129];
static s32 dead_event[136];
static s32 attack_event[287];
static s32 hit_check_event[119];
static __declspec(section ".data") s32 wait_event[6];

USER_FUNC(zakogun_kanbu_on_ball) {
    BattleUnit* kanbu = BattleGetUnitPtr(_battleWorkPointer, zakogun_get_kanbu_id());
    BtlUnit_SetPos(kanbu, work->pos.x, 45.0f + work->pos.y, work->pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(zakogun_ext_init3) {
    s32 i;
    ExtPose* pose = extGetPosePtr();
    BattleUnit* kanbu;
    s32 a;
    s32 b;
    f32 dx, dy, dz, dist;

    work->flag = 2;
    for (i = 0; i < 500; i++, pose++) {
        zakogun_ext_init123_common(pose, i);
        zakogun[i].home.x = -50.0f + 20.0f * (i % 12) + (5.0f * rand() / 32767.0f - 2.5f);
        zakogun[i].home.y = 0.0f;
        zakogun[i].home.z = -80.0f + 4.0f * (i / 12) + (5.0f * rand() / 32767.0f - 2.5f);
        kanbu = BattleGetUnitPtr(_battleWorkPointer, zakogun_get_kanbu_id());
        dx = zakogun[i].home.x - kanbu->mHomePosition.x;
        dy = zakogun[i].home.y - kanbu->mHomePosition.y;
        dz = zakogun[i].home.z - kanbu->mHomePosition.z;
        dist = sqrt(dx * dx + dy * dy + dz * dz);
        if (dist <= 30.0f) {
            zakogun[i].home.x += 30.0f * (dx / dist);
            zakogun[i].home.y += 30.0f * (dy / dist);
            zakogun[i].home.z += 30.0f * (dz / dist);
        }
    }
    for (i = 0; i < 250; i++) {
        Vec tmp;
        a = irand(500);
        b = irand(500);
        tmp = zakogun[a].home;
        zakogun[a].home = zakogun[b].home;
        zakogun[b].home = tmp;
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 negone_one$374 = 0xBF8000003F800000;

__declspec(section ".data") s32 neg_one$382[] = {
    -1082130432,
};

__declspec(section ".data") s32 __local_PI$383[] = {
    1078530011,
};

__declspec(section ".data") s32 __local_3PIO2$385[] = {
    1083624420,
};

__declspec(section ".data") u32 gap_04_000314E4_data[1] = {0};

__declspec(section ".data") u64 one_negone$373 = 0x3F800000BF800000;

__declspec(section ".data") s32 __local_PIO2$384[] = {
    1070141403,
};

__declspec(section ".data") s32 one$381[] = {
    1065353216,
};

__declspec(section ".data") u64 negone_one$360 = 0xBF8000003F800000;

__declspec(section ".data") s32 neg_one$365[] = {
    -1082130432,
};

__declspec(section ".data") s32 __local_PI$366[] = {
    1078530011,
};

__declspec(section ".data") s32 __local_3PIO2$368[] = {
    1083624420,
};

__declspec(section ".data") u32 gap_04_0003150C_data[1] = {0};

__declspec(section ".data") u64 one_negone$359 = 0x3F800000BF800000;

__declspec(section ".data") s32 __local_PIO2$367[] = {
    1070141403,
};

__declspec(section ".data") s32 one$364[] = {
    1065353216,
};

BattleUnitKind unit_boss_gundan_zako_group3 = {
    102,
    "btl_un_gundan_zako_group3",
    10,
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
    260,
    52,
    0,
    52,
    0.0f,
    0.0f,
    0.0f,
    0,
    -15,
    0.0f,
    0.0f,
    0.0f,
    130.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    150.0f,
    0.0f,
    70.0f,
    130.0f,
    33.8f,
    0.0f,
    10.0f,
    10.0f,
    0.0f,
    260.0f,
    52.0f,
    0,
    0,
    -1,
    0,
    0,
    0,
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
    {49, dead_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_gundan_zako_group3", "c_zako_n", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x3000009, 0, pose_table},
};

s32 weapon_gundan_zako_group3_attack[] = {
    0, 0, 0, 0, VERSION_PICK(1677721600, 1677721602), 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536887300, 770, 0, 135, 2047, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
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
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(zakogun_damage_pose_cancel)
    RETURN
EVT_END()

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 65627, (s32)zakogun_dead3, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_1", -250000000, 0, -250000000, 65545, 48,
    110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000,
    65541, 20, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    196699, (s32)evt_sub_random, 300, -29999997, 131126, -29999997, 150, 131125,
    -30000000, -29999997, 196699, (s32)evt_sub_random, 30, -29999997, 131125, -29999999,
    -29999997, 131122, -29999998, 75, 983131, (s32)evt_eff, 0, (s32)"kemuri_test",
    4, -30000000, -29999999, -29999998, -229999181, 0, 0, 0,
    0, 0, 0, 0, 65545, 1, 6, 112,
    196699, (s32)btlevtcmd_GetCoin, -2, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -2, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999997, -29999999, -29999998, 327771, (s32)_add_star_point_disp_offset, -2, -29999997,
    -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0, -29999997,
    -29999999, -29999998, -30000000, 0, 0, 0, 0, 0,
    0, 0, 65545, 20, 262235, (s32)btlevtcmd_CheckDamageCode, -2, 1024,
    -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_KillUnit, -2, 0,
    32, 196699, (s32)btlevtcmd_KillUnit, -2, 2, 33, 2, 1,
};

static s32 attack_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 131122, -29999991, (s32)weapon_gundan_zako_group3_attack,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 131163, (s32)zakogun_get_kanbu_id_evtcmd,
    -29999995, 196699, (s32)btlevtcmd_CheckActStatus, -29999995, -29999988, 131097, -29999988, 0,
    131163, (s32)zakogun_get_kanbu_id_evtcmd, -29999995, 65647, -29999985, 65545, 10, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"W_1", 327771, (s32)btlevtcmd_GetPos, -29999995, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999995, -30000000, 50, 524379,
    (s32)btlevtcmd_MovePosition, -29999995, -30000000, -29999999, -29999998, 60, -1, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"S_1", 112, 33, 110,
    65545, 32, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_TEAM_3RD_ADHERE1", 0, 112, 65627,
    (s32)zakogun_attack3_1, 131097, -29999988, 0, 65631, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999995, 1, (s32)"A_1A", 393307, (s32)btlevtcmd_snd_se, -29999995, (s32)"SFX_BOSS_KANBU_JUMP1", -250000000,
    0, -29999987, 327771, (s32)btlevtcmd_JumpSetting, -29999995, 0, -229993856, -229999693,
    458843, (s32)btlevtcmd_JumpPosition, -29999995, 0, 100, 0, 0, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"S_1", 131163, (s32)evt_snd_sfxoff, -29999987,
    33, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131163, (s32)zakogun_set_target_id, -29999997,
    131097, -29999988, 0, 65647, -29999986, 131163, (s32)zakogun_get_kanbu_id_evtcmd, -29999995,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"R_2", 65541, 0, 65627,
    (s32)zakogun_kanbu_on_ball, 65545, 1, 6, 112, 33, 110, 65630,
    (s32)hit_check_event, 112, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_TEAM_3RD_ROUND1", -29999987, 131163, (s32)zakogun_attack3_2,
    -29999987, 131097, -29999988, 0, 65631, -29999986, 65631, -29999985,
    33, 131097, -29999988, 0, 107, 131163, (s32)zakogun_get_kanbu_id_evtcmd, -29999995,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"A_1A", 327771, (s32)btlevtcmd_GetPos, -29999995,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting, -29999995, 30, 0,
    -229999693, 458843, (s32)btlevtcmd_JumpPosition, -29999995, -30000000, 0, -29999998, 30,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"S_1", 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -29999995, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"R_1", 327771,
    (s32)btlevtcmd_GetHomePos, -29999995, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -29999995,
    -229993856, 524379, (s32)btlevtcmd_MovePosition, -29999995, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -29999995, 1, (s32)"S_1", 131163,
    (s32)btlevtcmd_ResetFaceDirection, -29999995, 109, 33, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BOSS_TEAM_3RD_ADHERE2", 0,
    65627, (s32)zakogun_attack3_3, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

void zakogun_ext_main3(void) {
    s32 i;
    BattleUnit* unit = zakogun_get_ptr();
    ExtPose* pose = extGetPosePtr();
    ZakoGun* zako;
    f32 left;
    f32 top;
    f32 dx;
    f32 dy;
    Mtx m;
    Mtx m2;

    for (i = 0; i < 500; i++, pose++) {
        zako = &zakogun[i];
        pose->frame = zako->poseBase + zako->poseCount / zako->poseDiv;
        zako->poseCount++;
        if (zako->poseCount >= zako->poseNum * zako->poseDiv) {
            zako->poseCount = 0;
        }
        switch (zako->state) {
            case 0:
                zako->state = 3;
                zako->timer = 0;
                zako->rot.x = zako->rot.y = zako->rot.z = 0.0f;
                zakogun_set_pose(zako, 0, 20, 2);
                break;
            case 3:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 5;
                    zako->timer = 0;
                }
                break;
            case 5:
                zako->start.x = 300.0f;
                zako->start.y = 0.0f;
                zako->start.z = -75.0f + 150.0f * rand() / 32767.0f;
                zako->timerMax = zako->timer = irand(30) + 60;
                zako->state = 10;
                zakogun_set_pose(zako, 0x16, 10, 1);
            case 10:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->home.x);
                zako->pos.y = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.y, zako->home.y);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->home.z);
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 15;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 15:
                zako->pos.x = zako->home.x + (unit->mPosition.x - unit->mHomePosition.x);
                zako->pos.y = zako->home.y;
                if (zako->pos.y < unit->mPosition.y) {
                    zako->pos.y = unit->mPosition.y;
                }
                zako->pos.z = zako->home.z;
                break;
            case 20:
                if (i >= 0 && i < 484) {
                    left = work->pos.x - work->radius;
                    top = work->pos.y + work->radius;
                    zako->target.x = left + (i % 22) * (2.0f * work->radius / 22.0f);
                    zako->target.y = top - (i / 22) * (2.0f * work->radius / 22.0f);
                    zako->target.z = work->pos.z + rand() / 32767.0f - 0.5f;
                    dx = work->pos.x - zako->target.x;
                    dy = work->pos.y - zako->target.y;
                    if ((f32)sqrt(dx * dx + dy * dy) > work->radius) {
                        zako->target.x = work->pos.x;
                        zako->target.y = work->pos.y;
                        zako->target.z = work->pos.z - 10.0f;
                    }
                } else {
                    zako->target.x = work->pos.x;
                    zako->target.y = work->pos.y;
                    zako->target.z = work->pos.z - 10.0f;
                }
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
                zako->state = 25;
                zako->timer = zako->target.y;
            case 25:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 30;
                    zako->timerMax = zako->timer = 30;
                    zakogun_set_pose(zako, 0x22, 1, 1);
                }
                break;
            case 30:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 35;
                    zako->pos.y = zako->target.y;
                    zako->rot.z = 360.0f * rand() / 32767.0f;
                    zako->ofs.x = zako->pos.x - work->pos.x;
                    zako->ofs.y = zako->pos.y - work->pos.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                    work->count++;
                }
                break;
            case 35:
                if (work->count == 500) {
                    zako->state = 40;
                }
                break;
            case 50:
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->target.x = 200.0f * rand() / 32767.0f - 100.0f;
                zako->target.y = 0.0f;
                zako->target.z = 150.0f * rand() / 32767.0f - 75.0f;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
                zako->rot.z = 0.0f;
                zako->state = 55;
                zako->timer = zako->timerMax = 20;
                zakogun_set_pose(zako, 0x22, 1, 1);
            case 55:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 60;
                    zako->pos.y = zako->target.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 60:
                zako->start.x = zako->pos.x;
                zako->start.z = zako->pos.z;
                zako->timerMax = zako->timer = irand(30) + 30;
                zako->state = 65;
                zakogun_set_pose(zako, 0x16, 10, 1);
            case 65:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->home.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->home.z);
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 15;
                    zako->pos.y = zako->home.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 80:
                zako->rot.y = 0.0f;
                zako->timer = irand(5) + 48;
                zako->state = 82;
            case 82:
                if (zako->timer <= 48) {
                    zako->rot.y -= 15.0f;
                }
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->rot.y = 0.0f;
                    zako->state = 85;
                }
                break;
            case 85:
                zako->rot.x += 3.0f;
                if (zako->rot.x >= 90.0f) {
                    zako->state = -1;
                    {
                        Vec hide = {0.0f, -1000.0f, 0.0f};
                        zako->pos = hide;
                    }
                }
                break;
            case 90:
                zako->rot.y = 180.0f;
                zako->pos.x += 5.0f;
                if (zako->pos.x >= 300.0f) {
                    zako->state = -1;
                    zako->rot.y = 0.0f;
                }
                break;
        }
        if (zako->state >= 35 && zako->state <= 40) {
            PSMTXIdentity(pose->mtx);
            PSMTXRotRad(m, 'z', 0.017453292f * zako->rot.z);
            PSMTXConcat(pose->mtx, m, pose->mtx);
            pose->mtx[0][3] = zako->ofs.x;
            pose->mtx[1][3] = zako->ofs.y;
            pose->mtx[2][3] = work->pos.z + 0.05f * i;
            PSMTXRotRad(m, 'z', 0.017453292f * work->angle);
            PSMTXConcat(m, pose->mtx, pose->mtx);
            pose->mtx[0][3] += work->pos.x;
            pose->mtx[1][3] += work->pos.y;
            pose->mtx[2][3] += work->pos.z;
            zako->pos.x = pose->mtx[0][3];
            zako->pos.y = pose->mtx[1][3];
            zako->pos.z = pose->mtx[2][3];
        } else {
            PSMTXIdentity(pose->mtx);
            PSMTXRotRad(m2, 'x', 0.017453292f * zako->rot.x);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            PSMTXRotRad(m2, 'y', 0.017453292f * zako->rot.y);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            PSMTXRotRad(m2, 'z', 0.017453292f * zako->rot.z);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            pose->mtx[0][3] = zako->pos.x;
            pose->mtx[1][3] = zako->pos.y;
            pose->mtx[2][3] = zako->pos.z + 0.03f * i;
        }
    }
}

USER_FUNC(zakogun_attack3_1) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        Vec pos = {0.0f, 55.0f, 0.0f};
        work->pos = pos;
        work->radius = 25.0f;
        work->angle = 0.0f;
        work->count = 0;
        for (i = 0; i < 500; i++) {
            zakogun[i].state = 20;
        }
    }
    for (i = 0, n = 0; i < 500; i++) {
        if (zakogun[i].state == 40) {
            n++;
        }
    }
    return n == 500 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(zakogun_attack3_2) {
    BattleUnit* unit = zakogun_get_ptr();
    s32 sfx = evtGetValue(event, event->args[0]);

    if (isFirstCall) {
        work->count = 0;
        work->state = 0;
    }
    switch (work->state) {
        case 0:
            work->state = 5;
            work->speed = 0.0f;
        case 5:
            work->pos.x += work->speed;
            work->angle -= work->speed;
            work->speed -= 0.06f;
            if (work->targetId != -1) {
                BattleUnit* target = BattleGetUnitPtr(_battleWorkPointer, work->targetId);
                if (work->pos.x <= target->mPosition.x) {
                    unit->work[0] = 1;
                }
            }
            if (work->pos.x <= -200.0f) {
                work->state = 8;
            }
            break;
        case 8:
            work->pos.x += work->speed;
            work->angle -= work->speed;
            work->speed += 5.0f;
            if (work->speed >= 0.0f) {
                work->state = 10;
            }
            break;
        case 10:
            work->pos.x += work->speed;
            work->angle -= work->speed;
            work->speed += 0.06f;
            if (work->pos.x >= -30.0f) {
                work->state = 13;
            }
            break;
        case 13:
            work->pos.x += work->speed;
            work->angle -= work->speed;
            work->speed -= 1.0f;
            if (work->speed <= 0.0f) {
                work->state = 15;
                psndSFXOff(sfx);
                work->timer = 20;
            }
            break;
        case 15:
            work->timer--;
            if (work->timer < 0) {
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(zakogun_attack3_3) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        for (i = 0; i < 500; i++) {
            zakogun[i].state = 50;
        }
    }
    for (i = 0, n = 0; i < 500; i++) {
        if (zakogun[i].state == 15) {
            n++;
        }
    }
    return n == 500 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(zakogun_dead3) {
    s32 i;

    for (i = 0; i < 500; i++) {
        zakogun[i].state = 80;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(zakogun_escape3) {
    s32 i;
    s32 n;

    if (isFirstCall) {
        for (i = 0; i < 500; i++) {
            ZakoGun* zako = &zakogun[i];
            zako->state = 90;
            zakogun_set_pose(zako, 0x16, 10, 1);
        }
    }
    for (i = 0, n = 0; i < 500; i++) {
        if (zakogun[i].state == -1) {
            n++;
        }
    }
    return n == 500 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

static EVT_BEGIN(hit_check_event)
    LABEL(10)
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
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    IF_INT_NOT_EQUAL(LW(3), -1)
        CALL(zakogun_set_target_id, LW(3))
        GOTO(10)
        ELSE
        CALL(zakogun_set_target_id, -1)
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

