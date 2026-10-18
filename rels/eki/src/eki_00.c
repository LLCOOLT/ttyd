// FAKE: PREFIX asm (F2): functions 1-20 in target order (img_set_color .. moamoa_pose_main) are asm with their C kept under #ifdef NONMATCHING; moamoa_pose_init stays real C. The prefix ends at moamoa_pose_main because randf/pose_main need the compiler int->float constant that the asm pool owns (double_to_int_eki_00008df8 cannot be shared from C). Named .rodata in target order; suffix C points at the named str_/float objects.
#include "driver/imgdrv.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr.h"
#include "driver/mapdrv.h"
#include "string.h"
#include "memory.h"
#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "mario/mariost.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "driver/hitdrv.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/offscreendrv.h"
#include "system.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "party.h"
#include "party/party_cloud.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "manager/evtmgr_cmd.h"
#undef EXT_LIT
#define EXT_LIT(sym, val) (val)
extern const char str_00000664[];
extern const char zero_eki_00008e28[];
extern const f64 double_30_eki_00008e20;
extern const f32 float_0p1_eki_00008d54[];
extern const f32 float_1000_eki_00008df0[];
extern const f32 float_100_eki_00008d70[];
extern const f32 float_10_eki_00008e0c[];
extern const f32 float_180_eki_00008d9c[];
extern const f32 float_1E06_eki_00008e1c[];
extern const f32 float_1_eki_00008d10[];
extern const f32 float_20_eki_00008e08[];
extern const f32 float_30_eki_00008da0[];
extern const f32 float_32767_eki_00008d50[];
extern const f32 float_35_eki_00008e10[];
extern const f32 float_360_eki_00008d04[];
extern const f32 float_40_eki_00008e18[];
extern const f32 float_50_eki_00008d5c[];
extern const f32 float_60_eki_00008dec[];
extern const f32 float_65_eki_00008e14[];
extern const f32 float_6p2832_eki_00008d00[];
extern const f32 float_90_eki_00008d94[];
extern const f32 zero_eki_00008cf4[];
extern const char str_00000040[];
extern const char str_0000004C[];
extern const char str_00000050[];
extern const char str_00000054[];
extern const char str_00000060[];
extern const char str_0000006C[];
extern const char str_00000070[];
extern const char str_0000007C[];
extern const char str_00000080[];
extern const char str_00000088[];
extern const char str_0000008C[];
extern const char str_00000094[];
extern const char str_00000098[];
extern const char str_000000A0[];
extern const char str_000000A8[];
extern const char str_000000B0[];
extern const char str_00000170[];
extern const char str_00000178[];
extern const char str_00000184[];
extern const char str_00000190[];
extern const char str_00000198[];
extern const char str_000001A0[];
extern const char str_000001A8[];
extern const char str_000001B0[];
extern const char str_000001B8[];
extern const char str_000001C4[];
extern const char str_000001D0[];
extern const char str_000001DC[];
extern const char str_000001E8[];
extern const char str_000001F4[];
extern const char str_000001FC[];
extern const char str_00000204[];
extern const char str_00000208[];
extern const char str_00000214[];
extern const char str_0000021C[];
extern const char str_00000224[];
extern const char str_00000230[];
extern const char str_00000238[];
extern const char str_00000240[];
extern const char str_00000258[];
extern const char str_00000274[];
extern const char str_00000280[];
extern const char str_0000028C[];
extern const char str_000002A8[];
extern const char str_000002B0[];
extern const char str_000002B8[];
extern const char str_000002C8[];
extern const char str_000002D0[];
extern const char str_000002E0[];
extern const char str_000002F0[];
extern const char str_00000300[];
extern const char str_00000310[];
extern const char str_00000320[];
extern const char str_00000330[];
extern const char str_00000348[];
extern const char str_00000358[];
extern const char str_00000360[];
extern const char str_00000370[];
extern const char str_00000380[];
extern const char str_00000390[];
extern const char str_000003A0[];
extern const char str_000003B0[];
extern const char str_000003C0[];
extern const char str_000003D0[];
extern const char str_000003DC[];
extern const char str_000003E8[];
extern const char str_00000404[];
extern const char str_00000410[];
extern const char str_0000041C[];
extern const char str_00000428[];
extern const char str_0000042C[];
extern const char str_00000430[];
extern const char str_00000448[];
extern const char str_00000458[];
extern const char str_00000474[];
extern const char str_00000484[];
extern const char str_0000049C[];
extern const char str_000004B4[];
extern const char str_000004BC[];
extern const char str_000004D4[];
extern const char str_000004E0[];
extern const char str_000004EC[];
extern const char str_000004FC[];
extern const char str_00000508[];
extern const char str_00000514[];
extern const char str_00000524[];
extern const char str_00000560[];
extern const char str_00000578[];
extern const char str_0000057C[];
extern const char str_00000580[];
extern const char str_00000040[];
extern const char str_0000004C[];
extern const char str_00000050[];
extern const char str_00000054[];
extern const char str_00000060[];
extern const char str_0000006C[];
extern const char str_00000070[];
extern const char str_0000007C[];
extern const char str_00000080[];
extern const char str_00000088[];
extern const char str_0000008C[];
extern const char str_00000094[];
extern const char str_00000098[];
extern const char str_000000A0[];
extern const char str_000000A8[];
extern const char str_000000B0[];
extern const char str_00000170[];
extern const char str_00000178[];
extern const char str_00000184[];
extern const char str_00000190[];
extern const char str_00000198[];
extern const char str_000001A0[];
extern const char str_000001A8[];
extern const char str_000001B0[];
extern const char str_000001B8[];
extern const char str_000001C4[];
extern const char str_000001D0[];
extern const char str_000001DC[];
extern const char str_000001E8[];
extern const char str_000001F4[];
extern const char str_000001FC[];
extern const char str_00000204[];
extern const char str_00000208[];
extern const char str_00000214[];
extern const char str_0000021C[];
extern const char str_00000224[];
extern const char str_00000230[];
extern const char str_00000238[];
extern const char str_00000240[];
extern const char str_00000258[];
extern const char str_00000274[];
extern const char str_00000280[];
extern const char str_0000028C[];
extern const char str_000002A8[];
extern const char str_000002B0[];
extern const char str_000002B8[];
extern const char str_000002C8[];
extern const char str_000002D0[];
extern const char str_000002E0[];
extern const char str_000002F0[];
extern const char str_00000300[];
extern const char str_00000310[];
extern const char str_00000320[];
extern const char str_00000330[];
extern const char str_00000348[];
extern const char str_00000358[];
extern const char str_00000360[];
extern const char str_00000370[];
extern const char str_00000380[];
extern const char str_00000390[];
extern const char str_000003A0[];
extern const char str_000003B0[];
extern const char str_000003C0[];
extern const char str_000003D0[];
extern const char str_000003DC[];
extern const char str_000003E8[];
extern const char str_00000404[];
extern const char str_00000410[];
extern const char str_0000041C[];
extern const char str_00000428[];
extern const char str_0000042C[];
extern const char str_00000430[];
extern const char str_00000448[];
extern const char str_00000458[];
extern const char str_00000474[];
extern const char str_00000484[];
extern const char str_0000049C[];
extern const char str_000004B4[];
extern const char str_000004BC[];
extern const char str_000004D4[];
extern const char str_000004E0[];
extern const char str_000004EC[];
extern const char str_000004FC[];
extern const char str_00000508[];
extern const char str_00000514[];
extern const char str_00000524[];
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on
u32 gap_05_00000004_bss[1];
#pragma force_active reset
extern const char str_00000040[];
extern const char str_0000004C[];
extern const char str_00000050[];
extern const char str_00000054[];
extern const char str_00000170[];
extern const char str_00000178[];
extern const char str_00000184[];
extern const char str_00000190[];
extern const char str_00000198[];
extern const char str_000001A0[];
extern const char str_000001A8[];
extern const char str_000001B0[];
extern const char str_000001B8[];
extern const char str_000001C4[];
extern const char str_000001D0[];
extern const char str_000001DC[];
extern const char str_000001E8[];
extern const char str_000001F4[];
extern const char str_000001FC[];
extern const char str_00000204[];
extern const char str_00000208[];
extern const char str_00000214[];
extern const char str_0000021C[];
extern const char str_00000224[];
extern const char str_00000230[];
extern const char str_00000238[];
extern const char str_00000240[];
extern const char str_00000258[];
extern const char str_00000274[];
extern const char str_00000280[];
extern const char str_0000028C[];
extern const char str_000002A8[];
extern const char str_000002B0[];
extern const char str_000002B8[];
extern const char str_000002C8[];
extern const char str_000002D0[];
extern const char str_000002E0[];
extern const char str_000002F0[];
extern const char str_00000300[];
extern const char str_00000310[];
extern const char str_00000320[];
extern const char str_00000330[];
extern const char str_00000348[];
extern const char str_00000358[];
extern const char str_00000360[];
extern const char str_00000370[];
extern const char str_00000380[];
extern const char str_00000390[];
extern const char str_000003A0[];
extern const char str_000003B0[];
extern const char str_000003C0[];
extern const char str_000003D0[];
extern const char str_000003DC[];
extern const char str_000003E8[];
extern const char str_00000404[];
extern const char str_00000410[];
extern const char str_0000041C[];
extern const char str_00000428[];
extern const char str_0000042C[];
extern const char str_00000430[];
extern const char str_00000448[];
extern const char str_00000458[];
extern const char str_00000474[];
extern const char str_00000484[];
extern const char str_0000049C[];
extern const char str_000004B4[];
extern const char str_000004BC[];
extern const char str_000004D4[];
extern const char str_000004E0[];
extern const char str_000004EC[];
extern const char str_000004FC[];
extern const char str_00000508[];
extern const char str_00000514[];
extern const char str_00000524[];

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 lastX; f32 lastZ; Vec field_0x30; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 hitCount; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 idleFrames; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 bounceCount; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
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
extern const char* g_moamoa_chain_tbl[][2];
extern const s32 dat_80419a28;
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
#pragma inline_max_total_size(100000)
#pragma opt_propagation off
#pragma opt_lifetimes off
static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
static inline f32 moa_sinx(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 moa_cosx(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
#pragma opt_propagation reset
#pragma opt_lifetimes reset
s32 nokonokoGetStatus(PartyEntry* party);
f32 cloudGetBreathDist(void);
double sin(double x);
double cos(double x);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void ext_disp(CameraId camera, void* param);
static void ext_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);
static void ext_shadow_disp(CameraId camera, void* param);

s32 evt_bero_get_info(EventEntry* event, BOOL isFirstCall);
s32 evt_bero_mapchange(EventEntry* event, BOOL isFirstCall);
s32 evt_cam3d_evt_set(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_letter_box_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall);
s32 evt_ext_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_key_get_buttontrg(EventEntry* event, BOOL isFirstCall);
s32 evt_map_set_tevcallback(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_rotate(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_trans(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_dispflag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_key_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_normalize(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_set_pose(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_blow(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_flag_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_fusion_debug(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_kind_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print_party(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_battle_start(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_flag_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_pera_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_reverse_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_battle_info(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_ry(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_set_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_npc_wait_battle_end(EventEntry* event, BOOL isFirstCall);
s32 evt_party_cont_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_party_run(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_dir(EventEntry* event, BOOL isFirstCall);
s32 evt_party_set_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_stop(EventEntry* event, BOOL isFirstCall);
s32 evt_seq_wait(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_envon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxoff(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_sfxon_3d(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_mapname(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_sincos(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_stopwatch(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_get_system_flag(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_get_value(EventEntry* event, BOOL isFirstCall);
s32 evt_sub_intpl_msec_init(EventEntry* event, BOOL isFirstCall);
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
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_target_off(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_end_wait(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_ry_reset(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static s32 evt_moamoa_exit(EventEntry* event, BOOL isFirstCall);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void moamoa_pose_main(void);
static void moamoa_pose_init(void);
extern s32 evt_bero_info_run[];

s32 evt_cam3d_evt_off(EventEntry* event, BOOL isFirstCall);
s32 evt_cam_shake(EventEntry* event, BOOL isFirstCall);
s32 evt_del_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_exit_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_hitobj_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_img_alloc_capture(EventEntry* event, BOOL isFirstCall);
s32 evt_img_clear_virtual_point(EventEntry* event, BOOL isFirstCall);
s32 evt_img_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_img_onoff(EventEntry* event, BOOL isFirstCall);
s32 evt_img_set_paper(EventEntry* event, BOOL isFirstCall);
s32 evt_img_set_paper_anim(EventEntry* event, BOOL isFirstCall);
s32 evt_item_delete(EventEntry* event, BOOL isFirstCall);
s32 evt_item_delete_check(EventEntry* event, BOOL isFirstCall);
s32 evt_item_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_item_flag_on(EventEntry* event, BOOL isFirstCall);
s32 evt_item_get_position(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_bound_rate(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_gravity(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_jump_power(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_move_dir_speed(EventEntry* event, BOOL isFirstCall);
s32 evt_item_set_position(EventEntry* event, BOOL isFirstCall);
s32 evt_item_status_on(EventEntry* event, BOOL isFirstCall);
s32 evt_map_checkanim(EventEntry* event, BOOL isFirstCall);
s32 evt_map_playanim(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_clear_offscreen(EventEntry* event, BOOL isFirstCall);
s32 evt_mapobj_set_offscreen(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_party(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_mov_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_delete(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_set_scale(EventEntry* event, BOOL isFirstCall);
s32 evt_mobj_switch_blue(EventEntry* event, BOOL isFirstCall);
s32 evt_offscreen_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_paper_entry(EventEntry* event, BOOL isFirstCall);
s32 evt_party_jump_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_party_move_pos2(EventEntry* event, BOOL isFirstCall);
s32 evt_pouch_remove_item(EventEntry* event, BOOL isFirstCall);
s32 evt_run_case_evt(EventEntry* event, BOOL isFirstCall);
s32 evt_snd_bgmoff_f(EventEntry* event, BOOL isFirstCall);
s32 evt_win_item_select(EventEntry* event, BOOL isFirstCall);
s32 img_set_color(EventEntry* event, BOOL isFirstCall);
s32 img_set_color(EventEntry* event, BOOL isFirstCall);
extern s32 bero_case_entry[];

__declspec(section ".data") u64 fd_eki_00_negone_one_374;
__declspec(section ".data") s32 fd_eki_00_neg_one_382[1];
__declspec(section ".data") s32 fd_eki_00___local_PI_383[1];
__declspec(section ".data") s32 fd_eki_00___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_eki_00_one_negone_373;
__declspec(section ".data") s32 fd_eki_00___local_PIO2_384[1];
__declspec(section ".data") s32 fd_eki_00_one_381[1];
__declspec(section ".data") u64 fd_eki_00_negone_one_360;
__declspec(section ".data") s32 fd_eki_00_neg_one_365[1];
__declspec(section ".data") s32 fd_eki_00___local_PI_366[1];
__declspec(section ".data") s32 fd_eki_00___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_eki_00_one_negone_359;
__declspec(section ".data") s32 fd_eki_00___local_PIO2_367[1];
__declspec(section ".data") s32 fd_eki_00_one_364[1];
static s32 ext_moamoa_data[141];
__declspec(section ".data") static s32 e_door_close[12];
__declspec(section ".data") static s32 e_door_open[12];
static s32 s_door_close[22];
static s32 s_door_open[22];
static s32 bero_data[45];
s32 evt_bridge[14];
s32 evt_bridge2[118];
static s32 evt_origami[198];
static s32 evt_moamoa_init[29];
static s32 evt_meet_moamoa[215];
static s32 evt_moamoa_escape[47];
s32 evt_elv_rumble[60];
static s32 evt_elv_init[49];
s32 evt_elv_down[554];
s32 evt_elv_up[456];
__declspec(section ".data") static s32 item_tbl[2];
s32 evt_elv[61];
s32 evt_elv_nomsg[14];
static s32 evt_head[42];
static s32 evt_kanban[14];
s32 eki_00_init_evt[99];

__declspec(section ".data") u64 fd_eki_00_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_00_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_00___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_00___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_00_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_00___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_00_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_eki_00_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_eki_00_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_eki_00___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_eki_00___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_eki_00_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_eki_00___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_eki_00_one_364[] = {
    1065353216,
};

static s32 ext_moamoa_data[] = {
    (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 0, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1073741824, (s32)((char*)str_00000040), (s32)((char*)str_0000004C),
    1082130432, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1086324736, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1090519040, (s32)((char*)str_00000040),
    (s32)((char*)str_0000004C), 1092616192, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1094713344, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1096810496,
    (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1098907648, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1099956224, (s32)((char*)str_00000040), (s32)((char*)str_0000004C),
    1101004800, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1102053376, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1103101952, (s32)((char*)str_00000040),
    (s32)((char*)str_0000004C), 1104150528, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1105199104, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1106247680,
    (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1107296256, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1107820544, (s32)((char*)str_00000040), (s32)((char*)str_0000004C),
    1108344832, (s32)((char*)str_00000040), (s32)((char*)str_0000004C), 1108869120, (s32)((char*)str_00000040), (s32)((char*)str_00000050), 0, (s32)((char*)str_00000040),
    (s32)((char*)str_00000050), 1082130432, (s32)((char*)str_00000040), (s32)((char*)str_00000050), 1090519040, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 0,
    (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1073741824, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1082130432, (s32)((char*)str_00000054), (s32)((char*)str_0000004C),
    1086324736, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1090519040, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1092616192, (s32)((char*)str_00000054),
    (s32)((char*)str_0000004C), 1094713344, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1096810496, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1098907648,
    (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1099956224, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1101004800, (s32)((char*)str_00000054), (s32)((char*)str_0000004C),
    1102053376, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1103101952, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1104150528, (s32)((char*)str_00000054),
    (s32)((char*)str_0000004C), 1105199104, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1106247680, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1107296256,
    (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1107820544, (s32)((char*)str_00000054), (s32)((char*)str_0000004C), 1108344832, (s32)((char*)str_00000054), (s32)((char*)str_0000004C),
    1108869120, (s32)((char*)str_00000054), (s32)((char*)str_00000050), 0, (s32)((char*)str_00000054), (s32)((char*)str_00000050), 1082130432, (s32)((char*)str_00000054),
    (s32)((char*)str_00000050), 1090519040, 0, 0, 0,
};
extern const char str_00000040[];
extern const char str_0000004C[];
extern const char str_00000054[];
extern const char str_00000060[];
extern const char str_0000006C[];
extern const char str_00000070[];
extern const char str_0000007C[];
extern const char str_00000080[];
extern const char str_00000088[];
extern const char str_0000008C[];
extern const char str_00000094[];
extern const char str_00000098[];
extern const char str_000000A0[];
extern const char str_000000A8[];
extern const char str_000000B0[];
__declspec(section ".data") static u32 g5_group_tbl_s588[22] = { (u32)(char*)str_00000040, (u32)(char*)str_0000004C, (u32)(char*)str_00000054, (u32)(char*)str_0000004C, (u32)(char*)str_00000060, (u32)(char*)str_0000006C, (u32)(char*)str_00000070, (u32)(char*)str_0000007C, (u32)(char*)str_00000080, (u32)(char*)str_00000088, (u32)(char*)str_0000008C, (u32)(char*)str_00000094, (u32)(char*)str_00000098, (u32)(char*)str_0000006C, (u32)(char*)str_000000A0, (u32)(char*)str_0000006C, (u32)(char*)str_000000A8, (u32)(char*)str_0000006C, (u32)(char*)str_000000B0, (u32)(char*)str_0000006C, (u32)(char*)str_00000040, (u32)(char*)str_0000004C };
__declspec(section ".data") static u32 g5_mt_s758[12] = { 0x41000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000, 0x3F000000, 0x00000000, 0x00000000, 0x41000000, 0x00000000 };















int rand(void);







double sin(double x);


void envAddTev(s32 type, MapTevCallbackInfo* info);





#pragma dont_inline on
static void moamoa_pose_init(void) {
    MoamoaData* data = (MoamoaData*)ext_moamoa_data;
    s32 i = 0;
    s32 start;
    char model[32];
    char anim[32];

    strcpy(model, (char*)zero_eki_00008e28);
    strcpy(anim, (char*)zero_eki_00008e28);
    wp->numDefs = -1;
    do {
        if (strcmp(data->model, model)) {
            strcpy(model, data->model);
            strcpy(anim, (char*)zero_eki_00008e28);
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
        if (!strncmp(anim, (char*)str_00000664, 1)) {
            wp->defs[wp->numDefs].loop = 0;
        }
        i++;
    } while ((++data)->model != NULL);
    wp->numDefs++;
}
#pragma dont_inline reset
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
        t = float_60_eki_00008dec[0] * OSTicksToMilliseconds(now - moa->startTime) / float_1000_eki_00008df0[0] / def->speed;

        if (t >= float_1_eki_00008d10[0]) {
            moa->startTime = now;
            t = zero_eki_00008cf4[0];
        }
        pose->frame = def->start + (s32)((def->count - 1) * t);
    }
}
#endif
#ifdef NONMATCHING
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    static const char* group_tbl[][2] = {
        {(char*)str_00000040, (char*)str_0000004C},
        {(char*)str_00000054, (char*)str_0000004C},
        {(char*)str_00000060, (char*)str_0000006C},
        {(char*)str_00000070, (char*)str_0000007C},
        {(char*)str_00000080, (char*)str_00000088},
        {(char*)str_0000008C, (char*)str_00000094},
        {(char*)str_00000098, (char*)str_0000006C},
        {(char*)str_000000A0, (char*)str_0000006C},
        {(char*)str_000000A8, (char*)str_0000006C},
        {(char*)str_000000B0, (char*)str_0000006C},
        {(char*)str_00000040, (char*)str_0000004C},
    };
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = (char*)str_00000578;
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
            if (strncmp(anim, (char*)str_0000057C, 1)) {
                return;
            }
        }
        if (moa->flags & 0x10) {
            if (strncmp(anim, (char*)str_00000580, 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
#endif
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
        pose->field_0x14 = zero_eki_00008cf4[0];
        pose->field_0x1c = zero_eki_00008cf4[0];
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
            pose->mtx[2][2] = float_1_eki_00008d10[0];
            pose->mtx[1][1] = float_1_eki_00008d10[0];
            pose->mtx[0][0] = float_1_eki_00008d10[0];
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
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_0000004C);
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
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_0000004C);
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
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_0000004C);
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
#ifdef NONMATCHING
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / float_32767_eki_00008d50[0];

    return r * (max - min) + min;
}
#endif
#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING  // restored C definition (nmrepair)
__declspec(section ".rodata") static Vec ext_moamoa_t0 = {0.0f, 0.0f, 10.0f};
#endif
#ifdef NONMATCHING  // restored C definition (nmrepair)
__declspec(section ".rodata") static Vec ext_moamoa_t1 = {0.0f, 0.0f, 10.0f};
#endif
#ifdef NONMATCHING  // restored C definition (nmrepair)
__declspec(section ".rodata") static Vec ext_moamoa_t2 = {0.0f, 0.0f, 10.0f};
#endif
#ifdef NONMATCHING
static void ext_moamoa_init(void) {
    s32 i, j;
    ExtPose* pose;
    Moamoa* moa;
    f32 rad;
    f32 hitX, hitY, hitZ, dist, hd, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = ext_moamoa_t0;
    wp->target[1] = ext_moamoa_t1;
    wp->target[2] = ext_moamoa_t2;
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
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_0000004C);
        rad = randf(zero_eki_00008cf4[0], float_6p2832_eki_00008d00[0]);
        dist = randf(zero_eki_00008cf4[0], float_100_eki_00008d70[0]);
        pose->flags |= 0x13;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = wp->target[0].x + dist * moa_sin(rad);
        pose->mtx[1][3] = zero_eki_00008cf4[0];
        pose->mtx[0][3] = wp->target[0].z - dist * moa_cos(rad);
        hitX = hitY = hitZ = zero_eki_00008cf4[0];
        hd = float_1E06_eki_00008e1c[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hd, &nx, &ny, &nz, pose->mtx[0][3], float_100_eki_00008d70[0] + pose->mtx[1][3], pose->mtx[2][3], zero_eki_00008cf4[0], -float_1_eki_00008d10[0], zero_eki_00008cf4[0])) {
            pose->mtx[1][3] = hitY;
        }
    }
    for (j = 0; j < 600; j++) {
        ext_moamoa_main();
    }
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_0000041C), left, top, right, bottom);
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
        offscreenAddBoundingBox(offscreenNameToId((char*)str_0000041C), left, top, right, bottom);
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
        hitX = hitY = hitZ = zero_eki_00008cf4[0];
        dist = float_1E06_eki_00008e1c[0];
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, x, float_100_eki_00008d70[0] + y, z, zero_eki_00008cf4[0], -float_1_eki_00008d10[0], zero_eki_00008cf4[0])) {
            if (__fabs(y - hitY) > double_30_eki_00008e20) {
                speed -= float_0p1_eki_00008d54[0];
                gravity += float_0p1_eki_00008d54[0];
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
    pose->rot = float_180_eki_00008d9c[0] + angle;
    moa->flags |= 2;
    pose->flags |= 0x10;
    pose->flags &= ~4;
}
#endif
#pragma dont_inline reset
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

    if (mario->position.y > float_20_eki_00008e08[0] + pose->mtx[1][3]) {
        return 0;
    }
    if (pose->mtx[1][3] > mario->position.y + mario->wPlayerCollisionBox.y) {
        return 0;
    }
    if (distABf(pose->mtx[0][3], pose->mtx[2][3], mario->position.x, mario->position.z) < (mario->wPlayerCollisionBox.x + float_20_eki_00008e08[0]) / 2
        && mario->position.y > float_10_eki_00008e0c[0] + pose->mtx[1][3] && (mario->flags & 0x20000) && !(mario->flags & 0x10000)
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
        f32 r2; f32 t; cam = camGetPtr(CAMERA_3D);
        t = cam->viewYaw; r2 = float_6p2832_eki_00008d00[0] * reviseAngle((f32)(mario->displayDirection - float_90_eki_00008d94[0]) + t) / float_360_eki_00008d04[0];
        angle = float_35_eki_00008e10[0] * moa_sin(r2) + mario->position.x;
        dist = mario->position.z - float_35_eki_00008e10[0] * moa_cos(r2);
        if (distABf(pose->mtx[0][3], pose->mtx[2][3], angle, dist) < float_35_eki_00008e10[0]) {
            return 2;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14) {
        f32 (*m)[4] = pose->mtx;
        a = (Vec){m[0][3], m[1][3], m[2][3]};
        if (PSVECDistance(&mario->position, &a) < float_65_eki_00008e14[0]) {
            return 2;
        }
    }
    if (wp->breathDir >= zero_eki_00008cf4[0]) {
        f32 (*m)[4] = pose->mtx;
        b = (Vec){m[0][3], m[1][3], m[2][3]};
        if (PSVECDistance(&wp->breathPos, &b) < float_30_eki_00008da0[0]) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        f32 (*m)[4] = pose->mtx;
        c = (Vec){m[0][3], m[1][3], m[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < float_30_eki_00008da0[0]) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == 3 && partyGetPtr(0)->useMotionId == 0x46) {
        f32 (*m)[4] = pose->mtx;
        d = (Vec){m[0][3], m[1][3], m[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < float_50_eki_00008d5c[0]) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, pose->mtx[1][3], mario->position.z};
    f = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
    range = (mario->wPlayerCollisionBox.x + float_20_eki_00008e08[0]) / 2;
    if (PSVECDistance(&e, &f) < range) {
        pose->mtx[0][3] = moa->lastX;
        pose->mtx[2][3] = moa->lastZ;
        {
            f32 (*m)[4] = pose->mtx;
            f = (Vec){m[0][3], m[1][3], m[2][3]};
        }
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < float_40_eki_00008e18[0]) {
                mario->unk174.x = -((range - dist) * moa_sinx(float_6p2832_eki_00008d00[0] * mario->directionView / float_360_eki_00008d04[0]));
                mario->unk174.z = (range - dist) * moa_cosx(float_6p2832_eki_00008d00[0] * mario->directionView / float_360_eki_00008d04[0]);
            } else {
                rad = float_6p2832_eki_00008d00[0] * angle / float_360_eki_00008d04[0];
                mario->unk174.x = pose->mtx[0][3] - range * moa_sin(rad) - mario->position.x;
                mario->unk174.z = pose->mtx[2][3] + range * moa_cos(rad) - mario->position.z;
            }
        }
    }
    return 0;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING  // restored C definition (nmrepair)
__declspec(section ".rodata") static Vec moamoa_zero_vec = {0.0f, 0.0f, 0.0f};
#endif
#ifdef NONMATCHING
static void ext_moamoa_main(void)
{
  const char *sfx;
  MarioWork *mario = marioGetPtr();
  PartyEntry *party = partyGetPtr(0);
  CameraEntry *cam = camGetPtr(CAMERA_3D);
  s32 sndFlag;
  s32 i;
  s32 ret;
  s32 idx;
  ExtPose *pose;
  ExtPose *other;
  Moamoa *moa;
  Moamoa *m;
  f32 rad;
  f32 angle;
  f32 z;
  f32 y;
  f32 x;
  f32 dist;
  f32 spd;
  f32 grav;
  f32 tx;
  f32 tz;
  f32 ty;
  Vec sp;
  Vec pv;
  Mtx rot;
  Mtx rot2;
  s32 hit;
  f32 a;
  f32 d;
  f32 t;
  f32 r;
  f32 s;
  hit = 0;
  if (mario->currMotionId == 0x12)
  {
    wp->field_0x40++;
  }
  else
  {
    wp->field_0x40 = 0;
  }
  if (mario->currMotionId == 0)
  {
    wp->idleFrames++;
    if (wp->idleFrames > 1000)
    {
      wp->idleFrames = 1000;
    }
  }
  else
  {
    wp->idleFrames = 0;
  }
  if (party->flags & 0x100)
  {
    wp->flags |= 0x10;
  }
  else
  {
    wp->flags &= ~0x10;
  }
  wp->breathDir = -1.0f;
  wp->breathDist = -1.0f;
  if ((party->currentMemberId == 5) && (party->flags & 0x100))
  {
    wp->breathDir = cloudGetBreathDir();
    wp->breathDist = cloudGetBreathDist();
    wp->breathPos.x = (wp->breathDist * moa_sinx((6.2831855f * wp->breathDir) / 360.0f)) + party->position.x;
    wp->breathPos.y = party->position.y;
    wp->breathPos.z = party->position.z - (wp->breathDist * moa_cosx((6.2831855f * wp->breathDir) / 360.0f));
  }
  if (wp->hitCount > 250)
  {
    s32 j;
    Moamoa *mm;
    extGetPosePtr();
    for (j = 0, mm = wp->moa; j < wp->count; j++, mm++)
    {
      if (mm->flags & 4)
      {
        continue;
      }
      if (mm->flags & 0x10)
      {
        break;
      }
      mm->state = 25;
      mm->timer = 0;
      mm->flags |= 0x10;
    }

    if (wp->escapeEvt == ((void *) 0))
    {
      wp->escapeEvt = evtEntry(evt_moamoa_escape, 0, 0);
    }
  }
  pose = extGetPosePtr();
  sndFlag = 0;
  moa = wp->moa;
  sfx = (char*)str_00000560;
  for (i = 0; i < wp->count; i++, pose++, moa++)
  {
    wp->angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
    wp->dist = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
    if ((((((wp->flags & 1) && (!(wp->flags & 4))) && (!marioKeyOffChk())) && (!marioCtrlOffChk())) && (!hit)) && (!(moa->flags & 0x154)))
    {
      ret = moamoa_hit_check(pose, moa);
      if (ret == 1)
      {
        moa->flags |= 4;
        moa->state = 36;
        wp->hitCount++;
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_00000050);
        hit = 1;
      }
      else
        if ((ret == 2) || (ret == 4))
      {
        moa->flags |= 0xc;
        moa->state = 47;
        wp->hitCount++;
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_00000050);
        if (ret != 4)
        {
          hit = 1;
        }
      }
      else
        if (ret == 3)
      {
        angle = wp->breathDir + wp->angle;
        angle *= 0.5f;
        moa->flags |= 0x84;
        moa->state = 48;
        moa->target = moamoa_zero_vec;
        spd = randf(0.1f, 0.2f);
        rad = (6.2831855f * angle) / 360.0f;
        moa->vy = spd * moa_sinx(rad);
        moa->speed = randf(0.03f, 0.06f);
        moa->gravity = spd * (-moa_cosx(rad));
        moa->jumpTimer = 120;
        wp->hitCount++;
        moamoa_pose_change(moa, (char*)str_00000040, (char*)str_00000050);
        hit = 1;
      }
    }
    if (((wp->flags & 1) && (!(moa->flags & 0x155))) && (wp->dist < 50.0f))
    {
      if (moa->flags & 2)
      {
        moa->next = 1;
      }
      else
      {
        moa->state = 1;
      }
    }
    if ((((wp->flags & 1) && (!(moa->flags & 0x444))) && (i == (gp->retraceCount % wp->count))) && (irand(1000) < 200))
    {
      sp = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
      psndSFXOn_3D(sfx, &sp);
    }
    switch (moa->state)
    {
      case 0:
        if ((i % 50) < 20)
      {
        f32 ax;
        f32 az;
        f32 ar;
        rad = randf(0.0f, 6.2831855f);
        dist = randf(0.0f, 50.0f);
        ax = wp->target[i % 3].x + (dist * moa_sinx(rad));
        az = wp->target[i % 3].z - (dist * moa_cosx(rad));
        ar = (6.2831855f * angleABf(pose->mtx[0][3], pose->mtx[2][3], ax, az)) / 360.0f;
        x = (15.0f * moa_sinx(ar)) + pose->mtx[0][3];
        y = pose->mtx[1][3];
        z = pose->mtx[2][3] - (15.0f * moa_cosx(ar));
        {
          f32 k1;
          f32 k2;
          f32 r1 = rand() / 32767.0f;
          f32 r2 = rand() / 32767.0f;
          moamoa_jump(pose, moa, moa->state, 1, x, y, z, (r1 * (k1 = 3.0f - 1.5f)) + 1.5f, (r2 * (k2 = 2.0f - 0.8f)) + 0.8f);
        }
        moa->flags |= 1;
        break;
      }
      {
        f32 d;
        f32 a;
        f32 r;
        d = distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
        a = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
        if (d < 100.0f)
        {
          a = randf(0.0f, 360.0f);
        }
        r = (6.2831855f * a) / 360.0f;
        x = (5.0f * moa_sinx(r)) + pose->mtx[0][3];
        y = pose->mtx[1][3];
        z = pose->mtx[2][3] - (5.0f * moa_cosx(r));
      }
      {
        f32 k1;
        f32 k2;
        f32 r1 = rand() / 32767.0f;
        f32 r2 = rand() / 32767.0f;
        moamoa_jump(pose, moa, moa->state, 1, x, y, z, (r1 * (k1 = 0.5f - 0.3f)) + 0.3f, (r2 * (k2 = 0.8f - 0.5f)) + 0.5f);
      }
        moa->flags &= ~1;
        break;

      case 50:
        if ((--moa->timer) < 0)
      {
        moa->timer = 0;
        moa->state++;
      }
        break;

      case 51:
        moa->speed = randf(0.0f, 200.0f);
        moa->gravity = randf(0.0f, (300.0f * moa->speed) / 200.0f);
        moa->state++;
        moa->timer = 0;

      case 52:
        s = (moa->timer < 200) ? (1.0f) : ((800 - moa->timer) / 600.0f);
        if (s < 0.0f)
      {
        s = 0.0f;
        moa->flags |= 0x200;
      }
        tx = wp->target[i % 3].x;
        ty = wp->target[i % 3].y;
        tz = wp->target[i % 3].z;
        tx += s * (moa->gravity * ((f32) sin(((f32) (i + gp->retraceCount)) * 0.25f)));
        r = i + gp->retraceCount;
        ty += moa->speed * s;
        tz += s * ((-moa->gravity) * ((f32) cos(r * 0.25f)));
        pose->mtx[0][3] += (tx - pose->mtx[0][3]) / 15.0f;
        pose->mtx[1][3] += (ty - pose->mtx[1][3]) / 15.0f;
        pose->mtx[2][3] += (tz - pose->mtx[2][3]) / 15.0f;
        moa->timer++;
        break;

      case 1:
      {
        f32 rad;
        {
          f32 a = wp->angle + randf(-45.0f, 45.0f);
          rad = 6.2831855f;
          rad = (rad * a) / 360.0f;
        }
        x = pose->mtx[0][3] + (15.0f * moa_sinx(rad));
        d = wp->dist;
        y = pose->mtx[1][3];
        z = pose->mtx[2][3] - (15.0f * moa_cosx(rad));
        moamoa_jump(pose, moa, (d < 100.0f) ? (moa->state) : (0), 1, x, y, z, randf(1.0f, 1.0f), randf(0.4f, 0.4f));
      }
        break;

      case 2:
      {
        f32 r = randf(-45.0f, 45.0f);
        a = wp->angle;
        a += r;
      }
        a += 180.0f;
        d = wp->dist;
      {
        f32 rad = (6.2831855f * a) / 360.0f;
        x = pose->mtx[0][3] + (30.0f * moa_sinx(rad));
      }
        y = pose->mtx[1][3];
        z = pose->mtx[2][3];
      {
        f32 a2 = randf(0.4f, 0.4f);
        spd = 2.0f * randf(1.0f, 1.0f);
        a2 *= 2.0f;
        moamoa_jump(pose, moa, (d < 100.0f) ? (moa->state) : (0), 1, x, y, z, spd, a2);
      }
        break;

      case 3:
        pose->mtx[1][3] += moa->vy;
        moa->vy -= moa->gravity;
      {
        f32 rad = (6.2831855f * angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z)) / 360.0f;
        pose->mtx[0][3] += moa->speed * moa_sinx(rad);
        pose->mtx[2][3] = pose->mtx[2][3] + (moa->speed * (-moa_cosx(rad)));
      }
        if ((--moa->jumpTimer) < 0)
      {
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
        if ((++moa->timer) > 4)
      {
        moa->state = moa->next;
      }
        break;

      case 36:

      case 37:

      case 38:
      {
        f32 tz;
        if (!(moa->flags & 1))
        {
          tx = mario->position.x;
          tz = mario->position.z;
        }
        else
        {
          tx = wp->target[i % 3].x;
          tz = wp->target[i % 3].z;
        }
        {
          f32 r1 = rand() / 32767.0f;
          f32 rad = (6.2831855f * (angleABf(tx, tz, pose->mtx[0][3], pose->mtx[2][3]) + ((r1 * (45.0f - (-45.0f))) + (-45.0f)))) / 360.0f;
          x = pose->mtx[0][3] + (15.0f * moa_sinx(rad));
          y = pose->mtx[1][3];
          z = pose->mtx[2][3] - (15.0f * moa_cosx(rad));
        }
        {
          f32 k;
          f32 r1 = rand() / 32767.0f;
          f32 r2 = rand() / 32767.0f;
          k = 1.0f - 1.0f;
          moamoa_jump(pose, moa, moa->state + 1, 1, x, y, z, (r1 * k) + 1.0f, (r2 * k) + 1.0f);
        }
      }
        break;

      case 39:
        if ((++moa->timer) < 30)
      {
        pose->mtx[0][0] *= 0.9f;
        pose->mtx[1][1] *= 0.9f;
        pose->mtx[2][2] *= 0.9f;
      }
      else
      {
        moa->state = 49;
      }
        break;

      case 47:
        angle = rand() / 32767.0f;
        dist = rand() / 32767.0f;
        rad = (6.2831855f * ((angle * (225.0f - 135.0f)) + 135.0f)) / 360.0f;
        dist = (dist * (500.0f - 200.0f)) + 200.0f;
        x = (dist * moa_sinx(rad)) + pose->mtx[0][3];
        z = pose->mtx[2][3] - (dist * moa_cosx(rad));
      {
        f32 k;
        f32 r1 = rand() / 32767.0f;
        spd = (r1 * (k = 6.0f - 5.0f)) + 5.0f;
      }
      {
        f32 k;
        f32 r1 = rand() / 32767.0f;
        s = (r1 * (k = 0.3f - 0.2f)) + 0.2f;
      }
        if (!sndFlag)
      {
        psndSFXOn_3D((const char *) 0x6c3, &((Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]}));
        sndFlag = 1;
      }
        dist = -100.0f;
        moamoa_jump(pose, moa, 49, 0, x, dist, z, spd, s);
        break;

      case 48:
        if ((--moa->jumpTimer) > 0)
      {
        moa->target.x += moa->vy;
        moa->target.y += moa->speed;
        moa->target.z += moa->gravity;
        pose->mtx[0][3] += moa->target.x;
        pose->mtx[1][3] += moa->target.y;
        pose->mtx[2][3] += moa->target.z;
      }
      else
      {
        moa->state = 49;
      }
        break;

      case 49:
        if ((wp->flags & 0x1000) && (wp->flags & 0x2000))
      {
        moa->state = 62;
        break;
      }
        if (wp->hitCount < 250)
      {
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = wp->target[i % 3].x;
        pose->mtx[1][3] = wp->target[i % 3].y;
        pose->mtx[2][3] = wp->target[i % 3].z;
        moa->flags = 0;
        moa->state = 0;
        moa->timer = 0;
      }
      else
      {
        moa->state = 62;
      }
        break;

      case 25:
        if (moa->timer < 30)
      {
        PSMTXRotRad(rot, 'y', 0.20943952f);
        PSMTXConcat(pose->mtx, rot, pose->mtx);
        pose->flags &= ~2;
        moa->timer++;
      }
      else
      {
        pose->flags |= 2;
        moa->timer = (100.0f - distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z)) * 0.5f;
        moa->state++;
      }
        break;

      case 26:
        if ((--moa->timer) < 0)
      {
        moa->state++;
      }
        break;

      case 27:
      {
        f32 rad;
        if ((__fabs(pose->mtx[0][3]) < 300.0) && (__fabs(pose->mtx[2][3]) < 300.0))
        {
          s = rand() / 32767.0f;
          rad = (6.2831855f * (angleABf(wp->target[i % 3].x, wp->target[i % 3].z, pose->mtx[0][3], pose->mtx[2][3]) + ((s * (45.0f - (-45.0f))) + (-45.0f)))) / 360.0f;
          x = (15.0f * moa_sinx(rad)) + pose->mtx[0][3];
          z = pose->mtx[2][3] - (15.0f * moa_cosx(rad));
          {
            f32 k;
            f32 r1 = rand() / 32767.0f;
            f32 r2 = rand() / 32767.0f;
            moamoa_jump(pose, moa, moa->state, 1, x, 0.0f, z, 3.0f * ((r1 * (k = 1.0f - 1.0f)) + 1.0f), (r2 * k) + 1.0f);
          }
        }
        else
        {
          moa->state = 62;
        }
      }
        break;

      case 62:
        moa->flags |= 0x20;
        pose->flags &= ~1;
        pose->flags |= 4;
        break;

      case 63:
      {
        f32 k;
        f32 r1 = rand() / 32767.0f;
        spd = randf(2.0f, 3.0f);
        moa->timer = irand(i / 2);
        rad = (6.2831855f * ((r1 * (k = 315.0f - 225.0f)) + 225.0f)) / 360.0f;
      }
        moa->target.x = spd * moa_sinx(rad);
        moa->target.y = randf(1.0f, 2.0f);
        moa->target.z = spd * (-moa_cosx(rad));
        moa->state++;
        break;

      case 64:
        if ((--moa->timer) < 0)
      {
        moa->state++;
      }
        break;

      case 65:
        moa->target.x *= 1.1f;
        moa->target.y *= 1.02f;
        moa->target.z *= 1.1f;
        pose->mtx[0][3] += moa->target.x;
        pose->mtx[1][3] += moa->target.y;
        pose->mtx[2][3] += moa->target.z;
        PSMTXRotRad(rot2, 'y', 0.20943952f);
        PSMTXConcat(pose->mtx, rot2, pose->mtx);
        pose->flags &= ~2;
        if (pose->mtx[0][3] < (-1000.0f))
      {
        moa->state = 62;
      }
        break;

    }

    if (!(moa->flags & 0x98))
    {
      if (pose->mtx[0][3] > 280.0f)
      {
        pose->mtx[0][3] = 280.0f;
      }
      if (pose->mtx[0][3] < (-120.0f))
      {
        pose->mtx[0][3] = -120.0f;
      }
      if (pose->mtx[2][3] > 70.0f)
      {
        pose->mtx[2][3] = 70.0f;
      }
      if (pose->mtx[2][3] < (-70.0f))
      {
        pose->mtx[2][3] = -70.0f;
      }
    }
    moa->lastX = pose->mtx[0][3];
    moa->lastZ = pose->mtx[2][3];
  }

  moamoa_pose_main();
  if (wp->flags & 0x10)
  {
    mario->unk174.x = 0.0f;
    mario->unk174.y = 0.0f;
    mario->unk174.z = 0.0f;
  }
  else
  {
    pv = (Vec){mario->unk174.x, mario->unk174.y, mario->unk174.z};
    if (PSVECMag(&pv) > 2.0f)
    {
      PSVECNormalize(&pv, &pv);
      mario->unk174.x = 2.0f * pv.x;
      mario->unk174.y = 2.0f * pv.y;
      mario->unk174.z = 2.0f * pv.z;
    }
  }
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#ifdef NONMATCHING
static void ext_moamoa_dispent(void) {
    if (wp->flags & 1) {
        dispEntry(CAMERA_3D, zero_eki_00008cf4[0], 1, ext_disp, NULL);
        dispEntry(CAMERA_3D, zero_eki_00008cf4[0], 2, ext_shadow_disp, NULL);
    }
    if (wp->flags & 2) {
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 1, ext_disp, NULL);
        dispEntry(CAMERA_OFFSCREEN2, -5000.0f, 2, ext_shadow_disp, NULL);
    }
}
#endif


__declspec(section ".data") static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00000170)), 0, LW(0), 0)
    RETURN
EVT_END()

__declspec(section ".data") static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING(((char*)str_00000170)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000178)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000184)), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.38867188f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000178)), 0, LW(0), 0)
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000184)), 0, LW(0), 0)
    RETURN
EVT_END()

static s32 bero_data[] = {
    (s32)((char*)str_00000190), 65539, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)((char*)str_00000198), (s32)((char*)str_000001A0), 327685, (s32)e_door_close, (s32)e_door_open, (s32)((char*)str_000001A8),
    65542, 20000, 100000, 0, 0, -1, 0, -1,
    0, (s32)((char*)str_000001B0), (s32)((char*)str_000001B8), 327685, (s32)s_door_close, (s32)s_door_open, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};

EVT_BEGIN(evt_bridge)
    CALL(evt_mario_key_onoff, 0)
    WAIT_MS(500)
    SET_VALUE(GSWF(3576), 1)
    CALL(evt_bero_mapchange, STRING(((char*)str_000001B0)), STRING(((char*)str_000001B8)))
    RETURN
EVT_END()

EVT_BEGIN(evt_bridge2)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001D0)), 1, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001E8)), 1, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000001F4)), 2, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001FC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000204)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000208)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000214)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000021C)), 1)
    CALL(evt_map_playanim, STRING(((char*)str_00000224)), 2, 0)
    CALL(evt_mario_set_pos, -210, 60, 0)
    CALL(evt_party_set_pos, 0, -230, 60, 0)
    CALL(evt_item_delete_check, STRING(((char*)str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_party_cont_onoff, 0, 1)
    CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000238)), 0, 0, -80)
    SET_VALUE(GF(0), 1)
    SET_VALUE(GSW(0), 325)
    SET_VALUE(GSWF(3576), 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_origami)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mapobj_get_position, STRING(((char*)str_00000238)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000240)), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, -800, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000238)), 0, 0, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_cam3d_evt_set, 340, 80, 280, -130, 90, -15, 1000, 11)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SUBTRACT(LW(0), 1)
    SUBTRACT(LW(2), 1)
    CALL(evt_mario_mov_pos, LW(0), LW(2), 30)
    WAIT_MS(500)
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000258)), -220, 60, 0, 0)
    CALL(evt_map_playanim, STRING(((char*)str_000001F4)), 0, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001FC)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000204)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000208)), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000214)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_00000274)), 1, 1)
    CALL(evt_map_checkanim, STRING(((char*)str_000001F4)), LW(0), LW(1))
    WAIT_MS(1600)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000021C)), 1)
    WAIT_MS(1000)
    CALL(evt_mobj_switch_blue, 0, STRING(((char*)str_00000280)), -220, 60, 0, PTR(evt_bridge), GSWF(3725))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000028C)), -220, 60, 0, 0)
    CALL(evt_mobj_set_scale, STRING(((char*)str_00000280)), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
    CALL(evt_sub_intpl_msec_init, 8, 100, 1000, 1000)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    DIVIDE_FLOAT(LW(0), FLOAT(1000.0f))
    CALL(evt_mobj_set_scale, STRING(((char*)str_00000280)), LW(0), LW(0), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    SET_VALUE(GSW(0), 324)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(evt_moamoa_init)
    CALL(evt_npc_entry, STRING(((char*)str_000002A8)), STRING(((char*)str_00000040)))
    CALL(evt_npc_set_position, STRING(((char*)str_000002A8)), 0, -1000, 0)
    CALL(evt_npc_entry, STRING(((char*)str_000002B0)), STRING(((char*)str_00000054)))
    CALL(evt_npc_set_position, STRING(((char*)str_000002B0)), 0, -1000, 0)
    CALL(evt_ext_entry, 150, PTR(ext_moamoa_data), PTR(ext_moamoa_init), PTR(ext_moamoa_main), PTR(ext_moamoa_dispent))
    RETURN
EVT_END()

static EVT_BEGIN(evt_meet_moamoa)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING(((char*)str_000002B8)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING(((char*)str_000002D0)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING(((char*)str_000002E0)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING(((char*)str_000002F0)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000300)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000310)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000320)), 0, STRING(((char*)str_000002C8)))
    END_SWITCH
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, 1024)
        CALL(evt_snd_bgmon, 1, STRING(((char*)str_00000330)))
        WAIT_MS(2000)
        CALL(evt_snd_bgmoff, 513)
        CALL(evt_snd_bgmon, 288, 0)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, 32, 151, 528, 32, 56, -12, 500, 11)
    WAIT_MS(2000)
    CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000348)))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_dispflag_onoff, 1, 2)
        WAIT_MS(1000)
        CALL(evt_mario_set_pose, STRING(((char*)str_00000358)))
    END_INLINE_EVENT
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000360)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000370)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000380)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(5)
        CALL(evt_msg_print, 0, STRING(((char*)str_00000390)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(6)
        CALL(evt_msg_print, 0, STRING(((char*)str_000003A0)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING(((char*)str_000003B0)), 0, STRING(((char*)str_000002C8)))
        CASE_EQUAL(7)
        CALL(evt_msg_print, 0, STRING(((char*)str_000003C0)), 0, STRING(((char*)str_000002C8)))
    END_SWITCH
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    SET_VALUE(GSW(0), 322)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_party_run, 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_moamoa_escape)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, 0, 151, 528, 0, 56, -12, 500, 11)
    CALL(evt_snd_bgmoff_f, 512, 180)
    BEGIN_INLINE_EVENT
        CALL(evt_moamoa_end_wait)
        CALL(evt_moamoa_exit)
    END_INLINE_EVENT
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_000003D0)), 0, PTR(evt_origami), GW(10))
    SET_VALUE(GSW(0), 323)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

