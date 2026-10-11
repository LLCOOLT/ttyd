// include: data/mapdata.h
// include: pmario_sound.h
// proto: void _prolog(void);
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("sys_00", dummy_evt);
    relSetEvtAddr("sys_01", sys_01_init_evt);
    if (evtGetValue(NULL, GSW(0)) != 2 && evtGetValue(NULL, GSW(0)) != 125 && evtGetValue(NULL, GSW(0)) != 229 &&
        evtGetValue(NULL, GSW(0)) != 280) {
        psndStopAllFadeOut();
    }
    camGetPtr(CAMERA_2D)->flags |= 0x200;
    camGetPtr(CAMERA_2D)->flags &= ~0x100;
    camGetPtr(CAMERA_2D)->flags |= 0x400;
}
