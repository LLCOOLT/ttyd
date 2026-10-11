// include: memory.h
// include: stdlib.h
// proto: USER_FUNC(make_tbl);
USER_FUNC(make_tbl) {
    s32 i;
    s32 a;
    s32 b;
    s32 tmp;

    tbl = _mapAlloc(100);
    for (i = 0; i < 25; i++) {
        tbl[i] = i;
    }
    for (i = 0; i < 50; i++) {
        a = rand() % 25;
        b = rand() % 25;
        tmp = tbl[a];
        tbl[a] = tbl[b];
        tbl[b] = tmp;
    }
    if (!evtGetValue(NULL, GSWF(5408))) {
        for (i = 0; i < 25; i++) {
            if (tbl[i] == 0) {
                tmp = tbl[0];
                tbl[0] = tbl[i];
                tbl[i] = tmp;
                break;
            }
        }
    }
    return EVT_RETURN_DONE;
}
