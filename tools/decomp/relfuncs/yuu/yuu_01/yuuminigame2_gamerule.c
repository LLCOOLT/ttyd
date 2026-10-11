// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// include: mario/mario.h
// include: pmario_sound.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// decl: typedef struct FuneWork { u32 flags; s32 phase; s32 coins; s32 result; s32 index; s32 state; f32 dist; Vec dir; s32 timer; f32 y; f32 x; s32 monteCount; EventEntry* viewEvent; } FuneWork;
// decl: s32 yuucounter_get_data(void);
// decl: void yuucounter_flag_on(s32 flag);
// decl: void partyKeyOff(void);
// decl: void partyKeyOn(void);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: BOOL marioChkSwirlPower(void);
// decl: void marioSetSwirlPower(s32 time, f32 speed, f32 angle);
// decl: extern s32 s_nametbl[];
// decl: extern s32 turn_tbl[];
// decl: extern s32 hoko_tbl[];
// proto: BOOL yuuminigame2_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, FuneWork* data);
BOOL yuuminigame2_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, FuneWork* data) {
    MarioWork* mario = marioGetPtr();
    Vec box[3];
    Mtx mtx;
    Vec pos;
    Vec tmp;
    Vec ofs;
    f32 angle;
    s32 i;
    s32 j;
    s32 rnd;

    if (data->index == 0x15) {
        if ((mario->position.x <= -700.0f && mario->position.z <= 0.0f) || yuucounter_get_data() < 0) {
            data->coins = yuucounter_get_data();
            marioKeyOff();
            partyKeyOff();
            yuucounter_flag_on(2);
            return TRUE;
        }
    }
    box[2] = mario->position;
    box[1] = mario->position;
    box[0] = mario->position;
    box[0].x -= 12.5f;
    box[2].x += 12.5f;
    while (data->index < 1 || data->index >= 5) {
        for (i = 1; i < 5; i++) {
            mapObjGetPos((const char*)s_nametbl[i], &pos);
            pos.y = mario->position.y;
            for (j = 0; j < 3; j++) {
                if (PSVECSquareDistance(&box[j], &pos) <= 3306.25f) {
                    tmp = mario->position;
                    if (tmp.x == pos.x && tmp.z == pos.z) {
                        tmp.x += 1.0f;
                    }
                    data->index = i;
                    marioKeyOff();
                    partyKeyOff();
                    mario->flags |= 0x200;
                    mario->flags |= 0x100;
                    data->state = 0;
                    PSVECSubtract(&tmp, &pos, &data->dir);
                    data->dir.y = 0.0f;
                    data->dist = PSVECMag(&data->dir);
                    PSVECNormalize(&data->dir, &data->dir);
                    data->timer = 120;
                    data->y = mario->position.y;
                    mario->dispFlags |= 0x100;
                    psndSFXOn_3D((const char*)0x8DB, &mario->position);
                    data->result--;
                    break;
                }
            }
            if (j < 3) {
                break;
            }
        }
        if (i < 5) {
            break;
        }
        {
            for (i = 5; i < 13; i++) {
                mapObjGetPos((const char*)s_nametbl[i], &pos);
                pos.y = mario->position.y;
                for (j = 0; j < 3; j++) {
                    if (PSVECSquareDistance(&box[j], &pos) <= 225.0f) {
                        if (!marioChkSwirlPower()) {
                            psndSFXOn_3D((const char*)0x8DC, &mario->position);
                            data->result--;
                        }
                        data->index = i;
                        marioSetSwirlPower(1000, 8.0f, hoko_tbl[data->index] - (45 - irand(91)));
                        mario->dispFlags |= 0x100;
                        break;
                    }
                }
                if (j < 3) {
                    break;
                }
            }
        }
        if (i < 13) {
            break;
        }
        break;
    }
    if (data->index != 0x15) {
    angle = mario->unk1A8 + turn_tbl[data->index];
    if (data->index >= 5 && data->index < 13) {
        if (!marioChkSwirlPower()) {
            data->index = 0x15;
            mario->dispFlags &= ~0x100;
            if (mario->unk1A8 >= -90.0f && mario->unk1A8 < 90.0f) {
                angle = 0.0f;
            } else {
                angle = 180.0f;
            }
        }
    } else if (data->index >= 1 && data->index < 5) {
        switch (data->state) {
            case 0:
                data->timer--;
                PSMTXRotRad(mtx, 'Y', 0.017453292f * turn_tbl[data->index]);
                PSMTXMultVec(mtx, &data->dir, &data->dir);
                data->dir.y = 0.0f;
                PSVECNormalize(&data->dir, &data->dir);
                PSVECScale(&data->dir, &ofs, data->timer >= 30 ? data->dist * ((data->timer - 30) / 90.0f) : 0.0f);
                mapObjGetPos((const char*)s_nametbl[data->index], &pos);
                PSVECAdd(&ofs, &pos, &ofs);
                mario->position.x = ofs.x;
                mario->position.z = ofs.z;
                mario->position.y = data->y - 30.0f * ((120 - data->timer) / 120.0f);
                if (data->timer <= 0) {
                    data->state++;
                    angle = 0.0f;
                    data->timer = 30;
                    mario->dispFlags &= ~0x100;
                    data->x = mario->position.x;
                }
                break;
            case 1:
                data->timer--;
                angle = 0.0f;
                mario->position.x = data->x + -100.0f * ((30 - data->timer) / 30.0f);
                mario->position.y = data->y - 30.0f;
                if (data->timer <= 0) {
                    data->state++;
                    data->timer = 30;
                }
                break;
            case 2:
                data->timer--;
                angle = 0.0f;
                mario->position.y = data->y - 30.0f * (data->timer / 30.0f);
                if (data->timer <= 0) {
                    data->index = 0x15;
                    marioKeyOn();
                    partyKeyOn();
                    mario->flags &= ~0x200;
                    mario->flags &= ~0x100;
                }
                break;
        }
    }
    mario->unk1AC = reviseAngle(angle);
    mario->unk1A8 = mario->unk1AC;
    }
    return FALSE;
}
