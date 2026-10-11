// include: mario/mario.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// include: system.h
// include: driver/animdrv.h
// include: party/party_vivian.h
// decl: double sin(double x);
// decl: double cos(double x);
// decl: s32 _firebar_hitCheck2(FirebarWork* wp);
// proto: void _firebar_trans(FirebarWork* wp);
void _firebar_trans(FirebarWork* wp) {
    FirebarBall* ball = wp->balls;
    MarioWork* mario = marioGetPtr();
    s32 hit;
    f32 a1;
    f32 a2;
    f32 diff;
    f32 k;
    f32 dy;
    f32 dz;
    s32 i;

    sin(6.2831855f * wp->shadowAngle / 360.0f);
    switch (wp->state) {
        case 0:
            wp->scale += 0.05f;
            if (wp->scale > 1.0f) {
                wp->scale = 1.0f;
                wp->state++;
            }
            break;
        case 1:
            if (__fabsf(wp->pos.x - wp->field_0x28) < 20.0f * __fabsf(wp->speed)) {
                wp->state++;
            }
            break;
        case 2:
            wp->scale -= 0.05f;
            if (wp->scale < 0.0f) {
                wp->pos.x = wp->setup->pos.x;
                wp->state = 0;
            }
            break;
    }
    if (wp->state == 1) {
        k = wp->scale;
    } else {
        k = 1.0f;
    }
    wp->pos.x += wp->speed;
    for (i = 0; i < wp->count; i++, ball++) {
        animPoseMain(ball->pose);
        if (!(wp->flags & 1)) {
            dz = k * (i * wp->spacing);
            dy = 0.5f * (20.0f * (1.0f - wp->scale));
            ball->pos.x = wp->pos.x;
            ball->pos.y = wp->pos.y + dy;
            ball->pos.z = wp->pos.z + dz;
        }
    }
    if (wp->state == 1) {
        hit = _firebar_hitCheck2(wp);
        a1 = angleABf(wp->pos.x, wp->pos.z, mario->position.x, mario->position.z);
        a2 = angleABf(wp->pos.x, wp->pos.z, wp->balls[wp->count - 1].pos.x, wp->balls[wp->count - 1].pos.z);
    diff = compAngle(a1, a2);
        if (hit > 0) {
            wp->hitCount = 0;
            if (wp->callback != NULL) {
                wp->callback(wp, 2);
            }
        } else if (!(wp->flags & 6) && hit == 0 && vivianGetStatus() != 1 && vivianGetStatus() != 2) {
            if (wp->prevAngle < 0.0f && diff > 0.0f && wp->pos.y < mario->position.y) {
                wp->hitCount++;
                if (wp->callback != NULL) {
                    wp->callback(wp, 1);
                }
            }
        }
        wp->prevAngle = diff;
    }
}
