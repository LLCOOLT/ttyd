// proto: static f32 computePos(f32 a, f32 b, f32 t);
static f32 computePos(f32 a, f32 b, f32 t) {
    return (1.0f - t) * a + t * b;
}
