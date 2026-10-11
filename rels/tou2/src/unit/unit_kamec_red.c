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

EffectEntry* effMagic1N64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 arg7);
EffectEntry* effPokopiPchargeN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
EffectEntry* effThunderflareN64Entry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_AnimeFlagOnOff);
USER_FUNC(btlevtcmd_AnimeSetPoseTable);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeDataTable);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHp);
USER_FUNC(btlevtcmd_GetMaxHp);
USER_FUNC(btlevtcmd_GetPartsPos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetSelectEnemy);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_KillUnit);
USER_FUNC(btlevtcmd_OffAttribute);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnAttribute);
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
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
static USER_FUNC(eff_magic);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_eff);
USER_FUNC(evt_sub_intpl_get_value_para);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_random);
static USER_FUNC(kamec_copy_status);
static USER_FUNC(kamec_get_bunsin);
static USER_FUNC(kamec_get_live_num);
static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_staff2);
static USER_FUNC(eff_staff1);
static USER_FUNC(kamec_shuffle);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Damage[];
extern s32 btldefaultevt_Dummy[];
extern s32 btlevtcmd_AddRotate[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
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
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_JumpPosition[];
extern s32 btlevtcmd_OnUnitFlag[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_RunDataEventChild[];
extern s32 btlevtcmd_SetFallAccel[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetRotate[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_snd_sfxon[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_kamec_red_negone_one_374;
__declspec(section ".data") s32 fd_kamec_red_neg_one_382[1];
__declspec(section ".data") s32 fd_kamec_red___local_PI_383[1];
__declspec(section ".data") s32 fd_kamec_red___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_kamec_red_one_negone_373;
__declspec(section ".data") s32 fd_kamec_red___local_PIO2_384[1];
__declspec(section ".data") s32 fd_kamec_red_one_381[1];
__declspec(section ".data") u64 fd_kamec_red_negone_one_360;
__declspec(section ".data") s32 fd_kamec_red_neg_one_365[1];
__declspec(section ".data") s32 fd_kamec_red___local_PI_366[1];
__declspec(section ".data") s32 fd_kamec_red___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_kamec_red_one_negone_359;
__declspec(section ".data") s32 fd_kamec_red___local_PIO2_367[1];
__declspec(section ".data") s32 fd_kamec_red_one_364[1];
BattleUnitKind unit_kamec_red;
BattleUnitKind unit_kamec_red_bunsin;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static __declspec(section ".data") s32 regist_bunsin[6];
static PoseTableEntry pose_table[17];
static PoseTableEntry pose_table_sky[17];
static __declspec(section ".data") BattleDataEntry data_table[5];
static __declspec(section ".data") s32 data_table_sky[12];
static __declspec(section ".data") BattleDataEntry data_table_bunsin[3];
static __declspec(section ".data") s32 data_table_sky_bunsin[8];
static BattleUnitKindPart parts[2];
static s32 weapon_kamec_attack_magic[48];
static s32 weapon_kamec_dekadeka_magic[48];
static s32 weapon_kamec_biribiri_magic[48];
static s32 weapon_kamec_trans_magic[48];
static s32 weapon_kamec_katikati_magic[48];
static s32 weapon_kamec_recover_magic[48];
static s32 weapon_kamec_all_recover_magic[48];
static __declspec(section ".data") s32 entry_kamec[12];
static s32 init_event[22];
static s32 init_event2[87];
static s32 alpha_down_event[58];
static s32 alpha_up_event[58];
static s32 damage_event[66];
static s32 kamec_subset_bunsin_all_kill[68];
static s32 kamec_subset_dead_event[203];
static s32 kamec_subset_blow_dead_event[78];
static s32 avoid_miss_event[16];
static s32 bunsin_kill_event[37];
static __declspec(section ".data") s32 phase_event[2];
static s32 dmg_fall_event[159];
static s32 dmg_first_attack_pos[19];
static s32 attack_event[296];
static s32 ground_magic_common_event1[305];
static s32 ground_magic_common_event2[61];
static s32 sky_magic_common_event[258];
static s32 magic_common_event1[27];
static s32 magic_common_event2[16];
static s32 start_avoid[26];
static s32 attack_magic_event[325];
static s32 attack_magic_event_sub_no_hit[45];
static s32 attack_magic_event_sub_hit[30];
static s32 support_magic_event[140];
static __declspec(section ".data") s32 dekadeka_magic_event[7];
static __declspec(section ".data") s32 katikati_magic_event[7];
static __declspec(section ".data") s32 biribiri_magic_event[7];
static __declspec(section ".data") s32 trans_magic_event[7];
static s32 recover_magic_event[142];
static s32 all_recover_magic_event[180];
static s32 bunsin_magic_event[160];
static s32 spawn_event[66];
static s32 wait_event[55];

static USER_FUNC(eff_magic_get_posX) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    evtSetFloat(event, args[1], ((f32*)((EffectEntry*)unit->work[5])->userdata)[4]);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_kamec_red_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kamec_red_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kamec_red___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kamec_red___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kamec_red_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kamec_red___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kamec_red_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_kamec_red_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_kamec_red_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_kamec_red___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_kamec_red___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_kamec_red_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_kamec_red___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_kamec_red_one_364[] = {
    1065353216,
};

BattleUnitKind unit_kamec_red = {
    49,
    "btl_un_kamec_red",
    7,
    0,
    1,
    1,
    17,
    0,
    2,
    70,
    2,
    50,
    9999,
    42,
    42,
    0,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    27.3f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    42.0f,
    42.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KAMEKU_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    2,
    parts,
    init_event,
    data_table,
};

BattleUnitKind unit_kamec_red_bunsin = {
    50,
    "btl_un_kamec_red_bunsin",
    7,
    0,
    1,
    1,
    0,
    0,
    0,
    70,
    0,
    50,
    9999,
    42,
    42,
    0,
    42,
    0.0f,
    21.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    0.0f,
    21.0f,
    27.3f,
    0.0f,
    0.0f,
    21.0f,
    0.0f,
    42.0f,
    42.0f,
    0,
    0,
    0,
    2,
    0,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KAMEKU_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x400000,
    &regist,
    2,
    parts,
    init_event,
    data_table_bunsin,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {70, 75, 80, 100, 70, 100, 100, 70, 100, 90, 100, 90, 100, 95, 80, 70, 80, 100, 80, 100, 100, 95};

static __declspec(section ".data") s32 regist_bunsin[] = {
    0, 0, 0, 0, 0, 0,
};

static PoseTableEntry pose_table[] = {
    {1, "KMR_N_1"},
    {2, "KMR_Y_1"},
    {9, "KMR_Y_1"},
    {5, "KMR_K_1"},
    {4, "KMR_X_1"},
    {3, "KMR_X_1"},
    {28, "KMR_S_1"},
    {29, "KMR_Q_1"},
    {30, "KMR_Q_1"},
    {31, "KMR_S_1"},
    {39, "KMR_D_1"},
    {42, "KMR_R_1"},
    {40, "KMR_W_1"},
    {56, "KMR_X_1"},
    {57, "KMR_X_1"},
    {65, "KMR_T_1"},
    {69, "KMR_S_1"},
};

static PoseTableEntry pose_table_sky[] = {
    {1, "KMR_N_2"},
    {2, "KMR_Y_2"},
    {9, "KMR_Y_2"},
    {5, "KMR_K_2"},
    {4, "KMR_X_2"},
    {3, "KMR_X_2"},
    {28, "KMR_S_2"},
    {29, "KMR_Q_2"},
    {30, "KMR_Q_2"},
    {31, "KMR_S_2"},
    {39, "KMR_D_2"},
    {42, "KMR_R_2"},
    {40, "KMR_W_2"},
    {56, "KMR_X_2"},
    {57, "KMR_X_2"},
    {65, "KMR_T_2"},
    {69, "KMR_S_2"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, kamec_subset_dead_event},
    {58, kamec_subset_blow_dead_event},
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") s32 data_table_sky[] = {
    49, (s32)kamec_subset_dead_event, 58, (s32)kamec_subset_blow_dead_event, 46, (s32)avoid_miss_event, 14, (s32)dmg_fall_event,
    48, (s32)dmg_first_attack_pos, 0, 0,
};

static __declspec(section ".data") BattleDataEntry data_table_bunsin[] = {
    {46, avoid_miss_event},
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

static __declspec(section ".data") s32 data_table_sky_bunsin[] = {
    46, (s32)avoid_miss_event, 14, (s32)dmg_fall_event, 48, (s32)dmg_first_attack_pos, 0, 0,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_kamec_red", "c_kamek_r", 0.0f, 0.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f, 45.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
    {2, "btl_un_kamec_red", "c_kamek_r", 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static s32 weapon_kamec_attack_magic[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 199, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_dekadeka_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 264, 2047, -2147483648,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_biribiri_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 264, 2047, -2147483648,
    0, 0, 100, 50331648, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_trans_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 264, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677918208, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_katikati_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 264, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554371, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_recover_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 536870912, 770, 0, 0, 2047, 5376,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_kamec_all_recover_magic[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603360, 536870912, 770, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static __declspec(section ".data") s32 entry_kamec[] = {
    (s32)&unit_kamec_red_bunsin, 16777216, 67108868, -998637568, -998637568, -998637568, 0, 0,
    0, 0, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 4, 0)
    CALL_CHILD(PTR(init_event2))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(init_event2)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetPoseTable, -2, 1, PTR(pose_table_sky))
        CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_sky))
            ELSE
            CALL(btlevtcmd_ChangeDataTable, -2, PTR(data_table_sky_bunsin))
        END_IF
        CALL(btlevtcmd_OnAttribute, -2, 4)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 2097152)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 2048)
        CALL(btlevtcmd_OnPartsAttribute, -2, 1, 4194304)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, -2, LW(0), 40, LW(2))
        CALL(btlevtcmd_SetHomePos, -2, LW(0), 40, LW(2))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(alpha_down_event)
    IF_INT_EQUAL(LW(0), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 254)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 254, 0, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_OnPartsAttribute, LW(0), 1, 33554432)
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
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 0)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    CALL(evt_sub_intpl_init, 0, 0, 254, 30)
    LOOP(30)
        CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
        CALL(btlevtcmd_SetAlpha, LW(0), 1, LW(1))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetAlpha, LW(0), 1, 255)
    CALL(btlevtcmd_AnimeFlagOnOff, LW(0), 1, 1, 1)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_SetUnitWork, -2, 2, 1)
        END_IF
        ELSE
        SET_VALUE(LW(0), -2)
        CALL_CHILD(PTR(bunsin_kill_event))
        RETURN
    END_IF
    CALL_CHILD(PTR(btldefaultevt_Damage))
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(btlevtcmd_GetUnitWork, -2, 2, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(PTR(kamec_subset_bunsin_all_kill))
        END_IF
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(kamec_subset_bunsin_all_kill)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_WaitAttackEnd)
            CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
            SET_VALUE(LW(0), LW(1))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(2))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(3))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            SET_VALUE(LW(0), LW(4))
            SPAWN_EVENT(PTR(bunsin_kill_event))
            LOOP(0)
                CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_IF
    RETURN
