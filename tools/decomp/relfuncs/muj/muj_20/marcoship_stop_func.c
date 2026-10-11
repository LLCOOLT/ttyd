// decl: typedef struct MarcoShip { f32 angle; f32 speed; f32 max; s32 stopped; s32 state; s32 field_0x14; OSTime time; } MarcoShip;
// decl: MarcoShip* marcoship;
// proto: USER_FUNC(marcoship_stop_func);
USER_FUNC(marcoship_stop_func) {
    marcoship->state = 2;
    return EVT_RETURN_DONE;
}
