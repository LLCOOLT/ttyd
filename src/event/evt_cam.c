#include "evt/evt_cam.h"
#include "driver/camdrv.h"
#include "driver/npcdrv.h"
#include "evt/evt_npc.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/os.h>

extern GlobalWork* gp;

typedef struct CamRoadOut {
    Vec f_0;
    Vec pos; // 0xc
    Vec at;  // 0x18
} CamRoadOut;

void camRoadMain(CamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
void camRoadReset(void);
void camShiftReset(void);
void camShiftMain(CameraEntry* camera, MarioWork* mario, f32* out);
extern int __float_nan[];
void OSReport(const char* msg, ...);
double sin(double);
double cos(double);

#ifdef NONMATCHING
static inline s32 cam_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
#endif
#ifdef NONMATCHING
static inline f32 cam_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (cam_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif

// CameraId id, BOOL on
#ifdef NONMATCHING
USER_FUNC(evt_cam_ctrl_onoff) {
    s32* args = event->args;
    CameraId id = evtGetValue(event, args[0]);

    if (evtGetValue(event, args[1])) {
        camCtrlOn(id);
    }
    else {
        camCtrlOff(id);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam_get_pos) {
    s32* args = event->args;
    CameraEntry* camera = camGetPtr(evtGetValue(event, args[0]));

    evtSetFloat(event, args[1], camera->cameraPos.x);
    evtSetFloat(event, args[2], camera->cameraPos.y);
    evtSetFloat(event, args[3], camera->cameraPos.z);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam_get_at) {
    s32* args = event->args;
    CameraEntry* camera = camGetPtr(evtGetValue(event, args[0]));

    evtSetFloat(event, args[1], camera->cameraAt.x);
    evtSetFloat(event, args[2], camera->cameraAt.y);
    evtSetFloat(event, args[3], camera->cameraAt.z);
    return EVT_RETURN_DONE;
}
#endif

// CameraId id, f32 x, f32 y, s32 msec
#ifdef NONMATCHING
USER_FUNC(evt_cam_shake) {
    u64 now;
    s32* args = event->args;
    int new_var;
    u64 last;
    u32 hi;
    int new_var2;
    u32 lo;
    CameraId id;
    s32 msec;
    f32 x, y;
    f32 len;
    s32 onTime, offTime;

    id = evtGetValue(event, args[0]);
    x = evtGetFloat(event, args[1]);
    new_var2 = id;
    y = evtGetFloat(event, args[2]);
    msec = evtGetValue(event, args[3]);
    hi = ((u32*)&event->lifetime)[0];
    lo = ((u32*)&event->lifetime)[1];
    now = ((u64)hi << 32) | lo;
    if (isFirstCall) {
        event->userdata[0] = 0;
        ((u32*)&event->userdata[1])[0] = (now >> 32) & 0xFFFFFFFF;
        ((u32*)&event->userdata[1])[1] = now & 0xFFFFFFFF;
        *(s32*)&event->userdata3 = 0;
        ((u32*)&event->wInterpRelatedTime)[0] = (now >> 32) & 0xFFFFFFFF;
        ((u32*)&event->wInterpRelatedTime)[1] = now & 0xFFFFFFFF;
    }
    event->userdata[0]++;
    event->userdata[0] %= 4;
    if (event->userdata[0] < 2) {
        PSMTX44Trans(camGetPtr(new_var2)->projAdjust, x, y, 0.0f);
    }
    else {
        PSMTX44Trans(camGetPtr(new_var2)->projAdjust, -x, -y, 0.0f);
    }
    camGetPtr(new_var2)->flags |= 8;
    if (msec) {
        if ((u64)msec < OSTicksToMilliseconds(now - *(u64*)&event->userdata[1])) {
            camGetPtr(id)->flags &= ~8;
            padRumbleOff(0);
            return EVT_RETURN_DONE;
        }
    }
    len = cam_sqrtf(x * x + y * y);
    onTime = 13000.0f * len;
    offTime = 50.0f * (1.0f - len);
    last = event->wInterpRelatedTime;
    if (onTime && offTime) {
        if (!*(s32*)&event->userdata3) {
            padRumbleOn(0);
            if (onTime < OSTicksToMilliseconds(now - last)) {
                new_var = 32;
                event->userdata3 = 1 - event->userdata3;
                ((u32*)&event->wInterpRelatedTime)[0] = (now >> new_var) & 0xFFFFFFFF;
                ((u32*)&event->wInterpRelatedTime)[1] = now & 0xFFFFFFFF;
            }
        }
        else {
            padRumbleOff(0);
            if (offTime < OSTicksToMilliseconds(now - last)) {
                event->userdata3 = 1 - event->userdata3;
                ((u32*)&event->wInterpRelatedTime)[0] = (now >> 32) & 0xFFFFFFFF;
                ((u32*)&event->wInterpRelatedTime)[1] = now & 0xFFFFFFFF;
            }
        }
    }
    return EVT_RETURN_BLOCK;
}
#endif

// s32 percent, s32 msec, s32 dist, s32 curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_zoom_in) {
    s32* args = event->args;
    s32 percent, msec, dist, curve;
    CameraEntry* camera;
    Vec pos;

    percent = evtGetValue(event, args[0]);
    msec = evtGetValue(event, args[1]);
    dist = evtGetValue(event, args[2]);
    curve = evtGetValue(event, args[3]);
    camera = camGetPtr(CAMERA_3D);
    PSVECSubtract(&camera->cameraAt, &camera->cameraPos, &pos);
    PSVECScale(&pos, &pos, (f32)percent / 100.0f);
    PSVECAdd(&pos, &camera->cameraPos, &pos);
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = pos;
    camera->storedAt = camera->cameraAt;
    camera->storedPos.x += (f32)dist * (f32)cos(camera->viewYaw);
    camera->storedPos.z += (f32)dist * (f32)sin(camera->viewYaw);
    camera->storedAt.x += (f32)dist * (f32)cos(camera->viewYaw);
    camera->storedAt.z += (f32)dist * (f32)sin(camera->viewYaw);
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// s32 x, s32 y, s32 z, s32 percent, s32 msec, s32 curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_at) {
    s32* args = event->args;
    s32 x, y, z, percent, msec, curve;
    CameraEntry* camera;
    Vec at;
    Vec pos;

    x = evtGetValue(event, args[0]);
    y = evtGetValue(event, args[1]);
    z = evtGetValue(event, args[2]);
    percent = evtGetValue(event, args[3]);
    msec = evtGetValue(event, args[4]);
    curve = evtGetValue(event, args[5]);
    camera = camGetPtr(CAMERA_3D);
    at = (Vec){x, y, z};
    (Vec){0.0f, 0.0f, 0.0f};
    PSVECSubtract(&at, &camera->cameraPos, &pos);
    PSVECScale(&pos, &pos, (f32)percent / 100.0f);
    PSVECAdd(&pos, &camera->cameraPos, &pos);
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = pos;
    camera->storedAt = at;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// s32 posX, posY, posZ, atX, atY, atZ, msec, curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set) {
    s32* args = event->args;
    f32 px, py, pz, ax, ay, az;
    s32 msec, curve;
    CameraEntry* camera;
    Vec pos, at;

    px = evtGetValue(event, args[0]);
    py = evtGetValue(event, args[1]);
    pz = evtGetValue(event, args[2]);
    ax = evtGetValue(event, args[3]);
    ay = evtGetValue(event, args[4]);
    az = evtGetValue(event, args[5]);
    msec = evtGetValue(event, args[6]);
    curve = evtGetValue(event, args[7]);
    camera = camGetPtr(CAMERA_3D);
    pos = (Vec){px, py, pz};
    at = (Vec){ax, ay, az};
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = pos;
    camera->storedAt = at;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// s32 posX, posY, posZ (relative to at), atX, atY, atZ (relative to mario), msec, curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_rel) {
    s32* args = event->args;
    f32 px, py, pz, ax, ay, az;
    s32 msec, curve;
    CameraEntry* camera;
    MarioWork* mario;

    px = evtGetValue(event, args[0]);
    py = evtGetValue(event, args[1]);
    pz = evtGetValue(event, args[2]);
    ax = evtGetValue(event, args[3]);
    ay = evtGetValue(event, args[4]);
    az = evtGetValue(event, args[5]);
    msec = evtGetValue(event, args[6]);
    curve = evtGetValue(event, args[7]);
    camera = camGetPtr(CAMERA_3D);
    mario = marioGetPtr();
    {
        Vec pos, at;

        (Vec){0.0f, 0.0f, 0.0f};
        (Vec){0.0f, 0.0f, 0.0f};
        ax = mario->position.x + ax;
        ay = mario->position.y + ay;
        az = mario->position.z + az;
        pos.x = px + ax;
        pos.y = py + ay;
        pos.z = pz + az;
        at.x = ax;
        at.y = ay;
        at.z = az;

        camera->presetPos = camera->cameraPos;
        camera->presetAt = camera->cameraAt;
        camera->storedPos = pos;
        camera->storedAt = at;
    }
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// const char* npc, s32 posX, posY, posZ, atX, atY, atZ, msec, curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_npc_rel) {
    s32* args = event->args;
    const char* name;
    f32 px, py, pz, ax, ay, az;
    s32 msec, curve;
    CameraEntry* camera;
    NpcEntry* npc;
    Vec npcPos, npcAt;
    Vec pos, at;

    name = (const char*)evtGetValue(event, args[0]);
    px = evtGetValue(event, args[1]);
    py = evtGetValue(event, args[2]);
    pz = evtGetValue(event, args[3]);
    ax = evtGetValue(event, args[4]);
    ay = evtGetValue(event, args[5]);
    az = evtGetValue(event, args[6]);
    msec = evtGetValue(event, args[7]);
    curve = evtGetValue(event, args[8]);
    camera = camGetPtr(CAMERA_3D);
    npc = evtNpcNameToPtr(event, name);
    pos = (Vec){px, py, pz};
    at = (Vec){ax, ay, az};
    PSVECAdd(&npc->position, &at, &npcAt);
    PSVECAdd(&npcAt, &pos, &npcPos);
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = npcPos;
    camera->storedAt = npcAt;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// s32 posX, posY, posZ, atX, atY, atZ (rotated by camera yaw), msec, curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_rel_dir) {
    s32* args = event->args;
    f32 px, py, pz, ax, ay, az;
    s32 msec, curve;
    f32 yaw;
    CameraEntry* camera;
    MarioWork* mario;
    Mtx mtx;
    Vec marPos, marAt;
    Vec pos, at;

    px = evtGetValue(event, args[0]);
    py = evtGetValue(event, args[1]);
    pz = evtGetValue(event, args[2]);
    ax = evtGetValue(event, args[3]);
    ay = evtGetValue(event, args[4]);
    az = evtGetValue(event, args[5]);
    msec = evtGetValue(event, args[6]);
    curve = evtGetValue(event, args[7]);
    yaw = -camGetPtr(CAMERA_3D)->viewYaw;
    camera = camGetPtr(CAMERA_3D);
    mario = marioGetPtr();
    pos = (Vec){px, py, pz};
    at = (Vec){ax, ay, az};
    PSMTXRotRad(mtx, 'Y', 0.017453292f * yaw);
    PSMTXMultVec(mtx, &pos, &pos);
    PSMTXMultVec(mtx, &at, &at);
    PSVECAdd(&mario->position, &at, &marAt);
    PSVECAdd(&marAt, &pos, &marPos);
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = marPos;
    camera->storedAt = marAt;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// unused (dead-stripped): only its string and 100.0f survive
#ifdef NONMATCHING
static void evt_cam_debug_print(f32 a) /* restore */ {
    OSReport("%f%f%f%f%f%f%d%s", a / 100.0f);
}
#endif

// s32 msec, s32 curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_off) {
    s32* args = event->args;
    s32 msec, curve;
    CameraEntry* camera;

    msec = evtGetValue(event, args[0]);
    curve = evtGetValue(event, args[1]);
    camera = camGetPtr(CAMERA_3D);
    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 1;
    camera->curveA = curve;
    return EVT_RETURN_DONE;
}
#endif

// BOOL on
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_road_shift_onoff) {
    s32 on = evtGetValue(event, *event->args);
    CameraEntry* camera = camGetPtr(CAMERA_3D);

    if (on) {
        camera->flags &= ~0x20;
    }
    else {
        camera->flags |= 0x20;
    }
    return EVT_RETURN_DONE;
}
#endif

// s32 x, s32 y, s32 z, s32 dolly, s32 msec, s32 curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_xyz) {
    s32* args = event->args;
    s32 x, y, z, dolly, msec, curve;
    CameraEntry* camera;

    x = evtGetValue(event, args[0]);
    y = evtGetValue(event, args[1]);
    z = evtGetValue(event, args[2]);
    dolly = evtGetValue(event, args[3]);
    msec = evtGetValue(event, args[4]);
    curve = evtGetValue(event, args[5]);
    camera = camGetPtr(CAMERA_3D);
    camera->anchorPrev = (Vec){camera->blendPos.x, camera->blendPos.y, camera->blendPos.z};
    camera->anchor = (Vec){x, y, z};
    camera->dollyStartAlt = camera->dollyPercent;
    camera->dollyEnd = dolly;
    camera->startTimeB = gp->renderTime;
    camera->durationB = OSMillisecondsToTicks(msec);
    camera->stateB = 3;
    camera->curveB = curve;
    return EVT_RETURN_DONE;
}
#endif

