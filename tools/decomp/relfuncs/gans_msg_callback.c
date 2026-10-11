// proto: void gans_msg_callback(s32 type, void** work);
void gans_msg_callback(s32 type, void** work) {
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0x7A00);
    if (type == 2) {
        evtSetValue(evt, GW(10), evtGetValue(evt, GW(10)) + 1);
    }
}
