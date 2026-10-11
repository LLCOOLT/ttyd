#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/effdrv.h"
#include "battle/battle.h"
#include "battle/battle_stage_object.h"

EffectEntry* unk_las_bss0000009c[6];
s8 unk_las_bss00000098;
EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
void mapObjGetPos(const char* name, Vec* pos);

USER_FUNC(_gear_rotate);
USER_FUNC(check_battle_end);
USER_FUNC(evt_eff);
USER_FUNC(evt_eff_softdelete);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(unk_las_0000775c);
USER_FUNC(unk_las_00007774);
extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_heart_drop_param_default4[];
extern s32 battle_item_NONE[];
extern s32 battle_item_basabasa_chururu[];
extern s32 battle_item_default_param_list[];
extern s32 battle_item_karon[];
extern s32 battle_item_phantom[];
extern s32 battle_item_super_killer[];
extern s32 battle_item_super_killer_cannon[];
extern s32 battle_item_super_mahorn[];
extern s32 battle_item_wanwan[];
extern s32 unit_basabasa_chururu_17_data_528D0[];
extern s32 unit_black_karon[];
extern s32 unit_boss_batten_leader[];
extern s32 unit_boss_black_peach[];
extern s32 unit_boss_bunbaba[];
extern s32 unit_boss_koopa[];
extern s32 unit_boss_rampell_las[];
extern s32 unit_honenoko_17_data_57250[];
extern s32 unit_karon_17_data_3F680[];
extern s32 unit_phantom_17_data_540A8[];
extern s32 unit_red_honenoko_17_data_58C90[];
extern s32 unit_super_killer[];
extern s32 unit_super_killer_cannon[];
extern s32 unit_super_mahorn_17_data_4CA30[];
extern s32 unit_wanwan_17_data_50DF8[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_las_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_las_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_las___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_las___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_las_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_las___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_las_one_381[1];
__declspec(section ".data") u64 fd_battle_database_las_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_las_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_las___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_las___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_las_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_las___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_las_one_364[1];
s32 las_btlobject_data[228];
s32 las_btlstage_data[1090];
s32 btlparty_las_las_05_01[60];
__declspec(section ".data") s32 btlgrp_las_las_05_01[8];
__declspec(section ".data") s32 btlparty_las_las_17_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_17_01_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_17_02_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_17_02_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_17_03_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_17_03_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_17_04_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_17_04_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_09_rampell[12];
__declspec(section ".data") s32 btlgrp_las_las_09_rampell[8];
__declspec(section ".data") s32 btlparty_las_las_bunbaba[12];
__declspec(section ".data") s32 btlgrp_las_las_bunbaba[8];
__declspec(section ".data") s32 btlparty_las_las_28_batten_leader[12];
__declspec(section ".data") s32 btlgrp_las_las_28_batten_leader[8];
__declspec(section ".data") s32 btlparty_las_las_28_koopa[12];
__declspec(section ".data") s32 btlgrp_las_las_28_koopa[8];
__declspec(section ".data") s32 btlparty_las_las_29_black_peach_1[12];
__declspec(section ".data") s32 btlgrp_las_las_29_black_peach_1[8];
__declspec(section ".data") s32 btlparty_las_las_29_black_peach_2[12];
__declspec(section ".data") s32 btlgrp_las_las_29_black_peach_2[8];
s32 btlparty_las_las_01_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_01_01_off_1[8];
s32 btlparty_las_las_01_02_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_01_02_off_1[8];
s32 btlparty_las_las_01_03_off_1[48];
__declspec(section ".data") s32 btlgrp_las_las_01_03_off_1[8];
s32 btlparty_las_las_01_01_off_2[24];
__declspec(section ".data") s32 btlgrp_las_las_01_01_off_2[8];
s32 btlparty_las_las_01_02_off_2[36];
__declspec(section ".data") s32 btlgrp_las_las_01_02_off_2[8];
s32 btlparty_las_las_01_03_off_2[48];
__declspec(section ".data") s32 btlgrp_las_las_01_03_off_2[8];
s32 btlparty_las_las_02_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_02_01_off_1[8];
s32 btlparty_las_las_02_02_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_02_02_off_1[8];
s32 btlparty_las_las_02_03_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_02_03_off_1[8];
s32 btlparty_las_las_02_04_off_1[48];
__declspec(section ".data") s32 btlgrp_las_las_02_04_off_1[8];
s32 btlparty_las_las_02_05_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_02_05_off_1[8];
s32 btlparty_las_las_02_06_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_02_06_off_1[8];
s32 btlparty_las_las_02_99_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_02_99_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_03_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_03_01_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_03_02_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_03_02_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_03_03_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_03_03_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_03_01_off_2[12];
__declspec(section ".data") s32 btlgrp_las_las_03_01_off_2[8];
__declspec(section ".data") s32 btlparty_las_las_03_02_off_2[12];
__declspec(section ".data") s32 btlgrp_las_las_03_02_off_2[8];
__declspec(section ".data") s32 btlparty_las_las_03_03_off_2[12];
__declspec(section ".data") s32 btlgrp_las_las_03_03_off_2[8];
__declspec(section ".data") s32 btlparty_las_las_04_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_04_01_off_1[8];
s32 btlparty_las_las_06_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_01_off_1[8];
s32 btlparty_las_las_06_02_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_02_off_1[8];
s32 btlparty_las_las_06_03_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_03_off_1[8];
s32 btlparty_las_las_06_04_off_1[48];
__declspec(section ".data") s32 btlgrp_las_las_06_04_off_1[8];
s32 btlparty_las_las_06_05_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_05_off_1[8];
s32 btlparty_las_las_06_06_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_06_off_1[8];
s32 btlparty_las_las_06_99_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_06_99_off_1[8];
s32 btlparty_las_las_07_01_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_07_01_off_1[8];
s32 btlparty_las_las_07_02_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_07_02_off_1[8];
s32 btlparty_las_las_07_03_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_07_03_off_1[8];
s32 btlparty_las_las_09_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_09_01_off_1[8];
s32 btlparty_las_las_09_02_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_09_02_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_19_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_19_01_off_1[8];
s32 btlparty_las_las_19_02_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_19_02_off_1[8];
s32 btlparty_las_las_19_03_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_19_03_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_20_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_20_01_off_1[8];
s32 btlparty_las_las_21_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_21_01_off_1[8];
s32 btlparty_las_las_21_02_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_21_02_off_1[8];
s32 btlparty_las_las_22_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_22_01_off_1[8];
s32 btlparty_las_las_22_02_off_1[48];
__declspec(section ".data") s32 btlgrp_las_las_22_02_off_1[8];
s32 btlparty_las_las_22_03_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_22_03_off_1[8];
s32 btlparty_las_las_24_01_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_24_01_off_1[8];
__declspec(section ".data") s32 btlparty_las_las_25_01_off_1[12];
__declspec(section ".data") s32 btlgrp_las_las_25_01_off_1[8];
s32 btlparty_las_las_25_02_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_25_02_off_1[8];
s32 btlparty_las_las_25_03_off_1[48];
__declspec(section ".data") s32 btlgrp_las_las_25_03_off_1[8];
s32 btlparty_las_las_25_04_off_1[24];
__declspec(section ".data") s32 btlgrp_las_las_25_04_off_1[8];
s32 btlparty_las_las_25_05_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_25_05_off_1[8];
s32 btlparty_las_las_25_06_off_1[36];
__declspec(section ".data") s32 btlgrp_las_las_25_06_off_1[8];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test2_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test3_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test4_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test5_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test6_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test7_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_05_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_rampell_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_04_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_28_koopa_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_bunbaba_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_28_batten_leader_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_29_black_peach_1_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_29_black_peach_2_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_01_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_02_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_03_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_04_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_05_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_06_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_99_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_01_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_02_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_03_off[9];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_04_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_04_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_05_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_06_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_99_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_20_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_21_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_21_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_24_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_01_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_02_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_03_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_04_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_05_off[6];
__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_06_off[6];
s32 btlsetup_las_tbl[1037];
s32 btl_las_setup_no_tbl[122];
s32 bgset_las_gear_event[38];
s32 stg_08_1_init_sub_event[97];
__declspec(section ".data") s32 stg_08_1_init_event[4];
s32 stg_08_6_init_sub_event[46];
__declspec(section ".data") s32 stg_08_6_init_event[4];

USER_FUNC(unk_las_0000775c) {
    unk_las_bss00000098 = 1;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_battle_database_las_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_las_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_las___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_las___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_las_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_las___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_las_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_las_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_las_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_las___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_las___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_las_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_las___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_las_one_364[] = {
    1065353216,
};

s32 las_btlobject_data[] = {
    (s32)"A1", 131072, 1119485952, 0, -1031798784, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C_kabe", 131075, 0, 0,
    0, 3932160, (s32)"gear_01a", 131075, 0, 0, 0, 3932160,
    (s32)"gear_01b", 131075, 0, 0, 0, 3932160, (s32)"gear_02a", 131075,
    0, 0, 0, 3932160, (s32)"gear_02b", 131075, 0, 0,
    0, 3932160, (s32)"gear_03a", 131075, 0, 0, 0, 3932160,
    (s32)"gear_03b", 131075, 0, 0, 0, 3932160, (s32)"B", 131074,
    0, 0, 0, 3932160, (s32)"C", 131075, 0, 0,
    0, 3932160, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"if_wire", 327686,
    0, 1124204544, 0, 0, (s32)"if_body", 327686, 0, 1124204544,
    0, 0, (s32)"C", 131075, 0, 0, -1027211264, 3932160,
    (s32)"C", 131075, 0, 0, -1027211264, 3932160, (s32)"if_wire", 327686,
    0, 1124204544, 0, 0, (s32)"if_body", 327686, 0, 1124204544,
    0, 0, (s32)"daiza_01", 131072, 1126039552, 0, -1042284544, 3932160,
    (s32)"daiza_02", 131072, 1119748096, 0, -1035468800, 171048960, (s32)"daiza_03", 131072,
    -1021444096, 0, -1042284544, 338165760, (s32)"daiza_04", 131072, -1027735552, 0,
    -1035468800, 505282560, (s32)"B", 131074, 0, 0, 0, 3932160,
    (s32)"C", 131075, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"rou1", 131072, 1114112000, 0,
    -1029570560, 3932160, (s32)"rou2", 131072, -1025900544, 0, -1031143424, 3932160,
    (s32)"rou3", 131072, -1033371648, 0, -1029570560, 3932160, (s32)"rou4", 131072,
    1127415808, 0, -1034420224, 3932160, (s32)"rou5", 131072, 1121583104, 0,
    -1031143424, 3932160, (s32)"rou6", 131072, -1020067840, 0, -1034420224, 3932160,
    (s32)"B", 131074, 1119223808, 0, -1033633792, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160, (s32)"A2", 131073, 0, 0,
    1117782016, 3932160, (s32)"C", 131075, 0, 0, 0, 3932160,
    (s32)"B", 131074, 0, 0, 0, 3932160, (s32)"C", 131075,
    0, 0, 0, 3932160,
};

s32 las_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_08_5", 9, (s32)las_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, (s32)bgset_las_gear_event, 0, (s32)"bti_01", (s32)"stg_08_0", 2,
    (s32)(void*)((u8*)las_btlobject_data + 0xD8), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_08_0", 4, (s32)(void*)((u8*)las_btlobject_data + 0x108), 0, 0,
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
    (s32)"stg_08_2", 1, (s32)(void*)((u8*)las_btlobject_data + 0x168), 0, 0, 0, 0, 1677721602,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 1677721602,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 34603104, 536870912, 1704706, 0,
    0, 2047, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    100, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)"bti_01", (s32)"stg_08_2", 3, (s32)(void*)((u8*)las_btlobject_data + 0x180),
    0, 0, 0, 0, 1677721602, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 536870912, 1704706, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
    0, 0, 0, 0, 1677721602, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603104, 536870912, 1704706, 0, 0, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, (s32)"bti_01", (s32)"stg_08_4", 6, (s32)(void*)((u8*)las_btlobject_data + 0x1C8), 0, 0, 0,
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
    0, 0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_08_4",
    1, (s32)(void*)((u8*)las_btlobject_data + 0x258), 0, 0, 0, 0, 1677721602, 0,
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
    0, 0, 0, (s32)"bti_01", (s32)"stg_08_6", 8, (s32)(void*)((u8*)las_btlobject_data + 0x270), 0,
    0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    34603120, 268435456, 1704706, 0, 0, 2047, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 100, 0, 0, 0,
    0, 0, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    34603119, 536870912, 1704706, 0, 0, 2047, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 100, 0, 0, (s32)stg_08_6_init_event,
    0, 0, 0, 0, 0, 0, 0, 65793,
    (s32)"bti_01", (s32)"stg_08_1", 2, (s32)(void*)((u8*)las_btlobject_data + 0x330), 0, 0, 0, 0,
    1677721602, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, 0, 0, 0, 0,
    1677721602, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 34603104, 536870912, 1704706,
    0, 0, 2047, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 100, 0, 0, (s32)stg_08_1_init_event, 0, 0, 0,
    0, 0, 0, 0, 65793, (s32)"bti_01", (s32)"stg_08_3", 2,
    (s32)(void*)((u8*)las_btlobject_data + 0x360), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0,
};

