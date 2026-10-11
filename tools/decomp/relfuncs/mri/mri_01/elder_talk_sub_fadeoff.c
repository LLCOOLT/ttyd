// decl: void puniFadeOff(s32 index);
// proto: USER_FUNC(elder_talk_sub_fadeoff);
USER_FUNC(elder_talk_sub_fadeoff) {
    puniFadeOff(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
