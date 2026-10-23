#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "jin.h"

#pragma force_active on

extern s32 unit_faker_mario[];

__declspec(section ".data") u64 fd_battle_database_jin_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_jin_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_jin___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_jin___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_jin_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_jin___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_jin_one_381[1];
__declspec(section ".data") u64 fd_battle_database_jin_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_jin_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_jin___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_jin___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_jin_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_jin___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_jin_one_364[1];
s32 jin_btlobject_data[108];
s32 jin_btlstage_data[654];
__declspec(section ".data") s32 btlparty_jin_jin_04_ramper[12];
__declspec(section ".data") s32 btlgrp_jin_jin_04_ramper[8];
__declspec(section ".data") s32 btlparty_jin_jin_01_faker_mario[12];
__declspec(section ".data") s32 btlgrp_jin_jin_01_faker_mario[8];
__declspec(section ".data") s32 btlparty_jin_jin_00_atmic_teresa[12];
__declspec(section ".data") s32 btlgrp_jin_jin_00_atmic_teresa[8];
__declspec(section ".data") s32 btlparty_jin_jin_00_01_off_1[12];
__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_1[8];
s32 btlparty_jin_jin_00_01_off_2[24];
__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_2[8];
s32 btlparty_jin_jin_00_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_3[8];
s32 btlparty_jin_jin_00_01_off_4[48];
__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_4[8];
s32 btlparty_jin_jin_01_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_1[8];
s32 btlparty_jin_jin_01_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_2[8];
s32 btlparty_jin_jin_01_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_3[8];
s32 btlparty_jin_jin_01_03_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_1[8];
s32 btlparty_jin_jin_01_03_off_2[48];
__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_2[8];
s32 btlparty_jin_jin_01_03_off_3[24];
__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_3[8];
s32 btlparty_jin_jin_03_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_03_01_off_1[8];
s32 btlparty_jin_jin_03_02_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_03_02_off_1[8];
s32 btlparty_jin_jin_07_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_07_01_off_1[8];
s32 btlparty_jin_jin_07_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jin_jin_07_01_off_2[8];
s32 btlparty_jin_jin_07_02_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_07_02_off_1[8];
s32 btlparty_jin_jin_07_02_off_2[36];
__declspec(section ".data") s32 btlgrp_jin_jin_07_02_off_2[8];
__declspec(section ".data") s32 btlparty_jin_jin_09_01_off_1[12];
__declspec(section ".data") s32 btlgrp_jin_jin_09_01_off_1[8];
s32 btlparty_jin_jin_10_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_10_01_off_1[8];
__declspec(section ".data") s32 btlparty_jin_jin_10_02_off_1[12];
__declspec(section ".data") s32 btlgrp_jin_jin_10_02_off_1[8];
__declspec(section ".data") s32 btlparty_jin_jin_10_03_off_1[12];
__declspec(section ".data") s32 btlgrp_jin_jin_10_03_off_1[8];
s32 btlparty_jin_jin_10_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jin_jin_10_04_off_1[8];
s32 btlparty_jin_jin_10_05_off_1[24];
__declspec(section ".data") s32 btlgrp_jin_jin_10_05_off_1[8];
s32 btlparty_jin_jin_10_06_off_1[36];
__declspec(section ".data") s32 btlgrp_jin_jin_10_06_off_1[8];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test5_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_02_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_00_01_off[6];
s32 btlgrpsel_jin_btlno_jin_00_02_off[15];
s32 btlgrpsel_jin_btlno_jin_00_03_off[15];
s32 btlgrpsel_jin_btlno_jin_00_04_off[15];
s32 btlgrpsel_jin_btlno_jin_00_05_off[15];
s32 btlgrpsel_jin_btlno_jin_00_06_off[15];
s32 btlgrpsel_jin_btlno_jin_00_09_off[15];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_03_off[12];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_05_off[12];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_02_01_off[12];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_02_03_off[12];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_09_01_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_01_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_02_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_03_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_04_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_05_off[6];
__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_06_off[6];
s32 btlsetup_jin_tbl[442];
s32 btl_jin_setup_no_tbl[52];

__declspec(section ".data") u64 fd_battle_database_jin_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_jin_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_jin___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_jin___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_jin_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_jin___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_jin_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_jin_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_jin_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_jin___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_jin___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_jin_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_jin___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_jin_one_364[] = {
    1065353216,
};

s32 jin_btlobject_data[] = {
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"if_wire", 327686, 0, 1124204544, 0, 0, (s32)"if_body", 327686,
    0, 1124204544, 0, 0, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"ranpu", 131072, -1029046272, 0,
    -1039138816, 3932160, (s32)"tukue", 131072, -1042808832, 0, -1036517376, 338165760,
    (s32)"reizouko", 131072, -1023934464, 0, -1032847360, 338165760, (s32)"furo", 131072,
    1119354880, 0, -1037303808, 505282560, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 5898240,
};

