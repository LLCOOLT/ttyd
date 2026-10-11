// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(ss_ch_check);
USER_FUNC(ss_ch_check) {
    u64 out; // FAKEMATCH (decomp-permuter): reorders the args[1] load
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    out = args[1];
    evtSetFloat(event, out, ssf[index]);
    return EVT_RETURN_DONE;
}
