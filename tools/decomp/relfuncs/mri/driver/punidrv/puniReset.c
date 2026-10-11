// include: driver/punidrv.h
// include: memory.h
// include: string.h
// proto: void puniReset(void);
void puniReset(void) {
    PunidrvWork* wp = work;

    if (wp->poses != NULL) {
        __memFree(HEAP_EXT, wp->poses);
    }
    if (wp->texs != NULL) {
        __memFree(HEAP_EXT, wp->texs);
    }
    if (wp->mtxs != NULL) {
        __memFree(HEAP_EXT, wp->mtxs);
    }
    if (wp->vtx != NULL) {
        __memFree(HEAP_EXT, wp->vtx);
    }
    if (wp->sort != NULL) {
        __memFree(HEAP_EXT, wp->sort);
    }
    if (wp->dl != NULL) {
        __memFree(HEAP_EXT, wp->dl);
    }
    if (wp->dlSize != NULL) {
        __memFree(HEAP_EXT, wp->dlSize);
    }
    memset(wp, 0, sizeof(PunidrvWork));
}
