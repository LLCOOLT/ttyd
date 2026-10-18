// FAKE: whole unit as asm (scratch/asm_inline.py + hand data naming); C kept under #ifdef NONMATCHING. Best pure C: 48/52 (camera_change 97.68, get_info 99.22, get_info_num 99.42, move_mario_speed 99.68).
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
extern const char str_8041A3C8[4];
extern const char str_8041A3CC[4];
extern const char str_8041A3D0[4];
extern const char str_8041A3D4[4];
extern const char str_8041A3D8[4];
extern const char str_8041A3DC[4];
extern const char str_8041A3E0[4];
extern const char str_8041A3E4[4];
__declspec(section ".rodata") const char* const jumptable_802C4970[8] = { str_8041A3C8, str_8041A3CC, str_8041A3D0, str_8041A3D4, str_8041A3D8, str_8041A3DC, str_8041A3E0, str_8041A3E4 };
__declspec(section ".rodata") const f32 vec3_802c4990[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c499c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") char str_802C49A8[16] = "\223\171\212\307\202\251\202\347\215\176\202\350\202\275\000";
__declspec(section ".rodata") char str_802C49B8[16] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\061\000";
__declspec(section ".rodata") char str_802C49C8[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\127\117\117\104\061";
__declspec(section ".rodata") char str_802C49DC[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\127\117\117\104\062";
__declspec(section ".rodata") char str_802C49F0[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\127\117\117\104\063";
__declspec(section ".rodata") char str_802C4A04[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\111\122\117\116\061";
__declspec(section ".rodata") char str_802C4A18[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\111\122\117\116\062";
__declspec(section ".rodata") char str_802C4A2C[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\107\122\111\114\114\105\061\000\000";
__declspec(section ".rodata") char str_802C4A44[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\123\114\111\104\105\061\000\000\000";
__declspec(section ".rodata") char str_802C4A5C[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\124\125\122\116\061";
__declspec(section ".rodata") char str_802C4A70[20] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\105\114\105\103\061";
__declspec(section ".rodata") char str_802C4A84[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\123\124\117\116\105\061\000\000\000";
__declspec(section ".rodata") char str_802C4A9C[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\103\101\123\124\114\105\061\000\000";
__declspec(section ".rodata") char str_802C4AB4[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\103\101\123\124\114\105\062\000\000";
__declspec(section ".rodata") char str_802C4ACC[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\115\105\124\101\114\061\000\000\000";
__declspec(section ".rodata") char str_802C4AE4[20] = "\123\106\130\137\123\124\107\063\137\101\125\124\117\137\104\117\117\122\061";
__declspec(section ".rodata") char str_802C4AF8[24] = "\123\106\130\137\123\124\107\063\137\114\117\103\113\105\122\137\117\120\105\116\061\000\000";
__declspec(section ".rodata") char str_802C4B10[24] = "\123\106\130\137\104\117\117\122\137\117\120\105\116\137\123\114\111\104\105\061\137\063\000";
__declspec(section ".rodata") char str_802C4B28[16] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\061\000";
__declspec(section ".rodata") char str_802C4B38[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\127\117\117\104\061";
__declspec(section ".rodata") char str_802C4B4C[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\127\117\117\104\062";
__declspec(section ".rodata") char str_802C4B60[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\111\122\117\116\061";
__declspec(section ".rodata") char str_802C4B74[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\111\122\117\116\062";
__declspec(section ".rodata") char str_802C4B88[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\107\122\111\114\114\105\061\000\000";
__declspec(section ".rodata") char str_802C4BA0[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\123\114\111\104\105\061\000\000\000";
__declspec(section ".rodata") char str_802C4BB8[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\124\125\122\116\061";
__declspec(section ".rodata") char str_802C4BCC[20] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\105\114\105\103\061";
__declspec(section ".rodata") char str_802C4BE0[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\103\101\123\124\114\105\061\000\000";
__declspec(section ".rodata") char str_802C4BF8[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\103\101\123\124\114\105\062\000\000";
__declspec(section ".rodata") char str_802C4C10[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\115\105\124\101\114\061\000\000\000";
__declspec(section ".rodata") char str_802C4C28[24] = "\123\106\130\137\123\124\107\063\137\114\117\103\113\105\122\137\103\114\117\123\105\061\000";
__declspec(section ".rodata") char str_802C4C40[24] = "\123\106\130\137\104\117\117\122\137\123\110\125\124\137\123\114\111\104\105\061\137\063\000";
__declspec(section ".rodata") const f32 vec3_802c4c58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c4c64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") char str_802C4C70[20] = "\123\106\130\137\115\101\122\111\117\137\104\117\113\101\116\061\000\000\000";
__declspec(section ".rodata") char str_802C4C84[12] = "\203\170\203\215\223\157\230\136\000\000\000";
__declspec(section ".rodata") char str_802C4C90[48] = "\203\170\203\215\202\314\217\157\202\304\215\163\202\255\203\146\201\133\203\136\202\314\223\361\217\144\223\157\230\136\226\150\216\176\202\360\202\265\202\304\202\242\202\334\202\267\000";
__declspec(section ".rodata") char str_802C4CC0[20] = "\203\170\203\215\215\355\217\234\202\265\202\334\202\265\202\275\000\000\000";
__declspec(section ".rodata") char str_802C4CD4[64] = "\203\170\203\215\202\314\215\355\217\234\227\134\226\361\202\340\202\265\202\255\202\315\203\170\203\215\202\314\217\157\202\304\215\163\202\255\203\146\201\133\203\136\202\314\223\361\217\144\215\355\217\234\226\150\216\176\202\305\202\267\000\000\000";
__declspec(section ".rodata") char str_802C4D14[36] = "\203\132\201\133\203\165\203\165\203\215\203\142\203\116\202\251\202\347\202\314\203\215\201\133\203\150\216\236\202\314\217\210\227\235\000";
__declspec(section ".rodata") char str_802C4D38[36] = "\224\167\214\151\202\311\223\374\202\351\202\306\202\253\202\314\203\175\203\212\203\111\202\314\217\211\212\372\217\210\227\235\000\000\000";
__declspec(section ".rodata") char str_802C4D5C[36] = "\225\201\222\312\202\311\223\374\202\351\202\306\202\253\202\314\203\175\203\212\203\111\202\314\217\211\212\372\217\210\227\235\000\000\000";
__declspec(section ".rodata") char str_802C4D80[20] = "\202\331\202\251\202\314\217\211\212\372\220\335\222\350\212\112\216\156\000";
__declspec(section ".rodata") char str_802C4D94[8] = "\163\171\163\137\060\061\000";
__declspec(section ".rodata") const f64 double_to_int_802c4da0 = 4503601774854144.0;
__declspec(section ".rodata") char str_802C4DA8[12] = "\160\137\144\157\153\141\156\137\170\000\000";
__declspec(section ".rodata") char str_802C4DB4[12] = "\160\137\144\157\153\141\156\137\171\000\000";


extern GlobalWork* gp;

//.bss
extern s32 BeroID[16];
extern s32 BeroSW[16]; //switches
extern BeroEntry* BeroINFOARR[16];

//.sbss, NOTE: all are reversed because of -inline deferred
s32 BeroEXEC;
s32 BeroNUM, BeroNOWNUM;
s32 BeroCAM; //only seems to be set in scripts
f32 BeroOX, BeroOY, BeroOZ; //offset position
f32 BeroSX, BeroSY, BeroSZ; //start position
f32 BeroEX, BeroEY, BeroEZ; //end position
Vec BeroPT, BeroAT;
BOOL BeroMarioGO;

USER_FUNC(bero_get_position_normal);
USER_FUNC(bero_get_position_pipe2);
USER_FUNC(bero_get_position_pipe_pure);
USER_FUNC(evt_bero_1stcheck);
USER_FUNC(evt_bero_cam3d_change);
USER_FUNC(evt_bero_cam_shift_init);
USER_FUNC(evt_bero_case_id_load);
USER_FUNC(evt_bero_case_id_save);
USER_FUNC(evt_bero_disppos_load);
USER_FUNC(evt_bero_disppos_save);
USER_FUNC(evt_bero_exec_get);
USER_FUNC(evt_bero_exec_onoff);
USER_FUNC(evt_bero_get_info_anime);
USER_FUNC(evt_bero_get_info_kinddir);
USER_FUNC(evt_bero_get_info_length);
USER_FUNC(evt_bero_get_info_num);
USER_FUNC(evt_bero_get_into_info);
USER_FUNC(evt_bero_get_number);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bero_mario_go);
USER_FUNC(evt_bero_mario_go_init);
USER_FUNC(evt_bero_mario_go_wait);
USER_FUNC(evt_bero_move_mario_speed);
USER_FUNC(evt_bero_read_mario_pera);
USER_FUNC(evt_bero_set_now_number);
USER_FUNC(evt_bero_switch_off);
USER_FUNC(evt_bero_switch_on);
USER_FUNC(evt_cam3d_evt_off);
USER_FUNC(evt_cam_road_reset);
USER_FUNC(evt_cam_road_reset2);
USER_FUNC(evt_camera_change_event_from_road);
USER_FUNC(evt_del_case_evt);
USER_FUNC(evt_fade_end_wait);
USER_FUNC(evt_fade_set_mapchange_type);
USER_FUNC(evt_hit_get_position);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_map_checkanim);
USER_FUNC(evt_map_pauseanim);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_map_replayanim);
USER_FUNC(evt_mapobj_rotate);
USER_FUNC(evt_mario_bgmode_off);
USER_FUNC(evt_mario_bgmode_on);
USER_FUNC(evt_mario_cam_off);
USER_FUNC(evt_mario_cam_on);
USER_FUNC(evt_mario_cam_y_off);
USER_FUNC(evt_mario_cont_onoff);
USER_FUNC(evt_mario_dokan_end);
USER_FUNC(evt_mario_dokan_prepare);
USER_FUNC(evt_mario_get_mode);
USER_FUNC(evt_mario_get_motion);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_mario_mov_pos2);
USER_FUNC(evt_mario_paper_pose_dokan);
USER_FUNC(evt_mario_paper_pose_off);
USER_FUNC(evt_mario_party_bero_move);
USER_FUNC(evt_mario_set_dispdir);
USER_FUNC(evt_mario_set_force_dir);
USER_FUNC(evt_mario_set_pos);
USER_FUNC(evt_mario_set_prev_party);
USER_FUNC(evt_mario_set_prev_party_dokan);
USER_FUNC(evt_mario_wait_landon);
USER_FUNC(evt_npc_change_fbat_mode);
USER_FUNC(evt_npc_start_for_event);
USER_FUNC(evt_npc_stop_for_event);
USER_FUNC(evt_party_run);
USER_FUNC(evt_party_set_homing_dist);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
USER_FUNC(evt_run_case_evt_bero);
USER_FUNC(evt_seq_wait);
USER_FUNC(evt_snd_sfxon_3d);
USER_FUNC(evt_sub_get_system_flag);
USER_FUNC(evt_sub_intpl_msec_get_value_para);
USER_FUNC(evt_sub_intpl_msec_init);
USER_FUNC(evt_bero_overwrite);
USER_FUNC(evt_bero_id_filter);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_get_now_number);
USER_FUNC(evt_bero_get_info_nextarea);
USER_FUNC(evt_bero_get_end_position);
USER_FUNC(evt_bero_get_start_position);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_entername);
extern s32 bero_set_disp_position_pipe();
extern s32 bero_null[];
extern s32 default_entevt[];
extern s32 default_outevt[];
extern s32 evt_bero_info_run_none[];
extern s32 evt_bero_info_run_gate[];
extern s32 evt_bero_nonride_check[];
extern s32 bero_open_door_play_se[];
extern s32 bero_close_door_play_se[];
extern s32 bero_play_enter_anime[];
extern s32 bero_play_out_anime[];
extern s32 bero_case_init_check[];
extern s32 bero_case_exec_none[];
extern s32 bero_case_exec_road[];
extern s32 bero_case_exec_door[];
extern s32 bero_case_exec_pipe_sub[];
extern s32 bero_case_exec_pipe[];
extern s32 bero_case_exec_gate[];
extern s32 bero_case_entry[];
extern s32 bero_case_entry_sub[];
extern s32 bero_case_switch_on[];
extern s32 bero_case_switch_off[];
extern s32 evt_bero_info_run_road[];
extern s32 evt_bero_info_run_door[];
extern s32 evt_bero_info_run_pipe_sub00[];
extern s32 evt_bero_info_run_pipe[];
extern s32 evt_bero_info_run[];
extern s32 evt_bero_initial_pos[];
extern s32 evt_bero_mario_enter[];

s32 bero_null[] = {
    0, 251658240, 20000, 100000, 0, 0, -1, 0,
    -1, 0, 0, 0, 65537, 0, 0,
};

s32 default_entevt[] = {
    131122, -30000000, 0, 2, 1,
};

s32 default_outevt[] = {
    131122, -30000000, 0, 2, 1,
};

s32 evt_bero_info_run_none[] = {
    131163, (s32)evt_mario_key_onoff, 1, 2, 1,
};

s32 evt_bero_info_run_gate[] = {
    131163, (s32)evt_mario_key_onoff, 1, 2, 1,
};



//new in retail, f32* x, f32* y, f32* z
//new in retail, no args
extern void N_marioSetBottomlessRespawnPosOnBeroEntry(f32 x, f32 y, f32 z);

#ifdef NONMATCHING
USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry) {
	s32* args = event->args;
	s32 x, y, z;

	x = evtGetValue(event, args[0]);
	y = evtGetValue(event, args[1]);
	z = evtGetValue(event, args[2]);
	N_marioSetBottomlessRespawnPosOnBeroEntry((f32)x, (f32)y, (f32)z);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos) {
	MarioWork* wp = marioGetPtr();
	N_marioSetBottomlessRespawnPosOnBeroEntry(wp->position.x, wp->position.y, wp->position.z);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 bero_get_BeroEXEC(void) {
	return BeroEXEC;
}
#endif

#ifdef NONMATCHING
s32 bero_get_BeroNUM(void) {
	return BeroNUM;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSX(void) {
	return BeroSX;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSY(void) {
	return BeroSY;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSZ(void) {
	return BeroSZ;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEX(void) {
	return BeroEX;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEY(void) {
	return BeroEY;
}
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEZ(void) {
	return BeroEZ;
}
#endif

#ifdef NONMATCHING
BeroEntry** bero_get_ptr(void) {
	return BeroINFOARR;
}
#endif

#ifdef NONMATCHING
void bero_clear_Offset(void) {
	BeroOX = 0.0f;
	BeroOY = 0.0f;
	BeroOZ = 0.0f;
}
#endif

#ifdef NONMATCHING
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
#endif

//const char** mapName, const char** beroName
#ifdef NONMATCHING
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
#endif

//s32 retIndex
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_entername) {
	evtSetValue(event, *event->args, (s32)&gp->beroEnterName);
	return EVT_RETURN_DONE;
}
#endif

//BOOL* on/off, s32* mask
#ifdef NONMATCHING
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
#endif

//s32 retIndex
#ifdef NONMATCHING
USER_FUNC(evt_bero_exec_get) {
	evtSetValue(event, *event->args, BeroEXEC);
	return EVT_RETURN_DONE;
}
#endif

//s32* mask, TODO: add states, change EvtStatus to s32 and do #defines
#ifdef NONMATCHING
USER_FUNC(evt_bero_exec_wait) {
	return evtGetValue(event, *event->args) & BeroEXEC ? EVT_RETURN_DONE : 0;
}
#endif

//f32 retX, f32 retY, f32 retZ
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_start_position) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroSX);
	evtSetFloat(event, args[1], BeroSY);
	evtSetFloat(event, args[2], BeroSZ);
	return EVT_RETURN_DONE;
}
#endif

//f32 retX, f32 retY, f32 retZ
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_end_position) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroEX);
	evtSetFloat(event, args[1], BeroEY);
	evtSetFloat(event, args[2], BeroEZ);
	return EVT_RETURN_DONE;
}
#endif

//s32* id, s32 retIndex1, s32 retIndex2, s32 retIndex3, s32 retIndex4
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_anime) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->enterAnimeType);
	evtSetValue(event, args[2], *(u16*)&bero->exitAnimeType);
	evtSetValue(event, args[3], bero->enterAnimeArg);
	evtSetValue(event, args[4], bero->exitAnimeArg);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_length) {
	BeroEntry* bero;
	s32* args = event->args;
	s32 v5;
	f32 storeme;

	args = event->args;
	bero = BeroINFOARR[evtGetValue(event, args[0])];
	v5 = bero->length;
	if (v5 != -1) {
		evtSetFloat(event, args[1], (f32)v5);
		return EVT_RETURN_DONE;
	}
	switch (*(u16*)&bero->type & 0xFFF) {
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_kinddir) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->type);
	evtSetValue(event, args[2], *(u16*)&bero->sfxId);
	evtSetValue(event, args[3], bero->directionId);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_nextarea) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], bero->nextMapName);
	evtSetValue(event, args[2], (s32)bero->nextBeroName);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_set_now_number) {
	BeroNOWNUM = evtGetValue(event, *event->args);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_now_number) {
	evtSetValue(event, *event->args, BeroNOWNUM);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info) {
	BeroEntry** table;
	s32 i;
	BeroEntry* entry;
	HitEntry* hit;
	s32* switches;
	s32 val;

	table = BeroINFOARR;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	*table++ = NULL;
	table = BeroINFOARR;
	
	{
	BeroEntry* en;
	for (en = (BeroEntry*)event->lwData[0];; en++) {
		HitEntry* h = hitNameToPtr(en->hitName);
		if (!en->hitName) {
			break;
		}
		if (!h) {
			mapErrorEntry(1, en->hitName);
		}
	}
	}
	{
	BeroEntry* e = (BeroEntry*)event->lwData[0];
	switches = BeroSW;
	i = 0;
	while (1) {
		if (!e->hitName) {
			break;
		}
		*table = e;
		switches[i] = -1;
		table++;
		i++;
		e++;
	}
	}
	BeroNUM = i;
	BeroEXEC = 0;
	return EVT_RETURN_DONE;
}
#endif

extern void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end);
extern void N_marioReloadMapOnBottomlessOn(void);
extern double sin(double);
extern double cos(double);

#ifdef NONMATCHING
static inline s32 bero_get_kind(BeroEntry* bero) {
	u32 i;
	const char* dirs[8] = {"n_", "ne_", "e_", "se_", "s_", "sw_", "w_", "nw_"};
	s32 kind = bero->directionId;
	switch (kind) {
	case 20000:
		if (kind == 10000) {
			kind = 10000;
		} else {
		switch (*(u16*)&bero->type & 0xFFF) {
			case 0:
			case 1:
				for (i = 0; i < 8; i++) {
					if (!strncmp(dirs[i], bero->hitName, strlen(dirs[i]))) {
						break;
					}
				}
				break;
			default:
				i = 10000;
				break;
		}
		kind = i;
		}
		break;
	}
	return kind;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_into_info) {
	s32 i;
	BeroEntry* bero;
	s32* evt;
	BeroEntry** table;

	for (i = 0;; i++) {
		bero = BeroINFOARR[i];
		if (!bero || !strcmp(gp->beroEnterName, "")) {
			i = 0;
			bero = (BeroEntry*)bero_null;
			break;
		}
		if (!strcmp(bero->hitName, gp->beroEnterName)) break;
	}
	if ((gp->flags & 2) && !strcmp(gp->beroEnterName, "")) {
		bero = BeroINFOARR[0];
		event->lwData[1] = 0;
		event->lwData[2] = BeroNUM;
		event->lwData[3] = (s32)bero->hitName;
		event->lwData[4] = *(u16*)&bero->type;
		event->lwData[5] = bero_get_kind(bero);
		event->lwData[6] = (s32)&bero->centerPosition;
		evt = bero->enterEvent;
		if (!evt) evt = default_entevt;
		event->lwData[7] = (s32)evt;
		event->lwData[8] = 0xFFFF0000;
		return EVT_RETURN_DONE;
	} else {
		event->lwData[1] = i;
		event->lwData[2] = BeroNUM;
		event->lwData[3] = (s32)gp->beroEnterName;
		event->lwData[4] = *(u16*)&bero->type;
		event->lwData[5] = bero_get_kind(bero);
		event->lwData[6] = (s32)&bero->centerPosition;
		evt = bero->enterEvent;
		if (!evt) evt = default_entevt;
		event->lwData[7] = (s32)evt;
		event->lwData[8] = 0xFFFF0000;
		return EVT_RETURN_DONE;
	}
}
#endif

extern BOOL animGroupBaseAsync(const char* name, s32 group, void* callback);

#ifdef NONMATCHING
USER_FUNC(evt_bero_read_mario_pera) {
	if (isFirstCall) {
		event->userdata[0] = 0;
	}
	switch (event->userdata[0]) {
		case 0:
			if (animGroupBaseAsync(str_802C4DA8, 0, NULL)) {
				event->userdata[0] = 1;
			}
			break;
		case 1:
			if (animGroupBaseAsync("p_dokan_y\0\0", 0, NULL)) {
				event->userdata[0] = 100;
			}
			break;
		case 2:
			break;
		default:
			break;
	}
	return event->userdata[0] == 100 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_id_filter) {
	s32* args = event->args;
	evtSetValue(event, args[0], bero_id_filter(evtGetValue(event, args[0])));
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_num) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroEntry* bero = BeroINFOARR[id];
	s32 kind;
	s32* evt;

	event->lwData[3] = (s32)bero->hitName;
	event->lwData[4] = *(u16*)&bero->type;
	event->lwData[5] = bero_get_kind(bero);
	event->lwData[6] = (s32)&bero->centerPosition;
	evt = bero->enterEvent;
	if (!evt) evt = default_entevt;
	event->lwData[7] = (s32)evt;
	event->lwData[8] = 0xFFFF0000;
	event->lwData[9] = BeroSW[id];
	event->lwData[10] = bero->caseType;
	if (bero->caseType == -1) {
		switch (*(u16*)&bero->type & 0xFFF) {
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
	event->lwData[13] = bero->nextMapName;
	event->lwData[14] = (s32)bero->nextBeroName;
	return EVT_RETURN_DONE;
}
#endif



#ifdef NONMATCHING
s32 bero_get_position_normal(EventEntry *event, BOOL isFirstCall)
{
  s32 *args = event->args;
  MarioWork *wp = marioGetPtr();
  s32 dir = evtGetValue(event, args[0]);
  float new_var3;
  f32 new_var2;
  f32 len = evtGetFloat(event, args[1]);
  s32 *pos = (s32 *) event->lwData[6];
  const char *name = (const char *) event->lwData[3];
  s32 angle = event->lwData[5];
  Vec start;
  f32 *new_var;
  Vec end;
  start.x = pos[0];
  start.y = pos[1];
  start.z = pos[2];
  end.x = pos[0];
  end.y = pos[1];
  end.z = pos[2];
  if (pos[0] == 100000)
  {
    hitObjGetPos((const char *) name, &start);
  }
  if (len != 0.0f)
  {
    Vec tmp2;
    Vec tmp;
    f32 nz;
    f32 ny;
    f32 nx;
    f32 dist;
    f32 hz;
    f32 hy;
    f32 hx;
    f32 deg;
    f32 rad;
    hz = (hy = (hx = 0.0f));
    dist = 1000000.0f;
    deg = 0.125f;
    deg = (angle * 360.0f) * deg;
    new_var3 = 180.0f;
    if (dir == 1)
    {
      deg += new_var3;
    }
    rad = (6.2831855f * deg) / 360.0f;
    tmp.x = start.x - (30.0f * ((f32) sin((6.2831855f * deg) / 360.0f)));
    tmp.y = start.y;
    {
      f32 c0 = (f32) cos(rad);
      tmp.z = start.z - (30.0f * (-c0));
    }
    dist = 1000000.0f;
    new_var = &hx;
    if (hitCheckFilter((void *) 0, new_var, &hy, &hz, &dist, &nx, &ny, &nz, tmp.x, tmp.y, tmp.z, 0.0f, -1.0f, 0.0f))
    {
      tmp.y = hy;
    }
    tmp2 = tmp;
    tmp2.x += (30.0f + len) * ((0, (f32) sin(rad)));
    tmp2.z += (30.0f + len) * (-((f32) cos((6.2831855f * deg) / 360.0f)));
    start = tmp;
    end = tmp2;
  }
  BeroSX = start.x;
  BeroSY = start.y;
  BeroSZ = start.z;
  BeroEX = end.x;
  new_var2 = end.z;
  BeroEY = end.y;
  BeroEZ = end.z;
  N_marioSetBottomlessRespawnPosOnBeroEntry(end.x, end.y, new_var2);
  if (wp->currMotionId == 0x19)
  {
    N_marioReloadMapOnBottomlessOn();
  }
  return 2;
}
#endif

#ifdef NONMATCHING
void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end) {
	f32 hx, hy, hz, dist, nx, ny, nz;
	f32 ofs;
	hz = hy = hx = 0.0f;
	dist = 10000.0f;
	ofs = 20.0f;
	switch (kind) {
	case 6:
		a = -a;
		ofs = -ofs;
	case 2:
		if (id == 0) {
			hitObjGetPos((const char*)name, start);
			start->x -= ofs;
			end->x = start->x + a;
			end->y = start->y;
			end->z = start->z;
			hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, end->x, end->y, end->z, 0.0f, -1.0f, 0.0f);
		} else {
			hitObjGetPos((const char*)name, end);
			end->x -= ofs;
			start->x = end->x + a;
			start->y = end->y;
			start->z = end->z;
			hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, start->x, start->y, start->z, 0.0f, -1.0f, 0.0f);
		}
		end->y = start->y = hy;
		break;
	case 9:
		a = -a;
	case 8:
		if (id == 0) {
			hitObjGetPos((const char*)name, start);
			end->x = start->x;
			end->y = start->y + a;
			end->z = start->z;
		} else {
			hitObjGetPos((const char*)name, end);
			start->x = end->x;
			start->y = end->y + a;
			start->z = end->z;
		}
		break;
	case 10000:
	default:
		hitObjGetPos((const char*)name, start);
		hitObjGetPos((const char*)name, end);
		break;
	}
}
#endif


#ifdef NONMATCHING
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
	BeroEY = (f32)(kind == 8 ? end.y - 37.5f : end.y);
	BeroEZ = end.z;
	N_marioSetBottomlessRespawnPosOnBeroEntry(BeroEX, BeroEY, BeroEZ);
	return EVT_RETURN_DONE;
}
#endif


typedef struct { Vec f_0; Vec pos; Vec at; } BeroCamRoadOut;
extern void camRoadMain(BeroCamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
extern void camRoadReset(void);
extern void camShiftReset(void);

#ifdef NONMATCHING
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
#endif

EVT_BEGIN(evt_bero_nonride_check)
    IF_INT_NOT_EQUAL(LW(10), 6)
        SET_VALUE(LW(0), LW(3))
        CALL_CHILD(PTR(bero_case_switch_on))
        RETURN
    END_IF
    LOOP(0)
        CALL(evt_mario_get_motion, LW(0))
        IF_INT_EQUAL(LW(0), 3)
            BREAK_LOOP
        END_IF
        IF_INT_EQUAL(LW(0), 10)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    DEBUG_PUT_MSG(STRING(str_802C49A8))
    SET_VALUE(LW(0), LW(3))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

EVT_BEGIN(bero_open_door_play_se)
    CALL(evt_bero_get_info_num, LW(1))
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_hit_get_position, LW(3), LW(4), LW(5), LW(6))
    END_IF
    CALL(evt_bero_get_info_kinddir, LW(1), LW(10), LW(11), LW(12))
    SWITCH(LW(11))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_snd_sfxon_3d, STRING(str_802C49B8), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(2)
        CALL(evt_snd_sfxon_3d, STRING(str_802C49C8), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(3)
        CALL(evt_snd_sfxon_3d, STRING(str_802C49DC), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(4)
        CALL(evt_snd_sfxon_3d, STRING(str_802C49F0), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(5)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A04), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(6)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A18), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(7)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A2C), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(8)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A44), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(9)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A5C), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(10)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A70), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(11)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A84), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(12)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A9C), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(13)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4AB4), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(14)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4ACC), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(15)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4AE4), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(16)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4AF8), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(17)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B10), LW(4), LW(5), LW(6), 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(bero_close_door_play_se)
    CALL(evt_bero_get_info_num, LW(1))
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    SET_VALUE(LW(6), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_hit_get_position, LW(3), LW(4), LW(5), LW(6))
    END_IF
    CALL(evt_bero_get_info_kinddir, LW(1), LW(10), LW(11), LW(12))
    SWITCH(LW(11))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B28), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(2)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B38), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(3)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B4C), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(4)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B4C), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(5)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B60), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(6)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B74), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(7)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4B88), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(8)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4BA0), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(9)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4BB8), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(10)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4BCC), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(11)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4A84), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(12)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4BE0), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(13)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4BF8), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(14)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4C10), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(15)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4AE4), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(16)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4C28), LW(4), LW(5), LW(6), 0)
        CASE_EQUAL(17)
        CALL(evt_snd_sfxon_3d, STRING(str_802C4C40), LW(4), LW(5), LW(6), 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(bero_play_enter_anime)
    CALL(evt_bero_get_info_anime, LW(1), LW(10), LW(11), LW(12), LW(13))
    SWITCH(LW(10))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        BEGIN_INLINE_EVENT
            WAIT_MS(200)
            CALL(evt_bero_mario_go)
        END_INLINE_EVENT
        IF_INT_NOT_EQUAL(LW(12), 0)
            CALL(evt_map_playanim, LW(12), 0, 0)
            CALL(evt_map_pauseanim, 0, LW(12))
            WAIT_MS(700)
            SPAWN_EVENT(PTR(bero_close_door_play_se))
            CALL(evt_map_replayanim, 0, LW(12))
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(LW(12), 0)
            BREAK_SWITCH
        END_IF
        SET_VALUE(LW(8), LW(12))
        CALL(evt_mapobj_rotate, 1, LW(8), 0, -80, 0)
        CALL(evt_bero_mario_go)
        WAIT_MS(500)
        SPAWN_EVENT(PTR(bero_close_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, -80, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_rotate, 1, LW(8), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CASE_EQUAL(4)
        IF_INT_NOT_EQUAL(LW(12), 0)
            SPAWN_EVENT(LW(12))
        END_IF
        CASE_EQUAL(5)
        IF_INT_NOT_EQUAL(LW(12), 0)
            SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
            CALL_CHILD(LW(12))
            CALL(evt_bero_mario_go)
            WAIT_MS(500)
            SPAWN_EVENT(PTR(bero_close_door_play_se))
            SET_VALUE(LW(9), LW(12))
            CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(10))
                IF_INT_EQUAL(LW(10), 0)
                    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
                    CALL_CHILD(LW(9))
                    BREAK_LOOP
                    ELSE
                    CALL_CHILD(LW(9))
                END_IF
            END_LOOP
        END_IF
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(bero_play_out_anime)
    CALL(evt_bero_get_info_anime, LW(1), LW(10), LW(11), LW(12), LW(13))
    SWITCH(LW(11))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        IF_INT_NOT_EQUAL(LW(13), 0)
            SPAWN_EVENT(PTR(bero_open_door_play_se))
            CALL(evt_map_playanim, LW(13), 0, 0)
            BEGIN_INLINE_EVENT
                CALL(evt_map_checkanim, LW(13), LW(8), LW(9))
                WAIT_MS(LW(9))
                CALL(evt_bero_mario_go)
            END_INLINE_EVENT
            ELSE
            BEGIN_INLINE_EVENT
                WAIT_MS(500)
                CALL(evt_bero_mario_go)
            END_INLINE_EVENT
        END_IF
        CASE_EQUAL(2)
        IF_INT_EQUAL(LW(12), 0)
            BREAK_SWITCH
        END_IF
        SET_VALUE(LW(8), LW(12))
        SPAWN_EVENT(PTR(bero_open_door_play_se))
        CALL(evt_sub_intpl_msec_init, 11, 0, 80, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_rotate, 1, LW(8), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_bero_mario_go)
        CASE_EQUAL(4)
        IF_INT_NOT_EQUAL(LW(13), 0)
            SPAWN_EVENT(LW(13))
        END_IF
        CASE_EQUAL(5)
        IF_INT_NOT_EQUAL(LW(13), 0)
            SPAWN_EVENT(PTR(bero_open_door_play_se))
            SET_VALUE(LW(9), LW(13))
            CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(10))
                IF_INT_EQUAL(LW(10), 0)
                    SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
                    CALL_CHILD(LW(9))
                    BREAK_LOOP
                    ELSE
                    CALL_CHILD(LW(9))
                END_IF
            END_LOOP
            CALL(evt_bero_mario_go)
        END_IF
    END_SWITCH
    RETURN
EVT_END()


typedef struct { u8 pad[0xac]; u32 flags; s32 kind; } BeroPipeInfo;

#ifdef NONMATCHING
s32 bero_set_disp_position_pipe(BeroPipeInfo* info) {
	switch (info->kind) {
		case 2: case 6:
			if (!(info->flags & 0x1000)) {
				marioGetPtr()->dispOfs.y += 3.0f;
				marioGetPtr()->dispOfs.z -= 15.0f;
			}
			break;
		case 7: case 10000:
			break;
		case 8: case 9:
			if (!(info->flags & 0x1000)) {
				marioGetPtr()->dispOfs.z -= 13.0f;
			} else {
				marioGetPtr()->dispOfs.z -= 20.0f;
			}
			break;
	}
	return 2;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_switch_on) {
	BeroEntry** table = BeroINFOARR;
	s32* args = event->args;
	BeroEntry** temp;
	s32 id = evtGetValue(event, *args++);
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_switch_off) {
	BeroEntry** table = BeroINFOARR;
	s32* args = event->args;
	BeroEntry** temp;
	s32 id = evtGetValue(event, *args++);
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_number) {
	BeroEntry** table = BeroINFOARR;
	s32* args = event->args;
	BeroEntry** temp;
	s32 id = evtGetValue(event, *args++);
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_case_id_save) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroID[id] = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_case_id_load) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], BeroID[id]);
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_disppos_save) {
	BeroOX = marioGetPtr()->dispOfs.x;
	BeroOY = marioGetPtr()->dispOfs.y;
	BeroOZ = marioGetPtr()->dispOfs.z;
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_disppos_load) {
	marioGetPtr()->dispOfs.x = BeroOX;
	marioGetPtr()->dispOfs.y = BeroOY;
	marioGetPtr()->dispOfs.z = BeroOZ;
	return EVT_RETURN_DONE;
}
#endif


