// include: driver/itemdrv.h
// decl: u16 itemFlag(ItemEntry* item, u16 mask);
// proto: USER_FUNC(item_check_necklace_exist);
USER_FUNC(item_check_necklace_exist) {
    ItemEntry* item = itemNameToPtr("necklace");

    if (item != NULL && itemFlag(item, 1)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
