#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
static USER_FUNC(_get_mario_hammer_lv);
#include "driver/animdrv.h"
#include "driver/effdrv.h"
#include "eff/eff_energy.h"
#include "eff/eff_hibashira.h"
#include "eff/eff_majinai.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "system.h"
#include "pmario_sound.h"

extern BattleWork* _battleWorkPointer;
EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 duration);
void BattleMajinaiDone(void);
void BattleMajinaiEndCheck(void);
void BattleAudience_Case_JumpNewRecord(void);
void BtlUnit_SetAnim(BattleUnitPart* part, s32 anim);
EffectEntry* effWhirlwindN64Entry(s32 a, s32 b, s32 c, f32 scale);
void BtlUnit_SetPos(BattleUnit* unit, f32 x, f32 y, f32 z);
f32 sinfd(f32);
f32 cosfd(f32);

#include "battle/battle_unit.h"
static USER_FUNC(_get_mario_hammer_lv);


USER_FUNC(_battle_majinai_effect);
USER_FUNC(_majinai_powerup_check);
USER_FUNC(btlevtcmd_ACSuccessEffect);
USER_FUNC(btlevtcmd_AddPartsRotate);
USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePoseType);
USER_FUNC(btlevtcmd_AnnounceMessage);
USER_FUNC(btlevtcmd_AudienceDeclareACResult);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CommandCheckDamage);
USER_FUNC(btlevtcmd_CommandGetWeaponAddress);
USER_FUNC(btlevtcmd_FaceDirectionAdd);
USER_FUNC(btlevtcmd_GetBodyId);
USER_FUNC(btlevtcmd_GetDamage);
USER_FUNC(btlevtcmd_GetHeight);
USER_FUNC(btlevtcmd_GetHitPos);
USER_FUNC(btlevtcmd_GetPartsPos);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetResultAC);
USER_FUNC(btlevtcmd_GetResultPrizeLv);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_JumpPartsContinue);
USER_FUNC(btlevtcmd_JumpPartsPosition);
USER_FUNC(btlevtcmd_JumpPartsSetting);
USER_FUNC(btlevtcmd_JumpPosition);
USER_FUNC(btlevtcmd_OffPartsAttribute);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_RunDataEventChild);
USER_FUNC(btlevtcmd_SetFallAccel);
USER_FUNC(btlevtcmd_SetPartsPos);
USER_FUNC(btlevtcmd_SetPartsRotate);
USER_FUNC(btlevtcmd_SetPartsRotateOffset);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_StopAC);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(evt_btl_camera_off_posoffset_manual);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_btl_camera_set_moveSpeedLv);
USER_FUNC(evt_btl_camera_set_zoom);
USER_FUNC(evt_btl_camera_shake_h);
USER_FUNC(evt_eff64);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(_paper_light_off);
USER_FUNC(_fire_wave);
USER_FUNC(_mario_fire_ball_controll);
USER_FUNC(_kaiten_hammer_acrobat_rotate);
USER_FUNC(_hammer_star_effect);
USER_FUNC(mario_get_renzoku_count_max);
USER_FUNC(_record_renzoku_count);
USER_FUNC(_tatsumaki_effect);
USER_FUNC(_wait_jyabara_hit_iron_frame);
USER_FUNC(_bgset_iron_frame_check);
USER_FUNC(_jump_star_effect);
USER_FUNC(_whirlwind_effect);
extern s32 btldefaultevt_SuitoruBadgeEffect[];
extern s32 btlevtcmd_ACHelpSet[];
extern s32 btlevtcmd_ACRGetResult[];
extern s32 btlevtcmd_ACRStart[];
extern s32 btlevtcmd_AcGetDifficulty[];
extern s32 btlevtcmd_AcGetOutputParam[];
extern s32 btlevtcmd_AcSetDifficulty[];
extern s32 btlevtcmd_AcSetFlag[];
extern s32 btlevtcmd_AcSetParamAll[];
extern s32 btlevtcmd_AnimeChangePaperAnime[];
extern s32 btlevtcmd_AnimeChangePaperGroup[];
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeWaitPlayComplete[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_AttackDeclareAll[];
extern s32 btlevtcmd_AudienceDeclareAcrobatResult[];
extern s32 btlevtcmd_CalculateFaceDirection[];
extern s32 btlevtcmd_ChangeFaceDirection[];
extern s32 btlevtcmd_CheckToken[];
extern s32 btlevtcmd_CommandGetWeaponActionLv[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_CommandPreCheckDamage[];
extern s32 btlevtcmd_DamageDirect[];
extern s32 btlevtcmd_DivePartsPosition[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_FaceDirectionSub[];
extern s32 btlevtcmd_FallPartsPosition[];
extern s32 btlevtcmd_FallPosition[];
extern s32 btlevtcmd_GetEnemyBelong[];
extern s32 btlevtcmd_GetFaceDirection[];
extern s32 btlevtcmd_GetFirstAttackTarget[];
extern s32 btlevtcmd_GetFriendBelong[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetMoveFrame[];
extern s32 btlevtcmd_GetResultCountAC[];
extern s32 btlevtcmd_GetRotate[];
extern s32 btlevtcmd_GetScale[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetSelectNextEnemy[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetTakeoffPosition[];
extern s32 btlevtcmd_GetUnitWork[];
extern s32 btlevtcmd_GetWeaponActionLv[];
extern s32 btlevtcmd_InviteApInfoReport[];
extern s32 btlevtcmd_JumpContinue[];
extern s32 btlevtcmd_JumpSetting[];
extern s32 btlevtcmd_MarioJumpParam[];
extern s32 btlevtcmd_MarioJumpPosition[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OffToken[];
extern s32 btlevtcmd_PadCheckNow[];
extern s32 btlevtcmd_PreCheckDamage[];
extern s32 btlevtcmd_ResetFaceDirection[];
extern s32 btlevtcmd_ResultAC[];
extern s32 btlevtcmd_SamplingEnemy[];
extern s32 btlevtcmd_SetMoveSoundDataWork[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsBlur[];
extern s32 btlevtcmd_SetPartsWork[];
extern s32 btlevtcmd_SetPos[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_SetScale[];
extern s32 btlevtcmd_SetUnitWork[];
extern s32 btlevtcmd_SetupAC[];
extern s32 btlevtcmd_StartAC[];
extern s32 btlevtcmd_TransStageFloorPosition[];
extern s32 btlevtcmd_WaitEventEnd[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_ac_timing_flag_onoff[];
extern s32 btlevtcmd_ac_timing_get_success_frame[];
extern s32 btlevtcmd_check_battleflag[];
extern s32 btlevtcmd_ftof[];
extern s32 btlevtcmd_ftomsec[];
extern s32 btlevtcmd_snd_se[];
extern s32 btlevtcmd_snd_voice[];
extern s32 evt_audience_acrobat_notry[];
extern s32 evt_audience_ap_recovery[];
extern s32 evt_audience_reflesh_natural_all[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_homing_unitparts[];
extern s32 evt_btl_camera_set_posoffset[];
extern s32 evt_btl_camera_set_zoomSpeedLv[];
extern s32 evt_eff[];
extern s32 evt_majinai_effect_se_btl[];
extern s32 evt_snd_sfx_pit[];
extern s32 evt_snd_sfx_pos[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_sub_intpl_get_float[];
extern s32 evt_sub_intpl_get_value[];
extern s32 evt_sub_intpl_init[];
extern s32 evt_sub_intpl_init_float[];
extern s32 evt_sub_random[];
extern s32 marioAttackEvent_BakuGame[];
extern s32 marioAttackEvent_Deka[];
extern s32 marioAttackEvent_Genki0[];
extern s32 marioAttackEvent_Genki1[];
extern s32 marioAttackEvent_Muki[];
extern s32 marioAttackEvent_Scissor[];
extern s32 marioAttackEvent_Suki[];
extern s32 marioAttackEvent_ZubaStar[];
extern s32 weaponGetPowerDefault[];
extern s32 weaponGetPowerFromMarioHammerLv[];
extern s32 weaponGetPowerFromMarioJumpLv[];
extern s32 weaponGetPowerOverlapHammer1[];
extern s32 weaponGetPowerOverlapJump1[];
extern s32 weaponGetPowerTatsumaki[];
extern s32 weaponGetPower_Deka[];
extern s32 weaponGetPower_Scissor[];
extern s32 weaponGetPower_ZubaStar[];

s32 marioDefaultWeapon_Jump[48];
s32 marioWeapon_KururinJump[48];
s32 marioWeapon_KururinJump2[48];
s32 marioWeapon_JyabaraJump[48];
s32 marioWeapon_JyabaraJumpFailed[48];
s32 marioDefaultWeapon_FirstAttackKaitenHammer[48];
s32 marioDefaultWeapon_FirstAttackUltraHammer[48];
s32 marioDefaultWeapon_Hammer[48];
s32 marioWeapon_KaitenHammer[48];
s32 marioWeapon_KaitenHammerInvolved[48];
s32 marioWeapon_UltraHammer[48];
s32 marioWeapon_UltraHammerInvolved[48];
s32 marioWeapon_UltraHammerFinish[48];
s32 badgeWeapon_TugitugiJump[48];
s32 badgeWeapon_GatsunJump[48];
s32 badgeWeapon_DokanJump[48];
s32 badgeWeapon_RenzokuJump[48];
s32 badgeWeapon_TatsumakiJump[48];
s32 badgeWeapon_TatsumakiJumpInvolved[48];
s32 badgeWeapon_MiniminiFumi[48];
s32 badgeWeapon_NemuraseFumi[48];
s32 badgeWeapon_FunyafunyaJump[48];
s32 badgeWeapon_GatsunHammer[48];
s32 badgeWeapon_DokanHammer[48];
s32 badgeWeapon_JishinHammer[48];
s32 badgeWeapon_UltraJishinHammer[48];
s32 badgeWeapon_HammerNageru[48];
s32 badgeWeapon_TsuranukiNaguri[48];
s32 badgeWeapon_ConfuseHammer[48];
s32 badgeWeapon_FireNaguri[48];
s32 badgeWeapon_FireNaguriFailed[48];
s32 badgeWeapon_IceNaguri[48];
s32 badgeWeapon_Charge[48];
s32 badgeWeapon_ChargeP[48];
s32 badgeWeapon_SuperCharge[48];
s32 badgeWeapon_SuperChargeP[48];
s32 badgeWeapon_2KaiItem[48];
s32 badgeWeapon_3KaiItem[48];
s32 badgeWeapon_DefenceCommand[48];
s32 badgeWeapon_DefenceCommandP[48];
s32 marioWeapon_BakuGame[48];
s32 marioWeapon_Scissor[48];
s32 marioWeapon_ZubaStar[48];
s32 marioWeapon_Genki0[48];
s32 marioWeapon_Genki1[48];
s32 marioWeapon_Deka[48];
s32 marioWeapon_Muki[48];
s32 marioWeapon_Suki[48];
s32 superActionTable[18];
static s32 marioAttackEvent_NormalJump[889];
static s32 marioAttackEvent_KururinJump[1210];
s32 marioAttackEvent_JyabaraJump[1675];
s32 marioAttackEvent_GatsuDokaJump[624];
s32 marioAttackEvent_TatsumakiJump[1668];
s32 marioAttackEvent_RenzokuJump[840];
s32 marioAttackEvent_TugiTugiJump[793];
s32 marioAttackEvent_NormalHammer_Core[1326];
static s32 marioAttackEvent_KaitenHammer[1060];
s32 marioAttackEvent_FirstAttackKaitenHammer[19];
s32 marioAttackEvent_JishinHammer[834];
s32 marioAttackEvent_UltraJishinHammer[665];
s32 marioAttackEvent_HammerRotate[25];
s32 marioAttackEvent_HammerNageru[446];
s32 marioAttackEvent_HammerNageru_object[240];
s32 marioAttackEvent_FireNaguri[702];
s32 marioAttackEvent_FireNaguri_object[374];
s32 _NormalCharge_core[103];
s32 _SuperCharge_core[103];
s32 marioAttackEvent_GatsunJump[7];
s32 marioAttackEvent_DokanJump[7];
s32 marioAttackEvent_MiniminiFumi[4];
s32 marioAttackEvent_NemuraseFumi[4];
s32 marioAttackEvent_FunyafunyaJump[4];
static s32 marioAttackEvent_NormalHammer[7];
s32 marioAttackEvent_GatsunHammer[7];
s32 marioAttackEvent_IceNaguri[7];
s32 marioAttackEvent_TsuranukiHammer[7];
s32 marioAttackEvent_NormalCharge[7];
s32 marioAttackEvent_NormalChargeP[7];
s32 marioAttackEvent_SuperCharge[7];
s32 marioAttackEvent_SuperChargeP[7];
s32 marioAttackEvent_MajinaiPowerUpCheck[35];
s32 marioAttackEvent_MajinaiJump[43];
s32 _MajinaiPoseReset[14];
s32 marioAttackEvent_MajinaiDefenceUp[29];
s32 marioAttackEvent_MajinaiExpUp[27];

s32 marioDefaultWeapon_Jump[] = {
    (s32)"btl_wn_mario_normal_jump", 10420224, 0, (s32)"msg_normal_jump", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 219143, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_NormalJump, 100, 131585, 16777216,
};

s32 marioWeapon_KururinJump[] = {
    (s32)"btl_wn_mario_kururin_jump", 10551296, 0, (s32)"msg_kururin_jump", 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_k_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_KururinJump, 100, 132353, 16777216,
};


s32 marioWeapon_KururinJump2[] = {
    (s32)"btl_wn_mario_kururin_jump", 10551296, 0, (s32)"msg_kururin_jump", 1677721600, 1065353216, 17130546, (s32)weaponGetPowerFromMarioJumpLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_k_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_KururinJump, 329060, 657925, 84213760,
};

s32 marioWeapon_JyabaraJump[] = {
    (s32)"btl_wn_mario_jyabara_jump", 10485760, 0, (s32)"msg_jyabara_jump", 1677983744, 1065353216, 33907762, (s32)weaponGetPowerFromMarioJumpLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_j_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_JyabaraJump, 329060, 657925, 84213760,
};

s32 marioWeapon_JyabaraJumpFailed[] = {
    (s32)"btl_wn_mario_jyabara_jump", 10485760, 0, (s32)"msg_jyabara_jump", 1677983744, 1065353216, 33882418, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, 0, 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_JyabaraJump, 3289700, 50, 0,
};

s32 marioDefaultWeapon_FirstAttackKaitenHammer[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 918274, 0, 133255, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_FirstAttackKaitenHammer, 100, 0, 0,
};

s32 marioDefaultWeapon_FirstAttackUltraHammer[] = {
    0, 0, 0, 0, 1677721600, 1065353216, 16843009, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 553656320, 1049346, 0, 133255, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_FirstAttackKaitenHammer, 100, 0, 0,
};

s32 marioDefaultWeapon_Hammer[] = {
    (s32)"btl_wn_mario_normal_hammer", 10223616, 0, (s32)"msg_normal_hammer", 1677721600, 1065353216, 16868402, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 198791, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_NormalHammer, 197476, 50528771, 50331648,
};

s32 marioWeapon_KaitenHammer[] = {
    (s32)"btl_wn_mario_kaiten_hammer", 10289152, 0, (s32)"msg_kaiten_hammer", 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 918274, (s32)"msg_ac_kaiten_hammer", 133255, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_KaitenHammer, 100, 197888, 0,
};

s32 marioWeapon_KaitenHammerInvolved[] = {
    0, 0, 0, 0, 1677721600, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 537927680, 983810, 0, 131136, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 marioWeapon_UltraHammer[] = {
    (s32)"btl_wn_mario_ultra_hammer", 10354688, 0, (s32)"msg_ultra_hammer", 1677983744, 1065353216, 33907762, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 1049346, (s32)"msg_ac_ultra_hammer", 133127, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_KaitenHammer, 100, 197888, 0,
};

s32 marioWeapon_UltraHammerInvolved[] = {
    0, 0, 0, 0, 1677721600, 0, 0, (s32)weaponGetPowerDefault,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 537927680, 1114882, 0, 131136, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 marioWeapon_UltraHammerFinish[] = {
    (s32)"btl_wn_mario_ultra_hammer", 10354688, 0, (s32)"msg_ultra_hammer", 1677721600, 1065353216, 33907762, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17825888, 536870912, 1245954, 0, 133263, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_KaitenHammer, 100, 0, 327680,
};

s32 badgeWeapon_TugitugiJump[] = {
    0, 0, 241, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerOverlapJump1,
    0, 0, 1, 1, 2, 2, 241, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_TugiTugiJump, 100, 328962, 33554432,
};

s32 badgeWeapon_GatsunJump[] = {
    0, 0, 240, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerOverlapJump1,
    1, 2, 2, 4, 3, 6, 240, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_GatsunJump, 1644900, 421075205, 419758080,
};

s32 badgeWeapon_DokanJump[] = {
    0, 0, 332, 0, 1678114816, 1065353216, 17130546, (s32)weaponGetPowerOverlapJump1,
    1, 2, 2, 4, 3, 6, 332, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_DokanJump, 1644900, 419759365, 84213760,
};

s32 badgeWeapon_RenzokuJump[] = {
    0, 0, 242, 0, 1677918208, 1065353216, 17130546, (s32)weaponGetPowerOverlapJump1,
    0, 0, 1, 1, 2, 2, 242, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153623, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_RenzokuJump, 100, 328962, 33554432,
};

s32 badgeWeapon_TatsumakiJump[] = {
    0, 0, 243, 0, 1677918208, 1065353216, 50684978, (s32)weaponGetPowerOverlapJump1,
    0, 1, 1, 3, 2, 5, 243, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_tatsumaki_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_TatsumakiJump, 100, 0, 0,
};

s32 badgeWeapon_TatsumakiJumpInvolved[] = {
    0, 0, 0, 0, 1677721600, 0, 0, (s32)weaponGetPowerTatsumaki,
    0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870928, 770, 0, 131136, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 badgeWeapon_MiniminiFumi[] = {
    0, 0, 244, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 100, 66977792, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_MiniminiFumi, 100, 197889, 16777216,
};

s32 badgeWeapon_NemuraseFumi[] = {
    0, 0, 245, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    1678049280, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_NemuraseFumi, 100, 197889, 16777216,
};

s32 badgeWeapon_FunyafunyaJump[] = {
    0, 0, 246, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioJumpLv,
    1, 1, 2, 2, 3, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536875012, 770, (s32)"msg_ac_jump", 153607, 12, -2147475452,
    0, 0, 0, 0, 0, 0, 6554621, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_FunyafunyaJump, 100, 197889, 16777216,
};

s32 badgeWeapon_GatsunHammer[] = {
    0, 0, 247, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerOverlapHammer1,
    1, 2, 2, 4, 3, 6, 247, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 133255, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_GatsunHammer, 1644900, 421075205, 419758080,
};

s32 badgeWeapon_DokanHammer[] = {
    0, 0, 333, 0, 1678114816, 1065353216, 17130546, (s32)weaponGetPowerOverlapHammer1,
    1, 2, 2, 4, 3, 6, 333, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 133255, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_GatsunHammer, 1644900, 419759365, 84213760,
};

s32 badgeWeapon_JishinHammer[] = {
    0, 0, 248, 0, 1677918208, 1065353216, 33907762, (s32)weaponGetPowerOverlapHammer1,
    -1, 0, -1, 0, -1, 0, 248, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870920, 770, (s32)"msg_ac_hammer", 145607, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_JishinHammer, 3289700, 840505605, 419758080,
};

s32 badgeWeapon_UltraJishinHammer[] = {
    0, 0, 334, (s32)"msg_ultra_attack", 1678180352, 1065353216, 17130546, (s32)weaponGetPowerOverlapHammer1,
    3, 6, 3, 6, 3, 6, 334, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870920, 770, (s32)"msg_ac_ultra_jishin_hammer", 145607, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_UltraJishinHammer, 3289700, 839189765, 84213760,
};

s32 badgeWeapon_HammerNageru[] = {
    0, 0, 249, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerOverlapHammer1,
    0, 1, 1, 3, 2, 5, 249, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 536870912, 770, (s32)"msg_ac_hammer_nageru", 133255, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_HammerNageru, 100, 0, 0,
};

s32 badgeWeapon_TsuranukiNaguri[] = {
    0, 0, 250, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 133319, 2043, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_TsuranukiHammer, 1644900, 328965, 84213760,
};

s32 badgeWeapon_ConfuseHammer[] = {
    0, 0, 251, 0, 1677852672, 1065353216, 17130546, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 770, (s32)"msg_ac_hammer", 133255, 2043, -2147475452,
    0, 0, 6554368, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_NormalHammer, 329060, 328965, 84213760,
};

s32 badgeWeapon_FireNaguri[] = {
    0, 0, 252, 0, 1678049280, 1065353216, 33907762, (s32)weaponGetPowerOverlapHammer1,
    -1, 3, 0, 3, 1, 3, 252, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 33559136, 536879104, 16777986, (s32)"msg_ac_fire_naguri", 133223, 2047, -2147475452,
    0, 0, 0, 100, 50331648, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_FireNaguri, 100, 328965, 84213760,
};

s32 badgeWeapon_FireNaguriFailed[] = {
    0, 0, 252, 0, 1678049280, 1065353216, 33882418, (s32)weaponGetPowerFromMarioHammerLv,
    1, 5, 2, 5, 3, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603360, 268443648, 16777986, 0, 131079, 2047, -2147475452,
    0, 0, 0, 100, 50331648, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_FireNaguri, 100, 328965, 84213760,
};

s32 badgeWeapon_IceNaguri[] = {
    0, 0, 253, 0, 1677918208, 1065353216, 17130546, (s32)weaponGetPowerFromMarioHammerLv,
    1, 2, 2, 4, 3, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16781920, 553656320, 33555202, (s32)"msg_ac_hammer", 133127, 2043, -2147475452,
    0, 0, 0, 0, 6554112, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_IceNaguri, 329060, 328965, 84213760,
};

s32 badgeWeapon_Charge[] = {
    (s32)"btl_wn_mario_normal_charge", 10420224, 256, (s32)"btl_hlp_cmd_operation_charge", 1677787136, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, (s32)marioAttackEvent_NormalCharge, 100, 0, 0,
};

s32 badgeWeapon_ChargeP[] = {
    (s32)"btl_wn_mario_normal_charge", 10420224, 257, (s32)"btl_hlp_cmd_operation_charge", 1677787136, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, (s32)marioAttackEvent_NormalChargeP, 100, 0, 0,
};

s32 badgeWeapon_SuperCharge[] = {
    (s32)"btl_wn_mario_super_charge", 10420224, 337, (s32)"btl_hlp_cmd_operation_super_charge", 1677852672, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, (s32)marioAttackEvent_SuperCharge, 100, 0, 0,
};

s32 badgeWeapon_SuperChargeP[] = {
    (s32)"btl_wn_mario_super_charge", 10420224, 338, (s32)"btl_hlp_cmd_operation_super_charge", 1677852672, 1065353216, 16843009, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, (s32)marioAttackEvent_SuperChargeP, 100, 0, 0,
};

s32 badgeWeapon_2KaiItem[] = {
    (s32)"btl_wn_2kai_item", 0, 254, 0, 1677983744, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 badgeWeapon_3KaiItem[] = {
    (s32)"btl_wn_3kai_item", 0, 329, 0, 1678245888, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131336, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 badgeWeapon_DefenceCommand[] = {
    0, 0, 335, 0, 1677721600, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131080, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 6553857, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 badgeWeapon_DefenceCommandP[] = {
    0, 0, 336, 0, 1677721600, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 16793632, 268435456, 770, 0, 131080, 2047, -2147475452,
    0, 0, 0, 0, 0, 0, 6553857, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 marioWeapon_BakuGame[] = {
    (s32)"btl_wn_sac_bakugame", 26738688, 0, (s32)"msg_bakugame", 1677722112, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 536870912, 770, (s32)"msg_sac_3", 131208, 2047, 0,
    25601, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_BakuGame, 100, 0, 0,
};

s32 marioWeapon_Scissor[] = {
    (s32)"btl_wn_sac_scissor", 27000832, 0, (s32)"msg_scissor", 1677722624, 1065353216, 17130546, (s32)weaponGetPower_Scissor,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_sac_5", 131272, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Scissor, 100, 0, 0,
};

s32 marioWeapon_ZubaStar[] = {
    (s32)"btl_wn_sac_zubastar", 26935296, 0, (s32)"msg_zubastar", 1677723136, 1065353216, 17130546, (s32)weaponGetPower_ZubaStar,
    0, 3, 6, 9, 12, 15, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_sac_8", 131272, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_ZubaStar, 100, 0, 0,
};

s32 marioWeapon_Genki0[] = {
    (s32)"btl_wn_sac_genki0", 19988480, 0, (s32)"msg_genkigenki", 1677721856, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603120, 268435456, 770, (s32)"msg_sac_1", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Genki0, 100, 0, 0,
};

s32 marioWeapon_Genki1[] = {
    (s32)"btl_wn_sac_genki1", 27066368, 0, (s32)"msg_super_genki", 1677722880, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603120, 268435456, 770, (s32)"msg_sac_6", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Genki1, 100, 0, 0,
};

s32 marioWeapon_Deka[] = {
    (s32)"btl_wn_sac_dekkaku_dokkan", 26673152, 0, (s32)"msg_dekkaku_dokkan", 1677722112, 1065353216, 17130546, (s32)weaponGetPower_Deka,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_sac_2", 131272, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Deka, 100, 0, 0,
};

s32 marioWeapon_Muki[] = {
    (s32)"btl_wn_sac_mukimuki_body", 26869760, 0, (s32)"msg_mukimuki_body", 1677722368, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603120, 268435456, 770, (s32)"msg_sac_4", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Muki, 100, 0, 0,
};

s32 marioWeapon_Suki[] = {
    (s32)"btl_wn_sac_sukkari_sukkiri", 26804224, 0, (s32)"msg_sukkari_sukkiri", 1677722112, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34607712, 536870912, 770, (s32)"msg_sac_7", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 25600,
    0, 0, 0, 0, (s32)marioAttackEvent_Suki, 100, 0, 0,
};

s32 superActionTable[] = {
    (s32)marioWeapon_Genki0, (s32)marioWeapon_Deka, (s32)marioWeapon_BakuGame, (s32)marioWeapon_Muki, (s32)marioWeapon_Scissor, (s32)marioWeapon_Genki1, (s32)marioWeapon_Suki, (s32)marioWeapon_ZubaStar,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

static s32 marioAttackEvent_NormalJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_check_battleflag,
    -30000000, 2, 131097, -30000000, 0, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 131122,
    -29999988, (s32)marioDefaultWeapon_Jump, 131163, (s32)btlevtcmd_ACHelpSet, (s32)marioDefaultWeapon_Jump, 196699, (s32)evt_btl_camera_set_mode, 0,
    10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -29999997, -29999996, -2, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    32, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65540, 99, 33, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2,
    131096, -30000000, 0, 196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1,
    0, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000,
    0, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 250, 327771, (s32)btlevtcmd_SetPos, -2, -30000000,
    -29999999, -29999998, 65546, 1000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999994, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0,
    -29999993, 131099, -29999993, 22, 131126, -29999993, 22, 32,
    131126, -29999993, 22, 131127, -29999993, -1, 33, 110,
    65545, -29999993, 196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -29999995, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -29999995, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 32, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997,
    -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999994,
    110, 65570, -29999988, 65572, (s32)badgeWeapon_MiniminiFumi, 131122, -29999987, 4,
    65572, (s32)badgeWeapon_NemuraseFumi, 131122, -29999987, 3, 65572, (s32)badgeWeapon_FunyafunyaJump, 131122,
    -29999987, 1, 49, 65570, -29999988, 65579, (s32)badgeWeapon_MiniminiFumi, 65579,
    (s32)badgeWeapon_NemuraseFumi, 65579, (s32)badgeWeapon_FunyafunyaJump, 196699, (s32)_jump_star_effect, -2, -29999987, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_MARIO_HAMMER_SHINE1", -250000000, 0, -250000000, 46, 49, 112, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_StartAC, 1,
    131122, -29999990, 0, 65539, 10, 131101, -29999990, 1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 1048832, -29999995,
    32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256,
    -29999995, 33, 65570, -29999995, 65579, 2, 65579, 3,
    65579, 4, 65579, 6, 46, 65572, 1, 42,
    65546, 1000, 49, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 131101, -29999990, 1, 131122, -29999994, 36,
    393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999994, 110,
    65545, 3, 131122, -30000000, -29999994, 131128, -30000000, 2,
    131126, -30000000, 3, 131122, -29999999, -30000000, 131122, -29999998,
    -30000000, 131126, -29999999, 3, 131125, -29999998, 3, 131122,
    -30000000, -29999994, 131126, -30000000, 4, 393307, (s32)btlevtcmd_ACRStart, -2,
    -29999999, -29999998, -30000000, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993,
    65570, -29999994, 65577, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_A_4", 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, -60, -25, 0,
    196699, (s32)btlevtcmd_snd_voice, -2, 1, 42, 65627, (s32)evt_audience_acrobat_notry, 49,
    112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999994,
    3, -1, 32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000,
    0, -250000000, 131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2,
    -30000000, -29999999, -29999998, -29999994, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, -29999994, 0, -1, 33, 131097, -29999995,
    1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_D_2", 65545, 40, 65540, 95, 33, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1,
    131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 65545, -30000000,
    196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC,
    -29999994, 131103, -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 131096, -29999990, 0, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65540, 95, 33, 196699, (s32)btlevtcmd_snd_voice, -2, 2,
    131163, (s32)btlevtcmd_GetResultCountAC, -29999994, 131100, -29999994, 1, 107, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 65545,
    10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 109, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    131072, -29999995, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994,
    65545, 2, 131125, -29999990, 1, 65540, 10, 32,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 131328, -29999995, 65545, 2, 33, 65539,
    90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

static s32 marioAttackEvent_KururinJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999591, 196699, (s32)btlevtcmd_check_battleflag,
    -30000000, 2, 131097, -30000000, 0, 131122, -29999988, (s32)marioWeapon_KururinJump,
    131163, (s32)btlevtcmd_ACHelpSet, (s32)marioWeapon_KururinJump, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 131096,
    -29999997, -1, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0,
    10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -29999997, -29999996, -2, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 250, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999,
    -29999998, 65545, 30, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997,
    -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999994,
    458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999993,
    131099, -29999993, 22, 131126, -29999993, 22, 32, 131126,
    -29999993, 22, 131127, -29999993, -1, 33, 110, 65545,
    -29999993, 196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -29999995, 196699, (s32)btlevtcmd_AcSetDifficulty, -2,
    -29999995, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0, 112,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630,
    (s32)marioAttackEvent_MajinaiPowerUpCheck, 196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0,
    -2, 1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928,
    196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000,
    -29999998, 1, -29999994, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999994, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_StartAC, 1,
    131122, -29999990, 0, 65539, 10, 131101, -29999990, 1,
    458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 1048832, -29999995,
    32, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988, 256,
    -29999995, 33, 65570, -29999995, 65579, 2, 65579, 3,
    65579, 4, 65579, 6, 46, 65572, 1, 42,
    65546, 1000, 49, 131100, -29999990, 0, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998, 5,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 131122, -29999994, 36,
    393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999994, 110,
    131122, -30000000, -29999994, 131122, -29999999, -29999994, 131128, -30000000,
    2, 131126, -29999999, 1, 393307, (s32)btlevtcmd_ACRStart, -2, 5,
    -30000000, -29999999, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570,
    -29999994, 65577, 2, 196699, (s32)btlevtcmd_snd_voice, -2, 1, 393307,
    (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 14, 0, 65541, 15, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 0, -24, 65545, 1, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 42, 65627, (s32)evt_audience_acrobat_notry,
    49, 112, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0,
    -250000000, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999994,
    0, -1, 131097, -29999995, 1, 131096, -29999995, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 131163,
    (s32)btlevtcmd_JumpContinue, -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0,
    -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_D_2", 65545, 40,
    65540, 95, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D",
    196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128,
    -30000000, 2, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1,
    65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65540, 95, 33, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 65545, 10, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 109,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131072, -29999995,
    131125, -29999990, 1, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 327771,
    (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 33, 65647, -29999986,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_J_1B", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000,
    0, -250000000, 131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2,
    -30000000, -29999999, -29999998, -29999994, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, -29999994, 0, -1, 112, 65545, 15,
    65631, -29999986, 65540, 55, 65539, 52, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_N_7", 65545, 30, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_FallPosition, -2, -30000000,
    -29999999, -29999998, 14, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000,
    0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_D_2", 65545,
    28, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_U_3", 65545, 30,
    65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95,
    65539, 55, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985,
    -30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_1A", 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 12, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_JUMP_KURURIN1",
    -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER1", -250000000,
    0, -250000000, 65541, 12, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, -29999985, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0,
    0, 65545, 15, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    4, 0, 0, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_A_1B", 65545, 2, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1,
    131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 131125, -30000000,
    1, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994,
    131102, -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    (s32)marioWeapon_KururinJump2, 131328, -29999995, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 1, -29999994, 327771,
    (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, (s32)marioWeapon_KururinJump2,
    -29999994, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 32, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, (s32)marioWeapon_KururinJump2, 256, -29999995, 262235,
    (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, (s32)marioWeapon_KururinJump2, -29999994,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 33, 65540, 95,
    65539, 90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    60, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30,
    -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1, 65539,
    95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 marioAttackEvent_JyabaraJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699,
    (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 196699, (s32)btlevtcmd_GetWeaponActionLv,
    -29999988, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 327771, (s32)btlevtcmd_SetupAC,
    -2, 1, 1, 0, 65545, 21, 131163, (s32)btlevtcmd_StartAC,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_S_1", 65545, 1, 327771,
    (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, (s32)"p_jyabara", 1, 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2,
    1, (s32)"PM_J_1E", 65545, 16, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER2",
    -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_JUMP_JABARA1", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, (s32)"p_jyabara", 0,
    262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_1A", 65545, 8, 262235,
    (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_1B", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_JUMP_JABARA2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_2A",
    65545, 8, 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_2B", 65545,
    10, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_JUMP_JABARA3", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_3A", 65545, 10, 262235,
    (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_3B", 65545, 20, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_JUMP_JABARA4", -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_VOICE_MARIO_AC3_5", -250000000, 0, -250000000, 131163, (s32)_bgset_iron_frame_check, -30000000, 131097,
    -30000000, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 262235,
    (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_1C", 65644, -29999986, 65541, 50,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 48, 0, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 109,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2,
    (s32)"SFX_BTL_JUMP_CONTINUE1", 0, 0, -1, -1, 0, 0, 65644,
    -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0, -250000000,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 90, -2,
    109, 131163, (s32)_wait_jyabara_hit_iron_frame, -2, 65631, -29999986, 65631, -29999985,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 131163, (s32)btlevtcmd_WeaponAftereffect,
    (s32)marioWeapon_JyabaraJumpFailed, 65627, (s32)btlevtcmd_StopAC, 393307, (s32)evt_btl_camera_shake_h, 0, 2, 0,
    10, 13, 110, 131124, -30000000, -229998976, 65541, 5,
    65545, 1, 131131, -30000000, -229999796, 327771, (s32)btlevtcmd_SetScale, -2,
    -229998976, -30000000, -229998976, 6, 112, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, 130,
    -29999998, 5, 0, 0, 0, -1, 65545, 16,
    327771, (s32)btlevtcmd_SetScale, -2, -229998976, -229998976, -229998976, 262235, (s32)btlevtcmd_AnimeChangePaperAnime,
    -2, 1, (s32)"PM_J_1H", 327771, (s32)btlevtcmd_GetPos, -2, -29999995, -29999994,
    -29999993, 262235, (s32)btlevtcmd_TransStageFloorPosition, -29999995, -29999994, -29999993, 110, 131122,
    -29999995, -29999994, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999991, -250000000,
    131126, -29999991, -29999995, 131128, -29999991, 4, 327771, (s32)btlevtcmd_GetPos,
    -2, -250000000, -29999994, -250000000, 131126, -29999994, -29999991, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999993, -29999999, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000,
    -29999993, -29999999, 131125, -29999993, -29999991, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999992, -29999999, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999992, -29999999,
    327771, (s32)btlevtcmd_GetPos, -2, -250000000, -30000000, -250000000, 327771, (s32)evt_sub_intpl_init,
    0, -30000000, -29999994, 32, 65541, 32, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetPos, -2, -250000000, -30000000, -250000000, 65545, 1,
    6, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -30000000, -250000000, 327771,
    (s32)evt_sub_intpl_init, 0, -30000000, -29999993, 64, 65541, 64, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetPos, -2, -250000000, -30000000, -250000000, 65545,
    1, 6, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -30000000, -250000000,
    327771, (s32)evt_sub_intpl_init, 0, -30000000, -29999992, 32, 65541, 32,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetPos, -2, -250000000, -30000000, -250000000,
    65545, 1, 6, 112, 110, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999993, 131127,
    -29999993, -30, 131122, -29999999, -30000000, 131125, -29999999, -29999993,
    327771, (s32)evt_sub_intpl_init, 11, -30000000, -29999999, 26, 65541, 26,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -250000000, -250000000,
    65545, 1, 6, 65545, 6, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999993, 131127,
    -29999993, 60, 131122, -29999999, -30000000, 131125, -29999999, -29999993,
    327771, (s32)evt_sub_intpl_init, 11, -30000000, -29999999, 58, 65541, 58,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -250000000, -250000000,
    65545, 1, 6, 65545, 6, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -250000000, -250000000, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999993, 131127,
    -29999993, -30, 131122, -29999999, -30000000, 131125, -29999999, -29999993,
    327771, (s32)btlevtcmd_GetHomePos, -2, -29999999, -250000000, -250000000, 327771, (s32)evt_sub_intpl_init,
    11, -30000000, -29999999, 32, 65541, 32, 65627, (s32)evt_sub_intpl_get_value,
    327771, (s32)btlevtcmd_SetPos, -2, -30000000, -250000000, -250000000, 65545, 1,
    6, 112, 65545, 130, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_I_S", 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_1E", 65647, -29999985,
    327771, (s32)evt_sub_intpl_init_float, 5, -230000000, -229998772, 10, 65541, 10,
    196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771, (s32)btlevtcmd_GetScale, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2, -30000000, -29999995, -29999998,
    65545, 1, 6, 327771, (s32)evt_sub_intpl_init_float, 7, -229998772, -229998976,
    30, 65541, 30, 196699, (s32)evt_sub_intpl_get_float, -29999995, -250000000, 327771,
    (s32)btlevtcmd_GetScale, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_SetScale, -2,
    -30000000, -29999995, -29999998, 65545, 1, 6, 112, 131163,
    (s32)btlevtcmd_WaitEventEnd, -29999985, 65545, 20, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    65540, 95, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B",
    262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"PM_J_1C", 110, 65541, 50,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 48, 0, 65545, 1,
    6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_1A", 786523, (s32)btlevtcmd_SetPartsBlur, -2, 1,
    255, 255, 255, 80, 255, 255, 255, 0,
    0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 67108864, 112, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2,
    (s32)"SFX_BTL_JUMP_CONTINUE1", 0, 0, -1, -1, 0, 0, 196699,
    (s32)evt_sub_random, 20, -29999995, 131126, -29999995, 10, 131127, -29999995,
    6, 131125, -29999995, 180, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999847,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125,
    -29999998, 5, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    -29999995, -2, 458843, (s32)btlevtcmd_PreCheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 131097, -29999995, 1, 131096, -29999995, 3,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 131163,
    (s32)btlevtcmd_JumpContinue, -2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_B_2", 327771,
    (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0, 786523, (s32)btlevtcmd_SetPartsBlur, -2,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 107, 65545, 10, 262235, (s32)btlevtcmd_OffPartsAttribute, -2,
    1, 67108864, 109, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 35, 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999488, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 12, 0,
    110, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127, -30000000, -24,
    65541, 20, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000,
    65545, 1, 6, 112, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 20, -1, 262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000,
    20, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 110, 196699, (s32)btlevtcmd_GetFaceDirection,
    -2, -30000000, 131127, -30000000, -20, 65541, 12, 327771,
    (s32)btlevtcmd_AddRotate, -2, 0, 0, -30000000, 65545, 1, 6,
    112, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_Z_11", 262235, (s32)btlevtcmd_FaceDirectionAdd,
    -2, -30000000, 10, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999,
    -29999998, 20, 0, 4, 0, -1, 65545, 30,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_U_3", 65545, 12, 65540,
    95, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 65545,
    2, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0, 786523,
    (s32)btlevtcmd_SetPartsBlur, -2, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 107, 65545, 10, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 1, 67108864, 109, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1,
    1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 131125,
    -30000000, 2, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1,
    65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2,
    458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 256, -29999995,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 196699, (s32)btlevtcmd_GetDamage, -29999997, -30000000,
    393307, (s32)evt_btl_camera_shake_h, 0, -30000000, 0, 10, 13, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -29999988, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2,
    -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1,
    65540, 95, 32, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 131072, -29999995, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 65647, -29999986,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999488, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 131125, -29999998, 5, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_J_1B", 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000,
    0, -250000000, 131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2,
    -30000000, -29999999, -29999998, -29999994, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000,
    -29999999, -29999998, -29999994, 0, -1, 112, 65545, 15,
    65631, -29999986, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985,
    -30, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_1A", 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 12, 0, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER1",
    -250000000, 0, -250000000, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_JUMP_JABARA5", -250000000,
    0, -250000000, 65541, 12, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, -29999985, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 0,
    0, 65545, 15, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998,
    4, 0, 0, 0, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_A_1B", 65545, 2, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1,
    131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 131125, -30000000,
    1, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627,
    (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131102, -29999994, 2, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328, -29999995, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, 1, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999,
    -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 32, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -29999997, -29999996, -29999988, 256, -29999995, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, 0, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 196699,
    (s32)btlevtcmd_GetDamage, -29999997, -30000000, 393307, (s32)evt_btl_camera_shake_h, 0, -30000000, 0,
    10, 13, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 65627, (s32)btlevtcmd_StopAC, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B",
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 8, -1, 65540, 95, 33, 65539, 90,
    196699, (s32)btlevtcmd_GetDamage, -29999997, -30000000, 393307, (s32)evt_btl_camera_shake_h, 0, -30000000,
    0, 10, 13, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999988, 65627, (s32)btlevtcmd_StopAC,
    65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 110, 65545,
    1, 393307, (s32)btlevtcmd_ACRStart, -2, 11, 15, 29, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577, 2,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_4", 196699, (s32)btlevtcmd_snd_voice, -2,
    1, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0,
    42, 65627, (s32)evt_audience_acrobat_notry, 49, 112, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 30, -1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8, -1,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, 0, -1, 0, 65539,
    99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent,
    -2, 2, 1,
};

s32 marioAttackEvent_GatsuDokaJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 131163, (s32)btlevtcmd_StartAC, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_I_Y", 65545, 10, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 65570, -29999995, 65579, 2, 65579,
    3, 65579, 6, 65579, 4, 46, 65572, 1,
    42, 65546, 1000, 49, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_J_1B", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000,
    0, -250000000, 131122, -29999994, 36, 393307, (s32)btlevtcmd_MarioJumpParam, -2,
    -30000000, -29999999, -29999998, -29999994, 110, 131122, -30000000, -29999994,
    131122, -29999999, -29999994, 131128, -30000000, 2, 131126, -29999999,
    1, 393307, (s32)btlevtcmd_ACRStart, -2, 5, -30000000, -29999999, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577, 2,
    196699, (s32)btlevtcmd_snd_voice, -2, 1, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1,
    0, 0, 0, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 14,
    0, 65541, 15, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0,
    -24, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 42, 65627, (s32)evt_audience_acrobat_notry, 49, 112, 524379,
    (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999994, 0, -1,
    131097, -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_D_2", 65545, 40, 65540, 95,
    33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 196699, (s32)btlevtcmd_ac_timing_flag_onoff,
    1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2,
    65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627, (s32)btlevtcmd_ResultAC,
    131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 196699, (s32)btlevtcmd_GetDamage, -29999997,
    -30000000, 393307, (s32)evt_btl_camera_shake_h, 0, -30000000, 0, 10, 13,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65540, 95, 33, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997,
    -29999996, 131328, -29999995, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 327771,
    (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 65545, 2, 65539,
    90, 196699, (s32)btlevtcmd_GetDamage, -29999997, -30000000, 393307, (s32)evt_btl_camera_shake_h, 0,
    -30000000, 0, 10, 13, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627,
    (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 95, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 marioAttackEvent_TatsumakiJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0,
    -29999993, 131126, -29999993, 21, 131098, -29999993, 0, 131127,
    -29999993, -1, 65545, -29999993, 33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_StartAC,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_Y", 65545, 10,
    393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995, 65570,
    -29999995, 65579, 2, 65579, 3, 65579, 6, 65579,
    4, 46, 65572, 1, 42, 65546, 1000, 49,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 131125, -29999998, 5, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0, -250000000, 131122, -29999994,
    36, 393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999994,
    524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999994, 0,
    -1, 131097, -29999995, 1, 131096, -29999995, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 33, 131096, -29999995, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 33, 131096, -29999995, 2, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 40, 33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue,
    -2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0, -250000000,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_D_2", 65545, 40, 65540,
    95, 33, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 196699,
    (s32)btlevtcmd_ac_timing_flag_onoff, 1, 1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000,
    2, 65545, -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627,
    (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 65540, 90,
    33, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom,
    0, 200, 65545, 10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoom, 0, 250, 109, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 131328, -29999995, 196699, (s32)btlevtcmd_GetFriendBelong, -29999997, -29999985,
    131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997,
    0, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998,
    33, 65545, 2, 65627, (s32)btlevtcmd_StopAC, 65644, -29999987, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999847,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999,
    -29999998, 80, 3, -1, 109, 110, 65541, 24,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 15, 0, 65545, 1,
    6, 112, 65545, 27, 65631, -29999987, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 131163, (s32)btlevtcmd_AcGetDifficulty, -30000000,
    131126, -30000000, 3, 65570, -30000000, 65576, -3, 196699,
    (s32)btlevtcmd_ftof, 600, -30000000, 65572, -2, 196699, (s32)btlevtcmd_ftof, 480,
    -30000000, 65572, -1, 196699, (s32)btlevtcmd_ftof, 420, -30000000, 65572,
    0, 196699, (s32)btlevtcmd_ftof, 360, -30000000, 65572, 1, 196699,
    (s32)btlevtcmd_ftof, 300, -30000000, 65572, 2, 196699, (s32)btlevtcmd_ftof, 200,
    -30000000, 42, 196699, (s32)btlevtcmd_ftof, 100, -30000000, 49, 589915,
    (s32)btlevtcmd_AcSetParamAll, -30000000, 1, 3, -4, 3, -250000000, -250000000,
    -250000000, 131163, (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 10,
    1, 0, 65545, 1, 131163, (s32)btlevtcmd_StartAC, 1, 262235,
    (s32)btlevtcmd_SetUnitWork, -3, 5, 0, 262235, (s32)btlevtcmd_SetUnitWork, -3, 6,
    0, 262235, (s32)btlevtcmd_SetUnitWork, -3, 7, 0, 65644, -29999987,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 1, 262235, (s32)btlevtcmd_SetUnitWork, -2,
    3, 30, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4, 0, 131122,
    -30000000, 15, 65539, 60, 262235, (s32)btlevtcmd_GetUnitWork, -2, 2,
    -29999999, 131096, -29999999, 0, 65540, 61, 33, 262235,
    (s32)btlevtcmd_GetUnitWork, -2, 3, -29999990, 131125, -30000000, 1, 131099,
    -30000000, -29999990, 131122, -30000000, -29999990, 33, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 4, -30000000, 327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000,
    0, 65545, 1, 65540, 60, 65539, 61, 109,
    65647, -29999986, 131122, -30000000, 0, 65541, 1000, 65545,
    1, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -29999999, 131097, -29999999, -30000000,
    131122, -30000000, -29999999, 65570, -30000000, 65572, 0, 65572,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -3, 5, 1023, 262235, (s32)btlevtcmd_GetUnitWork,
    -3, 6, -29999990, 131126, -29999990, 1023, 131127, -29999990,
    -1, 131128, -29999990, 10, 262235, (s32)btlevtcmd_SetUnitWork, -3, 7,
    -29999990, 65572, 2, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 45,
    262235, (s32)btlevtcmd_SetUnitWork, -3, 5, 2046, 262235, (s32)btlevtcmd_GetUnitWork, -3,
    6, -29999990, 131126, -29999990, 2046, 131127, -29999990, -1,
    131128, -29999990, 10, 262235, (s32)btlevtcmd_SetUnitWork, -3, 7, -29999990,
    65572, 3, 262235, (s32)btlevtcmd_SetUnitWork, -3, 5, 3069, 262235,
    (s32)btlevtcmd_GetUnitWork, -3, 6, -29999990, 131126, -29999990, 3069, 131127,
    -29999990, -1, 131128, -29999990, 10, 262235, (s32)btlevtcmd_SetUnitWork, -3,
    7, -29999990, 42, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 60,
    49, 33, 6, 112, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_JUMP_TATUMAKI1", -29999989,
    65647, -29999988, 131122, -29999995, 5, 65541, -29999995, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)evt_snd_sfx_pos, -29999989,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetUnitWork, -3, 5, -29999999,
    262235, (s32)btlevtcmd_GetUnitWork, -3, 6, -30000000, 131097, -30000000, -29999999,
    262235, (s32)btlevtcmd_GetUnitWork, -3, 7, -29999998, 131125, -30000000, -29999998,
    131101, -29999998, 0, 131101, -30000000, -29999999, 131122, -30000000,
    -29999999, 33, 32, 131100, -30000000, -29999999, 131122, -30000000,
    -29999999, 33, 33, 262235, (s32)btlevtcmd_SetUnitWork, -3, 6, -30000000,
    196699, (s32)evt_snd_sfx_pit, -29999989, -30000000, 33, 65545, 1, 131122,
    -29999995, 5, 6, 112, 65627, (s32)btlevtcmd_ResultAC, 65545, 1,
    131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 65631, -29999986,
    110, 262235, (s32)btlevtcmd_SetUnitWork, -3, 5, -2728, 262235, (s32)btlevtcmd_GetUnitWork,
    -3, 6, -29999990, 131126, -29999990, -2728, 131127, -29999990,
    -1, 131128, -29999990, 40, 262235, (s32)btlevtcmd_SetUnitWork, -3, 7,
    -29999990, 112, 110, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -29999999,
    -250000000, 65541, 40, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000,
    131099, -30000000, 10, 131126, -30000000, 1, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 3, -30000000, 33, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000,
    -30000000, -250000000, 131098, -29999999, 90, 131101, -30000000, 90,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_N_7", 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_MARIO_FALL_CRUSH1", -250000000, 0, -250000000, 33, 33, 131122, -29999999,
    -30000000, 65545, 1, 6, 112, 65545, 40, 65631,
    -29999987, 65631, -29999988, 131163, (s32)evt_snd_sfxoff, -29999989, 65647, -29999987,
    65541, 60, 327771, (s32)btlevtcmd_GetRotate, -2, -250000000, -30000000, -250000000,
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -29999999, 131125, -30000000, -29999999,
    131101, -30000000, 360, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 7, 33, 327771, (s32)btlevtcmd_SetRotate, -2, 0, -30000000,
    0, 65545, 1, 6, 112, 131163, (s32)btlevtcmd_WaitEventEnd, -29999987,
    327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 65545, 60,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_JumpSetting,
    -2, 40, -230000000, -229999898, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999,
    -29999998, 110, 65545, 12, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_D_2",
    112, 393307, (s32)btlevtcmd_FallPosition, -2, -30000000, -29999999, -29999998, 16,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1,
    65545, 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_U_3", 65545,
    12, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95, 32,
    65631, -29999986, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 45, 65539,
    62, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -30000000, 131098, -30000000,
    44, 65545, 1, 65540, 62, 33, 110, 131122,
    -29999994, -29999997, 131163, (s32)_tatsumaki_effect, -2, 131122, -30000000, -29999985,
    262235, (s32)btlevtcmd_SamplingEnemy, -5, -30000000, (s32)badgeWeapon_TatsumakiJumpInvolved, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 65539, 50, 131096, -29999997, -1, 65540, 59,
    33, 131096, -29999997, -29999994, 65540, 58, 33, 458843,
    (s32)btlevtcmd_PreCheckDamage, -5, -29999997, -29999996, (s32)badgeWeapon_TatsumakiJumpInvolved, 256, -29999995, 65570,
    -29999995, 65572, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65572,
    3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 65572, 6, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 39, 65572, 4, 65572, 1, 131163,
    (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 458843, (s32)btlevtcmd_CheckDamage, -5,
    -29999997, -29999996, (s32)badgeWeapon_TatsumakiJumpInvolved, 131328, -29999995, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 1,
    -29999993, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999993, -30000000, -29999999, -29999998, 32,
    458843, (s32)btlevtcmd_CheckDamage, -5, -29999997, -29999996, (s32)badgeWeapon_TatsumakiJumpInvolved, 256, -29999995,
    33, 42, 49, 65539, 58, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 65540, 50, 65539, 59, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 1, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -30000000, -29999994, 112, 65545, 60, 65644, -29999987, 65541,
    30, 262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131126, -30000000,
    1, 262235, (s32)btlevtcmd_SetUnitWork, -2, 3, -30000000, 65545, 1,
    33, 262235, (s32)btlevtcmd_SetUnitWork, -2, 2, 0, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, 0, 65541, 6, 65545, 1,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 45, 0, 6, 65541,
    6, 65545, 1, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 15,
    0, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    109, 131163, (s32)btlevtcmd_WaitEventEnd, -29999987, 65631, -29999988, 131163, (s32)evt_snd_sfxoff,
    -29999989, 65545, 30, 110, 393307, (s32)btlevtcmd_ACRStart, -2, 7,
    21, 21, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 131101,
    -29999994, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_B_1", 33,
    112, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999847,
    393307, (s32)btlevtcmd_FallPosition, -2, -30000000, -29999999, -29999998, 16, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 65545, 6, 196699, (s32)btlevtcmd_ACRGetResult,
    -29999994, -29999993, 131101, -29999994, 2, 65540, 80, 33,
    33, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95, 65539,
    80, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229995904, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999,
    -29999998, 0, -29999993, 131122, -29999992, -29999993, 131125, -29999992,
    12, 110, 65545, 1, 393307, (s32)btlevtcmd_ACRStart, -2, -29999993,
    -29999992, -29999992, 0, 112, 131125, -29999992, 1, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999985, 131127, -29999985, 30, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 14, 0, 110, 131122, -29999990, 0,
    65541, -29999992, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, -29999985,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_snd_voice, -2, 1, 33,
    131125, -29999990, 1, 131101, -29999990, 12, 131122, -29999990,
    0, 33, 65545, 1, 6, 112, 524379, (s32)btlevtcmd_MovePosition,
    -2, -30000000, -29999999, -29999998, -29999992, -1, 0, 196699,
    (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 36, 65644, -29999986,
    327771, (s32)btlevtcmd_GetRotate, -2, -30000000, -29999999, -29999998, 131129, -29999998,
    360, 131128, -29999998, 10, 131125, -29999998, -29999995, 65541,
    10, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    109, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577,
    2, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, 0, 0, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999999, 50, 983131, (s32)evt_eff, (s32)"_BTLEF",
    (s32)"confetti", 3, -30000000, -29999999, -29999998, 90, 0, 0,
    0, 0, 0, 0, 0, 196699, (s32)btlevtcmd_snd_voice, -2,
    1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ACROBAT_FINISH1", 0, 65545, 90, 65576,
    -1, 65631, -29999986, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000,
    0, 0, 0, 0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ACROBAT_MISS1", 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_S", 65546, 1500, 42,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 65627, (s32)evt_audience_acrobat_notry, 49, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65540, 99, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1",
    196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1, 0,
    65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 marioAttackEvent_RenzokuJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 196699, (s32)btlevtcmd_GetSelectEnemy,
    -29999997, -29999996, 131096, -29999997, -1, 65540, 99, 33,
    262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1, 2, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2,
    -29999997, -29999996, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2,
    -1, -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2,
    -29999985, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 131163, (s32)btlevtcmd_StartAC,
    1, 131122, -29999990, 0, 65539, 10, 131101, -29999990,
    1, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 1048832, -29999995,
    32, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999995,
    33, 65570, -29999995, 65579, 2, 65579, 3, 65579,
    6, 65579, 4, 46, 65572, 1, 42, 65546,
    1000, 49, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 131125, -29999998,
    5, 131101, -29999990, 1, 131122, -29999992, 36, 393307,
    (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999992, 65570, -29999990,
    65572, 1, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE2", 65572, 2, 131122,
    -29999994, (s32)"SFX_BTL_JUMP_CONTINUE3", 65572, 3, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE4", 65572,
    4, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE5", 65572, 5, 131122, -29999994,
    (s32)"SFX_BTL_JUMP_CONTINUE6", 65572, 6, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE7", 65572, 7,
    131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE8", 65572, 8, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE9",
    42, 131122, -29999994, (s32)"SFX_BTL_JUMP_CONTINUE10", 49, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2,
    -29999994, 0, 0, -1, -1, 0, 0, 110,
    65545, 3, 393307, (s32)btlevtcmd_ACRStart, -2, 11, 15, 30,
    0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577,
    2, 196699, (s32)evt_sub_random, 2, -30000000, 65570, -30000000, 65572,
    0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_4", 65572, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_5", 42, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_A_6", 49, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, -60, -30, 0, 196699,
    (s32)btlevtcmd_snd_voice, -2, 1, 42, 65627, (s32)evt_audience_acrobat_notry, 49, 112,
    524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999992, 3,
    -2, 32, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0,
    -250000000, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_JUMP_CONTINUE1", 0, 0, -1,
    -1, 0, 0, 131122, -29999992, 36, 393307, (s32)btlevtcmd_MarioJumpParam,
    -2, -30000000, -29999999, -29999998, -29999992, 524379, (s32)btlevtcmd_MarioJumpPosition, -2,
    -30000000, -29999999, -29999998, -29999992, 0, -2, 33, 131097,
    -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_D_2", 65545, 40, 65540, 95, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1,
    1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 65545,
    -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627, (s32)btlevtcmd_ResultAC, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 32,
    131122, -29999994, -29999990, 131126, -29999994, 1, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, -29999994, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 33,
    65627, (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 65627, (s32)evt_audience_ap_recovery, 65627,
    (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999284, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_GetHomePos, -2, -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub,
    -2, -30000000, 27, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999,
    -29999998, 20, -1, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235,
    (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000,
    -29999999, -29999998, 12, -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    8, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 8,
    -1, 65540, 95, 33, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 65545, 10, 196699,
    (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom, 0, 250, 109,
    196699, (s32)btlevtcmd_snd_voice, -2, 2, 131163, (s32)btlevtcmd_GetResultCountAC, -29999994, 131163,
    (s32)_record_renzoku_count, -29999994, 131163, (s32)btlevtcmd_GetResultCountAC, -29999994, 262235, (s32)mario_get_renzoku_count_max, -29999997,
    -29999994, -29999993, 131098, -29999994, -29999993, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 131072, -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 131328, -29999995, 33, 131125, -29999990, 1,
    131122, -29999999, -169999968, 131122, -29999998, -169999965, 131127, -29999998,
    256, 131125, -29999999, -29999998, 131099, -29999990, -29999999, 131122,
    -30000000, -29999990, 131099, -30000000, 9999, 131122, -30000000, 9999,
    33, 131122, -29999999, -30000000, 131129, -29999999, 256, 131122,
    -29999998, -30000000, 131128, -29999998, 256, 131122, -169999968, -29999999,
    131122, -169999965, -29999998, 33, 131122, -30000000, -29999990, 131126,
    -30000000, 1, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -30000000, -29999994, 393307,
    (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect,
    -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 131163, (s32)btlevtcmd_GetResultCountAC, -29999994, 131098,
    -29999994, -29999993, 65545, 2, 131163, (s32)btlevtcmd_StartAC, 0, 65540,
    10, 33, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)evt_btl_camera_set_mode,
    0, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -30000000, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65539, 95, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection,
    -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 marioAttackEvent_TugiTugiJump[] = {
    327771, (s32)btlevtcmd_JumpSetting, -2, 20, -230000000, -229999284, 131163, (s32)btlevtcmd_AttackDeclareAll,
    -2, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131163,
    (s32)btlevtcmd_CommandPayWeaponCost, -2, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 250, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty,
    -2, -30000000, 327771, (s32)btlevtcmd_SetupAC, -2, 1, 1, 0,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 458843, (s32)btlevtcmd_GetTakeoffPosition, -2, -29999997, -29999996, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 131163, (s32)btlevtcmd_StartAC, 1, 131122, -29999990, 0,
    65539, 10, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 65570, -29999995, 65579, 2, 65579, 3, 65579,
    6, 65579, 4, 46, 65572, 1, 42, 65546,
    1000, 49, 589915, (s32)btlevtcmd_SetMoveSoundDataWork, -2, (s32)"SFX_BTL_JUMP_TUGITUGI1", 0, 0,
    -1, -1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_J_1B", 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999998, 5, 65570, -29999990, 65572, 0, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_BATTLE_JUMP1", -250000000, 0, -250000000, 131122, -29999992,
    36, 393307, (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999992,
    524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998, -29999992, 0,
    -2, 65572, 1, 131122, -29999992, 36, 393307, (s32)btlevtcmd_MarioJumpParam,
    -2, -30000000, -29999999, -29999998, -29999992, 110, 65545, 3,
    393307, (s32)btlevtcmd_ACRStart, -2, 13, 17, 30, 0, 196699,
    (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577, 2, 196699,
    (s32)evt_sub_random, 2, -30000000, 65570, -30000000, 65572, 0, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_4", 65572, 1, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_A_5", 42, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_A_6", 49, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -30000000, 1, -60, -30, 0, 42, 65627, (s32)evt_audience_acrobat_notry,
    49, 112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2, -30000000, -29999999, -29999998,
    -29999992, 3, -2, 42, 131122, -29999992, 36, 393307,
    (s32)btlevtcmd_MarioJumpParam, -2, -30000000, -29999999, -29999998, -29999992, 110, 65545,
    3, 393307, (s32)btlevtcmd_ACRStart, -2, 13, 17, 30, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577, 2,
    196699, (s32)evt_sub_random, 2, -30000000, 65570, -30000000, 65572, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_4", 65572, 1, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_5", 42, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_A_6", 49, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 393307,
    (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 1, -60, -30, 0, 65576, -1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_N_7", 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -30000000, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -30000000, 0, 0, 0, 0,
    42, 65627, (s32)evt_audience_acrobat_notry, 49, 112, 524379, (s32)btlevtcmd_MarioJumpPosition, -2,
    -30000000, -29999999, -29999998, -29999992, 4, -2, 49, 131097,
    -29999995, 1, 131096, -29999995, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999995, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999995, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_JumpContinue, -2, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_LAND_DAMAGE1", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_D_2", 65545, 40, 65540, 95, 33,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_J_1D", 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 1,
    1, 131163, (s32)btlevtcmd_ac_timing_get_success_frame, -30000000, 131128, -30000000, 2, 65545,
    -30000000, 196699, (s32)btlevtcmd_ac_timing_flag_onoff, 0, 1, 65627, (s32)btlevtcmd_ResultAC, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2,
    -29999997, -29999996, 256, -29999995, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    131096, -29999990, 0, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 32,
    131122, -29999994, -29999990, 131126, -29999994, 1, 262235, (s32)btlevtcmd_GetResultPrizeLv,
    -29999997, -29999994, -29999994, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 33,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771, (s32)btlevtcmd_GetPos,
    -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2, -250000000,
    -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 27, 458843,
    (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 20, -1, 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 20,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12, -1,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 8, -1, 65540, 95, 33,
    393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 131163,
    (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2, 196699, (s32)btlevtcmd_snd_voice, -2,
    2, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999990, -29999994, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    -30000000, -29999999, -29999998, 33, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996,
    131097, -29999997, -1, 107, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2,
    196699, (s32)evt_btl_camera_set_zoomSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0, 200,
    65545, 10, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoom,
    0, 250, 109, 65545, 2, 131125, -29999990, 1,
    107, 65545, 10, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1,
    -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 109, 65540,
    10, 33, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, -29999990, -29999994, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 65539,
    90, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 65627, (s32)btlevtcmd_StopAC, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_J_1B", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999284, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -250000000, -29999999, -250000000, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 60,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999386, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    20, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 12,
    -1, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 8, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 8, -1, 65539, 95,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

s32 marioAttackEvent_NormalHammer_Core[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 131122,
    -29999988, (s32)marioDefaultWeapon_Hammer, 196699, (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 196699, (s32)evt_btl_camera_set_mode, 0, 7,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -29999997, -1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    300, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 250,
    327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 65545, 30,
    32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997,
    -29999996, 131096, -29999997, -1, 65540, 99, 33, 262235,
    (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost,
    -2, -29999988, 196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck,
    196699, (s32)evt_btl_camera_set_mode, 0, 11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2,
    1, -29999997, -29999996, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 300, 33, 196699, (s32)btlevtcmd_check_battleflag, -30000000, 2,
    131096, -30000000, 0, 196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -30000000, 196699,
    (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 65570, -29999988, 65572, (s32)marioDefaultWeapon_Hammer, 589915,
    (s32)btlevtcmd_AcSetParamAll, 4, 25, 0, 0, 0, -250000000, -250000000,
    -250000000, 65572, (s32)badgeWeapon_ConfuseHammer, 589915, (s32)btlevtcmd_AcSetParamAll, 4, 30, 0,
    0, 0, -250000000, -250000000, -250000000, 65572, (s32)badgeWeapon_TsuranukiNaguri, 589915,
    (s32)btlevtcmd_AcSetParamAll, 4, 30, 0, 0, 0, -250000000, -250000000,
    -250000000, 42, 589915, (s32)btlevtcmd_AcSetParamAll, 4, 40, 0, 0,
    0, -250000000, -250000000, -250000000, 49, 131163, (s32)btlevtcmd_AcSetFlag, 0,
    327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0, 33, 196699,
    (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000,
    250, 327771, (s32)btlevtcmd_SetPos, -2, -30000000, -29999999, -29999998, 65546,
    1000, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2,
    1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999,
    -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -250000000, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 35, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229994880,
    131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000,
    -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 458843,
    (s32)btlevtcmd_GetMoveFrame, -2, -30000000, -29999999, -29999998, 0, -29999993, 131099,
    -29999993, 22, 131126, -29999993, 22, 32, 131126, -29999993,
    22, 131127, -29999993, -1, 33, 110, 65545, -29999993,
    196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000,
    65570, -29999988, 65572, (s32)marioDefaultWeapon_Hammer, 589915, (s32)btlevtcmd_AcSetParamAll, 4, 25,
    0, 0, 0, -250000000, -250000000, -250000000, 65572, (s32)badgeWeapon_ConfuseHammer,
    589915, (s32)btlevtcmd_AcSetParamAll, 4, 30, 0, 0, 0, -250000000,
    -250000000, -250000000, 65572, (s32)badgeWeapon_TsuranukiNaguri, 589915, (s32)btlevtcmd_AcSetParamAll, 4, 30,
    0, 0, 0, -250000000, -250000000, -250000000, 42, 589915,
    (s32)btlevtcmd_AcSetParamAll, 4, 40, 0, 0, 0, -250000000, -250000000,
    -250000000, 49, 131163, (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2,
    3, 1, 0, 112, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 32, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000,
    -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -250000000,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 35, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -30000000, -29999998, 1, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996,
    16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999988, 256, -29999994, 131096, -29999994,
    5, 65627, (s32)btlevtcmd_StopAC, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 2, 33, 131096, -29999988, (s32)badgeWeapon_TsuranukiNaguri,
    131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 131122,
    -30000000, (s32)"M_H_5A", 131122, -29999999, (s32)"M_H_5B", 131122, -29999998, (s32)"M_H_14",
    65572, 3, 131122, -30000000, (s32)"M_H_9A", 131122, -29999999, (s32)"M_H_9B",
    131122, -29999998, (s32)"M_H_15", 42, 131122, -30000000, (s32)"M_H_1A", 131122,
    -29999999, (s32)"M_H_1B", 131122, -29999998, (s32)"M_H_13", 49, 32, 131163,
    (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 131122, -30000000,
    (s32)"M_H_5A", 131122, -29999999, (s32)"M_H_5B", 131122, -29999998, (s32)"M_H_5C", 65572,
    3, 131122, -30000000, (s32)"M_H_9A", 131122, -29999999, (s32)"M_H_9B", 131122,
    -29999998, (s32)"M_H_9C", 42, 131122, -30000000, (s32)"M_H_1A", 131122, -29999999,
    (s32)"M_H_1B", 131122, -29999998, (s32)"M_H_1C", 49, 33, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_VOICE_MARIO_POWER2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, -30000000, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572,
    2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD2", -250000000, 0, -250000000,
    65572, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD1", -250000000, 0,
    -250000000, 42, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD3", -250000000, 0,
    -250000000, 49, 110, 65570, -29999988, 65572, (s32)badgeWeapon_ConfuseHammer, 131122,
    -29999987, 0, 65572, (s32)badgeWeapon_TsuranukiNaguri, 131122, -29999987, 2, 49,
    65570, -29999988, 65579, (s32)badgeWeapon_ConfuseHammer, 65579, (s32)badgeWeapon_TsuranukiNaguri, 196699, (s32)btlevtcmd_ftomsec,
    9, -30000000, 65546, -30000000, 196699, (s32)_hammer_star_effect, -2, -29999987,
    46, 49, 65570, -29999988, 65579, (s32)badgeWeapon_ConfuseHammer, 65579, (s32)badgeWeapon_TsuranukiNaguri,
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_MARIO_HAMMER_SHINE1", -250000000, 0, -250000000, 46, 49, 112,
    196699, (s32)btlevtcmd_ftomsec, 30, -30000000, 65546, -30000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999999, 131163, (s32)btlevtcmd_StartAC, 0, 65627, (s32)btlevtcmd_ResultAC,
    131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2", 0, 65572, 1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1",
    0, 42, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0, 49, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 7, 131096, -29999988,
    (s32)badgeWeapon_TsuranukiNaguri, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_TURANUKI1", 0, 32, 131163, (s32)_get_mario_hammer_lv,
    -30000000, 65570, -30000000, 65572, 2, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_HIT_GROUND3",
    0, 65572, 1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_HIT_GROUND2", 0, 42,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_HIT_GROUND1", 0, 49, 33, 131097, -29999994,
    1, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 65540, 90, 33, 131163, (s32)btlevtcmd_GetResultAC, -29999994, 131103,
    -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988,
    256, -29999995, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1, 65540, 90,
    33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328,
    -29999995, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0, 196699, (s32)evt_btl_camera_set_zoom, 0,
    250, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0, -29999994, 393307, (s32)btlevtcmd_GetHitPos,
    -29999997, -29999996, -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -29999994, 65539,
    90, 65627, (s32)btlevtcmd_StopAC, 196699, (s32)btlevtcmd_GetDamage, -29999997, -30000000, 393307,
    (s32)evt_btl_camera_shake_h, 0, -30000000, 0, 10, 13, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15, 60, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999985, -29999987, 131096, -29999985, 1, 65540,
    91, 33, 131100, -29999985, -1, 65540, 91, 33,
    65540, 92, 65539, 91, 65627, (s32)evt_audience_acrobat_notry, 131122, -30000000,
    60, 131126, -30000000, -29999987, 131101, -30000000, 1, 65545,
    -30000000, 33, 131096, -29999988, (s32)badgeWeapon_TsuranukiNaguri, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_H_16", 32, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_S_1",
    33, 65545, 10, 65540, 95, 65539, 92, 131097,
    -29999985, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 1, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 110, 196699, (s32)btlevtcmd_snd_voice, -2, 1, 327771, (s32)btlevtcmd_SetRotateOffset,
    -2, 0, 20, 0, 65541, 30, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 0, 12, 65545, 1, 6, 112,
    110, 65545, 8, 393307, (s32)btlevtcmd_ACRStart, -2, 12, 25,
    25, 0, 112, 110, 65545, 4, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_Z_1", 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_A_3A", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 35,
    458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998, 30, -1,
    65545, 4, 196699, (s32)btlevtcmd_ACRGetResult, -30000000, -29999999, 131096, -29999986,
    0, 131096, -30000000, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_A_3B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125,
    -29999999, 50, 983131, (s32)evt_eff, (s32)"_BTLEF", (s32)"confetti", 3, -30000000,
    -29999999, -29999998, 90, 0, 0, 0, 0, 0,
    0, 0, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 65545, 90, 65540, 95, 32, 65627, (s32)evt_audience_acrobat_notry,
    65540, 95, 33, 32, 65570, -30000000, 65572, 2,
    393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0, 65572,
    1, 65627, (s32)evt_audience_acrobat_notry, 65540, 95, 49, 33, 110,
    196699, (s32)btlevtcmd_snd_voice, -2, 1, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0,
    20, 0, 65541, 40, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    0, 18, 65545, 1, 6, 112, 110, 65545,
    18, 393307, (s32)btlevtcmd_ACRStart, -2, 12, 25, 25, 0,
    112, 110, 65545, 18, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_Z_1", 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3A", 196699,
    (s32)btlevtcmd_SetFallAccel, -2, -229999693, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999,
    -29999998, 262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 40, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 40, -1, 65545, 4,
    196699, (s32)btlevtcmd_ACRGetResult, -30000000, -29999999, 131097, -30000000, 2, 65540,
    95, 33, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 196699, (s32)btlevtcmd_snd_voice, -2, 1, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 20, 0, 110, 65541, 60, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 12, 12, 65545, 1, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 110, 65545,
    35, 393307, (s32)btlevtcmd_ACRStart, -2, 15, 28, 28, 0,
    112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_C_3", 196699, (s32)btlevtcmd_SetFallAccel,
    -2, -229999796, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 50, 458843, (s32)btlevtcmd_JumpPosition, -2,
    -30000000, -29999999, -29999998, 60, -1, 65545, 4, 196699,
    (s32)btlevtcmd_ACRGetResult, -30000000, -29999999, 131097, -30000000, 2, 65540, 95,
    33, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3B", 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131125, -29999999, 50, 983131, (s32)evt_eff,
    (s32)"_BTLEF", (s32)"confetti", 3, -30000000, -29999999, -29999998, 90, 0,
    0, 0, 0, 0, 0, 0, 196699, (s32)btlevtcmd_snd_voice,
    -2, 1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ACROBAT_FINISH1", 0, 65545, 90,
    33, 65539, 95, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

static s32 marioAttackEvent_KaitenHammer[] = {
    196699, (s32)btlevtcmd_check_battleflag, -30000000, 2, 131097, -30000000, 0, 196699,
    (s32)btlevtcmd_GetFirstAttackTarget, -29999997, -29999996, 131096, -29999997, -1, 65540, 99,
    33, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0,
    -29999997, -1, 196699, (s32)evt_btl_camera_set_zoom, 0, 300, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 2, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_FaceDirectionSub, -2, -30000000, 250, 327771, (s32)btlevtcmd_SetPos, -2,
    -30000000, -29999999, -29999998, 65545, 30, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -29999988, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997,
    -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997,
    -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999988, 196699,
    (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 196699, (s32)evt_btl_camera_set_mode, 0,
    11, 393307, (s32)evt_btl_camera_set_homing_unitparts, 0, -2, 1, -29999997, -29999996,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 300,
    33, 196699, (s32)btlevtcmd_GetWeaponActionLv, -29999988, -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2,
    -30000000, 65570, -29999988, 65579, (s32)marioWeapon_UltraHammer, 65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer, 589915,
    (s32)btlevtcmd_AcSetParamAll, 10, 8, 0, 0, 0, -250000000, -250000000,
    -250000000, 46, 42, 589915, (s32)btlevtcmd_AcSetParamAll, 7, 15, 0,
    0, 0, -250000000, -250000000, -250000000, 49, 131163, (s32)btlevtcmd_AcSetFlag,
    1, 327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999,
    -250000000, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 30, 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229996928, 131125, -29999998, 5, 458843, (s32)btlevtcmd_GetMoveFrame, -2,
    -30000000, -29999999, -29999998, 0, -29999993, 131126, -29999993, 21,
    131098, -29999993, 0, 131127, -29999993, -1, 65545, -29999993,
    33, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -30000000, -29999998, 1,
    -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 458843, (s32)btlevtcmd_CalculateFaceDirection,
    -2, -1, -29999997, -29999996, 16, -29999985, 196699, (s32)btlevtcmd_ChangeFaceDirection,
    -2, -29999985, 196699, (s32)evt_btl_camera_set_zoom, 0, 350, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999988, 256, -29999993, 131096, -29999993,
    5, 65627, (s32)btlevtcmd_StopAC, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 256, -29999995, 2, 33, 131163, (s32)_get_mario_hammer_lv, -30000000,
    65570, -30000000, 65572, 2, 131122, -30000000, (s32)"M_H_6A", 131122,
    -29999999, (s32)"M_H_6B", 65572, 3, 131122, -30000000, (s32)"M_H_10A", 131122,
    -29999999, (s32)"M_H_10B", 42, 131122, -30000000, (s32)"M_H_2A", 131122, -29999999,
    (s32)"M_H_2B", 49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER2", -250000000, 0,
    -250000000, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, (s32)"p_kaiten_h", 0, 262235,
    (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"P_H_1A", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    -30000000, 196699, (s32)_paper_light_off, -2, 1, 65570, -29999988, 65579,
    (s32)marioWeapon_KaitenHammer, 65579, (s32)marioDefaultWeapon_FirstAttackKaitenHammer, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_KAITEN1", -250000000,
    0, -29999985, 46, 65579, (s32)marioWeapon_UltraHammer, 65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_ULTRA1", -250000000, 0, -29999985, 46, 42,
    49, 65545, 28, 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"P_H_1B",
    131163, (s32)btlevtcmd_StartAC, 1, 65627, (s32)btlevtcmd_ResultAC, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 65570, -29999988, 65579, (s32)marioWeapon_KaitenHammer, 65579,
    (s32)marioDefaultWeapon_FirstAttackKaitenHammer, 131163, (s32)evt_snd_sfxoff, -29999985, 65579, (s32)marioWeapon_UltraHammer, 65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer,
    131163, (s32)evt_snd_sfxoff, -29999985, 46, 46, 49, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999999, 262235, (s32)btlevtcmd_AnimeChangePaperAnime, -2, 1, (s32)"P_H_1C",
    65545, 10, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    131097, -29999993, 1, 131096, -29999993, 3, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 38, 33, 131096, -29999993, 6, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 39, 33, 131096, -29999993, 2, 196699, (s32)btlevtcmd_StartAvoid,
    -29999997, 40, 33, 65540, 90, 33, 131163, (s32)btlevtcmd_GetResultAC,
    -29999994, 131103, -29999994, 2, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, -29999988, 256, -29999995, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -29999988, -1,
    65540, 90, 33, 65570, -29999988, 65579, (s32)marioWeapon_UltraHammer, 65579,
    (s32)marioDefaultWeapon_FirstAttackUltraHammer, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999988, 131328,
    -29999995, 46, 42, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996,
    -29999988, 131328, -29999995, 49, 262235, (s32)btlevtcmd_GetResultPrizeLv, -29999997, 0,
    -29999994, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_AudienceDeclareACResult,
    -29999988, -29999994, 65539, 90, 65627, (s32)btlevtcmd_StopAC, 131163, (s32)btlevtcmd_WeaponAftereffect,
    -29999988, 65570, -29999988, 65579, (s32)marioWeapon_UltraHammer, 65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer, 131122,
    -30000000, 1, 46, 42, 131122, -30000000, 0, 49,
    131096, -30000000, 1, 107, 196699, (s32)_whirlwind_effect, -2, 60,
    109, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -30000000, 131127, -30000000, 36,
    65647, -29999991, 65541, 6, 65570, -29999988, 65579, (s32)marioWeapon_UltraHammer,
    65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_ULTRA2", -250000000, 0,
    -250000000, 46, 49, 65541, 10, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, -30000000, 0, 65545, 1, 6, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 112, 131097, -29999993,
    1, 65545, 50, 65631, -29999991, 110, 131128, -30000000,
    3, 65541, 30, 327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000,
    0, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0,
    0, 0, 112, 65545, 8, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2,
    1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_S",
    65545, 24, 65546, 1500, 32, 786523, (s32)btlevtcmd_SetPartsBlur, -2,
    1, 255, 255, 255, 80, 255, 255, 255,
    0, 0, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 67108864, 107,
    65545, 50, 786523, (s32)btlevtcmd_SetPartsBlur, -2, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 65545,
    10, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, 1, 67108864, 109, 393307,
    (s32)btlevtcmd_ACRStart, -2, 40, 63, 63, 0, 196699, (s32)btlevtcmd_ACRGetResult,
    -29999994, -250000000, 65570, -29999994, 65577, 2, 65631, -29999991,
    327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0, 327771, (s32)_kaiten_hammer_acrobat_rotate,
    -2, 1, 30, (s32)"M_V_2", 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1,
    0, 0, 0, 65545, 30, 42, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999991, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 327771,
    (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0, 65627, (s32)evt_audience_acrobat_notry, 49,
    33, 32, 131097, -29999993, 1, 196699, (s32)btlevtcmd_GetFaceDirection, -2,
    -30000000, 131127, -30000000, 36, 65647, -29999991, 65541, 6,
    65570, -29999988, 65579, (s32)marioWeapon_KaitenHammer, 65579, (s32)marioDefaultWeapon_FirstAttackKaitenHammer, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_MARIO_HAMMER_KAITEN2", -250000000, 0, -250000000, 46, 49, 65541,
    10, 327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000, 0, 65545,
    1, 6, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 112, 65545, 50, 65631, -29999991, 110, 131128,
    -30000000, 3, 65541, 30, 327771, (s32)btlevtcmd_AddRotate, -2, 0,
    -30000000, 0, 65545, 1, 6, 327771, (s32)btlevtcmd_SetRotate, -2,
    0, 0, 0, 112, 65545, 8, 327771, (s32)btlevtcmd_AnimeChangePaperGroup,
    -2, 1, 0, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_I_S", 65545, 24, 65546, 1500, 32, 107, 196699,
    (s32)_whirlwind_effect, -2, 60, 109, 65647, -29999991, 196699, (s32)btlevtcmd_GetFaceDirection,
    -2, -30000000, 131127, -30000000, 36, 65541, 6, 65570,
    -29999988, 65579, (s32)marioWeapon_KaitenHammer, 65579, (s32)marioDefaultWeapon_FirstAttackKaitenHammer, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_MARIO_HAMMER_KAITEN2", -250000000, 0, -250000000, 46, 49, 65541, 10,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, -30000000, 0, 65545, 1,
    6, 6, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, 0,
    112, 393307, (s32)btlevtcmd_ACRStart, -2, 40, 63, 63, 0,
    196699, (s32)btlevtcmd_ACRGetResult, -29999994, -250000000, 65570, -29999994, 65577, 2,
    65631, -29999991, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0,
    327771, (s32)_kaiten_hammer_acrobat_rotate, -2, 1, 30, (s32)"M_V_2", 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult,
    -29999988, 1, 0, 0, 0, 65545, 30, 42,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999991, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0,
    0, 327771, (s32)btlevtcmd_AnimeChangePaperGroup, -2, 1, 0, 0, 65627,
    (s32)evt_audience_acrobat_notry, 49, 33, 33, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1,
    40, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 327771, (s32)btlevtcmd_GetHomePos, -2,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999,
    -29999998, 0, -1, 0, 65570, -29999988, 65579, (s32)marioWeapon_UltraHammer,
    65579, (s32)marioDefaultWeapon_FirstAttackUltraHammer, 46, 42, 65540, 99, 49, 131163,
    (s32)btlevtcmd_GetResultAC, -29999994, 131103, -29999994, 2, 65540, 99, 33,
    131097, -29999993, 1, 65540, 99, 33, 262235, (s32)btlevtcmd_CheckToken,
    -29999997, 32, -30000000, 131096, -30000000, 0, 65540, 99,
    33, 65539, 96, 262235, (s32)btlevtcmd_CheckToken, -29999997, 64, -30000000,
    131096, -30000000, 0, 65545, 1, 65540, 96, 33,
    196699, (s32)btlevtcmd_OffToken, -29999997, 64, 65539, 98, 262235, (s32)btlevtcmd_CheckToken,
    -29999997, 128, -30000000, 131096, -30000000, 0, 262235, (s32)btlevtcmd_CheckToken,
    -2, 256, -30000000, 131096, -30000000, 0, 33, 65545,
    1, 65540, 98, 33, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997,
    -29999996, (s32)marioWeapon_UltraHammerFinish, 131328, -29999995, 65539, 99, 65627, (s32)evt_audience_ap_recovery,
    65627, (s32)btlevtcmd_InviteApInfoReport, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163,
    (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

EVT_BEGIN(marioAttackEvent_FirstAttackKaitenHammer)
    CALL(_get_mario_hammer_lv, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 3)
        SET_VALUE(LW(12), PTR(marioDefaultWeapon_FirstAttackKaitenHammer))
        ELSE
        SET_VALUE(LW(12), PTR(marioDefaultWeapon_FirstAttackUltraHammer))
    END_IF
    CALL_CHILD(PTR(marioAttackEvent_KaitenHammer))
    RETURN
    RETURN
EVT_END()

s32 marioAttackEvent_JishinHammer[] = {
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, 4,
    25, 0, 0, 0, -250000000, -250000000, -250000000, 131163,
    (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    524379, (s32)btlevtcmd_MovePosition, -2, -60, -29999999, -29999998, 0, -1,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0,
    450, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2,
    131122, -30000000, (s32)"M_H_5A", 131122, -29999999, (s32)"M_H_5B", 131122, -29999998,
    (s32)"M_H_14", 65572, 3, 131122, -30000000, (s32)"M_H_9A", 131122, -29999999,
    (s32)"M_H_9B", 131122, -29999998, (s32)"M_H_15", 42, 131122, -30000000, (s32)"M_H_1A",
    131122, -29999999, (s32)"M_H_1B", 131122, -29999998, (s32)"M_H_13", 49, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER2", -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -30000000, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000,
    65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD2", -250000000, 0,
    -250000000, 65572, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD1", -250000000,
    0, -250000000, 42, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD3", -250000000,
    0, -250000000, 49, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, -29999999, 131163, (s32)btlevtcmd_StartAC, 1, 65545, 75, 65647,
    -29999987, 131122, -29999995, 5, 65541, -29999995, 196699, (s32)btlevtcmd_AcGetOutputParam,
    1, -29999994, 131101, -29999994, 3, 7, 33, 65545,
    1, 131122, -29999995, 5, 6, 65545, 25, 112,
    65647, -29999986, 131122, -29999995, 5, 65541, -29999995, 196699,
    (s32)btlevtcmd_AcGetOutputParam, 1, -29999994, 131101, -29999994, 3, 7, 33,
    65545, 1, 131122, -29999995, 5, 6, 65545, 5,
    196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 45, 327771,
    (s32)evt_sub_intpl_init, 11, 0, -29999995, 10, 65541, 10, 65627,
    (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545,
    1, 6, 65545, 8, 327771, (s32)evt_sub_intpl_init, 12, -29999995,
    0, 15, 65541, 15, 65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate,
    -2, 0, 0, -30000000, 65545, 1, 6, 112,
    65647, -29999985, 131122, -29999995, 5, 65541, -29999995, 196699,
    (s32)btlevtcmd_AcGetOutputParam, 1, -29999994, 131101, -29999994, 3, 7, 33,
    65545, 1, 131122, -29999995, 5, 6, 327771, (s32)btlevtcmd_GetPos,
    -2, -29999994, -29999993, -29999992, 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999693,
    458843, (s32)btlevtcmd_JumpPosition, -2, -29999994, -29999993, -29999992, 40, -1,
    112, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999992, 196699, (s32)btlevtcmd_AcGetOutputParam,
    1, -30000000, 131101, -30000000, 3, 65540, 10, 33,
    65631, -29999987, 65631, -29999986, 65631, -29999985, 131163, (s32)_get_mario_hammer_lv,
    -30000000, 65570, -30000000, 65572, 2, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2",
    0, 131122, -29999998, (s32)"M_H_14", 65572, 1, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_MARIO_HAMMER_SWING1", 0, 131122, -29999998, (s32)"M_H_13", 42, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_MARIO_HAMMER_SWING3", 0, 131122, -29999998, (s32)"M_H_15", 49, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999998, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_ATTACK_ULTRAQUAKE1", 0, 65545,
    10, 65540, 40, 65539, 10, 131163, (s32)btlevtcmd_WaitEventEnd, -29999987,
    131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2", 0, 65572, 1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1",
    0, 42, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0, 49, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_ATTACK_ULTRAQUAKE1", 0,
    131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65539, 40,
    196699, (s32)evt_btl_camera_set_mode, 0, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 0,
    196699, (s32)evt_btl_camera_set_zoom, 0, 0, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_ULTRAQUAKE1", 0, 393307, (s32)evt_btl_camera_shake_h, 0, 8, 0,
    42, 13, 131163, (s32)evt_audience_reflesh_natural_all, 100, 131163, (s32)btlevtcmd_GetResultAC, -29999993,
    131102, -29999993, 2, 262235, (s32)btlevtcmd_GetResultPrizeLv, -5, 0, -29999994,
    327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, 0, 50, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33,
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65627,
    (s32)btlevtcmd_StopAC, 65540, 90, 33, 65540, 51, 65539, 50,
    196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997, -1, 65627,
    (s32)btlevtcmd_StopAC, 65540, 90, 33, 65539, 51, 393307, (s32)btlevtcmd_CommandPreCheckDamage,
    -2, -29999997, -29999996, 256, -29999994, 131096, -29999994, 1,
    458843, (s32)btlevtcmd_DamageDirect, -29999997, -29999996, 0, 0, 2, 0,
    107, 65545, 42, 131102, -29999993, 2, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 131328, -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage,
    -2, -29999997, -29999996, 256, -29999995, 33, 109, 32,
    131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38, 33,
    131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 33,
    131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 33,
    33, 65540, 50, 65539, 90, 65545, 12, 196699,
    (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 65545,
    30, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000,
    65545, 60, 65647, -29999985, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    (s32)"M_H_16", 65545, 18, 112, 393307, (s32)btlevtcmd_ACRStart, -2, 0,
    17, 17, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570,
    -29999994, 65577, 2, 42, 65627, (s32)evt_audience_acrobat_notry, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65540, 95, 49,
    196699, (s32)btlevtcmd_AnimeWaitPlayComplete, -2, 1, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 110, 196699, (s32)btlevtcmd_snd_voice, -2,
    1, 327771, (s32)btlevtcmd_SetRotateOffset, -2, 0, 20, 0, 65541,
    60, 327771, (s32)btlevtcmd_AddRotate, -2, 0, 0, 12, 65545,
    1, 6, 112, 110, 65545, 8, 393307, (s32)btlevtcmd_ACRStart,
    -2, 42, 55, 55, 0, 112, 110, 65545,
    4, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_Z_1", 112, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3A", 196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796,
    327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition,
    -2, -30000000, -29999999, -29999998, 60, -1, 65545, 4,
    196699, (s32)btlevtcmd_ACRGetResult, -30000000, -29999999, 131096, -30000000, 2, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3B", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999999, 50, 983131, (s32)evt_eff, (s32)"_BTLEF",
    (s32)"confetti", 3, -30000000, -29999999, -29999998, 90, 0, 0,
    0, 0, 0, 0, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2,
    -29999988, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0, 0,
    65546, 1500, 33, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 65539,
    95, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed,
    -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771,
    (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2,
    -30000000, -29999999, -29999998, 0, -1, 0, 65539, 99,
    131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2,
    2, 1,
};

s32 marioAttackEvent_UltraJishinHammer[] = {
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, 4,
    16, 0, 0, 0, -250000000, -250000000, -250000000, 131163,
    (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 196699,
    (s32)btlevtcmd_SetMoveSpeed, -2, -229996928, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42,
    524379, (s32)btlevtcmd_MovePosition, -2, -60, -29999999, -29999998, 0, -1,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4, 196699, (s32)evt_btl_camera_set_zoom, 0,
    450, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2,
    131122, -30000000, (s32)"M_H_5A", 131122, -29999999, (s32)"M_H_5B", 131122, -29999998,
    (s32)"M_H_13", 65572, 3, 131122, -30000000, (s32)"M_H_9A", 131122, -29999999,
    (s32)"M_H_9B", 131122, -29999998, (s32)"M_H_14", 42, 131122, -30000000, (s32)"M_H_1A",
    131122, -29999999, (s32)"M_H_1B", 131122, -29999998, (s32)"M_H_15", 49, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -30000000, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570,
    -30000000, 65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD2", -250000000,
    0, -250000000, 65572, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD1",
    -250000000, 0, -250000000, 42, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD3",
    -250000000, 0, -250000000, 49, 65545, 30, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -29999999, 131163, (s32)btlevtcmd_StartAC, 1, 65545, 32,
    65647, -29999987, 131122, -29999995, 5, 65541, -29999995, 196699,
    (s32)btlevtcmd_AcGetOutputParam, 1, -29999994, 131101, -29999994, 2, 7, 33,
    65545, 1, 131122, -29999995, 5, 6, 65545, 44,
    112, 65647, -29999986, 131122, -29999995, 5, 65541, -29999995,
    196699, (s32)btlevtcmd_AcGetOutputParam, 1, -29999994, 131101, -29999994, 2, 7,
    33, 65545, 1, 131122, -29999995, 5, 6, 65545,
    10, 196699, (s32)btlevtcmd_GetFaceDirection, -2, -29999995, 131127, -29999995, 45,
    327771, (s32)evt_sub_intpl_init, 11, 0, -29999995, 10, 65541, 15,
    65627, (s32)evt_sub_intpl_get_value, 327771, (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000,
    65545, 1, 6, 65545, 14, 327771, (s32)evt_sub_intpl_init, 12,
    -29999995, 0, 15, 65541, 15, 65627, (s32)evt_sub_intpl_get_value, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, -30000000, 65545, 1, 6,
    112, 65647, -29999985, 131122, -29999995, 5, 65541, -29999995,
    196699, (s32)btlevtcmd_AcGetOutputParam, 1, -29999994, 131101, -29999994, 2, 7,
    33, 65545, 1, 131122, -29999995, 5, 6, 327771,
    (s32)btlevtcmd_GetPos, -2, -29999994, -29999993, -29999992, 196699, (s32)btlevtcmd_SetFallAccel, -2,
    -229999755, 458843, (s32)btlevtcmd_JumpPosition, -2, -29999994, -29999993, -29999992, 55,
    -1, 112, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -29999992, 196699,
    (s32)btlevtcmd_AcGetOutputParam, 1, -30000000, 131101, -30000000, 2, 65540, 10,
    33, 65631, -29999987, 65631, -29999986, 65631, -29999985, 131163,
    (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_MARIO_HAMMER_SWING2", 0, 131122, -29999998, (s32)"M_H_13", 65572, 1, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1", 0, 131122, -29999998, (s32)"M_H_15", 42, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0, 131122, -29999998, (s32)"M_H_14", 49, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_ATTACK_ULTRAQUAKE1", 0,
    65545, 10, 65540, 40, 65539, 10, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999987, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2", 0, 65572, 1, 196699, (s32)evt_snd_sfxon,
    (s32)"SFX_MARIO_HAMMER_SWING1", 0, 42, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0, 49,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_ATTACK_ULTRAQUAKE1",
    0, 131163, (s32)btlevtcmd_WaitEventEnd, -29999986, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65539,
    40, 196699, (s32)evt_btl_camera_set_mode, 0, 1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    0, 196699, (s32)evt_btl_camera_set_zoom, 0, 0, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_ULTRAQUAKE1", 0, 393307, (s32)evt_btl_camera_shake_h, 0, 8,
    0, 42, 13, 131163, (s32)evt_audience_reflesh_natural_all, 100, 131163, (s32)btlevtcmd_GetResultAC,
    -29999993, 131102, -29999993, 2, 262235, (s32)btlevtcmd_GetResultPrizeLv, -5, 0,
    -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994, 0, 50, 0, 196699,
    (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1,
    33, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65627, (s32)btlevtcmd_StopAC, 65540, 90, 33, 65540, 51, 65539,
    50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997, -1,
    65627, (s32)btlevtcmd_StopAC, 65540, 90, 33, 65539, 51, 393307,
    (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994, 131096, -29999994,
    1, 458843, (s32)btlevtcmd_DamageDirect, -29999997, -29999996, 0, 0, 2,
    0, 107, 65545, 42, 131102, -29999993, 2, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328, -29999995, 32, 393307,
    (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256, -29999995, 33, 109,
    32, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 38,
    33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 39,
    33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997, 40,
    33, 33, 65540, 50, 65539, 90, 65545, 12,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1,
    65545, 30, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 65545, 60, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_H_16", 65545, 10, 65539, 95,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000,
    -29999999, -29999998, 0, -1, 0, 65539, 99, 131163,
    (s32)btlevtcmd_ResetFaceDirection, -2, 65630, (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

EVT_BEGIN(marioAttackEvent_HammerRotate)
    SET_VALUE(LW(0), -25)
    CALL(btlevtcmd_SetPartsRotateOffset, -2, 3, 0, 12, 0)
    LABEL(0)
    CALL(btlevtcmd_AddPartsRotate, -2, 3, 0, 0, LW(0))
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

s32 marioAttackEvent_HammerNageru[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65540,
    99, 33, 262235, (s32)btlevtcmd_AttackDeclare, -2, -29999997, -29999996, 65627,
    (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, 5,
    40, 0, 0, 0, -250000000, -250000000, -250000000, 131163,
    (s32)btlevtcmd_AcSetFlag, 0, 327771, (s32)btlevtcmd_SetupAC, -2, 3, 1, 0,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256, -29999994,
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999985,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999985, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 4,
    196699, (s32)evt_btl_camera_set_zoom, 0, 450, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER2",
    -250000000, 0, -250000000, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000,
    65572, 2, 131122, -30000000, (s32)"M_H_5A", 131122, -29999999, (s32)"M_H_5B",
    131122, -29999998, (s32)"M_H_7", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 3, (s32)"M_H_8",
    65572, 3, 131122, -30000000, (s32)"M_H_9A", 131122, -29999999, (s32)"M_H_9B",
    131122, -29999998, (s32)"M_H_11", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 3, (s32)"M_H_12",
    42, 131122, -30000000, (s32)"M_H_1A", 131122, -29999999, (s32)"M_H_1B", 131122,
    -29999998, (s32)"M_H_3", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 3, (s32)"M_H_4", 49,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -30000000, 131163, (s32)_get_mario_hammer_lv, -30000000,
    65570, -30000000, 65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD2",
    -250000000, 0, -250000000, 65572, 1, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_MARIO_HAMMER_HOLD1", -250000000, 0, -250000000, 42, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_MARIO_HAMMER_HOLD3", -250000000, 0, -250000000, 49, 65545, 30, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999999, 131163, (s32)btlevtcmd_StartAC, 1, 65627,
    (s32)btlevtcmd_ResultAC, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    1, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_NAGERU1", 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 3, 131165,
    (s32)marioAttackEvent_HammerNageru_object, -29999985, 393307, (s32)btlevtcmd_ACRStart, -2, 0, 15, 15,
    0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993, 65570, -29999994, 65577,
    2, 42, 65627, (s32)evt_audience_acrobat_notry, 65546, 1000, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, (s32)"M_S_1", 65546, 667, 65540, 94, 49,
    110, 196699, (s32)btlevtcmd_snd_voice, -2, 1, 327771, (s32)btlevtcmd_SetRotateOffset, -2,
    0, 20, 0, 65541, 30, 327771, (s32)btlevtcmd_AddRotate, -2,
    0, 0, -24, 65545, 1, 6, 112, 110,
    65545, 8, 393307, (s32)btlevtcmd_ACRStart, -2, 12, 25, 25,
    0, 112, 110, 65545, 4, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_Z_1", 112, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3A",
    196699, (s32)btlevtcmd_SetFallAccel, -2, -229999796, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000,
    -29999999, -29999998, 458843, (s32)btlevtcmd_JumpPosition, -2, -30000000, -29999999, -29999998,
    30, -1, 65545, 4, 196699, (s32)btlevtcmd_ACRGetResult, -30000000, -29999999,
    131096, -30000000, 2, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_A_3B",
    327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 131125, -29999999,
    50, 983131, (s32)evt_eff, (s32)"_BTLEF", (s32)"confetti", 3, -30000000, -29999999,
    -29999998, 90, 0, 0, 0, 0, 0, 0,
    0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -29999988, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988,
    1, 0, 0, 0, 65546, 1500, 33, 65539,
    94, 131163, (s32)btlevtcmd_WaitEventEnd, -29999985, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport,
    65539, 95, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 196699, (s32)evt_btl_camera_set_moveSpeedLv,
    0, 5, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

EVT_BEGIN(marioAttackEvent_HammerNageru_object)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    ADD(LW(1), 25)
    CALL(btlevtcmd_SetPartsPos, -2, 3, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_OffPartsAttribute, -2, 3, 16777216)
    SET_VALUE(LW(0), -25)
    CALL(btlevtcmd_SetPartsRotate, -2, 3, 0, 0, 0)
    SPAWN_EVENT_GET_ID(PTR(marioAttackEvent_HammerRotate), LW(13))
    CALL(btlevtcmd_JumpPartsSetting, -2, 3, 0, FLOAT(6.0f), FLOAT(0.34960938f))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPartsPosition, -2, 3, LW(0), LW(1), LW(2), 0, -1)
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        CALL(btlevtcmd_JumpPartsContinue, -2, 3)
        CALL(btlevtcmd_WeaponAftereffect, LW(12))
        CALL(btlevtcmd_GetPartsPos, -2, 3, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), -30)
        CALL(btlevtcmd_JumpPartsPosition, -2, 3, LW(0), LW(1), LW(2), 20, -1)
        CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), -15)
        CALL(btlevtcmd_JumpPartsPosition, -2, 3, LW(0), LW(1), LW(2), 12, -1)
        DELETE_EVENT(LW(13))
        WAIT_FRAMES(30)
        CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
        GOTO(90)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_btl_camera_set_mode, 0, 1)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
        CALL(evt_btl_camera_set_zoom, 0, 0)
        CALL(evt_btl_camera_off_posoffset_manual, 0)
    END_INLINE_EVENT
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 131328, LW(5))
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), LW(6))
        ELSE
        CALL(btlevtcmd_CommandCheckDamage, -2, LW(3), LW(4), 256, LW(5))
        CALL(btlevtcmd_CommandGetWeaponAddress, -2, LW(0))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(0), -1)
    END_IF
    CALL(btlevtcmd_GetDamage, LW(3), LW(0))
    CALL(evt_btl_camera_shake_h, 0, LW(0), 0, 10, 13)
    DELETE_EVENT(LW(13))
    CALL(btlevtcmd_OnPartsAttribute, -2, 3, 16777216)
    WAIT_FRAMES(20)
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    RETURN
EVT_END()

s32 marioAttackEvent_FireNaguri[] = {
    131163, (s32)btlevtcmd_AttackDeclareAll, -2, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_RunDataEventChild, -2, 7, 65630, (s32)marioAttackEvent_MajinaiPowerUpCheck, 131163, (s32)btlevtcmd_CommandGetWeaponActionLv,
    -30000000, 196699, (s32)btlevtcmd_AcSetDifficulty, -2, -30000000, 589915, (s32)btlevtcmd_AcSetParamAll, 0,
    83, 63, 83, -250000000, -250000000, -250000000, -250000000, 131163,
    (s32)btlevtcmd_AcSetFlag, 16, 327771, (s32)btlevtcmd_SetupAC, -2, 11, 1, 0,
    65545, 2, 196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit,
    0, -2, -2, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699,
    (s32)evt_btl_camera_set_zoom, 0, 200, 327771, (s32)evt_btl_camera_set_posoffset, 0, 40, 0,
    0, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, 25, 262235, (s32)btlevtcmd_GetStageSize, -250000000, -29999999,
    -250000000, 393307, (s32)btlevtcmd_SetPartsPos, -2, 3, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 3, (s32)"M_H_8", 327771, (s32)btlevtcmd_SetPartsWork, -2,
    3, 0, 1, 110, 196699, (s32)_mario_fire_ball_controll, -2, 3,
    112, 327771, (s32)btlevtcmd_GetPos, -2, -250000000, -29999999, -250000000, 131125,
    -29999999, 140, 65647, -29999985, 720987, (s32)btlevtcmd_DivePartsPosition, -2, 3,
    -30000000, -29999999, -29999998, 60, 0, 5, 0, -1,
    112, 65539, 10, 262235, (s32)btlevtcmd_PadCheckNow, 0, 262144, -30000000,
    131096, -30000000, 0, 65545, 1, 65540, 10, 33,
    131178, -29999985, -30000000, 131097, -30000000, 0, 65631, -29999985,
    33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_VOICE_MARIO_POWER2", -250000000, 0, -250000000,
    131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572, 2, 131122,
    -30000000, (s32)"M_H_18A", 131122, -29999999, (s32)"M_H_18B", 131122, -29999998, (s32)"M_H_18C",
    65572, 3, 131122, -30000000, (s32)"M_H_19A", 131122, -29999999, (s32)"M_H_19B",
    131122, -29999998, (s32)"M_H_19C", 42, 131122, -30000000, (s32)"M_H_17A", 131122,
    -29999999, (s32)"M_H_17B", 131122, -29999998, (s32)"M_H_17C", 49, 262235, (s32)btlevtcmd_AnimeChangePose,
    -2, 1, -30000000, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000,
    65572, 2, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD2", -250000000, 0,
    -250000000, 65572, 1, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD1", -250000000,
    0, -250000000, 42, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_MARIO_HAMMER_HOLD3", -250000000,
    0, -250000000, 49, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_MARIO_HAMMER_FIRE1", -250000000,
    0, -29999985, 65644, -29999986, 393307, (s32)btlevtcmd_GetPartsPos, -2, 3,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998,
    393307, (s32)btlevtcmd_JumpPartsSetting, -2, 3, 0, -229995904, -229999796, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_MARIO_HAMMER_FIRE3", -250000000, 0, -250000000, 458843, (s32)btlevtcmd_FallPartsPosition,
    -2, 3, -30000000, -29999999, -29999998, 75, 109, 131163,
    (s32)btlevtcmd_StartAC, 1, 65545, 20, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1,
    -29999999, 65627, (s32)btlevtcmd_ResultAC, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131103, -30000000,
    2, 196699, (s32)btlevtcmd_AcGetOutputParam, 0, -30000000, 110, 131163, (s32)_get_mario_hammer_lv,
    -30000000, 65570, -30000000, 65572, 2, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2",
    0, 65572, 1, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1", 0, 42,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0, 49, 131163, (s32)evt_snd_sfxoff, -29999985,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_MARIO_HAMMER_FIRE2", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998, 65545, 7, 65545, 60,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_S_1", 112, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999986, 327771, (s32)btlevtcmd_SetPartsWork, -2, 3, 0, 0, 65627,
    (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 393307, (s32)btlevtcmd_GetPartsPos, -2, 3, -30000000,
    -29999999, -29999998, 983131, (s32)evt_eff64, (s32)"", (s32)"fire_spark_n64", 0, -30000000,
    -29999999, -29999998, 30, 40, -229998976, 12, 100, -229998976,
    -229998976, 0, 131125, -29999999, 5, 983131, (s32)evt_eff, (s32)"",
    (s32)"kemuri_test", 11, -30000000, -29999999, -29999998, -229998976, 0, 0,
    0, 0, 0, 0, 0, 196699, (s32)evt_btl_camera_set_mode, 0,
    1, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    0, 131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 196699, (s32)btlevtcmd_GetUnitId, -2, -29999994,
    196699, (s32)btlevtcmd_GetEnemyBelong, -29999994, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -5, -30000000,
    (s32)badgeWeapon_FireNaguriFailed, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 15, 131096,
    -29999997, -1, 65540, 17, 33, 131096, -29999997, -29999994,
    65540, 16, 33, 65539, 16, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 65540, 15, 65539, 17, 196699, (s32)btlevtcmd_GetUnitId, -2,
    -29999994, 196699, (s32)btlevtcmd_GetEnemyBelong, -29999994, -30000000, 262235, (s32)btlevtcmd_SamplingEnemy, -5,
    -30000000, (s32)badgeWeapon_FireNaguriFailed, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 65539, 20,
    131096, -29999997, -1, 65540, 22, 33, 131097, -29999997,
    -29999994, 65540, 21, 33, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997,
    -29999996, 256, -29999995, 65539, 21, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997,
    -29999996, 65540, 20, 65539, 22, 65545, 30, 65540,
    99, 33, 131163, (s32)_get_mario_hammer_lv, -30000000, 65570, -30000000, 65572,
    2, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING2", 0, 65572, 1, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING1", 0, 42, 196699, (s32)evt_snd_sfxon, (s32)"SFX_MARIO_HAMMER_SWING3", 0,
    49, 131163, (s32)evt_snd_sfxoff, -29999985, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_MARIO_HAMMER_FIRE2",
    -250000000, 0, -250000000, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, -29999998,
    65545, 7, 65631, -29999986, 196699, (s32)evt_btl_camera_set_mode, 0, 1,
    196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 196699, (s32)evt_btl_camera_set_zoom, 0, 0,
    131163, (s32)evt_btl_camera_off_posoffset_manual, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_MARIO_HAMMER_FIRE4", -250000000,
    0, -250000000, 131165, (s32)marioAttackEvent_FireNaguri_object, -29999985, 393307, (s32)btlevtcmd_ACRStart, -2,
    0, 15, 15, 0, 196699, (s32)btlevtcmd_ACRGetResult, -29999994, -29999993,
    65570, -29999994, 65577, 2, 65541, 20, 327771, (s32)btlevtcmd_AddRotate,
    -2, 0, 36, 0, 65545, 1, 6, 327771,
    (s32)btlevtcmd_SetRotate, -2, 0, 0, 0, 196699, (s32)btlevtcmd_snd_voice, -2,
    1, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_V_2", 196699, (s32)btlevtcmd_CommandGetWeaponAddress,
    -2, -29999988, 393307, (s32)btlevtcmd_AudienceDeclareAcrobatResult, -29999988, 1, 0, 0,
    0, 65546, 500, 42, 65627, (s32)evt_audience_acrobat_notry, 65545, 60,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_S_1", 49, 131163, (s32)btlevtcmd_WaitEventEnd,
    -29999985, 65627, (s32)evt_audience_ap_recovery, 65627, (s32)btlevtcmd_InviteApInfoReport, 196699, (s32)evt_btl_camera_set_mode, 0,
    0, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 1, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"M_W_1", 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229993856, 262235, (s32)btlevtcmd_AnimeChangePoseType,
    -2, 1, 40, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0,
    -1, 0, 65539, 99, 131163, (s32)btlevtcmd_ResetFaceDirection, -2, 65630,
    (s32)btldefaultevt_SuitoruBadgeEffect, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};

s32 marioAttackEvent_FireNaguri_object[] = {
    196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997, -1, 65627,
    (s32)btlevtcmd_StopAC, 393307, (s32)btlevtcmd_GetPartsPos, -2, 3, -30000000, -29999999, -29999998,
    262235, (s32)btlevtcmd_GetStageSize, -29999995, -250000000, -250000000, 131127, -29999995, 2,
    262235, (s32)btlevtcmd_FaceDirectionAdd, -2, -30000000, -29999995, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    3, 0, -229993856, -229999693, 458843, (s32)btlevtcmd_FallPartsPosition, -2, 3,
    -30000000, -29999999, -29999998, 0, 327771, (s32)btlevtcmd_SetPartsWork, -2, 3,
    0, 0, 2, 33, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_FaceDirectionAdd, -29999997, -30000000, 20,
    262235, (s32)btlevtcmd_TransStageFloorPosition, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    3, 0, -229995904, -229999488, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, 3,
    -30000000, -29999999, -29999998, 0, -1, 327771, (s32)btlevtcmd_SetPartsWork, -2,
    3, 0, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163,
    (s32)btlevtcmd_WeaponAftereffect, -30000000, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102, -30000000, 2,
    262235, (s32)btlevtcmd_GetResultPrizeLv, -5, 0, -29999994, 327771, (s32)btlevtcmd_ACSuccessEffect, -29999994,
    0, 50, 0, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 196699,
    (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -29999994, 32, 196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000,
    196699, (s32)btlevtcmd_AudienceDeclareACResult, -30000000, -1, 33, 393307, (s32)btlevtcmd_GetPartsPos, -2,
    3, -29999993, -29999992, -29999991, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1,
    -1, -1, 2, -29999988, 131127, -29999988, 16, 131122,
    -29999987, 5, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996, 131096, -29999997,
    -1, 65627, (s32)btlevtcmd_StopAC, 65540, 90, 33, 65540, 51,
    65539, 50, 196699, (s32)btlevtcmd_GetSelectNextEnemy, -29999997, -29999996, 131096, -29999997,
    -1, 65627, (s32)btlevtcmd_StopAC, 65540, 90, 33, 65539, 51,
    393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -29999989, -250000000, -250000000, 458843,
    (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -1, -1, 2, -29999986, 131101,
    -29999986, 0, 131100, -29999993, -29999989, 65545, 6, 131125,
    -29999993, -29999988, 107, 327771, (s32)_fire_wave, -29999993, -29999992, -29999991,
    -29999987, 109, 65540, 51, 33, 32, 131101, -29999993,
    -29999989, 65545, 6, 131125, -29999993, -29999988, 107, 327771,
    (s32)_fire_wave, -29999993, -29999992, -29999991, -29999987, 109, 65540, 51,
    33, 33, 393307, (s32)btlevtcmd_CommandPreCheckDamage, -2, -29999997, -29999996, 256,
    -29999994, 131096, -29999994, 1, 131163, (s32)btlevtcmd_GetResultAC, -30000000, 131102,
    -30000000, 2, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 131328,
    -29999995, 32, 393307, (s32)btlevtcmd_CommandCheckDamage, -2, -29999997, -29999996, 256,
    -29999995, 33, 131101, -29999987, 2, 131126, -29999987, 1,
    33, 32, 131096, -29999994, 3, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    38, 33, 131096, -29999994, 6, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    39, 33, 131096, -29999994, 2, 196699, (s32)btlevtcmd_StartAvoid, -29999997,
    40, 33, 33, 65540, 50, 65539, 90, 65539,
    92, 458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -1, -1, 2,
    -29999990, 262235, (s32)btlevtcmd_GetStageSize, -29999989, -250000000, -250000000, 131127, -29999989,
    -29999990, 131101, -29999989, 0, 131100, -29999993, -29999989, 65545,
    6, 131125, -29999993, -29999988, 107, 327771, (s32)_fire_wave, -29999993,
    -29999992, -29999991, -29999987, 109, 65540, 92, 33, 32,
    131101, -29999993, -29999989, 65545, 6, 131125, -29999993, -29999988,
    107, 327771, (s32)_fire_wave, -29999993, -29999992, -29999991, -29999987, 109,
    65540, 92, 33, 33, 2, 1,
};

EVT_BEGIN(_NormalCharge_core)
    CALL(btlevtcmd_GetUnitId, -2, LW(3))
    CALL(btlevtcmd_GetBodyId, -2, LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_PayWeaponCost, -2, LW(12))
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    WAIT_FRAMES(45)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, -2, 0, 24, 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_CHARGE1"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(5))
    DIVIDE(LW(5), 2)
    ADD(LW(1), LW(5))
    ADD(LW(2), 10)
    CALL(evt_eff64, STRING("noname"), STRING("crystal_n64"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 60, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(12), 256, LW(5))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(_SuperCharge_core)
    CALL(btlevtcmd_GetUnitId, -2, LW(3))
    CALL(btlevtcmd_GetBodyId, -2, LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_RunDataEventChild, -2, 7)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(12))
    CALL(btlevtcmd_AnimeChangePoseType, -2, 1, 42)
    WAIT_FRAMES(45)
    LOOP(30)
        CALL(btlevtcmd_AddRotate, -2, 0, 24, 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_SUPER_CHARGE1"), 0)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHeight, -2, LW(5))
    DIVIDE(LW(5), 2)
    ADD(LW(1), LW(5))
    ADD(LW(2), 10)
    CALL(evt_eff64, STRING("noname"), STRING("crystal_n64"), 7, LW(0), LW(1), LW(2), FLOAT(1.5f), 60, 0, 0, 0, 0, 0, 0)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(12), 256, LW(5))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_GatsunJump)
    SET_VALUE(LW(12), PTR(badgeWeapon_GatsunJump))
    CALL_CHILD(PTR(marioAttackEvent_GatsuDokaJump))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_DokanJump)
    SET_VALUE(LW(12), PTR(badgeWeapon_DokanJump))
    CALL_CHILD(PTR(marioAttackEvent_GatsuDokaJump))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_MiniminiFumi)
    CALL_CHILD(PTR(marioAttackEvent_NormalJump))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_NemuraseFumi)
    CALL_CHILD(PTR(marioAttackEvent_NormalJump))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_FunyafunyaJump)
    CALL_CHILD(PTR(marioAttackEvent_NormalJump))
    RETURN
EVT_END()

static EVT_BEGIN(marioAttackEvent_NormalHammer)
    SET_VALUE(LW(14), 0)
    CALL_CHILD(PTR(marioAttackEvent_NormalHammer_Core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_GatsunHammer)
    SET_VALUE(LW(14), 1)
    CALL_CHILD(PTR(marioAttackEvent_NormalHammer_Core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_IceNaguri)
    SET_VALUE(LW(14), 0)
    CALL_CHILD(PTR(marioAttackEvent_NormalHammer_Core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_TsuranukiHammer)
    SET_VALUE(LW(14), 1)
    CALL_CHILD(PTR(marioAttackEvent_NormalHammer_Core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_NormalCharge)
    SET_VALUE(LW(12), PTR(badgeWeapon_Charge))
    CALL_CHILD(PTR(_NormalCharge_core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_NormalChargeP)
    SET_VALUE(LW(12), PTR(badgeWeapon_ChargeP))
    CALL_CHILD(PTR(_NormalCharge_core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_SuperCharge)
    SET_VALUE(LW(12), PTR(badgeWeapon_SuperCharge))
    CALL_CHILD(PTR(_SuperCharge_core))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_SuperChargeP)
    SET_VALUE(LW(12), PTR(badgeWeapon_SuperChargeP))
    CALL_CHILD(PTR(_SuperCharge_core))
    RETURN
EVT_END()

static const Vec majinai_effect_pos = {0.0f, 10.0f, 0.0f};

EVT_BEGIN(marioAttackEvent_MajinaiPowerUpCheck)
    CALL(_majinai_powerup_check, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(evt_majinai_effect_se_btl))
    CALL(_battle_majinai_effect, -3)
    CALL_CHILD(PTR(marioAttackEvent_MajinaiJump))
    CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, STRING("btl_msg_mj_power_up"), 60)
    WAIT_FRAMES(60)
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_MajinaiJump)
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_SetFallAccel, -2, FLOAT(0.5f))
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetBodyId, -2, LW(6))
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(6), 44)
    CALL(btlevtcmd_JumpPosition, -2, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_AnimeChangePoseType, -2, LW(6), 35)
    RETURN
EVT_END()

EVT_BEGIN(_MajinaiPoseReset)
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_MajinaiDefenceUp)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(evt_majinai_effect_se_btl))
    CALL(_battle_majinai_effect, -3)
    CALL_CHILD(PTR(marioAttackEvent_MajinaiJump))
    CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, STRING("btl_msg_mj_defence_up"), 60)
    WAIT_FRAMES(60)
    CALL_CHILD(PTR(_MajinaiPoseReset))
    RETURN
EVT_END()

EVT_BEGIN(marioAttackEvent_MajinaiExpUp)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(evt_majinai_effect_se_btl))
    CALL(_battle_majinai_effect, -3)
    CALL_CHILD(PTR(marioAttackEvent_MajinaiJump))
    CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, STRING("btl_msg_mj_exp_up"), 60)
    WAIT_FRAMES(60)
    RETURN
EVT_END()
















#define BW(wp, off, T) (*(T*)((u8*)(wp) + (off)))

static USER_FUNC(_get_mario_hammer_lv) {
    s32 ret = *event->args;
    evtSetValue(event, ret, *(s8*)((u8*)pouchGetPtr() + 0x99));
    return EVT_RETURN_DONE;
}

USER_FUNC(_whirlwind_effect) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 arg1 = evtGetValue(event, args[1]);
    BattleUnit* unit;
    EffectEntry* eff;
    f32 pos[3];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos[0], &pos[1], &pos[2]);
    eff = effWhirlwindN64Entry(unit->faceDirection < 0, 0, arg1, unit->mSizeMultiplier);
    ((f32*)eff->userdata)[2] = pos[0];
    ((f32*)eff->userdata)[3] = pos[1];
    ((f32*)eff->userdata)[4] = pos[2];
    return EVT_RETURN_DONE;
}

USER_FUNC(_jump_star_effect) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id = evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]);
    s32 step;
    f32 rot;
    f32 dx;
    f32 size;
    f32 pos[3];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    step = event->userdata[0] / 4;
    if (event->userdata[0] % 4 == 0) {
        if (unit->faceDirection >= 0) {
            rot = 10.0f;
            dx = -10.0f;
        } else {
            rot = -10.0f;
            dx = 10.0f;
        }
        BtlUnit_GetPos(unit, &pos[0], &pos[1], &pos[2]);
        pos[0] += dx * unit->mSizeMultiplier;
        pos[1] += (f32)(step * 8 / 10);
        size = 0.1f * step + 0.8f;
        if (size > 2.0f) {
            size = 2.0f;
        }
        effEnergyEntry(type, 50, pos[0], pos[1], pos[0], size, rot, 0.05f);
    }
    if (event->userdata[0] <= 24) {
        event->userdata[0]++;
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_bgset_iron_frame_check) {
    s32 ret = *event->args;
    if (*((u8*)_battleWorkPointer + 0x180DC) & 0x20) {
        evtSetValue(event, ret, 0);
    } else {
        evtSetValue(event, ret, 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_wait_jyabara_hit_iron_frame) {
    BattleUnit* unit;
    f32 pos[3];
    s32 id = evtGetValue(event, *event->args);
    unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));
    BtlUnit_GetPos(unit, &pos[0], &pos[1], &pos[2]);
    if (pos[1] + BtlUnit_GetHeight(unit) < 130.0f) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_SetPos(unit, pos[0], 130 - BtlUnit_GetHeight(unit), pos[2]);
    return EVT_RETURN_DONE;
}

EffectEntry* effKamekiTornadeN64Entry(s32 a, s32 b, f32 x, f32 y, f32 z, f32 scale);
void psndSFX_pos(s32 id, Vec* position);

USER_FUNC(_tatsumaki_effect) {
    BattleWork* wp = _battleWorkPointer;
    s32* ud = event->userdata;
    BattleUnit* unit;
    s32 id = evtGetValue(event, *event->args);
    f32 r;
    f32 dx;
    f32 ang;
    f32 dz;
    Vec v;
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (isFirstCall) {
        ud[0] = 0;
    }
    switch (ud[0]) {
    case 0:
        ud[0]++;
        ud[1] = 0;
        ud[2] = (s32) * (f32*)((u8*)unit + 0x3C);
        ud[3] = (s32) * (f32*)((u8*)unit + 0x40) - 40;
        ud[4] = (s32) * (f32*)((u8*)unit + 0x44);
        ud[5] = (s32)effKamekiTornadeN64Entry(0, 90, ud[2], ud[3], ud[4], 3.0f);
        ud[6] = (s32)effKamekiTornadeN64Entry(0, 90, ud[2], ud[3], ud[4], 3.0f);
        ud[7] = ((s32(*)(const char*))psndSFXOn)("SFX_BTL_JUMP_TATUMAKI2\000");
        v.x = ud[2];
        v.y = ud[3];
        v.z = ud[4];
        psndSFX_pos(ud[7], &v);
    case 1:
        ud[1]++;
        r = ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, 80.0f, 5, ud[1], 90);
        ang = ud[1] * 4;
        dx = r * cosfd(ang);
        dz = r * sinfd(ang);
        ((f32*)((EffectEntry*)ud[5])->userdata)[1] = ud[2] + dx;
        ((f32*)((EffectEntry*)ud[5])->userdata)[2] = ud[3];
        ((f32*)((EffectEntry*)ud[5])->userdata)[3] = ud[4] + dz;
        ((f32*)((EffectEntry*)ud[6])->userdata)[1] = ud[2] - dx;
        ((f32*)((EffectEntry*)ud[6])->userdata)[2] = ud[3];
        ((f32*)((EffectEntry*)ud[6])->userdata)[3] = ud[4] - dz;
        if (ud[1] >= 90) {
            psndSFXOff(ud[7]);
            return EVT_RETURN_DONE;
        }
        break;
    default:
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_record_renzoku_count) {
    s32 n = evtGetValue(event, *event->args);
    u8* base = (u8*)_battleWorkPointer + 0x10000;
    PouchData* pouch = pouchGetPtr();
    if (n > *(u8*)(base + 0x6F24)) {
        if (n > *(u16*)((u8*)pouch + 0x9E)) {
            *(u16*)((u8*)pouch + 0x9E) = n;
            BattleAudience_Case_JumpNewRecord();
        }
        if (n > 100) {
            n = 100;
        }
        *(u8*)(base + 0x6F24) = n;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(mario_get_renzoku_count_max) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 count = evtGetValue(event, args[1]);
    s32 ret = args[2];
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s32 max;
    if (unit == NULL) {
        evtSetValue(event, ret, 0);
        return EVT_RETURN_DONE;
    }
    max = *(u16*)((u8*)unit->mKindParams + 0x14);
    if (count < max) {
        evtSetValue(event, ret, max);
        return EVT_RETURN_DONE;
    }
    if (count >= max * 2) {
        evtSetValue(event, ret, count);
        return EVT_RETURN_DONE;
    }
    if (irand(100) < 33) {
        evtSetValue(event, ret, count + 1);
    } else {
        evtSetValue(event, ret, count);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_hammer_star_effect) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id = evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]);
    f32 angle;
    f32 rot;
    f32 pos[3];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (unit->faceDirection >= 0) {
        angle = ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(210.0f, 420.0f, 1, event->userdata[0], 12);
        rot = -10.0f;
    } else {
        angle = ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(150.0f, -60.0f, 1, event->userdata[0], 12);
        rot = 10.0f;
    }
    BtlUnit_GetPos(unit, &pos[0], &pos[1], &pos[2]);
    pos[1] += unit->mSizeMultiplier * (0.85f * BtlUnit_GetHeight(unit));
    pos[0] += unit->mSizeMultiplier * (26.0f * -sinfd(angle));
    pos[1] += unit->mSizeMultiplier * (26.0f * cosfd(angle));
    effEnergyEntry(type, 30, pos[0], pos[1], pos[0], 0.08f * event->userdata[0] + 0.1f, rot, 0.05f);
    if (event->userdata[0] < 12) {
        event->userdata[0]++;
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_kaiten_hammer_acrobat_rotate) {
    BattleUnit* unit;
    BattleUnitPart* part;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 n;
    s32 anim;
    f32 rx, ry, rz;
    s32 id = evtGetValue(event, args[0]);
    s32 pn;
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    pn = evtGetValue(event, args[1]);
    part = BtlUnit_GetPartsPtr(unit, pn);
    n = evtGetValue(event, args[2]);
    anim = evtGetValue(event, args[3]);
    if (isFirstCall) {
        BtlUnit_GetRotate(unit, &rx, &ry, &rz);
        event->userdata[0] = n;
        if (unit->faceDirection >= 0) {
            f32 a = reviseAngle(ry);
            event->userdata[1] = 360.0f + (360.0f - a);
        } else {
            event->userdata[1] = 360.0f + reviseAngle(ry);
        }
        event->userdata[2] = unit->faceDirection * event->userdata[1] / n;
        event->field_84 = 0;
    }
    BtlUnit_AddRotate(unit, 0, event->userdata[2], 0);
    event->userdata[0]--;
    if ((s32)event->field_84 == 0) {
        event->userdata[1] -= event->userdata[2];
        if (event->userdata[1] <= 270) {
            event->field_84 = 1;
            BtlUnit_SetAnim(part, anim);
        }
    }
    if (event->userdata[0] > 0) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_SetRotate(unit, 0, 0, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(_mario_fire_ball_controll) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 partId = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, partId);
    EffectEntry* eff;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = (s32)effFireEntry(5, 0, 0, 0, (f32){1.0f}, 1000);
    }
    eff = (EffectEntry*)event->userdata[1];
    if (*(s32*)((u8*)part + 0x130) == 0) {
        effDelete(eff);
        return EVT_RETURN_DONE;
    }
    {
        f32* p = (f32*)eff->userdata;
        BtlUnit_GetPartsPos(part, &p[1], &p[2], &p[3]);
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_fire_wave) {
    s32* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);
    f32 scale = 0.6f * evtGetValue(event, args[3]);
    if (isFirstCall) {
        event->userdata[0] = (s32)effHibashiraEntry(0, 1, 90, x, y, z, x, y, z, scale);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_majinai_powerup_check) {
    BattleWork* wp = _battleWorkPointer;
    s32 ret = *event->args;
    if (*(u8*)((u8*)pouchGetPtr() + 0x5BA) != 1) {
        evtSetValue(event, ret, 0);
    } else {
        evtSetValue(event, ret, 1);
        *((u8*)wp + 0x18FE1) = 1;
        BattleMajinaiDone();
        BattleMajinaiEndCheck();
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_battle_majinai_effect) {
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    if (isFirstCall) {
        Vec v = majinai_effect_pos;
        event->userdata[0] = (s32)effMajinaiEntry(0, v.x, v.y, v.z);
        effSetName((EffectEntry*)event->userdata[0], "mjef_coinup");
    }
    if (event->userdata[0] && effNameToPtr("mjef_coinup")) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_paper_light_off) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 part;
    id = BattleTransID(event, id);
    part = evtGetValue(event, args[1]);
    animPoseSetMaterialLightFlagOff(BattleGetUnitPartsPtr(id, part)->poseId, 1);
    return EVT_RETURN_DONE;
}
