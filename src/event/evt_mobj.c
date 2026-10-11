#include "evt/evt_cmd.h"
#include "driver/mobjdrv.h"
#include "driver/animdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mariost.h"
#include "eff/eff_small_star.h"
#include "mario/mario_motion.h"
#include "memory.h"
#include "mario/mario.h"
#include <dolphin/mtx.h>
#include "manager/fontmgr.h"
#include <string.h>

extern s32 mobjEntry(const char* name, const char* animPoseName);
extern void mobjDelete(const char* name);
extern void hitGrpFlagOn(const char* name, u32 flag);
extern EventEntry* mobjRunEvent(MapObjectEntry* mobj, s32* eventCode);
extern s32 psndSFXOn_3D(const char* name, Vec* position);
extern s32 kpaGetLevel(void);
extern void kpaAddScore(s32 score);
extern void kpaAddScorePos(s32 score, Vec* pos);
extern void kpaPowUp(void);
extern void hitGrpFlagOff(const char* name, u32 flag);

static inline MapObjectEntry* MOBJ_PTR(EventEntry* event, const char* name) {
    return strcmp(name, "me") ? mobjNameToPtr(name) : event->thisMapObj;
}

static inline MapObjectEntry* MOBJ_PTR2(EventEntry* event, const char* name) {
    return !strcmp(name, "me") ? event->thisMapObj : mobjNameToPtr(name);
}

// ---- BEGIN tail (defined in reverse of target order) ----

USER_FUNC(evt_mobj_entry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* anim = (const char*)evtGetValue(event, args[1]);
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_delete) {
    mobjDelete((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_check) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtrNoAssert((const char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)mobj);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_flag_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    const char* name = (const char*)evtGetValue(event, args[1]);
    s32 mask = args[2];
    MapObjectEntry* mobj = mobjNameToPtr(name);
    if (on) {
        mobj->flags |= mask;
    } else {
        mobj->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_get_kindname) {
    s32* args = event->args;
    MapObjectEntry* mobj = mobjNameToPtr((const char*)evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)mobj->animName);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_get_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    evtSetFloat(event, args[1], mobj->position.x);
    evtSetFloat(event, args[2], mobj->position.y);
    evtSetFloat(event, args[3], mobj->position.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_get_x_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.x);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_get_y_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.y);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_get_z_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    evtSetFloat(event, args[1], mobj->position.z);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_scale) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    MapObjectEntry* mobj;
    f32 x, y, z;
    Vec scale;
    mobj = MOBJ_PTR2(event, name);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    {
    Vec s2 = {0.0f, 0.0f, 0.0f};
    scale = s2;
    }
    scale.x = x;
    scale.y = y;
    scale.z = z;
    mobj->scale = scale;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_position) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    Vec pos = {0.0f, 0.0f, 0.0f};
    pos.x = x;
    pos.y = y;
    pos.z = z;
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_x_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.x = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_y_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.y = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_z_position) {
    s32* args = event->args;
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, args[0]));
    Vec pos = mobj->position;
    pos.z = evtGetFloat(event, args[1]);
    mobj->position = pos;
    mobj->flags |= 4;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_exec_cancel) {
    MapObjectEntry* mobj = MOBJ_PTR(event, (const char*)evtGetValue(event, event->args[0]));
    mobj->flags |= 0x1000;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_gravity_bound) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    mobj->unk68 = a;
    mobj->unk6C = b;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_set_anim) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    const char* anim = (const char*)evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    animPoseSetAnim(mobj->poseId, anim, 1);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_wait_animation_end) {
    const char* name = (const char*)evtGetValue(event, event->args[0]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    if (animPoseGetLoopTimes(mobj->poseId) > 0.0f) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(evt_mobj_set_camid) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 cam = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    mobj->camId = cam;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_hitevt_onoff) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = MOBJ_PTR(event, name);
    if (on) {
        mobj->flags &= ~0x10;
    } else {
        mobj->flags |= 0x10;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_hit_onoff) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 on = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtr(name);
    s32 i;
    if (on) {
        for (i = 0; i < 2; i++) {
            if (mobj->hitObj[i].name) {
                hitGrpFlagOff(mobj->hitObj[i].name, 1);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (mobj->hitObj[i].name) {
                hitGrpFlagOn(mobj->hitObj[i].name, 1);
            }
        }
    }
    return EVT_RETURN_DONE;
}

// ---- switches ----

s32 mobj_switch_blue(MapObjectEntry* mobj) {
    switch (mobj->unk1DC) {
    case 0:
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->unk1D4);
            if (mobj->unk1E0 == 0x200000 || mobj->unk1E0 == 0x1000000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->unk1DC++;
        }
        break;
    case 1:
        if (animPoseGetLoopTimes(mobj->poseId) < 1.0f) {
            break;
        }
        animPoseSetAnim(mobj->poseId, "S_1", 1);
        effSmallStarCamChg(effSmallStarEntry(0, 4, mobj->position.x, mobj->position.y + 12.5f, mobj->position.z, 0.0f, -1.0f, 0.0f), mobj->camId);
        evtSetValue(NULL, mobj->unk1E4, 1);
        mobj->unk1DC = 0x63;
    case 0x63:
        mobjDelete(mobj->name);
        break;
    }
    return 0;
}

