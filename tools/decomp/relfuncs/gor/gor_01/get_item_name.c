// include: manager/evtmgr_cmd.h
// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// proto: USER_FUNC(get_item_name);
USER_FUNC(get_item_name) {
    s32* args = event->args;
    s32 item = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], (s32)itemDataTable[item].id);
    return EVT_RETURN_DONE;
}
