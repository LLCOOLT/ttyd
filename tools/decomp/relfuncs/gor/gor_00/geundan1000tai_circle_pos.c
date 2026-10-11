// include: system.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: void geundan1000tai_circle_pos(Vec* pos);
void geundan1000tai_circle_pos(Vec* pos) {
    f32 radius = irand(180) + 120;
    f32 angle = 6.2831855f * irand(360) / 360.0f;
    f32 s = sin(angle);
    f32 c = cos(angle);

    pos->x = 0.9f * (radius * s);
    pos->y = 15.0f;
    pos->z = 0.5f * (radius * c) - 300.0f;
}
