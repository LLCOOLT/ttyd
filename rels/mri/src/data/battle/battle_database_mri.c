#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_mapobj_flag_onoff);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_barriern[];
extern s32 battle_item_gundan_zako[];
extern s32 battle_item_magnum_battender[];
extern s32 battle_item_monochrome__pakkun[];
extern s32 battle_item_piders[];
extern s32 unit_barriern_19_data_2B8A8[];
extern s32 unit_boss_magnum_battender[];
extern s32 unit_gundan_zako_19_data_2A2B8[];
extern s32 unit_monochrome_pakkun_19_data_389E0[];
extern s32 unit_piders_19_data_2E9C8[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_mri_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_mri_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_mri___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_mri___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_mri_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_mri___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_mri_one_381[1];
__declspec(section ".data") u64 fd_battle_database_mri_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_mri_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_mri___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_mri___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_mri_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_mri___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_mri_one_364[1];
s32 mri_btlobject_data[258];
s32 mri_btlstage_data[436];
s32 btlparty_mri_mri_01_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_01_01[8];
__declspec(section ".data") s32 btlparty_mri_mri_04_01[12];
__declspec(section ".data") s32 btlgrp_mri_mri_04_01[8];
s32 btlparty_mri_mri_05_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_05_01[8];
s32 btlparty_mri_mri_06_2F_02[36];
__declspec(section ".data") s32 btlgrp_mri_mri_06_2F_02[8];
s32 btlparty_mri_mri_06_2F_03[48];
__declspec(section ".data") s32 btlgrp_mri_mri_06_2F_03[8];
s32 btlparty_mri_mri_12_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_12_01[8];
s32 btlparty_mri_mri_12_02[48];
__declspec(section ".data") s32 btlgrp_mri_mri_12_02[8];
s32 btlparty_mri_mri_15_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_15_01[8];
s32 btlparty_mri_mri_17_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_17_01[8];
s32 btlparty_mri_mri_18_02[36];
__declspec(section ".data") s32 btlgrp_mri_mri_18_02[8];
s32 btlparty_mri_mri_18_03[36];
__declspec(section ".data") s32 btlgrp_mri_mri_18_03[8];
s32 btlparty_mri_mri_19_01[24];
__declspec(section ".data") s32 btlgrp_mri_mri_19_01[8];
s32 btlparty_mri_mri_19_02[24];
__declspec(section ".data") s32 btlgrp_mri_mri_19_02[8];
s32 btlparty_mri_mri_19_04[48];
__declspec(section ".data") s32 btlgrp_mri_mri_19_04[8];
s32 btlparty_mri_mri_20_02[24];
__declspec(section ".data") s32 btlgrp_mri_mri_20_02[8];
s32 btlparty_mri_mri_20_03[36];
__declspec(section ".data") s32 btlgrp_mri_mri_20_03[8];
__declspec(section ".data") s32 btlparty_mri_mri_mb[12];
__declspec(section ".data") s32 btlgrp_mri_mri_mb[8];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_04_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_05_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_06_2f_02_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_06_2f_03_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_12_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_12_02_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_15_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_17_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_18_02_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_18_03_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_01_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_02_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_04_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_20_02_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_20_03_off[6];
__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_mb_off[6];
s32 btlsetup_mri_tbl[374];
s32 btl_mri_setup_no_tbl[44];
__declspec(section ".data") s32 stg_02_1_init_evt[8];

__declspec(section ".data") u64 fd_battle_database_mri_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_mri_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_mri___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_mri___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_mri_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_mri___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_mri_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_mri_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_mri_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_mri___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_mri___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_mri_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_mri___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_mri_one_364[] = {
    1065353216,
};

s32 mri_btlobject_data[] = {
    (s32)"S_isk_01", 131072, 1100480512, 0, -1034158080, 3932160, (s32)"S_ueki_01", 131073,
    -1019478016, 0, 1111490560, 3932160, (s32)"S_ueki_02", 131073, -1022164992, 0,
    -1034944512, 3932160, (s32)"S_ueki_03", 131073, -1033895936, 0, -1039138816, 3932160,
    (s32)"S_ueki_04", 131073, 1108869120, 0, -1042284544, 3932160, (s32)"S_ueki_05", 131073,
    1125974016, 0, -1035468800, 3932160, (s32)"S_ueki_06", 131073, 1128660992, 0,
    1113849856, 3932160, (s32)"S_ueki_07", 131073, -1018429440, 0, -1031798784, 3932160,
    (s32)"S_kusa_01", 131073, -1082130432, 0, 1117257728, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"S_isk_02", 131072, 1103626240, 0, -1034158080, 3932160,
    (s32)"S_ueki_01", 131073, -1019478016, 0, 1111490560, 3932160, (s32)"S_ueki_02", 131073,
    -1022164992, 0, -1034944512, 3932160, (s32)"S_ueki_03", 131073, -1033895936, 0,
    -1039138816, 3932160, (s32)"S_ueki_04", 131073, 1108869120, 0, -1042284544, 3932160,
    (s32)"S_ueki_05", 131073, 1125974016, 0, -1035468800, 3932160, (s32)"S_ueki_06", 131073,
    1128660992, 0, 1113849856, 3932160, (s32)"S_ueki_07", 131073, -1018429440, 0,
    -1031798784, 3932160, (s32)"S_kusa_01", 131073, -1082130432, 0, 1117257728, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"S_isk_03", 131072, 1094713344, 0,
    -1034158080, 3932160, (s32)"S_ueki_01", 131073, -1019478016, 0, 1111490560, 3932160,
    (s32)"S_ueki_02", 131073, -1022164992, 0, -1034944512, 3932160, (s32)"S_ueki_03", 131073,
    -1033895936, 0, -1039138816, 3932160, (s32)"S_ueki_04", 131073, 1108869120, 0,
    -1042284544, 3932160, (s32)"S_ueki_05", 131073, 1125974016, 0, -1035468800, 3932160,
    (s32)"S_ueki_06", 131073, 1128660992, 0, 1113849856, 3932160, (s32)"S_ueki_07", 131073,
    -1018429440, 0, -1031798784, 3932160, (s32)"S_kusa_01", 131073, -1082130432, 0,
    1117257728, 3932160, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"S_ueki_01", 131073,
    -1019478016, 0, 1111490560, 3932160, (s32)"S_ueki_02", 131073, -1022164992, 0,
    -1034944512, 3932160, (s32)"S_ueki_03", 131073, -1033895936, 0, -1036517376, 3932160,
    (s32)"S_ueki_04", 131073, 1108869120, 0, -1033633792, 3932160, (s32)"S_ueki_05", 131073,
    1125974016, 0, -1035468800, 3932160, (s32)"S_ueki_06", 131073, 1128660992, 0,
    1113849856, 3932160, (s32)"S_ueki_07", 131073, -1018429440, 0, -1031798784, 3932160,
    (s32)"S_kusa_01", 131073, -1082130432, 0, 1117257728, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160,
};

s32 mri_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_02_1", 11, (s32)mri_btlobject_data, 0, 0, 0, 0,
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
    0, 100, 0, 0, (s32)stg_02_1_init_evt, 0, 0, 0,
    0, 0, 0, 0, 65537, (s32)"bti_01", (s32)"stg_02_1", 11,
    (s32)(void*)((u8*)mri_btlobject_data + 0x108), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, (s32)stg_02_1_init_evt, 0, 0, 0, 0, 0, 0,
    0, 65537, (s32)"bti_01", (s32)"stg_02_1", 11, (s32)(void*)((u8*)mri_btlobject_data + 0x210), 0, 0,
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
    0, 0, 0, 100, 0, 0, (s32)stg_02_1_init_evt, 0,
    0, 0, 0, 0, 0, 0, 65537, (s32)"bti_01",
    (s32)"stg_02_1", 10, (s32)(void*)((u8*)mri_btlobject_data + 0x318), 0, 0, 0, 0, 1677721602,
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
    100, 0, 0, (s32)stg_02_1_init_evt, 0, 0, 0, 0,
    0, 0, 0, 65537,
};

