// proto: static USER_FUNC(lecture_button_get_icon_id);
static USER_FUNC(lecture_button_get_icon_id) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    LectButton* btn = &lbtn[index];

    evtSetValue(event, args[1], btn->seq);
    return EVT_RETURN_DONE;
}
