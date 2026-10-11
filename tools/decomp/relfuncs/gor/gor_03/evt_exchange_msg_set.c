// include: driver/msgdrv.h
// include: stdio.h
// decl: char* exchange_msgp;
// decl: typedef struct ExchangeRyokin { s32 ryokin; s32 medal; } ExchangeRyokin;
// decl: #define RYOKIN_TBL ((ExchangeRyokin(*)[3])exchange_ryokin_medal_tbl)
// decl: s32 exchange_ret_tbl_no(void);
// proto: USER_FUNC(evt_exchange_msg_set);
USER_FUNC(evt_exchange_msg_set) {
    s32* args = event->args;
    s32 value = evtGetValue(event, args[0]);
    const char* msg = msgSearch((const char*)evtGetValue(event, args[1]));
    ExchangeRyokin* tbl = RYOKIN_TBL[exchange_ret_tbl_no()];

    sprintf(exchange_msgp, msg, value, tbl[0].medal, tbl[0].ryokin, tbl[1].medal, tbl[1].ryokin, tbl[2].medal, tbl[2].ryokin);
    evtSetValue(event, args[2], (s32)exchange_msgp);
    return EVT_RETURN_DONE;
}
