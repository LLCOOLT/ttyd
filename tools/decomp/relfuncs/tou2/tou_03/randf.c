// decl: u32 __tou_rand(void);
// proto: static f32 randf(f32 min, f32 max);
#pragma dont_inline on
static f32 randf(f32 min, f32 max) {
    f32 r = __tou_rand() / 32767.0f;

    return r * (max - min) + min;
}
#pragma dont_inline reset
