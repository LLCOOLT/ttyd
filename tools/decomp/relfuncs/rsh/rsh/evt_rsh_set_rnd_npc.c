// proto: USER_FUNC(evt_rsh_set_rnd_npc);
USER_FUNC(evt_rsh_set_rnd_npc) {
    s32* args = event->args;
    s32 room = evtGetValue(event, args[0]);
    s32 group = evtGetValue(event, args[1]);
    s32 index = evtGetValue(event, args[2]);
    s32 value;

    switch (room) {
    case 0:
        value = evtGetValue(NULL, GSW(821));
        switch (group) {
        case 0:
            value |= index & 7;
            break;
        case 1:
            value |= (index & 3) << 3;
            break;
        case 2:
            value |= (index & 1) << 5;
            break;
        }
        evtSetValue(NULL, GSW(821), value);
        break;
    case 1:
        value = evtGetValue(NULL, GSW(822));
        switch (group) {
        case 0:
            value |= index & 0xF;
            break;
        case 1:
            value |= (index & 7) << 4;
            break;
        }
        evtSetValue(NULL, GSW(822), value);
        break;
    case 2:
        value = evtGetValue(NULL, GSW(823));
        switch (group) {
        case 0:
            value |= index & 1;
            break;
        case 1:
            value |= (index & 1) << 1;
            break;
        case 2:
            value |= (index & 1) << 2;
            break;
        case 3:
            value |= (index & 3) << 3;
            break;
        }
        evtSetValue(NULL, GSW(823), value);
        break;
    }
    return EVT_RETURN_DONE;
}
