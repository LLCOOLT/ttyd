#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"


s32 battle_item_gundan_zako[20];
s32 battle_item_gundan_zako_magician[20];
s32 battle_item_gundan_zako_elite[20];
s32 battle_item_hinnya[20];
s32 battle_item_hannya[20];
s32 battle_item_hennya[20];
s32 battle_item_kuriboo[20];
s32 battle_item_togekuri[20];
s32 battle_item_patakuri[20];
s32 battle_item_hyper_kuriboo[20];
s32 battle_item_hyper_togekuri[20];
s32 battle_item_hyper_patakuri[20];
s32 battle_item_yami_kuriboo[20];
s32 battle_item_yami_togekuri[20];
s32 battle_item_yami_patakuri[20];
s32 battle_item_nokonoko[20];
s32 battle_item_patapata[20];
s32 battle_item_yami_noko[20];
s32 battle_item_ura_noko[20];
s32 battle_item_ura_pata[20];
s32 battle_item_togenoko[20];
s32 battle_item_togenoko_ace[20];
s32 battle_item_hammer_bros[20];
s32 battle_item_met[20];
s32 battle_item_togemet[20];
s32 battle_item_patamet[20];
s32 battle_item_patatogemet[20];
s32 battle_item_hyper_togemet[14];
s32 battle_item_jyugem[20];
s32 battle_item_hyper_jyugem[20];
s32 battle_item_togezo[16];
s32 battle_item_kamec[20];
s32 battle_item_chorobon[18];
s32 battle_item_green_chorobon[18];
s32 battle_item_flower_chorobon[18];
s32 battle_item_honenoko[18];
s32 battle_item_karon[18];
s32 battle_item_monochrome_kurokumorn[18];
s32 battle_item_kurokumorn[18];
s32 battle_item_bllizard[18];
s32 battle_item_dokugassun[18];
s32 battle_item_pakkun_flower[14];
s32 battle_item_monochrome_sinemon[16];
s32 battle_item_sinemon[16];
s32 battle_item_hyper_sinnosuke[14];
s32 battle_item_hyper_sinemon[18];
s32 battle_item_basabasa[20];
s32 battle_item_basabasa_chururu[20];
s32 battle_item_basabasa_green[20];
s32 battle_item_teresa[20];
s32 battle_item_purple_teresa[20];
s32 battle_item_sambo[14];
s32 battle_item_sambo_mummy[16];
s32 battle_item_bomhei[20];
s32 battle_item_heavy_bom[18];
s32 battle_item_giant_bomb[18];
s32 battle_item_borodo[20];
s32 battle_item_badge_borodo[20];
s32 battle_item_mahorn[18];
s32 battle_item_super_mahorn[18];
s32 battle_item_mahorn_custom[18];
s32 battle_item_wanwan[14];
s32 battle_item_burst_wanwan[14];
s32 battle_item_bubble[16];
s32 battle_item_hermos[16];
s32 battle_item_phantom[16];
s32 battle_item_pansy[20];
s32 battle_item_twinkling_pansy[20];
s32 battle_item_dark_keeper[20];
s32 battle_heart_drop_param_default[200];
s32 battle_heart_drop_param_default2[180];
s32 battle_heart_drop_param_default3[160];
s32 battle_heart_drop_param_default4[140];
s32 battle_heart_drop_param_default5[120];
s32 battle_flower_drop_param_default[100];
s32 battle_flower_drop_param_default2[80];
s32 battle_flower_drop_param_default3[60];
s32 battle_flower_drop_param_default4[40];
s32 battle_flower_drop_param_default5[20];
s32 battle_item_NONE[2];
s32 battle_item_nokonoko_fighter[2];
s32 battle_item_patapata_fighter[2];
s32 battle_item_boomerang_bros[2];
s32 battle_item_fire_bros[2];
s32 battle_item_red_honenoko[2];
s32 battle_item_poison_pakkun[10];
s32 battle_item_ice_pakkun[10];
s32 battle_item_monochrome__pakkun[10];
s32 battle_item_piders[8];
s32 battle_item_churantalar[12];
s32 battle_item_barriern[2];
s32 battle_item_barriern_z[2];
s32 battle_item_barriern_custom[2];
s32 battle_item_iron_sinemon[2];
s32 battle_item_iron_sinemon2[2];
s32 battle_item_atmic_teresa[2];
s32 battle_item_killer[2];
s32 battle_item_super_killer[2];
s32 battle_item_killer_cannon[10];
s32 battle_item_super_killer_cannon[10];
s32 battle_item_borodo_king[2];
s32 battle_item_monban[2];
s32 battle_item_gold_chorobon[2];
s32 battle_item_sinnosuke[2];
s32 battle_item_togedaruma[2];
s32 battle_item_yamitogedaruma[10];
s32 battle_item_vivian1[2];
s32 battle_item_gesso[2];
s32 battle_item_gonbaba[2];
s32 battle_item_moamoa[2];
s32 battle_item_rampell[2];
s32 battle_item_faker_mario[2];
s32 battle_item_cortez[2];
s32 battle_item_kurikuri[2];
s32 battle_item_magnum_battender[2];
s32 battle_item_macho_gance[2];
s32 battle_item_champion[2];
s32 battle_item_kanbu1[2];
s32 battle_item_zonbaba[2];
s32 battle_item_default_param_list[2];

