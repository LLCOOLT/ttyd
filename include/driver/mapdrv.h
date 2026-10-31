// mapdrv.c: the map driver: map.dat structures (joints, materials, display lists) and map object drawing and animation.
#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include "driver/camdrv.h"

typedef struct DisplayList {
    u32 offset;      // 0x00 - Offset to vertex data
    u32 vertexCount; // 0x04 - Number of vertices
} DisplayList;

typedef struct PackedDisplayList {
    u32 offset; // 0x00 - Offset to packed data
    u32 size;   // 0x04 - display list size in bytes (GXCallDisplayList)
} PackedDisplayList;

// "vcd_table" chunk arrays: an element count, then the elements
typedef struct MapVtxArray {
    u32 count;  // 0x0
    u8 data[1]; // 0x4, GXSetArray base
} MapVtxArray;

typedef struct MapVcdTable {
    MapVtxArray* positions;    // 0x0
    MapVtxArray* normals;      // 0x4
    u8 pad_08[0xC - 0x8];      // 0x8
    MapVtxArray* colors[2];    // 0xC
    s32 texCount;              // 0x14
    MapVtxArray* texCoords[8]; // 0x18
    u8 pad_38[0x44 - 0x38];    // 0x38
    s32 posFrac;               // 0x44, fraction bits of the packed s16 positions (GX vtx fmt / GQR5 in hitdrv)
    s32 texFrac[8];            // 0x48, fraction bits of the packed s16 tex coords
} MapVcdTable;

typedef struct MapVtxRec {
    s16 pos;    // 0x0
    s16 nrm;    // 0x2
    s16 clr;    // 0x4
    s16 clr1;   // 0x6, second color index (never read)
    s16 tex[8]; // 0x8
} MapVtxRec;

typedef struct MapRawDL {
    s32 count;       // 0x0, vertices in the strip
    MapVtxRec vtx[]; // 0x4
} MapRawDL;

typedef struct MapFileMesh {
    u8 reserved_00;        // 0x0, map file byte, not read
    u8 padding[2];         // 0x1
    u8 isPackedDisplay;    // 0x3, BOOL
    s32 displayListCount;  // 0x4
    u32 elementMask;       // 0x8
    MapVcdTable* vcdTable; // 0xC
    union {
        MapRawDL* normalLists[1];         // unpacked: stride 4
        PackedDisplayList packedLists[1]; // packed:   stride 8, count = *(u16*)((u8*)packedLists[j].offset + 1)
    } displayLists;                       // at 0x10
} MapFileMesh;

typedef struct MapTexInfo {
    char* name; // 0x0
    u8 format;  // 0x4
    u8 pad_05[3];
    u16 width;  // 0x8
    u16 height; // 0xA
    void* data; // 0xC
} MapTexInfo;

typedef struct MapTexXform {
    union {
        struct {
            f32 tx;  // 0x0
            f32 ty;  // 0x4
            f32 sx;  // 0x8
            f32 sy;  // 0xC
            f32 rot; // 0x10
        };
        f32 ch[5]; // 0x0, tx..rot as the five material-animation channels
    };
    f32 cx; // 0x14
    f32 cy; // 0x18
} MapTexXform;

typedef struct MapMatSampler {
    MapTexInfo* tex; // 0x0
    u8 pad_04[4];    // 0x4
    u8 wrapS;        // 0x8
    u8 wrapT;        // 0x9
    u8 blendMode;    // 0xA, as MapMaterial.blendMode
} MapMatSampler;

typedef struct MapMaterial {
    char* name;                 // 0x0
    GXColor color;              // 0x4
    u8 lightMode;               // 0x8
    u8 pad_09;                  // 0x9
    u8 blendMode;               // 0xA, 0 opaque, 1 alpha-tested, 2 translucent (_mapEnt picks MapObject.blendMode)
    u8 samplerCount;            // 0xB
    MapMatSampler* samplers[8]; // 0xC
    MapTexXform xforms[8];      // 0x2C
    GXColor blendColor;         // 0x10C, last-stage blend colour (translucency test, mapSetMaterialLastStageBlend)
    u8* tevMode;                // 0x110
} MapMaterial;

typedef struct MapFileJointPart {
    MapMaterial* material; // 0x0
    MapFileMesh* mesh;     // 0x4
} MapFileJointPart;

