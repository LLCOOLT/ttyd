// include: dolphin/os.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// proto: s32 yuucounter_get_data(void);
s32 yuucounter_get_data(void) {
    if (_wp == NULL) {
        return 0;
    }
    return _wp->data;
}
