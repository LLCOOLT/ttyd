// proto: void yuurei_callback(s32 type, void* param);
void yuurei_callback(s32 type, void* param) {
    EventEntry* ev = *(EventEntry**)(*(u8**)param + 0x7A00);

    if (ev->lwData[13] != 0 && type == 3) {
        ev->lwData[14]++;
        if (ev->lwData[14] == 1) {
            ev->lwData[15] = (s32)evtEntry(evt_shake, 0, 0);
        } else if (ev->lwData[14] == 2 && (EventEntry*)ev->lwData[15] != NULL) {
            evtDelete((EventEntry*)ev->lwData[15]);
            evtEntry(evt_shake2, 0, 0);
        }
    }
}
