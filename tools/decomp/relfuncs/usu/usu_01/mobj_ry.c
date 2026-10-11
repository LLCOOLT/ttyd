// include: driver/mobjdrv.h
// proto: USER_FUNC(mobj_ry);
USER_FUNC(mobj_ry) {
    MapObjectEntry* mobj = mobjNameToPtr("mobj_box00");

    mobj->rotation.y = 135.0f;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}
