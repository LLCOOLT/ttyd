#include "evt/evt_cmd.h"
#include "evt/evt_npc.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/mobjdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include <dolphin/gx.h>
#include <string.h>
static void piders_draw_yarn_sub(CameraId cameraId, void* param);

double sqrt(double);
double sin(double);
double cos(double);
double __fabs(double);
#define fabs(x) __fabs(x)

EffectEntry* effFireEntry(f32 x, f32 y, f32 z, f32 scale, s32 type, s32 life);
EffectEntry* effMagic1N64Entry(s32 a, s32 b, f32 x, f32 y, f32 z, f32 w, f32 v, f32 u);
s32 kpaGetLevel(void);
BOOL npcCheckBlow(NpcEntry* npc);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* ab);

// functions are defined in reverse of target order (deferred inlining)

USER_FUNC(mahoon_get_groupname) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    evtSetValue(event, args[0], ((s32*)npc->tribe)[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(npc_check_wall_stop) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    if (npc->wallHit) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_wait_blow_end) {
    const char* nm = (const char*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, nm);
    if (npcCheckBlow(npc)) {
        npc->rotation.y += 18.0f;
        return EVT_RETURN_BLOCK;
    }
    npc->rotation.y = 0.0f;
    return EVT_RETURN_DONE;
}

USER_FUNC(pressCheck) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    f32 hx, hy, hz, dist, nx, ny, nz;
    if (kpaGetLevel() == 0) {
        evtSetValue(event, args[0], 0);
        return EVT_RETURN_DONE;
    }
    dist = 5.0f;
    if (hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, 1.0f + npc->position.y, npc->position.z, 0.0f, -1.0f, 0.0f)) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_2d_dead_jump) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    f32 tx = evtGetFloat(event, args[1]);
    f32 ty = evtGetFloat(event, args[2]);
    f32 tz = evtGetFloat(event, args[3]);
    f32 t = (f32)evtGetValue(event, args[4]) / 1000.0f;
    f32 spd = evtGetFloat(event, args[5]);
    f32 vy = evtGetFloat(event, args[6]);
    f32 gy = (f32)evtGetValue(event, args[7]);
    f32 h;
    NpcEntry* npc;
    Vec d;
    npc = evtNpcNameToPtr(event, (const char*)id);
    h = vy;
    npc->jumpFlags |= 0x10;
    npc->jumpFlags |= 0x1000;
    if (isFirstCall) {
        npc->flags |= 0x20000;
        npc->flags &= ~0x40000010;
        npc->field_188 = 0;
        npc->field_178 = 0;
        npc->field_108 = 0;
        npc->jumpTargetPos.x = tx;
        npc->jumpTargetPos.y = ty;
        npc->jumpTargetPos.z = tz;
        npc->jumpStartPos = npc->position;
        PSVECSubtract(&npc->jumpTargetPos, &npc->jumpStartPos, &d);
        if (d.x * d.x + d.z * d.z > 0.0f) {
            d.y = d.y;
        } else {
            d.y = d.y;
        }
        npc->moveDir = angleABf(0.0f, 0.0f, d.x, d.z);
        if (t > 0.0f) {
            npc->moveSpeed = fabs(tx - npc->position.x) / t;
        } else {
            npc->moveSpeed = spd;
        }
        npc->moveTime = 0.0f;
        npc->moveOffset.y = 0.0f;
        npc->jumpVelY = 0.0f;
        npc->jumpYScale = 1.0f;
        {
            f32 dy = npc->jumpTargetPos.y - npc->jumpStartPos.y;
            if (vy) {
                f32 g, half, apex;
                if (dy > 0.0f) {
                    h += dy;
                }
                npc->jumpVelY = 0.0f;
                if (t == 0.0f) {
                    npc->jumpVelY = vy;
                } else {
                    g = -980.0f * npc->jumpGravity;
                    half = 0.5f * t;
                    npc->jumpVelY = -(t * (g * t)) / t;
                    apex = npc->jumpVelY * half + half * (-980.0f * npc->jumpGravity * half);
                    if (apex != 0.0f) {
                        npc->jumpYScale = h / apex;
                    }
                }
            } else {
                if (dy >= 0.0f) {
                    return 1;
                }
            }
        }
        return 0;
    }
    {
        f32 s = (f32)sin(6.2831855f * npc->moveDir / 360.0f);
        npc->moveOffset.x += npc->moveDt * (npc->moveSpeed * s);
    }
    {
        f32 c = (f32)cos(6.2831855f * npc->moveDir / 360.0f);
        npc->moveOffset.z += npc->moveDt * (npc->moveSpeed * -c);
    }
    if (npc->position.y >= gy) {
        return 0;
    }
    npc->moveSpeed = 0.0f;
    npc->jumpVelY = 0.0f;
    npc->jumpYScale = 1.0f;
    npc->jumpGravity = 1.0f;
    return 1;
}

USER_FUNC(_2d_get_dead_jump_offset) {
    s32* args = event->args;
    f32 d;
    f32 k;
    const char* nm = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc = evtNpcNameToPtr(event, nm);
    s32 out = args[1];
    MarioWork* mario = marioGetPtr();
    if (mario->position.x == npc->position.x) {
        d = 0.0f;
    } else if (mario->position.x > npc->position.x) {
        d = -1.0f;
    } else {
        d = 1.0f;
    }
    k = 20.0f;
    k *= d;
    evtSetValue(event, out, (s32)k);
    return EVT_RETURN_DONE;
}

USER_FUNC(killer_make_name) {
    static char name[32];
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    s32 n = evtGetValue(event, args[0]);
    s32 len;
    strcpy(name, npc->description);
    len = strlen(name);
    name[len] = n + 0x31;
    name[len + 1] = 0;
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}

USER_FUNC(piders_get_height) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    evtSetFloat(event, args[0], npc->territoryLoiter.z);
    return EVT_RETURN_DONE;
}




















USER_FUNC(evt_eff);
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_fbat_trans_floor_position);
USER_FUNC(evt_get_target_dir);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_npc_add_dirdist);
USER_FUNC(evt_npc_add_rotate);
USER_FUNC(evt_npc_blur_onoff);
USER_FUNC(evt_npc_calc_score);
USER_FUNC(evt_npc_change_interrupt);
USER_FUNC(evt_npc_delete);
USER_FUNC(evt_npc_facedirection_add);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_get_btlsetup_work);
USER_FUNC(evt_npc_get_dir);
USER_FUNC(evt_npc_get_drop_coin);
USER_FUNC(evt_npc_get_drop_fixitem);
USER_FUNC(evt_npc_get_drop_flower);
USER_FUNC(evt_npc_get_drop_heart);
USER_FUNC(evt_npc_get_drop_item);
USER_FUNC(evt_npc_get_home_position);
USER_FUNC(evt_npc_get_kpencount_type);
USER_FUNC(evt_npc_get_loiter_dir);
USER_FUNC(evt_npc_get_position);
USER_FUNC(evt_npc_get_unitwork);
USER_FUNC(evt_npc_getback_item_entry);
USER_FUNC(evt_npc_glide_position);
USER_FUNC(evt_npc_homing_target);
USER_FUNC(evt_npc_jump_position);
USER_FUNC(evt_npc_move_position);
USER_FUNC(evt_npc_pera_onoff);
USER_FUNC(evt_npc_restart_regular_event);
USER_FUNC(evt_npc_return_interrupt);
USER_FUNC(evt_npc_reverse_ry);
USER_FUNC(evt_npc_set_anim);
USER_FUNC(evt_npc_set_attack_mode);
USER_FUNC(evt_npc_set_btlsetup_work);
USER_FUNC(evt_npc_set_confuse_anim);
USER_FUNC(evt_npc_set_damage_anim);
USER_FUNC(evt_npc_set_height);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_npc_set_rotate);
USER_FUNC(evt_npc_set_run_anim);
USER_FUNC(evt_npc_set_ry);
USER_FUNC(evt_npc_set_scale);
USER_FUNC(evt_npc_set_stay_anim);
USER_FUNC(evt_npc_set_talk_anim);
USER_FUNC(evt_npc_set_tribe);
USER_FUNC(evt_npc_set_unitwork);
USER_FUNC(evt_npc_set_walk_anim);
USER_FUNC(evt_npc_set_width);
USER_FUNC(evt_npc_slave_entry);
USER_FUNC(evt_npc_sound_data_reset);
USER_FUNC(evt_npc_sound_data_set);
USER_FUNC(evt_npc_status_onoff);
USER_FUNC(evt_npc_wait_msec);
USER_FUNC(evt_set_dir_to_home);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_random);
USER_FUNC(piders_draw_yawn);
USER_FUNC(urouro_init_func);
USER_FUNC(urouro_main_func);
USER_FUNC(gesso_ground_check);
USER_FUNC(set_bottle_flag_init);
USER_FUNC(unk_800ece0c);
USER_FUNC(zakoEntryFall);
USER_FUNC(dokanCheck);
USER_FUNC(zakoEntryDokan);
USER_FUNC(limitSpd);
USER_FUNC(getSpdRun);
USER_FUNC(getSpdWalk);
USER_FUNC(upperCheck);
USER_FUNC(cliffCheck);
USER_FUNC(camGetPos);
USER_FUNC(chain_main);
USER_FUNC(kamec_fire_magic_delete);
USER_FUNC(kamec_fire_magic);
extern s32 evt_eff64[];
extern s32 evt_mario_get_mov_spd[];
extern s32 evt_npc_set_color[];
extern s32 evt_npc_status_check[];

s32 enemy_common_dead_event[156];
s32 enemy_event_dead_event_sub[36];
s32 enemy_common_blow_event[13];
s32 enemy_2d_common_dead_event[415];
s32 _2d_dead_rotate_event[16];
s32 unk_evt_8033d458[13];
s32 npc_urouro_move_event[21];
s32 npc_urouro_return_event[37];
s32 kuriboo_move_event[39];
s32 kuriboo_find_event[54];
s32 kuriboo_lost_event[31];
s32 kuriboo_return_event[37];
s32 patakuri_move_event[148];
s32 patakuri_find_event[90];
s32 patakuri_lost_event[31];
s32 patakuri_return_event[170];
s32 nokonoko_shell_return_event[50];
s32 nokonoko_init_event[28];
s32 nokonoko_move_event[58];
s32 nokonoko_find_event[172];
s32 nokonoko_lost_event[46];
s32 nokonoko_return_event[55];
s32 togenoko_shell_return_event[50];
s32 togenoko_init_event[28];
s32 togenoko_move_event[58];
s32 togenoko_find_event[172];
s32 togenoko_lost_event[46];
s32 togenoko_return_event[55];
s32 patapata_move_event[123];
s32 patapata_find_event[131];
s32 patapata_lost_event[44];
s32 patapata_return_event[135];
s32 met_init_event_common[21];
s32 met_set_anim_wait_event[48];
s32 met_set_anim_walk_event[48];
s32 met_init_event[19];
s32 met_init_event_ceil[14];
s32 togemet_init_event[19];
s32 togemet_init_event_ceil[14];
s32 met_move_event[54];
s32 met_find_event[269];
s32 met_lost_event[43];
s32 met_return_event[51];
s32 patamet_move_event[151];
s32 patamet_find_event[108];
s32 patamet_lost_event[34];
s32 patamet_return_event[143];
s32 chorobon_move_event[69];
s32 chorobon_find_event[63];
s32 chorobon_lost_event[14];
s32 chorobon_return_event[43];
s32 pansy_move_event[42];
s32 pansy_find_event[46];
s32 pansy_lost_event[35];
s32 pansy_return_event[45];
s32 twinkling_pansy_move_event[42];
s32 twinkling_pansy_find_event[54];
s32 twinkling_pansy_lost_event[35];
s32 twinkling_pansy_return_event[45];
s32 karon_init_event[36];
s32 karon_move_event[57];
s32 karon_find_event[150];
s32 karon_lost_event[18];
s32 karon_return_event[37];
s32 karon_blow_event[19];
s32 honenoko2_init_event[18];
s32 honenoko2_move_event[49];
s32 honenoko2_find_event[58];
s32 honenoko2_lost_event[36];
s32 honenoko2_return_event[46];
s32 killer_init_event[19];
s32 killer_move_event[79];
s32 killer_dead_event[156];
s32 killer_cannon_init_event[13];
s32 killer_cannon_move_event[157];
s32 sambo_move_event[22];
s32 sambo_find_event[33];
s32 sambo_lost_event[22];
s32 sambo_return_event[30];
s32 sinnosuke_init_event[26];
s32 sinnosuke_move_event[21];
s32 sinnosuke_find_event[146];
s32 sinnosuke_lost_event[36];
s32 sinnosuke_return_event[94];
s32 sinemon_init_event[26];
s32 sinemon_move_event[26];
s32 sinemon_find_event[146];
s32 sinemon_lost_event[36];
s32 sinemon_return_event[94];
s32 togedaruma_move_event[49];
s32 togedaruma_find_event[61];
s32 togedaruma_lost_event[38];
s32 togedaruma_return_event[44];
s32 barriern_init_event[37];
s32 barriern_move_event[89];
s32 barriern2_move_event[70];
s32 barriern_dead_event[17];
s32 barriern_find_event[189];
s32 barriern_lost_event[17];
s32 barriern_return_event[42];
s32 barriern_blow_event[27];
s32 piders_move_event[111];
s32 piders_find_event[206];
s32 piders_blow_event[13];
s32 pakkun_attack_event[74];
s32 pakkun_init_event[34];
s32 pakkun_move_event[17];
s32 pakkun_find_event[106];
s32 pakkun_return_event[81];
s32 dokugassun_init_event[14];
s32 dokugassun_move_event[153];
s32 dokugassun_find_event[69];
s32 dokugassun_lost_event[27];
s32 dokugassun_return_event[158];
s32 basabasa_init_event[17];
s32 basabasa_move_event[67];
s32 basabasa_find_event[69];
s32 basabasa_lost_event[31];
s32 basabasa_return_event[44];
s32 basabasa2_move_event[148];
s32 basabasa2_find_event[60];
s32 basabasa2_lost_event[31];
s32 basabasa2_return_event[140];
s32 teresa_move_event[165];
s32 teresa_find_event[60];
s32 teresa_lost_event[31];
s32 teresa_return_event[104];
s32 bubble_move_event[159];
s32 bubble_find_event[63];
s32 bubble_lost_event[34];
s32 bubble_return_event[151];
s32 hbom_move_event[41];
s32 hbom_find_event[54];
s32 hbom_lost_event[31];
s32 hbom_return_event[37];
s32 zakowiz_init_event[38];
s32 zakowiz_move_event[70];
s32 zakowiz_find_event[159];
s32 zakowiz_lost_event[18];
s32 zakowiz_return_event[37];
s32 zakowiz_blow_event[19];
s32 hannya_move_event[37];
s32 hannya_find_event[86];
s32 hannya_lost_event[23];
s32 hannya_return_event[29];
s32 mahoon_init_event[120];
s32 mahoon_move_event[259];
s32 mahoon_dead_event[24];
s32 mahoon_find_event[177];
s32 mahoon_lost_event[142];
s32 mahoon_return_event[251];
s32 kamec_init_event[54];
s32 kamec_move_event[177];
s32 kamec_find_event[150];
s32 kamec_lost_event[31];
s32 kamec_return_event[150];
s32 kamec_blow_event[19];
s32 kamec2_init_event[54];
s32 kamec2_move_event[58];
s32 kamec2_find_event[153];
s32 kamec2_lost_event[31];
s32 kamec2_return_event[37];
s32 kamec2_blow_event[19];
s32 hbross_init_event[36];
s32 hbross_move_event[57];
s32 hbross_find_event[141];
s32 hbross_lost_event[18];
s32 hbross_return_event[37];
s32 hbross_blow_event[19];
s32 enemy_event_dead_event[10];
s32 enemy_slave_common_dead_event[8];
s32 enemy_common_flag_init_event[12];
s32 testenemynpc_init_event[4];
s32 npc_urouro_init_event[12];
s32 kuriboo_init_event[4];
s32 patakuri_init_event[12];
s32 patapata_init_event[12];
s32 patamet_init_event[12];
s32 chorobon_init_event[12];
s32 pansy_init_event[4];
s32 twinkling_pansy_init_event[4];
s32 karon_dead_event[9];
s32 sambo_init_event[12];
s32 togedaruma_init_event[4];
s32 piders_init_event[9];
s32 basabasa_dead_event[4];
s32 basabasa2_init_event[12];
s32 basabasa2_dead_event[4];
s32 teresa_init_event[12];
s32 teresa_dead_event[4];
s32 bubble_init_event[12];
s32 hbom_init_event[4];
s32 zakowiz_dead_event[9];
s32 hannya_init_event[9];
s32 kamec_dead_event[9];
s32 kamec2_dead_event[9];
s32 hbross_dead_event[9];
s32 zakoM2D_dead_event[9];
s32 wanwan_init_event[64];
s32 wanwan_init_event_sub[64];
s32 wanwan_move_event[151];
s32 wanwan_find_event[90];
s32 kuriboo2D_init_event[22];
s32 kuriboo2D_move_event[72];
s32 kuriboo2D_find_event[70];
s32 zako2D_init_event[27];
s32 zako2D_move_event[244];
s32 zako2D_find_event[74];
s32 dokan2D_init_event[19];
s32 dokan2D_regl_event[48];
s32 fall2D_init_event[19];
s32 fall2D_regl_event[34];
s32 zakoM2D_init_event[37];
s32 zakoM2D_move_event[95];
s32 zakoM2D_find_event[179];
s32 unk_evt_803497e8[88];
s32 gesso2D_init_event[34];
s32 gesso2D_move_event[262];

