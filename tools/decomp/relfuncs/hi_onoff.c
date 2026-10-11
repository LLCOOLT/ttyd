// include: driver/mapdrv.h
// include: driver/hitdrv.h
// include: driver/effdrv.h
// proto: USER_FUNC(hi_onoff);
EffectEntry* effTorchEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

USER_FUNC(hi_onoff) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObject* obj = mapGetMapObj((const char*)taimatu_data[index * 2]);
    Vec pos;

    if (on) {
        obj->flags &= ~1;
        hitObjGetPos((const char*)taimatu_data[index * 2 + 1], &pos);
        effSetName(effTorchEntry(0, pos.x, pos.y, pos.z, 0.7f), (const char*)taimatu_data[index * 2 + 1]);
    } else {
        obj->flags |= 1;
        effSoftDelete(effNameToPtr((const char*)taimatu_data[index * 2 + 1]));
    }
    return EVT_RETURN_DONE;
}
