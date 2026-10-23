#pragma once

#include "evt/evt_cmd.h"
#include <dolphin/types.h>

USER_FUNC(snd_door_in);
USER_FUNC(snd_door_out);
USER_FUNC(door_entry);

extern s32 door_close_se[];
extern s32 door_dark[];
extern s32 door_light[];
extern s32 door_light2[];
extern s32 door_open_se[];
extern s32 door_up_se[];
extern s32 evt_door_close[];
extern s32 evt_door_close_roll[];
USER_FUNC(evt_door_data_copy);
extern s32 evt_door_entry[];
extern s32 evt_door_open[];
extern s32 evt_door_open_bom_01[];
extern s32 evt_door_open_quick[];
extern s32 evt_door_open_roll[];
extern s32 evt_door_setup[];
extern s32 house_close_se[];
