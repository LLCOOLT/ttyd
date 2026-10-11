// proto: USER_FUNC(shop_item_disp_off);
USER_FUNC(shop_item_disp_off) {
    s32 i;

    for (i = 0; i < 6; i++) {
        mapObjFlagOn((const char*)obj_list[i * 2], 1);
    }
    return EVT_RETURN_DONE;
}
