#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_gonbaba[];
extern s32 battle_item_honenoko[];
extern s32 battle_item_nokonoko[];
extern s32 battle_item_patakuri[];
extern s32 battle_item_patapata[];
extern s32 battle_item_red_honenoko[];
extern s32 battle_item_togekuri[];
extern s32 unit_boss_gonbaba[];
extern s32 unit_honenoko[];
extern s32 unit_nokonoko[];
extern s32 unit_patakuri[];
extern s32 unit_patapata[];
extern s32 unit_red_honenoko[];
extern s32 unit_togekuri[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_gon_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_gon_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_gon___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_gon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_gon_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_gon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_gon_one_381[1];
__declspec(section ".data") u64 fd_battle_database_gon_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_gon_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_gon___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_gon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_gon_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_gon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_gon_one_364[1];
s32 gon_btlobject_data[60];
s32 gon_btlstage_data[545];
s32 btlparty_gon_gon_02_02_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_02_02_off_1[8];
s32 btlparty_gon_gon_02_03_off_1[24];
__declspec(section ".data") s32 btlgrp_gon_gon_02_03_off_1[8];
s32 btlparty_gon_gon_02_04_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_02_04_off_1[8];
s32 btlparty_gon_gon_03_01_off_1[60];
__declspec(section ".data") s32 btlgrp_gon_gon_03_01_off_1[8];
s32 btlparty_gon_gon_04_01_off_1[24];
__declspec(section ".data") s32 btlgrp_gon_gon_04_01_off_1[8];
s32 btlparty_gon_gon_04_02_off_1[48];
__declspec(section ".data") s32 btlgrp_gon_gon_04_02_off_1[8];
s32 btlparty_gon_gon_04_03_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_04_03_off_1[8];
s32 btlparty_gon_gon_06_03_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_06_03_off_1[8];
s32 btlparty_gon_gon_06_04_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_06_04_off_1[8];
s32 btlparty_gon_gon_08_01_off_1[24];
__declspec(section ".data") s32 btlgrp_gon_gon_08_01_off_1[8];
s32 btlparty_gon_gon_08_03_off_1[24];
__declspec(section ".data") s32 btlgrp_gon_gon_08_03_off_1[8];
s32 btlparty_gon_gon_08_05_off_1[24];
__declspec(section ".data") s32 btlgrp_gon_gon_08_05_off_1[8];
s32 btlparty_gon_gon_09_01_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_09_01_off_1[8];
s32 btlparty_gon_gon_09_02_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_09_02_off_1[8];
s32 btlparty_gon_gon_09_04_off_1[48];
__declspec(section ".data") s32 btlgrp_gon_gon_09_04_off_1[8];
s32 btlparty_gon_gon_10_01_off_1[48];
__declspec(section ".data") s32 btlgrp_gon_gon_10_01_off_1[8];
s32 btlparty_gon_gon_10_02_off_1[36];
__declspec(section ".data") s32 btlgrp_gon_gon_10_02_off_1[8];
s32 btlparty_gon_gon_10_03_off_1[48];
__declspec(section ".data") s32 btlgrp_gon_gon_10_03_off_1[8];
__declspec(section ".data") s32 btlparty_gon_gon_11_01_off_1[12];
__declspec(section ".data") s32 btlgrp_gon_gon_11_01_off_1[8];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_04_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_03_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_04_02_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_04_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_06_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_06_04_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_05_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_02_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_04_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_01_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_02_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_03_off[6];
__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_11_01_off[6];
s32 btlsetup_gon_tbl[374];
s32 btl_gon_setup_no_tbl[44];

__declspec(section ".data") u64 fd_battle_database_gon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_gon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_gon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_gon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_gon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_gon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_gon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_gon_one_364[] = {
    1065353216,
};

s32 gon_btlobject_data[] = {
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"haikei_B_a", 131074, 0, 0,
    0, 3932160, (s32)"haikei_C_a", 131075, 0, 0, 0, 3932160,
    (s32)"haikei_B_b", 131074, 0, 0, 0, 3932160, (s32)"haikei_C_b", 131075,
    0, 0, 0, 3932160, (s32)"haikei_B_c", 131074, 0, 0,
    0, 3932160, (s32)"haikei_C_c", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160,
};

s32 gon_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_01_5", 2, (s32)gon_btlobject_data, 0, 0, 0, 0,
    1677721602, 0, 0, 0, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_6", 2,
    (s32)(void*)((u8*)gon_btlobject_data + 0xC0), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_01_3", 2, (s32)(void*)((u8*)gon_btlobject_data + 0x30), 0, 0,
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
    (s32)"stg_01_3", 2, (s32)(void*)((u8*)gon_btlobject_data + 0x60), 0, 0, 0, 0, 1677721602,
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
    0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_3", 2, (s32)(void*)((u8*)gon_btlobject_data + 0x90),
    0, 0, 0, 0, 1677721602, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
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
    0,
};

