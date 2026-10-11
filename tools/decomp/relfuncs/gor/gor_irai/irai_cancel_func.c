// include: manager/evtmgr_cmd.h
// include: mario/mario_pouch.h
// decl: void irai_flag_clear(void);
// decl: extern s32 irai_item_table[];
// proto: USER_FUNC(irai_cancel_func);
static inline s32 irai_get_no(EventEntry* event) {
    return evtGetValue(event, event->args[0]) - 1;
}

USER_FUNC(irai_cancel_func) {
    s32 no = irai_get_no(event);
    s32* items;
    ItemType item;

    irai_flag_clear();
    items = (s32*)irai_item_table[no];
    while (TRUE) {
        item = *items;
        if (item == -1) {
            break;
        }
        while (TRUE) {
            if ((s32)pouchCheckItem(item) <= 0) {
                break;
            }
            pouchRemoveItem(item);
        }
        items++;
    }
    return EVT_RETURN_DONE;
}
