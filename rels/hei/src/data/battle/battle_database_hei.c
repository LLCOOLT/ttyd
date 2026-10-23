#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_chorobon[];
extern s32 battle_item_gold_chorobon[];
extern s32 battle_item_kuriboo[];
extern s32 battle_item_monochrome_sinemon[];
extern s32 battle_item_nokonoko[];
extern s32 battle_item_patakuri[];
extern s32 battle_item_sinnosuke[];
extern s32 battle_item_togedaruma[];
extern s32 battle_item_togekuri[];
extern s32 unit_chorobon[];
extern s32 unit_gold_chorobon[];
extern s32 unit_kuriboo[];
extern s32 unit_monochrome_sinemon[];
extern s32 unit_nokonoko[];
extern s32 unit_patakuri[];
extern s32 unit_sinnosuke[];
extern s32 unit_togedaruma[];
extern s32 unit_togekuri[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_hei_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_hei_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_hei___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_hei___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_hei_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_hei___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_hei_one_381[1];
__declspec(section ".data") u64 fd_battle_database_hei_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_hei_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_hei___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_hei___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_hei_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_hei___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_hei_one_364[1];
s32 hei_btlobject_data[354];
s32 hei_btlstage_data[1199];
s32 btlparty_hei_hei_01_01_off_1[48];
__declspec(section ".data") s32 btlgrp_hei_hei_01_01_off_1[8];
s32 btlparty_hei_hei_02_02_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_02_02_off_1[8];
s32 btlparty_hei_hei_02_03_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_02_03_off_1[8];
s32 btlparty_hei_hei_02_04_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_02_04_off_1[8];
s32 btlparty_hei_hei_03_01_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_03_01_off_1[8];
s32 btlparty_hei_hei_04_01_off_1[36];
__declspec(section ".data") s32 btlgrp_hei_hei_04_01_off_1[8];
s32 btlparty_hei_hei_04_01_off_2[24];
__declspec(section ".data") s32 btlgrp_hei_hei_04_01_off_2[8];
s32 btlparty_hei_hei_04_02_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_04_02_off_1[8];
s32 btlparty_hei_hei_04_02_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_04_02_off_2[8];
s32 btlparty_hei_hei_05_01_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_05_01_off_1[8];
s32 btlparty_hei_hei_06_02_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_06_02_off_1[8];
s32 btlparty_hei_hei_06_03_off_1[36];
__declspec(section ".data") s32 btlgrp_hei_hei_06_03_off_1[8];
s32 btlparty_hei_hei_06_03_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_06_03_off_2[8];
s32 btlparty_hei_hei_07_01_off_1[48];
__declspec(section ".data") s32 btlgrp_hei_hei_07_01_off_1[8];
s32 btlparty_hei_hei_08_01_off_1[48];
__declspec(section ".data") s32 btlgrp_hei_hei_08_01_off_1[8];
s32 btlparty_hei_hei_09_01_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_09_01_off_1[8];
s32 btlparty_hei_hei_09_01_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_09_01_off_2[8];
s32 btlparty_hei_hei_09_03_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_09_03_off_1[8];
s32 btlparty_hei_hei_09_03_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_09_03_off_2[8];
__declspec(section ".data") s32 btlparty_hei_hei_10_01_off_1[12];
__declspec(section ".data") s32 btlgrp_hei_hei_10_01_off_1[8];
s32 btlparty_hei_hei_11_01_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_11_01_off_1[8];
s32 btlparty_hei_hei_11_01_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_11_01_off_2[8];
s32 btlparty_hei_hei_11_03_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_11_03_off_1[8];
s32 btlparty_hei_hei_11_03_off_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_11_03_off_2[8];
s32 btlparty_hei_hei_12_01_off_1[48];
__declspec(section ".data") s32 btlgrp_hei_hei_12_01_off_1[8];
s32 btlparty_hei_hei_13_02_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_13_02_off_1[8];
s32 btlparty_hei_hei_13_02_on_1[36];
__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_1[8];
s32 btlparty_hei_hei_13_02_on_2[48];
__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_2[8];
s32 btlparty_hei_hei_13_02_on_3[60];
__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_3[8];
s32 btlparty_hei_hei_13_03_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_13_03_off_1[8];
s32 btlparty_hei_hei_13_03_on_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_13_03_on_1[8];
s32 btlparty_hei_hei_13_03_on_2[36];
__declspec(section ".data") s32 btlgrp_hei_hei_13_03_on_2[8];
s32 btlparty_hei_hei_13_04_off_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_13_04_off_1[8];
s32 btlparty_hei_hei_13_04_on_1[24];
__declspec(section ".data") s32 btlgrp_hei_hei_13_04_on_1[8];
s32 btlparty_hei_hei_13_04_on_2[48];
__declspec(section ".data") s32 btlgrp_hei_hei_13_04_on_2[8];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_03_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_04_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_03_01_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_04_01_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_04_02_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_05_01_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_06_02_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_06_03_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_07_01_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_08_01_off[6];
__declspec(section ".data") s32 R_btlgrpsel_hei_btlno_hei_08_02_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_09_01_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_09_03_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_10_01_off[6];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_11_01_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_11_03_off[9];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_12_01_off[6];
__declspec(section ".data") s32 R_btlgrpsel_hei_btlno_hei_12_02_off[6];
s32 btlgrpsel_hei_btlno_hei_13_02_off[15];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_13_03_off[12];
__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_13_04_off[12];
s32 btlsetup_hei_tbl[476];
s32 btl_hei_setup_no_tbl[56];

__declspec(section ".data") u64 fd_battle_database_hei_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_hei_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_hei___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_hei___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_hei_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_hei___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_hei_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_hei_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_hei_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_hei___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_hei___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_hei_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_hei___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_hei_one_364[] = {
    1065353216,
};

s32 hei_btlobject_data[] = {
    (s32)"ki_1", 131072, 1124597760, 0, -1032060928, 3932160, (s32)"ki_2", 131072,
    1118568448, 0, -1041235968, 171048960, (s32)"ki_3", 131072, 1109393408, 0,
    -1035468800, 338165760, (s32)"kusa_1", 131073, -1021968384, 0, -1041235968, 3932160,
    (s32)"kusa_2", 131073, 1127743488, 0, 1115815936, 171048960, (s32)"kusa_3", 131073,
    -1020985344, 0, 1111752704, 338165760, (s32)"hana_1", 131073, 1120403456, 0,
    1117257728, 505282560, (s32)"hana_2", 131073, -1037041664, 0, 1116995584, 3932160,
    (s32)"saku_1", 131073, -1044381696, 0, -1038352384, 171048960, (s32)"saku_2", 131073,
    1126957056, 0, -1039925248, 338165760, (s32)"saku_3", 131073, -1027211264, 0,
    -1031012352, 505282560, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"ki_1", 131072,
    1124270080, 0, -1040187392, 3932160, (s32)"kusa_1", 131073, 1104674816, 0,
    -1038090240, 3932160, (s32)"gareki_1_1", 131073, 1123942400, 0, -1033895936, 171048960,
    (s32)"gareki_1_2", 131073, -1034944512, 0, -1037303808, 338165760, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"ki_1", 131072, -1024196608, 0, -1037828096, 3932160,
    (s32)"toride_1", 131072, 1119485952, 0, -1034158080, 171048960, (s32)"kusa_1", 131073,
    -1030619136, 0, -1040711680, 3932160, (s32)"gareki_1_1", 131073, -1016004608, 0,
    -1037041664, 171048960, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"ki_1", 131072,
    1124270080, 0, -1040187392, 3932160, (s32)"kusa_1", 131073, 1104674816, 0,
    -1038090240, 3932160, (s32)"gareki_2_1", 131073, 1123942400, 0, -1033895936, 171048960,
    (s32)"gareki_2_2", 131073, -1034944512, 0, -1037303808, 338165760, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"ki_1", 131072, -1024196608, 0, -1037828096, 3932160,
    (s32)"toride_2", 131072, 1119485952, 0, -1034158080, 171048960, (s32)"kusa_1", 131073,
    -1019019264, 0, -1053818880, 3932160, (s32)"gareki_2_1", 131073, -1014398976, 0,
    -1036517376, 171048960, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"ki_1", 131072,
    1124270080, 0, -1040187392, 3932160, (s32)"kusa_1", 131073, 1104674816, 0,
    -1038090240, 3932160, (s32)"gareki_3_1", 131073, 1123942400, 0, -1033895936, 171048960,
    (s32)"gareki_3_2", 131073, -1034944512, 0, -1037303808, 338165760, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"ki_1", 131072, -1024196608, 0, -1037828096, 3932160,
    (s32)"toride_3", 131072, 1119485952, 0, -1034158080, 171048960, (s32)"kusa_1", 131073,
    -1029046272, 0, -1042808832, 3932160, (s32)"gareki_3_1", 131073, -1016070144, 0,
    -1035993088, 171048960, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"S_dai_01_3", 131072,
    -1023541248, 0, -1034682368, 3932160, (s32)"S_dai_02_3", 131072, 1123942400, 0,
    -1034682368, 171048960, (s32)"C_hei_03", 131075, 0, 0, 0, 3932160,
    (s32)"S_dai_01_5", 131072, -1023541248, 0, -1034682368, 3932160, (s32)"S_dai_02_5", 131072,
    1123942400, 0, -1034682368, 171048960, (s32)"C_hei_05", 131075, 0, 0,
    0, 3932160, (s32)"B_hei_07", 131072, 1119748096, 0, -1034944512, 3932160,
    (s32)"C_hei_07", 131075, 0, 0, 0, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160,
};

s32 hei_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_01_0", 13, (s32)hei_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_4", 6,
    (s32)(void*)((u8*)hei_btlobject_data + 0x138), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_01_4", 6, (s32)(void*)((u8*)hei_btlobject_data + 0x1C8), 0, 0,
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
    (s32)"stg_01_4", 6, (s32)(void*)((u8*)hei_btlobject_data + 0x258), 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603119, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 1677721602,
    0, 0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_4", 6, (s32)(void*)((u8*)hei_btlobject_data + 0x2E8),
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
    0, (s32)"bti_01", (s32)"stg_01_4", 6, (s32)(void*)((u8*)hei_btlobject_data + 0x378), 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603119, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603104, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_4",
    6, (s32)(void*)((u8*)hei_btlobject_data + 0x408), 0, 0, 0, 0, 1677721602, 0,
    0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 34603104, 536870912, 1704706, 0, 0,
    2047, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 100,
    0, 0, 0, 0, 0, 0, 1677721602, 0,
    0, (s32)weaponGetPowerDefault, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 34603104, 536870912, 1704706, 0, 0,
    2047, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 100,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)"bti_01", (s32)"stg_01_1", 3, (s32)(void*)((u8*)hei_btlobject_data + 0x498), 0,
    0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    34603104, 536870912, 1704706, 0, 0, 2047, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 100, 0, 0, 0,
    0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    34603104, 536870912, 1704706, 0, 0, 2047, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 100, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)"bti_01", (s32)"stg_01_1", 3, (s32)(void*)((u8*)hei_btlobject_data + 0x4E0), 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_01_1", 2,
    (s32)(void*)((u8*)hei_btlobject_data + 0x528), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_01_2", 2, (s32)(void*)((u8*)hei_btlobject_data + 0x558), 0, 0,
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
    0, 0, 0, 0, 0, 0, 0,
};

