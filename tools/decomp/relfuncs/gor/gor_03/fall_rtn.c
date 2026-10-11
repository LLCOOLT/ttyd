// include: driver/camdrv.h
// include: memory.h
// include: string.h
// include: mario/mario.h
// include: driver/dispdrv.h
// include: pmario_sound.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct GMonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } GMonteSub;
// decl: typedef struct GMonte { u8 hidden; u8 state; s16 wait; s16 timer; u8 unk6[2]; GMonteSub sub; Vec vel; SlotWork* owner; } GMonte;
// decl: static GMonte* monte_p;
// decl: typedef struct GorYuuWork { s32 unk0; s32 unk4; s32 medals; } GorYuuWork;
// decl: extern GorYuuWork* yuwp;
// decl: int rand(void);
// decl: static void monte_disp(CameraId camera, void* param);
// decl: static BOOL get_monte_check(Vec* a, Vec* b);
// decl: static const Vec fall_pos0 = {-113.0f, 70.0f, 0.0f}; /* @place "slot_mess_01" */
// decl: static const Vec fall_vel0 = {0.0f, 10.0f, 0.0f}; /* @place "slot_mess_01" */
// proto: static USER_FUNC(fall_rtn);
static USER_FUNC(fall_rtn) {
    Vec pos;
    s32 done = 0;
    const char* sfx1;
    const char* sfx2;
    const char* sfx3;
    SlotWork* data;
    GMonte* m;
    s32 i;

    if (isFirstCall) {
        data = ((GoryuuWork*)event->lwData[0])->data;
        monte_p = _mapAlloc(data->monteCount * sizeof(GMonte));
        memset(monte_p, 0, data->monteCount * sizeof(GMonte));
        monte_p->owner = data;
        for (i = 0; i < monte_p->owner->monteCount; i++) {
            GMonteSub* sub = &monte_p[i].sub;
            Vec pos = fall_pos0;
            f32 s;
            f32 c;
            f32 ofs;

            pos.z = ((f32*)montemedalzpos)[monte_p->owner->nowSlot];
            sub->pos = pos;
            ofs = ((i & 1) * 2.0f - 1.0f) * ((rand() % 101) / 10.0f);
            sub->pos.z += ofs;
            sub->scale = 1.0f;
            s = 0.0f;
            c = 0.0f;
            movePos(&s, &c, 2.0f + (rand() % 300) / 100.0f, 270.0f - 3.0f * ofs);
            {
                Vec vel = fall_vel0;

                vel.x = s;
                vel.z = c;
                monte_p[i].vel = vel;
            }
            monte_p[i].wait = ((rand() % 700 + 100) * 60) / 1000;
        }
    }
    sfx2 = "SFX_EVT_GAME_MONTE_COUNT1";
    sfx1 = "SFX_EVT_GAME_MONTE_LEAPED1";
    sfx3 = sfx2;
    for (i = 0; i < monte_p->owner->monteCount; i++) {
        m = &monte_p[i];
        switch (m->state) {
            case 0:
                if (m->wait != 0) {
                    m->wait--;
                } else {
                    m->state++;
                }
                break;
            case 1:
                PSVECAdd(&m->sub.pos, &m->vel, &m->sub.pos);
                m->vel.y -= 0.81667f;
                if (m->sub.pos.y <= 0.0f) {
                    m->sub.pos.y = 0.0f;
                    psndSFXOn_3D(sfx1, &m->sub.pos);
                    if (__fabs(m->vel.y) <= 4.0) {
                        m->state++;
                        m->timer = 300;
                    } else {
                        m->vel.y *= -(0.5f + (rand() % 21) / 100.0f);
                        m->vel.x = 0.0f;
                        m->vel.z = 0.0f;
                    }
                }
                if (get_monte_check(&m->sub.pos, &marioGetPtr()->position) == TRUE) {
                    psndSFXOn_3D(sfx2, &m->sub.pos);
                    if (yuwp->medals < 99999) {
                        yuwp->medals++;
                    }
                    m->hidden = 1;
                    m->state = 3;
                }
                break;
            case 2:
                m->timer--;
                if (m->timer == 0) {
                    m->hidden = 1;
                    m->state++;
                }
                if (m->timer < 60) {
                    if (m->timer & 2) {
                        m->sub.pos.y = 0.0f;
                    } else {
                        m->sub.pos.y = -1000.0f;
                    }
                }
                pos = m->sub.pos;
                pos.y = 0.0f;
                if (get_monte_check(&pos, &marioGetPtr()->position) == TRUE) {
                    psndSFXOn_3D(sfx3, &m->sub.pos);
                    if (yuwp->medals < 99999) {
                        yuwp->medals++;
                    }
                    m->hidden = 1;
                    m->state = 3;
                }
                break;
            case 3:
                done++;
                break;
        }
    }
    if (done < monte_p->owner->monteCount) {
        dispEntry(CAMERA_3D, 0.0f, 1, monte_disp, monte_p);
        return EVT_RETURN_BLOCK;
    }
    monte_p->owner->monteCount = 0;
    monte_p->owner->monteEvt = NULL;
    _mapFree(monte_p);
    return EVT_RETURN_DONE;
}
