#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "manager/evtmgr_cmd.h"
#include "dolphin/os.h"
#include "driver/icondrv.h"
#include "driver/dispdrv.h"
#include "string.h"
#include "driver/mapdrv.h"
#include "driver/effdrv.h"
#include "driver/camdrv.h"
#include "mario/mariost.h"
#include "dolphin/mtx.h"
#include "driver/mobjdrv.h"
#include "driver/fadedrv.h"
#include "system.h"

static OSTime wwstart;
void statusWinForceClose(void);
void statusWinForceCloseClear(void);
static s32 x_flag_data[2];
static void lecture_button_disp(CameraId camera, void* param);
typedef struct LectButtonDisp { s32 unk0; Vec pos; } LectButtonDisp;
typedef struct LectButton { u8 flags; u8 seq; u8 pad_2[0x8 - 0x2]; LectButtonDisp disp; u8 pad_18[0x40 - 0x18]; s16 iconId; s16 alpha; } LectButton;
static LectButton lbtn[2];
static inline void effitemget_cam_move(CameraEntry* camera, Vec ofs) { camera->presetPos = camera->cameraPos; camera->presetAt = camera->cameraAt; PSVECAdd(&camera->cameraPos, &ofs, &camera->storedPos); PSVECAdd(&camera->cameraAt, &ofs, &camera->storedAt); camera->startTimeA = gp->renderTime; camera->durationA = 0; camera->stateA = 3; camera->curveA = 11; }
void hitGrpFlagOn(const char* name, u32 flags);
static Vec daiv;
void unk_8009f9c8(void);
void motSlitCancel3(void);
BOOL marioRollKeyDisable(void);

USER_FUNC(evt_cam3d_evt_set_rel);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mario_set_pos);
static USER_FUNC(lect_map_cam_chg);
USER_FUNC(lect_set_systemlevel);
USER_FUNC(lect_test_systemlevel);
static USER_FUNC(bgm_start_wait);
static USER_FUNC(evt_nomal_cange);
static USER_FUNC(lect_push_r_check);
static USER_FUNC(evtflash);
static USER_FUNC(lect_slit_check);
static USER_FUNC(dai_moveti_get);
static USER_FUNC(dai_moveti_set);
static USER_FUNC(lect_mobj_hit_nasi);
static USER_FUNC(effitemget_busaiku);
static USER_FUNC(effitemget_open_ptr);
static USER_FUNC(effitemget_open);
static USER_FUNC(effitemgetchange_cam_ptr);
static USER_FUNC(effitemgetchange_cam);
static void lect_map_cam_chg_sub(MapObject* obj, s32 camId, BOOL siblings);
static USER_FUNC(lecture_button_set_pos);
static USER_FUNC(lecture_button_seq_wait);
static USER_FUNC(lecture_button_get_icon_id);
static USER_FUNC(lecture_button_set_seq);
static USER_FUNC(lecture_button_flag_on_off);
static USER_FUNC(lecture_button_set_alpha);
static USER_FUNC(lecture_button_set_icon_id);
static USER_FUNC(lecture_button_rtn);
static void lecture_button_disp(CameraId camera, void* param);
static USER_FUNC(x_flag_wait);
static USER_FUNC(x_flag_get);
static USER_FUNC(x_flag_add);
static USER_FUNC(x_flag_set);
static USER_FUNC(lect_status_on);
static USER_FUNC(lect_status_off);
static USER_FUNC(lect_mario_ido_sum);
static f32 lect_mario_ido_sub(f32 elapsed, f32 total, f32 end, f32 start);
extern s32 evt_cam3d_evt_set[];
extern s32 evt_cam_get_at[];
extern s32 evt_hit_bind_mapobj[];
extern s32 evt_hit_bind_update[];
extern s32 evt_key_get_buttontrg[];
extern s32 evt_mapobj_trans[];
extern s32 evt_mario_cont_onoff[];
extern s32 evt_mario_mov_pos2[];
extern s32 evt_mario_paper_plane[];
extern s32 evt_mario_set_pose[];
extern s32 evt_mario_wait_landon[];
extern s32 evt_msg_continue[];
extern s32 evt_msg_print[];
extern s32 evt_msg_print_add[];
extern s32 evt_msg_select[];
extern s32 evt_msg_toge[];
extern s32 evt_nonride_airport[];
extern s32 evt_npc_flag_onoff[];
extern s32 evt_npc_set_anim[];
extern s32 evt_npc_set_camid[];
extern s32 evt_npc_set_position[];
extern s32 evt_ride_airport[];
extern s32 evt_snd_sfxon_3d[];

