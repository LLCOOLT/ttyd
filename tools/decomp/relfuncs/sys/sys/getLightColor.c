// proto: s32 getLightColor(f32 angle);
s32 getLightColor(f32 angle) {
    f32 a = fmod(angle, 360.0);
    s32 c;

    if (a >= 270.0f) {
        c = 360.0f - a;
    } else if (a >= 180.0f) {
        c = a - 180.0f;
    } else if (a >= 90.0f) {
        c = 180.0f - a;
    } else {
        c = a;
    }
    return 255 - c * 2;
}
