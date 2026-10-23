#include "evt/evt_cmd.h"
#include "driver/mapdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mariost.h"
#include "memory.h"
#include "pmario_sound.h"
#include <string.h>

s32 psndGetFlag();
void mapObjGetPos();

typedef struct MovingFloor {
	u32 flags;       // 0x0
	s32 kind;        // 0x4
	f32 speed;       // 0x8
	f32 pos;         // 0xC
	f32 cur;         // 0x10
	u32 pad14;       // 0x14
	OSTime start;    // 0x18
	s32 mode;        // 0x20
	s32 phase;       // 0x24
	s32 idx;         // 0x28
	f32 a[3];        // 0x2C
	f32 b[3];        // 0x38
	f32 pos3[3];     // 0x44
	f32 prev[3];     // 0x50
	f32 yoff;        // 0x5C
	f32 prevYoff;    // 0x60
	f32 scale;       // 0x64
	s32 time[3];     // 0x68
	s32 stmsec;      // 0x74
	u32 seHalt;      // 0x78
	u32 seId;        // 0x7C
	f32 turn;        // 0x80
	f32 angle;       // 0x84
} MovingFloor;

USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_info_nextarea);
USER_FUNC(evt_bero_get_now_number);
USER_FUNC(evt_hit_bind_mapobj);
USER_FUNC(evt_hit_bind_update);
USER_FUNC(evt_mapobj_get_position);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mapobj_scale);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_get_exparty);
USER_FUNC(evt_mario_get_name_hitobj_head);
USER_FUNC(evt_mario_get_name_hitobj_ride);
USER_FUNC(evt_mario_get_party);
USER_FUNC(evt_mario_set_hosei_xyz);
USER_FUNC(evt_party_get_name_hitobj_head);
USER_FUNC(evt_party_get_name_hitobj_ride);
USER_FUNC(evt_party_set_hosei_xyz);
USER_FUNC(evt_snd_sfxoff);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_areaname);
USER_FUNC(moving_floor_get_end);
USER_FUNC(moving_floor_get_kind);
USER_FUNC(moving_floor_get_mode);
USER_FUNC(moving_floor_get_pause);
USER_FUNC(moving_floor_get_stmsec);
USER_FUNC(moving_floor_getf_now_bpoint);
USER_FUNC(moving_floor_getf_pos);
USER_FUNC(moving_floor_getf_xz_scale);
USER_FUNC(moving_floor_halt_se);
USER_FUNC(moving_floor_reverse);
USER_FUNC(moving_floor_set_se);
USER_FUNC(moving_floor_stop_se);
USER_FUNC(moving_floor_update_turn);