#include "system.h"
extern double sin(double);
extern double cos(double);

#ifdef NONMATCHING
USER_FUNC(evt_bero_move_mario_speed) {
	s32* args = event->args;
	f32 speed = evtGetFloat(event, args[0]);
	OSTime now = gp->inBattle ? gp->renderTime : gp->renderFieldTime;
	f32 s, c;
	f32 angle;
	f32 dx, dy;
	f32 dist;
	f32 ox, oy;
	BOOL xdone, ydone;

	if (isFirstCall) {
		event->savedTime = now;
	}
	speed = sysFrame2SecFloat(speed);
	angle = 6.2831855f * reviseAngle(angleABf(BeroSX, BeroSY, BeroEX, BeroEY)) / 360.0f;
	s = sin(angle);
	c = cos(angle);
	dist = speed * sysMsec2Frame((s32)OSTicksToMilliseconds((u64)((s32)now - (s32)event->savedTime)));
	dx = speed * s;
	dy = -(speed * c);
	ox = s * dist;
	marioGetPtr()->position.x = ox + BeroSX;
	oy = -(c * dist);
	marioGetPtr()->position.y = BeroSY + oy;
	marioGetPtr()->position.z = BeroSZ;
	xdone = FALSE;
	if (dx >= 0.0f && BeroEX <= marioGetPtr()->position.x) {
		xdone = TRUE;
	}
	if (dx < 0.0f && BeroEX >= marioGetPtr()->position.x) {
		xdone = TRUE;
	}
	ydone = FALSE;
	if (dy >= 0.0f && BeroEY <= marioGetPtr()->position.y) {
		ydone = TRUE;
	}
	if (dy < 0.0f && BeroEY >= marioGetPtr()->position.y) {
		ydone = TRUE;
	}
	if (xdone + ydone != 2) {
		return EVT_RETURN_BLOCK;
	}
	marioGetPtr()->position.x = BeroEX;
	marioGetPtr()->position.y = BeroEY;
	marioGetPtr()->position.z = BeroEZ;
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_cam_shift_init) {
	camRoadReset();
	camShiftReset();
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go_init) {
	BeroMarioGO = FALSE;
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go) {
	BeroMarioGO = TRUE;
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go_wait) {
	return BeroMarioGO == 0 ? 0 : EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_1stcheck) {
	s32* args = event->args;
	if (strcmp((const char*)event->lwData[13], str_802C4D94) == 0) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return EVT_RETURN_DONE;
}
#endif

