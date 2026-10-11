// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// include: system.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;
// decl: s32 yuucounter_get_data(void);
// decl: void yuucounter_flag_on(s32 flag);
// decl: void partyKeyOff(void);
// decl: extern s32 ryushi_event[];
// decl: #define REVISE360(a) ((3600.0f + (a)) - (s32)((3600.0f + (a)) / 360.0f) * 360)
// proto: BOOL yuuminigame4_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, SlitWork* data);
BOOL yuuminigame4_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, SlitWork* data) {
    MarioWork* mario = marioGetPtr();
    EventEntry* ev;
    f32 speed;

    data->timer--;
    switch (data->state) {
        case 0:
            if (data->timer == 0) {
                if (irand(2)) {
                    data->state = 1;
                    ev = evtEntryType(ryushi_event, 0, 0, 0);
                    ev->lwData[0] = (s32)wp;
                    ev->lwData[1] = 1;
                } else {
                    data->state = 5;
                    ev = evtEntryType(ryushi_event, 0, 0, 0);
                    ev->lwData[0] = (s32)wp;
                    ev->lwData[1] = 0;
                }
                data->timer = 60;
            }
            break;
        case 1:
            if (data->timer == 0) {
                data->state = 2;
                data->timer = 60;
            }
        case 2:
            if (data->timer == 0) {
                data->state = 3;
                data->timer = (irand(2001) + 3000) * 60 / 1000;
            }
            break;
        case 3:
            if (data->timer == 0) {
                data->state = 4;
                data->timer = 48;
            }
            break;
        case 4:
            if (data->timer == 0) {
                data->state = 0;
                data->timer = (irand(3901) + 100) * 60 / 1000;
                evtSetValue(event, GW(0), 1);
            }
            break;
        case 5:
            if (data->timer == 0) {
                data->state = 6;
                data->timer = 60;
            }
            break;
        case 6:
            if (data->timer == 0) {
                data->state = 7;
                data->timer = (irand(2001) + 3000) * 60 / 1000;
            }
            break;
        case 7:
            if (data->timer == 0) {
                data->state = 8;
                data->timer = 48;
            }
            break;
        case 8:
            if (data->timer == 0) {
                data->state = 0;
                data->timer = (irand(3901) + 100) * 60 / 1000;
                evtSetValue(event, GW(0), 1);
            }
            break;
    }
    switch (data->state) {
        case 0:
            break;
        case 1:
        case 2:
            data->rot1 += 36.0f * (120.0f - (data->timer - 1)) / 120.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 3:
            data->rot1 += 36.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 4:
            data->rot1 += 36.0f * (data->timer - 1) / 48.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 5:
        case 6:
            data->rot2 += 36.0f * (120.0f - (data->timer - 1)) / 120.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
        case 7:
            data->rot2 += 36.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
        case 8:
            data->rot2 += 36.0f * (data->timer - 1) / 48.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
    }
    if (mario->position.x < 1500.0f) {
        speed = 0.0f;
        switch (data->state) {
            case 2:
            case 3:
            case 4:
                if (mario->dispFlags & 0x1000000) {
                    if (mario->flags & 0x100000) {
                        speed = 0.0f;
                    } else {
                        speed = 0.0f;
                    }
                } else {
                    speed = 2.9166667f;
                }
                break;
            case 6:
            case 7:
            case 8:
                if (mario->dispFlags & 0x1000000) {
                    if (mario->flags & 0x100000) {
                        speed = -0.0f;
                    } else {
                        speed = -0.0f;
                    }
                } else {
                    speed = -2.9166667f;
                }
                break;
        }
        switch (data->state) {
            case 2:
            case 6:
                speed = speed * (60 - data->timer) / 60.0f;
                break;
        }
        mario->unk174.z += speed;
    }
    if (mario->position.y <= -100.0f || mario->position.x >= 1500.0f) {
        if (mario->position.y <= -100.0f) {
            data->coins = 701;
            yuucounter_flag_on(1);
        } else {
            data->coins = yuucounter_get_data();
        }
        data->state = 0;
        data->timer = (irand(3901) + 100) * 60 / 1000;
        marioKeyOff();
        partyKeyOff();
        yuucounter_flag_on(2);
        return TRUE;
    }
    return FALSE;
}