s32 jin_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_04_3", 2, (s32)jin_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_04_3", 4,
    (s32)(void*)((u8*)jin_btlobject_data + 0x30), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_04_2", 2, (s32)(void*)((u8*)jin_btlobject_data + 0x90), 0, 0,
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
    (s32)"stg_04_4", 6, (s32)(void*)((u8*)jin_btlobject_data + 0xC0), 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
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
    0, 0, 0, 0, (s32)"bti_01", (s32)"stg_04_5", 2, (s32)(void*)((u8*)jin_btlobject_data + 0x150),
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
    0, (s32)"bti_01", (s32)"stg_04_6", 2, (s32)(void*)((u8*)jin_btlobject_data + 0x180), 0, 0, 0,
    0, 1677721602, 0, 0, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlparty_jin_jin_04_ramper[] = {
    (s32)unit_boss_rampell, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_rampell,
};

__declspec(section ".data") s32 btlgrp_jin_jin_04_ramper[] = {
    1, (s32)btlparty_jin_jin_04_ramper, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_01_faker_mario[] = {
    (s32)unit_faker_mario, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_faker_mario,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_faker_mario[] = {
    1, (s32)btlparty_jin_jin_01_faker_mario, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_00_atmic_teresa[] = {
    (s32)unit_atmic_teresa, 16777216, 67108868, 1116471296, 1101004800, 0, 0, 0,
    0, 0, 0, (s32)battle_item_atmic_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_00_atmic_teresa[] = {
    1, (s32)btlparty_jin_jin_00_atmic_teresa, 0, 10, 0, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_00_01_off_1[] = {
    (s32)unit_teresa, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_1[] = {
    1, (s32)btlparty_jin_jin_00_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_00_01_off_2[] = {
    (s32)unit_teresa, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_2[] = {
    2, (s32)btlparty_jin_jin_00_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_00_01_off_3[] = {
    (s32)unit_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_3[] = {
    3, (s32)btlparty_jin_jin_00_01_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_00_01_off_4[] = {
    (s32)unit_teresa, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_teresa, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_00_01_off_4[] = {
    4, (s32)btlparty_jin_jin_00_01_off_4, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_01_01_off_1[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_1[] = {
    2, (s32)btlparty_jin_jin_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_01_01_off_2[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1119092736,
    1124204544, 0, 0, 0, 0, 0, 0, (s32)battle_item_basabasa,
    (s32)unit_basabasa, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_2[] = {
    3, (s32)btlparty_jin_jin_01_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_01_01_off_3[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_basabasa, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_01_off_3[] = {
    3, (s32)btlparty_jin_jin_01_01_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_01_03_off_1[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_1[] = {
    2, (s32)btlparty_jin_jin_01_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_01_03_off_2[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 0, 0, 0, 0, (s32)battle_item_basabasa,
    (s32)unit_basabasa, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1125515264,
    1124204544, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_2[] = {
    4, (s32)btlparty_jin_jin_01_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_01_03_off_3[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_teresa, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_01_03_off_3[] = {
    2, (s32)btlparty_jin_jin_01_03_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_03_01_off_1[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 1, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_03_01_off_1[] = {
    2, (s32)btlparty_jin_jin_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_03_02_off_1[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 1, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_03_02_off_1[] = {
    2, (s32)btlparty_jin_jin_03_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_07_01_off_1[] = {
    (s32)unit_teresa, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_07_01_off_1[] = {
    2, (s32)btlparty_jin_jin_07_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_07_01_off_2[] = {
    (s32)unit_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_07_01_off_2[] = {
    3, (s32)btlparty_jin_jin_07_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_07_02_off_1[] = {
    (s32)unit_teresa, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_07_02_off_1[] = {
    2, (s32)btlparty_jin_jin_07_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jin_jin_07_02_off_2[] = {
    (s32)unit_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jin_jin_07_02_off_2[] = {
    3, (s32)btlparty_jin_jin_07_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_09_01_off_1[] = {
    (s32)unit_met, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_met,
};

__declspec(section ".data") s32 btlgrp_jin_jin_09_01_off_1[] = {
    1, (s32)btlparty_jin_jin_09_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_10_01_off_1[] = {
    (s32)unit_met, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_met, (s32)unit_met, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_met,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_01_off_1[] = {
    2, (s32)btlparty_jin_jin_10_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_10_02_off_1[] = {
    (s32)unit_togemet, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togemet,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_02_off_1[] = {
    1, (s32)btlparty_jin_jin_10_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jin_jin_10_03_off_1[] = {
    (s32)unit_met, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_met,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_03_off_1[] = {
    1, (s32)btlparty_jin_jin_10_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_10_04_off_1[] = {
    (s32)unit_met, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_met, (s32)unit_met, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_met,
    (s32)unit_met, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_met, (s32)unit_met, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_met,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_04_off_1[] = {
    4, (s32)btlparty_jin_jin_10_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_10_05_off_1[] = {
    (s32)unit_togemet, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togemet, (s32)unit_togemet, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togemet,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_05_off_1[] = {
    2, (s32)btlparty_jin_jin_10_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jin_jin_10_06_off_1[] = {
    (s32)unit_met, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_met, (s32)unit_met, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_met,
    (s32)unit_togemet, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_togemet,
};

__declspec(section ".data") s32 btlgrp_jin_jin_10_06_off_1[] = {
    3, (s32)btlparty_jin_jin_10_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test1_off[] = {
    50, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test2_off[] = {
    50, (s32)btlgrp_jin_jin_00_01_off_1, (s32)jin_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test3_off[] = {
    50, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test4_off[] = {
    50, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_test5_off[] = {
    50, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_01_off[] = {
    50, (s32)btlgrp_jin_jin_04_ramper, (s32)(void*)((u8*)jin_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_02_off[] = {
    50, (s32)btlgrp_jin_jin_01_faker_mario, (s32)(void*)((u8*)jin_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_00_01_off[] = {
    50, (s32)btlgrp_jin_jin_00_atmic_teresa, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_02_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_03_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_04_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_05_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_06_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

s32 btlgrpsel_jin_btlno_jin_00_09_off[] = {
    10, (s32)btlgrp_jin_jin_00_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 20, (s32)btlgrp_jin_jin_00_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x368), 10, (s32)btlgrp_jin_jin_00_01_off_4, (s32)(void*)((u8*)jin_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_03_off[] = {
    20, (s32)btlgrp_jin_jin_01_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_01_05_off[] = {
    10, (s32)btlgrp_jin_jin_01_03_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_03_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 20, (s32)btlgrp_jin_jin_01_03_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_02_01_off[] = {
    50, (s32)btlgrp_jin_jin_01_03_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_03_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 20, (s32)btlgrp_jin_jin_01_03_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_02_03_off[] = {
    50, (s32)btlgrp_jin_jin_01_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_01_off_2, (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 10, (s32)btlgrp_jin_jin_01_01_off_3,
    (s32)(void*)((u8*)jin_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_09_01_off[] = {
    50, (s32)btlgrp_jin_jin_09_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_01_off[] = {
    50, (s32)btlgrp_jin_jin_10_01_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_02_off[] = {
    50, (s32)btlgrp_jin_jin_10_02_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_03_off[] = {
    50, (s32)btlgrp_jin_jin_10_03_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_04_off[] = {
    50, (s32)btlgrp_jin_jin_10_04_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_05_off[] = {
    50, (s32)btlgrp_jin_jin_10_05_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jin_btlno_jin_10_06_off[] = {
    50, (s32)btlgrp_jin_jin_10_06_off_1, (s32)(void*)((u8*)jin_btlstage_data + 0x884), 0, 0, 0,
};

s32 btlsetup_jin_tbl[] = {
    (s32)/*"マップstg_04_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_04_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_04_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x34", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_04_5"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x35", 0, 0, -1, 0,
    (s32)btlgrpsel_jin_btlno_jin_test4_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_04_6"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x34\x5F\x36", 0, 0, -1,
    0, (s32)btlgrpsel_jin_btlno_jin_test5_off, 0, 0, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_04ランペルその１"*/"\x4A\x49\x4E\x5F\x30\x34\x83\x89\x83\x93\x83\x79\x83\x8B\x82\xBB\x82\xCC\x82\x50", (s32)"jin_04", 0,
    -1, 0, (s32)btlgrpsel_jin_btlno_jin_01_01_off, 536870928, 0, 50529027, 50528256, 50529027,
    50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG4_RUNPELL1", (s32)/*"JIN_04ランペルその２"*/"\x4A\x49\x4E\x5F\x30\x34\x83\x89\x83\x93\x83\x79\x83\x8B\x82\xBB\x82\xCC\x82\x51", (s32)"jin_04",
    0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_01_02_off, 536870928, 6, 50529027, 50528256,
    50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG4_FAKEMARIO1", (s32)/*"JIN_00アトミックテレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x41\x83\x67\x83\x7E\x83\x62\x83\x4E\x83\x65\x83\x8C\x83\x54",
    0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_00_01_off, 536870928, 0, 0,
    168427520, 0, 0, 0, 0, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1",
    (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_00_02_off, 0, 0,
    67372036, 168427520, 67372036, 67372036, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_00_03_off, 0,
    0, 67372036, 168427520, 67372036, 67372036, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_00_04_off,
    0, 0, 67372036, 168427520, 67372036, 67372036, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0,
    (s32)btlgrpsel_jin_btlno_jin_00_05_off, 0, 0, 67372036, 168427520, 67372036, 67372036, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0, -1,
    0, (s32)btlgrpsel_jin_btlno_jin_00_06_off, 0, 0, 67372036, 168427520, 67372036, 67372036,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_00テレサ"*/"\x4A\x49\x4E\x5F\x30\x30\x83\x65\x83\x8C\x83\x54", 0, 0,
    -1, 0, (s32)btlgrpsel_jin_btlno_jin_00_09_off, 0, 0, 67372036, 168427520, 67372036,
    67372036, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_01バサバサ"*/"\x4A\x49\x4E\x5F\x30\x31\x83\x6F\x83\x54\x83\x6F\x83\x54", (s32)"jin_04",
    0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_01_03_off, 0, 0, 50529027, 50528256,
    50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_01バサバサ"*/"\x4A\x49\x4E\x5F\x30\x31\x83\x6F\x83\x54\x83\x6F\x83\x54",
    (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_01_05_off, 0, 0, 50529027,
    50528256, 50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"JIN_02バサバサ"*/"\x4A\x49\x4E\x5F\x30\x32\x83\x6F\x83\x54\x83\x6F\x83\x54", (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_02_01_off, 0, 0,
    50529027, 50528256, 50529027, 50529027, 50528256, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_02バサバサ"*/"\x4A\x49\x4E\x5F\x30\x32\x83\x6F\x83\x54\x83\x6F\x83\x54", (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_02_03_off, 0,
    0, 50529027, 50528256, 50529027, 50529027, 50528256, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_09メット"*/"\x4A\x49\x4E\x5F\x30\x39\x83\x81\x83\x62\x83\x67", (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_09_01_off,
    0, 0, 67372036, 0, 67372036, 67372036, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_10メット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x81\x83\x62\x83\x67", (s32)"jin_04", 0, -1, 0,
    (s32)btlgrpsel_jin_btlno_jin_10_01_off, 0, 0, 67372036, 0, 67372036, 67372036, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_10トゲメット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67", (s32)"jin_04", 0, -1,
    0, (s32)btlgrpsel_jin_btlno_jin_10_02_off, 0, 0, 67372036, 0, 67372036, 67372036,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_10メット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x81\x83\x62\x83\x67", (s32)"jin_04", 0,
    -1, 0, (s32)btlgrpsel_jin_btlno_jin_10_03_off, 0, 0, 67372036, 0, 67372036,
    67372036, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_10メット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x81\x83\x62\x83\x67", (s32)"jin_04",
    0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_10_04_off, 0, 0, 67372036, 0,
    67372036, 67372036, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"JIN_10トゲメット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67",
    (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_10_05_off, 0, 0, 67372036,
    0, 67372036, 67372036, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"JIN_10メット"*/"\x4A\x49\x4E\x5F\x31\x30\x83\x81\x83\x62\x83\x67", (s32)"jin_04", 0, -1, 0, (s32)btlgrpsel_jin_btlno_jin_10_06_off, 0, 0,
    67372036, 0, 67372036, 67372036, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s32 btl_jin_setup_no_tbl[] = {
    (s32)"BTLNO_JIN_TEST1", 0, (s32)"BTLNO_JIN_TEST2", 1, (s32)"BTLNO_JIN_TEST3", 2, (s32)"BTLNO_JIN_TEST4", 3,
    (s32)"BTLNO_JIN_TEST5", 4, (s32)"BTLNO_JIN_01_01", 5, (s32)"BTLNO_JIN_01_02", 6, (s32)"BTLNO_JIN_00_01", 7,
    (s32)"BTLNO_JIN_00_02", 8, (s32)"BTLNO_JIN_00_03", 9, (s32)"BTLNO_JIN_00_04", 10, (s32)"BTLNO_JIN_00_05", 11,
    (s32)"BTLNO_JIN_00_06", 12, (s32)"BTLNO_JIN_00_09", 13, (s32)"BTLNO_JIN_01_03", 14, (s32)"BTLNO_JIN_01_05", 15,
    (s32)"BTLNO_JIN_02_01", 16, (s32)"BTLNO_JIN_02_03", 17, (s32)"BTLNO_JIN_09_01", 18, (s32)"BTLNO_JIN_10_01", 19,
    (s32)"BTLNO_JIN_10_02", 20, (s32)"BTLNO_JIN_10_03", 21, (s32)"BTLNO_JIN_10_04", 22, (s32)"BTLNO_JIN_10_05", 23,
    (s32)"BTLNO_JIN_10_06", 24, 0, 0,
};