s32 btlparty_las_las_05_01[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_black_karon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_karon,
};

__declspec(section ".data") s32 btlgrp_las_las_05_01[] = {
    5, (s32)btlparty_las_las_05_01, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

__declspec(section ".data") s32 btlparty_las_las_17_01_off_1[] = {
    (s32)unit_honenoko_17_data_57250, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_NONE,
};

__declspec(section ".data") s32 btlgrp_las_las_17_01_off_1[] = {
    1, (s32)btlparty_las_las_17_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_17_02_off_1[] = {
    (s32)unit_red_honenoko_17_data_58C90, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_NONE,
};

__declspec(section ".data") s32 btlgrp_las_las_17_02_off_1[] = {
    1, (s32)btlparty_las_las_17_02_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_17_03_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_NONE,
};

__declspec(section ".data") s32 btlgrp_las_las_17_03_off_1[] = {
    1, (s32)btlparty_las_las_17_03_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

__declspec(section ".data") s32 btlparty_las_las_17_04_off_1[] = {
    (s32)unit_black_karon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_NONE,
};

__declspec(section ".data") s32 btlgrp_las_las_17_04_off_1[] = {
    1, (s32)btlparty_las_las_17_04_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_09_rampell[] = {
    (s32)unit_boss_rampell_las, 16777216, 67108868, 1113325568, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_09_rampell[] = {
    1, (s32)btlparty_las_las_09_rampell, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_bunbaba[] = {
    (s32)unit_boss_bunbaba, 16777216, 67108868, 1136033792, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_bunbaba[] = {
    1, (s32)btlparty_las_las_bunbaba, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_28_batten_leader[] = {
    (s32)unit_boss_batten_leader, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_28_batten_leader[] = {
    1, (s32)btlparty_las_las_28_batten_leader, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_28_koopa[] = {
    (s32)unit_boss_koopa, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_28_koopa[] = {
    1, (s32)btlparty_las_las_28_koopa, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_29_black_peach_1[] = {
    (s32)unit_boss_black_peach, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_29_black_peach_1[] = {
    1, (s32)btlparty_las_las_29_black_peach_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_29_black_peach_2[] = {
    (s32)unit_boss_black_peach, 16777216, 67108868, 1119092736, 0, 0, 0, 1,
    0, 0, 0, (s32)battle_item_default_param_list,
};

__declspec(section ".data") s32 btlgrp_las_las_29_black_peach_2[] = {
    1, (s32)btlparty_las_las_29_black_peach_2, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_01_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_01_off_1[] = {
    2, (s32)btlparty_las_las_01_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_02_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_02_off_1[] = {
    3, (s32)btlparty_las_las_01_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_03_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1125515264,
    1124204544, 1101004800, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_03_off_1[] = {
    4, (s32)btlparty_las_las_01_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_01_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1116471296, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1121714176,
    1124204544, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_01_off_2[] = {
    2, (s32)btlparty_las_las_01_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_02_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736,
    1124204544, 0, 0, 0, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_02_off_2[] = {
    3, (s32)btlparty_las_las_01_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_01_03_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 0, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1125515264,
    1124204544, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_01_03_off_2[] = {
    4, (s32)btlparty_las_las_01_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_02_01_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_karon,
};

__declspec(section ".data") s32 btlgrp_las_las_02_01_off_1[] = {
    2, (s32)btlparty_las_las_02_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_02_02_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_02_02_off_1[] = {
    3, (s32)btlparty_las_las_02_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_02_03_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_02_03_off_1[] = {
    3, (s32)btlparty_las_las_02_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_02_04_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_karon,
};

__declspec(section ".data") s32 btlgrp_las_las_02_04_off_1[] = {
    4, (s32)btlparty_las_las_02_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_02_05_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_02_05_off_1[] = {
    2, (s32)btlparty_las_las_02_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_02_06_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_02_06_off_1[] = {
    2, (s32)btlparty_las_las_02_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_02_99_off_1[] = {
    (s32)unit_super_killer, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer, (s32)unit_super_killer, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer,
};

__declspec(section ".data") s32 btlgrp_las_las_02_99_off_1[] = {
    2, (s32)btlparty_las_las_02_99_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_01_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_01_off_1[] = {
    1, (s32)btlparty_las_las_03_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_02_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_02_off_1[] = {
    1, (s32)btlparty_las_las_03_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_03_off_1[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_03_off_1[] = {
    1, (s32)btlparty_las_las_03_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_01_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_01_off_2[] = {
    1, (s32)btlparty_las_las_03_01_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_02_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_02_off_2[] = {
    1, (s32)btlparty_las_las_03_02_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_03_03_off_2[] = {
    (s32)unit_basabasa_chururu_17_data_528D0, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 0,
    0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_las_las_03_03_off_2[] = {
    1, (s32)btlparty_las_las_03_03_off_2, 25, 25, 50, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_04_01_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_04_01_off_1[] = {
    1, (s32)btlparty_las_las_04_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_06_01_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_06_01_off_1[] = {
    2, (s32)btlparty_las_las_06_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_06_02_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_06_02_off_1[] = {
    2, (s32)btlparty_las_las_06_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_06_03_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_06_03_off_1[] = {
    2, (s32)btlparty_las_las_06_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_06_04_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_06_04_off_1[] = {
    4, (s32)btlparty_las_las_06_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_06_05_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_06_05_off_1[] = {
    2, (s32)btlparty_las_las_06_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_06_06_off_1[] = {
    (s32)unit_super_killer_cannon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer_cannon, (s32)unit_super_killer_cannon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer_cannon,
};

__declspec(section ".data") s32 btlgrp_las_las_06_06_off_1[] = {
    2, (s32)btlparty_las_las_06_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_06_99_off_1[] = {
    (s32)unit_super_killer, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_killer, (s32)unit_super_killer, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_killer,
};

__declspec(section ".data") s32 btlgrp_las_las_06_99_off_1[] = {
    2, (s32)btlparty_las_las_06_99_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_07_01_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_07_01_off_1[] = {
    3, (s32)btlparty_las_las_07_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_07_02_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_07_02_off_1[] = {
    3, (s32)btlparty_las_las_07_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_07_03_off_1[] = {
    (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon_17_data_3F680, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_07_03_off_1[] = {
    3, (s32)btlparty_las_las_07_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_09_01_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_las_las_09_01_off_1[] = {
    2, (s32)btlparty_las_las_09_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_09_02_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_las_las_09_02_off_1[] = {
    3, (s32)btlparty_las_las_09_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_19_01_off_1[] = {
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_19_01_off_1[] = {
    1, (s32)btlparty_las_las_19_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_19_02_off_1[] = {
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_19_02_off_1[] = {
    2, (s32)btlparty_las_las_19_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_19_03_off_1[] = {
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_19_03_off_1[] = {
    3, (s32)btlparty_las_las_19_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

__declspec(section ".data") s32 btlparty_las_las_20_01_off_1[] = {
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_20_01_off_1[] = {
    1, (s32)btlparty_las_las_20_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_21_01_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_las_las_21_01_off_1[] = {
    2, (s32)btlparty_las_las_21_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_21_02_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_las_las_21_02_off_1[] = {
    2, (s32)btlparty_las_las_21_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_22_01_off_1[] = {
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_22_01_off_1[] = {
    2, (s32)btlparty_las_las_22_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_22_02_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_22_02_off_1[] = {
    4, (s32)btlparty_las_las_22_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_22_03_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_22_03_off_1[] = {
    2, (s32)btlparty_las_las_22_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_las_las_24_01_off_1[] = {
    (s32)unit_wanwan_17_data_50DF8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_24_01_off_1[] = {
    2, (s32)btlparty_las_las_24_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_las_las_25_01_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_25_01_off_1[] = {
    1, (s32)btlparty_las_las_25_01_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_25_02_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_25_02_off_1[] = {
    3, (s32)btlparty_las_las_25_02_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_25_03_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_25_03_off_1[] = {
    4, (s32)btlparty_las_las_25_03_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_25_04_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_25_04_off_1[] = {
    2, (s32)btlparty_las_las_25_04_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_25_05_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_super_mahorn_17_data_4CA30, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_las_las_25_05_off_1[] = {
    3, (s32)btlparty_las_las_25_05_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_las_las_25_06_off_1[] = {
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom_17_data_540A8, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_las_las_25_06_off_1[] = {
    3, (s32)btlparty_las_las_25_06_off_1, 25, 25, 50, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test1_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test2_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test3_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test4_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0xF54), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test5_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0x884), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test6_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_test7_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0xBEC), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_05_01_off[] = {
    50, (s32)btlgrp_las_las_05_01, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_rampell_off[] = {
    50, (s32)btlgrp_las_las_09_rampell, (s32)(void*)((u8*)las_btlstage_data + 0xF54), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_01_off[] = {
    50, (s32)btlgrp_las_las_17_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_02_off[] = {
    50, (s32)btlgrp_las_las_17_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_03_off[] = {
    50, (s32)btlgrp_las_las_17_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_17_04_off[] = {
    50, (s32)btlgrp_las_las_17_04_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xA38), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_28_koopa_off[] = {
    50, (s32)btlgrp_las_las_28_koopa, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_bunbaba_off[] = {
    50, (s32)btlgrp_las_las_bunbaba, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_28_batten_leader_off[] = {
    50, (s32)btlgrp_las_las_28_batten_leader, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_29_black_peach_1_off[] = {
    50, (s32)btlgrp_las_las_29_black_peach_1, (s32)(void*)((u8*)las_btlstage_data + 0xBEC), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_29_black_peach_2_off[] = {
    50, (s32)btlgrp_las_las_29_black_peach_2, (s32)(void*)((u8*)las_btlstage_data + 0xBEC), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_01_off[] = {
    20, (s32)btlgrp_las_las_01_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x1B4), 0, (s32)btlgrp_las_las_01_01_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x368), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_02_off[] = {
    20, (s32)btlgrp_las_las_01_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x1B4), 0, (s32)btlgrp_las_las_01_02_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x368), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_01_03_off[] = {
    20, (s32)btlgrp_las_las_01_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x1B4), 0, (s32)btlgrp_las_las_01_03_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x368), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_01_off[] = {
    20, (s32)btlgrp_las_las_02_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_02_off[] = {
    20, (s32)btlgrp_las_las_02_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_03_off[] = {
    20, (s32)btlgrp_las_las_02_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_04_off[] = {
    20, (s32)btlgrp_las_las_02_04_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_05_off[] = {
    20, (s32)btlgrp_las_las_02_05_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_06_off[] = {
    20, (s32)btlgrp_las_las_02_06_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_02_99_off[] = {
    20, (s32)btlgrp_las_las_02_99_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_01_off[] = {
    20, (s32)btlgrp_las_las_03_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, (s32)btlgrp_las_las_03_01_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x6D0), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_02_off[] = {
    20, (s32)btlgrp_las_las_03_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, (s32)btlgrp_las_las_03_02_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x6D0), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_03_03_off[] = {
    20, (s32)btlgrp_las_las_03_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, (s32)btlgrp_las_las_03_03_off_2, (s32)(void*)((u8*)las_btlstage_data + 0x6D0), 0, 0,
    0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_04_01_off[] = {
    20, (s32)btlgrp_las_las_04_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_01_off[] = {
    20, (s32)btlgrp_las_las_06_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_02_off[] = {
    20, (s32)btlgrp_las_las_06_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_03_off[] = {
    20, (s32)btlgrp_las_las_06_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_04_off[] = {
    20, (s32)btlgrp_las_las_06_04_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_05_off[] = {
    20, (s32)btlgrp_las_las_06_05_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_06_off[] = {
    20, (s32)btlgrp_las_las_06_06_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_06_99_off[] = {
    20, (s32)btlgrp_las_las_06_99_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xDA0), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_01_off[] = {
    20, (s32)btlgrp_las_las_07_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_02_off[] = {
    20, (s32)btlgrp_las_las_07_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_07_03_off[] = {
    20, (s32)btlgrp_las_las_07_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_01_off[] = {
    20, (s32)btlgrp_las_las_09_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xF54), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_09_02_off[] = {
    20, (s32)btlgrp_las_las_09_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0xF54), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_01_off[] = {
    20, (s32)btlgrp_las_las_19_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_02_off[] = {
    20, (s32)btlgrp_las_las_19_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_19_03_off[] = {
    20, (s32)btlgrp_las_las_19_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_20_01_off[] = {
    20, (s32)btlgrp_las_las_20_01_off_1, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_21_01_off[] = {
    20, (s32)btlgrp_las_las_21_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_21_02_off[] = {
    20, (s32)btlgrp_las_las_21_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_01_off[] = {
    20, (s32)btlgrp_las_las_22_01_off_1, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_02_off[] = {
    20, (s32)btlgrp_las_las_22_02_off_1, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_22_03_off[] = {
    20, (s32)btlgrp_las_las_22_03_off_1, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_24_01_off[] = {
    20, (s32)btlgrp_las_las_24_01_off_1, (s32)las_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_01_off[] = {
    20, (s32)btlgrp_las_las_25_01_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_02_off[] = {
    20, (s32)btlgrp_las_las_25_02_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_03_off[] = {
    20, (s32)btlgrp_las_las_25_03_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_04_off[] = {
    20, (s32)btlgrp_las_las_25_04_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_05_off[] = {
    20, (s32)btlgrp_las_las_25_05_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_las_btlno_las_25_06_off[] = {
    20, (s32)btlgrp_las_las_25_06_off_1, (s32)(void*)((u8*)las_btlstage_data + 0x51C), 0, 0, 0,
};

s32 btlsetup_las_tbl[] = {
    (s32)/*"マップstg_08_0"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x30", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_test1_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_1"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x31", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_test2_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_2"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x32", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_test3_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x33", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_test4_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_4"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x34", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_test5_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_5"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x35", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_test6_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マップstg_08_6"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x38\x5F\x36", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_test7_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"黒カロン"*/"\x8D\x95\x83\x4A\x83\x8D\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_05_01_off, 536870928, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_CHUBOSS_BATTLE1",
    (s32)/*"変身ランペル+魔女"*/"\x95\xCF\x90\x67\x83\x89\x83\x93\x83\x79\x83\x8B\x2B\x96\x82\x8F\x97", (s32)"las_09", 0, -1, 0, (s32)btlgrpsel_las_btlno_las_09_rampell_off, 536870928, 6,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_BOSS_STG3_3WOMEN1", (s32)/*"las17クリボー"*/"\x6C\x61\x73\x31\x37\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_17_01_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las17トゲクリボー"*/"\x6C\x61\x73\x31\x37\x83\x67\x83\x51\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_17_02_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las17ノコノコ"*/"\x6C\x61\x73\x31\x37\x83\x6D\x83\x52\x83\x6D\x83\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_17_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las17シンノスケ"*/"\x6C\x61\x73\x31\x37\x83\x56\x83\x93\x83\x6D\x83\x58\x83\x50", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_17_04_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"クッパ＆カメックオババ"*/"\x83\x4E\x83\x62\x83\x70\x81\x95\x83\x4A\x83\x81\x83\x62\x83\x4E\x83\x49\x83\x6F\x83\x6F", (s32)"las_28", 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_28_koopa_off, 536870928, 6, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG8_KOOPA", (s32)/*"ブンババ"*/"\x83\x75\x83\x93\x83\x6F\x83\x6F", (s32)"las_26",
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_bunbaba_off, 537919504, 6, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG1_GONBABA1", (s32)/*"バッテンリーダー"*/"\x83\x6F\x83\x62\x83\x65\x83\x93\x83\x8A\x81\x5B\x83\x5F\x81\x5B",
    (s32)"las_28", 0, -1, 0, (s32)btlgrpsel_las_btlno_las_28_batten_leader_off, 536870928, 5, 2570,
    0, 0, 0, 0, 0, 257, 16843009, (s32)"BGM_BOSS_STG8_3RDHEAD1",
    (s32)/*"ブラックピーチ1回目"*/"\x83\x75\x83\x89\x83\x62\x83\x4E\x83\x73\x81\x5B\x83\x60\x31\x89\xF1\x96\xDA", (s32)"las_29", 0, -1, 0, (s32)btlgrpsel_las_btlno_las_29_black_peach_1_off, 536870928, 6,
    168427777, 16843009, 16843009, 16845322, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_BOSS_STG8_WITCH", (s32)/*"ブラックピーチ2回目"*/"\x83\x75\x83\x89\x83\x62\x83\x4E\x83\x73\x81\x5B\x83\x60\x32\x89\xF1\x96\xDA", (s32)"las_29", 0, -1, 0, (s32)btlgrpsel_las_btlno_las_29_black_peach_2_off, 536870928,
    6, 168427777, 16843009, 16843009, 16845322, 16843009, 16843009, 16843009,
    16843009, (s32)"BGM_BOSS_STG8_LAST_BOSS2", (s32)/*"las01バサバサチュルル"*/"\x6C\x61\x73\x30\x31\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_01_01_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las01バサバサチュルル"*/"\x6C\x61\x73\x30\x31\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_01_02_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las01バサバサチュルル"*/"\x6C\x61\x73\x30\x31\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_01_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02カロン"*/"\x6C\x61\x73\x30\x32\x83\x4A\x83\x8D\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_02_01_off, 0, 0, 50529027, 50529027, 168428291,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02バサバサチュルル"*/"\x6C\x61\x73\x30\x32\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_02_02_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02カロン"*/"\x6C\x61\x73\x30\x32\x83\x4A\x83\x8D\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_02_03_off, 0, 0, 50529027,
    50529027, 168428291, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"las02カロン"*/"\x6C\x61\x73\x30\x32\x83\x4A\x83\x8D\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_02_04_off, 0, 0,
    50529027, 50529027, 168428291, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02スーパーキラー大砲"*/"\x6C\x61\x73\x30\x32\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_02_05_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02スーパーキラー大砲"*/"\x6C\x61\x73\x30\x32\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_02_06_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las02スーパーキラー"*/"\x6C\x61\x73\x30\x32\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_02_99_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las03バサバサチュルル"*/"\x6C\x61\x73\x30\x33\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_03_01_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las03バサバサチュルル"*/"\x6C\x61\x73\x30\x33\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_03_02_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las03バサバサチュルル"*/"\x6C\x61\x73\x30\x33\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_03_03_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las04ファントム"*/"\x6C\x61\x73\x30\x34\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_04_01_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"las06スーパーキラー大砲"*/"\x6C\x61\x73\x30\x36\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_06_01_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06スーパーキラー大砲"*/"\x6C\x61\x73\x30\x36\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_06_02_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06ファントム"*/"\x6C\x61\x73\x30\x36\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_06_03_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06ファントム"*/"\x6C\x61\x73\x30\x36\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_06_04_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06スーパーキラー大砲"*/"\x6C\x61\x73\x30\x36\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_06_05_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06スーパーキラー大砲"*/"\x6C\x61\x73\x30\x36\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B\x91\xE5\x96\x43", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_06_06_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las06スーパーキラー"*/"\x6C\x61\x73\x30\x36\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x4C\x83\x89\x81\x5B", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_06_99_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las07ファントム"*/"\x6C\x61\x73\x30\x37\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_07_01_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"las07カロン"*/"\x6C\x61\x73\x30\x37\x83\x4A\x83\x8D\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_07_02_off, 0, 0,
    50529027, 50529027, 168428291, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las07カロン"*/"\x6C\x61\x73\x30\x37\x83\x4A\x83\x8D\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_07_03_off, 0,
    0, 50529027, 50529027, 168428291, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las09ワンワン"*/"\x6C\x61\x73\x30\x39\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_09_01_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las09ワンワン"*/"\x6C\x61\x73\x30\x39\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_09_02_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las19スーパーマホーン"*/"\x6C\x61\x73\x31\x39\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_19_01_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las19スーパーマホーン"*/"\x6C\x61\x73\x31\x39\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_19_02_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las19スーパーマホーン"*/"\x6C\x61\x73\x31\x39\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_19_03_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las20スーパーマホーン"*/"\x6C\x61\x73\x32\x30\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_20_01_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"las21ワンワン"*/"\x6C\x61\x73\x32\x31\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_21_01_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las21ワンワン"*/"\x6C\x61\x73\x32\x31\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_21_02_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las22スーパーマホーン"*/"\x6C\x61\x73\x32\x32\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_22_01_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las22ファントム"*/"\x6C\x61\x73\x32\x32\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_22_02_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las22ワンワン"*/"\x6C\x61\x73\x32\x32\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_las_btlno_las_22_03_off, 0, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las24ワンワン"*/"\x6C\x61\x73\x32\x34\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_las_btlno_las_24_01_off, 0, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0,
    0, -1, 0, (s32)btlgrpsel_las_btlno_las_25_01_off, 0, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80",
    0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_25_02_off, 0, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_25_03_off, 0, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_25_04_off, 0,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_las_btlno_las_25_05_off,
    0, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"las25ファントム"*/"\x6C\x61\x73\x32\x35\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0, 0, -1, 0,
    (s32)btlgrpsel_las_btlno_las_25_06_off, 0, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

s32 btl_las_setup_no_tbl[] = {
    (s32)"BTLNO_LAS_TEST1", 0, (s32)"BTLNO_LAS_TEST2", 1, (s32)"BTLNO_LAS_TEST3", 2, (s32)"BTLNO_LAS_TEST4", 3,
    (s32)"BTLNO_LAS_TEST5", 4, (s32)"BTLNO_LAS_TEST6", 5, (s32)"BTLNO_LAS_TEST7", 6, (s32)"BTLNO_LAS_05_01", 7,
    (s32)"BTLNO_LAS_09_RAMPELL", 8, (s32)"BTLNO_LAS_17_01", 9, (s32)"BTLNO_LAS_17_02", 10, (s32)"BTLNO_LAS_17_03", 11,
    (s32)"BTLNO_LAS_17_04", 12, (s32)"BTLNO_LAS_28_KOOPA", 13, (s32)"BTLNO_LAS_BUNBABA", 14, (s32)"BTLNO_LAS_28_BATTEN_LEADER", 15,
    (s32)"BTLNO_LAS_29_BLACK_PEACH_1", 16, (s32)"BTLNO_LAS_29_BLACK_PEACH_2", 17, (s32)"BTLNO_LAS_01_01", 18, (s32)"BTLNO_LAS_01_02", 19,
    (s32)"BTLNO_LAS_01_03", 20, (s32)"BTLNO_LAS_02_01", 21, (s32)"BTLNO_LAS_02_02", 22, (s32)"BTLNO_LAS_02_03", 23,
    (s32)"BTLNO_LAS_02_04", 24, (s32)"BTLNO_LAS_02_05", 25, (s32)"BTLNO_LAS_02_06", 26, (s32)"BTLNO_LAS_02_99", 27,
    (s32)"BTLNO_LAS_03_01", 28, (s32)"BTLNO_LAS_03_02", 29, (s32)"BTLNO_LAS_03_03", 30, (s32)"BTLNO_LAS_04_01", 31,
    (s32)"BTLNO_LAS_06_01", 32, (s32)"BTLNO_LAS_06_02", 33, (s32)"BTLNO_LAS_06_03", 34, (s32)"BTLNO_LAS_06_04", 35,
    (s32)"BTLNO_LAS_06_05", 36, (s32)"BTLNO_LAS_06_06", 37, (s32)"BTLNO_LAS_06_99", 38, (s32)"BTLNO_LAS_07_01", 39,
    (s32)"BTLNO_LAS_07_02", 40, (s32)"BTLNO_LAS_07_03", 41, (s32)"BTLNO_LAS_09_01", 42, (s32)"BTLNO_LAS_09_02", 43,
    (s32)"BTLNO_LAS_19_01", 44, (s32)"BTLNO_LAS_19_02", 45, (s32)"BTLNO_LAS_19_03", 46, (s32)"BTLNO_LAS_20_01", 47,
    (s32)"BTLNO_LAS_21_01", 48, (s32)"BTLNO_LAS_21_02", 49, (s32)"BTLNO_LAS_22_01", 50, (s32)"BTLNO_LAS_22_02", 51,
    (s32)"BTLNO_LAS_22_03", 52, (s32)"BTLNO_LAS_24_01", 53, (s32)"BTLNO_LAS_25_01", 54, (s32)"BTLNO_LAS_25_02", 55,
    (s32)"BTLNO_LAS_25_03", 56, (s32)"BTLNO_LAS_25_04", 57, (s32)"BTLNO_LAS_25_05", 58, (s32)"BTLNO_LAS_25_06", 59,
    0, 0,
};

EVT_BEGIN(bgset_las_gear_event)
    SET_VALUE(LW(0), 0)
    SET_VALUE(LW(1), 0)
    SET_VALUE(LW(2), 0)
    LABEL(0)
    CALL(_gear_rotate, STRING("gear_01a"), STRING("gear_01b"), LW(0), 400, -1)
    CALL(_gear_rotate, STRING("gear_02a"), STRING("gear_02b"), LW(1), 600, 1)
    CALL(_gear_rotate, STRING("gear_03a"), STRING("gear_03b"), LW(2), 800, 1)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(stg_08_1_init_sub_event)
    CALL(evt_mapobj_get_position, STRING("hi1"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("_hi1"), STRING("fire"), 3, LW(0), LW(1), LW(2), FLOAT(1.0f), 1000, 0, 0, 0, 0, 0, 0)
    CALL(evt_mapobj_get_position, STRING("hi2"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("_hi2"), STRING("fire"), 3, LW(0), LW(1), LW(2), FLOAT(1.0f), 1000, 0, 0, 0, 0, 0, 0)
    CALL(evt_mapobj_get_position, STRING("hi3"), LW(0), LW(1), LW(2))
    CALL(evt_eff, STRING("_hi3"), STRING("fire"), 3, LW(0), LW(1), LW(2), FLOAT(1.0f), 1000, 0, 0, 0, 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi1"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi2"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi3"), 1)
    CALL(check_battle_end)
    CALL(evt_eff_softdelete, STRING("_hi1"))
    CALL(evt_eff_softdelete, STRING("_hi2"))
    CALL(evt_eff_softdelete, STRING("_hi3"))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(stg_08_1_init_event)
    SPAWN_EVENT(PTR(stg_08_1_init_sub_event))
    RETURN
EVT_END()

EVT_BEGIN(stg_08_6_init_sub_event)
    BEGIN_SIBLING_EVENT
        CALL(unk_las_00007774)
    END_SIBLING_EVENT
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi1"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi2"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi3"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi4"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi5"), 1)
    CALL(evt_mapobj_flag_onoff, 0, 1, STRING("hi6"), 1)
    CALL(check_battle_end)
    CALL(unk_las_0000775c)
    RETURN
EVT_END()

USER_FUNC(unk_las_00007774) {
    const char* names[6] = {"hi1", "hi2", "hi3", "hi4", "hi5", "hi6"};
    Vec pos;
    s32 i;

    if (isFirstCall) {
        unk_las_bss00000098 = 0;
        for (i = 0; i < 6; i++) {
            unk_las_bss0000009c[i] = effFireEntry(8, 0.0f, -1000.0f, 0.0f, 1.0f, 1000);
        }
    }
    if (unk_las_bss00000098) {
        for (i = 0; i < 6; i++) {
            effSoftDelete(unk_las_bss0000009c[i]);
        }
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 6; i++) {
        mapObjGetPos(names[i], &pos);
        if (pos.y > 0.0f) {
            f32* wk = unk_las_bss0000009c[i]->userdata;

            wk[1] = pos.x;
            wk[2] = pos.y - 15.0f;
            wk[3] = pos.z;
        }
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(check_battle_end) {
    return battleSeqEndCheck() ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(_gear_rotate) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    s32 frameVar = args[2];
    s32 frame = evtGetValue(event, frameVar);
    s32 total = evtGetValue(event, args[3]);
    s32 step = evtGetValue(event, args[4]);
    BattleStageObject* obj1 = BattleSearchObjectPtr(name1);
    BattleStageObject* obj2 = BattleSearchObjectPtr(name2);

    obj2->mRotation.z = obj1->mRotation.z = 360.0f * frame / total;
    frame += step;
    if (frame >= total) {
        frame = 0;
    }
    if (frame < 0) {
        frame = total - 1;
    }
    evtSetValue(event, frameVar, frame);
    return EVT_RETURN_DONE;
}

__declspec(section ".data") EVT_BEGIN(stg_08_6_init_event)
    SPAWN_EVENT(PTR(stg_08_6_init_sub_event))
    RETURN
EVT_END()

