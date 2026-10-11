// include: driver/itemdrv.h
// include: driver/effdrv.h
// proto: USER_FUNC(starstone_rotate_func);
USER_FUNC(starstone_rotate_func) {
    s32* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    f32 angle = evtGetValue(event, args[1]);

    ((f32*)itemNameToPtr(name)->effect->userdata)[7] = angle;
    return EVT_RETURN_BLOCK;
}
