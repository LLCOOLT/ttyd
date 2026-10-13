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
#include <math.h>
#include <string.h>

extern f32 queen_uv[4]; //gxsub.c
extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);

#define TWO_PI 6.28318530717958647692528676655900576839433879875021f

//.bss
MapError error_data[32];

//.sbss
MapWork* mapWork; //allocates two entries
s32 activeGroup;
BOOL mapClipOffFlag;
MapObject* current_mp;
BOOL error_flag;
s32 error_count;
BOOL unk_80418458;
BOOL __mapdrv_make_dl;
Mtx projMtx;
void* projTexImgRef;
GXTexObj projTexObj;
GXColor paperCraft_ambient;
GXColor paper_ambient;

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

//.rodata
const GXTexMtx texmtx_tbl[10] = {GX_TEXMTX0, GX_TEXMTX1, GX_TEXMTX2, GX_TEXMTX3, GX_TEXMTX4, GX_TEXMTX5, GX_TEXMTX6, GX_TEXMTX7, GX_TEXMTX8, GX_TEXMTX9};
const s32 texfmt_tbl[11] = {4, 5, 6, 14, 0, 1, 2, 3, 8, 9, 10};
const s32 texwrap_tbl[3] = {GX_CLAMP, GX_REPEAT, GX_MIRROR};
const s32 palfmt_tbl[2] = {1, 2};
const GXLightID lightid_tbl[8] = {GX_LIGHT0, GX_LIGHT1, GX_LIGHT2, GX_LIGHT3, GX_LIGHT4, GX_LIGHT5, GX_LIGHT6, GX_LIGHT7};

LightEntry* lightGetPaper(void);
LightEntry* lightGetPaperCraft(void);
LightEntry* lightGetCharaAmbient(void);
s32 lightCheckCharaLight(void);
#define lightGetNearObj(pos, out, count, flags) ((s32 (*)(Vec*, LightEntry**, s32, LightEntryFlags))lightGetNearObj)(pos, out, count, flags)

//.sdata
f32 scrl_uv[4] = {0.0f, 0.0f, 0.0f, 0.0f};
s32 fog_type[5] = {2, 4, 5, 6, 7};

//local prototypes
void mapGetJointsSub(MapFileJoint* joint, s32* numJoints);
void mapGetBoundingBox(Vec* min, Vec* max);
void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table);
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index);
MapObject* mapEntrySub(MapFileJoint* joint, MapObject* parent, Mtx mtx, BOOL isRoot, s32 index);
MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index);
void makeDisplayList(BOOL group);
//anim functions?
void _mapLoad(MapWork* wp, BOOL group, const char* map);

void mapErrorEntry(s32 arg0, const char* arg1) { //1:1
	MapError* error = error_data;

	error += error_count;
	error->field_0x20 = arg0;
	strncpy(error->field_0x0, arg1, sizeof(error->field_0x0) - 1);
	error_flag = TRUE;
	error_count++;
	error_count %= 32;
}

const char* getMapDataDvdRoot(void) {
	return ".";
}

void N_mapDispOff(void) {
	unk_80418458 = TRUE;
}

void N_mapDispOn(void) {
	unk_80418458 = FALSE;
}

MapWork* mapGetWork(void) {
	return &mapWork[activeGroup];
}

s32 mapGetActiveGroup(void) {
	return activeGroup;
}

void mapGetJointsSub(MapFileJoint* joint, s32* numJoints) { //1:1
	(*numJoints)++;
	if (joint->child) {
		mapGetJointsSub(joint->child, numJoints);
	}
	if (joint->next) {
		mapGetJointsSub(joint->next, numJoints);
	}
}

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

void mapInit(void) {
	mapWork = __memAlloc(HEAP_DEFAULT, sizeof(MapWork) * 2);
	memset(mapWork, 0, sizeof(MapWork) * 2);
	activeGroup = 0;
	mapClipOffFlag = FALSE;
}

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

