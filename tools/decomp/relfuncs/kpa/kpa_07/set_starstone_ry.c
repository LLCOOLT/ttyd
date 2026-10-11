// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(set_starstone_ry);
USER_FUNC(set_starstone_ry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    return EVT_RETURN_DONE;
}
