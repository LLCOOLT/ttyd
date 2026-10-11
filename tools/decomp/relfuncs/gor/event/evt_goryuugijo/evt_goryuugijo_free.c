// include: memory.h
// include: driver/camdrv.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// proto: USER_FUNC(evt_goryuugijo_free);
USER_FUNC(evt_goryuugijo_free) {
    s32* args = event->args;
    GoryuuWork* wp = (GoryuuWork*)evtGetValue(event, args[0]);

    if (wp == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        wp->flags |= 1;
    }
    if (!(wp->flags & 2)) {
        return EVT_RETURN_BLOCK;
    }
    if (wp->data != NULL) {
        _mapFree(wp->data);
    }
    _mapFree(wp);
    evtSetValue(event, args[0], 0);
    return EVT_RETURN_DONE;
}
