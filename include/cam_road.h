#pragma once

#include "dolphin/types.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>

typedef struct CamRoadCurve {
    char name[0x28];
    s32 off;               // 0x28
    u8 pad[0xb8 - 0x2c];
} CamRoadCurve;
typedef struct CamRoadCam {
    char name[0x20];       // 0x0
    u32 f_20;              // 0x20
    u8 pad1[0x40 - 0x24];
    s32 f_40;              // 0x40
    s32 f_44;              // 0x44
    u8 pad2[0x7c - 0x48];
    f32 f_7c;              // 0x7c
} CamRoadCam;
typedef struct CamRoadMap {
    u8 pad0[0x44];
    char version[0x84];    // 0x44
    s32 curveNum;          // 0xc8
    u8 pad1[0xe8 - 0xcc];
    Vec* f_e8;             // 0xe8
    CamRoadCurve* curves;  // 0xec
    void* f_f0;
    void* f_f4;
    void* f_f8;
    void* f_fc;
    void* f_100;
    void* f_104;
    void* f_108;
} CamRoadMap;
typedef struct CamRoadState {
    s32 on;                // 0x00
    s32 f_04;              // 0x04
    s32 f_08;              // 0x08
    f32 in[6];             // 0x0c
    CamRoadCam* cam;       // 0x24
    Vec pos;               // 0x28
    Vec dir;               // 0x34
    f32 dist;              // 0x40
    f32 angle;             // 0x44
    f32 rot;               // 0x48
    f32 f_4c;              // 0x4c
    OSTime time;           // 0x50
    f32 f_58;              // 0x58
    f32 shiftXRate;        // 0x5c
} CamRoadState;
typedef struct CamRoadOut {
    Vec f_0;
    Vec pos;               // 0xc
    Vec at;                // 0x18
} CamRoadOut;
typedef struct CamRoadWork {
    CamRoadMap* map;       // 0x0
    u8 pad0[4];
    CamRoadState cur;      // 0x8
    CamRoadState next;     // 0x68
    s32 f_c8;              // 0xc8
    s32 hokanType;         // 0xcc
    f32 hokanT;            // 0xd0
    f32 hokanSpeed;        // 0xd4
    CamRoadState prev;     // 0xd8
    CamRoadState start;    // 0x138
    u32 cmpFlags;          // 0x198
    f32 f_19c[11];         // 0x19c
    OSTime time;           // 0x1c8
    u32 state;             // 0x1d0
    f32 out[6];            // 0x1d4
    f32 in[6];             // 0x1ec
    s32 f_204;
    s32 f_208;
    u8 pad6[0x210 - 0x20c];
} CamRoadWork;

CamRoadWork* camRoadGetWorkPtr(void);

f32 camRoadGetCurrentShiftXRate(void);
void camRoadReset(void);