EVT_BEGIN(enemy_common_dead_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1024)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_damage_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_ENEMY_DIE1"), 0)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_drop_coin, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 121, LW(0), LW(1), LW(2), 10, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_heart, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 123, LW(0), LW(1), LW(2), 10, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_flower, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 124, LW(0), LW(1), LW(2), 10, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_item, STRING("me"), LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_item_entry, 0, LW(3), LW(0), LW(1), LW(2), 9, -1, 0)
    END_IF
    CALL(evt_npc_getback_item_entry, STRING("me"))
    CALL(evt_npc_get_drop_fixitem, STRING("me"), LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_item_entry, 0, LW(3), LW(0), LW(1), LW(2), 9, -1, 0)
    END_IF
    CALL(evt_npc_delete, STRING("me"))
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

// TODO: USER_FUNC(gesso_ground_check) { }

EVT_BEGIN(enemy_event_dead_event_sub)
    CALL(evt_npc_set_damage_anim, LW(10))
    WAIT_MS(500)
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_ENEMY_DIE1"), 0)
    CALL(evt_npc_delete, LW(10))
    RETURN
EVT_END()

EVT_BEGIN(enemy_common_blow_event)
    CALL(evt_npc_set_confuse_anim, STRING("me"))
    CALL(_wait_blow_end, STRING("me"))
    WAIT_MS(2000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(enemy_2d_common_dead_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 268435456)
    CALL(pressCheck, LW(15))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("me"), LW(0), LW(1), 200)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_ENEMY_DIE1"), 0)
    CALL(evt_npc_set_damage_anim, STRING("me"))
    CALL(evt_npc_get_kpencount_type, STRING("me"), LW(0))
    SWITCH(LW(0))
        CASE_FLAG(1)
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_calc_score, STRING("me"))
            SPAWN_EVENT(PTR(_2d_dead_rotate_event))
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
            ADD(LW(0), LW(3))
            CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(0.0f), -300)
            ELSE
            CALL(evt_npc_calc_score, STRING("me"))
            CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
            CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
            CALL(evt_npc_status_onoff, 0, STRING("me"), 2)
            CALL(evt_npc_set_talk_anim, STRING("me"))
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            SUBTRACT(LW(1), 5)
            CALL(evt_npc_set_position, STRING("me"), LW(0), LW(1), LW(2))
            WAIT_FRAMES(30)
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            BEGIN_SIBLING_EVENT
                LOOP(30)
                    CALL(evt_npc_add_rotate, STRING("me"), 0, 0, 1)
                    WAIT_FRAMES(1)
                END_LOOP
            END_SIBLING_EVENT
            SUBTRACT(LW(0), 40)
            SUBTRACT(LW(1), 20)
            CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, -10, 4, 0)
            LOOP(0)
                BEGIN_SIBLING_EVENT
                    LOOP(60)
                        CALL(evt_npc_add_rotate, STRING("me"), 0, 0, -1)
                        WAIT_FRAMES(1)
                    END_LOOP
                END_SIBLING_EVENT
                CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                ADD(LW(0), 80)
                SUBTRACT(LW(1), 20)
                CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 1000, 0, -10, 4, 0)
                BEGIN_SIBLING_EVENT
                    LOOP(60)
                        CALL(evt_npc_add_rotate, STRING("me"), 0, 0, 1)
                        WAIT_FRAMES(1)
                    END_LOOP
                END_SIBLING_EVENT
                CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                SUBTRACT(LW(0), 80)
                SUBTRACT(LW(1), 20)
                CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 1000, 0, -10, 4, 0)
                IF_INT_LESS_OR_EQUAL(LW(1), -200)
                    BREAK_LOOP
                END_IF
            END_LOOP
        END_IF
        CASE_FLAG(2)
        CALL(evt_npc_calc_score, STRING("me"))
        SPAWN_EVENT(PTR(_2d_dead_rotate_event))
        CALL(evt_npc_status_onoff, 1, STRING("me"), 4194304)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
        ADD(LW(0), LW(3))
        CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(65.0f), -300)
        CASE_FLAG(4)
        CALL(evt_npc_calc_score, STRING("me"))
        SPAWN_EVENT(PTR(_2d_dead_rotate_event))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
        ADD(LW(0), LW(3))
        CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(65.0f), -300)
        CASE_FLAG(32)
        SPAWN_EVENT(PTR(_2d_dead_rotate_event))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
        ADD(LW(0), LW(3))
        CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(65.0f), -300)
        CASE_FLAG(8)
        CALL(evt_npc_calc_score, STRING("me"))
        SPAWN_EVENT(PTR(_2d_dead_rotate_event))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
        ADD(LW(0), LW(3))
        CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(65.0f), -300)
        CASE_FLAG(16)
        CALL(evt_npc_calc_score, STRING("me"))
        SPAWN_EVENT(PTR(_2d_dead_rotate_event))
        CALL(evt_npc_status_onoff, 1, STRING("me"), 4194304)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(_2d_get_dead_jump_offset, STRING("me"), LW(3))
        ADD(LW(0), LW(3))
        CALL(_2d_dead_jump, STRING("me"), LW(0), LW(1), LW(2), 600, FLOAT(40.0f), FLOAT(65.0f), -300)
        CASE_DEFAULT
        WAIT_MS(500)
    END_SWITCH
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(_2d_dead_rotate_event)
    SET_VALUE(LW(0), -12)
    LOOP(15)
        CALL(evt_npc_add_rotate, STRING("me"), 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(unk_evt_8033d458)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    LABEL(0)
    WAIT_MS(500)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(npc_urouro_move_event)
    CALL_CHILD(PTR(npc_urouro_init_event))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(100.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(npc_urouro_return_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(kuriboo_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_sub_random, 360, LW(3))
    LABEL(0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(kuriboo_find_event)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
    CALL(evt_npc_homing_target, STRING("me"), STRING("mario"), 0, FLOAT(120.0f), FLOAT(10.0f), FLOAT(60.0f), 4)
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(kuriboo_lost_event)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(kuriboo_return_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patakuri_move_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_sub_random, 360, LW(3))
    LABEL(0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(10.0f), 0, 3)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(patakuri_find_event)
    CALL(evt_npc_set_run_anim, STRING("me"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_npc_add_dirdist, LW(1), LW(3), LW(0), FLOAT(100.0f))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 0, 75, FLOAT(-50.0f), 0, 3)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 1000, 0, 0, 0, 1)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patakuri_lost_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patakuri_return_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 1000, 0, 0, 0, 1)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_shell_return_event)
    CALL(evt_npc_get_unitwork, STRING("me"), 1, LW(15))
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
        CALL(evt_npc_set_unitwork, STRING("me"), 1, 0)
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
        CALL(evt_npc_set_stay_anim, STRING("me"))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_init_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1179672)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_move_event)
    CALL_CHILD(PTR(nokonoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_find_event)
    CALL_CHILD(PTR(nokonoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_NOKO_MOVE1"), 0, 0, 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 1, 1)
    CALL(evt_npc_set_attack_mode, STRING("me"), 11)
    CALL(evt_npc_set_anim, STRING("me"), STRING("NKT_A_1"))
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
    CALL(evt_npc_set_ry, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_NOKO_SHELL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(256.0f))
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_add_rotate, STRING("me"), 0, 40, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        LOOP(0)
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 800, FLOAT(400.0f), 4)
    DELETE_EVENT(LW(14))
    CALL_CHILD(PTR(nokonoko_shell_return_event))
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL_CHILD(PTR(nokonoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(nokonoko_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL_CHILD(PTR(nokonoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togenoko_shell_return_event)
    CALL(evt_npc_get_unitwork, STRING("me"), 1, LW(15))
    IF_INT_EQUAL(LW(15), 1)
        CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
        CALL(evt_npc_set_unitwork, STRING("me"), 1, 0)
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
        CALL(evt_npc_set_stay_anim, STRING("me"))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(togenoko_init_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1179672)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(togenoko_move_event)
    CALL_CHILD(PTR(togenoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(togenoko_find_event)
    CALL_CHILD(PTR(togenoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_NOKO_MOVE1"), 0, 0, 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 1, 1)
    CALL(evt_npc_set_attack_mode, STRING("me"), 11)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_1"))
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
    CALL(evt_npc_set_ry, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_NOKO_SHELL1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(256.0f))
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
            IF_INT_EQUAL(LW(15), 1)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_add_rotate, STRING("me"), 0, 40, 0)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(100)
    BEGIN_SIBLING_EVENT_GET_ID(LW(14))
        LOOP(0)
            CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
            ADD(LW(1), 10)
            CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
            WAIT_FRAMES(3)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 800, FLOAT(400.0f), 4)
    DELETE_EVENT(LW(14))
    CALL_CHILD(PTR(togenoko_shell_return_event))
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togenoko_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL_CHILD(PTR(togenoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togenoko_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL_CHILD(PTR(togenoko_shell_return_event))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patapata_move_event)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    SET_VALUE(LW(10), 0)
    LOOP(0)
        IF_INT_EQUAL(LW(10), 0)
            CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(-20.0f), FLOAT(20.0f))
        END_IF
        IF_INT_EQUAL(LW(10), 2)
            CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(-20.0f), FLOAT(20.0f))
        END_IF
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
        CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
        CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-7.0f), 0, 2)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
        CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
        CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(7.0f), 0, 2)
        IF_INT_GREATER_OR_EQUAL(LW(10), 4)
            BREAK_LOOP
        END_IF
        ADD(LW(10), 1)
    END_LOOP
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(patapata_find_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_pera_onoff, STRING("me"), 1)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    LOOP(18)
        CALL(evt_npc_add_rotate, STRING("me"), 0, 15, 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_anim, STRING("me"), STRING("PTP_A_5"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PATA_MOVE2"), LW(0), LW(1), LW(2), 0)
    LOOP(6)
        CALL(evt_npc_add_rotate, STRING("me"), 0, 15, 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 10)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_PATA_MOVE3"), 0, 0, 0, 0)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_npc_add_dirdist, LW(1), LW(3), LW(0), FLOAT(200.0f))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 1000, 0, FLOAT(-40.0f), 4, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patapata_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patapata_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(7.0f), 0, 2)
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-7.0f), 0, 2)
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(7.0f), 0, 2)
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(30.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-7.0f), 0, 2)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

s32 met_init_event_common[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 8, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)"me", 1048592, 262235, (s32)evt_npc_status_onoff, 1, (s32)"me", 2, 327771,
    (s32)evt_npc_set_rotate, (s32)"me", 0, 0, 0,
};

EVT_BEGIN(met_set_anim_wait_event)
    CALL(evt_npc_get_btlsetup_work, STRING("me"), 0, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("MET_S_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("TMT_S_1"))
        END_IF
        ELSE
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("SMT_S_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("STM_S_1"))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(met_set_anim_walk_event)
    CALL(evt_npc_get_btlsetup_work, STRING("me"), 0, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("MET_W_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("TMT_W_1"))
        END_IF
        ELSE
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("SMT_W_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("STM_W_1"))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(met_init_event)
    CALL_CHILD(PTR(met_init_event_common))
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 131072)
    CALL(evt_npc_set_btlsetup_work, STRING("me"), 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(met_init_event_ceil)
    CALL_CHILD(PTR(met_init_event_common))
    CALL(evt_npc_set_btlsetup_work, STRING("me"), 0, 1)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 0)
    RETURN
EVT_END()

EVT_BEGIN(togemet_init_event)
    CALL_CHILD(PTR(met_init_event_common))
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 131072)
    CALL(evt_npc_set_btlsetup_work, STRING("me"), 0, 0)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
    RETURN
EVT_END()

EVT_BEGIN(togemet_init_event_ceil)
    CALL_CHILD(PTR(met_init_event_common))
    CALL(evt_npc_set_btlsetup_work, STRING("me"), 0, 1)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
    RETURN
EVT_END()

EVT_BEGIN(met_move_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL_CHILD(PTR(met_set_anim_wait_event))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    WAIT_MS(500)
    CALL_CHILD(PTR(met_set_anim_walk_event))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(met_find_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_get_btlsetup_work, STRING("me"), 0, LW(15))
    IF_INT_EQUAL(LW(15), 0)
        CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
        CALL(evt_npc_set_attack_mode, STRING("me"), 11)
        CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_MET_ATTACK1"), 0, 0, 0, 0)
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("MET_A_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("TMT_A_1"))
        END_IF
        CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), LW(3))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(256.0f))
        BEGIN_SIBLING_EVENT
            SET_VALUE(LW(4), 0)
            SET_VALUE(LW(15), 0)
            LOOP(0)
                WAIT_FRAMES(1)
                ADD(LW(15), 1)
                IF_INT_GREATER_OR_EQUAL(LW(15), 55)
                    BREAK_LOOP
                END_IF
                ADD(LW(4), 40)
                CALL(evt_npc_set_rotate, STRING("me"), 0, LW(4), 0)
            END_LOOP
        END_SIBLING_EVENT
        WAIT_MS(100)
        BEGIN_SIBLING_EVENT_GET_ID(LW(14))
            LOOP(0)
                CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
                ADD(LW(1), 10)
                CALL(evt_eff, STRING(""), STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(0.2998047f), 0, 0, 0, 0, 0, 0, 0)
                WAIT_FRAMES(3)
            END_LOOP
        END_SIBLING_EVENT
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 800, FLOAT(400.0f), 4)
        DELETE_EVENT(LW(14))
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
        CALL_CHILD(PTR(met_set_anim_wait_event))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("me"), LW(0), LW(1), LW(2), 300, 0, FLOAT(20.0f), 0)
        ELSE
        CALL(evt_npc_set_attack_mode, STRING("me"), 11)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), 131072)
        CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(15))
        IF_INT_EQUAL(LW(15), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("SMT_A_1"))
            ELSE
            CALL(evt_npc_set_anim, STRING("me"), STRING("STM_A_1"))
        END_IF
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position, STRING("me"), LW(0), 0, LW(2), 0, 0, 0, 0)
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        CALL(evt_npc_set_btlsetup_work, STRING("me"), 0, 0)
        CALL_CHILD(PTR(met_set_anim_wait_event))
        WAIT_MS(1000)
    END_IF
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(met_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL_CHILD(PTR(met_set_anim_wait_event))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(met_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL_CHILD(PTR(met_set_anim_wait_event))
    WAIT_MS(500)
    CALL_CHILD(PTR(met_set_anim_walk_event))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patamet_move_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 0, 50, FLOAT(10.0f), 0, 3)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(patamet_find_event)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_PATAMET_MOVE2"), 0, 0, 0, 0)
    CALL(evt_npc_set_run_anim, STRING("me"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_npc_add_dirdist, LW(1), LW(3), LW(0), FLOAT(100.0f))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 0, 75, FLOAT(-50.0f), 0, 3)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(1), LW(2), LW(3))
    CALL(evt_fbat_trans_floor_position, LW(1), LW(2), LW(3), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(1), LW(2), LW(3), 1000, 0, 0, 0, 1)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patamet_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(patamet_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(-10.0f), 0, 3)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(25.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 50, 500)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, FLOAT(10.0f), 0, 3)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(chorobon_move_event)
    CALL(evt_npc_set_scale, STRING("me"), 1, 1, 1)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    LABEL(0)
    CALL(evt_sub_random, 3, LW(4))
    ADD(LW(4), 2)
    LOOP(LW(4))
        CALL(evt_sub_random, 360, LW(3))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), 50)
        CALL(evt_npc_jump_position, STRING("me"), LW(0), -10000, LW(2), 300, 0, FLOAT(30.0f), 0)
    END_LOOP
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
    CALL(evt_npc_set_ry, STRING("me"), LW(3))
    CALL(evt_sub_random, 500, LW(4))
    ADD(LW(4), 10)
    WAIT_MS(LW(4))
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(chorobon_find_event)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    LOOP(3)
        CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), LW(3))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), 50)
        CALL(evt_npc_jump_position, STRING("me"), LW(0), -10000, LW(2), 300, 0, FLOAT(30.0f), 0)
        WAIT_MS(50)
    END_LOOP
    CALL(evt_npc_set_scale, STRING("me"), 1, 1, 1)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(chorobon_lost_event)
    CALL(evt_npc_set_scale, STRING("me"), 1, 1, 1)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(chorobon_return_event)
    CALL(evt_npc_set_scale, STRING("me"), 1, 1, 1)
    CALL(evt_npc_set_walk_anim, STRING("me"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), 50)
    CALL(evt_npc_jump_position, STRING("me"), LW(0), -10000, LW(2), 300, 0, FLOAT(30.0f), 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(pansy_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(pansy_find_event)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_PANZI_MOVE2"), STRING("SFX_FLD_ENM_PANZI_MOVE2"), 30000, 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_homing_target, STRING("me"), STRING("mario"), 0, FLOAT(100.0f), FLOAT(10.0f), FLOAT(60.0f), 4)
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(pansy_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_S_1"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(pansy_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_S_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_W_1"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(twinkling_pansy_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_sound_data_reset, STRING("me"))
    LABEL(0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(twinkling_pansy_find_event)
    CALL(evt_npc_sound_data_set, STRING("me"), STRING("SFX_FLD_ENM_PANZI_MOVE2"), STRING("SFX_FLD_ENM_PANZI_MOVE2"), 30000, 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
    ADD(LW(3), 180)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(300.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 1000, FLOAT(300.0f), 6)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(twinkling_pansy_lost_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_S_1_K"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(twinkling_pansy_return_event)
    CALL(evt_npc_sound_data_reset, STRING("me"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_S_1_K"))
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_W_1_K"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

// TODO: USER_FUNC(set_bottle_flag_init) { }

EVT_BEGIN(karon_init_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(mahoon_get_groupname, LW(10))
    CALL(evt_npc_slave_entry, STRING("me"), 0, LW(10), LW(0), PTR(enemy_slave_common_dead_event))
    CALL(evt_npc_flag_onoff, 1, LW(0), 536870912)
    CALL(evt_npc_flag_onoff, 1, LW(0), 32)
    CALL(evt_npc_set_anim, STRING("slave_0"), STRING("KRN_H_1"))
    CALL(evt_npc_set_width, STRING("slave_0"), 24)
    CALL(evt_npc_set_height, STRING("slave_0"), 8)
    RETURN
EVT_END()

EVT_BEGIN(karon_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 128)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    CALL(evt_sub_random, 360, LW(3))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 2097152)
    CALL(evt_sub_random, 360, LW(3))
    LABEL(0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(karon_find_event)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 2097152)
    BEGIN_SIBLING_EVENT
        LABEL(0)
        CALL(evt_npc_add_rotate, STRING("slave_0"), 0, 0, 30)
        WAIT_FRAMES(1)
        GOTO(0)
    END_SIBLING_EVENT
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_A_1"))
    WAIT_MS(250)
    CALL(evt_npc_get_position, STRING("me"), LW(2), LW(3), LW(4))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_KARON_BONE_THROW1"), LW(2), LW(3), LW(4), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_A_2"))
    WAIT_MS(150)
    BEGIN_SIBLING_EVENT
        WAIT_MS(1000)
        CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_S_1"))
    END_SIBLING_EVENT
    CALL(evt_npc_set_rotate, STRING("slave_0"), 0, 0, 0)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    ADD(LW(1), 25)
    CALL(evt_npc_set_position, STRING("slave_0"), LW(0), LW(1), LW(2))
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 128)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 32)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 12)
    CALL(evt_npc_jump_position, STRING("slave_0"), LW(0), LW(1), LW(2), 1000, 0, FLOAT(75.0f), 0)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 2097152)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

// TODO: USER_FUNC(unk_800ece0c) { }

// TODO: USER_FUNC(zakoEntryFall) { }

// TODO: USER_FUNC(dokanCheck) { }

// TODO: USER_FUNC(zakoEntryDokan) { }

// TODO: USER_FUNC(limitSpd) { }

// TODO: USER_FUNC(getSpdRun) { }

// TODO: USER_FUNC(getSpdWalk) { }

// TODO: USER_FUNC(upperCheck) { }

// TODO: USER_FUNC(cliffCheck) { }

// TODO: USER_FUNC(camGetPos) { }

// TODO: static USER_FUNC(chain_main) { }

// TODO: USER_FUNC(kamec_fire_magic_delete) { }

// TODO: USER_FUNC(kamec_fire_magic) { }

// TODO: USER_FUNC(piders_draw_yawn) { }

EVT_BEGIN(karon_lost_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(karon_return_event)
    CALL(evt_npc_set_stay_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(karon_blow_event)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL_CHILD(PTR(enemy_common_blow_event))
    RETURN
EVT_END()

EVT_BEGIN(honenoko2_init_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_Z_2"))
    RETURN
EVT_END()

EVT_BEGIN(honenoko2_move_event)
    DEBUG_PUT_MSG(STRING("[EVENT] HONENOKO MOVE\n"))
    LABEL(0)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_npc_wait_msec, STRING("me"), 1000)
        GOTO(0)
    END_IF
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_D_2"))
    CALL(evt_npc_wait_msec, STRING("me"), 170)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_Z_2"))
    CALL(evt_npc_wait_msec, STRING("me"), 10)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(honenoko2_find_event)
    DEBUG_PUT_MSG(STRING("[EVENT] HONENOKO FIND\n"))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_D_3"))
    CALL(evt_npc_wait_msec, STRING("me"), 170)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_D_4"))
    CALL(evt_npc_wait_msec, STRING("me"), 170)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1024)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_homing_target, STRING("me"), STRING("mario"), 0, FLOAT(120.0f), FLOAT(10.0f), FLOAT(60.0f), 4)
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(honenoko2_lost_event)
    DEBUG_PUT_MSG(STRING("[EVENT] HONENOKO LOST\n"))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_wait_msec, STRING("me"), 1000)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_unitwork, STRING("me"), 0, 1)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_D_2"))
    WAIT_FRAMES(10)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_Z_2"))
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(honenoko2_return_event)
    DEBUG_PUT_MSG(STRING("[EVENT] HONENOKO RETURN\n"))
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_S_1"))
    CALL(evt_npc_wait_msec, STRING("me"), 1000)
    CALL(evt_npc_set_anim, STRING("me"), STRING("KRN_W_1"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(killer_init_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 64)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 4)
    RETURN
EVT_END()

EVT_BEGIN(killer_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    CALL(evt_npc_status_onoff, 0, STRING("me"), 4)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 11)
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), 2000)
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, 200, 4)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    ADD(LW(1), 15)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 17, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    RETURN
EVT_END()

