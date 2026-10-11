// proto: USER_FUNC(evt_rsh_get_rnd_npc);
USER_FUNC(evt_rsh_get_rnd_npc) {
    s32* args = event->args;
    s32 room = evtGetValue(event, args[0]);
    s32 group = evtGetValue(event, args[1]);
    s32 value;
    s32 index;

    switch (room) {
    case 0:
        value = evtGetValue(NULL, GSW(821));
        switch (group) {
        case 0:
            index = value & 7;
            break;
        case 1:
            index = (value >> 3) & 3;
            break;
        case 2:
            index = (value >> 5) & 1;
            break;
        default:
            index = 0;
            break;
        }
        break;
    case 1:
        value = evtGetValue(NULL, GSW(822));
        switch (group) {
        case 0:
            index = value & 0xF;
            break;
        case 1:
            index = (value >> 4) & 7;
            break;
        default:
            index = 0;
            break;
        }
        break;
    case 2:
        value = evtGetValue(NULL, GSW(823));
        switch (group) {
        case 0:
            index = value & 1;
            break;
        case 1:
            index = (value >> 1) & 1;
            break;
        case 2:
            index = (value >> 2) & 1;
            break;
        case 3:
            index = (value >> 3) & 3;
            break;
        default:
            index = 0;
            break;
        }
        break;
    }
    evtSetValue(event, args[2], index);
    return EVT_RETURN_DONE;
}
