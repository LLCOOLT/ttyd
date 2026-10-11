// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// include: memory.h
// include: string.h
// include: driver/animdrv.h
// include: eff/eff_kemu_test.h
// decl: int rand(void);
// decl: s32 psndSFXChk(s32 id);
// decl: void psndSFXOff(s32 id);
// decl: s32 psndSFXOn_3D(const char* name, Vec* position);
// decl: void _firebar_rot(FirebarWork* wp);
// decl: void _firebar_trans(FirebarWork* wp);
// proto: USER_FUNC(firebar_entry);
USER_FUNC(firebar_entry) {
    FirebarSetup* setup = (FirebarSetup*)evtGetValue(event, event->args[0]);
    FirebarWork* wp;
    FirebarBall* ball;
    MarioWork* mario;
    FirebarBall* balls;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;
    s32 n;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(FirebarWork));
        memset(wp, 0, sizeof(FirebarWork));
        wp->type = setup->type;
        wp->pos = setup->pos;
        wp->count = setup->count;
        wp->callback = setup->callback;
        wp->field_0x20 = setup->field_0x14;
        wp->spacing = setup->spacing;
        wp->speed = setup->speed;
        wp->scale = 1.0f;
        wp->prevAngle = 0.0f;
        wp->angle = 0.0f;
        wp->hitCount = 0;
        wp->setup = setup;
        wp->field_0x28 = setup->field_0x20;
        wp->radius = setup->radius;
        wp->sfxId = 0;
        wp->state = 0;
        wp->shadowAngle = 0.0f;
        switch (wp->type) {
            case 0:
                wp->angle = setup->field_0x20;
                break;
            case 1:
                if (setup->pos.x < setup->field_0x20) {
                    wp->speed = __fabsf(setup->speed);
                } else {
                    wp->speed = -1.0f * __fabsf(setup->speed);
                }
                wp->scale = 0.0f;
                break;
        }
        wp->balls = _mapAlloc(wp->count * sizeof(FirebarBall));
        memset(wp->balls, 0, wp->count * sizeof(FirebarBall));
        ball = wp->balls;
        for (i = 0; i < wp->count; i++, ball++) {
            ball->pose = animPoseEntry("c_fireber", 0);
            animPosePeraOn(ball->pose);
            ball->pos = (Vec){0.0f, 0.0f, 0.0f};
            animPoseSetAnim(ball->pose, "FRB_S_1", TRUE);
        }
        event->userdata[0] = (s32)wp;
    }
    *(s32*)&wp = event->userdata[0];
    if (wp->flags & 8) {
        if (psndSFXChk(wp->sfxId) == 0) {
            psndSFXOff(wp->sfxId);
            wp->sfxId = -1;
        }
        balls = wp->balls;
        for (j = 0; j < 3; j++) {
            n = (wp->count + 1) * j / 3;
            x = balls[n].pos.x + (rand() % 16 - 8);
            y = 10.0f + balls[n].pos.y;
            z = balls[n].pos.z + (rand() % 5 + 3);
            effKemuTestEntry(0, x, y, z, 1.0f);
        }
        ball = wp->balls;
        for (i = 0; i < wp->count; i++, ball++) {
            animPoseRelease(ball->pose);
        }
        _mapFree(wp->balls);
        _mapFree(wp);
        return EVT_RETURN_DONE;
    }
    mario = marioGetPtr();
    if (*(u16*)&mario->currMotionId == 0x20 || *(u16*)&mario->currMotionId == 0x1F || mario->unk4C > 0) {
        wp->flags |= 4;
    } else {
        wp->flags &= ~4;
    }
    if (__fabsf(mario->position.x - wp->pos.x) < 120.0f) {
        if (psndSFXChk(wp->sfxId)) {
            wp->sfxId = psndSFXOn_3D((const char*)0x1CD, &wp->pos);
        }
    } else if (psndSFXChk(wp->sfxId) == 0) {
        psndSFXOff(wp->sfxId);
        wp->sfxId = -1;
    }
    wp->shadowAngle += 6.0f;
    if (wp->shadowAngle > 360.0f) {
        wp->shadowAngle -= 360.0f;
    }
    switch (wp->type) {
        case 0:
            _firebar_rot(wp);
            break;
        case 1:
            _firebar_trans(wp);
            break;
    }
    if (wp->callback != NULL) {
        wp->callback(wp, 0);
    }
    return EVT_RETURN_BLOCK;
}
