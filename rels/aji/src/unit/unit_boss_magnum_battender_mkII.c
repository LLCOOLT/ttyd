#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "driver/effdrv.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "manager/evtmgr.h"
#include "dolphin/mtx.h"
#include "eff/n64/eff_akari_charge_n64.h"
#include "battle/battle_audience.h"
#include "evt/evt_cmd.h"
#include "eff/eff_kemu_test.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_batstage.h"
#include "evt/evt_eff.h"
#include "party/party_motion.h"

typedef struct ArmWork { Vec prevPos; Vec pos; f32 rot; f32 targetRot; EffectEntry* eff; } ArmWork;
double atan(double x);
typedef struct BattenEffWork { s32 field_0x0; Vec pos; u8 field_0x10[0x28 - 0x10]; Mtx mtx; } BattenEffWork;
EffectEntry* effBattenEntry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
typedef struct TargetWork { s32 state; s32 count; EffectEntry* eff; } TargetWork;
f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
s32 psndSFXOn(const char* name);
void psndSFXOff(s32 id);
typedef struct AudMember { s32 flags; s32 field_0x4; s32 field_0x8; u8 field_0xC[0x48 - 0xC]; Vec position; u8 field_0x54[0x60 - 0x54]; Vec scale; u8 field_0x6C[0x9C - 0x6C]; Vec rotation; u8 field_0xA8[0xB4 - 0xA8]; Vec home; u8 field_0xC0[0xF8 - 0xC0]; s32 frame; s32 frames; } AudMember;
s32 irand(s32 scalar);
int rand(void);
extern s32 aud_hit_event[];
void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);
void aud_fire_eff(f32 x, f32 y, f32 z);
void effKemuTestSetRxRz(EffectEntry* eff, f32 rx, f32 rz);
u8 psndSFX_get_vol(s32 id);
void psndSFX_vol(s32 id, u8 vol);
EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 rot, f32 scale1, f32 scale2);
EffectEntry* effKamekiTornadeN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
EffectEntry* eff_tor;
s32 torCount;
EffectEntry* eff_jet[2];
s32 jetCount;
static s32* list;
EffectEntry* eff_suikomi;
s32 screamId;
s32 scream_fade_timer;
u8 scream_fade_start_vol;
u8 scream_fade_vol;
TargetWork* wp_target;
s32 targetSoundId;
static EffectEntry* eff_charge;
static ArmWork* work[2];

static USER_FUNC(arm_check);
static USER_FUNC(arm_end);
static USER_FUNC(arm_init);
static USER_FUNC(arm_main);
USER_FUNC(btlevtcmd_AddUnitWork);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckDamageCode);
USER_FUNC(btlevtcmd_CheckDamagePattern);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_SetBaseRotate);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetStayPoseType);
USER_FUNC(btlevtcmd_SetTalkPoseType);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(evt_audience_delete);
USER_FUNC(evt_audience_jump_position_gravity);
USER_FUNC(evt_audience_move_position_frame);
USER_FUNC(evt_audience_num_updown_in_event);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveto);
USER_FUNC(evt_btl_camera_set_prilimit);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_battle_party);
USER_FUNC(evt_sub_random);
USER_FUNC(get_aud_num);
static USER_FUNC(waku_main);
static USER_FUNC(arm_init2);
static USER_FUNC(eff_dead_delete);
static USER_FUNC(eff_dead);
USER_FUNC(aud_target_mark);
USER_FUNC(aud_fire_no_hit);
USER_FUNC(aud_fire_hit);
void aud_fire_eff(f32 x, f32 y, f32 z);
void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);
USER_FUNC(aud_scream_fadeout);
USER_FUNC(aud_suikomi);
USER_FUNC(aud_jet_end);
USER_FUNC(aud_jet);
USER_FUNC(drill_jet);
USER_FUNC(drill_tor);

__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_negone_one_374;
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_one_negone_373;
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_one_381[1];
__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_negone_one_360;
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_one_negone_359;
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_one_364[1];
BattleUnitKind unit_boss_magnum_battender_mkII;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_no_arm[16];
static __declspec(section ".data") BattleDataEntry data_table[2];
static BattleUnitKindPart parts[4];
s32 weapon_batten_drill_attack[48];
s32 weapon_batten_boomerang_attack[48];
s32 weapon_batten_aud_attack[48];
static __declspec(section ".data") s32 entry_rocket_punch[12];
s32 aud_hit_event[24];
s32 aud_no_hit_event[16];
static s32 init_event[92];
static s32 waku_event[23];
static s32 damage_event[111];
static s32 dead_event[234];
static s32 entry_event[78];
static s32 attack_event[320];
s32 drill_attack_event[392];
s32 boomerang_attack_event[324];
s32 aud_attack_event[823];
s32 aud_attack_event_sub[139];
static s32 arm_bunri_event[199];
static s32 arm_return_event[151];
static __declspec(section ".data") s32 wait_event[6];
BattleUnitKind unit_boss_rocket_punch_mkII;
static __declspec(section ".data") BattleUnitDefense defence_r;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_r;
static __declspec(section ".data") StatusVulnerability regist_r;
static PoseTableEntry pose_table_r[14];
static __declspec(section ".data") BattleDataEntry data_table_r[1];
static BattleUnitKindPart parts_r[1];
static s32 weapon_batten_rocket_attack[48];
static s32 init_event_r[191];
static s32 arm_event[59];
static s32 arm_event_end[35];
static s32 damage_event_r[30];
static s32 attack_event_r[368];
static s32 wait_event_r[18];

__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_magnum_battender_mkII_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_magnum_battender_mkII_one_364[] = {
    1065353216,
};

BattleUnitKind unit_boss_magnum_battender_mkII = {
    121,
    "btl_un_magnum_battender_mkii",
    70,
    0,
    1,
    1,
    84,
    0,
    0,
    100,
    0,
    50,
    6,
    120,
    160,
    30,
    100,
    0.0f,
    80.0f,
    0.0f,
    0,
    0,
    30.0f,
    115.0f,
    0.0f,
    60.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    52.0f,
    0.0f,
    0.0f,
    30.0f,
    110.0f,
    20.0f,
    0.0f,
    80.0f,
    0.0f,
    120.0f,
    160.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MBTN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    4,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{2, 2, 2, 2, 2}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 40, 40, 0, 40, 0, 100, 20, 0, 0, 100, 0, 100, 80, 40, 0, 0, 100, 30, 0, 0, 0};

