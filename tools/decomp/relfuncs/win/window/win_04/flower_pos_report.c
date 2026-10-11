// decl: typedef struct Flower { s16 state; s16 timer; f32 x; f32 y; f32 scale; f32 targetScale; s32 alpha; } Flower;
// decl: typedef struct FlowerWork { s32 count; Flower* flowers; } FlowerWork;
// proto: USER_FUNC(flower_pos_report);
USER_FUNC(flower_pos_report) {
    FlowerWork* wp = (FlowerWork*)event->lwData[10];
    s32 i;

    for (i = 0; i < wp->count; i++) {
    }
    return EVT_RETURN_DONE;
}