static inline s32 mapSearchTexName(MapTexTable* table, char* name) {
	s32 i;

	for (i = 0; i < table->count; i++) {
		if (strcmp(table->names[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

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

#pragma dont_inline on
MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	return NULL;




}

#pragma dont_inline reset
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

MapObject* mapEntry(MapFileJoint* joint, Mtx mtx, s32 index) {
	MapWork* wp = &mapWork[activeGroup];
	u32 size;

	wp->entries[index].numJoints = mapGetJoints(joint);
	size = OSRoundUp32B(wp->entries[index].numJoints * sizeof(MapObject));
	wp->entries[index].objects = _mapAlloc(size);
	memset(wp->entries[index].objects, 0, size);
	return mapEntrySub(joint, NULL, mtx, TRUE, index);
}

s32 shadowGetCharShadowProjection(void);
void mapSetMaterial(MapObject* obj, void* material);

typedef struct MapObjectDL {
	u8 field_0x0[0xF4];  // 0x0
	void* dl[8];         // 0xF4
	u32 dlSize[8];       // 0x114
} MapObjectDL;
#define MAPOBJ_DL(obj) (((MapObjectDL*)(obj))->dl)
#define MAPOBJ_DLSIZE(obj) (((MapObjectDL*)(obj))->dlSize)

void makeDisplayList(BOOL group) {
	static const GXCullMode culling[4] = {GX_CULL_FRONT, GX_CULL_BACK, GX_CULL_ALL, GX_CULL_NONE};
	MapWork* wp = &mapWork[activeGroup];
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
	__mapdrv_make_dl = TRUE;
	total = 0;
	for (pass = 0; pass < 2; pass++) {
		obj = wp->entries[group].objects;
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
			if (!(wp->entries[group].flags & 0x8000)) {
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
			MAPENT_FIELD(&wp->entries[group], u32, 0x168) = total;
			if (MAPENT_FIELD(&wp->entries[group], u32, 0x168)) {
				MAPENT_FIELD(&wp->entries[group], void*, 0x16C) = _mapAllocTail(MAPENT_FIELD(&wp->entries[group], u32, 0x168));
				dst = MAPENT_FIELD(&wp->entries[group], void*, 0x16C);
			}
			else {
				MAPENT_FIELD(&wp->entries[group], void*, 0x16C) = NULL;
				break;
			}
		}
	}
	_mapFree(buf);
	__mapdrv_make_dl = FALSE;
}

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

void mapPauseAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x10;
	}
}

void mapReStartAnimation(const char* name) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->flags |= 0x20;
	}
}

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

void mapSetPlayRate(const char* name, f32 rate) {
	MapAnim* anim = mapSearchAnmObj_inl(name);
	if (anim) {
		anim->rate = rate;
	}
}

void _mapLoad(MapWork* wp, BOOL group, const char* map) {
	MapHeader* header;
	MapEntry* entry;
	DVDEntry* dvd;
	char str1[128];
	char str2[128];
	char str3[128];
	u32 sizeCheck;
	u8 *data;
	u32 r4, r7, r0;
	int i;

	MapFileInfo* info;

	entry = &wp->entries[group];
	error_flag = FALSE;
	error_count = 0;
	strncpy(entry->name, map, sizeof(entry->name));

	sprintf(str1, "./m/%s/d", map);
	arcOpen(str1, &entry->dat, &entry->datSize);
	if (!entry->dat) {
		sprintf(str2, "%s/%s", ".", str1);
		dvd = DVDMgrOpen(str2, 2, 0);
		entry->datSize = DVDMgrGetLength(dvd);
		entry->dat = _mapAllocTail(OSRoundUp32B(entry->datSize));
		DVDMgrRead(dvd, entry->dat, OSRoundUp32B(entry->datSize), 0);
		DVDMgrClose(dvd);
	}

	sprintf(str1, "./m/%s/t", map);
	entry->tpl = NULL;
	arcOpen(str1, &entry->tpl, &entry->tplSize);
	if (entry->tpl) {
		UnpackTexPalette(entry->tpl);
	}
	else {
		sprintf(str3, "%s/%s", ".", str1);
		dvd = DVDMgrOpen(str3, 2, 0);
		if (dvd) {
			entry->tplSize = DVDMgrGetLength(dvd);
			entry->tpl = _mapAllocTail(OSRoundUp32B(entry->tplSize));
			DVDMgrRead(dvd, entry->tpl, OSRoundUp32B(entry->tplSize), 0);
			DVDMgrClose(dvd);
			UnpackTexPalette(entry->tpl);
		}
	}

	GXInvalidateVtxCache();
	header = &entry->header;
	data = (u8*)entry->dat;
	if (header != NULL) {
		memset(header, 0, sizeof(MapHeader));
		header->field_0x3C |= 1;
		memcpy(header, entry->dat, sizeof(MapFileHeader));
		if (header->file.fileSize == entry->datSize) {
			sizeCheck = sizeof(MapFileHeader);
			if (header->file.dataSize) {
				header->data = &data[sizeCheck];
				sizeCheck = header->file.dataSize + sizeof(MapFileHeader);
			}
			if (header->file.relCount) {
				header->rel = &data[sizeCheck];
				sizeCheck += 4 * header->file.relCount; //TODO: sizeof
			}
			if (header->file.chunkCount) {
				header->chunks = (MapFileChunk*)&data[sizeCheck];
				sizeCheck += sizeof(MapFileChunk) * header->file.chunkCount;
			}
			if (header->file.unused) {
				header->unused = &data[sizeCheck];
				sizeCheck += 8 * header->file.unused;
			}
			if (sizeCheck < header->file.fileSize) {
				header->strings = (const char*)&data[sizeCheck];
			}

			//iunno about this section
			for (i = 0; i < header->file.relCount; i++) {
				r4 = (u32)entry->header.rel;
				r7 = (u32)entry->header.data;
				r4 = *(u32*)(r4 + i);
				r0 = *(u32*)(r7 + r4);
				if (r0 <= 0x80000000) {
					*(u32*)(r7 + r4) = (r0 + r7);
				}
			}
		}
	}
	info = NULL;
	for (i = 0; i < header->file.chunkCount; i++) {
		if (!strcmp(&header->strings[header->chunks[i].string], "information")) {
			info = (MapFileInfo*)&data[header->chunks[i].offset];
			break;
		}
	}


}

