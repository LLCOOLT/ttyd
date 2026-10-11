// include: manager/evtmgr_cmd.h
// decl: static Vec daiv;
// proto: static USER_FUNC(dai_moveti_get);
static USER_FUNC(dai_moveti_get) {
    s32* args = event->args;

    evtSetFloat(event, args[0], daiv.x);
    evtSetFloat(event, args[1], daiv.y);
    evtSetFloat(event, args[2], daiv.z);
    return EVT_RETURN_DONE;
}