extern void camShiftMain(CameraEntry* camera, MarioWork* mario, f32* out);

#ifdef NONMATCHING
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
#endif

EVT_BEGIN(bero_case_init_check)
    CALL(evt_bero_exec_onoff, 1, 65536)
    CALL(evt_bero_exec_get, LW(0))
    AND_RAW(LW(0), 1)
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4095)
    SWITCH(LW(0))
        CASE_OR_EQUAL(0)
        CASE_OR_EQUAL(1)
        CALL(evt_bero_get_info_length, LW(1), LW(0))
        CALL(bero_get_position_normal, 0, LW(0))
        CASE_END
        CASE_OR_EQUAL(3840)
        CASE_OR_EQUAL(3)
        CALL(bero_get_position_normal, 0, FLOAT(0.0f))
        CASE_END
        CASE_EQUAL(2)
        CALL(evt_bero_get_info_length, LW(1), LW(0))
        CALL(bero_get_position_pipe_pure, 0, LW(0))
    END_SWITCH
    CALL(evt_bero_set_now_number, LW(1))
    CALL(evt_bero_exec_onoff, 0, 1)
    SET_VALUE(LW(15), 0)
    CALL_CHILD(LW(11))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_npc_change_fbat_mode, 1)
        CALL(evt_npc_start_for_event)
        CALL(evt_bero_exec_onoff, 0, 65536)
        CALL(evt_bero_exec_onoff, 1, 1)
        SET_VALUE(LW(0), 1)
        RETURN
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_none)
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(PTR(bero_case_init_check))
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_onoff, 0, 65536)
    CALL(evt_bero_exec_onoff, 1, 1)
    CALL(evt_bero_exec_onoff, 0, 8)
    WAIT_FRAMES(2)
    CALL(evt_bero_1stcheck, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(evt_bero_mapchange, LW(13), LW(14))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_road)
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(PTR(bero_case_init_check))
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), LW(5))
        MULTIPLY(LW(0), 45)
        CALL(evt_mario_set_force_dir, LW(0))
        CALL(evt_mario_wait_landon)
        CALL(bero_get_position_normal, 0, FLOAT(150.0f))
        PEEK_FLOAT(LW(10), PTR(&BeroEX))
        PEEK_FLOAT(LW(12), PTR(&BeroEZ))
        CALL(evt_mario_mov_pos2, LW(10), LW(12), FLOAT(150.0f))
        CALL(evt_bero_exec_onoff, 0, 65536)
        CALL(evt_bero_exec_onoff, 1, 1)
    END_INLINE_EVENT
    WAIT_MS(150)
    CALL(evt_bero_exec_onoff, 0, 8)
    WAIT_FRAMES(2)
    CALL(evt_bero_1stcheck, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(evt_bero_mapchange, LW(13), LW(14))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_door)
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(PTR(bero_case_init_check))
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_hitobj_attr_onoff, 0, 1, LW(3), 8388608)
    CALL(evt_bero_mario_go_init)
    SPAWN_EVENT(PTR(bero_play_out_anime))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(0), LW(5))
        MULTIPLY(LW(0), 45)
        CALL(evt_mario_set_force_dir, LW(0))
        CALL(evt_mario_wait_landon)
        CALL(evt_bero_mario_go_wait)
        CALL(bero_get_position_normal, 0, FLOAT(150.0f))
        PEEK_FLOAT(LW(10), PTR(&BeroEX))
        PEEK_FLOAT(LW(12), PTR(&BeroEZ))
        CALL(evt_mario_mov_pos2, LW(10), LW(12), FLOAT(150.0f))
        CALL(evt_bero_exec_onoff, 0, 65536)
        CALL(evt_bero_exec_onoff, 1, 1)
    END_INLINE_EVENT
    CALL(evt_bero_mario_go_wait)
    WAIT_MS(150)
    CALL(evt_bero_exec_onoff, 0, 8)
    WAIT_FRAMES(2)
    CALL(evt_bero_1stcheck, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(evt_bero_mapchange, LW(13), LW(14))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_pipe_sub)
    BEGIN_INLINE_EVENT
        CALL(evt_camera_change_event_from_road)
    END_INLINE_EVENT
    IF_INT_EQUAL(LW(13), 0)
        BEGIN_INLINE_EVENT
            SET_VALUE(LW(0), LW(4))
            AND_RAW(LW(0), 4096)
            IF_INT_EQUAL(LW(0), 0)
                SET_VALUE(LF(0), 0)
                ELSE
                SET_VALUE(LF(0), 1)
            END_IF
            CALL(evt_bero_get_number, LW(14))
            CALL(evt_bero_set_now_number, LW(1))
            CALL(evt_bero_get_info_num, LW(1))
            SET_VALUE(LW(0), LW(4))
            AND_RAW(LW(0), 4096)
            IF_INT_EQUAL(LW(0), 0)
                SET_VALUE(LF(1), 0)
                ELSE
                SET_VALUE(LF(1), 1)
            END_IF
            SET_VALUE(LF(2), 0)
            IF_INT_EQUAL(LF(0), 0)
                IF_INT_EQUAL(LF(1), 1)
                    SET_VALUE(LF(2), 1)
                END_IF
            END_IF
            IF_INT_EQUAL(LF(2), 0)
                POKE_INT(0, PTR(&BeroCAM))
                CALL(evt_bero_get_info_length, LW(1), LW(10))
                CALL(bero_get_position_pipe2, 1, LW(10))
                LOOP(0)
                    PEEK_INT(LW(0), PTR(&BeroCAM))
                    IF_INT_EQUAL(LW(0), 1)
                        BREAK_LOOP
                    END_IF
                    WAIT_FRAMES(1)
                END_LOOP
                CALL(evt_bero_cam3d_change, 500, 11)
            END_IF
        END_INLINE_EVENT
    END_IF
    CALL(evt_bero_disppos_save)
    CALL(evt_bero_get_info_length, LW(1), LW(10))
    CALL(bero_get_position_pipe_pure, 0, LW(10))
    CALL(bero_set_disp_position_pipe)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(str_802C4C70), LW(0), LW(1), LW(2), 0)
    SWITCH(LW(5))
        CASE_EQUAL(6)
        CALL(evt_mario_paper_pose_dokan, 5)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(2)
        CALL(evt_mario_paper_pose_dokan, 5)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 2)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 3)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
    END_SWITCH
    POKE_INT(1, PTR(&BeroCAM))
    IF_INT_EQUAL(LW(13), 0)
        SET_VALUE(LW(0), LW(4))
        AND_RAW(LW(0), 4096)
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 0)
            ELSE
            SET_VALUE(LF(0), 1)
        END_IF
        WAIT_MS(500)
        CALL(evt_bero_get_number, LW(14))
        CALL(evt_bero_get_info_num, LW(1))
        CALL_CHILD(LW(7))
        SET_VALUE(LW(0), LW(4))
        AND_RAW(LW(0), 4096)
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(1), 0)
            ELSE
            SET_VALUE(LF(1), 1)
        END_IF
        CALL(evt_bero_disppos_load)
        CALL(evt_mario_paper_pose_off)
        CALL(evt_bero_disppos_save)
        CALL(evt_bero_exec_get, LW(0))
        IF_BITS_CLEAR(LW(0), 4)
            CALL(evt_bero_exec_onoff, 0, 2)
        END_IF
        CALL(evt_bero_get_info_length, LW(1), LW(10))
        CALL(bero_get_position_pipe_pure, 1, LW(10))
        CALL(bero_set_disp_position_pipe)
        WAIT_MS(500)
        IF_INT_NOT_EQUAL(LF(1), 0)
            CALL(evt_mario_bgmode_on)
            ELSE
            CALL(evt_mario_bgmode_off)
        END_IF
        PEEK_FLOAT(LW(0), PTR(&BeroEX))
        PEEK_FLOAT(LW(1), PTR(&BeroEY))
        PEEK_FLOAT(LW(2), PTR(&BeroEZ))
        CALL(evt_snd_sfxon_3d, STRING(str_802C4C70), LW(0), LW(1), LW(2), 0)
        CALL_CHILD(PTR(evt_bero_info_run_pipe_sub00))
        CALL(evt_bero_exec_get, LW(0))
        IF_BITS_CLEAR(LW(0), 4)
            CALL(evt_bero_exec_onoff, 1, 2)
        END_IF
        CALL(evt_bero_disppos_load)
        CALL(evt_mario_cont_onoff, 1)
        CALL(evt_mario_key_onoff, 1)
        SET_VALUE(LW(0), LW(3))
        CALL_CHILD(PTR(bero_case_switch_off))
        SPAWN_EVENT(PTR(evt_bero_nonride_check))
        CALL(evt_bero_cam_shift_init)
        CALL(evt_cam3d_evt_off, 500, 11)
        ELSE
        CALL(evt_bero_disppos_load)
        CALL(evt_mario_paper_pose_off)
        SET_VALUE(LW(0), LW(4))
        AND_RAW(LW(0), 4096)
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_mario_bgmode_on)
            ELSE
            CALL(evt_mario_bgmode_off)
        END_IF
    END_IF
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_start_for_event)
    CALL(evt_bero_exec_onoff, 0, 65536)
    CALL(evt_bero_exec_onoff, 1, 1)
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_pipe)
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(PTR(bero_case_init_check))
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_wait_landon)
    CALL(evt_mario_cont_onoff, 0)
    IF_INT_EQUAL(LW(13), 0)
        SPAWN_EVENT(PTR(bero_case_exec_pipe_sub))
        RETURN
    END_IF
    CALL(evt_mario_cam_off)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(str_802C4C70), LW(0), LW(1), LW(2), 0)
    SWITCH(LW(5))
        CASE_EQUAL(6)
        CALL(evt_mario_paper_pose_dokan, 5)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(2)
        CALL(evt_mario_paper_pose_dokan, 5)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 2)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 3)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
    END_SWITCH
    IF_BITS_CLEAR(LW(4), 8192)
        SWITCH(LW(5))
            CASE_EQUAL(6)
            CALL(evt_fade_set_mapchange_type, 1, 45, 0, -1, -1)
            CALL(evt_fade_set_mapchange_type, 0, 45, 0, -1, -1)
            CASE_EQUAL(2)
            CALL(evt_fade_set_mapchange_type, 1, 47, 0, -1, -1)
            CALL(evt_fade_set_mapchange_type, 0, 47, 0, -1, -1)
            CASE_EQUAL(8)
            CALL(evt_fade_set_mapchange_type, 1, 41, 0, -1, -1)
            CALL(evt_fade_set_mapchange_type, 0, 41, 0, -1, -1)
            CASE_EQUAL(9)
            CALL(evt_fade_set_mapchange_type, 1, 43, 0, -1, -1)
            CALL(evt_fade_set_mapchange_type, 0, 43, 0, -1, -1)
        END_SWITCH
    END_IF
    CALL(evt_bero_exec_onoff, 0, 8)
    WAIT_FRAMES(2)
    CALL(evt_bero_1stcheck, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(evt_bero_mapchange, LW(13), LW(14))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_exec_gate)
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(PTR(bero_case_init_check))
    CALL(evt_mario_key_onoff, 1)
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_bero_exec_onoff, 0, 65536)
    CALL(evt_bero_exec_onoff, 1, 1)
    CALL(evt_bero_exec_onoff, 0, 8)
    WAIT_FRAMES(2)
    CALL(evt_bero_1stcheck, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        WAIT_MS(1000)
    END_IF
    CALL(evt_bero_mapchange, LW(13), LW(14))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_entry)
    PEEK_INT(LW(2), PTR(&BeroNUM))
    SET_VALUE(LW(1), 0)
    LOOP(0)
        CALL(evt_bero_get_info_num, LW(1))
        IF_INT_EQUAL(LW(9), -1)
            SET_VALUE(LW(0), LW(4))
            AND_RAW(LW(0), 4095)
            SWITCH(LW(0))
                CASE_EQUAL(3840)
                CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_none), LW(15))
                CASE_EQUAL(0)
                CALL(evt_hitobj_attr_onoff, 0, 1, LW(3), 8388608)
                CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_road), LW(15))
                CASE_EQUAL(1)
                CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_door), LW(15))
                CASE_EQUAL(2)
                CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_pipe), LW(15))
                CASE_EQUAL(3)
                CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_gate), LW(15))
            END_SWITCH
            CALL(evt_bero_case_id_save, LW(1), LW(15))
            BEGIN_INLINE_EVENT
                CALL(evt_bero_switch_on, LW(1))
            END_INLINE_EVENT
        END_IF
        ADD(LW(1), 1)
        IF_INT_EQUAL(LW(1), LW(2))
            BREAK_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(bero_case_entry_sub)
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4095)
    SWITCH(LW(0))
        CASE_EQUAL(3840)
        CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_none), LW(15))
        CASE_EQUAL(0)
        CALL(evt_hitobj_attr_onoff, 0, 1, LW(3), 8388608)
        CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_road), LW(15))
        CASE_EQUAL(1)
        CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_door), LW(15))
        CASE_EQUAL(2)
        CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_pipe), LW(15))
        CASE_EQUAL(3)
        CALL(evt_run_case_evt_bero, LW(10), 1, LW(3), 0, PTR(bero_case_exec_gate), LW(15))
    END_SWITCH
    CALL(evt_bero_case_id_save, LW(1), LW(15))
    RETURN
