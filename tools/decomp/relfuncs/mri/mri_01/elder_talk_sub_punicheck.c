// include: driver/swdrv.h
// decl: void* puniGetPunigp(void);
// decl: void* puniGetPunidat(void);
// decl: void puniswGetindex(s32 flag, s32 index, s32* a, s32* b);
// decl: void puniswTrapGetindex(s32 index, s32* trap);
// proto: USER_FUNC(elder_talk_sub_punicheck);
USER_FUNC(elder_talk_sub_punicheck) {
    s32* args = event->args;
    s32* punigp = puniGetPunigp();
    s32 i;
    s32 traps = 0;
    s32 others = 0;
    s32 result;
    s32 c[5];
    s32 trap;
    s32 puni;

    for (i = 1; i < 103; i++) {
        puniGetPunidat();
        if (i == 1 && swGet(0xB14)) {
            continue;
        }
        puniswGetindex(LSW(0), i - 1, &puni, c);
        puniswTrapGetindex(i, &trap);
        if (trap != 0) {
            traps++;
        } else if (puni != 0 && puni != punigp[0x328 / 4]) {
            others++;
        }
    }
    result = 1;
    if (others != 0) {
        result = 0;
    } else if (traps != 0) {
        result = 2;
    }
    evtSetValue(event, args[0], result);
    return EVT_RETURN_DONE;
}