// MapJointDrawMode.modeFlags (from map.dat), copied into MapObject.flags by mapEntry
#define MAP_DRAWMODE_NO_DEPTH 0x1    // MAPOBJ_FLAG_NO_DEPTH
#define MAP_DRAWMODE_GROUP 0x2       // MAPOBJ_FLAG_GROUP, blend mode from blendType
#define MAP_DRAWMODE_CHAR_SHADOW 0x4 // MAPOBJ_FLAG_CHAR_SHADOW
#define MAP_DRAWMODE_NEAR_LIGHTS 0x8 // lit by the nearest map lights as well as lightMask; no prebuilt display list
#define MAP_DRAWMODE_DEPTH_BIAS 0x10 // MAPOBJ_FLAG_DEPTH_BIAS (groups)
typedef struct MapJointDrawMode {
    u8 blendType;          // 0x0, 0..3, selects MapObject.blendMode
    u8 cullMode;           // 0x1
    u8 modeFlags;          // 0x2, MAP_DRAWMODE_*
    u8 pad_03;             // 0x3, never accessed
    u32 lightMask;         // 0x4, bit i = map light i applies
    s32 hitAttributes;     // 0x8, copied to HitEntry.attributes
    u8 pad_0C[0x10 - 0xC]; // 0xC, never accessed
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
    u8 pad_54[0x58 - 0x54];      // 0x54, never accessed
    MapJointDrawMode* drawMode;  // 0x58
    s32 partCount;               // 0x5C
    MapFileJointPart parts[];    // 0x60+
} MapFileJoint;

typedef struct MapFileHeader {
    s32 fileSize;     // 0x0
    s32 dataSize;     // 0x4
    s32 relCount;     // 0x8, entries in the relocation table
    s32 chunkCount;   // 0xC, entries in the chunk (public root) table
    s32 externCount;  // 0x10, number of 8-byte extern (reference) entries after the chunk table
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
    MapFileHeader file;     // 0x0
    void* data;             // 0x20
    u32* rel;               // 0x24, relocation table: offsets into data of the pointers to rebase
    MapFileChunk* chunks;   // 0x28
    MapFileChunk* externs;  // 0x2C, extern table (externCount entries); located but never read
    const char* strings;    // 0x30
    u8 pad_34[0x3C - 0x34]; // 0x34, never accessed
    s32 loadFlags;          // 0x3C, bit 1 set by mapLoadHeader_ before the header copy
    void* rawFile;          // 0x40, the map.dat buffer the header was read from (SPM MapFileContext.rawFile)
} MapHeader;

