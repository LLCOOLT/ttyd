// include: evt/evt_cmd.h
// include: driver/swdrv.h
// proto: void irai_flag_clear(void);
void irai_flag_clear(void) {
    s32 i;

    for (i = GSWF(5405); i <= GSWF(5421); i++) {
        swClear(i + EVTDAT_GSWF_BASE);
    }
    for (i = GSW(1469); i <= GSW(1474); i++) {
        swByteSet(i + EVTDAT_GSW_BASE, 0);
    }
}
