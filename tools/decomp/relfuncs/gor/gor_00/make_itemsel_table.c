// include: memory.h
// include: mario/mario_pouch.h
// decl: static s32* itemsel_table_ram;
// proto: static USER_FUNC(make_itemsel_table);
static USER_FUNC(make_itemsel_table) {
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

        if (item >= 0xB3 && item < 0xEC) {
            *p++ = item;
            count++;
        }
        if (item >= 0x94 && item < 0xA1) {
            *p++ = item;
            count++;
        }
        switch (item) {
            case 0xA6:
            case 0xA7:
            case 0xA8:
            case 0xA9:
            case 0xAA:
            case 0xAB:
            case 0xAD:
            case 0xAE:
            case 0xAF:
            case 0xB0:
                *p++ = item;
                count++;
                break;
        }
    }
    *p = -1;
    evtSetValue(event, args[0], count);
    event->lwData[10] = (s32)itemsel_table_ram;
    return EVT_RETURN_DONE;
}
