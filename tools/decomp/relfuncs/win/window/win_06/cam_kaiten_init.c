// include: memory.h
// include: string.h
// include: dolphin/mtx.h
// decl: double atan2(double y, double x);
// proto: static USER_FUNC(cam_kaiten_init);
static USER_FUNC(cam_kaiten_init) {
    s32* args = event->args;
    Vec target;
    Vec pos;
    f32 dist;

    ckp0 = _mapAlloc(sizeof(KaitenParam));
    memset(ckp0, 0, sizeof(KaitenParam));
    ckp1 = _mapAlloc(sizeof(KaitenParam));
    memset(ckp1, 0, sizeof(KaitenParam));
    ckpw = _mapAlloc(sizeof(KaitenParam));
    memset(ckp1, 0, sizeof(KaitenParam));
    ckp0->pos.x = evtGetFloat(event, args[0]);
    ckp0->pos.y = evtGetFloat(event, args[1]);
    ckp0->pos.z = evtGetFloat(event, args[2]);
    ckp0->target.x = evtGetFloat(event, args[3]);
    ckp0->target.y = evtGetFloat(event, args[4]);
    ckp0->target.z = evtGetFloat(event, args[5]);
    ckp1->pos.x = evtGetFloat(event, args[6]);
    ckp1->pos.y = evtGetFloat(event, args[7]);
    ckp1->pos.z = evtGetFloat(event, args[8]);
    ckp1->target.x = evtGetFloat(event, args[9]);
    ckp1->target.y = evtGetFloat(event, args[10]);
    ckp1->target.z = evtGetFloat(event, args[11]);

    pos = ckp0->pos;
    target = ckp0->target;
    target.y = 0.0f;
    pos.y = 0.0f;
    dist = PSVECDistance(&pos, &target);
    ckp0->angle = 57.29579f * (f32)atan2(-(target.x - pos.x), target.z - pos.z);
    ckp0->dist = dist;

    pos = ckp1->pos;
    target = ckp1->target;
    target.y = 0.0f;
    pos.y = 0.0f;
    dist = PSVECDistance(&pos, &target);
    ckp1->angle = 57.29579f * (f32)atan2(-(target.x - pos.x), target.z - pos.z);
    ckp1->dist = dist;

    ckpw->pos = ckp0->pos;
    ckpw->target = ckp0->target;
    ckpw->angle = ckp0->angle;
    ckpw->dist = ckp0->dist;
    return EVT_RETURN_DONE;
}
