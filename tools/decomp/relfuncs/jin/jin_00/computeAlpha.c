// include: mario/mario.h
// decl: typedef struct Teresa { Vec vel; f32 angle; Vec ofs; f32 field_0x1C; f32 field_0x20; Vec from; Vec to; s32 wait; u8 alpha; u8 seq; } Teresa;
// proto: s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle);
s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle) {
    f32 dir;

    if (angle > 180.0f) {
        angle = 360.0f - angle;
    }
    dir = mp->unk1AC - 180.0f;
    if (dir < 0.0f) {
        dir += 360.0f;
    }
    if (dir < 90.0f) {
        if (angle < 90.0f) {
            ter->alpha = 128.0f * (angle / 90.0f) + 128.0f;
            return 0;
        }
        ter->alpha = 255;
        return 1;
    } else {
        if (angle > 90.0f) {
            ter->alpha = 128.0f * ((180.0f - angle) / 90.0f) + 128.0f;
            return 0;
        }
        ter->alpha = 255;
        return 1;
    }
}
