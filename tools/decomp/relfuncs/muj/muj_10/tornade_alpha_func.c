// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(tornade_alpha_func);
USER_FUNC(tornade_alpha_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 alpha = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[82] = alpha;
    return EVT_RETURN_DONE;
}
