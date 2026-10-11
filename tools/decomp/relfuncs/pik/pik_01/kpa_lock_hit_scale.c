// include: driver/mobjdrv.h
// proto: USER_FUNC(kpa_lock_hit_scale);
USER_FUNC(kpa_lock_hit_scale) {
    MapObjectEntry* mobj = mobjNameToPtr("lock");

    mobj->scale2.x *= 2.0f;
    mobj->scale2.y *= 2.0f;
    mobjCalcMtx2(mobj);
    mobj->flags &= ~4;
    return EVT_RETURN_DONE;
}
