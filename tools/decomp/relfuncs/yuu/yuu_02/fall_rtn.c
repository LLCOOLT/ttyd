// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// include: string.h
// include: mario/mario.h
// include: driver/dispdrv.h
// include: driver/hitdrv.h
// include: pmario_sound.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// decl: extern MonteTable montetable[];
// decl: static void monte_disp(CameraId camera, void* param);
// decl: static BOOL get_monte_check(Vec* a, Vec* b);
// proto: static USER_FUNC(fall_rtn);
static USER_FUNC(fall_rtn) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    BOOL exists = FALSE;
    RollWork* data = wp->data;
    const char* sfx;
    s32 total;
    s32 i;
    s32 t;
    s32 k;
    s32 j;
    s32 n;
    s32 r;
    s32 retry;
    MonteSub* sub;
    f32 lo;
    f32 hi;
    Vec v;
    Vec a;
    Vec b;
    Vec hit;
    HitCheckQuery query;
    HitCheckQuery* qp;
    Monte* m;

    if (isFirstCall) {
        if (monte_p != NULL) {
            exists = TRUE;
        }
        total = 0;
        for (i = 0; montetable[i].type; i++) {
            total += montetable[i].num;
        }
        monte_p = _mapAlloc(total * sizeof(Monte));
        memset(monte_p, 0, total * sizeof(Monte));
        monte_p->num = total;
        monte_p->wp = wp;
        data->monteCount = 0;
        t = 0;
        k = 0;
        n = 0;
        for (i = 0; i < monte_p->num; i++) {
            sub = &monte_p[i].sub;
            sub->pos.y = 210.0f;
            retry = 0;
            while (TRUE) {
                if (++retry > 500) {
                    sub->pos = (Vec){0.0f, 0.0f, 0.0f};
                    break;
                }
                if (montetable[t].x0 < montetable[t].x1) {
                    lo = montetable[t].x0;
                    hi = montetable[t].x1;
                } else {
                    lo = montetable[t].x1;
                    hi = montetable[t].x0;
                }
                sub->pos.x = lo + irand(100.0f * (hi - lo)) / 100.0f;
                if (montetable[t].z0 < montetable[t].z1) {
                    lo = montetable[t].z0;
                    hi = montetable[t].z1;
                } else {
                    lo = montetable[t].z1;
                    hi = montetable[t].z0;
                }
                hi -= lo;
                sub->pos.z = lo + irand(100.0f * hi) / 100.0f;
                a = sub->pos;
                a.y = 0.0f;
                for (j = 0; j < k; j++) {
                    b = (sub - (j + 1))->pos;
                    b.y = 0.0f;
                    PSVECSubtract(&a, &b, &v);
                    if (PSVECMag(&v) < 20.0f) {
                        break;
                    }
                }
                if (j != k) {
                    continue;
                }
                qp = &query;
                query.targetPos = sub->pos;
                query.targetDistance = 220.0f;
                query.targetDir = (Vec){0.0f, -1.0f, 0.0f};
                if (hitCheckVecFilter(qp, NULL) == NULL) {
                    continue;
                }
                query.targetPos.x -= 9.0f;
                hit = query.hitPos;
                if (hitCheckVecFilter(qp, NULL) != NULL && query.hitPos.y > hit.y + 1.0f) {
                    continue;
                }
                sub->pos.y = query.hitPos.y;
                break;
            }
            n++;
            if (++k >= montetable[t].num) {
                if (montetable[t].type == 2) {
                    for (j = 0; j < n; j++) {
                        monte_p[i - j].hidden = 1;
                        monte_p[i - j].state = 1;
                    }
                    for (j = 0; j < montetable[t].num; j++) {
                        do {
                            r = irand(n);
                        } while (!monte_p[i - r].hidden);
                        monte_p[i - r].hidden = 0;
                        monte_p[i - r].state = 0;
                    }
                    n = 0;
                }
                k = 0;
                t++;
            }
            sub->scale = 1.0f;
        }
    }
    sfx = (0, "SFX_EVT_GAME_MONTE_COUNT1"); /* comma expr: string address into its own saved reg */
    for (i = 0; i < monte_p->num; i++) {
        m = &monte_p[i];
        switch (m->state) {
            case 0:
                if (get_monte_check(&m->sub.pos, &marioGetPtr()->position) == TRUE) {
                    data->monteCount++;
                    psndSFXOn_3D(sfx, &marioGetPtr()->position);
                    m->hidden = 1;
                    m->state = 1;
                }
                break;
            case 1:
                break;
        }
    }
    if (!exists) {
        dispEntry(CAMERA_3D, 0.0f, 1, monte_disp, monte_p);
    }
    return EVT_RETURN_BLOCK;
}