static PoseTableEntry pose_table[] = {
    {1, "MGN_S_1"},
    {2, "MGN_2D_1"},
    {9, "MGN_2D_1"},
    {5, "MGN_X_1"},
    {4, "MGN_X_1"},
    {3, "MGN_X_1"},
    {28, "MGN_S_1"},
    {29, "MGN_Q_1"},
    {30, "MGN_Q_1"},
    {31, "MGN_S_1"},
    {39, "MGN_D_1"},
    {40, "MGN_W_1"},
    {41, "MGN_W_2"},
    {56, "MGN_S_1"},
    {57, "MGN_S_1"},
    {65, "MGN_T_1"},
    {69, "MGN_S_1"},
};

static PoseTableEntry pose_table_no_arm[] = {
    {1, "MGN_S_2"},
    {2, "MGN_2D_2"},
    {9, "MGN_2D_2"},
    {5, "MGN_X_2"},
    {4, "MGN_X_2"},
    {3, "MGN_X_2"},
    {28, "MGN_S_2"},
    {29, "MGN_Q_2"},
    {30, "MGN_Q_2"},
    {31, "MGN_S_2"},
    {39, "MGN_D_2"},
    {40, "MGN_W_3"},
    {56, "MGN_S_2"},
    {57, "MGN_S_2"},
    {65, "MGN_T_2"},
    {69, "MGN_S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
#ifdef VERSION_G8ME01
    {1, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, 0x600019, 0, pose_table},
#else
    {1, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 37.0f, 103.0f, 30.0f, 37.0f, 113.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
#endif
    {2, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 10.0f, 10.0f, 30.0f, 10.0f, 20.0f, 61.0f, 106, 174, 255, &defence, &defence_attr, 0x3100002, 0, pose_table},
    {3, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, 0x12010000, 0, pose_table},
    {4, "btl_un_magnum_battender_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

s32 weapon_batten_drill_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 135, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_boomerang_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 135, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_batten_aud_attack[] = {
#ifdef VERSION_G8ME01
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#else
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
#endif
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_rocket_punch[] = {
    (s32)&unit_boss_rocket_punch_mkII, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

EVT_BEGIN(aud_hit_event)
    CALL(evt_audience_move_position_frame, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_audience_jump_position_gravity, LW(0), LW(6), LW(7), LW(8), LW(9), LW(10))
    CALL(evt_audience_delete, LW(0))
    CALL(evt_audience_num_updown_in_event, FLOAT(-1.0f))
    RETURN
EVT_END()

EVT_BEGIN(aud_no_hit_event)
    CALL(evt_audience_move_position_frame, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(evt_audience_delete, LW(0))
    CALL(evt_audience_num_updown_in_event, FLOAT(-1.0f))
    RETURN
EVT_END()

static USER_FUNC(waku_main) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleUnitPart* waku;
    s32 poseId;
    AnimationPose* pose;
    s32 idx;
    f32 yaw;

    animGetPtr();
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    part = BtlUnit_GetPartsPtr(unit, 1);
    waku = BtlUnit_GetPartsPtr(unit, 3);
    poseId = part->poseId;
    animPoseWorldPositionEvalOn(poseId);
    animPoseGetAnimBaseDataPtr(poseId);
    pose = animPoseGetAnimPosePtr(poseId);
    idx = animPoseGetGroupIdx(poseId, "locator17\0\0");
    BtlUnit_SetPartsPos(waku, (*pose->worldPositions)[idx].x, (*pose->worldPositions)[idx].y,
                        (*pose->worldPositions)[idx].z);
    yaw = camGetPtr(CAMERA_3D)->viewYaw;
    BtlUnit_SetPartsRotate(waku, 0.0f, -yaw, 0.0f);
    return EVT_RETURN_DONE;
}

static USER_FUNC(arm_check) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 side = evtGetValue(event, args[0]);
    s32 found = -1;
    BattleUnit* unit;
    s32 i;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == UNIT_X_FIST || unit->currentKind == UNIT_X_PUNCH)) {
            if (side == 0 && (unit->work[0] == 0 || unit->work[0] == 2)) {
                found = i;
                break;
            }
            if (side == 1 && (unit->work[0] == 1 || unit->work[0] == 3)) {
                found = i;
                break;
            }
        }
    }
    evtSetValue(event, args[1], found);
    return EVT_RETURN_DONE;
}

USER_FUNC(drill_tor) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        eff_tor = effKamekiTornadeN64Entry(0, 1000, 0.0f, -1000.0f, 0.0f, 3.5f);
        torCount = 0;
    }
    if (y <= 300.0f) {
        ((BattenEffWork*)eff_tor->userdata)->pos.x = x;
        ((BattenEffWork*)eff_tor->userdata)->pos.y = y - 240.0f;
        ((BattenEffWork*)eff_tor->userdata)->pos.z = z;
    }
    if (++torCount >= 70) {
        effDelete(eff_tor);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(drill_jet) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BattenEffWork* ew;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        for (i = 0; i < 2; i++) {
            eff_jet[i] = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 3.0f);
        }
        jetCount = 0;
    }
    ew = eff_jet[0]->userdata;
    ew->pos.x = x - 20.0f;
    ew->pos.y = y;
    ew->pos.z = z - 20.0f;
    ew = eff_jet[1]->userdata;
    ew->pos.x = 20.0f + x;
    ew->pos.y = y;
    ew->pos.z = 20.0f + z;
    if (++jetCount >= 90) {
        for (i = 0; i < 2; i++) {
            effDelete(eff_jet[i]);
        }
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(aud_jet) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    Mtx mtx;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BattenEffWork* ew;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        for (i = 0; i < 2; i++) {
            eff_jet[i] = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 3.0f);
        }
        jetCount = 0;
    }
    PSMTXRotRad(mtx, 'z', -0.34906584f);
    ew = eff_jet[0]->userdata;
    ew->pos.x = x - 60.0f;
    ew->pos.y = 22.5f + y;
    ew->pos.z = z;
    PSMTXCopy(mtx, ((BattenEffWork*)eff_jet[0]->userdata)->mtx);
    ew = eff_jet[1]->userdata;
    ew->pos.x = x - 15.0f;
    ew->pos.y = 22.5f + y;
    ew->pos.z = 70.0f + z;
    PSMTXCopy(mtx, ((BattenEffWork*)eff_jet[1]->userdata)->mtx);
    if (jetCount == 1) {
        for (i = 0; i < 2; i++) {
            effDelete(eff_jet[i]);
        }
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(aud_jet_end) {
    jetCount = 1;
    return EVT_RETURN_DONE;
}

USER_FUNC(get_aud_num) {
    s32* args = event->args;

    evtSetValue(event, args[0], BattleAudience_GetAudienceNum());
    return EVT_RETURN_DONE;
}

USER_FUNC(aud_suikomi) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    s32 done = 0;
    AudMember* mem;
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    f32 x2;
    f32 y2;
    f32 z2;
    s32 ids[200];

    if (isFirstCall) {
        s32 n = 0;

        if (list != NULL) {
            BattleFree(list);
        }
        list = BattleAlloc(sizeof(s32) * 20);
        for (i = 0; i < 200; i++) {
            if ((u8)BattleAudience_GetExist(i) == TRUE) {
                ids[n] = i;
                n++;
            }
        }
        for (i = 0; i < 1000; i++) {
            s32 a = irand(n);
            s32 b = irand(n);
            s32 tmp = ids[a];

            ids[a] = ids[b];
            ids[b] = tmp;
        }
        for (i = 0; i < 20; i++) {
            mem = (AudMember*)BattleAudienceGetPtr(ids[i]);
            mem->flags |= 0x10;
            BattleAudience_SetAnim(ids[i], 9, FALSE);
            mem->frames = i * 3 + 60;
            mem->field_0x8 = 0;
            mem->rotation.y = 0.0f;
            list[i] = ids[i];
        }
        BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        eff_suikomi = effKumokumoN64Entry(2, 120, x - 10.0f, 10.0f + y, z, -40.0f, 1.0f, 1.5f);
        screamId = psndSFXOn("SFX_AUDIENCE_PANIC_SCREAM1");
    }
    BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, id), &x2, &y2, &z2);
    y2 += 5.0f;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 20; j++) {
            if (i == list[j]) {
                mem = (AudMember*)BattleAudienceGetPtr(i);
                mem->rotation.y += 19.0f;
                if (mem->frame < mem->frames) {
                    mem->frame++;
                } else {
                    done++;
                    mem->flags &= ~4;
                    mem->flags |= 2;
                }
                mem->position.x = intplGetValue(mem->home.x, x2, 4, mem->frame, mem->frames);
                mem->position.y = intplGetValue(mem->home.y, y2, 2, mem->frame, mem->frames);
                mem->position.z = intplGetValue(mem->home.z, z2, 4, mem->frame, mem->frames);
                mem->scale.x = mem->scale.y = intplGetValue(1.0f, 0.65f, 4, mem->frame, mem->frames);
                break;
            }
        }
    }
    return done < 20 ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

