// include: mario/mario.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// include: dolphin/mtx.h
// include: party/party_vivian.h
// proto: s32 _firebar_hitCheck2(FirebarWork* wp);
s32 _firebar_hitCheck2(FirebarWork* wp) {
    FirebarBall* balls = wp->balls;
    MarioWork* mario = marioGetPtr();
    Vec rel;
    Vec dir;
    Vec side;
    Vec up = {0.0f, 1.0f, 0.0f};
    f32 dy;
    f32 len;
    f32 w;
    f32 dp;
    f32 ds;
    f32 r;
    BOOL near;

    if (wp->flags & 6) {
        return 0;
    }
    dy = mario->position.y - wp->pos.y;
    near = FALSE;
    if (dy > 0.0f) {
        if (dy < 0.8f * (15.0f * wp->scale)) {
            near = TRUE;
        }
    } else if (__fabsf(dy) < mario->wPlayerCollisionBox.y) {
        near = TRUE;
    }
    if (!near) {
        return 0;
    }
    PSVECSubtract(&balls[wp->count - 1].pos, &balls[0].pos, &dir);
    PSVECCrossProduct(&dir, &up, &side);
    len = PSVECMag(&dir);
    w = 5.0f * wp->scale;
    PSVECNormalize(&dir, &dir);
    PSVECNormalize(&side, &side);
    PSVECSubtract(&mario->position, &balls[0].pos, &rel);
    dp = PSVECDotProduct(&dir, &rel);
    ds = PSVECDotProduct(&side, &rel);
    r = 10.0f + mario->wPlayerCollisionBox.x;
    if (dp > -r / 2.0f && dp <= r / 2.0f + len && __fabsf(ds) <= mario->wPlayerCollisionBox.x / 2.0f + w &&
        vivianGetStatus() != 1 && vivianGetStatus() != 2) {
        return 1;
    }
    return 0;
}