s32 img_set_color(EventEntry* event, BOOL isFirstCall);

#ifdef NONMATCHING
s32 img_set_color(EventEntry* event, BOOL isFirstCall) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 r = evtGetValue(event, args[1]);
    u8 g = evtGetValue(event, args[2]);
    u8 b = evtGetValue(event, args[3]);
    u8 a = evtGetValue(event, args[4]);
    ImageEntry* img = imgNameToPtr(name, gp->inBattle != 0);
    animPoseSetMaterialFlagOn(img->poseId, 0x40);
    animPoseSetMaterialEvtColor(img->poseId, (GXColor){r, g, b, a});
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(evt_elv_rumble)
    IF_INT_EQUAL(GF(0), 0)
        CALL(evt_map_checkanim, STRING(((char*)str_00000224)), LW(0), LW(1))
        ELSE
        CALL(evt_map_checkanim, STRING(((char*)str_000003DC)), LW(0), LW(1))
    END_IF
    SUBTRACT(LW(1), 500)
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000003E8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0048828125f), 250)
    WAIT_MS(LW(1))
    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_000003E8)), LW(3), LW(4), LW(5), 0)
    CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.0048828125f), 250)
    RETURN
EVT_END()

static EVT_BEGIN(evt_elv_init)
    CALL(evt_paper_entry, STRING(((char*)str_00000404)))
    CALL(evt_img_entry, STRING(((char*)str_00000410)))
    CALL(evt_img_set_paper, STRING(((char*)str_00000410)), STRING(((char*)str_00000404)))
    CALL(evt_offscreen_entry, STRING(((char*)str_0000041C)))
    CALL(evt_img_set_paper_anim, STRING(((char*)str_00000410)), STRING(((char*)str_00000428)))
    CALL(evt_img_alloc_capture, STRING(((char*)str_00000410)), 0, STRING(((char*)str_0000041C)), 0, 0, 0, 608, 480)
    CALL(evt_img_alloc_capture, STRING(((char*)str_00000410)), 2, STRING(((char*)str_0000041C)), 0, 0, 0, 608, 480)
    CALL(evt_img_clear_virtual_point, STRING(((char*)str_00000410)))
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 0)
    SET_VALUE(GF(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_elv_down)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000448)), 0, 0)
    WAIT_FRAMES(20)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT(60.0f))
    CALL(evt_map_checkanim, STRING(((char*)str_00000448)), LW(0), LW(1))
    ADD(LW(1), 1)
    WAIT_MS(LW(1))
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, 190, -65, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
        CALL(evt_party_jump_pos, 0, 160, 0, -160, 500, 0, -1000)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 90, 200)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 190, -160, FLOAT(60.0f))
    CALL(evt_mario_set_dir, 270, 200, 0)
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)str_000001DC)), STRING(((char*)str_0000041C)))
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)str_000001C4)))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001DC)), 1)
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)str_00000474)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000484)), LW(0), LW(1), LW(2), LW(10))
        CALL(evt_map_checkanim, STRING(((char*)str_00000224)), LW(0), LW(1))
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000224)), 0, 0)
    SPAWN_EVENT(PTR(evt_elv_rumble))
    CALL(evt_map_checkanim, STRING(((char*)str_00000224)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000049C)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(400)
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)str_000001DC)))
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)str_000001C4)), STRING(((char*)str_0000041C)))
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 1)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 1)
        CALL(evt_moamoa_flag_onoff, 1, 2)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000448)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)str_00000448)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 0)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 1, 1)
        CALL(evt_moamoa_flag_onoff, 0, 2)
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001D0)), 1, 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001E8)), 1, 0)
    SWITCH(GSW(0))
        CASE_LESS(323)
        CASE_EQUAL(323)
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_000003D0)), 0, PTR(evt_origami), GW(10))
        CASE_DEFAULT
        CALL(evt_mapobj_rotate, 1, STRING(((char*)str_00000238)), 0, 0, -80)
    END_SWITCH
    IF_INT_EQUAL(GSW(0), 324)
        CALL(evt_mobj_switch_blue, 0, STRING(((char*)str_00000280)), -220, 60, 0, PTR(evt_bridge), GSWF(3725))
    END_IF
    CALL(evt_item_delete_check, STRING(((char*)str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
        SUBTRACT(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    IF_INT_LESS(GSW(0), 324)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001FC)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000204)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000208)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000214)), 1)
        CALL(evt_hitobj_onoff, STRING(((char*)str_00000274)), 1, 0)
        ELSE
        CALL(evt_map_playanim, STRING(((char*)str_000001F4)), 2, 0)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001FC)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_00000204)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000208)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_00000214)), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_0000021C)), 1)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_party_stop, 0)
        WAIT_MS(100)
        CALL(evt_party_move_pos2, 0, 190, -65, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
        WAIT_MS(100)
        CALL(evt_party_move_pos2, 0, 150, -65, FLOAT(60.0f))
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT(60.0f))
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000474)), 0, 0)
    WAIT_MS(500)
    IF_INT_LESS(GSW(0), 322)
        CALL_CHILD(PTR(evt_meet_moamoa))
    END_IF
    IF_INT_EQUAL(GSW(0), 322)
        CALL(evt_snd_bgmon, 512, STRING(((char*)str_00000348)))
    END_IF
    CALL(evt_map_checkanim, STRING(((char*)str_00000474)), LW(0), LW(1))
    WAIT_MS(LW(1))
    RETURN
