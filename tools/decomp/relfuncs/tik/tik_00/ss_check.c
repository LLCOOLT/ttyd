// include: manager/evtmgr_cmd.h
// decl: static s32 ssf;
// proto: USER_FUNC(ss_check);
USER_FUNC(ss_check) {
    s32 a;
    s32 z;

    // FAKEMATCH (decomp-permuter): the dead condition moves the ssf load ahead of event->args; casts, temps and
    // u32 index variants do not reproduce it
    a = event->args[0];
    z = !ssf;
    if ((z && !ssf) != 0) {
    }
    evtSetFloat(event, a, ssf);
    return EVT_RETURN_DONE;
}
