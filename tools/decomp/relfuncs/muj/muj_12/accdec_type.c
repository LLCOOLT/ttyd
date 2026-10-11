// proto: static f32 accdec_type(s32 step, s32 total, f32 start, f32 end);
static f32 accdec_type(s32 step, s32 total, f32 start, f32 end) {
    f32 cur;
    f32 speed;
    f32 sum;
    s32 accel = total * 20 / 100;
    s32 decel = total * 80 / 100;
    s32 i;

    speed = 0.0f;
    sum = 0.0f;

    for (i = 0; i < total; i++) {
        if (i <= accel) {
            speed += 1.0f;
        } else if (i >= decel) {
            speed -= 1.0f;
        }
        sum += speed;
        if (i == step) {
            cur = sum;
        }
    }
    return start + cur * (end - start) / sum;
}
