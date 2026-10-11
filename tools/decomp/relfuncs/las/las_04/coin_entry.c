// include: manager/evtmgr_cmd.h
// include: driver/itemdrv.h
// decl: ItemEntry* itemEntry(const char* name, s32 itemId, s32 mode, s32 flag, void* script, f32 x, f32 y, f32 z);
// decl: void itemStatusOn(ItemEntry* item, s32 flags);
// proto: USER_FUNC(coin_entry);
USER_FUNC(coin_entry) {
    s32* args = event->args;
    s32 x = evtGetValue(event, args[0]);
    s32 y = evtGetValue(event, args[1]);
    s32 z = evtGetValue(event, args[2]);
    s32 w = evtGetValue(event, args[3]);
    ItemEntry* item = itemEntry(NULL, 121, 3, -1, NULL, x, y, z);

    itemStatusOn(item, 0x10);
    *(f32*)((u8*)item + 0x80) = 0.8f;
    *(f32*)((u8*)item + 0x84) = 1.0f;
    *(s32*)((u8*)item + 0x88) = 5;
    *(f32*)((u8*)item + 0x58) = 550.0f;
    *(f32*)((u8*)item + 0x50) = 70.0f;
    *(s32*)((u8*)item + 0x54) = w;
    return EVT_RETURN_DONE;
}
