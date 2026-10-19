#include "main.h"

#include "mario/mariost.h"
#include "sdk/DEMOInit.h"

extern GlobalWork* gp;

int main(void) {
    OSTick base_tick;

    marioStInit();
    marioStMain();
    while (1) {
        base_tick = OSGetTick();
        DEMOBeforeRender();
        marioStDisp();
        marioStMain();
        gp->mDeltaGame = OSGetTick() - base_tick;
        DEMODoneRender();
        gp->mDeltaRender = OSGetTick() - base_tick;
    }

    return 0;
}

// >>> nmpoolhost.py generated: NONMATCHING-only pool definitions
#ifdef NONMATCHING
#pragma force_active on
// src/driver/animdrv.c (48)
__declspec(section ".rodata") const char str_802C2A98[12] = "joint_00\0\0\0";
__declspec(section ".rodata") const char str_802C2AA4[16] = "jointdai1_A01\0\0";
__declspec(section ".rodata") const char str_802C2AB4[16] = "jointdai1_A02\0\0";
__declspec(section ".rodata") const char str_802C2AC4[16] = "jointdai1_A03\0\0";
__declspec(section ".rodata") const char str_802C2AD4[16] = "jointdai1_A04\0\0";
__declspec(section ".rodata") const char str_802C2AE4[16] = "jointdai1_A05\0\0";
__declspec(section ".rodata") const char str_802C2AF4[16] = "jointdai1_B01\0\0";
__declspec(section ".rodata") const char str_802C2B04[16] = "jointdai1_B02\0\0";
__declspec(section ".rodata") const char str_802C2B14[16] = "jointdai1_B03\0\0";
__declspec(section ".rodata") const char str_802C2B24[16] = "jointdai1_B04\0\0";
__declspec(section ".rodata") const char str_802C2B34[16] = "jointdai1_B05\0\0";
__declspec(section ".rodata") const char str_802C2B44[16] = "jointdai1_C01\0\0";
__declspec(section ".rodata") const char str_802C2B54[16] = "jointdai1_C02\0\0";
__declspec(section ".rodata") const char str_802C2B64[16] = "jointdai1_C03\0\0";
__declspec(section ".rodata") const char str_802C2B74[16] = "jointdai1_C04\0\0";
__declspec(section ".rodata") const char str_802C2B84[16] = "jointdai1_C05\0\0";
__declspec(section ".rodata") const char str_802C2B94[16] = "jointdai2_01\0\0\0";
__declspec(section ".rodata") const char str_802C2BA4[16] = "jointdai2_02\0\0\0";
__declspec(section ".rodata") const char str_802C2BB4[16] = "jointdai2_03\0\0\0";
__declspec(section ".rodata") const char str_802C2BC4[16] = "jointdai2_04\0\0\0";
__declspec(section ".rodata") const char str_802C2BD4[16] = "jointdai2_05\0\0\0";
__declspec(section ".rodata") const char str_802C2BE4[16] = "jointdai2_06\0\0\0";
__declspec(section ".rodata") const char str_802C2BF4[16] = "jointdai2_07\0\0\0";
__declspec(section ".rodata") const char str_802C2C04[20] = "jointdai2_upper01\0\0";
__declspec(section ".rodata") const char str_802C2C18[20] = "jointdai2_upper02\0\0";
__declspec(section ".rodata") const char str_802C2C2C[20] = "jointdai2_upper03\0\0";
__declspec(section ".rodata") const char str_802C2C40[20] = "jointdai2_upper04\0\0";
__declspec(section ".rodata") const char str_802C2C54[20] = "jointdai2_lower01\0\0";
__declspec(section ".rodata") const char str_802C2C68[20] = "jointdai2_lower02\0\0";
__declspec(section ".rodata") const char str_802C2C7C[20] = "jointdai2_lower03\0\0";
__declspec(section ".rodata") const char str_802C2C90[20] = "jointdai2_lower04\0\0";
__declspec(section ".rodata") const char str_802C2CA4[16] = "jointasi_A01\0\0\0";
__declspec(section ".rodata") const char str_802C2CB4[16] = "jointasi_A02\0\0\0";
__declspec(section ".rodata") const char str_802C2CC4[16] = "jointasi_A03\0\0\0";
__declspec(section ".rodata") const char str_802C2CD4[16] = "jointasi_A04\0\0\0";
__declspec(section ".rodata") const char str_802C2CE4[16] = "jointasi_B01\0\0\0";
__declspec(section ".rodata") const char str_802C2CF4[16] = "jointasi_B02\0\0\0";
__declspec(section ".rodata") const char str_802C2D04[16] = "jointasi_B03\0\0\0";
__declspec(section ".rodata") const char str_802C2D14[16] = "jointasi_B04\0\0\0";
__declspec(section ".rodata") const char str_802C2D24[16] = "jointasi_C01\0\0\0";
__declspec(section ".rodata") const char str_802C2D34[16] = "jointasi_C02\0\0\0";
__declspec(section ".rodata") const char str_802C2D44[16] = "jointasi_C03\0\0\0";
__declspec(section ".rodata") const char str_802C2D54[16] = "jointasi_C04\0\0\0";
__declspec(section ".rodata") const char str_802C2D64[16] = "jointasi_D01\0\0\0";
__declspec(section ".rodata") const char str_802C2D74[16] = "jointasi_D02\0\0\0";
__declspec(section ".rodata") const char str_802C2D84[16] = "jointasi_D03\0\0\0";
__declspec(section ".rodata") const char str_802C2D94[16] = "jointasi_D04\0\0\0";
__declspec(section ".rodata") const char str_802C2DA4[12] = "joint_core\0";

