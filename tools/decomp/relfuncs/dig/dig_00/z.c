// decl: double tan(double x);
// proto: static USER_FUNC(z);
static USER_FUNC(z) {
    f32 t = tan(0.21816612780094147);

    event->lwData[0] = (s32)(1024.0f * (240.0f / t)) - 230000000;
    return EVT_RETURN_DONE;
}
