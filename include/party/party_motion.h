// party_motion.c: partner motions (follow, jump, fall, stay, slit, upstairs) and the evt_snd_* sound script commands.
#pragma once

#include "evt/evt_cmd.h"
#include "pmario_sound.h" // PaperSoundFadeFlags arguments of the evt_snd script functions
#include "party.h"

USER_FUNC(evt_snd_bgm_scope);
USER_FUNC(evt_snd_bgmoff);
USER_FUNC(evt_snd_bgmoff_f);
USER_FUNC(evt_snd_bgmon_f);
USER_FUNC(evt_snd_envoff);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
USER_FUNC(evt_snd_sfx_pit);
USER_FUNC(evt_snd_sfx_pos);
USER_FUNC(evt_snd_sfx_vol);
USER_FUNC(evt_snd_sfxchk);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon);
void party_motion_behind_mario(PartyEntry* party);
void party_motion_behind_mario_continue(PartyEntry* party);
void party_motion_behind_mario_fly(PartyEntry* party);
void party_motion_beside_mario(PartyEntry* party);
void party_motion_damage(PartyEntry* party);
void party_motion_homing_fly(PartyEntry* party);
void party_motion_homing_walk(PartyEntry* party);
void party_motion_jump(PartyEntry* party);
void party_motion_jump2(PartyEntry* party);
void party_motion_stay(PartyEntry* party);
void party_motion_upstairs(PartyEntry* party);
void party_motion_wait(PartyEntry* party);

USER_FUNC(evt_snd_bgmon_f_d);
USER_FUNC(evt_snd_bgm_freq);
USER_FUNC(evt_snd_sfxon__);
USER_FUNC(evt_snd_sfxon_);
USER_FUNC(evt_snd_sfxon_3d_ex);
USER_FUNC(evt_snd_sfx_dist);
USER_FUNC(evt_snd_envon_f);
USER_FUNC(evt_snd_envoff_f);
USER_FUNC(evt_snd_env_lpf);
USER_FUNC(evt_snd_sfx_all_stop);
void L_partyForceSlitOff(PartyEntry* party);
void allPartySlitOn(void);
void allPartySlitOff(void);
void allPartyForceSlitOff(void);
void N_partyFollowCloseOn(PartyEntry* party);
void N_partyFollowCloseOff(PartyEntry* party);
void U_allPartySlitOffReq(void);
void partySlitReset(PartyEntry* party);

void party_set_behind_dir(PartyEntry* party, f32 dir);
s32 party_motion_fall(PartyEntry* party);
void partyChgWalkPose(PartyEntry* party, f32 speed);
