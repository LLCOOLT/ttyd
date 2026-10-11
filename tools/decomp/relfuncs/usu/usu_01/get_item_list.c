// include: mario/mario_pouch.h
// include: memory.h
// proto: USER_FUNC(get_item_list);
USER_FUNC(get_item_list) {
    s32* args = event->args;
    s32* list = _mapAlloc((pouchGetHaveItemCnt() + 1) * sizeof(s32));
    s32 n;
    s32 i;

    for (i = 0, n = 0; i < 20; i++) {
        if (pouchHaveItem(i)) {
            list[n] = pouchHaveItem(i);
            n++;
        }
    }
    list[n] = -1;
    evtSetValue(event, args[0], (s32)list);
    return EVT_RETURN_DONE;
}
