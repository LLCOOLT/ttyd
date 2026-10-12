// include: driver/camdrv.h
// include: driver/casedrv.h
// include: memory.h
// include: string.h
// include: system.h
// include: pmario_sound.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// decl: #define SLOTGARA ((s32(*)[3][8])slotgara)
// decl: typedef struct GMonteSub { s32 unk0; Vec pos; f32 scale; u8 unk14[0x38 - 0x14]; } GMonteSub;
// decl: typedef struct GMonte { u8 hidden; u8 state; s16 wait; s16 timer; u8 unk6[2]; GMonteSub sub; Vec vel; SlotWork* owner; } GMonte;
// decl: static GMonte* monte_p;
// decl: void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
// decl: void mapPlayAnimationLv(const char* name, s32 a, s32 b);
// decl: void goryuugijo_upsidewindow_disp_sub(s32 slot, s32 reel);
// decl: void goryuugijo_upsidewindow_dispoff_sub(s32 slot, s32 reel);
// decl: s32 slot_rotate_sub(GoryuuWork* wp, SlotWork* data, s32 reel);
// decl: void slot_neon_sub(GoryuuWork* wp, SlotWork* data);
// proto: void goryuugijo_main_slot(EventEntry* event, BOOL isFirstCall);
void goryuugijo_main_slot(EventEntry* event, BOOL isFirstCall) {
    GoryuuWork* wp = (GoryuuWork*)event->lwData[0];
    SlotWork* data = wp->data;
    s32 r;
    const char* sfx;
    s32 dir;
    s32 i;
    s32 j;
    s32 k;
    s32 count;
    s32 press;
    CaseSetup setup;
    s32 tbl[3][3];
    s32 gara[3];
    s32 gara2[3];

    switch (data->phase) {
        case 1:
            data->cursor = 0;
            data->counter = 0;
            data->neonCount = 0;
            data->wait[0] = data->wait[1] = data->wait[2] = 0;
            data->extra[0] = data->extra[1] = data->extra[2] = 0;
            data->state[0] = data->state[1] = data->state[2] = 1;
            data->speed[0] = data->speed[1] = data->speed[2] = 0.0f;
            data->flags &= ~2;
            data->flags &= ~4;
            data->phase++;
            break;
        case 2:
            slot_neon_sub(wp, data);
            if (data->counter >= 15) {
                data->counter = 0;
                data->phase++;
                data->sfxId = ((s32 (*)(const char*))psndSFXOn)("SFX_EVT_GAME_SLOT_ROUND1");
            } else {
                data->counter++;
                data->reberAngle += 4.0f;
                mapObjRotate((const char*)drumname[data->nowSlot * 17 + 3], 0.0f, 0.0f, data->reberAngle);
            }
            break;
        case 3:
            slot_neon_sub(wp, data);
            if (data->counter <= 6) {
                if (data->counter >= 6) {
                    data->reberAngle = 0.0f;
                } else {
                    data->reberAngle -= 10.0f;
                }
                mapObjRotate((const char*)drumname[data->nowSlot * 17 + 3], 0.0f, 0.0f, data->reberAngle);
                data->counter++;
            }
            if (data->state[data->cursor] != 2 || (keyGetDirRep(0) & 0xC000)) {
                if (data->state[data->cursor] != 2) {
                    dir = 1;
                } else {
                    u32 key = keyGetDirRep(0);

                    dir = 1;
                    if (key & 0x4000) {
                        dir = -1;
                    }
                }
                for (i = 0; i < 3; i++) {
                    data->cursor += dir;
                    if (data->cursor < 0) {
                        data->cursor = 2;
                    } else if (data->cursor > 2) {
                        data->cursor = 0;
                    }
                    if (data->state[data->cursor] == 2) {
                        break;
                    }
                }
            }
            sfx = (0, "SFX_EVT_GAME_SLOT_STOP1");
            count = 0;
            for (j = 0; j < 3; j++) {
                if (data->state[j] == 0) {
                    count++;
                    continue;
                }
                if (j == data->cursor) {
                    switch (j) {
                        case 0:
                            if (keyGetButtonTrg(0) & 0x100) {
                                press = 1;
                            } else {
                                press = 0;
                            }
                            break;
                        case 1:
                            if (keyGetButtonTrg(0) & 0x100) {
                                press = 1;
                            } else {
                                press = 0;
                            }
                            break;
                        case 2:
                            if (keyGetButtonTrg(0) & 0x100) {
                                press = 1;
                            } else {
                                press = 0;
                            }
                            break;
                    }
                } else {
                    press = 0;
                }
                if (press && data->state[j] == 2) {
                    data->state[j] = 3;
                    if (data->flags & 2) {
                        data->stopCount[j] = 0;
                    } else {
                        data->stopCount[j] = irand(2);
                    }
                    psndSFXOn(sfx);
                }
                count += slot_rotate_sub(wp, data, j);
            }
            if (count == 3) {
                for (i = 0; i < 3; i++) {
                    goryuugijo_upsidewindow_disp_sub(data->nowSlot, i);
                }
                mapPlayAnimationLv((const char*)drumname[data->nowSlot * 17 + 15], 0, 0);
                data->counter = 0;
                data->phase++;
            }
            break;
        case 4:
            if (data->counter == 0) {
                for (i = 0; i < 3; i++) {
                    gara[i] = SLOTGARA[data->nowSlot][i][(s32)(data->angle[data->nowSlot][i] / 45.0f)];
                }
                if (gara[0] == gara[1] && gara[1] == gara[2]) {
                    data->phase = 6;
                    break;
                }
                if (!(data->flags & 4)) {
                    data->phase = 6;
                    break;
                }
                count = 0;
                for (i = 0; i < 3; i++) {
                    if (data->face[data->nowSlot][i] == gara[i]) {
                        count++;
                    }
                }
                if (count < 2) {
                    data->phase = 6;
                    break;
                }
            }
            if (data->counter == 0 || data->counter == 18 || data->counter == 36) {
                for (i = 0; i < 3; i++) {
                    goryuugijo_upsidewindow_disp_sub(data->nowSlot, i);
                }
            }
            if (data->counter == 9 || data->counter == 27 || data->counter == 45) {
                for (i = 0; i < 3; i++) {
                    goryuugijo_upsidewindow_dispoff_sub(data->nowSlot, i);
                }
            }
            if (data->counter == 45) {
                for (j = 0; j < 3; j++) {
                    s32 f = data->angle[data->nowSlot][j] / 45.0f;

                    for (k = 0; k < 3; k++) {
                        tbl[k][j] = SLOTGARA[data->nowSlot][j][(f + k - 1) & 7];
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (tbl[1][i] != data->face[data->nowSlot][i]) {
                        r = irand(2);
                        for (k = 0; k < 2; k++) {
                            r = (r + 1) & 1;
                            switch (r) {
                                case 0:
                                    if (data->face[data->nowSlot][i] == tbl[0][i] ||
                                        !(data->face[data->nowSlot][i] == tbl[0][i] || tbl[2][i] == data->face[data->nowSlot][i])) {
                                        if (data->face[data->nowSlot][i] == 0) {
                                            data->stopCount[i] = 1;
                                            data->extra[i] = 1;
                                            data->speed[i] = -1.40625f;
                                        } else {
                                            data->stopCount[i] = 6;
                                            if (data->face[data->nowSlot][i] == 2) {
                                                data->stopCount[i] += 8;
                                            }
                                            data->extra[i] = 0;
                                            data->speed[i] = 1.40625f;
                                        }
                                        data->state[i] = 4;
                                        k = 1;
                                    }
                                    break;
                                case 1:
                                    if (tbl[2][i] == data->face[data->nowSlot][i] ||
                                        !(data->face[data->nowSlot][i] == tbl[0][i] || tbl[2][i] == data->face[data->nowSlot][i])) {
                                        if (data->face[data->nowSlot][i] == 0) {
                                            data->stopCount[i] = 0;
                                            data->extra[i] = 0;
                                            data->speed[i] = 1.40625f;
                                        } else {
                                            data->stopCount[i] = 7;
                                            if (data->face[data->nowSlot][i] == 2) {
                                                data->stopCount[i] += 8;
                                            }
                                            data->extra[i] = 1;
                                            data->speed[i] = -1.40625f;
                                        }
                                        data->state[i] = 4;
                                        k = 1;
                                    }
                                    break;
                            }
                        }
                    }
                }
                data->phase++;
            }
            data->counter++;
            break;
        case 5:
            press = 0;
            for (i = 0; i < 3; i++) {
                if (data->state[i] == 0) {
                    press++;
                } else {
                    press += slot_rotate_sub(wp, data, i);
                }
            }
            if (press == 3) {
                data->counter = 0;
                data->phase++;
            }
            break;
        case 6:
            for (i = 0; i < 3; i++) {
                gara2[i] = SLOTGARA[data->nowSlot][i][(s32)(data->angle[data->nowSlot][i] / 45.0f)];
            }
            if (gara2[0] == gara2[1] && gara2[1] == gara2[2]) {
                data->counter = 0;
                data->phase++;
                psndSFXOn("SFX_EVT_GAME_SLOT_SUCCESS1");
                switch (gara2[0]) {
                    case 0:
                        data->monteCount = 3;
                        break;
                    case 1:
                        data->monteCount = 15;
                        break;
                    case 2:
                        data->monteCount = 100;
                        break;
                }
                caseDelete(data->caseId[0]);
                caseDelete(data->caseId[1]);
                data->flags |= 1;
                mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[2], 1, 0);
                data->flags |= 8;
            } else {
                data->phase = 11;
            }
            psndSFXOff(data->sfxId);
            break;
        case 7:
            if (data->counter >= 48) {
                data->counter = 0;
                data->phase++;
            }
            data->counter++;
            break;
        case 8:
            if (data->counter >= 36) {
                data->counter = 19;
                data->phase++;
            }
            data->counter++;
            break;
        case 9:
            if (data->counter >= 19) {
                data->counter = 0;
                if (data->monteEvt == NULL) {
                    data->monteEvt = evtEntry(slot_fall_monte, 0, 0);
                    data->monteEvt->lwData[0] = event->lwData[0];
                }
                data->phase++;
            } else {
                data->counter++;
            }
            break;
        case 10:
            if (data->monteEvt == NULL || !evtCheckID(data->monteEvt->eventId)) {
                mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[2], 2, 0);
                data->flags &= ~8;
                mapPlayAnimationLv((const char*)drumname[data->nowSlot * 17 + 15], 0, 0);
                data->counter = 0;
                data->monteEvt = NULL;
                data->phase++;
            } else {
                data->counter++;
            }
            break;
        case 11:
            if (data->monteEvt != NULL) {
                monte_p->owner->monteCount = 0;
                _mapFree(monte_p);
                evtDeleteID(data->monteEvt->eventId);
                data->monteEvt = NULL;
            }
            data->counter = 0;
            data->neonCount = 0;
            data->phase = 0;
            data->wait[0] = data->wait[1] = data->wait[2] = 0;
            data->extra[0] = data->extra[1] = data->extra[2] = 0;
            if (data->flags & 1) {
                data->flags &= ~1;
                for (i = 0; i < 2; i++) {
                    setup.activeConditionId = 0x8009;
                    setup.hitObjName = DRUMNAME[i].anim;
                    setup.swFlag = 0;
                    setup.activeFunc = NULL;
                    setup.evtCode = (void*)slotevttbl[i];
                    setup.priority = 0;
                    memcpy(setup.lwData, event->lwData, sizeof(setup.lwData));
                    data->caseId[i] = caseEntry(&setup);
                }
            }
            if (data->flags & 8) {
                mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[2], 2, 0);
                data->flags &= ~8;
                mapPlayAnimationLv((const char*)drumname[data->nowSlot * 17 + 15], 0, 0);
            }
            break;
    }
}
