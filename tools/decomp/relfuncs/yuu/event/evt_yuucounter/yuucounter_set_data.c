// include: dolphin/os.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static void* yuunpc_wp;
// decl: static YuuCounterWork* _wp;
// proto: void yuucounter_set_data(s32 data);
void yuucounter_set_data(s32 data) {
    if (_wp == NULL) {
        return;
    }
    _wp->data = data;
}
