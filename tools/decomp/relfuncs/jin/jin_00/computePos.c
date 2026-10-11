// include: dolphin/mtx.h
// decl: typedef struct Teresa { Vec vel; f32 angle; Vec ofs; f32 field_0x1C; f32 field_0x20; Vec from; Vec to; s32 wait; u8 alpha; u8 seq; } Teresa;
// proto: static void computePos(Teresa* ter, Vec* out);
static void computePos(Teresa* ter, Vec* out) {
    Vec v;
    Mtx m;

    v.x = ter->ofs.x;
    v.y = 0.0f;
    v.z = ter->ofs.z;

    PSMTXRotRad(m, 'Y', 0.017453292f * ter->angle);
    PSMTXMultVec(m, &v, out);
}
