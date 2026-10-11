// include: driver/punidrv.h
// proto: void puniLoadShadowMtx(Mtx mtx);
void puniLoadShadowMtx(Mtx mtx) {
    PSMTXCopy(mtx, work->shadowMtx);
}
