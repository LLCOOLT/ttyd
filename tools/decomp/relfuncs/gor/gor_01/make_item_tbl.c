// include: manager/evtmgr_cmd.h
// include: mario/mario_pouch.h
// decl: extern s32 item_tbl[];
// proto: USER_FUNC(make_item_tbl);
USER_FUNC(make_item_tbl) {
    s32* args = event->args;
    s32 skip = evtGetValue(event, args[0]);
    s32 cnt = pouchGetHaveItemCnt();
    s32 n = 0;
    s32 i;
    s32 item;

    for (i = 0; i < cnt; i++) {
        if (skip != i) {
            item = pouchHaveItem(i);
            if (item != 0) {
                item_tbl[n] = item;
                n++;
            }
        }
    }
    item_tbl[n] = -1;
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}
