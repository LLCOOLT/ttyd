// proto: static USER_FUNC(cam_kaiten_get_para);
static USER_FUNC(cam_kaiten_get_para) {
    s32* args = event->args;
    KaitenParam* p;

    switch (evtGetValue(event, args[0])) {
        case 0:
            p = ckp0;
            break;
        case 1:
            p = ckp1;
            break;
        case 2:
        default:
            p = ckpw;
            break;
    }
    evtSetFloat(event, args[1], p->pos.x);
    evtSetFloat(event, args[2], p->pos.y);
    evtSetFloat(event, args[3], p->pos.z);
    evtSetFloat(event, args[4], p->target.x);
    evtSetFloat(event, args[5], p->target.y);
    evtSetFloat(event, args[6], p->target.z);
    evtSetFloat(event, args[7], p->angle);
    evtSetFloat(event, args[8], p->dist);
    return EVT_RETURN_DONE;
}
