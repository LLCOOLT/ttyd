// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// proto: USER_FUNC(check_tabemono);
USER_FUNC(check_tabemono) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    BOOL food = FALSE;

    if (*(u16*)&itemDataTable[id].usable_locations & 4) {
        food = TRUE;
    }
    evtSetValue(event, args[1], food);
    return EVT_RETURN_DONE;
}
