#include "version.h"
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "battle/battle_database_common.h"
#include "data/item_data.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/icondrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/mtx.h>
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_audience.h"
#include "evt/evt_mobj.h"

extern ItemData itemDataTable[];
void BattleSamplingEnemy(BattleWorkWeaponTargets* targets, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags, s8 direction);
void BattleStatusWindowSystemOn(void);
void N_statusClearBlink(void);
void statusMarioHPBlink(s32 frames);
void statusPartyHPBlink(s32 frames);
void statusFPBlink(s32 frames);
EffectEntry* effNanigaEntry(s32 type, s32* table, s32 item, f32 x, f32 y, f32 z);
void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
void _nancy_disp(CameraId cameraId, void* param);
void _disp_item_icon(CameraId cameraId, void* param);
extern s32 R_mystery_item_table[];

USER_FUNC(_cam_rot);
USER_FUNC(_full_ap_recover);
USER_FUNC(_get_throw_first_pos);
USER_FUNC(_nancy_mirage);
USER_FUNC(_naniga_okorukana_check);
USER_FUNC(_throw_item_icon);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_CheckCommandUnit);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckWeaponPluralTarget);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_CommandFlyItem);
USER_FUNC(btlevtcmd_CommandGetWeaponAddress);
USER_FUNC(btlevtcmd_CommandGetWeaponItemId);
USER_FUNC(btlevtcmd_ConsumeItem);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetConsumeItem);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetFaceDirection);
USER_FUNC(btlevtcmd_GetFriendBelong);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetHomePos);
USER_FUNC(btlevtcmd_GetItemRecoverParam);
USER_FUNC(btlevtcmd_GetPartsPos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetSelectEnemy);
USER_FUNC(btlevtcmd_GetSelectNextEnemy);
USER_FUNC(btlevtcmd_GetStatusMg);
USER_FUNC(btlevtcmd_GetUnitKind);
USER_FUNC(btlevtcmd_GetWidth);
USER_FUNC(btlevtcmd_MovePosition);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_RecoverFp);
USER_FUNC(btlevtcmd_RecoverHp);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetFp);
USER_FUNC(btlevtcmd_SetHp);
USER_FUNC(btlevtcmd_SetMoveSpeed);
USER_FUNC(btlevtcmd_StageDispellFog);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StatusWindowOnOff);
USER_FUNC(btlevtcmd_TransStageFloorPosition);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_audience_ap_recovery);
USER_FUNC(evt_btl_camera_noshake);
USER_FUNC(evt_btl_camera_set_homing_unit);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_btl_camera_shake_h);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff64);
USER_FUNC(evt_env_blur_on);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_random);
USER_FUNC(evt_sub_rumble_onoff);
USER_FUNC(_hpfp_change_declare_2);
USER_FUNC(_hpfp_change_declare_1);
USER_FUNC(_rank_up);
USER_FUNC(_sampling_random_target);

s32 _return_home_event[44];
s32 ItemEvent_Automatic_Target[38];
s32 ItemEvent_Recovery_Core_Effect[125];
s32 ItemEvent_Recovery_Core[22];
s32 ItemEvent_Recovery[125];
s32 ItemEvent_Support_Sub_UseDeclere[86];
s32 ItemEvent_GetTarget[68];
s32 ItemEvent_Support_Sub_Effect[71];
s32 ItemEvent_Support_NoEffect[20];
s32 ItemEvent_Support_RefreshEffect[101];
s32 ItemWeaponData_CookingItem[48];
s32 ItemWeaponData_Kinoko[48];
s32 ItemWeaponData_Kinkyuu_Kinoko[48];
s32 ItemWeaponData_Super_Kinoko[48];
s32 ItemWeaponData_Ultra_Kinoko[48];
s32 ItemWeaponData_Sinabita_Kinoko[48];
s32 ItemWeaponData_Honey_Syrup[48];
s32 ItemWeaponData_Maple_Syrup[48];
s32 ItemWeaponData_Royal_Jelly[48];
s32 ItemWeaponData_Tankobu[48];
s32 ItemEvent_Pow_Block[418];
s32 ItemWeaponData_Pow_Block[48];
s32 ItemEvent_Fire_Flower_Core[192];
s32 ItemEvent_Fire_Flower[31];
s32 ItemWeaponData_Fire_Flower[48];
s32 ItemEvent_Kaminari_Core[220];
s32 ItemEvent_Kaminari[83];
s32 ItemWeaponData_Kaminari_Dokkan[48];
s32 ItemWeaponData_Kaminari_Gorogoro[48];
s32 ItemEvent_Kirakira_Otoshi_Core[451];
s32 ItemEvent_Kirakira_Otoshi[29];
s32 ItemWeaponData_Kirakira_Otoshi[48];
s32 ItemEvent_Koorino_Ibuki[310];
s32 ItemWeaponData_Koorino_Ibuki[48];
s32 ItemEvent_Yurayura_Jishin[342];
s32 ItemWeaponData_Yurayura_Jishin[48];
s32 ItemEvent_Teresano_Fuku[236];
s32 ItemWeaponData_Teresano_Fuku[48];
s32 ItemEvent_Biribiri_Kinoko_Core[13];
s32 ItemEvent_Biribiri_Kinoko[14];
s32 ItemWeaponData_Biribiri_Kinoko[48];
s32 ItemEvent_Teki_Yokeeru_Core[13];
s32 ItemEvent_Teki_Yokeeru[14];
s32 ItemWeaponData_Teki_Yokeeru[48];
s32 ItemWeaponData_Madowaseno_Kona[48];
s32 ItemEvent_Nemure_Yoikoyo[VERSION_PICK(57, 91)];
s32 ItemWeaponData_Nemure_Yoikoyo[48];
s32 ItemEvent_Stop_Watch_Core[143];
s32 ItemEvent_Stop_Watch[86];
s32 ItemWeaponData_Stop_Watch[48];
s32 ItemEvent_Guruguru_Memawashi[35];
s32 ItemWeaponData_Guruguru_Memawashi[48];
s32 ItemWeaponData_Dekadeka_Drink[48];
s32 ItemWeaponData_Katikati_Koura[48];
s32 ItemEvent_Suitooru[281];
s32 ItemWeaponData_Suitooru[48];
s32 ItemEvent_Teki_Kyouka[236];
s32 ItemWeaponData_Teki_Kyouka[48];
s32 ItemWeaponData_Minimini_Kun[48];
s32 ItemWeaponData_Funyafunya_Kun[48];
s32 ItemWeaponData_Sukkiri_Drink[48];
s32 ItemEvent_Jiwajiwa_Kinoko_Core[13];
s32 ItemEvent_Jiwajiwa_Kinoko[14];
s32 ItemWeaponData_Jiwajiwa_Kinoko[48];
s32 ItemEvent_Jiwajiwa_Syrup_Core[13];
s32 ItemEvent_Jiwajiwa_Syrup[14];
s32 ItemWeaponData_Jiwajiwa_Syrup[48];
s32 ItemEvent_Irekaeeru[157];
s32 ItemWeaponData_Irekaeeru[48];
s32 ItemEvent_Attiike_Shisshi[167];
s32 ItemWeaponData_Attiike_Shisshi[48];
s32 ItemEvent_Naniga_Okorukana[207];
s32 ItemWeaponData_Naniga_Okorukana[48];
s32 R_mystery_item_table[14];
s32 ItemWeaponData_Shikaeshino_Kona[48];
s32 ItemWeaponData_Kameno_Noroi[48];
s32 ItemEvent_RecoveryAndStatus[246];
s32 ItemWeaponData_SpaceFood[48];
s32 ItemWeaponData_IceCandy[48];
s32 ItemWeaponData_NancyFrappe[48];
s32 ItemWeaponData_SnowRabbit[48];
s32 ItemWeaponData_TeaKinoko[48];
s32 ItemWeaponData_FirstLovePuddingBiribiri[48];
s32 ItemWeaponData_FirstLovePuddingTrans[48];
s32 ItemWeaponData_FirstLovePuddingSleep[48];
s32 ItemWeaponData_StarryDinner[48];
s32 ItemWeaponData_KararinaPasta[48];
s32 ItemWeaponData_MeromeroCake[48];
s32 ItemWeaponData_PeachTaltBiribiri[48];
s32 ItemWeaponData_PeachTaltDodge[48];
s32 ItemWeaponData_PeachTaltSleep[48];
s32 ItemWeaponData_BiribiriCandy[48];
s32 ItemWeaponData_HealthySalad[48];
s32 ItemWeaponData_FreshJuice[48];
s32 ItemWeaponData_RedKararing[48];
s32 ItemWeaponData_FutarideForever[48];
s32 ItemEvent_ThrowAttack[432];
s32 ItemWeaponData_NancyDynamite[48];
s32 ItemWeaponData_CoconutsBomb[48];
s32 ItemWeaponData_KachikachiDish[48];
s32 ItemWeaponData_BomberEgg[48];
s32 ItemEvent_Poison_Kinoko[86];
s32 ItemWeaponData_PoisonKinoko[48];
s32 ItemEvent_LastDinner[228];
s32 ItemWeaponData_LastDinner[48];
s32 ItemEvent_Kaminari_Dokkan[7];
s32 ItemEvent_Kaminari_Gorogoro[7];
s32 ItemEvent_Madowaseno_Kona[7];
s32 ItemEvent_Dekadeka_Drink[7];
s32 ItemEvent_Katikati_Koura[7];
s32 ItemEvent_Minimini_Kun[7];
s32 ItemEvent_Funyafunya_Kun[7];
s32 ItemEvent_Sukkiri_Drink[7];
s32 ItemEvent_Shikaeshino_Kona[7];
s32 ItemEvent_Kameno_Noroi[7];