EVT_BEGIN(killer_dead_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1024)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_damage_anim, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 4, LW(0), LW(1), LW(2), FLOAT(0.7998047f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_snd_sfxon, STRING("SFX_ENEMY_DIE1"), 0)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_drop_coin, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 121, LW(0), LW(1), LW(2), 8, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_heart, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 123, LW(0), LW(1), LW(2), 8, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_flower, STRING("me"), LW(3))
    IF_INT_GREATER(LW(3), 0)
        LOOP(LW(3))
            CALL(evt_item_entry, 0, 124, LW(0), LW(1), LW(2), 8, -1, 0)
        END_LOOP
    END_IF
    CALL(evt_npc_get_drop_item, STRING("me"), LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_item_entry, 0, LW(3), LW(0), LW(1), LW(2), 9, -1, 0)
    END_IF
    CALL(evt_npc_getback_item_entry, STRING("me"))
    CALL(evt_npc_get_drop_fixitem, STRING("me"), LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_item_entry, 0, LW(3), LW(0), LW(1), LW(2), 9, -1, 0)
    END_IF
    CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    RETURN
EVT_END()

EVT_BEGIN(killer_cannon_init_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_get_dir, STRING("me"), LW(0))
    CALL(evt_npc_set_unitwork, STRING("me"), 0, LW(0))
    RETURN
EVT_END()

EVT_BEGIN(killer_cannon_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_set_anim, STRING("me"), STRING("KTA_S_1"))
    SET_VALUE(LW(10), 0)
    LABEL(0)
    WAIT_MS(3000)
    LABEL(1)
    WAIT_MS(100)
    ADD(LW(10), 1)
    IF_INT_EQUAL(LW(10), 2)
        SET_VALUE(LW(10), 0)
    END_IF
    CALL(evt_npc_set_anim, STRING("me"), STRING("KTA_A_1"))
    WAIT_MS(200)
    CALL(evt_npc_get_position, STRING("me"), LW(2), LW(3), LW(4))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_KILLER_CANNON1"), LW(2), LW(3), LW(4), 0)
    WAIT_MS(200)
    CALL(evt_npc_get_dir, STRING("me"), LW(1))
    CALL(evt_npc_get_position, STRING("me"), LW(2), LW(3), LW(4))
    CALL(evt_npc_add_dirdist, LW(2), LW(4), LW(1), 30)
    ADD(LW(3), 30)
    CALL(evt_eff, STRING(""), STRING("kemuri_test"), 18, LW(2), LW(3), LW(4), FLOAT(1.5f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_npc_get_dir, STRING("me"), LW(1))
    CALL(killer_make_name, LW(10), LW(0))
    CALL(evt_npc_set_ry, LW(0), LW(1))
    CALL(evt_npc_get_position, STRING("me"), LW(2), LW(3), LW(4))
    CALL(evt_npc_add_dirdist, LW(2), LW(4), LW(1), 30)
    ADD(LW(3), 11)
    CALL(killer_make_name, LW(10), LW(0))
    CALL(evt_npc_set_position, LW(0), LW(2), LW(3), LW(4))
    CALL(killer_make_name, LW(10), LW(0))
    CALL(evt_npc_set_anim, LW(0), STRING("KIL_S_1"))
    CALL(killer_make_name, LW(10), LW(0))
    CALL(evt_npc_change_interrupt, LW(0), 1, PTR(killer_move_event))
    CALL(killer_make_name, LW(10), LW(0))
    CALL(evt_npc_restart_regular_event, LW(0))
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(sambo_move_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1048592)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SNB_S_1"))
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(sambo_find_event)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SNB_S_1"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_homing_target, STRING("me"), STRING("mario"), 0, FLOAT(100.0f), FLOAT(7.0f), FLOAT(60.0f), 4)
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sambo_lost_event)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SNB_S_1"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sambo_return_event)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SNB_S_1"))
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_home_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(100.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinnosuke_init_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 8)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1049616)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 268435456)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    RETURN
EVT_END()

EVT_BEGIN(sinnosuke_move_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1049616)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_Z_3"))
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(sinnosuke_find_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_Z_3"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 270)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_S_1"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 270, 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 360)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    LOOP(0)
        CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_A_1a"))
        WAIT_MS(300)
        CALL(evt_npc_set_attack_mode, STRING("me"), 13)
        CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), LW(3))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(200.0f), 6)
        CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_S_1"))
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        WAIT_MS(200)
    END_LOOP
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinnosuke_lost_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_S_1"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinnosuke_return_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_W_1"))
    CALL(evt_npc_get_home_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(30.0f), 4)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_S_1"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 270)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIS_Z_3"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 270, 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 360)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinemon_init_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 8)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1049616)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 131072)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    RETURN
