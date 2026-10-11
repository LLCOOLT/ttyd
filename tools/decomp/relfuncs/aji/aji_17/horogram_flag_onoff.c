// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: typedef struct HorogramWork { void* buf0; void* buf1; GXTexObj tex0; GXTexObj tex1; u16 ready; u16 flags; } HorogramWork;
// decl: HorogramWork* horogram_wp;
// proto: USER_FUNC(horogram_flag_onoff);
USER_FUNC(horogram_flag_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);

    if (on) {
        horogram_wp->flags |= mask;
    } else {
        horogram_wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
