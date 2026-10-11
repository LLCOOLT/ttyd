// include: mario/mario_pouch.h
// proto: USER_FUNC(iri_22_make_item_tbl);
USER_FUNC(iri_22_make_item_tbl) {
    s32* args = event->args;
    u8 bought;
    s32 n;
    s32 i;

    bought = evtGetValue(NULL, GSW(1469));
    for (i = 0; i < 4; i++) {
        iri_22_item_tbl[i] = -1;
    }
    n = 0;
    if (!(bought & 1) && (s32)pouchCheckItem(0xA9) != 0) {
        iri_22_item_tbl[0] = 0xA9;
        n = 1;
    }
    if (!(bought & 2) && (s32)pouchCheckItem(0xA8) != 0) {
        iri_22_item_tbl[n++] = 0xA8;
    }
    if (!(bought & 4) && (s32)pouchCheckItem(0xAA) != 0) {
        iri_22_item_tbl[n++] = 0xAA;
    }
    evtSetValue(event, args[0], (s32)iri_22_item_tbl);
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}
