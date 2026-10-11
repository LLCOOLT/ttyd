#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default2[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_purple_teresa[];
extern s32 unit_purple_teresa_22_data_E620[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_pik_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_pik_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_pik___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_pik___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_pik_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_pik___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_pik_one_381[1];
__declspec(section ".data") u64 fd_battle_database_pik_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_pik_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_pik___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_pik___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_pik_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_pik___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_pik_one_364[1];
__declspec(section ".data") s32 pik_btlobject_data[12];
s32 pik_btlstage_data[109];
s32 btlparty_pik_pik_06_01_off_1[24];
__declspec(section ".data") s32 btlgrp_pik_pik_06_01_off_1[8];
s32 btlparty_pik_pik_06_02_off_1[36];
__declspec(section ".data") s32 btlgrp_pik_pik_06_02_off_1[8];
__declspec(section ".data") s32 btlparty_pik_pik_06_03_off_1[12];
__declspec(section ".data") s32 btlgrp_pik_pik_06_03_off_1[8];
s32 btlparty_pik_pik_06_04_off_1[24];
__declspec(section ".data") s32 btlgrp_pik_pik_06_04_off_1[8];
s32 btlparty_pik_pik_06_05_off_1[24];
__declspec(section ".data") s32 btlgrp_pik_pik_06_05_off_1[8];
s32 btlparty_pik_pik_06_06_off_1[48];
__declspec(section ".data") s32 btlgrp_pik_pik_06_06_off_1[8];
__declspec(section ".data") s32 btlparty_pik_pik_06_07_off_1[12];
__declspec(section ".data") s32 btlgrp_pik_pik_06_07_off_1[8];
s32 btlparty_pik_pik_06_08_off_1[36];
__declspec(section ".data") s32 btlgrp_pik_pik_06_08_off_1[8];
s32 btlparty_pik_pik_06_09_off_1[48];
__declspec(section ".data") s32 btlgrp_pik_pik_06_09_off_1[8];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_01_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_02_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_03_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_04_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_05_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_06_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_07_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_08_off[6];
__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_09_off[6];
s32 btlsetup_pik_tbl[187];
s32 btl_pik_setup_no_tbl[22];

__declspec(section ".data") u64 fd_battle_database_pik_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_pik_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_pik___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_pik___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_pik_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_pik___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_pik_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_pik_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_pik_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_pik___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_pik___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_pik_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_pik___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_pik_one_364[] = {
    1065353216,
};

__declspec(section ".data") s32 pik_btlobject_data[] = {
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"A2", 131073,
    0, 0, -1030488064, 3932160,
};

s32 pik_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_06_4", 2, (s32)pik_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0,
};

s32 btlparty_pik_pik_06_01_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_01_off_1[] = {
    2, (s32)btlparty_pik_pik_06_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_02_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_02_off_1[] = {
    3, (s32)btlparty_pik_pik_06_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlparty_pik_pik_06_03_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_03_off_1[] = {
    1, (s32)btlparty_pik_pik_06_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_04_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_04_off_1[] = {
    2, (s32)btlparty_pik_pik_06_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_05_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_05_off_1[] = {
    2, (s32)btlparty_pik_pik_06_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_06_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_06_off_1[] = {
    4, (s32)btlparty_pik_pik_06_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlparty_pik_pik_06_07_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_07_off_1[] = {
    1, (s32)btlparty_pik_pik_06_07_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_08_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_08_off_1[] = {
    3, (s32)btlparty_pik_pik_06_08_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_pik_pik_06_09_off_1[] = {
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa_22_data_E620, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_pik_pik_06_09_off_1[] = {
    4, (s32)btlparty_pik_pik_06_09_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_test1_off[] = {
    50, (s32)btlgrp_pik_pik_06_01_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_01_off[] = {
    20, (s32)btlgrp_pik_pik_06_01_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_02_off[] = {
    20, (s32)btlgrp_pik_pik_06_02_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_03_off[] = {
    20, (s32)btlgrp_pik_pik_06_03_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_04_off[] = {
    20, (s32)btlgrp_pik_pik_06_04_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_05_off[] = {
    20, (s32)btlgrp_pik_pik_06_05_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_06_off[] = {
    20, (s32)btlgrp_pik_pik_06_06_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_07_off[] = {
    20, (s32)btlgrp_pik_pik_06_07_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_08_off[] = {
    20, (s32)btlgrp_pik_pik_06_08_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_pik_btlno_pik_03_09_off[] = {
    20, (s32)btlgrp_pik_pik_06_09_off_1, (s32)pik_btlstage_data, 0, 0, 0,
};

s32 btlsetup_pik_tbl[] = {
    (s32)/*"マップstg_06_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x36\x5F\x34", 0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_01_off, 0,
    0, 50529027, 168428291, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_02_off,
    0, 0, 50529027, 168428291, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0,
    (s32)btlgrpsel_pik_btlno_pik_03_03_off, 0, 0, 50529027, 168428291, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1,
    0, (s32)btlgrpsel_pik_btlno_pik_03_04_off, 0, 0, 50529027, 168428291, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0,
    -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_05_off, 0, 0, 50529027, 168428291, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0,
    0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_06_off, 0, 0, 50529027, 168428291,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54",
    0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_07_off, 0, 0, 50529027,
    168428291, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_08_off, 0, 0,
    50529027, 168428291, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"pik_03パープルテレサ"*/"\x70\x69\x6B\x5F\x30\x33\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1, 0, (s32)btlgrpsel_pik_btlno_pik_03_09_off, 0,
    0, 50529027, 168428291, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0,
};

s32 btl_pik_setup_no_tbl[] = {
    (s32)"BTLNO_PIK_TEST1", 0, (s32)"BTLNO_PIK_03_01", 1, (s32)"BTLNO_PIK_03_02", 2, (s32)"BTLNO_PIK_03_03", 3,
    (s32)"BTLNO_PIK_03_04", 4, (s32)"BTLNO_PIK_03_05", 5, (s32)"BTLNO_PIK_03_06", 6, (s32)"BTLNO_PIK_03_07", 7,
    (s32)"BTLNO_PIK_03_08", 8, (s32)"BTLNO_PIK_03_09", 9, 0, 0,
};

