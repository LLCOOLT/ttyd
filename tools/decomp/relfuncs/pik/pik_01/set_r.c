// include: driver/mobjdrv.h
// proto: USER_FUNC(set_r);
USER_FUNC(set_r) {
    MapObjectEntry* mobj = mobjNameToPtr("lock");

    mobj->rotation.y = -45.0f;
    return EVT_RETURN_DONE;
}
