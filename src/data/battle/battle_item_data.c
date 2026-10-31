// Battle weapon data for usable items (mushrooms, cooked dishes and so on) and their effects.
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
#include "evt/evt_eff.h"
#include "evt/evt_env.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "statuswindow.h"

#include "battle/battle_detect.h"
EffectEntry* effNanigaEntry(s32 type, s32* table, s32 item, f32 x, f32 y, f32 z);
static void _nancy_disp(CameraId cameraId, void* param);
static void _disp_item_icon(CameraId cameraId, void* param);

static USER_FUNC(_cam_rot);
static USER_FUNC(_get_throw_first_pos);
static USER_FUNC(_nancy_mirage);
static USER_FUNC(_naniga_okorukana_check);
static USER_FUNC(_throw_item_icon);
static USER_FUNC(_hpfp_change_declare_2);
static USER_FUNC(_hpfp_change_declare_1);
static USER_FUNC(_rank_up);
static USER_FUNC(_sampling_random_target);

extern EvtWord _return_home_event[];
extern EvtWord ItemEvent_Automatic_Target[];
extern EvtWord ItemEvent_Recovery_Core_Effect[];
extern EvtWord ItemEvent_Recovery_Core[];
extern EvtWord ItemEvent_Recovery[];
extern EvtWord ItemEvent_Support_Sub_UseDeclere[];
extern EvtWord ItemEvent_GetTarget[];
extern EvtWord ItemEvent_Support_Sub_Effect[];
extern EvtWord ItemEvent_Support_NoEffect[];
extern EvtWord ItemEvent_Support_RefreshEffect[];
BattleWeapon ItemWeaponData_CookingItem;
BattleWeapon ItemWeaponData_Kinoko;
BattleWeapon ItemWeaponData_Kinkyuu_Kinoko;
BattleWeapon ItemWeaponData_Super_Kinoko;
BattleWeapon ItemWeaponData_Ultra_Kinoko;
BattleWeapon ItemWeaponData_Sinabita_Kinoko;
BattleWeapon ItemWeaponData_Honey_Syrup;
BattleWeapon ItemWeaponData_Maple_Syrup;
BattleWeapon ItemWeaponData_Royal_Jelly;
BattleWeapon ItemWeaponData_Tankobu;
extern EvtWord ItemEvent_Pow_Block[];
BattleWeapon ItemWeaponData_Pow_Block;
extern EvtWord ItemEvent_Fire_Flower_Core[];
extern EvtWord ItemEvent_Fire_Flower[];
BattleWeapon ItemWeaponData_Fire_Flower;
extern EvtWord ItemEvent_Kaminari_Core[];
extern EvtWord ItemEvent_Kaminari[];
BattleWeapon ItemWeaponData_Kaminari_Dokkan;
BattleWeapon ItemWeaponData_Kaminari_Gorogoro;
extern EvtWord ItemEvent_Kirakira_Otoshi_Core[];
extern EvtWord ItemEvent_Kirakira_Otoshi[];
BattleWeapon ItemWeaponData_Kirakira_Otoshi;
extern EvtWord ItemEvent_Koorino_Ibuki[];
BattleWeapon ItemWeaponData_Koorino_Ibuki;
extern EvtWord ItemEvent_Yurayura_Jishin[];
BattleWeapon ItemWeaponData_Yurayura_Jishin;
extern EvtWord ItemEvent_Teresano_Fuku[];
BattleWeapon ItemWeaponData_Teresano_Fuku;
extern EvtWord ItemEvent_Biribiri_Kinoko_Core[];
extern EvtWord ItemEvent_Biribiri_Kinoko[];
BattleWeapon ItemWeaponData_Biribiri_Kinoko;
extern EvtWord ItemEvent_Teki_Yokeeru_Core[];
extern EvtWord ItemEvent_Teki_Yokeeru[];
BattleWeapon ItemWeaponData_Teki_Yokeeru;
BattleWeapon ItemWeaponData_Madowaseno_Kona;
extern EvtWord ItemEvent_Nemure_Yoikoyo[];
BattleWeapon ItemWeaponData_Nemure_Yoikoyo;
extern EvtWord ItemEvent_Stop_Watch_Core[];
extern EvtWord ItemEvent_Stop_Watch[];
BattleWeapon ItemWeaponData_Stop_Watch;
extern EvtWord ItemEvent_Guruguru_Memawashi[];
BattleWeapon ItemWeaponData_Guruguru_Memawashi;
BattleWeapon ItemWeaponData_Dekadeka_Drink;
BattleWeapon ItemWeaponData_Katikati_Koura;
extern EvtWord ItemEvent_Suitooru[];
BattleWeapon ItemWeaponData_Suitooru;
extern EvtWord ItemEvent_Teki_Kyouka[];
BattleWeapon ItemWeaponData_Teki_Kyouka;
BattleWeapon ItemWeaponData_Minimini_Kun;
BattleWeapon ItemWeaponData_Funyafunya_Kun;
BattleWeapon ItemWeaponData_Sukkiri_Drink;
extern EvtWord ItemEvent_Jiwajiwa_Kinoko_Core[];
extern EvtWord ItemEvent_Jiwajiwa_Kinoko[];
BattleWeapon ItemWeaponData_Jiwajiwa_Kinoko;
extern EvtWord ItemEvent_Jiwajiwa_Syrup_Core[];
extern EvtWord ItemEvent_Jiwajiwa_Syrup[];
BattleWeapon ItemWeaponData_Jiwajiwa_Syrup;
extern EvtWord ItemEvent_Irekaeeru[];
BattleWeapon ItemWeaponData_Irekaeeru;
extern EvtWord ItemEvent_Attiike_Shisshi[];
BattleWeapon ItemWeaponData_Attiike_Shisshi;
extern EvtWord ItemEvent_Naniga_Okorukana[];
BattleWeapon ItemWeaponData_Naniga_Okorukana;
static s32 _item_table[14];
BattleWeapon ItemWeaponData_Shikaeshino_Kona;
BattleWeapon ItemWeaponData_Kameno_Noroi;
extern EvtWord ItemEvent_RecoveryAndStatus[];
BattleWeapon ItemWeaponData_SpaceFood;
BattleWeapon ItemWeaponData_IceCandy;
BattleWeapon ItemWeaponData_NancyFrappe;
BattleWeapon ItemWeaponData_SnowRabbit;
BattleWeapon ItemWeaponData_TeaKinoko;
BattleWeapon ItemWeaponData_FirstLovePuddingBiribiri;
BattleWeapon ItemWeaponData_FirstLovePuddingTrans;
BattleWeapon ItemWeaponData_FirstLovePuddingSleep;
BattleWeapon ItemWeaponData_StarryDinner;
BattleWeapon ItemWeaponData_KararinaPasta;
BattleWeapon ItemWeaponData_MeromeroCake;
BattleWeapon ItemWeaponData_PeachTaltBiribiri;
BattleWeapon ItemWeaponData_PeachTaltDodge;
BattleWeapon ItemWeaponData_PeachTaltSleep;
BattleWeapon ItemWeaponData_BiribiriCandy;
BattleWeapon ItemWeaponData_HealthySalad;
BattleWeapon ItemWeaponData_FreshJuice;
BattleWeapon ItemWeaponData_RedKararing;
BattleWeapon ItemWeaponData_FutarideForever;
extern EvtWord ItemEvent_ThrowAttack[];
BattleWeapon ItemWeaponData_NancyDynamite;
BattleWeapon ItemWeaponData_CoconutsBomb;
BattleWeapon ItemWeaponData_KachikachiDish;
BattleWeapon ItemWeaponData_BomberEgg;
extern EvtWord ItemEvent_Poison_Kinoko[];
BattleWeapon ItemWeaponData_PoisonKinoko;
extern EvtWord ItemEvent_LastDinner[];
BattleWeapon ItemWeaponData_LastDinner;
extern EvtWord ItemEvent_Kaminari_Dokkan[];
extern EvtWord ItemEvent_Kaminari_Gorogoro[];
extern EvtWord ItemEvent_Madowaseno_Kona[];
extern EvtWord ItemEvent_Dekadeka_Drink[];
extern EvtWord ItemEvent_Katikati_Koura[];
extern EvtWord ItemEvent_Minimini_Kun[];
extern EvtWord ItemEvent_Funyafunya_Kun[];
extern EvtWord ItemEvent_Sukkiri_Drink[];
extern EvtWord ItemEvent_Shikaeshino_Kona[];
extern EvtWord ItemEvent_Kameno_Noroi[];

