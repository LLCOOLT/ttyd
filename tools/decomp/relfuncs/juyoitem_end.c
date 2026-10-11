// include: driver/itemdrv.h
// include: driver/icondrv.h
// include: driver/effdrv.h
// include: mario/mario.h
// proto: static USER_FUNC(juyoitem_end);
static USER_FUNC(juyoitem_end) {
    ItemEntry* item = (ItemEntry*)event->lwData[8];

    effSoftDelete((EffectEntry*)event->lwData[9]);
    marioSetCamId(4);
    iconFlagOff(item->name, 0x200);
    return EVT_RETURN_DONE;
}
