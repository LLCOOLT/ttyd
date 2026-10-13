#include "evt/evt_eff.h"
#include "driver/effdrv.h"
#include "eff/n64/eff_expbom_n64.h"
#include "eff/eff_n64.h"
#include "evt/evt_cmd.h"
#include <string.h>

extern f32 evtGetFloat(EventEntry* entry, s32 index);

USER_FUNC(evt_eff) {
	s32* args = event->args;
	EffectEntry* entry = NULL;
	const char* effName;
	const char* effSet;
	s32 int2, int3, int4, int5, int6, int7, int8, int9,
		int10, int11, int12, int13, int14;
	f32 float2, float3, float4, float5, float6, float7, float8,
		float9, float10, float11, float12, float13, float14;

	effName = (const char*)evtGetValue(event, args[0]);
	//these are probably storing different typecasts, s32 and u32
	evtGetValue(event, args[0]);
	evtGetValue(event, args[0]);
	effSet = (const char*)evtGetValue(event, args[1]);
	//these are probably storing different typecasts, s32 and u32
	evtGetValue(event, args[1]);
	evtGetValue(event, args[1]);
	int2 = evtGetValue(event, args[2]);
	int3 = evtGetValue(event, args[3]); //unused
	int4 = evtGetValue(event, args[4]); //unused
	int5 = evtGetValue(event, args[5]); //unused
	int6 = evtGetValue(event, args[6]);
	int7 = evtGetValue(event, args[7]);
	int8 = evtGetValue(event, args[8]);
	int9 = evtGetValue(event, args[9]);
	int10 = evtGetValue(event, args[10]);
	int11 = evtGetValue(event, args[11]);
	int12 = evtGetValue(event, args[12]); //unused
	int13 = evtGetValue(event, args[13]); //unused
	int14 = evtGetValue(event, args[14]); //unused

	float2 = evtGetFloat(event, args[2]); //unused
	float3 = evtGetFloat(event, args[3]);
	float4 = evtGetFloat(event, args[4]);
	float5 = evtGetFloat(event, args[5]);
	float6 = evtGetFloat(event, args[6]);
	float7 = evtGetFloat(event, args[7]);
	float8 = evtGetFloat(event, args[8]);
	float9 = evtGetFloat(event, args[9]);
	float10 = evtGetFloat(event, args[10]);
	float11 = evtGetFloat(event, args[11]);
	float12 = evtGetFloat(event, args[12]);
	float13 = evtGetFloat(event, args[13]);
	float14 = evtGetFloat(event, args[14]);

	switch (effGetSet(effSet)->id) {
		case 0: //kemuri
			//entry = effKemuriEntry(int2, float3, float4, float5, float6);
			break;

		//insert more with internal order here

		default:
			break;
	}

	if (entry && effName) {
		if (strcmp(effName, "")) {
			effSetName(entry, effName);
		}
	}

	return EVT_RETURN_DONE;
}





