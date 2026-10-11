#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"

static USER_FUNC(_space_rotate);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_item_barriern[];
extern s32 battle_item_barriern_custom[];
extern s32 battle_item_barriern_z[];
extern s32 battle_item_default_param_list[];
extern s32 battle_item_gundan_zako[];
extern s32 battle_item_gundan_zako_elite[];
extern s32 battle_item_gundan_zako_magician[];
extern s32 unit_barriern_2_data_3A830[];
extern s32 unit_barriern_custom[];
extern s32 unit_barriern_z_2_data_303C8[];
extern s32 unit_boss_magnum_battender_mkII[];
extern s32 unit_gundan_zako_2_data_2E898[];
extern s32 unit_gundan_zako_elite[];
extern s32 unit_gundan_zako_magician_2_data_34AD8[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_aji_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_aji_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_aji___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_aji___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_aji_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_aji___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_aji_one_381[1];
__declspec(section ".data") u64 fd_battle_database_aji_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_aji_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_aji___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_aji___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_aji_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_aji___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_aji_one_364[1];
s32 aji_btlobject_data[162];
s32 aji_btlstage_data[763];
__declspec(section ".data") s32 btlparty_aji_aji_mbmkII[12];
__declspec(section ".data") s32 btlgrp_aji_aji_mbmkII[8];
s32 btlparty_aji_aji_zako[24];
__declspec(section ".data") s32 btlgrp_aji_aji_zako[8];
s32 btlparty_aji_aji_01_01_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_01_01_off_1[8];
s32 btlparty_aji_aji_01_02_off_1[36];
__declspec(section ".data") s32 btlgrp_aji_aji_01_02_off_1[8];
s32 btlparty_aji_aji_01_03_off_1[48];
__declspec(section ".data") s32 btlgrp_aji_aji_01_03_off_1[8];
s32 btlparty_aji_aji_01_04_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_01_04_off_1[8];
s32 btlparty_aji_aji_01_05_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_01_05_off_1[8];
s32 btlparty_aji_aji_01_06_off_1[48];
__declspec(section ".data") s32 btlgrp_aji_aji_01_06_off_1[8];
s32 btlparty_aji_aji_01_07_off_1[36];
__declspec(section ".data") s32 btlgrp_aji_aji_01_07_off_1[8];
s32 btlparty_aji_aji_01_08_off_1[48];
__declspec(section ".data") s32 btlgrp_aji_aji_01_08_off_1[8];
s32 btlparty_aji_aji_04_01_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_04_01_off_1[8];
s32 btlparty_aji_aji_06_01_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_06_01_off_1[8];
s32 btlparty_aji_aji_08_01_off_1[36];
__declspec(section ".data") s32 btlgrp_aji_aji_08_01_off_1[8];
s32 btlparty_aji_aji_09_01_off_1[60];
__declspec(section ".data") s32 btlgrp_aji_aji_09_01_off_1[8];
__declspec(section ".data") s32 btlparty_aji_aji_10_01_off_1[12];
__declspec(section ".data") s32 btlgrp_aji_aji_10_01_off_1[8];
s32 btlparty_aji_aji_13_01_off_1[48];
__declspec(section ".data") s32 btlgrp_aji_aji_13_01_off_1[8];
s32 btlparty_aji_aji_13_02_off_1[24];
__declspec(section ".data") s32 btlgrp_aji_aji_13_02_off_1[8];
__declspec(section ".data") s32 btlparty_aji_aji_15_01_off_1[12];
__declspec(section ".data") s32 btlgrp_aji_aji_15_01_off_1[8];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test5_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_mbmkii_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_00_00_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_02_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_03_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_04_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_05_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_06_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_07_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_08_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_04_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_06_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_08_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_09_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_10_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_13_01_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_13_02_off[6];
__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_15_01_off[6];
s32 btlsetup_aji_tbl[408];
s32 btl_aji_setup_no_tbl[48];
s32 bgset_aji_space_event[35];

__declspec(section ".data") u64 fd_battle_database_aji_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_aji_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_aji___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_aji___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_aji_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_aji___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_aji_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_aji_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_aji_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_aji___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_aji___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_aji_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_aji___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_aji_one_364[] = {
    1065353216,
};

s32 aji_btlobject_data[] = {
    (s32)"dentou_01", 131072, 1125122048, 0, -1034420224, 3932160, (s32)"dentou_02", 131072,
    1115684864, 0, -1036255232, 171048960, (s32)"dentou_03", 131072, -1031798784, 0,
    -1036255232, 338165760, (s32)"dentou_04", 131072, -1022361600, 0, -1034420224, 505282560,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"haikei_C_a", 131075,
    0, 0, 0, 3932160, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"A2", 131073, 0, 0, -1030488064, 3932160,
    (s32)"haikei_C_b", 131075, 0, 0, 0, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"A2", 131073, 0, 0,
    -1030488064, 3932160, (s32)"haikei_C_c", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"A2", 131073,
    0, 0, -1030488064, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"A1", 131072, 0, 0, -1041235968, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"A1", 131072, 0, 0, -1034944512, 3932160,
    (s32)"c_ten", 131075, 0, 0, 1098907648, 3932160, (s32)"c_kabe", 131075,
    0, 0, 1098907648, 3932160, (s32)"c_o", 131075, 0, 0,
    1088421888, 3932160, (s32)"space", 131075, 0, 0, 1088421888, 3932160,
    (s32)"star_01", 131075, 0, 0, 1109131264, 3932160, (s32)"star_02", 131075,
    0, 0, 1103626240, 3932160, (s32)"star_03", 131075, 0, 0,
    1106771968, 3932160,
};

s32 aji_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_07_5", 5, (s32)aji_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_07_1", 3,
    (s32)(void*)((u8*)aji_btlobject_data + 0x78), 0, 0, 0, 0, 1677721602, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 34603104, 536870912, 1704706, 0, 0, 2047,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 100, 0,
    0, 0, 0, 0, 0, 1677721602, 0, 0,
    (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 34603104, 536870912, 1704706, 0, 0, 2047,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 100, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, (s32)"bti_01", (s32)"stg_07_1", 3, (s32)(void*)((u8*)aji_btlobject_data + 0xC0), 0, 0,
    0, 0, 1677721602, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 34603104,
    536870912, 1704706, 0, 0, 2047, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 0, 0, 0, 0,
    0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 34603104,
    536870912, 1704706, 0, 0, 2047, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)"bti_01",
    (s32)"stg_07_1", 3, (s32)(void*)((u8*)aji_btlobject_data + 0x108), 0, 0, 0, 0, 1677721602,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)"bti_01", (s32)"stg_07_2", 3, (s32)(void*)((u8*)aji_btlobject_data + 0x198),
    0, 0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 536870912, 1704706, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
    0, 0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 536870912, 1704706, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)"bti_01", (s32)"stg_07_3", 3, (s32)(void*)((u8*)aji_btlobject_data + 0x150), 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603104, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603104, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_07_6",
    7, (s32)(void*)((u8*)aji_btlobject_data + 0x1E0), 0, 0, 0, 0, 1677721602, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 34603104, 536870912, 1704706, 0, 0,
    2047, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 100,
    0, 0, 0, 0, 0, 0, 1677721602, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 34603104, 536870912, 1704706, 0, 0,
    2047, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 100,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)bgset_aji_space_event, 0,
};

