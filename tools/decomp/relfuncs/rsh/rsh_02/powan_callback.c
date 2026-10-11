// proto: void powan_callback(s32 type, void* param);
void powan_callback(s32 type, void* param) {
    u8* work = *(u8**)param;

    if (type == 3) {
        EventEntry* ev = *(EventEntry**)(work + 0x7A00);
        s32 count = evtGetValue(ev, LW(10));

        switch (count) {
            case 1:
                evtEntry(evt_powan_msg, 0, 0);
                break;
        }
        evtSetValue(ev, LW(10), count + 1);
    }
}