EVT_END()

EVT_BEGIN(evt_elv_up)
    CALL(evt_snd_bgmoff, 512)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000448)), 0, 0)
    WAIT_FRAMES(20)
    CALL(evt_mario_mov_pos2, 190, -65, FLOAT(60.0f))
    CALL(evt_map_checkanim, STRING(((char*)str_00000448)), LW(0), LW(1))
    ADD(LW(1), 1)
    WAIT_MS(LW(1))
    BEGIN_INLINE_EVENT
        CALL(evt_hitobj_onoff, STRING(((char*)str_000004B4)), 0, 0)
        CALL(evt_party_move_pos, 0, 190, -65, 500)
        CALL(evt_party_stop, 0)
        CALL(evt_party_move_pos, 0, 160, -160, 500)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir, 0, 90, 0)
        CALL(evt_hitobj_onoff, STRING(((char*)str_000004B4)), 0, 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos, 190, -160, 500)
    CALL(evt_mario_set_dir, 270, 0, 0)
    WAIT_MS(500)
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)str_000001DC)))
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)str_000001C4)), STRING(((char*)str_0000041C)))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001C4)), 1)
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 1)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 1)
        CALL(evt_moamoa_flag_onoff, 1, 2)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)str_00000474)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 0)
    IF_INT_LESS(GSW(0), 323)
        CALL(evt_moamoa_flag_onoff, 0, 2)
    END_IF
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000484)), LW(0), LW(1), LW(2), LW(10))
        CALL(evt_map_checkanim, STRING(((char*)str_000003DC)), LW(0), LW(1))
        WAIT_MS(LW(1))
        CALL(evt_snd_sfxoff, LW(10))
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_000003DC)), 0, 0)
    SPAWN_EVENT(PTR(evt_elv_rumble))
    CALL(evt_map_checkanim, STRING(((char*)str_000003DC)), LW(0), LW(1))
    WAIT_MS(LW(1))
    CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING(((char*)str_0000049C)), LW(0), LW(1), LW(2), 0)
    WAIT_MS(400)
    CALL(evt_mapobj_set_offscreen, 1, STRING(((char*)str_000001DC)), STRING(((char*)str_0000041C)))
    CALL(evt_mapobj_clear_offscreen, 1, STRING(((char*)str_000001C4)))
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000430)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000448)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)str_00000448)), LW(0), LW(2))
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, LW(2))
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(img_set_color, STRING(((char*)str_00000410)), 255, 255, 255, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_img_onoff, STRING(((char*)str_00000410)), 0)
    IF_INT_LESS(GSW(0), 324)
    END_IF
    IF_INT_EQUAL(GSW(0), 324)
        CALL(evt_mobj_delete, STRING(((char*)str_00000280)))
    END_IF
    CALL(evt_item_delete_check, STRING(((char*)str_00000230)), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_item_get_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
        ADD(LW(1), 2000)
        CALL(evt_item_set_position, STRING(((char*)str_00000230)), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001D0)), 1, 0)
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING(((char*)str_000001DC)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001E8)), 1, 1)
    IF_INT_EQUAL(GSW(0), 323)
        CALL(evt_del_case_evt, 0, GW(10))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_party_jump_pos, 0, 190, 0, -65, 500, 0, -1000)
        CALL(evt_party_stop, 0)
        CALL(evt_party_move_pos, 0, 150, -65, 1000)
        CALL(evt_party_stop, 0)
    END_INLINE_EVENT
    WAIT_FRAMES(30)
    CALL(evt_mario_mov_pos, 190, -65, 500)
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, STRING(((char*)str_0000042C)), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
        WAIT_MS(1000)
        CALL(evt_snd_sfxon_3d, STRING(((char*)str_00000458)), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_map_playanim, STRING(((char*)str_00000474)), 0, 0)
    CALL(evt_map_checkanim, STRING(((char*)str_00000474)), LW(0), LW(1))
    WAIT_MS(LW(1))
    RETURN
EVT_END()

__declspec(section ".data") static s32 item_tbl[] = {
    26, -1,
};

EVT_BEGIN(evt_elv)
    CALL(evt_mario_key_onoff, 0)
    IF_INT_LESS(GSW(0), 321)
        CALL(evt_win_item_select, 0, PTR(item_tbl), LW(1), 0)
        IF_INT_EQUAL(LW(1), -1)
            CALL(evt_mario_key_onoff, 1)
            RETURN
        END_IF
        CALL(evt_pouch_remove_item, 26, LW(0))
        SET_VALUE(GSW(0), 321)
        CALL(evt_snd_sfxon, STRING(((char*)str_000004BC)), 0)
        CALL(evt_msg_print, 0, STRING(((char*)str_000004D4)), 0, 0)
    END_IF
    IF_INT_EQUAL(GF(0), 0)
        CALL_CHILD(PTR(evt_elv_down))
        SET_VALUE(GF(0), 1)
        ELSE
        CALL_CHILD(PTR(evt_elv_up))
        SET_VALUE(GF(0), 0)
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_elv_nomsg)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_000004E0)), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_head)
    CALL(evt_item_delete, STRING(((char*)str_00000230)))
    CALL(evt_item_entry, STRING(((char*)str_00000230)), 300, -260, 160, -60, 4, GSWF(3745), 0)
    CALL(evt_item_set_move_dir_speed, STRING(((char*)str_00000230)), FLOAT(135.0f), FLOAT(90.0f))
    CALL(evt_item_set_gravity, STRING(((char*)str_00000230)), FLOAT(1.0f))
    CALL(evt_item_set_bound_rate, STRING(((char*)str_00000230)), FLOAT(0.5996094f))
    CALL(evt_item_set_jump_power, STRING(((char*)str_00000230)), FLOAT(500.0f))
    CALL(evt_item_status_on, STRING(((char*)str_00000230)), 16)
    CALL(evt_item_flag_on, STRING(((char*)str_00000230)), 2048)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

static EVT_BEGIN(evt_kanban)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING(((char*)str_000004EC)), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(eki_00_init_evt)
    SET_VALUE(LW(0), PTR(bero_data))
    CALL(evt_bero_get_info)
    IF_INT_EQUAL(GSWF(3576), 0)
        CALL_CHILD(PTR(evt_bero_info_run))
        ELSE
        CALL_CHILD(PTR(bero_case_entry))
    END_IF
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING(((char*)str_000001C4)), 1)
    CALL(evt_hitobj_onoff, STRING(((char*)str_000001D0)), 1, 0)
    IF_INT_GREATER_OR_EQUAL(GSW(0), 320)
        CALL_CHILD(PTR(evt_elv_init))
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_000004FC)), 0, PTR(evt_elv), 0)
        ELSE
        CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_000004FC)), 0, PTR(evt_elv_nomsg), 0)
    END_IF
    IF_INT_LESS(GSW(0), 323)
        CALL_CHILD(PTR(evt_moamoa_init))
    END_IF
    CALL(evt_item_entry, STRING(((char*)str_00000230)), 300, -260, 130, -60, 17, GSWF(3745), 0)
    IF_INT_EQUAL(GSWF(3745), 0)
        CALL(evt_run_case_evt, 16, 1, STRING(((char*)str_00000508)), 0, PTR(evt_head), 0)
    END_IF
    CALL(evt_snd_bgmoff, 512)
    CALL(evt_snd_envon, 272, STRING(((char*)str_00000514)))
    IF_INT_EQUAL(GSWF(3576), 1)
        SPAWN_EVENT(PTR(evt_bridge2))
    END_IF
    CALL(evt_run_case_evt, 9, 1, STRING(((char*)str_00000524)), 0, PTR(evt_kanban), 0)
    RETURN
EVT_END()