__declspec(section ".data") u64 fd_evt_lect_tik_negone_one_374;
__declspec(section ".data") s32 fd_evt_lect_tik_neg_one_382[1];
__declspec(section ".data") s32 fd_evt_lect_tik___local_PI_383[1];
__declspec(section ".data") s32 fd_evt_lect_tik___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_evt_lect_tik_one_negone_373;
__declspec(section ".data") s32 fd_evt_lect_tik___local_PIO2_384[1];
__declspec(section ".data") s32 fd_evt_lect_tik_one_381[1];
__declspec(section ".data") u64 fd_evt_lect_tik_negone_one_360;
__declspec(section ".data") s32 fd_evt_lect_tik_neg_one_365[1];
__declspec(section ".data") s32 fd_evt_lect_tik___local_PI_366[1];
__declspec(section ".data") s32 fd_evt_lect_tik___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_evt_lect_tik_one_negone_359;
__declspec(section ".data") s32 fd_evt_lect_tik___local_PIO2_367[1];
__declspec(section ".data") s32 fd_evt_lect_tik_one_364[1];
s32 plane_majin_lecture_init[73];
s32 plane_majin_lecture[715];

static f32 lect_mario_ido_sub(f32 elapsed, f32 total, f32 end, f32 start) {
    f32 rem = total - elapsed;

    return (rem * end + elapsed * start) / total;
}

static USER_FUNC(lect_mario_ido_sum) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    s32 frames = evtGetValue(event, args[0]);
    s32 elapsed;

    if (isFirstCall) {
        wwstart = event->lifetime;
        evtSetFloat(event, LW(0), mario->position.x);
        evtSetFloat(event, LW(1), mario->position.y);
        evtSetFloat(event, LW(2), mario->position.z);
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)event->lifetime - (u32)wwstart));
    if (elapsed > frames) {
        elapsed = frames;
    }
    mario->position.x = lect_mario_ido_sub(elapsed, frames, evtGetFloat(event, LW(3)), evtGetFloat(event, LW(0)));
    mario->position.y = lect_mario_ido_sub(elapsed, frames, evtGetFloat(event, LW(4)), evtGetFloat(event, LW(1)));
    mario->position.z = lect_mario_ido_sub(elapsed, frames, evtGetFloat(event, LW(5)), evtGetFloat(event, LW(2)));
    if (elapsed >= frames) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(lect_status_off) {
    statusWinForceClose();
    return EVT_RETURN_DONE;
}

static USER_FUNC(lect_status_on) {
    statusWinForceCloseClear();
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_set) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    x_flag_data[index] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_add) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    x_flag_data[index] += evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_get) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], x_flag_data[index]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(x_flag_wait) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);

    if (value == x_flag_data[index]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static void lecture_button_disp(CameraId camera, void* param) {
    s32 i;

    for (i = 0; i < 2; i++) {
        LectButton* btn = &lbtn[i];
        LectButtonDisp* disp = &btn->disp;

        if (!(btn->flags & 1)) {
            f32 ofs;
            Vec pos;

            switch (btn->iconId) {
                case 0x75:
                case 0x76:
                case 0x77:
                case 0x78:
                case 0x79:
                case 0x7A:
                case 0x7B:
                case 0x7C:
                case 0x7D:
                    ofs = -15.0f;
                    break;
                default:
                    ofs = 0.0f;
                    break;
            }
            pos = disp->pos;
            pos.y += ofs;
            iconDispGxAlpha(&pos, 0x50, btn->iconId, btn->alpha, 1.0f);
        }
    }
}

static USER_FUNC(lecture_button_rtn) {
    LectButton* btn;
    s32 i;
    s32 done;

    if (isFirstCall) {
        memset(lbtn, 0, sizeof(lbtn));
        {
            Vec pos = {200.0f, -25.0f, 0.0f};

            for (i = 0; i < 2; i++) {
                lbtn[i].disp.pos = pos;
            }
        }
    }
    done = 0;
    for (i = 0; i < 2; i++) {
        btn = &lbtn[i];
        switch (btn->seq) {
            case 0:
                btn->iconId = 0x68;
                btn->seq = 1;
                break;
            case 2:
                btn->alpha += 7;
                if (btn->alpha >= 255) {
                    btn->alpha = 255;
                    btn->seq = 1;
                }
                break;
            case 3:
                btn->alpha -= 7;
                if (btn->alpha <= 0) {
                    btn->alpha = 0;
                    btn->seq = 1;
                }
                break;
            case 4:
                btn->flags |= 1;
                done++;
                break;
        }
    }
    if (done >= 2) {
        return EVT_RETURN_DONE;
    }
    dispEntry(CAMERA_2D, 0.0f, 1, lecture_button_disp, NULL);
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(lecture_button_set_icon_id) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    btn->iconId = value;
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_set_alpha) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    btn->alpha = value;
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_flag_on_off) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    u8 flag = evtGetValue(event, args[1]);

    s32 on = evtGetValue(event, args[2]);
    LectButton* btn = &lbtn[index];

    if (on) {
        btn->flags |= flag;
    } else {
        btn->flags &= ~flag;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_set_seq) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 value = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    btn->seq = value;
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_get_icon_id) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    LectButton* btn = &lbtn[index];

    evtSetValue(event, args[1], btn->seq);
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_seq_wait) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    s32 seq = evtGetValue(event, args[1]);
    LectButton* btn = &lbtn[index];

    if (btn->seq != seq) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(lecture_button_set_pos) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    LectButton* btn = &lbtn[index];

    btn->disp.pos = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}

