// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// decl: s32 extGetPoseNum(void);
// proto: USER_FUNC(teresa_appear_breath);
USER_FUNC(teresa_appear_breath) {
    s32 type = evtGetValue(event, event->args[0]);
    s32 i;
    s32 state = (type == 1) ? 51 : 52;

    for (i = 0; i < extGetPoseNum(); i++) {
        teresa[i].state = state;
    }
    return EVT_RETURN_DONE;
}
