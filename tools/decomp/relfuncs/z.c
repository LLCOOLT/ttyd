// decl: double tan(double x);
// proto: USER_FUNC(z);
USER_FUNC(z) {
    f32 t = tan(0.21816612780094147);
    // evt float encoding of the distance that fits 240 units in the fov
    event->lwData[0] = (s32)(1024.0f * (240.0f / t / 2)) - 230000000;
    return EVT_RETURN_DONE;
}
