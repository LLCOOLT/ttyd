#include "driver/mapdrv.h"
#include "driver/arcdrv.h"
#include "manager/dvdmgr.h"
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
BOOL disableMapDraw;
BOOL __mapdrv_make_dl;
Mtx projMtx;
void* projTexImgRef;
GXTexObj projTexObj;
GXColor paperCraft_ambient;
GXColor paper_ambient;

//.rodata
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
	disableMapDraw = TRUE;
}

void N_mapDispOn(void) {
	disableMapDraw = FALSE;
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

void mapBuildTexture(MapObject* obj, TEXPalette* texture, void* table) {
	int i;
	MapFileJointPart* part;

	for (i = 0; i < obj->joints->partCount; i++) {
		part = &obj->joints->parts[i];
	}
	if (obj->child) {
		mapBuildTexture(obj->child, texture, table);
	}
	if (obj->next) {
		mapBuildTexture(obj->next, texture, table);
	}
}

MapObject* _mapEnt(MapFileJoint* joint, MapObject* parent, Mtx mtx, s32 index) {
	return NULL;




}

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
	return NULL;




}

void makeDisplayList(BOOL group) {

}

MapEntryAnimData* mapSearchAnmObj(const char* animName) {
	return NULL;



}

void mapCheckAnimation(const char* animName, BOOL* valid, f32* a3) {

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

void mapUnLoad(void) {

}

BOOL mapPreLoad(void) {
	return TRUE; //do nothing
}

void mapLoad(const char* map) {
	MapWork* wp;

	sysWaitDrawSync();
	wp = &mapWork[0];
	activeGroup = 0;
	memset(wp, 0, sizeof(MapWork));
	_mapLoad(&mapWork[0], 0, map);
	wp->entries[0].count = 1;
}

void mapMain(void) {

}

void mapDisp(void) {

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
		mapErrorEntry(0, name);
		return;
	}
	if (!(flags & 0x100) || obj->unk114) {
		obj->flags |= flags;
	}
}

void mapObjFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		mapErrorEntry(0, name);
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
		mapErrorEntry(0, name);
		return;
	}
	mapFlgOn(obj, flags, FALSE);
}

void mapGrpFlagOff(const char* name, u32 flags) {
	MapObject* obj = mapGetMapObj(name);

	if (!obj) {
		mapErrorEntry(0, name);
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
	MapWork* wp = mapGetWork();
	GXColor c = *color;

	wp->entries[0].fogType = type;
	wp->entries[0].fogStart = start;
	wp->entries[0].fogEnd = end;
	wp->entries[0].fogColor = c;
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
		mapErrorEntry(0, name);
		return;
	}
	*r = obj->color.r;
	*g = obj->color.g;
	*b = obj->color.b;
	*a = obj->color.a;
}