// MapObject.flags (mapObjFlagOn/Off, mapGrpFlagOn/Off and evt_mapobj_flag_onoff). Bits not listed have no
// script use and their meaning is not established from the readers.
#define MAPOBJ_FLAG_HIDE 0x1                     // not drawn on its own camera (an offscreen copy is still drawn)
#define MAPOBJ_FLAG_BBOX_CULL 0x2                // skipped when its bounding box is outside the view
#define MAPOBJ_FLAG_CHAR_SHADOW 0x4              // receives Mario's projected shadow
#define MAPOBJ_FLAG_NO_DEPTH 0x8                 // no depth test or write: blend modes 3-5 instead of 0-2 (draw mode MAP_DRAWMODE_NO_DEPTH)
#define MAPOBJ_FLAG_GROUP 0x10                   // a group node (drawn with mapDispMapGrp)
#define MAPOBJ_FLAG_IN_GROUP 0x20                // drawn as part of a parent group, not on its own
#define MAPOBJ_FLAG_COLOR_ALPHA 0x40             // MapObject.color alpha applies (translucent below 0xFF, skipped at 0)
#define MAPOBJ_FLAG_OFFSCREEN 0x80               // also drawn into its offscreen buffer (offscreenId)
#define MAPOBJ_FLAG_DISPLAY_LIST 0x100           // draw from the prebuilt display lists (only sticks when one exists)
#define MAPOBJ_FLAG_MTX_DIRTY 0x200              // world matrix is recalculated on the next mapReCalcMatrix
#define MAPOBJ_FLAG_PROJ_TEXTURE 0x400           // adds the projected texture stage (projTexObj)
#define MAPOBJ_FLAG_NO_BLEND 0x800               // ignores the map's blend colour (MapEntry flag 2) and colour (flag 8)
#define MAPOBJ_FLAG_NO_BLEND2 0x1000             // ignores the map's second blend colour (MapEntry flag 4)
#define MAPOBJ_FLAG_ANIM_MTX 0x2000              // uses animMtx instead of localMtx
#define MAPOBJ_FLAG_DISABLE 0x4000               // not drawn at all (no bounding box, no offscreen copy)
#define MAPOBJ_FLAG_DEPTH_BIAS 0x8000            // group part drawn with its depth pulled 0.01 per joint index toward the camera (MAP_DRAWMODE_DEPTH_BIAS)
#define MAPOBJ_FLAG_DEPTH_SHADOW 0x10000         // receives the depth shadow, subtracted (mapSetMaterialTev; ANIM_MATERIAL_FLAG_DEPTH_SHADOW)
#define MAPOBJ_FLAG_PROJ_SHADOW 0x20000          // receives the projected shadow (shadowGetProjShadowTexObj)
#define MAPOBJ_FLAG_DEPTH_SHADOW_ADD 0x40000     // as DEPTH_SHADOW, but the shadow colour is added instead of subtracted
#define MAPOBJ_FLAG_NO_FOG 0x80000               // drawn without the map fog
#define MAPOBJ_FLAG_HIGHLIGHT_OBJ_COLOR 0x100000 // the highlight stage uses the object colour, not the pulsing yellow
#define MAPOBJ_FLAG_TRANSFORM_MTX 0x200000       // transformMtx (mapObjRotate/Trans/Scale) applies
#define MAPOBJ_FLAG_KURURING_PASS 0x400000       // drawn again, unculled, by test_kururing_mapdisp
#define MAPOBJ_FLAG_CHARGE_SHINE 0x800000        // adds the scrolling shine texture stage (ANIM_MATERIAL_FLAG_CHARGE_SHINE)
#define MAPOBJ_FLAG_TEV_CALLBACK_MASK 0xF000000  // index into MapEntry.tevCallbacks, see MAPOBJ_TEV_CALLBACK
#define MAPOBJ_FLAG_NO_COLOR_STAGE 0x10000000    // skips the TEV stage that multiplies in the object and blend colour
#define MAPOBJ_FLAG_BBOX 0x20000000              // its screen bounding box is measured (mapDispMapObj_bbox)
#define MAPOBJ_FLAG_HIGHLIGHT 0x80000000         // mapSetMaterialTev adds a pulsing yellow colour stage (ANIM_MATERIAL_FLAG_HIGHLIGHT)

// MapObject.flags value that selects MapEntry.tevCallbacks[n] (1-15) for the object's extra TEV stages
#define MAPOBJ_TEV_CALLBACK(n) ((n) << 24)

// evt_mapobj_flag_onoff and the other evt_mapobj_* commands: first argument
#define MAPOBJ_SINGLE 0 // only the named map object
#define MAPOBJ_GROUP 1  // the named object and all its children

typedef struct MapObject {
    u32 flags;                // 0x0, MAPOBJ_FLAG_*
    u8 blendMode;             // 0x4
    u8 cameraId;              // 0x5, dispEntry camera (4 by default; set by evt_lect_* / tik_00)
    u8 pad_06[0x8 - 0x6];     // 0x6, never accessed
    MapFileJoint* joints;     // 0x8
    GXColor color;            // 0xC
    Vec center;               // 0x10
    Mtx modelWorldMtx;        // 0x1C
    Mtx localMtx;             // 0x4C
    Mtx animMtx;              // 0x7C, mapCalcAnimMatrix output, concatenated into modelWorldMtx
    Mtx transformMtx;         // 0xAC, mapObjRotate/mapObjTrans/mapObjScale matrix (identity at load)
    s16 offscreenId;          // 0xDC
    s16 groupIndex;           // 0xDE
    struct MapObject* parent; // 0xE0
    struct MapObject* child;  // 0xE4
    struct MapObject* next;   // 0xE8
    u16 screenRect[4];        // 0xEC, projected bounds (0x3FF when off screen)
    void* displayList[8];     // 0xF4, prebuilt display lists (makeDisplayList)
    u32 displayListSize[8];   // 0x114, their sizes; flag 0x100 (use display list) only sticks when [0] is nonzero
} MapObject;

