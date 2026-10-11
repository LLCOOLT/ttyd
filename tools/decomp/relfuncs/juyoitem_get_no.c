// include: driver/itemdrv.h
// proto: static USER_FUNC(juyoitem_get_no);
static USER_FUNC(juyoitem_get_no) {
    evtSetValue(event, event->args[0], ((ItemEntry*)event->lwData[8])->itemId);
    return EVT_RETURN_DONE;
}
