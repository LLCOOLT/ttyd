// proto: f32 randf(f32 min, f32 max);
int rand(void);

f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