void hitReInit(void);


void mapUnLoad(void) {
	MapEntry* entry2;
	MapEntry* entry;
	int i;
	MapWork* wp;

	sysWaitDrawSync();
	wp = mapWork;
	activeGroup = 0;
	for (i = 0, entry = wp->entries; i < wp->entries[0].count; entry++, i++) {
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
		if (MAPENT_FIELD(entry, void*, 0x16C)) {
			_mapFree(MAPENT_FIELD(entry, void*, 0x16C));
			MAPENT_FIELD(entry, void*, 0x16C) = NULL;
			MAPENT_FIELD(entry, s32, 0x168) = 0;
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
		if (MAPENT_FIELD(entry2, void*, 0x8C)) {
			_mapFree(MAPENT_FIELD(entry2, void*, 0x8C));
			MAPENT_FIELD(entry2, void*, 0x8C) = NULL;
		}
		strncpy(entry2->name, "", sizeof(entry2->name));
	}
	arcDelete(1);
	memset(wp, 0, sizeof(MapWork));
}

BOOL mapPreLoad(void) {
	return TRUE; //do nothing
}

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

void bmapUnLoad(void) {
	MapWork* wp0;
	MapEntry* entry2;
	MapEntry* entry;
	int i;
	MapWork* wp;


	sysWaitDrawSync();
	wp = &mapWork[1];
	activeGroup = 1;
	i = 0;
	for (entry = wp->entries; i < wp->entries[0].count; entry++, i++) {
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
		if (MAPENT_FIELD(entry, void*, 0x16C)) {
			_mapFree(MAPENT_FIELD(entry, void*, 0x16C));
			MAPENT_FIELD(entry, void*, 0x16C) = NULL;
			MAPENT_FIELD(entry, s32, 0x168) = 0;
		}
	}
	unk_80418458 = FALSE;
	hitReInit();
	lightReInit();
	envReInit();
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
		if (MAPENT_FIELD(entry2, void*, 0x8C)) {
			_mapFree(MAPENT_FIELD(entry2, void*, 0x8C));
			MAPENT_FIELD(entry2, void*, 0x8C) = NULL;
		}
		strncpy(entry2->name, "", sizeof(entry2->name));
	}
	arcDelete(1);
	arcDelete(2);
	memset(wp, 0, sizeof(MapWork));
	wp0 = mapWork;
	activeGroup = 0;
	for (i = 0, entry = wp0->entries; i < wp0->entries[0].count; entry++, i++) {


		if (MAPENT_FIELD(entry, void*, 0x170)) {
			entry->dat = _mapAllocTail(entry->datSize);
			entry->tpl = _mapAllocTail(entry->tplSize);
			aramMgrToMram(MAPENT_FIELD(entry, ARAMEntry*, 0x170), entry->dat);
			aramMgrToMram(MAPENT_FIELD(entry, ARAMEntry*, 0x178), entry->tpl);
			MAPENT_FIELD(entry, void*, 0x170) = NULL;
			MAPENT_FIELD(entry, void*, 0x178) = NULL;
		}
		else {
			MAPENT_FIELD(entry, void*, 0x8C) = _mapAllocTail(MAPENT_FIELD(entry, u32, 0x90));
			aramMgrToMram(MAPENT_FIELD(entry, ARAMEntry*, 0x174), MAPENT_FIELD(entry, void*, 0x8C));
			MAPENT_FIELD(entry, void*, 0x174) = NULL;
		}
		makeDisplayList(i);
	}
	if (MAPENT_FIELD(wp0->entries, void*, 0x8C)) {
		arcEntry(1, MAPENT_FIELD(wp0->entries, void*, 0x8C), MAPENT_FIELD(wp0->entries, u32, 0x90));

	}
}

