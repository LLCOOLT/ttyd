// proto: static f32 randf(f32 min, f32 max);
int rand(void);

#pragma dont_inline on
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
#pragma dont_inline reset
