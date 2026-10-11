// include: driver/punidrv.h
// include: memory.h
// proto: void puniInit(void);
void puniInit(void) {
    PunidrvWork* wp;

    work = wp = _mapAlloc(sizeof(PunidrvWork));
    wp->poseNum = 0;
    wp->poses = NULL;
    wp->useFade = TRUE;
}
