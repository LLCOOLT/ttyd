// include: driver/npcdrv.h
// include: driver/mapdrv.h
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: USER_FUNC(getY);
USER_FUNC(getY) {
    NpcEntry* npc = npcNameToPtr("\203K\203\223\203X");
    MapObject* obj = mapGetMapObj("block_5");
    Vec pos;
    f32 y;

    mapObjGetPos("group151", &pos);
    y = 100.0f + obj->modelWorldMtx[1][3];
    if (y > pos.y) {
        npc->position.y = y;
    } else {
        npc->position.x = npc->position.z = 0.0f;
        npc->position.y = pos.y;
    }
    return EVT_RETURN_DONE;
}