/**
 * Walks the item user back to its home position (if it moved), at walking speed;
 * the common ending of the item scripts.
 */
EVT_BEGIN(_return_home_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    LABEL(95)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(3), LW(4), LW(5))
    IF_INT_NOT_EQUAL(LW(0), LW(3))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), 42)
        END_SIBLING_EVENT
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    END_IF
    RETURN
EVT_END()

/**
 * Picks the target in LW(10)/LW(11) for the item in LW(8):
 * the player's selected target when a player unit uses it,
 * otherwise one chosen from the candidates (enemies using items).
 */
EVT_BEGIN(ItemEvent_Automatic_Target)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(8))
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    RETURN
EVT_END()

/**
 * The healing part of a recovery item on target LW(10)/LW(11):
 * reads the item's HP and FP restore from item LW(9),
 * shows the heart and flower effects over the target and restores the HP, then the FP.
 */
EVT_BEGIN(ItemEvent_Recovery_Core_Effect)
    CALL(evt_btl_camera_set_homing_unit, 0, LW(10), BTL_UNIT_NONE)
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

/**
 * Heals the target with ItemEvent_Recovery_Core_Effect, resets the camera,
 * returns the user home and ends both units' turns.
 */
EVT_BEGIN(ItemEvent_Recovery_Core)
    CALL_CHILD(ItemEvent_Recovery_Core_Effect)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(60)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Recovery items (Mushroom, Super and Ultra Shroom, Life Shroom, Dried Shroom, Honey and Maple Syrup,
 * Jammin' Jelly, the plain cooked dishes and so on):
 * the user steps forward, holds the item up and uses it on the chosen ally,
 * restoring the HP and FP the item table gives.
 */
EVT_BEGIN(ItemEvent_Recovery)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(8))
    CALL(btlevtcmd_WeaponAftereffect, LW(8))
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 60)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(8))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL_CHILD(ItemEvent_Recovery_Core)
    RETURN
EVT_END()

/**
 * The common opening of the support items: the camera closes in, Mario steps forward (enemies stay put),
 * holds the item up and it is consumed.
 */
EVT_BEGIN(ItemEvent_Support_Sub_UseDeclere)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(600)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    RETURN
EVT_END()

/**
 * Picks the target in LW(10)/LW(11) for weapon LW(12):
 * the first of all targets for items that hit several, the selected one for player units,
 * otherwise one chosen from the candidates.
 */
EVT_BEGIN(ItemEvent_GetTarget)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Applies weapon LW(12) to each of its targets in turn:
 * missed or dodged targets play their dodge, the rest take the item's damage and status.
 */
EVT_BEGIN(ItemEvent_Support_Sub_Effect)
    CALL_CHILD(ItemEvent_GetTarget)
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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

/**
 * Support items with no effect of their own (Power Punch, Courage Shell, Mini Mr. Mini, Mr. Softener,
 * Ruin Powder, Spite Pouch, Koopa Curse): use, apply weapon LW(12) to its targets, audience boost, return home.
 */
EVT_BEGIN(ItemEvent_Support_NoEffect)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Status-curing support items (Tasty Tonic): like ItemEvent_Support_NoEffect,
 * with the cleansing sound on each target hit.
 */
