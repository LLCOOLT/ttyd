// include: driver/effdrv.h
// proto: static USER_FUNC(efffukidashichange_cam);
static USER_FUNC(efffukidashichange_cam) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 camId = evtGetValue(event, args[1]);

    ((s32*)effNameToPtr(name)->userdata)[19] = camId;
    return EVT_RETURN_DONE;
}
