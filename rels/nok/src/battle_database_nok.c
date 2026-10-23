#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"

#pragma force_active on

extern s32 unit_act_mario[];

__declspec(section ".data") u64 fd_battle_database_nok_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_nok_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_nok___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_nok___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_nok_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_nok___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_nok_one_381[1];
__declspec(section ".data") u64 fd_battle_database_nok_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_nok_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_nok___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_nok___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_nok_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_nok___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_nok_one_364[1];
s32 nok_btlobject_data[60];
s32 nok_btlstage_data[109];
__declspec(section ".data") s32 btlparty_nok_hei_ep[12];
__declspec(section ".data") s32 btlgrp_nok_hei_ep[8];
__declspec(section ".data") s32 btlgrpsel_nok_btlno_hei_test1_off[6];
s32 btlsetup_nok_tbl[34];
__declspec(section ".data") s32 btl_nok_setup_no_tbl[4];

__declspec(section ".data") u64 fd_battle_database_nok_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_nok_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_nok___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_nok___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_nok_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_nok___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_nok_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_nok_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_nok_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_nok___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_nok___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_nok_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_nok___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_nok_one_364[] = {
    1065353216,
};

s32 nok_btlobject_data[] = {
    (s32)"ki_1", 131072, -1027080192, 0, -1041235968, 3932160, (s32)"isi_A", 131072,
    1125515264, 0, -1041235968, 171048960, (s32)"isi_B", 131072, 1112014848, 0,
    -1039663104, 338165760, (s32)"isigaki", 131073, 1073741824, 0, -1044905984, 3932160,
    (s32)"kusa_1", 131073, -1019740160, 0, 1108606976, 171048960, (s32)"kusa_2", 131073,
    1127481344, 0, 1114636288, 338165760, (s32)"kusa_3", 131073, 1116471296, 0,
    1115815936, 505282560, (s32)"kusa_4", 131073, -1028784128, 0, 1113587712, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160,
};

s32 nok_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_04_0", 10, (s32)nok_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlparty_nok_hei_ep[] = {
    (s32)unit_act_mario, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_nok_hei_ep[] = {
    1, (s32)btlparty_nok_hei_ep, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_nok_btlno_hei_test1_off[] = {
    50, (s32)btlgrp_nok_hei_ep, (s32)nok_btlstage_data, 0, 0, 0,
};

s32 btlsetup_nok_tbl[] = {
    (s32)/*"マップstg_01_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x31\x5F\x30", (s32)"nok_01", 0, -1, 0, (s32)btlgrpsel_nok_btlno_hei_test1_off, 1048576, 6,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

__declspec(section ".data") s32 btl_nok_setup_no_tbl[] = {
    (s32)"BTLNO_HEI_TEST1", 0, 0, 0,
};

