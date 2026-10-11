// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: void _hikariEntry(const char* name, s32 type, f32 scale);
// decl: typedef struct HikariData { s32 key; s32 id; } HikariData;
// decl: #define HIKARI_DATA ((HikariData*)hikari_data)
// proto: USER_FUNC(all_hikari_change_kuro);
USER_FUNC(all_hikari_change_kuro) {
    char name[8];
    s32 idx = evtGetValue(event, event->args[0]);
    s32 i;
    s32 key;

    if (idx != -1) {
        key = HIKARI_DATA[idx].key;
        while (key != -999) {
            sprintf(name, "hi%d", HIKARI_DATA[idx].id);
            effDelete(effNameToPtr(name));
            _hikariEntry(name, 8, 0.5f);
            idx++;
            key = HIKARI_DATA[idx].key;
        }
    }
    for (i = 39; i <= 66; i++) {
        if (i == 64 || i == 66) {
            continue;
        }
        sprintf(name, "hi%d", i);
        effDelete(effNameToPtr(name));
        _hikariEntry(name, 8, 0.5f);
    }
    return EVT_RETURN_DONE;
}