s32 battle_item_gundan_zako[] = {
    0, 13107500, 149, 655370, 155, 10, 132, 1310740,
    140, 655370, 141, 655370, 278, 131074, 280, 2,
    244, 2, 0, 0,
};

s32 battle_item_gundan_zako_magician[] = {
    0, 13107500, 149, 655370, 155, 10, 130, 1310740,
    140, 655370, 137, 655370, 270, 131073, 271, 131073,
    312, 2, 0, 0,
};

s32 battle_item_gundan_zako_elite[] = {
    0, 13107500, 149, 655370, 155, 10, 129, 1310740,
    140, 655370, 134, 655370, 262, 131073, 263, 131073,
    311, 2, 0, 0,
};

s32 battle_item_hinnya[] = {
    0, 13107500, 148, 327685, 154, 5, 128, 327685,
    138, 327685, 162, 10, 301, 131073, 302, 131073,
    247, 1, 0, 0,
};

s32 battle_item_hannya[] = {
    0, 13107500, 148, 327685, 154, 5, 128, 327685,
    138, 327685, 163, 10, 301, 131073, 302, 131073,
    247, 1, 0, 0,
};

s32 battle_item_hennya[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 655370,
    138, 327685, 177, 655370, 301, 131074, 302, 131074,
    247, 2, 0, 0,
};

s32 battle_item_kuriboo[] = {
    0, 13107500, 152, 655370, 153, 5, 132, 655370,
    138, 327685, 146, 327685, 299, 131073, 300, 131073,
    240, 1, 0, 0,
};

s32 battle_item_togekuri[] = {
    0, 13107500, 148, 327685, 154, 5, 132, 655370,
    138, 327685, 142, 327685, 299, 131073, 300, 131073,
    246, 1, 0, 0,
};

s32 battle_item_patakuri[] = {
    0, 13107500, 148, 327685, 154, 5, 132, 655370,
    138, 327685, 141, 327685, 299, 131073, 300, 131073,
    241, 1, 0, 0,
};

s32 battle_item_hyper_kuriboo[] = {
    0, 13107500, 151, 327685, 153, 5, 131, 327685,
    134, 1310740, 136, 655370, 272, 131073, 273, 131073,
    256, 2, 0, 0,
};

s32 battle_item_hyper_togekuri[] = {
    0, 13107500, 151, 327685, 153, 5, 131, 327685,
    134, 1310740, 142, 655370, 272, 131073, 273, 131073,
    257, 2, 0, 0,
};

s32 battle_item_hyper_patakuri[] = {
    0, 13107500, 151, 327685, 153, 5, 131, 327685,
    134, 1310740, 137, 655370, 272, 131073, 273, 131073,
    256, 2, 0, 0,
};

s32 battle_item_yami_kuriboo[] = {
    0, 13107500, 149, 655370, 155, 5, 132, 1310740,
    177, 327685, 135, 655370, 278, 131074, 279, 131074,
    240, 2, 0, 0,
};

s32 battle_item_yami_togekuri[] = {
    0, 13107500, 149, 655370, 155, 5, 132, 1310740,
    177, 327685, 144, 655370, 278, 131074, 279, 131074,
    246, 2, 0, 0,
};