__declspec(section ".data") s32 btlparty_aji_aji_mbmkII[] = {
    (s32)unit_boss_magnum_battender_mkII, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_aji_aji_mbmkII[] = {
    1, (s32)btlparty_aji_aji_mbmkII, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_zako[] = {
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_zako[] = {
    2, (s32)btlparty_aji_aji_zako, 0, 0, 100, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_01_off_1[] = {
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_01_off_1[] = {
    2, (s32)btlparty_aji_aji_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_02_off_1[] = {
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_02_off_1[] = {
    3, (s32)btlparty_aji_aji_01_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_03_off_1[] = {
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_03_off_1[] = {
    4, (s32)btlparty_aji_aji_01_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_04_off_1[] = {
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_04_off_1[] = {
    2, (s32)btlparty_aji_aji_01_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_aji_aji_01_05_off_1[] = {
    (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z, (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_magician,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_05_off_1[] = {
    2, (s32)btlparty_aji_aji_01_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_06_off_1[] = {
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_06_off_1[] = {
    4, (s32)btlparty_aji_aji_01_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_07_off_1[] = {
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
    (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1125515264, 1109393408, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_07_off_1[] = {
    3, (s32)btlparty_aji_aji_01_07_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_01_08_off_1[] = {
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_gundan_zako_elite, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_01_08_off_1[] = {
    4, (s32)btlparty_aji_aji_01_08_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_04_01_off_1[] = {
    (s32)unit_barriern_custom, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_custom, (s32)unit_barriern_custom, 16777216, 67108868, 1124204544,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern_custom,
};

__declspec(section ".data") s32 btlgrp_aji_aji_04_01_off_1[] = {
    2, (s32)btlparty_aji_aji_04_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_06_01_off_1[] = {
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_magician,
};

__declspec(section ".data") s32 btlgrp_aji_aji_06_01_off_1[] = {
    2, (s32)btlparty_aji_aji_06_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_aji_aji_08_01_off_1[] = {
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_barriern_2_data_3A830, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_barriern,
    (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1125515264, 1109393408, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_aji_aji_08_01_off_1[] = {
    3, (s32)btlparty_aji_aji_08_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_aji_aji_09_01_off_1[] = {
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_2_data_2E898, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician,
};

__declspec(section ".data") s32 btlgrp_aji_aji_09_01_off_1[] = {
    5, (s32)btlparty_aji_aji_09_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_aji_aji_10_01_off_1[] = {
    (s32)unit_barriern_custom, 16777216, 67108868, 1119092736, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_custom,
};

__declspec(section ".data") s32 btlgrp_aji_aji_10_01_off_1[] = {
    1, (s32)btlparty_aji_aji_10_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_aji_aji_13_01_off_1[] = {
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_magician,
    (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_magician, (s32)unit_gundan_zako_magician_2_data_34AD8, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako_magician,
};

__declspec(section ".data") s32 btlgrp_aji_aji_13_01_off_1[] = {
    4, (s32)btlparty_aji_aji_13_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_aji_aji_13_02_off_1[] = {
    (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z, (s32)unit_barriern_z_2_data_303C8, 16777216, 67108868, 1124204544,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_aji_aji_13_02_off_1[] = {
    2, (s32)btlparty_aji_aji_13_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_aji_aji_15_01_off_1[] = {
    (s32)unit_gundan_zako_elite, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako_elite,
};

__declspec(section ".data") s32 btlgrp_aji_aji_15_01_off_1[] = {
    1, (s32)btlparty_aji_aji_15_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test1_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test2_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)(void*)((u8*)aji_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test3_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)(void*)((u8*)aji_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test4_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)aji_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_test5_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)(void*)((u8*)aji_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_mbmkii_off[] = {
    50, (s32)btlgrp_aji_aji_mbmkII, (s32)(void*)((u8*)aji_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_00_00_off[] = {
    50, (s32)btlgrp_aji_aji_zako, (s32)(void*)((u8*)aji_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_01_off[] = {
    20, (s32)btlgrp_aji_aji_01_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_02_off[] = {
    20, (s32)btlgrp_aji_aji_01_02_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_03_off[] = {
    20, (s32)btlgrp_aji_aji_01_03_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_04_off[] = {
    20, (s32)btlgrp_aji_aji_01_04_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_05_off[] = {
    20, (s32)btlgrp_aji_aji_01_05_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_06_off[] = {
    20, (s32)btlgrp_aji_aji_01_06_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_07_off[] = {
    20, (s32)btlgrp_aji_aji_01_07_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_01_08_off[] = {
    20, (s32)btlgrp_aji_aji_01_08_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_04_01_off[] = {
    20, (s32)btlgrp_aji_aji_04_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_06_01_off[] = {
    20, (s32)btlgrp_aji_aji_06_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_08_01_off[] = {
    20, (s32)btlgrp_aji_aji_08_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_09_01_off[] = {
    20, (s32)btlgrp_aji_aji_09_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_10_01_off[] = {
    20, (s32)btlgrp_aji_aji_10_01_off_1, (s32)aji_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_13_01_off[] = {
    20, (s32)btlgrp_aji_aji_13_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_13_02_off[] = {
    20, (s32)btlgrp_aji_aji_13_02_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_aji_btlno_aji_15_01_off[] = {
    20, (s32)btlgrp_aji_aji_15_01_off_1, (s32)(void*)((u8*)aji_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_aji_tbl[] = {
    (s32)/*"マップstg_07_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_07_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_07_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_07_5"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x35", 0, 0, -1, 0,
    (s32)btlgrpsel_aji_btlno_aji_test4_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_07_6"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x36", 0, 0, -1,
    0, (s32)btlgrpsel_aji_btlno_aji_test5_off, 0, 0, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マグナムバッテンダー幕痛"*/"\x83\x7D\x83\x4F\x83\x69\x83\x80\x83\x6F\x83\x62\x83\x65\x83\x93\x83\x5F\x81\x5B\x96\x8B\x92\xC9", (s32)"aji_14", 0,
    -1, 0, (s32)btlgrpsel_aji_btlno_aji_mbmkii_off, 536870928, 6, 2570, 0, 0,
    0, 0, 0, 16843009, 16843009, (s32)"BGM_BOSS_STG3_3RDLEADER1", (s32)/*"軍団ザコエリート"*/"\x8C\x52\x92\x63\x83\x55\x83\x52\x83\x47\x83\x8A\x81\x5B\x83\x67", 0,
    0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_00_00_off, 536870928, 0, 50530826, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"aji01軍団ザコエリート"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52\x83\x47\x83\x8A\x81\x5B\x83\x67",
    0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_01_off, 0, 0, 50530826,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"aji01軍団ザコ"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_02_off, 0, 0,
    50530826, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01軍団ザコエリート"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52\x83\x47\x83\x8A\x81\x5B\x83\x67", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_03_off, 0,
    0, 50530826, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01軍団ザコ魔法使い"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52\x96\x82\x96\x40\x8E\x67\x82\xA2", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_04_off,
    0, 0, 50530826, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01バリアーンＺ"*/"\x61\x6A\x69\x30\x31\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x82\x79", 0, 0, -1, 0,
    (s32)btlgrpsel_aji_btlno_aji_01_05_off, 0, 0, 50530826, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01軍団ザコエリート"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52\x83\x47\x83\x8A\x81\x5B\x83\x67", 0, 0, -1,
    0, (s32)btlgrpsel_aji_btlno_aji_01_06_off, 0, 0, 50530826, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01軍団ザコ"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52", 0, 0,
    -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_07_off, 0, 0, 50530826, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji01軍団ザコ"*/"\x61\x6A\x69\x30\x31\x8C\x52\x92\x63\x83\x55\x83\x52", 0,
    0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_01_08_off, 0, 0, 50530826, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji04バリアーンカスタム"*/"\x61\x6A\x69\x30\x34\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x83\x4A\x83\x58\x83\x5E\x83\x80",
    0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_04_01_off, 16, 0, 50530826,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"aji06軍団ザコ魔法使い"*/"\x61\x6A\x69\x30\x36\x8C\x52\x92\x63\x83\x55\x83\x52\x96\x82\x96\x40\x8E\x67\x82\xA2", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_06_01_off, 0, 0,
    50530826, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji08軍団ザコ魔法使い"*/"\x61\x6A\x69\x30\x38\x8C\x52\x92\x63\x83\x55\x83\x52\x96\x82\x96\x40\x8E\x67\x82\xA2", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_08_01_off, 0,
    0, 50530826, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji09軍団ザコ"*/"\x61\x6A\x69\x30\x39\x8C\x52\x92\x63\x83\x55\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_09_01_off,
    0, 0, 50530826, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji10バリアーンカスタム"*/"\x61\x6A\x69\x31\x30\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x83\x4A\x83\x58\x83\x5E\x83\x80", 0, 0, -1, 0,
    (s32)btlgrpsel_aji_btlno_aji_10_01_off, 0, 0, 50530826, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji13軍団ザコ魔法使い"*/"\x61\x6A\x69\x31\x33\x8C\x52\x92\x63\x83\x55\x83\x52\x96\x82\x96\x40\x8E\x67\x82\xA2", 0, 0, -1,
    0, (s32)btlgrpsel_aji_btlno_aji_13_01_off, 0, 0, 50530826, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji13バリアーンＺ"*/"\x61\x6A\x69\x31\x33\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x82\x79", 0, 0,
    -1, 0, (s32)btlgrpsel_aji_btlno_aji_13_02_off, 0, 0, 50530826, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"aji15軍団ザコエリート"*/"\x61\x6A\x69\x31\x35\x8C\x52\x92\x63\x83\x55\x83\x52\x83\x47\x83\x8A\x81\x5B\x83\x67", 0,
    0, -1, 0, (s32)btlgrpsel_aji_btlno_aji_15_01_off, 0, 0, 50530826, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s32 btl_aji_setup_no_tbl[] = {
    (s32)"BTLNO_AJI_TEST1", 0, (s32)"BTLNO_AJI_TEST2", 1, (s32)"BTLNO_AJI_TEST3", 2, (s32)"BTLNO_AJI_TEST4", 3,
    (s32)"BTLNO_AJI_TEST5", 4, (s32)"BTLNO_AJI_MBMKII", 5, (s32)"BTLNO_AJI_00_00", 6, (s32)"BTLNO_AJI_01_01", 7,
    (s32)"BTLNO_AJI_01_02", 8, (s32)"BTLNO_AJI_01_03", 9, (s32)"BTLNO_AJI_01_04", 10, (s32)"BTLNO_AJI_01_05", 11,
    (s32)"BTLNO_AJI_01_06", 12, (s32)"BTLNO_AJI_01_07", 13, (s32)"BTLNO_AJI_01_08", 14, (s32)"BTLNO_AJI_04_01", 15,
    (s32)"BTLNO_AJI_06_01", 16, (s32)"BTLNO_AJI_08_01", 17, (s32)"BTLNO_AJI_09_01", 18, (s32)"BTLNO_AJI_10_01", 19,
    (s32)"BTLNO_AJI_13_01", 20, (s32)"BTLNO_AJI_13_02", 21, (s32)"BTLNO_AJI_15_01", 22, 0, 0,
};

EVT_BEGIN(bgset_aji_space_event)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    SET_VALUE(LW(3), 0)
    LABEL(0)
    CALL(_space_rotate, STRING("star_01"), LW(1), 7500)
    CALL(_space_rotate, STRING("star_02"), LW(2), 6750)
    CALL(_space_rotate, STRING("star_03"), LW(3), 6000)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

static USER_FUNC(_space_rotate) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 outVar = args[1];
    s32 step = evtGetValue(event, outVar);
    s32 total = evtGetValue(event, args[2]);
    BattleStageObject* obj = BattleSearchObjectPtr(name);

    obj->mRotation.z = 360.0f * step / total;
    step++;
    if (step >= total) {
        step = 0;
    }
    evtSetValue(event, outVar, step);
    return EVT_RETURN_DONE;
}
