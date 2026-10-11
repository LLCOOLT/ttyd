// include: memory.h
// decl: typedef struct OrbitData { f32 angle; f32 dist; } OrbitData;
// decl: OrbitData* _op;
// proto: USER_FUNC(mario_main_init_func);
USER_FUNC(mario_main_init_func) {
    _op = _mapAlloc(0x40);
    return EVT_RETURN_DONE;
}
