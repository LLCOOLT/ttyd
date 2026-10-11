// include: mario/mario.h
// include: system.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// proto: f32 computeAngle(ExtPose* pose, MarioWork* mp);
f32 computeAngle(ExtPose* pose, MarioWork* mp) {
    f32 a = angleABf(mp->position.x, mp->position.z, pose->mtx[0][3], pose->mtx[2][3]);

    if (0.0f <= a && a < 90.0f) {
        return 90.0f - a;
    }
    if (90.0f <= a && a < 180.0f) {
        return 360.0f - (a - 90.0f);
    }
    if (180.0f <= a && a < 270.0f) {
        return 180.0f + (270.0f - a);
    }
    return 90.0f + (360.0f - a);
}
