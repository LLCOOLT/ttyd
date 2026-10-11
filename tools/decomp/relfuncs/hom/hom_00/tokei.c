// include: dolphin/os.h
// proto: USER_FUNC(tokei);
USER_FUNC(tokei) {
    OSCalendarTime time;
    s32 sec;

    OSTicksToCalendarTime(OSGetTime(), &time);
    sec = time.hour * 3600 + time.min * 60 + time.sec;
    event->lwData[0] = (s32)(1024.0f * -(360.0f * (sec / 3600.0f) / 12.0f)) - 230000000;
    event->lwData[1] = (s32)(1024.0f * -(360.0f * (sec / 60.0f) / 60.0f)) - 230000000;
    return EVT_RETURN_DONE;
}
