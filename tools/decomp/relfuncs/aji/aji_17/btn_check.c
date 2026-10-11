// include: manager/evtmgr_cmd.h
// include: system.h
// proto: USER_FUNC(btn_check);
USER_FUNC(btn_check) {
    s32* args = event->args;
    s32 dir = evtGetValue(event, args[0]);
    u32 btn = keyGetButtonTrg(0);
    s32 a = btn & 0x100;
    s32 b = btn & 0x200;
    s32 x = btn & 0x400;
    s32 ret = 0;

    switch (dir) {
    case 1:
        if (a && !(b | x)) {
            ret = 1;
        } else if (!a && (b | x)) {
            ret = 2;
        }
        break;
    case 2:
        if (b && !(a | x)) {
            ret = 1;
        } else if (!b && (a | x)) {
            ret = 2;
        }
        break;
    case 0:
        if (x && !(a | b)) {
            ret = 1;
        } else if (!x && (a | b)) {
            ret = 2;
        }
        break;
    default:
        if (a | b | x) {
            ret = 2;
        }
        break;
    }
    evtSetValue(event, args[1], ret);
    return EVT_RETURN_DONE;
}
