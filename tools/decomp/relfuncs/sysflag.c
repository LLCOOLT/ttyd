// include: mario/mariost.h
// include: driver/fadedrv.h
// proto: USER_FUNC(sysflag);
USER_FUNC(sysflag) {
    if (gp->flags & 1) {
        gp->flags &= ~1;
        fadeEntry(0x1C, 0, (GXColor){0, 0, 0, 0});
    }
    return EVT_RETURN_DONE;
}
