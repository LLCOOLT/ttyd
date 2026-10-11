// decl: int rand(void);
// proto: s32 randn(s32 min, s32 max);
s32 randn(s32 min, s32 max) {
    return min + rand() % (max - min);
}
