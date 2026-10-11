// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: void _hikariEntry(const char* name, s32 type, f32 scale);
// proto: USER_FUNC(hikari_change);
USER_FUNC(hikari_change) {
    char name[8];
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    s32 type = evtGetValue(event, args[1]) ? 3 : 8;

    sprintf(name, "hi%d", n);
    effDelete(effNameToPtr(name));
    _hikariEntry(name, type, 0.0f);
    return EVT_RETURN_DONE;
}
