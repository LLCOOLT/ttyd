// include: memory.h
// include: string.h
// include: driver/msgdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(evt_yuutitle_alloc);
USER_FUNC(evt_yuutitle_alloc) {
    s32* args = event->args;
    YuuTitleWork* wp = _mapAlloc(sizeof(YuuTitleWork));

    memset(wp, 0, sizeof(YuuTitleWork));
    _wp = wp;
    wp->targetX = evtGetFloat(event, args[0]);
    wp->targetY = evtGetFloat(event, args[1]);
    wp->msg = msgSearch((const char*)evtGetValue(event, args[2]));
    wp->startX = wp->x = 200.0f + wp->targetX;
    wp->startY = wp->y = 200.0f + wp->targetY;
    wp->alpha = 0;
    wp->event = evtEntry(main_evt, 0, 0);
    wp->event->lwData[0] = (s32)wp;
    return EVT_RETURN_DONE;
}
