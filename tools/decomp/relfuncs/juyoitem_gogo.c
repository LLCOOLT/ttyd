// include: driver/itemdrv.h
// include: driver/icondrv.h
// include: mario/mariost.h
// decl: void itemSetPosition(ItemEntry* item, f32 x, f32 y, f32 z);
// decl: void marioChgStayMotion(void);
// proto: static USER_FUNC(juyoitem_gogo);
static USER_FUNC(juyoitem_gogo) {
    ItemEntry* item = (ItemEntry*)event->lwData[8];

    iconFlagOff(item->name, 0x200);
    itemSetPosition(item, 0.0f, -1000.0f, 0.0f);
    marioChgStayMotion();
    marioStSystemLevel(0);
    return EVT_RETURN_DONE;
}
