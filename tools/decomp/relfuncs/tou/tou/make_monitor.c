// include: manager/evtmgr_cmd.h
// include: memory.h
// include: driver/npcdrv.h
// include: driver/dispdrv.h
// include: dolphin/gx.h
// decl: typedef struct GansWork { smartEntry* buf; GXTexObj tex; s32 onoff; s32 alpha; s32 ready; } GansWork;
// decl: GansWork* gans_wp;
// decl: void gans_tex(CameraId cameraId, void* param);
// proto: USER_FUNC(make_monitor);
USER_FUNC(make_monitor) {
    NpcEntry* npc = npcNameToPtr_NoAssert(evtGetValue(NULL, GSW(0)) < 0xAC ? "\203K\203\223\203X" : "\203L\203m\203V\203R\203\217");
    GansWork* wp;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(GansWork));
        event->userdatap[0] = wp;
        wp->onoff = 0;
        wp->ready = 0;
    }
    if (npc == NULL) {
        return EVT_RETURN_BLOCK;
    }
    wp = event->userdatap[0];
    gans_wp = wp;
    wp->buf = smartAlloc(GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXInitTexObj(&wp->tex, wp->buf->address, 0x80, 0x80, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    if (gans_wp->onoff) {
        gans_wp->alpha += 4;
        if (gans_wp->alpha > 0x80) {
            gans_wp->alpha = 0x80;
        }
    } else {
        gans_wp->alpha -= 4;
        if (gans_wp->alpha < 0) {
            gans_wp->alpha = 0;
        }
    }
    dispEntry(CAMERA_SHADOW, 0.0f, 3, gans_tex, wp);
    return EVT_RETURN_BLOCK;
}
