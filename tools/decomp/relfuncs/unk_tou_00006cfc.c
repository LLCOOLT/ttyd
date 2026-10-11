// include: driver/itemdrv.h
// include: driver/icondrv.h
// proto: USER_FUNC(unk_tou_00006cfc);
USER_FUNC(unk_tou_00006cfc) {
    iconFlagOn(itemNameToPtr("belt")->name, 2);
    return EVT_RETURN_DONE;
}
