#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"


s32 audience_kinopio_run_front[14];
s32 audience_daisan_run_front[14];
s32 audience_teresa_run_front[14];
s32 audience_hammer_bros_run_front[14];
s32 audience_honenoko_run_front[14];
s32 audience_heiho_run_front[14];
s32 audience_pansy_run_front[14];
s32 audience_puni_run_front[14];
s32 audience_nokonoko_run_front[14];
s32 audience_heavy_bomb_run_front[14];
s32 audience_kuriboo_run_front[14];
s32 audience_pakkun_run_front[14];
s32 audience_luigi_run_front[14];
s32 audience_anim_kinopio[19];
s32 audience_anim_daisan[19];
s32 audience_anim_teresa[19];
s32 audience_anim_hammer_bros[19];
s32 audience_anim_honenoko[19];
s32 audience_anim_heiho[19];
s32 audience_anim_pansy[19];
s32 audience_anim_puni[19];
s32 audience_anim_nokonoko[19];
s32 audience_anim_heavy_bomb[19];
s32 audience_anim_kuriboo[19];
s32 audience_anim_pakkun[19];
s32 audience_anim_luigi[19];
s32 audience_item_kinopio[24];
s32 audience_item_heiho[34];
s32 audience_item_puni[22];
s32 audience_item_nokonoko[16];
s32 audience_item_luigi[24];
s32 audience_kind[104];
s32 audience_kinopio_wait_front[8];
s32 audience_kinopio_wait_back[8];
s32 audience_kinopio_jump_front[8];
s32 audience_kinopio_jump_back[8];
s32 audience_kinopio_raise_back[8];
s32 audience_kinopio_itemon_back[8];
s32 audience_kinopio_itemthrow_back[4];
s32 audience_kinopio_tumble_front[8];
s32 audience_kinopio_damage_front[4];
s32 audience_kinopio_sleep_front[8];
s32 audience_kinopio_sleep_back[8];
s32 audience_kinopio_confuse_front[8];
s32 audience_kinopio_confuse_back[8];
s32 audience_daisan_wait_front[8];
s32 audience_daisan_wait_back[8];
s32 audience_daisan_jump_front[8];
s32 audience_daisan_jump_back[8];
s32 audience_daisan_raise_back[8];
s32 audience_daisan_itemon_back[8];
s32 audience_daisan_itemthrow_back[4];
s32 audience_daisan_tumble_front[8];
s32 audience_daisan_damage_front[4];
s32 audience_daisan_sleep_front[8];
s32 audience_daisan_sleep_back[8];
s32 audience_daisan_confuse_front[8];
s32 audience_daisan_confuse_back[8];
s32 audience_teresa_wait_front[8];
s32 audience_teresa_wait_back[8];
s32 audience_teresa_jump_front[8];
s32 audience_teresa_jump_back[8];
s32 audience_teresa_raise_back[8];
s32 audience_teresa_itemon_back[8];
s32 audience_teresa_itemthrow_back[4];
s32 audience_teresa_tumble_front[8];
s32 audience_teresa_damage_front[4];
s32 audience_teresa_sleep_front[8];
s32 audience_teresa_sleep_back[8];
s32 audience_teresa_confuse_front[8];
s32 audience_teresa_confuse_back[8];
s32 audience_hammer_bros_wait_front[8];
s32 audience_hammer_bros_wait_back[8];
s32 audience_hammer_bros_jump_front[8];
s32 audience_hammer_bros_jump_back[8];
s32 audience_hammer_bros_raise_back[8];
s32 audience_hammer_bros_itemon_back[8];
s32 audience_hammer_bros_itemthrow_back[4];
s32 audience_hammer_bros_tumble_front[8];
s32 audience_hammer_bros_damage_front[4];
s32 audience_hammer_bros_sleep_front[8];
s32 audience_hammer_bros_sleep_back[8];
s32 audience_hammer_bros_confuse_front[8];
s32 audience_hammer_bros_confuse_back[8];
s32 audience_honenoko_wait_front[8];
s32 audience_honenoko_wait_back[8];
s32 audience_honenoko_jump_front[8];
s32 audience_honenoko_jump_back[8];
s32 audience_honenoko_raise_back[8];
s32 audience_honenoko_itemon_back[8];
s32 audience_honenoko_itemthrow_back[4];
s32 audience_honenoko_tumble_front[8];
s32 audience_honenoko_damage_front[4];
s32 audience_honenoko_sleep_front[8];
s32 audience_honenoko_sleep_back[8];
s32 audience_honenoko_confuse_front[8];
s32 audience_honenoko_confuse_back[8];
s32 audience_heiho_wait_front[8];
s32 audience_heiho_wait_back[8];
s32 audience_heiho_jump_front[8];
s32 audience_heiho_jump_back[8];
s32 audience_heiho_raise_back[8];
s32 audience_heiho_itemon_back[8];
s32 audience_heiho_itemthrow_back[4];
s32 audience_heiho_tumble_front[8];
s32 audience_heiho_damage_front[4];
s32 audience_heiho_sleep_front[8];
s32 audience_heiho_sleep_back[8];
s32 audience_heiho_confuse_front[8];
s32 audience_heiho_confuse_back[8];
s32 audience_pansy_wait_front[8];
s32 audience_pansy_wait_back[8];
s32 audience_pansy_jump_front[8];
s32 audience_pansy_jump_back[8];
s32 audience_pansy_raise_back[8];
s32 audience_pansy_itemon_back[8];
s32 audience_pansy_itemthrow_back[4];
s32 audience_pansy_tumble_front[8];
s32 audience_pansy_damage_front[4];
s32 audience_pansy_sleep_front[8];
s32 audience_pansy_sleep_back[8];
s32 audience_pansy_confuse_front[8];
s32 audience_pansy_confuse_back[8];
s32 audience_pansy_sing_front[11];
s32 audience_puni_wait_front[8];
s32 audience_puni_wait_back[8];
s32 audience_puni_jump_front[8];
s32 audience_puni_jump_back[8];
s32 audience_puni_raise_back[8];
s32 audience_puni_itemon_back[8];
s32 audience_puni_itemthrow_back[4];
s32 audience_puni_tumble_front[8];
s32 audience_puni_damage_front[4];
s32 audience_puni_sleep_front[8];
s32 audience_puni_sleep_back[8];
s32 audience_puni_confuse_front[8];
s32 audience_puni_confuse_back[8];
s32 audience_nokonoko_wait_front[8];
s32 audience_nokonoko_wait_back[8];
s32 audience_nokonoko_jump_front[8];
s32 audience_nokonoko_jump_back[8];
s32 audience_nokonoko_raise_back[8];
s32 audience_nokonoko_itemon_back[8];
s32 audience_nokonoko_itemthrow_back[4];
s32 audience_nokonoko_tumble_front[8];
s32 audience_nokonoko_damage_front[4];
s32 audience_nokonoko_sleep_front[8];
s32 audience_nokonoko_sleep_back[8];
s32 audience_nokonoko_confuse_front[8];
s32 audience_nokonoko_confuse_back[8];
s32 audience_nokonoko_shell_back[8];
s32 audience_heavy_bomb_wait_front[8];
s32 audience_heavy_bomb_wait_back[8];
s32 audience_heavy_bomb_jump_front[8];
s32 audience_heavy_bomb_jump_back[8];
s32 audience_heavy_bomb_raise_back[8];
s32 audience_heavy_bomb_itemon_back[8];
s32 audience_heavy_bomb_itemthrow_back[4];
s32 audience_heavy_bomb_tumble_front[8];
s32 audience_heavy_bomb_damage_front[4];
s32 audience_heavy_bomb_sleep_front[8];
s32 audience_heavy_bomb_sleep_back[8];
s32 audience_heavy_bomb_confuse_front[8];
s32 audience_heavy_bomb_confuse_back[8];
s32 audience_heavy_bomb_ignite_front[11];
s32 audience_heavy_bomb_ignite_back[11];
s32 audience_kuriboo_wait_front[8];
s32 audience_kuriboo_wait_back[8];
s32 audience_kuriboo_jump_front[8];
s32 audience_kuriboo_jump_back[8];
s32 audience_kuriboo_raise_back[8];
s32 audience_kuriboo_itemon_back[8];
s32 audience_kuriboo_itemthrow_back[4];
s32 audience_kuriboo_tumble_front[8];
s32 audience_kuriboo_damage_front[4];
s32 audience_kuriboo_sleep_front[8];
s32 audience_kuriboo_sleep_back[8];
s32 audience_kuriboo_confuse_front[8];
s32 audience_kuriboo_confuse_back[8];
s32 audience_pakkun_wait_front[8];
s32 audience_pakkun_wait_back[8];
s32 audience_pakkun_jump_front[8];
s32 audience_pakkun_jump_back[8];
s32 audience_pakkun_raise_back[8];
s32 audience_pakkun_itemon_back[8];
s32 audience_pakkun_itemthrow_back[4];
s32 audience_pakkun_tumble_front[8];
s32 audience_pakkun_damage_front[4];
s32 audience_pakkun_sleep_front[8];
s32 audience_pakkun_sleep_back[8];
s32 audience_pakkun_confuse_front[8];
s32 audience_pakkun_confuse_back[8];
s32 audience_pakkun_eat_front[7];
s32 audience_luigi_wait_front[8];
s32 audience_luigi_wait_back[8];
s32 audience_luigi_jump_front[8];
s32 audience_luigi_jump_back[8];
s32 audience_luigi_raise_back[8];
s32 audience_luigi_itemon_back[8];
s32 audience_luigi_itemthrow_back[4];
s32 audience_luigi_tumble_front[8];
s32 audience_luigi_damage_front[4];
s32 audience_luigi_sleep_front[8];
s32 audience_luigi_sleep_back[8];
s32 audience_luigi_confuse_front[8];
s32 audience_luigi_confuse_back[8];
s32 audience_item_daisan[6];
s32 audience_item_teresa[12];
s32 audience_item_hammer_bros[4];
s32 audience_item_honenoko[8];
s32 audience_item_pansy[2];
s32 audience_item_heavy_bomb[2];
s32 audience_item_kuriboo[6];
s32 audience_item_pakkun[2];