// src/driver/npcdrv.c (23)
__declspec(section ".rodata") const char str_802C2FC8[] = "SFX_EVT_FLD_INCANT_CUBE1\0\0\0";
__declspec(section ".rodata") const char str_802C2FE4[] = "SFX_EVT_FLD_INCANT_CUBE2\0\0\0";
__declspec(section ".rodata") const char str_802C3000[] = "SFX_EVT_FLD_INCANT_CUBE3\0\0\0";
__declspec(section ".rodata") const char str_802C301C[] = "SFX_EVT_FLD_INCANT_CUBE4\0\0\0";
__declspec(section ".rodata") const char str_802C3038[] = "SFX_EVT_FLD_INCANT_CUBE5\0\0\0";
__declspec(section ".rodata") const char str_802C3054[] = "SFX_EVT_BTL_INCANT_CUBE1\0\0\0";
__declspec(section ".rodata") const char str_802C3070[] = "SFX_EVT_BTL_INCANT_CUBE2\0\0\0";
__declspec(section ".rodata") const char str_802C308C[] = "SFX_EVT_BTL_INCANT_CUBE3\0\0\0";
__declspec(section ".rodata") const char str_802C30A8[] = "SFX_EVT_BTL_INCANT_CUBE4\0\0\0";
__declspec(section ".rodata") const char str_802C30C4[] = "SFX_EVT_BTL_INCANT_CUBE5\0\0\0";
__declspec(section ".rodata") const char str_802C30E0[] = "msg_mj_coin_up\0";
__declspec(section ".rodata") const char str_802C30F0[] = "msg_mj_last";
__declspec(section ".rodata") const char str_802C30FC[] = "a_magu\0";
__declspec(section ".rodata") const char str_802C3104[] = "kpa_03\0";
__declspec(section ".rodata") const char str_802C310C[] = "SFX_KUPPA_3RD_WATER_FALL1\0\0";
__declspec(section ".rodata") const char str_802C3128[] = "mjef_coinup";
__declspec(section ".rodata") const char str_802C3158[] = "fb_sensei_shita";
__declspec(section ".rodata") const char str_802C3168[] = "fb_sensei_sareta\0\0\0";
__declspec(section ".rodata") const char str_802C317C[] = "SFX_BTL_FLD_ENEMY_DAMAGED1\0";
__declspec(section ".rodata") const char str_802C3198[] = "SFX_BTL_FLD_MARIO_DAMAGED1\0";
__declspec(section ".rodata") const char str_802C31C0[] = "(^x^)party\0";
__declspec(section ".rodata") const char str_802C31CC[] = "extparty\0\0\0";
__declspec(section ".rodata") const char str_802C31E0[] = "c_luigi";

