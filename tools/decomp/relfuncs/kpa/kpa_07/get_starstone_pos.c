// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(get_starstone_pos);
USER_FUNC(get_starstone_pos) {
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));

    evtSetFloat(event, args[1], ((f32*)eff->userdata)[2]);
    evtSetFloat(event, args[2], ((f32*)eff->userdata)[3]);
    evtSetFloat(event, args[3], ((f32*)eff->userdata)[4]);
    return EVT_RETURN_DONE;
}
