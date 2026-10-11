// include: evt/evt_npc.h
// include: driver/npcdrv.h
// include: stdlib.h
// decl: typedef struct DigAnim { const char* name; u32 mask; s32 anim; } DigAnim;
// decl: #define ANIM_TBL ((DigAnim*)anim_tbl)
// decl: static s32 work[1];
// decl: #define DIG_WP ((s32*)wp[0])
// decl: s32 EXIGetType(s32 chan, u32 dev, u32* type);
// proto: USER_FUNC(evt_action_sub);
USER_FUNC(evt_action_sub) {
    s32* args = event->args;
    s32 idx;
    u32* maskp;
    u32 mask;
    s32 n;
    s32 k;
    s32 i;
    s32 bit;
    const char* name;
    u32 type;

    rand();
    do {
        idx = (u32)rand() % 48;
    } while (evtNpcNameToPtr_NoAssert(event, ANIM_TBL[idx].name) != NULL);
    maskp = &ANIM_TBL[idx].mask;
    mask = *maskp;
    n = 0;
    for (i = 0; i < 6; i++) {
        if ((1 << i) & mask) {
            n++;
        }
    }
    *maskp = mask;
    k = rand() % n;
    for (i = 0; i < 6; i++) {
        if ((1 << i) & *maskp) {
            if (--k < 0) {
                break;
            }
        }
    }
    name = ANIM_TBL[idx].name;
    bit = 1 << i;
    EXIGetType(0, 2, &type);
    if (type != 0x05070000) {
        evtSetValue(event, *args++, (s32)npcGetTribe(name)->modelName);
        evtSetValue(event, *args++, (s32)name);
    } else {
        evtSetValue(event, *args++, (s32)"a_mario");
        evtSetValue(event, *args++, (s32)"\202\311\202\271\203}\203\212\203I\202Q");
    }
    evtSetValue(event, *args++, bit);
    evtSetValue(event, *args++, anim_tbl[idx * 3 + 2]);
    return EVT_RETURN_DONE;
}
