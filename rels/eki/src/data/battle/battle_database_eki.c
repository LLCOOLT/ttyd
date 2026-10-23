#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_item_kurokumorn[];
extern s32 battle_item_patatogemet[];
extern s32 battle_item_sambo_mummy[];
extern s32 unit_kuriboo[];
extern s32 unit_kurokumorn[];
extern s32 unit_patatogemet[];
extern s32 unit_sambo_mummy[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_eki_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_eki_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_eki___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_eki___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_eki_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_eki___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_eki_one_381[1];
__declspec(section ".data") u64 fd_battle_database_eki_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_eki_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_eki___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_eki___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_eki_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_eki___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_eki_one_364[1];
s32 eki_btlobject_data[144];
s32 eki_btlstage_data[436];
s32 btlparty_eki_eki_06_01_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_06_01_off_1[8];
s32 btlparty_eki_eki_02_01_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_02_01_off_1[8];
s32 btlparty_eki_eki_02_02_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_02_02_off_1[8];
s32 btlparty_eki_eki_02_03_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_02_03_off_1[8];
s32 btlparty_eki_eki_03_01_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_03_01_off_1[8];
s32 btlparty_eki_eki_03_02_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_03_02_off_1[8];
s32 btlparty_eki_eki_03_03_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_03_03_off_1[8];
s32 btlparty_eki_eki_03_05_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_03_05_off_1[8];
s32 btlparty_eki_eki_03_07_off_1[48];
__declspec(section ".data") s32 btlgrp_eki_eki_03_07_off_1[8];
s32 btlparty_eki_eki_04_01_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_04_01_off_1[8];
s32 btlparty_eki_eki_04_02_off_1[36];
__declspec(section ".data") s32 btlgrp_eki_eki_04_02_off_1[8];
s32 btlparty_eki_eki_04_06_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_04_06_off_1[8];
s32 btlparty_eki_eki_04_03_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_04_03_off_1[8];
s32 btlparty_eki_eki_04_04_off_1[48];
__declspec(section ".data") s32 btlgrp_eki_eki_04_04_off_1[8];
s32 btlparty_eki_eki_04_05_off_1[24];
__declspec(section ".data") s32 btlgrp_eki_eki_04_05_off_1[8];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_06_01_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_06_02_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_01_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_03_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_01_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_02_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_03_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_06_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_08_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_01_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_02_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_06_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_03_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_04_off[6];
__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_05_off[6];
s32 btlsetup_eki_tbl[340];
s32 btl_eki_setup_no_tbl[40];

__declspec(section ".data") u64 fd_battle_database_eki_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_eki_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_eki___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_eki___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_eki_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_eki___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_eki_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_eki_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_eki_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_eki___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_eki___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_eki_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_eki___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_eki_one_364[] = {
    1065353216,
};

s32 eki_btlobject_data[] = {
    (s32)"lamp_01", 131072, -1024983040, 0, -1033109504, 3932160, (s32)"lamp_02", 131072,
    1122500608, 0, -1033109504, 171048960, (s32)"lamp_03", 131072, 0, 0,
    -1033109504, 338165760, (s32)"gomibako_01", 131073, -1020133376, 0, 1111752704, 3932160,
    (s32)"gomibako_02", 131073, 1127350272, 0, 1111752704, 171048960, (s32)"saku", 131073,
    0, 0, 1116340224, 338165760, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"gomibako_01", 131073, -1020133376, 0, 1111752704, 3932160, (s32)"gomibako_02", 131073,
    1127350272, 0, 1111752704, 171048960, (s32)"saku", 131073, 0, 0,
    1116340224, 338165760, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"A1", 131072, 0, 0, 1077936128, 3932160, (s32)"A2", 131073,
    0, 0, -1041235968, 3932160, (s32)"B", 131074, 0, 0,
    1084227584, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"saku_01", 131073, -1025245184, 0, -1044905984, 3932160, (s32)"saku_02", 131073,
    1124204544, 0, -1043857408, 171048960, (s32)"sikake_01", 131072, -1024720896, 0,
    -1037828096, 3932160, (s32)"sikake_02", 131072, -1037565952, 0, -1033109504, 171048960,
    (s32)"sikake_03", 131072, 1124335616, 0, -1038614528, 338165760, (s32)"sikake_04", 131072,
    1108344832, 0, -1035993088, 505282560, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
};

s32 eki_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_06_1", 8, (s32)eki_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 65793, (s32)"bti_01", (s32)"stg_06_1", 4,
    (s32)(void*)((u8*)eki_btlobject_data + 0xC0), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 65793, (s32)"bti_01", (s32)"stg_06_2", 4, (s32)(void*)((u8*)eki_btlobject_data + 0x120), 0, 0,
    0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0,
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
    (s32)"stg_06_3", 8, (s32)(void*)((u8*)eki_btlobject_data + 0x180), 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603119, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

s32 btlparty_eki_eki_06_01_off_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_eki_eki_06_01_off_1[] = {
    3, (s32)btlparty_eki_eki_06_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_02_01_off_1[] = {
    (s32)unit_kurokumorn, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn, (s32)unit_kurokumorn, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_eki_eki_02_01_off_1[] = {
    2, (s32)btlparty_eki_eki_02_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_02_02_off_1[] = {
    (s32)unit_kurokumorn, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn, (s32)unit_kurokumorn, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_kurokumorn,
    (s32)unit_kurokumorn, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_eki_eki_02_02_off_1[] = {
    3, (s32)btlparty_eki_eki_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_02_03_off_1[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_eki_eki_02_03_off_1[] = {
    2, (s32)btlparty_eki_eki_02_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_03_01_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_03_01_off_1[] = {
    2, (s32)btlparty_eki_eki_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_03_02_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_03_02_off_1[] = {
    3, (s32)btlparty_eki_eki_03_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_03_03_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_kurokumorn, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_kurokumorn,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_03_03_off_1[] = {
    3, (s32)btlparty_eki_eki_03_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_03_05_off_1[] = {
    (s32)unit_kurokumorn, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn, (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_03_05_off_1[] = {
    2, (s32)btlparty_eki_eki_03_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_03_07_off_1[] = {
    (s32)unit_kurokumorn, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn, (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_kurokumorn, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_eki_eki_03_07_off_1[] = {
    4, (s32)btlparty_eki_eki_03_07_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_01_off_1[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
    (s32)unit_patatogemet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_01_off_1[] = {
    3, (s32)btlparty_eki_eki_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_02_off_1[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_02_off_1[] = {
    3, (s32)btlparty_eki_eki_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_06_off_1[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_06_off_1[] = {
    2, (s32)btlparty_eki_eki_04_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_03_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_03_off_1[] = {
    2, (s32)btlparty_eki_eki_04_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_04_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_04_off_1[] = {
    4, (s32)btlparty_eki_eki_04_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_eki_eki_04_05_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_patatogemet, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_eki_eki_04_05_off_1[] = {
    2, (s32)btlparty_eki_eki_04_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test1_off[] = {
    50, (s32)btlgrp_eki_eki_06_01_off_1, (s32)eki_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test2_off[] = {
    50, (s32)btlgrp_eki_eki_06_01_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_test3_off[] = {
    50, (s32)btlgrp_eki_eki_06_01_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_06_01_off[] = {
    50, (s32)btlgrp_eki_eki_06_01_off_1, (s32)eki_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_06_02_off[] = {
    50, (s32)btlgrp_eki_eki_06_01_off_1, (s32)eki_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_01_off[] = {
    20, (s32)btlgrp_eki_eki_02_01_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_02_off[] = {
    20, (s32)btlgrp_eki_eki_02_02_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_02_03_off[] = {
    20, (s32)btlgrp_eki_eki_02_03_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_01_off[] = {
    20, (s32)btlgrp_eki_eki_03_01_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_02_off[] = {
    20, (s32)btlgrp_eki_eki_03_02_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_03_off[] = {
    20, (s32)btlgrp_eki_eki_03_03_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_06_off[] = {
    20, (s32)btlgrp_eki_eki_03_05_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_03_08_off[] = {
    20, (s32)btlgrp_eki_eki_03_07_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_01_off[] = {
    20, (s32)btlgrp_eki_eki_04_01_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_02_off[] = {
    20, (s32)btlgrp_eki_eki_04_02_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_06_off[] = {
    20, (s32)btlgrp_eki_eki_04_06_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_03_off[] = {
    20, (s32)btlgrp_eki_eki_04_03_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_04_off[] = {
    20, (s32)btlgrp_eki_eki_04_04_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_eki_btlno_eki_04_05_off[] = {
    20, (s32)btlgrp_eki_eki_04_05_off_1, (s32)(void*)((u8*)eki_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_eki_tbl[] = {
    (s32)/*"マップstg_06_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x36\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_06_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x36\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_06_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x36\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_06 クリボー３"*/"\x65\x6B\x69\x5F\x30\x36\x20\x83\x4E\x83\x8A\x83\x7B\x81\x5B\x82\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_eki_btlno_eki_06_01_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_06 クリボー３"*/"\x65\x6B\x69\x5F\x30\x36\x20\x83\x4E\x83\x8A\x83\x7B\x81\x5B\x82\x52", 0, 0, -1,
    0, (s32)btlgrpsel_eki_btlno_eki_06_02_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_02クロクモーン"*/"\x65\x6B\x69\x5F\x30\x32\x83\x4E\x83\x8D\x83\x4E\x83\x82\x81\x5B\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_eki_btlno_eki_02_01_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_02クロクモーン"*/"\x65\x6B\x69\x5F\x30\x32\x83\x4E\x83\x8D\x83\x4E\x83\x82\x81\x5B\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_02_02_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_02パタトゲメット"*/"\x65\x6B\x69\x5F\x30\x32\x83\x70\x83\x5E\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67",
    0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_02_03_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"eki_03サンボ"*/"\x65\x6B\x69\x5F\x30\x33\x83\x54\x83\x93\x83\x7B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_03_01_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_03サンボ"*/"\x65\x6B\x69\x5F\x30\x33\x83\x54\x83\x93\x83\x7B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_03_02_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_03サンボ"*/"\x65\x6B\x69\x5F\x30\x33\x83\x54\x83\x93\x83\x7B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_03_03_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_03クロクモーン"*/"\x65\x6B\x69\x5F\x30\x33\x83\x4E\x83\x8D\x83\x4E\x83\x82\x81\x5B\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_eki_btlno_eki_03_06_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_03クロクモーン"*/"\x65\x6B\x69\x5F\x30\x33\x83\x4E\x83\x8D\x83\x4E\x83\x82\x81\x5B\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_eki_btlno_eki_03_08_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_04パタトゲメット"*/"\x65\x6B\x69\x5F\x30\x34\x83\x70\x83\x5E\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67", 0, 0,
    -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_01_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_04パタトゲメット"*/"\x65\x6B\x69\x5F\x30\x34\x83\x70\x83\x5E\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67", 0,
    0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_02_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_04パタトゲメット"*/"\x65\x6B\x69\x5F\x30\x34\x83\x70\x83\x5E\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67",
    0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_06_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"eki_04サンボマミー"*/"\x65\x6B\x69\x5F\x30\x34\x83\x54\x83\x93\x83\x7B\x83\x7D\x83\x7E\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_03_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_04サンボマミー"*/"\x65\x6B\x69\x5F\x30\x34\x83\x54\x83\x93\x83\x7B\x83\x7D\x83\x7E\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_04_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"eki_04サンボマミー"*/"\x65\x6B\x69\x5F\x30\x34\x83\x54\x83\x93\x83\x7B\x83\x7D\x83\x7E\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_eki_btlno_eki_04_05_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

s32 btl_eki_setup_no_tbl[] = {
    (s32)"BTLNO_EKI_TEST1", 0, (s32)"BTLNO_EKI_TEST2", 1, (s32)"BTLNO_EKI_TEST3", 2, (s32)"BTLNO_EKI_06_01", 3,
    (s32)"BTLNO_EKI_06_02", 4, (s32)"BTLNO_EKI_02_01", 5, (s32)"BTLNO_EKI_02_02", 6, (s32)"BTLNO_EKI_02_03", 7,
    (s32)"BTLNO_EKI_03_01", 8, (s32)"BTLNO_EKI_03_02", 9, (s32)"BTLNO_EKI_03_03", 10, (s32)"BTLNO_EKI_03_06", 11,
    (s32)"BTLNO_EKI_03_08", 12, (s32)"BTLNO_EKI_04_01", 13, (s32)"BTLNO_EKI_04_02", 14, (s32)"BTLNO_EKI_04_06", 15,
    (s32)"BTLNO_EKI_04_03", 16, (s32)"BTLNO_EKI_04_04", 17, (s32)"BTLNO_EKI_04_05", 18, 0, 0,
};