EVT_END()

EVT_BEGIN(bero_case_switch_on)
    CALL(evt_bero_switch_on, LW(0))
    CALL(evt_bero_get_info_num, LW(1))
    IF_INT_EQUAL(LW(0), 0)
        DEBUG_PUT_MSG(STRING(str_802C4C84))
        CALL_CHILD(PTR(bero_case_entry_sub))
        ELSE
        DEBUG_PUT_MSG(STRING(str_802C4C90))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(bero_case_switch_off)
    CALL(evt_bero_switch_off, LW(0))
    CALL(evt_bero_get_info_num, LW(1))
    IF_INT_EQUAL(LW(0), 0)
        DEBUG_PUT_MSG(STRING(str_802C4CC0))
        CALL(evt_bero_case_id_load, LW(1), LW(15))
        CALL(evt_del_case_evt, 0, LW(15))
        CALL(evt_hitobj_attr_onoff, 0, 0, LW(3), 8388608)
        ELSE
        DEBUG_PUT_MSG(STRING(str_802C4CD4))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_info_run_road)
    PEEK_FLOAT(LW(13), PTR(&BeroEX))
    PEEK_FLOAT(LW(14), PTR(&BeroEY))
    PEEK_FLOAT(LW(15), PTR(&BeroEZ))
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(20.0f))
    CALL(evt_mario_mov_pos2, LW(13), LW(15), FLOAT(150.0f))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_party_set_homing_dist, 0, FLOAT(50.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(50.0f))
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_info_run_door)
    CALL(evt_bero_mario_go_init)
    SPAWN_EVENT(PTR(bero_play_enter_anime))
    CALL(evt_bero_mario_go_wait)
    PEEK_FLOAT(LW(13), PTR(&BeroEX))
    PEEK_FLOAT(LW(14), PTR(&BeroEY))
    PEEK_FLOAT(LW(15), PTR(&BeroEZ))
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(20.0f))
    CALL(evt_mario_party_bero_move, LW(13), LW(15), FLOAT(150.0f))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(evt_party_set_homing_dist, 0, FLOAT(50.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(50.0f))
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_info_run_pipe_sub00)
    CALL(evt_party_stop, 0)
    CALL(evt_party_stop, 1)
    SWITCH(LW(5))
        CASE_EQUAL(6)
        CALL(evt_mario_set_dispdir, 180)
        CALL(evt_mario_paper_pose_dokan, 4)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(2)
        CALL(evt_mario_set_dispdir, 0)
        CALL(evt_mario_paper_pose_dokan, 4)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 1)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 0)
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
    END_SWITCH
    CALL(evt_mario_dokan_end)
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_info_run_pipe)
    PEEK_FLOAT(LW(0), PTR(&BeroEX))
    PEEK_FLOAT(LW(1), PTR(&BeroEY))
    PEEK_FLOAT(LW(2), PTR(&BeroEZ))
    CALL(evt_cam_road_reset2, LW(0), LW(1), LW(2))
    CALL(evt_mario_cam_off)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(str_802C4C70), LW(0), LW(1), LW(2), 0)
    CALL_CHILD(PTR(evt_bero_info_run_pipe_sub00))
    CALL(evt_mario_cont_onoff, 1)
    SET_VALUE(LW(0), LW(3))
    CALL_CHILD(PTR(bero_case_switch_off))
    SPAWN_EVENT(PTR(evt_bero_nonride_check))
    CALL(evt_mario_cam_on)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_info_run)
    CALL(evt_bero_get_into_info)
    CALL(evt_bero_set_now_number, LW(1))
    CALL(evt_bero_read_mario_pera)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), 1)
        DEBUG_PUT_MSG(STRING(str_802C4D14))
        CALL(evt_bero_exec_onoff, 0, 1)
        WAIT_FRAMES(1)
        CALL(evt_bero_exec_get, LW(0))
        IF_BITS_CLEAR(LW(0), 4)
            CALL(evt_bero_exec_onoff, 0, 2)
        END_IF
        WAIT_FRAMES(1)
        CALL(evt_bero_exec_get, LW(0))
        IF_BITS_CLEAR(LW(0), 4)
            CALL(evt_bero_exec_onoff, 1, 2)
        END_IF
        CALL(evt_npc_change_fbat_mode, 1)
        CALL(evt_npc_start_for_event)
        CALL(evt_bero_exec_onoff, 1, 1)
        CALL(evt_bero_exec_onoff, 0, 65536)
        CALL_CHILD(PTR(bero_case_entry))
        RETURN
    END_IF
    CALL(evt_bero_exec_get, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    CALL(evt_bero_exec_onoff, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4096)
    IF_INT_NOT_EQUAL(LW(0), 0)
        DEBUG_PUT_MSG(STRING(str_802C4D38))
        CALL(evt_mario_bgmode_on)
        CALL(evt_mario_kill_party, 0)
        CALL(evt_mario_kill_party, 1)
        CALL(evt_mario_cam_y_off)
        ELSE
        DEBUG_PUT_MSG(STRING(str_802C4D5C))
        CALL(evt_mario_bgmode_off)
        SET_VALUE(LW(0), LW(4))
        AND_RAW(LW(0), 4095)
        IF_INT_EQUAL(LW(0), 2)
            CALL(evt_mario_set_prev_party_dokan, 0)
            CALL(evt_mario_set_prev_party_dokan, 1)
            ELSE
            CALL(evt_mario_set_prev_party, 0)
            CALL(evt_mario_set_prev_party, 1)
        END_IF
    END_IF
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4095)
    IF_INT_EQUAL(LW(0), 2)
        SWITCH(LW(5))
            CASE_EQUAL(6)
            CALL(evt_mario_dokan_prepare, 4)
            CASE_EQUAL(2)
            CALL(evt_mario_dokan_prepare, 4)
            CASE_EQUAL(9)
            CALL(evt_mario_dokan_prepare, 1)
            CASE_EQUAL(8)
            CALL(evt_mario_dokan_prepare, 0)
        END_SWITCH
    END_IF
    CALL_CHILD(PTR(evt_bero_initial_pos))
    IF_BITS_CLEAR(LW(4), 8192)
        SET_VALUE(LW(0), LW(4))
        AND_RAW(LW(0), 4095)
        IF_INT_EQUAL(LW(0), 2)
            SWITCH(LW(5))
                CASE_EQUAL(6)
                CALL(evt_fade_set_mapchange_type, 1, -1, -1, 46, 0)
                CALL(evt_fade_set_mapchange_type, 0, -1, -1, 46, 0)
                CASE_EQUAL(2)
                CALL(evt_fade_set_mapchange_type, 1, -1, -1, 48, 0)
                CALL(evt_fade_set_mapchange_type, 0, -1, -1, 48, 0)
                CASE_EQUAL(8)
                CALL(evt_fade_set_mapchange_type, 1, -1, -1, 42, 0)
                CALL(evt_fade_set_mapchange_type, 0, -1, -1, 42, 0)
                CASE_EQUAL(9)
                CALL(evt_fade_set_mapchange_type, 1, -1, -1, 44, 0)
                CALL(evt_fade_set_mapchange_type, 0, -1, -1, 44, 0)
            END_SWITCH
        END_IF
    END_IF
    DEBUG_PUT_MSG(STRING(str_802C4D80))
    SPAWN_EVENT(PTR(evt_bero_mario_enter))
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_initial_pos)
    CALL(evt_bero_get_into_info)
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4095)
    SWITCH(LW(0))
        CASE_EQUAL(3840)
        CASE_EQUAL(3)
        CALL(bero_get_position_normal, 0, FLOAT(0.0f))
        PEEK_FLOAT(LW(10), PTR(&BeroSX))
        PEEK_FLOAT(LW(11), PTR(&BeroSY))
        PEEK_FLOAT(LW(12), PTR(&BeroSZ))
        CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 1, LW(10), LW(11), LW(12))
        CASE_END
        CASE_EQUAL(0)
        CALL(evt_bero_get_info_length, LW(1), LW(10))
        CALL(bero_get_position_normal, 1, LW(10))
        PEEK_FLOAT(LW(10), PTR(&BeroSX))
        PEEK_FLOAT(LW(11), PTR(&BeroSY))
        PEEK_FLOAT(LW(12), PTR(&BeroSZ))
        CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 1, LW(10), LW(11), LW(12))
        CASE_EQUAL(1)
        CALL(evt_bero_get_info_length, LW(1), LW(10))
        CALL(bero_get_position_normal, 1, LW(10))
        PEEK_FLOAT(LW(10), PTR(&BeroSX))
        PEEK_FLOAT(LW(11), PTR(&BeroSY))
        PEEK_FLOAT(LW(12), PTR(&BeroSZ))
        CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 1, LW(10), LW(11), LW(12))
        CASE_EQUAL(2)
        CALL(evt_bero_get_info_length, LW(1), LW(10))
        CALL(bero_get_position_pipe_pure, 1, LW(10))
        PEEK_FLOAT(LW(10), PTR(&BeroSX))
        PEEK_FLOAT(LW(11), PTR(&BeroSY))
        PEEK_FLOAT(LW(12), PTR(&BeroSZ))
        CALL(evt_mario_set_pos, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_party_set_pos, 1, LW(10), LW(11), LW(12))
    END_SWITCH
    CALL(evt_cam_road_reset)
    RETURN