s32 battle_item_yami_patakuri[] = {
    0, 13107500, 149, 655370, 155, 5, 132, 1310740,
    177, 327685, 141, 655370, 278, 131074, 279, 131074,
    241, 2, 0, 0,
};

s32 battle_item_nokonoko[] = {
    0, 13107500, 148, 327685, 154, 5, 139, 1310740,
    143, 655370, 138, 327685, 292, 131073, 269, 131073,
    294, 1, 0, 0,
};

s32 battle_item_patapata[] = {
    0, 13107500, 148, 327685, 154, 5, 139, 1310740,
    143, 655370, 141, 327685, 268, 131073, 293, 131073,
    294, 1, 0, 0,
};

s32 battle_item_yami_noko[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 655370,
    143, 655370, 147, 1310740, 292, 131073, 267, 131073,
    311, 2, 0, 0,
};

s32 battle_item_ura_noko[] = {
    0, 13107500, 149, 327685, 155, 5, 133, 1310740,
    143, 327685, 135, 655370, 292, 131073, 268, 131073,
    311, 2, 0, 0,
};

s32 battle_item_ura_pata[] = {
    0, 13107500, 149, 327685, 155, 5, 133, 1310740,
    143, 327685, 141, 655370, 293, 131073, 269, 131073,
    312, 2, 0, 0,
};

s32 battle_item_togenoko[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 1310740,
    143, 327685, 136, 655370, 299, 131074, 300, 131074,
    252, 1, 0, 0,
};

s32 battle_item_togenoko_ace[] = {
    0, 13107500, 149, 327685, 155, 5, 130, 1310740,
    143, 327685, 134, 655370, 262, 131074, 263, 131074,
    314, 2, 0, 0,
};

s32 battle_item_hammer_bros[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 983050,
    146, 1310740, 142, 327685, 266, 131074, 267, 131074,
    249, 2, 0, 0,
};

s32 battle_item_met[] = {
    0, 13107500, 157, 655370, 158, 10, 133, 327685,
    142, 327685, 146, 327685, 240, 2, 247, 2,
    244, 2, 0, 0,
};

s32 battle_item_togemet[] = {
    0, 13107500, 157, 655370, 158, 10, 133, 327685,
    142, 327685, 136, 327685, 240, 2, 247, 2,
    244, 2, 0, 0,
};

s32 battle_item_patamet[] = {
    0, 13107500, 157, 655370, 158, 10, 133, 327685,
    142, 327685, 141, 327685, 241, 2, 248, 2,
    253, 2, 0, 0,
};

s32 battle_item_patatogemet[] = {
    0, 13107500, 157, 655370, 158, 10, 133, 327685,
    142, 327685, 147, 327685, 241, 2, 248, 2,
    250, 2, 0, 0,
};

s32 battle_item_hyper_togemet[] = {
    0, 13107500, 157, 655370, 158, 10, 133, 327685,
    142, 327685, 136, 327685, 0, 0,
};

s32 battle_item_jyugem[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 655370,
    177, 327685, 135, 655370, 258, 2, 259, 2,
    243, 2, 0, 0,
};

s32 battle_item_hyper_jyugem[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 1310740,
    177, 327685, 135, 655370, 258, 2, 259, 2,
    243, 2, 0, 0,
};

s32 battle_item_togezo[] = {
    0, 13107500, 148, 327685, 154, 5, 133, 655370,
    137, 327685, 146, 327685, 244, 2, 0, 0,
};

s32 battle_item_kamec[] = {
    0, 13107500, 149, 327685, 155, 5, 130, 655370,
    140, 1310740, 163, 10, 279, 131074, 258, 2,
    259, 2, 0, 0,
};

s32 battle_item_chorobon[] = {
    0, 13107500, 148, 327685, 154, 5, 132, 327685,
    138, 327685, 144, 655370, 245, 1, 251, 2,
    0, 0,
};

s32 battle_item_green_chorobon[] = {
    0, 13107500, 157, 327685, 158, 5, 131, 327685,
    138, 983055, 137, 327685, 272, 131073, 295, 1,
    0, 0,
};

s32 battle_item_flower_chorobon[] = {
    0, 13107500, 157, 327685, 158, 5, 131, 327685,
    138, 983055, 177, 327685, 273, 131073, 297, 1,
    0, 0,
};

