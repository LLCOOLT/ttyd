#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle_stage_object.h"
#include "system.h"

static USER_FUNC(_wave_offset);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_item_bubble[];
extern s32 battle_item_heavy_bom[];
extern s32 battle_item_hermos[];
extern s32 battle_item_killer[];
extern s32 battle_item_killer_cannon[];
extern s32 battle_item_patamet[];
extern s32 unit_bubble_6_data_11C80[];
extern s32 unit_heavy_bom_6_data_15A08[];
extern s32 unit_hermos_6_data_17118[];
extern s32 unit_killer[];
extern s32 unit_killer_cannon[];
extern s32 unit_kuriboo_6_data_110E8[];
extern s32 unit_patamet_6_data_19100[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_dou_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_dou_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_dou___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_dou___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_dou_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_dou___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_dou_one_381[1];
__declspec(section ".data") u64 fd_battle_database_dou_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_dou_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_dou___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_dou___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_dou_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_dou___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_dou_one_364[1];
s32 dou_btlobject_data[306];
s32 dou_btlstage_data[654];
s32 btlparty_dou_dou_00_01_off_1[36];
__declspec(section ".data") s32 btlgrp_dou_dou_00_01_off_1[8];
s32 btlparty_dou_dou_01_01_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_01_01_off_01[8];
s32 btlparty_dou_dou_02_01_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_02_01_off_01[8];
s32 btlparty_dou_dou_02_02_off_01[48];
__declspec(section ".data") s32 btlgrp_dou_dou_02_02_off_01[8];
s32 btlparty_dou_dou_03_01_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_03_01_off_01[8];
s32 btlparty_dou_dou_03_99_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_03_99_off_01[8];
s32 btlparty_dou_dou_03_02_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_03_02_off_01[8];
s32 btlparty_dou_dou_03_03_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_03_03_off_01[8];
s32 btlparty_dou_dou_05_01_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_05_01_off_01[8];
s32 btlparty_dou_dou_05_02_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_05_02_off_01[8];
s32 btlparty_dou_dou_06_01_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_06_01_off_01[8];
s32 btlparty_dou_dou_06_02_off_01[48];
__declspec(section ".data") s32 btlgrp_dou_dou_06_02_off_01[8];
__declspec(section ".data") s32 btlparty_dou_dou_06_03_off_01[12];
__declspec(section ".data") s32 btlgrp_dou_dou_06_03_off_01[8];
s32 btlparty_dou_dou_07_01_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_07_01_off_01[8];
s32 btlparty_dou_dou_08_01_off_01[48];
__declspec(section ".data") s32 btlgrp_dou_dou_08_01_off_01[8];
s32 btlparty_dou_dou_09_01_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_09_01_off_01[8];
s32 btlparty_dou_dou_09_02_off_01[36];
__declspec(section ".data") s32 btlgrp_dou_dou_09_02_off_01[8];
s32 btlparty_dou_dou_12_01_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_12_01_off_01[8];
s32 btlparty_dou_dou_12_99_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_12_99_off_01[8];
s32 btlparty_dou_dou_13_01_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_13_01_off_01[8];
s32 btlparty_dou_dou_13_99_off_01[24];
__declspec(section ".data") s32 btlgrp_dou_dou_13_99_off_01[8];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_01_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_02_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_99_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_03_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_05_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_05_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_03_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_07_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_08_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_09_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_09_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_99_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_01_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_02_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_03_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_04_off[6];
__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_99_off[6];
s32 btlsetup_dou_tbl[476];
s32 btl_dou_setup_no_tbl[56];
s32 bgset_dou_wave_event[77];

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

    obj->field_0x10.x = ampX * sinfd(stepX * 360 / periodX);
    obj->field_0x10.y = ampY * sinfd(stepY * 360 / periodY + 270) + ampY;
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

__declspec(section ".data") u64 fd_battle_database_dou_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_dou_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_dou___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_dou___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_dou_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_dou___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_dou_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_dou_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_dou_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_dou___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_dou___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_dou_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_dou___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_dou_one_364[] = {
    1065353216,
};

s32 dou_btlobject_data[] = {
    (s32)"taki", 131074, 0, 0, 0, 3932160, (s32)"B_kabe", 131074,
    0, 0, 0, 171048960, (s32)"zabu_1", 131074, 0, 0,
    0, 338165760, (s32)"zabu_2", 131074, 0, 0, 0, 505282560,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"B_kabe", 131074,
    0, 0, 0, 171048960, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"takara_01", 131073, 1121845248, 0, -1031143424, 3932160,
    (s32)"takara_02", 131073, -1028784128, 0, -1030750208, 171048960, (s32)"takara_03", 131073,
    1124597760, 0, 1113849856, 338165760, (s32)"takara_04", 131073, -1019871232, 0,
    1113849856, 505282560, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C_kabe", 131075, 0, 0, 0, 3932160, (s32)"nami_00", 131075,
    0, 0, 0, 3932160, (s32)"nami_01", 131075, 0, 0,
    0, 3932160, (s32)"fune_L", 131072, -1026555904, 0, -1031798784, 3932160,
    (s32)"fune_R", 131072, 1123024896, 0, -1031798784, 171048960, (s32)"A1_kabe", 131072,
    0, 0, -1035206656, 338165760, (s32)"iwa_01", 131073, 1130889216, 0,
    -1045954560, 3932160, (s32)"iwa_02", 131073, -1016463360, 0, -1045954560, 171048960,
    (s32)"iwa_03", 131073, 0, 0, -1038614528, 338165760, (s32)"B_kabe", 131074,
    0, 0, 0, 3932160, (s32)"nami_02", 131074, 0, 0,
    0, 171048960, (s32)"nami_03", 131074, 0, 0, 0, 338165760,
    (s32)"nami_04", 131074, 0, 0, 0, 505282560, (s32)"C_kabe", 131075,
    0, 0, 0, 3932160, (s32)"nami_00", 131075, 0, 0,
    0, 3932160, (s32)"nami_01", 131075, 0, 0, 0, 3932160,
    (s32)"fune_R", 131072, 1123024896, 0, -1031798784, 171048960, (s32)"A1_kabe", 131072,
    0, 0, -1035206656, 338165760, (s32)"iwa_01", 131073, 1130889216, 0,
    -1045954560, 3932160, (s32)"iwa_02", 131073, -1016463360, 0, -1045954560, 171048960,
    (s32)"iwa_03", 131073, 0, 0, -1038614528, 338165760, (s32)"B_kabe", 131074,
    0, 0, 0, 3932160, (s32)"nami_02", 131074, 0, 0,
    0, 171048960, (s32)"nami_03", 131074, 0, 0, 0, 338165760,
    (s32)"nami_04", 131074, 0, 0, 0, 505282560, (s32)"C_kabe", 131075,
    0, 0, 0, 3932160, (s32)"nami_00", 131075, 0, 0,
    0, 3932160, (s32)"nami_01", 131075, 0, 0, 0, 3932160,
    (s32)"A1_kabe", 131072, 0, 0, -1035206656, 338165760, (s32)"iwa_01", 131073,
    1128267776, 0, 1115160576, 3932160, (s32)"iwa_02", 131073, -1020461056, 0,
    1112801280, 171048960, (s32)"iwa_03", 131073, 0, 0, -1038614528, 338165760,
    (s32)"B_kabe", 131074, 0, 0, 0, 3932160, (s32)"nami_02", 131074,
    0, 0, 0, 171048960, (s32)"nami_03", 131074, 0, 0,
    0, 338165760, (s32)"nami_04", 131074, 0, 0, 0, 505282560,
    (s32)"C_kabe", 131075, 0, 0, 0, 3932160, (s32)"nami_00", 131075,
    0, 0, 0, 3932160, (s32)"nami_01", 131075, 0, 0,
    0, 3932160,
};

s32 dou_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_05_4", 5, (s32)dou_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 65793, (s32)"bti_01", (s32)"stg_05_4", 2,
    (s32)(void*)((u8*)dou_btlobject_data + 0x78), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 65793, (s32)"bti_01", (s32)"stg_05_5", 8, (s32)(void*)((u8*)dou_btlobject_data + 0xA8), 0, 0,
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
    (s32)"stg_05_3", 13, (s32)(void*)((u8*)dou_btlobject_data + 0x168), 0, 0, 0, 0, 1677721602,
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
    0, (s32)bgset_dou_wave_event, 0, 65793, (s32)"bti_01", (s32)"stg_05_3", 12, (s32)(void*)((u8*)dou_btlobject_data + 0x2A0),
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
    0, 0, 0, 0, 0, 0, (s32)bgset_dou_wave_event, 0,
    65793, (s32)"bti_01", (s32)"stg_05_3", 11, (s32)(void*)((u8*)dou_btlobject_data + 0x3C0), 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603104, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 34603104, 536870912,
    1704706, 0, 0, 2047, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 100, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)bgset_dou_wave_event, 0, 65793,
};