void bmapLoad(const char* map, const char* map2) {
	MapWork* wp;
	MapEntry* entry;
	MapEntry* e;
	int i;

	sysWaitDrawSync();
	wp = mapWork;
	activeGroup = 0;
	for (i = 0, entry = wp->entries; i < wp->entries[0].count; i++, entry++) {
		e = &mapWork[activeGroup].entries[i];
		if (MAPENT_FIELD(e, void*, 0x16C)) {
			_mapFree(MAPENT_FIELD(e, void*, 0x16C));
		}
		MAPENT_FIELD(e, s32, 0x168) = 0;
		MAPENT_FIELD(e, void*, 0x16C) = NULL;
		MAPENT_FIELD(entry, void*, 0x170) = NULL;
		MAPENT_FIELD(entry, void*, 0x178) = NULL;
		MAPENT_FIELD(entry, void*, 0x174) = NULL;
		if (entry->dat) {
			if (!arcDataCheck(entry->dat)) {
				MAPENT_FIELD(entry, ARAMEntry*, 0x170) = aramMgrToAram(entry->dat, entry->datSize);
				MAPENT_FIELD(entry, ARAMEntry*, 0x178) = aramMgrToAram(entry->tpl, entry->tplSize);
				_mapFree(entry->tpl);
				_mapFree(entry->dat);
				entry->tpl = NULL;
				entry->dat = NULL;
			}
			else {
				MAPENT_FIELD(entry, ARAMEntry*, 0x174) = aramMgrToAram(MAPENT_FIELD(entry, void*, 0x8C), MAPENT_FIELD(entry, u32, 0x90));
				_mapFree(MAPENT_FIELD(entry, void*, 0x8C));
				MAPENT_FIELD(entry, void*, 0x8C) = NULL;
			}
		}
	}
	wp = &mapWork[1];
	activeGroup = 1;
	memset(wp, 0, sizeof(MapWork));
	_mapLoad(wp, 0, map);
	wp->entries[0].count = 1;
	if (map2) {
		_mapLoad(wp, 1, map2);
		wp->entries[0].count = 2;
	}
}

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
				v[c] = mapHermite(cur, k0->time, k1->time, k0->ch[c].value, k0->ch[c].tanOut, k1->ch[c].value, k1->ch[c].tanIn);
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

void mapMain(void) {



}

void _mapDispMapObj(CameraId cam, MapObject* obj);
void _mapDispMapGrp(CameraId cam, MapObject* obj);
void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj);
void mapSetPolygon(MapObject* obj, MapFileMesh* mesh);
extern const GXCullMode culling[4];
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetTextureMatrix(struct MapMaterial* mat);
void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh);

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

void _mapDispMapObj(CameraId cam, MapObject* obj) {
	CameraEntry* camera;
	CameraEntry* cur;
	MapWork* wp;
	MapFileJoint* joint;
	f32 scale;
	s32 n;
	s32 mode;
	GXCullMode cull;
	f32 d;
	Mtx mtx;
	Mtx nrm;
	f32 proj[7];
	int i;
	int j;
	void* material;
	MapFileMesh* mesh;

	camera = camGetPtr(cam);
	current_mp = obj;
	if (!(obj->flags & 0x20)) {
		goto setup;
	}
	if (obj->flags & 0x8000) {
		n = 0;
		for (joint = obj->joints; joint->prev; joint = joint->prev) {
		}
		for (; joint != obj->joints; joint = joint->next) {
			n++;
		}
		scale = 0.01f * n;
		GXGetProjectionv(proj);
		d = 1.0f * (camera->far + camera->near) * (1.0f + scale);
		proj[5] *= 1.0f + (scale * (-2.0f * camera->far * camera->near)) / d;
		GXSetProjectionv(proj);
	}
	mode = obj->blendMode;
	if (obj->joints->partCount > 0) {
		if (mapObjIsTranslucent(obj->flags, obj->color, *(GXColor*)((u8*)obj->joints->parts[0].material + 0x10C))) {
			mode = 2;
		}
	}
	switch (mode) {
		case 0:
			GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 7);
			GXSetZCompLoc(GX_TRUE);
			GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
			break;
		case 3:
			GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
			GXSetZCompLoc(GX_TRUE);
			GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
			GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
			break;
		case 1:
			GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
			GXSetZCompLoc(GX_FALSE);
			GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
			break;
		case 4:
			GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, 0);
			GXSetZCompLoc(GX_FALSE);
			GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
			GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
			break;
		case 2:
		case 5:
		default:
			GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, 0);
			GXSetZCompLoc(GX_TRUE);
			GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
			GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
			break;
	}
