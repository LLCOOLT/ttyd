// decl: void mapObjFlagOn(const char* name, u32 flags);
// decl: void mapObjFlagOff(const char* name, u32 flags);
// proto: USER_FUNC(shop_item_disp_on);
USER_FUNC(shop_item_disp_on) {
    s32 i;

    for (i = 0; i < 6; i++) {
        mapObjFlagOff((const char*)obj_list[i * 2], 1);
    }
    return EVT_RETURN_DONE;
}
