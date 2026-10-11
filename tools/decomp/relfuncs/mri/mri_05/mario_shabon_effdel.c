// include: driver/effdrv.h
// proto: USER_FUNC(mario_shabon_effdel);
USER_FUNC(mario_shabon_effdel) {
    effDelete(marioeff);
    return EVT_RETURN_DONE;
}