setup:
	if (cam == 1) {
		GXSetZCompLoc(GX_FALSE);
	}
	PSMTXConcat(camera->view, obj->modelWorldMtx, mtx);
	GXLoadPosMtxImm(mtx, 0);
	if (!(obj->flags & 0x100)) {
		PSMTXInvXpose(mtx, nrm);
		GXLoadNrmMtxImm(nrm, 0);
	}
	GXSetCurrentMtx(0);
	GXGetCullMode(&cull);
	if (cull != culling[obj->joints->drawMode->cullMode]) {
		GXSetCullMode(culling[obj->joints->drawMode->cullMode]);
	}
	cur = camGetCurPtr();
	wp = &mapWork[activeGroup];
	if ((wp->entries[0].flags & 1) && !(obj->flags & 0x80000)) {
		GXSetFog((GXFogType)fog_type[wp->entries[0].fogType], wp->entries[0].fogStart, wp->entries[0].fogEnd,
				 cur->near, cur->far, wp->entries[0].fogColor);
	}
	else {
		GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
	}
	if (obj->flags & 0x20) {
		if (obj->flags & 0x4000) {
			goto end;
		}
		if ((obj->flags & 1) && !(obj->flags & 0x80)) {
			goto end;
		}
		if ((obj->flags & 0x40) && obj->color.a == 0) {
			goto end;
		}
	}
	if (obj->flags & 0x100) {
		for (i = 0; i < obj->joints->partCount; i++) {
			material = obj->joints->parts[i].material;
			mesh = obj->joints->parts[i].mesh;
			mapSetTextureMatrix(material);
			mapSetMaterialLastStageBlend(obj->flags, obj->color, *(GXColor*)((u8*)material + 0x10C));
			mapSetPolygonVtxDesc(obj, mesh);
			GXCallDisplayList(MAPOBJ_DL(obj)[i], MAPOBJ_DLSIZE(obj)[i]);
			for (j = 0; j < mesh->displayListCount; j++) {
				GXCallDisplayList((void*)mesh->displayLists.packedLists[j].offset, *(u32*)&mesh->displayLists.packedLists[j].vertexCount);
			}
		}
	}
	else {
		for (i = 0; i < obj->joints->partCount; i++) {
			material = obj->joints->parts[i].material;
			mesh = obj->joints->parts[i].mesh;
			mapSetTextureMatrix(material);
			mapSetMaterialLastStageBlend(obj->flags, obj->color, *(GXColor*)((u8*)material + 0x10C));
			mapSetMaterial(obj, material);
			mapSetPolygon(obj, mesh);
		}
	}
end:
	if (obj->flags & 0x8000) {
		GXSetProjection(camera->projection, camera->projType);
	}
	if (obj->flags & 0x0F000000) {
		GXSetTevDirect(GX_TEVSTAGE0);
		GXSetTevDirect(GX_TEVSTAGE1);
		GXSetTevDirect(GX_TEVSTAGE2);
		GXSetTevDirect(GX_TEVSTAGE3);
		GXSetTevDirect(GX_TEVSTAGE4);
		GXSetNumIndStages(0);
	}
}


void _mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
	if (obj->child) {
		_mapDispMapGrp(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp(cam, obj->next);
	}
}

void mapDispMapObj(CameraId cam, MapObject* obj) {
	_mapDispMapObj(cam, obj);
}

void mapDispMapGrp(CameraId cam, MapObject* obj) {
	_mapDispMapGrp(cam, obj);
}

void mapDispMapObj_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapObj(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}

void mapDispMapGrp_off(CameraId cam, MapObject* obj) {
	u16 left, top, right, bottom;

	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&left, &top, &right, &bottom);
	offscreenAddBoundingBox(obj->offscreenId, left, top, right, bottom);
}

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

void _mapDispMapGrp_NoMaterial(CameraId cam, MapObject* obj) {
	_mapDispMapObj_NoMaterial(cam, obj);
	if (obj->child) {
		_mapDispMapGrp_NoMaterial(cam, obj->child);
	}
	if ((obj->flags & 0x20) && obj->next) {
		_mapDispMapGrp_NoMaterial(cam, obj->next);
	}
}

void mapDispMapObj_bbox(CameraId cam, MapObject* obj) {

	int i;
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
	for (i = 0; i < obj->joints->partCount; i++) {
		mapSetPolygon(obj, obj->joints->parts[i].mesh);
	}
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}

void mapDispMapGrp_bbox(CameraId cam, MapObject* obj) {
	sysWaitDrawSync();
	GXClearBoundingBox();
	_mapDispMapGrp_NoMaterial(cam, obj);
	sysWaitDrawSync();
	GXReadBoundingBox(&obj->screenRect[0], &obj->screenRect[1], &obj->screenRect[2], &obj->screenRect[3]);
}

void mapDisp(void) {

}


typedef struct MapFileLight {
	const char* name; // 0x0
} MapFileLight;

typedef struct MapFileLightTable {
	s32 count;              // 0x0
	MapFileLight* lights[]; // 0x4
} MapFileLightTable;

#define MAP_LIGHT_TABLE(entry) (*(MapFileLightTable**)((u8*)(entry) + 0x98))

