// decl: s32 key_list[4];
// include: mario/mario_pouch.h
// proto: USER_FUNC(make_list);
USER_FUNC(make_list) {
    s32 n = 0;

    if ((s32)pouchCheckItem(0x1D) > 0) {
        key_list[n++] = 0x1D;
    }
    if ((s32)pouchCheckItem(0x1E) > 0) {
        key_list[n++] = 0x1E;
    }
    if ((s32)pouchCheckItem(0x1F) > 0) {
        key_list[n++] = 0x1F;
    }
    key_list[n] = -1;
    return EVT_RETURN_DONE;
}
