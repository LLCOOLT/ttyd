// proto: f32 randf(f32 min, f32 max);
int rand(void);

f32 randf(f32 min, f32 max) {
    return min + (max - min) * (rand() / 32767.0f);
}
