// include: driver/itemdrv.h
// include: string.h
// proto: USER_FUNC(evt_itemNameToItemID);
USER_FUNC(evt_itemNameToItemID) {
    static char tmp[64];
    s32* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    ItemEntry* item = itemNameToPtr(name);

    strncpy(tmp, name, sizeof(tmp));
    evtSetValue(event, args[1], item->itemId);
    evtSetValue(event, args[2], (s32)name);
    return EVT_RETURN_DONE;
}