s32 btlparty_mri_mri_01_01[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_mri_mri_01_01[] = {
    2, (s32)btlparty_mri_mri_01_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_mri_mri_04_01[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_mri_mri_04_01[] = {
    1, (s32)btlparty_mri_mri_04_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_05_01[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_mri_mri_05_01[] = {
    2, (s32)btlparty_mri_mri_05_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_06_2F_02[] = {
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_06_2F_02[] = {
    3, (s32)btlparty_mri_mri_06_2F_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_06_2F_03[] = {
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_06_2F_03[] = {
    4, (s32)btlparty_mri_mri_06_2F_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_12_01[] = {
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_mri_mri_12_01[] = {
    2, (s32)btlparty_mri_mri_12_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_mri_mri_12_02[] = {
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome__pakkun,
};

__declspec(section ".data") s32 btlgrp_mri_mri_12_02[] = {
    4, (s32)btlparty_mri_mri_12_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_mri_mri_15_01[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_mri_mri_15_01[] = {
    2, (s32)btlparty_mri_mri_15_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_17_01[] = {
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_17_01[] = {
    2, (s32)btlparty_mri_mri_17_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_18_02[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_gundan_zako,
    (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_barriern,
};

__declspec(section ".data") s32 btlgrp_mri_mri_18_02[] = {
    3, (s32)btlparty_mri_mri_18_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_18_03[] = {
    (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 0, 1109393408, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_barriern, (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1117126656,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_barriern,
    (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1125515264, 1109393408, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_barriern,
};

__declspec(section ".data") s32 btlgrp_mri_mri_18_03[] = {
    3, (s32)btlparty_mri_mri_18_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_19_01[] = {
    (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_19_01[] = {
    2, (s32)btlparty_mri_mri_19_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_19_02[] = {
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_19_02[] = {
    2, (s32)btlparty_mri_mri_19_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_mri_mri_19_04[] = {
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_monochrome_pakkun_19_data_389E0, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome__pakkun, (s32)unit_piders_19_data_2E9C8, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_mri_mri_19_04[] = {
    4, (s32)btlparty_mri_mri_19_04, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_mri_mri_20_02[] = {
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako, (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_barriern,
};

__declspec(section ".data") s32 btlgrp_mri_mri_20_02[] = {
    2, (s32)btlparty_mri_mri_20_02, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_mri_mri_20_03[] = {
    (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1092616192, 1109393408, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_barriern, (s32)unit_barriern_19_data_2B8A8, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_barriern,
    (s32)unit_gundan_zako_19_data_2A2B8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_gundan_zako,
};

__declspec(section ".data") s32 btlgrp_mri_mri_20_03[] = {
    3, (s32)btlparty_mri_mri_20_03, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_mri_mri_mb[] = {
    (s32)unit_boss_magnum_battender, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_magnum_battender,
};

__declspec(section ".data") s32 btlgrp_mri_mri_mb[] = {
    1, (s32)btlparty_mri_mri_mb, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test1_off[] = {
    50, (s32)btlgrp_mri_mri_01_01, (s32)mri_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test2_off[] = {
    50, (s32)btlgrp_mri_mri_01_01, (s32)(void*)((u8*)mri_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test3_off[] = {
    50, (s32)btlgrp_mri_mri_01_01, (s32)(void*)((u8*)mri_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_test4_off[] = {
    50, (s32)btlgrp_mri_mri_01_01, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_01_01_off[] = {
    10, (s32)btlgrp_mri_mri_01_01, (s32)mri_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_04_01_off[] = {
    10, (s32)btlgrp_mri_mri_04_01, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_05_01_off[] = {
    10, (s32)btlgrp_mri_mri_05_01, (s32)(void*)((u8*)mri_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_06_2f_02_off[] = {
    10, (s32)btlgrp_mri_mri_06_2F_02, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_06_2f_03_off[] = {
    10, (s32)btlgrp_mri_mri_06_2F_03, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_12_01_off[] = {
    10, (s32)btlgrp_mri_mri_12_01, (s32)(void*)((u8*)mri_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_12_02_off[] = {
    10, (s32)btlgrp_mri_mri_12_02, (s32)(void*)((u8*)mri_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_15_01_off[] = {
    10, (s32)btlgrp_mri_mri_15_01, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_17_01_off[] = {
    10, (s32)btlgrp_mri_mri_17_01, (s32)(void*)((u8*)mri_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_18_02_off[] = {
    10, (s32)btlgrp_mri_mri_18_02, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_18_03_off[] = {
    10, (s32)btlgrp_mri_mri_18_03, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_01_off[] = {
    10, (s32)btlgrp_mri_mri_19_01, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_02_off[] = {
    10, (s32)btlgrp_mri_mri_19_02, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_19_04_off[] = {
    10, (s32)btlgrp_mri_mri_19_04, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_20_02_off[] = {
    10, (s32)btlgrp_mri_mri_20_02, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_20_03_off[] = {
    10, (s32)btlgrp_mri_mri_20_03, (s32)(void*)((u8*)mri_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_mri_btlno_mri_mb_off[] = {
    10, (s32)btlgrp_mri_mri_mb, (s32)mri_btlstage_data, 0, 0, 0,
};

s32 btlsetup_mri_tbl[] = {
    (s32)/*"マップstg_02_1_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x32\x5F\x31\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_02_1_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x32\x5F\x31\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_02_1_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x32\x5F\x31\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_02_1_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x32\x5F\x31\x5F\x33", 0, 0, -1, 0,
    (s32)btlgrpsel_mri_btlno_mri_test4_off, 0, 0, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri01ぐんだんザコ"*/"\x6D\x72\x69\x30\x31\x82\xAE\x82\xF1\x82\xBE\x82\xF1\x83\x55\x83\x52", 0, 0, -1,
    0, (s32)btlgrpsel_mri_btlno_mri_01_01_off, 536870928, 0, 84216330, 0, 84215045, 0,
    84213760, 84215045, 16843009, 16843009, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"mri04ぐんだんザコ"*/"\x6D\x72\x69\x30\x34\x82\xAE\x82\xF1\x82\xBE\x82\xF1\x83\x55\x83\x52", 0, 0,
    -1, 0, (s32)btlgrpsel_mri_btlno_mri_04_01_off, 536870928, 0, 84216330, 0, 84215045,
    0, 84213760, 84215045, 16843009, 16843009, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"mri05ぐんだんザコ"*/"\x6D\x72\x69\x30\x35\x82\xAE\x82\xF1\x82\xBE\x82\xF1\x83\x55\x83\x52", 0,
    0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_05_01_off, 0, 0, 84216330, 0,
    84215045, 0, 84213760, 84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri06パイダース2F_２"*/"\x6D\x72\x69\x30\x36\x83\x70\x83\x43\x83\x5F\x81\x5B\x83\x58\x32\x46\x5F\x82\x51",
    0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_06_2f_02_off, 0, 0, 84215045,
    0, 84215045, 0, 84213760, 84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"mri06パイダース2F_３"*/"\x6D\x72\x69\x30\x36\x83\x70\x83\x43\x83\x5F\x81\x5B\x83\x58\x32\x46\x5F\x82\x52", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_06_2f_03_off, 0, 0,
    84215045, 0, 84215045, 0, 84213760, 84215045, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri12パックンフラワー"*/"\x6D\x72\x69\x31\x32\x83\x70\x83\x62\x83\x4E\x83\x93\x83\x74\x83\x89\x83\x8F\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_12_01_off, 0,
    0, 67372036, 0, 67372036, 2570, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri12パックンフラワー"*/"\x6D\x72\x69\x31\x32\x83\x70\x83\x62\x83\x4E\x83\x93\x83\x74\x83\x89\x83\x8F\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_12_02_off,
    0, 0, 67372036, 0, 67372036, 2570, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri15ぐんだんザコ"*/"\x6D\x72\x69\x31\x35\x82\xAE\x82\xF1\x82\xBE\x82\xF1\x83\x55\x83\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_mri_btlno_mri_15_01_off, 536870928, 0, 67373578, 0, 67372036, 2570, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_KOBOSS_BATTLE1", (s32)/*"mri17パイダース"*/"\x6D\x72\x69\x31\x37\x83\x70\x83\x43\x83\x5F\x81\x5B\x83\x58", 0, 0, -1,
    0, (s32)btlgrpsel_mri_btlno_mri_17_01_off, 0, 0, 67372036, 0, 67372036, 2570,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri18軍団ザコ"*/"\x6D\x72\x69\x31\x38\x8C\x52\x92\x63\x83\x55\x83\x52", 0, 0,
    -1, 0, (s32)btlgrpsel_mri_btlno_mri_18_02_off, 0, 0, 67373578, 0, 67372036,
    2570, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri18バリアーン"*/"\x6D\x72\x69\x31\x38\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_18_03_off, 0, 0, 67373578, 0,
    67372036, 2570, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri19パイダース"*/"\x6D\x72\x69\x31\x39\x83\x70\x83\x43\x83\x5F\x81\x5B\x83\x58",
    0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_19_01_off, 0, 0, 84216330,
    0, 84215045, 0, 84213760, 84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"mri19パックン１"*/"\x6D\x72\x69\x31\x39\x83\x70\x83\x62\x83\x4E\x83\x93\x82\x50", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_19_02_off, 0, 0,
    84215045, 0, 84215045, 0, 84213760, 84215045, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri19パックン３"*/"\x6D\x72\x69\x31\x39\x83\x70\x83\x62\x83\x4E\x83\x93\x82\x52", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_19_04_off, 0,
    0, 84215045, 0, 84215045, 0, 84213760, 84215045, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri20軍団ザコ"*/"\x6D\x72\x69\x32\x30\x8C\x52\x92\x63\x83\x55\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_mri_btlno_mri_20_02_off,
    0, 0, 84216330, 0, 84215045, 0, 84213760, 84215045,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"mri20バリアーン２"*/"\x6D\x72\x69\x32\x30\x83\x6F\x83\x8A\x83\x41\x81\x5B\x83\x93\x82\x51", 0, 0, -1, 0,
    (s32)btlgrpsel_mri_btlno_mri_20_03_off, 0, 0, 84216330, 0, 84215045, 0, 84213760,
    84215045, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マグナムバッテンダー"*/"\x83\x7D\x83\x4F\x83\x69\x83\x80\x83\x6F\x83\x62\x83\x65\x83\x93\x83\x5F\x81\x5B", (s32)"mri_01", 0, -1,
    0, (s32)btlgrpsel_mri_btlno_mri_mb_off, 536870928, 2, 2570, 0, 0, 2570,
    0, 0, 257, 16843009, (s32)"BGM_BOSS_STG3_3RDLEADER1", 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 btl_mri_setup_no_tbl[] = {
    (s32)"BTLNO_MRI_TEST1", 0, (s32)"BTLNO_MRI_TEST2", 1, (s32)"BTLNO_MRI_TEST3", 2, (s32)"BTLNO_MRI_TEST4", 3,
    (s32)"BTLNO_MRI_01_01", 4, (s32)"BTLNO_MRI_04_01", 5, (s32)"BTLNO_MRI_05_01", 6, (s32)"BTLNO_MRI_06_2F_02", 7,
    (s32)"BTLNO_MRI_06_2F_03", 8, (s32)"BTLNO_MRI_12_01", 9, (s32)"BTLNO_MRI_12_02", 10, (s32)"BTLNO_MRI_15_01", 11,
    (s32)"BTLNO_MRI_17_01", 12, (s32)"BTLNO_MRI_18_02", 13, (s32)"BTLNO_MRI_18_03", 14, (s32)"BTLNO_MRI_19_01", 15,
    (s32)"BTLNO_MRI_19_02", 16, (s32)"BTLNO_MRI_19_04", 17, (s32)"BTLNO_MRI_20_02", 18, (s32)"BTLNO_MRI_20_03", 19,
    (s32)"BTLNO_MRI_MB", 20, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(stg_02_1_init_evt)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("S_ueki"), 1)
    RETURN
EVT_END()

