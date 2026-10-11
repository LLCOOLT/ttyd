// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// proto: USER_FUNC(ramp_r);
double sin(double x);

USER_FUNC(ramp_r) {
    f32 amp = __fabsf(evtGetFloat(event, GW(0)));
    f32 wave = sin(gp->retraceCount / 15.0f);

    evtSetFloat(event, LW(10), 1.8f * amp * wave);
    return EVT_RETURN_DONE;
}