s32 battle_item_honenoko[] = {
    0, 13107500, 148, 327685, 154, 5, 132, 327685,
    177, 655370, 161, 10, 278, 2, 314, 1,
    0, 0,
};

s32 battle_item_karon[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    177, 1310740, 161, 10, 278, 2, 314, 1,
    0, 0,
};

s32 battle_item_monochrome_kurokumorn[] = {
    0, 13107500, 148, 327685, 154, 5, 128, 655370,
    141, 327685, 146, 327685, 245, 2, 297, 1,
    0, 0,
};

s32 battle_item_kurokumorn[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 983050,
    141, 327685, 147, 327685, 251, 2, 243, 2,
    0, 0,
};

s32 battle_item_bllizard[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 983050,
    141, 327685, 137, 327685, 246, 2, 253, 2,
    0, 0,
};

s32 battle_item_dokugassun[] = {
    0, 13107500, 149, 327685, 155, 5, 129, 983050,
    141, 327685, 142, 327685, 253, 2, 289, 2,
    0, 0,
};

s32 battle_item_pakkun_flower[] = {
    0, 13107500, 149, 5, 155, 10, 281, 1,
    282, 1, 306, 1, 0, 0,
};

s32 battle_item_monochrome_sinemon[] = {
    0, 13107500, 148, 327685, 154, 5, 133, 655370,
    146, 327685, 142, 327685, 248, 2, 0, 0,
};

s32 battle_item_sinemon[] = {
    0, 13107500, 149, 327685, 155, 5, 133, 655375,
    146, 327685, 140, 327685, 248, 2, 0, 0,
};

s32 battle_item_hyper_sinnosuke[] = {
    0, 13107500, 149, 327685, 155, 5, 133, 655370,
    146, 327685, 136, 327685, 0, 0,
};

s32 battle_item_hyper_sinemon[] = {
    0, 13107500, 149, 327685, 155, 5, 133, 983050,
    146, 327685, 136, 327685, 256, 2, 257, 2,
    0, 0,
};

s32 battle_item_basabasa[] = {
    0, 13107500, 148, 327685, 154, 5, 132, 327685,
    134, 327685, 144, 983055, 249, 1, 295, 2,
    296, 2, 0, 0,
};

s32 battle_item_basabasa_chururu[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    134, 327685, 141, 983055, 241, 2, 249, 2,
    296, 2, 0, 0,
};

s32 battle_item_basabasa_green[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    134, 327685, 137, 983055, 241, 2, 249, 2,
    303, 1, 0, 0,
};

s32 battle_item_teresa[] = {
    0, 13107500, 157, 655370, 158, 10, 132, 655370,
    141, 655370, 146, 655370, 258, 1, 259, 1,
    245, 2, 0, 0,
};

s32 battle_item_purple_teresa[] = {
    0, 13107500, 157, 655370, 158, 10, 129, 655370,
    141, 655370, 142, 655370, 258, 2, 259, 2,
    313, 1, 0, 0,
};

s32 battle_item_sambo[] = {
    0, 13107500, 151, 327685, 153, 15, 133, 327685,
    144, 327685, 147, 327685, 0, 0,
};

s32 battle_item_sambo_mummy[] = {
    0, 13107500, 151, 327685, 153, 15, 133, 327685,
    144, 327685, 147, 327685, 280, 2, 0, 0,
};

s32 battle_item_bomhei[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    140, 327685, 136, 327685, 251, 2, 277, 1,
    276, 1, 0, 0,
};

s32 battle_item_heavy_bom[] = {
    0, 13107500, 149, 5, 155, 5, 132, 5,
    140, 5, 141, 5, 276, 2, 277, 2,
    0, 0,
};

s32 battle_item_giant_bomb[] = {
    0, 13107500, 149, 5, 155, 5, 132, 5,
    140, 5, 141, 5, 274, 131074, 275, 131074,
    0, 0,
};

s32 battle_item_borodo[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    138, 655370, 162, 15, 301, 131073, 302, 131073,
    305, 2, 0, 0,
};

s32 battle_item_badge_borodo[] = {
    0, 13107500, 149, 327685, 155, 5, 131, 327685,
    138, 655370, 163, 15, 301, 131074, 302, 131074,
    305, 2, 0, 0,
};

