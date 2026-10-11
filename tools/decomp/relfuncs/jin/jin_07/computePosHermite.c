// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Teresa { Vec pos; Vec dst; f32 t; f32 field_0x1C; f32 field_0x20; f32 field_0x24; s32 wait; u8 state; } Teresa;
// decl: static Teresa* pTeresa;
// proto: void computePosHermite(ExtPose* pose, Teresa* ter);
void computePosHermite(ExtPose* pose, Teresa* ter) {
    Vec m0 = {0.0f, 0.0f, 0.0f};
    Vec m1 = {1.0f, 0.0f, 0.0f};
    f32 t = ter->t;
    f32 u = 1.0f - t;
    f32 tt = t * t;
    f32 t2 = 2.0f * t;
    f32 h00 = (1.0f + t2) * u * u;
    f32 h10 = t * u * u;
    f32 h11 = (t - 1.0f) * tt;
    f32 h01 = (3.0f - t2) * tt;

    m0.x = ter->field_0x24;
    m0.y = 3.4f * ter->dst.y;
    pose->mtx[0][3] = ter->pos.x * h00 + m0.x * h10 + m1.x * h11 + ter->dst.x * h01;
    pose->mtx[1][3] = ter->pos.y * h00 + m0.y * h10 + m1.y * h11 + ter->dst.y * h01;
    pose->mtx[2][3] = ter->pos.z * h00 + m0.z * h10 + m1.z * h11 + ter->dst.z * h01;
}
