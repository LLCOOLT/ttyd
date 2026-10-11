// include: driver/itemdrv.h
// include: driver/icondrv.h
// proto: USER_FUNC(icon_off);
USER_FUNC(icon_off) {
    iconFlagOn(itemNameToPtr("belt")->name, 2);
    return EVT_RETURN_DONE;
}
