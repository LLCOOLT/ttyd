#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct DisplayList {
    u32 offset;      // 0x00 - Offset to vertex data
    u32 vertexCount; // 0x04 - Number of vertices
} DisplayList;

typedef struct PackedDisplayList {
    u32 offset;      // 0x00 - Offset to packed data
    u16 vertexCount; // 0x04 - Number of vertices
    u8 padding[2];   // 0x06
} PackedDisplayList;

typedef struct MapFileMesh {
    u8 unk0;              // 0x0
    u8 padding[2];        // 0x1
    u8 isPackedDisplay;   // 0x3, BOOL
    s32 displayListCount; // 0x4
    u32 elementMask;      // 0x8
    u32 vcdTableOffset;   // 0xC
  union {
    u32* normalLists[1];               // unpacked: stride 4, count = *normalLists[j]
    PackedDisplayList packedLists[1];  // packed:   stride 8, count = *(u16*)((u8*)packedLists[j].offset + 1)
} displayLists;  // at 0x10
} MapFileMesh;

typedef struct MapFileJointPart {
    void* material;    // 0x0
    MapFileMesh* mesh; // 0x4
} MapFileJointPart;

typedef struct MapJointDrawMode {
    u8 unk0[0x1 - 0x0];  // 0x0
    u8 cullMode;         // 0x1
    u8 unk2[0x8 - 0x2];  // 0x2
    s32 unk8;            // 0x8
    u8 unkC[0x10 - 0xC]; // 0xC
} MapJointDrawMode;

typedef struct MapFileJoint {
    const char* name;            // 0x0
    const char* type;            // 0x4
    struct MapFileJoint* parent; // 0x8
    struct MapFileJoint* child;  // 0xC
    struct MapFileJoint* next;   // 0x10
    struct MapFileJoint* prev;   // 0x14
    Vec scale;                   // 0x18
    Vec rotation;                // 0x24
    Vec translation;             // 0x30
    Vec bboxMin;                 // 0x3C
    Vec bboxMax;                 // 0x48
    u8 field_0x54[0x58 - 0x54];  // 0x54
    MapJointDrawMode* drawMode;  // 0x58
    s32 partCount;               // 0x5C
    MapFileJointPart parts[];    // 0x60+
} MapFileJoint;

typedef struct MapFileHeader {
    s32 fileSize;     // 0x0
    s32 dataSize;     // 0x4
    s32 relCount;     // 0x8, TODO: rename?
    s32 chunkCount;   // 0xC, TODO: rename?
    s32 unused;       // 0x10
    u8 reserved[0xC]; // 0x14
} MapFileHeader;

// entry in the chunk table
typedef struct MapFileChunk {
    u32 offset; // 0x0, relative offset into data
    u32 string; // 0x4, relative offset into strings
} MapFileChunk;

typedef struct MapFileInfo {
    const char* version; // 0x0
    MapFileJoint* joint; // 0x4
    const char* mapName; // 0x8
    const char* hitName; // 0xC
} MapFileInfo;

typedef struct MapHeader {
    MapFileHeader file;         // 0x0
    void* data;                 // 0x20, TODO re-type?
    void* rel;                  // 0x24, TODO: re-type?
    MapFileChunk* chunks;       // 0x28
    void* unused;               // 0x2C
    const char* strings;        // 0x30
    u8 field_0x34[0x3C - 0x34]; // 0x34
    s32 field_0x3C;             // 0x3C, dispFlags something?
    u8 field_0x40[0x44 - 0x40]; // 0x40
} MapHeader;

