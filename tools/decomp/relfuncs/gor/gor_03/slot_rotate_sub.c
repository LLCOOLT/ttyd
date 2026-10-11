// include: driver/camdrv.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// decl: void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
// proto: s32 slot_rotate_sub(GoryuuWork* wp, SlotWork* data, s32 reel);
s32 slot_rotate_sub(GoryuuWork* wp, SlotWork* data, s32 reel) {
    s32 stopped = 0;
    f32 angle = data->angle[data->nowSlot][reel];
    f32 speed = data->speed[reel];
    s32 face = (s32)angle / 45.0f;
    s32 cross;
    f32 d;

    if (speed > 0.0f) {
        face = (face + 1) & 7;
        d = 45.0f * face - angle;
        if (d < 0.0f) {
            d += 360.0f;
        }
        if (d <= speed) {
            cross = 1;
        } else {
            cross = 0;
        }
    } else {
        d = 45.0f * face - angle;
        if (d > 0.0f) {
            d -= 360.0f;
        }
        if (d > speed) {
            cross = -1;
        } else {
            cross = 0;
        }
    }
    if ((data->state[reel] == 3 || data->state[reel] == 4) && cross != 0) {
        if (data->stopCount[reel] != 0) {
            if (data->state[reel] == 4) {
                if (data->wait[reel] == 0) {
                    if (data->extra[reel] != 0) {
                        data->extra[reel]--;
                        data->wait[reel] = 0;
                    } else {
                        data->wait[reel] = 18;
                    }
                } else {
                    data->wait[reel]--;
                }
            }
            if (data->wait[reel] != 0) {
                goto rotate;
            }
            data->stopCount[reel]--;
        } else {
            stopped = 1;
            data->state[reel] = 0;
            data->angle[data->nowSlot][reel] = 45.0f * face;
            goto rotate;
        }
    }
    data->angle[data->nowSlot][reel] += data->speed[reel];
    if (data->angle[data->nowSlot][reel] >= 360.0f) {
        data->angle[data->nowSlot][reel] -= 360.0f;
    }
    if (data->angle[data->nowSlot][reel] < 0.0f) {
        data->angle[data->nowSlot][reel] += 360.0f;
    }
rotate:
    mapObjRotate(DRUMNAME[data->nowSlot].drum[reel], 0.0f, 0.0f, data->angle[data->nowSlot][reel]);
    return stopped;
}