s32 btlparty_hei_hei_01_01_off_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
    (s32)unit_togekuri, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_patakuri, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_01_01_off_1[] = {
    4, (s32)btlparty_hei_hei_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_02_02_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_nokonoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_02_02_off_1[] = {
    2, (s32)btlparty_hei_hei_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_02_03_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_kuriboo, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_hei_hei_02_03_off_1[] = {
    2, (s32)btlparty_hei_hei_02_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_02_04_off_1[] = {
    (s32)unit_togekuri, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_nokonoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_02_04_off_1[] = {
    2, (s32)btlparty_hei_hei_02_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_03_01_off_1[] = {
    (s32)unit_sinnosuke, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sinnosuke, (s32)unit_sinnosuke, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinnosuke,
};

__declspec(section ".data") s32 btlgrp_hei_hei_03_01_off_1[] = {
    2, (s32)btlparty_hei_hei_03_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_04_01_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
    (s32)unit_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_04_01_off_1[] = {
    3, (s32)btlparty_hei_hei_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_04_01_off_2[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_nokonoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_04_01_off_2[] = {
    2, (s32)btlparty_hei_hei_04_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_04_02_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_nokonoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_04_02_off_1[] = {
    2, (s32)btlparty_hei_hei_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_04_02_off_2[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_nokonoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
    (s32)unit_nokonoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_04_02_off_2[] = {
    3, (s32)btlparty_hei_hei_04_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_05_01_off_1[] = {
    (s32)unit_togedaruma, 16777216, 67108868, 1117782016, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togedaruma, (s32)unit_togedaruma, 16777216, 67108868, 1125515264,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togedaruma,
};

__declspec(section ".data") s32 btlgrp_hei_hei_05_01_off_1[] = {
    2, (s32)btlparty_hei_hei_05_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_06_02_off_1[] = {
    (s32)unit_nokonoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko, (s32)unit_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_06_02_off_1[] = {
    2, (s32)btlparty_hei_hei_06_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_06_03_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_nokonoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
    (s32)unit_nokonoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_06_03_off_1[] = {
    3, (s32)btlparty_hei_hei_06_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_06_03_off_2[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
    (s32)unit_nokonoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_hei_hei_06_03_off_2[] = {
    3, (s32)btlparty_hei_hei_06_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_07_01_off_1[] = {
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_sinemon, (s32)unit_monochrome_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_sinemon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_07_01_off_1[] = {
    4, (s32)btlparty_hei_hei_07_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_08_01_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_08_01_off_1[] = {
    4, (s32)btlparty_hei_hei_08_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_09_01_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_09_01_off_1[] = {
    2, (s32)btlparty_hei_hei_09_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_09_01_off_2[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_09_01_off_2[] = {
    3, (s32)btlparty_hei_hei_09_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_09_03_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_09_03_off_1[] = {
    2, (s32)btlparty_hei_hei_09_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_09_03_off_2[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_09_03_off_2[] = {
    3, (s32)btlparty_hei_hei_09_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_hei_hei_10_01_off_1[] = {
    (s32)unit_gold_chorobon, 16777216, 67108868, 1123680256, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gold_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_10_01_off_1[] = {
    1, (s32)btlparty_hei_hei_10_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_11_01_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_11_01_off_1[] = {
    2, (s32)btlparty_hei_hei_11_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_11_01_off_2[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_11_01_off_2[] = {
    3, (s32)btlparty_hei_hei_11_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_11_03_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_11_03_off_1[] = {
    2, (s32)btlparty_hei_hei_11_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_11_03_off_2[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_11_03_off_2[] = {
    3, (s32)btlparty_hei_hei_11_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_12_01_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_hei_hei_12_01_off_1[] = {
    4, (s32)btlparty_hei_hei_12_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_02_off_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_02_off_1[] = {
    2, (s32)btlparty_hei_hei_13_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_02_on_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
    (s32)unit_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_1[] = {
    3, (s32)btlparty_hei_hei_13_02_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_02_on_2[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
    (s32)unit_kuriboo, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_2[] = {
    4, (s32)btlparty_hei_hei_13_02_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_02_on_3[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
    (s32)unit_kuriboo, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo, (s32)unit_kuriboo, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
    (s32)unit_kuriboo, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_02_on_3[] = {
    5, (s32)btlparty_hei_hei_13_02_on_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_03_off_1[] = {
    (s32)unit_togekuri, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_03_off_1[] = {
    2, (s32)btlparty_hei_hei_13_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_03_on_1[] = {
    (s32)unit_togekuri, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_03_on_1[] = {
    2, (s32)btlparty_hei_hei_13_03_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_03_on_2[] = {
    (s32)unit_togekuri, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
    (s32)unit_togekuri, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_03_on_2[] = {
    3, (s32)btlparty_hei_hei_13_03_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_04_off_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_04_off_1[] = {
    2, (s32)btlparty_hei_hei_13_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_04_on_1[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_04_on_1[] = {
    2, (s32)btlparty_hei_hei_13_04_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_hei_hei_13_04_on_2[] = {
    (s32)unit_patakuri, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
    (s32)unit_patakuri, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_patakuri, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_hei_hei_13_04_on_2[] = {
    4, (s32)btlparty_hei_hei_13_04_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test1_off[] = {
    50, (s32)btlgrp_hei_hei_01_01_off_1, (s32)hei_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test2_off[] = {
    50, (s32)btlgrp_hei_hei_01_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0xBEC), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test3_off[] = {
    50, (s32)btlgrp_hei_hei_01_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_test4_off[] = {
    50, (s32)btlgrp_hei_hei_01_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_01_01_off[] = {
    10, (s32)btlgrp_hei_hei_01_01_off_1, (s32)hei_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_02_off[] = {
    10, (s32)btlgrp_hei_hei_02_02_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_03_off[] = {
    10, (s32)btlgrp_hei_hei_02_03_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_02_04_off[] = {
    10, (s32)btlgrp_hei_hei_02_04_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_03_01_off[] = {
    10, (s32)btlgrp_hei_hei_03_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0xBEC), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_04_01_off[] = {
    10, (s32)btlgrp_hei_hei_04_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x6D0), 10, (s32)btlgrp_hei_hei_04_01_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x6D0), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_04_02_off[] = {
    10, (s32)btlgrp_hei_hei_04_02_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x51C), 10, (s32)btlgrp_hei_hei_04_02_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_05_01_off[] = {
    10, (s32)btlgrp_hei_hei_05_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_06_02_off[] = {
    10, (s32)btlgrp_hei_hei_06_02_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_06_03_off[] = {
    10, (s32)btlgrp_hei_hei_06_03_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0xA38), 10, (s32)btlgrp_hei_hei_06_03_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0xA38), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_07_01_off[] = {
    10, (s32)btlgrp_hei_hei_07_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0xF54), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_08_01_off[] = {
    10, (s32)btlgrp_hei_hei_08_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

__declspec(section ".data") s32 R_btlgrpsel_hei_btlno_hei_08_02_off[] = {
    10, (s32)btlgrp_hei_hei_08_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_09_01_off[] = {
    10, (s32)btlgrp_hei_hei_09_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 10, (s32)btlgrp_hei_hei_09_01_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_09_03_off[] = {
    10, (s32)btlgrp_hei_hei_09_03_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 10, (s32)btlgrp_hei_hei_09_03_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_10_01_off[] = {
    10, (s32)btlgrp_hei_hei_10_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_11_01_off[] = {
    10, (s32)btlgrp_hei_hei_11_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 10, (s32)btlgrp_hei_hei_11_01_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_11_03_off[] = {
    10, (s32)btlgrp_hei_hei_11_03_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 10, (s32)btlgrp_hei_hei_11_03_off_2, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_12_01_off[] = {
    10, (s32)btlgrp_hei_hei_12_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

__declspec(section ".data") s32 R_btlgrpsel_hei_btlno_hei_12_02_off[] = {
    10, (s32)btlgrp_hei_hei_12_01_off_1, (s32)(void*)((u8*)hei_btlstage_data + 0x1108), 0, 0, 0,
};

s32 btlgrpsel_hei_btlno_hei_13_02_off[] = {
    10, (s32)btlgrp_hei_hei_13_02_on_1, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_02_on_2, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_02_on_3,
    (s32)hei_btlstage_data, 50, (s32)btlgrp_hei_hei_13_02_off_1, (s32)hei_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_13_03_off[] = {
    50, (s32)btlgrp_hei_hei_13_03_on_1, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_03_on_2, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_03_off_1,
    (s32)hei_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_hei_btlno_hei_13_04_off[] = {
    50, (s32)btlgrp_hei_hei_13_04_on_1, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_04_on_2, (s32)hei_btlstage_data, 10, (s32)btlgrp_hei_hei_13_04_off_1,
    (s32)hei_btlstage_data, 0, 0, 0,
};

s32 btlsetup_hei_tbl[] = {
    (s32)/*"マップstg_01_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_01_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_01_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_01_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x34", 0, 0, -1, 0,
    (s32)btlgrpsel_hei_btlno_hei_test4_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei01クリボー"*/"\x68\x65\x69\x30\x31\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1,
    0, (s32)btlgrpsel_hei_btlno_hei_01_01_off, 0, 0, 84213760, 0, 1285, 0,
    0, 168427520, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei02パタクリ２"*/"\x68\x65\x69\x30\x32\x83\x70\x83\x5E\x83\x4E\x83\x8A\x82\x51", 0, 0,
    -1, 0, (s32)btlgrpsel_hei_btlno_hei_02_02_off, 0, 0, 84213760, 0, 1285,
    0, 84213760, 168427520, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei02ノコノコ"*/"\x68\x65\x69\x30\x32\x83\x6D\x83\x52\x83\x6D\x83\x52", 0,
    0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_02_03_off, 0, 0, 84213760, 0,
    1285, 0, 168427520, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei02トゲクリ"*/"\x68\x65\x69\x30\x32\x83\x67\x83\x51\x83\x4E\x83\x8A",
    0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_02_04_off, 0, 0, 84213760,
    0, 1285, 0, 84213760, 168427520, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"hei03シンノスケ"*/"\x68\x65\x69\x30\x33\x83\x56\x83\x93\x83\x6D\x83\x58\x83\x50", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_03_01_off, 536870927, 0,
    84213760, 0, 1285, 0, 84213760, 84213760, 16842752, 0,
    (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"hei04パタクリ"*/"\x68\x65\x69\x30\x34\x83\x70\x83\x5E\x83\x4E\x83\x8A", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_04_01_off, 0,
    0, 84213760, 0, 1285, 0, 84213760, 168427520, 16842752,
    0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei04ノコノコ"*/"\x68\x65\x69\x30\x34\x83\x6D\x83\x52\x83\x6D\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_04_02_off,
    0, 0, 84213760, 0, 1285, 0, 168427520, 84213760,
    16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei05トゲダルマー"*/"\x68\x65\x69\x30\x35\x83\x67\x83\x51\x83\x5F\x83\x8B\x83\x7D\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_hei_btlno_hei_05_01_off, 536870927, 0, 84213760, 0, 1285, 0, 84213760,
    84213760, 16842752, 0, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"hei06ノコノコ"*/"\x68\x65\x69\x30\x36\x83\x6D\x83\x52\x83\x6D\x83\x52", 0, 0, -1,
    0, (s32)btlgrpsel_hei_btlno_hei_06_02_off, 0, 0, 84213760, 0, 1285, 0,
    168427520, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei06パタクリ２"*/"\x68\x65\x69\x30\x36\x83\x70\x83\x5E\x83\x4E\x83\x8A\x82\x51", 0, 0,
    -1, 0, (s32)btlgrpsel_hei_btlno_hei_06_03_off, 0, 0, 84213760, 0, 1285,
    0, 84213760, 168427520, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei07モノクロシンエモン"*/"\x68\x65\x69\x30\x37\x83\x82\x83\x6D\x83\x4E\x83\x8D\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_07_01_off, 536870943, 0, 84213760, 0,
    1285, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"hei08チョロボン"*/"\x68\x65\x69\x30\x38\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_08_01_off, 536870928, 0, 84213760,
    0, 1285, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"hei08チョロボン２"*/"\x68\x65\x69\x30\x38\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x82\x51", 0, 0, -1, 0, (s32)R_btlgrpsel_hei_btlno_hei_08_02_off, 0, 0,
    84213760, 0, 1285, 0, 84213760, 84213760, 16842752, 0,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei09チョロボン1"*/"\x68\x65\x69\x30\x39\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x31", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_09_01_off, 0,
    0, 84213760, 0, 1285, 0, 84213760, 84213760, 16842752,
    0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei09チョロボン3"*/"\x68\x65\x69\x30\x39\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x33", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_09_03_off,
    0, 0, 84213760, 0, 1285, 0, 84213760, 84213760,
    16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei10ゴールドチョロボン"*/"\x68\x65\x69\x31\x30\x83\x53\x81\x5B\x83\x8B\x83\x68\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", (s32)"hei_10", 0, -1, 0,
    (s32)btlgrpsel_hei_btlno_hei_10_01_off, 536870928, 0, 84213760, 0, 1285, 0, 84213760,
    84213760, 16842752, 0, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"hei11チョロボン1"*/"\x68\x65\x69\x31\x31\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x31", 0, 0, -1,
    0, (s32)btlgrpsel_hei_btlno_hei_11_01_off, 0, 0, 84213760, 0, 1285, 0,
    84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei11チョロボン3"*/"\x68\x65\x69\x31\x31\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x33", 0, 0,
    -1, 0, (s32)btlgrpsel_hei_btlno_hei_11_03_off, 0, 0, 84213760, 0, 1285,
    0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei12チョロボン"*/"\x68\x65\x69\x31\x32\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_12_01_off, 536870928, 0, 84213760, 0,
    1285, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei12チョロボン２"*/"\x68\x65\x69\x31\x32\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93\x82\x51",
    0, 0, -1, 0, (s32)R_btlgrpsel_hei_btlno_hei_12_02_off, 0, 0, 84213760,
    0, 1285, 0, 84213760, 84213760, 16842752, 0, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"hei13クリボー2"*/"\x68\x65\x69\x31\x33\x83\x4E\x83\x8A\x83\x7B\x81\x5B\x32", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_13_02_off, 0, 0,
    84213760, 0, 1285, 0, 0, 84213760, 16842752, 0,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei13トゲクリ"*/"\x68\x65\x69\x31\x33\x83\x67\x83\x51\x83\x4E\x83\x8A", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_13_03_off, 0,
    0, 84213760, 0, 1285, 0, 0, 168427520, 16842752,
    0, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"hei13パタクリ"*/"\x68\x65\x69\x31\x33\x83\x70\x83\x5E\x83\x4E\x83\x8A", 0, 0, -1, 0, (s32)btlgrpsel_hei_btlno_hei_13_04_off,
    0, 0, 84213760, 0, 1285, 0, 0, 168427520,
    16842752, 0, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

s32 btl_hei_setup_no_tbl[] = {
    (s32)"BTLNO_HEI_TEST1", 0, (s32)"BTLNO_HEI_TEST2", 1, (s32)"BTLNO_HEI_TEST3", 2, (s32)"BTLNO_HEI_TEST4", 3,
    (s32)"BTLNO_HEI_01_01", 4, (s32)"BTLNO_HEI_02_02", 5, (s32)"BTLNO_HEI_02_03", 6, (s32)"BTLNO_HEI_02_04", 7,
    (s32)"BTLNO_HEI_03_01", 8, (s32)"BTLNO_HEI_04_01", 9, (s32)"BTLNO_HEI_04_02", 10, (s32)"BTLNO_HEI_05_01", 11,
    (s32)"BTLNO_HEI_06_02", 12, (s32)"BTLNO_HEI_06_03", 13, (s32)"BTLNO_HEI_07_01", 14, (s32)"BTLNO_HEI_08_01", 15,
    (s32)"BTLNO_HEI_08_02", 16, (s32)"BTLNO_HEI_09_01", 17, (s32)"BTLNO_HEI_09_03", 18, (s32)"BTLNO_HEI_10_01", 19,
    (s32)"BTLNO_HEI_11_01", 20, (s32)"BTLNO_HEI_11_03", 21, (s32)"BTLNO_HEI_12_01", 22, (s32)"BTLNO_HEI_12_02", 23,
    (s32)"BTLNO_HEI_13_02", 24, (s32)"BTLNO_HEI_13_03", 25, (s32)"BTLNO_HEI_13_04", 26, 0, 0,
};

