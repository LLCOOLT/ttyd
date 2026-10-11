// proto: static s32 compare(const void* a, const void* b);
static s32 compare(const void* a, const void* b) {
    if (((PunidrvSort*)a)->z > ((PunidrvSort*)b)->z) {
        return 1;
    }
    if (((PunidrvSort*)a)->z < ((PunidrvSort*)b)->z) {
        return -1;
    }
    return 0;
}