s32 battle_item_mahorn[] = {
    0, 13107500, 149, 655370, 155, 10, 129, 655370,
    140, 655370, 134, 327685, 289, 1, 290, 1,
    0, 0,
};

s32 battle_item_super_mahorn[] = {
    0, 13107500, 151, 655370, 155, 10, 129, 655370,
    140, 655370, 134, 327685, 260, 65537, 261, 65537,
    0, 0,
};

s32 battle_item_mahorn_custom[] = {
    0, 13107500, 150, 655370, 156, 10, 130, 655370,
    140, 655370, 134, 327685, 260, 131074, 261, 131074,
    0, 0,
};

s32 battle_item_wanwan[] = {
    0, 13107500, 149, 10, 155, 10, 142, 655370,
    274, 131073, 275, 131073, 0, 0,
};

s32 battle_item_burst_wanwan[] = {
    0, 13107500, 149, 10, 155, 10, 142, 655370,
    276, 131073, 277, 131073, 0, 0,
};

s32 battle_item_bubble[] = {
    0, 13107500, 149, 327685, 155, 5, 132, 15,
    142, 327685, 144, 655370, 252, 2, 0, 0,
};

s32 battle_item_hermos[] = {
    0, 13107500, 149, 327685, 155, 5, 132, 15,
    142, 327685, 177, 655370, 252, 2, 0, 0,
};

s32 battle_item_phantom[] = {
    0, 13107500, 149, 327685, 155, 5, 132, 15,
    142, 327685, 137, 655370, 252, 2, 0, 0,
};

s32 battle_item_pansy[] = {
    0, 13107500, 149, 655370, 155, 10, 128, 655370,
    161, 15, 162, 10, 294, 2, 282, 1,
    281, 1, 0, 0,
};

s32 battle_item_twinkling_pansy[] = {
    0, 13107500, 150, 655370, 156, 10, 130, 655370,
    161, 15, 163, 10, 294, 2, 282, 2,
    281, 2, 0, 0,
};

s32 battle_item_dark_keeper[] = {
    0, 13107500, 151, 655370, 153, 10, 130, 327685,
    137, 327685, 177, 327685, 270, 131074, 271, 131074,
    264, 1, 0, 0,
};

s32 battle_heart_drop_param_default[] = {
    20, 70, 2, 50, 30, 60, 2, 50,
    50, 50, 2, 40, 80, 40, 2, 40,
    100, 30, 2, 30, 20, 70, 3, 50,
    30, 60, 3, 50, 50, 50, 3, 40,
    80, 40, 3, 40, 100, 30, 3, 30,
    20, 70, 4, 50, 30, 60, 4, 50,
    50, 50, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 30, 20, 70, 5, 50,
    30, 60, 5, 50, 50, 50, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 30,
    20, 70, 6, 50, 30, 60, 6, 50,
    50, 50, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 30, 20, 40, 2, 40,
    30, 40, 2, 40, 50, 40, 2, 40,
    80, 40, 2, 40, 100, 30, 2, 40,
    20, 40, 3, 40, 30, 40, 3, 40,
    50, 40, 3, 40, 80, 40, 3, 40,
    100, 30, 3, 40, 20, 40, 4, 40,
    30, 40, 4, 40, 50, 40, 4, 40,
    80, 40, 4, 40, 100, 30, 4, 40,
    20, 40, 5, 40, 30, 40, 5, 40,
    50, 40, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 40, 20, 40, 6, 40,
    30, 40, 6, 40, 50, 40, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 40,
};

s32 battle_heart_drop_param_default2[] = {
    20, 70, 3, 50, 30, 60, 3, 50,
    50, 50, 3, 40, 80, 40, 3, 40,
    100, 30, 3, 30, 20, 70, 4, 50,
    30, 60, 4, 50, 50, 50, 4, 40,
    80, 40, 4, 40, 100, 30, 4, 30,
    20, 70, 5, 50, 30, 60, 5, 50,
    50, 50, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 30, 20, 70, 6, 50,
    30, 60, 6, 50, 50, 50, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 30,
    20, 40, 2, 40, 30, 40, 2, 40,
    50, 40, 2, 40, 80, 40, 2, 40,
    100, 30, 2, 40, 20, 40, 3, 40,
    30, 40, 3, 40, 50, 40, 3, 40,
    80, 40, 3, 40, 100, 30, 3, 40,
    20, 40, 4, 40, 30, 40, 4, 40,
    50, 40, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 40, 20, 40, 5, 40,
    30, 40, 5, 40, 50, 40, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 40,
    20, 40, 6, 40, 30, 40, 6, 40,
    50, 40, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 40,
};

