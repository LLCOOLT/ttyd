#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_item_faker_mario[];
extern s32 battle_item_hyper_kuriboo[];
extern s32 battle_item_hyper_patakuri[];
extern s32 battle_item_hyper_sinemon[];
extern s32 battle_item_hyper_togekuri[];
extern s32 battle_item_pansy[];
extern s32 battle_item_twinkling_pansy[];
extern s32 unit_faker_mario_gra[];
extern s32 unit_hyper_kuriboo[];
extern s32 unit_hyper_patakuri[];
extern s32 unit_hyper_sinemon[];
extern s32 unit_hyper_togekuri[];
extern s32 unit_pansy[];
extern s32 unit_twinkling_pansy[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_gra_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_gra_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_gra___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_gra___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_gra_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_gra___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_gra_one_381[1];
__declspec(section ".data") u64 fd_battle_database_gra_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_gra_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_gra___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_gra___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_gra_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_gra___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_gra_one_364[1];
s32 gra_btlobject_data[132];
s32 gra_btlstage_data[218];
__declspec(section ".data") s32 btlparty_gra_gra_00_01_off_1[12];
__declspec(section ".data") s32 btlgrp_gra_gra_00_01_off_1[8];
s32 btlparty_gra_gra_01_01_off_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_01_off_1[8];
s32 btlparty_gra_gra_01_01_on_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_1[8];
s32 btlparty_gra_gra_01_01_on_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_2[8];
s32 btlparty_gra_gra_01_01_on_3[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_3[8];
s32 btlparty_gra_gra_01_03_off_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_03_off_1[8];
s32 btlparty_gra_gra_01_03_on_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_1[8];
s32 btlparty_gra_gra_01_03_on_2[48];
__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_2[8];
s32 btlparty_gra_gra_01_03_on_3[48];
__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_3[8];
s32 btlparty_gra_gra_01_04_off_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_04_off_1[8];
s32 btlparty_gra_gra_01_04_on_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_1[8];
s32 btlparty_gra_gra_01_04_on_2[48];
__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_2[8];
s32 btlparty_gra_gra_01_04_on_3[36];
__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_3[8];
s32 btlparty_gra_gra_03_01_off_1[24];
__declspec(section ".data") s32 btlgrp_gra_gra_03_01_off_1[8];
s32 btlparty_gra_gra_03_01_off_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_03_01_off_2[8];
s32 btlparty_gra_gra_03_04_off_1[24];
__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_1[8];
s32 btlparty_gra_gra_03_04_off_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_2[8];
s32 btlparty_gra_gra_03_04_off_3[36];
__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_3[8];
s32 btlparty_gra_gra_03_05_off_1[48];
__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_1[8];
s32 btlparty_gra_gra_03_05_off_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_2[8];
s32 btlparty_gra_gra_03_05_off_3[48];
__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_3[8];
s32 btlparty_gra_gra_04_02_off_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_1[8];
s32 btlparty_gra_gra_04_02_off_2[24];
__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_2[8];
s32 btlparty_gra_gra_04_02_off_3[36];
__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_3[8];
s32 btlparty_gra_gra_05_01_off_1[24];
__declspec(section ".data") s32 btlgrp_gra_gra_05_01_off_1[8];
s32 btlparty_gra_gra_05_01_off_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_05_01_off_2[8];
s32 btlparty_gra_gra_05_03_off_1[36];
__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_1[8];
s32 btlparty_gra_gra_05_03_off_2[36];
__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_2[8];
s32 btlparty_gra_gra_05_03_off_3[48];
__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_3[8];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_00_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_00_02_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_01_on[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_03_on[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_04_on[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_04_off[6];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_01_off[9];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_04_off[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_05_off[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_04_02_off[12];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_05_01_off[9];
__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_05_03_off[12];
s32 btlsetup_gra_tbl[238];
s32 btl_gra_setup_no_tbl[28];

__declspec(section ".data") u64 fd_battle_database_gra_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gra_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gra___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gra___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gra_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gra___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gra_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_gra_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gra_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gra___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gra___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gra_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gra___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gra_one_364[] = {
    1065353216,
};

s32 gra_btlobject_data[] = {
    (s32)"ki_1", 131072, -1027080192, 0, -1041235968, 3932160, (s32)"isi_A", 131072,
    1125515264, 0, -1041235968, 171048960, (s32)"isi_B", 131072, 1112014848, 0,
    -1039663104, 338165760, (s32)"isigaki", 131073, 1073741824, 0, -1044905984, 3932160,
    (s32)"kusa_1", 131073, -1019740160, 0, 1108606976, 171048960, (s32)"kusa_2", 131073,
    1127481344, 0, 1114636288, 338165760, (s32)"kusa_3", 131073, 1116471296, 0,
    1115815936, 505282560, (s32)"kusa_4", 131073, -1028784128, 0, 1113587712, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"kusa_1", 131073, 1125318656, 0,
    1117257728, 3932160, (s32)"kusa_2", 131073, 1108082688, 0, 1117782016, 171048960,
    (s32)"kusa_3", 131073, -1030094848, 0, 1117388800, 338165760, (s32)"kusa_4", 131073,
    -1021640704, 0, 1116602368, 505282560, (s32)"kusamura_mae", 131073, 0, 0,
    1116733440, 3932160, (s32)"kusamura_usiro", 131073, 0, 0, -1031667712, 171048960,
    (s32)"iwa", 131073, 0, 0, -1030881280, 338165760, (s32)"ki_1", 131072,
    1120403456, 0, -1035206656, 3932160, (s32)"ki_2", 131072, -1024065536, 0,
    -1035993088, 171048960, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"murasaki", 131075, 0, 0, 0, 3932160, (s32)"ao", 131075,
    0, 0, 0, 3932160,
};

s32 gra_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_04_0", 10, (s32)gra_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_04_1", 11,
    (s32)(void*)((u8*)gra_btlobject_data + 0xF0), 0, 0, 0, 0, 1677721602, 0, 0,
    (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0, 0,
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
    0, 257,
};

__declspec(section ".data") s32 btlparty_gra_gra_00_01_off_1[] = {
    (s32)unit_faker_mario_gra, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_faker_mario,
};

__declspec(section ".data") s32 btlgrp_gra_gra_00_01_off_1[] = {
    1, (s32)btlparty_gra_gra_00_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_01_off_1[] = {
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo, (s32)unit_hyper_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_kuriboo,
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_01_off_1[] = {
    3, (s32)btlparty_gra_gra_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_01_on_1[] = {
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo, (s32)unit_hyper_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_kuriboo,
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_1[] = {
    3, (s32)btlparty_gra_gra_01_01_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_01_on_2[] = {
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo, (s32)unit_hyper_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_2[] = {
    3, (s32)btlparty_gra_gra_01_01_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_01_on_3[] = {
    (s32)unit_hyper_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_kuriboo, (s32)unit_hyper_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
    (s32)unit_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_01_on_3[] = {
    3, (s32)btlparty_gra_gra_01_01_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_03_off_1[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_03_off_1[] = {
    3, (s32)btlparty_gra_gra_01_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_03_on_1[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_1[] = {
    3, (s32)btlparty_gra_gra_01_03_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_03_on_2[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_2[] = {
    4, (s32)btlparty_gra_gra_01_03_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_03_on_3[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_pansy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_03_on_3[] = {
    4, (s32)btlparty_gra_gra_01_03_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_04_off_1[] = {
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri, (s32)unit_hyper_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_04_off_1[] = {
    3, (s32)btlparty_gra_gra_01_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_04_on_1[] = {
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri, (s32)unit_hyper_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_1[] = {
    3, (s32)btlparty_gra_gra_01_04_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_04_on_2[] = {
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri, (s32)unit_hyper_togekuri, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_2[] = {
    4, (s32)btlparty_gra_gra_01_04_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_01_04_on_3[] = {
    (s32)unit_hyper_togekuri, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togekuri, (s32)unit_hyper_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_kuriboo,
    (s32)unit_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_01_04_on_3[] = {
    3, (s32)btlparty_gra_gra_01_04_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_03_01_off_1[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_01_off_1[] = {
    2, (s32)btlparty_gra_gra_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_03_01_off_2[] = {
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_patakuri,
    (s32)unit_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_01_off_2[] = {
    3, (s32)btlparty_gra_gra_03_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_03_04_off_1[] = {
    (s32)unit_pansy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_1[] = {
    2, (s32)btlparty_gra_gra_03_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_03_04_off_2[] = {
    (s32)unit_pansy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_2[] = {
    3, (s32)btlparty_gra_gra_03_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_03_04_off_3[] = {
    (s32)unit_pansy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_hyper_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_04_off_3[] = {
    3, (s32)btlparty_gra_gra_03_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_03_05_off_1[] = {
    (s32)unit_pansy, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
    (s32)unit_pansy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_1[] = {
    4, (s32)btlparty_gra_gra_03_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_03_05_off_2[] = {
    (s32)unit_pansy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_2[] = {
    3, (s32)btlparty_gra_gra_03_05_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_03_05_off_3[] = {
    (s32)unit_pansy, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
    (s32)unit_hyper_patakuri, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_patakuri, (s32)unit_hyper_togekuri, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togekuri,
};

__declspec(section ".data") s32 btlgrp_gra_gra_03_05_off_3[] = {
    4, (s32)btlparty_gra_gra_03_05_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_04_02_off_1[] = {
    (s32)unit_pansy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_1[] = {
    3, (s32)btlparty_gra_gra_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_04_02_off_2[] = {
    (s32)unit_pansy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_hyper_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_2[] = {
    2, (s32)btlparty_gra_gra_04_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_04_02_off_3[] = {
    (s32)unit_pansy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pansy, (s32)unit_pansy, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_04_02_off_3[] = {
    3, (s32)btlparty_gra_gra_04_02_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_gra_gra_05_01_off_1[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_gra_gra_05_01_off_1[] = {
    2, (s32)btlparty_gra_gra_05_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_05_01_off_2[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_05_01_off_2[] = {
    3, (s32)btlparty_gra_gra_05_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_05_03_off_1[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_1[] = {
    3, (s32)btlparty_gra_gra_05_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_05_03_off_2[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_2[] = {
    3, (s32)btlparty_gra_gra_05_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gra_gra_05_03_off_3[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_pansy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_pansy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_hyper_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_gra_gra_05_03_off_3[] = {
    4, (s32)btlparty_gra_gra_05_03_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_test1_off[] = {
    50, (s32)btlgrp_gra_gra_01_01_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_test2_off[] = {
    50, (s32)btlgrp_gra_gra_01_01_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_00_01_off[] = {
    50, (s32)btlgrp_gra_gra_00_01_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_00_02_off[] = {
    50, (s32)btlgrp_gra_gra_00_01_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_01_on[] = {
    10, (s32)btlgrp_gra_gra_01_01_on_1, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_01_on_2, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_01_on_3,
    (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_01_off[] = {
    50, (s32)btlgrp_gra_gra_01_01_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_03_on[] = {
    10, (s32)btlgrp_gra_gra_01_03_on_1, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_03_on_2, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_03_on_3,
    (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_03_off[] = {
    50, (s32)btlgrp_gra_gra_01_03_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_04_on[] = {
    10, (s32)btlgrp_gra_gra_01_04_on_1, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_04_on_2, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_01_04_on_3,
    (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_01_04_off[] = {
    50, (s32)btlgrp_gra_gra_01_04_off_1, (s32)gra_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_01_off[] = {
    10, (s32)btlgrp_gra_gra_03_01_off_1, (s32)gra_btlstage_data, 10, (s32)btlgrp_gra_gra_03_01_off_2, (s32)gra_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_04_off[] = {
    50, (s32)btlgrp_gra_gra_03_04_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 10, (s32)btlgrp_gra_gra_03_04_off_2, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 40, (s32)btlgrp_gra_gra_03_04_off_3,
    (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_03_05_off[] = {
    30, (s32)btlgrp_gra_gra_03_05_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 10, (s32)btlgrp_gra_gra_03_05_off_2, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 30, (s32)btlgrp_gra_gra_03_05_off_3,
    (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_04_02_off[] = {
    60, (s32)btlgrp_gra_gra_04_02_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 30, (s32)btlgrp_gra_gra_04_02_off_2, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 10, (s32)btlgrp_gra_gra_04_02_off_3,
    (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_05_01_off[] = {
    100, (s32)btlgrp_gra_gra_05_01_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 10, (s32)btlgrp_gra_gra_05_01_off_2, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_gra_btlno_gra_05_03_off[] = {
    50, (s32)btlgrp_gra_gra_05_03_off_1, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 10, (s32)btlgrp_gra_gra_05_03_off_2, (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 40, (s32)btlgrp_gra_gra_05_03_off_3,
    (s32)(void*)((u8*)gra_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_gra_tbl[] = {
    (s32)/*"マップstg_04_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_04_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA00ランペルその１"*/"\x47\x52\x41\x30\x30\x83\x89\x83\x93\x83\x79\x83\x8B\x82\xBB\x82\xCC\x82\x50", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_00_01_off,
    536870912, 0, 67372036, 0, 67372036, 1028, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_BOSS_STG4_RUNPELL1", (s32)/*"GRA00ランペルその２"*/"\x47\x52\x41\x30\x30\x83\x89\x83\x93\x83\x79\x83\x8B\x82\xBB\x82\xCC\x82\x51", 0, 0, -1, 0,
    (s32)btlgrpsel_gra_btlno_gra_00_02_off, 536870912, 0, 67372036, 0, 67372036, 1028, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_BOSS_STG4_RUNPELL1", (s32)/*"GRA01ハイパークリボー"*/"\x47\x52\x41\x30\x31\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -129997919,
    (s32)btlgrpsel_gra_btlno_gra_01_01_on, (s32)btlgrpsel_gra_btlno_gra_01_01_off, 0, 0, 67372036, 0, 67372036, 1028,
    67371008, 168428548, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA01ハイパーパタクリ"*/"\x47\x52\x41\x30\x31\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x70\x83\x5E\x83\x4E\x83\x8A", 0, 0,
    -129997919, (s32)btlgrpsel_gra_btlno_gra_01_03_on, (s32)btlgrpsel_gra_btlno_gra_01_03_off, 0, 0, 67372036, 0, 67372036,
    1028, 67371008, 168428548, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA01ハイパートゲクリ"*/"\x47\x52\x41\x30\x31\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x67\x83\x51\x83\x4E\x83\x8A", 0,
    0, -129997919, (s32)btlgrpsel_gra_btlno_gra_01_04_on, (s32)btlgrpsel_gra_btlno_gra_01_04_off, 0, 0, 67372036, 0,
    67372036, 1028, 67371008, 168428548, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA03ハイパークリボー"*/"\x47\x52\x41\x30\x33\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x4E\x83\x8A\x83\x7B\x81\x5B",
    0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_03_01_off, 0, 0, 67372036,
    0, 67372036, 1028, 67371008, 168428548, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"GRA03パンジーさん"*/"\x47\x52\x41\x30\x33\x83\x70\x83\x93\x83\x57\x81\x5B\x82\xB3\x82\xF1", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_03_04_off, 0, 0,
    67372036, 0, 67372036, 168428548, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA03パンジーさん"*/"\x47\x52\x41\x30\x33\x83\x70\x83\x93\x83\x57\x81\x5B\x82\xB3\x82\xF1", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_03_05_off, 0,
    0, 67372036, 0, 67372036, 168428548, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA04パンジーさん"*/"\x47\x52\x41\x30\x34\x83\x70\x83\x93\x83\x57\x81\x5B\x82\xB3\x82\xF1", 0, 0, -1, 0, (s32)btlgrpsel_gra_btlno_gra_04_02_off,
    0, 0, 67372036, 0, 67372036, 168428548, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA05ハイパーシンエモン"*/"\x47\x52\x41\x30\x35\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_gra_btlno_gra_05_01_off, 0, 0, 67372036, 0, 67372036, 67372036, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"GRA05ハイパーシンエモン"*/"\x47\x52\x41\x30\x35\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_gra_btlno_gra_05_03_off, 0, 0, 67372036, 0, 67372036, 67372036,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 btl_gra_setup_no_tbl[] = {
    (s32)"BTLNO_GRA_TEST1", 0, (s32)"BTLNO_GRA_TEST2", 1, (s32)"BTLNO_GRA_00_01", 2, (s32)"BTLNO_GRA_00_02", 3,
    (s32)"BTLNO_GRA_01_01", 4, (s32)"BTLNO_GRA_01_03", 5, (s32)"BTLNO_GRA_01_04", 6, (s32)"BTLNO_GRA_03_01", 7,
    (s32)"BTLNO_GRA_03_04", 8, (s32)"BTLNO_GRA_03_05", 9, (s32)"BTLNO_GRA_04_02", 10, (s32)"BTLNO_GRA_05_01", 11,
    (s32)"BTLNO_GRA_05_03", 12, 0, 0,
};

