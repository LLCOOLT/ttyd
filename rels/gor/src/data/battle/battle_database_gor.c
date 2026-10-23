#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "gor.h"

#pragma force_active on

extern s32 unit_boss_kanbu1[];
extern s32 unit_lecture_christine[];

__declspec(section ".data") u64 fd_battle_database_gor_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_gor_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_gor___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_gor___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_gor_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_gor___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_gor_one_381[1];
__declspec(section ".data") u64 fd_battle_database_gor_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_gor_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_gor___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_gor___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_gor_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_gor___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_gor_one_364[1];
s32 gor_btlobject_data[36];
s32 gor_btlstage_data[218];
__declspec(section ".data") s32 btlparty_gor_gor_00_01_off_1[12];
__declspec(section ".data") s32 btlgrp_gor_gor_00_01_off_1[8];
__declspec(section ".data") s32 btlparty_gor_gor_02_ac_lecture[12];
__declspec(section ".data") s32 btlgrp_gor_gor_02_ac_lecture[8];
__declspec(section ".data") s32 btlparty_gor_gor_02_sac_lecture[12];
__declspec(section ".data") s32 btlgrp_gor_gor_02_sac_lecture[8];
__declspec(section ".data") s32 btlparty_gor_gor_02_01_off_1[12];
__declspec(section ".data") s32 btlgrp_gor_gor_02_01_off_1[8];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_00_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_aclec_off[6];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_saclec_off[6];
__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_01_off[6];
s32 btlsetup_gor_tbl[119];
s32 btl_gor_setup_no_tbl[14];

__declspec(section ".data") u64 fd_battle_database_gor_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gor_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gor___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gor___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gor_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gor___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gor_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_gor_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gor_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gor___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gor___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gor_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gor___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gor_one_364[] = {
    1065353216,
};

s32 gor_btlobject_data[] = {
    (s32)"A1", 131072, 1107558400, 0, -1035993088, 3932160, (s32)"A2", 131073,
    0, 0, 1116602368, 3932160, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160,
};

s32 gor_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_00_0", 4, (s32)gor_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603120, 268435456, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_00_4", 2,
    (s32)(void*)((u8*)gor_btlobject_data + 0x60), 0, 0, 0, 0, 1677721602, 0, 0,
    (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 34603119, 536870912, 1704706, 0, 0, 2047,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 100, 0,
    0, 0, 0, 0, 0, 1677721602, 0, 0,
    (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 34603104, 536870912, 1704706, 0, 0, 2047,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 100, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

__declspec(section ".data") s32 btlparty_gor_gor_00_01_off_1[] = {
    (s32)unit_boss_kanbu1, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kanbu1,
};

__declspec(section ".data") s32 btlgrp_gor_gor_00_01_off_1[] = {
    1, (s32)btlparty_gor_gor_00_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_gor_gor_02_ac_lecture[] = {
    (s32)unit_lecture_christine, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_gor_gor_02_ac_lecture[] = {
    1, (s32)btlparty_gor_gor_02_ac_lecture, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_gor_gor_02_sac_lecture[] = {
    (s32)unit_lecture_frankli_sac, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_gor_gor_02_sac_lecture[] = {
    1, (s32)btlparty_gor_gor_02_sac_lecture, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_gor_gor_02_01_off_1[] = {
    (s32)unit_monban, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monban,
};

__declspec(section ".data") s32 btlgrp_gor_gor_02_01_off_1[] = {
    1, (s32)btlparty_gor_gor_02_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_test1_off[] = {
    50, (s32)btlgrp_gor_gor_02_01_off_1, (s32)gor_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_test2_off[] = {
    50, (s32)btlgrp_gor_gor_02_01_off_1, (s32)(void*)((u8*)gor_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_00_01_off[] = {
    50, (s32)btlgrp_gor_gor_00_01_off_1, (s32)gor_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_aclec_off[] = {
    50, (s32)btlgrp_gor_gor_02_ac_lecture, (s32)(void*)((u8*)gor_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_saclec_off[] = {
    50, (s32)btlgrp_gor_gor_02_sac_lecture, (s32)(void*)((u8*)gor_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gor_btlno_gor_02_01_off[] = {
    50, (s32)btlgrp_gor_gor_02_01_off_1, (s32)(void*)((u8*)gor_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_gor_tbl[] = {
    (s32)/*"マップstg_00_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_gor_btlno_gor_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_00_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x34", 0, 0, -1, 0, (s32)btlgrpsel_gor_btlno_gor_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GOR00 幹部その１"*/"\x47\x4F\x52\x30\x30\x20\x8A\xB2\x95\x94\x82\xBB\x82\xCC\x82\x50", (s32)"gor_00", 0, -1, 0, (s32)btlgrpsel_gor_btlno_gor_00_01_off,
    536870928, 0, 1285, 0, 1285, 0, 0, 0,
    257, 16843009, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"GOR02 ACレクチャー"*/"\x47\x4F\x52\x30\x32\x20\x41\x43\x83\x8C\x83\x4E\x83\x60\x83\x83\x81\x5B", (s32)"gor_02", 0, -1, 0,
    (s32)btlgrpsel_gor_btlno_gor_02_aclec_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"GOR02 SACレクチャー"*/"\x47\x4F\x52\x30\x32\x20\x53\x41\x43\x83\x8C\x83\x4E\x83\x60\x83\x83\x81\x5B", (s32)"gor_02", 0, -1,
    0, (s32)btlgrpsel_gor_btlno_gor_02_saclec_off, 0, 0, 16842752, 0, 0, 0,
    0, 0, 0, 0, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"GOR02 もんばん"*/"\x47\x4F\x52\x30\x32\x20\x82\xE0\x82\xF1\x82\xCE\x82\xF1", (s32)"gor_02", 0,
    -1, 0, (s32)btlgrpsel_gor_btlno_gor_02_01_off, 536870912, 0, 84213760, 0, 1285,
    0, 0, 84213760, 16843009, 16843009, (s32)"BGM_KOBOSS_BATTLE1", 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
};

s32 btl_gor_setup_no_tbl[] = {
    (s32)"BTLNO_GOR_TEST1", 0, (s32)"BTLNO_GOR_TEST2", 1, (s32)"BTLNO_GOR_00_01", 2, (s32)"BTLNO_GOR_02_ACLEC", 3,
    (s32)"BTLNO_GOR_02_SACLEC", 4, (s32)"BTLNO_GOR_02_01", 5, 0, 0,
};