s32 audience_kinopio_run_front[] = {
    -4, 0, -2, 8, 4, -2, 9, 4,
    -2, 10, 4, -5, 0, -1,
};

s32 audience_daisan_run_front[] = {
    -4, 0, -2, 24, 4, -2, 25, 4,
    -2, 26, 4, -5, 0, -1,
};

s32 audience_teresa_run_front[] = {
    -4, 0, -2, 40, 4, -2, 41, 4,
    -2, 42, 4, -5, 0, -1,
};

s32 audience_hammer_bros_run_front[] = {
    -4, 0, -2, 58, 4, -2, 59, 4,
    -2, 60, 4, -5, 0, -1,
};

s32 audience_honenoko_run_front[] = {
    -4, 0, -2, 74, 4, -2, 75, 4,
    -2, 76, 4, -5, 0, -1,
};

s32 audience_heiho_run_front[] = {
    -4, 0, -2, 90, 4, -2, 91, 4,
    -2, 92, 4, -5, 0, -1,
};

s32 audience_pansy_run_front[] = {
    -4, 0, -2, 108, 4, -2, 109, 4,
    -2, 110, 4, -5, 0, -1,
};

s32 audience_puni_run_front[] = {
    -4, 0, -2, 126, 4, -2, 127, 4,
    -2, 128, 4, -5, 0, -1,
};

