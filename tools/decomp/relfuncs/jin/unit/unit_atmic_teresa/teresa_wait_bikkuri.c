// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// proto: USER_FUNC(teresa_wait_bikkuri);
USER_FUNC(teresa_wait_bikkuri) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (teresa[i].state != 15) {
            return EVT_RETURN_BLOCK;
        }
    }
    return EVT_RETURN_DONE;
}
