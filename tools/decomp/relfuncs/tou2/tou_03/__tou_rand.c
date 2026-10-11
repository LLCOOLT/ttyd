// proto: u32 __tou_rand(void);
u32 __tou_rand(void) {
    x[0] = x[0] * 1103515245 + 12345;
    return ((u32)x[0] >> 16) & 0x7FFF;
}