typedef struct MapError {
    char name[32]; // 0x0, map object name that was not found
    s32 type;      // 0x20, mapErrorEntry type (0 for missing objects)
} MapError;

// "animation_table" entry in map.dat (SPM MapFileAnimData)
typedef struct MapAnimHeader {
    const char* name;                    // 0x0
    u8 pad_04[0x8 - 0x4];                // 0x4
    f32 length;                          // 0x8
    struct MapAnimList* jointAnims;      // 0xC, also read by hitMain as the joint list (count + joints)
    struct MapAnimList* materialAnims;   // 0x10
    struct MapAnimList* alphaAnims;      // 0x14
    struct MapAnimList* lightAnims;      // 0x18
    struct MapAnimList* lightColorAnims; // 0x1C
} MapAnimHeader;

// MapEntryAnimData.flags (mapPlayAnimationLv, mapMain)
#define MAP_ANIM_FLAG_PLAYING 0x1        // started by mapPlayAnimationLv
#define MAP_ANIM_FLAG_ENDED 0x2          // reached its end (not looping); mapMain stops advancing it
#define MAP_ANIM_FLAG_LOOP 0x4           // mode 1: wraps around at the end
#define MAP_ANIM_FLAG_PAUSED 0x10        // mapPauseAnimation: time stands still
#define MAP_ANIM_FLAG_RESUME 0x20        // mapReStartAnimation: mapMain clears this and PAUSED, resuming at the stopped frame
#define MAP_ANIM_FLAG_LV0 0x100          // level 1: timed on gp->systemLv0Time
#define MAP_ANIM_FLAG_LV1 0x200          // level 2: gp->systemLv1Time
#define MAP_ANIM_FLAG_LV2 0x400          // level 3: gp->systemLv2Time
#define MAP_ANIM_FLAG_LV3 0x800          // level 4: gp->systemLv3Time
#define MAP_ANIM_FLAG_HIT_APPLIED 0x1000 // hitMain moved the collision objects to this ended animation's last frame
typedef struct MapEntryAnimData {
    u16 flags;              // 0x0
    u8 pad_02[0x8 - 0x2];   // 0x2
    OSTime startTime;       // 0x8
    f32 time;               // 0x10
    f32 rate;               // 0x14
    MapAnimHeader* anim;    // 0x18
    u8 pad_1C[0x20 - 0x1C]; // 0x1C
} MapEntryAnimData;

// Joint animation keys of a map animation (the jointAnims lists of MapEntryAnimData.anim; mapCalcAnimMatrix).
typedef struct MapAnimKeyCh {
    f32 value;  // 0x0
    f32 tanIn;  // 0x4
    f32 tanOut; // 0x8
    f32 extra;  // 0xC, map file value, never read
    s32 step;   // 0x10
} MapAnimKeyCh;

typedef struct MapAnimKey {
    f32 time;            // 0x0
    MapAnimKeyCh ch[21]; // 0x4
} MapAnimKey;

typedef struct MapAnimJoint {
    u8 nameRef[0x4 - 0x0];    // 0x0, probably the joint name, not read
    f32 base[9];              // 0x4
    u8 baseRest[0x58 - 0x28]; // 0x28, base values of channels 9..20, not read
    s32 keyCount;             // 0x58
    MapAnimKey keys[];        // 0x5C
} MapAnimJoint;

// "light_table" chunk
typedef struct MapFileLight {
    const char* name; // 0x0
    const char* type; // 0x4
    Vec position;     // 0x8
    Vec rotation;     // 0x14
    u8 pad_20[0x2C - 0x20];
    GXColor color;  // 0x2C
    f32 spotAngle;  // 0x30
    f32 attenAngle; // 0x34
    s32 attenType;  // 0x38
    s32 lflags;     // 0x3C
    s32 magic;      // 0x40
} MapFileLight;

typedef struct MapFileLightTable {
    s32 count;              // 0x0
    MapFileLight* lights[]; // 0x4
} MapFileLightTable;

