// proto: void __tou_srand(u32 seed);
#pragma dont_inline on
void __tou_srand(u32 seed) {
    x[0] = seed;
}
#pragma dont_inline reset
