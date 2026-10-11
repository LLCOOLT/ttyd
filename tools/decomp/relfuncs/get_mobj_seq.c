// include: driver/mobjdrv.h
// proto: USER_FUNC(get_mobj_seq);
USER_FUNC(get_mobj_seq) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtrNoAssert((const char*)evtGetValue(event, args[0]));

    if (mobj == NULL) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], mobj->unk1DC);
    }
    return EVT_RETURN_DONE;
}
