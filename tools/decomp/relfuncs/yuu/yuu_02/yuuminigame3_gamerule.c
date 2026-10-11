// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct RollWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; EventEntry* jumpEvent; Vec pos; s32 monteCount; EventEntry* viewEvent; } RollWork;
// decl: typedef struct MonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } MonteSub;
// decl: typedef struct Monte { u8 hidden; u8 unk1; s16 num; u8 state; u8 unk5[3]; MonteSub sub; MiniGameWork* wp; } Monte;
// decl: typedef struct MonteTable { f32 x0; f32 x1; f32 z0; f32 z1; s32 num; s32 type; } MonteTable;
// decl: static void* yuunpc_wp;
// decl: static Monte* monte_p; /* unk_yuu_bss00000004 */
// decl: static Monte* icon_monte_p;
// decl: s32 yuucounter_get_data(void);
// decl: void yuucounter_flag_on(s32 flag);
// decl: void partyKeyOff(void);
// decl: extern s32 yuu_02_jumpret[];
// decl: extern Vec fukkipoint[];
// proto: BOOL yuuminigame3_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, RollWork* data);
BOOL yuuminigame3_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, RollWork* data) {
    MarioWork* mario = marioGetPtr();

    if (!(data->flags & 2) && mario->position.y <= -50.0f) {
        data->flags |= 2;
        data->jumpEvent = evtEntry(yuu_02_jumpret, 0, 0);
        data->jumpEvent->lwData[0] = (s32)fukkipoint[data->index].x + (fukkipoint[data->index].z >= 0.0f ? 5 : -5);
        data->jumpEvent->lwData[1] = (s32)fukkipoint[data->index].y + 200;
        data->jumpEvent->lwData[2] = (s32)fukkipoint[data->index].z;
        data->jumpEvent->lwData[3] = (s32)fukkipoint[data->index].y;
        data->result--;
    }
    if (!(data->flags & 2)) {
        if (mario->position.z * fukkipoint[data->index + 1].z >= 0.0f && mario->position.y >= fukkipoint[data->index + 1].y - 1.0f) {
            if ((mario->position.z >= 0.0f && data->pos.x < fukkipoint[data->index + 1].x && mario->position.x >= fukkipoint[data->index + 1].x) ||
                (mario->position.z < 0.0f && data->pos.x > fukkipoint[data->index + 1].x && mario->position.x <= fukkipoint[data->index + 1].x)) {
                if (data->index < 14) {
                    data->index++;
                }
                icon_monte_p->hidden = 1;
            }
        }
        if (mario->position.z * fukkipoint[data->index].z >= 0.0f) {
            if ((mario->position.z < 0.0f && data->pos.x < fukkipoint[data->index].x && mario->position.x >= fukkipoint[data->index].x) ||
                (mario->position.z >= 0.0f && data->pos.x > fukkipoint[data->index].x && mario->position.x <= fukkipoint[data->index].x)) {
                if (data->index > 0) {
                    data->index--;
                }
                icon_monte_p->hidden = 0;
            }
        }
        data->pos = mario->position;
        if (yuucounter_get_data() < 0 || data->index >= 13) {
            data->coins = yuucounter_get_data();
            data->index = 0;
            marioKeyOff();
            partyKeyOff();
            yuucounter_flag_on(2);
            icon_monte_p->hidden = 1;
            return TRUE;
        }
    } else {
        data->pos = mario->position;
        if (!evtCheckID(data->jumpEvent->eventId)) {
            data->flags &= ~2;
        }
    }
    return FALSE;
}
