// include: manager/evtmgr_cmd.h
// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// decl: typedef struct ShopSel { u8 field_0x0[8]; s32* items; u8 field_0xC[0x24 - 0xC]; s32 sel; } ShopSel;
// proto: static USER_FUNC(get_value);
static USER_FUNC(get_value) {
    s32* args = event->args;
    ShopSel* wp = (ShopSel*)evtGetValue(event, args[0]);

    evtSetValue(event, args[1], (s32)itemDataTable[wp->items[wp->sel]].id);
    evtSetValue(event, args[2], wp->items[wp->sel]);
    evtSetValue(event, args[3], itemDataTable[wp->items[wp->sel]].discount_price);
    evtSetValue(event, args[4], itemDataTable[wp->items[wp->sel]].bp_cost);
    return EVT_RETURN_DONE;
}