EVT_BEGIN(_return_home_event)
    CALL(btlevtcmd_GetHomePos, -2, LW(0), LW(1), LW(2))
    LABEL(95)
    CALL(btlevtcmd_GetPos, -2, LW(3), LW(4), LW(5))
    IF_INT_NOT_EQUAL(LW(0), LW(3))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_GetBodyId, -2, LW(0))
            CALL(btlevtcmd_AnimeChangePoseType, -2, LW(0), 42)
        END_SIBLING_EVENT
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(5.0f))
        CALL(btlevtcmd_MovePosition, -2, LW(0), LW(1), LW(2), 0, -1, 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Automatic_Target)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(8))
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Recovery_Core_Effect)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(10), -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_GetItemRecoverParam, LW(9), LW(5), LW(6), LW(7))
    IF_INT_GREATER_OR_EQUAL(LW(5), 1)
        CALL(btlevtcmd_GetPartsPos, LW(10), LW(11), LW(12), LW(13), LW(14))
        CALL(btlevtcmd_GetStatusMg, LW(10), LW(0))
        CALL(btlevtcmd_GetHeight, LW(10), LW(1))
        MULTIPLY_FLOAT(LW(0), LW(1))
        ADD(LW(13), LW(0))
        CALL(evt_eff, 0, STRING("recovery"), 0, LW(12), LW(13), LW(14), LW(5), 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(120)
        CALL(btlevtcmd_RecoverHp, LW(10), LW(11), LW(5))
        WAIT_FRAMES(60)
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(6), 1)
        CALL(btlevtcmd_GetPartsPos, LW(10), LW(11), LW(12), LW(13), LW(14))
        CALL(btlevtcmd_GetStatusMg, LW(10), LW(0))
        CALL(btlevtcmd_GetHeight, LW(10), LW(1))
        MULTIPLY_FLOAT(LW(0), LW(1))
        ADD(LW(13), LW(0))
        CALL(evt_eff, 0, STRING("recovery"), 1, LW(12), LW(13), LW(14), LW(6), 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(120)
        CALL(btlevtcmd_RecoverFp, LW(10), LW(11), LW(6))
        WAIT_FRAMES(60)
    END_IF
    IF_INT_GREATER_OR_EQUAL(LW(7), 1)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Recovery_Core)
    CALL_CHILD(PTR(ItemEvent_Recovery_Core_Effect))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(60)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Recovery)
    CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(8))
    CALL(btlevtcmd_WeaponAftereffect, LW(8))
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 60)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(8))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL_CHILD(PTR(ItemEvent_Recovery_Core))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Support_Sub_UseDeclere)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(600)
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_GetTarget)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Support_Sub_Effect)
    CALL_CHILD(PTR(ItemEvent_GetTarget))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Support_NoEffect)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Support_RefreshEffect)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_GetTarget))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_REST_CONDITION1"), LW(0), LW(1), LW(2), 0)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_CookingItem[] = {
    0, 0, 0, 0, 1677721600, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196616, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Kinoko[] = {
    0, 0, 148, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Kinkyuu_Kinoko[] = {
    0, 0, 151, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Super_Kinoko[] = {
    0, 0, 149, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Ultra_Kinoko[] = {
    0, 0, 150, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Sinabita_Kinoko[] = {
    0, 0, 152, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Honey_Syrup[] = {
    0, 0, 154, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, -2147483646,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Maple_Syrup[] = {
    0, 0, 155, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, -2147483646,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Royal_Jelly[] = {
    0, 0, 156, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, -2147483646,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemWeaponData_Tankobu[] = {
    0, 0, 165, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196936, 2047, -2147483646,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Recovery, 100, 0, 0,
};

s32 ItemEvent_Pow_Block[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 65546, 1000, 196699, (s32)btlevtcmd_GetFriendBelong, -2, -30000000, 131096,
    -30000000, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_GetBodyId, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 524379, (s32)btlevtcmd_MovePosition, -2,
    -60, -29999999, -29999998, 0, -1, 0, 33, 196699,
    (s32)btlevtcmd_GetBodyId, -2, -29999991, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 52,
    196699, (s32)btlevtcmd_CommandFlyItem, -2, 40, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991,
    69, 131163, (s32)btlevtcmd_ConsumeItem, -2, 196699, (s32)btlevtcmd_CheckCommandUnit, -2, -30000000,
    131097, -30000000, 0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_GetHeight, -2, -29999995, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2,
    -30000000, 30, 131125, -29999999, 16, 131125, -29999999, -29999995,
    32, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_GetHeight, -2, -29999995, 131125, -29999999, 16, 131125, -29999999,
    -29999995, 33, 110, 65546, 100, 196699, (s32)evt_mobj_entry, (s32)"_BtCIPw",
    (s32)"MOBJ_PowerBlock", 327771, (s32)evt_mobj_set_position, (s32)"_BtCIPw", -30000000, -29999999, -29999998, 393307,
    (s32)evt_snd_sfxon_3d, (s32)"SFX_ITEM_POW_APPEAR1", -30000000, -29999999, -29999998, 0, 112, 131125,
    -29999999, 10, 131125, -29999998, 25, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 2, -30000000, -29999999, -29999998, -229998976, 0, 0,
    0, 0, 0, 0, 0, 107, 65546, 2050,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 2, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    109, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 69, 65545, 5,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65545, 30, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 42, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 43, 65545,
    30, 110, 327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999181,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 44, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 14, -1, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 43,
    65545, 60, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 42, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 43, 112,
    107, 65545, 5, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_MOBJ_POW_BLOCK1", -30000000, -29999999, -29999998, 0,
    196699, (s32)evt_mobj_set_anim, (s32)"_BtCIPw", (s32)"A_1", 65545, 3, 393307, (s32)evt_btl_camera_shake_h,
    0, 8, 0, 10, 13, 65545, 50, 131163,
    (s32)evt_mobj_delete, (s32)"_BtCIPw", 109, 131163, (s32)evt_audience_reflesh_natural_all, 100, 65545, 7,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    (s32)ItemWeaponData_Pow_Block, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 65539, 10, 131096,
    -29999990, -1, 65540, 90, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -2,
    -29999990, -29999989, (s32)ItemWeaponData_Pow_Block, 256, -29999995, 65570, -29999995, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999990, 38, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999990, 39, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999990,
    40, 65572, 1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999990, -29999989,
    (s32)ItemWeaponData_Pow_Block, 256, -29999995, 49, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999990, -29999989,
    65540, 10, 65539, 90, 65627, (s32)evt_audience_ap_recovery, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)ItemWeaponData_Pow_Block, 65545, 150, 65630, (s32)_return_home_event, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 ItemWeaponData_Pow_Block[] = {
    0, 0, 139, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 208960, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Pow_Block, 6579300, 1258947845, 84213760,
};

EVT_BEGIN(ItemEvent_Fire_Flower_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_MS(100)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(0), 40)
    SET_VALUE(LW(3), LW(0))
    SET_VALUE(LW(4), LW(1))
    SET_VALUE(LW(5), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, -2, LW(3), 240)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_eff64, STRING(""), STRING("fireflower_n64"), 0, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(45)
            LOOP(36)
                CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_FIRE_FLOWER1"), LW(0), LW(1), LW(2), 0)
                WAIT_FRAMES(5)
            END_LOOP
        END_SIBLING_EVENT
        ELSE
        CALL(evt_eff64, STRING(""), STRING("fireflower_n64"), 1, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
        BEGIN_SIBLING_EVENT
            WAIT_FRAMES(45)
            LOOP(36)
                CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_FIRE_FLOWER1"), LW(0), LW(1), LW(2), 0)
                WAIT_FRAMES(5)
            END_LOOP
        END_SIBLING_EVENT
    END_IF
    WAIT_MS(2800)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), PTR(ItemWeaponData_Fire_Flower))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), PTR(ItemWeaponData_Fire_Flower), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), PTR(ItemWeaponData_Fire_Flower), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    WAIT_MS(80)
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Fire_Flower)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Fire_Flower))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Fire_Flower_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Fire_Flower[] = {
    0, 0, 132, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 16777986, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Fire_Flower, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Kaminari_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(evt_sub_random, 2, LW(4))
    ADD(LW(4), 3)
    CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetWidth, LW(10), LW(5))
    CALL(btlevtcmd_GetHeight, LW(10), LW(6))
    CALL(evt_eff64, STRING(""), STRING("thunder_n64"), LW(4), LW(0), LW(1), LW(2), LW(5), LW(6), 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_ICE_THUNDER_FALL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_btl_camera_shake_h, 0, 3, 0, 25, 13)
    CALL(evt_sub_rumble_onoff, 0, 0)
    WAIT_MS(83)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    WAIT_MS(167)
    CALL(evt_sub_rumble_onoff, 1, 0)
    WAIT_MS(167)
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Kaminari)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL_CHILD(PTR(ItemEvent_Kaminari_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Kaminari_Dokkan[] = {
    0, 0, 129, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 67109634, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Kaminari_Dokkan, 100, 328965, 83886080,
};

s32 ItemWeaponData_Kaminari_Gorogoro[] = {
    0, 0, 128, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 67109634, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Kaminari_Gorogoro, 100, 328965, 83886080,
};

s32 ItemEvent_Kirakira_Otoshi_Core[] = {
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65545, 30, 196699, (s32)btlevtcmd_CheckCommandUnit, -2, -30000000, 131097, -30000000,
    0, 131122, -29999985, 0, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988, -30000000,
    131097, -30000000, 0, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235,
    (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 131122, -29999985, 1, 33,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 32, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988,
    -30000000, 131097, -30000000, 0, 131122, -29999985, 1, 196699,
    (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 32, 131122, -29999985, 0,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999990, -29999989, 33, 33,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_ITEM_KIRAKIRA_FALL1", 0, 131096, -29999985, 0, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -250000000,
    -29999999, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999990, -29999989, -29999997, -29999996,
    -29999995, 983131, (s32)evt_eff64, (s32)"", (s32)"sstar_n64", 2, -30000000, -29999999,
    -29999998, -29999997, -29999996, -29999995, -229989760, 0, 0, 0,
    0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_ITEM_KIRAKIRA_FALL1", -30000000, -29999999, -29999998, 0,
    65545, 50, 32, 110, 65546, 500, 65541, 5,
    393307, (s32)evt_btl_camera_shake_h, 0, 5, 0, 20, 12, 65546,
    400, 65546, 200, 6, 112, 65647, -29999985, 65541,
    5, 196699, (s32)evt_sub_random, 6, -30000000, 131125, -30000000, 27,
    65545, -30000000, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 327771, (s32)_sampling_random_target,
    -29999988, -29999990, -29999989, -30000000, 131097, -29999990, -1, 393307,
    (s32)btlevtcmd_GetHitPos, -29999990, -29999989, -30000000, -29999999, -29999998, 983131, (s32)evt_eff,
    0, (s32)"hit", 0, -30000000, -29999999, -29999998, -229998976, 3,
    0, 0, 0, 0, 0, 0, 33, 6,
    112, 110, 65541, 7, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_ITEM_KIRAKIRA_FALL1", -30000000,
    -29999999, -29999998, 0, 65546, 500, 6, 112, 65541,
    60, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_GetStageSize, -250000000, -29999999, -250000000, 196699, (s32)evt_sub_random, 200, -30000000,
    196699, (s32)evt_sub_random, 320, -29999997, 196699, (s32)btlevtcmd_GetFriendBelong, -29999990, -29999994,
    131096, -29999994, 0, 131127, -29999997, -1, 131122, -29999996,
    0, 32, 131127, -30000000, -1, 131122, -29999996, 0,
    33, 196699, (s32)btlevtcmd_check_battleflag, -29999992, 256, 131096, -29999992, 0,
    131122, -29999998, 0, 131122, -29999995, 0, 32, 131122,
    -29999998, 200, 131122, -29999995, 200, 33, 196699, (s32)evt_sub_random,
    120, -29999992, 131126, -29999992, 60, 131125, -29999995, -29999992,
    196699, (s32)evt_sub_random, 120, -29999992, 131126, -29999992, 60, 131125,
    -29999998, -29999992, 262235, (s32)btlevtcmd_TransStageFloorPosition, -29999997, -29999996, -29999995, 983131,
    (s32)evt_eff64, (s32)"", (s32)"sstar_n64", 2, -30000000, -29999999, -29999998, -29999997,
    -29999996, -29999995, -229991808, 0, 0, 0, 0, 65545,
    3, 6, 65545, 50, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 196699,
    (s32)btlevtcmd_CheckCommandUnit, -2, -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 196699,
    (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 32, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999990,
    -29999989, 33, 33, 65539, 10, 131096, -29999990, -1,
    65540, 90, 33, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999990, -29999989,
    -29999988, 256, -29999995, 65570, -29999995, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999990, 38, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999990,
    39, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999990, 40, 65572,
    1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999990, -29999989, -29999988, 256,
    -29999995, 49, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988, -30000000, 131097, -30000000,
    0, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999990, -29999989, 32, 131122, -29999990,
    -1, 33, 65546, 80, 65540, 10, 65539, 90,
    65627, (s32)evt_audience_ap_recovery, 65545, 150, 65630, (s32)_return_home_event, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

EVT_BEGIN(ItemEvent_Kirakira_Otoshi)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Kirakira_Otoshi))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    CALL_CHILD(PTR(ItemEvent_Kirakira_Otoshi_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Kirakira_Otoshi[] = {
    0, 0, 130, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Kirakira_Otoshi, 658020, 167772160, 0,
};

EVT_BEGIN(ItemEvent_Koorino_Ibuki)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Koorino_Ibuki))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_ICE_WIND1"), LW(0), LW(1), LW(2), LW(15))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, -2, LW(5))
    ADD(LW(1), 10)
    ADD(LW(2), 20)
    IF_INT_GREATER_OR_EQUAL(LW(5), 0)
        CALL(evt_eff, 0, STRING("ibuki"), 0, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(evt_eff, 0, STRING("ibuki"), 1, LW(0), LW(1), LW(2), 180, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_MS(500)
    CALL(btlevtcmd_StageDispellFog)
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, LW(15))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Koorino_Ibuki[] = {
    0, 0, 131, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 33555202, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 6226432, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Koorino_Ibuki, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Yurayura_Jishin)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Yurayura_Jishin))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    BEGIN_SIBLING_EVENT
        CALL(evt_eff64, 0, STRING("hokori_n64"), 0, 0, 300, 0, 150, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(600)
        CALL(evt_eff64, 0, STRING("hokori_n64"), 0, 0, 300, 0, 60, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(600)
        CALL(evt_eff64, 0, STRING("hokori_n64"), 0, 0, 300, 0, 60, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(600)
        CALL(evt_eff64, 0, STRING("hokori_n64"), 0, 0, 300, 0, 60, 0, 0, 0, 0, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_QUAKE1"), LW(10))
    CALL(evt_btl_camera_shake_h, 0, 0, 5, 90, 0)
    WAIT_MS(1500)
    CALL(evt_btl_camera_shake_h, 0, 5, 5, 40, 0)
    WAIT_MS(667)
    CALL(evt_btl_camera_shake_h, 0, 5, 0, 30, 13)
    WAIT_MS(333)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Yurayura_Jishin[] = {
    0, 0, 133, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870920, 770, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Yurayura_Jishin, 6579300, 1258947845, 84213760,
};

EVT_BEGIN(ItemEvent_Teresano_Fuku)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Teresano_Fuku))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Teresano_Fuku[] = {
    0, 0, 134, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677852672, 0, (s32)ItemEvent_Teresano_Fuku, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Biribiri_Kinoko_Core)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Biribiri_Kinoko)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Biribiri_Kinoko))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Biribiri_Kinoko_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Biribiri_Kinoko[] = {
    0, 0, 135, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 100, 83886080, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Biribiri_Kinoko, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Teki_Yokeeru_Core)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Teki_Yokeeru)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Teki_Yokeeru))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Teki_Yokeeru_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Teki_Yokeeru[] = {
    0, 0, 136, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 6554624, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Teki_Yokeeru, 100, 0, 0,
};

