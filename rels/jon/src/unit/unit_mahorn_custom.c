#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "manager/evtmgr_cmd.h"
#include "string.h"
#include "system.h"
#include "memory.h"

EffectEntry* effMahorn2Entry(s32 type, f32 x, f32 y, f32 z, f32 a, f32 b, f32 c, f32 scale, f32 speed);
double __fabs(double x);
static inline double mahorn_fabs(double x) { return __fabs(x); }
void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);

USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeFlagOnOff);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetFirstAttackTarget);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_RecoverHp);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetAlpha);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHomePos);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRegistStatus);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_SpawnUnit);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StopWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff64);
USER_FUNC(evt_sub_intpl_get_value_para);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_random);
static USER_FUNC(hand_ctrl);
static USER_FUNC(hand_init);
static USER_FUNC(mahorn_copy_status);
static USER_FUNC(mahorn_get_bunsin);
static USER_FUNC(mahorn_get_live_num);
static USER_FUNC(set_hand_dest);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_magic);
static USER_FUNC(mahorn_shuffle);
static USER_FUNC(hand_end);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckDamageCode[];
extern s32 btlevtcmd_CheckDataOfDataTable[];
extern s32 btlevtcmd_CheckSpace[];
extern s32 btlevtcmd_ClearAllStatus[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionAdd[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_GetBackItem[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetPartsPos[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsBlur[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_snd_sfxon[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_mahorn_custom_negone_one_374;
__declspec(section ".data") s32 fd_mahorn_custom_neg_one_382[1];
__declspec(section ".data") s32 fd_mahorn_custom___local_PI_383[1];
__declspec(section ".data") s32 fd_mahorn_custom___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_mahorn_custom_one_negone_373;
__declspec(section ".data") s32 fd_mahorn_custom___local_PIO2_384[1];
__declspec(section ".data") s32 fd_mahorn_custom_one_381[1];
__declspec(section ".data") u64 fd_mahorn_custom_negone_one_360;
__declspec(section ".data") s32 fd_mahorn_custom_neg_one_365[1];
__declspec(section ".data") s32 fd_mahorn_custom___local_PI_366[1];
__declspec(section ".data") s32 fd_mahorn_custom___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_mahorn_custom_one_negone_359;
__declspec(section ".data") s32 fd_mahorn_custom___local_PIO2_367[1];
__declspec(section ".data") s32 fd_mahorn_custom_one_364[1];
BattleUnitKind unit_mahorn_custom;
BattleUnitKind unit_mahorn_custom_bunsin;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") s32 regist_bunsin[6];
static BattleUnitKindPart parts[5];
static s32 weapon_mahorn_attack_magic[48];
static s32 weapon_mahorn_all_attack_magic[48];
static s32 weapon_mahorn_attack_punch[48];
static s32 weapon_mahorn_trans_magic[48];
static s32 weapon_mahorn_yokeyoke_magic[48];
static s32 weapon_mahorn_dekadeka_magic[48];
static s32 weapon_mahorn_katikati_magic[48];
static s32 weapon_mahorn_recover_magic[48];
static __declspec(section ".data") s32 entry_mahorn[12];
static s32 attack_event[239];
static __declspec(section ".data") s32 attack_event_bunsin[7];
static PoseTableEntry pose_table[17];
static __declspec(section ".data") BattleDataEntry data_table[5];
static __declspec(section ".data") BattleDataEntry data_table_bunsin[3];
static s32 init_event[88];
static s32 alpha_down_event[98];
static s32 alpha_up_event[118];
static s32 hand_ctrl_event[23];
static s32 damage_event[66];
static s32 mahorn_subset_bunsin_all_kill[68];
static s32 mahorn_subset_dead_event[203];
static s32 mahorn_subset_blow_dead_event[78];
static s32 avoid_miss_event[16];
static s32 bunsin_kill_event[37];
static s32 attack_punch_event[429];
static s32 start_avoid[26];
static s32 attack_enemy_common_event[299];
static s32 attack_enemy_all_common_event[189];
static s32 attack_enemy_common_event_sub1[90];
static s32 attack_enemy_common_event_sub2[231];
static s32 attack_enemy_common_event_sub_no_hit[65];
static s32 attack_enemy_common_event_sub_hit[50];
static s32 attack_magic_event[54];
static s32 confuse_magic_event[41];
static s32 all_attack_magic_event[41];
static s32 support_friend_common_event[227];
static s32 dekadeka_magic_event[49];
static s32 katikati_magic_event[49];
static s32 trans_magic_event[49];
static s32 yokeyoke_magic_event[49];
static s32 recover_magic_event[70];
static s32 bunsin_event[152];
static s32 spawn_event[76];
static s32 wait_event[386];

__declspec(section ".data") u64 fd_mahorn_custom_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mahorn_custom_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mahorn_custom___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mahorn_custom___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mahorn_custom_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mahorn_custom___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mahorn_custom_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_mahorn_custom_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_mahorn_custom_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_mahorn_custom___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_mahorn_custom___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_mahorn_custom_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_mahorn_custom___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_mahorn_custom_one_364[] = {
    1065353216,
};

BattleUnitKind unit_mahorn_custom = {
    169,
    "btl_un_mahorn_custom",
    12,
    0,
    1,
    1,
    36,
    2,
    3,
    70,
    2,
    50,
    9999,
    48,
    44,
    0,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    -9,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    0.0f,
    16.0f,
    28.6f,
    10.0f,
    0.0f,
    22.0f,
    0.0f,
    48.0f,
    44.0f,
    0,
    0,
    0,
    2,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_MAHO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    5,
    parts,
    init_event,
    data_table,
};

BattleUnitKind unit_mahorn_custom_bunsin = {
    170,
    "btl_un_mahorn_custom_bunsin",
    12,
    0,
    1,
    1,
    1,
    2,
    0,
    60,
    0,
    50,
    9999,
    48,
    44,
    0,
    44,
    0.0f,
    22.0f,
    0.0f,
    0,
    -9,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    24.0f,
    0.0f,
    0.0f,
    16.0f,
    28.6f,
    10.0f,
    0.0f,
    22.0f,
    0.0f,
    48.0f,
    44.0f,
    0,
    0,
    0,
    2,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_MAHO_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x400004,
    &regist,
    5,
    parts,
    init_event,
    data_table_bunsin,
};

static __declspec(section ".data") BattleUnitDefense defence = {{5, 5, 5, 5, 5}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 30, 80, 100, 20, 100, 100, 40, 100, 75, 100, 75, 100, 80, 20, 10, 75, 100, 20, 100, 100, 20};

static __declspec(section ".data") s32 regist_bunsin[] = {
    100, 0, 0, 0, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_mahorn_custom", "c_maho_w", 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_mahorn_custom", "c_maho_w", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {3, "btl_un_mahorn_custom", "c_maho_w", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {4, "btl_un_mahorn_custom", "c_maho_w", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
    {5, "btl_un_mahorn_custom", "c_maho_w", 0.0f, 0.0f, 0.0f, 5.0f, 30.0f, 0.0f, 0.0f, 35.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x2010009, 0, pose_table},
};

static s32 weapon_mahorn_attack_magic[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 199, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_all_attack_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 67109634, 0, 7, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_attack_punch[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 770, 0, 135, 2, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_trans_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677918208, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_yokeyoke_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 6554368, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_dekadeka_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_katikati_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 536870912, 770, 0, 264, 2047, 0,
    0, 0, 0, 0, 0, 0, 6554371, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_mahorn_recover_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 0, 2047, 5376,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_mahorn[] = {
    (s32)&unit_mahorn_custom_bunsin, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_mahorn_attack_punch))
        CALL_CHILD(PTR(attack_punch_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    CALL(mahorn_get_live_num, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL_CHILD(PTR(bunsin_event))
        RETURN
        ELSE
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL_CHILD(PTR(subsetevt_confuse_flustered))
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(weapon_mahorn_attack_magic))
            CALL_CHILD(PTR(attack_magic_event))
            GOTO(99)
            ELSE
            LABEL(10)
            SET_VALUE(LW(0), 0)
            ADD(LW(0), 30)
            ADD(LW(0), 60)
            ADD(LW(0), 10)
            ADD(LW(0), 10)
            ADD(LW(0), 10)
            ADD(LW(0), 10)
            ADD(LW(0), 10)
            ADD(LW(0), 10)
            SUBTRACT(LW(0), 1)
            CALL(evt_sub_random, LW(0), LW(1))
            SET_VALUE(LW(0), 30)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_attack_punch))
                CALL_CHILD(PTR(attack_punch_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 60)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_attack_magic))
                CALL_CHILD(PTR(attack_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_all_attack_magic))
                CALL_CHILD(PTR(all_attack_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_dekadeka_magic))
                CALL_CHILD(PTR(dekadeka_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_katikati_magic))
                CALL_CHILD(PTR(katikati_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_trans_magic))
                CALL_CHILD(PTR(trans_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_yokeyoke_magic))
                CALL_CHILD(PTR(yokeyoke_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(0), 10)
            IF_INT_LESS(LW(1), LW(0))
                SET_VALUE(LW(9), PTR(weapon_mahorn_recover_magic))
                CALL_CHILD(PTR(recover_magic_event))
                GOTO(99)
            END_IF
            GOTO(10)
        END_IF
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(attack_event_bunsin)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static PoseTableEntry pose_table[] = {
    {1, "MAH_N_1"},
    {2, "MAH_Y_1"},
    {9, "MAH_Y_1"},
    {5, "MAH_K_1"},
    {4, "MAH_X_1"},
    {3, "MAH_X_1"},
    {28, "MAH_S_1"},
    {29, "MAH_Q_1"},
    {30, "MAH_Q_1"},
    {31, "MAH_A_1"},
    {39, "MAH_D_1"},
    {40, "MAH_W_1"},
    {42, "MAH_R_1"},
    {56, "MAH_X_1"},
    {57, "MAH_X_1"},
    {65, "MAH_T_1"},
    {69, "MAH_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, mahorn_subset_dead_event},
    {58, mahorn_subset_blow_dead_event},
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") BattleDataEntry data_table_bunsin[] = {
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, -2, LW(0), 20, LW(2))
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(hand_init, -2)
    CALL(set_hand_dest, -2, 2, FLOAT(-25.0f), FLOAT(30.0f), FLOAT(-10.0f))
    CALL(set_hand_dest, -2, 3, FLOAT(25.0f), FLOAT(30.0f), FLOAT(10.0f))
    CALL(set_hand_dest, -2, 4, FLOAT(-25.0f), FLOAT(10.0f), FLOAT(-10.0f))
    CALL(set_hand_dest, -2, 5, FLOAT(25.0f), FLOAT(10.0f), FLOAT(10.0f))
    SPAWN_EVENT(PTR(hand_ctrl_event))
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 6, 0)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(alpha_down_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 254)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 255, 0, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 2, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 3, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 4, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 5, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 1, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 2, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 3, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 4, 33554432)
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 5, 33554432)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

static EVT_BEGIN(alpha_up_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 1, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 2, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 3, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 4, 33554432)
    CALL(btlevtcmd_OffPartsAttribute, LW(0), 5, 33554432)
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 0, 254, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 2, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 3, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 4, LW(1))
        CALL(btlevtcmd_SetAlpha, LW(0), 5, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 2, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 3, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 4, 255)
    CALL(btlevtcmd_SetAlpha, LW(0), 5, 255)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

static EVT_BEGIN(hand_ctrl_event)
    LABEL(0)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(hand_ctrl, -2)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, -2, 5, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, -2, 5, 1)
        END_IF
        ELSE
        SET_VALUE(LW(0), -2)
        CALL_CHILD(PTR(bunsin_kill_event))
        RETURN
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, -2, 5, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(PTR(mahorn_subset_bunsin_all_kill))
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(mahorn_subset_bunsin_all_kill)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
            SET_VALUE(LW(0), LW(1))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(2))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(3))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(4))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            LOOP(0)
                CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 mahorn_subset_dead_event[] = {
    262235, (s32)btlevtcmd_CheckDataOfDataTable, -29999990, -30000000, 50, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_RunDataEventChild, -29999990, 50, 33, 131122, -30000000, 48,
    196699, (s32)btlevtcmd_OnUnitFlag, -29999990, 134217728, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_1",
    -250000000, 0, -250000000, 65539, 10, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -29999990, 0, -15, 0, 131126, -30000000, 1,
    131099, -30000000, 0, 65540, 10, 33, 327771, (s32)btlevtcmd_SetRotate,
    -29999990, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2",
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
    -30000000, 6, 33, 327771, (s32)btlevtcmd_SetRotateOffset, -29999990, 0, 0,
    0, 131122, -30000000, 30, 65539, 20, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -29999990, 3, 0, 0, 131126, -30000000,
    1, 131099, -30000000, 0, 65540, 20, 33, 131163,
    (s32)btlevtcmd_GetBackItem, -29999990, 131163, (s32)btlevtcmd_ClearAllStatus, -29999990, 196699, (s32)btlevtcmd_OnAttribute, -29999990,
    16777216, 196699, (s32)btlevtcmd_OnAttribute, -29999990, 536870912, 65630, (s32)mahorn_subset_bunsin_all_kill, 262235,
    (s32)btlevtcmd_CheckDamageCode, -29999990, 1024, -30000000, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_KillUnit, -29999990, 0, 32, 196699, (s32)btlevtcmd_KillUnit, -29999990, 2,
    33, 2, 1,
};

static s32 mahorn_subset_blow_dead_event[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 65630, (s32)mahorn_subset_bunsin_all_kill,
    196699, (s32)btlevtcmd_KillUnit, -2, 0, 2, 1,
};

static EVT_BEGIN(avoid_miss_event)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), -2)
        CALL_CHILD(PTR(bunsin_kill_event))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(bunsin_kill_event)
    CALL(btlevtcmd_GetUnitId, LW(0), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, LW(0), 6, LW(1))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetUnitWork, LW(0), 6, 1)
    CALL_CHILD(PTR(alpha_down_event))
    LABEL(10)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_KillUnit, LW(0), 0)
    RETURN
