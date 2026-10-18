// FAKE: PREFIX asm (F2): functions 1-20 (npc_jump .. moamoa_pose_main) in target order are asm with their C kept under #ifdef NONMATCHING; moamoa_pose_init stays real C. The prefix ends at moamoa_pose_main because randf/pose_main need the compiler int->float constant that the asm pool owns (cannot be shared from C). Named .rodata in target order; suffix C points at the named str_/float objects.
#pragma inline_max_total_size(11500)
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "string.h"
#include "memory.h"
#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "mario/mariost.h"
#include "driver/mapdrv.h"
#include "manager/evtmgr.h"
#include "driver/hitdrv.h"
#include "driver/npcdrv.h"
#include "driver/hitdrv.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/offscreendrv.h"
#include "system.h"
#define _MATH_H_
#define fabs(x) __fabs(x)
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "party.h"
#include "party/party_cloud.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "manager/evtmgr_cmd.h"
#undef EXT_LIT
#define EXT_LIT(sym, val) (val)
extern const char zero_rsh_00013c64[];
extern const char str_000041C8[];
extern const f64 double_30_rsh_00013c38;
extern const f32 float_0p03_rsh_00013b84[];
extern const f32 float_0p1_rsh_00013b80[];
extern const f32 float_0p20944_rsh_00013be4[];
extern const f32 float_0p25_rsh_00013bb0[];
extern const f32 float_0p2_rsh_00013bd8[];
extern const f32 float_0p3_rsh_00013ba0[];
extern const f32 float_0p4_rsh_00013bbc[];
extern const f32 float_0p5_rsh_00013b24[];
extern const f32 float_0p8_rsh_00013b94[];
extern const f32 float_0p9_rsh_00013bd0[];
extern const f32 float_1000_rsh_00013b1c[];
extern const f32 float_100_rsh_00013bc0[];
extern const f32 float_10_rsh_00013c24[];
extern const f32 float_135_rsh_00013bd4[];
extern const f32 float_15_rsh_00013b8c[];
extern const f32 float_180_rsh_00013bc4[];
extern const f32 float_1E06_rsh_00013c34[];
extern const f32 float_1_rsh_00013b38[];
extern const f32 float_1p02_rsh_00013c00[];
extern const f32 float_1p1_rsh_00013bfc[];
extern const f32 float_1p5_rsh_00013b90[];
extern const f32 float_200_rsh_00013b78[];
extern const f32 float_20_rsh_00013c20[];
extern const f32 float_225_rsh_00013bf8[];
extern const f32 float_290_rsh_00013c08[];
extern const f32 float_2_rsh_00013bcc[];
extern const f32 float_300_rsh_00013ba8[];
extern const f32 float_30_rsh_00013bc8[];
extern const f32 float_32767_rsh_00013b7c[];
extern const f32 float_35_rsh_00013c28[];
extern const f32 float_360_rsh_00013b2c[];
extern const f32 float_3_rsh_00013bf0[];
extern const f32 float_40_rsh_00013c30[];
extern const f32 float_50_rsh_00013b88[];
extern const f32 float_5_rsh_00013b9c[];
extern const f32 float_600_rsh_00013bac[];
extern const f32 float_60_rsh_00013b18[];
extern const f32 float_65_rsh_00013c2c[];
extern const f32 float_6_rsh_00013bec[];
extern const f32 float_6p2832_rsh_00013b28[];
extern const f32 float_90_rsh_00013bb8[];
extern const f32 zero_rsh_00013b20[];
extern const char str_00003BB8[];
extern const char str_00003BC4[];
extern const char str_00003BC8[];
extern const char str_00003BCC[];
extern const char str_00003BD8[];
extern const char str_00003BE4[];
extern const char str_00003BE8[];
extern const char str_00003BF4[];
extern const char str_00003BF8[];
extern const char str_00003C00[];
extern const char str_00003C04[];
extern const char str_00003C0C[];
extern const char str_00003C10[];
extern const char str_00003C18[];
extern const char str_00003C20[];
extern const char str_00003C28[];
extern const char str_00003D00[];
extern const char str_00003D08[];
extern const char str_00003D10[];
extern const char str_00003D20[];
extern const char str_00003D28[];
extern const char str_00003D44[];
extern const char str_00003D4C[];
extern const char str_00003D54[];
extern const char str_00003D64[];
extern const char str_00003D74[];
extern const char str_00003D7C[];
extern const char str_00003D8C[];
extern const char str_00003D9C[];
extern const char str_00003DAC[];
extern const char str_00003DBC[];
extern const char str_00003DCC[];
extern const char str_00003DDC[];
extern const char str_00003DEC[];
extern const char str_00003DFC[];
extern const char str_00003E00[];
extern const char str_00003E10[];
extern const char str_00003E20[];
extern const char str_00003E30[];
extern const char str_00003E38[];
extern const char str_00003E3C[];
extern const char str_00003E40[];
extern const char str_00003E48[];
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
extern const char str_00003ED4[];
extern const char str_00003EE0[];
extern const char str_00003EEC[];
extern const char str_00003EF8[];
extern const char str_00003F08[];
extern const char str_00003F18[];
extern const char str_00003F28[];
extern const char str_00003F38[];
extern const char str_00003F48[];
extern const char str_00003F58[];
extern const char str_00003F64[];
extern const char str_00003F70[];
extern const char str_00003F80[];
extern const char str_00003F8C[];
extern const char str_00003F94[];
extern const char str_00003FA4[];
extern const char str_00003FAC[];
extern const char str_00003FBC[];
extern const char str_00003FC4[];
extern const char str_00003FD4[];
extern const char str_00003FDC[];
extern const char str_00003FEC[];
extern const char str_00003FF0[];
extern const char str_00004000[];
extern const char str_00004008[];
extern const char str_00004010[];
extern const char str_00004020[];
extern const char str_00004030[];
extern const char str_00004040[];
extern const char str_00004050[];
extern const char str_00004060[];
extern const char str_00004068[];
extern const char str_000040C0[];
extern const char str_000041A0[];
extern const char str_000041AC[];
extern const char str_000041B0[];
extern const char str_000041B4[];
extern const char str_000041BC[];
extern const char str_00003BB8[];
extern const char str_00003BC4[];
extern const char str_00003BC8[];
extern const char str_00003BCC[];
extern const char str_00003BD8[];
extern const char str_00003BE4[];
extern const char str_00003BE8[];
extern const char str_00003BF4[];
extern const char str_00003BF8[];
extern const char str_00003C00[];
extern const char str_00003C04[];
extern const char str_00003C0C[];
extern const char str_00003C10[];
extern const char str_00003C18[];
extern const char str_00003C20[];
extern const char str_00003C28[];
extern const char str_00003D00[];
extern const char str_00003D08[];
extern const char str_00003D10[];
extern const char str_00003D20[];
extern const char str_00003D28[];
extern const char str_00003D44[];
extern const char str_00003D4C[];
extern const char str_00003D54[];
extern const char str_00003D64[];
extern const char str_00003D74[];
extern const char str_00003D7C[];
extern const char str_00003D8C[];
extern const char str_00003D9C[];
extern const char str_00003DAC[];
extern const char str_00003DBC[];
extern const char str_00003DCC[];
extern const char str_00003DDC[];
extern const char str_00003DEC[];
extern const char str_00003DFC[];
extern const char str_00003E00[];
extern const char str_00003E10[];
extern const char str_00003E20[];
extern const char str_00003E30[];
extern const char str_00003E38[];
extern const char str_00003E3C[];
extern const char str_00003E40[];
extern const char str_00003E48[];
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
extern const char str_00003ED4[];
extern const char str_00003EE0[];
extern const char str_00003EEC[];
extern const char str_00003EF8[];
extern const char str_00003F08[];
extern const char str_00003F18[];
extern const char str_00003F28[];
extern const char str_00003F38[];
extern const char str_00003F48[];
extern const char str_00003F58[];
extern const char str_00003F64[];
extern const char str_00003F70[];
extern const char str_00003F80[];
extern const char str_00003F8C[];
extern const char str_00003F94[];
extern const char str_00003FA4[];
extern const char str_00003FAC[];
extern const char str_00003FBC[];
extern const char str_00003FC4[];
extern const char str_00003FD4[];
extern const char str_00003FDC[];
extern const char str_00003FEC[];
extern const char str_00003FF0[];
extern const char str_00004000[];
extern const char str_00004008[];
extern const char str_00004010[];
extern const char str_00004020[];
extern const char str_00004030[];
extern const char str_00004040[];
extern const char str_00004050[];
extern const char str_00004060[];
extern const char str_00004068[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
#pragma force_active reset
extern const char str_00003BB8[];
extern const char str_00003BC4[];
extern const char str_00003BC8[];
extern const char str_00003BCC[];
extern const char str_00003BD8[];
extern const char str_00003BE4[];
extern const char str_00003BE8[];
extern const char str_00003BF4[];
extern const char str_00003BF8[];
extern const char str_00003C00[];
extern const char str_00003C04[];
extern const char str_00003C0C[];
extern const char str_00003C10[];
extern const char str_00003C18[];
extern const char str_00003C20[];
extern const char str_00003C28[];
extern const char str_00003D00[];
extern const char str_00003D08[];
extern const char str_00003D10[];
extern const char str_00003D20[];
extern const char str_00003D28[];
extern const char str_00003D44[];
extern const char str_00003D4C[];
extern const char str_00003D54[];
extern const char str_00003D64[];
extern const char str_00003D74[];
extern const char str_00003D7C[];
extern const char str_00003D8C[];
extern const char str_00003D9C[];
extern const char str_00003DAC[];
extern const char str_00003DBC[];
extern const char str_00003DCC[];
extern const char str_00003DDC[];
extern const char str_00003DEC[];
extern const char str_00003DFC[];
extern const char str_00003E00[];
extern const char str_00003E10[];
extern const char str_00003E20[];
extern const char str_00003E30[];
extern const char str_00003E38[];
extern const char str_00003E3C[];
extern const char str_00003E40[];
extern const char str_00003E48[];
extern const char str_00003E5C[];
extern const char str_00003E6C[];
extern const char str_00003E70[];
extern const char str_00003E80[];
extern const char str_00003E94[];
extern const char str_00003EA4[];
extern const char str_00003EAC[];
extern const char str_00003EB8[];
extern const char str_00003EC8[];
extern const char str_00003ED4[];
extern const char str_00003EE0[];
extern const char str_00003EEC[];
extern const char str_00003EF8[];
extern const char str_00003F08[];
extern const char str_00003F18[];
extern const char str_00003F28[];
extern const char str_00003F38[];
extern const char str_00003F48[];
extern const char str_00003F58[];
extern const char str_00003F64[];
extern const char str_00003F70[];
extern const char str_00003F80[];
extern const char str_00003F8C[];
extern const char str_00003F94[];
extern const char str_00003FA4[];
extern const char str_00003FAC[];
extern const char str_00003FBC[];
extern const char str_00003FC4[];
extern const char str_00003FD4[];
extern const char str_00003FDC[];
extern const char str_00003FEC[];
extern const char str_00003FF0[];
extern const char str_00004000[];
extern const char str_00004008[];
extern const char str_00004010[];
extern const char str_00004020[];
extern const char str_00004030[];
extern const char str_00004040[];
extern const char str_00004050[];
extern const char str_00004060[];
extern const char str_00004068[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 lastX; f32 lastZ; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 hitCount; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 idleFrames; EventEntry* escapeEvt; u8 field_0x48[0x4c - 0x48]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 bounceCount; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
static s32 bss_pad;
static MoamoaWork* wp;
ExtPose* extGetPosePtr(void);
s32 extGetPoseNum(void);
void extReset(void);
int rand(void);
static f32 randf(f32 min, f32 max);
static f32 randf(f32 min, f32 max);
static void moamoa_pose_init(void);
static void moamoa_pose_init(void);
static void moamoa_pose_main(void);
static void moamoa_pose_main(void);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
static inline f32 moa_sinx(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cosx(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
double sin(double x);
double cos(double x);
static void ext_moamoa_main(void);
static void ext_moamoa_main(void);
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
void extLoadShadowMtx(Mtx mtx);
void extLoadShadowRenderMode(void);
void extLoadShadowVertex(void);
void extLoadShadowTev(void);
void extDrawShadow(void);
s32 nokonokoGetStatus(PartyEntry* party);
f32 cloudGetBreathDist(void);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);

s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set_at(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set_xyz(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_xyz_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_zoom_in(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_get_item(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_add(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_select(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_change_interrupt(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_move_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_autotalkpose(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_tribe(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_setup(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_status_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_sincos(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_random(EventEntry* event, BOOL isFirstCall);
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
static void ext_moamoa_dispent(void);
static void ext_moamoa_dispent(void);
static void ext_moamoa_main(void);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_moamoa_init(void);
static void ext_moamoa_init(void);
static f32 randf(f32 min, f32 max);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void moamoa_pose_main(void);
static void moamoa_pose_init(void);
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 evt_bero_info_run[];

__declspec(section ".data") u64 fd_rsh_05_negone_one_374;
__declspec(section ".data") s32 fd_rsh_05_neg_one_382[1];
__declspec(section ".data") s32 fd_rsh_05___local_PI_383[1];
__declspec(section ".data") s32 fd_rsh_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_rsh_05_one_negone_373;
__declspec(section ".data") s32 fd_rsh_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_rsh_05_one_381[1];
__declspec(section ".data") u64 fd_rsh_05_negone_one_360;
__declspec(section ".data") s32 fd_rsh_05_neg_one_365[1];
__declspec(section ".data") s32 fd_rsh_05___local_PI_366[1];
__declspec(section ".data") s32 fd_rsh_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_rsh_05_one_negone_359;
__declspec(section ".data") s32 fd_rsh_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_rsh_05_one_364[1];
static s32 ext_moamoa_data[141];
static s32 evt_moamoa_init[57];
static s32 evt_meet_moamoa[185];
s32 evt_moamoa_help[166];
s32 evt_moamoa_escape0[15];
s32 evt_moamoa_escape1[15];
static s32 evt_moamoa_escape[228];
static s32 init_syashou[30];
static s32 talk_syashou[19];
static s32 init_waitless[30];
static s32 talk_waitless[19];
static s32 bero_data_a[45];
static s32 bero_data_b[45];
static s32 bero_data_c[45];
static s32 npc_data[69];
__declspec(section ".data") s32 evt_ghost_diary[5];
s32 evt_ghost_diary_read[53];
static s32 access_tbl[13];
static s32 evt_access[14];
static s32 evt_access2[47];
static s32 evt_access_entry[31];
s32 rsh_05_init_evt[96];
s32 rsh_05_a_init_evt[103];
s32 rsh_05_init_evt_nidome[59];
s32 rsh_05_a_init_evt_nidome[29];

__declspec(section ".data") u64 fd_rsh_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_rsh_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_rsh_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_rsh_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_rsh_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_rsh_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_rsh_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_rsh_05_one_364[] = {
    1065353216,
};

static s32 ext_moamoa_data[] = {
    (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 0, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1073741824, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4),
    1082130432, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1086324736, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1090519040, (s32)((char*)str_00003BB8),
    (s32)((char*)str_00003BC4), 1092616192, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1094713344, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1096810496,
    (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1098907648, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1099956224, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4),
    1101004800, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1102053376, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1103101952, (s32)((char*)str_00003BB8),
    (s32)((char*)str_00003BC4), 1104150528, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1105199104, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1106247680,
    (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1107296256, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1107820544, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4),
    1108344832, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC4), 1108869120, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC8), 0, (s32)((char*)str_00003BB8),
    (s32)((char*)str_00003BC8), 1082130432, (s32)((char*)str_00003BB8), (s32)((char*)str_00003BC8), 1090519040, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 0,
    (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1073741824, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1082130432, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4),
    1086324736, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1090519040, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1092616192, (s32)((char*)str_00003BCC),
    (s32)((char*)str_00003BC4), 1094713344, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1096810496, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1098907648,
    (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1099956224, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1101004800, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4),
    1102053376, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1103101952, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1104150528, (s32)((char*)str_00003BCC),
    (s32)((char*)str_00003BC4), 1105199104, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1106247680, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1107296256,
    (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1107820544, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4), 1108344832, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC4),
    1108869120, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC8), 0, (s32)((char*)str_00003BCC), (s32)((char*)str_00003BC8), 1082130432, (s32)((char*)str_00003BCC),
    (s32)((char*)str_00003BC8), 1090519040, 0, 0, 0,
};

#pragma dont_inline on
static void moamoa_pose_init(void) {
    MoamoaData* data = (MoamoaData*)ext_moamoa_data;
    s32 i = 0;
    s32 start;
    char model[32];
    char anim[32];

    strcpy(model, (char*)zero_rsh_00013c64);
    strcpy(anim, (char*)zero_rsh_00013c64);
    wp->numDefs = -1;
    do {
        if (strcmp(data->model, model)) {
            strcpy(model, data->model);
            strcpy(anim, (char*)zero_rsh_00013c64);
        }
        if (strcmp(data->anim, anim)) {
            strcpy(anim, data->anim);
            start = i;
            wp->numDefs++;
        }
        strcpy(wp->defs[wp->numDefs].model, model);
        strcpy(wp->defs[wp->numDefs].anim, anim);
        wp->defs[wp->numDefs].start = start;
        wp->defs[wp->numDefs].count = i - start + 1;
        wp->defs[wp->numDefs].speed = data->speed;
        wp->defs[wp->numDefs].loop = 1;
        if (!strncmp(anim, (char*)str_000041C8, 1)) {
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}

#ifdef NONMATCHING
static void moamoa_pose_main(void) {
    f32 t;
    u64 now;
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    MoamoaPoseDef* def;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = float_60_rsh_00013b18[0] * OSTicksToMilliseconds(now - moa->startTime) / float_1000_rsh_00013b1c[0] / def->speed;

        if (t >= float_1_rsh_00013b38[0]) {
            moa->startTime = now;
            t = zero_rsh_00013b20[0];
        }
        pose->frame = def->start + (s32)((def->count - 1) * t);
    }
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
static const char* group_tbl[][2] = {
    {((char*)str_00003BB8), ((char*)str_00003BC4)},
    {((char*)str_00003BCC), ((char*)str_00003BC4)},
    {((char*)str_00003BD8), ((char*)str_00003BE4)},
    {((char*)str_00003BE8), ((char*)str_00003BF4)},
    {((char*)str_00003BF8), ((char*)str_00003C00)},
    {((char*)str_00003C04), ((char*)str_00003C0C)},
    {((char*)str_00003C10), ((char*)str_00003BE4)},
    {((char*)str_00003C18), ((char*)str_00003BE4)},
    {((char*)str_00003C20), ((char*)str_00003BE4)},
    {((char*)str_00003C28), ((char*)str_00003BE4)},
    {((char*)str_00003BB8), ((char*)str_00003BC4)},
};
#else
extern const char str_00003BB8[];
extern const char str_00003BC4[];
extern const char str_00003BCC[];
extern const char str_00003BD8[];
extern const char str_00003BE4[];
extern const char str_00003BE8[];
extern const char str_00003BF4[];
extern const char str_00003BF8[];
extern const char str_00003C00[];
extern const char str_00003C04[];
extern const char str_00003C0C[];
extern const char str_00003C10[];
extern const char str_00003C18[];
extern const char str_00003C20[];
extern const char str_00003C28[];
__declspec(section ".data") static u32 g5_group_tbl_s582[22] = { (u32)(char*)str_00003BB8, (u32)(char*)str_00003BC4, (u32)(char*)str_00003BCC, (u32)(char*)str_00003BC4, (u32)(char*)str_00003BD8, (u32)(char*)str_00003BE4, (u32)(char*)str_00003BE8, (u32)(char*)str_00003BF4, (u32)(char*)str_00003BF8, (u32)(char*)str_00003C00, (u32)(char*)str_00003C04, (u32)(char*)str_00003C0C, (u32)(char*)str_00003C10, (u32)(char*)str_00003BE4, (u32)(char*)str_00003C18, (u32)(char*)str_00003BE4, (u32)(char*)str_00003C20, (u32)(char*)str_00003BE4, (u32)(char*)str_00003C28, (u32)(char*)str_00003BE4, (u32)(char*)str_00003BB8, (u32)(char*)str_00003BC4 };
__declspec(section ".data") static u32 g5_mt_s746[12] = { 0x41000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000, 0x3F000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000 };
#endif
#ifdef NONMATCHING
static inline void /**/ moamoa_pose_change_i(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = (char*)str_000041AC;
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
            if (strncmp(anim, (char*)str_000041B0, 1)) {
                return;
            }
        }
        if (moa->flags & 0x10) {
            if (strncmp(anim, (char*)str_000041B4, 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = (char*)str_000041AC;
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
            if (strncmp(anim, (char*)str_000041B0, 1)) {
                return;
            }
        }
        if (moa->flags & 0x10) {
            if (strncmp(anim, (char*)str_000041B4, 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
#endif
#pragma dont_inline reset

#ifdef NONMATCHING
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);

    if (on) {
        wp->flags |= mask;
    } else {
        wp->flags &= ~mask;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall) {
    extReset();
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    for (i = 0; i < wp->count; i++, pose++) {
        pose->field_0x14 = zero_rsh_00013b20[0];
        pose->field_0x1c = zero_rsh_00013b20[0];
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    Moamoa* moa;

    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (!(moa->flags & 0x20)) {
            return EVT_RETURN_BLOCK;
        }
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;

    if (isFirstCall) {
        pose = extGetPosePtr();
        moa = wp->moa;
        for (i = 0; i < wp->count; i++, pose++, moa++) {
            pose->mtx[2][2] = float_1_rsh_00013b38[0];
            pose->mtx[1][1] = float_1_rsh_00013b38[0];
            pose->mtx[0][0] = float_1_rsh_00013b38[0];
            moa->next = 14;
            moa->state = 14;
            moa->timer = i < 100 ? i % 100 : i % 60 + 100;
            moa->flags |= 0x100;
        }
    }
    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (!(moa->flags & 0x200)) {
            return EVT_RETURN_BLOCK;
        }
    }
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        pose->flags |= 4;
        moa->flags |= 0x400;
        moa->state = 61;
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    s32 all = evtGetValue(event, args[1]);
    s32 i;
    Moamoa* moa;

    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (on) {
            if (!all) {
                if (moa->kind == 1) {
                    moa->flags |= 0x800;
                }
            } else {
                moa->flags |= 0x800;
            }
        } else {
            if (!all) {
                if (moa->kind != 1) {
                    moa->flags &= ~0x800;
                }
            } else {
                moa->flags &= ~0x800;
            }
        }
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    Moamoa* moa;

    evtGetValue(event, event->args[0]);
    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        moa->flags &= ~0x400;
        moa->state = 63;
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall) {
    s32 i;
    ExtPose* pose = extGetPosePtr();
    Moamoa* moa = wp->moa;

    for (i = 0; i < wp->count; i++, pose++, moa++) {
        pose->flags |= 4;
        moa->flags |= 0x400;
        moa->flags |= 0x100;
        moa->flags |= 0x200;
        moa->state = 61;
        moa->flags |= 0x800;
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall) {
    s32 i = evtGetValue(event, event->args[0]);

    wp->target[i] = wp->target[1 - i];
    wp->field_0x3a[i] = 100;
    if (i == 0) {
        wp->flags |= 0x1000;
    } else {
        wp->flags |= 0x2000;
    }
    return EVT_RETURN_DONE;
}
#endif

int rand(void);

#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / float_32767_rsh_00013b7c[0];

    return r * (max - min) + min;
}
#endif

#ifdef NONMATCHING
static void ext_moamoa_init(void) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    f32 hitX, hitY, hitZ, hitDist, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = npcNameToPtr("ウェイトレス")->position;
    wp->target[1] = npcNameToPtr("車掌")->position;
    wp->target[2] = (Vec){-float_290_rsh_00013c08[0], float_65_rsh_00013c2c[0], -95.0f};
    wp->count = extGetPoseNum();
    wp->moa = _mapAlloc(wp->count * sizeof(Moamoa));
    memset(wp->moa, 0, wp->count * sizeof(Moamoa));
    moamoa_pose_init();
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        moa->flags = 0;
        moa->state = 0;
        moa->timer = 0;
        moamoa_pose_change_i(moa, (char*)str_00003BB8, (char*)str_00003BC4);
        pose->flags |= 3;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-float_290_rsh_00013c08[0], 240.0f);
        pose->mtx[1][3] = zero_rsh_00013b20[0];
        pose->mtx[2][3] = randf(-130.0f, float_50_rsh_00013b88[0]);
        hitX = hitY = hitZ = zero_rsh_00013b20[0];
        hitDist = float_1E06_rsh_00013c34[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &nx, &ny, &nz, pose->mtx[0][3], float_100_rsh_00013bc0[0] + pose->mtx[1][3], pose->mtx[2][3], zero_rsh_00013b20[0], -float_1_rsh_00013b38[0], zero_rsh_00013b20[0])) {
            pose->mtx[1][3] = hitY;
        }
    }
    wp->mobj = mapGetMapObj((char*)str_000041BC);
    wp->mobjY = *(f32*)((u8*)wp->mobj + 0x98);
    for (i = 0; i < 600; i++) {
        ext_moamoa_main();
    }
}
#endif

#ifdef NONMATCHING
static void ext_disp(CameraId camera, void* param) {
    u16 left, top, right, bottom;

    if (camera == CAMERA_OFFSCREEN2) {
        GXClearBoundingBox();
    }
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    if (camera == CAMERA_OFFSCREEN2) {
        sysWaitDrawSync();
        GXReadBoundingBox(&left, &top, &right, &bottom);
        offscreenAddBoundingBox(offscreenNameToId((char*)str_000041A0), left, top, right, bottom);
    }
}
#endif

#ifdef NONMATCHING
static void ext_shadow_disp(CameraId camera, void* param) {
    static Mtx mt = {
        {8.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 8.0f, 0.0f, 0.5f},
        {0.0f, 0.0f, 8.0f, 0.0f},
    };
    u16 left, top, right, bottom;

    if (camera == CAMERA_OFFSCREEN2) {
        GXClearBoundingBox();
    }
    extLoadShadowMtx(mt);
    extLoadShadowRenderMode();
    extLoadShadowVertex();
    extLoadShadowTev();
    extDrawShadow();
    if (camera == CAMERA_OFFSCREEN2) {
        sysWaitDrawSync();
        GXReadBoundingBox(&left, &top, &right, &bottom);
        offscreenAddBoundingBox(offscreenNameToId((char*)str_000041A0), left, top, right, bottom);
    }
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;
    f32 dy;
    f32 d;
    f32 angle;

    if (checkGround) {
        hitX = hitY = hitZ = zero_rsh_00013b20[0];
        dist = float_1E06_rsh_00013c34[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, x, float_100_rsh_00013bc0[0] + y, z, zero_rsh_00013b20[0], -float_1_rsh_00013b38[0], zero_rsh_00013b20[0])) {
            if (fabs(y - hitY) > double_30_rsh_00013c38) {
                speed -= float_0p1_rsh_00013b80[0];
                gravity += float_0p1_rsh_00013b80[0];
            }
            y = hitY;
        }
    }
    moa->target = (Vec){x, y, z};
    moa->speed = speed;
    moa->gravity = gravity;
    dy = moa->target.y - pose->mtx[1][3];
    d = distABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z);
    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z);
    moa->jumpTimer = d / moa->speed;
    moa->vy = dy / moa->jumpTimer + moa->gravity * moa->jumpTimer / 2;
    moa->state = 3;
    moa->next = next;
    pose->rot = float_180_rsh_00013bc4[0] + angle;
    moa->flags |= 2;
    pose->flags |= 0x10;
    pose->flags &= ~4;
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa) {
    MarioWork* mario = marioGetPtr();
    CameraEntry* cam;
    f32 range;
    f32 dist;
    f32 angle;
    f32 rad;
    Vec a, b, c, d, e, f;

    if (mario->position.y > float_20_rsh_00013c20[0] + pose->mtx[1][3]) {
        return 0;
    }
    if (pose->mtx[1][3] > mario->position.y + mario->wPlayerCollisionBox.y) {
        return 0;
    }
    if (distABf(pose->mtx[0][3], pose->mtx[2][3], mario->position.x, mario->position.z) < (float_20_rsh_00013c20[0] + mario->wPlayerCollisionBox.x) / float_2_rsh_00013bcc[0]
        && mario->position.y > float_10_rsh_00013c24[0] + pose->mtx[1][3] && (mario->flags & 0x20000) && !(mario->flags & 0x10000)
        && wp->bounceCount < 2) {
        if (mario->currMotionId != 0x16 && mario->currMotionId != 0x1a) {
            marioChgMot(5);
        }
        wp->bounceCount++;
        return 1;
    }
    if (!(mario->flags & 0x30000)) {
        wp->bounceCount = 0;
    }
    if (mario->currMotionId == 0x12 && wp->field_0x40 > 10) {
        rad = float_6p2832_rsh_00013b28[0] * reviseAngle(camGetPtr(CAMERA_3D)->viewYaw + (mario->displayDirection - float_90_rsh_00013bb8[0])) / float_360_rsh_00013b2c[0];
        dist = float_35_rsh_00013c28[0] * moa_sinx(rad) + mario->position.x;
        if (distABf(pose->mtx[0][3], pose->mtx[2][3], dist, mario->position.z - float_35_rsh_00013c28[0] * moa_cosx(rad)) < float_35_rsh_00013c28[0]) {
            return 2;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14) {
        f32 (*mtx)[4] = pose->mtx;
        a = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&mario->position, &a) < float_65_rsh_00013c2c[0]) {
            return 2;
        }
    }
    if (wp->breathDir >= zero_rsh_00013b20[0]) {
        f32 (*mtx)[4] = pose->mtx;
        b = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&wp->breathPos, &b) < float_30_rsh_00013bc8[0]) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        f32 (*mtx)[4] = pose->mtx;
        c = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < float_30_rsh_00013bc8[0]) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == 3 && partyGetPtr(0)->useMotionId == 0x46) {
        f32 (*mtx)[4] = pose->mtx;
        d = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < float_50_rsh_00013b88[0]) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, pose->mtx[1][3], mario->position.z};
    f = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
    range = (float_20_rsh_00013c20[0] + mario->wPlayerCollisionBox.x) / float_2_rsh_00013bcc[0];
    if (PSVECDistance(&e, &f) < range) {
        pose->mtx[0][3] = moa->lastX;
        pose->mtx[2][3] = moa->lastZ;
        {
        f32 (*mtx)[4] = pose->mtx;
        f = (Vec){mtx[0][3], mtx[1][3], mtx[2][3]};
        }
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < float_40_rsh_00013c30[0]) {
                mario->unk174.x = -((range - dist) * moa_sinx(float_6p2832_rsh_00013b28[0] * mario->directionView / float_360_rsh_00013b2c[0]));
                mario->unk174.z = (range - dist) * moa_cosx(float_6p2832_rsh_00013b28[0] * mario->directionView / float_360_rsh_00013b2c[0]);
            } else {
                mario->unk174.x = pose->mtx[0][3] - range * moa_sinx(float_6p2832_rsh_00013b28[0] * angle / float_360_rsh_00013b2c[0]) - mario->position.x;
                mario->unk174.z = pose->mtx[2][3] + range * moa_cosx(float_6p2832_rsh_00013b28[0] * angle / float_360_rsh_00013b2c[0]) - mario->position.z;
            }
        }
    }
    return 0;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#pragma dont_inline reset

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING  // restored C definition (nmrepair)
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
#endif
#ifdef NONMATCHING
static void ext_moamoa_main(void) {
    MarioWork* mario;
    PartyEntry* party;
    const char* voice;
    ExtPose* pose;
    Moamoa* moa;
    s32 i;
    s32 hit;
    s32 sfx;
    s32 ret;
    f32 y;
    f32 a;
    f32 rad;
    f32 s;
    f32 z;
    f32 d;
    f32 t;
    f32 r;
    f32 x;
    Mtx m1;
    Mtx m;
    Vec sp2_;
    Vec v;

    mario = marioGetPtr();
    party = partyGetPtr(0);
    camGetPtr(CAMERA_3D);
    hit = 0;
    if (mario->currMotionId == 0x12) {
        wp->field_0x40++;
    } else {
        wp->field_0x40 = 0;
    }
    if (mario->currMotionId == 0) {
        wp->idleFrames++;
        if (wp->idleFrames > 1000) {
            wp->idleFrames = 1000;
        }
    } else {
        wp->idleFrames = 0;
    }
    if (party->flags & 0x100) {
        wp->flags |= 0x10;
    } else {
        wp->flags &= ~0x10;
    }
    wp->breathDir = -float_1_rsh_00013b38[0];
    wp->breathDist = -float_1_rsh_00013b38[0];
    if (party->currentMemberId == 5 && (party->flags & 0x100)) {
        wp->breathDir = cloudGetBreathDir();
        wp->breathDist = cloudGetBreathDist();
        wp->breathPos.x = wp->breathDist * moa_sinx(float_6p2832_rsh_00013b28[0] * wp->breathDir / float_360_rsh_00013b2c[0]) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - wp->breathDist * moa_cosx(float_6p2832_rsh_00013b28[0] * wp->breathDir / float_360_rsh_00013b2c[0]);
    }
    if (wp->field_0x3a[0] > 50) {
        wp->target[0] = wp->target[1];
        if (!(wp->flags & 0x1000)) {
            wp->flags |= 0x1000;
            evtEntry(evt_moamoa_escape0, 0, 0);
        }
    }
    if (wp->field_0x3a[1] > 50) {
        wp->target[1] = wp->target[0];
        if (!(wp->flags & 0x2000)) {
            wp->flags |= 0x2000;
            evtEntry(evt_moamoa_escape1, 0, 0);
        }
    }
    if ((wp->flags & 0x1000) && (wp->flags & 0x2000)) {
        s32 j;
        Moamoa* m2;

        extGetPosePtr();
        m2 = wp->moa;
        for (j = 0; j < wp->count; j++, m2++) {
            if (m2->flags & 4) {
                continue;
            }
            if (m2->flags & 0x10) {
                break;
            }
            m2->state = 0x19;
            m2->timer = 0;
            m2->flags |= 0x10;
        }
        if (wp->escapeEvt == NULL) {
            wp->escapeEvt = evtEntry(evt_moamoa_escape, 0, 0);
        }
    }

    pose = extGetPosePtr();
    sfx = 0;
    moa = wp->moa;
    voice = (char*)str_000040C0;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        if ((wp->flags & 1) && !(wp->flags & 4) && !marioKeyOffChk() && !marioCtrlOffChk() && !hit && !(moa->flags & 0x154)) {
            ret = moamoa_hit_check(pose, moa);
            if (ret == 1) {
                moa->flags |= 4;
                moa->state = 0x24;
                {
                s32 idx;
                wp->hitCount++;
                idx = i % 3;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < float_200_rsh_00013b78[0]) {
                    wp->field_0x3a[idx]++;
                }
                }
                moamoa_pose_change(moa, (char*)str_00003BB8, (char*)str_00003BC8);
                hit = 1;
            } else if (ret == 2 || ret == 4) {
                moa->flags |= 0xc;
                moa->state = 0x2f;
                {
                s32 idx;
                wp->hitCount++;
                idx = i % 3;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < float_200_rsh_00013b78[0]) {
                    wp->field_0x3a[idx]++;
                }
                }
                moamoa_pose_change(moa, (char*)str_00003BB8, (char*)str_00003BC8);
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                x = wp->breathDir + wp->angle;
                x *= float_0p5_rsh_00013b24[0];
                moa->flags |= 0x84;
                moa->state = 0x30;
                moa->target = moamoa_zero_vec;
                s = randf(float_0p1_rsh_00013b80[0], float_0p2_rsh_00013bd8[0]);
                rad = float_6p2832_rsh_00013b28[0] * x / float_360_rsh_00013b2c[0];
                moa->vy = s * moa_sinx(rad);
                moa->speed = randf(float_0p03_rsh_00013b84[0], 0.06f);
                moa->gravity = s * -moa_cosx(rad);
                moa->jumpTimer = 120;
                {
                s32 idx;
                wp->hitCount++;
                idx = i % 3;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < float_200_rsh_00013b78[0]) {
                    wp->field_0x3a[idx]++;
                }
                }
                moamoa_pose_change(moa, (char*)str_00003BB8, (char*)str_00003BC8);
                hit = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x155) && wp->dist < float_50_rsh_00013b88[0]) {
            if (moa->flags & 2) {
                moa->next = 1;
            } else {
                moa->state = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x444) && i == gp->retraceCount % wp->count && irand(1000) < 200) {
            sp2_ = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]}; psndSFXOn_3D(voice, &sp2_);
        }
        switch (moa->state) {
            case 0:
                if (i % 133 < 100) {
                    a = randf(zero_rsh_00013b20[0], float_6p2832_rsh_00013b28[0]);
                    d = randf(zero_rsh_00013b20[0], float_50_rsh_00013b88[0]);
                    {
                        f32 rad;
                        f32 tx = wp->target[i % 3].x + d * moa_sinx(a);
                        f32 tz = wp->target[i % 3].z - d * moa_cosx(a);
                        rad = float_6p2832_rsh_00013b28[0] * angleABf(pose->mtx[0][3], pose->mtx[2][3], tx, tz) / float_360_rsh_00013b2c[0];
                    x = pose->mtx[0][3] + float_15_rsh_00013b8c[0] * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - float_15_rsh_00013b8c[0] * moa_cosx(rad);
                    }
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, rand() / float_32767_rsh_00013b7c[0] * (float_3_rsh_00013bf0[0] - float_1p5_rsh_00013b90[0]) + float_1p5_rsh_00013b90[0], rand() / float_32767_rsh_00013b7c[0] * (float_2_rsh_00013bcc[0] - float_0p8_rsh_00013b94[0]) + float_0p8_rsh_00013b94[0]);
                    moa->flags |= 1;
                } else {
                    d = distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                    { f32 a = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                    f32 rad;
                    if (d < float_200_rsh_00013b78[0]) {
                        a = randf(zero_rsh_00013b20[0], float_360_rsh_00013b2c[0]);
                    }
                    rad = float_6p2832_rsh_00013b28[0] * a / float_360_rsh_00013b2c[0];
                    x = pose->mtx[0][3] + float_5_rsh_00013b9c[0] * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - float_5_rsh_00013b9c[0] * moa_cosx(rad); }
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, rand() / float_32767_rsh_00013b7c[0] * (float_0p5_rsh_00013b24[0] - float_0p3_rsh_00013ba0[0]) + float_0p3_rsh_00013ba0[0], rand() / float_32767_rsh_00013b7c[0] * (float_0p8_rsh_00013b94[0] - float_0p5_rsh_00013b24[0]) + float_0p5_rsh_00013b24[0]);
                    moa->flags &= ~1;
                }
                break;
            case 50:
                if (--moa->timer < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 51:
                moa->speed = randf(zero_rsh_00013b20[0], float_200_rsh_00013b78[0]);
                moa->gravity = randf(zero_rsh_00013b20[0], float_300_rsh_00013ba8[0] * moa->speed / float_200_rsh_00013b78[0]);
                moa->state++;
                moa->timer = 0;
            case 52:
                {
                t = moa->timer < 200 ? float_1_rsh_00013b38[0] : (800 - moa->timer) / float_600_rsh_00013bac[0];
                if (t < zero_rsh_00013b20[0]) {
                    t = zero_rsh_00013b20[0];
                    moa->flags |= 0x200;
                }
                x = wp->target[i % 3].x;
                y = wp->target[i % 3].y;
                z = wp->target[i % 3].z;
                x += t * (moa->gravity * (f32)sin((f32)(i + gp->retraceCount) * float_0p25_rsh_00013bb0[0]));
                                r = i + gp->retraceCount;
                y += moa->speed * t;
                z += t * (-moa->gravity * (f32)cos(r * float_0p25_rsh_00013bb0[0]));

                pose->mtx[0][3] += (x - pose->mtx[0][3]) / float_15_rsh_00013b8c[0];
                pose->mtx[1][3] += (y - pose->mtx[1][3]) / float_15_rsh_00013b8c[0];
                pose->mtx[2][3] += (z - pose->mtx[2][3]) / float_15_rsh_00013b8c[0];
                moa->timer++;
                }
                break;
            case 1:
                {
                f32 rad;
                {
                f32 a = wp->angle + randf(-45.0f, 45.0f);
                rad = float_6p2832_rsh_00013b28[0];
                rad = rad * a / float_360_rsh_00013b2c[0];
                }
                x = pose->mtx[0][3] + float_15_rsh_00013b8c[0] * moa_sinx(rad);
                d = wp->dist;
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - float_15_rsh_00013b8c[0] * moa_cosx(rad);
                { f32 k; f32 r1 = rand() / float_32767_rsh_00013b7c[0]; t = r1 * (k = float_1_rsh_00013b38[0] - float_1_rsh_00013b38[0]) + float_1_rsh_00013b38[0];
                moamoa_jump(pose, moa, d < float_100_rsh_00013bc0[0] ? moa->state : 0, 1, x, y, z, t, randf(float_0p4_rsh_00013bbc[0], float_0p4_rsh_00013bbc[0])); }
                                }
                break;
            case 2:
                { f32 r;
                r = wp->angle + randf(-45.0f, 45.0f);
                a = r + float_180_rsh_00013bc4[0];
                d = wp->dist;
                {
                f32 rad = float_6p2832_rsh_00013b28[0] * a / float_360_rsh_00013b2c[0];
                x = pose->mtx[0][3] + float_30_rsh_00013bc8[0] * moa_sinx(rad);
                }
                y = pose->mtx[1][3];
                z = pose->mtx[2][3];
                { f32 a1 = float_2_rsh_00013bcc[0] * randf(float_1_rsh_00013b38[0], float_1_rsh_00013b38[0]); f32 a2 = float_2_rsh_00013bcc[0] * randf(float_0p4_rsh_00013bbc[0], float_0p4_rsh_00013bbc[0]); moamoa_jump(pose, moa, d < float_100_rsh_00013bc0[0] ? moa->state : 0, 1, x, y, z, a1, a2); } }
                break;
            case 3:
                pose->mtx[1][3] += moa->vy;
                moa->vy -= moa->gravity;
                {
                f32 rad = float_6p2832_rsh_00013b28[0] * angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z) / float_360_rsh_00013b2c[0];
                pose->mtx[0][3] += moa->speed * moa_sin(rad);
                pose->mtx[2][3] += moa->speed * -moa_cos(rad);
                }
                if (--moa->jumpTimer < 0) {
                    pose->mtx[0][3] = moa->target.x;
                    pose->mtx[1][3] = moa->target.y;
                    pose->mtx[2][3] = moa->target.z;
                    moa->flags &= ~2;
                    pose->flags &= ~0x10;
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 4:
                if (++moa->timer > 4) {
                    moa->state = moa->next;
                }
                break;
            case 36:
            case 37:
            case 38:
                if (!(moa->flags & 1)) {
                    x = mario->position.x;
                    z = mario->position.z;
                } else {
                    x = wp->target[i % 3].x;
                    z = wp->target[i % 3].z;
                }
                {
                f32 r1 = rand() / float_32767_rsh_00013b7c[0];
                f32 rad = float_6p2832_rsh_00013b28[0] * (angleABf(x, z, pose->mtx[0][3], pose->mtx[2][3]) + (r1 * (45.0f - -45.0f) + -45.0f)) / float_360_rsh_00013b2c[0];
                x = pose->mtx[0][3] + float_15_rsh_00013b8c[0] * moa_sinx(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - float_15_rsh_00013b8c[0] * moa_cosx(rad);
                }
                { f32 k; f32 r1 = rand() / float_32767_rsh_00013b7c[0]; f32 r2 = rand() / float_32767_rsh_00013b7c[0]; k = float_1_rsh_00013b38[0] - float_1_rsh_00013b38[0]; moamoa_jump(pose, moa, moa->state + 1, 1, x, y, z, r1 * k + float_1_rsh_00013b38[0], r2 * k + float_1_rsh_00013b38[0]); }
                break;
            case 39:
                if (++moa->timer < 30) {
                    pose->mtx[0][0] *= float_0p9_rsh_00013bd0[0];
                    pose->mtx[1][1] *= float_0p9_rsh_00013bd0[0];
                    pose->mtx[2][2] *= float_0p9_rsh_00013bd0[0];
                } else {
                    moa->state = 0x31;
                }
                break;
            case 47:
                { f32 x;
                a = rand() / float_32767_rsh_00013b7c[0];
                d = rand() / float_32767_rsh_00013b7c[0];
                rad = float_6p2832_rsh_00013b28[0] * (a * (float_225_rsh_00013bf8[0] - float_135_rsh_00013bd4[0]) + float_135_rsh_00013bd4[0]) / float_360_rsh_00013b2c[0];
                d = d * (500.0f - float_300_rsh_00013ba8[0]) + float_300_rsh_00013ba8[0];
                x = d * moa_sinx(rad) + pose->mtx[0][3];
                z = pose->mtx[2][3] - d * moa_cosx(rad);
                a = rand() / float_32767_rsh_00013b7c[0] * (float_6_rsh_00013bec[0] - float_5_rsh_00013b9c[0]) + float_5_rsh_00013b9c[0];
                s = rand() / float_32767_rsh_00013b7c[0] * (float_0p3_rsh_00013ba0[0] - float_0p2_rsh_00013bd8[0]) + float_0p2_rsh_00013bd8[0];
                if (!sfx) {
                    psndSFXOn_3D((const char*)0x6c3, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                    sfx = 1;
                }
                moamoa_jump(pose, moa, 0x31, 0, x, -float_100_rsh_00013bc0[0], z, a, s); }
                break;
            case 48:
                if (--moa->jumpTimer > 0) {
                    moa->target.x += moa->vy;
                    moa->target.y += moa->speed;
                    moa->target.z += moa->gravity;
                    pose->mtx[0][3] += moa->target.x;
                    pose->mtx[1][3] += moa->target.y;
                    pose->mtx[2][3] += moa->target.z;
                } else {
                    moa->state = 0x31;
                }
                break;
            case 49:
                if ((wp->flags & 0x1000) && (wp->flags & 0x2000)) {
                    moa->state = 0x3e;
                } else if (wp->hitCount < 500) {
                    PSMTXIdentity(pose->mtx);
                    pose->mtx[0][3] = wp->target[i % 3].x;
                    pose->mtx[1][3] = wp->target[i % 3].y;
                    pose->mtx[2][3] = wp->target[i % 3].z;
                    moa->flags = 0;
                    moa->state = 0;
                    moa->timer = 0;
                } else {
                    moa->state = 0x3e;
                }
                break;
            case 25:
                if (moa->timer < 30) {
                    PSMTXRotRad(m1, 'y', float_0p20944_rsh_00013be4[0]);
                    PSMTXConcat(pose->mtx, m1, pose->mtx);
                    pose->flags &= ~2;
                    moa->timer++;
                } else {
                    pose->flags |= 2;
                    moa->timer = rand() % 30;
                    moa->state++;
                }
                break;
            case 26:
                if (--moa->timer < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 27:
                d = distABf(pose->mtx[0][3], pose->mtx[2][3], -275.0f, -float_100_rsh_00013bc0[0]);
                { f32 r1 = rand() / float_32767_rsh_00013b7c[0];
                a = angleABf(pose->mtx[0][3], pose->mtx[2][3], -275.0f, -float_100_rsh_00013bc0[0]);
                a += r1 * (45.0f - -45.0f) + -45.0f; }
                if (d > float_6_rsh_00013bec[0] && (y = pose->mtx[1][3]) < float_60_rsh_00013b18[0]) {
                    f32 rad = float_6p2832_rsh_00013b28[0] * a / float_360_rsh_00013b2c[0];
                    x = pose->mtx[0][3] + float_15_rsh_00013b8c[0] * moa_sinx(rad);
                    z = pose->mtx[2][3] - float_15_rsh_00013b8c[0] * moa_cosx(rad);
                    { f32 k; f32 r1 = rand() / float_32767_rsh_00013b7c[0]; f32 r2 = rand() / float_32767_rsh_00013b7c[0]; moamoa_jump(pose, moa, moa->state, 1, x, y, z, float_3_rsh_00013bf0[0] * (r1 * (k = float_1_rsh_00013b38[0] - float_1_rsh_00013b38[0]) + float_1_rsh_00013b38[0]), r2 * k + float_1_rsh_00013b38[0]); }
                } else {
                    moa->state++;
                }
                break;
            case 28:
                if (pose->mtx[0][3] > -350.0f) {
                    f32 rad;
                    f32 r1 = rand() / float_32767_rsh_00013b7c[0];
                    rad = float_6p2832_rsh_00013b28[0] * (angleABf(pose->mtx[0][3], pose->mtx[2][3], -350.0f, -float_100_rsh_00013bc0[0]) + (r1 * (45.0f - -45.0f) + -45.0f)) / float_360_rsh_00013b2c[0];
                    x = pose->mtx[0][3] + float_15_rsh_00013b8c[0] * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - float_15_rsh_00013b8c[0] * moa_cosx(rad);
                    { f32 k; f32 r1 = rand() / float_32767_rsh_00013b7c[0]; f32 r2 = rand() / float_32767_rsh_00013b7c[0]; moamoa_jump(pose, moa, moa->state, 1, x, y, z, float_3_rsh_00013bf0[0] * (r1 * (k = float_1_rsh_00013b38[0] - float_1_rsh_00013b38[0]) + float_1_rsh_00013b38[0]), r2 * k + float_1_rsh_00013b38[0]); }
                } else {
                    moa->state = 0x3e;
                }
                break;
            case 62:
                moa->flags |= 0x20;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63:
                { f32 k; f32 r1 = rand() / float_32767_rsh_00013b7c[0];
                s = randf(float_2_rsh_00013bcc[0], float_3_rsh_00013bf0[0]);
                moa->timer = irand(i / 2);
                rad = float_6p2832_rsh_00013b28[0] * (r1 * (k = 315.0f - float_225_rsh_00013bf8[0]) + float_225_rsh_00013bf8[0]) / float_360_rsh_00013b2c[0]; }
                moa->target.x = s * moa_sinx(rad);
                moa->target.y = randf(float_1_rsh_00013b38[0], float_2_rsh_00013bcc[0]);
                moa->target.z = s * -moa_cosx(rad);
                moa->state++;
                break;
            case 64:
                if (--moa->timer < 0) {
                    moa->state++;
                }
                break;
            case 65:
                moa->target.x *= float_1p1_rsh_00013bfc[0];
                moa->target.y *= float_1p02_rsh_00013c00[0];
                moa->target.z *= float_1p1_rsh_00013bfc[0];
                pose->mtx[0][3] += moa->target.x;
                pose->mtx[1][3] += moa->target.y;
                pose->mtx[2][3] += moa->target.z;
                PSMTXRotRad(m, 'y', float_0p20944_rsh_00013be4[0]);
                PSMTXConcat(pose->mtx, m, pose->mtx);
                pose->flags &= ~2;
                if (pose->mtx[0][3] < -float_1000_rsh_00013b1c[0]) {
                    moa->state = 0x3e;
                }
                break;
        }
        if (!(moa->flags & 0x98)) {
            if (pose->mtx[0][3] > float_290_rsh_00013c08[0]) {
                pose->mtx[0][3] = float_290_rsh_00013c08[0];
            }
            if (pose->mtx[0][3] < -float_290_rsh_00013c08[0]) {
                pose->mtx[0][3] = -float_290_rsh_00013c08[0];
            }
            if (pose->mtx[2][3] > float_50_rsh_00013b88[0]) {
                pose->mtx[2][3] = float_50_rsh_00013b88[0];
            }
            if (pose->mtx[2][3] < -130.0f) {
                pose->mtx[2][3] = -130.0f;
            }
        }
        pose->mtx[1][3] += wp->mobj->modelWorldMtx[1][3] - wp->mobjY;
        moa->lastX = pose->mtx[0][3];
        moa->lastZ = pose->mtx[2][3];
    }
    moamoa_pose_main();
    wp->mobjY = wp->mobj->modelWorldMtx[1][3];
    if (wp->flags & 0x10) {
        static const Vec zv2 = {0.0f, 0.0f, 0.0f};
        mario->unk174.x = zero_rsh_00013b20[0];
        mario->unk174.y = zero_rsh_00013b20[0];
        mario->unk174.z = zero_rsh_00013b20[0];
    } else {
        v = (Vec){mario->unk174.x, mario->unk174.y, mario->unk174.z};
        if (PSVECMag(&v) > float_2_rsh_00013bcc[0]) {
            PSVECNormalize(&v, &v);
            mario->unk174.x = float_2_rsh_00013bcc[0] * v.x;
            mario->unk174.y = float_2_rsh_00013bcc[0] * v.y;
            mario->unk174.z = float_2_rsh_00013bcc[0] * v.z;
        }
    }
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#pragma dont_inline reset

#ifdef NONMATCHING
static void ext_moamoa_dispent(void) {
    if (wp->flags & 1) {
        dispEntry(CAMERA_3D, zero_rsh_00013b20[0], 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, zero_rsh_00013b20[0], 2, ext_shadow_disp, NULL);
    }
    if (wp->flags & 2) {
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 2, ext_shadow_disp, NULL);
    }
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    f32 gravity = evtGetFloat(event, args[5]);
    s32 frames = evtGetValue(event, args[6]);
    f32 t = float_60_rsh_00013b18[0] * frames / float_1000_rsh_00013b1c[0];
    NpcEntry* npc = npcNameToPtr(name);
    f32 dy;
    f32 vy;
    f32 dist;
    f32 angle;

    if (isFirstCall) {
        static const Vec va = {0.0f, 0.0f, 0.0f};
        static const Vec vb = {0.0f, 0.0f, 0.0f};
        Vec a;
        Vec b;

        b = vb; b.x = npc->position.x; b.z = npc->position.z;
        a = va; a.x = x; a.z = z;
        dist = PSVECDistance(&a, &b);
        dy = y - npc->position.y;
        if (t == zero_rsh_00013b20[0]) {
            t = dist / speed;
        } else {
            speed = dist / t;
        }
        vy = dy / t + gravity * t / float_2_rsh_00013bcc[0];
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = float_6p2832_rsh_00013b28[0] * angleABf(npc->position.x, npc->position.z, x, z) / float_360_rsh_00013b2c[0];
    npc->position.x = speed * moa_sinx(angle) + npc->position.x;
    npc->position.z = npc->position.z - speed * moa_cosx(angle);
    npc->position.y += vy;
    vy -= gravity;
    t -= float_1_rsh_00013b38[0];
    if (t < zero_rsh_00013b20[0]) {
        npc->position = (Vec){x, y, z};
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return 0;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset


static EVT_BEGIN(evt_moamoa_init)
    CALL(evt_npc_entry, STRING(((char*)str_00003D00)), STRING(((char*)str_00003BB8)))
    CALL(evt_npc_set_position, STRING(((char*)str_00003D00)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)str_00003D08)), STRING(((char*)str_00003BCC)))
    CALL(evt_npc_set_position, STRING(((char*)str_00003D08)), 0, -1000, 0)
    CALL(evt_ext_entry, 400, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    CALL(evt_moamoa_flag_onoff, 1, 1)
    IF_INT_EQUAL(GSWF(3450), 1)
        CALL(evt_moamoa_target_off, 0)
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
    END_IF
    IF_INT_EQUAL(GSWF(3451), 1)
        CALL(evt_moamoa_target_off, 1)
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_meet_moamoa)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_seq_wait, 2)
    WAIT_MS(1500)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_set_anim, STRING(((char*)str_00003D10)), STRING(((char*)str_00003BE4)))
    CALL(evt_npc_set_anim, STRING(((char*)str_00003D20)), STRING(((char*)str_00003BE4)))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00003D28)), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(((char*)str_00003D44)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, STRING(((char*)str_00003D4C)), 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D54)), 0, 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_zoom_in, 25, 1500, 0, 11)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set_at, -200, 60, -80, 0, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(2000)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_moamoa_ry_reset)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D64)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D7C)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D8C)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003D9C)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DAC)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DBC)), 0, STRING(((char*)str_00003D74)))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003DCC)), 0, STRING(((char*)str_00003D74)))
    END_SWITCH
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    SET_VALUE(GSW(0), 330)
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_help)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 0, LW(0), 512)
        IF_STR_EQUAL(LW(0), STRING(((char*)str_00003D20)))
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DDC)), 0, LW(0))
            ELSE
            CALL(evt_msg_print, 0, STRING(((char*)str_00003DEC)), 0, LW(0))
        END_IF
        CALL(evt_npc_flag_onoff, 1, LW(0), 512)
    END_INLINE_EVENT
    CALL(evt_npc_flag_onoff, 1, LW(0), 32)
    CALL(evt_npc_flag_onoff, 0, LW(0), 1024)
    SET_VALUE(LW(10), LW(0))
    CALL(evt_npc_get_position, LW(0), LW(1), LW(2), LW(3))
    CALL(evt_sub_random, 1000, LW(4))
    IF_INT_LESS(LW(4), 500)
        SET_VALUE(LW(4), 90)
        ELSE
        SET_VALUE(LW(4), 270)
    END_IF
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(30.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(30.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.5f), 400)
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(20.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(20.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.2998047f), 200)
    CALL(evt_sub_get_sincos, LW(4), LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(10.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(10.0f))
    ADD_FLOAT(LW(1), LW(5))
    SUBTRACT_FLOAT(LW(3), LW(6))
    CALL(npc_jump, LW(0), LW(1), LW(2), LW(3), FLOAT(0.0f), FLOAT(0.19921875f), 100)
    CALL(evt_npc_flag_onoff, 1, LW(0), 1024)
    CALL(evt_npc_flag_onoff, 0, LW(0), 32)
    IF_STR_EQUAL(LW(10), STRING(((char*)str_00003D20)))
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)str_00003C00)))
        ELSE
        CALL(evt_npc_set_anim, LW(10), STRING(((char*)str_00003DFC)))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_escape0)
    SET_VALUE(LW(0), STRING(((char*)str_00003D10)))
    SPAWN_EVENT(PTR(evt_moamoa_help))
    SET_VALUE(GSWF(3450), 1)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
    RETURN
