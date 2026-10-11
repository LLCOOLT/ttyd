// include: pmario_sound.h
// decl: typedef struct Mri02Switch { f32 base; f32 weight; f32 target; f32 pos; } Mri02Switch;
// decl: Mri02Switch mri02switch;
// decl: void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
// decl: void hitBindUpdate(const char* name);
// proto: USER_FUNC(moveSwitch);
USER_FUNC(moveSwitch) {
    Mri02Switch* sw = &mri02switch;
    f32 delta;

    if (isFirstCall) {
        sw->target = sw->pos = sw->base = sw->weight = 0.0f;
        event->userdataf[0] = 0.0f;
        event->userdata[1] = 0;
        event->userdata[2] = 0;
    }
    sw->target = sw->base + sw->weight;
    if (sw->target < -10.0f) {
        sw->target = -10.0f;
    }
    delta = sw->target - sw->pos;
    if (delta >= 0.25f) {
        delta = 0.25f;
    } else if (delta <= -0.25f) {
        delta = -0.25f;
    }
    sw->pos += delta;
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        BOOL changed = FALSE;

        event->userdata[2]--;
        if (event->userdata[2] < 0) {
            event->userdata[2] = 0;
            if (event->userdataf[0] != delta) {
                changed = TRUE;
            }
            event->userdataf[0] = delta;
        }
        if (changed) {
            if (event->userdata[1] != 0) {
                psndSFXOff(event->userdata[1]);
            }
            if (delta < 0.0f) {
                event->userdata[1] = psndSFXOn_3D("SFX_STG2_SWITCH_ON1", &pos);
                event->userdata[2] = 3;
            }
            if (delta > 0.0f) {
                event->userdata[1] = psndSFXOn_3D("SFX_STG2_SWITCH_OFF1", &pos);
                event->userdata[2] = 3;
            }
        }
    }
    mapObjTranslate("S_sui_l", 0.0f, sw->pos, 0.0f);
    hitBindUpdate("A_sui_l");
    return EVT_RETURN_BLOCK;
}
