#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/effdrv.h"

EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
static EffectEntry* eff;
static EffectEntry* eff2[10];
static s32 step[10];

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_CheckSpace);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_FaceDirectionSub);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_StartWaitEvent);
static USER_FUNC(eff_all_fire);
USER_FUNC(evt_sub_random);
static USER_FUNC(eff_fire);
static USER_FUNC(bubble_copy_status);
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddPos[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_DivePartsPosition[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SpawnUnit[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_add_zoom[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_shake_h[];
extern s32 evt_eff[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_phantom_negone_one_374;
__declspec(section ".data") s32 fd_phantom_neg_one_382[1];
__declspec(section ".data") s32 fd_phantom___local_PI_383[1];
__declspec(section ".data") s32 fd_phantom___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_phantom_one_negone_373;
__declspec(section ".data") s32 fd_phantom___local_PIO2_384[1];
__declspec(section ".data") s32 fd_phantom_one_381[1];
__declspec(section ".data") u64 fd_phantom_negone_one_360;
__declspec(section ".data") s32 fd_phantom_neg_one_365[1];
__declspec(section ".data") s32 fd_phantom___local_PI_366[1];
__declspec(section ".data") s32 fd_phantom___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_phantom_one_negone_359;
__declspec(section ".data") s32 fd_phantom___local_PIO2_367[1];
__declspec(section ".data") s32 fd_phantom_one_364[1];
BattleUnitKind unit_phantom;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[4];
static BattleUnitKindPart parts[2];
static s32 weapon_bubble_attack[48];
static s32 weapon_bubble_fire_attack[48];
static __declspec(section ".data") s32 entry_bubble[12];
static s32 init_event[39];
static __declspec(section ".data") s32 damage_event[10];
static s32 avoid_fire_event[16];
static s32 damage_fire_explosion_event[103];
static s32 friend_event[99];
static s32 attack_event[51];
static s32 normal_attack_event[412];
static s32 fire_attack_event[365];
static __declspec(section ".data") s32 all_fire_attackEvent_sub[10];
static s32 all_fire_attack_event[321];
static __declspec(section ".data") s32 wait_event[6];

static USER_FUNC(bubble_copy_status) {
    s32* args = event->args;
    s32 id1 = BattleTransID(event, evtGetValue(event, args[0]));
    s32 id2 = BattleTransID(event, evtGetValue(event, args[1]));
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    if (unit2->currentHp > unit2->maxHp) {
        unit2->currentHp = unit2->maxHp;
    }
    unit2->mSizeChangeTurns = unit1->mSizeChangeTurns;
    unit2->mSizeChangeStrength = unit1->mSizeChangeStrength;
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_phantom_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_phantom_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_phantom___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_phantom___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_phantom_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_phantom___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_phantom_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_phantom_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_phantom_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_phantom___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_phantom___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_phantom_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_phantom___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_phantom_one_364[] = {
    1065353216,
};

BattleUnitKind unit_phantom = {
    124,
    "btl_un_phantom",
    10,
    0,
    1,
    1,
    30,
    0,
    2,
    70,
    2,
    50,
    9999,
    26,
    36,
    8,
    24,
    0.0f,
    18.0f,
    0.0f,
    0,
    -3,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    13.0f,
    0.0f,
    0.0f,
    13.0f,
    23.4f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    26.0f,
    36.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BUBBLE_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 3, 1, 1, 0}};

static __declspec(section ".data") StatusVulnerability regist = {40, 80, 100, 100, 65, 100, 0, 40, 100, 80, 100, 80, 100, 90, 65, 40, 80, 100, 65, 100, 100, 90};

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
    {31, "A_2B"},
    {39, "D_1"},
    {50, "A_1"},
    {42, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {11, damage_fire_explosion_event},
    {40, avoid_fire_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_phantom", "c_phantom", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x109, 0x10, pose_table},
    {2, NULL, "c_phantom", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 15, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static s32 weapon_bubble_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 16777986, 0, 135, 112, 8196,
    0, 0, 0, 0, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_bubble_fire_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 16777986, 0, 199, 2047, -2147475452,
    0, 0, 0, 75, 50331648, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_bubble[] = {
    (s32)&unit_phantom, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, -2, LW(0), 10, LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), 10, LW(2))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 avoid_fire_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_FIRE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 65546, 1000, 2, 1,
};

static EVT_BEGIN(damage_fire_explosion_event)
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("A_2B"))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionSub, -2, LW(0), 40)
        IF_INT_LESS_OR_EQUAL(LW(0), 170)
            ADD(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(friend_event))
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    LOOP(0)
        CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
        IF_INT_GREATER_OR_EQUAL(LW(0), 10)
            SUBTRACT(LW(2), 10)
            CALL(btlevtcmd_CheckSpace, LW(3), LW(0), LW(1), LW(2), 40, 0, 0, 0)
            IF_INT_EQUAL(LW(3), -1)
                CALL_CHILD(PTR(friend_event))
                WAIT_MS(500)
                GOTO(99)
            END_IF
            ELSE
            BREAK_LOOP
        END_IF
    END_LOOP
    LABEL(99)
    RETURN
EVT_END()

static s32 friend_event[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -29999990, -29999989, (s32)"S_1", 327771, (s32)btlevtcmd_GetPos, -2,
    -29999988, -29999987, -29999986, 262235, (s32)btlevtcmd_SpawnUnit, -29999997, (s32)entry_bubble, 0,
    196699, (s32)bubble_copy_status, -2, -29999997, 327771, (s32)btlevtcmd_SetPos, -29999997, -29999988,
    -29999987, -29999986, 327771, (s32)btlevtcmd_JumpSetting, -29999997, 0, 10, -229999488,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_SPLIT1", -250000000, 0, -250000000, 110,
    327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 10, 0, 131122, -29999988,
    0, 65541, 0, 65545, 1, 131125, -29999988, 1,
    131101, -29999988, 30, 7, 33, 327771, (s32)btlevtcmd_AddRotate, -29999997,
    0, 0, 40, 6, 327771, (s32)btlevtcmd_SetRotate, -29999997, 0,
    0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -29999997, 0, 0, 0,
    112, 458843, (s32)btlevtcmd_JumpPosition, -29999997, -30000000, -29999999, -29999998, -229969280,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -29999997, -30000000, -29999999, -29999998, 65546,
    1000, 2, 1,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
        RETURN
    END_IF
    SET_VALUE(LW(0), 70)
    ADD(LW(0), 30)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 70)
        SET_VALUE(LW(9), PTR(weapon_bubble_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(9), PTR(weapon_bubble_fire_attack))
    CALL_CHILD(PTR(fire_attack_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 normal_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -29999997,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250,
    65647, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_MOVE1", -250000000, 0,
    -250000000, 65545, 120, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1A", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 13, 131126, -29999999, 20,
    131098, -29999999, 0, 131122, -29999999, 0, 33, 131125,
    -29999998, 5, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    30, 0, 0, 0, -1, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    5, 131126, -29999999, 20, 131098, -29999999, 0, 131122,
    -29999999, 0, 33, 131125, -29999998, 5, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 30, 0, 4, 0,
    -1, 65631, -29999985, 65545, 30, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 49, 65539,
    90, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_FIRE1", -250000000, 0, -250000000,
    65541, 4, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65545,
    10, 6, 65540, 98, 65539, 91, 393307, (s32)evt_btl_camera_shake_h,
    0, 1, 1, 8, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_add_zoom, 0, -50, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BUBBLE_FIRE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"A_1B", 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, -29999991, 256, -29999995, 65545, 10, 65541,
    3, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1B", 65545, 10,
    6, 65540, 98, 65539, 98, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_MOVE2", -250000000, 0, -250000000,
    110, 65545, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A",
    112, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 131125, -29999999, 20,
    655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30, 20,
    0, 0, -1, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 100, 131125,
    -29999999, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    30, -30, 0, 0, -1, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 40, 25, 4, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"S_1", 65546, 400, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static USER_FUNC(eff_fire) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, 2);
    f32* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        eff = effFireEntry(7, 0.0f, -1000.0f, 0.0f, 1.0f, 106);
        ((f32*)eff->userdata)[30] = 0.0f;
        ((f32*)eff->userdata)[31] = 0.0f;
    }
    wk = eff->userdata;
    if (wk != NULL) {
        BtlUnit_GetPartsPos(part, &x, &y, &z);
        *(Vec*)&wk[1] = (Vec){x, y, z};
        wk[30] += 0.1f * unit->mSizeMultiplier;
        if (wk[30] >= unit->mSizeMultiplier) {
            wk[30] = unit->mSizeMultiplier;
        }
        wk[31] += 0.1f * unit->mSizeMultiplier;
        if (wk[31] >= unit->mSizeMultiplier) {
            wk[31] = unit->mSizeMultiplier;
        }
    }
    return EVT_RETURN_BLOCK;
}

static s32 fire_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 110, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"T_1", 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"S_1",
    112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_ATTACK2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, 2, 33554432, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5,
    393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 110,
    131163, (s32)eff_fire, -2, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 0, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 131131, -29999990,
    -30000000, 131131, -29999988, -29999998, 131132, -29999990, -229999284, 131132,
    -29999988, -229999386, 131130, -30000000, -29999990, 131130, -29999998, -29999988,
    720987, (s32)btlevtcmd_DivePartsPosition, -2, 2, -30000000, -29999999, -29999998, 40,
    0, 4, 0, -1, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 5, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999990, -29999989, -29999988, 131131, -29999990,
    -30000000, 131131, -29999988, -29999998, 131132, -29999990, -229999591, 131132,
    -29999988, -229999591, 131130, -30000000, -29999990, 131130, -29999998, -29999988,
    720987, (s32)btlevtcmd_DivePartsPosition, -2, 2, -30000000, -29999999, -29999998, 20,
    0, 4, 0, -1, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 2, -30000000, -29999999, -29999998,
    30, 0, 1, 0, -1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BUBBLE_ATTACK3", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2,
    33554432, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 0,
    -29999995, 65570, -29999995, 65579, 4, 65540, 90, 46,
    65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90,
    46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540,
    90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540,
    90, 65572, 1, 65540, 91, 46, 42, 65540,
    98, 46, 49, 65539, 90, 65540, 98, 65539,
    91, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 16, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999991, 256, -29999995, 65540, 98, 65539, 98,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65546, 400, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static USER_FUNC(eff_all_fire) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 index = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 scales[10] = {1.0f, 1.25f, 1.5f, 1.75f, 2.0f, 2.25f, 2.0f, 1.75f, 1.5f, 1.25f};
    f32* wk;
    f32 x;
    f32 y;
    f32 z;

    if (isFirstCall) {
        eff2[index] = effFireEntry(7, 0.0f, -1000.0f, 0.0f, 1.0f, 120);
        ((f32*)eff2[index]->userdata)[30] = 2.0f;
        ((f32*)eff2[index]->userdata)[31] = unit->mSizeMultiplier * scales[index];
    }
    wk = eff2[index]->userdata;
    if (wk != NULL) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        *(Vec*)&wk[1] = (Vec){x + 24.0f * unit->faceDirection * (index + 1), y - 15.0f - 2.0f * scales[index], z - 10.0f};
    }
    return EVT_RETURN_BLOCK;
}

static __declspec(section ".data") EVT_BEGIN(all_fire_attackEvent_sub)
    BEGIN_SIBLING_EVENT
        CALL(eff_all_fire, -2, LW(0))
    END_SIBLING_EVENT
    WAIT_FRAMES(120)
    RETURN
EVT_END()

static s32 all_fire_attack_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2,
    -29999991, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -2, -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom,
    0, 250, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_MOVE1", -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -40,
    -29999999,
#ifdef VERSION_G8ME01
    -15,
#else
    -29999998,
#endif
    30, 0, 4, 0, -1, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985, 196699,
    (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_ATTACK4", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2A", 65541,
    20, 327771, (s32)btlevtcmd_AddPos, -2, 2, 0, 0, 65545,
    2, 327771, (s32)btlevtcmd_AddPos, -2, -2, 0, 0, 65545,
    2, 6, 110, 131122, -30000000, 0, 65541, 10,
    65628, (s32)all_fire_attackEvent_sub, 65545, 2, 131125, -30000000, 1, 6,
    112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_ATTACK2", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_2B", 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131122, -29999990, 0,
    65539, 0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991,
    0, -29999995, 65570, -29999995, 65579, 4, 65540, 90,
    46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540,
    90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    65540, 90, 65572, 1, 65540, 91, 46, 42,
    65540, 98, 46, 49, 65539, 90, 65540, 98,
    65539, 91, 131096, -29999990, 0, 196699, (s32)btlevtcmd_ResultACDefence, -29999997,
    -29999991, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65540, 97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy,
    -29999997, -29999996, 131097, -29999997, -1, 131125, -29999990, 1,
    65540, 0, 33, 65539, 98, 65545, 180, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"A_1A", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BUBBLE_MOVE1",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30,
    0, 4, 0, -1, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 400, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2,
    1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

