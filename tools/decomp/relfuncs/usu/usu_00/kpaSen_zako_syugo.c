// include: dolphin/mtx.h
// decl: typedef struct KpaSen { s8 state; u8 field_0x1; u16 wait; f32 t; Vec start; Vec end; u8 pose99Lo; u8 pose99Hi; u8 pose1Lo; u8 pose1Hi; } KpaSen;
// decl: KpaSen* kpaSen;
// proto: USER_FUNC(kpaSen_zako_syugo);
USER_FUNC(kpaSen_zako_syugo) {
    s32 i;

    for (i = 0; i < 100; i++) {
        kpaSen[i].state = 0;
    }
    return EVT_RETURN_DONE;
}
