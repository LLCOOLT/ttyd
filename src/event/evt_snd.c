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

USER_FUNC(evt_snd_bgmon) {
    EvtWord* args = event->args;
    psndBGMOn(args[0], (char*)args[1]);
    return EVT_RETURN_DONE;
}

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

USER_FUNC(evt_snd_bgmoff) {
    psndBGMOff(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgmoff_f) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgm_freq) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGM_rate(a, t);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_bgm_scope) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndBGMScope(a, t);
    return EVT_RETURN_DONE;
}

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

USER_FUNC(evt_snd_sfxoff) {
    psndSFXOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfxchk) {
    EvtWord* args = event->args;
    evtSetValue(event, args[1], psndSFXChk(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_pit) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_pit(id, t);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_vol) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 t = evtGetValue(event, args[1]);
    psndSFX_vol(id, t);
    return EVT_RETURN_DONE;
}

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

USER_FUNC(evt_snd_sfx_dist) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    psndSFX_dist(id, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envon) {
    EvtWord* args = event->args;
    ((PsndENVOnS32S32Fn)psndENVOn)(args[0], args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envon_f) {
    EvtWord* args = event->args;
    s32 flags = args[0];
    const char* name = (const char*)args[1];
    s32 fadetime = evtGetValue(event, args[2]);
    psndENVOn_f_d(flags, name, fadetime, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envoff) {
    psndENVOff(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_envoff_f) {
    EvtWord* args = event->args;
    s32 a = args[0];
    s32 t = evtGetValue(event, args[1]);
    psndENVOff_f_d(a, t, 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_env_lpf) {
    EvtWord* args = event->args;
    s32 a = args[0];
    psndENV_LPF(a, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_set_rev_mode) {
    psndSetReverb(event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_snd_sfx_all_stop) {
    psndSFXAllOff();
    return EVT_RETURN_DONE;
}