s32 battle_heart_drop_param_default3[] = {
    20, 70, 4, 50, 30, 60, 4, 50,
    50, 50, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 30, 20, 70, 5, 50,
    30, 60, 5, 50, 50, 50, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 30,
    20, 70, 6, 50, 30, 60, 6, 50,
    50, 50, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 30, 20, 40, 2, 40,
    30, 40, 2, 40, 50, 40, 2, 40,
    80, 40, 2, 40, 100, 30, 2, 40,
    20, 40, 3, 40, 30, 40, 3, 40,
    50, 40, 3, 40, 80, 40, 3, 40,
    100, 30, 3, 40, 20, 40, 4, 40,
    30, 40, 4, 40, 50, 40, 4, 40,
    80, 40, 4, 40, 100, 30, 4, 40,
    20, 40, 5, 40, 30, 40, 5, 40,
    50, 40, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 40, 20, 40, 6, 40,
    30, 40, 6, 40, 50, 40, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 40,
};

s32 battle_heart_drop_param_default4[] = {
    20, 70, 5, 50, 30, 60, 5, 50,
    50, 50, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 30, 20, 70, 6, 50,
    30, 60, 6, 50, 50, 50, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 30,
    20, 40, 2, 40, 30, 40, 2, 40,
    50, 40, 2, 40, 80, 40, 2, 40,
    100, 30, 2, 40, 20, 40, 3, 40,
    30, 40, 3, 40, 50, 40, 3, 40,
    80, 40, 3, 40, 100, 30, 3, 40,
    20, 40, 4, 40, 30, 40, 4, 40,
    50, 40, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 40, 20, 40, 5, 40,
    30, 40, 5, 40, 50, 40, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 40,
    20, 40, 6, 40, 30, 40, 6, 40,
    50, 40, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 40,
};

s32 battle_heart_drop_param_default5[] = {
    20, 70, 6, 50, 30, 60, 6, 50,
    50, 50, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 30, 20, 40, 2, 40,
    30, 40, 2, 40, 50, 40, 2, 40,
    80, 40, 2, 40, 100, 30, 2, 40,
    20, 40, 3, 40, 30, 40, 3, 40,
    50, 40, 3, 40, 80, 40, 3, 40,
    100, 30, 3, 40, 20, 40, 4, 40,
    30, 40, 4, 40, 50, 40, 4, 40,
    80, 40, 4, 40, 100, 30, 4, 40,
    20, 40, 5, 40, 30, 40, 5, 40,
    50, 40, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 40, 20, 40, 6, 40,
    30, 40, 6, 40, 50, 40, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 40,
};

s32 battle_flower_drop_param_default[] = {
    20, 40, 2, 40, 30, 40, 2, 40,
    50, 40, 2, 40, 80, 40, 2, 40,
    100, 30, 2, 40, 20, 40, 3, 40,
    30, 40, 3, 40, 50, 40, 3, 40,
    80, 40, 3, 40, 100, 30, 3, 40,
    20, 40, 4, 40, 30, 40, 4, 40,
    50, 40, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 40, 20, 40, 5, 40,
    30, 40, 5, 40, 50, 40, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 40,
    20, 40, 6, 40, 30, 40, 6, 40,
    50, 40, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 40,
};

s32 battle_flower_drop_param_default2[] = {
    20, 40, 3, 40, 30, 40, 3, 40,
    50, 40, 3, 40, 80, 40, 3, 40,
    100, 30, 3, 40, 20, 40, 4, 40,
    30, 40, 4, 40, 50, 40, 4, 40,
    80, 40, 4, 40, 100, 30, 4, 40,
    20, 40, 5, 40, 30, 40, 5, 40,
    50, 40, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 40, 20, 40, 6, 40,
    30, 40, 6, 40, 50, 40, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 40,
};