EVT_BEGIN(ItemEvent_Support_RefreshEffect)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_GetTarget)
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_CookingItem = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, 0.0f, 0, 0, 0, 0, // baseFpCost..reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    148, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Kinkyuu_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    151, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Super_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    149, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Ultra_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    150, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Sinabita_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    152, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Honey_Syrup = {
    NULL, 0, // name..icon
    {0}, // pad_06
    154, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_PARTNER | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Maple_Syrup = {
    NULL, 0, // name..icon
    {0}, // pad_06
    155, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_PARTNER | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Royal_Jelly = {
    NULL, 0, // name..icon
    {0}, // pad_06
    156, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_PARTNER | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_Tankobu = {
    NULL, 0, // name..icon
    {0}, // pad_06
    165, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_PARTNER | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Recovery, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** POW Block: a POW Block appears above Mario, he hits it and every enemy takes 2 damage as the stage shakes. */
EVT_BEGIN(ItemEvent_Pow_Block)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
        ADD(LW(1), 16)
        ADD(LW(1), LW(5))
    ELSE
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(5))
        ADD(LW(1), 16)
        ADD(LW(1), LW(5))
    END_IF
    BEGIN_SIBLING_EVENT
        WAIT_MS(100)
        CALL(evt_mobj_entry, STRING("_BtCIPw"), STRING("MOBJ_PowerBlock"))
        CALL(evt_mobj_set_position, STRING("_BtCIPw"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_POW_APPEAR1"), LW(0), LW(1), LW(2), 0)
    END_SIBLING_EVENT
    ADD(LW(1), 10)
    ADD(LW(2), 25)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(2050)
        CALL(evt_eff, STRING(""), STRING("kemuri_test"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    WAIT_FRAMES(5)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 43)
    WAIT_FRAMES(30)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.7998047f))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 44)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 14, -1)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 43)
        WAIT_FRAMES(60)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 42)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 43)
    END_SIBLING_EVENT
    BEGIN_INLINE_EVENT
        WAIT_FRAMES(5)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_MOBJ_POW_BLOCK1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mobj_set_anim, STRING("_BtCIPw"), STRING("A_1"))
        WAIT_FRAMES(3)
        CALL(evt_btl_camera_shake_h, 0, 8, 0, 10, 13)
        WAIT_FRAMES(50)
        CALL(evt_mobj_delete, STRING("_BtCIPw"))
    END_INLINE_EVENT
    CALL(evt_audience_reflesh_natural_all, 100)
    WAIT_FRAMES(7)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&ItemWeaponData_Pow_Block))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(&ItemWeaponData_Pow_Block), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(&ItemWeaponData_Pow_Block), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&ItemWeaponData_Pow_Block))
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Pow_Block = {
    NULL, 0, // name..icon
    {0}, // pad_06
    139, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {2, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_FLIPS_SHELLED | SPECIAL_FLIPS_BOMB_FLIPPABLE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Pow_Block, // attackEvtScript
    {0, 100, 100, 100, 75, 10, 5, 5, 5, 5, 0, 0}, // stageEffectRates
};

/** Fire Flower's attack: the fire effect rains on the enemies with its sound, then each enemy takes 3 fire damage. */
EVT_BEGIN(ItemEvent_Fire_Flower_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_MS(100)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 40)
    SET_VALUE(LW(3), LW(0))
    SET_VALUE(LW(4), LW(1))
    SET_VALUE(LW(5), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(3), 240)
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
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&ItemWeaponData_Fire_Flower))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(&ItemWeaponData_Fire_Flower), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), PTR(&ItemWeaponData_Fire_Flower), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    WAIT_MS(80)
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Fire Flower: the use animation, then ItemEvent_Fire_Flower_Core. */
EVT_BEGIN(ItemEvent_Fire_Flower)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Fire_Flower))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Fire_Flower_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Fire_Flower = {
    NULL, 0, // name..icon
    {0}, // pad_06
    132, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    1, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Fire_Flower, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Thunder attack for weapon LW(12): lightning strikes each target (one or all) and deals the weapon's damage,
 * then the user returns home.
 */
EVT_BEGIN(ItemEvent_Kaminari_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
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
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** The thunder items' use animation (weapon LW(12)), then ItemEvent_Kaminari_Core. */
EVT_BEGIN(ItemEvent_Kaminari)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL_CHILD(ItemEvent_Kaminari_Core)
    RETURN
EVT_END()

/** Thunder Rage: 5 lightning damage to every enemy. */
EVT_BEGIN(ItemEvent_Kaminari_Dokkan)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Kaminari_Dokkan))
    CALL_CHILD(ItemEvent_Kaminari)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Kaminari_Dokkan = {
    NULL, 0, // name..icon
    {0}, // pad_06
    129, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    4, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Kaminari_Dokkan, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

/** Thunder Bolt: 5 lightning damage to one enemy. */
EVT_BEGIN(ItemEvent_Kaminari_Gorogoro)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Kaminari_Gorogoro))
    CALL_CHILD(ItemEvent_Kaminari)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Kaminari_Gorogoro = {
    NULL, 0, // name..icon
    {0}, // pad_06
    128, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    4, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Kaminari_Gorogoro, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

/**
 * Shooting Star's attack: stars fall over the enemies one after another (to random targets),
 * then every enemy takes 6 damage.
 */
EVT_BEGIN(ItemEvent_Kirakira_Otoshi_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(15), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            SET_VALUE(LW(15), 1)
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(15), 1)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            SET_VALUE(LW(15), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_KIRAKIRA_FALL1"), 0)
    IF_INT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(3), LW(4), LW(5))
        CALL(evt_eff64, STRING(""), STRING("sstar_n64"), 2, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), FLOAT(10.0f), 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_KIRAKIRA_FALL1"), LW(0), LW(1), LW(2), 0)
        WAIT_FRAMES(50)
    ELSE
        BEGIN_SIBLING_EVENT
            WAIT_MS(500)
            LOOP(5)
                CALL(evt_btl_camera_shake_h, 0, 5, 0, 20, 12)
                WAIT_MS(400)
                WAIT_MS(200)
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            LOOP(5)
                CALL(evt_sub_random, 6, LW(0))
                ADD(LW(0), 27)
                WAIT_FRAMES(LW(0))
                CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
                CALL(_sampling_random_target, LW(12), LW(10), LW(11), LW(0))
                IF_INT_NOT_EQUAL(LW(10), -1)
                    CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
                    CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
                END_IF
            END_LOOP
        END_SIBLING_EVENT
        BEGIN_SIBLING_EVENT
            LOOP(7)
                CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_KIRAKIRA_FALL1"), LW(0), LW(1), LW(2), 0)
                WAIT_MS(500)
            END_LOOP
        END_SIBLING_EVENT
        LOOP(60)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_GetStageSize, EVT_NULLPTR, LW(1), EVT_NULLPTR)
            CALL(evt_sub_random, 200, LW(0))
            CALL(evt_sub_random, 320, LW(3))
            CALL(btlevtcmd_GetFriendBelong, LW(10), LW(6))
            IF_INT_EQUAL(LW(6), 0)
                MULTIPLY(LW(3), -1)
                SET_VALUE(LW(4), 0)
            ELSE
                MULTIPLY(LW(0), -1)
                SET_VALUE(LW(4), 0)
            END_IF
            CALL(btlevtcmd_check_battleflag, LW(8), 256)
            IF_INT_EQUAL(LW(8), 0)
                SET_VALUE(LW(2), 0)
                SET_VALUE(LW(5), 0)
            ELSE
                SET_VALUE(LW(2), 200)
                SET_VALUE(LW(5), 200)
            END_IF
            CALL(evt_sub_random, 120, LW(8))
            SUBTRACT(LW(8), 60)
            ADD(LW(5), LW(8))
            CALL(evt_sub_random, 120, LW(8))
            SUBTRACT(LW(8), 60)
            ADD(LW(2), LW(8))
            CALL(btlevtcmd_TransStageFloorPosition, LW(3), LW(4), LW(5))
            CALL(evt_eff64, STRING(""), STRING("sstar_n64"), 2, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), FLOAT(8.0f), 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
        WAIT_FRAMES(50)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    ELSE
        SET_VALUE(LW(10), -1)
    END_IF
    WAIT_MS(80)
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Shooting Star: the use animation, then ItemEvent_Kirakira_Otoshi_Core. */
EVT_BEGIN(ItemEvent_Kirakira_Otoshi)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Kirakira_Otoshi))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    CALL_CHILD(ItemEvent_Kirakira_Otoshi_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Kirakira_Otoshi = {
    NULL, 0, // name..icon
    {0}, // pad_06
    130, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Kirakira_Otoshi, // attackEvtScript
    {0, 10, 10, 100, 10, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Ice Storm: an icy wind blows over the enemies for 3 ice damage each, with a chance to freeze them for two turns. */
EVT_BEGIN(ItemEvent_Koorino_Ibuki)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Koorino_Ibuki))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_ICE_WIND1"), LW(0), LW(1), LW(2), LW(15))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
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
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Koorino_Ibuki = {
    NULL, 0, // name..icon
    {0}, // pad_06
    131, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {3, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    2, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, // burnTime
#if VERSION <= VERSION_DEMO_US
    100, // freezeChance
#else
    95, // freezeChance
#endif
    2, // freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Koorino_Ibuki, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Earthquake: the stage shakes and dust falls, and every enemy that is not floating takes 5 damage. */
EVT_BEGIN(ItemEvent_Yurayura_Jishin)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Yurayura_Jishin))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
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
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Yurayura_Jishin = {
    NULL, 0, // name..icon
    {0}, // pad_06
    133, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_NO_FLOATING_2 | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Yurayura_Jishin, // attackEvtScript
    {0, 100, 100, 100, 75, 10, 5, 5, 5, 5, 0, 0}, // stageEffectRates
};

/** Boo's Sheet: makes the chosen ally invisible for two turns. */
EVT_BEGIN(ItemEvent_Teresano_Fuku)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Teresano_Fuku))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Teresano_Fuku = {
    NULL, 0, // name..icon
    {0}, // pad_06
    134, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    100, // invisibleChance
    2, // invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Teresano_Fuku, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Volt Shroom's effect on its target (electrified for five turns), then the user returns home. */
EVT_BEGIN(ItemEvent_Biribiri_Kinoko_Core)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Volt Shroom: the use animation, then ItemEvent_Biribiri_Kinoko_Core. */
EVT_BEGIN(ItemEvent_Biribiri_Kinoko)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Biribiri_Kinoko))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Biribiri_Kinoko_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Biribiri_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    135, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, // poisonStrength..confuseTime
    100, // electricChance
    5, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Biribiri_Kinoko, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Repel Cape's effect on its target (dodgy for four turns), then the user returns home. */
