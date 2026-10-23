#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"

static USER_FUNC(_space_rotate);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_item_barriern_z[];
extern s32 battle_item_default_param_list[];
extern s32 battle_item_sinemon[];
extern s32 unit_barriern_z[];
extern s32 unit_kuriboo[];
extern s32 unit_sinemon[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_moo_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_moo_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_moo___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_moo___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_moo_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_moo___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_moo_one_381[1];
__declspec(section ".data") u64 fd_battle_database_moo_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_moo_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_moo___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_moo___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_moo_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_moo___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_moo_one_364[1];
s32 moo_btlobject_data[30];
s32 moo_btlstage_data[109];
s32 btlparty_moo_moo_00_01_off_1[36];
__declspec(section ".data") s32 btlgrp_moo_moo_00_01_off_1[8];
s32 btlparty_moo_moo_01_01_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_01_01_off_1[8];
s32 btlparty_moo_moo_01_02_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_01_02_off_1[8];
s32 btlparty_moo_moo_01_02_off_2[36];
__declspec(section ".data") s32 btlgrp_moo_moo_01_02_off_2[8];
s32 btlparty_moo_moo_01_03_off_1[36];
__declspec(section ".data") s32 btlgrp_moo_moo_01_03_off_1[8];
s32 btlparty_moo_moo_01_04_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_1[8];
s32 btlparty_moo_moo_01_04_off_2[36];
__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_2[8];
s32 btlparty_moo_moo_01_04_off_3[48];
__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_3[8];
s32 btlparty_moo_moo_01_05_off_1[48];
__declspec(section ".data") s32 btlgrp_moo_moo_01_05_off_1[8];
s32 btlparty_moo_moo_02_01_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_02_01_off_1[8];
s32 btlparty_moo_moo_02_02_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_02_02_off_1[8];
s32 btlparty_moo_moo_02_03_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_02_03_off_1[8];
s32 btlparty_moo_moo_02_04_off_1[36];
__declspec(section ".data") s32 btlgrp_moo_moo_02_04_off_1[8];
s32 btlparty_moo_moo_02_05_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_02_05_off_1[8];
s32 btlparty_moo_moo_05_01_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_1[8];
s32 btlparty_moo_moo_05_01_off_2[36];
__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_2[8];
s32 btlparty_moo_moo_05_01_off_3[48];
__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_3[8];
s32 btlparty_moo_moo_05_02_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_05_02_off_1[8];
s32 btlparty_moo_moo_05_03_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_05_03_off_1[8];
s32 btlparty_moo_moo_05_03_off_2[36];
__declspec(section ".data") s32 btlgrp_moo_moo_05_03_off_2[8];
s32 btlparty_moo_moo_05_04_off_1[36];
__declspec(section ".data") s32 btlgrp_moo_moo_05_04_off_1[8];
s32 btlparty_moo_moo_05_05_off_1[24];
__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_1[8];
s32 btlparty_moo_moo_05_05_off_2[36];
__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_2[8];
s32 btlparty_moo_moo_05_05_off_3[48];
__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_3[8];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_02_off[9];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_03_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_04_off[12];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_05_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_01_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_03_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_04_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_05_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_01_off[12];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_02_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_03_off[9];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_04_off[6];
__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_05_off[12];
s32 btlsetup_moo_tbl[289];
s32 btl_moo_setup_no_tbl[34];
s32 bgset_moo_space_event[35];

__declspec(section ".data") u64 fd_battle_database_moo_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_moo_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_moo___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_moo___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_moo_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_moo___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_moo_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_moo_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_moo_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_moo___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_moo___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_moo_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_moo___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_moo_one_364[] = {
    1065353216,
};

s32 moo_btlobject_data[] = {
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"space", 131075,
    0, 0, 0, 3932160, (s32)"star_01", 131075, 0, 0,
    0, 3932160, (s32)"star_02", 131075, 0, 0, 0, 3932160,
    (s32)"star_03", 131075, 0, 0, 0, 3932160,
};

s32 moo_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_07_4", 5, (s32)moo_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, (s32)bgset_moo_space_event, 0,
};