EVT_END()

EVT_BEGIN(sinemon_move_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1049616)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 131072)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_Z_3"))
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(sinemon_find_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_Z_3"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 270)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_S_1"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 270, 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 360)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    LOOP(0)
        CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_A_1a"))
        WAIT_MS(300)
        CALL(evt_npc_set_attack_mode, STRING("me"), 14)
        CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), LW(3))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(200.0f), 6)
        CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_S_1"))
        CALL(evt_npc_set_attack_mode, STRING("me"), 0)
        WAIT_MS(200)
    END_LOOP
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinemon_lost_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_S_1"))
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(sinemon_return_event)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_W_1"))
    CALL(evt_npc_get_home_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(30.0f), 4)
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_S_1"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    SET_VALUE(LW(15), 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 270)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_anim, STRING("me"), STRING("SIN_Z_3"))
    CALL(evt_npc_set_rotate, STRING("me"), 0, 270, 0)
    LOOP(0)
        WAIT_FRAMES(1)
        ADD(LW(15), 30)
        CALL(evt_npc_set_rotate, STRING("me"), 0, LW(15), 0)
        IF_INT_GREATER_OR_EQUAL(LW(15), 360)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togedaruma_move_event)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_sub_random, 360, LW(3))
    LABEL(0)
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 2000, FLOAT(40.0f), 4)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(togedaruma_find_event)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_set_attack_mode, STRING("me"), 15)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(evt_npc_add_rotate, STRING("me"), 0, 45, 0)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_npc_homing_target, STRING("me"), STRING("mario"), 0, FLOAT(120.0f), FLOAT(10.0f), FLOAT(60.0f), 4)
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togedaruma_lost_event)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 1, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(togedaruma_return_event)
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    CALL(evt_npc_set_attack_mode, STRING("me"), 0)
    WAIT_MS(500)
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 4)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(barriern_init_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_slave_entry, STRING("me"), 0, STRING("c_baria"), LW(0), PTR(enemy_slave_common_dead_event))
    CALL(evt_npc_flag_onoff, 1, LW(0), 536870912)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 131072)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    RETURN
EVT_END()

EVT_BEGIN(barriern_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 128)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 2097152)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 131072)
    LABEL(0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_3"))
    WAIT_FRAMES(60)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    WAIT_FRAMES(60)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 30, 50)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 2000, FLOAT(40.0f), 0, 0, 1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(barriern2_move_event)
    CALL_CHILD(PTR(enemy_common_flag_init_event))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 131072)
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 131072)
    LABEL(0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_3"))
    WAIT_FRAMES(60)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    WAIT_FRAMES(60)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 30, 50)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 1000, FLOAT(120.0f), 0, 0, 1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(barriern_dead_event)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(10))
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 128)
    CALL_CHILD(PTR(enemy_common_dead_event))
    RETURN
EVT_END()

EVT_BEGIN(barriern_find_event)
    CALL(evt_eff_fukidashi, 1, 0, STRING("me"), 0, 0, 0, 0, 0, 0, 0, 30)
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(0))
    CALL(evt_npc_set_ry, STRING("me"), LW(0))
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 2097152)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    LABEL(0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_2"))
    WAIT_FRAMES(30)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_3"))
    WAIT_FRAMES(10)
    CALL(evt_npc_set_anim, STRING("me"), STRING("A_4"))
    BEGIN_SIBLING_EVENT
        SET_FLOAT_VALUE(LW(15), 0)
        LOOP(60)
            ADD_FLOAT(LW(15), FLOAT(0.029296875f))
            CALL(evt_npc_set_scale, STRING("slave_0"), 1, LW(15), 1)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_npc_set_anim, STRING("slave_0"), STRING("Z_3"))
    CALL(evt_npc_blur_onoff, 1, STRING("slave_0"))
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 128)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("slave_0"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_BARRI_ATTACK1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_BARRI_ATTACK2"), LW(0), LW(1), LW(2), LW(10))
    CALL(evt_npc_set_unitwork, STRING("me"), 0, LW(10))
    CALL(evt_get_target_dir, STRING("me"), STRING("mario"), LW(3))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(500.0f))
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 32)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 17)
    CALL(evt_npc_glide_position, STRING("slave_0"), LW(0), LW(1), LW(2), 1250, 10, 0, 0, 1)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 0)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(10))
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_3"))
    WAIT_FRAMES(30)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    WAIT_FRAMES(30)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 2097152)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

static void piders_draw_yarn_sub(CameraId cameraId, void* param) {
    NpcEntry* npc = param;
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    Vec p;
    Vec q;
    Vec a = {0.0f, 0.0f, 0.0f};
    Vec b = {0.0f, 0.0f, 0.0f};
    a.x = npc->territoryBase.x;
    a.y = 30.0f + npc->territoryBase.y;
    a.z = npc->territoryBase.z;
    b.x = npc->position.x;
    b.y = 30.0f + npc->position.y;
    b.z = npc->position.z;
    p = a;
    q = b;
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(p.x - 1.0f, p.y, p.z - 5.0f);
    GXPosition3f32(1.0f + p.x, p.y, p.z - 5.0f);
    GXPosition3f32(1.0f + q.x, q.y, q.z - 5.0f);
    GXPosition3f32(q.x - 1.0f, q.y, q.z - 5.0f);
    GXEnd();
}


USER_FUNC(piders_draw_yawn) {
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    dispEntry(CAMERA_3D, 0.0f, 1, piders_draw_yarn_sub, npc);
    return EVT_RETURN_DONE;
}


USER_FUNC(kamec_fire_magic) {
    s32* args = event->args;
    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    s32 c = evtGetValue(event, args[2]);
    s32 d = evtGetValue(event, args[3]);
    s32 e = evtGetValue(event, args[4]);
    s32 f = evtGetValue(event, args[5]);
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    EffectEntry* eff = effMagic1N64Entry(0, 60, (f32)a, (f32)b, (f32)c, (f32)d, (f32)e, (f32)f);
    effSetName(eff, npc->description);
    evtSetValue(event, args[6], (s32)eff);
    return EVT_RETURN_DONE;
}


USER_FUNC(kamec_fire_magic_delete) {
    EffectEntry* eff = effNameToPtr(evtNpcNameToPtr(event, "me")->description);
    if (eff) {
        *(s32*)((u8*)eff->userdata + 0x30) = 1;
    }
    return EVT_RETURN_DONE;
}


// TODO: static USER_FUNC(piders_draw_yarn_sub) { }

// TODO: USER_FUNC(piders_get_height) { }

// TODO: USER_FUNC(killer_make_name) { }

// TODO: USER_FUNC(_2d_get_dead_jump_offset) { }

// TODO: USER_FUNC(_2d_dead_jump) { }

// TODO: USER_FUNC(pressCheck) { }

// TODO: USER_FUNC(_wait_blow_end) { }

// TODO: USER_FUNC(npc_check_wall_stop) { }

// TODO: USER_FUNC(mahoon_get_groupname) { }

EVT_BEGIN(barriern_lost_event)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_3"))
    WAIT_FRAMES(60)
    CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
    WAIT_FRAMES(60)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(barriern_return_event)
    CALL(evt_set_dir_to_home, STRING("me"))
    CALL(evt_npc_get_dir, STRING("me"), LW(3))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_add_dirdist, LW(0), LW(2), LW(3), FLOAT(100.0f))
    CALL(evt_fbat_trans_floor_position, LW(0), LW(1), LW(2), 30, 50)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 2000, FLOAT(40.0f), 0, 0, 1)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(barriern_blow_event)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 0)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_get_unitwork, STRING("me"), 0, LW(10))
    CALL(evt_snd_sfxoff, LW(10))
    CALL_CHILD(PTR(enemy_common_blow_event))
    RETURN
EVT_END()

EVT_BEGIN(piders_move_event)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), 1024)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAI_S_1"))
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(piders_draw_yawn)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(evt_npc_get_home_position, STRING("me"), LW(0), LW(1), LW(2))
            SET_VALUE(LW(3), LW(1))
            SUBTRACT(LW(1), 10)
            CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 150, 0, 0, 4, 0)
            CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(3), LW(2), 150, 0, 0, 4, 0)
            WAIT_FRAMES(100)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
        LOOP(20)
            CALL(evt_npc_add_rotate, STRING("me"), 0, 2, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            LOOP(40)
                CALL(evt_npc_add_rotate, STRING("me"), 0, -2, 0)
                WAIT_FRAMES(1)
            END_LOOP
            LOOP(40)
                CALL(evt_npc_add_rotate, STRING("me"), 0, 2, 0)
                WAIT_FRAMES(1)
            END_LOOP
        END_LOOP
    END_SIBLING_EVENT
    LABEL(0)
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(piders_find_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1024)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(piders_draw_yawn)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    BEGIN_INLINE_EVENT
        LOOP(10)
            CALL(evt_npc_add_rotate, STRING("me"), 0, 6, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(22)
            CALL(evt_npc_add_rotate, STRING("me"), 0, -5, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(20)
            CALL(evt_npc_add_rotate, STRING("me"), 0, 4, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(16)
            CALL(evt_npc_add_rotate, STRING("me"), 0, -3, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(14)
            CALL(evt_npc_add_rotate, STRING("me"), 0, 2, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(10)
            CALL(evt_npc_add_rotate, STRING("me"), 0, -1, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_npc_set_rotate, STRING("me"), 0, 0, 0)
    END_INLINE_EVENT
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PAIDA_MOVE1"), LW(0), LW(1), LW(2), 0)
    CALL(piders_get_height, LW(15))
    SET_VALUE(LW(14), LW(15))
    DIVIDE(LW(14), 3)
    CALL(evt_npc_get_home_position, STRING("me"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(1))
    SUBTRACT(LW(1), LW(15))
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 500, 0, 0, 4, 0)
    WAIT_FRAMES(60)
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PAIDA_MOVE2"), LW(0), LW(1), LW(2), 0)
    ADD(LW(1), LW(14))
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 700, 0, 20, 4, 0)
    ADD(LW(1), LW(14))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PAIDA_MOVE2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(1), LW(2), 700, 0, 20, 4, 0)
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PAIDA_MOVE2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_glide_position, STRING("me"), LW(0), LW(3), LW(2), 600, 0, 0, 4, 0)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

EVT_BEGIN(piders_blow_event)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            WAIT_FRAMES(1)
            CALL(piders_draw_yawn)
        END_LOOP
    END_SIBLING_EVENT
    CALL_CHILD(PTR(enemy_common_blow_event))
    RETURN
EVT_END()

EVT_BEGIN(pakkun_attack_event)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_FLD_ENM_PAKKUN_ATTACK1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PKF_A_1A"))
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PKF_A_1B"))
    CALL(evt_npc_flag_onoff, 0, STRING("slave_0"), 32)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 18)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_npc_facedirection_add, STRING("me"), LW(0), 30)
    CALL(evt_npc_set_position, STRING("slave_0"), LW(0), LW(1), LW(2))
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PKF_A_1C"))
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    CALL(evt_npc_set_attack_mode, STRING("slave_0"), 0)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    WAIT_MS(200)
    RETURN
EVT_END()

EVT_BEGIN(pakkun_init_event)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), 1048600)
    CALL(evt_npc_slave_entry, STRING("me"), 0, STRING("c_pakflwr"), LW(0), PTR(enemy_slave_common_dead_event))
    CALL(evt_npc_set_tribe, STRING("slave_0"), STRING("パックンフラワー"))
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 128)
    CALL(evt_npc_set_position, STRING("slave_0"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("slave_0"), 32)
    RETURN
EVT_END()

s32 pakkun_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"PKF_S_1", 65539, 0, 65545, 1, 65540, 0, 2,
    1,
};

s32 pakkun_find_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_PAKKUN_MOVE1", -30000000, -29999999,
    -29999998, 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 32, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"PKF_E_2", 65545, 10, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 196699, (s32)evt_sub_random, 10, -29999997, 131163,
    (s32)evt_mario_get_mov_spd, -29999996, 131132, -29999996, -229999488, 131130, -29999997, -29999996,
    131130, -29999997, 30, 262235, (s32)evt_npc_facedirection_add, (s32)"mario", -30000000, -29999997,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 200, 0, 4,
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me",
    -30000000, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 393307,
    (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_PAKKUN_MOVE2", -30000000, -29999999, -29999998, 0, 196699, (s32)evt_npc_set_anim,
    (s32)"me", (s32)"PKF_E_1", 65545, 10, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me",
    32, 65545, 20, 65630, (s32)pakkun_attack_event, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 pakkun_return_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 2097152, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_PAKKUN_MOVE2", -30000000, -29999999,
    -29999998, 0, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"PKF_E_1", 65545, 10,
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 32, 65545, 20, 65630,
    (s32)pakkun_attack_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 32, 196699, (s32)evt_npc_set_anim,
    (s32)"me", (s32)"PKF_E_2", 65545, 10, 327771, (s32)evt_npc_get_home_position, (s32)"me", -30000000,
    -29999999, -29999998, 458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 200,
    0, 4, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"PKF_E_1", 65545, 10,
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 32, 65545, 25, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2,
    1,
};

s32 dokugassun_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"me", 268435456, 2, 1,
};

s32 dokugassun_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699, (s32)evt_sub_random, 360,
    -29999997, 65539, 0, 65546, 500, 262235, (s32)evt_npc_get_loiter_dir, -29999997,
    -229877120, -229754240, 131163, (s32)evt_npc_sound_data_reset, (s32)"me", 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 10, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 1,
    -229993856, 0, 2, 458843, (s32)evt_npc_sound_data_set, (s32)"me", 0, 0,
    0, 0, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 10, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 500, 1, -230006144, 0,
    2, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 10, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 500, 1, -229993856, 0, 2, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    10, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    500, 1, -229993856, 0, 2, 65540, 0, 2,
    1,
};

