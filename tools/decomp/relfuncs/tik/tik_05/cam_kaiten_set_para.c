// include: manager/evtmgr_cmd.h
// decl: typedef struct KaitenParam { Vec pos; Vec target; f32 angle; f32 dist; } KaitenParam;
// decl: static KaitenParam* ckp0;
// decl: static KaitenParam* ckp1;
// decl: static KaitenParam* ckpw;
// proto: static USER_FUNC(cam_kaiten_set_para);
static USER_FUNC(cam_kaiten_set_para) {
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
    p->pos.x = evtGetFloat(event, args[1]);
    p->pos.y = evtGetFloat(event, args[2]);
    p->pos.z = evtGetFloat(event, args[3]);
    p->target.x = evtGetFloat(event, args[4]);
    p->target.y = evtGetFloat(event, args[5]);
    p->target.z = evtGetFloat(event, args[6]);
    p->angle = evtGetFloat(event, args[7]);
    p->dist = evtGetFloat(event, args[8]);
    return EVT_RETURN_DONE;
}
