// include: manager/evtmgr_cmd.h
// include: dolphin/os.h
// include: memory.h
// include: string.h
// include: mario/mariost.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// decl: void unk_8022439c(s32* evt);
// proto: USER_FUNC(evt_yuucounter_alloc);
USER_FUNC(evt_yuucounter_alloc) {
    s32* args = event->args;
    YuuCounterWork* wp = _mapAlloc(sizeof(YuuCounterWork));
    s32 value;

    memset(wp, 0, sizeof(YuuCounterWork));
    _wp = wp;
    wp->x = evtGetFloat(event, args[0]);
    wp->y = evtGetFloat(event, args[1]);
    wp->type = evtGetValue(event, args[2]);
    value = evtGetValue(event, args[3]);
    switch (wp->type) {
        case 1:
            wp->limit = value * 1000;
            wp->lastTime = gp->renderTime;
            wp->elapsed = 0;
            wp->data = wp->limit;
            break;
        case 2:
            wp->field_0x34 = value;
            break;
    }
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    if (wp->type == 1) {
        unk_8022439c(unk_evt_yuu_00019728);
    } else {
        unk_8022439c(unk_evt_yuu_00019740);
    }
    return EVT_RETURN_DONE;
}