s32 dokugassun_find_event[] = {
    131163, (s32)evt_npc_sound_data_reset, (s32)"me", 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1024,
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 65546, 200, 262235,
    (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me", -29999999,
    -29999998, -29999997, 327771, (s32)evt_npc_add_dirdist, -29999999, -29999997, -30000000, -229795200,
    393307, (s32)evt_fbat_trans_floor_position, -29999999, -29999998, -29999997, 10, 500, 196699,
    (s32)evt_npc_set_ry, (s32)"me", -30000000, 655451, (s32)evt_npc_glide_position, (s32)"me", -29999999, -29999998,
    -29999997, 1000, 1, 0, 4, 1, 65546, 500,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 dokugassun_lost_event[] = {
    131163, (s32)evt_npc_sound_data_reset, (s32)"me", 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024,
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546,
    500, 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 1000, 131163, (s32)evt_npc_return_interrupt,
    (s32)"me", 2, 1,
};

s32 dokugassun_return_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"S_1", 65546, 500, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"W_1", 131163,
    (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 131163, (s32)evt_npc_sound_data_reset,
    (s32)"me", 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 10, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 500, 1, -230006144, 0, 2, 458843,
    (s32)evt_npc_sound_data_set, (s32)"me", 0, 0, 0, 0, 0, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    10, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    500, 1, -229993856, 0, 2, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 10, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 1,
    -230006144, 0, 2, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 10, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 500, 1, -229993856, 0,
    2, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1049624, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 2,
    1,
};

s32 basabasa_move_event[] = {
    327771, (s32)evt_npc_get_home_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position,
    (s32)"me", -29999997, -29999996, -29999995, 131098, -29999996, -29999999, 131163,
    (s32)evt_npc_set_walk_anim, (s32)"me", 131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me",
    -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 327771, (s32)evt_npc_get_home_position, (s32)"me",
    -29999996, -29999999, -29999995, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 500, 0, -230051200, 0, 2, 33, 65539,
    0, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"BSA_S_2", 65545, 60, 65540,
    0, 2, 1,
};

s32 basabasa_find_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 2097152, 131163, (s32)evt_npc_set_run_anim, (s32)"me",
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me", -29999999, -29999998, -29999997,
    327771, (s32)evt_npc_get_home_position, (s32)"me", -29999996, -29999995, -29999994, 327771, (s32)evt_npc_add_dirdist,
    -29999999, -29999997, -30000000, -229897600, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000,
    655451, (s32)evt_npc_glide_position, (s32)"me", -29999999, -29999995, -29999997, 0, 75,
    -230143360, 0, 0, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    1, 0, 0, 0, 0, 0, 0, 30,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa_return_event[] = {
    131163, (s32)evt_npc_set_walk_anim, (s32)"me", 131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir,
    (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 327771, (s32)evt_npc_get_home_position,
    (s32)"me", -29999996, -29999999, -29999995, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 500, 0, -230051200, 0, 2, 131163,
    (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa2_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699, (s32)evt_sub_random, 360,
    -29999997, 65539, 0, 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500,
    131163, (s32)evt_npc_set_walk_anim, (s32)"me", 262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120, -229754240,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999,
    -29999998, 80, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 0, 50, -230010240, 0, 3, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 80,
    500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0,
    50, -229989760, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400,
    393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 80, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 50, -230010240,
    0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position,
    -30000000, -29999999, -29999998, 80, 500, 655451, (s32)evt_npc_glide_position, (s32)"me",
    -30000000, -29999999, -29999998, 0, 50, -229989760, 0, 3,
    65540, 0, 2, 1,
};

s32 basabasa2_find_event[] = {
    131163, (s32)evt_npc_set_run_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    0, 0, 0, 0, 0, 0, 0, 30,
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me",
    -29999999, -29999998, -29999997, 327771, (s32)evt_npc_add_dirdist, -29999999, -29999997, -30000000,
    -229897600, 393307, (s32)evt_fbat_trans_floor_position, -29999999, -29999998, -29999997, 80, 500,
    196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 655451, (s32)evt_npc_glide_position, (s32)"me", -29999999,
    -29999998, -29999997, 0, 75, -230081920, 0, 0, 131163,
    (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa2_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    1, 0, 0, 0, 0, 0, 0, 30,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 basabasa2_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me",
    131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    80, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    500, 0, -230010240, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 80, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 0,
    -229989760, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 80, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 500, 0, -230010240, 0,
    3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 80, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 500, 0, -229989760, 0, 3, 131163,
    (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 teresa_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)"me", 2097152, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 32, 393307,
    (s32)evt_npc_set_color, (s32)"me", 255, 255, 255, 255, 196699, (s32)evt_sub_random,
    360, -29999997, 65539, 0, 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546,
    500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me", 262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120,
    -229754240, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 0, 50, -230010240, 0, 3, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    0, 50, -229989760, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 50,
    -230010240, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 0, 50, -229989760, 0,
    3, 65540, 0, 2, 1,
};

s32 teresa_find_event[] = {
    131163, (s32)evt_npc_set_run_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    0, 0, 0, 0, 0, 0, 0, 30,
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me",
    -29999999, -29999998, -29999997, 327771, (s32)evt_npc_add_dirdist, -29999999, -29999997, -30000000,
    -229897600, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 393307, (s32)evt_fbat_trans_floor_position, -29999999,
    -29999998, -29999997, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -29999999,
    -29999998, -29999997, 0, 75, -230040960, 0, 0, 131163,
    (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 teresa_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    1, 0, 0, 0, 0, 0, 0, 30,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 teresa_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me",
    131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"me", 2097152, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me",
    32, 131122, -30000000, 255, 65541, 16, 393307, (s32)evt_npc_set_color,
    (s32)"me", 255, 255, 255, -30000000, 131126, -30000000, 16,
    65546, 30, 6, 393307, (s32)evt_npc_set_color, (s32)"me", 255, 255,
    255, 0, 65546, 500, 327771, (s32)evt_npc_get_home_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_set_position, (s32)"me", -30000000, -29999999, -29999998,
    131122, -30000000, 0, 65541, 16, 131125, -30000000, 16,
    131099, -30000000, 255, 131122, -30000000, 255, 33, 393307,
    (s32)evt_npc_set_color, (s32)"me", 255, 255, 255, -30000000, 65546, 30,
    6, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 32, 262235, (s32)evt_npc_flag_onoff,
    0, (s32)"me", 2097152, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 bubble_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699, (s32)evt_sub_random, 360,
    -29999997, 65539, 0, 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500,
    131163, (s32)evt_npc_sound_data_reset, (s32)"me", 131163, (s32)evt_npc_set_walk_anim, (s32)"me", 262235, (s32)evt_npc_get_loiter_dir,
    -29999997, -229877120, -229754240, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 0, 50, -230005120, 0,
    3, 458843, (s32)evt_npc_sound_data_set, (s32)"me", 0, 0, 0, 0,
    0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 0, 50, -229994880, 0, 3, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    0, 50, -230005120, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 50,
    -229994880, 0, 3, 65540, 0, 2, 1,
};

s32 bubble_find_event[] = {
    131163, (s32)evt_npc_sound_data_reset, (s32)"me", 131163, (s32)evt_npc_set_run_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi,
    1, 0, (s32)"me", 0, 0, 0, 0, 0,
    0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000,
    327771, (s32)evt_npc_get_position, (s32)"me", -29999999, -29999998, -29999997, 327771, (s32)evt_npc_add_dirdist,
    -29999999, -29999997, -30000000, -229897600, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000,
    393307, (s32)evt_fbat_trans_floor_position, -29999999, -29999998, -29999997, 20, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -29999999, -29999998, -29999997, 0, 90, -230000000,
    0, 2, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 bubble_lost_event[] = {
    131163, (s32)evt_npc_sound_data_reset, (s32)"me", 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi,
    1, 0, (s32)"me", 1, 0, 0, 0, 0,
    0, 0, 30, 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 bubble_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me",
    131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 131163,
    (s32)evt_npc_sound_data_reset, (s32)"me", 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position,
    -30000000, -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me",
    -30000000, -29999999, -29999998, 500, 0, -230005120, 0, 3,
    458843, (s32)evt_npc_sound_data_set, (s32)"me", 0, 0, 0, 0, 0,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999,
    -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 500, 0, -229994880, 0, 3, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20,
    500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500,
    0, -230005120, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400,
    393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 0, -229994880,
    0, 3, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hbom_move_event[] = {
    65630, (s32)enemy_common_flag_init_event, 196699, (s32)evt_sub_random, 360, -29999997, 65539, 0,
    65546, 500, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120, -229754240, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229897600, 458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998,
    2000, -229979520, 4, 65546, 1000, 65540, 0, 2,
    1,
};

s32 hbom_find_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 589915, (s32)evt_npc_jump_position, (s32)"me", -30000000,
    -29999999, -29999998, 300, 0, -229979520, 0, 524379, (s32)evt_npc_homing_target,
    (s32)"me", (s32)"mario", 0, -229938560, -229989760, -229938560, 4, 65546,
    500, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hbom_lost_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 1, 0, 0,
    0, 0, 0, 0, 30, 131163, (s32)evt_npc_set_stay_anim, (s32)"me",
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hbom_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_set_dir_to_home, (s32)"me",
    196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 0, -229969280, 4,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 zakowiz_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 393307, (s32)evt_npc_slave_entry, (s32)"me", 0, (s32)"c_zako_m", -30000000,
    (s32)enemy_slave_common_dead_event, 262235, (s32)evt_npc_flag_onoff, 1, -30000000, 536870912, 262235, (s32)evt_npc_flag_onoff,
    1, -30000000, 32, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"B_1A", 196699,
    (s32)evt_npc_set_width, (s32)"slave_0", 10, 196699, (s32)evt_npc_set_height, (s32)"slave_0", 10, 262235,
    (s32)evt_npc_set_unitwork, (s32)"me", 0, 1, 2, 1,
};

s32 zakowiz_move_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 196699, (s32)evt_sub_random, 360, -29999997, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 65539, 0, 65546, 500,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235, (s32)evt_npc_get_loiter_dir,
    -29999997, -229877120, -229754240, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229897600, 458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 2000, -229959040,
    4, 131163, (s32)npc_check_wall_stop, -30000000, 131096, -30000000, 1, 131163,
    (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546,
    1000, 33, 65540, 0, 2, 1,
};

s32 zakowiz_find_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"me", 2097152, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"A_1B", 65546,
    500, 110, 65546, 700, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1",
    112, 327771, (s32)evt_npc_set_rotate, (s32)"slave_0", 0, 0, 0, 196699,
    (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125,
    -29999999, 25, 327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998,
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_0", 128, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"B_1A", 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"slave_0", 32, 196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 12,
    589915, (s32)evt_npc_jump_position, (s32)"slave_0", -30000000, -29999999, -29999998, 1000, 0,
    -229923200, 0, 327771, (s32)evt_npc_get_position, (s32)"slave_0", -30000000, -29999999, -29999998,
    983131, (s32)evt_eff, (s32)"", (s32)"kemuri_test", 16, -30000000, -29999999, -29999998,
    -229998976, 0, 0, 0, 0, 0, 0, 0,
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"B_2", 65546, 300, 327771,
    (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)"me", 2097152, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 zakowiz_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 zakowiz_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_set_dir_to_home, (s32)"me",
    196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 0, -229959040, 4,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 zakowiz_blow_event[] = {
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 65630,
    (s32)enemy_common_blow_event, 2, 1,
};

s32 hannya_move_event[] = {
    196699, (s32)evt_sub_random, 360, -29999997, 65539, 0, 65546, 1000,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235, (s32)evt_npc_get_loiter_dir,
    -29999997, -229877120, -229754240, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229897600, 458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 2000, -229959040,
    4, 65540, 0, 2, 1,
};

s32 hannya_find_event[] = {
    131163, (s32)evt_npc_set_run_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    0, 0, 0, 0, 0, 0, 0, 30,
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me",
    -29999999, -29999998, -29999997, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_HANNYA_MOVE1", -29999999, -29999998,
    -29999997, 0, 327771, (s32)evt_npc_get_home_position, (s32)"me", -29999996, -29999995, -29999994,
    327771, (s32)evt_npc_add_dirdist, -29999999, -29999997, -30000000, -229897600, 196699, (s32)evt_npc_set_attack_mode,
    (s32)"me", 11, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"A_3", 458843, (s32)evt_npc_move_position, (s32)"me", -29999999, -29999997,
    0, -229815680, 6, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1024,
    196699, (s32)evt_npc_set_attack_mode, (s32)"me", 0, 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546,
    1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hannya_lost_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 1, 0, 0,
    0, 0, 0, 0, 30, 131163, (s32)evt_npc_set_stay_anim, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hannya_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 1000, 262235, (s32)evt_npc_status_onoff, 0,
    (s32)"me", 2, 327771, (s32)evt_npc_get_home_position, (s32)"me", -30000000, -29999999, -29999998,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 3000, -229959040, 4,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 mahoon_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 131163, (s32)mahoon_get_groupname, -29999990, 393307, (s32)evt_npc_slave_entry, (s32)"me",
    0, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"MAH_S_2A",
    327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 393307, (s32)evt_npc_slave_entry,
    (s32)"me", 1, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim, (s32)"slave_1",
    (s32)"MAH_S_2A", 327771, (s32)evt_npc_set_position, (s32)"slave_1", 0, -1000, 0, 393307,
    (s32)evt_npc_slave_entry, (s32)"me", 2, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim,
    (s32)"slave_2", (s32)"MAH_S_2A", 327771, (s32)evt_npc_set_position, (s32)"slave_2", 0, -1000, 0,
    393307, (s32)evt_npc_slave_entry, (s32)"me", 3, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699,
    (s32)evt_npc_set_anim, (s32)"slave_3", (s32)"MAH_S_2A", 327771, (s32)evt_npc_set_position, (s32)"slave_3", 0, -1000,
    0, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 262235, (s32)evt_npc_flag_onoff,
    0, (s32)"slave_0", 131072, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_1", 131072,
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_2", 131072, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)"slave_3", 131072, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 32, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"slave_1", 32, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_2",
    32, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_3", 32, 2, 1,
};

s32 mahoon_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 110, 65541, 0,
    65545, 1, 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 196699, (s32)evt_npc_set_ry,
    (s32)"slave_0", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_1", -29999997, 196699, (s32)evt_npc_set_ry,
    (s32)"slave_2", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_3", -29999997, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 131125, -29999999, 5, 327771, (s32)evt_npc_set_position, (s32)"slave_0",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -230025600, 131125,
    -29999999, 5, 327771, (s32)evt_npc_set_position, (s32)"slave_1", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 131125, -29999999, 30, 327771,
    (s32)evt_npc_set_position, (s32)"slave_2", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -230025600, 131125, -29999999, 30, 327771, (s32)evt_npc_set_position, (s32)"slave_3", -30000000,
    -29999999, -29999998, 6, 112, 196699, (s32)evt_sub_random, 360, -29999997,
    65539, 0, 131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163,
    (s32)evt_npc_set_walk_anim, (s32)"me", 262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120, -229754240, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000,
    -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998,
    20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998,
    0, 50, -230005120, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 50,
    -229994880, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307,
    (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position,
    (s32)"me", -30000000, -29999999, -29999998, 0, 50, -230005120, 0,
    3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000,
    -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000,
    -29999999, -29999998, 0, 50, -229994880, 0, 3, 65540,
    0, 2, 1,
};

s32 mahoon_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)"slave_1", 128, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_2", 128, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"slave_3", 128, 65630, (s32)enemy_common_dead_event, 2, 1,
};

s32 mahoon_find_event[] = {
    110, 65541, 0, 65545, 1, 196699, (s32)evt_npc_get_dir, (s32)"me",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_0", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_1",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_2", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_3",
    -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125, -29999999, 5,
    327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -230025600, 131125, -29999999, 5, 327771, (s32)evt_npc_set_position, (s32)"slave_1",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125,
    -29999999, 30, 327771, (s32)evt_npc_set_position, (s32)"slave_2", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -230025600, 131125, -29999999, 30, 327771,
    (s32)evt_npc_set_position, (s32)"slave_3", -30000000, -29999999, -29999998, 6, 112, 131163,
    (s32)evt_npc_set_run_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0,
    0, 0, 0, 0, 0, 0, 30, 262235,
    (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me", -29999999,
    -29999998, -29999997, 327771, (s32)evt_npc_get_home_position, (s32)"me", -29999996, -29999995, -29999994,
    327771, (s32)evt_npc_add_dirdist, -29999999, -29999997, -30000000, -229897600, 393307, (s32)evt_fbat_trans_floor_position,
    -29999999, -29999998, -29999997, 20, 500, 196699, (s32)evt_npc_set_ry, (s32)"me",
    -30000000, 655451, (s32)evt_npc_glide_position, (s32)"me", -29999999, -29999998, -29999997, 0,
    135, -230000000, 0, 0, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2,
    1,
};

s32 mahoon_lost_event[] = {
    110, 65541, 0, 65545, 1, 196699, (s32)evt_npc_get_dir, (s32)"me",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_0", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_1",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_2", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_3",
    -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125, -29999999, 5,
    327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -230025600, 131125, -29999999, 5, 327771, (s32)evt_npc_set_position, (s32)"slave_1",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125,
    -29999999, 30, 327771, (s32)evt_npc_set_position, (s32)"slave_2", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -230025600, 131125, -29999999, 30, 327771,
    (s32)evt_npc_set_position, (s32)"slave_3", -30000000, -29999999, -29999998, 6, 112, 131163,
    (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 1,
    0, 0, 0, 0, 0, 0, 30, 131163,
    (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546,
    1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 mahoon_return_event[] = {
    110, 65541, 0, 65545, 1, 196699, (s32)evt_npc_get_dir, (s32)"me",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_0", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_1",
    -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_2", -29999997, 196699, (s32)evt_npc_set_ry, (s32)"slave_3",
    -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125, -29999999, 5,
    327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -230025600, 131125, -29999999, 5, 327771, (s32)evt_npc_set_position, (s32)"slave_1",
    -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 131125,
    -29999999, 30, 327771, (s32)evt_npc_set_position, (s32)"slave_2", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -230025600, 131125, -29999999, 30, 327771,
    (s32)evt_npc_set_position, (s32)"slave_3", -30000000, -29999999, -29999998, 6, 112, 131163,
    (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me", 131163,
    (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20,
    500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500,
    0, -230005120, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400,
    393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 20, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 0, -229994880,
    0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position,
    -30000000, -29999999, -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me",
    -30000000, -29999999, -29999998, 500, 0, -230005120, 0, 3,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999,
    -29999998, 20, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 500, 0, -229994880, 0, 3, 131163, (s32)evt_npc_return_interrupt,
    (s32)"me", 2, 1,
};

s32 kamec_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 131163, (s32)mahoon_get_groupname, -29999990, 393307, (s32)evt_npc_slave_entry, (s32)"me",
    0, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 262235, (s32)evt_npc_flag_onoff, 1, -30000000,
    536870912, 262235, (s32)evt_npc_flag_onoff, 1, -30000000, 32, 262235, (s32)evt_npc_flag_onoff,
    0, -30000000, 131072, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"KMK_Z_1", 196699,
    (s32)evt_npc_set_width, (s32)"slave_0", 10, 196699, (s32)evt_npc_set_height, (s32)"slave_0", 10, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 2, 1,
};

s32 kamec_move_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699, (s32)evt_sub_random, 360,
    -29999997, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"slave_0", 32, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_S_2", 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 65539, 0, 131163, (s32)evt_npc_set_stay_anim,
    (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me", 262235, (s32)evt_npc_get_loiter_dir,
    -29999997, -229877120, -229754240, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999,
    -29999998, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 0, 50, -230005120, 0, 3, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50,
    500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0,
    50, -229994880, 0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400,
    393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 50, -230005120,
    0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position,
    -30000000, -29999999, -29999998, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me",
    -30000000, -29999999, -29999998, 0, 50, -229994880, 0, 3,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1024, 65540, 0, 2,
    1,
};

s32 kamec_find_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"me", 2097152, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_A_3A", 65546,
    700, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_A_3B", 65546, 150, 110,
    65546, 1000, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_S_2", 112, 327771,
    (s32)evt_npc_set_rotate, (s32)"slave_0", 0, 0, 0, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229979520, 327771, (s32)evt_npc_set_position, (s32)"slave_0",
    -30000000, -29999999, -29999998, 327771, (s32)evt_mario_get_pos, 0, -29999997, -29999996,
    -29999995, 131125, -29999996, 20, 524379, (s32)kamec_fire_magic, -30000000, -29999999,
    -29999998, -29999997, -29999996, -29999995, -29999990, 327771, (s32)evt_mario_get_pos, 0,
    -30000000, -29999999, -29999998, 131125, -29999999, 20, 262235, (s32)evt_npc_flag_onoff,
    0, (s32)"slave_0", 32, 196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 12, 655451,
    (s32)evt_npc_glide_position, (s32)"slave_0", -30000000, -29999999, -29999998, 1000, 0, -230000000,
    0, 3, 131163, (s32)kamec_fire_magic_delete, -29999990, 196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0",
    0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 32, 327771, (s32)evt_npc_set_position,
    (s32)"slave_0", 0, -1000, 0, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me",
    2097152, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 kamec_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me",
    1, 0, 0, 0, 0, 0, 0, 30,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 kamec_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_npc_set_walk_anim, (s32)"me",
    131163, (s32)evt_set_dir_to_home, (s32)"me", 196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400,
    393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50, 500, 655451,
    (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500, 0, -230005120,
    0, 3, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position,
    -30000000, -29999999, -29999998, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me",
    -30000000, -29999999, -29999998, 500, 0, -229994880, 0, 3,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist,
    -30000000, -29999998, -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999,
    -29999998, 50, 500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999,
    -29999998, 500, 0, -230005120, 0, 3, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998,
    -29999997, -229974400, 393307, (s32)evt_fbat_trans_floor_position, -30000000, -29999999, -29999998, 50,
    500, 655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 500,
    0, -229994880, 0, 3, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me",
    1024, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 kamec_blow_event[] = {
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 65630,
    (s32)enemy_common_blow_event, 2, 1,
};

s32 kamec2_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1049624, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 131163, (s32)mahoon_get_groupname, -29999990, 393307, (s32)evt_npc_slave_entry, (s32)"me",
    0, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 262235, (s32)evt_npc_flag_onoff, 1, -30000000,
    536870912, 262235, (s32)evt_npc_flag_onoff, 1, -30000000, 32, 262235, (s32)evt_npc_flag_onoff,
    0, -30000000, 131072, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"KMK_Z_1", 196699,
    (s32)evt_npc_set_width, (s32)"slave_0", 10, 196699, (s32)evt_npc_set_height, (s32)"slave_0", 10, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 2, 1,
};

s32 kamec2_move_event[] = {
    65630, (s32)enemy_common_flag_init_event, 196699, (s32)evt_sub_random, 360, -29999997, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"slave_0", 128, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 32,
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_S_1", 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me",
    2097152, 65539, 0, 65546, 500, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120, -229754240,
    327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600, 458843, (s32)evt_npc_move_position,
    (s32)"me", -30000000, -29999998, 2000, -229959040, 4, 65540, 0,
    2, 1,
};

s32 kamec2_find_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"me", 2097152, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_A_2A", 65546,
    700, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_A_2B", 65546, 150, 110,
    65546, 1000, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"KMK_S_1", 112, 327771,
    (s32)evt_npc_set_rotate, (s32)"slave_0", 0, 0, 0, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 131125, -29999999, 30, 196699, (s32)evt_npc_get_dir,
    (s32)"me", -29999997, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229979520,
    327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998, 327771, (s32)evt_mario_get_pos,
    0, -29999997, -29999996, -29999995, 131125, -29999996, 20, 524379,
    (s32)kamec_fire_magic, -30000000, -29999999, -29999998, -29999997, -29999996, -29999995, -29999990,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131125, -29999999,
    20, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_0", 32, 196699, (s32)evt_npc_set_attack_mode,
    (s32)"slave_0", 12, 655451, (s32)evt_npc_glide_position, (s32)"slave_0", -30000000, -29999999, -29999998,
    1000, 0, -230000000, 0, 3, 131163, (s32)kamec_fire_magic_delete, -29999990,
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2,
    1,
};

s32 kamec2_lost_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 1, 0, 0,
    0, 0, 0, 0, 30, 131163, (s32)evt_npc_set_stay_anim, (s32)"me",
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 kamec2_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_set_dir_to_home, (s32)"me",
    196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 0, -229959040, 4,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 kamec2_blow_event[] = {
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 65630,
    (s32)enemy_common_blow_event, 2, 1,
};

s32 hbross_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 131163, (s32)mahoon_get_groupname, -29999990, 393307, (s32)evt_npc_slave_entry, (s32)"me",
    0, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 262235, (s32)evt_npc_flag_onoff, 1, -30000000,
    536870912, 262235, (s32)evt_npc_flag_onoff, 1, -30000000, 32, 196699, (s32)evt_npc_set_anim,
    (s32)"slave_0", (s32)"BRO_A_1B", 196699, (s32)evt_npc_set_width, (s32)"slave_0", 10, 196699, (s32)evt_npc_set_height,
    (s32)"slave_0", 10, 2, 1,
};

s32 hbross_move_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"BRO_S_1", 196699, (s32)evt_sub_random, 360, -29999997, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 196699, (s32)evt_sub_random, 360, -29999997,
    65539, 0, 65546, 500, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 262235, (s32)evt_npc_get_loiter_dir, -29999997, -229877120, -229754240, 327771,
    (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600, 458843, (s32)evt_npc_move_position, (s32)"me",
    -30000000, -29999998, 2000, -229959040, 4, 65540, 0, 2,
    1,
};

s32 hbross_find_event[] = {
    786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0, 0,
    0, 0, 0, 0, 30, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 262235, (s32)evt_npc_flag_onoff,
    1, (s32)"me", 2097152, 110, 65539, 0, 327771, (s32)evt_npc_add_rotate,
    (s32)"slave_0", 0, 0, 30, 65545, 1, 65540, 0,
    112, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"BRO_A_1A", 65546, 400, 110,
    65546, 500, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"BRO_S_1", 112, 327771,
    (s32)evt_npc_set_rotate, (s32)"slave_0", 0, 0, 0, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 131125, -29999999, 25, 196699, (s32)evt_npc_get_dir,
    (s32)"me", -29999997, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229979520,
    327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998, 262235, (s32)evt_npc_flag_onoff,
    0, (s32)"slave_0", 128, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999,
    -29999998, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_0", 32, 196699, (s32)evt_npc_set_attack_mode,
    (s32)"slave_0", 12, 589915, (s32)evt_npc_jump_position, (s32)"slave_0", -30000000, -29999999, -29999998,
    1000, 0, -229923200, 0, 196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 32, 327771, (s32)evt_npc_set_position, (s32)"slave_0",
    0, -1000, 0, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

USER_FUNC(chain_main) {
    NpcEntry* me = evtNpcNameToPtr(event, "me");
    NpcEntry* end = me->slaves[3];
    NpcEntry* cur;
    NpcEntry* prev;
    f32 len, sag, cx, cy, cz, dx, dy, dz, t;
    s32 i;
    dx = me->position.x - end->position.x;
    dy = me->position.y - end->position.y;
    dz = me->position.z - end->position.z;
    len = (f32)sqrt(dx * dx + dy * dy + dz * dz) / 4.0f;
    if (len < 10.0f) {
        len = 10.0f;
    }
    sag = 300.0f / (len * len);
    cur = me->slaves[0];
    cy = cur->position.y;
    cy -= sag;
    cx = cur->position.x;
    cz = cur->position.z;
    dx = me->position.x - cx;
    dy = me->position.y - cy;
    dz = me->position.z - cz;
    {
    f32 dist = (f32)sqrt(dx * dx + dy * dy + dz * dz);
    t = 1.0f - len / dist;
    }
    cy = dy * t + cy;
    cx = dx * t + cx;
    cz = dz * t + cz;
    if (cy < me->territoryBase.y) {
        cy = me->territoryBase.y;
    }
    {
    Vec a = {0.0f, 0.0f, 0.0f};
    a.x = cx;
    a.y = cy;
    a.z = cz;
    cur->position = a;
    }
    for (i = 0; i < 2; i++) {
        cur = me->slaves[i + 1];
        prev = me->slaves[i];
        cy = cur->position.y;
        cy -= sag;
        cx = cur->position.x;
        cz = cur->position.z;
        dx = prev->position.x - cx;
        dy = prev->position.y - cy;
        dz = prev->position.z - cz;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        cy = dy * t + cy;
        cx = dx * t + cx;
        cz = dz * t + cz;
        if (cy < me->territoryBase.y) {
            cy = me->territoryBase.y;
        }
        {
        Vec b = {0.0f, 0.0f, 0.0f};
        b.x = cx;
        b.y = cy;
        b.z = cz;
        cur->position = b;
        }
    }
    for (i = 3; i >= 1; i--) {
        cur = me->slaves[i - 1];
        prev = me->slaves[i];
        cy = cur->position.y;
        cy -= sag;
        cx = cur->position.x;
        cz = cur->position.z;
        dx = prev->position.x - cx;
        dy = prev->position.y - cy;
        dz = prev->position.z - cz;
        t = 1.0f - len / (f32)sqrt(dx * dx + dy * dy + dz * dz);
        cy = dy * t + cy;
        cx = dx * t + cx;
        cz = dz * t + cz;
        if (cy < me->territoryBase.y) {
            cy = me->territoryBase.y;
        }
        {
        Vec c = {0.0f, 0.0f, 0.0f};
        c.x = cx;
        c.y = cy;
        c.z = cz;
        cur->position = c;
        }
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(camGetPos) {
    s32* args = event->args;
    evtSetFloat(event, args[0], *(f32*)((u8*)camGetPtr(CAMERA_3D) + 0xc));
    return EVT_RETURN_DONE;
}


USER_FUNC(cliffCheck) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    f32 dirv;
    f32 hx, hy, hz, dist, nx, ny, nz;
    HitEntry* h1;
    HitEntry* h2;
    if (90.0f == npcTransRytoFaceDir(npc)) {
        dirv = 1.0f;
    } else {
        dirv = -1.0f;
    }
    dist = 5.0f;
    h1 = hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, 1.0f + npc->position.y, npc->position.z, 0.0f, -1.0f, 0.0f);
    dist = 5.0f;
    h2 = hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, 1.0f + npc->position.y, npc->position.z, dirv, -1.0f, 0.0f);
    if (h1 && h2) {
        evtSetValue(event, args[0], 0);
    } else if (h1 && !h2) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 2);
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(upperCheck) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    f32 hx, hy, hz, dist, nx, ny, nz;
    HitEntry* h1;
    HitEntry* h2;
    dist = 5.0f;
    h1 = hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x - 15.0f, 30.0f + npc->position.y, npc->position.z, 0.0f, 2.0f, 0.0f);
    h2 = hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, 15.0f + npc->position.x, 30.0f + npc->position.y, npc->position.z, 0.0f, 2.0f, 0.0f);
    if (h1 || h2) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(getSpdWalk) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    evtSetFloat(event, args[0], npc->territoryLoiter.z);
    return EVT_RETURN_DONE;
}


USER_FUNC(getSpdRun) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    evtSetFloat(event, args[0], npc->territoryHoming.z);
    return EVT_RETURN_DONE;
}


USER_FUNC(limitSpd) {
    f32 v = evtGetFloat(event, event->args[0]);
    evtNpcNameToPtr(event, "me")->field_1D0 = v;
    return EVT_RETURN_DONE;
}


s32 hbross_lost_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 500,
    131163, (s32)evt_npc_reverse_ry, (s32)"me", 65546, 1000, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 hbross_return_event[] = {
    131163, (s32)evt_npc_set_stay_anim, (s32)"me", 65546, 500, 131163, (s32)evt_set_dir_to_home, (s32)"me",
    196699, (s32)evt_npc_get_dir, (s32)"me", -29999997, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, -229897600,
    458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 0, -229959040, 4,
    131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 hbross_blow_event[] = {
    196699, (s32)evt_npc_set_attack_mode, (s32)"slave_0", 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000, 0, 65630,
    (s32)enemy_common_blow_event, 2, 1,
};

s32 enemy_event_dead_event[] = {
    131122, -29999990, (s32)"me", 65630, (s32)enemy_event_dead_event_sub, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 enemy_slave_common_dead_event[] = {
    131163, (s32)evt_npc_delete, (s32)"me", 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 enemy_common_flag_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 269616152, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 testenemynpc_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 npc_urouro_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1536, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 kuriboo_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 patakuri_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 patapata_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1114136, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 patamet_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 chorobon_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1179672, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 pansy_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 twinkling_pansy_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 karon_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65630, (s32)enemy_common_dead_event, 2,
    1,
};

s32 sambo_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 8, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)"me", 1049616, 2, 1,
};

s32 togedaruma_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 piders_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 2,
    1,
};

s32 basabasa_dead_event[] = {
    65630, (s32)enemy_common_dead_event, 2, 1,
};

s32 basabasa2_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 basabasa2_dead_event[] = {
    65630, (s32)enemy_common_dead_event, 2, 1,
};

s32 teresa_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 teresa_dead_event[] = {
    65630, (s32)enemy_common_dead_event, 2, 1,
};

s32 bubble_init_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 1048600, 262235, (s32)evt_npc_status_onoff, 1,
    (s32)"me", 2, 2, 1,
};

s32 hbom_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 2, 1,
};

s32 zakowiz_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65630, (s32)enemy_common_dead_event, 2,
    1,
};

s32 hannya_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me", 2, 2,
    1,
};

