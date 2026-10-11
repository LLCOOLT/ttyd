// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: memory.h
// include: string.h
// include: mario/mario.h
// include: driver/dispdrv.h
// include: pmario_sound.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct HikokiWork { u32 flags; s32 phase; s32 coins; s32 result; s32 monteCount; EventEntry* viewEvent; } HikokiWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 y0; f32 y1; s32 num; } MonteTable;
// decl: static Monte* monte_p;
// decl: static void* yuunpc_wp;
// decl: #define MONTETABLE ((MonteTable*)montetable)
// decl: static void monte_disp(CameraId camera, void* param);
// decl: static BOOL get_monte_check(Vec* a, Vec* b);
// proto: static USER_FUNC(fall_rtn);
static USER_FUNC(fall_rtn) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    BOOL exists = FALSE;
    HikokiWork* data = wp->data;
    const char* sfx;
    s32 total;
    s32 i;
    s32 t;
    s32 k;
    s32 j;
    MonteSub* sub;
    f32 lo;
    f32 hi;
    Vec v;
    Monte* m;

    if (isFirstCall) {
        if (monte_p != NULL) {
            exists = TRUE;
        }
        total = 0;
        for (i = 0; MONTETABLE[i].num; i++) {
            total += MONTETABLE[i].num;
        }
        monte_p = _mapAlloc(total * sizeof(Monte));
        memset(monte_p, 0, total * sizeof(Monte));
        monte_p->num = total;
        monte_p->wp = wp;
        data->monteCount = 0;
        t = 0;
        k = 0;
        for (i = 0; i < monte_p->num; i++) {
            sub = &monte_p[i].sub;
            sub->pos.z = 0.0f;
            do {
                if (MONTETABLE[t].x0 < MONTETABLE[t].x1) {
                    lo = MONTETABLE[t].x0;
                    hi = MONTETABLE[t].x1;
                } else {
                    lo = MONTETABLE[t].x1;
                    hi = MONTETABLE[t].x0;
                }
                sub->pos.x = lo + irand(100.0f * (hi - lo)) / 100.0f;
                if (MONTETABLE[t].y0 < MONTETABLE[t].y1) {
                    lo = MONTETABLE[t].y0;
                    hi = MONTETABLE[t].y1;
                } else {
                    lo = MONTETABLE[t].y1;
                    hi = MONTETABLE[t].y0;
                }
                sub->pos.y = lo + irand(100.0f * (hi - lo)) / 100.0f;
                for (j = 0; j < k; j++) {
                    PSVECSubtract(&sub->pos, &(sub - (j + 1))->pos, &v);
                    if (PSVECMag(&v) < 20.0f) {
                        break;
                    }
                }
            } while (j != k);
            if (++k >= MONTETABLE[t].num) {
                k = 0;
                t++;
            }
            sub->scale = 1.0f;
        }
    }
    sfx = "SFX_EVT_GAME_MONTE_COUNT1";
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
