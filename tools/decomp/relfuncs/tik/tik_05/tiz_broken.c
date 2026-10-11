// include: memory.h
// include: string.h
// include: system.h
// include: dolphin/gx.h
// include: driver/dispdrv.h
// decl: typedef struct BrokenPiece { s32 state; s32 delay; s32 dir; Vec vel; Vec pos; f32 rot; f32 rotSpeed; f32 gx; f32 gy; } BrokenPiece;
// decl: typedef struct BrokenWork { s32 copied; smartEntry* tex; smartEntry* pieces; } BrokenWork;
// decl: s32 select;
// decl: BrokenWork broken_work;
// decl: extern int __float_nan[];
// decl: static inline s32 tb_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
// decl: static inline f32 tb_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (tb_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
// decl: static inline f32 tb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 tb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: void tiz_broken_draw(CameraId cameraId, void* param);
// proto: USER_FUNC(tiz_broken);
USER_FUNC(tiz_broken) {
    s32 done = 0;
    BrokenPiece* p;
    s32 x;
    s32 y;
    f32 dx;
    f32 dy;
    f32 nx;
    f32 ny;
    f32 len;
    f32 angle;

    if (isFirstCall) {
        memset(broken_wp, 0, sizeof(BrokenWork));
        broken_wp->tex = smartAlloc(GXGetTexBufferSize(304, 240, GX_TF_RGB565, GX_FALSE, 0), 1);
        broken_wp->pieces = smartAlloc(sizeof(BrokenPiece) * 31 * 39, 1);
        broken_wp->copied = 0;
        p = broken_wp->pieces->address;
        for (y = 0; y < 30; y++) {
            for (x = 0; x < 38; x++) {
                dy = 0.5f + -y / 29.0f;
                dx = x / 37.0f - 0.5f;
                if (dy > 0.0f) {
                    if (dx < 0.0f) {
                        p->dir = 0;
                    } else {
                        p->dir = 1;
                    }
                } else {
                    if (dx < 0.0f) {
                        p->dir = 2;
                    } else {
                        p->dir = 3;
                    }
                }
                if (dx != 0.0f || dy != 0.0f) {
                    len = tb_sqrtf(dx * dx + dy * dy);
                    nx = dx / len;
                    ny = dy / len;
                } else {
                    nx = ny = len = 0.0f;
                }
                p->state = 0;
                p->delay = param_tbl[0] * len;
                p->pos.x = 0.0f;
                p->pos.y = 0.0f;
                p->pos.z = 0.0f;
                p->rotSpeed = 0.0f;
                p->rot = 0.0f;
                p->vel.x = -nx * param_tbl[1];
                p->vel.y = -ny * param_tbl[1];
                p->vel.z = 10.0f;
                angle = 6.2831855f * angleABf(0.0f, 0.0f, dx, dy) / 360.0f;
                p->gx = param_tbl[3] * tb_sin(angle);
                p->gy = param_tbl[3] * -tb_cos(angle);
                p++;
            }
            p++;
        }
    }
    p = broken_wp->pieces->address;
    for (y = 0; y < 30; y++) {
        for (x = 0; x < 38; x++) {
            switch (p->state) {
                case 0:
                    if (p->delay != 0) {
                        p->delay--;
                        break;
                    }
                    p->pos.x += p->gx;
                    p->pos.y += p->gy;
                    p->pos.x += p->vel.x;
                    p->pos.y += p->vel.y;
                    p->pos.z += p->vel.z;
                    p->vel.x *= param_tbl[2];
                    p->vel.y *= param_tbl[2];
                    p->vel.z *= param_tbl[2];
                    p->rotSpeed += param_tbl[4];
                    p->rot += p->rotSpeed;
                    if (__fabs(p->pos.x) > 340.0 || __fabs(p->pos.y) > 260.0) {
                        p->state++;
                    }
                    break;
                case 1:
                    done++;
                    break;
            }
            p++;
        }
        p++;
    }
    if (done >= 30 * 38) {
        smartFree(broken_wp->tex);
        smartFree(broken_wp->pieces);
        return EVT_RETURN_DONE;
    }
    dispEntry((CameraId)8, 0.0f, 0, tiz_broken_draw, NULL);
    return EVT_RETURN_BLOCK;
}
