// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(dai_moveti_set);
static USER_FUNC(dai_moveti_set) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    daiv = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}
