// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// proto: USER_FUNC(evt_eff_barriersizechange);
USER_FUNC(evt_eff_barriersizechange) {
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));

    ((f32*)eff->userdata)[4] = evtGetFloat(event, args[1]);
    return EVT_RETURN_DONE;
}
