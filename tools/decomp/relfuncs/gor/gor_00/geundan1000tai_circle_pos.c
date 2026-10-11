// include: system.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: void geundan1000tai_circle_pos(Vec* pos);
void geundan1000tai_circle_pos(Vec* pos) {
    f32 s;
    f32 angle;
    f32 radius;
    f32 c;

    radius = irand(180) + 120;
    angle = 6.2831855f * irand(360) / 360.0f;
    s = sin(angle);
    c = cos(angle);

    pos->x = 0.9f * (radius * s);
    pos->y = 15.0f;
    pos->z = 0.5f * (radius * c) - 300.0f;
}