s32 ItemWeaponData_Madowaseno_Kona[] = {
    0, 0, 137, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    0, 0, 6554368, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Madowaseno_Kona, 100, 0, 0,
};

#ifdef VERSION_G8ME01
EVT_BEGIN(ItemEvent_Nemure_Yoikoyo)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Nemure_Yoikoyo))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_shake_h, 0, 1, 0, 10000, 0)
    CALL(btlevtcmd_check_battleflag, LW(0), 256)
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), 0, 0, 0, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        ADD(LW(2), 15)
        CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_FRAMES(300)
    CALL(evt_btl_camera_noshake, 0)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#else
EVT_BEGIN(ItemEvent_Nemure_Yoikoyo)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Nemure_Yoikoyo))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_shake_h, 0, 1, 0, 10000, 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(300)
    CALL(evt_btl_camera_noshake, 0)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()
#endif

s32 ItemWeaponData_Nemure_Yoikoyo[] = {
    0, 0, 138, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    1594163200, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Nemure_Yoikoyo, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Stop_Watch_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_STOP_WATCH1"), 0)
    CALL(btlevtcmd_check_battleflag, LW(0), 256)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_eff64, 0, STRING("timestamp_n64"), 0, 0, 0, 103, FLOAT(1.0f), 200, 0, 0, 0, 0, 0, 0)
        ELSE
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        ADD(LW(2), 30)
        CALL(evt_eff64, 0, STRING("timestamp_n64"), 0, 0, 0, LW(2), FLOAT(1.0f), 200, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_FRAMES(200)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Stop_Watch)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Stop_Watch))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL_CHILD(PTR(ItemEvent_Stop_Watch_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Stop_Watch[] = {
    0, 0, 140, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    24323, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Stop_Watch, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Guruguru_Memawashi)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Guruguru_Memawashi))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_GURUGURU1"), 0)
    BEGIN_SIBLING_EVENT
        CALL(evt_env_blur_on, 0, 2000)
    END_SIBLING_EVENT
    CALL(_cam_rot)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Guruguru_Memawashi[] = {
    0, 0, 141, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    0, 1677918208, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Guruguru_Memawashi, 100, 0, 0,
};

