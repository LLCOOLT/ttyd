// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// decl: #define ATMIC_TERESA_SCALE (*(f32*)atmic_teresa_scale)
// proto: USER_FUNC(teresa_wait_bikkuri2);
USER_FUNC(teresa_wait_bikkuri2) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (teresa[i].state != 30) {
            return EVT_RETURN_BLOCK;
        }
    }
    for (i = 0; i < 8; i++) {
        teresa[i].state = 31;
    }
    ATMIC_TERESA_SCALE = 1.0f;
    return EVT_RETURN_DONE;
}
