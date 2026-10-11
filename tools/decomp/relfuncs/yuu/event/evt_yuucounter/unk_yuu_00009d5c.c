// include: dolphin/os.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// proto: USER_FUNC(unk_yuu_00009d5c);
USER_FUNC(unk_yuu_00009d5c) {
    s32* args = event->args;
    BOOL on = evtGetValue(event, args[0]);
    u32 mask = evtGetValue(event, args[1]);
    YuuCounterWork* wp = _wp;

    if (on) {
        wp->dispFlags |= mask;
    } else {
        wp->dispFlags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
