// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// include: driver/hitdrv.h
// include: string.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct HikokiWork { u32 flags; s32 phase; s32 coins; s32 result; s32 monteCount; EventEntry* viewEvent; } HikokiWork;
// decl: s32 yuucounter_get_data(void);
// decl: void yuucounter_flag_on(s32 flag);
// decl: void partyKeyOff(void);
// proto: BOOL yuuminigame1_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, HikokiWork* data);
BOOL yuuminigame1_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, HikokiWork* data) {
    MarioWork* mario = marioGetPtr();

    if (mario->hitobjStandOn != NULL && (u16)((mario->trigFlags & 1) ? mario->prevMotionId : mario->currMotionId) != 0x18) {
        data->result = 1;
        data->coins = yuucounter_get_data();
        if (!strcmp("A_dai_01", hitGetName(mario->hitobjStandOn))) {
            data->result = 2;
        }
        if (!strcmp("A_dai_02", hitGetName(mario->hitobjStandOn))) {
            data->result = 2;
        }
        if (!strcmp("A_dai_03", hitGetName(mario->hitobjStandOn))) {
            data->result = 2;
        }
        if (!strcmp("A_dai_04", hitGetName(mario->hitobjStandOn))) {
            data->result = 3;
        }
        if (!strcmp("A_dai_05", hitGetName(mario->hitobjStandOn))) {
            data->result = 5;
        }
        if (!strcmp("A_ground_02", hitGetName(mario->hitobjStandOn))) {
            data->result = -5;
        }
        if (!strcmp("A_ground_05", hitGetName(mario->hitobjStandOn))) {
            data->result = -5;
        }
        if (!strcmp("A_ground_03", hitGetName(mario->hitobjStandOn))) {
            data->result = -10;
        }
        if (!strcmp("A_ground_06", hitGetName(mario->hitobjStandOn))) {
            data->result = -15;
        }
        if (!strcmp("A_ground_04", hitGetName(mario->hitobjStandOn))) {
            data->result = -20;
        }
        marioKeyOff();
        partyKeyOff();
        yuucounter_flag_on(2);
        return TRUE;
    }
    return FALSE;
}
