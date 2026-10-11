// proto: static f32 lect_mario_ido_sub(f32 elapsed, f32 total, f32 end, f32 start);
static f32 lect_mario_ido_sub(f32 elapsed, f32 total, f32 end, f32 start) {
    f32 rem = total - elapsed;

    return (rem * end + elapsed * start) / total;
}
