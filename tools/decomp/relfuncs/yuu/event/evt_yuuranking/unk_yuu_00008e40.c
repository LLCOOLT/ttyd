// include: manager/fontmgr.h
// include: dolphin/mtx.h
// decl: void FontDrawMessageMtx(Mtx mtx, const char* msg);
// proto: void unk_yuu_00008e40(f32 x, f32 y, f32 scale, const char* msg, s32 width);
void unk_yuu_00008e40(f32 x, f32 y, f32 scale, const char* msg, s32 width) {
    Mtx trans;
    Mtx scl;
    Mtx mtx;
    f32 sx;

    PSMTXTrans(trans, x, y, 0.0f);
    if (FontGetMessageWidth(msg) > width) {
        sx = (width * scale) / FontGetMessageWidth(msg);
    } else {
        sx = scale;
    }
    PSMTXScale(scl, sx, scale, scale);
    PSMTXConcat(trans, scl, mtx);
    FontDrawMessageMtx(mtx, msg);
}
