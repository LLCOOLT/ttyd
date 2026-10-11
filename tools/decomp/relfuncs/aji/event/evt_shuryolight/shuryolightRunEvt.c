// include: driver/npcdrv.h
// include: driver/animdrv.h
// decl: typedef struct ShuryoLight { NpcEntry* npc; const char** anims; s32 status; s32 group; s32 shape; } ShuryoLight;
// decl: typedef struct ShuryoWork { s32 powerEvt; s32 headEvt; s32 tueEvt; ShuryoLight lights[5]; } ShuryoWork;
// decl: static ShuryoWork* slhp;
// proto: static s32 shuryolightRunEvt(s32* code, s32 id);
static s32 shuryolightRunEvt(s32* code, s32 id) {
    if (evtCheckID(id)) {
        evtDeleteID(id);
    }
    return evtEntryType(code, 0, 0, 0)->eventId;
}
