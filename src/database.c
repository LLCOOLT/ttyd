#include "database.h"
#include "driver/arcdrv.h"
#include "manager/evtmgr.h"
#include "memory.h"
#include "system.h"
#include "driver/npcdrv.h"
#include "data/npc_data.h"
#include "data/mapdata.h"
#include "parse.h"
#include <string.h>

extern int sprintf(char* str, const char* format, ...);

//.sbss
void* ptr; //but why
u32 size;

void setupDataLoad(const char* mapName) {
	char path[64];
	DVDEntry* dvd;
	u32 filesize;

	ptr = NULL;
	sprintf(path, "%s/m/%s/s", getMarioStDvdRoot(), mapName);
	if (strcmp(mapName, "muj_20") || evtGetValue(NULL, (s32)0xF5DE0180) != 2) {
		arcOpen(path, &ptr, &size);
		if (!ptr) {
			dvd = DVDMgrOpen(path, 2, 0);
			if (dvd) {
				filesize = DVDMgrGetLength(dvd);
				size = filesize;
				if (filesize) {
					ptr = _mapAlloc(OSRoundUp32B(filesize));
					DVDMgrRead(dvd, ptr, OSRoundUp32B(size), 0);
				}
				DVDMgrClose(dvd);
			}
		}
	}
}

typedef struct MapAttrEntry {
	const char* name;
	s32 area;
	u32 flags;
} MapAttrEntry;

extern MapAttrEntry _map_attr_data[];
extern NpcTerritoryInfo npc_define_territory_type[];
extern NpcAiInfo npc_ai_type_table[];
extern void* memset(void*, int, u32);
extern char* strcpy(char*, const char*);
extern void animPoseSetAnim(s32, const char*, int);


#include "mario/mariost.h"

