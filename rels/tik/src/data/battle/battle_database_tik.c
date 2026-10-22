#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"
#include "system.h"

f32 sinfd(f32 degrees);

static USER_FUNC(_wave_offset);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_flower_drop_param_default4[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_heart_drop_param_default4[];
extern s32 battle_item_gesso[];
extern s32 battle_item_hammer_bros[];
extern s32 battle_item_hannya[];
extern s32 battle_item_hennya[];
extern s32 battle_item_hinnya[];
extern s32 battle_item_kamec[];
extern s32 battle_item_kuriboo[];
extern s32 battle_item_kurikuri[];
extern s32 battle_item_nokonoko[];
extern s32 battle_item_patakuri[];
extern s32 battle_item_patapata[];
extern s32 battle_item_togekuri[];
extern s32 battle_item_togenoko[];
extern s32 unit_boss_gesso[];
extern s32 unit_hammer_bros_26_data_240F0[];
extern s32 unit_hannya_26_data_20220[];
extern s32 unit_hennya_26_data_30370[];
extern s32 unit_hinnya_26_data_20DE0[];
extern s32 unit_kamec[];
extern s32 unit_kuriboo_26_data_1CBF8[];
extern s32 unit_lecture_frankli_kuriboo[];
extern s32 unit_nokonoko_26_data_2DCC8[];
extern s32 unit_patakuri_26_data_21998[];
extern s32 unit_patapata_26_data_29498[];
extern s32 unit_togekuri_26_data_23050[];
extern s32 unit_togenoko[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_tik_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_tik_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_tik___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_tik___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_tik_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_tik___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_tik_one_381[1];
__declspec(section ".data") u64 fd_battle_database_tik_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_tik_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_tik___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_tik___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_tik_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_tik___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_tik_one_364[1];
s32 tik_btlobject_data[120];
s32 tik_btlstage_data[436];
__declspec(section ".data") s32 btlparty_tik_tik_gesso[12];
__declspec(section ".data") s32 btlgrp_tik_tik_gesso[8];
s32 btlparty_tik_tik_01_01_off_1[48];
__declspec(section ".data") s32 btlgrp_tik_tik_01_01_off_1[8];
s32 btlparty_tik_tik_01_02_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_01_02_off_1[8];
__declspec(section ".data") s32 btlparty_tik_tik_04_01_off_1[12];
__declspec(section ".data") s32 btlgrp_tik_tik_04_01_off_1[8];
__declspec(section ".data") s32 btlparty_tik_tik_04_01_on_1[12];
__declspec(section ".data") s32 btlgrp_tik_tik_04_01_on_1[8];
s32 btlparty_tik_tik_04_01_on_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_01_on_2[8];
s32 btlparty_tik_tik_04_02_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_02_off_1[8];
s32 btlparty_tik_tik_04_02_on_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_02_on_1[8];
s32 btlparty_tik_tik_04_02_on_2[36];
__declspec(section ".data") s32 btlgrp_tik_tik_04_02_on_2[8];
s32 btlparty_tik_tik_04_03_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_1[8];
s32 btlparty_tik_tik_04_03_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_2[8];
s32 btlparty_tik_tik_04_03_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_3[8];
s32 btlparty_tik_tik_04_04_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_1[8];
s32 btlparty_tik_tik_04_04_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_2[8];
s32 btlparty_tik_tik_04_04_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_3[8];
s32 btlparty_tik_tik_07_01_off_1[36];
__declspec(section ".data") s32 btlgrp_tik_tik_07_01_off_1[8];
s32 btlparty_tik_tik_07_01_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_01_off_2[8];
s32 btlparty_tik_tik_07_02_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_02_off_1[8];
s32 btlparty_tik_tik_07_02_off_2[36];
__declspec(section ".data") s32 btlgrp_tik_tik_07_02_off_2[8];
s32 btlparty_tik_tik_07_03_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_1[8];
s32 btlparty_tik_tik_07_03_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_2[8];
s32 btlparty_tik_tik_07_03_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_3[8];
s32 btlparty_tik_tik_07_04_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_1[8];
s32 btlparty_tik_tik_07_04_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_2[8];
s32 btlparty_tik_tik_07_04_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_3[8];
__declspec(section ".data") s32 btlparty_tik_tik_15_01_off_1[12];
__declspec(section ".data") s32 btlgrp_tik_tik_15_01_off_1[8];
__declspec(section ".data") s32 btlparty_tik_tik_15_02_off_1[12];
__declspec(section ".data") s32 btlgrp_tik_tik_15_02_off_1[8];
__declspec(section ".data") s32 btlparty_tik_tik_15_03_off_1[12];
__declspec(section ".data") s32 btlgrp_tik_tik_15_03_off_1[8];
s32 btlparty_tik_tik_15_04_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_1[8];
s32 btlparty_tik_tik_15_04_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_2[8];
s32 btlparty_tik_tik_15_04_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_3[8];
s32 btlparty_tik_tik_15_05_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_1[8];
s32 btlparty_tik_tik_15_05_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_2[8];
s32 btlparty_tik_tik_15_05_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_3[8];
s32 btlparty_tik_tik_18_01_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_01_off_1[8];
s32 btlparty_tik_tik_18_01_off_2[36];
__declspec(section ".data") s32 btlgrp_tik_tik_18_01_off_2[8];
s32 btlparty_tik_tik_18_02_off_1[48];
__declspec(section ".data") s32 btlgrp_tik_tik_18_02_off_1[8];
s32 btlparty_tik_tik_18_02_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_02_off_2[8];
s32 btlparty_tik_tik_18_03_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_1[8];
s32 btlparty_tik_tik_18_03_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_2[8];
s32 btlparty_tik_tik_18_03_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_3[8];
s32 btlparty_tik_tik_18_04_off_1[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_1[8];
s32 btlparty_tik_tik_18_04_off_2[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_2[8];
s32 btlparty_tik_tik_18_04_off_3[24];
__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_3[8];
s32 btlparty_tik_tik_20_01_off_1[60];
__declspec(section ".data") s32 btlgrp_tik_tik_20_01_off_1[8];
s32 btlparty_tik_tik_20_02_off_1[48];
__declspec(section ".data") s32 btlgrp_tik_tik_20_02_off_1[8];
s32 btlparty_tik_tik_20_03_off_1[36];
__declspec(section ".data") s32 btlgrp_tik_tik_20_03_off_1[8];
s32 btlparty_tik_tik_20_04_off_1[48];
__declspec(section ".data") s32 btlgrp_tik_tik_20_04_off_1[8];
s32 btlparty_tik_tik_20_05_off_1[60];
__declspec(section ".data") s32 btlgrp_tik_tik_20_05_off_1[8];
s32 btlparty_tik_tik_20_06_off_1[60];
__declspec(section ".data") s32 btlgrp_tik_tik_20_06_off_1[8];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_gesso_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_01_02_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_01_on[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_01_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_02_on[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_02_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_03_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_04_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_01_off[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_02_off[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_03_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_04_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_01_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_02_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_03_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_04_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_05_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_01_off[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_02_off[9];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_03_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_04_off[12];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_01_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_02_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_03_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_04_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_05_off[6];
__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_06_off[6];
s32 btlsetup_tik_tbl[510];
s32 btl_tik_setup_no_tbl[60];
s32 bgset_tik_wave_event[59];

__declspec(section ".data") u64 fd_battle_database_tik_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_tik_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_tik___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_tik___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_tik_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_tik___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_tik_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_tik_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_tik_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_tik___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_tik___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_tik_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_tik___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_tik_one_364[] = {
    1065353216,
};

s32 tik_btlobject_data[] = {
    (s32)"isi_2", 131072, -1021968384, 0, -1044905984, 171048960, (s32)"isi_3", 131072,
    -1032847360, 0, -1034420224, 338165760, (s32)"isi_4", 131072, 1127219200, 0,
    -1032323072, 505282560, (s32)"nami_0", 131074, 0, 0, 0, 3932160,
    (s32)"nami_1", 131074, 0, 0, 0, 3932160, (s32)"nami_2", 131074,
    0, 0, 0, 3932160, (s32)"nami_3", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"nami_0", 131074, 0, 0, 0, 3932160, (s32)"nami_1", 131074,
    0, 0, 0, 3932160, (s32)"nami_2", 131074, 0, 0,
    0, 3932160, (s32)"nami_3", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"B_0", 131074,
    0, 0, 0, 3932160, (s32)"jon_0", 131075, 0, 0,
    0, 3932160, (s32)"isi_1", 131073, -1018560512, 0, -1048051712, 3932160,
    (s32)"isi_2", 131073, 1128792064, 0, -1041235968, 171048960, (s32)"A1", 131072,
    0, 0, -1035468800, 3932160, (s32)"B_mati", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
};

s32 tik_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_00_2", 8, (s32)tik_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 65793, (s32)"bti_01", (s32)"stg_00_2", 5,
    (s32)(void*)((u8*)tik_btlobject_data + 0xC0), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_00_3", 2, (s32)(void*)((u8*)tik_btlobject_data + 0x138), 0, 0,
    0, 0, 1677721602, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 34603104,
    536870912, 1704706, 0, 0, 2047, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 0, 0, 0, 0,
    0, 0, 1677721602, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 34603104,
    536870912, 1704706, 0, 0, 2047, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 100, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)"bti_01",
    (s32)"stg_00_1", 5, (s32)(void*)((u8*)tik_btlobject_data + 0x168), 0, 0, 0, 0, 1677721602,
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
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlparty_tik_tik_gesso[] = {
    (s32)unit_boss_gesso, 16777216, 67108868, 1123287040, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gesso,
};

__declspec(section ".data") s32 btlgrp_tik_tik_gesso[] = {
    1, (s32)btlparty_tik_tik_gesso, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_01_01_off_1[] = {
    (s32)unit_kuriboo_26_data_1CBF8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kurikuri, (s32)unit_togekuri_26_data_23050, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
    (s32)unit_patakuri_26_data_21998, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri, (s32)unit_lecture_frankli_kuriboo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tik_tik_01_01_off_1[] = {
    4, (s32)btlparty_tik_tik_01_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_01_02_off_1[] = {
    (s32)unit_togekuri_26_data_23050, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri, (s32)unit_togekuri_26_data_23050, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_01_02_off_1[] = {
    2, (s32)btlparty_tik_tik_01_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tik_tik_04_01_off_1[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_01_off_1[] = {
    1, (s32)btlparty_tik_tik_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tik_tik_04_01_on_1[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_01_on_1[] = {
    1, (s32)btlparty_tik_tik_04_01_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_01_on_2[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_01_on_2[] = {
    2, (s32)btlparty_tik_tik_04_01_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_02_off_1[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_02_off_1[] = {
    2, (s32)btlparty_tik_tik_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_02_on_1[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_02_on_1[] = {
    2, (s32)btlparty_tik_tik_04_02_on_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_02_on_2[] = {
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_02_on_2[] = {
    3, (s32)btlparty_tik_tik_04_02_on_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_03_off_1[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_patapata_26_data_29498, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patapata,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_1[] = {
    2, (s32)btlparty_tik_tik_04_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_04_03_off_2[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_2[] = {
    2, (s32)btlparty_tik_tik_04_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_04_03_off_3[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_03_off_3[] = {
    2, (s32)btlparty_tik_tik_04_03_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_04_04_off_1[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_togekuri_26_data_23050, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_1[] = {
    2, (s32)btlparty_tik_tik_04_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_04_off_2[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_2[] = {
    2, (s32)btlparty_tik_tik_04_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_04_04_off_3[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_04_04_off_3[] = {
    2, (s32)btlparty_tik_tik_04_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_01_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_01_off_1[] = {
    3, (s32)btlparty_tik_tik_07_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_01_off_2[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_01_off_2[] = {
    2, (s32)btlparty_tik_tik_07_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_02_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_02_off_1[] = {
    2, (s32)btlparty_tik_tik_07_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_02_off_2[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_02_off_2[] = {
    3, (s32)btlparty_tik_tik_07_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_03_off_1[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_nokonoko_26_data_2DCC8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_1[] = {
    2, (s32)btlparty_tik_tik_07_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_03_off_2[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_2[] = {
    2, (s32)btlparty_tik_tik_07_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_03_off_3[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hammer_bros,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_03_off_3[] = {
    2, (s32)btlparty_tik_tik_07_03_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_07_04_off_1[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_1[] = {
    2, (s32)btlparty_tik_tik_07_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_tik_tik_07_04_off_2[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hammer_bros,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_2[] = {
    2, (s32)btlparty_tik_tik_07_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_tik_tik_07_04_off_3[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_07_04_off_3[] = {
    2, (s32)btlparty_tik_tik_07_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

__declspec(section ".data") s32 btlparty_tik_tik_15_01_off_1[] = {
    (s32)unit_kuriboo_26_data_1CBF8, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_01_off_1[] = {
    1, (s32)btlparty_tik_tik_15_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tik_tik_15_02_off_1[] = {
    (s32)unit_patakuri_26_data_21998, 16777216, 67108868, 1119092736, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_02_off_1[] = {
    1, (s32)btlparty_tik_tik_15_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tik_tik_15_03_off_1[] = {
    (s32)unit_togekuri_26_data_23050, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togekuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_03_off_1[] = {
    1, (s32)btlparty_tik_tik_15_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_15_04_off_1[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_kuriboo_26_data_1CBF8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kuriboo,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_1[] = {
    2, (s32)btlparty_tik_tik_15_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_tik_tik_15_04_off_2[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hammer_bros,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_2[] = {
    2, (s32)btlparty_tik_tik_15_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_tik_tik_15_04_off_3[] = {
    (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_04_off_3[] = {
    2, (s32)btlparty_tik_tik_15_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_tik_tik_15_05_off_1[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_patakuri_26_data_21998, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_1[] = {
    2, (s32)btlparty_tik_tik_15_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_15_05_off_2[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_2[] = {
    2, (s32)btlparty_tik_tik_15_05_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_15_05_off_3[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_hammer_bros_26_data_240F0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hammer_bros,
};

__declspec(section ".data") s32 btlgrp_tik_tik_15_05_off_3[] = {
    2, (s32)btlparty_tik_tik_15_05_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_18_01_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_01_off_1[] = {
    2, (s32)btlparty_tik_tik_18_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_01_off_2[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_01_off_2[] = {
    3, (s32)btlparty_tik_tik_18_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_02_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_02_off_1[] = {
    4, (s32)btlparty_tik_tik_18_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_02_off_2[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hinnya_26_data_20DE0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_02_off_2[] = {
    2, (s32)btlparty_tik_tik_18_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_03_off_1[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_patakuri_26_data_21998, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patakuri,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_1[] = {
    2, (s32)btlparty_tik_tik_18_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_18_03_off_2[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_2[] = {
    2, (s32)btlparty_tik_tik_18_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_18_03_off_3[] = {
    (s32)unit_kamec, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_03_off_3[] = {
    2, (s32)btlparty_tik_tik_18_03_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_tik_tik_18_04_off_1[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_1[] = {
    2, (s32)btlparty_tik_tik_18_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_04_off_2[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_togenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_togenoko,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_2[] = {
    2, (s32)btlparty_tik_tik_18_04_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_18_04_off_3[] = {
    (s32)unit_togenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko, (s32)unit_kamec, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tik_tik_18_04_off_3[] = {
    2, (s32)btlparty_tik_tik_18_04_off_3, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_01_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_01_off_1[] = {
    5, (s32)btlparty_tik_tik_20_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_02_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_02_off_1[] = {
    4, (s32)btlparty_tik_tik_20_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_03_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_03_off_1[] = {
    3, (s32)btlparty_tik_tik_20_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_04_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_04_off_1[] = {
    4, (s32)btlparty_tik_tik_20_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_05_off_1[] = {
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_05_off_1[] = {
    5, (s32)btlparty_tik_tik_20_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_tik_tik_20_06_off_1[] = {
    (s32)unit_hennya_26_data_30370, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya_26_data_20220, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_tik_tik_20_06_off_1[] = {
    5, (s32)btlparty_tik_tik_20_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test1_off[] = {
    50, (s32)btlgrp_tik_tik_01_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test2_off[] = {
    50, (s32)btlgrp_tik_tik_01_01_off_1, (s32)tik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_test3_off[] = {
    50, (s32)btlgrp_tik_tik_01_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_gesso_off[] = {
    50, (s32)btlgrp_tik_tik_gesso, (s32)tik_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_01_01_off[] = {
    50, (s32)btlgrp_tik_tik_01_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_01_02_off[] = {
    50, (s32)btlgrp_tik_tik_01_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_01_on[] = {
    20, (s32)btlgrp_tik_tik_04_01_on_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_01_on_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_01_off[] = {
    20, (s32)btlgrp_tik_tik_04_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_02_on[] = {
    20, (s32)btlgrp_tik_tik_04_02_on_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_02_on_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_02_off[] = {
    20, (s32)btlgrp_tik_tik_04_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_03_off[] = {
    20, (s32)btlgrp_tik_tik_04_03_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_03_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_03_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_04_04_off[] = {
    20, (s32)btlgrp_tik_tik_04_04_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_04_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_04_04_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_01_off[] = {
    20, (s32)btlgrp_tik_tik_07_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_01_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_02_off[] = {
    20, (s32)btlgrp_tik_tik_07_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_02_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_03_off[] = {
    20, (s32)btlgrp_tik_tik_07_03_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_03_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_03_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_07_04_off[] = {
    20, (s32)btlgrp_tik_tik_07_04_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_04_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_07_04_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_01_off[] = {
    20, (s32)btlgrp_tik_tik_15_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_02_off[] = {
    20, (s32)btlgrp_tik_tik_15_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_03_off[] = {
    20, (s32)btlgrp_tik_tik_15_03_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_04_off[] = {
    20, (s32)btlgrp_tik_tik_15_04_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_15_04_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_15_04_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_15_05_off[] = {
    20, (s32)btlgrp_tik_tik_15_05_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_15_05_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_15_05_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_01_off[] = {
    20, (s32)btlgrp_tik_tik_18_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_01_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_02_off[] = {
    20, (s32)btlgrp_tik_tik_18_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_02_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_03_off[] = {
    20, (s32)btlgrp_tik_tik_18_03_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_03_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_03_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_18_04_off[] = {
    20, (s32)btlgrp_tik_tik_18_04_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_04_off_2, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 20, (s32)btlgrp_tik_tik_18_04_off_3,
    (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_01_off[] = {
    20, (s32)btlgrp_tik_tik_20_01_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_02_off[] = {
    20, (s32)btlgrp_tik_tik_20_02_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_03_off[] = {
    20, (s32)btlgrp_tik_tik_20_03_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_04_off[] = {
    20, (s32)btlgrp_tik_tik_20_04_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_05_off[] = {
    20, (s32)btlgrp_tik_tik_20_05_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tik_btlno_tik_20_06_off[] = {
    20, (s32)btlgrp_tik_tik_20_06_off_1, (s32)(void*)((u8*)tik_btlstage_data + 0x51C), 0, 0, 0,
};

s32 btlsetup_tik_tbl[] = {
    (s32)/*"マップstg_00_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_00_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_00_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik12ゲッソー"*/"\x74\x69\x6B\x31\x32\x83\x51\x83\x62\x83\x5C\x81\x5B", (s32)"tik_02", 0, -1, 0,
    (s32)btlgrpsel_tik_btlno_tik_gesso_off, 536870928, 0, 84213760, 0, 1285, 0, 0,
    84213760, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"tik01クリボー３人衆"*/"\x74\x69\x6B\x30\x31\x83\x4E\x83\x8A\x83\x7B\x81\x5B\x82\x52\x90\x6C\x8F\x4F", (s32)"tik_01", 0, -1,
    0, (s32)btlgrpsel_tik_btlno_tik_01_01_off, 536870928, 0, 0, 0, 0, 0,
    0, 84213760, 257, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik01トゲクリボー"*/"\x74\x69\x6B\x30\x31\x83\x67\x83\x51\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0,
    -1, 0, (s32)btlgrpsel_tik_btlno_tik_01_02_off, 0, 0, 84213760, 0, 1285,
    0, 0, 168427520, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik04ヒンニャー1"*/"\x74\x69\x6B\x30\x34\x83\x71\x83\x93\x83\x6A\x83\x83\x81\x5B\x31", 0,
    0, -129998754, (s32)btlgrpsel_tik_btlno_tik_04_01_on, (s32)btlgrpsel_tik_btlno_tik_04_01_off, 0, 0, 84213760, 0,
    1285, 0, 0, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik04ヒンニャー2"*/"\x74\x69\x6B\x30\x34\x83\x71\x83\x93\x83\x6A\x83\x83\x81\x5B\x32",
    0, 0, -129998754, (s32)btlgrpsel_tik_btlno_tik_04_02_on, (s32)btlgrpsel_tik_btlno_tik_04_02_off, 0, 0, 84213760,
    0, 1285, 0, 0, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"tik04カメック"*/"\x74\x69\x6B\x30\x34\x83\x4A\x83\x81\x83\x62\x83\x4E", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_04_03_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik04トゲノコ"*/"\x74\x69\x6B\x30\x34\x83\x67\x83\x51\x83\x6D\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_04_04_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik07ハンニャー1"*/"\x74\x69\x6B\x30\x37\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B\x31", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_07_01_off,
    0, 0, 84213760, 0, 84215045, 0, 84213760, 84215045,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik07ハンニャー2"*/"\x74\x69\x6B\x30\x37\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B\x32", 0, 0, -1, 0,
    (s32)btlgrpsel_tik_btlno_tik_07_02_off, 0, 0, 84213760, 0, 84215045, 0, 84213760,
    84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik07トゲノコ"*/"\x74\x69\x6B\x30\x37\x83\x67\x83\x51\x83\x6D\x83\x52", 0, 0, -1,
    0, (s32)btlgrpsel_tik_btlno_tik_07_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik07ハンマーブロス"*/"\x74\x69\x6B\x30\x37\x83\x6E\x83\x93\x83\x7D\x81\x5B\x83\x75\x83\x8D\x83\x58", 0, 0,
    -1, 0, (s32)btlgrpsel_tik_btlno_tik_07_04_off, 0, 0, 50529027, 50529034, 167969539,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik15クリボー"*/"\x74\x69\x6B\x31\x35\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0,
    0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_15_01_off, 0, 0, 84213760, 0,
    1285, 0, 0, 168427520, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik15パタクリボー"*/"\x74\x69\x6B\x31\x35\x83\x70\x83\x5E\x83\x4E\x83\x8A\x83\x7B\x81\x5B",
    0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_15_02_off, 0, 0, 84213760,
    0, 1285, 0, 0, 168427520, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"tik15トゲクリボー"*/"\x74\x69\x6B\x31\x35\x83\x67\x83\x51\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_15_03_off, 0, 0,
    84213760, 0, 1285, 0, 0, 168427520, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik15ハンマーブロス"*/"\x74\x69\x6B\x31\x35\x83\x6E\x83\x93\x83\x7D\x81\x5B\x83\x75\x83\x8D\x83\x58", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_15_04_off, 0,
    0, 50529027, 50529034, 167969539, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik15カメック"*/"\x74\x69\x6B\x31\x35\x83\x4A\x83\x81\x83\x62\x83\x4E", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_15_05_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik18ハンニャー1"*/"\x74\x69\x6B\x31\x38\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B\x31", 0, 0, -1, 0,
    (s32)btlgrpsel_tik_btlno_tik_18_01_off, 0, 0, 84213760, 0, 84215045, 0, 84213760,
    84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik18ハンニャー2"*/"\x74\x69\x6B\x31\x38\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B\x32", 0, 0, -1,
    0, (s32)btlgrpsel_tik_btlno_tik_18_02_off, 0, 0, 84213760, 0, 84215045, 0,
    84213760, 84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik18カメック"*/"\x74\x69\x6B\x31\x38\x83\x4A\x83\x81\x83\x62\x83\x4E", 0, 0,
    -1, 0, (s32)btlgrpsel_tik_btlno_tik_18_03_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik18トゲノコ"*/"\x74\x69\x6B\x31\x38\x83\x67\x83\x51\x83\x6D\x83\x52", 0,
    0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_18_04_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik20ハンニャー"*/"\x74\x69\x6B\x32\x30\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B",
    0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_20_01_off, 0, 0, 33686018,
    33686018, 33686018, 33686018, 33686018, 33686018, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"tik20ハンニャー"*/"\x74\x69\x6B\x32\x30\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_20_02_off, 0, 0,
    33686018, 33686018, 33686018, 33686018, 33686018, 33686018, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik20ハンニャー"*/"\x74\x69\x6B\x32\x30\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_20_03_off, 0,
    0, 33686018, 33686018, 33686018, 33686018, 33686018, 33686018, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik20ハンニャー"*/"\x74\x69\x6B\x32\x30\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_tik_btlno_tik_20_04_off,
    0, 0, 33686018, 33686018, 33686018, 33686018, 33686018, 33686018,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik20ハンニャー"*/"\x74\x69\x6B\x32\x30\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_tik_btlno_tik_20_05_off, 0, 0, 33686018, 33686018, 33686018, 33686018, 33686018,
    33686018, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"tik20ヘンニャー"*/"\x74\x69\x6B\x32\x30\x83\x77\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1,
    0, (s32)btlgrpsel_tik_btlno_tik_20_06_off, 0, 0, 33686018, 33686018, 33686018, 33686018,
    33686018, 33686018, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 btl_tik_setup_no_tbl[] = {
    (s32)"BTLNO_TIK_TEST1", 0, (s32)"BTLNO_TIK_TEST2", 1, (s32)"BTLNO_TIK_TEST3", 2, (s32)"BTLNO_TIK_GESSO", 3,
    (s32)"BTLNO_TIK_01_01", 4, (s32)"BTLNO_TIK_01_02", 5, (s32)"BTLNO_TIK_04_01", 6, (s32)"BTLNO_TIK_04_02", 7,
    (s32)"BTLNO_TIK_04_03", 8, (s32)"BTLNO_TIK_04_04", 9, (s32)"BTLNO_TIK_07_01", 10, (s32)"BTLNO_TIK_07_02", 11,
    (s32)"BTLNO_TIK_07_03", 12, (s32)"BTLNO_TIK_07_04", 13, (s32)"BTLNO_TIK_15_01", 14, (s32)"BTLNO_TIK_15_02", 15,
    (s32)"BTLNO_TIK_15_03", 16, (s32)"BTLNO_TIK_15_04", 17, (s32)"BTLNO_TIK_15_05", 18, (s32)"BTLNO_TIK_18_01", 19,
    (s32)"BTLNO_TIK_18_02", 20, (s32)"BTLNO_TIK_18_03", 21, (s32)"BTLNO_TIK_18_04", 22, (s32)"BTLNO_TIK_20_01", 23,
    (s32)"BTLNO_TIK_20_02", 24, (s32)"BTLNO_TIK_20_03", 25, (s32)"BTLNO_TIK_20_04", 26, (s32)"BTLNO_TIK_20_05", 27,
    (s32)"BTLNO_TIK_20_06", 28, 0, 0,
};

static USER_FUNC(_wave_offset) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 varX = args[1];
    s32 stepX = evtGetValue(event, varX);
    s32 periodX = evtGetValue(event, args[2]);
    s32 ampX = evtGetValue(event, args[3]);
    s32 varY = args[4];
    s32 stepY = evtGetValue(event, varY);
    s32 periodY = evtGetValue(event, args[5]);
    s32 ampY = evtGetValue(event, args[6]);
    BattleStageObject* obj = BattleSearchObjectPtr(name);

    obj->positionOffset.x = ampX * sinfd(stepX * 360 / periodX);
    obj->positionOffset.y = ampY * sinfd(stepY * 360 / periodY + 270) + ampY;
    stepX++;
    if (stepX >= periodX) {
        stepX = 0;
    }
    evtSetValue(event, varX, stepX);
    stepY++;
    if (stepY >= periodY) {
        stepY = 0;
    }
    evtSetValue(event, varY, stepY);
    return EVT_RETURN_DONE;
}

EVT_BEGIN(bgset_tik_wave_event)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    SET_VALUE(LW(3), 0)
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    SET_VALUE(LW(7), 0)
    LABEL(0)
    CALL(_wave_offset, STRING("nami_1"), LW(2), 600, 20, LW(3), 250, 6)
    CALL(_wave_offset, STRING("nami_2"), LW(4), 1100, 40, LW(5), 360, 7)
    CALL(_wave_offset, STRING("nami_3"), LW(6), 1250, 50, LW(7), 450, 8)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