static u32 sintbl[450] = {
	0x00000000, 0x3C8EF77F, 0x3D0EF241, 0x3D565E46, 0x3D8EDC3C, 0x3DB27ED8,
	0x3DD612C7, 0x3DF99674, 0x3E0E835E, 0x3E20303C, 0x3E31D0C8, 0x3E43636F,
	0x3E54E6E2, 0x3E66598E, 0x3E77BA67, 0x3E8483ED, 0x3E8D204B, 0x3E95B1C8,
	0x3E9E377A, 0x3EA6B0D9, 0x3EAF1D3F, 0x3EB77C03, 0x3EBFCC7D, 0x3EC80DE5,
	0x3ED03FD5, 0x3ED86163, 0x3EE0722A, 0x3EE87161, 0x3EF05E81, 0x3EF83904,
	0x3F000000, 0x3F03D988, 0x3F07A8C6, 0x3F0B6D76, 0x3F0F2746, 0x3F12D5E0,
	0x3F167914, 0x3F1A108C, 0x3F1D9BF6, 0x3F211B1E, 0x3F248DC1, 0x3F27F37C,
	0x3F2B4C2B, 0x3F2E976C, 0x3F31D51B, 0x3F3504F7, 0x3F3826AB, 0x3F3B3A04,
	0x3F3E3EC0, 0x3F41349C, 0x3F441B76, 0x3F46F30A, 0x3F49BB17, 0x3F4C7358,
	0x3F4F1BBD, 0x3F51B3F2, 0x3F543BC5, 0x3F56B314, 0x3F5919AC, 0x3F5B6F4C,
	0x3F5DB3D0, 0x3F5FE719, 0x3F6208D1, 0x3F6418F8, 0x3F66175D, 0x3F6803CD,
	0x3F69DE16, 0x3F6BA637, 0x3F6D5BEE, 0x3F6EFF19, 0x3F708FB8, 0x3F720D78,
	0x3F737868, 0x3F74D068, 0x3F761544, 0x3F7746ED, 0x3F786552, 0x3F797050,
	0x3F7A67E8, 0x3F7B4BE8, 0x3F7C1C61, 0x3F7CD91F, 0x3F7D8234, 0x3F7E177F,
	0x3F7E98FE, 0x3F7F06A3, 0x3F7F605B, 0x3F7FA637, 0x3F7FD817, 0x3F7FF60A,
	0x3F800000, 0x3F7FF60A, 0x3F7FD817, 0x3F7FA637, 0x3F7F605B, 0x3F7F06A3,
	0x3F7E98FE, 0x3F7E177F, 0x3F7D8234, 0x3F7CD91F, 0x3F7C1C61, 0x3F7B4BE8,
	0x3F7A67E8, 0x3F797050, 0x3F786552, 0x3F7746ED, 0x3F761544, 0x3F74D068,
	0x3F737879, 0x3F720D88, 0x3F708FB8, 0x3F6EFF2A, 0x3F6D5BEE, 0x3F6BA637,
	0x3F69DE27, 0x3F6803CD, 0x3F66175D, 0x3F641909, 0x3F6208E1, 0x3F5FE719,
	0x3F5DB3E1, 0x3F5B6F5D, 0x3F5919AC, 0x3F56B325, 0x3F543BD6, 0x3F51B3F2,
	0x3F4F1BBD, 0x3F4C7369, 0x3F49BB17, 0x3F46F30A, 0x3F441B86, 0x3F4134AD,
	0x3F3E3EC0, 0x3F3B3A04, 0x3F3826AB, 0x3F3504F7, 0x3F31D52C, 0x3F2E977D,
	0x3F2B4C2B, 0x3F27F37C, 0x3F248DC1, 0x3F211B2E, 0x3F1D9C06, 0x3F1A108C,
	0x3F167925, 0x3F12D5F1, 0x3F0F2746, 0x3F0B6D76, 0x3F07A8D6, 0x3F03D999,
	0x3F000000, 0x3EF83904, 0x3EF05EA2, 0x3EE87182, 0x3EE0724B, 0x3ED86184,
	0x3ED03FD5, 0x3EC80E06, 0x3EBFCC7D, 0x3EB77C24, 0x3EAF1D60, 0x3EA6B0FB,
	0x3E9E377A, 0x3E95B1C8, 0x3E8D206D, 0x3E84840E, 0x3E77BAAA, 0x3E6659D1,
	0x3E54E6E2, 0x3E43636F, 0x3E31D10B, 0x3E20307F, 0x3E0E83A1, 0x3DF996FB,
	0x3DD6134D, 0x3DB27ED8, 0x3D8EDCC2, 0x3D565F52, 0x3D0EF34D, 0x3C8EF998,
	0x358637BD, 0xBC8EF77F, 0xBD0EF241, 0xBD565D3A, 0xBD8EDC3C, 0xBDB27E52,
	0xBDD612C7, 0xBDF99674, 0xBE0E835E, 0xBE20303C, 0xBE31D0C8, 0xBE43632C,
	0xBE54E69F, 0xBE66594B, 0xBE77BA23, 0xBE8483ED, 0xBE8D204B, 0xBE95B1A7,
	0xBE9E3758, 0xBEA6B0D9, 0xBEAF1D1D, 0xBEB77BE1, 0xBEBFCC5C, 0xBEC80DC3,
	0xBED03FB3, 0xBED86163, 0xBEE0722A, 0xBEE87161, 0xBEF05E81, 0xBEF838E3,
	0xBEFFFFDE, 0xBF03D977, 0xBF07A8C6, 0xBF0B6D76, 0xBF0F2735, 0xBF12D5E0,
	0xBF167914, 0xBF1A107B, 0xBF1D9BF6, 0xBF211B1E, 0xBF248DB0, 0xBF27F36B,
	0xBF2B4C1B, 0xBF2E976C, 0xBF31D51B, 0xBF3504E6, 0xBF38269A, 0xBF3B39F3,
	0xBF3E3EAF, 0xBF41349C, 0xBF441B76, 0xBF46F2FA, 0xBF49BB06, 0xBF4C7358,
	0xBF4F1BAC, 0xBF51B3F2, 0xBF543BC5, 0xBF56B314, 0xBF5919AC, 0xBF5B6F4C,
	0xBF5DB3D0, 0xBF5FE708, 0xBF6208D1, 0xBF6418F8, 0xBF66175D, 0xBF6803BC,
	0xBF69DE16, 0xBF6BA626, 0xBF6D5BDD, 0xBF6EFF19, 0xBF708FA8, 0xBF720D78,
	0xBF737868, 0xBF74D057, 0xBF761533, 0xBF7746ED, 0xBF786541, 0xBF797050,
	0xBF7A67D7, 0xBF7B4BE8, 0xBF7C1C61, 0xBF7CD91F, 0xBF7D8234, 0xBF7E177F,
	0xBF7E98FE, 0xBF7F06A3, 0xBF7F605B, 0xBF7FA626, 0xBF7FD817, 0xBF7FF60A,
	0xBF800000, 0xBF7FF60A, 0xBF7FD817, 0xBF7FA637, 0xBF7F605B, 0xBF7F06A3,
	0xBF7E98FE, 0xBF7E177F, 0xBF7D8234, 0xBF7CD91F, 0xBF7C1C61, 0xBF7B4BE8,
	0xBF7A67E8, 0xBF797050, 0xBF786552, 0xBF7746ED, 0xBF761544, 0xBF74D068,
	0xBF737879, 0xBF720D88, 0xBF708FB8, 0xBF6EFF2A, 0xBF6D5BEE, 0xBF6BA637,
	0xBF69DE27, 0xBF6803CD, 0xBF66176E, 0xBF641909, 0xBF6208E1, 0xBF5FE719,
	0xBF5DB3E1, 0xBF5B6F5D, 0xBF5919BD, 0xBF56B325, 0xBF543BD6, 0xBF51B403,
	0xBF4F1BCE, 0xBF4C7369, 0xBF49BB17, 0xBF46F31B, 0xBF441B86, 0xBF4134AD,
	0xBF3E3ED1, 0xBF3B3A04, 0xBF3826BB, 0xBF350508, 0xBF31D52C, 0xBF2E977D,
	0xBF2B4C3C, 0xBF27F38C, 0xBF248DC1, 0xBF211B2E, 0xBF1D9C06, 0xBF1A109D,
	0xBF167925, 0xBF12D5F1, 0xBF0F2757, 0xBF0B6D87, 0xBF07A8D6, 0xBF03D999,
	0xBF000011, 0xBEF83926, 0xBEF05EC4, 0xBEE87182, 0xBEE0724B, 0xBED86184,
	0xBED03FD5, 0xBEC80E06, 0xBEBFCC9F, 0xBEB77C24, 0xBEAF1D82, 0xBEA6B0FB,
	0xBE9E379B, 0xBE95B1EA, 0xBE8D206D, 0xBE84840E, 0xBE77BAAA, 0xBE6659D1,
	0xBE54E725, 0xBE4363B2, 0xBE31D10B, 0xBE20307F, 0xBE0E83E4, 0xBDF99781,
	0xBDD613D3, 0xBDB27F5F, 0xBD8EDD48, 0xBD565F52, 0xBD0EF45A, 0xBC8EFBB1,
	0xB58637BD, 0x3C8EF566, 0x3D0EF241, 0x3D565D3A, 0x3D8EDBB6, 0x3DB27DCC,
	0x3DD61240, 0x3DF995EE, 0x3E0E831B, 0x3E202FF9, 0x3E31D085, 0x3E43632C,
	0x3E54E65C, 0x3E66594B, 0x3E77BA23, 0x3E8483CB, 0x3E8D2029, 0x3E95B1A7,
	0x3E9E3737, 0x3EA6B0B8, 0x3EAF1D1D, 0x3EB77BE1, 0x3EBFCC3A, 0x3EC80DC3,
	0x3ED03FB3, 0x3ED86141, 0x3EE07208, 0x3EE87161, 0x3EF05E81, 0x3EF838E3,
	0x3EFFFFDE, 0x3F03D977, 0x3F07A8B5, 0x3F0B6D65, 0x3F0F2724, 0x3F12D5D0,
	0x3F167903, 0x3F1A107B, 0x3F1D9BF6, 0x3F211B0D, 0x3F248DB0, 0x3F27F36B,
	0x3F2B4C1B, 0x3F2E975B, 0x3F31D50B, 0x3F3504D5, 0x3F38269A, 0x3F3B39F3,
	0x3F3E3EAF, 0x3F41349C, 0x3F441B76, 0x3F46F2FA, 0x3F49BB06, 0x3F4C7358,
	0x3F4F1BAC, 0x3F51B3E1, 0x3F543BC5, 0x3F56B314, 0x3F59199C, 0x3F5B6F3B,
	0x3F5DB3D0, 0x3F5FE708, 0x3F6208D1, 0x3F6418F8, 0x3F66174C, 0x3F6803BC,
	0x3F69DE16, 0x3F6BA626, 0x3F6D5BDD, 0x3F6EFF19, 0x3F708FA8, 0x3F720D78,
	0x3F737868, 0x3F74D057, 0x3F761533, 0x3F7746DC, 0x3F786541, 0x3F797050,
	0x3F7A67D7, 0x3F7B4BE8, 0x3F7C1C61, 0x3F7CD91F, 0x3F7D8234, 0x3F7E177F,
	0x3F7E98FE, 0x3F7F06A3, 0x3F7F605B, 0x3F7FA626, 0x3F7FD817, 0x3F7FF60A
};


