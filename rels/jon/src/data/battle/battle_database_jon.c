#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on

extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_flower_drop_param_default4[];
extern s32 battle_flower_drop_param_default5[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_heart_drop_param_default4[];
extern s32 battle_heart_drop_param_default5[];
extern s32 battle_item_badge_borodo[];
extern s32 battle_item_basabasa_chururu[];
extern s32 battle_item_basabasa_green[];
extern s32 battle_item_bllizard[];
extern s32 battle_item_bomhei[];
extern s32 battle_item_borodo[];
extern s32 battle_item_bubble[];
extern s32 battle_item_burst_wanwan[];
extern s32 battle_item_chorobon[];
extern s32 battle_item_churantalar[];
extern s32 battle_item_dark_keeper[];
extern s32 battle_item_dokugassun[];
extern s32 battle_item_flower_chorobon[];
extern s32 battle_item_giant_bomb[];
extern s32 battle_item_hannya[];
extern s32 battle_item_heavy_bom[];
extern s32 battle_item_hennya[];
extern s32 battle_item_hinnya[];
extern s32 battle_item_honenoko[];
extern s32 battle_item_hyper_jyugem[];
extern s32 battle_item_hyper_sinemon[];
extern s32 battle_item_ice_pakkun[];
extern s32 battle_item_jyugem[];
extern s32 battle_item_karon[];
extern s32 battle_item_mahorn[];
extern s32 battle_item_mahorn_custom[];
extern s32 battle_item_monochrome_kurokumorn[];
extern s32 battle_item_pakkun_flower[];
extern s32 battle_item_patamet[];
extern s32 battle_item_patatogemet[];
extern s32 battle_item_phantom[];
extern s32 battle_item_piders[];
extern s32 battle_item_purple_teresa[];
extern s32 battle_item_sambo[];
extern s32 battle_item_sambo_mummy[];
extern s32 battle_item_sinemon[];
extern s32 battle_item_super_mahorn[];
extern s32 battle_item_teresa[];
extern s32 battle_item_togenoko_ace[];
extern s32 battle_item_twinkling_pansy[];
extern s32 battle_item_ura_noko[];
extern s32 battle_item_wanwan[];
extern s32 battle_item_yami_kuriboo[];
extern s32 battle_item_yami_noko[];
extern s32 battle_item_yami_patakuri[];
extern s32 battle_item_yami_togekuri[];
extern s32 battle_item_yamitogedaruma[];
extern s32 battle_item_zonbaba[];
extern s32 unit_badge_borodo[];
extern s32 unit_basabasa_chururu[];
extern s32 unit_basabasa_green[];
extern s32 unit_bllizard[];
extern s32 unit_bomhei[];
extern s32 unit_borodo[];
extern s32 unit_boss_zonbaba[];
extern s32 unit_bubble[];
extern s32 unit_burst_wanwan[];
extern s32 unit_chorobon[];
extern s32 unit_churantalar[];
extern s32 unit_dark_keeper[];
extern s32 unit_dokugassun[];
extern s32 unit_flower_chorobon[];
extern s32 unit_giant_bomb[];
extern s32 unit_hannya[];
extern s32 unit_heavy_bom[];
extern s32 unit_hennya[];
extern s32 unit_hinnya[];
extern s32 unit_honenoko[];
extern s32 unit_hyper_jyugem[];
extern s32 unit_hyper_sinemon[];
extern s32 unit_ice_pakkun[];
extern s32 unit_jyugem[];
extern s32 unit_karon[];
extern s32 unit_mahorn[];
extern s32 unit_mahorn_custom[];
extern s32 unit_monochrome_kurokumorn[];
extern s32 unit_monochrome_sinemon[];
extern s32 unit_pakkun_flower[];
extern s32 unit_patamet[];
extern s32 unit_patatogemet[];
extern s32 unit_phantom[];
extern s32 unit_piders[];
extern s32 unit_purple_teresa[];
extern s32 unit_sambo[];
extern s32 unit_sambo_mummy[];
extern s32 unit_sinemon[];
extern s32 unit_super_mahorn[];
extern s32 unit_teresa[];
extern s32 unit_togenoko_ace[];
extern s32 unit_twinkling_pansy[];
extern s32 unit_ura_noko[];
extern s32 unit_wanwan[];
extern s32 unit_yami_kuriboo[];
extern s32 unit_yami_noko[];
extern s32 unit_yami_pata[];
extern s32 unit_yami_patakuri[];
extern s32 unit_yami_togekuri[];
extern s32 unit_yamitogedaruma[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_battle_database_jon_negone_one_374;
__declspec(section ".data") s32 fd_battle_database_jon_neg_one_382[1];
__declspec(section ".data") s32 fd_battle_database_jon___local_PI_383[1];
__declspec(section ".data") s32 fd_battle_database_jon___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_battle_database_jon_one_negone_373;
__declspec(section ".data") s32 fd_battle_database_jon___local_PIO2_384[1];
__declspec(section ".data") s32 fd_battle_database_jon_one_381[1];
__declspec(section ".data") u64 fd_battle_database_jon_negone_one_360;
__declspec(section ".data") s32 fd_battle_database_jon_neg_one_365[1];
__declspec(section ".data") s32 fd_battle_database_jon___local_PI_366[1];
__declspec(section ".data") s32 fd_battle_database_jon___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_battle_database_jon_one_negone_359;
__declspec(section ".data") s32 fd_battle_database_jon___local_PIO2_367[1];
__declspec(section ".data") s32 fd_battle_database_jon_one_364[1];
s32 jon_btlobject_data[48];
s32 jon_btlstage_data[436];
__declspec(section ".data") s32 btlparty_jon_jon_100_01_off_1[12];
__declspec(section ".data") s32 btlgrp_jon_jon_100_01_off_1[8];
__declspec(section ".data") s32 btlparty_jon_jon_01_01_off_1[12];
__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_1[8];
s32 btlparty_jon_jon_01_01_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_2[8];
s32 btlparty_jon_jon_01_01_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_3[8];
s32 btlparty_jon_jon_01_02_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_1[8];
s32 btlparty_jon_jon_01_02_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_2[8];
s32 btlparty_jon_jon_01_02_off_3[60];
__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_3[8];
s32 btlparty_jon_jon_01_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_1[8];
s32 btlparty_jon_jon_01_03_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_2[8];
s32 btlparty_jon_jon_01_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_3[8];
s32 btlparty_jon_jon_01_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_1[8];
s32 btlparty_jon_jon_01_04_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_2[8];
s32 btlparty_jon_jon_01_04_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_3[8];
s32 btlparty_jon_jon_01_05_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_1[8];
s32 btlparty_jon_jon_01_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_2[8];
s32 btlparty_jon_jon_01_05_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_3[8];
s32 btlparty_jon_jon_11_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_1[8];
s32 btlparty_jon_jon_11_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_2[8];
s32 btlparty_jon_jon_11_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_3[8];
s32 btlparty_jon_jon_11_02_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_1[8];
s32 btlparty_jon_jon_11_02_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_2[8];
s32 btlparty_jon_jon_11_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_3[8];
s32 btlparty_jon_jon_11_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_1[8];
s32 btlparty_jon_jon_11_03_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_2[8];
s32 btlparty_jon_jon_11_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_3[8];
s32 btlparty_jon_jon_11_04_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_1[8];
s32 btlparty_jon_jon_11_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_2[8];
s32 btlparty_jon_jon_11_04_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_3[8];
s32 btlparty_jon_jon_11_05_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_1[8];
s32 btlparty_jon_jon_11_05_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_2[8];
s32 btlparty_jon_jon_11_05_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_3[8];
s32 btlparty_jon_jon_21_01_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_1[8];
s32 btlparty_jon_jon_21_01_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_2[8];
s32 btlparty_jon_jon_21_01_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_3[8];
s32 btlparty_jon_jon_21_02_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_1[8];
s32 btlparty_jon_jon_21_02_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_2[8];
s32 btlparty_jon_jon_21_02_off_3[60];
__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_3[8];
s32 btlparty_jon_jon_21_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_1[8];
s32 btlparty_jon_jon_21_03_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_2[8];
s32 btlparty_jon_jon_21_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_3[8];
s32 btlparty_jon_jon_21_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_1[8];
s32 btlparty_jon_jon_21_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_2[8];
s32 btlparty_jon_jon_21_04_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_3[8];
s32 btlparty_jon_jon_21_05_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_1[8];
s32 btlparty_jon_jon_21_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_2[8];
s32 btlparty_jon_jon_21_05_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_3[8];
s32 btlparty_jon_jon_31_01_off_1[24];
__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_1[8];
s32 btlparty_jon_jon_31_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_2[8];
s32 btlparty_jon_jon_31_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_3[8];
s32 btlparty_jon_jon_31_02_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_1[8];
s32 btlparty_jon_jon_31_02_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_2[8];
s32 btlparty_jon_jon_31_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_3[8];
s32 btlparty_jon_jon_31_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_1[8];
s32 btlparty_jon_jon_31_03_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_2[8];
s32 btlparty_jon_jon_31_03_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_3[8];
s32 btlparty_jon_jon_31_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_1[8];
s32 btlparty_jon_jon_31_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_2[8];
s32 btlparty_jon_jon_31_04_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_3[8];
s32 btlparty_jon_jon_31_05_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_1[8];
s32 btlparty_jon_jon_31_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_2[8];
s32 btlparty_jon_jon_31_05_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_3[8];
s32 btlparty_jon_jon_41_01_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_1[8];
s32 btlparty_jon_jon_41_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_2[8];
s32 btlparty_jon_jon_41_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_3[8];
s32 btlparty_jon_jon_41_02_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_1[8];
s32 btlparty_jon_jon_41_02_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_2[8];
s32 btlparty_jon_jon_41_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_3[8];
s32 btlparty_jon_jon_41_03_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_1[8];
s32 btlparty_jon_jon_41_03_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_2[8];
s32 btlparty_jon_jon_41_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_3[8];
s32 btlparty_jon_jon_41_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_1[8];
s32 btlparty_jon_jon_41_04_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_2[8];
s32 btlparty_jon_jon_41_04_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_3[8];
s32 btlparty_jon_jon_41_05_off_1[24];
__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_1[8];
s32 btlparty_jon_jon_41_05_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_2[8];
s32 btlparty_jon_jon_41_05_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_3[8];
s32 btlparty_jon_jon_51_01_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_1[8];
s32 btlparty_jon_jon_51_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_2[8];
s32 btlparty_jon_jon_51_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_3[8];
s32 btlparty_jon_jon_51_02_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_1[8];
s32 btlparty_jon_jon_51_02_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_2[8];
s32 btlparty_jon_jon_51_02_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_3[8];
s32 btlparty_jon_jon_51_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_1[8];
s32 btlparty_jon_jon_51_03_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_2[8];
s32 btlparty_jon_jon_51_03_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_3[8];
s32 btlparty_jon_jon_51_04_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_1[8];
s32 btlparty_jon_jon_51_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_2[8];
s32 btlparty_jon_jon_51_04_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_3[8];
s32 btlparty_jon_jon_51_05_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_1[8];
s32 btlparty_jon_jon_51_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_2[8];
s32 btlparty_jon_jon_51_05_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_3[8];
s32 btlparty_jon_jon_61_01_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_1[8];
s32 btlparty_jon_jon_61_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_2[8];
s32 btlparty_jon_jon_61_01_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_3[8];
s32 btlparty_jon_jon_61_02_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_1[8];
s32 btlparty_jon_jon_61_02_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_2[8];
s32 btlparty_jon_jon_61_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_3[8];
s32 btlparty_jon_jon_61_03_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_1[8];
s32 btlparty_jon_jon_61_03_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_2[8];
s32 btlparty_jon_jon_61_03_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_3[8];
s32 btlparty_jon_jon_61_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_1[8];
s32 btlparty_jon_jon_61_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_2[8];
s32 btlparty_jon_jon_61_04_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_3[8];
s32 btlparty_jon_jon_61_05_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_1[8];
s32 btlparty_jon_jon_61_05_off_2[24];
__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_2[8];
s32 btlparty_jon_jon_61_05_off_3[24];
__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_3[8];
s32 btlparty_jon_jon_71_01_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_1[8];
s32 btlparty_jon_jon_71_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_2[8];
s32 btlparty_jon_jon_71_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_3[8];
s32 btlparty_jon_jon_71_02_off_1[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_1[8];
s32 btlparty_jon_jon_71_02_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_2[8];
s32 btlparty_jon_jon_71_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_3[8];
s32 btlparty_jon_jon_71_03_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_1[8];
s32 btlparty_jon_jon_71_03_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_2[8];
s32 btlparty_jon_jon_71_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_3[8];
s32 btlparty_jon_jon_71_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_1[8];
s32 btlparty_jon_jon_71_04_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_2[8];
s32 btlparty_jon_jon_71_04_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_3[8];
s32 btlparty_jon_jon_71_05_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_1[8];
s32 btlparty_jon_jon_71_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_2[8];
s32 btlparty_jon_jon_71_05_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_3[8];
s32 btlparty_jon_jon_81_01_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_1[8];
s32 btlparty_jon_jon_81_01_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_2[8];
s32 btlparty_jon_jon_81_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_3[8];
s32 btlparty_jon_jon_81_02_off_1[24];
__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_1[8];
s32 btlparty_jon_jon_81_02_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_2[8];
s32 btlparty_jon_jon_81_02_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_3[8];
s32 btlparty_jon_jon_81_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_1[8];
s32 btlparty_jon_jon_81_03_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_2[8];
s32 btlparty_jon_jon_81_03_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_3[8];
s32 btlparty_jon_jon_81_04_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_1[8];
s32 btlparty_jon_jon_81_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_2[8];
s32 btlparty_jon_jon_81_04_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_3[8];
s32 btlparty_jon_jon_81_05_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_1[8];
s32 btlparty_jon_jon_81_05_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_2[8];
s32 btlparty_jon_jon_81_05_off_3[60];
__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_3[8];
s32 btlparty_jon_jon_91_01_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_1[8];
s32 btlparty_jon_jon_91_01_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_2[8];
s32 btlparty_jon_jon_91_01_off_3[36];
__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_3[8];
s32 btlparty_jon_jon_91_02_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_1[8];
s32 btlparty_jon_jon_91_02_off_2[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_2[8];
s32 btlparty_jon_jon_91_02_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_3[8];
s32 btlparty_jon_jon_91_03_off_1[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_1[8];
s32 btlparty_jon_jon_91_03_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_2[8];
s32 btlparty_jon_jon_91_03_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_3[8];
s32 btlparty_jon_jon_91_04_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_1[8];
s32 btlparty_jon_jon_91_04_off_2[36];
__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_2[8];
s32 btlparty_jon_jon_91_04_off_3[48];
__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_3[8];
s32 btlparty_jon_jon_91_05_off_1[60];
__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_1[8];
s32 btlparty_jon_jon_91_05_off_2[60];
__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_2[8];
s32 btlparty_jon_jon_91_05_off_3[60];
__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_3[8];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_test1_off[6];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_01_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_02_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_03_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_04_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_05_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_11_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_12_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_13_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_14_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_15_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_21_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_22_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_23_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_24_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_25_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_31_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_32_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_33_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_34_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_35_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_41_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_42_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_43_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_44_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_45_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_51_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_52_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_53_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_54_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_55_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_61_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_62_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_63_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_64_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_65_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_71_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_72_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_73_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_74_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_75_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_81_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_82_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_83_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_84_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_85_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_91_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_92_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_93_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_94_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_95_off[12];
__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_100_zonbaba_off[6];
s32 btlsetup_jon_tbl[901];
s32 btl_jon_setup_no_tbl[106];

__declspec(section ".data") u64 fd_battle_database_jon_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_jon_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_jon___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_jon___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_jon_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_jon___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_jon_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_battle_database_jon_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_battle_database_jon_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_battle_database_jon___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_battle_database_jon___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_battle_database_jon_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_battle_database_jon___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_battle_database_jon_one_364[] = {
    1065353216,
};

s32 jon_btlobject_data[] = {
    (s32)"B_0", 131074, 0, 0, 0, 3932160, (s32)"jon_0", 131075,
    0, 0, 0, 3932160, (s32)"B_1", 131074, 0, 0,
    0, 3932160, (s32)"jon_1", 131075, 0, 0, 0, 3932160,
    (s32)"B_2", 131074, 0, 0, 0, 3932160, (s32)"jon_2", 131075,
    0, 0, 0, 3932160, (s32)"B_6", 131074, 0, 0,
    0, 3932160, (s32)"jon_6", 131075, 0, 0, 0, 3932160,
};

s32 jon_btlstage_data[] = {
    (s32)"bti_01", (s32)"stg_00_3", 2, (s32)jon_btlobject_data, 0, 0, 0, 0,
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
    0, 0, 0, 0, 0, (s32)"bti_01", (s32)"stg_00_3", 2,
    (s32)(void*)((u8*)jon_btlobject_data + 0x30), 0, 0, 0, 0, 1677721602, 0, 0,
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
    0, 0, (s32)"bti_01", (s32)"stg_00_3", 2, (s32)(void*)((u8*)jon_btlobject_data + 0x60), 0, 0,
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
    (s32)"stg_00_3", 2, (s32)(void*)((u8*)jon_btlobject_data + 0x90), 0, 0, 0, 0, 1677721602,
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
    100, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 btlparty_jon_jon_100_01_off_1[] = {
    (s32)unit_boss_zonbaba, 16777216, 67108868, 1136033792, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_zonbaba,
};

__declspec(section ".data") s32 btlgrp_jon_jon_100_01_off_1[] = {
    1, (s32)btlparty_jon_jon_100_01_off_1, 0, 0, 100, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

__declspec(section ".data") s32 btlparty_jon_jon_01_01_off_1[] = {
    (s32)unit_yami_kuriboo, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yami_kuriboo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_1[] = {
    1, (s32)btlparty_jon_jon_01_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_01_off_2[] = {
    (s32)unit_yami_kuriboo, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yami_kuriboo, (s32)unit_hannya, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_2[] = {
    2, (s32)btlparty_jon_jon_01_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_01_off_3[] = {
    (s32)unit_yami_kuriboo, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yami_kuriboo, (s32)unit_honenoko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_01_off_3[] = {
    2, (s32)btlparty_jon_jon_01_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_02_off_1[] = {
    (s32)unit_hinnya, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hinnya, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hinnya, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hinnya, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_1[] = {
    5, (s32)btlparty_jon_jon_01_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_02_off_2[] = {
    (s32)unit_hinnya, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_yami_kuriboo, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_kuriboo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_2[] = {
    2, (s32)btlparty_jon_jon_01_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_02_off_3[] = {
    (s32)unit_hinnya, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hannya, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hinnya, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya, (s32)unit_hannya, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hinnya, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_02_off_3[] = {
    5, (s32)btlparty_jon_jon_01_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_03_off_1[] = {
    (s32)unit_hannya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
    (s32)unit_hannya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_hannya, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hannya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_1[] = {
    4, (s32)btlparty_jon_jon_01_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_03_off_2[] = {
    (s32)unit_hannya, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_yami_kuriboo, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_kuriboo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_2[] = {
    2, (s32)btlparty_jon_jon_01_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_03_off_3[] = {
    (s32)unit_hannya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_chorobon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_hannya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hannya, (s32)unit_chorobon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_03_off_3[] = {
    4, (s32)btlparty_jon_jon_01_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_04_off_1[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_honenoko, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_honenoko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_1[] = {
    4, (s32)btlparty_jon_jon_01_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_04_off_2[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_yami_kuriboo, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_kuriboo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_2[] = {
    2, (s32)btlparty_jon_jon_01_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_04_off_3[] = {
    (s32)unit_honenoko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_honenoko, (s32)unit_hinnya, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hinnya,
    (s32)unit_hinnya, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hinnya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_04_off_3[] = {
    3, (s32)btlparty_jon_jon_01_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_05_off_1[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_chorobon, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_chorobon,
    (s32)unit_chorobon, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_1[] = {
    5, (s32)btlparty_jon_jon_01_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_05_off_2[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_yami_kuriboo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_kuriboo,
    (s32)unit_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_2[] = {
    3, (s32)btlparty_jon_jon_01_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_01_05_off_3[] = {
    (s32)unit_chorobon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_honenoko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
    (s32)unit_chorobon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_chorobon, (s32)unit_honenoko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_honenoko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_01_05_off_3[] = {
    4, (s32)btlparty_jon_jon_01_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_01_off_1[] = {
    (s32)unit_yami_patakuri, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_yami_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_1[] = {
    2, (s32)btlparty_jon_jon_11_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_01_off_2[] = {
    (s32)unit_yami_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_piders, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_piders, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_2[] = {
    3, (s32)btlparty_jon_jon_11_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_01_off_3[] = {
    (s32)unit_yami_patakuri, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_sambo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
    (s32)unit_sambo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_01_off_3[] = {
    3, (s32)btlparty_jon_jon_11_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_02_off_1[] = {
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_1[] = {
    4, (s32)btlparty_jon_jon_11_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_02_off_2[] = {
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_yami_patakuri, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_2[] = {
    3, (s32)btlparty_jon_jon_11_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_02_off_3[] = {
    (s32)unit_monochrome_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_piders, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_02_off_3[] = {
    3, (s32)btlparty_jon_jon_11_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_03_off_1[] = {
    (s32)unit_sambo, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo, (s32)unit_sambo, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
    (s32)unit_sambo, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo, (s32)unit_sambo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_1[] = {
    4, (s32)btlparty_jon_jon_11_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_03_off_2[] = {
    (s32)unit_sambo, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sambo, (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_2[] = {
    2, (s32)btlparty_jon_jon_11_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_03_off_3[] = {
    (s32)unit_sambo, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo, (s32)unit_piders, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_piders, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_sambo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_03_off_3[] = {
    4, (s32)btlparty_jon_jon_11_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_04_off_1[] = {
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_1[] = {
    3, (s32)btlparty_jon_jon_11_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_04_off_2[] = {
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_sambo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_2[] = {
    3, (s32)btlparty_jon_jon_11_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_04_off_3[] = {
    (s32)unit_monochrome_kurokumorn, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_monochrome_kurokumorn, (s32)unit_yami_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_04_off_3[] = {
    2, (s32)btlparty_jon_jon_11_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_05_off_1[] = {
    (s32)unit_piders, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_piders,
    (s32)unit_piders, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_piders, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_piders,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_1[] = {
    4, (s32)btlparty_jon_jon_11_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_05_off_2[] = {
    (s32)unit_piders, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_yami_patakuri, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_2[] = {
    2, (s32)btlparty_jon_jon_11_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_11_05_off_3[] = {
    (s32)unit_piders, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_sambo, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
    (s32)unit_piders, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_piders, (s32)unit_sambo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sambo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_11_05_off_3[] = {
    4, (s32)btlparty_jon_jon_11_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_01_off_1[] = {
    (s32)unit_yami_togekuri, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_togekuri, (s32)unit_yami_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
    (s32)unit_yami_togekuri, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_togekuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_1[] = {
    3, (s32)btlparty_jon_jon_21_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_01_off_2[] = {
    (s32)unit_yami_togekuri, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_togekuri, (s32)unit_yami_togekuri, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
    (s32)unit_bomhei, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_borodo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_borodo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_2[] = {
    4, (s32)btlparty_jon_jon_21_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_01_off_3[] = {
    (s32)unit_yami_togekuri, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_togekuri, (s32)unit_yami_togekuri, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
    (s32)unit_teresa, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_01_off_3[] = {
    4, (s32)btlparty_jon_jon_21_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_02_off_1[] = {
    (s32)unit_borodo, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_borodo, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_borodo,
    (s32)unit_borodo, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_borodo, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_borodo,
    (s32)unit_borodo, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_borodo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_1[] = {
    5, (s32)btlparty_jon_jon_21_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_02_off_2[] = {
    (s32)unit_borodo, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_yami_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_2[] = {
    2, (s32)btlparty_jon_jon_21_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_02_off_3[] = {
    (s32)unit_borodo, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_teresa, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_borodo, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_teresa, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_borodo, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_borodo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_02_off_3[] = {
    5, (s32)btlparty_jon_jon_21_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_03_off_1[] = {
    (s32)unit_jyugem, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_jyugem, (s32)unit_jyugem, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_jyugem,
    (s32)unit_jyugem, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_jyugem, (s32)unit_jyugem, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_jyugem,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_1[] = {
    4, (s32)btlparty_jon_jon_21_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_21_03_off_2[] = {
    (s32)unit_jyugem, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_jyugem, (s32)unit_yami_togekuri, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_2[] = {
    2, (s32)btlparty_jon_jon_21_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_21_03_off_3[] = {
    (s32)unit_jyugem, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_jyugem, (s32)unit_bomhei, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
    (s32)unit_bomhei, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_jyugem, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_jyugem,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_03_off_3[] = {
    4, (s32)btlparty_jon_jon_21_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_21_04_off_1[] = {
    (s32)unit_bomhei, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_bomhei, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
    (s32)unit_bomhei, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_bomhei, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_bomhei,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_1[] = {
    4, (s32)btlparty_jon_jon_21_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_04_off_2[] = {
    (s32)unit_bomhei, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_yami_togekuri, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_togekuri,
    (s32)unit_bomhei, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_2[] = {
    3, (s32)btlparty_jon_jon_21_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_04_off_3[] = {
    (s32)unit_bomhei, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_teresa, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_bomhei, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bomhei, (s32)unit_teresa, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_04_off_3[] = {
    4, (s32)btlparty_jon_jon_21_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_21_05_off_1[] = {
    (s32)unit_teresa, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_teresa, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_1[] = {
    4, (s32)btlparty_jon_jon_21_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_21_05_off_2[] = {
    (s32)unit_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_yami_togekuri, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_togekuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_2[] = {
    3, (s32)btlparty_jon_jon_21_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_21_05_off_3[] = {
    (s32)unit_teresa, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_teresa, (s32)unit_teresa, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_teresa,
    (s32)unit_borodo, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_borodo, (s32)unit_borodo, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_borodo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_21_05_off_3[] = {
    4, (s32)btlparty_jon_jon_21_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_31_01_off_1[] = {
    (s32)unit_yami_noko, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yami_noko, (s32)unit_yami_noko, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_noko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_1[] = {
    2, (s32)btlparty_jon_jon_31_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_01_off_2[] = {
    (s32)unit_yami_noko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_noko, (s32)unit_patamet, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
    (s32)unit_patamet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_2[] = {
    3, (s32)btlparty_jon_jon_31_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_01_off_3[] = {
    (s32)unit_yami_noko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_noko, (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_01_off_3[] = {
    3, (s32)btlparty_jon_jon_31_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_02_off_1[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_1[] = {
    3, (s32)btlparty_jon_jon_31_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_02_off_2[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_ura_noko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_2[] = {
    3, (s32)btlparty_jon_jon_31_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_02_off_3[] = {
    (s32)unit_hyper_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_sinemon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
    (s32)unit_patamet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_02_off_3[] = {
    3, (s32)btlparty_jon_jon_31_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_03_off_1[] = {
    (s32)unit_patamet, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_patamet, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
    (s32)unit_patamet, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_patamet, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_1[] = {
    4, (s32)btlparty_jon_jon_31_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_03_off_2[] = {
    (s32)unit_patamet, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_ura_noko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
    (s32)unit_patamet, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_ura_noko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_2[] = {
    4, (s32)btlparty_jon_jon_31_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_03_off_3[] = {
    (s32)unit_patamet, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patamet, (s32)unit_flower_chorobon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_03_off_3[] = {
    2, (s32)btlparty_jon_jon_31_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_04_off_1[] = {
    (s32)unit_ura_noko, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko, (s32)unit_ura_noko, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
    (s32)unit_ura_noko, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko, (s32)unit_ura_noko, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_1[] = {
    4, (s32)btlparty_jon_jon_31_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_04_off_2[] = {
    (s32)unit_ura_noko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko, (s32)unit_yami_noko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_noko,
    (s32)unit_ura_noko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_2[] = {
    3, (s32)btlparty_jon_jon_31_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_04_off_3[] = {
    (s32)unit_ura_noko, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ura_noko, (s32)unit_ura_noko, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ura_noko,
    (s32)unit_patamet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patamet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_04_off_3[] = {
    3, (s32)btlparty_jon_jon_31_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_05_off_1[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_flower_chorobon, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_1[] = {
    5, (s32)btlparty_jon_jon_31_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_05_off_2[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_flower_chorobon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_flower_chorobon,
    (s32)unit_yami_noko, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_noko,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_2[] = {
    3, (s32)btlparty_jon_jon_31_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_31_05_off_3[] = {
    (s32)unit_flower_chorobon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_flower_chorobon, (s32)unit_hyper_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_sinemon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_31_05_off_3[] = {
    2, (s32)btlparty_jon_jon_31_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_01_off_1[] = {
    (s32)unit_yami_pata, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_yami_pata, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
    (s32)unit_yami_pata, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_yami_pata, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_1[] = {
    4, (s32)btlparty_jon_jon_41_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_01_off_2[] = {
    (s32)unit_yami_pata, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_yami_pata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
    (s32)unit_patatogemet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_2[] = {
    3, (s32)btlparty_jon_jon_41_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_01_off_3[] = {
    (s32)unit_yami_pata, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri, (s32)unit_yami_pata, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
    (s32)unit_heavy_bom, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_01_off_3[] = {
    3, (s32)btlparty_jon_jon_41_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_02_off_1[] = {
    (s32)unit_heavy_bom, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
    (s32)unit_heavy_bom, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_1[] = {
    4, (s32)btlparty_jon_jon_41_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_02_off_2[] = {
    (s32)unit_heavy_bom, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_heavy_bom, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_2[] = {
    2, (s32)btlparty_jon_jon_41_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_02_off_3[] = {
    (s32)unit_heavy_bom, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_heavy_bom, (s32)unit_sambo_mummy, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_patatogemet, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_02_off_3[] = {
    3, (s32)btlparty_jon_jon_41_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_03_off_1[] = {
    (s32)unit_bubble, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
    (s32)unit_bubble, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bubble,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_1[] = {
    3, (s32)btlparty_jon_jon_41_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_41_03_off_2[] = {
    (s32)unit_bubble, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
    (s32)unit_yami_pata, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_2[] = {
    3, (s32)btlparty_jon_jon_41_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_41_03_off_3[] = {
    (s32)unit_bubble, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_bubble, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_heavy_bom, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_heavy_bom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_03_off_3[] = {
    4, (s32)btlparty_jon_jon_41_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_41_04_off_1[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_sambo_mummy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sambo_mummy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_1[] = {
    4, (s32)btlparty_jon_jon_41_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_04_off_2[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_patatogemet, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
    (s32)unit_sambo_mummy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_patatogemet, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_2[] = {
    4, (s32)btlparty_jon_jon_41_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_04_off_3[] = {
    (s32)unit_sambo_mummy, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_sambo_mummy, (s32)unit_yami_pata, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yami_patakuri,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_04_off_3[] = {
    2, (s32)btlparty_jon_jon_41_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_05_off_1[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_1[] = {
    2, (s32)btlparty_jon_jon_41_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_05_off_2[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
    (s32)unit_patatogemet, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_2[] = {
    4, (s32)btlparty_jon_jon_41_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_41_05_off_3[] = {
    (s32)unit_patatogemet, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_patatogemet, (s32)unit_patatogemet, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_patatogemet,
    (s32)unit_bubble, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bubble, (s32)unit_bubble, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_bubble,
};

__declspec(section ".data") s32 btlgrp_jon_jon_41_05_off_3[] = {
    4, (s32)btlparty_jon_jon_41_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_01_off_1[] = {
    (s32)unit_badge_borodo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_badge_borodo, (s32)unit_badge_borodo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_badge_borodo,
    (s32)unit_badge_borodo, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_badge_borodo,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_1[] = {
    3, (s32)btlparty_jon_jon_51_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_01_off_2[] = {
    (s32)unit_badge_borodo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_badge_borodo, (s32)unit_badge_borodo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_badge_borodo,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_2[] = {
    3, (s32)btlparty_jon_jon_51_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_01_off_3[] = {
    (s32)unit_badge_borodo, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_badge_borodo, (s32)unit_badge_borodo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_badge_borodo,
    (s32)unit_purple_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_01_off_3[] = {
    3, (s32)btlparty_jon_jon_51_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_02_off_1[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_bllizard, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
    (s32)unit_bllizard, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_bllizard, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_1[] = {
    4, (s32)btlparty_jon_jon_51_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_02_off_2[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_purple_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_2[] = {
    3, (s32)btlparty_jon_jon_51_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_02_off_3[] = {
    (s32)unit_bllizard, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard, (s32)unit_sinemon, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_02_off_3[] = {
    2, (s32)btlparty_jon_jon_51_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_03_off_1[] = {
    (s32)unit_purple_teresa, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_1[] = {
    4, (s32)btlparty_jon_jon_51_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_51_03_off_2[] = {
    (s32)unit_purple_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_badge_borodo, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_badge_borodo,
    (s32)unit_purple_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_2[] = {
    3, (s32)btlparty_jon_jon_51_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_51_03_off_3[] = {
    (s32)unit_purple_teresa, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa, (s32)unit_purple_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_burst_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_03_off_3[] = {
    3, (s32)btlparty_jon_jon_51_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_51_04_off_1[] = {
    (s32)unit_burst_wanwan, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan, (s32)unit_burst_wanwan, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_burst_wanwan,
    (s32)unit_burst_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_1[] = {
    3, (s32)btlparty_jon_jon_51_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_04_off_2[] = {
    (s32)unit_burst_wanwan, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan, (s32)unit_purple_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_burst_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_2[] = {
    3, (s32)btlparty_jon_jon_51_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_04_off_3[] = {
    (s32)unit_burst_wanwan, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan, (s32)unit_bllizard, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_bllizard,
    (s32)unit_bllizard, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_bllizard,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_04_off_3[] = {
    3, (s32)btlparty_jon_jon_51_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_05_off_1[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_sinemon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_1[] = {
    4, (s32)btlparty_jon_jon_51_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_05_off_2[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_sinemon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_sinemon,
    (s32)unit_burst_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_burst_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_2[] = {
    3, (s32)btlparty_jon_jon_51_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_51_05_off_3[] = {
    (s32)unit_sinemon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_sinemon, (s32)unit_purple_teresa, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_purple_teresa,
    (s32)unit_purple_teresa, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_purple_teresa,
};

__declspec(section ".data") s32 btlgrp_jon_jon_51_05_off_3[] = {
    3, (s32)btlparty_jon_jon_51_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_01_off_1[] = {
    (s32)unit_hyper_jyugem, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_jyugem, (s32)unit_hyper_jyugem, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_jyugem,
    (s32)unit_hyper_jyugem, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_jyugem,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_1[] = {
    3, (s32)btlparty_jon_jon_61_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_01_off_2[] = {
    (s32)unit_hyper_jyugem, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_jyugem, (s32)unit_hyper_jyugem, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_jyugem,
    (s32)unit_dark_keeper, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dark_keeper,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_2[] = {
    3, (s32)btlparty_jon_jon_61_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_01_off_3[] = {
    (s32)unit_hyper_jyugem, 16777216, 67108868, 1116471296, 1109393408, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_jyugem, (s32)unit_super_mahorn, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_01_off_3[] = {
    2, (s32)btlparty_jon_jon_61_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_02_off_1[] = {
    (s32)unit_karon, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_karon, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_karon, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_karon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_1[] = {
    4, (s32)btlparty_jon_jon_61_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_02_off_2[] = {
    (s32)unit_karon, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_dark_keeper, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_dark_keeper,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_2[] = {
    2, (s32)btlparty_jon_jon_61_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_02_off_3[] = {
    (s32)unit_karon, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_karon, (s32)unit_ice_pakkun, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_ice_pakkun, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_02_off_3[] = {
    3, (s32)btlparty_jon_jon_61_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_03_off_1[] = {
    (s32)unit_super_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_super_mahorn, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_super_mahorn,
    (s32)unit_super_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_1[] = {
    3, (s32)btlparty_jon_jon_61_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_03_off_2[] = {
    (s32)unit_super_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_dark_keeper, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_dark_keeper,
    (s32)unit_super_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_2[] = {
    3, (s32)btlparty_jon_jon_61_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_03_off_3[] = {
    (s32)unit_super_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_super_mahorn, (s32)unit_karon, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_karon,
    (s32)unit_karon, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_karon,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_03_off_3[] = {
    3, (s32)btlparty_jon_jon_61_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_04_off_1[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
    (s32)unit_ice_pakkun, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_ice_pakkun, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_ice_pakkun,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_1[] = {
    4, (s32)btlparty_jon_jon_61_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_04_off_2[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_hyper_jyugem, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_hyper_jyugem,
    (s32)unit_hyper_jyugem, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hyper_jyugem,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_2[] = {
    3, (s32)btlparty_jon_jon_61_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_04_off_3[] = {
    (s32)unit_ice_pakkun, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_ice_pakkun, (s32)unit_dark_keeper, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_dark_keeper,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_04_off_3[] = {
    2, (s32)btlparty_jon_jon_61_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_61_05_off_1[] = {
    (s32)unit_dark_keeper, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_dark_keeper, (s32)unit_dark_keeper, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_dark_keeper,
    (s32)unit_dark_keeper, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dark_keeper,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_1[] = {
    3, (s32)btlparty_jon_jon_61_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_05_off_2[] = {
    (s32)unit_dark_keeper, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_dark_keeper, (s32)unit_hyper_jyugem, 16777216, 67108868, 1121714176,
    1109393408, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hyper_jyugem,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_2[] = {
    2, (s32)btlparty_jon_jon_61_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_61_05_off_3[] = {
    (s32)unit_dark_keeper, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_dark_keeper, (s32)unit_dark_keeper, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_dark_keeper,
};

__declspec(section ".data") s32 btlgrp_jon_jon_61_05_off_3[] = {
    2, (s32)btlparty_jon_jon_61_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_01_off_1[] = {
    (s32)unit_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn, (s32)unit_mahorn, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_mahorn,
    (s32)unit_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_1[] = {
    3, (s32)btlparty_jon_jon_71_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_01_off_2[] = {
    (s32)unit_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn, (s32)unit_togenoko_ace, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
    (s32)unit_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_2[] = {
    3, (s32)btlparty_jon_jon_71_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_01_off_3[] = {
    (s32)unit_mahorn, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn, (s32)unit_wanwan, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
    (s32)unit_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_01_off_3[] = {
    3, (s32)btlparty_jon_jon_71_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_02_off_1[] = {
    (s32)unit_togenoko_ace, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko_ace, (s32)unit_togenoko_ace, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
    (s32)unit_togenoko_ace, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko_ace,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_1[] = {
    3, (s32)btlparty_jon_jon_71_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_02_off_2[] = {
    (s32)unit_togenoko_ace, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko_ace, (s32)unit_wanwan, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
    (s32)unit_wanwan, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_2[] = {
    3, (s32)btlparty_jon_jon_71_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_02_off_3[] = {
    (s32)unit_togenoko_ace, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko_ace, (s32)unit_togenoko_ace, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
    (s32)unit_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_02_off_3[] = {
    3, (s32)btlparty_jon_jon_71_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default2, 5,
};

s32 btlparty_jon_jon_71_03_off_1[] = {
    (s32)unit_phantom, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_phantom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_1[] = {
    5, (s32)btlparty_jon_jon_71_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_71_03_off_2[] = {
    (s32)unit_phantom, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_phantom, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_phantom,
    (s32)unit_phantom, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_mahorn, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_2[] = {
    4, (s32)btlparty_jon_jon_71_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_71_03_off_3[] = {
    (s32)unit_phantom, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_phantom, (s32)unit_basabasa_chururu, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_wanwan, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_togenoko_ace, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_03_off_3[] = {
    4, (s32)btlparty_jon_jon_71_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_71_04_off_1[] = {
    (s32)unit_basabasa_chururu, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_basabasa_chururu, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu, 16777216, 67108868, 1125515264,
    1124204544, 1101004800, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_1[] = {
    4, (s32)btlparty_jon_jon_71_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_04_off_2[] = {
    (s32)unit_basabasa_chururu, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_basabasa_chururu, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_chururu,
    (s32)unit_mahorn, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn, (s32)unit_mahorn, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_2[] = {
    4, (s32)btlparty_jon_jon_71_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_04_off_3[] = {
    (s32)unit_basabasa_chururu, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_togenoko_ace, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
    (s32)unit_basabasa_chururu, 16777216, 67108868, 1121714176, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_chururu, (s32)unit_togenoko_ace, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_04_off_3[] = {
    4, (s32)btlparty_jon_jon_71_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default2, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_05_off_1[] = {
    (s32)unit_wanwan, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
    (s32)unit_wanwan, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_1[] = {
    4, (s32)btlparty_jon_jon_71_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_05_off_2[] = {
    (s32)unit_wanwan, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_togenoko_ace, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_togenoko_ace,
    (s32)unit_togenoko_ace, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_togenoko_ace,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_2[] = {
    3, (s32)btlparty_jon_jon_71_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_71_05_off_3[] = {
    (s32)unit_wanwan, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_wanwan, (s32)unit_wanwan, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_wanwan,
    (s32)unit_mahorn, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn,
};

__declspec(section ".data") s32 btlgrp_jon_jon_71_05_off_3[] = {
    3, (s32)btlparty_jon_jon_71_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_01_off_1[] = {
    (s32)unit_hennya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_1[] = {
    4, (s32)btlparty_jon_jon_81_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_01_off_2[] = {
    (s32)unit_hennya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_churantalar, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
    (s32)unit_hennya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_churantalar, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_2[] = {
    4, (s32)btlparty_jon_jon_81_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_01_off_3[] = {
    (s32)unit_hennya, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_pakkun_flower, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pakkun_flower,
    (s32)unit_yamitogedaruma, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yamitogedaruma,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_01_off_3[] = {
    3, (s32)btlparty_jon_jon_81_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_02_off_1[] = {
    (s32)unit_yamitogedaruma, 16777216, 67108868, 1116471296, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_yamitogedaruma, (s32)unit_yamitogedaruma, 16777216, 67108868, 1121714176,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_yamitogedaruma,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_1[] = {
    2, (s32)btlparty_jon_jon_81_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_81_02_off_2[] = {
    (s32)unit_yamitogedaruma, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yamitogedaruma, (s32)unit_churantalar, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
    (s32)unit_churantalar, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar, (s32)unit_churantalar, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_2[] = {
    4, (s32)btlparty_jon_jon_81_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_81_02_off_3[] = {
    (s32)unit_yamitogedaruma, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_yamitogedaruma, (s32)unit_yamitogedaruma, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yamitogedaruma,
    (s32)unit_hennya, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_02_off_3[] = {
    3, (s32)btlparty_jon_jon_81_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_81_03_off_1[] = {
    (s32)unit_churantalar, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar, (s32)unit_churantalar, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
    (s32)unit_churantalar, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar, (s32)unit_churantalar, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_1[] = {
    4, (s32)btlparty_jon_jon_81_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_81_03_off_2[] = {
    (s32)unit_churantalar, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar, (s32)unit_pakkun_flower, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pakkun_flower,
    (s32)unit_churantalar, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_2[] = {
    3, (s32)btlparty_jon_jon_81_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_81_03_off_3[] = {
    (s32)unit_churantalar, 16777216, 67108868, 1112014848, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_churantalar, (s32)unit_churantalar, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_churantalar,
    (s32)unit_yamitogedaruma, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_yamitogedaruma,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_03_off_3[] = {
    3, (s32)btlparty_jon_jon_81_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_81_04_off_1[] = {
    (s32)unit_pakkun_flower, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pakkun_flower, (s32)unit_pakkun_flower, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_pakkun_flower,
    (s32)unit_pakkun_flower, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pakkun_flower, (s32)unit_pakkun_flower, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_pakkun_flower,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_1[] = {
    4, (s32)btlparty_jon_jon_81_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default5, 5,
};

s32 btlparty_jon_jon_81_04_off_2[] = {
    (s32)unit_pakkun_flower, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pakkun_flower, (s32)unit_yamitogedaruma, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_yamitogedaruma,
    (s32)unit_pakkun_flower, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_pakkun_flower,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_2[] = {
    3, (s32)btlparty_jon_jon_81_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default5, 5,
};

s32 btlparty_jon_jon_81_04_off_3[] = {
    (s32)unit_pakkun_flower, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_pakkun_flower, (s32)unit_hennya, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_04_off_3[] = {
    4, (s32)btlparty_jon_jon_81_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default, (s32)battle_flower_drop_param_default5, 5,
};

s32 btlparty_jon_jon_81_05_off_1[] = {
    (s32)unit_hennya, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_1[] = {
    4, (s32)btlparty_jon_jon_81_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_05_off_2[] = {
    (s32)unit_hennya, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_2[] = {
    3, (s32)btlparty_jon_jon_81_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_81_05_off_3[] = {
    (s32)unit_hennya, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_hennya, (s32)unit_hennya, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_hennya,
    (s32)unit_hennya, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_hennya,
};

__declspec(section ".data") s32 btlgrp_jon_jon_81_05_off_3[] = {
    5, (s32)btlparty_jon_jon_81_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_01_off_1[] = {
    (s32)unit_mahorn_custom, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom, (s32)unit_mahorn_custom, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_mahorn_custom,
    (s32)unit_mahorn_custom, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom, (s32)unit_mahorn_custom, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_mahorn_custom,
    (s32)unit_mahorn_custom, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_1[] = {
    5, (s32)btlparty_jon_jon_91_01_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_91_01_off_2[] = {
    (s32)unit_mahorn_custom, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom, (s32)unit_dokugassun, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
    (s32)unit_dokugassun, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_2[] = {
    3, (s32)btlparty_jon_jon_91_01_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_91_01_off_3[] = {
    (s32)unit_mahorn_custom, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom, (s32)unit_mahorn_custom, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_mahorn_custom,
    (s32)unit_basabasa_green, 16777216, 67108868, 1124204544, 1124204544, 1092616192, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_01_off_3[] = {
    3, (s32)btlparty_jon_jon_91_01_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default4, 5,
};

s32 btlparty_jon_jon_91_02_off_1[] = {
    (s32)unit_dokugassun, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_dokugassun, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
    (s32)unit_dokugassun, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_dokugassun, 16777216, 67108868, 1125515264,
    1109393408, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_1[] = {
    4, (s32)btlparty_jon_jon_91_02_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_91_02_off_2[] = {
    (s32)unit_dokugassun, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_dokugassun, 16777216, 67108868, 1116471296,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
    (s32)unit_dokugassun, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_giant_bomb, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_giant_bomb,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_2[] = {
    4, (s32)btlparty_jon_jon_91_02_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_91_02_off_3[] = {
    (s32)unit_dokugassun, 16777216, 67108868, 1106247680, 1109393408, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_basabasa_green, 16777216, 67108868, 1116471296,
    1124204544, 0, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_green,
    (s32)unit_dokugassun, 16777216, 67108868, 1121714176, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun, (s32)unit_twinkling_pansy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_02_off_3[] = {
    4, (s32)btlparty_jon_jon_91_02_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default3, 5,
};

s32 btlparty_jon_jon_91_03_off_1[] = {
    (s32)unit_giant_bomb, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_giant_bomb, (s32)unit_giant_bomb, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_giant_bomb,
    (s32)unit_giant_bomb, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_giant_bomb, (s32)unit_giant_bomb, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_giant_bomb,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_1[] = {
    4, (s32)btlparty_jon_jon_91_03_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default5, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_03_off_2[] = {
    (s32)unit_giant_bomb, 16777216, 67108868, 1112014848, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_giant_bomb, (s32)unit_giant_bomb, 16777216, 67108868, 1119092736,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_giant_bomb,
    (s32)unit_mahorn_custom, 16777216, 67108868, 1124204544, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_mahorn_custom,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_2[] = {
    3, (s32)btlparty_jon_jon_91_03_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default5, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_03_off_3[] = {
    (s32)unit_giant_bomb, 16777216, 67108868, 1106247680, 0, -1054867456, 0, 0,
    0, 0, 0, (s32)battle_item_giant_bomb, (s32)unit_giant_bomb, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_giant_bomb,
    (s32)unit_giant_bomb, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_giant_bomb, (s32)unit_twinkling_pansy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_03_off_3[] = {
    4, (s32)btlparty_jon_jon_91_03_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default5, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_04_off_1[] = {
    (s32)unit_basabasa_green, 16777216, 67108868, 1092616192, 1124204544, -1046478848, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green, (s32)unit_basabasa_green, 16777216, 67108868, 1112014848,
    1124204544, -1054867456, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_green,
    (s32)unit_basabasa_green, 16777216, 67108868, 1119092736, 1124204544, 0, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green, (s32)unit_basabasa_green, 16777216, 67108868, 1124204544,
    1124204544, 1092616192, 0, 1, 0, 0, 0, (s32)battle_item_basabasa_green,
    (s32)unit_basabasa_green, 16777216, 67108868, 1126825984, 1124204544, 1101004800, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_1[] = {
    5, (s32)btlparty_jon_jon_91_04_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_04_off_2[] = {
    (s32)unit_basabasa_green, 16777216, 67108868, 1112014848, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green, (s32)unit_dokugassun, 16777216, 67108868, 1119092736,
    1109393408, 0, 0, 0, 0, 0, 0, (s32)battle_item_dokugassun,
    (s32)unit_dokugassun, 16777216, 67108868, 1124204544, 1109393408, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_dokugassun,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_2[] = {
    3, (s32)btlparty_jon_jon_91_04_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_04_off_3[] = {
    (s32)unit_basabasa_green, 16777216, 67108868, 1106247680, 1124204544, -1054867456, 0, 1,
    0, 0, 0, (s32)battle_item_basabasa_green, (s32)unit_mahorn_custom, 16777216, 67108868, 1116471296,
    0, 0, 0, 0, 0, 0, 0, (s32)battle_item_mahorn_custom,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1121714176, 0, 1092616192, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1125515264,
    0, 1101004800, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_04_off_3[] = {
    4, (s32)btlparty_jon_jon_91_04_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default4, (s32)battle_flower_drop_param_default, 5,
};

s32 btlparty_jon_jon_91_05_off_1[] = {
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_1[] = {
    5, (s32)btlparty_jon_jon_91_05_off_1, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default5, 5,
};

s32 btlparty_jon_jon_91_05_off_2[] = {
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_2[] = {
    5, (s32)btlparty_jon_jon_91_05_off_2, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default5, 5,
};

s32 btlparty_jon_jon_91_05_off_3[] = {
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1092616192, 0, -1046478848, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1112014848,
    0, -1054867456, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1119092736, 0, 0, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy, (s32)unit_twinkling_pansy, 16777216, 67108868, 1124204544,
    0, 1092616192, 0, 0, 0, 0, 0, (s32)battle_item_twinkling_pansy,
    (s32)unit_twinkling_pansy, 16777216, 67108868, 1126825984, 0, 1101004800, 0, 0,
    0, 0, 0, (s32)battle_item_twinkling_pansy,
};

__declspec(section ".data") s32 btlgrp_jon_jon_91_05_off_3[] = {
    5, (s32)btlparty_jon_jon_91_05_off_3, 20, 20, 60, (s32)battle_heart_drop_param_default3, (s32)battle_flower_drop_param_default5, 5,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_test1_off[] = {
    50, (s32)btlgrp_jon_jon_01_01_off_1, (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_01_off[] = {
    10, (s32)btlgrp_jon_jon_01_01_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_01_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_01_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_02_off[] = {
    10, (s32)btlgrp_jon_jon_01_02_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_02_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_02_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_03_off[] = {
    10, (s32)btlgrp_jon_jon_01_03_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_03_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_03_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_04_off[] = {
    10, (s32)btlgrp_jon_jon_01_04_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_04_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_04_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_05_off[] = {
    10, (s32)btlgrp_jon_jon_01_05_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_05_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_01_05_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_11_off[] = {
    10, (s32)btlgrp_jon_jon_11_01_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_01_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_01_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_12_off[] = {
    10, (s32)btlgrp_jon_jon_11_02_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_02_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_02_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_13_off[] = {
    10, (s32)btlgrp_jon_jon_11_03_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_03_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_03_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_14_off[] = {
    10, (s32)btlgrp_jon_jon_11_04_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_04_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_04_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_15_off[] = {
    10, (s32)btlgrp_jon_jon_11_05_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_05_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_11_05_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_21_off[] = {
    10, (s32)btlgrp_jon_jon_21_01_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_01_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_01_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_22_off[] = {
    10, (s32)btlgrp_jon_jon_21_02_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_02_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_02_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_23_off[] = {
    10, (s32)btlgrp_jon_jon_21_03_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_03_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_03_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_24_off[] = {
    10, (s32)btlgrp_jon_jon_21_04_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_04_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_04_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_25_off[] = {
    10, (s32)btlgrp_jon_jon_21_05_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_05_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_21_05_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_31_off[] = {
    10, (s32)btlgrp_jon_jon_31_01_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_01_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_01_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_32_off[] = {
    10, (s32)btlgrp_jon_jon_31_02_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_02_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_02_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_33_off[] = {
    10, (s32)btlgrp_jon_jon_31_03_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_03_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_03_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_34_off[] = {
    10, (s32)btlgrp_jon_jon_31_04_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_04_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_04_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_35_off[] = {
    10, (s32)btlgrp_jon_jon_31_05_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_05_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_31_05_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_41_off[] = {
    10, (s32)btlgrp_jon_jon_41_01_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_01_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_01_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_42_off[] = {
    10, (s32)btlgrp_jon_jon_41_02_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_02_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_02_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_43_off[] = {
    10, (s32)btlgrp_jon_jon_41_03_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_03_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_03_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_44_off[] = {
    10, (s32)btlgrp_jon_jon_41_04_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_04_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_04_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_45_off[] = {
    10, (s32)btlgrp_jon_jon_41_05_off_1, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_05_off_2, (s32)jon_btlstage_data, 10, (s32)btlgrp_jon_jon_41_05_off_3,
    (s32)jon_btlstage_data, 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_51_off[] = {
    10, (s32)btlgrp_jon_jon_51_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_01_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_01_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_52_off[] = {
    10, (s32)btlgrp_jon_jon_51_02_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_02_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_02_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_53_off[] = {
    10, (s32)btlgrp_jon_jon_51_03_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_03_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_03_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_54_off[] = {
    10, (s32)btlgrp_jon_jon_51_04_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_04_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_04_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_55_off[] = {
    10, (s32)btlgrp_jon_jon_51_05_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_05_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_51_05_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_61_off[] = {
    10, (s32)btlgrp_jon_jon_61_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_01_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_01_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_62_off[] = {
    10, (s32)btlgrp_jon_jon_61_02_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_02_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_02_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_63_off[] = {
    10, (s32)btlgrp_jon_jon_61_03_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_03_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_03_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_64_off[] = {
    10, (s32)btlgrp_jon_jon_61_04_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_04_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_04_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_65_off[] = {
    10, (s32)btlgrp_jon_jon_61_05_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_05_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_61_05_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_71_off[] = {
    10, (s32)btlgrp_jon_jon_71_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_01_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_01_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_72_off[] = {
    10, (s32)btlgrp_jon_jon_71_02_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_02_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_02_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_73_off[] = {
    10, (s32)btlgrp_jon_jon_71_03_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_03_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_03_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_74_off[] = {
    10, (s32)btlgrp_jon_jon_71_04_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_04_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_04_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_75_off[] = {
    10, (s32)btlgrp_jon_jon_71_05_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_05_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_71_05_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_81_off[] = {
    10, (s32)btlgrp_jon_jon_81_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_01_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_01_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_82_off[] = {
    10, (s32)btlgrp_jon_jon_81_02_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_02_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_02_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_83_off[] = {
    10, (s32)btlgrp_jon_jon_81_03_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_03_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_03_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_84_off[] = {
    10, (s32)btlgrp_jon_jon_81_04_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_04_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_04_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_85_off[] = {
    10, (s32)btlgrp_jon_jon_81_05_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_05_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 10, (s32)btlgrp_jon_jon_81_05_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x1B4), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_91_off[] = {
    10, (s32)btlgrp_jon_jon_91_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_01_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_01_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_92_off[] = {
    10, (s32)btlgrp_jon_jon_91_02_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_02_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_02_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_93_off[] = {
    10, (s32)btlgrp_jon_jon_91_03_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_03_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_03_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_94_off[] = {
    10, (s32)btlgrp_jon_jon_91_04_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_04_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_04_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_95_off[] = {
    10, (s32)btlgrp_jon_jon_91_05_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_05_off_2, (s32)(void*)((u8*)jon_btlstage_data + 0x368), 10, (s32)btlgrp_jon_jon_91_05_off_3,
    (s32)(void*)((u8*)jon_btlstage_data + 0x368), 0, 0, 0,
};

__declspec(section ".data") s32 btlgrpsel_jon_btlno_jon_100_zonbaba_off[] = {
    10, (s32)btlgrp_jon_jon_100_01_off_1, (s32)(void*)((u8*)jon_btlstage_data + 0x51C), 0, 0, 0,
};

s32 btlsetup_jon_tbl[] = {
    (s32)/*"マップstg_00_3"*/"\x83\x7D\x83\x62\x83\x76\x73\x74\x67\x5F\x30\x30\x5F\x33", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_test1_off, 268435456, 0,
    16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミクリボー"*/"\x83\x84\x83\x7E\x83\x4E\x83\x8A\x83\x7B\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_01_off, 268435456,
    0, 84213760, 0, 84215045, 0, 84213760, 168427520, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヒンニャー"*/"\x83\x71\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_02_off,
    268435456, 0, 84213760, 0, 84215045, 0, 84213760, 84213760,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ハンニャー"*/"\x83\x6E\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_03_off, 268435456, 0, 84213760, 0, 84215045, 0, 84213760,
    84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ホネノコ"*/"\x83\x7A\x83\x6C\x83\x6D\x83\x52", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_04_off, 268435456, 0, 84213760, 0, 168428805, 0,
    84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"チョロボン"*/"\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_05_off, 268435456, 0, 84213760, 0, 84215045,
    0, 84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミパタクリ"*/"\x83\x84\x83\x7E\x83\x70\x83\x5E\x83\x4E\x83\x8A", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_11_off, 268435456, 0, 84215045, 0,
    84215045, 0, 84213760, 168427520, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"モノクロシンエモン"*/"\x83\x82\x83\x6D\x83\x4E\x83\x8D\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_12_off, 268435456, 0, 84215045,
    0, 84215045, 0, 84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"サンボ"*/"\x83\x54\x83\x93\x83\x7B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_13_off, 268435456, 0,
    84215045, 0, 84215045, 0, 84213760, 84213760, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"モノクロクロクモーン"*/"\x83\x82\x83\x6D\x83\x4E\x83\x8D\x83\x4E\x83\x8D\x83\x4E\x83\x82\x81\x5B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_14_off, 268435456,
    0, 84215045, 0, 84215045, 0, 84213760, 84213760, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"パイダース"*/"\x83\x70\x83\x43\x83\x5F\x81\x5B\x83\x58", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_15_off,
    268435456, 0, 84215045, 0, 84215045, 0, 84213760, 84213760,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミトゲクリ"*/"\x83\x84\x83\x7E\x83\x67\x83\x51\x83\x4E\x83\x8A", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_21_off, 268435456, 0, 84215045, 0, 84215045, 0, 84213760,
    168427520, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ボロドー"*/"\x83\x7B\x83\x8D\x83\x68\x81\x5B", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_22_off, 268435456, 0, 84215045, 0, 84215045, 0,
    84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ジュゲム"*/"\x83\x57\x83\x85\x83\x51\x83\x80", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_23_off, 268435456, 0, 84215045, 0, 84215045,
    0, 84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ボムへい"*/"\x83\x7B\x83\x80\x82\xD6\x82\xA2", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_24_off, 268435456, 0, 84215045, 0,
    84215045, 0, 84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"テレサ"*/"\x83\x65\x83\x8C\x83\x54",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_25_off, 268435456, 0, 84215045,
    168427520, 84215045, 0, 84213760, 84213760, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"ヤミノコノコ"*/"\x83\x84\x83\x7E\x83\x6D\x83\x52\x83\x6D\x83\x52", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_31_off, 268435456, 0,
    67372036, 67371008, 67372036, 67372036, 168427520, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ハイパーシンエモン"*/"\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_32_off, 268435456,
    0, 67372036, 67371008, 67372036, 67372036, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"パタメット"*/"\x83\x70\x83\x5E\x83\x81\x83\x62\x83\x67", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_33_off,
    268435456, 0, 67372036, 67371008, 67372036, 67372036, 67371008, 67372036,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ウラノコ"*/"\x83\x45\x83\x89\x83\x6D\x83\x52", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_34_off, 268435456, 0, 67372036, 67371008, 67372036, 67372036, 168427520,
    67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"フラワーチョロボン"*/"\x83\x74\x83\x89\x83\x8F\x81\x5B\x83\x60\x83\x87\x83\x8D\x83\x7B\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_35_off, 268435456, 0, 67372036, 67371008, 67372036, 67372036,
    67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミパタパタ"*/"\x83\x84\x83\x7E\x83\x70\x83\x5E\x83\x70\x83\x5E", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_41_off, 268435456, 0, 67372036, 67371008, 67372036,
    67372036, 168427520, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヘビーボム"*/"\x83\x77\x83\x72\x81\x5B\x83\x7B\x83\x80", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_42_off, 268435456, 0, 67372036, 67371008,
    67372036, 67372036, 67373578, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バブル"*/"\x83\x6F\x83\x75\x83\x8B",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_43_off, 268435456, 0, 67372036,
    67371008, 67372036, 67372036, 67371008, 67372036, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"サンボマミー"*/"\x83\x54\x83\x93\x83\x7B\x83\x7D\x83\x7E\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_44_off, 268435456, 0,
    67372036, 67371008, 67372036, 67372036, 67371008, 67372036, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"パタトゲメット"*/"\x83\x70\x83\x5E\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_45_off, 268435456,
    0, 67372036, 67371008, 67372036, 67372036, 67371008, 67372036, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バッジボロドー"*/"\x83\x6F\x83\x62\x83\x57\x83\x7B\x83\x8D\x83\x68\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_51_off,
    268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ブリザード"*/"\x83\x75\x83\x8A\x83\x55\x81\x5B\x83\x68", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_52_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"パープルテレサ"*/"\x83\x70\x81\x5B\x83\x76\x83\x8B\x83\x65\x83\x8C\x83\x54", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_53_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バーストワンワン"*/"\x83\x6F\x81\x5B\x83\x58\x83\x67\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_54_off, 268435456, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"シンエモン"*/"\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_55_off, 268435456, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ハイパージュゲム"*/"\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x57\x83\x85\x83\x51\x83\x80",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_61_off, 268435456, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"カロン"*/"\x83\x4A\x83\x8D\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_62_off, 268435456, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"スーパーマホーン"*/"\x83\x58\x81\x5B\x83\x70\x81\x5B\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_63_off, 268435456,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"アイスパックン"*/"\x83\x41\x83\x43\x83\x58\x83\x70\x83\x62\x83\x4E\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_64_off,
    268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ダークキーパー"*/"\x83\x5F\x81\x5B\x83\x4E\x83\x4C\x81\x5B\x83\x70\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_65_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マホーン"*/"\x83\x7D\x83\x7A\x81\x5B\x83\x93", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_71_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"トゲノコエース"*/"\x83\x67\x83\x51\x83\x6D\x83\x52\x83\x47\x81\x5B\x83\x58", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_72_off, 268435456, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ファントム"*/"\x83\x74\x83\x40\x83\x93\x83\x67\x83\x80", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_73_off, 268435456, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バサバサチュルル"*/"\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x60\x83\x85\x83\x8B\x83\x8B",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_74_off, 268435456, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"ワンワン"*/"\x83\x8F\x83\x93\x83\x8F\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_75_off, 268435456, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヘンニャー"*/"\x83\x77\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_81_off, 268435456,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヤミトゲダルマー"*/"\x83\x84\x83\x7E\x83\x67\x83\x51\x83\x5F\x83\x8B\x83\x7D\x81\x5B", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_82_off,
    268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"チュランタラー"*/"\x83\x60\x83\x85\x83\x89\x83\x93\x83\x5E\x83\x89\x81\x5B", 0, 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_83_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"パックンフラワー"*/"\x83\x70\x83\x62\x83\x4E\x83\x93\x83\x74\x83\x89\x83\x8F\x81\x5B", 0, 0, -1,
    0, (s32)btlgrpsel_jon_btlno_jon_84_off, 268435456, 0, 50529027, 50529027, 50529027, 50529027,
    50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ヘンニャー"*/"\x83\x77\x83\x93\x83\x6A\x83\x83\x81\x5B", 0, 0,
    -1, 0, (s32)btlgrpsel_jon_btlno_jon_85_off, 268435456, 0, 50529027, 50529027, 50529027,
    50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"マホーンカスタム"*/"\x83\x7D\x83\x7A\x81\x5B\x83\x93\x83\x4A\x83\x58\x83\x5E\x83\x80", 0,
    0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_91_off, 268435456, 0, 50529027, 50529027,
    50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ドクガッスン"*/"\x83\x68\x83\x4E\x83\x4B\x83\x62\x83\x58\x83\x93",
    0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_92_off, 268435456, 0, 50529027,
    50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1",
    (s32)/*"ジャイアントボム"*/"\x83\x57\x83\x83\x83\x43\x83\x41\x83\x93\x83\x67\x83\x7B\x83\x80", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_93_off, 268435456, 0,
    50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009, 16843009,
    (s32)"BGM_ZAKO_BATTLE1", (s32)/*"バサバサグリーン"*/"\x83\x6F\x83\x54\x83\x6F\x83\x54\x83\x4F\x83\x8A\x81\x5B\x83\x93", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_94_off, 268435456,
    0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027, 16843009,
    16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"きらめくパンジーさん"*/"\x82\xAB\x82\xE7\x82\xDF\x82\xAD\x83\x70\x83\x93\x83\x57\x81\x5B\x82\xB3\x82\xF1", 0, 0, -1, 0, (s32)btlgrpsel_jon_btlno_jon_95_off,
    268435456, 0, 50529027, 50529027, 50529027, 50529027, 50529027, 50529027,
    16843009, 16843009, (s32)"BGM_ZAKO_BATTLE1", (s32)/*"ゾンババ"*/"\x83\x5D\x83\x93\x83\x6F\x83\x6F", (s32)"jon_06", 0, -1, 0,
    (s32)btlgrpsel_jon_btlno_jon_100_zonbaba_off, 537919504, 0, 50529027, 50529027, 50529027, 50529027, 50529027,
    50529027, 16843009, 16843009, (s32)"BGM_BOSS_STG1_GONBABA1", 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

s32 btl_jon_setup_no_tbl[] = {
    (s32)"BTLNO_JON_TEST1", 0, (s32)"BTLNO_JON_01", 1, (s32)"BTLNO_JON_02", 2, (s32)"BTLNO_JON_03", 3,
    (s32)"BTLNO_JON_04", 4, (s32)"BTLNO_JON_05", 5, (s32)"BTLNO_JON_11", 6, (s32)"BTLNO_JON_12", 7,
    (s32)"BTLNO_JON_13", 8, (s32)"BTLNO_JON_14", 9, (s32)"BTLNO_JON_15", 10, (s32)"BTLNO_JON_21", 11,
    (s32)"BTLNO_JON_22", 12, (s32)"BTLNO_JON_23", 13, (s32)"BTLNO_JON_24", 14, (s32)"BTLNO_JON_25", 15,
    (s32)"BTLNO_JON_31", 16, (s32)"BTLNO_JON_32", 17, (s32)"BTLNO_JON_33", 18, (s32)"BTLNO_JON_34", 19,
    (s32)"BTLNO_JON_35", 20, (s32)"BTLNO_JON_41", 21, (s32)"BTLNO_JON_42", 22, (s32)"BTLNO_JON_43", 23,
    (s32)"BTLNO_JON_44", 24, (s32)"BTLNO_JON_45", 25, (s32)"BTLNO_JON_51", 26, (s32)"BTLNO_JON_52", 27,
    (s32)"BTLNO_JON_53", 28, (s32)"BTLNO_JON_54", 29, (s32)"BTLNO_JON_55", 30, (s32)"BTLNO_JON_61", 31,
    (s32)"BTLNO_JON_62", 32, (s32)"BTLNO_JON_63", 33, (s32)"BTLNO_JON_64", 34, (s32)"BTLNO_JON_65", 35,
    (s32)"BTLNO_JON_71", 36, (s32)"BTLNO_JON_72", 37, (s32)"BTLNO_JON_73", 38, (s32)"BTLNO_JON_74", 39,
    (s32)"BTLNO_JON_75", 40, (s32)"BTLNO_JON_81", 41, (s32)"BTLNO_JON_82", 42, (s32)"BTLNO_JON_83", 43,
    (s32)"BTLNO_JON_84", 44, (s32)"BTLNO_JON_85", 45, (s32)"BTLNO_JON_91", 46, (s32)"BTLNO_JON_92", 47,
    (s32)"BTLNO_JON_93", 48, (s32)"BTLNO_JON_94", 49, (s32)"BTLNO_JON_95", 50, (s32)"BTLNO_JON_100_ZONBABA\0\0", 51,
    0, 0,
};

