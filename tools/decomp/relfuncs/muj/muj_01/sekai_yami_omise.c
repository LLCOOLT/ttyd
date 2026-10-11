// include: driver/icondrv.h
// include: stdio.h
// proto: USER_FUNC(sekai_yami_omise);
USER_FUNC(sekai_yami_omise) {
    char name[44];
    s32 i;

    for (i = 0; i < 6; i++) {
        sprintf(name, "shp%d", i);
        iconNameToPtr(name)->color = (GXColor){0x40, 0x40, 0x40, 0xFF};
    }
    return EVT_RETURN_DONE;
}
