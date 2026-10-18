#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "memory.h"
#include "string.h"
#include "stdlib.h"
#include "system.h"
#include "manager/filemgr.h"
#include "manager/evtmgr_cmd.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "sdk/texPalette.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "win/win_main.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "dolphin/os.h"
#include "driver/effdrv.h"
#include "eff/n64/eff_ripple_n64.h"
#include "evt/evt_cmd.h"
#include "stdio.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
extern const char str_00000194[];
extern const char str_000001A0[];
extern const char str_000001AC[];
extern const char str_000001B8[];
extern const char str_000001C8[];
extern const char str_000001D4[];
extern const char str_000001E0[];
extern const char str_000001EC[];
extern const char str_000001F8[];
extern const char str_00000200[];
extern const char str_00000208[];
extern const char str_00000210[];
extern const char str_00000218[];
extern const char str_00000220[];
extern const char str_00000234[];
extern const char str_00000244[];
extern const char str_0000025C[];
extern const char str_000002AC[];
extern const char str_000002B4[];
extern const char str_000002C0[];
extern const char str_000002DC[];
extern const char str_000002E4[];
extern const char str_000002EC[];
extern const char str_000002F8[];
extern const char str_00000300[];
extern const char str_0000030C[];
extern const char str_00000318[];
extern const char str_0000031C[];
extern const char str_00000324[];
extern const char str_0000032C[];
extern const char str_00000330[];
extern const char str_00000338[];
extern const char str_00000340[];
extern const char str_00000348[];
extern const char str_00000350[];
extern const char str_00000368[];
extern const char str_00000370[];
extern const char str_00000380[];
extern const char str_00000390[];
extern const char str_000003A0[];
extern const char str_000003AC[];
extern const char str_000003BC[];
extern const char str_000003C8[];
extern const char str_000003CC[];
extern const char str_000003D8[];
extern const char str_000003E4[];
extern const char str_000003EC[];
extern const char str_000003F4[];
extern const char str_00000410[];
extern const char str_00000418[];
extern const char str_00000430[];
extern const char str_00000440[];
extern const char str_00000450[];
extern const char str_00000468[];
extern const char str_0000047C[];
extern const char str_00000484[];
extern const char str_00000490[];
extern const char str_000004A0[];
extern const char str_000004AC[];
extern const char str_000004B8[];
extern const char str_000004C4[];
extern const char str_000004D0[];
extern const char str_000004EC[];
extern const char str_00000508[];
extern const char str_00000510[];
extern const char str_0000051C[];
extern const char str_00000528[];
extern const char str_00000534[];
extern const char str_0000054C[];
extern const char str_00000558[];
extern const char str_00000564[];
extern const char str_0000057C[];
extern const char str_00000594[];
extern const char str_000005AC[];
extern const char str_000005B4[];
extern const char str_000005C0[];
extern const char str_000005D8[];
extern const char str_000005E8[];
extern const char str_000005F8[];
extern const char str_00000610[];
extern const char str_0000061C[];
extern const char str_0000062C[];
extern const char str_0000063C[];
extern const char str_0000064C[];
extern const char str_0000065C[];
extern const char str_0000066C[];
extern const char str_0000067C[];
extern const char str_0000068C[];
extern const char str_0000069C[];
extern const char str_000006A8[];
extern const char str_000006BC[];
extern const char str_000006C8[];
extern const char str_000006E0[];
extern const char str_000006EC[];
extern const char str_00000704[];
extern const char str_0000071C[];
extern const char str_00000728[];
extern const char str_00000730[];
extern const char str_0000073C[];
extern const char str_00000748[];
extern const char str_00000760[];
extern const char str_00000768[];
extern const char str_00000774[];
extern const char str_0000077C[];
extern const char str_00000794[];
extern const char str_000007A0[];
extern const char str_000007BC[];
extern const char str_000007CC[];
extern const char str_000007DC[];
extern const char str_000007EC[];
extern const char str_00000804[];
extern const char str_00000814[];
extern const char str_00000824[];
extern const char str_00000834[];
extern const char str_00000840[];
extern const char str_0000084C[];
extern const char str_00000854[];
extern const char str_00000870[];
extern const char str_00000888[];
extern const char str_0000089C[];
extern const char str_000008B4[];
extern const char str_000008C4[];
extern const char str_000008D0[];
extern const char str_000008DC[];
extern const char str_000008E8[];
extern const char str_000008F4[];
extern const char str_000008FC[];
extern const char str_00000910[];
extern const char str_00000924[];
extern const char str_00000934[];
extern const char str_00000940[];
extern const char str_00000950[];
extern const char str_0000095C[];
extern const char str_0000096C[];
extern const char str_0000097C[];
extern const char str_00000988[];
extern const char str_00000998[];
extern const char str_000009A4[];
extern const char str_000009B4[];
extern const char str_000009C4[];
extern const char str_000009D0[];
extern const char str_000009E0[];
extern const char str_000009EC[];
extern const char str_000009FC[];
extern const char str_00000A0C[];
extern const char str_00000A18[];
extern const char str_00000A28[];
extern const char str_00000A34[];
extern const char str_00000A44[];
extern const char str_00000A54[];
extern const char str_00000A60[];
extern const char str_00000A6C[];
extern const char str_00000A7C[];
extern const char str_00000A88[];
extern const char str_00000A94[];
extern const char str_00000AA4[];
extern const char str_00000AB0[];
extern const char str_00000ABC[];
extern const char str_00000ACC[];
extern const char str_00000AD8[];
extern const char str_00000AE4[];
extern const char str_00000AF4[];
extern const char str_00000B00[];
extern const char str_00000B0C[];
extern const char str_00000B1C[];
extern const char str_00000B2C[];
extern const char str_00000B3C[];
extern const char str_00000B4C[];
extern const char str_00000B60[];
extern const char str_00000B6C[];
extern const char str_00000B80[];
extern const char str_00000B8C[];
extern const char str_00000BA0[];
extern const char str_00000BAC[];
extern const char str_00000BC0[];
extern const char str_00000BD4[];
extern const char str_00000BE8[];
extern const char str_00000BFC[];
extern const char str_00000C10[];
extern const char str_00000C24[];
extern const char str_00000C30[];
extern const char str_00000C38[];
extern const char str_00000C44[];
extern const char str_00000C54[];
extern const char str_00000C60[];
extern const char str_00000CA8[];
extern const char str_00000CB0[];
extern const char str_00000CBC[];
extern const char str_00000CCC[];
extern const char str_00000CDC[];
extern const char str_00000CEC[];
extern const char str_00000CFC[];
extern const char str_00000D0C[];
extern const char str_00000D1C[];
extern const char str_00000D2C[];
extern const char str_00000D34[];
extern const char str_00000D40[];
extern const char str_00000D50[];
extern const char str_00000D64[];
extern const char str_00000D74[];
extern const char str_00000D84[];
extern const char str_00000D8C[];
extern const char str_00000D94[];
extern const char str_00000D9C[];
extern const char str_00000DA4[];
extern const char str_00000DAC[];
extern const char str_00000DB4[];
extern const char str_00000DBC[];

typedef struct SightWork { FileEntry* tpl; s32 level[5]; f32 rot; s32 dir; s32 count1; s32 count2; } SightWork;
SightWork* sight_wp;
typedef struct BomSoundWork { u8 pad_0[0x330]; u16 sampleBank; u8 pad_332[0x5C0 - 0x332]; s16 samples[2][0x400]; u32 sampleIndex; } BomSoundWork;
extern BomSoundWork sound;
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
void disp_sight(CameraId camera, void* param);
void disp_sight(CameraId camera, void* param);
typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct ExtAnimDef { const char* file; const char* name; f32 time; } ExtAnimDef;
typedef struct BomAnim { char name[8]; f32 time; s32 start; s32 count; } BomAnim;
typedef struct Bom { u8 state; u8 next; u8 pad_2[2]; Vec target; f32 field_0x10; f32 gravity; s16 timer; u8 pad_1a[2]; f32 vy; s32 anim; u8 pad_24[4]; OSTime time; } Bom;
typedef struct BomWork { u16 flags; u8 pad_2[2]; s32 count; BomAnim anims[8]; s32 animCount; u8 pad_ac[4]; Bom bom[1000]; } BomWork;
#ifdef NONMATCHING
smartEntry* lp;
#else
// FAKE: target .bss is lp, name$915[0x40], sight_wp; MWCC put the local static first, so name is folded in as lp+4
smartEntry* lp[0x11];
#endif
#define EXT_DATA ((ExtAnimDef*)ext_data)
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
static void pose_change(s32 i, const char* name);
static void pose_change(s32 i, const char* name);
static s32 ext_data[93];
#ifdef NONMATCHING
static inline f32 chb_sin(f32 x) { f32 y; f32 x2; f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
#endif
#ifdef NONMATCHING
static inline f32 chb_cos(f32 x) { f32 y; f32 x2; f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
static void pose_init(void);
static void pose_init(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
double sin(double x);
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void pose_main(void);
static void pose_main(void);
static void ext_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
double cos(double x);
void effKemuTestSetRxRz(EffectEntry* effect, f32 rx, f32 rz);
static void depthDisp(CameraId camera, void* param);
static void depthDisp(CameraId camera, void* param);
typedef struct YamiParam { s32 field_0x0; f32 (*mtx)[4]; s32 field_0x8; s32 numTevStages; s32 field_0x10; s32 numTexGens; s32 numIndStages; } YamiParam;
void envSetYami(YamiParam* param);
void extPoseDraw(s32 i);
void ext_disp_minnnanokoe(CameraId camera, void* param);
void ext_disp_minnnanokoe(CameraId camera, void* param);
void jump_minnnanokoe(s32 i, f32 h);
void jump_minnnanokoe(s32 i, f32 h);

s32 L_evt_party_vivian_tail(EventEntry* event, BOOL isFirstCall);
s32 N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos(EventEntry* event, BOOL isFirstCall);
static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(anim_tevcallback);
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
static s32 depth(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(depth);
s32 evt_bero_get_entername(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_bg_set_color(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_letter_box_disable(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_letter_box_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall);
s32 evt_eff(EventEntry* event, BOOL isFirstCall);
s32 evt_eff64(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_delete(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_reset(EventEntry* event, BOOL isFirstCall);
s32 evt_fade_set_mapchange_type(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_map_blend_off(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_blend(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_tevcallback(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_trans(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_toge(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_interrupt(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_jump_position_nohit(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_reverse_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_tribe(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_wait_pera(EventEntry* event, BOOL isFirstCall);
s32 evt_party_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pose(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_remove_item(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_set_dir_to_target(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgm_scope(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_env_lpf(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfx_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_spline_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_spline_init(EventEntry* event, BOOL isFirstCall);
s32 evt_telop_entry(EventEntry* event, BOOL isFirstCall);
s32 make_ext_table(EventEntry* event, BOOL isFirstCall);
s32 make_ext_table(EventEntry* event, BOOL isFirstCall);
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall);
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall);
static s32 make_name(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(make_name);
s32 sight(EventEntry* event, BOOL isFirstCall);
s32 sight(EventEntry* event, BOOL isFirstCall);
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(starstone_entry);
static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(starstone_set_pos);
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(starstone_set_ry);
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
static s32 yami_view(EventEntry* event, BOOL isFirstCall);
static USER_FUNC(yami_view);
void ext_dispent_minnnanokoe(void);
void ext_dispent_minnnanokoe(void);
void ext_disp_minnnanokoe(CameraId camera, void* param);
void jump_minnnanokoe(s32 i, f32 h);
void ext_init_minnnanokoe(void);
void ext_init_minnnanokoe(void);
static void depthDisp(CameraId camera, void* param);
static void ext_dispent(void);
static void ext_dispent(void);
static void ext_main(void);
static void ext_main(void);
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
static void ext_init(void);
static void ext_init(void);
static void pose_change(s32 i, const char* name);
static void pose_main(void);
static void pose_init(void);
void disp_sight(CameraId camera, void* param);
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
extern s32 bero_case_entry[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];
extern s32 evt_bom_snowfall[];
extern s32 evt_door_open_bom_01[];
extern s32 evt_sub_mail_event[];

__declspec(section ".data") u64 fd_bom_01_negone_one_374;
__declspec(section ".data") s32 fd_bom_01_neg_one_382[1];
__declspec(section ".data") s32 fd_bom_01___local_PI_383[1];
__declspec(section ".data") s32 fd_bom_01___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_bom_01_one_negone_373;
__declspec(section ".data") s32 fd_bom_01___local_PIO2_384[1];
__declspec(section ".data") s32 fd_bom_01_one_381[1];
__declspec(section ".data") u64 fd_bom_01_negone_one_360;
__declspec(section ".data") s32 fd_bom_01_neg_one_365[1];
__declspec(section ".data") s32 fd_bom_01___local_PI_366[1];
__declspec(section ".data") s32 fd_bom_01___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_bom_01_one_negone_359;
__declspec(section ".data") s32 fd_bom_01___local_PIO2_367[1];
__declspec(section ".data") s32 fd_bom_01_one_364[1];
__declspec(section ".data") s32 evt_door_1[12];
__declspec(section ".data") static s32 evt_door_2[12];
__declspec(section ".data") static s32 evt_wall[12];
__declspec(section ".data") s32 door_npc[4];
__declspec(section ".data") static s32 door_open[9];
__declspec(section ".data") static s32 door_close[10];
s32 door[18];
static s32 bero_entry_data[45];
static s32 first_evt[148];
s32 evt_bom_01_karakara[123];
static s32 ext_data[93];
s32 evt_bom1000[15];
__declspec(section ".data") s32 gamen_shake[8];
s32 gamen_shake2[26];
s32 mario_tobideru[54];
s32 mario_shot[160];
__declspec(section ".data") s32 effect_delete[11];
static s32 mario_kemuri[29];
__declspec(section ".data") s32 evt_depth[4];
s32 cam_outside[48];
s32 cam_inside[52];
s32 cam_inside2[52];
static s32 party_damage_pose[52];
s32 effect_1[84];
s32 open_hatch[83];
__declspec(section ".data") static s32 spline_dt[9];
__declspec(section ".data") s32 oh_data[8];
static s32 evt_taihou[2446];
static s32 init_soncho[13];
static s32 talk_soncho[24];
__declspec(section ".data") s32 init_nitoro[8];
s32 talk_nitoro[44];
__declspec(section ".data") s32 init_pentrit[8];
s32 talk_pentrit[44];
__declspec(section ".data") s32 init_surary[8];
s32 talk_surary[44];
__declspec(section ".data") s32 init_murabito_d[8];
s32 talk_murabito_d[44];
__declspec(section ".data") static s32 init_murabito_e[8];
static s32 talk_murabito_e[28];
__declspec(section ".data") static s32 init_murabito_f[8];
static s32 talk_murabito_f[28];
__declspec(section ".data") static s32 init_murabito_g[8];
static s32 talk_murabito_g[28];
__declspec(section ".data") static s32 init_murabito_h[8];
static s32 talk_murabito_h[28];
__declspec(section ".data") static s32 init_murabito_i[8];
static s32 talk_murabito_i[28];
static s32 init_white[22];
static s32 talk_white[39];
static s32 musume_talk[64];
static s32 musume_a_entry[26];
static s32 musume_b_entry[26];
static s32 musume_c_entry[26];
static s32 npcEnt[161];
s32 bom1000_minnnanokoe[21];
static s32 minnnanokoe_evt[450];
static s32 evt_door[14];
s32 bom_01_init_evt[189];

#ifdef NONMATCHING
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    Mtx trans;
    Mtx rotm;
    Mtx scale;
    GXTexObj obj;
    s16 w;
    u16 h;

    TEXGetGXTexObjFromPalette(*sight_wp->tpl->data, &obj, id);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    if (id == 0) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_KONST, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
    }
    PSMTXTrans(trans, x, y, 0.0f);
    PSMTXScale(scale, sx, sy, 1.0f);
    PSMTXRotRad(rotm, 'z', MTXDegToRad(rot));
    PSMTXConcat(trans, scale, scale);
    PSMTXConcat(scale, rotm, trans);
    PSMTXConcat(cam->view, trans, trans);
    GXLoadPosMtxImm(trans, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    w = GXGetTexObjWidth(&obj);
    h = GXGetTexObjHeight(&obj);
    GXPosition3s16(-w, h, 0);
    GXTexCoord2s16(0, 0);
    GXPosition3s16(0, h, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(0, 0, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(-w, 0, 0);
    GXTexCoord2s16(0, 1);
    GXEnd();
}
#endif

#ifdef NONMATCHING
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    GXTexObj obj;
    s32 i;
    s32 id;
    f32 w;
    s32 n = num < 0 ? -num : num;

    winTexInit(*sight_wp->tpl->data);
    for (i = 0; i < digits; i++) {
        id = n % 10 + 13;
        TEXGetGXTexObjFromPalette(*sight_wp->tpl->data, &obj, id);
        w = scale * GXGetTexObjWidth(&obj);
        w += 2.0f;
        winTexSet(id, (Vec){x + w * (digits - i - 1), y, 0.0f},
                  (Vec){scale, scale, scale}, color);
        n /= 10;
    }
}
#endif

#ifdef NONMATCHING
void disp_sight(CameraId camera, void* param) {
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    s32 i;
    s32 j;
    s32 n;
    s32 id;
    int on;
    f32 x;
    f32 y;

    drawBG(0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f);
    drawBG(1, 0.0f, 0.0f, 1.0f, 1.0f, sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, -1.0f, 1.0f, -sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, 1.0f, -1.0f, -sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, -1.0f, -1.0f, sight_wp->rot);
    if (sight_wp->dir == 2) {
        sight_wp->rot += 2.0f;
    } else if (sight_wp->dir == 3) {
        sight_wp->rot -= 2.0f;
    } else if (sight_wp->dir == 0) {
        sight_wp->rot -= 2.0f;
    } else {
        sight_wp->rot += 1.0f;
    }

    winTexInit(*sight_wp->tpl->data);
    winTexSet(5, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black);
    for (id = 0; id < 3; id++) {
        if ((s32)(gp->retraceCount % 30) / 10 != id) {
            i = 4 - id;
            drawBG(i, 100.0f, 60.0f, 1.0f, 1.0f, 0.0f);
            drawBG(i, -100.0f, 60.0f, -1.0f, 1.0f, 0.0f);
            drawBG(i, 100.0f, -60.0f, 1.0f, -1.0f, 0.0f);
            drawBG(i, -100.0f, -60.0f, -1.0f, -1.0f, 0.0f);
        }
    }

    winTexInit(*sight_wp->tpl->data);
    winTexSet(23, (Vec){-200.0f, 150.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    drawNum((gp->renderTime / 100) / 1000, 10, 90.0f, 180.0f, 0.6f);
    drawNum((gp->renderTime / 200) / 1000, 8, 126.0f, 150.0f, 0.6f);
    drawNum((gp->renderTime / 300) / 1000, 6, 162.0f, 120.0f, 0.6f);
    drawNum((gp->renderTime / 400) / 1000, 6, 162.0f, 90.0f, 0.6f);
    drawNum(gp->retraceCount / 4, 4, 110.0f, -160.0f, 1.0f);
    drawNum(gp->retraceCount / 8, 2, 230.0f, -170.0f, 0.8f);

    winTexSet(8, (Vec){-210.0f, -140.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    if ((gp->retraceCount & 3) == 0) {
        for (i = 0; i < 4; i++) {
            sight_wp->level[i] = sight_wp->level[i + 1];
        }
        sight_wp->level[4] = abs(sound.samples[sound.sampleBank][sound.sampleIndex]);
    }
    for (i = 0; i < 5; i++) {
        n = sight_wp->level[i];
        n /= 300;
        if (n > 7) {
            n = 7;
        }
        x = (-240.0f) + 20.0f * i;
        for (j = 0; j < n; j++) {
            y = (-190.0f) + 16.0f * j;
            if (j == 6) {
                drawBG(10, x, y, 1.0f, 1.0f, 0.0f);
            } else {
                drawBG(9, x, y, 1.0f, 1.0f, 0.0f);
            }
        }
        for (j = n; j < 7; j++) {
            y = (-190.0f) + 16.0f * j;
            if (j == 6) {
                drawBG(12, x, y, 1.0f, 1.0f, 0.0f);
            } else {
                drawBG(11, x, y, 1.0f, 1.0f, 0.0f);
            }
        }
    }

    winTexInit(*sight_wp->tpl->data);
    for (i = 0; i < 4; i++) {
        on = (gp->retraceCount % 20 > 6 && i == sight_wp->dir) ? 1 : 0;
        id = 7;
        if (on != 0) {
            id = 6;
        }
        if (sight_wp->dir == 4) {
            on = 0;
            id = 7;
        }
        switch (i) {
            case 0:
                drawBG(id, 16.0f, 180.0f, 1.0f, 1.0f, 90.0f);
                break;
            case 1:
                drawBG(id, -16.0f, -180.0f, 1.0f, 1.0f, 270.0f);
                break;
            case 2:
                drawBG(id, -180.0f, 16.0f, 1.0f, 1.0f, 180.0f);
                if (on && (gp->retraceCount & 3) == 0) {
                    sight_wp->count1++;
                }
                break;
            case 3:
                drawBG(id, 180.0f, -16.0f, 1.0f, 1.0f, 0.0f);
                if (on && (gp->retraceCount & 3) == 0) {
                    sight_wp->count2++;
                }
                break;
        }
    }
    drawNum(sight_wp->count1, 2, -220.0f, 0.0f, 0.8f);
    drawNum(sight_wp->count2, 2, 200.0f, 0.0f, 0.8f);
}
#endif

#ifdef NONMATCHING
s32 sight(EventEntry* event, BOOL isFirstCall) {
    s32 i;

    if (isFirstCall) {
        sight_wp = _mapAlloc(sizeof(SightWork));
        memset(sight_wp, 0, sizeof(SightWork));
        for (i = 0; i < 5; i++) {
            sight_wp->level[i] = 0;
        }
        sight_wp->count1 = rand();
        sight_wp->count2 = rand();
        sight_wp->dir = 5;
    }
    if (sight_wp->tpl == NULL) {
        if (fileAsyncf(4, NULL, "%s/%s", getMarioStDvdRoot(), "taihou.tpl") == 0U) {
            return EVT_RETURN_BLOCK;
        }
        sight_wp->tpl = fileAllocf(4, "%s/%s", getMarioStDvdRoot(), "taihou.tpl");
    }
    if (sight_wp->dir == 6) {
        fileFree(sight_wp->tpl);
        _mapFree(sight_wp);
        return EVT_RETURN_DONE;
    }
    if (sight_wp->dir != 5) {
        dispEntry(CAMERA_2D, 800.0f, 0, disp_sight, NULL);
    }
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
s32 sight_dir(EventEntry* event, BOOL isFirstCall) {
    sight_wp->dir = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 bom_flag(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);
    BomWork* wp = lp->address;

    if (on) {
        wp->flags |= mask;
    } else {
        wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 bom_fall(EventEntry* event, BOOL isFirstCall) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr();
    s32 i;

    for (i = 0; i < wp->count; i++, pose++) {
        wp->bom[i].state = 127;
        pose->mtx[0][3] = 600.0f * rand() / 32767.0f;
        pose->mtx[1][3] = 300.0f + 3700.0f * rand() / 32767.0f;
        pose->mtx[2][3] = -650.0f + -450.0f * rand() / 32767.0f;
        pose_change(i, "S_2");
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static void pose_init(void) {
    BomWork* wp; ExtAnimDef* def; char buf[32]; s32 i; s32 start; i = 0; wp = lp->address; def = EXT_DATA; strcpy(buf, ""); wp->animCount = -1; do { if (strcmp(def->name, buf) != 0) { strcpy(buf, def->name); wp->animCount++; start = i; } strcpy(wp->anims[wp->animCount].name, buf); wp->anims[wp->animCount].start = start; wp->anims[wp->animCount].count = i - start + 1; i++; wp->anims[wp->animCount].time = def->time; } while ((++def)->file != NULL); wp->animCount++;
}
#endif

#ifdef NONMATCHING
static void pose_main(void) {
    OSTime now;
    BomWork* wp = lp->address;
    s32 i;
    ExtPose* pose = extGetPosePtr();
    f32 t;

    for (i = 0; i < wp->count; i++, pose++) {
        BomAnim* a = &wp->anims[wp->bom[i].anim];
        now = gp->renderTime;

        t = 60.0f * OSTicksToMilliseconds((u64)(now - wp->bom[i].time)) / 1000.0f / a->time;
        if (t >= 1.0f) {
            wp->bom[i].time = now;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
#endif

#ifdef NONMATCHING
static void pose_change(s32 i, const char* name) {
    BomWork* wp = lp->address; s32 j = 0; BomAnim* a; for (a = wp->anims; j < wp->animCount; j++, a++) { if (strcmp(a->name, name) == 0) { break; } } if (j < wp->animCount && wp->bom[i].anim != j) { wp->bom[i].anim = (s16)j; wp->bom[i].time = gp->renderTime + rand(); }
}
#endif

#ifdef NONMATCHING
s32 make_ext_table(EventEntry* event, BOOL isFirstCall) {
    s32 i;

    memset(ext_data, 0, sizeof(ext_data));
    for (i = 0; i < 10; i++) {
        EXT_DATA[i].file = "c_bom_sen";
        EXT_DATA[i].name = "R_1";
        EXT_DATA[i].time = 2.0f * i;
    }
    for (i = 0; i < 20; i++) {
        EXT_DATA[10 + i].file = "c_bom_sen";
        EXT_DATA[10 + i].name = "S_2";
        EXT_DATA[10 + i].time = 6.0f * i;
    }
    EXT_DATA[30].file = NULL;
    return EVT_RETURN_DONE;
}
#endif

__declspec(section ".data") u64 fd_bom_01_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_01_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_01___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_01___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_01_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_01___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_01_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_bom_01_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_bom_01_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_bom_01___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_bom_01___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_bom_01_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_bom_01___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_bom_01_one_364[] = {
    1065353216,
};

__declspec(section ".data") EVT_BEGIN(evt_door_1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5546875f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_door_2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), LW(0), FLOAT(0.0f), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(evt_wall)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), FLOAT(0.0f), LW(0), FLOAT(0.0f))
    RETURN
EVT_END()

__declspec(section ".data") s32 door_npc[] = {
    (s32)/*"ホワイト"*/(char*)str_000001AC, (s32)/*"ペントリット"*/(char*)str_000001B8, (s32)/*"スラリー"*/(char*)str_000001C8, 0,
};

__declspec(section ".data") static EVT_BEGIN(door_open)
    CALL(evt_snd_envoff, 18432)
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(door_close)
    CALL(evt_snd_envon, 160, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

s32 door[] = {
    0, 3, 1, (s32)((char*)str_00000194), (s32)((char*)str_000001D4), (s32)((char*)str_000001E0), (s32)((char*)str_000001A0), 0,
    (s32)((char*)str_000001EC), 0, (s32)evt_door_1, (s32)evt_door_2, (s32)evt_wall, (s32)door_npc, 0, 0,
    (s32)door_open, (s32)door_close,
};

static s32 bero_entry_data[] = {
    (s32)((char*)str_000001F8), 0, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00000200), (s32)((char*)str_00000208), 65537, 0, 0, (s32)((char*)str_00000210),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00000218), (s32)((char*)str_000001F8), 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static EVT_BEGIN(first_evt)
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_cam_letter_box_onoff, 1, 1)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 340, 100, -53, 340, 80, -302, 0, 11)
    CALL(evt_mario_set_pos, -580, 0, 0)
    CALL(evt_party_set_pos, 0, -580, 0, 0)
    CALL(evt_seq_wait, 2)
    BEGIN_INLINE_EVENT
        WAIT_MS(6000)
        CALL(evt_telop_entry, 13)
    END_INLINE_EVENT
    WAIT_MS(4000)
    CALL(evt_cam3d_evt_set, 200, 150, 1001, -40, 130, 348, 6000, 11)
    WAIT_MS(6000)
    CALL(evt_mario_normalize)
    CALL(evt_mario_mov_pos2, -351, 0, FLOAT(120.0f))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, -380, 97, 267, -380, 38, -9, 0, 11)
    WAIT_MS(300)
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_party_stop, 0)
    WAIT_MS(200)
    IF_INT_EQUAL(GSWF(3885), 1)
        CALL(evt_msg_print_party, STRING(((char*)str_00000220)))
        ELSE
        CALL(evt_msg_print_party, STRING(((char*)str_00000234)))
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000244)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_0000025C)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSW(0), 353)
    CALL(N_evt_bero_set_mario_bottomless_respawn_pos_to_current_mario_pos)
    SET_VALUE(LW(0), STRING(((char*)str_000001F8)))
    CALL_CHILD(PTR(bero_case_switch_on))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_snd_bgm_scope, 0, 0)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_bom_01_karakara)
    SET_VALUE(LW(9), LW(0))
    SET_VALUE(LW(8), 0)
    LOOP(0)
        CALL(evt_mapobj_get_position, LW(9), LW(0), LW(1), LW(2))
        CALL(evt_sub_intpl_msec_init, 12, 1, 10, 1000)
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        SUBTRACT(LW(8), LW(0))
        IF_INT_LESS(LW(8), 0)
            ADD(LW(8), 360)
        END_IF
        CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(8), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        CALL(evt_sub_random, 10, LW(5))
        ADD(LW(5), 1)
        MULTIPLY(LW(5), 30)
        LOOP(LW(5))
            SUBTRACT(LW(8), LW(0))
            IF_INT_LESS(LW(8), 0)
                ADD(LW(8), 360)
            END_IF
            CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(8), 0)
            WAIT_FRAMES(1)
        END_LOOP
        BEGIN_INLINE_EVENT
            WAIT_MS(900)
        END_INLINE_EVENT
        CALL(evt_sub_intpl_msec_init, 12, 10, 1, 1000)
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        SUBTRACT(LW(8), LW(0))
        IF_INT_LESS(LW(8), 0)
            ADD(LW(8), 360)
        END_IF
        CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(8), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
    END_LOOP
    RETURN
EVT_END()

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static void ext_init(void) {
    s32 i;
    BomWork* wp;
    ExtPose* pose;
    f32 angle;
    f32 dist;
    f32 sv;

    lp = smartAlloc(sizeof(BomWork), 1);
    wp = lp->address;
    memset(wp, 0, sizeof(BomWork));
    wp->count = extGetPoseNum();
    pose_init();

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
        wp->bom[i].vy = 0.0f;
        wp->bom[i].gravity = 0.0f;
        wp->bom[i].state = 0;
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        angle = 6.2831855f * rand() / 32767.0f;
        dist = 500.0f + 400.0f * rand() / 32767.0f;
        sv = chb_sin(angle);
        pose->mtx[0][3] = dist * sv;
        pose->mtx[1][3] = 0.0f;
        sv = chb_cos(angle);
        pose->mtx[2][3] = dist * sv;
        pose_change(i, "R_1");
    }
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
static void ext_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}
#endif

#ifdef NONMATCHING
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr() + i;
    f32 dy;
    f32 dist;

    wp->bom[i].target = (Vec){x, y, z};
    wp->bom[i].field_0x10 = speed;
    wp->bom[i].gravity = gravity;
    dy = y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], x, z);
    angleABf(pose->mtx[0][3], pose->mtx[2][3], x, z);
    wp->bom[i].timer = dist / wp->bom[i].field_0x10;
    wp->bom[i].vy = dy / wp->bom[i].timer + wp->bom[i].gravity * wp->bom[i].timer / 2;
    wp->bom[i].next = next;
    wp->bom[i].state = 100;
    pose->rot = angleABf(x, z, pose->mtx[0][3], pose->mtx[2][3]);
    if (i % 20 == 0 && !(wp->flags & 1)) {
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        psndSFXOn_3D("SFX_STG7_BOMB_TOGETHER2", &pos);
    }
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static void ext_main(void) {
    
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr();
    s32 i;
    f32 angle;
    f32  speed;
    f32 gravity; f32 new_var2 ;
    f32 x;
    f32 z; f32 dist ;
    f32 rad;
    Mtx m1;
    Mtx m2;
    Mtx m3;
    const char* se = "SFX_STG7_BOMB_FALL1";

    for (i = 0; i < wp->count; i++, pose++) {
        Vec center = {0.0f, 0.0f, 0.0f};
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        Vec dir; Vec move = {0.0f, 0.0f, 0.0f};

        switch ((s8)wp->bom[i].state) {
            case 0:
                new_var2 = PSVECDistance(&center, &pos) ; if (new_var2 > 280.0f) {
                    PSVECSubtract(&center, &pos, &dir);
                    PSVECNormalize(&dir, &dir);
                    PSVECScale(&dir, &move, 3.0f);
                    PSVECAdd(&pos, &move, &pos);
                    pose->mtx[0][3] = pos.x;
                    pose->mtx[1][3] = pos.y;
                    pose->mtx[2][3] = pos.z;
                    pose->rot = angleABf(0.0f, 0.0f, pos.x, pos.z);
                } else {
                    wp->bom[i].state++;
                }
                break;
            case 1:
                angle = ( 6.2831855f * rand() ) / 32767.0f;
                dist = 150.0f + (( 30.0f * rand() ) / 32767.0f) ;
                gravity = 0.1f + (( 0.1f * rand() ) / 32767.0f) ;
                speed = 3.0f + ( rand() / 32767.0f) ;
                z = dist * ( -chb_cos(angle) );
                x = dist * chb_sin(angle);
                jump(i, 2, x, 150.0f, z, speed, gravity);
                break;
            case 2:
                angle = ( 6.2831855f * rand() ) / 32767.0f;
                dist = 50.0f + (( 30.0f * rand() ) / 32767.0f) ;
                x = ( 0.1f * rand() ) / 32767.0f; gravity = 0.1f + x ;
                speed = 3.0f + ( rand() / 32767.0f) ;
                z = dist * ( -chb_cos(angle) );
                x = dist * chb_sin(angle);
                jump(i, 3, x, 400.0f, z, speed, gravity);
                break;
            case 3:
                angle = ( 6.2831855f * rand() ) / 32767.0f;
                dist = ( 70.0f * rand() ) / 32767.0f;
                gravity =  0.1f + (( 0.0f * rand() ) / gravity); gravity = 32767.0f ; speed = rand () ;
                speed = 3.0f + (( 0.0f * speed) / 32767.0f) ;
                z = dist * ( -chb_cos(angle)) ;
                x = ( dist * chb_sin(angle) ) + (100.0f + ( i % 100) );
                jump(i, 4, x, 350.0f + ( i % 150) , z, speed, gravity);
                break;
            case 4:
                wp->bom[i].state++;
                break;
            case 5:
                break;
            case 100:
                pose->mtx[1][3] += wp->bom[i].vy;
                wp->bom[i].vy -= wp->bom[i].gravity;
                rad = ( 3.1415927f * angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->bom[i].target.x, wp->bom[i].target.z) ) / 180.0f;
                pose->mtx[0][3] += wp->bom[i].field_0x10 * chb_sin(rad);
                pose->mtx[2][3] += wp->bom[i].field_0x10 * ( -chb_cos(rad)) ;
                if ( (--wp->bom[i].timer ) < 0) {
                    pose->mtx[0][3] = wp->bom[i].target.x;
                    pose->mtx[1][3] = wp->bom[i].target.y;
                    pose->mtx[2][3] = wp->bom[i].target.z;
                    wp->bom[i].state = wp->bom[i].next;
                }
                break;
            case 127:
                if (pose->mtx[2][3] > ( -1000.0f) ) {
                    pose->mtx[1][3] = pose->mtx[1][3] - 2.0f;
                    pose->flags &= ~2;
                    PSMTXTrans(m1, 0.0f, -20.0f, 0.0f);
                    PSMTXRotRad(m2, 'z', 0.017453292f * (10.0f * (( f32)sin((gp->retraceCount + i) / 100.0f) )));
                    PSMTXTrans(m3, 0.0f, 20.0f, 0.0f);
                    PSMTXConcat(m1, m2, m2);
                    PSMTXConcat(m2, m3, m3);
                    PSMTXTrans(m1, pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]);
                    PSMTXConcat(m1, m3, pose->mtx);
                    if (irand(100) == 0) {
                        Vec p = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                        psndSFXOn_3D(se, &p);
                    }
                }
                break;
        }
    }
    pose_main();
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
static void ext_dispent(void) {
    BomWork* wp = lp->address;

    if (!(wp->flags & 1)) {
        dispEntry(CAMERA_3D, 0.0f, 1, ext_disp, NULL);
    }
}
#endif

static s32 ext_data[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_bom1000)
    CALL(make_ext_table)
    CALL(evt_npc_entry, STRING(((char*)str_000002AC)), STRING(((char*)str_000002B4)))
    CALL(evt_ext_entry, 1000, PTR(ext_data), PTR(ext_init), PTR(ext_main), PTR(ext_dispent))
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(gamen_shake)
    CALL(evt_cam_shake, 4, FLOAT(0.001953125f), FLOAT(0.0f), 0)
    RETURN
EVT_END()

EVT_BEGIN(gamen_shake2)
    CALL(evt_cam_shake, 4, FLOAT(0.01953125f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.009765625f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.0048828125f), FLOAT(0.0f), 100)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 100)
    RETURN
EVT_END()

EVT_BEGIN(mario_tobideru)
    CALL(evt_mario_set_pos, 400, 780, 0)
    CALL(evt_sub_intpl_msec_init, 2, 0, 400, 300)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(LW(2), 400)
    SET_VALUE(LW(3), 780)
    ADD(LW(2), LW(0))
    ADD(LW(3), LW(0))
    CALL(evt_mario_set_pos, LW(2), LW(3), 0)
    SUBTRACT(LW(2), 30)
    SUBTRACT(LW(3), 30)
    CALL(evt_party_set_pos, 0, LW(2), LW(3), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(mario_shot)
    SPAWN_EVENT(PTR(mario_tobideru))
    CALL(evt_snd_sfxon, STRING(((char*)str_000002C0)), 0)
    CALL(evt_sub_intpl_msec_init, 2, 0, -50, 150)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000002DC)), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SPAWN_EVENT(PTR(gamen_shake2))
    CALL(evt_eff, STRING(((char*)str_000002E4)), STRING(((char*)str_000002EC)), 11, 570, 950, 0, FLOAT(3.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff64, STRING(((char*)str_000002F8)), STRING(((char*)str_00000300)), 2, 570, 950, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff, STRING(((char*)str_0000030C)), STRING(((char*)str_0000030C)), 0, 520, 900, 0, 1, 1, 0, 100, 0, 0, 0, 0)
    CALL(taihou_r)
    BEGIN_INLINE_EVENT
        CALL(evt_eff, 0, STRING(((char*)str_00000318)), 1, 570, 950, 0, FLOAT(3.0f), 4, 0, 0, 0, 0, 0, 0)
        WAIT_MS(200)
        CALL(evt_eff, 0, STRING(((char*)str_00000318)), 1, 570, 950, 0, FLOAT(3.0f), 4, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 5, -50, 0, 150)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, -40)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000002DC)), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(effect_delete)
    CALL(evt_eff_delete, STRING(((char*)str_000002E4)))
    CALL(evt_eff_delete, STRING(((char*)str_000002F8)))
    CALL(evt_eff_delete, STRING(((char*)str_0000030C)))
    RETURN
EVT_END()

static EVT_BEGIN(mario_kemuri)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 12, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        WAIT_FRAMES(2)
    END_LOOP
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(evt_depth)
    CALL(depth)
    RETURN
EVT_END()

EVT_BEGIN(cam_outside)
    CALL(evt_map_set_blend, 0, 255, 255, 255, 255)
    CALL(evt_map_set_blend, 1, 255, 255, 255, 255)
    CALL(evt_map_blend_off, 0)
    CALL(evt_map_blend_off, 1)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001A0)), 1)
    RETURN
EVT_END()

EVT_BEGIN(cam_inside)
    CALL(evt_cam3d_evt_set, -160, 125, -100, 10, 55, -427, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 0)
    CALL(evt_map_set_blend, 1, 0, 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001A0)), 1)
    RETURN
EVT_END()

EVT_BEGIN(cam_inside2)
    CALL(evt_cam3d_evt_set, -93, 104, -250, 9, 62, -447, 0, 11)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 0)
    CALL(evt_map_set_blend, 1, 0, 0, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000194)), 90, 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000001A0)), 0, -90, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001A0)), 1)
    RETURN