EVT_BEGIN(ItemEvent_Teki_Yokeeru_Core)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Repel Cape: the use animation, then ItemEvent_Teki_Yokeeru_Core. */
EVT_BEGIN(ItemEvent_Teki_Yokeeru)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Teki_Yokeeru))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Teki_Yokeeru_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Teki_Yokeeru = {
    NULL, 0, // name..icon
    {0}, // pad_06
    136, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, // poisonStrength..electricTime
    100, // dodgyChance
    4, // dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Teki_Yokeeru, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Ruin Powder: confuses every enemy for three turns. */
EVT_BEGIN(ItemEvent_Madowaseno_Kona)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Madowaseno_Kona))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Madowaseno_Kona = {
    NULL, 0, // name..icon
    {0}, // pad_06
    137, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, // poisonStrength
    100, // confuseChance
    3, // confuseTime
    0, 0, 0, 0, 0, 0, 0, 0, // electricChance..freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Madowaseno_Kona, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Sleepy Sheep: a flock of sheep runs across the enemies, putting them to sleep for five turns. */
EVT_BEGIN(ItemEvent_Nemure_Yoikoyo)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Nemure_Yoikoyo))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(evt_btl_camera_shake_h, 0, 1, 0, 10000, 0)
#if VERSION <= VERSION_JP
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
#else
    CALL(btlevtcmd_check_battleflag, LW(0), 256)
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    ELSE
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(2), 15)
        CALL(evt_eff, 0, STRING("sheep"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    END_IF
#endif
    WAIT_FRAMES(300)
    CALL(evt_btl_camera_noshake, 0)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Nemure_Yoikoyo = {
    NULL, 0, // name..icon
    {0}, // pad_06
    138, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
#if VERSION <= VERSION_DEMO_US
    100, // sleepChance
#else
    95, // sleepChance
#endif
    5, // sleepTime
    0, 0, 0, 0, 0, 0, 0, 0, // stopChance..confuseChance
    0, 0, 0, 0, 0, 0, 0, 0, // confuseTime..freezeChance
    0, 0, 0, 0, 0, 0, 0, 0, // freezeTime..defChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeTime..fastTime
    0, 0, 0, 0, 0, 0, 0, 0, // slowChance..invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Nemure_Yoikoyo, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Stopwatch's effect: the clock effect over the stage, then every enemy is stopped for three turns. */
EVT_BEGIN(ItemEvent_Stop_Watch_Core)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_STOP_WATCH1"), 0)
    CALL(btlevtcmd_check_battleflag, LW(0), 256)
    IF_INT_EQUAL(LW(0), 0)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_eff64, 0, STRING("timestamp_n64"), 0, 0, 0, 0, FLOAT(1.0f), 200, 0, 0, 0, 0, 0, 0)
#else
        CALL(evt_eff64, 0, STRING("timestamp_n64"), 0, 0, 0, 103, FLOAT(1.0f), 200, 0, 0, 0, 0, 0, 0)
#endif
    ELSE
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        ADD(LW(2), 30)
        CALL(evt_eff64, 0, STRING("timestamp_n64"), 0, 0, 0, LW(2), FLOAT(1.0f), 200, 0, 0, 0, 0, 0, 0)
    END_IF
    WAIT_FRAMES(200)
    CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
    CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetSelectNextEnemy, LW(10), LW(11))
    GOTO(10)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Stopwatch: the use animation, then ItemEvent_Stop_Watch_Core. */
EVT_BEGIN(ItemEvent_Stop_Watch)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Stop_Watch))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL_CHILD(ItemEvent_Stop_Watch_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Stop_Watch = {
    NULL, 0, // name..icon
    {0}, // pad_06
    140, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, // sleepChance..sleepTime
#if VERSION <= VERSION_DEMO_US
    100, // stopChance
#else
    95, // stopChance
#endif
    3, // stopTime
    0, 0, 0, 0, 0, 0, 0, 0, // dizzyChance..electricChance
    0, 0, 0, 0, 0, 0, 0, 0, // electricTime..sizeChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeTime..defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Stop_Watch, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Dizzy Dial: the camera rolls around twice (_cam_rot) and every enemy becomes dizzy for three turns. */
EVT_BEGIN(ItemEvent_Guruguru_Memawashi)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Guruguru_Memawashi))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(evt_snd_sfxon, STRING("SFX_ITEM_GURUGURU1"), 0)
    BEGIN_SIBLING_EVENT
        CALL(evt_env_blur_on, 0, 2000)
    END_SIBLING_EVENT
    CALL(_cam_rot)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Guruguru_Memawashi = {
    NULL, 0, // name..icon
    {0}, // pad_06
    141, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, // sleepChance..stopTime
    100, // dizzyChance
    3, // dizzyTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonChance..dodgyChance
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyTime..sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Guruguru_Memawashi, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Power Punch: makes the chosen ally huge (attack up) for three turns. */
EVT_BEGIN(ItemEvent_Dekadeka_Drink)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Dekadeka_Drink))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Dekadeka_Drink = {
    NULL, 0, // name..icon
    {0}, // pad_06
    142, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Dekadeka_Drink, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Courage Shell: raises the chosen ally's defence by 3 for three turns. */
EVT_BEGIN(ItemEvent_Katikati_Koura)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Katikati_Koura))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Katikati_Koura = {
    NULL, 0, // name..icon
    {0}, // pad_06
    143, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, // atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    3, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Katikati_Koura, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** HP Drain: deals 5 damage to one enemy and restores as much HP to the user as it dealt. */
EVT_BEGIN(ItemEvent_Suitooru)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Suitooru))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL(btlevtcmd_GetDamage, LW(10), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, LW(9), LW(0))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
        CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(8))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Suitooru = {
    NULL, 0, // name..icon
    {0}, // pad_06
    144, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {5, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Suitooru, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Trade Off: raises the enemies' level by 5 (_rank_up), which raises the Star Points they are worth. */
EVT_BEGIN(ItemEvent_Teki_Kyouka)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Teki_Kyouka))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    LABEL(10)
    IF_INT_EQUAL(LW(10), -1)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_ITEM_RANK_UP_ENEMY1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("rankup"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(_rank_up, LW(10))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Teki_Kyouka = {
    NULL, 0, // name..icon
    {0}, // pad_06
    145, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Teki_Kyouka, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Mini Mr. Mini: shrinks every enemy (attack down) for three turns. */
EVT_BEGIN(ItemEvent_Minimini_Kun)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Minimini_Kun))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Minimini_Kun = {
    NULL, 0, // name..icon
    {0}, // pad_06
    146, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, // burnTime..freezeTime
    100, // sizeChangeChance
    3, // sizeChangeTime
    -2, // sizeChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeChance..allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Minimini_Kun, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Mr. Softener: lowers every enemy's defence by 3 for three turns. */
EVT_BEGIN(ItemEvent_Funyafunya_Kun)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Funyafunya_Kun))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Funyafunya_Kun = {
    NULL, 0, // name..icon
    {0}, // pad_06
    147, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, // atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    -3, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Funyafunya_Kun, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Tasty Tonic: cures the chosen ally's bad status effects. */
EVT_BEGIN(ItemEvent_Sukkiri_Drink)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Sukkiri_Drink))
    CALL_CHILD(ItemEvent_Support_RefreshEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Sukkiri_Drink = {
    NULL, 0, // name..icon
    {0}, // pad_06
    153, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    100, // sleepChance
    0, // sleepTime
    100, // stopChance
    0, // stopTime
    100, // dizzyChance
    0, // dizzyTime
    100, // poisonChance
    0, 0, // poisonTime..poisonStrength
    100, // confuseChance
    0, 0, 0, 0, 0, // confuseTime..dodgyTime
    100, // burnChance
    0, // burnTime
    100, // freezeChance
    0, // freezeTime
    100, // sizeChangeChance
    0, 0, 0, 0, 0, // sizeChangeTime..atkChangeStrength
    100, // defChangeChance
    0, 0, // defChangeTime..defChangeStrength
    100, // allergicChance
    0, 0, 0, 0, 0, // allergicTime..fastTime
    100, // slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Sukkiri_Drink, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Slow Shroom's effect on its target (HP regained over several turns), then the user returns home. */
EVT_BEGIN(ItemEvent_Jiwajiwa_Kinoko_Core)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Slow Shroom: the use animation, then ItemEvent_Jiwajiwa_Kinoko_Core. */
EVT_BEGIN(ItemEvent_Jiwajiwa_Kinoko)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Jiwajiwa_Kinoko))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Jiwajiwa_Kinoko_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Jiwajiwa_Kinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    157, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE | TARGET_WEIGHT_PREFER_LOW_HP_RATIO | TARGET_WEIGHT_PREFER_IN_PERIL, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, // invisibleChance..invisibleTime
    10, // hpRegenTime
    2, // hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Jiwajiwa_Kinoko, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Gradual Syrup's effect on its target (FP regained over several turns), then the user returns home. */
