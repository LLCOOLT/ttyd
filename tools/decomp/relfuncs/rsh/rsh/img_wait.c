// include: driver/imgdrv.h
// include: mario/mariost.h
// proto: BOOL img_wait(void);
BOOL img_wait(void) {
    ImageEntry* img = imgNameToPtr("capture_img", gp->inBattle != 0);

    if (!(img->flags & 2) && img->field_0x118 < 1.0f) {
        return FALSE;
    }
    return TRUE;
}
