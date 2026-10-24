#pragma once

#include "evt/evt_cmd.h"
#include <dolphin/types.h>

USER_FUNC(evt_map_playanim);

USER_FUNC(evt_map_blend_off);
USER_FUNC(evt_map_get_fog);
USER_FUNC(evt_map_replayanim);
USER_FUNC(evt_map_set_blend);
USER_FUNC(evt_map_set_fog);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_trans);
extern EvtWord evt_nonride_airport[];
extern EvtWord evt_ride_airport[];