EVT_END()

EVT_BEGIN(evt_moamoa_escape1)
    SET_VALUE(LW(0), STRING(((char*)str_00003D20)))
    SPAWN_EVENT(PTR(evt_moamoa_help))
    SET_VALUE(GSWF(3451), 1)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
    RETURN
EVT_END()

static EVT_BEGIN(evt_moamoa_escape)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set_xyz, -200, 0, 0, 0, 3000, 11)
    WAIT_MS(3000)
    CALL(evt_moamoa_end_wait)
    CALL(evt_moamoa_exit)
    CALL(evt_cam3d_evt_xyz_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 1, STRING(((char*)str_00003D10)), 32)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00003D20)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_00003D20)), -80, 22, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)str_00003D20)), 90)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_status_onoff, 1, STRING(((char*)str_00003D10)), 2)
        CALL(evt_npc_move_position, STRING(((char*)str_00003D10)), 0, 15, 1000, 0, 1)
        CALL(evt_npc_set_ry, STRING(((char*)str_00003D10)), 270)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -20, -10, FLOAT(80.0f))
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    IF_INT_LESS(LW(2), -140)
        CALL(evt_mario_mov_pos2, LW(0), -100, FLOAT(80.0f))
    END_IF
    CALL(evt_mario_flag_onoff, 1, 1024)
    CALL(evt_mario_mov_pos2, -45, 5, FLOAT(80.0f))
    CALL(evt_mario_set_dir, 270, 300, 0)
    CALL(evt_mario_flag_onoff, 0, 1024)
    CALL(evt_cam3d_evt_set, -40, 90, 283, -40, 38, -13, 500, 11)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E00)), 0, STRING(((char*)str_00003D20)))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E10)), 0, STRING(((char*)str_00003D10)))
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING(((char*)str_00003E20)), 0, STRING(((char*)str_00003D20)))
    WAIT_MS(500)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_party_run, 0)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003D20)), 32)
    CALL(evt_npc_flag_onoff, 0, STRING(((char*)str_00003D10)), 32)
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
    CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
    SET_VALUE(GSW(0), 331)
    SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
    CALL_CHILD(PTR(bero_case_switch_on))
    RETURN
