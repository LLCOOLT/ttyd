// decl: USER_FUNC(evt_img_alloc_capture);
// proto: static void _img_alloc_capture(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
static void _img_alloc_capture(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7) {
    EventEntry event;
    s32 args[10];

    event.args = args;
    args[0] = a0;
    args[1] = a1;
    args[2] = a2;
    args[3] = a3;
    args[4] = a4;
    args[5] = a5;
    args[6] = a6;
    args[7] = a7;
    evt_img_alloc_capture(&event, TRUE);
}