BOOL setupDataCheck(void) {
	char tribeName[64];
	BOOL b;

	if (!ptr) return TRUE;
	parseInit(ptr, size);
	while (parsePush("<Npc>")) {
		parseTagGet1("<tribe>", 0, tribeName);
		parsePopNext();
		b = gp->inBattle != 0;
		if (!animGroupBaseAsync(npcGetTribe(tribeName)->modelName, b, NULL)) return FALSE;
	}
	parsePop();
	return TRUE;
}
void setupDataBase(const char* mapName, NpcEntry* unused) {
	char npcName[64];
	char tribeName[64];
	Vec pos;
	f32 dir;
	char aiType[64];
	char terrType[64];
	Vec base;
	Vec loiter;
	Vec homing;
	f32 searchRange, searchAngle, homingRange, homingAngle;
	char btlSetup[64];
	FieldBattleData* fbat;
	MapAttrEntry* attr;
	MapAttrEntry* a;
	MapAttrEntry* b;
	NpcDeadInfo* dead;
	NpcDeadInfo tmp;
	int i, j;
	int isMarker;
	NpcTribeInfo* tribe;
	NpcEntry* npc;
	NpcAiInfo* ai;
	AreaData* area;
	s32 btl;

	fbat = fbatGetPointer();
	attr = _map_attr_data;
	dead = fbat->deadInfo;
	while (attr->name && strcmp(attr->name, mapName)) attr++;

	for (i = 0; i < 64; i++) {
		if (strcmp(fbat->deadInfo[i].mapName, "") == 0) {
			memset(&fbat->deadInfo[i], 0, sizeof(NpcDeadInfo));
			strcpy(fbat->deadInfo[i].mapName, mapName);
			break;
		}
		if (strcmp(fbat->deadInfo[i].mapName, mapName) == 0) break;
	}
	if (i > 0) {
		tmp = fbat->deadInfo[i];
		for (j = i; j >= 1; j--) fbat->deadInfo[j] = fbat->deadInfo[j - 1];
		fbat->deadInfo[0] = tmp;
	}

	if (attr->flags & 1) {
		a = _map_attr_data;
		for (;;) { if (!a->name || !strcmp(a->name, mapName)) break; a++; }
		b = _map_attr_data;
		for (;;) { if (!b->name || !strcmp(b->name, dead[1].mapName)) break; b++; }
		if (a->area != b->area) {
			memset(dead, 0, 0x500);
			strcpy(dead->mapName, mapName);
		} else if (!(attr->flags & 2) && (attr->flags & 4)) {
			memset(&dead[2], 0, 0x4d8);
		}
	}

	i = 0;
	isMarker = (attr->flags & 1) ? 1 : 0;
	if (ptr) {
		parseInit(ptr, size);
		while (parsePush("<Npc>")) {
			parseTagGet1("<name>", 0, npcName);
			parseTagGet1("<tribe>", 0, tribeName);
			parseTagGet1("<position>", 3, &pos);
			parseTagGet1("<dir>", 2, &dir);
			parseTagGet1("<aitype>", 0, aiType);
			parseTagGet1("<territory_type>", 0, terrType);
			parseTagGet1("<territory_base>", 3, &base);
			parseTagGet1("<territory_loiter>", 3, &loiter);
			parseTagGet1("<territory_homing>", 3, &homing);
			parseTagGet1("<search_range>", 2, &searchRange);
			parseTagGet1("<search_angle>", 2, &searchAngle);
			parseTagGet1("<homing_range>", 2, &homingRange);
			parseTagGet1("<homing_angle>", 2, &homingAngle);
			parseTagGet1("<btl_setup_no>", 0, btlSetup);
			parsePopNext();
			if (!isMarker || !(dead->mask & (1 << (u8)i))) {
				tribe = npcGetTribe(tribeName);
				npcEntry(npcName, (const char*)tribe->modelName);
				npc = npcNameToPtr(npcName);
				npc->field_314 = i;
				ai = npc_ai_type_table;
				npc->flags |= 4;
				npc->position = pos;
				npc->direction = dir;
				npc->tribe = tribe;
				npc->width = tribe->width;
				npc->height = tribe->height;
				npc->flags &= ~2;
				while (ai->description) {
					if (strcmp(ai->description, aiType) == 0) {
						npc->flags |= ai->flags;
						npc->initEvent = ai->initEvent;
						npc->moveEvent = ai->moveEvent;
						npc->deadEvent = ai->deadEvent;
						npc->findEvent = ai->findEvent;
						npc->lostEvent = ai->lostEvent;
						npc->returnEvent = ai->returnEvent;
						npc->blowEvent = ai->blowEvent;
						break;
					}
					ai++;
				}
				npc->territoryType = dbGetDefData(npc_define_territory_type, terrType);
				npc->territoryBase = base;
				npc->territoryLoiter = loiter;
				npc->territoryHoming = homing;
				npc->searchRange = searchRange;
				npc->searchAngle = searchAngle;
				npc->homingRange = homingRange;
				npc->homingAngle = homingAngle;
				npc->footstepSfxA = tribe->footstepSfxA;
				npc->footstepSfxB = tribe->footstepSfxB;
				npc->jumpSfx = tribe->jumpSfx;
				npc->landSfx = tribe->landSfx;
				npc->footstepStride = tribe->footstepStride;
				npc->footstepToggle = 1;
				npc->footstepAccum = 0.0f;
				btl = -1;
				area = areaDataPtr(mapName);
				if (strcmp(btlSetup, "BTLNO_INVALID")) {
					btl = dbGetDefData((NpcTerritoryInfo*)area->field_C, btlSetup);
				}
				npcSetBattleInfo(npc, btl);
				if (tribe->stayAnim) strcpy(npc->stayAnim, tribe->stayAnim);
				if (tribe->talkAnim) strcpy(npc->talkAnim, tribe->talkAnim);
				if (tribe->initialAnim) {
					strcpy(npc->currentAnim, tribe->initialAnim);
					animPoseSetAnim(npc->poseId, npc->currentAnim, 1);
				}
			}
			i++;
		}
		parsePop();
	}
}
