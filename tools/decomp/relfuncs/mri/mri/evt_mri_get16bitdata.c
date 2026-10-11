// proto: USER_FUNC(evt_mri_get16bitdata);
USER_FUNC(evt_mri_get16bitdata) {
    s32* args = event->args;
    s16* table = (s16*)evtGetValue(event, args[0]);
    s32 index = evtGetValue(event, args[1]);
    evtSetValue(event, args[2], table[index]);
    return EVT_RETURN_DONE;
}
