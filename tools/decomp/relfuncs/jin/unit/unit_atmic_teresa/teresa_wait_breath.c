// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// proto: USER_FUNC(teresa_wait_breath);
USER_FUNC(teresa_wait_breath) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (teresa[i].state != 60) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 30; i++) {
        AtmTeresa* t = &teresa[i];
        t->state = 63;
        t->wait = 30;
    }
    return EVT_RETURN_DONE;
}
