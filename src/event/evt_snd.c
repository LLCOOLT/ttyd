// Sound script commands: evt_snd_* start and stop BGM, SFX and environment sounds (ENV) and set their pitch, volume,
// position, distance, low-pass filter and reverb.
#include "evt/evt_snd.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include <dolphin/mtx.h>
#include "version.h"

// FAKE: evt_snd.c calls psndENVOn through this prototype (the types it was compiled with) instead of the one in pmario_sound.h; same registers, behaviour-identical.
typedef BOOL (*PsndENVOnS32S32Fn)(s32, s32);

// Functions are defined in reverse order (-inline deferred).

/**
 * Starts BGM args[1] (a name in the BGM list) at once on the slot/flags in args[0];
 * arguments are taken as literals, not script variables.
 */
USER_FUNC(evt_snd_bgmon) {
    EvtWord* args = event->args;
    psndBGMOn(args[0], (char*)args[1]);
    return EVT_RETURN_DONE;
}

/** Starts BGM args[1] on slot/flags args[0], fading it in over args[2] milliseconds. */
USER_FUNC(evt_snd_bgmon_f) {
    EvtWord* args = event->args;
    s32 flags = args[0];
    char* name = (char*)args[1];
    s32 fadetime = evtGetValue(event, args[2]);
#if VERSION >= VERSION_JP
    psndBGMOn_f(flags, name, fadetime, 0);
#else
    psndBGMOn_f_d(flags, name, fadetime, 0);
#endif
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/**
 * Retail only: starts BGM args[1] on args[0] with fade-in args[2];
 * args[3] is meant as the old BGM's fade-out time but is read and ignored, args[2] is used for both.
 */
USER_FUNC(evt_snd_bgmon_f_d) {
    EvtWord* args = event->args;
    s32 flags = args[0];
    char* name = (char*)args[1];
    s32 fadetime = evtGetValue(event, args[2]);
    evtGetValue(event, args[3]); // as in the original: the fade-out time is read but unused, fadetime is passed for both
    psndBGMOn_f_d(flags, name, fadetime, fadetime, 0);
    return EVT_RETURN_DONE;
}
#endif

/** Stops the BGM on slot/flags args[0] at once. */
USER_FUNC(evt_snd_bgmoff) {
    psndBGMOff(event->args[0]);
    return EVT_RETURN_DONE;
}

/** Fades out the BGM on slot/flags args[0] over args[1] milliseconds. */
USER_FUNC(evt_snd_bgmoff_f) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

/**
 * Sets the playback rate of the streamed BGM on slot args[0] to args[1] (only streamed tracks change);
 * used to slow down or speed up music.
 */
USER_FUNC(evt_snd_bgm_freq) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGM_rate(a, t);
    return EVT_RETURN_DONE;
}

/**
 * Guess: muffles or restores the BGM on slot args[0].
 * args[1] > 0 sets its scope timer to 255, < 0 clears it, 0 sets 30.
 */
USER_FUNC(evt_snd_bgm_scope) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMScope(a, t);
    return EVT_RETURN_DONE;
}

/**
 * Plays sound effect args[0] (a literal name) unpositioned;
 * if args[1] names a variable it gets the sound id for later evt_snd_sfxoff/sfx_* calls.
 */
USER_FUNC(evt_snd_sfxon) {
    EvtWord* args = event->args;
    const char* name = (const char*)args[0];
    s32 out = args[1];
    if (!out) {
        psndSFXOn(name);
    } else {
        evtSetValue(event, out, psndSFXOn(name));
    }
    return EVT_RETURN_DONE;
}

/** Like evt_snd_sfxon, but the sound name args[0] is read through a script variable. */
USER_FUNC(evt_snd_sfxon__) {
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 out = args[1];
    if (!out) {
        psndSFXOn(name);
    } else {
        evtSetValue(event, out, psndSFXOn(name));
    }
    return EVT_RETURN_DONE;
}

/** Like evt_snd_sfxon, but the sound plays even while sound effects are switched off (PSND_FLAG_SFX_OFF). */
USER_FUNC(evt_snd_sfxon_) {
    EvtWord* args = event->args;
    const char* name = (const char*)args[0];
    s32 out = args[1];
    if (!out) {
        psndSFXOn_(name);
    } else {
        evtSetValue(event, out, psndSFXOn_(name));
    }
    return EVT_RETURN_DONE;
}

/**
 * Plays sound effect args[0] at world position args[1..3], so it pans and fades with the camera;
 * args[4], if a variable, gets the sound id.
 */
