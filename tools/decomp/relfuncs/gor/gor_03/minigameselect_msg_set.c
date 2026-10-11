// include: driver/msgdrv.h
// decl: char* exchange_msgp;
// proto: USER_FUNC(minigameselect_msg_set);
USER_FUNC(minigameselect_msg_set) {
    s32* args = event->args;
    const s8* msg = (const s8*)msgSearch((const char*)evtGetValue(event, args[0]));
    s32 flags[4];
    s32 k;
    s32 i;
    s32 val;
    s32 j;
    s32 count;

    flags[0] = evtGetValue(event, GSWF(1232));
    flags[1] = evtGetValue(event, GSWF(1235));
    flags[2] = evtGetValue(event, GSWF(1234));
    flags[3] = evtGetValue(event, GSWF(1233));
    j = 0;
    i = 0;
    while (msg[i] != '\n') {
        exchange_msgp[j++] = msg[i++];
    }
    exchange_msgp[j++] = msg[i++];
    count = 0;
    for (k = 0; k < 4; k++) {
        if (flags[k]) {
            while (msg[i] != '\n') {
                exchange_msgp[j++] = msg[i++];
            }
            count++;
            exchange_msgp[j++] = msg[i++];
        } else {
            while (msg[i] != '\n') {
                i++;
            }
            i++;
        }
    }
    while (msg[i] != '\0') {
        exchange_msgp[j++] = msg[i++];
    }
    exchange_msgp[j] = msg[i];
    k = 0;
    while (((s8*)exchange_msgp)[k] != '>') {
        k++;
    }
    while (((s8*)exchange_msgp)[k] != ' ') {
        k--;
    }
    val = 80 - (4 - count) * 12;
    k++;
    exchange_msgp[k] = val / 10 + '0';
    k++;
    exchange_msgp[k] = val % 10 + '0';
    evtSetValue(event, args[1], (s32)exchange_msgp);
    return EVT_RETURN_DONE;
}
