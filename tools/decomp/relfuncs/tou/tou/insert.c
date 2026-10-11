// proto: static void insert(s32* list, s32 num, s32 from, s32 to);
static void insert(s32* list, s32 num, s32 from, s32 to) {
    s32 i;

    if (from < to) {
        s32 tmp = list[from];
        for (i = from; i < to; i++) {
            list[i] = list[i + 1];
        }
        list[to] = tmp;
    } else {
        s32 tmp = list[from];
        for (i = from; i > to; i--) {
            list[i] = list[i - 1];
        }
        list[to] = tmp;
    }
}
