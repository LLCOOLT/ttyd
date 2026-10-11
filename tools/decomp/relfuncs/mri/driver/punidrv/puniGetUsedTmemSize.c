// include: driver/punidrv.h
// proto: u32 puniGetUsedTmemSize(void);
u32 puniGetUsedTmemSize(void) {
    return work->usedTmem;
}
