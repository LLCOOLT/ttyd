// include: driver/icondrv.h
// include: stdio.h
// proto: USER_FUNC(sekai_yami_omise);
USER_FUNC(sekai_yami_omise) {
    char name[40];
    s32 i;
    IconEntry* icon;

    for (i = 0; i < 6; i++) {
        sprintf(name, "shp%d", i);
        icon = iconNameToPtr(name);
        icon->color = (GXColor){0x40, 0x40, 0x40, 0xFF};
    }
    return EVT_RETURN_DONE;
}
