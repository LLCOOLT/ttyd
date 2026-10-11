// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: typedef struct RyushiWork { s32 flag; s32 mode; Vec base; Vec pos; s32 alpha; s32 count; f32 scale; s32 r; s32 g; s32 b; s32 r2; s32 g2; s32 b2; } RyushiWork;
// decl: RyushiWork* xwp;
// decl: s32 ryuwp;
// decl: static f32 randf(f32 min, f32 max);
// proto: USER_FUNC(evt_ryushi_clr);
USER_FUNC(evt_ryushi_clr) {
    s32* args = event->args;
    RyushiWork* p;
    s32 n;
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    s32 z;

    p = xwp;
    n = ryuwp;
    p->mode = evtGetValue(event, args[0]);
    p->count = 0;
    p->alpha = 0;
    p->pos.x = 0.0f;
    p->pos.y = 0.0f;
    p->pos.z = 0.0f;
    xwp->base.x = 50.0f;
    xwp->base.y = 50.0f;
    xwp->base.z = 100.0f;
    for (i = 1, p++; i < n; i++, p++) {
        j = i - 1;
        p->flag = 0;
        x = j % 10;
        y = (j / 10) % 6;
        z = j / 60;
        p->base.x = x * xwp->base.x - 4.5f * xwp->base.x + xwp->base.x * 0.5f * ((y + z) & 1);
        p->base.y = y * xwp->base.y - 2.5f * xwp->base.y;
        p->base.z = z * xwp->base.z - 1.5f * xwp->base.z;
        p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
        p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
        p->pos.z = p->base.z + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
        p->scale = 0.5f;
    }
    return EVT_RETURN_DONE;
}
