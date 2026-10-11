// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// decl: #define ATMIC_TERESA_SCALE (*(f32*)atmic_teresa_scale)
// proto: USER_FUNC(teresa_wait_breath2);
USER_FUNC(teresa_wait_breath2) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if (teresa[i].state != 70) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 30; i++) {
        teresa[i].state = 71;
    }
    ATMIC_TERESA_SCALE = 1.0f;
    return EVT_RETURN_DONE;
}