EVT_END()

static EVT_BEGIN(party_damage_pose)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000031C)))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000324)))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_0000032C)))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000330)))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000338)))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000340)))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING(((char*)str_00000348)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(effect_1)
    SET_VALUE(LW(0), -220)
    LOOP(22)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, LW(0), 5, -220, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, LW(0), 5, 220, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        ADD(LW(0), 20)
    END_LOOP
    SET_VALUE(LW(0), -220)
    LOOP(22)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, -220, 5, LW(0), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff, 0, STRING(((char*)str_000002EC)), 2, 220, 5, LW(0), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        ADD(LW(0), 20)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(open_hatch)
    CALL(evt_mapobj_get_position, LW(1), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000350)), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(9), LW(1))
    SET_VALUE(LW(7), LW(2))
    CALL(evt_sub_intpl_msec_init, 1, 0, 180, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    IF_INT_EQUAL(LW(7), 0)
        CALL(evt_mapobj_trans, 1, LW(9), 0, 0, LW(0))
        MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
        CALL(evt_mapobj_trans, 1, LW(8), 0, 0, LW(0))
        ELSE
        CALL(evt_mapobj_trans, 1, LW(9), LW(0), 0, 0)
        MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
        CALL(evt_mapobj_trans, 1, LW(8), LW(0), 0, 0)
    END_IF
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SPAWN_EVENT(PTR(gamen_shake2))
    RETURN
EVT_END()

__declspec(section ".data") static s32 spline_dt[] = {
    -1018691584, 0, 1143111680, 1142128640, 1128792064, -989437952, 1152155648, 1120403456,
    -979718144,
};

__declspec(section ".data") s32 oh_data[] = {
    (s32)/*((char*)str_00000368)*/((char*)str_00000368), (s32)((char*)str_00000370), (s32)/*((char*)str_000001B8)*/((char*)str_000001B8), (s32)((char*)str_00000380), (s32)/*((char*)str_000001C8)*/((char*)str_000001C8), (s32)((char*)str_00000390), (s32)/*((char*)str_000003A0)*/((char*)str_000003A0), (s32)((char*)str_000003AC),
};

static EVT_BEGIN(evt_taihou)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_msg_print, 0, STRING(((char*)str_000003BC)), 0, STRING(((char*)str_000003C8)))
    WAIT_MS(300)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000003C8)), 32)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos, 0, 10, 0, 500)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, 0, 10, 500)
    CALL(evt_cam3d_evt_set, 0, 152, 555, 0, 57, 13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003D8)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003E4)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003EC)), 1)
    CALL(evt_party_stop, 0)
    CALL(evt_mario_dispflag_onoff, 1, 2)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000003F4)), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000410)))
    CALL_CHILD(PTR(party_damage_pose))
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000418)), LW(10), LW(11), LW(12), LW(9))
    CALL(evt_sub_intpl_msec_init, 12, 0, 20, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), LW(0), -5, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), LW(0), -5, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_snd_sfxoff, LW(9))
    WAIT_MS(800)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000450)), LW(3), LW(4), LW(5), LW(6))
    CALL(evt_sub_intpl_msec_init, 1, 0, -100, 400)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_mario_set_pos, LW(3), LW(0), LW(5))
    CALL(evt_snd_sfx_pos, LW(6), LW(3), LW(0), LW(5))
    CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_party_set_pos, 0, LW(3), LW(0), LW(5))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_mario_set_pos, 0, -500, 0)
    CALL(evt_party_set_pos, 0, 0, -500, 0)
    CALL(evt_snd_sfxoff, LW(6))
    CALL(evt_mario_cont_onoff, 1)
    WAIT_FRAMES(1)
    CALL(evt_mario_set_pose, STRING(((char*)str_00000410)))
    WAIT_FRAMES(1)
    CALL(evt_mario_cont_onoff, 0)
    DEBUG_PUT_MSG(STRING(((char*)str_00000468)))
    CALL(L_evt_party_vivian_tail, 0, 0)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000003C8)), 2)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -50, -40, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -55, -30, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), -45, 80, 0, FLOAT(80.0f), 1)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000003C8)), 0, 275, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING(((char*)str_000003C8)), STRING(((char*)str_0000047C)))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_cam3d_evt_set, 0, 230, 994, 0, 80, 259, 1000, 11)
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000003C8)), 32768)
    CALL(evt_npc_set_ry, STRING(((char*)str_000003C8)), 90)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000484)), 0, STRING(((char*)str_000003C8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000490)), 0, STRING(((char*)str_000001AC)))
    SET_INT_READ_ADDR(PTR(oh_data))
    LOOP(4)
        READ_INT2(LW(0), LW(1))
        BEGIN_INLINE_EVENT
            CALL(evt_set_dir_to_target, LW(0), STRING(((char*)str_0000047C)))
            CALL(evt_msg_print, 0, LW(1), 0, LW(0))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_npc_get_position, LW(0), LW(10), LW(11), LW(12))
            CALL(evt_npc_jump_position_nohit, LW(0), LW(10), LW(11), LW(12), 300, FLOAT(20.0f))
        END_INLINE_EVENT
        WAIT_MS(300)
    END_LOOP
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_000004A0)), 0, STRING(((char*)str_000003C8)))
    SET_VALUE(GF(0), 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_000001C8)), 512)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001AC)))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING(((char*)str_000001AC)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001B8)))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING(((char*)str_000001B8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001B8)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_get_position, STRING(((char*)str_000001C8)), LW(0), LW(1), LW(2))
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001C8)), LW(0), LW(1), LW(2), 300, FLOAT(20.0f))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING(((char*)str_000004AC)), 0, STRING(((char*)str_000001C8)))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(1000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GF(0), 0)
    SET_VALUE(GF(1), 0)
    SET_VALUE(GF(2), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001AC)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -50, -80, 0, FLOAT(100.0f), 1)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001B8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 0, -80, 0, FLOAT(100.0f), 1)
        SET_VALUE(GF(1), 1)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000001C8)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 50, -80, 0, FLOAT(100.0f), 1)
        SET_VALUE(GF(2), 1)
    END_INLINE_EVENT
    LABEL(2)
    IF_INT_EQUAL(GF(0), 0)
        WAIT_FRAMES(1)
        GOTO(2)
    END_IF
    IF_INT_EQUAL(GF(1), 0)
        WAIT_FRAMES(1)
        GOTO(2)
    END_IF
    IF_INT_EQUAL(GF(2), 0)
        WAIT_FRAMES(1)
        GOTO(2)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001AC)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001B8)), 512)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_000001C8)), 512)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -50, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), -35, -260, 0, FLOAT(80.0f), 1)
    END_INLINE_EVENT
    WAIT_MS(400)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), -50, -80, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), -55, -225, 0, FLOAT(80.0f), 1)
    END_INLINE_EVENT
    WAIT_MS(400)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), -50, -80, 0, FLOAT(80.0f), 1)
    CALL(evt_cam3d_evt_set, 0, 152, 108, 0, 57, -432, 0, 11)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), -70, -180, 0, FLOAT(80.0f), 1)
    END_INLINE_EVENT
    SET_VALUE(GF(0), 0)
    SET_VALUE(LW(0), PTR(door))
    SPAWN_EVENT(PTR(evt_door_open_bom_01))
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 0, -320, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 35, -330, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 80, -380, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), 70, 30, -435, 300, FLOAT(20.0f))
        CALL(evt_npc_move_position, STRING(((char*)str_000001AC)), 40, -445, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001AC)), 0, 40, -430, 300, FLOAT(20.0f))
        CALL(evt_npc_set_ry, STRING(((char*)str_000001AC)), 90)
    END_INLINE_EVENT
    WAIT_MS(400)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 0, -320, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 35, -330, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 80, -380, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 80, -415, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_move_position, STRING(((char*)str_000001B8)), 45, -415, 0, FLOAT(70.0f), 1)
        CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001B8)), -20, 15, -390, 300, FLOAT(20.0f))
        CALL(evt_npc_set_ry, STRING(((char*)str_000001B8)), 315)
    END_INLINE_EVENT
    WAIT_MS(400)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 0, -320, 0, FLOAT(70.0f), 1)
    SET_VALUE(GF(0), 0)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 35, -330, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 80, -380, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 80, -415, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_move_position, STRING(((char*)str_000001C8)), 45, -415, 0, FLOAT(70.0f), 1)
    CALL(evt_npc_jump_position_nohit, STRING(((char*)str_000001C8)), 20, 15, -390, 300, FLOAT(20.0f))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001C8)), 90)
    CALL(evt_cam3d_evt_set, -160, 125, -100, 10, 55, -427, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001AC)), STRING(((char*)str_000001B8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000004B8)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001B8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_000004C4)), 0, STRING(((char*)str_000001B8)))
    WAIT_MS(300)
    CALL(evt_npc_reverse_ry, STRING(((char*)str_000001B8)))
    CALL(evt_snd_sfxon, STRING(((char*)str_000004D0)), 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL(evt_map_playanim, STRING(((char*)str_00000508)), 1, 0)
    WAIT_MS(1000)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001B8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000510)), 0, STRING(((char*)str_000001B8)))
    CALL(evt_npc_set_ry, STRING(((char*)str_000001B8)), 315)
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001AC)), STRING(((char*)str_000001C8)))
    CALL(evt_msg_print, 0, STRING(((char*)str_0000051C)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_set_dir_to_target, STRING(((char*)str_000001C8)), STRING(((char*)str_000001AC)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000528)), 0, STRING(((char*)str_000001C8)))
    WAIT_MS(300)
    CALL(evt_npc_reverse_ry, STRING(((char*)str_000001C8)))
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, 200, 350, 1224, 200, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    CALL(evt_snd_sfxon, STRING(((char*)str_00000534)), LW(10))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 1, 0, 0, 0)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000054C)), 0, STRING(((char*)str_000001AC)))
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 0, 350, 1224, 0, 125, 250, 6000, 11)
    WAIT_MS(6000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000558)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000564)))
    CALL(evt_cam3d_evt_set, 0, 350, 1224, 0, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 0, 283, 932, 0, 125, 250, 3000, 11)
    WAIT_MS(1500)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000057C)), LW(7))
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    WAIT_MS(1500)
    SPAWN_EVENT(PTR(effect_1))
    CALL(evt_snd_sfxon, STRING(((char*)str_00000594)), 0)
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000005AC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003CC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000005B4)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000003CC)), 0, FLOAT(0.0f), 0)
    CALL(evt_snd_sfxon, STRING(((char*)str_000005C0)), LW(8))
    CALL(evt_sub_intpl_msec_init, 0, 0, -20, 1000)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005D8)), 0, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005E8)), 0, LW(0), 0)
    ADD(LW(0), -5)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), -20, LW(0), 0)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), 20, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_snd_sfxon, STRING(((char*)str_000005F8)), LW(8))
    CALL(evt_sub_intpl_msec_init, 0, 0, 170, 3000)
    LABEL(4)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005E8)), LW(0), -20, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000005D8)), LW(0), -20, 0)
    ADD(LW(0), -20)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000440)), LW(0), -25, 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000430)), LW(0), -25, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(4)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(600)
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxoff, LW(7))
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 100)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000610)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, 0, 283, 932, 0, 125, 250, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, -200, 734, 684, -10, 50, 63, 2800, 11)
    WAIT_MS(1800)
    SET_VALUE(LW(0), STRING(((char*)str_0000061C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000062C)))
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
    SET_VALUE(LW(0), STRING(((char*)str_0000063C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000064C)))
    SET_VALUE(LW(2), 1)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
    SET_VALUE(LW(0), STRING(((char*)str_0000065C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000066C)))
    SET_VALUE(LW(2), 0)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
    SET_VALUE(LW(0), STRING(((char*)str_0000067C)))
    SET_VALUE(LW(1), STRING(((char*)str_0000068C)))
    SET_VALUE(LW(2), 1)
    SPAWN_EVENT(PTR(open_hatch))
    WAIT_MS(400)
    WAIT_MS(1000)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
    CALL_CHILD(PTR(cam_inside2))
    WAIT_MS(300)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000069C)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, -230, 734, 684, -10, 50, 63, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    SET_VALUE(LW(0), 0)
    LOOP(36)
        ADD(LW(0), 1)
        CALL(make_name, LW(0), LW(1))
        CALL(evt_mapobj_flag_onoff, 1, 0, LW(1), 1)
        WAIT_MS(100)
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(4000)
        CALL(evt_cam3d_evt_set, -543, 200, 1194, -16, 175, 60, 3000, 11)
        WAIT_MS(5500)
        CALL(evt_cam3d_evt_set, 0, 70, 650, 0, 60, 250, 0, 11)
    END_INLINE_EVENT
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    CALL(evt_snd_sfxon, STRING(((char*)str_000006A8)), LW(8))
    CALL(evt_sub_intpl_msec_init, 1, 0, 1600, 11250)
    LABEL(5)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000006BC)), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(5)
    END_IF
    SPAWN_EVENT(PTR(effect_1))
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_snd_sfxon, STRING(((char*)str_000006C8)), 0)
    DELETE_EVENT(LW(9))
    SPAWN_EVENT(PTR(gamen_shake2))
    WAIT_MS(2000)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000005B4)), 1)
    CALL(evt_cam3d_evt_set, 1500, 100, 2539, 0, 650, 0, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, -1500, 100, 2539, 0, 650, 0, 5000, 11)
    WAIT_MS(5000)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_000006E0)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    SET_VALUE(GW(5), 70)
    SPAWN_EVENT_GET_ID(PTR(evt_depth), LW(9))
    CALL(sight_dir, 3)
    CALL_CHILD(PTR(cam_outside))
    CALL(evt_cam3d_evt_set, 400, 151, -171, 400, 62, -676, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_set, 420, 151, -171, 420, 62, -676, 2000, 11)
    WAIT_MS(2000)
    CALL(sight_dir, 2)
    CALL(evt_cam3d_evt_set, 400, 151, -171, 400, 62, -676, 2000, 11)
    WAIT_MS(2000)
    CALL(sight_dir, 5)
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, -1500, 100, 2539, 0, 650, 0, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000006EC)), LW(8))
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    CALL(evt_sub_intpl_msec_init, 11, 0, -500, 3000)
    LABEL(6)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(6)
    END_IF
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxon, STRING(((char*)str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 500)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(8))
    SET_VALUE(GW(10), 70)
    SPAWN_EVENT_GET_ID(PTR(evt_depth), LW(9))
    CALL(sight_dir, 4)
    CALL_CHILD(PTR(cam_outside))
    CALL(evt_cam3d_evt_set, 400, 151, -171, 400, 62, -676, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(300)
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000071C)), 0, 0)
    WAIT_MS(300)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000728)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_00000728)), 400, -738, -676)
    CALL(evt_mapobj_scale, 1, STRING(((char*)str_00000728)), FLOAT(0.7998047f), FLOAT(0.7998047f), FLOAT(0.7998047f))
    CALL(sight_dir, 0)
    CALL(evt_cam3d_evt_set, 400, 151, -171, 400, 262, -676, 2000, 11)
    WAIT_MS(2000)
    CALL(sight_dir, 4)
    CALL(evt_sub_intpl_msec_init, 11, 70, 0, 1000)
    LABEL(100)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(GW(5), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(100)
    END_IF
    DELETE_EVENT(LW(9))
    WAIT_MS(2000)
    CALL(sight_dir, 6)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000728)), 1)
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000730)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, -1500, 100, 2539, 0, 650, 0, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_000006EC)), LW(8))
    SPAWN_EVENT_GET_ID(PTR(gamen_shake), LW(9))
    CALL(evt_sub_intpl_msec_init, 11, -500, -400, 1000)
    LABEL(7)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_000002DC)), 0, 0, LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(7)
    END_IF
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxon, STRING(((char*)str_00000704)), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0f), 500)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_0000073C)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_00000748)), LW(8))
    CALL(evt_sub_intpl_msec_init, 11, 0, -1200, 1000)
    LABEL(8)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000760)), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(8)
    END_IF
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, 21, 175, 781, 9, 42, 265, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000768)), 0, STRING(((char*)str_00000774)))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000077C)), LW(8))
    CALL_CHILD(PTR(evt_bom1000))
    WAIT_MS(5000)
    CALL(evt_snd_sfxoff, LW(8))
    CALL(evt_cam3d_evt_set, -120, 697, 788, 39, 556, 265, 0, 11)
    WAIT_MS(5000)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL(bom_flag, 1, 1)
    CALL_CHILD(PTR(cam_inside2))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000794)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(bom_flag, 0, 1)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, -120, 697, 788, 39, 556, 265, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_FRAMES(1)
    CALL(evt_snd_sfxon, STRING(((char*)str_000007A0)), LW(7))
    CALL(evt_msg_toge, 2, 180, 520, 100)
    CALL(evt_msg_print, 0, STRING(((char*)str_000007BC)), 0, 0)
    CALL(evt_msg_toge, 2, 100, 400, 95)
    CALL(evt_msg_print, 0, STRING(((char*)str_000007CC)), 0, 0)
    CALL(evt_msg_toge, 2, 10, 475, 75)
    CALL(evt_msg_print, 0, STRING(((char*)str_000007DC)), 0, 0)
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_sfxon, STRING(((char*)str_000007EC)), LW(8))
        CALL(evt_sub_intpl_msec_init, 11, -1200, 0, 3000)
        LABEL(9)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000760)), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(9)
        END_IF
        CALL(evt_snd_sfxoff, LW(8))
        CALL(evt_snd_sfxoff, LW(7))
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_msg_toge, 2, 180, 520, 100)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000804)), 0, 0)
    CALL(evt_msg_toge, 2, 100, 400, 95)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000814)), 0, 0)
    CALL(evt_msg_toge, 2, 10, 475, 75)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000824)), 0, 0)
    WAIT_MS(300)
    CALL(evt_npc_reverse_ry, STRING(((char*)str_00000774)))
    CALL(bom_flag, 1, 1)
    CALL(evt_snd_sfxon, STRING(((char*)str_000004EC)), LW(10))
    CALL_CHILD(PTR(cam_inside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000834)), 0, STRING(((char*)str_000001AC)))
    WAIT_MS(300)
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_cam3d_evt_set, 21, 175, 781, 9, 42, 265, 0, 11)
    CALL_CHILD(PTR(cam_outside))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000840)), 0, STRING(((char*)str_00000774)))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_set, 200, 0, 2483, 200, 550, 0, 0, 11)
    SPAWN_EVENT(PTR(mario_shot))
    WAIT_MS(800)
    CALL_CHILD(PTR(effect_delete))
    CALL(evt_cam3d_evt_set, 806, 1189, 451, 600, 982, 69, 0, 11)
    SPAWN_EVENT(PTR(mario_shot))
    WAIT_MS(800)
    CALL_CHILD(PTR(effect_delete))
    CALL(evt_cam3d_evt_set, -605, 170, 785, -25, 334, 227, 0, 11)
    SPAWN_EVENT(PTR(mario_shot))
    WAIT_MS(800)
    CALL_CHILD(PTR(effect_delete))
    SPAWN_EVENT_GET_ID(PTR(mario_kemuri), LW(9))
    CALL(evt_mario_set_pos, 200, 0, -650)
    CALL(evt_party_set_pos, 0, 200, 0, -650)
    CALL(evt_cam3d_evt_set, 370, 245, -173, 370, 62, -1205, 0, 11)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000084C)), 1)
    WAIT_FRAMES(1)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000854)), 200, 0, -650, 0)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000870)), 200, 0, -650, LW(4))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000888)), 200, 0, -650, LW(5))
    SET_FLOAT_VALUE(LW(6), FLOAT(0.0f))
    CALL(evt_sub_spline_init, 1, 11, PTR(spline_dt), 3, 0, 2000)
    LABEL(20)
    CALL(evt_sub_spline_get_value, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfx_pos, LW(4), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfx_pos, LW(5), LW(0), LW(1), LW(2))
    ADD(LW(0), -20)
    ADD(LW(1), -20)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(3), 1)
        GOTO(20)
    END_IF
    DELETE_EVENT(LW(9))
    CALL(evt_snd_sfxoff, LW(5))
    WAIT_FRAMES(1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    WAIT_MS(1000)
    WAIT_MS(500)
    CALL(evt_snd_sfxon, STRING(((char*)str_0000089C)), 0)
    CALL(evt_eff64, 0, STRING(((char*)str_000008B4)), 0, LW(0), LW(1), LW(2), 60, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(2000)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_msg_toge, 2, 340, 200, -590)
        CALL(evt_msg_print, 0, STRING(((char*)str_000008C4)), 0, 0)
        CALL(evt_msg_toge, 2, 400, 160, -590)
        CALL(evt_msg_print, 0, STRING(((char*)str_000008D0)), 0, 0)
        CALL(evt_msg_toge, 2, 373, 135, -590)
        CALL(evt_msg_print, 0, STRING(((char*)str_000008DC)), 0, 0)
    END_INLINE_EVENT
    CALL(bom_flag, 0, 1)
    CALL(bom_fall)
    WAIT_MS(6000)
    CALL(evt_ext_reset)
    CALL(evt_npc_set_ry, STRING(((char*)str_00000774)), 90)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000774)), 32768)
    CALL(evt_cam3d_evt_set, -60, 26, 493, 22, 33, 257, 0, 11)
    WAIT_MS(2000)
    CALL(evt_msg_print, 0, STRING(((char*)str_000008E8)), 0, STRING(((char*)str_00000774)))
    CALL(evt_snd_bgmoff_f, 512, 2000)
    WAIT_MS(300)
    WAIT_MS(2000)
    CALL(evt_pouch_remove_item, 82, LW(0))
    CALL(evt_bero_mapchange, STRING(((char*)str_000008F4)), 0)
    RETURN
EVT_END()

static EVT_BEGIN(init_soncho)
    SWITCH(GSW(0))
        CASE_GREATER_OR_EQUAL(356)
        CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -15, 0, -35)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_soncho)
    SWITCH(GSW(0))
        CASE_LESS(357)
        CALL_CHILD(PTR(evt_taihou))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_000008FC)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000910)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_nitoro)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -120, 0, -220)
    RETURN
EVT_END()

EVT_BEGIN(talk_nitoro)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000924)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000934)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000940)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000950)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_0000095C)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_pentrit)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -150, 0, 130)
    RETURN
EVT_END()

EVT_BEGIN(talk_pentrit)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000096C)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING(((char*)str_0000097C)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000988)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000998)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_000009A4)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_surary)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 152, 0, -188)
    RETURN
EVT_END()

EVT_BEGIN(talk_surary)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009B4)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009C4)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009D0)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009E0)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_000009EC)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") EVT_BEGIN(init_murabito_d)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 175, 0, 210)
    RETURN
EVT_END()

EVT_BEGIN(talk_murabito_d)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_000009FC)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A0C)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A18)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A28)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A34)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_e)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -200, 0, -80)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_e)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A44)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A54)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A60)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_f)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -150, 0, -80)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_f)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A6C)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A7C)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A88)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_g)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -100, 0, -80)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_g)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000A94)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AA4)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AB0)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_h)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), -50, 0, -80)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_h)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000ABC)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000ACC)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AD8)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(init_murabito_i)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 0, 0, -80)
    RETURN
EVT_END()

static EVT_BEGIN(talk_murabito_i)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AE4)), 0, STRING(((char*)str_000003C8)))
        CASE_LESS(357)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000AF4)), 0, STRING(((char*)str_000003C8)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B00)), 0, STRING(((char*)str_000003C8)))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(init_white)
    IF_INT_EQUAL(GSW(1420), 25)
        IF_INT_EQUAL(GSWF(5411), 0)
            RETURN
        END_IF
    END_IF