// "fog_table" chunk
typedef struct MapFileFog {
    s32 enable;    // 0x0
    s32 type;      // 0x4
    f32 start;     // 0x8
    f32 end;       // 0xC
    GXColor color; // 0x10
} MapFileFog;

// "texture_table" chunk
typedef struct MapTexTable {
    s32 count;     // 0x0
    char* names[]; // 0x4
} MapTexTable;

// "material_name_table" chunk
typedef struct MapMaterialName {
    const char* name; // 0x0
    void* data;       // 0x4
} MapMaterialName;

typedef struct MapMaterialNameTable {
    s32 count;                 // 0x0
    MapMaterialName entries[]; // 0x4
} MapMaterialNameTable;

// MapEntry.flags
#define MAPENT_FLAG_FOG 0x1         // map fog on (fog_table enable, mapFogOn/Off)
#define MAPENT_FLAG_BLEND 0x2       // blend colour on (mapSetBlend); objects with MAPOBJ_FLAG_NO_BLEND ignore it
#define MAPENT_FLAG_BLEND2 0x4      // second blend colour on (mapSetBlend2); MAPOBJ_FLAG_NO_BLEND2 opts out
#define MAPENT_FLAG_COLOR 0x8       // map colour stage on; MAPOBJ_FLAG_NO_BLEND opts out
#define MAPENT_FLAG_VER_1_02 0x8000 // map.dat is "ver1.02": prebuilt display lists are made for it
typedef struct MapEntry {
    union {
        s32 count;                     // 0x0, entries[0]: number of active entries
        struct ARAMEntry* prevTplAram; // 0x0, entries[1] / MapWork.lastTplAram: the previous entry's tpl ARAM copy (MAPENT_TPLARAM)
    };
    u16 flags;                               // 0x4
    char name[16];                           // 0x6
    GXColor blend;                           // 0x16
    GXColor blend2;                          // 0x1A
    GXColor color;                           // 0x1E
    u8 pad_22[0x24 - 0x22];                  // 0x22, never accessed
    s32 fogEnable;                           // 0x24, fog_table word 0
    s32 fogType;                             // 0x28
    f32 fogStart;                            // 0x2C
    f32 fogEnd;                              // 0x30
    GXColor fogColor;                        // 0x34
    MapHeader header;                        // 0x38
    void* dat;                               // 0x7C, ./map/%s/map.dat
    u32 datSize;                             // 0x80
    void* tpl;                               // 0x84, ./map/%s/texture.tpl
    u32 tplSize;                             // 0x88
    void* arcData;                           // 0x8C, LZ77-decoded map archive from <root>/b/<map> (mapLoad); dat/tpl may point into it; copied to ARAM as arcAram
    u32 arcSize;                             // 0x90
    MapTexTable* textureTable;               // 0x94, "texture_table" chunk
    MapFileLightTable* lightTable;           // 0x98, "light_table" chunk
    MapFileFog* fogTable;                    // 0x9C, "fog_table" chunk
    MapMaterialNameTable* materialNameTable; // 0xA0, "material_name_table" chunk
    MapVcdTable* vcdTable;                   // 0xA4, "vcd_table" chunk
    MapObject* rootMapObj;                   // 0xA8
    struct HitEntry* rootHitObj;             // 0xAC
    Vec bbox[8];                             // 0xB0
    void* tevCallbacks[16];                  // 0x110
    s32 numJoints;                           // 0x150, one MapObject per joint
    MapObject* objects;                      // 0x154, numJoints entries
    s32 hitNumJoints;                        // 0x158
    struct HitEntry* hitEntries;             // 0x15C
    s32 numAnims;                            // 0x160
    MapEntryAnimData* animData;              // 0x164
    u32 dispListSize;                        // 0x168, total display-list bytes (makeDisplayList)
    void* dispListBuf;                       // 0x16C, _mapAllocTail(dispListSize); freed in bmapLoad
    struct ARAMEntry* datAram;               // 0x170, ARAM copy of dat (bmapLoad / bmapUnLoad)
    struct ARAMEntry* arcAram;               // 0x174, ARAM copy of arcData
    // the tpl ARAM copy has no slot of its own: it lives in the first word after the entry (MAPENT_TPLARAM)
} MapEntry;

