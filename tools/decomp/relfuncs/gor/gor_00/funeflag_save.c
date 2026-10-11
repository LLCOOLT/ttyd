// include: driver/mapdrv.h
// proto: USER_FUNC(funeflag_save);
USER_FUNC(funeflag_save) {
    MapObject* b = mapGetMapObj("S_fune_b");
    MapObject* c = mapGetMapObj("S_fune_c");
    event->lwData[8] = b->flags & 1;
    event->lwData[9] = c->flags & 1;
    return EVT_RETURN_DONE;
}
