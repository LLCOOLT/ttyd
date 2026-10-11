// include: memory.h
// decl: char* exchange_msgp;
// proto: USER_FUNC(evt_exchange_msg_free);
USER_FUNC(evt_exchange_msg_free) {
    if (exchange_msgp == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(exchange_msgp);
    exchange_msgp = NULL;
    return EVT_RETURN_DONE;
}
