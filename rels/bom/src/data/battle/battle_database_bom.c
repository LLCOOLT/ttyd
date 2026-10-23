#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "bom.h"

#pragma force_active on

USER_FUNC(_snow_control);

__declspec(section ".data") u64 fd_battle_database_bom_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_bom_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_bom___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_bom___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_bom_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_bom___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_bom_one_381[1];
__declspec(section ".data") u64 fd_battle_database_bom_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_bom_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_bom___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_bom___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_bom_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_bom___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_bom_one_364[1];
s32 bom_btlobject_data[66];
s32 bom_btlstage_data[109];
__declspec(section ".data") s32 btlparty_bom_bom_00_01_off_1[12];
__declspec(section ".data") s32 btlgrp_bom_bom_00_01_off_1[8];
s32 btlparty_bom_bom_03_01_off_1[24];
__declspec(section ".data") s32 btlgrp_bom_bom_03_01_off_1[8];
s32 btlparty_bom_bom_03_01_off_2[36];
__declspec(section ".data") s32 btlgrp_bom_bom_03_01_off_2[8];
s32 btlparty_bom_bom_03_03_off_1[24];
__declspec(section ".data") s32 btlgrp_bom_bom_03_03_off_1[8];
s32 btlparty_bom_bom_03_03_off_2[36];
__declspec(section ".data") s32 btlgrp_bom_bom_03_03_off_2[8];
s32 btlparty_bom_bom_04_01_off_1[24];
__declspec(section ".data") s32 btlgrp_bom_bom_04_01_off_1[8];
s32 btlparty_bom_bom_04_01_off_2[36];
__declspec(section ".data") s32 btlgrp_bom_bom_04_01_off_2[8];
s32 btlparty_bom_bom_04_02_off_1[24];
__declspec(section ".data") s32 btlgrp_bom_bom_04_02_off_1[8];
s32 btlparty_bom_bom_04_02_off_2[36];
__declspec(section ".data") s32 btlgrp_bom_bom_04_02_off_2[8];
s32 btlparty_bom_bom_04_03_off_1[48];
__declspec(section ".data") s32 btlgrp_bom_bom_04_03_off_1[8];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_01_off[9];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_02_off[9];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_03_off[9];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_01_off[9];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_02_off[9];
__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_03_off[6];
s32 btlsetup_bom_tbl[136];
s32 btl_bom_setup_no_tbl[16];
__declspec(section ".data") s32 bgset_bom_snow_event[4];

__declspec(section ".data") u64 fd_battle_database_bom_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_bom_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_bom___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_bom___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_bom_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_bom___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_bom_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_bom_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_bom_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_bom___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_bom___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_bom_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_bom___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_bom_one_364[] = {
    1065353216,
};

s32 bom_btlobject_data[] = {
    (s32)"yuki_front", 131073, 0, 0, 1117257728, 3932160, (s32)"yuki_back", 131073,
    0, 0, -1038090240, 171048960, (s32)"kusa_01", 131073, -1020854272, 0,
    -1045954560, 338165760, (s32)"kusa_02", 131073, 1126301696, 0, -1053818880, 505282560,
    (s32)"kabe_01", 131073, 1128398848, 0, 1115947008, 3932160, (s32)"kabe_02", 131073,
    1121845248, 0, -1043857408, 171048960, (s32)"kabe_03", 131072, -1030881280, 0,
    -1032847360, 3932160, (s32)"ki_01", 131072, 1127809024, 0, -1034158080, 171048960,
    (s32)"ki_02", 131072, 1117257728, 0, -1035468800, 338165760, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160,
};

s32 bom_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_07_0", 11, (s32)bom_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, (s32)bgset_bom_snow_event, 65793,
};

