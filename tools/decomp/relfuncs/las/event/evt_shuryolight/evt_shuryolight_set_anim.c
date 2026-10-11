// proto: static USER_FUNC(evt_shuryolight_set_anim);
static USER_FUNC(evt_shuryolight_set_anim) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    shuryolightSetAnim(index, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}