s32 btlparty_gon_gon_02_02_off_1[] = {
    (s32)unit_patapata, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patapata, (s32)unit_patapata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
    (s32)unit_patapata, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_02_02_off_1[] = {
    3, (s32)btlparty_gon_gon_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_02_03_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_patapata, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_02_03_off_1[] = {
    2, (s32)btlparty_gon_gon_02_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_02_04_off_1[] = {
    (s32)unit_patapata, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patapata, (s32)unit_nokonoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
    (s32)unit_nokonoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_02_04_off_1[] = {
    3, (s32)btlparty_gon_gon_02_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_03_01_off_1[] = {
    (s32)unit_red_honenoko, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_red_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1092616192,
    0, -1046478848, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_honenoko, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_03_01_off_1[] = {
    5, (s32)btlparty_gon_gon_03_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_04_01_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_04_01_off_1[] = {
    2, (s32)btlparty_gon_gon_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_04_02_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_honenoko, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_04_02_off_1[] = {
    4, (s32)btlparty_gon_gon_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_04_03_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_honenoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_04_03_off_1[] = {
    3, (s32)btlparty_gon_gon_04_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_06_03_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patapata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
    (s32)unit_patapata, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_06_03_off_1[] = {
    3, (s32)btlparty_gon_gon_06_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_06_04_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
    (s32)unit_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_06_04_off_1[] = {
    3, (s32)btlparty_gon_gon_06_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_08_01_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_08_01_off_1[] = {
    2, (s32)btlparty_gon_gon_08_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_08_03_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_gon_gon_08_03_off_1[] = {
    2, (s32)btlparty_gon_gon_08_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_08_05_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patapata, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_08_05_off_1[] = {
    2, (s32)btlparty_gon_gon_08_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_09_01_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_honenoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_nokonoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_09_01_off_1[] = {
    3, (s32)btlparty_gon_gon_09_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_09_02_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_nokonoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
    (s32)unit_honenoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_09_02_off_1[] = {
    3, (s32)btlparty_gon_gon_09_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_09_04_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_nokonoko, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_nokonoko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_gon_gon_09_04_off_1[] = {
    4, (s32)btlparty_gon_gon_09_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_10_01_off_1[] = {
    (s32)unit_togekuri, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_nokonoko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
    (s32)unit_patapata, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patapata, (s32)unit_togekuri, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_gon_gon_10_01_off_1[] = {
    4, (s32)btlparty_gon_gon_10_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_10_02_off_1[] = {
    (s32)unit_patapata, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patapata, (s32)unit_patapata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
    (s32)unit_patapata, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_10_02_off_1[] = {
    3, (s32)btlparty_gon_gon_10_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_gon_gon_10_03_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_togekuri, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
    (s32)unit_patakuri, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patapata, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_gon_gon_10_03_off_1[] = {
    4, (s32)btlparty_gon_gon_10_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_gon_gon_11_01_off_1[] = {
    (s32)unit_boss_gonbaba, 16777216, 67108868, 1136033792, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gonbaba,
};

__declspec(section ".data") s32 btlgrp_gon_gon_11_01_off_1[] = {
    1, (s32)btlparty_gon_gon_11_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test1_off[] = {
    50, (s32)btlgrp_gon_gon_02_02_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test2_off[] = {
    50, (s32)btlgrp_gon_gon_02_02_off_1, (s32)gon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_test3_off[] = {
    50, (s32)btlgrp_gon_gon_02_02_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_02_off[] = {
    50, (s32)btlgrp_gon_gon_02_02_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_03_off[] = {
    10, (s32)btlgrp_gon_gon_02_03_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_02_04_off[] = {
    10, (s32)btlgrp_gon_gon_02_04_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_03_01_off[] = {
    10, (s32)btlgrp_gon_gon_03_01_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_04_02_off[] = {
    10, (s32)btlgrp_gon_gon_04_02_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_04_03_off[] = {
    10, (s32)btlgrp_gon_gon_04_03_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_06_03_off[] = {
    10, (s32)btlgrp_gon_gon_06_03_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_06_04_off[] = {
    10, (s32)btlgrp_gon_gon_06_04_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_01_off[] = {
    10, (s32)btlgrp_gon_gon_08_01_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_03_off[] = {
    10, (s32)btlgrp_gon_gon_08_03_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_08_05_off[] = {
    10, (s32)btlgrp_gon_gon_08_05_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_01_off[] = {
    10, (s32)btlgrp_gon_gon_09_01_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_02_off[] = {
    10, (s32)btlgrp_gon_gon_09_02_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_09_04_off[] = {
    10, (s32)btlgrp_gon_gon_09_04_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_01_off[] = {
    10, (s32)btlgrp_gon_gon_10_01_off_1, (s32)gon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_02_off[] = {
    10, (s32)btlgrp_gon_gon_10_02_off_1, (s32)gon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_10_03_off[] = {
    10, (s32)btlgrp_gon_gon_10_03_off_1, (s32)gon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_gon_btlno_gon_11_01_off[] = {
    20, (s32)btlgrp_gon_gon_11_01_off_1, (s32)(void*)((u8*)gon_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_gon_tbl[] = {
    (s32)/*"マップstg_01_03"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x30\x33", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_01_05"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x30\x35", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_01_06"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x30\x36", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon02パタパタ1"*/"\x67\x6F\x6E\x30\x32\x83\x70\x83\x5E\x83\x70\x83\x5E\x31", 0, 0, -1, 0,
    (s32)btlgrpsel_gon_btlno_gon_02_02_off, 0, 0, 84213760, 0, 1285, 0, 168427520,
    84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon02ノコノコ2"*/"\x67\x6F\x6E\x30\x32\x83\x6D\x83\x52\x83\x6D\x83\x52\x32", 0, 0, -1,
    0, (s32)btlgrpsel_gon_btlno_gon_02_03_off, 0, 0, 84213760, 0, 1285, 0,
    168427520, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon02パタパタ2"*/"\x67\x6F\x6E\x30\x32\x83\x70\x83\x5E\x83\x70\x83\x5E\x32", 0, 0,
    -1, 0, (s32)btlgrpsel_gon_btlno_gon_02_04_off, 0, 0, 84213760, 0, 1285,
    0, 168427520, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon03赤ホネノコ"*/"\x67\x6F\x6E\x30\x33\x90\xD4\x83\x7A\x83\x6C\x83\x6D\x83\x52", 0,
    0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_03_01_off, 536870928, 3, 0, 0,
    16842752, 0, 0, 0, 0, 0, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"gon04ホネノコ2"*/"\x67\x6F\x6E\x30\x34\x83\x7A\x83\x6C\x83\x6D\x83\x52\x32",
    0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_04_02_off, 0, 0, 84213760,
    0, 84216330, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"gon04ホネノコ3"*/"\x67\x6F\x6E\x30\x34\x83\x7A\x83\x6C\x83\x6D\x83\x52\x33", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_04_03_off, 0, 0,
    84213760, 0, 84216330, 0, 84213760, 84213760, 16842752, 0,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon06トゲクリボー"*/"\x67\x6F\x6E\x30\x36\x83\x67\x83\x51\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_06_03_off, 0,
    0, 84213760, 0, 84215045, 0, 84213760, 168427520, 16842752,
    0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon06ホネノコ2"*/"\x67\x6F\x6E\x30\x36\x83\x7A\x83\x6C\x83\x6D\x83\x52\x32", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_06_04_off,
    0, 0, 84213760, 0, 84216330, 0, 84213760, 84213760,
    16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon08ホネノコ"*/"\x67\x6F\x6E\x30\x38\x83\x7A\x83\x6C\x83\x6D\x83\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_gon_btlno_gon_08_01_off, 0, 0, 84213760, 0, 84216330, 0, 84213760,
    84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon08ホネノコ2"*/"\x67\x6F\x6E\x30\x38\x83\x7A\x83\x6C\x83\x6D\x83\x52\x32", 0, 0, -1,
    0, (s32)btlgrpsel_gon_btlno_gon_08_03_off, 0, 0, 84213760, 0, 84216330, 0,
    84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon08パタクリ"*/"\x67\x6F\x6E\x30\x38\x83\x70\x83\x5E\x83\x4E\x83\x8A", 0, 0,
    -1, 0, (s32)btlgrpsel_gon_btlno_gon_08_05_off, 0, 0, 84213760, 0, 84215045,
    0, 84213760, 168427520, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon09ノコノコ1"*/"\x67\x6F\x6E\x30\x39\x83\x6D\x83\x52\x83\x6D\x83\x52\x31", 0,
    0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_09_01_off, 0, 0, 84213760, 0,
    84215045, 0, 168427520, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon09ホネノコ1"*/"\x67\x6F\x6E\x30\x39\x83\x7A\x83\x6C\x83\x6D\x83\x52\x31",
    0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_09_02_off, 0, 0, 84213760,
    0, 84216330, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"gon09ホネノコ2"*/"\x67\x6F\x6E\x30\x39\x83\x7A\x83\x6C\x83\x6D\x83\x52\x32", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_09_04_off, 0, 0,
    84213760, 0, 84216330, 0, 84213760, 84213760, 16842752, 0,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon10トゲクリボー"*/"\x67\x6F\x6E\x31\x30\x83\x67\x83\x51\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_10_01_off, 0,
    0, 84213760, 0, 84215045, 0, 84213760, 168427520, 16842752,
    0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon10パタパタ"*/"\x67\x6F\x6E\x31\x30\x83\x70\x83\x5E\x83\x70\x83\x5E", 0, 0, -1, 0, (s32)btlgrpsel_gon_btlno_gon_10_02_off,
    0, 0, 84213760, 0, 84215045, 0, 168427520, 84213760,
    16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon10ノコノコ"*/"\x67\x6F\x6E\x31\x30\x83\x6D\x83\x52\x83\x6D\x83\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_gon_btlno_gon_10_03_off, 0, 0, 84213760, 0, 84215045, 0, 168427520,
    84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"gon11ゴンババ"*/"\x67\x6F\x6E\x31\x31\x83\x53\x83\x93\x83\x6F\x83\x6F", (s32)"gon_11", 0, -1,
    0, (s32)btlgrpsel_gon_btlno_gon_11_01_off, 537919504, 3, 84213760, 0, 84215045, 0,
    84213760, 84213760, 16842752, 0, (s32)"BGM_BOSS_STG1_GONBABA1", 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 btl_gon_setup_no_tbl[] = {
    (s32)"BTLNO_GON_TEST1", 0, (s32)"BTLNO_GON_TEST2", 1, (s32)"BTLNO_GON_TEST3", 2, (s32)"BTLNO_GON_02_02", 3,
    (s32)"BTLNO_GON_02_03", 4, (s32)"BTLNO_GON_02_04", 5, (s32)"BTLNO_GON_03_01", 6, (s32)"BTLNO_GON_04_02", 7,
    (s32)"BTLNO_GON_04_03", 8, (s32)"BTLNO_GON_06_03", 9, (s32)"BTLNO_GON_06_04", 10, (s32)"BTLNO_GON_08_01", 11,
    (s32)"BTLNO_GON_08_03", 12, (s32)"BTLNO_GON_08_05", 13, (s32)"BTLNO_GON_09_01", 14, (s32)"BTLNO_GON_09_02", 15,
    (s32)"BTLNO_GON_09_04", 16, (s32)"BTLNO_GON_10_01", 17, (s32)"BTLNO_GON_10_02", 18, (s32)"BTLNO_GON_10_03", 19,
    (s32)"BTLNO_GON_11_01", 20, 0, 0,
};

