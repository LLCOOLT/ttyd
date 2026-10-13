#include "evt/evt_bero.h"
#include "driver/hitdrv.h"
#include "driver/seqdrv.h"
#include "evt/evt_cmd.h"
#include "evt/evt_npc.h"
#include "evt/evt_seq.h"
#include "mario/mario.h"
#include "mario/mario_sbr.h"
#include "mario/mariost.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include <string.h>
#include "driver/camdrv.h"

extern GlobalWork* gp;

//.bss
s32 BeroID[16];
s32 BeroSW[16]; //switches
BeroEntry* BeroINFOARR[16];

//.sbss, NOTE: all are reversed because of -inline deferred
s32 BeroEXEC;
s32 BeroNUM, BeroNOWNUM;
s32 BeroCAM; //only seems to be set in scripts
f32 BeroOX, BeroOY, BeroOZ; //offset position
f32 BeroSX, BeroSY, BeroSZ; //start position
f32 BeroEX, BeroEY, BeroEZ; //end position
Vec BeroPT, BeroAT;
BOOL BeroMarioGO;

EVT_BEGIN(evt_bero_mario_enter)
CALL(evt_seq_wait, SEQ_GAME)
CALL(evt_npc_change_fbat_mode, 7)



EVT_END()

EVT_BEGIN(evt_bero_info_run)
CALL(evt_bero_get_into_info)


EVT_END()

//new in retail, f32* x, f32* y, f32* z
USER_FUNC(evt_bero_set_reset_position) {
	s32* args = event->args;
	s32 x, y, z;

	x = evtGetValue(event, args[0]);
	y = evtGetValue(event, args[1]);
	z = evtGetValue(event, args[2]);
	marioSetBottomlessResetPosition((f32)x, (f32)y, (f32)z);
	return EVT_RETURN_DONE;
}

//new in retail, no args
extern void N_marioSetBottomlessRespawnPosOnBeroEntry(f32 x, f32 y, f32 z);

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry) {
	s32* args = event->args;
	s32 x, y, z;

	x = evtGetValue(event, args[0]);
	y = evtGetValue(event, args[1]);
	z = evtGetValue(event, args[2]);
	N_marioSetBottomlessRespawnPosOnBeroEntry((f32)x, (f32)y, (f32)z);
	return EVT_RETURN_DONE;
}

USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos) {
	MarioWork* wp = marioGetPtr();
	N_marioSetBottomlessRespawnPosOnBeroEntry(wp->position.x, wp->position.y, wp->position.z);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_set_reset_position_current) {
	MarioWork* wp = marioGetPtr();
	marioSetBottomlessResetPosition(wp->position.x, wp->position.y, wp->position.z);
	return EVT_RETURN_DONE;
}

s32 bero_get_BeroEXEC(void) {
	return BeroEXEC;
}

s32 bero_get_BeroNUM(void) {
	return BeroNUM;
}

f32 bero_get_BeroSX(void) {
	return BeroSX;
}

f32 bero_get_BeroSY(void) {
	return BeroSY;
}

f32 bero_get_BeroSZ(void) {
	return BeroSZ;
}

f32 bero_get_BeroEX(void) {
	return BeroEX;
}

f32 bero_get_BeroEY(void) {
	return BeroEY;
}

f32 bero_get_BeroEZ(void) {
	return BeroEZ;
}

BeroEntry** bero_get_ptr(void) {
	return BeroINFOARR;
}

void bero_clear_Offset(void) {
	BeroOX = 0.0f;
	BeroOY = 0.0f;
	BeroOZ = 0.0f;
}

s32 bero_id_filter(s32 id) { //1:1, cursed function, do not touch
	BeroEntry** temp, **table = BeroINFOARR;
	s32 newId = id;
	const char *string, *test;

	if (id < 0 || id >= 16) {
		test = (const char*)id;
		if (&newId != NULL) {
			newId = 0;
		}
		temp = table;
		while (1) {
			string = (*temp)->hitName;
			if (!string || !strcmp(string, test)) {
				break;
			}
			temp++;
			if (&newId != NULL) {
				newId++;
			}
		}
	}
	return newId;
}

//const char** mapName, const char** beroName
USER_FUNC(evt_bero_mapchange) {
	s32* args = event->args;
	const char *map, *bero;

	map = (const char*)evtGetValue(event, args[0]);
	bero = (const char*)evtGetValue(event, args[1]);
	if (isFirstCall) {
		seqSetSeq(SEQ_MAP_CHANGE, map, bero);
	}
	return EVT_RETURN_BLOCK;
}

