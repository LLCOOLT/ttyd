// cam_road.c: the camera road system (CamRoadCurve records and the road camera entry points that move the field camera).
#pragma once

#include "dolphin/types.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>

/* camera road curve record (0xB8): the road cameras, collision curves and the curve table all use it */
typedef struct CamRoadCurve {
    char name[0x20]; // 0x0
    u32 fixYOn;      // 0x20, version 1.01: the camera height is fixedY instead of the target height
    f32 fixedY;      // 0x24
    u32 off;         // 0x28
    u8 pad_2c[0x40 - 0x2c];
    s32 idxA; // 0x40
    s32 idxB; // 0x44
    f32 limA; // 0x48
    f32 limB; // 0x4c
    u8 pad_50[0x58 - 0x50];
    f32 dist; // 0x58, camera distance from the curve
    u8 pad_5c[0x64 - 0x5c];
    f32 angle; // 0x64, elevation angle
    u8 pad_68[0x70 - 0x68];
    f32 rot; // 0x70, look-at turn
    u8 pad_74[0x7c - 0x74];
    f32 shiftXRate; // 0x7c, sideways shift allowed (camRoadGetCurrentShiftXRate)
    u8 pad_80[0x84 - 0x80];
    s32 flag; // 0x84
    u8 pad_88[0x8c - 0x88];
    f32 height; // 0x8c
    u8 pad_90[0xa0 - 0x90];
    s32 vtxOfs;     // 0xa0, into CamRoadMap.curveVtx
    s32 vtxNum;     // 0xa4
    s32 grpOfs;     // 0xa8, into CamRoadMap.groups
    s32 grpNum;     // 0xac
    s32 collGrpOfs; // 0xb0, into CamRoadMap.collGroups: the group the camera position is clamped to
    s32 collGrpNum; // 0xb4, only tested for nonzero (the first group is used)
} CamRoadCurve;
typedef struct CamRoadGroup {
    u8 pad_00[0x58];
    s32 vtxOfs; // 0x58, into CamRoadMap.groupVtx
    u8 pad_5C[4];
    s32 stripOfs; // 0x60, into CamRoadMap.strips (or curveVtx for collision)
    s32 stripNum; // 0x64
} CamRoadGroup;
typedef struct CamRoadStrip {
    s32 idxOfs; // 0x0, into CamRoadMap.stripIdx
    s32 num;    // 0x4
} CamRoadStrip;
typedef struct CamRoadMap {
    u8 pad_00[0x44];
    char version[0x84]; // 0x44
    s32 curveNum;       // 0xc8
    u8 pad_CC[0xe8 - 0xcc];
    Vec* projection;          // 0xe8, x fovY, y aspect, z far
    CamRoadCurve* curves;     // 0xec
    CamRoadGroup* groups;     // 0xf0, floor groups that pick a curve
    CamRoadStrip* strips;     // 0xf4, their triangle strips
    Vec* curveVtx;            // 0xf8, curve points, then as many directions
    Vec* groupVtx;            // 0xfc, floor group vertices
    s32* stripIdx;            // 0x100, strip vertex indices
    CamRoadGroup* collGroups; // 0x104, groups the camera position is clamped to
    void* extra;              // 0x108, Unknown: relocated on load, never read
} CamRoadMap;
typedef struct CamRoadState {
    s32 on;            // 0x00
    s32 onCurve;       // 0x04, the floor probe hit a curve this frame
    s32 hitFlags;      // 0x08, collisionCurve flags: 1 past a curve end, 2 clamped to a side limit; 1 during a free blend
    f32 in[6];         // 0x0c
    CamRoadCurve* cam; // 0x24
    Vec pos;           // 0x28
    Vec dir;           // 0x34
    f32 dist;          // 0x40
    f32 angle;         // 0x44
    f32 rot;           // 0x48
    f32 segment;       // 0x4c, curve point index the camera is at
    OSTime time;       // 0x50
    f32 shift;         // 0x58, the sideways shift (g) camRoadMain got
    f32 shiftXRate;    // 0x5c
} CamRoadState;
/* camera parameters a camera road produces (camdrv blends them into the live camera) */
typedef struct CameraParams {
    f32 fovY;   // 0x0
    f32 aspect; // 0x4
    f32 far;    // 0x8
    Vec pos;    // 0xc
    Vec at;     // 0x18
} CameraParams;
typedef struct CamRoadWork {
    CamRoadMap* map; // 0x0
    u8 pad_04[4];
    CamRoadState cur;   // 0x8
    CamRoadState next;  // 0x68
    s32 hokanOn;        // 0xc8, a blend between road states runs
    s32 hokanType;      // 0xcc
    f32 hokanT;         // 0xd0
    f32 hokanSpeed;     // 0xd4
    CamRoadState prev;  // 0xd8
    CamRoadState start; // 0x138
    u32 cmpFlags;       // 0x198
    f32 tuning[11];     // 0x19c, follow and blend tuning: 0/1 follow speeds, 2/3 recovery of the 4/5 scales
                        // (zeroed when a limit releases), 6-10 blend length per heading, angle, rot, dist, position
    OSTime time;        // 0x1c8
    u32 state;          // 0x1d0
    f32 out[6];         // 0x1d4
    f32 in[6];          // 0x1ec
    s32 keptIdx;        // 0x204, Unknown: -1 on setup, kept across camRoadReset, never read
    s32 unusedFlag;     // 0x208, Unknown: zeroed on setup and reset, never read
    u8 pad_20C[0x210 - 0x20c];
} CamRoadWork;

CamRoadWork* camRoadGetWorkPtr(void);
void camRoadMain(CameraParams* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);

f32 camRoadGetCurrentShiftXRate(void);
void camRoadReset(void);

s32 camRoadSetup(const char* name);

void camRoadCurveOn(const char* name);