s32 kamec_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65630, (s32)enemy_common_dead_event, 2,
    1,
};

s32 kamec2_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65630, (s32)enemy_common_dead_event, 2,
    1,
};

s32 hbross_dead_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65630, (s32)enemy_common_dead_event, 2,
    1,
};

s32 zakoM2D_dead_event[] = {
    262235, (s32)evt_npc_status_onoff, 0, (s32)"slave_0", 4, 65630, (s32)enemy_2d_common_dead_event, 2,
    1,
};

s32 wanwan_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 131163,
    (s32)mahoon_get_groupname, -29999990, 393307, (s32)evt_npc_slave_entry, (s32)"me", 0, -29999990, -30000000,
    (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim, -30000000, (s32)"WAN_S_1B", 65630, (s32)wanwan_init_event_sub, 393307,
    (s32)evt_npc_slave_entry, (s32)"me", 1, -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim,
    -30000000, (s32)"WAN_S_1B", 65630, (s32)wanwan_init_event_sub, 393307, (s32)evt_npc_slave_entry, (s32)"me", 2,
    -29999990, -30000000, (s32)enemy_slave_common_dead_event, 196699, (s32)evt_npc_set_anim, -30000000, (s32)"WAN_S_1B", 65630,
    (s32)wanwan_init_event_sub, 393307, (s32)evt_npc_slave_entry, (s32)"me", 3, -29999990, -30000000, (s32)enemy_slave_common_dead_event,
    196699, (s32)evt_npc_set_anim, -30000000, (s32)"WAN_Z_2", 65630, (s32)wanwan_init_event_sub, 2, 1,
};

