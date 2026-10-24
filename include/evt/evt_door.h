#pragma once

#include "evt/evt_cmd.h"
#include <dolphin/types.h>

USER_FUNC(snd_door_in);
USER_FUNC(snd_door_out);
USER_FUNC(door_entry);

extern EvtWord door_close_se[];
extern EvtWord door_dark[];
extern EvtWord door_light[];
extern EvtWord door_light2[];
extern EvtWord door_open_se[];
extern EvtWord door_up_se[];
extern EvtWord evt_door_close[];
extern EvtWord evt_door_close_roll[];
USER_FUNC(evt_door_data_copy);
extern EvtWord evt_door_entry[];
extern EvtWord evt_door_open[];
extern EvtWord evt_door_open_bom_01[];
extern EvtWord evt_door_open_quick[];
extern EvtWord evt_door_open_roll[];
extern EvtWord evt_door_setup[];
extern EvtWord house_close_se[];