// s32 msec, s32 curve
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_xyz_off) {
    s32* args = event->args;
    s32 msec, curve;
    CameraEntry* camera;

    msec = evtGetValue(event, args[0]);
    curve = evtGetValue(event, args[1]);
    camera = camGetPtr(CAMERA_3D);
    camera->anchorPrev = (Vec){camera->blendPos.x, camera->blendPos.y, camera->blendPos.z};
    camera->dollyStartAlt = camera->dollyPercent;
    camera->startTimeB = gp->renderTime;
    camera->durationB = OSMillisecondsToTicks(msec);
    camera->stateB = 1;
    camera->curveB = curve;
    return EVT_RETURN_DONE;
}
#endif

// f32 x, f32 y, f32 z, out f32 shift
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_get_shift) {
    s32* args = event->args;
    MarioWork* mario;
    CameraEntry* camera;
    f32 x, y, z;
    f32 sx, sy, sz;
    f32 shift;

    mario = marioGetPtr();
    camera = camGetPtr(CAMERA_3D);
    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    sx = mario->position.x;
    sy = mario->position.y;
    sz = mario->position.z;
    mario->position.x = x;
    mario->position.y = y;
    mario->position.z = z;
    camShiftMain(camera, mario, &shift);
    mario->position.x = sx;
    mario->position.y = sy;
    mario->position.z = sz;
    evtSetFloat(event, args[3], shift);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam3d_evt_set_now) {
    CameraEntry* camera = camGetPtr(CAMERA_3D);

    camera->storedPos = camera->cameraPos;
    camera->presetPos = camera->storedPos;
    camera->storedAt = camera->cameraAt;
    camera->presetAt = camera->storedAt;
    camera->startTimeA = gp->renderTime;
    camera->durationA = 0;
    camera->stateA = 3;
    camera->curveA = 11;
    return EVT_RETURN_DONE;
}
#endif

// f32 x, f32 y, f32 z, f32 w, out f32 posX, posY, posZ, atX, atY, atZ
#ifdef NONMATCHING
USER_FUNC(evt_cam3d_event_from_road) {
    s32* args = event->args;
    f32 x, y, z, w;
    CamRoadOut out;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    w = evtGetFloat(event, args[3]);
    camRoadMain(&out, x, y, z, x, y, z, w);
    evtSetFloat(event, args[4], out.pos.x);
    evtSetFloat(event, args[5], out.pos.y);
    evtSetFloat(event, args[6], out.pos.z);
    evtSetFloat(event, args[7], out.at.x);
    evtSetFloat(event, args[8], out.at.y);
    evtSetFloat(event, args[9], out.at.z);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam_road_reset) {
    MarioWork* mario = marioGetPtr();
    CameraEntry* camera = camGetPtr(CAMERA_3D);

    camera->marioPos.x = mario->position.x;
    camera->marioPos.y = 0.01f + mario->position.y;
    camera->marioPos.z = mario->position.z;
    camera->marioAt.x = camera->marioPos.x;
    camera->marioAt.y = camera->marioPos.y;
    camera->marioAt.z = camera->marioPos.z;
    mario->camTarget = mario->position;
    mario->camCollision = mario->position;
    camRoadReset();
    camShiftReset();
    return EVT_RETURN_DONE;
}
#endif