EVT_END()

EVT_BEGIN(evt_bero_mario_enter)
    CALL(evt_seq_wait, 2)
    CALL(evt_npc_change_fbat_mode, 7)
    CALL(evt_npc_stop_for_event)
    CALL_CHILD(LW(7))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_mario_key_onoff, 1)
        GOTO(100)
    END_IF
    CALL(evt_bero_exec_get, LW(0))
    IF_BITS_CLEAR(LW(0), 4)
        CALL(evt_bero_exec_onoff, 0, 2)
    END_IF
    CALL(evt_bero_get_into_info)
    SET_VALUE(LW(0), LW(4))
    AND_RAW(LW(0), 4095)
    SWITCH(LW(0))
        CASE_EQUAL(3840)
        CALL_CHILD(PTR(evt_bero_info_run_none))
        CASE_EQUAL(0)
        CALL_CHILD(PTR(evt_bero_info_run_road))
        CASE_EQUAL(1)
        CALL_CHILD(PTR(evt_bero_info_run_door))
        CASE_EQUAL(2)
        CALL_CHILD(PTR(evt_bero_info_run_pipe))
        CASE_EQUAL(3)
        CALL_CHILD(PTR(evt_bero_info_run_gate))
        CASE_DEFAULT
        CALL(evt_mario_key_onoff, 1)
    END_SWITCH
    CALL(evt_bero_exec_get, LW(0))
    IF_BITS_CLEAR(LW(0), 4)
        CALL(evt_bero_exec_onoff, 1, 2)
    END_IF
    LABEL(100)
    CALL(evt_npc_change_fbat_mode, 1)
    CALL(evt_npc_start_for_event)
    CALL_CHILD(PTR(bero_case_entry))
    CALL(evt_bero_exec_onoff, 1, 1)
    CALL(evt_bero_exec_onoff, 0, 65536)
    RETURN
EVT_END()

#pragma force_active on
__declspec(section ".data") u32 gap_05_8030DA24_data[1] = {0};

#pragma force_active reset

#ifndef NONMATCHING
// ASM-STOPGAP: N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
extern void __div2u(void);
extern void __mod2u(void);
extern void __div2i(void);
extern void __mod2i(void);
extern const char str_8041A3C8[4];
extern const char str_8041A3CC[4];
extern const char str_8041A3D0[4];
extern const char str_8041A3D4[4];
extern const char str_8041A3D8[4];
extern const char str_8041A3DC[4];
extern const char str_8041A3E0[4];
extern const char str_8041A3E4[4];
__declspec(section ".sdata2") const char str_8041A3C8[4] = "n_";
__declspec(section ".sdata2") const char str_8041A3CC[4] = "ne_";
__declspec(section ".sdata2") const char str_8041A3D0[4] = "e_";
__declspec(section ".sdata2") const char str_8041A3D4[4] = "se_";
__declspec(section ".sdata2") const char str_8041A3D8[4] = "s_";
__declspec(section ".sdata2") const char str_8041A3DC[4] = "sw_";
__declspec(section ".sdata2") const char str_8041A3E0[4] = "w_";
__declspec(section ".sdata2") const char str_8041A3E4[4] = "nw_";
__declspec(section ".sdata2") const f32 float_6p2832_8041a3e8 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_360_8041a3ec = 360.0f;
__declspec(section ".sdata2") const f32 float_0_8041a3f0 = 0.0f;
__declspec(section ".sdata2") const f32 float_3_8041a3f4 = 3.0f;
__declspec(section ".sdata2") const f32 float_15_8041a3f8 = 15.0f;
__declspec(section ".sdata2") const f32 float_13_8041a3fc = 13.0f;
__declspec(section ".sdata2") const f32 float_20_8041a400 = 20.0f;
__declspec(section ".sdata2") const f32 float_1_8041a404 = 1.0f;
__declspec(section ".sdata2") const f32 float_37p5_8041a408 = 37.5f;
__declspec(section ".sdata2") const f32 float_10000_8041a40c = 10000.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041a410 = -1.0f;
__declspec(section ".sdata2") const f32 float_1E06_8041a414 = 1000000.0f;
__declspec(section ".sdata2") const f32 float_0p125_8041a418 = 0.125f;
__declspec(section ".sdata2") const f32 float_180_8041a41c = 180.0f;
__declspec(section ".sdata2") const f32 float_30_8041a420 = 30.0f;
__declspec(section ".sdata2") const f32 float_0_8041a424 = 0.0f;
__declspec(section ".sdata2") const f32 float_60_8041a428 = 60.0f;
__declspec(section ".sdata2") const u32 gap_09_8041A42C_sdata2 = 0;

