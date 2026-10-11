// include: driver/effdrv.h
// proto: static USER_FUNC(effitemgetchange_cam_ptr);
static USER_FUNC(effitemgetchange_cam_ptr) {
    s32* args = event->args;
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, args[0]);

    ((s32*)eff->userdata)[14] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}
