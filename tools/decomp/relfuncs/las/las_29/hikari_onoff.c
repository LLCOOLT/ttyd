// include: manager/evtmgr_cmd.h
// decl: typedef struct HikariData { s32 key; s32 id; } HikariData;
// decl: extern s32 hikari_on_evt[];
// decl: extern s32 hikari_off_evt[];
// proto: USER_FUNC(hikari_onoff);
USER_FUNC(hikari_onoff) {
    s32* args = event->args;
    HikariData* tbl = (HikariData*)args[0];
    s32 val = evtGetValue(event, args[1]);
    s32 off = evtGetValue(event, args[2]);
    s32 start = evtGetValue(event, args[3]);
    s32 limit = evtGetValue(event, args[4]);
    s32 key = tbl[start].key;
    s32* evt = off ? hikari_off_evt : hikari_on_evt;
    EventEntry* e;
    s32 i;

    if (key == -999) {
        evtSetValue(event, args[5], -1);
        return EVT_RETURN_DONE;
    }
    i = start;
    while (key > limit && key != -999) {
        e = evtEntry(evt, 0, 0);
        e->lwData[0] = tbl[i].id;
        e->lwData[1] = val;
        i++;
        key = tbl[i].key;
    }
    evtSetValue(event, args[5], i);
    return EVT_RETURN_DONE;
}
