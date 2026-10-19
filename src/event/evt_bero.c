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
#ifdef NONMATCHING
extern const char str_8041A3C8[4];
extern const char str_8041A3CC[4];
extern const char str_8041A3D0[4];
extern const char str_8041A3D4[4];
extern const char str_8041A3D8[4];
extern const char str_8041A3DC[4];
extern const char str_8041A3E0[4];
extern const char str_8041A3E4[4];
#endif
#ifndef NONMATCHING
__declspec(section ".sdata2") extern const f32 float_6p2832_8041a3e8;
__declspec(section ".sdata2") extern const f32 float_360_8041a3ec;
__declspec(section ".sdata2") extern const f32 float_0_8041a3f0;
__declspec(section ".sdata2") extern const f32 float_3_8041a3f4;
__declspec(section ".sdata2") extern const f32 float_15_8041a3f8;
__declspec(section ".sdata2") extern const f32 float_13_8041a3fc;
__declspec(section ".sdata2") extern const f32 float_20_8041a400;
__declspec(section ".sdata2") extern const f32 float_1_8041a404;
__declspec(section ".sdata2") extern const f32 float_37p5_8041a408;
__declspec(section ".sdata2") extern const f32 float_10000_8041a40c;
__declspec(section ".sdata2") extern const f32 float_neg1_8041a410;
__declspec(section ".sdata2") extern const f32 float_1E06_8041a414;
__declspec(section ".sdata2") extern const f32 float_0p125_8041a418;
__declspec(section ".sdata2") extern const f32 float_180_8041a41c;
__declspec(section ".sdata2") extern const f32 float_30_8041a420;
__declspec(section ".sdata2") extern const f32 float_0_8041a424;
__declspec(section ".sdata2") extern const f32 float_60_8041a428;
__declspec(section ".sdata2") extern const u32 gap_09_8041A42C_sdata2;
#define EXT_LIT(sym, val) (sym)