EVT_BEGIN(ItemEvent_Jiwajiwa_Syrup_Core)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Gradual Syrup: the use animation, then ItemEvent_Jiwajiwa_Syrup_Core. */
EVT_BEGIN(ItemEvent_Jiwajiwa_Syrup)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Jiwajiwa_Syrup))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL_CHILD(ItemEvent_Jiwajiwa_Syrup_Core)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Jiwajiwa_Syrup = {
    NULL, 0, // name..icon
    {0}, // pad_06
    158, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, // invisibleChance..hpRegenStrength
    10, // fpRegenTime
    2, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Jiwajiwa_Syrup, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Point Swap: swaps the target's HP and FP, blinking the HP and FP in the status window. */
EVT_BEGIN(ItemEvent_Irekaeeru)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Irekaeeru))
    CALL_CHILD(ItemEvent_GetTarget)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(_hpfp_change_declare_1, LW(10))
    CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    ADD(LW(2), 5)
    CALL(evt_eff, STRING(""), STRING("irekae"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_snd_se, LW(10), STRING("SFX_ITEM_HP_FP_CHANGE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(120)
    CALL(btlevtcmd_CheckAttribute, LW(10), 1048576, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetMaxHp, LW(10), LW(5))
        CALL(btlevtcmd_GetHp, LW(10), LW(6))
        CALL(btlevtcmd_GetMaxFp, LW(10), LW(7))
        CALL(btlevtcmd_GetFp, LW(10), LW(8))
        IF_INT_GREATER(LW(8), LW(5))
            SET_VALUE(LW(8), LW(5))
        END_IF
        CALL(btlevtcmd_SetHp, LW(10), LW(8))
        IF_INT_GREATER(LW(6), LW(7))
            SET_VALUE(LW(6), LW(7))
        END_IF
        CALL(btlevtcmd_SetFp, LW(10), LW(6))
        CALL(_hpfp_change_declare_2, LW(10))
        IF_INT_EQUAL(LW(8), 0)
            CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
            SWITCH(LW(5))
                CASE_EQUAL(3)
                CALL(btlevtcmd_StartAvoid, LW(10), 38)
                CASE_EQUAL(6)
                CALL(btlevtcmd_StartAvoid, LW(10), 39)
                CASE_EQUAL(2)
                CALL(btlevtcmd_StartAvoid, LW(10), 40)
                CASE_EQUAL(1)
                CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
            END_SWITCH
        END_IF
    END_IF
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(30)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Irekaeeru = {
    NULL, 0, // name..icon
    {0}, // pad_06
    161, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, // element
    27, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Irekaeeru, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Fright Mask: a scary hologram appears twice and frightens the enemies, which can make them flee. */
EVT_BEGIN(ItemEvent_Attiike_Shisshi)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Attiike_Shisshi))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ITEM_HORROR1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(60)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ITEM_HORROR2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
#if VERSION <= VERSION_DEMO_US
    CALL(evt_eff64, STRING(""), STRING("holography_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 120, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(120)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_FRAMES(150)
#else
    CALL(evt_eff64, 0, STRING("holography_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 120, 0, 0, 0, 0, 0, 0)
    BEGIN_SIBLING_EVENT
        WAIT_MS(400)
        CALL(evt_env_blur_on, 0, 1600)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        WAIT_MS(400)
        CALL(evt_btl_camera_set_mode, 0, 3)
        CALL(evt_btl_camera_set_moveto, 0, 0, 90, 450, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_moveto, 0, 0, 110, 750, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_moveto, 0, 0, 90, 450, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_moveto, 0, 0, 110, 750, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_moveto, 0, 0, 90, 450, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_moveto, 0, 0, 110, 750, 0, 60, 0, 30, 11)
        WAIT_MS(250)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    END_SIBLING_EVENT
    WAIT_MS(2000)
    CALL_CHILD(ItemEvent_Support_Sub_Effect)
    CALL(evt_audience_ap_recovery)
    WAIT_MS(2500)
#endif
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Attiike_Shisshi = {
    NULL, 0, // name..icon
    {0}, // pad_06
    162, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, // fastChance..slowTime
    100, // frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Attiike_Shisshi, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Mystery: a roulette picks a random item (_naniga_okorukana_check) and its effect is played:
 * one of the recovery, status or attack item scripts on a fitting target.
 */
EVT_BEGIN(ItemEvent_Naniga_Okorukana)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Naniga_Okorukana))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(_naniga_okorukana_check, BTL_UNIT_SELF, LW(13))
    SWITCH(LW(13))
        CASE_EQUAL(148)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        SET_VALUE(LW(9), 148)
        CALL_CHILD(ItemEvent_Recovery_Core)
        CASE_EQUAL(150)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Ultra_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        SET_VALUE(LW(9), 150)
        CALL_CHILD(ItemEvent_Recovery_Core)
        CASE_EQUAL(152)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Sinabita_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        SET_VALUE(LW(9), 152)
        CALL_CHILD(ItemEvent_Recovery_Core)
        CASE_EQUAL(154)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Honey_Syrup))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        SET_VALUE(LW(9), 154)
        CALL_CHILD(ItemEvent_Recovery_Core)
        CASE_EQUAL(156)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Royal_Jelly))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        SET_VALUE(LW(9), 156)
        CALL_CHILD(ItemEvent_Recovery_Core)
        CASE_EQUAL(135)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Biribiri_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Biribiri_Kinoko_Core)
        CASE_EQUAL(136)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Teki_Yokeeru))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Teki_Yokeeru_Core)
        CASE_EQUAL(157)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Jiwajiwa_Kinoko))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Jiwajiwa_Kinoko_Core)
        CASE_EQUAL(158)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Jiwajiwa_Syrup))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Jiwajiwa_Syrup_Core)
        CASE_EQUAL(128)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Kaminari_Gorogoro))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Kaminari_Core)
        CASE_EQUAL(129)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Kaminari_Dokkan))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Kaminari_Core)
        CASE_EQUAL(132)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Fire_Flower))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Fire_Flower_Core)
        CASE_EQUAL(130)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Kirakira_Otoshi))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Kirakira_Otoshi_Core)
        CASE_EQUAL(140)
        SET_VALUE(LW(12), PTR(&ItemWeaponData_Stop_Watch))
        SET_VALUE(LW(8), LW(12))
        CALL_CHILD(ItemEvent_Automatic_Target)
        CALL_CHILD(ItemEvent_Stop_Watch_Core)
        CASE_DEFAULT
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_SWITCH
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Naniga_Okorukana = {
    NULL, 0, // name..icon
    {0}, // pad_06
    163, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Naniga_Okorukana, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

// The items Naniga Okorukana (the mystery item) can turn into. The demo map has the table as a static local of
// _naniga_okorukana_check (_item_table$597); there it would land at the end of .data instead of here, so it
// stays at file scope.
static s32 _item_table[] = {
    148, 154, 156, 135, 136, 157, 158, 150,
    152, 129, 132, 130, 140, 0,
};

/** Spite Pouch: gives the chosen ally payback for three turns. */
EVT_BEGIN(ItemEvent_Shikaeshino_Kona)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Shikaeshino_Kona))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Shikaeshino_Kona = {
    NULL, 0, // name..icon
    {0}, // pad_06
    177, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, // fastChance..galeForceChance
    3, // paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Shikaeshino_Kona, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/** Koopa Curse: slows the chosen enemy for three turns. */
EVT_BEGIN(ItemEvent_Kameno_Noroi)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_Kameno_Noroi))
    CALL_CHILD(ItemEvent_Support_NoEffect)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_Kameno_Noroi = {
    NULL, 0, // name..icon
    {0}, // pad_06
    178, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, // fastChance..fastTime
    100, // slowChance
    3, // slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Kameno_Noroi, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Cooked dishes that heal and also apply a status (Space Food, Icicle Pop, Snow Bunny, Love Pudding,
 * Peach Tart and others): heal as ItemEvent_Recovery, then apply the dish's weapon;
 * Love Pudding and Peach Tart pick one of three effects at random (40/40/20%).
 */