EVT_END()

static s32 kamec_subset_dead_event[] = {
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
    16777216, 196699, (s32)btlevtcmd_OnAttribute, -29999990, 536870912, 65630, (s32)kamec_subset_bunsin_all_kill, 262235,
    (s32)btlevtcmd_CheckDamageCode, -29999990, 1024, -30000000, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_KillUnit, -29999990, 0, 32, 196699, (s32)btlevtcmd_KillUnit, -29999990, 2,
    33, 2, 1,
};

static s32 kamec_subset_blow_dead_event[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 65630, (s32)kamec_subset_bunsin_all_kill,
    196699, (s32)btlevtcmd_KillUnit, -2, 0, 2, 1,
};

static EVT_BEGIN(avoid_miss_event)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
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
    CALL(btlevtcmd_GetUnitWork, LW(0), 3, LW(1))
    IF_INT_EQUAL(LW(1), 1)
        GOTO(10)
    END_IF
    CALL(btlevtcmd_SetUnitWork, LW(0), 3, 1)
    CALL_CHILD(PTR(alpha_down_event))
    LABEL(10)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_KillUnit, LW(0), 0)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static s32 dmg_fall_event[] = {
    131122, -29999990, -2, 131122, -29999989, 1, 196699, (s32)btlevtcmd_OffAttribute,
    -2, 4, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2048, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 1, 2097152, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1,
    4194304, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 65546, 500,
    262235, (s32)btlevtcmd_AnimeSetPoseTable, -2, 1, (s32)pose_table, 262235, (s32)btlevtcmd_GetUnitWork, -2,
    1, -30000000, 131096, -30000000, 0, 196699, (s32)btlevtcmd_ChangeDataTable, -2,
    (s32)data_table, 32, 196699, (s32)btlevtcmd_ChangeDataTable, -2, (s32)data_table_bunsin, 33, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 107, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"KMR_H_1", 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 2, 16777216, 65545, 20, 327771, (s32)evt_sub_intpl_init,
    0, 255, 0, 30, 65541, 30, 196699, (s32)evt_sub_intpl_get_value_para,
    -29999999, -29999998, 262235, (s32)btlevtcmd_SetAlpha, -2, 2, -29999999, 65545,
    1, 6, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 2, 16777216, 109,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_FALL1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229998976, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, 0, -29999998, 10,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, 0, -29999998, 65546,
    500, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 65630, (s32)init_event2,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 39, 2, 1,
};