s32 btlparty_dou_dou_00_01_off_1[] = {
    (s32)unit_kuriboo_6_data_110E8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, 0, (s32)unit_kuriboo_6_data_110E8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, 0,
    (s32)unit_kuriboo_6_data_110E8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrp_dou_dou_00_01_off_1[] = {
    3, (s32)btlparty_dou_dou_00_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_01_01_off_01[] = {
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hermos, (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hermos,
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hermos,
};

__declspec(section ".data") s32 btlgrp_dou_dou_01_01_off_01[] = {
    3, (s32)btlparty_dou_dou_01_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_02_01_off_01[] = {
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
};

__declspec(section ".data") s32 btlgrp_dou_dou_02_01_off_01[] = {
    2, (s32)btlparty_dou_dou_02_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_02_02_off_01[] = {
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
};

__declspec(section ".data") s32 btlgrp_dou_dou_02_02_off_01[] = {
    4, (s32)btlparty_dou_dou_02_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_03_01_off_01[] = {
    (s32)unit_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer_cannon, (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_03_01_off_01[] = {
    2, (s32)btlparty_dou_dou_03_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_03_99_off_01[] = {
    (s32)unit_killer, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer, (s32)unit_killer, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_killer,
};

__declspec(section ".data") s32 btlgrp_dou_dou_03_99_off_01[] = {
    2, (s32)btlparty_dou_dou_03_99_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_03_02_off_01[] = {
    (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_03_02_off_01[] = {
    2, (s32)btlparty_dou_dou_03_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_03_03_off_01[] = {
    (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
    (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_03_03_off_01[] = {
    3, (s32)btlparty_dou_dou_03_03_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_05_01_off_01[] = {
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hermos, (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hermos,
};

__declspec(section ".data") s32 btlgrp_dou_dou_05_01_off_01[] = {
    2, (s32)btlparty_dou_dou_05_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_05_02_off_01[] = {
    (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_dou_dou_05_02_off_01[] = {
    2, (s32)btlparty_dou_dou_05_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_06_01_off_01[] = {
    (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
    (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_dou_dou_06_01_off_01[] = {
    3, (s32)btlparty_dou_dou_06_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_06_02_off_01[] = {
    (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, 0, (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_dou_dou_06_02_off_01[] = {
    4, (s32)btlparty_dou_dou_06_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_dou_dou_06_03_off_01[] = {
    (s32)unit_patamet_6_data_19100, 16777216, 67108868, 1119092736, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_dou_dou_06_03_off_01[] = {
    1, (s32)btlparty_dou_dou_06_03_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_07_01_off_01[] = {
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hermos, (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hermos,
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hermos,
};

__declspec(section ".data") s32 btlgrp_dou_dou_07_01_off_01[] = {
    3, (s32)btlparty_dou_dou_07_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_08_01_off_01[] = {
    (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
    (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom_6_data_15A08, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_08_01_off_01[] = {
    4, (s32)btlparty_dou_dou_08_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_09_01_off_01[] = {
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hermos,
};

__declspec(section ".data") s32 btlgrp_dou_dou_09_01_off_01[] = {
    3, (s32)btlparty_dou_dou_09_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_09_02_off_01[] = {
    (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hermos, (s32)unit_hermos_6_data_17118, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hermos,
    (s32)unit_bubble_6_data_11C80, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bubble,
};

__declspec(section ".data") s32 btlgrp_dou_dou_09_02_off_01[] = {
    3, (s32)btlparty_dou_dou_09_02_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_dou_dou_12_01_off_01[] = {
    (s32)unit_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer_cannon, (s32)unit_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_12_01_off_01[] = {
    2, (s32)btlparty_dou_dou_12_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_12_99_off_01[] = {
    (s32)unit_killer, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer, (s32)unit_killer, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_killer,
};

__declspec(section ".data") s32 btlgrp_dou_dou_12_99_off_01[] = {
    2, (s32)btlparty_dou_dou_12_99_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_13_01_off_01[] = {
    (s32)unit_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer_cannon, (s32)unit_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_dou_dou_13_01_off_01[] = {
    2, (s32)btlparty_dou_dou_13_01_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_dou_dou_13_99_off_01[] = {
    (s32)unit_killer, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_killer, (s32)unit_killer, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_killer,
};

__declspec(section ".data") s32 btlgrp_dou_dou_13_99_off_01[] = {
    2, (s32)btlparty_dou_dou_13_99_off_01, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test1_off[] = {
    50, (s32)btlgrp_dou_dou_00_01_off_1, (s32)(void*)((u8*)dou_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test2_off[] = {
    50, (s32)btlgrp_dou_dou_00_01_off_1, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_test3_off[] = {
    50, (s32)btlgrp_dou_dou_00_01_off_1, (s32)(void*)((u8*)dou_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_01_01_off[] = {
    20, (s32)btlgrp_dou_dou_01_01_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_02_01_off[] = {
    20, (s32)btlgrp_dou_dou_02_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_02_02_off[] = {
    20, (s32)btlgrp_dou_dou_02_02_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_01_off[] = {
    20, (s32)btlgrp_dou_dou_03_01_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_99_off[] = {
    20, (s32)btlgrp_dou_dou_03_99_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_02_off[] = {
    20, (s32)btlgrp_dou_dou_03_02_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_03_03_off[] = {
    20, (s32)btlgrp_dou_dou_03_03_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_05_01_off[] = {
    20, (s32)btlgrp_dou_dou_05_01_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_05_02_off[] = {
    20, (s32)btlgrp_dou_dou_05_02_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_01_off[] = {
    20, (s32)btlgrp_dou_dou_06_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_02_off[] = {
    20, (s32)btlgrp_dou_dou_06_02_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_06_03_off[] = {
    20, (s32)btlgrp_dou_dou_06_03_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_07_01_off[] = {
    20, (s32)btlgrp_dou_dou_07_01_off_01, (s32)dou_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_08_01_off[] = {
    20, (s32)btlgrp_dou_dou_08_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_09_01_off[] = {
    20, (s32)btlgrp_dou_dou_09_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_09_02_off[] = {
    20, (s32)btlgrp_dou_dou_09_02_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x6D0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_01_off[] = {
    20, (s32)btlgrp_dou_dou_12_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_02_off[] = {
    20, (s32)btlgrp_dou_dou_12_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_12_99_off[] = {
    20, (s32)btlgrp_dou_dou_12_99_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_01_off[] = {
    20, (s32)btlgrp_dou_dou_13_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_02_off[] = {
    20, (s32)btlgrp_dou_dou_13_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_03_off[] = {
    20, (s32)btlgrp_dou_dou_13_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_04_off[] = {
    20, (s32)btlgrp_dou_dou_13_01_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_dou_btlno_dou_13_99_off[] = {
    20, (s32)btlgrp_dou_dou_13_99_off_01, (s32)(void*)((u8*)dou_btlstage_data + 0x1B4), 0, 0, 0,
};

s32 btlsetup_dou_tbl[] = {
    (s32)/*"マップstg_05_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_test1_off, 0, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_05_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x34", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_test2_off, 0,
    0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_05_5"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x35\x5F\x35", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_test3_off,
    0, 0, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU01エルモス"*/"\x44\x4F\x55\x30\x31\x83\x47\x83\x8B\x83\x82\x83\x58", 0, 0, -1, 0,
    (s32)btlgrpsel_dou_btlno_dou_01_01_off, 0, 0, 50529027, 50528256, 50529027, 50529027, 50528256,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU02バブル"*/"\x44\x4F\x55\x30\x32\x83\x6F\x83\x75\x83\x8B", 0, 0, -1,
    0, (s32)btlgrpsel_dou_btlno_dou_02_01_off, 0, 0, 50529027, 50528256, 50529027, 50529027,
    50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU02バブル"*/"\x44\x4F\x55\x30\x32\x83\x6F\x83\x75\x83\x8B", 0, 0,
    -1, 0, (s32)btlgrpsel_dou_btlno_dou_02_02_off, 0, 0, 50529027, 50528256, 50529027,
    50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU03キラー大砲"*/"\x44\x4F\x55\x30\x33\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0,
    0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_03_01_off, 0, 0, 50529027, 50528256,
    50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU03キラー"*/"\x44\x4F\x55\x30\x33\x83\x4C\x83\x89\x81\x5B",
    0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_03_99_off, 0, 0, 50529027,
    50528256, 50529027, 50529027, 50528256, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"DOU03ヘビーボム"*/"\x44\x4F\x55\x30\x33\x83\x77\x83\x72\x81\x5B\x83\x7B\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_03_02_off, 0, 0,
    50529027, 50528256, 50529027, 50529027, 50530826, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU03ヘビーボム"*/"\x44\x4F\x55\x30\x33\x83\x77\x83\x72\x81\x5B\x83\x7B\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_03_03_off, 0,
    0, 50529027, 50528256, 50529027, 50529027, 50530826, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU05エルモス"*/"\x44\x4F\x55\x30\x35\x83\x47\x83\x8B\x83\x82\x83\x58", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_05_01_off,
    0, 0, 50529027, 50528256, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU05パタメット"*/"\x44\x4F\x55\x30\x35\x83\x70\x83\x5E\x83\x81\x83\x62\x83\x67", 0, 0, -1, 0,
    (s32)btlgrpsel_dou_btlno_dou_05_02_off, 0, 0, 50529027, 50528256, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU06パタメット"*/"\x44\x4F\x55\x30\x36\x83\x70\x83\x5E\x83\x81\x83\x62\x83\x67", 0, 0, -1,
    0, (s32)btlgrpsel_dou_btlno_dou_06_01_off, 0, 0, 50529027, 50528256, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU06パタメット"*/"\x44\x4F\x55\x30\x36\x83\x70\x83\x5E\x83\x81\x83\x62\x83\x67", 0, 0,
    -1, 0, (s32)btlgrpsel_dou_btlno_dou_06_02_off, 0, 0, 50529027, 50528256, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU06パタメット"*/"\x44\x4F\x55\x30\x36\x83\x70\x83\x5E\x83\x81\x83\x62\x83\x67", 0,
    0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_06_03_off, 0, 0, 50529027, 50528256,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU07エルモス"*/"\x44\x4F\x55\x30\x37\x83\x47\x83\x8B\x83\x82\x83\x58",
    0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_07_01_off, 0, 0, 50529027,
    50528256, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"DOU08ヘビーボム"*/"\x44\x4F\x55\x30\x38\x83\x77\x83\x72\x81\x5B\x83\x7B\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_08_01_off, 0, 0,
    50529027, 50528256, 50529027, 50529027, 50530826, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU09バブル"*/"\x44\x4F\x55\x30\x39\x83\x6F\x83\x75\x83\x8B", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_09_01_off, 0,
    0, 50529027, 50528256, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU09エルモス"*/"\x44\x4F\x55\x30\x39\x83\x47\x83\x8B\x83\x82\x83\x58", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_09_02_off,
    0, 0, 50529027, 50528256, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU12キラー大砲"*/"\x44\x4F\x55\x31\x32\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0,
    (s32)btlgrpsel_dou_btlno_dou_12_01_off, 0, 0, 50529027, 50528256, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU12キラー大砲"*/"\x44\x4F\x55\x31\x32\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1,
    0, (s32)btlgrpsel_dou_btlno_dou_12_02_off, 0, 0, 50529027, 50528256, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU12キラー"*/"\x44\x4F\x55\x31\x32\x83\x4C\x83\x89\x81\x5B", 0, 0,
    -1, 0, (s32)btlgrpsel_dou_btlno_dou_12_99_off, 0, 0, 50529027, 50528256, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU13キラー大砲"*/"\x44\x4F\x55\x31\x33\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0,
    0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_13_01_off, 0, 0, 50529027, 50528256,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU13キラー大砲"*/"\x44\x4F\x55\x31\x33\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43",
    0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_13_02_off, 0, 0, 50529027,
    50528256, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"DOU13キラー大砲"*/"\x44\x4F\x55\x31\x33\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_13_03_off, 0, 0,
    50529027, 50528256, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU13キラー大砲"*/"\x44\x4F\x55\x31\x33\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_13_04_off, 0,
    0, 50529027, 50528256, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"DOU13キラー"*/"\x44\x4F\x55\x31\x33\x83\x4C\x83\x89\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_dou_btlno_dou_13_99_off,
    0, 0, 50529027, 50528256, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

s32 btl_dou_setup_no_tbl[] = {
    (s32)"BTLNO_DOU_TEST1", 0, (s32)"BTLNO_DOU_TEST2", 1, (s32)"BTLNO_DOU_TEST3", 2, (s32)"BTLNO_DOU_01_01", 3,
    (s32)"BTLNO_DOU_02_01", 4, (s32)"BTLNO_DOU_02_02", 5, (s32)"BTLNO_DOU_03_01", 6, (s32)"BTLNO_DOU_03_99", 7,
    (s32)"BTLNO_DOU_03_02", 8, (s32)"BTLNO_DOU_03_03", 9, (s32)"BTLNO_DOU_05_01", 10, (s32)"BTLNO_DOU_05_02", 11,
    (s32)"BTLNO_DOU_06_01", 12, (s32)"BTLNO_DOU_06_02", 13, (s32)"BTLNO_DOU_06_03", 14, (s32)"BTLNO_DOU_07_01", 15,
    (s32)"BTLNO_DOU_08_01", 16, (s32)"BTLNO_DOU_09_01", 17, (s32)"BTLNO_DOU_09_02", 18, (s32)"BTLNO_DOU_12_01", 19,
    (s32)"BTLNO_DOU_12_02", 20, (s32)"BTLNO_DOU_12_99", 21, (s32)"BTLNO_DOU_13_01", 22, (s32)"BTLNO_DOU_13_02", 23,
    (s32)"BTLNO_DOU_13_03", 24, (s32)"BTLNO_DOU_13_04", 25, (s32)"BTLNO_DOU_13_99", 26, 0, 0,
};

EVT_BEGIN(bgset_dou_wave_event)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 200)
    SET_VALUE(LW(2), 200)
    SET_VALUE(LW(3), 100)
    SET_VALUE(LW(4), 300)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 400)
    SET_VALUE(LW(7), 2500)
    LABEL(0)
    CALL(_wave_offset, STRING("s00_suimen"), LW(0), 800, 30, LW(1), 300, 10)
    CALL(_wave_offset, STRING("mobj_jump01"), LW(2), 600, 20, LW(3), 250, 6)
    CALL(_wave_offset, STRING("SFX_STG5_SHIP_ON1"), LW(4), 1100, 40, LW(5), 360, 7)
    CALL(_wave_offset, STRING("BGM_STG5_DOU1"), LW(6), 1250, 50, LW(7), 450, 8)
    CALL(_wave_offset, STRING("ENV_STG5_DOU3"), LW(8), 1100, 50, LW(9), 400, 6)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

