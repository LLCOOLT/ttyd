// include: manager/evtmgr_cmd.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// include: stdio.h
// proto: USER_FUNC(kpa_get_msg);
USER_FUNC(kpa_get_msg) {
    static char label[16];
    s32* args = event->args;
    s32 n = kwp->lives;
    s32 stage = kwp->stage;

    if (n > 30) {
        n = 30;
    }
    sprintf(label, "kpa_start_%03d", n + (stage - 1) * 30 - 1);
    evtSetValue(event, args[0], (s32)label);
    return EVT_RETURN_DONE;
}
