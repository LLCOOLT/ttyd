// proto: static f32 randf(f32 min, f32 max);
#pragma opt_propagation off
#pragma opt_lifetimes off
int rand(void);

static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
