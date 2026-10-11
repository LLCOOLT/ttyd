// include: memory.h
// decl: static s32* itemsel_table_ram;
// proto: static USER_FUNC(delete_itemsel_table);
static USER_FUNC(delete_itemsel_table) {
    _mapFree(itemsel_table_ram);
    return EVT_RETURN_DONE;
}