s32 mapSetLight(MapObject* obj, LightEntry** lights) {
	Vec pos;
	s32 count;
	s32 i;
	LightEntry** out;
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
			out = lights;
			for (i = 0; i < 32; i++) {
				if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
					light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
					if (!(*(u16*)light & 0x8000)) {
						count++;
						*out = light;
						out++;
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
		out = lights;
		for (i = 0; i < 32; i++) {
			if (((MapJointDrawModeEx*)obj->joints->drawMode)->lightMask & (1 << i)) {
				light = lightNameToPtr(MAP_LIGHT_TABLE(&mapWork[activeGroup].entries[obj->groupIndex])->lights[i]->name);
				if (!(*(u16*)light & 0x8000)) {
					count++;
					*out = light;
					out++;
					if (count >= 8) {
						break;
					}
				}
			}
		}
	}
	else {
		count = 0;
	}
	return count;
}

void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx) {
	GXTevStageID tevStage;
	Mtx queen_mtx;
	
	if (texCount > 0) {
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
				scrl_uv[0] += queen_uv[0];
				if (scrl_uv[0] > 100.0f) {
					scrl_uv[0] -= 100.0f;
				}
				if (scrl_uv[0] < -100.0f) {
					scrl_uv[0] += 100.0f;
				}

				scrl_uv[1] += queen_uv[1];
				if (scrl_uv[1] > 100.0f) {
					scrl_uv[1] -= 100.0f;
				}
				if (scrl_uv[1] < -100.0f) {
					scrl_uv[1] += 100.0f;
				}

				scrl_uv[2] += queen_uv[2];
				if (scrl_uv[2] > 100.0f) {
					scrl_uv[2] -= 100.0f;
				}
				if (scrl_uv[2] < -100.0f) {
					scrl_uv[2] += 100.0f;
				}

				scrl_uv[3] += queen_uv[3];
				if (scrl_uv[3] > 100.0f) {
					scrl_uv[3] -= 100.0f;
				}
				if (scrl_uv[3] < -100.0f) {
					scrl_uv[3] += 100.0f;
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
		GXSetTevSwapMode(tevStage++, GX_TEV_SWAP0, GX_TEV_SWAP0);
	}

}

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

typedef struct MapMaterial {
	char* name;                  // 0x0
	GXColor color;               // 0x4
	u8 lightMode;                // 0x8
	u8 pad9[2];                  // 0x9
	u8 samplerCount;             // 0xB
	MapMatSampler* samplers[8];  // 0xC
	MapTexXform xforms[8];       // 0x2C
	u8 pad10C[4];                // 0x10C
	u8* tevMode;                 // 0x110
} MapMaterial;

LightEntry* lightGetAmbient(void);

void mapSetTextureMatrix(MapMaterial* mat) {
	s32 i;
	s32 j;
	s32 k;
	f32 sx, sy, tx, ty, rot;
	f32 cx, cy;
	Mtx mtx, tmpMtx, transMtx, rotMtx, scaleMtx;

	j = 0;
	k = 0;
	for (i = mat->samplerCount - 1; i >= 0; i--, j++, k++) {
		sx = mat->xforms[i].sx;
		sy = mat->xforms[i].sy;
		rot = -mat->xforms[i].rot;
		tx = mat->xforms[i].tx;
		ty = -mat->xforms[i].ty;
		if (1.0f != sx || 1.0f != sy || 0.0f != tx || 0.0f != ty || 0.0f != rot) {
			if (rot != 0.0f) {
				cx = 0.5f * mat->xforms[i].cx * sx;
				cy = (1.0f - 0.5f * mat->xforms[i].cy) * sy;
				MTXTrans(mtx, cx, cy, 0.0f);
				MTXRotRad(rotMtx, 'z', MTXDegToRad(rot));
				MTXTrans(tmpMtx, -cx, -cy, 0.0f);
				MTXConcat(mtx, rotMtx, rotMtx);
				MTXConcat(rotMtx, tmpMtx, rotMtx);
			}
			if (sx != 0.0f || sy != 0.0f) {
				MTXScale(scaleMtx, sx, sy, 1.0f);
			}
			if (tx != 0.0f || ty != 0.0f) {
				MTXTrans(transMtx, tx, ty, 0.0f);
			}
			if (rot != 0.0f) {
				if (sx != 0.0f || sy != 0.0f) {
					MTXConcat(rotMtx, scaleMtx, mtx);
					if (tx != 0.0f || ty != 0.0f) {
						MTXConcat(mtx, transMtx, mtx);
					}
				}
				else if (tx != 0.0f || ty != 0.0f) {
					MTXConcat(rotMtx, transMtx, mtx);
				}
				else {
					MTXCopy(rotMtx, mtx);
				}
			}
			else if (sx != 0.0f || sy != 0.0f) {
				if (tx != 0.0f || ty != 0.0f) {
					MTXConcat(scaleMtx, transMtx, mtx);
				}
				else {
					MTXCopy(scaleMtx, mtx);
				}
			}
			else if (tx != 0.0f || ty != 0.0f) {
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

void mapSetMaterial(MapObject* obj, void* material) {
	MapMaterial* mat = material;
	GXColor ambColor = {0x00, 0x00, 0x00, 0xFF};
	s32 count;
	s32 i;
	s32 attnFn;
	u32 lightMask;
	s32 texIdx;
	LightEntry* light;
	LightEntry** lp;
	MapWork* wp;
	MapMatSampler* sampler;
	MapTexTable* table;
	char* name;
	s32 k;
	TEXDescriptor* desc;
	TEXHeader* hdr;
	GXBool mip;
	GXColor ambient;
	GXLightObj lightObj;
	GXTexObj texObj;
	Mtx rotX, rotY, rotZ;
	LightEntry* lights[8];
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
			GXInitLightSpot(&lightObj, lights[i]->spotAngle * 0.5f, GX_SP_SHARP);
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
		wp = &mapWork[activeGroup];
		sampler = mat->samplers[i];
		k = mapSearchTexName(MAPENT_FIELD(&wp->entries[obj->groupIndex], MapTexTable*, 0x94), sampler->tex->name);
		desc = TEXGet(wp->entries[obj->groupIndex].tpl, k);
		hdr = desc->textureHeader;
		if (hdr->minLOD == hdr->maxLOD) {
			mip = GX_FALSE;
		}
		else {
			mip = GX_TRUE;
		}
		GXInitTexObj(&texObj, hdr->data, hdr->width, hdr->height, (GXTexFmt)hdr->format,
					 (GXTexWrapMode)texwrap_tbl[sampler->wrapS], (GXTexWrapMode)texwrap_tbl[sampler->wrapT],
					 mip);
		hdr = desc->textureHeader;
		GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, hdr->minLOD, hdr->maxLOD, hdr->LODBias, GX_FALSE, hdr->edgeLODEnable, GX_ANISO_1);
		GXLoadTexObj(&texObj, (GXTexMapID)texIdx);
		texIdx++;
	}
	mapSetMaterialTev(mat->samplerCount, mat->tevMode ? *mat->tevMode : 0, obj->flags, obj->modelWorldMtx);
}

void mapSetPaperAmbColor(GXColor* color) {
	paper_ambient = *color;
}

void mapResetPaperAmbColor(void) {
	paper_ambient = (GXColor){0x70, 0x70, 0x70, 0xFF};
}

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
			GXInitLightSpot(&lightObj, lights[i]->spotAngle * 0.5f, GX_SP_SHARP);
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

#define MAP_VTXFMT(entry) (*(MapVtxFmtInfo**)((u8*)(entry) + 0xA4))

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

const GXCullMode culling[4] = {GX_CULL_FRONT, GX_CULL_BACK, GX_CULL_ALL, GX_CULL_NONE};
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

void mapSetPolygon(MapObject* obj, MapFileMesh* mesh) {
	MapWork* wp;
	void* nrm;
	void* pos;
	s32 texCount;
	MapVcdTable* vcd;

	int i;
	int j;
	int k;
	MapRawDL* dl;
	MapVtxRec* v;

	wp = &mapWork[activeGroup];
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
		GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->posFrac);
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

void mapSetPolygonVtxDesc(MapObject* obj, MapFileMesh* mesh) {

	MapWork* wp = &mapWork[activeGroup];
	u32 mask;
	MapVcdTable* vcd;
	void* pos;
	void* nrm;
	int i;

	vcd = (MapVcdTable*)mesh->vcdTableOffset;
	mask = mesh->elementMask;
	pos = (u8*)vcd->positions + 4;
	nrm = (u8*)vcd->normals + 4;
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->posFrac);
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
		GXSetVtxDesc((GXAttr)(GX_VA_TEX0 + i), GX_INDEX16);
		GXSetVtxAttrFmt(GX_VTXFMT0, (GXAttr)(GX_VA_TEX0 + i), GX_TEX_ST, GX_S16, (u8)MAP_VTXFMT(&wp->entries[obj->groupIndex])->texFrac[i]);
		GXSetArray((GXAttr)(GX_VA_TEX0 + i), (u8*)((MapVcdTable*)mesh->vcdTableOffset)->texCoords[i] + 4, 4);
	}
}

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
		if (found) {
			return found;
		}
	}
	return NULL;
}

