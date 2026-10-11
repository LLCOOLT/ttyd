// include: mario/mariost.h
// include: string.h
// decl: void tegami_delete(void);
void _epilog(void) {
    voidfunctionptr* dtor;

    if (strcmp(gp->currentMapName, "gor_10") == 0) {
        tegami_delete();
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
