// Declares the shared star-power special move helpers.
#pragma once

#include "evt/evt_cmd.h"
#include "dolphin/types.h"

USER_FUNC(sac_ac_help_off);
USER_FUNC(sac_ac_help_on);
USER_FUNC(sac_cheer);
USER_FUNC(sac_cheer_end);
USER_FUNC(sac_enemy_slide_go);
USER_FUNC(sac_enemy_slide_return);
USER_FUNC(sac_handbeat);
USER_FUNC(sac_handbeat_end);
extern EvtWord sac_mario_back_home[];
extern EvtWord sac_mario_item_on_end_evt[];
extern EvtWord sac_mario_item_on_evt[];
extern EvtWord sac_start_camera_evt[];
extern EvtWord sac_start_stardust[];
USER_FUNC(sac_wao);