__declspec(section ".data") s32 btlparty_bom_bom_00_01_off_1[] = {
    (s32)unit_kuriboo, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_bom_bom_00_01_off_1[] = {
    1, (s32)btlparty_bom_bom_00_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_bom_bom_03_01_off_1[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_bllizard, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_bom_bom_03_01_off_1[] = {
    2, (s32)btlparty_bom_bom_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_bom_bom_03_01_off_2[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_bllizard, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_bom_bom_03_01_off_2[] = {
    3, (s32)btlparty_bom_bom_03_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_bom_bom_03_03_off_1[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_bom_bom_03_03_off_1[] = {
    2, (s32)btlparty_bom_bom_03_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_bom_bom_03_03_off_2[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_ice_pakkun, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_bom_bom_03_03_off_2[] = {
    3, (s32)btlparty_bom_bom_03_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_bom_bom_04_01_off_1[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_bllizard, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_bom_bom_04_01_off_1[] = {
    2, (s32)btlparty_bom_bom_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_bom_bom_04_01_off_2[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_bom_bom_04_01_off_2[] = {
    3, (s32)btlparty_bom_bom_04_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_bom_bom_04_02_off_1[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_ice_pakkun, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_bom_bom_04_02_off_1[] = {
    2, (s32)btlparty_bom_bom_04_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_bom_bom_04_02_off_2[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_ice_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_bom_bom_04_02_off_2[] = {
    3, (s32)btlparty_bom_bom_04_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_bom_bom_04_03_off_1[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_ice_pakkun, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_bom_bom_04_03_off_1[] = {
    4, (s32)btlparty_bom_bom_04_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_test1_off[] = {
    50, (s32)btlgrp_bom_bom_00_01_off_1, (s32)bom_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_01_off[] = {
    20, (s32)btlgrp_bom_bom_03_01_off_1, (s32)bom_btlstage_data, 10, (s32)btlgrp_bom_bom_03_01_off_2, (s32)bom_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_02_off[] = {
    10, (s32)btlgrp_bom_bom_03_01_off_1, (s32)bom_btlstage_data, 20, (s32)btlgrp_bom_bom_03_01_off_2, (s32)bom_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_03_03_off[] = {
    10, (s32)btlgrp_bom_bom_03_03_off_1, (s32)bom_btlstage_data, 10, (s32)btlgrp_bom_bom_03_03_off_2, (s32)bom_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_01_off[] = {
    10, (s32)btlgrp_bom_bom_04_01_off_1, (s32)bom_btlstage_data, 10, (s32)btlgrp_bom_bom_04_01_off_2, (s32)bom_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_02_off[] = {
    10, (s32)btlgrp_bom_bom_04_02_off_1, (s32)bom_btlstage_data, 10, (s32)btlgrp_bom_bom_04_02_off_2, (s32)bom_btlstage_data, 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_bom_btlno_bom_04_03_off[] = {
    10, (s32)btlgrp_bom_bom_04_03_off_1, (s32)bom_btlstage_data, 0, 0, 0,
};

s32 btlsetup_bom_tbl[] = {
    (s32)/*"マップstg_07_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x37\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_bom_btlno_bom_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom03ブリザード"*/"\x62\x6F\x6D\x30\x33\x83\x75\x83\x8A\x83\x55\x81\x5B\x83\x68", 0, 0, -1, 0, (s32)btlgrpsel_bom_btlno_bom_03_01_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom03ブリザード"*/"\x62\x6F\x6D\x30\x33\x83\x75\x83\x8A\x83\x55\x81\x5B\x83\x68", 0, 0, -1, 0, (s32)btlgrpsel_bom_btlno_bom_03_02_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom03アイスパックン"*/"\x62\x6F\x6D\x30\x33\x83\x41\x83\x43\x83\x58\x83\x70\x83\x62\x83\x4E\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_bom_btlno_bom_03_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50530826, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom04アイスパックン"*/"\x62\x6F\x6D\x30\x34\x83\x41\x83\x43\x83\x58\x83\x70\x83\x62\x83\x4E\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_bom_btlno_bom_04_01_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50530826, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom04ブリザード"*/"\x62\x6F\x6D\x30\x34\x83\x75\x83\x8A\x83\x55\x81\x5B\x83\x68", 0, 0,
    -1, 0, (s32)btlgrpsel_bom_btlno_bom_04_02_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"bom04アイスパックン"*/"\x62\x6F\x6D\x30\x34\x83\x41\x83\x43\x83\x58\x83\x70\x83\x62\x83\x4E\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_bom_btlno_bom_04_03_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50530826, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

s32 btl_bom_setup_no_tbl[] = {
    (s32)"BTLNO_BOM_TEST1", 0, (s32)"BTLNO_BOM_03_01", 1, (s32)"BTLNO_BOM_03_02", 2, (s32)"BTLNO_BOM_03_03", 3,
    (s32)"BTLNO_BOM_04_01", 4, (s32)"BTLNO_BOM_04_02", 5, (s32)"BTLNO_BOM_04_03", 6, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(bgset_bom_snow_event)
    CALL(_snow_control)
    RETURN
EVT_END()

struct EffEntry* effSnowfallN64Entry(s32 type, s32 count);

USER_FUNC(_snow_control) {
    if (isFirstCall) {
        effSnowfallN64Entry(0, 64);
    }
    return EVT_RETURN_BLOCK;
}
