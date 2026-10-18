#include "driver/mapdrv.h"
#include "driver/arcdrv.h"
#include "manager/dvdmgr.h"
#include "manager/arammgr.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include "texPalette.h"
#include "driver/offscreendrv.h"
#include "driver/camdrv.h"
#include "driver/lightdrv.h"
#include "driver/shadowdrv.h"
double sin(double);
double cos(double);
#ifdef NONMATCHING
static inline f32 sinf(f32 x) { return sin(x); }
#endif
#include <string.h>
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active on
__declspec(section ".sdata") u32 gap_08_804184BC_sbss[1];
#pragma force_active reset
void envReInit(void);

__declspec(section ".sdata2") const u32 gap_10_80422F94_sbss2;
__declspec(section ".sdata2") const u32 unk_80422f90;
__declspec(section ".sdata2") const u32 unk_80422f8c;
__declspec(section ".sdata2") const u32 unk_80422f88;
__declspec(section ".sdata2") const u32 unk_80422f84;
__declspec(section ".sdata2") const u32 unk_80422f80;
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
int __cvt_dbl_usll();
int __cvt_ull_flt();
int __div2i();
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void _mapDispMapObj(CameraId cam, MapObject *obj);
void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
void _mapLoad(MapWork* wp, BOOL group, const char* map);
void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext);
void makeDisplayList(BOOL group);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext);
void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
void mapGrpFlagOff(const char* name, u32 flags);
void mapGrpFlagOn(const char* name, u32 flags);
void mapGrpSetColor(const char* name, GXColor color);
void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext);
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix);
s32 mapSetLight(MapObject* obj, LightEntry** lights);
void mapSetMaterial(MapObject* obj, void* material);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);
void setColor(MapObject* obj, GXColor color, BOOL doNext);
int strcat();
__declspec(section ".sdata") f32 g5_scrl_uv_s1622[4] = {0.0f, 0.0f, 0.0f, 0.0f};
void mapDispMapGrp(CameraId cam, MapObject* obj);
void mapDispMapGrp_bbox(CameraId cam, MapObject* obj);
void mapDispMapGrp_off(CameraId cam, MapObject* obj);
void mapDispMapObj(CameraId cam, MapObject* obj);
void mapDispMapObj_bbox(CameraId cam, MapObject* obj);
void mapDispMapObj_off(CameraId cam, MapObject* obj);
asm void bmapUnLoad(void);
extern f32 queen_uv[]; //gxsub.c
extern GlobalWork* gp;
// FAKE: the last .sdata2 constants (0xCC-0xDB) are named objects defined at the end of the file so the
// bmapUnLoad asm can address "" and they keep the original pool order (explicit data lands after the pool)
extern const char mapEmptyStr[4];
extern const char mapPathFmt[8];
extern const f32 mapF20000;
extern int sprintf(char* str, const char* format, ...);

#define TWO_PI 6.28318530717958647692528676655900576839433879875021f

//.bss
MapError error_data[32];

//.sbss
GXColor paper_ambient;
GXColor paperCraft_ambient;
GXTexObj projTexObj;
void* projTexImgRef;
Mtx projMtx;
BOOL __mapdrv_make_dl;
BOOL unk_80418458;
s32 error_count;
BOOL error_flag;
MapObject* current_mp;
BOOL mapClipOffFlag;
s32 activeGroup;
MapWork* mapWork; //allocates two entries

typedef struct MapAnimHeader {
	const char* name; // 0x0
	u8 field_0x4[0x8 - 0x4]; // 0x4
	f32 length; // 0x8
} MapAnimHeader;

typedef struct MapAnim {
	u16 flags; // 0x0
	u8 field_0x2[0x8 - 0x2]; // 0x2
	OSTime startTime; // 0x8
	f32 time; // 0x10
	f32 rate; // 0x14
	MapAnimHeader* anim; // 0x18
	u8 field_0x1C[0x20 - 0x1C]; // 0x1C
} MapAnim;

#define MAPENT_FIELD(entry, type, off) (*(type*)((u8*)(entry) + (off)))

typedef struct MapJointDrawModeEx {
	u8 field_0x0[0x2 - 0x0]; // 0x0
	u8 flags;                 // 0x2
	u8 field_0x3;             // 0x3
	u32 lightMask;            // 0x4
} MapJointDrawModeEx;


LightEntry* lightGetPaper(void);
LightEntry* lightGetPaperCraft(void);
LightEntry* lightGetCharaAmbient(void);
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
s32 lightCheckCharaLight(void);
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)

//.sdata
s32 fog_type[5] = {2, 4, 5, 6, 7};

//local prototypes
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
void _mapLoad(MapWork* wp, BOOL group, const char* map);
void makeDisplayList(BOOL group);
void makeDisplayList(BOOL group);
//anim functions?
void _mapLoad(MapWork* wp, BOOL group, const char* map);

#ifdef NONMATCHING
void mapErrorEntry(s32 arg0, const char* arg1) { //1:1
	MapError* error = error_data;

	error += error_count;
	error->field_0x20 = arg0;
	strncpy(error->field_0x0, arg1, sizeof(error->field_0x0) - 1);
	error_flag = TRUE;
	error_count++;
	error_count %= 32;
}
#endif

#ifdef NONMATCHING
const char* getMapDataDvdRoot(void) {
	return ".";
}
#endif

#ifdef NONMATCHING
void N_mapDispOff(void) {
	unk_80418458 = TRUE;
}
#endif

#ifdef NONMATCHING
void N_mapDispOn(void) {
	unk_80418458 = FALSE;
}
#endif

#ifdef NONMATCHING
MapWork* mapGetWork(void) {
	return &mapWork[activeGroup];
}
#endif

#ifdef NONMATCHING
s32 mapGetActiveGroup(void) {
	return activeGroup;
}
#endif

#ifdef NONMATCHING
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints) { //1:1
	(*numJoints)++;
	if (joint->child) {
		mapGetJointsSub(joint->child, numJoints);
	}
	if (joint->next) {
		mapGetJointsSub(joint->next, numJoints);
	}
}
#endif

#ifdef NONMATCHING
s32 mapGetJoints(MapFileJoint* joint) { //1:1
	s32 numJoints;

	numJoints = 0;
	if (joint) {
		numJoints = 1;
		if (joint->child) {
			mapGetJointsSub(joint->child, &numJoints);
		}
	}
	return numJoints;
}
#endif

#ifdef NONMATCHING
void mapGetBoundingBox(Vec* min, Vec* max) {
	MapWork* wp = &mapWork[activeGroup];
	MapObject* obj;
	int i;
	Vec vec;

	*min = (Vec){0.0f, 0.0f, 0.0f};
	*max = (Vec){0.0f, 0.0f, 0.0f};
	obj = wp->entries[0].objects;
	for (i = 0; i < wp->entries[0].numJoints; i++, obj++) {
		if (obj->joints && obj->joints->partCount) {
			MTXMultVec(obj->modelWorldMtx, &obj->joints->bboxMin, &vec);
			if (min->x > vec.x) min->x = vec.x;
			if (min->y > vec.y) min->y = vec.y;
			if (min->z > vec.z) min->z = vec.z;
			if (max->x < vec.x) max->x = vec.x;
			if (max->y < vec.y) max->y = vec.y;
			if (max->z < vec.z) max->z = vec.z;
			MTXMultVec(obj->modelWorldMtx, &obj->joints->bboxMax, &vec);
			if (min->x > vec.x) min->x = vec.x;
			if (min->y > vec.y) min->y = vec.y;
			if (min->z > vec.z) min->z = vec.z;
			if (max->x < vec.x) max->x = vec.x;
			if (max->y < vec.y) max->y = vec.y;
			if (max->z < vec.z) max->z = vec.z;
		}
	}
}
#endif

#ifdef NONMATCHING
void mapInit(void) {
	mapWork = __memAlloc(HEAP_DEFAULT, sizeof(MapWork) * 2);
	memset(mapWork, 0, sizeof(MapWork) * 2);
	activeGroup = 0;
	mapClipOffFlag = FALSE;
}
#endif

typedef struct MapTexInfo {
	char* name;   // 0x0
	u8 format;    // 0x4
	u8 pad5[3];
	u16 width;    // 0x8
	u16 height;   // 0xA
	void* data;   // 0xC
} MapTexInfo;

typedef struct MapTexSampler {
	MapTexInfo* tex; // 0x0
} MapTexSampler;

typedef struct MapTexMaterial {
	u8 pad0[0xB];
	u8 samplerCount;          // 0xB
	MapTexSampler* samplers[]; // 0xC
} MapTexMaterial;

typedef struct MapTexTable {
	s32 count;
	char* names[];
} MapTexTable;

#ifdef NONMATCHING
static inline s32 mapSearchTexName(MapTexTable* table, char* name) {
	s32 i;

	for (i = 0; i < table->count; i++) {
		if (strcmp(table->names[i], name) == 0) {
			return i;
		}
	}
	return -1;
}
#endif

#ifdef NONMATCHING
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table) {
	int i;
	int j;
	int k;
	int idx;
	MapTexMaterial* mat;
	MapTexSampler* sampler;
	TEXDescriptor* desc;

	for (i = 0; i < obj->joints->partCount; i++) {
		mat = obj->joints->parts[i].material;
		for (j = 0; j < mat->samplerCount; j++) {
			sampler = mat->samplers[j];
			k = mapSearchTexName(table, sampler->tex->name);
			idx = k;
			if (k == -1) {
				idx = 0;
			}
			desc = TEXGet(texture, idx);
			sampler->tex->data = desc->textureHeader->data;
			sampler->tex->width = desc->textureHeader->width;
			sampler->tex->height = desc->textureHeader->height;
			switch (desc->textureHeader->format) {
				case 4: sampler->tex->format = 0; break;
				if (!k) {
				}
				case 5: sampler->tex->format = 1; break;
				case 6: sampler->tex->format = 2; break;
				case 14: sampler->tex->format = 3; break;
				case 0: sampler->tex->format = 4; break;
				case 1: sampler->tex->format = 5; break;
				case 2: sampler->tex->format = 6; break;
				case 3: sampler->tex->format = 7; break;
				case 8: sampler->tex->format = 8; break;
				case 9: sampler->tex->format = 9; break;
				case 10: sampler->tex->format = 10; break;
			}
		}
	}
	if (obj->child) {
		mapBuildTexture(obj->child, texture, table);
	}
	if (obj->next) {
		mapBuildTexture(obj->next, texture, table);
	}
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	MapWork* wp = &mapWork[activeGroup];
	MapObject* obj;
	s32 i;
	Mtx trans, scale, rotX, rotY, rotZ;
	Vec a, b;

	obj = wp->entries[index].objects;
	for (i = 0; i < wp->entries[index].numJoints; i++, obj++) {
		if (!obj->joints) break;
	}
	obj->flags = 0;
	obj->joints = joint;
	obj->groupIndex = (s16)index;
	PSMTXTrans(trans, joint->translation.x, joint->translation.y, joint->translation.z);
	PSMTXScale(scale, joint->scale.x, joint->scale.y, joint->scale.z);
	PSMTXRotRad(rotX, 'x', 0.017453292f * joint->rotation.x);
	PSMTXRotRad(rotY, 'y', 0.017453292f * joint->rotation.y);
	PSMTXRotRad(rotZ, 'z', 0.017453292f * joint->rotation.z);
	PSMTXConcat(trans, rotZ, trans);
	PSMTXConcat(trans, rotY, trans);
	PSMTXConcat(trans, rotX, trans);
	PSMTXConcat(trans, scale, obj->localMtx);
	PSMTXConcat(mtx, obj->localMtx, obj->modelWorldMtx);
	PSMTXIdentity(obj->unkAC);
	obj->flags |= 0x200;
	obj->unk5 = 4;
	obj->offscreenId = -1;
	obj->parent = parent;
	obj->next = NULL;
	obj->child = NULL;
	if (joint->drawMode) {
		if (((u8*)joint->drawMode)[2] & 1) {
			obj->flags |= 8;
		}
		switch (joint->drawMode->unk0[0]) {
			case 0: {
				MapFileJoint* j = obj->joints;
				s32 k, n2 = 0, n1 = 0;
				for (i = 0; i < obj->joints->partCount; i++) {
					u8 t = *((u8*)obj->joints->parts[i].material + 0xa);
					if (t == 2) { n2++; if (!obj) { } }
					else if (t == 1) { if (1) { } n1++; }
					for (k = 0; k < 8; k++) {
						u8* tex = *(u8**)((u8*)obj->joints->parts[i].material + 0xc + k * 4);
						if (!tex) break;
						t = tex[0xa];
						if (t == 2) n2++;
						else if (t == 1) n1++;
					}
				}
				if (n2) obj->blendMode = 2;
				else if (n1) obj->blendMode = 1;
				else obj->blendMode = 0;
				break;
			}
			case 1:
				{ u8 m = 0; if (obj->flags & 8) m = 3; obj->blendMode = m; }
				break;
			case 2:
				obj->blendMode = (obj->flags & 8) ? 4 : 1;
				break;
			case 3:
				obj->blendMode = (obj->flags & 8) ? 5 : 2;
				break;
		}
		if (((u8*)joint->drawMode)[2] & 2) {
			obj->flags |= 0x10;
			if (((u8*)joint->drawMode)[2] & 0x10) {
				obj->flags |= 0x8000;
			}
			switch (joint->drawMode->unk0[0]) {
				case 0: obj->blendMode = 2; break;
				case 1: obj->blendMode = 0; break;
				case 2: obj->blendMode = 1; break;
				case 3:
				default: obj->blendMode = 2; break;
			}
		}
		if (obj->flags & 0x10) {
			if (parent && (parent->flags & 0x10 || parent->flags & 0x20)) {
				obj->flags &= ~0x10;
			}
		} else if (parent && (parent->flags & 0x10 || parent->flags & 0x20)) {
			obj->flags |= 0x20;
			if (parent->flags & 0x8000) {
				obj->flags |= 0x8000;
			}
		}
		if (((u8*)joint->drawMode)[2] & 4) {
			obj->flags |= 4;
		}
	} else {
		OSPanic("mapdrv.c", 0x2e5, "\x83\x57\x83\x87\x83\x43\x83\x93\x83\x67\x82\xcc\x83\x66\x81\x5b\x83\x5e\x82\xcc\x8e\x77\x92\xe8\x82\xc9\x82\xa8\x82\xa9\x82\xb5\x82\xc8\x82\xe0\x82\xcc\x82\xaa\x82\xa0\x82\xe9\n");
	}
	if (joint->partCount) {
		PSVECAdd(&joint->bboxMin, &joint->bboxMax, &obj->center);
		PSVECScale(&obj->center, &obj->center, 0.5f);
	} else {
		obj->center = joint->translation;
	}
	if (joint->partCount) {
		PSMTXMultVec(obj->modelWorldMtx, &obj->center, &a);
		PSMTXMultVec(obj->modelWorldMtx, &joint->bboxMax, &b);
		if (PSVECSquareDistance(&a, &b) < mapF20000) {
			obj->flags |= 2;
		}
	}
	return obj;
}
#endif

#pragma dont_inline reset
#ifdef NONMATCHING
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index) {
	MapObject* obj = _mapEnt(joint, parent, mtx, index);
	if (joint->child) {
		obj->child = mapEntrySub(joint->child, obj, obj->modelWorldMtx, FALSE, index);
	}
	if (!isRoot) {
		if (joint->next) {
			obj->next = mapEntrySub(joint->next, parent, mtx, FALSE, index);
		}
	}
	return obj;
}
#endif

#ifdef NONMATCHING
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index) {
	MapWork* wp = (0, &mapWork[activeGroup]);
	u32 size;

	wp->entries[index].numJoints = mapGetJoints(joint);
	size = (((wp->entries[index].numJoints * sizeof(MapObject)) + 32) - 1) & ~(32 - 1);
	wp->entries[index].objects = _mapAlloc(size);
	memset(wp->entries[index].objects, 0, size);
	return mapEntrySub(joint, NULL, mtx, TRUE, index);
}
#endif

s32 shadowGetCharShadowProjection(void);
GXTexObj* shadowGetCharShadowTexObj(void);
GXColor shadowGetCharShadowColor(void);
f32 (*shadowGetCharShadowProjTexMtx(void))[4];
GXTexObj* shadowGetDepthShadowTexObj(void);
f32 (*shadowGetDepthShadowDepthMtx(void))[4];
f32 (*shadowGetDepthShadowProjTexMtx(void))[4];
GXColor shadowGetDepthShadowColor(void);
ShadowConfig* shadowGetDepthShadowConfig(void);
GXTexObj* shadowGetRamp8TexObj(void);
GXTexObj* shadowGetRamp16TexObj(void);
GXTexObj* shadowGetProjShadowTexObj(void);
f32 (*shadowGetProjShadowProjTexMtx(void))[4];
GXColor shadowGetProjShadowColor(void);
ShadowConfig* shadowGetProjShadowConfig(void);
void mapSetMaterial(MapObject* obj, void* material);
void mapSetMaterial(MapObject* obj, void* material);
void mapResetPaperAmbColor(void);
void mapResetPaperAmbColor(void);
static inline void mapResetPaperCraftAmbColor(void);

typedef struct MapObjectDL {
	u8 field_0x0[0xF4];  // 0x0
	void* dl[8];         // 0xF4
	u32 dlSize[8];       // 0x114
} MapObjectDL;
#define MAPOBJ_DL(obj) (((MapObjectDL*)(obj))->dl)
#define MAPOBJ_DLSIZE(obj) (((MapObjectDL*)(obj))->dlSize)

#ifdef NONMATCHING
void makeDisplayList(BOOL group) {
	static const GXCullMode culling[4] = {GX_CULL_FRONT, GX_CULL_BACK, GX_CULL_ALL, GX_CULL_NONE};
	MapEntry* e;
	MapWork* wp = mapGetWork();
	void* buf;
	int i;
	int j;
	int pass;
	u32 total;
	u8* dst;
	MapObject* obj;
	MapJointDrawModeEx* dm;
	s32 k;
	void* material;

	buf = _mapAlloc(0x10000);
	e = &wp->entries[group];
	__mapdrv_make_dl = TRUE;
	total = 0;
	for (pass = 0; pass < 2; pass++) {
		obj = e->objects;
		for (k = 0; k < 8; k++) {
			MAPOBJ_DL(obj)[k] = NULL;
			MAPOBJ_DLSIZE(obj)[k] = 0;
		}
		for (i = 0; i < wp->entries[group].numJoints; i++, obj++) {
			if (obj->joints->partCount < 1 || obj->joints->partCount > 8) {
				continue;
			}
			dm = (MapJointDrawModeEx*)obj->joints->drawMode;
			if (dm->flags & 8) {
				continue;
			}
			if (dm->lightMask) {
				continue;
			}
			if (shadowGetCharShadowProjection() && (obj->flags & 4)) {
				continue;
			}
			if (!(e->flags & 0x8000)) {
				continue;
			}
			for (j = 0; j < obj->joints->partCount; j++) {
				material = obj->joints->parts[j].material;
				memset(buf, 0, 0x10000);
				DCInvalidateRange(buf, 0x10000);
				GXBeginDisplayList(buf, 0x10000);
				GXResetWriteGatherPipe();
				mapSetMaterial(obj, material);
				GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
				MAPOBJ_DLSIZE(obj)[j] = GXEndDisplayList();
				if (pass == 0) {
					total += MAPOBJ_DLSIZE(obj)[j];
				}
				else {
					MAPOBJ_DL(obj)[j] = dst;
					dst += MAPOBJ_DLSIZE(obj)[j];
					memcpy(MAPOBJ_DL(obj)[j], buf, MAPOBJ_DLSIZE(obj)[j]);
					DCFlushRange(MAPOBJ_DL(obj)[j], MAPOBJ_DLSIZE(obj)[j]);
				}
			}
		}
		if (pass == 0) {
			e->dispListSize = total;
			if (e->dispListSize) {
				e->dispListBuf = _mapAllocTail(e->dispListSize);
				dst = e->dispListBuf;
			}
			else {
				((void**)((u8*)wp + 0x16C))[group * 0x5E] = NULL;
				break;
			}
		}
	}
	_mapFree(buf);
	__mapdrv_make_dl = FALSE;
}
#endif

#ifdef NONMATCHING
static inline MapAnim* mapSearchAnmObj_inl(const char* animName) {
	MapEntry* entry;
	MapWork* wp = &mapWork[activeGroup];
	int j;
	int i;
	MapAnim* anim;

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if ((anim->flags & 1) && !strcmp(anim->anim->name, animName)) {
				return anim;
			}
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
MapEntryAnimData* mapSearchAnmObj(const char* animName) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry;
	int j;
	int i;
	MapAnim* anim;

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if ((anim->flags & 1) && !strcmp(anim->anim->name, animName)) {
				return (MapEntryAnimData*)anim;
			}
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3) {
	MapAnim* anim = mapSearchAnmObj_inl(animName);

	*valid = FALSE;
	*a3 = 0.0f;
	if (anim) {
		if (anim->flags & 2) {
			*valid = TRUE;
		}
		*a3 = 1000.0f * (anim->anim->length - anim->time) / gp->framerate;
	}
	else {
		*valid = TRUE;
	}
}
#endif

#ifdef NONMATCHING
void mapPlayAnimationLv(const char* name, s32 a, s32 b) {
	MapAnim* anim = NULL;
	MapWork* wp;
	MapEntry* entry;
	int j;
	int i = 0;
	BOOL found = FALSE;
	OSTime t;

	wp = &mapWork[activeGroup];
	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			if (!strcmp(anim->anim->name, name)) {
				found = TRUE;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	if (found) {
		anim->flags = 0;
		switch (b) {
			case 0:
				break;
			case 1:
				anim->flags |= 0x100;
				break;
			case 2:
				anim->flags |= 0x200;
				break;
			case 3:
				anim->flags |= 0x400;
				break;
			case 4:
				anim->flags |= 0x800;
				break;
		}
		if (anim->flags & 0x100) {
			t = gp->systemLv0Time;
		}
		else if (anim->flags & 0x200) {
			t = gp->systemLv1Time;
		}
		else if (anim->flags & 0x400) {
			t = gp->systemLv2Time;
		}
		else if (anim->flags & 0x800) {
			t = gp->systemLv3Time;
		}
		else if (gp->inBattle) {
			t = gp->renderTime;
		}
		else {
			t = gp->renderFieldTime;
		}
		anim->startTime = OSTicksToMilliseconds(t);
		anim->time = 0.0f;
		anim->rate = 1.0f;
		anim->flags |= 1;
		if (a == 1) {
			anim->flags |= 4;
		}
		if (a == 2) {
			anim->startTime -= (u64)(1000.0f * anim->anim->length / gp->framerate);
		}
	}
}
#endif

#ifdef NONMATCHING
void mapPauseAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x10;
	}
}
#endif

#ifdef NONMATCHING
void mapReStartAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x20;
	}
}
#endif

#ifdef NONMATCHING
void mapPauseAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x10;
		}
	}
}
#endif

#ifdef NONMATCHING
void mapReStartAnimationAll(const char* name) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	int j;
	int i;
	MapAnim* anim;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			anim->flags |= 0x20;
		}
	}
}
#endif

#ifdef NONMATCHING
void mapSetPlayRate(const char* name, f32 rate) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->rate = rate;
	}
}
#endif

typedef struct MapFileLightEx {
	const char* name;   // 0x0
	const char* type;   // 0x4
	Vec position;       // 0x8
	Vec rotation;       // 0x14
	u8 pad20[0x2C - 0x20];
	GXColor color;      // 0x2C
	f32 spotAngle;      // 0x30
	f32 attenAngle;     // 0x34
	s32 attenType;      // 0x38
	s32 lflags;         // 0x3C
	s32 magic;          // 0x40
} MapFileLightEx;

struct HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);

#ifdef NONMATCHING
static inline void* mapSearchChunk(MapHeader* header, const char* name) {
	u32 k;

	for (k = 0; k < header->file.chunkCount; k++) {
		if (!strcmp(&header->strings[header->chunks[k].string], name)) {
			return (u8*)header->data + header->chunks[k].offset;
		}
	}
	return NULL;
}
#endif


#ifdef NONMATCHING
static inline u32* mapLoadFindChunk_(MapEntry* e2, const char* name) {
	u32 k;
	for (k = 0; k < e2->header.file.chunkCount; k++) {
		if (!strcmp(&e2->header.strings[e2->header.chunks[k].string], name)) {
			return (u32*)((u8*)e2->header.data + e2->header.chunks[k].offset);
		}
	}
	return NULL;
}
#endif
typedef struct MapEntryOv {
	u8 pad0[0x24];
	s32 fogEnable;
	u8 pad28[0x78 - 0x28];
	void* hdr40;
	u8 pad7C[0x94 - 0x7C];
	void* textureTable;
	void* lightTable;
	void* fogTable;
	void* materialNameTable;
	void* vcdTable;
	u8 padA8[0x178 - 0xA8];
} MapEntryOv;
typedef struct MapWorkOv {
	MapEntryOv entries[2];
} MapWorkOv;
#ifdef NONMATCHING
static inline void mapLoadReloc_(MapEntry* entry) {
	u32 k;
	for (k = 0; k < (u32)entry->header.file.relCount; k++) {
		u32* rel = (u32*)((u8*)entry->header.data + ((u32*)entry->header.rel)[k]);
		if (*rel <= 0x80000000) {
			*rel += (u32)entry->header.data;
		}
	}
}
#endif
#ifdef NONMATCHING
static inline void mapLoadHeader_(MapWork* wp, BOOL group) {
	u32 datSize = wp->entries[group].datSize;
	u8* data = (u8*)wp->entries[group].dat;
	u32 sizeCheck;
	MapHeader* header = &wp->entries[group].header;
	if (header != NULL) {
		memset(header, 0, sizeof(MapHeader));
		wp->entries[group].header.field_0x3C |= 1;
		memcpy(header, data, sizeof(MapFileHeader));
		if (wp->entries[group].header.file.fileSize == datSize) {
			sizeCheck = sizeof(MapFileHeader);
			if ((u32)wp->entries[group].header.file.dataSize != 0u) {
				wp->entries[group].header.data = &data[sizeCheck];
				sizeCheck = wp->entries[group].header.file.dataSize;
				sizeCheck += sizeof(MapFileHeader);
			}
			if ((u32)wp->entries[group].header.file.relCount != 0u) {
				wp->entries[group].header.rel = &data[sizeCheck];
				sizeCheck += 4 * wp->entries[group].header.file.relCount;
			}
			if ((u32)wp->entries[group].header.file.chunkCount != 0u) {
				wp->entries[group].header.chunks = (MapFileChunk*)&data[sizeCheck];
				sizeCheck += sizeof(MapFileChunk) * wp->entries[group].header.file.chunkCount;
			}
			if ((u32)wp->entries[group].header.file.unused != 0u) {
				wp->entries[group].header.unused = &data[sizeCheck];
				sizeCheck += 8 * wp->entries[group].header.file.unused;
			}
			if (sizeCheck < wp->entries[group].header.file.fileSize) {
				wp->entries[group].header.strings = (const char*)&data[sizeCheck];
			}
			*(u8**)((u8*)&wp->entries[group] + 0x78) = data;

			mapLoadReloc_(&wp->entries[group]);
		}
	}
}
#endif
#ifdef NONMATCHING
void _mapLoad(MapWork* wp, BOOL group, const char* map) {
	MapFileInfo* info;
	u32 datSize, k;
	int i;
	u32 r4, r7, r0;
	u32 sizeCheck;
	char str1[128];
	char str2[128];
	char str3[128];
	DVDEntry* dvd;
	MapWorkOv* wo;
	u8 *data;
	MapHeader* header;

	wo = (MapWorkOv*)wp;
	error_flag = FALSE;
	error_count = 0;
	strncpy(wp->entries[group].name, map, sizeof(wp->entries[group].name));

	sprintf(str1, "./m/%s/d", map);
	arcOpen(str1, &wp->entries[group].dat, &wp->entries[group].datSize);
	if (!wp->entries[group].dat) {
		sprintf(str2, mapPathFmt, ".", str1);
		dvd = DVDMgrOpen(str2, 2, 0);
		wp->entries[group].datSize = DVDMgrGetLength(dvd);
		wp->entries[group].dat = _mapAllocTail(OSRoundUp32B(wp->entries[group].datSize));
		DVDMgrRead(dvd, wp->entries[group].dat, OSRoundUp32B(wp->entries[group].datSize), 0);
		DVDMgrClose(dvd);
	}

	sprintf(str1, "./m/%s/t", map);
	wp->entries[group].tpl = NULL;
	arcOpen(str1, &wp->entries[group].tpl, &wp->entries[group].tplSize);
	if (wp->entries[group].tpl) {
		UnpackTexPalette(wp->entries[group].tpl);
	}
	else {
		sprintf(str3, mapPathFmt, ".", str1);
		dvd = DVDMgrOpen(str3, 2, 0);
		if (dvd) {
			wp->entries[group].tplSize = DVDMgrGetLength(dvd);
			wp->entries[group].tpl = _mapAllocTail(OSRoundUp32B(wp->entries[group].tplSize));
			DVDMgrRead(dvd, wp->entries[group].tpl, OSRoundUp32B(wp->entries[group].tplSize), 0);
			DVDMgrClose(dvd);
			UnpackTexPalette(wp->entries[group].tpl);
		}
	}

	GXInvalidateVtxCache();
	mapLoadHeader_(wp, group);
	header = &wp->entries[group].header;
	info = (MapFileInfo*)mapSearchChunk(header, "information");
	wo->entries[group].textureTable = mapSearchChunk(header, "texture_table");
	wo->entries[group].lightTable = mapSearchChunk(header, "light_table");
	wo->entries[group].fogTable = mapSearchChunk(header, "fog_table");
	wo->entries[group].materialNameTable = mapSearchChunk(header, "material_name_table");
	wo->entries[group].vcdTable = mapSearchChunk(header, "vcd_table");
	{
		MapFileJoint* mapJoint = mapSearchDmdJoint(info->joint, info->mapName);
		MapFileJoint* hitJoint = mapSearchDmdJoint(info->joint, info->hitName);
		Mtx scale;
		s32 n;
		u32* animTbl;
		MapEntry* e2;
		MapWork* w;
		if (strcmp(info->version, "ver1.02") == 0) {
			wp->entries[group].flags |= 0x8000;
		}
		else {
			wp->entries[group].flags &= 0x7FFF;
		}
		PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
		wp->entries[group].rootMapObj = mapEntry(mapJoint, scale, group);
		wp->entries[group].rootHitObj = hitEntry(hitJoint, scale, group);
		{
			for (i = 0; i < ((s32*)wp->entries[group].lightTable)[0]; i++) {
				MapFileLightEx* light = (MapFileLightEx*)((u32*)wp->entries[group].lightTable)[i + 1];
				Vec pos;
				GXColor lcolor;
				s32 type = 1;
				s32 lflags = 0;
				PSVECScale(&light->position, &pos, 1.0f);
				if (!strcmp(light->type, "ambientLight")) {
					type = 0;
				}
				else if (!strcmp(light->type, "pointLight")) {
					type = 1;
				}
				else if (!strcmp(light->type, "directionalLight")) {
					type = 2;
				}
				else if (!strcmp(light->type, "spotLight")) {
					type = 3;
				}
				if (light->magic == 0x12D60D8) {
					lflags = light->lflags;
				}
				lcolor = light->color;
				((s32(*)(const char*, s32, Vec*, Vec*, GXColor*, f32, f32, s32, s32))lightEntry)(light->name, type, &pos, &light->rotation, &lcolor, light->spotAngle, light->attenAngle, light->attenType, lflags);
			}
		}
		mapResetPaperAmbColor();
		mapResetPaperCraftAmbColor();
		if ((&wo->entries[group])->fogTable != NULL) {
			wo->entries[group].fogEnable = ((s32*)(&wo->entries[group])->fogTable)[0];
			wp->entries[group].fogType = ((s32*)(&wo->entries[group])->fogTable)[1];
			wp->entries[group].fogStart = ((f32*)(&wo->entries[group])->fogTable)[2];
			wp->entries[group].fogEnd = ((f32*)(&wo->entries[group])->fogTable)[3];
			wp->entries[group].fogColor = ((GXColor*)(&wo->entries[group])->fogTable)[4];
			if (wo->entries[group].fogEnable != 0) {
				wp->entries[group].flags |= 1;
			}
		}
		else {
			wo->entries[group].fogEnable = 0;
			wp->entries[group].fogType = 0;
			wp->entries[group].fogStart = 0.0f;
			wp->entries[group].fogEnd = 0.0f;
			wp->entries[group].fogColor = (GXColor){0, 0, 0, 0};
			wp->entries[group].flags &= ~1;
		}
		if (activeGroup != 1) {
			sprintf(str1, "./m/%s/c", map);
			camLoadRoad(4, str1);
		}
		camSetTypePersp(4);
		mapBuildTexture(wp->entries[group].rootMapObj, wp->entries[group].tpl, (&wo->entries[group])->textureTable);
		{
			Vec mn;
			Vec mx;
			mapGetBoundingBox(&mn, &mx);
#define BBOX(idx, X, Y, Z) { Vec v = {0.0f, 0.0f, 0.0f}; v.x = X; v.y = Y; v.z = Z; wp->entries[group].bbox[idx] = v; }
			BBOX(0, mx.x, mx.y, mx.z)
			BBOX(1, mn.x, mx.y, mx.z)
			BBOX(2, mx.x, mn.y, mx.z)
			BBOX(3, mx.x, mx.y, mn.z)
			BBOX(4, mn.x, mn.y, mx.z)
			BBOX(5, mx.x, mn.y, mn.z)
			BBOX(6, mn.x, mx.y, mn.z)
			BBOX(7, mn.x, mn.y, mn.z)
#undef BBOX
		}
		w = &mapWork[activeGroup];
		e2 = &w->entries[group];
		animTbl = mapLoadFindChunk_(e2, "animation_table");
		if (animTbl != NULL) {
			w->entries[group].numAnims = animTbl[0];
			if (w->entries[group].numAnims != 0) {
				n = OSRoundUp32B(w->entries[group].numAnims * 32);
				w->entries[group].animData = _mapAlloc(n);
				memset(w->entries[group].animData, 0, n);
				{
					MapEntryAnimData* a = w->entries[group].animData;
					for (i = 0; i < e2->numAnims; i++) {
						a->flags = 0;
						MAPENT_FIELD(a, u32, 0x18) = *++animTbl;
						a++;
					}
				}
			}
		}
	}
	makeDisplayList(group);
	{
		MapWork* w3 = &mapWork[activeGroup];
		MapObject* o = w3->entries[group].objects;
		for (i = 0; i < w3->entries[group].numJoints; i++, o++) {
			MapJointDrawModeEx* dm;
			if (o->joints->partCount < 1 || o->joints->partCount > 8) {
				continue;
			}
			dm = (MapJointDrawModeEx*)o->joints->drawMode;
			if (dm->flags & 8) {
				continue;
			}
			if (dm->lightMask) {
				continue;
			}
			if (shadowGetCharShadowProjection() && (o->flags & 4)) {
				continue;
			}
			if (!(w3->entries[group].flags & 0x8000)) {
				continue;
			}
			o->flags |= 0x100;
		}
	}
	unk_80418458 = FALSE;
}
#endif

void hitReInit(void);


#ifdef NONMATCHING
void mapUnLoad(void) {
	MapEntry* entry2;
	MapEntry* entry;
	int i;
	MapWork* wp;

	sysWaitDrawSync();
	entry = mapWork->entries;
	wp = mapWork;
	activeGroup = i = 0;
	for (; i < wp->entries[0].count; entry++, i++) {
		if (entry->objects) {
			_mapFree(entry->objects);
			entry->numJoints = 0;
			entry->objects = NULL;
		}
		if (entry->animData) {
			_mapFree(entry->animData);
			entry->numAnims = 0;
			entry->animData = NULL;
		}
		if (entry->dispListBuf) {
			_mapFree(entry->dispListBuf);
			entry->dispListBuf = NULL;
			entry->dispListSize = 0;
		}
	}
	unk_80418458 = FALSE;
	hitReInit();
	lightReInit();
	envReInit();
	camUnLoadRoad(4);
	camSetTypePersp(4);
	entry2 = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry2++, i++) {
		if (entry2->dat) {
			if (!arcDataCheck(entry2->dat)) {
				_mapFree(entry2->dat);
			}
			entry2->dat = NULL;
		}
		if (entry2->tpl) {
			if (!arcDataCheck(entry2->tpl)) {
				_mapFree(entry2->tpl);
			}
			entry2->tpl = NULL;
		}
		if (entry2->arcData) {
			_mapFree(entry2->arcData);
			entry2->arcData = NULL;
		}
		strncpy(entry2->name, mapEmptyStr, sizeof(entry2->name));
	}
	arcDelete(1);
	memset(wp, 0, sizeof(MapWork));
}
#endif

#ifdef NONMATCHING
BOOL mapPreLoad(void) {
	return TRUE; //do nothing
}
#endif

#ifdef NONMATCHING
void mapLoad(const char* map) {
	MapWork* wp;

	MapWork* wp2;
	sysWaitDrawSync();
	wp2 = wp = mapWork;
	activeGroup = 0;

	memset(wp2, 0, sizeof(MapWork));
	_mapLoad(wp, 0, map);
	wp->entries[0].count = 1;
}
#endif

// FAKE: whole-function asm; best pure C 99.62 (loop-3 r30/r31 tie: const 0 vs mapWork)
#ifdef NONMATCHING
asm void bmapUnLoad(void) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    bl sysWaitDrawSync
    lwz r3, mapWork(r13)
    li r0, 0x1
    stw r0, activeGroup(r13)
    li r30, 0x0
    addi r31, r3, 0x2f4
    mr r29, r31
    b lbl_80028570
lbl_80028514:
    lwz r3, 0x154(r29)
    cmplwi r3, 0x0
    beq lbl_80028530
    bl _mapFree
    li r0, 0x0
    stw r0, 0x150(r29)
    stw r0, 0x154(r29)
lbl_80028530:
    lwz r3, 0x164(r29)
    cmplwi r3, 0x0
    beq lbl_8002854C
    bl _mapFree
    li r0, 0x0
    stw r0, 0x160(r29)
    stw r0, 0x164(r29)
lbl_8002854C:
    lwz r3, 0x16c(r29)
    cmplwi r3, 0x0
    beq lbl_80028568
    bl _mapFree
    li r0, 0x0
    stw r0, 0x16c(r29)
    stw r0, 0x168(r29)
lbl_80028568:
    addi r29, r29, 0x178
    addi r30, r30, 0x1
lbl_80028570:
    lwz r0, 0x0(r31)
    cmpw r30, r0
    blt lbl_80028514
    li r0, 0x0
    stw r0, unk_80418458(r13)
    bl hitReInit
    bl lightReInit
    bl envReInit
    mr r29, r31
    li r30, 0x0
    b lbl_8002861C
lbl_8002859C:
    lwz r3, 0x7c(r29)
    cmplwi r3, 0x0
    beq lbl_800285C4
    bl arcDataCheck
    cmpwi r3, 0x0
    bne lbl_800285BC
    lwz r3, 0x7c(r29)
    bl _mapFree
lbl_800285BC:
    li r0, 0x0
    stw r0, 0x7c(r29)
lbl_800285C4:
    lwz r3, 0x84(r29)
    cmplwi r3, 0x0
    beq lbl_800285EC
    bl arcDataCheck
    cmpwi r3, 0x0
    bne lbl_800285E4
    lwz r3, 0x84(r29)
    bl _mapFree
lbl_800285E4:
    li r0, 0x0
    stw r0, 0x84(r29)
lbl_800285EC:
    lwz r3, 0x8c(r29)
    cmplwi r3, 0x0
    beq lbl_80028604
    bl _mapFree
    li r0, 0x0
    stw r0, 0x8c(r29)
lbl_80028604:
    addi r3, r29, 0x6
    la r4, mapEmptyStr(r2)
    li r5, 0x10
    bl strncpy
    addi r29, r29, 0x178
    addi r30, r30, 0x1
lbl_8002861C:
    lwz r0, 0x0(r31)
    cmpw r30, r0
    blt lbl_8002859C
    li r3, 0x1
    bl arcDelete
    li r3, 0x2
    bl arcDelete
    mr r3, r31
    li r4, 0x0
    li r5, 0x2f4
    bl memset
    li r31, 0x0
    lwz r30, mapWork(r13)
    stw r31, activeGroup(r13)
    mr r29, r30
    b lbl_800286D8
lbl_8002865C:
    lwz r0, 0x170(r29)
    cmplwi r0, 0x0
    beq lbl_800286A8
    lwz r3, 0x80(r29)
    bl _mapAllocTail
    stw r3, 0x7c(r29)
    lwz r3, 0x88(r29)
    bl _mapAllocTail
    stw r3, 0x84(r29)
    lwz r3, 0x170(r29)
    lwz r4, 0x7c(r29)
    bl aramMgrToMram
    lwz r3, 0x178(r29)
    lwz r4, 0x84(r29)
    bl aramMgrToMram
    li r0, 0x0
    stw r0, 0x170(r29)
    stw r0, 0x178(r29)
    b lbl_800286C8
lbl_800286A8:
    lwz r3, 0x90(r29)
    bl _mapAllocTail
    stw r3, 0x8c(r29)
    lwz r3, 0x174(r29)
    lwz r4, 0x8c(r29)
    bl aramMgrToMram
    li r0, 0x0
    stw r0, 0x174(r29)
lbl_800286C8:
    mr r3, r31
    bl makeDisplayList
    addi r29, r29, 0x178
    addi r31, r31, 0x1
lbl_800286D8:
    lwz r0, 0x0(r30)
    cmpw r31, r0
    blt lbl_8002865C
    lwz r4, 0x8c(r30)
    cmplwi r4, 0x0
    beq lbl_800286FC
    lwz r5, 0x90(r30)
    li r3, 0x1
    bl arcEntry
lbl_800286FC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
#endif

#ifdef NONMATCHING
void bmapLoad(const char *map, const char *map2)
{
  MapWork *wp;
  MapEntry *entry;
  MapEntry *e;
  int i;
  sysWaitDrawSync();
  activeGroup = 0;
  wp = mapGetWork();
  for (i = 0; i < wp->entries[0].count; i++)
  {
    e = &mapWork[activeGroup].entries[i];
    entry = &wp->entries[i];
    if (e->dispListBuf)
    {
      _mapFree(e->dispListBuf);
    }
    e->dispListSize = 0;
    e->dispListBuf = (void *) 0;
    // NB: +0x178 is past sizeof(MapEntry) (0x178): it is the next entry's count (or MapWork.field_2F0 for entry 1).
    // The original strides entries by 0x178 everywhere, so this matches the game; the real layout is probably
    // MapWork { s32 count; entries } with a tplAram as each entry's last field (all MapEntry offsets +4).
    entry->datAram = (void *) 0;
    *((void **) (((u8 *) entry) + 0x178)) = (void *) 0;
    entry->arcAram = (void *) 0;
    if (entry->dat)
    {
      if (!arcDataCheck(entry->dat))
      {
        entry->datAram = aramMgrToAram(entry->dat, entry->datSize);
        *((ARAMEntry **) (((u8 *) entry) + 0x178)) = aramMgrToAram(entry->tpl, entry->tplSize);
        _mapFree(entry->tpl);
        _mapFree(entry->dat);
        entry->tpl = (void *) 0;
        entry->dat = (void *) 0;
      }
      else
      {
        entry->arcAram = aramMgrToAram(entry->arcData, entry->arcSize);
        _mapFree(entry->arcData);
        entry->arcData = (void *) 0;
      }
    }
  }

  wp = (0, &mapWork[1]);
  activeGroup = 1;
  memset(wp, 0, sizeof(MapWork));
  _mapLoad(wp, 0, map);
  wp->entries[0].count = 1;
  if (map2)
  {
    _mapLoad(wp, 1, map2);
    wp->entries[0].count = 2;
  }
}
#endif

typedef struct MapAnimKeyCh {
	f32 value;  // 0x0
	f32 tanIn;  // 0x4
	f32 tanOut; // 0x8
	f32 unkC;   // 0xC
	s32 step;   // 0x10
} MapAnimKeyCh;

typedef struct MapAnimKey {
	f32 time;             // 0x0
	MapAnimKeyCh ch[21];  // 0x4
} MapAnimKey;

typedef struct MapAnimJoint {
	u8 field_0x0[0x4 - 0x0];    // 0x0
	f32 base[9];                // 0x4
	u8 field_0x28[0x58 - 0x28]; // 0x28
	s32 keyCount;               // 0x58
	MapAnimKey keys[];          // 0x5C
} MapAnimJoint;
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint);

#ifdef NONMATCHING
static inline f32 mapHermite(f32 cur, f32 t0, f32 t1, f32 p0, f32 m0, f32 p1, f32 m1) {
	f32 s = cur - t0;
	f32 dt = t1 - t0;
	f32 t = s / (!dt ? 1e-8f : dt);
	f32 t2 = t * t;
	f32 t3 = t2 * t;

	return p0 * (2.0f * t3 - 3.0f * t2 + 1.0f)
		+ m0 * (dt * (t3 - 2.0f * t2 + t))
		+ p1 * (-2.0f * t3 + 3.0f * t2)
		+ m1 * (dt * (t3 - t2));
}
#endif


#ifdef NONMATCHING
static inline f32 mapHermiteCh(f32 cur, f32 t0, f32 t1, MapAnimKeyCh* a, MapAnimKeyCh* b) {
	f32 s = cur - t0;
	f32 dt = t1 - t0;
	f32 m1 = b->tanIn;
	f32 p1 = b->value;
	f32 m0 = a->tanOut;
	f32 p0 = a->value;
	f32 t = s / (!dt ? 1e-8f : dt);
	f32 t2 = t * t;
	f32 t3 = t2 * t;

	return p0 * (2.0f * t3 - 3.0f * t2 + 1.0f)
		+ m0 * (dt * (t3 - 2.0f * t2 + t))
		+ p1 * (-2.0f * t3 + 3.0f * t2)
		+ m1 * (dt * (t3 - t2));
}
#endif

#ifdef NONMATCHING
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint) {
	f32 v[21];
	Mtx mT;
	Mtx mS;
	Mtx mX;
	Mtx mY;
	Mtx mZ;
	Mtx m;
	f32 dx, dy, dz, rx, ry, sx, sy, sz, rz;
	f32 cur, t, t2, t3, dt;
	int c;
	int i;
	MapAnimKey* k0;
	MapAnimKey* k1;


	for (i = 1; i < joint->keyCount; i++) {
		k1 = &joint->keys[i];
		k0 = &joint->keys[i - 1];
		if (anim->time <= k1->time) {
			cur = anim->time;
		}
		else if (i == joint->keyCount - 1) {
			cur = k1->time;
		}
		else {
			continue;
		}
		for (c = 0; c < 9; c++) {
			if (k0->ch[c].step) {
				v[c] = k0->ch[c].value;
			}
			else {
				v[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
			}
		}
		dx = v[0] - joint->base[0];
		dy = v[1] - joint->base[1];
		dz = v[2] - joint->base[2];
		rx = v[3] - joint->base[3];
		ry = v[4] - joint->base[4];
		rz = v[5] - joint->base[5];
		sx = v[6] / joint->base[6];
		sy = v[7] / joint->base[7];
		sz = v[8] / joint->base[8];
		if (dx || dy || dz) {
			PSMTXTrans(mT, dx, dy, dz);
		}
		if (rx) {
			PSMTXRotRad(mX, 'x', 0.017453292f * rx);
		}
		if (ry) {
			PSMTXRotRad(mY, 'y', 0.017453292f * ry);
		}
		if (rz) {
			PSMTXRotRad(mZ, 'z', 0.017453292f * rz);
		}
		PSMTXScale(mS, sx, sy, sz);
		PSMTXIdentity(m);
		if (dx || dy || dz) {
			PSMTXConcat(m, mT, m);
		}
		if (rz) {
			PSMTXConcat(m, mZ, m);
		}
		if (ry) {
			PSMTXConcat(m, mY, m);
		}
		if (rx) {
			PSMTXConcat(m, mX, m);
		}
		if (sx || sy || sz) {
			PSMTXConcat(m, mS, m);
		}
		PSMTXConcat(in, m, out);
		return;
	}
}
#endif

#ifdef NONMATCHING
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force) {
	BOOL dirty = FALSE;

	if (obj->flags & 0x200) {
		dirty = TRUE;
	}
	if (force) {
		dirty = TRUE;
	}
	if (dirty) {
		if (obj->flags & 0x2000) {
			PSMTXConcat(mtx, obj->unk7C, obj->modelWorldMtx);
		}
		else {
			PSMTXConcat(mtx, obj->localMtx, obj->modelWorldMtx);
		}
		if (obj->flags & 0x200000) {
			PSMTXConcat(obj->modelWorldMtx, obj->unkAC, obj->modelWorldMtx);
		}
		obj->flags &= ~0x200;
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, TRUE);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
	else {
		if (obj->child) {
			mapReCalcMatrix(obj->child, obj->modelWorldMtx, force);
		}
		if (obj->next) {
			mapReCalcMatrix(obj->next, mtx, force);
		}
	}
}
#endif

typedef struct MapAnimNm {
	const char** name; // 0x0
	u8* data;          // 0x4
} MapAnimNm;

typedef struct MapAnimList {
	s32 count;
	MapAnimNm* items[1];
} MapAnimList;

typedef struct MapAnimKey4 {
	f32 time;
	MapAnimKeyCh ch[4];
} MapAnimKey4;

typedef struct MapAnimKey5 {
	f32 time;
	MapAnimKeyCh ch[5];
} MapAnimKey5;

typedef struct MapAnimKey9 {
	f32 time;
	MapAnimKeyCh ch[9];
} MapAnimKey9;

typedef struct MapAnimMatData {
	const char* name;
	s32 idx;
	f32 u;
	f32 v;
	s32 keyCount;
	MapAnimKey5 keys[1];
} MapAnimMatData;

typedef struct MapAnimAlphaData {
	const char* name;
	s32 keyCount;
	MapAnimKey4 keys[1];
} MapAnimAlphaData;

typedef struct MapAnimLightData {
	const char* name;
	s32 keyCount;
	MapAnimKey9 keys[1];
} MapAnimLightData;

typedef struct MapAnimLightData2 {
	const char* name;
	s32 keyCount;
	MapAnimKey5 keys[1];
} MapAnimLightData2;


#ifdef NONMATCHING
static inline void mapMainMatKeys_(MapAnim* a_, MapAnimMatData* d, u8* obj) {
	int n, c;
	f32 cur;
	for (n = 1; n < d->keyCount; n++) {
		MapAnimKey5* k0 = &d->keys[n - 1];
		MapAnimKey5* k1 = &d->keys[n];
		if (a_->time <= k1->time) {
			cur = a_->time;
		}
		else if (n == d->keyCount - 1) {
			cur = k1->time;
		}
		else { continue; }

		for (c = 0; c < 5; c++) {
			if (k0->ch[c].step) {
				*(f32*)(obj + d->idx * 0x1c + c * 4 + 0x2c) = k0->ch[c].value;
			}
			else {
				*(f32*)(obj + d->idx * 0x1c + c * 4 + 0x2c) = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
			}
		}
		*(f32*)(obj + d->idx * 0x1c + 0x40) = d->u;
		*(f32*)(obj + d->idx * 0x1c + 0x44) = d->v;
		break;
	}
}
#endif
#ifdef NONMATCHING
static inline void mapMainAlphaKeys_(MapAnim* a_, MapAnimAlphaData* d, u8* obj) {
	int n;
	f32 cur;
	for (n = 1; n < d->keyCount; n++) {
		MapAnimKey4* k0 = &d->keys[n - 1];
		MapAnimKey4* k1 = &d->keys[n];

		cur = a_->time;
		if (cur <= d->keys[n].time) {
			cur = a_->time;
		}
		else if (n == d->keyCount - 1) {
			cur = k1->time;
		}
		else { continue; }

		if (k0->ch[0].step) {
			*(u8*)(obj + 0x10c) = (u8)(255.0f - 255.0f * k0->ch[0].value);
		}
		else {
			*(u8*)(obj + 0x10c) = (u8)(255.0f - 255.0f * mapHermiteCh(cur, k0->time, k1->time, (MapAnimKeyCh*)&k0->ch[0], (MapAnimKeyCh*)&k1->ch[0]));
		}

		break;
	}
}
#endif
#ifdef NONMATCHING
static inline void mapMainLight_ll(MapAnim* anim, LightEntry* lp, MapAnimLightData* d, f32* v) {
	int n, c;
	f32 cur;

						
						for (n = 1; n < d->keyCount; n++) {
							MapAnimKey9* k0 = &d->keys[n - 1];
							MapAnimKey9* k1 = &d->keys[n];
							if (anim->time <= k1->time) {
								cur = anim->time;
							}
							else if (n == d->keyCount - 1) {
								cur = k1->time;
							}
							else {
								continue;
							}
							for (c = 0; c < 9; c++) {
								if (k0->ch[c].step) {
									v[c] = k0->ch[c].value;
								}
								else {
									v[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
								}
							}
							lp->position.x = 10.0f * v[0];
							lp->position.y = 10.0f * v[1];
							lp->position.z = 10.0f * v[2];
							lp->rotation.x = v[3];
							lp->rotation.y = v[4];
							lp->rotation.z = v[5];
							break;
						}
					}
#endif
#ifdef NONMATCHING
static inline void mapMainLight_lc(MapAnim* anim, LightEntry* lp, MapAnimLightData2* d, f32* cv) {
	int n, c;
	f32 cur;

						
						for (n = 1; n < d->keyCount; n++) {
							MapAnimKey5* k0 = &d->keys[n - 1];
							MapAnimKey5* k1 = &d->keys[n];
							if (anim->time <= k1->time) {
								cur = anim->time;
							}
							else if (n == d->keyCount - 1) {
								cur = k1->time;
							}
							else {
								continue;
							}
							for (c = 0; c < 5; c++) {
								if (k0->ch[c].step) {
									cv[c] = k0->ch[c].value;
								}
								else {
									cv[c] = mapHermiteCh(cur, k0->time, k1->time, &k0->ch[c], &k1->ch[c]);
								}
							}
							lp->color.r = (u8)(255.0f * cv[0]);
							lp->color.g = (u8)(255.0f * cv[1]);
							lp->color.b = (u8)(255.0f * cv[2]);
							lp->color.a = 0xff;
							lp->spotAngle = cv[4];
							lp->attenAngle = cv[3];
							break;
						}
					}
#endif

#ifdef NONMATCHING
static inline u8* mapMainFindTbl_(const char* nm_) {
	MapEntry* e_;
	MapWork* w_;
	int j_;
	u32* pr_;
	int i_;
	w_ = &mapWork[activeGroup];

	for (i_ = 0; i_ < w_->entries[0].count; i_++) {
		e_ = &w_->entries[i_];
		if (!((u32*)e_->materialNameTable)) {
			return NULL;
		}
		for (j_ = 0; j_ < (s32)((u32*)e_->materialNameTable)[0]; j_++) {
			pr_ = (u32*)&((struct { u32 n_; struct { const char* nm; u8* p; } e_[1]; }*)((u32*)e_->materialNameTable))->e_[j_];
			if (!strcmp((const char*)pr_[0], nm_)) {
				return (u8*)pr_[1];
			}
		}
	}
	return NULL;
}
#endif

#define mapMainMat(a_, i_, b_, x_) \
{ \
	u8* obj; \
	strcpy(b_, (const char*)i_->name); \
	if (x_) { \
		strcat(b_, x_); \
	} \
	obj = mapMainFindTbl_(b_); \
	if (obj) { \
		mapMainMatKeys_(a_, (void*)i_, obj); \
	} \
}

#define mapMainAlpha(a_, i_, b_, x_) \
{ \
	u8* obj; \
	strcpy(b_, (const char*)i_->name); \
	if (x_) { \
		strcat(b_, x_); \
	} \
	obj = mapMainFindTbl_(b_); \
	if (obj) { \
		mapMainAlphaKeys_(a_, (void*)i_, obj); \
	} \
}

#ifdef NONMATCHING
void mapMain(void) {
	int i_, j_;
	MapEntry* e_;
	MapWork* w_;
	MapObject* o;
	MapObject* o_;
	s32 c, n;
	f32 cur;
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry;
	char mbuf[0x100];
	s32 i, j;
	s32 k;
	MapAnim* anim;
	BOOL changed;
	OSTime ms, t;
	char abuf[0x100];
	Mtx scale;
	f32 v[9];
	f32 cv[5];

	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		changed = FALSE;
		anim = (MapAnim*)entry->animData;
		for (j = 0; j < entry->numAnims; j++, anim++) {
			MapAnimList* jl = MAPENT_FIELD(anim->anim, MapAnimList*, 0xC);
			MapAnimList* ml = MAPENT_FIELD(anim->anim, MapAnimList*, 0x10);
			MapAnimList* al = MAPENT_FIELD(anim->anim, MapAnimList*, 0x14);
			MapAnimList* ll = MAPENT_FIELD(anim->anim, MapAnimList*, 0x18);
			MapAnimList* lc = MAPENT_FIELD(anim->anim, MapAnimList*, 0x1C);

			if (!(anim->flags & 1) || (anim->flags & 2)) {
				continue;
			}
			if (anim->flags & 0x100) {
				t = gp->systemLv0Time;
			}
			else if (anim->flags & 0x200) {
				t = gp->systemLv1Time;
			}
			else if (anim->flags & 0x400) {
				t = gp->systemLv2Time;
			}
			else if (anim->flags & 0x800) {
				t = gp->systemLv3Time;
			}
			else if (gp->inBattle) {
				t = gp->renderTime;
			}
			else {
				t = gp->renderFieldTime;
			}
			if (!(anim->flags & 0x10)) {
				ms = OSTicksToMilliseconds(t);
				cur = gp->framerate * (f32)(u64)(ms - anim->startTime) / 1000.0f;
				if (cur < anim->time) {
					anim->time = anim->time - (anim->time - cur);
				}
				else {
					anim->time = anim->time + anim->rate * (cur - anim->time);
				}
				anim->startTime = OSTicksToMilliseconds(t);
				anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
			}
			else if (anim->flags & 0x20) {
				anim->startTime = OSTicksToMilliseconds(t);
				anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
				anim->flags &= ~0x20;
				anim->flags &= ~0x10;
			}
			if (anim->time >= anim->anim->length) {
				if (anim->flags & 4) {
					f32 t2 = anim->time;
					while (t2 > anim->anim->length) {
						t2 -= anim->anim->length;
					}
					anim->time = t2;
					anim->startTime = OSTicksToMilliseconds(t);
					anim->startTime -= (u64)(1000.0f * anim->time / gp->framerate);
				}
				else {
					anim->time = anim->anim->length;
					anim->flags |= 2;
				}
			}
			if (jl) {
				for (k = 0; k < jl->count; k++) {
					o = mapGetMapObj((const char*)jl->items[k]->name);
					if (o) {
						mapCalcAnimMatrix(o->unk7C, o->localMtx, anim, (MapAnimJoint*)jl->items[k]);
						changed = TRUE;
						o->flags |= 0x2000;
						o->flags |= 0x200;
					}
				}
			}
			if (ml) {
				for (k = 0; k < ml->count; k++) {
					mapMainMat(anim, ml->items[k], mbuf, NULL);
					mapMainMat(anim, ml->items[k], mbuf, "_v");
					mapMainMat(anim, ml->items[k], mbuf, "_v_x");
				}
			}
			if (al) {
				for (k = 0; k < al->count; k++) {
					mapMainAlpha(anim, al->items[k], abuf, NULL);
					mapMainAlpha(anim, al->items[k], abuf, "_v");
					mapMainAlpha(anim, al->items[k], abuf, "_v_x");
				}
			}
			if (ll) {
				for (k = 0; k < ll->count; k++) {
					LightEntry* lp = lightNameToPtr((const char*)ll->items[k]->name);
					if (lp) {
						mapMainLight_ll(anim, lp, (MapAnimLightData*)ll->items[k], v);
					}
				}
			}
			if (lc) {
				for (k = 0; k < lc->count; k++) {
					LightEntry* lp = lightNameToPtr((const char*)lc->items[k]->name);
					if (lp) {
						mapMainLight_lc(anim, lp, (MapAnimLightData2*)lc->items[k], cv);
					}
				}
			}
		}
		if (changed) {
			PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
			mapReCalcMatrix(entry->rootMapObj, scale, 0);
		}
	}
}
#endif

typedef struct MapTexXform {
	f32 tx;  // 0x0
	f32 ty;  // 0x4
	f32 sx;  // 0x8
	f32 sy;  // 0xC
	f32 rot; // 0x10
	f32 cx;  // 0x14
	f32 cy;  // 0x18
} MapTexXform;

typedef struct MapMatSampler {
	MapTexInfo* tex; // 0x0
	u8 pad4[4];      // 0x4
	u8 wrapS;        // 0x8
	u8 wrapT;        // 0x9
} MapMatSampler;

void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
typedef struct MapMaterial {
	char* name;                  // 0x0
	GXColor color;               // 0x4
	u8 lightMode;                // 0x8
	u8 pad9[2];                  // 0x9
	u8 samplerCount;             // 0xB
	MapMatSampler* samplers[8];  // 0xC
	MapTexXform xforms[8];       // 0x2C
	GXColor blendColor;          // 0x10C, last-stage blend colour (translucency test, mapSetMaterialLastStageBlend)
	u8* tevMode;                 // 0x110
} MapMaterial;
void mapSetTextureMatrix(MapMaterial* mat);

void _mapDispMapObj(CameraId cam, MapObject *obj);
void _mapDispMapObj(CameraId cam, MapObject* obj);
static inline void mapSetObjFog(MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
extern const GXCullMode culling[4];
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetTextureMatrix(MapMaterial* mat);
void mapSetTextureMatrix(struct MapMaterial* mat);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);

#ifdef NONMATCHING
static inline BOOL mapObjIsTranslucent(u32 flags, GXColor objColor, GXColor matColor) {
	if ((flags & 0x40) && objColor.a != 0xFF) {
		return TRUE;
	}
	if (matColor.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x800) && (mapGetWork()->entries[0].flags & 2) && mapGetWork()->entries[0].blend.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x1000) && (mapGetWork()->entries[0].flags & 4) && mapGetWork()->entries[0].blend2.a != 0xFF) {
		return TRUE;
	}
	return FALSE;
}
#endif

#ifdef NONMATCHING
static inline void callPackedLists(MapFileMesh* mesh) {
  int j;
  for (j = 0; j < mesh->displayListCount; j++)
  {
    GXCallDisplayList((void *) mesh->displayLists.packedLists[j].offset, *((u32 *) (&mesh->displayLists.packedLists[j].vertexCount)));
  }
}
#endif

#ifdef NONMATCHING
void _mapDispMapObj(CameraId cam, MapObject *obj)
{
  CameraEntry *camera;
  CameraEntry *cur;
  MapFileJoint *joint;
  f32 scale;
  s32 n;
  s32 mode;
  GXCullMode cull;
  f32 d;
  Mtx mtx;
  Mtx nrm;
  f32 proj[7];
  MapFileMesh *mesh;
  int i;
  MapWork *wp;
  int j;
  void *material;
  camera = camGetPtr(cam);
  current_mp = obj;
  if (!(obj->flags & 0x20))
  {
    goto setup;
  }
  if (obj->flags & 0x8000)
  {
    n = 0;
    for (joint = obj->joints; joint->prev; joint = joint->prev)
    {
    }

    for (; joint != obj->joints; joint = joint->next)
    {
      n++;
    }

    scale = 0.01f * n;
    GXGetProjectionv(proj);
    d = 1.0f;
    d = (d * (camera->far + camera->near)) * (d + scale);
    proj[5] *= 1.0f + ((scale * (((-2.0f) * camera->far) * camera->near)) / d);
    GXSetProjectionv(proj);
  }
  mode = obj->blendMode;
  if (obj->joints->partCount > 0)
  {
    if (mapObjIsTranslucent(obj->flags, obj->color, *((GXColor *) (((u8 *) obj->joints->parts[0].material) + 0x10C))))
    {
      mode = 2;
    }
  }
  switch (mode)
  {
    case 0:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 7);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 1);
      break;

    case 3:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 0, GX_LEQUAL, (GXBool) 0);
      break;

    case 1:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 0);
      GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 1);
      break;

    case 4:
      GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
      GXSetZCompLoc((GXBool) 0);
      GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
      GXSetZMode((GXBool) 0, GX_LEQUAL, (GXBool) 0);
      break;

    case 2:

    case 5:

    default:
      GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, 0);
      GXSetZCompLoc((GXBool) 1);
      GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
      GXSetZMode((GXBool) 1, GX_LEQUAL, (GXBool) 0);
      break;

  }

  setup:
  if (cam == 1)
  {
    GXSetZCompLoc((GXBool) 0);
  }

  PSMTXConcat(camera->view, obj->modelWorldMtx, mtx);
  GXLoadPosMtxImm(mtx, 0);
  if (!(obj->flags & 0x100))
  {
    PSMTXInvXpose(mtx, nrm);
    GXLoadNrmMtxImm(nrm, 0);
  }
  GXSetCurrentMtx(0);
  GXGetCullMode(&cull);
  if (cull != culling[obj->joints->drawMode->cullMode])
  {
    GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
  }
  mapSetObjFog(obj);
  if (obj->flags & 0x20)
  {
    if (obj->flags & 0x4000)
    {
      goto end;
    }
    if ((obj->flags & 1) && (!(obj->flags & 0x80)))
    {
      goto end;
    }
    if ((obj->flags & 0x40) && (obj->color.a == 0))
    {
      goto end;
    }
  }
  if (obj->flags & 0x100)
  {
    for (i = 0; i < obj->joints->partCount; i++)
    {
      mesh = obj->joints->parts[i].mesh;
      material = obj->joints->parts[i].material;
      mapSetTextureMatrix(material);
      mapSetMaterialLastStageBlend(obj->flags, obj->color, *((GXColor *) (((u8 *) material) + 0x10C)));
      mapSetPolygonVtxDesc(obj, mesh);
      GXCallDisplayList(((MapObjectDL *) obj)->dl[i], ((MapObjectDL *) obj)->dlSize[i]);
      callPackedLists(mesh);

    }

  }
  else
  {
    for (i = 0; i < obj->joints->partCount; i++)
    {
      material = obj->joints->parts[i].material;
      mesh = obj->joints->parts[i].mesh;
      mapSetTextureMatrix(material);
      mapSetMaterialLastStageBlend(obj->flags, obj->color, *((GXColor *) (((u8 *) material) + 0x10C)));
      mapSetMaterial(obj, material);
      mapSetPolygon(obj, mesh);
    }

  }
  end:
  if (obj->flags & 0x8000)
  {
    GXSetProjection(camera->projection, camera->projType);
  }

  if (obj->flags & 0x0F000000)
  {
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevDirect(GX_TEVSTAGE3);
    GXSetTevDirect(GX_TEVSTAGE4);
    GXSetNumIndStages(0);
  }
}
#endif


#ifdef NONMATCHING
void _mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
	if (obj->child) {
		_mapDispMapGrp(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp(cam, obj->next);
	}
}
#endif

#ifdef NONMATCHING
void mapDispMapObj(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
}
#endif

#ifdef NONMATCHING
void mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapGrp(cam, obj);
}
#endif

#ifdef NONMATCHING
void mapDispMapObj_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapObj(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}
#endif

#ifdef NONMATCHING
void mapDispMapGrp_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}
#endif

#ifdef NONMATCHING
void test_kururing_mapdisp(CameraId cam) {
	MapWork* wp = &mapWork[activeGroup];
	MapEntry* entry = wp->entries;
	u32 flags;
	int j;
	int i;
	MapObject* obj;

	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		obj = entry->objects;
		for (j = 0; j < entry->numJoints; j++, obj++) {
			flags = obj->flags;
			if (flags & 0x400000) {
				obj->flags = flags & ~2;
				_mapDispMapObj(cam, obj);
				obj->flags = flags;
			}
		}
	}
}
#endif

#ifdef NONMATCHING
void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj) {
	Mtx mtx;
	Mtx nrm;
	int i;

	PSMTXConcat(camGetPtr(cam)->view, obj->modelWorldMtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	PSMTXInvXpose(mtx, nrm);
	GXLoadNrmMtxImm(nrm, 0);
	GXSetCurrentMtx(0);
	GXSetCullMode(GX_CULL_ALL);
	GXSetNumChans(1);
	GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	for (i = 0; i < obj->joints->partCount; i++) {
		mapSetPolygon(obj, obj->joints->parts[i].mesh);
	}
}
#endif

#ifdef NONMATCHING
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj) {
	_mapDispMapObj_NoMaterial(cam, obj);
	if (obj->child) {
		_mapDispMapGrp_NoMaterial(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp_NoMaterial(cam, obj->next);
	}
}
#endif

#ifdef NONMATCHING
void mapDispMapObj_bbox(CameraId cam, MapObject* obj) {

	int new_var[2];
	Mtx nrm;
	Mtx mtx;

	sysWaitDrawSync();
	GXClearBoundingBox();
	PSMTXConcat(camGetPtr(cam)->view, obj->modelWorldMtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	PSMTXInvXpose(mtx, nrm);
	GXLoadNrmMtxImm(nrm, 0);
	GXSetCurrentMtx(0);
	GXSetCullMode(GX_CULL_ALL);
	GXSetNumChans(1);
	GXSetChanMatColor(GX_COLOR0A0, (GXColor){0, 0, 0, 0});
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTexGens(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
	for (new_var[1] = 0, new_var[0] = 0; obj->joints->partCount > new_var[1]; new_var[0] += 8, new_var[1]++) {
		mapSetPolygon(obj, *(void**)((u8*)obj->joints + 0x64 + new_var[0]));
	}
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}
#endif

#ifdef NONMATCHING
void mapDispMapGrp_bbox(CameraId cam, MapObject* obj) {
	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp_NoMaterial(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}
#endif

#ifdef NONMATCHING
#ifdef NONMATCHING
const GXTexMtx texmtx_tbl[10] = {GX_TEXMTX0, GX_TEXMTX1, GX_TEXMTX2, GX_TEXMTX3, GX_TEXMTX4, GX_TEXMTX5, GX_TEXMTX6, GX_TEXMTX7, GX_TEXMTX8, GX_TEXMTX9};
#endif
#ifdef NONMATCHING
const s32 texfmt_tbl[11] = {4, 5, 6, 14, 0, 1, 2, 3, 8, 9, 10};
#endif
#ifdef NONMATCHING
const s32 texwrap_tbl[3] = {GX_CLAMP, GX_REPEAT, GX_MIRROR};
#endif
#ifdef NONMATCHING
const s32 palfmt_tbl[2] = {1, 2};
#endif
#ifdef NONMATCHING
const GXLightID lightid_tbl[8] = {GX_LIGHT0, GX_LIGHT1, GX_LIGHT2, GX_LIGHT3, GX_LIGHT4, GX_LIGHT5, GX_LIGHT6, GX_LIGHT7};
#endif
static inline BOOL mapClipTest(Vec* v) {
	if (v->z > -1.0f && v->z < 0.0f && v->x >= -1.0f && v->x <= 1.0f && v->y >= -1.0f && v->y <= 1.0f) {
		return TRUE;
	}
	return FALSE;
}
#endif

void dispEntry(CameraId camera, f32 order, s32 renderMode, void* callback, void* param);
#define MAP_CLIP_IN(v) ((v).z > -1.0f && (v).z < 0.0f && (v).x >= -1.0f && (v).x <= 1.0f && (v).y >= -1.0f && (v).y <= 1.0f)
#define MJF(j, off) (*(f32*)((u8*)(j) + (off)))

#ifdef NONMATCHING
void mapDisp(void) {
	MapWork* wp = &mapWork[activeGroup];
	CameraEntry* camera = camGetPtr(4);
	MapEntry* entry;
	MapObject* obj;
	int j, i;
	Mtx scale;
	Mtx mtx;
	Vec v;
	Vec center;
	f32 z;
	s32 mode;
	u8* joint;
	BOOL clipped;

	if (unk_80418458) {
		return;
	}
	entry = wp->entries;
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		if (entry->rootMapObj != NULL) {
			PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
			mapReCalcMatrix(entry->rootMapObj, scale, 0);
		}
		obj = entry->objects;
		for (j = 0; j < entry->numJoints; j++, obj++) {
			if (obj->flags & 0x4000) continue;
			if ((obj->flags & 1) && !(obj->flags & 0x80)) continue;
			if ((obj->flags & 0x40) && obj->color.a == 0) continue;
			if (obj->flags & 0x20000000) {
				obj->screenRect[2] = 0;
				obj->screenRect[3] = 0;
				obj->screenRect[0] = 0;
				obj->screenRect[1] = 0;
			}
			if (obj->flags & 0x20) continue;
			if (!(obj->flags & 0x10) && *(s32*)((u8*)obj->joints + 0x5C) < 1) continue;
			if (!(obj->flags & 0x800) && (entry->flags & 2) && entry->blend.a == 0) continue;
			if (!(obj->flags & 0x1000) && (entry->flags & 4) && entry->blend2.a == 0) continue;
			PSMTXConcat(camera->view, obj->modelWorldMtx, mtx);
			if ((obj->flags & 2) && !mapClipOffFlag) {
				joint = (u8*)obj->joints;
				clipped = FALSE;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x50);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x48); v.y = MJF(joint, 0x40); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				v.x = MJF(joint, 0x3C); v.y = MJF(joint, 0x4C); v.z = MJF(joint, 0x44);
				PSMTXMultVec(mtx, &v, &v);
				PSMTX44MultVec(camera->projection, &v, &v);
				if (MAP_CLIP_IN(v)) goto vis;
				clipped = TRUE;
			vis:
				if (clipped) continue;
			}
			PSMTXMultVec(mtx, &obj->center, &center);
			PSMTX44MultVec(camera->projection, &center, &center);
			z = 5000.0f * center.z + 5000.0f;
			if (z < 0.0f) {
				z = 0.0f;
			} else if (z > 10000.0f) {
				z = 10000.0f;
			}
			z *= -1.0f;
			mode = obj->blendMode;
			if (*(s32*)((u8*)obj->joints + 0x5C) > 0) {
				if (mapObjIsTranslucent(obj->flags, obj->color,
						(*(MapMaterial**)((u8*)obj->joints + 0x60))->blendColor)) {
					mode = 2;
				}
			}
			if (obj->flags & 0x20000000) {
				dispEntry((CameraId)1, 5000.0f, 3, !(obj->flags & 0x10) ? mapDispMapObj_bbox : mapDispMapGrp_bbox, obj);
			}
			if (obj->flags & 0x80) {
				dispEntry((CameraId)1, z, mode, !(obj->flags & 0x10) ? mapDispMapObj_off : mapDispMapGrp_off, obj);
			}
			if (!(obj->flags & 1)) {
				dispEntry(obj->unk5, z, mode, !(obj->flags & 0x10) ? mapDispMapObj : mapDispMapGrp, obj);
			}
		}
	}
}
#endif


typedef struct MapFileLight {
	const char* name; // 0x0
} MapFileLight;

typedef struct MapFileLightTable {
	s32 count;              // 0x0
	MapFileLight* lights[]; // 0x4
} MapFileLightTable;

#define MAP_LIGHT_TABLE(entry) ((MapFileLightTable*)(entry)->lightTable)

#ifdef NONMATCHING
s32 mapSetLight(MapObject* obj, LightEntry** lights) {
	Vec pos;
	s32 count;
	s32 i;
	LightEntry* light;
	MapJointDrawModeEx* dm;

	count = 0;
	PSMTXMultVec(obj->modelWorldMtx, &obj->center, &pos);
	dm = (MapJointDrawModeEx*)obj->joints->drawMode;
	if (dm->flags & 8) {
		if (!dm->lightMask) {
			count = lightGetNearObj(&pos, lights, 8, 0);
		}
		else {
			for (i = 0; i < 32; i++) {
				if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
					light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
					if (!(light->flags & 0x8000)) {
						lights[count] = light;
						count++;
						if (count >= 8) {
							break;
						}
					}
				}
			}
			if (count < 8) {
				count += lightGetNearObj(&pos, &lights[count], 8 - count, 0);
			}
		}
	}
	else if (dm->lightMask) {
		for (i = 0; i < 32; i++) {
			if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
				light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
				if (!(light->flags & 0x8000)) {
					lights[count] = light;
						count++;
					if (count >= 8) {
						break;
					}
				}
			}
		}
	}
	else {
		count = 0; // FAKE: redundant (count is already 0); the target emits this else branch
	}
	return count;
}
#endif


static u32 texture_0[64] ATTRIBUTE_ALIGN(32) = {
	0xEB88E228, 0x55FFAA00, 0x00000000, 0x00000000,
	0xF528EC08, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFEE8F5A8, 0x55FFAA00, 0x00000000, 0x00000000,
	0xFF47D6E8, 0x00AAFF55, 0x00000000, 0x00000000,
	0xBEA8860A, 0x00AAFF55, 0x00000000, 0x00000000,
	0x7DEA0D8B, 0x00AAFF55, 0x00000000, 0x00000000,
	0x056B054A, 0x00AAAA00, 0x00000000, 0x00000000,
	0x056B054E, 0x0000AAFF, 0x00000000, 0x00000000,
	0x05BA0570, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05DE05BA, 0x55FFAAAA, 0x00000000, 0x00000000,
	0x05BD051B, 0x0000AA55, 0x00000000, 0x00000000,
	0x1376049A, 0x55FFAA00, 0x00000000, 0x00000000,
	0x33154253, 0x00AA5555, 0x00000000, 0x00000000,
	0x6A333A53, 0xFFFFAA00, 0x00000000, 0x00000000,
	0xB1F28212, 0x55FFAA00, 0x00000000, 0x00000000,
	0xE9F2C212, 0x55FFAA00, 0x00000000, 0x00000000,
};
__declspec(section ".data") static void* jumptable_803033E0[] = {
    (char*)mapSetMaterialTev + 0x58,
    (char*)mapSetMaterialTev + 0x90,
    (char*)mapSetMaterialTev + 0x23C,
    (char*)mapSetMaterialTev + 0x594,
    (char*)mapSetMaterialTev + 0x740,
    (char*)mapSetMaterialTev + 0x8EC,
    (char*)mapSetMaterialTev + 0xB24,
    (char*)mapSetMaterialTev + 0xCD0,
    (char*)mapSetMaterialTev + 0xE7C,
    (char*)mapSetMaterialTev + 0xF80,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x12A4,
    (char*)mapSetMaterialTev + 0x3E8,
};
__declspec(section ".data") static void* jumptable_80303414[] = {
    (char*)mapBuildTexture + 0x134,
    (char*)mapBuildTexture + 0x144,
    (char*)mapBuildTexture + 0x154,
    (char*)mapBuildTexture + 0x164,
    (char*)mapBuildTexture + 0xF4,
    (char*)mapBuildTexture + 0x104,
    (char*)mapBuildTexture + 0x114,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x174,
    (char*)mapBuildTexture + 0x184,
    (char*)mapBuildTexture + 0x194,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x1A0,
    (char*)mapBuildTexture + 0x124,
};

#pragma push
#pragma opt_lifetimes off
#ifdef NONMATCHING
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx) {
	static f32 scrl_uv[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	GXTexMapID map;
	GXTexCoordID coord;
	s32 tevStage;
	s32 indStages;
	s32 i;
	Mtx queen_mtx;

	map = (GXTexMapID)texCount;
	coord = (GXTexCoordID)texCount;
	indStages = 0;
	
	if ((s32)texCount > 0) {
		switch (drawMode) {
			case 0:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;

			case 1:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 2:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 12:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 3:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 4:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_TEXC, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 5:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG1);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C1, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_A0, GX_CA_A1, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE4;
				break;

			case 6:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_APREV, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 7:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			case 8:
				GXSetTevColor(GX_TEVREG0, (GXColor) {
					0, (u8)((127.0f * sinf((TWO_PI * (f32)(2 * gp->retraceCount)) / 360.0f)) + 127.0f),
					0, 0}); //TODO: check
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_C0);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_A0);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;

			case 9:
				for (i = 0; i < 4; i++) {
					scrl_uv[i] += queen_uv[i];
					if (scrl_uv[i] > 100.0f) {
						scrl_uv[i] -= 100.0f;
					}
					if (scrl_uv[i] < -100.0f) {
						scrl_uv[i] += 100.0f;
					}
				}

				MTXTrans(queen_mtx, scrl_uv[0], scrl_uv[1], 0.0f);
				GXLoadTexMtxImm(queen_mtx, 0x1E, GX_MTX2x4);
				GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
				MTXTrans(queen_mtx, scrl_uv[2], scrl_uv[3], 0.0f);
				GXLoadTexMtxImm(queen_mtx, 0x21, GX_MTX2x4);
				GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
				GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_ZERO, GX_CA_TEXA, GX_CA_TEXA);
				GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE3;
				break;

			default:
				GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
				GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
				GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
				GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage = GX_TEVSTAGE1;
				break;
		}
	}
	else {
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
		GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
		GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
		GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage = GX_TEVSTAGE1;
	}

	if (!(flags & 0x10000000)) {
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K0);
		GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_K0_A);
		GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_APREV, GX_CA_KONST, GX_CA_ZERO);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage++;
	}

	if ((flags & 4) && shadowGetCharShadowProjection() && shadowGetCharShadowTexObj()) {
		GXColor shColor = shadowGetCharShadowColor();
		Mtx shMtx;
		PSMTXConcat(shadowGetCharShadowProjTexMtx(), mtx, shMtx);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexMtxImm(shMtx, texmtx_tbl[map], GX_MTX3x4);
		GXLoadTexObj(shadowGetCharShadowTexObj(), (GXTexMapID)map);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_KONST, GX_CC_TEXC, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, shColor);
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if (flags & 0x400) {
		Mtx pjMtx;
		GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
		GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
		PSMTXConcat(projMtx, mtx, pjMtx);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexMtxImm(pjMtx, texmtx_tbl[map], GX_MTX3x4);
		GXLoadTexObj(smartTexObj(&projTexObj, projTexImgRef), (GXTexMapID)map);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP3, GX_TEV_SWAP3);
		GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
		GXSetTevColor(GX_TEVREG1, (GXColor){0, 0, 0, 0xFF});
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
		GXSetTevOrder((GXTevStageID)(tevStage + 1), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_C0, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
		GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
		GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
		tevStage += 2;
	}

	if ((flags & 0x10000) && shadowGetDepthShadowTexObj()) {
		GXTexObj* depthTex = shadowGetDepthShadowTexObj();
		MtxPtr depthMtx = shadowGetDepthShadowDepthMtx();
		MtxPtr projTexMtx = shadowGetDepthShadowProjTexMtx();
		GXColor depthColor = shadowGetDepthShadowColor();
		Mtx dsMtx;

		switch ((s32)shadowGetDepthShadowConfig()->format) {
			case 0:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_C0);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage += 3;
				break;

			case 1:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0x00, 0x00, 0x00});
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 2:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0x00, 0x00, 0x00});
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 3:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP2);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_C0);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				tevStage += 3;
				break;

			case 4:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0xFF, 0x00, 0x00});
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;

			case 5:
				GXSetTevColor(GX_TEVREG1, (GXColor){0xFF, 0xFF, 0x00, 0x00});
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				tevStage++;
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 1);
				break;
		}
	}

	if ((flags & 0x20000) && shadowGetProjShadowTexObj()) {
		GXTexObj* projTex = shadowGetProjShadowTexObj();
		MtxPtr projTexMtx = shadowGetProjShadowProjTexMtx();
		GXColor projColor = shadowGetProjShadowColor();
		Mtx psMtx;

		shadowGetProjShadowConfig();
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_KONST, GX_CC_TEXA, GX_CC_ZERO);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_APREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXLoadTexObj(projTex, (GXTexMapID)map);
		PSMTXConcat(projTexMtx, mtx, psMtx);
		GXLoadTexMtxImm(psMtx, texmtx_tbl[map], GX_MTX3x4);
		GXSetTevKColor(GX_KCOLOR1, projColor);
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		GXSetTevKAlphaSel(tevStage, GX_TEV_KASEL_K1_A);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if ((flags & 0x40000) && shadowGetDepthShadowTexObj()) {
		GXTexObj* depthTex = shadowGetDepthShadowTexObj();
		MtxPtr depthMtx = shadowGetDepthShadowDepthMtx();
		MtxPtr projTexMtx = shadowGetDepthShadowProjTexMtx();
		GXColor depthColor = shadowGetDepthShadowColor();
		Mtx dsMtx;

		switch ((s32)shadowGetDepthShadowConfig()->format) {
			case 0:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp8TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_C0, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevKAlphaSel((GXTevStageID)(tevStage + 2), GX_TEV_KASEL_K1_A);
				tevStage += 3;
				break;

			case 3:
				GXSetTevColorOp((GXTevStageID)(tevStage - 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevAlphaOp((GXTevStageID)tevStage - 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
				GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_ALPHA, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
				GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn(tevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
				GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP1);
				GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(shadowGetRamp16TexObj(), (GXTexMapID)map);
				PSMTXConcat(depthMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				GXSetTevOrder((GXTevStageID)(tevStage + 1), (GXTexCoordID)(coord + 1), (GXTexMapID)map, GX_COLOR_NULL);
				GXSetTevColorIn((GXTevStageID)(tevStage + 1), GX_CC_CPREV, GX_CC_TEXC, GX_CC_ONE, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 1), GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 1), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 1), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 1), GX_TEV_SWAP0, GX_TEV_SWAP2);
				GXSetTexCoordGen2((GXTexCoordID)(coord + 1), GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
				GXLoadTexObj(depthTex, (GXTexMapID)map);
				PSMTXConcat(projTexMtx, mtx, dsMtx);
				GXLoadTexMtxImm(dsMtx, texmtx_tbl[map], GX_MTX3x4);
				map = (GXTexMapID)(map + 1);
				coord = (GXTexCoordID)(coord + 2);
				GXSetTevOrder((GXTevStageID)(tevStage + 2), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
				GXSetTevColorIn((GXTevStageID)(tevStage + 2), GX_CC_C0, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
				GXSetTevColorOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevAlphaIn((GXTevStageID)(tevStage + 2), GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
				GXSetTevAlphaOp((GXTevStageID)(tevStage + 2), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
				GXSetTevSwapMode((GXTevStageID)(tevStage + 2), GX_TEV_SWAP0, GX_TEV_SWAP0);
				GXSetTevKColor(GX_KCOLOR1, depthColor);
				GXSetTevKColorSel((GXTevStageID)(tevStage + 2), GX_TEV_KCSEL_K1);
				GXSetTevKAlphaSel((GXTevStageID)(tevStage + 2), GX_TEV_KASEL_K1_A);
				tevStage += 3;
				break;
		}
	}

	if (flags & 0x80100000) {
		s32 r, g, b, a;
		f32 pulse;

		if (flags & 0x100000) {
			r = current_mp->color.r;
			g = current_mp->color.g;
			b = current_mp->color.b;
			a = current_mp->color.a;
		}
		else {
			r = 0xF0;
			g = 0xF0;
			b = 0x64;
			pulse = cos((1.5707964f * gp->retraceCount) / 20.0f);
			a = (u8)(64.0f * (1.0f - pulse) / 2.0f + 64.0f);
		}
		GXSetTevOrder(tevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_ZERO, GX_CC_KONST);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, (GXColor){r * a / 255, g * a / 255, b * a / 255, 0xFF});
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
	}

	if (flags & 0x800000) {
		Vec camPos = {0.0f, 0.0f, 1.0f};
		Vec camUp = {0.0f, 1.0f, 0.0f};
		Vec target = {0.0f, 0.0f, 0.0f};
		GXTexObj waveTex;
		Mtx texMtx;
		Mtx lookMtx;
		s32 level;
		f32 pulse;

		pulse = cos((1.5707964f * gp->retraceCount) / 30.0f);
		level = (127.0f * (1.0f - pulse)) / 2.0f + 128.0f;
		GXInitTexObj(&waveTex, texture_0, 4, 64, GX_TF_CMPR, GX_CLAMP, GX_REPEAT, GX_FALSE);
		GXLoadTexObj(&waveTex, (GXTexMapID)map);
		C_MTXLightOrtho(texMtx, -2.0f, 2.0f, -2.0f, 2.0f, 0.5f, 0.5f, 0.5f, gp->retraceCount / 50.0f);
		C_MTXLookAt(lookMtx, &camPos, &camUp, &target);
		PSMTXConcat(texMtx, lookMtx, texMtx);
		GXLoadTexMtxImm(texMtx, texmtx_tbl[map], GX_MTX3x4);
		GXSetTexCoordGen2((GXTexCoordID)coord, GX_TG_MTX3x4, GX_TG_POS, texmtx_tbl[map], GX_FALSE, GX_PTIDENTITY);
		GXSetTevOrder(tevStage, (GXTexCoordID)coord, (GXTexMapID)map, GX_COLOR_NULL);
		GXSetTevColorOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevAlphaOp(tevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
		GXSetTevColorIn(tevStage, GX_CC_TEXC, GX_CC_CPREV, GX_CC_KONST, GX_CC_ZERO);
		GXSetTevAlphaIn(tevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
		GXSetTevSwapMode(tevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
		GXSetTevKColor(GX_KCOLOR1, (GXColor){level, level, level, 0xFF});
		GXSetTevKColorSel(tevStage, GX_TEV_KCSEL_K1);
		tevStage++;
		map = (GXTexMapID)(map + 1);
		coord = (GXTexCoordID)(coord + 1);
	}

	if (flags & 0xF000000) {
		MapTevCallbackInfo info;
		MapTevCallback callback;
		MapTevCallbackInfo* ip = &info;

		*(MapObject**)info.field_0x0 = current_mp;
		info.mtx = mtx;
		*(s32*)info.field_0x8 = drawMode;
		info.tevStage = tevStage;
		info.texCoord = map;
		info.texMap = coord;
		info.indStage = 0;
		callback = ((MapTevCallback*)((u8*)&mapWork[activeGroup] + offsetof(MapEntry, tevCallbacks)))[(u32)(flags & 0xF000000) >> 24];
		if (callback) {
			callback(ip);
		}
		tevStage = info.tevStage;
		coord = info.texMap;
		indStages = info.indStage;
	}

	GXSetNumTexGens((u8)coord);
	GXSetNumTevStages((u8)tevStage);
	GXSetNumIndStages((u8)indStages);
}
#endif
#pragma pop

#ifdef NONMATCHING
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2) {
	MapWork* wp = mapGetWork();
	GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};

	if (flags & 0x40) {
		color.r = color.r * color1.r / 255;
		color.g = color.g * color1.g / 255;
		color.b = color.b * color1.b / 255;
		color.a = color.a * color1.a / 255;
	}
	if (color2.r != 0xFF) {
		color.a = color.a * color2.r / 255;
	}
	if ((wp->entries[0].flags & 2) && !(flags & 0x800)) {
		color.r = color.r * wp->entries[0].blend.r / 255;
		color.g = color.g * wp->entries[0].blend.g / 255;
		color.b = color.b * wp->entries[0].blend.b / 255;
		color.a = color.a * wp->entries[0].blend.a / 255;
	}
	if ((wp->entries[0].flags & 4) && !(flags & 0x1000)) {
		color.r = color.r * wp->entries[0].blend2.r / 255;
		color.g = color.g * wp->entries[0].blend2.g / 255;
		color.b = color.b * wp->entries[0].blend2.b / 255;
		color.a = color.a * wp->entries[0].blend2.a / 255;
	}
	if ((wp->entries[0].flags & 8) && !(flags & 0x800)) {
		color.r = color.r * wp->entries[0].color.r / 255;
		color.g = color.g * wp->entries[0].color.g / 255;
		color.b = color.b * wp->entries[0].color.b / 255;
		color.a = color.a * wp->entries[0].color.a / 255;
	}
	GXSetTevKColor(GX_KCOLOR0, color);
}
#endif

#ifdef NONMATCHING
void mapSetMaterialFog(void) {
	CameraEntry* camera = camGetCurPtr();
	MapWork* wp = mapGetWork();

	if (wp->entries[0].flags & 1) {
		GXSetFog((GXFogType)fog_type[wp->entries[0].fogType], wp->entries[0].fogStart, wp->entries[0].fogEnd,
				 camera->near, camera->far, wp->entries[0].fogColor);
	}
	else {
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
	}
}
#endif

#ifdef NONMATCHING
static inline void mapSetObjFog(MapObject* obj) {
	CameraEntry* camera = camGetCurPtr();
	MapWork* wp = mapGetWork();

	if ((wp->entries[0].flags & 1) && !(obj->flags & 0x80000)) {
		GXSetFog((GXFogType)fog_type[wp->entries[0].fogType], wp->entries[0].fogStart, wp->entries[0].fogEnd,
				 camera->near, camera->far, wp->entries[0].fogColor);
	}
	else {
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
	}
}
#endif



LightEntry* lightGetAmbient(void);

#ifdef NONMATCHING
void mapSetTextureMatrix(MapMaterial* mat) {
	s32 j;
	s32 k;
	s32 i;
	f32 rot, sx, sy, tx, ty;
	f32 cx, cy;
	Mtx mtx, tmpMtx, transMtx, rotMtx, scaleMtx;

	j = 0;
	k = 0;
	for (i = mat->samplerCount - 1; i >= 0; j++, k++, i--) {
		sx = mat->xforms[i].sx;
		rot = -mat->xforms[i].rot;
		sy = mat->xforms[i].sy;
		ty = -mat->xforms[i].ty;
		tx = mat->xforms[i].tx;
		if (1.0f != mat->xforms[i].sx || 1.0f != mat->xforms[i].sy || 0.0f != tx || 0.0f != ty || 0.0f != rot) {
			if (rot) {
				cx = 0.5f * mat->xforms[i].cx * mat->xforms[i].sx;
				cy = (1.0f - 0.5f * mat->xforms[i].cy) * mat->xforms[i].sy;
				MTXTrans(mtx, cx, cy, 0.0f);
				MTXRotRad(rotMtx, 'z', MTXDegToRad(rot));
				MTXTrans(tmpMtx, -cx, -cy, 0.0f);
				MTXConcat(mtx, rotMtx, rotMtx);
				MTXConcat(rotMtx, tmpMtx, rotMtx);
			}
			if (sx || sy) {
				MTXScale(scaleMtx, sx, sy, 1.0f);
			}
			if (tx || ty) {
				MTXTrans(transMtx, tx, ty, 0.0f);
			}
			if (rot) {
				if (sx || sy) {
					MTXConcat(rotMtx, scaleMtx, mtx);
					if (tx || ty) {
						MTXConcat(mtx, transMtx, mtx);
					}
				}
				else if (tx || ty) {
					MTXConcat(rotMtx, transMtx, mtx);
				}
				else {
					MTXCopy(rotMtx, mtx);
				}
			}
			else if (sx || sy) {
				if (tx || ty) {
					MTXConcat(scaleMtx, transMtx, mtx);
				}
				else {
					MTXCopy(scaleMtx, mtx);
				}
			}
			else if (tx || ty) {
				MTXCopy(transMtx, mtx);
			}
			GXLoadTexMtxImm(mtx, texmtx_tbl[i], GX_MTX2x4);
			GXSetTexCoordGen2((GXTexCoordID)j, GX_TG_MTX2x4, (GXTexGenSrc)(mat->samplerCount + 3 - k), texmtx_tbl[i], GX_FALSE, GX_PTIDENTITY);
		}
		else {
			GXSetTexCoordGen2((GXTexCoordID)j, GX_TG_MTX2x4, (GXTexGenSrc)(mat->samplerCount + 3 - k), GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
		}
	}
}
#endif


#ifdef NONMATCHING
void mapSetMaterial(MapObject* obj, void* material) {
	MapMaterial* mat = material;
	GXColor ambient;
	GXColor ambColor = {0x00, 0x00, 0x00, 0xFF};
	s32 count;
	s32 texIdx;
	u32 lightMask;
	s32 attnFn;
	s32 i;
	LightEntry* light;
	LightEntry** lp;
	MapWork* wp;
	MapMatSampler* sampler;
	MapTexTable* table;
	char* name;
	s32 k;
	TEXDescriptor* desc;
	GXBool mip;
	GXLightObj lightObj;
	Mtx rotX, rotY, rotZ;
	LightEntry* lights[8];
	GXTexObj texObj;
	Vec pos;

	texIdx = 0;
	attnFn = GX_AF_NONE;
	count = mapSetLight(obj, lights);
	lightMask = 0;
	for (i = 0; i < count; i++) {
		Vec dir = {0.0f, 0.0f, -1.0f};

		light = lights[i];
		if (light->flags & LIGHT_POINT) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, lights[i]->attenDistCoef.x, lights[i]->attenDistCoef.y, lights[i]->attenDistCoef.z);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		else if (light->flags & LIGHT_SPOT) {
			MTXRotRad(rotX, 'x', MTXDegToRad(light->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			VECScale(&dir, &dir, -1048576.0f);
			VECAdd(&lights[i]->position, &dir, &pos);
			MTXMultVec(camGetCurPtr()->view, &pos, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_DIRECTIONAL) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			MTXRotRad(rotX, 'x', MTXDegToRad(lights[i]->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			MTXMultVecSR(camGetCurPtr()->view, &dir, &dir);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightDir(&lightObj, dir.x, dir.y, dir.z);
			GXInitLightSpot(&lightObj, lights[i]->spotAngle / 2, GX_SP_SHARP);
			GXInitLightDistAttn(&lightObj, 1000.0f, 0.5f, GX_DA_OFF);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		lightMask |= lightid_tbl[i];
	}

	light = lightGetAmbient();
	if (light) {
		ambient = light->color;
	}
	else {
		ambient = ambColor;
	}
	GXSetNumChans(1);
	GXSetChanAmbColor(GX_COLOR0A0, ambient);
	GXSetChanMatColor(GX_COLOR0A0, mat->color);
	switch (mat->lightMode) {
		case 0:
			GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
			GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
			break;
		case 1:
			GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_VTX, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
			GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
			break;
	}

	for (i = mat->samplerCount - 1; i >= 0; i--) {
		sampler = mat->samplers[i];
		wp = mapGetWork();
		k = mapSearchTexName(MAPENT_FIELD(&wp->entries[obj->groupIndex], MapTexTable*, 0x94), sampler->tex->name);
		desc = TEXGet(wp->entries[obj->groupIndex].tpl, k);
		if (desc->textureHeader->minLOD == desc->textureHeader->maxLOD) {
			mip = GX_FALSE;
		} else {
			mip = GX_TRUE;
		}
		GXInitTexObj(&texObj, desc->textureHeader->data, desc->textureHeader->width, desc->textureHeader->height, (GXTexFmt)desc->textureHeader->format,
					 (GXTexWrapMode)texwrap_tbl[sampler->wrapS], (GXTexWrapMode)texwrap_tbl[sampler->wrapT],
					 mip);
		GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, desc->textureHeader->minLOD, desc->textureHeader->maxLOD, desc->textureHeader->LODBias, GX_FALSE, desc->textureHeader->edgeLODEnable, GX_ANISO_1);
		GXLoadTexObj(&texObj, (GXTexMapID)texIdx);
		texIdx++;
	}
	mapSetMaterialTev(mat->samplerCount, mat->tevMode ? *mat->tevMode : 0, obj->flags, obj->modelWorldMtx);
}
#endif

#ifdef NONMATCHING
void mapSetPaperAmbColor(GXColor* color) {
	paper_ambient = *color;
}
#endif

#ifdef NONMATCHING
void mapResetPaperAmbColor(void) {
	paper_ambient = (GXColor){0x70, 0x70, 0x70, 0xFF};
}
#endif

#ifdef NONMATCHING
static inline void mapResetPaperCraftAmbColor(void) {
	paperCraft_ambient = (GXColor){0x70, 0x70, 0x70, 0xFF};
}
#endif

#ifdef NONMATCHING
void mapSetMaterialLight(s32 flags, Vec position) {
	GXColor matColor = {0xFF, 0xFF, 0xFF, 0xFF};
	GXColor ambColor = {0x00, 0x00, 0x00, 0xFF};
	s32 count;
	u32 lightMask;
	u32 paper;
	s32 attnFn;
	s32 i;
	u32 paperCraft;
	LightEntry* light;
	GXLightObj lightObj;
	Mtx rotX, rotY, rotZ;
	LightEntry* lights[8];
	GXColor ambient;
	Vec pos;

	count = 0;
	attnFn = GX_AF_NONE;
	paper = flags & 1;
	if (paper) {
		lights[0] = lightGetPaper();
		count = 1;
	}
	paperCraft = flags & 8;
	if (paperCraft) {
		lights[count] = lightGetPaperCraft();
		count++;
	}
	if (flags & 0x10) {
		lights[count] = lightGetPaper();
		count++;
	}
	if ((flags & 2) && lightCheckCharaLight() && count < 8) {
		count += lightGetNearObj(&position, &lights[count], 8 - count, LIGHT_CHARA);
	}
	if (flags & 0x19) {
		if (count == 1) {
			if (paper) {
				ambColor = paper_ambient;
			}
			else if (paperCraft) {
				ambColor = paperCraft_ambient;
			}
			else {
				ambColor = (GXColor){0x00, 0x00, 0x00, 0xFF};
			}
		}
		else {
			count = lightGetNearObj(&position, lights, 8, LIGHT_CHARA);
		}
	}

	lightMask = 0;
	for (i = 0; i < count; i++) {
		Vec dir = {0.0f, 0.0f, -1.0f};

		light = lights[i];
		if (light->flags & LIGHT_POINT) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			if (lights[i]->flags & LIGHT_NO_DIST_ATTEN) {
				GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			}
			else {
				GXInitLightAttn(&lightObj, lights[i]->attenAngle, 0.0f, 0.0f, lights[i]->attenDistCoef.x, lights[i]->attenDistCoef.y, lights[i]->attenDistCoef.z);
				attnFn = GX_AF_SPOT;
			}
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_SPOT) {
			MTXRotRad(rotX, 'x', MTXDegToRad(light->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			VECScale(&dir, &dir, -1048576.0f);
			VECAdd(&lights[i]->position, &dir, &pos);
			MTXMultVec(camGetCurPtr()->view, &pos, &pos);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
		}
		else if (light->flags & LIGHT_DIRECTIONAL) {
			MTXMultVec(camGetCurPtr()->view, &light->position, &pos);
			MTXRotRad(rotX, 'x', MTXDegToRad(lights[i]->rotation.x));
			MTXRotRad(rotY, 'y', MTXDegToRad(lights[i]->rotation.y));
			MTXRotRad(rotZ, 'z', MTXDegToRad(lights[i]->rotation.z));
			MTXConcat(rotZ, rotY, rotY);
			MTXConcat(rotY, rotX, rotX);
			MTXMultVec(rotX, &dir, &dir);
			MTXMultVecSR(camGetCurPtr()->view, &dir, &dir);
			GXInitLightPos(&lightObj, pos.x, pos.y, pos.z);
			GXInitLightDir(&lightObj, dir.x, dir.y, dir.z);
			{
				f32 ang = lights[i]->spotAngle;
				ang *= 0.5f;
				GXInitLightSpot(&lightObj, ang, GX_SP_SHARP);
			}
			GXInitLightDistAttn(&lightObj, 1000.0f, 0.5f, GX_DA_OFF);
			GXInitLightColor(&lightObj, lights[i]->color);
			GXLoadLightObjImm(&lightObj, lightid_tbl[i]);
			attnFn = GX_AF_SPOT;
		}
		lightMask |= lightid_tbl[i];
	}

	light = lightGetCharaAmbient();
	if (light) {
		ambient = light->color;
	}
	else {
		ambient = ambColor;
	}
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, matColor);
	GXSetNumChans(1);
	GXSetChanAmbColor(GX_COLOR0A0, ambient);
	if (flags & 4) {
		GXSetChanMatColor(GX_COLOR0A0, matColor);
		GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_REG, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
		GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	}
	else {
		GXSetChanCtrl(GX_COLOR0, count > 0, GX_SRC_REG, GX_SRC_VTX, lightMask, GX_DF_CLAMP, (GXAttnFn)attnFn);
		GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	}
}
#endif

typedef struct MapVcdTable {
	void* positions;          // 0x0
	void* normals;            // 0x4
	u8 field_0x8[0xC - 0x8];  // 0x8
	void* colors[2];          // 0xC
	s32 texCount;             // 0x14
	void* texCoords[8];       // 0x18
} MapVcdTable;

typedef struct MapVtxFmtInfo {
	u8 field_0x0[0x44 - 0x0]; // 0x0
	s32 posFrac;              // 0x44
	s32 texFrac[8];           // 0x48
} MapVtxFmtInfo;

#define MAP_VTXFMT(entry) ((MapVtxFmtInfo*)(entry)->vcdTable)

typedef struct MapVtxRec {
	s16 pos;     // 0x0
	s16 nrm;     // 0x2
	s16 clr;     // 0x4
	s16 unk6;    // 0x6
	s16 tex[8];  // 0x8
} MapVtxRec;

typedef struct MapRawDL {
	s32 count;        // 0x0

	MapVtxRec vtx[];  // 0x4
} MapRawDL;
#ifdef NONMATCHING
const GXVtxAttrFmtList attr_fmt[12] = {
	{GX_VA_POS, GX_POS_XYZ, GX_F32, 0},
	{GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0},
	{GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0},
	{GX_VA_TEX0, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX1, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX2, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX3, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX4, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX5, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX6, GX_TEX_ST, GX_F32, 0},
	{GX_VA_TEX7, GX_TEX_ST, GX_F32, 0},
	{GX_VA_NULL, GX_POS_XY, GX_U8, 0},
};
#endif


#ifdef NONMATCHING
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh) {
	MapWork* wp;
	void* pos;
	void* nrm;
	s32 texCount;
	MapVcdTable* vcd;

	int i;
	int j;
	int k;
	MapRawDL* dl;
	MapVtxRec* v;

	wp = mapGetWork();
	vcd = (MapVcdTable*)mesh->vcdTableOffset;
	pos = (u8*)vcd->positions + 4;
	nrm = (u8*)vcd->normals + 4;
	texCount = vcd->texCount;

	GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
	if (!(wp->entries[obj->groupIndex].flags & 0x8000)) {
		GXClearVtxDesc();
		GXSetVtxAttrFmtv(GX_VTXFMT0, attr_fmt);
		GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
		GXSetArray(GX_VA_POS, pos, 12);
		GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
		GXSetArray(GX_VA_NRM, nrm, 12);
		GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
		GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[0] + 4, 4);
		for (i = 0; i < texCount; i++) {
			GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
			GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 8);
		}
		for (i = 0; i < mesh->displayListCount; i++) {
			dl = (MapRawDL*)mesh->displayLists.normalLists[i];
			GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (u16)dl->count);
			for (j = 0; j < dl->count; j++) {
				v = &dl->vtx[j];
				GXPosition1x16(v->pos);
				GXNormal1x16(v->nrm);
				GXColor1x16(v->clr);
				for (k = 0; k < texCount; k++) {

					GXTexCoord1x16(v->tex[k] != -1 ? (u16)v->tex[k] : 0);
				}
			}
		}
	}
	else {
		u32 mask = mesh->elementMask;
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)((MapVtxFmtInfo*)wp->entries[obj->groupIndex].vcdTable)->posFrac);
		GXSetArray(GX_VA_POS, pos, 6);
		GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
		GXSetArray(GX_VA_NRM, nrm, 3);
		for (i = 0; i < 2; i++) {
			if (!(mask & (1 << (i + 2)))) {
				break;
			}
			GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
			GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[i] + 4, 4);
		}
		for (i = 0; i < 8; i++) {
			if (!(mask & (1 << (i + 4)))) {

				break;
			}
			GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
			GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->texFrac[i]);
			GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 4);
		}
		for (i = 0; i < mesh->displayListCount; i++) {
			GXCallDisplayList((void*)mesh->displayLists.packedLists[i].offset, *(u32*)&mesh->displayLists.packedLists[i].vertexCount);
		}
	}
}
#endif

#ifdef NONMATCHING
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh) {

	MapWork* wp;
	u32 mask;
	MapVcdTable* vcd;
	void* pos;
	void* nrm;
	int i;

	wp = mapGetWork();

	vcd = (MapVcdTable*)mesh->vcdTableOffset;
	mask = mesh->elementMask;
	pos = (u8*)vcd->positions + 4;
	nrm = (u8*)vcd->normals + 4;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)((MapVtxFmtInfo*)wp->entries[obj->groupIndex].vcdTable)->posFrac);
	GXSetArray(GX_VA_POS, pos, 6);
	GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_S8, 6);
	GXSetArray(GX_VA_NRM, nrm, 3);
	for (i = 0; i < 2; i++) {
		if (!(mask & (1 << (i + 2)))) {
			break;
		}
		GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GXSetArray(GX_VA_CLR0, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->colors[i] + 4, 4);
	}
	for (i = 0; i < 8; i++) {
		if (!(mask & (1 << (i + 4)))) {
			break;
		}
		GXSetVtxDesc(GX_VA_TEX0 + i, GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->texFrac[i]);
		GXSetArray(GX_VA_TEX0 + i, (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 4);
	}
}
#endif

#ifdef NONMATCHING
MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name) {
	MapFileJoint* found;

	if (!strcmp(joint->name, name)) {
		return joint;
	}
	if (joint->child) {
		found = mapSearchDmdJointSub(joint->child, name);
		if (found) {
			return found;
		}
	}
	if (joint->next) {
		found = mapSearchDmdJointSub(joint->next, name);
		if (found) {
			return found;
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix) {
	MapFileJoint* found;
	char path[256];

	strcpy(path, prefix);
	strcat(path, joint->name);
	if (!strcmp(path, name)) {
		return joint;
	}
	if (joint->child) {
		strcat(path, "|");
		found = mapSearchDmdJointSub2(joint->child, name, path);
		if (found) {
			return found;
		}
	}
	if (joint->next) {
		found = mapSearchDmdJointSub2(joint->next, name, prefix);
		if (1) {
			if (found) {
				return found;
			}
		}
	}
	return NULL;
}
#endif

#ifdef NONMATCHING
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name) {
	if ((s32)name[0] != '|') {
		return mapSearchDmdJointSub(joint, name);
	}
	return mapSearchDmdJointSub2(joint, name, "|");
}
#endif

#ifdef NONMATCHING
MapObject* mapGetMapObj(const char *name) { // 1:1
    MapWork *wp;
    MapEntry* entry;
    int j;
    int i;
    MapObject *object;

    wp = mapGetWork();
    if (!name) {
        return 0;
    }
    for (i = 0; i < wp->entries[0].count; i++) {
        entry = &wp->entries[i];
        object = entry->objects;
        for (j = 0; j < entry->numJoints; j++, object++) {
            if (!strcmp(object->joints->name, name)) {
                return object;
            }
        }
    }
    return 0;
}
#endif

#ifdef NONMATCHING
void mapObjFlagOn(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	if (!(flags & 0x100) || obj->unk114) {
		obj->flags |= flags;
	}
}
#endif

#ifdef NONMATCHING
void mapObjFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	obj->flags &= ~flags;
}
#endif

#ifdef NONMATCHING
void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext) {
	if (!(flags & 0x100) || obj->unk114) {
		obj->flags |= flags;
	}
	if (obj->child) {
		mapFlgOn(obj->child, flags, TRUE);
	}
	if (doNext && obj->next) {
		mapFlgOn(obj->next, flags, TRUE);
	}
}
#endif

#ifdef NONMATCHING
void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext) {
	obj->flags &= ~flags;
	if (obj->child) {
		mapFlgOff(obj->child, flags, TRUE);
	}
	if (doNext && obj->next) {
		mapFlgOff(obj->next, flags, TRUE);
	}
}
#endif

#ifdef NONMATCHING
void mapGrpFlagOn(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	mapFlgOn(obj, flags, FALSE);
}
#endif

#ifdef NONMATCHING
void mapGrpFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	mapFlgOff(obj, flags, FALSE);
}
#endif

#ifdef NONMATCHING
void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext) {
	obj->offscreenId = id;
	if (id != -1) {
		obj->flags |= 0x80;
	}
	else {
		obj->flags &= ~0x80;
	}
	if (obj->child) {
		_setOffScrnId(obj->child, id, TRUE);
	}
	if (doNext && obj->next) {
		_setOffScrnId(obj->next, id, TRUE);
	}
}
#endif

#ifdef NONMATCHING
void mapObjSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj;
	MapObject* object;
	int i;
	int j;
	MapWork* wp;
	MapEntry* entry;

	wp = &mapWork[activeGroup];
	if (!name) {
		obj = NULL;
		goto done;
	}
	entry = &wp->entries[0];
	for (i = 0; i < wp->entries[0].count; entry++, i++) {
		object = entry->objects;
		for (j = 0; j < entry->numJoints; j++, object++) {
			if (!strcmp(object->joints->name, name)) {
				obj = object;
				goto done;
			}
		}
	}
	obj = NULL;
done:

	obj->offscreenId = offscreenNameToId(offscreen);
	obj->flags |= 0x80;
}
#endif

#ifdef NONMATCHING
void mapGrpSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj = mapGetMapObj(name);
	s32 id = offscreenNameToId(offscreen);

	_setOffScrnId(obj, id, FALSE);
}
#endif

#ifdef NONMATCHING
void mapObjClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	obj->offscreenId = -1;
	obj->flags &= ~0x80;
}
#endif

#ifdef NONMATCHING
void mapGrpClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	_setOffScrnId(obj, -1, FALSE);
}
#endif


#ifdef NONMATCHING
void mapObjRotate(const char* name, f32 x, f32 y, f32 z) {
	MapObject* obj = mapGetMapObj(name);
	Mtx rotX, rotY, rotZ;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
		MTXRotRad(rotX, 'x', MTXDegToRad(x));
		MTXRotRad(rotY, 'y', MTXDegToRad(y));
		MTXRotRad(rotZ, 'z', MTXDegToRad(z));
		if (1) {
			MTXConcat(obj->unkAC, rotZ, obj->unkAC);
			MTXConcat(obj->unkAC, rotY, obj->unkAC);
			MTXConcat(obj->unkAC, rotX, obj->unkAC);
		}
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}
#endif

#ifdef NONMATCHING
void mapObjTranslate(const char* name, f32 x, f32 y, f32 z) {
	MapObject* obj = mapGetMapObj(name);
	Mtx trans;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
		MTXTrans(trans, x / 10.0f, y / 10.0f, z / 10.0f);
		MTXConcat(obj->unkAC, trans, obj->unkAC);
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}
#endif

#ifdef NONMATCHING
void mapObjScale(const char* name, f32 x, f32 y, f32 z) {
	MapObject* obj = mapGetMapObj(name);
	Mtx scale;

	if (obj) {
		if (!(obj->flags & 0x200)) {
			MTXIdentity(obj->unkAC);
		}
		MTXScale(scale, x, y, z);
		MTXConcat(obj->unkAC, scale, obj->unkAC);
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}
#endif

#ifdef NONMATCHING
void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext) {
	Vec pos;

	if (obj->child) {
		mapObjGetPosSub(obj->child, sum, count, TRUE);
	}
	else {
		MTXMultVec(obj->modelWorldMtx, &obj->center, &pos);
		VECAdd(sum, &pos, sum);
		(*count)++;
	}
	if (doNext && obj->next) {
		mapObjGetPosSub(obj->next, sum, count, TRUE);
	}
}
#endif

#ifdef NONMATCHING
void mapObjGetPos(const char* name, Vec* pos) {
	s32 count = 0;
	Vec sum = {0.0f, 0.0f, 0.0f};
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		*pos = (Vec){0.0f, 0.0f, 0.0f};
		return;
	}
	mapObjGetPosSub(obj, &sum, &count, FALSE);
	VECScale(&sum, pos, 1.0f / count);
}
#endif

#ifdef NONMATCHING
void mapSetFog(s32 type, f32 start, f32 end, GXColor color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].fogType = type;
	wp->entries[0].fogStart = start;
	wp->entries[0].fogEnd = end;
	wp->entries[0].fogColor = color;
}
#endif

#ifdef NONMATCHING
void mapGetFog(s32* type, f32* start, f32* end, GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	*type = wp->entries[0].fogType;
	*start = wp->entries[0].fogStart;
	*end = wp->entries[0].fogEnd;
	*color = wp->entries[0].fogColor;
}
#endif

#ifdef NONMATCHING
void mapFogOn(void) {
	mapGetWork()->entries[0].flags |= 1;
}
#endif

#ifdef NONMATCHING
void mapFogOff(void) {
	mapGetWork()->entries[0].flags &= ~1;
}
#endif

#ifdef NONMATCHING
void mapSetBlend(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend = *color;
	wp->entries[0].flags |= 2;
}
#endif

#ifdef NONMATCHING
void mapSetBlend2(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend2 = *color;
	wp->entries[0].flags |= 4;
}
#endif

#ifdef NONMATCHING
void mapGetBlend(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 2) {
		*color = wp->entries[0].blend;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}
#endif

#ifdef NONMATCHING
void mapGetBlend2(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 4) {
		*color = wp->entries[0].blend2;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}
#endif

#ifdef NONMATCHING
void mapBlendOff(void) {
	mapGetWork()->entries[0].flags &= ~2;
}
#endif

#ifdef NONMATCHING
void mapBlendOff2(void) {
	mapGetWork()->entries[0].flags &= ~4;
}
#endif

#ifdef NONMATCHING
void mapObjSetColor(const char* name, GXColor* color) {
	MapObject* obj = mapGetMapObj(name);

	if (obj) {
		obj->color = *color;
		obj->flags |= 0x40;
	}
}
#endif

#ifdef NONMATCHING
void setColor(MapObject* obj, GXColor color, BOOL doNext) {
	if (obj) {
		obj->color = color;
		obj->flags |= 0x40;
		if (obj->child) {
			setColor(obj->child, color, TRUE);
		}
		if (doNext && obj->next) {
			setColor(obj->next, color, TRUE);
		}
	}
}
#endif

#ifdef NONMATCHING
void mapGrpSetColor(const char* name, GXColor color) {
	setColor(mapGetMapObj(name), color, FALSE);
}
#endif

#ifdef NONMATCHING
void mapSetProjTexObj(GXTexObj* obj, void* imgRef) {
	projTexObj = *obj;
	projTexImgRef = imgRef;
}
#endif

#ifdef NONMATCHING
void mapSetProjMtx(Mtx mtx) {
	MTXCopy(mtx, projMtx);
}
#endif

extern int __float_nan[];
#ifdef NONMATCHING
static inline s32 sp_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
#endif
#ifdef NONMATCHING
static inline f32 sp_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (sp_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif

#ifdef NONMATCHING
void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out) {
	f32* h;
	Vec* w;
	s32 i;
	f32 dx, dy, dz;
	f32 ax, ay, az;

	h = _mapAlloc(n * sizeof(f32));
	w = _mapAlloc(n * sizeof(Vec));
	t[0] = 0.0f;
	for (i = 1; i < n; i++) {
		dx = pts[i].x - pts[i - 1].x;
		dy = pts[i].y - pts[i - 1].y;
		dz = pts[i].z - pts[i - 1].z;
		t[i] = t[i - 1] + sp_sqrtf(dx * dx + dy * dy + dz * dz);
	}
	for (i = 1; i < n; i++) {
		t[i] /= t[n - 1];
	}
	out[0].x = 0.0f;
	out[0].y = 0.0f;
	out[0].z = 0.0f;
	out[n - 1].x = 0.0f;
	out[n - 1].y = 0.0f;
	out[n - 1].z = 0.0f;
	for (i = 0; i < n - 1; i++) {
		h[i] = t[i + 1] - t[i];
		if (h[i] == 0.0f) {
			h[i] = 0.0001f;
		}
		w[i + 1].x = (pts[i + 1].x - pts[i].x) / h[i];
		w[i + 1].y = (pts[i + 1].y - pts[i].y) / h[i];
		w[i + 1].z = (pts[i + 1].z - pts[i].z) / h[i];
	}
	out[1].x = w[2].x - w[1].x;
	out[1].y = w[2].y - w[1].y;
	out[1].z = w[2].z - w[1].z;
	w[1].x = 2.0f * (t[2] - t[0]);
	w[1].y = 2.0f * (t[2] - t[0]);
	w[1].z = 2.0f * (t[2] - t[0]);
	for (i = 1; i < n - 2; i++) {
		ax = h[i] / w[i].x;
		ay = h[i] / w[i].y;
		az = h[i] / w[i].z;
		out[i + 1].x = (w[i + 2].x - w[i + 1].x) - ax * out[i].x;
		out[i + 1].y = (w[i + 2].y - w[i + 1].y) - ay * out[i].y;
		out[i + 1].z = (w[i + 2].z - w[i + 1].z) - az * out[i].z;
		w[i + 1].x = 2.0f * (t[i + 2] - t[i]) - ax * h[i];
		w[i + 1].y = 2.0f * (t[i + 2] - t[i]) - ay * h[i];
		w[i + 1].z = 2.0f * (t[i + 2] - t[i]) - az * h[i];
	}
	out[n - 2].x -= h[n - 2] * out[n - 1].x;
	out[n - 2].y -= h[n - 2] * out[n - 1].y;
	out[n - 2].z -= h[n - 2] * out[n - 1].z;
	for (i = n - 2; i > 0; i--) {
		out[i].x = (out[i].x - h[i] * out[i + 1].x) / w[i].x;
		out[i].y = (out[i].y - h[i] * out[i + 1].y) / w[i].y;
		out[i].z = (out[i].z - h[i] * out[i + 1].z) / w[i].z;
	}
	_mapFree(w);
	_mapFree(h);
}
#endif

#ifdef NONMATCHING
void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl) {
	s32 lo;
	s32 hi;
	s32 mid;
	f32 new_var;
	f32 u;
	f32 h;

	if (n == 2) {
		out->x = t * (pts[1].x - pts[0].x) + pts[0].x;
		new_var = pts[0].y;
		out->y = t * (pts[1].y - new_var) + new_var;
		out->z = t * (pts[1].z - pts[0].z) + pts[0].z;
		return;
	}
	hi = n - 1;
	lo = 0;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		if (ts[mid] < t) {
			lo = mid + 1;
		}
		else {
			hi = mid;
		}
	}
	if (lo > 0) {
		lo--;
	}
	u = t - ts[lo];
	h = ts[lo + 1] - ts[lo];
	out->x = pts[lo].x + u * ((pts[lo + 1].x - pts[lo].x) / h - h * (2.0f * tbl[lo].x + tbl[lo + 1].x) + u * (3.0f * tbl[lo].x + u * (tbl[lo + 1].x - tbl[lo].x) / h));
	out->y = pts[lo].y + u * ((pts[lo + 1].y - pts[lo].y) / h - h * (2.0f * tbl[lo].y + tbl[lo + 1].y) + u * (3.0f * tbl[lo].y + u * (tbl[lo + 1].y - tbl[lo].y) / h));
	out->z = pts[lo].z + u * ((pts[lo + 1].z - pts[lo].z) / h - h * (2.0f * tbl[lo].z + tbl[lo + 1].z) + u * (3.0f * tbl[lo].z + u * (tbl[lo + 1].z - tbl[lo].z) / h));
}
#endif

#ifdef NONMATCHING
BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor) {
	if ((flags & 0x40) && color->a != 0xFF) {
		return TRUE;
	}
	if (matColor->a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x800) && (mapGetWork()->entries[0].flags & 2) && mapGetWork()->entries[0].blend.a != 0xFF) {
		return TRUE;
	}
	if (!(flags & 0x1000) && (mapGetWork()->entries[0].flags & 4) && mapGetWork()->entries[0].blend2.a != 0xFF) {
		return TRUE;
	}
	return FALSE;
}
#endif

#ifdef NONMATCHING
void mapSetTevCallback(s32 index, MapTevCallback callback) {
	mapGetWork()->entries[0].tevCallbacks[index] = callback;
}
#endif

#ifdef NONMATCHING
void mapObjFlushOn(const char* name) {
	mapObjFlagOn(name, 0x100000);
}
#endif

#ifdef NONMATCHING
void mapObjFlushOff(const char* name) {
	mapObjFlagOff(name, 0x100000);
}
#endif

#ifdef NONMATCHING
void mapGrpFlushOn(const char* name) {
	mapGrpFlagOn(name, 0x100000);
}
#endif

#ifdef NONMATCHING
void mapGrpFlushOff(const char* name) {
	mapGrpFlagOff(name, 0x100000);
}
#endif

#ifdef NONMATCHING
void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	GXColor color = {0};

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	mapObjSetColor(name, &color);
	mapObjFlagOff(name, 0x40);
}
#endif

#ifdef NONMATCHING
void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	mapGrpSetColor(name, (GXColor){r, g, b, a});
	mapGrpFlagOff(name, 0x40);
}
#endif

#ifdef NONMATCHING
void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		error_data[error_count].field_0x20 = 0;
		strncpy(error_data[error_count].field_0x0, name, sizeof(error_data[0].field_0x0) - 1);
		error_flag = TRUE;
		error_count++;
		error_count %= 32;
		return;
	}
	*r = obj->color.r;
	*g = obj->color.g;
	*b = obj->color.b;
	*a = obj->color.a;
}
#endif

// Stand-in for a function the original linker dead-stripped; it only keeps the
// constants that function left behind in .rodata/.sdata2 in their original order.
#ifdef NONMATCHING
void mapStrippedPool(const char** str, f32* val) {
	str[0] = ".";
	val[0] = 3.0f;
	val[1] = 0.0f;
	val[2] = 0.5f;
	val[3] = 2.0f;
	str[1] = "%s/m/%s/d";
	str[2] = "information";
	str[3] = "ver1.01";
	str[4] = "ver1.02";
	str[5] = "--/--/-- --:--:--";
	str[6] = "\x83\x52\x83\x93\x83\x6F\x81\x5B\x83\x67\x82\xB3\x82\xEA\x82\xC4\x82\xA2\x82\xDC\x82\xB9\x82\xF1";
	str[7] = "animation_table";
	str[8] = "curve_table";
}
#endif

#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".sdata") u32 gap_07_8040F3F4_sdata[3] = {0};
#pragma explicit_zero_data reset
#pragma force_active reset


#ifndef NONMATCHING
#undef lightGetNearObj
// FAKE (asm stopgap, asmfake.py --whole): mapErrorEntry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".sdata2") const u32 dat_80419800 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419804 = 0xFF000000;
__declspec(section ".sdata2") const u32 dat_80419808 = 0xFF000000;
__declspec(section ".sdata2") const u32 dat_8041980c = 0xFFFF0000;
__declspec(section ".sdata2") const u32 dat_80419810 = 0xFFFF0000;
__declspec(section ".sdata2") const u32 dat_80419814 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419818 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041981c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419820 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419824 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419828 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041982c = 0x707070FF;
__declspec(section ".sdata2") const u32 dat_80419830 = 0x707070FF;
__declspec(section ".sdata2") const u32 dat_80419834 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419838 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041983c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_80419840 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419844 = 0xFFFFFFFF;
__declspec(section ".sdata2") const char str_80419848[4] = ".\0\0";
__declspec(section ".sdata2") const f32 float_3_8041984c = 3.0f;
__declspec(section ".sdata2") const f32 float_0_80419850 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p5_80419854 = 0.5f;
__declspec(section ".sdata2") const f32 float_2_80419858 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p0001_8041985c = 0.0001f;
__declspec(section ".sdata2") const f32 float_1_80419860 = 1.0f;
__declspec(section ".sdata2") const f32 float_10_80419864 = 10.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419868 = 0.017453292f;
__declspec(section ".sdata2") const char str_8041986C[4] = "|\0\0";
__declspec(section ".sdata2") const f32 float_neg1p0486E06_80419870 = -1048576.0f;
__declspec(section ".sdata2") const f32 float_1000_80419874 = 1000.0f;
__declspec(section ".sdata2") const f32 float_6p2832_80419878 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041987c = 360.0f;
__declspec(section ".sdata2") const f32 float_127_80419880 = 127.0f;
__declspec(section ".sdata2") const f32 float_100_80419884 = 100.0f;
__declspec(section ".sdata2") const f32 float_neg100_80419888 = -100.0f;
__declspec(section ".sdata2") const f32 float_1p5708_8041988c = 1.5707964f;
__declspec(section ".sdata2") const f32 float_20_80419890 = 20.0f;
__declspec(section ".sdata2") const f32 float_64_80419894 = 64.0f;
__declspec(section ".sdata2") const f32 float_30_80419898 = 30.0f;
__declspec(section ".sdata2") const f32 float_128_8041989c = 128.0f;
__declspec(section ".sdata2") const f32 float_neg2_804198a0 = -2.0f;
__declspec(section ".sdata2") const f32 float_50_804198a4 = 50.0f;
__declspec(section ".sdata2") const f32 float_neg1_804198a8 = -1.0f;
__declspec(section ".sdata2") const f32 float_5000_804198ac = 5000.0f;
__declspec(section ".sdata2") const f32 float_10000_804198b0 = 10000.0f;
__declspec(section ".sdata2") const f32 float_0p01_804198b4 = 0.01f;
__declspec(section ".sdata2") const f32 float_1Eneg08_804198b8 = 0.00000001f;
__declspec(section ".sdata2") const char str_804198BC[4] = "_v\0";
__declspec(section ".sdata2") const char str_804198C0[8] = "_v_x\0\0\0";
__declspec(section ".sdata2") const f32 float_255_804198c8 = 255.0f;
__declspec(section ".sdata2") const f32 float_0_804198cc = 0.0f;
__declspec(section ".sdata2") const char str_804198D0[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const f32 float_20000_804198d8 = 20000.0f;
__declspec(section ".sdata2") const u32 gap_09_804198DC_sdata2 = 0x00000000;
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c16d8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c16e4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 g5_culling_s678[4] = { 0x00000001, 0x00000002, 0x00000003, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802c1700[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c170c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1718[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1724[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1730[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c173c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1748[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1754[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const GXCullMode culling[4] = { (GXCullMode)0x00000001, (GXCullMode)0x00000002, (GXCullMode)0x00000003, (GXCullMode)0x00000000 };
__declspec(section ".rodata") const u32 texmtx_tbl[10] = { 0x0000001E, 0x00000021, 0x00000024, 0x00000027, 0x0000002A, 0x0000002D, 0x00000030, 0x00000033, 0x00000036, 0x00000039 };
__declspec(section ".rodata") const u32 texfmt_tbl[11] = { 0x00000004, 0x00000005, 0x00000006, 0x0000000E, 0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000008, 0x00000009, 0x0000000A };
__declspec(section ".rodata") const u32 texwrap_tbl[3] = { 0x00000000, 0x00000001, 0x00000002 };
__declspec(section ".rodata") const u32 palfmt_tbl[2] = { 0x00000001, 0x00000002 };
__declspec(section ".rodata") const u32 lightid_tbl[8] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080 };
__declspec(section ".rodata") const f32 vec3_802c17f8[3] = { 0.0f, 0.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802c1804[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1810[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c181c[3] = { 0.0f, 0.0f, -1.0f };
__declspec(section ".rodata") const f32 vec3_802c1828[3] = { 0.0f, 0.0f, -1.0f };
__declspec(section ".rodata") const u32 attr_fmt[48] = { 0x00000009, 0x00000001, 0x00000004, 0x00000000, 0x0000000A, 0x00000000, 0x00000004, 0x00000000, 0x0000000B, 0x00000001, 0x00000005, 0x00000000, 0x0000000D, 0x00000001, 0x00000004, 0x00000000, 0x0000000E, 0x00000001, 0x00000004, 0x00000000, 0x0000000F, 0x00000001, 0x00000004, 0x00000000, 0x00000010, 0x00000001, 0x00000004, 0x00000000, 0x00000011, 0x00000001, 0x00000004, 0x00000000, 0x00000012, 0x00000001, 0x00000004, 0x00000000, 0x00000013, 0x00000001, 0x00000004, 0x00000000, 0x00000014, 0x00000001, 0x00000004, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802c18f4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1900[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_802C190C[] = "%s/m/%s/d\000\000";
__declspec(section ".rodata") const char str_802C1918[] = "information";
__declspec(section ".rodata") const char str_802C1924[] = "ver1.01";
__declspec(section ".rodata") const char str_802C192C[] = "ver1.02";
__declspec(section ".rodata") const char str_802C1934[] = "--/--/-- --:--:--\000\000";
__declspec(section ".rodata") const char str_802C1948[] = "\203R\203\223\203o\201[\203g\202\263\202\352\202\304\202\242\202\334\202\271\202\361\000\000\000";
__declspec(section ".rodata") const char str_802C1964[] = "animation_table";
__declspec(section ".rodata") const char str_802C1974[] = "curve_table";
__declspec(section ".rodata") const f64 double_0p5_802c1980 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c1988 = 3;
__declspec(section ".rodata") const f64 double_0_802c1990 = 0;
__declspec(section ".rodata") const f64 double_to_int_802c1998 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_802c19a0 = 4503599627370496;
__declspec(section ".rodata") const char str_802C19A8[] = "./m/%s/d\000\000\000";
__declspec(section ".rodata") const char str_802C19B4[] = "./m/%s/t\000\000\000";
__declspec(section ".rodata") const char str_802C19C0[] = "texture_table\000\000";
__declspec(section ".rodata") const char str_802C19D0[] = "light_table";
__declspec(section ".rodata") const char str_802C19DC[] = "fog_table\000\000";
__declspec(section ".rodata") const char str_802C19E8[] = "material_name_table";
__declspec(section ".rodata") const char str_802C19FC[] = "vcd_table\000\000";
__declspec(section ".rodata") const char str_802C1A08[] = "ambientLight\000\000\000";
__declspec(section ".rodata") const char str_802C1A18[] = "pointLight\000";
__declspec(section ".rodata") const char str_802C1A24[] = "directionalLight\000\000\000";
__declspec(section ".rodata") const char str_802C1A38[] = "spotLight\000\000";
__declspec(section ".rodata") const char str_802C1A44[] = "./m/%s/c\000\000\000";
__declspec(section ".rodata") const char str_802C1A50[] = "mapdrv.c\000\000\000";
__declspec(section ".rodata") const char str_802C1A5C[] = "\203W\203\207\203C\203\223\203g\202\314\203f\201[\203^\202\314\216w\222\350\202\311\202\250\202\251\202\265\202\310\202\340\202\314\202\252\202\240\202\351\n\000\000";
__declspec(section ".rodata") const u32 gap_04_802C1A8C_rodata[1] = { 0x00000000 };
#pragma force_active reset
void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a);
void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);
void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a);
void mapGrpFlushOff(const char* name);
void mapGrpFlushOn(const char* name);
void mapObjFlushOff(const char* name);
void mapObjFlushOn(const char* name);
void mapSetTevCallback(s32 index, MapTevCallback callback);
BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);
void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl);
void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out);
void mapSetProjMtx(Mtx mtx);
void mapSetProjTexObj(GXTexObj* obj, void* imgRef);
void mapGrpSetColor(const char* name, GXColor color);
void setColor(MapObject* obj, GXColor color, BOOL doNext);
void mapObjSetColor(const char* name, GXColor* color);
void mapBlendOff2(void);
void mapBlendOff(void);
void mapGetBlend2(GXColor* color);
void mapGetBlend(GXColor* color);
void mapSetBlend2(GXColor* color);
void mapSetBlend(GXColor* color);
void mapFogOff(void);
void mapFogOn(void);
void mapGetFog(s32* type, f32* start, f32* end, GXColor* color);
void mapSetFog(s32 type, f32 start, f32 end, GXColor color);
void mapObjGetPos(const char* name, Vec* pos);
void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext);
void mapObjScale(const char* name, f32 x, f32 y, f32 z);
void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
void mapGrpClearOffScreen(const char* name);
void mapObjClearOffScreen(const char* name);
void mapGrpSetOffScreen(const char* name, const char* offscreen);
void mapObjSetOffScreen(const char* name, const char* offscreen);
void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext);
void mapGrpFlagOff(const char* name, u32 flags);
void mapGrpFlagOn(const char* name, u32 flags);
void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext);
void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext);
void mapObjFlagOff(const char* name, u32 flags);
void mapObjFlagOn(const char* name, u32 flags);
MapObject* mapGetMapObj(const char *name);
MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name);
MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix);
MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
void mapSetMaterialLight(s32 flags, Vec position);
void mapResetPaperAmbColor(void);
void mapSetPaperAmbColor(GXColor* color);
void mapSetMaterial(MapObject* obj, void* material);
void mapSetTextureMatrix(MapMaterial* mat);
void mapSetMaterialFog(void);
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);
s32 mapSetLight(MapObject* obj, LightEntry** lights);
void mapDisp(void);
void mapDispMapGrp_bbox(CameraId cam, MapObject* obj);
void mapDispMapObj_bbox(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj);
void test_kururing_mapdisp(CameraId cam);
void mapDispMapGrp_off(CameraId cam, MapObject* obj);
void mapDispMapObj_off(CameraId cam, MapObject* obj);
void mapDispMapGrp(CameraId cam, MapObject* obj);
void mapDispMapObj(CameraId cam, MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapObj(CameraId cam, MapObject *obj);
void mapMain(void);
void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force);
void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint);
void bmapLoad(const char *map, const char *map2);
asm void bmapUnLoad(void);
void mapLoad(const char* map);
BOOL mapPreLoad(void);
void mapUnLoad(void);
void _mapLoad(MapWork* wp, BOOL group, const char* map);
void mapSetPlayRate(const char* name, f32 rate);
void mapReStartAnimationAll(const char* name);
void mapPauseAnimationAll(const char* name);
void mapReStartAnimation(const char* name);
void mapPauseAnimation(const char* name);
void mapPlayAnimationLv(const char* name, s32 a, s32 b);
void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3);
MapEntryAnimData* mapSearchAnmObj(const char* animName);
void makeDisplayList(BOOL group);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
void mapInit(void);
void mapGetBoundingBox(Vec* min, Vec* max);
s32 mapGetJoints(MapFileJoint* joint);
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
s32 mapGetActiveGroup(void);
MapWork* mapGetWork(void);
void N_mapDispOn(void);
void N_mapDispOff(void);
const char* getMapDataDvdRoot(void);
void mapErrorEntry(s32 arg0, const char* arg1);

asm void mapObjGetFlushColor(const char* name, u8* r, u8* g, u8* b, u8* a) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r22, 0x8(r1)
	mr. r31, r3
	mr r22, r4
	mr r23, r5
	mr r24, r6
	mr r25, r7
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	lbz r0, 0xc(r30)
	stb r0, 0x0(r22)
	lbz r0, 0xd(r30)
	stb r0, 0x0(r23)
	lbz r0, 0xe(r30)
	stb r0, 0x0(r24)
	lbz r0, 0xf(r30)
	stb r0, 0x0(r25)
	L_af_9:
	lmw r22, 0x8(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lwz r0, unk_80422f90(r2)
	stw r0, 0x8(r1)
	stb r4, 0x8(r1)
	addi r4, r1, 0xc
	stb r5, 0x9(r1)
	stb r6, 0xa(r1)
	stb r7, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl mapGrpSetColor
	mr r3, r31
	li r4, 0x40
	bl mapGrpFlagOff
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r26, 0x18(r1)
	mr. r31, r3
	lwz r8, unk_80422f8c(r2)
	lwz r0, activeGroup(r13)
	stw r8, 0x8(r1)
	mulli r0, r0, 0x2f4
	lwz r3, mapWork(r13)
	stb r4, 0x8(r1)
	stb r5, 0x9(r1)
	add r27, r3, r0
	stb r6, 0xa(r1)
	stb r7, 0xb(r1)
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	beq L_af_8
	lwz r0, 0x8(r1)
	stw r0, 0xc(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x40
	stw r0, 0x0(r30)
	L_af_8:
	lwz r0, activeGroup(r13)
	cmplwi r31, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_9
	li r28, 0x0
	b L_af_10
	L_af_9:
	mr r26, r27
	li r29, 0x0
	b L_af_11
	L_af_12:
	lwz r28, 0x154(r26)
	li r30, 0x0
	b L_af_13
	L_af_14:
	lwz r3, 0x8(r28)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_15
	b L_af_10
	L_af_15:
	addi r30, r30, 0x1
	addi r28, r28, 0x134
	L_af_13:
	lwz r0, 0x150(r26)
	cmpw r30, r0
	blt L_af_14
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_11:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_12
	li r28, 0x0
	L_af_10:
	cmplwi r28, 0x0
	bne L_af_16
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_17
	L_af_16:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	stw r0, 0x0(r28)
	L_af_17:
	lmw r26, 0x18(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapGrpFlushOff(const char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, 0x10
	stw r0, 0x14(r1)
	bl mapGrpFlagOff
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapGrpFlushOn(const char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, 0x10
	stw r0, 0x14(r1)
	bl mapGrpFlagOn
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapObjFlushOff(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r26
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x0(r31)
	L_af_9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapObjFlushOn(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r26
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	lwz r0, 0x0(r31)
	oris r0, r0, 0x10
	stw r0, 0x0(r31)
	L_af_9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapSetTevCallback(s32 index, MapTevCallback callback) {
	nofralloc
	lwz r5, activeGroup(r13)
	slwi r0, r3, 2
	lwz r6, mapWork(r13)
	mulli r3, r5, 0x2f4
	addi r3, r3, 0x110
	add r0, r3, r0
	stwx r4, r6, r0
	blr
}

asm BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor) {
	nofralloc
	rlwinm. r0, r3, 0, 25, 25
	beq L_af_1
	lbz r0, 0x3(r4)
	cmplwi r0, 0xff
	beq L_af_1
	li r3, 0x1
	blr
	L_af_1:
	lbz r0, 0x3(r5)
	cmplwi r0, 0xff
	beq L_af_2
	li r3, 0x1
	blr
	L_af_2:
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_3
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r4, r4, r0
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_3
	lbz r0, 0x19(r4)
	cmplwi r0, 0xff
	beq L_af_3
	li r3, 0x1
	blr
	L_af_3:
	rlwinm. r0, r3, 0, 19, 19
	bne L_af_4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	lhz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_4
	lbz r0, 0x1d(r3)
	cmplwi r0, 0xff
	beq L_af_4
	li r3, 0x1
	blr
	L_af_4:
	li r3, 0x0
	blr
}

asm void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl) {
	nofralloc
	cmpwi r4, 0x2
	bne L_af_1
	lfs f2, 0x0(r5)
	lfs f0, 0xc(r5)
	fsubs f0, f0, f2
	fmadds f0, f1, f0, f2
	stfs f0, 0x0(r3)
	lfs f2, 0x4(r5)
	lfs f0, 0x10(r5)
	fsubs f0, f0, f2
	fmadds f0, f1, f0, f2
	stfs f0, 0x4(r3)
	lfs f2, 0x8(r5)
	lfs f0, 0x14(r5)
	fsubs f0, f0, f2
	fmadds f0, f1, f0, f2
	stfs f0, 0x8(r3)
	blr
	L_af_1:
	subi r9, r4, 0x1
	li r8, 0x0
	b L_af_2
	L_af_3:
	add r4, r8, r9
	srwi r0, r4, 31
	add r0, r0, r4
	srawi r4, r0, 1
	slwi r0, r4, 2
	lfsx f0, r6, r0
	fcmpo cr0, f0, f1
	bge L_af_4
	addi r8, r4, 0x1
	b L_af_2
	L_af_4:
	mr r9, r4
	L_af_2:
	cmpw r8, r9
	blt L_af_3
	cmpwi r8, 0x0
	ble L_af_5
	subi r8, r8, 0x1
	L_af_5:
	mulli r9, r8, 0xc
	slwi r0, r8, 2
	lfsx f2, r6, r0
	add r8, r6, r0
	lfs f6, float_2_80419858(r2)
	add r6, r7, r9
	lfsx f7, r7, r9
	add r4, r5, r9
	lfs f4, 0xc(r6)
	fsubs f1, f1, f2
	lfs f0, 0x4(r8)
	fsubs f5, f4, f7
	lfsx f8, r5, r9
	lfs f3, 0xc(r4)
	fsubs f2, f0, f2
	fmadds f4, f6, f7, f4
	lfs f0, float_3_8041984c(r2)
	fmuls f5, f1, f5
	fsubs f3, f3, f8
	fdivs f5, f5, f2
	fdivs f3, f3, f2
	fmadds f5, f0, f7, f5
	fnmsubs f3, f2, f4, f3
	fmadds f3, f1, f5, f3
	fmadds f3, f1, f3, f8
	stfs f3, 0x0(r3)
	lfs f7, 0x4(r6)
	lfs f4, 0x10(r6)
	lfs f8, 0x4(r4)
	fsubs f5, f4, f7
	lfs f3, 0x10(r4)
	fmadds f4, f6, f7, f4
	fsubs f3, f3, f8
	fmuls f5, f1, f5
	fdivs f3, f3, f2
	fdivs f5, f5, f2
	fmadds f5, f0, f7, f5
	fnmsubs f3, f2, f4, f3
	fmadds f3, f1, f5, f3
	fmadds f3, f1, f3, f8
	stfs f3, 0x4(r3)
	lfs f7, 0x8(r6)
	lfs f4, 0x14(r6)
	lfs f8, 0x8(r4)
	fsubs f5, f4, f7
	lfs f3, 0x14(r4)
	fmadds f4, f6, f7, f4
	fsubs f3, f3, f8
	fmuls f5, f1, f5
	fdivs f3, f3, f2
	fdivs f5, f5, f2
	fmadds f5, f0, f7, f5
	fnmsubs f0, f2, f4, f3
	fmadds f0, f1, f5, f0
	fmadds f0, f1, f0, f8
	stfs f0, 0x8(r3)
	blr
}

asm void spline_maketable(s32 n, Vec* pts, f32* t, Vec* out) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r26, 0x18(r1)
	mr r26, r3
	lis r3, vec3_802c16d8@ha
	mr r27, r4
	addi r31, r3, vec3_802c16d8@l
	mr r28, r5
	mr r29, r6
	slwi r3, r26, 2
	bl _mapAlloc
	mr r0, r3
	mulli r3, r26, 0xc
	mr r30, r0
	bl _mapAlloc
	lfs f4, float_0_80419850(r2)
	subi r0, r26, 0x1
	addi r5, r27, 0xc
	addi r6, r28, 0x4
	stfs f4, 0x0(r28)
	mtctr r0
	cmpwi r26, 0x1
	ble L_af_1
	L_af_2:
	lfs f1, 0x4(r5)
	lfs f0, -0x8(r5)
	lfs f3, 0x0(r5)
	fsubs f5, f1, f0
	lfs f0, -0xc(r5)
	lfs f2, 0x8(r5)
	fsubs f3, f3, f0
	lfs f1, -0x4(r5)
	fmuls f0, f5, f5
	fsubs f1, f2, f1
	fmadds f0, f3, f3, f0
	fmadds f5, f1, f1, f0
	fcmpo cr0, f5, f4
	ble L_af_3
	frsqrte f1, f5
	lfd f3, 0x2a8(r31)
	lfd f2, 0x2b0(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f0, f1, f0
	fmul f5, f5, f0
	frsp f5, f5
	b L_af_4
	L_af_3:
	lfd f0, 0x2b8(r31)
	fcmpo cr0, f5, f0
	bge L_af_5
	lis r4, __float_nan@ha
	lfs f5, __float_nan@l(r4)
	b L_af_4
	L_af_5:
	stfs f5, 0x8(r1)
	lis r0, 0x7f80
	lwz r7, 0x8(r1)
	rlwinm r4, r7, 0, 1, 8
	cmpw r4, r0
	beq L_af_6
	bge L_af_7
	cmpwi r4, 0x0
	beq L_af_8
	b L_af_7
	L_af_6:
	clrlwi. r0, r7, 9
	beq L_af_9
	li r0, 0x1
	b L_af_10
	L_af_9:
	li r0, 0x2
	b L_af_10
	L_af_8:
	clrlwi. r0, r7, 9
	beq L_af_11
	li r0, 0x5
	b L_af_10
	L_af_11:
	li r0, 0x3
	b L_af_10
	L_af_7:
	li r0, 0x4
	L_af_10:
	cmpwi r0, 0x1
	bne L_af_4
	lis r4, __float_nan@ha
	lfs f5, __float_nan@l(r4)
	L_af_4:
	lfs f0, -0x4(r6)
	addi r5, r5, 0xc
	fadds f0, f0, f5
	stfs f0, 0x0(r6)
	addi r6, r6, 0x4
	bdnz L_af_2
	L_af_1:
	cmpwi r26, 0x1
	li r7, 0x1
	ble L_af_12
	subi r0, r26, 0x1
	subi r5, r26, 0x8
	cmpwi r0, 0x8
	ble L_af_13
	addi r0, r5, 0x6
	slwi r4, r26, 2
	srwi r0, r0, 3
	addi r6, r28, 0x4
	subi r4, r4, 0x4
	mtctr r0
	cmpwi r5, 0x1
	ble L_af_13
	L_af_14:
	lfs f1, 0x0(r6)
	addi r7, r7, 0x8
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x0(r6)
	lfs f1, 0x4(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x4(r6)
	lfs f1, 0x8(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x8(r6)
	lfs f1, 0xc(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0xc(r6)
	lfs f1, 0x10(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x10(r6)
	lfs f1, 0x14(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x14(r6)
	lfs f1, 0x18(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x18(r6)
	lfs f1, 0x1c(r6)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x1c(r6)
	addi r6, r6, 0x20
	bdnz L_af_14
	L_af_13:
	slwi r5, r7, 2
	slwi r4, r26, 2
	subf r0, r7, r26
	add r5, r28, r5
	subi r4, r4, 0x4
	mtctr r0
	cmpw r7, r26
	bge L_af_12
	L_af_15:
	lfs f1, 0x0(r5)
	lfsx f0, r28, r4
	fdivs f0, f1, f0
	stfs f0, 0x0(r5)
	addi r5, r5, 0x4
	bdnz L_af_15
	L_af_12:
	lfs f3, float_0_80419850(r2)
	mulli r9, r26, 0xc
	subic. r0, r26, 0x1
	stfs f3, 0x0(r29)
	mr r4, r28
	add r10, r29, r9
	mr r5, r30
	stfs f3, 0x4(r29)
	mr r6, r27
	mr r7, r3
	stfs f3, 0x8(r29)
	stfs f3, -0xc(r10)
	stfs f3, -0x8(r10)
	stfs f3, -0x4(r10)
	mtctr r0
	ble L_af_16
	L_af_17:
	lfs f1, 0x4(r4)
	lfs f0, 0x0(r4)
	fsubs f0, f1, f0
	stfs f0, 0x0(r5)
	lfs f0, 0x0(r5)
	fcmpu cr0, f3, f0
	bne L_af_18
	lfs f0, float_0p0001_8041985c(r2)
	stfs f0, 0x0(r5)
	L_af_18:
	lfs f2, 0xc(r6)
	addi r4, r4, 0x4
	lfs f1, 0x0(r6)
	lfs f0, 0x0(r5)
	fsubs f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0xc(r7)
	lfs f2, 0x10(r6)
	lfs f1, 0x4(r6)
	lfs f0, 0x0(r5)
	fsubs f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x10(r7)
	lfs f2, 0x14(r6)
	lfs f1, 0x8(r6)
	addi r6, r6, 0xc
	lfs f0, 0x0(r5)
	addi r5, r5, 0x4
	fsubs f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x14(r7)
	addi r7, r7, 0xc
	bdnz L_af_17
	L_af_16:
	lfs f2, 0x18(r3)
	subi r4, r26, 0x2
	lfs f1, 0xc(r3)
	subi r0, r4, 0x1
	lfs f0, float_2_80419858(r2)
	addi r5, r3, 0xc
	fsubs f1, f2, f1
	addi r6, r30, 0x4
	addi r7, r29, 0xc
	addi r8, r28, 0x4
	stfs f1, 0xc(r29)
	lfs f2, 0x1c(r3)
	lfs f1, 0x10(r3)
	fsubs f1, f2, f1
	stfs f1, 0x10(r29)
	lfs f2, 0x20(r3)
	lfs f1, 0x14(r3)
	fsubs f1, f2, f1
	stfs f1, 0x14(r29)
	lfs f2, 0x8(r28)
	lfs f1, 0x0(r28)
	fsubs f1, f2, f1
	fmuls f1, f0, f1
	stfs f1, 0xc(r3)
	lfs f2, 0x8(r28)
	lfs f1, 0x0(r28)
	fsubs f1, f2, f1
	fmuls f1, f0, f1
	stfs f1, 0x10(r3)
	lfs f2, 0x8(r28)
	lfs f1, 0x0(r28)
	fsubs f1, f2, f1
	fmuls f1, f0, f1
	stfs f1, 0x14(r3)
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_19
	L_af_20:
	lfs f6, 0x0(r6)
	lfs f1, 0x0(r5)
	lfs f5, 0x4(r5)
	fdivs f7, f6, f1
	lfs f4, 0x8(r5)
	lfs f2, 0x18(r5)
	lfs f1, 0xc(r5)
	lfs f3, 0x0(r7)
	fsubs f1, f2, f1
	fdivs f5, f6, f5
	fnmsubs f1, f7, f3, f1
	fdivs f4, f6, f4
	stfs f1, 0xc(r7)
	lfs f2, 0x1c(r5)
	lfs f1, 0x10(r5)
	lfs f3, 0x4(r7)
	fsubs f1, f2, f1
	fnmsubs f1, f5, f3, f1
	stfs f1, 0x10(r7)
	lfs f2, 0x20(r5)
	lfs f1, 0x14(r5)
	lfs f3, 0x8(r7)
	fsubs f1, f2, f1
	fnmsubs f1, f4, f3, f1
	stfs f1, 0x14(r7)
	addi r7, r7, 0xc
	lfs f1, 0x0(r6)
	lfs f3, 0x8(r8)
	lfs f2, 0x0(r8)
	fmuls f1, f7, f1
	fsubs f2, f3, f2
	fmsubs f1, f0, f2, f1
	stfs f1, 0xc(r5)
	lfs f1, 0x0(r6)
	lfs f3, 0x8(r8)
	lfs f2, 0x0(r8)
	fmuls f1, f5, f1
	fsubs f2, f3, f2
	fmsubs f1, f0, f2, f1
	stfs f1, 0x10(r5)
	lfs f1, 0x0(r6)
	addi r6, r6, 0x4
	lfs f3, 0x8(r8)
	lfs f2, 0x0(r8)
	fmuls f1, f4, f1
	addi r8, r8, 0x4
	fsubs f2, f3, f2
	fmsubs f1, f0, f2, f1
	stfs f1, 0x14(r5)
	addi r5, r5, 0xc
	bdnz L_af_20
	L_af_19:
	slwi r0, r26, 2
	add r5, r29, r9
	add r9, r30, r0
	lfs f1, -0xc(r10)
	lfs f2, -0x8(r9)
	mulli r8, r4, 0xc
	lfs f0, -0x18(r5)
	slwi r0, r4, 2
	cmpwi r4, 0x0
	fnmsubs f0, f2, f1, f0
	add r6, r29, r8
	add r7, r30, r0
	add r8, r3, r8
	stfs f0, -0x18(r5)
	lfs f2, -0x8(r9)
	lfs f1, -0x8(r10)
	lfs f0, -0x14(r5)
	fnmsubs f0, f2, f1, f0
	stfs f0, -0x14(r5)
	lfs f2, -0x8(r9)
	lfs f1, -0x4(r10)
	lfs f0, -0x10(r5)
	fnmsubs f0, f2, f1, f0
	stfs f0, -0x10(r5)
	ble L_af_21
	srwi. r0, r4, 1
	mtctr r0
	beq L_af_22
	L_af_23:
	lfs f3, 0x0(r7)
	lfs f2, 0xc(r6)
	lfs f1, 0x0(r6)
	lfs f0, 0x0(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x0(r6)
	lfs f3, 0x0(r7)
	lfs f2, 0x10(r6)
	lfs f1, 0x4(r6)
	lfs f0, 0x4(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x4(r6)
	lfs f3, 0x0(r7)
	lfs f2, 0x14(r6)
	lfs f1, 0x8(r6)
	lfs f0, 0x8(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x8(r6)
	lfs f3, -0x4(r7)
	lfs f2, 0x0(r6)
	lfs f1, -0xc(r6)
	lfs f0, -0xc(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, -0xc(r6)
	lfs f3, -0x4(r7)
	lfs f2, 0x4(r6)
	lfs f1, -0x8(r6)
	lfs f0, -0x8(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, -0x8(r6)
	lfs f3, -0x4(r7)
	subi r7, r7, 0x8
	lfs f0, -0x4(r8)
	subi r8, r8, 0x18
	lfs f2, 0x8(r6)
	lfs f1, -0x4(r6)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, -0x4(r6)
	subi r6, r6, 0x18
	bdnz L_af_23
	andi. r4, r4, 0x1
	beq L_af_21
	L_af_22:
	mtctr r4
	L_af_24:
	lfs f3, 0x0(r7)
	lfs f2, 0xc(r6)
	lfs f1, 0x0(r6)
	lfs f0, 0x0(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x0(r6)
	lfs f3, 0x0(r7)
	lfs f2, 0x10(r6)
	lfs f1, 0x4(r6)
	lfs f0, 0x4(r8)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x4(r6)
	lfs f3, 0x0(r7)
	subi r7, r7, 0x4
	lfs f0, 0x8(r8)
	subi r8, r8, 0xc
	lfs f2, 0x14(r6)
	lfs f1, 0x8(r6)
	fnmsubs f1, f3, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x8(r6)
	subi r6, r6, 0xc
	bdnz L_af_24
	L_af_21:
	bl _mapFree
	mr r3, r30
	bl _mapFree
	lmw r26, 0x18(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapSetProjMtx(Mtx mtx) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	la r4, projMtx(r13)
	stw r0, 0x14(r1)
	bl PSMTXCopy
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapSetProjTexObj(GXTexObj* obj, void* imgRef) {
	nofralloc
	lwz r5, 0x0(r3)
	lwz r0, 0x4(r3)
	stw r5, projTexObj(r13)
	stw r0, projTexObj+0x4(r13)
	lwz r5, 0x8(r3)
	lwz r0, 0xc(r3)
	stw r5, projTexObj+0x8(r13)
	stw r0, projTexObj+0xC(r13)
	lwz r5, 0x10(r3)
	lwz r0, 0x14(r3)
	stw r5, projTexObj+0x10(r13)
	stw r0, projTexObj+0x14(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x1c(r3)
	stw r5, projTexObj+0x18(r13)
	stw r0, projTexObj+0x1C(r13)
	stw r4, projTexImgRef(r13)
	blr
}

asm void mapGrpSetColor(const char* name, GXColor color) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lwz r4, 0x0(r4)
	stw r0, 0x34(r1)
	stmw r26, 0x18(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	stw r4, 0x8(r1)
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	mr r3, r31
	addi r4, r1, 0x8
	li r5, 0x0
	bl setColor
	lmw r26, 0x18(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void setColor(MapObject* obj, GXColor color, BOOL doNext) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stmw r26, 0x58(r1)
	mr. r28, r3
	mr r29, r4
	mr r30, r5
	beq L_af_1
	lwz r3, 0x0(r29)
	stw r3, 0xc(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x40
	stw r0, 0x0(r28)
	lwz r31, 0xe4(r28)
	cmplwi r31, 0x0
	beq L_af_2
	stw r3, 0x4c(r1)
	beq L_af_2
	stw r3, 0xc(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x40
	stw r0, 0x0(r31)
	lwz r27, 0xe4(r31)
	cmplwi r27, 0x0
	beq L_af_3
	beq L_af_3
	stw r3, 0xc(r27)
	lwz r0, 0x0(r27)
	ori r0, r0, 0x40
	stw r0, 0x0(r27)
	lwz r26, 0xe4(r27)
	cmplwi r26, 0x0
	beq L_af_4
	beq L_af_4
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r0, 0xe4(r26)
	cmplwi r0, 0x0
	beq L_af_5
	stw r3, 0x40(r1)
	addi r4, r1, 0x40
	li r5, 0x1
	lwz r3, 0xe4(r26)
	bl setColor
	L_af_5:
	lwz r0, 0xe8(r26)
	cmplwi r0, 0x0
	beq L_af_4
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x44
	li r5, 0x1
	stw r0, 0x44(r1)
	lwz r3, 0xe8(r26)
	bl setColor
	L_af_4:
	lwz r26, 0xe8(r27)
	cmplwi r26, 0x0
	beq L_af_3
	beq L_af_3
	lwz r3, 0x4c(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r0, 0xe4(r26)
	cmplwi r0, 0x0
	beq L_af_6
	stw r3, 0x38(r1)
	addi r4, r1, 0x38
	li r5, 0x1
	lwz r3, 0xe4(r26)
	bl setColor
	L_af_6:
	lwz r0, 0xe8(r26)
	cmplwi r0, 0x0
	beq L_af_3
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x3c
	li r5, 0x1
	stw r0, 0x3c(r1)
	lwz r3, 0xe8(r26)
	bl setColor
	L_af_3:
	lwz r26, 0xe8(r31)
	cmplwi r26, 0x0
	beq L_af_2
	beq L_af_2
	lwz r3, 0x4c(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_7
	beq L_af_7
	stw r3, 0xc(r27)
	lwz r0, 0x0(r27)
	ori r0, r0, 0x40
	stw r0, 0x0(r27)
	lwz r0, 0xe4(r27)
	cmplwi r0, 0x0
	beq L_af_8
	stw r3, 0x30(r1)
	addi r4, r1, 0x30
	li r5, 0x1
	lwz r3, 0xe4(r27)
	bl setColor
	L_af_8:
	lwz r0, 0xe8(r27)
	cmplwi r0, 0x0
	beq L_af_7
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x34
	li r5, 0x1
	stw r0, 0x34(r1)
	lwz r3, 0xe8(r27)
	bl setColor
	L_af_7:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_2
	beq L_af_2
	lwz r3, 0x4c(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r0, 0xe4(r26)
	cmplwi r0, 0x0
	beq L_af_9
	stw r3, 0x28(r1)
	addi r4, r1, 0x28
	li r5, 0x1
	lwz r3, 0xe4(r26)
	bl setColor
	L_af_9:
	lwz r0, 0xe8(r26)
	cmplwi r0, 0x0
	beq L_af_2
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x2c
	li r5, 0x1
	stw r0, 0x2c(r1)
	lwz r3, 0xe8(r26)
	bl setColor
	L_af_2:
	cmpwi r30, 0x0
	beq L_af_1
	lwz r31, 0xe8(r28)
	cmplwi r31, 0x0
	beq L_af_1
	lwz r3, 0x0(r29)
	stw r3, 0x48(r1)
	beq L_af_1
	stw r3, 0xc(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x40
	stw r0, 0x0(r31)
	lwz r26, 0xe4(r31)
	cmplwi r26, 0x0
	beq L_af_10
	beq L_af_10
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_11
	beq L_af_11
	stw r3, 0xc(r27)
	lwz r0, 0x0(r27)
	ori r0, r0, 0x40
	stw r0, 0x0(r27)
	lwz r0, 0xe4(r27)
	cmplwi r0, 0x0
	beq L_af_12
	stw r3, 0x20(r1)
	addi r4, r1, 0x20
	li r5, 0x1
	lwz r3, 0xe4(r27)
	bl setColor
	L_af_12:
	lwz r0, 0xe8(r27)
	cmplwi r0, 0x0
	beq L_af_11
	lwz r0, 0x48(r1)
	addi r4, r1, 0x24
	li r5, 0x1
	stw r0, 0x24(r1)
	lwz r3, 0xe8(r27)
	bl setColor
	L_af_11:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_10
	beq L_af_10
	lwz r3, 0x48(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r0, 0xe4(r26)
	cmplwi r0, 0x0
	beq L_af_13
	stw r3, 0x18(r1)
	addi r4, r1, 0x18
	li r5, 0x1
	lwz r3, 0xe4(r26)
	bl setColor
	L_af_13:
	lwz r0, 0xe8(r26)
	cmplwi r0, 0x0
	beq L_af_10
	lwz r0, 0x48(r1)
	addi r4, r1, 0x1c
	li r5, 0x1
	stw r0, 0x1c(r1)
	lwz r3, 0xe8(r26)
	bl setColor
	L_af_10:
	lwz r26, 0xe8(r31)
	cmplwi r26, 0x0
	beq L_af_1
	beq L_af_1
	lwz r3, 0x48(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_14
	beq L_af_14
	stw r3, 0xc(r27)
	lwz r0, 0x0(r27)
	ori r0, r0, 0x40
	stw r0, 0x0(r27)
	lwz r0, 0xe4(r27)
	cmplwi r0, 0x0
	beq L_af_15
	stw r3, 0x10(r1)
	addi r4, r1, 0x10
	li r5, 0x1
	lwz r3, 0xe4(r27)
	bl setColor
	L_af_15:
	lwz r0, 0xe8(r27)
	cmplwi r0, 0x0
	beq L_af_14
	lwz r0, 0x48(r1)
	addi r4, r1, 0x14
	li r5, 0x1
	stw r0, 0x14(r1)
	lwz r3, 0xe8(r27)
	bl setColor
	L_af_14:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_1
	beq L_af_1
	lwz r3, 0x48(r1)
	stw r3, 0xc(r26)
	lwz r0, 0x0(r26)
	ori r0, r0, 0x40
	stw r0, 0x0(r26)
	lwz r0, 0xe4(r26)
	cmplwi r0, 0x0
	beq L_af_16
	stw r3, 0x8(r1)
	addi r4, r1, 0x8
	li r5, 0x1
	lwz r3, 0xe4(r26)
	bl setColor
	L_af_16:
	lwz r0, 0xe8(r26)
	cmplwi r0, 0x0
	beq L_af_1
	lwz r0, 0x48(r1)
	addi r4, r1, 0xc
	li r5, 0x1
	stw r0, 0xc(r1)
	lwz r3, 0xe8(r26)
	bl setColor
	L_af_1:
	lmw r26, 0x58(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void mapObjSetColor(const char* name, GXColor* color) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r25, r3
	mr r26, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	beq L_af_8
	lwz r0, 0x0(r26)
	stw r0, 0xc(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x40
	stw r0, 0x0(r31)
	L_af_8:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapBlendOff2(void) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r0, 0x2f4
	addi r3, r3, 0x4
	lhzx r0, r4, r3
	rlwinm r0, r0, 0, 30, 28
	sthx r0, r4, r3
	blr
}

asm void mapBlendOff(void) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r0, 0x2f4
	addi r3, r3, 0x4
	lhzx r0, r4, r3
	rlwinm r0, r0, 0, 31, 29
	sthx r0, r4, r3
	blr
}

asm void mapGetBlend2(GXColor* color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r4, r4, r0
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_1
	lwz r0, 0x1a(r4)
	stw r0, 0x0(r3)
	blr
	L_af_1:
	lwz r0, dat_80419844(r2)
	stw r0, 0x0(r3)
	blr
}

asm void mapGetBlend(GXColor* color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r4, r4, r0
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_1
	lwz r0, 0x16(r4)
	stw r0, 0x0(r3)
	blr
	L_af_1:
	lwz r0, dat_80419840(r2)
	stw r0, 0x0(r3)
	blr
}

asm void mapSetBlend2(GXColor* color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r5, mapWork(r13)
	mulli r4, r0, 0x2f4
	lwz r0, 0x0(r3)
	add r3, r5, r4
	stw r0, 0x1a(r3)
	lhz r0, 0x4(r3)
	ori r0, r0, 0x4
	sth r0, 0x4(r3)
	blr
}

asm void mapSetBlend(GXColor* color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r5, mapWork(r13)
	mulli r4, r0, 0x2f4
	lwz r0, 0x0(r3)
	add r3, r5, r4
	stw r0, 0x16(r3)
	lhz r0, 0x4(r3)
	ori r0, r0, 0x2
	sth r0, 0x4(r3)
	blr
}

asm void mapFogOff(void) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r0, 0x2f4
	addi r3, r3, 0x4
	lhzx r0, r4, r3
	rlwinm r0, r0, 0, 16, 30
	sthx r0, r4, r3
	blr
}

asm void mapFogOn(void) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r0, 0x2f4
	addi r3, r3, 0x4
	lhzx r0, r4, r3
	ori r0, r0, 0x1
	sthx r0, r4, r3
	blr
}

asm void mapGetFog(s32* type, f32* start, f32* end, GXColor* color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r7, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r7, r7, r0
	lwz r0, 0x28(r7)
	stw r0, 0x0(r3)
	lfs f0, 0x2c(r7)
	stfs f0, 0x0(r4)
	lfs f0, 0x30(r7)
	stfs f0, 0x0(r5)
	lwz r0, 0x34(r7)
	stw r0, 0x0(r6)
	blr
}

asm void mapSetFog(s32 type, f32 start, f32 end, GXColor color) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r6, mapWork(r13)
	mulli r5, r0, 0x2f4
	lwz r0, 0x0(r4)
	add r4, r6, r5
	stw r3, 0x28(r4)
	stfs f1, 0x2c(r4)
	stfs f2, 0x30(r4)
	stw r0, 0x34(r4)
	blr
}

asm void mapObjGetPos(const char* name, Vec* pos) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r5, vec3_802c18f4@ha
	stw r0, 0x44(r1)
	stmw r25, 0x24(r1)
	mr. r30, r3
	li r28, 0x0
	mr r31, r4
	lwzu r7, vec3_802c18f4@l(r5)
	lwz r0, activeGroup(r13)
	lwz r6, 0x4(r5)
	lwz r5, 0x8(r5)
	mulli r0, r0, 0x2f4
	lwz r3, mapWork(r13)
	stw r28, 0x8(r1)
	add r26, r3, r0
	stw r7, 0xc(r1)
	stw r6, 0x10(r1)
	stw r5, 0x14(r1)
	bne L_af_1
	b L_af_2
	L_af_1:
	mr r25, r26
	b L_af_3
	L_af_4:
	lwz r29, 0x154(r25)
	li r27, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r29)
	mr r4, r30
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	mr r28, r29
	b L_af_2
	L_af_7:
	addi r27, r27, 0x1
	addi r29, r29, 0x134
	L_af_5:
	lwz r0, 0x150(r25)
	cmpw r27, r0
	blt L_af_6
	addi r25, r25, 0x178
	addi r28, r28, 0x1
	L_af_3:
	lwz r0, 0x0(r26)
	cmpw r28, r0
	blt L_af_4
	li r28, 0x0
	L_af_2:
	cmplwi r28, 0x0
	bne L_af_8
	lis r3, vec3_802c1900@ha
	addi r4, r3, vec3_802c1900@l
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0x8(r4)
	stw r0, 0x8(r31)
	b L_af_9
	L_af_8:
	mr r3, r28
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	li r6, 0x0
	bl mapObjGetPosSub
	lwz r4, 0x8(r1)
	lis r0, 0x4330
	stw r0, 0x18(r1)
	lis r3, double_to_int_802c1998@ha
	xoris r0, r4, 0x8000
	lfd f1, double_to_int_802c1998@l(r3)
	stw r0, 0x1c(r1)
	mr r4, r31
	lfs f2, float_1_80419860(r2)
	addi r3, r1, 0xc
	lfd f0, 0x18(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl PSVECScale
	L_af_9:
	lmw r25, 0x24(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void mapObjGetPosSub(MapObject* obj, Vec* sum, s32* count, BOOL doNext) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stmw r25, 0xc4(r1)
	mr r28, r3
	mr r31, r4
	mr r30, r5
	mr r29, r6
	lwz r27, 0xe4(r3)
	cmplwi r27, 0x0
	beq L_af_1
	lwz r26, 0xe4(r27)
	cmplwi r26, 0x0
	beq L_af_2
	lwz r25, 0xe4(r26)
	cmplwi r25, 0x0
	beq L_af_3
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_4
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_5
	L_af_4:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x5c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x5c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_5:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_6
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_6
	L_af_3:
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	addi r5, r1, 0x8c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x8c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_6:
	lwz r25, 0xe8(r26)
	cmplwi r25, 0x0
	beq L_af_7
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_8
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_9
	L_af_8:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x50
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x50
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_9:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_7
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_7
	L_af_2:
	addi r3, r27, 0x1c
	addi r4, r27, 0x10
	addi r5, r1, 0xa4
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0xa4
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_7:
	lwz r25, 0xe8(r27)
	cmplwi r25, 0x0
	beq L_af_10
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_11
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_13
	L_af_12:
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	addi r5, r1, 0x44
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x44
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_13:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_14
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_14
	L_af_11:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x80
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x80
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_14:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_10
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_16
	L_af_15:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x38
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x38
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_16:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_10
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_10
	L_af_1:
	addi r3, r28, 0x1c
	addi r4, r28, 0x10
	addi r5, r1, 0xb0
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0xb0
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_10:
	cmpwi r29, 0x0
	beq L_af_17
	lwz r25, 0xe8(r28)
	cmplwi r25, 0x0
	beq L_af_17
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_18
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_19
	lwz r3, 0xe4(r27)
	cmplwi r3, 0x0
	beq L_af_20
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_21
	L_af_20:
	addi r3, r27, 0x1c
	addi r4, r27, 0x10
	addi r5, r1, 0x2c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x2c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_21:
	lwz r3, 0xe8(r27)
	cmplwi r3, 0x0
	beq L_af_22
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_22
	L_af_19:
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	addi r5, r1, 0x74
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x74
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_22:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_23
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_24
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_25
	L_af_24:
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	addi r5, r1, 0x20
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x20
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_25:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_23
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_23
	L_af_18:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x98
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x98
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_23:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_17
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_26
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_27
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_28
	L_af_27:
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	addi r5, r1, 0x14
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x14
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_28:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_29
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_29
	L_af_26:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x68
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x68
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_29:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_17
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_30
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	b L_af_31
	L_af_30:
	addi r3, r25, 0x1c
	addi r4, r25, 0x10
	addi r5, r1, 0x8
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x8
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	L_af_31:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_17
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl mapObjGetPosSub
	L_af_17:
	lmw r25, 0xc4(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm void mapObjScale(const char* name, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x68(r1)
	fmr f31, f3
	stfd f30, 0x60(r1)
	fmr f30, f2
	stfd f29, 0x58(r1)
	fmr f29, f1
	stmw r26, 0x40(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	beq L_af_8
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	bne L_af_9
	addi r3, r31, 0xac
	bl PSMTXIdentity
	L_af_9:
	fmr f1, f29
	addi r3, r1, 0x8
	fmr f2, f30
	fmr f3, f31
	bl PSMTXScale
	addi r3, r31, 0xac
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r31)
	oris r0, r0, 0x20
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x200
	stw r0, 0x0(r31)
	L_af_8:
	lfd f31, 0x68(r1)
	lfd f30, 0x60(r1)
	lfd f29, 0x58(r1)
	lmw r26, 0x40(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void mapObjTranslate(const char* name, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stmw r26, 0x38(r1)
	lwz r0, activeGroup(r13)
	mr. r26, r3
	fmr f29, f1
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	fmr f30, f2
	fmr f31, f3
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	beq L_af_8
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	bne L_af_9
	addi r3, r31, 0xac
	bl PSMTXIdentity
	L_af_9:
	lfs f0, float_10_80419864(r2)
	addi r3, r1, 0x8
	fdivs f1, f29, f0
	fdivs f2, f30, f0
	fdivs f3, f31, f0
	bl PSMTXTrans
	addi r3, r31, 0xac
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r31)
	oris r0, r0, 0x20
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x200
	stw r0, 0x0(r31)
	L_af_8:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	lmw r26, 0x38(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void mapObjRotate(const char* name, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stfd f31, 0xd0(r1)
	psq_st f31, 0xd8(r1), 0, 0
	stfd f30, 0xc0(r1)
	psq_st f30, 0xc8(r1), 0, 0
	stfd f29, 0xb0(r1)
	psq_st f29, 0xb8(r1), 0, 0
	stmw r26, 0x98(r1)
	lwz r0, activeGroup(r13)
	mr. r26, r3
	fmr f29, f1
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	fmr f30, f2
	fmr f31, f3
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	cmplwi r31, 0x0
	beq L_af_8
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	bne L_af_9
	addi r3, r31, 0xac
	bl PSMTXIdentity
	L_af_9:
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x68
	li r4, 0x78
	fmuls f1, f0, f29
	bl PSMTXRotRad
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x38
	li r4, 0x79
	fmuls f1, f0, f30
	bl PSMTXRotRad
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x8
	li r4, 0x7a
	fmuls f1, f0, f31
	bl PSMTXRotRad
	addi r3, r31, 0xac
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	addi r3, r31, 0xac
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	addi r3, r31, 0xac
	addi r4, r1, 0x68
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r31)
	oris r0, r0, 0x20
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x200
	stw r0, 0x0(r31)
	L_af_8:
	psq_l f31, 0xd8(r1), 0, 0
	lfd f31, 0xd0(r1)
	psq_l f30, 0xc8(r1), 0, 0
	lfd f30, 0xc0(r1)
	psq_l f29, 0xb8(r1), 0, 0
	lfd f29, 0xb0(r1)
	lmw r26, 0x98(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm void mapGrpClearOffScreen(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	mr r3, r31
	li r4, -0x1
	li r5, 0x0
	bl _setOffScrnId
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapObjClearOffScreen(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	li r0, -0x1
	sth r0, 0xdc(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r31)
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapGrpSetOffScreen(const char* name, const char* offscreen) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r25, r3
	mr r26, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	mr r3, r26
	bl offscreenNameToId
	mr r0, r3
	mr r3, r31
	mr r4, r0
	li r5, 0x0
	bl _setOffScrnId
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapObjSetOffScreen(const char* name, const char* offscreen) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r25, r3
	mr r26, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	bne L_af_1
	li r31, 0x0
	b L_af_2
	L_af_1:
	mr r27, r28
	li r30, 0x0
	b L_af_3
	L_af_4:
	lwz r31, 0x154(r27)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_5:
	lwz r0, 0x150(r27)
	cmpw r29, r0
	blt L_af_6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_4
	li r31, 0x0
	L_af_2:
	mr r3, r26
	bl offscreenNameToId
	sth r3, 0xdc(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x80
	stw r0, 0x0(r31)
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void _setOffScrnId(MapObject* obj, s32 id, BOOL doNext) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r31, r4
	cmpwi r31, -0x1
	mr r28, r3
	mr r29, r5
	sth r31, 0xdc(r3)
	beq L_af_1
	lwz r0, 0x0(r28)
	ori r0, r0, 0x80
	stw r0, 0x0(r28)
	b L_af_2
	L_af_1:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r28)
	L_af_2:
	lwz r30, 0xe4(r28)
	cmplwi r30, 0x0
	beq L_af_3
	cmpwi r31, -0x1
	sth r31, 0xdc(r30)
	beq L_af_4
	lwz r0, 0x0(r30)
	ori r0, r0, 0x80
	stw r0, 0x0(r30)
	b L_af_5
	L_af_4:
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r30)
	L_af_5:
	lwz r27, 0xe4(r30)
	cmplwi r27, 0x0
	beq L_af_6
	cmpwi r31, -0x1
	sth r31, 0xdc(r27)
	beq L_af_7
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b L_af_8
	L_af_7:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	L_af_8:
	lwz r26, 0xe4(r27)
	cmplwi r26, 0x0
	beq L_af_9
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_10
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_11
	L_af_10:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_11:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_12:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_9
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_9:
	lwz r26, 0xe8(r27)
	cmplwi r26, 0x0
	beq L_af_6
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_13
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_14
	L_af_13:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_14:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_15:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_6
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_6:
	lwz r26, 0xe8(r30)
	cmplwi r26, 0x0
	beq L_af_3
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_16
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_17
	L_af_16:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_17:
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_18
	cmpwi r31, -0x1
	sth r31, 0xdc(r27)
	beq L_af_19
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b L_af_20
	L_af_19:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	L_af_20:
	lwz r3, 0xe4(r27)
	cmplwi r3, 0x0
	beq L_af_21
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_21:
	lwz r3, 0xe8(r27)
	cmplwi r3, 0x0
	beq L_af_18
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_18:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_3
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_22
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_23
	L_af_22:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_23:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_24
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_24:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_3
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_3:
	cmpwi r29, 0x0
	beq L_af_25
	lwz r30, 0xe8(r28)
	cmplwi r30, 0x0
	beq L_af_25
	cmpwi r31, -0x1
	sth r31, 0xdc(r30)
	beq L_af_26
	lwz r0, 0x0(r30)
	ori r0, r0, 0x80
	stw r0, 0x0(r30)
	b L_af_27
	L_af_26:
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r30)
	L_af_27:
	lwz r26, 0xe4(r30)
	cmplwi r26, 0x0
	beq L_af_28
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_29
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_30
	L_af_29:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_30:
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_31
	cmpwi r31, -0x1
	sth r31, 0xdc(r27)
	beq L_af_32
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b L_af_33
	L_af_32:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	L_af_33:
	lwz r3, 0xe4(r27)
	cmplwi r3, 0x0
	beq L_af_34
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_34:
	lwz r3, 0xe8(r27)
	cmplwi r3, 0x0
	beq L_af_31
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_31:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_28
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_35
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_36
	L_af_35:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_36:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_37
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_37:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_28
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_28:
	lwz r26, 0xe8(r30)
	cmplwi r26, 0x0
	beq L_af_25
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_38
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_39
	L_af_38:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_39:
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_40
	cmpwi r31, -0x1
	sth r31, 0xdc(r27)
	beq L_af_41
	lwz r0, 0x0(r27)
	ori r0, r0, 0x80
	stw r0, 0x0(r27)
	b L_af_42
	L_af_41:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r27)
	L_af_42:
	lwz r3, 0xe4(r27)
	cmplwi r3, 0x0
	beq L_af_43
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_43:
	lwz r3, 0xe8(r27)
	cmplwi r3, 0x0
	beq L_af_40
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_40:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_25
	cmpwi r31, -0x1
	sth r31, 0xdc(r26)
	beq L_af_44
	lwz r0, 0x0(r26)
	ori r0, r0, 0x80
	stw r0, 0x0(r26)
	b L_af_45
	L_af_44:
	lwz r0, 0x0(r26)
	rlwinm r0, r0, 0, 25, 23
	stw r0, 0x0(r26)
	L_af_45:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_46
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_46:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_25
	mr r4, r31
	li r5, 0x1
	bl _setOffScrnId
	L_af_25:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapGrpFlagOff(const char* name, u32 flags) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r31, r3
	mr r25, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	mr r3, r30
	mr r4, r25
	li r5, 0x0
	bl mapFlgOff
	L_af_9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapGrpFlagOn(const char* name, u32 flags) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r31, r3
	mr r25, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	mr r3, r30
	mr r4, r25
	li r5, 0x0
	bl mapFlgOn
	L_af_9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r31, r4
	nor r30, r31, r31
	mr r28, r3
	mr r29, r5
	lwz r0, 0x0(r3)
	and r0, r0, r30
	stw r0, 0x0(r3)
	lwz r27, 0xe4(r3)
	cmplwi r27, 0x0
	beq L_af_1
	lwz r0, 0x0(r27)
	and r0, r0, r30
	stw r0, 0x0(r27)
	lwz r26, 0xe4(r27)
	cmplwi r26, 0x0
	beq L_af_2
	lwz r0, 0x0(r26)
	and r0, r0, r30
	stw r0, 0x0(r26)
	lwz r25, 0xe4(r26)
	cmplwi r25, 0x0
	beq L_af_3
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_4
	li r5, 0x1
	bl mapFlgOff
	L_af_4:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_3
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_3:
	lwz r25, 0xe8(r26)
	cmplwi r25, 0x0
	beq L_af_2
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_5
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_5:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_2
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_2:
	lwz r25, 0xe8(r27)
	cmplwi r25, 0x0
	beq L_af_1
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_6
	lwz r0, 0x0(r26)
	and r0, r0, r30
	stw r0, 0x0(r26)
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_7
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_7:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_6
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_6:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_1
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_8
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_8:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_1
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_1:
	cmpwi r29, 0x0
	beq L_af_9
	lwz r25, 0xe8(r28)
	cmplwi r25, 0x0
	beq L_af_9
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_10
	lwz r0, 0x0(r26)
	and r0, r0, r30
	stw r0, 0x0(r26)
	lwz r27, 0xe4(r26)
	cmplwi r27, 0x0
	beq L_af_11
	lwz r0, 0x0(r27)
	and r0, r0, r30
	stw r0, 0x0(r27)
	lwz r3, 0xe4(r27)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_12:
	lwz r3, 0xe8(r27)
	cmplwi r3, 0x0
	beq L_af_11
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_11:
	lwz r26, 0xe8(r26)
	cmplwi r26, 0x0
	beq L_af_10
	lwz r0, 0x0(r26)
	and r0, r0, r30
	stw r0, 0x0(r26)
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_13
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_13:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_10
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_10:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_9
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_14
	lwz r0, 0x0(r26)
	and r0, r0, r30
	stw r0, 0x0(r26)
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_15:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_14
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_14:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_9
	lwz r0, 0x0(r25)
	and r0, r0, r30
	stw r0, 0x0(r25)
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_16
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_16:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_9
	mr r4, r31
	li r5, 0x1
	bl mapFlgOff
	L_af_9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapFlgOn(MapObject* obj, u32 flags, BOOL doNext) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	rlwinm. r29, r4, 0, 23, 23
	mr r31, r4
	mr r27, r3
	mr r28, r5
	beq L_af_1
	lwz r0, 0x114(r27)
	cmplwi r0, 0x0
	beq L_af_2
	L_af_1:
	lwz r0, 0x0(r27)
	or r0, r0, r31
	stw r0, 0x0(r27)
	L_af_2:
	lwz r30, 0xe4(r27)
	cmplwi r30, 0x0
	beq L_af_3
	cmplwi r29, 0x0
	beq L_af_4
	lwz r0, 0x114(r30)
	cmplwi r0, 0x0
	beq L_af_5
	L_af_4:
	lwz r0, 0x0(r30)
	or r0, r0, r31
	stw r0, 0x0(r30)
	L_af_5:
	lwz r26, 0xe4(r30)
	cmplwi r26, 0x0
	beq L_af_6
	cmplwi r29, 0x0
	beq L_af_7
	lwz r0, 0x114(r26)
	cmplwi r0, 0x0
	beq L_af_8
	L_af_7:
	lwz r0, 0x0(r26)
	or r0, r0, r31
	stw r0, 0x0(r26)
	L_af_8:
	lwz r25, 0xe4(r26)
	cmplwi r25, 0x0
	beq L_af_9
	cmplwi r29, 0x0
	beq L_af_10
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_11
	L_af_10:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_11:
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_12:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_9
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_9:
	lwz r25, 0xe8(r26)
	cmplwi r25, 0x0
	beq L_af_6
	cmplwi r29, 0x0
	beq L_af_13
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_14
	L_af_13:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_14:
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_15:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_6
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_6:
	lwz r25, 0xe8(r30)
	cmplwi r25, 0x0
	beq L_af_3
	cmplwi r29, 0x0
	beq L_af_16
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_17
	L_af_16:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_17:
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_18
	cmplwi r29, 0x0
	beq L_af_19
	lwz r0, 0x114(r26)
	cmplwi r0, 0x0
	beq L_af_20
	L_af_19:
	lwz r0, 0x0(r26)
	or r0, r0, r31
	stw r0, 0x0(r26)
	L_af_20:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_21
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_21:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_18
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_18:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_3
	cmplwi r29, 0x0
	beq L_af_22
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_23
	L_af_22:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_23:
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_24
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_24:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_3
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_3:
	cmpwi r28, 0x0
	beq L_af_25
	lwz r30, 0xe8(r27)
	cmplwi r30, 0x0
	beq L_af_25
	cmplwi r29, 0x0
	beq L_af_26
	lwz r0, 0x114(r30)
	cmplwi r0, 0x0
	beq L_af_27
	L_af_26:
	lwz r0, 0x0(r30)
	or r0, r0, r31
	stw r0, 0x0(r30)
	L_af_27:
	lwz r25, 0xe4(r30)
	cmplwi r25, 0x0
	beq L_af_28
	cmplwi r29, 0x0
	beq L_af_29
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_30
	L_af_29:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_30:
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_31
	cmplwi r29, 0x0
	beq L_af_32
	lwz r0, 0x114(r26)
	cmplwi r0, 0x0
	beq L_af_33
	L_af_32:
	lwz r0, 0x0(r26)
	or r0, r0, r31
	stw r0, 0x0(r26)
	L_af_33:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_34
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_34:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_31
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_31:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_28
	cmplwi r29, 0x0
	beq L_af_35
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_36
	L_af_35:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_36:
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_37
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_37:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_28
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_28:
	lwz r25, 0xe8(r30)
	cmplwi r25, 0x0
	beq L_af_25
	cmplwi r29, 0x0
	beq L_af_38
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_39
	L_af_38:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_39:
	lwz r26, 0xe4(r25)
	cmplwi r26, 0x0
	beq L_af_40
	cmplwi r29, 0x0
	beq L_af_41
	lwz r0, 0x114(r26)
	cmplwi r0, 0x0
	beq L_af_42
	L_af_41:
	lwz r0, 0x0(r26)
	or r0, r0, r31
	stw r0, 0x0(r26)
	L_af_42:
	lwz r3, 0xe4(r26)
	cmplwi r3, 0x0
	beq L_af_43
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_43:
	lwz r3, 0xe8(r26)
	cmplwi r3, 0x0
	beq L_af_40
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_40:
	lwz r25, 0xe8(r25)
	cmplwi r25, 0x0
	beq L_af_25
	cmplwi r29, 0x0
	beq L_af_44
	lwz r0, 0x114(r25)
	cmplwi r0, 0x0
	beq L_af_45
	L_af_44:
	lwz r0, 0x0(r25)
	or r0, r0, r31
	stw r0, 0x0(r25)
	L_af_45:
	lwz r3, 0xe4(r25)
	cmplwi r3, 0x0
	beq L_af_46
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_46:
	lwz r3, 0xe8(r25)
	cmplwi r3, 0x0
	beq L_af_25
	mr r4, r31
	li r5, 0x1
	bl mapFlgOn
	L_af_25:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapObjFlagOff(const char* name, u32 flags) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r31, r3
	mr r25, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	lwz r0, 0x0(r30)
	andc r0, r0, r25
	stw r0, 0x0(r30)
	L_af_9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapObjFlagOn(const char* name, u32 flags) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr. r31, r3
	mr r25, r4
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	bne L_af_1
	li r30, 0x0
	b L_af_2
	L_af_1:
	mr r26, r27
	li r29, 0x0
	b L_af_3
	L_af_4:
	lwz r30, 0x154(r26)
	li r28, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r30)
	mr r4, r31
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_2
	L_af_7:
	addi r28, r28, 0x1
	addi r30, r30, 0x134
	L_af_5:
	lwz r0, 0x150(r26)
	cmpw r28, r0
	blt L_af_6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	L_af_3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt L_af_4
	li r30, 0x0
	L_af_2:
	cmplwi r30, 0x0
	bne L_af_8
	lwz r0, error_count(r13)
	lis r3, error_data@ha
	addi r3, r3, error_data@l
	li r6, 0x0
	mulli r0, r0, 0x24
	mr r4, r31
	li r5, 0x1f
	add r3, r3, r0
	stw r6, 0x20(r3)
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	b L_af_9
	L_af_8:
	rlwinm. r0, r25, 0, 23, 23
	beq L_af_10
	lwz r0, 0x114(r30)
	cmplwi r0, 0x0
	beq L_af_9
	L_af_10:
	lwz r0, 0x0(r30)
	or r0, r0, r25
	stw r0, 0x0(r30)
	L_af_9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm MapObject* mapGetMapObj(const char *name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr. r26, r3
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r31, r3, r0
	bne L_af_1
	li r3, 0x0
	b L_af_2
	L_af_1:
	mr r30, r31
	li r28, 0x0
	b L_af_3
	L_af_4:
	lwz r27, 0x154(r30)
	li r29, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x8(r27)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	mr r3, r27
	b L_af_2
	L_af_7:
	addi r29, r29, 0x1
	addi r27, r27, 0x134
	L_af_5:
	lwz r0, 0x150(r30)
	cmpw r29, r0
	blt L_af_6
	addi r30, r30, 0x178
	addi r28, r28, 0x1
	L_af_3:
	lwz r0, 0x0(r31)
	cmpw r28, r0
	blt L_af_4
	li r3, 0x0
	L_af_2:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lbz r0, 0x0(r4)
	cmpwi r0, 0x7c
	beq L_af_1
	bl mapSearchDmdJointSub
	b L_af_2
	L_af_1:
	la r5, str_8041986C(r2)
	bl mapSearchDmdJointSub2
	L_af_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm MapFileJoint* mapSearchDmdJointSub2(MapFileJoint* joint, const char* name, const char* prefix) {
	nofralloc
	stwu r1, -0x720(r1)
	mflr r0
	stw r0, 0x724(r1)
	stmw r27, 0x70c(r1)
	mr r29, r3
	mr r30, r5
	mr r31, r4
	addi r3, r1, 0x608
	mr r4, r30
	bl strcpy
	lwz r4, 0x0(r29)
	addi r3, r1, 0x608
	bl strcat
	mr r4, r31
	addi r3, r1, 0x608
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_1
	mr r3, r29
	b L_af_2
	L_af_1:
	lwz r0, 0xc(r29)
	cmplwi r0, 0x0
	beq L_af_3
	addi r3, r1, 0x608
	la r4, str_8041986C(r2)
	bl strcat
	lwz r27, 0xc(r29)
	addi r3, r1, 0x508
	addi r4, r1, 0x608
	bl strcpy
	lwz r4, 0x0(r27)
	addi r3, r1, 0x508
	bl strcat
	mr r4, r31
	addi r3, r1, 0x508
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_4
	b L_af_5
	L_af_4:
	lwz r0, 0xc(r27)
	cmplwi r0, 0x0
	beq L_af_6
	addi r3, r1, 0x508
	la r4, str_8041986C(r2)
	bl strcat
	lwz r28, 0xc(r27)
	addi r3, r1, 0x308
	addi r4, r1, 0x508
	bl strcpy
	lwz r4, 0x0(r28)
	addi r3, r1, 0x308
	bl strcat
	mr r4, r31
	addi r3, r1, 0x308
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_8
	L_af_7:
	lwz r0, 0xc(r28)
	cmplwi r0, 0x0
	beq L_af_9
	addi r3, r1, 0x308
	la r4, str_8041986C(r2)
	bl strcat
	lwz r3, 0xc(r28)
	mr r4, r31
	addi r5, r1, 0x308
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_9
	mr r28, r3
	b L_af_8
	L_af_9:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_10
	mr r4, r31
	addi r5, r1, 0x508
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_10
	mr r28, r3
	b L_af_8
	L_af_10:
	li r28, 0x0
	L_af_8:
	cmplwi r28, 0x0
	beq L_af_6
	mr r27, r28
	b L_af_5
	L_af_6:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_11
	addi r3, r1, 0x208
	addi r4, r1, 0x608
	bl strcpy
	lwz r4, 0x0(r27)
	addi r3, r1, 0x208
	bl strcat
	mr r4, r31
	addi r3, r1, 0x208
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_12
	b L_af_13
	L_af_12:
	lwz r0, 0xc(r27)
	cmplwi r0, 0x0
	beq L_af_14
	addi r3, r1, 0x208
	la r4, str_8041986C(r2)
	bl strcat
	lwz r3, 0xc(r27)
	mr r4, r31
	addi r5, r1, 0x208
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_14
	mr r27, r3
	b L_af_13
	L_af_14:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	addi r5, r1, 0x608
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_15
	mr r27, r3
	b L_af_13
	L_af_15:
	li r27, 0x0
	L_af_13:
	cmplwi r27, 0x0
	beq L_af_11
	b L_af_5
	L_af_11:
	li r27, 0x0
	L_af_5:
	cmplwi r27, 0x0
	beq L_af_3
	mr r3, r27
	b L_af_2
	L_af_3:
	lwz r27, 0x10(r29)
	cmplwi r27, 0x0
	beq L_af_16
	mr r4, r30
	addi r3, r1, 0x408
	bl strcpy
	lwz r4, 0x0(r27)
	addi r3, r1, 0x408
	bl strcat
	mr r4, r31
	addi r3, r1, 0x408
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_17
	b L_af_18
	L_af_17:
	lwz r0, 0xc(r27)
	cmplwi r0, 0x0
	beq L_af_19
	addi r3, r1, 0x408
	la r4, str_8041986C(r2)
	bl strcat
	lwz r28, 0xc(r27)
	addi r3, r1, 0x108
	addi r4, r1, 0x408
	bl strcpy
	lwz r4, 0x0(r28)
	addi r3, r1, 0x108
	bl strcat
	mr r4, r31
	addi r3, r1, 0x108
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_20
	b L_af_21
	L_af_20:
	lwz r0, 0xc(r28)
	cmplwi r0, 0x0
	beq L_af_22
	addi r3, r1, 0x108
	la r4, str_8041986C(r2)
	bl strcat
	lwz r3, 0xc(r28)
	mr r4, r31
	addi r5, r1, 0x108
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_22
	mr r28, r3
	b L_af_21
	L_af_22:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_23
	mr r4, r31
	addi r5, r1, 0x408
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_23
	mr r28, r3
	b L_af_21
	L_af_23:
	li r28, 0x0
	L_af_21:
	cmplwi r28, 0x0
	beq L_af_19
	mr r27, r28
	b L_af_18
	L_af_19:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_24
	mr r4, r30
	addi r3, r1, 0x8
	bl strcpy
	lwz r4, 0x0(r27)
	addi r3, r1, 0x8
	bl strcat
	mr r4, r31
	addi r3, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_25
	b L_af_26
	L_af_25:
	lwz r0, 0xc(r27)
	cmplwi r0, 0x0
	beq L_af_27
	addi r3, r1, 0x8
	la r4, str_8041986C(r2)
	bl strcat
	lwz r3, 0xc(r27)
	mr r4, r31
	addi r5, r1, 0x8
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_27
	mr r27, r3
	b L_af_26
	L_af_27:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_28
	mr r4, r31
	mr r5, r30
	bl mapSearchDmdJointSub2
	cmplwi r3, 0x0
	beq L_af_28
	mr r27, r3
	b L_af_26
	L_af_28:
	li r27, 0x0
	L_af_26:
	cmplwi r27, 0x0
	beq L_af_24
	b L_af_18
	L_af_24:
	li r27, 0x0
	L_af_18:
	cmplwi r27, 0x0
	beq L_af_16
	mr r3, r27
	b L_af_2
	L_af_16:
	li r3, 0x0
	L_af_2:
	lmw r27, 0x70c(r1)
	lwz r0, 0x724(r1)
	mtlr r0
	addi r1, r1, 0x720
	blr
}

asm MapFileJoint* mapSearchDmdJointSub(MapFileJoint* joint, const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r29, r3
	mr r30, r4
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_1
	mr r3, r29
	b L_af_2
	L_af_1:
	lwz r31, 0xc(r29)
	cmplwi r31, 0x0
	beq L_af_3
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_4
	b L_af_5
	L_af_4:
	lwz r27, 0xc(r31)
	cmplwi r27, 0x0
	beq L_af_6
	lwz r3, 0x0(r27)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_8
	L_af_7:
	lwz r28, 0xc(r27)
	cmplwi r28, 0x0
	beq L_af_9
	lwz r3, 0x0(r28)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_10
	b L_af_11
	L_af_10:
	lwz r3, 0xc(r28)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_12
	mr r28, r3
	b L_af_11
	L_af_12:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_13
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_13
	mr r28, r3
	b L_af_11
	L_af_13:
	li r28, 0x0
	L_af_11:
	cmplwi r28, 0x0
	beq L_af_9
	mr r27, r28
	b L_af_8
	L_af_9:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_14
	lwz r3, 0x0(r27)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_15
	b L_af_16
	L_af_15:
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_17
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_17
	mr r27, r3
	b L_af_16
	L_af_17:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_18
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_18
	mr r27, r3
	b L_af_16
	L_af_18:
	li r27, 0x0
	L_af_16:
	cmplwi r27, 0x0
	beq L_af_14
	b L_af_8
	L_af_14:
	li r27, 0x0
	L_af_8:
	cmplwi r27, 0x0
	beq L_af_6
	mr r31, r27
	b L_af_5
	L_af_6:
	lwz r31, 0x10(r31)
	cmplwi r31, 0x0
	beq L_af_19
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_20
	b L_af_21
	L_af_20:
	lwz r27, 0xc(r31)
	cmplwi r27, 0x0
	beq L_af_22
	lwz r3, 0x0(r27)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_23
	b L_af_24
	L_af_23:
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_25
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_25
	mr r27, r3
	b L_af_24
	L_af_25:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_26
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_26
	mr r27, r3
	b L_af_24
	L_af_26:
	li r27, 0x0
	L_af_24:
	cmplwi r27, 0x0
	beq L_af_22
	mr r31, r27
	b L_af_21
	L_af_22:
	lwz r31, 0x10(r31)
	cmplwi r31, 0x0
	beq L_af_27
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_28
	b L_af_29
	L_af_28:
	lwz r3, 0xc(r31)
	cmplwi r3, 0x0
	beq L_af_30
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_30
	mr r31, r3
	b L_af_29
	L_af_30:
	lwz r3, 0x10(r31)
	cmplwi r3, 0x0
	beq L_af_31
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_31
	mr r31, r3
	b L_af_29
	L_af_31:
	li r31, 0x0
	L_af_29:
	cmplwi r31, 0x0
	beq L_af_27
	b L_af_21
	L_af_27:
	li r31, 0x0
	L_af_21:
	cmplwi r31, 0x0
	beq L_af_19
	b L_af_5
	L_af_19:
	li r31, 0x0
	L_af_5:
	cmplwi r31, 0x0
	beq L_af_3
	mr r3, r31
	b L_af_2
	L_af_3:
	lwz r31, 0x10(r29)
	cmplwi r31, 0x0
	beq L_af_32
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_33
	b L_af_34
	L_af_33:
	lwz r28, 0xc(r31)
	cmplwi r28, 0x0
	beq L_af_35
	lwz r3, 0x0(r28)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_36
	b L_af_37
	L_af_36:
	lwz r27, 0xc(r28)
	cmplwi r27, 0x0
	beq L_af_38
	lwz r3, 0x0(r27)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_39
	b L_af_40
	L_af_39:
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_41
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_41
	mr r27, r3
	b L_af_40
	L_af_41:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_42
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_42
	mr r27, r3
	b L_af_40
	L_af_42:
	li r27, 0x0
	L_af_40:
	cmplwi r27, 0x0
	beq L_af_38
	mr r28, r27
	b L_af_37
	L_af_38:
	lwz r28, 0x10(r28)
	cmplwi r28, 0x0
	beq L_af_43
	lwz r3, 0x0(r28)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_44
	b L_af_45
	L_af_44:
	lwz r3, 0xc(r28)
	cmplwi r3, 0x0
	beq L_af_46
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_46
	mr r28, r3
	b L_af_45
	L_af_46:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_47
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_47
	mr r28, r3
	b L_af_45
	L_af_47:
	li r28, 0x0
	L_af_45:
	cmplwi r28, 0x0
	beq L_af_43
	b L_af_37
	L_af_43:
	li r28, 0x0
	L_af_37:
	cmplwi r28, 0x0
	beq L_af_35
	mr r31, r28
	b L_af_34
	L_af_35:
	lwz r31, 0x10(r31)
	cmplwi r31, 0x0
	beq L_af_48
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_49
	b L_af_50
	L_af_49:
	lwz r27, 0xc(r31)
	cmplwi r27, 0x0
	beq L_af_51
	lwz r3, 0x0(r27)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_52
	b L_af_53
	L_af_52:
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_54
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_54
	mr r27, r3
	b L_af_53
	L_af_54:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_55
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_55
	mr r27, r3
	b L_af_53
	L_af_55:
	li r27, 0x0
	L_af_53:
	cmplwi r27, 0x0
	beq L_af_51
	mr r31, r27
	b L_af_50
	L_af_51:
	lwz r31, 0x10(r31)
	cmplwi r31, 0x0
	beq L_af_56
	lwz r3, 0x0(r31)
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_57
	b L_af_58
	L_af_57:
	lwz r3, 0xc(r31)
	cmplwi r3, 0x0
	beq L_af_59
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_59
	mr r31, r3
	b L_af_58
	L_af_59:
	lwz r3, 0x10(r31)
	cmplwi r3, 0x0
	beq L_af_60
	mr r4, r30
	bl mapSearchDmdJointSub
	cmplwi r3, 0x0
	beq L_af_60
	mr r31, r3
	b L_af_58
	L_af_60:
	li r31, 0x0
	L_af_58:
	cmplwi r31, 0x0
	beq L_af_56
	b L_af_50
	L_af_56:
	li r31, 0x0
	L_af_50:
	cmplwi r31, 0x0
	beq L_af_48
	b L_af_34
	L_af_48:
	li r31, 0x0
	L_af_34:
	cmplwi r31, 0x0
	beq L_af_32
	mr r3, r31
	b L_af_2
	L_af_32:
	li r3, 0x0
	L_af_2:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r27, r4
	mr r26, r3
	lwz r0, activeGroup(r13)
	lwz r6, 0xc(r4)
	mulli r0, r0, 0x2f4
	lwz r5, mapWork(r13)
	lwz r4, 0x0(r6)
	lwz r3, 0x4(r6)
	lwz r28, 0x8(r27)
	add r31, r5, r0
	addi r29, r4, 0x4
	addi r30, r3, 0x4
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x3
	bl GXSetVtxDesc
	lha r0, 0xde(r26)
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	mulli r0, r0, 0x178
	li r6, 0x3
	add r7, r31, r0
	lwz r7, 0xa4(r7)
	lwz r0, 0x44(r7)
	clrlwi r7, r0, 24
	bl GXSetVtxAttrFmt
	mr r4, r29
	li r3, 0x9
	li r5, 0x6
	bl GXSetArray
	li r3, 0xa
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xa
	li r5, 0x0
	li r6, 0x1
	li r7, 0x6
	bl GXSetVtxAttrFmt
	mr r4, r30
	li r3, 0xa
	li r5, 0x3
	bl GXSetArray
	li r25, 0x0
	li r30, 0x0
	li r29, 0x1
	L_af_1:
	addi r0, r25, 0x2
	slw r0, r29, r0
	and. r0, r28, r0
	beq L_af_2
	li r3, 0xb
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lwz r4, 0xc(r27)
	addi r0, r30, 0xc
	li r3, 0xb
	li r5, 0x4
	lwzx r4, r4, r0
	addi r4, r4, 0x4
	bl GXSetArray
	addi r25, r25, 0x1
	addi r30, r30, 0x4
	cmpwi r25, 0x2
	blt L_af_1
	L_af_2:
	li r29, 0x0
	mr r30, r29
	L_af_3:
	addi r0, r29, 0x4
	li r3, 0x1
	slw r0, r3, r0
	and. r0, r28, r0
	beq L_af_4
	addi r3, r29, 0xd
	li r4, 0x3
	bl GXSetVtxDesc
	lha r5, 0xde(r26)
	addi r0, r30, 0x48
	addi r4, r29, 0xd
	li r3, 0x0
	mulli r7, r5, 0x178
	li r5, 0x1
	li r6, 0x3
	addi r7, r7, 0xa4
	lwzx r7, r31, r7
	lwzx r0, r7, r0
	clrlwi r7, r0, 24
	bl GXSetVtxAttrFmt
	lwz r4, 0xc(r27)
	addi r0, r30, 0x18
	addi r3, r29, 0xd
	li r5, 0x4
	lwzx r4, r4, r0
	addi r4, r4, 0x4
	bl GXSetArray
	addi r29, r29, 0x1
	addi r30, r30, 0x4
	cmpwi r29, 0x8
	blt L_af_3
	L_af_4:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapSetPolygon(MapObject* obj, MapFileMesh* mesh) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r27, r4
	mr r26, r3
	lwz r4, 0x8(r3)
	lis r3, culling@ha
	lwz r5, activeGroup(r13)
	addi r3, r3, culling@l
	lwz r4, 0x58(r4)
	lwz r8, 0xc(r27)
	mulli r6, r5, 0x2f4
	lbz r0, 0x1(r4)
	lwz r7, mapWork(r13)
	slwi r0, r0, 2
	lwz r5, 0x0(r8)
	lwz r4, 0x4(r8)
	add r31, r7, r6
	lwz r28, 0x14(r8)
	addi r29, r5, 0x4
	lwzx r3, r3, r0
	addi r30, r4, 0x4
	bl GXSetCullMode
	lha r0, 0xde(r26)
	mulli r0, r0, 0x178
	add r3, r31, r0
	lhz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 16, 16
	bne L_af_1
	bl GXClearVtxDesc
	lis r4, attr_fmt@ha
	li r3, 0x0
	addi r4, r4, attr_fmt@l
	bl GXSetVtxAttrFmtv
	li r3, 0x9
	li r4, 0x3
	bl GXSetVtxDesc
	mr r4, r29
	li r3, 0x9
	li r5, 0xc
	bl GXSetArray
	li r3, 0xa
	li r4, 0x3
	bl GXSetVtxDesc
	mr r4, r30
	li r3, 0xa
	li r5, 0xc
	bl GXSetArray
	li r3, 0xb
	li r4, 0x3
	bl GXSetVtxDesc
	lwz r4, 0xc(r27)
	li r3, 0xb
	li r5, 0x4
	lwz r4, 0xc(r4)
	addi r4, r4, 0x4
	bl GXSetArray
	li r25, 0x0
	li r26, 0x0
	b L_af_2
	L_af_3:
	addi r3, r25, 0xd
	li r4, 0x3
	bl GXSetVtxDesc
	lwz r4, 0xc(r27)
	addi r0, r26, 0x18
	addi r3, r25, 0xd
	li r5, 0x8
	lwzx r4, r4, r0
	addi r4, r4, 0x4
	bl GXSetArray
	addi r26, r26, 0x4
	addi r25, r25, 0x1
	L_af_2:
	cmpw r25, r28
	blt L_af_3
	mr r31, r27
	li r29, 0x0
	lis r26, 0xcc01
	b L_af_4
	L_af_5:
	lwz r30, 0x10(r31)
	li r3, 0x98
	li r4, 0x0
	lwz r0, 0x0(r30)
	clrlwi r5, r0, 16
	bl GXBegin
	mr r6, r30
	li r8, 0x0
	b L_af_6
	L_af_7:
	lha r0, 0x4(r6)
	addi r4, r6, 0x4
	cmpwi r28, 0x0
	mr r3, r28
	sth r0, -0x8000(r26)
	mr r5, r4
	lha r0, 0x6(r6)
	sth r0, -0x8000(r26)
	lha r0, 0x8(r6)
	sth r0, -0x8000(r26)
	ble L_af_8
	srwi. r0, r28, 2
	mtctr r0
	beq L_af_9
	L_af_10:
	lha r7, 0x8(r5)
	addi r4, r7, 0x1
	subfic r0, r7, -0x1
	or r4, r4, r0
	clrlwi r0, r7, 16
	srawi r4, r4, 31
	and r0, r0, r4
	sth r0, -0x8000(r26)
	lha r7, 0xa(r5)
	addi r4, r7, 0x1
	subfic r0, r7, -0x1
	or r4, r4, r0
	clrlwi r0, r7, 16
	srawi r4, r4, 31
	and r0, r0, r4
	sth r0, -0x8000(r26)
	lha r7, 0xc(r5)
	addi r4, r7, 0x1
	subfic r0, r7, -0x1
	or r4, r4, r0
	clrlwi r0, r7, 16
	srawi r4, r4, 31
	and r0, r0, r4
	sth r0, -0x8000(r26)
	lha r7, 0xe(r5)
	addi r5, r5, 0x8
	addi r4, r7, 0x1
	subfic r0, r7, -0x1
	or r4, r4, r0
	clrlwi r0, r7, 16
	srawi r4, r4, 31
	and r0, r0, r4
	sth r0, -0x8000(r26)
	bdnz L_af_10
	andi. r3, r3, 0x3
	beq L_af_8
	L_af_9:
	mtctr r3
	L_af_11:
	lha r7, 0x8(r5)
	addi r5, r5, 0x2
	addi r4, r7, 0x1
	subfic r0, r7, -0x1
	or r4, r4, r0
	clrlwi r0, r7, 16
	srawi r4, r4, 31
	and r0, r0, r4
	sth r0, -0x8000(r26)
	bdnz L_af_11
	L_af_8:
	addi r6, r6, 0x18
	addi r8, r8, 0x1
	L_af_6:
	lwz r0, 0x0(r30)
	cmpw r8, r0
	blt L_af_7
	addi r31, r31, 0x4
	addi r29, r29, 0x1
	L_af_4:
	lwz r0, 0x4(r27)
	cmpw r29, r0
	blt L_af_5
	b L_af_12
	L_af_1:
	lwz r28, 0x8(r27)
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x3
	bl GXSetVtxDesc
	lha r0, 0xde(r26)
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	mulli r0, r0, 0x178
	li r6, 0x3
	add r7, r31, r0
	lwz r7, 0xa4(r7)
	lwz r0, 0x44(r7)
	clrlwi r7, r0, 24
	bl GXSetVtxAttrFmt
	mr r4, r29
	li r3, 0x9
	li r5, 0x6
	bl GXSetArray
	li r3, 0xa
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xa
	li r5, 0x0
	li r6, 0x1
	li r7, 0x6
	bl GXSetVtxAttrFmt
	mr r4, r30
	li r3, 0xa
	li r5, 0x3
	bl GXSetArray
	li r25, 0x0
	li r29, 0x1
	mr r30, r25
	L_af_13:
	addi r0, r25, 0x2
	slw r0, r29, r0
	and. r0, r28, r0
	beq L_af_14
	li r3, 0xb
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lwz r4, 0xc(r27)
	addi r0, r30, 0xc
	li r3, 0xb
	li r5, 0x4
	lwzx r4, r4, r0
	addi r4, r4, 0x4
	bl GXSetArray
	addi r25, r25, 0x1
	addi r30, r30, 0x4
	cmpwi r25, 0x2
	blt L_af_13
	L_af_14:
	li r29, 0x0
	mr r30, r29
	L_af_15:
	addi r0, r29, 0x4
	li r3, 0x1
	slw r0, r3, r0
	and. r0, r28, r0
	beq L_af_16
	addi r3, r29, 0xd
	li r4, 0x3
	bl GXSetVtxDesc
	lha r5, 0xde(r26)
	addi r0, r30, 0x48
	addi r4, r29, 0xd
	li r3, 0x0
	mulli r7, r5, 0x178
	li r5, 0x1
	li r6, 0x3
	addi r7, r7, 0xa4
	lwzx r7, r31, r7
	lwzx r0, r7, r0
	clrlwi r7, r0, 24
	bl GXSetVtxAttrFmt
	lwz r4, 0xc(r27)
	addi r0, r30, 0x18
	addi r3, r29, 0xd
	li r5, 0x4
	lwzx r4, r4, r0
	addi r4, r4, 0x4
	bl GXSetArray
	addi r29, r29, 0x1
	addi r30, r30, 0x4
	cmpwi r29, 0x8
	blt L_af_15
	L_af_16:
	mr r26, r27
	li r28, 0x0
	b L_af_17
	L_af_18:
	lwz r3, 0x10(r26)
	lwz r4, 0x14(r26)
	bl GXCallDisplayList
	addi r26, r26, 0x8
	addi r28, r28, 0x1
	L_af_17:
	lwz r0, 0x4(r27)
	cmpw r28, r0
	blt L_af_18
	L_af_12:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapSetMaterialLight(s32 flags, Vec position) {
	nofralloc
	stwu r1, -0x160(r1)
	mflr r0
	stw r0, 0x164(r1)
	stmw r23, 0x13c(r1)
	mr r24, r3
	clrlwi. r25, r24, 31
	mr r23, r4
	li r28, 0x0
	li r26, 0x2
	lwz r3, dat_80419834(r2)
	lwz r0, dat_80419838(r2)
	stw r3, 0x28(r1)
	stw r0, 0x24(r1)
	beq L_af_1
	bl lightGetPaper
	stw r3, 0x44(r1)
	li r28, 0x1
	L_af_1:
	rlwinm. r27, r24, 0, 28, 28
	beq L_af_2
	bl lightGetPaperCraft
	slwi r0, r28, 2
	addi r4, r1, 0x44
	stwx r3, r4, r0
	addi r28, r28, 0x1
	L_af_2:
	rlwinm. r0, r24, 0, 27, 27
	beq L_af_3
	bl lightGetPaper
	slwi r0, r28, 2
	addi r4, r1, 0x44
	stwx r3, r4, r0
	addi r28, r28, 0x1
	L_af_3:
	rlwinm. r0, r24, 0, 30, 30
	beq L_af_4
	bl lightCheckCharaLight
	cmpwi r3, 0x0
	beq L_af_4
	cmpwi r28, 0x8
	bge L_af_4
	slwi r0, r28, 2
	addi r4, r1, 0x44
	mr r3, r23
	subfic r5, r28, 0x8
	add r4, r4, r0
	li r6, 0x80
	bl lightGetNearObj
	add r28, r28, r3
	L_af_4:
	andi. r0, r24, 0x19
	beq L_af_5
	cmpwi r28, 0x1
	bne L_af_6
	cmplwi r25, 0x0
	beq L_af_7
	lwz r0, paper_ambient(r13)
	stw r0, 0x24(r1)
	b L_af_5
	L_af_7:
	cmplwi r27, 0x0
	beq L_af_8
	lwz r0, paperCraft_ambient(r13)
	stw r0, 0x24(r1)
	b L_af_5
	L_af_8:
	lwz r0, dat_8041983c(r2)
	stw r0, 0x24(r1)
	b L_af_5
	L_af_6:
	mr r3, r23
	addi r4, r1, 0x44
	li r5, 0x8
	li r6, 0x80
	bl lightGetNearObj
	mr r28, r3
	L_af_5:
	lis r4, lightid_tbl@ha
	lis r3, vec3_802c1828@ha
	addi r29, r4, lightid_tbl@l
	addi r30, r1, 0x44
	addi r31, r3, vec3_802c1828@l
	li r27, 0x0
	li r25, 0x0
	b L_af_9
	L_af_10:
	lwz r4, 0x0(r31)
	lwz r3, 0x4(r31)
	lwz r0, 0x8(r31)
	stw r4, 0x2c(r1)
	lwz r23, 0x0(r30)
	stw r3, 0x30(r1)
	stw r0, 0x34(r1)
	lhz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 19, 19
	beq L_af_11
	bl camGetCurPtr
	addi r3, r3, 0x11c
	addi r4, r23, 0x24
	addi r5, r1, 0x38
	bl PSMTXMultVec
	lfs f1, 0x38(r1)
	addi r3, r1, 0xf4
	lfs f2, 0x3c(r1)
	lfs f3, 0x40(r1)
	bl GXInitLightPos
	lwz r5, 0x0(r30)
	addi r3, r1, 0xf4
	addi r4, r1, 0x1c
	lwz r0, 0x48(r5)
	stw r0, 0x1c(r1)
	bl GXInitLightColor
	lwz r4, 0x0(r30)
	lhz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 25, 25
	beq L_af_12
	lfs f2, float_0_80419850(r2)
	addi r3, r1, 0xf4
	lfs f1, 0x50(r4)
	fmr f3, f2
	lfs f4, float_1_80419860(r2)
	fmr f5, f2
	fmr f6, f2
	bl GXInitLightAttn
	b L_af_13
	L_af_12:
	lfs f2, float_0_80419850(r2)
	addi r3, r1, 0xf4
	lfs f1, 0x50(r4)
	fmr f3, f2
	lfs f4, 0x54(r4)
	lfs f5, 0x58(r4)
	lfs f6, 0x5c(r4)
	bl GXInitLightAttn
	li r26, 0x1
	L_af_13:
	lwz r4, 0x0(r29)
	addi r3, r1, 0xf4
	bl GXLoadLightObjImm
	b L_af_14
	L_af_11:
	rlwinm. r0, r3, 0, 18, 18
	beq L_af_15
	lfs f1, float_deg2rad_80419868(r2)
	addi r3, r1, 0xc4
	lfs f0, 0x30(r23)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r30)
	addi r3, r1, 0x94
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x79
	lfs f0, 0x34(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r30)
	addi r3, r1, 0x64
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x7a
	lfs f0, 0x38(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x94
	addi r3, r1, 0x64
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xc4
	addi r3, r1, 0x94
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x2c
	addi r3, r1, 0xc4
	mr r5, r4
	bl PSMTXMultVec
	addi r3, r1, 0x2c
	lfs f1, float_neg1p0486E06_80419870(r2)
	mr r4, r3
	bl PSVECScale
	lwz r3, 0x0(r30)
	addi r4, r1, 0x2c
	addi r5, r1, 0x38
	addi r3, r3, 0x24
	bl PSVECAdd
	bl camGetCurPtr
	addi r4, r1, 0x38
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXMultVec
	lfs f1, 0x38(r1)
	addi r3, r1, 0xf4
	lfs f2, 0x3c(r1)
	lfs f3, 0x40(r1)
	bl GXInitLightPos
	lwz r5, 0x0(r30)
	addi r3, r1, 0xf4
	addi r4, r1, 0x18
	lwz r0, 0x48(r5)
	stw r0, 0x18(r1)
	bl GXInitLightColor
	lwz r4, 0x0(r29)
	addi r3, r1, 0xf4
	bl GXLoadLightObjImm
	b L_af_14
	L_af_15:
	rlwinm. r0, r3, 0, 17, 17
	beq L_af_14
	bl camGetCurPtr
	addi r3, r3, 0x11c
	addi r4, r23, 0x24
	addi r5, r1, 0x38
	bl PSMTXMultVec
	lwz r5, 0x0(r30)
	addi r3, r1, 0xc4
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x78
	lfs f0, 0x30(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r30)
	addi r3, r1, 0x94
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x79
	lfs f0, 0x34(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r30)
	addi r3, r1, 0x64
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x7a
	lfs f0, 0x38(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x94
	addi r3, r1, 0x64
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xc4
	addi r3, r1, 0x94
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x2c
	addi r3, r1, 0xc4
	mr r5, r4
	bl PSMTXMultVec
	bl camGetCurPtr
	addi r4, r1, 0x2c
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXMultVecSR
	lfs f1, 0x38(r1)
	addi r3, r1, 0xf4
	lfs f2, 0x3c(r1)
	lfs f3, 0x40(r1)
	bl GXInitLightPos
	lfs f1, 0x2c(r1)
	addi r3, r1, 0xf4
	lfs f2, 0x30(r1)
	lfs f3, 0x34(r1)
	bl GXInitLightDir
	lwz r5, 0x0(r30)
	addi r3, r1, 0xf4
	lfs f0, float_0p5_80419854(r2)
	li r4, 0x4
	lfs f1, 0x4c(r5)
	fmuls f1, f1, f0
	bl GXInitLightSpot
	lfs f1, float_1000_80419874(r2)
	addi r3, r1, 0xf4
	lfs f2, float_0p5_80419854(r2)
	li r4, 0x0
	bl GXInitLightDistAttn
	lwz r5, 0x0(r30)
	addi r3, r1, 0xf4
	addi r4, r1, 0x14
	lwz r0, 0x48(r5)
	stw r0, 0x14(r1)
	bl GXInitLightColor
	lwz r4, 0x0(r29)
	addi r3, r1, 0xf4
	bl GXLoadLightObjImm
	li r26, 0x1
	L_af_14:
	lwz r0, 0x0(r29)
	addi r30, r30, 0x4
	addi r29, r29, 0x4
	addi r25, r25, 0x1
	or r27, r27, r0
	L_af_9:
	cmpw r25, r28
	blt L_af_10
	bl lightGetCharaAmbient
	cmplwi r3, 0x0
	beq L_af_16
	lwz r0, 0x48(r3)
	stw r0, 0x134(r1)
	b L_af_17
	L_af_16:
	lwz r0, 0x24(r1)
	stw r0, 0x134(r1)
	L_af_17:
	lfs f1, float_0_80419850(r2)
	addi r4, r1, 0x10
	lwz r5, 0x134(r1)
	li r3, 0x0
	lwz r0, 0x28(r1)
	fmr f2, f1
	fmr f3, f1
	stw r5, 0x20(r1)
	fmr f4, f1
	stw r0, 0x10(r1)
	bl GXSetFog
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, 0x20(r1)
	addi r4, r1, 0xc
	li r3, 0x4
	stw r0, 0xc(r1)
	bl GXSetChanAmbColor
	rlwinm. r0, r24, 0, 29, 29
	beq L_af_18
	lwz r0, 0x28(r1)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	neg r0, r28
	mr r7, r27
	andc r0, r0, r28
	mr r9, r26
	srwi r4, r0, 31
	li r3, 0x0
	li r5, 0x0
	li r6, 0x0
	li r8, 0x2
	bl GXSetChanCtrl
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	b L_af_19
	L_af_18:
	neg r0, r28
	mr r7, r27
	andc r0, r0, r28
	mr r9, r26
	srwi r4, r0, 31
	li r3, 0x0
	li r5, 0x0
	li r6, 0x1
	li r8, 0x2
	bl GXSetChanCtrl
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	L_af_19:
	lmw r23, 0x13c(r1)
	lwz r0, 0x164(r1)
	mtlr r0
	addi r1, r1, 0x160
	blr
}

asm void mapResetPaperAmbColor(void) {
	nofralloc
	lwz r0, dat_8041982c(r2)
	stw r0, paper_ambient(r13)
	blr
}

asm void mapSetPaperAmbColor(GXColor* color) {
	nofralloc
	lwz r0, 0x0(r3)
	stw r0, paper_ambient(r13)
	blr
}

asm void mapSetMaterial(MapObject* obj, void* material) {
	nofralloc
	stwu r1, -0x1b0(r1)
	mflr r0
	stw r0, 0x1b4(r1)
	stfd f31, 0x1a0(r1)
	psq_st f31, 0x1a8(r1), 0, 0
	stmw r19, 0x16c(r1)
	lwz r0, dat_80419828(r2)
	lis r5, vec3_802c16d8@ha
	mr r31, r4
	mr r30, r3
	stw r0, 0x1c(r1)
	addi r28, r5, vec3_802c16d8@l
	addi r4, r1, 0x5c
	li r25, 0x0
	li r23, 0x2
	bl mapSetLight
	mr r29, r3
	addi r27, r1, 0x5c
	addi r26, r28, 0x100
	li r24, 0x0
	li r22, 0x0
	b L_af_1
	L_af_2:
	lwz r4, 0x144(r28)
	lwz r3, 0x148(r28)
	lwz r0, 0x14c(r28)
	stw r4, 0x24(r1)
	lwz r19, 0x0(r27)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	lhz r3, 0x0(r19)
	rlwinm. r0, r3, 0, 19, 19
	beq L_af_3
	bl camGetCurPtr
	addi r3, r3, 0x11c
	addi r4, r19, 0x24
	addi r5, r1, 0x30
	bl PSMTXMultVec
	lfs f1, 0x30(r1)
	addi r3, r1, 0x10c
	lfs f2, 0x34(r1)
	lfs f3, 0x38(r1)
	bl GXInitLightPos
	lwz r5, 0x0(r27)
	addi r3, r1, 0x10c
	addi r4, r1, 0x18
	lwz r0, 0x48(r5)
	stw r0, 0x18(r1)
	bl GXInitLightColor
	lfs f2, float_0_80419850(r2)
	addi r3, r1, 0x10c
	lwz r4, 0x0(r27)
	fmr f3, f2
	lfs f1, 0x50(r4)
	lfs f4, 0x54(r4)
	lfs f5, 0x58(r4)
	lfs f6, 0x5c(r4)
	bl GXInitLightAttn
	lwz r4, 0x0(r26)
	addi r3, r1, 0x10c
	bl GXLoadLightObjImm
	li r23, 0x1
	b L_af_4
	L_af_3:
	rlwinm. r0, r3, 0, 18, 18
	beq L_af_5
	lfs f1, float_deg2rad_80419868(r2)
	addi r3, r1, 0xdc
	lfs f0, 0x30(r19)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r27)
	addi r3, r1, 0xac
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x79
	lfs f0, 0x34(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r27)
	addi r3, r1, 0x7c
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x7a
	lfs f0, 0x38(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0xac
	addi r3, r1, 0x7c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xdc
	addi r3, r1, 0xac
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x24
	addi r3, r1, 0xdc
	mr r5, r4
	bl PSMTXMultVec
	addi r3, r1, 0x24
	lfs f1, float_neg1p0486E06_80419870(r2)
	mr r4, r3
	bl PSVECScale
	lwz r3, 0x0(r27)
	addi r4, r1, 0x24
	addi r5, r1, 0x30
	addi r3, r3, 0x24
	bl PSVECAdd
	bl camGetCurPtr
	addi r4, r1, 0x30
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXMultVec
	lfs f1, 0x30(r1)
	addi r3, r1, 0x10c
	lfs f2, 0x34(r1)
	lfs f3, 0x38(r1)
	bl GXInitLightPos
	lwz r5, 0x0(r27)
	addi r3, r1, 0x10c
	addi r4, r1, 0x14
	lwz r0, 0x48(r5)
	stw r0, 0x14(r1)
	bl GXInitLightColor
	lfs f2, float_0_80419850(r2)
	addi r3, r1, 0x10c
	lwz r4, 0x0(r27)
	fmr f3, f2
	lfs f6, float_1_80419860(r2)
	fmr f4, f2
	lfs f1, 0x50(r4)
	fmr f5, f2
	bl GXInitLightAttn
	lwz r4, 0x0(r26)
	addi r3, r1, 0x10c
	bl GXLoadLightObjImm
	b L_af_4
	L_af_5:
	rlwinm. r0, r3, 0, 17, 17
	beq L_af_4
	bl camGetCurPtr
	addi r3, r3, 0x11c
	addi r4, r19, 0x24
	addi r5, r1, 0x30
	bl PSMTXMultVec
	lwz r5, 0x0(r27)
	addi r3, r1, 0xdc
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x78
	lfs f0, 0x30(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r27)
	addi r3, r1, 0xac
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x79
	lfs f0, 0x34(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lwz r5, 0x0(r27)
	addi r3, r1, 0x7c
	lfs f1, float_deg2rad_80419868(r2)
	li r4, 0x7a
	lfs f0, 0x38(r5)
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0xac
	addi r3, r1, 0x7c
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xdc
	addi r3, r1, 0xac
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0x24
	addi r3, r1, 0xdc
	mr r5, r4
	bl PSMTXMultVec
	bl camGetCurPtr
	addi r4, r1, 0x24
	addi r3, r3, 0x11c
	mr r5, r4
	bl PSMTXMultVecSR
	lfs f1, 0x30(r1)
	addi r3, r1, 0x10c
	lfs f2, 0x34(r1)
	lfs f3, 0x38(r1)
	bl GXInitLightPos
	lfs f1, 0x24(r1)
	addi r3, r1, 0x10c
	lfs f2, 0x28(r1)
	lfs f3, 0x2c(r1)
	bl GXInitLightDir
	lwz r5, 0x0(r27)
	addi r3, r1, 0x10c
	lfs f0, float_0p5_80419854(r2)
	li r4, 0x4
	lfs f1, 0x4c(r5)
	fmuls f1, f1, f0
	bl GXInitLightSpot
	lfs f1, float_1000_80419874(r2)
	addi r3, r1, 0x10c
	lfs f2, float_0p5_80419854(r2)
	li r4, 0x0
	bl GXInitLightDistAttn
	lwz r5, 0x0(r27)
	addi r3, r1, 0x10c
	addi r4, r1, 0x10
	lwz r0, 0x48(r5)
	stw r0, 0x10(r1)
	bl GXInitLightColor
	lwz r4, 0x0(r26)
	addi r3, r1, 0x10c
	bl GXLoadLightObjImm
	li r23, 0x1
	L_af_4:
	lwz r0, 0x0(r26)
	addi r27, r27, 0x4
	addi r26, r26, 0x4
	addi r22, r22, 0x1
	or r24, r24, r0
	L_af_1:
	cmpw r22, r29
	blt L_af_2
	bl lightGetAmbient
	cmplwi r3, 0x0
	beq L_af_6
	lwz r0, 0x48(r3)
	stw r0, 0x14c(r1)
	b L_af_7
	L_af_6:
	lwz r0, 0x1c(r1)
	stw r0, 0x14c(r1)
	L_af_7:
	lwz r0, 0x14c(r1)
	li r3, 0x1
	stw r0, 0x20(r1)
	bl GXSetNumChans
	lwz r0, 0x20(r1)
	addi r4, r1, 0xc
	li r3, 0x4
	stw r0, 0xc(r1)
	bl GXSetChanAmbColor
	lwz r0, 0x4(r31)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	lbz r0, 0x8(r31)
	cmpwi r0, 0x1
	beq L_af_8
	bge L_af_9
	cmpwi r0, 0x0
	bge L_af_10
	b L_af_9
	L_af_10:
	neg r0, r29
	mr r7, r24
	andc r0, r0, r29
	mr r9, r23
	srwi r4, r0, 31
	li r3, 0x0
	li r5, 0x0
	li r6, 0x0
	li r8, 0x2
	bl GXSetChanCtrl
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	b L_af_9
	L_af_8:
	neg r0, r29
	mr r7, r24
	andc r0, r0, r29
	mr r9, r23
	srwi r4, r0, 31
	li r3, 0x0
	li r5, 0x0
	li r6, 0x1
	li r8, 0x2
	bl GXSetChanCtrl
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	L_af_9:
	lbz r3, 0xb(r31)
	addi r24, r28, 0xec
	lfd f31, 0x2c8(r28)
	lis r23, 0x4330
	subi r27, r3, 0x1
	slwi r0, r27, 2
	add r26, r31, r0
	b L_af_11
	L_af_12:
	lwz r3, activeGroup(r13)
	li r28, 0x0
	lha r0, 0xde(r30)
	mulli r5, r3, 0x2f4
	lwz r22, 0xc(r26)
	lwz r6, mapWork(r13)
	lwz r4, 0x0(r22)
	mulli r3, r0, 0x178
	add r29, r6, r5
	lwz r20, 0x0(r4)
	addi r0, r3, 0x94
	lwzx r21, r29, r0
	mr r19, r21
	b L_af_13
	L_af_14:
	lwz r3, 0x4(r19)
	mr r4, r20
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_15
	b L_af_16
	L_af_15:
	addi r19, r19, 0x4
	addi r28, r28, 0x1
	L_af_13:
	lwz r0, 0x0(r21)
	cmpw r28, r0
	blt L_af_14
	li r28, -0x1
	L_af_16:
	lha r0, 0xde(r30)
	mr r4, r28
	mulli r3, r0, 0x178
	addi r0, r3, 0x84
	lwzx r3, r29, r0
	bl TEXGet
	mr r28, r3
	lwz r7, 0x0(r3)
	lbz r3, 0x21(r7)
	lbz r0, 0x22(r7)
	cmplw r3, r0
	bne L_af_17
	li r10, 0x0
	b L_af_18
	L_af_17:
	li r10, 0x1
	L_af_18:
	lbz r4, 0x8(r22)
	addi r3, r1, 0x3c
	lbz r0, 0x9(r22)
	slwi r8, r4, 2
	lwz r4, 0x8(r7)
	slwi r0, r0, 2
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	lwzx r8, r24, r8
	lwzx r9, r24, r0
	bl GXInitTexObj
	lwz r9, 0x0(r28)
	addi r3, r1, 0x3c
	stw r23, 0x150(r1)
	li r4, 0x1
	lbz r7, 0x21(r9)
	li r5, 0x1
	lbz r0, 0x22(r9)
	li r6, 0x0
	stw r7, 0x154(r1)
	li r8, 0x0
	lfs f3, 0x1c(r9)
	lfd f0, 0x150(r1)
	stw r0, 0x15c(r1)
	fsubs f1, f0, f31
	lbz r7, 0x20(r9)
	stw r23, 0x158(r1)
	lfd f0, 0x158(r1)
	fsubs f2, f0, f31
	bl GXInitTexObjLOD
	mr r4, r25
	addi r3, r1, 0x3c
	bl GXLoadTexObj
	addi r25, r25, 0x1
	subi r26, r26, 0x4
	subi r27, r27, 0x1
	L_af_11:
	cmpwi r27, 0x0
	bge L_af_12
	lwz r3, 0x110(r31)
	cmplwi r3, 0x0
	beq L_af_19
	lbz r4, 0x0(r3)
	b L_af_20
	L_af_19:
	li r4, 0x0
	L_af_20:
	lbz r3, 0xb(r31)
	addi r6, r30, 0x1c
	lwz r5, 0x0(r30)
	bl mapSetMaterialTev
	psq_l f31, 0x1a8(r1), 0, 0
	lfd f31, 0x1a0(r1)
	lmw r19, 0x16c(r1)
	lwz r0, 0x1b4(r1)
	mtlr r0
	addi r1, r1, 0x1b0
	blr
}

asm void mapSetTextureMatrix(MapMaterial* mat) {
	nofralloc
	stwu r1, -0x190(r1)
	mflr r0
	stw r0, 0x194(r1)
	stfd f31, 0x180(r1)
	psq_st f31, 0x188(r1), 0, 0
	stfd f30, 0x170(r1)
	psq_st f30, 0x178(r1), 0, 0
	stfd f29, 0x160(r1)
	psq_st f29, 0x168(r1), 0, 0
	stfd f28, 0x150(r1)
	psq_st f28, 0x158(r1), 0, 0
	stfd f27, 0x140(r1)
	psq_st f27, 0x148(r1), 0, 0
	stfd f26, 0x130(r1)
	psq_st f26, 0x138(r1), 0, 0
	stfd f25, 0x120(r1)
	psq_st f25, 0x128(r1), 0, 0
	stfd f24, 0x110(r1)
	psq_st f24, 0x118(r1), 0, 0
	stmw r26, 0xf8(r1)
	mr r26, r3
	lis r3, texmtx_tbl@ha
	lbz r4, 0xb(r26)
	addi r0, r3, texmtx_tbl@l
	lfs f31, float_1_80419860(r2)
	li r29, 0x0
	subi r27, r4, 0x1
	li r28, 0x0
	mulli r4, r27, 0x1c
	slwi r3, r27, 2
	add r31, r26, r4
	add r30, r0, r3
	b L_af_1
	L_af_2:
	lfs f5, 0x34(r31)
	lfs f1, 0x3c(r31)
	lfs f6, 0x38(r31)
	fmr f29, f5
	lfs f0, 0x30(r31)
	fcmpu cr0, f31, f5
	fmr f28, f6
	lfs f27, 0x2c(r31)
	fneg f30, f1
	fneg f26, f0
	bne L_af_3
	fcmpu cr0, f31, f6
	bne L_af_3
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f0, f27
	bne L_af_3
	fcmpu cr0, f0, f26
	bne L_af_3
	fcmpu cr0, f0, f30
	beq L_af_4
	L_af_3:
	lfs f3, float_0_80419850(r2)
	fcmpu cr0, f30, f3
	beq L_af_5
	lfs f4, float_0p5_80419854(r2)
	addi r3, r1, 0xc8
	lfs f2, 0x40(r31)
	lfs f1, 0x44(r31)
	lfs f0, float_1_80419860(r2)
	fmuls f2, f4, f2
	fnmsubs f0, f4, f1, f0
	fmuls f25, f2, f5
	fmuls f24, f0, f6
	fmr f1, f25
	fmr f2, f24
	bl PSMTXTrans
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x38
	li r4, 0x7a
	fmuls f1, f0, f30
	bl PSMTXRotRad
	fneg f1, f25
	lfs f3, float_0_80419850(r2)
	fneg f2, f24
	addi r3, r1, 0x98
	bl PSMTXTrans
	addi r4, r1, 0x38
	addi r3, r1, 0xc8
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x38
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	L_af_5:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f29, f0
	bne L_af_6
	fcmpu cr0, f28, f0
	beq L_af_7
	L_af_6:
	fmr f1, f29
	lfs f3, float_1_80419860(r2)
	fmr f2, f28
	addi r3, r1, 0x8
	bl PSMTXScale
	L_af_7:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f27, f0
	bne L_af_8
	fcmpu cr0, f26, f0
	beq L_af_9
	L_af_8:
	fmr f1, f27
	lfs f3, float_0_80419850(r2)
	fmr f2, f26
	addi r3, r1, 0x68
	bl PSMTXTrans
	L_af_9:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f30, f0
	beq L_af_10
	fcmpu cr0, f29, f0
	bne L_af_11
	fcmpu cr0, f28, f0
	beq L_af_12
	L_af_11:
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	addi r5, r1, 0xc8
	bl PSMTXConcat
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f27, f0
	bne L_af_13
	fcmpu cr0, f26, f0
	beq L_af_14
	L_af_13:
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	mr r5, r3
	bl PSMTXConcat
	b L_af_14
	L_af_12:
	fcmpu cr0, f27, f0
	bne L_af_15
	fcmpu cr0, f26, f0
	beq L_af_16
	L_af_15:
	addi r3, r1, 0x38
	addi r4, r1, 0x68
	addi r5, r1, 0xc8
	bl PSMTXConcat
	b L_af_14
	L_af_16:
	addi r3, r1, 0x38
	addi r4, r1, 0xc8
	bl PSMTXCopy
	b L_af_14
	L_af_10:
	fcmpu cr0, f29, f0
	bne L_af_17
	fcmpu cr0, f28, f0
	beq L_af_18
	L_af_17:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f27, f0
	bne L_af_19
	fcmpu cr0, f26, f0
	beq L_af_20
	L_af_19:
	addi r3, r1, 0x8
	addi r4, r1, 0x68
	addi r5, r1, 0xc8
	bl PSMTXConcat
	b L_af_14
	L_af_20:
	addi r3, r1, 0x8
	addi r4, r1, 0xc8
	bl PSMTXCopy
	b L_af_14
	L_af_18:
	fcmpu cr0, f27, f0
	bne L_af_21
	fcmpu cr0, f26, f0
	beq L_af_14
	L_af_21:
	addi r3, r1, 0x68
	addi r4, r1, 0xc8
	bl PSMTXCopy
	L_af_14:
	lwz r4, 0x0(r30)
	addi r3, r1, 0xc8
	li r5, 0x1
	bl GXLoadTexMtxImm
	lbz r5, 0xb(r26)
	mr r3, r29
	lwz r6, 0x0(r30)
	li r4, 0x1
	addi r0, r5, 0x3
	li r7, 0x0
	subf r5, r28, r0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_af_22
	L_af_4:
	lbz r5, 0xb(r26)
	mr r3, r29
	li r4, 0x1
	li r6, 0x3c
	addi r0, r5, 0x3
	li r7, 0x0
	subf r5, r28, r0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	L_af_22:
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	subi r31, r31, 0x1c
	subi r30, r30, 0x4
	subi r27, r27, 0x1
	L_af_1:
	cmpwi r27, 0x0
	bge L_af_2
	psq_l f31, 0x188(r1), 0, 0
	lfd f31, 0x180(r1)
	psq_l f30, 0x178(r1), 0, 0
	lfd f30, 0x170(r1)
	psq_l f29, 0x168(r1), 0, 0
	lfd f29, 0x160(r1)
	psq_l f28, 0x158(r1), 0, 0
	lfd f28, 0x150(r1)
	psq_l f27, 0x148(r1), 0, 0
	lfd f27, 0x140(r1)
	psq_l f26, 0x138(r1), 0, 0
	lfd f26, 0x130(r1)
	psq_l f25, 0x128(r1), 0, 0
	lfd f25, 0x120(r1)
	psq_l f24, 0x118(r1), 0, 0
	lfd f24, 0x110(r1)
	lmw r26, 0xf8(r1)
	lwz r0, 0x194(r1)
	mtlr r0
	addi r1, r1, 0x190
	blr
}

asm void mapSetMaterialFog(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl camGetCurPtr
	lwz r0, activeGroup(r13)
	mr r5, r3
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r6, r3, r0
	lhz r0, 0x4(r6)
	clrlwi. r0, r0, 31
	beq L_af_1
	lwz r0, 0x34(r6)
	la r3, fog_type(r13)
	addi r4, r1, 0xc
	stw r0, 0xc(r1)
	lwz r0, 0x28(r6)
	lfs f1, 0x2c(r6)
	slwi r0, r0, 2
	lfs f2, 0x30(r6)
	lwzx r3, r3, r0
	lfs f3, 0x30(r5)
	lfs f4, 0x34(r5)
	bl GXSetFog
	b L_af_2
	L_af_1:
	lfs f1, float_0_80419850(r2)
	addi r4, r1, 0x8
	lwz r0, dat_80419820(r2)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stw r0, 0x8(r1)
	fmr f4, f1
	bl GXSetFog
	L_af_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	rlwinm. r0, r3, 0, 25, 25
	stw r31, 0x1c(r1)
	lwz r7, activeGroup(r13)
	lwz r6, dat_8041981c(r2)
	mulli r0, r7, 0x2f4
	lwz r7, mapWork(r13)
	stw r6, 0xc(r1)
	add r6, r7, r0
	beq L_af_1
	lbz r8, 0xc(r1)
	lis r7, 0x8081
	lbz r0, 0x0(r4)
	subi r31, r7, 0x7f7f
	lbz r11, 0xd(r1)
	mullw r12, r8, r0
	lbz r10, 0x1(r4)
	lbz r8, 0x2(r4)
	lbz r0, 0x3(r4)
	lbz r7, 0xf(r1)
	lbz r9, 0xe(r1)
	mullw r0, r7, r0
	mulhw r7, r31, r12
	mullw r4, r11, r10
	add r7, r7, r12
	srawi r10, r7, 7
	mullw r8, r9, r8
	srwi r11, r10, 31
	add r10, r10, r11
	stb r10, 0xc(r1)
	mulhw r9, r31, r4
	mulhw r7, r31, r8
	add r4, r9, r4
	srawi r9, r4, 7
	add r7, r7, r8
	srwi r8, r9, 31
	mulhw r4, r31, r0
	add r9, r9, r8
	srawi r7, r7, 7
	stb r9, 0xd(r1)
	srwi r8, r7, 31
	add r0, r4, r0
	srawi r0, r0, 7
	add r7, r7, r8
	srwi r4, r0, 31
	stb r7, 0xe(r1)
	add r0, r0, r4
	stb r0, 0xf(r1)
	L_af_1:
	lbz r5, 0x0(r5)
	cmplwi r5, 0xff
	beq L_af_2
	lbz r0, 0xf(r1)
	lis r4, 0x8081
	subi r4, r4, 0x7f7f
	mullw r0, r0, r5
	mulhw r4, r4, r0
	add r0, r4, r0
	srawi r0, r0, 7
	srwi r4, r0, 31
	add r0, r0, r4
	stb r0, 0xf(r1)
	L_af_2:
	lhz r0, 0x4(r6)
	rlwinm. r4, r0, 0, 30, 30
	beq L_af_3
	rlwinm. r4, r3, 0, 20, 20
	bne L_af_3
	lbz r7, 0xc(r1)
	lis r4, 0x8081
	lbz r5, 0x16(r6)
	subi r12, r4, 0x7f7f
	lbz r10, 0xd(r1)
	mullw r11, r7, r5
	lbz r9, 0x17(r6)
	lbz r8, 0xe(r1)
	lbz r7, 0x18(r6)
	lbz r5, 0xf(r1)
	lbz r4, 0x19(r6)
	mullw r7, r8, r7
	mulhw r8, r12, r11
	mullw r9, r10, r9
	add r8, r8, r11
	srawi r10, r8, 7
	mullw r4, r5, r4
	srwi r11, r10, 31
	add r10, r10, r11
	stb r10, 0xc(r1)
	mulhw r5, r12, r9
	mulhw r8, r12, r7
	add r5, r5, r9
	srawi r9, r5, 7
	add r7, r8, r7
	mulhw r5, r12, r4
	srwi r8, r9, 31
	srawi r7, r7, 7
	add r9, r9, r8
	srwi r8, r7, 31
	stb r9, 0xd(r1)
	add r4, r5, r4
	add r7, r7, r8
	srawi r4, r4, 7
	stb r7, 0xe(r1)
	srwi r5, r4, 31
	add r4, r4, r5
	stb r4, 0xf(r1)
	L_af_3:
	rlwinm. r4, r0, 0, 29, 29
	beq L_af_4
	rlwinm. r4, r3, 0, 19, 19
	bne L_af_4
	lbz r7, 0xc(r1)
	lis r4, 0x8081
	lbz r5, 0x1a(r6)
	subi r12, r4, 0x7f7f
	lbz r10, 0xd(r1)
	mullw r11, r7, r5
	lbz r9, 0x1b(r6)
	lbz r8, 0xe(r1)
	lbz r7, 0x1c(r6)
	lbz r5, 0xf(r1)
	lbz r4, 0x1d(r6)
	mullw r7, r8, r7
	mulhw r8, r12, r11
	mullw r9, r10, r9
	add r8, r8, r11
	srawi r10, r8, 7
	mullw r4, r5, r4
	srwi r11, r10, 31
	add r10, r10, r11
	stb r10, 0xc(r1)
	mulhw r5, r12, r9
	mulhw r8, r12, r7
	add r5, r5, r9
	srawi r9, r5, 7
	add r7, r8, r7
	mulhw r5, r12, r4
	srwi r8, r9, 31
	srawi r7, r7, 7
	add r9, r9, r8
	srwi r8, r7, 31
	stb r9, 0xd(r1)
	add r4, r5, r4
	add r7, r7, r8
	srawi r4, r4, 7
	stb r7, 0xe(r1)
	srwi r5, r4, 31
	add r4, r4, r5
	stb r4, 0xf(r1)
	L_af_4:
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_5
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_5
	lbz r4, 0xc(r1)
	lis r3, 0x8081
	lbz r0, 0x1e(r6)
	subi r10, r3, 0x7f7f
	lbz r8, 0xd(r1)
	mullw r9, r4, r0
	lbz r7, 0x1f(r6)
	lbz r4, 0x20(r6)
	lbz r0, 0x21(r6)
	lbz r5, 0xe(r1)
	lbz r3, 0xf(r1)
	mullw r4, r5, r4
	mulhw r5, r10, r9
	mullw r6, r8, r7
	add r5, r5, r9
	srawi r7, r5, 7
	mullw r0, r3, r0
	srwi r8, r7, 31
	add r7, r7, r8
	stb r7, 0xc(r1)
	mulhw r3, r10, r6
	mulhw r5, r10, r4
	add r3, r3, r6
	srawi r6, r3, 7
	add r4, r5, r4
	mulhw r3, r10, r0
	srwi r5, r6, 31
	srawi r4, r4, 7
	add r6, r6, r5
	srwi r5, r4, 31
	stb r6, 0xd(r1)
	add r0, r3, r0
	add r4, r4, r5
	srawi r0, r0, 7
	stb r4, 0xe(r1)
	srwi r3, r0, 31
	add r0, r0, r3
	stb r0, 0xf(r1)
	L_af_5:
	lwz r0, 0xc(r1)
	addi r4, r1, 0x8
	li r3, 0x0
	stw r0, 0x8(r1)
	bl GXSetTevKColor
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx) {
	nofralloc
	stwu r1, -0x290(r1)
	mflr r0
	cmpwi r3, 0x0
	lis r7, vec3_802c16d8@ha
	stw r0, 0x294(r1)
	stmw r19, 0x25c(r1)
	mr r29, r4
	mr r30, r5
	mr r31, r6
	mr r27, r3
	mr r26, r3
	addi r28, r7, vec3_802c16d8@l
	li r24, 0x0
	ble L_af_1
	cmplwi r29, 0xc
	bgt L_af_2
	lis r3, jumptable_803033E0@ha
	slwi r0, r29, 2
	addi r3, r3, jumptable_803033E0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_af_3:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x1
	b L_af_4
	L_af_5:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x8
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_6:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x0
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_7:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x0
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_8:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0xf
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x7
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_9:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0x0
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x0
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0x8
	li r5, 0x0
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_10:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x2
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x2
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0x2
	li r5, 0x2
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0x2
	li r5, 0x4
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x1
	li r5, 0x2
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x3
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x3
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x3
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x3
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x3
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x3
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x4
	b L_af_4
	L_af_11:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x8
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x7
	li r5, 0x4
	li r6, 0x0
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_12:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x8
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x7
	li r6, 0x4
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_13:
	lwz r3, gp(r13)
	lis r0, 0x4330
	lwz r4, unk_80422f88(r2)
	lwz r3, 0x1c(r3)
	stw r0, 0x240(r1)
	slwi r0, r3, 1
	lfd f2, 0x2c8(r28)
	stw r0, 0x244(r1)
	lfs f3, float_6p2832_80419878(r2)
	lfd f1, 0x240(r1)
	lfs f0, float_360_8041987c(r2)
	fsubs f1, f1, f2
	stw r4, 0x44(r1)
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl sin
	frsp f1, f1
	lfs f0, float_127_80419880(r2)
	addi r4, r1, 0x48
	li r3, 0x1
	fmadds f0, f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x248(r1)
	lwz r0, 0x24c(r1)
	stb r0, 0x45(r1)
	lwz r0, 0x44(r1)
	stw r0, 0x48(r1)
	bl GXSetTevColor
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xa
	li r6, 0x8
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x1
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x1
	b L_af_4
	L_af_14:
	lis r3, queen_uv@ha
	lfs f3, g5_scrl_uv_s1622(r13)
	lfsu f0, queen_uv@l(r3)
	la r4, g5_scrl_uv_s1622(r13)
	lfs f2, float_100_80419884(r2)
	fadds f0, f3, f0
	lfs f1, float_neg100_80419888(r2)
	stfs f0, g5_scrl_uv_s1622(r13)
	lfs f0, g5_scrl_uv_s1622(r13)
	fcmpo cr0, f0, f2
	ble L_af_15
	fsubs f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_15:
	lfs f0, 0x0(r4)
	fcmpo cr0, f0, f1
	bge L_af_16
	fadds f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_16:
	lfs f3, 0x4(r4)
	lfsu f0, 0x4(r3)
	fadds f0, f3, f0
	stfs f0, 0x4(r4)
	lfsu f0, 0x4(r4)
	fcmpo cr0, f0, f2
	ble L_af_17
	fsubs f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_17:
	lfs f0, 0x0(r4)
	fcmpo cr0, f0, f1
	bge L_af_18
	fadds f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_18:
	lfs f3, 0x4(r4)
	lfsu f0, 0x4(r3)
	fadds f0, f3, f0
	stfs f0, 0x4(r4)
	lfsu f0, 0x4(r4)
	fcmpo cr0, f0, f2
	ble L_af_19
	fsubs f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_19:
	lfs f0, 0x0(r4)
	fcmpo cr0, f0, f1
	bge L_af_20
	fadds f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_20:
	lfs f3, 0x4(r4)
	lfs f0, 0x4(r3)
	fadds f0, f3, f0
	stfs f0, 0x4(r4)
	lfsu f0, 0x4(r4)
	fcmpo cr0, f0, f2
	ble L_af_21
	fsubs f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_21:
	lfs f0, 0x0(r4)
	fcmpo cr0, f0, f1
	bge L_af_22
	fadds f0, f0, f2
	stfs f0, 0x0(r4)
	L_af_22:
	la r3, g5_scrl_uv_s1622(r13)
	lfs f1, g5_scrl_uv_s1622(r13)
	lfs f2, 0x4(r3)
	addi r3, r1, 0x20c
	lfs f3, float_0_80419850(r2)
	bl PSMTXTrans
	addi r3, r1, 0x20c
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	la r4, g5_scrl_uv_s1622(r13)
	lfs f3, float_0_80419850(r2)
	lfs f1, 0x8(r4)
	addi r3, r1, 0x20c
	lfs f2, 0xc(r4)
	bl PSMTXTrans
	addi r3, r1, 0x20c
	li r4, 0x21
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x1
	li r4, 0x1
	li r5, 0x5
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x1
	li r4, 0x1
	li r5, 0x1
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x8
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x7
	li r6, 0x4
	li r7, 0x4
	bl GXSetTevAlphaIn
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r3, 0x2
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x2
	li r4, 0xf
	li r5, 0x0
	li r6, 0xa
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x2
	li r4, 0x7
	li r5, 0x0
	li r6, 0x5
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x2
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x3
	b L_af_4
	L_af_2:
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xa
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x5
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x1
	b L_af_4
	L_af_1:
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xa
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	li r25, 0x1
	L_af_4:
	rlwinm. r0, r30, 0, 3, 3
	bne L_af_23
	mr r3, r25
	li r4, 0xc
	bl GXSetTevKColorSel
	mr r3, r25
	li r4, 0x1c
	bl GXSetTevKAlphaSel
	mr r3, r25
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0xf
	li r5, 0x0
	li r6, 0xe
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x7
	li r5, 0x0
	li r6, 0x6
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r25, r25, 0x1
	L_af_23:
	rlwinm. r0, r30, 0, 29, 29
	beq L_af_24
	bl shadowGetCharShadowProjection
	cmpwi r3, 0x0
	beq L_af_24
	bl shadowGetCharShadowTexObj
	cmplwi r3, 0x0
	beq L_af_24
	bl shadowGetCharShadowColor
	stw r3, 0x58(r1)
	bl shadowGetCharShadowProjTexMtx
	mr r4, r31
	addi r5, r1, 0x1dc
	bl PSMTXConcat
	slwi r20, r27, 2
	addi r21, r28, 0x98
	lwzx r6, r21, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r21, r20
	addi r3, r1, 0x1dc
	li r5, 0x0
	bl GXLoadTexMtxImm
	bl shadowGetCharShadowTexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0xe
	li r6, 0x8
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	lwz r0, 0x58(r1)
	addi r4, r1, 0x40
	li r3, 0x1
	stw r0, 0x40(r1)
	bl GXSetTevKColor
	mr r3, r25
	li r4, 0xd
	bl GXSetTevKColorSel
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	L_af_24:
	rlwinm. r0, r30, 0, 21, 21
	beq L_af_25
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	mr r4, r31
	addi r5, r1, 0x1ac
	la r3, projMtx(r13)
	bl PSMTXConcat
	slwi r20, r27, 2
	addi r21, r28, 0x98
	lwzx r6, r21, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwzx r4, r21, r20
	addi r3, r1, 0x1ac
	li r5, 0x0
	bl GXLoadTexMtxImm
	lwz r4, projTexImgRef(r13)
	la r3, projTexObj(r13)
	bl smartTexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x1
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x4
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x4
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x3
	li r5, 0x3
	bl GXSetTevSwapMode
	li r3, 0x3
	li r4, 0x0
	li r5, 0x1
	li r6, 0x2
	li r7, 0x0
	bl GXSetTevSwapModeTable
	lwz r0, dat_80419800(r2)
	addi r4, r1, 0x3c
	li r3, 0x2
	stw r0, 0x3c(r1)
	bl GXSetTevColor
	addi r20, r25, 0x1
	li r4, 0xff
	mr r3, r20
	li r5, 0xff
	li r6, 0xff
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	bl GXSetTevOrder
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r20
	li r4, 0x2
	li r5, 0x0
	li r6, 0x1
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r20
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x1
	bl GXSetTevAlphaIn
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r25, r25, 0x2
	L_af_25:
	rlwinm. r0, r30, 0, 15, 15
	beq L_af_26
	bl shadowGetDepthShadowTexObj
	cmplwi r3, 0x0
	beq L_af_26
	bl shadowGetDepthShadowTexObj
	mr r23, r3
	bl shadowGetDepthShadowDepthMtx
	mr r22, r3
	bl shadowGetDepthShadowProjTexMtx
	mr r21, r3
	bl shadowGetDepthShadowColor
	stw r3, 0x54(r1)
	bl shadowGetDepthShadowConfig
	lwz r0, 0x3c(r3)
	cmpwi r0, 0x3
	beq L_af_27
	bge L_af_28
	cmpwi r0, 0x1
	beq L_af_29
	bge L_af_30
	cmpwi r0, 0x0
	bge L_af_31
	b L_af_26
	L_af_28:
	cmpwi r0, 0x5
	beq L_af_32
	bge L_af_26
	b L_af_33
	L_af_31:
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r20, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp8TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r20
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x1
	addi r22, r26, 0x1
	addi r27, r27, 0x1
	li r6, 0xff
	mr r3, r19
	mr r4, r22
	mr r5, r27
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x0
	li r5, 0x8
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r20, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r20
	mr r3, r22
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r23
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r21
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r20
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x2
	li r4, 0xff
	mr r3, r19
	li r5, 0xff
	li r6, 0xff
	addi r27, r27, 0x1
	addi r26, r26, 0x2
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0xf
	li r5, 0xe
	li r6, 0x0
	li r7, 0x2
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	lwz r0, 0x54(r1)
	addi r4, r1, 0x38
	li r3, 0x1
	stw r0, 0x38(r1)
	bl GXSetTevKColor
	mr r3, r19
	li r4, 0xd
	bl GXSetTevKColorSel
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x1
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r25, r25, 0x3
	b L_af_26
	L_af_29:
	lwz r0, dat_80419804(r2)
	addi r4, r1, 0x34
	li r3, 0x2
	stw r0, 0x34(r1)
	bl GXSetTevColor
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0x8
	li r6, 0x4
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r20, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp8TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r20
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	b L_af_26
	L_af_30:
	lwz r0, dat_80419808(r2)
	addi r4, r1, 0x30
	li r3, 0x2
	stw r0, 0x30(r1)
	bl GXSetTevColor
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0x8
	li r6, 0x4
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r20, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r23
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r21
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r20
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	b L_af_26
	L_af_27:
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x3
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	li r3, 0x2
	li r4, 0x3
	li r5, 0x1
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x1
	bl GXSetTevSwapMode
	slwi r20, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r20
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp16TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r20
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x1
	addi r20, r26, 0x1
	addi r27, r27, 0x1
	li r6, 0xff
	mr r3, r19
	mr r4, r20
	mr r5, r27
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x0
	li r5, 0x8
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0xa
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x2
	bl GXSetTevSwapMode
	slwi r22, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r22
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r23
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r21
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r22
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x2
	li r4, 0xff
	mr r3, r19
	li r5, 0xff
	li r6, 0x4
	addi r27, r27, 0x1
	addi r26, r26, 0x2
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0xf
	li r5, 0xe
	li r6, 0x0
	li r7, 0x2
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	lwz r0, 0x54(r1)
	addi r4, r1, 0x2c
	li r3, 0x1
	stw r0, 0x2c(r1)
	bl GXSetTevKColor
	mr r3, r19
	li r4, 0xd
	bl GXSetTevKColorSel
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x1
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r25, r25, 0x3
	b L_af_26
	L_af_33:
	lwz r0, dat_8041980c(r2)
	addi r4, r1, 0x28
	li r3, 0x2
	stw r0, 0x28(r1)
	bl GXSetTevColor
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0x8
	li r6, 0x4
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x1
	bl GXSetTevSwapMode
	slwi r21, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r21
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp16TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r21
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	b L_af_26
	L_af_32:
	lwz r0, dat_80419810(r2)
	addi r4, r1, 0x24
	li r3, 0x2
	stw r0, 0x24(r1)
	bl GXSetTevColor
	li r3, 0x1
	li r4, 0x0
	li r5, 0x3
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0x8
	li r6, 0x4
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x1
	bl GXSetTevSwapMode
	slwi r22, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r22
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r23
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r21
	mr r4, r31
	addi r5, r1, 0x17c
	bl PSMTXConcat
	lwzx r4, r19, r22
	addi r3, r1, 0x17c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	L_af_26:
	rlwinm. r0, r30, 0, 14, 14
	beq L_af_34
	bl shadowGetProjShadowTexObj
	cmplwi r3, 0x0
	beq L_af_34
	bl shadowGetProjShadowTexObj
	mr r20, r3
	bl shadowGetProjShadowProjTexMtx
	mr r22, r3
	bl shadowGetProjShadowColor
	stw r3, 0x50(r1)
	bl shadowGetProjShadowConfig
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0xe
	li r6, 0x9
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x6
	li r6, 0x4
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r21, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r21
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r20
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x14c
	bl PSMTXConcat
	lwzx r4, r19, r21
	addi r3, r1, 0x14c
	li r5, 0x0
	bl GXLoadTexMtxImm
	lwz r0, 0x50(r1)
	addi r4, r1, 0x20
	li r3, 0x1
	stw r0, 0x20(r1)
	bl GXSetTevKColor
	mr r3, r25
	li r4, 0xd
	bl GXSetTevKColorSel
	mr r3, r25
	li r4, 0x1d
	bl GXSetTevKAlphaSel
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	L_af_34:
	rlwinm. r0, r30, 0, 13, 13
	beq L_af_35
	bl shadowGetDepthShadowTexObj
	cmplwi r3, 0x0
	beq L_af_35
	bl shadowGetDepthShadowTexObj
	mr r21, r3
	bl shadowGetDepthShadowDepthMtx
	mr r20, r3
	bl shadowGetDepthShadowProjTexMtx
	mr r22, r3
	bl shadowGetDepthShadowColor
	stw r3, 0x4c(r1)
	bl shadowGetDepthShadowConfig
	lwz r0, 0x3c(r3)
	cmpwi r0, 0x3
	beq L_af_36
	bge L_af_35
	cmpwi r0, 0x0
	beq L_af_37
	b L_af_35
	L_af_37:
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r23, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r23
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp8TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r20
	mr r4, r31
	addi r5, r1, 0x11c
	bl PSMTXConcat
	lwzx r4, r19, r23
	addi r3, r1, 0x11c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x1
	addi r20, r26, 0x1
	addi r27, r27, 0x1
	li r6, 0xff
	mr r3, r19
	mr r4, r20
	mr r5, r27
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x0
	li r5, 0x8
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x8
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	slwi r23, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r23
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r21
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x11c
	bl PSMTXConcat
	lwzx r4, r19, r23
	addi r3, r1, 0x11c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x2
	li r4, 0xff
	mr r3, r19
	li r5, 0xff
	li r6, 0x4
	addi r27, r27, 0x1
	addi r26, r26, 0x2
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x2
	li r5, 0xe
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x6
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x1c
	li r3, 0x1
	stw r0, 0x1c(r1)
	bl GXSetTevKColor
	mr r3, r19
	li r4, 0xd
	bl GXSetTevKColorSel
	mr r3, r19
	li r4, 0x1d
	bl GXSetTevKAlphaSel
	addi r25, r25, 0x3
	b L_af_35
	L_af_36:
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevColorOp
	subi r3, r25, 0x1
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x1
	bl GXSetTevAlphaOp
	li r3, 0x1
	li r4, 0x0
	li r5, 0x3
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	li r3, 0x2
	li r4, 0x3
	li r5, 0x1
	li r6, 0x2
	li r7, 0x3
	bl GXSetTevSwapModeTable
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x8
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x1
	bl GXSetTevSwapMode
	slwi r23, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r23
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	bl shadowGetRamp16TexObj
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r20
	mr r4, r31
	addi r5, r1, 0x11c
	bl PSMTXConcat
	lwzx r4, r19, r23
	addi r3, r1, 0x11c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x1
	addi r20, r26, 0x1
	addi r27, r27, 0x1
	li r6, 0xff
	mr r3, r19
	mr r4, r20
	mr r5, r27
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x0
	li r5, 0x8
	li r6, 0xc
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0xa
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x7
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x2
	bl GXSetTevSwapMode
	slwi r23, r27, 2
	addi r19, r28, 0x98
	lwzx r6, r19, r23
	mr r3, r20
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r21
	mr r4, r27
	bl GXLoadTexObj
	mr r3, r22
	mr r4, r31
	addi r5, r1, 0x11c
	bl PSMTXConcat
	lwzx r4, r19, r23
	addi r3, r1, 0x11c
	li r5, 0x0
	bl GXLoadTexMtxImm
	addi r19, r25, 0x2
	li r4, 0xff
	mr r3, r19
	li r5, 0xff
	li r6, 0x4
	addi r27, r27, 0x1
	addi r26, r26, 0x2
	bl GXSetTevOrder
	mr r3, r19
	li r4, 0x2
	li r5, 0xe
	li r6, 0x0
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r19
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x6
	bl GXSetTevAlphaIn
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r19
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	lwz r0, 0x4c(r1)
	addi r4, r1, 0x18
	li r3, 0x1
	stw r0, 0x18(r1)
	bl GXSetTevKColor
	mr r3, r19
	li r4, 0xd
	bl GXSetTevKColorSel
	mr r3, r19
	li r4, 0x1d
	bl GXSetTevKAlphaSel
	addi r25, r25, 0x3
	L_af_35:
	andis. r0, r30, 0x8010
	beq L_af_38
	rlwinm. r0, r30, 0, 11, 11
	beq L_af_39
	lwz r3, current_mp(r13)
	lbz r19, 0xc(r3)
	lbz r21, 0xd(r3)
	lbz r22, 0xe(r3)
	lbz r20, 0xf(r3)
	b L_af_40
	L_af_39:
	lwz r3, gp(r13)
	lis r0, 0x4330
	stw r0, 0x248(r1)
	li r19, 0xf0
	lwz r0, 0x1c(r3)
	li r21, 0xf0
	lfd f2, 0x2c8(r28)
	li r22, 0x64
	stw r0, 0x24c(r1)
	lfs f3, float_1p5708_8041988c(r2)
	lfd f1, 0x248(r1)
	lfs f0, float_20_80419890(r2)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl cos
	frsp f3, f1
	lfs f1, float_1_80419860(r2)
	lfs f2, float_64_80419894(r2)
	lfs f0, float_0p5_80419854(r2)
	fsubs f1, f1, f3
	fmuls f1, f2, f1
	fmadds f0, f1, f0, f2
	fctiwz f0, f0
	stfd f0, 0x240(r1)
	lwz r0, 0x244(r1)
	clrlwi r20, r0, 24
	L_af_40:
	mr r3, r25
	li r4, 0xff
	li r5, 0xff
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x0
	li r5, 0xf
	li r6, 0xf
	li r7, 0xe
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	mullw r5, r19, r20
	lis r3, 0x8081
	lwz r0, dat_80419814(r2)
	addi r4, r1, 0x14
	subi r9, r3, 0x7f7f
	stw r0, 0x10(r1)
	mullw r6, r21, r20
	li r3, 0x1
	mulhw r8, r9, r5
	mulhw r7, r9, r6
	add r5, r8, r5
	srawi r8, r5, 7
	mullw r0, r22, r20
	add r6, r7, r6
	srawi r6, r6, 7
	mulhw r5, r9, r0
	srwi r9, r8, 31
	add r7, r8, r9
	stb r7, 0x10(r1)
	add r0, r5, r0
	srwi r5, r6, 31
	add r5, r6, r5
	srawi r0, r0, 7
	stb r5, 0x11(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x12(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	bl GXSetTevKColor
	mr r3, r25
	li r4, 0xd
	bl GXSetTevKColorSel
	addi r25, r25, 0x1
	L_af_38:
	rlwinm. r0, r30, 0, 8, 8
	beq L_af_41
	lwz r3, 0x120(r28)
	lis r0, 0x4330
	lwz r11, 0x124(r28)
	lwz r10, 0x128(r28)
	lwz r9, 0x12c(r28)
	lwz r8, 0x130(r28)
	lwz r7, 0x134(r28)
	lwz r6, 0x138(r28)
	lwz r5, 0x13c(r28)
	lwz r4, 0x140(r28)
	stw r3, 0x74(r1)
	lwz r3, gp(r13)
	stw r11, 0x78(r1)
	lfd f2, 0x2c8(r28)
	stw r10, 0x7c(r1)
	lfs f3, float_1p5708_8041988c(r2)
	stw r9, 0x68(r1)
	lfs f0, float_30_80419898(r2)
	stw r8, 0x6c(r1)
	stw r7, 0x70(r1)
	stw r6, 0x5c(r1)
	stw r5, 0x60(r1)
	stw r4, 0x64(r1)
	lwz r3, 0x1c(r3)
	stw r0, 0x248(r1)
	stw r3, 0x24c(r1)
	lfd f1, 0x248(r1)
	fsubs f1, f1, f2
	fmuls f1, f3, f1
	fdivs f1, f1, f0
	bl cos
	frsp f2, f1
	lfs f0, float_1_80419860(r2)
	lis r3, texture_0@ha
	lfs f3, float_127_80419880(r2)
	addi r4, r3, texture_0@l
	lfs f1, float_0p5_80419854(r2)
	fsubs f2, f0, f2
	lfs f0, float_128_8041989c(r2)
	addi r3, r1, 0x9c
	li r5, 0x4
	li r6, 0x40
	li r7, 0xe
	fmuls f2, f3, f2
	li r8, 0x0
	li r9, 0x1
	li r10, 0x0
	fmadds f0, f2, f1, f0
	fctiwz f0, f0
	stfd f0, 0x240(r1)
	lwz r20, 0x244(r1)
	bl GXInitTexObj
	mr r4, r27
	addi r3, r1, 0x9c
	bl GXLoadTexObj
	lwz r4, gp(r13)
	lis r0, 0x4330
	lfs f5, float_0p5_80419854(r2)
	addi r3, r1, 0xec
	lwz r4, 0x1c(r4)
	lfs f1, float_neg2_804198a0(r2)
	fmr f6, f5
	stw r4, 0x254(r1)
	fmr f7, f5
	lfs f2, float_2_80419858(r2)
	fmr f3, f1
	stw r0, 0x250(r1)
	lfd f9, 0x2c8(r28)
	fmr f4, f2
	lfd f8, 0x250(r1)
	lfs f0, float_50_804198a4(r2)
	fsubs f8, f8, f9
	fdivs f8, f8, f0
	bl C_MTXLightOrtho
	addi r3, r1, 0xbc
	addi r4, r1, 0x74
	addi r5, r1, 0x68
	addi r6, r1, 0x5c
	bl C_MTXLookAt
	addi r3, r1, 0xec
	addi r4, r1, 0xbc
	mr r5, r3
	bl PSMTXConcat
	slwi r21, r27, 2
	addi r19, r28, 0x98
	lwzx r4, r19, r21
	addi r3, r1, 0xec
	li r5, 0x0
	bl GXLoadTexMtxImm
	lwzx r6, r19, r21
	mr r3, r26
	li r4, 0x0
	li r5, 0x0
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r25
	mr r4, r26
	mr r5, r27
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	mr r3, r25
	li r4, 0x8
	li r5, 0x0
	li r6, 0xe
	li r7, 0xf
	bl GXSetTevColorIn
	mr r3, r25
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x0
	bl GXSetTevAlphaIn
	mr r3, r25
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	lwz r0, dat_80419818(r2)
	addi r4, r1, 0xc
	li r3, 0x1
	stw r0, 0x8(r1)
	stb r20, 0x8(r1)
	stb r20, 0x9(r1)
	stb r20, 0xa(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	bl GXSetTevKColor
	mr r3, r25
	li r4, 0xd
	bl GXSetTevKColorSel
	addi r25, r25, 0x1
	addi r27, r27, 0x1
	addi r26, r26, 0x1
	L_af_41:
	rlwinm. r0, r30, 0, 4, 7
	beq L_af_42
	lwz r3, activeGroup(r13)
	li r6, 0x0
	lwz r7, current_mp(r13)
	rlwinm r0, r0, 10, 22, 29
	mulli r4, r3, 0x2f4
	stw r31, 0x84(r1)
	lwz r5, mapWork(r13)
	addi r3, r1, 0x80
	stw r7, 0x80(r1)
	addi r4, r4, 0x110
	stw r29, 0x88(r1)
	add r0, r4, r0
	stw r25, 0x8c(r1)
	stw r27, 0x90(r1)
	stw r26, 0x94(r1)
	stw r6, 0x98(r1)
	lwzx r12, r5, r0
	cmplwi r12, 0x0
	beq L_af_43
	mtctr r12
	bctrl
	L_af_43:
	lwz r25, 0x8c(r1)
	lwz r26, 0x94(r1)
	lwz r24, 0x98(r1)
	L_af_42:
	clrlwi r3, r26, 24
	bl GXSetNumTexGens
	clrlwi r3, r25, 24
	bl GXSetNumTevStages
	clrlwi r3, r24, 24
	bl GXSetNumIndStages
	lmw r19, 0x25c(r1)
	lwz r0, 0x294(r1)
	mtlr r0
	addi r1, r1, 0x290
	blr
}

asm s32 mapSetLight(MapObject* obj, LightEntry** lights) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	addi r5, r1, 0x8
	stmw r26, 0x18(r1)
	mr r26, r3
	mr r27, r4
	li r28, 0x0
	addi r3, r26, 0x1c
	addi r4, r26, 0x10
	bl PSMTXMultVec
	lwz r3, 0x8(r26)
	lwz r3, 0x58(r3)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_1
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	bne L_af_2
	mr r4, r27
	addi r3, r1, 0x8
	li r5, 0x8
	li r6, 0x0
	bl lightGetNearObj
	mr r28, r3
	b L_af_3
	L_af_2:
	mr r30, r27
	li r29, 0x0
	li r31, 0x0
	L_af_4:
	lwz r3, 0x8(r26)
	li r0, 0x1
	slw r0, r0, r29
	lwz r3, 0x58(r3)
	lwz r3, 0x4(r3)
	and. r0, r3, r0
	beq L_af_5
	lwz r4, activeGroup(r13)
	addi r0, r31, 0x4
	lha r3, 0xde(r26)
	mulli r4, r4, 0x2f4
	lwz r5, mapWork(r13)
	mulli r3, r3, 0x178
	add r3, r4, r3
	addi r3, r3, 0x98
	lwzx r3, r5, r3
	lwzx r3, r3, r0
	lwz r3, 0x0(r3)
	bl lightNameToPtr
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	bne L_af_5
	addi r28, r28, 0x1
	stw r3, 0x0(r30)
	cmpwi r28, 0x8
	addi r30, r30, 0x4
	bge L_af_6
	L_af_5:
	addi r29, r29, 0x1
	addi r31, r31, 0x4
	cmpwi r29, 0x20
	blt L_af_4
	L_af_6:
	cmpwi r28, 0x8
	bge L_af_3
	slwi r0, r28, 2
	addi r3, r1, 0x8
	add r4, r27, r0
	subfic r5, r28, 0x8
	li r6, 0x0
	bl lightGetNearObj
	add r28, r28, r3
	b L_af_3
	L_af_1:
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq L_af_7
	li r29, 0x0
	mr r31, r27
	mr r30, r29
	L_af_8:
	lwz r3, 0x8(r26)
	li r0, 0x1
	slw r0, r0, r29
	lwz r3, 0x58(r3)
	lwz r3, 0x4(r3)
	and. r0, r3, r0
	beq L_af_9
	lwz r4, activeGroup(r13)
	addi r0, r30, 0x4
	lha r3, 0xde(r26)
	mulli r4, r4, 0x2f4
	lwz r5, mapWork(r13)
	mulli r3, r3, 0x178
	add r3, r4, r3
	addi r3, r3, 0x98
	lwzx r3, r5, r3
	lwzx r3, r3, r0
	lwz r3, 0x0(r3)
	bl lightNameToPtr
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 16, 16
	bne L_af_9
	addi r28, r28, 0x1
	stw r3, 0x0(r31)
	cmpwi r28, 0x8
	addi r31, r31, 0x4
	bge L_af_3
	L_af_9:
	addi r29, r29, 0x1
	addi r30, r30, 0x4
	cmpwi r29, 0x20
	blt L_af_8
	b L_af_3
	L_af_7:
	li r28, 0x0
	L_af_3:
	mr r3, r28
	lmw r26, 0x18(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapDisp(void) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stmw r24, 0x90(r1)
	lwz r0, activeGroup(r13)
	li r3, 0x4
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r30, r4, r0
	bl camGetPtr
	lwz r0, unk_80418458(r13)
	mr r31, r3
	cmpwi r0, 0x0
	bne L_af_1
	mr r29, r30
	li r26, 0x0
	b L_af_2
	L_af_3:
	lwz r0, 0xa8(r29)
	cmplwi r0, 0x0
	beq L_af_4
	lfs f1, float_10_80419864(r2)
	addi r3, r1, 0x58
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lwz r3, 0xa8(r29)
	addi r4, r1, 0x58
	li r5, 0x0
	bl mapReCalcMatrix
	L_af_4:
	lwz r28, 0x154(r29)
	li r27, 0x0
	b L_af_5
	L_af_6:
	lwz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 17, 17
	bne L_af_7
	clrlwi. r0, r3, 31
	beq L_af_8
	rlwinm. r0, r3, 0, 24, 24
	beq L_af_7
	L_af_8:
	rlwinm. r0, r3, 0, 25, 25
	beq L_af_9
	lbz r0, 0xf(r28)
	cmplwi r0, 0x0
	beq L_af_7
	L_af_9:
	rlwinm. r0, r3, 0, 2, 2
	beq L_af_10
	li r0, 0x0
	sth r0, 0xf0(r28)
	sth r0, 0xf2(r28)
	sth r0, 0xec(r28)
	sth r0, 0xee(r28)
	L_af_10:
	lwz r4, 0x0(r28)
	rlwinm. r0, r4, 0, 26, 26
	bne L_af_7
	rlwinm. r0, r4, 0, 27, 27
	bne L_af_11
	lwz r3, 0x8(r28)
	lwz r0, 0x5c(r3)
	cmpwi r0, 0x1
	blt L_af_7
	L_af_11:
	rlwinm. r0, r4, 0, 20, 20
	bne L_af_12
	lhz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_12
	lbz r0, 0x19(r29)
	cmplwi r0, 0x0
	beq L_af_7
	L_af_12:
	rlwinm. r0, r4, 0, 19, 19
	bne L_af_13
	lhz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_13
	lbz r0, 0x1d(r29)
	cmplwi r0, 0x0
	beq L_af_7
	L_af_13:
	addi r3, r31, 0x11c
	addi r4, r28, 0x1c
	addi r5, r1, 0x28
	bl PSMTXConcat
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_14
	lwz r0, mapClipOffFlag(r13)
	cmpwi r0, 0x0
	bne L_af_14
	lwz r25, 0x8(r28)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	lfs f0, 0x48(r25)
	li r24, 0x0
	stfs f0, 0x1c(r1)
	lfs f0, 0x4c(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x50(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_15
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_15
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_15
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_15
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_15
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_15:
	lfs f0, 0x3c(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x40(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x44(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_17
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_17
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_17
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_17
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_17
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_17:
	lfs f0, 0x3c(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x4c(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x50(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_18
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_18
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_18
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_18
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_18
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_18:
	lfs f0, 0x48(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x40(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x50(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_19
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_19
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_19
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_19
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_19
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_19:
	lfs f0, 0x48(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x4c(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x44(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r1, 0x28
	mr r5, r4
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_20
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_20
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_20
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_20
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_20
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_20:
	lfs f0, 0x3c(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x40(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x50(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_21
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_21
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_21
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_21
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_21
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_21:
	lfs f0, 0x48(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x40(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x44(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_22
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_22
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_22
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_22
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_22
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_22:
	lfs f0, 0x3c(r25)
	addi r4, r1, 0x1c
	mr r5, r4
	addi r3, r1, 0x28
	stfs f0, 0x1c(r1)
	lfs f0, 0x4c(r25)
	stfs f0, 0x20(r1)
	lfs f0, 0x44(r25)
	stfs f0, 0x24(r1)
	bl PSMTXMultVec
	addi r4, r1, 0x1c
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, 0x24(r1)
	lfs f1, float_neg1_804198a8(r2)
	fcmpo cr0, f2, f1
	ble L_af_23
	lfs f0, float_0_80419850(r2)
	fcmpo cr0, f2, f0
	bge L_af_23
	lfs f2, 0x1c(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_23
	lfs f0, float_1_80419860(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne L_af_23
	lfs f2, 0x20(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne L_af_23
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_af_16
	L_af_23:
	li r24, 0x1
	L_af_16:
	cmpwi r24, 0x0
	bne L_af_7
	L_af_14:
	addi r3, r1, 0x28
	addi r4, r28, 0x10
	addi r5, r1, 0x10
	bl PSMTXMultVec
	addi r4, r1, 0x10
	addi r3, r31, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, float_5000_804198ac(r2)
	lfs f1, 0x18(r1)
	lfs f0, float_0_80419850(r2)
	fmadds f31, f2, f1, f2
	fcmpo cr0, f31, f0
	bge L_af_24
	fmr f31, f0
	b L_af_25
	L_af_24:
	lfs f0, float_10000_804198b0(r2)
	fcmpo cr0, f31, f0
	ble L_af_25
	fmr f31, f0
	L_af_25:
	lwz r3, 0x8(r28)
	lfs f0, float_neg1_804198a8(r2)
	lwz r0, 0x5c(r3)
	fmuls f31, f31, f0
	lbz r25, 0x4(r28)
	cmpwi r0, 0x0
	ble L_af_26
	lwz r3, 0x60(r3)
	lwz r5, 0x0(r28)
	lwz r4, 0xc(r28)
	lwz r3, 0x10c(r3)
	rlwinm. r0, r5, 0, 25, 25
	stw r4, 0xc(r1)
	stw r3, 0x8(r1)
	beq L_af_27
	lbz r0, 0xf(r1)
	cmplwi r0, 0xff
	beq L_af_27
	li r0, 0x1
	b L_af_28
	L_af_27:
	lbz r0, 0xb(r1)
	cmplwi r0, 0xff
	beq L_af_29
	li r0, 0x1
	b L_af_28
	L_af_29:
	rlwinm. r0, r5, 0, 20, 20
	bne L_af_30
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	lhz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_30
	lbz r0, 0x19(r3)
	cmplwi r0, 0xff
	beq L_af_30
	li r0, 0x1
	b L_af_28
	L_af_30:
	rlwinm. r0, r5, 0, 19, 19
	bne L_af_31
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	lhz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_31
	lbz r0, 0x1d(r3)
	cmplwi r0, 0xff
	beq L_af_31
	li r0, 0x1
	b L_af_28
	L_af_31:
	li r0, 0x0
	L_af_28:
	cmpwi r0, 0x0
	beq L_af_26
	li r25, 0x2
	L_af_26:
	lwz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 2, 2
	beq L_af_32
	rlwinm. r0, r3, 0, 27, 27
	lis r3, mapDispMapGrp_bbox@ha
	lfs f1, float_5000_804198ac(r2)
	addi r5, r3, mapDispMapGrp_bbox@l
	li r3, 0x1
	li r4, 0x3
	bne L_af_33
	lis r5, mapDispMapObj_bbox@ha
	addi r5, r5, mapDispMapObj_bbox@l
	L_af_33:
	mr r6, r28
	bl dispEntry
	L_af_32:
	lwz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 24, 24
	beq L_af_34
	rlwinm. r0, r3, 0, 27, 27
	fmr f1, f31
	lis r3, mapDispMapGrp_off@ha
	mr r4, r25
	addi r5, r3, mapDispMapGrp_off@l
	li r3, 0x1
	bne L_af_35
	lis r5, mapDispMapObj_off@ha
	addi r5, r5, mapDispMapObj_off@l
	L_af_35:
	mr r6, r28
	bl dispEntry
	L_af_34:
	lwz r3, 0x0(r28)
	clrlwi. r0, r3, 31
	bne L_af_7
	rlwinm. r0, r3, 0, 27, 27
	lis r3, mapDispMapGrp@ha
	addi r5, r3, mapDispMapGrp@l
	fmr f1, f31
	lbz r3, 0x5(r28)
	mr r4, r25
	bne L_af_36
	lis r5, mapDispMapObj@ha
	addi r5, r5, mapDispMapObj@l
	L_af_36:
	mr r6, r28
	bl dispEntry
	L_af_7:
	addi r27, r27, 0x1
	addi r28, r28, 0x134
	L_af_5:
	lwz r0, 0x150(r29)
	cmpw r27, r0
	blt L_af_6
	addi r29, r29, 0x178
	addi r26, r26, 0x1
	L_af_2:
	lwz r0, 0x0(r30)
	cmpw r26, r0
	blt L_af_3
	L_af_1:
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	lmw r24, 0x90(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm void mapDispMapGrp_bbox(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	mr r3, r30
	mr r4, r31
	bl _mapDispMapGrp_NoMaterial
	bl sysWaitDrawSync
	addi r3, r31, 0xec
	addi r4, r31, 0xee
	addi r5, r31, 0xf0
	addi r6, r31, 0xf2
	bl GXReadBoundingBox
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapDispMapObj_bbox(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stw r31, 0x7c(r1)
	stw r30, 0x78(r1)
	mr r30, r3
	stw r29, 0x74(r1)
	mr r29, r4
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	mr r3, r30
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r29, 0x1c
	addi r5, r1, 0xc
	bl PSMTXConcat
	addi r3, r1, 0xc
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0xc
	addi r4, r1, 0x3c
	bl PSMTXInvXpose
	addi r3, r1, 0x3c
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x3
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, unk_80422f84(r2)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x4
	bl GXSetTevOp
	li r31, 0x0
	mr r30, r31
	b L_af_1
	L_af_2:
	addi r0, r30, 0x64
	mr r3, r29
	lwzx r4, r4, r0
	bl mapSetPolygon
	addi r30, r30, 0x8
	addi r31, r31, 0x1
	L_af_1:
	lwz r4, 0x8(r29)
	lwz r0, 0x5c(r4)
	cmpw r31, r0
	blt L_af_2
	bl sysWaitDrawSync
	addi r3, r29, 0xec
	addi r4, r29, 0xee
	addi r5, r29, 0xf0
	addi r6, r29, 0xf2
	bl GXReadBoundingBox
	lwz r0, 0x84(r1)
	lwz r31, 0x7c(r1)
	lwz r30, 0x78(r1)
	lwz r29, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stmw r27, 0x13c(r1)
	mr r30, r3
	mr r31, r4
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r31, 0x1c
	addi r5, r1, 0xd4
	bl PSMTXConcat
	addi r3, r1, 0xd4
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0xd4
	addi r4, r1, 0x104
	bl PSMTXInvXpose
	addi r3, r1, 0x104
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x3
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, unk_80422f84(r2)
	addi r4, r1, 0x10
	li r3, 0x4
	stw r0, 0x10(r1)
	bl GXSetChanMatColor
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x4
	bl GXSetTevOp
	li r29, 0x0
	mr r28, r29
	b L_af_1
	L_af_2:
	addi r0, r28, 0x64
	mr r3, r31
	lwzx r4, r4, r0
	bl mapSetPolygon
	addi r28, r28, 0x8
	addi r29, r29, 0x1
	L_af_1:
	lwz r4, 0x8(r31)
	lwz r0, 0x5c(r4)
	cmpw r29, r0
	blt L_af_2
	lwz r27, 0xe4(r31)
	cmplwi r27, 0x0
	beq L_af_3
	mr r3, r30
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r27, 0x1c
	addi r5, r1, 0x74
	bl PSMTXConcat
	addi r3, r1, 0x74
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0x74
	addi r4, r1, 0xa4
	bl PSMTXInvXpose
	addi r3, r1, 0xa4
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x3
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, unk_80422f84(r2)
	addi r4, r1, 0xc
	li r3, 0x4
	stw r0, 0xc(r1)
	bl GXSetChanMatColor
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x4
	bl GXSetTevOp
	li r29, 0x0
	mr r28, r29
	b L_af_4
	L_af_5:
	addi r0, r28, 0x64
	mr r3, r27
	lwzx r4, r4, r0
	bl mapSetPolygon
	addi r28, r28, 0x8
	addi r29, r29, 0x1
	L_af_4:
	lwz r4, 0x8(r27)
	lwz r0, 0x5c(r4)
	cmpw r29, r0
	blt L_af_5
	lwz r28, 0xe4(r27)
	cmplwi r28, 0x0
	beq L_af_6
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj_NoMaterial
	lwz r4, 0xe4(r28)
	cmplwi r4, 0x0
	beq L_af_7
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_7:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_6
	lwz r4, 0xe8(r28)
	cmplwi r4, 0x0
	beq L_af_6
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_6:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_3
	lwz r27, 0xe8(r27)
	cmplwi r27, 0x0
	beq L_af_3
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj_NoMaterial
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_8
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_8:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_3
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_3
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_3:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r27, 0xe8(r31)
	cmplwi r27, 0x0
	beq L_af_9
	mr r3, r30
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r27, 0x1c
	addi r5, r1, 0x14
	bl PSMTXConcat
	addi r3, r1, 0x14
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0x14
	addi r4, r1, 0x44
	bl PSMTXInvXpose
	addi r3, r1, 0x44
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x3
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, unk_80422f84(r2)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x4
	bl GXSetTevOp
	li r29, 0x0
	mr r28, r29
	b L_af_10
	L_af_11:
	addi r0, r28, 0x64
	mr r3, r27
	lwzx r4, r4, r0
	bl mapSetPolygon
	addi r28, r28, 0x8
	addi r29, r29, 0x1
	L_af_10:
	lwz r4, 0x8(r27)
	lwz r0, 0x5c(r4)
	cmpw r29, r0
	blt L_af_11
	lwz r28, 0xe4(r27)
	cmplwi r28, 0x0
	beq L_af_12
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj_NoMaterial
	lwz r4, 0xe4(r28)
	cmplwi r4, 0x0
	beq L_af_13
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_13:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_12
	lwz r4, 0xe8(r28)
	cmplwi r4, 0x0
	beq L_af_12
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_12:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r27, 0xe8(r27)
	cmplwi r27, 0x0
	beq L_af_9
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj_NoMaterial
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_14
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_14:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_9
	mr r3, r30
	bl _mapDispMapGrp_NoMaterial
	L_af_9:
	lmw r27, 0x13c(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
	blr
}

asm void _mapDispMapObj_NoMaterial(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stw r31, 0x7c(r1)
	stw r30, 0x78(r1)
	stw r29, 0x74(r1)
	mr r29, r4
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r29, 0x1c
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r3, r1, 0x3c
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0x3c
	addi r4, r1, 0xc
	bl PSMTXInvXpose
	addi r3, r1, 0xc
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x3
	bl GXSetCullMode
	li r3, 0x1
	bl GXSetNumChans
	lwz r0, unk_80422f84(r2)
	addi r4, r1, 0x8
	li r3, 0x4
	stw r0, 0x8(r1)
	bl GXSetChanMatColor
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x0
	bl GXSetNumTexGens
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0xff
	li r5, 0xff
	li r6, 0x4
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x4
	bl GXSetTevOp
	li r30, 0x0
	li r31, 0x0
	b L_af_1
	L_af_2:
	addi r0, r31, 0x64
	mr r3, r29
	lwzx r4, r4, r0
	bl mapSetPolygon
	addi r31, r31, 0x8
	addi r30, r30, 0x1
	L_af_1:
	lwz r4, 0x8(r29)
	lwz r0, 0x5c(r4)
	cmpw r30, r0
	blt L_af_2
	lwz r0, 0x84(r1)
	lwz r31, 0x7c(r1)
	lwz r30, 0x78(r1)
	lwz r29, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void test_kururing_mapdisp(CameraId cam) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	li r27, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r31, r3, r0
	mr r30, r31
	b L_af_1
	L_af_2:
	lwz r26, 0x154(r30)
	li r28, 0x0
	b L_af_3
	L_af_4:
	lwz r29, 0x0(r26)
	rlwinm. r0, r29, 0, 9, 9
	beq L_af_5
	rlwinm r0, r29, 0, 31, 29
	mr r3, r25
	stw r0, 0x0(r26)
	mr r4, r26
	bl _mapDispMapObj
	stw r29, 0x0(r26)
	L_af_5:
	addi r28, r28, 0x1
	addi r26, r26, 0x134
	L_af_3:
	lwz r0, 0x150(r30)
	cmpw r28, r0
	blt L_af_4
	addi r30, r30, 0x178
	addi r27, r27, 0x1
	L_af_1:
	lwz r0, 0x0(r31)
	cmpw r27, r0
	blt L_af_2
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapDispMapGrp_off(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r4
	stw r30, 0x18(r1)
	mr r30, r3
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	mr r3, r30
	mr r4, r31
	bl _mapDispMapGrp
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lha r3, 0xdc(r31)
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapDispMapObj_off(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r4
	stw r30, 0x18(r1)
	mr r30, r3
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	mr r3, r30
	mr r4, r31
	bl _mapDispMapObj
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lha r3, 0xdc(r31)
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapDispMapGrp(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl _mapDispMapGrp
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapDispMapObj(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl _mapDispMapObj
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _mapDispMapGrp(CameraId cam, MapObject* obj) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r30, r3
	mr r31, r4
	bl _mapDispMapObj
	lwz r29, 0xe4(r31)
	cmplwi r29, 0x0
	beq L_af_1
	mr r3, r30
	mr r4, r29
	bl _mapDispMapObj
	lwz r28, 0xe4(r29)
	cmplwi r28, 0x0
	beq L_af_2
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj
	lwz r27, 0xe4(r28)
	cmplwi r27, 0x0
	beq L_af_3
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_4
	mr r3, r30
	bl _mapDispMapGrp
	L_af_4:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_3
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_3
	mr r3, r30
	bl _mapDispMapGrp
	L_af_3:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_2
	lwz r27, 0xe8(r28)
	cmplwi r27, 0x0
	beq L_af_2
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_5
	mr r3, r30
	bl _mapDispMapGrp
	L_af_5:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_2
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_2
	mr r3, r30
	bl _mapDispMapGrp
	L_af_2:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_1
	lwz r27, 0xe8(r29)
	cmplwi r27, 0x0
	beq L_af_1
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r28, 0xe4(r27)
	cmplwi r28, 0x0
	beq L_af_6
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj
	lwz r4, 0xe4(r28)
	cmplwi r4, 0x0
	beq L_af_7
	mr r3, r30
	bl _mapDispMapGrp
	L_af_7:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_6
	lwz r4, 0xe8(r28)
	cmplwi r4, 0x0
	beq L_af_6
	mr r3, r30
	bl _mapDispMapGrp
	L_af_6:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_1
	lwz r27, 0xe8(r27)
	cmplwi r27, 0x0
	beq L_af_1
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_8
	mr r3, r30
	bl _mapDispMapGrp
	L_af_8:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_1
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_1
	mr r3, r30
	bl _mapDispMapGrp
	L_af_1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r27, 0xe8(r31)
	cmplwi r27, 0x0
	beq L_af_9
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r28, 0xe4(r27)
	cmplwi r28, 0x0
	beq L_af_10
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj
	lwz r29, 0xe4(r28)
	cmplwi r29, 0x0
	beq L_af_11
	mr r3, r30
	mr r4, r29
	bl _mapDispMapObj
	lwz r4, 0xe4(r29)
	cmplwi r4, 0x0
	beq L_af_12
	mr r3, r30
	bl _mapDispMapGrp
	L_af_12:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_11
	lwz r4, 0xe8(r29)
	cmplwi r4, 0x0
	beq L_af_11
	mr r3, r30
	bl _mapDispMapGrp
	L_af_11:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_10
	lwz r28, 0xe8(r28)
	cmplwi r28, 0x0
	beq L_af_10
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj
	lwz r4, 0xe4(r28)
	cmplwi r4, 0x0
	beq L_af_13
	mr r3, r30
	bl _mapDispMapGrp
	L_af_13:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_10
	lwz r4, 0xe8(r28)
	cmplwi r4, 0x0
	beq L_af_10
	mr r3, r30
	bl _mapDispMapGrp
	L_af_10:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r27, 0xe8(r27)
	cmplwi r27, 0x0
	beq L_af_9
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r28, 0xe4(r27)
	cmplwi r28, 0x0
	beq L_af_14
	mr r3, r30
	mr r4, r28
	bl _mapDispMapObj
	lwz r4, 0xe4(r28)
	cmplwi r4, 0x0
	beq L_af_15
	mr r3, r30
	bl _mapDispMapGrp
	L_af_15:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_14
	lwz r4, 0xe8(r28)
	cmplwi r4, 0x0
	beq L_af_14
	mr r3, r30
	bl _mapDispMapGrp
	L_af_14:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r27, 0xe8(r27)
	cmplwi r27, 0x0
	beq L_af_9
	mr r3, r30
	mr r4, r27
	bl _mapDispMapObj
	lwz r4, 0xe4(r27)
	cmplwi r4, 0x0
	beq L_af_16
	mr r3, r30
	bl _mapDispMapGrp
	L_af_16:
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 26, 26
	beq L_af_9
	lwz r4, 0xe8(r27)
	cmplwi r4, 0x0
	beq L_af_9
	mr r3, r30
	bl _mapDispMapGrp
	L_af_9:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void _mapDispMapObj(CameraId cam, MapObject *obj) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stmw r24, 0xc0(r1)
	mr r26, r3
	mr r31, r4
	bl camGetPtr
	stw r31, current_mp(r13)
	mr r30, r3
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 26, 26
	beq L_af_1
	rlwinm. r0, r3, 0, 16, 16
	beq L_af_2
	lwz r3, 0x8(r31)
	li r5, 0x0
	mr r4, r3
	b L_af_3
	L_af_4:
	mr r4, r0
	L_af_3:
	lwz r0, 0x14(r4)
	cmplwi r0, 0x0
	bne L_af_4
	b L_af_5
	L_af_6:
	lwz r4, 0x10(r4)
	addi r5, r5, 0x1
	L_af_5:
	cmplw r4, r3
	bne L_af_6
	xoris r3, r5, 0x8000
	lis r0, 0x4330
	stw r3, 0xbc(r1)
	lis r4, double_to_int_802c1998@ha
	lfd f1, double_to_int_802c1998@l(r4)
	addi r3, r1, 0x3c
	stw r0, 0xb8(r1)
	lfs f2, float_0p01_804198b4(r2)
	lfd f0, 0xb8(r1)
	fsubs f0, f0, f1
	fmuls f31, f2, f0
	bl GXGetProjectionv
	lfs f5, 0x30(r30)
	addi r3, r1, 0x3c
	lfs f2, 0x34(r30)
	lfs f0, float_neg2_804198a0(r2)
	lfs f3, float_1_80419860(r2)
	fadds f1, f2, f5
	fmuls f2, f0, f2
	lfs f4, 0x50(r1)
	fadds f0, f3, f31
	fmuls f1, f3, f1
	fmuls f2, f2, f5
	fmuls f0, f1, f0
	fmuls f1, f31, f2
	fdivs f0, f1, f0
	fadds f0, f3, f0
	fmuls f0, f4, f0
	stfs f0, 0x50(r1)
	bl GXSetProjectionv
	L_af_2:
	lwz r4, 0x8(r31)
	lbz r0, 0x4(r31)
	lwz r3, 0x5c(r4)
	cmpwi r3, 0x0
	ble L_af_7
	lwz r4, 0x60(r4)
	lwz r6, 0x0(r31)
	lwz r5, 0xc(r31)
	lwz r4, 0x10c(r4)
	rlwinm. r3, r6, 0, 25, 25
	stw r5, 0x34(r1)
	stw r4, 0x30(r1)
	beq L_af_8
	lbz r3, 0x37(r1)
	cmplwi r3, 0xff
	beq L_af_8
	li r3, 0x1
	b L_af_9
	L_af_8:
	lbz r3, 0x33(r1)
	cmplwi r3, 0xff
	beq L_af_10
	li r3, 0x1
	b L_af_9
	L_af_10:
	rlwinm. r3, r6, 0, 20, 20
	bne L_af_11
	lwz r3, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r3, 0x2f4
	add r4, r4, r3
	lhz r3, 0x4(r4)
	rlwinm. r3, r3, 0, 30, 30
	beq L_af_11
	lbz r3, 0x19(r4)
	cmplwi r3, 0xff
	beq L_af_11
	li r3, 0x1
	b L_af_9
	L_af_11:
	rlwinm. r3, r6, 0, 19, 19
	bne L_af_12
	lwz r3, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r3, r3, 0x2f4
	add r4, r4, r3
	lhz r3, 0x4(r4)
	rlwinm. r3, r3, 0, 29, 29
	beq L_af_12
	lbz r3, 0x1d(r4)
	cmplwi r3, 0xff
	beq L_af_12
	li r3, 0x1
	b L_af_9
	L_af_12:
	li r3, 0x0
	L_af_9:
	cmpwi r3, 0x0
	beq L_af_7
	li r0, 0x2
	L_af_7:
	cmpwi r0, 0x3
	beq L_af_13
	bge L_af_14
	cmpwi r0, 0x1
	beq L_af_15
	bge L_af_16
	cmpwi r0, 0x0
	bge L_af_17
	b L_af_16
	L_af_14:
	cmpwi r0, 0x5
	beq L_af_16
	bge L_af_16
	b L_af_18
	L_af_17:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x7
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	b L_af_1
	L_af_13:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	b L_af_1
	L_af_15:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	b L_af_1
	L_af_18:
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	b L_af_1
	L_af_16:
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	L_af_1:
	cmpwi r26, 0x1
	bne L_af_19
	li r3, 0x0
	bl GXSetZCompLoc
	L_af_19:
	addi r3, r30, 0x11c
	addi r4, r31, 0x1c
	addi r5, r1, 0x88
	bl PSMTXConcat
	addi r3, r1, 0x88
	li r4, 0x0
	bl GXLoadPosMtxImm
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	bne L_af_20
	addi r3, r1, 0x88
	addi r4, r1, 0x58
	bl PSMTXInvXpose
	addi r3, r1, 0x58
	li r4, 0x0
	bl GXLoadNrmMtxImm
	L_af_20:
	li r3, 0x0
	bl GXSetCurrentMtx
	addi r3, r1, 0x38
	bl GXGetCullMode
	lwz r4, 0x8(r31)
	lis r3, culling@ha
	addi r3, r3, culling@l
	lwz r5, 0x38(r1)
	lwz r4, 0x58(r4)
	lbz r0, 0x1(r4)
	slwi r0, r0, 2
	lwzx r3, r3, r0
	cmpw r5, r3
	beq L_af_21
	bl GXSetCullMode
	L_af_21:
	bl camGetCurPtr
	lwz r0, activeGroup(r13)
	mr r5, r3
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r6, r3, r0
	lhz r0, 0x4(r6)
	clrlwi. r0, r0, 31
	beq L_af_22
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 12, 12
	bne L_af_22
	lwz r0, 0x34(r6)
	la r3, fog_type(r13)
	addi r4, r1, 0x18
	stw r0, 0x18(r1)
	lwz r0, 0x28(r6)
	lfs f1, 0x2c(r6)
	slwi r0, r0, 2
	lfs f2, 0x30(r6)
	lwzx r3, r3, r0
	lfs f3, 0x30(r5)
	lfs f4, 0x34(r5)
	bl GXSetFog
	b L_af_23
	L_af_22:
	lfs f1, float_0_80419850(r2)
	addi r4, r1, 0x1c
	lwz r0, dat_80419824(r2)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stw r0, 0x1c(r1)
	fmr f4, f1
	bl GXSetFog
	L_af_23:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 26, 26
	beq L_af_24
	rlwinm. r0, r3, 0, 17, 17
	bne L_af_25
	clrlwi. r0, r3, 31
	beq L_af_26
	rlwinm. r0, r3, 0, 24, 24
	beq L_af_25
	L_af_26:
	rlwinm. r0, r3, 0, 25, 25
	beq L_af_24
	lbz r0, 0xf(r31)
	cmplwi r0, 0x0
	beq L_af_25
	L_af_24:
	rlwinm. r0, r3, 0, 23, 23
	beq L_af_27
	mr r28, r31
	li r27, 0x0
	li r29, 0x0
	b L_af_28
	L_af_29:
	add r3, r3, r29
	lwz r24, 0x60(r3)
	lwz r26, 0x64(r3)
	mr r3, r24
	bl mapSetTextureMatrix
	lwz r3, 0x0(r31)
	lwz r4, activeGroup(r13)
	rlwinm. r0, r3, 0, 25, 25
	lwz r7, 0x10c(r24)
	lwz r6, 0xc(r31)
	mulli r4, r4, 0x2f4
	lwz r5, dat_8041981c(r2)
	lwz r0, mapWork(r13)
	stw r7, 0x28(r1)
	add r4, r0, r4
	stw r6, 0x2c(r1)
	stw r5, 0x10(r1)
	beq L_af_30
	lbz r7, 0x10(r1)
	lis r5, 0x8081
	lbz r6, 0x2c(r1)
	subi r0, r5, 0x7f7f
	lbz r10, 0x11(r1)
	mullw r11, r7, r6
	lbz r9, 0x2d(r1)
	lbz r6, 0x13(r1)
	lbz r5, 0x2f(r1)
	lbz r8, 0x12(r1)
	lbz r7, 0x2e(r1)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x10(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x11(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0x12(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x13(r1)
	L_af_30:
	lbz r6, 0x28(r1)
	cmplwi r6, 0xff
	beq L_af_31
	lbz r0, 0x13(r1)
	lis r5, 0x8081
	subi r5, r5, 0x7f7f
	mullw r0, r0, r6
	mulhw r5, r5, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x13(r1)
	L_af_31:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_32
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_32
	lbz r7, 0x10(r1)
	lis r5, 0x8081
	lbz r6, 0x16(r4)
	subi r0, r5, 0x7f7f
	lbz r10, 0x11(r1)
	mullw r11, r7, r6
	lbz r9, 0x17(r4)
	lbz r6, 0x13(r1)
	lbz r5, 0x19(r4)
	lbz r8, 0x12(r1)
	lbz r7, 0x18(r4)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x10(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x11(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0x12(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x13(r1)
	L_af_32:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_33
	rlwinm. r0, r3, 0, 19, 19
	bne L_af_33
	lbz r7, 0x10(r1)
	lis r5, 0x8081
	lbz r6, 0x1a(r4)
	subi r0, r5, 0x7f7f
	lbz r10, 0x11(r1)
	mullw r11, r7, r6
	lbz r9, 0x1b(r4)
	lbz r6, 0x13(r1)
	lbz r5, 0x1d(r4)
	lbz r8, 0x12(r1)
	lbz r7, 0x1c(r4)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x10(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x11(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0x12(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0x13(r1)
	L_af_33:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_34
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_34
	lbz r5, 0x10(r1)
	lis r3, 0x8081
	lbz r0, 0x1e(r4)
	subi r10, r3, 0x7f7f
	lbz r8, 0x11(r1)
	mullw r9, r5, r0
	lbz r7, 0x1f(r4)
	lbz r6, 0x12(r1)
	lbz r5, 0x20(r4)
	lbz r0, 0x21(r4)
	lbz r3, 0x13(r1)
	mullw r4, r6, r5
	mulhw r5, r10, r9
	add r5, r5, r9
	srawi r6, r5, 7
	mullw r7, r8, r7
	srwi r8, r6, 31
	mullw r0, r3, r0
	mulhw r3, r10, r7
	mulhw r5, r10, r4
	add r3, r3, r7
	add r7, r6, r8
	srawi r6, r3, 7
	stb r7, 0x10(r1)
	add r4, r5, r4
	mulhw r3, r10, r0
	srwi r5, r6, 31
	srawi r4, r4, 7
	add r6, r6, r5
	srwi r5, r4, 31
	stb r6, 0x11(r1)
	add r0, r3, r0
	add r4, r4, r5
	srawi r0, r0, 7
	stb r4, 0x12(r1)
	srwi r3, r0, 31
	add r0, r0, r3
	stb r0, 0x13(r1)
	L_af_34:
	lwz r0, 0x10(r1)
	addi r4, r1, 0x14
	li r3, 0x0
	stw r0, 0x14(r1)
	bl GXSetTevKColor
	mr r3, r31
	mr r4, r26
	bl mapSetPolygonVtxDesc
	lwz r3, 0xf4(r28)
	lwz r4, 0x114(r28)
	bl GXCallDisplayList
	mr r24, r26
	li r25, 0x0
	b L_af_35
	L_af_36:
	lwz r3, 0x10(r24)
	lwz r4, 0x14(r24)
	bl GXCallDisplayList
	addi r24, r24, 0x8
	addi r25, r25, 0x1
	L_af_35:
	lwz r0, 0x4(r26)
	cmpw r25, r0
	blt L_af_36
	addi r29, r29, 0x8
	addi r28, r28, 0x4
	addi r27, r27, 0x1
	L_af_28:
	lwz r3, 0x8(r31)
	lwz r0, 0x5c(r3)
	cmpw r27, r0
	blt L_af_29
	b L_af_25
	L_af_27:
	li r29, 0x0
	mr r28, r29
	b L_af_37
	L_af_38:
	add r3, r3, r28
	lwz r26, 0x60(r3)
	lwz r27, 0x64(r3)
	mr r3, r26
	bl mapSetTextureMatrix
	lwz r3, 0x0(r31)
	lwz r4, activeGroup(r13)
	rlwinm. r0, r3, 0, 25, 25
	lwz r7, 0x10c(r26)
	lwz r6, 0xc(r31)
	mulli r4, r4, 0x2f4
	lwz r5, dat_8041981c(r2)
	lwz r0, mapWork(r13)
	stw r7, 0x20(r1)
	add r4, r0, r4
	stw r6, 0x24(r1)
	stw r5, 0x8(r1)
	beq L_af_39
	lbz r7, 0x8(r1)
	lis r5, 0x8081
	lbz r6, 0x24(r1)
	subi r0, r5, 0x7f7f
	lbz r10, 0x9(r1)
	mullw r11, r7, r6
	lbz r9, 0x25(r1)
	lbz r6, 0xb(r1)
	lbz r5, 0x27(r1)
	lbz r8, 0xa(r1)
	lbz r7, 0x26(r1)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x8(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x9(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0xa(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xb(r1)
	L_af_39:
	lbz r6, 0x20(r1)
	cmplwi r6, 0xff
	beq L_af_40
	lbz r0, 0xb(r1)
	lis r5, 0x8081
	subi r5, r5, 0x7f7f
	mullw r0, r0, r6
	mulhw r5, r5, r0
	add r0, r5, r0
	srawi r0, r0, 7
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xb(r1)
	L_af_40:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_41
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_41
	lbz r7, 0x8(r1)
	lis r5, 0x8081
	lbz r6, 0x16(r4)
	subi r0, r5, 0x7f7f
	lbz r10, 0x9(r1)
	mullw r11, r7, r6
	lbz r9, 0x17(r4)
	lbz r6, 0xb(r1)
	lbz r5, 0x19(r4)
	lbz r8, 0xa(r1)
	lbz r7, 0x18(r4)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x8(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x9(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0xa(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xb(r1)
	L_af_41:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_42
	rlwinm. r0, r3, 0, 19, 19
	bne L_af_42
	lbz r7, 0x8(r1)
	lis r5, 0x8081
	lbz r6, 0x1a(r4)
	subi r0, r5, 0x7f7f
	lbz r10, 0x9(r1)
	mullw r11, r7, r6
	lbz r9, 0x1b(r4)
	lbz r6, 0xb(r1)
	lbz r5, 0x1d(r4)
	lbz r8, 0xa(r1)
	lbz r7, 0x1c(r4)
	mullw r5, r6, r5
	mulhw r6, r0, r11
	mullw r9, r10, r9
	add r6, r6, r11
	srawi r10, r6, 7
	mullw r7, r8, r7
	srwi r11, r10, 31
	mulhw r8, r0, r9
	mulhw r6, r0, r7
	add r8, r8, r9
	add r9, r10, r11
	srawi r8, r8, 7
	stb r9, 0x8(r1)
	add r6, r6, r7
	mulhw r0, r0, r5
	srwi r7, r8, 31
	srawi r6, r6, 7
	add r8, r8, r7
	srwi r7, r6, 31
	stb r8, 0x9(r1)
	add r0, r0, r5
	add r6, r6, r7
	srawi r0, r0, 7
	stb r6, 0xa(r1)
	srwi r5, r0, 31
	add r0, r0, r5
	stb r0, 0xb(r1)
	L_af_42:
	lhz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_43
	rlwinm. r0, r3, 0, 20, 20
	bne L_af_43
	lbz r5, 0x8(r1)
	lis r3, 0x8081
	lbz r0, 0x1e(r4)
	subi r10, r3, 0x7f7f
	lbz r8, 0x9(r1)
	mullw r9, r5, r0
	lbz r7, 0x1f(r4)
	lbz r6, 0xa(r1)
	lbz r5, 0x20(r4)
	lbz r0, 0x21(r4)
	lbz r3, 0xb(r1)
	mullw r4, r6, r5
	mulhw r5, r10, r9
	add r5, r5, r9
	srawi r6, r5, 7
	mullw r7, r8, r7
	srwi r8, r6, 31
	mullw r0, r3, r0
	mulhw r3, r10, r7
	mulhw r5, r10, r4
	add r3, r3, r7
	add r7, r6, r8
	srawi r6, r3, 7
	stb r7, 0x8(r1)
	add r4, r5, r4
	mulhw r3, r10, r0
	srwi r5, r6, 31
	srawi r4, r4, 7
	add r6, r6, r5
	srwi r5, r4, 31
	stb r6, 0x9(r1)
	add r0, r3, r0
	add r4, r4, r5
	srawi r0, r0, 7
	stb r4, 0xa(r1)
	srwi r3, r0, 31
	add r0, r0, r3
	stb r0, 0xb(r1)
	L_af_43:
	lwz r0, 0x8(r1)
	addi r4, r1, 0xc
	li r3, 0x0
	stw r0, 0xc(r1)
	bl GXSetTevKColor
	mr r3, r31
	mr r4, r26
	bl mapSetMaterial
	mr r3, r31
	mr r4, r27
	bl mapSetPolygon
	addi r28, r28, 0x8
	addi r29, r29, 0x1
	L_af_37:
	lwz r3, 0x8(r31)
	lwz r0, 0x5c(r3)
	cmpw r29, r0
	blt L_af_38
	L_af_25:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 16, 16
	beq L_af_44
	lwz r4, 0x19c(r30)
	addi r3, r30, 0x15c
	bl GXSetProjection
	L_af_44:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 4, 7
	beq L_af_45
	li r3, 0x0
	bl GXSetTevDirect
	li r3, 0x1
	bl GXSetTevDirect
	li r3, 0x2
	bl GXSetTevDirect
	li r3, 0x3
	bl GXSetTevDirect
	li r3, 0x4
	bl GXSetTevDirect
	li r3, 0x0
	bl GXSetNumIndStages
	L_af_45:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	lmw r24, 0xc0(r1)
	lwz r0, 0xf4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm void mapMain(void) {
	nofralloc
	stwu r1, -0x2e0(r1)
	mflr r0
	stw r0, 0x2e4(r1)
	stmw r14, 0x298(r1)
	li r14, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r0, r3, r0
	stw r0, 0x288(r1)
	mr r24, r0
	b L_af_1
	L_af_2:
	lwz r21, 0x164(r24)
	li r20, 0x0
	li r23, 0x0
	b L_af_3
	L_af_4:
	lhz r4, 0x0(r21)
	lwz r3, 0x18(r21)
	clrlwi. r0, r4, 31
	lwz r19, 0xc(r3)
	lwz r18, 0x10(r3)
	lwz r17, 0x14(r3)
	lwz r16, 0x18(r3)
	lwz r15, 0x1c(r3)
	beq L_af_5
	rlwinm. r0, r4, 0, 30, 30
	bne L_af_5
	rlwinm. r0, r4, 0, 23, 23
	beq L_af_6
	lwz r3, gp(r13)
	lwz r22, 0x48(r3)
	lwz r25, 0x4c(r3)
	b L_af_7
	L_af_6:
	rlwinm. r0, r4, 0, 22, 22
	beq L_af_8
	lwz r3, gp(r13)
	lwz r22, 0x50(r3)
	lwz r25, 0x54(r3)
	b L_af_7
	L_af_8:
	rlwinm. r0, r4, 0, 21, 21
	beq L_af_9
	lwz r3, gp(r13)
	lwz r22, 0x58(r3)
	lwz r25, 0x5c(r3)
	b L_af_7
	L_af_9:
	rlwinm. r0, r4, 0, 20, 20
	beq L_af_10
	lwz r3, gp(r13)
	lwz r22, 0x60(r3)
	lwz r25, 0x64(r3)
	b L_af_7
	L_af_10:
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_af_11
	lwz r22, 0x38(r3)
	lwz r25, 0x3c(r3)
	b L_af_7
	L_af_11:
	lwz r22, 0x40(r3)
	lwz r25, 0x44(r3)
	L_af_7:
	rlwinm. r0, r4, 0, 27, 27
	bne L_af_12
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r6, r3, 0x4dd3
	mr r3, r22
	mr r4, r25
	srwi r0, r0, 2
	li r5, 0x0
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	lwz r5, 0xc(r21)
	lwz r0, 0x8(r21)
	subfc r4, r5, r4
	subfe r3, r0, r3
	bl __cvt_ull_flt
	lwz r4, gp(r13)
	lis r0, 0x4330
	stw r0, 0x270(r1)
	lis r3, double_to_int_802c1998@ha
	lwz r0, 0x4(r4)
	lfd f3, double_to_int_802c1998@l(r3)
	xoris r0, r0, 0x8000
	lfs f0, float_1000_80419874(r2)
	stw r0, 0x274(r1)
	lfs f4, 0x10(r21)
	lfd f2, 0x270(r1)
	fsubs f2, f2, f3
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	fcmpo cr0, f0, f4
	bge L_af_13
	fsubs f0, f4, f0
	fsubs f0, f4, f0
	stfs f0, 0x10(r21)
	b L_af_14
	L_af_13:
	fsubs f0, f0, f4
	lfs f1, 0x14(r21)
	fmadds f0, f1, f0, f4
	stfs f0, 0x10(r21)
	L_af_14:
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r6, r3, 0x4dd3
	mr r3, r22
	mr r4, r25
	srwi r0, r0, 2
	li r5, 0x0
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	stw r4, 0xc(r21)
	lis r0, 0x4330
	lis r4, double_to_int_802c1998@ha
	lfs f2, float_1000_80419874(r2)
	stw r3, 0x8(r21)
	lfd f1, double_to_int_802c1998@l(r4)
	lwz r3, gp(r13)
	lfs f0, 0x10(r21)
	lwz r3, 0x4(r3)
	stw r0, 0x270(r1)
	fmuls f2, f2, f0
	xoris r0, r3, 0x8000
	stw r0, 0x274(r1)
	lfd f0, 0x270(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl __cvt_dbl_usll
	lwz r0, 0xc(r21)
	lwz r5, 0x8(r21)
	subfc r0, r4, r0
	stw r0, 0xc(r21)
	subfe r0, r3, r5
	stw r0, 0x8(r21)
	b L_af_15
	L_af_12:
	rlwinm. r0, r4, 0, 26, 26
	beq L_af_15
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r6, r3, 0x4dd3
	mr r3, r22
	mr r4, r25
	srwi r0, r0, 2
	li r5, 0x0
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	stw r4, 0xc(r21)
	lis r0, 0x4330
	lis r4, double_to_int_802c1998@ha
	lfs f2, float_1000_80419874(r2)
	stw r3, 0x8(r21)
	lfd f1, double_to_int_802c1998@l(r4)
	lwz r3, gp(r13)
	lfs f0, 0x10(r21)
	lwz r3, 0x4(r3)
	stw r0, 0x270(r1)
	fmuls f2, f2, f0
	xoris r0, r3, 0x8000
	stw r0, 0x274(r1)
	lfd f0, 0x270(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl __cvt_dbl_usll
	lwz r0, 0xc(r21)
	lwz r5, 0x8(r21)
	subfc r0, r4, r0
	stw r0, 0xc(r21)
	subfe r0, r3, r5
	stw r0, 0x8(r21)
	lhz r0, 0x0(r21)
	rlwinm r0, r0, 0, 27, 25
	sth r0, 0x0(r21)
	lhz r0, 0x0(r21)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r21)
	L_af_15:
	lwz r3, 0x18(r21)
	lfs f0, 0x10(r21)
	lfs f1, 0x8(r3)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne L_af_16
	lhz r0, 0x0(r21)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_17
	b L_af_18
	L_af_19:
	fsubs f0, f0, f1
	L_af_18:
	fcmpo cr0, f0, f1
	bgt L_af_19
	stfs f0, 0x10(r21)
	lis r5, 0x8000
	lis r4, 0x1062
	mr r3, r22
	lwz r0, 0xf8(r5)
	addi r6, r4, 0x4dd3
	mr r4, r25
	li r5, 0x0
	srwi r0, r0, 2
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	stw r4, 0xc(r21)
	lis r0, 0x4330
	lis r4, double_to_int_802c1998@ha
	lfs f2, float_1000_80419874(r2)
	stw r3, 0x8(r21)
	lfd f1, double_to_int_802c1998@l(r4)
	lwz r3, gp(r13)
	lfs f0, 0x10(r21)
	lwz r3, 0x4(r3)
	stw r0, 0x270(r1)
	fmuls f2, f2, f0
	xoris r0, r3, 0x8000
	stw r0, 0x274(r1)
	lfd f0, 0x270(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl __cvt_dbl_usll
	lwz r0, 0xc(r21)
	lwz r5, 0x8(r21)
	subfc r0, r4, r0
	stw r0, 0xc(r21)
	subfe r0, r3, r5
	stw r0, 0x8(r21)
	b L_af_16
	L_af_17:
	stfs f1, 0x10(r21)
	lhz r0, 0x0(r21)
	ori r0, r0, 0x2
	sth r0, 0x0(r21)
	L_af_16:
	cmplwi r19, 0x0
	beq L_af_20
	mr r25, r19
	li r22, 0x0
	b L_af_21
	L_af_22:
	lwz r3, 0x4(r25)
	lwz r0, activeGroup(r13)
	lwz r28, 0x0(r3)
	mulli r0, r0, 0x2f4
	lwz r3, mapWork(r13)
	cmplwi r28, 0x0
	add r27, r3, r0
	bne L_af_23
	li r31, 0x0
	b L_af_24
	L_af_23:
	mr r26, r27
	li r30, 0x0
	b L_af_25
	L_af_26:
	lwz r31, 0x154(r26)
	li r29, 0x0
	b L_af_27
	L_af_28:
	lwz r3, 0x8(r31)
	mr r4, r28
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_29
	b L_af_24
	L_af_29:
	addi r29, r29, 0x1
	addi r31, r31, 0x134
	L_af_27:
	lwz r0, 0x150(r26)
	cmpw r29, r0
	blt L_af_28
	addi r26, r26, 0x178
	addi r30, r30, 0x1
	L_af_25:
	lwz r0, 0x0(r27)
	cmpw r30, r0
	blt L_af_26
	li r31, 0x0
	L_af_24:
	cmplwi r31, 0x0
	beq L_af_30
	lwz r6, 0x4(r25)
	mr r5, r21
	addi r3, r31, 0x7c
	addi r4, r31, 0x4c
	bl mapCalcAnimMatrix
	lwz r0, 0x0(r31)
	li r20, 0x1
	ori r0, r0, 0x2000
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x200
	stw r0, 0x0(r31)
	L_af_30:
	addi r25, r25, 0x4
	addi r22, r22, 0x1
	L_af_21:
	lwz r0, 0x0(r19)
	cmpw r22, r0
	blt L_af_22
	L_af_20:
	cmplwi r18, 0x0
	beq L_af_31
	mr r19, r18
	li r22, 0x0
	b L_af_32
	L_af_33:
	lwz r4, 0x4(r19)
	addi r3, r1, 0x170
	lwz r4, 0x0(r4)
	bl strcpy
	lwz r0, activeGroup(r13)
	li r25, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	mr r29, r27
	b L_af_34
	L_af_35:
	lwz r0, 0xa0(r29)
	cmplwi r0, 0x0
	bne L_af_36
	li r3, 0x0
	b L_af_37
	L_af_36:
	li r26, 0x0
	mr r28, r26
	b L_af_38
	L_af_39:
	addi r30, r28, 0x4
	addi r4, r1, 0x170
	add r30, r3, r30
	lwz r3, 0x0(r30)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_40
	lwz r3, 0x4(r30)
	b L_af_37
	L_af_40:
	addi r28, r28, 0x8
	addi r26, r26, 0x1
	L_af_38:
	lwz r3, 0xa0(r29)
	lwz r0, 0x0(r3)
	cmpw r26, r0
	blt L_af_39
	addi r29, r29, 0x178
	addi r25, r25, 0x1
	L_af_34:
	lwz r0, 0x0(r27)
	cmpw r25, r0
	blt L_af_35
	li r3, 0x0
	L_af_37:
	cmplwi r3, 0x0
	beq L_af_41
	lwz r6, 0x4(r19)
	li r7, 0x1
	lwz r4, 0x10(r6)
	addi r8, r6, 0x68
	subi r0, r4, 0x1
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_41
	L_af_42:
	addi r4, r8, 0x14
	subi r5, r7, 0x1
	lfs f12, 0x10(r21)
	mulli r5, r5, 0x68
	lfs f0, 0x14(r8)
	fcmpo cr0, f12, f0
	addi r5, r5, 0x14
	add r5, r6, r5
	cror eq, lt, eq
	bne L_af_43
	b L_af_44
	L_af_43:
	cmpw r7, r0
	bne L_af_45
	fmr f12, f0
	L_af_44:
	li r0, 0x5
	mr r7, r5
	mr r9, r4
	li r8, 0x0
	mtctr r0
	L_af_46:
	lwz r0, 0x14(r7)
	cmpwi r0, 0x0
	beq L_af_47
	lwz r0, 0x4(r6)
	lfs f0, 0x4(r7)
	mulli r0, r0, 0x1c
	add r10, r0, r8
	addi r0, r10, 0x2c
	stfsx f0, r3, r0
	b L_af_48
	L_af_47:
	lfs f3, 0x0(r5)
	lfs f1, 0x0(r4)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f12, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r9)
	lfs f9, 0x4(r9)
	lfs f8, 0xc(r7)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r7)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_49
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_50
	L_af_49:
	fmr f0, f11
	L_af_50:
	fdivs f6, f2, f0
	lwz r0, 0x4(r6)
	lfs f1, float_2_80419858(r2)
	mulli r0, r0, 0x1c
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	fmuls f4, f6, f6
	add r10, r0, r8
	lfs f3, float_neg2_804198a0(r2)
	addi r0, r10, 0x2c
	fmuls f5, f4, f6
	fmuls f13, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f13
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f13
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfsx f0, r3, r0
	L_af_48:
	addi r7, r7, 0x14
	addi r8, r8, 0x4
	addi r9, r9, 0x14
	bdnz L_af_46
	lwz r0, 0x4(r6)
	lfs f0, 0x8(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x40
	stfsx f0, r3, r0
	lwz r0, 0x4(r6)
	lfs f0, 0xc(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x44
	stfsx f0, r3, r0
	b L_af_41
	L_af_45:
	addi r8, r8, 0x68
	addi r7, r7, 0x1
	bdnz L_af_42
	L_af_41:
	lwz r4, 0x4(r19)
	addi r3, r1, 0x170
	lwz r4, 0x0(r4)
	bl strcpy
	addi r3, r1, 0x170
	la r4, str_804198BC(r2)
	bl strcat
	lwz r0, activeGroup(r13)
	li r25, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	mr r29, r27
	b L_af_51
	L_af_52:
	lwz r0, 0xa0(r29)
	cmplwi r0, 0x0
	bne L_af_53
	li r3, 0x0
	b L_af_54
	L_af_53:
	li r26, 0x0
	mr r28, r26
	b L_af_55
	L_af_56:
	addi r30, r28, 0x4
	addi r4, r1, 0x170
	add r30, r3, r30
	lwz r3, 0x0(r30)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_57
	lwz r3, 0x4(r30)
	b L_af_54
	L_af_57:
	addi r28, r28, 0x8
	addi r26, r26, 0x1
	L_af_55:
	lwz r3, 0xa0(r29)
	lwz r0, 0x0(r3)
	cmpw r26, r0
	blt L_af_56
	addi r29, r29, 0x178
	addi r25, r25, 0x1
	L_af_51:
	lwz r0, 0x0(r27)
	cmpw r25, r0
	blt L_af_52
	li r3, 0x0
	L_af_54:
	cmplwi r3, 0x0
	beq L_af_58
	lwz r6, 0x4(r19)
	li r7, 0x1
	lwz r4, 0x10(r6)
	addi r8, r6, 0x68
	subi r0, r4, 0x1
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_58
	L_af_59:
	addi r4, r8, 0x14
	subi r5, r7, 0x1
	lfs f12, 0x10(r21)
	mulli r5, r5, 0x68
	lfs f0, 0x14(r8)
	fcmpo cr0, f12, f0
	addi r5, r5, 0x14
	add r5, r6, r5
	cror eq, lt, eq
	bne L_af_60
	b L_af_61
	L_af_60:
	cmpw r7, r0
	bne L_af_62
	fmr f12, f0
	L_af_61:
	li r0, 0x5
	mr r7, r5
	mr r9, r4
	li r8, 0x0
	mtctr r0
	L_af_63:
	lwz r0, 0x14(r7)
	cmpwi r0, 0x0
	beq L_af_64
	lwz r0, 0x4(r6)
	lfs f0, 0x4(r7)
	mulli r0, r0, 0x1c
	add r10, r0, r8
	addi r0, r10, 0x2c
	stfsx f0, r3, r0
	b L_af_65
	L_af_64:
	lfs f3, 0x0(r5)
	lfs f1, 0x0(r4)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f12, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r9)
	lfs f9, 0x4(r9)
	lfs f8, 0xc(r7)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r7)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_66
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_67
	L_af_66:
	fmr f0, f11
	L_af_67:
	fdivs f6, f2, f0
	lwz r0, 0x4(r6)
	lfs f1, float_2_80419858(r2)
	mulli r0, r0, 0x1c
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	fmuls f4, f6, f6
	add r10, r0, r8
	lfs f3, float_neg2_804198a0(r2)
	addi r0, r10, 0x2c
	fmuls f5, f4, f6
	fmuls f13, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f13
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f13
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfsx f0, r3, r0
	L_af_65:
	addi r7, r7, 0x14
	addi r8, r8, 0x4
	addi r9, r9, 0x14
	bdnz L_af_63
	lwz r0, 0x4(r6)
	lfs f0, 0x8(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x40
	stfsx f0, r3, r0
	lwz r0, 0x4(r6)
	lfs f0, 0xc(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x44
	stfsx f0, r3, r0
	b L_af_58
	L_af_62:
	addi r8, r8, 0x68
	addi r7, r7, 0x1
	bdnz L_af_59
	L_af_58:
	lwz r4, 0x4(r19)
	addi r3, r1, 0x170
	lwz r4, 0x0(r4)
	bl strcpy
	addi r3, r1, 0x170
	la r4, str_804198C0(r2)
	bl strcat
	lwz r0, activeGroup(r13)
	li r25, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r27, r3, r0
	mr r29, r27
	b L_af_68
	L_af_69:
	lwz r0, 0xa0(r29)
	cmplwi r0, 0x0
	bne L_af_70
	li r3, 0x0
	b L_af_71
	L_af_70:
	li r26, 0x0
	mr r28, r26
	b L_af_72
	L_af_73:
	addi r30, r28, 0x4
	addi r4, r1, 0x170
	add r30, r3, r30
	lwz r3, 0x0(r30)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_74
	lwz r3, 0x4(r30)
	b L_af_71
	L_af_74:
	addi r28, r28, 0x8
	addi r26, r26, 0x1
	L_af_72:
	lwz r3, 0xa0(r29)
	lwz r0, 0x0(r3)
	cmpw r26, r0
	blt L_af_73
	addi r29, r29, 0x178
	addi r25, r25, 0x1
	L_af_68:
	lwz r0, 0x0(r27)
	cmpw r25, r0
	blt L_af_69
	li r3, 0x0
	L_af_71:
	cmplwi r3, 0x0
	beq L_af_75
	lwz r6, 0x4(r19)
	li r7, 0x1
	lwz r4, 0x10(r6)
	addi r8, r6, 0x68
	subi r0, r4, 0x1
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_75
	L_af_76:
	addi r4, r8, 0x14
	subi r5, r7, 0x1
	lfs f12, 0x10(r21)
	mulli r5, r5, 0x68
	lfs f0, 0x14(r8)
	fcmpo cr0, f12, f0
	addi r5, r5, 0x14
	add r5, r6, r5
	cror eq, lt, eq
	bne L_af_77
	b L_af_78
	L_af_77:
	cmpw r7, r0
	bne L_af_79
	fmr f12, f0
	L_af_78:
	li r0, 0x5
	mr r7, r5
	mr r9, r4
	li r8, 0x0
	mtctr r0
	L_af_80:
	lwz r0, 0x14(r7)
	cmpwi r0, 0x0
	beq L_af_81
	lwz r0, 0x4(r6)
	lfs f0, 0x4(r7)
	mulli r0, r0, 0x1c
	add r10, r0, r8
	addi r0, r10, 0x2c
	stfsx f0, r3, r0
	b L_af_82
	L_af_81:
	lfs f3, 0x0(r5)
	lfs f1, 0x0(r4)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f12, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r9)
	lfs f9, 0x4(r9)
	lfs f8, 0xc(r7)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r7)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_83
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_84
	L_af_83:
	fmr f0, f11
	L_af_84:
	fdivs f6, f2, f0
	lwz r0, 0x4(r6)
	lfs f1, float_2_80419858(r2)
	mulli r0, r0, 0x1c
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	fmuls f4, f6, f6
	add r10, r0, r8
	lfs f3, float_neg2_804198a0(r2)
	addi r0, r10, 0x2c
	fmuls f5, f4, f6
	fmuls f13, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f13
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f13
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfsx f0, r3, r0
	L_af_82:
	addi r7, r7, 0x14
	addi r8, r8, 0x4
	addi r9, r9, 0x14
	bdnz L_af_80
	lwz r0, 0x4(r6)
	lfs f0, 0x8(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x40
	stfsx f0, r3, r0
	lwz r0, 0x4(r6)
	lfs f0, 0xc(r6)
	mulli r4, r0, 0x1c
	addi r0, r4, 0x44
	stfsx f0, r3, r0
	b L_af_75
	L_af_79:
	addi r8, r8, 0x68
	addi r7, r7, 0x1
	bdnz L_af_76
	L_af_75:
	addi r19, r19, 0x4
	addi r22, r22, 0x1
	L_af_32:
	lwz r0, 0x0(r18)
	cmpw r22, r0
	blt L_af_33
	L_af_31:
	cmplwi r17, 0x0
	beq L_af_85
	mr r18, r17
	li r19, 0x0
	b L_af_86
	L_af_87:
	lwz r4, 0x4(r18)
	addi r3, r1, 0x70
	lwz r4, 0x0(r4)
	bl strcpy
	lwz r0, activeGroup(r13)
	li r22, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r25, r3, r0
	mr r26, r25
	b L_af_88
	L_af_89:
	lwz r0, 0xa0(r26)
	cmplwi r0, 0x0
	bne L_af_90
	li r4, 0x0
	b L_af_91
	L_af_90:
	li r28, 0x0
	mr r29, r28
	b L_af_92
	L_af_93:
	addi r27, r29, 0x4
	addi r4, r1, 0x70
	add r27, r3, r27
	lwz r3, 0x0(r27)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_94
	lwz r4, 0x4(r27)
	b L_af_91
	L_af_94:
	addi r29, r29, 0x8
	addi r28, r28, 0x1
	L_af_92:
	lwz r3, 0xa0(r26)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	blt L_af_93
	addi r26, r26, 0x178
	addi r22, r22, 0x1
	L_af_88:
	lwz r0, 0x0(r25)
	cmpw r22, r0
	blt L_af_89
	li r4, 0x0
	L_af_91:
	cmplwi r4, 0x0
	beq L_af_95
	lwz r6, 0x4(r18)
	li r5, 0x1
	lwz r3, 0x4(r6)
	addi r7, r6, 0x54
	subi r0, r3, 0x1
	mtctr r0
	cmpwi r3, 0x1
	ble L_af_95
	L_af_96:
	subi r3, r5, 0x1
	lfs f2, 0x10(r21)
	lfs f0, 0x8(r7)
	mulli r3, r3, 0x54
	fcmpo cr0, f2, f0
	addi r3, r3, 0x8
	add r3, r6, r3
	cror eq, lt, eq
	bne L_af_97
	b L_af_98
	L_af_97:
	cmpw r5, r0
	bne L_af_99
	fmr f2, f0
	L_af_98:
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_af_100
	lfs f1, float_255_804198c8(r2)
	lfs f0, 0x4(r3)
	fnmsubs f0, f1, f0, f1
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_95
	L_af_100:
	lfs f3, 0x0(r3)
	lfs f1, 0x8(r7)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f2, f3
	fsubs f12, f1, f3
	lfs f11, 0x10(r7)
	lfs f10, 0xc(r7)
	lfs f9, 0xc(r3)
	fcmpu cr0, f12, f0
	lfs f8, 0x4(r3)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_101
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_102
	L_af_101:
	fmr f0, f12
	L_af_102:
	fdivs f7, f2, f0
	lfs f2, float_2_80419858(r2)
	lfs f1, float_3_8041984c(r2)
	lfs f3, float_1_80419860(r2)
	lfs f4, float_neg2_804198a0(r2)
	lfs f0, float_255_804198c8(r2)
	fmuls f5, f7, f7
	fmuls f6, f5, f7
	fmuls f13, f1, f5
	fnmsubs f1, f2, f5, f6
	fmsubs f2, f2, f6, f13
	fsubs f5, f6, f5
	fadds f1, f7, f1
	fadds f2, f3, f2
	fmadds f3, f4, f6, f13
	fmuls f1, f12, f1
	fmuls f4, f12, f5
	fmuls f1, f9, f1
	fmadds f1, f8, f2, f1
	fmadds f1, f10, f3, f1
	fmadds f1, f11, f4, f1
	fnmsubs f0, f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_95
	L_af_99:
	addi r7, r7, 0x54
	addi r5, r5, 0x1
	bdnz L_af_96
	L_af_95:
	lwz r4, 0x4(r18)
	addi r3, r1, 0x70
	lwz r4, 0x0(r4)
	bl strcpy
	addi r3, r1, 0x70
	la r4, str_804198BC(r2)
	bl strcat
	lwz r0, activeGroup(r13)
	li r22, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r25, r3, r0
	mr r26, r25
	b L_af_103
	L_af_104:
	lwz r0, 0xa0(r26)
	cmplwi r0, 0x0
	bne L_af_105
	li r4, 0x0
	b L_af_106
	L_af_105:
	li r28, 0x0
	mr r29, r28
	b L_af_107
	L_af_108:
	addi r27, r29, 0x4
	addi r4, r1, 0x70
	add r27, r3, r27
	lwz r3, 0x0(r27)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_109
	lwz r4, 0x4(r27)
	b L_af_106
	L_af_109:
	addi r29, r29, 0x8
	addi r28, r28, 0x1
	L_af_107:
	lwz r3, 0xa0(r26)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	blt L_af_108
	addi r26, r26, 0x178
	addi r22, r22, 0x1
	L_af_103:
	lwz r0, 0x0(r25)
	cmpw r22, r0
	blt L_af_104
	li r4, 0x0
	L_af_106:
	cmplwi r4, 0x0
	beq L_af_110
	lwz r6, 0x4(r18)
	li r5, 0x1
	lwz r3, 0x4(r6)
	addi r7, r6, 0x54
	subi r0, r3, 0x1
	mtctr r0
	cmpwi r3, 0x1
	ble L_af_110
	L_af_111:
	subi r3, r5, 0x1
	lfs f2, 0x10(r21)
	lfs f0, 0x8(r7)
	mulli r3, r3, 0x54
	fcmpo cr0, f2, f0
	addi r3, r3, 0x8
	add r3, r6, r3
	cror eq, lt, eq
	bne L_af_112
	b L_af_113
	L_af_112:
	cmpw r5, r0
	bne L_af_114
	fmr f2, f0
	L_af_113:
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_af_115
	lfs f1, float_255_804198c8(r2)
	lfs f0, 0x4(r3)
	fnmsubs f0, f1, f0, f1
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_110
	L_af_115:
	lfs f3, 0x0(r3)
	lfs f1, 0x8(r7)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f2, f3
	fsubs f12, f1, f3
	lfs f11, 0x10(r7)
	lfs f10, 0xc(r7)
	lfs f9, 0xc(r3)
	fcmpu cr0, f12, f0
	lfs f8, 0x4(r3)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_116
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_117
	L_af_116:
	fmr f0, f12
	L_af_117:
	fdivs f7, f2, f0
	lfs f2, float_2_80419858(r2)
	lfs f1, float_3_8041984c(r2)
	lfs f3, float_1_80419860(r2)
	lfs f4, float_neg2_804198a0(r2)
	lfs f0, float_255_804198c8(r2)
	fmuls f5, f7, f7
	fmuls f6, f5, f7
	fmuls f13, f1, f5
	fnmsubs f1, f2, f5, f6
	fmsubs f2, f2, f6, f13
	fsubs f5, f6, f5
	fadds f1, f7, f1
	fadds f2, f3, f2
	fmadds f3, f4, f6, f13
	fmuls f1, f12, f1
	fmuls f4, f12, f5
	fmuls f1, f9, f1
	fmadds f1, f8, f2, f1
	fmadds f1, f10, f3, f1
	fmadds f1, f11, f4, f1
	fnmsubs f0, f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_110
	L_af_114:
	addi r7, r7, 0x54
	addi r5, r5, 0x1
	bdnz L_af_111
	L_af_110:
	lwz r4, 0x4(r18)
	addi r3, r1, 0x70
	lwz r4, 0x0(r4)
	bl strcpy
	addi r3, r1, 0x70
	la r4, str_804198C0(r2)
	bl strcat
	lwz r0, activeGroup(r13)
	li r22, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r25, r3, r0
	mr r26, r25
	b L_af_118
	L_af_119:
	lwz r0, 0xa0(r26)
	cmplwi r0, 0x0
	bne L_af_120
	li r4, 0x0
	b L_af_121
	L_af_120:
	li r28, 0x0
	mr r29, r28
	b L_af_122
	L_af_123:
	addi r27, r29, 0x4
	addi r4, r1, 0x70
	add r27, r3, r27
	lwz r3, 0x0(r27)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_124
	lwz r4, 0x4(r27)
	b L_af_121
	L_af_124:
	addi r29, r29, 0x8
	addi r28, r28, 0x1
	L_af_122:
	lwz r3, 0xa0(r26)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	blt L_af_123
	addi r26, r26, 0x178
	addi r22, r22, 0x1
	L_af_118:
	lwz r0, 0x0(r25)
	cmpw r22, r0
	blt L_af_119
	li r4, 0x0
	L_af_121:
	cmplwi r4, 0x0
	beq L_af_125
	lwz r6, 0x4(r18)
	li r5, 0x1
	lwz r3, 0x4(r6)
	addi r7, r6, 0x54
	subi r0, r3, 0x1
	mtctr r0
	cmpwi r3, 0x1
	ble L_af_125
	L_af_126:
	subi r3, r5, 0x1
	lfs f2, 0x10(r21)
	lfs f0, 0x8(r7)
	mulli r3, r3, 0x54
	fcmpo cr0, f2, f0
	addi r3, r3, 0x8
	add r3, r6, r3
	cror eq, lt, eq
	bne L_af_127
	b L_af_128
	L_af_127:
	cmpw r5, r0
	bne L_af_129
	fmr f2, f0
	L_af_128:
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_af_130
	lfs f1, float_255_804198c8(r2)
	lfs f0, 0x4(r3)
	fnmsubs f0, f1, f0, f1
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_125
	L_af_130:
	lfs f3, 0x0(r3)
	lfs f1, 0x8(r7)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f2, f3
	fsubs f12, f1, f3
	lfs f11, 0x10(r7)
	lfs f10, 0xc(r7)
	lfs f9, 0xc(r3)
	fcmpu cr0, f12, f0
	lfs f8, 0x4(r3)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_131
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_132
	L_af_131:
	fmr f0, f12
	L_af_132:
	fdivs f7, f2, f0
	lfs f2, float_2_80419858(r2)
	lfs f1, float_3_8041984c(r2)
	lfs f3, float_1_80419860(r2)
	lfs f4, float_neg2_804198a0(r2)
	lfs f0, float_255_804198c8(r2)
	fmuls f5, f7, f7
	fmuls f6, f5, f7
	fmuls f13, f1, f5
	fnmsubs f1, f2, f5, f6
	fmsubs f2, f2, f6, f13
	fsubs f5, f6, f5
	fadds f1, f7, f1
	fadds f2, f3, f2
	fmadds f3, f4, f6, f13
	fmuls f1, f12, f1
	fmuls f4, f12, f5
	fmuls f1, f9, f1
	fmadds f1, f8, f2, f1
	fmadds f1, f10, f3, f1
	fmadds f1, f11, f4, f1
	fnmsubs f0, f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0x270(r1)
	lwz r0, 0x274(r1)
	stb r0, 0x10c(r4)
	b L_af_125
	L_af_129:
	addi r7, r7, 0x54
	addi r5, r5, 0x1
	bdnz L_af_126
	L_af_125:
	addi r18, r18, 0x4
	addi r19, r19, 0x1
	L_af_86:
	lwz r0, 0x0(r17)
	cmpw r19, r0
	blt L_af_87
	L_af_85:
	cmplwi r16, 0x0
	beq L_af_133
	mr r17, r16
	li r18, 0x0
	b L_af_134
	L_af_135:
	lwz r3, 0x4(r17)
	lwz r3, 0x0(r3)
	bl lightNameToPtr
	cmplwi r3, 0x0
	beq L_af_136
	lwz r7, 0x4(r17)
	li r6, 0x1
	lwz r4, 0x4(r7)
	addi r8, r7, 0xb8
	subi r0, r4, 0x1
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_136
	L_af_137:
	addi r5, r8, 0x8
	subi r4, r6, 0x1
	lfs f12, 0x10(r21)
	mulli r4, r4, 0xb8
	lfs f0, 0x8(r8)
	fcmpo cr0, f12, f0
	addi r4, r4, 0x8
	add r4, r7, r4
	cror eq, lt, eq
	bne L_af_138
	b L_af_139
	L_af_138:
	cmpw r6, r0
	bne L_af_140
	fmr f12, f0
	L_af_139:
	li r0, 0x9
	mr r6, r4
	mr r8, r5
	addi r7, r1, 0x1c
	mtctr r0
	L_af_141:
	lwz r0, 0x14(r6)
	cmpwi r0, 0x0
	beq L_af_142
	lfs f0, 0x4(r6)
	stfs f0, 0x0(r7)
	b L_af_143
	L_af_142:
	lfs f3, 0x0(r4)
	lfs f1, 0x0(r5)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f12, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r8)
	lfs f9, 0x4(r8)
	lfs f8, 0xc(r6)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r6)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_144
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_145
	L_af_144:
	fmr f0, f11
	L_af_145:
	fdivs f6, f2, f0
	lfs f1, float_2_80419858(r2)
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	lfs f3, float_neg2_804198a0(r2)
	fmuls f4, f6, f6
	fmuls f5, f4, f6
	fmuls f13, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f13
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f13
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfs f0, 0x0(r7)
	L_af_143:
	addi r6, r6, 0x14
	addi r7, r7, 0x4
	addi r8, r8, 0x14
	bdnz L_af_141
	lfs f3, float_10_80419864(r2)
	lfs f0, 0x1c(r1)
	lfs f1, 0x20(r1)
	fmuls f5, f3, f0
	lfs f0, 0x24(r1)
	fmuls f4, f3, f1
	lfs f2, 0x28(r1)
	fmuls f3, f3, f0
	lfs f1, 0x2c(r1)
	stfs f5, 0x24(r3)
	lfs f0, 0x30(r1)
	stfs f4, 0x28(r3)
	stfs f3, 0x2c(r3)
	stfs f2, 0x30(r3)
	stfs f1, 0x34(r3)
	stfs f0, 0x38(r3)
	b L_af_136
	L_af_140:
	addi r8, r8, 0xb8
	addi r6, r6, 0x1
	bdnz L_af_137
	L_af_136:
	addi r17, r17, 0x4
	addi r18, r18, 0x1
	L_af_134:
	lwz r0, 0x0(r16)
	cmpw r18, r0
	blt L_af_135
	L_af_133:
	cmplwi r15, 0x0
	beq L_af_5
	mr r16, r15
	li r17, 0x0
	b L_af_146
	L_af_147:
	lwz r3, 0x4(r16)
	lwz r3, 0x0(r3)
	bl lightNameToPtr
	cmplwi r3, 0x0
	beq L_af_148
	lwz r7, 0x4(r16)
	li r6, 0x1
	lwz r4, 0x4(r7)
	addi r8, r7, 0x68
	subi r0, r4, 0x1
	mtctr r0
	cmpwi r4, 0x1
	ble L_af_148
	L_af_149:
	addi r5, r8, 0x8
	subi r4, r6, 0x1
	lfs f12, 0x10(r21)
	mulli r4, r4, 0x68
	lfs f0, 0x8(r8)
	fcmpo cr0, f12, f0
	addi r4, r4, 0x8
	add r4, r7, r4
	cror eq, lt, eq
	bne L_af_150
	b L_af_151
	L_af_150:
	cmpw r6, r0
	bne L_af_152
	fmr f12, f0
	L_af_151:
	li r0, 0x5
	mr r6, r4
	mr r8, r5
	addi r7, r1, 0x8
	mtctr r0
	L_af_153:
	lwz r0, 0x14(r6)
	cmpwi r0, 0x0
	beq L_af_154
	lfs f0, 0x4(r6)
	stfs f0, 0x0(r7)
	b L_af_155
	L_af_154:
	lfs f3, 0x0(r4)
	lfs f1, 0x0(r5)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f12, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r8)
	lfs f9, 0x4(r8)
	lfs f8, 0xc(r6)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r6)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_156
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_157
	L_af_156:
	fmr f0, f11
	L_af_157:
	fdivs f6, f2, f0
	lfs f1, float_2_80419858(r2)
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	lfs f3, float_neg2_804198a0(r2)
	fmuls f4, f6, f6
	fmuls f5, f4, f6
	fmuls f13, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f13
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f13
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfs f0, 0x0(r7)
	L_af_155:
	addi r6, r6, 0x14
	addi r7, r7, 0x4
	addi r8, r8, 0x14
	bdnz L_af_153
	lfs f2, float_255_804198c8(r2)
	li r0, 0xff
	lfs f0, 0x8(r1)
	lfs f1, 0xc(r1)
	fmuls f4, f2, f0
	lfs f0, 0x10(r1)
	fmuls f3, f2, f1
	lfs f1, 0x18(r1)
	fmuls f2, f2, f0
	lfs f0, 0x14(r1)
	fctiwz f4, f4
	fctiwz f3, f3
	fctiwz f2, f2
	stfd f4, 0x270(r1)
	stfd f3, 0x278(r1)
	lwz r4, 0x274(r1)
	stfd f2, 0x280(r1)
	lwz r5, 0x27c(r1)
	stb r4, 0x48(r3)
	lwz r4, 0x284(r1)
	stb r5, 0x49(r3)
	stb r4, 0x4a(r3)
	stb r0, 0x4b(r3)
	stfs f1, 0x4c(r3)
	stfs f0, 0x50(r3)
	b L_af_148
	L_af_152:
	addi r8, r8, 0x68
	addi r6, r6, 0x1
	bdnz L_af_149
	L_af_148:
	addi r16, r16, 0x4
	addi r17, r17, 0x1
	L_af_146:
	lwz r0, 0x0(r15)
	cmpw r17, r0
	blt L_af_147
	L_af_5:
	addi r23, r23, 0x1
	addi r21, r21, 0x20
	L_af_3:
	lwz r0, 0x160(r24)
	cmpw r23, r0
	blt L_af_4
	cmpwi r20, 0x0
	beq L_af_158
	lfs f1, float_10_80419864(r2)
	addi r3, r1, 0x40
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lwz r3, 0xa8(r24)
	addi r4, r1, 0x40
	li r5, 0x0
	bl mapReCalcMatrix
	L_af_158:
	addi r24, r24, 0x178
	addi r14, r14, 0x1
	L_af_1:
	lwz r3, 0x288(r1)
	lwz r0, 0x0(r3)
	cmpw r14, r0
	blt L_af_2
	lmw r14, 0x298(r1)
	lwz r0, 0x2e4(r1)
	mtlr r0
	addi r1, r1, 0x2e0
	blr
}

asm void mapReCalcMatrix(MapObject* obj, Mtx mtx, BOOL force) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r5
	stw r30, 0x18(r1)
	mr r30, r4
	li r4, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	stw r28, 0x10(r1)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 22, 22
	beq L_af_1
	li r4, 0x1
	L_af_1:
	cmpwi r31, 0x0
	beq L_af_2
	li r4, 0x1
	L_af_2:
	cmpwi r4, 0x0
	beq L_af_3
	rlwinm. r0, r3, 0, 18, 18
	beq L_af_4
	mr r3, r30
	addi r4, r29, 0x7c
	addi r5, r29, 0x1c
	bl PSMTXConcat
	b L_af_5
	L_af_4:
	mr r3, r30
	addi r4, r29, 0x4c
	addi r5, r29, 0x1c
	bl PSMTXConcat
	L_af_5:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 10, 10
	beq L_af_6
	addi r3, r29, 0x1c
	addi r4, r29, 0xac
	mr r5, r3
	bl PSMTXConcat
	L_af_6:
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x0(r29)
	lwz r28, 0xe4(r29)
	cmplwi r28, 0x0
	beq L_af_7
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 18, 18
	beq L_af_8
	addi r3, r29, 0x1c
	addi r4, r28, 0x7c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	b L_af_9
	L_af_8:
	addi r3, r29, 0x1c
	addi r4, r28, 0x4c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	L_af_9:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq L_af_10
	addi r3, r28, 0x1c
	addi r4, r28, 0xac
	mr r5, r3
	bl PSMTXConcat
	L_af_10:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x0(r28)
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_11
	addi r4, r28, 0x1c
	li r5, 0x1
	bl mapReCalcMatrix
	L_af_11:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_7
	addi r4, r29, 0x1c
	li r5, 0x1
	bl mapReCalcMatrix
	L_af_7:
	lwz r28, 0xe8(r29)
	cmplwi r28, 0x0
	beq L_af_12
	lwz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 22, 22
	beq L_af_13
	li r3, 0x1
	L_af_13:
	cmpwi r31, 0x0
	beq L_af_14
	li r3, 0x1
	L_af_14:
	cmpwi r3, 0x0
	beq L_af_15
	rlwinm. r0, r4, 0, 18, 18
	beq L_af_16
	mr r3, r30
	addi r4, r28, 0x7c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	b L_af_17
	L_af_16:
	mr r3, r30
	addi r4, r28, 0x4c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	L_af_17:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq L_af_18
	addi r3, r28, 0x1c
	addi r4, r28, 0xac
	mr r5, r3
	bl PSMTXConcat
	L_af_18:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x0(r28)
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_19
	addi r4, r28, 0x1c
	li r5, 0x1
	bl mapReCalcMatrix
	L_af_19:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r30
	mr r5, r31
	bl mapReCalcMatrix
	b L_af_12
	L_af_15:
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_20
	mr r5, r31
	addi r4, r28, 0x1c
	bl mapReCalcMatrix
	L_af_20:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r30
	mr r5, r31
	bl mapReCalcMatrix
	b L_af_12
	L_af_3:
	lwz r28, 0xe4(r29)
	cmplwi r28, 0x0
	beq L_af_21
	lwz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 22, 22
	beq L_af_22
	li r3, 0x1
	L_af_22:
	cmpwi r31, 0x0
	beq L_af_23
	li r3, 0x1
	L_af_23:
	cmpwi r3, 0x0
	beq L_af_24
	rlwinm. r0, r4, 0, 18, 18
	beq L_af_25
	addi r3, r29, 0x1c
	addi r4, r28, 0x7c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	b L_af_26
	L_af_25:
	addi r3, r29, 0x1c
	addi r4, r28, 0x4c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	L_af_26:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq L_af_27
	addi r3, r28, 0x1c
	addi r4, r28, 0xac
	mr r5, r3
	bl PSMTXConcat
	L_af_27:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x0(r28)
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_28
	addi r4, r28, 0x1c
	li r5, 0x1
	bl mapReCalcMatrix
	L_af_28:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_21
	mr r5, r31
	addi r4, r29, 0x1c
	bl mapReCalcMatrix
	b L_af_21
	L_af_24:
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_29
	mr r5, r31
	addi r4, r28, 0x1c
	bl mapReCalcMatrix
	L_af_29:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_21
	mr r5, r31
	addi r4, r29, 0x1c
	bl mapReCalcMatrix
	L_af_21:
	lwz r28, 0xe8(r29)
	cmplwi r28, 0x0
	beq L_af_12
	lwz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 22, 22
	beq L_af_30
	li r3, 0x1
	L_af_30:
	cmpwi r31, 0x0
	beq L_af_31
	li r3, 0x1
	L_af_31:
	cmpwi r3, 0x0
	beq L_af_32
	rlwinm. r0, r4, 0, 18, 18
	beq L_af_33
	mr r3, r30
	addi r4, r28, 0x7c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	b L_af_34
	L_af_33:
	mr r3, r30
	addi r4, r28, 0x4c
	addi r5, r28, 0x1c
	bl PSMTXConcat
	L_af_34:
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 10, 10
	beq L_af_35
	addi r3, r28, 0x1c
	addi r4, r28, 0xac
	mr r5, r3
	bl PSMTXConcat
	L_af_35:
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0x0(r28)
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_36
	addi r4, r28, 0x1c
	li r5, 0x1
	bl mapReCalcMatrix
	L_af_36:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r30
	mr r5, r31
	bl mapReCalcMatrix
	b L_af_12
	L_af_32:
	lwz r3, 0xe4(r28)
	cmplwi r3, 0x0
	beq L_af_37
	mr r5, r31
	addi r4, r28, 0x1c
	bl mapReCalcMatrix
	L_af_37:
	lwz r3, 0xe8(r28)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r30
	mr r5, r31
	bl mapReCalcMatrix
	L_af_12:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapCalcAnimMatrix(Mtx out, Mtx in, MapAnim* anim, MapAnimJoint* joint) {
	nofralloc
	stwu r1, -0x220(r1)
	mflr r0
	stw r0, 0x224(r1)
	stfd f31, 0x210(r1)
	psq_st f31, 0x218(r1), 0, 0
	stfd f30, 0x200(r1)
	psq_st f30, 0x208(r1), 0, 0
	stfd f29, 0x1f0(r1)
	psq_st f29, 0x1f8(r1), 0, 0
	stfd f28, 0x1e0(r1)
	psq_st f28, 0x1e8(r1), 0, 0
	stfd f27, 0x1d0(r1)
	psq_st f27, 0x1d8(r1), 0, 0
	stfd f26, 0x1c0(r1)
	psq_st f26, 0x1c8(r1), 0, 0
	stfd f25, 0x1b0(r1)
	psq_st f25, 0x1b8(r1), 0, 0
	stfd f24, 0x1a0(r1)
	psq_st f24, 0x1a8(r1), 0, 0
	stfd f23, 0x190(r1)
	psq_st f23, 0x198(r1), 0, 0
	stw r31, 0x18c(r1)
	stw r30, 0x188(r1)
	lwz r7, 0x58(r6)
	mr r30, r3
	mr r31, r4
	addi r4, r6, 0x1a8
	subi r0, r7, 0x1
	li r8, 0x1
	mtctr r0
	cmpwi r7, 0x1
	ble L_af_1
	L_af_2:
	addi r9, r4, 0x5c
	subi r3, r8, 0x1
	lfs f0, 0x10(r5)
	mulli r3, r3, 0x1a8
	lfs f1, 0x5c(r4)
	fcmpo cr0, f0, f1
	addi r7, r3, 0x5c
	add r7, r6, r7
	cror eq, lt, eq
	bne L_af_3
	fmr f13, f0
	b L_af_4
	L_af_3:
	cmpw r8, r0
	bne L_af_5
	fmr f13, f1
	L_af_4:
	li r0, 0x9
	mr r3, r7
	mr r5, r9
	addi r4, r1, 0x128
	mtctr r0
	L_af_6:
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_af_7
	lfs f0, 0x4(r3)
	stfs f0, 0x0(r4)
	b L_af_8
	L_af_7:
	lfs f3, 0x0(r7)
	lfs f1, 0x0(r9)
	lfs f0, float_0_80419850(r2)
	fsubs f2, f13, f3
	fsubs f11, f1, f3
	lfs f10, 0x8(r5)
	lfs f9, 0x4(r5)
	lfs f8, 0xc(r3)
	fcmpu cr0, f11, f0
	lfs f7, 0x4(r3)
	mfcr r0
	extrwi r0, r0, 1, 2
	xori r0, r0, 0x1
	cntlzw r0, r0
	srwi. r0, r0, 5
	beq L_af_9
	lfs f0, float_1Eneg08_804198b8(r2)
	b L_af_10
	L_af_9:
	fmr f0, f11
	L_af_10:
	fdivs f6, f2, f0
	lfs f1, float_2_80419858(r2)
	lfs f0, float_3_8041984c(r2)
	lfs f2, float_1_80419860(r2)
	lfs f3, float_neg2_804198a0(r2)
	fmuls f4, f6, f6
	fmuls f5, f4, f6
	fmuls f12, f0, f4
	fnmsubs f0, f1, f4, f5
	fmsubs f1, f1, f5, f12
	fsubs f4, f5, f4
	fadds f0, f6, f0
	fadds f1, f2, f1
	fmadds f2, f3, f5, f12
	fmuls f0, f11, f0
	fmuls f3, f11, f4
	fmuls f0, f8, f0
	fmadds f0, f7, f1, f0
	fmadds f0, f9, f2, f0
	fmadds f0, f10, f3, f0
	stfs f0, 0x0(r4)
	L_af_8:
	addi r3, r3, 0x14
	addi r4, r4, 0x4
	addi r5, r5, 0x14
	bdnz L_af_6
	lfs f1, 0x140(r1)
	lfs f0, 0x1c(r6)
	lfs f3, 0x144(r1)
	lfs f2, 0x20(r6)
	fdivs f26, f1, f0
	lfs f1, 0x148(r1)
	lfs f0, 0x24(r6)
	lfs f12, 0x128(r1)
	lfs f11, 0x4(r6)
	lfs f10, 0x12c(r1)
	lfs f9, 0x8(r6)
	fdivs f25, f3, f2
	lfs f8, 0x130(r1)
	lfs f7, 0xc(r6)
	lfs f6, 0x134(r1)
	lfs f5, 0x10(r6)
	lfs f4, 0x138(r1)
	lfs f3, 0x14(r6)
	fdivs f24, f1, f0
	lfs f2, 0x13c(r1)
	lfs f1, 0x18(r6)
	lfs f0, float_0_80419850(r2)
	fsubs f31, f12, f11
	fsubs f30, f10, f9
	fsubs f29, f8, f7
	fcmpu cr0, f31, f0
	fsubs f28, f6, f5
	fsubs f27, f4, f3
	fsubs f23, f2, f1
	bne L_af_11
	fcmpu cr0, f30, f0
	bne L_af_11
	fcmpu cr0, f29, f0
	beq L_af_12
	L_af_11:
	fmr f1, f31
	addi r3, r1, 0xf8
	fmr f2, f30
	fmr f3, f29
	bl PSMTXTrans
	L_af_12:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f28, f0
	beq L_af_13
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x98
	li r4, 0x78
	fmuls f1, f0, f28
	bl PSMTXRotRad
	L_af_13:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f27, f0
	beq L_af_14
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x68
	li r4, 0x79
	fmuls f1, f0, f27
	bl PSMTXRotRad
	L_af_14:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f23, f0
	beq L_af_15
	lfs f0, float_deg2rad_80419868(r2)
	addi r3, r1, 0x38
	li r4, 0x7a
	fmuls f1, f0, f23
	bl PSMTXRotRad
	L_af_15:
	fmr f1, f26
	addi r3, r1, 0xc8
	fmr f2, f25
	fmr f3, f24
	bl PSMTXScale
	addi r3, r1, 0x8
	bl PSMTXIdentity
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f31, f0
	bne L_af_16
	fcmpu cr0, f30, f0
	bne L_af_16
	fcmpu cr0, f29, f0
	beq L_af_17
	L_af_16:
	addi r3, r1, 0x8
	addi r4, r1, 0xf8
	mr r5, r3
	bl PSMTXConcat
	L_af_17:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f23, f0
	beq L_af_18
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	L_af_18:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f27, f0
	beq L_af_19
	addi r3, r1, 0x8
	addi r4, r1, 0x68
	mr r5, r3
	bl PSMTXConcat
	L_af_19:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f28, f0
	beq L_af_20
	addi r3, r1, 0x8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	L_af_20:
	lfs f0, float_0_80419850(r2)
	fcmpu cr0, f26, f0
	bne L_af_21
	fcmpu cr0, f25, f0
	bne L_af_21
	fcmpu cr0, f24, f0
	beq L_af_22
	L_af_21:
	addi r3, r1, 0x8
	addi r4, r1, 0xc8
	mr r5, r3
	bl PSMTXConcat
	L_af_22:
	mr r3, r31
	mr r5, r30
	addi r4, r1, 0x8
	bl PSMTXConcat
	b L_af_1
	L_af_5:
	addi r4, r4, 0x1a8
	addi r8, r8, 0x1
	bdnz L_af_2
	L_af_1:
	psq_l f31, 0x218(r1), 0, 0
	lfd f31, 0x210(r1)
	psq_l f30, 0x208(r1), 0, 0
	lfd f30, 0x200(r1)
	psq_l f29, 0x1f8(r1), 0, 0
	lfd f29, 0x1f0(r1)
	psq_l f28, 0x1e8(r1), 0, 0
	lfd f28, 0x1e0(r1)
	psq_l f27, 0x1d8(r1), 0, 0
	lfd f27, 0x1d0(r1)
	psq_l f26, 0x1c8(r1), 0, 0
	lfd f26, 0x1c0(r1)
	psq_l f25, 0x1b8(r1), 0, 0
	lfd f25, 0x1b0(r1)
	psq_l f24, 0x1a8(r1), 0, 0
	lfd f24, 0x1a0(r1)
	psq_l f23, 0x198(r1), 0, 0
	lfd f23, 0x190(r1)
	lwz r31, 0x18c(r1)
	lwz r0, 0x224(r1)
	lwz r30, 0x188(r1)
	mtlr r0
	addi r1, r1, 0x220
	blr
}

asm void bmapLoad(const char *map, const char *map2) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r30, r3
	mr r31, r4
	bl sysWaitDrawSync
	li r28, 0x0
	lwz r29, mapWork(r13)
	stw r28, activeGroup(r13)
	li r25, 0x0
	mr r27, r29
	b L_af_1
	L_af_2:
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r26, r0, r28
	add r26, r3, r26
	lwz r3, 0x16c(r26)
	cmplwi r3, 0x0
	beq L_af_3
	bl _mapFree
	L_af_3:
	li r0, 0x0
	stw r0, 0x168(r26)
	stw r0, 0x16c(r26)
	stw r0, 0x170(r27)
	stw r0, 0x178(r27)
	stw r0, 0x174(r27)
	lwz r3, 0x7c(r27)
	cmplwi r3, 0x0
	beq L_af_4
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_5
	lwz r3, 0x7c(r27)
	lwz r4, 0x80(r27)
	bl aramMgrToAram
	stw r3, 0x170(r27)
	lwz r3, 0x84(r27)
	lwz r4, 0x88(r27)
	bl aramMgrToAram
	stw r3, 0x178(r27)
	lwz r3, 0x84(r27)
	bl _mapFree
	lwz r3, 0x7c(r27)
	bl _mapFree
	li r0, 0x0
	stw r0, 0x84(r27)
	stw r0, 0x7c(r27)
	b L_af_4
	L_af_5:
	lwz r3, 0x8c(r27)
	lwz r4, 0x90(r27)
	bl aramMgrToAram
	stw r3, 0x174(r27)
	lwz r3, 0x8c(r27)
	bl _mapFree
	li r0, 0x0
	stw r0, 0x8c(r27)
	L_af_4:
	addi r28, r28, 0x178
	addi r27, r27, 0x178
	addi r25, r25, 0x1
	L_af_1:
	lwz r0, 0x0(r29)
	cmpw r25, r0
	blt L_af_2
	lwz r3, mapWork(r13)
	li r0, 0x1
	stw r0, activeGroup(r13)
	li r4, 0x0
	addi r29, r3, 0x2f4
	li r5, 0x2f4
	mr r3, r29
	bl memset
	mr r3, r29
	mr r5, r30
	li r4, 0x0
	bl _mapLoad
	li r0, 0x1
	cmplwi r31, 0x0
	stw r0, 0x0(r29)
	beq L_af_6
	mr r3, r29
	mr r5, r31
	li r4, 0x1
	bl _mapLoad
	li r0, 0x2
	stw r0, 0x0(r29)
	L_af_6:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void bmapUnLoad(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl sysWaitDrawSync
	lwz r3, mapWork(r13)
	li r0, 0x1
	stw r0, activeGroup(r13)
	li r30, 0x0
	addi r31, r3, 0x2f4
	mr r29, r31
	b L_af_1
	L_af_2:
	lwz r3, 0x154(r29)
	cmplwi r3, 0x0
	beq L_af_3
	bl _mapFree
	li r0, 0x0
	stw r0, 0x150(r29)
	stw r0, 0x154(r29)
	L_af_3:
	lwz r3, 0x164(r29)
	cmplwi r3, 0x0
	beq L_af_4
	bl _mapFree
	li r0, 0x0
	stw r0, 0x160(r29)
	stw r0, 0x164(r29)
	L_af_4:
	lwz r3, 0x16c(r29)
	cmplwi r3, 0x0
	beq L_af_5
	bl _mapFree
	li r0, 0x0
	stw r0, 0x16c(r29)
	stw r0, 0x168(r29)
	L_af_5:
	addi r29, r29, 0x178
	addi r30, r30, 0x1
	L_af_1:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_2
	li r0, 0x0
	stw r0, unk_80418458(r13)
	bl hitReInit
	bl lightReInit
	bl envReInit
	mr r29, r31
	li r30, 0x0
	b L_af_6
	L_af_7:
	lwz r3, 0x7c(r29)
	cmplwi r3, 0x0
	beq L_af_8
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_9
	lwz r3, 0x7c(r29)
	bl _mapFree
	L_af_9:
	li r0, 0x0
	stw r0, 0x7c(r29)
	L_af_8:
	lwz r3, 0x84(r29)
	cmplwi r3, 0x0
	beq L_af_10
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_11
	lwz r3, 0x84(r29)
	bl _mapFree
	L_af_11:
	li r0, 0x0
	stw r0, 0x84(r29)
	L_af_10:
	lwz r3, 0x8c(r29)
	cmplwi r3, 0x0
	beq L_af_12
	bl _mapFree
	li r0, 0x0
	stw r0, 0x8c(r29)
	L_af_12:
	addi r3, r29, 0x6
	la r4, float_0_804198cc(r2)
	li r5, 0x10
	bl strncpy
	addi r29, r29, 0x178
	addi r30, r30, 0x1
	L_af_6:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_7
	li r3, 0x1
	bl arcDelete
	li r3, 0x2
	bl arcDelete
	mr r3, r31
	li r4, 0x0
	li r5, 0x2f4
	bl memset
	li r31, 0x0
	lwz r30, mapWork(r13)
	stw r31, activeGroup(r13)
	mr r29, r30
	b L_af_13
	L_af_14:
	lwz r0, 0x170(r29)
	cmplwi r0, 0x0
	beq L_af_15
	lwz r3, 0x80(r29)
	bl _mapAllocTail
	stw r3, 0x7c(r29)
	lwz r3, 0x88(r29)
	bl _mapAllocTail
	stw r3, 0x84(r29)
	lwz r3, 0x170(r29)
	lwz r4, 0x7c(r29)
	bl aramMgrToMram
	lwz r3, 0x178(r29)
	lwz r4, 0x84(r29)
	bl aramMgrToMram
	li r0, 0x0
	stw r0, 0x170(r29)
	stw r0, 0x178(r29)
	b L_af_16
	L_af_15:
	lwz r3, 0x90(r29)
	bl _mapAllocTail
	stw r3, 0x8c(r29)
	lwz r3, 0x174(r29)
	lwz r4, 0x8c(r29)
	bl aramMgrToMram
	li r0, 0x0
	stw r0, 0x174(r29)
	L_af_16:
	mr r3, r31
	bl makeDisplayList
	addi r29, r29, 0x178
	addi r31, r31, 0x1
	L_af_13:
	lwz r0, 0x0(r30)
	cmpw r31, r0
	blt L_af_14
	lwz r4, 0x8c(r30)
	cmplwi r4, 0x0
	beq L_af_17
	lwz r5, 0x90(r30)
	li r3, 0x1
	bl arcEntry
	L_af_17:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapLoad(const char* map) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	bl sysWaitDrawSync
	lwz r31, mapWork(r13)
	li r0, 0x0
	stw r0, activeGroup(r13)
	li r4, 0x0
	mr r3, r31
	li r5, 0x2f4
	bl memset
	mr r3, r31
	mr r5, r30
	li r4, 0x0
	bl _mapLoad
	li r0, 0x1
	stw r0, 0x0(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL mapPreLoad(void) {
	nofralloc
	li r3, 0x1
	blr
}

asm void mapUnLoad(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl sysWaitDrawSync
	lwz r31, mapWork(r13)
	li r30, 0x0
	stw r30, activeGroup(r13)
	mr r29, r31
	b L_af_1
	L_af_2:
	lwz r3, 0x154(r29)
	cmplwi r3, 0x0
	beq L_af_3
	bl _mapFree
	li r0, 0x0
	stw r0, 0x150(r29)
	stw r0, 0x154(r29)
	L_af_3:
	lwz r3, 0x164(r29)
	cmplwi r3, 0x0
	beq L_af_4
	bl _mapFree
	li r0, 0x0
	stw r0, 0x160(r29)
	stw r0, 0x164(r29)
	L_af_4:
	lwz r3, 0x16c(r29)
	cmplwi r3, 0x0
	beq L_af_5
	bl _mapFree
	li r0, 0x0
	stw r0, 0x16c(r29)
	stw r0, 0x168(r29)
	L_af_5:
	addi r29, r29, 0x178
	addi r30, r30, 0x1
	L_af_1:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_2
	li r0, 0x0
	stw r0, unk_80418458(r13)
	bl hitReInit
	bl lightReInit
	bl envReInit
	li r3, 0x4
	bl camUnLoadRoad
	li r3, 0x4
	bl camSetTypePersp
	mr r29, r31
	li r30, 0x0
	b L_af_6
	L_af_7:
	lwz r3, 0x7c(r29)
	cmplwi r3, 0x0
	beq L_af_8
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_9
	lwz r3, 0x7c(r29)
	bl _mapFree
	L_af_9:
	li r0, 0x0
	stw r0, 0x7c(r29)
	L_af_8:
	lwz r3, 0x84(r29)
	cmplwi r3, 0x0
	beq L_af_10
	bl arcDataCheck
	cmpwi r3, 0x0
	bne L_af_11
	lwz r3, 0x84(r29)
	bl _mapFree
	L_af_11:
	li r0, 0x0
	stw r0, 0x84(r29)
	L_af_10:
	lwz r3, 0x8c(r29)
	cmplwi r3, 0x0
	beq L_af_12
	bl _mapFree
	li r0, 0x0
	stw r0, 0x8c(r29)
	L_af_12:
	addi r3, r29, 0x6
	la r4, float_0_804198cc(r2)
	li r5, 0x10
	bl strncpy
	addi r29, r29, 0x178
	addi r30, r30, 0x1
	L_af_6:
	lwz r0, 0x0(r31)
	cmpw r30, r0
	blt L_af_7
	li r3, 0x1
	bl arcDelete
	mr r3, r31
	li r4, 0x0
	li r5, 0x2f4
	bl memset
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void _mapLoad(MapWork* wp, BOOL group, const char* map) {
	nofralloc
	stwu r1, -0x280(r1)
	mflr r0
	stw r0, 0x284(r1)
	li r0, 0x0
	stmw r17, 0x244(r1)
	mr r25, r4
	mr r26, r5
	mr r24, r3
	mulli r30, r25, 0x178
	lis r3, vec3_802c16d8@ha
	mr r4, r26
	addi r23, r3, vec3_802c16d8@l
	add r31, r24, r30
	li r5, 0x10
	addi r3, r31, 0x6
	stw r0, error_flag(r13)
	stw r0, error_count(r13)
	bl strncpy
	mr r5, r26
	addi r3, r1, 0x1c0
	addi r4, r23, 0x2d0
	crclr 6
	bl sprintf
	addi r3, r1, 0x1c0
	addi r4, r31, 0x7c
	addi r5, r31, 0x80
	bl arcOpen
	lwz r0, 0x7c(r31)
	mr r20, r31
	cmplwi r0, 0x0
	bne L_af_1
	addi r3, r1, 0x140
	addi r6, r1, 0x1c0
	la r4, str_804198D0(r2)
	la r5, str_80419848(r2)
	crclr 6
	bl sprintf
	addi r3, r1, 0x140
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr r18, r3
	bl DVDMgrGetLength
	stw r3, 0x80(r31)
	mr r17, r31
	lwz r3, 0x80(r31)
	addi r0, r3, 0x1f
	clrrwi r3, r0, 5
	bl _mapAllocTail
	stw r3, 0x7c(r20)
	mr r3, r18
	li r6, 0x0
	lwz r5, 0x80(r17)
	lwz r4, 0x7c(r20)
	addi r0, r5, 0x1f
	clrrwi r5, r0, 5
	bl DVDMgrRead
	mr r3, r18
	bl DVDMgrClose
	L_af_1:
	mr r5, r26
	addi r3, r1, 0x1c0
	addi r4, r23, 0x2dc
	crclr 6
	bl sprintf
	add r29, r24, r30
	li r0, 0x0
	stw r0, 0x84(r29)
	addi r3, r1, 0x1c0
	addi r4, r31, 0x84
	addi r5, r31, 0x88
	bl arcOpen
	lwz r3, 0x84(r29)
	cmplwi r3, 0x0
	beq L_af_2
	bl UnpackTexPalette
	b L_af_3
	L_af_2:
	addi r3, r1, 0xc0
	addi r6, r1, 0x1c0
	la r4, str_804198D0(r2)
	la r5, str_80419848(r2)
	crclr 6
	bl sprintf
	addi r3, r1, 0xc0
	li r4, 0x2
	li r5, 0x0
	bl DVDMgrOpen
	mr. r18, r3
	beq L_af_3
	bl DVDMgrGetLength
	stw r3, 0x88(r29)
	mr r17, r29
	lwz r3, 0x88(r29)
	addi r0, r3, 0x1f
	clrrwi r3, r0, 5
	bl _mapAllocTail
	stw r3, 0x84(r29)
	mr r3, r18
	li r6, 0x0
	lwz r5, 0x88(r17)
	lwz r4, 0x84(r29)
	addi r0, r5, 0x1f
	clrrwi r5, r0, 5
	bl DVDMgrRead
	mr r3, r18
	bl DVDMgrClose
	lwz r3, 0x84(r29)
	bl UnpackTexPalette
	L_af_3:
	bl GXInvalidateVtxCache
	add r3, r24, r30
	addic. r28, r31, 0x38
	lwz r17, 0x80(r3)
	lwz r27, 0x7c(r20)
	beq L_af_4
	mr r3, r28
	li r4, 0x0
	li r5, 0x44
	bl memset
	add r6, r24, r30
	mr r3, r28
	lwz r0, 0x74(r6)
	mr r4, r27
	li r5, 0x20
	ori r0, r0, 0x1
	stw r0, 0x74(r6)
	bl memcpy
	add r3, r24, r30
	lwz r0, 0x38(r3)
	cmplw r0, r17
	bne L_af_4
	lwz r0, 0x3c(r3)
	li r4, 0x20
	cmplwi r0, 0x0
	beq L_af_5
	addi r0, r27, 0x20
	stw r0, 0x58(r3)
	lwz r4, 0x3c(r3)
	addi r4, r4, 0x20
	L_af_5:
	add r5, r24, r30
	lwz r0, 0x40(r5)
	cmplwi r0, 0x0
	beq L_af_6
	add r0, r27, r4
	stw r0, 0x5c(r5)
	lwz r0, 0x40(r5)
	slwi r0, r0, 2
	add r4, r4, r0
	L_af_6:
	add r5, r24, r30
	lwz r0, 0x44(r5)
	cmplwi r0, 0x0
	beq L_af_7
	add r0, r27, r4
	stw r0, 0x60(r5)
	lwz r0, 0x44(r5)
	slwi r0, r0, 3
	add r4, r4, r0
	L_af_7:
	add r5, r24, r30
	lwz r0, 0x48(r5)
	cmplwi r0, 0x0
	beq L_af_8
	add r0, r27, r4
	stw r0, 0x64(r5)
	lwz r0, 0x48(r5)
	slwi r0, r0, 3
	add r4, r4, r0
	L_af_8:
	lwz r0, 0x38(r3)
	cmplw r4, r0
	bge L_af_9
	add r0, r27, r4
	add r3, r24, r30
	stw r0, 0x68(r3)
	L_af_9:
	add r3, r24, r30
	li r5, 0x0
	stw r27, 0x78(r3)
	mr r6, r5
	lis r3, 0x8000
	b L_af_10
	L_af_11:
	lwz r4, 0x5c(r31)
	lwz r7, 0x58(r31)
	lwzx r4, r4, r6
	lwzx r0, r7, r4
	cmplw r0, r3
	bgt L_af_12
	add r0, r0, r7
	stwx r0, r7, r4
	L_af_12:
	addi r6, r6, 0x4
	addi r5, r5, 0x1
	L_af_10:
	lwz r0, 0x40(r31)
	cmplw r5, r0
	blt L_af_11
	L_af_4:
	li r17, 0x0
	mr r18, r17
	b L_af_13
	L_af_14:
	lwz r3, 0x28(r28)
	addi r0, r18, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x240
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_15
	lwz r3, 0x28(r28)
	slwi r0, r17, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r22, r4, r0
	b L_af_16
	L_af_15:
	addi r18, r18, 0x8
	addi r17, r17, 0x1
	L_af_13:
	lwz r0, 0xc(r28)
	cmplw r17, r0
	blt L_af_14
	li r22, 0x0
	L_af_16:
	li r17, 0x0
	mr r18, r17
	b L_af_17
	L_af_18:
	lwz r3, 0x28(r28)
	addi r0, r18, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x2e8
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_19
	lwz r3, 0x28(r28)
	slwi r0, r17, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r0, r4, r0
	b L_af_20
	L_af_19:
	addi r18, r18, 0x8
	addi r17, r17, 0x1
	L_af_17:
	lwz r0, 0xc(r28)
	cmplw r17, r0
	blt L_af_18
	li r0, 0x0
	L_af_20:
	add r27, r24, r30
	li r21, 0x0
	stw r0, 0x94(r27)
	mr r17, r21
	b L_af_21
	L_af_22:
	lwz r3, 0x28(r28)
	addi r0, r17, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x2f8
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_23
	lwz r3, 0x28(r28)
	slwi r0, r21, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r0, r4, r0
	b L_af_24
	L_af_23:
	addi r17, r17, 0x8
	addi r21, r21, 0x1
	L_af_21:
	lwz r0, 0xc(r28)
	cmplw r21, r0
	blt L_af_22
	li r0, 0x0
	L_af_24:
	add r3, r24, r30
	li r21, 0x0
	stw r0, 0x98(r3)
	mr r17, r21
	b L_af_25
	L_af_26:
	lwz r3, 0x28(r28)
	addi r0, r17, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x304
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_27
	lwz r3, 0x28(r28)
	slwi r0, r21, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r0, r4, r0
	b L_af_28
	L_af_27:
	addi r17, r17, 0x8
	addi r21, r21, 0x1
	L_af_25:
	lwz r0, 0xc(r28)
	cmplw r21, r0
	blt L_af_26
	li r0, 0x0
	L_af_28:
	add r19, r24, r30
	li r21, 0x0
	stw r0, 0x9c(r19)
	mr r20, r21
	b L_af_29
	L_af_30:
	lwz r3, 0x28(r28)
	addi r0, r20, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x310
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_31
	lwz r3, 0x28(r28)
	slwi r0, r21, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r0, r4, r0
	b L_af_32
	L_af_31:
	addi r20, r20, 0x8
	addi r21, r21, 0x1
	L_af_29:
	lwz r0, 0xc(r28)
	cmplw r21, r0
	blt L_af_30
	li r0, 0x0
	L_af_32:
	add r3, r24, r30
	li r21, 0x0
	stw r0, 0xa0(r3)
	mr r20, r21
	b L_af_33
	L_af_34:
	lwz r3, 0x28(r28)
	addi r0, r20, 0x4
	lwz r5, 0x30(r28)
	addi r4, r23, 0x324
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_35
	lwz r3, 0x28(r28)
	slwi r0, r21, 3
	lwz r4, 0x20(r28)
	lwzx r0, r3, r0
	add r0, r4, r0
	b L_af_36
	L_af_35:
	addi r20, r20, 0x8
	addi r21, r21, 0x1
	L_af_33:
	lwz r0, 0xc(r28)
	cmplw r21, r0
	blt L_af_34
	li r0, 0x0
	L_af_36:
	add r3, r24, r30
	stw r0, 0xa4(r3)
	lwz r3, 0x4(r22)
	lwz r4, 0x8(r22)
	bl mapSearchDmdJoint
	mr r0, r3
	lwz r3, 0x4(r22)
	lwz r4, 0xc(r22)
	mr r20, r0
	bl mapSearchDmdJoint
	mr r0, r3
	lwz r3, 0x0(r22)
	mr r22, r0
	addi r4, r23, 0x254
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_37
	add r3, r24, r30
	lhz r0, 0x4(r3)
	ori r0, r0, 0x8000
	sth r0, 0x4(r3)
	b L_af_38
	L_af_37:
	add r3, r24, r30
	lhz r0, 0x4(r3)
	clrlwi r0, r0, 17
	sth r0, 0x4(r3)
	L_af_38:
	lfs f1, float_10_80419864(r2)
	addi r3, r1, 0x90
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r20
	mr r5, r25
	addi r4, r1, 0x90
	bl mapEntry
	add r21, r24, r30
	mr r5, r25
	stw r3, 0xa8(r21)
	mr r3, r22
	addi r4, r1, 0x90
	bl hitEntry
	stw r3, 0xac(r21)
	li r22, 0x0
	li r20, 0x0
	b L_af_39
	L_af_40:
	addi r0, r20, 0x4
	lfs f1, float_10_80419864(r2)
	lwzx r28, r3, r0
	addi r4, r1, 0x84
	li r18, 0x1
	li r17, 0x0
	addi r3, r28, 0x8
	bl PSVECScale
	lwz r3, 0x4(r28)
	addi r4, r23, 0x330
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_41
	li r18, 0x0
	b L_af_42
	L_af_41:
	lwz r3, 0x4(r28)
	addi r4, r23, 0x340
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_43
	li r18, 0x1
	b L_af_42
	L_af_43:
	lwz r3, 0x4(r28)
	addi r4, r23, 0x34c
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_44
	li r18, 0x2
	b L_af_42
	L_af_44:
	lwz r3, 0x4(r28)
	addi r4, r23, 0x360
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_42
	li r18, 0x3
	L_af_42:
	lwz r3, 0x40(r28)
	subis r0, r3, 0x12d
	cmplwi r0, 0x60d8
	bne L_af_45
	lwz r17, 0x3c(r28)
	L_af_45:
	lwz r0, 0x2c(r28)
	mr r4, r18
	mr r9, r17
	addi r5, r1, 0x84
	stw r0, 0x8(r1)
	addi r6, r28, 0x14
	addi r7, r1, 0x8
	lwz r3, 0x0(r28)
	lfs f1, 0x30(r28)
	lfs f2, 0x34(r28)
	lwz r8, 0x38(r28)
	bl lightEntry
	addi r20, r20, 0x4
	addi r22, r22, 0x1
	L_af_39:
	lwz r3, 0x98(r31)
	lwz r0, 0x0(r3)
	cmpw r22, r0
	blt L_af_40
	lwz r3, dat_8041982c(r2)
	lwz r0, dat_80419830(r2)
	stw r3, paper_ambient(r13)
	stw r0, paperCraft_ambient(r13)
	lwz r3, 0x9c(r19)
	cmplwi r3, 0x0
	beq L_af_46
	lwz r0, 0x0(r3)
	add r4, r24, r30
	stw r0, 0x24(r4)
	lwz r3, 0x9c(r19)
	lwz r0, 0x4(r3)
	stw r0, 0x28(r4)
	lwz r3, 0x9c(r19)
	lfs f0, 0x8(r3)
	stfs f0, 0x2c(r4)
	lwz r3, 0x9c(r19)
	lfs f0, 0xc(r3)
	stfs f0, 0x30(r4)
	lwz r3, 0x9c(r19)
	lwz r0, 0x10(r3)
	stw r0, 0x34(r4)
	lwz r0, 0x24(r4)
	cmpwi r0, 0x0
	beq L_af_47
	lhz r0, 0x4(r4)
	ori r0, r0, 0x1
	sth r0, 0x4(r4)
	b L_af_47
	L_af_46:
	add r3, r24, r30
	li r0, 0x0
	stw r0, 0x24(r3)
	lfs f0, float_0_80419850(r2)
	stw r0, 0x28(r3)
	stfs f0, 0x2c(r3)
	stfs f0, 0x30(r3)
	lwz r0, unk_80422f80(r2)
	stw r0, 0x34(r3)
	lhz r0, 0x4(r3)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x4(r3)
	L_af_47:
	lwz r0, activeGroup(r13)
	cmpwi r0, 0x1
	beq L_af_48
	mr r5, r26
	addi r3, r1, 0x1c0
	addi r4, r23, 0x36c
	crclr 6
	bl sprintf
	addi r4, r1, 0x1c0
	li r3, 0x4
	bl camLoadRoad
	L_af_48:
	li r3, 0x4
	bl camSetTypePersp
	lwz r3, 0xa8(r21)
	lwz r4, 0x84(r29)
	lwz r5, 0x94(r27)
	bl mapBuildTexture
	addi r3, r1, 0x78
	addi r4, r1, 0x6c
	bl mapGetBoundingBox
	lwz r0, 0x28(r23)
	add r3, r24, r30
	lwz r4, 0x2c(r23)
	stw r0, 0x60(r1)
	lfs f0, 0x6c(r1)
	lwz r0, 0x30(r23)
	stfs f0, 0x60(r1)
	lfs f1, 0x70(r1)
	stw r4, 0x64(r1)
	lfs f0, 0x74(r1)
	stw r0, 0x68(r1)
	lwz r0, 0x60(r1)
	stfs f1, 0x64(r1)
	stfs f0, 0x68(r1)
	lwz r4, 0x64(r1)
	stw r0, 0xb0(r3)
	lwz r0, 0x68(r1)
	stw r4, 0xb4(r3)
	stw r0, 0xb8(r3)
	lwz r5, 0x34(r23)
	lwz r4, 0x38(r23)
	lwz r0, 0x3c(r23)
	stw r5, 0x54(r1)
	lfs f0, 0x78(r1)
	stw r4, 0x58(r1)
	lfs f1, 0x70(r1)
	stfs f0, 0x54(r1)
	lfs f0, 0x74(r1)
	stw r0, 0x5c(r1)
	lwz r0, 0x54(r1)
	stfs f1, 0x58(r1)
	stfs f0, 0x5c(r1)
	lwz r4, 0x58(r1)
	stw r0, 0xbc(r3)
	lwz r0, 0x5c(r1)
	stw r4, 0xc0(r3)
	stw r0, 0xc4(r3)
	lwz r5, 0x40(r23)
	lwz r4, 0x44(r23)
	lwz r0, 0x48(r23)
	stw r5, 0x48(r1)
	lfs f0, 0x6c(r1)
	stw r4, 0x4c(r1)
	lfs f1, 0x7c(r1)
	stfs f0, 0x48(r1)
	lfs f0, 0x74(r1)
	stw r0, 0x50(r1)
	lwz r0, 0x48(r1)
	stfs f1, 0x4c(r1)
	stfs f0, 0x50(r1)
	lwz r4, 0x4c(r1)
	stw r0, 0xc8(r3)
	lwz r0, 0x50(r1)
	stw r4, 0xcc(r3)
	stw r0, 0xd0(r3)
	lwz r5, 0x4c(r23)
	lwz r4, 0x50(r23)
	lwz r0, 0x54(r23)
	stw r5, 0x3c(r1)
	lfs f0, 0x6c(r1)
	stw r4, 0x40(r1)
	lfs f1, 0x70(r1)
	stfs f0, 0x3c(r1)
	lfs f0, 0x80(r1)
	stw r0, 0x44(r1)
	lwz r0, 0x3c(r1)
	stfs f1, 0x40(r1)
	stfs f0, 0x44(r1)
	lwz r4, 0x40(r1)
	stw r0, 0xd4(r3)
	lwz r0, 0x44(r1)
	stw r4, 0xd8(r3)
	stw r0, 0xdc(r3)
	lwz r5, 0x58(r23)
	lwz r4, 0x5c(r23)
	lwz r0, 0x60(r23)
	stw r5, 0x30(r1)
	lfs f0, 0x78(r1)
	stw r4, 0x34(r1)
	lfs f1, 0x7c(r1)
	stfs f0, 0x30(r1)
	lfs f0, 0x74(r1)
	stw r0, 0x38(r1)
	lwz r0, 0x30(r1)
	stfs f1, 0x34(r1)
	stfs f0, 0x38(r1)
	lwz r4, 0x34(r1)
	stw r0, 0xe0(r3)
	lwz r0, 0x38(r1)
	stw r4, 0xe4(r3)
	stw r0, 0xe8(r3)
	lwz r5, 0x64(r23)
	lwz r4, 0x68(r23)
	lwz r0, 0x6c(r23)
	stw r5, 0x24(r1)
	stw r4, 0x28(r1)
	stw r0, 0x2c(r1)
	lfs f0, 0x6c(r1)
	li r21, 0x0
	lfs f1, 0x7c(r1)
	mr r20, r21
	stfs f0, 0x24(r1)
	lfs f0, 0x80(r1)
	stfs f1, 0x28(r1)
	lwz r0, 0x24(r1)
	stfs f0, 0x2c(r1)
	lwz r4, 0x28(r1)
	stw r0, 0xec(r3)
	lwz r0, 0x2c(r1)
	stw r4, 0xf0(r3)
	stw r0, 0xf4(r3)
	lwz r5, 0x70(r23)
	lwz r4, 0x74(r23)
	lwz r0, 0x78(r23)
	stw r5, 0x18(r1)
	lfs f0, 0x78(r1)
	stw r4, 0x1c(r1)
	lfs f1, 0x70(r1)
	stfs f0, 0x18(r1)
	lfs f0, 0x80(r1)
	stw r0, 0x20(r1)
	lwz r0, 0x18(r1)
	stfs f1, 0x1c(r1)
	stfs f0, 0x20(r1)
	lwz r4, 0x1c(r1)
	stw r0, 0xf8(r3)
	lwz r0, 0x20(r1)
	stw r4, 0xfc(r3)
	stw r0, 0x100(r3)
	lwz r5, 0x7c(r23)
	lwz r4, 0x80(r23)
	lwz r0, 0x84(r23)
	stw r5, 0xc(r1)
	lfs f0, 0x78(r1)
	stw r4, 0x10(r1)
	lfs f1, 0x7c(r1)
	stfs f0, 0xc(r1)
	lfs f0, 0x80(r1)
	stw r0, 0x14(r1)
	lwz r0, 0xc(r1)
	stfs f1, 0x10(r1)
	stfs f0, 0x14(r1)
	lwz r4, 0x10(r1)
	stw r0, 0x104(r3)
	lwz r0, 0x14(r1)
	stw r4, 0x108(r3)
	stw r0, 0x10c(r3)
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r22, r3, r0
	add r19, r22, r30
	b L_af_49
	L_af_50:
	lwz r3, 0x60(r19)
	addi r0, r20, 0x4
	lwz r5, 0x68(r19)
	addi r4, r23, 0x28c
	lwzx r0, r3, r0
	add r3, r5, r0
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_51
	lwz r3, 0x60(r19)
	slwi r0, r21, 3
	lwz r4, 0x58(r19)
	lwzx r0, r3, r0
	add r18, r4, r0
	b L_af_52
	L_af_51:
	addi r20, r20, 0x8
	addi r21, r21, 0x1
	L_af_49:
	lwz r0, 0x44(r19)
	cmplw r21, r0
	blt L_af_50
	li r18, 0x0
	L_af_52:
	cmplwi r18, 0x0
	beq L_af_53
	lwz r0, 0x0(r18)
	add r3, r22, r30
	stw r0, 0x160(r3)
	lwz r0, 0x160(r3)
	cmpwi r0, 0x0
	beq L_af_53
	slwi r3, r0, 5
	addi r0, r3, 0x1f
	clrrwi r17, r0, 5
	mr r3, r17
	bl _mapAlloc
	add r20, r22, r30
	mr r5, r17
	stw r3, 0x164(r20)
	li r4, 0x0
	lwz r3, 0x164(r20)
	bl memset
	li r4, 0x0
	lwz r5, 0x164(r20)
	mr r3, r4
	b L_af_54
	L_af_55:
	sth r3, 0x0(r5)
	addi r4, r4, 0x1
	lwzu r0, 0x4(r18)
	stw r0, 0x18(r5)
	addi r5, r5, 0x20
	L_af_54:
	lwz r0, 0x160(r19)
	cmpw r4, r0
	blt L_af_55
	L_af_53:
	mr r3, r25
	bl makeDisplayList
	lwz r0, activeGroup(r13)
	li r18, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r0, r3, r0
	add r17, r0, r30
	lwz r19, 0x154(r17)
	b L_af_56
	L_af_57:
	lwz r3, 0x8(r19)
	lwz r0, 0x5c(r3)
	cmpwi r0, 0x1
	blt L_af_58
	cmpwi r0, 0x8
	bgt L_af_58
	lwz r3, 0x58(r3)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 28, 28
	bne L_af_58
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	bne L_af_58
	bl shadowGetCharShadowProjection
	cmpwi r3, 0x0
	beq L_af_59
	lwz r0, 0x0(r19)
	rlwinm. r0, r0, 0, 29, 29
	bne L_af_58
	L_af_59:
	lhz r0, 0x4(r17)
	rlwinm. r0, r0, 0, 16, 16
	beq L_af_58
	lwz r0, 0x0(r19)
	ori r0, r0, 0x100
	stw r0, 0x0(r19)
	L_af_58:
	addi r18, r18, 0x1
	addi r19, r19, 0x134
	L_af_56:
	lwz r0, 0x150(r17)
	cmpw r18, r0
	blt L_af_57
	li r0, 0x0
	stw r0, unk_80418458(r13)
	lmw r17, 0x244(r1)
	lwz r0, 0x284(r1)
	mtlr r0
	addi r1, r1, 0x280
	blr
}

asm void mapSetPlayRate(const char* name, f32 rate) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x28(r1)
	fmr f31, f1
	stmw r26, 0x10(r1)
	mr r26, r3
	li r30, 0x0
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r4, r0
	mr r27, r28
	b L_af_1
	L_af_2:
	lwz r31, 0x164(r27)
	li r29, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq L_af_5
	lwz r3, 0x18(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	b L_af_6
	L_af_5:
	addi r29, r29, 0x1
	addi r31, r31, 0x20
	L_af_3:
	lwz r0, 0x160(r27)
	cmpw r29, r0
	blt L_af_4
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_1:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_2
	li r31, 0x0
	L_af_6:
	cmplwi r31, 0x0
	beq L_af_7
	stfs f31, 0x14(r31)
	L_af_7:
	lfd f31, 0x28(r1)
	lmw r26, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void mapReStartAnimationAll(const char* name) {
	nofralloc
	lwz r0, activeGroup(r13)
	li r6, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	mr r4, r3
	b L_af_1
	L_af_2:
	lwz r7, 0x164(r4)
	li r5, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r7)
	addi r5, r5, 0x1
	ori r0, r0, 0x20
	sth r0, 0x0(r7)
	addi r7, r7, 0x20
	L_af_3:
	lwz r0, 0x160(r4)
	cmpw r5, r0
	blt L_af_4
	addi r4, r4, 0x178
	addi r6, r6, 0x1
	L_af_1:
	lwz r0, 0x0(r3)
	cmpw r6, r0
	blt L_af_2
	blr
}

asm void mapPauseAnimationAll(const char* name) {
	nofralloc
	lwz r0, activeGroup(r13)
	li r6, 0x0
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	mr r4, r3
	b L_af_1
	L_af_2:
	lwz r7, 0x164(r4)
	li r5, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r7)
	addi r5, r5, 0x1
	ori r0, r0, 0x10
	sth r0, 0x0(r7)
	addi r7, r7, 0x20
	L_af_3:
	lwz r0, 0x160(r4)
	cmpw r5, r0
	blt L_af_4
	addi r4, r4, 0x178
	addi r6, r6, 0x1
	L_af_1:
	lwz r0, 0x0(r3)
	cmpw r6, r0
	blt L_af_2
	blr
}

asm void mapReStartAnimation(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	li r30, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	mr r27, r28
	b L_af_1
	L_af_2:
	lwz r31, 0x164(r27)
	li r29, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq L_af_5
	lwz r3, 0x18(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	b L_af_6
	L_af_5:
	addi r29, r29, 0x1
	addi r31, r31, 0x20
	L_af_3:
	lwz r0, 0x160(r27)
	cmpw r29, r0
	blt L_af_4
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_1:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_2
	li r31, 0x0
	L_af_6:
	cmplwi r31, 0x0
	beq L_af_7
	lhz r0, 0x0(r31)
	ori r0, r0, 0x20
	sth r0, 0x0(r31)
	L_af_7:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapPauseAnimation(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	li r30, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r28, r3, r0
	mr r27, r28
	b L_af_1
	L_af_2:
	lwz r31, 0x164(r27)
	li r29, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq L_af_5
	lwz r3, 0x18(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	b L_af_6
	L_af_5:
	addi r29, r29, 0x1
	addi r31, r31, 0x20
	L_af_3:
	lwz r0, 0x160(r27)
	cmpw r29, r0
	blt L_af_4
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	L_af_1:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt L_af_2
	li r31, 0x0
	L_af_6:
	cmplwi r31, 0x0
	beq L_af_7
	lhz r0, 0x0(r31)
	ori r0, r0, 0x10
	sth r0, 0x0(r31)
	L_af_7:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void mapPlayAnimationLv(const char* name, s32 a, s32 b) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r23, 0x1c(r1)
	mr r23, r3
	mr r30, r4
	mr r24, r5
	li r31, 0x0
	li r25, 0x0
	li r26, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r29, r3, r0
	mr r28, r29
	b L_af_1
	L_af_2:
	lwz r31, 0x164(r28)
	li r27, 0x0
	b L_af_3
	L_af_4:
	lwz r3, 0x18(r31)
	mr r4, r23
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	li r25, 0x1
	b L_af_6
	L_af_5:
	addi r27, r27, 0x1
	addi r31, r31, 0x20
	L_af_3:
	lwz r0, 0x160(r28)
	cmpw r27, r0
	blt L_af_4
	L_af_6:
	cmpwi r25, 0x0
	bne L_af_7
	addi r28, r28, 0x178
	addi r26, r26, 0x1
	L_af_1:
	lwz r0, 0x0(r29)
	cmpw r26, r0
	blt L_af_2
	L_af_7:
	cmpwi r25, 0x0
	beq L_af_8
	li r0, 0x0
	cmpwi r24, 0x2
	sth r0, 0x0(r31)
	beq L_af_9
	bge L_af_10
	cmpwi r24, 0x0
	beq L_af_11
	bge L_af_12
	b L_af_11
	L_af_10:
	cmpwi r24, 0x4
	beq L_af_13
	bge L_af_11
	b L_af_14
	L_af_12:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x100
	sth r0, 0x0(r31)
	b L_af_11
	L_af_9:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x200
	sth r0, 0x0(r31)
	b L_af_11
	L_af_14:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x400
	sth r0, 0x0(r31)
	b L_af_11
	L_af_13:
	lhz r0, 0x0(r31)
	ori r0, r0, 0x800
	sth r0, 0x0(r31)
	L_af_11:
	lhz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 23, 23
	beq L_af_15
	lwz r4, gp(r13)
	lwz r3, 0x48(r4)
	lwz r4, 0x4c(r4)
	b L_af_16
	L_af_15:
	rlwinm. r0, r3, 0, 22, 22
	beq L_af_17
	lwz r4, gp(r13)
	lwz r3, 0x50(r4)
	lwz r4, 0x54(r4)
	b L_af_16
	L_af_17:
	rlwinm. r0, r3, 0, 21, 21
	beq L_af_18
	lwz r4, gp(r13)
	lwz r3, 0x58(r4)
	lwz r4, 0x5c(r4)
	b L_af_16
	L_af_18:
	rlwinm. r0, r3, 0, 20, 20
	beq L_af_19
	lwz r4, gp(r13)
	lwz r3, 0x60(r4)
	lwz r4, 0x64(r4)
	b L_af_16
	L_af_19:
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq L_af_20
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	b L_af_16
	L_af_20:
	lwz r3, 0x40(r4)
	lwz r4, 0x44(r4)
	L_af_16:
	lis r6, 0x8000
	lis r5, 0x1062
	lwz r0, 0xf8(r6)
	addi r6, r5, 0x4dd3
	li r5, 0x0
	srwi r0, r0, 2
	mulhwu r0, r6, r0
	srwi r6, r0, 6
	bl __div2i
	stw r4, 0xc(r31)
	cmpwi r30, 0x1
	lfs f1, float_0_80419850(r2)
	stw r3, 0x8(r31)
	lfs f0, float_1_80419860(r2)
	stfs f1, 0x10(r31)
	stfs f0, 0x14(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x1
	sth r0, 0x0(r31)
	bne L_af_21
	lhz r0, 0x0(r31)
	ori r0, r0, 0x4
	sth r0, 0x0(r31)
	L_af_21:
	cmpwi r30, 0x2
	bne L_af_8
	lwz r4, gp(r13)
	lis r0, 0x4330
	lwz r5, 0x18(r31)
	lis r3, double_to_int_802c1998@ha
	lwz r4, 0x4(r4)
	stw r0, 0x8(r1)
	xoris r0, r4, 0x8000
	lfs f3, float_1000_80419874(r2)
	stw r0, 0xc(r1)
	lfs f2, 0x8(r5)
	lfd f1, double_to_int_802c1998@l(r3)
	lfd f0, 0x8(r1)
	fmuls f2, f3, f2
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl __cvt_dbl_usll
	lwz r0, 0xc(r31)
	lwz r5, 0x8(r31)
	subfc r0, r4, r0
	stw r0, 0xc(r31)
	subfe r0, r3, r5
	stw r0, 0x8(r31)
	L_af_8:
	lmw r23, 0x1c(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r24, 0x10(r1)
	mr r24, r3
	mr r29, r4
	mr r30, r5
	li r28, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r26, r3, r0
	mr r25, r26
	b L_af_1
	L_af_2:
	lwz r31, 0x164(r25)
	li r27, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq L_af_5
	lwz r3, 0x18(r31)
	mr r4, r24
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	b L_af_6
	L_af_5:
	addi r27, r27, 0x1
	addi r31, r31, 0x20
	L_af_3:
	lwz r0, 0x160(r25)
	cmpw r27, r0
	blt L_af_4
	addi r25, r25, 0x178
	addi r28, r28, 0x1
	L_af_1:
	lwz r0, 0x0(r26)
	cmpw r28, r0
	blt L_af_2
	li r31, 0x0
	L_af_6:
	li r0, 0x0
	lfs f0, float_0_80419850(r2)
	stw r0, 0x0(r29)
	cmplwi r31, 0x0
	stfs f0, 0x0(r30)
	beq L_af_7
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_8
	li r0, 0x1
	stw r0, 0x0(r29)
	L_af_8:
	lwz r4, gp(r13)
	lis r0, 0x4330
	lwz r6, 0x18(r31)
	lis r3, double_to_int_802c1998@ha
	lwz r5, 0x4(r4)
	addi r4, r3, double_to_int_802c1998@l
	lfs f1, 0x8(r6)
	xoris r3, r5, 0x8000
	lfs f0, 0x10(r31)
	stw r3, 0xc(r1)
	fsubs f2, f1, f0
	lfs f3, float_1000_80419874(r2)
	stw r0, 0x8(r1)
	lfd f1, 0x0(r4)
	lfd f0, 0x8(r1)
	fmuls f2, f3, f2
	fsubs f0, f0, f1
	fdivs f0, f2, f0
	stfs f0, 0x0(r30)
	b L_af_9
	L_af_7:
	li r0, 0x1
	stw r0, 0x0(r29)
	L_af_9:
	lmw r24, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm MapEntryAnimData* mapSearchAnmObj(const char* animName) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	li r28, 0x0
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r31, r3, r0
	mr r30, r31
	b L_af_1
	L_af_2:
	lwz r27, 0x164(r30)
	li r29, 0x0
	b L_af_3
	L_af_4:
	lhz r0, 0x0(r27)
	clrlwi. r0, r0, 31
	beq L_af_5
	lwz r3, 0x18(r27)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	mr r3, r27
	b L_af_6
	L_af_5:
	addi r29, r29, 0x1
	addi r27, r27, 0x20
	L_af_3:
	lwz r0, 0x160(r30)
	cmpw r29, r0
	blt L_af_4
	addi r30, r30, 0x178
	addi r28, r28, 0x1
	L_af_1:
	lwz r0, 0x0(r31)
	cmpw r28, r0
	blt L_af_2
	li r3, 0x0
	L_af_6:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void makeDisplayList(BOOL group) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r18, 0x8(r1)
	mr r18, r3
	lis r3, 0x1
	lwz r0, activeGroup(r13)
	lwz r4, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r31, r4, r0
	bl _mapAlloc
	mulli r27, r18, 0x178
	li r0, 0x1
	stw r0, __mapdrv_make_dl(r13)
	li r22, 0x0
	mr r26, r3
	add r28, r31, r27
	li r23, 0x0
	L_af_1:
	lwz r20, 0x154(r28)
	li r0, 0x0
	li r25, 0x0
	stw r0, 0xf4(r20)
	stw r0, 0x114(r20)
	stw r0, 0xf8(r20)
	stw r0, 0x118(r20)
	stw r0, 0xfc(r20)
	stw r0, 0x11c(r20)
	stw r0, 0x100(r20)
	stw r0, 0x120(r20)
	stw r0, 0x104(r20)
	stw r0, 0x124(r20)
	stw r0, 0x108(r20)
	stw r0, 0x128(r20)
	stw r0, 0x10c(r20)
	stw r0, 0x12c(r20)
	stw r0, 0x110(r20)
	stw r0, 0x130(r20)
	b L_af_2
	L_af_3:
	lwz r3, 0x8(r20)
	lwz r0, 0x5c(r3)
	cmpwi r0, 0x1
	blt L_af_4
	cmpwi r0, 0x8
	bgt L_af_4
	lwz r3, 0x58(r3)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 28, 28
	bne L_af_4
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	bne L_af_4
	bl shadowGetCharShadowProjection
	cmpwi r3, 0x0
	beq L_af_5
	lwz r0, 0x0(r20)
	rlwinm. r0, r0, 0, 29, 29
	bne L_af_4
	L_af_5:
	lhz r0, 0x4(r28)
	rlwinm. r0, r0, 0, 16, 16
	beq L_af_4
	lis r3, g5_culling_s678@ha
	mr r29, r20
	addi r19, r3, g5_culling_s678@l
	li r24, 0x0
	li r30, 0x0
	b L_af_6
	L_af_7:
	addi r0, r30, 0x60
	mr r3, r26
	lwzx r18, r4, r0
	li r4, 0x0
	lis r5, 0x1
	bl memset
	mr r3, r26
	lis r4, 0x1
	bl DCInvalidateRange
	mr r3, r26
	lis r4, 0x1
	bl GXBeginDisplayList
	bl GXResetWriteGatherPipe
	mr r3, r20
	mr r4, r18
	bl mapSetMaterial
	lwz r3, 0x8(r20)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	slwi r0, r0, 2
	lwzx r3, r19, r0
	bl GXSetCullMode
	bl GXEndDisplayList
	cmpwi r23, 0x0
	stw r3, 0x114(r29)
	bne L_af_8
	lwz r0, 0x114(r29)
	add r22, r22, r0
	b L_af_9
	L_af_8:
	stw r21, 0xf4(r29)
	mr r4, r26
	lwz r5, 0x114(r29)
	lwz r3, 0xf4(r29)
	add r21, r21, r5
	bl memcpy
	lwz r3, 0xf4(r29)
	lwz r4, 0x114(r29)
	bl DCFlushRange
	L_af_9:
	addi r30, r30, 0x8
	addi r29, r29, 0x4
	addi r24, r24, 0x1
	L_af_6:
	lwz r4, 0x8(r20)
	lwz r0, 0x5c(r4)
	cmpw r24, r0
	blt L_af_7
	L_af_4:
	addi r25, r25, 0x1
	addi r20, r20, 0x134
	L_af_2:
	lwz r0, 0x150(r28)
	cmpw r25, r0
	blt L_af_3
	cmpwi r23, 0x0
	bne L_af_10
	stw r22, 0x168(r28)
	lwz r3, 0x168(r28)
	cmplwi r3, 0x0
	beq L_af_11
	bl _mapAllocTail
	stw r3, 0x16c(r28)
	lwz r21, 0x16c(r28)
	b L_af_10
	L_af_11:
	add r3, r31, r27
	li r0, 0x0
	stw r0, 0x16c(r3)
	b L_af_12
	L_af_10:
	addi r23, r23, 0x1
	cmpwi r23, 0x2
	blt L_af_1
	L_af_12:
	mr r3, r26
	bl _mapFree
	li r0, 0x0
	stw r0, __mapdrv_make_dl(r13)
	lmw r18, 0x8(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	mr r27, r4
	mr r28, r5
	lwz r0, activeGroup(r13)
	lwz r6, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r31, r6, r0
	bl mapGetJoints
	mulli r30, r28, 0x178
	add r4, r31, r30
	stw r3, 0x150(r4)
	lwz r0, 0x150(r4)
	mulli r3, r0, 0x134
	addi r0, r3, 0x1f
	clrrwi r29, r0, 5
	mr r3, r29
	bl _mapAlloc
	add r6, r31, r30
	mr r5, r29
	stw r3, 0x154(r6)
	li r4, 0x0
	lwz r3, 0x154(r6)
	bl memset
	mr r3, r26
	mr r5, r27
	mr r7, r28
	li r4, 0x0
	li r6, 0x1
	bl mapEntrySub
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r21, 0x14(r1)
	mr r30, r7
	mr r29, r6
	mr r26, r3
	mr r27, r4
	mr r28, r5
	mr r6, r30
	bl _mapEnt
	lwz r22, 0xc(r26)
	mr r31, r3
	cmplwi r22, 0x0
	beq L_af_1
	mr r3, r22
	mr r4, r31
	mr r6, r30
	addi r5, r31, 0x1c
	bl _mapEnt
	lwz r21, 0xc(r22)
	mr r25, r3
	cmplwi r21, 0x0
	beq L_af_2
	addi r23, r25, 0x1c
	mr r3, r21
	mr r4, r25
	mr r6, r30
	mr r5, r23
	bl _mapEnt
	lwz r0, 0xc(r21)
	mr r24, r3
	cmplwi r0, 0x0
	beq L_af_3
	mr r3, r0
	mr r4, r24
	mr r7, r30
	addi r5, r24, 0x1c
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe4(r24)
	L_af_3:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq L_af_4
	mr r4, r25
	mr r5, r23
	mr r7, r30
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe8(r24)
	L_af_4:
	stw r24, 0xe4(r25)
	L_af_2:
	lwz r21, 0x10(r22)
	cmplwi r21, 0x0
	beq L_af_5
	mr r3, r21
	mr r4, r31
	mr r6, r30
	addi r5, r31, 0x1c
	bl _mapEnt
	lwz r0, 0xc(r21)
	mr r23, r3
	cmplwi r0, 0x0
	beq L_af_6
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0x1c
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe4(r23)
	L_af_6:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq L_af_7
	mr r4, r31
	mr r7, r30
	addi r5, r31, 0x1c
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe8(r23)
	L_af_7:
	stw r23, 0xe8(r25)
	L_af_5:
	stw r25, 0xe4(r31)
	L_af_1:
	cmpwi r29, 0x0
	bne L_af_8
	lwz r21, 0x10(r26)
	cmplwi r21, 0x0
	beq L_af_8
	mr r3, r21
	mr r4, r27
	mr r5, r28
	mr r6, r30
	bl _mapEnt
	lwz r22, 0xc(r21)
	mr r25, r3
	cmplwi r22, 0x0
	beq L_af_9
	addi r24, r25, 0x1c
	mr r3, r22
	mr r4, r25
	mr r6, r30
	mr r5, r24
	bl _mapEnt
	lwz r0, 0xc(r22)
	mr r23, r3
	cmplwi r0, 0x0
	beq L_af_10
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0x1c
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe4(r23)
	L_af_10:
	lwz r3, 0x10(r22)
	cmplwi r3, 0x0
	beq L_af_11
	mr r4, r25
	mr r5, r24
	mr r7, r30
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe8(r23)
	L_af_11:
	stw r23, 0xe4(r25)
	L_af_9:
	lwz r21, 0x10(r21)
	cmplwi r21, 0x0
	beq L_af_12
	mr r3, r21
	mr r4, r27
	mr r5, r28
	mr r6, r30
	bl _mapEnt
	lwz r0, 0xc(r21)
	mr r23, r3
	cmplwi r0, 0x0
	beq L_af_13
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0x1c
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe4(r23)
	L_af_13:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq L_af_14
	mr r4, r27
	mr r5, r28
	mr r7, r30
	li r6, 0x0
	bl mapEntrySub
	stw r3, 0xe8(r23)
	L_af_14:
	stw r23, 0xe8(r25)
	L_af_12:
	stw r25, 0xe8(r31)
	L_af_8:
	mr r3, r31
	lmw r21, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	mulli r8, r6, 0x178
	stw r0, 0x124(r1)
	stw r31, 0x11c(r1)
	stw r30, 0x118(r1)
	mr r30, r4
	stw r29, 0x114(r1)
	mr r29, r3
	stw r28, 0x110(r1)
	mr r28, r5
	lwz r0, activeGroup(r13)
	lwz r7, mapWork(r13)
	mulli r3, r0, 0x2f4
	addi r0, r8, 0x150
	add r4, r7, r3
	lwzx r0, r4, r0
	add r3, r4, r8
	lwz r31, 0x154(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble L_af_1
	L_af_2:
	lwz r0, 0x8(r31)
	cmplwi r0, 0x0
	beq L_af_1
	addi r31, r31, 0x134
	bdnz L_af_2
	L_af_1:
	li r0, 0x0
	addi r3, r1, 0xe0
	stw r0, 0x0(r31)
	stw r29, 0x8(r31)
	sth r6, 0xde(r31)
	lfs f1, 0x30(r29)
	lfs f2, 0x34(r29)
	lfs f3, 0x38(r29)
	bl PSMTXTrans
	lfs f1, 0x18(r29)
	addi r3, r1, 0xb0
	lfs f2, 0x1c(r29)
	lfs f3, 0x20(r29)
	bl PSMTXScale
	lfs f1, float_deg2rad_80419868(r2)
	addi r3, r1, 0x80
	lfs f0, 0x24(r29)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_80419868(r2)
	addi r3, r1, 0x50
	lfs f0, 0x28(r29)
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_80419868(r2)
	addi r3, r1, 0x20
	lfs f0, 0x2c(r29)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xe0
	addi r4, r1, 0x20
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xe0
	addi r4, r1, 0x50
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xe0
	addi r4, r1, 0x80
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xe0
	addi r4, r1, 0xb0
	addi r5, r31, 0x4c
	bl PSMTXConcat
	mr r3, r28
	addi r4, r31, 0x4c
	addi r5, r31, 0x1c
	bl PSMTXConcat
	addi r3, r31, 0xac
	bl PSMTXIdentity
	lwz r5, 0x0(r31)
	li r4, 0x4
	li r3, -0x1
	li r0, 0x0
	ori r5, r5, 0x200
	stw r5, 0x0(r31)
	stb r4, 0x5(r31)
	sth r3, 0xdc(r31)
	stw r30, 0xe0(r31)
	stw r0, 0xe8(r31)
	stw r0, 0xe4(r31)
	lwz r3, 0x58(r29)
	cmplwi r3, 0x0
	beq L_af_3
	lbz r0, 0x2(r3)
	clrlwi. r0, r0, 31
	beq L_af_4
	lwz r0, 0x0(r31)
	ori r0, r0, 0x8
	stw r0, 0x0(r31)
	L_af_4:
	lwz r3, 0x58(r29)
	lbz r0, 0x0(r3)
	cmpwi r0, 0x2
	beq L_af_5
	bge L_af_6
	cmpwi r0, 0x0
	beq L_af_7
	bge L_af_8
	b L_af_9
	L_af_6:
	cmpwi r0, 0x4
	bge L_af_9
	b L_af_10
	L_af_7:
	lwz r8, 0x8(r31)
	li r9, 0x0
	mr r6, r9
	li r11, 0x0
	lwz r7, 0x5c(r8)
	li r12, 0x0
	b L_af_11
	L_af_12:
	addi r0, r6, 0x60
	lwzx r3, r8, r0
	lbz r0, 0xa(r3)
	cmplwi r0, 0x2
	bne L_af_13
	addi r11, r11, 0x1
	b L_af_14
	L_af_13:
	cmplwi r0, 0x1
	bne L_af_14
	addi r12, r12, 0x1
	L_af_14:
	li r0, 0x2
	addi r4, r6, 0x60
	li r10, 0x0
	li r5, 0x0
	mtctr r0
	L_af_15:
	lwzx r3, r8, r4
	addi r0, r5, 0xc
	lwzx r3, r3, r0
	cmplwi r3, 0x0
	beq L_af_16
	lbz r0, 0xa(r3)
	cmplwi r0, 0x2
	bne L_af_17
	addi r11, r11, 0x1
	b L_af_18
	L_af_17:
	cmplwi r0, 0x1
	bne L_af_18
	addi r12, r12, 0x1
	L_af_18:
	lwzx r3, r8, r4
	addi r0, r5, 0x10
	lwzx r3, r3, r0
	cmplwi r3, 0x0
	beq L_af_16
	lbz r0, 0xa(r3)
	cmplwi r0, 0x2
	bne L_af_19
	addi r11, r11, 0x1
	b L_af_20
	L_af_19:
	cmplwi r0, 0x1
	bne L_af_20
	addi r12, r12, 0x1
	L_af_20:
	lwzx r3, r8, r4
	addi r0, r5, 0x14
	lwzx r3, r3, r0
	cmplwi r3, 0x0
	beq L_af_16
	lbz r0, 0xa(r3)
	cmplwi r0, 0x2
	bne L_af_21
	addi r11, r11, 0x1
	b L_af_22
	L_af_21:
	cmplwi r0, 0x1
	bne L_af_22
	addi r12, r12, 0x1
	L_af_22:
	lwzx r3, r8, r4
	addi r0, r5, 0x18
	lwzx r3, r3, r0
	cmplwi r3, 0x0
	beq L_af_16
	lbz r0, 0xa(r3)
	cmplwi r0, 0x2
	bne L_af_23
	addi r11, r11, 0x1
	b L_af_24
	L_af_23:
	cmplwi r0, 0x1
	bne L_af_24
	addi r12, r12, 0x1
	L_af_24:
	addi r5, r5, 0x10
	addi r10, r10, 0x3
	bdnz L_af_15
	L_af_16:
	addi r6, r6, 0x8
	addi r9, r9, 0x1
	L_af_11:
	cmpw r9, r7
	blt L_af_12
	cmpwi r11, 0x0
	beq L_af_25
	li r0, 0x2
	stb r0, 0x4(r31)
	b L_af_9
	L_af_25:
	cmpwi r12, 0x0
	beq L_af_26
	li r0, 0x1
	stb r0, 0x4(r31)
	b L_af_9
	L_af_26:
	li r0, 0x0
	stb r0, 0x4(r31)
	b L_af_9
	L_af_8:
	lwz r0, 0x0(r31)
	li r3, 0x0
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_27
	li r3, 0x3
	L_af_27:
	stb r3, 0x4(r31)
	b L_af_9
	L_af_5:
	lwz r0, 0x0(r31)
	li r3, 0x1
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_28
	li r3, 0x4
	L_af_28:
	stb r3, 0x4(r31)
	b L_af_9
	L_af_10:
	lwz r0, 0x0(r31)
	li r3, 0x2
	rlwinm. r0, r0, 0, 28, 28
	beq L_af_29
	li r3, 0x5
	L_af_29:
	stb r3, 0x4(r31)
	L_af_9:
	lwz r3, 0x58(r29)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq L_af_30
	lwz r0, 0x0(r31)
	ori r0, r0, 0x10
	stw r0, 0x0(r31)
	lwz r3, 0x58(r29)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_af_31
	lwz r0, 0x0(r31)
	ori r0, r0, 0x8000
	stw r0, 0x0(r31)
	L_af_31:
	lwz r3, 0x58(r29)
	lbz r0, 0x0(r3)
	cmpwi r0, 0x2
	beq L_af_32
	bge L_af_33
	cmpwi r0, 0x0
	beq L_af_34
	bge L_af_35
	b L_af_33
	b L_af_33
	L_af_34:
	li r0, 0x2
	stb r0, 0x4(r31)
	b L_af_30
	L_af_35:
	li r0, 0x0
	stb r0, 0x4(r31)
	b L_af_30
	L_af_32:
	li r0, 0x1
	stb r0, 0x4(r31)
	b L_af_30
	L_af_33:
	li r0, 0x2
	stb r0, 0x4(r31)
	L_af_30:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq L_af_36
	cmplwi r30, 0x0
	beq L_af_37
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 27, 27
	bne L_af_38
	rlwinm. r0, r3, 0, 26, 26
	beq L_af_37
	L_af_38:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r31)
	b L_af_37
	L_af_36:
	cmplwi r30, 0x0
	beq L_af_37
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 27, 27
	bne L_af_39
	rlwinm. r0, r3, 0, 26, 26
	beq L_af_37
	L_af_39:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x20
	stw r0, 0x0(r31)
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 16, 16
	beq L_af_37
	lwz r0, 0x0(r31)
	ori r0, r0, 0x8000
	stw r0, 0x0(r31)
	L_af_37:
	lwz r3, 0x58(r29)
	lbz r0, 0x2(r3)
	rlwinm. r0, r0, 0, 29, 29
	beq L_af_40
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	b L_af_40
	L_af_3:
	lis r3, str_802C1A50@ha
	lis r5, str_802C1A5C@ha
	addi r3, r3, str_802C1A50@l
	li r4, 0x2e5
	addi r5, r5, str_802C1A5C@l
	crclr 6
	bl OSPanic
	L_af_40:
	lwz r0, 0x5c(r29)
	cmpwi r0, 0x0
	beq L_af_41
	addi r3, r29, 0x3c
	addi r4, r29, 0x48
	addi r5, r31, 0x10
	bl PSVECAdd
	addi r3, r31, 0x10
	lfs f1, float_0p5_80419854(r2)
	mr r4, r3
	bl PSVECScale
	b L_af_42
	L_af_41:
	lwz r3, 0x30(r29)
	lwz r0, 0x34(r29)
	stw r3, 0x10(r31)
	stw r0, 0x14(r31)
	lwz r0, 0x38(r29)
	stw r0, 0x18(r31)
	L_af_42:
	lwz r0, 0x5c(r29)
	cmpwi r0, 0x0
	beq L_af_43
	addi r3, r31, 0x1c
	addi r4, r31, 0x10
	addi r5, r1, 0x14
	bl PSMTXMultVec
	addi r3, r31, 0x1c
	addi r4, r29, 0x48
	addi r5, r1, 0x8
	bl PSMTXMultVec
	addi r3, r1, 0x14
	addi r4, r1, 0x8
	bl PSVECSquareDistance
	lfs f0, float_20000_804198d8(r2)
	fcmpo cr0, f1, f0
	bge L_af_43
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	L_af_43:
	lwz r0, 0x124(r1)
	mr r3, r31
	lwz r31, 0x11c(r1)
	lwz r30, 0x118(r1)
	lwz r29, 0x114(r1)
	lwz r28, 0x110(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r20, 0x10(r1)
	mr r23, r3
	mr r24, r4
	mr r25, r5
	li r29, 0x0
	li r30, 0x0
	b L_af_1
	L_af_2:
	addi r0, r30, 0x60
	li r28, 0x0
	lwzx r27, r3, r0
	mr r31, r27
	b L_af_3
	L_af_4:
	lwz r26, 0xc(r31)
	mr r20, r25
	li r22, 0x0
	lwz r3, 0x0(r26)
	lwz r21, 0x0(r3)
	b L_af_5
	L_af_6:
	lwz r3, 0x4(r20)
	mr r4, r21
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_7
	b L_af_8
	L_af_7:
	addi r20, r20, 0x4
	addi r22, r22, 0x1
	L_af_5:
	lwz r0, 0x0(r25)
	cmpw r22, r0
	blt L_af_6
	li r22, -0x1
	L_af_8:
	cmpwi r22, -0x1
	mr r4, r22
	bne L_af_9
	li r4, 0x0
	L_af_9:
	mr r3, r24
	bl TEXGet
	lwz r5, 0x0(r3)
	lwz r4, 0x0(r26)
	lwz r0, 0x8(r5)
	stw r0, 0xc(r4)
	lwz r5, 0x0(r3)
	lwz r4, 0x0(r26)
	lhz r0, 0x2(r5)
	sth r0, 0x8(r4)
	lwz r5, 0x0(r3)
	lwz r4, 0x0(r26)
	lhz r0, 0x0(r5)
	sth r0, 0xa(r4)
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	cmplwi r0, 0xe
	bgt L_af_10
	lis r3, jumptable_80303414@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80303414@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_af_11:
	lwz r3, 0x0(r26)
	li r0, 0x0
	stb r0, 0x4(r3)
	b L_af_10
	L_af_12:
	lwz r3, 0x0(r26)
	li r0, 0x1
	stb r0, 0x4(r3)
	b L_af_10
	L_af_13:
	lwz r3, 0x0(r26)
	li r0, 0x2
	stb r0, 0x4(r3)
	b L_af_10
	L_af_14:
	lwz r3, 0x0(r26)
	li r0, 0x3
	stb r0, 0x4(r3)
	b L_af_10
	L_af_15:
	lwz r3, 0x0(r26)
	li r0, 0x4
	stb r0, 0x4(r3)
	b L_af_10
	L_af_16:
	lwz r3, 0x0(r26)
	li r0, 0x5
	stb r0, 0x4(r3)
	b L_af_10
	L_af_17:
	lwz r3, 0x0(r26)
	li r0, 0x6
	stb r0, 0x4(r3)
	b L_af_10
	L_af_18:
	lwz r3, 0x0(r26)
	li r0, 0x7
	stb r0, 0x4(r3)
	b L_af_10
	L_af_19:
	lwz r3, 0x0(r26)
	li r0, 0x8
	stb r0, 0x4(r3)
	b L_af_10
	L_af_20:
	lwz r3, 0x0(r26)
	li r0, 0x9
	stb r0, 0x4(r3)
	b L_af_10
	L_af_21:
	lwz r3, 0x0(r26)
	li r0, 0xa
	stb r0, 0x4(r3)
	L_af_10:
	addi r31, r31, 0x4
	addi r28, r28, 0x1
	L_af_3:
	lbz r0, 0xb(r27)
	cmpw r28, r0
	blt L_af_4
	addi r30, r30, 0x8
	addi r29, r29, 0x1
	L_af_1:
	lwz r3, 0x8(r23)
	lwz r0, 0x5c(r3)
	cmpw r29, r0
	blt L_af_2
	lwz r3, 0xe4(r23)
	cmplwi r3, 0x0
	beq L_af_22
	mr r4, r24
	mr r5, r25
	bl mapBuildTexture
	L_af_22:
	lwz r3, 0xe8(r23)
	cmplwi r3, 0x0
	beq L_af_23
	mr r4, r24
	mr r5, r25
	bl mapBuildTexture
	L_af_23:
	lmw r20, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void mapInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	li r4, 0x5e8
	stw r0, 0x14(r1)
	bl __memAlloc
	stw r3, mapWork(r13)
	li r4, 0x0
	li r5, 0x5e8
	bl memset
	li r0, 0x0
	stw r0, activeGroup(r13)
	stw r0, mapClipOffFlag(r13)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapGetBoundingBox(Vec* min, Vec* max) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r5, vec3_802c16d8@ha
	stw r0, 0x34(r1)
	addi r7, r5, vec3_802c16d8@l
	lis r5, vec3_802c16e4@ha
	stmw r27, 0x1c(r1)
	mr r30, r3
	mr r31, r4
	li r27, 0x0
	lwz r0, activeGroup(r13)
	lwz r9, mapWork(r13)
	mulli r8, r0, 0x2f4
	lwz r6, 0x0(r7)
	lwz r0, 0x4(r7)
	stw r6, 0x0(r3)
	add r29, r9, r8
	stw r0, 0x4(r3)
	lwz r0, 0x8(r7)
	stw r0, 0x8(r3)
	lwzu r3, vec3_802c16e4@l(r5)
	lwz r0, 0x4(r5)
	stw r3, 0x0(r4)
	stw r0, 0x4(r4)
	lwz r0, 0x8(r5)
	stw r0, 0x8(r4)
	lwz r28, 0x154(r29)
	b L_af_1
	L_af_2:
	lwz r4, 0x8(r28)
	cmplwi r4, 0x0
	beq L_af_3
	lwz r0, 0x5c(r4)
	cmpwi r0, 0x0
	beq L_af_3
	addi r3, r28, 0x1c
	addi r4, r4, 0x3c
	addi r5, r1, 0x8
	bl PSMTXMultVec
	lfs f0, 0x0(r30)
	lfs f1, 0x8(r1)
	fcmpo cr0, f0, f1
	ble L_af_4
	stfs f1, 0x0(r30)
	L_af_4:
	lfs f0, 0x4(r30)
	lfs f1, 0xc(r1)
	fcmpo cr0, f0, f1
	ble L_af_5
	stfs f1, 0x4(r30)
	L_af_5:
	lfs f0, 0x8(r30)
	lfs f1, 0x10(r1)
	fcmpo cr0, f0, f1
	ble L_af_6
	stfs f1, 0x8(r30)
	L_af_6:
	lfs f0, 0x0(r31)
	lfs f1, 0x8(r1)
	fcmpo cr0, f0, f1
	bge L_af_7
	stfs f1, 0x0(r31)
	L_af_7:
	lfs f0, 0x4(r31)
	lfs f1, 0xc(r1)
	fcmpo cr0, f0, f1
	bge L_af_8
	stfs f1, 0x4(r31)
	L_af_8:
	lfs f0, 0x8(r31)
	lfs f1, 0x10(r1)
	fcmpo cr0, f0, f1
	bge L_af_9
	stfs f1, 0x8(r31)
	L_af_9:
	lwz r4, 0x8(r28)
	addi r3, r28, 0x1c
	addi r5, r1, 0x8
	addi r4, r4, 0x48
	bl PSMTXMultVec
	lfs f0, 0x0(r30)
	lfs f1, 0x8(r1)
	fcmpo cr0, f0, f1
	ble L_af_10
	stfs f1, 0x0(r30)
	L_af_10:
	lfs f0, 0x4(r30)
	lfs f1, 0xc(r1)
	fcmpo cr0, f0, f1
	ble L_af_11
	stfs f1, 0x4(r30)
	L_af_11:
	lfs f0, 0x8(r30)
	lfs f1, 0x10(r1)
	fcmpo cr0, f0, f1
	ble L_af_12
	stfs f1, 0x8(r30)
	L_af_12:
	lfs f0, 0x0(r31)
	lfs f1, 0x8(r1)
	fcmpo cr0, f0, f1
	bge L_af_13
	stfs f1, 0x0(r31)
	L_af_13:
	lfs f0, 0x4(r31)
	lfs f1, 0xc(r1)
	fcmpo cr0, f0, f1
	bge L_af_14
	stfs f1, 0x4(r31)
	L_af_14:
	lfs f0, 0x8(r31)
	lfs f1, 0x10(r1)
	fcmpo cr0, f0, f1
	bge L_af_3
	stfs f1, 0x8(r31)
	L_af_3:
	addi r27, r27, 0x1
	addi r28, r28, 0x134
	L_af_1:
	lwz r0, 0x150(r29)
	cmpw r27, r0
	blt L_af_2
	lmw r27, 0x1c(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 mapGetJoints(MapFileJoint* joint) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmplwi r3, 0x0
	stw r0, 0x14(r1)
	li r0, 0x0
	stw r0, 0x8(r1)
	beq L_af_1
	li r0, 0x1
	stw r0, 0x8(r1)
	lwz r3, 0xc(r3)
	cmplwi r3, 0x0
	beq L_af_1
	addi r4, r1, 0x8
	bl mapGetJointsSub
	L_af_1:
	lwz r0, 0x14(r1)
	lwz r3, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void mapGetJointsSub(MapFileJoint* joint, s32* numJoints) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r30, r3
	mr r31, r4
	lwz r3, 0x0(r4)
	addi r0, r3, 0x1
	stw r0, 0x0(r4)
	lwz r29, 0xc(r30)
	cmplwi r29, 0x0
	beq L_af_1
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r28, 0xc(r29)
	cmplwi r28, 0x0
	beq L_af_2
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r27, 0xc(r28)
	cmplwi r27, 0x0
	beq L_af_3
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_4
	bl mapGetJointsSub
	L_af_4:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_3
	mr r4, r31
	bl mapGetJointsSub
	L_af_3:
	lwz r27, 0x10(r28)
	cmplwi r27, 0x0
	beq L_af_2
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_5
	mr r4, r31
	bl mapGetJointsSub
	L_af_5:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_2
	mr r4, r31
	bl mapGetJointsSub
	L_af_2:
	lwz r27, 0x10(r29)
	cmplwi r27, 0x0
	beq L_af_1
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r28, 0xc(r27)
	cmplwi r28, 0x0
	beq L_af_6
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r28)
	cmplwi r3, 0x0
	beq L_af_7
	mr r4, r31
	bl mapGetJointsSub
	L_af_7:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_6
	mr r4, r31
	bl mapGetJointsSub
	L_af_6:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_1
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_8
	mr r4, r31
	bl mapGetJointsSub
	L_af_8:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_1
	mr r4, r31
	bl mapGetJointsSub
	L_af_1:
	lwz r27, 0x10(r30)
	cmplwi r27, 0x0
	beq L_af_9
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r28, 0xc(r27)
	cmplwi r28, 0x0
	beq L_af_10
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r29, 0xc(r28)
	cmplwi r29, 0x0
	beq L_af_11
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r29)
	cmplwi r3, 0x0
	beq L_af_12
	mr r4, r31
	bl mapGetJointsSub
	L_af_12:
	lwz r3, 0x10(r29)
	cmplwi r3, 0x0
	beq L_af_11
	mr r4, r31
	bl mapGetJointsSub
	L_af_11:
	lwz r28, 0x10(r28)
	cmplwi r28, 0x0
	beq L_af_10
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r28)
	cmplwi r3, 0x0
	beq L_af_13
	mr r4, r31
	bl mapGetJointsSub
	L_af_13:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_10
	mr r4, r31
	bl mapGetJointsSub
	L_af_10:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_9
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r28, 0xc(r27)
	cmplwi r28, 0x0
	beq L_af_14
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r28)
	cmplwi r3, 0x0
	beq L_af_15
	mr r4, r31
	bl mapGetJointsSub
	L_af_15:
	lwz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_af_14
	mr r4, r31
	bl mapGetJointsSub
	L_af_14:
	lwz r27, 0x10(r27)
	cmplwi r27, 0x0
	beq L_af_9
	lwz r3, 0x0(r31)
	addi r0, r3, 0x1
	stw r0, 0x0(r31)
	lwz r3, 0xc(r27)
	cmplwi r3, 0x0
	beq L_af_16
	mr r4, r31
	bl mapGetJointsSub
	L_af_16:
	lwz r3, 0x10(r27)
	cmplwi r3, 0x0
	beq L_af_9
	mr r4, r31
	bl mapGetJointsSub
	L_af_9:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 mapGetActiveGroup(void) {
	nofralloc
	lwz r3, activeGroup(r13)
	blr
}

asm MapWork* mapGetWork(void) {
	nofralloc
	lwz r0, activeGroup(r13)
	lwz r3, mapWork(r13)
	mulli r0, r0, 0x2f4
	add r3, r3, r0
	blr
}

asm void N_mapDispOn(void) {
	nofralloc
	li r0, 0x0
	stw r0, unk_80418458(r13)
	blr
}

asm void N_mapDispOff(void) {
	nofralloc
	li r0, 0x1
	stw r0, unk_80418458(r13)
	blr
}

asm const char* getMapDataDvdRoot(void) {
	nofralloc
	la r3, str_80419848(r2)
	blr
}

asm void mapErrorEntry(s32 arg0, const char* arg1) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, error_data@ha
	stw r0, 0x14(r1)
	addi r6, r5, error_data@l
	li r5, 0x1f
	lwz r0, error_count(r13)
	mulli r0, r0, 0x24
	add r6, r6, r0
	stw r3, 0x20(r6)
	mr r3, r6
	bl strncpy
	lwz r3, error_count(r13)
	li r0, 0x1
	stw r0, error_flag(r13)
	addi r3, r3, 0x1
	slwi r0, r3, 27
	stw r3, error_count(r13)
	srwi r3, r3, 31
	subf r0, r3, r0
	rotlwi r0, r0, 5
	add r0, r0, r3
	stw r0, error_count(r13)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_05_80303450_data[4] = {0};
#pragma force_active reset