EVT_END()

static EVT_BEGIN(init_syashou)
    SWITCH(GSW(0))
        CASE_BETWEEN(329, 332)
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), -115, 0, 20)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_00003E38)), STRING(((char*)str_00003C00)), STRING(((char*)str_00003E3C)))
        CALL(evt_npc_set_tribe, STRING(((char*)str_00003E38)), STRING(((char*)str_00003E40)))
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_syashou)
    IF_INT_LESS(GSW(0), 331)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E48)), 0, 0)
        ELSE
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E5C)), 0, 0)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(init_waitless)
    SWITCH(GSW(0))
        CASE_BETWEEN(329, 332)
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 50, 0, 0)
        CALL(evt_npc_set_autotalkpose, STRING(((char*)str_00003E38)), STRING(((char*)str_00003DFC)), STRING(((char*)str_00003E6C)))
        CALL(evt_npc_set_tribe, STRING(((char*)str_00003E38)), STRING(((char*)str_00003E70)))
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING(((char*)str_00003E38)), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(talk_waitless)
    IF_INT_LESS(GSW(0), 331)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E80)), 0, 0)
        ELSE
        CALL(evt_msg_print, 0, STRING(((char*)str_00003E94)), 0, 0)
    END_IF
    RETURN
EVT_END()

static s32 bero_data_a[] = {
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EAC), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_b[] = {
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EE0), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 bero_data_c[] = {
    (s32)((char*)str_00003EA4), 65544, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00003EEC), (s32)((char*)str_00003E30), 65537, (s32)((char*)str_00003EB8), (s32)((char*)str_00003EC8), (s32)((char*)str_00003E30),
    0, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_00003ED4), (s32)((char*)str_00003E30), 65537, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

static s32 npc_data[] = {
    (s32)/*"車掌"*/(char*)str_00003D20, 1536, 0, (s32)init_syashou, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, (s32)/*"ウェイトレス"*/(char*)str_00003D10,
    1536, 0, (s32)init_waitless, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

__declspec(section ".data") EVT_BEGIN(evt_ghost_diary)
    SET_VALUE(GSW(0), 299)
    RETURN
EVT_END()

EVT_BEGIN(evt_ghost_diary_read)
    CALL(evt_msg_print, 0, STRING(((char*)str_00003EF8)), 0, 0)
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F18)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F28)))
    CALL(evt_msg_select, 0, STRING(((char*)str_00003F08)))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING(((char*)str_00003F38)))
    CALL(evt_msg_print, 0, STRING(((char*)str_00003F48)), 0, STRING(((char*)str_00003F58)))
    RETURN
EVT_END()

static s32 access_tbl[] = {
    (s32)((char*)str_00003F64), (s32)((char*)str_00003F70), (s32)((char*)str_00003F80), (s32)((char*)str_00003F70), (s32)((char*)str_00003F8C), (s32)((char*)str_00003F94), (s32)((char*)str_00003FA4), (s32)((char*)str_00003FAC),
    (s32)((char*)str_00003FBC), (s32)((char*)str_00003FC4), (s32)((char*)str_00003FD4), (s32)((char*)str_00003FC4), 0,
};

static EVT_BEGIN(evt_access)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, LW(1), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_access2)
    IF_INT_EQUAL(LSWF(12), 0)
        SET_VALUE(LSWF(12), 1)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003FDC)), 0, 0)
        CALL(evt_item_entry, STRING(((char*)str_00003FEC)), 142, 0, -1000, 0, 17, -1, 0)
        CALL(evt_item_get_item, STRING(((char*)str_00003FEC)))
        CALL(evt_mario_key_onoff, 1)
        ELSE
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING(((char*)str_00003FF0)), 0, 0)
        CALL(evt_mario_key_onoff, 1)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(evt_access_entry)
    SET_INT_READ_ADDR(PTR(access_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, 9, 1, LW(0), 0, PTR(evt_access), 0)
    END_LOOP
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00004000)), 0, PTR(evt_access2), 0)
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_init_evt)
    SWITCH(GSW(0))
        CASE_BETWEEN(310, 325)
        CASE_DEFAULT
        CALL(evt_map_playanim, STRING(((char*)str_00004008)), 1, 0)
    END_SWITCH
    CALL_CHILD(PTR(evt_access_entry))
    SWITCH(GSW(0))
        CASE_BETWEEN(284, 286)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
        CASE_BETWEEN(304, 309)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004010)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
        CASE_BETWEEN(310, 325)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004030)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_BETWEEN(327, 328)
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
        CASE_BETWEEN(329, 331)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004040)))
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
        CASE_BETWEEN(334, 344)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004050)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        CASE_DEFAULT
        CALL(evt_snd_bgmoff, 512)
        CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_a_init_evt)
    SWITCH(GSW(0))
        CASE_LESS(288)
        SET_VALUE(LW(0), PTR(bero_data_a))
        CASE_LESS(294)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CASE_LESS(303)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CASE_LESS(309)
        SET_VALUE(LW(0), PTR(bero_data_a))
        CASE_LESS(326)
        SET_VALUE(LW(0), PTR(bero_data_b))
        CASE_LESS(328)
        SET_VALUE(LW(0), PTR(bero_data_c))
        CASE_DEFAULT
        SET_VALUE(LW(0), PTR(bero_data_a))
    END_SWITCH
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_05_init_evt))
    CALL(evt_npc_setup, PTR(npc_data))
    SWITCH(GSW(0))
        CASE_LESS(329)
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_EQUAL(329)
        CALL_CHILD(PTR(evt_moamoa_init))
        SPAWN_EVENT(PTR(evt_meet_moamoa))
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_EQUAL(330)
        CALL_CHILD(PTR(evt_moamoa_init))
        SET_VALUE(LW(0), STRING(((char*)str_00003E30)))
        CALL_CHILD(PTR(bero_case_switch_off))
        CASE_DEFAULT
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D20)), 6, PTR(talk_syashou))
        CALL(evt_npc_change_interrupt, STRING(((char*)str_00003D10)), 6, PTR(talk_waitless))
    END_SWITCH
    IF_INT_LESS(GSW(0), 299)
        CALL(evt_item_entry, STRING(((char*)str_00004060)), 78, -90, 0, -140, 0, -1, PTR(evt_ghost_diary))
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_init_evt_nidome)
    IF_INT_EQUAL(GSWF(3579), 0)
        IF_INT_EQUAL(GSWF(3580), 0)
            IF_INT_EQUAL(GSWF(3581), 0)
                CALL(evt_map_playanim, STRING(((char*)str_00004008)), 1, 0)
            END_IF
        END_IF
    END_IF
    CALL(evt_npc_setup, PTR(npc_data))
    IF_INT_EQUAL(GSWF(3460), 1)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004050)))
        CALL(evt_snd_envoff, 512)
        CALL(evt_snd_bgmoff, 26624)
        ELSE
        IF_INT_EQUAL(GSWF(3461), 1)
            CALL(evt_snd_bgmon, 512, STRING(((char*)str_00004068)))
            CALL(evt_snd_envoff, 512)
            CALL(evt_snd_bgmoff, 26624)
            ELSE
            CALL(evt_snd_bgmoff, 512)
            CALL(evt_snd_envon, 272, STRING(((char*)str_00004020)))
        END_IF
    END_IF
    RETURN
EVT_END()