s32 ItemWeaponData_Dekadeka_Drink[] = {
    0, 0, 142, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 100, 50462720, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Dekadeka_Drink, 100, 0, 0,
};

s32 ItemWeaponData_Katikati_Koura[] = {
    0, 0, 143, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554371, 0,
    0, 0, 0, 0, (s32)ItemEvent_Katikati_Koura, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Suitooru)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Suitooru))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_RecoverHp, -2, LW(9), LW(0))
        CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
        CALL(btlevtcmd_GetHeight, -2, LW(8))
        ADD(LW(6), LW(8))
        ADD(LW(7), 3)
        CALL(evt_eff, 0, STRING("recovery"), 0, LW(5), LW(6), LW(7), LW(0), 0, 0, 0, 0, 0, 0, 0)
    END_IF
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(60)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Suitooru[] = {
    0, 0, 144, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 196928, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Suitooru, 100, 0, 0,
};

s32 ItemEvent_Teki_Kyouka[] = {
    131122, -29999988, (s32)ItemWeaponData_Teki_Kyouka, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235,
    (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 200, 65546, 1000, 196699, (s32)btlevtcmd_GetFriendBelong,
    -2, -30000000, 131096, -30000000, 0, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_GetBodyId, -2, -29999991, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928,
    524379, (s32)btlevtcmd_MovePosition, -2, -60, -29999999, -29999998, 0, -1,
    0, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 196699, (s32)btlevtcmd_GetBodyId, -2,
    -29999991, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 52, 196699, (s32)btlevtcmd_CommandFlyItem,
    -2, 40, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -29999991, 69, 131163,
    (s32)btlevtcmd_ConsumeItem, -2, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 65545, 30, 196699, (s32)btlevtcmd_CheckCommandUnit, -2, -30000000,
    131097, -30000000, 0, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988, -30000000, 131097,
    -30000000, 0, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy,
    -2, -30000000, -29999988, 33, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989,
    32, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988, -30000000, 131097, -30000000, 0,
    196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000,
    -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999990, -29999989, 32, 196699, (s32)btlevtcmd_GetEnemyBelong,
    -2, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999988, 262235,
    (s32)btlevtcmd_ChoiceSamplingEnemy, -29999988, -29999990, -29999989, 33, 33, 65539, 10,
    131096, -29999990, -1, 65540, 90, 33, 393307, (s32)btlevtcmd_snd_se,
    -29999990, (s32)"SFX_ITEM_RANK_UP_ENEMY1", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_GetHitPos, -29999990,
    -29999989, -30000000, -29999999, -29999998, 131125, -29999999, 20, 131125,
    -29999998, 5, 983131, (s32)evt_eff, (s32)"", (s32)"rankup", 0, -30000000,
    -29999999, -29999998, 0, 0, 0, 0, 0, 0,
    0, 0, 131163, (s32)_rank_up, -29999990, 196699, (s32)btlevtcmd_CheckWeaponPluralTarget, -29999988,
    -30000000, 131097, -30000000, 0, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999990, -29999989,
    32, 131122, -29999990, -1, 33, 65540, 10, 65539,
    90, 65627, (s32)evt_audience_ap_recovery, 65545, 150, 65630, (s32)_return_home_event, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 ItemWeaponData_Teki_Kyouka[] = {
    0, 0, 145, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Teki_Kyouka, 100, 0, 0,
};

s32 ItemWeaponData_Minimini_Kun[] = {
    0, 0, 146, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    0, 0, 0, 0, 100, 66977792, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Minimini_Kun, 100, 0, 0,
};

s32 ItemWeaponData_Funyafunya_Kun[] = {
    0, 0, 147, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554621, 0,
    0, 0, 0, 0, (s32)ItemEvent_Funyafunya_Kun, 100, 0, 0,
};

s32 ItemWeaponData_Sukkiri_Drink[] = {
    0, 0, 153, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    1677747200, 1677747200, 6553600, 100, 6553700, 0, 6553600, 1677721600,
    25600, 0, 0, 0, (s32)ItemEvent_Sukkiri_Drink, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Jiwajiwa_Kinoko_Core)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Jiwajiwa_Kinoko)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Jiwajiwa_Kinoko))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Jiwajiwa_Kinoko_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Jiwajiwa_Kinoko[] = {
    0, 0, 157, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, 4368,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2562, 0, (s32)ItemEvent_Jiwajiwa_Kinoko, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Jiwajiwa_Syrup_Core)
    CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Jiwajiwa_Syrup)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Jiwajiwa_Syrup))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(ItemEvent_Jiwajiwa_Syrup_Core))
    RETURN
