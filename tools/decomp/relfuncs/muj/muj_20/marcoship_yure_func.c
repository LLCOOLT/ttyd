// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: dolphin/os.h
// decl: typedef struct MarcoShip { f32 angle; f32 speed; f32 max; s32 stopped; s32 state; s32 field_0x14; OSTime time; } MarcoShip;
// decl: MarcoShip* marcoship;
// proto: USER_FUNC(marcoship_yure_func);
USER_FUNC(marcoship_yure_func) {
    MarcoShip* ms = marcoship;
    s32* args = event->args;

    switch (ms->state) {
        case 0:
            if (ms->speed > 0.0f) {
                if (ms->angle > ms->max) {
                    ms->speed *= -1.0f;
                    ms->state = 1;
                    ms->time = gp->renderTime;
                    break;
                }
            } else if (ms->angle < -ms->max) {
                ms->speed *= -1.0f;
                ms->state = 1;
                ms->time = gp->renderTime;
                break;
            }
            ms->angle += ms->speed;
            break;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)ms->time) > 500) {
                ms->state = 0;
            }
            break;
        case 2:
            if (ms->speed > 0.0f) {
                if (ms->angle > 0.0f) {
                    ms->state = 3;
                    break;
                }
            } else if (ms->angle < 0.0f) {
                ms->state = 3;
                break;
            }
            ms->angle += ms->speed;
            break;
        case 3:
            ms->angle = 0.0f;
            ms->stopped = 1;
            break;
    }
    evtSetFloat(event, args[0], ms->angle);
    evtSetValue(event, args[1], ms->stopped);
    return EVT_RETURN_DONE;
}