static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(9), PTR(weapon_kamec_attack_magic))
        CALL_CHILD(PTR(attack_magic_event))
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        GOTO(99)
    END_IF
    CALL(kamec_get_live_num, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        LABEL(10)
        SET_VALUE(LW(1), 40)
        ADD(LW(1), 0)
        ADD(LW(1), 40)
        SUBTRACT(LW(1), 1)
        CALL(evt_sub_random, LW(1), LW(0))
        SET_VALUE(LW(1), 40)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(weapon_kamec_attack_magic))
            CALL_CHILD(PTR(attack_magic_event))
            GOTO(99)
        END_IF
        ADD(LW(1), 0)
        IF_INT_LESS(LW(0), LW(1))
            SET_VALUE(LW(9), PTR(weapon_kamec_recover_magic))
            CALL_CHILD(PTR(recover_magic_event))
            IF_INT_EQUAL(LW(0), 0)
                GOTO(10)
            END_IF
            GOTO(99)
            ELSE
            CALL_CHILD(PTR(bunsin_magic_event))
            GOTO(99)
        END_IF
        ELSE
        CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL_CHILD(PTR(subsetevt_confuse_flustered))
                GOTO(99)
            END_IF
            SET_VALUE(LW(9), PTR(weapon_kamec_attack_magic))
            CALL_CHILD(PTR(attack_magic_event))
            GOTO(99)
            ELSE
            LABEL(20)
            SET_VALUE(LW(1), 50)
            ADD(LW(1), 20)
            ADD(LW(1), 20)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            ADD(LW(1), 0)
            CALL(evt_sub_random, LW(1), LW(0))
            SET_VALUE(LW(1), 50)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_attack_magic))
                CALL_CHILD(PTR(attack_magic_event))
                GOTO(99)
            END_IF
            ADD(LW(1), 20)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_dekadeka_magic))
                CALL_CHILD(PTR(dekadeka_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 20)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_katikati_magic))
                CALL_CHILD(PTR(katikati_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_biribiri_magic))
                CALL_CHILD(PTR(biribiri_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_trans_magic))
                CALL_CHILD(PTR(trans_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
            ADD(LW(1), 0)
            IF_INT_LESS(LW(0), LW(1))
                SET_VALUE(LW(9), PTR(weapon_kamec_recover_magic))
                CALL_CHILD(PTR(recover_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
                ELSE
                SET_VALUE(LW(9), PTR(weapon_kamec_all_recover_magic))
                CALL_CHILD(PTR(all_recover_magic_event))
                IF_INT_EQUAL(LW(0), 0)
                    GOTO(20)
                END_IF
                GOTO(99)
            END_IF
        END_IF
    END_IF
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static s32 ground_magic_common_event1[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 393307, (s32)kamec_get_bunsin,
    -29999989, -29999988, -29999987, -29999986, -30000000, 131096, -29999985, 0,
    110, 131163, (s32)eff_staff1, -2, 112, 110, 131097, -29999989,
    -1, 131163, (s32)eff_staff1, -29999989, 33, 112, 110, 131097,
    -29999988, -1, 131163, (s32)eff_staff1, -29999988, 33, 112, 110,
    131097, -29999987, -1, 131163, (s32)eff_staff1, -29999987, 33, 112,
    110, 131097, -29999986, -1, 131163, (s32)eff_staff1, -29999986, 33,
    112, 32, 110, 131163, (s32)eff_staff2, -2, 112, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_1A", 131097, -29999989, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_1A", 33, 131097, -29999988,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_1A", 33, 131097,
    -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1, (s32)"KMR_A_1A", 33,
    131097, -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_1A",
    33, 65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC4", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_1B", 131097,
    -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_1B", 33,
    131097, -29999988, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_1B",
    33, 131097, -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1,
    (s32)"KMR_A_1B", 33, 131097, -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986,
    1, (s32)"KMR_A_1B", 33, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"KMR_A_1C", 131097, -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999989,
    1, (s32)"KMR_A_1C", 33, 131097, -29999988, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999988, 1, (s32)"KMR_A_1C", 33, 131097, -29999987, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999987, 1, (s32)"KMR_A_1C", 33, 131097, -29999986, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_1C", 33, 65545, 30,
    110, 65545, 10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC8", -250000000,
    0, -250000000, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_1D",
    131097, -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_1D",
    33, 131097, -29999988, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1,
    (s32)"KMR_A_1D", 33, 131097, -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987,
    1, (s32)"KMR_A_1D", 33, 131097, -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999986, 1, (s32)"KMR_A_1D", 33, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KMR_A_1E", 131097, -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999989, 1, (s32)"KMR_A_1E", 33, 131097, -29999988, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_1E", 33, 131097, -29999987, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1, (s32)"KMR_A_1E", 33, 131097, -29999986,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_1E", 33, 2,
    1,
};

static s32 ground_magic_common_event2[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 110, 131163,
    (s32)eff_staff1, -2, 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_1A",
    65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC6", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_2A", 65545, 40,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC7", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_2B", 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"KMR_A_2C", 2, 1,
};

static s32 sky_magic_common_event[] = {
    110, 65541, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC1", -250000000,
    0, -250000000, 65545, 40, 6, 112, 393307, (s32)kamec_get_bunsin,
    -29999989, -29999988, -29999987, -29999986, -30000000, 131096, -29999985, 0,
    110, 131163, (s32)eff_staff1, -2, 112, 110, 131097, -29999989,
    -1, 131163, (s32)eff_staff1, -29999989, 33, 112, 110, 131097,
    -29999988, -1, 131163, (s32)eff_staff1, -29999988, 33, 112, 110,
    131097, -29999987, -1, 131163, (s32)eff_staff1, -29999987, 33, 112,
    110, 131097, -29999986, -1, 131163, (s32)eff_staff1, -29999986, 33,
    112, 32, 110, 131163, (s32)eff_staff2, -2, 112, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_3A", 131097, -29999989, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_3A", 33, 131097, -29999988,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_3A", 33, 131097,
    -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1, (s32)"KMR_A_3A", 33,
    131097, -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_3A",
    33, 65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC8", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_3B", 131097,
    -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_3B", 33,
    131097, -29999988, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_3B",
    33, 131097, -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1,
    (s32)"KMR_A_3B", 33, 131097, -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986,
    1, (s32)"KMR_A_3B", 33, 65545, 35, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_ENM_KAMEKU_MAGIC7", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"KMR_A_3C", 131097, -29999989, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999989, 1,
    (s32)"KMR_A_3C", 33, 131097, -29999988, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999988,
    1, (s32)"KMR_A_3C", 33, 131097, -29999987, -1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -29999987, 1, (s32)"KMR_A_3C", 33, 131097, -29999986, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_3C", 33, 65545, 15, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"KMR_A_3D", 131097, -29999989, -1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -29999989, 1, (s32)"KMR_A_3D", 33, 131097, -29999988, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -29999988, 1, (s32)"KMR_A_3D", 33, 131097, -29999987,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999987, 1, (s32)"KMR_A_3D", 33, 131097,
    -29999986, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -29999986, 1, (s32)"KMR_A_3D", 33,
    2, 1,
};

static EVT_BEGIN(magic_common_event1)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetUnitId, -2, LW(13))
        IF_INT_NOT_EQUAL(LW(3), LW(13))
            CALL_CHILD(PTR(ground_magic_common_event1))
            ELSE
            CALL_CHILD(PTR(ground_magic_common_event2))
        END_IF
        ELSE
        CALL_CHILD(PTR(sky_magic_common_event))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(magic_common_event2)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL_CHILD(PTR(ground_magic_common_event2))
        ELSE
        CALL_CHILD(PTR(sky_magic_common_event))
    END_IF
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

static s32 attack_magic_event[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 33, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken,
    -2, 16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered,
    2, 33, 65540, 99, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997,
    -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131122,
    -29999985, 0, 65630, (s32)magic_common_event1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_MAGIC3_2",
    -250000000, 0, -250000000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 458843,
    (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999991, 0, -29999995, 65570,
    -29999995, 65579, 4, 65540, 90, 46, 65572, 3,
    65540, 90, 46, 65572, 6, 65540, 90, 65572,
    2, 65540, 90, 65572, 1, 65540, 91, 46,
    42, 65540, 98, 46, 65539, 90, 110, 65545,
    1, 65541, 0, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131096,
    -30000000, -1, 196699, (s32)eff_magic_get_posX, -2, -30000000, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999994, -29999993, -29999992, 131100, -30000000, -29999994,
    65630, (s32)start_avoid, 7, 33, 32, 196699, (s32)eff_magic_get_posX, -2,
    -30000000, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999994, -29999993, -29999992,
    131101, -30000000, -29999994, 65630, (s32)start_avoid, 7, 33, 33,
    65545, 1, 6, 112, 393307, (s32)kamec_get_bunsin, -29999994, -29999993,
    -29999992, -29999987, -30000000, 131122, -29999986, -2, 65630, (s32)attack_magic_event_sub_no_hit,
    131122, -29999986, -29999994, 65630, (s32)attack_magic_event_sub_no_hit, 131122, -29999986, -29999993,
    65630, (s32)attack_magic_event_sub_no_hit, 131122, -29999986, -29999992, 65630, (s32)attack_magic_event_sub_no_hit, 131122,
    -29999986, -29999987, 65630, (s32)attack_magic_event_sub_no_hit, 65545, 60, 65540, 98,
    65539, 91, 393307, (s32)kamec_get_bunsin, -29999994, -29999993, -29999992, -29999987,
    -30000000, 131122, -29999986, -2, 65630, (s32)attack_magic_event_sub_hit, 131122, -29999986,
    -29999994, 65630, (s32)attack_magic_event_sub_hit, 131122, -29999986, -29999993, 65630, (s32)attack_magic_event_sub_hit,
    131122, -29999986, -29999992, 65630, (s32)attack_magic_event_sub_hit, 131122, -29999986, -29999987,
    65630, (s32)attack_magic_event_sub_hit, 65545, 45, 196699, (s32)btlevtcmd_ResultACDefence, -29999997, -29999991,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991, 256, -29999995,
    65540, 98, 65539, 98, 65545, 30, 393307, (s32)kamec_get_bunsin,
    -29999994, -29999993, -29999992, -29999991, -30000000, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 43, 131097, -29999994, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -29999994,
    1, 43, 33, 131097, -29999993, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -29999993, 1, 43, 33, 131097, -29999992, -1, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -29999992, 1, 43, 33, 131097, -29999991, -1,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -29999991, 1, 43, 33, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 2, 1,
};

static s32 attack_magic_event_sub_no_hit[] = {
    131096, -29999986, -1, 2, 33, 327771, (s32)btlevtcmd_GetPos, -29999986,
    -30000000, -29999999, -29999998, 131125, -29999999, 10, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -29999990, -29999989, -29999988, 262235, (s32)btlevtcmd_GetStageSize, -29999990,
    -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -29999986, -30000000, 131127, -29999990,
    -30000000, 131126, -29999989, 5, 393307, (s32)eff_magic, -29999986, -29999990,
    -29999989, -29999988, 60, 2, 1,
};

static EVT_BEGIN(attack_magic_event_sub_hit)
    IF_INT_EQUAL(LW(14), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetPos, LW(14), LW(0), LW(1), LW(2))
    ADD(LW(1), 10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(10), LW(11), LW(12))
    CALL(eff_magic, LW(14), LW(10), LW(11), LW(12), 45)
    RETURN
EVT_END()

static EVT_BEGIN(support_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    IF_INT_EQUAL(LW(15), 10)
        CALL(btlevtcmd_CheckStatus, LW(3), 10, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 14)
        CALL(btlevtcmd_CheckStatus, LW(3), 14, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 6)
        CALL(btlevtcmd_CheckStatus, LW(3), 6, LW(0))
    END_IF
    IF_INT_EQUAL(LW(15), 18)
        CALL(btlevtcmd_CheckStatus, LW(3), 18, LW(0))
    END_IF
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(PTR(magic_common_event1))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(5))
    WAIT_FRAMES(30)
    LABEL(99)
    SET_VALUE(LW(0), 1)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(dekadeka_magic_event)
    SET_VALUE(LW(15), 10)
    CALL_CHILD(PTR(support_magic_event))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(katikati_magic_event)
    SET_VALUE(LW(15), 14)
    CALL_CHILD(PTR(support_magic_event))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(biribiri_magic_event)
    SET_VALUE(LW(15), 6)
    CALL_CHILD(PTR(support_magic_event))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(trans_magic_event)
    SET_VALUE(LW(15), 18)
    CALL_CHILD(PTR(support_magic_event))
    RETURN
EVT_END()

static EVT_BEGIN(recover_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetHp, LW(3), LW(0))
    CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
    IF_INT_EQUAL(LW(0), LW(1))
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(15))
    SET_VALUE(LW(15), 0)
    CALL_CHILD(PTR(magic_common_event1))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 8)
    CALL(btlevtcmd_GetPartsPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(3), LW(5))
    CALL(btlevtcmd_GetStatusMg, LW(3), LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    ADD(LW(1), LW(5))
    CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 8, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(40)
    LABEL(99)
    SET_VALUE(LW(0), 1)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    RETURN
EVT_END()

static EVT_BEGIN(all_recover_magic_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            SET_VALUE(LW(0), 1)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(5)
    CALL(btlevtcmd_GetHp, LW(3), LW(0))
    CALL(btlevtcmd_GetMaxHp, LW(3), LW(1))
    IF_INT_LESS(LW(0), LW(1))
        GOTO(8)
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    GOTO(5)
    LABEL(8)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    CALL_CHILD(PTR(magic_common_event2))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    LABEL(10)
    BEGIN_SIBLING_EVENT
        CALL(evt_sub_random, 10, LW(0))
        WAIT_FRAMES(LW(0))
        CALL(btlevtcmd_RecoverHp, LW(3), LW(4), 4)
        CALL(btlevtcmd_GetPartsPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHeight, LW(3), LW(5))
        CALL(btlevtcmd_GetStatusMg, LW(3), LW(6))
        MULTIPLY_FLOAT(LW(5), LW(6))
        ADD(LW(1), LW(5))
        CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), 4, 0, 0, 0, 0, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        GOTO(10)
    END_IF
    SET_VALUE(LW(0), 1)
    WAIT_FRAMES(120)
    RETURN
EVT_END()

static s32 bunsin_magic_event[] = {
    131122, -29999997, -2, 131122, -29999996, 1, 131122, -29999985,
    1, 65630, (s32)magic_common_event1, 196699, (s32)evt_btl_camera_set_mode, 0, 3, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_OFFSHOOT1", -250000000, 0, -250000000, 131122, -30000000,
    -2, 65630, (s32)alpha_down_event, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 40,
    131122, -29999996, -30000000, 131099, -29999996, 0, 131126, -29999998,
    10, 589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999, -29999998, 40,
    0, 0, 0, 131096, -29999997, -1, 65630, (s32)spawn_event,
    33, 32, 7, 33, 6, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 65541, 0, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 40, 131100, -30000000, 170, 131125, -29999998, 10,
    589915, (s32)btlevtcmd_CheckSpace, -29999997, -30000000, -29999999, -29999998, 40, 0,
    0, 0, 131096, -29999997, -1, 65630, (s32)spawn_event, 33,
    32, 7, 33, 6, 65627, (s32)kamec_shuffle, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_KAMEKU_OFFSHOOT2", -250000000, 0, -250000000,
    131122, -30000000, -2, 65628, (s32)alpha_up_event, 393307, (s32)kamec_get_bunsin, -29999999,
    -29999998, -29999997, -29999996, -30000000, 131122, -30000000, -29999999, 65628,
    (s32)alpha_up_event, 131122, -30000000, -29999998, 65628, (s32)alpha_up_event, 131122, -30000000,
    -29999997, 65628, (s32)alpha_up_event, 131122, -30000000, -29999996, 65628, (s32)alpha_up_event,
    65545, 60, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 2, 1,
};

static USER_FUNC(eff_magic) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 type = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &x, &y, &z);
    // from the tip of the wand
    x += 25.0f * unit->mSizeMultiplier * unit->faceDirection;
    y += 20.0f * unit->mSizeMultiplier;
    z += 5.0f;
    eff = effMagic1N64Entry(0, type, x, y, z, a, b, c);
    unit->work[5] = (s32)eff;
    ((f32*)eff->userdata)[10] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}

static USER_FUNC(eff_staff2) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[4] = (s32)effPokopiPchargeN64Entry(0, 0.0f, -1000.0f, 0.0f, 1.0f, 60);
    }
    if (!(((EffectEntry*)unit->work[4])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[4])->userdata;
    wk[13] = unit->mSizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[1] = x + 22.5f * unit->mSizeMultiplier * unit->faceDirection;
    wk[2] = y + 40.0f * unit->mSizeMultiplier;
    wk[3] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(eff_staff1) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;
    f32* wk;

    if (isFirstCall) {
        unit->work[4] = (s32)effThunderflareN64Entry(0, 0.0f, -1000.0f, 0.0f, 1.0f, 60);
    }
    if (!(((EffectEntry*)unit->work[4])->flags & 1)) {
        return EVT_RETURN_DONE;
    }
    wk = ((EffectEntry*)unit->work[4])->userdata;
    wk[10] = unit->mSizeMultiplier;
    BtlUnit_GetPos(unit, &x, &y, &z);
    wk[2] = x + 22.5f * unit->mSizeMultiplier * unit->faceDirection;
    wk[3] = y + 40.0f * unit->mSizeMultiplier;
    wk[4] = 5.0f + z;
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(kamec_copy_status) {
    s32* args = event->args;
    s32 id1 = evtGetValue(event, args[0]);
    s32 id2 = evtGetValue(event, args[1]);
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit1 = BattleGetUnitPtr(wp, id1);
    BattleUnit* unit2 = BattleGetUnitPtr(wp, id2);

    // the copy shares the real magikoopa's hp and status
    unit2->currentHp = unit1->currentHp;
    memcpy((u8*)unit2 + 0x118, (u8*)unit1 + 0x118, 0x1E);
    unit2->hpGauge.field_0xC = unit2->currentHp;
    unit2->hpGauge.field_0x10 = unit2->currentHp;
    unit2->hpGauge.field_0x14 = unit2->hpGauge.field_0x18 = (f32)unit2->currentHp / unit2->maxHp;
    return EVT_RETURN_DONE;
}

static USER_FUNC(kamec_shuffle) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* kamecs[6];
    s32 n = 0;
    s32 i;

    // the real magikoopa and its copies
    for (i = 0; i < 64; i++) {
        kamecs[n] = wp->units[i];
        if (kamecs[n] != NULL && (kamecs[n]->currentKind == 0x31 || kamecs[n]->currentKind == 0x32)) {
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

static USER_FUNC(kamec_get_bunsin) {
    s32* args = event->args;
    s32 copies[4];
    s32 n = 0;
    s32 i;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // indices of the magikoopa's copies
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && unit->currentKind == 0x32) {
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

static USER_FUNC(kamec_get_live_num) {
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

static EVT_BEGIN(spawn_event)
    CALL(btlevtcmd_SpawnUnit, LW(3), PTR(entry_kamec), 0)
    CALL(btlevtcmd_SetAlpha, LW(3), 1, 0)
    CALL(btlevtcmd_GetUnitWork, -2, 0, LW(10))
    CALL(btlevtcmd_SetUnitWork, LW(3), 0, LW(10))
    WAIT_FRAMES(2)
    CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetHomePos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetUnitId, -2, LW(13))
    CALL(kamec_copy_status, LW(13), LW(3))
    CALL(btlevtcmd_OffAttribute, LW(3), 33554432)
    CALL(btlevtcmd_SetUnitWork, LW(3), 1, 1)
    CALL(btlevtcmd_SetEventAttack, LW(3), PTR(attack_event))
    CALL(btlevtcmd_SetRegistStatus, LW(3), PTR(regist_bunsin))
    CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, 16384)
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(kamec_get_bunsin, LW(1), LW(2), LW(3), LW(4), LW(0))
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
    RETURN
EVT_END()

