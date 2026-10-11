// proto: f32 lineardec_type(s32 step, s32 total, f32 start, f32 end);
f32 lineardec_type(s32 step, s32 total, f32 start, f32 end) {
    f32 cur;
    f32 speed;
    f32 sum;
    s32 accel = total * 20 / 100;
    s32 decel = total * 80 / 100;
    s32 i;

    speed = accel;
    sum = speed;

    for (i = 0; i < total; i++) {
        if (i >= decel) {
            speed -= 1.0f;
        }
        sum += speed;
        if (i == step) {
            cur = sum;
        }
    }
    return start + cur * (end - start) / sum;
}
