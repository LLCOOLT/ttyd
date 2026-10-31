// evt_mobj.c: script commands for map objects (mobj): blocks, item boxes, save blocks and switches.
#pragma once

#include "evt/evt_cmd.h"
#include "driver/mobjdrv.h"
#include "version.h"

USER_FUNC(evt_mobj_delete);
USER_FUNC(evt_mobj_entry);
USER_FUNC(evt_mobj_flag_onoff);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_get_x_position);
USER_FUNC(evt_mobj_get_y_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_kururing_floor);
USER_FUNC(evt_mobj_recovery_blk);
USER_FUNC(evt_mobj_save_blk);
USER_FUNC(evt_mobj_set_anim);
USER_FUNC(evt_mobj_set_position);
USER_FUNC(evt_mobj_set_scale);
USER_FUNC(evt_mobj_set_x_position);
USER_FUNC(evt_mobj_set_y_position);

extern EvtWord mobj_save_blk_sysevt[];

USER_FUNC(evt_mobj_check);
USER_FUNC(evt_mobj_get_kindname);
USER_FUNC(evt_mobj_set_z_position);
USER_FUNC(evt_mobj_exec_cancel);
USER_FUNC(evt_mobj_set_gravity_bound);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_mobj_set_camid);
USER_FUNC(evt_mobj_hitevt_onoff);
USER_FUNC(evt_mobj_hit_onoff);
USER_FUNC(evt_mobj_switch_blue);
USER_FUNC(evt_mobj_floatswitch_blue);
USER_FUNC(evt_mobj_tornadoswitch_blue);
USER_FUNC(evt_mobj_switch_red);
USER_FUNC(evt_mobj_floatswitch_red);
USER_FUNC(evt_mobj_tornadoswitch_red);
USER_FUNC(evt_mobj_timerswitch);
USER_FUNC(evt_mobj_rideswitch_a);
USER_FUNC(evt_mobj_rideswitch_b);
USER_FUNC(evt_mobj_rideswitch_lightblue);
USER_FUNC(evt_mobj_jumpstand_red);
USER_FUNC(evt_mobj_jumpstand_blue);
USER_FUNC(evt_mobj_lv_blk);
USER_FUNC(evt_mobj_float_blk);
USER_FUNC(evt_mobj_switch_float_blk);
USER_FUNC(evt_mobj_lock_unlock);
USER_FUNC(evt_mobj_lock);
USER_FUNC(evt_mobj_signboard);
USER_FUNC(evt_mobj_arrow);
USER_FUNC(evt_mobj_blk);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_powerupblk);
USER_FUNC(evt_mobj_brick);
USER_FUNC(evt_mobj_breaking_floor);
USER_FUNC(evt_mobj_trap);
USER_FUNC(evt_mobj_bombrock);
USER_FUNC(evt_mobj_koopa_ojama_blk);
USER_FUNC(evt_mobj_koopa_stone_blk);
USER_FUNC(evt_mobj_koopa_brick);
USER_FUNC(evt_mobj_koopa_badgeblk);
USER_FUNC(evt_mobj_koopa_hidden_blk);
USER_FUNC(evt_mobj_koopa_blk);
USER_FUNC(evt_mobj_koopa_dokan);
USER_FUNC(evt_mobj_koopa_sango);
USER_FUNC(evt_mobj_koopa_fireber_dodai);
USER_FUNC(evt_mobj_koopa_pole);

USER_FUNC(evt_mobj_get_z_position);
#if VERSION == VERSION_DEMO || VERSION == VERSION_EU
s32 mobj_blk(MapObjectEntry* mobj);
#endif
#if VERSION == VERSION_DEMO
USER_FUNC(kpa_set_mario_dir);
USER_FUNC(kpa_get_mario_pos);
#endif
