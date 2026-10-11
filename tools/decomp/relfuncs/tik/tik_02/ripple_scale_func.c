// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(ripple_scale_func);
USER_FUNC(ripple_scale_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 scale = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[5] = scale;
    return EVT_RETURN_DONE;
}
