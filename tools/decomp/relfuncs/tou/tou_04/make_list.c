// include: driver/msgdrv.h
// include: memory.h
// include: stdio.h
// include: string.h
// proto: USER_FUNC(make_list);
USER_FUNC(make_list) {
    static char* tmp;
    static const char* list[] = {
        "stg3_tou_hushigi_list_1",
        "stg3_tou_hushigi_list_2",
        "stg3_tou_hushigi_list_3",
        "stg3_tou_hushigi_list_4",
        "stg3_tou_hushigi_list_5",
        "stg3_tou_hushigi_list_6",
        "stg3_tou_hushigi_list_7",
    };
    s32* args = event->args;
    s32 i;

    if (tmp == NULL) {
        tmp = _mapAlloc(0x1000);
    }
    sprintf(tmp, "<select %d %d %d %d>", 0, 7, 300, 140);
    for (i = 0; i < 7; i++) {
        strcat(tmp, "\n");
        strcat(tmp, msgSearch(list[i]));
    }
    evtSetValue(event, args[0], (s32)tmp);
    return EVT_RETURN_DONE;
}
