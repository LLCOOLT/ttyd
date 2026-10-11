// include: driver/effdrv.h
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(hoshi);
USER_FUNC(hoshi) {
    event->lwData[10] = (s32)effStarStoneEntry(5, 0.0f, 60.0f, -950.0f, 1.0f);
    return EVT_RETURN_DONE;
}