USER_FUNC(evt_snd_sfxon_3d) {
    EvtWord* args = event->args;
    const char* name = (const char*)args[0];
    Vec pos;
    s32 out;
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    out = args[4];
    if (!out || out == EVT_NULLPTR) {
        psndSFXOn_3D(name, &pos);
    } else {
        evtSetValue(event, out, psndSFXOn_3D(name, &pos));
    }
    return EVT_RETURN_DONE;
}

/**
 * Plays sound effect args[0] at position args[1..3] with volume args[4], pan args[5],
 * pitch args[6] and audible distance args[7]; args[8], if a variable, gets the sound id.
 */
USER_FUNC(evt_snd_sfxon_3d_ex) {
    EvtWord* args = event->args;
    const char* name = (const char*)args[0];
    Vec pos;
    u16 a, b, c, d;
    s32 out;
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    a = evtGetValue(event, args[4]);
    b = evtGetValue(event, args[5]);
    c = evtGetValue(event, args[6]);
    d = evtGetValue(event, args[7]);
    out = args[8];
    if (!out) {
        psndSFXOnEx_3D(name, &pos, a, b, c, d);
    } else {
        evtSetValue(event, out, psndSFXOnEx_3D(name, &pos, a, b, c, d));
    }
    return EVT_RETURN_DONE;
}

/** Stops the sound effect whose id is args[0] (from an evt_snd_sfxon call). */
USER_FUNC(evt_snd_sfxoff) {
    psndSFXOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

/** Writes to args[1] whether sound effect id args[0] is still playing, so scripts can wait for it. */
USER_FUNC(evt_snd_sfxchk) {
    EvtWord* args = event->args;
    evtSetValue(event, args[1], psndSFXChk(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}

/** Changes the pitch of playing sound effect id args[0] to args[1]. */
USER_FUNC(evt_snd_sfx_pit) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_pit(id, t);
    return EVT_RETURN_DONE;
}

/** Changes the volume of playing sound effect id args[0] to args[1] (0-255). */
USER_FUNC(evt_snd_sfx_vol) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_vol(id, t);
    return EVT_RETURN_DONE;
}

/** Moves playing sound effect id args[0] to world position args[1..3], for sounds that follow a moving object. */
USER_FUNC(evt_snd_sfx_pos) {
    EvtWord* args = event->args;
    Vec pos;
    s32 id = evtGetValue(event, args[0]);
    pos.x = evtGetFloat(event, args[1]);
    pos.y = evtGetFloat(event, args[2]);
    pos.z = evtGetFloat(event, args[3]);
    psndSFX_pos(id, &pos);
    return EVT_RETURN_DONE;
}

/** Sets how far playing sound effect id args[0] can be heard (args[1]) before it fades out. */
USER_FUNC(evt_snd_sfx_dist) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    psndSFX_dist(id, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

/** Starts environment (ambient) sound args[1] at once on slot/flags args[0], such as wind, water or crowds. */
USER_FUNC(evt_snd_envon) {
    EvtWord* args = event->args;
    ((PsndENVOnS32S32Fn)psndENVOn)(args[0], args[1]);
    return EVT_RETURN_DONE;
}

/** Starts environment sound args[1] on slot/flags args[0], fading in over args[2] milliseconds. */
USER_FUNC(evt_snd_envon_f) {
    EvtWord* args = event->args;
    s32 flags = args[0];
    const char* name = (const char*)args[1];
    s32 fadetime = evtGetValue(event, args[2]);
    psndENVOn_f_d(flags, name, fadetime, 0);
    return EVT_RETURN_DONE;
}

/** Stops the environment sound on slot/flags args[0] at once. */
USER_FUNC(evt_snd_envoff) {
    psndENVOff(event->args[0]);
    return EVT_RETURN_DONE;
}

/** Fades out the environment sound on slot/flags args[0] over args[1] milliseconds. */
USER_FUNC(evt_snd_envoff_f) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndENVOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

/**
 * Sets the low-pass filter of the environment sound on slot args[0] to args[1],
 * muffling it (for example when a door or wall is between Mario and the source).
 */
USER_FUNC(evt_snd_env_lpf) {
    EvtWord* args = event->args;
    s32 a = args[0];
    psndENV_LPF(a, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

/** Sets the reverb level for the map: args[0] 0-3 selects 0, 20, 40 or 60. */
USER_FUNC(evt_snd_set_rev_mode) {
    psndSetReverb(event->args[0]);
    return EVT_RETURN_DONE;
}

/** Stops every playing sound effect. */
USER_FUNC(evt_snd_sfx_all_stop) {
    psndSFXAllOff();
    return EVT_RETURN_DONE;
}
