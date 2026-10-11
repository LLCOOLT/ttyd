// include: mario/mario.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// include: party/party_vivian.h
// decl: extern int __float_nan[];
// decl: static inline s32 fb_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
// decl: static inline f32 fb_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (fb_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
// proto: s32 _firebar_hitCheck(FirebarWork* wp, FirebarBall* ball);
s32 _firebar_hitCheck(FirebarWork* wp, FirebarBall* ball) {
    MarioWork* mario = marioGetPtr();
    f32 dx;
    f32 dz;
    f32 dy;
    BOOL near = FALSE;

    if (wp->flags & 6) {
        return 0;
    }
    dx = mario->position.x - ball->pos.x;
    dy = mario->position.y - ball->pos.y;
    dz = mario->position.z - ball->pos.z;
    if (dy > 0.0f) {
        if (dy < 0.8f * (15.0f * wp->scale)) {
            near = TRUE;
        }
    } else if (__fabsf(dy) < mario->wPlayerCollisionBox.y) {
        near = TRUE;
    }
    if (near && fb_sqrtf(dx * dx + dz * dz) <= mario->wPlayerCollisionBox.x / 2.0f / 2.0f + wp->spacing / 2.0f * wp->scale &&
        vivianGetStatus() != 1 && vivianGetStatus() != 2) {
        return 1;
    }
    return 0;
}