s32 mobj_switch_red(MapObjectEntry* mobj) {
    switch (mobj->unk1DC) {
    case 0:
        if (mobj->flags & 8) {
            mobjRunEvent(mobj, (s32*)mobj->unk1D4);
            if (mobj->unk1E0 == 0x200000 || mobj->unk1E0 == 0x1000000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
        }
        break;
    case 1:
        if (mobj->flags & 8) {
            psndSFXOn_3D((const char*)0x1d2, &mobj->position);
            if (mobj->unk1E0 == 0x200000) {
                marioChgMot(MARIO_MOTION_JUMP_SW);
            }
            animPoseSetAnim(mobj->poseId, "A_1", 1);
            mobj->flags &= ~8;
        }
        if (!(animPoseGetLoopTimes(mobj->poseId) < 1.0f)) {
            animPoseSetAnim(mobj->poseId, "S_1", 1);
            mobj->flags &= ~8;
            mobj->unk1DC = 0;
        }
        break;
    }
    return 0;
}

USER_FUNC(evt_mobj_tornadoswitch_blue) {
    f32 x, y, z;
    MapObjectEntry* mobj;
    s32 val;
    const char* anim;
    s32* args = event->args;
    s32 arg6;
    const char* name;

    evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    anim = "MOBJ_BlueTornadoSwitch";
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_blue;
    mobj->unk1D4 = val;
    mobj->flags |= 4;
    mobj->flags |= 0x1000000;
    mobj->unk1E4 = arg6;
    mobj->unk1DC = 0;
    if (evtGetValue(event, arg6)) {
        mobj->unk1DC = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_mobj_floatswitch_blue) {
    s32 val;
    s32* args = event->args;
    const char* name;
    f32 x, y, z;
    s32 arg6;
    MapObjectEntry* mobj;
    const char* anim;
    evtGetValue(event, args[0]);
    name = (const char*)evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    val = evtGetValue(event, args[5]);
    arg6 = args[6];
    anim = "MOBJ_BlueSwitchBlock";
    if (animGroupBaseAsync(anim, gp->inBattle != 0, NULL) == 0) {
        return EVT_RETURN_BLOCK;
    }
    mobjEntry(name, anim);
    mobj = mobjNameToPtr(name);
    mobjSetPosition(name, x, y, z);
    mobj->mainFunc = mobj_switch_blue;
    mobj->unk1D4 = val;
    mobj->flags |= 4;
    mobj->flags |= 0x400000;
    mobj->unk1E4 = arg6;
    mobj->unk1DC = 0;
    if (evtGetValue(event, arg6)) {
        mobj->unk1DC = 99;
    }
    mobjCalcMtx(mobj);
    return EVT_RETURN_DONE;
}

// ---- kpa ----

typedef struct KpaPoleScoreWork {
    char str[8];
    f32 x;
    f32 y;
    f32 z;
} KpaPoleScoreWork;

static KpaPoleScoreWork* psw;

USER_FUNC(kpa_powerup) {
    s32* args = event->args;
    Vec pos;
    pos.x = evtGetFloat(event, args[0]);
    pos.y = evtGetFloat(event, args[1]);
    pos.z = evtGetFloat(event, args[2]);
    kpaAddScorePos(500, &pos);
    if (kpaGetLevel() == 3) {
        kpaAddScore(1000);
    }
    kpaPowUp();
    return EVT_RETURN_DONE;
}

USER_FUNC(kpa_get_pole_name) {
    MapObjectEntry* mobj = event->thisMapObj;
    s32* args = event->args;
    if (mobj != NULL) {
        evtSetValue(event, args[0], (s32)mobj->name);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(kpa_get_hata_name) {
    MapObjectEntry* mobj = event->thisMapObj;
    s32* args = event->args;
    if (mobj != NULL) {
        evtSetValue(event, args[0], (s32)mobj->unk1B8);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(kpa_get_level) {
    s32* args = event->args;
    evtSetValue(event, args[0], kpaGetLevel());
    return EVT_RETURN_DONE;
}

USER_FUNC(kpa_get_width) {
    s32* args = event->args;
    evtSetValue(event, args[0], (s32)marioGetPtr()->wPlayerCollisionBox.x);
    return EVT_RETURN_DONE;
}

void kpa_disp_pole_score(CameraId camId, void* param) {
    Mtx trans;
    Mtx scale;
    PSMTXTrans(trans, psw->x, psw->y, 300.0f);
    PSMTXScale(scale, 0.5f, 0.5f, 0.5f);
    PSMTXConcat(trans, scale, trans);
    FontDrawStart();
    FontDrawColor((GXColor){255, 255, 255, 255});
    FontDrawStringMtx(trans, psw->str);
}

USER_FUNC(kpa_disp_pole_init) {
    psw = _mapAlloc(0x14);
    psw->str[0] = 0;
    psw->z = 0.0f;
    psw->y = 0.0f;
    psw->x = 0.0f;
    return EVT_RETURN_DONE;
}

USER_FUNC(kpa_clear_jump_data) {
    MarioWork* mario = marioGetPtr();
    mario->airTimer = 0;
    return EVT_RETURN_DONE;
}