asm s32 evt_camera_change_event_from_road(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	bl marioGetPtr
	mr r0, r3
	li r3, 0x4
	mr r28, r0
	bl camGetPtr
	mr r31, r3
	mr r4, r28
	addi r5, r1, 0x8
	bl camShiftMain
	lfs f3, 0x94(r28)
	addi r3, r1, 0x24
	lfs f2, 0x98(r31)
	lfs f1, 0x8c(r28)
	fmr f6, f3
	fmr f5, f2
	lfs f7, 0x8(r1)
	fmr f4, f1
	bl camRoadMain
	lis r3, vec3_802c4c58@ha
	lis r4, vec3_802c4c64@ha
	addi r5, r3, vec3_802c4c58@l
	lis r3, 0x1062
	addi r8, r4, vec3_802c4c64@l
	lwz r28, 0x0(r5)
	lwz r29, 0x4(r5)
	lis r6, 0x8000
	lwz r10, 0x8(r5)
	addi r7, r3, 0x4dd3
	lwz r30, 0x0(r8)
	li r5, 0x0
	lwz r12, 0x4(r8)
	li r4, 0x3
	lwz r11, 0x8(r8)
	li r0, 0xb
	lfs f5, 0x30(r1)
	li r3, 0x2
	lfs f4, 0x34(r1)
	lfs f3, 0x38(r1)
	lfs f2, 0x3c(r1)
	lfs f1, 0x40(r1)
	lfs f0, 0x44(r1)
	lwz r9, 0xc(r31)
	lwz r8, 0x10(r31)
	stw r28, 0x18(r1)
	stw r9, 0x58(r31)
	stw r8, 0x5c(r31)
	lwz r8, 0x14(r31)
	stw r29, 0x1c(r1)
	stw r8, 0x60(r31)
	stfs f5, 0x18(r1)
	lwz r9, 0x18(r31)
	lwz r8, 0x1c(r31)
	stw r10, 0x20(r1)
	lwz r10, 0x18(r1)
	stw r9, 0x64(r31)
	stw r8, 0x68(r31)
	lwz r8, 0x20(r31)
	stfs f4, 0x1c(r1)
	stw r8, 0x6c(r31)
	lwz r8, 0x1c(r1)
	stfs f3, 0x20(r1)
	stw r30, 0xc(r1)
	lwz r9, 0x20(r1)
	stw r10, 0x40(r31)
	stw r12, 0x10(r1)
	stfs f2, 0xc(r1)
	stw r8, 0x44(r31)
	lwz r8, 0xc(r1)
	stw r11, 0x14(r1)
	stfs f1, 0x10(r1)
	stw r9, 0x48(r31)
	lwz r9, 0x10(r1)
	stfs f0, 0x14(r1)
	stw r8, 0x4c(r31)
	lwz r8, 0x14(r1)
	stw r9, 0x50(r31)
	stw r8, 0x54(r31)
	lwz r9, gp(r13)
	lwz r8, 0x38(r9)
	lwz r9, 0x3c(r9)
	stw r9, 0x74(r31)
	stw r8, 0x70(r31)
	lwz r6, 0xf8(r6)
	srwi r6, r6, 2
	mulhwu r6, r7, r6
	srwi r6, r6, 6
	mulli r6, r6, 0x1f4
	stw r6, 0x7c(r31)
	stw r5, 0x78(r31)
	sth r4, 0x4(r31)
	stb r0, 0x80(r31)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r28, 0x50(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_bero_1stcheck(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lis r3, str_802C4D94@ha
	addi r4, r3, str_802C4D94@l
	lwz r31, 0x18(r30)
	lwz r3, 0xd0(r30)
	bl strcmp
	cmpwi r3, 0x0
	bne @1
	lwz r4, 0x0(r31)
	mr r3, r30
	li r5, 0x1
	bl evtSetValue
	b @2
	@1:
	lwz r4, 0x0(r31)
	mr r3, r30
	li r5, 0x0
	bl evtSetValue
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_mario_go_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	lwz r3, BeroMarioGO(r13)
	li r0, 0x2
	cntlzw r3, r3
	extrwi r3, r3, 1, 26
	neg r3, r3
	andc r3, r0, r3
	blr
}

asm s32 evt_bero_mario_go(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	li r0, 0x1
	li r3, 0x2
	stw r0, BeroMarioGO(r13)
	blr
}

asm s32 evt_bero_mario_go_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	li r0, 0x0
	li r3, 0x2
	stw r0, BeroMarioGO(r13)
	blr
}

asm s32 evt_bero_cam_shift_init(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl camRoadReset
	bl camShiftReset
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_cam3d_change(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	li r3, 0x4
	lwz r31, 0x18(r29)
	bl camGetPtr
	lwz r4, 0x0(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	lwz r0, 0xc(r30)
	lis r4, 0x1062
	lwz r7, 0x10(r30)
	addi r6, r4, 0x4dd3
	lis r5, 0x8000
	li r4, 0x0
	stw r0, 0x58(r30)
	li r0, 0x3
	stw r7, 0x5c(r30)
	lwz r7, 0x14(r30)
	stw r7, 0x60(r30)
	lwz r8, 0x18(r30)
	lwz r7, 0x1c(r30)
	stw r8, 0x64(r30)
	stw r7, 0x68(r30)
	lwz r7, 0x20(r30)
	stw r7, 0x6c(r30)
	lwz r8, BeroPT(r13)
	lwz r7, BeroPT+0x4(r13)
	stw r8, 0x40(r30)
	stw r7, 0x44(r30)
	lwz r7, BeroPT+0x8(r13)
	stw r7, 0x48(r30)
	lwz r8, BeroAT(r13)
	lwz r7, BeroAT+0x4(r13)
	stw r8, 0x4c(r30)
	stw r7, 0x50(r30)
	lwz r7, BeroAT+0x8(r13)
	stw r7, 0x54(r30)
	lwz r8, gp(r13)
	lwz r7, 0x38(r8)
	lwz r8, 0x3c(r8)
	stw r8, 0x74(r30)
	stw r7, 0x70(r30)
	lwz r5, 0xf8(r5)
	srwi r5, r5, 2
	mulhwu r5, r6, r5
	srwi r5, r5, 6
	mullw r5, r31, r5
	stw r5, 0x7c(r30)
	stw r4, 0x78(r30)
	sth r0, 0x4(r30)
	stb r3, 0x80(r30)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x24(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_overwrite(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x24(r1)
	addi r0, r4, BeroINFOARR@l
	stw r31, 0x1c(r1)
	mr r31, r0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	cmpwi r3, 0x0
	stw r3, 0x8(r1)
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r29, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	lwz r3, 0x0(r31)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r31, r31, 0x4
	beq @3
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @3
	@2:
	lwz r4, 0x4(r30)
	mr r3, r28
	bl evtGetValue
	lwz r0, 0x8(r1)
	lis r4, BeroINFOARR@ha
	addi r4, r4, BeroINFOARR@l
	slwi r0, r0, 2
	stwx r3, r4, r0
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_move_mario_speed(EventEntry* event, BOOL isFirstCall) {
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
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stfd f27, 0x30(r1)
	psq_st f27, 0x38(r1), 0, 0
	stfd f26, 0x20(r1)
	psq_st f26, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	mr r30, r4
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetFloat
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq @1
	lwz r0, 0x38(r3)
	lwz r31, 0x3c(r3)
	b @2
	@1:
	lwz r0, 0x40(r3)
	lwz r31, 0x44(r3)
	@2:
	cmpwi r30, 0x0
	beq @3
	stw r31, 0x19c(r29)
	stw r0, 0x198(r29)
	@3:
	bl sysFrame2SecFloat
	fmr f29, f1
	lfs f1, BeroSX(r13)
	lfs f2, BeroSY(r13)
	lfs f3, BeroEX(r13)
	lfs f4, BeroEY(r13)
	bl angleABf
	bl reviseAngle
	lfs f2, float_6p2832_8041a3e8(r2)
	lfs f0, float_360_8041a3ec(r2)
	fmuls f1, f2, f1
	fdivs f27, f1, f0
	fmr f1, f27
	bl sin
	frsp f28, f1
	fmr f1, f27
	bl cos
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r3, r3, 0x4dd3
	lwz r4, 0x19c(r29)
	frsp f27, f1
	srwi r0, r0, 2
	li r5, 0x0
	mulhwu r0, r3, r0
	subf r4, r4, r31
	srawi r3, r4, 31
	srwi r6, r0, 6
	bl __div2u
	mr r3, r4
	bl sysMsec2Frame
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_802c4da0@ha
	fmuls f2, f29, f27
	lfd f1, double_to_int_802c4da0@l(r4)
	stw r0, 0x8(r1)
	fmuls f31, f29, f28
	lfd f0, 0x8(r1)
	fneg f30, f2
	lfs f2, BeroSX(r13)
	fsubs f0, f0, f1
	fmuls f26, f29, f0
	fmuls f0, f28, f26
	fadds f29, f2, f0
	bl marioGetPtr
	fmuls f0, f27, f26
	stfs f29, 0x8c(r3)
	lfs f1, BeroSY(r13)
	fneg f0, f0
	fadds f29, f1, f0
	bl marioGetPtr
	stfs f29, 0x90(r3)
	lfs f29, BeroSZ(r13)
	bl marioGetPtr
	lfs f0, float_0_8041a3f0(r2)
	li r31, 0x0
	stfs f29, 0x94(r3)
	fcmpo cr0, f31, f0
	cror eq, gt, eq
	bne @4
	bl marioGetPtr
	lfs f1, 0x8c(r3)
	lfs f0, BeroEX(r13)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @4
	li r31, 0x1
	@4:
	lfs f0, float_0_8041a3f0(r2)
	fcmpo cr0, f31, f0
	bge @5
	bl marioGetPtr
	lfs f1, 0x8c(r3)
	lfs f0, BeroEX(r13)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @5
	li r31, 0x1
	@5:
	lfs f0, float_0_8041a3f0(r2)
	li r30, 0x0
	fcmpo cr0, f30, f0
	cror eq, gt, eq
	bne @6
	bl marioGetPtr
	lfs f1, 0x90(r3)
	lfs f0, BeroEY(r13)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @6
	li r30, 0x1
	@6:
	lfs f0, float_0_8041a3f0(r2)
	fcmpo cr0, f30, f0
	bge @7
	bl marioGetPtr
	lfs f1, 0x90(r3)
	lfs f0, BeroEY(r13)
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @7
	li r30, 0x1
	@7:
	add r0, r31, r30
	cmpwi r0, 0x2
	beq @8
	li r3, 0x0
	b @9
	@8:
	lfs f30, BeroEX(r13)
	bl marioGetPtr
	stfs f30, 0x8c(r3)
	lfs f30, BeroEY(r13)
	bl marioGetPtr
	stfs f30, 0x90(r3)
	lfs f30, BeroEZ(r13)
	bl marioGetPtr
	stfs f30, 0x94(r3)
	li r3, 0x2
	@9:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	psq_l f27, 0x38(r1), 0, 0
	lfd f27, 0x30(r1)
	psq_l f26, 0x28(r1), 0, 0
	lfd f26, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x84(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 evt_bero_disppos_load(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x10(r1)
	psq_st f31, 0x18(r1), 0, 0
	lfs f31, BeroOX(r13)
	bl marioGetPtr
	stfs f31, 0x98(r3)
	lfs f31, BeroOY(r13)
	bl marioGetPtr
	stfs f31, 0x9c(r3)
	lfs f31, BeroOZ(r13)
	bl marioGetPtr
	stfs f31, 0xa0(r3)
	li r3, 0x2
	psq_l f31, 0x18(r1), 0, 0
	lwz r0, 0x24(r1)
	lfd f31, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_disppos_save(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lfs f0, 0x98(r3)
	stfs f0, BeroOX(r13)
	bl marioGetPtr
	lfs f0, 0x9c(r3)
	stfs f0, BeroOY(r13)
	bl marioGetPtr
	lfs f0, 0xa0(r3)
	li r3, 0x2
	stfs f0, BeroOZ(r13)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_case_id_load(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lis r5, BeroID@ha
	slwi r0, r3, 2
	addi r5, r5, BeroID@l
	lwz r4, 0x4(r31)
	lwzx r5, r5, r0
	mr r3, r30
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_case_id_save(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lis r4, BeroID@ha
	slwi r0, r31, 2
	addi r4, r4, BeroID@l
	stwx r3, r4, r0
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_get_number(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x24(r1)
	addi r0, r4, BeroINFOARR@l
	stw r31, 0x1c(r1)
	mr r31, r0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r5, 0x18(r3)
	lwz r4, 0x0(r5)
	bl evtGetValue
	cmpwi r3, 0x0
	stw r3, 0x8(r1)
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r30, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	lwz r3, 0x0(r31)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r31, r31, 0x4
	beq @3
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @3
	@2:
	lwz r0, 0x8(r1)
	li r3, 0x2
	stw r0, 0xa0(r29)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_switch_off(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x24(r1)
	addi r0, r4, BeroINFOARR@l
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	mr r30, r0
	stw r29, 0x14(r1)
	lwz r5, 0x18(r3)
	lwz r4, 0x0(r5)
	bl evtGetValue
	cmpwi r3, 0x0
	stw r3, 0x8(r1)
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r29, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	lwz r3, 0x0(r30)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r30, r30, 0x4
	beq @3
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @3
	@2:
	lwz r0, 0x8(r1)
	lis r3, BeroSW@ha
	addi r3, r3, BeroSW@l
	slwi r0, r0, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x1
	beq @4
	li r0, 0x1
	stw r0, 0x9c(r31)
	b @5
	@4:
	li r0, 0x0
	stw r0, 0x9c(r31)
	@5:
	lwz r6, 0x8(r1)
	lis r3, BeroSW@ha
	addi r4, r3, BeroSW@l
	li r5, 0x0
	slwi r0, r6, 2
	li r3, 0x2
	stwx r5, r4, r0
	stw r6, 0xa0(r31)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_switch_on(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x24(r1)
	addi r0, r4, BeroINFOARR@l
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	mr r30, r0
	stw r29, 0x14(r1)
	lwz r5, 0x18(r3)
	lwz r4, 0x0(r5)
	bl evtGetValue
	cmpwi r3, 0x0
	stw r3, 0x8(r1)
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r29, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	lwz r3, 0x0(r30)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r30, r30, 0x4
	beq @3
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @3
	@2:
	lwz r0, 0x8(r1)
	lis r3, BeroSW@ha
	addi r3, r3, BeroSW@l
	slwi r0, r0, 2
	lwzx r0, r3, r0
	cmpwi r0, 0x1
	bne @4
	li r0, 0x1
	stw r0, 0x9c(r31)
	b @5
	@4:
	li r0, 0x0
	stw r0, 0x9c(r31)
	@5:
	lwz r6, 0x8(r1)
	lis r3, BeroSW@ha
	addi r4, r3, BeroSW@l
	li r5, 0x1
	slwi r0, r6, 2
	li r3, 0x2
	stwx r5, r4, r0
	stw r6, 0xa0(r31)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 bero_set_disp_position_pipe(BeroPipeInfo* info) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r0, 0xb0(r3)
	cmpwi r0, 0x7
	beq @1
	bge @2
	cmpwi r0, 0x2
	beq @3
	blt @1
	cmpwi r0, 0x6
	bge @3
	b @1
	@2:
	cmpwi r0, 0x2710
	beq @1
	bge @1
	cmpwi r0, 0xa
	bge @1
	b @4
	@3:
	lwz r0, 0xac(r3)
	rlwinm. r0, r0, 0, 19, 19
	bne @1
	bl marioGetPtr
	lfs f1, 0x9c(r3)
	lfs f0, float_3_8041a3f4(r2)
	fadds f0, f1, f0
	stfs f0, 0x9c(r3)
	bl marioGetPtr
	lfs f1, 0xa0(r3)
	lfs f0, float_15_8041a3f8(r2)
	fsubs f0, f1, f0
	stfs f0, 0xa0(r3)
	b @1
	@4:
	lwz r0, 0xac(r3)
	rlwinm. r0, r0, 0, 19, 19
	bne @5
	bl marioGetPtr
	lfs f1, 0xa0(r3)
	lfs f0, float_13_8041a3fc(r2)
	fsubs f0, f1, f0
	stfs f0, 0xa0(r3)
	b @1
	@5:
	bl marioGetPtr
	lfs f1, 0xa0(r3)
	lfs f0, float_20_8041a400(r2)
	fsubs f0, f1, f0
	stfs f0, 0xa0(r3)
	@1:
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 bero_get_position_pipe2(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stw r31, 0x6c(r1)
	stw r30, 0x68(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fctiwz f0, f1
	lwz r5, 0xa8(r30)
	lwz r6, 0xb0(r30)
	mr r3, r31
	addi r7, r1, 0x2c
	addi r8, r1, 0x20
	stfd f0, 0x60(r1)
	lwz r4, 0x64(r1)
	bl bero_get_position_pipe_sub
	lfs f1, 0x24(r1)
	lfs f0, float_1_8041a404(r2)
	fadds f0, f1, f0
	stfs f0, 0x24(r1)
	bl camRoadReset
	bl camShiftReset
	lfs f3, 0x28(r1)
	addi r3, r1, 0x38
	lfs f2, 0x24(r1)
	lfs f1, 0x20(r1)
	fmr f6, f3
	fmr f5, f2
	lfs f7, float_0_8041a3f0(r2)
	fmr f4, f1
	bl camRoadMain
	lis r4, vec3_802c4990@ha
	lwzu r9, vec3_802c4990@l(r4)
	lis r3, vec3_802c499c@ha
	lfs f5, 0x44(r1)
	addi r6, r3, vec3_802c499c@l
	lwz r8, 0x4(r4)
	lwz r7, 0x8(r4)
	li r3, 0x2
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r9, 0x14(r1)
	lfs f4, 0x48(r1)
	stw r8, 0x18(r1)
	lfs f3, 0x4c(r1)
	stw r7, 0x1c(r1)
	lfs f2, 0x50(r1)
	stw r5, 0x8(r1)
	lfs f1, 0x54(r1)
	stw r4, 0xc(r1)
	lfs f0, 0x58(r1)
	stw r0, 0x10(r1)
	stfs f5, 0x14(r1)
	stfs f4, 0x18(r1)
	lwz r8, 0x14(r1)
	stfs f3, 0x1c(r1)
	lwz r7, 0x18(r1)
	stfs f2, 0x8(r1)
	lwz r6, 0x1c(r1)
	stfs f1, 0xc(r1)
	lwz r5, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r4, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r8, BeroPT(r13)
	stw r7, BeroPT+0x4(r13)
	stw r6, BeroPT+0x8(r13)
	stw r5, BeroAT(r13)
	stw r4, BeroAT+0x4(r13)
	stw r0, BeroAT+0x8(r13)
	lwz r31, 0x6c(r1)
	lwz r0, 0x74(r1)
	lwz r30, 0x68(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 bero_get_position_pipe_pure(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetFloat
	fctiwz f0, f1
	lwz r30, 0xb0(r29)
	lwz r5, 0xa8(r29)
	mr r3, r31
	mr r6, r30
	addi r7, r1, 0x14
	stfd f0, 0x20(r1)
	addi r8, r1, 0x8
	lwz r4, 0x24(r1)
	bl bero_get_position_pipe_sub
	lfs f0, 0x14(r1)
	cmpwi r30, 0x8
	stfs f0, BeroSX(r13)
	bne @1
	lfs f1, 0x18(r1)
	lfs f0, float_37p5_8041a408(r2)
	fsubs f2, f1, f0
	b @2
	@1:
	lfs f2, 0x18(r1)
	@2:
	lfs f0, 0x1c(r1)
	cmpwi r30, 0x8
	lfs f1, 0x8(r1)
	stfs f2, BeroSY(r13)
	stfs f0, BeroSZ(r13)
	stfs f1, BeroEX(r13)
	bne @3
	lfs f2, 0xc(r1)
	lfs f0, float_37p5_8041a408(r2)
	fsubs f0, f2, f0
	b @4
	@3:
	lfs f0, 0xc(r1)
	@4:
	lfs f3, 0x10(r1)
	frsp f2, f0
	stfs f0, BeroEY(r13)
	stfs f3, BeroEZ(r13)
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	lwz r0, 0x44(r1)
	li r3, 0x2
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	stw r28, 0x30(r1)
	lfs f1, float_0_8041a3f0(r2)
	cmpwi r6, 0x8
	lfs f0, float_10000_8041a40c(r2)
	mr r28, r4
	stfs f1, 0x20(r1)
	mr r29, r5
	lfs f31, float_20_8041a400(r2)
	mr r30, r7
	stfs f1, 0x1c(r1)
	mr r31, r8
	stfs f1, 0x18(r1)
	stfs f0, 0x14(r1)
	beq @1
	bge @2
	cmpwi r6, 0x6
	beq @3
	bge @4
	cmpwi r6, 0x2
	beq @5
	b @4
	@2:
	cmpwi r6, 0x2710
	beq @4
	bge @4
	cmpwi r6, 0xa
	bge @4
	b @6
	@3:
	neg r28, r28
	fneg f31, f31
	@5:
	cmpwi r3, 0x0
	bne @7
	mr r3, r29
	mr r4, r30
	bl hitObjGetPos
	lfs f0, 0x0(r30)
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c4da0@ha
	fsubs f0, f0, f31
	stw r3, 0x2c(r1)
	addi r3, r4, double_to_int_802c4da0@l
	lfs f4, float_0_8041a3f0(r2)
	stw r0, 0x28(r1)
	addi r4, r1, 0x20
	stfs f0, 0x0(r30)
	fmr f6, f4
	lfd f1, 0x0(r3)
	addi r5, r1, 0x1c
	lfd f0, 0x28(r1)
	addi r6, r1, 0x18
	lfs f2, 0x0(r30)
	fsubs f0, f0, f1
	lfs f5, float_neg1_8041a410(r2)
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	fadds f0, f2, f0
	li r3, 0x0
	stfs f0, 0x0(r31)
	lfs f0, 0x4(r30)
	stfs f0, 0x4(r31)
	lfs f0, 0x8(r30)
	stfs f0, 0x8(r31)
	lfs f1, 0x0(r31)
	lfs f2, 0x4(r31)
	lfs f3, 0x8(r31)
	bl hitCheckFilter
	b @8
	@7:
	mr r3, r29
	mr r4, r31
	bl hitObjGetPos
	lfs f0, 0x0(r31)
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c4da0@ha
	fsubs f0, f0, f31
	stw r3, 0x2c(r1)
	addi r3, r4, double_to_int_802c4da0@l
	lfs f4, float_0_8041a3f0(r2)
	stw r0, 0x28(r1)
	addi r4, r1, 0x20
	stfs f0, 0x0(r31)
	fmr f6, f4
	lfd f1, 0x0(r3)
	addi r5, r1, 0x1c
	lfd f0, 0x28(r1)
	addi r6, r1, 0x18
	lfs f2, 0x0(r31)
	fsubs f0, f0, f1
	lfs f5, float_neg1_8041a410(r2)
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	fadds f0, f2, f0
	li r3, 0x0
	stfs f0, 0x0(r30)
	lfs f0, 0x4(r31)
	stfs f0, 0x4(r30)
	lfs f0, 0x8(r31)
	stfs f0, 0x8(r30)
	lfs f1, 0x0(r30)
	lfs f2, 0x4(r30)
	lfs f3, 0x8(r30)
	bl hitCheckFilter
	@8:
	lfs f0, 0x1c(r1)
	stfs f0, 0x4(r30)
	stfs f0, 0x4(r31)
	b @9
	@6:
	neg r28, r28
	@1:
	cmpwi r3, 0x0
	bne @10
	mr r3, r29
	mr r4, r30
	bl hitObjGetPos
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	stw r3, 0x2c(r1)
	lis r4, double_to_int_802c4da0@ha
	lfs f2, 0x0(r30)
	stw r0, 0x28(r1)
	lfd f1, double_to_int_802c4da0@l(r4)
	lfd f0, 0x28(r1)
	stfs f2, 0x0(r31)
	fsubs f0, f0, f1
	lfs f1, 0x4(r30)
	fadds f0, f1, f0
	stfs f0, 0x4(r31)
	lfs f0, 0x8(r30)
	stfs f0, 0x8(r31)
	b @9
	@10:
	mr r3, r29
	mr r4, r31
	bl hitObjGetPos
	xoris r3, r28, 0x8000
	lis r0, 0x4330
	stw r3, 0x2c(r1)
	lis r4, double_to_int_802c4da0@ha
	lfs f2, 0x0(r31)
	stw r0, 0x28(r1)
	lfd f1, double_to_int_802c4da0@l(r4)
	lfd f0, 0x28(r1)
	stfs f2, 0x0(r30)
	fsubs f0, f0, f1
	lfs f1, 0x4(r31)
	fadds f0, f1, f0
	stfs f0, 0x4(r30)
	lfs f0, 0x8(r31)
	stfs f0, 0x8(r30)
	b @9
	@4:
	mr r3, r29
	mr r4, r30
	bl hitObjGetPos
	mr r3, r29
	mr r4, r31
	bl hitObjGetPos
	@9:
	psq_l f31, 0x48(r1), 0, 0
	lwz r0, 0x54(r1)
	lfd f31, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	lwz r28, 0x30(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 bero_get_position_normal(EventEntry *event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stfd f30, 0xa0(r1)
	psq_st f30, 0xa8(r1), 0, 0
	stw r31, 0x9c(r1)
	stw r30, 0x98(r1)
	stw r29, 0x94(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	bl marioGetPtr
	lwz r4, 0x0(r30)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	lwz r7, 0xb4(r29)
	lis r4, 0x4330
	lis r3, double_to_int_802c4da0@ha
	stw r4, 0x58(r1)
	lwz r6, 0x0(r7)
	fmr f31, f1
	lfd f4, double_to_int_802c4da0@l(r3)
	xoris r5, r6, 0x8000
	lwz r3, 0xa8(r29)
	stw r5, 0x5c(r1)
	subis r0, r6, 0x1
	lwz r29, 0xb0(r29)
	cmplwi r0, 0x86a0
	lfd f0, 0x58(r1)
	stw r4, 0x60(r1)
	fsubs f0, f0, f4
	stw r5, 0x74(r1)
	stfs f0, 0x48(r1)
	lwz r0, 0x4(r7)
	stw r4, 0x70(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x64(r1)
	lfd f0, 0x60(r1)
	stw r0, 0x7c(r1)
	fsubs f1, f0, f4
	lfd f0, 0x70(r1)
	stw r4, 0x78(r1)
	fsubs f2, f0, f4
	stfs f1, 0x4c(r1)
	lfd f0, 0x78(r1)
	lwz r0, 0x8(r7)
	fsubs f1, f0, f4
	stw r4, 0x68(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x6c(r1)
	lfd f3, 0x68(r1)
	stw r0, 0x84(r1)
	fsubs f3, f3, f4
	stw r4, 0x80(r1)
	lfd f0, 0x80(r1)
	stfs f3, 0x50(r1)
	fsubs f0, f0, f4
	stfs f2, 0x3c(r1)
	stfs f1, 0x40(r1)
	stfs f0, 0x44(r1)
	bne @1
	addi r4, r1, 0x48
	bl hitObjGetPos
	@1:
	lfs f4, float_0_8041a3f0(r2)
	fcmpu cr0, f4, f31
	beq @2
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x84(r1)
	lis r4, double_to_int_802c4da0@ha
	lfs f3, float_1E06_8041a414(r2)
	cmpwi r30, 0x1
	stw r0, 0x80(r1)
	lfd f1, double_to_int_802c4da0@l(r4)
	lfd f0, 0x80(r1)
	lfs f2, float_360_8041a3ec(r2)
	fsubs f1, f0, f1
	lfs f0, float_0p125_8041a418(r2)
	stfs f4, 0x8(r1)
	fmuls f1, f2, f1
	stfs f4, 0xc(r1)
	stfs f4, 0x10(r1)
	fmuls f2, f1, f0
	stfs f3, 0x14(r1)
	bne @3
	lfs f0, float_180_8041a41c(r2)
	fadds f2, f2, f0
	@3:
	lfs f1, float_6p2832_8041a3e8(r2)
	lfs f0, float_360_8041a3ec(r2)
	fmuls f1, f1, f2
	fdivs f30, f1, f0
	fmr f1, f30
	bl sin
	frsp f4, f1
	lfs f0, 0x4c(r1)
	lfs f3, float_30_8041a420(r2)
	fmr f1, f30
	lfs f2, 0x48(r1)
	stfs f0, 0x28(r1)
	fnmsubs f0, f3, f4, f2
	stfs f0, 0x24(r1)
	bl cos
	frsp f1, f1
	lfs f4, float_0_8041a3f0(r2)
	lfs f0, float_1E06_8041a414(r2)
	addi r4, r1, 0x8
	lfs f5, float_30_8041a420(r2)
	fmr f6, f4
	fneg f3, f1
	lfs f2, 0x50(r1)
	stfs f0, 0x14(r1)
	addi r5, r1, 0xc
	lfs f1, 0x24(r1)
	addi r6, r1, 0x10
	fnmsubs f3, f5, f3, f2
	lfs f2, 0x28(r1)
	lfs f5, float_neg1_8041a410(r2)
	addi r7, r1, 0x14
	addi r8, r1, 0x18
	addi r9, r1, 0x1c
	stfs f3, 0x2c(r1)
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @4
	lfs f0, 0xc(r1)
	stfs f0, 0x28(r1)
	@4:
	lwz r4, 0x24(r1)
	fmr f1, f30
	lwz r3, 0x28(r1)
	lwz r0, 0x2c(r1)
	stw r4, 0x30(r1)
	stw r3, 0x34(r1)
	stw r0, 0x38(r1)
	bl sin
	lfs f2, float_30_8041a420(r2)
	frsp f3, f1
	lfs f0, 0x30(r1)
	fmr f1, f30
	fadds f30, f2, f31
	fmadds f0, f30, f3, f0
	stfs f0, 0x30(r1)
	bl cos
	frsp f0, f1
	lwz r6, 0x24(r1)
	lwz r0, 0x28(r1)
	lwz r5, 0x2c(r1)
	fneg f1, f0
	lfs f0, 0x38(r1)
	lwz r4, 0x30(r1)
	lwz r3, 0x34(r1)
	fmadds f0, f30, f1, f0
	stw r6, 0x48(r1)
	stw r0, 0x4c(r1)
	stfs f0, 0x38(r1)
	lwz r0, 0x38(r1)
	stw r5, 0x50(r1)
	stw r4, 0x3c(r1)
	stw r3, 0x40(r1)
	stw r0, 0x44(r1)
	@2:
	lfs f1, 0x3c(r1)
	lfs f2, 0x40(r1)
	lfs f3, 0x44(r1)
	lfs f5, 0x48(r1)
	lfs f4, 0x4c(r1)
	lfs f0, 0x50(r1)
	stfs f5, BeroSX(r13)
	stfs f4, BeroSY(r13)
	stfs f0, BeroSZ(r13)
	stfs f1, BeroEX(r13)
	stfs f2, BeroEY(r13)
	stfs f3, BeroEZ(r13)
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x19
	bne @5
	bl N_marioReloadMapOnBottomlessOn
	@5:
	li r3, 0x2
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	psq_l f30, 0xa8(r1), 0, 0
	lfd f30, 0xa0(r1)
	lwz r31, 0x9c(r1)
	lwz r30, 0x98(r1)
	lwz r0, 0xc4(r1)
	lwz r29, 0x94(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm s32 evt_bero_get_info_num(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r27, 0x2c(r1)
	mr r29, r3
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lis r5, BeroINFOARR@ha
	lis r4, jumptable_802C4970@ha
	slwi r31, r3, 2
	addi r3, r5, BeroINFOARR@l
	addi r10, r4, jumptable_802C4970@l
	lwzx r30, r3, r31
	lwz r0, 0x0(r30)
	stw r0, 0xa8(r29)
	lhz r0, 0x4(r30)
	stw r0, 0xac(r29)
	lwz r27, 0x8(r30)
	lwz r9, 0x0(r10)
	lwz r8, 0x4(r10)
	cmpwi r27, 0x4e20
	lwz r7, 0x8(r10)
	lwz r6, 0xc(r10)
	lwz r5, 0x10(r10)
	lwz r4, 0x14(r10)
	lwz r3, 0x18(r10)
	lwz r0, 0x1c(r10)
	stw r9, 0x8(r1)
	stw r8, 0xc(r1)
	stw r7, 0x10(r1)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	beq @1
	b @2
	@1:
	cmpwi r27, 0x2710
	bne @3
	li r27, 0x2710
	b @2
	@3:
	lhz r0, 0x4(r30)
	clrlwi r0, r0, 20
	cmpwi r0, 0x2
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @4
	@5:
	li r27, 0x0
	addi r28, r1, 0x8
	@6:
	lwz r3, 0x0(r28)
	bl strlen
	mr r5, r3
	lwz r3, 0x0(r28)
	lwz r4, 0x0(r30)
	bl strncmp
	cmpwi r3, 0x0
	beq @2
	addi r27, r27, 0x1
	addi r28, r28, 0x4
	cmplwi r27, 0x8
	blt @6
	b @2
	@4:
	li r27, 0x2710
	@2:
	stw r27, 0xb0(r29)
	addi r0, r30, 0xc
	stw r0, 0xb4(r29)
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	bne @7
	la r0, default_entevt(r13)
	@7:
	stw r0, 0xb8(r29)
	lis r0, 0xffff
	lis r3, BeroSW@ha
	stw r0, 0xbc(r29)
	addi r3, r3, BeroSW@l
	lwzx r0, r3, r31
	stw r0, 0xc0(r29)
	lwz r0, 0x20(r30)
	stw r0, 0xc4(r29)
	lwz r0, 0x20(r30)
	cmpwi r0, -0x1
	bne @8
	lhz r0, 0x4(r30)
	clrlwi r0, r0, 20
	cmpwi r0, 0x3
	beq @9
	bge @10
	cmpwi r0, 0x1
	beq @11
	bge @12
	cmpwi r0, 0x0
	bge @13
	b @8
	@10:
	cmpwi r0, 0xf00
	beq @14
	b @8
	@14:
	li r0, 0x0
	stw r0, 0xc4(r29)
	b @8
	@13:
	li r0, 0xa
	stw r0, 0xc4(r29)
	b @8
	@11:
	li r0, 0x9
	stw r0, 0xc4(r29)
	b @8
	@12:
	li r0, 0x4
	stw r0, 0xc4(r29)
	b @8
	@9:
	li r0, 0x7
	stw r0, 0xc4(r29)
	@8:
	lwz r0, 0x24(r30)
	cmplwi r0, 0x0
	bne @15
	la r0, default_outevt(r13)
	@15:
	stw r0, 0xc8(r29)
	lis r0, 0xffff
	li r3, 0x2
	stw r0, 0xcc(r29)
	lwz r0, 0x28(r30)
	stw r0, 0xd0(r29)
	lwz r0, 0x2c(r30)
	stw r0, 0xd4(r29)
	lmw r27, 0x2c(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 evt_bero_id_filter(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r29, 0x18(r3)
	lwz r4, 0x0(r29)
	bl evtGetValue
	cmpwi r3, 0x0
	lis r4, BeroINFOARR@ha
	stw r3, 0x8(r1)
	addi r30, r4, BeroINFOARR@l
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r31, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	lwz r3, 0x0(r30)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r30, r30, 0x4
	beq @3
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @3
	@2:
	lwz r4, 0x0(r29)
	mr r3, r28
	lwz r5, 0x8(r1)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_read_mario_pera(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	beq @1
	li r0, 0x0
	stw r0, 0x78(r31)
	@1:
	lwz r0, 0x78(r31)
	cmpwi r0, 0x1
	beq @2
	bge @3
	cmpwi r0, 0x0
	bge @4
	b @3
	b @3
	@4:
	lis r3, str_802C4DA8@ha
	li r4, 0x0
	addi r3, r3, str_802C4DA8@l
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @3
	li r0, 0x1
	stw r0, 0x78(r31)
	b @3
	@2:
	lis r3, str_802C4DB4@ha
	li r4, 0x0
	addi r3, r3, str_802C4DB4@l
	li r5, 0x0
	bl animGroupBaseAsync
	cmpwi r3, 0x0
	beq @3
	li r0, 0x64
	stw r0, 0x78(r31)
	@3:
	lwz r3, 0x78(r31)
	li r0, 0x2
	subi r4, r3, 0x64
	subfic r3, r3, 0x64
	nor r3, r4, r3
	srawi r3, r3, 31
	and r3, r0, r3
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_get_into_info(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x64(r1)
	stw r31, 0x5c(r1)
	addi r31, r4, BeroINFOARR@l
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	mr r29, r3
	stw r28, 0x50(r1)
	li r28, 0x0
	@1:
	lwz r30, 0x0(r31)
	cmplwi r30, 0x0
	beq @2
	lwz r3, gp(r13)
	la r4, float_0_8041a424(r2)
	addi r3, r3, 0x11c
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	@2:
	lis r3, bero_null@ha
	li r28, 0x0
	addi r0, r3, bero_null@l
	mr r30, r0
	b @4
	@3:
	lwz r4, gp(r13)
	lwz r3, 0x0(r30)
	addi r4, r4, 0x11c
	bl strcmp
	cmpwi r3, 0x0
	beq @4
	addi r31, r31, 0x4
	addi r28, r28, 0x1
	b @1
	@4:
	lwz r3, gp(r13)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @5
	addi r3, r3, 0x11c
	la r4, float_0_8041a424(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	lis r4, BeroINFOARR@ha
	lis r3, jumptable_802C4970@ha
	lwz r30, BeroINFOARR@l(r4)
	li r31, 0x0
	addi r10, r3, jumptable_802C4970@l
	stw r31, 0xa0(r29)
	lwz r0, BeroNUM(r13)
	stw r0, 0xa4(r29)
	lwz r0, 0x0(r30)
	stw r0, 0xa8(r29)
	lhz r0, 0x4(r30)
	stw r0, 0xac(r29)
	lwz r11, 0x8(r30)
	lwz r9, 0x0(r10)
	lwz r8, 0x4(r10)
	cmpwi r11, 0x4e20
	lwz r7, 0x8(r10)
	lwz r6, 0xc(r10)
	lwz r5, 0x10(r10)
	lwz r4, 0x14(r10)
	lwz r3, 0x18(r10)
	lwz r0, 0x1c(r10)
	stw r9, 0x28(r1)
	stw r8, 0x2c(r1)
	stw r7, 0x30(r1)
	stw r6, 0x34(r1)
	stw r5, 0x38(r1)
	stw r4, 0x3c(r1)
	stw r3, 0x40(r1)
	stw r0, 0x44(r1)
	beq @6
	b @7
	@6:
	cmpwi r11, 0x2710
	bne @8
	li r11, 0x2710
	b @7
	@8:
	lhz r0, 0x4(r30)
	clrlwi r0, r0, 20
	cmpwi r0, 0x2
	bge @9
	cmpwi r0, 0x0
	bge @10
	b @9
	@10:
	addi r28, r1, 0x28
	@11:
	lwz r3, 0x0(r28)
	bl strlen
	mr r5, r3
	lwz r3, 0x0(r28)
	lwz r4, 0x0(r30)
	bl strncmp
	cmpwi r3, 0x0
	beq @12
	addi r31, r31, 0x1
	addi r28, r28, 0x4
	cmplwi r31, 0x8
	blt @11
	b @12
	@9:
	li r31, 0x2710
	@12:
	mr r11, r31
	@7:
	stw r11, 0xb0(r29)
	addi r0, r30, 0xc
	stw r0, 0xb4(r29)
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	bne @13
	la r0, default_entevt(r13)
	@13:
	stw r0, 0xb8(r29)
	lis r0, 0xffff
	li r3, 0x2
	stw r0, 0xbc(r29)
	b @14
	@5:
	stw r28, 0xa0(r29)
	lis r3, jumptable_802C4970@ha
	addi r10, r3, jumptable_802C4970@l
	lwz r0, BeroNUM(r13)
	stw r0, 0xa4(r29)
	lwz r3, gp(r13)
	addi r0, r3, 0x11c
	stw r0, 0xa8(r29)
	lhz r0, 0x4(r30)
	stw r0, 0xac(r29)
	lwz r31, 0x8(r30)
	lwz r9, 0x0(r10)
	lwz r8, 0x4(r10)
	cmpwi r31, 0x4e20
	lwz r7, 0x8(r10)
	lwz r6, 0xc(r10)
	lwz r5, 0x10(r10)
	lwz r4, 0x14(r10)
	lwz r3, 0x18(r10)
	lwz r0, 0x1c(r10)
	stw r9, 0x8(r1)
	stw r8, 0xc(r1)
	stw r7, 0x10(r1)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r3, 0x20(r1)
	stw r0, 0x24(r1)
	beq @15
	b @16
	@15:
	cmpwi r31, 0x2710
	bne @17
	li r31, 0x2710
	b @16
	@17:
	lhz r0, 0x4(r30)
	clrlwi r0, r0, 20
	cmpwi r0, 0x2
	bge @18
	cmpwi r0, 0x0
	bge @19
	b @18
	@19:
	li r31, 0x0
	addi r28, r1, 0x8
	@20:
	lwz r3, 0x0(r28)
	bl strlen
	mr r5, r3
	lwz r3, 0x0(r28)
	lwz r4, 0x0(r30)
	bl strncmp
	cmpwi r3, 0x0
	beq @16
	addi r31, r31, 0x1
	addi r28, r28, 0x4
	cmplwi r31, 0x8
	blt @20
	b @16
	@18:
	li r31, 0x2710
	@16:
	stw r31, 0xb0(r29)
	addi r0, r30, 0xc
	stw r0, 0xb4(r29)
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	bne @21
	la r0, default_entevt(r13)
	@21:
	stw r0, 0xb8(r29)
	lis r0, 0xffff
	li r3, 0x2
	stw r0, 0xbc(r29)
	@14:
	lwz r0, 0x64(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	stw r0, 0x24(r1)
	li r0, 0x0
	stw r31, 0x1c(r1)
	addi r31, r4, BeroINFOARR@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	stw r0, 0x0(r31)
	stw r0, 0x4(r31)
	stw r0, 0x8(r31)
	stw r0, 0xc(r31)
	stw r0, 0x10(r31)
	stw r0, 0x14(r31)
	stw r0, 0x18(r31)
	stw r0, 0x1c(r31)
	stw r0, 0x20(r31)
	stw r0, 0x24(r31)
	stw r0, 0x28(r31)
	stw r0, 0x2c(r31)
	stw r0, 0x30(r31)
	stw r0, 0x34(r31)
	stw r0, 0x38(r31)
	stw r0, 0x3c(r31)
	lwz r30, 0x9c(r29)
	@1:
	lwz r3, 0x0(r30)
	bl hitNameToPtr
	lwz r4, 0x0(r30)
	cmplwi r4, 0x0
	beq @2
	cmplwi r3, 0x0
	bne @3
	li r3, 0x1
	bl mapErrorEntry
	@3:
	addi r30, r30, 0x3c
	b @1
	@2:
	lis r3, BeroSW@ha
	lwz r6, 0x9c(r29)
	addi r4, r3, BeroSW@l
	li r5, 0x0
	li r0, -0x1
	@4:
	lwz r3, 0x0(r6)
	cmplwi r3, 0x0
	beq @5
	stw r6, 0x0(r31)
	addi r31, r31, 0x4
	addi r5, r5, 0x1
	addi r6, r6, 0x3c
	stw r0, 0x0(r4)
	addi r4, r4, 0x4
	b @4
	@5:
	li r0, 0x0
	stw r5, BeroNUM(r13)
	li r3, 0x2
	stw r0, BeroEXEC(r13)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_get_now_number(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r5, BeroNOWNUM(r13)
	lwz r4, 0x0(r4)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_set_now_number(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	stw r3, BeroNOWNUM(r13)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_get_info_nextarea(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lis r4, BeroINFOARR@ha
	slwi r0, r3, 2
	addi r3, r4, BeroINFOARR@l
	lwz r4, 0x4(r30)
	lwzx r31, r3, r0
	mr r3, r29
	lwz r5, 0x28(r31)
	bl evtSetValue
	lwz r4, 0x8(r30)
	mr r3, r29
	lwz r5, 0x2c(r31)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_get_info_kinddir(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lis r4, BeroINFOARR@ha
	slwi r0, r3, 2
	addi r3, r4, BeroINFOARR@l
	lwz r4, 0x4(r30)
	lwzx r31, r3, r0
	mr r3, r29
	lhz r5, 0x4(r31)
	bl evtSetValue
	lwz r4, 0x8(r30)
	mr r3, r29
	lhz r5, 0x6(r31)
	bl evtSetValue
	lwz r4, 0xc(r30)
	mr r3, r29
	lwz r5, 0x8(r31)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_get_info_length(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lis r4, BeroINFOARR@ha
	slwi r0, r3, 2
	addi r3, r4, BeroINFOARR@l
	lwzx r3, r3, r0
	lwz r0, 0x18(r3)
	cmpwi r0, -0x1
	beq @1
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802c4da0@ha
	stw r3, 0xc(r1)
	addi r5, r4, double_to_int_802c4da0@l
	lwz r4, 0x4(r31)
	stw r0, 0x8(r1)
	mr r3, r30
	lfd f1, 0x0(r5)
	lfd f0, 0x8(r1)
	fsubs f1, f0, f1
	bl evtSetFloat
	li r3, 0x2
	b @2
	@1:
	lhz r0, 0x4(r3)
	clrlwi r0, r0, 20
	cmpwi r0, 0x3
	beq @3
	bge @4
	cmpwi r0, 0x1
	beq @5
	bge @6
	cmpwi r0, 0x0
	bge @3
	b @7
	@4:
	cmpwi r0, 0xf00
	beq @3
	b @7
	@3:
	lfs f1, float_30_8041a420(r2)
	b @8
	@5:
	lfs f1, float_60_8041a428(r2)
	b @8
	@6:
	lfs f1, float_60_8041a428(r2)
	b @8
	@7:
	lfs f1, float_60_8041a428(r2)
	@8:
	lwz r4, 0x4(r31)
	mr r3, r30
	bl evtSetFloat
	li r3, 0x2
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_get_info_anime(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lis r4, BeroINFOARR@ha
	slwi r0, r3, 2
	addi r3, r4, BeroINFOARR@l
	lwz r4, 0x4(r30)
	lwzx r31, r3, r0
	mr r3, r29
	lhz r5, 0x30(r31)
	bl evtSetValue
	lwz r4, 0x8(r30)
	mr r3, r29
	lhz r5, 0x32(r31)
	bl evtSetValue
	lwz r4, 0xc(r30)
	mr r3, r29
	lwz r5, 0x34(r31)
	bl evtSetValue
	lwz r4, 0x10(r30)
	mr r3, r29
	lwz r5, 0x38(r31)
	bl evtSetValue
	lwz r0, 0x24(r1)
	li r3, 0x2
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 evt_bero_get_end_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lfs f1, BeroEX(r13)
	lwz r4, 0x0(r31)
	bl evtSetFloat
	lwz r4, 0x4(r31)
	mr r3, r30
	lfs f1, BeroEY(r13)
	bl evtSetFloat
	lwz r4, 0x8(r31)
	mr r3, r30
	lfs f1, BeroEZ(r13)
	bl evtSetFloat
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_get_start_position(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lfs f1, BeroSX(r13)
	lwz r4, 0x0(r31)
	bl evtSetFloat
	lwz r4, 0x4(r31)
	mr r3, r30
	lfs f1, BeroSY(r13)
	bl evtSetFloat
	lwz r4, 0x8(r31)
	mr r3, r30
	lfs f1, BeroSZ(r13)
	bl evtSetFloat
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lwz r4, BeroEXEC(r13)
	li r0, 0x2
	and r4, r4, r3
	neg r3, r4
	or r3, r3, r4
	srawi r3, r3, 31
	and r3, r0, r3
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_exec_get(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r5, BeroEXEC(r13)
	lwz r4, 0x0(r4)
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_exec_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lwz r0, BeroEXEC(r13)
	cmpwi r31, 0x0
	or r4, r0, r3
	beq @1
	andc r4, r0, r3
	@1:
	stw r4, BeroEXEC(r13)
	li r3, 0x2
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r5, gp(r13)
	lwz r4, 0x0(r4)
	addi r5, r5, 0x11c
	bl evtSetValue
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r4
	stw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	cmpwi r30, 0x0
	beq @1
	mr r4, r31
	mr r5, r3
	li r3, 0x3
	bl seqSetSeq
	@1:
	lwz r0, 0x24(r1)
	li r3, 0x0
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 bero_id_filter(s32 id) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, BeroINFOARR@ha
	cmpwi r3, 0x0
	stw r0, 0x24(r1)
	addi r0, r4, BeroINFOARR@l
	mr r4, r0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r3, 0x8(r1)
	blt @1
	cmpwi r3, 0x10
	blt @2
	@1:
	addic. r0, r1, 0x8
	mr r30, r3
	beq @3
	li r0, 0x0
	stw r0, 0x8(r1)
	@3:
	mr r31, r4
	@4:
	lwz r3, 0x0(r31)
	lwz r3, 0x0(r3)
	cmplwi r3, 0x0
	beq @2
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	addic. r0, r1, 0x8
	addi r31, r31, 0x4
	beq @4
	lwz r3, 0x8(r1)
	addi r0, r3, 0x1
	stw r0, 0x8(r1)
	b @4
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r3, 0x8(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void bero_clear_Offset(void) {
	nofralloc
	lfs f0, float_0_8041a3f0(r2)
	stfs f0, BeroOX(r13)
	stfs f0, BeroOY(r13)
	stfs f0, BeroOZ(r13)
	blr
}

asm BeroEntry** bero_get_ptr(void) {
	nofralloc
	lis r3, BeroINFOARR@ha
	addi r3, r3, BeroINFOARR@l
	blr
}

asm f32 bero_get_BeroEZ(void) {
	nofralloc
	lfs f1, BeroEZ(r13)
	blr
}

asm f32 bero_get_BeroEY(void) {
	nofralloc
	lfs f1, BeroEY(r13)
	blr
}

asm f32 bero_get_BeroEX(void) {
	nofralloc
	lfs f1, BeroEX(r13)
	blr
}

asm f32 bero_get_BeroSZ(void) {
	nofralloc
	lfs f1, BeroSZ(r13)
	blr
}

asm f32 bero_get_BeroSY(void) {
	nofralloc
	lfs f1, BeroSY(r13)
	blr
}

asm f32 bero_get_BeroSX(void) {
	nofralloc
	lfs f1, BeroSX(r13)
	blr
}

asm s32 bero_get_BeroNUM(void) {
	nofralloc
	lwz r3, BeroNUM(r13)
	blr
}

asm s32 bero_get_BeroEXEC(void) {
	nofralloc
	lwz r3, BeroEXEC(r13)
	blr
}

asm s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPtr
	lfs f1, 0x8c(r3)
	lfs f2, 0x90(r3)
	lfs f3, 0x94(r3)
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	lwz r4, 0x8(r31)
	mr r31, r3
	mr r3, r29
	bl evtGetValue
	lis r5, 0x4330
	xoris r6, r30, 0x8000
	stw r6, 0xc(r1)
	xoris r0, r3, 0x8000
	xoris r4, r31, 0x8000
	lis r3, double_to_int_802c4da0@ha
	stw r5, 0x8(r1)
	lfd f3, double_to_int_802c4da0@l(r3)
	lfd f0, 0x8(r1)
	stw r4, 0x14(r1)
	fsubs f1, f0, f3
	stw r5, 0x10(r1)
	lfd f0, 0x10(r1)
	stw r0, 0x1c(r1)
	fsubs f2, f0, f3
	stw r5, 0x18(r1)
	lfd f0, 0x18(r1)
	fsubs f3, f0, f3
	bl N_marioSetBottomlessRespawnPosOnBeroEntry
	lwz r0, 0x34(r1)
	li r3, 0x2
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}
// clang-format on
#endif

// FAKE: .bss defined at file end so the asm-only unit keeps target order
BeroEntry* BeroINFOARR[16];
s32 BeroSW[16];
s32 BeroID[16];