#define GETW() ((MovingFloor*)evtGetValue(event, event->args[0]))
#define WOBBLE(w)                                                                                  \
	if ((w)->kind == 1) {                                                                          \
		(w)->yoff = 3.0f * ((f32*)sintbl)[(s32)(5.625f * (f32)((gp->retraceCount + event->eventId * 39) & 63))]; \
	} else {                                                                                       \
		(w)->yoff = 0.0f;                                                                          \
	}

USER_FUNC(evt_moving_floor_alloc) {
	s32* args = event->args;
	MovingFloor* w = (MovingFloor*)_mapAlloc(sizeof(MovingFloor));
	memset(w, 0, sizeof(MovingFloor));
	w->mode = event->lwData[6];
	w->kind = event->lwData[12];
	switch (w->mode) {
		case 0:
			w->flags &= ~1;
			w->idx = 0;
			w->scale = 1.0f;
			w->a[0] = event->lwData[2];
			w->b[0] = event->lwData[3];
			w->time[0] = event->lwData[4];
			w->pos3[0] = w->a[0];
			w->turn = event->lwData[11];
			break;
		case 1:
			w->idx = 1;
			w->scale = 1.0f;
			w->a[1] = event->lwData[2];
			w->b[1] = event->lwData[3];
			w->time[1] = event->lwData[4];
			w->pos3[1] = w->a[1];
			w->turn = event->lwData[11];
			break;
		case 2:
			w->idx = 2;
			w->scale = 1.0f;
			w->a[2] = event->lwData[2];
			w->b[2] = event->lwData[3];
			w->time[2] = event->lwData[4];
			w->pos3[2] = w->a[2];
			w->turn = event->lwData[11];
			break;
		case 3:
			w->idx = 0;
			w->scale = 1.0f;
			w->a[0] = event->lwData[2];
			w->b[0] = event->lwData[3];
			w->time[0] = event->lwData[4];
			w->pos3[0] = 0.5f * w->a[0] + 0.5f * w->b[0];
			w->a[2] = event->lwData[8];
			w->b[2] = event->lwData[9];
			w->time[2] = event->lwData[10];
			w->pos3[2] = 0.5f * w->a[2] + 0.5f * w->b[2];
			w->turn = event->lwData[11];
			break;
		case 4:
			w->idx = 2;
			w->scale = 1.0f;
			w->a[0] = event->lwData[2];
			w->b[0] = event->lwData[3];
			w->time[0] = event->lwData[4];
			w->pos3[0] = w->a[0];
			w->a[2] = event->lwData[8];
			w->b[2] = event->lwData[9];
			w->time[2] = event->lwData[10];
			w->pos3[2] = w->a[2];
			w->turn = event->lwData[11];
			break;
		case 5:
			w->flags &= ~1;
			w->idx = 0;
			w->scale = 1.0f;
			w->a[0] = event->lwData[2];
			w->b[0] = event->lwData[3];
			w->time[0] = event->lwData[4];
			w->pos3[0] = w->a[0];
			w->turn = event->lwData[11];
			break;
	}
	w->stmsec = event->lwData[5];
	w->prev[0] = w->pos3[0];
	w->prev[1] = w->pos3[1];
	w->prev[2] = w->pos3[2];
	w->prevYoff = w->yoff;
	WOBBLE(w)
	evtSetValue(event, args[0], (s32)w);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_moving_floor_free) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	if (w == NULL) {
		return EVT_RETURN_DONE;
	}
	_mapFree(w);
	evtSetValue(event, args[0], 0);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_moving_floor_init) {
	MovingFloor* w = GETW();
	s32 dir;
	f32 t;
	f32 d;
	switch (w->mode) {
		case 0:
			dir = w->phase;
			t = 0.0f;
			w->phase++;
			if (w->phase >= 2) {
				w->phase = 0;
			}
			break;
		case 1:
			dir = w->phase;
			t = 0.0f;
			w->phase++;
			if (w->phase >= 2) {
				w->phase = 0;
			}
			break;
		case 2:
			dir = w->phase;
			t = 0.0f;
			w->phase++;
			if (w->phase >= 2) {
				w->phase = 0;
			}
			break;
		case 3:
			switch (w->phase) {
				case 0:
					dir = 1;
					t = 0.5f;
					w->flags &= ~1;
					w->idx = 0;
					w->scale = 1.0f;
					break;
				case 1:
					dir = 0;
					t = 0.0f;
					w->flags |= 1;
					w->idx = 0;
					w->scale = 0.5f;
					break;
				case 2:
					dir = 1;
					t = 0.5f;
					w->flags &= ~1;
					w->idx = 2;
					w->scale = 1.0f;
					break;
				case 3:
					dir = 0;
					t = 0.0f;
					w->flags |= 1;
					w->idx = 2;
					w->scale = 0.5f;
					break;
				case 4:
					dir = 0;
					t = 0.5f;
					w->flags &= ~1;
					w->idx = 0;
					w->scale = 1.0f;
					break;
				case 5:
					dir = 1;
					t = 0.0f;
					w->flags |= 1;
					w->idx = 0;
					w->scale = 0.5f;
					break;
				case 6:
					dir = 0;
					t = 0.5f;
					w->flags &= ~1;
					w->idx = 2;
					w->scale = 1.0f;
					break;
				case 7:
					dir = 1;
					t = 0.0f;
					w->flags |= 1;
					w->idx = 2;
					w->scale = 0.5f;
					break;
			}
			w->phase++;
			if (w->phase >= 8) {
				w->phase = 0;
			}
			break;
		case 4:
			switch (w->phase) {
				case 0:
					w->idx = 2;
					w->scale = 1.0f;
					dir = 0;
					t = 0.0f;
					break;
				case 1:
					w->idx = 0;
					w->scale = 1.0f;
					dir = 0;
					t = 0.0f;
					break;
				case 2:
					w->idx = 2;
					w->scale = 1.0f;
					dir = 1;
					t = 0.0f;
					break;
				case 3:
					w->idx = 0;
					w->scale = 1.0f;
					dir = 1;
					t = 0.0f;
					break;
			}
			w->phase++;
			if (w->phase >= 4) {
				w->phase = 0;
			}
			break;
		case 5:
			dir = w->phase;
			t = 1.0f;
			break;
	}
	if (dir) {
		d = w->a[w->idx] - w->b[w->idx];
	} else {
		d = w->b[w->idx] - w->a[w->idx];
	}
	w->speed = d / (f32)w->time[w->idx];
	if (dir) {
		w->pos = w->b[w->idx] * (1.0f - t) + w->a[w->idx] * t;
	} else {
		w->pos = w->a[w->idx] * (1.0f - t) + w->b[w->idx] * t;
	}
	w->cur = (f32)w->time[w->idx] * t;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_moving_floor_main) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	s32 us = (((u32)event->lifetime - (u32)w->start) * 8) / ((*(u32*)0x800000F8 >> 2) / 125000);
	f32 t = (f32)us;
	w->pos += w->speed * t / 1000.0f;
	w->cur += t / 1000.0f;
	w->prev[0] = w->pos3[0];
	w->prev[1] = w->pos3[1];
	w->prev[2] = w->pos3[2];
	w->prevYoff = w->yoff;
	WOBBLE(w)
	w->pos3[w->idx] = w->pos;
	evtSetFloat(event, args[1], w->pos3[0]);
	evtSetFloat(event, args[2], w->pos3[1] + w->yoff);
	evtSetFloat(event, args[3], w->pos3[2]);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_moving_floor_main2) {
	MovingFloor* w = GETW();
	w->start = event->lifetime;
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_get_end) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	s32 a = (s32)w->cur;
	s32 b = (s32)((f32)w->time[w->idx] * w->scale);
	if (a >= b) {
		evtSetValue(event, args[1], 1);
	} else {
		evtSetValue(event, args[1], 0);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_get_pause) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	if (w->flags & 2) {
		evtSetValue(event, args[1], 1);
	} else {
		evtSetValue(event, args[1], 0);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_get_kind) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	evtSetValue(event, args[1], w->kind);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_get_mode) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	evtSetValue(event, args[1], w->mode);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_update_turn) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	w->angle += w->turn;
	if (w->angle < 0.0f) {
		w->angle += 360.0f;
	}
	if (w->angle >= 360.0f) {
		w->angle -= 360.0f;
	}
	evtSetFloat(event, args[1], w->angle);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_getf_pos) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	w->prevYoff = w->yoff;
	WOBBLE(w)
	evtSetFloat(event, args[1], w->pos3[0]);
	evtSetFloat(event, args[2], w->pos3[1] + w->yoff);
	evtSetFloat(event, args[3], w->pos3[2]);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_getf_now_bpoint) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	evtSetFloat(event, args[1], w->pos3[0] - w->prev[0]);
	evtSetFloat(event, args[2], (w->pos3[1] + w->yoff) - (w->prev[1] + w->prevYoff));
	evtSetFloat(event, args[3], w->pos3[2] - w->prev[2]);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_get_stmsec) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	if (w->flags & 1) {
		evtSetValue(event, args[1], 0);
	} else {
		evtSetValue(event, args[1], w->stmsec * 60 / 1000);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_getf_xz_scale) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	f32 v = evtGetFloat(event, (s32)(w->pos3[1] + w->yoff));
	evtSetFloat(event, args[1], (500.0f - v) / 500.0f);
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_reverse) {
	MovingFloor* w = GETW();
	f32 e;
	if (w->speed >= 0.0f) {
		return EVT_RETURN_DONE;
	}
	w->speed *= -1.0f;
	e = (f32)w->time[w->idx] * w->scale;
	w->cur = e - w->cur;
	w->phase ^= 1;
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_set_se) {
	s32* args = event->args;
	MovingFloor* w = GETW();
	char* name = (char*)evtGetValue(event, args[1]);
	MapObject* obj;
	Vec pos;
	s32 flags;
	if (w->seHalt) {
		return EVT_RETURN_DONE;
	}
	if (w->seId == 0) {
		mapObjGetPos(name, &pos);
		obj = mapGetMapObj(name);
		if (obj == NULL) {
			mapErrorEntry(0, name);
			return EVT_RETURN_DONE;
		}
		flags = 0;
		if ((psndGetFlag() & 0x100) && !(obj->flags & 0x1800)) {
			flags = 0x10000;
		}
		w->seId = psndSFXOn_3D((const char*)(flags | 0x424), &pos);
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_stop_se) {
	MovingFloor* w = GETW();
	if (w->seHalt == 0 && w->seId) {
		psndSFXOff(w->seId);
		w->seId = 0;
	}
	return EVT_RETURN_DONE;
}

USER_FUNC(moving_floor_halt_se) {
	MovingFloor* w = GETW();
	w->seHalt = 1;
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_moving_floor_delete) {
	s32 id = evtGetValue(event, event->args[0]);
	EventEntry* e = evtGetPtrID(id);
	MovingFloor* w = (MovingFloor*)e->lwData[9];
	if (w->seHalt == 0 && w->seId) {
		psndSFXOff(w->seId);
		w->seId = 0;
	}
	if (w != NULL) {
		_mapFree(w);
		e->lwData[9] = 0;
	}
	if (evtCheckID(id)) {
		evtDeleteID(id);
	}
	return EVT_RETURN_DONE;
}

s32 moving_floor_bero_check[] = {
	131163, (s32)evt_sub_get_areaname, -30000000, 131084, -30000000, (s32)"yuu",
	2, 33, 65541, 0, 131163, (s32)evt_bero_exec_wait,
	65536, 65649, (s32)"\216\251\223\256\215\355\217\234\203`\203F\203b\203N\221\322\202\277\000\000\000", 131163, (s32)evt_bero_exec_wait, 1,
	131163, (s32)evt_bero_get_now_number, -29999990, 262235, (s32)evt_bero_get_info_nextarea, -29999990,
	-29999997, -29999996, 131097, -29999997, 0, 7,
	33, 6, 65649, (s32)"\216\251\223\256\215\355\217\234\212\256\227\271\000\000\000", 131163, (s32)moving_floor_stop_se,
	-29999991, 131163, (s32)moving_floor_halt_se, -29999991, 2, 1,
};

s32 moving_floor[] = {
	131163, (s32)evt_moving_floor_alloc, -29999991, 196699, (s32)evt_hit_bind_mapobj, -29999999,
	-30000000, 65628, (s32)moving_floor_bero_check, 65541, 0, 131163,
	(s32)evt_moving_floor_init, -29999991, 131163, (s32)evt_moving_floor_main2, -29999991, 196699,
	(s32)moving_floor_get_mode, -29999991, -29999992, 131096, -29999992, 5,
	65540, 0, 33, 65541, 0, 65541,
	0, 196699, (s32)moving_floor_get_pause, -29999991, -29999992, 131096,
	-29999992, 0, 7, 33, 65545, 1,
	327771, (s32)moving_floor_getf_pos, -29999991, -29999988, -29999987, -29999986,
	131163, (s32)evt_moving_floor_main2, -29999991, 393307, (s32)evt_mapobj_trans, 1,
	-30000000, -29999988, -29999987, -29999986, 196699, (s32)moving_floor_update_turn,
	-29999991, -29999992, 393307, (s32)evt_mapobj_rotate, 1, -30000000,
	-230000000, -29999992, -230000000, 131163, (s32)evt_hit_bind_update, -29999999,
	131085, -29999993, 0, 393307, (s32)evt_mapobj_trans, 1,
	-29999993, -29999988, 0, -29999986, 393307, (s32)evt_mapobj_rotate,
	1, -29999993, -230000000, -29999992, -230000000, 196699,
	(s32)moving_floor_getf_xz_scale, -29999991, -29999992, 393307, (s32)evt_mapobj_scale, 1,
	-29999993, -29999992, 1, -29999992, 33, 6,
	65545, 1, 327771, (s32)evt_moving_floor_main, -29999991, -29999988,
	-29999987, -29999986, 131163, (s32)evt_moving_floor_main2, -29999991, 393307,
	(s32)evt_mapobj_trans, 1, -30000000, -29999988, -29999987, -29999986,
	196699, (s32)moving_floor_update_turn, -29999991, -29999992, 393307, (s32)evt_mapobj_rotate,
	1, -30000000, -230000000, -29999992, -230000000, 131163,
	(s32)evt_hit_bind_update, -29999999, 131085, -29999993, 0, 393307,
	(s32)evt_mapobj_trans, 1, -29999993, -29999988, 0, -29999986,
	393307, (s32)evt_mapobj_rotate, 1, -29999993, -230000000, -29999992,
	-230000000, 196699, (s32)moving_floor_getf_xz_scale, -29999991, -29999992, 393307,
	(s32)evt_mapobj_scale, 1, -29999993, -29999992, 1, -29999992,
	33, 131163, (s32)evt_mario_get_name_hitobj_head, -29999998, 131163, (s32)evt_mario_get_party,
	-29999990, 131122, -29999997, 0, 131097, -29999990,
	0, 196699, (s32)evt_party_get_name_hitobj_head, 0, -29999997, 33,
	131163, (s32)evt_mario_get_exparty, -29999990, 131122, -29999996, 0,
	131097, -29999990, 0, 196699, (s32)evt_party_get_name_hitobj_head, 1,
	-29999996, 33, 131122, -70000000, 0, 131096,
	-29999994, 1, 131084, -29999998, -29999999, 131122,
	-70000000, 1, 33, 131084, -29999997, -29999999,
	131122, -70000000, 1, 33, 131084, -29999996,
	-29999999, 131122, -70000000, 1, 33, 33,
	131096, -70000000, 1, 131163, (s32)moving_floor_reverse, -29999991,
	33, 196699, (s32)moving_floor_get_kind, -29999991, -29999992, 131096,
	-29999992, 0, 327771, (s32)moving_floor_getf_now_bpoint, -29999991, -29999988,
	-29999987, -29999986, 131163, (s32)evt_mario_get_name_hitobj_ride, -29999992, 131084,
	-29999992, -29999999, 262235, (s32)evt_mario_set_hosei_xyz, -29999988, -29999987,
	-29999986, 33, 196699, (s32)evt_party_get_name_hitobj_ride, 0, -29999992,
	131084, -29999992, -29999999, 327771, (s32)evt_party_set_hosei_xyz, 0,
	-29999988, -29999987, -29999986, 33, 196699, (s32)evt_party_get_name_hitobj_ride,
	1, -29999992, 131084, -29999992, -29999999, 327771,
	(s32)evt_party_set_hosei_xyz, 1, -29999988, -29999987, -29999986, 33,
	33, 196699, (s32)moving_floor_get_end, -29999991, -29999992, 131097,
	-29999992, 0, 7, 33, 196699, (s32)moving_floor_get_kind,
	-29999991, -29999992, 131096, -29999992, 0, 131122,
	-70000000, 1, 131090, -29999988, -230000000, 131090,
	-29999987, -230000000, 131090, -29999986, -230000000, 131122,
	-70000000, 0, 33, 33, 33, 131096,
	-70000000, 0, 131163, (s32)moving_floor_stop_se, -29999991, 32,
	196699, (s32)moving_floor_set_se, -29999991, -30000000, 33, 33,
	6, 131163, (s32)moving_floor_stop_se, -29999991, 65539, 0,
	196699, (s32)moving_floor_get_stmsec, -29999991, -29999990, 65541, -29999990,
	196699, (s32)moving_floor_get_mode, -29999991, -29999992, 131096, -29999992,
	5, 131122, -29999990, 0, 32, 131096,
	-29999990, 0, 7, 33, 33, 65541,
	0, 196699, (s32)moving_floor_get_pause, -29999991, -29999992, 131096,
	-29999992, 0, 7, 33, 65545, 1,
	327771, (s32)moving_floor_getf_pos, -29999991, -29999988, -29999987, -29999986,
	131163, (s32)evt_moving_floor_main2, -29999991, 393307, (s32)evt_mapobj_trans, 1,
	-30000000, -29999988, -29999987, -29999986, 196699, (s32)moving_floor_update_turn,
	-29999991, -29999992, 393307, (s32)evt_mapobj_rotate, 1, -30000000,
	-230000000, -29999992, -230000000, 131163, (s32)evt_hit_bind_update, -29999999,
	131085, -29999993, 0, 393307, (s32)evt_mapobj_trans, 1,
	-29999993, -29999988, 0, -29999986, 393307, (s32)evt_mapobj_rotate,
	1, -29999993, -230000000, -29999992, -230000000, 196699,
	(s32)moving_floor_getf_xz_scale, -29999991, -29999992, 393307, (s32)evt_mapobj_scale, 1,
	-29999993, -29999992, 1, -29999992, 33, 6,
	65545, 1, 327771, (s32)moving_floor_getf_pos, -29999991, -29999988,
	-29999987, -29999986, 131163, (s32)evt_moving_floor_main2, -29999991, 393307,
	(s32)evt_mapobj_trans, 1, -30000000, -29999988, -29999987, -29999986,
	196699, (s32)moving_floor_update_turn, -29999991, -29999992, 393307, (s32)evt_mapobj_rotate,
	1, -30000000, -230000000, -29999992, -230000000, 131163,
	(s32)evt_hit_bind_update, -29999999, 131085, -29999993, 0, 393307,
	(s32)evt_mapobj_trans, 1, -29999993, -29999988, 0, -29999986,
	393307, (s32)evt_mapobj_rotate, 1, -29999993, -230000000, -29999992,
	-230000000, 196699, (s32)moving_floor_getf_xz_scale, -29999991, -29999992, 393307,
	(s32)evt_mapobj_scale, 1, -29999993, -29999992, 1, -29999992,
	33, 6, 6, 131163, (s32)evt_moving_floor_free, -29999991,
	2, 1,
};

s32 ridedown_floor[] = {
	196699, (s32)evt_hit_bind_mapobj, -29999999, -30000000, 131122, -29999990,
	-29999998, 131126, -29999990, -29999997, 131161, -29999994,
	-29999986, 131161, -29999994, -29999985, 131122, -29999991,
	0, 65541, 0, 131096, -29999995, 0,
	131161, -29999993, -29999988, 131149, -29999988, 65534,
	131159, -29999993, -29999988, 32, 131161, -29999993,
	-29999988, 131149, -29999988, 65533, 131159, -29999993,
	-29999988, 33, 131163, (s32)evt_mario_get_name_hitobj_ride, -29999989, 131084,
	-29999989, -29999999, 131096, -29999995, 0, 131161,
	-29999994, -29999989, 131126, -29999989, -29999996, 131100,
	-29999989, 0, 131122, -29999989, 0, 33,
	131159, -29999994, -29999989, 131161, -29999993, -29999988,
	131151, -29999988, 1, 131159, -29999993, -29999988,
	32, 131161, -29999994, -29999989, 131125, -29999989,
	-29999996, 131101, -29999989, 10000, 131122, -29999989,
	10000, 33, 131159, -29999994, -29999989, 131161,
	-29999993, -29999988, 131151, -29999988, 2, 131159,
	-29999993, -29999988, 33, 33, 131161, -29999993,
	-29999988, 131096, -29999988, 0, 131096, -29999995,
	0, 131161, -29999994, -29999989, 131101, -29999989,
	-29999985, 131126, -29999989, -29999996, 131100, -29999989,
	-29999985, 131122, -29999989, -29999985, 33, 32,
	131125, -29999989, -29999996, 131101, -29999989, -29999985,
	131122, -29999989, -29999985, 33, 33, 131159,
	-29999994, -29999989, 33, 33, 131161, -29999994,
	-29999989, 131127, -29999989, -29999990, 131132, -29999989,
	-229999990, 131132, -29999989, -229999990, 131096, -29999995,
	0, 131124, -29999988, -29999997, 131130, -29999988,
	-29999989, 32, 131124, -29999988, -29999998, 131131,
	-29999988, -29999989, 33, 393307, (s32)evt_mapobj_trans, 1,
	-30000000, 0, -29999988, 0, 131163, (s32)evt_hit_bind_update,
	-29999999, 131124, -29999987, -29999988, 131131, -29999987,
	-29999986, 131124, -29999986, -29999988, 131163, (s32)evt_mario_get_name_hitobj_ride,
	-29999989, 131084, -29999989, -29999999, 262235, (s32)evt_mario_set_hosei_xyz,
	0, -29999987, 0, 33, 196699, (s32)evt_party_get_name_hitobj_ride,
	0, -29999989, 131084, -29999989, -29999999, 327771,
	(s32)evt_party_set_hosei_xyz, 0, 0, -29999987, 0, 33,
	196699, (s32)evt_party_get_name_hitobj_ride, 1, -29999989, 131084, -29999989,
	-29999999, 327771, (s32)evt_party_set_hosei_xyz, 1, 0, -29999987,
	0, 33, 131090, -29999987, -230000000, 131097,
	-29999991, 0, 131163, (s32)evt_snd_sfxoff, -29999991, 131122,
	-29999991, 0, 33, 32, 131096, -29999991,
	0, 327771, (s32)evt_mapobj_get_position, -30000000, -29999989, -29999988,
	-29999987, 393307, (s32)evt_snd_sfxon_3d, (s32)"SFX_STG1_TIK_FLOOR_MOVE1\000\000\000", -29999989, -29999988,
	-29999987, -29999991, 33, 33, 65545, 1,
	6, 2, 1,
};

