#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"
#include "system.h"

f32 sinfd(f32 degrees);

static USER_FUNC(_wave_offset);
USER_FUNC(evt_eff64);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_cortez[];
extern s32 battle_item_flower_chorobon[];
extern s32 battle_item_green_chorobon[];
extern s32 battle_item_gundan_zako[];
extern s32 battle_item_kanbu1[];
extern s32 battle_item_poison_pakkun[];
extern s32 unit_boss_cortez[];
extern s32 unit_boss_gundan_zako_group1[];
extern s32 unit_boss_kanbu3[];
extern s32 unit_flower_chorobon[];
extern s32 unit_green_chorobon[];
extern s32 unit_hermos[];
extern s32 unit_kuriboo[];
extern s32 unit_poison_pakkun[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_muj_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_muj_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_muj___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_muj___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_muj_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_muj___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_muj_one_381[1];
__declspec(section ".data") u64 fd_battle_database_muj_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_muj_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_muj___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_muj___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_muj_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_muj___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_muj_one_364[1];
s32 muj_btlobject_data[186];
s32 muj_btlstage_data[436];
__declspec(section ".data") s32 btlparty_muj_muj_cortez[12];
__declspec(section ".data") s32 btlgrp_muj_muj_cortez[8];
s32 btlparty_muj_muj_kanbu[24];
__declspec(section ".data") s32 btlgrp_muj_muj_kanbu[8];
s32 btlparty_muj_muj_01_01[36];
__declspec(section ".data") s32 btlgrp_muj_muj_01_01[8];
s32 btlparty_muj_muj_05_01[36];
__declspec(section ".data") s32 btlgrp_muj_muj_05_01[8];
s32 btlparty_muj_muj_05_02[36];
__declspec(section ".data") s32 btlgrp_muj_muj_05_02[8];
s32 btlparty_muj_muj_00_01[36];
__declspec(section ".data") s32 btlgrp_muj_muj_00_01[8];
__declspec(section ".data") s32 btlparty_muj_muj_02_01_off_01[12];
__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_01[8];
s32 btlparty_muj_muj_02_01_off_02[24];
__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_02[8];
s32 btlparty_muj_muj_02_01_off_03[36];
__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_03[8];
s32 btlparty_muj_muj_02_01_off_04[48];
__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_04[8];
__declspec(section ".data") s32 btlparty_muj_muj_02_04_off_01[12];
__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_01[8];
s32 btlparty_muj_muj_02_04_off_02[24];
__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_02[8];
s32 btlparty_muj_muj_02_04_off_03[36];
__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_03[8];
s32 btlparty_muj_muj_02_07_off_01[24];
__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_01[8];
s32 btlparty_muj_muj_02_07_off_02[36];
__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_02[8];
s32 btlparty_muj_muj_02_07_off_03[48];
__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_03[8];
s32 btlparty_muj_muj_03_01_off_01[24];
__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_01[8];
s32 btlparty_muj_muj_03_01_off_02[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_02[8];
s32 btlparty_muj_muj_03_01_off_03[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_03[8];
s32 btlparty_muj_muj_03_02_off_01[24];
__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_01[8];
s32 btlparty_muj_muj_03_02_off_02[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_02[8];
s32 btlparty_muj_muj_03_02_off_03[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_03[8];
s32 btlparty_muj_muj_03_04_off_01[24];
__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_01[8];
s32 btlparty_muj_muj_03_04_off_02[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_02[8];
s32 btlparty_muj_muj_03_04_off_03[36];
__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_03[8];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_cortez_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_kanbu_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_05_01_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_05_02_off[6];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_01_off[12];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_02_off[12];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_07_off[12];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_01_off[12];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_02_off[12];
__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_04_off[12];
s32 btlsetup_muj_tbl[272];
s32 btl_muj_setup_no_tbl[32];
s32 bgset_muj_wave_event[59];
s32 bgset_muj_sun_event[18];

__declspec(section ".data") u64 fd_battle_database_muj_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_muj_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_muj___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_muj___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_muj_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_muj___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_muj_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_muj_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_muj_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_muj___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_muj___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_muj_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_muj___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_muj_one_364[] = {
    1065353216,
};

s32 muj_btlobject_data[] = {
    (s32)"A1", 131072, 0, 0, -1035468800, 3932160, (s32)"hata", 131073,
    1127350272, 0, -1035730944, 3932160, (s32)"iwa", 131073, -1019805696, 0,
    -1042284544, 171048960, (s32)"zai", 131073, 1123811328, 0, -1043333120, 338165760,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"A1", 131072, 0, 0,
    -1033895936, 3932160, (s32)"kusa_mae", 131073, 0, 0, 1116471296, 3932160,
    (s32)"kusa_usiro", 131073, 0, 0, -1037041664, 171048960, (s32)"kusa_01", 131073,
    -1029832704, 0, -1042284544, 338165760, (s32)"kusa_02", 131073, 1124073472, 0,
    -1039925248, 505282560, (s32)"necco", 131073, 0, 0, -1039663104, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"takara_01", 131073, 1121845248, 0,
    -1031143424, 3932160, (s32)"takara_02", 131073, -1028784128, 0, -1030750208, 171048960,
    (s32)"takara_03", 131073, 1124597760, 0, 1113849856, 338165760, (s32)"takara_04", 131073,
    -1019871232, 0, 1113849856, 505282560, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C_kabe", 131075, 0, 0, 0, 3932160,
    (s32)"nami_00", 131075, 0, 0, 0, 3932160, (s32)"nami_01", 131075,
    0, 0, 0, 3932160, (s32)"A1", 131072, 1121320960, 0,
    -1034682368, 3932160, (s32)"S_mae_l", 131073, -1028390912, 0, 1111490560, 3932160,
    (s32)"S_mae_r", 131073, 1118306304, 0, 1111490560, 3932160, (s32)"S_oku_l", 131073,
    -1039400960, 0, -1037565952, 3932160, (s32)"S_oku_r", 131073, 1108082688, 0,
    -1037565952, 3932160, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"if_wire", 327686,
    0, 1124204544, 0, 0, (s32)"if_body", 327686, 0, 1124204544,
    0, 0,
};

s32 muj_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_05_1", 6, (s32)muj_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, (s32)bgset_muj_sun_event, 0, (s32)"bti_01", (s32)"stg_05_2", 8,
    (s32)(void*)((u8*)muj_btlobject_data + 0x90), 0, 0, 0, 0, 1677721602, 0, 0,
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
    (s32)bgset_muj_sun_event, 0, (s32)"bti_01", (s32)"stg_05_5", 8, (s32)(void*)((u8*)muj_btlobject_data + 0x150), 0, 0,
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
    (s32)"stg_05_0", 9, (s32)(void*)((u8*)muj_btlobject_data + 0x210), 0, 0, 0, 0, 1677721602,
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
    0, 0, (s32)bgset_muj_sun_event, 0,
};

__declspec(section ".data") s32 btlparty_muj_muj_cortez[] = {
    (s32)unit_boss_cortez, 16777216, 67108868, 1125253120, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_cortez,
};

__declspec(section ".data") s32 btlgrp_muj_muj_cortez[] = {
    1, (s32)btlparty_muj_muj_cortez, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_kanbu[] = {
    (s32)unit_boss_gundan_zako_group1, 16777216, 67108868, 1117782016, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_boss_kanbu3, 16777216, 67108868, 1126170624,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_kanbu1,
};

__declspec(section ".data") s32 btlgrp_muj_muj_kanbu[] = {
    2, (s32)btlparty_muj_muj_kanbu, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_01_01[] = {
    (s32)unit_hermos, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_hermos, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_hermos, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_muj_muj_01_01[] = {
    3, (s32)btlparty_muj_muj_01_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_muj_muj_05_01[] = {
    (s32)unit_hermos, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_hermos, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_hermos, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_muj_muj_05_01[] = {
    3, (s32)btlparty_muj_muj_05_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_muj_muj_05_02[] = {
    (s32)unit_hermos, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_hermos, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_hermos, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_muj_muj_05_02[] = {
    3, (s32)btlparty_muj_muj_05_02, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_muj_muj_00_01[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_kuriboo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_muj_muj_00_01[] = {
    3, (s32)btlparty_muj_muj_00_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_muj_muj_02_01_off_01[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_01[] = {
    1, (s32)btlparty_muj_muj_02_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_01_off_02[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_green_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_02[] = {
    2, (s32)btlparty_muj_muj_02_01_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_01_off_03[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_green_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_green_chorobon,
    (s32)unit_green_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_03[] = {
    3, (s32)btlparty_muj_muj_02_01_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_01_off_04[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_green_chorobon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_green_chorobon,
    (s32)unit_green_chorobon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_green_chorobon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_01_off_04[] = {
    4, (s32)btlparty_muj_muj_02_01_off_04, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_muj_muj_02_04_off_01[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_01[] = {
    1, (s32)btlparty_muj_muj_02_04_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_04_off_02[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_02[] = {
    2, (s32)btlparty_muj_muj_02_04_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_04_off_03[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_04_off_03[] = {
    3, (s32)btlparty_muj_muj_02_04_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_07_off_01[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_01[] = {
    2, (s32)btlparty_muj_muj_02_07_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_07_off_02[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_green_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_02[] = {
    3, (s32)btlparty_muj_muj_02_07_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_02_07_off_03[] = {
    (s32)unit_green_chorobon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_green_chorobon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_02_07_off_03[] = {
    4, (s32)btlparty_muj_muj_02_07_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_03_01_off_01[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_01[] = {
    2, (s32)btlparty_muj_muj_03_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_01_off_02[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_green_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_02[] = {
    3, (s32)btlparty_muj_muj_03_01_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_01_off_03[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_poison_pakkun, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_01_off_03[] = {
    3, (s32)btlparty_muj_muj_03_01_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_02_off_01[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_01[] = {
    2, (s32)btlparty_muj_muj_03_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_02_off_02[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_02[] = {
    3, (s32)btlparty_muj_muj_03_02_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_02_off_03[] = {
    (s32)unit_poison_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_poison_pakkun, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_poison_pakkun,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_02_off_03[] = {
    3, (s32)btlparty_muj_muj_03_02_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_muj_muj_03_04_off_01[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_poison_pakkun, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_01[] = {
    2, (s32)btlparty_muj_muj_03_04_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_03_04_off_02[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_green_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_green_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_02[] = {
    3, (s32)btlparty_muj_muj_03_04_off_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_muj_muj_03_04_off_03[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_poison_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_poison_pakkun,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_muj_muj_03_04_off_03[] = {
    3, (s32)btlparty_muj_muj_03_04_off_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test1_off[] = {
    50, (s32)btlgrp_muj_muj_01_01, (s32)(void*)((u8*)muj_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test2_off[] = {
    50, (s32)btlgrp_muj_muj_01_01, (s32)muj_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test3_off[] = {
    50, (s32)btlgrp_muj_muj_01_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_test4_off[] = {
    50, (s32)btlgrp_muj_muj_01_01, (s32)(void*)((u8*)muj_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_cortez_off[] = {
    50, (s32)btlgrp_muj_muj_cortez, (s32)(void*)((u8*)muj_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_kanbu_off[] = {
    50, (s32)btlgrp_muj_muj_kanbu, (s32)(void*)((u8*)muj_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_01_01_off[] = {
    50, (s32)btlgrp_muj_muj_01_01, (s32)muj_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_05_01_off[] = {
    50, (s32)btlgrp_muj_muj_05_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_05_02_off[] = {
    50, (s32)btlgrp_muj_muj_05_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_01_off[] = {
    10, (s32)btlgrp_muj_muj_02_01_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 20, (s32)btlgrp_muj_muj_02_01_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_02_01_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_02_off[] = {
    10, (s32)btlgrp_muj_muj_02_04_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 20, (s32)btlgrp_muj_muj_02_04_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_02_04_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_02_07_off[] = {
    10, (s32)btlgrp_muj_muj_02_07_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 20, (s32)btlgrp_muj_muj_02_07_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_02_07_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_01_off[] = {
    10, (s32)btlgrp_muj_muj_03_01_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 20, (s32)btlgrp_muj_muj_03_01_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_03_01_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_02_off[] = {
    10, (s32)btlgrp_muj_muj_03_02_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 20, (s32)btlgrp_muj_muj_03_02_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_03_02_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_muj_btlno_muj_03_04_off[] = {
    10, (s32)btlgrp_muj_muj_03_04_off_01, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_03_04_off_02, (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 10, (s32)btlgrp_muj_muj_03_04_off_03,
    (s32)(void*)((u8*)muj_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_muj_tbl[] = {
    (s32)/*"マップstg_05_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_05_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_05_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_05_5"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x35", 0, 0, -1, 0,
    (s32)btlgrpsel_muj_btlno_muj_test4_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"コルテス"*/"\x83\x52\x83\x8B\x83\x65\x83\x58", (s32)"muj_12", 0, -1,
    0, (s32)btlgrpsel_muj_btlno_muj_cortez_off, 536870928, 6, 50529027, 50528256, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG5_KORTESS1", (s32)/*"幹部その３"*/"\x8A\xB2\x95\x94\x82\xBB\x82\xCC\x82\x52", (s32)"muj_00", 0,
    -1, 0, (s32)btlgrpsel_muj_btlno_muj_kanbu_off, 536870928, 0, 50529027, 50528256, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG3_3RDLEADER1", (s32)/*"MUJ01おんりょう１"*/"\x4D\x55\x4A\x30\x31\x82\xA8\x82\xF1\x82\xE8\x82\xE5\x82\xA4\x82\x50", 0,
    0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_01_01_off, 536870928, 0, 50529027, 50528256,
    50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"MUJ01おんりょう２"*/"\x4D\x55\x4A\x30\x31\x82\xA8\x82\xF1\x82\xE8\x82\xE5\x82\xA4\x82\x51",
    0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_05_01_off, 536870928, 0, 50529027,
    50528256, 50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1",
    (s32)/*"MUJ01おんりょう３"*/"\x4D\x55\x4A\x30\x31\x82\xA8\x82\xF1\x82\xE8\x82\xE5\x82\xA4\x82\x52", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_05_02_off, 0, 0,
    50529027, 50528256, 50529027, 50529027, 50528256, 50529027, 16843009, 16843009,
    (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"MUJ02グリーンチョロボン"*/"\x4D\x55\x4A\x30\x32\x83\x4F\x83\x8A\x81\x5B\x83\x93\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_02_01_off, 0,
    0, 50529027, 50528256, 50529027, 50529027, 50528256, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"MUJ02フラワーチョロボン"*/"\x4D\x55\x4A\x30\x32\x83\x74\x83\x89\x83\x8F\x81\x5B\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_02_02_off,
    0, 0, 50529027, 50528256, 50529027, 50529027, 50528256, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"MUJ02グリーンチョロボン"*/"\x4D\x55\x4A\x30\x32\x83\x4F\x83\x8A\x81\x5B\x83\x93\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_muj_btlno_muj_02_07_off, 0, 0, 50529027, 50528256, 50529027, 50529027, 50528256,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"MUJ03ポイズンパックン"*/"\x4D\x55\x4A\x30\x33\x83\x7C\x83\x43\x83\x59\x83\x93\x83\x70\x83\x62\x83\x4E\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_muj_btlno_muj_03_01_off, 0, 0, 50529027, 50528256, 50529027, 50529027,
    50528256, 50530826, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"MUJ03ポイズンパックン"*/"\x4D\x55\x4A\x30\x33\x83\x7C\x83\x43\x83\x59\x83\x93\x83\x70\x83\x62\x83\x4E\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_muj_btlno_muj_03_02_off, 0, 0, 50529027, 50528256, 50529027,
    50529027, 50528256, 50530826, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"MUJ03フラワーチョロボン"*/"\x4D\x55\x4A\x30\x33\x83\x74\x83\x89\x83\x8F\x81\x5B\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_muj_btlno_muj_03_04_off, 0, 0, 50529027, 50528256,
    50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s32 btl_muj_setup_no_tbl[] = {
    (s32)"BTLNO_MUJ_TEST1", 0, (s32)"BTLNO_MUJ_TEST2", 1, (s32)"BTLNO_MUJ_TEST3", 2, (s32)"BTLNO_MUJ_TEST4", 3,
    (s32)"BTLNO_MUJ_CORTEZ", 4, (s32)"BTLNO_MUJ_KANBU", 5, (s32)"BTLNO_MUJ_01_01", 6, (s32)"BTLNO_MUJ_05_01", 7,
    (s32)"BTLNO_MUJ_05_02", 8, (s32)"BTLNO_MUJ_02_01", 9, (s32)"BTLNO_MUJ_02_02", 10, (s32)"BTLNO_MUJ_02_07", 11,
    (s32)"BTLNO_MUJ_03_01", 12, (s32)"BTLNO_MUJ_03_02", 13, (s32)"BTLNO_MUJ_03_04", 14, 0, 0,
};

EVT_BEGIN(bgset_muj_wave_event)
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

EVT_BEGIN(bgset_muj_sun_event)
    CALL(evt_eff64, STRING("sunlight_bt"), STRING("sunlight_n64"), 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    RETURN
EVT_END()

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