typedef struct MapObject {
    u32 flags;                   // 0x0
    union {
        u8 field_0x4[0x8 - 0x4]; // 0x4 (old name, used by linked evt_lect_*.c)
        struct {
            u8 blendMode;        // 0x4
            u8 unk5;             // 0x5
            u8 field_0x6[0x8 - 0x6]; // 0x6
        };
    };
    MapFileJoint* joints;        // 0x8
    GXColor color;               // 0xC
    Vec center;                  // 0x10
    Mtx modelWorldMtx;           // 0x1C
    Mtx localMtx;                // 0x4C
    Mtx unk7C;                   // 0x7C
    Mtx unkAC;                   // 0xAC
    s16 offscreenId;             // 0xDC
    s16 groupIndex;              // 0xDE
    struct MapObject* parent;    // 0xE0
    struct MapObject* child;     // 0xE4
    struct MapObject* next;      // 0xE8
    u16 screenRect[4];           // 0xEC, projected bounds (0x3FF when off screen)
    u8 field_0xF4[0x114 - 0xF4]; // 0xF4
    void* unk114;                // 0x114
    u8 field_0x118[0x134 - 0x118]; // 0x118
} MapObject;

typedef struct MapError {
    char field_0x0[32]; // 0x0
    s32 field_0x20;     // 0x20
} MapError;

typedef struct MapEntryAnimData {
    u16 flags;                // 0x0
    u8 field_0x2[0x20 - 0x2]; // 0x2
} MapEntryAnimData;

typedef struct MapEntry {
    s32 count;                     // 0x0
    u16 flags;                     // 0x4
    char name[16];                 // 0x6
    GXColor blend;                 // 0x16
    GXColor blend2;                // 0x1A
    GXColor color;                 // 0x1E
    u8 field_0x22[0x28 - 0x22];    // 0x22
    s32 fogType;                   // 0x28
    f32 fogStart;                  // 0x2C
    f32 fogEnd;                    // 0x30
    GXColor fogColor;              // 0x34
    MapHeader header;              // 0x38
    void* dat;                     // 0x7C, ./map/%s/map.dat
    u32 datSize;                   // 0x80
    void* tpl;                     // 0x84, ./map/%s/texture.tpl
    u32 tplSize;                   // 0x88
    u8 field_0x8C[0xA8 - 0x8C];    // 0x8C
    MapObject* rootMapObj;         // 0xA8
    struct HitEntry* rootHitObj;     // 0xAC
    Vec bbox[8];                   // 0xB0
    void* tevCallbacks[16];        // 0x110
    s32 numJoints;                 // 0x150, TODO: rename? see: hitNumJoints
    MapObject* objects;            // 0x154, TODO: rename? see: hitNumJoints
    s32 hitNumJoints;              // 0x158
    struct HitEntry* hitEntries;     // 0x15C
    s32 numAnims;                  // 0x160
    MapEntryAnimData* animData;    // 0x164
    u8 field_0x168[0x178 - 0x168]; // 0x168
} MapEntry;

typedef struct MapWork {
    MapEntry entries[2]; // 0x0
    s32 field_2F0;       // 0x2F0
} MapWork;

void mapErrorEntry(s32 arg0, const char* arg1);
const char* getMapDataDvdRoot(void);
void N_mapDispOff(void);
void N_mapDispOn(void);
MapWork* mapGetWork(void);
s32 mapGetActiveGroup(void);
s32 mapGetJoints(MapFileJoint* joint);
void mapInit(void);
MapEntryAnimData* mapSearchAnmObj(const char* animName);
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3);
// more animation functions?
void mapUnLoad(void);
BOOL mapPreLoad(void);
void mapLoad(const char* map);

void mapMain(void);
void mapDisp(void);

void mapSetMaterialLight(s32 flags, Vec position);
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetMaterialFog(void);
typedef struct MapTevCallbackInfo {
    u8 field_0x0[0x4]; // 0x0
    MtxPtr mtx;        // 0x4
    u8 field_0x8[0x4]; // 0x8
    s32 tevStage;      // 0xC, next free TEV stage
    s32 texCoord;      // 0x10
    s32 texMap;        // 0x14
    s32 field_0x18;    // 0x18
} MapTevCallbackInfo;

typedef void (*MapTevCallback)(MapTevCallbackInfo* info);
void mapSetTevCallback(s32 index, MapTevCallback callback);
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);

MapObject* mapGetMapObj(const char* name);