static void lect_map_cam_chg_sub(MapObject* obj, s32 camId, BOOL siblings) {
    obj->field_0x4[1] = camId;
    if (obj->child != NULL) {
        lect_map_cam_chg_sub(obj->child, camId, TRUE);
    }
    if (siblings && obj->next != NULL) {
        lect_map_cam_chg_sub(obj->next, camId, TRUE);
    }
}

static USER_FUNC(lect_map_cam_chg) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 camId = evtGetValue(event, args[1]);
    MapObject* obj = mapGetMapObj(name);

    if (obj != NULL) {
        lect_map_cam_chg_sub(obj, camId, FALSE);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(effitemgetchange_cam) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 camId = evtGetValue(event, args[1]);

    ((s32*)effNameToPtr(name)->userdata)[14] = camId;
    return EVT_RETURN_DONE;
}

static USER_FUNC(effitemgetchange_cam_ptr) {
    s32* args = event->args;
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, args[0]);

    ((s32*)eff->userdata)[14] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(effitemget_open) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[8] = 1;
    return EVT_RETURN_DONE;
}

static USER_FUNC(effitemget_open_ptr) {
    EffectEntry* eff = (EffectEntry*)evtGetValue(event, event->args[0]);

    ((s32*)eff->userdata)[8] = 1;
    return EVT_RETURN_DONE;
}

static USER_FUNC(effitemget_busaiku) {
    s32 up = evtGetValue(event, event->args[0]);
    CameraEntry* camera = camGetPtr(4);
    Vec ofs;

    if (up) {
        ofs = (Vec){0.0f, 2016.0f, 0.0f};
    } else {
        ofs = (Vec){0.0f, -2016.0f, 0.0f};
    }
    effitemget_cam_move(camera, ofs);
    return EVT_RETURN_DONE;
}

static USER_FUNC(lect_mobj_hit_nasi) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj;
    s32 i;

    if (strcmp(name, "me") != 0) {
        mobj = mobjNameToPtr(name);
    } else {
        mobj = event->thisMapObj;
    }
    for (i = 0; i < 2; i++) {
        if (mobj->hitObj[i].name != NULL && strcmp(mobj->hitObj[i].name, "") != 0) {
            hitGrpFlagOn(mobj->hitObj[i].name, 1);
        }
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(dai_moveti_set) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    daiv = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}

static USER_FUNC(dai_moveti_get) {
    s32* args = event->args;

    evtSetFloat(event, args[0], daiv.x);
    evtSetFloat(event, args[1], daiv.y);
    evtSetFloat(event, args[2], daiv.z);
    return EVT_RETURN_DONE;
}