EVT_END()

s32 ItemWeaponData_Jiwajiwa_Syrup[] = {
    0, 0, 158, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 167903232, (s32)ItemEvent_Jiwajiwa_Syrup, 100, 0, 0,
};

s32 ItemEvent_Irekaeeru[] = {
    131122, -29999988, (s32)ItemWeaponData_Irekaeeru, 65630, (s32)ItemEvent_GetTarget, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988,
    65630, (s32)ItemEvent_Support_Sub_UseDeclere, 65545, 30, 131163, (s32)_hpfp_change_declare_1, -29999990, 393307,
    (s32)btlevtcmd_GetHitPos, -29999990, -29999989, -30000000, -29999999, -29999998, 131125, -29999999,
    20, 131125, -29999998, 5, 983131, (s32)evt_eff, (s32)"", (s32)"irekae",
    0, -30000000, -29999999, -29999998, 0, 0, 0, 0,
    0, 0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_ITEM_HP_FP_CHANGE1",
    -250000000, 0, -250000000, 65545, 120, 262235, (s32)btlevtcmd_CheckAttribute, -29999990,
    1048576, -30000000, 131096, -30000000, 0, 196699, (s32)btlevtcmd_GetMaxHp, -29999990,
    -29999995, 196699, (s32)btlevtcmd_GetHp, -29999990, -29999994, 196699, (s32)btlevtcmd_GetMaxFp, -29999990,
    -29999993, 196699, (s32)btlevtcmd_GetFp, -29999990, -29999992, 131099, -29999992, -29999995,
    131122, -29999992, -29999995, 33, 196699, (s32)btlevtcmd_SetHp, -29999990, -29999992,
    131099, -29999994, -29999993, 131122, -29999994, -29999993, 33, 196699,
    (s32)btlevtcmd_SetFp, -29999990, -29999994, 131163, (s32)_hpfp_change_declare_2, -29999990, 131096, -29999992,
    0, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999990, -29999989, -29999988, 256,
    -29999995, 65570, -29999995, 65572, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999990,
    38, 65572, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999990, 39, 65572,
    2, 196699, (s32)btlevtcmd_StartAvoid, -29999990, 40, 65572, 1, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999990, -29999989, -29999988, 256, -29999995, 49,
    33, 33, 65627, (s32)evt_audience_ap_recovery, 65545, 30, 65630, (s32)_return_home_event,
    131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 ItemWeaponData_Irekaeeru[] = {
    0, 0, 161, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 1770242, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Irekaeeru, 100, 0, 0,
};

s32 ItemEvent_Attiike_Shisshi[] = {
    131122, -29999988, (s32)ItemWeaponData_Attiike_Shisshi, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 65630, (s32)ItemEvent_Support_Sub_UseDeclere,
    65545, 30, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ITEM_HORROR1", -250000000, 0,
    -250000000, 110, 65545, 60, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ITEM_HORROR2",
    -250000000, 0, -250000000, 112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 983131, (s32)evt_eff64, 0, (s32)"holography_n64", 0, -30000000,
    -29999999, -29999998, -229998976, 120, 0, 0, 0, 0,
    0, 0, 110, 65546, 400, 196699, (s32)evt_env_blur_on, 0,
    1600, 112, 110, 65546, 400, 196699, (s32)evt_btl_camera_set_mode, 0,
    3, 655451, (s32)evt_btl_camera_set_moveto, 0, 0, 90, 450, 0,
    60, 0, 30, 11, 65546, 250, 655451, (s32)evt_btl_camera_set_moveto,
    0, 0, 110, 750, 0, 60, 0, 30,
    11, 65546, 250, 655451, (s32)evt_btl_camera_set_moveto, 0, 0, 90,
    450, 0, 60, 0, 30, 11, 65546, 250,
    655451, (s32)evt_btl_camera_set_moveto, 0, 0, 110, 750, 0, 60,
    0, 30, 11, 65546, 250, 655451, (s32)evt_btl_camera_set_moveto, 0,
    0, 90, 450, 0, 60, 0, 30, 11,
    65546, 250, 655451, (s32)evt_btl_camera_set_moveto, 0, 0, 110, 750,
    0, 60, 0, 30, 11, 65546, 250, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 112,
    65546, 2000, 65630, (s32)ItemEvent_Support_Sub_Effect, 65627, (s32)evt_audience_ap_recovery, 65546, 2500,
    65630, (s32)_return_home_event, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 ItemWeaponData_Attiike_Shisshi[] = {
    0, 0, 162, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, 0, 196608, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1677721600, 0, 0, (s32)ItemEvent_Attiike_Shisshi, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Naniga_Okorukana)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Naniga_Okorukana))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(_naniga_okorukana_check, -2, LW(13))
    SWITCH(LW(13))
        CASE_EQUAL(148)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        SET_VALUE(LW(9), 148)
        CALL_CHILD(PTR(ItemEvent_Recovery_Core))
        CASE_EQUAL(150)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Ultra_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        SET_VALUE(LW(9), 150)
        CALL_CHILD(PTR(ItemEvent_Recovery_Core))
        CASE_EQUAL(152)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Sinabita_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        SET_VALUE(LW(9), 152)
        CALL_CHILD(PTR(ItemEvent_Recovery_Core))
        CASE_EQUAL(154)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Honey_Syrup))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        SET_VALUE(LW(9), 154)
        CALL_CHILD(PTR(ItemEvent_Recovery_Core))
        CASE_EQUAL(156)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Royal_Jelly))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        SET_VALUE(LW(9), 156)
        CALL_CHILD(PTR(ItemEvent_Recovery_Core))
        CASE_EQUAL(135)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Biribiri_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Biribiri_Kinoko_Core))
        CASE_EQUAL(136)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Teki_Yokeeru))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Teki_Yokeeru_Core))
        CASE_EQUAL(157)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Jiwajiwa_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Jiwajiwa_Kinoko_Core))
        CASE_EQUAL(158)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Jiwajiwa_Syrup))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Jiwajiwa_Syrup_Core))
        CASE_EQUAL(128)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Kaminari_Gorogoro))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Kaminari_Core))
        CASE_EQUAL(129)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Kaminari_Dokkan))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Kaminari_Core))
        CASE_EQUAL(132)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Fire_Flower))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Fire_Flower_Core))
        CASE_EQUAL(130)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Kirakira_Otoshi))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Kirakira_Otoshi_Core))
        CASE_EQUAL(140)
        SET_VALUE(LW(12), PTR(ItemWeaponData_Stop_Watch))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(PTR(ItemEvent_Automatic_Target))
        CALL_CHILD(PTR(ItemEvent_Stop_Watch_Core))
        CASE_DEFAULT
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_SWITCH
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_Naniga_Okorukana[] = {
    0, 0, 163, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Naniga_Okorukana, 100, 0, 0,
};

