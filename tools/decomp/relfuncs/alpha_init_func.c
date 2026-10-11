// include: memory.h
// decl: static u8* _ap;
// proto: USER_FUNC(alpha_init_func);
USER_FUNC(alpha_init_func) {
    _ap = _mapAlloc(1);
    *_ap = 255;
    return EVT_RETURN_DONE;
}
