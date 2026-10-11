// include: driver/mobjdrv.h
// proto: USER_FUNC(box_r);
USER_FUNC(box_r) {
    MapObjectEntry* mobj = mobjNameToPtr("pera_box");

    mobj->rotation.y = 135.0f;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
