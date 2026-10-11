// include: memory.h
// proto: USER_FUNC(delete_item_list);
USER_FUNC(delete_item_list) {
    _mapFree((void*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