#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): moamoa_pose_init (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
void jt_00000FEC(void);
void jt_00001A6C(void);
void jt_00001D64(void);
void jt_00001FC8(void);
void jt_00002224(void);
void jt_000031F4(void);
void jt_00002A40(void);
void jt_00002B0C(void);
void jt_00002B30(void);
void jt_00002248(void);
void jt_0000254C(void);
void jt_000025AC(void);
void jt_000028FC(void);
void jt_0000298C(void);
void jt_000017D4(void);
void jt_00001800(void);
void jt_000018C8(void);
void jt_00002E50(void);
void jt_00002E78(void);
void jt_00003104(void);
void jt_00003128(void);
__declspec(section ".data") void* jumptable_00002400[66] = {jt_00000FEC, jt_00001A6C, jt_00001D64, jt_00001FC8, jt_00002224, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_00002A40, jt_00002B0C, jt_00002B30, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_00002248, jt_00002248, jt_00002248, jt_0000254C, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000025AC, jt_000028FC, jt_0000298C, jt_000017D4, jt_00001800, jt_000018C8, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_000031F4, jt_00002E50, jt_00002E78, jt_00003104, jt_00003128};
#pragma force_active on
__declspec(section ".rodata") const char str_00000040[] = "c_n_moa_a\000\000";
__declspec(section ".rodata") const char str_0000004C[] = "S_1";
__declspec(section ".rodata") const char str_00000050[] = "D_1";
__declspec(section ".rodata") const char str_00000054[] = "c_n_moa_b\000\000";
__declspec(section ".rodata") const char str_00000060[] = "c_kinodebu\000";
__declspec(section ".rodata") const char str_0000006C[] = "G_1";
__declspec(section ".rodata") const char str_00000070[] = "c_puku_c\000\000\000";
__declspec(section ".rodata") const char str_0000007C[] = "U_1";
__declspec(section ".rodata") const char str_00000080[] = "c_powan";
__declspec(section ".rodata") const char str_00000088[] = "O_1";
__declspec(section ".rodata") const char str_0000008C[] = "c_smoko";
__declspec(section ".rodata") const char str_00000094[] = "T_2";
__declspec(section ".rodata") const char str_00000098[] = "c_rose\000";
__declspec(section ".rodata") const char str_000000A0[] = "c_papab";
__declspec(section ".rodata") const char str_000000A8[] = "c_mamab";
__declspec(section ".rodata") const char str_000000B0[] = "c_konari\000\000\000";
__declspec(section ".rodata") const f32 vec3_eki_00008884[3] = { 0.0f, 0.0f, 10.0f };
__declspec(section ".rodata") const f32 vec3_eki_00008890[3] = { 0.0f, 0.0f, 10.0f };
__declspec(section ".rodata") const f32 vec3_eki_0000889c[3] = { 0.0f, 0.0f, 10.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088a8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088b4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088c0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088d8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088e4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088f0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_000088fc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_00008908[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_00008914[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_00008920[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_eki_0000892c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const char str_00000170[] = "e_door\000";
__declspec(section ".rodata") const char str_00000178[] = "s_door_a\000\000\000";
__declspec(section ".rodata") const char str_00000184[] = "s_door_b\000\000\000";
__declspec(section ".rodata") const char str_00000190[] = "e_bero\000";
__declspec(section ".rodata") const char str_00000198[] = "eki_01\000";
__declspec(section ".rodata") const char str_000001A0[] = "w_dero\000";
__declspec(section ".rodata") const char str_000001A8[] = "s_bero\000";
__declspec(section ".rodata") const char str_000001B0[] = "hom_00\000";
__declspec(section ".rodata") const char str_000001B8[] = "n_bero_2\000\000\000";
__declspec(section ".rodata") const char str_000001C4[] = "s_eki_07\000\000\000";
__declspec(section ".rodata") const char str_000001D0[] = "a_eki_07\000\000\000";
__declspec(section ".rodata") const char str_000001DC[] = "s_eki_00\000\000\000";
__declspec(section ".rodata") const char str_000001E8[] = "a_eki_00\000\000\000";
__declspec(section ".rodata") const char str_000001F4[] = "anm_ori";
__declspec(section ".rodata") const char str_000001FC[] = "kaidann";
__declspec(section ".rodata") const char str_00000204[] = "ori";
__declspec(section ".rodata") const char str_00000208[] = "n_kaidan\000\000\000";
__declspec(section ".rodata") const char str_00000214[] = "n_ori\000\000";
__declspec(section ".rodata") const char str_0000021C[] = "n_kabe\000";
__declspec(section ".rodata") const char str_00000224[] = "anm_ere_1\000\000";
__declspec(section ".rodata") const char str_00000230[] = "item\000\000\000";
__declspec(section ".rodata") const char str_00000238[] = "s_lever";
__declspec(section ".rodata") const char str_00000240[] = "SFX_STG6_SWITCH_MOVE1\000\000";
__declspec(section ".rodata") const char str_00000258[] = "SFX_STG6_ORIGAMI_APPEAR1\000\000\000";
__declspec(section ".rodata") const char str_00000274[] = "kaidann_A\000\000";
__declspec(section ".rodata") const char str_00000280[] = "bridge_sw\000\000";
__declspec(section ".rodata") const char str_0000028C[] = "SFX_STG6_OBJ_SWITCH_APPEAR1";
__declspec(section ".rodata") const char str_000002A8[] = "moa_a\000\000";
__declspec(section ".rodata") const char str_000002B0[] = "moa_b\000\000";
__declspec(section ".rodata") const char str_000002B8[] = "stg6_eki_02_0\000\000";
__declspec(section ".rodata") const char str_000002C8[] = "party\000\000";
__declspec(section ".rodata") const char str_000002D0[] = "stg6_eki_02_1\000\000";
__declspec(section ".rodata") const char str_000002E0[] = "stg6_eki_02_2\000\000";
__declspec(section ".rodata") const char str_000002F0[] = "stg6_eki_02_3\000\000";
__declspec(section ".rodata") const char str_00000300[] = "stg6_eki_02_4\000\000";
__declspec(section ".rodata") const char str_00000310[] = "stg6_eki_02_5\000\000";
__declspec(section ".rodata") const char str_00000320[] = "stg6_eki_02_6\000\000";
__declspec(section ".rodata") const char str_00000330[] = "BGM_FF_ENV_SURPRISED1\000\000";
__declspec(section ".rodata") const char str_00000348[] = "BGM_EVT_DANGER4";
__declspec(section ".rodata") const char str_00000358[] = "M_N_2\000\000";
__declspec(section ".rodata") const char str_00000360[] = "stg6_eki_03_0\000\000";
__declspec(section ".rodata") const char str_00000370[] = "stg6_eki_03_1\000\000";
__declspec(section ".rodata") const char str_00000380[] = "stg6_eki_03_2\000\000";
__declspec(section ".rodata") const char str_00000390[] = "stg6_eki_03_3\000\000";
__declspec(section ".rodata") const char str_000003A0[] = "stg6_eki_03_4\000\000";
__declspec(section ".rodata") const char str_000003B0[] = "stg6_eki_03_5\000\000";
__declspec(section ".rodata") const char str_000003C0[] = "stg6_eki_03_6\000\000";
__declspec(section ".rodata") const char str_000003D0[] = "a_lever";
__declspec(section ".rodata") const u32 zero_eki_00008ba0[1] = { 0x00000000 };
__declspec(section ".rodata") const char str_000003DC[] = "anm_ere_2\000\000";
__declspec(section ".rodata") const char str_000003E8[] = "SFX_STG6_ELEVATOR_SHAKE1\000\000\000";
__declspec(section ".rodata") const char str_00000404[] = "OFF_hei_07\000";
__declspec(section ".rodata") const char str_00000410[] = "capture_img";
__declspec(section ".rodata") const char str_0000041C[] = "offscreen\000\000";
__declspec(section ".rodata") const char str_00000428[] = "Z_1";
__declspec(section ".rodata") const char str_0000042C[] = "d_1";
__declspec(section ".rodata") const char str_00000430[] = "SFX_STG6_ELEVATOR_OPEN1";
__declspec(section ".rodata") const char str_00000448[] = "anm_ere_door_1\000";
__declspec(section ".rodata") const char str_00000458[] = "SFX_STG6_ELEVATOR_CLOSE1\000\000\000";
__declspec(section ".rodata") const char str_00000474[] = "anm_ere_door_2\000";
__declspec(section ".rodata") const char str_00000484[] = "SFX_STG6_ELEVATOR_MOVE1";
__declspec(section ".rodata") const char str_0000049C[] = "SFX_STG6_ELEVATOR_BELL1";
__declspec(section ".rodata") const char str_000004B4[] = "ere__A\000";
__declspec(section ".rodata") const char str_000004BC[] = "SFX_STG6_ELEVATOR_KEY1\000";
__declspec(section ".rodata") const char str_000004D4[] = "stg6_eki_07";
__declspec(section ".rodata") const char str_000004E0[] = "stg6_eki_06";
__declspec(section ".rodata") const char str_000004EC[] = "stg6_eki_00_01\000";
__declspec(section ".rodata") const char str_000004FC[] = "a_suitti\000\000\000";
__declspec(section ".rodata") const char str_00000508[] = "a_dai_sita\000";
__declspec(section ".rodata") const char str_00000514[] = "ENV_STG6_EKI2\000\000";
__declspec(section ".rodata") const char str_00000524[] = "a_kan\000\000";
__declspec(section ".rodata") const f32 zero_eki_00008cf4[1] = { 0.0f };
__declspec(section ".rodata") const f32 float_neg5000_eki_00008cf8[1] = { -5000.0f };
__declspec(section ".rodata") const f32 float_neg1_eki_00008cfc[1] = { -1.0f };
__declspec(section ".rodata") const f32 float_6p2832_eki_00008d00[1] = { 6.2831855f };
__declspec(section ".rodata") const f32 float_360_eki_00008d04[1] = { 360.0f };
__declspec(section ".rodata") const f32 float_0p00761_eki_00008d08[1] = { 0.00761f };
__declspec(section ".rodata") const f32 float_0p16605_eki_00008d0c[1] = { 0.16605f };
__declspec(section ".rodata") const f32 float_1_eki_00008d10[1] = { 1.0f };
__declspec(section ".rodata") const f32 float_3p1416_eki_00008d14[1] = { 3.1415927f };
__declspec(section ".rodata") const f32 float_1p5708_eki_00008d18[1] = { 1.5707964f };
__declspec(section ".rodata") const f32 float_4p7124_eki_00008d1c[1] = { 4.712389f };
__declspec(section ".rodata") const f32 float_0p03705_eki_00008d20[1] = { 0.03705f };
__declspec(section ".rodata") const f32 float_0p4967_eki_00008d24[1] = { 0.4967f };
__declspec(section ".rodata") const char str_00000560[] = "SFX_STG6_MOAMOA_VOICE1\000";
__declspec(section ".rodata") const char str_00000578[] = "S_2";
__declspec(section ".rodata") const char str_0000057C[] = "D\000\000";
__declspec(section ".rodata") const char str_00000580[] = "R\000\000";
__declspec(section ".rodata") const f32 float_0p5_eki_00008d4c[1] = { 0.5f };
__declspec(section ".rodata") const f32 float_32767_eki_00008d50[1] = { 32767.0f };
__declspec(section ".rodata") const f32 float_0p1_eki_00008d54[1] = { 0.1f };
__declspec(section ".rodata") const f32 float_0p03_eki_00008d58[1] = { 0.03f };
__declspec(section ".rodata") const f32 float_50_eki_00008d5c[1] = { 50.0f };
__declspec(section ".rodata") const f32 float_15_eki_00008d60[1] = { 15.0f };
__declspec(section ".rodata") const f32 float_1p5_eki_00008d64[1] = { 1.5f };
__declspec(section ".rodata") const f32 float_0p8_eki_00008d68[1] = { 0.8f };
__declspec(section ".rodata") const f32 float_1p2_eki_00008d6c[1] = { 1.2f };
__declspec(section ".rodata") const f32 float_100_eki_00008d70[1] = { 100.0f };
__declspec(section ".rodata") const f32 float_5_eki_00008d74[1] = { 5.0f };
__declspec(section ".rodata") const f32 float_0p3_eki_00008d78[1] = { 0.3f };
__declspec(section ".rodata") const f32 float_0p2_eki_00008d7c[1] = { 0.19999999f };
__declspec(section ".rodata") const f32 float_200_eki_00008d80[1] = { 200.0f };
__declspec(section ".rodata") const f32 float_300_eki_00008d84[1] = { 300.0f };
__declspec(section ".rodata") const f32 float_600_eki_00008d88[1] = { 600.0f };
__declspec(section ".rodata") const f32 float_0p25_eki_00008d8c[1] = { 0.25f };
__declspec(section ".rodata") const f32 float_neg45_eki_00008d90[1] = { -45.0f };
__declspec(section ".rodata") const f32 float_90_eki_00008d94[1] = { 90.0f };
__declspec(section ".rodata") const f32 float_0p4_eki_00008d98[1] = { 0.4f };
__declspec(section ".rodata") const f32 float_180_eki_00008d9c[1] = { 180.0f };
__declspec(section ".rodata") const f32 float_30_eki_00008da0[1] = { 30.0f };
__declspec(section ".rodata") const f32 float_2_eki_00008da4[1] = { 2.0f };
__declspec(section ".rodata") const f32 float_0p9_eki_00008da8[1] = { 0.9f };
__declspec(section ".rodata") const f32 float_135_eki_00008dac[1] = { 135.0f };
__declspec(section ".rodata") const f32 float_0p2_eki_00008db0[1] = { 0.2f };
__declspec(section ".rodata") const f32 float_0p1_eki_00008db4[1] = { 0.10000001f };
__declspec(section ".rodata") const f32 float_neg100_eki_00008db8[1] = { -100.0f };
__declspec(section ".rodata") const f32 float_0p20944_eki_00008dbc[1] = { 0.20943952f };
__declspec(section ".rodata") const f64 double_300_eki_00008dc0 = 300;
__declspec(section ".rodata") const f32 float_3_eki_00008dc8[1] = { 3.0f };
__declspec(section ".rodata") const f32 float_225_eki_00008dcc[1] = { 225.0f };
__declspec(section ".rodata") const f32 float_1p1_eki_00008dd0[1] = { 1.1f };
__declspec(section ".rodata") const f32 float_1p02_eki_00008dd4[1] = { 1.02f };
__declspec(section ".rodata") const f32 float_neg1000_eki_00008dd8[1] = { -1000.0f };
__declspec(section ".rodata") const f32 float_280_eki_00008ddc[1] = { 280.0f };
__declspec(section ".rodata") const f32 float_neg120_eki_00008de0[1] = { -120.0f };
__declspec(section ".rodata") const f32 float_70_eki_00008de4[1] = { 70.0f };
__declspec(section ".rodata") const f32 float_neg70_eki_00008de8[1] = { -70.0f };
__declspec(section ".rodata") const f32 float_60_eki_00008dec[1] = { 60.0f };
__declspec(section ".rodata") const f32 float_1000_eki_00008df0[1] = { 1000.0f };
__declspec(section ".rodata") const f64 double_to_int_eki_00008df8 = 4503601774854144;
__declspec(section ".rodata") const f64 double_to_int_mask_eki_00008e00 = 4503599627370496;
__declspec(section ".rodata") const f32 float_20_eki_00008e08[1] = { 20.0f };
__declspec(section ".rodata") const f32 float_10_eki_00008e0c[1] = { 10.0f };
__declspec(section ".rodata") const f32 float_35_eki_00008e10[1] = { 35.0f };
__declspec(section ".rodata") const f32 float_65_eki_00008e14[1] = { 65.0f };
__declspec(section ".rodata") const f32 float_40_eki_00008e18[1] = { 40.0f };
__declspec(section ".rodata") const f32 float_1E06_eki_00008e1c[1] = { 1000000.0f };
__declspec(section ".rodata") const f64 double_30_eki_00008e20 = 30;
__declspec(section ".rodata") const char zero_eki_00008e28[4] = {0};
__declspec(section ".rodata") const char str_00000664[] = "J\000\000";
#pragma force_active reset
s32 img_set_color(EventEntry* event, BOOL isFirstCall);
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
void animPoseSetMaterialEvtColor(s32 poseId, GXColor color);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
CameraEntry* camGetPtr(CameraId cameraId);
f32 cloudGetBreathDir(void);
f32 compAngle(f32 angle1, f32 angle2);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
s32 evtGetValue(EventEntry* entry, s32 index);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
ImageEntry* imgNameToPtr(const char* name, s32 type);
s32 irand(s32 scalar);
void marioChgMot(MarioMotion);
s32 marioCtrlOffChk(void);
MarioWork* marioGetPtr(void);
s32 marioKeyOffChk(void);
void *memset(void *dest, int ch, size_t count);
void offscreenAddBoundingBox(s32 id, u16 left, u16 top, u16 right, u16 bottom);
s32 offscreenNameToId(const char* name);
PartyEntry* partyGetPtr(s32 index);
s32 psndSFXOn_3D(const char* name, Vec* position);
f32 reviseAngle(f32 angle);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
int strncmp(const char *s1, const char *s2, size_t n);
void sysWaitDrawSync(void);
asm s32 img_set_color(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r26, 0x18(r1)
	mr r26, r3
	lwz r31, 0x18(r3)
	lwz r4, 0x0(r31)
	bl evtGetValue
	lwz r4, 0x4(r31)
	mr r30, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x8(r31)
	clrlwi r29, r3, 24
	mr r3, r26
	bl evtGetValue
	lwz r4, 0xc(r31)
	clrlwi r28, r3, 24
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x10(r31)
	clrlwi r27, r3, 24
	mr r3, r26
	bl evtGetValue
	lis r4, gp@ha
	clrlwi r26, r3, 24
	addi r4, r4, gp@l
	mr r3, r30
	lwz r4, 0x0(r4)
	lwz r4, 0x14(r4)
	subic r0, r4, 0x1
	subfe r4, r0, r4
	bl imgNameToPtr
	mr r31, r3
	li r4, 0x40
	lwz r3, 0x104(r3)
	bl animPoseSetMaterialFlagOn
	lis r3, zero_eki_00008ba0@ha
	addi r4, r1, 0xc
	lwz r0, zero_eki_00008ba0@l(r3)
	stw r0, 0x8(r1)
	stb r29, 0x8(r1)
	stb r28, 0x9(r1)
	stb r27, 0xa(r1)
	stb r26, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	lmw r26, 0x18(r1)
	li r3, 0x2
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
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
	lis r3, zero_eki_00008cf4@ha
	lis r4, ext_disp@ha
	addi r6, r3, zero_eki_00008cf4@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x4
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, zero_eki_00008cf4@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, zero_eki_00008cf4@l
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
	lis r3, float_neg5000_eki_00008cf8@ha
	lis r4, ext_disp@ha
	addi r6, r3, float_neg5000_eki_00008cf8@l
	lfs f1, 0x0(r6)
	addi r5, r4, ext_disp@l
	li r3, 0x1
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lis r3, float_neg5000_eki_00008cf8@ha
	lis r4, ext_shadow_disp@ha
	addi r6, r3, float_neg5000_eki_00008cf8@l
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
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stmw r18, 0xb8(r1)
	bl marioGetPtr
	mr r28, r3
	li r3, 0x0
	bl partyGetPtr
	mr r23, r3
	li r3, 0x4
	bl camGetPtr
	lhz r0, 0x2e(r28)
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
	lhz r0, 0x2e(r28)
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
	lis r4, float_neg1_eki_00008cfc@ha
	lis r3, wp@ha
	addi r5, r4, float_neg1_eki_00008cfc@l
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
	lis r4, float_6p2832_eki_00008d00@ha
	addi r10, r3, wp@l
	lis r7, float_0p00761_eki_00008d08@ha
	lwz r5, 0x0(r10)
	lis r3, float_360_eki_00008d04@ha
	addi r8, r3, float_360_eki_00008d04@l
	addi r9, r4, float_6p2832_eki_00008d00@l
	stfs f1, 0x560(r5)
	lis r3, float_3p1416_eki_00008d14@ha
	addi r4, r3, float_3p1416_eki_00008d14@l
	lis r6, float_0p16605_eki_00008d0c@ha
	lwz r3, 0x0(r10)
	lis r5, float_1_eki_00008d10@ha
	lfs f2, 0x0(r9)
	lfs f1, 0x55c(r3)
	lfs f0, 0x0(r8)
	fmuls f2, f2, f1
	lfs f1, 0x0(r4)
	lfs f4, float_0p00761_eki_00008d08@l(r7)
	lfs f3, float_0p16605_eki_00008d0c@l(r6)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r5)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @8
	lis r4, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r4)
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
	lis r4, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r4)
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
	lis r4, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r4)
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
	lis r4, float_6p2832_eki_00008d00@ha
	addi r8, r4, float_6p2832_eki_00008d00@l
	lis r6, float_0p03705_eki_00008d20@ha
	fmadds f0, f1, f4, f0
	lis r4, float_360_eki_00008d04@ha
	addi r7, r4, float_360_eki_00008d04@l
	lis r5, float_0p4967_eki_00008d24@ha
	lis r4, float_3p1416_eki_00008d14@ha
	addi r10, r9, wp@l
	stfs f0, 0x564(r3)
	lis r3, float_1_eki_00008d10@ha
	lfs f3, 0x0(r8)
	lfs f0, 0x5c(r23)
	lwz r9, 0x0(r10)
	lfs f1, float_3p1416_eki_00008d14@l(r4)
	stfs f0, 0x568(r9)
	lfs f0, 0x0(r7)
	lwz r7, 0x0(r10)
	lfs f5, float_0p03705_eki_00008d20@l(r6)
	lfs f2, 0x55c(r7)
	lfs f4, float_0p4967_eki_00008d24@l(r5)
	fmuls f2, f3, f2
	lfs f3, float_1_eki_00008d10@l(r3)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f2, f0
	bge @15
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lha r0, 0x38(r3)
	cmpwi r0, 0xfa
	ble @16
	bl extGetPosePtr
	lis r3, wp@ha
	li r8, 0x0
	addi r6, r3, wp@l
	li r4, 0x19
	lwz r5, 0x0(r6)
	li r3, 0x0
	lwz r9, 0x8(r5)
	b @17
	@18:
	lhz r5, 0x0(r9)
	rlwinm. r0, r5, 0, 29, 29
	bne @19
	rlwinm. r0, r5, 0, 27, 27
	bne @20
	sth r4, 0x2(r9)
	sth r3, 0x4(r9)
	lhz r0, 0x0(r9)
	ori r0, r0, 0x10
	sth r0, 0x0(r9)
	@19:
	addi r8, r8, 0x1
	addi r9, r9, 0x50
	@17:
	lwz r7, 0x0(r6)
	lwz r0, 0x4(r7)
	cmpw r8, r0
	blt @18
	@20:
	lwz r0, 0x44(r7)
	cmplwi r0, 0x0
	bne @16
	lis r3, evt_moamoa_escape@ha
	li r4, 0x0
	addi r3, r3, evt_moamoa_escape@l
	li r5, 0x0
	bl evtEntry
	lis r4, wp@ha
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	stw r3, 0x44(r4)
	@16:
	bl extGetPosePtr
	lis r5, wp@ha
	lis r4, str_00000560@ha
	addi r27, r5, wp@l
	mr r30, r3
	lwz r5, 0x0(r27)
	addi r24, r4, str_00000560@l
	li r26, 0x0
	li r29, 0x0
	lwz r31, 0x8(r5)
	b @21
	@22:
	lwz r3, 0xc(r30)
	lfs f1, 0x8c(r28)
	lfs f2, 0x94(r28)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl angleABf
	lwz r3, 0x0(r27)
	stfs f1, 0x550(r3)
	lwz r3, 0xc(r30)
	lfs f1, 0x8c(r28)
	lfs f2, 0x94(r28)
	lfs f3, 0xc(r3)
	lfs f4, 0x2c(r3)
	bl distABf
	lwz r3, 0x0(r27)
	stfs f1, 0x554(r3)
	lwz r3, 0x0(r27)
	lhz r3, 0x0(r3)
	clrlwi. r0, r3, 31
	beq @23
	rlwinm. r0, r3, 0, 29, 29
	bne @23
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne @23
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	bne @23
	cmpwi r25, 0x0
	bne @23
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x154
	bne @23
	mr r3, r30
	mr r4, r31
	bl moamoa_hit_check
	mr r23, r3
	cmpwi r23, 0x1
	bne @24
	lhz r0, 0x0(r31)
	lis r4, str_00000050@ha
	lis r3, str_00000040@ha
	lis r5, wp@ha
	ori r6, r0, 0x4
	li r0, 0x24
	sth r6, 0x0(r31)
	addi r21, r4, str_00000050@l
	addi r22, r3, str_00000040@l
	sth r0, 0x2(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r25, r3, 0x50
	beq @25
	lbz r4, 0x4c(r31)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r22, 0x0(r3)
	blt @26
	lwz r21, 0x4(r3)
	@26:
	cmplwi r4, 0xa
	bne @25
	lis r3, str_00000578@ha
	addi r21, r3, str_00000578@l
	@25:
	lis r3, wp@ha
	li r23, 0x0
	addi r18, r3, wp@l
	b @27
	@28:
	mr r3, r25
	mr r4, r22
	bl strcmp
	cmpwi r3, 0x0
	bne @29
	mr r4, r21
	addi r3, r25, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @30
	@29:
	addi r23, r23, 0x1
	addi r25, r25, 0x28
	@27:
	lwz r3, 0x0(r18)
	lwz r0, 0x4c(r3)
	cmpw r23, r0
	blt @28
	@30:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r23, r0
	bge @31
	lha r0, 0x3c(r31)
	cmpw r0, r23
	beq @31
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @32
	lis r4, str_0000057C@ha
	mr r3, r21
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @31
	@32:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @33
	lis r4, str_00000580@ha
	mr r3, r21
	addi r4, r4, str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @31
	@33:
	lis r3, gp@ha
	sth r23, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@31:
	li r25, 0x1
	b @23
	@24:
	cmpwi r23, 0x2
	beq @34
	cmpwi r23, 0x4
	bne @35
	@34:
	lhz r0, 0x0(r31)
	lis r4, str_00000050@ha
	lis r3, str_00000040@ha
	lis r5, wp@ha
	ori r6, r0, 0xc
	li r0, 0x2f
	sth r6, 0x0(r31)
	addi r19, r4, str_00000050@l
	addi r20, r3, str_00000040@l
	sth r0, 0x2(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r22, r3, 0x50
	beq @36
	lbz r4, 0x4c(r31)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r20, 0x0(r3)
	blt @37
	lwz r19, 0x4(r3)
	@37:
	cmplwi r4, 0xa
	bne @36
	lis r3, str_00000578@ha
	addi r19, r3, str_00000578@l
	@36:
	lis r3, wp@ha
	li r21, 0x0
	addi r18, r3, wp@l
	b @38
	@39:
	mr r3, r22
	mr r4, r20
	bl strcmp
	cmpwi r3, 0x0
	bne @40
	mr r4, r19
	addi r3, r22, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @41
	@40:
	addi r21, r21, 0x1
	addi r22, r22, 0x28
	@38:
	lwz r3, 0x0(r18)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	blt @39
	@41:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r21, r0
	bge @42
	lha r0, 0x3c(r31)
	cmpw r0, r21
	beq @42
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @43
	lis r4, str_0000057C@ha
	mr r3, r19
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @42
	@43:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @44
	lis r4, str_00000580@ha
	mr r3, r19
	addi r4, r4, str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @42
	@44:
	lis r3, gp@ha
	sth r21, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@42:
	cmpwi r23, 0x4
	beq @23
	li r25, 0x1
	b @23
	@35:
	cmpwi r23, 0x3
	bne @23
	lis r3, wp@ha
	lhz r0, 0x0(r31)
	addi r4, r3, wp@l
	lwz r7, 0x0(r4)
	ori r5, r0, 0x84
	lis r4, float_0p5_eki_00008d4c@ha
	li r0, 0x30
	lfs f2, 0x55c(r7)
	addi r6, r4, float_0p5_eki_00008d4c@l
	lfs f1, 0x550(r7)
	lis r3, vec3_eki_00008908@ha
	addi r4, r3, vec3_eki_00008908@l
	lfs f0, 0x0(r6)
	sth r5, 0x0(r31)
	fadds f1, f2, f1
	sth r0, 0x2(r31)
	fmuls f27, f1, f0
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x8(r31)
	stw r0, 0xc(r31)
	lwz r0, 0x8(r4)
	stw r0, 0x10(r31)
	bl rand
	xoris r4, r3, 0x8000
	lis r0, 0x4330
	lis r3, float_6p2832_eki_00008d00@ha
	stw r4, 0xac(r1)
	lfs f0, float_6p2832_eki_00008d00@l(r3)
	lis r5, double_to_int_eki_00008df8@ha
	stw r0, 0xa8(r1)
	lis r3, float_360_eki_00008d04@ha
	lfd f3, double_to_int_eki_00008df8@l(r5)
	fmuls f1, f0, f27
	lfs f0, float_360_eki_00008d04@l(r3)
	lis r4, float_32767_eki_00008d50@ha
	lfd f2, 0xa8(r1)
	lis r5, float_0p00761_eki_00008d08@ha
	fdivs f30, f1, f0
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f5, float_0p00761_eki_00008d08@l(r5)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r3, float_1_eki_00008d10@ha
	fsubs f3, f2, f3
	lfs f2, float_32767_eki_00008d50@l(r4)
	lis r4, float_0p1_eki_00008d54@ha
	addi r6, r4, float_0p1_eki_00008d54@l
	fcmpo cr0, f30, f1
	fdivs f2, f3, f2
	lfs f0, 0x0(r6)
	lis r4, float_0p16605_eki_00008d0c@ha
	lfs f4, float_0p16605_eki_00008d0c@l(r4)
	lfs f3, float_1_eki_00008d10@l(r3)
	fmadds f31, f2, f0, f0
	cror eq, lt, eq
	bne @45
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @46
	fmuls f0, f30, f30
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f30
	b @47
	@46:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @47
	@45:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f30, f0
	bge @48
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @47
	@48:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@47:
	fmuls f0, f31, f5
	stfs f0, 0x14(r31)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_eki_00008df8@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_eki_00008df8@l
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r4, r3, float_32767_eki_00008d50@l
	lfd f2, 0x0(r5)
	lis r3, float_0p03_eki_00008d58@ha
	lfd f1, 0xa8(r1)
	addi r6, r3, float_0p03_eki_00008d58@l
	lfs f0, 0x0(r4)
	lis r5, float_0p03705_eki_00008d20@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_0p4967_eki_00008d24@ha
	lis r3, float_1_eki_00008d10@ha
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	fdivs f2, f2, f0
	lfs f0, 0x0(r6)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	fmadds f0, f2, f0, f0
	lfs f2, float_1_eki_00008d10@l(r3)
	fcmpo cr0, f30, f1
	stfs f0, 0x1c(r31)
	cror eq, lt, eq
	bne @49
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @50
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @51
	@50:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @51
	@49:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f30, f0
	bge @52
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @51
	@52:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@51:
	fneg f0, f4
	lis r4, str_00000050@ha
	lis r3, str_00000040@ha
	li r0, 0x78
	lis r5, wp@ha
	addi r22, r4, str_00000050@l
	fmuls f0, f31, f0
	addi r21, r3, str_00000040@l
	stfs f0, 0x20(r31)
	sth r0, 0x18(r31)
	lwzu r4, wp@l(r5)
	lha r3, 0x38(r4)
	addi r0, r3, 0x1
	sth r0, 0x38(r4)
	lhz r0, 0x0(r31)
	lwz r3, 0x0(r5)
	rlwinm. r0, r0, 0, 20, 20
	addi r20, r3, 0x50
	beq @53
	lbz r4, 0x4c(r31)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r21, 0x0(r3)
	blt @54
	lwz r22, 0x4(r3)
	@54:
	cmplwi r4, 0xa
	bne @53
	lis r3, str_00000578@ha
	addi r22, r3, str_00000578@l
	@53:
	lis r3, wp@ha
	li r19, 0x0
	addi r23, r3, wp@l
	b @55
	@56:
	mr r3, r20
	mr r4, r21
	bl strcmp
	cmpwi r3, 0x0
	bne @57
	mr r4, r22
	addi r3, r20, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @58
	@57:
	addi r19, r19, 0x1
	addi r20, r20, 0x28
	@55:
	lwz r3, 0x0(r23)
	lwz r0, 0x4c(r3)
	cmpw r19, r0
	blt @56
	@58:
	lis r3, wp@ha
	addi r3, r3, wp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x4c(r3)
	cmpw r19, r0
	bge @59
	lha r0, 0x3c(r31)
	cmpw r0, r19
	beq @59
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq @60
	lis r4, str_0000057C@ha
	mr r3, r22
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @59
	@60:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq @61
	lis r4, str_00000580@ha
	mr r3, r22
	addi r4, r4, str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @59
	@61:
	lis r3, gp@ha
	sth r19, 0x3c(r31)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r31)
	stw r0, 0x40(r31)
	@59:
	li r25, 0x1
	@23:
	lwz r4, 0x0(r27)
	lhz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @62
	lhz r5, 0x0(r31)
	andi. r0, r5, 0x155
	bne @62
	lis r3, float_50_eki_00008d5c@ha
	lfs f1, 0x554(r4)
	lfs f0, float_50_eki_00008d5c@l(r3)
	fcmpo cr0, f1, f0
	bge @62
	rlwinm. r0, r5, 0, 30, 30
	beq @63
	li r0, 0x1
	sth r0, 0x24(r31)
	b @62
	@63:
	li r0, 0x1
	sth r0, 0x2(r31)
	@62:
	lwz r3, 0x0(r27)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @64
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x444
	bne @64
	lis r4, gp@ha
	lwz r3, 0x4(r3)
	addi r4, r4, gp@l
	lwz r4, 0x0(r4)
	lwz r4, 0x1c(r4)
	divwu r0, r4, r3
	mullw r0, r0, r3
	subf r0, r0, r4
	cmplw r29, r0
	bne @64
	li r3, 0x3e8
	bl irand
	cmpwi r3, 0xc8
	bge @64
	lis r3, vec3_eki_00008914@ha
	lwz r5, 0xc(r30)
	addi r8, r3, vec3_eki_00008914@l
	mr r3, r24
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
	@64:
	lha r0, 0x2(r31)
	cmplwi r0, 0x41
	bgt @65
	lis r3, jumptable_00002400@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_00002400@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@66:
	entry jt_00000FEC
	li r3, 0x32
	divw r0, r29, r3
	mullw r0, r0, r3
	subf r0, r0, r29
	cmpwi r0, 0x14
	bge @67
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, float_6p2832_eki_00008d00@ha
	lfd f0, 0xa8(r1)
	lis r3, zero_eki_00008cf4@ha
	fsubs f3, f0, f1
	lfs f1, float_6p2832_eki_00008d00@l(r4)
	lfs f0, zero_eki_00008cf4@l(r3)
	fdivs f2, f3, f2
	fmadds f31, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_eki_00008df8@ha
	stw r3, 0xb4(r1)
	addi r5, r4, double_to_int_eki_00008df8@l
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r4, r3, float_32767_eki_00008d50@l
	lfd f2, 0x0(r5)
	lis r5, float_50_eki_00008d5c@ha
	lfd f1, 0xb0(r1)
	addi r7, r5, float_50_eki_00008d5c@l
	lfs f0, 0x0(r4)
	lis r4, zero_eki_00008cf4@ha
	fsubs f2, f1, f2
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	addi r6, r4, zero_eki_00008cf4@l
	lis r5, float_0p00761_eki_00008d08@ha
	lis r4, float_0p16605_eki_00008d0c@ha
	fdivs f3, f2, f0
	lfs f2, 0x0(r7)
	lfs f0, 0x0(r6)
	lis r3, float_1_eki_00008d10@ha
	lfs f4, float_0p00761_eki_00008d08@l(r5)
	fmadds f7, f3, f2, f0
	fcmpo cr0, f31, f1
	lfs f3, float_0p16605_eki_00008d0c@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @68
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f31, f1
	cror eq, lt, eq
	bne @69
	fmuls f0, f31, f31
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f31
	b @70
	@69:
	fsubs f0, f31, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @70
	@68:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f31, f0
	bge @71
	fsubs f1, f31, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @70
	@71:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f31, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@70:
	li r4, 0x3
	lis r5, wp@ha
	divw r0, r29, r4
	lwz r6, wp@l(r5)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r5, float_0p03705_eki_00008d20@ha
	lis r3, float_1_eki_00008d10@ha
	mullw r0, r0, r4
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f5, float_0p4967_eki_00008d24@l(r4)
	fcmpo cr0, f31, f1
	lfs f6, float_0p03705_eki_00008d20@l(r5)
	lfs f2, float_1_eki_00008d10@l(r3)
	subf r0, r0, r29
	mulli r0, r0, 0xc
	add r4, r6, r0
	lfs f0, 0x14(r4)
	fmadds f3, f7, f4, f0
	cror eq, lt, eq
	bne @72
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f31, f1
	cror eq, lt, eq
	bne @73
	fmuls f0, f31, f31
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	b @74
	@73:
	fsubs f0, f31, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	fneg f6, f6
	b @74
	@72:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f31, f0
	bge @75
	fsubs f0, f31, f1
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	fneg f6, f6
	b @74
	@75:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f31, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f6, f6, f0, f5
	fmadds f6, f6, f0, f2
	@74:
	lfs f0, 0x1c(r4)
	lwz r3, 0xc(r30)
	fnmsubs f4, f7, f6, f0
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	bl angleABf
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_eki_00008d04@l(r4)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @76
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @77
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @78
	@77:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @78
	@76:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @79
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @78
	@79:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@78:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_15_eki_00008d60@ha
	lfs f2, float_15_eki_00008d60@l(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_eki_00008d20@ha
	lis r3, float_1_eki_00008d10@ha
	fmadds f28, f2, f4, f0
	lfs f29, 0x1c(r6)
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @80
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @81
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @82
	@81:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @82
	@80:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @83
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @82
	@83:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@82:
	lis r3, float_15_eki_00008d60@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_eki_00008d60@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f30, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	lis r5, float_1p5_eki_00008d64@ha
	lfs f4, float_1p5_eki_00008d64@l(r5)
	lis r4, float_1p2_eki_00008d6c@ha
	lfd f1, 0xa8(r1)
	fmr f3, f27
	lfs f0, float_32767_eki_00008d50@l(r3)
	lis r3, float_0p8_eki_00008d68@ha
	fsubs f2, f1, f2
	lfs f5, float_1p2_eki_00008d6c@l(r4)
	fmr f1, f28
	fmadds f4, f30, f4, f4
	lha r5, 0x2(r31)
	fdivs f6, f2, f0
	lfs f0, float_0p8_eki_00008d68@l(r3)
	mr r3, r30
	mr r4, r31
	li r6, 0x1
	fmr f2, f29
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	lhz r0, 0x0(r31)
	ori r0, r0, 0x1
	sth r0, 0x0(r31)
	b @65
	@67:
	li r3, 0x3
	lwz r5, 0xc(r30)
	divw r0, r29, r3
	lis r4, wp@ha
	lfs f1, 0xc(r5)
	addi r4, r4, wp@l
	lfs f2, 0x2c(r5)
	lwz r4, 0x0(r4)
	mullw r0, r0, r3
	subf r0, r0, r29
	mulli r18, r0, 0xc
	add r3, r4, r18
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r3, wp@ha
	lwz r4, 0xc(r30)
	lwz r0, wp@l(r3)
	fmr f28, f1
	lfs f1, 0xc(r4)
	add r3, r0, r18
	lfs f2, 0x2c(r4)
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl angleABf
	lis r3, float_100_eki_00008d70@ha
	lfs f0, float_100_eki_00008d70@l(r3)
	fcmpo cr0, f28, f0
	bge @84
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, float_360_eki_00008d04@ha
	lfd f0, 0xb0(r1)
	lis r3, zero_eki_00008cf4@ha
	fsubs f3, f0, f1
	lfs f1, float_360_eki_00008d04@l(r4)
	lfs f0, zero_eki_00008cf4@l(r3)
	fdivs f2, f3, f2
	fmadds f1, f2, f1, f0
	@84:
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_eki_00008d04@l(r4)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @85
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @86
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @87
	@86:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @87
	@85:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @88
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @87
	@88:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@87:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_5_eki_00008d74@ha
	lfs f2, float_5_eki_00008d74@l(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_eki_00008d20@ha
	lis r3, float_1_eki_00008d10@ha
	fmadds f30, f2, f4, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @89
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @90
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @91
	@90:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @91
	@89:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @92
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @91
	@92:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@91:
	lis r3, float_5_eki_00008d74@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_5_eki_00008d74@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	lis r5, float_0p2_eki_00008d7c@ha
	lfs f0, float_32767_eki_00008d50@l(r3)
	lis r4, float_0p3_eki_00008d78@ha
	lfd f1, 0xa8(r1)
	lis r3, float_0p5_eki_00008d4c@ha
	lfs f4, float_0p2_eki_00008d7c@l(r5)
	fmr f3, f27
	fsubs f2, f1, f2
	lfs f5, float_0p3_eki_00008d78@l(r4)
	fmr f1, f30
	lha r5, 0x2(r31)
	fmadds f4, f28, f4, f5
	fdivs f6, f2, f0
	lfs f0, float_0p5_eki_00008d4c@l(r3)
	mr r3, r30
	mr r4, r31
	li r6, 0x1
	fmr f2, f31
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	lhz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 30
	sth r0, 0x0(r31)
	b @65
	@93:
	entry jt_000017D4
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @65
	li r0, 0x0
	sth r0, 0x4(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@94:
	entry jt_00001800
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f1, 0x0(r5)
	lis r4, float_200_eki_00008d80@ha
	lfd f0, 0xb0(r1)
	lis r3, zero_eki_00008cf4@ha
	addi r5, r4, float_200_eki_00008d80@l
	fsubs f3, f0, f2
	addi r4, r3, zero_eki_00008cf4@l
	lfs f2, 0x0(r5)
	lis r3, float_300_eki_00008d84@ha
	lfs f0, 0x0(r4)
	fdivs f3, f3, f1
	lfs f1, float_300_eki_00008d84@l(r3)
	fmadds f0, f3, f2, f0
	stfs f0, 0x1c(r31)
	lfs f0, 0x1c(r31)
	fmuls f0, f1, f0
	fdivs f28, f0, f2
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_eki_00008df8@ha
	stw r3, 0xac(r1)
	addi r5, r4, double_to_int_eki_00008df8@l
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r4, r3, float_32767_eki_00008d50@l
	lfd f1, 0x0(r5)
	lis r3, zero_eki_00008cf4@ha
	lfd f0, 0xa8(r1)
	li r0, 0x0
	lfs f2, 0x0(r4)
	fsubs f3, f0, f1
	lfs f1, zero_eki_00008cf4@l(r3)
	fsubs f0, f28, f1
	fdivs f2, f3, f2
	fmadds f0, f2, f0, f1
	stfs f0, 0x20(r31)
	lha r3, 0x2(r31)
	addi r3, r3, 0x1
	sth r3, 0x2(r31)
	sth r0, 0x4(r31)
	@95:
	entry jt_000018C8
	lha r0, 0x4(r31)
	cmpwi r0, 0xc8
	bge @96
	lis r3, float_1_eki_00008d10@ha
	lfs f1, float_1_eki_00008d10@l(r3)
	b @97
	@96:
	subfic r3, r0, 0x320
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_eki_00008df8@ha
	stw r3, 0xb4(r1)
	lis r3, float_600_eki_00008d88@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_600_eki_00008d88@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f1, f1, f0
	@97:
	lis r3, zero_eki_00008cf4@ha
	fmr f28, f1
	lfs f0, zero_eki_00008cf4@l(r3)
	fcmpo cr0, f1, f0
	bge @98
	lhz r0, 0x0(r31)
	fmr f28, f0
	ori r0, r0, 0x200
	sth r0, 0x0(r31)
	@98:
	li r6, 0x3
	lis r3, gp@ha
	divw r5, r29, r6
	lwz r4, gp@l(r3)
	lis r0, 0x4330
	stw r0, 0xb0(r1)
	lis r3, double_to_int_mask_eki_00008e00@ha
	lwz r0, 0x1c(r4)
	mullw r4, r5, r6
	add r0, r29, r0
	stw r0, 0xb4(r1)
	lis r5, wp@ha
	lfd f1, double_to_int_mask_eki_00008e00@l(r3)
	lis r3, float_0p25_eki_00008d8c@ha
	lfd f0, 0xb0(r1)
	subf r0, r4, r29
	mulli r0, r0, 0xc
	fsubs f1, f0, f1
	lfs f0, float_0p25_eki_00008d8c@l(r3)
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
	lis r3, double_to_int_mask_eki_00008e00@ha
	lfs f1, 0x20(r31)
	addi r4, r3, double_to_int_mask_eki_00008e00@l
	lwz r5, 0x1c(r5)
	fmuls f3, f1, f2
	stw r0, 0xa8(r1)
	add r0, r29, r5
	lfs f0, 0x1c(r31)
	stw r0, 0xac(r1)
	lis r3, float_0p25_eki_00008d8c@ha
	lfd f2, 0x0(r4)
	fmadds f30, f0, f28, f30
	lfd f1, 0xa8(r1)
	fmadds f27, f28, f3, f27
	lfs f0, float_0p25_eki_00008d8c@l(r3)
	fsubs f1, f1, f2
	fmuls f1, f1, f0
	bl cos
	lwz r4, 0xc(r30)
	lis r3, float_15_eki_00008d60@ha
	lfs f0, 0x20(r31)
	frsp f4, f1
	lfs f3, 0xc(r4)
	fneg f1, f0
	lfs f2, float_15_eki_00008d60@l(r3)
	fsubs f0, f27, f3
	fmuls f1, f1, f4
	fdivs f0, f0, f2
	fadds f0, f3, f0
	fmadds f29, f28, f1, f29
	stfs f0, 0xc(r4)
	lwz r3, 0xc(r30)
	lfs f1, 0x1c(r3)
	fsubs f0, f30, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lwz r3, 0xc(r30)
	lfs f1, 0x2c(r3)
	fsubs f0, f29, f1
	fdivs f0, f0, f2
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x4(r31)
	addi r0, r3, 0x1
	sth r0, 0x4(r31)
	b @65
	@99:
	entry jt_00001A6C
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lis r4, float_90_eki_00008d94@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xb0(r1)
	lis r3, float_neg45_eki_00008d90@ha
	addi r9, r4, float_90_eki_00008d94@l
	lis r4, float_6p2832_eki_00008d00@ha
	fsubs f1, f1, f2
	addi r5, r3, float_neg45_eki_00008d90@l
	lis r3, wp@ha
	addi r8, r4, float_6p2832_eki_00008d00@l
	addi r6, r3, wp@l
	lis r4, float_1_eki_00008d10@ha
	fdivs f2, f1, f0
	lwz r10, 0x0(r6)
	lfs f0, 0x0(r5)
	lis r3, float_360_eki_00008d04@ha
	lfs f1, 0x0(r9)
	addi r7, r3, float_360_eki_00008d04@l
	fmadds f1, f2, f1, f0
	lfs f3, 0x550(r10)
	lfs f2, 0x0(r8)
	lis r6, float_0p00761_eki_00008d08@ha
	lis r5, float_0p16605_eki_00008d0c@ha
	lfs f0, 0x0(r7)
	fadds f3, f3, f1
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lfs f28, 0x554(r10)
	fmuls f2, f2, f3
	lfs f5, float_0p00761_eki_00008d08@l(r6)
	lfs f4, float_0p16605_eki_00008d0c@l(r5)
	lfs f3, float_1_eki_00008d10@l(r4)
	fdivs f6, f2, f0
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @100
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @101
	fmuls f0, f6, f6
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f6
	b @102
	@101:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	b @102
	@100:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f6, f0
	bge @103
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	b @102
	@103:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f1
	fneg f5, f5
	@102:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_15_eki_00008d60@ha
	lfs f2, float_15_eki_00008d60@l(r4)
	lis r5, float_0p03705_eki_00008d20@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f6, f1
	lis r4, float_0p4967_eki_00008d24@ha
	lis r3, float_1_eki_00008d10@ha
	fmadds f30, f2, f5, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @104
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @105
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @106
	@105:
	fsubs f0, f6, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @106
	@104:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f6, f0
	bge @107
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @106
	@107:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@106:
	lis r3, float_15_eki_00008d60@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_eki_00008d60@l(r3)
	fnmsubs f29, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, zero_eki_00008cf4@ha
	lfd f0, 0xb0(r1)
	lis r3, float_1_eki_00008d10@ha
	fsubs f3, f0, f1
	lfs f1, zero_eki_00008cf4@l(r4)
	lfs f0, float_1_eki_00008d10@l(r3)
	fdivs f2, f3, f2
	fmadds f27, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f0, 0x0(r5)
	lis r4, zero_eki_00008cf4@ha
	lfd f1, 0xa8(r1)
	lis r3, float_0p4_eki_00008d98@ha
	addi r5, r4, zero_eki_00008cf4@l
	fmr f4, f27
	fsubs f3, f1, f2
	addi r4, r3, float_0p4_eki_00008d98@l
	lfs f1, 0x0(r4)
	lis r3, float_100_eki_00008d70@ha
	lfs f2, 0x0(r5)
	fdivs f3, f3, f0
	lfs f0, float_100_eki_00008d70@l(r3)
	mr r3, r30
	mr r4, r31
	fmadds f5, f3, f2, f1
	fmr f1, f30
	fmr f2, f31
	fmr f3, f29
	fcmpo cr0, f28, f0
	bge @108
	lha r5, 0x2(r31)
	b @109
	@108:
	li r5, 0x0
	@109:
	li r6, 0x1
	bl moamoa_jump
	b @65
	@110:
	entry jt_00001D64
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lis r4, float_90_eki_00008d94@ha
	lis r3, float_neg45_eki_00008d90@ha
	lfd f1, 0xb0(r1)
	addi r7, r4, float_90_eki_00008d94@l
	lfs f0, 0x0(r5)
	addi r6, r3, float_neg45_eki_00008d90@l
	fsubs f1, f1, f2
	lis r3, wp@ha
	addi r5, r3, wp@l
	lis r4, float_180_eki_00008d9c@ha
	lwz r9, 0x0(r5)
	addi r8, r4, float_180_eki_00008d9c@l
	fdivs f2, f1, f0
	lfs f0, 0x0(r6)
	lfs f1, 0x0(r7)
	lis r3, float_6p2832_eki_00008d00@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	fmadds f0, f2, f1, f0
	lfs f4, 0x550(r9)
	lfs f3, 0x0(r8)
	addi r7, r4, float_360_eki_00008d04@l
	lfs f2, 0x0(r5)
	lis r3, float_3p1416_eki_00008d14@ha
	fadds f4, f4, f0
	lis r6, float_0p00761_eki_00008d08@ha
	lfs f0, 0x0(r7)
	lis r5, float_0p16605_eki_00008d0c@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	fadds f4, f4, f3
	lfs f28, 0x554(r9)
	lfs f5, float_0p00761_eki_00008d08@l(r6)
	lfs f3, float_1_eki_00008d10@l(r4)
	fmuls f2, f2, f4
	lfs f4, float_0p16605_eki_00008d0c@l(r5)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @111
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @112
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @113
	@112:
	fsubs f0, f2, f1
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	b @113
	@111:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f2, f0
	bge @114
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	b @113
	@114:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fmuls f5, f5, f2
	fneg f5, f5
	@113:
	lwz r4, 0xc(r30)
	lis r3, float_30_eki_00008da0@ha
	lfs f1, float_30_eki_00008da0@l(r3)
	lfs f0, 0xc(r4)
	lfs f31, 0x1c(r4)
	fmadds f30, f1, f5, f0
	lfs f29, 0x2c(r4)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, zero_eki_00008cf4@ha
	lfd f0, 0xb0(r1)
	lis r3, float_1_eki_00008d10@ha
	lis r5, float_2_eki_00008da4@ha
	fsubs f3, f0, f1
	lfs f1, zero_eki_00008cf4@l(r4)
	lfs f0, float_1_eki_00008d10@l(r3)
	fdivs f3, f3, f2
	lfs f2, float_2_eki_00008da4@l(r5)
	fmadds f0, f3, f1, f0
	fmuls f27, f2, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lis r6, float_2_eki_00008da4@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xa8(r1)
	lis r4, zero_eki_00008cf4@ha
	lis r3, float_0p4_eki_00008d98@ha
	lfs f4, float_2_eki_00008da4@l(r6)
	fsubs f1, f1, f2
	addi r5, r4, zero_eki_00008cf4@l
	addi r4, r3, float_0p4_eki_00008d98@l
	lfs f2, 0x0(r5)
	lis r3, float_100_eki_00008d70@ha
	fdivs f3, f1, f0
	lfs f1, 0x0(r4)
	mr r4, r31
	lfs f0, float_100_eki_00008d70@l(r3)
	mr r3, r30
	fmadds f3, f3, f2, f1
	fmr f1, f30
	fmr f2, f31
	fmuls f5, f4, f3
	fmr f3, f29
	fmr f4, f27
	fcmpo cr0, f28, f0
	bge @115
	lha r5, 0x2(r31)
	b @116
	@115:
	li r5, 0x0
	@116:
	li r6, 0x1
	bl moamoa_jump
	b @65
	@117:
	entry jt_00001FC8
	lwz r3, 0xc(r30)
	lfs f0, 0x14(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lfs f1, 0x14(r31)
	lfs f0, 0x20(r31)
	fsubs f0, f1, f0
	stfs f0, 0x14(r31)
	lwz r3, 0xc(r30)
	lfs f3, 0x8(r31)
	lfs f1, 0xc(r3)
	lfs f2, 0x2c(r3)
	lfs f4, 0x10(r31)
	bl angleABf
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_eki_00008d04@l(r4)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @118
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @119
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @120
	@119:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @120
	@118:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @121
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @120
	@121:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@120:
	lwz r7, 0xc(r30)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r5, float_0p4967_eki_00008d24@ha
	lfs f2, 0x1c(r31)
	lis r6, float_0p03705_eki_00008d20@ha
	lfs f0, 0xc(r7)
	fcmpo cr0, f5, f1
	lis r4, float_1_eki_00008d10@ha
	lfs f3, float_0p4967_eki_00008d24@l(r5)
	fmadds f0, f2, f4, f0
	lfs f4, float_0p03705_eki_00008d20@l(r6)
	lfs f2, float_1_eki_00008d10@l(r4)
	stfs f0, 0xc(r7)
	cror eq, lt, eq
	bne @122
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @123
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @124
	@123:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @124
	@122:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @125
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @124
	@125:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@124:
	lwz r3, 0xc(r30)
	fneg f1, f4
	lfs f2, 0x1c(r31)
	lfs f0, 0x2c(r3)
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r3)
	lha r3, 0x18(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r31)
	bge @65
	lfs f0, 0x8(r31)
	li r0, 0x0
	lwz r3, 0xc(r30)
	stfs f0, 0xc(r3)
	lfs f0, 0xc(r31)
	lwz r3, 0xc(r30)
	stfs f0, 0x1c(r3)
	lfs f0, 0x10(r31)
	lwz r3, 0xc(r30)
	stfs f0, 0x2c(r3)
	lhz r3, 0x0(r31)
	rlwinm r3, r3, 0, 31, 29
	sth r3, 0x0(r31)
	lwz r3, 0x0(r30)
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x0(r30)
	sth r0, 0x4(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@126:
	entry jt_00002224
	lha r3, 0x4(r31)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r31)
	cmpwi r0, 0x4
	ble @65
	lha r0, 0x24(r31)
	sth r0, 0x2(r31)
	b @65
	@127:
	entry jt_00002248
	lhz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	bne @128
	lfs f27, 0x8c(r28)
	lfs f28, 0x94(r28)
	b @129
	@128:
	li r3, 0x3
	lis r4, wp@ha
	divw r0, r29, r3
	addi r4, r4, wp@l
	lwz r4, 0x0(r4)
	mullw r0, r0, r3
	subf r0, r0, r29
	mulli r0, r0, 0xc
	add r3, r4, r0
	lfs f27, 0x14(r3)
	lfs f28, 0x1c(r3)
	@129:
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f4, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	fmr f2, f28
	lfs f0, float_32767_eki_00008d50@l(r3)
	fmr f1, f27
	lfd f3, 0xb0(r1)
	lwz r5, 0xc(r30)
	fsubs f5, f3, f4
	lfs f3, 0xc(r5)
	lfs f4, 0x2c(r5)
	fdivs f28, f5, f0
	bl angleABf
	lis r3, float_90_eki_00008d94@ha
	lis r4, float_neg45_eki_00008d90@ha
	addi r5, r3, float_90_eki_00008d94@l
	lfs f0, float_neg45_eki_00008d90@l(r4)
	lfs f2, 0x0(r5)
	lis r3, float_6p2832_eki_00008d00@ha
	addi r8, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	fmadds f0, f28, f2, f0
	addi r7, r4, float_360_eki_00008d04@l
	lis r6, float_0p00761_eki_00008d08@ha
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lis r4, float_1_eki_00008d10@ha
	fadds f2, f1, f0
	lfs f1, 0x0(r8)
	lfs f0, 0x0(r7)
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @130
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @131
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @132
	@131:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @132
	@130:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @133
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @132
	@133:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@132:
	lwz r6, 0xc(r30)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_15_eki_00008d60@ha
	lfs f2, float_15_eki_00008d60@l(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_eki_00008d20@ha
	lis r3, float_1_eki_00008d10@ha
	fmadds f30, f2, f4, f0
	lfs f31, 0x1c(r6)
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @134
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @135
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @136
	@135:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @136
	@134:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @137
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @136
	@137:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@136:
	lis r3, float_15_eki_00008d60@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_eki_00008d60@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f0, 0x0(r5)
	lis r4, zero_eki_00008cf4@ha
	lfd f1, 0xa8(r1)
	lis r3, float_1_eki_00008d10@ha
	lfs f5, zero_eki_00008cf4@l(r4)
	mr r4, r31
	fsubs f3, f1, f2
	lha r5, 0x2(r31)
	fmr f1, f30
	li r6, 0x1
	fmr f2, f31
	addi r5, r5, 0x1
	fdivs f6, f3, f0
	lfs f0, float_1_eki_00008d10@l(r3)
	mr r3, r30
	fmadds f4, f28, f5, f0
	fmr f3, f27
	fmadds f5, f6, f5, f0
	bl moamoa_jump
	b @65
	@138:
	entry jt_0000254C
	lha r3, 0x4(r31)
	addi r3, r3, 0x1
	extsh r0, r3
	sth r3, 0x4(r31)
	cmpwi r0, 0x1e
	bge @139
	lwz r4, 0xc(r30)
	lis r3, float_0p9_eki_00008da8@ha
	lfs f1, float_0p9_eki_00008da8@l(r3)
	lfs f0, 0x0(r4)
	fmuls f0, f0, f1
	stfs f0, 0x0(r4)
	lwz r3, 0xc(r30)
	lfs f0, 0x14(r3)
	fmuls f0, f0, f1
	stfs f0, 0x14(r3)
	lwz r3, 0xc(r30)
	lfs f0, 0x28(r3)
	fmuls f0, f0, f1
	stfs f0, 0x28(r3)
	b @65
	@139:
	li r0, 0x31
	sth r0, 0x2(r31)
	b @65
	@140:
	entry jt_000025AC
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	lis r5, float_90_eki_00008d94@ha
	lis r4, float_135_eki_00008dac@ha
	lfs f0, float_135_eki_00008dac@l(r4)
	xoris r6, r3, 0x8000
	lfs f1, float_90_eki_00008d94@l(r5)
	lis r0, 0x4330
	lis r3, float_6p2832_eki_00008d00@ha
	lis r4, double_to_int_eki_00008df8@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	stw r6, 0xac(r1)
	fmadds f0, f28, f1, f0
	addi r6, r4, double_to_int_eki_00008df8@l
	stw r0, 0xa8(r1)
	lis r3, float_360_eki_00008d04@ha
	lfs f1, 0x0(r5)
	addi r4, r3, float_360_eki_00008d04@l
	lis r3, float_32767_eki_00008d50@ha
	fmuls f1, f1, f0
	lfs f0, 0x0(r4)
	addi r5, r3, float_32767_eki_00008d50@l
	lfd f3, 0x0(r6)
	lis r4, float_300_eki_00008d84@ha
	lfd f2, 0xa8(r1)
	fdivs f7, f1, f0
	addi r6, r4, float_300_eki_00008d84@l
	lis r3, float_3p1416_eki_00008d14@ha
	lis r4, float_0p16605_eki_00008d0c@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r3, float_1_eki_00008d10@ha
	fsubs f3, f2, f3
	lfs f2, 0x0(r5)
	lis r5, float_200_eki_00008d80@ha
	lfs f0, 0x0(r6)
	addi r7, r5, float_200_eki_00008d80@l
	fcmpo cr0, f7, f1
	fdivs f3, f3, f2
	lfs f2, 0x0(r7)
	lis r5, float_0p00761_eki_00008d08@ha
	lfs f4, float_0p16605_eki_00008d0c@l(r4)
	lfs f5, float_0p00761_eki_00008d08@l(r5)
	fmadds f6, f3, f2, f0
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @141
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @142
	fmuls f0, f7, f7
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f7
	b @143
	@142:
	fsubs f0, f7, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	b @143
	@141:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f7, f0
	bge @144
	fsubs f1, f7, f1
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	b @143
	@144:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fmuls f5, f5, f1
	fneg f5, f5
	@143:
	lis r3, float_3p1416_eki_00008d14@ha
	lwz r6, 0xc(r30)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r5, float_0p03705_eki_00008d20@ha
	lfs f0, 0xc(r6)
	lis r4, float_0p4967_eki_00008d24@ha
	fcmpo cr0, f7, f1
	lis r3, float_1_eki_00008d10@ha
	fmadds f30, f6, f5, f0
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @145
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f7, f1
	cror eq, lt, eq
	bne @146
	fmuls f0, f7, f7
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @147
	@146:
	fsubs f0, f7, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @147
	@145:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f7, f0
	bge @148
	fsubs f0, f7, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @147
	@148:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f7, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@147:
	lfs f0, 0x2c(r6)
	fnmsubs f31, f6, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, float_1_eki_00008d10@ha
	lfd f0, 0xb0(r1)
	lis r3, float_5_eki_00008d74@ha
	fsubs f3, f0, f1
	lfs f1, float_1_eki_00008d10@l(r4)
	lfs f0, float_5_eki_00008d74@l(r3)
	fdivs f2, f3, f2
	fmadds f27, f2, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, float_0p1_eki_00008db4@ha
	lfd f0, 0xa8(r1)
	lis r3, float_0p2_eki_00008db0@ha
	cmpwi r26, 0x0
	fsubs f3, f0, f1
	lfs f1, float_0p1_eki_00008db4@l(r4)
	lfs f0, float_0p2_eki_00008db0@l(r3)
	fdivs f2, f3, f2
	fmadds f28, f2, f1, f0
	bne @149
	lis r3, vec3_eki_00008920@ha
	addi r4, r1, 0x14
	addi r7, r3, vec3_eki_00008920@l
	li r3, 0x6c3
	lwz r6, 0x0(r7)
	lwz r5, 0x4(r7)
	lwz r0, 0x8(r7)
	stw r6, 0x14(r1)
	stw r5, 0x18(r1)
	stw r0, 0x1c(r1)
	lwz r5, 0xc(r30)
	lfs f0, 0xc(r5)
	stfs f0, 0x14(r1)
	lfs f0, 0x1c(r5)
	stfs f0, 0x18(r1)
	lfs f0, 0x2c(r5)
	stfs f0, 0x1c(r1)
	bl psndSFXOn_3D
	li r26, 0x1
	@149:
	lis r3, float_neg100_eki_00008db8@ha
	fmr f1, f30
	lfs f2, float_neg100_eki_00008db8@l(r3)
	fmr f3, f31
	fmr f4, f27
	mr r3, r30
	fmr f5, f28
	mr r4, r31
	li r5, 0x31
	li r6, 0x0
	bl moamoa_jump
	b @65
	@150:
	entry jt_000028FC
	lha r3, 0x18(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x18(r31)
	ble @151
	lfs f1, 0x8(r31)
	lfs f0, 0x14(r31)
	fadds f0, f1, f0
	stfs f0, 0x8(r31)
	lfs f1, 0xc(r31)
	lfs f0, 0x1c(r31)
	fadds f0, f1, f0
	stfs f0, 0xc(r31)
	lfs f1, 0x10(r31)
	lfs f0, 0x20(r31)
	fadds f0, f1, f0
	stfs f0, 0x10(r31)
	lwz r3, 0xc(r30)
	lfs f0, 0x8(r31)
	lfs f1, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r30)
	lfs f0, 0xc(r31)
	lfs f1, 0x1c(r3)
	fadds f0, f1, f0
	stfs f0, 0x1c(r3)
	lwz r3, 0xc(r30)
	lfs f0, 0x10(r31)
	lfs f1, 0x2c(r3)
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	b @65
	@151:
	li r0, 0x31
	sth r0, 0x2(r31)
	b @65
	@152:
	entry jt_0000298C
	lis r3, wp@ha
	lwz r4, wp@l(r3)
	lhz r3, 0x0(r4)
	rlwinm. r0, r3, 0, 19, 19
	beq @153
	rlwinm. r0, r3, 0, 18, 18
	beq @153
	li r0, 0x3e
	sth r0, 0x2(r31)
	b @65
	@153:
	lha r0, 0x38(r4)
	cmpwi r0, 0xfa
	bge @154
	lwz r3, 0xc(r30)
	bl PSMTXIdentity
	li r5, 0x3
	lis r6, wp@ha
	divw r4, r29, r5
	lwz r3, 0xc(r30)
	addi r7, r6, wp@l
	lwz r6, 0x0(r7)
	li r0, 0x0
	mullw r4, r4, r5
	subf r4, r4, r29
	mulli r8, r4, 0xc
	addi r4, r8, 0x14
	lfsx f0, r6, r4
	addi r5, r8, 0x18
	addi r4, r8, 0x1c
	stfs f0, 0xc(r3)
	lwz r6, 0x0(r7)
	lwz r3, 0xc(r30)
	lfsx f0, r6, r5
	stfs f0, 0x1c(r3)
	lwz r5, 0x0(r7)
	lwz r3, 0xc(r30)
	lfsx f0, r5, r4
	stfs f0, 0x2c(r3)
	sth r0, 0x0(r31)
	sth r0, 0x2(r31)
	sth r0, 0x4(r31)
	b @65
	@154:
	li r0, 0x3e
	sth r0, 0x2(r31)
	b @65
	@155:
	entry jt_00002A40
	lha r0, 0x4(r31)
	cmpwi r0, 0x1e
	bge @156
	lis r4, float_0p20944_eki_00008dbc@ha
	addi r3, r1, 0x74
	addi r5, r4, float_0p20944_eki_00008dbc@l
	li r4, 0x79
	lfs f1, 0x0(r5)
	bl PSMTXRotRad
	lwz r3, 0xc(r30)
	addi r4, r1, 0x74
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	lha r3, 0x4(r31)
	addi r0, r3, 0x1
	sth r0, 0x4(r31)
	b @65
	@156:
	li r3, 0x3
	lwz r5, 0x0(r30)
	divw r0, r29, r3
	lis r4, wp@ha
	ori r5, r5, 0x2
	stw r5, 0x0(r30)
	lwz r5, 0xc(r30)
	lfs f1, 0xc(r5)
	mullw r0, r0, r3
	lwz r3, wp@l(r4)
	lfs f2, 0x2c(r5)
	subf r0, r0, r29
	mulli r0, r0, 0xc
	add r3, r3, r0
	lfs f3, 0x14(r3)
	lfs f4, 0x1c(r3)
	bl distABf
	lis r4, float_100_eki_00008d70@ha
	lis r3, float_0p5_eki_00008d4c@ha
	lfs f2, float_100_eki_00008d70@l(r4)
	lfs f0, float_0p5_eki_00008d4c@l(r3)
	fsubs f1, f2, f1
	fmuls f0, f1, f0
	fctiwz f0, f0
	stfd f0, 0xb0(r1)
	lwz r0, 0xb4(r1)
	sth r0, 0x4(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@157:
	entry jt_00002B0C
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @65
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@158:
	entry jt_00002B30
	lwz r4, 0xc(r30)
	lis r3, double_300_eki_00008dc0@ha
	lfd f1, double_300_eki_00008dc0@l(r3)
	lfs f0, 0xc(r4)
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge @159
	lfs f0, 0x2c(r4)
	fabs f0, f0
	fcmpo cr0, f0, f1
	bge @159
	bl rand
	li r4, 0x3
	xoris r5, r3, 0x8000
	divw r0, r29, r4
	lwz r6, 0xc(r30)
	lis r3, 0x4330
	stw r5, 0xb4(r1)
	lis r5, double_to_int_eki_00008df8@ha
	lfs f3, 0xc(r6)
	stw r3, 0xb0(r1)
	lis r3, float_32767_eki_00008d50@ha
	lfs f0, float_32767_eki_00008d50@l(r3)
	mullw r0, r0, r4
	lfd f2, double_to_int_eki_00008df8@l(r5)
	lis r3, wp@ha
	lfd f1, 0xb0(r1)
	addi r3, r3, wp@l
	lfs f4, 0x2c(r6)
	fsubs f1, f1, f2
	subf r0, r0, r29
	mulli r0, r0, 0xc
	lwz r3, 0x0(r3)
	fdivs f28, f1, f0
	add r3, r3, r0
	lfs f1, 0x14(r3)
	lfs f2, 0x1c(r3)
	bl angleABf
	lis r3, float_90_eki_00008d94@ha
	lis r4, float_neg45_eki_00008d90@ha
	addi r5, r3, float_90_eki_00008d94@l
	lfs f0, float_neg45_eki_00008d90@l(r4)
	lfs f2, 0x0(r5)
	lis r3, float_6p2832_eki_00008d00@ha
	addi r8, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	fmadds f0, f28, f2, f0
	addi r7, r4, float_360_eki_00008d04@l
	lis r6, float_0p00761_eki_00008d08@ha
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lis r4, float_1_eki_00008d10@ha
	fadds f2, f1, f0
	lfs f1, 0x0(r8)
	lfs f0, 0x0(r7)
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @160
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @161
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b @162
	@161:
	fsubs f0, f5, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @162
	@160:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @163
	fsubs f1, f5, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @162
	@163:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@162:
	lis r3, float_3p1416_eki_00008d14@ha
	lwz r6, 0xc(r30)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_15_eki_00008d60@ha
	lfs f2, float_15_eki_00008d60@l(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f0, 0xc(r6)
	fcmpo cr0, f5, f1
	lis r5, float_0p03705_eki_00008d20@ha
	lis r3, float_1_eki_00008d10@ha
	fmadds f30, f2, f4, f0
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @164
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @165
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @166
	@165:
	fsubs f0, f5, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @166
	@164:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @167
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @166
	@167:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@166:
	lis r3, float_15_eki_00008d60@ha
	lfs f0, 0x2c(r6)
	lfs f1, float_15_eki_00008d60@l(r3)
	fnmsubs f27, f1, f4, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lis r3, float_1_eki_00008d10@ha
	lfs f0, 0x0(r5)
	lfd f1, 0xa8(r1)
	lis r4, zero_eki_00008cf4@ha
	addi r5, r4, zero_eki_00008cf4@l
	lfs f5, float_1_eki_00008d10@l(r3)
	fsubs f1, f1, f2
	lfs f2, 0x0(r5)
	lis r4, float_3_eki_00008dc8@ha
	fmr f3, f27
	lfs f4, float_3_eki_00008dc8@l(r4)
	mr r3, r30
	fdivs f6, f1, f0
	lha r5, 0x2(r31)
	mr r4, r31
	li r6, 0x1
	fmadds f0, f28, f2, f5
	fmr f1, f30
	fmadds f5, f6, f2, f5
	fmuls f4, f4, f0
	bl moamoa_jump
	b @65
	@159:
	li r0, 0x3e
	sth r0, 0x2(r31)
	b @65
	@168:
	entry jt_00002E50
	lhz r0, 0x0(r31)
	ori r0, r0, 0x20
	sth r0, 0x0(r31)
	lwz r0, 0x0(r30)
	clrrwi r0, r0, 1
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	b @65
	@169:
	entry jt_00002E78
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xb4(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f2, double_to_int_eki_00008df8@l(r4)
	stw r0, 0xb0(r1)
	lfs f0, float_32767_eki_00008d50@l(r3)
	lfd f1, 0xb0(r1)
	fsubs f1, f1, f2
	fdivs f28, f1, f0
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0xac(r1)
	lis r4, double_to_int_eki_00008df8@ha
	lfd f1, double_to_int_eki_00008df8@l(r4)
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xa8(r1)
	addi r5, r3, float_32767_eki_00008d50@l
	lfs f2, 0x0(r5)
	lis r4, float_1_eki_00008d10@ha
	lfd f0, 0xa8(r1)
	lis r3, float_2_eki_00008da4@ha
	srawi r0, r29, 1
	fsubs f3, f0, f1
	lfs f0, float_2_eki_00008da4@l(r3)
	lfs f1, float_1_eki_00008d10@l(r4)
	addze r3, r0
	fdivs f2, f3, f2
	fmadds f31, f2, f1, f0
	bl irand
	lis r5, float_90_eki_00008d94@ha
	lis r4, float_225_eki_00008dcc@ha
	lfs f1, float_90_eki_00008d94@l(r5)
	lis r7, float_0p00761_eki_00008d08@ha
	lfs f0, float_225_eki_00008dcc@l(r4)
	lis r6, float_6p2832_eki_00008d00@ha
	lis r5, float_360_eki_00008d04@ha
	lis r4, float_3p1416_eki_00008d14@ha
	fmadds f0, f28, f1, f0
	lfs f1, float_6p2832_eki_00008d00@l(r6)
	lis r6, float_0p16605_eki_00008d0c@ha
	sth r3, 0x4(r31)
	lfs f4, float_0p00761_eki_00008d08@l(r7)
	fmuls f2, f1, f0
	lfs f0, float_360_eki_00008d04@l(r5)
	lis r5, float_1_eki_00008d10@ha
	lfs f1, float_3p1416_eki_00008d14@l(r4)
	fdivs f30, f2, f0
	lfs f3, float_0p16605_eki_00008d0c@l(r6)
	lfs f2, float_1_eki_00008d10@l(r5)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @170
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @171
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f30
	b @172
	@171:
	fsubs f0, f30, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b @172
	@170:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f30, f0
	bge @173
	fsubs f1, f30, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b @172
	@173:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@172:
	fmuls f0, f31, f4
	stfs f0, 0x8(r31)
	bl rand
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_eki_00008df8@ha
	stw r3, 0xb4(r1)
	addi r5, r4, double_to_int_eki_00008df8@l
	lis r3, float_32767_eki_00008d50@ha
	stw r0, 0xb0(r1)
	addi r4, r3, float_32767_eki_00008d50@l
	lfd f2, 0x0(r5)
	lis r3, float_1_eki_00008d10@ha
	lfd f1, 0xb0(r1)
	addi r5, r3, float_1_eki_00008d10@l
	lfs f0, 0x0(r4)
	lis r4, float_0p03705_eki_00008d20@ha
	fsubs f3, f1, f2
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r3, float_0p4967_eki_00008d24@ha
	lfs f2, 0x0(r5)
	fdivs f0, f3, f0
	lfs f4, float_0p03705_eki_00008d20@l(r4)
	lfs f3, float_0p4967_eki_00008d24@l(r3)
	fmadds f0, f0, f2, f2
	fcmpo cr0, f30, f1
	stfs f0, 0xc(r31)
	cror eq, lt, eq
	bne @174
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f30, f1
	cror eq, lt, eq
	bne @175
	fmuls f0, f30, f30
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b @176
	@175:
	fsubs f0, f30, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @176
	@174:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f30, f0
	bge @177
	fsubs f0, f30, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @176
	@177:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f30, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	@176:
	fneg f0, f4
	fmuls f0, f31, f0
	stfs f0, 0x10(r31)
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@178:
	entry jt_00003104
	lha r3, 0x4(r31)
	subi r3, r3, 0x1
	extsh. r0, r3
	sth r3, 0x4(r31)
	bge @65
	lha r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b @65
	@179:
	entry jt_00003128
	lis r3, float_1p1_eki_00008dd0@ha
	lis r4, float_1p02_eki_00008dd4@ha
	addi r6, r3, float_1p1_eki_00008dd0@l
	lis r3, float_0p20944_eki_00008dbc@ha
	lfs f1, 0x8(r31)
	addi r5, r4, float_1p02_eki_00008dd4@l
	lfs f3, 0x0(r6)
	addi r4, r3, float_0p20944_eki_00008dbc@l
	lfs f0, 0x0(r5)
	addi r3, r1, 0x44
	fmuls f2, f1, f3
	lfs f1, 0x0(r4)
	li r4, 0x79
	stfs f2, 0x8(r31)
	lfs f2, 0xc(r31)
	fmuls f0, f2, f0
	stfs f0, 0xc(r31)
	lfs f0, 0x10(r31)
	fmuls f0, f0, f3
	stfs f0, 0x10(r31)
	lwz r5, 0xc(r30)
	lfs f0, 0x8(r31)
	lfs f2, 0xc(r5)
	fadds f0, f2, f0
	stfs f0, 0xc(r5)
	lwz r5, 0xc(r30)
	lfs f0, 0xc(r31)
	lfs f2, 0x1c(r5)
	fadds f0, f2, f0
	stfs f0, 0x1c(r5)
	lwz r5, 0xc(r30)
	lfs f0, 0x10(r31)
	lfs f2, 0x2c(r5)
	fadds f0, f2, f0
	stfs f0, 0x2c(r5)
	bl PSMTXRotRad
	lwz r3, 0xc(r30)
	addi r4, r1, 0x44
	mr r5, r3
	bl PSMTXConcat
	lwz r0, 0x0(r30)
	lis r3, float_neg1000_eki_00008dd8@ha
	lfs f0, float_neg1000_eki_00008dd8@l(r3)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	lwz r3, 0xc(r30)
	lfs f1, 0xc(r3)
	fcmpo cr0, f1, f0
	bge @65
	li r0, 0x3e
	sth r0, 0x2(r31)
	@65:
	entry jt_000031F4
	lhz r0, 0x0(r31)
	andi. r0, r0, 0x98
	bne @180
	lwz r4, 0xc(r30)
	lis r3, float_280_eki_00008ddc@ha
	lfs f0, float_280_eki_00008ddc@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	ble @181
	stfs f0, 0xc(r4)
	@181:
	lwz r4, 0xc(r30)
	lis r3, float_neg120_eki_00008de0@ha
	lfs f0, float_neg120_eki_00008de0@l(r3)
	lfs f1, 0xc(r4)
	fcmpo cr0, f1, f0
	bge @182
	stfs f0, 0xc(r4)
	@182:
	lwz r4, 0xc(r30)
	lis r3, float_70_eki_00008de4@ha
	lfs f0, float_70_eki_00008de4@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	ble @183
	stfs f0, 0x2c(r4)
	@183:
	lwz r4, 0xc(r30)
	lis r3, float_neg70_eki_00008de8@ha
	lfs f0, float_neg70_eki_00008de8@l(r3)
	lfs f1, 0x2c(r4)
	fcmpo cr0, f1, f0
	bge @180
	stfs f0, 0x2c(r4)
	@180:
	lwz r3, 0xc(r30)
	addi r29, r29, 0x1
	lfs f0, 0xc(r3)
	stfs f0, 0x28(r31)
	lwz r3, 0xc(r30)
	addi r30, r30, 0x20
	lfs f0, 0x2c(r3)
	stfs f0, 0x2c(r31)
	addi r31, r31, 0x50
	@21:
	lwz r3, 0x0(r27)
	lwz r0, 0x4(r3)
	cmpw r29, r0
	blt @22
	bl extGetPosePtr
	lis r4, wp@ha
	lis r7, float_60_eki_00008dec@ha
	addi r26, r4, wp@l
	lis r6, float_1000_eki_00008df0@ha
	lwz r9, 0x0(r26)
	lis r5, float_1_eki_00008d10@ha
	lis r4, double_to_int_eki_00008df8@ha
	lis r8, gp@ha
	lwz r19, 0x8(r9)
	mr r20, r3
	lfs f31, float_60_eki_00008dec@l(r7)
	addi r25, r8, gp@l
	lfs f30, float_1000_eki_00008df0@l(r6)
	li r21, 0x0
	lfs f29, float_1_eki_00008d10@l(r5)
	lis r24, 0x8000
	lfd f28, double_to_int_eki_00008df8@l(r4)
	lis r27, 0x4330
	b @184
	@185:
	lwz r3, 0xf8(r24)
	li r0, 0x3e8
	lwz r4, 0x0(r25)
	li r5, 0x0
	srwi r3, r3, 2
	lha r8, 0x3c(r19)
	divwu r6, r3, r0
	lwz r23, 0x3c(r4)
	lwz r0, 0x44(r19)
	lwz r22, 0x38(r4)
	subfc r4, r0, r23
	lwz r0, 0x40(r19)
	mulli r8, r8, 0x28
	subfe r3, r0, r22
	addi r18, r8, 0x50
	add r18, r7, r18
	bl __div2u
	bl __cvt_ull_flt
	fmuls f1, f31, f1
	lfs f0, 0x1c(r18)
	fdivs f1, f1, f30
	fdivs f1, f1, f0
	fcmpo cr0, f1, f29
	cror eq, gt, eq
	bne @186
	stw r23, 0x44(r19)
	lis r3, zero_eki_00008cf4@ha
	lfs f1, zero_eki_00008cf4@l(r3)
	stw r22, 0x40(r19)
	@186:
	lwz r3, 0x24(r18)
	addi r21, r21, 0x1
	stw r27, 0xb0(r1)
	addi r19, r19, 0x50
	subi r0, r3, 0x1
	lwz r3, 0x20(r18)
	xoris r0, r0, 0x8000
	stw r0, 0xb4(r1)
	lfd f0, 0xb0(r1)
	fsubs f0, f0, f28
	fmuls f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0xa8(r1)
	lwz r0, 0xac(r1)
	add r0, r3, r0
	stw r0, 0x10(r20)
	addi r20, r20, 0x20
	@184:
	lwz r7, 0x0(r26)
	lwz r0, 0x4(r7)
	cmpw r21, r0
	blt @185
	lhz r0, 0x0(r7)
	rlwinm. r0, r0, 0, 27, 27
	beq @187
	lis r3, zero_eki_00008cf4@ha
	lfs f0, zero_eki_00008cf4@l(r3)
	stfs f0, 0x174(r28)
	stfs f0, 0x178(r28)
	stfs f0, 0x17c(r28)
	b @188
	@187:
	lis r3, vec3_eki_0000892c@ha
	lfs f2, 0x174(r28)
	addi r6, r3, vec3_eki_0000892c@l
	lfs f1, 0x178(r28)
	lwz r5, 0x0(r6)
	addi r3, r1, 0x2c
	lwz r4, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0x8(r1)
	lfs f0, 0x17c(r28)
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
	lis r3, float_2_eki_00008da4@ha
	lfs f0, float_2_eki_00008da4@l(r3)
	fcmpo cr0, f1, f0
	ble @188
	addi r3, r1, 0x2c
	mr r4, r3
	bl PSVECNormalize
	lis r3, float_2_eki_00008da4@ha
	lfs f0, 0x2c(r1)
	lfs f1, float_2_eki_00008da4@l(r3)
	fmuls f0, f1, f0
	stfs f0, 0x174(r28)
	lfs f0, 0x30(r1)
	fmuls f0, f1, f0
	stfs f0, 0x178(r28)
	lfs f0, 0x34(r1)
	fmuls f0, f1, f0
	stfs f0, 0x17c(r28)
	@188:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	lmw r18, 0xb8(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
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
	lis r4, float_20_eki_00008e08@ha
	lfs f0, float_20_eki_00008e08@l(r4)
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
	lis r4, float_20_eki_00008e08@ha
	lis r3, float_0p5_eki_00008d4c@ha
	lfs f2, 0x1b4(r31)
	lfs f3, float_20_eki_00008e08@l(r4)
	lfs f0, float_0p5_eki_00008d4c@l(r3)
	fadds f2, f3, f2
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	bge @4
	lwz r3, 0xc(r29)
	lis r4, float_10_eki_00008e0c@ha
	lfs f1, float_10_eki_00008e0c@l(r4)
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
	lis r4, float_90_eki_00008d94@ha
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_eki_00008d94@l(r4)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	lfs f0, 0x0(r5)
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fmuls f2, f0, f1
	lfs f0, float_360_eki_00008d04@l(r4)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f6, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne @8
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
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
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@10:
	lis r3, float_3p1416_eki_00008d14@ha
	lis r4, float_35_eki_00008e10@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r5, float_0p03705_eki_00008d20@ha
	lfs f2, float_35_eki_00008e10@l(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	lfs f0, 0x8c(r31)
	fcmpo cr0, f6, f1
	lis r3, float_1_eki_00008d10@ha
	lfs f5, float_0p03705_eki_00008d20@l(r5)
	fmadds f3, f2, f4, f0
	lfs f4, float_0p4967_eki_00008d24@l(r4)
	lfs f2, float_1_eki_00008d10@l(r3)
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f6, f0
	bge @15
	fsubs f0, f6, f1
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	fneg f5, f5
	b @14
	@15:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f6, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f2
	@14:
	lis r3, float_35_eki_00008e10@ha
	lwz r4, 0xc(r29)
	lfs f0, 0x94(r31)
	lfs f2, float_35_eki_00008e10@l(r3)
	lfs f1, 0xc(r4)
	fnmsubs f4, f2, f5, f0
	lfs f2, 0x2c(r4)
	bl distABf
	lis r3, float_35_eki_00008e10@ha
	lfs f0, float_35_eki_00008e10@l(r3)
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
	lis r3, vec3_eki_000088b4@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_eki_000088b4@l
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
	lis r3, float_65_eki_00008e14@ha
	lfs f0, float_65_eki_00008e14@l(r3)
	fcmpo cr0, f1, f0
	bge @16
	li r3, 0x2
	b @2
	@16:
	lis r4, wp@ha
	lis r3, zero_eki_00008cf4@ha
	addi r4, r4, wp@l
	lfs f0, zero_eki_00008cf4@l(r3)
	lwz r4, 0x0(r4)
	lfs f1, 0x55c(r4)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @17
	lis r3, vec3_eki_000088c0@ha
	lwz r8, 0xc(r29)
	addi r7, r3, vec3_eki_000088c0@l
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
	lis r3, float_30_eki_00008da0@ha
	lfs f0, float_30_eki_00008da0@l(r3)
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
	lis r3, vec3_eki_000088cc@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_eki_000088cc@l
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
	lis r3, float_30_eki_00008da0@ha
	lfs f0, float_30_eki_00008da0@l(r3)
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
	lis r3, vec3_eki_000088d8@ha
	lwz r7, 0xc(r29)
	addi r6, r3, vec3_eki_000088d8@l
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
	lis r3, float_50_eki_00008d5c@ha
	lfs f0, float_50_eki_00008d5c@l(r3)
	fcmpo cr0, f1, f0
	bge @19
	li r3, 0x4
	b @2
	@19:
	lis r3, vec3_eki_000088e4@ha
	lwz r11, 0xc(r29)
	addi r5, r3, vec3_eki_000088e4@l
	lis r3, vec3_eki_000088f0@ha
	lwz r4, 0x0(r5)
	addi r9, r3, vec3_eki_000088f0@l
	lwz r0, 0x4(r5)
	lis r3, float_20_eki_00008e08@ha
	lwz r10, 0x8(r5)
	addi r6, r3, float_20_eki_00008e08@l
	stw r4, 0x20(r1)
	lis r3, float_0p5_eki_00008d4c@ha
	lfs f0, 0x8c(r31)
	addi r5, r3, float_0p5_eki_00008d4c@l
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
	lis r3, vec3_eki_000088fc@ha
	lwz r5, 0xc(r29)
	addi r7, r3, vec3_eki_000088fc@l
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
	lis r3, float_40_eki_00008e18@ha
	fabs f1, f1
	lfs f0, float_40_eki_00008e18@l(r3)
	fcmpo cr0, f1, f0
	bge @21
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lfs f0, 0x1a0(r31)
	lfs f1, 0x0(r5)
	lis r5, float_0p16605_eki_00008d0c@ha
	lis r4, float_360_eki_00008d04@ha
	lis r3, float_3p1416_eki_00008d14@ha
	fmuls f2, f1, f0
	lfs f0, float_360_eki_00008d04@l(r4)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r4, float_1_eki_00008d10@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	fdivs f5, f2, f0
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @22
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
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
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	@24:
	fsubs f6, f31, f29
	lis r3, float_6p2832_eki_00008d00@ha
	addi r8, r3, float_6p2832_eki_00008d00@l
	lis r6, float_0p03705_eki_00008d20@ha
	lis r3, float_360_eki_00008d04@ha
	lfs f3, 0x0(r8)
	fmuls f0, f6, f4
	addi r7, r3, float_360_eki_00008d04@l
	lis r5, float_0p4967_eki_00008d24@ha
	lis r3, float_3p1416_eki_00008d14@ha
	lis r4, float_1_eki_00008d10@ha
	lfs f5, float_0p03705_eki_00008d20@l(r6)
	fneg f1, f0
	lfs f0, 0x0(r7)
	lfs f4, float_0p4967_eki_00008d24@l(r5)
	stfs f1, 0x174(r31)
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lfs f2, 0x1a0(r31)
	fmuls f2, f3, f2
	lfs f3, float_1_eki_00008d10@l(r4)
	fdivs f2, f2, f0
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @26
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f2, f0
	bge @29
	fsubs f2, f2, f1
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	fneg f5, f5
	b @28
	@29:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f2, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f2, f1, f0
	fmuls f0, f2, f2
	fmsubs f5, f5, f0, f4
	fmadds f5, f5, f0, f3
	@28:
	fmuls f0, f6, f5
	stfs f0, 0x17c(r31)
	b @20
	@21:
	lis r3, float_6p2832_eki_00008d00@ha
	lis r6, float_0p00761_eki_00008d08@ha
	addi r5, r3, float_6p2832_eki_00008d00@l
	lis r4, float_360_eki_00008d04@ha
	lfs f0, 0x0(r5)
	lis r3, float_3p1416_eki_00008d14@ha
	lis r5, float_0p16605_eki_00008d0c@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	fmuls f2, f0, f30
	lfs f0, float_360_eki_00008d04@l(r4)
	lis r4, float_1_eki_00008d10@ha
	lfs f4, float_0p00761_eki_00008d08@l(r6)
	lfs f3, float_0p16605_eki_00008d0c@l(r5)
	fdivs f5, f2, f0
	lfs f2, float_1_eki_00008d10@l(r4)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne @30
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
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
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	@32:
	lwz r4, 0xc(r29)
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f1, float_3p1416_eki_00008d14@l(r3)
	lis r5, float_0p03705_eki_00008d20@ha
	lfs f0, 0xc(r4)
	lis r4, float_0p4967_eki_00008d24@ha
	fcmpo cr0, f5, f1
	lis r3, float_1_eki_00008d10@ha
	fnmsubs f2, f31, f4, f0
	lfs f0, 0x8c(r31)
	lfs f4, float_0p03705_eki_00008d20@l(r5)
	lfs f3, float_0p4967_eki_00008d24@l(r4)
	fsubs f0, f2, f0
	lfs f2, float_1_eki_00008d10@l(r3)
	stfs f0, 0x174(r31)
	cror eq, lt, eq
	bne @34
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f5, f0
	bge @37
	fsubs f0, f5, f1
	fmuls f0, f0, f0
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b @36
	@37:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f5, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
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
	lis r4, zero_eki_00008cf4@ha
	lis r3, float_100_eki_00008d70@ha
	addi r5, r4, zero_eki_00008cf4@l
	lfs f0, float_100_eki_00008d70@l(r3)
	lfs f4, 0x0(r5)
	lis r4, float_1E06_eki_00008e1c@ha
	lfs f7, float_1E06_eki_00008e1c@l(r4)
	lis r3, float_neg1_eki_00008cfc@ha
	fmr f6, f4
	lfs f5, float_neg1_eki_00008cfc@l(r3)
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
	lis r3, double_30_eki_00008e20@ha
	fsubs f1, f28, f0
	lfd f0, double_30_eki_00008e20@l(r3)
	fabs f1, f1
	fcmpo cr0, f1, f0
	ble @2
	lis r3, float_0p1_eki_00008d54@ha
	lfs f0, float_0p1_eki_00008d54@l(r3)
	fsubs f31, f31, f0
	fadds f30, f30, f0
	@2:
	lfs f28, 0x1c(r1)
	@1:
	lis r3, vec3_eki_000088a8@ha
	addi r4, r3, vec3_eki_000088a8@l
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
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_0p5_eki_00008d4c@ha
	fdivs f0, f31, f0
	addi r6, r4, double_to_int_eki_00008df8@l
	addi r4, r3, float_0p5_eki_00008d4c@l
	lis r3, float_180_eki_00008d9c@ha
	stw r5, 0x40(r1)
	li r0, 0x3
	fctiwz f2, f0
	lfs f0, float_180_eki_00008d9c@l(r3)
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
	lis r3, g5_mt_s758@ha
	addi r3, r3, g5_mt_s758@l
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
	lis r3, str_0000041C@ha
	addi r3, r3, str_0000041C@l
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
	lis r3, str_0000041C@ha
	addi r3, r3, str_0000041C@l
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
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stfd f26, 0xe0(r1)
	psq_st f26, 0xe8(r1), 0, 0
	stfd f25, 0xd0(r1)
	psq_st f25, 0xd8(r1), 0, 0
	stfd f24, 0xc0(r1)
	psq_st f24, 0xc8(r1), 0, 0
	stfd f23, 0xb0(r1)
	psq_st f23, 0xb8(r1), 0, 0
	stfd f22, 0xa0(r1)
	psq_st f22, 0xa8(r1), 0, 0
	stfd f21, 0x90(r1)
	psq_st f21, 0x98(r1), 0, 0
	stfd f20, 0x80(r1)
	psq_st f20, 0x88(r1), 0, 0
	stmw r17, 0x44(r1)
	li r3, 0x870
	bl _mapAlloc
	lis r5, wp@ha
	li r4, 0x0
	addi r6, r5, wp@l
	li r5, 0x870
	stw r3, 0x0(r6)
	bl memset
	lis r5, wp@ha
	lis r3, vec3_eki_00008884@ha
	addi r7, r3, vec3_eki_00008884@l
	lis r4, vec3_eki_00008890@ha
	addi r9, r5, wp@l
	lwz r6, 0x0(r7)
	lwz r8, 0x0(r9)
	lis r3, vec3_eki_0000889c@ha
	lwz r0, 0x4(r7)
	addi r5, r4, vec3_eki_00008890@l
	addi r4, r3, vec3_eki_0000889c@l
	stw r6, 0x14(r8)
	stw r0, 0x18(r8)
	lwz r0, 0x8(r7)
	stw r0, 0x1c(r8)
	lwz r6, 0x0(r9)
	lwz r3, 0x0(r5)
	lwz r0, 0x4(r5)
	stw r3, 0x20(r6)
	stw r0, 0x24(r6)
	lwz r0, 0x8(r5)
	stw r0, 0x28(r6)
	lwz r5, 0x0(r9)
	lwz r3, 0x0(r4)
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
	lis r18, double_to_int_eki_00008df8@ha
	addi r21, r4, wp@l
	lis r17, float_32767_eki_00008d50@ha
	lwz r4, 0x0(r21)
	lis r11, zero_eki_00008cf4@ha
	addi r20, r18, double_to_int_eki_00008df8@l
	lis r12, float_6p2832_eki_00008d00@ha
	addi r18, r12, float_6p2832_eki_00008d00@l
	addi r19, r17, float_32767_eki_00008d50@l
	lis r10, float_100_eki_00008d70@ha
	addi r25, r11, zero_eki_00008cf4@l
	lis r9, float_0p16605_eki_00008d0c@ha
	lis r22, str_0000004C@ha
	addi r17, r10, float_100_eki_00008d70@l
	lis r8, float_1_eki_00008d10@ha
	addi r10, r8, float_1_eki_00008d10@l
	addi r11, r9, float_0p16605_eki_00008d0c@l
	lis r7, float_3p1416_eki_00008d14@ha
	lis r23, str_00000040@ha
	addi r9, r7, float_3p1416_eki_00008d14@l
	lis r6, float_0p4967_eki_00008d24@ha
	addi r7, r6, float_0p4967_eki_00008d24@l
	lis r5, float_1E06_eki_00008e1c@ha
	addi r6, r5, float_1E06_eki_00008e1c@l
	lis r12, float_0p00761_eki_00008d08@ha
	lis r8, float_0p03705_eki_00008d20@ha
	lis r5, float_neg1_eki_00008cfc@ha
	lwz r29, 0x8(r4)
	mr r30, r3
	lfd f26, 0x0(r20)
	addi r22, r22, str_0000004C@l
	lfs f27, 0x0(r19)
	addi r23, r23, str_00000040@l
	lfs f28, 0x0(r18)
	addi r26, r12, float_0p00761_eki_00008d08@l
	lfs f29, 0x0(r25)
	addi r27, r8, float_0p03705_eki_00008d20@l
	lfs f30, 0x0(r17)
	addi r28, r5, float_neg1_eki_00008cfc@l
	lfs f24, 0x0(r11)
	li r31, 0x0
	lfs f25, 0x0(r10)
	lis r24, 0x4330
	lfs f31, 0x0(r9)
	lfs f23, 0x0(r7)
	lfs f20, 0x0(r6)
	b @1
	@2:
	li r0, 0x0
	mr r17, r22
	sth r0, 0x0(r29)
	mr r18, r23
	sth r0, 0x2(r29)
	sth r0, 0x4(r29)
	lhz r0, 0x0(r29)
	lwz r3, 0x0(r21)
	rlwinm. r0, r0, 0, 20, 20
	addi r19, r3, 0x50
	beq @3
	lbz r4, 0x4c(r29)
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r18, 0x0(r3)
	blt @4
	lwz r17, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_00000578@ha
	addi r17, r3, str_00000578@l
	@3:
	li r20, 0x0
	b @5
	@6:
	mr r3, r19
	mr r4, r18
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	mr r4, r17
	addi r3, r19, 0x10
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	@7:
	addi r20, r20, 0x1
	addi r19, r19, 0x28
	@5:
	lwz r3, 0x0(r21)
	lwz r0, 0x4c(r3)
	cmpw r20, r0
	blt @6
	@8:
	lwz r3, 0x0(r21)
	lwz r0, 0x4c(r3)
	cmpw r20, r0
	bge @9
	lha r0, 0x3c(r29)
	cmpw r0, r20
	beq @9
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 29, 29
	beq @10
	lis r4, str_0000057C@ha
	mr r3, r17
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_00000580@ha
	mr r3, r17
	addi r4, r4, str_00000580@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@11:
	lis r3, gp@ha
	sth r20, 0x3c(r29)
	addi r3, r3, gp@l
	lwz r3, 0x0(r3)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x44(r29)
	stw r0, 0x40(r29)
	@9:
	bl rand
	xoris r0, r3, 0x8000
	stw r24, 0x28(r1)
	stw r0, 0x2c(r1)
	lfd f0, 0x28(r1)
	fsubs f0, f0, f26
	fdivs f0, f0, f27
	fmadds f22, f0, f28, f29
	bl rand
	xoris r3, r3, 0x8000
	lwz r0, 0x0(r30)
	stw r3, 0x34(r1)
	ori r0, r0, 0x13
	stw r24, 0x30(r1)
	lfd f0, 0x30(r1)
	stw r0, 0x0(r30)
	fsubs f0, f0, f26
	lwz r3, 0xc(r30)
	fdivs f0, f0, f27
	fmadds f21, f0, f30, f29
	bl PSMTXIdentity
	fcmpo cr0, f22, f31
	lfs f2, 0x0(r26)
	cror eq, lt, eq
	bne @12
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f22, f1
	cror eq, lt, eq
	bne @13
	fmuls f0, f22, f22
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f22
	b @14
	@13:
	fsubs f0, f22, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	b @14
	@12:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f22, f0
	bge @15
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f0, float_3p1416_eki_00008d14@l(r3)
	fsubs f1, f22, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	b @14
	@15:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f22, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f2, f2, f0, f24
	fmadds f2, f2, f0, f25
	fmuls f2, f2, f1
	fneg f2, f2
	@14:
	lwz r4, 0x0(r21)
	fcmpo cr0, f22, f31
	lwz r3, 0xc(r30)
	lfs f0, 0x14(r4)
	lfs f3, 0x0(r27)
	fmadds f0, f21, f2, f0
	stfs f0, 0xc(r3)
	lwz r3, 0xc(r30)
	stfs f29, 0x1c(r3)
	cror eq, lt, eq
	bne @16
	lis r3, float_1p5708_eki_00008d18@ha
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fcmpo cr0, f22, f1
	cror eq, lt, eq
	bne @17
	fmuls f0, f22, f22
	fmsubs f3, f3, f0, f23
	fmadds f3, f3, f0, f25
	b @18
	@17:
	fsubs f0, f22, f1
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f3, f3, f0, f23
	fmadds f3, f3, f0, f25
	fneg f3, f3
	b @18
	@16:
	lis r3, float_4p7124_eki_00008d1c@ha
	lfs f0, float_4p7124_eki_00008d1c@l(r3)
	fcmpo cr0, f22, f0
	bge @19
	lis r3, float_3p1416_eki_00008d14@ha
	lfs f0, float_3p1416_eki_00008d14@l(r3)
	fsubs f0, f22, f0
	fmuls f0, f0, f0
	fmsubs f3, f3, f0, f23
	fmadds f3, f3, f0, f25
	fneg f3, f3
	b @18
	@19:
	lis r3, float_1p5708_eki_00008d18@ha
	fsubs f0, f22, f0
	lfs f1, float_1p5708_eki_00008d18@l(r3)
	fsubs f0, f1, f0
	fmuls f0, f0, f0
	fmsubs f3, f3, f0, f23
	fmadds f3, f3, f0, f25
	@18:
	lwz r3, 0x0(r21)
	addi r4, r1, 0x20
	lfs f4, 0x0(r25)
	addi r5, r1, 0x1c
	lfs f0, 0x1c(r3)
	addi r6, r1, 0x18
	lwz r3, 0xc(r30)
	fmr f6, f4
	fnmsubs f0, f21, f3, f0
	lfs f5, 0x0(r28)
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	addi r9, r1, 0xc
	stfs f0, 0xc(r3)
	addi r10, r1, 0x8
	li r3, 0x0
	stfs f29, 0x18(r1)
	stfs f29, 0x1c(r1)
	stfs f29, 0x20(r1)
	stfs f20, 0x14(r1)
	lwz r11, 0xc(r30)
	lfs f0, 0x1c(r11)
	lfs f1, 0xc(r11)
	fadds f2, f30, f0
	lfs f3, 0x2c(r11)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq @20
	lfs f0, 0x1c(r1)
	lwz r3, 0xc(r30)
	stfs f0, 0x1c(r3)
	@20:
	addi r31, r31, 0x1
	addi r30, r30, 0x20
	addi r29, r29, 0x50
	@1:
	lwz r3, 0x0(r21)
	lwz r0, 0x4(r3)
	cmpw r31, r0
	blt @2
	li r17, 0x0
	@21:
	bl ext_moamoa_main
	addi r17, r17, 0x1
	cmpwi r17, 0x258
	blt @21
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	psq_l f26, 0xe8(r1), 0, 0
	lfd f26, 0xe0(r1)
	psq_l f25, 0xd8(r1), 0, 0
	lfd f25, 0xd0(r1)
	psq_l f24, 0xc8(r1), 0, 0
	lfd f24, 0xc0(r1)
	psq_l f23, 0xb8(r1), 0, 0
	lfd f23, 0xb0(r1)
	psq_l f22, 0xa8(r1), 0, 0
	lfd f22, 0xa0(r1)
	psq_l f21, 0x98(r1), 0, 0
	lfd f21, 0x90(r1)
	psq_l f20, 0x88(r1), 0, 0
	lfd f20, 0x80(r1)
	lmw r17, 0x44(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
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
	lis r4, double_to_int_eki_00008df8@ha
	lis r3, float_32767_eki_00008d50@ha
	lfd f3, double_to_int_eki_00008df8@l(r4)
	stw r0, 0x8(r1)
	fsubs f0, f31, f30
	lfs f1, float_32767_eki_00008d50@l(r3)
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
	lis r5, str_0000004C@ha
	addi r29, r4, wp@l
	mr r24, r3
	lwz r6, 0x0(r29)
	lis r4, str_00000040@ha
	addi r30, r5, str_0000004C@l
	li r25, 0x0
	lwz r23, 0x8(r6)
	addi r31, r4, str_00000040@l
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
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @4
	lwz r26, 0x4(r3)
	@4:
	cmplwi r4, 0xa
	bne @3
	lis r3, str_00000578@ha
	addi r26, r3, str_00000578@l
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
	lis r4, str_0000057C@ha
	mr r3, r26
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @9
	@10:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @11
	lis r4, str_00000580@ha
	mr r3, r26
	addi r4, r4, str_00000580@l
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
	lis r4, str_0000004C@ha
	addi r29, r3, wp@l
	lis r3, str_00000040@ha
	lwz r5, 0x0(r29)
	addi r30, r4, str_0000004C@l
	addi r31, r3, str_00000040@l
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
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r21, 0x0(r3)
	blt @8
	lwz r25, 0x4(r3)
	@8:
	cmplwi r4, 0xa
	bne @7
	lis r3, str_00000578@ha
	addi r25, r3, str_00000578@l
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
	lis r4, str_0000057C@ha
	mr r3, r25
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @13
	@14:
	lhz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 27, 27
	beq @15
	lis r4, str_00000580@ha
	mr r3, r25
	addi r4, r4, str_00000580@l
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
	lis r4, float_1_eki_00008d10@ha
	addi r6, r5, wp@l
	lfs f0, float_1_eki_00008d10@l(r4)
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
	lis r5, str_0000004C@ha
	addi r29, r4, wp@l
	mr r25, r3
	lwz r6, 0x0(r29)
	lis r4, str_00000040@ha
	addi r30, r5, str_0000004C@l
	li r23, 0x0
	lwz r24, 0x8(r6)
	addi r31, r4, str_00000040@l
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
	lis r3, g5_group_tbl_s588@ha
	addi r0, r3, g5_group_tbl_s588@l
	clrlslwi r3, r4, 24, 3
	cmplwi r4, 0x2
	add r3, r0, r3
	lwz r27, 0x0(r3)
	blt @13
	lwz r26, 0x4(r3)
	@13:
	cmplwi r4, 0xa
	bne @12
	lis r3, str_00000578@ha
	addi r26, r3, str_00000578@l
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
	lis r4, str_0000057C@ha
	mr r3, r26
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @18
	@19:
	lhz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 27, 27
	beq @20
	lis r4, str_00000580@ha
	mr r3, r26
	addi r4, r4, str_00000580@l
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
	lis r4, zero_eki_00008cf4@ha
	li r6, 0x0
	addi r5, r4, zero_eki_00008cf4@l
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
	lis r3, g5_group_tbl_s588@ha
	addi r3, r3, g5_group_tbl_s588@l
	clrlslwi r4, r0, 24, 3
	cmplwi r0, 0x2
	lwzx r26, r3, r4
	blt @2
	add r3, r3, r4
	lwz r30, 0x4(r3)
	@2:
	cmplwi r0, 0xa
	bne @1
	lis r3, str_00000578@ha
	addi r0, r3, str_00000578@l
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
	lis r4, str_0000057C@ha
	mr r3, r30
	addi r4, r4, str_0000057C@l
	li r5, 0x1
	bl strncmp
	cmpwi r3, 0x0
	bne @7
	@8:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 27, 27
	beq @9
	lis r4, str_00000580@ha
	mr r3, r30
	addi r4, r4, str_00000580@l
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
	lis r7, float_60_eki_00008dec@ha
	addi r29, r4, wp@l
	lis r6, float_1000_eki_00008df0@ha
	lwz r9, 0x0(r29)
	lis r5, float_1_eki_00008d10@ha
	lis r4, double_to_int_eki_00008df8@ha
	lis r8, gp@ha
	lwz r24, 0x8(r9)
	mr r25, r3
	lfs f28, float_60_eki_00008dec@l(r7)
	addi r30, r8, gp@l
	lfs f29, float_1000_eki_00008df0@l(r6)
	li r26, 0x0
	lfs f30, float_1_eki_00008d10@l(r5)
	lis r31, 0x8000
	lfd f31, double_to_int_eki_00008df8@l(r4)
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
	lis r3, zero_eki_00008cf4@ha
	lfs f1, zero_eki_00008cf4@l(r3)
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
#pragma force_active reset
