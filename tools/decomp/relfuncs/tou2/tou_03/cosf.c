// decl: double cos(double x);
// proto: static f32 cosf(f32 x);
#pragma dont_inline on
static f32 cosf(f32 x) {
    return cos(x);
}
#pragma dont_inline reset