END_IF
IF_INT_EQUAL(GSWF(3876), 1)
    CALL(evt_npc_set_position, STRING(((char*)str_000003C8)), 50, 0, -100)
END_IF
RETURN
EVT_END()

static EVT_BEGIN(talk_white)
    SWITCH(GSW(0))
        CASE_LESS(357)
        IF_INT_EQUAL(GSWF(3874), 0)
            CALL(evt_msg_print, 0, STRING(((char*)str_00000B0C)), 0, 0)
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)str_00000B1C)), 0, 0)
        END_IF
        CASE_LESS_OR_EQUAL(402)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B2C)), 0, 0)
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B3C)), 0, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(musume_talk)
    SWITCH(GSW(0))
        CASE_LESS(354)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B4C)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B6C)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000B8C)), 0, STRING(((char*)str_00000BA0)))
        CASE_LESS(356)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BAC)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BC0)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BD4)), 0, STRING(((char*)str_00000BA0)))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BE8)), 0, STRING(((char*)str_00000B60)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000BFC)), 0, STRING(((char*)str_00000B80)))
        CALL(evt_msg_print, 0, STRING(((char*)str_00000C10)), 0, STRING(((char*)str_00000BA0)))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(musume_a_entry)
    CALL(evt_npc_entry, STRING(((char*)str_00000B60)), STRING(((char*)str_00000C24)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000B60)), STRING(((char*)str_00000C30)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000B60)), 370, 5, -120)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000B60)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000B60)), 6, PTR(musume_talk))
    RETURN
EVT_END()

static EVT_BEGIN(musume_b_entry)
    CALL(evt_npc_entry, STRING(((char*)str_00000B80)), STRING(((char*)str_00000C38)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000B80)), STRING(((char*)str_00000C44)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000B80)), 400, 5, -150)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000B80)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000B80)), 6, PTR(musume_talk))
    RETURN
EVT_END()

static EVT_BEGIN(musume_c_entry)
    CALL(evt_npc_entry, STRING(((char*)str_00000BA0)), STRING(((char*)str_00000C54)))
    CALL(evt_npc_set_tribe, STRING(((char*)str_00000BA0)), STRING(((char*)str_00000C60)))
    CALL(evt_npc_set_position, STRING(((char*)str_00000BA0)), 430, 5, -100)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00000BA0)), 1536)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00000BA0)), 6, PTR(musume_talk))
    RETURN
EVT_END()

static s32 npcEnt[] = {
    (s32)/*"村長"*/(char*)str_00000774, 1073743360, 0, (s32)init_soncho, 0, (s32)talk_soncho, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ニトロ"*/(char*)str_00000368,
    1073743360, 0, (s32)init_nitoro, 0, (s32)talk_nitoro, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (s32)/*"ペントリット"*/((char*)str_000001B8), 1073743360,
    0, (s32)init_pentrit, 0, (s32)talk_pentrit, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, (s32)/*"スラリー"*/((char*)str_000001C8), 1073743360, 0,
    (s32)init_surary, 0, (s32)talk_surary, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)/*"ボムヘイD"*/(char*)str_000003A0, 1073743360, 0, (s32)init_murabito_d,
    0, (s32)talk_murabito_d, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, (s32)/*"ホワイト"*/((char*)str_000001AC), 1073743360, 0, (s32)init_white, 0,
    (s32)talk_white, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
};

#ifdef NONMATCHING
s32 taihou_r(EventEntry* event, BOOL isFirstCall) {
    f32 c = cos(0.7853981852531433);
    f32 s = sin(0.7853981852531433);
    f32 x;
    f32 y;
    f32 rx;
    f32 rz;

    x = 100.0f * c;
    rx = -angleABf(0.0f, 0.0f, 0.0f, y = 100.0f * s);
    rz = -angleABf(0.0f, 0.0f, x, y);

    effKemuTestSetRxRz(effNameToPtr("kemuri"), rx, rz);
    effRippleN64SetRxRz(effNameToPtr("ripple"), rx, rz);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static inline f32 dd_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x;
        } else {
            y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a;
    }
    return a;
}
#endif

#ifdef NONMATCHING
static inline f32 dd_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x; a = a * x2 - b; a = a * x2 + c;
        } else {
            y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c;
    }
    return a;
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static void depthDisp(CameraId camera, void* param) {
    f32 amp = evtGetValue(NULL, GW(5)) / 100.0f;
    CameraEntry* cam = camGetPtr(camera);
    smartEntry* buf = smartAlloc(GXGetTexBufferSize(608, 480, GX_TF_RGB565, GX_FALSE, 0), 3);
    GXTexObj obj;
    Mtx mtx;
    f32 a;
    f32 s;
    f32 c;
    s32 i;
    BOOL first;
    GXTevColorArg carg;

    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(608, 480, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(buf->address, GX_FALSE);
    GXPixModeSync();
    GXInitTexObj(&obj, buf->address, 608, 480, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(8);
    GXSetNumTevStages(8);
    for (i = 0; i < 8; i++) {
        a = 6.2831855f * i / 8.0f;
        s = dd_sin(a);
        c = dd_cos(a);
        MTXTrans(mtx, (amp * s) / 100.0f, (amp * c) / 100.0f, 0.0f);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0 + i * 3, GX_MTX2x4);
        GXSetTexCoordGen2((GXTexCoordID)i, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0 + i * 3, GX_FALSE, GX_PTIDENTITY);
        GXSetTevKColorSel((GXTevStageID)i, GX_TEV_KCSEL_1_8);
        GXSetTevKAlphaSel((GXTevStageID)i, GX_TEV_KASEL_1_8);
        GXSetTevOrder((GXTevStageID)i, (GXTexCoordID)i, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        first = !i;
        carg = first ? GX_CC_ZERO : GX_CC_CPREV;
        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST, carg);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, first ? GX_CA_ZERO : GX_CA_APREV);
        GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
    }
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(-304, 240, 0);
    GXTexCoord2s16(0, 0);
    GXPosition3s16(304, 240, 0);
    GXTexCoord2s16(1, 0);
    GXPosition3s16(304, -240, 0);
    GXTexCoord2s16(1, 1);
    GXPosition3s16(-304, -240, 0);
    GXTexCoord2s16(0, 1);
    GXEnd();
    sysWaitDrawSync();
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
static s32 depth(EventEntry* event, BOOL isFirstCall) {
    dispEntry(CAMERA_2D, 1000.0f, 0, depthDisp, NULL);
    return EVT_RETURN_BLOCK;
}
#endif

#ifdef NONMATCHING
static s32 make_name(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    static char name[64];

    sprintf(name, "S_hikari%d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (s32)name);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall) {
    s32 i;

    memset(ext_data, 0, sizeof(ext_data));
    for (i = 0; i < 10; i++) {
        EXT_DATA[i].file = "c_bom_sen";
        EXT_DATA[i].name = "S_1";
        EXT_DATA[i].time = 4.0f * i;
    }
    for (i = 0; i < 20; i++) {
        EXT_DATA[10 + i].file = "c_bom_sen";
        EXT_DATA[10 + i].name = "R_1";
        EXT_DATA[10 + i].time = 2.0f * i;
    }
    EXT_DATA[30].file = NULL;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
void ext_init_minnnanokoe(void) {
    s32 i;
    BomWork* wp;
    ExtPose* pose;
    s32 x;
    s32 z;

    lp = smartAlloc(sizeof(BomWork), 1);
    wp = lp->address;
    memset(wp, 0, sizeof(BomWork));
    wp->count = extGetPoseNum();
    pose_init();

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
        wp->bom[i].vy = 0.0f;
        wp->bom[i].gravity = 0.0f;
        wp->bom[i].state = 5;
        pose->flags |= 3;
        PSMTXIdentity(pose->mtx);
        x = (i % 14) * 30 - 205 + rand() % 10;
        z = 190 - (i / 14) * 20 + rand() % 20;
        pose->mtx[0][3] = x;
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = z;
        pose->rot = 270.0f;
        pose_change(i, "S_1");
    }
}
#endif

#ifdef NONMATCHING
void jump_minnnanokoe(s32 i, f32 h) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr() + i;

    wp->bom[i].target = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
    wp->bom[i].field_0x10 = 0.0f;
    wp->bom[i].gravity = 0.1f;
    wp->bom[i].timer = 20;
    wp->bom[i].vy = wp->bom[i].gravity * wp->bom[i].timer / 2 + h / wp->bom[i].timer;
    wp->bom[i].next = 5;
    wp->bom[i].state = 100;
    if (evtGetValue(NULL, GSW(0)) != 401 && i % 5 == 0) {
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        psndSFXOn_3D("SFX_STG7_BOMB_TOGETHER2", &pos);
    }
}
#endif

#ifdef NONMATCHING
void ext_disp_minnnanokoe(CameraId camera, void* param) {
    YamiParam yp;
    YamiParam* p = &yp;
    ExtPose* pose = extGetPosePtr();
    s32 i;

    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        yp.numTevStages = 1;
        yp.field_0x10 = 1;
        yp.numTexGens = 1;
        yp.numIndStages = 0;
        yp.mtx = pose->mtx;
        envSetYami(p);
        GXSetNumTexGens(yp.numTexGens);
        GXSetNumTevStages(yp.numTevStages);
        GXSetNumIndStages(yp.numIndStages);
        extPoseDraw(i);
    }
    extLoadTextureExit();
}
#endif

#ifdef NONMATCHING
void ext_dispent_minnnanokoe(void) {
    dispEntry(CAMERA_3D, 0.0f, 1, ext_disp_minnnanokoe, NULL);
}
#endif

#ifdef NONMATCHING
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32* fa = args;
    s32 flag;
    s32 type = evtGetValue(event, *fa++);
    s32 idx = evtGetValue(event, *fa++);
    ExtPose* pose = extGetPosePtr();
    ExtPose* p;
    s32 row;
    s32 n;

    if (type == 0) {
        row = 3;
        flag = 1;
    } else {
        row = 10;
        flag = 0;
    }
    n = idx + row * 14;
    idx += (rand() % 2 + 1) * 4;
    idx %= 14;
    p = &pose[n];
    evtSetValue(event, args[0], flag);
    evtSetValue(event, args[1], idx);
    evtSetFloat(event, fa[0], p->mtx[0][3]);
    evtSetFloat(event, fa[1], p->mtx[2][3]);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall) {
    BomWork* wp = lp->address;
    s32 i = rand() % wp->count;

    s32 state = wp->bom[i].state;

    if (state != 100) {
        jump_minnnanokoe(i, 10.0f);
    }
    return EVT_RETURN_DONE;
}
#endif

void envSetYamiView(Mtx mtx);

#ifdef NONMATCHING
static s32 yami_view(EventEntry* event, BOOL isFirstCall) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr_NoAssert(name);

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(npc->poseId, (flag & 0xF) << 24);
    return EVT_RETURN_DONE;
}
#endif

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);

#ifdef NONMATCHING
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    effSetName(effStarStoneEntry(6, x, y, z, 1.0f), name);
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[2] = x;
    ((f32*)eff->userdata)[3] = y;
    ((f32*)eff->userdata)[4] = z;
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);

    ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    return EVT_RETURN_DONE;
}
#endif


EVT_BEGIN(bom1000_minnnanokoe)
    CALL(make_ext_table_minnnanokoe)
    CALL(evt_npc_entry, STRING(((char*)str_000002AC)), STRING(((char*)str_000002B4)))
    CALL(evt_npc_set_position, STRING(((char*)str_000002AC)), 0, -1000, 0)
    CALL(evt_ext_entry, 250, PTR(ext_data), PTR(ext_init_minnnanokoe), PTR(ext_main), PTR(ext_dispent_minnnanokoe))
    RETURN
EVT_END()

static EVT_BEGIN(minnnanokoe_evt)
    SPAWN_EVENT(PTR(bom1000_minnnanokoe))
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000003E4)), 1)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING(((char*)str_00000774)), 520, 0, 0)
    CALL(evt_npc_set_ry, STRING(((char*)str_00000774)), 270)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00000774)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_00000368)), -30, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)str_00000368)), 270)
    CALL(evt_npc_set_position, STRING(((char*)str_000001B8)), 0, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001B8)), 270)
    CALL(evt_npc_set_position, STRING(((char*)str_000001C8)), 30, 0, -180)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001C8)), 90)
    CALL(evt_npc_set_position, STRING(((char*)str_000003A0)), 570, 0, 25)
    CALL(evt_npc_set_ry, STRING(((char*)str_000003A0)), 270)
    CALL(evt_npc_status_onoff, 1, STRING(((char*)str_000003A0)), 2)
    CALL(evt_npc_set_position, STRING(((char*)str_000001AC)), 0, 0, -230)
    CALL(evt_npc_set_ry, STRING(((char*)str_000001AC)), 270)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000CA8)), 16777216)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000CA8)), 256)
    CALL(anim_tevcallback, STRING(((char*)str_00000774)), 1)
    CALL(anim_tevcallback, STRING(((char*)str_00000368)), 1)
    CALL(anim_tevcallback, STRING(((char*)str_000001B8)), 1)
    CALL(anim_tevcallback, STRING(((char*)str_000001C8)), 1)
    CALL(anim_tevcallback, STRING(((char*)str_000003A0)), 1)
    CALL(anim_tevcallback, STRING(((char*)str_000001AC)), 1)
    CALL(yami_view, -1500)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(starstone_entry, STRING(((char*)str_00000CB0)), 0, 50, 10)
    SET_VALUE(GW(0), 50)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(starstone_set_pos, STRING(((char*)str_00000CB0)), 0, GW(0), 10)
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(starstone_set_ry, STRING(((char*)str_00000CB0)), LW(0))
            SUBTRACT_FLOAT(LW(0), FLOAT(3.0f))
            IF_INT_LESS_OR_EQUAL(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 5000, 5500, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 5500, 5000, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(0), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(2)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 400, 106, 331, 400, 45, -13, 0, 11)
    CALL(evt_seq_wait, 2)
    WAIT_MS(500)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING(((char*)str_000003A0)), 450, 25, 0, 90, 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING(((char*)str_00000774)), 400, 0, 0, 90, 0)
    WAIT_FRAMES(1)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000CBC)), 0, STRING(((char*)str_00000774)))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000CCC)), 0, STRING(((char*)str_00000774)))
    CALL(evt_cam3d_evt_set, 0, 283, 1182, 0, 75, 0, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000CDC)), 0, 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(bom1000_jump)
            WAIT_MS(100)
        END_LOOP
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        SET_VALUE(LW(14), 0)
        SET_VALUE(LW(15), 3)
        LOOP(0)
            CALL(bom1000_msg, LW(14), LW(15), LW(0), LW(2))
            CALL(evt_sub_random, 2, LW(1))
            ADD(LW(1), 1)
            MULTIPLY(LW(1), 30)
            CALL(evt_sub_random, 20, LW(3))
            SUBTRACT(LW(3), 10)
            ADD(LW(1), LW(3))
            CALL(evt_msg_toge, 3, LW(0), LW(1), LW(2))
            CALL(evt_sub_random, 2, LW(3))
            SWITCH(LW(3))
                CASE_EQUAL(0)
                SET_VALUE(LW(3), STRING(((char*)str_00000CEC)))
                CASE_EQUAL(1)
                SET_VALUE(LW(3), STRING(((char*)str_00000CFC)))
                CASE_EQUAL(2)
                SET_VALUE(LW(3), STRING(((char*)str_00000D0C)))
            END_SWITCH
            BEGIN_INLINE_EVENT
                CALL(evt_msg_print, 0, LW(3), 0, 0)
            END_INLINE_EVENT
            WAIT_MS(300)
        END_LOOP
    END_SIBLING_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_set, 400, 106, 331, 400, 45, -13, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_npc_set_ry, STRING(((char*)str_00000774)), 90)
    WAIT_MS(300)
    CALL(evt_npc_set_ry, STRING(((char*)str_000003A0)), 90)
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING(((char*)str_000003A0)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00000D1C)), 0, STRING(((char*)str_00000774)))
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, 10, 300, 9, 300)
    CALL(evt_bero_mapchange, STRING(((char*)str_00000D2C)), STRING(((char*)str_00000D34)))
    RETURN
EVT_END()