s32 R_mystery_item_table[] = {
    148, 154, 156, 135, 136, 157, 158, 150,
    152, 129, 132, 130, 140, 0,
};

s32 ItemWeaponData_Shikaeshino_Kona[] = {
    0, 0, 177, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 768, 0, 0, (s32)ItemEvent_Shikaeshino_Kona, 100, 0, 0,
};

s32 ItemWeaponData_Kameno_Noroi[] = {
    0, 0, 178, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 196616, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    25603, 0, 0, 0, (s32)ItemEvent_Kameno_Noroi, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_RecoveryAndStatus)
    CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(8))
    CALL(btlevtcmd_WeaponAftereffect, LW(8))
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 60)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(8))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL_CHILD(PTR(ItemEvent_Recovery_Core_Effect))
    SWITCH(LW(9))
        CASE_EQUAL(216)
        CALL(evt_sub_random, 100, LW(0))
        IF_INT_LESS(LW(0), 40)
            SET_VALUE(LW(8), PTR(ItemWeaponData_FirstLovePuddingBiribiri))
            ELSE
            IF_INT_LESS(LW(0), 80)
                SET_VALUE(LW(8), PTR(ItemWeaponData_FirstLovePuddingTrans))
                ELSE
                SET_VALUE(LW(8), PTR(ItemWeaponData_FirstLovePuddingSleep))
            END_IF
        END_IF
        CASE_EQUAL(226)
        CALL(evt_sub_random, 100, LW(0))
        IF_INT_LESS(LW(0), 40)
            SET_VALUE(LW(8), PTR(ItemWeaponData_PeachTaltBiribiri))
            ELSE
            IF_INT_LESS(LW(0), 80)
                SET_VALUE(LW(8), PTR(ItemWeaponData_PeachTaltDodge))
                ELSE
                SET_VALUE(LW(8), PTR(ItemWeaponData_PeachTaltSleep))
            END_IF
        END_IF
        CASE_OR_EQUAL(233)
        CASE_OR_EQUAL(235)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_REST_CONDITION1"), LW(0), LW(1), LW(2), 0)
        CASE_END
    END_SWITCH
    SET_VALUE(LW(12), LW(8))
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_SpaceFood[] = {
    0, 0, 198, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 839057408,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_IceCandy[] = {
    0, 0, 199, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 1311232, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_NancyFrappe[] = {
    0, 0, 200, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 1311232, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_SnowRabbit[] = {
    0, 0, 201, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 3277568, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_TeaKinoko[] = {
    0, 0, 212, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554623, 0,
    0, 0, 1282, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_FirstLovePuddingBiribiri[] = {
    0, 0, 216, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 100, 33554432, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_FirstLovePuddingTrans[] = {
    0, 0, 216, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1677852672, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_FirstLovePuddingSleep[] = {
    0, 0, 216, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    1677852672, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_StarryDinner[] = {
    0, 0, 217, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 770, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_KararinaPasta[] = {
    0, 0, 224, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_MeromeroCake[] = {
    0, 0, 225, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 6554623, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_PeachTaltBiribiri[] = {
    0, 0, 226, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 100, 33554432, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_PeachTaltDodge[] = {
    0, 0, 226, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 6554112, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_PeachTaltSleep[] = {
    0, 0, 226, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    1677852672, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_BiribiriCandy[] = {
    0, 0, 227, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 100, 67108864, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_HealthySalad[] = {
    0, 0, 233, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    1677747200, 1677747200, 6553600, 100, 6553700, 0, 6553600, 1677721600,
    25600, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_FreshJuice[] = {
    0, 0, 235, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    1677747200, 1677747200, 6553600, 100, 6553700, 0, 6553600, 1677721600,
    25600, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_RedKararing[] = {
    0, 0, 173, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

s32 ItemWeaponData_FutarideForever[] = {
    0, 0, 219, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830240, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2562, 0, (s32)ItemEvent_RecoveryAndStatus, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_ThrowAttack)
    CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(12))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, -2, -1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, -2, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, -2, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, -2, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, -2, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, -2, 40)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(9), 69)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(12))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL(btlevtcmd_ConsumeItem, -2)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_CheckCommandUnit, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
            ELSE
            CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
            CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    CALL(btlevtcmd_GetUnitKind, -2, LW(0))
    IF_INT_EQUAL(LW(0), 222)
        CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("M_C_1"))
        BEGIN_SIBLING_EVENT
            WAIT_MS(500)
            CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 43)
        END_SIBLING_EVENT
    END_IF
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(5), LW(6), LW(7))
        ELSE
        CALL(btlevtcmd_GetFriendBelong, LW(10), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
            SET_VALUE(LW(5), -120)
            ELSE
            CALL(btlevtcmd_GetPos, -2, LW(5), LW(6), LW(7))
            SET_VALUE(LW(5), 100)
        END_IF
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    END_IF
    CALL(_get_throw_first_pos, -2, LW(0), LW(1), LW(2))
    CALL(_throw_item_icon, LW(9), LW(0), LW(1), LW(2), LW(5), LW(6), LW(7))
    SWITCH(LW(9))
        CASE_EQUAL(196)
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_THUNDERS_ATTACK4"), LW(5), LW(6), LW(7), 0)
        SET_VALUE(LW(0), LW(5))
        SET_VALUE(LW(1), LW(6))
        SET_VALUE(LW(2), LW(7))
        ADD(LW(0), 100)
        CALL(evt_eff, 0, STRING("hibashira"), 5, LW(5), LW(6), LW(6), LW(0), LW(1), LW(2), 6, FLOAT(1.3994141f), 60, 0, 0)
        SUBTRACT(LW(0), 200)
        CALL(evt_eff, 0, STRING("hibashira"), 5, LW(5), LW(6), LW(6), LW(0), LW(1), LW(2), 6, FLOAT(1.3994141f), 60, 0, 0)
        BEGIN_INLINE_EVENT
            ADD(LW(7), 20)
            CALL(_nancy_mirage, LW(5), LW(6), LW(7))
        END_INLINE_EVENT
        WAIT_MS(500)
        CASE_OR_EQUAL(202)
        CASE_OR_EQUAL(209)
        CALL(evt_eff, 0, STRING("bomb"), 0, LW(5), LW(6), LW(7), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_BTL_THUNDERS_ATTACK3"), LW(5), LW(6), LW(7), 0)
        CASE_END
    END_SWITCH
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, -2, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
        ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(30)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_NancyDynamite[] = {
    0, 0, 196, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 50332418, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_ThrowAttack, 100, 328965, 83886080,
};

s32 ItemWeaponData_CoconutsBomb[] = {
    0, 0, 202, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 50332418, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_ThrowAttack, 100, 328965, 83886080,
};

s32 ItemWeaponData_KachikachiDish[] = {
    0, 0, 203, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_ThrowAttack, 100, 328965, 83886080,
};

s32 ItemWeaponData_BomberEgg[] = {
    0, 0, 209, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 50332418, 0, 196672, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_ThrowAttack, 100, 328965, 83886080,
};

EVT_BEGIN(ItemEvent_Poison_Kinoko)
    SET_VALUE(LW(12), PTR(ItemWeaponData_PoisonKinoko))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(evt_sub_random, 100, LW(0))
    IF_INT_LESS(LW(0), 80)
        CALL_CHILD(PTR(ItemEvent_Support_Sub_Effect))
        ELSE
        CALL_CHILD(PTR(ItemEvent_GetTarget))
        CALL(evt_btl_camera_set_homing_unit, 0, LW(10), -1)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
        CALL(evt_btl_camera_set_zoom, 0, 200)
        CALL(btlevtcmd_GetPartsPos, LW(10), LW(11), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetStatusMg, LW(10), LW(5))
        MULTIPLY_FLOAT(LW(5), 50)
        ADD(LW(1), LW(5))
        CALL(evt_eff, 0, STRING("recovery"), 4, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(60)
        CALL(btlevtcmd_RecoverHp, LW(10), LW(11), 999)
    END_IF
END_IF
CALL(evt_audience_ap_recovery)
CALL_CHILD(PTR(_return_home_event))
CALL(btlevtcmd_StartWaitEvent, -2)
RETURN
EVT_END()

s32 ItemWeaponData_PoisonKinoko[] = {
    0, 0, 213, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerHPHalf2,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196680, 2047, -2147483648,
    0, 25603, 16777216, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_Poison_Kinoko, 100, 328965, 83886080,
};


#define EVW(evt, off) (*(s32*)((u8*)(evt) + (off)))
#define EVP(evt, off) (*(ThrowWork**)((u8*)(evt) + (off)))

typedef struct ThrowWork {
    Vec start;    // 0x0
    Vec pos;      // 0xC
    Vec target;   // 0x18
    s32 frames;   // 0x24
    f32 speed;    // 0x28
    f32 gravity;  // 0x2C
    f32 vy;       // 0x30
    u8 pad[0x7C - 0x34];
} ThrowWork;

USER_FUNC(_sampling_random_target) {
    BattleWorkWeaponTargets targets;
    BattleWork* wp;
    BattleWeapon* weapon;
    s32* args;
    s8 belong;
    s32 outUnit;
    s32 outPart;
    BattleWorkWeaponTargets* t;
    s32 idx;
    s32 r;
    wp = _battleWorkPointer;
    args = event->args;
    weapon = (BattleWeapon*)evtGetValue(event, args[0]);
    outUnit = args[1];
    outPart = args[2];
    belong = evtGetValue(event, args[3]);
    t = &targets;
    BattleSamplingEnemy(t, weapon, BattleTransID(event, -2), belong, weapon->targetClassFlags,
                        weapon->targetPropertyFlags, -wp->alliances[belong].attackDirection);
    if (t->numTargets <= 0) {
        evtSetValue(event, outUnit, -1);
        evtSetValue(event, outPart, -1);
    } else {
        r = irand(t->numTargets);
        idx = t->targetIndices[r];
        evtSetValue(event, outUnit, t->targets[idx].unitIdx);
        evtSetValue(event, outPart, t->targets[idx].partIdx);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_cam_rot) {
    f32 rot;

    if (isFirstCall) {
        event->userdata[0] = sysMsec2Frame(2000);
        event->userdata[1] = event->userdata[0];
    }
    rot = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(720.0f, 0.0f, 4, event->userdata[0], event->userdata[1]);
    camGetPtr(4)->rollAngle = rot;
    event->userdata[0]--;
    if (event->userdata[0] <= 0) {
        camGetPtr(4)->rollAngle = 0.0f;
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_rank_up) {
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));

    if (unit) {
        unit->mLevel += 5;
        if (unit->mLevel > 99) {
            unit->mLevel = 99;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_hpfp_change_declare_1) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (unit) {
        if (unit->currentKind == 0xDE) {
            BattleStatusWindowSystemOn();
        } else if (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
            BattleStatusWindowSystemOn();
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_hpfp_change_declare_2) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (unit) {
        if (unit->currentKind == 0xDE) {
            N_statusClearBlink();
            statusMarioHPBlink(120);
            statusFPBlink(120);
        } else if (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
            N_statusClearBlink();
            statusPartyHPBlink(120);
            statusFPBlink(120);
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_naniga_okorukana_check) {
    Vec pos;
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    BattleUnit* unit;
    s32 item;
    s32 i;
    u8* a;
    u8* b;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    if (!(unit->mAttributeFlags & 0x10)) {
        if (unit->mAttributeFlags & 0x2) {
            pos.y -= 5.0f;
        } else {
            pos.y += BtlUnit_GetHeight(unit) + 20;
        }
    }
    if (isFirstCall) {
        for (i = 0; R_mystery_item_table[i] != 0; i++) {
        }
        item = R_mystery_item_table[irand(i)];
        event->userdata[0] = (s32)effNanigaEntry(0, R_mystery_item_table, item, pos.x, pos.y, pos.z);
        effSetName((EffectEntry*)event->userdata[0], "effNaniga\0\0");
        evtSetValue(event, out, item);
        if (unit->currentKind == 0xDE) {
            a = (u8*)wp + BWOFF(0x16F25);
            b = (u8*)wp + BWOFF(0x16F26);
        } else if (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
            a = (u8*)wp + BWOFF(0x16F27);
            b = (u8*)wp + BWOFF(0x16F28);
        } else {
            goto end;
        }
        switch (item) {
            case 0x80:
            case 0x81:
            case 0x82:
            case 0x84:
            case 0x8C:
                (*a)++;
                break;
            default:
                (*b)++;
                break;
        }
    }
end:
    if (effNameToPtr("effNaniga\0\0")) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_get_throw_first_pos) {
    BattleUnit* unit;
    Vec pos;
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 ox = args[1];
    s32 oy = args[2];
    s32 oz = args[3];

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.y += 10.0f;
    if (!(unit->mAttributeFlags & 0x10)) {
        if (unit->mAttributeFlags & 0x2) {
            pos.y -= 5.0f;
        } else {
            pos.y += unit->mSizeMultiplier * BtlUnit_GetHeight(unit);
        }
    }
    evtSetFloat(event, ox, pos.x);
    evtSetFloat(event, oy, pos.y);
    evtSetFloat(event, oz, pos.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(_throw_item_icon) {
    s32* args = event->args;
    ThrowWork* wk;
    s32 item = evtGetValue(event, args[0]);
    f32 sx = evtGetFloat(event, args[1]);
    f32 sy = evtGetFloat(event, args[2]);
    f32 sz = evtGetFloat(event, args[3]);
    f32 tx = evtGetFloat(event, args[4]);
    f32 ty = evtGetFloat(event, args[5]);
    f32 tz = evtGetFloat(event, args[6]);

    if (isFirstCall) {
        Vec v;
        ((ThrowWork*)event->userdatap[0]) = BattleAlloc(sizeof(ThrowWork));
        wk = ((ThrowWork*)event->userdatap[0]);
        wk->target.x = tx;
        wk->target.y = ty;
        wk->target.z = tz;
        v.x = sx;
        v.y = sy;
        v.z = sz;
        wk->pos = v;
        wk->start = v;
        wk->frames = (s32)(distABf(wk->start.x, wk->start.z, wk->target.x, wk->target.z) / 15.0f) + 30;
        wk->gravity = 0.5f;
        wk->vy = (wk->target.y - wk->start.y) / wk->frames + wk->gravity * wk->frames / 2.0f;
        wk->speed = distABf(wk->start.x, wk->start.z, wk->target.x, wk->target.z) / wk->frames;
        event->userdata[1] = item;
        event->userdata[2] = 0;
        EVW(event, 0x84) = psndSFXOn_3D("SFX_ITEM_COOKING_THROW1", &v);
    }
    wk = ((ThrowWork*)event->userdatap[0]);
    if (event->userdata[2]) {
        psndSFXOff(EVW(event, 0x84));
        BattleFree(wk);
        return EVT_RETURN_DONE;
    }
    wk->pos.y += wk->vy;
    wk->vy -= wk->gravity;
    if (wk->vy < 0.0f && wk->pos.y < wk->target.y) {
        wk->pos.y = wk->target.y;
    }
    btlMovePos(wk->speed, angleABf(wk->start.x, wk->start.z, wk->target.x, wk->target.z), &wk->pos.x, &wk->pos.z);
    wk->frames--;
    if (wk->frames <= 0) {
        event->userdata[2] = 1;
        wk->pos = wk->target;
    }
    dispEntry(CAMERA_3D, 900.0f, 1, _disp_item_icon, event);
    return EVT_RETURN_BLOCK;
}

void _disp_item_icon(CameraId cameraId, void* param) {
    EventEntry* event = param;
    iconDispGx(&((ThrowWork*)event->userdatap[0])->pos, 0, itemDataTable[event->userdata[1]].icon_id, 1.0f);
}

USER_FUNC(_nancy_mirage) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    if (isFirstCall) {
        event->userdata[0] = 60;
        event->userdata[1] = animPoseEntry("c_cook", 1);
        event->userdata[2] = 0;
        EVW(event, 0x84) = x;
        EVW(event, 0x88) = y;
        EVW(event, 0x8C) = z;
        animPoseSetAnim(event->userdata[1], "A_2", 1);
        animPoseSetEffectAnim(event->userdata[1], "PM_Y_1A", 1);
    }
    event->userdata[0]--;
    if (event->userdata[0] < 0) {
        animPoseSetEffect(event->userdata[1], NULL, 0);
        animPoseRelease(event->userdata[1]);
        return EVT_RETURN_DONE;
    }
    animPoseMain(event->userdata[1]);
    dispEntry(CAMERA_3D, z, 2, _nancy_disp, event);
    return EVT_RETURN_BLOCK;
}

void _nancy_disp(CameraId cameraId, void* param) {
    EventEntry* event = param;
    Mtx mtx;
    Mtx scale;
    Mtx trans;
    f32 s;
    u8 alpha;
    s32 n;

    if (event->userdata[0] < 30) {
        n = 30 - event->userdata[0];
        s = 4.0f + 0.05f * n;
        alpha = 128 - n * 4;
    } else {
        s = 4.0f;
        alpha = 128;
    }
    PSMTXTrans(trans, EVW(event, 0x84), EVW(event, 0x88), EVW(event, 0x8C));
    PSMTXScale(scale, s, s, 1.0f);
    PSMTXIdentity(mtx);
    PSMTXConcat(scale, mtx, mtx);
    PSMTXConcat(trans, mtx, mtx);
    animPoseSetMaterialEvtColor(event->userdata[1], (GXColor){0xFF, 0xFF, 0xFF, alpha});
    animPoseSetMaterialFlagOn(event->userdata[1], 0x40);
    animPoseDrawMtx(event->userdata[1], mtx, 1, 0.0f, 2.0f);
    animPoseDrawMtx(event->userdata[1], mtx, 2, 0.0f, 2.0f);
    animPoseDrawMtx(event->userdata[1], mtx, 3, 0.0f, 2.0f);
}

USER_FUNC(_full_ap_recover) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (BtlUnit_GetBelong(unit) == 0) {
        pouchSetAP(pouchGetMaxAP());
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(ItemEvent_LastDinner)
    SET_VALUE(LW(12), PTR(ItemWeaponData_PoisonKinoko))
    CALL_CHILD(PTR(ItemEvent_Support_Sub_UseDeclere))
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(PTR(ItemEvent_GetTarget))
    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, LW(10), LW(5))
    CALL(btlevtcmd_GetStatusMg, LW(10), LW(6))
    MULTIPLY_FLOAT(LW(5), LW(6))
    DIVIDE(LW(5), 2)
    ADD(LW(1), LW(5))
    ADD(LW(2), 10)
    CALL(evt_eff, 0, STRING("charge"), 1, LW(0), LW(1), LW(2), FLOAT(1.0f), 120, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff, 0, STRING("mist"), 6, LW(0), LW(1), LW(2), 0, 180, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST2"), LW(0), LW(1), LW(2), LW(7))
    WAIT_MS(2000)
    CALL(evt_snd_sfxoff, LW(7))
    CALL(btlevtcmd_SetHp, LW(10), 1)
    CALL(btlevtcmd_SetFp, LW(10), 0)
    CALL(_full_ap_recover, LW(10))
    CALL(btlevtcmd_StatusWindowOnOff, 2)
    CALL(evt_eff, 0, STRING("indirect"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST3"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 1, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST3"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST3"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 3, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST3"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1750)
    CALL(evt_audience_ap_recovery)
    CALL_CHILD(PTR(_return_home_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 ItemWeaponData_LastDinner[] = {
    0, 0, 218, 0, 1677721600, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17826144, 268435456, 770, 0, 196872, 2047, -2147483648,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)ItemEvent_LastDinner, 100, 0, 0,
};

EVT_BEGIN(ItemEvent_Kaminari_Dokkan)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Kaminari_Dokkan))
    CALL_CHILD(PTR(ItemEvent_Kaminari))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Kaminari_Gorogoro)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Kaminari_Gorogoro))
    CALL_CHILD(PTR(ItemEvent_Kaminari))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Madowaseno_Kona)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Madowaseno_Kona))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Dekadeka_Drink)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Dekadeka_Drink))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Katikati_Koura)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Katikati_Koura))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Minimini_Kun)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Minimini_Kun))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Funyafunya_Kun)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Funyafunya_Kun))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Sukkiri_Drink)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Sukkiri_Drink))
    CALL_CHILD(PTR(ItemEvent_Support_RefreshEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Shikaeshino_Kona)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Shikaeshino_Kona))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()

EVT_BEGIN(ItemEvent_Kameno_Noroi)
    SET_VALUE(LW(12), PTR(ItemWeaponData_Kameno_Noroi))
    CALL_CHILD(PTR(ItemEvent_Support_NoEffect))
    RETURN
EVT_END()