//s32 retIndex
USER_FUNC(evt_bero_get_entername) {
	evtSetValue(event, *event->args, (s32)&gp->beroEnterName);
	return EVT_RETURN_DONE;
}

//BOOL* on/off, s32* mask
USER_FUNC(evt_bero_exec_onoff) {
	s32* args = event->args;
	BOOL onoff;
	s32 mask, value;

	onoff = evtGetValue(event, args[0]);
	mask = evtGetValue(event, args[1]);
	value = BeroEXEC | mask;
	if (onoff) {
		value = BeroEXEC & ~mask;
	}
	BeroEXEC = value;
	return EVT_RETURN_DONE;
}

//s32 retIndex
USER_FUNC(evt_bero_exec_get) {
	evtSetValue(event, *event->args, BeroEXEC);
	return EVT_RETURN_DONE;
}

//s32* mask, TODO: add states, change EvtStatus to s32 and do #defines
USER_FUNC(evt_bero_exec_wait) {
	return evtGetValue(event, *event->args) & BeroEXEC ? EVT_RETURN_DONE : 0;
}

//f32 retX, f32 retY, f32 retZ
USER_FUNC(evt_bero_get_start_position) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroSX);
	evtSetFloat(event, args[1], BeroSY);
	evtSetFloat(event, args[2], BeroSZ);
	return EVT_RETURN_DONE;
}

//f32 retX, f32 retY, f32 retZ
USER_FUNC(evt_bero_get_end_position) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroEX);
	evtSetFloat(event, args[1], BeroEY);
	evtSetFloat(event, args[2], BeroEZ);
	return EVT_RETURN_DONE;
}

//s32* id, s32 retIndex1, s32 retIndex2, s32 retIndex3, s32 retIndex4
USER_FUNC(evt_bero_get_info_anime) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->animeArg1);
	evtSetValue(event, args[2], *(u16*)&bero->animeArg2);
	evtSetValue(event, args[3], bero->animeArg3);
	evtSetValue(event, args[4], bero->animeArg4);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_info_length) {
	BeroEntry* bero;
	s32* args = event->args;
	s32 v5;
	f32 storeme;

	args = event->args;
	bero = BeroINFOARR[evtGetValue(event, args[0])];
	v5 = bero->field_0x18;
	if (v5 != -1) {
		evtSetFloat(event, args[1], (f32)v5);
		return EVT_RETURN_DONE;
	}
	switch (*(u16*)&bero->kinddirArg1 & 0xFFF) {
		case 0:
		case 3:
		case 0xF00:
			storeme = 30.0f;
			break;
		case 1:
			storeme = 60.0f;
			break;
		case 2:
			storeme = 60.0f;
			break;
		default:
			storeme = 60.0f;
			break;
	}
	evtSetFloat(event, args[1], storeme);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_info_kinddir) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->kinddirArg1);
	evtSetValue(event, args[2], *(u16*)&bero->kinddirArg2);
	evtSetValue(event, args[3], bero->kinddirArg3);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_info_nextarea) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], bero->nextareaArg1);
	evtSetValue(event, args[2], (s32)bero->nextareaArg2);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_set_now_number) {
	BeroNOWNUM = evtGetValue(event, *event->args);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_now_number) {
	evtSetValue(event, *event->args, BeroNOWNUM);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_info) {
	BeroEntry** table = BeroINFOARR;
	BeroEntry* entry;
	HitEntry* hit;
	s32* switches;
	s32 val;
	s32 i;

	table[0]=table[1]=table[2]=table[3]=table[4]=table[5]=table[6]=table[7]=table[8]=table[9]=table[10]=table[11]=table[12]=table[13]=table[14]=table[15]=NULL;
	
	for (entry = (BeroEntry*)event->lwData[0];; entry++) {
		hit = hitNameToPtr(entry->hitName);
		if (!entry->hitName) {
			break;
		}
		if (!hit) {
			mapErrorEntry(1, entry->hitName);
		}
	}
	entry = (BeroEntry*)event->lwData[0];
	switches = BeroSW;
	i = 0;
	while (1) {
		if (!entry->hitName) {
			break;
		}
		*table = entry;
		switches[i] = -1;
		table++;
		i++;
		entry++;
	}
	BeroNUM = i;
	BeroEXEC = 0;
	return EVT_RETURN_DONE;
}