static EVT_BEGIN(evt_door)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_00000D40)), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(bom_01_init_evt)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    SWITCH(GSW(0))
        CASE_LESS(349)
        CALL_CHILD(PTR(evt_bero_info_run))
        CASE_LESS(353)
        CALL_CHILD(PTR(bero_case_entry))
        CASE_DEFAULT
        CALL_CHILD(PTR(evt_bero_info_run))
    END_SWITCH
    IF_INT_EQUAL(GSW(0), 400)
        SET_VALUE(LF(0), 0)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING(((char*)str_00000D34)))
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000D50)))
            CALL(evt_snd_envoff, 512)
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000D64)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00000D74)))
    END_IF
    SET_VALUE(LW(0), STRING(((char*)str_00000D84)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)str_00000D8C)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)str_00000D94)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)str_00000D9C)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)str_00000DA4)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    SET_VALUE(LW(0), STRING(((char*)str_00000DAC)))
    SPAWN_EVENT(PTR(evt_bom_01_karakara))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003CC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00000DB4)), 1, 0)
    CALL_CHILD(PTR(evt_bom_snowfall))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000728)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000003EC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000005AC)), 1)
    CALL(evt_mapobj_trans, 1, STRING(((char*)str_000003CC)), 0, FLOAT(-1.0f), 0)
    CALL(evt_npc_setup, PTR(npcEnt))
    SWITCH(GSW(0))
        CASE_BETWEEN(352, 357)
        CALL_CHILD(PTR(musume_a_entry))
        CALL_CHILD(PTR(musume_b_entry))
        CALL_CHILD(PTR(musume_c_entry))
    END_SWITCH
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_000001E0)), 0, PTR(evt_door), 0)
    CALL(evt_item_entry, STRING(((char*)str_00000DBC)), 125, -180, 5, 450, 16, GSWF(5659), 0)
    SWITCH(GSW(0))
        CASE_LESS(349)
        SET_VALUE(GSWF(3885), 1)
        CASE_LESS(353)
        SPAWN_EVENT(PTR(first_evt))
    END_SWITCH
    IF_INT_EQUAL(GSW(0), 400)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING(((char*)str_00000D34)))
            SPAWN_EVENT(PTR(minnnanokoe_evt))
        END_IF
    END_IF
    SPAWN_EVENT(PTR(evt_sub_mail_event))
    BEGIN_INLINE_EVENT
        CALL(sight)
    END_INLINE_EVENT
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): drawBG (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on
__declspec(section ".rodata") const u32 dat_bom_00006360[1] = { 0xFFFFFFFF };
__declspec(section ".rodata") const f32 vec3_bom_00006364[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006370[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 dat_bom_0000637c[1] = { 0xFFFFFFFF };
__declspec(section ".rodata") const u32 dat_bom_00006380[1] = { 0x000000FF };
__declspec(section ".rodata") const f32 vec3_bom_00006384[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006390[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_bom_0000639c[3] = { -200.0f, 150.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000063a8[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_bom_000063b4[3] = { -210.0f, -140.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000063c0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const char str_00000194[] = "s_ie_door\000\000";
__declspec(section ".rodata") const char str_000001A0[] = "s_ie_kai\000\000\000";
__declspec(section ".rodata") const char str_000001AC[] = "\203z\203\217\203C\203g\000\000\000";
__declspec(section ".rodata") const char str_000001B8[] = "\203y\203\223\203g\203\212\203b\203g\000\000\000";
__declspec(section ".rodata") const char str_000001C8[] = "\203X\203\211\203\212\201[\000\000\000";
__declspec(section ".rodata") const char str_000001D4[] = "A_ie_door_u";
__declspec(section ".rodata") const char str_000001E0[] = "A_ie_door\000\000";
__declspec(section ".rodata") const char str_000001EC[] = "S_ie_naka\000\000";
__declspec(section ".rodata") const char str_000001F8[] = "w_bero\000";
__declspec(section ".rodata") const char str_00000200[] = "bom_04\000";
__declspec(section ".rodata") const char str_00000208[] = "e_bero4";
__declspec(section ".rodata") const char str_00000210[] = "e_bero\000";
__declspec(section ".rodata") const char str_00000218[] = "bom_02\000";
__declspec(section ".rodata") const char str_00000220[] = "stg7_bom_01__2_00\000\000";
__declspec(section ".rodata") const char str_00000234[] = "stg7_bom_01__2\000";
__declspec(section ".rodata") const char str_00000244[] = "SFX_VOICE_MARIO_NOD1_3\000";
__declspec(section ".rodata") const char str_0000025C[] = "M_N_2\000\000";
__declspec(section ".rodata") const f32 vec3_bom_0000649c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000064a8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000064b4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000064c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000064cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_000064d8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_000002AC[] = "dummy\000\000";
__declspec(section ".rodata") const char str_000002B4[] = "c_bom_sen\000\000";
__declspec(section ".rodata") const char str_000002C0[] = "SFX_STG7_CANNON_DISCHARGE1\000";
__declspec(section ".rodata") const char str_000002DC[] = "dekatai";
__declspec(section ".rodata") const char str_000002E4[] = "kemuri\000";
__declspec(section ".rodata") const char str_000002EC[] = "kemuri_test";
__declspec(section ".rodata") const char str_000002F8[] = "ripple\000";
__declspec(section ".rodata") const char str_00000300[] = "ripple_n64\000";
__declspec(section ".rodata") const char str_0000030C[] = "particle\000\000\000";
__declspec(section ".rodata") const char str_00000318[] = "hit";
__declspec(section ".rodata") const char str_0000031C[] = "PKR_D_1";
__declspec(section ".rodata") const char str_00000324[] = "PNK_D_1";
__declspec(section ".rodata") const char str_0000032C[] = "D_1";
__declspec(section ".rodata") const char str_00000330[] = "PYS_D_1";
__declspec(section ".rodata") const char str_00000338[] = "PWD_D_1";
__declspec(section ".rodata") const char str_00000340[] = "PTR_D_1";
__declspec(section ".rodata") const char str_00000348[] = "PCH_D_1";
__declspec(section ".rodata") const char str_00000350[] = "SFX_STG7_SHUTTER_OPEN1\000";
__declspec(section ".rodata") const char str_00000368[] = "\203j\203g\203\215\000";
__declspec(section ".rodata") const char str_00000370[] = "stg7_bom_65_a\000\000";
__declspec(section ".rodata") const char str_00000380[] = "stg7_bom_65_b\000\000";
__declspec(section ".rodata") const char str_00000390[] = "stg7_bom_65_c\000\000";
__declspec(section ".rodata") const char str_000003A0[] = "\203{\203\200\203w\203CD\000\000";
__declspec(section ".rodata") const char str_000003AC[] = "stg7_bom_65_d\000\000";
__declspec(section ".rodata") const char str_000003BC[] = "stg7_bom_63";
__declspec(section ".rodata") const char str_000003C8[] = "me\000";
__declspec(section ".rodata") const char str_000003CC[] = "chika_off\000\000";
__declspec(section ".rodata") const char str_000003D8[] = "jime_ugo\000\000\000";
__declspec(section ".rodata") const char str_000003E4[] = "S_yuka1";
__declspec(section ".rodata") const char str_000003EC[] = "S_yuka2";
__declspec(section ".rodata") const char str_000003F4[] = "SFX_VOICE_MARIO_SURPRISED1\000";
__declspec(section ".rodata") const char str_00000410[] = "M_N_7\000\000";
__declspec(section ".rodata") const char str_00000418[] = "SFX_STG7_FLOOR_OPEN1\000\000\000";
__declspec(section ".rodata") const char str_00000430[] = "hiraku_ss_1_b\000\000";
__declspec(section ".rodata") const char str_00000440[] = "hiraku_ss_1_a\000\000";
__declspec(section ".rodata") const char str_00000450[] = "SFX_STG7_MARIO_FALL1\000\000\000";
__declspec(section ".rodata") const char str_00000468[] = "\203r\203r\203A\203\223\202\265\202\301\202\333\226\263\214\370\000";
__declspec(section ".rodata") const char str_0000047C[] = "mario\000\000";
__declspec(section ".rodata") const char str_00000484[] = "stg7_bom_64";
__declspec(section ".rodata") const char str_00000490[] = "stg7_bom_64_01\000";
__declspec(section ".rodata") const char str_000004A0[] = "stg7_bom_66";
__declspec(section ".rodata") const char str_000004AC[] = "stg7_bom_67";
__declspec(section ".rodata") const char str_000004B8[] = "stg7_bom_68";
__declspec(section ".rodata") const char str_000004C4[] = "stg7_bom_69";
__declspec(section ".rodata") const char str_000004D0[] = "SFX_STG7_CANNON_SYS_ACTIVE1";
__declspec(section ".rodata") const char str_000004EC[] = "SFX_STG7_CANNON_SYS_ACTIVE2";
__declspec(section ".rodata") const char str_00000508[] = "kikai\000\000";
__declspec(section ".rodata") const char str_00000510[] = "stg7_bom_70";
__declspec(section ".rodata") const char str_0000051C[] = "stg7_bom_71";
__declspec(section ".rodata") const char str_00000528[] = "stg7_bom_72";
__declspec(section ".rodata") const char str_00000534[] = "SFX_STG7_CANNON_SIREN1\000";
__declspec(section ".rodata") const char str_0000054C[] = "stg7_bom_73";
__declspec(section ".rodata") const char str_00000558[] = "stg7_bom_74";
__declspec(section ".rodata") const char str_00000564[] = "BGM_EVT_STG7_HUGE_GUN1\000";
__declspec(section ".rodata") const char str_0000057C[] = "SFX_STG7_FLOOR_QUAKE1\000\000";
__declspec(section ".rodata") const char str_00000594[] = "SFX_STG7_FLOOR_QUAKE2\000\000";
__declspec(section ".rodata") const char str_000005AC[] = "S_yuka3";
__declspec(section ".rodata") const char str_000005B4[] = "S_hikari\000\000\000";
__declspec(section ".rodata") const char str_000005C0[] = "SFX_STG7_FLOOR_DOWN1\000\000\000";
__declspec(section ".rodata") const char str_000005D8[] = "hiraku_l_1_a\000\000\000";
__declspec(section ".rodata") const char str_000005E8[] = "hiraku_l_1_b\000\000\000";
__declspec(section ".rodata") const char str_000005F8[] = "SFX_STG7_FLOOR_OPEN2\000\000\000";
__declspec(section ".rodata") const char str_00000610[] = "stg7_bom_75";
__declspec(section ".rodata") const char str_0000061C[] = "hiraku_s_1_a\000\000\000";
__declspec(section ".rodata") const char str_0000062C[] = "hiraku_s_1_b\000\000\000";
__declspec(section ".rodata") const char str_0000063C[] = "hiraku_s_2_a\000\000\000";
__declspec(section ".rodata") const char str_0000064C[] = "hiraku_s_2_b\000\000\000";
__declspec(section ".rodata") const char str_0000065C[] = "hiraku_s_3_a\000\000\000";
__declspec(section ".rodata") const char str_0000066C[] = "hiraku_s_3_b\000\000\000";
__declspec(section ".rodata") const char str_0000067C[] = "hiraku_s_4_a\000\000\000";
__declspec(section ".rodata") const char str_0000068C[] = "hiraku_s_4_b\000\000\000";
__declspec(section ".rodata") const char str_0000069C[] = "stg7_bom_76";
__declspec(section ".rodata") const char str_000006A8[] = "SFX_STG7_CANNON_UP1";
__declspec(section ".rodata") const char str_000006BC[] = "S_dekatai\000\000";
__declspec(section ".rodata") const char str_000006C8[] = "SFX_STG7_CANNON_STOP1\000\000";
__declspec(section ".rodata") const char str_000006E0[] = "stg7_bom_77";
__declspec(section ".rodata") const char str_000006EC[] = "SFX_STG7_CANNON_MOVE1\000\000";
__declspec(section ".rodata") const char str_00000704[] = "SFX_STG7_CANNON_STOP2\000\000";
__declspec(section ".rodata") const char str_0000071C[] = "stg7_bom_78";
__declspec(section ".rodata") const char str_00000728[] = "S_moon\000";
__declspec(section ".rodata") const char str_00000730[] = "stg7_bom_79";
__declspec(section ".rodata") const char str_0000073C[] = "stg7_bom_80";
__declspec(section ".rodata") const char str_00000748[] = "SFX_STG7_HATCH_OPEN1\000\000\000";
__declspec(section ".rodata") const char str_00000760[] = "futa\000\000\000";
__declspec(section ".rodata") const char str_00000768[] = "stg7_bom_81";
__declspec(section ".rodata") const char str_00000774[] = "\221\272\222\267\000\000\000";
__declspec(section ".rodata") const char str_0000077C[] = "SFX_STG7_BOMB_TOGETHER1";
__declspec(section ".rodata") const char str_00000794[] = "stg7_bom_85";
__declspec(section ".rodata") const char str_000007A0[] = "SFX_STG7_BOMB_TOGETHER1_2\000\000";
__declspec(section ".rodata") const char str_000007BC[] = "stg7_bom_85_1\000\000";
__declspec(section ".rodata") const char str_000007CC[] = "stg7_bom_85_2\000\000";
__declspec(section ".rodata") const char str_000007DC[] = "stg7_bom_85_3\000\000";
__declspec(section ".rodata") const char str_000007EC[] = "SFX_STG7_HATCH_SHUT1\000\000\000";
__declspec(section ".rodata") const char str_00000804[] = "stg7_bom_85_4\000\000";
__declspec(section ".rodata") const char str_00000814[] = "stg7_bom_85_5\000\000";
__declspec(section ".rodata") const char str_00000824[] = "stg7_bom_85_6\000\000";
__declspec(section ".rodata") const char str_00000834[] = "stg7_bom_86";
__declspec(section ".rodata") const char str_00000840[] = "stg7_bom_87";
__declspec(section ".rodata") const char str_0000084C[] = "HAIKEI\000";
__declspec(section ".rodata") const char str_00000854[] = "SFX_VOICE_MARIO_DAMAGED2\000\000\000";
__declspec(section ".rodata") const char str_00000870[] = "SFX_VOICE_MARIO_AC3_4\000\000";
__declspec(section ".rodata") const char str_00000888[] = "SFX_STG7_MARIO_FLY1";
__declspec(section ".rodata") const char str_0000089C[] = "SFX_STG7_MARIO_LIGHT1\000\000";
__declspec(section ".rodata") const char str_000008B4[] = "wangflush_n64\000\000";
__declspec(section ".rodata") const char str_000008C4[] = "stg7_bom_88";
__declspec(section ".rodata") const char str_000008D0[] = "stg7_bom_89";
__declspec(section ".rodata") const char str_000008DC[] = "stg7_bom_90";
__declspec(section ".rodata") const char str_000008E8[] = "stg7_bom_91";
__declspec(section ".rodata") const char str_000008F4[] = "moo_03\000";
__declspec(section ".rodata") const char str_000008FC[] = "stg7_bom_59_04_1\000\000\000";
__declspec(section ".rodata") const char str_00000910[] = "stg7_bom_59_04_2\000\000\000";
__declspec(section ".rodata") const char str_00000924[] = "stg7_bom_02_00\000";
__declspec(section ".rodata") const char str_00000934[] = "stg7_bom_02";
__declspec(section ".rodata") const char str_00000940[] = "stg7_bom_02_1\000\000";
__declspec(section ".rodata") const char str_00000950[] = "stg7_bom_03";
__declspec(section ".rodata") const char str_0000095C[] = "stg7_bom_03_1\000\000";
__declspec(section ".rodata") const char str_0000096C[] = "stg7_bom_04_00\000";
__declspec(section ".rodata") const char str_0000097C[] = "stg7_bom_04";
__declspec(section ".rodata") const char str_00000988[] = "stg7_bom_04_1\000\000";
__declspec(section ".rodata") const char str_00000998[] = "stg7_bom_05";
__declspec(section ".rodata") const char str_000009A4[] = "stg7_bom_05_1\000\000";
__declspec(section ".rodata") const char str_000009B4[] = "stg7_bom_06_00\000";
__declspec(section ".rodata") const char str_000009C4[] = "stg7_bom_06";
__declspec(section ".rodata") const char str_000009D0[] = "stg7_bom_06_1\000\000";
__declspec(section ".rodata") const char str_000009E0[] = "stg7_bom_07";
__declspec(section ".rodata") const char str_000009EC[] = "stg7_bom_07_1\000\000";
__declspec(section ".rodata") const char str_000009FC[] = "stg7_bom_08_00\000";
__declspec(section ".rodata") const char str_00000A0C[] = "stg7_bom_08";
__declspec(section ".rodata") const char str_00000A18[] = "stg7_bom_08_1\000\000";
__declspec(section ".rodata") const char str_00000A28[] = "stg7_bom_09";
__declspec(section ".rodata") const char str_00000A34[] = "stg7_bom_09_1\000\000";
__declspec(section ".rodata") const char str_00000A44[] = "stg7_bom_10_00\000";
__declspec(section ".rodata") const char str_00000A54[] = "stg7_bom_10";
__declspec(section ".rodata") const char str_00000A60[] = "stg7_bom_11";
__declspec(section ".rodata") const char str_00000A6C[] = "stg7_bom_12_00\000";
__declspec(section ".rodata") const char str_00000A7C[] = "stg7_bom_12";
__declspec(section ".rodata") const char str_00000A88[] = "stg7_bom_13";
__declspec(section ".rodata") const char str_00000A94[] = "stg7_bom_14_00\000";
__declspec(section ".rodata") const char str_00000AA4[] = "stg7_bom_14";
__declspec(section ".rodata") const char str_00000AB0[] = "stg7_bom_15";
__declspec(section ".rodata") const char str_00000ABC[] = "stg7_bom_16_00\000";
__declspec(section ".rodata") const char str_00000ACC[] = "stg7_bom_16";
__declspec(section ".rodata") const char str_00000AD8[] = "stg7_bom_17";
__declspec(section ".rodata") const char str_00000AE4[] = "stg7_bom_18_00\000";
__declspec(section ".rodata") const char str_00000AF4[] = "stg7_bom_18";
__declspec(section ".rodata") const char str_00000B00[] = "stg7_bom_19";
__declspec(section ".rodata") const char str_00000B0C[] = "stg7_bom_59_02\000";
__declspec(section ".rodata") const char str_00000B1C[] = "stg7_bom_59_03\000";
__declspec(section ".rodata") const char str_00000B2C[] = "stg7_bom_59_04\000";
__declspec(section ".rodata") const char str_00000B3C[] = "stg7_bom_59_05\000";
__declspec(section ".rodata") const char str_00000B4C[] = "stg7_bom_09_01_01\000\000";
__declspec(section ".rodata") const char str_00000B60[] = "\202R\220l\226\272\202`\000\000\000";
__declspec(section ".rodata") const char str_00000B6C[] = "stg7_bom_09_01_02\000\000";
__declspec(section ".rodata") const char str_00000B80[] = "\202R\220l\226\272\202a\000\000\000";
__declspec(section ".rodata") const char str_00000B8C[] = "stg7_bom_09_01_03\000\000";
__declspec(section ".rodata") const char str_00000BA0[] = "\202R\220l\226\272\202b\000\000\000";
__declspec(section ".rodata") const char str_00000BAC[] = "stg7_bom_09_01_04\000\000";
__declspec(section ".rodata") const char str_00000BC0[] = "stg7_bom_09_01_05\000\000";
__declspec(section ".rodata") const char str_00000BD4[] = "stg7_bom_09_01_06\000\000";
__declspec(section ".rodata") const char str_00000BE8[] = "stg7_bom_09_01_07\000\000";
__declspec(section ".rodata") const char str_00000BFC[] = "stg7_bom_09_01_08\000\000";
__declspec(section ".rodata") const char str_00000C10[] = "stg7_bom_09_01_09\000\000";
__declspec(section ".rodata") const char str_00000C24[] = "c_dance_r\000\000";
__declspec(section ".rodata") const char str_00000C30[] = "\227x\202\350\216q\000";
__declspec(section ".rodata") const char str_00000C38[] = "c_dance_p\000\000";
__declspec(section ".rodata") const char str_00000C44[] = "\227x\202\350\216q\203s\203\223\203N\000\000\000";
__declspec(section ".rodata") const char str_00000C54[] = "c_dance_k\000\000";
__declspec(section ".rodata") const char str_00000C60[] = "\227x\202\350\216q\211\251\227\316\000";
__declspec(section ".rodata") const f32 vec3_bom_00006ea4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006eb0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006ebc[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006ec8[3] = { 0.0f, 1.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_bom_00006ed4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00000CA8[] = "S_bom01";
__declspec(section ".rodata") const char str_00000CB0[] = "starstone\000\000";
__declspec(section ".rodata") const char str_00000CBC[] = "stg8_las_148_65";
__declspec(section ".rodata") const char str_00000CCC[] = "stg8_las_148_66";
__declspec(section ".rodata") const char str_00000CDC[] = "stg8_las_148_67";
__declspec(section ".rodata") const char str_00000CEC[] = "stg8_las_148_68";
__declspec(section ".rodata") const char str_00000CFC[] = "stg8_las_148_69";
__declspec(section ".rodata") const char str_00000D0C[] = "stg8_las_148_70";
__declspec(section ".rodata") const char str_00000D1C[] = "stg8_las_148_71";
__declspec(section ".rodata") const char str_00000D2C[] = "las_29\000";
__declspec(section ".rodata") const char str_00000D34[] = "minnnanokoe";
__declspec(section ".rodata") const char str_00000D40[] = "stg7_bom_09_01\000";
__declspec(section ".rodata") const char str_00000D50[] = "BGM_EVT_STG8_VOICE1";
__declspec(section ".rodata") const char str_00000D64[] = "BGM_STG7_BOM1\000\000";
__declspec(section ".rodata") const char str_00000D74[] = "ENV_STG7_BOM2\000\000";
__declspec(section ".rodata") const char str_00000D84[] = "group10";
__declspec(section ".rodata") const char str_00000D8C[] = "group11";
__declspec(section ".rodata") const char str_00000D94[] = "group12";
__declspec(section ".rodata") const char str_00000D9C[] = "group13";
__declspec(section ".rodata") const char str_00000DA4[] = "group14";
__declspec(section ".rodata") const char str_00000DAC[] = "group15";
__declspec(section ".rodata") const char str_00000DB4[] = "A_chika";
__declspec(section ".rodata") const char str_00000DBC[] = "item_00";
__declspec(section ".rodata") const f32 float_1_bom_00006ffc[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_100_bom_00007000[1] = { 100.0f };
__declspec(section ".rodata") const f32 zero_bom_00007004[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_0p1_bom_00007008[1] = { 0.1f };
__declspec(section ".rodata") const f32 float_0p5_bom_0000700c[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_10_bom_00007010[1] = { 10.0f };
__declspec(section ".rodata") const char str_00000DDC[] = "SFX_STG7_BOMB_TOGETHER2";
__declspec(section ".rodata") const f64 double_to_int_bom_00007030 = 4503601774854144;
__declspec(section ".rodata") const u32 zero_bom_00007038[1] = { 0x00000000 };
__declspec(section ".rodata") const f32 float_270_bom_0000703c[1] = { 270.0f };
__declspec(section ".rodata") const char str_00000E08[] = "S_1";
__declspec(section ".rodata") const f32 float_4_bom_00007044[1] = { 4.0f };
__declspec(section ".rodata") const char str_00000E10[] = "R_1";
__declspec(section ".rodata") const f32 float_2_bom_0000704c[1] = { 2.0f };
__declspec(section ".rodata") const char str_00000E18[] = "S_hikari%d\000";
__declspec(section ".rodata") const f32 float_1000_bom_0000705c[1] = { 1000.0f };
__declspec(section ".rodata") const f32 float_6p2832_bom_00007060[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_0p125_bom_00007064[1] = { 0.125f };
__declspec(section ".rodata") const f32 float_0p00761_bom_00007068[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_bom_0000706c[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_3p1416_bom_00007070[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_bom_00007074[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_bom_00007078[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_0p03705_bom_0000707c[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_bom_00007080[1] = { 0.4967f };
__declspec(section ".rodata") const f64 double_0p7854_bom_00007088 = 0.7853981852531433;
__declspec(section ".rodata") const char str_00000E58[] = "SFX_STG7_BOMB_FALL1";
__declspec(section ".rodata") const f32 float_280_bom_000070a4[1] = { 280.0f };
__declspec(section ".rodata") const f32 float_3_bom_000070a8[1] = { 3.0f };
__declspec(section ".rodata") const f32 float_32767_bom_000070ac[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_150_bom_000070b0[1] = { 150.0f };
__declspec(section ".rodata") const f32 float_30_bom_000070b4[1] = { 30.0f };
__declspec(section ".rodata") const f32 float_50_bom_000070b8[1] = { 50.0f };
__declspec(section ".rodata") const f32 float_400_bom_000070bc[1] = { 400.0f };
__declspec(section ".rodata") const f32 float_70_bom_000070c0[1] = { 70.0f };
__declspec(section ".rodata") const f32 float_350_bom_000070c4[1] = { 350.0f };
__declspec(section ".rodata") const f32 float_180_bom_000070c8[1] = { 180.0f };
__declspec(section ".rodata") const f32 float_neg1000_bom_000070cc[1] = { -1000.0f };
__declspec(section ".rodata") const f32 float_neg20_bom_000070d0[1] = { -20.0f };
__declspec(section ".rodata") const f32 float_deg2rad_bom_000070d4[1] = { 0.017453292f };
__declspec(section ".rodata") const f32 float_20_bom_000070d8[1] = { 20.0f };
__declspec(section ".rodata") const f32 float_60_bom_000070dc[1] = { 60.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_bom_000070e0 = 4503599627370496;
__declspec(section ".rodata") const f32 float_500_bom_000070e8[1] = { 500.0f };
__declspec(section ".rodata") const char str_00000EB4[] = "S_2";
__declspec(section ".rodata") const f32 float_6_bom_000070f0[1] = { 6.0f };
__declspec(section ".rodata") const f32 float_600_bom_000070f4[1] = { 600.0f };
__declspec(section ".rodata") const f32 float_300_bom_000070f8[1] = { 300.0f };
__declspec(section ".rodata") const f32 float_3700_bom_000070fc[1] = { 3700.0f };
__declspec(section ".rodata") const f32 float_neg650_bom_00007100[1] = { -650.0f };
__declspec(section ".rodata") const f32 float_neg450_bom_00007104[1] = { -450.0f };
__declspec(section ".rodata") const char str_00000ED0[] = "%s/%s\000\000";
__declspec(section ".rodata") const char str_00000ED8[] = "taihou.tpl\000";
__declspec(section ".rodata") const f32 float_800_bom_0000711c[1] = { 800.0f };
__declspec(section ".rodata") const f32 float_neg1_bom_00007120[1] = { -1.0f };
__declspec(section ".rodata") const f32 float_neg100_bom_00007124[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_neg60_bom_00007128[1] = { -60.0f };
__declspec(section ".rodata") const f32 float_0p6_bom_0000712c[1] = { 0.6f };
__declspec(section ".rodata") const f32 float_90_bom_00007130[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_126_bom_00007134[1] = { 126.0f };
__declspec(section ".rodata") const f32 float_162_bom_00007138[1] = { 162.0f };
__declspec(section ".rodata") const f32 float_120_bom_0000713c[1] = { 120.0f };
__declspec(section ".rodata") const f32 float_110_bom_00007140[1] = { 110.0f };
__declspec(section ".rodata") const f32 float_neg160_bom_00007144[1] = { -160.0f };
__declspec(section ".rodata") const f32 float_0p8_bom_00007148[1] = { 0.8f };
__declspec(section ".rodata") const f32 float_230_bom_0000714c[1] = { 230.0f };
__declspec(section ".rodata") const f32 float_neg170_bom_00007150[1] = { -170.0f };
__declspec(section ".rodata") const f32 float_neg240_bom_00007154[1] = { -240.0f };
__declspec(section ".rodata") const f32 float_neg190_bom_00007158[1] = { -190.0f };
__declspec(section ".rodata") const f32 float_16_bom_0000715c[1] = { 16.0f };
__declspec(section ".rodata") const f32 float_neg16_bom_00007160[1] = { -16.0f };
__declspec(section ".rodata") const f32 float_neg180_bom_00007164[1] = { -180.0f };
__declspec(section ".rodata") const f32 float_neg220_bom_00007168[1] = { -220.0f };
__declspec(section ".rodata") const f32 float_200_bom_0000716c[1] = { 200.0f };
static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall);
static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall);
static s32 starstone_entry(EventEntry* event, BOOL isFirstCall);
static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall);
static s32 yami_view(EventEntry* event, BOOL isFirstCall);
s32 bom1000_jump(EventEntry* event, BOOL isFirstCall);
s32 bom1000_msg(EventEntry* event, BOOL isFirstCall);
void ext_dispent_minnnanokoe(void);
void ext_disp_minnnanokoe(CameraId camera, void* param);
void jump_minnnanokoe(s32 i, f32 h);
void ext_init_minnnanokoe(void);
s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall);
static s32 make_name(EventEntry* event, BOOL isFirstCall);
static s32 depth(EventEntry* event, BOOL isFirstCall);
static void depthDisp(CameraId camera, void* param);
s32 taihou_r(EventEntry* event, BOOL isFirstCall);
static void ext_dispent(void);
static void ext_main(void);
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
static void ext_init(void);
s32 make_ext_table(EventEntry* event, BOOL isFirstCall);
static void pose_change(s32 i, const char* name);
static void pose_main(void);
static void pose_init(void);
s32 bom_fall(EventEntry* event, BOOL isFirstCall);
s32 bom_flag(EventEntry* event, BOOL isFirstCall);
s32 sight_dir(EventEntry* event, BOOL isFirstCall);
s32 sight(EventEntry* event, BOOL isFirstCall);
void disp_sight(CameraId camera, void* param);
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);

void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
u16 GXGetTexObjHeight(const GXTexObj* to);
u16 GXGetTexObjWidth(const GXTexObj* to);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXPixModeSync(void);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetNumChans(u8 nChans);
void GXSetNumIndStages(u8 nIndStages);
void GXSetNumTevStages(u8 nStages);
void GXSetNumTexGens(u8 nTexGens);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
f32 PSVECDistance(const Vec* a, const Vec* b);
void PSVECNormalize(const Vec* src, Vec* dst);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void TEXGetGXTexObjFromPalette(TEXPalette* pal, GXTexObj* to, u32 id);
void __cvt_ull_flt();
void __div2i();
void __div2u();
void* _mapAlloc(u32 size);
void _mapFree(void* alloc);
void _restfpr_29();
void _savefpr_29();
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
EffectEntry* effNameToPtr(const char* name);
void effRippleN64SetRxRz(EffectEntry* effect, f32 rx, f32 rz);
void effSetName(EffectEntry* effect, const char* name);
f32 evtGetFloat(EventEntry* entry, s32 index);
s32 evtGetValue(EventEntry* entry, s32 index);
f32 evtSetFloat(EventEntry* entry, s32 index, f32 value);
s32 evtSetValue(EventEntry* entry, s32 index, s32 value);
FileEntry* fileAllocf(s32 type, const char* format, ...);
s32 fileAsyncf(s32 type, FileCallback callback, const char* format, ...);
void fileFree(FileEntry* handle);
const char* getMarioStDvdRoot(void);
s32 irand(s32 scalar);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr_NoAssert(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);
int rand(void);
smartEntry* smartAlloc(u32 size, u8 type);
int sprintf(char *s, const char *format, ...);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
void sysWaitDrawSync(void);
void winTexInit(TEXPalette* texture);
void winTexSet(u32 textureId, Vec translate, Vec scale, GXColor color);
asm static s32 starstone_set_ry(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x18(r1)
	stmw r30, 0x10(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	mr r3, r31
	bl effNameToPtr
	lwz r4, 0xc(r3)
	li r3, 0x2
	stfs f31, 0x1c(r4)
	lfd f31, 0x18(r1)
	lmw r30, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static s32 starstone_set_pos(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	addi r11, r1, 0x30
	bl _savefpr_29
	stmw r29, 0xc(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	mr r3, r30
	bl effNameToPtr
	lwz r4, 0xc(r3)
	stfs f29, 0x8(r4)
	lwz r4, 0xc(r3)
	stfs f30, 0xc(r4)
	lwz r4, 0xc(r3)
	li r3, 0x2
	stfs f31, 0x10(r4)
	addi r11, r1, 0x30
	bl _restfpr_29
	lmw r29, 0xc(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm static s32 starstone_entry(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x8(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r29
	bl evtGetFloat
	fmr f0, f1
	lis r3, float_1_bom_00006ffc@ha
	lfs f4, float_1_bom_00006ffc@l(r3)
	fmr f1, f31
	fmr f2, f30
	li r3, 0x6
	fmr f3, f0
	bl effStarStoneEntry
	mr r4, r30
	bl effSetName
	li r3, 0x2
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	lmw r29, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm static s32 anim_tevcallback(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r29, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r29
	bl evtGetValue
	mr r31, r3
	mr r3, r30
	bl npcNameToPtr_NoAssert
	cmplwi r3, 0x0
	bne @1
	li r3, 0x2
	b @2
	@1:
	lwz r3, 0x104(r3)
	clrlslwi r4, r31, 28, 24
	bl animPoseSetMaterialFlagOn
	li r3, 0x2
	@2:
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static s32 yami_view(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stw r31, 0x6c(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetFloat
	lis r3, float_100_bom_00007000@ha
	lis r5, vec3_bom_00006ed4@ha
	addi r5, r5, vec3_bom_00006ed4@l
	lfs f0, float_100_bom_00007000@l(r3)
	lis r4, vec3_bom_00006ebc@ha
	lis r3, vec3_bom_00006ec8@ha
	addi r6, r3, vec3_bom_00006ec8@l
	fadds f0, f0, f1
	addi r8, r4, vec3_bom_00006ebc@l
	lwz r4, 0x8(r5)
	lwz r0, 0x8(r8)
	addi r3, r1, 0x2c
	stw r4, 0x10(r1)
	lwz r31, 0x0(r5)
	addi r4, r1, 0x20
	stw r0, 0x28(r1)
	lwz r12, 0x4(r5)
	addi r5, r1, 0x14
	lwz r11, 0x0(r6)
	lwz r10, 0x4(r6)
	lwz r9, 0x8(r6)
	addi r6, r1, 0x8
	lwz r7, 0x0(r8)
	lwz r0, 0x4(r8)
	stw r31, 0x8(r1)
	stw r12, 0xc(r1)
	stfs f1, 0x10(r1)
	stw r11, 0x14(r1)
	stw r10, 0x18(r1)
	stw r9, 0x1c(r1)
	stw r7, 0x20(r1)
	stw r0, 0x24(r1)
	stfs f0, 0x28(r1)
	bl C_MTXLookAt
	addi r3, r1, 0x2c
	bl envSetYamiView
	lwz r0, 0x74(r1)
	li r3, 0x2
	lwz r31, 0x6c(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 bom1000_jump(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r3, lp@ha
	stw r0, 0x54(r1)
	addi r3, r3, lp@l
	stmw r28, 0x40(r1)
	lwz r3, 0x0(r3)
	lwz r28, 0x0(r3)
	bl rand
	lwz r4, 0x4(r28)
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r29, r0, r3
	mulli r30, r29, 0x30
	add r3, r28, r30
	lbz r0, 0xb0(r3)
	cmpwi r0, 0x64
	beq @1
	lis r3, lp@ha
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r28, 0x0(r3)
	bl extGetPosePtr
	slwi r0, r29, 5
	lis r4, vec3_bom_00006ea4@ha
	addi r6, r4, vec3_bom_00006ea4@l
	lis r8, 0x4330
	add r31, r3, r0
	lwz r0, 0x0(r6)
	lwz r7, 0xc(r31)
	lis r3, zero_bom_00007004@ha
	lwz r5, 0x4(r6)
	addi r4, r3, zero_bom_00007004@l
	stw r0, 0x14(r1)
	lis r3, float_0p1_bom_00007008@ha
	lfs f0, 0xc(r7)
	addi r11, r3, float_0p1_bom_00007008@l
	lwz r0, 0x8(r6)
	lis r3, double_to_int_bom_00007030@ha
	stfs f0, 0x14(r1)
	addi r9, r3, double_to_int_bom_00007030@l
	lfs f1, 0x1c(r7)
	add r28, r28, r30
	stw r5, 0x18(r1)
	lis r3, float_10_bom_00007010@ha
	lfs f0, 0x2c(r7)
	addi r6, r3, float_10_bom_00007010@l
	stw r0, 0x1c(r1)
	lis r3, float_0p5_bom_0000700c@ha
	lwz r12, 0x14(r1)
	addi r7, r3, float_0p5_bom_0000700c@l
	stfs f1, 0x18(r1)
	lis r3, 0xf5de
	lfs f1, 0x0(r4)
	li r10, 0x14
	stfs f0, 0x1c(r1)
	li r5, 0x5
	lwz r30, 0x18(r1)
	li r0, 0x64
	stw r12, 0xb4(r28)
	addi r4, r3, 0x180
	lwz r12, 0x1c(r1)
	li r3, 0x0
	stw r30, 0xb8(r28)
	lfs f0, 0x0(r11)
	stw r12, 0xbc(r28)
	lfd f3, 0x0(r9)
	stfs f1, 0xc0(r28)
	lfs f1, 0x0(r6)
	stfs f0, 0xc4(r28)
	lfs f2, 0x0(r7)
	sth r10, 0xc8(r28)
	lha r6, 0xc8(r28)
	stw r8, 0x38(r1)
	xoris r6, r6, 0x8000
	lfs f4, 0xc4(r28)
	stw r6, 0x3c(r1)
	lfd f0, 0x38(r1)
	stw r6, 0x34(r1)
	fsubs f0, f0, f3
	stw r8, 0x30(r1)
	fdivs f0, f1, f0
	lfd f1, 0x30(r1)
	fsubs f1, f1, f3
	fmuls f1, f4, f1
	fmadds f0, f1, f2, f0
	stfs f0, 0xcc(r28)
	stb r5, 0xb1(r28)
	stb r0, 0xb0(r28)
	bl evtGetValue
	cmpwi r3, 0x191
	beq @1
	li r3, 0x5
	divw r0, r29, r3
	mullw r0, r0, r3
	subf. r0, r0, r29
	bne @1
	lis r3, vec3_bom_00006eb0@ha
	lwz r7, 0xc(r31)
	addi r4, r3, vec3_bom_00006eb0@l
	lwz r6, 0x0(r4)
	lis r3, str_00000DDC@ha
	lwz r5, 0x4(r4)
	addi r3, r3, str_00000DDC@l
	lwz r0, 0x8(r4)
	addi r4, r1, 0x8
	stw r6, 0x20(r1)
	lfs f0, 0xc(r7)
	stw r5, 0x24(r1)
	lfs f1, 0x1c(r7)
	stfs f0, 0x20(r1)
	lfs f0, 0x2c(r7)
	stw r0, 0x28(r1)
	lwz r6, 0x20(r1)
	stfs f1, 0x24(r1)
	stfs f0, 0x28(r1)
	lwz r5, 0x24(r1)
	lwz r0, 0x28(r1)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl psndSFXOn_3D
	@1:
	lmw r28, 0x40(r1)
	li r3, 0x2
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm s32 bom1000_msg(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r30, r3
	lwz r27, 0x18(r3)
	lwz r4, 0x0(r27)
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r29, r3
	mr r3, r30
	addi r31, r27, 0x8
	bl evtGetValue
	mr r28, r3
	bl extGetPosePtr
	cmpwi r29, 0x0
	mr r29, r3
	bne @1
	li r0, 0x3
	li r26, 0x1
	b @2
	@1:
	li r0, 0xa
	li r26, 0x0
	@2:
	mulli r0, r0, 0xe
	add r25, r28, r0
	bl rand
	srwi r4, r3, 31
	clrlwi r0, r3, 31
	xor r3, r0, r4
	slwi r0, r25, 5
	subf r3, r4, r3
	li r7, 0xe
	addi r3, r3, 0x1
	lwz r4, 0x0(r27)
	slwi r5, r3, 2
	mr r3, r30
	add r28, r28, r5
	mr r5, r26
	divw r6, r28, r7
	add r26, r29, r0
	mullw r0, r6, r7
	subf r28, r0, r28
	bl evtSetValue
	lwz r4, 0x4(r27)
	mr r3, r30
	mr r5, r28
	bl evtSetValue
	lwz r5, 0xc(r26)
	mr r3, r30
	lwz r4, 0x0(r31)
	lfs f1, 0xc(r5)
	bl evtSetFloat
	lwz r5, 0xc(r26)
	mr r3, r30
	lwz r4, 0x4(r31)
	lfs f1, 0x2c(r5)
	bl evtSetFloat
	lmw r25, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void ext_dispent_minnnanokoe(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, zero_bom_00007004@ha
	lis r4, ext_disp_minnnanokoe@ha
	addi r6, r3, zero_bom_00007004@l
	stw r0, 0x14(r1)
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp_minnnanokoe@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void ext_disp_minnnanokoe(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r29, 0x34(r1)
	addi r31, r1, 0x8
	bl extGetPosePtr
	mr r30, r3
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	li r29, 0x0
	b @1
	@2:
	li r4, 0x1
	li r0, 0x0
	stw r4, 0x14(r1)
	mr r3, r31
	stw r4, 0x18(r1)
	stw r4, 0x1c(r1)
	stw r0, 0x20(r1)
	lwz r0, 0xc(r30)
	stw r0, 0xc(r1)
	bl envSetYami
	lwz r0, 0x1c(r1)
	clrlwi r3, r0, 24
	bl GXSetNumTexGens
	lwz r0, 0x14(r1)
	clrlwi r3, r0, 24
	bl GXSetNumTevStages
	lwz r0, 0x20(r1)
	clrlwi r3, r0, 24
	bl GXSetNumIndStages
	mr r3, r29
	bl extPoseDraw
	addi r29, r29, 0x1
	addi r30, r30, 0x20
	@1:
	bl extGetPoseNum
	cmpw r29, r3
	blt @2
	bl extLoadTextureExit
	lmw r29, 0x34(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void jump_minnnanokoe(s32 i, f32 h) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stmw r29, 0x44(r1)
	lis r4, lp@ha
	mr r30, r3
	lwz r3, lp@l(r4)
	fmr f31, f1
	lwz r29, 0x0(r3)
	bl extGetPosePtr
	slwi r0, r30, 5
	lis r4, vec3_bom_00006ea4@ha
	addi r6, r4, vec3_bom_00006ea4@l
	lis r7, 0x4330
	add r31, r3, r0
	lwz r0, 0x0(r6)
	lwz r8, 0xc(r31)
	mulli r9, r30, 0x30
	lwz r5, 0x4(r6)
	lis r3, float_0p1_bom_00007008@ha
	stw r0, 0x14(r1)
	lis r4, zero_bom_00007004@ha
	lfs f0, 0xc(r8)
	lwz r0, 0x8(r6)
	add r29, r29, r9
	stfs f0, 0x14(r1)
	addi r10, r3, float_0p1_bom_00007008@l
	lfs f1, 0x1c(r8)
	lis r3, double_to_int_bom_00007030@ha
	stw r5, 0x18(r1)
	li r9, 0x14
	lfs f0, 0x2c(r8)
	addi r8, r3, double_to_int_bom_00007030@l
	stw r0, 0x1c(r1)
	lis r3, float_0p5_bom_0000700c@ha
	lwz r11, 0x14(r1)
	addi r6, r3, float_0p5_bom_0000700c@l
	stfs f1, 0x18(r1)
	li r5, 0x5
	lfs f1, zero_bom_00007004@l(r4)
	lis r3, 0xf5de
	stfs f0, 0x1c(r1)
	addi r4, r3, 0x180
	lwz r12, 0x18(r1)
	li r0, 0x64
	stw r11, 0xb4(r29)
	li r3, 0x0
	lwz r11, 0x1c(r1)
	stw r12, 0xb8(r29)
	lfs f0, 0x0(r10)
	stw r11, 0xbc(r29)
	lfd f3, 0x0(r8)
	stfs f1, 0xc0(r29)
	lfs f1, 0x0(r6)
	stfs f0, 0xc4(r29)
	sth r9, 0xc8(r29)
	lha r6, 0xc8(r29)
	stw r7, 0x38(r1)
	xoris r6, r6, 0x8000
	lfs f4, 0xc4(r29)
	stw r6, 0x3c(r1)
	lfd f0, 0x38(r1)
	stw r6, 0x34(r1)
	fsubs f0, f0, f3
	stw r7, 0x30(r1)
	fdivs f0, f31, f0
	lfd f2, 0x30(r1)
	fsubs f2, f2, f3
	fmuls f2, f4, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0xcc(r29)
	stb r5, 0xb1(r29)
	stb r0, 0xb0(r29)
	bl evtGetValue
	cmpwi r3, 0x191
	beq @1
	li r3, 0x5
	divw r0, r30, r3
	mullw r0, r0, r3
	subf. r0, r0, r30
	bne @1
	lis r3, vec3_bom_00006eb0@ha
	lwz r7, 0xc(r31)
	addi r4, r3, vec3_bom_00006eb0@l
	lwz r6, 0x0(r4)
	lis r3, str_00000DDC@ha
	lwz r5, 0x4(r4)
	addi r3, r3, str_00000DDC@l
	lwz r0, 0x8(r4)
	addi r4, r1, 0x20
	stw r6, 0x8(r1)
	lfs f0, 0xc(r7)
	stw r5, 0xc(r1)
	lfs f1, 0x1c(r7)
	stfs f0, 0x8(r1)
	lfs f0, 0x2c(r7)
	stw r0, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r6, 0x20(r1)
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	bl psndSFXOn_3D
	@1:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	lmw r29, 0x44(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void ext_init_minnnanokoe(void) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stmw r22, 0x38(r1)
	lis r3, 0x1
	li r4, 0x1
	subi r3, r3, 0x43d0
	bl smartAlloc
	lis r4, lp@ha
	lis r5, 0x1
	addi r6, r4, lp@l
	li r4, 0x0
	stw r3, 0x0(r6)
	subi r5, r5, 0x43d0
	lwz r25, 0x0(r3)
	mr r3, r25
	bl memset
	bl extGetPoseNum
	stw r3, 0x4(r25)
	lis r3, lp@ha
	addi r4, r3, lp@l
	li r30, 0x0
	lwz r5, 0x0(r4)
	lis r3, ext_data@ha
	lis r4, zero_bom_00007038@ha
	lwz r28, 0x0(r5)
	addi r31, r3, ext_data@l
	addi r3, r1, 0x8
	addi r4, r4, zero_bom_00007038@l
	bl strcpy
	li r0, -0x1
	stw r0, 0xa8(r28)
	@1:
	lwz r3, 0x4(r31)
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x4(r31)
	addi r3, r1, 0x8
	bl strcpy
	lwz r3, 0xa8(r28)
	mr r29, r30
	addi r0, r3, 0x1
	stw r0, 0xa8(r28)
	@2:
	lwz r0, 0xa8(r28)
	addi r4, r1, 0x8
	mulli r3, r0, 0x14
	addi r3, r3, 0x8
	add r3, r28, r3
	bl strcpy
	lwz r0, 0xa8(r28)
	subf r3, r29, r30
	addi r4, r3, 0x1
	addi r30, r30, 0x1
	mulli r3, r0, 0x14
	addi r0, r3, 0x14
	stwx r29, r28, r0
	lwz r0, 0xa8(r28)
	mulli r3, r0, 0x14
	addi r0, r3, 0x18
	stwx r4, r28, r0
	lwz r0, 0xa8(r28)
	lfs f0, 0x8(r31)
	mulli r3, r0, 0x14
	addi r0, r3, 0x10
	stfsx f0, r28, r0
	lwzu r0, 0xc(r31)
	cmplwi r0, 0x0
	bne @1
	lwz r3, 0xa8(r28)
	addi r0, r3, 0x1
	stw r0, 0xa8(r28)
	bl extGetPosePtr
	lis r6, zero_bom_00007004@ha
	lis r5, double_to_int_bom_00007030@ha
	addi r7, r5, double_to_int_bom_00007030@l
	lis r4, float_270_bom_0000703c@ha
	addi r8, r6, zero_bom_00007004@l
	lis r5, lp@ha
	addi r6, r4, float_270_bom_0000703c@l
	lis r4, str_00000E08@ha
	lfs f29, 0x0(r8)
	mr r24, r3
	lfd f30, 0x0(r7)
	addi r31, r4, str_00000E08@l
	lfs f31, 0x0(r6)
	addi r30, r5, lp@l
	li r26, 0x0
	li r23, 0x0
	lis r29, 0x4330
	b @3
	@4:
	add r3, r25, r23
	li r0, 0x5
	stfs f29, 0xcc(r3)
	stfs f29, 0xc4(r3)
	stb r0, 0xb0(r3)
	lwz r0, 0x0(r24)
	ori r0, r0, 0x3
	stw r0, 0x0(r24)
	lwz r3, 0xc(r24)
	bl PSMTXIdentity
	bl rand
	li r4, 0xe
	li r6, 0xa
	divw r0, r26, r4
	divw r5, r3, r6
	mullw r0, r0, r4
	mullw r4, r5, r6
	subf r0, r0, r26
	mulli r0, r0, 0x1e
	subf r3, r4, r3
	add r22, r0, r3
	subi r22, r22, 0xcd
	bl rand
	li r7, 0x14
	li r5, 0xe
	divw r6, r3, r7
	xoris r0, r22, 0x8000
	stw r0, 0x2c(r1)
	li r28, 0x0
	lwz r4, 0xc(r24)
	stw r29, 0x28(r1)
	divw r0, r26, r5
	lfd f0, 0x28(r1)
	stw r29, 0x30(r1)
	fsubs f0, f0, f30
	stfs f0, 0xc(r4)
	lwz r4, 0xc(r24)
	mullw r5, r6, r7
	stfs f29, 0x1c(r4)
	lwz r4, 0xc(r24)
	mulli r0, r0, 0x14
	subf r3, r5, r3
	subfic r0, r0, 0xbe
	add r0, r0, r3
	xoris r0, r0, 0x8000
	stw r0, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f30
	stfs f0, 0x2c(r4)
	stfs f31, 0x4(r24)
	lwz r3, 0x0(r30)
	lwz r22, 0x0(r3)
	addi r27, r22, 0x8
	b @5
	@6:
	mr r3, r27
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	addi r28, r28, 0x1
	addi r27, r27, 0x14
	@5:
	lwz r0, 0xa8(r22)
	cmpw r28, r0
	blt @6
	@7:
	lwz r0, 0xa8(r22)
	cmpw r28, r0
	bge @8
	add r27, r22, r23
	lwz r0, 0xd0(r27)
	cmpw r0, r28
	beq @8
	extsh r0, r28
	stw r0, 0xd0(r27)
	bl rand
	lis r4, gp@ha
	srawi r0, r3, 31
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r5, 0x3c(r4)
	lwz r4, 0x38(r4)
	addc r3, r5, r3
	stw r3, 0xdc(r27)
	adde r0, r4, r0
	stw r0, 0xd8(r27)
	@8:
	addi r26, r26, 0x1
	addi r23, r23, 0x30
	addi r24, r24, 0x20
	@3:
	lwz r0, 0x4(r25)
	cmpw r26, r0
	blt @4
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	lmw r22, 0x38(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm s32 make_ext_table_minnnanokoe(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, ext_data@ha
	li r4, 0x0
	stw r0, 0x14(r1)
	addi r3, r3, ext_data@l
	li r5, 0x174
	bl memset
	lis r4, float_4_bom_00007044@ha
	lis r3, double_to_int_bom_00007030@ha
	lis r7, str_000002B4@ha
	lis r6, ext_data@ha
	lis r5, str_00000E08@ha
	lfs f2, float_4_bom_00007044@l(r4)
	lfd f1, double_to_int_bom_00007030@l(r3)
	li r0, 0xa
	addi r7, r7, str_000002B4@l
	addi r6, r6, ext_data@l
	addi r5, r5, str_00000E08@l
	li r9, 0x0
	li r3, 0x0
	lis r4, 0x4330
	mtctr r0
	@1:
	xoris r0, r9, 0x8000
	add r8, r6, r3
	stw r0, 0xc(r1)
	addi r9, r9, 0x1
	addi r3, r3, 0xc
	stw r4, 0x8(r1)
	lfd f0, 0x8(r1)
	stw r7, 0x0(r8)
	fsubs f0, f0, f1
	stw r5, 0x4(r8)
	fmuls f0, f2, f0
	stfs f0, 0x8(r8)
	bdnz @1
	lis r4, float_2_bom_0000704c@ha
	lis r3, double_to_int_bom_00007030@ha
	lis r7, str_000002B4@ha
	lis r6, ext_data@ha
	lis r5, str_00000E10@ha
	lfs f2, float_2_bom_0000704c@l(r4)
	lfd f1, double_to_int_bom_00007030@l(r3)
	li r0, 0x14
	addi r7, r7, str_000002B4@l
	addi r6, r6, ext_data@l
	addi r5, r5, str_00000E10@l
	li r9, 0x0
	li r3, 0x0
	lis r4, 0x4330
	mtctr r0
	@2:
	xoris r0, r9, 0x8000
	add r8, r6, r3
	stw r0, 0xc(r1)
	addi r9, r9, 0x1
	addi r3, r3, 0xc
	stw r4, 0x8(r1)
	lfd f0, 0x8(r1)
	stw r7, 0x78(r8)
	fsubs f0, f0, f1
	stw r5, 0x7c(r8)
	fmuls f0, f2, f0
	stfs f0, 0x80(r8)
	bdnz @2
	lis r3, ext_data@ha
	li r0, 0x0
	addi r4, r3, ext_data@l
	li r3, 0x2
	stw r0, 0x168(r4)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 make_name(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lis r4, str_00000E18@ha
	lis r6, (lp+4)@ha
	mr r5, r3
	addi r3, r6, (lp+4)@l
	addi r4, r4, str_00000E18@l
	crclr 6
	bl sprintf
	lis r3, (lp+4)@ha
	lwz r4, 0x4(r31)
	addi r5, r3, (lp+4)@l
	mr r3, r30
	bl evtSetValue
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 depth(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, float_1000_bom_0000705c@ha
	lis r4, depthDisp@ha
	addi r6, r3, float_1000_bom_0000705c@l
	stw r0, 0x14(r1)
	lfs f1, 0x0(r6)
	addi r5, r4, depthDisp@l
	li r3, 0x8
	li r4, 0x0
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	li r3, 0x0
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void depthDisp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stfd f27, 0xc0(r1)
	psq_st f27, 0xc8(r1), 0, 0
	stfd f26, 0xb0(r1)
	psq_st f26, 0xb8(r1), 0, 0
	stfd f25, 0xa0(r1)
	psq_st f25, 0xa8(r1), 0, 0
	stfd f24, 0x90(r1)
	psq_st f24, 0x98(r1), 0, 0
	stfd f23, 0x80(r1)
	psq_st f23, 0x88(r1), 0, 0
	stmw r24, 0x60(r1)
	lis r4, 0xfd05
	mr r24, r3
	addi r4, r4, 0xf85
	li r3, 0x0
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x5c(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_100_bom_00007000@ha
	stw r0, 0x58(r1)
	addi r4, r3, float_100_bom_00007000@l
	lfd f2, 0x0(r5)
	mr r3, r24
	lfd f1, 0x58(r1)
	lfs f0, 0x0(r4)
	fsubs f1, f1, f2
	fdivs f24, f1, f0
	bl camGetPtr
	mr r28, r3
	li r3, 0x260
	li r4, 0x1e0
	li r5, 0x4
	li r6, 0x0
	li r7, 0x0
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	mr r24, r3
	li r3, 0x0
	li r4, 0x0
	li r5, 0x260
	li r6, 0x1e0
	bl GXSetTexCopySrc
	li r3, 0x260
	li r4, 0x1e0
	li r5, 0x4
	li r6, 0x0
	bl GXSetTexCopyDst
	lwz r3, 0x0(r24)
	li r4, 0x0
	bl GXCopyTex
	bl GXPixModeSync
	lwz r4, 0x0(r24)
	addi r3, r1, 0x8
	li r5, 0x260
	li r6, 0x1e0
	li r7, 0x4
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	lis r4, zero_bom_00007004@ha
	addi r3, r1, 0x8
	addi r5, r4, zero_bom_00007004@l
	li r4, 0x1
	lfs f1, 0x0(r5)
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	fmr f2, f1
	li r8, 0x0
	fmr f3, f1
	bl GXInitTexObjLOD
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
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
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x2
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x8
	bl GXSetNumTexGens
	li r3, 0x8
	bl GXSetNumTevStages
	lis r10, float_6p2832_bom_00007060@ha
	lis r9, double_to_int_bom_00007030@ha
	lis r8, float_0p125_bom_00007064@ha
	lis r7, float_0p16605_bom_0000706c@ha
	lis r6, float_1_bom_00006ffc@ha
	lis r5, float_3p1416_bom_00007070@ha
	lis r4, float_0p4967_bom_00007080@ha
	lis r3, float_100_bom_00007000@ha
	addi r24, r10, float_6p2832_bom_00007060@l
	addi r12, r9, double_to_int_bom_00007030@l
	addi r11, r8, float_0p125_bom_00007064@l
	addi r9, r7, float_0p16605_bom_0000706c@l
	addi r8, r6, float_1_bom_00006ffc@l
	addi r7, r5, float_3p1416_bom_00007070@l
	addi r5, r4, float_0p4967_bom_00007080@l
	addi r4, r3, float_100_bom_00007000@l
	lis r10, float_0p00761_bom_00007068@ha
	lis r6, float_0p03705_bom_0000707c@ha
	lis r3, zero_bom_00007004@ha
	lfs f28, 0x0(r24)
	lfd f29, 0x0(r12)
	addi r30, r10, float_0p00761_bom_00007068@l
	lfs f30, 0x0(r11)
	addi r31, r6, float_0p03705_bom_0000707c@l
	lfs f26, 0x0(r9)
	addi r24, r3, zero_bom_00007004@l
	lfs f27, 0x0(r8)
	li r27, 0x0
	lfs f31, 0x0(r7)
	li r26, 0x0
	lfs f25, 0x0(r5)
	lis r29, 0x4330
	lfs f23, 0x0(r4)
	@1:
	xoris r0, r27, 0x8000
	stw r29, 0x58(r1)
	lfs f2, 0x0(r30)
	stw r0, 0x5c(r1)
	lfd f0, 0x58(r1)
	fsubs f0, f0, f29
	fmuls f0, f28, f0
	fmuls f3, f0, f30
	fcmpo cr0, f3, f31
	cror eq, lt, eq
	bne @2
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @3
	fmuls f0, f3, f3
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f3
	b @4
	@3:
	fsubs f0, f3, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	b @4
	@2:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f3, f0
	bge @5
	lis r3, float_3p1416_bom_00007070@ha
	lfs f0, float_3p1416_bom_00007070@l(r3)
	fsubs f1, f3, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	fneg f2, f2
	b @4
	@5:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f3, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f26
	fmadds f2, f2, f0, f27
	fmuls f2, f2, f1
	fneg f2, f2
	@4:
	fcmpo cr0, f3, f31
	lfs f4, 0x0(r31)
	cror eq, lt, eq
	bne @6
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f3, f1
	cror eq, lt, eq
	bne @7
	fmuls f0, f3, f3
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	b @8
	@7:
	fsubs f0, f3, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	fneg f4, f4
	b @8
	@6:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f3, f0
	bge @9
	lis r3, float_3p1416_bom_00007070@ha
	lfs f0, float_3p1416_bom_00007070@l(r3)
	fsubs f0, f3, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	fneg f4, f4
	b @8
	@9:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f3, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f25
	fmadds f4, f4, f0, f27
	@8:
	fmuls f1, f24, f2
	lfs f3, 0x0(r24)
	fmuls f0, f24, f4
	addi r3, r1, 0x28
	fdivs f1, f1, f23
	fdivs f2, f0, f23
	bl PSMTXTrans
	addi r25, r26, 0x1e
	addi r3, r1, 0x28
	mr r4, r25
	li r5, 0x1
	bl GXLoadTexMtxImm
	mr r3, r27
	mr r6, r25
	li r4, 0x1
	li r5, 0x4
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r27
	li r4, 0x7
	bl GXSetTevKColorSel
	mr r3, r27
	li r4, 0x7
	bl GXSetTevKAlphaSel
	mr r3, r27
	mr r4, r27
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	mr r3, r27
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevColorOp
	mr r3, r27
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x1
	li r8, 0x0
	bl GXSetTevAlphaOp
	cntlzw r0, r27
	li r7, 0x0
	srwi. r25, r0, 5
	beq @10
	li r7, 0xf
	@10:
	mr r3, r27
	li r4, 0xf
	li r5, 0x8
	li r6, 0xe
	bl GXSetTevColorIn
	cmpwi r25, 0x0
	mr r3, r27
	li r4, 0x7
	li r5, 0x4
	li r6, 0x6
	li r7, 0x0
	beq @11
	li r7, 0x7
	@11:
	bl GXSetTevAlphaIn
	mr r3, r27
	li r4, 0x0
	li r5, 0x0
	bl GXSetTevSwapMode
	addi r27, r27, 0x1
	addi r26, r26, 0x3
	cmpwi r27, 0x8
	blt @1
	addi r3, r28, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x2
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	li r8, -0x130
	lis r7, 0xcc01
	sth r8, -0x8000(r7)
	li r6, 0xf0
	li r5, 0x0
	li r4, 0x130
	sth r6, -0x8000(r7)
	li r3, 0x1
	li r0, -0xf0
	sth r5, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r4, -0x8000(r7)
	sth r6, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r3, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r4, -0x8000(r7)
	sth r0, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r3, -0x8000(r7)
	sth r3, -0x8000(r7)
	sth r8, -0x8000(r7)
	sth r0, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r5, -0x8000(r7)
	sth r3, -0x8000(r7)
	bl sysWaitDrawSync
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	psq_l f27, 0xc8(r1), 0, 0
	lfd f27, 0xc0(r1)
	psq_l f26, 0xb8(r1), 0, 0
	lfd f26, 0xb0(r1)
	psq_l f25, 0xa8(r1), 0, 0
	lfd f25, 0xa0(r1)
	psq_l f24, 0x98(r1), 0, 0
	lfd f24, 0x90(r1)
	psq_l f23, 0x88(r1), 0, 0
	lfd f23, 0x80(r1)
	lmw r24, 0x60(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}

asm s32 taihou_r(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stfd f29, 0x10(r1)
	psq_st f29, 0x18(r1), 0, 0
	lis r3, double_0p7854_bom_00007088@ha
	lfd f1, double_0p7854_bom_00007088@l(r3)
	bl cos
	lis r3, double_0p7854_bom_00007088@ha
	frsp f31, f1
	lfd f1, double_0p7854_bom_00007088@l(r3)
	bl sin
	lis r3, float_100_bom_00007000@ha
	frsp f2, f1
	lfs f0, float_100_bom_00007000@l(r3)
	lis r4, zero_bom_00007004@ha
	lfs f1, zero_bom_00007004@l(r4)
	fmuls f30, f0, f2
	fmr f2, f1
	fmr f3, f1
	fmr f4, f30
	bl angleABf
	lis r3, float_100_bom_00007000@ha
	lis r4, zero_bom_00007004@ha
	fneg f29, f1
	lfs f0, float_100_bom_00007000@l(r3)
	lfs f1, zero_bom_00007004@l(r4)
	fmr f4, f30
	fmuls f3, f0, f31
	fmr f2, f1
	bl angleABf
	fneg f30, f1
	lis r3, str_000002E4@ha
	addi r3, r3, str_000002E4@l
	bl effNameToPtr
	fmr f1, f29
	fmr f2, f30
	bl effKemuTestSetRxRz
	lis r3, str_000002F8@ha
	addi r3, r3, str_000002F8@l
	bl effNameToPtr
	fmr f1, f29
	fmr f2, f30
	bl effRippleN64SetRxRz
	li r3, 0x2
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	psq_l f29, 0x18(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f29, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm static void ext_dispent(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, lp@ha
	stw r0, 0x14(r1)
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	bne @1
	lis r3, zero_bom_00007004@ha
	lis r4, ext_disp@ha
	addi r6, r3, zero_bom_00007004@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_main(void) {
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
	stmw r17, 0x184(r1)
	lis r3, lp@ha
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r26, 0x0(r3)
	bl extGetPosePtr
	lis r5, str_00000DDC@ha
	lis r4, str_00000E58@ha
	addi r31, r5, str_00000DDC@l
	lis r6, vec3_bom_000064b4@ha
	addi r28, r4, str_00000E58@l
	lis r5, vec3_bom_000064c0@ha
	lis r4, vec3_bom_000064cc@ha
	mr r25, r3
	mr r30, r31
	mr r29, r31
	addi r20, r6, vec3_bom_000064b4@l
	addi r21, r5, vec3_bom_000064c0@l
	addi r22, r4, vec3_bom_000064cc@l
	li r27, 0x0
	li r24, 0x0
	li r23, 0x0
	b @1
	@2:
	lwz r0, 0x0(r20)
	add r17, r26, r23
	lwz r4, 0x4(r20)
	lwz r3, 0x8(r20)
	stw r0, 0xbc(r1)
	lwz r7, 0x0(r21)
	lwz r6, 0x4(r21)
	lwz r0, 0x8(r21)
	stw r4, 0xc0(r1)
	lwz r5, 0x0(r22)
	stw r3, 0xc4(r1)
	lwz r3, 0x4(r22)
	lwz r4, 0xc(r25)
	stw r7, 0x80(r1)
	lfs f1, 0xc(r4)
	stw r6, 0x84(r1)
	lfs f2, 0x1c(r4)
	lfs f0, 0x2c(r4)
	stw r0, 0x88(r1)
	lwz r0, 0x8(r22)
	stfs f1, 0x80(r1)
	stfs f2, 0x84(r1)
	lwz r8, 0x80(r1)
	stfs f0, 0x88(r1)
	lwz r7, 0x84(r1)
	lwz r6, 0x88(r1)
	stw r8, 0xb0(r1)
	stw r7, 0xb4(r1)
	stw r6, 0xb8(r1)
	stw r5, 0xa4(r1)
	stw r3, 0xa8(r1)
	stw r0, 0xac(r1)
	lbz r3, 0xb0(r17)
	extsb r0, r3
	cmpwi r0, 0x5
	beq @3
	bge @4
	cmpwi r0, 0x2
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	bge @8
	b @3
	@6:
	cmpwi r0, 0x4
	bge @9
	b @10
	@4:
	cmpwi r0, 0x7f
	beq @11
	bge @3
	cmpwi r0, 0x64
	beq @12
	b @3
	@7:
	addi r3, r1, 0xbc
	addi r4, r1, 0xb0
	bl PSVECDistance
	lis r3, float_280_bom_000070a4@ha
	lfs f0, float_280_bom_000070a4@l(r3)
	fcmpo cr0, f1, f0
	ble @13
	addi r3, r1, 0xbc
	addi r4, r1, 0xb0
	addi r5, r1, 0x98
	bl PSVECSubtract
	addi r3, r1, 0x98
	mr r4, r3
	bl PSVECNormalize
	lis r4, float_3_bom_000070a8@ha
	addi r3, r1, 0x98
	addi r5, r4, float_3_bom_000070a8@l
	addi r4, r1, 0xa4
	lfs f1, 0x0(r5)
	bl PSVECScale
	addi r3, r1, 0xb0
	addi r4, r1, 0xa4
	mr r5, r3
	bl PSVECAdd
	lfs f0, 0xb0(r1)
	lis r3, zero_bom_00007004@ha
	lwz r4, 0xc(r25)
	lfs f1, zero_bom_00007004@l(r3)
	stfs f0, 0xc(r4)
	fmr f2, f1
	lfs f0, 0xb4(r1)
	lwz r3, 0xc(r25)
	stfs f0, 0x1c(r3)
	lfs f0, 0xb8(r1)
	lwz r3, 0xc(r25)
	stfs f0, 0x2c(r3)
	lfs f3, 0xb0(r1)
	lfs f4, 0xb8(r1)
	bl angleABf
	stfs f1, 0x4(r25)
	b @3
	@13:
	lbz r3, 0xb0(r17)
	addi r0, r3, 0x1
	stb r0, 0xb0(r17)
	b @3
	@8:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x15c(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_6p2832_bom_00007060@ha
	stw r0, 0x158(r1)
	addi r4, r3, float_6p2832_bom_00007060@l
	lfd f2, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x158(r1)
	lfs f1, 0x0(r4)
	fsubs f2, f0, f2
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x164(r1)
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_30_bom_000070b4@ha
	lfd f1, double_to_int_bom_00007030@l(r4)
	stw r0, 0x160(r1)
	addi r5, r3, float_30_bom_000070b4@l
	lis r3, float_32767_bom_000070ac@ha
	lfs f2, 0x0(r5)
	lfd f0, 0x160(r1)
	addi r4, r3, float_32767_bom_000070ac@l
	lis r3, float_150_bom_000070b0@ha
	fsubs f3, f0, f1
	lfs f1, 0x0(r4)
	lfs f0, float_150_bom_000070b0@l(r3)
	fmuls f2, f2, f3
	fdivs f1, f2, f1
	fadds f28, f0, f1
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x16c(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_0p1_bom_00007008@ha
	stw r0, 0x168(r1)
	addi r4, r3, float_0p1_bom_00007008@l
	lfd f1, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x168(r1)
	lfs f2, 0x0(r4)
	fsubs f1, f0, f1
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	fadds f29, f2, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x174(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_32767_bom_000070ac@ha
	stw r0, 0x170(r1)
	addi r4, r3, float_32767_bom_000070ac@l
	lfd f2, 0x0(r5)
	lis r5, float_0p03705_bom_0000707c@ha
	lfd f1, 0x170(r1)
	lis r3, float_3p1416_bom_00007070@ha
	lfs f0, 0x0(r4)
	lis r4, float_3_bom_000070a8@ha
	fsubs f2, f1, f2
	lfs f1, float_3p1416_bom_00007070@l(r3)
	addi r6, r4, float_3_bom_000070a8@l
	lis r4, float_0p4967_bom_00007080@ha
	fcmpo cr0, f27, f1
	lis r3, float_1_bom_00006ffc@ha
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f4, float_0p03705_bom_0000707c@l(r5)
	lfs f3, float_0p4967_bom_00007080@l(r4)
	fadds f30, f0, f2
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @14
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @15
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @16
	@15:
	fsubs f0, f27, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @16
	@14:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @17
	fsubs f0, f27, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @16
	@17:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@16:
	lis r3, float_3p1416_bom_00007070@ha
	fneg f0, f4
	lfs f1, float_3p1416_bom_00007070@l(r3)
	lis r5, float_0p00761_bom_00007068@ha
	lis r4, float_0p16605_bom_0000706c@ha
	lis r3, float_1_bom_00006ffc@ha
	fcmpo cr0, f27, f1
	fmuls f31, f28, f0
	lfs f4, float_0p00761_bom_00007068@l(r5)
	lfs f3, float_0p16605_bom_0000706c@l(r4)
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @18
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @19
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f27
	b @20
	@19:
	fsubs f0, f27, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @20
	@18:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @21
	fsubs f1, f27, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @20
	@21:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@20:
	lis r3, lp@ha
	fmuls f26, f28, f4
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r18, 0x0(r3)
	bl extGetPosePtr
	lis r5, vec3_bom_0000649c@ha
	lis r4, float_150_bom_000070b0@ha
	addi r6, r5, vec3_bom_0000649c@l
	add r19, r3, r24
	lwz r5, 0x0(r6)
	add r17, r18, r23
	lwz r0, 0x4(r6)
	fmr f3, f26
	stw r5, 0x5c(r1)
	fmr f4, f31
	lwz r3, 0x8(r6)
	stfs f26, 0x5c(r1)
	lfs f2, float_150_bom_000070b0@l(r4)
	stw r0, 0x60(r1)
	lwz r0, 0x5c(r1)
	stw r3, 0x64(r1)
	stfs f2, 0x60(r1)
	stfs f31, 0x64(r1)
	lwz r3, 0x60(r1)
	stw r0, 0xb4(r17)
	lwz r0, 0x64(r1)
	stw r3, 0xb8(r17)
	stw r0, 0xbc(r17)
	stfs f30, 0xc0(r17)
	stfs f29, 0xc4(r17)
	lwz r3, 0xc(r19)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f28, f2, f0
	lfs f2, 0x2c(r3)
	bl distABf
	lwz r3, 0xc(r19)
	fmr f27, f1
	fmr f3, f26
	fmr f4, f31
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lfs f0, 0xc0(r17)
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_0p5_bom_0000700c@ha
	fdivs f0, f27, f0
	addi r5, r4, double_to_int_bom_00007030@l
	addi r4, r3, float_0p5_bom_0000700c@l
	stw r0, 0x160(r1)
	lfd f5, 0x0(r5)
	li r3, 0x2
	fctiwz f0, f0
	stw r0, 0x168(r1)
	lfs f3, 0x0(r4)
	li r0, 0x64
	fmr f1, f26
	stfd f0, 0x170(r1)
	fmr f2, f31
	lwz r4, 0x174(r1)
	sth r4, 0xc8(r17)
	lha r4, 0xc8(r17)
	lfs f6, 0xc4(r17)
	xoris r4, r4, 0x8000
	stw r4, 0x164(r1)
	lfd f0, 0x160(r1)
	stw r4, 0x16c(r1)
	fsubs f0, f0, f5
	lfd f4, 0x168(r1)
	fdivs f0, f28, f0
	fsubs f4, f4, f5
	fmuls f4, f6, f4
	fmadds f0, f4, f3, f0
	stfs f0, 0xcc(r17)
	stb r3, 0xb1(r17)
	stb r0, 0xb0(r17)
	lwz r3, 0xc(r19)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	li r3, 0x14
	stfs f1, 0x4(r19)
	divw r0, r27, r3
	mullw r0, r0, r3
	subf. r0, r0, r27
	bne @3
	lhz r0, 0x0(r18)
	clrlwi. r0, r0, 31
	bne @3
	lis r3, vec3_bom_000064a8@ha
	lwz r5, 0xc(r19)
	addi r8, r3, vec3_bom_000064a8@l
	mr r3, r31
	lwz r7, 0x0(r8)
	addi r4, r1, 0x50
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x68(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x6c(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x68(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x70(r1)
	lwz r6, 0x68(r1)
	stfs f1, 0x6c(r1)
	stfs f0, 0x70(r1)
	lwz r5, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r6, 0x50(r1)
	stw r5, 0x54(r1)
	stw r0, 0x58(r1)
	bl psndSFXOn_3D
	b @3
	@5:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x174(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_6p2832_bom_00007060@ha
	stw r0, 0x170(r1)
	addi r4, r3, float_6p2832_bom_00007060@l
	lfd f2, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x170(r1)
	lfs f1, 0x0(r4)
	fsubs f2, f0, f2
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x16c(r1)
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_30_bom_000070b4@ha
	lfd f1, double_to_int_bom_00007030@l(r4)
	stw r0, 0x168(r1)
	addi r5, r3, float_30_bom_000070b4@l
	lis r3, float_32767_bom_000070ac@ha
	lfs f2, 0x0(r5)
	lfd f0, 0x168(r1)
	addi r4, r3, float_32767_bom_000070ac@l
	lis r3, float_50_bom_000070b8@ha
	fsubs f3, f0, f1
	lfs f1, 0x0(r4)
	lfs f0, float_50_bom_000070b8@l(r3)
	fmuls f2, f2, f3
	fdivs f1, f2, f1
	fadds f28, f0, f1
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x164(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_0p1_bom_00007008@ha
	stw r0, 0x160(r1)
	addi r4, r3, float_0p1_bom_00007008@l
	lfd f1, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x160(r1)
	lfs f2, 0x0(r4)
	fsubs f1, f0, f1
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	fadds f31, f2, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x15c(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_32767_bom_000070ac@ha
	stw r0, 0x158(r1)
	addi r4, r3, float_32767_bom_000070ac@l
	lfd f2, 0x0(r5)
	lis r5, float_0p03705_bom_0000707c@ha
	lfd f1, 0x158(r1)
	lis r3, float_3p1416_bom_00007070@ha
	lfs f0, 0x0(r4)
	lis r4, float_3_bom_000070a8@ha
	fsubs f2, f1, f2
	lfs f1, float_3p1416_bom_00007070@l(r3)
	addi r6, r4, float_3_bom_000070a8@l
	lis r4, float_0p4967_bom_00007080@ha
	fcmpo cr0, f27, f1
	lis r3, float_1_bom_00006ffc@ha
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f4, float_0p03705_bom_0000707c@l(r5)
	lfs f3, float_0p4967_bom_00007080@l(r4)
	fadds f30, f0, f2
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @22
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @23
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @24
	@23:
	fsubs f0, f27, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @24
	@22:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @25
	fsubs f0, f27, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @24
	@25:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@24:
	lis r3, float_3p1416_bom_00007070@ha
	fneg f0, f4
	lfs f1, float_3p1416_bom_00007070@l(r3)
	lis r5, float_0p00761_bom_00007068@ha
	lis r4, float_0p16605_bom_0000706c@ha
	lis r3, float_1_bom_00006ffc@ha
	fcmpo cr0, f27, f1
	fmuls f29, f28, f0
	lfs f4, float_0p00761_bom_00007068@l(r5)
	lfs f3, float_0p16605_bom_0000706c@l(r4)
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @26
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @27
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f27
	b @28
	@27:
	fsubs f0, f27, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @28
	@26:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @29
	fsubs f1, f27, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @28
	@29:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@28:
	lis r3, lp@ha
	fmuls f28, f28, f4
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r19, 0x0(r3)
	bl extGetPosePtr
	lis r5, vec3_bom_0000649c@ha
	lis r4, float_400_bom_000070bc@ha
	addi r6, r5, vec3_bom_0000649c@l
	add r18, r3, r24
	lwz r5, 0x0(r6)
	add r17, r19, r23
	lwz r0, 0x4(r6)
	fmr f3, f28
	stw r5, 0x38(r1)
	fmr f4, f29
	lwz r3, 0x8(r6)
	stfs f28, 0x38(r1)
	lfs f2, float_400_bom_000070bc@l(r4)
	stw r0, 0x3c(r1)
	lwz r0, 0x38(r1)
	stw r3, 0x40(r1)
	stfs f2, 0x3c(r1)
	stfs f29, 0x40(r1)
	lwz r3, 0x3c(r1)
	stw r0, 0xb4(r17)
	lwz r0, 0x40(r1)
	stw r3, 0xb8(r17)
	stw r0, 0xbc(r17)
	stfs f30, 0xc0(r17)
	stfs f31, 0xc4(r17)
	lwz r3, 0xc(r18)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f26, f2, f0
	lfs f2, 0x2c(r3)
	bl distABf
	lwz r3, 0xc(r18)
	fmr f27, f1
	fmr f3, f28
	fmr f4, f29
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lfs f0, 0xc0(r17)
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_0p5_bom_0000700c@ha
	fdivs f0, f27, f0
	addi r5, r4, double_to_int_bom_00007030@l
	addi r4, r3, float_0p5_bom_0000700c@l
	stw r0, 0x160(r1)
	lfd f5, 0x0(r5)
	li r3, 0x3
	fctiwz f0, f0
	stw r0, 0x168(r1)
	lfs f3, 0x0(r4)
	li r0, 0x64
	fmr f1, f28
	stfd f0, 0x170(r1)
	fmr f2, f29
	lwz r4, 0x174(r1)
	sth r4, 0xc8(r17)
	lha r4, 0xc8(r17)
	lfs f6, 0xc4(r17)
	xoris r4, r4, 0x8000
	stw r4, 0x164(r1)
	lfd f0, 0x160(r1)
	stw r4, 0x16c(r1)
	fsubs f0, f0, f5
	lfd f4, 0x168(r1)
	fdivs f0, f26, f0
	fsubs f4, f4, f5
	fmuls f4, f6, f4
	fmadds f0, f4, f3, f0
	stfs f0, 0xcc(r17)
	stb r3, 0xb1(r17)
	stb r0, 0xb0(r17)
	lwz r3, 0xc(r18)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	li r3, 0x14
	stfs f1, 0x4(r18)
	divw r0, r27, r3
	mullw r0, r0, r3
	subf. r0, r0, r27
	bne @3
	lhz r0, 0x0(r19)
	clrlwi. r0, r0, 31
	bne @3
	lis r3, vec3_bom_000064a8@ha
	lwz r5, 0xc(r18)
	addi r8, r3, vec3_bom_000064a8@l
	mr r3, r30
	lwz r7, 0x0(r8)
	addi r4, r1, 0x2c
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x44(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x48(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x44(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x4c(r1)
	lwz r6, 0x44(r1)
	stfs f1, 0x48(r1)
	stfs f0, 0x4c(r1)
	lwz r5, 0x48(r1)
	lwz r0, 0x4c(r1)
	stw r6, 0x2c(r1)
	stw r5, 0x30(r1)
	stw r0, 0x34(r1)
	bl psndSFXOn_3D
	b @3
	@10:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x174(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_6p2832_bom_00007060@ha
	stw r0, 0x170(r1)
	addi r4, r3, float_6p2832_bom_00007060@l
	lfd f2, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x170(r1)
	lfs f1, 0x0(r4)
	fsubs f2, f0, f2
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f1, f2
	fdivs f27, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	stw r3, 0x16c(r1)
	addi r5, r4, double_to_int_bom_00007030@l
	lis r3, float_70_bom_000070c0@ha
	stw r0, 0x168(r1)
	addi r4, r3, float_70_bom_000070c0@l
	lfd f2, 0x0(r5)
	lis r3, float_32767_bom_000070ac@ha
	lfd f0, 0x168(r1)
	lfs f1, 0x0(r4)
	fsubs f2, f0, f2
	lfs f0, float_32767_bom_000070ac@l(r3)
	fmuls f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	lis r3, float_0p1_bom_00007008@ha
	lfs f31, float_0p1_bom_00007008@l(r3)
	bl rand
	lis r3, float_3p1416_bom_00007070@ha
	lis r6, float_3_bom_000070a8@ha
	lfs f1, float_3p1416_bom_00007070@l(r3)
	lis r5, float_0p03705_bom_0000707c@ha
	lis r4, float_0p4967_bom_00007080@ha
	lis r3, float_1_bom_00006ffc@ha
	fcmpo cr0, f27, f1
	lfs f30, float_3_bom_000070a8@l(r6)
	lfs f4, float_0p03705_bom_0000707c@l(r5)
	lfs f3, float_0p4967_bom_00007080@l(r4)
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @30
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @31
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @32
	@31:
	fsubs f0, f27, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @32
	@30:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @33
	fsubs f0, f27, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @32
	@33:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@32:
	lis r3, float_3p1416_bom_00007070@ha
	fneg f0, f4
	lfs f1, float_3p1416_bom_00007070@l(r3)
	lis r5, float_0p00761_bom_00007068@ha
	lis r4, float_0p16605_bom_0000706c@ha
	lis r3, float_1_bom_00006ffc@ha
	fcmpo cr0, f27, f1
	fmuls f29, f28, f0
	lfs f4, float_0p00761_bom_00007068@l(r5)
	lfs f3, float_0p16605_bom_0000706c@l(r4)
	lfs f2, float_1_bom_00006ffc@l(r3)
	cror eq, lt, eq
	bne @34
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f27, f1
	cror eq, lt, eq
	bne @35
	fmuls f0, f27, f27
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f27
	b @36
	@35:
	fsubs f0, f27, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @36
	@34:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f27, f0
	bge @37
	fsubs f1, f27, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @36
	@37:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f27, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@36:
	li r6, 0x64
	lis r0, 0x4330
	divw r5, r27, r6
	stw r0, 0x170(r1)
	lis r3, double_to_int_bom_00007030@ha
	lis r7, float_100_bom_00007000@ha
	addi r4, r3, double_to_int_bom_00007030@l
	lfs f2, float_100_bom_00007000@l(r7)
	mullw r0, r5, r6
	lis r3, lp@ha
	lfd f1, 0x0(r4)
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	subf r0, r0, r27
	xoris r0, r0, 0x8000
	lwz r19, 0x0(r3)
	stw r0, 0x174(r1)
	lfd f0, 0x170(r1)
	fsubs f0, f0, f1
	fadds f0, f2, f0
	fmadds f28, f28, f4, f0
	bl extGetPosePtr
	li r6, 0x96
	lis r0, 0x4330
	divw r5, r27, r6
	stw r0, 0x168(r1)
	lis r4, double_to_int_bom_00007030@ha
	fmr f3, f28
	lis r7, vec3_bom_0000649c@ha
	lfd f1, double_to_int_bom_00007030@l(r4)
	mullw r0, r5, r6
	addi r8, r7, vec3_bom_0000649c@l
	lis r5, float_350_bom_000070c4@ha
	lwz r7, 0x0(r8)
	lwz r6, 0x4(r8)
	add r18, r3, r24
	subf r0, r0, r27
	stw r7, 0x14(r1)
	xoris r0, r0, 0x8000
	lwz r3, 0x8(r8)
	stw r0, 0x16c(r1)
	add r17, r19, r23
	lfs f2, float_350_bom_000070c4@l(r5)
	fmr f4, f29
	lfd f0, 0x168(r1)
	stfs f28, 0x14(r1)
	fsubs f0, f0, f1
	lwz r0, 0x14(r1)
	stw r6, 0x18(r1)
	fadds f2, f2, f0
	stw r3, 0x1c(r1)
	stfs f2, 0x18(r1)
	stfs f29, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0xb4(r17)
	lwz r0, 0x1c(r1)
	stw r3, 0xb8(r17)
	stw r0, 0xbc(r17)
	stfs f30, 0xc0(r17)
	stfs f31, 0xc4(r17)
	lwz r3, 0xc(r18)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f26, f2, f0
	lfs f2, 0x2c(r3)
	bl distABf
	lwz r3, 0xc(r18)
	fmr f27, f1
	fmr f3, f28
	fmr f4, f29
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lfs f0, 0xc0(r17)
	lis r0, 0x4330
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_0p5_bom_0000700c@ha
	fdivs f0, f27, f0
	addi r5, r4, double_to_int_bom_00007030@l
	addi r4, r3, float_0p5_bom_0000700c@l
	stw r0, 0x178(r1)
	lfd f5, 0x0(r5)
	li r3, 0x4
	fctiwz f0, f0
	stw r0, 0x158(r1)
	lfs f3, 0x0(r4)
	li r0, 0x64
	fmr f1, f28
	stfd f0, 0x160(r1)
	fmr f2, f29
	lwz r4, 0x164(r1)
	sth r4, 0xc8(r17)
	lha r4, 0xc8(r17)
	lfs f6, 0xc4(r17)
	xoris r4, r4, 0x8000
	stw r4, 0x17c(r1)
	lfd f0, 0x178(r1)
	stw r4, 0x15c(r1)
	fsubs f0, f0, f5
	lfd f4, 0x158(r1)
	fdivs f0, f26, f0
	fsubs f4, f4, f5
	fmuls f4, f6, f4
	fmadds f0, f4, f3, f0
	stfs f0, 0xcc(r17)
	stb r3, 0xb1(r17)
	stb r0, 0xb0(r17)
	lwz r3, 0xc(r18)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	li r3, 0x14
	stfs f1, 0x4(r18)
	divw r0, r27, r3
	mullw r0, r0, r3
	subf. r0, r0, r27
	bne @3
	lhz r0, 0x0(r19)
	clrlwi. r0, r0, 31
	bne @3
	lis r3, vec3_bom_000064a8@ha
	lwz r5, 0xc(r18)
	addi r8, r3, vec3_bom_000064a8@l
	mr r3, r29
	lwz r7, 0x0(r8)
	addi r4, r1, 0x8
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x20(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x24(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x20(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x28(r1)
	lwz r6, 0x20(r1)
	stfs f1, 0x24(r1)
	stfs f0, 0x28(r1)
	lwz r5, 0x24(r1)
	lwz r0, 0x28(r1)
	stw r6, 0x8(r1)
	stw r5, 0xc(r1)
	stw r0, 0x10(r1)
	bl psndSFXOn_3D
	b @3
	@9:
	addi r0, r3, 0x1
	stb r0, 0xb0(r17)
	b @3
	@12:
	lfs f0, 0xcc(r17)
	fadds f0, f2, f0
	stfs f0, 0x1c(r4)
	lfs f1, 0xcc(r17)
	lfs f0, 0xc4(r17)
	fsubs f0, f1, f0
	stfs f0, 0xcc(r17)
	lwz r3, 0xc(r25)
	lfs f3, 0xb4(r17)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0xbc(r17)
	bl angleABf
	lis r4, float_3p1416_bom_00007070@ha
	lis r3, float_180_bom_000070c8@ha
	lfs f2, float_3p1416_bom_00007070@l(r4)
	addi r6, r3, float_180_bom_000070c8@l
	lis r5, float_0p00761_bom_00007068@ha
	lis r4, float_0p16605_bom_0000706c@ha
	fmuls f1, f2, f1
	lfs f0, 0x0(r6)
	lis r3, float_1_bom_00006ffc@ha
	lfs f5, float_0p00761_bom_00007068@l(r5)
	lfs f4, float_0p16605_bom_0000706c@l(r4)
	fdivs f6, f1, f0
	lfs f3, float_1_bom_00006ffc@l(r3)
	fcmpo cr0, f6, f2
	cror eq, lt, eq
	bne @38
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @39
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b @40
	@39:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @40
	@38:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f6, f0
	bge @41
	fsubs f1, f6, f2
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @40
	@41:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@40:
	lwz r7, 0xc(r25)
	lis r3, float_3p1416_bom_00007070@ha
	lfs f1, float_3p1416_bom_00007070@l(r3)
	lis r6, float_0p03705_bom_0000707c@ha
	lfs f2, 0xc0(r17)
	lis r5, float_0p4967_bom_00007080@ha
	lfs f0, 0xc(r7)
	fcmpo cr0, f6, f1
	lis r4, float_1_bom_00006ffc@ha
	lfs f4, float_0p03705_bom_0000707c@l(r6)
	fmadds f0, f2, f5, f0
	lfs f3, float_0p4967_bom_00007080@l(r5)
	lfs f2, float_1_bom_00006ffc@l(r4)
	stfs f0, 0xc(r7)
	cror eq, lt, eq
	bne @42
	lis r3, float_1p5708_bom_00007074@ha
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @43
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @44
	@43:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @44
	@42:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f0, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f6, f0
	bge @45
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @44
	@45:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_bom_00007074@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@44:
	lwz r3, 0xc(r25)
	fneg f1, f4
	lfs f2, 0xc0(r17)
	lfs f0, 0x2c(r3)
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0xc8(r17)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0xc8(r17)
	bge @3
	lfs f0, 0xb4(r17)
	lwz r3, 0xc(r25)
	stfs f0, 0xc(r3)
	lfs f0, 0xb8(r17)
	lwz r3, 0xc(r25)
	stfs f0, 0x1c(r3)
	lfs f0, 0xbc(r17)
	lwz r3, 0xc(r25)
	stfs f0, 0x2c(r3)
	lbz r0, 0xb1(r17)
	stb r0, 0xb0(r17)
	b @3
	@11:
	lis r3, float_neg1000_bom_000070cc@ha
	lfs f0, float_neg1000_bom_000070cc@l(r3)
	fcmpo cr0, f2, f0
	ble @3
	lis r3, float_2_bom_0000704c@ha
	lis r5, zero_bom_00007004@ha
	addi r6, r3, float_2_bom_0000704c@l
	lfs f1, zero_bom_00007004@l(r5)
	lfs f0, 0x0(r6)
	lis r3, float_neg20_bom_000070d0@ha
	fmr f3, f1
	fsubs f0, f2, f0
	lfs f2, float_neg20_bom_000070d0@l(r3)
	addi r3, r1, 0x128
	stfs f0, 0x1c(r4)
	lwz r0, 0x0(r25)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r25)
	bl PSMTXTrans
	lis r3, gp@ha
	lis r0, 0x4330
	addi r4, r3, gp@l
	stw r0, 0x178(r1)
	lwz r5, 0x0(r4)
	lis r3, double_to_int_mask_bom_000070e0@ha
	addi r4, r3, double_to_int_mask_bom_000070e0@l
	lwz r0, 0x1c(r5)
	lis r3, float_100_bom_00007000@ha
	lfd f2, 0x0(r4)
	add r0, r27, r0
	lfs f0, float_100_bom_00007000@l(r3)
	stw r0, 0x17c(r1)
	lfd f1, 0x178(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	bl sin
	lis r3, float_10_bom_00007010@ha
	frsp f2, f1
	lfs f0, float_10_bom_00007010@l(r3)
	lis r4, float_deg2rad_bom_000070d4@ha
	lfs f1, float_deg2rad_bom_000070d4@l(r4)
	addi r3, r1, 0xf8
	fmuls f0, f0, f2
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lis r3, zero_bom_00007004@ha
	lis r4, float_20_bom_000070d8@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f2, float_20_bom_000070d8@l(r4)
	lfs f1, 0x0(r5)
	addi r3, r1, 0xc8
	fmr f3, f1
	bl PSMTXTrans
	addi r4, r1, 0xf8
	addi r3, r1, 0x128
	mr r5, r4
	bl PSMTXConcat
	addi r4, r1, 0xc8
	addi r3, r1, 0xf8
	mr r5, r4
	bl PSMTXConcat
	lwz r4, 0xc(r25)
	addi r3, r1, 0x128
	lfs f1, 0xc(r4)
	lfs f2, 0x1c(r4)
	lfs f3, 0x2c(r4)
	bl PSMTXTrans
	lwz r5, 0xc(r25)
	addi r3, r1, 0x128
	addi r4, r1, 0xc8
	bl PSMTXConcat
	li r3, 0x64
	bl irand
	cmpwi r3, 0x0
	bne @3
	lis r3, vec3_bom_000064d8@ha
	lwz r5, 0xc(r25)
	addi r8, r3, vec3_bom_000064d8@l
	mr r3, r28
	lwz r7, 0x0(r8)
	addi r4, r1, 0x8c
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x74(r1)
	lfs f0, 0xc(r5)
	stw r6, 0x78(r1)
	lfs f1, 0x1c(r5)
	stfs f0, 0x74(r1)
	lfs f0, 0x2c(r5)
	stw r0, 0x7c(r1)
	lwz r6, 0x74(r1)
	stfs f1, 0x78(r1)
	stfs f0, 0x7c(r1)
	lwz r5, 0x78(r1)
	lwz r0, 0x7c(r1)
	stw r6, 0x8c(r1)
	stw r5, 0x90(r1)
	stw r0, 0x94(r1)
	bl psndSFXOn_3D
	@3:
	addi r27, r27, 0x1
	addi r24, r24, 0x20
	addi r23, r23, 0x30
	addi r25, r25, 0x20
	@1:
	lwz r0, 0x4(r26)
	cmpw r27, r0
	blt @2
	lis r3, lp@ha
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r20, 0x0(r3)
	bl extGetPosePtr
	lis r7, float_60_bom_000070dc@ha
	lis r6, float_1000_bom_0000705c@ha
	lis r5, float_1_bom_00006ffc@ha
	lis r4, double_to_int_bom_00007030@ha
	lis r8, gp@ha
	lfs f30, float_60_bom_000070dc@l(r7)
	lfs f29, float_1000_bom_0000705c@l(r6)
	mr r18, r3
	lfs f28, float_1_bom_00006ffc@l(r5)
	addi r24, r8, gp@l
	lfd f27, double_to_int_bom_00007030@l(r4)
	li r19, 0x0
	li r25, 0x0
	lis r23, 0x8000
	lis r26, 0x4330
	b @46
	@47:
	lwz r3, 0xf8(r23)
	add r17, r20, r25
	lwz r4, 0x0(r24)
	li r0, 0x3e8
	srwi r3, r3, 2
	lwz r7, 0xd0(r17)
	divwu r6, r3, r0
	lwz r22, 0x3c(r4)
	lwz r0, 0xdc(r17)
	li r5, 0x0
	lwz r21, 0x38(r4)
	subfc r4, r0, r22
	mulli r7, r7, 0x14
	lwz r0, 0xd8(r17)
	subfe r3, r0, r21
	addi r27, r7, 0x8
	add r27, r20, r27
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f30, f1
	lfs f0, 0x8(r27)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f28
	cror eq, gt, eq
	bne @48
	stw r22, 0xdc(r17)
	lis r3, zero_bom_00007004@ha
	lfs f1, zero_bom_00007004@l(r3)
	stw r21, 0xd8(r17)
	@48:
	lwz r3, 0x10(r27)
	addi r19, r19, 0x1
	stw r26, 0x178(r1)
	addi r25, r25, 0x30
	subi r0, r3, 0x1
	lwz r3, 0xc(r27)
	xoris r0, r0, 0x8000
	stw r0, 0x17c(r1)
	lfd f0, 0x178(r1)
	fsubs f0, f0, f27
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x170(r1)
	lwz r0, 0x174(r1)
	add r0, r3, r0
	stw r0, 0x10(r18)
	addi r18, r18, 0x20
	@46:
	lwz r0, 0x4(r20)
	cmpw r19, r0
	blt @47
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
	lmw r17, 0x184(r1)
	lwz r0, 0x224(r1)
	mtlr r0
	addi r1, r1, 0x220
	blr
}

asm void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stfd f27, 0x60(r1)
	psq_st f27, 0x68(r1), 0, 0
	stmw r26, 0x48(r1)
	lis r5, lp@ha
	fmr f27, f1
	addi r5, r5, lp@l
	fmr f28, f2
	lwz r5, 0x0(r5)
	fmr f29, f3
	fmr f31, f4
	fmr f30, f5
	lwz r30, 0x0(r5)
	mr r27, r3
	mr r28, r4
	bl extGetPosePtr
	lis r4, vec3_bom_0000649c@ha
	slwi r6, r27, 5
	addi r5, r4, vec3_bom_0000649c@l
	fmr f3, f27
	lwz r0, 0x0(r5)
	mulli r31, r27, 0x30
	lwz r4, 0x4(r5)
	add r29, r3, r6
	stw r0, 0x14(r1)
	lwz r0, 0x8(r5)
	add r26, r30, r31
	stw r4, 0x18(r1)
	fmr f4, f29
	stfs f27, 0x14(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f28, 0x18(r1)
	stfs f29, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0xb4(r26)
	lwz r0, 0x1c(r1)
	stw r3, 0xb8(r26)
	stw r0, 0xbc(r26)
	stfs f31, 0xc0(r26)
	stfs f30, 0xc4(r26)
	lwz r3, 0xc(r29)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f30, f28, f0
	lfs f2, 0x2c(r3)
	bl distABf
	lwz r3, 0xc(r29)
	fmr f31, f1
	fmr f3, f27
	fmr f4, f29
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lfs f0, 0xc0(r26)
	lis r4, 0x4330
	lis r3, float_0p5_bom_0000700c@ha
	lis r5, double_to_int_bom_00007030@ha
	fdivs f0, f31, f0
	lfs f3, float_0p5_bom_0000700c@l(r3)
	stw r4, 0x40(r1)
	li r0, 0x64
	lfd f5, double_to_int_bom_00007030@l(r5)
	stw r4, 0x38(r1)
	fctiwz f0, f0
	fmr f1, f27
	fmr f2, f29
	stfd f0, 0x30(r1)
	lwz r3, 0x34(r1)
	sth r3, 0xc8(r26)
	lha r3, 0xc8(r26)
	lfs f6, 0xc4(r26)
	xoris r3, r3, 0x8000
	stw r3, 0x44(r1)
	lfd f0, 0x40(r1)
	stw r3, 0x3c(r1)
	fsubs f0, f0, f5
	lfd f4, 0x38(r1)
	fdivs f0, f30, f0
	fsubs f4, f4, f5
	fmuls f4, f6, f4
	fmadds f0, f4, f3, f0
	stfs f0, 0xcc(r26)
	stb r28, 0xb1(r26)
	stb r0, 0xb0(r26)
	lwz r3, 0xc(r29)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	li r3, 0x14
	stfs f1, 0x4(r29)
	divw r0, r27, r3
	mullw r0, r0, r3
	subf. r0, r0, r27
	bne @1
	lhz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	bne @1
	lis r3, vec3_bom_000064a8@ha
	lwz r7, 0xc(r29)
	addi r4, r3, vec3_bom_000064a8@l
	lwz r6, 0x0(r4)
	lis r3, str_00000DDC@ha
	lwz r5, 0x4(r4)
	addi r3, r3, str_00000DDC@l
	lwz r0, 0x8(r4)
	addi r4, r1, 0x20
	stw r6, 0x8(r1)
	lfs f0, 0xc(r7)
	stw r5, 0xc(r1)
	lfs f1, 0x1c(r7)
	stfs f0, 0x8(r1)
	lfs f0, 0x2c(r7)
	stw r0, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r6, 0x20(r1)
	stw r5, 0x24(r1)
	stw r0, 0x28(r1)
	bl psndSFXOn_3D
	@1:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	psq_l f27, 0x68(r1), 0, 0
	lfd f27, 0x60(r1)
	lmw r26, 0x48(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm static void ext_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	bl extDraw
	bl extLoadTextureExit
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_init(void) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stfd f31, 0x110(r1)
	psq_st f31, 0x118(r1), 0, 0
	stfd f30, 0x100(r1)
	psq_st f30, 0x108(r1), 0, 0
	stfd f29, 0xf0(r1)
	psq_st f29, 0xf8(r1), 0, 0
	stfd f28, 0xe0(r1)
	psq_st f28, 0xe8(r1), 0, 0
	stfd f27, 0xd0(r1)
	psq_st f27, 0xd8(r1), 0, 0
	stfd f26, 0xc0(r1)
	psq_st f26, 0xc8(r1), 0, 0
	stfd f25, 0xb0(r1)
	psq_st f25, 0xb8(r1), 0, 0
	stfd f24, 0xa0(r1)
	psq_st f24, 0xa8(r1), 0, 0
	stfd f23, 0x90(r1)
	psq_st f23, 0x98(r1), 0, 0
	stfd f22, 0x80(r1)
	psq_st f22, 0x88(r1), 0, 0
	stfd f21, 0x70(r1)
	psq_st f21, 0x78(r1), 0, 0
	stmw r20, 0x40(r1)
	lis r3, 0x1
	li r4, 0x1
	subi r3, r3, 0x43d0
	bl smartAlloc
	lis r4, lp@ha
	lis r5, 0x1
	addi r6, r4, lp@l
	li r4, 0x0
	stw r3, 0x0(r6)
	subi r5, r5, 0x43d0
	lwz r24, 0x0(r3)
	mr r3, r24
	bl memset
	bl extGetPoseNum
	stw r3, 0x4(r24)
	lis r3, lp@ha
	addi r4, r3, lp@l
	li r28, 0x0
	lwz r5, 0x0(r4)
	lis r3, ext_data@ha
	lis r4, zero_bom_00007038@ha
	lwz r30, 0x0(r5)
	addi r29, r3, ext_data@l
	addi r3, r1, 0x8
	addi r4, r4, zero_bom_00007038@l
	bl strcpy
	li r0, -0x1
	stw r0, 0xa8(r30)
	@1:
	lwz r3, 0x4(r29)
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x4(r29)
	addi r3, r1, 0x8
	bl strcpy
	lwz r3, 0xa8(r30)
	mr r27, r28
	addi r0, r3, 0x1
	stw r0, 0xa8(r30)
	@2:
	lwz r0, 0xa8(r30)
	addi r4, r1, 0x8
	mulli r3, r0, 0x14
	addi r3, r3, 0x8
	add r3, r30, r3
	bl strcpy
	lwz r0, 0xa8(r30)
	subf r3, r27, r28
	addi r4, r3, 0x1
	addi r28, r28, 0x1
	mulli r3, r0, 0x14
	addi r0, r3, 0x14
	stwx r27, r30, r0
	lwz r0, 0xa8(r30)
	mulli r3, r0, 0x14
	addi r0, r3, 0x18
	stwx r4, r30, r0
	lwz r0, 0xa8(r30)
	lfs f0, 0x8(r29)
	mulli r3, r0, 0x14
	addi r0, r3, 0x10
	stfsx f0, r30, r0
	lwzu r0, 0xc(r29)
	cmplwi r0, 0x0
	bne @1
	lwz r3, 0xa8(r30)
	addi r0, r3, 0x1
	stw r0, 0xa8(r30)
	bl extGetPosePtr
	lis r22, zero_bom_00007004@ha
	lis r12, double_to_int_bom_00007030@ha
	lis r11, float_6p2832_bom_00007060@ha
	lis r10, float_32767_bom_000070ac@ha
	addi r26, r11, float_6p2832_bom_00007060@l
	addi r27, r22, zero_bom_00007004@l
	lis r9, float_400_bom_000070bc@ha
	addi r23, r12, double_to_int_bom_00007030@l
	lis r8, float_500_bom_000070e8@ha
	addi r25, r10, float_32767_bom_000070ac@l
	lis r7, float_0p16605_bom_0000706c@ha
	addi r22, r9, float_400_bom_000070bc@l
	addi r10, r7, float_0p16605_bom_0000706c@l
	lis r6, float_1_bom_00006ffc@ha
	addi r12, r8, float_500_bom_000070e8@l
	lis r5, float_3p1416_bom_00007070@ha
	addi r8, r5, float_3p1416_bom_00007070@l
	addi r9, r6, float_1_bom_00006ffc@l
	lis r4, float_0p4967_bom_00007080@ha
	lis r11, float_0p00761_bom_00007068@ha
	addi r6, r4, float_0p4967_bom_00007080@l
	lis r7, float_0p03705_bom_0000707c@ha
	lis r4, str_00000E10@ha
	lis r5, lp@ha
	lfs f25, 0x0(r27)
	addi r31, r4, str_00000E10@l
	lfd f26, 0x0(r23)
	mr r23, r3
	lfs f28, 0x0(r25)
	addi r28, r11, float_0p00761_bom_00007068@l
	lfs f29, 0x0(r22)
	addi r29, r7, float_0p03705_bom_0000707c@l
	lfs f27, 0x0(r26)
	addi r30, r5, lp@l
	lfs f30, 0x0(r12)
	li r25, 0x0
	lfs f23, 0x0(r10)
	li r22, 0x0
	lfs f24, 0x0(r9)
	lis r27, 0x4330
	lfs f31, 0x0(r8)
	lfs f22, 0x0(r6)
	b @3
	@4:
	add r3, r24, r22
	li r0, 0x0
	stfs f25, 0xcc(r3)
	stfs f25, 0xc4(r3)
	stb r0, 0xb0(r3)
	lwz r0, 0x0(r23)
	ori r0, r0, 0x7
	stw r0, 0x0(r23)
	lwz r3, 0xc(r23)
	bl PSMTXIdentity
	bl rand
	xoris r0, r3, 0x8000
	stw r27, 0x28(r1)
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f26
	fmuls f0, f27, f0
	fdivs f21, f0, f28
	bl rand
	xoris r0, r3, 0x8000
	stw r27, 0x30(r1)
	fcmpo cr0, f21, f31
	lfs f3, 0x0(r28)
	stw r0, 0x34(r1)
	lfd f0, 0x30(r1)
	fsubs f0, f0, f26
	fmuls f0, f29, f0
	fdivs f0, f0, f28
	fadds f0, f30, f0
	cror eq, lt, eq
	bne @5
	lis r3, float_1p5708_bom_00007074@ha
	lfs f2, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f21, f2
	cror eq, lt, eq
	bne @6
	fmuls f1, f21, f21
	fmsubs f3, f3, f1, f23
	fmadds f3, f3, f1, f24
	fmuls f3, f3, f21
	b @7
	@6:
	fsubs f1, f21, f2
	fsubs f2, f2, f1
	fmuls f1, f2, f2
	fmsubs f3, f3, f1, f23
	fmadds f3, f3, f1, f24
	fmuls f3, f3, f2
	b @7
	@5:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f1, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f21, f1
	bge @8
	lis r3, float_3p1416_bom_00007070@ha
	lfs f1, float_3p1416_bom_00007070@l(r3)
	fsubs f2, f21, f1
	fmuls f1, f2, f2
	fmsubs f3, f3, f1, f23
	fmadds f3, f3, f1, f24
	fmuls f3, f3, f2
	fneg f3, f3
	b @7
	@8:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f1, f21, f1
	lfs f2, float_1p5708_bom_00007074@l(r3)
	fsubs f2, f2, f1
	fmuls f1, f2, f2
	fmsubs f3, f3, f1, f23
	fmadds f3, f3, f1, f24
	fmuls f3, f3, f2
	fneg f3, f3
	@7:
	fmuls f1, f0, f3
	lwz r3, 0xc(r23)
	fcmpo cr0, f21, f31
	lfs f3, 0x0(r29)
	stfs f1, 0xc(r3)
	lwz r3, 0xc(r23)
	stfs f25, 0x1c(r3)
	cror eq, lt, eq
	bne @9
	lis r3, float_1p5708_bom_00007074@ha
	lfs f2, float_1p5708_bom_00007074@l(r3)
	fcmpo cr0, f21, f2
	cror eq, lt, eq
	bne @10
	fmuls f1, f21, f21
	fmsubs f3, f3, f1, f22
	fmadds f3, f3, f1, f24
	b @11
	@10:
	fsubs f1, f21, f2
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f3, f3, f1, f22
	fmadds f3, f3, f1, f24
	fneg f3, f3
	b @11
	@9:
	lis r3, float_4p7124_bom_00007078@ha
	lfs f1, float_4p7124_bom_00007078@l(r3)
	fcmpo cr0, f21, f1
	bge @12
	lis r3, float_3p1416_bom_00007070@ha
	lfs f1, float_3p1416_bom_00007070@l(r3)
	fsubs f1, f21, f1
	fmuls f1, f1, f1
	fmsubs f3, f3, f1, f22
	fmadds f3, f3, f1, f24
	fneg f3, f3
	b @11
	@12:
	lis r3, float_1p5708_bom_00007074@ha
	fsubs f1, f21, f1
	lfs f2, float_1p5708_bom_00007074@l(r3)
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f3, f3, f1, f22
	fmadds f3, f3, f1, f24
	@11:
	fmuls f0, f0, f3
	lwz r3, 0xc(r23)
	li r21, 0x0
	stfs f0, 0x2c(r3)
	lwz r3, 0x0(r30)
	lwz r20, 0x0(r3)
	addi r26, r20, 0x8
	b @13
	@14:
	mr r3, r26
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	addi r21, r21, 0x1
	addi r26, r26, 0x14
	@13:
	lwz r0, 0xa8(r20)
	cmpw r21, r0
	blt @14
	@15:
	lwz r0, 0xa8(r20)
	cmpw r21, r0
	bge @16
	add r26, r20, r22
	lwz r0, 0xd0(r26)
	cmpw r0, r21
	beq @16
	extsh r0, r21
	stw r0, 0xd0(r26)
	bl rand
	lis r4, gp@ha
	srawi r0, r3, 31
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r5, 0x3c(r4)
	lwz r4, 0x38(r4)
	addc r3, r5, r3
	stw r3, 0xdc(r26)
	adde r0, r4, r0
	stw r0, 0xd8(r26)
	@16:
	addi r25, r25, 0x1
	addi r22, r22, 0x30
	addi r23, r23, 0x20
	@3:
	lwz r0, 0x4(r24)
	cmpw r25, r0
	blt @4
	psq_l f31, 0x118(r1), 0, 0
	lfd f31, 0x110(r1)
	psq_l f30, 0x108(r1), 0, 0
	lfd f30, 0x100(r1)
	psq_l f29, 0xf8(r1), 0, 0
	lfd f29, 0xf0(r1)
	psq_l f28, 0xe8(r1), 0, 0
	lfd f28, 0xe0(r1)
	psq_l f27, 0xd8(r1), 0, 0
	lfd f27, 0xd0(r1)
	psq_l f26, 0xc8(r1), 0, 0
	lfd f26, 0xc0(r1)
	psq_l f25, 0xb8(r1), 0, 0
	lfd f25, 0xb0(r1)
	psq_l f24, 0xa8(r1), 0, 0
	lfd f24, 0xa0(r1)
	psq_l f23, 0x98(r1), 0, 0
	lfd f23, 0x90(r1)
	psq_l f22, 0x88(r1), 0, 0
	lfd f22, 0x80(r1)
	psq_l f21, 0x78(r1), 0, 0
	lfd f21, 0x70(r1)
	lmw r20, 0x40(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm s32 make_ext_table(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, ext_data@ha
	li r4, 0x0
	stw r0, 0x14(r1)
	addi r3, r3, ext_data@l
	li r5, 0x174
	bl memset
	lis r4, float_2_bom_0000704c@ha
	lis r3, double_to_int_bom_00007030@ha
	lis r7, str_000002B4@ha
	lis r6, ext_data@ha
	lis r5, str_00000E10@ha
	lfs f2, float_2_bom_0000704c@l(r4)
	lfd f1, double_to_int_bom_00007030@l(r3)
	li r0, 0xa
	addi r7, r7, str_000002B4@l
	addi r6, r6, ext_data@l
	addi r5, r5, str_00000E10@l
	li r9, 0x0
	li r3, 0x0
	lis r4, 0x4330
	mtctr r0
	@1:
	xoris r0, r9, 0x8000
	add r8, r6, r3
	stw r0, 0xc(r1)
	addi r9, r9, 0x1
	addi r3, r3, 0xc
	stw r4, 0x8(r1)
	lfd f0, 0x8(r1)
	stw r7, 0x0(r8)
	fsubs f0, f0, f1
	stw r5, 0x4(r8)
	fmuls f0, f2, f0
	stfs f0, 0x8(r8)
	bdnz @1
	lis r4, float_6_bom_000070f0@ha
	lis r3, double_to_int_bom_00007030@ha
	lis r7, str_000002B4@ha
	lis r6, ext_data@ha
	lis r5, str_00000EB4@ha
	lfs f2, float_6_bom_000070f0@l(r4)
	lfd f1, double_to_int_bom_00007030@l(r3)
	li r0, 0x14
	addi r7, r7, str_000002B4@l
	addi r6, r6, ext_data@l
	addi r5, r5, str_00000EB4@l
	li r9, 0x0
	li r3, 0x0
	lis r4, 0x4330
	mtctr r0
	@2:
	xoris r0, r9, 0x8000
	add r8, r6, r3
	stw r0, 0xc(r1)
	addi r9, r9, 0x1
	addi r3, r3, 0xc
	stw r4, 0x8(r1)
	lfd f0, 0x8(r1)
	stw r7, 0x78(r8)
	fsubs f0, f0, f1
	stw r5, 0x7c(r8)
	fmuls f0, f2, f0
	stfs f0, 0x80(r8)
	bdnz @2
	lis r3, ext_data@ha
	li r0, 0x0
	addi r4, r3, ext_data@l
	li r3, 0x2
	stw r0, 0x168(r4)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void pose_change(s32 i, const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, lp@ha
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	addi r3, r5, lp@l
	mr r28, r4
	li r29, 0x0
	lwz r3, 0x0(r3)
	lwz r30, 0x0(r3)
	addi r31, r30, 0x8
	b @1
	@2:
	mr r3, r31
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	addi r29, r29, 0x1
	addi r31, r31, 0x14
	@1:
	lwz r0, 0xa8(r30)
	cmpw r29, r0
	blt @2
	@3:
	lwz r0, 0xa8(r30)
	cmpw r29, r0
	bge @4
	mulli r31, r27, 0x30
	add r3, r30, r31
	lwz r0, 0xd0(r3)
	cmpw r0, r29
	beq @4
	extsh r0, r29
	stw r0, 0xd0(r3)
	bl rand
	lis r4, gp@ha
	srawi r0, r3, 31
	addi r5, r4, gp@l
	add r4, r30, r31
	lwz r5, 0x0(r5)
	lwz r6, 0x3c(r5)
	lwz r5, 0x38(r5)
	addc r3, r6, r3
	stw r3, 0xdc(r4)
	adde r0, r5, r0
	stw r0, 0xd8(r4)
	@4:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void pose_main(void) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	stw r0, 0x94(r1)
	stfd f31, 0x80(r1)
	psq_st f31, 0x88(r1), 0, 0
	stfd f30, 0x70(r1)
	psq_st f30, 0x78(r1), 0, 0
	stfd f29, 0x60(r1)
	psq_st f29, 0x68(r1), 0, 0
	stfd f28, 0x50(r1)
	psq_st f28, 0x58(r1), 0, 0
	stmw r21, 0x24(r1)
	lis r3, lp@ha
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r26, 0x0(r3)
	bl extGetPosePtr
	lis r7, float_60_bom_000070dc@ha
	lis r6, float_1000_bom_0000705c@ha
	lis r5, float_1_bom_00006ffc@ha
	lis r4, double_to_int_bom_00007030@ha
	lis r8, gp@ha
	lfs f28, float_60_bom_000070dc@l(r7)
	lfs f29, float_1000_bom_0000705c@l(r6)
	mr r24, r3
	lfs f30, float_1_bom_00006ffc@l(r5)
	addi r30, r8, gp@l
	lfd f31, double_to_int_bom_00007030@l(r4)
	li r25, 0x0
	li r23, 0x0
	lis r31, 0x8000
	lis r22, 0x4330
	b @1
	@2:
	lwz r3, 0xf8(r31)
	add r29, r26, r23
	lwz r4, 0x0(r30)
	li r0, 0x3e8
	srwi r3, r3, 2
	lwz r7, 0xd0(r29)
	divwu r6, r3, r0
	lwz r27, 0x3c(r4)
	lwz r0, 0xdc(r29)
	li r5, 0x0
	lwz r28, 0x38(r4)
	subfc r4, r0, r27
	mulli r7, r7, 0x14
	lwz r0, 0xd8(r29)
	subfe r3, r0, r28
	addi r21, r7, 0x8
	add r21, r26, r21
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f28, f1
	lfs f0, 0x8(r21)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f30
	cror eq, gt, eq
	bne @3
	stw r27, 0xdc(r29)
	lis r3, zero_bom_00007004@ha
	lfs f1, zero_bom_00007004@l(r3)
	stw r28, 0xd8(r29)
	@3:
	lwz r3, 0x10(r21)
	addi r25, r25, 0x1
	stw r22, 0x8(r1)
	addi r23, r23, 0x30
	subi r0, r3, 0x1
	lwz r3, 0xc(r21)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f31
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	add r0, r3, r0
	stw r0, 0x10(r24)
	addi r24, r24, 0x20
	@1:
	lwz r0, 0x4(r26)
	cmpw r25, r0
	blt @2
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	lmw r21, 0x24(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm static void pose_init(void) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r3, lp@ha
	lis r4, ext_data@ha
	stw r0, 0x44(r1)
	addi r5, r3, lp@l
	lis r3, zero_bom_00007038@ha
	addi r0, r4, ext_data@l
	stmw r28, 0x30(r1)
	addi r4, r3, zero_bom_00007038@l
	addi r3, r1, 0x8
	mr r30, r0
	li r29, 0x0
	lwz r5, 0x0(r5)
	lwz r31, 0x0(r5)
	bl strcpy
	li r0, -0x1
	stw r0, 0xa8(r31)
	@1:
	lwz r3, 0x4(r30)
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	lwz r4, 0x4(r30)
	addi r3, r1, 0x8
	bl strcpy
	lwz r3, 0xa8(r31)
	mr r28, r29
	addi r0, r3, 0x1
	stw r0, 0xa8(r31)
	@2:
	lwz r0, 0xa8(r31)
	addi r4, r1, 0x8
	mulli r3, r0, 0x14
	addi r3, r3, 0x8
	add r3, r31, r3
	bl strcpy
	lwz r0, 0xa8(r31)
	subf r3, r28, r29
	addi r4, r3, 0x1
	addi r29, r29, 0x1
	mulli r3, r0, 0x14
	addi r0, r3, 0x14
	stwx r28, r31, r0
	lwz r0, 0xa8(r31)
	mulli r3, r0, 0x14
	addi r0, r3, 0x18
	stwx r4, r31, r0
	lwz r0, 0xa8(r31)
	lfs f0, 0x8(r30)
	mulli r3, r0, 0x14
	addi r0, r3, 0x10
	stfsx f0, r31, r0
	lwzu r0, 0xc(r30)
	cmplwi r0, 0x0
	bne @1
	lwz r3, 0xa8(r31)
	addi r0, r3, 0x1
	stw r0, 0xa8(r31)
	lmw r28, 0x30(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 bom_fall(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stfd f31, 0xb0(r1)
	psq_st f31, 0xb8(r1), 0, 0
	stfd f30, 0xa0(r1)
	psq_st f30, 0xa8(r1), 0, 0
	stfd f29, 0x90(r1)
	psq_st f29, 0x98(r1), 0, 0
	stfd f28, 0x80(r1)
	psq_st f28, 0x88(r1), 0, 0
	stfd f27, 0x70(r1)
	psq_st f27, 0x78(r1), 0, 0
	stfd f26, 0x60(r1)
	psq_st f26, 0x68(r1), 0, 0
	stfd f25, 0x50(r1)
	psq_st f25, 0x58(r1), 0, 0
	stmw r22, 0x28(r1)
	lis r3, lp@ha
	addi r3, r3, lp@l
	lwz r3, 0x0(r3)
	lwz r27, 0x0(r3)
	bl extGetPosePtr
	lis r10, double_to_int_bom_00007030@ha
	lis r9, float_600_bom_000070f4@ha
	addi r12, r10, double_to_int_bom_00007030@l
	lis r8, float_32767_bom_000070ac@ha
	addi r11, r9, float_600_bom_000070f4@l
	lis r7, float_3700_bom_000070fc@ha
	addi r10, r8, float_32767_bom_000070ac@l
	lis r6, float_300_bom_000070f8@ha
	addi r9, r7, float_3700_bom_000070fc@l
	lis r5, float_neg450_bom_00007104@ha
	addi r7, r5, float_neg450_bom_00007104@l
	addi r8, r6, float_300_bom_000070f8@l
	lis r4, float_neg650_bom_00007100@ha
	lis r5, lp@ha
	addi r6, r4, float_neg650_bom_00007100@l
	lfd f30, 0x0(r12)
	lis r4, str_00000EB4@ha
	lfs f31, 0x0(r11)
	lfs f25, 0x0(r10)
	mr r26, r3
	lfs f26, 0x0(r9)
	addi r31, r4, str_00000EB4@l
	lfs f27, 0x0(r8)
	addi r30, r5, lp@l
	lfs f28, 0x0(r7)
	li r25, 0x0
	lfs f29, 0x0(r6)
	li r24, 0x0
	lis r29, 0x4330
	b @1
	@2:
	addi r0, r24, 0xb0
	li r3, 0x7f
	stbx r3, r27, r0
	bl rand
	xoris r0, r3, 0x8000
	stw r29, 0x8(r1)
	lwz r3, 0xc(r26)
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f30
	fmuls f0, f31, f0
	fdivs f0, f0, f25
	stfs f0, 0xc(r3)
	bl rand
	xoris r0, r3, 0x8000
	stw r29, 0x10(r1)
	lwz r3, 0xc(r26)
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f30
	fmuls f0, f26, f0
	fdivs f0, f0, f25
	fadds f0, f27, f0
	stfs f0, 0x1c(r3)
	bl rand
	xoris r0, r3, 0x8000
	stw r29, 0x18(r1)
	lwz r3, 0xc(r26)
	li r23, 0x0
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	fsubs f0, f0, f30
	fmuls f0, f28, f0
	fdivs f0, f0, f25
	fadds f0, f29, f0
	stfs f0, 0x2c(r3)
	lwz r3, 0x0(r30)
	lwz r22, 0x0(r3)
	addi r28, r22, 0x8
	b @3
	@4:
	mr r3, r28
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @5
	addi r23, r23, 0x1
	addi r28, r28, 0x14
	@3:
	lwz r0, 0xa8(r22)
	cmpw r23, r0
	blt @4
	@5:
	lwz r0, 0xa8(r22)
	cmpw r23, r0
	bge @6
	add r28, r22, r24
	lwz r0, 0xd0(r28)
	cmpw r0, r23
	beq @6
	extsh r0, r23
	stw r0, 0xd0(r28)
	bl rand
	lis r4, gp@ha
	srawi r0, r3, 31
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r5, 0x3c(r4)
	lwz r4, 0x38(r4)
	addc r3, r5, r3
	stw r3, 0xdc(r28)
	adde r0, r4, r0
	stw r0, 0xd8(r28)
	@6:
	addi r25, r25, 0x1
	addi r24, r24, 0x30
	addi r26, r26, 0x20
	@1:
	lwz r0, 0x4(r27)
	cmpw r25, r0
	blt @2
	li r3, 0x2
	psq_l f31, 0xb8(r1), 0, 0
	lfd f31, 0xb0(r1)
	psq_l f30, 0xa8(r1), 0, 0
	lfd f30, 0xa0(r1)
	psq_l f29, 0x98(r1), 0, 0
	lfd f29, 0x90(r1)
	psq_l f28, 0x88(r1), 0, 0
	lfd f28, 0x80(r1)
	psq_l f27, 0x78(r1), 0, 0
	lfd f27, 0x70(r1)
	psq_l f26, 0x68(r1), 0, 0
	lfd f26, 0x60(r1)
	psq_l f25, 0x58(r1), 0, 0
	lfd f25, 0x50(r1)
	lmw r22, 0x28(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm s32 bom_flag(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	mr r30, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lis r4, lp@ha
	cmpwi r31, 0x0
	addi r4, r4, lp@l
	lwz r4, 0x0(r4)
	lwz r4, 0x0(r4)
	beq @1
	lhz r0, 0x0(r4)
	or r0, r0, r3
	sth r0, 0x0(r4)
	b @2
	@1:
	lhz r0, 0x0(r4)
	andc r0, r0, r3
	sth r0, 0x0(r4)
	@2:
	lmw r30, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 sight_dir(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lis r4, sight_wp@ha
	addi r4, r4, sight_wp@l
	lwz r4, 0x0(r4)
	stw r3, 0x1c(r4)
	li r3, 0x2
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 sight(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x14(r1)
	beq @1
	li r3, 0x28
	bl _mapAlloc
	lis r5, sight_wp@ha
	li r4, 0x0
	addi r6, r5, sight_wp@l
	li r5, 0x28
	stw r3, 0x0(r6)
	bl memset
	li r3, 0x0
	lis r4, sight_wp@ha
	li r0, 0x5
	mr r6, r3
	addi r5, r4, sight_wp@l
	mtctr r0
	@2:
	lwz r4, 0x0(r5)
	addi r0, r3, 0x4
	addi r3, r3, 0x4
	stwx r6, r4, r0
	bdnz @2
	bl rand
	lis r4, sight_wp@ha
	addi r4, r4, sight_wp@l
	lwz r4, 0x0(r4)
	stw r3, 0x20(r4)
	bl rand
	lis r4, sight_wp@ha
	li r0, 0x5
	addi r5, r4, sight_wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x24(r4)
	lwz r3, 0x0(r5)
	stw r0, 0x1c(r3)
	@1:
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne @3
	bl getMarioStDvdRoot
	lis r5, str_00000ED0@ha
	lis r4, str_00000ED8@ha
	mr r6, r3
	li r3, 0x4
	addi r7, r4, str_00000ED8@l
	addi r5, r5, str_00000ED0@l
	li r4, 0x0
	crclr 6
	bl fileAsyncf
	cmplwi r3, 0x0
	bne @4
	li r3, 0x0
	b @5
	@4:
	bl getMarioStDvdRoot
	lis r4, str_00000ED0@ha
	lis r6, str_00000ED8@ha
	mr r5, r3
	li r3, 0x4
	addi r4, r4, str_00000ED0@l
	addi r6, r6, str_00000ED8@l
	crclr 6
	bl fileAllocf
	lis r4, sight_wp@ha
	addi r4, r4, sight_wp@l
	lwz r4, 0x0(r4)
	stw r3, 0x0(r4)
	@3:
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x1c(r3)
	cmpwi r0, 0x6
	bne @6
	lwz r3, 0x0(r3)
	bl fileFree
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	bl _mapFree
	li r3, 0x2
	b @5
	@6:
	cmpwi r0, 0x5
	beq @7
	lis r3, float_800_bom_0000711c@ha
	lis r4, disp_sight@ha
	addi r6, r3, float_800_bom_0000711c@l
	lfs f1, 0x0(r6)
	addi r5, r4, disp_sight@l
	li r3, 0x8
	li r4, 0x0
	li r6, 0x0
	bl dispEntry
	@7:
	li r3, 0x0
	@5:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void disp_sight(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x3c0(r1)
	mflr r0
	stw r0, 0x3c4(r1)
	stfd f31, 0x3b0(r1)
	psq_st f31, 0x3b8(r1), 0, 0
	stfd f30, 0x3a0(r1)
	psq_st f30, 0x3a8(r1), 0, 0
	stfd f29, 0x390(r1)
	psq_st f29, 0x398(r1), 0, 0
	stfd f28, 0x380(r1)
	psq_st f28, 0x388(r1), 0, 0
	stfd f27, 0x370(r1)
	psq_st f27, 0x378(r1), 0, 0
	stfd f26, 0x360(r1)
	psq_st f26, 0x368(r1), 0, 0
	stmw r24, 0x340(r1)
	lis r4, zero_bom_00007004@ha
	lis r3, float_1_bom_00006ffc@ha
	lfs f1, zero_bom_00007004@l(r4)
	lis r4, dat_bom_00006380@ha
	lfs f3, float_1_bom_00006ffc@l(r3)
	lis r5, dat_bom_0000637c@ha
	lwz r3, dat_bom_0000637c@l(r5)
	fmr f2, f1
	lwz r0, dat_bom_00006380@l(r4)
	fmr f4, f3
	stw r3, 0x58(r1)
	fmr f5, f1
	li r3, 0x0
	stw r0, 0x54(r1)
	bl drawBG
	lis r3, zero_bom_00007004@ha
	lis r4, float_neg1_bom_00007120@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f3, float_neg1_bom_00007120@l(r4)
	lfs f1, 0x0(r5)
	lis r3, float_1_bom_00006ffc@ha
	lfs f4, float_1_bom_00006ffc@l(r3)
	li r3, 0x0
	fmr f2, f1
	fmr f5, f1
	bl drawBG
	lis r3, zero_bom_00007004@ha
	lis r4, float_1_bom_00006ffc@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f3, float_1_bom_00006ffc@l(r4)
	lfs f1, 0x0(r5)
	lis r3, float_neg1_bom_00007120@ha
	lfs f4, float_neg1_bom_00007120@l(r3)
	li r3, 0x0
	fmr f2, f1
	fmr f5, f1
	bl drawBG
	lis r3, zero_bom_00007004@ha
	lis r4, float_neg1_bom_00007120@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f3, float_neg1_bom_00007120@l(r4)
	lfs f1, 0x0(r5)
	li r3, 0x0
	fmr f4, f3
	fmr f2, f1
	fmr f5, f1
	bl drawBG
	lis r3, zero_bom_00007004@ha
	lis r4, float_1_bom_00006ffc@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f3, float_1_bom_00006ffc@l(r4)
	lis r3, sight_wp@ha
	lfs f1, 0x0(r5)
	lwz r4, sight_wp@l(r3)
	fmr f4, f3
	fmr f2, f1
	li r3, 0x1
	lfs f5, 0x18(r4)
	bl drawBG
	lis r3, sight_wp@ha
	lis r4, zero_bom_00007004@ha
	addi r3, r3, sight_wp@l
	lfs f1, zero_bom_00007004@l(r4)
	lwz r3, 0x0(r3)
	lis r5, float_neg1_bom_00007120@ha
	lis r4, float_1_bom_00006ffc@ha
	fmr f2, f1
	lfs f0, 0x18(r3)
	li r3, 0x1
	lfs f3, float_neg1_bom_00007120@l(r5)
	fneg f5, f0
	lfs f4, float_1_bom_00006ffc@l(r4)
	bl drawBG
	lis r3, sight_wp@ha
	lis r4, zero_bom_00007004@ha
	addi r3, r3, sight_wp@l
	lfs f1, zero_bom_00007004@l(r4)
	lwz r3, 0x0(r3)
	lis r5, float_1_bom_00006ffc@ha
	lis r4, float_neg1_bom_00007120@ha
	fmr f2, f1
	lfs f0, 0x18(r3)
	li r3, 0x1
	lfs f3, float_1_bom_00006ffc@l(r5)
	fneg f5, f0
	lfs f4, float_neg1_bom_00007120@l(r4)
	bl drawBG
	lis r3, zero_bom_00007004@ha
	lis r4, float_neg1_bom_00007120@ha
	addi r5, r3, zero_bom_00007004@l
	lfs f3, float_neg1_bom_00007120@l(r4)
	lis r3, sight_wp@ha
	lfs f1, 0x0(r5)
	lwz r4, sight_wp@l(r3)
	fmr f4, f3
	fmr f2, f1
	li r3, 0x1
	lfs f5, 0x18(r4)
	bl drawBG
	lis r3, sight_wp@ha
	lwz r4, sight_wp@l(r3)
	lwz r0, 0x1c(r4)
	cmpwi r0, 0x2
	bne @1
	lis r3, float_2_bom_0000704c@ha
	lfs f1, 0x18(r4)
	lfs f0, float_2_bom_0000704c@l(r3)
	fadds f0, f1, f0
	stfs f0, 0x18(r4)
	b @2
	@1:
	cmpwi r0, 0x3
	bne @3
	lis r3, float_2_bom_0000704c@ha
	lfs f1, 0x18(r4)
	lfs f0, float_2_bom_0000704c@l(r3)
	fsubs f0, f1, f0
	stfs f0, 0x18(r4)
	b @2
	@3:
	cmpwi r0, 0x0
	bne @4
	lis r3, float_2_bom_0000704c@ha
	lfs f1, 0x18(r4)
	lfs f0, float_2_bom_0000704c@l(r3)
	fsubs f0, f1, f0
	stfs f0, 0x18(r4)
	b @2
	@4:
	lis r3, float_1_bom_00006ffc@ha
	lfs f1, 0x18(r4)
	lfs f0, float_1_bom_00006ffc@l(r3)
	fadds f0, f1, f0
	stfs f0, 0x18(r4)
	@2:
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r4, vec3_bom_00006390@ha
	lis r3, vec3_bom_00006384@ha
	addi r5, r4, vec3_bom_00006390@l
	lwz r25, 0x54(r1)
	addi r9, r3, vec3_bom_00006384@l
	lwz r12, 0x0(r5)
	lwz r11, 0x4(r5)
	addi r4, r1, 0x218
	lwz r10, 0x8(r5)
	addi r5, r1, 0x20c
	lwz r8, 0x0(r9)
	addi r6, r1, 0x50
	lwz r7, 0x4(r9)
	li r3, 0x5
	lwz r0, 0x8(r9)
	stw r25, 0x50(r1)
	stw r12, 0x20c(r1)
	stw r11, 0x210(r1)
	stw r10, 0x214(r1)
	stw r8, 0x218(r1)
	stw r7, 0x21c(r1)
	stw r0, 0x220(r1)
	bl winTexSet
	lis r3, gp@ha
	li r26, 0x0
	addi r27, r3, gp@l
	@5:
	lwz r3, 0x0(r27)
	li r4, 0x1e
	li r0, 0xa
	lwz r5, 0x1c(r3)
	divwu r3, r5, r4
	mullw r3, r3, r4
	subf r3, r3, r5
	divw r0, r3, r0
	cmpw r0, r26
	beq @6
	lis r3, float_1_bom_00006ffc@ha
	lis r5, float_100_bom_00007000@ha
	lfs f3, float_1_bom_00006ffc@l(r3)
	addi r6, r5, float_100_bom_00007000@l
	lis r4, float_60_bom_000070dc@ha
	lis r3, zero_bom_00007004@ha
	addi r5, r4, float_60_bom_000070dc@l
	fmr f4, f3
	addi r4, r3, zero_bom_00007004@l
	subfic r25, r26, 0x4
	lfs f1, 0x0(r6)
	mr r3, r25
	lfs f2, 0x0(r5)
	lfs f5, 0x0(r4)
	bl drawBG
	lis r7, float_neg100_bom_00007124@ha
	lis r6, float_60_bom_000070dc@ha
	lis r5, float_neg1_bom_00007120@ha
	lis r4, float_1_bom_00006ffc@ha
	lis r3, zero_bom_00007004@ha
	addi r8, r7, float_neg100_bom_00007124@l
	addi r7, r6, float_60_bom_000070dc@l
	addi r6, r5, float_neg1_bom_00007120@l
	addi r5, r4, float_1_bom_00006ffc@l
	addi r4, r3, zero_bom_00007004@l
	lfs f1, 0x0(r8)
	mr r3, r25
	lfs f2, 0x0(r7)
	lfs f3, 0x0(r6)
	lfs f4, 0x0(r5)
	lfs f5, 0x0(r4)
	bl drawBG
	lis r7, float_100_bom_00007000@ha
	lis r6, float_neg60_bom_00007128@ha
	lis r5, float_1_bom_00006ffc@ha
	lis r4, float_neg1_bom_00007120@ha
	lis r3, zero_bom_00007004@ha
	addi r8, r7, float_100_bom_00007000@l
	addi r7, r6, float_neg60_bom_00007128@l
	addi r6, r5, float_1_bom_00006ffc@l
	addi r5, r4, float_neg1_bom_00007120@l
	addi r4, r3, zero_bom_00007004@l
	lfs f1, 0x0(r8)
	mr r3, r25
	lfs f2, 0x0(r7)
	lfs f3, 0x0(r6)
	lfs f4, 0x0(r5)
	lfs f5, 0x0(r4)
	bl drawBG
	lis r3, float_neg1_bom_00007120@ha
	lis r5, float_neg100_bom_00007124@ha
	lfs f3, float_neg1_bom_00007120@l(r3)
	addi r6, r5, float_neg100_bom_00007124@l
	lis r4, float_neg60_bom_00007128@ha
	lis r3, zero_bom_00007004@ha
	addi r5, r4, float_neg60_bom_00007128@l
	fmr f4, f3
	addi r4, r3, zero_bom_00007004@l
	lfs f1, 0x0(r6)
	lfs f2, 0x0(r5)
	mr r3, r25
	lfs f5, 0x0(r4)
	bl drawBG
	@6:
	addi r26, r26, 0x1
	cmpwi r26, 0x3
	blt @5
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r4, vec3_bom_000063a8@ha
	lis r3, vec3_bom_0000639c@ha
	addi r5, r4, vec3_bom_000063a8@l
	lwz r25, 0x58(r1)
	addi r9, r3, vec3_bom_0000639c@l
	lwz r12, 0x0(r5)
	lwz r11, 0x4(r5)
	addi r4, r1, 0x200
	lwz r10, 0x8(r5)
	addi r5, r1, 0x1f4
	lwz r8, 0x0(r9)
	addi r6, r1, 0x4c
	lwz r7, 0x4(r9)
	li r3, 0x17
	lwz r0, 0x8(r9)
	stw r25, 0x4c(r1)
	stw r12, 0x1f4(r1)
	stw r11, 0x1f8(r1)
	stw r10, 0x1fc(r1)
	stw r8, 0x200(r1)
	stw r7, 0x204(r1)
	stw r0, 0x208(r1)
	bl winTexSet
	lis r3, gp@ha
	li r5, 0x0
	lwz r4, gp@l(r3)
	li r6, 0x64
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	bl __div2i
	li r5, 0x0
	li r6, 0x3e8
	bl __div2i
	lis r3, sight_wp@ha
	lis r6, dat_bom_00006360@ha
	addi r3, r3, sight_wp@l
	srawi r5, r4, 31
	lwz r3, 0x0(r3)
	addi r6, r6, dat_bom_00006360@l
	lwz r6, 0x0(r6)
	xor r0, r5, r4
	lwz r3, 0x0(r3)
	subf r26, r5, r0
	stw r6, 0x40(r1)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p6_bom_0000712c@ha
	addi r9, r7, float_0p6_bom_0000712c@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_90_bom_00007130@ha
	lis r3, float_180_bom_000070c8@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x40(r1)
	li r25, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_90_bom_00007130@l(r4)
	lfs f26, float_180_bom_000070c8@l(r3)
	@7:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r26, r5
	addi r4, r1, 0x304
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r26
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x304
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x32c(r1)
	subfic r3, r25, 0xa
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x328(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x328(r1)
	addi r4, r1, 0x1ac
	lwz r9, 0x8(r28)
	addi r5, r1, 0x1c4
	fsubs f0, f0, f31
	stw r0, 0x334(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x44
	stw r30, 0x330(r1)
	fmuls f1, f30, f0
	lfd f0, 0x330(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0x1d0(r1)
	fsubs f0, f0, f28
	stw r10, 0x1d4(r1)
	stw r9, 0x1d8(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0x1b8(r1)
	stw r0, 0x1bc(r1)
	stfs f30, 0x1d0(r1)
	stfs f30, 0x1d4(r1)
	lwz r11, 0x1d0(r1)
	stfs f30, 0x1d8(r1)
	lwz r10, 0x1d4(r1)
	stfs f0, 0x1b8(r1)
	lwz r9, 0x1d8(r1)
	stfs f26, 0x1bc(r1)
	lwz r7, 0x1b8(r1)
	lwz r0, 0x1bc(r1)
	stw r29, 0x44(r1)
	stw r11, 0x1c4(r1)
	stw r10, 0x1c8(r1)
	stw r9, 0x1cc(r1)
	stw r8, 0x1c0(r1)
	stw r7, 0x1ac(r1)
	stw r0, 0x1b0(r1)
	stw r8, 0x1b4(r1)
	bl winTexSet
	li r0, 0xa
	addi r25, r25, 0x1
	divw r26, r26, r0
	cmpwi r25, 0xa
	blt @7
	lis r3, gp@ha
	li r5, 0x0
	lwz r4, gp@l(r3)
	li r6, 0xc8
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	bl __div2i
	li r5, 0x0
	li r6, 0x3e8
	bl __div2i
	lis r3, sight_wp@ha
	lis r6, dat_bom_00006360@ha
	addi r3, r3, sight_wp@l
	srawi r5, r4, 31
	lwz r3, 0x0(r3)
	addi r6, r6, dat_bom_00006360@l
	lwz r6, 0x0(r6)
	xor r0, r5, r4
	lwz r3, 0x0(r3)
	subf r25, r5, r0
	stw r6, 0x38(r1)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p6_bom_0000712c@ha
	addi r9, r7, float_0p6_bom_0000712c@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_126_bom_00007134@ha
	lis r3, float_150_bom_000070b0@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x38(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_126_bom_00007134@l(r4)
	lfs f26, float_150_bom_000070b0@l(r3)
	@8:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x2e4
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x2e4
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x8
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0x17c
	lwz r9, 0x8(r28)
	addi r5, r1, 0x194
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x3c
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0x1a0(r1)
	fsubs f0, f0, f28
	stw r10, 0x1a4(r1)
	stw r9, 0x1a8(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0x188(r1)
	stw r0, 0x18c(r1)
	stfs f30, 0x1a0(r1)
	stfs f30, 0x1a4(r1)
	lwz r11, 0x1a0(r1)
	stfs f30, 0x1a8(r1)
	lwz r10, 0x1a4(r1)
	stfs f0, 0x188(r1)
	lwz r9, 0x1a8(r1)
	stfs f26, 0x18c(r1)
	lwz r7, 0x188(r1)
	lwz r0, 0x18c(r1)
	stw r29, 0x3c(r1)
	stw r11, 0x194(r1)
	stw r10, 0x198(r1)
	stw r9, 0x19c(r1)
	stw r8, 0x190(r1)
	stw r7, 0x17c(r1)
	stw r0, 0x180(r1)
	stw r8, 0x184(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x8
	blt @8
	lis r3, gp@ha
	li r5, 0x0
	lwz r4, gp@l(r3)
	li r6, 0x12c
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	bl __div2i
	li r5, 0x0
	li r6, 0x3e8
	bl __div2i
	lis r3, sight_wp@ha
	lis r6, dat_bom_00006360@ha
	addi r3, r3, sight_wp@l
	srawi r5, r4, 31
	lwz r3, 0x0(r3)
	addi r6, r6, dat_bom_00006360@l
	lwz r6, 0x0(r6)
	xor r0, r5, r4
	lwz r3, 0x0(r3)
	subf r25, r5, r0
	stw r6, 0x30(r1)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p6_bom_0000712c@ha
	addi r9, r7, float_0p6_bom_0000712c@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_162_bom_00007138@ha
	lis r3, float_120_bom_0000713c@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x30(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_162_bom_00007138@l(r4)
	lfs f26, float_120_bom_0000713c@l(r3)
	@9:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x2c4
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x2c4
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x6
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0x14c
	lwz r9, 0x8(r28)
	addi r5, r1, 0x164
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x34
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0x170(r1)
	fsubs f0, f0, f28
	stw r10, 0x174(r1)
	stw r9, 0x178(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0x158(r1)
	stw r0, 0x15c(r1)
	stfs f30, 0x170(r1)
	stfs f30, 0x174(r1)
	lwz r11, 0x170(r1)
	stfs f30, 0x178(r1)
	lwz r10, 0x174(r1)
	stfs f0, 0x158(r1)
	lwz r9, 0x178(r1)
	stfs f26, 0x15c(r1)
	lwz r7, 0x158(r1)
	lwz r0, 0x15c(r1)
	stw r29, 0x34(r1)
	stw r11, 0x164(r1)
	stw r10, 0x168(r1)
	stw r9, 0x16c(r1)
	stw r8, 0x160(r1)
	stw r7, 0x14c(r1)
	stw r0, 0x150(r1)
	stw r8, 0x154(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x6
	blt @9
	lis r3, gp@ha
	li r5, 0x0
	lwz r4, gp@l(r3)
	li r6, 0x190
	lwz r3, 0x38(r4)
	lwz r4, 0x3c(r4)
	bl __div2i
	li r5, 0x0
	li r6, 0x3e8
	bl __div2i
	lis r3, sight_wp@ha
	lis r6, dat_bom_00006360@ha
	addi r3, r3, sight_wp@l
	srawi r5, r4, 31
	lwz r3, 0x0(r3)
	addi r6, r6, dat_bom_00006360@l
	lwz r6, 0x0(r6)
	xor r0, r5, r4
	lwz r3, 0x0(r3)
	subf r25, r5, r0
	stw r6, 0x28(r1)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p6_bom_0000712c@ha
	addi r9, r7, float_0p6_bom_0000712c@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_162_bom_00007138@ha
	lis r3, float_90_bom_00007130@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x28(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_162_bom_00007138@l(r4)
	lfs f26, float_90_bom_00007130@l(r3)
	@10:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x2a4
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x2a4
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x6
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0x11c
	lwz r9, 0x8(r28)
	addi r5, r1, 0x134
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x2c
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0x140(r1)
	fsubs f0, f0, f28
	stw r10, 0x144(r1)
	stw r9, 0x148(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0x128(r1)
	stw r0, 0x12c(r1)
	stfs f30, 0x140(r1)
	stfs f30, 0x144(r1)
	lwz r11, 0x140(r1)
	stfs f30, 0x148(r1)
	lwz r10, 0x144(r1)
	stfs f0, 0x128(r1)
	lwz r9, 0x148(r1)
	stfs f26, 0x12c(r1)
	lwz r7, 0x128(r1)
	lwz r0, 0x12c(r1)
	stw r29, 0x2c(r1)
	stw r11, 0x134(r1)
	stw r10, 0x138(r1)
	stw r9, 0x13c(r1)
	stw r8, 0x130(r1)
	stw r7, 0x11c(r1)
	stw r0, 0x120(r1)
	stw r8, 0x124(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x6
	blt @10
	lis r4, gp@ha
	lis r3, sight_wp@ha
	addi r5, r4, gp@l
	addi r3, r3, sight_wp@l
	lwz r5, 0x0(r5)
	lwz r3, 0x0(r3)
	lis r4, dat_bom_00006360@ha
	lwz r0, 0x1c(r5)
	lwz r3, 0x0(r3)
	lwz r5, dat_bom_00006360@l(r4)
	srwi r0, r0, 2
	lwz r3, 0xa0(r3)
	srawi r4, r0, 31
	xor r0, r4, r0
	stw r5, 0x20(r1)
	lwz r3, 0x0(r3)
	subf r25, r4, r0
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_1_bom_00006ffc@ha
	addi r9, r7, float_1_bom_00006ffc@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_110_bom_00007140@ha
	lis r3, float_neg160_bom_00007144@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x20(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_110_bom_00007140@l(r4)
	lfs f26, float_neg160_bom_00007144@l(r3)
	@11:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x284
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x284
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x4
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0xec
	lwz r9, 0x8(r28)
	addi r5, r1, 0x104
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x24
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0x110(r1)
	fsubs f0, f0, f28
	stw r10, 0x114(r1)
	stw r9, 0x118(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0xf8(r1)
	stw r0, 0xfc(r1)
	stfs f30, 0x110(r1)
	stfs f30, 0x114(r1)
	lwz r11, 0x110(r1)
	stfs f30, 0x118(r1)
	lwz r10, 0x114(r1)
	stfs f0, 0xf8(r1)
	lwz r9, 0x118(r1)
	stfs f26, 0xfc(r1)
	lwz r7, 0xf8(r1)
	lwz r0, 0xfc(r1)
	stw r29, 0x24(r1)
	stw r11, 0x104(r1)
	stw r10, 0x108(r1)
	stw r9, 0x10c(r1)
	stw r8, 0x100(r1)
	stw r7, 0xec(r1)
	stw r0, 0xf0(r1)
	stw r8, 0xf4(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x4
	blt @11
	lis r4, gp@ha
	lis r3, sight_wp@ha
	addi r5, r4, gp@l
	addi r3, r3, sight_wp@l
	lwz r5, 0x0(r5)
	lwz r3, 0x0(r3)
	lis r4, dat_bom_00006360@ha
	lwz r0, 0x1c(r5)
	lwz r3, 0x0(r3)
	lwz r5, dat_bom_00006360@l(r4)
	srwi r0, r0, 3
	lwz r3, 0xa0(r3)
	srawi r4, r0, 31
	xor r0, r4, r0
	stw r5, 0x18(r1)
	lwz r3, 0x0(r3)
	subf r25, r4, r0
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p8_bom_00007148@ha
	addi r9, r7, float_0p8_bom_00007148@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_230_bom_0000714c@ha
	lis r3, float_neg170_bom_00007150@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x18(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_230_bom_0000714c@l(r4)
	lfs f26, float_neg170_bom_00007150@l(r3)
	@12:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x264
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x264
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x2
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0xbc
	lwz r9, 0x8(r28)
	addi r5, r1, 0xd4
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x1c
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0xe0(r1)
	fsubs f0, f0, f28
	stw r10, 0xe4(r1)
	stw r9, 0xe8(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0xc8(r1)
	stw r0, 0xcc(r1)
	stfs f30, 0xe0(r1)
	stfs f30, 0xe4(r1)
	lwz r11, 0xe0(r1)
	stfs f30, 0xe8(r1)
	lwz r10, 0xe4(r1)
	stfs f0, 0xc8(r1)
	lwz r9, 0xe8(r1)
	stfs f26, 0xcc(r1)
	lwz r7, 0xc8(r1)
	lwz r0, 0xcc(r1)
	stw r29, 0x1c(r1)
	stw r11, 0xd4(r1)
	stw r10, 0xd8(r1)
	stw r9, 0xdc(r1)
	stw r8, 0xd0(r1)
	stw r7, 0xbc(r1)
	stw r0, 0xc0(r1)
	stw r8, 0xc4(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x2
	blt @12
	lis r4, vec3_bom_000063c0@ha
	lis r3, vec3_bom_000063b4@ha
	addi r5, r4, vec3_bom_000063c0@l
	lwz r25, 0x58(r1)
	addi r9, r3, vec3_bom_000063b4@l
	lwz r12, 0x0(r5)
	lwz r11, 0x4(r5)
	addi r4, r1, 0x1e8
	lwz r10, 0x8(r5)
	addi r5, r1, 0x1dc
	lwz r8, 0x0(r9)
	addi r6, r1, 0x48
	lwz r7, 0x4(r9)
	li r3, 0x8
	lwz r0, 0x8(r9)
	stw r25, 0x48(r1)
	stw r12, 0x1dc(r1)
	stw r11, 0x1e0(r1)
	stw r10, 0x1e4(r1)
	stw r8, 0x1e8(r1)
	stw r7, 0x1ec(r1)
	stw r0, 0x1f0(r1)
	bl winTexSet
	lis r3, gp@ha
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x1c(r3)
	clrlwi. r0, r0, 30
	bne @13
	lis r3, sight_wp@ha
	li r0, 0x4
	addi r4, r3, sight_wp@l
	li r3, 0x0
	mtctr r0
	@14:
	lwz r0, 0x0(r4)
	add r5, r0, r3
	addi r3, r3, 0x4
	lwz r0, 0x8(r5)
	stw r0, 0x4(r5)
	bdnz @14
	lis r4, sound@ha
	lis r3, sight_wp@ha
	addi r5, r4, sound@l
	lhz r4, 0x330(r5)
	addi r3, r3, sight_wp@l
	lwz r0, 0x15c0(r5)
	slwi r4, r4, 11
	lwz r3, 0x0(r3)
	add r4, r5, r4
	slwi r0, r0, 1
	add r4, r4, r0
	lha r0, 0x5c0(r4)
	srawi r4, r0, 31
	xor r0, r4, r0
	subf r0, r4, r0
	stw r0, 0x14(r3)
	@13:
	lis r5, float_16_bom_0000715c@ha
	lis r4, double_to_int_bom_00007030@ha
	lis r3, float_neg190_bom_00007158@ha
	lis r7, float_20_bom_000070d8@ha
	lis r6, float_neg240_bom_00007154@ha
	lis r8, sight_wp@ha
	lfs f28, float_16_bom_0000715c@l(r5)
	addi r27, r8, sight_wp@l
	lfd f27, double_to_int_bom_00007030@l(r4)
	li r25, 0x0
	lfs f26, float_neg190_bom_00007158@l(r3)
	li r26, 0x0
	lfs f30, float_20_bom_000070d8@l(r7)
	lis r28, 0x4330
	lfs f29, float_neg240_bom_00007154@l(r6)
	@15:
	lwz r4, 0x0(r27)
	addi r3, r26, 0x4
	li r0, 0x12c
	lwzx r29, r4, r3
	divw r29, r29, r0
	cmpwi r29, 0x7
	ble @16
	li r29, 0x7
	@16:
	xoris r0, r25, 0x8000
	stw r28, 0x330(r1)
	li r24, 0x0
	stw r0, 0x334(r1)
	lfd f0, 0x330(r1)
	fsubs f0, f0, f27
	fmadds f31, f30, f0, f29
	b @17
	@18:
	xoris r0, r24, 0x8000
	stw r28, 0x330(r1)
	cmpwi r24, 0x6
	stw r0, 0x334(r1)
	lfd f0, 0x330(r1)
	fsubs f0, f0, f27
	fmadds f2, f28, f0, f26
	bne @19
	lis r4, float_1_bom_00006ffc@ha
	lis r3, zero_bom_00007004@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	fmr f1, f31
	lfs f5, zero_bom_00007004@l(r3)
	li r3, 0xa
	fmr f4, f3
	bl drawBG
	b @20
	@19:
	lis r4, float_1_bom_00006ffc@ha
	lis r3, zero_bom_00007004@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	fmr f1, f31
	lfs f5, zero_bom_00007004@l(r3)
	li r3, 0x9
	fmr f4, f3
	bl drawBG
	@20:
	addi r24, r24, 0x1
	@17:
	cmpw r24, r29
	blt @18
	mr r24, r29
	b @21
	@22:
	xoris r0, r24, 0x8000
	stw r28, 0x330(r1)
	cmpwi r24, 0x6
	stw r0, 0x334(r1)
	lfd f0, 0x330(r1)
	fsubs f0, f0, f27
	fmadds f2, f28, f0, f26
	bne @23
	lis r4, float_1_bom_00006ffc@ha
	lis r3, zero_bom_00007004@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	fmr f1, f31
	lfs f5, zero_bom_00007004@l(r3)
	li r3, 0xc
	fmr f4, f3
	bl drawBG
	b @24
	@23:
	lis r4, float_1_bom_00006ffc@ha
	lis r3, zero_bom_00007004@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	fmr f1, f31
	lfs f5, zero_bom_00007004@l(r3)
	li r3, 0xb
	fmr f4, f3
	bl drawBG
	@24:
	addi r24, r24, 0x1
	@21:
	cmpwi r24, 0x7
	blt @22
	addi r25, r25, 0x1
	addi r26, r26, 0x4
	cmpwi r25, 0x5
	blt @15
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lis r4, gp@ha
	lis r3, sight_wp@ha
	addi r28, r4, gp@l
	li r25, 0x0
	addi r27, r3, sight_wp@l
	@25:
	lwz r4, 0x0(r28)
	li r3, 0x14
	li r5, 0x0
	lwz r4, 0x1c(r4)
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplwi r0, 0x6
	ble @26
	lis r3, sight_wp@ha
	addi r3, r3, sight_wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x1c(r3)
	cmpw r25, r0
	bne @26
	li r5, 0x1
	@26:
	subic r3, r5, 0x1
	li r0, 0x7
	subfe. r3, r3, r5
	mr r26, r3
	beq @27
	li r0, 0x6
	@27:
	lwz r4, 0x0(r27)
	mr r3, r0
	lwz r0, 0x1c(r4)
	cmpwi r0, 0x4
	bne @28
	li r26, 0x0
	li r3, 0x7
	@28:
	cmpwi r25, 0x2
	beq @29
	bge @30
	cmpwi r25, 0x0
	beq @31
	bge @32
	b @33
	@30:
	cmpwi r25, 0x4
	bge @33
	b @34
	@31:
	lis r4, float_1_bom_00006ffc@ha
	lis r6, float_16_bom_0000715c@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	lis r5, float_180_bom_000070c8@ha
	lis r4, float_90_bom_00007130@ha
	lfs f1, float_16_bom_0000715c@l(r6)
	fmr f4, f3
	lfs f2, float_180_bom_000070c8@l(r5)
	lfs f5, float_90_bom_00007130@l(r4)
	bl drawBG
	b @33
	@32:
	lis r4, float_1_bom_00006ffc@ha
	lis r6, float_neg16_bom_00007160@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	lis r5, float_neg180_bom_00007164@ha
	lis r4, float_270_bom_0000703c@ha
	lfs f1, float_neg16_bom_00007160@l(r6)
	fmr f4, f3
	lfs f2, float_neg180_bom_00007164@l(r5)
	lfs f5, float_270_bom_0000703c@l(r4)
	bl drawBG
	b @33
	@29:
	lis r4, float_1_bom_00006ffc@ha
	lis r6, float_neg180_bom_00007164@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	lis r5, float_16_bom_0000715c@ha
	lis r4, float_180_bom_000070c8@ha
	lfs f1, float_neg180_bom_00007164@l(r6)
	fmr f4, f3
	lfs f2, float_16_bom_0000715c@l(r5)
	lfs f5, float_180_bom_000070c8@l(r4)
	bl drawBG
	cmpwi r26, 0x0
	beq @33
	lis r3, gp@ha
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x1c(r3)
	clrlwi. r0, r0, 30
	bne @33
	lis r3, sight_wp@ha
	lwz r4, sight_wp@l(r3)
	lwz r3, 0x20(r4)
	addi r0, r3, 0x1
	stw r0, 0x20(r4)
	b @33
	@34:
	lis r4, float_1_bom_00006ffc@ha
	lis r6, float_180_bom_000070c8@ha
	lfs f3, float_1_bom_00006ffc@l(r4)
	lis r5, float_neg16_bom_00007160@ha
	lis r4, zero_bom_00007004@ha
	lfs f1, float_180_bom_000070c8@l(r6)
	fmr f4, f3
	lfs f2, float_neg16_bom_00007160@l(r5)
	lfs f5, zero_bom_00007004@l(r4)
	bl drawBG
	cmpwi r26, 0x0
	beq @33
	lis r3, gp@ha
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x1c(r3)
	clrlwi. r0, r0, 30
	bne @33
	lis r3, sight_wp@ha
	lwz r4, sight_wp@l(r3)
	lwz r3, 0x24(r4)
	addi r0, r3, 0x1
	stw r0, 0x24(r4)
	@33:
	addi r25, r25, 0x1
	cmpwi r25, 0x4
	blt @25
	lis r4, sight_wp@ha
	lis r3, dat_bom_00006360@ha
	addi r4, r4, sight_wp@l
	lwz r0, dat_bom_00006360@l(r3)
	lwz r4, 0x0(r4)
	stw r0, 0x10(r1)
	lwz r3, 0x0(r4)
	lwz r5, 0x20(r4)
	lwz r3, 0xa0(r3)
	srawi r4, r5, 31
	xor r0, r4, r5
	lwz r3, 0x0(r3)
	subf r25, r4, r0
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p8_bom_00007148@ha
	addi r9, r7, float_0p8_bom_00007148@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_neg220_bom_00007168@ha
	lis r3, zero_bom_00007004@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f31, 0x0(r10)
	addi r31, r11, sight_wp@l
	lfs f30, 0x0(r9)
	addi r28, r7, vec3_bom_00006370@l
	lfs f29, 0x0(r8)
	addi r27, r6, vec3_bom_00006364@l
	lwz r29, 0x10(r1)
	li r26, 0x0
	lfd f28, double_to_int_bom_00007030@l(r5)
	lis r30, 0x4330
	lfs f27, float_neg220_bom_00007168@l(r4)
	lfs f26, zero_bom_00007004@l(r3)
	@35:
	li r5, 0xa
	lwz r3, 0x0(r31)
	divw r0, r25, r5
	addi r4, r1, 0x244
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x244
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r27)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x2
	subi r0, r3, 0x1
	lwz r11, 0x0(r28)
	stw r30, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r28)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0x8c
	lwz r9, 0x8(r28)
	addi r5, r1, 0xa4
	fsubs f0, f0, f31
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r27)
	addi r6, r1, 0x14
	stw r30, 0x328(r1)
	fmuls f1, f30, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r27)
	fadds f1, f1, f29
	stw r11, 0xb0(r1)
	fsubs f0, f0, f28
	stw r10, 0xb4(r1)
	stw r9, 0xb8(r1)
	fmadds f0, f1, f0, f27
	stw r7, 0x98(r1)
	stw r0, 0x9c(r1)
	stfs f30, 0xb0(r1)
	stfs f30, 0xb4(r1)
	lwz r11, 0xb0(r1)
	stfs f30, 0xb8(r1)
	lwz r10, 0xb4(r1)
	stfs f0, 0x98(r1)
	lwz r9, 0xb8(r1)
	stfs f26, 0x9c(r1)
	lwz r7, 0x98(r1)
	lwz r0, 0x9c(r1)
	stw r29, 0x14(r1)
	stw r11, 0xa4(r1)
	stw r10, 0xa8(r1)
	stw r9, 0xac(r1)
	stw r8, 0xa0(r1)
	stw r7, 0x8c(r1)
	stw r0, 0x90(r1)
	stw r8, 0x94(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x2
	blt @35
	lis r4, sight_wp@ha
	lis r3, dat_bom_00006360@ha
	addi r4, r4, sight_wp@l
	lwz r0, dat_bom_00006360@l(r3)
	lwz r4, 0x0(r4)
	stw r0, 0x8(r1)
	lwz r3, 0x0(r4)
	lwz r5, 0x24(r4)
	lwz r3, 0xa0(r3)
	srawi r4, r5, 31
	xor r0, r4, r5
	lwz r3, 0x0(r3)
	subf r25, r4, r0
	bl winTexInit
	lis r8, double_to_int_mask_bom_000070e0@ha
	lis r7, float_0p8_bom_00007148@ha
	addi r9, r7, float_0p8_bom_00007148@l
	lis r5, double_to_int_bom_00007030@ha
	lis r4, float_200_bom_0000716c@ha
	lis r3, zero_bom_00007004@ha
	addi r10, r8, double_to_int_mask_bom_000070e0@l
	lis r6, float_2_bom_0000704c@ha
	addi r8, r6, float_2_bom_0000704c@l
	lis r11, sight_wp@ha
	lis r7, vec3_bom_00006370@ha
	lis r6, vec3_bom_00006364@ha
	lfd f26, 0x0(r10)
	addi r27, r11, sight_wp@l
	lfs f27, 0x0(r9)
	addi r30, r7, vec3_bom_00006370@l
	lfs f28, 0x0(r8)
	addi r31, r6, vec3_bom_00006364@l
	lwz r29, 0x8(r1)
	li r26, 0x0
	lfd f29, double_to_int_bom_00007030@l(r5)
	lis r28, 0x4330
	lfs f30, float_200_bom_0000716c@l(r4)
	lfs f31, zero_bom_00007004@l(r3)
	@36:
	li r5, 0xa
	lwz r3, 0x0(r27)
	divw r0, r25, r5
	addi r4, r1, 0x224
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r25
	addi r24, r5, 0xd
	mr r5, r24
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x224
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r31)
	stw r0, 0x334(r1)
	subfic r3, r26, 0x2
	subi r0, r3, 0x1
	lwz r11, 0x0(r30)
	stw r28, 0x330(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r30)
	mr r3, r24
	lfd f0, 0x330(r1)
	addi r4, r1, 0x5c
	lwz r9, 0x8(r30)
	addi r5, r1, 0x74
	fsubs f0, f0, f26
	stw r0, 0x32c(r1)
	lwz r7, 0x0(r31)
	addi r6, r1, 0xc
	stw r28, 0x328(r1)
	fmuls f1, f27, f0
	lfd f0, 0x328(r1)
	lwz r0, 0x4(r31)
	fadds f1, f1, f28
	stw r11, 0x80(r1)
	fsubs f0, f0, f29
	stw r10, 0x84(r1)
	stw r9, 0x88(r1)
	fmadds f0, f1, f0, f30
	stw r7, 0x68(r1)
	stw r0, 0x6c(r1)
	stfs f27, 0x80(r1)
	stfs f27, 0x84(r1)
	lwz r11, 0x80(r1)
	stfs f27, 0x88(r1)
	lwz r10, 0x84(r1)
	stfs f0, 0x68(r1)
	lwz r9, 0x88(r1)
	stfs f31, 0x6c(r1)
	lwz r7, 0x68(r1)
	lwz r0, 0x6c(r1)
	stw r29, 0xc(r1)
	stw r11, 0x74(r1)
	stw r10, 0x78(r1)
	stw r9, 0x7c(r1)
	stw r8, 0x70(r1)
	stw r7, 0x5c(r1)
	stw r0, 0x60(r1)
	stw r8, 0x64(r1)
	bl winTexSet
	li r0, 0xa
	addi r26, r26, 0x1
	divw r25, r25, r0
	cmpwi r26, 0x2
	blt @36
	psq_l f31, 0x3b8(r1), 0, 0
	lfd f31, 0x3b0(r1)
	psq_l f30, 0x3a8(r1), 0, 0
	lfd f30, 0x3a0(r1)
	psq_l f29, 0x398(r1), 0, 0
	lfd f29, 0x390(r1)
	psq_l f28, 0x388(r1), 0, 0
	lfd f28, 0x380(r1)
	psq_l f27, 0x378(r1), 0, 0
	lfd f27, 0x370(r1)
	psq_l f26, 0x368(r1), 0, 0
	lfd f26, 0x360(r1)
	lmw r24, 0x340(r1)
	lwz r0, 0x3c4(r1)
	mtlr r0
	addi r1, r1, 0x3c0
	blr
}

asm void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stmw r23, 0x7c(r1)
	lis r5, sight_wp@ha
	lis r7, dat_bom_00006360@ha
	addi r5, r5, sight_wp@l
	srawi r6, r3, 31
	lwz r5, 0x0(r5)
	addi r7, r7, dat_bom_00006360@l
	lwz r7, 0x0(r7)
	xor r0, r6, r3
	lwz r3, 0x0(r5)
	fmr f26, f1
	fmr f27, f2
	stw r7, 0xc(r1)
	lwz r3, 0xa0(r3)
	fmr f28, f3
	mr r25, r4
	lwz r3, 0x0(r3)
	subf r26, r6, r0
	bl winTexInit
	lis r5, double_to_int_mask_bom_000070e0@ha
	lis r4, float_2_bom_0000704c@ha
	addi r7, r5, double_to_int_mask_bom_000070e0@l
	lis r3, double_to_int_bom_00007030@ha
	addi r6, r4, float_2_bom_0000704c@l
	lis r8, sight_wp@ha
	lis r5, vec3_bom_00006370@ha
	lis r4, vec3_bom_00006364@ha
	lfd f29, 0x0(r7)
	addi r28, r8, sight_wp@l
	lfs f30, 0x0(r6)
	addi r31, r5, vec3_bom_00006370@l
	lwz r30, 0xc(r1)
	addi r24, r4, vec3_bom_00006364@l
	lfd f31, double_to_int_bom_00007030@l(r3)
	li r27, 0x0
	lis r29, 0x4330
	b @1
	@2:
	li r5, 0xa
	lwz r3, 0x0(r28)
	divw r0, r26, r5
	addi r4, r1, 0x40
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	mullw r0, r0, r5
	subf r5, r0, r26
	addi r23, r5, 0xd
	mr r5, r23
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x40
	bl GXGetTexObjWidth
	clrlwi r0, r3, 16
	lwz r8, 0x8(r24)
	stw r0, 0x64(r1)
	subf r3, r27, r25
	subi r0, r3, 0x1
	lwz r11, 0x0(r31)
	stw r29, 0x60(r1)
	xoris r0, r0, 0x8000
	lwz r10, 0x4(r31)
	mr r3, r23
	lfd f0, 0x60(r1)
	addi r4, r1, 0x34
	lwz r9, 0x8(r31)
	addi r5, r1, 0x1c
	fsubs f0, f0, f29
	stw r0, 0x6c(r1)
	lwz r7, 0x0(r24)
	addi r6, r1, 0x8
	stw r29, 0x68(r1)
	fmuls f1, f28, f0
	lfd f0, 0x68(r1)
	lwz r0, 0x4(r24)
	fadds f1, f1, f30
	stw r11, 0x10(r1)
	fsubs f0, f0, f31
	stw r10, 0x14(r1)
	stw r9, 0x18(r1)
	fmadds f0, f1, f0, f26
	stw r7, 0x28(r1)
	stw r0, 0x2c(r1)
	stfs f28, 0x10(r1)
	stfs f28, 0x14(r1)
	lwz r11, 0x10(r1)
	stfs f28, 0x18(r1)
	lwz r10, 0x14(r1)
	stfs f0, 0x28(r1)
	lwz r9, 0x18(r1)
	stfs f27, 0x2c(r1)
	lwz r7, 0x28(r1)
	lwz r0, 0x2c(r1)
	stw r30, 0x8(r1)
	stw r11, 0x1c(r1)
	stw r10, 0x20(r1)
	stw r9, 0x24(r1)
	stw r8, 0x30(r1)
	stw r7, 0x34(r1)
	stw r0, 0x38(r1)
	stw r8, 0x3c(r1)
	bl winTexSet
	li r0, 0xa
	addi r27, r27, 0x1
	divw r26, r26, r0
	@1:
	cmpw r27, r25
	blt @2
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	lmw r23, 0x7c(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot) {
	nofralloc
	stwu r1, -0x110(r1)
	mflr r0
	stw r0, 0x114(r1)
	stfd f31, 0x100(r1)
	psq_st f31, 0x108(r1), 0, 0
	stfd f30, 0xf0(r1)
	psq_st f30, 0xf8(r1), 0, 0
	stfd f29, 0xe0(r1)
	psq_st f29, 0xe8(r1), 0, 0
	stfd f28, 0xd0(r1)
	psq_st f28, 0xd8(r1), 0, 0
	stfd f27, 0xc0(r1)
	psq_st f27, 0xc8(r1), 0, 0
	stmw r30, 0xb8(r1)
	fmr f27, f1
	mr r30, r3
	fmr f28, f2
	li r3, 0x8
	fmr f29, f3
	fmr f30, f4
	fmr f31, f5
	bl camGetPtr
	lis r4, sight_wp@ha
	mr r31, r3
	addi r3, r4, sight_wp@l
	mr r5, r30
	lwz r3, 0x0(r3)
	addi r4, r1, 0x8
	lwz r3, 0x0(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	addi r3, r1, 0x8
	li r4, 0x0
	bl GXLoadTexObj
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
	li r3, 0x0
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x3
	bl GXSetTevOp
	cmpwi r30, 0x0
	bne @1
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0xf
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x6
	li r5, 0x7
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	li r3, 0x0
	li r4, 0x0
	bl GXSetTevKAlphaSel
	@1:
	lis r3, zero_bom_00007004@ha
	fmr f1, f27
	lfs f3, zero_bom_00007004@l(r3)
	fmr f2, f28
	addi r3, r1, 0x88
	bl PSMTXTrans
	lis r3, float_1_bom_00006ffc@ha
	fmr f1, f29
	lfs f3, float_1_bom_00006ffc@l(r3)
	fmr f2, f30
	addi r3, r1, 0x28
	bl PSMTXScale
	lis r4, float_deg2rad_bom_000070d4@ha
	addi r3, r1, 0x58
	addi r5, r4, float_deg2rad_bom_000070d4@l
	li r4, 0x7a
	lfs f0, 0x0(r5)
	fmuls f1, f0, f31
	bl PSMTXRotRad
	addi r4, r1, 0x28
	addi r3, r1, 0x88
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x28
	addi r4, r1, 0x58
	addi r5, r1, 0x88
	bl PSMTXConcat
	addi r4, r1, 0x88
	addi r3, r31, 0x11c
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x88
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x3
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	addi r3, r1, 0x8
	bl GXGetTexObjWidth
	extsh r31, r3
	addi r3, r1, 0x8
	bl GXGetTexObjHeight
	neg r6, r31
	lis r5, 0xcc01
	sth r6, -0x8000(r5)
	li r4, 0x0
	li r0, 0x1
	sth r3, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r3, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r0, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r0, -0x8000(r5)
	sth r0, -0x8000(r5)
	sth r6, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r4, -0x8000(r5)
	sth r0, -0x8000(r5)
	psq_l f31, 0x108(r1), 0, 0
	lfd f31, 0x100(r1)
	psq_l f30, 0xf8(r1), 0, 0
	lfd f30, 0xf0(r1)
	psq_l f29, 0xe8(r1), 0, 0
	lfd f29, 0xe0(r1)
	psq_l f28, 0xd8(r1), 0, 0
	lfd f28, 0xd0(r1)
	psq_l f27, 0xc8(r1), 0, 0
	lfd f27, 0xc0(r1)
	lmw r30, 0xb8(r1)
	lwz r0, 0x114(r1)
	mtlr r0
	addi r1, r1, 0x110
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
