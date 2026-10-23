#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

USER_FUNC(evt_map_set_tevcallback);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(tou_gamen_screen_tev_init);
extern s32 battle_heart_drop_param_default[];
extern s32 battle_item_basabasa[];
extern s32 battle_item_bllizard[];
extern s32 battle_item_bomhei[];
extern s32 battle_item_boomerang_bros[];
extern s32 battle_item_borodo[];
extern s32 battle_item_borodo_king[];
extern s32 battle_item_burst_wanwan[];
extern s32 battle_item_champion[];
extern s32 battle_item_dokugassun[];
extern s32 battle_item_fire_bros[];
extern s32 battle_item_hammer_bros[];
extern s32 battle_item_hyper_sinnosuke[];
extern s32 battle_item_hyper_togemet[];
extern s32 battle_item_iron_sinemon[];
extern s32 battle_item_iron_sinemon2[];
extern s32 battle_item_kamec[];
extern s32 battle_item_kurikuri[];
extern s32 battle_item_kurokumorn[];
extern s32 battle_item_macho_gance[];
extern s32 battle_item_monban[];
extern s32 battle_item_nokonoko_fighter[];
extern s32 battle_item_patapata_fighter[];
extern s32 battle_item_sambo[];
extern s32 battle_item_togezo[];
extern s32 battle_item_ura_noko[];
extern s32 battle_item_ura_pata[];
extern s32 tou_gamen_screen_tev[];
extern s32 unit_basabasa[];
extern s32 unit_bomhei[];
extern s32 unit_boomerang_bros[];
extern s32 unit_borodo[];
extern s32 unit_borodo_king[];
extern s32 unit_boss_champion[];
extern s32 unit_boss_koopa_tou[];
extern s32 unit_boss_macho_gance[];
extern s32 unit_burst_wanwan[];
extern s32 unit_chorobon[];
extern s32 unit_crimson_togemet[];
extern s32 unit_dark_keeper[];
extern s32 unit_fire_bros[];
extern s32 unit_flower_chorobon[];
extern s32 unit_green_chorobon[];
extern s32 unit_hammer_bros[];
extern s32 unit_hannya[];
extern s32 unit_hinnya[];
extern s32 unit_honenoko[];
extern s32 unit_hyper_sinnosuke[];
extern s32 unit_iron_sinemon[];
extern s32 unit_iron_sinemon2[];
extern s32 unit_jyugem[];
extern s32 unit_kamec_green[];
extern s32 unit_kamec_red[];
extern s32 unit_kamec_white[];
extern s32 unit_kurikuri[];
extern s32 unit_monochrome_kurokumorn[];
extern s32 unit_monochrome_pakkun[];
extern s32 unit_nokonoko_fighter[];
extern s32 unit_patapata_fighter[];
extern s32 unit_piders[];
extern s32 unit_sambo[];
extern s32 unit_togedaruma[];
extern s32 unit_togenoko_ace[];
extern s32 unit_togezo[];
extern s32 unit_ura_noko[];
extern s32 unit_ura_pata[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_tou_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_tou_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_tou___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_tou___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_tou_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_tou___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_tou_one_381[1];
__declspec(section ".data") u64 fd_battle_database_tou_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_tou_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_tou___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_tou___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_tou_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_tou___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_tou_one_364[1];
s32 tou_btlobject_data[84];
s32 tou_btlstage_data[218];
s32 btlparty_tou_tou_rank_19[60];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_19[8];
s32 btlparty_tou_tou_rank_18[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_18[8];
s32 btlparty_tou_tou_rank_17[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_17[8];
s32 btlparty_tou_tou_rank_16[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_16[8];
s32 btlparty_tou_tou_rank_15[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_15[8];
s32 btlparty_tou_tou_rank_14[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_14[8];
s32 btlparty_tou_tou_rank_13[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_13[8];
s32 btlparty_tou_tou_rank_12[48];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_12[8];
s32 btlparty_tou_tou_rank_11[48];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_11[8];
s32 btlparty_tou_tou_rank_10[24];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_10[8];
s32 btlparty_tou_tou_rank_9[24];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_9[8];
s32 btlparty_tou_tou_rank_8[24];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_8[8];
s32 btlparty_tou_tou_rank_7[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_7[8];
s32 btlparty_tou_tou_rank_6[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_6[8];
s32 btlparty_tou_tou_rank_5[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_5[8];
__declspec(section ".data") s32 btlparty_tou_tou_rank_4[12];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_4[8];
s32 btlparty_tou_tou_rank_3[36];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_3[8];
s32 btlparty_tou_tou_rank_2[24];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_2[8];
__declspec(section ".data") s32 btlparty_tou_tou_rank_1[12];
__declspec(section ".data") s32 btlgrp_tou_tou_rank_1[8];
s32 btlparty_tou_tou_add_1[48];
__declspec(section ".data") s32 btlgrp_tou_tou_add_1[8];
s32 btlparty_tou_tou_add_2[48];
__declspec(section ".data") s32 btlgrp_tou_tou_add_2[8];
__declspec(section ".data") s32 btlparty_tou_tou_boss[12];
__declspec(section ".data") s32 btlgrp_tou_tou_boss[8];
__declspec(section ".data") s32 btlparty_tou_tou_champ[12];
__declspec(section ".data") s32 btlgrp_tou_tou_champ[8];
__declspec(section ".data") s32 btlparty_tou_tou_koopa[12];
__declspec(section ".data") s32 btlgrp_tou_tou_koopa[8];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_02_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_03_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_04_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_05_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_06_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_07_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_08_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_09_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_10_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_11_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_12_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_13_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_14_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_15_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_16_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_17_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_18_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_19_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_20_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_21_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_22_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_23_off[6];
__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_24_off[6];
s32 btlsetup_tou_tbl[442];
s32 btl_tou_setup_no_tbl[52];
s32 bgset_tou_screen_evt[22];

__declspec(section ".data") u64 fd_battle_database_tou_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_tou_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_tou___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_tou___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_tou_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_tou___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_tou_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_tou_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_tou_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_tou___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_tou___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_tou_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_tou___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_tou_one_364[] = {
    1065353216,
};

s32 tou_btlobject_data[] = {
    (s32)"gamen", 131072, 0, 0, -1035468800, 3932160, (s32)"etc", 131072,
    0, 0, -1034420224, 171048960, (s32)"side__L", 131072, -1022820352, 0,
    -1038090240, 338165760, (s32)"side__R", 131072, 1124663296, 0, -1038090240, 505282560,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"gamen", 131072, 0, 0,
    -1035468800, 3932160, (s32)"etc", 131072, 0, 0, -1034420224, 171048960,
    (s32)"side__L", 131072, -1022820352, 0, -1038090240, 338165760, (s32)"side__R", 131072,
    1124663296, 0, -1038090240, 505282560, (s32)"B", 131074, 0, 0,
    0, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"if_wire", 327686, 0, 1124204544, 0, 0, (s32)"if_body", 327686,
    0, 1124204544, 0, 0,
};

s32 tou_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_03_0", 6, (s32)tou_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, (s32)bgset_tou_screen_evt, 65793, (s32)"bti_01", (s32)"stg_03_0", 8,
    (s32)(void*)((u8*)tou_btlobject_data + 0x90), 0, 0, 0, 0, 1677721602, 0, 0,
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
    (s32)bgset_tou_screen_evt, 65793,
};

s32 btlparty_tou_tou_rank_19[] = {
    (s32)unit_kurikuri, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_kurikuri, (s32)unit_kurikuri, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_kurikuri,
    (s32)unit_kurikuri, 16777216, 67108868, 1119092736, 0, 0, 0, 1,
    0, 0, 0, (s32)battle_item_kurikuri, (s32)unit_kurikuri, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_kurikuri,
    (s32)unit_kurikuri, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_kurikuri,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_19[] = {
    5, (s32)btlparty_tou_tou_rank_19, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_18[] = {
    (s32)unit_nokonoko_fighter, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_nokonoko_fighter, (s32)unit_nokonoko_fighter, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_nokonoko_fighter,
    (s32)unit_patapata_fighter, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_patapata_fighter,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_18[] = {
    3, (s32)btlparty_tou_tou_rank_18, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_17[] = {
    (s32)unit_sambo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo, (s32)unit_sambo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
    (s32)unit_sambo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_sambo,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_17[] = {
    3, (s32)btlparty_tou_tou_rank_17, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_16[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_honenoko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
    (s32)unit_honenoko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_bomhei,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_16[] = {
    3, (s32)btlparty_tou_tou_rank_16, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_15[] = {
    (s32)unit_togezo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kurokumorn, (s32)unit_togezo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
    (s32)unit_jyugem, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_15[] = {
    3, (s32)btlparty_tou_tou_rank_15, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_14[] = {
    (s32)unit_monochrome_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togezo, (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_togezo,
    (s32)unit_piders, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_togezo,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_14[] = {
    3, (s32)btlparty_tou_tou_rank_14, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_13[] = {
    (s32)unit_hyper_sinnosuke, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinnosuke, (s32)unit_hyper_sinnosuke, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinnosuke,
    (s32)unit_hyper_sinnosuke, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_hyper_sinnosuke,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_13[] = {
    3, (s32)btlparty_tou_tou_rank_13, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_12[] = {
    (s32)unit_bomhei, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_bomhei, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
    (s32)unit_bomhei, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_bomhei, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_12[] = {
    4, (s32)btlparty_tou_tou_rank_12, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_11[] = {
    (s32)unit_borodo, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_borodo, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_borodo,
    (s32)unit_borodo_king, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_borodo_king, (s32)unit_borodo_king, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_borodo_king,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_11[] = {
    4, (s32)btlparty_tou_tou_rank_11, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_10[] = {
    (s32)unit_iron_sinemon, 16777216, 67108868, 1117782016, 0, 0, 0, 50,
    0, 0, 0, (s32)battle_item_iron_sinemon, (s32)unit_iron_sinemon2, 16777216, 67108868, 1125515264,
    0, 1092616192, 0, 130, 0, 0, 0, (s32)battle_item_iron_sinemon2,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_10[] = {
    2, (s32)btlparty_tou_tou_rank_10, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_9[] = {
    (s32)unit_crimson_togemet, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_togemet, (s32)unit_crimson_togemet, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_togemet,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_9[] = {
    2, (s32)btlparty_tou_tou_rank_9, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_8[] = {
    (s32)unit_togedaruma, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)unit_togedaruma, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_8[] = {
    2, (s32)btlparty_tou_tou_rank_8, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_7[] = {
    (s32)unit_ura_noko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko, (s32)unit_ura_pata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
    (s32)unit_ura_noko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_ura_pata,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_7[] = {
    3, (s32)btlparty_tou_tou_rank_7, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_6[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_kamec, (s32)unit_green_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_kamec,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_kamec,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_6[] = {
    3, (s32)btlparty_tou_tou_rank_6, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_5[] = {
    (s32)unit_kamec_red, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hammer_bros, (s32)unit_kamec_white, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_fire_bros,
    (s32)unit_kamec_green, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_boomerang_bros,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_5[] = {
    3, (s32)btlparty_tou_tou_rank_5, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tou_tou_rank_4[] = {
    (s32)unit_dark_keeper, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_4[] = {
    1, (s32)btlparty_tou_tou_rank_4, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_3[] = {
    (s32)unit_hammer_bros, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_fire_bros, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
    (s32)unit_boomerang_bros, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_3[] = {
    3, (s32)btlparty_tou_tou_rank_3, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_rank_2[] = {
    (s32)unit_burst_wanwan, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan, (s32)unit_burst_wanwan, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_burst_wanwan,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_2[] = {
    2, (s32)btlparty_tou_tou_rank_2, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tou_tou_rank_1[] = {
    (s32)unit_togenoko_ace, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tou_tou_rank_1[] = {
    1, (s32)btlparty_tou_tou_rank_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_add_1[] = {
    (s32)unit_basabasa, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa,
    (s32)unit_basabasa, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa, (s32)unit_basabasa, 16777216, 67108868, 1125515264,
    1124204544, 1101004800, 0, 1, 0, 0, 0, (s32)battle_item_basabasa,
};

__declspec(section ".data") s32 btlgrp_tou_tou_add_1[] = {
    4, (s32)btlparty_tou_tou_add_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

s32 btlparty_tou_tou_add_2[] = {
    (s32)unit_hinnya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monban, (s32)unit_hannya, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monban,
    (s32)unit_hinnya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monban, (s32)unit_hannya, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tou_tou_add_2[] = {
    4, (s32)btlparty_tou_tou_add_2, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tou_tou_boss[] = {
    (s32)unit_boss_macho_gance, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_macho_gance,
};

__declspec(section ".data") s32 btlgrp_tou_tou_boss[] = {
    1, (s32)btlparty_tou_tou_boss, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tou_tou_champ[] = {
    (s32)unit_boss_champion, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_champion,
};

__declspec(section ".data") s32 btlgrp_tou_tou_champ[] = {
    1, (s32)btlparty_tou_tou_champ, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_tou_tou_koopa[] = {
    (s32)unit_boss_koopa_tou, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_tou_tou_koopa[] = {
    1, (s32)btlparty_tou_tou_koopa, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_heart_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_test1_off[] = {
    50, (s32)btlgrp_tou_tou_rank_19, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_01_off[] = {
    50, (s32)btlgrp_tou_tou_rank_19, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_02_off[] = {
    50, (s32)btlgrp_tou_tou_rank_18, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_03_off[] = {
    50, (s32)btlgrp_tou_tou_rank_17, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_04_off[] = {
    50, (s32)btlgrp_tou_tou_rank_16, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_05_off[] = {
    50, (s32)btlgrp_tou_tou_rank_15, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_06_off[] = {
    50, (s32)btlgrp_tou_tou_rank_14, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_07_off[] = {
    50, (s32)btlgrp_tou_tou_rank_13, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_08_off[] = {
    50, (s32)btlgrp_tou_tou_rank_12, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_09_off[] = {
    50, (s32)btlgrp_tou_tou_rank_11, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_10_off[] = {
    50, (s32)btlgrp_tou_tou_rank_10, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_11_off[] = {
    50, (s32)btlgrp_tou_tou_rank_9, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_12_off[] = {
    50, (s32)btlgrp_tou_tou_rank_8, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_13_off[] = {
    50, (s32)btlgrp_tou_tou_rank_7, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_14_off[] = {
    50, (s32)btlgrp_tou_tou_rank_6, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_15_off[] = {
    50, (s32)btlgrp_tou_tou_rank_5, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_16_off[] = {
    50, (s32)btlgrp_tou_tou_rank_4, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_17_off[] = {
    50, (s32)btlgrp_tou_tou_rank_3, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_18_off[] = {
    50, (s32)btlgrp_tou_tou_rank_2, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_19_off[] = {
    50, (s32)btlgrp_tou_tou_rank_1, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_20_off[] = {
    50, (s32)btlgrp_tou_tou_add_1, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_21_off[] = {
    50, (s32)btlgrp_tou_tou_add_2, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_22_off[] = {
    50, (s32)btlgrp_tou_tou_champ, (s32)(void*)((u8*)tou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_23_off[] = {
    50, (s32)btlgrp_tou_tou_boss, (s32)tou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_tou_btlno_tou_01_24_off[] = {
    50, (s32)btlgrp_tou_tou_koopa, (s32)tou_btlstage_data, 0, 0, 0,
};

s32 btlsetup_tou_tbl[] = {
    (s32)/*"マップstg_03_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x33\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"クリクリブラザーズ"*/"\x83\x4E\x83\x8A\x83\x4E\x83\x8A\x83\x75\x83\x89\x83\x55\x81\x5B\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_01_off, 64,
    0, 67372036, 0, 67372036, 1028, 67371008, 168428548, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"コウラーズ"*/"\x83\x52\x83\x45\x83\x89\x81\x5B\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_02_off,
    64, 0, 67372036, 0, 67372036, 1028, 168427520, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"サンボ三兄弟"*/"\x83\x54\x83\x93\x83\x7B\x8E\x4F\x8C\x5A\x92\xED", (s32)"tou_03", 0, -1, 0,
    (s32)btlgrpsel_tou_btlno_tou_01_03_off, 64, 0, 67372036, 0, 67372036, 1028, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ボンバーズ"*/"\x83\x7B\x83\x93\x83\x6F\x81\x5B\x83\x59", (s32)"tou_03", 0, -1,
    0, (s32)btlgrpsel_tou_btlno_tou_01_04_off, 64, 0, 67372036, 0, 67372036, 1028,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"クモーンズ"*/"\x83\x4E\x83\x82\x81\x5B\x83\x93\x83\x59", (s32)"tou_03", 0,
    -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_05_off, 64, 0, 67372036, 0, 67372036,
    1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ジュゲムとイタい仲間たち"*/"\x83\x57\x83\x85\x83\x51\x83\x80\x82\xC6\x83\x43\x83\x5E\x82\xA2\x92\x87\x8A\xD4\x82\xBD\x82\xBF", (s32)"tou_03",
    0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_06_off, 64, 0, 67372036, 0,
    67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ハイパーズ"*/"\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x59",
    (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_07_off, 64, 0, 67372036,
    0, 67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"ボロドーズ"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_08_off, 64, 0,
    67372036, 0, 67372036, 1028, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"クッパぐんだんズ"*/"\x83\x4E\x83\x62\x83\x70\x82\xAE\x82\xF1\x82\xBE\x82\xF1\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_09_off, 64,
    0, 67372036, 0, 67372036, 1028, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"こうてつウォリアーズ"*/"\x82\xB1\x82\xA4\x82\xC4\x82\xC2\x83\x45\x83\x48\x83\x8A\x83\x41\x81\x5B\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_10_off,
    536870976, 0, 67372036, 0, 67372036, 1028, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1", (s32)/*"ザ・トゲトゲン"*/"\x83\x55\x81\x45\x83\x67\x83\x51\x83\x67\x83\x51\x83\x93", (s32)"tou_03", 0, -1, 0,
    (s32)btlgrpsel_tou_btlno_tou_01_11_off, 64, 0, 67372036, 0, 67372036, 1028, 67371008,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミトゲダルマー"*/"\x83\x84\x83\x7E\x83\x67\x83\x51\x83\x5F\x83\x8B\x83\x7D\x81\x5B", (s32)"tou_03", 0, -1,
    0, (s32)btlgrpsel_tou_btlno_tou_01_12_off, 64, 0, 67372036, 0, 67372036, 1028,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ザ・ウラウラン"*/"\x83\x55\x81\x45\x83\x45\x83\x89\x83\x45\x83\x89\x83\x93", (s32)"tou_03", 0,
    -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_13_off, 64, 0, 67372036, 0, 67372036,
    1028, 168427520, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"レッドデビルズ"*/"\x83\x8C\x83\x62\x83\x68\x83\x66\x83\x72\x83\x8B\x83\x59", (s32)"tou_03",
    0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_14_off, 64, 0, 67372036, 0,
    67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"トリプルブロス"*/"\x83\x67\x83\x8A\x83\x76\x83\x8B\x83\x75\x83\x8D\x83\x58",
    (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_15_off, 64, 0, 67372036,
    2570, 67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"ザ・マホーンズ"*/"\x83\x55\x81\x45\x83\x7D\x83\x7A\x81\x5B\x83\x93\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_16_off, 64, 0,
    67372036, 0, 67372036, 1028, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"キラーボムヘイズ"*/"\x83\x4C\x83\x89\x81\x5B\x83\x7B\x83\x80\x83\x77\x83\x43\x83\x59", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_17_off, 64,
    0, 67372036, 0, 67372036, 1028, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バーストワンワン"*/"\x83\x6F\x81\x5B\x83\x58\x83\x67\x83\x8F\x83\x93\x83\x8F\x83\x93", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_18_off,
    64, 0, 67372036, 0, 67372036, 1028, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"トゲノコエース"*/"\x83\x67\x83\x51\x83\x6D\x83\x52\x83\x47\x81\x5B\x83\x58", (s32)"tou_03", 0, -1, 0,
    (s32)btlgrpsel_tou_btlno_tou_01_19_off, 64, 0, 67372036, 0, 67372036, 1028, 168427520,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ナイトウィングス"*/"\x83\x69\x83\x43\x83\x67\x83\x45\x83\x42\x83\x93\x83\x4F\x83\x58", (s32)"tou_03", 0, -1,
    0, (s32)btlgrpsel_tou_btlno_tou_01_20_off, 64, 0, 67372036, 0, 67372036, 1028,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"スネイルズ"*/"\x83\x58\x83\x6C\x83\x43\x83\x8B\x83\x59", (s32)"tou_03", 0,
    -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_21_off, 64, 0, 67372036, 0, 67372036,
    1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ブレッドハート"*/"\x83\x75\x83\x8C\x83\x62\x83\x68\x83\x6E\x81\x5B\x83\x67", (s32)"tou_03",
    0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_22_off, 536870976, 0, 67372036, 0,
    67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_BOSS_STG3_CHAMP1", (s32)/*"マッチョガンス"*/"\x83\x7D\x83\x62\x83\x60\x83\x87\x83\x4B\x83\x93\x83\x58",
    (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_23_off, 536870928, 6, 67372036,
    0, 67372036, 1028, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_BOSS_STG3_GANCE1",
#ifdef VERSION_G8ME01
    (s32)/*"乱入クッパ"*/"\x97\x90\x93\xFC\x83\x4E\x83\x62\x83\x70", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_24_off, 536870976, 0,
#else
    (s32)/*"乱入クッパ"*/"\x97\x90\x93\xFC\x83\x4E\x83\x62\x83\x70", (s32)"tou_03", 0, -1, 0, (s32)btlgrpsel_tou_btlno_tou_01_24_off, 536870912, 0,
#endif
    0, 0, 67372036, 0, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_BOSS_STG8_KOOPA", 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s32 btl_tou_setup_no_tbl[] = {
    (s32)"BTLNO_TOU_TEST1", 0, (s32)"BTLNO_TOU_01_01", 1, (s32)"BTLNO_TOU_01_02", 2, (s32)"BTLNO_TOU_01_03", 3,
    (s32)"BTLNO_TOU_01_04", 4, (s32)"BTLNO_TOU_01_05", 5, (s32)"BTLNO_TOU_01_06", 6, (s32)"BTLNO_TOU_01_07", 7,
    (s32)"BTLNO_TOU_01_08", 8, (s32)"BTLNO_TOU_01_09", 9, (s32)"BTLNO_TOU_01_10", 10, (s32)"BTLNO_TOU_01_11", 11,
    (s32)"BTLNO_TOU_01_12", 12, (s32)"BTLNO_TOU_01_13", 13, (s32)"BTLNO_TOU_01_14", 14, (s32)"BTLNO_TOU_01_15", 15,
    (s32)"BTLNO_TOU_01_16", 16, (s32)"BTLNO_TOU_01_17", 17, (s32)"BTLNO_TOU_01_18", 18, (s32)"BTLNO_TOU_01_19", 19,
    (s32)"BTLNO_TOU_01_20", 20, (s32)"BTLNO_TOU_01_21", 21, (s32)"BTLNO_TOU_01_22", 22, (s32)"BTLNO_TOU_01_23", 23,
    (s32)"BTLNO_TOU_01_24", 24, 0, 0,
};

EVT_BEGIN(bgset_tou_screen_evt)
    CALL(tou_gamen_screen_tev_init)
    WAIT_FRAMES(1)
    CALL(evt_map_set_tevcallback, 8, PTR(tou_gamen_screen_tev))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("gamen"), 134217728)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("gamen"), 256)
    RETURN
EVT_END()