s32 audience_nokonoko_run_front[] = {
    -4, 0, -2, 142, 4, -2, 143, 4,
    -2, 144, 4, -5, 0, -1,
};

s32 audience_heavy_bomb_run_front[] = {
    -4, 0, -2, 159, 4, -2, 160, 4,
    -2, 161, 4, -5, 0, -1,
};

s32 audience_kuriboo_run_front[] = {
    -4, 0, -2, 179, 4, -2, 180, 4,
    -2, 181, 4, -5, 0, -1,
};

s32 audience_pakkun_run_front[] = {
    -4, 0, -2, 195, 4, -2, 196, 4,
    -2, 197, 4, -5, 0, -1,
};

s32 audience_luigi_run_front[] = {
    -4, 0, -2, 8, 4, -2, 9, 4,
    -2, 10, 4, -5, 0, -1,
};

s32 audience_anim_kinopio[] = {
    (s32)audience_kinopio_wait_front, (s32)audience_kinopio_wait_back, (s32)audience_kinopio_jump_front, (s32)audience_kinopio_jump_back, (s32)audience_kinopio_raise_back, (s32)audience_kinopio_itemon_back, (s32)audience_kinopio_itemthrow_back, (s32)audience_kinopio_run_front,
    (s32)audience_kinopio_tumble_front, (s32)audience_kinopio_damage_front, (s32)audience_kinopio_sleep_front, (s32)audience_kinopio_sleep_back, (s32)audience_kinopio_confuse_front, (s32)audience_kinopio_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_daisan[] = {
    (s32)audience_daisan_wait_front, (s32)audience_daisan_wait_back, (s32)audience_daisan_jump_front, (s32)audience_daisan_jump_back, (s32)audience_daisan_raise_back, (s32)audience_daisan_itemon_back, (s32)audience_daisan_itemthrow_back, (s32)audience_daisan_run_front,
    (s32)audience_daisan_tumble_front, (s32)audience_daisan_damage_front, (s32)audience_daisan_sleep_front, (s32)audience_daisan_sleep_back, (s32)audience_daisan_confuse_front, (s32)audience_daisan_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_teresa[] = {
    (s32)audience_teresa_wait_front, (s32)audience_teresa_wait_back, (s32)audience_teresa_jump_front, (s32)audience_teresa_jump_back, (s32)audience_teresa_raise_back, (s32)audience_teresa_itemon_back, (s32)audience_teresa_itemthrow_back, (s32)audience_teresa_run_front,
    (s32)audience_teresa_tumble_front, (s32)audience_teresa_damage_front, (s32)audience_teresa_sleep_front, (s32)audience_teresa_sleep_back, (s32)audience_teresa_confuse_front, (s32)audience_teresa_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_hammer_bros[] = {
    (s32)audience_hammer_bros_wait_front, (s32)audience_hammer_bros_wait_back, (s32)audience_hammer_bros_jump_front, (s32)audience_hammer_bros_jump_back, (s32)audience_hammer_bros_raise_back, (s32)audience_hammer_bros_itemon_back, (s32)audience_hammer_bros_itemthrow_back, (s32)audience_hammer_bros_run_front,
    (s32)audience_hammer_bros_tumble_front, (s32)audience_hammer_bros_damage_front, (s32)audience_hammer_bros_sleep_front, (s32)audience_hammer_bros_sleep_back, (s32)audience_hammer_bros_confuse_front, (s32)audience_hammer_bros_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_honenoko[] = {
    (s32)audience_honenoko_wait_front, (s32)audience_honenoko_wait_back, (s32)audience_honenoko_jump_front, (s32)audience_honenoko_jump_back, (s32)audience_honenoko_raise_back, (s32)audience_honenoko_itemon_back, (s32)audience_honenoko_itemthrow_back, (s32)audience_honenoko_run_front,
    (s32)audience_honenoko_tumble_front, (s32)audience_honenoko_damage_front, (s32)audience_honenoko_sleep_front, (s32)audience_honenoko_sleep_back, (s32)audience_honenoko_confuse_front, (s32)audience_honenoko_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_heiho[] = {
    (s32)audience_heiho_wait_front, (s32)audience_heiho_wait_back, (s32)audience_heiho_jump_front, (s32)audience_heiho_jump_back, (s32)audience_heiho_raise_back, (s32)audience_heiho_itemon_back, (s32)audience_heiho_itemthrow_back, (s32)audience_heiho_run_front,
    (s32)audience_heiho_tumble_front, (s32)audience_heiho_damage_front, (s32)audience_heiho_sleep_front, (s32)audience_heiho_sleep_back, (s32)audience_heiho_confuse_front, (s32)audience_heiho_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_pansy[] = {
    (s32)audience_pansy_wait_front, (s32)audience_pansy_wait_back, (s32)audience_pansy_jump_front, (s32)audience_pansy_jump_back, (s32)audience_pansy_raise_back, (s32)audience_pansy_itemon_back, (s32)audience_pansy_itemthrow_back, (s32)audience_pansy_run_front,
    (s32)audience_pansy_tumble_front, (s32)audience_pansy_damage_front, (s32)audience_pansy_sleep_front, (s32)audience_pansy_sleep_back, (s32)audience_pansy_confuse_front, (s32)audience_pansy_confuse_back, (s32)audience_pansy_sing_front, 0,
    0, 0, 0,
};

s32 audience_anim_puni[] = {
    (s32)audience_puni_wait_front, (s32)audience_puni_wait_back, (s32)audience_puni_jump_front, (s32)audience_puni_jump_back, (s32)audience_puni_raise_back, (s32)audience_puni_itemon_back, (s32)audience_puni_itemthrow_back, (s32)audience_puni_run_front,
    (s32)audience_puni_tumble_front, (s32)audience_puni_damage_front, (s32)audience_puni_sleep_front, (s32)audience_puni_sleep_back, (s32)audience_puni_confuse_front, (s32)audience_puni_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_nokonoko[] = {
    (s32)audience_nokonoko_wait_front, (s32)audience_nokonoko_wait_back, (s32)audience_nokonoko_jump_front, (s32)audience_nokonoko_jump_back, (s32)audience_nokonoko_raise_back, (s32)audience_nokonoko_itemon_back, (s32)audience_nokonoko_itemthrow_back, (s32)audience_nokonoko_run_front,
    (s32)audience_nokonoko_tumble_front, (s32)audience_nokonoko_damage_front, (s32)audience_nokonoko_sleep_front, (s32)audience_nokonoko_sleep_back, (s32)audience_nokonoko_confuse_front, (s32)audience_nokonoko_confuse_back, 0, (s32)audience_nokonoko_shell_back,
    0, 0, 0,
};

s32 audience_anim_heavy_bomb[] = {
    (s32)audience_heavy_bomb_wait_front, (s32)audience_heavy_bomb_wait_back, (s32)audience_heavy_bomb_jump_front, (s32)audience_heavy_bomb_jump_back, (s32)audience_heavy_bomb_raise_back, (s32)audience_heavy_bomb_itemon_back, (s32)audience_heavy_bomb_itemthrow_back, (s32)audience_heavy_bomb_run_front,
    (s32)audience_heavy_bomb_tumble_front, (s32)audience_heavy_bomb_damage_front, (s32)audience_heavy_bomb_sleep_front, (s32)audience_heavy_bomb_sleep_back, (s32)audience_heavy_bomb_confuse_front, (s32)audience_heavy_bomb_confuse_back, 0, 0,
    (s32)audience_heavy_bomb_ignite_front, (s32)audience_heavy_bomb_ignite_back, 0,
};

s32 audience_anim_kuriboo[] = {
    (s32)audience_kuriboo_wait_front, (s32)audience_kuriboo_wait_back, (s32)audience_kuriboo_jump_front, (s32)audience_kuriboo_jump_back, (s32)audience_kuriboo_raise_back, (s32)audience_kuriboo_itemon_back, (s32)audience_kuriboo_itemthrow_back, (s32)audience_kuriboo_run_front,
    (s32)audience_kuriboo_tumble_front, (s32)audience_kuriboo_damage_front, (s32)audience_kuriboo_sleep_front, (s32)audience_kuriboo_sleep_back, (s32)audience_kuriboo_confuse_front, (s32)audience_kuriboo_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_anim_pakkun[] = {
    (s32)audience_pakkun_wait_front, (s32)audience_pakkun_wait_back, (s32)audience_pakkun_jump_front, (s32)audience_pakkun_jump_back, (s32)audience_pakkun_raise_back, (s32)audience_pakkun_itemon_back, (s32)audience_pakkun_itemthrow_back, (s32)audience_pakkun_run_front,
    (s32)audience_pakkun_tumble_front, (s32)audience_pakkun_damage_front, (s32)audience_pakkun_sleep_front, (s32)audience_pakkun_sleep_back, (s32)audience_pakkun_confuse_front, (s32)audience_pakkun_confuse_back, 0, 0,
    0, 0, (s32)audience_pakkun_eat_front,
};

s32 audience_anim_luigi[] = {
    (s32)audience_luigi_wait_front, (s32)audience_luigi_wait_back, (s32)audience_luigi_jump_front, (s32)audience_luigi_jump_back, (s32)audience_luigi_raise_back, (s32)audience_luigi_itemon_back, (s32)audience_luigi_itemthrow_back, (s32)audience_luigi_run_front,
    (s32)audience_luigi_tumble_front, (s32)audience_luigi_damage_front, (s32)audience_luigi_sleep_front, (s32)audience_luigi_sleep_back, (s32)audience_luigi_confuse_front, (s32)audience_luigi_confuse_back, 0, 0,
    0, 0, 0,
};

s32 audience_item_kinopio[] = {
    121, 10, 123, 10, 124, 10, 148, 50,
    149, 10, 150, 1, 151, 5, 154, 10,
    132, 10, 129, 5, 130, 5, 0, 0,
};

s32 audience_item_heiho[] = {
    131, 10, 133, 10, 135, 10, 138, 10,
    141, 10, 137, 10, 142, 10, 140, 10,
    146, 10, 147, 10, 161, 10, 162, 10,
    163, 10, 144, 10, 237, 30, 236, 30,
    0, 0,
};

s32 audience_item_puni[] = {
    121, 10, 123, 10, 124, 10, 152, 30,
    154, 20, 155, 5, 156, 1, 153, 10,
    157, 10, 158, 10, 0, 0,
};

s32 audience_item_nokonoko[] = {
    121, 10, 123, 10, 124, 10, 143, 10,
    139, 10, 237, 10, 236, 10, 0, 0,
};

s32 audience_item_luigi[] = {
    121, 10, 123, 10, 124, 10, 148, 10,
    149, 10, 150, 10, 154, 10, 155, 10,
    156, 10, 130, 10, 237, 10, 0, 0,
};

s32 audience_kind[] = {
    0, (s32)audience_anim_kinopio, (s32)audience_item_kinopio, 1092616192, 1103626240, 1077936128, 1065353216, 1065353216,
    0, (s32)audience_anim_daisan, (s32)audience_item_daisan, 1092616192, 1103626240, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_teresa, (s32)audience_item_teresa, 0, 1106247680, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_hammer_bros, (s32)audience_item_hammer_bros, 1092616192, 1101004800, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_honenoko, (s32)audience_item_honenoko, 1092616192, 1103626240, 0, 1065353216, 1065353216,
    0, (s32)audience_anim_heiho, (s32)audience_item_heiho, 1092616192, 1103626240, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_pansy, (s32)audience_item_pansy, 1092616192, 1092616192, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_puni, (s32)audience_item_puni, 1092616192, 1101004800, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_nokonoko, (s32)audience_item_nokonoko, 1092616192, 1103626240, 1065353216, 1065353216, 1065353216,
    16777216, (s32)audience_anim_heavy_bomb, (s32)audience_item_heavy_bomb, 0, 1112014848, 1065353216, 1069547520, 1069547520,
    0, (s32)audience_anim_kuriboo, (s32)audience_item_kuriboo, 1092616192, 1103626240, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_pakkun, (s32)audience_item_pakkun, 0, 1101004800, 1065353216, 1065353216, 1065353216,
    0, (s32)audience_anim_luigi, (s32)audience_item_luigi, 0, 1109393408, 1065353216, 1067030938, 1067030938,
};

s32 audience_kinopio_wait_front[] = {
    -4, 0, -2, 0, 8, -5, 0, -1,
};

s32 audience_kinopio_wait_back[] = {
    -4, 0, -2, 1, 8, -5, 0, -1,
};

s32 audience_kinopio_jump_front[] = {
    -4, 0, -2, 2, 8, -5, 0, -1,
};

s32 audience_kinopio_jump_back[] = {
    -4, 0, -2, 3, 8, -5, 0, -1,
};

s32 audience_kinopio_raise_back[] = {
    -4, 0, -2, 4, 8, -5, 0, -1,
};

s32 audience_kinopio_itemon_back[] = {
    -4, 0, -2, 6, 8, -5, 0, -1,
};

s32 audience_kinopio_itemthrow_back[] = {
    -2, 7, 32, -1,
};

s32 audience_kinopio_tumble_front[] = {
    -4, 0, -2, 11, 8, -5, 0, -1,
};

s32 audience_kinopio_damage_front[] = {
    -2, 11, 32, -1,
};

s32 audience_kinopio_sleep_front[] = {
    -4, 0, -2, 12, 8, -5, 0, -1,
};

s32 audience_kinopio_sleep_back[] = {
    -4, 0, -2, 13, 8, -5, 0, -1,
};

s32 audience_kinopio_confuse_front[] = {
    -4, 0, -2, 14, 8, -5, 0, -1,
};

s32 audience_kinopio_confuse_back[] = {
    -4, 0, -2, 15, 8, -5, 0, -1,
};

s32 audience_daisan_wait_front[] = {
    -4, 0, -2, 16, 8, -5, 0, -1,
};

s32 audience_daisan_wait_back[] = {
    -4, 0, -2, 17, 8, -5, 0, -1,
};

s32 audience_daisan_jump_front[] = {
    -4, 0, -2, 18, 8, -5, 0, -1,
};

s32 audience_daisan_jump_back[] = {
    -4, 0, -2, 19, 8, -5, 0, -1,
};

s32 audience_daisan_raise_back[] = {
    -4, 0, -2, 21, 8, -5, 0, -1,
};

s32 audience_daisan_itemon_back[] = {
    -4, 0, -2, 22, 8, -5, 0, -1,
};

s32 audience_daisan_itemthrow_back[] = {
    -2, 23, 32, -1,
};

s32 audience_daisan_tumble_front[] = {
    -4, 0, -2, 27, 8, -5, 0, -1,
};

s32 audience_daisan_damage_front[] = {
    -2, 27, 32, -1,
};

s32 audience_daisan_sleep_front[] = {
    -4, 0, -2, 28, 8, -5, 0, -1,
};

s32 audience_daisan_sleep_back[] = {
    -4, 0, -2, 29, 8, -5, 0, -1,
};

s32 audience_daisan_confuse_front[] = {
    -4, 0, -2, 30, 8, -5, 0, -1,
};

s32 audience_daisan_confuse_back[] = {
    -4, 0, -2, 31, 8, -5, 0, -1,
};

s32 audience_teresa_wait_front[] = {
    -4, 0, -2, 32, 8, -5, 0, -1,
};

s32 audience_teresa_wait_back[] = {
    -4, 0, -2, 33, 8, -5, 0, -1,
};

s32 audience_teresa_jump_front[] = {
    -4, 0, -2, 34, 8, -5, 0, -1,
};

s32 audience_teresa_jump_back[] = {
    -4, 0, -2, 35, 8, -5, 0, -1,
};

s32 audience_teresa_raise_back[] = {
    -4, 0, -2, 36, 8, -5, 0, -1,
};

s32 audience_teresa_itemon_back[] = {
    -4, 0, -2, 38, 8, -5, 0, -1,
};

s32 audience_teresa_itemthrow_back[] = {
    -2, 39, 32, -1,
};

s32 audience_teresa_tumble_front[] = {
    -4, 0, -2, 43, 8, -5, 0, -1,
};

s32 audience_teresa_damage_front[] = {
    -2, 43, 32, -1,
};

s32 audience_teresa_sleep_front[] = {
    -4, 0, -2, 44, 8, -5, 0, -1,
};

s32 audience_teresa_sleep_back[] = {
    -4, 0, -2, 45, 8, -5, 0, -1,
};

s32 audience_teresa_confuse_front[] = {
    -4, 0, -2, 46, 8, -5, 0, -1,
};

s32 audience_teresa_confuse_back[] = {
    -4, 0, -2, 47, 8, -5, 0, -1,
};

s32 audience_hammer_bros_wait_front[] = {
    -4, 0, -2, 50, 8, -5, 0, -1,
};

s32 audience_hammer_bros_wait_back[] = {
    -4, 0, -2, 51, 8, -5, 0, -1,
};

s32 audience_hammer_bros_jump_front[] = {
    -4, 0, -2, 52, 8, -5, 0, -1,
};

s32 audience_hammer_bros_jump_back[] = {
    -4, 0, -2, 53, 8, -5, 0, -1,
};

s32 audience_hammer_bros_raise_back[] = {
    -4, 0, -2, 55, 8, -5, 0, -1,
};

s32 audience_hammer_bros_itemon_back[] = {
    -4, 0, -2, 56, 8, -5, 0, -1,
};

s32 audience_hammer_bros_itemthrow_back[] = {
    -2, 57, 32, -1,
};

s32 audience_hammer_bros_tumble_front[] = {
    -4, 0, -2, 61, 8, -5, 0, -1,
};

s32 audience_hammer_bros_damage_front[] = {
    -2, 61, 32, -1,
};

s32 audience_hammer_bros_sleep_front[] = {
    -4, 0, -2, 62, 8, -5, 0, -1,
};

s32 audience_hammer_bros_sleep_back[] = {
    -4, 0, -2, 63, 8, -5, 0, -1,
};

s32 audience_hammer_bros_confuse_front[] = {
    -4, 0, -2, 64, 8, -5, 0, -1,
};

s32 audience_hammer_bros_confuse_back[] = {
    -4, 0, -2, 65, 8, -5, 0, -1,
};

s32 audience_honenoko_wait_front[] = {
    -4, 0, -2, 66, 8, -5, 0, -1,
};

s32 audience_honenoko_wait_back[] = {
    -4, 0, -2, 67, 8, -5, 0, -1,
};

s32 audience_honenoko_jump_front[] = {
    -4, 0, -2, 68, 8, -5, 0, -1,
};

s32 audience_honenoko_jump_back[] = {
    -4, 0, -2, 69, 8, -5, 0, -1,
};

s32 audience_honenoko_raise_back[] = {
    -4, 0, -2, 71, 8, -5, 0, -1,
};

s32 audience_honenoko_itemon_back[] = {
    -4, 0, -2, 72, 8, -5, 0, -1,
};

s32 audience_honenoko_itemthrow_back[] = {
    -2, 73, 32, -1,
};

s32 audience_honenoko_tumble_front[] = {
    -4, 0, -2, 77, 8, -5, 0, -1,
};

s32 audience_honenoko_damage_front[] = {
    -2, 77, 32, -1,
};

s32 audience_honenoko_sleep_front[] = {
    -4, 0, -2, 78, 8, -5, 0, -1,
};

s32 audience_honenoko_sleep_back[] = {
    -4, 0, -2, 79, 8, -5, 0, -1,
};

s32 audience_honenoko_confuse_front[] = {
    -4, 0, -2, 80, 8, -5, 0, -1,
};

s32 audience_honenoko_confuse_back[] = {
    -4, 0, -2, 81, 8, -5, 0, -1,
};

s32 audience_heiho_wait_front[] = {
    -4, 0, -2, 82, 8, -5, 0, -1,
};

s32 audience_heiho_wait_back[] = {
    -4, 0, -2, 83, 8, -5, 0, -1,
};

s32 audience_heiho_jump_front[] = {
    -4, 0, -2, 84, 8, -5, 0, -1,
};

s32 audience_heiho_jump_back[] = {
    -4, 0, -2, 85, 8, -5, 0, -1,
};

s32 audience_heiho_raise_back[] = {
    -4, 0, -2, 87, 8, -5, 0, -1,
};

s32 audience_heiho_itemon_back[] = {
    -4, 0, -2, 88, 8, -5, 0, -1,
};

s32 audience_heiho_itemthrow_back[] = {
    -2, 89, 32, -1,
};

s32 audience_heiho_tumble_front[] = {
    -4, 0, -2, 93, 8, -5, 0, -1,
};

s32 audience_heiho_damage_front[] = {
    -2, 93, 32, -1,
};

s32 audience_heiho_sleep_front[] = {
    -4, 0, -2, 94, 8, -5, 0, -1,
};

s32 audience_heiho_sleep_back[] = {
    -4, 0, -2, 95, 8, -5, 0, -1,
};

s32 audience_heiho_confuse_front[] = {
    -4, 0, -2, 96, 8, -5, 0, -1,
};

s32 audience_heiho_confuse_back[] = {
    -4, 0, -2, 97, 8, -5, 0, -1,
};

s32 audience_pansy_wait_front[] = {
    -4, 0, -2, 100, 8, -5, 0, -1,
};

s32 audience_pansy_wait_back[] = {
    -4, 0, -2, 101, 8, -5, 0, -1,
};

s32 audience_pansy_jump_front[] = {
    -4, 0, -2, 102, 8, -5, 0, -1,
};

s32 audience_pansy_jump_back[] = {
    -4, 0, -2, 103, 8, -5, 0, -1,
};

s32 audience_pansy_raise_back[] = {
    -4, 0, -2, 104, 8, -5, 0, -1,
};

s32 audience_pansy_itemon_back[] = {
    -4, 0, -2, 106, 8, -5, 0, -1,
};

s32 audience_pansy_itemthrow_back[] = {
    -2, 107, 32, -1,
};

s32 audience_pansy_tumble_front[] = {
    -4, 0, -2, 111, 8, -5, 0, -1,
};

s32 audience_pansy_damage_front[] = {
    -2, 111, 32, -1,
};

s32 audience_pansy_sleep_front[] = {
    -4, 0, -2, 112, 8, -5, 0, -1,
};

s32 audience_pansy_sleep_back[] = {
    -4, 0, -2, 113, 8, -5, 0, -1,
};

s32 audience_pansy_confuse_front[] = {
    -4, 0, -2, 114, 8, -5, 0, -1,
};

s32 audience_pansy_confuse_back[] = {
    -4, 0, -2, 115, 8, -5, 0, -1,
};

s32 audience_pansy_sing_front[] = {
    -4, 0, -2, 116, 16, -2, 117, 16,
    -5, 0, -1,
};

s32 audience_puni_wait_front[] = {
    -4, 0, -2, 118, 8, -5, 0, -1,
};

s32 audience_puni_wait_back[] = {
    -4, 0, -2, 119, 8, -5, 0, -1,
};

s32 audience_puni_jump_front[] = {
    -4, 0, -2, 120, 8, -5, 0, -1,
};

s32 audience_puni_jump_back[] = {
    -4, 0, -2, 121, 8, -5, 0, -1,
};

s32 audience_puni_raise_back[] = {
    -4, 0, -2, 123, 8, -5, 0, -1,
};

s32 audience_puni_itemon_back[] = {
    -4, 0, -2, 124, 8, -5, 0, -1,
};

s32 audience_puni_itemthrow_back[] = {
    -2, 125, 32, -1,
};

s32 audience_puni_tumble_front[] = {
    -4, 0, -2, 129, 8, -5, 0, -1,
};

s32 audience_puni_damage_front[] = {
    -2, 129, 32, -1,
};

s32 audience_puni_sleep_front[] = {
    -4, 0, -2, 130, 8, -5, 0, -1,
};

s32 audience_puni_sleep_back[] = {
    -4, 0, -2, 131, 8, -5, 0, -1,
};

s32 audience_puni_confuse_front[] = {
    -4, 0, -2, 132, 8, -5, 0, -1,
};

s32 audience_puni_confuse_back[] = {
    -4, 0, -2, 133, 8, -5, 0, -1,
};

s32 audience_nokonoko_wait_front[] = {
    -4, 0, -2, 134, 8, -5, 0, -1,
};

s32 audience_nokonoko_wait_back[] = {
    -4, 0, -2, 135, 8, -5, 0, -1,
};

s32 audience_nokonoko_jump_front[] = {
    -4, 0, -2, 136, 8, -5, 0, -1,
};

s32 audience_nokonoko_jump_back[] = {
    -4, 0, -2, 137, 8, -5, 0, -1,
};

s32 audience_nokonoko_raise_back[] = {
    -4, 0, -2, 138, 8, -5, 0, -1,
};

s32 audience_nokonoko_itemon_back[] = {
    -4, 0, -2, 140, 8, -5, 0, -1,
};

s32 audience_nokonoko_itemthrow_back[] = {
    -2, 141, 32, -1,
};

s32 audience_nokonoko_tumble_front[] = {
    -4, 0, -2, 145, 8, -5, 0, -1,
};

s32 audience_nokonoko_damage_front[] = {
    -2, 145, 32, -1,
};

s32 audience_nokonoko_sleep_front[] = {
    -4, 0, -2, 146, 8, -5, 0, -1,
};

s32 audience_nokonoko_sleep_back[] = {
    -4, 0, -2, 147, 8, -5, 0, -1,
};

s32 audience_nokonoko_confuse_front[] = {
    -4, 0, -2, 148, 8, -5, 0, -1,
};

s32 audience_nokonoko_confuse_back[] = {
    -4, 0, -2, 149, 8, -5, 0, -1,
};

s32 audience_nokonoko_shell_back[] = {
    -4, 0, -2, 150, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_wait_front[] = {
    -4, 0, -2, 151, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_wait_back[] = {
    -4, 0, -2, 152, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_jump_front[] = {
    -4, 0, -2, 153, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_jump_back[] = {
    -4, 0, -2, 154, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_raise_back[] = {
    -4, 0, -2, 156, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_itemon_back[] = {
    -4, 0, -2, 157, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_itemthrow_back[] = {
    -2, 158, 32, -1,
};

s32 audience_heavy_bomb_tumble_front[] = {
    -4, 0, -2, 162, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_damage_front[] = {
    -2, 162, 32, -1,
};

s32 audience_heavy_bomb_sleep_front[] = {
    -4, 0, -2, 163, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_sleep_back[] = {
    -4, 0, -2, 164, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_confuse_front[] = {
    -4, 0, -2, 165, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_confuse_back[] = {
    -4, 0, -2, 166, 8, -5, 0, -1,
};

s32 audience_heavy_bomb_ignite_front[] = {
    -4, 0, -2, 167, 2, -2, 168, 2,
    -5, 0, -1,
};

s32 audience_heavy_bomb_ignite_back[] = {
    -4, 0, -2, 169, 2, -2, 170, 2,
    -5, 0, -1,
};

s32 audience_kuriboo_wait_front[] = {
    -4, 0, -2, 171, 8, -5, 0, -1,
};

s32 audience_kuriboo_wait_back[] = {
    -4, 0, -2, 172, 8, -5, 0, -1,
};

s32 audience_kuriboo_jump_front[] = {
    -4, 0, -2, 173, 8, -5, 0, -1,
};

s32 audience_kuriboo_jump_back[] = {
    -4, 0, -2, 174, 8, -5, 0, -1,
};

s32 audience_kuriboo_raise_back[] = {
    -4, 0, -2, 175, 8, -5, 0, -1,
};

s32 audience_kuriboo_itemon_back[] = {
    -4, 0, -2, 177, 8, -5, 0, -1,
};

s32 audience_kuriboo_itemthrow_back[] = {
    -2, 178, 32, -1,
};

s32 audience_kuriboo_tumble_front[] = {
    -4, 0, -2, 182, 8, -5, 0, -1,
};

s32 audience_kuriboo_damage_front[] = {
    -2, 182, 32, -1,
};

s32 audience_kuriboo_sleep_front[] = {
    -4, 0, -2, 183, 8, -5, 0, -1,
};

s32 audience_kuriboo_sleep_back[] = {
    -4, 0, -2, 184, 8, -5, 0, -1,
};

s32 audience_kuriboo_confuse_front[] = {
    -4, 0, -2, 185, 8, -5, 0, -1,
};

s32 audience_kuriboo_confuse_back[] = {
    -4, 0, -2, 186, 8, -5, 0, -1,
};

s32 audience_pakkun_wait_front[] = {
    -4, 0, -2, 187, 8, -5, 0, -1,
};

s32 audience_pakkun_wait_back[] = {
    -4, 0, -2, 188, 8, -5, 0, -1,
};

s32 audience_pakkun_jump_front[] = {
    -4, 0, -2, 189, 8, -5, 0, -1,
};

s32 audience_pakkun_jump_back[] = {
    -4, 0, -2, 190, 8, -5, 0, -1,
};

s32 audience_pakkun_raise_back[] = {
    -4, 0, -2, 192, 8, -5, 0, -1,
};

s32 audience_pakkun_itemon_back[] = {
    -4, 0, -2, 193, 8, -5, 0, -1,
};

s32 audience_pakkun_itemthrow_back[] = {
    -2, 194, 32, -1,
};

s32 audience_pakkun_tumble_front[] = {
    -4, 0, -2, 198, 8, -5, 0, -1,
};

s32 audience_pakkun_damage_front[] = {
    -2, 198, 32, -1,
};

s32 audience_pakkun_sleep_front[] = {
    -4, 0, -2, 199, 8, -5, 0, -1,
};

s32 audience_pakkun_sleep_back[] = {
    -4, 0, -2, 200, 8, -5, 0, -1,
};

s32 audience_pakkun_confuse_front[] = {
    -4, 0, -2, 201, 8, -5, 0, -1,
};

s32 audience_pakkun_confuse_back[] = {
    -4, 0, -2, 202, 8, -5, 0, -1,
};

s32 audience_pakkun_eat_front[] = {
    -2, 203, 10, -2, 204, 10, -1,
};

s32 audience_luigi_wait_front[] = {
    -4, 0, -2, 0, 8, -5, 0, -1,
};

s32 audience_luigi_wait_back[] = {
    -4, 0, -2, 1, 8, -5, 0, -1,
};

s32 audience_luigi_jump_front[] = {
    -4, 0, -2, 2, 8, -5, 0, -1,
};

s32 audience_luigi_jump_back[] = {
    -4, 0, -2, 3, 8, -5, 0, -1,
};

s32 audience_luigi_raise_back[] = {
    -4, 0, -2, 5, 8, -5, 0, -1,
};

s32 audience_luigi_itemon_back[] = {
    -4, 0, -2, 6, 8, -5, 0, -1,
};

s32 audience_luigi_itemthrow_back[] = {
    -2, 7, 32, -1,
};

s32 audience_luigi_tumble_front[] = {
    -4, 0, -2, 11, 8, -5, 0, -1,
};

s32 audience_luigi_damage_front[] = {
    -2, 11, 32, -1,
};

s32 audience_luigi_sleep_front[] = {
    -4, 0, -2, 12, 8, -5, 0, -1,
};

s32 audience_luigi_sleep_back[] = {
    -4, 0, -2, 13, 8, -5, 0, -1,
};

s32 audience_luigi_confuse_front[] = {
    -4, 0, -2, 14, 8, -5, 0, -1,
};

s32 audience_luigi_confuse_back[] = {
    -4, 0, -2, 15, 8, -5, 0, -1,
};

s32 audience_item_daisan[] = {
    237, 10, 236, 10, 0, 0,
};

s32 audience_item_teresa[] = {
    136, 10, 134, 20, 177, 10, 237, 10,
    236, 10, 0, 0,
};

s32 audience_item_hammer_bros[] = {
    239, 10, 0, 0,
};

s32 audience_item_honenoko[] = {
    238, 10, 237, 10, 236, 10, 0, 0,
};

s32 audience_item_pansy[] = {
    0, 0,
};

s32 audience_item_heavy_bomb[] = {
    0, 0,
};

s32 audience_item_kuriboo[] = {
    237, 20, 236, 20, 0, 0,
};

s32 audience_item_pakkun[] = {
    0, 0,
};