s32 btlparty_moo_moo_00_01_off_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list, (s32)unit_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_moo_moo_00_01_off_1[] = {
    3, (s32)btlparty_moo_moo_00_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_01_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_01_off_1[] = {
    2, (s32)btlparty_moo_moo_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_02_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_02_off_1[] = {
    2, (s32)btlparty_moo_moo_01_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_02_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_02_off_2[] = {
    3, (s32)btlparty_moo_moo_01_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_03_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_03_off_1[] = {
    3, (s32)btlparty_moo_moo_01_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_04_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_1[] = {
    2, (s32)btlparty_moo_moo_01_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_04_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_2[] = {
    3, (s32)btlparty_moo_moo_01_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_04_off_3[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_04_off_3[] = {
    4, (s32)btlparty_moo_moo_01_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_01_05_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_01_05_off_1[] = {
    4, (s32)btlparty_moo_moo_01_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_02_01_off_1[] = {
    (s32)unit_barriern_z, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z, (s32)unit_barriern_z, 16777216, 67108868, 1124204544,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_moo_moo_02_01_off_1[] = {
    2, (s32)btlparty_moo_moo_02_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_moo_moo_02_02_off_1[] = {
    (s32)unit_barriern_z, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_02_02_off_1[] = {
    2, (s32)btlparty_moo_moo_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_moo_moo_02_03_off_1[] = {
    (s32)unit_barriern_z, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_barriern_z, (s32)unit_barriern_z, 16777216, 67108868, 1124204544,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_moo_moo_02_03_off_1[] = {
    2, (s32)btlparty_moo_moo_02_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_moo_moo_02_04_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_barriern_z, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_02_04_off_1[] = {
    3, (s32)btlparty_moo_moo_02_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_02_05_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_barriern_z, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern_z,
};

__declspec(section ".data") s32 btlgrp_moo_moo_02_05_off_1[] = {
    2, (s32)btlparty_moo_moo_02_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_01_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_1[] = {
    2, (s32)btlparty_moo_moo_05_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_01_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_2[] = {
    3, (s32)btlparty_moo_moo_05_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_01_off_3[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_01_off_3[] = {
    4, (s32)btlparty_moo_moo_05_01_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_02_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_02_off_1[] = {
    2, (s32)btlparty_moo_moo_05_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_03_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_03_off_1[] = {
    2, (s32)btlparty_moo_moo_05_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_03_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_03_off_2[] = {
    3, (s32)btlparty_moo_moo_05_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_04_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_04_off_1[] = {
    3, (s32)btlparty_moo_moo_05_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_05_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_1[] = {
    2, (s32)btlparty_moo_moo_05_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_05_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_2[] = {
    3, (s32)btlparty_moo_moo_05_05_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_moo_moo_05_05_off_3[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_moo_moo_05_05_off_3[] = {
    4, (s32)btlparty_moo_moo_05_05_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_test1_off[] = {
    50, (s32)btlgrp_moo_moo_00_01_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_01_off[] = {
    10, (s32)btlgrp_moo_moo_01_01_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_02_off[] = {
    10, (s32)btlgrp_moo_moo_01_02_off_1, (s32)moo_btlstage_data, 10, (s32)btlgrp_moo_moo_01_02_off_2, (s32)moo_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_03_off[] = {
    10, (s32)btlgrp_moo_moo_01_03_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_04_off[] = {
    10, (s32)btlgrp_moo_moo_01_04_off_1, (s32)moo_btlstage_data, 10, (s32)btlgrp_moo_moo_01_04_off_2, (s32)moo_btlstage_data, 5, (s32)btlgrp_moo_moo_01_04_off_3,
    (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_01_05_off[] = {
    5, (s32)btlgrp_moo_moo_01_05_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_01_off[] = {
    20, (s32)btlgrp_moo_moo_02_01_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_02_off[] = {
    20, (s32)btlgrp_moo_moo_02_02_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_03_off[] = {
    20, (s32)btlgrp_moo_moo_02_03_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_04_off[] = {
    20, (s32)btlgrp_moo_moo_02_04_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_02_05_off[] = {
    20, (s32)btlgrp_moo_moo_02_05_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_01_off[] = {
    10, (s32)btlgrp_moo_moo_05_01_off_1, (s32)moo_btlstage_data, 10, (s32)btlgrp_moo_moo_05_01_off_2, (s32)moo_btlstage_data, 5, (s32)btlgrp_moo_moo_05_01_off_3,
    (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_02_off[] = {
    20, (s32)btlgrp_moo_moo_05_02_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_03_off[] = {
    10, (s32)btlgrp_moo_moo_05_03_off_1, (s32)moo_btlstage_data, 10, (s32)btlgrp_moo_moo_05_03_off_2, (s32)moo_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_04_off[] = {
    20, (s32)btlgrp_moo_moo_05_04_off_1, (s32)moo_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_moo_btlno_moo_05_05_off[] = {
    10, (s32)btlgrp_moo_moo_05_05_off_1, (s32)moo_btlstage_data, 10, (s32)btlgrp_moo_moo_05_05_off_2, (s32)moo_btlstage_data, 5, (s32)btlgrp_moo_moo_05_05_off_3,
    (s32)moo_btlstage_data, 0, 0, 0,
};

s32 btlsetup_moo_tbl[] = {
    (s32)/*"マップstg_07_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x34", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo01シンエモン"*/"\x6D\x6F\x6F\x30\x31\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_01_01_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo01シンエモン"*/"\x6D\x6F\x6F\x30\x31\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_01_02_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo01シンエモン"*/"\x6D\x6F\x6F\x30\x31\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_moo_btlno_moo_01_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo01シンエモン"*/"\x6D\x6F\x6F\x30\x31\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_moo_btlno_moo_01_04_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo01シンエモン"*/"\x6D\x6F\x6F\x30\x31\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_moo_btlno_moo_01_05_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo02バリアーンZ"*/"\x6D\x6F\x6F\x30\x32\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x5A", 0,
    0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_02_01_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo02バリアーンZ"*/"\x6D\x6F\x6F\x30\x32\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x5A",
    0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_02_02_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"moo02バリアーンZ"*/"\x6D\x6F\x6F\x30\x32\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x5A", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_02_03_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo02シンエモン"*/"\x6D\x6F\x6F\x30\x32\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_02_04_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo02シンエモン"*/"\x6D\x6F\x6F\x30\x32\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_02_05_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo05シンエモン"*/"\x6D\x6F\x6F\x30\x35\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_moo_btlno_moo_05_01_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo05シンエモン"*/"\x6D\x6F\x6F\x30\x35\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_moo_btlno_moo_05_02_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo05シンエモン"*/"\x6D\x6F\x6F\x30\x35\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_moo_btlno_moo_05_03_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo05シンエモン"*/"\x6D\x6F\x6F\x30\x35\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_05_04_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"moo05シンエモン"*/"\x6D\x6F\x6F\x30\x35\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_moo_btlno_moo_05_05_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

s32 btl_moo_setup_no_tbl[] = {
    (s32)"BTLNO_MOO_TEST1", 0, (s32)"BTLNO_MOO_01_01", 1, (s32)"BTLNO_MOO_01_02", 2, (s32)"BTLNO_MOO_01_03", 3,
    (s32)"BTLNO_MOO_01_04", 4, (s32)"BTLNO_MOO_01_05", 5, (s32)"BTLNO_MOO_02_01", 6, (s32)"BTLNO_MOO_02_02", 7,
    (s32)"BTLNO_MOO_02_03", 8, (s32)"BTLNO_MOO_02_04", 9, (s32)"BTLNO_MOO_02_05", 10, (s32)"BTLNO_MOO_05_01", 11,
    (s32)"BTLNO_MOO_05_02", 12, (s32)"BTLNO_MOO_05_03", 13, (s32)"BTLNO_MOO_05_04", 14, (s32)"BTLNO_MOO_05_05", 15,
    0, 0,
};

EVT_BEGIN(bgset_moo_space_event)
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
