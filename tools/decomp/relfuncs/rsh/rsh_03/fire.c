// include: driver/effdrv.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: void mapObjFlagOn(const char* name, u32 flags);
// proto: USER_FUNC(fire);
USER_FUNC(fire) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    Vec pos;

    mapObjGetPos(name, &pos);
    mapObjFlagOn(name, 0x4000);
    effFireEntry(3, pos.x, pos.y - 4.0f, pos.z, 0.5f, 0);
    return EVT_RETURN_DONE;
}