USER_FUNC(aud_scream_fadeout) {
    if (isFirstCall) {
        scream_fade_timer = 120;
        scream_fade_start_vol = psndSFX_get_vol(screamId);
    }
    scream_fade_timer--;
    scream_fade_vol = intplGetValue(scream_fade_start_vol, 0.0f, 0, 120 - scream_fade_timer, 120);
    psndSFX_vol(screamId, scream_fade_vol);
    if (scream_fade_timer <= 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z) {
    BtlUnit_GetPos(unit, x, y, z);
    *x += 10.0f;
    *y += 78.0f;
}

void aud_fire_eff(f32 x, f32 y, f32 z) {
    effKemuTestSetRxRz(effKemuTestEntry(11, x - 50.0f, 20.0f + y, 50.0f + z, 0.75f), 40.0f, 110.0f);
}

USER_FUNC(aud_fire_hit) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 target = BattleTransID(event, evtGetValue(event, args[1]));
    s32 start = evtGetValue(event, args[2]);
    BattleUnit* unit;
    BattleUnitPart* part;
    AudMember* mem;
    EventEntry* evt;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;

    if (isFirstCall) {
        aud_get_pod_pos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        aud_fire_eff(x, y, z);
        unit = BattleGetUnitPtr(_battleWorkPointer, target);
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        BtlUnit_GetHitPos(unit, part, &hx, &hy, &hz);
        for (i = start; i < start + 2; i++) {
            mem = (AudMember*)BattleAudienceGetPtr(list[i]);
            BattleAudience_SetAnim(list[i], 9, FALSE);
            mem->position = (Vec){x, y, z};
            mem->frames = 0;
            mem->field_0x8 = 0;
            mem->rotation.y = 0.0f;
            mem->scale.x = mem->scale.y = 1.0f;
            mem->flags |= 4;
            evt = evtEntry(aud_hit_event, 0, 0x20);
            evt->lwData[0] = list[i];
            evt->lwData[1] = (s32)(1024.0f * hx) - EVTDAT_FLOAT_BASE;
            evt->lwData[2] = (s32)(1024.0f * hy) - EVTDAT_FLOAT_BASE;
            evt->lwData[3] = (s32)(1024.0f * hz) - EVTDAT_FLOAT_BASE;
            evt->lwData[4] = 0;
            evt->lwData[5] = irand(3) + 10;
            evt->lwData[6] = (s32)(1024.0f * (hx + 200.0f * rand() / 32767.0f - 100.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[7] = FLOAT(-100.0f);
            evt->lwData[8] = (s32)(1024.0f * (hz + 100.0f * rand() / 32767.0f - 50.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[9] = irand(30) + 30;
            evt->lwData[10] = FLOAT(-0.3f);
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(aud_fire_no_hit) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 target = BattleTransID(event, evtGetValue(event, args[1]));
    s32 start = evtGetValue(event, args[2]);
    BattleUnit* unit;
    BattleUnitPart* part;
    AudMember* mem;
    EventEntry* evt;
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;

    if (isFirstCall) {
        aud_get_pod_pos(BattleGetUnitPtr(_battleWorkPointer, id), &x, &y, &z);
        aud_fire_eff(x, y, z);
        unit = BattleGetUnitPtr(_battleWorkPointer, target);
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        BtlUnit_GetHitPos(unit, part, &hx, &hy, &hz);
        for (i = start; i < start + 2; i++) {
            mem = (AudMember*)BattleAudienceGetPtr(list[i]);
            BattleAudience_SetAnim(list[i], 9, FALSE);
            mem->position = (Vec){x, y, z};
            mem->frames = 0;
            mem->field_0x8 = 0;
            mem->rotation.y = 0.0f;
            mem->scale.x = mem->scale.y = 1.0f;
            mem->flags |= 4;
            evt = evtEntry(aud_hit_event, 0, 0x20);
            evt->lwData[0] = list[i];
            evt->lwData[1] = FLOAT(-275.0f);
            evt->lwData[2] = (s32)(1024.0f * (hy - 20.0f)) - EVTDAT_FLOAT_BASE;
            evt->lwData[3] = (s32)(1024.0f * hz) - EVTDAT_FLOAT_BASE;
            evt->lwData[4] = 0;
            evt->lwData[5] = irand(3) + 10;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(aud_target_mark) {
    s32* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    BattenEffWork* ew;

    if (isFirstCall) {
        wp_target = BattleAlloc(sizeof(TargetWork));
        wp_target->eff = effBattenEntry(1, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
        wp_target->state = 0;
        wp_target->count = 0;
        targetSoundId = psndSFXOn("SFX_BOSS_MBTN_SEARCH1");
    }
    ew = wp_target->eff->userdata;
    switch (wp_target->state) {
        case 0:
            wp_target->count++;
            ew->pos.x = intplGetValue(60.0f + x, x - 5.0f, 4, wp_target->count, 60);
            ew->pos.y = intplGetValue(20.0f + y, 60.0f + y, 4, wp_target->count, 60);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 60) {
                wp_target->state = 5;
                wp_target->count = 0;
            }
            break;
        case 5:
            wp_target->count++;
            ew->pos.x = intplGetValue(x - 5.0f, x - 25.0f, 4, wp_target->count, 40);
            ew->pos.y = intplGetValue(60.0f + y, 20.0f + y, 4, wp_target->count, 40);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 40) {
                wp_target->state = 10;
                wp_target->count = 0;
            }
            break;
        case 10:
            wp_target->count++;
            ew->pos.x = intplGetValue(x - 25.0f, x, 4, wp_target->count, 20);
            ew->pos.y = intplGetValue(20.0f + y, y, 4, wp_target->count, 20);
            ew->pos.z = 20.0f + z;
            if (wp_target->count >= 20) {
                wp_target->state = 15;
                wp_target->count = 0;
                effDelete(wp_target->eff);
                wp_target->eff = effBattenEntry(2, 1000, x, y, 10.0f + z, 1.0f);
                psndSFXOff(targetSoundId);
                psndSFXOn("SFX_BOSS_MBTN_LOCKON1");
            }
            break;
        case 15:
            wp_target->count++;
            if (wp_target->count >= 90) {
                effDelete(wp_target->eff);
                BattleFree(wp_target);
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(eff_dead) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    eff_charge = effAkariChargeN64Entry(0, 1000, x, y, z, 1.5f);
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_dead_delete) {
    effDelete(eff_charge);
    return EVT_RETURN_DONE;
}

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_OnUnitFlag, -2, 16777216)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("MGN_L_1"))
    SPAWN_EVENT(PTR(waku_event))
    CALL(arm_init)
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_SetHomePos, -2, 125, 0, 0)
    CALL(btlevtcmd_SetPos, -2, 125, 0, 0)
    CALL(btlevtcmd_SetBaseRotate, -2, 0, -55, 0)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 26, 26, 26)
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_BOSS_MBTN_MOVE1"), STRING("SFX_BOSS_MBTN_MOVE1"), 20, 20, 20)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(waku_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(waku_main, -2)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_CheckDamagePattern, -2, 10, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_OffPartsAttribute, -2, 3, 16777216)
    CALL(btlevtcmd_GetUnitWork, -2, 6, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 14)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(btlevtcmd_SetUnitWork, -2, 6, 1)
            CALL(btlevtcmd_StatusWindowOnOff, 0)
            CALL(evt_btl_camera_set_prilimit, 1)
            CALL(evt_btl_camera_set_mode, 1, 3)
            CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 20)
            CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
            WAIT_FRAMES(20)
            CALL(btlevtcmd_SetTalkPoseType, -2, 65)
            CALL(btlevtcmd_SetStayPoseType, -2, 69)
            CALL(evt_msg_print, 2, STRING("stg7_aji_41_06"), 0, -2)
            CALL(evt_btl_camera_set_prilimit, 0)
            CALL(evt_btl_camera_set_mode, 0, 0)
            CALL(btlevtcmd_StatusWindowOnOff, 1)
            WAIT_MS(500)
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 dead_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 6, 1, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -29999999, 70, 131125, -29999998,
    10, 262235, (s32)eff_dead, -30000000, -29999999, -29999998, 65627, (s32)btlevtcmd_WaitAttackEnd,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_btl_camera_set_mode,
    1, 3, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131126, -30000000, 20, 655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 160,
    600, -30000000, 110, -100, 20, 11, 65545, 20,
    196699, (s32)btlevtcmd_SetTalkPoseType, -2, 39, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 39,
    327771, (s32)evt_msg_print, 2, (s32)"stg7_aji_41_07", 0, -2, 131163, (s32)evt_btl_camera_set_prilimit,
    0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    65546, 500, 196699, (s32)arm_check, 0, -30000000, 131097, -30000000,
    -1, 262235, (s32)btlevtcmd_CheckDamageCode, -30000000, 512, -29999999, 131096, -29999999,
    0, 131122, -29999990, -30000000, 107, 65630, (s32)subsetevt_dead_core, 131163,
    (s32)arm_end, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 16777216, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 33554432, 109, 33, 33, 196699,
    (s32)arm_check, 1, -30000000, 131097, -30000000, -1, 262235, (s32)btlevtcmd_CheckDamageCode,
    -30000000, 512, -29999999, 131096, -29999999, 0, 131122, -29999990,
    -30000000, 107, 65630, (s32)subsetevt_dead_core, 131163, (s32)arm_end, 1, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1,
    33554432, 109, 33, 33, 131122, -29999990, -2, 393307,
    (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000, 0, -250000000, 196699, (s32)btlevtcmd_GetCoin,
    -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990,
    -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997,
    -29999999, -29999998, 131125, -29999998, 50, 131125, -29999999, 30,
    327771, (s32)_add_star_point_disp_offset, -29999990, -29999997, -29999999, -29999998, 983131, (s32)evt_eff,
    (s32)"", (s32)"star_point", 0, -29999997, -29999999, -29999998, -30000000, 0,
    0, 0, 0, 0, 0, 0, 131101, -30000000,
    1, 65541, -30000000, 6, 33, 65545, 120, 131163,
    (s32)btlevtcmd_GetBackItem, -29999990, 196699, (s32)btlevtcmd_KillUnit, -29999990, 1, 65627, (s32)eff_dead_delete,
    2, 1,
};

static EVT_BEGIN(entry_event)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_StatusWindowOnOff, 0)
    CALL(evt_btl_camera_set_prilimit, 1)
    CALL(evt_btl_camera_set_mode, 1, 3)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 20)
    CALL(evt_btl_camera_set_moveto, 1, LW(0), 160, 600, LW(0), 110, -100, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print, 2, STRING("stg7_aji_41_00"), 0, -2)
    CALL(evt_btl_camera_set_moveto, 1, -102, 83, 334, -102, 59, 0, 20, 11)
    WAIT_FRAMES(20)
    CALL(evt_msg_print_battle_party, STRING("stg7_aji_41_01"))
    CALL(evt_btl_camera_set_prilimit, 0)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_StatusWindowOnOff, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_GetBodyId, -4, LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, -4, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_check, 0, LW(0))
        IF_INT_EQUAL(LW(0), -1)
            CALL(arm_check, 1, LW(0))
            IF_INT_EQUAL(LW(0), -1)
                CALL(btlevtcmd_AddUnitWork, -2, 1, -1)
                CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
                IF_INT_LESS_OR_EQUAL(LW(0), 0)
                    CALL_CHILD(PTR(arm_return_event))
                END_IF
            END_IF
        END_IF
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(drill_attack_event))
            GOTO(99)
        END_IF
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_GREATER(LW(0), 63)
            CALL_CHILD(PTR(drill_attack_event))
            GOTO(99)
            ELSE
            CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL_CHILD(PTR(arm_bunri_event))
                GOTO(99)
            END_IF
            CALL(btlevtcmd_GetHp, -2, LW(0))
            IF_INT_GREATER(LW(0), 35)
                SET_VALUE(LW(0), 0)
                ADD(LW(0), 40)
                ADD(LW(0), 40)
                SUBTRACT(LW(0), 1)
                CALL(evt_sub_random, LW(0), LW(1))
                SET_VALUE(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(PTR(drill_attack_event))
                    GOTO(99)
                    ELSE
                    CALL_CHILD(PTR(arm_bunri_event))
                    GOTO(99)
                END_IF
                ELSE
                CALL(btlevtcmd_GetUnitWork, -2, 7, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL(get_aud_num, LW(0))
                    IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                        CALL_CHILD(PTR(aud_attack_event))
                        GOTO(99)
                    END_IF
                END_IF
                LABEL(10)
                SET_VALUE(LW(0), 0)
                ADD(LW(0), 40)
                ADD(LW(0), 40)
                ADD(LW(0), 25)
                SUBTRACT(LW(0), 1)
                CALL(evt_sub_random, LW(0), LW(1))
                SET_VALUE(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(PTR(drill_attack_event))
                    GOTO(99)
                END_IF
                ADD(LW(0), 40)
                IF_INT_LESS(LW(1), LW(0))
                    CALL_CHILD(PTR(arm_bunri_event))
                    GOTO(99)
                END_IF
                ADD(LW(0), 25)
                IF_INT_LESS(LW(1), LW(0))
                    CALL(get_aud_num, LW(0))
                    IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                        CALL_CHILD(PTR(aud_attack_event))
                        GOTO(99)
                    END_IF
                END_IF
                GOTO(10)
            END_IF
        END_IF
        ELSE
        CALL(btlevtcmd_GetHp, -2, LW(0))
        IF_INT_GREATER(LW(0), 35)
            CALL_CHILD(PTR(boomerang_attack_event))
            GOTO(99)
            ELSE
            CALL(btlevtcmd_GetUnitWork, -2, 7, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(get_aud_num, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                    CALL_CHILD(PTR(aud_attack_event))
                    GOTO(99)
                END_IF
            END_IF
            LABEL(20)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 75)
            ADD(LW(0), 20)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 75)
            IF_INT_LESS(LW(1), LW(0))
                CALL_CHILD(PTR(boomerang_attack_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 20)
            IF_INT_LESS(LW(1), LW(0))
                CALL(get_aud_num, LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                    CALL_CHILD(PTR(aud_attack_event))
                    GOTO(99)
                END_IF
            END_IF
            GOTO(20)
        END_IF
    END_IF
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 drill_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_batten_drill_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_batten_drill_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 5, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 5, 1, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131163, (s32)evt_btl_camera_set_prilimit,
    1, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131126, -30000000, 20, 655451, (s32)evt_btl_camera_set_moveto,
    1, -30000000, 160, 600, -30000000, 110, -100, 20,
    11, 65545, 20, 327771, (s32)evt_msg_print, 2, (s32)"stg7_aji_41_02", 0,
    -2, 131163, (s32)evt_btl_camera_set_prilimit, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 65546, 500, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_batten_drill_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_batten_drill_attack, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_DRILL_ATTACK1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A3_1",
    65546, 800, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_DRILL_ATTACK2", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A3_2", 110, 131163,
    (s32)drill_jet, -2, 112, 65546, 300, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -29999999, 300, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 60, 0, 1, 0,
    -1, 65546, 300, 327771, (s32)btlevtcmd_SetPos, -2, -125, 500,
    0, 327771, (s32)btlevtcmd_SetRotate, -2, 180, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A3_3", 110, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_MBTN_DRILL_ATTACK3", -250000000, 0, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -125,
    -200, 0, 60, 0, 0, 0, -1, 112,
    107, 131163, (s32)drill_tor, -2, 109, 65541, 0, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131100, -29999999, 200,
    7, 33, 65545, 1, 6, 393307, (s32)evt_btl_camera_shake_h, 0,
    7, 0, 80, 0, 131122, -29999994, 0, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 10, 131096, -29999997, -1,
    65540, 97, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    (s32)weapon_batten_drill_attack, 256, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 49, 65539, 90, 65540,
    95, 65539, 91, 131096, -29999994, 0, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, (s32)weapon_batten_drill_attack, 131122, -29999994, 1, 33, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, (s32)weapon_batten_drill_attack, 256, -29999995, 65540, 95,
    65539, 95, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 10,
    65539, 97, 65541, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131100, -29999999, -200, 7, 33, 65545,
    1, 6, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 200,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetPos, -2, 400,
    -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 60, -1, 0, 2, 1,
};

s32 boomerang_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_batten_boomerang_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_batten_boomerang_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)weapon_batten_boomerang_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove,
    196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_batten_boomerang_attack, 110, 65546, 900, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_BOOME_DIVIDE1", -250000000, 0, -250000000, 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A6_1", 65546, 1160, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MBTN_BOOME_ROUND1", -250000000, 0, -29999985, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 70,
    131125, -29999999, 70, 393307, (s32)btlevtcmd_SetPartsPos, -2, 4, -30000000,
    -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 4, 0, 55,
    65, 110, 65546, 1600, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_BOOME_ACTIVE1",
    -250000000, 0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 4,
    (s32)"MGN_A4_2", 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 4, 16777216, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 4, 33554432, 110, 65546, 2500, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 4, (s32)"MGN_A4_3", 112, 393307, (s32)btlevtcmd_GetPartsPos, -2, 4,
    -30000000, -29999999, -29999998, 131125, -29999999, 30, 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 25, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 4, -30000000,
    -29999999, -29999998, 80, -40, 0, 0, -1, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 25, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 4,
    -30000000, -29999999, -29999998, 80, 40, 0, 0, -1,
    110, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 4, -400, 120, -29999998,
    40, -20, 1, 0, -1, 112, 131163, (s32)evt_snd_sfxoff,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_BOOME_MOVE1", -250000000, 0, -250000000,
    65545, 20, 131122, -29999994, 0, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 65539, 10, 131096, -29999997, -1, 65540, 97,
    33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_batten_boomerang_attack, 256,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 95, 65539,
    91, 131096, -29999994, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_batten_boomerang_attack,
    131122, -29999994, 1, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_batten_boomerang_attack, 256, -29999995, 65540, 95, 65539, 95,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 65540, 10, 65539, 97,
    65546, 700, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 4, 16777216, 262235,
    (s32)btlevtcmd_OnPartsAttribute, -2, 4, 33554432, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 200, 2, 1,
};

s32 aud_attack_event[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_batten_aud_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_batten_aud_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 33, 2, 33, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 7, -30000000, 131096, -30000000, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff,
    0, 131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_btl_camera_set_mode, 1, 3,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131126, -30000000,
    20, 655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 160, 600, -30000000,
    110, -100, 20, 11, 65545, 20, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 0, -30000000, 131096, -30000000, 0, 196699, (s32)btlevtcmd_SetTalkPose,
    -2, (s32)"MGN_T_1", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"MGN_S_1", 32, 196699,
    (s32)btlevtcmd_SetTalkPose, -2, (s32)"MGN_T_2", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"MGN_S_2", 33,
    327771, (s32)evt_msg_print, 2, (s32)"stg7_aji_41_04", 0, -2, 131163, (s32)evt_btl_camera_set_prilimit,
    0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    65546, 500, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_batten_aud_attack, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    (s32)weapon_batten_aud_attack, 65545, 30, 110, 65546, 200, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MBTN_MOVE1", -250000000, 0, -29999985, 65546, 300, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MOVE1", -250000000, 0, -29999985, 65546, 300,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MOTOR_ACTIVE1", -250000000, 0, -29999985, 65546,
    700, 131163, (s32)evt_snd_sfxoff, -29999985, 112, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"MGN_A2_1", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_1",
    33, 65546, 1600, 110, 131163, (s32)drill_jet, -2, 112,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_2", 32, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"MGN_A5_2", 33, 65546, 300, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MBTN_JUMP1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -29999999, 300, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 60, 0, 1, 0,
    -1, 65546, 300, 196699, (s32)evt_btl_camera_set_mode, 0, 6, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 262235, (s32)evt_batstage_set_aud_dark, 0, 30, 0,
    110, 131163, (s32)aud_jet, -2, 112, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"MGN_A2_7", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_7",
    33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_FALL1", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999998,
    150, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 131125,
    -29999999, 300, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, 25, -29999998,
    60, 0, 4, 0, -1, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"MGN_A2_3", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_3",
    33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_INHALE1", -250000000, 0, -29999985,
    131163, (s32)aud_suikomi, -2, 110, 65627, (s32)aud_scream_fadeout, 112, 131163,
    (s32)evt_snd_sfxoff, -29999985, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096,
    -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_7", 32,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_7", 33, 65546, 300,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_JUMP1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 300,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 60, 0,
    1, 0, -1, 65627, (s32)aud_jet_end, 65546, 300, 196699,
    (s32)evt_batstage_return_aud_dark_base, 30, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 110, 131163, (s32)drill_jet, -2, 112,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_2", 32, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"MGN_A5_2", 33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_FALL1",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 300, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 60, 0,
    4, 0, -1, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MOTOR_ACTIVE1",
    -250000000, 0, -29999985, 65546, 600, 131163, (s32)evt_snd_sfxoff, -29999985,
    65546, 400, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_CHEST_OPEN1", -250000000, 0,
    -250000000, 112, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096,
    -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_4", 32,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_4", 33, 65546, 1200,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 7, -30000000, 131096, -30000000, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 7, 1, 131163, (s32)btlevtcmd_StatusWindowOnOff, 0,
    131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_btl_camera_set_mode, 1, 3, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131126, -30000000, 20,
    655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 160, 600, -30000000, 110,
    -100, 20, 11, 65545, 20, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    0, -30000000, 131096, -30000000, 0, 196699, (s32)btlevtcmd_SetTalkPose, -2,
    (s32)"MGN_T_3", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"MGN_A2_8", 32, 196699, (s32)btlevtcmd_SetTalkPose,
    -2, (s32)"MGN_T_4", 196699, (s32)btlevtcmd_SetStayPose, -2, (s32)"MGN_A5_8", 33, 327771,
    (s32)evt_msg_print, 2, (s32)"stg7_aji_41_05", 0, -2, 196699, (s32)btlevtcmd_SetTalkPoseType, -2,
    65, 196699, (s32)btlevtcmd_SetStayPoseType, -2, 69, 131163, (s32)evt_btl_camera_set_prilimit, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1, 65546,
    500, 33, 393307, (s32)btlevtcmd_GetPartsPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 131125, -29999999, 20, 262235, (s32)aud_target_mark, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_5", 32, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_5", 33, 131122, -29999990, 0,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 8, 0, 65541, 10, 65546,
    250, 65630, (s32)aud_attack_event_sub, 6, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -30000000, -10, 131125, -29999999, 78,
    65546, 250, 983131, (s32)evt_eff, (s32)"", (s32)"machingegun", 0, -30000000,
    -29999999, -29999998, 180, -229991808, -229997850, 0, 0, 0,
    0, 0, 65546, 250, 983131, (s32)evt_eff, (s32)"", (s32)"machingegun",
    0, -30000000, -29999999, -29999998, 170, -229991808, -229997850, 0,
    0, 0, 0, 0, 65546, 250, 983131, (s32)evt_eff,
    (s32)"", (s32)"machingegun", 0, -30000000, -29999999, -29999998, 185, -229991808,
    -229997850, 0, 0, 0, 0, 0, 262235, (s32)btlevtcmd_GetUnitWork,
    -2, 0, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"MGN_A2_8", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"MGN_A5_8", 33, 65546, 1000, 110, 65546, 100, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_CHEST_OPEN1", -250000000, 0, -250000000, 65546, 300,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MOVE1", -250000000, 0, -250000000, 65546,
    300, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MOVE1", -250000000, 0, -250000000,
    112, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A2_6", 32, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A5_6", 33, 65546, 1000, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65546, 200, 2, 1,
};

s32 aud_attack_event_sub[] = {
    131096, -29999990, 9, 262235, (s32)btlevtcmd_GetUnitWork, -2, 8, -30000000,
    131096, -30000000, 1, 65540, 91, 33, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_MACHINEGUN1", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, (s32)weapon_batten_aud_attack, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 131122, -29999989, -29999990, 131127, -29999989, 2,
    262235, (s32)aud_fire_no_hit, -2, -29999997, -29999989, 65540, 95, 65539,
    91, 131122, -29999989, -29999990, 131127, -29999989, 2, 262235,
    (s32)aud_fire_hit, -2, -29999997, -29999989, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_batten_aud_attack,
    131096, -29999990, 9, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)weapon_batten_aud_attack, 256, -29999995, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)weapon_batten_aud_attack, 0, -29999995, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    8, 1, 65540, 95, 65539, 95, 131125, -29999990,
    1, 2, 1,
};

static s32 arm_bunri_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 2, -30000000, 131096, -30000000, 0,
    131163, (s32)btlevtcmd_StatusWindowOnOff, 0, 131163, (s32)evt_btl_camera_set_prilimit, 1, 196699, (s32)evt_btl_camera_set_mode,
    1, 3, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131126, -30000000, 20, 655451, (s32)evt_btl_camera_set_moveto, 1, -30000000, 160,
    600, -30000000, 110, -100, 20, 11, 65545, 20,
    327771, (s32)evt_msg_print, 2, (s32)"stg7_aji_41_03", 0, -2, 131163, (s32)evt_btl_camera_set_prilimit,
    0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StatusWindowOnOff, 1,
    65546, 500, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    1, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_ACTIVE1", -250000000, 0,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A1_1", 65546, 600,
    131163, (s32)evt_snd_sfxoff, -29999985, 65546, 200, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_MBTN_PUNCH_STOP1", -250000000, 0, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"MGN_A1_2", 65546, 500, 131163, (s32)evt_snd_sfxoff, -29999985, 65546, 100,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A1_3", 65546, 100, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_IGNITE1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_w,
    0, 3, 0, 20, 0, 65546, 100, 262235,
    (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_rocket_punch, 0, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0,
    0, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 1, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -29999997, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, 1, 69,
    262235, (s32)btlevtcmd_SpawnUnit, -29999996, (s32)entry_rocket_punch, 0, 262235, (s32)btlevtcmd_SetUnitWork, -29999996,
    0, 1, 262235, (s32)btlevtcmd_SetUnitWork, -29999996, 1, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 4, -29999996, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999996, 1,
    69, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table_no_arm, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 69, 65546, 1500, 2, 1,
};

static s32 arm_return_event[] = {
    262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"MGN_A1_6", 65546, 600, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_rocket_punch,
    0, 262235, (s32)btlevtcmd_SetUnitWork, -29999997, 0, 2, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -29999997, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999997, 1, 69,
    262235, (s32)btlevtcmd_SpawnUnit, -29999996, (s32)entry_rocket_punch, 0, 262235, (s32)btlevtcmd_SetUnitWork, -29999996,
    0, 3, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, -29999996, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999996, 1, 69, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1",
    -250000000, 0, -250000000, 110, 327771, (s32)btlevtcmd_SetPos, -29999997, 300,
    40, -100, 655451, (s32)btlevtcmd_DivePosition, -29999997, 30, 100, -40,
    30, -10, 0, 0, -1, 112, 327771, (s32)btlevtcmd_SetPos,
    -29999996, 350, 40, 100, 655451, (s32)btlevtcmd_DivePosition, -29999996, 80,
    100, 40, 30, -10, 0, 0, -1, 131163,
    (s32)arm_end, 0, 131163, (s32)arm_end, 1, 196699, (s32)btlevtcmd_KillUnit, -29999997,
    0, 196699, (s32)btlevtcmd_KillUnit, -29999996, 0, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_MBTN_PUNCH_IGNITE1", -250000000, 0, -250000000, 393307, (s32)evt_btl_camera_shake_w, 0, 3,
    0, 20, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A1_7",
    65546, 300, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A1_8", 65546,
    600, 262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 69, 65546, 500, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

BattleUnitKind unit_boss_rocket_punch_mkII = {
    122,
    "btl_un_rocket_punch_mkii",
    5,
    0,
    1,
    1,
    0,
    0,
    0,
    100,
    0,
    50,
    10,
    50,
    34,
    0,
    15,
    0.0f,
    0.0f,
    0.0f,
    0,
    -20,
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
    24.0f,
    16.0f,
    0.0f,
    -5.0f,
    0.0f,
    0.0f,
    50.0f,
    34.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_MBTN_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist_r,
    1,
    parts_r,
    init_event_r,
    data_table_r,
};

static __declspec(section ".data") BattleUnitDefense defence_r = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr_r = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist_r = {0, 70, 70, 100, 70, 100, 100, 70, 0, 0, 100, 0, 100, 85, 70, 0, 100, 100, 70, 0, 0, 0};

static PoseTableEntry pose_table_r[] = {
    {1, "MGN_A1_9"},
    {2, "MGN_A1_4"},
    {9, "MGN_A1_4"},
    {5, "MGN_A1_9"},
    {4, "MGN_A1_9"},
    {3, "MGN_A1_9"},
    {28, "MGN_A1_9"},
    {29, "MGN_A1_9"},
    {30, "MGN_A1_9"},
    {31, "MGN_A1_9"},
    {39, "MGN_A1_9"},
    {56, "MGN_A1_9"},
    {57, "MGN_A1_9"},
    {69, "MGN_A1_9"},
};

static __declspec(section ".data") BattleDataEntry data_table_r[] = {
    {0, NULL},
};

static BattleUnitKindPart parts_r[] = {
    {1, "btl_un_rocket_punch_mkii", "c_mb_robo_2b", 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 10.0f, 0.0f, 106, 174, 255, &defence_r, &defence_attr_r, 0x600009, 0x2, pose_table_r},
};

static s32 weapon_batten_rocket_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536875008, 770, 0, 135, 2047, 8196,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 init_event_r[] = {
    196699, (s32)btlevtcmd_OnUnitFlag, -2, 16777216, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"MGN_A1_4", 196699, (s32)btlevtcmd_SetEventWait, -2, (s32)wait_event_r, 196699, (s32)btlevtcmd_SetEventAttack, -2,
    (s32)attack_event_r, 196699, (s32)btlevtcmd_SetEventDamage, -2, (s32)damage_event_r, 196699, (s32)btlevtcmd_SetEventConfusion, -2,
    (s32)btldefaultevt_Confuse, 327771, (s32)btlevtcmd_SetBaseRotate, -2, 0, -90, 0, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096, -30000000, 0, 131163,
    (s32)arm_init2, 0, 33, 131096, -30000000, 2, 131163, (s32)arm_init2,
    0, 33, 131096, -30000000, 1, 131163, (s32)arm_init2, 1,
    33, 131096, -30000000, 3, 131163, (s32)arm_init2, 1, 33,
    65628, (s32)arm_event, 262235, (s32)btlevtcmd_GetUnitWork, -2, 0, -30000000, 131096,
    -30000000, 0, 327771, (s32)btlevtcmd_SetPos, -2, 30, 100, -40,
    655451, (s32)btlevtcmd_DivePosition, -2, -100, 150, -60, 20, 0,
    4, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1", -250000000,
    0, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, 350, 110, -80,
    30, 50, 0, 0, -1, 655451, (s32)btlevtcmd_DivePosition, -2,
    30, 60, -40, 25, -30, 4, 0, -1,
    327771, (s32)btlevtcmd_SetHomePos, -2, 30, 60, -40, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 33, 131096, -30000000, 1, 327771, (s32)btlevtcmd_SetPos, -2,
    80, 100, 40, 655451, (s32)btlevtcmd_DivePosition, -2, -50, 150,
    60, 20, 0, 4, 0, -1, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1", -250000000, 0, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2,
    300, 120, 80, 30, 50, 0, 0, -1,
    655451, (s32)btlevtcmd_DivePosition, -2, 80, 60, 40, 30, -30,
    4, 0, -1, 327771, (s32)btlevtcmd_SetHomePos, -2, 80, 60,
    40, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 33, 2, 1,
};

static EVT_BEGIN(arm_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL_CHILD(PTR(arm_event_end))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(arm_main, -2, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(arm_main, -2, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_main, -2, 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        CALL(arm_main, -2, 1)
    END_IF
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(arm_event_end)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(arm_end, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        CALL(arm_end, 0)
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        CALL(arm_end, 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        CALL(arm_end, 1)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(damage_event_r)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_CheckDamageCode, -2, 512, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDamageCode, -2, 2048, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(arm_event_end))
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 attack_event_r[] = {
    262235, (s32)btlevtcmd_AddUnitWork, -2, 1, -1, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    1, -30000000, 131101, -30000000, 1, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 1, 1, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, (s32)weapon_batten_rocket_attack,
    262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_batten_rocket_attack, -29999997, -29999996, 131096, -29999997, -1,
    262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000, 0,
    65630, (s32)subsetevt_confuse_flustered, 33, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 33,
    196699, (s32)evt_sub_random, 1, -29999994, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_batten_rocket_attack, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, (s32)weapon_batten_rocket_attack, 196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 200, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MGN_A1_4",
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, (s32)weapon_batten_rocket_attack, 256, -29999995,
    65570, -29999995, 65579, 4, 65540, 90, 46, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46,
    65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90,
    65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90,
    65572, 1, 65540, 91, 46, 42, 65540, 98,
    46, 49, 65539, 90, 65540, 95, 65539, 91,
    110, 65541, 0, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -29999990, -29999989, -29999988,
    131100, -29999990, -30000000, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_batten_rocket_attack, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)weapon_batten_rocket_attack, 256, -29999995, 393307,
    (s32)evt_btl_camera_shake_w, 0, 3, 0, 10, 0, 7, 33,
    65545, 1, 6, 112, 65540, 95, 65539, 95,
    131096, -29999994, 0, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 110, 131122,
    -29999999, 120, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1", -250000000, 0,
    -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30,
    10, 4, 0, -1, 65545, 5, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, -20, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1", -250000000, 0,
    -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -250, 0, -29999998, 20,
    -10, 0, 0, -1, 32, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000,
    -200, 131125, -29999999, 140, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_MBTN_PUNCH_FLY1",
    -250000000, 0, -250000000, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 40, -80, 1, 0, -1, 33, 65546,
    250, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 0, -29999990, 131096, -29999990, 0, 327771,
    (s32)btlevtcmd_SetPos, -2, 300, -29999999, -100, 32, 327771, (s32)btlevtcmd_SetPos,
    -2, 300, -29999999, 100, 33, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BOSS_MBTN_PUNCH_FLY1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    30, 0, 4, 0, -1, 65539, 99, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static EVT_BEGIN(wait_event_r)
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

static USER_FUNC(arm_init) {
    s32 i;

    for (i = 0; i < 2; i++) {
        work[i] = BattleAlloc(sizeof(ArmWork));
        work[i]->prevPos = work[i]->pos = (Vec){0.0f, 0.0f, 0.0f};
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(arm_init2) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    arm->eff = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 1.0f);
    return EVT_RETURN_DONE;
}

static USER_FUNC(arm_main) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id = evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    ArmWork* arm = work[idx];
    BattenEffWork* eff;
    f32 x, y, z;
    f32 rx, ry, rz;
    f32 bx, by, bz;
    Mtx m;
    Mtx rot;
    Vec ofs;
    f32 dx, dy;

    if (arm->eff == NULL) {
        return EVT_RETURN_DONE;
    }
    eff = arm->eff->userdata;
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    arm->prevPos = arm->pos;
    {
        Vec p = {0.0f, 0.0f, 0.0f};

        p.x = x;
        p.y = y;
        p.z = z;
        arm->pos = p;
    }
    if (evtCheckID(unit->waitEventId) != TRUE) {
        dx = arm->pos.x - arm->prevPos.x;
        dy = arm->pos.y - arm->prevPos.y;
        if (dx != 0.0f) {
            arm->targetRot = 360.0f * (f32)atan(dy / dx) / 6.283184f;
            arm->rot += (arm->targetRot - arm->rot) / 3.0f;
            BtlUnit_GetRotate(unit, &rx, &ry, &rz);
            BtlUnit_SetRotate(unit, rx, ry, arm->rot);
        } else {
            arm->targetRot = 0.0f;
        }
    }
    BtlUnit_GetBaseRotate(unit, &bx, &by, &bz);
    BtlUnit_GetRotate(unit, &rx, &ry, &rz);
    rx += bx;
    ry += by;
    rz += bz;
    PSMTXRotRad(m, 'x', 1.5707964f);
    PSMTXRotRad(rot, 'y', 0.017453292f * ry);
    PSMTXConcat(rot, m, m);
    PSMTXRotRad(rot, 'x', 0.017453292f * rx);
    PSMTXConcat(rot, m, m);
    PSMTXRotRad(rot, 'z', 0.017453292f * rz);
    PSMTXConcat(rot, m, m);
    PSMTXCopy(m, eff->mtx);
    ofs = (Vec){0.0f, -18.0f, 0.0f};
    PSMTXMultVec(m, &ofs, &ofs);
    eff->pos.x = arm->pos.x + ofs.x;
    eff->pos.y = arm->pos.y + ofs.y;
    eff->pos.z = arm->pos.z + ofs.z;
    return EVT_RETURN_DONE;
}

static USER_FUNC(arm_end) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    if (arm->eff != NULL) {
        effDelete(arm->eff);
        arm->eff = NULL;
    }
    return EVT_RETURN_DONE;
}