USER_FUNC(evt_eff64) {
	s32* args = event->args;
	const char* effName;
	const char* effSet;
	s32 int2, int3, int4, int5, int6, int7, int8, int9,
		int10, int11, int12, int13, int14, raw3;
	f32 float2, float3, float4, float5, float6, float7, float8,
		float9, float10, float11, float12, float13, float14;
	EffectEntry* effect;

	effName = (const char*)evtGetValue(event, args[0]);
	//these are probably storing different typecasts, s32 and u32
	evtGetValue(event, args[0]);
	evtGetValue(event, args[0]);
	effSet = (const char*)evtGetValue(event, args[1]);
	//these are probably storing different typecasts, s32 and u32
	evtGetValue(event, args[1]);
	evtGetValue(event, args[1]);

	int2 = evtGetValue(event, args[2]);
	int3 = evtGetValue(event, args[3]);
	int4 = evtGetValue(event, args[4]);
	int5 = evtGetValue(event, args[5]);
	int6 = evtGetValue(event, args[6]);
	int7 = evtGetValue(event, args[7]);
	int8 = evtGetValue(event, args[8]);
	int9 = evtGetValue(event, args[9]);
	int10 = evtGetValue(event, args[10]);
	int11 = evtGetValue(event, args[11]);
	int12 = evtGetValue(event, args[12]);
	int13 = evtGetValue(event, args[13]);
	int14 = evtGetValue(event, args[14]);

	float2 = evtGetFloat(event, args[2]); //unused
	float3 = evtGetFloat(event, args[3]);
	float4 = evtGetFloat(event, args[4]);
	float5 = evtGetFloat(event, args[5]);
	float6 = evtGetFloat(event, args[6]);
	float7 = evtGetFloat(event, args[7]);
	float8 = evtGetFloat(event, args[8]);
	float9 = evtGetFloat(event, args[9]);
	float10 = evtGetFloat(event, args[10]);
	float11 = evtGetFloat(event, args[11]);
	float12 = evtGetFloat(event, args[12]);
	float13 = evtGetFloat(event, args[13]);
	float14 = evtGetFloat(event, args[14]);
	raw3 = args[3];
	effect = NULL;
	switch (effGetSetN64(effSet)->id) {
		case 0:
			effect = effExpBomN64Entry(float2, float3, float4); //x, y, z
			break;

		//TODO: many more
	}

	if (effect && effName) {
		if (strcmp(effName, "")) {
			effSetName(effect, effName);
		}
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_softdelete) {
	effSoftDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_delete) {
	effDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_softdelete_ptr) {
	effSoftDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_delete_ptr) {
	effDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

extern void* marioGetPtr(void);
extern s32 marioGetPartyId(void);
extern s32 marioGetExtraPartyId(void);
extern void* partyGetPtr(s32 id);
extern EffectEntry* effFukidashiEntry(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, f32 w, f32 e);

USER_FUNC(evt_eff_fukidashi) {
	s32* args = event->args;
	s32 mode = evtGetValue(event, args[0]);
	const char* effName = (const char*)evtGetValue(event, args[1]);
	const char* npcName = (const char*)evtGetValue(event, args[2]);
	s32 a = evtGetValue(event, args[3]);
	s32 b = evtGetValue(event, args[4]);
	f32 x = evtGetFloat(event, args[5]);
	f32 y = evtGetFloat(event, args[6]);
	f32 z = evtGetFloat(event, args[7]);
	f32 w = evtGetFloat(event, args[8]);
	f32 e = evtGetFloat(event, args[9]);
	s32 d = evtGetValue(event, args[10]);
	EffectEntry* entry = NULL;
	void* p;
	f32 h;

	switch (mode) {
		case 0:
			h = *(f32*)((u8*)marioGetPtr() + 0x1b8);
			y = 2.0f * h / 3.0f;
			w = h / 3.0f;
			entry = effFukidashiEntry(a, b, -1, d, 0.0f, y, 0.0f, w, e);
			break;
		case 1:
			p = !strcmp(npcName, "me") ? (void*)event->ownerNPC : (void*)npcNameToPtr(npcName);
			h = *(f32*)((u8*)p + 0x150);
			y = 2.0f * h / 3.0f;
			w = h / 3.0f;
			entry = effFukidashiEntry(a, b, (s32)p, d, 0.0f, y, 0.0f, w, e);
			break;
		case 2:
			entry = effFukidashiEntry(a, b, 0, d, x, y, z, w, e);
			break;
		case 3:
			p = partyGetPtr(marioGetPartyId());
			if (p) {
				h = *(f32*)((u8*)p + 0xf0);
				y = 2.0f * h / 3.0f;
			w = h / 3.0f;
			entry = effFukidashiEntry(a, b, -2, d, 0.0f, y, 0.0f, w, e);
			}
			break;
		case 4:
			p = partyGetPtr(marioGetExtraPartyId());
			if (p) {
				h = *(f32*)((u8*)p + 0xf0);
				y = 2.0f * h / 3.0f;
			w = h / 3.0f;
			entry = effFukidashiEntry(a, b, -3, d, 0.0f, y, 0.0f, w, e);
			}
			break;
	}

	if (effName && strcmp(effName, "") && entry) {
		effSetName(entry, effName);
	}
	return EVT_RETURN_DONE;
}