// src/mario/mario_hit.c (9)
__declspec(section ".rodata") const char str_802C5940[] = "dou_10\0";
__declspec(section ".rodata") const char str_802C5948[] = "eki_04\0";
__declspec(section ".rodata") const char str_802C5950[] = "MOBJ_PowerUpBlock\0\0";
__declspec(section ".rodata") const char str_802C5964[] = "MOBJ_SaveBlock\0";
__declspec(section ".rodata") const char str_802C5974[] = "MOBJ_RecoveryBlock\0";
__declspec(section ".rodata") const char str_802C5988[] = "MOBJ_CoinTakenRecoveryBlock";
__declspec(section ".rodata") const char str_802C59A4[] = "MOBJ_HiddenHatenaBlock\0";
__declspec(section ".rodata") const char str_802C59BC[] = "MOBJ_HiddenBadgeBlock\0\0";
__declspec(section ".rodata") const char str_802C59D4[] = "MOBJ_Hidden10CountBlock";

// src/motion/mot_ship.c (10)
__declspec(section ".rodata") const char str_802C5E00[] = "SFX_MARIO_SHIP1_1\0\0";
__declspec(section ".rodata") const char str_802C5E14[] = "SFX_MARIO_SHIP2";
__declspec(section ".rodata") const char str_802C5E24[] = "p_hune\0";
__declspec(section ".rodata") const char str_802C5E2C[] = "p_hune_g\0\0\0";
__declspec(section ".rodata") const char str_802C5E38[] = "p_hune_y\0\0\0";
__declspec(section ".rodata") const char str_802C5E44[] = "p_hune_v\0\0\0";
__declspec(section ".rodata") const char str_802C5E58[] = "M_J_1B\0";
__declspec(section ".rodata") const char str_802C5E60[] = "PM_H_1A";
__declspec(section ".rodata") const char str_802C5E68[] = "dou_03\0";
__declspec(section ".rodata") const char str_802C5E70[] = "PM_H_1B";

// src/party.c (15)
__declspec(section ".rodata") const char str_802CCD60[12] = "c_babyyoshi";
__declspec(section ".rodata") const char str_802CCD6C[15] = "c_babyyoshi2\0\0\0";
__declspec(section ".rodata") const char str_802CCD7C[15] = "c_babyyoshi3\0\0\0";
__declspec(section ".rodata") const char str_802CCD8C[15] = "c_babyyoshi4\0\0\0";
__declspec(section ".rodata") const char str_802CCD9C[15] = "c_babyyoshi5\0\0\0";
__declspec(section ".rodata") const char str_802CCDAC[15] = "c_babyyoshi6\0\0\0";
__declspec(section ".rodata") const char str_802CCDBC[15] = "c_babyyoshi7\0\0\0";
__declspec(section ".rodata") const char str_802CCEEC[8] = "d_mario";
__declspec(section ".rodata") const char str_802CCF08[8] = "PM_D_1B";
__declspec(section ".rodata") const char str_802CCF10[11] = "p_dokan_y\0\0";
__declspec(section ".rodata") const char str_802CCF1C[7] = "p_roll\0";
__declspec(section ".rodata") const char str_802CCF24[8] = "p_plane";
__declspec(section ".rodata") const char str_802CCF2C[11] = "p_dokan_x\0\0";
__declspec(section ".rodata") const char str_802CCF38[7] = "p_slit\0";
__declspec(section ".rodata") const char str_802CCF40[8] = "PM_D_1A";

// src/mario/mario_pouch.c (1)
__declspec(section ".rodata") const char str_802CE170[12] = "name_party3";

