// decl: s32 shadowEntry(f32 x, f32 y, f32 z, f32 size);
// decl: void shadowSetCollision(s32 id, s32 on);
// proto: USER_FUNC(dummy_shadow);
USER_FUNC(dummy_shadow) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 size = evtGetFloat(event, args[3]);

    shadowSetCollision(shadowEntry(x, y, z, 10.0f * size), 0);
    return EVT_RETURN_BLOCK;
}
