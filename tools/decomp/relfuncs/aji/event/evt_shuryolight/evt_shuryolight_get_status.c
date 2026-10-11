// proto: static USER_FUNC(evt_shuryolight_get_status);
static USER_FUNC(evt_shuryolight_get_status) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    ShuryoLight* light = &slhp->lights[index];

    evtSetValue(event, args[1], light->status);
    return EVT_RETURN_DONE;
}