s32 battle_flower_drop_param_default3[] = {
    20, 40, 4, 40, 30, 40, 4, 40,
    50, 40, 4, 40, 80, 40, 4, 40,
    100, 30, 4, 40, 20, 40, 5, 40,
    30, 40, 5, 40, 50, 40, 5, 40,
    80, 40, 5, 40, 100, 30, 5, 40,
    20, 40, 6, 40, 30, 40, 6, 40,
    50, 40, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 40,
};

s32 battle_flower_drop_param_default4[] = {
    20, 40, 5, 40, 30, 40, 5, 40,
    50, 40, 5, 40, 80, 40, 5, 40,
    100, 30, 5, 40, 20, 40, 6, 40,
    30, 40, 6, 40, 50, 40, 6, 40,
    80, 40, 6, 40, 100, 30, 6, 40,
};

s32 battle_flower_drop_param_default5[] = {
    20, 40, 6, 40, 30, 40, 6, 40,
    50, 40, 6, 40, 80, 40, 6, 40,
    100, 30, 6, 40,
};

s32 battle_item_NONE[] = {
    0, 0,
};

s32 battle_item_nokonoko_fighter[] = {
    0, 0,
};

s32 battle_item_patapata_fighter[] = {
    0, 0,
};

s32 battle_item_boomerang_bros[] = {
    0, 0,
};

s32 battle_item_fire_bros[] = {
    0, 0,
};

s32 battle_item_red_honenoko[] = {
    0, 0,
};

s32 battle_item_poison_pakkun[] = {
    0, 13107500, 149, 5, 155, 10, 280, 1,
    0, 0,
};

s32 battle_item_ice_pakkun[] = {
    0, 13107500, 149, 5, 155, 10, 253, 1,
    0, 0,
};

s32 battle_item_monochrome__pakkun[] = {
    0, 13107500, 148, 5, 154, 10, 280, 1,
    0, 0,
};

s32 battle_item_piders[] = {
    0, 13107500, 157, 10, 158, 5, 0, 0,
};

s32 battle_item_churantalar[] = {
    0, 13107500, 157, 10, 158, 5, 306, 2,
    264, 2, 0, 0,
};

s32 battle_item_barriern[] = {
    0, 0,
};

s32 battle_item_barriern_z[] = {
    0, 0,
};

s32 battle_item_barriern_custom[] = {
    0, 0,
};

s32 battle_item_iron_sinemon[] = {
    0, 0,
};

s32 battle_item_iron_sinemon2[] = {
    0, 0,
};

s32 battle_item_atmic_teresa[] = {
    0, 0,
};

s32 battle_item_killer[] = {
    0, 0,
};

s32 battle_item_super_killer[] = {
    0, 0,
};

s32 battle_item_killer_cannon[] = {
    0, 13107500, 148, 5, 154, 5, 313, 2,
    0, 0,
};

s32 battle_item_super_killer_cannon[] = {
    0, 13107500, 149, 5, 155, 5, 313, 2,
    0, 0,
};

s32 battle_item_borodo_king[] = {
    0, 0,
};

s32 battle_item_monban[] = {
    0, 0,
};

s32 battle_item_gold_chorobon[] = {
    0, 0,
};

s32 battle_item_sinnosuke[] = {
    0, 0,
};

s32 battle_item_togedaruma[] = {
    0, 0,
};

s32 battle_item_yamitogedaruma[] = {
    0, 13107500, 149, 10, 155, 10, 290, 2,
    0, 0,
};

s32 battle_item_vivian1[] = {
    0, 0,
};

s32 battle_item_gesso[] = {
    0, 0,
};

s32 battle_item_gonbaba[] = {
    0, 0,
};

s32 battle_item_moamoa[] = {
    0, 0,
};

s32 battle_item_rampell[] = {
    0, 0,
};

s32 battle_item_faker_mario[] = {
    0, 0,
};

s32 battle_item_cortez[] = {
    0, 0,
};

s32 battle_item_kurikuri[] = {
    0, 0,
};

s32 battle_item_magnum_battender[] = {
    0, 0,
};

s32 battle_item_macho_gance[] = {
    0, 0,
};

s32 battle_item_champion[] = {
    0, 0,
};

s32 battle_item_kanbu1[] = {
    0, 0,
};

s32 battle_item_zonbaba[] = {
    0, 0,
};

s32 battle_item_default_param_list[] = {
    0, 0,
};

