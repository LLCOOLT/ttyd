// include: stdlib.h
// proto: static f32 randf(f32 min, f32 max);
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
