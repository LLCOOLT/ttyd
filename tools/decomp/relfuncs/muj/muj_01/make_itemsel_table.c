// include: memory.h
// include: mario/mario_pouch.h
// proto: USER_FUNC(make_itemsel_table);
USER_FUNC(make_itemsel_table) {
    s32* args = event->args;
    PouchData* pouch = pouchGetPtr();
    s32* p;
    s32 count;
    s32 i;

    itemsel_table_ram = _mapAlloc(0x54);
    p = itemsel_table_ram;
    count = 0;
    for (i = 0; i < 20; i++) {
        s32 item = pouch->heldItems[i];

        if (item > 0) {
            *p++ = item;
            count++;
        }
    }
    *p = -1;
    evtSetValue(event, args[0], count);
    event->lwData[10] = (s32)itemsel_table_ram;
    return EVT_RETURN_DONE;
}
