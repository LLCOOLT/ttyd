// decl: typedef void (*voidfunctionptr)(void);
// decl: extern voidfunctionptr _ctors[];
// decl: extern voidfunctionptr _dtors[];
// proto: void _epilog(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    if (strcmp(gp->currentMapName, "sys_01") == 0) {
        sys_01_release();
    }
    camGetPtr(CAMERA_2D)->flags &= ~0x200;
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