EVT_BEGIN(ItemEvent_RecoveryAndStatus)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(8))
    CALL(btlevtcmd_WeaponAftereffect, LW(8))
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(8))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(8), LW(10), LW(11))
    END_IF
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 60)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(8))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL_CHILD(ItemEvent_Recovery_Core_Effect)
    SWITCH(LW(9))
        CASE_EQUAL(216)
        CALL(evt_sub_random, 100, LW(0))
        IF_INT_LESS(LW(0), 40)
            SET_VALUE(LW(8), PTR(&ItemWeaponData_FirstLovePuddingBiribiri))
        ELSE
            IF_INT_LESS(LW(0), 80)
                SET_VALUE(LW(8), PTR(&ItemWeaponData_FirstLovePuddingTrans))
            ELSE
                SET_VALUE(LW(8), PTR(&ItemWeaponData_FirstLovePuddingSleep))
            END_IF
        END_IF
        CASE_EQUAL(226)
        CALL(evt_sub_random, 100, LW(0))
        IF_INT_LESS(LW(0), 40)
            SET_VALUE(LW(8), PTR(&ItemWeaponData_PeachTaltBiribiri))
        ELSE
            IF_INT_LESS(LW(0), 80)
                SET_VALUE(LW(8), PTR(&ItemWeaponData_PeachTaltDodge))
            ELSE
                SET_VALUE(LW(8), PTR(&ItemWeaponData_PeachTaltSleep))
            END_IF
        END_IF
        CASE_OR_EQUAL(233)
        CASE_OR_EQUAL(235)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_REST_CONDITION1"), LW(0), LW(1), LW(2), 0)
        CASE_END
    END_SWITCH
    SET_VALUE(LW(12), LW(8))
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    END_SWITCH
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_SpaceFood = {
    NULL, 0, // name..icon
    {0}, // pad_06
    198, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, // atkChangeStrength..defChangeStrength
    50, // allergicChance
    3, // allergicTime
    0, 0, 0, 0, 0, 0, 0, 0, // ohkoChance..galeForceChance
    0, 0, 0, 0, 0, 0, 0, 0, // paybackTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_IceCandy = {
    NULL, 0, // name..icon
    {0}, // pad_06
    199, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, // burnTime
    20, // freezeChance
    2, // freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_NancyFrappe = {
    NULL, 0, // name..icon
    {0}, // pad_06
    200, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, // burnTime
    20, // freezeChance
    2, // freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_SnowRabbit = {
    NULL, 0, // name..icon
    {0}, // pad_06
    201, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, // burnTime
    50, // freezeChance
    3, // freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_TeaKinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    212, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, // atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    -1, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, // frightChance..invisibleTime
    5, // hpRegenTime
    2, // hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_FirstLovePuddingBiribiri = {
    NULL, 0, // name..icon
    {0}, // pad_06
    216, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, // poisonStrength..confuseTime
    100, // electricChance
    2, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_FirstLovePuddingTrans = {
    NULL, 0, // name..icon
    {0}, // pad_06
    216, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    100, // invisibleChance
    2, // invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_FirstLovePuddingSleep = {
    NULL, 0, // name..icon
    {0}, // pad_06
    216, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    100, // sleepChance
    2, // sleepTime
    0, 0, 0, 0, 0, 0, 0, 0, // stopChance..confuseChance
    0, 0, 0, 0, 0, 0, 0, 0, // confuseTime..freezeChance
    0, 0, 0, 0, 0, 0, 0, 0, // freezeTime..defChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeTime..fastTime
    0, 0, 0, 0, 0, 0, 0, 0, // slowChance..invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_StarryDinner = {
    NULL, 0, // name..icon
    {0}, // pad_06
    217, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, // invisibleChance..invisibleTime
    3, // hpRegenTime
    2, // hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_KararinaPasta = {
    NULL, 0, // name..icon
    {0}, // pad_06
    224, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..ohkoChance
    1, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_MeromeroCake = {
    NULL, 0, // name..icon
    {0}, // pad_06
    225, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, // atkChangeStrength
    100, // defChangeChance
    3, // defChangeTime
    -1, // defChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // allergicChance..slowTime
    0, 0, 0, 0, 0, 0, 0, 0, // frightChance..hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_PeachTaltBiribiri = {
    NULL, 0, // name..icon
    {0}, // pad_06
    226, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, // poisonStrength..confuseTime
    100, // electricChance
    2, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_PeachTaltDodge = {
    NULL, 0, // name..icon
    {0}, // pad_06
    226, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, // poisonStrength..electricTime
    100, // dodgyChance
    2, // dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_PeachTaltSleep = {
    NULL, 0, // name..icon
    {0}, // pad_06
    226, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    100, // sleepChance
    2, // sleepTime
    0, 0, 0, 0, 0, 0, 0, 0, // stopChance..confuseChance
    0, 0, 0, 0, 0, 0, 0, 0, // confuseTime..freezeChance
    0, 0, 0, 0, 0, 0, 0, 0, // freezeTime..defChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeTime..fastTime
    0, 0, 0, 0, 0, 0, 0, 0, // slowChance..invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_BiribiriCandy = {
    NULL, 0, // name..icon
    {0}, // pad_06
    227, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, // poisonStrength..confuseTime
    100, // electricChance
    4, // electricTime
    0, 0, 0, 0, 0, 0, 0, 0, // dodgyChance..sizeChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeStrength..allergicChance
    0, 0, 0, 0, 0, 0, 0, 0, // allergicTime..frightChance
    0, 0, 0, 0, 0, 0, 0, 0, // galeForceChance..fpRegenTime
    0, // fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_HealthySalad = {
    NULL, 0, // name..icon
    {0}, // pad_06
    233, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    100, // sleepChance
    0, // sleepTime
    100, // stopChance
    0, // stopTime
    100, // dizzyChance
    0, // dizzyTime
    100, // poisonChance
    0, 0, // poisonTime..poisonStrength
    100, // confuseChance
    0, 0, 0, 0, 0, // confuseTime..dodgyTime
    100, // burnChance
    0, // burnTime
    100, // freezeChance
    0, // freezeTime
    100, // sizeChangeChance
    0, 0, 0, 0, 0, // sizeChangeTime..atkChangeStrength
    100, // defChangeChance
    0, 0, // defChangeTime..defChangeStrength
    100, // allergicChance
    0, 0, 0, 0, 0, // allergicTime..fastTime
    100, // slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_FreshJuice = {
    NULL, 0, // name..icon
    {0}, // pad_06
    235, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    100, // sleepChance
    0, // sleepTime
    100, // stopChance
    0, // stopTime
    100, // dizzyChance
    0, // dizzyTime
    100, // poisonChance
    0, 0, // poisonTime..poisonStrength
    100, // confuseChance
    0, 0, 0, 0, 0, // confuseTime..dodgyTime
    100, // burnChance
    0, // burnTime
    100, // freezeChance
    0, // freezeTime
    100, // sizeChangeChance
    0, 0, 0, 0, 0, // sizeChangeTime..atkChangeStrength
    100, // defChangeChance
    0, 0, // defChangeTime..defChangeStrength
    100, // allergicChance
    0, 0, 0, 0, 0, // allergicTime..fastTime
    100, // slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_RedKararing = {
    NULL, 0, // name..icon
    {0}, // pad_06
    173, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..ohkoChance
    1, // chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_FutarideForever = {
    NULL, 0, // name..icon
    {0}, // pad_06
    219, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, // invisibleChance..invisibleTime
    10, // hpRegenTime
    2, // hpRegenStrength
    0, 0, // fpRegenTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

#if VERSION <= VERSION_DEMO_US
// demo only: Fire Candy (item 228) still had battle data
BattleWeapon ItemWeaponData_FireCandy = {
    NULL, 0, // name..icon
    {0}, // pad_06
    228, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    1, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_RecoveryAndStatus, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

#endif
/**
 * Thrown cooked dishes (Zess Dynamite, Coconut Bomb, Egg Bomb and others):
 * the dish's icon is thrown in an arc at the target, which takes the dish's damage;
 * Zess Dynamite also shows fire pillars and the cook's ghostly image, the bombs explode.
 */
EVT_BEGIN(ItemEvent_ThrowAttack)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    WAIT_MS(1000)
    CALL(btlevtcmd_GetFriendBelong, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 40)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, -60, LW(1), LW(2), 0, -1, 0)
    END_IF
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(9))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), 52)
    CALL(btlevtcmd_CommandFlyItem, BTL_UNIT_SELF, 40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(9), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_CommandGetWeaponItemId, LW(9), LW(12))
    IF_INT_EQUAL(LW(9), 0)
        CALL(btlevtcmd_GetConsumeItem, LW(9))
    END_IF
    CALL(btlevtcmd_ConsumeItem, BTL_UNIT_SELF)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_CheckCommandUnit, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
        END_IF
        CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
    ELSE
        CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_GetSelectEnemy, LW(10), LW(11))
        ELSE
            CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
            CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), LW(12))
            CALL(btlevtcmd_ChoiceSamplingEnemy, LW(12), LW(10), LW(11))
        END_IF
    END_IF
    CALL(btlevtcmd_GetUnitKind, BTL_UNIT_SELF, LW(0))
    IF_INT_EQUAL(LW(0), 222)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_C_1"))
        BEGIN_SIBLING_EVENT
            WAIT_MS(500)
            CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
        END_SIBLING_EVENT
    END_IF
    CALL(btlevtcmd_CheckWeaponPluralTarget, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetHitPos, LW(10), LW(11), LW(5), LW(6), LW(7))
    ELSE
        CALL(btlevtcmd_GetFriendBelong, LW(10), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
            SET_VALUE(LW(5), -120)
        ELSE
            CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
            SET_VALUE(LW(5), 100)
        END_IF
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    END_IF
    CALL(_get_throw_first_pos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
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
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
    SWITCH(LW(5))
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(10), 38)
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(10), 39)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(10), 40)
        CASE_EQUAL(1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(10), LW(11), LW(12), 256, LW(5))
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
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_NancyDynamite = {
    NULL, 0, // name..icon
    {0}, // pad_06
    196, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    3, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_ThrowAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_CoconutsBomb = {
    NULL, 0, // name..icon
    {0}, // pad_06
    202, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    3, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_ThrowAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_KachikachiDish = {
    NULL, 0, // name..icon
    {0}, // pad_06
    203, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {4, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_ThrowAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

BattleWeapon ItemWeaponData_BomberEgg = {
    NULL, 0, // name..icon
    {0}, // pad_06
    209, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {6, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    3, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_ThrowAttack, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

/** Poison Shroom: 80% of the time the target is poisoned; otherwise the target's HP is fully restored. */
EVT_BEGIN(ItemEvent_Poison_Kinoko)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_PoisonKinoko))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(evt_sub_random, 100, LW(0))
    IF_INT_LESS(LW(0), 80)
        CALL_CHILD(ItemEvent_Support_Sub_Effect)
    ELSE
        CALL_CHILD(ItemEvent_GetTarget)
        CALL(evt_btl_camera_set_homing_unit, 0, LW(10), BTL_UNIT_NONE)
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
    // the original script has one END_IF too many; the interpreter ignores it
    END_IF
    CALL(evt_audience_ap_recovery)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_PoisonKinoko = {
    NULL, 0, // name..icon
    {0}, // pad_06
    213, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerHPHalf2, // hpDamageFn
    {7, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, // sleepChance..dizzyTime
    100, // poisonChance
    3, // poisonTime
    1, // poisonStrength
    0, 0, 0, 0, 0, 0, 0, 0, // confuseChance..burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_Poison_Kinoko, // attackEvtScript
    {0, 0, 0, 100, 0, 5, 5, 5, 5, 0, 0, 0}, // stageEffectRates
};

// _nancy_mirage keeps x/y/z as three s32 words from userdata3 on (over wInterpRelatedTime)
#define EVT_XYZ(evt) ((s32*)&(evt)->userdata3)

typedef struct ThrowWork {
    Vec start;                   // 0x0
    Vec pos;                     // 0xC
    Vec target;                  // 0x18
    s32 frames;                  // 0x24
    f32 speed;                   // 0x28
    f32 gravity;                 // 0x2C
    f32 vy;                      // 0x30
    u8 reserved_34[0x7C - 0x34]; // 0x34, never accessed (keeps the 0x7C-byte BattleAlloc)
} ThrowWork;

/**
 * Picks a random target of weapon args[0] among the alliance args[3]'s opponents
 * and returns it in args[1] (unit) and args[2] (part), or -1 and -1 if there is none.
 * Used by Shooting Star's falling stars.
 */
static USER_FUNC(_sampling_random_target) {
    BattleWorkWeaponTargets targets;
    BattleWork* wp;
    BattleWeapon* weapon;
    EvtWord* args;
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

/** Spins the 3D camera's roll from 720 degrees back to 0 over two seconds, for Dizzy Dial. */
static USER_FUNC(_cam_rot) {
    f32 rot;

    if (isFirstCall) {
        event->userdata[0] = sysMsec2Frame(2000);
        event->userdata[1] = event->userdata[0];
    }
    rot = intplGetValue(4, 720.0f, 0.0f, event->userdata[0], event->userdata[1]);
    camGetPtr(CAMERA_3D)->rollAngle = rot;
    event->userdata[0]--;
    if (event->userdata[0] <= 0) {
        camGetPtr(CAMERA_3D)->rollAngle = 0.0f;
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

/** Raises unit args[0]'s level by 5 (at most 99), for Trade Off. */
static USER_FUNC(_rank_up) {
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));

    if (unit) {
        unit->level += 5;
        if (unit->level > 99) {
            unit->level = 99;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Opens the battle status window when unit args[0] is Mario or a partner,
 * before Point Swap changes their HP and FP.
 */
static USER_FUNC(_hpfp_change_declare_1) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (unit) {
        if (unit->currentKind == UNIT_MARIO) {
            BattleStatusWindowSystemOn();
        } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
            BattleStatusWindowSystemOn();
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Blinks the HP and FP readouts for 120 frames when unit args[0] is Mario or a partner, after Point Swap.
 * The JP and later releases clear any earlier blink first.
 */
static USER_FUNC(_hpfp_change_declare_2) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (unit) {
        if (unit->currentKind == UNIT_MARIO) {
#if VERSION >= VERSION_JP
            N_statusClearBlink();
#endif
            statusMarioHPBlink(120);
            statusFPBlink(120);
        } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
#if VERSION >= VERSION_JP
            N_statusClearBlink();
#endif
            statusPartyHPBlink(120);
            statusFPBlink(120);
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Runs Mystery's roulette over unit args[0]: picks a random item from _item_table,
 * starts the roulette effect showing it and returns the item id in args[1];
 * waits until the roulette effect is gone.
 * The JP and later releases also count the item in the battle's attack or support item record.
 */
static USER_FUNC(_naniga_okorukana_check) {
    Vec pos;
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];
    BattleUnit* unit;
    s32 item;
    s32 i;
    u8* a;
    u8* b;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    if (!(unit->attributeFlags & UNIT_ATTR_VEILED)) {
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            pos.y -= 5.0f;
        } else {
            pos.y += BtlUnit_GetHeight(unit) + 20;
        }
    }
    if (isFirstCall) {
        for (i = 0; _item_table[i] != 0; i++) {
        }
        item = _item_table[irand(i)];
        event->userdata[0] = (EvtWord)effNanigaEntry(0, _item_table, item, pos.x, pos.y, pos.z);
        effSetName((EffectEntry*)event->userdata[0], "effNaniga");
        evtSetValue(event, out, item);
#if VERSION >= VERSION_JP
        if (unit->currentKind == UNIT_MARIO) {
            a = &wp->actRecord.marioAttackItems;
            b = &wp->actRecord.marioSupportItems;
        } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
            a = &wp->actRecord.partnerAttackItems;
            b = &wp->actRecord.partnerSupportItems;
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
#endif
    }
#if VERSION >= VERSION_JP
end:
#endif
    if (effNameToPtr("effNaniga")) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

/** Returns in args[1..3] where a thrown item starts: just above unit args[0]'s head (just below for ceiling units). */
static USER_FUNC(_get_throw_first_pos) {
    BattleUnit* unit;
    Vec pos;
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 ox = args[1];
    s32 oy = args[2];
    s32 oz = args[3];

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.y += 10.0f;
    if (!(unit->attributeFlags & UNIT_ATTR_VEILED)) {
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            pos.y -= 5.0f;
        } else {
            pos.y += unit->sizeMultiplier * BtlUnit_GetHeight(unit);
        }
    }
    evtSetFloat(event, ox, pos.x);
    evtSetFloat(event, oy, pos.y);
    evtSetFloat(event, oz, pos.z);
    return EVT_RETURN_DONE;
}

/**
 * Throws the icon of item args[0] from args[1..3] to args[4..6] in an arc (a few frames longer the farther it
 * goes), with the throwing sound; finishes when it lands.
 */
static USER_FUNC(_throw_item_icon) {
    EvtWord* args = event->args;
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
        event->userdatap[0] = BattleAlloc(sizeof(ThrowWork));
        wk = event->userdatap[0];
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
        event->userdata3 = psndSFXOn_3D("SFX_ITEM_COOKING_THROW1", &v);
    }
    wk = event->userdatap[0];
    if (event->userdata[2]) {
        psndSFXOff(event->userdata3);
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

/** Draws the thrown item's icon at its current position. */
static void _disp_item_icon(CameraId cameraId, void* param) {
    EventEntry* event = param;
    iconDispGx(&((ThrowWork*)event->userdatap[0])->pos, 0, itemDataTable[event->userdata[1]].icon_id, 1.0f);
}

/**
 * Shows the cook's ghostly image (c_cook) at args[0..2] for 60 frames, fading and growing in the last 30,
 * for Zess Dynamite.
 */
static USER_FUNC(_nancy_mirage) {
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    if (isFirstCall) {
        event->userdata[0] = 60;
        event->userdata[1] = animPoseEntry("c_cook", 1);
        event->userdata[2] = 0;
        EVT_XYZ(event)
        [0] = x;
        EVT_XYZ(event)
        [1] = y;
        EVT_XYZ(event)
        [2] = z;
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

/** Draws the cook's image for _nancy_mirage, scaled up and translucent as it fades. */
static void _nancy_disp(CameraId cameraId, void* param) {
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
    PSMTXTrans(trans, EVT_XYZ(event)[0], EVT_XYZ(event)[1], EVT_XYZ(event)[2]);
    PSMTXScale(scale, s, s, 1.0f);
    PSMTXIdentity(mtx);
    PSMTXConcat(scale, mtx, mtx);
    PSMTXConcat(trans, mtx, mtx);
    animPoseSetMaterialEvtColor(event->userdata[1], (GXColor){0xFF, 0xFF, 0xFF, alpha});
    animPoseSetMaterialFlagOn(event->userdata[1], ANIM_MATERIAL_FLAG_EVT_COLOR);
    animPoseDrawMtx(event->userdata[1], mtx, 1, 0.0f, 2.0f);
    animPoseDrawMtx(event->userdata[1], mtx, 2, 0.0f, 2.0f);
    animPoseDrawMtx(event->userdata[1], mtx, 3, 0.0f, 2.0f);
}

/** Fills the party's Star Power when unit args[0] is on the player's side, for Trial Stew. */
static USER_FUNC(_full_ap_recover) {
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, event->args[0]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));

    if (BtlUnit_GetBelong(unit) == 0) {
        pouchSetAP(pouchGetMaxAP());
    }
    return EVT_RETURN_DONE;
}

/**
 * Trial Stew: a dark cloud over the target, then its HP drops to 1,
 * its FP to 0 and the party's Star Power fills;
 * the demos play the cooking sound once, the releases after each hit.
 */
EVT_BEGIN(ItemEvent_LastDinner)
    SET_VALUE(LW(12), PTR(&ItemWeaponData_PoisonKinoko))
    CALL_CHILD(ItemEvent_Support_Sub_UseDeclere)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL_CHILD(ItemEvent_GetTarget)
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
    // Two copies: the demos play the cooking sound once before the hits; the releases play it after each hit.
#if VERSION <= VERSION_DEMO_US
    CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_COOK_LAST3"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff, 0, STRING("indirect"), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, 0, STRING("hit"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 1, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 2, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
    WAIT_MS(250)
    CALL(evt_eff, 0, STRING("hit"), 3, LW(0), LW(1), LW(2), FLOAT(1.0f), 3, 0, 0, 0, 0, 0, 0)
#else
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
#endif
    WAIT_MS(1750)
    CALL(evt_audience_ap_recovery)
    CALL_CHILD(_return_home_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

BattleWeapon ItemWeaponData_LastDinner = {
    NULL, 0, // name..icon
    {0}, // pad_06
    218, // itemId
    NULL, // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_IGNORE_STATUS_VULNERABILITY | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    ItemEvent_LastDinner, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};
