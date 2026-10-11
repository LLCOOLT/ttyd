// decl: int rand(void);
// decl: extern s32 R_mystery_cook_list[];
// proto: s32 naniga_okorukana_cook(void);
s32 naniga_okorukana_cook(void) {
    s32 r = rand() % 100;

    if (r < 50) {
        return R_mystery_cook_list[(s32)((u32)(r * 20) / 50.0f)];
    }
    return 182;
}