// src/battle/battle_seq.c (40)
__declspec(section ".rodata") const char str_802EF310[] = "stg3_tou_cp_001";
__declspec(section ".rodata") const char str_802EF320[] = "stg3_tou_cp_002";
__declspec(section ".rodata") const char str_802EF330[] = "stg3_tou_cp_004";
__declspec(section ".rodata") const char str_802EF340[] = "stg3_tou_cp_008";
__declspec(section ".rodata") const char str_802EF350[] = "stg3_tou_cp_000";
__declspec(section ".rodata") const char str_802EF360[] = "stg3_tou_cp_005";
__declspec(section ".rodata") const char str_802EF370[] = "stg3_tou_cp_006";
__declspec(section ".rodata") const char str_802EF380[] = "stg3_tou_cp_009";
__declspec(section ".rodata") const char str_802EF390[] = "stg3_tou_cp_003";
__declspec(section ".rodata") const char str_802EF3A0[] = "stg3_tou_cp_007";
__declspec(section ".rodata") const char str_802EF3B0[] = "stg3_tou_cp_011";
__declspec(section ".rodata") const char str_802EF3C0[] = "stg3_tou_cp_012";
__declspec(section ".rodata") const char str_802EF3D0[] = "stg3_tou_cp_014";
__declspec(section ".rodata") const char str_802EF3E0[] = "stg3_tou_cp_019";
__declspec(section ".rodata") const char str_802EF3F0[] = "stg3_tou_cp_020";
__declspec(section ".rodata") const char str_802EF400[] = "stg3_tou_cp_010";
__declspec(section ".rodata") const char str_802EF410[] = "stg3_tou_cp_018";
__declspec(section ".rodata") const char str_802EF420[] = "stg3_tou_cp_015";
__declspec(section ".rodata") const char str_802EF430[] = "stg3_tou_cp_016";
__declspec(section ".rodata") const char str_802EF440[] = "stg3_tou_cp_021";
__declspec(section ".rodata") const char str_802EF450[] = "stg3_tou_cp_013";
__declspec(section ".rodata") const char str_802EF460[] = "stg3_tou_cp_017";
__declspec(section ".rodata") const char str_802EF470[] = "stg3_tou_cp_024";
__declspec(section ".rodata") const char str_802EF480[] = "stg3_tou_cp_023";
__declspec(section ".rodata") const char str_802EF490[] = "stg3_tou_cp_022";
__declspec(section ".rodata") const char str_802EF4A0[] = "stg3_tou_cp_041";
__declspec(section ".rodata") const char str_802EF4B0[] = "stg3_tou_cp_042";
__declspec(section ".rodata") const char str_802EF4C0[] = "stg3_tou_cp_044";
__declspec(section ".rodata") const char str_802EF4D0[] = "stg3_tou_cp_049";
__declspec(section ".rodata") const char str_802EF4E0[] = "stg3_tou_cp_050";
__declspec(section ".rodata") const char str_802EF4F0[] = "stg3_tou_cp_040";
__declspec(section ".rodata") const char str_802EF500[] = "stg3_tou_cp_048";
__declspec(section ".rodata") const char str_802EF510[] = "stg3_tou_cp_045";
__declspec(section ".rodata") const char str_802EF520[] = "stg3_tou_cp_046";
__declspec(section ".rodata") const char str_802EF530[] = "stg3_tou_cp_051";
__declspec(section ".rodata") const char str_802EF540[] = "stg3_tou_cp_043";
__declspec(section ".rodata") const char str_802EF550[] = "stg3_tou_cp_047";
__declspec(section ".rodata") const char str_802EF560[] = "stg3_tou_cp_054";
__declspec(section ".rodata") const char str_802EF570[] = "stg3_tou_cp_053";
__declspec(section ".rodata") const char str_802EF580[] = "stg3_tou_cp_052";

