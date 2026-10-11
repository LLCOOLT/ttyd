#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_item_monochrome__pakkun[];
extern s32 battle_item_monochrome_kurokumorn[];
extern s32 battle_item_monochrome_sinemon[];
extern s32 battle_item_vivian1[];
extern s32 unit_boss_vivian[];
extern s32 unit_monochrome_kurokumorn_30_data_17868[];
extern s32 unit_monochrome_pakkun_30_data_166A8[];
extern s32 unit_monochrome_sinemon_30_data_15620[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_win_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_win_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_win___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_win___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_win_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_win___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_win_one_381[1];
__declspec(section ".data") u64 fd_battle_database_win_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_win_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_win___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_win___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_win_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_win___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_win_one_364[1];
s32 win_btlobject_data[30];
s32 win_btlstage_data[109];
s32 btlparty_win_win_00_01_off_1[24];
__declspec(section ".data") s32 btlgrp_win_win_00_01_off_1[8];
s32 btlparty_win_win_00_01_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_00_01_on_1[8];
s32 btlparty_win_win_00_01_on_2[36];
__declspec(section ".data") s32 btlgrp_win_win_00_01_on_2[8];
s32 btlparty_win_win_00_01_on_3[48];
__declspec(section ".data") s32 btlgrp_win_win_00_01_on_3[8];
s32 btlparty_win_win_00_02_off_1[24];
__declspec(section ".data") s32 btlgrp_win_win_00_02_off_1[8];
s32 btlparty_win_win_00_02_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_00_02_on_1[8];
s32 btlparty_win_win_00_02_on_2[36];
__declspec(section ".data") s32 btlgrp_win_win_00_02_on_2[8];
s32 btlparty_win_win_00_03_off_1[36];
__declspec(section ".data") s32 btlgrp_win_win_00_03_off_1[8];
s32 btlparty_win_win_00_03_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_00_03_on_1[8];
s32 btlparty_win_win_00_03_on_2[24];
__declspec(section ".data") s32 btlgrp_win_win_00_03_on_2[8];
__declspec(section ".data") s32 btlparty_win_win_00_04_off_1[12];
__declspec(section ".data") s32 btlgrp_win_win_00_04_off_1[8];
s32 btlparty_win_win_02_01_off_1[24];
__declspec(section ".data") s32 btlgrp_win_win_02_01_off_1[8];
s32 btlparty_win_win_02_01_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_02_01_on_1[8];
s32 btlparty_win_win_02_01_on_2[36];
__declspec(section ".data") s32 btlgrp_win_win_02_01_on_2[8];
s32 btlparty_win_win_02_01_on_3[36];
__declspec(section ".data") s32 btlgrp_win_win_02_01_on_3[8];
s32 btlparty_win_win_02_02_off_1[24];
__declspec(section ".data") s32 btlgrp_win_win_02_02_off_1[8];
s32 btlparty_win_win_02_02_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_02_02_on_1[8];
s32 btlparty_win_win_02_02_on_2[36];
__declspec(section ".data") s32 btlgrp_win_win_02_02_on_2[8];
s32 btlparty_win_win_02_02_on_3[36];
__declspec(section ".data") s32 btlgrp_win_win_02_02_on_3[8];
s32 btlparty_win_win_03_01_off_1[48];
__declspec(section ".data") s32 btlgrp_win_win_03_01_off_1[8];
s32 btlparty_win_win_03_01_on_1[24];
__declspec(section ".data") s32 btlgrp_win_win_03_01_on_1[8];
s32 btlparty_win_win_03_01_on_2[36];
__declspec(section ".data") s32 btlgrp_win_win_03_01_on_2[8];
s32 btlparty_win_win_03_01_on_3[36];
__declspec(section ".data") s32 btlgrp_win_win_03_01_on_3[8];
s32 btlparty_win_win_03_01_on_4[48];
__declspec(section ".data") s32 btlgrp_win_win_03_01_on_4[8];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_01_on[12];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_01_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_02_on[9];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_02_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_03_on[9];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_03_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_04_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_01_on[12];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_01_off[6];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_02_on[12];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_02_off[6];
s32 btlgrpsel_win_btlno_win_03_01_on[15];
__declspec(section ".data") s32 btlgrpsel_win_btlno_win_03_01_off[6];
s32 btlsetup_win_tbl[153];
s32 btl_win_setup_no_tbl[18];

__declspec(section ".data") u64 fd_battle_database_win_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_win_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_win___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_win___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_win_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_win___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_win_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_win_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_win_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_win___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_win___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_win_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_win___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_win_one_364[] = {
    1065353216,
};

s32 win_btlobject_data[] = {
    (s32)"A1", 131072, 1119354880, 0, -1036517376, 3932160, (s32)"S_hana", 131073,
    1073741824, 0, -1036517376, 3932160, (s32)"S_kusa", 131073, 1073741824, 0,
    1115684864, 3932160, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160,
};

s32 win_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_02_0", 5, (s32)win_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603119, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

s32 btlparty_win_win_00_01_off_1[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_01_off_1[] = {
    2, (s32)btlparty_win_win_00_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_01_on_1[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_01_on_1[] = {
    2, (s32)btlparty_win_win_00_01_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_01_on_2[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_01_on_2[] = {
    3, (s32)btlparty_win_win_00_01_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_01_on_3[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_01_on_3[] = {
    4, (s32)btlparty_win_win_00_01_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_02_off_1[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_02_off_1[] = {
    2, (s32)btlparty_win_win_00_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_02_on_1[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_02_on_1[] = {
    2, (s32)btlparty_win_win_00_02_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_02_on_2[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_02_on_2[] = {
    3, (s32)btlparty_win_win_00_02_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_03_off_1[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_03_off_1[] = {
    3, (s32)btlparty_win_win_00_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_03_on_1[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_win_win_00_03_on_1[] = {
    2, (s32)btlparty_win_win_00_03_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_00_03_on_2[] = {
    (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_00_03_on_2[] = {
    2, (s32)btlparty_win_win_00_03_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_win_win_00_04_off_1[] = {
    (s32)unit_boss_vivian, 16777216, 67108868, 1113325568, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_vivian1,
};

__declspec(section ".data") s32 btlgrp_win_win_00_04_off_1[] = {
    1, (s32)btlparty_win_win_00_04_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_02_01_off_1[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_02_01_off_1[] = {
    2, (s32)btlparty_win_win_02_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_02_01_on_1[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_02_01_on_1[] = {
    2, (s32)btlparty_win_win_02_01_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_02_01_on_2[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_02_01_on_2[] = {
    3, (s32)btlparty_win_win_02_01_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_02_01_on_3[] = {
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_02_01_on_3[] = {
    3, (s32)btlparty_win_win_02_01_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_win_win_02_02_off_1[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_02_02_off_1[] = {
    2, (s32)btlparty_win_win_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_02_02_on_1[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_02_02_on_1[] = {
    2, (s32)btlparty_win_win_02_02_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_02_02_on_2[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_02_02_on_2[] = {
    3, (s32)btlparty_win_win_02_02_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_02_02_on_3[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_02_02_on_3[] = {
    3, (s32)btlparty_win_win_02_02_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_03_01_off_1[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_03_01_off_1[] = {
    4, (s32)btlparty_win_win_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_03_01_on_1[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_03_01_on_1[] = {
    2, (s32)btlparty_win_win_03_01_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_03_01_on_2[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_03_01_on_2[] = {
    3, (s32)btlparty_win_win_03_01_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_03_01_on_3[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_kurokumorn_30_data_17868, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_sinemon_30_data_15620, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_win_win_03_01_on_3[] = {
    3, (s32)btlparty_win_win_03_01_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_win_win_03_01_on_4[] = {
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_30_data_166A8, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_win_win_03_01_on_4[] = {
    4, (s32)btlparty_win_win_03_01_on_4, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_test1_off[] = {
    50, (s32)btlgrp_win_win_00_01_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_01_on[] = {
    20, (s32)btlgrp_win_win_00_01_on_1, (s32)win_btlstage_data, 20, (s32)btlgrp_win_win_00_01_on_2, (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_00_01_on_3,
    (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_01_off[] = {
    10, (s32)btlgrp_win_win_00_01_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_02_on[] = {
    20, (s32)btlgrp_win_win_00_02_on_1, (s32)win_btlstage_data, 20, (s32)btlgrp_win_win_00_02_on_2, (s32)win_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_02_off[] = {
    10, (s32)btlgrp_win_win_00_02_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_03_on[] = {
    20, (s32)btlgrp_win_win_00_03_on_1, (s32)win_btlstage_data, 20, (s32)btlgrp_win_win_00_03_on_2, (s32)win_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_03_off[] = {
    10, (s32)btlgrp_win_win_00_03_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_00_04_off[] = {
    50, (s32)btlgrp_win_win_00_04_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_01_on[] = {
    20, (s32)btlgrp_win_win_02_01_on_1, (s32)win_btlstage_data, 20, (s32)btlgrp_win_win_02_01_on_2, (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_02_01_on_3,
    (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_01_off[] = {
    10, (s32)btlgrp_win_win_02_01_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_02_on[] = {
    20, (s32)btlgrp_win_win_02_02_on_1, (s32)win_btlstage_data, 20, (s32)btlgrp_win_win_02_02_on_2, (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_02_02_on_3,
    (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_02_02_off[] = {
    10, (s32)btlgrp_win_win_02_02_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

s32 btlgrpsel_win_btlno_win_03_01_on[] = {
    10, (s32)btlgrp_win_win_03_01_on_1, (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_03_01_on_2, (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_03_01_on_3,
    (s32)win_btlstage_data, 10, (s32)btlgrp_win_win_03_01_on_4, (s32)win_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_win_btlno_win_03_01_off[] = {
    10, (s32)btlgrp_win_win_03_01_off_1, (s32)win_btlstage_data, 0, 0, 0,
};

s32 btlsetup_win_tbl[] = {
    (s32)/*"マップstg_02_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x32\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_win_btlno_win_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win_00ドクガッスン１"*/"\x77\x69\x6E\x5F\x30\x30\x83\x68\x83\x4E\x83\x4B\x83\x62\x83\x58\x83\x93\x82\x50", 0, 0, -129997318, (s32)btlgrpsel_win_btlno_win_00_01_on, (s32)btlgrpsel_win_btlno_win_00_01_off, 0,
    0, 84213760, 0, 84215045, 0, 84213760, 84215045, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win_00モノクロシンエモン"*/"\x77\x69\x6E\x5F\x30\x30\x83\x82\x83\x6D\x83\x4E\x83\x8D\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -129997318, (s32)btlgrpsel_win_btlno_win_00_02_on, (s32)btlgrpsel_win_btlno_win_00_02_off,
    0, 0, 84213760, 0, 84215045, 0, 84213760, 84215045,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win_00ドクガッスン３"*/"\x77\x69\x6E\x5F\x30\x30\x83\x68\x83\x4E\x83\x4B\x83\x62\x83\x58\x83\x93\x82\x52", 0, 0, -129997318, (s32)btlgrpsel_win_btlno_win_00_03_on,
    (s32)btlgrpsel_win_btlno_win_00_03_off, 0, 0, 84213760, 0, 84215045, 0, 84213760,
    84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win00ビビアン３姉妹"*/"\x77\x69\x6E\x30\x30\x83\x72\x83\x72\x83\x41\x83\x93\x82\x52\x8E\x6F\x96\x85", (s32)"win_00", 0, -1,
    0, (s32)btlgrpsel_win_btlno_win_00_04_off, 536870928, 0, 84213760, 0, 84215045, 0,
    84213760, 84215045, 16843009, 16843009, (s32)"BGM_BOSS_STG3_3WOMEN1", (s32)/*"win_02シンエモン１"*/"\x77\x69\x6E\x5F\x30\x32\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93\x82\x50", 0, 0,
    -129997320, (s32)btlgrpsel_win_btlno_win_02_01_on, (s32)btlgrpsel_win_btlno_win_02_01_off, 0, 0, 84213760, 0, 84215045,
    0, 84213760, 84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win_02パックンフラワー"*/"\x77\x69\x6E\x5F\x30\x32\x83\x70\x83\x62\x83\x4E\x83\x93\x83\x74\x83\x89\x83\x8F\x81\x5B", 0,
    0, -129997320, (s32)btlgrpsel_win_btlno_win_02_02_on, (s32)btlgrpsel_win_btlno_win_02_02_off, 0, 0, 84213760, 0,
    84215045, 0, 84213760, 84216330, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"win_03パックン１"*/"\x77\x69\x6E\x5F\x30\x33\x83\x70\x83\x62\x83\x4E\x83\x93\x82\x50",
    0, 0, -129997319, (s32)btlgrpsel_win_btlno_win_03_01_on, (s32)btlgrpsel_win_btlno_win_03_01_off, 0, 0, 84213760,
    0, 84215045, 0, 84213760, 84216330, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

s32 btl_win_setup_no_tbl[] = {
    (s32)"BTLNO_WIN_TEST1", 0, (s32)"BTLNO_WIN_00_01", 1, (s32)"BTLNO_WIN_00_02", 2, (s32)"BTLNO_WIN_00_03", 3,
    (s32)"BTLNO_WIN_00_04", 4, (s32)"BTLNO_WIN_02_01", 5, (s32)"BTLNO_WIN_02_02", 6, (s32)"BTLNO_WIN_03_01", 7,
    0, 0,
};

