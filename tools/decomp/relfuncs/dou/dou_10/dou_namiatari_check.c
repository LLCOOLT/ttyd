// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// decl: static inline f32 addf(f32 a, f32 b) { return a + b; }
// proto: USER_FUNC(dou_namiatari_check);
USER_FUNC(dou_namiatari_check) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 w = 30.0f;
    f32 d = w;
    f32 mx = mario->position.x;
    f32 mz = mario->position.z;
    BOOL hit;

    if (y <= -45.0f) {
        evtSetValue(event, args[3], 0);
        return EVT_RETURN_DONE;
    }
    if (y <= -5.0f) {
        f32 r = (50.0f + y) / 45.0f;

        w *= r;
        d *= r;
    }
    hit = TRUE;
    // FAKEMATCH (decomp-permuter): the addf inline fixes the fadds operand order
    if (__fabsf(x - mx) > __fabsf(addf(w, 20.0f))) {
        hit = FALSE;
    }
    if (__fabsf(z - mz) > __fabsf(addf(d, 10.0f))) {
        hit = FALSE;
    }
    evtSetValue(event, args[3], hit);
    return EVT_RETURN_DONE;
}
