#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "mario/mario_pouch.h"
#include "data/item_data.h"
#include "system.h"

extern ItemData itemDataTable[];
void BtlUnit_EquipItem(BattleUnit* unit, s32 flags, ItemType type);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_CheckUnitFlag);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetRunSound);
USER_FUNC(btlevtcmd_SetWalkSound);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(evt_sub_random);
static USER_FUNC(_steal_item);
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_AnnounceMessage[];
extern s32 btlevtcmd_AnnounceSetParam[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_BtlIconDelete[];
extern s32 btlevtcmd_BtlIconEntry[];
extern s32 btlevtcmd_BtlIconJumpPosition[];
extern s32 btlevtcmd_BtlIconSetFallAccel[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_ChoiceSamplingEnemy[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetResultACDefence[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnPartsAttribute[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PayWeaponCost[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultACDefence[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsBlur[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffsetFromCenterOffset[];
extern s32 btlevtcmd_StartAvoid[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_borodo_negone_one_374;
__declspec(section ".data") s32 fd_borodo_neg_one_382[1];
__declspec(section ".data") s32 fd_borodo___local_PI_383[1];
__declspec(section ".data") s32 fd_borodo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_borodo_one_negone_373;
__declspec(section ".data") s32 fd_borodo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_borodo_one_381[1];
__declspec(section ".data") u64 fd_borodo_negone_one_360;
__declspec(section ".data") s32 fd_borodo_neg_one_365[1];
__declspec(section ".data") s32 fd_borodo___local_PI_366[1];
__declspec(section ".data") s32 fd_borodo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_borodo_one_negone_359;
__declspec(section ".data") s32 fd_borodo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_borodo_one_364[1];
BattleUnitKind unit_borodo_15_data_211F8;
static s32 weapon_borodo_attack[48];
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[20];
static PoseTableEntry pose_table_item_have[18];
static __declspec(section ".data") BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static s32 init_event[57];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static s32 attack_event[59];
static s32 _borodo_normal_attack[503];
static s32 _borodo_steal_attack[610];
static s32 escape_event[115];
static s32 wait_event[26];

static USER_FUNC(_steal_item) {
    s32* args = event->args;
    s32 coins;
    s32 num;
    PouchData* pouch = pouchGetPtr();
    BattleUnit* unit;
    BattleUnit* target;
    s32 itemVar;
    s32 iconVar;
    s32 numVar;
    s32 id;
    s32 tid;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    tid = evtGetValue(event, args[1]);
    tid = BattleTransID(event, tid);
    target = BattleGetUnitPtr(_battleWorkPointer, tid);
    if (target == NULL) {
        return EVT_RETURN_DONE;
    }
    itemVar = args[2];
    iconVar = args[3];
    numVar = args[4];
    evtSetValue(event, itemVar, 0);
    evtSetValue(event, iconVar, 0);
    evtSetValue(event, numVar, 0);
    if (irand(100) < 100) {
        coins = pouchGetCoin();
        num = 5;
        if (coins < 5) {
            num = coins;
        }
        if (num > 0) {
            evtSetValue(event, itemVar, ITEM_COIN);
            evtSetValue(event, iconVar, 395);
            evtSetValue(event, numVar, num);
            unit->heldItem = ITEM_COIN;
            unit->field_0x30C[0] = num;
            pouchSetCoin(coins - num);
        }
        return EVT_RETURN_DONE;
    }
    {
        s32 item = 0;
        s32 count = 0;
        s32 r;
        s32 i;

        for (i = 0; i < 20; i++) {
            if (pouch->heldItems[i] != 0) {
                count++;
            }
        }
        if (count <= 0) {
            return EVT_RETURN_DONE;
        }
        r = irand(count);
        if (r >= count) {
            s32 j;

            r -= count;
            for (j = 0; j < 200; j++) {
                if (pouch->badges[j] != 0) {
                    if (--r < 0) {
                        item = pouch->badges[j];
                        break;
                    }
                }
            }
        } else {
            s32 k;

            for (k = 0; k < 20; k++) {
                if (pouch->heldItems[k] != 0) {
                    if (--r < 0) {
                        item = pouch->heldItems[k];
                        break;
                    }
                }
            }
        }
        if (item != 0) {
            if (!pouchRemoveItem(item)) {
                return EVT_RETURN_DONE;
            }
            unit->heldItem = item;
            if (item >= 240 && item < 339) {
                if (target->currentKind == 222) {
                    BtlUnit_EquipItem(target, 3, 0);
                } else if (target->currentKind >= 224 && target->currentKind < 231) {
                    BtlUnit_EquipItem(target, 5, 0);
                }
                pouchReviseMarioParam();
                pouchRevisePartyParam();
            }
            evtSetValue(event, itemVar, item);
            evtSetValue(event, iconVar, itemDataTable[item].icon_id);
        }
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_borodo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_borodo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_borodo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_borodo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_borodo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_borodo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_borodo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_borodo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_borodo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_borodo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_borodo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_borodo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_borodo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_borodo_one_364[] = {
    1065353216,
};

BattleUnitKind unit_borodo_15_data_211F8 = {
    44,
    "btl_un_borodo",
    5,
    0,
    1,
    1,
    11,
    0,
    2,
    70,
    1,
    50,
    9999,
    26,
    34,
    0,
    34,
    0.0f,
    17.0f,
    0.0f,
    0,
    0,
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
    9.0f,
    26.0f,
    0.0f,
    0.0f,
    17.0f,
    0.0f,
    26.0f,
    34.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_BORODO_DAMAGED1",
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

static s32 weapon_borodo_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 7, 2, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {100, 90, 70, 100, 100, 100, 100, 70, 100, 95, 100, 95, 100, 100, 90, 95, 80, 100, 90, 100, 100, 95};

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
    {50, "A_1"},
    {51, "A_2"},
    {42, "R_1"},
    {41, "R_1"},
    {40, "W_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "T_1"},
    {69, "S_1"},
};

static PoseTableEntry pose_table_item_have[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "X_1"},
    {28, "S_2"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "S_2"},
    {39, "D_1"},
    {50, "A_1"},
    {51, "A_2"},
    {42, "R_2"},
    {41, "R_2"},
    {40, "W_2"},
    {65, "S_2"},
    {69, "S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_borodo", "c_borodo", 0.0f, 0.0f, 0.0f, 0.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, -2, STRING("SFX_ENM_BORODO_MOVE1L"), STRING("SFX_ENM_BORODO_MOVE1R"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, -2, STRING("SFX_ENM_BORODO_MOVE1L"), STRING("SFX_ENM_BORODO_MOVE1R"), 0, 10, 10)
    CALL(btlevtcmd_CheckUnitFlag, -2, 1073741824, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
        ELSE
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_item_have))
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_CheckUnitFlag, -2, 1073741824, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(escape_event))
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(_borodo_normal_attack))
        RETURN
    END_IF
    SET_VALUE(LW(1), 225)
    SUBTRACT(LW(1), 1)
    CALL(evt_sub_random, LW(1), LW(0))
    IF_INT_LESS(LW(0), 25)
        CALL_CHILD(PTR(_borodo_normal_attack))
        ELSE
        CALL_CHILD(PTR(_borodo_steal_attack))
    END_IF
    RETURN
EVT_END()

static s32 _borodo_normal_attack[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_borodo_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_borodo_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_borodo_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_borodo_attack, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 60, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)evt_btl_camera_set_zoom,
    0, 350, 65541, 8, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1L",
    -250000000, 0, -29999986, 65545, 3, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BORODO_MOVE1R", -250000000, 0, -29999986, 65545, 3, 6, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    (s32)weapon_borodo_attack, 256, -29999995, 131096, -29999995, 5, 196699, (s32)btlevtcmd_GetStatusMg,
    -29999997, -29999994, 131132, -29999994, 40, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_ATT1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 131163, (s32)evt_snd_sfxoff, -29999986, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_borodo_attack, 256, -29999995, 2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_ATT1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, 20, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)evt_snd_sfxoff, -29999986, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 49, 65539, 90, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999591, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1L", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1R",
    -250000000, 0, -250000000, 65545, 20, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_borodo_attack, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_borodo_attack, 256, -29999995, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999744, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 40, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"O_1", 110, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000,
    131101, -30000000, 0, 131122, -29999995, 0, 131122, -29999994,
    360, 32, 131122, -29999995, 360, 131122, -29999994, 0,
    33, 131163, (s32)btlevtcmd_SetRotateOffsetFromCenterOffset, -2, 327771, (s32)evt_sub_intpl_init, 13, -29999995,
    -29999994, 24, 65541, 25, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, -30000000, 65545, 1, 6, 112,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 36, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"X_1", 65546, 1000, 65539,
    98, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 _borodo_steal_attack[] = {
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)weapon_borodo_attack, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, (s32)weapon_borodo_attack, -29999997, -29999996, 131096, -29999997,
    -1, 262235, (s32)btlevtcmd_CheckToken, -2, 16, -30000000, 131097, -30000000,
    0, 65630, (s32)subsetevt_confuse_flustered, 2, 33, 65540, 99, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 8, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -29999997, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 131163, (s32)btlevtcmd_WeaponAftereffect, (s32)weapon_borodo_attack, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, (s32)weapon_borodo_attack, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 60, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)evt_btl_camera_set_zoom,
    0, 350, 65541, 8, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1L",
    -250000000, 0, -29999986, 65545, 3, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BORODO_MOVE1R", -250000000, 0, -29999986, 65545, 3, 6, 196699,
    (s32)evt_btl_camera_set_mode, 0, 3, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    (s32)weapon_borodo_attack, 256, -29999995, 131096, -29999995, 5, 196699, (s32)btlevtcmd_GetStatusMg,
    -29999997, -29999994, 131132, -29999994, 40, 327771, (s32)btlevtcmd_GetPos, -29999997,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, -29999994, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_ATT1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229994880, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 131163, (s32)evt_snd_sfxoff, -29999986, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_borodo_attack, 256, -29999995, 2, 33, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_ATT1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 50, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 327771,
    (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997,
    -30000000, 20, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    131163, (s32)evt_snd_sfxoff, -29999986, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    65540, 90, 46, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 65540, 90, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 49, 65539, 90, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999591, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 30,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 18, -1,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1L", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_MOVE1R",
    -250000000, 0, -250000000, 65545, 20, 65540, 98, 65539,
    91, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, (s32)weapon_borodo_attack, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999997, -29999996, (s32)weapon_borodo_attack, 256, -29999995, 131122, -29999992, 0,
    131163, (s32)btlevtcmd_GetResultACDefence, -29999993, 131100, -29999993, 3, 393307, (s32)_steal_item,
    -2, -29999997, -29999992, -29999991, -29999993, 131097, -29999992, 0,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_SUCCESS1", -250000000, 0, -250000000, 107,
    65545, 20, 196699, (s32)btlevtcmd_AnnounceSetParam, 0, -29999992, 393307, (s32)btlevtcmd_AnnounceMessage,
    1, 0, 0, (s32)"btl_msg_steal_item_lost", 90, 109, 107, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_BtlIconEntry,
    -29999991, -30000000, -29999999, -29999998, -29999990, 196699, (s32)btlevtcmd_BtlIconSetFallAccel, -29999990,
    -229999488, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_BtlIconJumpPosition, -29999990, -30000000, -29999999,
    -29999998, 20, 131163, (s32)btlevtcmd_BtlIconDelete, -29999990, 196699, (s32)btlevtcmd_OnUnitFlag, -2,
    1073741824, 109, 33, 33, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 10, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"O_1", 65545, 10, 131096, -29999992, 0, 65545,
    20, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_INCLINE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"B_1", 65545, 52, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_4",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65540, 99, 33, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"O_2", 65545, 14, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_BORODO_LAUGH1", -250000000, 0, -250000000, 65545, 30, 262235, (s32)btlevtcmd_AnimeSetPoseTable,
    -2, 1, (s32)pose_table_item_have, 65540, 98, 65539, 98, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998,
    0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

static s32 escape_event[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_WAIT1", -250000000, 0, -29999985, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"R_3", 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    180, 0, 65546, 250, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 589915, (s32)btlevtcmd_SetMoveSoundDataWork,
    -2, (s32)"SFX_ENM_BORODO_JUMP1", 0, 0, -1, -1, 0, 0,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, -229979520, -2,
    786523, (s32)btlevtcmd_SetPartsBlur, -2, 1, 255, 255, 255, 255,
    100, 100, 100, 50, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2,
    1, 67108864, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_BORODO_ESCAPE1", -250000000, 0,
    -250000000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229990784, 524379, (s32)btlevtcmd_MovePosition, -2,
    300, -29999999, -29999998, 0, 0, 0, 786523, (s32)btlevtcmd_SetPartsBlur,
    -2, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 65545, 40, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    1, 67108864, 131163, (s32)evt_snd_sfxoff, -29999985, 196699, (s32)btlevtcmd_KillUnit, -2,
    0, 2, 1,
};

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_CheckUnitFlag, -2, 1073741824, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table))
        ELSE
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_item_have))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