s32 wanwan_init_event_sub[] = {
    262235, (s32)evt_npc_flag_onoff, 1, -30000000, 32, 262235, (s32)evt_npc_flag_onoff, 0,
    -30000000, 131072, 262235, (s32)evt_npc_flag_onoff, 0, -30000000, 16, 262235,
    (s32)evt_npc_flag_onoff, 0, -30000000, 512, 262235, (s32)evt_npc_flag_onoff, 0, -30000000,
    1024, 262235, (s32)evt_npc_flag_onoff, 0, -30000000, 2048, 262235, (s32)evt_npc_flag_onoff,
    1, -30000000, 16777216, 262235, (s32)evt_npc_flag_onoff, 1, -30000000, 2097152,
    262235, (s32)evt_npc_flag_onoff, 1, -30000000, 64, 262235, (s32)evt_npc_flag_onoff, 1,
    -30000000, 262144, 327771, (s32)evt_npc_get_home_position, (s32)"me", -29999999, -29999998, -29999997,
    327771, (s32)evt_npc_set_position, -30000000, -29999999, -29999998, -29999997, 2, 1,
};

s32 wanwan_move_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 196699,
    (s32)evt_npc_set_attack_mode, (s32)"me", 0, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"WAN_S_1A", 110,
    65541, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    327771, (s32)evt_mario_get_pos, 0, -29999990, -29999989, -29999988, 131101, -30000000,
    -29999990, 196699, (s32)evt_npc_set_ry, (s32)"me", 270, 32, 196699, (s32)evt_npc_set_ry,
    (s32)"me", 90, 33, 65545, 1, 6, 112, 110,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 2097152, 65546, 1500, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 2097152, 112, 110, 65541, 0,
    65627, (s32)chain_main, 65545, 1, 6, 112, 110, 65541,
    0, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"WAN_A_1", 65546, 1000, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"WAN_S_1A", 65546, 500, 6, 112, 65539,
    0, 327771, (s32)evt_npc_get_home_position, (s32)"me", -30000000, -29999999, -29999998, 196699,
    (s32)evt_sub_random, 360, -29999997, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997,
    50, 196699, (s32)evt_sub_random, 15, -29999996, 131125, -29999996, 15,
    131122, -29999995, -29999996, 131122, -29999994, -29999996, 131127, -29999994,
    17, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_WAN_MOVE1", -30000000, -29999999, -29999998, 0,
    589915, (s32)evt_npc_jump_position, (s32)"me", -30000000, -29999999, -29999998, -29999994, 80,
    -29999995, 1, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_WAN_LANDING1", -30000000, -29999999, -29999998,
    0, 65545, 1, 65540, 0, 2, 1,
};