EVT_BEGIN(rsh_05_a_init_evt_nidome)
    IF_INT_EQUAL(GSWF(3453), 1)
        SET_VALUE(LW(0), PTR(bero_data_a))
    END_IF
    IF_INT_EQUAL(GSWF(3454), 1)
        SET_VALUE(LW(0), PTR(bero_data_b))
    END_IF
    IF_INT_EQUAL(GSWF(3455), 1)
        SET_VALUE(LW(0), PTR(bero_data_c))
    END_IF
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(rsh_05_init_evt_nidome))
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): moamoa_pose_init (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
void jt_00003A88(void);
void jt_00004508(void);
void jt_00004800(void);
void jt_00004A64(void);
void jt_00004CC0(void);
void jt_00005F44(void);
void jt_000054DC(void);
void jt_00005560(void);
void jt_0000558C(void);
void jt_000058AC(void);
void jt_00004CE4(void);
void jt_00004FE8(void);
void jt_00005048(void);
void jt_00005398(void);
void jt_00005428(void);
void jt_00004270(void);
void jt_0000429C(void);
void jt_00004364(void);
void jt_00005BA0(void);
void jt_00005BC8(void);
void jt_00005E54(void);
void jt_00005E78(void);
__declspec(section ".data") void* jumptable_00014F3C[66] = {jt_00003A88, jt_00004508, jt_00004800, jt_00004A64, jt_00004CC0, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_000054DC, jt_00005560, jt_0000558C, jt_000058AC, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00004CE4, jt_00004CE4, jt_00004CE4, jt_00004FE8, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005048, jt_00005398, jt_00005428, jt_00004270, jt_0000429C, jt_00004364, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005F44, jt_00005BA0, jt_00005BC8, jt_00005E54, jt_00005E78};
#pragma force_active on
__declspec(section ".rodata") const char str_00003BB8[] = "c_n_moa_a\000\000";
__declspec(section ".rodata") const char str_00003BC4[] = "S_1";
__declspec(section ".rodata") const char str_00003BC8[] = "D_1";
__declspec(section ".rodata") const char str_00003BCC[] = "c_n_moa_b\000\000";
__declspec(section ".rodata") const char str_00003BD8[] = "c_kinodebu\000";
__declspec(section ".rodata") const char str_00003BE4[] = "G_1";
__declspec(section ".rodata") const char str_00003BE8[] = "c_puku_c\000\000\000";
__declspec(section ".rodata") const char str_00003BF4[] = "U_1";
__declspec(section ".rodata") const char str_00003BF8[] = "c_powan";
__declspec(section ".rodata") const char str_00003C00[] = "O_1";
__declspec(section ".rodata") const char str_00003C04[] = "c_smoko";
__declspec(section ".rodata") const char str_00003C0C[] = "T_2";
__declspec(section ".rodata") const char str_00003C10[] = "c_rose\000";
__declspec(section ".rodata") const char str_00003C18[] = "c_papab";
__declspec(section ".rodata") const char str_00003C20[] = "c_mamab";
__declspec(section ".rodata") const char str_00003C28[] = "c_konari\000\000\000";
__declspec(section ".rodata") const f32 vec3_rsh_000136d4[3] = { -290.0f, 65.0f, -95.0f };
__declspec(section ".rodata") const f32 vec3_rsh_000136e0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_000136ec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_000136f8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013704[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013710[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_0001371c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013728[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013734[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013740[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_0001374c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013758[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013764[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013770[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_0001377c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013788[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_rsh_00013794[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00003D00[] = "moa_a\000\000";
__declspec(section ".rodata") const char str_00003D08[] = "moa_b\000\000";
__declspec(section ".rodata") const char str_00003D10[] = "\203E\203F\203C\203g\203\214\203X\000\000\000";
__declspec(section ".rodata") const char str_00003D20[] = "\216\324\217\266\000\000\000";
__declspec(section ".rodata") const char str_00003D28[] = "SFX_VOICE_MARIO_SURPRISED2\000";
__declspec(section ".rodata") const char str_00003D44[] = "eff0\000\000\000";
__declspec(section ".rodata") const char str_00003D4C[] = "eff1\000\000\000";
__declspec(section ".rodata") const char str_00003D54[] = "stg6_rsh_237\000\000\000";
__declspec(section ".rodata") const char str_00003D64[] = "stg6_rsh_238_0\000";
__declspec(section ".rodata") const char str_00003D74[] = "party\000\000";
__declspec(section ".rodata") const char str_00003D7C[] = "stg6_rsh_238_1\000";
__declspec(section ".rodata") const char str_00003D8C[] = "stg6_rsh_238_2\000";
__declspec(section ".rodata") const char str_00003D9C[] = "stg6_rsh_238_3\000";
__declspec(section ".rodata") const char str_00003DAC[] = "stg6_rsh_238_4\000";
__declspec(section ".rodata") const char str_00003DBC[] = "stg6_rsh_238_5\000";
__declspec(section ".rodata") const char str_00003DCC[] = "stg6_rsh_238_6\000";
__declspec(section ".rodata") const char str_00003DDC[] = "stg6_rsh_249_00";
__declspec(section ".rodata") const char str_00003DEC[] = "stg6_rsh_249_01";
__declspec(section ".rodata") const char str_00003DFC[] = "P_1";
__declspec(section ".rodata") const char str_00003E00[] = "stg6_rsh_240_00";
__declspec(section ".rodata") const char str_00003E10[] = "stg6_rsh_241\000\000\000";
__declspec(section ".rodata") const char str_00003E20[] = "stg6_rsh_240_01";
__declspec(section ".rodata") const char str_00003E30[] = "w_bero\000";
__declspec(section ".rodata") const char str_00003E38[] = "me\000";
__declspec(section ".rodata") const char str_00003E3C[] = "T_3";
__declspec(section ".rodata") const char str_00003E40[] = "\216\324\217\266\224\337\000";
__declspec(section ".rodata") const char str_00003E48[] = "stg6_rsh_249_01_01\000";
__declspec(section ".rodata") const char str_00003E5C[] = "stg6_rsh_242\000\000\000";
__declspec(section ".rodata") const char str_00003E6C[] = "T_5";
__declspec(section ".rodata") const char str_00003E70[] = "\203E\203F\203C\203g\203\214\203X\224\337\000";
__declspec(section ".rodata") const char str_00003E80[] = "stg6_rsh_249_01_02\000";
__declspec(section ".rodata") const char str_00003E94[] = "stg6_rsh_243\000\000\000";
__declspec(section ".rodata") const char str_00003EA4[] = "e_bero\000";
__declspec(section ".rodata") const char str_00003EAC[] = "rsh_04_a\000\000\000";
__declspec(section ".rodata") const char str_00003EB8[] = "e_door_close\000\000\000";
__declspec(section ".rodata") const char str_00003EC8[] = "e_door_open";
__declspec(section ".rodata") const char str_00003ED4[] = "rsh_06_a\000\000\000";
__declspec(section ".rodata") const char str_00003EE0[] = "rsh_04_b\000\000\000";
__declspec(section ".rodata") const char str_00003EEC[] = "rsh_04_c\000\000\000";
__declspec(section ".rodata") const char str_00003EF8[] = "stg6_rsh_130\000\000\000";
__declspec(section ".rodata") const char str_00003F08[] = "stg6_rsh_130_yn";
__declspec(section ".rodata") const char str_00003F18[] = "stg6_rsh_131\000\000\000";
__declspec(section ".rodata") const char str_00003F28[] = "stg6_rsh_132\000\000\000";
__declspec(section ".rodata") const char str_00003F38[] = "stg6_rsh_133\000\000\000";
__declspec(section ".rodata") const char str_00003F48[] = "stg6_rsh_134\000\000\000";
__declspec(section ".rodata") const char str_00003F58[] = "\202\344\202\244\202\352\202\242\000\000\000";
__declspec(section ".rodata") const char str_00003F64[] = "kihako_1\000\000\000";
__declspec(section ".rodata") const char str_00003F70[] = "stg6_rsh_275\000\000\000";
__declspec(section ".rodata") const char str_00003F80[] = "kibako_2\000\000\000";
__declspec(section ".rodata") const char str_00003F8C[] = "bin_1\000\000";
__declspec(section ".rodata") const char str_00003F94[] = "stg6_rsh_276\000\000\000";
__declspec(section ".rodata") const char str_00003FA4[] = "wagon\000\000";
__declspec(section ".rodata") const char str_00003FAC[] = "stg6_rsh_280\000\000\000";
__declspec(section ".rodata") const char str_00003FBC[] = "hako_1\000";
__declspec(section ".rodata") const char str_00003FC4[] = "stg6_rsh_281\000\000\000";
__declspec(section ".rodata") const char str_00003FD4[] = "hako_2\000";
__declspec(section ".rodata") const char str_00003FDC[] = "stg6_rsh_277\000\000\000";
__declspec(section ".rodata") const char str_00003FEC[] = "a\000\000";
__declspec(section ".rodata") const char str_00003FF0[] = "stg6_rsh_279\000\000\000";
__declspec(section ".rodata") const char str_00004000[] = "bin_2\000\000";
__declspec(section ".rodata") const char str_00004008[] = "yure\000\000\000";
__declspec(section ".rodata") const char str_00004010[] = "BGM_EVT_POWAN1\000";
__declspec(section ".rodata") const char str_00004020[] = "ENV_STG6_RSH1_3";
__declspec(section ".rodata") const char str_00004030[] = "BGM_STG6_HOM1\000\000";
__declspec(section ".rodata") const char str_00004040[] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char str_00004050[] = "BGM_STG6_PIK1\000\000";
__declspec(section ".rodata") const char str_00004060[] = "diary\000\000";
__declspec(section ".rodata") const char str_00004068[] = "BGM_STG0_GOR1\000\000";
__declspec(section ".rodata") const f32 float_60_rsh_00013b18[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_1000_rsh_00013b1c[1] = { 1000.0f };
__declspec(section ".rodata") const f32 zero_rsh_00013b20[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_0p5_rsh_00013b24[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_6p2832_rsh_00013b28[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_360_rsh_00013b2c[1] = { 360.0f };
__declspec(section ".rodata") const f32 float_0p00761_rsh_00013b30[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_rsh_00013b34[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_1_rsh_00013b38[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_3p1416_rsh_00013b3c[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_rsh_00013b40[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_rsh_00013b44[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_0p03705_rsh_00013b48[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_rsh_00013b4c[1] = { 0.4967f };
__declspec(section ".rodata") const f64 double_to_int_rsh_00013b50 = 4503601774854144;
__declspec(section ".rodata") const f32 float_neg5000_rsh_00013b58[1] = { -5000.0f };
__declspec(section ".rodata") const f32 float_neg1_rsh_00013b5c[1] = { -1.0f };
__declspec(section ".rodata") const char str_000040C0[] = "SFX_STG6_MOAMOA_VOICE1\000";
__declspec(section ".rodata") const f32 float_200_rsh_00013b78[1] = { 200.0f };
__declspec(section ".rodata") const f32 float_32767_rsh_00013b7c[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_0p1_rsh_00013b80[1] = { 0.1f };
__declspec(section ".rodata") const f32 float_0p03_rsh_00013b84[1] = { 0.03f };
__declspec(section ".rodata") const f32 float_50_rsh_00013b88[1] = { 50.0f };
__declspec(section ".rodata") const f32 float_15_rsh_00013b8c[1] = { 15.0f };
__declspec(section ".rodata") const f32 float_1p5_rsh_00013b90[1] = { 1.5f };
__declspec(section ".rodata") const f32 float_0p8_rsh_00013b94[1] = { 0.8f };
__declspec(section ".rodata") const f32 float_1p2_rsh_00013b98[1] = { 1.2f };
__declspec(section ".rodata") const f32 float_5_rsh_00013b9c[1] = { 5.0f };
__declspec(section ".rodata") const f32 float_0p3_rsh_00013ba0[1] = { 0.3f };
__declspec(section ".rodata") const f32 float_0p2_rsh_00013ba4[1] = { 0.19999999f };
__declspec(section ".rodata") const f32 float_300_rsh_00013ba8[1] = { 300.0f };
__declspec(section ".rodata") const f32 float_600_rsh_00013bac[1] = { 600.0f };
__declspec(section ".rodata") const f32 float_0p25_rsh_00013bb0[1] = { 0.25f };
__declspec(section ".rodata") const f32 float_neg45_rsh_00013bb4[1] = { -45.0f };
__declspec(section ".rodata") const f32 float_90_rsh_00013bb8[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_0p4_rsh_00013bbc[1] = { 0.4f };
__declspec(section ".rodata") const f32 float_100_rsh_00013bc0[1] = { 100.0f };
__declspec(section ".rodata") const f32 float_180_rsh_00013bc4[1] = { 180.0f };
__declspec(section ".rodata") const f32 float_30_rsh_00013bc8[1] = { 30.0f };
__declspec(section ".rodata") const f32 float_2_rsh_00013bcc[1] = { 2.0f };
__declspec(section ".rodata") const f32 float_0p9_rsh_00013bd0[1] = { 0.9f };
__declspec(section ".rodata") const f32 float_135_rsh_00013bd4[1] = { 135.0f };
__declspec(section ".rodata") const f32 float_0p2_rsh_00013bd8[1] = { 0.2f };
__declspec(section ".rodata") const f32 float_0p1_rsh_00013bdc[1] = { 0.10000001f };
__declspec(section ".rodata") const f32 float_neg100_rsh_00013be0[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_0p20944_rsh_00013be4[1] = { 0.20943952f };
__declspec(section ".rodata") const f32 float_neg275_rsh_00013be8[1] = { -275.0f };
__declspec(section ".rodata") const f32 float_6_rsh_00013bec[1] = { 6.0f };
__declspec(section ".rodata") const f32 float_3_rsh_00013bf0[1] = { 3.0f };
__declspec(section ".rodata") const f32 float_neg350_rsh_00013bf4[1] = { -350.0f };
__declspec(section ".rodata") const f32 float_225_rsh_00013bf8[1] = { 225.0f };
__declspec(section ".rodata") const f32 float_1p1_rsh_00013bfc[1] = { 1.1f };
__declspec(section ".rodata") const f32 float_1p02_rsh_00013c00[1] = { 1.02f };
__declspec(section ".rodata") const f32 float_neg1000_rsh_00013c04[1] = { -1000.0f };
__declspec(section ".rodata") const f32 float_290_rsh_00013c08[1] = { 290.0f };
__declspec(section ".rodata") const f32 float_neg290_rsh_00013c0c[1] = { -290.0f };
__declspec(section ".rodata") const f32 float_neg130_rsh_00013c10[1] = { -130.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_rsh_00013c18 = 4503599627370496;
__declspec(section ".rodata") const f32 float_20_rsh_00013c20[1] = { 20.0f };
__declspec(section ".rodata") const f32 float_10_rsh_00013c24[1] = { 10.0f };
__declspec(section ".rodata") const f32 float_35_rsh_00013c28[1] = { 35.0f };
__declspec(section ".rodata") const f32 float_65_rsh_00013c2c[1] = { 65.0f };
__declspec(section ".rodata") const f32 float_40_rsh_00013c30[1] = { 40.0f };
__declspec(section ".rodata") const f32 float_1E06_rsh_00013c34[1] = { 1000000.0f };
__declspec(section ".rodata") const f64 double_30_rsh_00013c38 = 30;
__declspec(section ".rodata") const char str_000041A0[] = "offscreen\000\000";
__declspec(section ".rodata") const char str_000041AC[] = "S_2";
__declspec(section ".rodata") const char str_000041B0[] = "D\000\000";
__declspec(section ".rodata") const char str_000041B4[] = "R\000\000";
__declspec(section ".rodata") const f32 float_530_rsh_00013c58[1] = { 530.0f };
__declspec(section ".rodata") const char str_000041BC[] = "ressha\000";
__declspec(section ".rodata") const char zero_rsh_00013c64[4] = {0};
__declspec(section ".rodata") const char str_000041C8[] = "J\000\000";
__declspec(section ".rodata") const u32 gap_03_000041CC_rodata[1] = { 0x00000000 };
#pragma force_active reset
static s32 npc_jump(EventEntry* event, BOOL isFirstCall);
static void ext_moamoa_dispent(void);
static void ext_moamoa_main(void);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_moamoa_init(void);
static f32 randf(f32 min, f32 max);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void moamoa_pose_main(void);
static void moamoa_pose_init(void);

void GXClearBoundingBox(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void GXSetNumIndStages(u8 nIndStages);
void GXSetTevDirect(GXTevStageID tev_stage);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
f32 PSVECDistance(const Vec* a, const Vec* b);
f32 PSVECMag(const Vec* v);
void PSVECNormalize(const Vec* src, Vec* dst);
void __cvt_ull_flt();
void __div2u();
void* _mapAlloc(u32 size);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
CameraEntry* camGetPtr(CameraId cameraId);
f32 cloudGetBreathDir(void);
f32 compAngle(f32 angle1, f32 angle2);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
f32 evtGetFloat(EventEntry* entry, s32 index);
s32 evtGetValue(EventEntry* entry, s32 index);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
s32 irand(s32 scalar);
MapObject* mapGetMapObj(const char* name);
void marioChgMot(MarioMotion);
s32 marioCtrlOffChk(void);
MarioWork* marioGetPtr(void);
s32 marioKeyOffChk(void);
void *memset(void *dest, int ch, size_t count);
NpcEntry* npcNameToPtr(const char* name);
void offscreenAddBoundingBox(s32 id, u16 left, u16 top, u16 right, u16 bottom);
s32 offscreenNameToId(const char* name);
PartyEntry* partyGetPtr(s32 index);
s32 psndSFXOn_3D(const char* name, Vec* position);
f32 reviseAngle(f32 angle);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
int strncmp(const char *s1, const char *s2, size_t n);
void sysWaitDrawSync(void);
asm static s32 npc_jump(EventEntry* event, BOOL isFirstCall) {
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
	stmw r28, 0x40(r1)
	mr r30, r3
	mr r28, r4
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r29, r3
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0xc(r31)
	mr r3, r30
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x10(r31)
	mr r3, r30
	bl evtGetFloat
	stfs f1, 0x10(r1)
	mr r3, r30
	lwz r4, 0x14(r31)
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x18(r31)
	mr r3, r30
	bl evtGetValue
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0x3c(r1)
	addi r3, r4, double_to_int_rsh_00013b50@l
	lis r4, float_60_rsh_00013b18@ha
	stw r0, 0x38(r1)
	addi r5, r4, float_60_rsh_00013b18@l
	lfd f1, 0x0(r3)
	lis r3, float_1000_rsh_00013b1c@ha
	lfd f0, 0x38(r1)
	addi r4, r3, float_1000_rsh_00013b1c@l
	lfs f2, 0x0(r5)
	mr r3, r29
	fsubs f1, f0, f1
	lfs f0, 0x0(r4)
	fmuls f1, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0xc(r1)
	bl npcNameToPtr
	cmpwi r28, 0x0
	mr r31, r3
	beq @1
	lis r3, vec3_rsh_00013788@ha
	lis r4, vec3_rsh_0001377c@ha
	addi r7, r3, vec3_rsh_00013788@l
	addi r3, r1, 0x2c
	lwz r6, 0x0(r7)
	addi r5, r4, vec3_rsh_0001377c@l
	lwz r0, 0x4(r7)
	addi r4, r1, 0x20
	lwz r7, 0x8(r7)
	stw r6, 0x20(r1)
	lwz r6, 0x0(r5)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r5)
	stw r7, 0x28(r1)
	lwz r5, 0x4(r5)
	lfs f0, 0x8c(r31)
	stfs f0, 0x20(r1)
	lfs f0, 0x94(r31)
	stw r6, 0x2c(r1)
	stw r0, 0x34(r1)
	stfs f0, 0x28(r1)
	stw r5, 0x30(r1)
	stfs f29, 0x2c(r1)
	stfs f28, 0x34(r1)
	bl PSVECDistance
	lis r3, zero_rsh_00013b20@ha
	lfs f2, 0x90(r31)
	lfs f3, 0xc(r1)
	lfs f0, zero_rsh_00013b20@l(r3)
	fsubs f4, f30, f2
	fcmpu cr0, f0, f3
	mfcr r0
	extrwi. r0, r0, 1, 2
	beq @2
	lfs f0, 0x10(r1)
	fdivs f0, f1, f0
	stfs f0, 0xc(r1)
	@2:
	cmpwi r0, 0x0
	bne @3
	fdivs f0, f1, f3
	stfs f0, 0x10(r1)
	@3:
	lfs f2, 0xc(r1)
	lis r3, float_0p5_rsh_00013b24@ha
	lwz r0, 0xc(r1)
	fdivs f0, f4, f2
	lfs f1, float_0p5_rsh_00013b24@l(r3)
	stw r0, 0x78(r30)
	lwz r0, 0x10(r1)
	fmuls f2, f31, f2
	fmadds f0, f2, f1, f0
	stfs f0, 0x8(r1)
	lwz r3, 0x8(r1)
	stw r3, 0x7c(r30)
	stw r0, 0x80(r30)
	@1:
	lfs f1, 0x78(r30)
	fmr f3, f29
	lfs f2, 0x7c(r30)
	fmr f4, f28
	lfs f0, 0x80(r30)
	stfs f1, 0xc(r1)
	lfs f1, 0x8c(r31)
	stfs f2, 0x8(r1)
	lfs f2, 0x94(r31)
	stfs f0, 0x10(r1)
	bl angleABf
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @4
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @5
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @6
	@5:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @6
	@4:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @7
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @6
	@7:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@6:
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f2, 0x10(r1)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0x8c(r31)
	lis r5, float_0p03705_rsh_00013b48@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_rsh_00013b38@ha
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	stfs f0, 0x8c(r31)
	cror eq, lt, eq
	bne @8
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @9
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @10
	@9:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @10
	@8:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @11
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @10
	@11:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@10:
	lfs f1, 0x10(r1)
	lis r3, float_1_rsh_00013b38@ha
	lfs f0, 0x94(r31)
	addi r4, r3, float_1_rsh_00013b38@l
	lfs f3, 0x8(r1)
	lis r3, zero_rsh_00013b20@ha
	fnmsubs f4, f1, f4, f0
	lfs f1, 0xc(r1)
	fsubs f2, f3, f31
	lfs f0, 0x0(r4)
	stfs f4, 0x94(r31)
	fsubs f1, f1, f0
	lfs f0, zero_rsh_00013b20@l(r3)
	lfs f4, 0x90(r31)
	stfs f2, 0x8(r1)
	fcmpo cr0, f1, f0
	fadds f2, f4, f3
	stfs f1, 0xc(r1)
	stfs f2, 0x90(r31)
	bge @12
	lis r4, vec3_rsh_00013794@ha
	li r3, 0x1
	addi r5, r4, vec3_rsh_00013794@l
	lwz r0, 0x0(r5)
	lwz r4, 0x4(r5)
	stw r0, 0x14(r1)
	lwz r0, 0x8(r5)
	stw r4, 0x18(r1)
	stfs f29, 0x14(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f30, 0x18(r1)
	stfs f28, 0x1c(r1)
	lwz r4, 0x18(r1)
	stw r0, 0x8c(r31)
	lwz r0, 0x1c(r1)
	stw r4, 0x90(r31)
	stw r0, 0x94(r31)
	b @13
	@12:
	lwz r4, 0xc(r1)
	li r3, 0x0
	lwz r0, 0x8(r1)
	stw r4, 0x78(r30)
	stw r0, 0x7c(r30)
	@13:
	psq_l f31, 0x88(r1), 0, 0
	lfd f31, 0x80(r1)
	psq_l f30, 0x78(r1), 0, 0
	lfd f30, 0x70(r1)
	psq_l f29, 0x68(r1), 0, 0
	lfd f29, 0x60(r1)
	psq_l f28, 0x58(r1), 0, 0
	lfd f28, 0x50(r1)
	lmw r28, 0x40(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm static void ext_moamoa_dispent(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, wp@ha
	stw r0, 0x14(r1)
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @1
	lis r3, zero_rsh_00013b20@ha
	lis r4, ext_disp@ha
	addi r6, r3, zero_rsh_00013b20@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, zero_rsh_00013b20@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, zero_rsh_00013b20@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_shadow_disp@l
	li r3, 0x4
	li r4, 0x2
	li r6, 0x0
	bl dispEntry
	@1:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @2
	lis r3, float_neg5000_rsh_00013b58@ha
	lis r4, ext_disp@ha
	addi r6, r3, float_neg5000_rsh_00013b58@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x1
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, float_neg5000_rsh_00013b58@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, float_neg5000_rsh_00013b58@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_shadow_disp@l
	li r3, 0x1
	li r4, 0x2
	li r6, 0x0
	bl dispEntry
	@2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static void ext_moamoa_main(void) {
	nofralloc
	stwu r1, -0x130(r1)
	mflr r0
	stw r0, 0x134(r1)
	stfd f31, 0x120(r1)
	psq_st f31, 0x128(r1), 0, 0
	stfd f30, 0x110(r1)
	psq_st f30, 0x118(r1), 0, 0
	stfd f29, 0x100(r1)
	psq_st f29, 0x108(r1), 0, 0
	stfd f28, 0xf0(r1)
	psq_st f28, 0xf8(r1), 0, 0
	stfd f27, 0xe0(r1)
	psq_st f27, 0xe8(r1), 0, 0
	stmw r22, 0xb8(r1)
	bl marioGetPtr
	mr r30, r3
	li r3, 0x0
	bl partyGetPtr
	mr r23, r3
	li r3, 0x4
	bl camGetPtr
	lhz r0, 0x2e(r30)
	li r25, 0x0
	cmplwi r0, 0x12
	bne @1
	lis r3, wp@ha
	lwz r4, wp@l(r3)
	lha r3, 0x40(r4)
	addi r0, r3, 0x1
	sth r0, 0x40(r4)
	b @2
	@1:
	lis r3, wp@ha
	li r0, 0x0
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	sth r0, 0x40(r3)
	@2:
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x0
	bne @3
	lis r3, wp@ha
	addi r5, r3, wp@l
	lwz r4, 0x0(r5)
	lha r3, 0x42(r4)
	addi r0, r3, 0x1
	sth r0, 0x42(r4)
	lwz r3, 0x0(r5)
	lha r0, 0x42(r3)
	cmpwi r0, 0x3e8
	ble @4
	li r0, 0x3e8
	sth r0, 0x42(r3)
	b @4
	@3:
	lis r3, wp@ha
	li r0, 0x0
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	sth r0, 0x42(r3)
	@4:
	lwz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 23, 23
	beq @5
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x10
	sth r0, 0x0(r3)
	b @6
	@5:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r3)
	@6:
	lis r4, float_neg1_rsh_00013b5c@ha
	lis r3, wp@ha
	addi r5, r4, float_neg1_rsh_00013b5c@l
	addi r4, r3, wp@l
	lfs f0, 0x0(r5)
	lwz r3, 0x0(r4)
	stfs f0, 0x55c(r3)
	lwz r3, 0x0(r4)
	stfs f0, 0x560(r3)
	lbz r0, 0x31(r23)
	cmpwi r0, 0x5
	bne @7
	lwz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 23, 23
	beq @7
	bl cloudGetBreathDir
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	stfs f1, 0x55c(r3)
	bl cloudGetBreathDist
	lis r3, wp@ha
	lis r4, float_6p2832_rsh_00013b28@ha
	addi r10, r3, wp@l
	lis r7, float_0p00761_rsh_00013b30@ha
	lwz r5, 0x0(r10)
	lis r3, float_360_rsh_00013b2c@ha
	addi r8, r3, float_360_rsh_00013b2c@l
	addi r9, r4, float_6p2832_rsh_00013b28@l
	stfs f1, 0x560(r5)
	lis r3, float_3p1416_rsh_00013b3c@ha
	addi r4, r3, float_3p1416_rsh_00013b3c@l
	lis r6, float_0p16605_rsh_00013b34@ha
	lwz r3, 0x0(r10)
	lis r5, float_1_rsh_00013b38@ha
	lfs f2, 0x0(r9)
	lfs f1, 0x55c(r3)
	lfs f0, 0x0(r8)
	fmuls f2, f2, f1
	lfs f1, 0x0(r4)
	lfs f4, float_0p00761_rsh_00013b30@l(r7)
	lfs f3, float_0p16605_rsh_00013b34@l(r6)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r5)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @8
	lis r4, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @9
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @10
	@9:
	fsubs f0, f5, f1
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @10
	@8:
	lis r4, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r4)
	fcmpo cr0, f5, f0
	bge @11
	fsubs f5, f5, f1
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	b @10
	@11:
	lis r4, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	@10:
	lfs f1, 0x560(r3)
	lis r9, wp@ha
	lfs f0, 0x58(r23)
	lis r4, float_6p2832_rsh_00013b28@ha
	addi r8, r4, float_6p2832_rsh_00013b28@l
	lis r6, float_0p03705_rsh_00013b48@ha
	fmadds f0, f1, f4, f0
	lis r4, float_360_rsh_00013b2c@ha
	addi r7, r4, float_360_rsh_00013b2c@l
	lis r5, float_0p4967_rsh_00013b4c@ha
	lis r4, float_3p1416_rsh_00013b3c@ha
	addi r10, r9, wp@l
	stfs f0, 0x564(r3)
	lis r3, float_1_rsh_00013b38@ha
	lfs f3, 0x0(r8)
	lfs f0, 0x5c(r23)
	lwz r9, 0x0(r10)
	lfs f1, float_3p1416_rsh_00013b3c@l(r4)
	stfs f0, 0x568(r9)
	lfs f0, 0x0(r7)
	lwz r7, 0x0(r10)
	lfs f5, float_0p03705_rsh_00013b48@l(r6)
	lfs f2, 0x55c(r7)
	lfs f4, float_0p4967_rsh_00013b4c@l(r5)
	fmuls f2, f3, f2
	lfs f3, float_1_rsh_00013b38@l(r3)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @13
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	b @14
	@13:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @14
	@12:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f2, f0
	bge @15
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@14:
	lfs f1, 0x560(r7)
	lfs f0, 0x60(r23)
	fnmsubs f0, f1, f5, f0
	stfs f0, 0x56c(r7)
	@7:
	lis r3, wp@ha
	addi r4, r3, wp@l
	lwz r5, 0x0(r4)
	lha r0, 0x3a(r5)
	cmpwi r0, 0x32
	ble @16
	lwz r3, 0x20(r5)
	lwz r0, 0x24(r5)
	stw r3, 0x14(r5)
	stw r0, 0x18(r5)
	lwz r0, 0x28(r5)
	stw r0, 0x1c(r5)
	lwz r4, 0x0(r4)
	lhz r3, 0x0(r4)
	rlwinm. r0, r3, 0, 19, 19
	bne @16
	ori r0, r3, 0x1000
	lis r3, evt_moamoa_escape0@ha
	sth r0, 0x0(r4)
	addi r3, r3, evt_moamoa_escape0@l
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	@16:
	lis r3, wp@ha
	addi r4, r3, wp@l
	lwz r5, 0x0(r4)
	lha r0, 0x3c(r5)
	cmpwi r0, 0x32
	ble @17
	lwz r3, 0x14(r5)
	lwz r0, 0x18(r5)
	stw r3, 0x20(r5)
	stw r0, 0x24(r5)
	lwz r0, 0x1c(r5)
	stw r0, 0x28(r5)
	lwz r4, 0x0(r4)
	lhz r3, 0x0(r4)
	rlwinm. r0, r3, 0, 18, 18
	bne @17
	ori r0, r3, 0x2000
	lis r3, evt_moamoa_escape1@ha
	sth r0, 0x0(r4)
	addi r3, r3, evt_moamoa_escape1@l
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	@17:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lhz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 19, 19
	beq @18
	rlwinm. r0, r3, 0, 18, 18
	beq @18
	bl extGetPosePtr
	lis r3, wp@ha
	li r8, 0x0
	addi r6, r3, wp@l
	li r4, 0x19
	lwz r5, 0x0(r6)
	li r3, 0x0
	lwz r9, 0x8(r5)
	b @19
	@20:
	lhz r5, 0x0(r9)
	rlwinm. r0, r5, 0, 29, 29
	bne @21
	rlwinm. r0, r5, 0, 27, 27
	bne @22
	sth r4, 0x2(r9)
	sth r3, 0x4(r9)
	lhz r0, 0x0(r9)
	ori r0, r0, 0x10
	sth r0, 0x0(r9)
	@21:
	addi r8, r8, 0x1
	addi r9, r9, 0x50
	@19:
	lwz r7, 0x0(r6)
	lwz r0, 0x4(r7)
	cmpw r8, r0
	blt @20
	@22:
	lwz r0, 0x44(r7)
	cmplwi r0, 0x0
	bne @18
	lis r3, evt_moamoa_escape@ha
	li r4, 0x0
	addi r3, r3, evt_moamoa_escape@l
	li r5, 0x0
	bl evtEntry
	lis r4, wp@ha
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	stw r3, 0x44(r4)
	@18:
	bl extGetPosePtr
	lis r5, wp@ha
	lis r4, str_000040C0@ha
	addi r31, r5, wp@l
	mr r28, r3
	lwz r5, 0x0(r31)
	addi r29, r4, str_000040C0@l
	li r24, 0x0
	li r26, 0x0
	lwz r27, 0x8(r5)
	b @23
	@24:
	lwz r3, 0xc(r28)
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	lwz r3, 0x0(r31)
	stfs f1, 0x550(r3)
	lwz r3, 0xc(r28)
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl distABf
	lwz r3, 0x0(r31)
	stfs f1, 0x554(r3)
	lwz r3, 0x0(r31)
	lhz r3, 0x0(r3)
	clrlwi. r0, r3, 31
	beq @25
	rlwinm. r0, r3, 0, 29, 29
	bne @25
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @25
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	bne @25
	cmpwi r25, 0x0
	bne @25
	lhz r0, 0x0(r27)
	andi. r0, r0, 0x154
	bne @25
	mr r3, r28
	mr r4, r27
	bl moamoa_hit_check
	mr r23, r3
	cmpwi r23, 0x1
	bne @26
	li r3, 0x3
	lhz r5, 0x0(r27)
	divw r0, r26, r3
	li r6, 0x24
	ori r5, r5, 0x4
	sth r5, 0x0(r27)
	lis r4, wp@ha
	sth r6, 0x2(r27)
	addi r5, r4, wp@l
	mullw r0, r0, r3
	lwz r4, 0x0(r5)
	lha r3, 0x38(r4)
	subf r23, r0, r26
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	mulli r0, r23, 0xc
	lwz r4, 0xc(r28)
	lwz r3, 0x0(r5)
	lfs f1, 0xc(r4)
	add r3, r3, r0
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, float_200_rsh_00013b78@ha
	lfs f0, float_200_rsh_00013b78@l(r3)
	fcmpo cr0, f1, f0
	bge @27
	lis r4, wp@ha
	slwi r3, r23, 1
	lwz r5, wp@l(r4)
	addi r4, r3, 0x3a
	lhax r3, r5, r4
	addi r0, r3, 0x1
	sthx r0, r5, r4
	@27:
	lis r3, str_00003BB8@ha
	lis r5, str_00003BC8@ha
	addi r4, r3, str_00003BB8@l
	mr r3, r27
	addi r5, r5, str_00003BC8@l
	bl moamoa_pose_change
	li r25, 0x1
	b @25
	@26:
	cmpwi r23, 0x2
	beq @28
	cmpwi r23, 0x4
	bne @29
	@28:
	li r3, 0x3
	lhz r5, 0x0(r27)
	divw r0, r26, r3
	li r6, 0x2f
	ori r5, r5, 0xc
	sth r5, 0x0(r27)
	lis r4, wp@ha
	sth r6, 0x2(r27)
	addi r5, r4, wp@l
	mullw r0, r0, r3
	lwz r4, 0x0(r5)
	lha r3, 0x38(r4)
	subf r22, r0, r26
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	mulli r0, r22, 0xc
	lwz r4, 0xc(r28)
	lwz r3, 0x0(r5)
	lfs f1, 0xc(r4)
	add r3, r3, r0
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, float_200_rsh_00013b78@ha
	lfs f0, float_200_rsh_00013b78@l(r3)
	fcmpo cr0, f1, f0
	bge @30
	lis r4, wp@ha
	slwi r3, r22, 1
	lwz r5, wp@l(r4)
	addi r4, r3, 0x3a
	lhax r3, r5, r4
	addi r0, r3, 0x1
	sthx r0, r5, r4
	@30:
	lis r3, str_00003BB8@ha
	lis r5, str_00003BC8@ha
	addi r4, r3, str_00003BB8@l
	mr r3, r27
	addi r5, r5, str_00003BC8@l
	bl moamoa_pose_change
	cmpwi r23, 0x4
	beq @25
	li r25, 0x1
	b @25
	@29:
	cmpwi r23, 0x3
	bne @25
	lis r3, wp@ha
	lhz r0, 0x0(r27)
	addi r4, r3, wp@l
	lwz r7, 0x0(r4)
	ori r5, r0, 0x84
	lis r4, float_0p5_rsh_00013b24@ha
	li r0, 0x30
	lfs f2, 0x55c(r7)
	addi r6, r4, float_0p5_rsh_00013b24@l
	lfs f1, 0x550(r7)
	lis r3, vec3_rsh_00013740@ha
	addi r4, r3, vec3_rsh_00013740@l
	lfs f0, 0x0(r6)
	sth r5, 0x0(r27)
	fadds f1, f2, f1
	sth r0, 0x2(r27)
	fmuls f27, f1, f0
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x8(r27)
	stw r0, 0xc(r27)
	lwz r0, 0x8(r4)
	stw r0, 0x10(r27)
	bl rand
	xoris r4, r3, 0x8000
	lis r0, 0x4330
	lis r3, float_6p2832_rsh_00013b28@ha
	stw r4, 0xac(r1)
	lfs f0, float_6p2832_rsh_00013b28@l(r3)
	lis r5, double_to_int_rsh_00013b50@ha
	stw r0, 0xa8(r1)
	lis r3, float_360_rsh_00013b2c@ha
	lfd f3, double_to_int_rsh_00013b50@l(r5)
	fmuls f1, f0, f27
	lfs f0, float_360_rsh_00013b2c@l(r3)
	lis r4, float_32767_rsh_00013b7c@ha
	lfd f2, 0xa8(r1)
	lis r5, float_0p00761_rsh_00013b30@ha
	fdivs f30, f1, f0
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f5, float_0p00761_rsh_00013b30@l(r5)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r3, float_1_rsh_00013b38@ha
	fsubs f3, f2, f3
	lfs f2, float_32767_rsh_00013b7c@l(r4)
	lis r4, float_0p1_rsh_00013b80@ha
	addi r6, r4, float_0p1_rsh_00013b80@l
	fcmpo cr0, f30, f1
	fdivs f2, f3, f2
	lfs f0, 0x0(r6)
	lis r4, float_0p16605_rsh_00013b34@ha
	lfs f4, float_0p16605_rsh_00013b34@l(r4)
	lfs f3, float_1_rsh_00013b38@l(r3)
	fmadds f31, f2, f0, f0
	cror eq, lt, eq
	bne @31
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @32
	fmuls f0, f30, f30
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f30
	b @33
	@32:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @33
	@31:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f30, f0
	bge @34
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @33
	@34:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@33:
	fmuls f0, f31, f5
	stfs f0, 0x14(r27)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_rsh_00013b50@l
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r4, r3, float_32767_rsh_00013b7c@l
	lfd f2, 0x0(r5)
	lis r3, float_0p03_rsh_00013b84@ha
	lfd f1, 0xa8(r1)
	addi r6, r3, float_0p03_rsh_00013b84@l
	lfs f0, 0x0(r4)
	lis r5, float_0p03705_rsh_00013b48@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lis r3, float_1_rsh_00013b38@ha
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	fmadds f0, f2, f0, f0
	lfs f2, float_1_rsh_00013b38@l(r3)
	fcmpo cr0, f30, f1
	stfs f0, 0x1c(r27)
	cror eq, lt, eq
	bne @35
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @36
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @37
	@36:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @37
	@35:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f30, f0
	bge @38
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @37
	@38:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@37:
	li r3, 0x3
	fneg f0, f4
	divw r0, r26, r3
	lis r4, wp@ha
	li r6, 0x78
	fmuls f0, f31, f0
	addi r5, r4, wp@l
	stfs f0, 0x20(r27)
	sth r6, 0x18(r27)
	mullw r0, r0, r3
	lwz r4, 0x0(r5)
	lha r3, 0x38(r4)
	subf r22, r0, r26
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	mulli r0, r22, 0xc
	lwz r4, 0xc(r28)
	lwz r3, 0x0(r5)
	lfs f1, 0xc(r4)
	add r3, r3, r0
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, float_200_rsh_00013b78@ha
	lfs f0, float_200_rsh_00013b78@l(r3)
	fcmpo cr0, f1, f0
	bge @39
	lis r4, wp@ha
	slwi r3, r22, 1
	lwz r5, wp@l(r4)
	addi r4, r3, 0x3a
	lhax r3, r5, r4
	addi r0, r3, 0x1
	sthx r0, r5, r4
	@39:
	lis r3, str_00003BB8@ha
	lis r5, str_00003BC8@ha
	addi r4, r3, str_00003BB8@l
	mr r3, r27
	addi r5, r5, str_00003BC8@l
	bl moamoa_pose_change
	li r25, 0x1
	@25:
	lwz r4, 0x0(r31)
	lhz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @40
	lhz r5, 0x0(r27)
	andi. r0, r5, 0x155
	bne @40
	lis r3, float_50_rsh_00013b88@ha
	lfs f1, 0x554(r4)
	lfs f0, float_50_rsh_00013b88@l(r3)
	fcmpo cr0, f1, f0
	bge @40
	rlwinm. r0, r5, 0, 30, 30
	beq @41
	li r0, 0x1
	sth r0, 0x24(r27)
	b @40
	@41:
	li r0, 0x1
	sth r0, 0x2(r27)
	@40:
	lwz r3, 0x0(r31)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @42
	lhz r0, 0x0(r27)
	andi. r0, r0, 0x444
	bne @42
	lis r4, gp@ha
	lwz r3, 0x4(r3)
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r4, 0x1c(r4)
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplw r26, r0
	bne @42
	li r3, 0x3e8
	bl irand
	cmpwi r3, 0xc8
	bge @42
	lis r3, vec3_rsh_0001374c@ha
	lwz r5, 0xc(r28)
	addi r8, r3, vec3_rsh_0001374c@l
	mr r3, r29
	lwz r7, 0x0(r8)
	addi r4, r1, 0x38
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
	stw r6, 0x38(r1)
	stw r5, 0x3c(r1)
	stw r0, 0x40(r1)
	bl psndSFXOn_3D
	@42:
	lha r0, 0x2(r27)
	cmplwi r0, 0x41
	bgt @43
	lis r3, jumptable_00014F3C@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_00014F3C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@44:
	entry jt_00003A88
	li r3, 0x85
	divw r0, r26, r3
	mullw r0, r0, r3
	subf r0, r0, r26
	cmpwi r0, 0x64
	bge @45
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, float_6p2832_rsh_00013b28@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_rsh_00013b20@ha
	fsubs f3, f0, f1
	lfs f1, float_6p2832_rsh_00013b28@l(r4)
	lfs f0, zero_rsh_00013b20@l(r3)
	fdivs f2, f3, f2
	fmadds f31, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0xb4(r1)
	addi r5, r4, double_to_int_rsh_00013b50@l
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r4, r3, float_32767_rsh_00013b7c@l
	lfd f2, 0x0(r5)
	lis r5, float_50_rsh_00013b88@ha
	lfd f1, 0xb0(r1)
	addi r7, r5, float_50_rsh_00013b88@l
	lfs f0, 0x0(r4)
	lis r4, zero_rsh_00013b20@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	addi r6, r4, zero_rsh_00013b20@l
	lis r5, float_0p00761_rsh_00013b30@ha
	lis r4, float_0p16605_rsh_00013b34@ha
	fdivs f3, f2, f0
	lfs f2, 0x0(r7)
	lfs f0, 0x0(r6)
	lis r3, float_1_rsh_00013b38@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r5)
	fmadds f7, f3, f2, f0
	fcmpo cr0, f31, f1
	lfs f3, float_0p16605_rsh_00013b34@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @46
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f31, f1
	cror eq, lt, eq
	bne @47
	fmuls f0, f31, f31
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f31
	b @48
	@47:
	fsubs f0, f31, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @48
	@46:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f31, f0
	bge @49
	fsubs f1, f31, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @48
	@49:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f31, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@48:
	li r4, 0x3
	lis r5, wp@ha
	divw r0, r26, r4
	lwz r6, wp@l(r5)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r5, float_0p03705_rsh_00013b48@ha
	lis r3, float_1_rsh_00013b38@ha
	mullw r0, r0, r4
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f5, float_0p4967_rsh_00013b4c@l(r4)
	fcmpo cr0, f31, f1
	lfs f6, float_0p03705_rsh_00013b48@l(r5)
	lfs f2, float_1_rsh_00013b38@l(r3)
	subf r0, r0, r26
	mulli r0, r0, 0xc
	add r4, r6, r0
	lfs f0, 0x14(r4)
	fmadds f3, f7, f4, f0
	cror eq, lt, eq
	bne @50
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f31, f1
	cror eq, lt, eq
	bne @51
	fmuls f0, f31, f31
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	b @52
	@51:
	fsubs f0, f31, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	fneg f6, f6
	b @52
	@50:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f31, f0
	bge @53
	fsubs f0, f31, f1
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	fneg f6, f6
	b @52
	@53:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f31, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	@52:
	lfs f0, 0x1c(r4)
	lwz r3, 0xc(r28)
	fnmsubs f4, f7, f6, f0
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @54
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @55
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @56
	@55:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @56
	@54:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @57
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @56
	@57:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@56:
	lwz r6, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_15_rsh_00013b8c@ha
	lfs f2, float_15_rsh_00013b8c@l(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_00013b48@ha
	lis r3, float_1_rsh_00013b38@ha
	fmadds f28, f2, f4, f0
	lfs f29, 0x1c(r6)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @58
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @59
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @60
	@59:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @60
	@58:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @61
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @60
	@61:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@60:
	lis r3, float_15_rsh_00013b8c@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00013b8c@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f30, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	lis r5, float_1p5_rsh_00013b90@ha
	lfs f4, float_1p5_rsh_00013b90@l(r5)
	lis r4, float_1p2_rsh_00013b98@ha
	lfd f1, 0xa8(r1)
	fmr f3, f27
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lis r3, float_0p8_rsh_00013b94@ha
	fsubs f2, f1, f2
	lfs f5, float_1p2_rsh_00013b98@l(r4)
	fmr f1, f28
	fmadds f4, f30, f4, f4
	lha r5, 0x2(r27)
	fdivs f6, f2, f0
	lfs f0, float_0p8_rsh_00013b94@l(r3)
	mr r3, r28
	mr r4, r27
	li r6, 0x1
	fmr f2, f29
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	lhz r0, 0x0(r27)
	ori r0, r0, 0x1
	sth r0, 0x0(r27)
	b @43
	@45:
	li r3, 0x3
	lwz r5, 0xc(r28)
	divw r0, r26, r3
	lis r4, wp@ha
	lfs f1, 0xc(r5)
	addi r4, r4, wp@l
	lfs f2, 0x2c(r5)
	lwz r4, 0x0(r4)
	mullw r0, r0, r3
	subf r0, r0, r26
	mulli r22, r0, 0xc
	add r3, r4, r22
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, wp@ha
	lwz r4, 0xc(r28)
	lwz r0, wp@l(r3)
	fmr f28, f1
	lfs f1, 0xc(r4)
	add r3, r0, r22
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl angleABf
	lis r3, float_200_rsh_00013b78@ha
	lfs f0, float_200_rsh_00013b78@l(r3)
	fcmpo cr0, f28, f0
	bge @62
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, float_360_rsh_00013b2c@ha
	lfd f0, 0xb0(r1)
	lis r3, zero_rsh_00013b20@ha
	fsubs f3, f0, f1
	lfs f1, float_360_rsh_00013b2c@l(r4)
	lfs f0, zero_rsh_00013b20@l(r3)
	fdivs f2, f3, f2
	fmadds f1, f2, f1, f0
	@62:
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @63
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @64
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @65
	@64:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @65
	@63:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @66
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @65
	@66:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@65:
	lwz r6, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_5_rsh_00013b9c@ha
	lfs f2, float_5_rsh_00013b9c@l(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_00013b48@ha
	lis r3, float_1_rsh_00013b38@ha
	fmadds f30, f2, f4, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @67
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @68
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @69
	@68:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @69
	@67:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @70
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @69
	@70:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@69:
	lis r3, float_5_rsh_00013b9c@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_5_rsh_00013b9c@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	lis r5, float_0p2_rsh_00013ba4@ha
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lis r4, float_0p3_rsh_00013ba0@ha
	lfd f1, 0xa8(r1)
	lis r3, float_0p5_rsh_00013b24@ha
	lfs f4, float_0p2_rsh_00013ba4@l(r5)
	fmr f3, f27
	fsubs f2, f1, f2
	lfs f5, float_0p3_rsh_00013ba0@l(r4)
	fmr f1, f30
	lha r5, 0x2(r27)
	fmadds f4, f28, f4, f5
	fdivs f6, f2, f0
	lfs f0, float_0p5_rsh_00013b24@l(r3)
	mr r3, r28
	mr r4, r27
	li r6, 0x1
	fmr f2, f31
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	lhz r0, 0x0(r27)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r27)
	b @43
	@71:
	entry jt_00004270
	lha r3, 0x4(r27)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r27)
	bge @43
	li r0, 0x0
	sth r0, 0x4(r27)
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@72:
	entry jt_0000429C
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f1, 0x0(r5)
	lis r4, float_200_rsh_00013b78@ha
	lfd f0, 0xb0(r1)
	lis r3, zero_rsh_00013b20@ha
	addi r5, r4, float_200_rsh_00013b78@l
	fsubs f3, f0, f2
	addi r4, r3, zero_rsh_00013b20@l
	lfs f2, 0x0(r5)
	lis r3, float_300_rsh_00013ba8@ha
	lfs f0, 0x0(r4)
	fdivs f3, f3, f1
	lfs f1, float_300_rsh_00013ba8@l(r3)
	fmadds f0, f3, f2, f0
	stfs f0, 0x1c(r27)
	lfs f0, 0x1c(r27)
	fmuls f0, f1, f0
	fdivs f28, f0, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_rsh_00013b50@l
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r4, r3, float_32767_rsh_00013b7c@l
	lfd f1, 0x0(r5)
	lis r3, zero_rsh_00013b20@ha
	lfd f0, 0xa8(r1)
	li r0, 0x0
	lfs f2, 0x0(r4)
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00013b20@l(r3)
	fsubs f0, f28, f1
	fdivs f2, f3, f2
	fmadds f0, f2, f0, f1
	stfs f0, 0x20(r27)
	lha r3, 0x2(r27)
	addi r3, r3, 0x1
	sth r3, 0x2(r27)
	sth r0, 0x4(r27)
	@73:
	entry jt_00004364
	lha r0, 0x4(r27)
	cmpwi r0, 0xc8
	bge @74
	lis r3, float_1_rsh_00013b38@ha
	lfs f1, float_1_rsh_00013b38@l(r3)
	b @75
	@74:
	subfic r3, r0, 0x320
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0xb4(r1)
	lis r3, float_600_rsh_00013bac@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_600_rsh_00013bac@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	@75:
	lis r3, zero_rsh_00013b20@ha
	fmr f28, f1
	lfs f0, zero_rsh_00013b20@l(r3)
	fcmpo cr0, f1, f0
	bge @76
	lhz r0, 0x0(r27)
	fmr f28, f0
	ori r0, r0, 0x200
	sth r0, 0x0(r27)
	@76:
	li r6, 0x3
	lis r3, gp@ha
	divw r5, r26, r6
	lwz r4, gp@l(r3)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	lis r3, double_to_int_mask_rsh_00013c18@ha
	lwz r0, 0x1c(r4)
	mullw r4, r5, r6
	add r0, r26, r0
	stw r0, 0xb4(r1)
	lis r5, wp@ha
	lfd f1, double_to_int_mask_rsh_00013c18@l(r3)
	lis r3, float_0p25_rsh_00013bb0@ha
	lfd f0, 0xb0(r1)
	subf r0, r4, r26
	mulli r0, r0, 0xc
	fsubs f1, f0, f1
	lfs f0, float_0p25_rsh_00013bb0@l(r3)
	lwz r3, wp@l(r5)
	add r3, r3, r0
	fmuls f1, f1, f0
	lfs f27, 0x14(r3)
	lfs f30, 0x18(r3)
	lfs f29, 0x1c(r3)
	bl sin
	lis r3, gp@ha
	lis r0, 0x4330
	addi r4, r3, gp@l
	frsp f2, f1
	lwz r5, 0x0(r4)
	lis r3, double_to_int_mask_rsh_00013c18@ha
	lfs f1, 0x20(r27)
	addi r4, r3, double_to_int_mask_rsh_00013c18@l
	lwz r5, 0x1c(r5)
	fmuls f3, f1, f2
	stw r0, 0xa8(r1)
	add r0, r26, r5
	lfs f0, 0x1c(r27)
	stw r0, 0xac(r1)
	lis r3, float_0p25_rsh_00013bb0@ha
	lfd f2, 0x0(r4)
	fmadds f30, f0, f28, f30
	lfd f1, 0xa8(r1)
	fmadds f27, f28, f3, f27
	lfs f0, float_0p25_rsh_00013bb0@l(r3)
	fsubs f1, f1, f2
	fmuls f1, f1, f0
	bl cos
	lwz r4, 0xc(r28)
	lis r3, float_15_rsh_00013b8c@ha
	lfs f0, 0x20(r27)
	frsp f4, f1
	lfs f3, 0xc(r4)
	fneg f1, f0
	lfs f2, float_15_rsh_00013b8c@l(r3)
	fsubs f0, f27, f3
	fmuls f1, f1, f4
	fdivs f0, f0, f2
	fadds f0, f3, f0
	fmadds f29, f28, f1, f29
	stfs f0, 0xc(r4)
	lwz r3, 0xc(r28)
	lfs f1, 0x1c(r3)
	fsubs f0, f30, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lwz r3, 0xc(r28)
	lfs f1, 0x2c(r3)
	fsubs f0, f29, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x4(r27)
	addi r0, r3, 0x1
	sth r0, 0x4(r27)
	b @43
	@77:
	entry jt_00004508
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lis r4, float_90_rsh_00013bb8@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xb0(r1)
	lis r3, float_neg45_rsh_00013bb4@ha
	addi r9, r4, float_90_rsh_00013bb8@l
	lis r4, float_6p2832_rsh_00013b28@ha
	fsubs f1, f1, f2
	addi r5, r3, float_neg45_rsh_00013bb4@l
	lis r3, wp@ha
	addi r8, r4, float_6p2832_rsh_00013b28@l
	addi r6, r3, wp@l
	lis r4, float_1_rsh_00013b38@ha
	fdivs f2, f1, f0
	lwz r10, 0x0(r6)
	lfs f0, 0x0(r5)
	lis r3, float_360_rsh_00013b2c@ha
	lfs f1, 0x0(r9)
	addi r7, r3, float_360_rsh_00013b2c@l
	fmadds f1, f2, f1, f0
	lfs f3, 0x550(r10)
	lfs f2, 0x0(r8)
	lis r6, float_0p00761_rsh_00013b30@ha
	lis r5, float_0p16605_rsh_00013b34@ha
	lfs f0, 0x0(r7)
	fadds f3, f3, f1
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lfs f28, 0x554(r10)
	fmuls f2, f2, f3
	lfs f5, float_0p00761_rsh_00013b30@l(r6)
	lfs f4, float_0p16605_rsh_00013b34@l(r5)
	lfs f3, float_1_rsh_00013b38@l(r4)
	fdivs f6, f2, f0
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @78
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @79
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b @80
	@79:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @80
	@78:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f6, f0
	bge @81
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @80
	@81:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@80:
	lwz r6, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_15_rsh_00013b8c@ha
	lfs f2, float_15_rsh_00013b8c@l(r4)
	lis r5, float_0p03705_rsh_00013b48@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f6, f1
	lis r4, float_0p4967_rsh_00013b4c@ha
	lis r3, float_1_rsh_00013b38@ha
	fmadds f30, f2, f5, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @82
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @83
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @84
	@83:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @84
	@82:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f6, f0
	bge @85
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @84
	@85:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@84:
	lis r3, float_15_rsh_00013b8c@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00013b8c@l(r3)
	fnmsubs f29, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f0, 0xb0(r1)
	lis r3, float_1_rsh_00013b38@ha
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00013b20@l(r4)
	lfs f0, float_1_rsh_00013b38@l(r3)
	fdivs f2, f3, f2
	fmadds f27, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f1, 0xa8(r1)
	lis r3, float_0p4_rsh_00013bbc@ha
	addi r5, r4, zero_rsh_00013b20@l
	fmr f4, f27
	fsubs f3, f1, f2
	addi r4, r3, float_0p4_rsh_00013bbc@l
	lfs f1, 0x0(r4)
	lis r3, float_100_rsh_00013bc0@ha
	lfs f2, 0x0(r5)
	fdivs f3, f3, f0
	lfs f0, float_100_rsh_00013bc0@l(r3)
	mr r3, r28
	mr r4, r27
	fmadds f5, f3, f2, f1
	fmr f1, f30
	fmr f2, f31
	fmr f3, f29
	fcmpo cr0, f28, f0
	bge @86
	lha r5, 0x2(r27)
	b @87
	@86:
	li r5, 0x0
	@87:
	li r6, 0x1
	bl moamoa_jump
	b @43
	@88:
	entry jt_00004800
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lis r4, float_90_rsh_00013bb8@ha
	lis r3, float_neg45_rsh_00013bb4@ha
	lfd f1, 0xb0(r1)
	addi r7, r4, float_90_rsh_00013bb8@l
	lfs f0, 0x0(r5)
	addi r6, r3, float_neg45_rsh_00013bb4@l
	fsubs f1, f1, f2
	lis r3, wp@ha
	addi r5, r3, wp@l
	lis r4, float_180_rsh_00013bc4@ha
	lwz r9, 0x0(r5)
	addi r8, r4, float_180_rsh_00013bc4@l
	fdivs f2, f1, f0
	lfs f0, 0x0(r6)
	lfs f1, 0x0(r7)
	lis r3, float_6p2832_rsh_00013b28@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	fmadds f0, f2, f1, f0
	lfs f4, 0x550(r9)
	lfs f3, 0x0(r8)
	addi r7, r4, float_360_rsh_00013b2c@l
	lfs f2, 0x0(r5)
	lis r3, float_3p1416_rsh_00013b3c@ha
	fadds f4, f4, f0
	lis r6, float_0p00761_rsh_00013b30@ha
	lfs f0, 0x0(r7)
	lis r5, float_0p16605_rsh_00013b34@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	fadds f4, f4, f3
	lfs f28, 0x554(r9)
	lfs f5, float_0p00761_rsh_00013b30@l(r6)
	lfs f3, float_1_rsh_00013b38@l(r4)
	fmuls f2, f2, f4
	lfs f4, float_0p16605_rsh_00013b34@l(r5)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @89
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @90
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @91
	@90:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @91
	@89:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f2, f0
	bge @92
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	b @91
	@92:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	@91:
	lwz r4, 0xc(r28)
	lis r3, float_30_rsh_00013bc8@ha
	lfs f1, float_30_rsh_00013bc8@l(r3)
	lfs f0, 0xc(r4)
	lfs f31, 0x1c(r4)
	fmadds f30, f1, f5, f0
	lfs f29, 0x2c(r4)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f0, 0xb0(r1)
	lis r3, float_1_rsh_00013b38@ha
	lis r5, float_2_rsh_00013bcc@ha
	fsubs f3, f0, f1
	lfs f1, zero_rsh_00013b20@l(r4)
	lfs f0, float_1_rsh_00013b38@l(r3)
	fdivs f3, f3, f2
	lfs f2, float_2_rsh_00013bcc@l(r5)
	fmadds f0, f3, f1, f0
	fmuls f27, f2, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lis r6, float_2_rsh_00013bcc@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xa8(r1)
	lis r4, zero_rsh_00013b20@ha
	lis r3, float_0p4_rsh_00013bbc@ha
	lfs f4, float_2_rsh_00013bcc@l(r6)
	fsubs f1, f1, f2
	addi r5, r4, zero_rsh_00013b20@l
	addi r4, r3, float_0p4_rsh_00013bbc@l
	lfs f2, 0x0(r5)
	lis r3, float_100_rsh_00013bc0@ha
	fdivs f3, f1, f0
	lfs f1, 0x0(r4)
	mr r4, r27
	lfs f0, float_100_rsh_00013bc0@l(r3)
	mr r3, r28
	fmadds f3, f3, f2, f1
	fmr f1, f30
	fmr f2, f31
	fmuls f5, f4, f3
	fmr f3, f29
	fmr f4, f27
	fcmpo cr0, f28, f0
	bge @93
	lha r5, 0x2(r27)
	b @94
	@93:
	li r5, 0x0
	@94:
	li r6, 0x1
	bl moamoa_jump
	b @43
	@95:
	entry jt_00004A64
	lwz r3, 0xc(r28)
	lfs f0, 0x14(r27)
	lfs f1, 0x1c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lfs f1, 0x14(r27)
	lfs f0, 0x20(r27)
	fsubs f0, f1, f0
	stfs f0, 0x14(r27)
	lwz r3, 0xc(r28)
	lfs f3, 0x8(r27)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r27)
	bl angleABf
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @96
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @97
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @98
	@97:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @98
	@96:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @99
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @98
	@99:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@98:
	lwz r7, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r5, float_0p4967_rsh_00013b4c@ha
	lfs f2, 0x1c(r27)
	lis r6, float_0p03705_rsh_00013b48@ha
	lfs f0, 0xc(r7)
	fcmpo cr0, f5, f1
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p4967_rsh_00013b4c@l(r5)
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_rsh_00013b48@l(r6)
	lfs f2, float_1_rsh_00013b38@l(r4)
	stfs f0, 0xc(r7)
	cror eq, lt, eq
	bne @100
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @101
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @102
	@101:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @102
	@100:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @103
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @102
	@103:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@102:
	lwz r3, 0xc(r28)
	fneg f1, f4
	lfs f2, 0x1c(r27)
	lfs f0, 0x2c(r3)
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x18(r27)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r27)
	bge @43
	lfs f0, 0x8(r27)
	li r0, 0x0
	lwz r3, 0xc(r28)
	stfs f0, 0xc(r3)
	lfs f0, 0xc(r27)
	lwz r3, 0xc(r28)
	stfs f0, 0x1c(r3)
	lfs f0, 0x10(r27)
	lwz r3, 0xc(r28)
	stfs f0, 0x2c(r3)
	lhz r3, 0x0(r27)
	rlwinm r3, r3, 0, 31, 29
	sth r3, 0x0(r27)
	lwz r3, 0x0(r28)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x0(r28)
	sth r0, 0x4(r27)
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@104:
	entry jt_00004CC0
	lha r3, 0x4(r27)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r27)
	cmpwi r0, 0x4
	ble @43
	lha r0, 0x24(r27)
	sth r0, 0x2(r27)
	b @43
	@105:
	entry jt_00004CE4
	lhz r0, 0x0(r27)
	clrlwi. r0, r0, 31
	bne @106
	lfs f27, 0x8c(r30)
	lfs f28, 0x94(r30)
	b @107
	@106:
	li r3, 0x3
	lis r4, wp@ha
	divw r0, r26, r3
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	mullw r0, r0, r3
	subf r0, r0, r26
	mulli r0, r0, 0xc
	add r3, r4, r0
	lfs f27, 0x14(r3)
	lfs f28, 0x1c(r3)
	@107:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f4, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	fmr f2, f28
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	fmr f1, f27
	lfd f3, 0xb0(r1)
	lwz r5, 0xc(r28)
	fsubs f5, f3, f4
	lfs f3, 0xc(r5)
	lfs f4, 0x2c(r5)
	fdivs f28, f5, f0
	bl angleABf
	lis r3, float_90_rsh_00013bb8@ha
	lis r4, float_neg45_rsh_00013bb4@ha
	addi r5, r3, float_90_rsh_00013bb8@l
	lfs f0, float_neg45_rsh_00013bb4@l(r4)
	lfs f2, 0x0(r5)
	lis r3, float_6p2832_rsh_00013b28@ha
	addi r8, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	fmadds f0, f28, f2, f0
	addi r7, r4, float_360_rsh_00013b2c@l
	lis r6, float_0p00761_rsh_00013b30@ha
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r4, float_1_rsh_00013b38@ha
	fadds f2, f1, f0
	lfs f1, 0x0(r8)
	lfs f0, 0x0(r7)
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @108
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @109
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @110
	@109:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @110
	@108:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @111
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @110
	@111:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@110:
	lwz r6, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_15_rsh_00013b8c@ha
	lfs f2, float_15_rsh_00013b8c@l(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_00013b48@ha
	lis r3, float_1_rsh_00013b38@ha
	fmadds f30, f2, f4, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @112
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @113
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @114
	@113:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @114
	@112:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @115
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @114
	@115:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@114:
	lis r3, float_15_rsh_00013b8c@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00013b8c@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f1, 0xa8(r1)
	lis r3, float_1_rsh_00013b38@ha
	lfs f5, zero_rsh_00013b20@l(r4)
	mr r4, r27
	fsubs f3, f1, f2
	lha r5, 0x2(r27)
	fmr f1, f30
	li r6, 0x1
	fmr f2, f31
	addi r5, r5, 0x1
	fdivs f6, f3, f0
	lfs f0, float_1_rsh_00013b38@l(r3)
	mr r3, r28
	fmadds f4, f28, f5, f0
	fmr f3, f27
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	b @43
	@116:
	entry jt_00004FE8
	lha r3, 0x4(r27)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r27)
	cmpwi r0, 0x1e
	bge @117
	lwz r4, 0xc(r28)
	lis r3, float_0p9_rsh_00013bd0@ha
	lfs f1, float_0p9_rsh_00013bd0@l(r3)
	lfs f0, 0x0(r4)
	fmuls f0, f0, f1
	stfs f0, 0x0(r4)
	lwz r3, 0xc(r28)
	lfs f0, 0x14(r3)
	fmuls f0, f0, f1
	stfs f0, 0x14(r3)
	lwz r3, 0xc(r28)
	lfs f0, 0x28(r3)
	fmuls f0, f0, f1
	stfs f0, 0x28(r3)
	b @43
	@117:
	li r0, 0x31
	sth r0, 0x2(r27)
	b @43
	@118:
	entry jt_00005048
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	lis r5, float_90_rsh_00013bb8@ha
	lis r4, float_135_rsh_00013bd4@ha
	lfs f0, float_135_rsh_00013bd4@l(r4)
	xoris r6, r3, 0x8000
	lfs f1, float_90_rsh_00013bb8@l(r5)
	lis r0, 0x4330
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r4, double_to_int_rsh_00013b50@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	stw r6, 0xac(r1)
	fmadds f0, f28, f1, f0
	addi r6, r4, double_to_int_rsh_00013b50@l
	stw r0, 0xa8(r1)
	lis r3, float_360_rsh_00013b2c@ha
	lfs f1, 0x0(r5)
	addi r4, r3, float_360_rsh_00013b2c@l
	lis r3, float_32767_rsh_00013b7c@ha
	fmuls f1, f1, f0
	lfs f0, 0x0(r4)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfd f3, 0x0(r6)
	lis r4, float_300_rsh_00013ba8@ha
	lfd f2, 0xa8(r1)
	fdivs f7, f1, f0
	addi r6, r4, float_300_rsh_00013ba8@l
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r4, float_0p16605_rsh_00013b34@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r3, float_1_rsh_00013b38@ha
	fsubs f3, f2, f3
	lfs f2, 0x0(r5)
	lis r5, float_200_rsh_00013b78@ha
	lfs f0, 0x0(r6)
	addi r7, r5, float_200_rsh_00013b78@l
	fcmpo cr0, f7, f1
	fdivs f3, f3, f2
	lfs f2, 0x0(r7)
	lis r5, float_0p00761_rsh_00013b30@ha
	lfs f4, float_0p16605_rsh_00013b34@l(r4)
	lfs f5, float_0p00761_rsh_00013b30@l(r5)
	fmadds f6, f3, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @119
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @120
	fmuls f0, f7, f7
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f7
	b @121
	@120:
	fsubs f0, f7, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	b @121
	@119:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f7, f0
	bge @122
	fsubs f1, f7, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	b @121
	@122:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	@121:
	lis r3, float_3p1416_rsh_00013b3c@ha
	lwz r6, 0xc(r28)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r5, float_0p03705_rsh_00013b48@ha
	lfs f0, 0xc(r6)
	lis r4, float_0p4967_rsh_00013b4c@ha
	fcmpo cr0, f7, f1
	lis r3, float_1_rsh_00013b38@ha
	fmadds f30, f6, f5, f0
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @123
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @124
	fmuls f0, f7, f7
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @125
	@124:
	fsubs f0, f7, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @125
	@123:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f7, f0
	bge @126
	fsubs f0, f7, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @125
	@126:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@125:
	lfs f0, 0x2c(r6)
	fnmsubs f31, f6, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, float_1_rsh_00013b38@ha
	lfd f0, 0xb0(r1)
	lis r3, float_5_rsh_00013b9c@ha
	fsubs f3, f0, f1
	lfs f1, float_1_rsh_00013b38@l(r4)
	lfs f0, float_5_rsh_00013b9c@l(r3)
	fdivs f2, f3, f2
	fmadds f27, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, float_0p1_rsh_00013bdc@ha
	lfd f0, 0xa8(r1)
	lis r3, float_0p2_rsh_00013bd8@ha
	cmpwi r24, 0x0
	fsubs f3, f0, f1
	lfs f1, float_0p1_rsh_00013bdc@l(r4)
	lfs f0, float_0p2_rsh_00013bd8@l(r3)
	fdivs f2, f3, f2
	fmadds f28, f2, f1, f0
	bne @127
	lis r3, vec3_rsh_00013758@ha
	addi r4, r1, 0x14
	addi r7, r3, vec3_rsh_00013758@l
	li r3, 0x6c3
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r5, 0xc(r28)
	lfs f0, 0xc(r5)
	stfs f0, 0x14(r1)
	lfs f0, 0x1c(r5)
	stfs f0, 0x18(r1)
	lfs f0, 0x2c(r5)
	stfs f0, 0x1c(r1)
	bl psndSFXOn_3D
	li r24, 0x1
	@127:
	lis r3, float_neg100_rsh_00013be0@ha
	fmr f1, f30
	lfs f2, float_neg100_rsh_00013be0@l(r3)
	fmr f3, f31
	fmr f4, f27
	mr r3, r28
	fmr f5, f28
	mr r4, r27
	li r5, 0x31
	li r6, 0x0
	bl moamoa_jump
	b @43
	@128:
	entry jt_00005398
	lha r3, 0x18(r27)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r27)
	ble @129
	lfs f1, 0x8(r27)
	lfs f0, 0x14(r27)
	fadds f0, f1, f0
	stfs f0, 0x8(r27)
	lfs f1, 0xc(r27)
	lfs f0, 0x1c(r27)
	fadds f0, f1, f0
	stfs f0, 0xc(r27)
	lfs f1, 0x10(r27)
	lfs f0, 0x20(r27)
	fadds f0, f1, f0
	stfs f0, 0x10(r27)
	lwz r3, 0xc(r28)
	lfs f0, 0x8(r27)
	lfs f1, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r28)
	lfs f0, 0xc(r27)
	lfs f1, 0x1c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lwz r3, 0xc(r28)
	lfs f0, 0x10(r27)
	lfs f1, 0x2c(r3)
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	b @43
	@129:
	li r0, 0x31
	sth r0, 0x2(r27)
	b @43
	@130:
	entry jt_00005428
	lis r3, wp@ha
	lwz r4, wp@l(r3)
	lhz r3, 0x0(r4)
	rlwinm. r0, r3, 0, 19, 19
	beq @131
	rlwinm. r0, r3, 0, 18, 18
	beq @131
	li r0, 0x3e
	sth r0, 0x2(r27)
	b @43
	@131:
	lha r0, 0x38(r4)
	cmpwi r0, 0x1f4
	bge @132
	lwz r3, 0xc(r28)
	bl PSMTXIdentity
	li r5, 0x3
	lis r6, wp@ha
	divw r4, r26, r5
	lwz r3, 0xc(r28)
	addi r7, r6, wp@l
	lwz r6, 0x0(r7)
	li r0, 0x0
	mullw r4, r4, r5
	subf r4, r4, r26
	mulli r8, r4, 0xc
	addi r4, r8, 0x14
	lfsx f0, r6, r4
	addi r5, r8, 0x18
	addi r4, r8, 0x1c
	stfs f0, 0xc(r3)
	lwz r6, 0x0(r7)
	lwz r3, 0xc(r28)
	lfsx f0, r6, r5
	stfs f0, 0x1c(r3)
	lwz r5, 0x0(r7)
	lwz r3, 0xc(r28)
	lfsx f0, r5, r4
	stfs f0, 0x2c(r3)
	sth r0, 0x0(r27)
	sth r0, 0x2(r27)
	sth r0, 0x4(r27)
	b @43
	@132:
	li r0, 0x3e
	sth r0, 0x2(r27)
	b @43
	@133:
	entry jt_000054DC
	lha r0, 0x4(r27)
	cmpwi r0, 0x1e
	bge @134
	lis r4, float_0p20944_rsh_00013be4@ha
	addi r3, r1, 0x74
	addi r5, r4, float_0p20944_rsh_00013be4@l
	li r4, 0x79
	lfs f1, 0x0(r5)
	bl PSMTXRotRad
	lwz r3, 0xc(r28)
	addi r4, r1, 0x74
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r28)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r28)
	lha r3, 0x4(r27)
	addi r0, r3, 0x1
	sth r0, 0x4(r27)
	b @43
	@134:
	lwz r0, 0x0(r28)
	ori r0, r0, 0x2
	stw r0, 0x0(r28)
	bl rand
	li r4, 0x1e
	divw r0, r3, r4
	mullw r0, r0, r4
	subf r0, r0, r3
	sth r0, 0x4(r27)
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@135:
	entry jt_00005560
	lha r3, 0x4(r27)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r27)
	bge @43
	li r0, 0x0
	sth r0, 0x4(r27)
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@136:
	entry jt_0000558C
	lwz r5, 0xc(r28)
	lis r4, float_neg275_rsh_00013be8@ha
	lis r3, float_neg100_rsh_00013be0@ha
	lfs f3, float_neg275_rsh_00013be8@l(r4)
	lfs f1, 0xc(r5)
	lfs f2, 0x2c(r5)
	lfs f4, float_neg100_rsh_00013be0@l(r3)
	bl distABf
	fmr f28, f1
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	lis r4, float_neg275_rsh_00013be8@ha
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lis r3, float_neg100_rsh_00013be0@ha
	lfd f1, 0xb0(r1)
	lwz r5, 0xc(r28)
	fsubs f3, f1, f2
	lfs f4, float_neg100_rsh_00013be0@l(r3)
	lfs f1, 0xc(r5)
	lfs f2, 0x2c(r5)
	fdivs f29, f3, f0
	lfs f3, float_neg275_rsh_00013be8@l(r4)
	bl angleABf
	lis r3, float_90_rsh_00013bb8@ha
	lis r4, float_neg45_rsh_00013bb4@ha
	addi r5, r3, float_90_rsh_00013bb8@l
	lfs f2, float_neg45_rsh_00013bb4@l(r4)
	lfs f3, 0x0(r5)
	lis r3, float_6_rsh_00013bec@ha
	lfs f0, float_6_rsh_00013bec@l(r3)
	fmadds f2, f29, f3, f2
	fcmpo cr0, f28, f0
	fadds f1, f1, f2
	ble @137
	lwz r3, 0xc(r28)
	lis r4, float_60_rsh_00013b18@ha
	lfs f0, float_60_rsh_00013b18@l(r4)
	lfs f30, 0x1c(r3)
	fcmpo cr0, f30, f0
	bge @137
	lis r4, float_6p2832_rsh_00013b28@ha
	lis r7, float_0p00761_rsh_00013b30@ha
	addi r6, r4, float_6p2832_rsh_00013b28@l
	lis r5, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r6)
	lis r6, float_0p16605_rsh_00013b34@ha
	lis r4, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r7)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r5)
	lfs f1, float_3p1416_rsh_00013b3c@l(r4)
	lis r5, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r6)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r5)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @138
	lis r4, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @139
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @140
	@139:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @140
	@138:
	lis r4, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r4)
	fcmpo cr0, f5, f0
	bge @141
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @140
	@141:
	lis r4, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@140:
	lis r4, float_3p1416_rsh_00013b3c@ha
	lis r5, float_15_rsh_00013b8c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r4)
	lis r6, float_0p03705_rsh_00013b48@ha
	lfs f2, float_15_rsh_00013b8c@l(r5)
	lis r5, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0xc(r3)
	fcmpo cr0, f5, f1
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p4967_rsh_00013b4c@l(r5)
	fmadds f31, f2, f4, f0
	lfs f4, float_0p03705_rsh_00013b48@l(r6)
	lfs f2, float_1_rsh_00013b38@l(r4)
	cror eq, lt, eq
	bne @142
	lis r4, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @143
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @144
	@143:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @144
	@142:
	lis r4, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r4)
	fcmpo cr0, f5, f0
	bge @145
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @144
	@145:
	lis r4, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r4)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@144:
	lis r4, float_15_rsh_00013b8c@ha
	lfs f0, 0x2c(r3)
	lfs f1, float_15_rsh_00013b8c@l(r4)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f1, 0xa8(r1)
	lis r3, float_1_rsh_00013b38@ha
	lfs f6, zero_rsh_00013b20@l(r4)
	lis r5, float_3_rsh_00013bf0@ha
	fsubs f1, f1, f2
	lfs f5, float_1_rsh_00013b38@l(r3)
	lfs f4, float_3_rsh_00013bf0@l(r5)
	fmr f2, f30
	fmr f3, f27
	lha r5, 0x2(r27)
	fdivs f7, f1, f0
	mr r3, r28
	mr r4, r27
	li r6, 0x1
	fmadds f0, f28, f6, f5
	fmr f1, f31
	fmadds f5, f7, f6, f5
	fmuls f4, f4, f0
	bl moamoa_jump
	b @43
	@137:
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@146:
	entry jt_000058AC
	lwz r4, 0xc(r28)
	lis r3, float_neg350_rsh_00013bf4@ha
	lfs f0, float_neg350_rsh_00013bf4@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	ble @147
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	lis r4, float_neg350_rsh_00013bf4@ha
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lis r3, float_neg100_rsh_00013be0@ha
	lfd f1, 0xb0(r1)
	lwz r5, 0xc(r28)
	fsubs f3, f1, f2
	lfs f4, float_neg100_rsh_00013be0@l(r3)
	lfs f1, 0xc(r5)
	lfs f2, 0x2c(r5)
	fdivs f28, f3, f0
	lfs f3, float_neg350_rsh_00013bf4@l(r4)
	bl angleABf
	lis r3, float_90_rsh_00013bb8@ha
	lis r4, float_neg45_rsh_00013bb4@ha
	addi r5, r3, float_90_rsh_00013bb8@l
	lfs f0, float_neg45_rsh_00013bb4@l(r4)
	lfs f2, 0x0(r5)
	lis r3, float_6p2832_rsh_00013b28@ha
	addi r8, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	fmadds f0, f28, f2, f0
	addi r7, r4, float_360_rsh_00013b2c@l
	lis r6, float_0p00761_rsh_00013b30@ha
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r4, float_1_rsh_00013b38@ha
	fadds f2, f1, f0
	lfs f1, 0x0(r8)
	lfs f0, 0x0(r7)
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @148
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @149
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @150
	@149:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @150
	@148:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @151
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @150
	@151:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@150:
	lwz r6, 0xc(r28)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_15_rsh_00013b8c@ha
	lfs f2, float_15_rsh_00013b8c@l(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_rsh_00013b48@ha
	lis r3, float_1_rsh_00013b38@ha
	fmadds f30, f2, f4, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @152
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @153
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @154
	@153:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @154
	@152:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @155
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @154
	@155:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@154:
	lis r3, float_15_rsh_00013b8c@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_rsh_00013b8c@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f0, 0x0(r5)
	lis r4, zero_rsh_00013b20@ha
	lfd f1, 0xa8(r1)
	lis r3, float_1_rsh_00013b38@ha
	lfs f6, zero_rsh_00013b20@l(r4)
	lis r5, float_3_rsh_00013bf0@ha
	fsubs f1, f1, f2
	lfs f5, float_1_rsh_00013b38@l(r3)
	lfs f4, float_3_rsh_00013bf0@l(r5)
	fmr f2, f31
	fmr f3, f27
	lha r5, 0x2(r27)
	fdivs f7, f1, f0
	mr r3, r28
	mr r4, r27
	li r6, 0x1
	fmadds f0, f28, f6, f5
	fmr f1, f30
	fmadds f5, f7, f6, f5
	fmuls f4, f4, f0
	bl moamoa_jump
	b @43
	@147:
	li r0, 0x3e
	sth r0, 0x2(r27)
	b @43
	@156:
	entry jt_00005BA0
	lhz r0, 0x0(r27)
	ori r0, r0, 0x20
	sth r0, 0x0(r27)
	lwz r0, 0x0(r28)
	clrrwi r0, r0, 1
	stw r0, 0x0(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x4
	stw r0, 0x0(r28)
	b @43
	@157:
	entry jt_00005BC8
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f2, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_rsh_00013b7c@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lfd f1, double_to_int_rsh_00013b50@l(r4)
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_rsh_00013b7c@l
	lfs f2, 0x0(r5)
	lis r4, float_1_rsh_00013b38@ha
	lfd f0, 0xa8(r1)
	lis r3, float_2_rsh_00013bcc@ha
	srawi r0, r26, 1
	fsubs f3, f0, f1
	lfs f0, float_2_rsh_00013bcc@l(r3)
	lfs f1, float_1_rsh_00013b38@l(r4)
	addze r3, r0
	fdivs f2, f3, f2
	fmadds f31, f2, f1, f0
	bl irand
	lis r5, float_90_rsh_00013bb8@ha
	lis r4, float_225_rsh_00013bf8@ha
	lfs f1, float_90_rsh_00013bb8@l(r5)
	lis r7, float_0p00761_rsh_00013b30@ha
	lfs f0, float_225_rsh_00013bf8@l(r4)
	lis r6, float_6p2832_rsh_00013b28@ha
	lis r5, float_360_rsh_00013b2c@ha
	lis r4, float_3p1416_rsh_00013b3c@ha
	fmadds f0, f28, f1, f0
	lfs f1, float_6p2832_rsh_00013b28@l(r6)
	lis r6, float_0p16605_rsh_00013b34@ha
	sth r3, 0x4(r27)
	lfs f4, float_0p00761_rsh_00013b30@l(r7)
	fmuls f2, f1, f0
	lfs f0, float_360_rsh_00013b2c@l(r5)
	lis r5, float_1_rsh_00013b38@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r4)
	fdivs f30, f2, f0
	lfs f3, float_0p16605_rsh_00013b34@l(r6)
	lfs f2, float_1_rsh_00013b38@l(r5)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @158
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @159
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f30
	b @160
	@159:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @160
	@158:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f30, f0
	bge @161
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @160
	@161:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@160:
	fmuls f0, f31, f4
	stfs f0, 0x8(r27)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	stw r3, 0xb4(r1)
	addi r5, r4, double_to_int_rsh_00013b50@l
	lis r3, float_32767_rsh_00013b7c@ha
	stw r0, 0xb0(r1)
	addi r4, r3, float_32767_rsh_00013b7c@l
	lfd f2, 0x0(r5)
	lis r3, float_1_rsh_00013b38@ha
	lfd f1, 0xb0(r1)
	addi r5, r3, float_1_rsh_00013b38@l
	lfs f0, 0x0(r4)
	lis r4, float_0p03705_rsh_00013b48@ha
	fsubs f3, f1, f2
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r3, float_0p4967_rsh_00013b4c@ha
	lfs f2, 0x0(r5)
	fdivs f0, f3, f0
	lfs f4, float_0p03705_rsh_00013b48@l(r4)
	lfs f3, float_0p4967_rsh_00013b4c@l(r3)
	fmadds f0, f0, f2, f2
	fcmpo cr0, f30, f1
	stfs f0, 0xc(r27)
	cror eq, lt, eq
	bne @162
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @163
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @164
	@163:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @164
	@162:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f30, f0
	bge @165
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @164
	@165:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@164:
	fneg f0, f4
	fmuls f0, f31, f0
	stfs f0, 0x10(r27)
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@166:
	entry jt_00005E54
	lha r3, 0x4(r27)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r27)
	bge @43
	lha r3, 0x2(r27)
	addi r0, r3, 0x1
	sth r0, 0x2(r27)
	b @43
	@167:
	entry jt_00005E78
	lis r3, float_1p1_rsh_00013bfc@ha
	lis r4, float_1p02_rsh_00013c00@ha
	addi r6, r3, float_1p1_rsh_00013bfc@l
	lis r3, float_0p20944_rsh_00013be4@ha
	lfs f1, 0x8(r27)
	addi r5, r4, float_1p02_rsh_00013c00@l
	lfs f3, 0x0(r6)
	addi r4, r3, float_0p20944_rsh_00013be4@l
	lfs f0, 0x0(r5)
	addi r3, r1, 0x44
	fmuls f2, f1, f3
	lfs f1, 0x0(r4)
	li r4, 0x79
	stfs f2, 0x8(r27)
	lfs f2, 0xc(r27)
	fmuls f0, f2, f0
	stfs f0, 0xc(r27)
	lfs f0, 0x10(r27)
	fmuls f0, f0, f3
	stfs f0, 0x10(r27)
	lwz r5, 0xc(r28)
	lfs f0, 0x8(r27)
	lfs f2, 0xc(r5)
	fadds f0, f2, f0
	stfs f0, 0xc(r5)
	lwz r5, 0xc(r28)
	lfs f0, 0xc(r27)
	lfs f2, 0x1c(r5)
	fadds f0, f2, f0
	stfs f0, 0x1c(r5)
	lwz r5, 0xc(r28)
	lfs f0, 0x10(r27)
	lfs f2, 0x2c(r5)
	fadds f0, f2, f0
	stfs f0, 0x2c(r5)
	bl PSMTXRotRad
	lwz r3, 0xc(r28)
	addi r4, r1, 0x44
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r28)
	lis r3, float_neg1000_rsh_00013c04@ha
	lfs f0, float_neg1000_rsh_00013c04@l(r3)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r28)
	lwz r3, 0xc(r28)
	lfs f1, 0xc(r3)
	fcmpo cr0, f1, f0
	bge @43
	li r0, 0x3e
	sth r0, 0x2(r27)
	@43:
	entry jt_00005F44
	lhz r0, 0x0(r27)
	andi. r0, r0, 0x98
	bne @168
	lwz r4, 0xc(r28)
	lis r3, float_290_rsh_00013c08@ha
	lfs f0, float_290_rsh_00013c08@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	ble @169
	stfs f0, 0xc(r4)
	@169:
	lwz r4, 0xc(r28)
	lis r3, float_neg290_rsh_00013c0c@ha
	lfs f0, float_neg290_rsh_00013c0c@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	bge @170
	stfs f0, 0xc(r4)
	@170:
	lwz r4, 0xc(r28)
	lis r3, float_50_rsh_00013b88@ha
	lfs f0, float_50_rsh_00013b88@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	ble @171
	stfs f0, 0x2c(r4)
	@171:
	lwz r4, 0xc(r28)
	lis r3, float_neg130_rsh_00013c10@ha
	lfs f0, float_neg130_rsh_00013c10@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	bge @168
	stfs f0, 0x2c(r4)
	@168:
	lwz r5, 0x0(r31)
	addi r26, r26, 0x1
	lwz r4, 0xc(r28)
	lwz r3, 0xc(r5)
	lfs f0, 0x10(r5)
	lfs f1, 0x38(r3)
	lfs f2, 0x1c(r4)
	fsubs f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x1c(r4)
	lwz r3, 0xc(r28)
	lfs f0, 0xc(r3)
	stfs f0, 0x28(r27)
	lwz r3, 0xc(r28)
	addi r28, r28, 0x20
	lfs f0, 0x2c(r3)
	stfs f0, 0x2c(r27)
	addi r27, r27, 0x50
	@23:
	lwz r3, 0x0(r31)
	lwz r0, 0x4(r3)
	cmpw r26, r0
	blt @24
	bl moamoa_pose_main
	lis r3, wp@ha
	addi r4, r3, wp@l
	lwz r5, 0x0(r4)
	lwz r3, 0xc(r5)
	lfs f0, 0x38(r3)
	stfs f0, 0x10(r5)
	lwz r3, 0x0(r4)
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq @172
	lis r3, zero_rsh_00013b20@ha
	lfs f0, zero_rsh_00013b20@l(r3)
	stfs f0, 0x174(r30)
	stfs f0, 0x178(r30)
	stfs f0, 0x17c(r30)
	b @173
	@172:
	lis r3, vec3_rsh_00013764@ha
	lfs f2, 0x174(r30)
	addi r6, r3, vec3_rsh_00013764@l
	lfs f1, 0x178(r30)
	lwz r5, 0x0(r6)
	addi r3, r1, 0x2c
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f0, 0x17c(r30)
	stw r4, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f2, 0x8(r1)
	stfs f1, 0xc(r1)
	lwz r5, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r4, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r5, 0x2c(r1)
	stw r4, 0x30(r1)
	stw r0, 0x34(r1)
	bl PSVECMag
	lis r3, float_2_rsh_00013bcc@ha
	lfs f0, float_2_rsh_00013bcc@l(r3)
	fcmpo cr0, f1, f0
	ble @173
	addi r3, r1, 0x2c
	mr r4, r3
	bl PSVECNormalize
	lis r3, float_2_rsh_00013bcc@ha
	lfs f0, 0x2c(r1)
	lfs f1, float_2_rsh_00013bcc@l(r3)
	fmuls f0, f1, f0
	stfs f0, 0x174(r30)
	lfs f0, 0x30(r1)
	fmuls f0, f1, f0
	stfs f0, 0x178(r30)
	lfs f0, 0x34(r1)
	fmuls f0, f1, f0
	stfs f0, 0x17c(r30)
	@173:
	psq_l f31, 0x128(r1), 0, 0
	lfd f31, 0x120(r1)
	psq_l f30, 0x118(r1), 0, 0
	lfd f30, 0x110(r1)
	psq_l f29, 0x108(r1), 0, 0
	lfd f29, 0x100(r1)
	psq_l f28, 0xf8(r1), 0, 0
	lfd f28, 0xf0(r1)
	psq_l f27, 0xe8(r1), 0, 0
	lfd f27, 0xe0(r1)
	lmw r22, 0xb8(r1)
	lwz r0, 0x134(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa) {
	nofralloc
	stwu r1, -0xf0(r1)
	mflr r0
	stw r0, 0xf4(r1)
	stfd f31, 0xe0(r1)
	psq_st f31, 0xe8(r1), 0, 0
	stfd f30, 0xd0(r1)
	psq_st f30, 0xd8(r1), 0, 0
	stfd f29, 0xc0(r1)
	psq_st f29, 0xc8(r1), 0, 0
	stmw r29, 0xb4(r1)
	mr r29, r3
	mr r30, r4
	bl marioGetPtr
	lwz r5, 0xc(r29)
	lis r4, float_20_rsh_00013c20@ha
	lfs f0, float_20_rsh_00013c20@l(r4)
	mr r31, r3
	lfs f2, 0x1c(r5)
	lfs f1, 0x90(r3)
	fadds f0, f0, f2
	fcmpo cr0, f1, f0
	ble @1
	li r3, 0x0
	b @2
	@1:
	lfs f0, 0x1b8(r31)
	fadds f0, f1, f0
	fcmpo cr0, f2, f0
	ble @3
	li r3, 0x0
	b @2
	@3:
	lfs f1, 0xc(r5)
	lfs f2, 0x2c(r5)
	lfs f3, 0x8c(r31)
	lfs f4, 0x94(r31)
	bl distABf
	lis r4, float_20_rsh_00013c20@ha
	lis r3, float_0p5_rsh_00013b24@ha
	lfs f2, 0x1b4(r31)
	lfs f3, float_20_rsh_00013c20@l(r4)
	lfs f0, float_0p5_rsh_00013b24@l(r3)
	fadds f2, f3, f2
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	bge @4
	lwz r3, 0xc(r29)
	lis r4, float_10_rsh_00013c24@ha
	lfs f1, float_10_rsh_00013c24@l(r4)
	lfs f0, 0x1c(r3)
	lfs f2, 0x90(r31)
	fadds f0, f1, f0
	fcmpo cr0, f2, f0
	ble @4
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 14, 14
	beq @4
	rlwinm. r0, r3, 0, 15, 15
	bne @4
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x558(r3)
	cmpwi r0, 0x2
	bge @4
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x16
	beq @5
	cmplwi r0, 0x1a
	beq @5
	li r3, 0x5
	bl marioChgMot
	@5:
	lis r4, wp@ha
	li r3, 0x1
	lwz r5, wp@l(r4)
	lwz r4, 0x558(r5)
	addi r0, r4, 0x1
	stw r0, 0x558(r5)
	b @2
	@4:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 15
	bne @6
	lis r3, wp@ha
	li r0, 0x0
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	stw r0, 0x558(r3)
	@6:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x12
	bne @7
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lha r0, 0x40(r3)
	cmpwi r0, 0xa
	ble @7
	li r3, 0x4
	bl camGetPtr
	lis r4, float_90_rsh_00013bb8@ha
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_rsh_00013bb8@l(r4)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f6, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @8
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @9
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f6
	b @10
	@9:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @10
	@8:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f6, f0
	bge @11
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @10
	@11:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@10:
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r4, float_35_rsh_00013c28@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r5, float_0p03705_rsh_00013b48@ha
	lfs f2, float_35_rsh_00013c28@l(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	lfs f0, 0x8c(r31)
	fcmpo cr0, f6, f1
	lis r3, float_1_rsh_00013b38@ha
	lfs f5, float_0p03705_rsh_00013b48@l(r5)
	fmadds f3, f2, f4, f0
	lfs f4, float_0p4967_rsh_00013b4c@l(r4)
	lfs f2, float_1_rsh_00013b38@l(r3)
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @13
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	b @14
	@13:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @14
	@12:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f6, f0
	bge @15
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	@14:
	lis r3, float_35_rsh_00013c28@ha
	lwz r4, 0xc(r29)
	lfs f0, 0x94(r31)
	lfs f2, float_35_rsh_00013c28@l(r3)
	lfs f1, 0xc(r4)
	fnmsubs f4, f2, f5, f0
	lfs f2, 0x2c(r4)
	bl distABf
	lis r3, float_35_rsh_00013c28@ha
	lfs f0, float_35_rsh_00013c28@l(r3)
	fcmpo cr0, f1, f0
	bge @7
	li r3, 0x2
	b @2
	@7:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x13
	bne @16
	lwz r0, 0x44(r31)
	cmpwi r0, 0x14
	bne @16
	lis r3, vec3_rsh_000136ec@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_rsh_000136ec@l
	addi r3, r31, 0x8c
	lwz r6, 0x0(r7)
	addi r4, r1, 0x98
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x50(r1)
	lfs f0, 0xc(r8)
	stw r5, 0x54(r1)
	lfs f1, 0x1c(r8)
	stfs f0, 0x50(r1)
	lfs f0, 0x2c(r8)
	stw r0, 0x58(r1)
	lwz r6, 0x50(r1)
	stfs f1, 0x54(r1)
	stfs f0, 0x58(r1)
	lwz r5, 0x54(r1)
	lwz r0, 0x58(r1)
	stw r6, 0x98(r1)
	stw r5, 0x9c(r1)
	stw r0, 0xa0(r1)
	bl PSVECDistance
	lis r3, float_65_rsh_00013c2c@ha
	lfs f0, float_65_rsh_00013c2c@l(r3)
	fcmpo cr0, f1, f0
	bge @16
	li r3, 0x2
	b @2
	@16:
	lis r4, wp@ha
	lis r3, zero_rsh_00013b20@ha
	addi r4, r4, wp@l
	lfs f0, zero_rsh_00013b20@l(r3)
	lwz r4, 0x0(r4)
	lfs f1, 0x55c(r4)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @17
	lis r3, vec3_rsh_000136f8@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_rsh_000136f8@l
	addi r3, r4, 0x564
	lwz r6, 0x0(r7)
	addi r4, r1, 0x8c
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x44(r1)
	lfs f0, 0xc(r8)
	stw r5, 0x48(r1)
	lfs f1, 0x1c(r8)
	stfs f0, 0x44(r1)
	lfs f0, 0x2c(r8)
	stw r0, 0x4c(r1)
	lwz r6, 0x44(r1)
	stfs f1, 0x48(r1)
	stfs f0, 0x4c(r1)
	lwz r5, 0x48(r1)
	lwz r0, 0x4c(r1)
	stw r6, 0x8c(r1)
	stw r5, 0x90(r1)
	stw r0, 0x94(r1)
	bl PSVECDistance
	lis r3, float_30_rsh_00013bc8@ha
	lfs f0, float_30_rsh_00013bc8@l(r3)
	fcmpo cr0, f1, f0
	bge @17
	li r3, 0x3
	b @2
	@17:
	li r3, 0x0
	bl partyGetPtr
	bl nokonokoGetStatus
	cmpwi r3, 0x2
	bne @18
	lis r3, vec3_rsh_00013704@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_rsh_00013704@l
	li r3, 0x0
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x38(r1)
	lfs f0, 0xc(r7)
	stw r4, 0x3c(r1)
	lfs f1, 0x1c(r7)
	stfs f0, 0x38(r1)
	lfs f0, 0x2c(r7)
	stw r0, 0x40(r1)
	lwz r5, 0x38(r1)
	stfs f1, 0x3c(r1)
	stfs f0, 0x40(r1)
	lwz r4, 0x3c(r1)
	lwz r0, 0x40(r1)
	stw r5, 0x80(r1)
	stw r4, 0x84(r1)
	stw r0, 0x88(r1)
	bl partyGetPtr
	addi r3, r3, 0x58
	addi r4, r1, 0x80
	bl PSVECDistance
	lis r3, float_30_rsh_00013bc8@ha
	lfs f0, float_30_rsh_00013bc8@l(r3)
	fcmpo cr0, f1, f0
	bge @18
	li r3, 0x2
	b @2
	@18:
	li r3, 0x0
	bl partyGetPtr
	lbz r0, 0x31(r3)
	cmpwi r0, 0x3
	bne @19
	li r3, 0x0
	bl partyGetPtr
	lbz r0, 0x39(r3)
	cmplwi r0, 0x46
	bne @19
	lis r3, vec3_rsh_00013710@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_rsh_00013710@l
	li r3, 0x0
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x2c(r1)
	lfs f0, 0xc(r7)
	stw r4, 0x30(r1)
	lfs f1, 0x1c(r7)
	stfs f0, 0x2c(r1)
	lfs f0, 0x2c(r7)
	stw r0, 0x34(r1)
	lwz r5, 0x2c(r1)
	stfs f1, 0x30(r1)
	stfs f0, 0x34(r1)
	lwz r4, 0x30(r1)
	lwz r0, 0x34(r1)
	stw r5, 0x74(r1)
	stw r4, 0x78(r1)
	stw r0, 0x7c(r1)
	bl partyGetPtr
	addi r3, r3, 0x58
	addi r4, r1, 0x74
	bl PSVECDistance
	lis r3, float_50_rsh_00013b88@ha
	lfs f0, float_50_rsh_00013b88@l(r3)
	fcmpo cr0, f1, f0
	bge @19
	li r3, 0x4
	b @2
	@19:
	lis r3, vec3_rsh_0001371c@ha
	lwz r11, 0xc(r29)
	addi r5, r3, vec3_rsh_0001371c@l
	lis r3, vec3_rsh_00013728@ha
	lwz r4, 0x0(r5)
	addi r9, r3, vec3_rsh_00013728@l
	lwz r0, 0x4(r5)
	lis r3, float_20_rsh_00013c20@ha
	lwz r10, 0x8(r5)
	addi r6, r3, float_20_rsh_00013c20@l
	stw r4, 0x20(r1)
	lis r3, float_0p5_rsh_00013b24@ha
	lfs f0, 0x8c(r31)
	addi r5, r3, float_0p5_rsh_00013b24@l
	stw r0, 0x24(r1)
	addi r3, r1, 0x68
	lfs f1, 0x1c(r11)
	addi r4, r1, 0x5c
	stfs f0, 0x20(r1)
	lwz r8, 0x0(r9)
	stfs f1, 0x24(r1)
	lwz r7, 0x4(r9)
	lwz r0, 0x8(r9)
	stw r7, 0x18(r1)
	lfs f0, 0x94(r31)
	stw r10, 0x28(r1)
	lwz r10, 0x20(r1)
	stfs f0, 0x28(r1)
	lwz r9, 0x24(r1)
	lwz r7, 0x28(r1)
	stfs f1, 0x18(r1)
	lfs f2, 0x0(r6)
	stw r10, 0x68(r1)
	lwz r6, 0x18(r1)
	stw r9, 0x6c(r1)
	lfs f0, 0x0(r5)
	stw r7, 0x70(r1)
	stw r8, 0x14(r1)
	lfs f3, 0xc(r11)
	lfs f1, 0x2c(r11)
	stw r0, 0x1c(r1)
	stfs f3, 0x14(r1)
	stfs f1, 0x1c(r1)
	lwz r5, 0x14(r1)
	lwz r0, 0x1c(r1)
	stw r5, 0x5c(r1)
	stw r6, 0x60(r1)
	stw r0, 0x64(r1)
	lfs f1, 0x1b4(r31)
	fadds f1, f2, f1
	fmuls f31, f1, f0
	bl PSVECDistance
	fcmpo cr0, f1, f31
	bge @20
	lfs f0, 0x28(r30)
	lis r3, vec3_rsh_00013734@ha
	lwz r5, 0xc(r29)
	addi r7, r3, vec3_rsh_00013734@l
	addi r3, r1, 0x68
	addi r4, r1, 0x5c
	stfs f0, 0xc(r5)
	lfs f0, 0x2c(r30)
	lwz r5, 0xc(r29)
	stfs f0, 0x2c(r5)
	lwz r8, 0xc(r29)
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x8(r1)
	lfs f0, 0xc(r8)
	stw r5, 0xc(r1)
	lfs f1, 0x1c(r8)
	stfs f0, 0x8(r1)
	lfs f0, 0x2c(r8)
	stw r0, 0x10(r1)
	lwz r6, 0x8(r1)
	stfs f1, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r6, 0x5c(r1)
	stw r5, 0x60(r1)
	stw r0, 0x64(r1)
	bl PSVECDistance
	fmr f29, f1
	fcmpo cr0, f29, f31
	bge @20
	lwz r3, 0xc(r29)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	fmr f30, f1
	lfs f2, 0x1a0(r31)
	bl compAngle
	lis r3, float_40_rsh_00013c30@ha
	fabs f1, f1
	lfs f0, float_40_rsh_00013c30@l(r3)
	fcmpo cr0, f1, f0
	bge @21
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lfs f0, 0x1a0(r31)
	lfs f1, 0x0(r5)
	lis r5, float_0p16605_rsh_00013b34@ha
	lis r4, float_360_rsh_00013b2c@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	fmuls f2, f1, f0
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r4, float_1_rsh_00013b38@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	fdivs f5, f2, f0
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @22
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @23
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @24
	@23:
	fsubs f0, f5, f1
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @24
	@22:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @25
	fsubs f5, f5, f1
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	b @24
	@25:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	@24:
	fsubs f6, f31, f29
	lis r3, float_6p2832_rsh_00013b28@ha
	addi r8, r3, float_6p2832_rsh_00013b28@l
	lis r6, float_0p03705_rsh_00013b48@ha
	lis r3, float_360_rsh_00013b2c@ha
	lfs f3, 0x0(r8)
	fmuls f0, f6, f4
	addi r7, r3, float_360_rsh_00013b2c@l
	lis r5, float_0p4967_rsh_00013b4c@ha
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r4, float_1_rsh_00013b38@ha
	lfs f5, float_0p03705_rsh_00013b48@l(r6)
	fneg f1, f0
	lfs f0, 0x0(r7)
	lfs f4, float_0p4967_rsh_00013b4c@l(r5)
	stfs f1, 0x174(r31)
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lfs f2, 0x1a0(r31)
	fmuls f2, f3, f2
	lfs f3, float_1_rsh_00013b38@l(r4)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @26
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @27
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	b @28
	@27:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @28
	@26:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f2, f0
	bge @29
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @28
	@29:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@28:
	fmuls f0, f6, f5
	stfs f0, 0x17c(r31)
	b @20
	@21:
	lis r3, float_6p2832_rsh_00013b28@ha
	lis r6, float_0p00761_rsh_00013b30@ha
	addi r5, r3, float_6p2832_rsh_00013b28@l
	lis r4, float_360_rsh_00013b2c@ha
	lfs f0, 0x0(r5)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lis r5, float_0p16605_rsh_00013b34@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	fmuls f2, f0, f30
	lfs f0, float_360_rsh_00013b2c@l(r4)
	lis r4, float_1_rsh_00013b38@ha
	lfs f4, float_0p00761_rsh_00013b30@l(r6)
	lfs f3, float_0p16605_rsh_00013b34@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @30
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @31
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @32
	@31:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @32
	@30:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @33
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @32
	@33:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@32:
	lwz r4, 0xc(r29)
	lis r3, float_3p1416_rsh_00013b3c@ha
	lfs f1, float_3p1416_rsh_00013b3c@l(r3)
	lis r5, float_0p03705_rsh_00013b48@ha
	lfs f0, 0xc(r4)
	lis r4, float_0p4967_rsh_00013b4c@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_rsh_00013b38@ha
	fnmsubs f2, f31, f4, f0
	lfs f0, 0x8c(r31)
	lfs f4, float_0p03705_rsh_00013b48@l(r5)
	lfs f3, float_0p4967_rsh_00013b4c@l(r4)
	fsubs f0, f2, f0
	lfs f2, float_1_rsh_00013b38@l(r3)
	stfs f0, 0x174(r31)
	cror eq, lt, eq
	bne @34
	lis r3, float_1p5708_rsh_00013b40@ha
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @35
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @36
	@35:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @36
	@34:
	lis r3, float_4p7124_rsh_00013b44@ha
	lfs f0, float_4p7124_rsh_00013b44@l(r3)
	fcmpo cr0, f5, f0
	bge @37
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @36
	@37:
	lis r3, float_1p5708_rsh_00013b40@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_rsh_00013b40@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@36:
	lwz r3, 0xc(r29)
	lfs f0, 0x94(r31)
	lfs f1, 0x2c(r3)
	fmadds f1, f31, f4, f1
	fsubs f0, f1, f0
	stfs f0, 0x17c(r31)
	@20:
	li r3, 0x0
	@2:
	psq_l f31, 0xe8(r1), 0, 0
	lfd f31, 0xe0(r1)
	psq_l f30, 0xd8(r1), 0, 0
	lfd f30, 0xd0(r1)
	psq_l f29, 0xc8(r1), 0, 0
	lfd f29, 0xc0(r1)
	lmw r29, 0xb4(r1)
	lwz r0, 0xf4(r1)
	mtlr r0
	addi r1, r1, 0xf0
	blr
}

asm static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
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
	stmw r29, 0x54(r1)
	fmr f27, f1
	cmpwi r6, 0x0
	fmr f28, f2
	mr r29, r3
	fmr f29, f3
	mr r30, r4
	fmr f31, f4
	mr r31, r5
	fmr f30, f5
	beq @1
	lis r4, zero_rsh_00013b20@ha
	lis r3, float_100_rsh_00013bc0@ha
	addi r5, r4, zero_rsh_00013b20@l
	lfs f0, float_100_rsh_00013bc0@l(r3)
	lfs f4, 0x0(r5)
	lis r4, float_1E06_rsh_00013c34@ha
	lfs f7, float_1E06_rsh_00013c34@l(r4)
	lis r3, float_neg1_rsh_00013b5c@ha
	fmr f6, f4
	lfs f5, float_neg1_rsh_00013b5c@l(r3)
	fadds f2, f0, f28
	stfs f4, 0x18(r1)
	addi r4, r1, 0x20
	addi r5, r1, 0x1c
	stfs f4, 0x1c(r1)
	addi r6, r1, 0x18
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	stfs f4, 0x20(r1)
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	stfs f7, 0x14(r1)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @1
	lfs f0, 0x1c(r1)
	lis r3, double_30_rsh_00013c38@ha
	fsubs f1, f28, f0
	lfd f0, double_30_rsh_00013c38@l(r3)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @2
	lis r3, float_0p1_rsh_00013b80@ha
	lfs f0, float_0p1_rsh_00013b80@l(r3)
	fsubs f31, f31, f0
	fadds f30, f30, f0
	@2:
	lfs f28, 0x1c(r1)
	@1:
	lis r3, vec3_rsh_000136e0@ha
	addi r4, r3, vec3_rsh_000136e0@l
	lwz r0, 0x0(r4)
	lwz r3, 0x4(r4)
	stw r0, 0x24(r1)
	lwz r0, 0x8(r4)
	stw r3, 0x28(r1)
	stfs f27, 0x24(r1)
	stw r0, 0x2c(r1)
	lwz r0, 0x24(r1)
	stfs f28, 0x28(r1)
	stfs f29, 0x2c(r1)
	lwz r3, 0x28(r1)
	stw r0, 0x8(r30)
	lwz r0, 0x2c(r1)
	stw r3, 0xc(r30)
	stw r0, 0x10(r30)
	stfs f31, 0x1c(r30)
	stfs f30, 0x20(r30)
	lwz r3, 0xc(r29)
	lfs f2, 0xc(r30)
	lfs f0, 0x1c(r3)
	lfs f1, 0xc(r3)
	fsubs f30, f2, f0
	lfs f2, 0x2c(r3)
	lfs f3, 0x8(r30)
	lfs f4, 0x10(r30)
	bl distABf
	lwz r3, 0xc(r29)
	fmr f31, f1
	lfs f3, 0x8(r30)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r30)
	bl angleABf
	lfs f0, 0x1c(r30)
	lis r5, 0x4330
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_0p5_rsh_00013b24@ha
	fdivs f0, f31, f0
	addi r6, r4, double_to_int_rsh_00013b50@l
	addi r4, r3, float_0p5_rsh_00013b24@l
	lis r3, float_180_rsh_00013bc4@ha
	stw r5, 0x40(r1)
	li r0, 0x3
	fctiwz f2, f0
	lfs f0, float_180_rsh_00013bc4@l(r3)
	lfd f4, 0x0(r6)
	fadds f0, f0, f1
	stw r5, 0x38(r1)
	stfd f2, 0x30(r1)
	lfs f2, 0x0(r4)
	lwz r3, 0x34(r1)
	sth r3, 0x18(r30)
	lha r3, 0x18(r30)
	lfs f5, 0x20(r30)
	xoris r3, r3, 0x8000
	stw r3, 0x44(r1)
	lfd f1, 0x40(r1)
	stw r3, 0x3c(r1)
	fsubs f1, f1, f4
	lfd f3, 0x38(r1)
	fdivs f1, f30, f1
	fsubs f3, f3, f4
	fmuls f3, f5, f3
	fmadds f1, f3, f2, f1
	stfs f1, 0x14(r30)
	sth r0, 0x2(r30)
	sth r31, 0x24(r30)
	stfs f0, 0x4(r29)
	lhz r0, 0x0(r30)
	ori r0, r0, 0x2
	sth r0, 0x0(r30)
	lwz r0, 0x0(r29)
	ori r0, r0, 0x10
	stw r0, 0x0(r29)
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x0(r29)
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
	lmw r29, 0x54(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm static void ext_shadow_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	cmpwi r31, 0x1
	bne @1
	bl GXClearBoundingBox
	@1:
	lis r3, g5_mt_s746@ha
	addi r3, r3, g5_mt_s746@l
	bl extLoadShadowMtx
	bl extLoadShadowRenderMode
	bl extLoadShadowVertex
	bl extLoadShadowTev
	bl extDrawShadow
	cmpwi r31, 0x1
	bne @2
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lis r3, str_000041A0@ha
	addi r3, r3, str_000041A0@l
	bl offscreenNameToId
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void ext_disp(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	cmpwi r31, 0x1
	bne @1
	bl GXClearBoundingBox
	@1:
	bl extLoadRenderMode
	bl extLoadVertex
	bl extLoadTexture
	bl extLoadTev
	bl extDraw
	bl extLoadTextureExit
	li r3, 0x0
	bl GXSetNumIndStages
	li r3, 0x0
	bl GXSetTevDirect
	cmpwi r31, 0x1
	bne @2
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lis r3, str_000041A0@ha
	addi r3, r3, str_000041A0@l
	bl offscreenNameToId
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void ext_moamoa_init(void) {
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
	stfd f25, 0x90(r1)
	psq_st f25, 0x98(r1), 0, 0
	stfd f24, 0x80(r1)
	psq_st f24, 0x88(r1), 0, 0
	stfd f23, 0x70(r1)
	psq_st f23, 0x78(r1), 0, 0
	stmw r19, 0x3c(r1)
	li r3, 0x870
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	li r5, 0x870
	stw r3, 0x0(r6)
	bl memset
	lis r3, str_00003D10@ha
	addi r3, r3, str_00003D10@l
	bl npcNameToPtr
	lis r5, wp@ha
	lis r4, str_00003D20@ha
	addi r6, r5, wp@l
	lwz r5, 0x8c(r3)
	lwz r6, 0x0(r6)
	addi r0, r4, str_00003D20@l
	lwz r4, 0x90(r3)
	stw r5, 0x14(r6)
	stw r4, 0x18(r6)
	lwz r4, 0x94(r3)
	mr r3, r0
	stw r4, 0x1c(r6)
	bl npcNameToPtr
	lis r5, wp@ha
	lwz r0, 0x90(r3)
	addi r7, r5, wp@l
	lwz r5, 0x8c(r3)
	lwz r6, 0x0(r7)
	lis r4, vec3_rsh_000136d4@ha
	stw r5, 0x20(r6)
	stw r0, 0x24(r6)
	lwz r0, 0x94(r3)
	stw r0, 0x28(r6)
	lwzu r3, vec3_rsh_000136d4@l(r4)
	lwz r5, 0x0(r7)
	lwz r0, 0x4(r4)
	stw r3, 0x2c(r5)
	stw r0, 0x30(r5)
	lwz r0, 0x8(r4)
	stw r0, 0x34(r5)
	bl extGetPoseNum
	lis r4, wp@ha
	addi r5, r4, wp@l
	lwz r4, 0x0(r5)
	stw r3, 0x4(r4)
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r3)
	mulli r3, r0, 0x50
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	lwz r5, 0x0(r6)
	stw r3, 0x8(r5)
	lwz r3, 0x0(r6)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	mulli r5, r0, 0x50
	bl memset
	bl moamoa_pose_init
	bl extGetPosePtr
	lis r4, wp@ha
	lis r8, zero_rsh_00013b20@ha
	addi r26, r4, wp@l
	lis r12, double_to_int_rsh_00013b50@ha
	lwz r19, 0x0(r26)
	lis r7, float_180_rsh_00013bc4@ha
	addi r30, r8, zero_rsh_00013b20@l
	lis r11, float_32767_rsh_00013b7c@ha
	lis r10, float_530_rsh_00013c58@ha
	lis r9, float_neg290_rsh_00013c0c@ha
	addi r8, r7, float_180_rsh_00013bc4@l
	lis r6, float_neg130_rsh_00013c10@ha
	addi r7, r6, float_neg130_rsh_00013c10@l
	lis r5, float_1E06_rsh_00013c34@ha
	addi r6, r5, float_1E06_rsh_00013c34@l
	lis r4, float_100_rsh_00013bc0@ha
	addi r5, r4, float_100_rsh_00013bc0@l
	lis r22, str_00003BC4@ha
	lis r21, str_00003BB8@ha
	lis r4, float_neg1_rsh_00013b5c@ha
	addi r28, r21, str_00003BB8@l
	lwz r19, 0x8(r19)
	lfd f23, double_to_int_rsh_00013b50@l(r12)
	mr r20, r3
	lfs f24, float_32767_rsh_00013b7c@l(r11)
	addi r27, r22, str_00003BC4@l
	lfs f25, float_530_rsh_00013c58@l(r10)
	addi r31, r4, float_neg1_rsh_00013b5c@l
	lfs f26, float_neg290_rsh_00013c0c@l(r9)
	li r21, 0x0
	lfs f27, 0x0(r30)
	lis r29, 0x4330
	lfs f28, 0x0(r8)
	lfs f29, 0x0(r7)
	lfs f30, 0x0(r6)
	lfs f31, 0x0(r5)
	b @1
	@2:
	li r0, 0x0
	mr r22, r27
	sth r0, 0x0(r19)
	mr r23, r28
	sth r0, 0x2(r19)
	sth r0, 0x4(r19)
	lhz r0, 0x0(r19)
	lwz r3, 0x0(r26)
	rlwinm. r0, r0, 0, 20, 20
	addi r24, r3, 0x50
	beq @3
	lbz r4, 0x4c(r19)
	lis r3, g5_group_tbl_s582@ha
	addi r0, r3, g5_group_tbl_s582@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r23, 0x0(r3)
	blt @4
	lwz r22, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_000041AC@ha
	addi r22, r3, str_000041AC@l
	@3:
	li r25, 0x0
	b @5
	@6:
	mr r3, r24
	mr r4, r23
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	mr r4, r22
	addi r3, r24, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	@7:
	addi r25, r25, 0x1
	addi r24, r24, 0x28
	@5:
	lwz r3, 0x0(r26)
	lwz r0, 0x4c(r3)
	cmpw r25, r0
	blt @6
	@8:
	lwz r3, 0x0(r26)
	lwz r0, 0x4c(r3)
	cmpw r25, r0
	bge @9
	lha r0, 0x3c(r19)
	cmpw r0, r25
	beq @9
	lhz r0, 0x0(r19)
	rlwinm. r0, r0, 0, 29, 29
	beq @10
	lis r4, str_000041B0@ha
	mr r3, r22
	addi r4, r4, str_000041B0@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r19)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_000041B4@ha
	mr r3, r22
	addi r4, r4, str_000041B4@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@11:
	lis r3, gp@ha
	sth r25, 0x3c(r19)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r19)
	stw r0, 0x40(r19)
	@9:
	lwz r0, 0x0(r20)
	ori r0, r0, 0x3
	stw r0, 0x0(r20)
	lwz r3, 0xc(r20)
	bl PSMTXIdentity
	bl rand
	xoris r0, r3, 0x8000
	stw r29, 0x28(r1)
	lwz r3, 0xc(r20)
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f23
	fdivs f0, f0, f24
	fmadds f0, f0, f25, f26
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r20)
	stfs f27, 0x1c(r3)
	bl rand
	xoris r0, r3, 0x8000
	lfs f4, 0x0(r30)
	stw r0, 0x34(r1)
	addi r4, r1, 0x20
	lwz r11, 0xc(r20)
	fmr f6, f4
	stw r29, 0x30(r1)
	addi r5, r1, 0x1c
	lfs f5, 0x0(r31)
	addi r6, r1, 0x18
	lfd f0, 0x30(r1)
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	fsubs f0, f0, f23
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	fdivs f0, f0, f24
	fmadds f0, f0, f28, f29
	stfs f0, 0x2c(r11)
	stfs f27, 0x18(r1)
	stfs f27, 0x1c(r1)
	stfs f27, 0x20(r1)
	stfs f30, 0x14(r1)
	lwz r11, 0xc(r20)
	lfs f0, 0x1c(r11)
	lfs f1, 0xc(r11)
	fadds f2, f31, f0
	lfs f3, 0x2c(r11)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @12
	lfs f0, 0x1c(r1)
	lwz r3, 0xc(r20)
	stfs f0, 0x1c(r3)
	@12:
	addi r21, r21, 0x1
	addi r20, r20, 0x20
	addi r19, r19, 0x50
	@1:
	lwz r3, 0x0(r26)
	lwz r0, 0x4(r3)
	cmpw r21, r0
	blt @2
	lis r3, str_000041BC@ha
	addi r3, r3, str_000041BC@l
	bl mapGetMapObj
	lis r4, wp@ha
	li r19, 0x0
	addi r5, r4, wp@l
	lwz r4, 0x0(r5)
	stw r3, 0xc(r4)
	lwz r4, 0x0(r5)
	lwz r3, 0xc(r4)
	lfs f0, 0x98(r3)
	stfs f0, 0x10(r4)
	@13:
	bl ext_moamoa_main
	addi r19, r19, 0x1
	cmpwi r19, 0x258
	blt @13
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
	psq_l f25, 0x98(r1), 0, 0
	lfd f25, 0x90(r1)
	psq_l f24, 0x88(r1), 0, 0
	lfd f24, 0x80(r1)
	psq_l f23, 0x78(r1), 0, 0
	lfd f23, 0x70(r1)
	lmw r19, 0x3c(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm static f32 randf(f32 min, f32 max) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stfd f30, 0x10(r1)
	psq_st f30, 0x18(r1), 0, 0
	fmr f30, f1
	fmr f31, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_rsh_00013b50@ha
	lis r3, float_32767_rsh_00013b7c@ha
	lfd f3, double_to_int_rsh_00013b50@l(r4)
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfs f1, float_32767_rsh_00013b7c@l(r3)
	lfd f2, 0x8(r1)
	fsubs f2, f2, f3
	fdivs f1, f2, f1
	fmadds f1, f1, f0, f30
	psq_l f31, 0x28(r1), 0, 0
	lfd f31, 0x20(r1)
	psq_l f30, 0x18(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f30, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	lis r5, wp@ha
	subfic r4, r3, 0x1
	addi r8, r5, wp@l
	slwi r0, r3, 1
	lwz r5, 0x0(r8)
	mulli r4, r4, 0xc
	cmpwi r3, 0x0
	addi r9, r5, 0x14
	add r6, r9, r4
	li r4, 0x64
	mulli r7, r3, 0xc
	lwz r5, 0x0(r6)
	lwz r3, 0x4(r6)
	add r7, r9, r7
	stw r5, 0x0(r7)
	stw r3, 0x4(r7)
	lwz r3, 0x8(r6)
	stw r3, 0x8(r7)
	lwz r3, 0x0(r8)
	add r3, r3, r0
	sth r4, 0x3a(r3)
	bne @1
	lwz r3, 0x0(r8)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x1000
	sth r0, 0x0(r3)
	b @2
	@1:
	lwz r3, 0x0(r8)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x2000
	sth r0, 0x0(r3)
	@2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r22, 0x8(r1)
	bl extGetPosePtr
	lis r4, wp@ha
	lis r5, str_00003BC4@ha
	addi r29, r4, wp@l
	mr r24, r3
	lwz r6, 0x0(r29)
	lis r4, str_00003BB8@ha
	addi r30, r5, str_00003BC4@l
	li r25, 0x0
	lwz r23, 0x8(r6)
	addi r31, r4, str_00003BB8@l
	b @1
	@2:
	lwz r3, 0x0(r24)
	li r0, 0x3d
	mr r26, r30
	mr r27, r31
	ori r3, r3, 0x4
	stw r3, 0x0(r24)
	lhz r3, 0x0(r23)
	ori r3, r3, 0x400
	sth r3, 0x0(r23)
	lhz r3, 0x0(r23)
	ori r3, r3, 0x100
	sth r3, 0x0(r23)
	lhz r3, 0x0(r23)
	ori r3, r3, 0x200
	sth r3, 0x0(r23)
	sth r0, 0x2(r23)
	lhz r0, 0x0(r23)
	ori r0, r0, 0x800
	sth r0, 0x0(r23)
	lhz r0, 0x0(r23)
	lwz r3, 0x0(r29)
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @3
	lbz r4, 0x4c(r23)
	lis r3, g5_group_tbl_s582@ha
	addi r0, r3, g5_group_tbl_s582@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @4
	lwz r26, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_000041AC@ha
	addi r26, r3, str_000041AC@l
	@3:
	li r28, 0x0
	b @5
	@6:
	mr r3, r22
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	mr r4, r26
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	@7:
	addi r28, r28, 0x1
	addi r22, r22, 0x28
	@5:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	blt @6
	@8:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	bge @9
	lha r0, 0x3c(r23)
	cmpw r0, r28
	beq @9
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq @10
	lis r4, str_000041B0@ha
	mr r3, r26
	addi r4, r4, str_000041B0@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_000041B4@ha
	mr r3, r26
	addi r4, r4, str_000041B4@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@11:
	lis r3, gp@ha
	sth r28, 0x3c(r23)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r23)
	stw r0, 0x40(r23)
	@9:
	addi r25, r25, 0x1
	addi r24, r24, 0x20
	addi r23, r23, 0x50
	@1:
	lwz r3, 0x0(r29)
	lwz r0, 0x4(r3)
	cmpw r25, r0
	blt @2
	lmw r22, 0x8(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl extGetPosePtr
	lis r3, wp@ha
	li r6, 0x0
	addi r5, r3, wp@l
	li r4, 0x3f
	lwz r3, 0x0(r5)
	lwz r7, 0x8(r3)
	b @1
	@2:
	lhz r0, 0x0(r7)
	addi r6, r6, 0x1
	rlwinm r0, r0, 0, 22, 20
	sth r0, 0x0(r7)
	sth r4, 0x2(r7)
	addi r7, r7, 0x50
	@1:
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r3)
	cmpw r6, r0
	blt @2
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r21, 0x14(r1)
	mr r22, r3
	lwz r21, 0x18(r3)
	lwz r4, 0x0(r21)
	bl evtGetValue
	lwz r4, 0x4(r21)
	mr r27, r3
	mr r3, r22
	bl evtGetValue
	mr r28, r3
	bl extGetPosePtr
	lis r3, wp@ha
	lis r4, str_00003BC4@ha
	addi r29, r3, wp@l
	lis r3, str_00003BB8@ha
	lwz r5, 0x0(r29)
	addi r30, r4, str_00003BC4@l
	addi r31, r3, str_00003BB8@l
	li r24, 0x0
	lwz r23, 0x8(r5)
	b @1
	@2:
	cmpwi r27, 0x0
	beq @3
	cmpwi r28, 0x0
	bne @4
	lbz r0, 0x4c(r23)
	cmplwi r0, 0x1
	bne @5
	lhz r0, 0x0(r23)
	ori r0, r0, 0x800
	sth r0, 0x0(r23)
	b @5
	@4:
	lhz r0, 0x0(r23)
	ori r0, r0, 0x800
	sth r0, 0x0(r23)
	b @5
	@3:
	cmpwi r28, 0x0
	bne @6
	lbz r0, 0x4c(r23)
	cmplwi r0, 0x1
	beq @5
	lhz r0, 0x0(r23)
	rlwinm r0, r0, 0, 21, 19
	sth r0, 0x0(r23)
	b @5
	@6:
	lhz r0, 0x0(r23)
	rlwinm r0, r0, 0, 21, 19
	sth r0, 0x0(r23)
	@5:
	lhz r0, 0x0(r23)
	mr r25, r30
	lwz r3, 0x0(r29)
	mr r21, r31
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @7
	lbz r4, 0x4c(r23)
	lis r3, g5_group_tbl_s582@ha
	addi r0, r3, g5_group_tbl_s582@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r21, 0x0(r3)
	blt @8
	lwz r25, 0x4(r3)
	@8:
	cmplwi r4, 0xa
	bne @7
	lis r3, str_000041AC@ha
	addi r25, r3, str_000041AC@l
	@7:
	li r26, 0x0
	b @9
	@10:
	mr r3, r22
	mr r4, r21
	bl strcmp
	cmpwi r3, 0x0
	bne @11
	mr r4, r25
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @12
	@11:
	addi r26, r26, 0x1
	addi r22, r22, 0x28
	@9:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r26, r0
	blt @10
	@12:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r26, r0
	bge @13
	lha r0, 0x3c(r23)
	cmpw r0, r26
	beq @13
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq @14
	lis r4, str_000041B0@ha
	mr r3, r25
	addi r4, r4, str_000041B0@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@14:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @15
	lis r4, str_000041B4@ha
	mr r3, r25
	addi r4, r4, str_000041B4@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@15:
	lis r3, gp@ha
	sth r26, 0x3c(r23)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r23)
	stw r0, 0x40(r23)
	@13:
	addi r24, r24, 0x1
	addi r23, r23, 0x50
	@1:
	lwz r3, 0x0(r29)
	lwz r0, 0x4(r3)
	cmpw r24, r0
	blt @2
	lmw r21, 0x14(r1)
	li r3, 0x2
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	cmpwi r4, 0x0
	stw r0, 0x34(r1)
	stmw r22, 0x8(r1)
	beq @1
	bl extGetPosePtr
	lis r5, wp@ha
	lis r4, float_1_rsh_00013b38@ha
	addi r6, r5, wp@l
	lfs f0, float_1_rsh_00013b38@l(r4)
	lwz r5, 0x0(r6)
	lwz r7, 0x8(r5)
	li r5, 0x0
	b @2
	@3:
	lwz r4, 0xc(r3)
	li r0, 0xe
	cmpwi r5, 0x64
	stfs f0, 0x28(r4)
	lwz r4, 0xc(r3)
	stfs f0, 0x14(r4)
	lwz r4, 0xc(r3)
	stfs f0, 0x0(r4)
	sth r0, 0x24(r7)
	sth r0, 0x2(r7)
	bge @4
	li r4, 0x64
	divw r0, r5, r4
	mullw r0, r0, r4
	subf r0, r0, r5
	b @5
	@4:
	li r4, 0x3c
	divw r0, r5, r4
	mullw r0, r0, r4
	subf r4, r0, r5
	addi r0, r4, 0x64
	@5:
	sth r0, 0x4(r7)
	addi r5, r5, 0x1
	addi r3, r3, 0x20
	lhz r0, 0x0(r7)
	ori r0, r0, 0x100
	sth r0, 0x0(r7)
	addi r7, r7, 0x50
	@2:
	lwz r4, 0x0(r6)
	lwz r0, 0x4(r4)
	cmpw r5, r0
	blt @3
	@1:
	bl extGetPosePtr
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @6
	@7:
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 22, 22
	bne @8
	li r3, 0x0
	b @9
	@8:
	addi r3, r3, 0x50
	bdnz @7
	@6:
	bl extGetPosePtr
	lis r4, wp@ha
	lis r5, str_00003BC4@ha
	addi r29, r4, wp@l
	mr r25, r3
	lwz r6, 0x0(r29)
	lis r4, str_00003BB8@ha
	addi r30, r5, str_00003BC4@l
	li r23, 0x0
	lwz r24, 0x8(r6)
	addi r31, r4, str_00003BB8@l
	b @10
	@11:
	lwz r3, 0x0(r25)
	li r0, 0x3d
	mr r26, r30
	mr r27, r31
	ori r3, r3, 0x4
	stw r3, 0x0(r25)
	lhz r3, 0x0(r24)
	ori r3, r3, 0x400
	sth r3, 0x0(r24)
	sth r0, 0x2(r24)
	lhz r0, 0x0(r24)
	lwz r3, 0x0(r29)
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @12
	lbz r4, 0x4c(r24)
	lis r3, g5_group_tbl_s582@ha
	addi r0, r3, g5_group_tbl_s582@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @13
	lwz r26, 0x4(r3)
	@13:
	cmplwi r4, 0xa
	bne @12
	lis r3, str_000041AC@ha
	addi r26, r3, str_000041AC@l
	@12:
	li r28, 0x0
	b @14
	@15:
	mr r3, r22
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne @16
	mr r4, r26
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @17
	@16:
	addi r28, r28, 0x1
	addi r22, r22, 0x28
	@14:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	blt @15
	@17:
	lwz r3, 0x0(r29)
	lwz r0, 0x4c(r3)
	cmpw r28, r0
	bge @18
	lha r0, 0x3c(r24)
	cmpw r0, r28
	beq @18
	lhz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 29, 29
	beq @19
	lis r4, str_000041B0@ha
	mr r3, r26
	addi r4, r4, str_000041B0@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @18
	@19:
	lhz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 27, 27
	beq @20
	lis r4, str_000041B4@ha
	mr r3, r26
	addi r4, r4, str_000041B4@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @18
	@20:
	lis r3, gp@ha
	sth r28, 0x3c(r24)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r24)
	stw r0, 0x40(r24)
	@18:
	addi r23, r23, 0x1
	addi r25, r25, 0x20
	addi r24, r24, 0x50
	@10:
	lwz r3, 0x0(r29)
	lwz r0, 0x4(r3)
	cmpw r23, r0
	blt @11
	li r3, 0x2
	@9:
	lmw r22, 0x8(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extGetPosePtr
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4(r3)
	lwz r3, 0x8(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @1
	@2:
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 26, 26
	bne @3
	li r3, 0x0
	b @4
	@3:
	addi r3, r3, 0x50
	bdnz @2
	@1:
	li r3, 0x2
	@4:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extGetPosePtr
	lis r4, zero_rsh_00013b20@ha
	li r6, 0x0
	addi r5, r4, zero_rsh_00013b20@l
	lis r4, wp@ha
	lfs f0, 0x0(r5)
	addi r5, r4, wp@l
	b @1
	@2:
	stfs f0, 0x14(r3)
	addi r6, r6, 0x1
	stfs f0, 0x1c(r3)
	addi r3, r3, 0x20
	@1:
	lwz r4, 0x0(r5)
	lwz r0, 0x4(r4)
	cmpw r6, r0
	blt @2
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl extReset
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall) {
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
	cmpwi r31, 0x0
	beq @1
	lis r4, wp@ha
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	lhz r0, 0x0(r4)
	or r0, r0, r3
	sth r0, 0x0(r4)
	b @2
	@1:
	lis r4, wp@ha
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
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

asm static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r29, r3
	lis r3, wp@ha
	mr r26, r4
	addi r3, r3, wp@l
	mr r30, r5
	lhz r0, 0x0(r29)
	lwz r3, 0x0(r3)
	rlwinm. r0, r0, 0, 20, 20
	addi r27, r3, 0x50
	beq @1
	lbz r0, 0x4c(r29)
	lis r3, g5_group_tbl_s582@ha
	addi r3, r3, g5_group_tbl_s582@l
	clrlslwi r4, r0, 24, 3
	cmplwi r0, 0x2
	lwzx r26, r3, r4
	blt @2
	add r3, r3, r4
	lwz r30, 0x4(r3)
	@2:
	cmplwi r0, 0xa
	bne @1
	lis r3, str_000041AC@ha
	addi r0, r3, str_000041AC@l
	mr r30, r0
	@1:
	lis r3, wp@ha
	li r31, 0x0
	addi r28, r3, wp@l
	b @3
	@4:
	mr r3, r27
	mr r4, r26
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	mr r4, r30
	addi r3, r27, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @6
	@5:
	addi r31, r31, 0x1
	addi r27, r27, 0x28
	@3:
	lwz r3, 0x0(r28)
	lwz r0, 0x4c(r3)
	cmpw r31, r0
	blt @4
	@6:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r31, r0
	bge @7
	lha r0, 0x3c(r29)
	cmpw r0, r31
	beq @7
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 29, 29
	beq @8
	lis r4, str_000041B0@ha
	mr r3, r30
	addi r4, r4, str_000041B0@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @7
	@8:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 27, 27
	beq @9
	lis r4, str_000041B4@ha
	mr r3, r30
	addi r4, r4, str_000041B4@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @7
	@9:
	lis r3, gp@ha
	sth r31, 0x3c(r29)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r29)
	stw r0, 0x40(r29)
	@7:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm static void moamoa_pose_main(void) {
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
	stmw r22, 0x18(r1)
	bl extGetPosePtr
	lis r4, wp@ha
	lis r7, float_60_rsh_00013b18@ha
	addi r29, r4, wp@l
	lis r6, float_1000_rsh_00013b1c@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_rsh_00013b38@ha
	lis r4, double_to_int_rsh_00013b50@ha
	lis r8, gp@ha
	lwz r24, 0x8(r9)
	mr r25, r3
	lfs f28, float_60_rsh_00013b18@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_rsh_00013b1c@l(r6)
	li r26, 0x0
	lfs f30, float_1_rsh_00013b38@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_rsh_00013b50@l(r4)
	lis r23, 0x4330
	b @1
	@2:
	lwz r3, 0xf8(r31)
	li r0, 0x3e8
	lwz r4, 0x0(r30)
	li r5, 0x0
	srwi r3, r3, 2
	lha r7, 0x3c(r24)
	divwu r6, r3, r0
	lwz r27, 0x3c(r4)
	lwz r0, 0x44(r24)
	lwz r28, 0x38(r4)
	subfc r4, r0, r27
	lwz r0, 0x40(r24)
	mulli r7, r7, 0x28
	subfe r3, r0, r28
	addi r22, r7, 0x50
	add r22, r8, r22
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f28, f1
	lfs f0, 0x1c(r22)
	fdivs f1, f1, f29
	fdivs f1, f1, f0
	fcmpo cr0, f1, f30
	cror eq, gt, eq
	bne @3
	stw r27, 0x44(r24)
	lis r3, zero_rsh_00013b20@ha
	lfs f1, zero_rsh_00013b20@l(r3)
	stw r28, 0x40(r24)
	@3:
	lwz r3, 0x24(r22)
	addi r26, r26, 0x1
	stw r23, 0x8(r1)
	addi r24, r24, 0x50
	subi r0, r3, 0x1
	lwz r3, 0x20(r22)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f31
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x10(r1)
	lwz r0, 0x14(r1)
	add r0, r3, r0
	stw r0, 0x10(r25)
	addi r25, r25, 0x20
	@1:
	lwz r8, 0x0(r29)
	lwz r0, 0x4(r8)
	cmpw r26, r0
	blt @2
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	lmw r22, 0x18(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".data") u32 gap_04_00015044_data[1] = {0};
#pragma force_active reset
