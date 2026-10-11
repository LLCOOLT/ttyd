// include: manager/evtmgr_cmd.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// decl: void kpaAddScore(s32 score);
// proto: USER_FUNC(kpa_time_countdown);
USER_FUNC(kpa_time_countdown) {
    KpaWork* wp = kwp;

    if (wp->time != 0) {
        wp->time--;
        kpaAddScore(100);
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