// f32 x, f32 y, f32 z
#ifdef NONMATCHING
USER_FUNC(evt_cam_road_reset2) {
    s32* args = event->args;
    f32 x, y, z;
    MarioWork* mario;
    CameraEntry* camera;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    mario = marioGetPtr();
    camera = camGetPtr(CAMERA_3D);
    camera->marioPos.x = x;
    camera->marioPos.y = 0.01f + y;
    camera->marioPos.z = z;
    camera->dollyStart = 0.0f;
    camera->marioAt.x = camera->marioPos.x;
    camera->marioAt.y = camera->marioPos.y;
    camera->marioAt.z = camera->marioPos.z;
    mario->camTarget = (Vec){x, y, z};
    mario->camCollision = (Vec){x, y, z};
    camRoadReset();
    camShiftReset();
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam_shift_reset) {
    marioGetPtr();
    camGetPtr(CAMERA_3D);
    camShiftReset();
    return EVT_RETURN_DONE;
}
#endif

// BOOL ortho, CameraId id
#ifdef NONMATCHING
USER_FUNC(evt_cam_type_change) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    CameraId id = evtGetValue(event, args[1]);

    if (type == 0) {
        camSetTypePersp(id);
    }
    else {
        camSetTypeOrtho(id);
    }
    return EVT_RETURN_DONE;
}
#endif

// BOOL on, BOOL flag
#ifdef NONMATCHING
USER_FUNC(evt_cam_letter_box_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    CameraEntry* camera = camGetPtr(CAMERA_2D);

    if (on) {
        camera->flags |= 0x100;
        psndSetFlag(0x20);
        camera->letterBoxAlpha = 255;
        camera->letterBoxTop = 0;
        camera->letterBoxBottom = 0;
        camera->letterBoxCamId = CAMERA_2D;
    }
    else {
        camera->flags &= ~0x100;
        psndClearFlag(0x20);
    }
    if (flag) {
        camera->flags |= 0x400;
    }
    return EVT_RETURN_DONE;
}
#endif

