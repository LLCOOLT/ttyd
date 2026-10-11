// decl: typedef struct MajoSortEntry { s32 id; s32 value; } MajoSortEntry;
// proto: USER_FUNC(majo3_sort);
USER_FUNC(majo3_sort) {
    MajoSortEntry tbl[3];
    MajoSortEntry tmp1;
    MajoSortEntry tmp3;
    MajoSortEntry tmp2;
    s32 i;

    for (i = 0; i < 3; i++) {
        tbl[i].id = event->lwData[3 + i];
        tbl[i].value = event->lwData[i];
    }
    if (tbl[0].value < tbl[1].value) {
        tmp1 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp1;
    }
    if (tbl[1].value < tbl[2].value) {
        tmp2 = tbl[1];
        tbl[1] = tbl[2];
        tbl[2] = tmp2;
    }
    if (tbl[0].value < tbl[1].value) {
        tmp3 = tbl[0];
        tbl[0] = tbl[1];
        tbl[1] = tmp3;
    }
    for (i = 0; i < 3; i++) {
        event->lwData[i] = tbl[i].id;
    }
    return EVT_RETURN_DONE;
}
