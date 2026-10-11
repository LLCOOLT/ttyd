// include: mario/mario.h
// proto: void msg_callback(s32 type, void* param);
void msg_callback(s32 type, void* param) {
    EventEntry* ev = *(EventEntry**)(*(u8**)param + 0x7A00);

    switch (type) {
        case 0:
            evtSetValue(ev, GW(0), 0);
            evtSetValue(ev, GW(1), 0);
            ev->lwData[15] = 0;
            break;
        case 5:
            if (ev->lwData[15] == 3) {
                marioKeyOff();
            }
            ev->lwData[15]++;
            break;
        case 1:
            evtSetValue(ev, GW(1), 1);
            break;
        case 3:
            evtSetValue(ev, GW(0), 1);
            break;
    }
}