extern void bero_get_position_pipe_sub(s32 id, s32 a, s32 b, s32 kind, Vec* start, Vec* end);

USER_FUNC(bero_get_position_pipe_pure) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	s32 a = evtGetFloat(event, args[1]);
	s32 kind = event->lwData[5];
	Vec start, end;
	bero_get_position_pipe_sub(id, a, event->lwData[3], kind, &start, &end);
	BeroSX = start.x;
	BeroSY = kind == 8 ? start.y - 37.5f : start.y;
	BeroSZ = start.z;
	BeroEX = end.x;
	BeroEY = kind == 8 ? end.y - 37.5f : end.y;
	BeroEZ = end.z;
	N_marioSetBottomlessRespawnPosOnBeroEntry(BeroEX, BeroEY, BeroEZ);
	return EVT_RETURN_DONE;
}


typedef struct { Vec f_0; Vec pos; Vec at; } BeroCamRoadOut;
extern void camRoadMain(BeroCamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
extern void camRoadReset(void);
extern void camShiftReset(void);

USER_FUNC(bero_get_position_pipe2) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	s32 a = evtGetFloat(event, args[1]);
	Vec start, end;
	BeroCamRoadOut out;
	bero_get_position_pipe_sub(id, a, event->lwData[3], event->lwData[5], &start, &end);
	end.y += 1.0f;
	camRoadReset();
	camShiftReset();
	camRoadMain(&out, end.x, end.y, end.z, end.x, end.y, end.z, 0.0f);
	{
	Vec pt = {0.0f, 0.0f, 0.0f};
	Vec at = {0.0f, 0.0f, 0.0f};
	pt.x = out.pos.x;
	pt.y = out.pos.y;
	pt.z = out.pos.z;
	at.x = out.at.x;
	at.y = out.at.y;
	at.z = out.at.z;
	BeroPT = pt;
	BeroAT = at;
	}
	return EVT_RETURN_DONE;
}

typedef struct { u8 pad[0xac]; u32 flags; s32 kind; } BeroPipeInfo;

s32 bero_set_disp_position_pipe(BeroPipeInfo* info) {
	switch (info->kind) {
		case 2: case 3: case 4: case 5:
			if (!(info->flags & 0x1000)) {
				marioGetPtr()->field_0x98.y += 3.0f;
				marioGetPtr()->field_0x98.z -= 15.0f;
			}
			break;
		case 7: case 10000:
			break;
		case 8: case 9:
			if (!(info->flags & 0x1000)) {
				marioGetPtr()->field_0x98.z -= 13.0f;
			} else {
				marioGetPtr()->field_0x98.z -= 20.0f;
			}
			break;
	}
	return 2;
}

USER_FUNC(evt_bero_switch_on) {
	s32* args = event->args;
	BeroEntry** temp, **table = BeroINFOARR;
	s32 id = evtGetValue(event, *args);
	s32 newId = id;
	const char *string, *test;
	if (id < 0 || id >= 16) {
		test = (const char*)id;
		if (&newId != NULL) {
			newId = 0;
		}
		temp = table;
		while (1) {
			string = (*temp)->hitName;
			if (!string || !strcmp(string, test)) {
				break;
			}
			temp++;
			if (&newId != NULL) {
				newId++;
			}
		}
	}
	if (BeroSW[newId] == 1) {
		event->lwData[0] = 1;
	} else {
		event->lwData[0] = 0;
	}
	BeroSW[newId] = 1;
	event->lwData[1] = newId;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_switch_off) {
	s32* args = event->args;
	BeroEntry** temp, **table = BeroINFOARR;
	s32 id = evtGetValue(event, *args);
	s32 newId = id;
	const char *string, *test;
	if (id < 0 || id >= 16) {
		test = (const char*)id;
		if (&newId != NULL) {
			newId = 0;
		}
		temp = table;
		while (1) {
			string = (*temp)->hitName;
			if (!string || !strcmp(string, test)) {
				break;
			}
			temp++;
			if (&newId != NULL) {
				newId++;
			}
		}
	}
	if (BeroSW[newId] != 1) {
		event->lwData[0] = 1;
	} else {
		event->lwData[0] = 0;
	}
	BeroSW[newId] = 0;
	event->lwData[1] = newId;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_number) {
	s32* args = event->args;
	BeroEntry** temp, **table = BeroINFOARR;
	s32 id = evtGetValue(event, *args);
	s32 newId = id;
	const char *string, *test;
	if (id < 0 || id >= 16) {
		test = (const char*)id;
		if (&newId != NULL) {
			newId = 0;
		}
		temp = table;
		while (1) {
			string = (*temp)->hitName;
			if (!string || !strcmp(string, test)) {
				break;
			}
			temp++;
			if (&newId != NULL) {
				newId++;
			}
		}
	}
	event->lwData[1] = newId;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_case_id_save) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroID[id] = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_case_id_load) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], BeroID[id]);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_disppos_save) {
	BeroOX = marioGetPtr()->field_0x98.x;
	BeroOY = marioGetPtr()->field_0x98.y;
	BeroOZ = marioGetPtr()->field_0x98.z;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_disppos_load) {
	marioGetPtr()->field_0x98.x = BeroOX;
	marioGetPtr()->field_0x98.y = BeroOY;
	marioGetPtr()->field_0x98.z = BeroOZ;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_into_info) {

}