// src/window/win_mario.c (29)
__declspec(section ".rodata") const char str_802F5650[20] = "msg_menu_mario_lv\0\0";
__declspec(section ".rodata") const char str_802F5664[24] = "msg_menu_mario_star_r\0\0";
__declspec(section ".rodata") const char str_802F567C[20] = "msg_menu_mario_hp\0\0";
__declspec(section ".rodata") const char str_802F5690[20] = "msg_menu_mario_fp\0\0";
__declspec(section ".rodata") const char str_802F56A4[20] = "msg_menu_mario_bp\0\0";
__declspec(section ".rodata") const char str_802F56B8[12] = "msg_slit\0\0\0";
__declspec(section ".rodata") const char str_802F56C4[12] = "msg_plane\0\0";
__declspec(section ".rodata") const char str_802F56D0[12] = "msg_ship\0\0\0";
__declspec(section ".rodata") const char str_802F56DC[12] = "msg_roll\0\0\0";
__declspec(section ".rodata") const char str_802F56E8[20] = "msg_menu_star_power";
__declspec(section ".rodata") const char str_802F56FC[20] = "msg_menu_mario_waza";
__declspec(section ".rodata") const char str_802F5710[24] = "msg_menu_mario_star_p\0\0";
__declspec(section ".rodata") const char str_802F5728[20] = "msg_menu_mario_coin";
__declspec(section ".rodata") const char str_802F573C[24] = "msg_menu_mario_kakera\0\0";
__declspec(section ".rodata") const char str_802F5754[24] = "msg_menu_mario_scoin\0\0\0";
__declspec(section ".rodata") const char str_802F576C[20] = "msg_menu_mario_time";
__declspec(section ".rodata") const char str_802F5780[16] = "msg_hammer_1\0\0\0";
__declspec(section ".rodata") const char str_802F5790[16] = "msg_hammer_2\0\0\0";
__declspec(section ".rodata") const char str_802F57A0[16] = "msg_hammer_3\0\0\0";
__declspec(section ".rodata") const char str_802F57B0[12] = "msg_boots_1";
__declspec(section ".rodata") const char str_802F57BC[12] = "msg_boots_2";
__declspec(section ".rodata") const char str_802F57C8[12] = "msg_boots_3";
__declspec(section ".sdata2") const char str_8041D578[8] = "M_S_1\0\0";
__declspec(section ".sdata2") const char str_8041D580[4] = "S_1";
__declspec(section ".sdata2") const char str_8041D584[8] = "M_H_1\0\0";
__declspec(section ".sdata2") const char str_8041D58C[4] = "R_1";
__declspec(section ".sdata2") const char str_8041D590[8] = "M_R_1\0\0";
__declspec(section ".sdata2") const char str_8041D598[8] = "M_H_4\0\0";
__declspec(section ".sdata2") const char str_8041D5A0[8] = "M_H_7\0\0";

// src/event/evt_win.c (14)
__declspec(section ".rodata") const char str_802F68B0[8] = "%s_%04d";
__declspec(section ".sdata2") const char str_8041D958[8] = "_kur\0\0\0";
__declspec(section ".sdata2") const char str_8041D960[8] = "_nok\0\0\0";
__declspec(section ".sdata2") const char str_8041D968[8] = "_win\0\0\0";
__declspec(section ".sdata2") const char str_8041D970[8] = "_yos\0\0\0";
__declspec(section ".sdata2") const char str_8041D978[8] = "_viv\0\0\0";
__declspec(section ".sdata2") const char str_8041D980[8] = "_bom\0\0\0";
__declspec(section ".sdata2") const char str_8041D988[8] = "_chu\0\0\0";
__declspec(section ".sdata2") const char str_8041D990[4] = "_hp";
__declspec(section ".sdata2") const char str_8041D994[4] = "_fp";
__declspec(section ".sdata2") const char str_8041D998[4] = "_bp";
__declspec(section ".sdata2") const char str_8041D99C[8] = "\x82g\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D9A4[8] = "\x82" "e\x82o\0\0\0";
__declspec(section ".sdata2") const char str_8041D9AC[8] = "\x82" "a\x82o\0\0\0";
#pragma force_active reset
#endif
// <<< nmpoolhost.py generated
