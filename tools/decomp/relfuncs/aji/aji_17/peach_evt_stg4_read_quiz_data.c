// include: manager/evtmgr_cmd.h
// note: rels file declares the data as s32 peach_evt_stg4_quiz_data[5][4] (hand edit after gen)
// proto: USER_FUNC(peach_evt_stg4_read_quiz_data);
USER_FUNC(peach_evt_stg4_read_quiz_data) {
    s32* args = event->args;
    s32 no = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], peach_evt_stg4_quiz_data[no][0]);
    evtSetValue(event, args[2], peach_evt_stg4_quiz_data[no][1]);
    evtSetValue(event, args[3], peach_evt_stg4_quiz_data[no][2]);
    evtSetValue(event, args[4], peach_evt_stg4_quiz_data[no][3]);
    return EVT_RETURN_DONE;
}