static USER_FUNC(lect_slit_check) {
    s32* args = event->args;

    if (marioGetPtr()->flags & 0x100000) {
        evtSetValue(event, args[0], TRUE);
    } else {
        evtSetValue(event, args[0], FALSE);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(evtflash) {
    if (isFirstCall) {
        event->userdata[2] = 0;
    }
    switch (event->userdata[2]) {
        case 0:
            fadeEntry(10, 40, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
            event->userdata[2]++;
        case 1:
            if (fadeIsFinish() != TRUE) {
                return EVT_RETURN_BLOCK;
            }
            event->userdata[0] = 60;
            event->savedTime = (s32)gp->renderTime;
            event->userdata[2]++;
            if (event->userdata[0] == 0) {
                event->userdata[2]++;
            }
            return EVT_RETURN_BLOCK;
        case 2:
            if (OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime) < (u32)event->userdata[0]) {
                return EVT_RETURN_BLOCK;
            }
            event->userdata[2]++;
            return EVT_RETURN_BLOCK;
        case 3:
            fadeEntry(9, 40, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
            event->userdata[2]++;
        case 4:
            if (fadeIsFinish() != TRUE) {
                return EVT_RETURN_BLOCK;
            }
            event->userdata[0] = 60;
            event->savedTime = (s32)gp->renderTime;
            event->userdata[2]++;
            if (event->userdata[0] == 0) {
                event->userdata[2]++;
            }
            return EVT_RETURN_BLOCK;
        case 5:
            if (OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime) < (u32)event->userdata[0]) {
                return EVT_RETURN_BLOCK;
            }
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_evt_lect_tik_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_lect_tik_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_lect_tik___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_lect_tik___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_lect_tik_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_lect_tik___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_lect_tik_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_evt_lect_tik_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_lect_tik_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_lect_tik___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_lect_tik___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_lect_tik_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_lect_tik___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_lect_tik_one_364[] = {
    1065353216,
};

EVT_BEGIN(plane_majin_lecture_init)
    CALL(lect_set_systemlevel, 0)
    CALL(lect_test_systemlevel)
    CALL(evt_cam3d_evt_set_rel, FLOAT(0.0f), FLOAT(98.0f), FLOAT(558.0f), FLOAT(0.0f), FLOAT(42.0f), FLOAT(-101.799805f), 1000, 0)
    WAIT_MS(1000)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, -300, -600, 0)
    CALL(evt_cam3d_evt_set_rel, FLOAT(0.0f), FLOAT(98.0f), FLOAT(558.0f), FLOAT(0.0f), FLOAT(42.0f), FLOAT(-101.799805f), 0, 11)
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pos, -300, -600, 0)
    CALL(evt_mario_set_dir, 90, 300, 0)
    CALL(evt_cam3d_evt_set_rel, FLOAT(0.0f), FLOAT(98.0f), FLOAT(558.0f), FLOAT(0.0f), FLOAT(42.0f), FLOAT(-101.799805f), 0, 11)
    CALL(lect_map_cam_chg, STRING("hikou"), 7)
    WAIT_FRAMES(1)
    RETURN
EVT_END()

s32 plane_majin_lecture[] = {
    110, 65627, (s32)lecture_button_rtn, 112, 65545, 1, 327771, (s32)lecture_button_set_pos,
    0, -230204800, -230025600, -230000000, 107, 131122, -30000000, (s32)"hikou",
    131122, -29999999, (s32)"a_asiba", 131122, -29999995, (s32)"a_hikou", 196699, (s32)evt_hit_bind_mapobj,
    -29999999, -30000000, 196699, (s32)evt_hit_bind_mapobj, -29999995, -30000000, 262235, (s32)dai_moveti_set,
    -230000000, -230000000, -230000000, 65541, 0, 262235, (s32)dai_moveti_get, -29999998,
    -29999997, -29999996, 393307, (s32)evt_mapobj_trans, 1, -30000000, -29999998, -29999997,
    -29999996, 131163, (s32)evt_hit_bind_update, -29999999, 131163, (s32)evt_hit_bind_update, -29999995, 65545,
    1, 6, 109, 262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 1536,
    262235, (s32)evt_npc_flag_onoff, 1, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 1073741856, 196699, (s32)evt_npc_set_camid, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C",
    7, 65545, 1, 110, 65541, 0, 327771, (s32)evt_cam_get_at,
    4, -30000000, -29999999, -29999998, 131126, -29999999, 25, 327771,
    (s32)evt_npc_set_position, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", -30000000, -29999999, -29999998, 65545, 1, 6,
    112, 196699, (s32)evt_npc_set_anim, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", (s32)"P_1", 65546, 200, 327771,
    (s32)evt_msg_toge, 1, 0, 0, 0, 327771, (s32)evt_msg_print, 0,
    (s32)"mac_majin_13", 0, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 131163, (s32)evt_mario_set_pose, (s32)"M_N_H", 65541, 4,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 393307, (s32)evt_snd_sfxon_3d,
    (s32)"SFX_EVT_PERAMAJIN_LIGHT1", -30000000, -29999999, -29999998, 0, 65627, (s32)evtflash, 6,
    131163, (s32)evt_mario_set_pose, (s32)"M_S_1", 327771, (s32)evt_msg_toge, 1, 0, 0,
    0, 327771, (s32)evt_msg_print, 0, (s32)"mac_majin_14", 0, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 589915,
    (s32)evt_cam3d_evt_set_rel, -230000000, -229899648, -229428608, -229918080, -229956992, -230104243, 1000,
    11, 131124, -29999999, -229997270, 262235, (s32)dai_moveti_get, -30000000, -29999998,
    -29999997, 65541, 0, 131131, -30000000, -29999999, 131100, -30000000,
    -230225280, 131124, -30000000, -230225280, 262235, (s32)dai_moveti_set, -30000000, -29999998,
    -29999997, 7, 32, 262235, (s32)dai_moveti_set, -30000000, -29999998, -29999997,
    33, 65545, 1, 6, 327771, (s32)evt_msg_toge, 1, 0,
    0, 0, 327771, (s32)evt_msg_print, 0, (s32)"mac_majin_15", 0, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C",
    65541, 0, 196699, (s32)x_flag_set, 0, 1, 107, 131122,
    -30000000, (s32)"hikou", 131122, -29999999, (s32)"a_hikou_ue", 65541, 0, 131165,
    (s32)evt_ride_airport, -29999998, 65545, 2, 131178, -29999998, -29999997, 131096,
    -29999997, 1, 7, 33, 6, 196699, (s32)x_flag_wait, 0,
    2, 131178, -29999998, -29999997, 131096, -29999997, 1, 65631,
    -29999998, 33, 65541, 0, 131165, (s32)evt_nonride_airport, -29999998, 65545,
    2, 131178, -29999998, -29999997, 131096, -29999997, 1, 7,
    33, 6, 131178, -29999998, -29999997, 131096, -29999997, 1,
    65631, -29999998, 33, 109, 196699, (s32)x_flag_set, 1, 1,
    110, 65541, 0, 327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999,
    -29999998, 131101, -30000000, -220, 7, 33, 65545, 1,
    6, 65541, 0, 196699, (s32)x_flag_get, 1, -30000000, 131097,
    -30000000, 3, 589915, (s32)evt_cam3d_evt_set_rel, -230000000, -229899648, -229428608, -230000000,
    -229956992, -230104243, 0, 11, 33, 131096, -30000000, 2,
    7, 33, 65545, 1, 6, 112, 262235, (s32)evt_mario_mov_pos2,
    -230204800, -230000000, -229918080, 196699, (s32)evt_msg_print_add, 0, (s32)"mac_majin_15_1", 327771,
    (s32)lecture_button_set_pos, 0, -230204800, -230025600, -230000000, 262235, (s32)lecture_button_flag_on_off, 0,
    2, 1, 196699, (s32)lecture_button_set_icon_id, 0, 106, 196699, (s32)lecture_button_set_seq,
    0, 2, 196699, (s32)lecture_button_seq_wait, 0, 1, 196699, (s32)x_flag_set,
    0, 1, 107, 65541, 0, 196699, (s32)lecture_button_set_icon_id, 0,
    107, 65546, 300, 196699, (s32)x_flag_get, 0, -30000000, 131096,
    -30000000, 2, 7, 33, 196699, (s32)lecture_button_set_icon_id, 0, 106,
    65546, 300, 196699, (s32)x_flag_get, 0, -30000000, 131096, -30000000,
    2, 7, 33, 6, 109, 65541, 0, 196699,
    (s32)evt_key_get_buttontrg, 0, -30000000, 131102, -30000000, 2048, 7, 33,
    65545, 1, 6, 65627, (s32)evt_msg_continue, 131163, (s32)evt_mario_paper_plane, 1,
    196699, (s32)x_flag_set, 0, 2, 196699, (s32)lecture_button_set_seq, 0, 3,
    107, 196699, (s32)x_flag_set, 0, 1, 65541, 0, 327771,
    (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131100, -29999999, -750,
    7, 33, 65545, 1, 6, 196699, (s32)x_flag_set, 1,
    3, 65545, 1, 262235, (s32)evt_mario_set_pos, -30000000, -29999999, -29999998,
    65545, 1, 262235, (s32)evt_mario_set_pos, -30000000, -29999999, -29999998, 262235,
    (s32)dai_moveti_set, -226928000, -230000000, -230000000, 327771, (s32)evt_mario_get_pos, 0, -29999997,
    -29999996, -29999995, 131122, -30000000, -300, 131122, -29999999, -490,
    131122, -29999998, 0, 262235, (s32)evt_mario_set_pos, -30000000, -29999999, -29999998,
    589915, (s32)evt_cam3d_evt_set, -230304128, -230359424, -229532032, -230304128, -230459776, -230104243,
    1000, 0, 131163, (s32)evt_mario_cont_onoff, 0, 131163, (s32)lect_mario_ido_sum, 1000,
    131163, (s32)evt_mario_cont_onoff, 1, 262235, (s32)dai_moveti_set, -230000000, -230000000, -230000000,
    196699, (s32)x_flag_set, 1, 1, 65541, 0, 262235, (s32)evt_mario_set_pos,
    -30000000, -29999999, -29999998, 196699, (s32)x_flag_get, 0, -29999997, 131097,
    -29999997, 1, 7, 33, 65545, 1, 6, 109,
    196699, (s32)lecture_button_seq_wait, 0, 1, 262235, (s32)lecture_button_flag_on_off, 0, 2,
    0, 65546, 300, 327771, (s32)evt_msg_toge, 1, 0, 0,
    0, 327771, (s32)evt_msg_print, 0, (s32)"mac_majin_16", 0, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 196699,
    (s32)evt_msg_select, 0, (s32)"mac_majin_17", 131122, -29999997, -30000000, 65541, 0,
    327771, (s32)evt_mario_get_pos, 0, -30000000, -29999999, -29999998, 131101, -29999999,
    -550, 7, 33, 65545, 1, 6, 131096, -29999997,
    0, 196699, (s32)x_flag_set, 1, 2, 65545, 2, 589915,
    (s32)evt_cam3d_evt_set, -230307200, -230471040, -229532032, -230307200, -230571392, -230104243, 1200,
    0, 196699, (s32)x_flag_set, 0, 2, 131163, (s32)evt_mario_paper_plane, 0,
    65627, (s32)evt_mario_wait_landon, 589915, (s32)evt_cam3d_evt_set_rel, -230000000, -229899648, -229428608, -229918080,
    -229956992, -230104243, 1000, 11, 131124, -29999999, -229997270, 262235,
    (s32)dai_moveti_get, -30000000, -29999998, -29999997, 65541, 0, 131131, -30000000,
    -29999999, 131100, -30000000, -230225280, 131124, -30000000, -230225280, 262235,
    (s32)dai_moveti_set, -30000000, -29999998, -29999997, 7, 32, 262235, (s32)dai_moveti_set,
    -30000000, -29999998, -29999997, 33, 65545, 1, 6, 196699,
    (s32)evt_msg_print_add, 0, (s32)"mac_majin_18", 32, 7, 33, 6, 196699,
    (s32)evt_msg_print_add, 0, (s32)"mac_majin_18_1", 196699, (s32)x_flag_set, 1, 2, 65545,
    2, 589915, (s32)evt_cam3d_evt_set, -230307200, -230471040, -229532032, -230307200, -230571392,
    -230104243, 1200, 0, 196699, (s32)x_flag_set, 0, 2, 131163,
    (s32)evt_mario_paper_plane, 0, 65627, (s32)evt_mario_wait_landon, 196699, (s32)evt_msg_print_add, 0, (s32)"mac_majin_19",
    196699, (s32)evt_npc_set_anim, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", (s32)"P_2", 65546, 200, 196699, (s32)evt_npc_set_camid,
    (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 4, 327771, (s32)evt_npc_set_position, (s32)/*"ペラ魔人"*/"\x83\x79\x83\x89\x96\x82\x90\x6C", 0, -1000, 0,
    2, 1, 0,
};


static USER_FUNC(lect_push_r_check) {
    s32* args = event->args;

    if (keyGetButton(0) & 0x20) {
        evtSetValue(event, args[0], TRUE);
    } else {
        evtSetValue(event, args[0], FALSE);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(evt_nomal_cange) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        unk_8009f9c8();
        if (mario->flags & 0x100000) {
            motSlitCancel3();
        }
    }
    if (!marioRollKeyDisable()) {
        return EVT_RETURN_BLOCK;
    }
    return (mario->dispFlags & 0x1000000) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

BOOL psndBGMStartCheck(s32 id);

static USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

