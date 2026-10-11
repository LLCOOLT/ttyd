// include: memory.h
// include: string.h
// decl: char* exchange_msgp;
// proto: USER_FUNC(evt_exchange_msg_alloc);
USER_FUNC(evt_exchange_msg_alloc) {
    exchange_msgp = _mapAlloc(0x100);
    memset(exchange_msgp, 0, 0x100);
    return EVT_RETURN_DONE;
}