extern const char str_8041A3C8[];
extern const char str_8041A3CC[];
extern const char str_8041A3D0[];
extern const char str_8041A3D4[];
extern const char str_8041A3D8[];
extern const char str_8041A3DC[];
extern const char str_8041A3E0[];
extern const char str_8041A3E4[];
#endif
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

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 bero_get_position_normal(EventEntry* event, BOOL isFirstCall);
s32 bero_get_position_pipe2(EventEntry* event, BOOL isFirstCall);
s32 bero_get_position_pipe_pure(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_1stcheck(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_cam3d_change(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_cam_shift_init(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_case_id_load(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_case_id_save(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_disppos_load(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_disppos_save(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_get(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info_anime(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info_kinddir(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info_length(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info_num(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_into_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_number(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mario_go(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mario_go_init(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mario_go_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_move_mario_speed(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_read_mario_pera(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_set_now_number(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_switch_off(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_switch_on(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_road_reset(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_road_reset2(EventEntry* event, BOOL isFirstCall);
s32 evt_camera_change_event_from_road(EventEntry* event, BOOL isFirstCall);
s32 evt_del_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_end_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_set_mapchange_type(EventEntry* event, BOOL isFirstCall);
s32 evt_hit_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_attr_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_pauseanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_replayanim(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_bgmode_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_bgmode_on(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cam_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cam_on(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cam_y_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dokan_end(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dokan_prepare(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_motion(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_kill_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_paper_pose_dokan(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_paper_pose_off(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_party_bero_move(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dispdir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_force_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_prev_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_prev_party_dokan(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_wait_landon(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_fbat_mode(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_start_for_event(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_stop_for_event(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_homing_dist(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt_bero(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_system_flag(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value_para(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_overwrite(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_id_filter(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_now_number(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info_nextarea(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_end_position(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_start_position(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
#endif
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

#ifdef NONMATCHING
s32 default_entevt[] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 default_entevt[] = {
#endif
    131122, -30000000, 0, 2, 1,
};

#ifdef NONMATCHING
s32 default_outevt[] = {
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") s32 default_outevt[] = {
#endif
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
#endif
#ifndef NONMATCHING
typedef struct { Vec f_0; Vec pos; Vec at; } BeroCamRoadOut;
int __div2u();
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
BOOL animGroupBaseAsync(const char* name, s32 group, void* callback);
void mapErrorEntry(s32 arg0, const char* arg1);
f32 reviseAngle(f32 angle);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
f32 sysFrame2SecFloat(f32 frame);
s32 sysMsec2Frame(s32 msec);
extern void N_marioReloadMapOnBottomlessOn(void);
extern void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end);
extern void camRoadMain(BeroCamRoadOut* out, f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g);
extern void camRoadReset(void);
extern void camShiftMain(CameraEntry* camera, MarioWork* mario, f32* out);
extern void camShiftReset(void);
extern double cos(double);
extern double sin(double);
s32 N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
	x = evtGetValue(event, args[0]);
	y = evtGetValue(event, args[1]);
	z = evtGetValue(event, args[2]);
	N_marioSetBottomlessRespawnPosOnBeroEntry((f32)x, (f32)y, (f32)z);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos) {
	MarioWork* wp = marioGetPtr();
	N_marioSetBottomlessRespawnPosOnBeroEntry(wp->position.x, wp->position.y, wp->position.z);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 bero_get_BeroEXEC(void);
#endif

#ifdef NONMATCHING
s32 bero_get_BeroEXEC(void) {
	return BeroEXEC;
}
#endif
#ifndef NONMATCHING
s32 bero_get_BeroNUM(void);
#endif

#ifdef NONMATCHING
s32 bero_get_BeroNUM(void) {
	return BeroNUM;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroSX(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSX(void) {
	return BeroSX;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroSY(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSY(void) {
	return BeroSY;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroSZ(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroSZ(void) {
	return BeroSZ;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroEX(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEX(void) {
	return BeroEX;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroEY(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEY(void) {
	return BeroEY;
}
#endif
#ifndef NONMATCHING
f32 bero_get_BeroEZ(void);
#endif

#ifdef NONMATCHING
f32 bero_get_BeroEZ(void) {
	return BeroEZ;
}
#endif
#ifndef NONMATCHING
BeroEntry** bero_get_ptr(void);
#endif

#ifdef NONMATCHING
BeroEntry** bero_get_ptr(void) {
	return BeroINFOARR;
}
#endif
#ifndef NONMATCHING
void bero_clear_Offset(void);
#endif

#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
s32 bero_id_filter(s32 id);
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
#ifndef NONMATCHING
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
#endif

//s32 retIndex
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_entername) {
	evtSetValue(event, *event->args, (s32)&gp->beroEnterName);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_exec_onoff(EventEntry* event, BOOL isFirstCall);
#endif

//s32 retIndex
#ifdef NONMATCHING
USER_FUNC(evt_bero_exec_get) {
	evtSetValue(event, *event->args, BeroEXEC);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_exec_get(EventEntry* event, BOOL isFirstCall);
#endif

//s32* mask, TODO: add states, change EvtStatus to s32 and do #defines
#ifdef NONMATCHING
USER_FUNC(evt_bero_exec_wait) {
	return evtGetValue(event, *event->args) & BeroEXEC ? EVT_RETURN_DONE : 0;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_get_start_position(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_get_end_position(EventEntry* event, BOOL isFirstCall);
#endif

//s32* id, s32 retIndex1, s32 retIndex2, s32 retIndex3, s32 retIndex4
#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_anime) {
	BeroEntry* bero;
	s32* args = event->args;
#endif
#ifndef NONMATCHING
s32 evt_bero_get_info_anime(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->enterAnimeType);
	evtSetValue(event, args[2], *(u16*)&bero->exitAnimeType);
	evtSetValue(event, args[3], bero->enterAnimeArg);
	evtSetValue(event, args[4], bero->exitAnimeArg);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_get_info_length(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_length) {
	BeroEntry* bero;
	s32* args = event->args;
	s32 v5;
	f32 storeme;
#endif
#ifndef NONMATCHING
s32 evt_bero_get_info_kinddir(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 evt_bero_get_info_nextarea(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_get_info_kinddir) {
	BeroEntry* bero;
	s32* args = event->args;
#endif
#ifndef NONMATCHING
s32 evt_bero_set_now_number(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->type);
	evtSetValue(event, args[2], *(u16*)&bero->sfxId);
	evtSetValue(event, args[3], bero->directionId);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_get_now_number(EventEntry* event, BOOL isFirstCall);
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

USER_FUNC(evt_bero_set_now_number) {
	BeroNOWNUM = evtGetValue(event, *event->args);
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_bero_get_now_number) {
	evtSetValue(event, *event->args, BeroNOWNUM);
	return EVT_RETURN_DONE;
}

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
#ifndef NONMATCHING
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_get_into_info(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_read_mario_pera(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_id_filter) {
	s32* args = event->args;
	evtSetValue(event, args[0], bero_id_filter(evtGetValue(event, args[0])));
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_id_filter(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_get_info_num(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 bero_get_position_normal(EventEntry *event, BOOL isFirstCall);
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
#ifndef NONMATCHING
void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end);
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
#ifndef NONMATCHING
s32 bero_get_position_pipe_pure(EventEntry* event, BOOL isFirstCall);
#endif


#ifdef NONMATCHING
typedef struct { Vec f_0; Vec pos; Vec at; } BeroCamRoadOut;
#endif
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
#ifndef NONMATCHING
s32 bero_get_position_pipe2(EventEntry* event, BOOL isFirstCall);
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
#ifdef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
#endif
#ifndef NONMATCHING
            SET_FLOAT_VALUE(LW(0), FLOAT((180.0f)))
#endif
            CALL_CHILD(LW(12))
            CALL(evt_bero_mario_go)
            WAIT_MS(500)
            SPAWN_EVENT(PTR(bero_close_door_play_se))
            SET_VALUE(LW(9), LW(12))
            CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
            LOOP(0)
                CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(10))
                IF_INT_EQUAL(LW(10), 0)
#ifdef NONMATCHING
                    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
#endif
#ifndef NONMATCHING
                    SET_FLOAT_VALUE(LW(0), FLOAT((0.0f)))
#endif
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
#ifdef NONMATCHING
                    SET_FLOAT_VALUE(LW(0), FLOAT(180.0f))
#endif
#ifndef NONMATCHING
                    SET_FLOAT_VALUE(LW(0), FLOAT((180.0f)))
#endif
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
#ifndef NONMATCHING
s32 bero_set_disp_position_pipe(BeroPipeInfo* info);
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
#ifndef NONMATCHING
s32 evt_bero_switch_on(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_switch_off(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_get_number(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_case_id_save) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroID[id] = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_case_id_save(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_case_id_load) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], BeroID[id]);
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_case_id_load(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_disppos_save) {
	BeroOX = marioGetPtr()->dispOfs.x;
	BeroOY = marioGetPtr()->dispOfs.y;
	BeroOZ = marioGetPtr()->dispOfs.z;
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_disppos_save(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_disppos_load) {
	marioGetPtr()->dispOfs.x = BeroOX;
	marioGetPtr()->dispOfs.y = BeroOY;
	marioGetPtr()->dispOfs.z = BeroOZ;
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_disppos_load(EventEntry* event, BOOL isFirstCall);
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
#endif
#ifndef NONMATCHING
s32 evt_bero_move_mario_speed(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
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
#ifndef NONMATCHING
s32 evt_bero_overwrite(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_cam3d_change(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_bero_cam_shift_init(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_cam_shift_init) {
	camRoadReset();
	camShiftReset();
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_mario_go_init(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go_init) {
	BeroMarioGO = FALSE;
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_mario_go(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go) {
	BeroMarioGO = TRUE;
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 evt_bero_mario_go_wait(EventEntry* event, BOOL isFirstCall);
#endif

#ifdef NONMATCHING
USER_FUNC(evt_bero_mario_go_wait) {
	return BeroMarioGO == 0 ? 0 : EVT_RETURN_DONE;
}

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
#ifndef NONMATCHING
s32 evt_bero_1stcheck(EventEntry* event, BOOL isFirstCall);
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
#ifndef NONMATCHING
s32 evt_camera_change_event_from_road(EventEntry* event, BOOL isFirstCall);
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
#ifdef NONMATCHING
        CALL(bero_get_position_normal, 0, FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        CALL(bero_get_position_normal, 0, FLOAT((0.0f)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(2)
        CALL(evt_mario_paper_pose_dokan, 5)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 2)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 3)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(2)
        CALL(evt_mario_paper_pose_dokan, 5)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 2)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 3)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_party_set_homing_dist, 0, FLOAT((20.0f)))
    CALL(evt_party_set_homing_dist, 1, FLOAT((20.0f)))
#endif
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
#ifdef NONMATCHING
    CALL(evt_party_set_homing_dist, 0, FLOAT(20.0f))
    CALL(evt_party_set_homing_dist, 1, FLOAT(20.0f))
#endif
#ifndef NONMATCHING
    CALL(evt_party_set_homing_dist, 0, FLOAT((20.0f)))
    CALL(evt_party_set_homing_dist, 1, FLOAT((20.0f)))
#endif
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
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(2)
        CALL(evt_mario_set_dispdir, 0)
        CALL(evt_mario_paper_pose_dokan, 4)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(9)
        CALL(evt_mario_paper_pose_dokan, 1)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
        CASE_EQUAL(8)
        CALL(evt_mario_paper_pose_dokan, 0)
#ifdef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT(60.0f))
#endif
#ifndef NONMATCHING
        CALL(evt_bero_move_mario_speed, FLOAT((60.0f)))
#endif
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
#ifdef NONMATCHING
        CALL(bero_get_position_normal, 0, FLOAT(0.0f))
#endif
#ifndef NONMATCHING
        CALL(bero_get_position_normal, 0, FLOAT((0.0f)))
#endif
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


// FAKE: .bss defined at file end so the asm-only unit keeps target order

#ifndef NONMATCHING
static inline s32 bero_id_filter__af_inl(s32 id) { //1:1, cursed function, do not touch
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
s32 evt_bero_get_into_info(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[64];
	asm {
		lis r4, BeroINFOARR@ha
		addi r31, r4, BeroINFOARR@l
		mr r29, r3
	}
	asm volatile {
		li r28, 0x0
		opword 0x83DF0000
		opword 0x281E0000
		opword 0x4182001C
		lwz r3, gp(r13)
		la r4, float_0_8041a424(r2)
		opword 0x3863011C
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		lis r3, bero_null@ha
		opword 0x3B800000
		addi r0, r3, bero_null@l
		opword 0x7C1E0378
		opword 0x48000028
		lwz r4, gp(r13)
		opword 0x807E0000
		opword 0x3884011C
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x3BFF0004
		opword 0x3B9C0001
		opword 0x4BFFFFA8
		lwz r3, gp(r13)
		opword 0x80030000
		opword 0x540007BD
		opword 0x41820134
		opword 0x3863011C
		la r4, float_0_8041a424(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820120
		lis r4, BeroINFOARR@ha
		lis r3, jumptable_802C4970@ha
		lwz r30, BeroINFOARR@l(r4)
		opword 0x3BE00000
		addi r10, r3, jumptable_802C4970@l
		opword 0x93FD00A0
		lwz r0, BeroNUM(r13)
		opword 0x901D00A4
		opword 0x801E0000
		opword 0x901D00A8
		opword 0xA01E0004
		opword 0x901D00AC
		opword 0x817E0008
		opword 0x812A0000
		opword 0x810A0004
		opword 0x2C0B4E20
		opword 0x80EA0008
		opword 0x80CA000C
		opword 0x80AA0010
		opword 0x808A0014
		opword 0x806A0018
		opword 0x800A001C
		stw r9, _af_pad+32(r1)
		opword 0x9101002C
		opword 0x90E10030
		opword 0x90C10034
		opword 0x90A10038
		opword 0x9081003C
		opword 0x90610040
		opword 0x90010044
		opword 0x41820008
		opword 0x48000070
		opword 0x2C0B2710
		opword 0x4082000C
		opword 0x39602710
		opword 0x48000060
		opword 0xA01E0004
		opword 0x5400053E
		opword 0x2C000002
		opword 0x40800048
		opword 0x2C000000
		opword 0x40800008
		opword 0x4800003C
		opword 0x3B810028
		opword 0x807C0000
		bl strlen
		opword 0x7C651B78
		opword 0x807C0000
		opword 0x809E0000
		bl strncmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3BFF0001
		opword 0x3B9C0004
		opword 0x281F0008
		opword 0x4180FFD4
		opword 0x48000008
		opword 0x3BE02710
		opword 0x7FEBFB78
		opword 0x917D00B0
		opword 0x381E000C
		opword 0x901D00B4
		opword 0x801E001C
		opword 0x28000000
		opword 0x40820008
		la r0, default_entevt(r13)
		opword 0x901D00B8
		opword 0x3C00FFFF
		opword 0x38600002
		opword 0x901D00BC
		opword 0x48000114
		opword 0x939D00A0
		lis r3, jumptable_802C4970@ha
		addi r10, r3, jumptable_802C4970@l
		lwz r0, BeroNUM(r13)
		opword 0x901D00A4
		lwz r3, gp(r13)
		opword 0x3803011C
		opword 0x901D00A8
		opword 0xA01E0004
		opword 0x901D00AC
		opword 0x83FE0008
		opword 0x812A0000
		opword 0x810A0004
		opword 0x2C1F4E20
		opword 0x80EA0008
		opword 0x80CA000C
		opword 0x80AA0010
		opword 0x808A0014
		opword 0x806A0018
		opword 0x800A001C
		opword 0x91210008
		opword 0x9101000C
		opword 0x90E10010
		opword 0x90C10014
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90610020
		opword 0x90010024
		opword 0x41820008
		opword 0x48000070
		opword 0x2C1F2710
		opword 0x4082000C
		opword 0x3BE02710
		opword 0x48000060
		opword 0xA01E0004
		opword 0x5400053E
		opword 0x2C000002
		opword 0x4080004C
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000040
		opword 0x3BE00000
		opword 0x3B810008
		opword 0x807C0000
		bl strlen
		opword 0x7C651B78
		opword 0x807C0000
		opword 0x809E0000
		bl strncmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3BFF0001
		opword 0x3B9C0004
		opword 0x281F0008
		opword 0x4180FFD4
		opword 0x48000008
		opword 0x3BE02710
		opword 0x93FD00B0
		opword 0x381E000C
		opword 0x901D00B4
		opword 0x801E001C
		opword 0x28000000
		opword 0x40820008
		la r0, default_entevt(r13)
		opword 0x901D00B8
		opword 0x3C00FFFF
		opword 0x38600002
		opword 0x901D00BC
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_bero_read_mario_pera(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x2C040000
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C7F1B78
		opword 0x4182000C
		opword 0x38000000
		opword 0x901F0078
		opword 0x801F0078
		opword 0x2C000001
		opword 0x41820040
		opword 0x40800060
		opword 0x2C000000
		opword 0x4080000C
		opword 0x48000054
		opword 0x48000050
		lis r3, str_802C4DA8@ha
		opword 0x38800000
		addi r3, r3, str_802C4DA8@l
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x41820034
		opword 0x38000001
		opword 0x901F0078
		opword 0x48000028
		lis r3, str_802C4DB4@ha
		opword 0x38800000
		addi r3, r3, str_802C4DB4@l
		opword 0x38A00000
		bl animGroupBaseAsync
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000064
		opword 0x901F0078
		opword 0x807F0078
		opword 0x38000002
		opword 0x3883FF9C
		opword 0x20630064
		opword 0x7C8318F8
		opword 0x7C63FE70
		opword 0x7C031838
		opword 0x83E1000C
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

#define bero_id_filter bero_id_filter__af_inl
s32 evt_bero_id_filter(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	evtSetValue(event, args[0], bero_id_filter(evtGetValue(event, args[0])));
	return EVT_RETURN_DONE;
}

#undef bero_id_filter

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_bero_get_info_num(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xBF61002C
		opword 0x7C7D1B78
		opword 0x80830018
		opword 0x80840000
		bl evtGetValue
		lis r5, BeroINFOARR@ha
		lis r4, jumptable_802C4970@ha
		opword 0x547F103A
		addi r3, r5, BeroINFOARR@l
		addi r10, r4, jumptable_802C4970@l
		opword 0x7FC3F82E
		opword 0x801E0000
		opword 0x901D00A8
		opword 0xA01E0004
		opword 0x901D00AC
		opword 0x837E0008
		opword 0x812A0000
		opword 0x810A0004
		opword 0x2C1B4E20
		opword 0x80EA0008
		opword 0x80CA000C
		opword 0x80AA0010
		opword 0x808A0014
		opword 0x806A0018
		opword 0x800A001C
		opword 0x91210008
		opword 0x9101000C
		opword 0x90E10010
		opword 0x90C10014
		opword 0x90A10018
		opword 0x9081001C
		opword 0x90610020
		opword 0x90010024
		opword 0x41820008
		opword 0x48000070
		opword 0x2C1B2710
		opword 0x4082000C
		opword 0x3B602710
		opword 0x48000060
		opword 0xA01E0004
		opword 0x5400053E
		opword 0x2C000002
		opword 0x4080004C
		opword 0x2C000000
		opword 0x40800008
		opword 0x48000040
		opword 0x3B600000
		opword 0x3B810008
		opword 0x807C0000
		bl strlen
		opword 0x7C651B78
		opword 0x807C0000
		opword 0x809E0000
		bl strncmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x3B7B0001
		opword 0x3B9C0004
		opword 0x281B0008
		opword 0x4180FFD4
		opword 0x48000008
		opword 0x3B602710
		opword 0x937D00B0
		opword 0x381E000C
		opword 0x901D00B4
		opword 0x801E001C
		opword 0x28000000
		opword 0x40820008
		la r0, default_entevt(r13)
		opword 0x901D00B8
		opword 0x3C00FFFF
		lis r3, BeroSW@ha
		opword 0x901D00BC
		addi r3, r3, BeroSW@l
		opword 0x7C03F82E
		opword 0x901D00C0
		opword 0x801E0020
		opword 0x901D00C4
		opword 0x801E0020
		opword 0x2C00FFFF
		opword 0x40820074
		opword 0xA01E0004
		opword 0x5400053E
		opword 0x2C000003
		opword 0x4182005C
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820038
		opword 0x40800040
		opword 0x2C000000
		opword 0x40800020
		opword 0x48000048
		opword 0x2C000F00
		opword 0x41820008
		opword 0x4800003C
		opword 0x38000000
		opword 0x901D00C4
		opword 0x48000030
		opword 0x3800000A
		opword 0x901D00C4
		opword 0x48000024
		opword 0x38000009
		opword 0x901D00C4
		opword 0x48000018
		opword 0x38000004
		opword 0x901D00C4
		opword 0x4800000C
		opword 0x38000007
		opword 0x901D00C4
		opword 0x801E0024
		opword 0x28000000
		opword 0x40820008
		la r0, default_outevt(r13)
		opword 0x901D00C8
		opword 0x3C00FFFF
		opword 0x38600002
		opword 0x901D00CC
		opword 0x801E0028
		opword 0x901D00D0
		opword 0x801E002C
		opword 0x901D00D4
		opword 0xBB61002C
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 bero_get_position_normal(EventEntry *event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF40
		opword 0x7C0802A6
		opword 0x900100C4
		opword 0xDBE100B0
		opword 0xF3E100B8
		opword 0xDBC100A0
		opword 0xF3C100A8
		opword 0x93E1009C
		opword 0x93C10098
		opword 0x93A10094
		opword 0x7C7D1B78
		opword 0x83C30018
		bl marioGetPtr
		opword 0x809E0000
		opword 0x7C7F1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x809E0004
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetFloat
		opword 0x80FD00B4
		opword 0x3C804330
		lis r3, double_to_int_802c4da0@ha
		opword 0x90810058
		opword 0x80C70000
		opword 0xFFE00890
		lfd f4, double_to_int_802c4da0@l(r3)
		opword 0x6CC58000
		opword 0x807D00A8
		opword 0x90A1005C
		opword 0x3C06FFFF
		opword 0x83BD00B0
		opword 0x280086A0
		opword 0xC8010058
		opword 0x90810060
		opword 0xEC002028
		opword 0x90A10074
		opword 0xD0010048
		opword 0x80070004
		opword 0x90810070
		opword 0x6C008000
		opword 0x90010064
		opword 0xC8010060
		opword 0x9001007C
		opword 0xEC202028
		opword 0xC8010070
		opword 0x90810078
		opword 0xEC402028
		opword 0xD021004C
		opword 0xC8010078
		opword 0x80070008
		opword 0xEC202028
		opword 0x90810068
		opword 0x6C008000
		opword 0x9001006C
		opword 0xC8610068
		opword 0x90010084
		opword 0xEC632028
		opword 0x90810080
		opword 0xC8010080
		opword 0xD0610050
		opword 0xEC002028
		opword 0xD041003C
		opword 0xD0210040
		opword 0xD0010044
		opword 0x4082000C
		opword 0x38810048
		bl hitObjGetPos
		lfs f4, float_0_8041a3f0(r2)
		opword 0xFC04F800
		opword 0x41820180
		opword 0x6FA38000
		opword 0x3C004330
		opword 0x90610084
		lis r4, double_to_int_802c4da0@ha
		lfs f3, float_1E06_8041a414(r2)
		opword 0x2C1E0001
		opword 0x90010080
		lfd f1, double_to_int_802c4da0@l(r4)
		opword 0xC8010080
		lfs f2, float_360_8041a3ec(r2)
		opword 0xEC200828
		lfs f0, float_0p125_8041a418(r2)
		opword 0xD0810008
		opword 0xEC220072
		opword 0xD081000C
		opword 0xD0810010
		opword 0xEC410032
		opword 0xD0610014
		opword 0x4082000C
		lfs f0, float_180_8041a41c(r2)
		opword 0xEC42002A
		lfs f1, float_6p2832_8041a3e8(r2)
		lfs f0, float_360_8041a3ec(r2)
		opword 0xEC2100B2
		opword 0xEFC10024
		opword 0xFC20F090
		bl sin
		opword 0xFC800818
		opword 0xC001004C
		lfs f3, float_30_8041a420(r2)
		opword 0xFC20F090
		opword 0xC0410048
		opword 0xD0010028
		opword 0xEC03113C
		opword 0xD0010024
		bl cos
		opword 0xFC200818
		lfs f4, float_0_8041a3f0(r2)
		lfs f0, float_1E06_8041a414(r2)
		opword 0x38810008
		lfs f5, float_30_8041a420(r2)
		opword 0xFCC02090
		opword 0xFC600850
		opword 0xC0410050
		opword 0xD0010014
		opword 0x38A1000C
		opword 0xC0210024
		opword 0x38C10010
		opword 0xEC6510FC
		opword 0xC0410028
		lfs f5, float_neg1_8041a410(r2)
		opword 0x38E10014
		opword 0x39010018
		opword 0x3921001C
		opword 0xD061002C
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4182000C
		opword 0xC001000C
		opword 0xD0010028
		opword 0x80810024
		opword 0xFC20F090
		opword 0x80610028
		opword 0x8001002C
		opword 0x90810030
		opword 0x90610034
		opword 0x90010038
		bl sin
		lfs f2, float_30_8041a420(r2)
		opword 0xFC600818
		opword 0xC0010030
		opword 0xFC20F090
		opword 0xEFC2F82A
		opword 0xEC1E00FA
		opword 0xD0010030
		bl cos
		opword 0xFC000818
		opword 0x80C10024
		opword 0x80010028
		opword 0x80A1002C
		opword 0xFC200050
		opword 0xC0010038
		opword 0x80810030
		opword 0x80610034
		opword 0xEC1E007A
		opword 0x90C10048
		opword 0x9001004C
		opword 0xD0010038
		opword 0x80010038
		opword 0x90A10050
		opword 0x9081003C
		opword 0x90610040
		opword 0x90010044
		opword 0xC021003C
		opword 0xC0410040
		opword 0xC0610044
		opword 0xC0A10048
		opword 0xC081004C
		opword 0xC0010050
		stfs f5, BeroSX(r13)
		stfs f4, BeroSY(r13)
		stfs f0, BeroSZ(r13)
		stfs f1, BeroEX(r13)
		stfs f2, BeroEY(r13)
		stfs f3, BeroEZ(r13)
		bl N_marioSetBottomlessRespawnPosOnBeroEntry
		opword 0xA01F002E
		opword 0x28000019
		opword 0x40820008
		bl N_marioReloadMapOnBottomlessOn
		opword 0x38600002
		opword 0xE3E100B8
		opword 0xCBE100B0
		opword 0xE3C100A8
		opword 0xCBC100A0
		opword 0x83E1009C
		opword 0x83C10098
		opword 0x800100C4
		opword 0x83A10094
		opword 0x7C0803A6
		opword 0x382100C0
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end) {
	char _af_pad[32];
	asm volatile {
		lfs f1, float_0_8041a3f0(r2)
		opword 0x2C060008
		lfs f0, float_10000_8041a40c(r2)
		opword 0x7C9C2378
		stfs f1, _af_pad+24(r1)
		opword 0x7CBD2B78
		lfs f31, float_20_8041a400(r2)
		opword 0x7CFE3B78
		opword 0xD021001C
		opword 0x7D1F4378
		opword 0xD0210018
		opword 0xD0010014
		opword 0x41820188
		opword 0x4080001C
		opword 0x2C060006
		opword 0x4182002C
		opword 0x40800218
		opword 0x2C060002
		opword 0x41820028
		opword 0x4800020C
		opword 0x2C062710
		opword 0x41820204
		opword 0x40800200
		opword 0x2C06000A
		opword 0x408001F8
		opword 0x48000150
		neg r28, r28
		opword 0xFFE0F850
		opword 0x2C030000
		opword 0x4082009C
		opword 0x7FA3EB78
		opword 0x7FC4F378
		bl hitObjGetPos
		opword 0xC01E0000
		opword 0x6F838000
		opword 0x3C004330
		lis r4, double_to_int_802c4da0@ha
		opword 0xEC00F828
		opword 0x9061002C
		addi r3, r4, double_to_int_802c4da0@l
		lfs f4, float_0_8041a3f0(r2)
		opword 0x90010028
		opword 0x38810020
		opword 0xD01E0000
		opword 0xFCC02090
		opword 0xC8230000
		opword 0x38A1001C
		opword 0xC8010028
		opword 0x38C10018
		opword 0xC05E0000
		opword 0xEC000828
		lfs f5, float_neg1_8041a410(r2)
		opword 0x38E10014
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0xEC02002A
		opword 0x38600000
		opword 0xD01F0000
		opword 0xC01E0004
		opword 0xD01F0004
		opword 0xC01E0008
		opword 0xD01F0008
		opword 0xC03F0000
		opword 0xC05F0004
		opword 0xC07F0008
		bl hitCheckFilter
		opword 0x48000098
		opword 0x7FA3EB78
		opword 0x7FE4FB78
		bl hitObjGetPos
		opword 0xC01F0000
		opword 0x6F838000
		opword 0x3C004330
		lis r4, double_to_int_802c4da0@ha
		opword 0xEC00F828
		opword 0x9061002C
		addi r3, r4, double_to_int_802c4da0@l
		lfs f4, float_0_8041a3f0(r2)
		opword 0x90010028
		opword 0x38810020
		opword 0xD01F0000
		opword 0xFCC02090
		opword 0xC8230000
		opword 0x38A1001C
		opword 0xC8010028
		opword 0x38C10018
		opword 0xC05F0000
		opword 0xEC000828
		lfs f5, float_neg1_8041a410(r2)
		opword 0x38E10014
		opword 0x39010010
		opword 0x3921000C
		opword 0x39410008
		opword 0xEC02002A
		opword 0x38600000
		opword 0xD01E0000
		opword 0xC01F0004
		opword 0xD01E0004
		opword 0xC01F0008
		opword 0xD01E0008
		opword 0xC03E0000
		opword 0xC05E0004
		opword 0xC07E0008
		bl hitCheckFilter
		opword 0xC001001C
		opword 0xD01E0004
		opword 0xD01F0004
		opword 0x480000C0
		opword 0x7F9C00D0
		opword 0x2C030000
		opword 0x40820050
		opword 0x7FA3EB78
		opword 0x7FC4F378
		bl hitObjGetPos
		opword 0x6F838000
		opword 0x3C004330
		opword 0x9061002C
		lis r4, double_to_int_802c4da0@ha
		opword 0xC05E0000
		opword 0x90010028
		lfd f1, double_to_int_802c4da0@l(r4)
		opword 0xC8010028
		opword 0xD05F0000
		opword 0xEC000828
		opword 0xC03E0004
		opword 0xEC01002A
		opword 0xD01F0004
		opword 0xC01E0008
		opword 0xD01F0008
		opword 0x48000068
		opword 0x7FA3EB78
		opword 0x7FE4FB78
		bl hitObjGetPos
		opword 0x6F838000
		opword 0x3C004330
		opword 0x9061002C
		lis r4, double_to_int_802c4da0@ha
		opword 0xC05F0000
		opword 0x90010028
		lfd f1, double_to_int_802c4da0@l(r4)
		opword 0xC8010028
		opword 0xD05E0000
		opword 0xEC000828
		opword 0xC03F0004
		opword 0xEC01002A
		opword 0xD01E0004
		opword 0xC01F0008
		opword 0xD01E0008
		opword 0x4800001C
		opword 0x7FA3EB78
		opword 0x7FC4F378
		bl hitObjGetPos
		opword 0x7FA3EB78
		opword 0x7FE4FB78
		bl hitObjGetPos
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 bero_get_position_pipe_pure(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0x93E1003C
		opword 0x93C10038
		opword 0x93A10034
		opword 0x7C7D1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7F1B78
		opword 0x7FA3EB78
		bl evtGetFloat
		opword 0xFC00081E
		opword 0x83DD00B0
		opword 0x80BD00A8
		opword 0x7FE3FB78
		opword 0x7FC6F378
		opword 0x38E10014
		opword 0xD8010020
		opword 0x39010008
		opword 0x80810024
		bl bero_get_position_pipe_sub
		opword 0xC0010014
		opword 0x2C1E0008
		stfs f0, BeroSX(r13)
		opword 0x40820014
		opword 0xC0210018
		lfs f0, float_37p5_8041a408(r2)
		opword 0xEC410028
		opword 0x48000008
		opword 0xC0410018
		opword 0xC001001C
		opword 0x2C1E0008
		opword 0xC0210008
		stfs f2, BeroSY(r13)
		stfs f0, BeroSZ(r13)
		stfs f1, BeroEX(r13)
		opword 0x40820014
		opword 0xC041000C
		lfs f0, float_37p5_8041a408(r2)
		opword 0xEC020028
		opword 0x48000008
		opword 0xC001000C
		opword 0xC0610010
		opword 0xFC400018
		stfs f0, BeroEY(r13)
		stfs f3, BeroEZ(r13)
		bl N_marioSetBottomlessRespawnPosOnBeroEntry
		opword 0x80010044
		opword 0x38600002
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x83A10034
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 bero_get_position_pipe2(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0x93E1006C
		opword 0x93C10068
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFC00081E
		opword 0x80BE00A8
		opword 0x80DE00B0
		opword 0x7FE3FB78
		opword 0x38E1002C
		opword 0x39010020
		opword 0xD8010060
		opword 0x80810064
		bl bero_get_position_pipe_sub
		opword 0xC0210024
		lfs f0, float_1_8041a404(r2)
		opword 0xEC01002A
		opword 0xD0010024
		bl camRoadReset
		bl camShiftReset
		opword 0xC0610028
		opword 0x38610038
		opword 0xC0410024
		opword 0xC0210020
		opword 0xFCC01890
		opword 0xFCA01090
		lfs f7, float_0_8041a3f0(r2)
		opword 0xFC800890
		bl camRoadMain
		lis r4, vec3_802c4990@ha
		lwzu r9, vec3_802c4990@l(r4)
		lis r3, vec3_802c499c@ha
		opword 0xC0A10044
		addi r6, r3, vec3_802c499c@l
		opword 0x81040004
		opword 0x80E40008
		opword 0x38600002
		opword 0x80A60000
		opword 0x80860004
		opword 0x80060008
		opword 0x91210014
		opword 0xC0810048
		opword 0x91010018
		opword 0xC061004C
		opword 0x90E1001C
		opword 0xC0410050
		opword 0x90A10008
		opword 0xC0210054
		opword 0x9081000C
		opword 0xC0010058
		opword 0x90010010
		opword 0xD0A10014
		opword 0xD0810018
		opword 0x81010014
		opword 0xD061001C
		opword 0x80E10018
		opword 0xD0410008
		opword 0x80C1001C
		opword 0xD021000C
		opword 0x80A10008
		opword 0xD0010010
		opword 0x8081000C
		opword 0x80010010
		stw r8, BeroPT(r13)
		stw r7, BeroPT+0x4(r13)
		stw r6, BeroPT+0x8(r13)
		stw r5, BeroAT(r13)
		stw r4, BeroAT+0x4(r13)
		stw r0, BeroAT+0x8(r13)
		opword 0x83E1006C
		opword 0x80010074
		opword 0x83C10068
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 bero_set_disp_position_pipe(BeroPipeInfo* info) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x800300B0
		opword 0x2C000007
		opword 0x418200A8
		opword 0x4080001C
		opword 0x2C000002
		opword 0x4182002C
		opword 0x41800098
		opword 0x2C000006
		opword 0x40800020
		opword 0x4800008C
		opword 0x2C002710
		opword 0x41820084
		opword 0x40800080
		opword 0x2C00000A
		opword 0x40800078
		opword 0x4800003C
		opword 0x800300AC
		opword 0x540004E7
		opword 0x40820068
		bl marioGetPtr
		opword 0xC023009C
		lfs f0, float_3_8041a3f4(r2)
		opword 0xEC01002A
		opword 0xD003009C
		bl marioGetPtr
		opword 0xC02300A0
		lfs f0, float_15_8041a3f8(r2)
		opword 0xEC010028
		opword 0xD00300A0
		opword 0x4800003C
		opword 0x800300AC
		opword 0x540004E7
		opword 0x4082001C
		bl marioGetPtr
		opword 0xC02300A0
		lfs f0, float_13_8041a3fc(r2)
		opword 0xEC010028
		opword 0xD00300A0
		opword 0x48000018
		bl marioGetPtr
		opword 0xC02300A0
		lfs f0, float_20_8041a400(r2)
		opword 0xEC010028
		opword 0xD00300A0
		opword 0x80010014
		opword 0x38600002
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

s32 evt_bero_switch_on(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_switch_off(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_get_number(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_case_id_save(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	BeroID[id] = evtGetValue(event, args[1]);
	return EVT_RETURN_DONE;
}

s32 evt_bero_case_id_load(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	s32 id = evtGetValue(event, args[0]);
	evtSetValue(event, args[1], BeroID[id]);
	return EVT_RETURN_DONE;
}

s32 evt_bero_disppos_save(EventEntry* event, BOOL isFirstCall) {
	BeroOX = marioGetPtr()->dispOfs.x;
	BeroOY = marioGetPtr()->dispOfs.y;
	BeroOZ = marioGetPtr()->dispOfs.z;
	return EVT_RETURN_DONE;
}

s32 evt_bero_disppos_load(EventEntry* event, BOOL isFirstCall) {
	marioGetPtr()->dispOfs.x = BeroOX;
	marioGetPtr()->dispOfs.y = BeroOY;
	marioGetPtr()->dispOfs.z = BeroOZ;
	return EVT_RETURN_DONE;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 evt_bero_move_mario_speed(EventEntry* event, BOOL isFirstCall) {
	char _af_pad[4];
	asm volatile {
		mr r29, r3
		opword 0x7C9E2378
		opword 0x80830018
		opword 0x80840000
		bl evtGetFloat
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820010
		opword 0x80030038
		opword 0x83E3003C
		opword 0x4800000C
		opword 0x80030040
		opword 0x83E30044
		opword 0x2C1E0000
		opword 0x4182000C
		opword 0x93FD019C
		opword 0x901D0198
		bl sysFrame2SecFloat
		opword 0xFFA00890
		lfs f1, BeroSX(r13)
		lfs f2, BeroSY(r13)
		lfs f3, BeroEX(r13)
		lfs f4, BeroEY(r13)
		bl angleABf
		bl reviseAngle
		lfs f2, float_6p2832_8041a3e8(r2)
		lfs f0, float_360_8041a3ec(r2)
		opword 0xEC220072
		opword 0xEF610024
		opword 0xFC20D890
		bl sin
		opword 0xFF800818
		opword 0xFC20D890
		bl cos
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38634DD3
		opword 0x809D019C
		opword 0xFF600818
		opword 0x5400F0BE
		opword 0x38A00000
		opword 0x7C030016
		opword 0x7C84F850
		opword 0x7C83FE70
		opword 0x5406D1BE
		bl __div2u
		opword 0x7C832378
		bl sysMsec2Frame
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_802c4da0@ha
		opword 0xEC5D06F2
		lfd f1, double_to_int_802c4da0@l(r4)
		stw r0, _af_pad+0(r1)
		opword 0xEFFD0732
		opword 0xC8010008
		opword 0xFFC01050
		lfs f2, BeroSX(r13)
		opword 0xEC000828
		fmuls f26, f29, f0
		opword 0xEC1C06B2
		opword 0xEFA2002A
		bl marioGetPtr
		opword 0xEC1B06B2
		opword 0xD3A3008C
		lfs f1, BeroSY(r13)
		opword 0xFC000050
		opword 0xEFA1002A
		bl marioGetPtr
		opword 0xD3A30090
		lfs f29, BeroSZ(r13)
		bl marioGetPtr
		lfs f0, float_0_8041a3f0(r2)
		opword 0x3BE00000
		opword 0xD3A30094
		opword 0xFC1F0040
		opword 0x4C411382
		opword 0x40820020
		bl marioGetPtr
		opword 0xC023008C
		lfs f0, BeroEX(r13)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820008
		opword 0x3BE00001
		lfs f0, float_0_8041a3f0(r2)
		opword 0xFC1F0040
		opword 0x40800020
		bl marioGetPtr
		opword 0xC023008C
		lfs f0, BeroEX(r13)
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820008
		opword 0x3BE00001
		lfs f0, float_0_8041a3f0(r2)
		opword 0x3BC00000
		opword 0xFC1E0040
		opword 0x4C411382
		opword 0x40820020
		bl marioGetPtr
		opword 0xC0230090
		lfs f0, BeroEY(r13)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820008
		opword 0x3BC00001
		lfs f0, float_0_8041a3f0(r2)
		opword 0xFC1E0040
		opword 0x40800020
		bl marioGetPtr
		opword 0xC0230090
		lfs f0, BeroEY(r13)
		opword 0xFC000840
		opword 0x4C411382
		opword 0x40820008
		opword 0x3BC00001
		opword 0x7C1FF214
		opword 0x2C000002
		opword 0x4182000C
		opword 0x38600000
		opword 0x4800002C
		lfs f30, BeroEX(r13)
		bl marioGetPtr
		opword 0xD3C3008C
		lfs f30, BeroEY(r13)
		bl marioGetPtr
		opword 0xD3C30090
		lfs f30, BeroEZ(r13)
		bl marioGetPtr
		opword 0xD3C30094
		opword 0x38600002
	}
}
#pragma pop

s32 evt_bero_overwrite(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_cam3d_change(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_cam_shift_init(EventEntry* event, BOOL isFirstCall) {
	camRoadReset();
	camShiftReset();
	return EVT_RETURN_DONE;
}

s32 evt_bero_mario_go_init(EventEntry* event, BOOL isFirstCall) {
	BeroMarioGO = FALSE;
	return EVT_RETURN_DONE;
}

s32 evt_bero_mario_go(EventEntry* event, BOOL isFirstCall) {
	BeroMarioGO = TRUE;
	return EVT_RETURN_DONE;
}

s32 evt_bero_mario_go_wait(EventEntry* event, BOOL isFirstCall) {
	return BeroMarioGO == 0 ? 0 : EVT_RETURN_DONE;
}

s32 evt_bero_1stcheck(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	if (strcmp((const char*)event->lwData[13], str_802C4D94) == 0) {
		evtSetValue(event, args[0], 1);
	} else {
		evtSetValue(event, args[0], 0);
	}
	return EVT_RETURN_DONE;
}

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_camera_change_event_from_road(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0x93E1005C
		opword 0x93C10058
		opword 0x93A10054
		opword 0x93810050
		bl marioGetPtr
		opword 0x7C601B78
		opword 0x38600004
		opword 0x7C1C0378
		bl camGetPtr
		opword 0x7C7F1B78
		opword 0x7F84E378
		opword 0x38A10008
		bl camShiftMain
		opword 0xC07C0094
		opword 0x38610024
		opword 0xC05F0098
		opword 0xC03C008C
		opword 0xFCC01890
		opword 0xFCA01090
		opword 0xC0E10008
		opword 0xFC800890
		bl camRoadMain
		lis r3, vec3_802c4c58@ha
		lis r4, vec3_802c4c64@ha
		addi r5, r3, vec3_802c4c58@l
		opword 0x3C601062
		addi r8, r4, vec3_802c4c64@l
		opword 0x83850000
		opword 0x83A50004
		opword 0x3CC08000
		opword 0x81450008
		opword 0x38E34DD3
		opword 0x83C80000
		opword 0x38A00000
		opword 0x81880004
		opword 0x38800003
		opword 0x81680008
		opword 0x3800000B
		opword 0xC0A10030
		opword 0x38600002
		opword 0xC0810034
		opword 0xC0610038
		opword 0xC041003C
		opword 0xC0210040
		opword 0xC0010044
		opword 0x813F000C
		opword 0x811F0010
		opword 0x93810018
		opword 0x913F0058
		opword 0x911F005C
		opword 0x811F0014
		opword 0x93A1001C
		opword 0x911F0060
		opword 0xD0A10018
		opword 0x813F0018
		opword 0x811F001C
		opword 0x91410020
		opword 0x81410018
		opword 0x913F0064
		opword 0x911F0068
		opword 0x811F0020
		opword 0xD081001C
		opword 0x911F006C
		opword 0x8101001C
		opword 0xD0610020
		opword 0x93C1000C
		opword 0x81210020
		opword 0x915F0040
		opword 0x91810010
		opword 0xD041000C
		opword 0x911F0044
		opword 0x8101000C
		opword 0x91610014
		opword 0xD0210010
		opword 0x913F0048
		opword 0x81210010
		opword 0xD0010014
		opword 0x911F004C
		opword 0x81010014
		opword 0x913F0050
		opword 0x911F0054
		lwz r9, gp(r13)
		opword 0x81090038
		opword 0x8129003C
		opword 0x913F0074
		opword 0x911F0070
		opword 0x80C600F8
		opword 0x54C6F0BE
		opword 0x7CC73016
		opword 0x54C6D1BE
		opword 0x1CC601F4
		opword 0x90DF007C
		opword 0x90BF0078
		opword 0xB09F0004
		opword 0x981F0080
		opword 0x83E1005C
		opword 0x83C10058
		opword 0x83A10054
		opword 0x83810050
		opword 0x80010064
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
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
L_af_1:
	lwz r3, 0x0(r30)
	bl hitNameToPtr
	lwz r4, 0x0(r30)
	cmplwi r4, 0x0
	beq L_af_2
	cmplwi r3, 0x0
	bne L_af_3
	li r3, 0x1
	bl mapErrorEntry
L_af_3:
	addi r30, r30, 0x3c
	b L_af_1
L_af_2:
	lis r3, BeroSW@ha
	lwz r6, 0x9c(r29)
	addi r4, r3, BeroSW@l
	li r5, 0x0
	li r0, -0x1
L_af_4:
	lwz r3, 0x0(r6)
	cmplwi r3, 0x0
	beq L_af_5
	stw r6, 0x0(r31)
	addi r31, r31, 0x4
	addi r5, r5, 0x1
	addi r6, r6, 0x3c
	stw r0, 0x0(r4)
	addi r4, r4, 0x4
	b L_af_4
L_af_5:
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 N_evt_bero_set_mario_bottomless_respawn_pos_on_bero_entry(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x93A10024
		opword 0x7C7D1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		opword 0x809F0004
		opword 0x7C7E1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x809F0008
		opword 0x7C7F1B78
		opword 0x7FA3EB78
		bl evtGetValue
		opword 0x3CA04330
		opword 0x6FC68000
		opword 0x90C1000C
		opword 0x6C608000
		opword 0x6FE48000
		lis r3, double_to_int_802c4da0@ha
		opword 0x90A10008
		lfd f3, double_to_int_802c4da0@l(r3)
		opword 0xC8010008
		opword 0x90810014
		opword 0xEC201828
		opword 0x90A10010
		opword 0xC8010010
		opword 0x9001001C
		opword 0xEC401828
		opword 0x90A10018
		opword 0xC8010018
		opword 0xEC601828
		bl N_marioSetBottomlessRespawnPosOnBeroEntry
		opword 0x80010034
		opword 0x38600002
		opword 0x83E1002C
		opword 0x83C10028
		opword 0x83A10024
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall) {
	MarioWork* wp = marioGetPtr();
	N_marioSetBottomlessRespawnPosOnBeroEntry(wp->position.x, wp->position.y, wp->position.z);
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

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void bero_clear_Offset(void) {
	asm volatile {
		lfs f0, float_0_8041a3f0(r2)
		stfs f0, BeroOX(r13)
		stfs f0, BeroOY(r13)
		stfs f0, BeroOZ(r13)
	}
}
#pragma pop

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

s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;
	const char *map, *bero;

	map = (const char*)evtGetValue(event, args[0]);
	bero = (const char*)evtGetValue(event, args[1]);
	if (isFirstCall) {
		seqSetSeq(SEQ_MAP_CHANGE, map, bero);
	}
	return EVT_RETURN_BLOCK;
}

s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall) {
	evtSetValue(event, *event->args, (s32)&gp->beroEnterName);
	return EVT_RETURN_DONE;
}

s32 evt_bero_exec_onoff(EventEntry* event, BOOL isFirstCall) {
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

s32 evt_bero_exec_get(EventEntry* event, BOOL isFirstCall) {
	evtSetValue(event, *event->args, BeroEXEC);
	return EVT_RETURN_DONE;
}

s32 evt_bero_exec_wait(EventEntry* event, BOOL isFirstCall) {
	return evtGetValue(event, *event->args) & BeroEXEC ? EVT_RETURN_DONE : 0;
}

s32 evt_bero_get_start_position(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroSX);
	evtSetFloat(event, args[1], BeroSY);
	evtSetFloat(event, args[2], BeroSZ);
	return EVT_RETURN_DONE;
}

s32 evt_bero_get_end_position(EventEntry* event, BOOL isFirstCall) {
	s32* args = event->args;

	evtSetFloat(event, args[0], BeroEX);
	evtSetFloat(event, args[1], BeroEY);
	evtSetFloat(event, args[2], BeroEZ);
	return EVT_RETURN_DONE;
}

s32 evt_bero_get_info_anime(EventEntry* event, BOOL isFirstCall) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->enterAnimeType);
	evtSetValue(event, args[2], *(u16*)&bero->exitAnimeType);
	evtSetValue(event, args[3], bero->enterAnimeArg);
	evtSetValue(event, args[4], bero->exitAnimeArg);
	return EVT_RETURN_DONE;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_bero_get_info_length(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x7C7E1B78
		opword 0x83E30018
		opword 0x809F0000
		bl evtGetValue
		lis r4, BeroINFOARR@ha
		opword 0x5460103A
		addi r3, r4, BeroINFOARR@l
		opword 0x7C63002E
		opword 0x80030018
		opword 0x2C00FFFF
		opword 0x4182003C
		opword 0x6C038000
		opword 0x3C004330
		lis r4, double_to_int_802c4da0@ha
		opword 0x9061000C
		addi r5, r4, double_to_int_802c4da0@l
		opword 0x809F0004
		opword 0x90010008
		opword 0x7FC3F378
		opword 0xC8250000
		opword 0xC8010008
		opword 0xEC200828
		bl evtSetFloat
		opword 0x38600002
		opword 0x48000068
		opword 0xA0030004
		opword 0x5400053E
		opword 0x2C000003
		opword 0x4182002C
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820028
		opword 0x4080002C
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000028
		opword 0x2C000F00
		opword 0x41820008
		opword 0x4800001C
		lfs f1, float_30_8041a420(r2)
		opword 0x48000018
		lfs f1, float_60_8041a428(r2)
		opword 0x48000010
		lfs f1, float_60_8041a428(r2)
		opword 0x48000008
		lfs f1, float_60_8041a428(r2)
		opword 0x809F0004
		opword 0x7FC3F378
		bl evtSetFloat
		opword 0x38600002
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

s32 evt_bero_get_info_kinddir(EventEntry* event, BOOL isFirstCall) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], *(u16*)&bero->type);
	evtSetValue(event, args[2], *(u16*)&bero->sfxId);
	evtSetValue(event, args[3], bero->directionId);
	return EVT_RETURN_DONE;
}

s32 evt_bero_get_info_nextarea(EventEntry* event, BOOL isFirstCall) {
	BeroEntry* bero;
	s32* args = event->args;

	bero = BeroINFOARR[evtGetValue(event, args[0])];
	evtSetValue(event, args[1], bero->nextMapName);
	evtSetValue(event, args[2], (s32)bero->nextBeroName);
	return EVT_RETURN_DONE;
}

s32 evt_bero_set_now_number(EventEntry* event, BOOL isFirstCall) {
	BeroNOWNUM = evtGetValue(event, *event->args);
	return EVT_RETURN_DONE;
}

s32 evt_bero_get_now_number(EventEntry* event, BOOL isFirstCall) {
	evtSetValue(event, *event->args, BeroNOWNUM);
	return EVT_RETURN_DONE;
}


// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".sdata2") const char str_8041A3C8[4] = "n_\0";
__declspec(section ".sdata2") const char str_8041A3CC[4] = "ne_";
__declspec(section ".sdata2") const char str_8041A3D0[4] = "e_\0";
__declspec(section ".sdata2") const char str_8041A3D4[4] = "se_";
__declspec(section ".sdata2") const char str_8041A3D8[4] = "s_\0";
__declspec(section ".sdata2") const char str_8041A3DC[4] = "sw_";
__declspec(section ".sdata2") const char str_8041A3E0[4] = "w_\0";
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
__declspec(section ".sdata2") const u32 gap_09_8041A42C_sdata2 = 0x00000000;

#endif

// .bss definitions last (target order BeroID, BeroSW, BeroINFOARR: reverse declaration order)
BeroEntry* BeroINFOARR[16];
s32 BeroSW[16];
s32 BeroID[16];

#ifdef NONMATCHING // all-C link: pool objects the C names, defined on the asm side only
__declspec(section ".sdata2") const char str_8041A3C8[4] = "n_\0";
__declspec(section ".sdata2") const char str_8041A3CC[4] = "ne_";
__declspec(section ".sdata2") const char str_8041A3D0[4] = "e_\0";
__declspec(section ".sdata2") const char str_8041A3D4[4] = "se_";
__declspec(section ".sdata2") const char str_8041A3D8[4] = "s_\0";
__declspec(section ".sdata2") const char str_8041A3DC[4] = "sw_";
__declspec(section ".sdata2") const char str_8041A3E0[4] = "w_\0";
__declspec(section ".sdata2") const char str_8041A3E4[4] = "nw_";
#endif
