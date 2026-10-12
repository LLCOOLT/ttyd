// decl: typedef struct ExchangeRyokin { s32 ryokin; s32 medal; } ExchangeRyokin;
// decl: #define RYOKIN_TBL ((ExchangeRyokin(*)[3])exchange_ryokin_medal_tbl)
// decl: s32 exchange_ret_tbl_no(void);
// proto: USER_FUNC(exchange_ryokin_medal);
USER_FUNC(exchange_ryokin_medal) {
    s32* args = event->args;
    ExchangeRyokin (*new_var)[3];
    s32 idx = evtGetValue(event, args[0]);
    s32 no = exchange_ret_tbl_no();

    evtSetValue(event, args[1], RYOKIN_TBL[no][idx].ryokin);
    new_var = RYOKIN_TBL;
    evtSetValue(event, args[2], new_var[no][idx].medal);
    return EVT_RETURN_DONE;
}