typedef struct MapWork {
    MapEntry entries[2];           // 0x0
    struct ARAMEntry* lastTplAram; // 0x2F0, entries[1]'s tpl ARAM copy (MAPENT_TPLARAM(&entries[1]))
} MapWork;

// tpl ARAM copy of a map entry: stored in the word after it (the next entry's count slot, or lastTplAram)
#define MAPENT_TPLARAM(entry) ((entry) + 1)->prevTplAram

void mapErrorEntry(s32 type, const char* name);
const char* getMapDataDvdRoot(void);
void N_mapDispOff(void);
void N_mapDispOn(void);
MapWork* mapGetWork(void);
s32 mapGetActiveGroup(void);
s32 mapGetJoints(MapFileJoint* joint);
void mapInit(void);
MapEntryAnimData* mapSearchAnmObj(const char* animName);
void mapCheckAnimation(const char* animName, BOOL* valid, f32* msLeft);
// more animation functions?
void mapUnLoad(void);
BOOL mapPreLoad(const char* map);
void mapLoad(const char* map);

void mapMain(void);
void mapDisp(void);

void mapSetMaterialLight(s32 flags, Vec position);
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetMaterialFog(void);
typedef struct MapTevCallbackInfo {
    u8 mapObj[0x4];   // 0x0, MapObject* being drawn (stored raw)
    MtxPtr mtx;       // 0x4
    u8 drawMode[0x4]; // 0x8, s32 draw mode (stored raw)
    s32 tevStage;     // 0xC, next free TEV stage
    s32 texCoord;     // 0x10
    s32 texMap;       // 0x14
    s32 indStage;     // 0x18, next free indirect TEV stage
} MapTevCallbackInfo;

typedef void (*MapTevCallback)(MapTevCallbackInfo* info);
void mapSetTevCallback(s32 index, MapTevCallback callback);
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);

MapObject* mapGetMapObj(const char* name);

void mapGetBlend(GXColor* color);
void mapGetBlend2(GXColor* color);
BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);

extern BOOL __mapdrv_make_dl; // mapdrv.c
void mapGrpFlagOn(const char* name, u32 flags);

extern const GXCullMode culling[4];
extern s32 fog_type[5];

void mapGrpFlagOff(const char* name, u32 flags);

void mapGrpSetColor(const char* name, GXColor color);
void bmapUnLoad(void);
void mapResetPaperAmbColor(void);
void mapPlayAnimationLv(const char* name, s32 mode, s32 level);
void mapPauseAnimation(const char* name);
void mapReStartAnimation(const char* name);
void mapPauseAnimationAll(const char* name);
void mapReStartAnimationAll(const char* name);
void mapSetPlayRate(const char* name, f32 rate);
BOOL bmapPreLoad(const char* map, const char* map2);
void bmapLoad(const char* map, const char* map2);
void mapCalcAnimMatrix(Mtx out, Mtx in, MapEntryAnimData* anim, MapAnimJoint* joint);
void mapObjFlagOn(const char* name, u32 flags);
void mapObjFlagOff(const char* name, u32 flags);
void mapObjClearOffScreen(const char* name);
void mapGrpClearOffScreen(const char* name);
void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
void mapObjScale(const char* name, f32 x, f32 y, f32 z);
void mapObjGetPos(const char* name, Vec* pos);
void mapSetFog(s32 type, f32 start, f32 end, GXColor color);
void mapGetFog(s32* type, f32* start, f32* end, GXColor* color);
void mapFogOn(void);
void mapFogOff(void);
void mapBlendOff(void);
void mapBlendOff2(void);
void mapSetProjMtx(Mtx mtx);
void mapObjFlushOn(const char* name);
void mapObjFlushOff(const char* name);
void mapGrpFlushOn(const char* name);
void mapGrpFlushOff(const char* name);
void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);
void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);
void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a);
void mapSetPaperAmbColor(GXColor* color);
void mapSetProjTexObj(GXTexObj* obj, void* imgRef);
void test_kururing_mapdisp(CameraId cam);
void mapGrpSetOffScreen(const char* name, const char* offscreen);
void mapObjSetColor(const char* name, GXColor* color);
void mapObjSetOffScreen(const char* name, const char* offscreen);
void mapSetBlend(GXColor color);
void mapSetBlend2(GXColor color);
void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl);
void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out);