MapFileJoint* mapSearchDmdJoint(MapFileJoint* joint, const char* name) {
	if ((s32)name[0] != '|') {
		return mapSearchDmdJointSub(joint, name);
	}
	return mapSearchDmdJointSub2(joint, name, "|");
}

MapObject* mapGetMapObj(const char *name) { // 1:1
    MapEntry* entry;
    MapWork *wp;
    int j;
    int i;
    MapObject *object;
    
    wp = &mapWork[activeGroup];
    if (!name) {
        return 0;
    }
    entry = &wp->entries[0];
    for (i = 0; i < wp->entries[0].count; entry++, i++) {
        object = entry->objects;
        for (j = 0; j < entry->numJoints; j++, object++) {
            if (!strcmp(object->joints->name, name)) {
                return object;
            }
        }
    }
    return 0;
}

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

void mapFlgOff(MapObject* obj, u32 flags, BOOL doNext) {
	obj->flags &= ~flags;
	if (obj->child) {
		mapFlgOff(obj->child, flags, TRUE);
	}
	if (doNext && obj->next) {
		mapFlgOff(obj->next, flags, TRUE);
	}
}

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

void mapObjSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj = mapGetMapObj(name);

	obj->offscreenId = offscreenNameToId(offscreen);
	obj->flags |= 0x80;
}

void mapGrpSetOffScreen(const char* name, const char* offscreen) {
	MapObject* obj = mapGetMapObj(name);
	s32 id = offscreenNameToId(offscreen);

	_setOffScrnId(obj, id, FALSE);
}

void mapObjClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	obj->offscreenId = -1;
	obj->flags &= ~0x80;
}

void mapGrpClearOffScreen(const char* name) {
	MapObject* obj = mapGetMapObj(name);

	_setOffScrnId(obj, -1, FALSE);
}

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
		MTXConcat(obj->unkAC, rotZ, obj->unkAC);
		MTXConcat(obj->unkAC, rotY, obj->unkAC);
		MTXConcat(obj->unkAC, rotX, obj->unkAC);
		obj->flags |= 0x200000;
		obj->flags |= 0x200;
	}
}

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

void mapSetFog(s32 type, f32 start, f32 end, GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];
	u32 c = *(u32*)color;

	wp->entries[0].fogType = type;
	wp->entries[0].fogStart = start;
	wp->entries[0].fogEnd = end;
	*(u32*)&wp->entries[0].fogColor = c;
}

void mapGetFog(s32* type, f32* start, f32* end, GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	*type = wp->entries[0].fogType;
	*start = wp->entries[0].fogStart;
	*end = wp->entries[0].fogEnd;
	*color = wp->entries[0].fogColor;
}

void mapFogOn(void) {
	mapGetWork()->entries[0].flags |= 1;
}

void mapFogOff(void) {
	mapGetWork()->entries[0].flags &= ~1;
}

void mapSetBlend(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend = *color;
	wp->entries[0].flags |= 2;
}

void mapSetBlend2(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	wp->entries[0].blend2 = *color;
	wp->entries[0].flags |= 4;
}

void mapGetBlend(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 2) {
		*color = wp->entries[0].blend;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}

void mapGetBlend2(GXColor* color) {
	MapWork* wp = &mapWork[activeGroup];

	if (wp->entries[0].flags & 4) {
		*color = wp->entries[0].blend2;
	}
	else {
		*color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
	}
}

void mapBlendOff(void) {
	mapGetWork()->entries[0].flags &= ~2;
}

void mapBlendOff2(void) {
	mapGetWork()->entries[0].flags &= ~4;
}

void mapObjSetColor(const char* name, GXColor* color) {
	MapObject* obj = mapGetMapObj(name);

	if (obj) {
		obj->color = *color;
		obj->flags |= 0x40;
	}
}

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

void mapGrpSetColor(const char* name, GXColor color) {
	setColor(mapGetMapObj(name), color, FALSE);
}

void mapSetProjTexObj(GXTexObj* obj, void* imgRef) {
	projTexObj = *obj;
	projTexImgRef = imgRef;
}

void mapSetProjMtx(Mtx mtx) {
	MTXCopy(mtx, projMtx);
}

extern int __float_nan[];
static inline s32 sp_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 sp_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (sp_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }

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

void spline_getvalue(Vec* out, f32 t, s32 n, Vec* pts, f32* ts, Vec* tbl) {
	s32 lo;
	s32 hi;
	s32 mid;
	f32 h;

	if (n == 2) {
		out->x = t * (pts[1].x - pts[0].x) + pts[0].x;
		out->y = t * (pts[1].y - pts[0].y) + pts[0].y;
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
	h = ts[lo];
	t -= h;
	h = ts[lo + 1] - h;
	out->x = pts[lo].x + t * ((pts[lo + 1].x - pts[lo].x) / h - h * (2.0f * tbl[lo].x + tbl[lo + 1].x) + t * (3.0f * tbl[lo].x + t * (tbl[lo + 1].x - tbl[lo].x) / h));
	out->y = pts[lo].y + t * ((pts[lo + 1].y - pts[lo].y) / h - h * (2.0f * tbl[lo].y + tbl[lo + 1].y) + t * (3.0f * tbl[lo].y + t * (tbl[lo + 1].y - tbl[lo].y) / h));
	out->z = pts[lo].z + t * ((pts[lo + 1].z - pts[lo].z) / h - h * (2.0f * tbl[lo].z + tbl[lo + 1].z) + t * (3.0f * tbl[lo].z + t * (tbl[lo + 1].z - tbl[lo].z) / h));
}

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

void mapSetTevCallback(s32 index, MapTevCallback callback) {
	mapGetWork()->entries[0].tevCallbacks[index] = callback;
}

void mapObjFlushOn(const char* name) {
	mapObjFlagOn(name, 0x100000);
}

void mapObjFlushOff(const char* name) {
	mapObjFlagOff(name, 0x100000);
}

void mapGrpFlushOn(const char* name) {
	mapGrpFlagOn(name, 0x100000);
}

void mapGrpFlushOff(const char* name) {
	mapGrpFlagOff(name, 0x100000);
}

void mapObjSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	GXColor color = {0};

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	mapObjSetColor(name, &color);
	mapObjFlagOff(name, 0x40);
}

void mapGrpSetFlushColor(const char* name, u8 r, u8 g, u8 b, u8 a) {
	GXColor color = {0};

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	mapGrpSetColor(name, color);
	mapGrpFlagOff(name, 0x40);
}

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