extern BOOL animGroupBaseAsync(const char* name, s32 group, void* callback);

USER_FUNC(evt_bero_read_mario_pera) {
	if (isFirstCall) {
		event->userdata[0] = 0;
	}
	switch (event->userdata[0]) {
		case 0:
			if (animGroupBaseAsync("p_dokan_x", 0, NULL)) {
				event->userdata[0] = 1;
			}
			break;
		case 1:
			if (animGroupBaseAsync("p_dokan_y", 0, NULL)) {
				event->userdata[0] = 100;
			}
			break;
	}
	return event->userdata[0] == 100 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

USER_FUNC(evt_bero_id_filter) {
	s32* args = event->args;
	evtSetValue(event, args[0], bero_id_filter(evtGetValue(event, args[0])));
	return EVT_RETURN_DONE;
}


extern s32 default_entevt[1];
extern s32 default_outevt[1];

USER_FUNC(evt_bero_get_info_num) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroEntry* bero = BeroINFOARR[id];
	const char* dirs[8] = {"n_", "ne_", "e_", "se_", "s_", "sw_", "w_", "nw_"};
	s32 kind;
	s32* evt;

	event->lwData[3] = (s32)bero->hitName;
	event->lwData[4] = *(u16*)&bero->kinddirArg1;
	kind = bero->kinddirArg3;
	switch (kind) {
	case 20000:
		if (kind == 10000) {
			kind = 10000;
		} else switch (*(u16*)&bero->kinddirArg1 & 0xFFF) {
			case 0:
			case 1:
				for (kind = 0; (u32)kind < 8; kind++) {
					if (!strncmp(dirs[kind], bero->hitName, strlen(dirs[kind]))) {
						break;
					}
				}
				break;
			default:
				kind = 10000;
				break;
		}
		break;
	}
	event->lwData[5] = kind;
	event->lwData[6] = (s32)&bero->field_0xC;
	evt = bero->enterEvent;
	if (!evt) evt = default_entevt;
	event->lwData[7] = (s32)evt;
	event->lwData[8] = 0xFFFF0000;
	event->lwData[9] = BeroSW[id];
	event->lwData[10] = bero->field_0x20;
	if (bero->field_0x20 == -1) {
		switch (*(u16*)&bero->kinddirArg1 & 0xFFF) {
			case 0xF00: event->lwData[10] = 0; break;
			case 0: event->lwData[10] = 10; break;
			case 1: event->lwData[10] = 9; break;
			case 2: event->lwData[10] = 4; break;
			case 3: event->lwData[10] = 7; break;
		}
	}
	evt = bero->exitEvent;
	if (!evt) evt = default_outevt;
	event->lwData[11] = (s32)evt;
	event->lwData[12] = 0xFFFF0000;
	event->lwData[13] = bero->nextareaArg1;
	event->lwData[14] = (s32)bero->nextareaArg2;
	return EVT_RETURN_DONE;
}

#include "system.h"
extern double sin(double);
extern double cos(double);

