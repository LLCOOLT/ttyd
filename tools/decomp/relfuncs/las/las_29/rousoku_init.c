// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: void _hikariEntry(const char* name, s32 type, f32 scale);
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// proto: static USER_FUNC(rousoku_init);
static USER_FUNC(rousoku_init) {
    char name[8];
    s32 val = evtGetValue(event, event->args[0]);
    s32 type;
    s32 i;

    type = 3;
    if (val) {
        type = 8;
    }
    for (i = 1; i <= 66; i++) {
        sprintf(name, "hi%d", i);
        mapGrpFlagOn(name, 1);
        _hikariEntry(name, type, 0.5f);
    }
    return EVT_RETURN_DONE;
}
