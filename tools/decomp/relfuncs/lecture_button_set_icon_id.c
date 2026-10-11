// proto: static USER_FUNC(lecture_button_set_icon_id);
static USER_FUNC(lecture_button_set_icon_id) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    btn->iconId = value;
    return EVT_RETURN_DONE;
}
