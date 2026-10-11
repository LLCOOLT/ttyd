// include: memory.h
// decl: typedef struct MarcoShip { f32 angle; f32 speed; f32 max; s32 stopped; s32 state; s32 field_0x14; OSTime time; } MarcoShip;
// decl: MarcoShip* marcoship;
// proto: USER_FUNC(marcoship_yure_init_func);
USER_FUNC(marcoship_yure_init_func) {
    MarcoShip* ms;

    marcoship = ms = _mapAlloc(sizeof(MarcoShip));
    ms->angle = 0.0f;
    ms->speed = 0.02f;
    ms->max = 1.5f;
    ms->stopped = 0;
    ms->state = 0;
    ms->time = 0;
    return EVT_RETURN_DONE;
}