EVT_END()

static s32 attack_punch_event[] = {
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
    393307, (s32)set_hand_dest, -2, 2, -230016384, -229970304, -230005120, 393307,
    (s32)set_hand_dest, -2, 3, -229983616, -229970304, -229994880, 393307, (s32)set_hand_dest,
    -2, 4, -230016384, -229988736, -230005120, 393307, (s32)set_hand_dest, -2,
    5, -229983616, -229988736, -229994880, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_ATTACK1",
    -250000000, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131096, -29999985, -1, 131125, -30000000, 35,
    32, 131126, -30000000, 35, 33, 327771, (s32)btlevtcmd_JumpSetting, -2,
    0, 4, -229999999, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 20,
    -29999998, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MAH_S_1",
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"MAH_Z_2", 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    3, (s32)"MAH_Z_2", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 4, (s32)"MAH_Z_2", 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"MAH_Z_2", 131122, -29999990, 2, 65541,
    4, 786523, (s32)btlevtcmd_SetPartsBlur, -2, -29999990, 255, 255, 255,
    255, 255, 255, 255, 100, 0, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -2, -29999990, 67108864, 131125, -29999990, 1, 6, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_ATTACK2", -250000000, 0, -250000000, 65541, 25,
    131122, -29999990, 2, 65541, 4, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    -29999990, -30000000, -29999999, -29999998, 131096, -29999985, -1, 196699,
    (s32)evt_sub_random, 120, -29999989, 131125, -29999989, -90, 32, 196699,
    (s32)evt_sub_random, 120, -29999989, 131127, -29999989, -1, 131125, -29999989,
    90, 33, 196699, (s32)evt_sub_random, 60, -29999988, 131125, -29999988,
    -20, 393307, (s32)set_hand_dest, -2, -29999990, -29999989, -29999988, -29999998,
    131125, -29999990, 1, 6, 65545, 2, 6, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MAH_S_1", 393307, (s32)set_hand_dest, -2, 2,
    -230016384, -229970304, -230005120, 393307, (s32)set_hand_dest, -2, 3, -229983616,
    -229970304, -229994880, 393307, (s32)set_hand_dest, -2, 4, -230016384, -229988736,
    -230005120, 393307, (s32)set_hand_dest, -2, 5, -229983616, -229988736, -229994880,
    131122, -29999990, 2, 65541, 4, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    -29999990, 67108864, 131125, -29999990, 1, 6, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 0, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 65539,
    90, 65545, 30, 65540, 98, 65539, 91, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999991, 256, -29999995, 65545, 30, 65540, 98, 65539,
    98, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_ATTACK1_2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 0, 6, -229999999, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 65545, 45, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

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

static s32 attack_enemy_common_event[] = {
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_CHARGE1", -250000000, 0,
    -250000000, 393307, (s32)mahorn_get_bunsin, -29999989, -29999988, -29999987, -29999986, -30000000,
    131122, -29999985, -29999989, 65628, (s32)attack_enemy_common_event_sub1, 131122, -29999985, -29999988,
    65628, (s32)attack_enemy_common_event_sub1, 131122, -29999985, -29999987, 65628, (s32)attack_enemy_common_event_sub1, 131122,
    -29999985, -29999986, 65628, (s32)attack_enemy_common_event_sub1, 131122, -29999985, -2, 65630,
    (s32)attack_enemy_common_event_sub1, 110, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC2", -250000000, 0,
    -250000000, 65545, 25, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC2", -250000000,
    0, -250000000, 112, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996,
    -29999991, 0, -29999995, 65570, -29999995, 65579, 4, 65540,
    90, 46, 65572, 3, 65540, 90, 46, 65572,
    6, 65540, 90, 65572, 2, 65540, 90, 65572,
    1, 65540, 91, 46, 42, 65540, 98, 46,
    65539, 90, 110, 65545, 60, 65541, 0, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131096, -30000000, -1, 196699, (s32)eff_magic_get_posX,
    -2, -30000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993,
    -29999992, 131100, -30000000, -29999994, 65630, (s32)start_avoid, 7, 33,
    32, 196699, (s32)eff_magic_get_posX, -2, -30000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -29999994, -29999993, -29999992, 131101, -30000000, -29999994, 65630,
    (s32)start_avoid, 7, 33, 33, 65545, 1, 6, 112,
    393307, (s32)mahorn_get_bunsin, -29999989, -29999988, -29999987, -29999986, -30000000, 131122,
    -29999985, -29999989, 65628, (s32)attack_enemy_common_event_sub_no_hit, 131122, -29999985, -29999988, 65628,
    (s32)attack_enemy_common_event_sub_no_hit, 131122, -29999985, -29999987, 65628, (s32)attack_enemy_common_event_sub_no_hit, 131122, -29999985,
    -29999986, 65628, (s32)attack_enemy_common_event_sub_no_hit, 131122, -29999985, -2, 65630, (s32)attack_enemy_common_event_sub_no_hit,
    65540, 98, 65539, 91, 393307, (s32)mahorn_get_bunsin, -29999989, -29999988,
    -29999987, -29999986, -30000000, 131122, -29999985, -29999989, 65628, (s32)attack_enemy_common_event_sub_hit,
    131122, -29999985, -29999988, 65628, (s32)attack_enemy_common_event_sub_hit, 131122, -29999985, -29999987,
    65628, (s32)attack_enemy_common_event_sub_hit, 131122, -29999985, -29999986, 65628, (s32)attack_enemy_common_event_sub_hit, 131122,
    -29999985, -2, 65630, (s32)attack_enemy_common_event_sub_hit, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 98, 65539, 98, 393307, (s32)mahorn_get_bunsin, -29999989, -29999988,
    -29999987, -29999986, -30000000, 131097, -29999989, -1, 131163, (s32)btlevtcmd_StartWaitEvent,
    -29999989, 33, 131097, -29999988, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -29999988,
    33, 131097, -29999987, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -29999987, 33,
    131097, -29999986, -1, 131163, (s32)btlevtcmd_StartWaitEvent, -29999986, 33, 65545,
    30, 2, 1,
};

static s32 attack_enemy_all_common_event[] = {
    131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996,
    65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_CHARGE1", -250000000, 0,
    -250000000, 131122, -29999985, -2, 65630, (s32)attack_enemy_common_event_sub1, 110, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC2", -250000000, 0, -250000000, 65545, 25,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC2", -250000000, 0, -250000000, 112,
    131122, -29999985, -2, 65630, (s32)attack_enemy_common_event_sub2, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 131122, -29999994, 0, 65539, 10, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 0, -29999995, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 983131, (s32)evt_eff64, (s32)"",
    (s32)"thunder_n64", 4, -30000000, -29999999, -29999998, 0, 0, 0,
    0, 0, 0, 0, 0, 65570, -29999995, 65579,
    4, 65540, 90, 46, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 65540, 90, 46, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1, 65540,
    91, 46, 42, 65540, 98, 46, 65539, 90,
    65540, 97, 65539, 91, 131096, -29999994, 0, 196699,
    (s32)btlevtcmd_ResultACDefence, -29999997, -29999991, 131122, -29999994, 1, 33, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995, 65540,
    97, 65539, 97, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 98, 33, 65540, 10, 65539,
    98, 65545, 30, 2, 1,
};

static EVT_BEGIN(attack_enemy_common_event_sub1)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_StopWaitEvent, LW(15))
    CALL(btlevtcmd_GetPos, LW(15), LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_eff64, STRING(""), STRING("akari_charge_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 70, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, LW(15), 1, STRING("MAH_A_4"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_5A"))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_5A"))
    CALL(set_hand_dest, LW(15), 2, FLOAT(-16.0f), FLOAT(29.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, LW(15), 3, FLOAT(16.0f), FLOAT(29.0f), FLOAT(5.0f))
    CALL(set_hand_dest, LW(15), 4, FLOAT(-16.0f), FLOAT(11.0f), FLOAT(-5.0f))
    CALL(set_hand_dest, LW(15), 5, FLOAT(16.0f), FLOAT(11.0f), FLOAT(5.0f))
    WAIT_FRAMES(50)
    RETURN
EVT_END()

static EVT_BEGIN(attack_enemy_common_event_sub2)
    IF_INT_EQUAL(LW(15), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_StopWaitEvent, LW(15))
    CALL(btlevtcmd_AnimeChangePose, LW(15), 1, STRING("MAH_A_1"))
    BEGIN_INLINE_EVENT
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(-16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 2, LW(0), FLOAT(29.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 2, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 2, LW(0), FLOAT(29.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(7)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 5, LW(0), FLOAT(11.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 5, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 5, LW(0), FLOAT(11.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(10)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(-16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 4, LW(0), FLOAT(11.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 4, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 4, LW(0), FLOAT(11.0f), FLOAT(-5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(15)
        LOOP(2)
            SET_FLOAT_VALUE(LW(0), FLOAT(16.0f))
            SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
            CALL(btlevtcmd_GetFaceDirection, -2, LW(2))
            MULTIPLY_FLOAT(LW(1), LW(2))
            CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_2B"))
            ADD(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 3, LW(0), FLOAT(29.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
            CALL(btlevtcmd_AnimeChangePose, LW(15), 3, STRING("MAH_S_2A"))
            SUBTRACT(LW(0), LW(1))
            CALL(set_hand_dest, LW(15), 3, LW(0), FLOAT(29.0f), FLOAT(5.0f))
            WAIT_FRAMES(20)
        END_LOOP
    END_INLINE_EVENT
    WAIT_FRAMES(55)
    RETURN
EVT_END()

static s32 attack_enemy_common_event_sub_no_hit[] = {
    131096, -29999985, -1, 2, 33, 327771, (s32)btlevtcmd_GetPos, -29999985,
    -30000000, -29999999, -29999998, 131125, -29999999, 10, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999990, -29999989, -29999988, 262235, (s32)btlevtcmd_GetStageSize, -29999990,
    -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -29999985, -29999987, 131127, -29999990,
    -29999987, 131126, -29999989, 5, 393307, (s32)eff_magic, -29999985, -29999990,
    -29999989, -29999988, 40, 65630, (s32)attack_enemy_common_event_sub2, 65545, 5, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC1", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_MAHO_MAGIC3", -250000000, 0, -250000000, 65545, 40, 2,
    1,
};

static s32 attack_enemy_common_event_sub_hit[] = {
    131096, -29999985, -1, 2, 33, 327771, (s32)btlevtcmd_GetPos, -29999985,
    -30000000, -29999999, -29999998, 131125, -29999999, 10, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999990, -29999989, -29999988, 393307, (s32)eff_magic, -29999985,
    -29999990, -29999989, -29999988, 20, 65630, (s32)attack_enemy_common_event_sub2, 65545, 5,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC1", -250000000, 0, -250000000, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC3", -250000000, 0, -250000000, 65545, 20,
    2, 1,
};

static EVT_BEGIN(attack_magic_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL_CHILD(PTR(attack_enemy_common_event))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(confuse_magic_event)
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
    CALL_CHILD(PTR(attack_enemy_common_event))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(all_attack_magic_event)
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
    CALL_CHILD(PTR(attack_enemy_all_common_event))
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static s32 support_friend_common_event[] = {
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_CHARGE1",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 131125, -29999999, 40, 983131, (s32)evt_eff64, (s32)"", (s32)"akari_charge_n64",
    0, -30000000, -29999999, -29999998, -229998976, 70, 0, 0,
    0, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"MAH_A_4", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"MAH_S_5A", 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 3, (s32)"MAH_S_5A", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 4, (s32)"MAH_S_5A",
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"MAH_S_5A", 393307, (s32)set_hand_dest, -2,
    2, -230016384, -229970304, -230005120, 393307, (s32)set_hand_dest, -2, 3,
    -229983616, -229970304, -229994880, 393307, (s32)set_hand_dest, -2, 4, -230016384,
    -229988736, -230005120, 393307, (s32)set_hand_dest, -2, 5, -229983616, -229988736,
    -229994880, 65545, 50, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"MAH_A_2A",
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"MAH_S_4A", 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    3, (s32)"MAH_S_4A", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 4, (s32)"MAH_S_4A", 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 5, (s32)"MAH_S_4A", 393307, (s32)set_hand_dest, -2, 2,
    -230020480, -229959040, -230015360, 393307, (s32)set_hand_dest, -2, 3, -229979520,
    -229959040, -229984640, 393307, (s32)set_hand_dest, -2, 4, -230020480, -230000000,
    -230015360, 393307, (s32)set_hand_dest, -2, 5, -229979520, -230000000, -229984640,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC4", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999, 15,
    983131, (s32)evt_eff, (s32)"", (s32)"mahorn", 0, -30000000, -29999999, -29999998,
    -229998567, 2, 30, 0, 0, 0, 0, 0,
    65545, 30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_MAGIC4", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_GetPos, -29999997, -30000000, -29999999, -29999998, 131125,
    -29999999, 15, 983131, (s32)evt_eff, (s32)"", (s32)"mahorn", 0, -30000000,
    -29999999, -29999998, -229998567, 2, 30, 0, 0, 0,
    0, 0, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"MAH_A_2C", 2, 1,
};

static EVT_BEGIN(dekadeka_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(support_friend_common_event))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(katikati_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(support_friend_common_event))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(trans_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(support_friend_common_event))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(yokeyoke_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(support_friend_common_event))
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(recover_magic_event)
    SET_VALUE(LW(3), -2)
    SET_VALUE(LW(4), 1)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(support_friend_common_event))
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 10)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    ADD(LW(1), 30)
    ADD(LW(2), 10)
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 10, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(10)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static s32 bunsin_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 65630, (s32)support_friend_common_event,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_OFFSHOOT1", -250000000, 0, -250000000, 131122,
    -30000000, -2, 65630, (s32)alpha_down_event, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    40, 131122, -29999996, -30000000, 131099, -29999996, 0, 131126,
    -29999998, 10, 589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999, -29999998,
    40, 0, 0, 0, 131096, -29999997, -1, 65630,
    (s32)spawn_event, 33, 32, 7, 33, 6, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 40, 131100, -30000000, 170, 131125, -29999998,
    10, 589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999, -29999998, 40,
    0, 0, 0, 131096, -29999997, -1, 65630, (s32)spawn_event,
    33, 32, 7, 33, 6, 65627, (s32)mahorn_shuffle, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_MAHO_OFFSHOOT2", -250000000, 0,
    -250000000, 131122, -30000000, -2, 65628, (s32)alpha_up_event, 327771, (s32)mahorn_get_bunsin,
    -29999999, -29999998, -29999997, -29999996, 131122, -30000000, -29999999, 65628,
    (s32)alpha_up_event, 131122, -30000000, -29999998, 65628, (s32)alpha_up_event, 131122, -30000000,
    -29999997, 65628, (s32)alpha_up_event, 131122, -30000000, -29999996, 65628, (s32)alpha_up_event,
    65545, 60, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static EVT_BEGIN(spawn_event)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_mahorn), 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 1, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 2, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 3, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 4, 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 5, 0)
    WAIT_FRAMES(2)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(13))
    CALL(mahorn_copy_status, LW(13), LW(3))
    CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
    CALL(btlevtcmd_SetUnitWork, LW(3), 4, 1)
    CALL(btlevtcmd_SetEventAttack, LW(3), PTR(attack_event_bunsin))
    CALL(btlevtcmd_SetRegistStatus, LW(3), PTR(regist_bunsin))
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, 16384)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_GetUnitWork, -2, 4, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(mahorn_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
        IF_INT_NOT_EQUAL(LW(1), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(1), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(2), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(2), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(3), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(3), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(4), -1)
            CALL(btlevtcmd_AnimeChangePoseFromTable, LW(4), 1)
        END_IF
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 9, LW(13))
    CALL(btlevtcmd_CheckStatus, -2, 1, LW(14))
    CALL(btlevtcmd_CheckStatus, -2, 2, LW(15))
    OR(LW(15), LW(13))
    OR(LW(15), LW(14))
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, -2, 4, STRING("MAH_Z_2"))
        CALL(btlevtcmd_AnimeChangePose, -2, 5, STRING("MAH_Z_2"))
        ELSE
        BEGIN_SIBLING_EVENT
            LABEL(10)
            CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, -2, 2, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(10)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(11)
            CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, -2, 3, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(11)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(12)
            CALL(btlevtcmd_AnimeChangePose, -2, 4, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, -2, 4, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(12)
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LABEL(13)
            CALL(btlevtcmd_AnimeChangePose, -2, 5, STRING("MAH_S_4A"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            CALL(btlevtcmd_AnimeChangePose, -2, 5, STRING("MAH_S_4B"))
            CALL(evt_sub_random, 15, LW(0))
            ADD(LW(0), 15)
            WAIT_FRAMES(LW(0))
            GOTO(13)
        END_SIBLING_EVENT
    END_IF
    BEGIN_SIBLING_EVENT
        LABEL(0)
        CALL(set_hand_dest, -2, 2, FLOAT(-25.0f), FLOAT(30.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, -2, 2, FLOAT(-15.0f), FLOAT(40.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(0)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LABEL(1)
        CALL(set_hand_dest, -2, 3, FLOAT(25.0f), FLOAT(30.0f), FLOAT(10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, -2, 3, FLOAT(15.0f), FLOAT(40.0f), FLOAT(10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(1)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LABEL(2)
        CALL(set_hand_dest, -2, 4, FLOAT(-25.0f), FLOAT(10.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        CALL(set_hand_dest, -2, 4, FLOAT(-15.0f), FLOAT(0.0f), FLOAT(-10.0f))
        CALL(evt_sub_random, 15, LW(0))
        ADD(LW(0), 15)
        WAIT_FRAMES(LW(0))
        GOTO(2)
    END_SIBLING_EVENT
    LABEL(3)
    CALL(set_hand_dest, -2, 5, FLOAT(25.0f), FLOAT(10.0f), FLOAT(10.0f))
    CALL(evt_sub_random, 15, LW(0))
    ADD(LW(0), 15)
    WAIT_FRAMES(LW(0))
    CALL(set_hand_dest, -2, 5, FLOAT(15.0f), FLOAT(0.0f), FLOAT(10.0f))
    CALL(evt_sub_random, 15, LW(0))
    ADD(LW(0), 15)
    WAIT_FRAMES(LW(0))
    GOTO(3)
    RETURN
EVT_END()

static USER_FUNC(eff_magic_get_posX) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, *args++));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = (EffectEntry*)unit->work[7];
    f32* work = eff->userdata;
    s32 i;

    for (i = 0; i < eff->count; i++, work += 15) {
        if (((s32*)work)[11] == 3) {
            evtSetFloat(event, *args++, work[1]);
            break;
        }
    }
    if (i == eff->count) {
        evtSetFloat(event, *args++, 0.0f);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_magic) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 time = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    x += unit->mSizeMultiplier * unit->faceDirection;
    y += 18.0f * unit->mSizeMultiplier;
    z += 5.0f;
    unit->work[7] = (s32)effMahorn2Entry(0, x, y, z, a, y, z, unit->mSizeMultiplier, mahorn_fabs((a - x) / time));
    return EVT_RETURN_DONE;
}

static USER_FUNC(mahorn_copy_status) {
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    unit2->currentHp = unit1->currentHp;
    memcpy(&unit2->mSleepTurns, &unit1->mSleepTurns, 0x1E);
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

static USER_FUNC(mahorn_shuffle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* kamecs[6];
    s32 n = 0;
    s32 i;

    // the real wizzerd and its copies
    for (i = 0; i < 64; i++) {
        kamecs[n] = wp->units[i];
        if (kamecs[n] != NULL && (kamecs[n]->currentKind == 0x80 || kamecs[n]->currentKind == 0x81 || kamecs[n]->currentKind == 0xA9 || kamecs[n]->currentKind == 0xAA)) {
            n++;
        }
    }
    for (i = 0; i < 10; i++) {
        s32 a = irand(n);
        s32 b = irand(n);
        BattleUnit* ua = kamecs[a];
        BattleUnit* ub = kamecs[b];
        f32 tmp;

        tmp = ua->mPosition.x;
        ua->mPosition.x = ub->mPosition.x;
        ub->mPosition.x = tmp;
        tmp = ua->mHomePosition.x;
        ua->mHomePosition.x = ub->mHomePosition.x;
        ub->mHomePosition.x = tmp;
        tmp = ua->mPosition.z;
        ua->mPosition.z = ub->mPosition.z;
        ub->mPosition.z = tmp;
        tmp = ua->mHomePosition.z;
        ua->mHomePosition.z = ub->mHomePosition.z;
        ub->mHomePosition.z = tmp;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(mahorn_get_bunsin) {
    s32* args = event->args;
    s32 copies[4];
    s32 n = 0;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // indices of the wizzerd's copies
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x81 || unit->currentKind == 0xAA)) {
            copies[n] = i;
            n++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i < n) {
            evtSetValue(event, *args++, copies[i]);
        } else {
            evtSetValue(event, *args++, -1);
        }
    }
    evtSetValue(event, *args, n);
    return EVT_RETURN_DONE;
}

static USER_FUNC(set_hand_dest) {
    s32 hand;
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id;
    f32* dest;
    f32 x;
    f32 y;
    f32 z;

    id = evtGetValue(event, args[0]);
    hand = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    hand -= 2;
    dest = (f32*)unit->work[hand];
    if (BtlUnit_CheckStatus(unit, 10)) {
        dest[0] = 1.25f * -x;
        dest[1] = 1.25f * y;
        dest[2] = 1.25f * z;
    } else if (BtlUnit_CheckStatus(unit, 11)) {
        dest[0] = 0.75f * -x;
        dest[1] = 0.75f * y;
        dest[2] = 0.75f * z;
    } else {
        dest[0] = -x;
        dest[1] = y;
        dest[2] = z;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(hand_ctrl) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s8 turns;
    s8 strength;
    BattleUnitPart* part;
    f32* dest;
    Vec* scale;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_GetStatus(unit, 2, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 9, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 1, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    for (j = 0, i = 2; i <= 5; i++, j++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        dest = (f32*)unit->work[j];
        scale = &part->mBaseScale;
        x = part->mPositionOffset.x * scale->x;
        y = part->mPositionOffset.y * scale->y;
        z = part->mPositionOffset.z * scale->z;
        x += (dest[0] - x) / 10.0f;
        y += (dest[1] - y) / 10.0f;
        z += (dest[2] - z) / 10.0f;
        part->mPositionOffset.x = x;
        part->mPositionOffset.y = y;
        part->mPositionOffset.z = z;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(hand_end) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 i;
    s32 j;

    for (i = 2, j = 0; i <= 5; i++, j++) {
        if ((void*)unit->work[j] != NULL) {
            BattleFree((void*)unit->work[j]);
            unit->work[j] = 0;
        }
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(hand_init) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    f32 x;
    f32 y;
    f32 z;
    f32* dest;
    s32 i;
    s32 j;

    BtlUnit_GetPos(unit, &x, &y, &z);
    for (j = 0, i = 2; i <= 5; i++, j++) {
        BtlUnit_SetAnim(BtlUnit_GetPartsPtr(unit, i), "MAH_Z_2");
        dest = __memAlloc((HEAP_TYPE)4, 12);
        unit->work[j] = (s32)dest;
        dest[0] = 0.0f;
        dest[1] = 0.0f;
        dest[2] = 0.0f;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(mahorn_get_live_num) {
    s32 i;
    s32* args = event->args;
    s32 num = 0;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->mAlliance == 1 && !BtlUnit_CheckStatus(unit, 0x1B)) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}