USER_FUNC(evt_bero_move_mario_speed) {
	s32* args = event->args;
	f32 speed = evtGetFloat(event, args[0]);
	OSTime now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
	f32 angle, s, c, dx, dy, dist, dist2;
	s32 xdone, ydone;

	if (isFirstCall) {
		event->savedTime = now;
	}
	speed = sysFrame2SecFloat(speed);
	angle = 6.2832f * reviseAngle(angleABf(BeroSX, BeroSY, BeroEX, BeroEY)) / 360.0f;
	s = sin(angle);
	c = cos(angle);
	dist = speed * (f32)sysMsec2Frame((s32)(((s32)now - (s32)event->savedTime) / (u64)((*(u32*)0x800000F8 / 4) / 1000)));
	dx = speed * s;
	dy = -(speed * c);
	dist2 = s * dist;
	marioGetPtr()->position.x = BeroSX + dist2;
	dist2 = c * dist;
	marioGetPtr()->position.y = BeroSY + -dist2;
	marioGetPtr()->position.z = BeroSZ;
	xdone = 0;
	if (dx >= 0.0f && BeroEX <= marioGetPtr()->position.x) xdone = 1;
	if (dx < 0.0f && BeroEX >= marioGetPtr()->position.x) xdone = 1;
	ydone = 0;
	if (dy >= 0.0f && BeroEY <= marioGetPtr()->position.y) ydone = 1;
	if (dy < 0.0f && BeroEY >= marioGetPtr()->position.y) ydone = 1;
	if (xdone + ydone != 2) {
		return EVT_RETURN_BLOCK;
	}
	marioGetPtr()->position.x = BeroEX;
	marioGetPtr()->position.y = BeroEY;
	marioGetPtr()->position.z = BeroEZ;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_overwrite) {
	BeroEntry** temp, **table = BeroINFOARR;
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	s32 newId = id;
	const char *string, *test;
	if (id < 0 || id >= 16) {
		test = (const char*)id;
		if (&newId != NULL) {
			newId = 0;
		}
		temp = table;
		while (1) {
			string = (*temp)->hitName;
			if (!string || !strcmp(string, test)) {
				break;
			}
			temp++;
			if (&newId != NULL) {
				newId++;
			}
		}
	}
	BeroINFOARR[newId] = (BeroEntry*)evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_cam3d_change) {
	s32* args = event->args;
	CameraEntry* cam = camGetPtr(4);
	s32 time = evtGetValue(event, args[0]);
	s32 curve = evtGetValue(event, args[1]);
	cam->presetPos = cam->cameraPos;
	cam->presetAt = cam->cameraAt;
	cam->storedPos = BeroPT;
	cam->storedAt = BeroAT;
	cam->startTimeA = gp->renderTime;
	cam->durationA = (u32)(time * ((*(u32*)0x800000F8 / 4) / 1000));
	cam->stateA = 3;
	cam->curveA = curve;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_cam_shift_init) {
	camRoadReset();
	camShiftReset();
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_mario_go_init) {
	BeroMarioGO = FALSE;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_mario_go) {
	BeroMarioGO = TRUE;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_mario_go_wait) {
	return BeroMarioGO == 0 ? 0 : EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_1stcheck) {
	s32* args = event->args;
	if (strcmp((const char*)event->lwData[13], "sys_01") == 0) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return EVT_RETURN_DONE;
}

extern void camShiftMain(CameraEntry* camera, MarioWork* mario, f32* out);

USER_FUNC(evt_camera_change_event_from_road) {
	MarioWork* mario = marioGetPtr();
	CameraEntry* cam = camGetPtr(4);
	f32 bank;
	BeroCamRoadOut out;
	camShiftMain(cam, mario, &bank);
	camRoadMain(&out, mario->position.x, *(f32*)((u8*)cam + 0x98), mario->position.z, mario->position.x, *(f32*)((u8*)cam + 0x98), mario->position.z, bank);
	{
	Vec pt = {0.0f, 0.0f, 0.0f};
	Vec at = {0.0f, 0.0f, 0.0f};
	pt.x = out.pos.x; pt.y = out.pos.y; pt.z = out.pos.z;
	at.x = out.at.x; at.y = out.at.y; at.z = out.at.z;
	cam->presetPos = cam->cameraPos;
	cam->presetAt = cam->cameraAt;
	cam->storedPos = pt;
	cam->storedAt = at;
	cam->startTimeA = gp->renderTime;
	cam->durationA = (u32)(500 * ((*(u32*)0x800000F8 / 4) / 1000));
	cam->stateA = 3;
	cam->curveA = 11;
	}
	return EVT_RETURN_DONE;
}
