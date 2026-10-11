// proto: static USER_FUNC(lecture_button_set_seq);
static USER_FUNC(lecture_button_set_seq) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    btn->seq = value;
    return EVT_RETURN_DONE;
}
