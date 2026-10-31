// evt_snd.c: sound script commands for BGM (evt_snd_bgmon), SFX (evt_snd_sfxon_3d) and environment sounds
// (evt_snd_envon).
#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"
#include "pmario_sound.h" // PaperSoundFadeFlags arguments of the evt_snd script functions

USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_bgmon_f_d);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgm_freq);
USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_sfxon);
USER_FUNC(evt_snd_sfxon__);
USER_FUNC(evt_snd_sfxon_);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_snd_sfxon_3d_ex);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxchk);
USER_FUNC(evt_snd_sfx_pit);
USER_FUNC(evt_snd_sfx_vol);
USER_FUNC(evt_snd_sfx_pos);
USER_FUNC(evt_snd_sfx_dist);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_envon_f);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfx_all_stop);