// BOOL disable
#ifdef NONMATCHING
USER_FUNC(evt_cam_letter_box_disable) {
    s32 disable = evtGetValue(event, *event->args);
    CameraEntry* camera = camGetPtr(CAMERA_2D);

    if (disable) {
        camera->flags |= 0x200;
        psndSetFlag(0x40);
    }
    else {
        camera->flags &= ~0x200;
        psndClearFlag(0x40);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_cam_letter_box_wait) {
    CameraEntry* camera = camGetPtr(CAMERA_2D);

    if ((camera->flags & 0x100) && camera->letterBoxTop == 49 && camera->letterBoxBottom == 44) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
#endif

// CameraId id
#ifdef NONMATCHING
USER_FUNC(evt_cam_letter_box_camid) {
    CameraId id = evtGetValue(event, *event->args);

    camGetPtr(CAMERA_2D)->letterBoxCamId = id;
    return EVT_RETURN_DONE;
}
#endif

void __div2u();
#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): evt_cam_ctrl_onoff (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".sdata2") const f32 float_0p01_8041af28 = 0.01f;
__declspec(section ".sdata2") const f32 float_0_8041af2c = 0.0f;
__declspec(section ".sdata2") const f32 float_100_8041af30 = 100.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041af34 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_13000_8041af38 = 13000.0f;
__declspec(section ".sdata2") const f32 float_50_8041af3c = 50.0f;
__declspec(section ".sdata2") const f32 float_1_8041af40 = 1.0f;
__declspec(section ".sdata2") const u32 gap_09_8041AF44_sdata2 = 0x00000000;
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c5f38[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f44[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f50[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f5c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f68[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f74[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f80[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f8c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5f98[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fa4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fb0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fbc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fc8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fd4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c5fe0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802c5ff0 = 4503601774854144;
__declspec(section ".rodata") const char str_802C5FF8[] = "%f%f%f%f%f%f%d%s\000\000\000";
__declspec(section ".rodata") const f64 double_0p5_802c6010 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c6018 = 3;
__declspec(section ".rodata") const f64 double_0_802c6020 = 0;
#pragma force_active reset
USER_FUNC(evt_cam_letter_box_camid);
USER_FUNC(evt_cam_letter_box_wait);
USER_FUNC(evt_cam_letter_box_disable);
USER_FUNC(evt_cam_letter_box_onoff);
USER_FUNC(evt_cam_type_change);
USER_FUNC(evt_cam_shift_reset);
USER_FUNC(evt_cam_road_reset2);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cam3d_event_from_road);
USER_FUNC(evt_cam3d_evt_set_now);
USER_FUNC(evt_cam3d_get_shift);
USER_FUNC(evt_cam3d_evt_xyz_off);
USER_FUNC(evt_cam3d_evt_set_xyz);
USER_FUNC(evt_cam3d_road_shift_onoff);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam3d_evt_set_rel_dir);
USER_FUNC(evt_cam3d_evt_set_npc_rel);
USER_FUNC(evt_cam3d_evt_set_rel);
USER_FUNC(evt_cam3d_evt_set);
USER_FUNC(evt_cam3d_evt_set_at);
USER_FUNC(evt_cam3d_evt_zoom_in);
USER_FUNC(evt_cam_shake);
USER_FUNC(evt_cam_get_at);
USER_FUNC(evt_cam_get_pos);
USER_FUNC(evt_cam_ctrl_onoff);

asm s32 evt_cam_letter_box_camid(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r31, r3
	li r3, 0x8
	bl camGetPtr
	stw r31, 0x1e8(r3)
	li r3, 0x2
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam_letter_box_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x8
	stw r0, 0x14(r1)
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @1
	lha r0, 0x1e2(r3)
	cmpwi r0, 0x31
	bne @1
	lha r0, 0x1e4(r3)
	cmpwi r0, 0x2c
	bne @1
	li r3, 0x2
	b @2
	@1:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam_letter_box_disable(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r31, r3
	li r3, 0x8
	bl camGetPtr
	cmpwi r31, 0x0
	beq @1
	lhz r0, 0x0(r3)
	ori r0, r0, 0x200
	sth r0, 0x0(r3)
	li r3, 0x40
	bl psndSetFlag
	b @2
	@1:
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 23, 21
	sth r0, 0x0(r3)
	li r3, 0x40
	bl psndClearFlag
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam_letter_box_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	mr r30, r3
	li r3, 0x8
	bl camGetPtr
	cmpwi r31, 0x0
	mr r31, r3
	beq @1
	lhz r0, 0x0(r31)
	li r3, 0x20
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	bl psndSetFlag
	li r0, 0xff
	li r3, 0x0
	sth r0, 0x1e0(r31)
	li r0, 0x8
	sth r3, 0x1e2(r31)
	sth r3, 0x1e4(r31)
	stw r0, 0x1e8(r31)
	b @2
	@1:
	lhz r0, 0x0(r31)
	li r3, 0x20
	rlwinm r0, r0, 0, 24, 22
	sth r0, 0x0(r31)
	bl psndClearFlag
	@2:
	cmpwi r30, 0x0
	beq @3
	lhz r0, 0x0(r31)
	ori r0, r0, 0x400
	sth r0, 0x0(r31)
	@3:
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_cam_type_change(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	cmpwi r31, 0x0
	bne @1
	bl camSetTypePersp
	b @2
	@1:
	bl camSetTypeOrtho
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam_shift_reset(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	li r3, 0x4
	bl camGetPtr
	bl camShiftReset
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam_road_reset2(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x4(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	bl marioGetPtr
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lfs f0, float_0p01_8041af28(r2)
	lis r5, vec3_802c5fd4@ha
	stfs f29, 0x94(r3)
	lis r4, vec3_802c5fe0@ha
	fadds f1, f0, f30
	lfs f0, float_0_8041af2c(r2)
	stfs f1, 0x98(r3)
	stfs f31, 0x9c(r3)
	stfs f0, 0xe8(r3)
	lfs f0, 0x94(r3)
	stfs f0, 0xac(r3)
	lfs f0, 0x98(r3)
	stfs f0, 0xb0(r3)
	lfs f0, 0x9c(r3)
	stfs f0, 0xb4(r3)
	lwzu r0, vec3_802c5fd4@l(r5)
	stw r0, 0x14(r1)
	lwz r3, 0x4(r5)
	lwz r0, 0x8(r5)
	stw r3, 0x18(r1)
	stw r0, 0x1c(r1)
	stfs f29, 0x14(r1)
	lwz r0, 0x14(r1)
	stfs f30, 0x18(r1)
	stfs f31, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0xec(r31)
	lwz r0, 0x1c(r1)
	stw r3, 0xf0(r31)
	stw r0, 0xf4(r31)
	lwzu r0, vec3_802c5fe0@l(r4)
	stw r0, 0x8(r1)
	lwz r3, 0x4(r4)
	lwz r0, 0x8(r4)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f29, 0x8(r1)
	lwz r0, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0xf8(r31)
	lwz r0, 0x10(r1)
	stw r3, 0xfc(r31)
	stw r0, 0x100(r31)
	bl camRoadReset
	bl camShiftReset
	li r3, 0x2
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r0, 0x64(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_cam_road_reset(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPtr
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lfs f0, 0x8c(r31)
	lfs f1, float_0p01_8041af28(r2)
	stfs f0, 0x94(r3)
	lfs f0, 0x90(r31)
	fadds f0, f1, f0
	stfs f0, 0x98(r3)
	lfs f0, 0x94(r31)
	stfs f0, 0x9c(r3)
	lfs f0, 0x94(r3)
	stfs f0, 0xac(r3)
	lfs f0, 0x98(r3)
	stfs f0, 0xb0(r3)
	lfs f0, 0x9c(r3)
	stfs f0, 0xb4(r3)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xec(r31)
	stw r0, 0xf0(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xf4(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xf8(r31)
	stw r0, 0xfc(r31)
	lwz r0, 0x94(r31)
	stw r0, 0x100(r31)
	bl camRoadReset
	bl camShiftReset
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam3d_event_from_road(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x4(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0xc(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f0, f1
	addi r3, r1, 0x8
	fmr f1, f31
	fmr f2, f30
	fmr f7, f0
	fmr f3, f29
	fmr f4, f31
	fmr f5, f30
	fmr f6, f29
	bl camRoadMain
	lwz r4, 0x10(r31)
	mr r3, r30
	lfs f1, 0x14(r1)
	bl evtSetFloat
	lwz r4, 0x14(r31)
	mr r3, r30
	lfs f1, 0x18(r1)
	bl evtSetFloat
	lwz r4, 0x18(r31)
	mr r3, r30
	lfs f1, 0x1c(r1)
	bl evtSetFloat
	lwz r4, 0x1c(r31)
	mr r3, r30
	lfs f1, 0x20(r1)
	bl evtSetFloat
	lwz r4, 0x20(r31)
	mr r3, r30
	lfs f1, 0x24(r1)
	bl evtSetFloat
	lwz r4, 0x24(r31)
	mr r3, r30
	lfs f1, 0x28(r1)
	bl evtSetFloat
	li r3, 0x2
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r0, 0x74(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 evt_cam3d_evt_set_now(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x4
	stw r0, 0x14(r1)
	bl camGetPtr
	lwz r7, 0xc(r3)
	li r5, 0x0
	lwz r6, 0x10(r3)
	li r4, 0x3
	li r0, 0xb
	stw r7, 0x40(r3)
	stw r6, 0x44(r3)
	lwz r6, 0x14(r3)
	stw r6, 0x48(r3)
	lwz r7, 0x40(r3)
	lwz r6, 0x44(r3)
	stw r7, 0x58(r3)
	stw r6, 0x5c(r3)
	lwz r6, 0x48(r3)
	stw r6, 0x60(r3)
	lwz r7, 0x18(r3)
	lwz r6, 0x1c(r3)
	stw r7, 0x4c(r3)
	stw r6, 0x50(r3)
	lwz r6, 0x20(r3)
	stw r6, 0x54(r3)
	lwz r7, 0x4c(r3)
	lwz r6, 0x50(r3)
	stw r7, 0x64(r3)
	stw r6, 0x68(r3)
	lwz r6, 0x54(r3)
	stw r6, 0x6c(r3)
	lwz r7, gp(r13)
	lwz r6, 0x38(r7)
	lwz r7, 0x3c(r7)
	stw r7, 0x74(r3)
	stw r6, 0x70(r3)
	stw r5, 0x7c(r3)
	stw r5, 0x78(r3)
	sth r4, 0x4(r3)
	stb r0, 0x80(r3)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam3d_get_shift(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stfd f28, 0x30(r1)
	psq_st f28, 0x38(r1), 0, 0
	stfd f27, 0x20(r1)
	psq_st f27, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r31, 0x18(r3)
	bl marioGetPtr
	mr r0, r3
	li r3, 0x4
	mr r30, r0
	bl camGetPtr
	lwz r4, 0x0(r31)
	mr r29, r3
	mr r3, r28
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x4(r31)
	mr r3, r28
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r28
	bl evtGetFloat
	lfs f29, 0x8c(r30)
	mr r3, r29
	lfs f28, 0x90(r30)
	mr r4, r30
	lfs f27, 0x94(r30)
	addi r5, r1, 0x8
	stfs f30, 0x8c(r30)
	stfs f31, 0x90(r30)
	stfs f1, 0x94(r30)
	bl camShiftMain
	stfs f29, 0x8c(r30)
	mr r3, r28
	stfs f28, 0x90(r30)
	stfs f27, 0x94(r30)
	lwz r4, 0xc(r31)
	lfs f1, 0x8(r1)
	bl evtSetFloat
	li r3, 0x2
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	psq_l f28, 0x38(r1), 0, 0
	lfd f28, 0x30(r1)
	psq_l f27, 0x28(r1), 0, 0
	lfd f27, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x74(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 evt_cam3d_evt_xyz_off(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lis r5, vec3_802c5fc8@ha
	lis r4, 0x1062
	addi r7, r5, vec3_802c5fc8@l
	lfs f0, 0x88(r3)
	lwz r0, 0x0(r7)
	addi r6, r4, 0x4dd3
	lwz r8, 0x4(r7)
	lis r5, 0x8000
	stw r0, 0x8(r1)
	li r4, 0x0
	lwz r7, 0x8(r7)
	li r0, 0x1
	stfs f0, 0x8(r1)
	lfs f1, 0x8c(r3)
	stw r8, 0xc(r1)
	lfs f0, 0x90(r3)
	stw r7, 0x10(r1)
	lwz r7, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r8, 0xc(r1)
	stw r7, 0xc4(r3)
	lwz r7, 0x10(r1)
	stw r8, 0xc8(r3)
	stw r7, 0xcc(r3)
	lfs f0, 0xe4(r3)
	stfs f0, 0xf0(r3)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0xd4(r3)
	stw r7, 0xd0(r3)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r30, r5
	stw r5, 0xdc(r3)
	stw r4, 0xd8(r3)
	sth r0, 0x82(r3)
	stb r31, 0xe0(r3)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r0, 0x24(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_cam3d_evt_set_xyz(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r26, 0x48(r1)
	mr r31, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r26, r3
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x8(r30)
	mr r29, r3
	mr r3, r31
	bl evtGetValue
	lwz r4, 0xc(r30)
	mr r28, r3
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x10(r30)
	mr r27, r3
	mr r3, r31
	bl evtGetValue
	lwz r4, 0x14(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lis r4, vec3_802c5fb0@ha
	lis r10, 0x4330
	addi r7, r4, vec3_802c5fb0@l
	xoris r9, r29, 0x8000
	lwz r0, 0x0(r7)
	xoris r11, r26, 0x8000
	lwz r6, 0x4(r7)
	lis r4, double_to_int_802c5ff0@ha
	stw r0, 0x14(r1)
	addi r12, r4, double_to_int_802c5ff0@l
	lfs f0, 0x88(r3)
	xoris r8, r28, 0x8000
	lwz r0, 0x8(r7)
	xoris r7, r27, 0x8000
	stfs f0, 0x14(r1)
	lis r5, vec3_802c5fbc@ha
	lfs f1, 0x8c(r3)
	addi r27, r5, vec3_802c5fbc@l
	stw r6, 0x18(r1)
	lis r4, 0x1062
	lfs f0, 0x90(r3)
	addi r6, r4, 0x4dd3
	stw r0, 0x1c(r1)
	lis r5, 0x8000
	lwz r29, 0x14(r1)
	li r4, 0x0
	stfs f1, 0x18(r1)
	li r0, 0x3
	lfd f2, 0x0(r12)
	stfs f0, 0x1c(r1)
	lwz r28, 0x18(r1)
	stw r29, 0xc4(r3)
	lwz r12, 0x1c(r1)
	stw r28, 0xc8(r3)
	stw r12, 0xcc(r3)
	lwz r29, 0x4(r27)
	lwz r28, 0x0(r27)
	lwz r12, 0x8(r27)
	stw r11, 0x24(r1)
	stw r10, 0x20(r1)
	lfd f0, 0x20(r1)
	stw r9, 0x2c(r1)
	fsubs f1, f0, f2
	stw r10, 0x28(r1)
	lfd f0, 0x28(r1)
	stw r28, 0x8(r1)
	fsubs f0, f0, f2
	stw r29, 0xc(r1)
	stfs f1, 0x8(r1)
	lwz r9, 0x8(r1)
	stw r8, 0x34(r1)
	stfs f0, 0xc(r1)
	stw r10, 0x30(r1)
	lwz r8, 0xc(r1)
	lfd f0, 0x30(r1)
	stw r9, 0xb8(r3)
	fsubs f0, f0, f2
	stw r12, 0x10(r1)
	stfs f0, 0x10(r1)
	stw r8, 0xbc(r3)
	lwz r8, 0x10(r1)
	stw r7, 0x3c(r1)
	stw r10, 0x38(r1)
	stw r8, 0xc0(r3)
	lfd f0, 0x38(r1)
	lfs f1, 0xe4(r3)
	fsubs f0, f0, f2
	stfs f1, 0xf0(r3)
	stfs f0, 0xec(r3)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0xd4(r3)
	stw r7, 0xd0(r3)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r30, r5
	stw r5, 0xdc(r3)
	stw r4, 0xd8(r3)
	sth r0, 0x82(r3)
	stb r31, 0xe0(r3)
	li r3, 0x2
	lmw r26, 0x48(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_cam3d_road_shift_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	cmpwi r31, 0x0
	beq @1
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 27, 25
	sth r0, 0x0(r3)
	b @2
	@1:
	lhz r0, 0x0(r3)
	ori r0, r0, 0x20
	sth r0, 0x0(r3)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stw r30, 0x8(r1)
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lwz r0, 0xc(r3)
	lis r4, 0x1062
	lwz r7, 0x10(r3)
	addi r6, r4, 0x4dd3
	lis r5, 0x8000
	li r4, 0x0
	stw r0, 0x58(r3)
	li r0, 0x1
	stw r7, 0x5c(r3)
	lwz r7, 0x14(r3)
	stw r7, 0x60(r3)
	lwz r8, 0x18(r3)
	lwz r7, 0x1c(r3)
	stw r8, 0x64(r3)
	stw r7, 0x68(r3)
	lwz r7, 0x20(r3)
	stw r7, 0x6c(r3)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r3)
	stw r7, 0x70(r3)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r30, r5
	stw r5, 0x7c(r3)
	stw r4, 0x78(r3)
	sth r0, 0x4(r3)
	stb r31, 0x80(r3)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_cam3d_evt_set_rel_dir(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x130(r1)
	mflr r0
	stw r0, 0x134(r1)
	stfd f31, 0x120(r1)
	psq_st f31, 0x128(r1), 0, 0
	stfd f30, 0x110(r1)
	psq_st f30, 0x118(r1), 0, 0
	stfd f29, 0x100(r1)
	psq_st f29, 0x108(r1), 0, 0
	stfd f28, 0xf0(r1)
	psq_st f28, 0xf8(r1), 0, 0
	stfd f27, 0xe0(r1)
	psq_st f27, 0xe8(r1), 0, 0
	stfd f26, 0xd0(r1)
	psq_st f26, 0xd8(r1), 0, 0
	stfd f25, 0xc0(r1)
	psq_st f25, 0xc8(r1), 0, 0
	stw r31, 0xbc(r1)
	stw r30, 0xb8(r1)
	stw r29, 0xb4(r1)
	stw r28, 0xb0(r1)
	mr r29, r3
	lwz r28, 0x18(r3)
	lwz r4, 0x0(r28)
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x84(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x4(r28)
	stw r0, 0x80(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x80(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x8c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x8(r28)
	stw r0, 0x88(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x88(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x94(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0xc(r28)
	stw r0, 0x90(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x90(r1)
	fsubs f29, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x9c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x10(r28)
	stw r0, 0x98(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0x98(r1)
	fsubs f28, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0xa4(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x14(r28)
	stw r0, 0xa0(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0xa0(r1)
	fsubs f27, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x18(r28)
	stw r0, 0xa8(r1)
	mr r3, r29
	lfd f1, 0x0(r5)
	lfd f0, 0xa8(r1)
	fsubs f26, f0, f1
	bl evtGetValue
	lwz r4, 0x1c(r28)
	mr r28, r3
	mr r3, r29
	bl evtGetValue
	mr r29, r3
	li r3, 0x4
	bl camGetPtr
	lfs f0, 0x114(r3)
	li r3, 0x4
	fneg f25, f0
	bl camGetPtr
	mr r30, r3
	bl marioGetPtr
	lis r5, vec3_802c5f98@ha
	lwzu r10, vec3_802c5f98@l(r5)
	lis r4, vec3_802c5fa4@ha
	lfs f0, float_deg2rad_8041af34(r2)
	addi r7, r4, vec3_802c5fa4@l
	lwz r9, 0x4(r5)
	lwz r8, 0x8(r5)
	mr r31, r3
	lwz r6, 0x0(r7)
	fmuls f1, f0, f25
	lwz r5, 0x4(r7)
	addi r3, r1, 0x50
	lwz r0, 0x8(r7)
	li r4, 0x59
	stw r10, 0x14(r1)
	stw r9, 0x18(r1)
	stw r8, 0x1c(r1)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f31, 0x14(r1)
	stfs f30, 0x18(r1)
	lwz r9, 0x14(r1)
	stfs f29, 0x1c(r1)
	lwz r8, 0x18(r1)
	stfs f28, 0x8(r1)
	lwz r7, 0x1c(r1)
	stfs f27, 0xc(r1)
	lwz r6, 0x8(r1)
	stfs f26, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r9, 0x2c(r1)
	stw r8, 0x30(r1)
	stw r7, 0x34(r1)
	stw r6, 0x20(r1)
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	bl PSMTXRotRad
	addi r4, r1, 0x2c
	addi r3, r1, 0x50
	mr r5, r4
	bl PSMTXMultVec
	addi r4, r1, 0x20
	addi r3, r1, 0x50
	mr r5, r4
	bl PSMTXMultVec
	addi r3, r31, 0x8c
	addi r4, r1, 0x20
	addi r5, r1, 0x38
	bl PSVECAdd
	addi r3, r1, 0x38
	addi r4, r1, 0x2c
	addi r5, r1, 0x44
	bl PSVECAdd
	lwz r0, 0xc(r30)
	lis r3, 0x1062
	lwz r7, 0x10(r30)
	addi r6, r3, 0x4dd3
	lis r5, 0x8000
	li r4, 0x0
	stw r0, 0x58(r30)
	li r0, 0x3
	li r3, 0x2
	stw r7, 0x5c(r30)
	lwz r7, 0x14(r30)
	stw r7, 0x60(r30)
	lwz r8, 0x18(r30)
	lwz r7, 0x1c(r30)
	stw r8, 0x64(r30)
	stw r7, 0x68(r30)
	lwz r7, 0x20(r30)
	stw r7, 0x6c(r30)
	lwz r8, 0x44(r1)
	lwz r7, 0x48(r1)
	stw r8, 0x40(r30)
	stw r7, 0x44(r30)
	lwz r7, 0x4c(r1)
	stw r7, 0x48(r30)
	lwz r8, 0x38(r1)
	lwz r7, 0x3c(r1)
	stw r8, 0x4c(r30)
	stw r7, 0x50(r30)
	lwz r7, 0x40(r1)
	stw r7, 0x54(r30)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r30)
	stw r7, 0x70(r30)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r28, r5
	stw r5, 0x7c(r30)
	stw r4, 0x78(r30)
	sth r0, 0x4(r30)
	stb r29, 0x80(r30)
	psq_l f31, 0x128(r1), 0, 0
	lfd f31, 0x120(r1)
	psq_l f30, 0x118(r1), 0, 0
	lfd f30, 0x110(r1)
	psq_l f29, 0x108(r1), 0, 0
	lfd f29, 0x100(r1)
	psq_l f28, 0xf8(r1), 0, 0
	lfd f28, 0xf0(r1)
	psq_l f27, 0xe8(r1), 0, 0
	lfd f27, 0xe0(r1)
	psq_l f26, 0xd8(r1), 0, 0
	lfd f26, 0xd0(r1)
	psq_l f25, 0xc8(r1), 0, 0
	lfd f25, 0xc0(r1)
	lwz r31, 0xbc(r1)
	lwz r30, 0xb8(r1)
	lwz r29, 0xb4(r1)
	lwz r0, 0x134(r1)
	lwz r28, 0xb0(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm s32 evt_cam3d_evt_set_npc_rel(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stmw r27, 0x8c(r1)
	mr r27, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r28, r3
	mr r3, r27
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x54(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x8(r29)
	stw r0, 0x50(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x50(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x5c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0xc(r29)
	stw r0, 0x58(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x58(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x64(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x10(r29)
	stw r0, 0x60(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x60(r1)
	fsubs f29, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x6c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x14(r29)
	stw r0, 0x68(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x68(r1)
	fsubs f28, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x74(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x18(r29)
	stw r0, 0x70(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x70(r1)
	fsubs f27, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x7c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x1c(r29)
	stw r0, 0x78(r1)
	mr r3, r27
	lfd f1, 0x0(r5)
	lfd f0, 0x78(r1)
	fsubs f26, f0, f1
	bl evtGetValue
	lwz r4, 0x20(r29)
	mr r29, r3
	mr r3, r27
	bl evtGetValue
	mr r30, r3
	li r3, 0x4
	bl camGetPtr
	mr r31, r3
	mr r3, r27
	mr r4, r28
	bl evtNpcNameToPtr
	lis r5, vec3_802c5f80@ha
	lwzu r11, vec3_802c5f80@l(r5)
	lis r4, vec3_802c5f8c@ha
	addi r3, r3, 0x8c
	addi r8, r4, vec3_802c5f8c@l
	lwz r10, 0x4(r5)
	lwz r9, 0x8(r5)
	addi r4, r1, 0x20
	lwz r7, 0x0(r8)
	addi r5, r1, 0x38
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r11, 0x14(r1)
	stw r10, 0x18(r1)
	stw r9, 0x1c(r1)
	stw r7, 0x8(r1)
	stw r6, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f31, 0x14(r1)
	stfs f30, 0x18(r1)
	lwz r10, 0x14(r1)
	stfs f29, 0x1c(r1)
	lwz r9, 0x18(r1)
	stfs f28, 0x8(r1)
	lwz r8, 0x1c(r1)
	stfs f27, 0xc(r1)
	lwz r7, 0x8(r1)
	stfs f26, 0x10(r1)
	lwz r6, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r10, 0x2c(r1)
	stw r9, 0x30(r1)
	stw r8, 0x34(r1)
	stw r7, 0x20(r1)
	stw r6, 0x24(r1)
	stw r0, 0x28(r1)
	bl PSVECAdd
	addi r3, r1, 0x38
	addi r4, r1, 0x2c
	addi r5, r1, 0x44
	bl PSVECAdd
	lwz r0, 0xc(r31)
	lis r3, 0x1062
	lwz r7, 0x10(r31)
	addi r6, r3, 0x4dd3
	lis r5, 0x8000
	li r4, 0x0
	stw r0, 0x58(r31)
	li r0, 0x3
	li r3, 0x2
	stw r7, 0x5c(r31)
	lwz r7, 0x14(r31)
	stw r7, 0x60(r31)
	lwz r8, 0x18(r31)
	lwz r7, 0x1c(r31)
	stw r8, 0x64(r31)
	stw r7, 0x68(r31)
	lwz r7, 0x20(r31)
	stw r7, 0x6c(r31)
	lwz r8, 0x44(r1)
	lwz r7, 0x48(r1)
	stw r8, 0x40(r31)
	stw r7, 0x44(r31)
	lwz r7, 0x4c(r1)
	stw r7, 0x48(r31)
	lwz r8, 0x38(r1)
	lwz r7, 0x3c(r1)
	stw r8, 0x4c(r31)
	stw r7, 0x50(r31)
	lwz r7, 0x40(r1)
	stw r7, 0x54(r31)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r31)
	stw r7, 0x70(r31)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r29, r5
	stw r5, 0x7c(r31)
	stw r4, 0x78(r31)
	sth r0, 0x4(r31)
	stb r30, 0x80(r31)
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	lmw r27, 0x8c(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm s32 evt_cam3d_evt_set_rel(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stfd f30, 0xa0(r1)
	psq_st f30, 0xa8(r1), 0, 0
	stfd f29, 0x90(r1)
	psq_st f29, 0x98(r1), 0, 0
	stfd f28, 0x80(r1)
	psq_st f28, 0x88(r1), 0, 0
	stfd f27, 0x70(r1)
	psq_st f27, 0x78(r1), 0, 0
	stfd f26, 0x60(r1)
	psq_st f26, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x24(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x4(r29)
	stw r0, 0x20(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x20(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x2c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x8(r29)
	stw r0, 0x28(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x28(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x34(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0xc(r29)
	stw r0, 0x30(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x30(r1)
	fsubs f29, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x3c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x10(r29)
	stw r0, 0x38(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x38(r1)
	fsubs f28, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x44(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x14(r29)
	stw r0, 0x40(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x40(r1)
	fsubs f27, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x4c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x18(r29)
	stw r0, 0x48(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x48(r1)
	fsubs f26, f0, f1
	bl evtGetValue
	lwz r4, 0x1c(r29)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	mr r30, r3
	li r3, 0x4
	bl camGetPtr
	mr r31, r3
	bl marioGetPtr
	lfs f2, 0x8c(r3)
	lis r4, 0x1062
	lfs f1, 0x90(r3)
	addi r6, r4, 0x4dd3
	lfs f0, 0x94(r3)
	fadds f3, f2, f28
	lwz r3, 0xc(r31)
	fadds f4, f1, f27
	lwz r0, 0x10(r31)
	fadds f5, f0, f26
	fadds f2, f31, f3
	stw r3, 0x58(r31)
	fadds f1, f30, f4
	fadds f0, f29, f5
	lis r5, 0x8000
	stw r0, 0x5c(r31)
	li r4, 0x0
	li r0, 0x3
	lwz r7, 0x14(r31)
	stfs f2, 0x14(r1)
	li r3, 0x2
	stw r7, 0x60(r31)
	lwz r9, 0x14(r1)
	lwz r7, 0x18(r31)
	lwz r8, 0x1c(r31)
	stfs f1, 0x18(r1)
	stw r7, 0x64(r31)
	lwz r7, 0x18(r1)
	stw r8, 0x68(r31)
	lwz r8, 0x20(r31)
	stfs f0, 0x1c(r1)
	stw r8, 0x6c(r31)
	lwz r8, 0x1c(r1)
	stw r9, 0x40(r31)
	stw r7, 0x44(r31)
	stfs f3, 0x8(r1)
	lwz r7, 0x8(r1)
	stw r8, 0x48(r31)
	stfs f4, 0xc(r1)
	lwz r8, 0xc(r1)
	stw r7, 0x4c(r31)
	stfs f5, 0x10(r1)
	lwz r7, 0x10(r1)
	stw r8, 0x50(r31)
	stw r7, 0x54(r31)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r31)
	stw r7, 0x70(r31)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r29, r5
	stw r5, 0x7c(r31)
	stw r4, 0x78(r31)
	sth r0, 0x4(r31)
	stb r30, 0x80(r31)
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	psq_l f30, 0xa8(r1), 0, 0
	lfd f30, 0xa0(r1)
	psq_l f29, 0x98(r1), 0, 0
	lfd f29, 0x90(r1)
	psq_l f28, 0x88(r1), 0, 0
	lfd f28, 0x80(r1)
	psq_l f27, 0x78(r1), 0, 0
	lfd f27, 0x70(r1)
	psq_l f26, 0x68(r1), 0, 0
	lfd f26, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r0, 0xc4(r1)
	lwz r29, 0x54(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stfd f30, 0xa0(r1)
	psq_st f30, 0xa8(r1), 0, 0
	stfd f29, 0x90(r1)
	psq_st f29, 0x98(r1), 0, 0
	stfd f28, 0x80(r1)
	psq_st f28, 0x88(r1), 0, 0
	stfd f27, 0x70(r1)
	psq_st f27, 0x78(r1), 0, 0
	stfd f26, 0x60(r1)
	psq_st f26, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	mr r31, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x24(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x4(r30)
	stw r0, 0x20(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x20(r1)
	fsubs f31, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x2c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x8(r30)
	stw r0, 0x28(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x28(r1)
	fsubs f30, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x34(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0xc(r30)
	stw r0, 0x30(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x30(r1)
	fsubs f29, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x3c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x10(r30)
	stw r0, 0x38(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x38(r1)
	fsubs f28, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x44(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x14(r30)
	stw r0, 0x40(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x40(r1)
	fsubs f27, f0, f1
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x4c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	lwz r4, 0x18(r30)
	stw r0, 0x48(r1)
	mr r3, r31
	lfd f1, 0x0(r5)
	lfd f0, 0x48(r1)
	fsubs f26, f0, f1
	bl evtGetValue
	lwz r4, 0x1c(r30)
	mr r30, r3
	mr r3, r31
	bl evtGetValue
	mr r31, r3
	li r3, 0x4
	bl camGetPtr
	lis r4, vec3_802c5f50@ha
	lis r5, vec3_802c5f5c@ha
	addi r6, r4, vec3_802c5f50@l
	lwz r8, 0xc(r3)
	addi r7, r5, vec3_802c5f5c@l
	lwz r28, 0x0(r6)
	lwz r29, 0x4(r6)
	lis r5, 0x8000
	lwz r9, 0x8(r6)
	lis r4, 0x1062
	lwz r12, 0x0(r7)
	addi r6, r4, 0x4dd3
	lwz r11, 0x4(r7)
	li r4, 0x0
	lwz r10, 0x8(r7)
	li r0, 0x3
	lwz r7, 0x10(r3)
	stw r28, 0x14(r1)
	stw r8, 0x58(r3)
	stw r7, 0x5c(r3)
	lwz r7, 0x14(r3)
	stw r29, 0x18(r1)
	stw r7, 0x60(r3)
	stw r9, 0x1c(r1)
	lwz r8, 0x18(r3)
	lwz r7, 0x1c(r3)
	stfs f31, 0x14(r1)
	stw r8, 0x64(r3)
	lwz r9, 0x14(r1)
	stw r7, 0x68(r3)
	lwz r7, 0x20(r3)
	stfs f29, 0x1c(r1)
	stw r7, 0x6c(r3)
	lwz r8, 0x1c(r1)
	stfs f30, 0x18(r1)
	stw r12, 0x8(r1)
	lwz r7, 0x18(r1)
	stw r9, 0x40(r3)
	stw r11, 0xc(r1)
	stw r7, 0x44(r3)
	stfs f28, 0x8(r1)
	stw r10, 0x10(r1)
	lwz r7, 0x8(r1)
	stw r8, 0x48(r3)
	stfs f27, 0xc(r1)
	lwz r8, 0xc(r1)
	stw r7, 0x4c(r3)
	stfs f26, 0x10(r1)
	lwz r7, 0x10(r1)
	stw r8, 0x50(r3)
	stw r7, 0x54(r3)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r3)
	stw r7, 0x70(r3)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r30, r5
	stw r5, 0x7c(r3)
	stw r4, 0x78(r3)
	sth r0, 0x4(r3)
	stb r31, 0x80(r3)
	li r3, 0x2
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	psq_l f30, 0xa8(r1), 0, 0
	lfd f30, 0xa0(r1)
	psq_l f29, 0x98(r1), 0, 0
	lfd f29, 0x90(r1)
	psq_l f28, 0x88(r1), 0, 0
	lfd f28, 0x80(r1)
	psq_l f27, 0x78(r1), 0, 0
	lfd f27, 0x70(r1)
	psq_l f26, 0x68(r1), 0, 0
	lfd f26, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r0, 0xc4(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm s32 evt_cam3d_evt_set_at(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stmw r26, 0x58(r1)
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r26, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r27, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0xc(r29)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x10(r29)
	mr r28, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x14(r29)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	mr r30, r3
	li r3, 0x4
	bl camGetPtr
	lis r6, 0x4330
	xoris r4, r26, 0x8000
	xoris r5, r27, 0x8000
	stw r4, 0x34(r1)
	xoris r0, r31, 0x8000
	lis r7, double_to_int_802c5ff0@ha
	stw r6, 0x30(r1)
	mr r31, r3
	lis r8, vec3_802c5f38@ha
	lwzu r10, vec3_802c5f38@l(r8)
	stw r5, 0x3c(r1)
	addi r3, r1, 0x20
	lwz r9, 0x4(r8)
	addi r4, r31, 0xc
	stw r6, 0x38(r1)
	addi r5, r1, 0x14
	lwz r8, 0x8(r8)
	lfd f3, double_to_int_802c5ff0@l(r7)
	lfd f1, 0x30(r1)
	lfd f0, 0x38(r1)
	fsubs f2, f1, f3
	stw r10, 0x8(r1)
	fsubs f1, f0, f3
	stw r9, 0xc(r1)
	stfs f2, 0x8(r1)
	lwz r7, 0x8(r1)
	stw r0, 0x44(r1)
	stw r6, 0x40(r1)
	lfd f0, 0x40(r1)
	stfs f1, 0xc(r1)
	fsubs f0, f0, f3
	stw r8, 0x10(r1)
	lwz r6, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r0, 0x10(r1)
	stw r7, 0x20(r1)
	stw r6, 0x24(r1)
	stw r0, 0x28(r1)
	bl PSVECSubtract
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x4c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	addi r3, r1, 0x14
	stw r0, 0x48(r1)
	mr r4, r3
	lfd f2, 0x0(r5)
	lfd f1, 0x48(r1)
	lfs f0, float_100_8041af30(r2)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	bl PSVECScale
	addi r3, r1, 0x14
	addi r4, r31, 0xc
	mr r5, r3
	bl PSVECAdd
	lwz r0, 0xc(r31)
	lis r3, 0x1062
	lwz r7, 0x10(r31)
	addi r6, r3, 0x4dd3
	lis r5, 0x8000
	li r4, 0x0
	stw r0, 0x58(r31)
	li r0, 0x3
	li r3, 0x2
	stw r7, 0x5c(r31)
	lwz r7, 0x14(r31)
	stw r7, 0x60(r31)
	lwz r8, 0x18(r31)
	lwz r7, 0x1c(r31)
	stw r8, 0x64(r31)
	stw r7, 0x68(r31)
	lwz r7, 0x20(r31)
	stw r7, 0x6c(r31)
	lwz r8, 0x14(r1)
	lwz r7, 0x18(r1)
	stw r8, 0x40(r31)
	stw r7, 0x44(r31)
	lwz r7, 0x1c(r1)
	stw r7, 0x48(r31)
	lwz r8, 0x20(r1)
	lwz r7, 0x24(r1)
	stw r8, 0x4c(r31)
	stw r7, 0x50(r31)
	lwz r7, 0x28(r1)
	stw r7, 0x54(r31)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r31)
	stw r7, 0x70(r31)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r29, r5
	stw r5, 0x7c(r31)
	stw r4, 0x78(r31)
	sth r0, 0x4(r31)
	stb r30, 0x80(r31)
	lmw r26, 0x58(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 evt_cam3d_evt_zoom_in(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stmw r27, 0x4c(r1)
	mr r30, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r27, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r28, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0xc(r29)
	mr r29, r3
	mr r3, r30
	bl evtGetValue
	mr r30, r3
	li r3, 0x4
	bl camGetPtr
	mr r31, r3
	addi r5, r1, 0x8
	addi r3, r31, 0x18
	addi r4, r31, 0xc
	bl PSVECSubtract
	xoris r3, r27, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c5ff0@ha
	stw r3, 0x1c(r1)
	addi r5, r4, double_to_int_802c5ff0@l
	addi r3, r1, 0x8
	stw r0, 0x18(r1)
	mr r4, r3
	lfd f2, 0x0(r5)
	lfd f1, 0x18(r1)
	lfs f0, float_100_8041af30(r2)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	bl PSVECScale
	addi r3, r1, 0x8
	addi r4, r31, 0xc
	mr r5, r3
	bl PSVECAdd
	lwz r3, 0xc(r31)
	lwz r0, 0x10(r31)
	stw r3, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0x14(r31)
	stw r0, 0x60(r31)
	lwz r3, 0x18(r31)
	lwz r0, 0x1c(r31)
	stw r3, 0x64(r31)
	stw r0, 0x68(r31)
	lwz r0, 0x20(r31)
	stw r0, 0x6c(r31)
	lwz r3, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r3, 0x40(r31)
	stw r0, 0x44(r31)
	lwz r0, 0x10(r1)
	stw r0, 0x48(r31)
	lwz r3, 0x18(r31)
	lwz r0, 0x1c(r31)
	stw r3, 0x4c(r31)
	stw r0, 0x50(r31)
	lwz r0, 0x20(r31)
	stw r0, 0x54(r31)
	lfs f1, 0x114(r31)
	bl cos
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x24(r1)
	lis r4, double_to_int_802c5ff0@ha
	frsp f3, f1
	lfd f2, double_to_int_802c5ff0@l(r4)
	stw r0, 0x20(r1)
	lfs f0, 0x40(r31)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmadds f0, f1, f3, f0
	stfs f0, 0x40(r31)
	lfs f1, 0x114(r31)
	bl sin
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x2c(r1)
	lis r4, double_to_int_802c5ff0@ha
	frsp f3, f1
	lfd f2, double_to_int_802c5ff0@l(r4)
	stw r0, 0x28(r1)
	lfs f0, 0x48(r31)
	lfd f1, 0x28(r1)
	fsubs f1, f1, f2
	fmadds f0, f1, f3, f0
	stfs f0, 0x48(r31)
	lfs f1, 0x114(r31)
	bl cos
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x34(r1)
	lis r4, double_to_int_802c5ff0@ha
	frsp f3, f1
	lfd f2, double_to_int_802c5ff0@l(r4)
	stw r0, 0x30(r1)
	lfs f0, 0x4c(r31)
	lfd f1, 0x30(r1)
	fsubs f1, f1, f2
	fmadds f0, f1, f3, f0
	stfs f0, 0x4c(r31)
	lfs f1, 0x114(r31)
	bl sin
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x3c(r1)
	lis r4, double_to_int_802c5ff0@ha
	lfd f2, double_to_int_802c5ff0@l(r4)
	lis r3, 0x1062
	stw r0, 0x38(r1)
	frsp f3, f1
	addi r6, r3, 0x4dd3
	lfs f0, 0x54(r31)
	lfd f1, 0x38(r1)
	lis r5, 0x8000
	li r4, 0x0
	fsubs f1, f1, f2
	li r0, 0x3
	li r3, 0x2
	fmadds f0, f1, f3, f0
	stfs f0, 0x54(r31)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r31)
	stw r7, 0x70(r31)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r28, r5
	stw r5, 0x7c(r31)
	stw r4, 0x78(r31)
	sth r0, 0x4(r31)
	stb r30, 0x80(r31)
	lmw r27, 0x4c(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stmw r24, 0x20(r1)
	mr r29, r3
	lis r5, vec3_802c5f38@ha
	lwz r27, 0x18(r3)
	mr r30, r4
	addi r26, r5, vec3_802c5f38@l
	lwz r4, 0x0(r27)
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r25, r3
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r27)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r27)
	mr r3, r29
	bl evtGetValue
	cmpwi r30, 0x0
	lwz r31, 0x0(r29)
	lwz r30, 0x4(r29)
	mr r27, r3
	beq @1
	li r3, 0x0
	li r0, -0x1
	stw r3, 0x78(r29)
	and r4, r31, r0
	and r0, r30, r0
	stw r4, 0x7c(r29)
	stw r0, 0x80(r29)
	stw r3, 0x84(r29)
	stw r4, 0x88(r29)
	stw r0, 0x8c(r29)
	@1:
	lwz r3, 0x78(r29)
	addi r0, r3, 0x1
	stw r0, 0x78(r29)
	lwz r3, 0x78(r29)
	slwi r0, r3, 30
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 2
	add r0, r0, r3
	stw r0, 0x78(r29)
	lwz r0, 0x78(r29)
	cmpwi r0, 0x2
	bge @2
	mr r3, r25
	bl camGetPtr
	fmr f1, f31
	lfs f3, float_0_8041af2c(r2)
	fmr f2, f30
	addi r3, r3, 0x1a0
	bl PSMTX44Trans
	b @3
	@2:
	mr r3, r25
	bl camGetPtr
	fneg f1, f31
	lfs f3, float_0_8041af2c(r2)
	fneg f2, f30
	addi r3, r3, 0x1a0
	bl PSMTX44Trans
	@3:
	mr r3, r25
	bl camGetPtr
	lhz r0, 0x0(r3)
	cmpwi r27, 0x0
	ori r0, r0, 0x8
	sth r0, 0x0(r3)
	beq @4
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r3, r3, 0x4dd3
	lwz r4, 0x80(r29)
	li r5, 0x0
	srwi r0, r0, 2
	lwz r6, 0x7c(r29)
	mulhwu r0, r3, r0
	subfc r4, r4, r30
	subfe r3, r6, r31
	srwi r6, r0, 6
	bl __div2u
	srawi r5, r27, 31
	subfc r0, r4, r27
	subfe r0, r3, r5
	subfe r0, r24, r24
	neg. r0, r0
	beq @4
	mr r3, r25
	bl camGetPtr
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 29, 27
	sth r0, 0x0(r3)
	li r3, 0x0
	bl padRumbleOff
	li r3, 0x2
	b @5
	@4:
	fmuls f1, f30, f30
	lfs f0, float_0_8041af2c(r2)
	fmadds f4, f31, f31, f1
	fcmpo cr0, f4, f0
	ble @6
	frsqrte f1, f4
	lfd f3, 0xd8(r26)
	lfd f2, 0xe0(r26)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b @7
	@6:
	lfd f0, 0xe8(r26)
	fcmpo cr0, f4, f0
	bge @8
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b @7
	@8:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq @9
	bge @10
	cmpwi r3, 0x0
	beq @11
	b @10
	@9:
	clrlwi. r0, r4, 9
	beq @12
	li r0, 0x1
	b @13
	@12:
	li r0, 0x2
	b @13
	@11:
	clrlwi. r0, r4, 9
	beq @14
	li r0, 0x5
	b @13
	@14:
	li r0, 0x3
	b @13
	@10:
	li r0, 0x4
	@13:
	cmpwi r0, 0x1
	bne @7
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	@7:
	lfs f1, float_13000_8041af38(r2)
	lfs f0, float_1_8041af40(r2)
	fmuls f2, f1, f4
	lfs f1, float_50_8041af3c(r2)
	fsubs f0, f0, f4
	lwz r27, 0x88(r29)
	lwz r24, 0x8c(r29)
	fctiwz f2, f2
	fmuls f0, f1, f0
	stfd f2, 0x10(r1)
	fctiwz f0, f0
	lwz r25, 0x14(r1)
	stfd f0, 0x18(r1)
	cmpwi r25, 0x0
	lwz r26, 0x1c(r1)
	beq @15
	cmpwi r26, 0x0
	beq @15
	lwz r0, 0x84(r29)
	cmpwi r0, 0x0
	bne @16
	li r3, 0x0
	bl padRumbleOn
	lis r3, 0x8000
	lis r5, 0x1062
	lwz r0, 0xf8(r3)
	subfc r4, r24, r30
	addi r5, r5, 0x4dd3
	subfe r3, r27, r31
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2u
	srawi r5, r25, 31
	subfc r0, r4, r25
	subfe r0, r3, r5
	subfe r0, r28, r28
	neg. r0, r0
	beq @15
	lwz r3, 0x84(r29)
	li r0, -0x1
	subfic r4, r3, 0x1
	and r3, r31, r0
	stw r4, 0x84(r29)
	and r0, r30, r0
	stw r3, 0x88(r29)
	stw r0, 0x8c(r29)
	b @15
	@16:
	li r3, 0x0
	bl padRumbleOff
	lis r3, 0x8000
	lis r5, 0x1062
	lwz r0, 0xf8(r3)
	subfc r4, r24, r30
	addi r5, r5, 0x4dd3
	subfe r3, r27, r31
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2u
	srawi r5, r26, 31
	subfc r0, r4, r26
	subfe r0, r3, r5
	subfe r0, r28, r28
	neg. r0, r0
	beq @15
	lwz r3, 0x84(r29)
	li r0, -0x1
	subfic r4, r3, 0x1
	and r3, r31, r0
	stw r4, 0x84(r29)
	and r0, r30, r0
	stw r3, 0x88(r29)
	stw r0, 0x8c(r29)
	@15:
	li r3, 0x0
	@5:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	lmw r24, 0x20(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_cam_get_at(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	bl camGetPtr
	mr r31, r3
	lwz r4, 0x4(r30)
	lfs f1, 0x18(r3)
	mr r3, r29
	bl evtSetFloat
	lwz r4, 0x8(r30)
	mr r3, r29
	lfs f1, 0x1c(r31)
	bl evtSetFloat
	lwz r4, 0xc(r30)
	mr r3, r29
	lfs f1, 0x20(r31)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_cam_get_pos(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	bl camGetPtr
	mr r31, r3
	lwz r4, 0x4(r30)
	lfs f1, 0xc(r3)
	mr r3, r29
	bl evtSetFloat
	lwz r4, 0x8(r30)
	mr r3, r29
	lfs f1, 0x10(r31)
	bl evtSetFloat
	lwz r4, 0xc(r30)
	mr r3, r29
	lfs f1, 0x14(r31)
	bl evtSetFloat
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_cam_ctrl_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	cmpwi r3, 0x0
	beq @1
	mr r3, r31
	bl camCtrlOn
	b @2
	@1:
	mr r3, r31
	bl camCtrlOff
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
