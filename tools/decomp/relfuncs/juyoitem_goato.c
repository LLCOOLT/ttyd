// include: driver/itemdrv.h
// include: driver/icondrv.h
// proto: static USER_FUNC(juyoitem_goato);
static USER_FUNC(juyoitem_goato) {
    iconFlagOn(((ItemEntry*)event->lwData[8])->name, 2);
    return EVT_RETURN_DONE;
}