s32 wanwan_find_event[] = {
    262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 2097152, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"WAN_A_1", 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0,
    0, 0, 0, 0, 0, 30, 196699, (s32)evt_npc_set_attack_mode,
    (s32)"me", 12, 110, 65541, 0, 65627, (s32)chain_main, 65545,
    1, 6, 112, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_WAN_MOVE2", -30000000, -29999999, -29999998, 0,
    393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_FLD_ENM_WAN_ATTACK2", -30000000, -29999999, -29999998, 0, 327771,
    (s32)evt_npc_get_home_position, (s32)"me", -30000000, -29999999, -29999998, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -29999997, 327771, (s32)evt_npc_add_dirdist, -30000000, -29999998, -29999997, 100,
    655451, (s32)evt_npc_glide_position, (s32)"me", -30000000, -29999999, -29999998, 0, 600,
    -230000000, 0, 6, 65546, 1500, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

USER_FUNC(zakoEntryDokan) {
    char names[3][16];
    char nm3[32];
    NpcEntry* me = evtNpcNameToPtr(event, "me");
    NpcEntry* zako;
    s32 i;
    if (!strcmp(me->description, "\214R\222c\203U\203R\202\252\202\305\202\351\223y\212\307\202P\000\000\000")) {
        strcpy(names[0], "\214R\222c\203U\203R\223y\212\307\202P\000");
        strcpy(names[1], "\214R\222c\203U\203R\223y\212\307\202Q\000");
        strcpy(names[2], "\214R\222c\203U\203R\223y\212\307\202R\000");
        strcpy(nm3, "MOBJ_mobj9");
    }
    if (!strcmp(me->description, "\214R\222c\203U\203R\202\252\202\305\202\351\223y\212\307\202Q\000\000\000")) {
        strcpy(names[0], "\214R\222c\203U\203R\223y\212\307\202S\000");
        strcpy(names[1], "\214R\222c\203U\203R\223y\212\307\202T\000");
        strcpy(names[2], "\214R\222c\203U\203R\223y\212\307\202U\000");
        strcpy(nm3, "MOBJ_mobj14");
    }
    {
        const char* hn = hitGetName(marioGetPtr()->hitobjStandOn);
        if (hn && !strcmp(hn, nm3)) return EVT_RETURN_DONE;
        hn = hitGetName(marioGetPtr()->hitobjJumpFrom);
        if (hn && !strcmp(hn, nm3)) return EVT_RETURN_DONE;
        hn = hitGetName(marioGetPtr()->hitobjFront);
        if (hn && !strcmp(hn, nm3)) return EVT_RETURN_DONE;
    }
    for (i = 0; i < 3; i++) {
        zako = npcNameToPtr(names[i]);
        if (zako->position.y <= -75.0f) {
            zako->flags |= 0x20410;
            zako->flags &= ~0x20;
            zako->jumpFlags |= 0x1002;
            zako->jumpFlags &= 0xEFAFFFFB;
            {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = me->position.x;
            pos.y = me->position.y - 35.0f;
            pos.z = me->position.z;
            zako->position = pos;
            }
            zako->rotation = (Vec){0.0f, 0.0f, 0.0f};
            zako->unitWork[0] = (void*)1;
            if (zako->moveEvent) {
                EventEntry* e;
                if (zako->regularEvtId) {
                    evtDeleteID(zako->regularEvtId);
                }
                e = evtEntry(zako->moveEvent, 0, 0x20);
                e->wNpcEventType = 1;
                e->ownerNPC = zako;
                zako->regularEvtId = e->eventId;
            }
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(dokanCheck) {
    s32* args = event->args;
    char name[32];
    NpcEntry* me = evtNpcNameToPtr(event, "me");
    if (!strcmp(me->description, "\214R\222c\203U\203R\202\252\202\305\202\351\223y\212\307\202P\000\000\000")) {
        strcpy(name, "mobj9");
    }
    if (!strcmp(me->description, "\214R\222c\203U\203R\202\252\202\305\202\351\223y\212\307\202Q\000\000\000")) {
        strcpy(name, "mobj14");
    }
    if (mobjNameToPtrNoAssert(name)) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(zakoEntryFall) {
    char names[3][16];
    NpcEntry* me = evtNpcNameToPtr(event, "me");
    NpcEntry* zako;
    s32 i;
    if (!strcmp(me->description, "\214R\222c\203U\203R\215~\211\272\222n\223_\202P\000")) {
        strcpy(names[0], "\214R\222c\203U\203R\215~\211\272\202P\000");
        strcpy(names[1], "\202\310\202\265");
        strcpy(names[2], "\202\310\202\265");
    }
    if (!strcmp(me->description, "\214R\222c\203U\203R\215~\211\272\222n\223_\202Q\201Q\202P\000")) {
        strcpy(names[0], "\214R\222c\203U\203R\215~\211\272\202P\000");
        strcpy(names[1], "\214R\222c\203U\203R\215~\211\272\202Q\000");
        strcpy(names[2], "\214R\222c\203U\203R\215~\211\272\202R\000");
    }
    if (!strcmp(me->description, "\214R\222c\203U\203R\215~\211\272\222n\223_\202Q\201Q\202Q\000")) {
        strcpy(names[0], "\214R\222c\203U\203R\215~\211\272\202S\000");
        strcpy(names[1], "\214R\222c\203U\203R\215~\211\272\202T\000");
        strcpy(names[2], "\214R\222c\203U\203R\215~\211\272\202U\000");
    }
    for (i = 0; i < 3; i++) {
        zako = npcNameToPtr_NoAssert(names[i]);
        if (zako && zako->position.y <= -75.0f) {
            zako->flags |= 0x20410;
            zako->flags &= ~0x20;
            zako->jumpFlags |= 0x1002;
            zako->jumpFlags &= 0xEF8FFFFB;
            {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = me->position.x;
            pos.y = me->position.y;
            pos.z = me->position.z;
            zako->position = pos;
            }
            zako->rotation = (Vec){0.0f, 0.0f, 0.0f};
            zako->unitWork[0] = (void*)2;
            if (zako->moveEvent) {
                EventEntry* e;
                if (zako->regularEvtId) {
                    evtDeleteID(zako->regularEvtId);
                }
                e = evtEntry(zako->moveEvent, 0, 0x20);
                e->wNpcEventType = 1;
                e->ownerNPC = zako;
                zako->regularEvtId = e->eventId;
            }
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_DONE;
}


USER_FUNC(unk_800ece0c) {
    s32* args;
    NpcEntry* npc;
    f32 x, y, z;
    EffectEntry* eff;
    npc = evtNpcNameToPtr(event, "me");
    args = event->args;
    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    eff = (EffectEntry*)evtGetValue(event, args[3]);
    if (isFirstCall) {
        npc->unitWork[0] = effFireEntry(x, y, z, 1.0f, 5, 1000);
        npc->unitWork[1] = (void*)eff;
    }
    eff = npc->unitWork[0];
    npc->unitWork[1] = (void*)((s32)npc->unitWork[1] - 1);
    if ((s32)npc->unitWork[1] <= 30) {
        f32 sc = intplGetValue(1, 30 - (s32)npc->unitWork[1], 30, 1.0f, 0.0f);
        *(f32*)((u8*)eff->userdata + 0x78) = sc;
        *(f32*)((u8*)eff->userdata + 0x7c) = sc;
        ((u8*)eff->userdata)[0x10] = (u8)intplGetValue(0, 30 - (s32)npc->unitWork[1], 30, 255.0f, 0.0f);
    }
    if ((s32)npc->unitWork[1] <= 0) {
        effDelete(eff);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}


USER_FUNC(set_bottle_flag_init) {
    NpcEntry* npc = evtNpcNameToPtr(event, "slave_0");
    npc->flags |= 0x28020020;
    npc->field_31E |= 0x1f;
    return EVT_RETURN_DONE;
}


USER_FUNC(gesso_ground_check) {
    s32* args = event->args;
    NpcEntry* npc = evtNpcNameToPtr(event, "me");
    f32 hx, hy, hz, dist, nx, ny, nz;
    dist = 5.0f;
    if (hitCheckFilter(0, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, 1.0f + npc->position.y, npc->position.z, 0.0f, -1.0f, 0.0f)) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}


s32 kuriboo2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 134217728, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me",
    4, 131163, (s32)limitSpd, -229590400, 2, 1,
};

s32 kuriboo2D_move_event[] = {
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 65539, 0, 262235, (s32)evt_npc_status_onoff,
    1, (s32)"me", 4096, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000,
    -250000000, 131163, (s32)camGetPos, -29999999, 131126, -30000000, -29999999, 131100,
    -30000000, 250, 65540, 1, 33, 65545, 1, 65540,
    0, 65539, 1, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"W_1", 65539,
    2, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235,
    (s32)evt_npc_facedirection_add, (s32)"me", -30000000, 1000, 131163, (s32)getSpdWalk, -29999997, 458843,
    (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 0, -29999997, 4, 131163,
    (s32)evt_npc_reverse_ry, (s32)"me", 65545, 1, 65540, 2, 2, 1,
};

s32 kuriboo2D_find_event[] = {
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 131101, -29999999,
    -100, 786523, (s32)evt_eff_fukidashi, 1, 0, (s32)"me", 0, 0,
    0, 0, 0, 0, 0, 30, 33, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"R_1", 262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000,
    196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 131163, (s32)evt_npc_reverse_ry, (s32)"me", 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me",
    -30000000, 1000, 131163, (s32)getSpdRun, -29999997, 458843, (s32)evt_npc_move_position, (s32)"me",
    -30000000, -29999998, 4000, -29999997, 2, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"S_1", 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 zako2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 134217728, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 262235, (s32)evt_npc_status_onoff, 1, (s32)"me",
    2097152, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me", 4, 131163, (s32)limitSpd,
    -229590400, 2, 1,
};

s32 zako2D_move_event[] = {
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me",
    1024, 65539, 0, 262235, (s32)evt_npc_status_onoff, 1, (s32)"me", 4096,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000, -250000000, 131163, (s32)camGetPos,
    -29999999, 131126, -30000000, -29999999, 131100, -30000000, 250, 65540,
    1, 33, 65545, 1, 65540, 0, 65539, 1,
    262235, (s32)evt_npc_get_unitwork, (s32)"me", 0, -30000000, 131096, -30000000, 1,
    262235, (s32)evt_npc_set_unitwork, (s32)"me", 0, 0, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"Z_1", 262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry,
    (s32)"me", -30000000, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 16, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 65541, 35, 262235, (s32)evt_npc_status_onoff,
    1, (s32)"me", 4096, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 131125, -29999999, 1, 327771, (s32)evt_npc_set_position, (s32)"me", -30000000,
    -29999999, -29999998, 65545, 1, 6, 262235, (s32)evt_npc_flag_onoff, 1,
    (s32)"me", 16, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 131072, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"W_1", 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me", -30000000, 50, 589915, (s32)evt_npc_jump_position,
    (s32)"me", -30000000, -29999999, -29999998, 500, -229897600, -229969280, 1,
    33, 262235, (s32)evt_npc_get_unitwork, (s32)"me", 0, -30000000, 131096, -30000000,
    2, 262235, (s32)evt_npc_set_unitwork, (s32)"me", 0, 0, 196699, (s32)evt_npc_set_anim,
    (s32)"me", (s32)"S_1", 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 131072, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 589915, (s32)evt_npc_jump_position, (s32)"me",
    -30000000, -100, -29999998, 0, -229897600, -230000000, 1, 33,
    262235, (s32)evt_npc_status_onoff, 0, (s32)"me", 4096, 196699, (s32)evt_npc_set_anim, (s32)"me",
    (s32)"W_1", 65539, 10, 65647, -29999985, 65541, 0, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me",
    -30000000, 1000, 131163, (s32)getSpdWalk, -29999997, 458843, (s32)evt_npc_move_position, (s32)"me",
    -30000000, -29999998, 0, -29999997, 4, 131163, (s32)evt_npc_reverse_ry, (s32)"me",
    65545, 1, 6, 112, 65539, 11, 131163, (s32)cliffCheck,
    -30000000, 131096, -30000000, 1, 65631, -29999985, 131163, (s32)evt_npc_reverse_ry,
    (s32)"me", 65545, 1, 65540, 10, 33, 65545, 1,
    65540, 11, 2, 1,
};

s32 zako2D_find_event[] = {
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 131101, -29999999, -100, 786523, (s32)evt_eff_fukidashi,
    1, 0, (s32)"me", 0, 0, 0, 0, 0,
    0, 0, 30, 33, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"A_1",
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me",
    -30000000, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 262235,
    (s32)evt_npc_facedirection_add, (s32)"me", -30000000, 1000, 131163, (s32)getSpdRun, -29999997, 458843,
    (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 3000, -29999997, 2, 196699,
    (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 65539, 99, 131163, (s32)evt_npc_return_interrupt, (s32)"me",
    2, 1,
};

s32 dokan2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"me", 160, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me",
    4, 2, 1,
};

s32 dokan2D_regl_event[] = {
    65539, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000, -250000000,
    131163, (s32)camGetPos, -29999999, 131126, -30000000, -29999999, 131100, -30000000,
    250, 65540, 1, 33, 65545, 1, 65540, 0,
    65539, 1, 131163, (s32)dokanCheck, -30000000, 131096, -30000000, 0,
    65540, 99, 33, 65627, (s32)zakoEntryDokan, 65545, 120, 65540,
    1, 65539, 99, 131163, (s32)evt_npc_delete, (s32)"me", 2, 1,
};

s32 fall2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me", 131072, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"me", 160, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me",
    4, 2, 1,
};

s32 fall2D_regl_event[] = {
    65539, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000, -250000000,
    131163, (s32)camGetPos, -29999999, 131126, -30000000, -29999999, 131100, -30000000,
    250, 65540, 1, 33, 65545, 1, 65540, 0,
    65539, 1, 65627, (s32)zakoEntryFall, 65545, 120, 65540, 1,
    2, 1,
};

s32 zakoM2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 134217728, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me",
    4, 131163, (s32)limitSpd, -229590400, 393307, (s32)evt_npc_slave_entry, (s32)"me", 0,
    (s32)"c_zako_km\000\000", -30000000, (s32)enemy_slave_common_dead_event, 327771, (s32)evt_npc_set_position, (s32)"slave_0", 0, -1000,
    0, 65627, (s32)set_bottle_flag_init, 2, 1,
};

s32 zakoM2D_move_event[] = {
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 65539, 2, 262235, (s32)evt_npc_status_onoff,
    1, (s32)"me", 4096, 262235, (s32)evt_npc_status_check, (s32)"me", 4, -30000000,
    131096, -30000000, 0, 65540, 3, 33, 65545, 1,
    65540, 2, 65539, 3, 110, 65541, 0, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 458843, (s32)evt_npc_move_position, (s32)"me",
    -30000000, -29999998, 100, 0, 0, 65545, 1, 6,
    112, 65539, 0, 262235, (s32)evt_npc_status_onoff, 1, (s32)"me", 4096,
    327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000, -250000000, 131163, (s32)camGetPos,
    -29999999, 131126, -30000000, -29999999, 131100, -30000000, 250, 65540,
    1, 33, 65545, 1, 65540, 0, 65539, 1,
    262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me",
    -30000000, 65545, 1, 65540, 1, 2, 1,
};

s32 zakoM2D_find_event[] = {
    196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"B_1", 327771, (s32)evt_npc_get_position, (s32)"me", -30000000,
    -29999999, -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me", -30000000, 10, 131125,
    -29999999, 20, 327771, (s32)evt_npc_set_position, (s32)"slave_0", -30000000, -29999999, -29999998,
    262235, (s32)evt_npc_flag_onoff, 0, (s32)"slave_0", 32, 262235, (s32)evt_npc_flag_onoff, 0,
    (s32)"slave_0", 128, 131101, -29999990, 200, 327771, (s32)evt_npc_get_position, (s32)"me",
    -30000000, -29999999, -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me", -30000000, 100,
    589915, (s32)evt_npc_jump_position, (s32)"slave_0", -30000000, -29999999, -29999998, 0, -229692800,
    -229692800, 0, 32, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 262235, (s32)evt_npc_facedirection_add, (s32)"me", -30000000, -29999990, 131132, -29999990,
    -229998464, 589915, (s32)evt_npc_jump_position, (s32)"slave_0", -30000000, -29999999, -29999998, 0,
    -29999990, -229692800, 0, 33, 327771, (s32)evt_npc_get_position, (s32)"slave_0", -30000000,
    -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_CONDITION_FIRE1", -30000000, -29999999, -29999998,
    0, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_ENM_3RD2_CRASH1", -30000000, -29999999, -29999998, 0,
    131126, -29999999, 5, 131125, -29999998, 200, 983131, (s32)evt_eff,
    (s32)"", (s32)"kemuri_test", 16, -30000000, -29999999, -29999998, -229998976, 0,
    0, 0, 0, 0, 0, 0, 65541, 12,
    983131, (s32)evt_eff64, (s32)"", (s32)"glass_n64", 0, -30000000, -29999999, -29999998,
    -229998976, 30, 0, 0, 0, 0, 0, 0,
    6, 107, 327771, (s32)unk_800ece0c, -30000000, -29999999, -29999998, 60,
    109, 196699, (s32)evt_npc_set_anim, (s32)"slave_0", (s32)"B_2", 65545, 10, 262235,
    (s32)evt_npc_flag_onoff, 1, (s32)"slave_0", 128, 65545, 60, 327771, (s32)evt_npc_set_position,
    (s32)"slave_0", 0, -1000, 0, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"slave_0",
    32, 2, 1,
};

s32 unk_evt_803497e8[] = {
    110, 65541, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999,
    -29999998, 458843, (s32)evt_npc_move_position, (s32)"me", -30000000, -29999998, 100, 0,
    0, 65545, 1, 6, 112, 262235, (s32)evt_get_target_dir, (s32)"me",
    (s32)"mario", -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 327771, (s32)evt_mario_get_pos,
    0, -30000000, -29999999, -29999998, 327771, (s32)evt_npc_get_position, (s32)"me", -29999990,
    -29999989, -29999988, 131131, -29999990, -30000000, 131098, -29999990, 0,
    131132, -29999990, -230001024, 33, 131098, -29999990, 30, 131124,
    -29999990, -229969280, 33, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"A_1", 65545,
    64, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"A_2", 65545, 24, 110,
    65545, 24, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 112, 65628,
    (s32)zakoM2D_find_event, 65545, 100, 131163, (s32)evt_npc_return_interrupt, (s32)"me", 2, 1,
};

s32 gesso2D_init_event[] = {
    65630, (s32)enemy_common_flag_init_event, 262235, (s32)evt_npc_flag_onoff, 1, (s32)"me", 134217728, 262235,
    (s32)evt_npc_flag_onoff, 0, (s32)"me", 1024, 262235, (s32)evt_npc_flag_onoff, 0, (s32)"me",
    131072, 262235, (s32)evt_npc_status_onoff, 1, (s32)"me", 268435456, 262235, (s32)evt_npc_status_onoff,
    1, (s32)"me", 2097152, 262235, (s32)evt_npc_status_onoff, 0, (s32)"me", 4,
    2, 1,
};

s32 gesso2D_move_event[] = {
    196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 65539, 0, 262235, (s32)evt_npc_status_onoff,
    1, (s32)"me", 4096, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -250000000,
    -250000000, 131163, (s32)camGetPos, -29999999, 131126, -30000000, -29999999, 131100,
    -30000000, 250, 65540, 1, 33, 65545, 1, 65540,
    0, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"S_1", 65539, 1, 131124,
    -29999999, -230000000, 131124, -29999987, -230000000, 65541, 0, 327771,
    (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998, 327771, (s32)evt_mario_get_pos, 0,
    -29999990, -29999989, -29999988, 65545, 1, 131126, -30000000, -29999990,
    131101, -30000000, 300, 65540, 5, 33, 131100, -30000000,
    -300, 65540, 5, 33, 131098, -29999999, -29999989, 7,
    33, 131098, -29999999, 90, 7, 33, 65539, 5,
    131163, (s32)gesso_ground_check, -29999985, 131096, -29999985, 0, 327771, (s32)evt_npc_get_position,
    (s32)"me", -30000000, -29999999, -29999998, 131124, -29999986, -29999999, 131131,
    -29999986, -29999987, 131130, -29999987, -229999898, 131101, -29999987, -229998976,
    131124, -29999987, -229998976, 33, 327771, (s32)evt_npc_set_position, (s32)"me", -30000000,
    -29999986, -29999998, 33, 6, 262235, (s32)evt_get_target_dir, (s32)"me", (s32)"mario",
    -30000000, 196699, (s32)evt_npc_set_ry, (s32)"me", -30000000, 327771, (s32)evt_npc_get_position, (s32)"me",
    -29999990, -29999989, -29999988, 262235, (s32)evt_npc_facedirection_add, (s32)"me", -29999990, 100,
    131125, -29999989, 50, 131099, -29999989, 350, 131122, -29999989,
    350, 33, 65541, 60, 131163, (s32)gesso_ground_check, -29999985, 131096,
    -29999985, 0, 327771, (s32)evt_npc_get_position, (s32)"me", -30000000, -29999999, -29999998,
    131124, -29999986, -29999999, 131131, -29999986, -29999987, 131130, -29999987,
    -229999898, 131101, -29999987, -229998976, 131124, -29999987, -229998976, 33,
    327771, (s32)evt_npc_set_position, (s32)"me", -30000000, -29999986, -29999998, 33, 65545,
    1, 6, 196699, (s32)evt_npc_set_anim, (s32)"me", (s32)"A_1", 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_KUPPA_GESSO_MOVE1", -29999990, -29999989, -29999988, 0, 262235, (s32)evt_npc_set_unitwork, (s32)"me",
    0, 0, 65647, -29999985, 655451, (s32)evt_npc_glide_position, (s32)"me", -29999990,
    -29999989, -29999988, 2000, -229948800, 10, 4, 0, 262235,
    (s32)evt_npc_set_unitwork, (s32)"me", 0, 1, 112, 65541, 0, 262235,
    (s32)evt_npc_get_unitwork, (s32)"me", 0, -30000000, 131096, -30000000, 1, 7,
    33, 131163, (s32)upperCheck, -30000000, 131096, -30000000, 1, 65631,
    -29999985, 7, 33, 65545, 1, 6, 196699, (s32)evt_npc_set_anim,
    (s32)"me", (s32)"S_1", 65540, 1, 2, 1,
};

